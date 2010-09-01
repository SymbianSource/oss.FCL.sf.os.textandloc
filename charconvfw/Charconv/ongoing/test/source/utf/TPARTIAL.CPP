/*
* Copyright (c) 1997-2005 Nokia Corporation and/or its subsidiary(-ies). 
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
#include <e32test.h>
#include <utf.h>

///////////////////////////////////////////////////////////////////////////////////////

RTest TheTest(_L("TPartial"));
	
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//Tests macroses and functions.
static void Check(TInt aValue, TInt aLine)
	{
	if(!aValue)
		{
		TheTest(EFalse, aLine);
		}
	}
#define TEST(arg) ::Check((arg), __LINE__)

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
	
const TInt KUtfBufferLength=100;
const TUint KIllegalUtfByteValue=0xff;
const TUint KIllegalUnicodeCharacter=0xffff;

LOCAL_C void FillWithIllegalUtf(TUint8* aUtfBuffer)
	{
	for (TInt i=0; i<KUtfBufferLength; ++i)
		{
		aUtfBuffer[i]=KIllegalUtfByteValue;
		}
	}

LOCAL_C TBool FillWithIllegalUtfReturningIfMatched(TUint8* aUtfBuffer, const TDes8& aDescriptorAroundBuffer, const TDesC8& aUtfToMatch)
	{
	__ASSERT_ALWAYS(aDescriptorAroundBuffer.Ptr()==aUtfBuffer, User::Panic(_L("TPARTIAL"), 0));
	__ASSERT_ALWAYS(aDescriptorAroundBuffer.MaxLength()>=aUtfToMatch.Length(), User::Panic(_L("TPARTIAL"), 1));
	__ASSERT_ALWAYS(aDescriptorAroundBuffer.MaxLength()<=KUtfBufferLength, User::Panic(_L("TPARTIAL"), 2));
	TBool matched=TPtrC8(aUtfBuffer, aUtfToMatch.Length())==aUtfToMatch;
	if (matched)
		{
		for (TInt i=aDescriptorAroundBuffer.MaxLength(); i<KUtfBufferLength; ++i)
			{
			if (aUtfBuffer[i]!=KIllegalUtfByteValue)
				{
				matched=EFalse;
				break;
				}
			}
		}
	FillWithIllegalUtf(aUtfBuffer);
	return matched;
	}

LOCAL_C void FillWithIllegalUnicode(TUint16* aUnicodeBuffer)
	{
	for (TInt i=0; i<KUtfBufferLength; ++i)
		{
		aUnicodeBuffer[i]=KIllegalUnicodeCharacter;
		}
	}

LOCAL_C TBool FillWithIllegalUnicodeReturningIfMatched(TUint16* aUnicodeBuffer, const TDesC16& aUnicodeToMatch)
	{
	const TInt lengthToMatch=aUnicodeToMatch.Length();
	TBool matched=TPtrC16(aUnicodeBuffer, lengthToMatch)==aUnicodeToMatch;
	if (matched)
		{
		for (TInt i=lengthToMatch; i<KUtfBufferLength; ++i)
			{
			if (aUnicodeBuffer[i]!=KIllegalUnicodeCharacter)
				{
				matched=EFalse;
				break;
				}
			}
		}
	FillWithIllegalUnicode(aUnicodeBuffer);
	return matched;
	}
/**
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0572
@SYMTestCaseDesc        Tests that partial conversions work
@SYMTestPriority        Medium
@SYMTestActions        	Tests for converting to Unicode from UTF- 7 
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void TestConvertingToUtf(TUint8* aUtfBuffer, TInt aMaximumLengthOfUtfDescriptor, const TDesC16& aUnicode, TBool aBoolParameter, TInt aNumberOfUnicodeItemsExpectedToBeConverted, const TDesC8& aFirstHalfOfUtfExpected, const TDesC8& aSecondHalfOfUtfExpected)
	{
	TPtr8 utf(aUtfBuffer, aMaximumLengthOfUtfDescriptor);
	FillWithIllegalUtf(aUtfBuffer);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(utf, aUnicode, aBoolParameter)==aNumberOfUnicodeItemsExpectedToBeConverted);
	TEST(FillWithIllegalUtfReturningIfMatched(aUtfBuffer, utf, aFirstHalfOfUtfExpected));
	TPtr8 restOfUtf(aUtfBuffer, KUtfBufferLength);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(restOfUtf, aUnicode.Right(aNumberOfUnicodeItemsExpectedToBeConverted), aBoolParameter)==0);
	TEST(FillWithIllegalUtfReturningIfMatched(aUtfBuffer, restOfUtf, aSecondHalfOfUtfExpected));
	TBuf8<KUtfBufferLength> originalUtf(aFirstHalfOfUtfExpected);
	originalUtf.Append(aSecondHalfOfUtfExpected);
	TBuf16<20> generatedUnicode;
	TInt state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, originalUtf, state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode==aUnicode);
	}
/**
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0573
@SYMTestCaseDesc        Tests that partial conversions work
@SYMTestPriority        Medium
@SYMTestActions        	Tests for converting to Unicode from UTF- 7
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void TestUtf7StatePreservation(const TDesC8& aUtf7)
	{
	TInt state=CnvUtfConverter::KStateDefault;
	TBuf16<50> wholeGeneratedUnicode;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(wholeGeneratedUnicode, aUtf7, state)==0);
	for (TInt i=aUtf7.Length()-1; i>=0; --i)
		{
		state=CnvUtfConverter::KStateDefault;
		TBuf16<50> generatedUnicode1;
		TInt numberOfUtf7BytesNotConvertedByFirstCall=CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode1, aUtf7.Left(i), state);
		if (numberOfUtf7BytesNotConvertedByFirstCall<0)
			{
			TEST(numberOfUtf7BytesNotConvertedByFirstCall==CnvUtfConverter::EErrorIllFormedInput);
			numberOfUtf7BytesNotConvertedByFirstCall=i;
			generatedUnicode1=KNullDesC16;
			state=CnvUtfConverter::KStateDefault;
			}
		TEST(numberOfUtf7BytesNotConvertedByFirstCall>=0);
		TBuf16<50> generatedUnicode2;
		TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode2, aUtf7.Mid(i-numberOfUtf7BytesNotConvertedByFirstCall), state)==0);
		generatedUnicode1+=generatedUnicode2;
		TEST(generatedUnicode1==wholeGeneratedUnicode);
		}
	}

LOCAL_C void TestConvertingToUtf(TUint8* aUtfBuffer, TInt aMaximumLengthOfUtfDescriptor, const TDesC16& aUnicode, TInt aNumberOfUnicodeItemsExpectedToBeConverted, const TDesC8& aFirstHalfOfUtfExpected, const TDesC8& aSecondHalfOfUtfExpected)
	{
	TestConvertingToUtf(aUtfBuffer, aMaximumLengthOfUtfDescriptor, aUnicode, EFalse, aNumberOfUnicodeItemsExpectedToBeConverted, aFirstHalfOfUtfExpected, aSecondHalfOfUtfExpected);
	}

GLDEF_C TInt E32Main()
	{
	TheTest.Title();
	TheTest.Start(_L("Checking that partial conversions work"));
	TUint8 utfBuffer[KUtfBufferLength];
	TUint16 unicodeBuffer[KUtfBufferLength];
	TheTest.Next(_L("Testing trivial UTF-7 and UTF-8"));
	{
	for (TInt i=0; i<6; ++i)
		{
		const TInt numberOfUnconvertedItemsAtEndOfInputDescriptor=5-i;
		TPtr8 utf(utfBuffer, i);
		FillWithIllegalUtf(utfBuffer);
		TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(utf, _L16("abcde"), EFalse)==numberOfUnconvertedItemsAtEndOfInputDescriptor);
		TEST(FillWithIllegalUtfReturningIfMatched(utfBuffer, utf, _L8("abcde").Left(i)));
		TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(utf, _L16("abcde"), ETrue)==numberOfUnconvertedItemsAtEndOfInputDescriptor);
		TEST(FillWithIllegalUtfReturningIfMatched(utfBuffer, utf, _L8("abcde").Left(i)));
		TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(utf, _L16("abcde"))==numberOfUnconvertedItemsAtEndOfInputDescriptor);
		TEST(FillWithIllegalUtfReturningIfMatched(utfBuffer, utf, _L8("abcde").Left(i)));
		TPtr16 unicode(unicodeBuffer, i);
		TInt state=CnvUtfConverter::KStateDefault;
		FillWithIllegalUnicode(unicodeBuffer);
		TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(unicode, _L8("abcde"), state)==numberOfUnconvertedItemsAtEndOfInputDescriptor);
		TEST(FillWithIllegalUnicodeReturningIfMatched(unicodeBuffer, _L16("abcde").Left(i)));
		TEST(state==CnvUtfConverter::KStateDefault);
		TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(unicode, _L8("abcde"))==numberOfUnconvertedItemsAtEndOfInputDescriptor);
		TEST(FillWithIllegalUnicodeReturningIfMatched(unicodeBuffer, _L16("abcde").Left(i)));
		}
	}
	TheTest.Next(_L("Testing converting to UTF-7"));
	{
	TBuf16<20> originalUnicode;
	TBuf16<20> generatedUnicode;
	TBuf8<20> generatedUtf;
	originalUnicode.Format(_L16("%c%c%c%c?"), 0x8fd9, 0x662f, 0x4ec0, 0x4e48); // Chinese: zhe4 shi4 shen2 me?
	TInt i;
	for (i=0; i<=4; ++i)
		{
		TestConvertingToUtf(utfBuffer, i, originalUnicode, 5, KNullDesC8, _L8("+j9lmL07ATkg-?"));
		}
	for (i=5; i<=7; ++i)
		{
		TestConvertingToUtf(utfBuffer, i, originalUnicode, 4, _L8("+j9k-"), _L8("+Zi9OwE5I-?"));
		}
	for (i=8; i<=9; ++i)
		{
		TestConvertingToUtf(utfBuffer, i, originalUnicode, 3, _L8("+j9lmLw-"), _L8("+TsBOSA-?"));
		}
	for (i=10; i<=12; ++i)
		{
		TestConvertingToUtf(utfBuffer, i, originalUnicode, 2, _L8("+j9lmL07A-"), _L8("+Tkg-?"));
		}
	TestConvertingToUtf(utfBuffer, 13, originalUnicode, 1, _L8("+j9lmL07ATkg-"), _L8("?"));
	TestConvertingToUtf(utfBuffer, 14, originalUnicode, 0, _L8("+j9lmL07ATkg-?"), KNullDesC8);
	originalUnicode.Format(_L16("%c %c%c %c%c%c%c."), 0x042f, 0x043d, 0x0435, 0x0437, 0x043d, 0x0430, 0x044e); // Russian: ya nye znayu.
	for (i=0; i<=4; ++i)
		{
		TestConvertingToUtf(utfBuffer, i, originalUnicode, 10, KNullDesC8, _L8("+BC8- +BD0ENQ- +BDcEPQQwBE4-."));
		}
	TestConvertingToUtf(utfBuffer, 5, originalUnicode, 9, _L8("+BC8-"), _L8(" +BD0ENQ- +BDcEPQQwBE4-."));
	for (i=6; i<=10; ++i)
		{
		TestConvertingToUtf(utfBuffer, i, originalUnicode, 8, _L8("+BC8- "), _L8("+BD0ENQ- +BDcEPQQwBE4-."));
		}
	for (i=11; i<=13; ++i)
		{
		TestConvertingToUtf(utfBuffer, i, originalUnicode, 7, _L8("+BC8- +BD0-"), _L8("+BDU- +BDcEPQQwBE4-."));
		}
	TestConvertingToUtf(utfBuffer, 14, originalUnicode, 6, _L8("+BC8- +BD0ENQ-"), _L8(" +BDcEPQQwBE4-."));
	for (i=15; i<=19; ++i)
		{
		TestConvertingToUtf(utfBuffer, i, originalUnicode, 5, _L8("+BC8- +BD0ENQ- "), _L8("+BDcEPQQwBE4-."));
		}
	for (i=20; i<=22; ++i)
		{
		TestConvertingToUtf(utfBuffer, i, originalUnicode, 4, _L8("+BC8- +BD0ENQ- +BDc-"), _L8("+BD0EMARO-."));
		}
	for (i=23; i<=24; ++i)
		{
		TestConvertingToUtf(utfBuffer, i, originalUnicode, 3, _L8("+BC8- +BD0ENQ- +BDcEPQ-"), _L8("+BDAETg-."));
		}
	for (i=25; i<=27; ++i)
		{
		TestConvertingToUtf(utfBuffer, i, originalUnicode, 2, _L8("+BC8- +BD0ENQ- +BDcEPQQw-"), _L8("+BE4-."));
		}
	TestConvertingToUtf(utfBuffer, 28, originalUnicode, 1, _L8("+BC8- +BD0ENQ- +BDcEPQQwBE4-"), _L8("."));
	TestConvertingToUtf(utfBuffer, 29, originalUnicode, 0, _L8("+BC8- +BD0ENQ- +BDcEPQQwBE4-."), KNullDesC8);
	TheTest.Next(_L("Testing converting UCS-2 ending in truncated sequences"));
	originalUnicode.Format(_L16(" %c"), 0xd800);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf, originalUnicode, EFalse)==0);
	TEST(generatedUtf==_L8(" +2AA-"));
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf, originalUnicode, ETrue)==0);
	TEST(generatedUtf==_L8(" +2AA-"));
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf, originalUnicode)==1);
	TEST(generatedUtf.Length()==1);
	TEST(generatedUtf[0]==' ');
	originalUnicode.Format(_L16("%c"), 0xd800);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf, originalUnicode, EFalse)==0);
	TEST(generatedUtf==_L8("+2AA-"));
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf, originalUnicode, ETrue)==0);
	TEST(generatedUtf==_L8("+2AA-"));
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf, originalUnicode)==CnvUtfConverter::EErrorIllFormedInput);
	originalUnicode.Format(_L16("%c%c"), 0xd800, 0xdbff);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf, originalUnicode)==CnvUtfConverter::EErrorIllFormedInput);
	originalUnicode.Format(_L16("%c%c"), 0xd800, 0xdc00);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf, originalUnicode)==0);
	TEST(generatedUtf==_L8("\xf0\x90\x80\x80"));
	TheTest.Next(_L("Testing converting UTF-7 ending in truncated sequences"));
	TInt state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+"), state)==CnvUtfConverter::EErrorIllFormedInput);
	state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("e+"), state)==1);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]=='e');
	TEST(state==CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+-"), state)==0);
	TEST(generatedUnicode==_L16("+"));
	TEST(state==CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("++"), state)==1);
	TEST(generatedUnicode.Length()==0);
	TEST(state!=CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+"), state)==CnvUtfConverter::EErrorIllFormedInput); // before resetting state
	state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("++-"), state)==CnvUtfConverter::EErrorIllFormedInput);
	state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+++"), state)==2);
	TEST(generatedUnicode.Length()==0);
	TEST(state!=CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("++"), state)==CnvUtfConverter::EErrorIllFormedInput); // before resetting state
	state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+++-"), state)==CnvUtfConverter::EErrorIllFormedInput);
	state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("++++"), state)==3);
	TEST(generatedUnicode.Length()==0);
	TEST(state!=CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+++"), state)==CnvUtfConverter::EErrorIllFormedInput); // before resetting state
	state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("++++-"), state)==CnvUtfConverter::EErrorIllFormedInput);
	state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+++8"), state)==0);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0xfbef);
	TEST(state!=CnvUtfConverter::KStateDefault); // this is imporant, as even though we've converted all the input UTF-7, the input may be being received in chunks, in which case, we need to make sure we remember when converting the next chunk that we were previously in a base-64 sequence
	state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+++8-"), state)==0);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0xfbef);
	TEST(state==CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("++++/"), state)==1);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0xfbef);
	TEST(state!=CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("++++/-"), state)==CnvUtfConverter::EErrorIllFormedInput);
	state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("++++//"), state)==2);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0xfbef);
	TEST(state!=CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("++++//-"), state)==CnvUtfConverter::EErrorIllFormedInput);
	state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("++++///"), state)==3);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0xfbef);
	TEST(state!=CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("++++///-"), state)==CnvUtfConverter::EErrorIllFormedInput);
	state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("++++//w"), state)==0);
	TEST(generatedUnicode.Length()==2);
	TEST(generatedUnicode[0]==0xfbef);
	TEST(generatedUnicode[1]==0xbfff);
	TEST(state!=CnvUtfConverter::KStateDefault); // this is imporant, as even though we've converted all the input UTF-7, the input may be being received in chunks, in which case, we need to make sure we remember when converting the next chunk that we were previously in a base-64 sequence
	state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("++++//w-"), state)==0);
	TEST(generatedUnicode.Length()==2);
	TEST(generatedUnicode[0]==0xfbef);
	TEST(generatedUnicode[1]==0xbfff);
	TEST(state==CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("++++///h"), state)==1);
	TEST(generatedUnicode.Length()==2);
	TEST(generatedUnicode[0]==0xfbef);
	TEST(generatedUnicode[1]==0xbfff);
	TEST(state!=CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("++++///h-"), state)==CnvUtfConverter::EErrorIllFormedInput);
	state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("++++///hh"), state)==0);
	TEST(generatedUnicode.Length()==3);
	TEST(generatedUnicode[0]==0xfbef);
	TEST(generatedUnicode[1]==0xbfff);
	TEST(generatedUnicode[2]==0xf861);
	TEST(state!=CnvUtfConverter::KStateDefault); // this is imporant, as even though we've converted all the input UTF-7, the input may be being received in chunks, in which case, we need to make sure we remember when converting the next chunk that we were previously in a base-64 sequence
	state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("++++///hh-"), state)==0);
	TEST(generatedUnicode.Length()==3);
	TEST(generatedUnicode[0]==0xfbef);
	TEST(generatedUnicode[1]==0xbfff);
	TEST(generatedUnicode[2]==0xf861);
	TEST(state==CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("++++///hht"), state)==1);
	TEST(generatedUnicode.Length()==3);
	TEST(generatedUnicode[0]==0xfbef);
	TEST(generatedUnicode[1]==0xbfff);
	TEST(generatedUnicode[2]==0xf861);
	TEST(state!=CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("++++///hht-"), state)==CnvUtfConverter::EErrorIllFormedInput);
	state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("++++///hhtt"), state)==2);
	TEST(generatedUnicode.Length()==3);
	TEST(generatedUnicode[0]==0xfbef);
	TEST(generatedUnicode[1]==0xbfff);
	TEST(generatedUnicode[2]==0xf861);
	TEST(state!=CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("++++///hhtt-"), state)==CnvUtfConverter::EErrorIllFormedInput);
	state=CnvUtfConverter::KStateDefault;
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+34-"), state)==CnvUtfConverter::EErrorIllFormedInput);
	TestUtf7StatePreservation(_L8("++34-"));
	TestUtf7StatePreservation(_L8("+rY4/5b+al3V98w-"));
	TestUtf7StatePreservation(_L8("+ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/-"));
	TheTest.Next(_L("Testing converting UTF-8 ending in truncated sequences"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, _L8("\xc8"))==CnvUtfConverter::EErrorIllFormedInput);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, _L8("x\xc8"))==1);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]=='x');
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, _L8("\xc8\xc0"))==1); 
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, _L8("\xc8\xb0"))==0);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0x0230);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, _L8("\xe4"))==CnvUtfConverter::EErrorIllFormedInput);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, _L8("y\xe4"))==1);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]=='y');
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, _L8("\xe4\x80"))==CnvUtfConverter::EErrorIllFormedInput); 
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, _L8("H\xe4\x80"))==2);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]=='H');
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, _L8("\xe4\xc0"))==CnvUtfConverter::EErrorIllFormedInput); 
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, _L8("e\xe4\xc0"))==2);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]=='e');
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, _L8("\xe4\x80\xc0"))==1);  
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, _L8("\xe4\x80\xb0"))==0);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0x4030);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, _L8("\xf2"))==CnvUtfConverter::EErrorIllFormedInput); 
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, _L8("7\xf2"))==1);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]=='7');
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, _L8("\xf2\x80"))==CnvUtfConverter::EErrorIllFormedInput); 
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, _L8("\\\xf2\x80"))==2);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]=='\\');
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, _L8("\xf2\xc0"))==CnvUtfConverter::EErrorIllFormedInput); 
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, _L8("$\xf2\xc0"))==2);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]=='$');
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, _L8("\xf2\x80\x80"))==CnvUtfConverter::EErrorIllFormedInput); 
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, _L8("{\xf2\x80\x80"))==3);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]=='{');
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, _L8("\xf2\x80\xc0"))==CnvUtfConverter::EErrorIllFormedInput);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, _L8(" \xf2\x80\xc0"))==3);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==' ');
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, _L8("\xf2\x80\x80\xc0"))==1);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, _L8("\xf2\x80\x80\xb0"))==0);
	TEST(generatedUnicode.Length()==2);
	TEST(generatedUnicode[0]==0xd9c0);
	TEST(generatedUnicode[1]==0xdc30);
	}
	TheTest.End();
	TheTest.Close();
	return KErrNone;
	}

