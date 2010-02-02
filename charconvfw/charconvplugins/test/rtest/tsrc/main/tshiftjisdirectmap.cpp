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

RTest TheTest(_L("TSHIFTJISDIRECTMAP"));

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

LOCAL_C void TestTruncatedConversionFromUnicodeToShiftJisDirectmap(CCnvCharacterSetConverter& aCharacterSetConverter, const TDesC16& aOriginalUnicode)
	{
	for (TInt i=aOriginalUnicode.Length(); i>=0; --i)
		{
		TBuf8<KBufferLength> generatedShiftJisDirectmap;
		const TInt returnValue=aCharacterSetConverter.ConvertFromUnicode(generatedShiftJisDirectmap, aOriginalUnicode.Left(i));
		TEST(returnValue>=0);
		TBuf8<KBufferLength> generatedsecondPartOfShiftJisDirectmap;
		TEST(aCharacterSetConverter.ConvertFromUnicode(generatedsecondPartOfShiftJisDirectmap, aOriginalUnicode.Mid(i-returnValue))==0);
		generatedShiftJisDirectmap.Append(generatedsecondPartOfShiftJisDirectmap);
		TInt state=CCnvCharacterSetConverter::KStateDefault;
		TBuf16<KBufferLength> generatedUnicode;
		TEST(aCharacterSetConverter.ConvertToUnicode(generatedUnicode, generatedShiftJisDirectmap, state)==0);
		TEST(generatedUnicode==aOriginalUnicode);
		}
	}

LOCAL_C void TestSplittingConvertingFromUnicodeToShiftJisDirectmap(CCnvCharacterSetConverter& aCharacterSetConverter, TInt aMaximumLengthLowerLimit, TInt aMaximumLengthUpperLimit, TInt aExpectedNumberOfUnicodeCharactersNotConvertedAtSplit, TInt aExpectedLengthOfFirstPartOfShiftJisDirectmap, const TDesC8& aExpectedShiftJisDirectmap, const TDesC16& aOriginalUnicode)
	{
	TEST(aMaximumLengthLowerLimit<=aMaximumLengthUpperLimit);
	TEST(aMaximumLengthUpperLimit<=KBufferLength);
	TUint8 shiftJisDirectmapBuffer[KBufferLength];
	for (TInt i=aMaximumLengthLowerLimit; i<=aMaximumLengthUpperLimit; ++i)
		{
		TPtr8 generatedFirstPartOfShiftJisDirectmap(shiftJisDirectmapBuffer, i);
		TEST(aCharacterSetConverter.ConvertFromUnicode(generatedFirstPartOfShiftJisDirectmap, aOriginalUnicode)==aExpectedNumberOfUnicodeCharactersNotConvertedAtSplit);
		TEST(generatedFirstPartOfShiftJisDirectmap==aExpectedShiftJisDirectmap.Left(aExpectedLengthOfFirstPartOfShiftJisDirectmap));
		TBuf8<KBufferLength> generatedSecondPartOfShiftJisDirectmap;
		TEST(aCharacterSetConverter.ConvertFromUnicode(generatedSecondPartOfShiftJisDirectmap, aOriginalUnicode.Right(aExpectedNumberOfUnicodeCharactersNotConvertedAtSplit))==0);
		TEST(generatedSecondPartOfShiftJisDirectmap==aExpectedShiftJisDirectmap.Mid(aExpectedLengthOfFirstPartOfShiftJisDirectmap));
		TInt state=CCnvCharacterSetConverter::KStateDefault;
		TBuf16<KBufferLength> generatedUnicode;
		TEST(aCharacterSetConverter.ConvertToUnicode(generatedUnicode, generatedFirstPartOfShiftJisDirectmap, state)==0);
		TEST(state==CCnvCharacterSetConverter::KStateDefault);
		TBuf16<KBufferLength> generatedSecondPartOfUnicode;
		TEST(aCharacterSetConverter.ConvertToUnicode(generatedSecondPartOfUnicode, generatedSecondPartOfShiftJisDirectmap, state)==0);
		TEST(state==CCnvCharacterSetConverter::KStateDefault);
		generatedUnicode.Append(generatedSecondPartOfUnicode);
		TEST(generatedUnicode==aOriginalUnicode);
		}
	}

LOCAL_C void TestTruncatedConversionToUnicodeFromShiftJisDirectmap(CCnvCharacterSetConverter& aCharacterSetConverter, const TDesC16& aExpectedUnicode, const TDesC8& aOriginalShiftJisDirectmap)
	{
	for (TInt i=aOriginalShiftJisDirectmap.Length(); i>=3; --i)
		{
		TInt state=CCnvCharacterSetConverter::KStateDefault;
		TBuf16<KBufferLength> generatedUnicode;
		const TInt returnValue=aCharacterSetConverter.ConvertToUnicode(generatedUnicode, aOriginalShiftJisDirectmap.Left(i), state);
		TEST(returnValue>=0);
		TBuf16<KBufferLength> generatedsecondPartOfUnicode;
		TEST(aCharacterSetConverter.ConvertToUnicode(generatedsecondPartOfUnicode, aOriginalShiftJisDirectmap.Mid(i-returnValue), state)==0);
		generatedUnicode.Append(generatedsecondPartOfUnicode);
		TEST(generatedUnicode==aExpectedUnicode);
		}
	}

LOCAL_C void TestSplittingConvertingToUnicodeFromShiftJisDirectmap(CCnvCharacterSetConverter& aCharacterSetConverter, TInt aMaximumLengthLowerLimit, TInt aMaximumLengthUpperLimit, TInt aExpectedNumberOfShiftJisDirectmapBytesNotConvertedAtSplit, TInt aExpectedLengthOfFirstPartOfUnicode, const TDesC16& aExpectedUnicode, const TDesC8& aOriginalShiftJisDirectmap)
	{
	TEST(aMaximumLengthLowerLimit<=aMaximumLengthUpperLimit);
	TEST(aMaximumLengthUpperLimit<=KBufferLength);
	TUint16 unicodeBuffer[KBufferLength];
	for (TInt i=aMaximumLengthLowerLimit; i<=aMaximumLengthUpperLimit; ++i)
		{
		TPtr16 generatedFirstPartOfUnicode(unicodeBuffer, i);
		TInt state=CCnvCharacterSetConverter::KStateDefault;
		TEST(aCharacterSetConverter.ConvertToUnicode(generatedFirstPartOfUnicode, aOriginalShiftJisDirectmap, state)==aExpectedNumberOfShiftJisDirectmapBytesNotConvertedAtSplit);
		TEST(generatedFirstPartOfUnicode==aExpectedUnicode.Left(aExpectedLengthOfFirstPartOfUnicode));
		TEST(state==CCnvCharacterSetConverter::KStateDefault);
		TBuf16<KBufferLength> generatedSecondPartOfUnicode;
		TEST(aCharacterSetConverter.ConvertToUnicode(generatedSecondPartOfUnicode, aOriginalShiftJisDirectmap.Right(aExpectedNumberOfShiftJisDirectmapBytesNotConvertedAtSplit), state)==0);
		TEST(generatedSecondPartOfUnicode==aExpectedUnicode.Mid(aExpectedLengthOfFirstPartOfUnicode));
		TEST(state==CCnvCharacterSetConverter::KStateDefault);
		TBuf8<KBufferLength> generatedShiftJisDirectmap;
		TEST(aCharacterSetConverter.ConvertFromUnicode(generatedShiftJisDirectmap, generatedFirstPartOfUnicode)==0);
		TBuf8<KBufferLength> generatedSecondPartOfShiftJisDirectmap;
		TEST(aCharacterSetConverter.ConvertFromUnicode(generatedSecondPartOfShiftJisDirectmap, generatedSecondPartOfUnicode)==0);
		generatedShiftJisDirectmap.Append(generatedSecondPartOfShiftJisDirectmap);
		TEST(generatedShiftJisDirectmap==aOriginalShiftJisDirectmap);
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
	TheTest.Start(_L("Testing ShiftJis (DirectMap) conversions "));
	characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierShiftJisDirectmap, *arrayOfCharacterSetsAvailable, fileServerSession);
	//
	TheTest.Next(_L("Empty descriptor"));
	TestSplittingConvertingFromUnicodeToShiftJisDirectmap(*characterSetConverter, 0, 10, 0, 0, KNullDesC8, KNullDesC16);
	TestSplittingConvertingToUnicodeFromShiftJisDirectmap(*characterSetConverter, 0, 10, 0, 0, KNullDesC16, KNullDesC8);
	
	TheTest.Next(_L("Testing converting to ShiftJis (DirectMap)"));
	TBuf16<50> originalUnicode;
	originalUnicode.Format(_L16("Some %c%c%c%c"), 0xff9a, 0xff70, 0x6f22, 0x5b57);
	const TPtrC8 expectedShiftJisDirectmap(_S8("Some \xda\xb0\x8a\xbf\x8e\x9a"));
	TestTruncatedConversionFromUnicodeToShiftJisDirectmap(*characterSetConverter, originalUnicode);
	TestSplittingConvertingFromUnicodeToShiftJisDirectmap(*characterSetConverter, 0, 0, 9, 0, expectedShiftJisDirectmap, originalUnicode);
	TestSplittingConvertingFromUnicodeToShiftJisDirectmap(*characterSetConverter, 1, 1, 8, 1, expectedShiftJisDirectmap, originalUnicode);
	TestSplittingConvertingFromUnicodeToShiftJisDirectmap(*characterSetConverter, 2, 2, 7, 2, expectedShiftJisDirectmap, originalUnicode);
	TestSplittingConvertingFromUnicodeToShiftJisDirectmap(*characterSetConverter, 3, 3, 6, 3, expectedShiftJisDirectmap, originalUnicode);
	TestSplittingConvertingFromUnicodeToShiftJisDirectmap(*characterSetConverter, 4, 4, 5, 4, expectedShiftJisDirectmap, originalUnicode);
	TestSplittingConvertingFromUnicodeToShiftJisDirectmap(*characterSetConverter, 5, 5, 4, 5, expectedShiftJisDirectmap, originalUnicode);
	TestSplittingConvertingFromUnicodeToShiftJisDirectmap(*characterSetConverter, 6, 6, 3, 6, expectedShiftJisDirectmap, originalUnicode);
	TestSplittingConvertingFromUnicodeToShiftJisDirectmap(*characterSetConverter, 7, 7, 2, 7, expectedShiftJisDirectmap, originalUnicode);
	TestSplittingConvertingFromUnicodeToShiftJisDirectmap(*characterSetConverter, 9, 9, 1, 9, expectedShiftJisDirectmap, originalUnicode);
	TestSplittingConvertingFromUnicodeToShiftJisDirectmap(*characterSetConverter, 11, 11, 0, 11, expectedShiftJisDirectmap, originalUnicode);
	
	TheTest.Next(_L("Testing converting to Unicode"));
	const TPtrC8 originalShiftJisDirectmap(_S8("pool\xbe\xae\xc3\xd3\x8e\xcc\x8e\xdf\x8e\xd9\x8f\xc0\xcd\x8f\xc8\xc5pool\x8e\xcc\x8e\xdf\x8e\xd9\xbe\xae\xc3\xd3\x8f\xc0\xcd\x8f\xc8\xc5\xbe\xae\xc3\xd3pool\x8f\xc0\xcd\x8f\xc8\xc5\x8e\xcc\x8e\xdf\x8e\xd9pool"));
	TBuf16<50> expectedUnicode;
	expectedUnicode.Format(_L16("pool%c%c%c%c%c%c%c%c%c%c%cpool%c%c%c%c%c%c%c%c%c%c%c%c%c%c%cpool%c%c%c%c%c%c%cpool"), 0xFF7E, 0xFF6E, 0xFF83, 0xFF93, 0x6368, 0x91C8, 0x52FA, 0x6CBC, 0xFF8D, 0x7701, 0xFF85, 0x6368, 0x91C8, 0x52FA, 0xFF7E, 0xFF6E, 0xFF83, 0xFF93, 0x6CBC, 0xFF8D, 0x7701, 0xFF85, 0xFF7E, 0xFF6E, 0xFF83, 0xFF93, 0x6CBC, 0xFF8D, 0x7701, 0xFF85, 0x6368, 0x91C8, 0x52FA);
	TestTruncatedConversionToUnicodeFromShiftJisDirectmap(*characterSetConverter, expectedUnicode, originalShiftJisDirectmap);
	TestTruncatedConversionToUnicodeFromShiftJisDirectmap(*characterSetConverter, expectedUnicode.Mid(4, 4), originalShiftJisDirectmap.Mid(4, 4));
	TestTruncatedConversionToUnicodeFromShiftJisDirectmap(*characterSetConverter, expectedUnicode.Mid(6, 3), originalShiftJisDirectmap.Mid(6, 4));
	TestTruncatedConversionToUnicodeFromShiftJisDirectmap(*characterSetConverter, expectedUnicode.Mid(11, 4), originalShiftJisDirectmap.Mid(14, 6));
	TestSplittingConvertingToUnicodeFromShiftJisDirectmap(*characterSetConverter, 4, 4, 60, 4, expectedUnicode, originalShiftJisDirectmap);
	TestSplittingConvertingToUnicodeFromShiftJisDirectmap(*characterSetConverter, 5, 5, 59, 5, expectedUnicode, originalShiftJisDirectmap);
	TestSplittingConvertingToUnicodeFromShiftJisDirectmap(*characterSetConverter, 6, 6, 58, 6, expectedUnicode, originalShiftJisDirectmap);
	
    const TPtrC8 originalShiftJisDirectmapYen(_S8("pool\x5c"));
    TBuf16<10> expectedUnicodeBackSlash;
    expectedUnicodeBackSlash.Format(_L16("pool%c"), 0x005c);
    TInt state=CCnvCharacterSetConverter::KStateDefault;
    TBuf16<KBufferLength> generatedUnicodeBackSlash;
    TEST(characterSetConverter->ConvertToUnicode(generatedUnicodeBackSlash, originalShiftJisDirectmapYen, state) == 0);
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

