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
#include <e32base.h>
#include <e32test.h>
#include <f32file.h>
#include <charconv.h>
#include <utf.h>

///////////////////////////////////////////////////////////////////////////////////////

RTest TheTest(_L("TJava"));
	
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
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0571
@SYMTestCaseDesc        CnvUtfConverter class functionality test
@SYMTestPriority        Medium
@SYMTestActions        	Checking that Java-conformant UTF-8 is generated and handled correctly
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void DoE32MainL()
	{
	RFs fileServerSession;
	CleanupClosePushL(fileServerSession);
	User::LeaveIfError(fileServerSession.Connect());
	CCnvCharacterSetConverter* characterSetConverter=CCnvCharacterSetConverter::NewLC();
	TheTest.Start(_L("Checking that Java-conformant UTF-8 is generated and handled correctly"));
	TEST(characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierJavaConformantUtf8, fileServerSession)==CCnvCharacterSetConverter::EAvailable);
	TBuf16<32> unicode;
	TBuf16<32> generatedUnicode;
	TBuf8<64> generatedUtf8;
	//
	TheTest.Next(_L("Testing the behaviour of the Unicode character 0x0000"));
	unicode.Format(_L16("%c"), 0x0000);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==TPtrC8(REINTERPRET_CAST(const TText8*, "\x00"), 1)); // can't use _L8 as that gets the length by assuming it's a zero-terminated string
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	TEST(characterSetConverter->ConvertFromUnicode(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xc0\x80"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	unicode.Format(_L16("%c%c"), 0x0000, 0x0026);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==TPtrC8(REINTERPRET_CAST(const TText8*, "\x00\x26"), 2)); // can't use _L8 as that gets the length by assuming it's a zero-terminated string
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	TEST(characterSetConverter->ConvertFromUnicode(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xc0\x80\x26"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	unicode.Format(_L16("%c%c"), 0x0000, 0x05d9);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==TPtrC8(REINTERPRET_CAST(const TText8*, "\x00\xd7\x99"), 3)); // can't use _L8 as that gets the length by assuming it's a zero-terminated string
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	TEST(characterSetConverter->ConvertFromUnicode(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xc0\x80\xd7\x99"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	unicode.Format(_L16("%c%c"), 0x0000, 0x81ea);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==TPtrC8(REINTERPRET_CAST(const TText8*, "\x00\xe8\x87\xaa"), 4)); // can't use _L8 as that gets the length by assuming it's a zero-terminated string
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	TEST(characterSetConverter->ConvertFromUnicode(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xc0\x80\xe8\x87\xaa"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	unicode.Format(_L16("%c%c%c"), 0x0000, 0xd9e0, 0xdda3);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==TPtrC8(REINTERPRET_CAST(const TText8*, "\x00\xf2\x88\x86\xa3"), 5)); // can't use _L8 as that gets the length by assuming it's a zero-terminated string
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	TEST(characterSetConverter->ConvertFromUnicode(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xc0\x80\xed\xa7\xa0\xed\xb6\xa3"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	unicode.Format(_L16("%c%c"), 0x0071, 0x0000);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==TPtrC8(REINTERPRET_CAST(const TText8*, "\x71\x00"), 2)); // can't use _L8 as that gets the length by assuming it's a zero-terminated string
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	TEST(characterSetConverter->ConvertFromUnicode(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\x71\xc0\x80"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	unicode.Format(_L16("%c%c"), 0x06aa, 0x0000);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==TPtrC8(REINTERPRET_CAST(const TText8*, "\xda\xaa\x00"), 3)); // can't use _L8 as that gets the length by assuming it's a zero-terminated string
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	TEST(characterSetConverter->ConvertFromUnicode(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xda\xaa\xc0\x80"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	unicode.Format(_L16("%c%c"), 0xc427, 0x0000);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==TPtrC8(REINTERPRET_CAST(const TText8*, "\xec\x90\xa7\x00"), 4)); // can't use _L8 as that gets the length by assuming it's a zero-terminated string
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	TEST(characterSetConverter->ConvertFromUnicode(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xec\x90\xa7\xc0\x80"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	unicode.Format(_L16("%c%c%c"), 0xd801, 0xdef1, 0x0000);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==TPtrC8(REINTERPRET_CAST(const TText8*, "\xf0\x90\x9b\xb1\x00"), 5)); // can't use _L8 as that gets the length by assuming it's a zero-terminated string
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	TEST(characterSetConverter->ConvertFromUnicode(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xed\xa0\x81\xed\xbb\xb1\xc0\x80"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	TheTest.Next(_L("Testing the generation of UTF-8 from surrogate pairs"));
	unicode.Format(_L16("%c"), 0xd7ff);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xed\x9f\xbf"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	TEST(characterSetConverter->ConvertFromUnicode(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xed\x9f\xbf"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	unicode.Format(_L16("%c"), 0xe000);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xee\x80\x80"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	TEST(characterSetConverter->ConvertFromUnicode(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xee\x80\x80"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	unicode.Format(_L16("%c%c"), 0xd800, 0xdc00);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xf0\x90\x80\x80"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	TEST(characterSetConverter->ConvertFromUnicode(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xed\xa0\x80\xed\xb0\x80"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	unicode.Format(_L16("%c%c"), 0xd800, 0xdfff);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xf0\x90\x8f\xbf"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	TEST(characterSetConverter->ConvertFromUnicode(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xed\xa0\x80\xed\xbf\xbf"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	unicode.Format(_L16("%c%c"), 0xdbff, 0xdc00);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xf4\x8f\xb0\x80"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	TEST(characterSetConverter->ConvertFromUnicode(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xed\xaf\xbf\xed\xb0\x80"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	unicode.Format(_L16("%c%c"), 0xdbff, 0xdfff);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xf4\x8f\xbf\xbf"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	TEST(characterSetConverter->ConvertFromUnicode(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xed\xaf\xbf\xed\xbf\xbf"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	unicode.Format(_L16("%c%c"), 0xd8e9, 0xdcd4);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xf1\x8a\x93\x94"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	TEST(characterSetConverter->ConvertFromUnicode(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xed\xa3\xa9\xed\xb3\x94"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	unicode.Format(_L16("%c%c%c"), 0xd8e9, 0xdcd4, 0x003e);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xf1\x8a\x93\x94\x3e"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	TEST(characterSetConverter->ConvertFromUnicode(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xed\xa3\xa9\xed\xb3\x94\x3e"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	unicode.Format(_L16("%c%c%c"), 0xd8e9, 0xdcd4, 0x01e9);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xf1\x8a\x93\x94\xc7\xa9"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	TEST(characterSetConverter->ConvertFromUnicode(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xed\xa3\xa9\xed\xb3\x94\xc7\xa9"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	unicode.Format(_L16("%c%c%c"), 0xd8e9, 0xdcd4, 0x1f9a);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xf1\x8a\x93\x94\xe1\xbe\x9a"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	TEST(characterSetConverter->ConvertFromUnicode(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xed\xa3\xa9\xed\xb3\x94\xe1\xbe\x9a"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	unicode.Format(_L16("%c%c%c"), 0x0025, 0xd8e9, 0xdcd4);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\x25\xf1\x8a\x93\x94"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	TEST(characterSetConverter->ConvertFromUnicode(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\x25\xed\xa3\xa9\xed\xb3\x94"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	unicode.Format(_L16("%c%c%c"), 0x00a5, 0xd8e9, 0xdcd4);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xc2\xa5\xf1\x8a\x93\x94"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	TEST(characterSetConverter->ConvertFromUnicode(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xc2\xa5\xed\xa3\xa9\xed\xb3\x94"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	unicode.Format(_L16("%c%c%c"), 0x0ca6, 0xd8e9, 0xdcd4);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xe0\xb2\xa6\xf1\x8a\x93\x94"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	TEST(characterSetConverter->ConvertFromUnicode(generatedUtf8, unicode)==0);
	TEST(generatedUtf8==_L8("\xe0\xb2\xa6\xed\xa3\xa9\xed\xb3\x94"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==unicode);
	CleanupStack::PopAndDestroy(2); // characterSetConverter and fileServerSession
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

