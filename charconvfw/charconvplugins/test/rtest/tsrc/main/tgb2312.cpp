/*
* Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description: 
*
*/


#include <e32std.h>
#include <e32base.h>
#include <e32test.h>
#include <f32file.h>
#include <charconv.h>

///////////////////////////////////////////////////////////////////////////////////////

RTest TheTest(_L("TGB2312"));

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//Tests macroses and functions.
//If (!aValue) then the test will be panicked, the test data files will be deleted.
static void Check(TInt aValue, TInt aLine)
	{
	if(!aValue)
		{
		TheTest(EFalse, aLine);
		}
	}
//If (aValue != aExpected) then the test will be panicked, the test data files will be deleted.
static void Check(TInt aValue, TInt aExpected, TInt aLine)
	{
	if(aValue != aExpected)
		{
		RDebug::Print(_L("*** Expected error: %d, got: %d\r\n"), aExpected, aValue);
		TheTest(EFalse, aLine);
		}
	}
//Use these to test conditions.
#define TEST(arg) ::Check((arg), __LINE__)
#define TEST2(aValue, aExpected) ::Check(aValue, aExpected, __LINE__)

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
/**
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0502
@SYMTestCaseDesc        Tests for converting GB 2312-80 character set to Unicode
@SYMTestPriority        Medium
@SYMTestActions         Tests for simple GB 2312-80 round trips,
						Tests for varying the default Endianness
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void DoE32MainL()
	{
	RFs fileServerSession;
	CleanupClosePushL(fileServerSession);
	User::LeaveIfError(fileServerSession.Connect());
	CCnvCharacterSetConverter* characterSetConverter=CCnvCharacterSetConverter::NewLC();
	CArrayFix<CCnvCharacterSetConverter::SCharacterSet>* arrayOfCharacterSetsAvailable=CCnvCharacterSetConverter::CreateArrayOfCharacterSetsAvailableLC(fileServerSession);
	TheTest.Printf(_L("Available:\n"));
	for (TInt i=arrayOfCharacterSetsAvailable->Count()-1; i>=0; --i)
		{
		const CCnvCharacterSetConverter::SCharacterSet& charactersSet=(*arrayOfCharacterSetsAvailable)[i];
		characterSetConverter->PrepareToConvertToOrFromL(charactersSet.Identifier(), *arrayOfCharacterSetsAvailable, fileServerSession);
		TPtrC charactersSetName(charactersSet.Name());
		if (charactersSet.NameIsFileName())
			{
			charactersSetName.Set(TParsePtrC(charactersSetName).Name());
			}
		TheTest.Printf(_L("    %S\n"), &charactersSetName);
		}
	TheTest.Start(_L(" @SYMTestCaseID:SYSLIB-CHARCONV-CT-0502 Testing simple GB 2312-80 round trips "));
	characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierGb2312, *arrayOfCharacterSetsAvailable, fileServerSession);
	TBuf8<256> originalGb2312;
	TBuf16<256> originalUnicode;
	TBuf8<256> generatedGb2312;
	TBuf16<256> generatedUnicode;
	TInt state=CCnvCharacterSetConverter::KStateDefault;
	//
	TheTest.Next(_L("Empty descriptor"));
	originalUnicode=_L16("");
	TEST(characterSetConverter->ConvertFromUnicode(generatedGb2312, originalUnicode)==0);
	TEST(generatedGb2312==_L8(""));
	TEST(characterSetConverter->ConvertToUnicode(generatedUnicode, generatedGb2312, state)==0);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(generatedUnicode==originalUnicode);
	TheTest.Next(_L("A couple of sample characters"));
	originalGb2312=_L8("\xb9\xa4\xc8\xcb");
	TEST(characterSetConverter->ConvertToUnicode(generatedUnicode, originalGb2312, state)==0);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(generatedUnicode.Length()==2);
	TEST(generatedUnicode[0]==0x5de5);
	TEST(generatedUnicode[1]==0x4eba);
	TEST(characterSetConverter->ConvertFromUnicode(generatedGb2312, generatedUnicode)==0);
	TEST(generatedGb2312==originalGb2312);
	TheTest.Next(_L("Converting trunctated GB 2312-80 which ends half-way through a multi-byte character"));
	originalGb2312=_L8("\xb9\xa4\xc8");
	TEST(characterSetConverter->ConvertToUnicode(generatedUnicode, originalGb2312, state)==1);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0x5de5);
	originalGb2312=_L8("\xc8");
	TEST(characterSetConverter->ConvertToUnicode(generatedUnicode, originalGb2312, state)==CCnvCharacterSetConverter::EErrorIllFormedInput);
	TheTest.Next(_L("Testing varying the default endianness"));
	originalGb2312=_L8("\xb4\xf2");
	characterSetConverter->SetDefaultEndiannessOfForeignCharacters(CCnvCharacterSetConverter::ELittleEndian);
	TEST(characterSetConverter->ConvertToUnicode(generatedUnicode, originalGb2312, state)==0);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0x6253);
	TEST(characterSetConverter->ConvertFromUnicode(generatedGb2312, generatedUnicode)==0);
	TEST(generatedGb2312==originalGb2312);
	characterSetConverter->SetDefaultEndiannessOfForeignCharacters(CCnvCharacterSetConverter::EBigEndian);
	TEST(characterSetConverter->ConvertToUnicode(generatedUnicode, originalGb2312, state)==0);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0x6253);
	TEST(characterSetConverter->ConvertFromUnicode(generatedGb2312, generatedUnicode)==0);
	TEST(generatedGb2312==originalGb2312);
	TheTest.Next(_L("Testing a many-to-one conversion"));
	originalUnicode.SetLength(4);
	originalUnicode[0]=0x30fb;
	originalUnicode[1]=0x00b7;
	originalUnicode[2]=0x2014;
	originalUnicode[3]=0x2015;
	TEST(characterSetConverter->ConvertFromUnicode(generatedGb2312, originalUnicode)==0);
	TEST(generatedGb2312==_L8("\xa1\xa4\xa1\xa4\xa1\xaa\xa1\xaa"));
	TEST(characterSetConverter->ConvertToUnicode(generatedUnicode, generatedGb2312, state)==0);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(generatedUnicode.Length()==4);
	TEST(generatedUnicode[0]==0x00b7);
	TEST(generatedUnicode[1]==0x00b7);
	TEST(generatedUnicode[2]==0x2015);
	TEST(generatedUnicode[3]==0x2015);
	TheTest.Next(_L("Testing GB2312 being aliased to GBK"));
	TUint charSetId = characterSetConverter->ConvertStandardNameOfCharacterSetToIdentifierL(_L8("GB2312"), fileServerSession);
	TEST(charSetId==KCharacterSetIdentifierGbk);
	TEST(characterSetConverter->ConvertStandardNameOfCharacterSetToIdentifierL(_L8("csGB2312"), fileServerSession)==KCharacterSetIdentifierGbk);
	TEST(characterSetConverter->ConvertStandardNameOfCharacterSetToIdentifierL(_L8("iso-ir-58"), fileServerSession)==KCharacterSetIdentifierGbk);
	TEST(characterSetConverter->ConvertStandardNameOfCharacterSetToIdentifierL(_L8("chinese"), fileServerSession)==KCharacterSetIdentifierGbk);
	TEST(characterSetConverter->ConvertStandardNameOfCharacterSetToIdentifierL(_L8("csISO58GB231280"), fileServerSession)==KCharacterSetIdentifierGbk);
	TEST(characterSetConverter->ConvertMibEnumOfCharacterSetToIdentifierL(57, fileServerSession)==KCharacterSetIdentifierGbk);
	TEST(characterSetConverter->ConvertMibEnumOfCharacterSetToIdentifierL(2025, fileServerSession)==KCharacterSetIdentifierGbk);
	characterSetConverter->PrepareToConvertToOrFromL(charSetId, *arrayOfCharacterSetsAvailable, fileServerSession);
	originalUnicode.SetLength(3);
	originalUnicode[0]=0x9556; // this has a corresponding GB2312 character
	originalUnicode[1]=0x9555; // this has a corresponding GBK character not in GB2312...
	originalUnicode[2]=0x9394; // ... as does this
	TEST(characterSetConverter->ConvertFromUnicode(generatedGb2312, originalUnicode)==0);
	TEST(generatedGb2312.Length()==6);
	TEST(generatedGb2312==_L8("\xef\xda\xe9\x46\xe6\x67"));
	CleanupStack::PopAndDestroy(3); // arrayOfCharacterSetsAvailable and characterSetConverter and fileServerSession
	}

GLDEF_C TInt E32Main()
	{
	__UHEAP_MARK;

	TheTest.Title();

	CTrapCleanup* trapCleanup=CTrapCleanup::New();
	TEST(trapCleanup != NULL);

	TRAPD(error, DoE32MainL());
	TEST2(error, KErrNone);

	delete trapCleanup;

	TheTest.End();
	TheTest.Close();

	__UHEAP_MARKEND;
	return KErrNone;
	}

