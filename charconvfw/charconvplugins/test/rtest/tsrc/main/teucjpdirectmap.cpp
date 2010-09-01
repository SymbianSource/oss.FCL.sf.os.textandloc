/*
* Copyright (c) 2000-2009 Nokia Corporation and/or its subsidiary(-ies).
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

RTest TheTest(_L("TEUCJPDIRECTMAP"));

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


const TInt KBufferLength=100;

LOCAL_C void TestTruncatedConversionFromUnicodeToEucJpDirectmap(CCnvCharacterSetConverter& aCharacterSetConverter, const TDesC16& aOriginalUnicode)
	{
	for (TInt i=aOriginalUnicode.Length(); i>=0; --i)
		{
		TBuf8<KBufferLength> generatedEucJpDirectmap;
		const TInt returnValue=aCharacterSetConverter.ConvertFromUnicode(generatedEucJpDirectmap, aOriginalUnicode.Left(i));
		TEST(returnValue>=0);
		TBuf8<KBufferLength> generatedsecondPartOfEucJpDirectmap;
		TEST(aCharacterSetConverter.ConvertFromUnicode(generatedsecondPartOfEucJpDirectmap, aOriginalUnicode.Mid(i-returnValue))==0);
		generatedEucJpDirectmap.Append(generatedsecondPartOfEucJpDirectmap);
		TInt state=CCnvCharacterSetConverter::KStateDefault;
		TBuf16<KBufferLength> generatedUnicode;
		TEST(aCharacterSetConverter.ConvertToUnicode(generatedUnicode, generatedEucJpDirectmap, state)==0);
		TEST(generatedUnicode==aOriginalUnicode);
		}
	}

LOCAL_C void TestSplittingConvertingFromUnicodeToEucJpDirectmap(CCnvCharacterSetConverter& aCharacterSetConverter, TInt aMaximumLengthLowerLimit, TInt aMaximumLengthUpperLimit, TInt aExpectedNumberOfUnicodeCharactersNotConvertedAtSplit, TInt aExpectedLengthOfFirstPartOfEucJpDirectmap, const TDesC8& aExpectedEucJpDirectmap, const TDesC16& aOriginalUnicode)
	{
	TEST(aMaximumLengthLowerLimit<=aMaximumLengthUpperLimit);
	TEST(aMaximumLengthUpperLimit<=KBufferLength);
	TUint8 eucJpDirectmapBuffer[KBufferLength];
	for (TInt i=aMaximumLengthLowerLimit; i<=aMaximumLengthUpperLimit; ++i)
		{
		TPtr8 generatedFirstPartOfEucJpDirectmap(eucJpDirectmapBuffer, i);
		TEST(aCharacterSetConverter.ConvertFromUnicode(generatedFirstPartOfEucJpDirectmap, aOriginalUnicode)==aExpectedNumberOfUnicodeCharactersNotConvertedAtSplit);
		TEST(generatedFirstPartOfEucJpDirectmap==aExpectedEucJpDirectmap.Left(aExpectedLengthOfFirstPartOfEucJpDirectmap));
		TBuf8<KBufferLength> generatedSecondPartOfEucJpDirectmap;
		TEST(aCharacterSetConverter.ConvertFromUnicode(generatedSecondPartOfEucJpDirectmap, aOriginalUnicode.Right(aExpectedNumberOfUnicodeCharactersNotConvertedAtSplit))==0);
		TEST(generatedSecondPartOfEucJpDirectmap==aExpectedEucJpDirectmap.Mid(aExpectedLengthOfFirstPartOfEucJpDirectmap));
		TInt state=CCnvCharacterSetConverter::KStateDefault;
		TBuf16<KBufferLength> generatedUnicode;
		TEST(aCharacterSetConverter.ConvertToUnicode(generatedUnicode, generatedFirstPartOfEucJpDirectmap, state)==0);
		TEST(state==CCnvCharacterSetConverter::KStateDefault);
		TBuf16<KBufferLength> generatedSecondPartOfUnicode;
		TEST(aCharacterSetConverter.ConvertToUnicode(generatedSecondPartOfUnicode, generatedSecondPartOfEucJpDirectmap, state)==0);
		TEST(state==CCnvCharacterSetConverter::KStateDefault);
		generatedUnicode.Append(generatedSecondPartOfUnicode);
		TEST(generatedUnicode==aOriginalUnicode);
		}
	}

LOCAL_C void TestTruncatedConversionToUnicodeFromEucJpDirectmap(CCnvCharacterSetConverter& aCharacterSetConverter, const TDesC16& aExpectedUnicode, const TDesC8& aOriginalEucJpDirectmap)
	{
	for (TInt i=aOriginalEucJpDirectmap.Length(); i>=3; --i) 
		{
		TInt state=CCnvCharacterSetConverter::KStateDefault;
		TBuf16<KBufferLength> generatedUnicode;
		const TInt returnValue=aCharacterSetConverter.ConvertToUnicode(generatedUnicode, aOriginalEucJpDirectmap.Left(i), state);
		TEST(returnValue>=0);
		TBuf16<KBufferLength> generatedsecondPartOfUnicode;
		TEST(aCharacterSetConverter.ConvertToUnicode(generatedsecondPartOfUnicode, aOriginalEucJpDirectmap.Mid(i-returnValue), state)==0);
		generatedUnicode.Append(generatedsecondPartOfUnicode);
		TEST(generatedUnicode==aExpectedUnicode);
		}
	}

LOCAL_C void TestSplittingConvertingToUnicodeFromEucJpDirectmap(CCnvCharacterSetConverter& aCharacterSetConverter, TInt aMaximumLengthLowerLimit, TInt aMaximumLengthUpperLimit, TInt aExpectedNumberOfEucJpDirectmapBytesNotConvertedAtSplit, TInt aExpectedLengthOfFirstPartOfUnicode, const TDesC16& aExpectedUnicode, const TDesC8& aOriginalEucJpDirectmap)
	{
	TEST(aMaximumLengthLowerLimit<=aMaximumLengthUpperLimit);
	TEST(aMaximumLengthUpperLimit<=KBufferLength);
	TUint16 unicodeBuffer[KBufferLength];
	for (TInt i=aMaximumLengthLowerLimit; i<=aMaximumLengthUpperLimit; ++i)
		{
		TPtr16 generatedFirstPartOfUnicode(unicodeBuffer, i);
		TInt state=CCnvCharacterSetConverter::KStateDefault;
		TEST(aCharacterSetConverter.ConvertToUnicode(generatedFirstPartOfUnicode, aOriginalEucJpDirectmap, state)==aExpectedNumberOfEucJpDirectmapBytesNotConvertedAtSplit);
		TEST(generatedFirstPartOfUnicode==aExpectedUnicode.Left(aExpectedLengthOfFirstPartOfUnicode));
		TEST(state==CCnvCharacterSetConverter::KStateDefault);
		TBuf16<KBufferLength> generatedSecondPartOfUnicode;
		TEST(aCharacterSetConverter.ConvertToUnicode(generatedSecondPartOfUnicode, aOriginalEucJpDirectmap.Right(aExpectedNumberOfEucJpDirectmapBytesNotConvertedAtSplit), state)==0);
		TEST(generatedSecondPartOfUnicode==aExpectedUnicode.Mid(aExpectedLengthOfFirstPartOfUnicode));
		TEST(state==CCnvCharacterSetConverter::KStateDefault);
		TBuf8<KBufferLength> generatedEucJpDirectmap;
		TEST(aCharacterSetConverter.ConvertFromUnicode(generatedEucJpDirectmap, generatedFirstPartOfUnicode)==0);
		TBuf8<KBufferLength> generatedSecondPartOfEucJpDirectmap;
		TEST(aCharacterSetConverter.ConvertFromUnicode(generatedSecondPartOfEucJpDirectmap, generatedSecondPartOfUnicode)==0);
		generatedEucJpDirectmap.Append(generatedSecondPartOfEucJpDirectmap);
		TEST(generatedEucJpDirectmap==aOriginalEucJpDirectmap);
		}
	}

LOCAL_C void TestIsIllFormedEucJpDirectmap(CCnvCharacterSetConverter& aCharacterSetConverter, const TDesC8& aEucJpDirectmap)
	{
	TBuf16<50> generatedUnicode;
	TInt state=CCnvCharacterSetConverter::KStateDefault;
	TPtrC8 remainderOfEucJpDirectmap(aEucJpDirectmap);
	TInt lastReturnValue=KMaxTInt;
	FOREVER
		{
		const TInt returnValue=aCharacterSetConverter.ConvertToUnicode(generatedUnicode, remainderOfEucJpDirectmap, state);
		if (returnValue==CCnvCharacterSetConverter::EErrorIllFormedInput)
			{
			break;
			}
		TEST(returnValue>0);
		TEST(returnValue<lastReturnValue);
		lastReturnValue=returnValue;
		remainderOfEucJpDirectmap.Set(remainderOfEucJpDirectmap.Right(returnValue));
		}
	}

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
	TheTest.Start(_L("Testing EUC-JP (DirectMap) conversions "));
	characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierEucJpDirectmap, *arrayOfCharacterSetsAvailable, fileServerSession);
	//
	TheTest.Next(_L("Empty descriptor"));
	TestSplittingConvertingFromUnicodeToEucJpDirectmap(*characterSetConverter, 0, 10, 0, 0, KNullDesC8, KNullDesC16);
	TestSplittingConvertingToUnicodeFromEucJpDirectmap(*characterSetConverter, 0, 10, 0, 0, KNullDesC16, KNullDesC8);
	TheTest.Next(_L("Testing converting to EUC-JP (DirectMap)"));
	TBuf16<50> originalUnicode;
	originalUnicode.Format(_L16("Some %c%c%c%c%c%c"), 0xff9a, 0xff70, 0x6f22, 0x5b57, 0x5379, 0x5dce);
	const TPtrC8 expectedEucJpDirectmap(_S8("Some \x8e\xda\x8e\xb0\xb4\xc1\xbb\xfa\x8f\xb4\xc1\x8f\xbb\xfa"));
	TestTruncatedConversionFromUnicodeToEucJpDirectmap(*characterSetConverter, originalUnicode);
	TestSplittingConvertingFromUnicodeToEucJpDirectmap(*characterSetConverter, 0, 0, 11, 0, expectedEucJpDirectmap, originalUnicode);
	TestSplittingConvertingFromUnicodeToEucJpDirectmap(*characterSetConverter, 1, 1, 10, 1, expectedEucJpDirectmap, originalUnicode);
	TestSplittingConvertingFromUnicodeToEucJpDirectmap(*characterSetConverter, 2, 2, 9, 2, expectedEucJpDirectmap, originalUnicode);
	TestSplittingConvertingFromUnicodeToEucJpDirectmap(*characterSetConverter, 3, 3, 8, 3, expectedEucJpDirectmap, originalUnicode);
	TestSplittingConvertingFromUnicodeToEucJpDirectmap(*characterSetConverter, 4, 4, 7, 4, expectedEucJpDirectmap, originalUnicode);
	TestSplittingConvertingFromUnicodeToEucJpDirectmap(*characterSetConverter, 5, 6, 6, 5, expectedEucJpDirectmap, originalUnicode);
	TestSplittingConvertingFromUnicodeToEucJpDirectmap(*characterSetConverter, 7, 8, 5, 7, expectedEucJpDirectmap, originalUnicode);
	TestSplittingConvertingFromUnicodeToEucJpDirectmap(*characterSetConverter, 9, 10, 4, 9, expectedEucJpDirectmap, originalUnicode);
	TestSplittingConvertingFromUnicodeToEucJpDirectmap(*characterSetConverter, 11, 12, 3, 11, expectedEucJpDirectmap, originalUnicode);
	TestSplittingConvertingFromUnicodeToEucJpDirectmap(*characterSetConverter, 13, 15, 2, 13, expectedEucJpDirectmap, originalUnicode);
	TestSplittingConvertingFromUnicodeToEucJpDirectmap(*characterSetConverter, 16, 18, 1, 16, expectedEucJpDirectmap, originalUnicode);
	TestSplittingConvertingFromUnicodeToEucJpDirectmap(*characterSetConverter, 19, 30, 0, 19, expectedEucJpDirectmap, originalUnicode);
	TheTest.Next(_L("Testing converting to Unicode"));
	const TPtrC8 originalEucJpDirectmap(_S8("pool\xbe\xae\xc3\xd3\x8e\xcc\x8e\xdf\x8e\xd9\x8f\xc0\xcd\x8f\xc8\xc5pool\x8e\xcc\x8e\xdf\x8e\xd9\xbe\xae\xc3\xd3\x8f\xc0\xcd\x8f\xc8\xc5\xbe\xae\xc3\xd3pool\x8f\xc0\xcd\x8f\xc8\xc5\x8e\xcc\x8e\xdf\x8e\xd9pool"));
	TBuf16<50> expectedUnicode;
	expectedUnicode.Format(_L16("pool%c%c%c%c%c%c%cpool%c%c%c%c%c%c%c%c%cpool%c%c%c%c%cpool"), 0x5c0f, 0x6c60, 0xff8c, 0xff9f, 0xff99, 0x641e, 0x6f0d, 0xff8c, 0xff9f, 0xff99, 0x5c0f, 0x6c60, 0x641e, 0x6f0d, 0x5c0f, 0x6c60, 0x641e, 0x6f0d, 0xff8c, 0xff9f, 0xff99);
	TestTruncatedConversionToUnicodeFromEucJpDirectmap(*characterSetConverter, expectedUnicode, originalEucJpDirectmap);
	TestTruncatedConversionToUnicodeFromEucJpDirectmap(*characterSetConverter, expectedUnicode.Mid(4, 2), originalEucJpDirectmap.Mid(4, 4));
	TestTruncatedConversionToUnicodeFromEucJpDirectmap(*characterSetConverter, expectedUnicode.Mid(6, 3), originalEucJpDirectmap.Mid(8, 6));
	TestTruncatedConversionToUnicodeFromEucJpDirectmap(*characterSetConverter, expectedUnicode.Mid(9, 2), originalEucJpDirectmap.Mid(14, 6));
	static const TInt numberOfCharactersInEachHomogeneousRun[13]={4, 2, 3, 2, 4, 3, 2, 2, 2, 4, 2, 3, 4};
	static const TInt numberOfBytesPerCharacterInEachHomogeneousRun[13]={1, 2, 2, 3, 1, 2, 2, 3, 2, 1, 3, 2, 1};
	TInt e=64;
	TInt u=0;
	for (i=0; i<13; ++i)
		{
		TInt j;
		for (j=0; j<numberOfCharactersInEachHomogeneousRun[i]; ++j, ++u, e-=numberOfBytesPerCharacterInEachHomogeneousRun[i])
			{
			TestSplittingConvertingToUnicodeFromEucJpDirectmap(*characterSetConverter, u, u, e, u, expectedUnicode, originalEucJpDirectmap);
			}
		}
	TEST(e==0);
	TEST(u==37);
	TestSplittingConvertingToUnicodeFromEucJpDirectmap(*characterSetConverter, u, u+10, e, u, expectedUnicode, originalEucJpDirectmap);
	TheTest.Next(_L("Testing ill-formed EUC-JP (DirectMap)"));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("\xa1"));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("\xa1\xb2\xc3"));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("\xa1\xb2\x8e"));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("\xa1\xb2\x8f"));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("\xa1\xb2\x8f\xaa"));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("\x8e\xd4\x8e"));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("\x8e\xd4\x8f"));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("\x8e\xd4\x8f\xbb"));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("\x8f\xe5\x8e"));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("\x8f\xe5\x8f"));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("\x8f\xe5\x8f\xcc"));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("xyz\x8e\xd4\x8e"));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("xyz\x8e\xd4\x8f"));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("xyz\x8e\xd4\x8f\xdd"));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("xyz\x8f\xe5\x8e"));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("xyz\x8f\xe5\x8f"));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("xyz\x8f\xe5\x8f\xee"));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("\x8e "));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("\x8f "));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("\x8f\xf1 "));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("\x8e\x41"));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("\x8f\x41"));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("\x8f\xe2\x41"));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("amb\x8e "));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("amb\x8f "));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("amb\x8f\xf1 "));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("amb\x8e\x41"));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("amb\x8f\x41"));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("amb\x8f\xe2\x41"));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("\xa1 "));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("\xa1\x61"));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("eb\xa1 "));
	TestIsIllFormedEucJpDirectmap(*characterSetConverter, _L8("eb\xa1\x61"));
	
	const TPtrC8 originalEucJpDirectmapYen(_S8("pool\x5c"));
	TBuf16<10> expectedUnicodeBackSlash;
	expectedUnicodeBackSlash.Format(_L16("pool%c"), 0x005c);
    TInt state=CCnvCharacterSetConverter::KStateDefault;
    TBuf16<KBufferLength> generatedUnicodeBackSlash;
    TEST(characterSetConverter->ConvertToUnicode(generatedUnicodeBackSlash, originalEucJpDirectmapYen, state) == 0);
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

