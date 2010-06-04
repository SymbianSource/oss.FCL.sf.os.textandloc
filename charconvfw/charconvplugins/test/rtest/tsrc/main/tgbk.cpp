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

RTest TheTest(_L("TGBK"));

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


const TInt KMibValue = 113;
const TInt KBufferLength=100;
/**
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0509
@SYMTestCaseDesc        Tests for truncated conversion from Unicode to GBK
@SYMTestPriority        Medium
@SYMTestActions         Tests for truncated conversion from Unicode to Gbk and back to Unicode.
                        Tests for the generated Unicode with original Unicode
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void TestTruncatedConversionFromUnicodeToGbk(CCnvCharacterSetConverter& aCharacterSetConverter, const TDesC16& aOriginalUnicode)
	{
	TheTest.Next(_L(" @SYMTestCaseID:SYSLIB-CHARCONV-CT-0509 "));
	for (TInt i=aOriginalUnicode.Length(); i>=0; --i)
		{
		TBuf8<KBufferLength> generatedGbk;
		const TInt returnValue=aCharacterSetConverter.ConvertFromUnicode(generatedGbk, aOriginalUnicode.Left(i));
		TEST(returnValue>=0);
		TBuf8<KBufferLength> generatedsecondPartOfGbk;
		TEST(aCharacterSetConverter.ConvertFromUnicode(generatedsecondPartOfGbk, aOriginalUnicode.Mid(i-returnValue))==0);
		generatedGbk.Append(generatedsecondPartOfGbk);
		TInt state=CCnvCharacterSetConverter::KStateDefault;
		TBuf16<KBufferLength> generatedUnicode;
		TEST(aCharacterSetConverter.ConvertToUnicode(generatedUnicode, generatedGbk, state)==0);
		TEST(generatedUnicode==aOriginalUnicode);
		}
	}
/**
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0510
@SYMTestCaseDesc        Splitting and converting from Unicode to GBK test
@SYMTestPriority        Medium
@SYMTestActions         Tests for conversion after splitting from Unicode to Gbk and back to Unicode
						Tests for the generated Unicode with original Unicode
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void TestSplittingConvertingFromUnicodeToGbk(CCnvCharacterSetConverter& aCharacterSetConverter, TInt aMaximumLengthLowerLimit, TInt aMaximumLengthUpperLimit, TInt aExpectedNumberOfUnicodeCharactersNotConvertedAtSplit, TInt aExpectedLengthOfFirstPartOfGbk, const TDesC8& aExpectedGbk, const TDesC16& aOriginalUnicode)
	{
	TheTest.Next(_L(" @SYMTestCaseID:SYSLIB-CHARCONV-CT-0510 "));
	TEST(aMaximumLengthLowerLimit<=aMaximumLengthUpperLimit);
	TEST(aMaximumLengthUpperLimit<=KBufferLength);
	TUint8 gbkBuffer[KBufferLength];
	for (TInt i=aMaximumLengthLowerLimit; i<=aMaximumLengthUpperLimit; ++i)
		{
		TPtr8 generatedFirstPartOfGbk(gbkBuffer, i);
		TEST(aCharacterSetConverter.ConvertFromUnicode(generatedFirstPartOfGbk, aOriginalUnicode)==aExpectedNumberOfUnicodeCharactersNotConvertedAtSplit);
		TEST(generatedFirstPartOfGbk==aExpectedGbk.Left(aExpectedLengthOfFirstPartOfGbk));
		TBuf8<KBufferLength> generatedSecondPartOfGbk;
		TEST(aCharacterSetConverter.ConvertFromUnicode(generatedSecondPartOfGbk, aOriginalUnicode.Right(aExpectedNumberOfUnicodeCharactersNotConvertedAtSplit))==0);
		TEST(generatedSecondPartOfGbk==aExpectedGbk.Mid(aExpectedLengthOfFirstPartOfGbk));
		TInt state=CCnvCharacterSetConverter::KStateDefault;
		TBuf16<KBufferLength> generatedUnicode;
		TEST(aCharacterSetConverter.ConvertToUnicode(generatedUnicode, generatedFirstPartOfGbk, state)==0);
		TEST(state==CCnvCharacterSetConverter::KStateDefault);
		TBuf16<KBufferLength> generatedSecondPartOfUnicode;
		TEST(aCharacterSetConverter.ConvertToUnicode(generatedSecondPartOfUnicode, generatedSecondPartOfGbk, state)==0);
		TEST(state==CCnvCharacterSetConverter::KStateDefault);
		generatedUnicode.Append(generatedSecondPartOfUnicode);
		TEST(generatedUnicode==aOriginalUnicode);
		}
	}
/**
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0511
@SYMTestCaseDesc        Tests for truncated conversion from GBK to Unicode
@SYMTestPriority        Medium
@SYMTestActions         Tests for conversion after truncation from Unicode to Hz and back to Unicode
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void TestTruncatedConversionToUnicodeFromGbk(CCnvCharacterSetConverter& aCharacterSetConverter, const TDesC16& aExpectedUnicode, const TDesC8& aOriginalGbk)
	{
	TheTest.Next(_L(" @SYMTestCaseID:SYSLIB-CHARCONV-CT-0511 "));
	for (TInt i=aOriginalGbk.Length(); i>=2; --i) // 2 is the length of GBK's longest multi-byte characters
		{
		TInt state=CCnvCharacterSetConverter::KStateDefault;
		TBuf16<KBufferLength> generatedUnicode;
		const TInt returnValue=aCharacterSetConverter.ConvertToUnicode(generatedUnicode, aOriginalGbk.Left(i), state);
		TEST(returnValue>=0);
		TBuf16<KBufferLength> generatedsecondPartOfUnicode;
		TEST(aCharacterSetConverter.ConvertToUnicode(generatedsecondPartOfUnicode, aOriginalGbk.Mid(i-returnValue), state)==0);
		generatedUnicode.Append(generatedsecondPartOfUnicode);
		TEST(generatedUnicode==aExpectedUnicode);
		}
	}
/**
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0512
@SYMTestCaseDesc        Splitting and converting from GBK to Unicode test
@SYMTestPriority        Medium
@SYMTestActions         Tests for conversion after splitting from Hz to Unicode and back to Hz
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void TestSplittingConvertingToUnicodeFromGbk(CCnvCharacterSetConverter& aCharacterSetConverter, TInt aMaximumLengthLowerLimit, TInt aMaximumLengthUpperLimit, TInt aExpectedNumberOfGbkBytesNotConvertedAtSplit, TInt aExpectedLengthOfFirstPartOfUnicode, const TDesC16& aExpectedUnicode, const TDesC8& aOriginalGbk)
	{
	TheTest.Next(_L(" @SYMTestCaseID:SYSLIB-CHARCONV-CT-0512 "));
	TEST(aMaximumLengthLowerLimit<=aMaximumLengthUpperLimit);
	TEST(aMaximumLengthUpperLimit<=KBufferLength);
	TUint16 unicodeBuffer[KBufferLength];
	for (TInt i=aMaximumLengthLowerLimit; i<=aMaximumLengthUpperLimit; ++i)
		{
		TPtr16 generatedFirstPartOfUnicode(unicodeBuffer, i);
		TInt state=CCnvCharacterSetConverter::KStateDefault;
		TEST(aCharacterSetConverter.ConvertToUnicode(generatedFirstPartOfUnicode, aOriginalGbk, state)==aExpectedNumberOfGbkBytesNotConvertedAtSplit);
		TEST(generatedFirstPartOfUnicode==aExpectedUnicode.Left(aExpectedLengthOfFirstPartOfUnicode));
		TEST(state==CCnvCharacterSetConverter::KStateDefault);
		TBuf16<KBufferLength> generatedSecondPartOfUnicode;
		TEST(aCharacterSetConverter.ConvertToUnicode(generatedSecondPartOfUnicode, aOriginalGbk.Right(aExpectedNumberOfGbkBytesNotConvertedAtSplit), state)==0);
		TEST(generatedSecondPartOfUnicode==aExpectedUnicode.Mid(aExpectedLengthOfFirstPartOfUnicode));
		TEST(state==CCnvCharacterSetConverter::KStateDefault);
		TBuf8<KBufferLength> generatedGbk;
		TEST(aCharacterSetConverter.ConvertFromUnicode(generatedGbk, generatedFirstPartOfUnicode)==0);
		TBuf8<KBufferLength> generatedSecondPartOfGbk;
		TEST(aCharacterSetConverter.ConvertFromUnicode(generatedSecondPartOfGbk, generatedSecondPartOfUnicode)==0);
		generatedGbk.Append(generatedSecondPartOfGbk);
		TEST(generatedGbk==aOriginalGbk);
		}
	}


/**
Tests retreiving the MIB value from the GBK UID
Tests retreiving the GBK UID from the MIB value

@SYMTestCaseID          SYSLIB-CHARCONV-CT-0513
@SYMTestCaseDesc        Tests for conversion from MIB to UID and UID to MIB
@SYMTestPriority        Medium
@SYMTestActions         Tests CCnvCharacterSetConverter::ConvertMibEnumOfCharacterSetToIdentifierL(),
                        CCnvCharacterSetConverter::ConvertCharacterSetIdentifierToMibEnumL() functions
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void CharacterSetValueAndMIBTests(CCnvCharacterSetConverter& aCharacterSetConverter, RFs& aFileServerSession)
{
	TheTest.Next(_L(" @SYMTestCaseID:SYSLIB-CHARCONV-CT-0513 "));
	// check that the character set value of '113' is converted to the GBK UID (0x10003ecb)
	TEST(aCharacterSetConverter.ConvertMibEnumOfCharacterSetToIdentifierL(KMibValue,aFileServerSession)==KCharacterSetIdentifierGbk);
	TheTest.Printf(_L("\nMIB->Char Set UID - OK"));

	// check that the UCS2 GUID (0x10003ecb) is converted to the character set value of '113'
	TEST(aCharacterSetConverter.ConvertCharacterSetIdentifierToMibEnumL(KCharacterSetIdentifierGbk,aFileServerSession)==KMibValue);
	TheTest.Printf(_L("\nChar Set UID->MIB - OK"));
}
/**
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0514
@SYMTestCaseDesc        Conversion tests for GBK to Unicode
@SYMTestPriority        Medium
@SYMTestActions         Tests for conversion from GBK to Unicode and vice versa.
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
	TPtrC8 originalGbk;
	TBuf16<KBufferLength> originalUnicode;
	TBuf8<KBufferLength> generatedGbk;
	TBuf16<KBufferLength> generatedUnicode;
	TInt state=CCnvCharacterSetConverter::KStateDefault;

	// test that we can get MIB and Charset values
	CharacterSetValueAndMIBTests(*characterSetConverter, fileServerSession);

	characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierGbk, *arrayOfCharacterSetsAvailable, fileServerSession);

	TheTest.Start(_L(" @SYMTestCaseID:SYSLIB-CHARCONV-CT-0514 Testing characters shared with GB 2312-80 and characters only in GBK "));
	originalGbk.Set(_L8("A\xfd\x7d\xdd\xb6\xb1\xc9\xe9\x8e\xe8\x9d""E b\xd3\x59\xd2\x40\x95\xc0"));
	originalUnicode.Format(_L16("A%c%c%c%c%cE b%c%c%c"), 0x9f77, 0x837b, 0x9119, 0x95b9, 0x94e6, 0x89bb, 0x8938, 0x66b2);
	TestTruncatedConversionFromUnicodeToGbk(*characterSetConverter, originalUnicode);
	TestSplittingConvertingFromUnicodeToGbk(*characterSetConverter, 0, 0, 12, 0, originalGbk, originalUnicode);
	TestSplittingConvertingFromUnicodeToGbk(*characterSetConverter, 1, 2, 11, 1, originalGbk, originalUnicode);
	TestSplittingConvertingFromUnicodeToGbk(*characterSetConverter, 3, 4, 10, 3, originalGbk, originalUnicode);
	TestSplittingConvertingFromUnicodeToGbk(*characterSetConverter, 5, 6, 9, 5, originalGbk, originalUnicode);
	TestSplittingConvertingFromUnicodeToGbk(*characterSetConverter, 7, 8, 8, 7, originalGbk, originalUnicode);
	TestSplittingConvertingFromUnicodeToGbk(*characterSetConverter, 9, 10, 7, 9, originalGbk, originalUnicode);
	TestSplittingConvertingFromUnicodeToGbk(*characterSetConverter, 11, 11, 6, 11, originalGbk, originalUnicode);
	TestSplittingConvertingFromUnicodeToGbk(*characterSetConverter, 12, 12, 5, 12, originalGbk, originalUnicode);
	TestSplittingConvertingFromUnicodeToGbk(*characterSetConverter, 13, 13, 4, 13, originalGbk, originalUnicode);
	TestSplittingConvertingFromUnicodeToGbk(*characterSetConverter, 14, 15, 3, 14, originalGbk, originalUnicode);
	TestSplittingConvertingFromUnicodeToGbk(*characterSetConverter, 16, 17, 2, 16, originalGbk, originalUnicode);
	TestSplittingConvertingFromUnicodeToGbk(*characterSetConverter, 18, 19, 1, 18, originalGbk, originalUnicode);
	TestSplittingConvertingFromUnicodeToGbk(*characterSetConverter, 20, 40, 0, 20, originalGbk, originalUnicode);
	TestTruncatedConversionToUnicodeFromGbk(*characterSetConverter, originalUnicode, originalGbk);
	TestTruncatedConversionToUnicodeFromGbk(*characterSetConverter, originalUnicode.Mid(1, 2), originalGbk.Mid(1, 4));
	TestSplittingConvertingToUnicodeFromGbk(*characterSetConverter, 0, 0, 20, 0, originalUnicode, originalGbk);
	TestSplittingConvertingToUnicodeFromGbk(*characterSetConverter, 1, 1, 19, 1, originalUnicode, originalGbk);
	TestSplittingConvertingToUnicodeFromGbk(*characterSetConverter, 2, 2, 17, 2, originalUnicode, originalGbk);
	TestSplittingConvertingToUnicodeFromGbk(*characterSetConverter, 3, 3, 15, 3, originalUnicode, originalGbk);
	TestSplittingConvertingToUnicodeFromGbk(*characterSetConverter, 4, 4, 13, 4, originalUnicode, originalGbk);
	TestSplittingConvertingToUnicodeFromGbk(*characterSetConverter, 5, 5, 11, 5, originalUnicode, originalGbk);
	TestSplittingConvertingToUnicodeFromGbk(*characterSetConverter, 6, 6, 9, 6, originalUnicode, originalGbk);
	TestSplittingConvertingToUnicodeFromGbk(*characterSetConverter, 7, 7, 8, 7, originalUnicode, originalGbk);
	TestSplittingConvertingToUnicodeFromGbk(*characterSetConverter, 8, 8, 7, 8, originalUnicode, originalGbk);
	TestSplittingConvertingToUnicodeFromGbk(*characterSetConverter, 9, 9, 6, 9, originalUnicode, originalGbk);
	TestSplittingConvertingToUnicodeFromGbk(*characterSetConverter, 10, 10, 4, 10, originalUnicode, originalGbk);
	TestSplittingConvertingToUnicodeFromGbk(*characterSetConverter, 11, 11, 2, 11, originalUnicode, originalGbk);
	TestSplittingConvertingToUnicodeFromGbk(*characterSetConverter, 12, 30, 0, 12, originalUnicode, originalGbk);

	TheTest.Next(_L("Testing GBK characters where the first byte has the high-bit set and the second byte doesn't"));
	originalGbk.Set(_L8("\x20\x5d\xa0\x5d\xa0\xdd"));
	originalUnicode.Format(_L16(" ]%c%c"), 0x71f7, 0x72a6);
	TestTruncatedConversionFromUnicodeToGbk(*characterSetConverter, originalUnicode);
	TestSplittingConvertingFromUnicodeToGbk(*characterSetConverter, 0, 0, 4, 0, originalGbk, originalUnicode);
	TestSplittingConvertingFromUnicodeToGbk(*characterSetConverter, 1, 1, 3, 1, originalGbk, originalUnicode);
	TestSplittingConvertingFromUnicodeToGbk(*characterSetConverter, 2, 3, 2, 2, originalGbk, originalUnicode);
	TestSplittingConvertingFromUnicodeToGbk(*characterSetConverter, 4, 5, 1, 4, originalGbk, originalUnicode);
	TestSplittingConvertingFromUnicodeToGbk(*characterSetConverter, 6, 20, 0, 6, originalGbk, originalUnicode);
	TestTruncatedConversionToUnicodeFromGbk(*characterSetConverter, originalUnicode, originalGbk);
	TestSplittingConvertingToUnicodeFromGbk(*characterSetConverter, 0, 0, 6, 0, originalUnicode, originalGbk);
	TestSplittingConvertingToUnicodeFromGbk(*characterSetConverter, 1, 1, 5, 1, originalUnicode, originalGbk);
	TestSplittingConvertingToUnicodeFromGbk(*characterSetConverter, 2, 2, 4, 2, originalUnicode, originalGbk);
	TestSplittingConvertingToUnicodeFromGbk(*characterSetConverter, 3, 3, 2, 3, originalUnicode, originalGbk);
	TestSplittingConvertingToUnicodeFromGbk(*characterSetConverter, 4, 20, 0, 4, originalUnicode, originalGbk);

	TheTest.Next(_L("Testing the many-to-many mapping in GBK"));
	originalGbk.Set(_L8("\xa8\x44\xa1\xaa"));
	TEST(characterSetConverter->ConvertToUnicode(generatedUnicode, originalGbk, state)==0);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(generatedUnicode.Length()==2);
	TEST(generatedUnicode[0]==0x2015);
	TEST(generatedUnicode[1]==0x2015);
	originalUnicode.SetLength(2);
	originalUnicode[0]=0x2014;
	originalUnicode[1]=0x2015;
	TEST(characterSetConverter->ConvertFromUnicode(generatedGbk, originalUnicode)==0);
	TEST(generatedGbk==_L8("\xa1\xaa\xa1\xaa"));

	TheTest.Next(_L("Testing truncated GBK sequences"));
	originalGbk.Set(_L8("qwe\xb5"));
	TEST(characterSetConverter->ConvertToUnicode(generatedUnicode, originalGbk, state)==1);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(generatedUnicode==_L16("qwe"));
	originalGbk.Set(_L8("qwe\x80"));
	TEST(characterSetConverter->ConvertToUnicode(generatedUnicode, originalGbk, state)==1);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(generatedUnicode==_L16("qwe"));
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

