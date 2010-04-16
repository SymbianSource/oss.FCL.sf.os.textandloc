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

RTest TheTest(_L("TSimple7"));
	
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
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0562
@SYMTestCaseDesc        Conversion tests from Unicode to UTF-7 character set
@SYMTestPriority        Medium
@SYMTestActions        	Tests for CnvUtfConverter::ConvertFromUnicodeToUtf7() function
						Tests for CnvUtfConverter::ConvertToUnicodeFromUtf7() function
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
GLDEF_C TInt E32Main()
	{
	TheTest.Title();
	TheTest.Start(_L("Testing simple UTF-7 round trips"));
	TBuf16<256> originalUnicode;
	TBuf8<256> generatedUtf7;
	TBuf16<256> generatedUnicode;
	TInt state=CnvUtfConverter::KStateDefault;
	//
	TheTest.Next(_L("Empty descriptor"));
	originalUnicode=_L16("");
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf7, originalUnicode, ETrue)==0);
	TEST(generatedUtf7==_L8(""));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, generatedUtf7, state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode==originalUnicode);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf7, originalUnicode, EFalse)==0);
	TEST(generatedUtf7==_L8(""));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, generatedUtf7, state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode==originalUnicode);
	TheTest.Next(_L("English \"Hello!\""));
	originalUnicode=_L16("Hello!");
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf7, originalUnicode, ETrue)==0);
	TEST(generatedUtf7==_L8("Hello+ACE-"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, generatedUtf7, state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode==originalUnicode);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf7, originalUnicode, EFalse)==0);
	TEST(generatedUtf7==_L8("Hello!"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, generatedUtf7, state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode==originalUnicode);
	TheTest.Next(_L("Russian \"Hello!\""));
	originalUnicode.Format(_L16("%c%c%c%c%c%c%c%c%c%c%c%c!"), 0x0417, 0x0434, 0x0440, 0x0430, 0x0432, 0x0441, 0x0442, 0x0432, 0x0443, 0x0439, 0x0442, 0x0435);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf7, originalUnicode, ETrue)==0);
	TEST(generatedUtf7==_L8("+BBcENARABDAEMgRBBEIEMgRDBDkEQgQ1ACE-"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, generatedUtf7, state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode==originalUnicode);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf7, originalUnicode, EFalse)==0);
	TEST(generatedUtf7==_L8("+BBcENARABDAEMgRBBEIEMgRDBDkEQgQ1-!"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, generatedUtf7, state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode==originalUnicode);
	TheTest.Next(_L("Greek \"Hello!\""));
	originalUnicode.Format(_L16("%c%c%c%c%c!"), 0x0393, 0x03b1, 0x03c3, 0x03bf, 0x03c5);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf7, originalUnicode, ETrue)==0);
	TEST(generatedUtf7==_L8("+A5MDsQPDA78DxQAh-"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, generatedUtf7, state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode==originalUnicode);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf7, originalUnicode, EFalse)==0);
	TEST(generatedUtf7==_L8("+A5MDsQPDA78DxQ-!"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, generatedUtf7, state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode==originalUnicode);
	TheTest.Next(_L("Chinese \"Hello!\""));
	originalUnicode.Format(_L16("%c%c!"), 0x4f60, 0x597d);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf7, originalUnicode, ETrue)==0);
	TEST(generatedUtf7==_L8("+T2BZfQAh-"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, generatedUtf7, state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode==originalUnicode);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf7, originalUnicode, EFalse)==0);
	TEST(generatedUtf7==_L8("+T2BZfQ-!"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, generatedUtf7, state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode==originalUnicode);
	TheTest.Next(_L("Japanese \"Hello!\""));
	originalUnicode.Format(_L16("%c%c%c!"), 0x4eca, 0x65e5, 0x306f);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf7, originalUnicode, ETrue)==0);
	TEST(generatedUtf7==_L8("+Tspl5TBvACE-"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, generatedUtf7, state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode==originalUnicode);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf7, originalUnicode, EFalse)==0);
	TEST(generatedUtf7==_L8("+Tspl5TBv-!"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, generatedUtf7, state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode==originalUnicode);
	TheTest.Next(_L("Trailing \"-\" character"));
	originalUnicode=_L16(":-");
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf7, originalUnicode, ETrue)==0);
	TEST(generatedUtf7==_L8(":-"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, generatedUtf7, state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode==originalUnicode);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf7, originalUnicode, EFalse)==0);
	TEST(generatedUtf7==_L8(":-"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, generatedUtf7, state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode==originalUnicode);
	originalUnicode=_L16("=-");
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf7, originalUnicode, ETrue)==0);
	TEST(generatedUtf7==_L8("+AD0--"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, generatedUtf7, state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode==originalUnicode);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf7, originalUnicode, EFalse)==0);
	TEST(generatedUtf7==_L8("=-"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, generatedUtf7, state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode==originalUnicode);
	originalUnicode.Format(_L16("%c-"), 0x1e77);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf7, originalUnicode, ETrue)==0);
	TEST(generatedUtf7==_L8("+Hnc--"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, generatedUtf7, state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode==originalUnicode);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf7, originalUnicode, EFalse)==0);
	TEST(generatedUtf7==_L8("+Hnc--"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, generatedUtf7, state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode==originalUnicode);
	TheTest.Next(_L("Interspersed \"+\" characters"));
	originalUnicode.Format(_L16("+%c+&+a+"), 0x52ff);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf7, originalUnicode, ETrue)==0);
	TEST(generatedUtf7==_L8("+-+Uv8-+-+ACY-+-a+-"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, generatedUtf7, state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode==originalUnicode);
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(generatedUtf7, originalUnicode, EFalse)==0);
	TEST(generatedUtf7==_L8("+-+Uv8-+-&+-a+-"));
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(generatedUnicode, generatedUtf7, state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(generatedUnicode==originalUnicode);

	TheTest.End();
	TheTest.Close();
	return KErrNone;
	}

