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

///////////////////////////////////////////////////////////////////////////////////////

RTest TheTest(_L("TEUCJP_PACKED_2"));

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
// this is the test plug implementation ID in rather than KCharacterSetIdentifierEucJpPacked
const TUint KCharacterSetTestEucjpPacked_2=0x01000005;

const TInt KBufferLength=100;
/**
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0535
@SYMTestCaseDesc        Tests for truncated conversion from Unicode to EucJpPacked
@SYMTestPriority        Medium
@SYMTestActions         Tests for truncated conversion from Unicode to EucJpPacked and back to Unicode
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void TestTruncatedConversionFromUnicodeToEucJpPacked(CCnvCharacterSetConverter& aCharacterSetConverter, const TDesC16& aOriginalUnicode)
	{
	TheTest.Next(_L(" @SYMTestCaseID:SYSLIB-CHARCONV-CT-0535 "));
	for (TInt i=aOriginalUnicode.Length(); i>=0; --i)
		{
		TBuf8<KBufferLength> generatedEucJpPacked;
		const TInt returnValue=aCharacterSetConverter.ConvertFromUnicode(generatedEucJpPacked, aOriginalUnicode.Left(i));
		TEST(returnValue>=0);
		TBuf8<KBufferLength> generatedsecondPartOfEucJpPacked;
		TEST(aCharacterSetConverter.ConvertFromUnicode(generatedsecondPartOfEucJpPacked, aOriginalUnicode.Mid(i-returnValue))==0);
		generatedEucJpPacked.Append(generatedsecondPartOfEucJpPacked);
		TInt state=CCnvCharacterSetConverter::KStateDefault;
		TBuf16<KBufferLength> generatedUnicode;
		TEST(aCharacterSetConverter.ConvertToUnicode(generatedUnicode, generatedEucJpPacked, state)==0);
		TEST(generatedUnicode==aOriginalUnicode);
		}
	}
/**
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0536
@SYMTestCaseDesc        Splitting and converting from Unicode to EucJpPacked test
@SYMTestPriority        Medium
@SYMTestActions         Tests for conversion after splitting, from Unicode to EucJpPacked and back to Unicode
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void TestSplittingConvertingFromUnicodeToEucJpPacked(CCnvCharacterSetConverter& aCharacterSetConverter, TInt aMaximumLengthLowerLimit, TInt aMaximumLengthUpperLimit, TInt aExpectedNumberOfUnicodeCharactersNotConvertedAtSplit, TInt aExpectedLengthOfFirstPartOfEucJpPacked, const TDesC8& aExpectedEucJpPacked, const TDesC16& aOriginalUnicode)
	{
	TheTest.Next(_L(" @SYMTestCaseID:SYSLIB-CHARCONV-CT-0536 "));
	TEST(aMaximumLengthLowerLimit<=aMaximumLengthUpperLimit);
	TEST(aMaximumLengthUpperLimit<=KBufferLength);
	TUint8 eucJpPackedBuffer[KBufferLength];
	for (TInt i=aMaximumLengthLowerLimit; i<=aMaximumLengthUpperLimit; ++i)
		{
		TPtr8 generatedFirstPartOfEucJpPacked(eucJpPackedBuffer, i);
		TEST(aCharacterSetConverter.ConvertFromUnicode(generatedFirstPartOfEucJpPacked, aOriginalUnicode)==aExpectedNumberOfUnicodeCharactersNotConvertedAtSplit);
		TEST(generatedFirstPartOfEucJpPacked==aExpectedEucJpPacked.Left(aExpectedLengthOfFirstPartOfEucJpPacked));
		TBuf8<KBufferLength> generatedSecondPartOfEucJpPacked;
		TEST(aCharacterSetConverter.ConvertFromUnicode(generatedSecondPartOfEucJpPacked, aOriginalUnicode.Right(aExpectedNumberOfUnicodeCharactersNotConvertedAtSplit))==0);
		TEST(generatedSecondPartOfEucJpPacked==aExpectedEucJpPacked.Mid(aExpectedLengthOfFirstPartOfEucJpPacked));
		TInt state=CCnvCharacterSetConverter::KStateDefault;
		TBuf16<KBufferLength> generatedUnicode;
		TEST(aCharacterSetConverter.ConvertToUnicode(generatedUnicode, generatedFirstPartOfEucJpPacked, state)==0);
		TEST(state==CCnvCharacterSetConverter::KStateDefault);
		TBuf16<KBufferLength> generatedSecondPartOfUnicode;
		TEST(aCharacterSetConverter.ConvertToUnicode(generatedSecondPartOfUnicode, generatedSecondPartOfEucJpPacked, state)==0);
		TEST(state==CCnvCharacterSetConverter::KStateDefault);
		generatedUnicode.Append(generatedSecondPartOfUnicode);
		TEST(generatedUnicode==aOriginalUnicode);
		}
	}
/**
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0537
@SYMTestCaseDesc        Tests for truncated conversion from EucJpPacked to Unicode
@SYMTestPriority        Medium
@SYMTestActions         Tests for truncated conversion from EucJpPacked to Unicode and back to EucJpPacked
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void TestTruncatedConversionToUnicodeFromEucJpPacked(CCnvCharacterSetConverter& aCharacterSetConverter, const TDesC16& aExpectedUnicode, const TDesC8& aOriginalEucJpPacked)
	{
	TheTest.Next(_L(" @SYMTestCaseID:SYSLIB-CHARCONV-CT-0537 "));
	for (TInt i=aOriginalEucJpPacked.Length(); i>=3; --i) // 3 is the length of GBK's longest multi-byte characters
		{
		TInt state=CCnvCharacterSetConverter::KStateDefault;
		TBuf16<KBufferLength> generatedUnicode;
		const TInt returnValue=aCharacterSetConverter.ConvertToUnicode(generatedUnicode, aOriginalEucJpPacked.Left(i), state);
		TEST(returnValue>=0);
		TBuf16<KBufferLength> generatedsecondPartOfUnicode;
		TEST(aCharacterSetConverter.ConvertToUnicode(generatedsecondPartOfUnicode, aOriginalEucJpPacked.Mid(i-returnValue), state)==0);
		generatedUnicode.Append(generatedsecondPartOfUnicode);
		TEST(generatedUnicode==aExpectedUnicode);
		}
	}
/**
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0538
@SYMTestCaseDesc        Splitting and converting from EucJpPacked to Unicode test
@SYMTestPriority        Medium
@SYMTestActions         Tests for conversion after splitting, from EucJpPacked to Unicode and back to EucJpPacked
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void TestSplittingConvertingToUnicodeFromEucJpPacked(CCnvCharacterSetConverter& aCharacterSetConverter, TInt aMaximumLengthLowerLimit, TInt aMaximumLengthUpperLimit, TInt aExpectedNumberOfEucJpPackedBytesNotConvertedAtSplit, TInt aExpectedLengthOfFirstPartOfUnicode, const TDesC16& aExpectedUnicode, const TDesC8& aOriginalEucJpPacked)
	{
	TheTest.Next(_L(" @SYMTestCaseID:SYSLIB-CHARCONV-CT-0538 "));
	TEST(aMaximumLengthLowerLimit<=aMaximumLengthUpperLimit);
	TEST(aMaximumLengthUpperLimit<=KBufferLength);
	TUint16 unicodeBuffer[KBufferLength];
	for (TInt i=aMaximumLengthLowerLimit; i<=aMaximumLengthUpperLimit; ++i)
		{
		TPtr16 generatedFirstPartOfUnicode(unicodeBuffer, i);
		TInt state=CCnvCharacterSetConverter::KStateDefault;
		TEST(aCharacterSetConverter.ConvertToUnicode(generatedFirstPartOfUnicode, aOriginalEucJpPacked, state)==aExpectedNumberOfEucJpPackedBytesNotConvertedAtSplit);
		TEST(generatedFirstPartOfUnicode==aExpectedUnicode.Left(aExpectedLengthOfFirstPartOfUnicode));
		TEST(state==CCnvCharacterSetConverter::KStateDefault);
		TBuf16<KBufferLength> generatedSecondPartOfUnicode;
		TEST(aCharacterSetConverter.ConvertToUnicode(generatedSecondPartOfUnicode, aOriginalEucJpPacked.Right(aExpectedNumberOfEucJpPackedBytesNotConvertedAtSplit), state)==0);
		TEST(generatedSecondPartOfUnicode==aExpectedUnicode.Mid(aExpectedLengthOfFirstPartOfUnicode));
		TEST(state==CCnvCharacterSetConverter::KStateDefault);
		TBuf8<KBufferLength> generatedEucJpPacked;
		TEST(aCharacterSetConverter.ConvertFromUnicode(generatedEucJpPacked, generatedFirstPartOfUnicode)==0);
		TBuf8<KBufferLength> generatedSecondPartOfEucJpPacked;
		TEST(aCharacterSetConverter.ConvertFromUnicode(generatedSecondPartOfEucJpPacked, generatedSecondPartOfUnicode)==0);
		generatedEucJpPacked.Append(generatedSecondPartOfEucJpPacked);
		TEST(generatedEucJpPacked==aOriginalEucJpPacked);
		}
	}
/**
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0539
@SYMTestCaseDesc        Conversion of bad EucJpPacked format to Unicode test
@SYMTestPriority        Medium
@SYMTestActions         Tests to convert Ill formed EucJpPacked input to Unicode.
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void TestIsIllFormedEucJpPacked(CCnvCharacterSetConverter& aCharacterSetConverter, const TDesC8& aEucJpPacked)
	{
	TheTest.Next(_L(" @SYMTestCaseID:SYSLIB-CHARCONV-CT-0539 "));
	TBuf16<50> generatedUnicode;
	TInt state=CCnvCharacterSetConverter::KStateDefault;
	TPtrC8 remainderOfEucJpPacked(aEucJpPacked);
	TInt lastReturnValue=KMaxTInt;
	FOREVER
		{
		const TInt returnValue=aCharacterSetConverter.ConvertToUnicode(generatedUnicode, remainderOfEucJpPacked, state);
		if (returnValue==CCnvCharacterSetConverter::EErrorIllFormedInput)
			{
			break;
			}
		TEST(returnValue>0);
		TEST(returnValue<lastReturnValue);
		lastReturnValue=returnValue;
		remainderOfEucJpPacked.Set(remainderOfEucJpPacked.Right(returnValue));
		}
	}
/**
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0540
@SYMTestCaseDesc        JIS to Unicode and Unicode to EucJpPacked conversion tests
@SYMTestPriority        Medium
@SYMTestActions         Calls up all conversion test functions from EucJpPacked to Unicode
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
	TInt i;
	for (i=arrayOfCharacterSetsAvailable->Count()-1; i>=0; --i)
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
	TheTest.Start(_L(" @SYMTestCaseID:SYSLIB-CHARCONV-CT-0540 Testing EUC-JP (packed) conversions "));
	characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetTestEucjpPacked_2, *arrayOfCharacterSetsAvailable, fileServerSession);
	//
	TheTest.Next(_L("Empty descriptor"));
	TestSplittingConvertingFromUnicodeToEucJpPacked(*characterSetConverter, 0, 10, 0, 0, KNullDesC8, KNullDesC16);
	TestSplittingConvertingToUnicodeFromEucJpPacked(*characterSetConverter, 0, 10, 0, 0, KNullDesC16, KNullDesC8);
	TheTest.Next(_L("Testing converting to EUC-JP (packed)"));
	TBuf16<50> originalUnicode;
	originalUnicode.Format(_L16("Some %c%c%c%c%c%c"), 0xff9a, 0xff70, 0x6f22, 0x5b57, 0x5379, 0x5dce);
	const TPtrC8 expectedEucJpPacked(_S8("Some \x8e\xda\x8e\xb0\xb4\xc1\xbb\xfa\x8f\xb4\xc1\x8f\xbb\xfa"));
	TestTruncatedConversionFromUnicodeToEucJpPacked(*characterSetConverter, originalUnicode);
	TestSplittingConvertingFromUnicodeToEucJpPacked(*characterSetConverter, 0, 0, 11, 0, expectedEucJpPacked, originalUnicode);
	TestSplittingConvertingFromUnicodeToEucJpPacked(*characterSetConverter, 1, 1, 10, 1, expectedEucJpPacked, originalUnicode);
	TestSplittingConvertingFromUnicodeToEucJpPacked(*characterSetConverter, 2, 2, 9, 2, expectedEucJpPacked, originalUnicode);
	TestSplittingConvertingFromUnicodeToEucJpPacked(*characterSetConverter, 3, 3, 8, 3, expectedEucJpPacked, originalUnicode);
	TestSplittingConvertingFromUnicodeToEucJpPacked(*characterSetConverter, 4, 4, 7, 4, expectedEucJpPacked, originalUnicode);
	TestSplittingConvertingFromUnicodeToEucJpPacked(*characterSetConverter, 5, 6, 6, 5, expectedEucJpPacked, originalUnicode);
	TestSplittingConvertingFromUnicodeToEucJpPacked(*characterSetConverter, 7, 8, 5, 7, expectedEucJpPacked, originalUnicode);
	TestSplittingConvertingFromUnicodeToEucJpPacked(*characterSetConverter, 9, 10, 4, 9, expectedEucJpPacked, originalUnicode);
	TestSplittingConvertingFromUnicodeToEucJpPacked(*characterSetConverter, 11, 12, 3, 11, expectedEucJpPacked, originalUnicode);
	TestSplittingConvertingFromUnicodeToEucJpPacked(*characterSetConverter, 13, 15, 2, 13, expectedEucJpPacked, originalUnicode);
	TestSplittingConvertingFromUnicodeToEucJpPacked(*characterSetConverter, 16, 18, 1, 16, expectedEucJpPacked, originalUnicode);
	TestSplittingConvertingFromUnicodeToEucJpPacked(*characterSetConverter, 19, 30, 0, 19, expectedEucJpPacked, originalUnicode);
	TheTest.Next(_L("Testing converting to Unicode"));
	const TPtrC8 originalEucJpPacked(_S8("pool\xbe\xae\xc3\xd3\x8e\xcc\x8e\xdf\x8e\xd9\x8f\xc0\xcd\x8f\xc8\xc5pool\x8e\xcc\x8e\xdf\x8e\xd9\xbe\xae\xc3\xd3\x8f\xc0\xcd\x8f\xc8\xc5\xbe\xae\xc3\xd3pool\x8f\xc0\xcd\x8f\xc8\xc5\x8e\xcc\x8e\xdf\x8e\xd9pool"));
	TBuf16<50> expectedUnicode;
	expectedUnicode.Format(_L16("pool%c%c%c%c%c%c%cpool%c%c%c%c%c%c%c%c%cpool%c%c%c%c%cpool"), 0x5c0f, 0x6c60, 0xff8c, 0xff9f, 0xff99, 0x641e, 0x6f0d, 0xff8c, 0xff9f, 0xff99, 0x5c0f, 0x6c60, 0x641e, 0x6f0d, 0x5c0f, 0x6c60, 0x641e, 0x6f0d, 0xff8c, 0xff9f, 0xff99);
	TestTruncatedConversionToUnicodeFromEucJpPacked(*characterSetConverter, expectedUnicode, originalEucJpPacked);
	TestTruncatedConversionToUnicodeFromEucJpPacked(*characterSetConverter, expectedUnicode.Mid(4, 2), originalEucJpPacked.Mid(4, 4));
	TestTruncatedConversionToUnicodeFromEucJpPacked(*characterSetConverter, expectedUnicode.Mid(6, 3), originalEucJpPacked.Mid(8, 6));
	TestTruncatedConversionToUnicodeFromEucJpPacked(*characterSetConverter, expectedUnicode.Mid(9, 2), originalEucJpPacked.Mid(14, 6));
	static const TInt numberOfCharactersInEachHomogeneousRun[13]={4, 2, 3, 2, 4, 3, 2, 2, 2, 4, 2, 3, 4};
	static const TInt numberOfBytesPerCharacterInEachHomogeneousRun[13]={1, 2, 2, 3, 1, 2, 2, 3, 2, 1, 3, 2, 1};
	TInt e=64;
	TInt u=0;
	for (i=0; i<13; ++i)
		{
		TInt j;
		for (j=0; j<numberOfCharactersInEachHomogeneousRun[i]; ++j, ++u, e-=numberOfBytesPerCharacterInEachHomogeneousRun[i])
			{
			TestSplittingConvertingToUnicodeFromEucJpPacked(*characterSetConverter, u, u, e, u, expectedUnicode, originalEucJpPacked);
			}
		}
	TEST(e==0);
	TEST(u==37);
	TestSplittingConvertingToUnicodeFromEucJpPacked(*characterSetConverter, u, u+10, e, u, expectedUnicode, originalEucJpPacked);
	TheTest.Next(_L("Testing ill-formed EUC-JP (packed)"));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("\xa1"));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("\xa1\xb2\xc3"));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("\xa1\xb2\x8e"));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("\xa1\xb2\x8f"));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("\xa1\xb2\x8f\xaa"));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("\x8e\xd4\x8e"));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("\x8e\xd4\x8f"));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("\x8e\xd4\x8f\xbb"));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("\x8f\xe5\x8e"));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("\x8f\xe5\x8f"));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("\x8f\xe5\x8f\xcc"));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("xyz\x8e\xd4\x8e"));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("xyz\x8e\xd4\x8f"));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("xyz\x8e\xd4\x8f\xdd"));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("xyz\x8f\xe5\x8e"));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("xyz\x8f\xe5\x8f"));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("xyz\x8f\xe5\x8f\xee"));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("\x8e "));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("\x8f "));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("\x8f\xf1 "));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("\x8e\x41"));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("\x8f\x41"));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("\x8f\xe2\x41"));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("amb\x8e "));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("amb\x8f "));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("amb\x8f\xf1 "));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("amb\x8e\x41"));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("amb\x8f\x41"));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("amb\x8f\xe2\x41"));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("\xa1 "));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("\xa1\x61"));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("eb\xa1 "));
	TestIsIllFormedEucJpPacked(*characterSetConverter, _L8("eb\xa1\x61"));

    const TPtrC8 originalEucJpPackedYen(_S8("pool\x5c"));
    TBuf16<10> expectedUnicodeBackSlash;
    expectedUnicodeBackSlash.Format(_L16("pool%c"), 0x005c);
    TInt state=CCnvCharacterSetConverter::KStateDefault;
    TBuf16<KBufferLength> generatedUnicodeBackSlash;
    TEST(characterSetConverter->ConvertToUnicode(generatedUnicodeBackSlash, originalEucJpPackedYen, state) == 0);
    TEST(generatedUnicodeBackSlash==expectedUnicodeBackSlash);
	
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

