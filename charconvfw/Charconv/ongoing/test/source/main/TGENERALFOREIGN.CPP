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

RTest TheTest(_L("TGeneralForeign"));
	
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

const TUint KTibetanCharacter=0x0f65;
/**
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0498
@SYMTestCaseDesc        Tests for CCnvCharacterSetConverter::ConvertToUnicode(),
                        CCnvCharacterSetConverter::ConvertFromUnicode() functions
@SYMTestPriority        Medium
@SYMTestActions         Tests for converting various character sets to Unicode and from Unicode back to original character set.
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
	TheTest.Printf(_L("No of CharacterSets available:%d\n"),sizeof(arrayOfCharacterSetsAvailable ));

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
	TPtrC8 originalForeign;
	
	HBufC * originalUnicodeHBuf = HBufC::NewLC(128);
	TPtr16 originalUnicode = originalUnicodeHBuf->Des();

	HBufC * generatedUnicodeHBuf = HBufC::NewLC(128);
	TPtr16 generatedUnicode = generatedUnicodeHBuf->Des();

	HBufC * expectedUnicodeHBuf = HBufC::NewLC(128);
	TPtr16 expectedUnicode = expectedUnicodeHBuf->Des();
	
	HBufC8 * generatedForeignHBuf = HBufC8::NewLC(128);
	TPtr8 generatedForeign = generatedForeignHBuf->Des(); 
	
	TInt state=CCnvCharacterSetConverter::KStateDefault;

	TheTest.Start(_L("Big-5"));
	characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierBig5, *arrayOfCharacterSetsAvailable, fileServerSession);
	originalForeign.Set(_L8("\xa2\xaf\xa1\x40\xc7\xcd\xc7\xce\xc7\xcfk\xa3\x7e"));
	expectedUnicode.Format(_L16("%c%c%c%c%ck%c"), 0xff10, 0x3000, 0x0435, 0x0451, 0x0436, 0x310f);
	TEST(characterSetConverter->ConvertToUnicode(generatedUnicode, originalForeign, state)==0);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, generatedUnicode)==0);
	TEST(generatedForeign==originalForeign);

	TheTest.Next(_L("GB-12345-90"));
	characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierGb12345, *arrayOfCharacterSetsAvailable, fileServerSession);
	originalForeign.Set(_L8("\xa2\xd2i\xa1\xa6\xa2\xfc\xa3\xa1\xa3\xa2\xa3\xa3\xa3\xa4\xa3\xa5\xef\xfd\xef\xfe\xf0\xa1\xf0\xa2"));
	expectedUnicode.Format(_L16("%ci%c%c%c%c%c%c%c%c%c%c%c"), 0x2481, 0x02c7, 0x216b, 0xff01, 0xff02, 0xff03, 0xffe5, 0xff05, 0x7a1e, 0x7a14, 0x7a39, 0x7a37);
	TEST(characterSetConverter->ConvertToUnicode(generatedUnicode, originalForeign, state)==0);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, generatedUnicode)==0);
	TEST(generatedForeign==originalForeign);

	TheTest.Next(_L("GB-2312-80"));
	characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierGb2312, *arrayOfCharacterSetsAvailable, fileServerSession);
	originalForeign.Set(_L8("4\x27\x26\x27\x27\x27\x28\x29\x6e\x29\x6f\x30\x21\x30\x22\x77\x7e"));
	expectedUnicode.Format(_L16("4%c%c%c%c%c%c%c%c"), 0x0415, 0x0401, 0x0416, 0x254a, 0x254b, 0x554a, 0x963f, 0x9f44);
	TEST(characterSetConverter->ConvertToUnicode(generatedUnicode, originalForeign, state)==0);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, generatedUnicode)==0);
	TEST(generatedForeign==originalForeign);

	TheTest.Next(_L("GBK"));
	characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierGbk, *arrayOfCharacterSetsAvailable, fileServerSession);
	originalForeign.Set(_L8("\xf7\xfd\xf7\xfe\xf8\x40\xf8\x41\xa6\xea\xa6\xeb\xa6\xee\xa6\xef\xa9\x88\xa9\x96\xfe\x4f:"));
	expectedUnicode.Format(_L16("%c%c%c%c%c%c%c%c%c%c%c:"), 0x9f3e, 0x9f44, 0x9ce3, 0x9ce4, 0xfe43, 0xfe44, 0xfe3b, 0xfe3c, 0xfe6b, 0x3007, 0xfa29);
	TEST(characterSetConverter->ConvertToUnicode(generatedUnicode, originalForeign, state)==0);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, generatedUnicode)==0);
	TEST(generatedForeign==originalForeign);

	TheTest.Next(_L("JIS X 0208"));
	characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierShiftJis, *arrayOfCharacterSetsAvailable, fileServerSession);
	originalForeign.Set(_L8("\x81\xf6\x81\xf7\x81\xfc\x82\x4f\x82\x50+\x81\x40\xa1\xdf\xea\xa4"));
	expectedUnicode.Format(_L16("%c%c%c%c%c+%c%c"), 0x2021, 0x00b6, 0x25ef, 0xff10, 0xff11, 0x3000, 0xff61, 0xff9f, 0x7199);
	TEST(characterSetConverter->ConvertToUnicode(generatedUnicode, originalForeign, state)==0);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, generatedUnicode)==0);
	TEST(generatedForeign==originalForeign);

	TheTest.Next(_L("JIS X 0212"));
	characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierEucJpPacked, *arrayOfCharacterSetsAvailable, fileServerSession);
	originalForeign.Set(_L8("\x8f\xa9\xaf\x8e\xcd\x8f\xa9\xb0\xed\xe3\x8f\xa9\xc1&\x8f\xa9\xc2\x8f\xed\xe3\x8f\xd5\xb7\x8f\xa2\xaf\x8f\xa2\xb3"));
	expectedUnicode.Format(_L16("%c%c%c%c%c&%c%c%c%c%c"), 0x0166, 0xff8d, 0x00de, 0x8f9c, 0x00e6, 0x0111, 0x9fa5, 0x7fc3, 0x02d8, 0x02dd);
	TEST(characterSetConverter->ConvertToUnicode(generatedUnicode, originalForeign, state)==0);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, generatedUnicode)==0);
	TEST(generatedForeign==originalForeign);
	TheTest.Next(_L("Testing unconvertible characters"));
	TInt numberOfUnconvertibleCharacters;
	TInt indexOfFirstUnconvertibleCharacter;
	CCnvCharacterSetConverter::TArrayOfAscendingIndices indicesOfUnconvertibleCharacters;
	originalUnicode.Format(_L16("%c"), KTibetanCharacter);
	characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierIso2022Jp, *arrayOfCharacterSetsAvailable, fileServerSession);
	TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, originalUnicode)==0);
	TEST(generatedForeign==_L8("\x1b\x24\x42\x21\x29"));
	characterSetConverter->SetReplacementForUnconvertibleUnicodeCharactersL(_L8("amb"));
	TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, originalUnicode)==0);
	TEST(generatedForeign==_L8("amb"));
	TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, originalUnicode)==0);
	TEST(generatedForeign==_L8("amb"));
	characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierAscii, *arrayOfCharacterSetsAvailable, fileServerSession);
	characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierIso2022Jp, *arrayOfCharacterSetsAvailable, fileServerSession);
	TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, originalUnicode)==0);
	TEST(generatedForeign==_L8("\x1b\x24\x42\x21\x29"));
	TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, originalUnicode, numberOfUnconvertibleCharacters)==0);
	TEST(generatedForeign==_L8("\x1b\x24\x42\x21\x29"));
	TEST(numberOfUnconvertibleCharacters==1);
	TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, originalUnicode, numberOfUnconvertibleCharacters, indexOfFirstUnconvertibleCharacter)==0);
	TEST(generatedForeign==_L8("\x1b\x24\x42\x21\x29"));
	TEST(numberOfUnconvertibleCharacters==1);
	TEST(indexOfFirstUnconvertibleCharacter==0);
	TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, originalUnicode, indicesOfUnconvertibleCharacters)==0);
	TEST(generatedForeign==_L8("\x1b\x24\x42\x21\x29"));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==1);
	TEST(indicesOfUnconvertibleCharacters[0]==0);
	indicesOfUnconvertibleCharacters.RemoveAll();
	characterSetConverter->SetReplacementForUnconvertibleUnicodeCharactersL(_L8("amb"));
	TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, originalUnicode, numberOfUnconvertibleCharacters)==0);
	TEST(generatedForeign==_L8("amb"));
	TEST(numberOfUnconvertibleCharacters==1);
	TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, originalUnicode, numberOfUnconvertibleCharacters, indexOfFirstUnconvertibleCharacter)==0);
	TEST(generatedForeign==_L8("amb"));
	TEST(numberOfUnconvertibleCharacters==1);
	TEST(indexOfFirstUnconvertibleCharacter==0);
	TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, originalUnicode, indicesOfUnconvertibleCharacters)==0);
	TEST(generatedForeign==_L8("amb"));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==1);
	TEST(indicesOfUnconvertibleCharacters[0]==0);
	indicesOfUnconvertibleCharacters.RemoveAll();
	TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, _L16("amb"), numberOfUnconvertibleCharacters)==0);
	TEST(generatedForeign==_L8("amb"));
	TEST(numberOfUnconvertibleCharacters==0);
	TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, _L16("amb"), numberOfUnconvertibleCharacters, indexOfFirstUnconvertibleCharacter)==0);
	TEST(generatedForeign==_L8("amb"));
	TEST(numberOfUnconvertibleCharacters==0);
	TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, _L16("amb"), indicesOfUnconvertibleCharacters)==0);
	TEST(generatedForeign==_L8("amb"));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==0);
	indicesOfUnconvertibleCharacters.RemoveAll();
	originalUnicode.Format(_L16("Red, %cer, green. Je voudrais du j%con."), KTibetanCharacter, KTibetanCharacter);
	TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, originalUnicode, indicesOfUnconvertibleCharacters)==0);
    TEST(generatedForeign==_L8("Red, amb""er, green. Je voudrais du jambon."));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==2);
	TEST(indicesOfUnconvertibleCharacters[0]==5);
	TEST(indicesOfUnconvertibleCharacters[1]==33);
	indicesOfUnconvertibleCharacters.RemoveAll();
	originalUnicode.Format(_L16("Red, amber, green%c Je voudrais du jambon%c"), KTibetanCharacter, KTibetanCharacter);
	characterSetConverter->SetReplacementForUnconvertibleUnicodeCharactersL(_L8("."));
	TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, originalUnicode, indicesOfUnconvertibleCharacters)==0);
	TEST(generatedForeign==_L8("Red, amber, green. Je voudrais du jambon."));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==2);
	TEST(indicesOfUnconvertibleCharacters[0]==17);
	TEST(indicesOfUnconvertibleCharacters[1]==40);
	indicesOfUnconvertibleCharacters.RemoveAll();
	originalUnicode.Format(_L16("%ced, amber, green. Je voudrais du jambon."), KTibetanCharacter);
	characterSetConverter->SetReplacementForUnconvertibleUnicodeCharactersL(_L8("R"));
	TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, originalUnicode, indicesOfUnconvertibleCharacters)==0);
	TEST(generatedForeign==_L8("R""ed, amber, green. Je voudrais du jambon."));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==1);
	TEST(indicesOfUnconvertibleCharacters[0]==0);
	indicesOfUnconvertibleCharacters.RemoveAll();
	characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierGb2312, *arrayOfCharacterSetsAvailable, fileServerSession);
	characterSetConverter->SetReplacementForUnconvertibleUnicodeCharactersL(_L8("e"));
	originalUnicode.Format(_L16("R%cd, amb%cr, gr%c%cn. J%c voudrais du jambon."), KTibetanCharacter, KTibetanCharacter, KTibetanCharacter, KTibetanCharacter, KTibetanCharacter);
	TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, originalUnicode, indicesOfUnconvertibleCharacters)==0);
	TEST(generatedForeign==_L8("Red, amber, green. Je voudrais du jambon."));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==5);
	TEST(indicesOfUnconvertibleCharacters[0]==1);
	TEST(indicesOfUnconvertibleCharacters[1]==8);
	TEST(indicesOfUnconvertibleCharacters[2]==14);
	TEST(indicesOfUnconvertibleCharacters[3]==15);
	TEST(indicesOfUnconvertibleCharacters[4]==20);
	indicesOfUnconvertibleCharacters.RemoveAll();
	originalUnicode.Format(_L16("Red, amber, green%c Je voudrais du jambon%c"), KTibetanCharacter, KTibetanCharacter);
	characterSetConverter->SetReplacementForUnconvertibleUnicodeCharactersL(_L8("."));
	TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, originalUnicode, indicesOfUnconvertibleCharacters)==0);
	TEST(generatedForeign==_L8("Red, amber, green. Je voudrais du jambon."));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==2);
	TEST(indicesOfUnconvertibleCharacters[0]==17);
	TEST(indicesOfUnconvertibleCharacters[1]==40);
	indicesOfUnconvertibleCharacters.RemoveAll();
	originalUnicode.Format(_L16("%ced, amber, green. Je voudrais du jambon."), KTibetanCharacter);
	characterSetConverter->SetReplacementForUnconvertibleUnicodeCharactersL(_L8("R"));
	TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, originalUnicode, indicesOfUnconvertibleCharacters)==0);
	TEST(generatedForeign==_L8("Red, amber, green. Je voudrais du jambon."));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==1);
	TEST(indicesOfUnconvertibleCharacters[0]==0);
	indicesOfUnconvertibleCharacters.RemoveAll();
	TUint8* const foreignBuffer=CONST_CAST(TUint8*, generatedForeign.Ptr());
	TPtr8 shortForeignOutputBuffer(NULL, 0, 0);
	characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierJis, *arrayOfCharacterSetsAvailable, fileServerSession);
	originalUnicode.Format(_L16("%c%c%c%c%cT%c%c%c%c"), KTibetanCharacter, 0x7a83, KTibetanCharacter, 0xff78, KTibetanCharacter, KTibetanCharacter, KTibetanCharacter, 0x68e5, KTibetanCharacter);
	_LIT8(KLit8ExpectedJis_1, "\x1b\x24\x42\x21\x29\x1b\x24\x42\x40\x60\x1b\x24\x42\x21\x29\x1b\x28\x49\x38\x1b\x24\x42\x21\x29\x1b\x28\x4aT\x1b\x24\x42\x21\x29\x1b\x24\x42\x21\x29\x1b\x24\x28\x44\x44\x28\x1b\x24\x42\x21\x29");
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 49);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==0);
	TEST(shortForeignOutputBuffer==KLit8ExpectedJis_1);
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==6);
	TEST(indicesOfUnconvertibleCharacters[0]==0);
	TEST(indicesOfUnconvertibleCharacters[1]==2);
	TEST(indicesOfUnconvertibleCharacters[2]==4);
	TEST(indicesOfUnconvertibleCharacters[3]==6);
	TEST(indicesOfUnconvertibleCharacters[4]==7);
	TEST(indicesOfUnconvertibleCharacters[5]==9);
	indicesOfUnconvertibleCharacters.RemoveAll();
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 48);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==1);
	TEST(shortForeignOutputBuffer==KLit8ExpectedJis_1().Left(44));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==5);
	TEST(indicesOfUnconvertibleCharacters[0]==0);
	TEST(indicesOfUnconvertibleCharacters[1]==2);
	TEST(indicesOfUnconvertibleCharacters[2]==4);
	TEST(indicesOfUnconvertibleCharacters[3]==6);
	TEST(indicesOfUnconvertibleCharacters[4]==7);
	indicesOfUnconvertibleCharacters.RemoveAll();
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 37);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==3);
	TEST(shortForeignOutputBuffer==KLit8ExpectedJis_1().Left(33));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==4);
	TEST(indicesOfUnconvertibleCharacters[0]==0);
	TEST(indicesOfUnconvertibleCharacters[1]==2);
	TEST(indicesOfUnconvertibleCharacters[2]==4);
	TEST(indicesOfUnconvertibleCharacters[3]==6);
	indicesOfUnconvertibleCharacters.RemoveAll();
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 32);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==4);
	TEST(shortForeignOutputBuffer==KLit8ExpectedJis_1().Left(28));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==3);
	TEST(indicesOfUnconvertibleCharacters[0]==0);
	TEST(indicesOfUnconvertibleCharacters[1]==2);
	TEST(indicesOfUnconvertibleCharacters[2]==4);
	indicesOfUnconvertibleCharacters.RemoveAll();
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 23);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==6);
	TEST(shortForeignOutputBuffer==KLit8ExpectedJis_1().Left(19));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==2);
	TEST(indicesOfUnconvertibleCharacters[0]==0);
	TEST(indicesOfUnconvertibleCharacters[1]==2);
	indicesOfUnconvertibleCharacters.RemoveAll();
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 14);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==8);
	TEST(shortForeignOutputBuffer==KLit8ExpectedJis_1().Left(10));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==1);
	TEST(indicesOfUnconvertibleCharacters[0]==0);
	indicesOfUnconvertibleCharacters.RemoveAll();
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 4);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==10);
	TEST(shortForeignOutputBuffer==KNullDesC8);
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==0);
	indicesOfUnconvertibleCharacters.RemoveAll();
	characterSetConverter->SetReplacementForUnconvertibleUnicodeCharactersL(_L8("\x1b\x28\x42_"));
	_LIT8(KLit8ExpectedJis_2, "\x1b\x28\x42_\x1b\x24\x42\x40\x60\x1b\x28\x42_\x1b\x28\x49\x38\x1b\x28\x42_\x1b\x28\x4aT\x1b\x28\x42_\x1b\x28\x42_\x1b\x24\x28\x44\x44\x28\x1b\x28\x42_");
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 43);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==0);
	TEST(shortForeignOutputBuffer==KLit8ExpectedJis_2);
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==6);
	TEST(indicesOfUnconvertibleCharacters[0]==0);
	TEST(indicesOfUnconvertibleCharacters[1]==2);
	TEST(indicesOfUnconvertibleCharacters[2]==4);
	TEST(indicesOfUnconvertibleCharacters[3]==6);
	TEST(indicesOfUnconvertibleCharacters[4]==7);
	TEST(indicesOfUnconvertibleCharacters[5]==9);
	indicesOfUnconvertibleCharacters.RemoveAll();
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 42);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==1);
	TEST(shortForeignOutputBuffer==KLit8ExpectedJis_2().Left(39));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==5);
	TEST(indicesOfUnconvertibleCharacters[0]==0);
	TEST(indicesOfUnconvertibleCharacters[1]==2);
	TEST(indicesOfUnconvertibleCharacters[2]==4);
	TEST(indicesOfUnconvertibleCharacters[3]==6);
	TEST(indicesOfUnconvertibleCharacters[4]==7);
	indicesOfUnconvertibleCharacters.RemoveAll();
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 32);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==3);
	TEST(shortForeignOutputBuffer==KLit8ExpectedJis_2().Left(29));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==4);
	TEST(indicesOfUnconvertibleCharacters[0]==0);
	TEST(indicesOfUnconvertibleCharacters[1]==2);
	TEST(indicesOfUnconvertibleCharacters[2]==4);
	TEST(indicesOfUnconvertibleCharacters[3]==6);
	indicesOfUnconvertibleCharacters.RemoveAll();
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 28);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==4);
	TEST(shortForeignOutputBuffer==KLit8ExpectedJis_2().Left(25));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==3);
	TEST(indicesOfUnconvertibleCharacters[0]==0);
	TEST(indicesOfUnconvertibleCharacters[1]==2);
	TEST(indicesOfUnconvertibleCharacters[2]==4);
	indicesOfUnconvertibleCharacters.RemoveAll();
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 20);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==6);
	TEST(shortForeignOutputBuffer==KLit8ExpectedJis_2().Left(17));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==2);
	TEST(indicesOfUnconvertibleCharacters[0]==0);
	TEST(indicesOfUnconvertibleCharacters[1]==2);
	indicesOfUnconvertibleCharacters.RemoveAll();
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 12);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==8);
	TEST(shortForeignOutputBuffer==KLit8ExpectedJis_2().Left(9));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==1);
	TEST(indicesOfUnconvertibleCharacters[0]==0);
	indicesOfUnconvertibleCharacters.RemoveAll();
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 3);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==10);
	TEST(shortForeignOutputBuffer==KNullDesC8);
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==0);
	indicesOfUnconvertibleCharacters.RemoveAll();
	characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierGb2312, *arrayOfCharacterSetsAvailable, fileServerSession);
	originalUnicode.Format(_L16("%c%c!%c%c%c"), 0x4e2d, KTibetanCharacter, KTibetanCharacter, 0x56fd, KTibetanCharacter);
	_LIT8(KLit8ExpectedGb2312_1, "\xd6\xd0\xa3\xbf!\xa3\xbf\xb9\xfa\xa3\xbf");
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 11);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==0);
	TEST(shortForeignOutputBuffer==KLit8ExpectedGb2312_1);
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==3);
	TEST(indicesOfUnconvertibleCharacters[0]==1);
	TEST(indicesOfUnconvertibleCharacters[1]==3);
	TEST(indicesOfUnconvertibleCharacters[2]==5);
	indicesOfUnconvertibleCharacters.RemoveAll();
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 10);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==1);
	TEST(shortForeignOutputBuffer==KLit8ExpectedGb2312_1().Left(9));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==2);
	TEST(indicesOfUnconvertibleCharacters[0]==1);
	TEST(indicesOfUnconvertibleCharacters[1]==3);
	indicesOfUnconvertibleCharacters.RemoveAll();
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 6);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==3);
	TEST(shortForeignOutputBuffer==KLit8ExpectedGb2312_1().Left(5));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==1);
	TEST(indicesOfUnconvertibleCharacters[0]==1);
	indicesOfUnconvertibleCharacters.RemoveAll();
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 3);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==5);
	TEST(shortForeignOutputBuffer==KLit8ExpectedGb2312_1().Left(2));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==0);
	indicesOfUnconvertibleCharacters.RemoveAll();
	characterSetConverter->SetReplacementForUnconvertibleUnicodeCharactersL(_L8("_"));
	_LIT8(KLit8ExpectedGb2312_2, "\xd6\xd0_!_\xb9\xfa_");
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 8);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==0);
	TEST(shortForeignOutputBuffer==KLit8ExpectedGb2312_2);
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==3);
	TEST(indicesOfUnconvertibleCharacters[0]==1);
	TEST(indicesOfUnconvertibleCharacters[1]==3);
	TEST(indicesOfUnconvertibleCharacters[2]==5);
	indicesOfUnconvertibleCharacters.RemoveAll();
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 7);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==1);
	TEST(shortForeignOutputBuffer==KLit8ExpectedGb2312_2().Left(7));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==2);
	TEST(indicesOfUnconvertibleCharacters[0]==1);
	TEST(indicesOfUnconvertibleCharacters[1]==3);
	indicesOfUnconvertibleCharacters.RemoveAll();
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 4);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==3);
	TEST(shortForeignOutputBuffer==KLit8ExpectedGb2312_2().Left(4));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==1);
	TEST(indicesOfUnconvertibleCharacters[0]==1);
	indicesOfUnconvertibleCharacters.RemoveAll();
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 2);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==5);
	TEST(shortForeignOutputBuffer==KLit8ExpectedGb2312_2().Left(2));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==0);
	indicesOfUnconvertibleCharacters.RemoveAll();
	characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierHz, *arrayOfCharacterSetsAvailable, fileServerSession);
	originalUnicode.Format(_L16("%c%c%c%c^%cZ%c"), 0x6ee1, KTibetanCharacter, 0x80ea, KTibetanCharacter, KTibetanCharacter, KTibetanCharacter);
	_LIT8(KLit8ExpectedHz_1, "~{Bz#?kM#?~}^~{#?~}Z~{#?~}"); // if a 2-byte character is to be used for HZ's replacement character, then it must be in 8-bit GB-2312-80 form, rather than in the 7-bit form with a "~{" and "~}" wrapper
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 26);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==0);
	TEST(shortForeignOutputBuffer==KLit8ExpectedHz_1);
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==4);
	TEST(indicesOfUnconvertibleCharacters[0]==1);
	TEST(indicesOfUnconvertibleCharacters[1]==3);
	TEST(indicesOfUnconvertibleCharacters[2]==5);
	TEST(indicesOfUnconvertibleCharacters[3]==7);
	indicesOfUnconvertibleCharacters.RemoveAll();
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 25);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==1);
	TEST(shortForeignOutputBuffer==KLit8ExpectedHz_1().Left(20));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==3);
	TEST(indicesOfUnconvertibleCharacters[0]==1);
	TEST(indicesOfUnconvertibleCharacters[1]==3);
	TEST(indicesOfUnconvertibleCharacters[2]==5);
	indicesOfUnconvertibleCharacters.RemoveAll();
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 18);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==3);
	TEST(shortForeignOutputBuffer==KLit8ExpectedHz_1().Left(13));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==2);
	TEST(indicesOfUnconvertibleCharacters[0]==1);
	TEST(indicesOfUnconvertibleCharacters[1]==3);
	indicesOfUnconvertibleCharacters.RemoveAll();
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 11);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==5);
	TEST(shortForeignOutputBuffer==_L8("~{Bz#?kM~}"));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==1);
	TEST(indicesOfUnconvertibleCharacters[0]==1);
	indicesOfUnconvertibleCharacters.RemoveAll();
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 7);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==7);
	TEST(shortForeignOutputBuffer==_L8("~{Bz~}"));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==0);
	indicesOfUnconvertibleCharacters.RemoveAll();
	characterSetConverter->SetReplacementForUnconvertibleUnicodeCharactersL(_L8("_"));
	_LIT8(KLit8ExpectedHz_2, "~{Bz~}_~{kM~}_^_Z_");
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 18);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==0);
	TEST(shortForeignOutputBuffer==KLit8ExpectedHz_2);
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==4);
	TEST(indicesOfUnconvertibleCharacters[0]==1);
	TEST(indicesOfUnconvertibleCharacters[1]==3);
	TEST(indicesOfUnconvertibleCharacters[2]==5);
	TEST(indicesOfUnconvertibleCharacters[3]==7);
	indicesOfUnconvertibleCharacters.RemoveAll();
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 17);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==1);
	TEST(shortForeignOutputBuffer==KLit8ExpectedHz_2().Left(17));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==3);
	TEST(indicesOfUnconvertibleCharacters[0]==1);
	TEST(indicesOfUnconvertibleCharacters[1]==3);
	TEST(indicesOfUnconvertibleCharacters[2]==5);
	indicesOfUnconvertibleCharacters.RemoveAll();
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 15);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==3);
	TEST(shortForeignOutputBuffer==KLit8ExpectedHz_2().Left(15));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==2);
	TEST(indicesOfUnconvertibleCharacters[0]==1);
	TEST(indicesOfUnconvertibleCharacters[1]==3);
	indicesOfUnconvertibleCharacters.RemoveAll();
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 13);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==5);
	TEST(shortForeignOutputBuffer==KLit8ExpectedHz_2().Left(13));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==1);
	TEST(indicesOfUnconvertibleCharacters[0]==1);
	indicesOfUnconvertibleCharacters.RemoveAll();
	shortForeignOutputBuffer.Set(foreignBuffer, 0, 6);
	TEST(characterSetConverter->ConvertFromUnicode(shortForeignOutputBuffer, originalUnicode, indicesOfUnconvertibleCharacters)==7);
	TEST(shortForeignOutputBuffer==KLit8ExpectedHz_2().Left(6));
	TEST(indicesOfUnconvertibleCharacters.NumberOfIndices()==0);
	indicesOfUnconvertibleCharacters.RemoveAll();
	TheTest.Next(_L("unconvertible foreign characters"));
	TUint16* const unicodeBuffer=CONST_CAST(TUint16*, generatedUnicode.Ptr());
	TPtr16 shortUnicodeOutputBuffer(NULL, 0, 0);
	TInt indexOfFirstByteOfFirstUnconvertibleCharacter;
	characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierGbk, *arrayOfCharacterSetsAvailable, fileServerSession);
	originalForeign.Set(TPtrC8(_S8("qwe\x80\x00rt\x81\x40\x81\x3f\xb6\x7e\xfe\xfe\xa1\xa1\xff\xff"), 19));
	expectedUnicode.Format(_L16("qwe%crt%c%c%c%c%c%c"), 0xfffd, 0x4e02, 0xfffd, 0x79ea, 0xfffd, 0x3000, 0xfffd);
	state=CCnvCharacterSetConverter::KStateDefault;
	shortUnicodeOutputBuffer.Set(unicodeBuffer, 0, 12);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters)==0);
	TEST(shortUnicodeOutputBuffer==expectedUnicode);
	TEST(numberOfUnconvertibleCharacters==4);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters, indexOfFirstByteOfFirstUnconvertibleCharacter)==0);
	TEST(shortUnicodeOutputBuffer==expectedUnicode);
	TEST(numberOfUnconvertibleCharacters==4);
	TEST(indexOfFirstByteOfFirstUnconvertibleCharacter==3);
	shortUnicodeOutputBuffer.Set(unicodeBuffer, 0, 11);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters)==2);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(11));
	TEST(numberOfUnconvertibleCharacters==3);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters, indexOfFirstByteOfFirstUnconvertibleCharacter)==2);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(11));
	TEST(numberOfUnconvertibleCharacters==3);
	TEST(indexOfFirstByteOfFirstUnconvertibleCharacter==3);
	shortUnicodeOutputBuffer.Set(unicodeBuffer, 0, 9);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters)==6);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(9));
	TEST(numberOfUnconvertibleCharacters==2);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters, indexOfFirstByteOfFirstUnconvertibleCharacter)==6);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(9));
	TEST(numberOfUnconvertibleCharacters==2);
	TEST(indexOfFirstByteOfFirstUnconvertibleCharacter==3);
	shortUnicodeOutputBuffer.Set(unicodeBuffer, 0, 7);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters)==10);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(7));
	TEST(numberOfUnconvertibleCharacters==1);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters, indexOfFirstByteOfFirstUnconvertibleCharacter)==10);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(7));
	TEST(numberOfUnconvertibleCharacters==1);
	TEST(indexOfFirstByteOfFirstUnconvertibleCharacter==3);
	shortUnicodeOutputBuffer.Set(unicodeBuffer, 0, 3);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters)==16);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(3));
	TEST(numberOfUnconvertibleCharacters==0);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters, indexOfFirstByteOfFirstUnconvertibleCharacter)==16);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(3));
	TEST(numberOfUnconvertibleCharacters==0);
	TEST(indexOfFirstByteOfFirstUnconvertibleCharacter==-1);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierShiftJis, *arrayOfCharacterSetsAvailable, fileServerSession);
	originalForeign.Set(_S8("\xea\xa5\xaf\xea\xa6\x9a\xeb\xea\xeb@\xea\x56\xea\xfc"));
	expectedUnicode.Format(_L16("%c%c%c%c%c@%c%c"), 0xfffd, 0xff6f, 0xfffd, 0x68a6, 0xfffd, 0x9dcf, 0xfffd);
	state=CCnvCharacterSetConverter::KStateDefault;
	shortUnicodeOutputBuffer.Set(unicodeBuffer, 0, 8);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters)==0);
	TEST(shortUnicodeOutputBuffer==expectedUnicode);
	TEST(numberOfUnconvertibleCharacters==4);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters, indexOfFirstByteOfFirstUnconvertibleCharacter)==0);
	TEST(shortUnicodeOutputBuffer==expectedUnicode);
	TEST(numberOfUnconvertibleCharacters==4);
	TEST(indexOfFirstByteOfFirstUnconvertibleCharacter==0);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	shortUnicodeOutputBuffer.Set(unicodeBuffer, 0, 7);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters)==2);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(7));
	TEST(numberOfUnconvertibleCharacters==3);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters, indexOfFirstByteOfFirstUnconvertibleCharacter)==2);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(7));
	TEST(numberOfUnconvertibleCharacters==3);
	TEST(indexOfFirstByteOfFirstUnconvertibleCharacter==0);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	shortUnicodeOutputBuffer.Set(unicodeBuffer, 0, 4);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters)==7);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(4));
	TEST(numberOfUnconvertibleCharacters==2);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters, indexOfFirstByteOfFirstUnconvertibleCharacter)==7);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(4));
	TEST(numberOfUnconvertibleCharacters==2);
	TEST(indexOfFirstByteOfFirstUnconvertibleCharacter==0);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	shortUnicodeOutputBuffer.Set(unicodeBuffer, 0, 2);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters)==11);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(2));
	TEST(numberOfUnconvertibleCharacters==1);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters, indexOfFirstByteOfFirstUnconvertibleCharacter)==11);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(2));
	TEST(numberOfUnconvertibleCharacters==1);
	TEST(indexOfFirstByteOfFirstUnconvertibleCharacter==0);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	shortUnicodeOutputBuffer.Set(unicodeBuffer, 0, 0);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters)==14);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(0));
	TEST(numberOfUnconvertibleCharacters==0);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters, indexOfFirstByteOfFirstUnconvertibleCharacter)==14);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(0));
	TEST(numberOfUnconvertibleCharacters==0);
	TEST(indexOfFirstByteOfFirstUnconvertibleCharacter==-1);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierIso2022Jp1, *arrayOfCharacterSetsAvailable, fileServerSession);
	originalForeign.Set(_S8("\x1b\x28\x49\x20\x4b\x60\x1b\x24\x40\x4b\x7f\x4b\x60\x4b\x20\x1b\x28\x42*+\x1b\x24\x28\x44\x6d\x50\x6d\x64\x46\x3f"));
	expectedUnicode.Format(_L16("%c%c%c%c%c%c*+%c%c%c"), 0xfffd, 0xff8b, 0xfffd, 0xfffd, 0x6469, 0xfffd, 0x9f6e, 0xfffd, 0x6bf1);
	state=CCnvCharacterSetConverter::KStateDefault;
	shortUnicodeOutputBuffer.Set(unicodeBuffer, 0, 11);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters)==0);
	TEST(shortUnicodeOutputBuffer==expectedUnicode);
	TEST(numberOfUnconvertibleCharacters==5);
	state=CCnvCharacterSetConverter::KStateDefault;
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters, indexOfFirstByteOfFirstUnconvertibleCharacter)==0);
	TEST(shortUnicodeOutputBuffer==expectedUnicode);
	TEST(numberOfUnconvertibleCharacters==5);	
	TEST(indexOfFirstByteOfFirstUnconvertibleCharacter==3);
	state=CCnvCharacterSetConverter::KStateDefault;
	shortUnicodeOutputBuffer.Set(unicodeBuffer, 0, 9);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters)==4);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(9));
	TEST(numberOfUnconvertibleCharacters==4);
	state=CCnvCharacterSetConverter::KStateDefault;
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters, indexOfFirstByteOfFirstUnconvertibleCharacter)==4);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(9));
	TEST(numberOfUnconvertibleCharacters==4);
	TEST(indexOfFirstByteOfFirstUnconvertibleCharacter==3);
	state=CCnvCharacterSetConverter::KStateDefault;
	shortUnicodeOutputBuffer.Set(unicodeBuffer, 0, 5);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters)==17);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(5));
	TEST(numberOfUnconvertibleCharacters==3);
	state=CCnvCharacterSetConverter::KStateDefault;
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters, indexOfFirstByteOfFirstUnconvertibleCharacter)==17);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(5));
	TEST(numberOfUnconvertibleCharacters==3);
	TEST(indexOfFirstByteOfFirstUnconvertibleCharacter==3);
	state=CCnvCharacterSetConverter::KStateDefault;
	shortUnicodeOutputBuffer.Set(unicodeBuffer, 0, 3);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters)==21);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(3));
	TEST(numberOfUnconvertibleCharacters==2);
	state=CCnvCharacterSetConverter::KStateDefault;
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters, indexOfFirstByteOfFirstUnconvertibleCharacter)==21);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(3));
	TEST(numberOfUnconvertibleCharacters==2);
	TEST(indexOfFirstByteOfFirstUnconvertibleCharacter==3);
	state=CCnvCharacterSetConverter::KStateDefault;
	shortUnicodeOutputBuffer.Set(unicodeBuffer, 0, 2);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters)==25);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(2));
	TEST(numberOfUnconvertibleCharacters==1);
	state=CCnvCharacterSetConverter::KStateDefault;
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters, indexOfFirstByteOfFirstUnconvertibleCharacter)==25);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(2));
	TEST(numberOfUnconvertibleCharacters==1);
	TEST(indexOfFirstByteOfFirstUnconvertibleCharacter==3);
	state=CCnvCharacterSetConverter::KStateDefault;
	shortUnicodeOutputBuffer.Set(unicodeBuffer, 0, 0);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters)==30);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(0));
	TEST(numberOfUnconvertibleCharacters==0);
	state=CCnvCharacterSetConverter::KStateDefault;
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters, indexOfFirstByteOfFirstUnconvertibleCharacter)==30);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(0));
	TEST(numberOfUnconvertibleCharacters==0);
	TEST(indexOfFirstByteOfFirstUnconvertibleCharacter==-1);
	characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierHz, *arrayOfCharacterSetsAvailable, fileServerSession);
	originalForeign.Set(_S8("{~{  !!\"o~}~~~{o\"x#R7~}}"));
	expectedUnicode.Format(_L16("{%c%c%c~%c%c%c}"), 0xfffd, 0x3000, 0xfffd, 0x94eb, 0xfffd, 0x66f3);
	state=CCnvCharacterSetConverter::KStateDefault;
	shortUnicodeOutputBuffer.Set(unicodeBuffer, 0, 9);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters)==0);
	TEST(shortUnicodeOutputBuffer==expectedUnicode);
	TEST(numberOfUnconvertibleCharacters==3);
	state=CCnvCharacterSetConverter::KStateDefault;
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters, indexOfFirstByteOfFirstUnconvertibleCharacter)==0);
	TEST(shortUnicodeOutputBuffer==expectedUnicode);
	TEST(numberOfUnconvertibleCharacters==3);	
	TEST(indexOfFirstByteOfFirstUnconvertibleCharacter==3);
	state=CCnvCharacterSetConverter::KStateDefault;
	shortUnicodeOutputBuffer.Set(unicodeBuffer, 0, 6);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters)==7);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(6));
	TEST(numberOfUnconvertibleCharacters==2);
	state=CCnvCharacterSetConverter::KStateDefault;
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters, indexOfFirstByteOfFirstUnconvertibleCharacter)==7);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(6));
	TEST(numberOfUnconvertibleCharacters==2);	
	TEST(indexOfFirstByteOfFirstUnconvertibleCharacter==3);
	state=CCnvCharacterSetConverter::KStateDefault;
	shortUnicodeOutputBuffer.Set(unicodeBuffer, 0, 3);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters)==17);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(3));
	TEST(numberOfUnconvertibleCharacters==1);
	state=CCnvCharacterSetConverter::KStateDefault;
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters, indexOfFirstByteOfFirstUnconvertibleCharacter)==17);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(3));
	TEST(numberOfUnconvertibleCharacters==1);	
	TEST(indexOfFirstByteOfFirstUnconvertibleCharacter==3);
	state=CCnvCharacterSetConverter::KStateDefault;
	shortUnicodeOutputBuffer.Set(unicodeBuffer, 0, 1);
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters)==21);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(1));
	TEST(numberOfUnconvertibleCharacters==0);
	state=CCnvCharacterSetConverter::KStateDefault;
	TEST(characterSetConverter->ConvertToUnicode(shortUnicodeOutputBuffer, originalForeign, state, numberOfUnconvertibleCharacters, indexOfFirstByteOfFirstUnconvertibleCharacter)==21);
	TEST(shortUnicodeOutputBuffer==expectedUnicode.Left(1));
	TEST(numberOfUnconvertibleCharacters==0);	
	TEST(indexOfFirstByteOfFirstUnconvertibleCharacter==-1);
	// Cleanup: arrayOfCharacterSetsAvailable and characterSetConverter and fileServerSession
	// and originalUnicodeHBuf, generatedUnicodeHBuf, expectedUnicodeHBuf, generatedForeignHBuf
	CleanupStack::PopAndDestroy(7); 
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

