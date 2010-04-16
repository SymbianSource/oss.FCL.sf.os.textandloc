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

RTest TheTest(_L("TNewLin7"));
	
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
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0570
@SYMTestCaseDesc        Testing base64 sequences combined with line-breaks
@SYMTestPriority        Medium
@SYMTestActions        	Tests for conversion from UTF-7 to Unicode with line-breaks 
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
GLDEF_C TInt E32Main()
	{
	TheTest.Title();
	TheTest.Start(_L("Testing base64 sequences combined with line-breaks"));
	TBuf16<256> unicode;
	TBuf8<256> utf7;
	TInt state=CnvUtfConverter::KStateDefault;
	utf7=_L8("+U0E\nU0E");
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(unicode, utf7, state)==0);
	TEST(state==CnvUtfConverter::KStateDefault);
	TEST(unicode.Length()==5);
	TEST(unicode[0]==0x5341);
	TEST(unicode[1]==0x000a);
	TEST(unicode[2]==0x0055);
	TEST(unicode[3]==0x0030);
	TEST(unicode[4]==0x0045);
	unicode=_L16(")\n)\n*\n*\n+\n+\n)\n)\n*\n*\n+\n+");
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(utf7, unicode, ETrue)==0);
	TEST(utf7==_L8(")\n)\n+ACo-\n+ACo-\n+-\n+-\n)\n)\n+ACo-\n+ACo-\n+-\n+-"));
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(utf7, unicode, EFalse)==0);
	TEST(utf7==_L8(")\n)\n*\n*\n+-\n+-\n)\n)\n*\n*\n+-\n+-"));
	TheTest.End();
	TheTest.Close();
	return KErrNone;
	}

