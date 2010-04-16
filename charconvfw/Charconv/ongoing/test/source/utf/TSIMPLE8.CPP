/*
* Copyright (c) 1997-2005 Nokia Corporation and/or its subsidiary(-ies). 
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of the License "Eclipse Public License v1.0"
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

RTest TheTest(_L("TSimple8"));
	
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
/**
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0563
@SYMTestCaseDesc        Conversion tests from Unicode to UTF-8 character set
@SYMTestPriority        Medium
@SYMTestActions        	Tests for CnvUtfConverter::ConvertFromUnicodeToUtf8(),
                        CnvUtfConverter::ConvertToUnicodeFromUtf8L() function  
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void DoE32MainL()
	{
	TheTest.Start(_L("Testing simple UTF-8 round trips"));
	TBuf16<256> originalUnicode;
	TBuf8<256> generatedUtf8;
	TBuf16<256> generatedUnicode;
	//
	TheTest.Next(_L("Empty descriptor"));
	originalUnicode=_L16("");
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, originalUnicode)==0);
	TEST(generatedUtf8==_L8(""));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==originalUnicode);
	// Testing the new API
	HBufC8* testbuffer8;
	HBufC* testbuffer;
	testbuffer8= CnvUtfConverter::ConvertFromUnicodeToUtf8L(originalUnicode);
	TPtr8 comparebuffer8 = testbuffer8->Des();
	TEST(comparebuffer8==generatedUtf8);
	testbuffer = CnvUtfConverter::ConvertToUnicodeFromUtf8L(generatedUtf8);
	TPtr compareBuffer = testbuffer->Des();
	TEST(compareBuffer == originalUnicode);
	delete testbuffer8;
	delete testbuffer;

	TheTest.Next(_L("English \"Hello!\""));
	originalUnicode=_L16("Hello!");
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, originalUnicode)==0);
	TEST(generatedUtf8==_L8("Hello!"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==originalUnicode);
	// Testing the new API
	testbuffer8= CnvUtfConverter::ConvertFromUnicodeToUtf8L(originalUnicode);
	comparebuffer8.Set(testbuffer8->Des());
	TEST(comparebuffer8==generatedUtf8);
	testbuffer = CnvUtfConverter::ConvertToUnicodeFromUtf8L(generatedUtf8);
	compareBuffer.Set(testbuffer->Des());
	TEST(compareBuffer == originalUnicode);
	delete testbuffer8;
	delete testbuffer;

	TheTest.Next(_L("Russian \"Hello!\""));
	originalUnicode.Format(_L16("%c%c%c%c%c%c%c%c%c%c%c%c%c"), 0x0417, 0x0434, 0x0440, 0x0430, 0x0432, 0x0441, 0x0442, 0x0432, 0x0443, 0x0439, 0x0442, 0x0435, 0x0021);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, originalUnicode)==0);
	TEST(generatedUtf8==_L8("\xd0\x97\xd0\xb4\xd1\x80\xd0\xb0\xd0\xb2\xd1\x81\xd1\x82\xd0\xb2\xd1\x83\xd0\xb9\xd1\x82\xd0\xb5\x21"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==originalUnicode);
	// Testing the new API
	testbuffer8= CnvUtfConverter::ConvertFromUnicodeToUtf8L(originalUnicode);
	comparebuffer8.Set(testbuffer8->Des());
	TEST(comparebuffer8==generatedUtf8);
	testbuffer = CnvUtfConverter::ConvertToUnicodeFromUtf8L(generatedUtf8);
	compareBuffer.Set(testbuffer->Des());
	TEST(compareBuffer == originalUnicode);
	delete testbuffer8;
	delete testbuffer;

	TheTest.Next(_L("Greek \"Hello!\""));
	originalUnicode.Format(_L16("%c%c%c%c%c%c"), 0x0393, 0x03b1, 0x03c3, 0x03bf, 0x03c5, 0x0021);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, originalUnicode)==0);
	TEST(generatedUtf8==_L8("\xce\x93\xce\xb1\xcf\x83\xce\xbf\xcf\x85\x21"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==originalUnicode);
	// Testing the new API
	testbuffer8= CnvUtfConverter::ConvertFromUnicodeToUtf8L(originalUnicode);
	comparebuffer8.Set(testbuffer8->Des());
	TEST(comparebuffer8==generatedUtf8);
	testbuffer = CnvUtfConverter::ConvertToUnicodeFromUtf8L(generatedUtf8);
	compareBuffer.Set(testbuffer->Des());
	TEST(compareBuffer == originalUnicode);
	delete testbuffer8;
	delete testbuffer;

	TheTest.Next(_L("Chinese \"Hello!\""));
	originalUnicode.Format(_L16("%c%c%c"), 0x4f60, 0x597d, 0x0021);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, originalUnicode)==0);
	TEST(generatedUtf8==_L8("\xe4\xbd\xa0\xe5\xa5\xbd\x21"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==originalUnicode);
	// Testing the new API
	testbuffer8= CnvUtfConverter::ConvertFromUnicodeToUtf8L(originalUnicode);
	comparebuffer8.Set(testbuffer8->Des());
	TEST(comparebuffer8==generatedUtf8);
	testbuffer = CnvUtfConverter::ConvertToUnicodeFromUtf8L(generatedUtf8);
	compareBuffer.Set(testbuffer->Des());
	TEST(compareBuffer == originalUnicode);
	delete testbuffer8;
	delete testbuffer;

	TheTest.Next(_L("Japanese \"Hello!\""));
	originalUnicode.Format(_L16("%c%c%c%c"), 0x4eca, 0x65e5, 0x306f, 0x0021);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(generatedUtf8, originalUnicode)==0);
	TEST(generatedUtf8==_L8("\xe4\xbb\x8a\xe6\x97\xa5\xe3\x81\xaf\x21"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(generatedUnicode, generatedUtf8)==0);
	TEST(generatedUnicode==originalUnicode);
	// Testing the new API
	testbuffer8= CnvUtfConverter::ConvertFromUnicodeToUtf8L(originalUnicode);
	comparebuffer8.Set(testbuffer8->Des());
	TEST(comparebuffer8==generatedUtf8);
	testbuffer = CnvUtfConverter::ConvertToUnicodeFromUtf8L(generatedUtf8);
	compareBuffer.Set(testbuffer->Des());
	TEST(compareBuffer == originalUnicode);
	delete testbuffer8;
	delete testbuffer;
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

