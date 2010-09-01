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

RTest TheTest(_L("TRealUT8"));
	
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
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0567
@SYMTestCaseDesc        Testing a real UTF8 file's round trip
@SYMTestPriority        Medium
@SYMTestActions        	Tests for CnvUtfConverter::ConvertToUnicodeFromUtf8() function  
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
GLDEF_C TInt E32Main()
	{
	TheTest.Title();
	TheTest.Start(_L("Testing a \"real\" UTF8 file's round trip"));
	RFs fs;
	RFile inputFile;
	TEST2(fs.Connect(), KErrNone);
	TFindFile findFile=fs;
	TEST(findFile.FindByDir(_L("ETHIOPIC.UT8"), _L("\\system\\data\\"))==KErrNone);
	TEST(inputFile.Open(fs, findFile.File(), EFileShareExclusive|EFileStream|EFileRead)==KErrNone);
	TInt size=0;
	TEST2(inputFile.Size(size), KErrNone);
	HBufC8* originalUtf8=HBufC8::New(size);
	HBufC16* generatedUnicode=HBufC16::New(size);
	HBufC8* generatedUtf8=HBufC8::New(size);
	RFile outputFile;
	TEST(originalUtf8!=NULL);
	TEST(generatedUnicode!=NULL);
	TEST(generatedUtf8!=NULL);
	TPtr8 ptr1=originalUtf8->Des();
	TEST2(inputFile.Read(ptr1), KErrNone);
	TEST(outputFile.Replace(fs, _L("c:\\ETHIOPIC.UNI"), EFileShareExclusive|EFileStream|EFileWrite)==KErrNone);
	TPtr16 ptr2=generatedUnicode->Des();
	TEST(CnvUtfConverter::ConvertToUnicodeFromUtf8(ptr2, *originalUtf8)==0);
	TPtr8 ptr3=generatedUtf8->Des();
	TEST(CnvUtfConverter::ConvertFromUnicodeToUtf8(ptr3, *generatedUnicode)==0);
	TEST(*generatedUtf8==*originalUtf8);
	TEST(outputFile.Write(TPtrC8(REINTERPRET_CAST(const TUint8*, generatedUnicode->Ptr()), generatedUnicode->Size()))==KErrNone);
	outputFile.Close();
	delete generatedUtf8;
	delete generatedUnicode;
	delete originalUtf8;
	inputFile.Close();
	fs.Close();
	TheTest.End();
	TheTest.Close();
	return KErrNone;
	}

