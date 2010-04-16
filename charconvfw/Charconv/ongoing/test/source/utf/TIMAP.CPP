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
#include <e32base.h>
#include <e32test.h>
#include <f32file.h>
#include <charconv.h>

///////////////////////////////////////////////////////////////////////////////////////

RTest TheTest(_L("TImap"));
	
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
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0574
@SYMTestCaseDesc        Tests for converting to Unicode from UTF- 7, from UTF-7 to Unicode
@SYMTestPriority        Medium
@SYMTestActions        	Tests for CCnvCharacterSetConverter::ConvertToUnicode(),
						CCnvCharacterSetConverter::ConvertFromUnicode() function
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void DoE32MainL()
	{
	RFs fileServerSession;
	CleanupClosePushL(fileServerSession);
	User::LeaveIfError(fileServerSession.Connect());
	CCnvCharacterSetConverter* characterSetConverter=CCnvCharacterSetConverter::NewLC();
	TInt state=CCnvCharacterSetConverter::KStateDefault;
	TheTest.Start(_L("Testing IMAP UTF-7"));
	TEST(characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierImapUtf7, fileServerSession)==CCnvCharacterSetConverter::EAvailable);
	TBuf16<256> originalUnicode;
	TBuf8<256> generatedUtf7;
	TBuf16<256> generatedUnicode;
	//
	TheTest.Next(_L("Empty descriptor"));
	originalUnicode=_L16("");
	TEST(characterSetConverter->ConvertFromUnicode(generatedUtf7, originalUnicode)==0);
	TEST(generatedUtf7==_L8(""));
	TEST(characterSetConverter->ConvertToUnicode(generatedUnicode, generatedUtf7, state)==0);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(generatedUnicode==originalUnicode);
	TheTest.Next(_L("Characters \" +&-~\\\""));
	originalUnicode=_L16(" +&-~\\");
	TEST(characterSetConverter->ConvertFromUnicode(generatedUtf7, originalUnicode)==0);
	TEST(generatedUtf7==_L8(" +&--~\\"));
	TEST(characterSetConverter->ConvertToUnicode(generatedUnicode, generatedUtf7, state)==0);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(generatedUnicode==originalUnicode);
	TheTest.Next(_L("Example quoted in RFC 2060 (Section 5.1.3)"));
	originalUnicode.Format(_L16("~peter/mail/%c%c%c/%c%c"), 0x65e5, 0x672c, 0x8a9e, 0x53f0, 0x5317);
	TEST(characterSetConverter->ConvertFromUnicode(generatedUtf7, originalUnicode)==0);
	TEST(generatedUtf7==_L8("~peter/mail/&ZeVnLIqe-/&U,BTFw-"));
	TEST(characterSetConverter->ConvertToUnicode(generatedUnicode, generatedUtf7, state)==0);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(generatedUnicode==originalUnicode);
	TheTest.Next(_L("Testing fix for defect EDNDSEF-4KMEUH in \"Symbian Defect Tracking v3.0\""));
	originalUnicode.Format(_L16("%c%c%c%c%c%c%c%c%c"), 0x30ad, 0x30e3, 0x30d3, 0x30cd, 0x30c3, 0x30c8, 0x3068, 0x306f, 0xff1f);
	TEST(characterSetConverter->ConvertFromUnicode(generatedUtf7, originalUnicode)==0);
	TEST(generatedUtf7==_L8("&MK0w4zDTMM0wwzDIMGgwb,8f-"));
	TEST(characterSetConverter->ConvertToUnicode(generatedUnicode, generatedUtf7, state)==0);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(generatedUnicode==originalUnicode);
	TBuf8<0x14> generatedUtf7_0x14;
	TEST(characterSetConverter->ConvertFromUnicode(generatedUtf7_0x14, originalUnicode)==3);
	TEST(generatedUtf7_0x14==_L8("&MK0w4zDTMM0wwzDI-"));
	TEST(characterSetConverter->ConvertToUnicode(generatedUnicode, generatedUtf7_0x14, state)==0);
	TEST(state==CCnvCharacterSetConverter::KStateDefault);
	TEST(generatedUnicode==originalUnicode.Left(6));
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

