/*
* Copyright (c) 2000-2005 Nokia Corporation and/or its subsidiary(-ies). 
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

RTest TheTest(_L("TReplacement"));
	
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
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0546
@SYMTestCaseDesc        Tests for the conversion of uncovertible Unicode characters 
@SYMTestPriority        Medium
@SYMTestActions         Tests for the replacement of uncovertible Unicode characters
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
	characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierGb2312, *arrayOfCharacterSetsAvailable, fileServerSession);
	TheTest.Start(_L("Testing various values for iReplacementForUnconvertibleUnicodeCharacters"));
	//
	TheTest.Next(_L("Testing iReplacementForUnconvertibleUnicodeCharacters being long"));
	{
	TBuf16<50> originalUnicode;
	originalUnicode.Format(_L16("Here is a Georgian character - %c"), 0x10da);
	characterSetConverter->SetReplacementForUnconvertibleUnicodeCharactersL(_L8("[something quite long]"));
	const TInt KLengthOfForeignBuffer=100;
	TUint8 foreignBuffer[KLengthOfForeignBuffer];
	for (TInt i=31; ; ++i)
		{
		TEST(i<=KLengthOfForeignBuffer);
		TPtr8 generatedForeign(foreignBuffer, i);
		TInt numberOfUnconvertibleCharacters;
		TInt indexOfFirstUnconvertibleCharacter;
		const TInt returnValue=characterSetConverter->ConvertFromUnicode(generatedForeign, originalUnicode, numberOfUnconvertibleCharacters, indexOfFirstUnconvertibleCharacter);
		if (i==53)
			{
			TEST(returnValue==0);
			TEST(generatedForeign==_L8("Here is a Georgian character - [something quite long]"));
			TEST(numberOfUnconvertibleCharacters==1);
			TEST(indexOfFirstUnconvertibleCharacter==31);
			break;
			}
		TEST(returnValue==1);
		TEST(generatedForeign==_L8("Here is a Georgian character - "));
		TEST(numberOfUnconvertibleCharacters==0);
		TEST(indexOfFirstUnconvertibleCharacter==-1); // not something that the API guarantees (it's undefined if numberOfUnconvertibleCharacters==0), but we'll check it any
		}
	}
	TheTest.Next(_L("Testing lots of unconvertible Unicode characters"));
	{
	characterSetConverter->SetReplacementForUnconvertibleUnicodeCharactersL(_L8("?Q"));
	TInt numberOfUnconvertibleCharacters;
	TInt indexOfFirstUnconvertibleCharacter;
	TInt i;
	TPtr16 originalUnicode(HBufC16::NewMaxLC(10+(sizeof(CCnvCharacterSetConverter::TArrayOfAscendingIndices)/sizeof(TUint16)))->Des());
	TPtr8 generatedForeign(HBufC8::NewLC(originalUnicode.Length()*sizeof(TUint16))->Des());
	originalUnicode.Fill(0x7535);
	TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, originalUnicode, numberOfUnconvertibleCharacters, indexOfFirstUnconvertibleCharacter)==0);
	TEST(generatedForeign.Length()>0);
	TEST(generatedForeign.Length()==originalUnicode.Length()*STATIC_CAST(TInt, sizeof(TUint16)));
	TEST(numberOfUnconvertibleCharacters==0);
	for (i=generatedForeign.Length()-1; i>=0; i-=2)
		{
		TEST(generatedForeign[i-1]==0xb5);
		TEST(generatedForeign[i]==0xe7);
		}
	originalUnicode.Fill(0x0f0a); // a Tibetan character, not in GB 2312-80
	const TInt returnValue=characterSetConverter->ConvertFromUnicode(generatedForeign, originalUnicode, numberOfUnconvertibleCharacters, indexOfFirstUnconvertibleCharacter);
	TEST(returnValue>0);
	TEST(generatedForeign.Length()>0);
	TEST(generatedForeign.Length()==(originalUnicode.Length()-returnValue)*STATIC_CAST(TInt, sizeof(TUint16)));
	TEST(numberOfUnconvertibleCharacters==generatedForeign.Length()/2);
	TEST(indexOfFirstUnconvertibleCharacter==0);
	for (i=generatedForeign.Length()-1; i>=0; i-=2)
		{
		TEST(generatedForeign[i-1]=='?');
		TEST(generatedForeign[i]=='Q');
		}
	CleanupStack::PopAndDestroy(2); // generatedForeign and originalUnicode
	}
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

