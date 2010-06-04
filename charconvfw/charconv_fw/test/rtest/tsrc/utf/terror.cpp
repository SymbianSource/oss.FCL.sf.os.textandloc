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
#include <e32test.h>
#include <utf.h>

///////////////////////////////////////////////////////////////////////////////////////

RTest TheTest(_L("TError"));

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
		TheTest.Printf(_L("*** Expected error: %d, got: %d\r\n"), aExpected, aValue);
		TheTest(EFalse, aLine);
		}
	}
//Use these to test conditions.
#define TEST(arg) ::Check((arg), __LINE__)
#define TEST2(aValue, aExpected) ::Check(aValue, aExpected, __LINE__)

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

typedef TInt (*FConvertFromUtfX)(TDes16& aUnicode, const TDesC8& aUtfX, TInt& aState);

LOCAL_C TInt ConvertToUnicodeFromUtf7(TDes16& aUnicode, const TDesC8& aUtf7, TInt& aState)
	{
	return CnvUtfConverter::ConvertToUnicodeFromUtf7(aUnicode, aUtf7, aState);
	}

LOCAL_C TInt ConvertToUnicodeFromUtf8(TDes16& aUnicode, const TDesC8& aUtf8, TInt&)
	{
	return CnvUtfConverter::ConvertToUnicodeFromUtf8(aUnicode, aUtf8);
	}

LOCAL_C void ExhaustivelyLengthTest(const TDesC16& aUnicode, const TDesC8& aUtfX, FConvertFromUtfX aConvertFromUtfX)
	{
	enum {ECharacterCodeThatCannotOccurInUnicode=0xffff};
	enum {ELengthOfWorkSpace=256};

	TUint16 workSpace[ELengthOfWorkSpace];

	const TInt lengthOfUnicode=aUnicode.Length();
	TEST(lengthOfUnicode<ELengthOfWorkSpace);
	TInt i=0;
	FOREVER
		{
  		TPtr16 unicode(workSpace, 0, i);

		const TUint16* const lastCharacterOfWorkSpace=&workSpace[ELengthOfWorkSpace-1];

		{TUint16* characterPointer=&workSpace[i];
		FOREVER
			{
			*characterPointer=ECharacterCodeThatCannotOccurInUnicode;
			if (characterPointer==lastCharacterOfWorkSpace)
				{
				break;
				}
			++characterPointer;
			}}
		TInt state=CnvUtfConverter::KStateDefault;

		const TInt returnValue=(*aConvertFromUtfX)(unicode, aUtfX, state);
		TEST((returnValue!=0) || (state==CnvUtfConverter::KStateDefault));
		{const TUint16* characterPointer=&workSpace[i];
		FOREVER
			{
			TEST(*characterPointer==ECharacterCodeThatCannotOccurInUnicode);
			if (characterPointer==lastCharacterOfWorkSpace)
				{
				break;
				}
			++characterPointer;
			}}
		if (i==lengthOfUnicode)
			{
			TEST(unicode==aUnicode);
			if (returnValue!=0)
				{
				TEST(returnValue>0);
				TEST((*aConvertFromUtfX)(unicode, aUtfX.Right(returnValue), state)==0);
				TEST(unicode.Length()==0);
				TEST(state==CnvUtfConverter::KStateDefault);
				}
			break;
			}
		TEST(returnValue>0);
		++i;
		}
	}

typedef TInt (*FConvertToUtfX)(TDes8& aUtfX, const TDesC16& aUnicode);

LOCAL_C TInt ConvertFromUnicodeToUtf7WithOptionalDirectCharactersEncodedInBase64(TDes8& aUtf7, const TDesC16& aUnicode)
	{
	return CnvUtfConverter::ConvertFromUnicodeToUtf7(aUtf7, aUnicode, ETrue);
	}

LOCAL_C TInt ConvertFromUnicodeToUtf7WithOptionalDirectCharactersEncodedDirectly(TDes8& aUtf7, const TDesC16& aUnicode)
	{
	return CnvUtfConverter::ConvertFromUnicodeToUtf7(aUtf7, aUnicode, EFalse);
	}

LOCAL_C TInt ConvertFromUnicodeToUtf8(TDes8& aUtf8, const TDesC16& aUnicode)
	{
	return CnvUtfConverter::ConvertFromUnicodeToUtf8(aUtf8, aUnicode);
	}

LOCAL_C void ExhaustivelyLengthTest(const TDesC8& aUtfX, const TDesC16& aUnicode, FConvertToUtfX aConvertToUtfX)
	{
	enum {EByteValueThatCannotOccurInEitherUtf7OrUtf8=0xff};
	enum {ELengthOfWorkSpace=512};
	TUint8 workSpace[ELengthOfWorkSpace];
	const TInt lengthOfUtfX=aUtfX.Length();
	TEST(lengthOfUtfX<ELengthOfWorkSpace);
	TInt i=0;
	FOREVER
		{
		TPtr8 utfX(workSpace, 0, i);
		const TUint8* const lastByteOfWorkSpace=&workSpace[ELengthOfWorkSpace-1];
		{TUint8* bytePointer=&workSpace[i];
		FOREVER
			{
			*bytePointer=EByteValueThatCannotOccurInEitherUtf7OrUtf8;
			if (bytePointer==lastByteOfWorkSpace)
				{
				break;
				}
			++bytePointer;
			}}
		const TInt returnValue=(*aConvertToUtfX)(utfX, aUnicode);
		{const TUint8* bytePointer=&workSpace[i];
		FOREVER
			{
			TEST(*bytePointer==EByteValueThatCannotOccurInEitherUtf7OrUtf8);
			if (bytePointer==lastByteOfWorkSpace)
				{
				break;
				}
			++bytePointer;
			}}
		if (i==lengthOfUtfX)
			{
			TEST(returnValue==0);
			TEST(utfX==aUtfX);
			break;
			}
		TEST(returnValue>0);
		++i;
		}
	}

LOCAL_C void ExhaustivelyLengthTest(const TDesC16& aUnicode, const TDesC8& aUtf7WithOptionalDirectCharactersEncodedInBase64, const TDesC8& aUtf7WithOptionalDirectCharactersEncodedDirectly, const TDesC8& aUtf8)
	{
	ExhaustivelyLengthTest(aUnicode, aUtf7WithOptionalDirectCharactersEncodedInBase64, ConvertToUnicodeFromUtf7);
	ExhaustivelyLengthTest(aUnicode, aUtf7WithOptionalDirectCharactersEncodedDirectly, ConvertToUnicodeFromUtf7);
	ExhaustivelyLengthTest(aUnicode, aUtf8, ConvertToUnicodeFromUtf8);
	ExhaustivelyLengthTest(aUtf7WithOptionalDirectCharactersEncodedInBase64, aUnicode, ConvertFromUnicodeToUtf7WithOptionalDirectCharactersEncodedInBase64);
	ExhaustivelyLengthTest(aUtf7WithOptionalDirectCharactersEncodedDirectly, aUnicode, ConvertFromUnicodeToUtf7WithOptionalDirectCharactersEncodedDirectly);
	ExhaustivelyLengthTest(aUtf8, aUnicode, ConvertFromUnicodeToUtf8);
	}

LOCAL_C void ExhaustivelyLengthTest(const TDesC16& aUnicode, const TDesC8& aUtf7, const TDesC8& aUtf8)
	{
	ExhaustivelyLengthTest(aUnicode, aUtf7, aUtf7, aUtf8);
	}

LOCAL_C void ResetDescriptorsForNullTest(TDes8& aEmpty8, TDes16& aEmpty16, TDes8& aNonEmpty8, TDes16& aNonEmpty16)
	{
	aEmpty8.SetLength(0);
	aEmpty16.SetLength(0);
	aNonEmpty8=_L8("abc");
	aNonEmpty16=_L16("xyz");
	}

LOCAL_C void LengthTestGeneratingUtf7()
	{
	TBuf16<7> unicode;
	unicode.Format(_L16("+%c+&+a+"), 0x52ff);
	TPtr8 generatedUtf7(NULL, 0, 0);
	TUint8 utf7[15];
	TInt i;
	generatedUtf7.Set(utf7, 0, 15);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf7, unicode, EFalse)==0);
	TEST(generatedUtf7==_L8("+-+Uv8-+-&+-a+-"));
	for (i=14; i>=13; --i)
		{
		generatedUtf7.Set(utf7, 0, i);
		TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf7, unicode, EFalse)==1);
		TEST(generatedUtf7==_L8("+-+Uv8-+-&+-a"));
		}
	generatedUtf7.Set(utf7, 0, 12);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf7, unicode, EFalse)==2);
	TEST(generatedUtf7==_L8("+-+Uv8-+-&+-"));
	for (i=11; i>=10; --i)
		{
		generatedUtf7.Set(utf7, 0, i);
		TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf7, unicode, EFalse)==3);
		TEST(generatedUtf7==_L8("+-+Uv8-+-&"));
		}
	generatedUtf7.Set(utf7, 0, 9);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf7, unicode, EFalse)==4);
	TEST(generatedUtf7==_L8("+-+Uv8-+-"));
	for (i=8; i>=7; --i)
		{
		generatedUtf7.Set(utf7, 0, i);
		TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf7, unicode, EFalse)==5);
		TEST(generatedUtf7==_L8("+-+Uv8-"));
		}
	for (i=6; i>=2; --i)
		{
		generatedUtf7.Set(utf7, 0, i);
		TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf7, unicode, EFalse)==6);
		TEST(generatedUtf7==_L8("+-"));
		}
	for (i=1; i>=0; --i)
		{
		generatedUtf7.Set(utf7, 0, i);
		TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf7, unicode, EFalse)==7);
		TEST(generatedUtf7==KNullDesC8);
		}
	}

LOCAL_C void LengthTestGeneratingUtf8()
	{
	TBuf16<5> unicode;
	unicode.Format(_L16("J%c%c%c%c"), 0x027e, 0xb205, 0xdbab, 0xde4d);
	TPtr8 generatedUtf8(NULL, 0, 0);
	TUint8 utf8[10];
	TInt i;
	generatedUtf8.Set(utf8, 0, 10);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("J\xc9\xbe\xeb\x88\x85\xf3\xba\xb9\x8d"));
	for (i=9; i>=6; --i)
		{
		generatedUtf8.Set(utf8, 0, i);
		TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==2);
		TEST(generatedUtf8==_L8("J\xc9\xbe\xeb\x88\x85"));
		}
	for (i=5; i>=3; --i)
		{
		generatedUtf8.Set(utf8, 0, i);
		TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==3);
		TEST(generatedUtf8==_L8("J\xc9\xbe"));
		}
	for (i=2; i>=1; --i)
		{
		generatedUtf8.Set(utf8, 0, i);
		TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==4);
		TEST(generatedUtf8==_L8("J"));
		}
	generatedUtf8.Set(utf8, 0, 0);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==5);
	TEST(generatedUtf8==KNullDesC8);
	}
/**
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0569
@SYMTestCaseDesc        CnvUtfConverter class functionality test
@SYMTestPriority        Medium
@SYMTestActions        	Checking that error conditions yield appropriate error values
                        Tests exhaustively for length-testing UTF-8 2,3,4- byte Unicode character
						Tests for converting bad UTF-7 to Unicode
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
GLDEF_C TInt DoE32MainL()
	{
	TheTest.Start(_L(" @SYMTestCaseID:SYSLIB-CHARCONV-CT-0569 Checking that error conditions yield appropriate error values "));
	ExhaustivelyLengthTest(KNullDesC16, KNullDesC8, KNullDesC8);
	ExhaustivelyLengthTest(_L16("Hello!"), _L8("Hello+ACE-"), _L8("Hello!"), _L8("Hello!"));

	HBufC * unicodeHBuf = HBufC::NewLC(32);
    TPtr16 unicode = unicodeHBuf->Des();
    HBufC * generatedUnicodeHBuf = HBufC::NewLC(32);
    TPtr16 generatedUnicode = generatedUnicodeHBuf->Des();
    HBufC8 * utf8HBuf = HBufC8::NewLC(64);
    TPtr8 utf8 = utf8HBuf->Des();
    HBufC8 * generatedUtf8HBuf = HBufC8::NewLC(64);
    TPtr8 generatedUtf8 = generatedUtf8HBuf->Des();

	const TPtrC16 percentC_16=_L16("%c");
	const TPtrC16 percentCPercentC_16=_L16("%c%c");
	const TPtrC8 percentC_8=_L8("%c");
	const TPtrC8 percentCPercentC_8=_L8("%c%c");
	const TPtrC8 percentCPercentCPercentC_8=_L8("%c%c%c");
	const TPtrC8 percentCPercentCPercentCPercentC_8=_L8("%c%c%c%c");
	TInt state=CnvUtfConverter::KStateDefault;
	//
	TheTest.Next(_L("Exhaustively length-testing a UTF-8 2-byte Unicode character"));
	unicode.Format(_L16("%c"), 0x0635);
	utf8.Format(_L8("%c%c"), 0xd8, 0xb5);
	ExhaustivelyLengthTest(unicode, _L8("+BjU-"), utf8);
	TheTest.Next(_L("Exhaustively length-testing a UTF-8 3-byte Unicode character"));
	unicode.Format(_L16("%c"), 0x679e);
	utf8.Format(_L8("%c%c%c"), 0xe6, 0x9e, 0x9e);
	ExhaustivelyLengthTest(unicode, _L8("+Z54-"), utf8);
	TheTest.Next(_L("Exhaustively length-testing a UTF-8 4-byte Unicode surrogate-pair"));
	unicode.Format(_L16("%c%c"), 0xdb0d, 0xdcab);
	utf8.Format(_L8("%c%c%c%c"), 0xf3, 0x93, 0x92, 0xab);
	ExhaustivelyLengthTest(unicode, _L8("+2w3cqw-"), utf8);
	TheTest.Next(_L("Exhaustively length-testing a UTF-7 various strings"));
	unicode.Format(_L16("a%c"), 0x0105);
	utf8.Format(_L8("a%c%c"), 0xc4, 0x85);
	ExhaustivelyLengthTest(unicode, _L8("a+AQU-"), utf8);
	unicode.Format(_L16("b%c%c"), 0x0431, 0x0431);
	utf8.Format(_L8("b%c%c%c%c"), 0xd0, 0xb1, 0xd0, 0xb1);
	ExhaustivelyLengthTest(unicode, _L8("b+BDEEMQ-"), utf8);
	unicode.Format(_L16("c%c%c%c"), 0x05e6, 0x05e6, 0x05e6);
	utf8.Format(_L8("c%c%c%c%c%c%c"), 0xd7, 0xa6, 0xd7, 0xa6, 0xd7, 0xa6);
	ExhaustivelyLengthTest(unicode, _L8("c+BeYF5gXm-"), utf8);
	unicode.Format(_L16(" %c%c%c%c"), 0xd86a, 0xdfa7, 0xd9e3, 0xde08);
	utf8.Format(_L8(" %c%c%c%c%c%c%c%c"), 0xf0, 0xaa, 0xae, 0xa7, 0xf2, 0x88, 0xb8, 0x88);
	ExhaustivelyLengthTest(unicode, _L8(" +2Grfp9nj3gg-"), utf8);
	unicode.Format(_L16("%cd"), 0x0636);
	utf8.Format(_L8("%c%cd"), 0xd8, 0xb6);
	ExhaustivelyLengthTest(unicode, _L8("+BjY-d"), utf8);
	unicode.Format(_L16("%c%ce"), 0x090f, 0x090f);
	utf8.Format(_L8("%c%c%c%c%c%ce"), 0xe0, 0xa4, 0x8f, 0xe0, 0xa4, 0x8f);
	ExhaustivelyLengthTest(unicode, _L8("+CQ8JDw-e"), utf8);
	unicode.Format(_L16("%c%c%cf"), 0x6cd5, 0x6cd5, 0x6cd5);
	utf8.Format(_L8("%c%c%c%c%c%c%c%c%cf"), 0xe6, 0xb3, 0x95, 0xe6, 0xb3, 0x95, 0xe6, 0xb3, 0x95);
	ExhaustivelyLengthTest(unicode, _L8("+bNVs1WzV-f"), utf8);
	unicode.Format(_L16("%c%c%c%c "), 0xdbe9, 0xdcfe, 0xdb52, 0xddb4);
	utf8.Format(_L8("%c%c%c%c%c%c%c%c "), 0xf4, 0x8a, 0x93, 0xbe, 0xf3, 0xa4, 0xa6, 0xb4);
	ExhaustivelyLengthTest(unicode, _L8("+2+nc/ttS3bQ- "), utf8);
	TheTest.Next(_L("Converting to short UTF-7 descriptors"));
	LengthTestGeneratingUtf7();
	TheTest.Next(_L("Converting to short UTF-8 descriptors"));
	LengthTestGeneratingUtf8();
	{
	TheTest.Next(_L("Testing converting bad UTF-7 to Unicode"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+"), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8(")+"), state)==1);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==')');
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+ "), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+>"), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+-"), state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode==_L16("+"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+A"), state)==0);
	TEST(state!=CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(generatedUnicode.Length()==0);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+A "), state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode==_L16(" "));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+A-"), state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode.Length()==0);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+B"), state)==1);
	TEST(state!=CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(generatedUnicode.Length()==0);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+B "), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+B-"), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+AA"), state)==0);
	TEST(state!=CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(generatedUnicode.Length()==0);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+AA "), state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode==_L16(" "));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+AA-"), state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode.Length()==0);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+AB"), state)==2);
	TEST(state!=CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(generatedUnicode.Length()==0);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+AB "), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+AB-"), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+BA"), state)==2);
	TEST(state!=CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(generatedUnicode.Length()==0);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+BA "), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+BA-"), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+BB"), state)==2);
	TEST(state!=CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(generatedUnicode.Length()==0);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+BB "), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+BB-"), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnY"), state)==0);
	TEST(state!=CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0xb676);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnY "), state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode.Length()==2);
	TEST(generatedUnicode[0]==0xb676);
	TEST(generatedUnicode[1]==0x0020);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnY-"), state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0xb676);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnZ"), state)==3);
	TEST(state!=CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(generatedUnicode.Length()==0);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnZ "), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnZ-"), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tna"), state)==3);
	TEST(state!=CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(generatedUnicode.Length()==0);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tna "), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tna-"), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnb"), state)==3);
	TEST(state!=CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(generatedUnicode.Length()==0);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnb "), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnb-"), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnYA"), state)==0);
	TEST(state!=CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0xb676);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnYA "), state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode.Length()==2);
	TEST(generatedUnicode[0]==0xb676);
	TEST(generatedUnicode[1]==0x0020);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnYA-"), state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0xb676);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnYB"), state)==1);
	TEST(state!=CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0xb676);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnYB "), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnYB-"), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnZA"), state)==1);
	TEST(state!=CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0xb676);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnZA "), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnZA-"), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnZB"), state)==1);
	TEST(state!=CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0xb676);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnZB "), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnZB-"), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnYAA"), state)==0);
	TEST(state!=CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0xb676);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnYAA "), state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode.Length()==2);
	TEST(generatedUnicode[0]==0xb676);
	TEST(generatedUnicode[1]==0x0020);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnYAA-"), state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0xb676);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnYAB"), state)==2);
	TEST(state!=CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0xb676);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnYAB "), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnYAB-"), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnYBA"), state)==2);
	TEST(state!=CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0xb676);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnYBA "), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnYBA-"), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnYBB"), state)==2);
	TEST(state!=CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0xb676);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnYBB "), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnYBB-"), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnZAA"), state)==2);
	TEST(state!=CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0xb676);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnZAA "), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnZAA-"), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnZAB"), state)==2);
	TEST(state!=CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0xb676);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnZAB "), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnZAB-"), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnZBA"), state)==2);
	TEST(state!=CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0xb676);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnZBA "), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnZBA-"), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnZBB"), state)==2);
	TEST(state!=CnvUtfConverter::KStateDefault);
	state=CnvUtfConverter::KStateDefault;
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0xb676);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnZBB "), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+tnZBB-"), state)==CnvUtfConverter::EErrorIllFormedInput);
	TEST(state==CnvUtfConverter::KStateDefault);
	}
	{
	TheTest.Next(_L("Testing converting bad UTF-8 to Unicode"));
	utf8.Format(percentC_8, 0x80);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	utf8.Format(percentC_8, 0xbf);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	utf8.Format(percentC_8, 0xa1);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	utf8.Format(percentC_8, 0xc0);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	utf8.Format(percentCPercentC_8, '=', 0xc0);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	TEST(generatedUnicode.Length()==2);
	TEST(generatedUnicode[0]=='=');
	TEST(generatedUnicode[1]==0xFFFD);
	utf8.Format(percentCPercentC_8, 0xc0, 0x00);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	utf8.Format(percentCPercentC_8, 0xc0, 0x80);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	TEST(generatedUnicode.Length()==2);
	TEST(generatedUnicode[0]==0xFFFD);
	TEST(generatedUnicode[1]==0xFFFD);
	utf8.Format(percentC_8, 0xdf);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==CnvUtfConverter::EErrorIllFormedInput);
	utf8.Format(percentCPercentC_8, '*', 0xdf);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==1);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]=='*');
	utf8.Format(percentCPercentC_8, 0xdf, 0x7f);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	utf8.Format(percentCPercentC_8, 0xdf, 0xbf);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0x07ff);
	utf8.Format(percentC_8, 0xd7);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==CnvUtfConverter::EErrorIllFormedInput);
	utf8.Format(percentCPercentC_8, '\'', 0xd7);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==1);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]=='\'');
	utf8.Format(percentCPercentC_8, 0xd7, 0xd9);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==1);
	utf8.Format(percentCPercentC_8, 0xd7, 0x99);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0x05d9);
	utf8.Format(percentC_8, 0xe0);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==CnvUtfConverter::EErrorIllFormedInput);
	utf8.Format(percentCPercentC_8, '@', 0xe0);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==1);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]=='@');
	utf8.Format(percentCPercentC_8, 0xe0, 0x80);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==CnvUtfConverter::EErrorIllFormedInput);
	utf8.Format(percentCPercentCPercentC_8, ':', 0xe0, 0x80);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==2);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==':');
	utf8.Format(percentCPercentCPercentC_8, 0xe0, 0x80, 0x80);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	TEST(generatedUnicode.Length()==3);
	TEST(generatedUnicode[0]==0xfffd);
	TEST(generatedUnicode[1]==0xfffd);
	TEST(generatedUnicode[2]==0xfffd);
	utf8.Format(percentCPercentC_8, 0xef, 0x3f);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==CnvUtfConverter::EErrorIllFormedInput);
	utf8.Format(percentCPercentCPercentC_8, '~', 0xef, 0x3f);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==2);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]=='~');
	utf8.Format(percentCPercentCPercentC_8, 0xef, 0x3f, 0xbf);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	utf8.Format(percentCPercentC_8, 0xef, 0x7f);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==CnvUtfConverter::EErrorIllFormedInput);
	utf8.Format(percentCPercentCPercentC_8, 'L', 0xef, 0x7f);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==2);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]=='L');
	utf8.Format(percentCPercentCPercentC_8, 0xef, 0x7f, 0xbf);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	utf8.Format(percentCPercentC_8, 0xef, 0xff);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==CnvUtfConverter::EErrorIllFormedInput);
	utf8.Format(percentCPercentCPercentC_8, '^', 0xef, 0xff);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==2);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]=='^');
	utf8.Format(percentCPercentCPercentC_8, 0xef, 0xff, 0xbf);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	utf8.Format(percentCPercentCPercentC_8, 0xef, 0xbf, 0x3f);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	utf8.Format(percentCPercentCPercentC_8, 0xef, 0xbf, 0x7f);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	utf8.Format(percentCPercentCPercentC_8, 0xef, 0xbf, 0xff);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	utf8.Format(percentCPercentCPercentC_8, 0xef, 0xbf, 0xbf);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0xffff);
	utf8.Format(percentC_8, 0xf4);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==CnvUtfConverter::EErrorIllFormedInput);
	utf8.Format(percentCPercentC_8, ',', 0xf4);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==1);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==',');
	utf8.Format(percentCPercentC_8, 0xf4, 0x06);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==CnvUtfConverter::EErrorIllFormedInput);
	utf8.Format(percentCPercentCPercentC_8, 'J', 0xf4, 0x06);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==2);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]=='J');
	utf8.Format(percentCPercentCPercentC_8, 0xf4, 0x06, 0xab);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==CnvUtfConverter::EErrorIllFormedInput);
	utf8.Format(percentCPercentCPercentCPercentC_8, ']', 0xf4, 0x06, 0xab);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==3);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==']');
	utf8.Format(percentCPercentCPercentCPercentC_8, 0xf4, 0x06, 0xab, 0x9c);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	utf8.Format(percentCPercentC_8, 0xf4, 0x46);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==CnvUtfConverter::EErrorIllFormedInput);
	utf8.Format(percentCPercentCPercentC_8, 'o', 0xf4, 0x46);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==2);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]=='o');
	utf8.Format(percentCPercentCPercentC_8, 0xf4, 0x46, 0xab);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==CnvUtfConverter::EErrorIllFormedInput);
	utf8.Format(percentCPercentCPercentCPercentC_8, '!', 0xf4, 0x46, 0xab);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==3);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]=='!');
	utf8.Format(percentCPercentCPercentCPercentC_8, 0xf4, 0x46, 0xab, 0x9c);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	utf8.Format(percentCPercentC_8, 0xf4, 0xc6);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==CnvUtfConverter::EErrorIllFormedInput);
	utf8.Format(percentCPercentCPercentC_8, 'm', 0xf4, 0xc6);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==2);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]=='m');
	utf8.Format(percentCPercentCPercentC_8, 0xf4, 0xc6, 0xab);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==CnvUtfConverter::EErrorIllFormedInput);
	utf8.Format(percentCPercentCPercentCPercentC_8, '&', 0xf4, 0xc6, 0xab);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==3);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]=='&');
	utf8.Format(percentCPercentCPercentCPercentC_8, 0xf4, 0xc6, 0xab, 0x9c);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	utf8.Format(percentCPercentCPercentC_8, 0xf4, 0x86, 0x2b);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==CnvUtfConverter::EErrorIllFormedInput);
	utf8.Format(percentCPercentCPercentCPercentC_8, 'v', 0xf4, 0x86, 0x2b);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==3);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]=='v');
	utf8.Format(percentCPercentCPercentCPercentC_8, 0xf4, 0x86, 0x2b, 0x9c);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	utf8.Format(percentCPercentCPercentC_8, 0xf4, 0x86, 0x6b);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==CnvUtfConverter::EErrorIllFormedInput);
	utf8.Format(percentCPercentCPercentCPercentC_8, 'Q', 0xf4, 0x86, 0x6b);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==3);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]=='Q');
	utf8.Format(percentCPercentCPercentCPercentC_8, 0xf4, 0x86, 0x6b, 0x9c);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	utf8.Format(percentCPercentCPercentC_8, 0xf4, 0x86, 0xeb);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==CnvUtfConverter::EErrorIllFormedInput);
	utf8.Format(percentCPercentCPercentCPercentC_8, '?', 0xf4, 0x86, 0xeb);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==3);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]=='?');
	utf8.Format(percentCPercentCPercentCPercentC_8, 0xf4, 0x86, 0xeb, 0x9c);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==2);
	utf8.Format(percentCPercentCPercentCPercentC_8, 0xf4, 0x86, 0xab, 0x1c);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	utf8.Format(percentCPercentCPercentCPercentC_8, 0xf4, 0x86, 0xab, 0x5c);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	utf8.Format(percentCPercentCPercentCPercentC_8, 0xf4, 0x86, 0xab, 0xdc);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==1);
	utf8.Format(percentCPercentCPercentCPercentC_8, 0xf4, 0x86, 0xab, 0x9c);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	TEST(generatedUnicode.Length()==2);
	TEST(generatedUnicode[0]==0xdbda);
	TEST(generatedUnicode[1]==0xdedc);

	// Additional tests added for INC117111...

	utf8.Format(_L8("%c%c%c%c"), 0xf4, 0xc6, 0xab, 0x9c);     // Invalid 4 bit
	TInt returnval = CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8);
	TEST(generatedUnicode.Length()==3);
	TEST(generatedUnicode[0]==0xFFFD);
	TEST(generatedUnicode[1]==0x01AB);
	TEST(generatedUnicode[2]==0xFFFD);

	unicode.Format(percentCPercentC_16, 0xd800, 0xdc00); // a surrogate pair
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);

	TEST(generatedUtf8==_L8("\xf0\x90\x80\x80")); // round trip test
	returnval = CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8);
	TEST(generatedUnicode.Length()==2);
	TEST(generatedUnicode[0]==0xd800);
	TEST(generatedUnicode[1]==0xdc00);

	unicode.Format(percentCPercentC_16, 0xd7ff, 0xdfff);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xed\x9f\xbf\xed\xbf\xbf"));

	utf8.Format(_L8("%c"), 0xc0); // An invalid char.
	returnval = CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8);
	TEST(generatedUnicode.Length()==1);
	TEST(generatedUnicode[0]==0xFFFD);

	utf8.Format(_L8("%c%c%c%c%c"), 0xf4, 0x20, 0x01, 0x02, 0x10); // Invalid 4 bit and a ASCI
	returnval = CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8);
	TEST(generatedUnicode.Length()==5);
	TEST(generatedUnicode[0]==0xFFFD);
	TEST(generatedUnicode[1]==0x0020);
	TEST(generatedUnicode[2]==0x0001);
	TEST(generatedUnicode[3]==0x0002);
	TEST(generatedUnicode[4]==0x0010);

	utf8.Format(_L8("%c%c%c%c"), 0xed, 0xa0, 0x80, 0x10);		// Invalid 3 bit and a ASCI
	returnval = CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8);
	TEST(generatedUnicode.Length()==4);
	TEST(generatedUnicode[0]==0xFFFD);
	TEST(generatedUnicode[1]==0xFFFD);
	TEST(generatedUnicode[2]==0xFFFD);
	TEST(generatedUnicode[3]==0x0010);

	utf8.Format(_L8("%c%c%c%c%c"), 0xf4, 0x81, 0x81, 0x81, 0x10);     // Valid 4 bit and a ASCI
	returnval = CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8);
	TEST(generatedUnicode.Length()==3);
	TEST(generatedUnicode[0]==0xdbc4);
	TEST(generatedUnicode[1]==0xdc41);
	TEST(generatedUnicode[2]==0x0010);

	utf8.Format(_L8("%c%c%c%c%c"), 0xf4, 0xc6, 0xab, 0x9c, 0x10);     // Invalid 4 bit and a ASCI
	returnval = CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8);
	TEST(generatedUnicode.Length()==4);
	TEST(generatedUnicode[0]==0xFFFD);
	TEST(generatedUnicode[1]==0x01AB);
	TEST(generatedUnicode[2]==0xFFFD);
	TEST(generatedUnicode[3]==0x0010);

	utf8.Format(_L8("%c%c%c%c%c"), 0xf4, 0x8c, 0x81, 0x81, 0x10);     // Valid 4 bit and a ASCI
	returnval = CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8);

	//INC044750
	utf8.Format(_L8("%c%c%c%c%c"),0x3C, 0xFC, 0xDC, 0x3C,0x3C);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	TEST(generatedUnicode==_L("<\xFFFD\xFFFD<<"));
	}
	TheTest.Next(_L("Testing bad uuuuu (wwww+1) bits in 4-byte UTF-8"));
	utf8.Format(percentCPercentCPercentCPercentC_8, 0xf4, 0x96, 0xab, 0x9c);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	utf8.Format(percentCPercentCPercentCPercentC_8, 0xf0, 0x86, 0xab, 0x9c);
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8)==0);
	{
	TheTest.Next(_L("Testing converting bad Unicode surrogate-pairs to UTF-8"));
	unicode.Format(percentC_16, 0xd800);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==CnvUtfConverter::EErrorIllFormedInput);
	unicode.Format(percentCPercentC_16, '>', 0xd800);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==1);
	TEST(generatedUtf8.Length()==1);
	TEST(generatedUtf8[0]=='>');
	unicode.Format(percentC_16, 0xdbff);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==CnvUtfConverter::EErrorIllFormedInput);
	unicode.Format(percentCPercentC_16, 'Z', 0xdbff);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==1);
	TEST(generatedUtf8.Length()==1);
	TEST(generatedUtf8[0]=='Z');
	unicode.Format(percentC_16, 0xdaaa);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==CnvUtfConverter::EErrorIllFormedInput);
	unicode.Format(percentCPercentC_16, '|', 0xdaaa);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==1);
	TEST(generatedUtf8.Length()==1);
	TEST(generatedUtf8[0]=='|');
	unicode.Format(percentC_16, 0xd7ff);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xed\x9f\xbf"));
	unicode.Format(percentC_16, 0xdc00);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xed\xb0\x80"));
	unicode.Format(percentCPercentC_16, 0xd800, 0xe000);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==CnvUtfConverter::EErrorIllFormedInput);
	unicode.Format(percentCPercentC_16, 0xdbff, 0xe000);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==CnvUtfConverter::EErrorIllFormedInput);
	unicode.Format(percentCPercentC_16, 0xdaaa, 0xe000);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==CnvUtfConverter::EErrorIllFormedInput);
	unicode.Format(percentCPercentC_16, 0xd7ff, 0xe000);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xed\x9f\xbf\xee\x80\x80"));
	unicode.Format(percentCPercentC_16, 0xdc00, 0xe000);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xed\xb0\x80\xee\x80\x80"));
	unicode.Format(percentCPercentC_16, 0xd800, 0xdbff);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==CnvUtfConverter::EErrorIllFormedInput);
	unicode.Format(percentCPercentC_16, 0xdbff, 0xdbff);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==CnvUtfConverter::EErrorIllFormedInput);
	unicode.Format(percentCPercentC_16, 0xdaaa, 0xdbff);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==CnvUtfConverter::EErrorIllFormedInput);
	unicode.Format(percentCPercentC_16, 0xd7ff, 0xdbff);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==1);
	TEST(generatedUtf8==_L8("\xed\x9f\xbf"));
	unicode.Format(percentCPercentC_16, 0xdc00, 0xdbff);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==1);
	TEST(generatedUtf8==_L8("\xed\xb0\x80"));
	unicode.Format(percentCPercentC_16, 0xd800, 0xd7ff);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==CnvUtfConverter::EErrorIllFormedInput);
	unicode.Format(percentCPercentC_16, 0xdbff, 0xd7ff);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==CnvUtfConverter::EErrorIllFormedInput);
	unicode.Format(percentCPercentC_16, 0xdaaa, 0xd7ff);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==CnvUtfConverter::EErrorIllFormedInput);
	unicode.Format(percentCPercentC_16, 0xd7ff, 0xd7ff);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xed\x9f\xbf\xed\x9f\xbf"));
	unicode.Format(percentCPercentC_16, 0xdc00, 0xd7ff);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xed\xb0\x80\xed\x9f\xbf"));
	unicode.Format(percentCPercentC_16, 0xd800, 0xdfff);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xf0\x90\x8f\xbf"));
	unicode.Format(percentCPercentC_16, 0xdbff, 0xdfff);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xf4\x8f\xbf\xbf"));
	unicode.Format(percentCPercentC_16, 0xdaaa, 0xdfff);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xf2\xba\xaf\xbf"));
	unicode.Format(percentCPercentC_16, 0xd7ff, 0xdfff);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xed\x9f\xbf\xed\xbf\xbf"));
	unicode.Format(percentCPercentC_16, 0xdc00, 0xdfff);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xed\xb0\x80\xed\xbf\xbf"));
	unicode.Format(percentCPercentC_16, 0xd800, 0xdc00);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xf0\x90\x80\x80"));
	unicode.Format(percentCPercentC_16, 0xdbff, 0xdc00);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xf4\x8f\xb0\x80"));
	unicode.Format(percentCPercentC_16, 0xdaaa, 0xdc00);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xf2\xba\xa0\x80"));
	unicode.Format(percentCPercentC_16, 0xd7ff, 0xdc00);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xed\x9f\xbf\xed\xb0\x80"));
	unicode.Format(percentCPercentC_16, 0xdc00, 0xdc00);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xed\xb0\x80\xed\xb0\x80"));
	unicode.Format(percentCPercentC_16, 0xd800, 0xde37);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xf0\x90\x88\xb7"));
	unicode.Format(percentCPercentC_16, 0xdbff, 0xde37);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xf4\x8f\xb8\xb7"));
	unicode.Format(percentCPercentC_16, 0xdaaa, 0xde37);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xf2\xba\xa8\xb7"));
	unicode.Format(percentCPercentC_16, 0xd7ff, 0xde37);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xed\x9f\xbf\xed\xb8\xb7"));
	unicode.Format(percentCPercentC_16, 0xdc00, 0xde37);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xed\xb0\x80\xed\xb8\xb7"));
	}
	TUint i;
	for (i=0; i<=0x1f; ++i)
		{
		utf8.Format(_L8("%c%c\x99\xb1"), 0xf0|(i>>2), 0x85|((i&0x03)<<4));
		const TInt returnValue=CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8);
		if ((i<1) || ((i-1)&~0x0f))
			{
			TEST(returnValue==0);
			}
		else
			{
			TEST(returnValue==0);
			TEST(generatedUnicode.Length()==2);
			TEST((0xd815&~((i-1)<<6))==0xd815); // sanity check ((i-1)<<6)
			TEST(generatedUnicode[0]==(0xd815|((i-1)<<6)));
			TEST(generatedUnicode[1]==0xde71);
			}
		}
	for (i=0; i<=0x1f; ++i)
		{
		utf8.Format(_L8("%c%c\x80\x80"), 0xf0|(i>>2), 0x80|((i&0x03)<<4));
		const TInt returnValue=CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, utf8);
		if ((i<1) || ((i-1)&~0x0f))
			{
			TEST(returnValue==0);
			}
		else
			{
			TEST(returnValue==0);
			TEST(generatedUnicode.Length()==2);
			TEST((0xd800&~((i-1)<<6))==0xd800); // sanity check ((i-1)<<6)
			TEST(generatedUnicode[0]==(0xd800|((i-1)<<6)));
			TEST(generatedUnicode[1]==0xdc00);
			}
		}
	TheTest.Next(_L("Testing passing in descriptors that are empty and have NULL pointers"));
	enum {EBufferLength8=32};
	TUint8 buffer8[EBufferLength8];
	TPtr8 null8(NULL, 0, 0);
	TPtr8 trash8(REINTERPRET_CAST(TUint8*, 1), 0, 0);
	TPtr8 empty8(buffer8, 0, EBufferLength8);
	TPtr8 nonEmpty8(buffer8, 0, EBufferLength8);
	enum {EBufferLength16=16};
	TUint16 buffer16[EBufferLength16];
	TPtr16 null16(NULL, 0, 0);
	TPtr16 trash16(REINTERPRET_CAST(TUint16*, 2), 0, 0);
	TPtr16 empty16(buffer16, 0, EBufferLength16);
	TPtr16 nonEmpty16(buffer16, 0, EBufferLength16);
	for (i=0; ; ++i)
		{
		const TUint j=i/4;
		const TUint k=j/4;
		TDes8& descriptor8=(i%4==0)? null8: (i%4==1)? trash8: (i%4==2)? empty8: nonEmpty8;
		TDes16& descriptor16=(j%4==0)? null16: (j%4==1)? trash16: (j%4==2)? empty16: nonEmpty16;
		ResetDescriptorsForNullTest(empty8, empty16, nonEmpty8, nonEmpty16);
		const TBool inCompleteConversion8=((descriptor8.MaxLength()==0) && (descriptor16.Length()>0));
		const TBool inCompleteConversion16=((descriptor16.MaxLength()==0) && (descriptor8.Length()>0));
		TInt returnValue;
		returnValue=CnvUtfConverter::ConvertFromUnicodeToUtf7(descriptor8, descriptor16, k&0x1);
		TEST(inCompleteConversion8? (returnValue>0): (returnValue==0));
		ResetDescriptorsForNullTest(empty8, empty16, nonEmpty8, nonEmpty16);
		returnValue=CnvUtfConverter::ConvertFromUnicodeToUtf8(descriptor8, descriptor16);
		TEST(inCompleteConversion8? (returnValue>0): (returnValue==0));
		ResetDescriptorsForNullTest(empty8, empty16, nonEmpty8, nonEmpty16);
		state=CnvUtfConverter::KStateDefault;
		returnValue=CnvUtfConverter::ConvertToUnicodeFromUtf7(descriptor16, descriptor8, state);
		TEST(inCompleteConversion16? (returnValue>0): (returnValue==0));
		TEST(inCompleteConversion16 || (state==CnvUtfConverter::KStateDefault));
		ResetDescriptorsForNullTest(empty8, empty16, nonEmpty8, nonEmpty16);
		returnValue=CnvUtfConverter::ConvertToUnicodeFromUtf8(descriptor16, descriptor8);
		TEST(inCompleteConversion16? (returnValue>0): (returnValue==0));
		if (k&0x2)
			{
			break;
			}
		}
	state=CnvUtfConverter::KStateDefault; // in case any more tests are added below

	// Pop and destroy: unicodeHBuf, generatedUnicode, utf8, generatedUtf8
	CleanupStack::PopAndDestroy(4);
	return KErrNone;
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
