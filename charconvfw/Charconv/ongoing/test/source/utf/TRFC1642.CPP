/*
* Copyright (c) 1642 Nokia Corporation and/or its subsidiary(-ies). 
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

RTest TheTest(_L("TRFC1642"));
	
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
/**
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0564
@SYMTestCaseDesc        Tests for conversion from UTF-7 to Unicode character set
@SYMTestPriority        Medium
@SYMTestActions        	Tests for CnvUtfConverter::ConvertToUnicodeFromUtf7() function
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
GLDEF_C TInt E32Main()
	{
	TheTest.Title();
	TheTest.Start(_L("Testing the examples given in RFC 1642"));
	TBuf16<256> generatedUnicode;
	TInt state=CnvUtfConverter::KStateDefault;
	//
	TheTest.Next(_L("Empty descriptor"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8(""), state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode==_L16(""));
	TheTest.Next(_L("\"A<NOT IDENTICAL TO><ALPHA>.\""));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("A+ImIDkQ."), state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode.Length()==4);
	TEST(generatedUnicode[0]==0x0041);
	TEST(generatedUnicode[1]==0x2262);
	TEST(generatedUnicode[2]==0x0391);
	TEST(generatedUnicode[3]==0x002e);
	TheTest.Next(_L("\"Hi Mom <WHITE SMILING FACE>!\""));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("Hi Mom +Jjo-!"), state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode.Length()==9);
	TEST(generatedUnicode[0]==0x0048);
	TEST(generatedUnicode[1]==0x0069);
	TEST(generatedUnicode[2]==0x0020);
	TEST(generatedUnicode[3]==0x004d);
	TEST(generatedUnicode[4]==0x006f);
	TEST(generatedUnicode[5]==0x006d);
	TEST(generatedUnicode[6]==0x0020);
	TEST(generatedUnicode[7]==0x263a);
	TEST(generatedUnicode[8]==0x0021);
	TheTest.Next(_L("The japanese word \"nihongo\""));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+ZeVnLIqe-"), state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode.Length()==3);
	TEST(generatedUnicode[0]==0x65e5);
	TEST(generatedUnicode[1]==0x672c);
	TEST(generatedUnicode[2]==0x8a9e);
	TheTest.Next(_L("The special case of \"+-\""));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("+-"), state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode==_L16("+"));
	TheTest.Next(_L("The special case of \"+-\" in a context"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, _L8("2+-3 is 5"), state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode==_L16("2+3 is 5"));
	//
	TheTest.End();
	TheTest.Close();
	return KErrNone;
	}

