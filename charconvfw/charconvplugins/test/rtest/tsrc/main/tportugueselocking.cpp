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

const TUint KCharacterSetIdentifier=KCharacterSetIdentifierPortugueseLockingSms7Bit;

#ifdef __WINS__
_LIT(KInputUnicodeFilename, "c:\\test\\data\\portuguese_locking_gsm7ext_uni_input.dat");
_LIT(KInputForeignFilename, "c:\\test\\data\\portuguese_locking_gsm7ext_for_input.dat");
_LIT(KExpectUnicodeFilename, "c:\\test\\data\\portuguese_locking_gsm7ext_uni_expect.dat");
_LIT(KExpectForeignFilename, "c:\\test\\data\\portuguese_locking_gsm7ext_for_expect.dat");
#else
_LIT(KInputUnicodeFilename, "z:\\test\\data\\portuguese_locking_gsm7ext_uni_input.dat");
_LIT(KInputForeignFilename, "z:\\test\\data\\portuguese_locking_gsm7ext_for_input.dat");
_LIT(KExpectUnicodeFilename, "z:\\test\\data\\portuguese_locking_gsm7ext_uni_expect.dat");
_LIT(KExpectForeignFilename, "z:\\test\\data\\portuguese_locking_gsm7ext_for_expect.dat");
#endif

///////////////////////////////////////////////////////////////////////////////////////
RTest TheTest(_L("TPortugueseLockingGsm7Ext"));
CCnvCharacterSetConverter* characterSetConverter;
RFs fileServerSession;
TBuf8<970> temp;
TBuf16<485> originalUnicode;
TBuf8<485> generatedForeign;
TBuf16<485> generatedUnicode;
	
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


static void ReadDescL(TDes8& aDes, const TDesC& aFilename, RFs& aFs)
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
static void Unicode_Big(TDesC8& aSource, TDes16& aTarget)
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
@SYMTestCaseID				TI18N-CHARCONV-UT-4033
@SYMTestCaseDesc			Testcase to test new converter name can be listed
@SYMTestPriority			High
@SYMTestActions				Test for CreateArrayOfCharacterSetsAvailableLC() 
@SYMTestExpectedResults		The test passed, if Available character sets are listed in epocwind.out
@SYMPREQ					PREQ 2592
@SYMREQ						REQ 12583
*/
void ListAlltheConvertersL()
	{
	CArrayFix<CCnvCharacterSetConverter::SCharacterSet>* arrayOfCharacterSetsAvailable=\
		CCnvCharacterSetConverter::CreateArrayOfCharacterSetsAvailableLC(fileServerSession);
	TheTest.Start(_L(" @SYMTestCaseID:TI18N-CHARCONV-UT-4033 Available:\n "));
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
@SYMTestCaseID				TI18N-CHARCONV-UT-4034
@SYMTestCaseDesc			Testcase to test new converter can be prepared
@SYMTestPriority			High
@SYMTestActions				Test for PrepareToConvertToOrFromL()
@SYMTestExpectedResults		The test passed, If EAvailable is returned
@SYMPREQ					PREQ 2592
@SYMREQ						REQ 12583
*/
void PrepareNewConverterL()
	{
	TheTest.Next(_L(" @SYMTestCaseID:TI18N-CHARCONV-UT-4034 Testing new converter can be prepared "));
	CCnvCharacterSetConverter::TAvailability avaible = 	characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifier, fileServerSession);
	TEST( CCnvCharacterSetConverter::EAvailable == avaible );
	}

/**
@SYMTestCaseID				TI18N-CHARCONV-UT-4035
@SYMTestCaseDesc			Convert Unicode code to foreign character set
@SYMTestPriority			High
@SYMTestActions				Test for ConvertFromUnicode()
@SYMTestExpectedResults		Test must not fail
@SYMPREQ					PREQ 2592
@SYMREQ						REQ 12583
*/
LOCAL_C void ConvertFromUnicodeToForeignL()
	{
	TheTest.Next(_L(" @SYMTestCaseID:TI18N-CHARCONV-UT-4035 Testing encoding from Unicode to Foreign "));
	ReadDescL(temp, KInputUnicodeFilename, fileServerSession);
	Unicode_Big(temp, originalUnicode); 
	TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, originalUnicode) == 0);
	ReadDescL(temp, KExpectForeignFilename, fileServerSession);
	TEST(generatedForeign == temp);
	}

/**
@SYMTestCaseID				TI18N-CHARCONV-UT-4036
@SYMTestCaseDesc			Convert foreign character set to Unicode code 
@SYMTestPriority			High
@SYMTestActions				Test for ConvertToUnicode() with legal foreign characters, 0x00 - 0x7F
@SYMTestExpectedResults		Test must not fail
@SYMPREQ					PREQ 2592
@SYMREQ						REQ 12583
*/
LOCAL_C void ConvertFromForeignToUnicodeL()
	{
	TheTest.Next(_L(" @SYMTestCaseID:TI18N-CHARCONV-UT-4036 Testing encoding from Foreign to Unicode "));
	ReadDescL(generatedForeign, KInputForeignFilename, fileServerSession);
	TInt state=CCnvCharacterSetConverter::KStateDefault;
	TEST( 0 == characterSetConverter->ConvertToUnicode(generatedUnicode, generatedForeign, state));
	ReadDescL(temp, KExpectUnicodeFilename, fileServerSession);
	originalUnicode.Zero();
	Unicode_Big(temp, originalUnicode); 
	TEST(generatedUnicode == originalUnicode);
	}	
	
/**
@SYMTestCaseID				TI18N-CHARCONV-UT-4037
@SYMTestCaseDesc			Convert illegal character from foreign character set to unicode 
@SYMTestPriority			High
@SYMTestActions				Test for ConvertToUnicode() with illegal foreign characters 0x1B
@SYMTestExpectedResults		Test must not fail
@SYMPREQ					PREQ 2592
@SYMREQ						REQ 12583
*/
LOCAL_C void ConvertIllegalForeignCharacter()
	{
	//test 0x1b
	TheTest.Next(_L(" @SYMTestCaseID:TI18N-CHARCONV-UT-4037 Testing EErrorIllFormedInput "));
	generatedForeign.SetLength(1);
	generatedForeign[0] = 0x1b; 		//the escape character
	TInt state=CCnvCharacterSetConverter::KStateDefault;	
	TEST( -20 == characterSetConverter->ConvertToUnicode(generatedUnicode, generatedForeign, state));
	}

/**
@SYMTestCaseID				TI18N-CHARCONV-UT-4038
@SYMTestCaseDesc			Convert out of range characters from foreign character set to Unicode 
@SYMTestPriority			High
@SYMTestActions				Test for ConvertToUnicode() for some out of range foreign characters 0x80 - 0xFF
@SYMTestExpectedResults		Test must not fail
@SYMPREQ					PREQ 2592
@SYMREQ						REQ 12583
*/
LOCAL_C void ConvertOutOfRangeForeignCharacters()
	{
	//test foreign chararcter point which is not in the scope, e.g. 0x80 in GSM03.38, which should always mapped to 0xFFFD
	TheTest.Next(_L(" @SYMTestCaseID:TI18N-CHARCONV-UT-4038 Testing Characters not in the Scope "));	
	generatedForeign.SetLength(1);
	generatedForeign[0] = 0x80;
	TInt state=CCnvCharacterSetConverter::KStateDefault;
	_LIT16(KExpected2, "\xfffd"); 	//the expected foreign
	TEST( 0 == characterSetConverter->ConvertToUnicode(generatedUnicode, generatedForeign, state));
	TEST( generatedUnicode == KExpected2 );
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
	ConvertIllegalForeignCharacter();
	ConvertOutOfRangeForeignCharacters();
	
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
