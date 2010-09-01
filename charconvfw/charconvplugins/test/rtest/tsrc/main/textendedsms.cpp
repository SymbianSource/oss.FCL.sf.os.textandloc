/*
* Copyright (c) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#ifdef __WINS__
_LIT(KInputUnicodeFilename, "c:\\test\\data\\extendedsms_uni_input.dat");
_LIT(KInputForeignFilename, "c:\\test\\data\\extendedsms_for_input.dat");
_LIT(KExpectUnicodeFilename, "c:\\test\\data\\extendedsms_uni_expect.dat");
_LIT(KExpectForeignFilename, "c:\\test\\data\\extendedsms_for_expect.dat");
#else
_LIT(KInputUnicodeFilename, "z:\\test\\data\\extendedsms_uni_input.dat");
_LIT(KInputForeignFilename, "z:\\test\\data\\extendedsms_for_input.dat");
_LIT(KExpectUnicodeFilename, "z:\\test\\data\\extendedsms_uni_expect.dat");
_LIT(KExpectForeignFilename, "z:\\test\\data\\extendedsms_for_expect.dat");
#endif

GLDEF_C RTest TheTest(_L("TExtendedSMS"));
GLDEF_C CCnvCharacterSetConverter* characterSetConverter;
GLDEF_C RFs fileServerSession;
GLDEF_C TBuf8<1254> temp;
GLDEF_C TBuf16<627> originalUnicode;
GLDEF_C TBuf8<627> generatedForeign;
GLDEF_C TBuf16<627> generatedUnicode;
	
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

//Local functions

//read test data from file
void ReadDescL(TDes8& aDes, const TDesC& aFilename, RFs& aFs)
	{
	RFile file;
	TInt err = file.Open(aFs, aFilename, EFileRead);
	TEST2(err, KErrNone);
	CleanupClosePushL(file);	
	err = file.Read(aDes);
	TEST2(err, KErrNone);
	CleanupStack::PopAndDestroy(&file);
	}

//translate from unicode big endian TDesC8 to TDes16
void Unicode_Big(TDesC8& aSource, TDes16& aTarget)
	{
	TInt length = aSource.Length();
	TInt i = 0;
	for(i=0;i<length-1;i++)
		{
		TInt32 temp = *(aSource.Ptr()+(i))*16*16 + *(aSource.Ptr()+i+1);
		aTarget.Append(temp);
		i++;
		}	
	}

/**
@SYMTestCaseID				SYSLIB-CHARCONV-UT-4003
@SYMTestCaseDesc			Testcase to test new converter name can be listed
@SYMTestPriority			High
@SYMTestActions				Test for CreateArrayOfCharacterSetsAvailableLC() 
@SYMTestExpectedResults		The test passed, if Available character sets are listed in epocwind.out
@SYMPREQ					PREQ2090
@SYMREQ						REQ10364
*/
void ListAlltheConvertersL()
	{
	CArrayFix<CCnvCharacterSetConverter::SCharacterSet>* arrayOfCharacterSetsAvailable=\
		CCnvCharacterSetConverter::CreateArrayOfCharacterSetsAvailableLC(fileServerSession);
	TheTest.Start(_L(" @SYMTestCaseID:SYSLIB-CHARCONV-UT-4003 Available Converters\n "));
	for (TInt i=arrayOfCharacterSetsAvailable->Count()-1; i>=0; --i)
		{
		const CCnvCharacterSetConverter::SCharacterSet& charactersSet=(*arrayOfCharacterSetsAvailable)[i];
		TPtrC charactersSetName(charactersSet.Name());
		if (charactersSet.NameIsFileName())
			{
			charactersSetName.Set(TParsePtrC(charactersSetName).Name());
			}
		TheTest.Printf(_L("    %S\n"), &charactersSetName);
		}	
	CleanupStack::PopAndDestroy(arrayOfCharacterSetsAvailable);
	}

/**
@SYMTestCaseID				SYSLIB-CHARCONV-UT-4004
@SYMTestCaseDesc			Testcase to test new converter name can be prepared for converting
@SYMTestPriority			High
@SYMTestActions				Test for PrepareToConvertToOrFromL()
@SYMTestExpectedResults		The test passed, If EAvailable is returned
@SYMPREQ					PREQ2090
@SYMREQ						REQ10364
*/
void PrepareNewConverterL()
	{
	TheTest.Next(_L(" @SYMTestCaseID:SYSLIB-CHARCONV-UT-4004 Preparing the new converter "));
	CCnvCharacterSetConverter::TAvailability avaible = 	characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierExtendedSms7Bit, fileServerSession);
	TEST( CCnvCharacterSetConverter::EAvailable == avaible );
	}

/**
@SYMTestCaseID				SYSLIB-CHARCONV-UT-4005
@SYMTestCaseDesc			Convert Unicode code to foreign character set
@SYMTestPriority			High
@SYMTestActions				Test for ConvertFromUnicode()
@SYMTestExpectedResults		Test is passed if the generated cod and Expected code is same
@SYMPREQ					PREQ2090
@SYMREQ						REQ10364					
*/
void ConvertFromUnicodeToForeignL()
	{
	TheTest.Next(_L(" @SYMTestCaseID:SYSLIB-CHARCONV-UT-4005 Encoding from Unicode to Foreign "));
	ReadDescL(temp, KInputUnicodeFilename, fileServerSession);
	Unicode_Big(temp, originalUnicode); 
	TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, originalUnicode) == 0);
	ReadDescL(temp, KExpectForeignFilename, fileServerSession);
	TEST(generatedForeign == temp);
	}

/**
@SYMTestCaseID				SYSLIB-CHARCONV-UT-4006
@SYMTestCaseDesc			Convert foreign character set to Unicode code 
@SYMTestPriority			High
@SYMTestActions				Test for ConvertToUnicode() with legal foreign characters, 0x00 - 0x7F
@SYMTestExpectedResults		Test is passed if contents of generatedUnicode buffer with OriginalUnicode buffer are same.
@SYMPREQ					PREQ2090
@SYMREQ						REQ10364
*/
void ConvertFromForeignToUnicodeL()
	{
	TheTest.Next(_L(" @SYMTestCaseID:SYSLIB-CHARCONV-UT-4006 Encoding from Foreign to Unicode "));	
	ReadDescL(generatedForeign, KInputForeignFilename, fileServerSession);
	TInt state=CCnvCharacterSetConverter::KStateDefault;
	TEST( 0 == characterSetConverter->ConvertToUnicode(generatedUnicode, generatedForeign, state));
	ReadDescL(temp, KExpectUnicodeFilename, fileServerSession);
	originalUnicode.Zero();
	Unicode_Big(temp, originalUnicode); 
	TEST(generatedUnicode == originalUnicode);
	}	

/**
@SYMTestCaseID				SYSLIB-CHARCONV-UT-4007
@SYMTestCaseDesc			Convert out of range characters from foreign character set to Unicode 
@SYMTestPriority			High
@SYMTestActions				Test for ConvertToUnicode() for some out of range foreign characters 0x80 - 0xFF
@SYMTestExpectedResults		The test is passed if generated code is same as expected code
@SYMPREQ					PREQ2090
@SYMREQ						REQ10364
*/
void ConvertOutOfRangeForeignCharacters()
	{
	//test foreign chararcter point which is not in the scope, e.g. 0x80 in GSM03.38, which should always mapped to 0xFFFD
	TheTest.Next(_L(" @SYMTestCaseID:SYSLIB-CHARCONV-UT-4007 Testing Characters not in the Scope "));	
	generatedForeign.SetLength(1);
	generatedForeign[0] = 0x81;
	TInt state=CCnvCharacterSetConverter::KStateDefault;
	_LIT16(KExpected2, "\xfffd"); 	//the expected foreign
	TEST( 0 == characterSetConverter->ConvertToUnicode(generatedUnicode, generatedForeign, state));
	TEST( generatedUnicode == KExpected2 );
	}

/**
@SYMTestCaseID				SYSLIB-CHARCONV-UT-4008
@SYMTestCaseDesc			Convert illegal character from foreign character set to unicode 
@SYMTestPriority			High
@SYMTestActions				Test for ConvertToUnicode() with illegal foreign characters 0x1B
@SYMTestExpectedResults		Test is passed if KErrCorrupt is returned
@SYMPREQ					PREQ2090
@SYMREQ						REQ10364
*/
void ConvertIllegalForeignCharacter()
	{
	//test 0x1b
	TheTest.Next(_L(" @SYMTestCaseID:SYSLIB-CHARCONV-UT-4008 Testing EErrorIllFormedInput "));	
	generatedForeign.SetLength(1);
	generatedForeign[0] = 0x1b; 		//the escape character
	TInt state=CCnvCharacterSetConverter::KStateDefault;	
	TEST( KErrCorrupt == characterSetConverter->ConvertToUnicode(generatedUnicode, generatedForeign, state));
	}

LOCAL_C void DoE32MainL()
	{
	CleanupClosePushL(fileServerSession);
	User::LeaveIfError(fileServerSession.Connect());
	characterSetConverter=CCnvCharacterSetConverter::NewLC();
	
	ListAlltheConvertersL();
	PrepareNewConverterL();
	ConvertFromUnicodeToForeignL();
	ConvertFromForeignToUnicodeL();
	ConvertOutOfRangeForeignCharacters();
	ConvertIllegalForeignCharacter();

	CleanupStack::PopAndDestroy(2);
	}

//  Global Functions

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
