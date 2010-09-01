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
#include <f32file.h>
#include <utf.h>

///////////////////////////////////////////////////////////////////////////////////////

RTest TheTest(_L("TRealUni"));
	
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
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0568
@SYMTestCaseDesc        Testing a real Unicode file's round trip
@SYMTestPriority        Medium
@SYMTestActions        	Tests for CnvUtfConverter::ConvertFromUnicodeToUtf8() function   
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
GLDEF_C TInt E32Main()
	{
	TheTest.Title();
	TheTest.Start(_L("Testing a \"real\" Unicode file's round trip"));
	RFs fs;
	RFile file;
	TEST2(fs.Connect(), KErrNone);
	TFindFile findFile=fs;
	TEST(findFile.FindByDir(_L("DAXUE.UNI"), _L("\\system\\data\\"))==KErrNone);
	TEST(file.Open(fs, findFile.File(), EFileShareExclusive|EFileStream|EFileRead)==KErrNone);
	TInt size=0;
	TEST2(file.Size(size), KErrNone);
	TEST((size>0) && (size%2==0));
	HBufC16* originalUnicode=HBufC16::New(size/2);
	HBufC8* generatedUtf8=HBufC8::New(size*2);
	HBufC16* generatedUnicode=HBufC16::New(size/2);
	TEST(originalUnicode!=NULL);
 	TEST(generatedUtf8!=NULL);
 	TEST(generatedUnicode!=NULL);
	TPtr8 ptr1(REINTERPRET_CAST(TUint8*, CONST_CAST(TUint16*, originalUnicode->Ptr())), 0, size);
	TEST2(file.Read(ptr1), KErrNone);
	TEST(ptr1.Length()==size);
	TPtr16 ptr2=originalUnicode->Des();
	ptr2.SetLength(size/2);
	TEST(originalUnicode->Size()==size);
	TPtr8 ptr3=generatedUtf8->Des();
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(ptr3, *originalUnicode)==0);
	TPtr16 ptr4=generatedUnicode->Des();
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(ptr4, *generatedUtf8)==0);
	TEST(*generatedUnicode==*originalUnicode);
	delete originalUnicode;
	delete generatedUtf8;
	delete generatedUnicode;
	file.Close();
	fs.Close();
	TheTest.End();
	TheTest.Close();
	return KErrNone;
	}

