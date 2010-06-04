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
#include <e32base.h>
#include <e32test.h>
#include <f32file.h>
#include <charconv.h>

///////////////////////////////////////////////////////////////////////////////////////

RTest TheTest(_L("TSNM"));

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
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0547
@SYMTestCaseDesc        Testing SNM files
@SYMTestPriority        Medium
@SYMTestActions         Tests for conversions from UIDs to  Standard names and MIB enums
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void DoE32MainL()
	{
	RFs fileServerSession;
	CleanupClosePushL(fileServerSession);
	User::LeaveIfError(fileServerSession.Connect());
	CCnvCharacterSetConverter* characterSetConverter=CCnvCharacterSetConverter::NewLC();
	TheTest.Start(_L(" @SYMTestCaseID:SYSLIB-CHARCONV-CT-0547 Testing SNM files (conversion between UIDs and Standard names/MIB enums) "));
	TEST(characterSetConverter->ConvertStandardNameOfCharacterSetToIdentifierL(_L8("ANSI_X3.4-1968"), fileServerSession)==KCharacterSetIdentifierAscii);
	TEST(characterSetConverter->ConvertStandardNameOfCharacterSetToIdentifierL(_L8("iso-ir-6"), fileServerSession)==KCharacterSetIdentifierAscii);
	TEST(characterSetConverter->ConvertStandardNameOfCharacterSetToIdentifierL(_L8("ANSI_X3.4-1986"), fileServerSession)==KCharacterSetIdentifierAscii);
	TEST(characterSetConverter->ConvertStandardNameOfCharacterSetToIdentifierL(_L8("ISO_646.irv:1991"), fileServerSession)==KCharacterSetIdentifierAscii);
	TEST(characterSetConverter->ConvertStandardNameOfCharacterSetToIdentifierL(_L8("ISO646-US"), fileServerSession)==KCharacterSetIdentifierAscii);
	TEST(characterSetConverter->ConvertStandardNameOfCharacterSetToIdentifierL(_L8("us"), fileServerSession)==KCharacterSetIdentifierAscii);
	TEST(characterSetConverter->ConvertStandardNameOfCharacterSetToIdentifierL(_L8("IBM367"), fileServerSession)==KCharacterSetIdentifierAscii);
	TEST(characterSetConverter->ConvertStandardNameOfCharacterSetToIdentifierL(_L8("cp367"), fileServerSession)==KCharacterSetIdentifierAscii);
	TEST(characterSetConverter->ConvertStandardNameOfCharacterSetToIdentifierL(_L8("csASCII"), fileServerSession)==KCharacterSetIdentifierAscii);
	TEST(characterSetConverter->ConvertMibEnumOfCharacterSetToIdentifierL(3, fileServerSession)==KCharacterSetIdentifierAscii);
	TEST(characterSetConverter->ConvertStandardNameOfCharacterSetToIdentifierL(_L8("DUMMY CHARACTER SET"), fileServerSession)==0x000eb205);
	TEST(characterSetConverter->ConvertMibEnumOfCharacterSetToIdentifierL(9415824, fileServerSession)==0x000eb205);
	TEST(characterSetConverter->ConvertMibEnumOfCharacterSetToIdentifierL(103, fileServerSession)==KCharacterSetIdentifierUtf7);
	TEST(characterSetConverter->ConvertMibEnumOfCharacterSetToIdentifierL(104, fileServerSession)==KCharacterSetIdentifierUtf7);
	TEST(characterSetConverter->ConvertMibEnumOfCharacterSetToIdentifierL(18, fileServerSession)==KCharacterSetIdentifierEucJpPacked);
	TEST(characterSetConverter->ConvertMibEnumOfCharacterSetToIdentifierL(17, fileServerSession)==KCharacterSetIdentifierShiftJis);
	TEST(characterSetConverter->ConvertMibEnumOfCharacterSetToIdentifierL(2026, fileServerSession)==KCharacterSetIdentifierBig5);
	TEST(characterSetConverter->ConvertMibEnumOfCharacterSetToIdentifierL(57, fileServerSession)==KCharacterSetIdentifierGbk);
	TEST(characterSetConverter->ConvertMibEnumOfCharacterSetToIdentifierL(2025, fileServerSession)==KCharacterSetIdentifierGbk);
	TEST(characterSetConverter->ConvertMibEnumOfCharacterSetToIdentifierL(4, fileServerSession)==KCharacterSetIdentifierIso88591);
	TEST(characterSetConverter->ConvertMibEnumOfCharacterSetToIdentifierL(1000, fileServerSession)==KCharacterSetIdentifierUcs2);
	TEST(characterSetConverter->ConvertStandardNameOfCharacterSetToIdentifierL(_L8("UTF-8"), fileServerSession)==KCharacterSetIdentifierUtf8);
	TEST(characterSetConverter->ConvertStandardNameOfCharacterSetToIdentifierL(_L8("windows-1252"), fileServerSession)==KCharacterSetIdentifierCodePage1252);
	TEST(characterSetConverter->ConvertStandardNameOfCharacterSetToIdentifierL(_L8("iso-ir-58"), fileServerSession)==KCharacterSetIdentifierGbk);
	TEST(characterSetConverter->ConvertStandardNameOfCharacterSetToIdentifierL(_L8("chinese"), fileServerSession)==KCharacterSetIdentifierGbk);
	TEST(characterSetConverter->ConvertStandardNameOfCharacterSetToIdentifierL(_L8("CHINESE"), fileServerSession)==KCharacterSetIdentifierGbk);
	TEST(characterSetConverter->ConvertStandardNameOfCharacterSetToIdentifierL(_L8("Big5"), fileServerSession)==KCharacterSetIdentifierBig5);
	TEST(characterSetConverter->ConvertStandardNameOfCharacterSetToIdentifierL(_L8("csISO2022JP"), fileServerSession)==KCharacterSetIdentifierIso2022Jp);
	TEST(characterSetConverter->ConvertStandardNameOfCharacterSetToIdentifierL(_L8("JIS_Encoding"), fileServerSession)==KCharacterSetIdentifierJis);
	TEST(characterSetConverter->ConvertCharacterSetIdentifierToMibEnumL(KCharacterSetIdentifierEucJpPacked, fileServerSession)==18);
	TEST(characterSetConverter->ConvertCharacterSetIdentifierToMibEnumL(KCharacterSetIdentifierUtf7, fileServerSession)==103);
	TEST(characterSetConverter->ConvertCharacterSetIdentifierToMibEnumL(KCharacterSetIdentifierGbk, fileServerSession)==113);
	HBufC8* const standardName1=characterSetConverter->ConvertCharacterSetIdentifierToStandardNameL(KCharacterSetIdentifierUtf8, fileServerSession);
	TEST(*standardName1==_L8("UTF-8"));
	delete standardName1;
	HBufC8* const standardName2=characterSetConverter->ConvertCharacterSetIdentifierToStandardNameL(KCharacterSetIdentifierShiftJis, fileServerSession);
	TEST(*standardName2==_L8("Shift_JIS"));
	delete standardName2;
	HBufC8* const standardName3=characterSetConverter->ConvertCharacterSetIdentifierToStandardNameL(KCharacterSetIdentifierBig5, fileServerSession);
	TEST(*standardName3==_L8("Big5"));
	delete standardName3;
	CleanupStack::PopAndDestroy(1); // characterSetConverter

	//Add more test steps for DEF085268. When a related charset ID with Name is not found in rom drive
	//and system hasn't been scanned yet, it will rescan the system. Otherwise, it will return 0.
	characterSetConverter=CCnvCharacterSetConverter::NewLC();
	TEST(characterSetConverter->ConvertStandardNameOfCharacterSetToIdentifierL(_L8("NONEXIST CHARACTER SET 1"), fileServerSession)==0);
	TEST(characterSetConverter->ConvertStandardNameOfCharacterSetToIdentifierL(_L8("DUMMY CHARACTER SET"), fileServerSession)==0x000eb205);
	TEST(characterSetConverter->ConvertStandardNameOfCharacterSetToIdentifierL(_L8("NONEXIST CHARACTER SET 2"), fileServerSession)==0);
	CleanupStack::PopAndDestroy(1); // characterSetConverter

	//Add more test steps for DEF085268. When a related charset name with ID is not found in rom drive
	//and system hasn't been scanned yet, it will rescan the system. Otherwise, it will return NULL.
	characterSetConverter=CCnvCharacterSetConverter::NewLC();
	HBufC8* const standardName4=characterSetConverter->ConvertCharacterSetIdentifierToStandardNameL(0xFFFFFFFE, fileServerSession);
	TEST(standardName4==NULL);
	delete standardName4;
	HBufC8* const standardName5=characterSetConverter->ConvertCharacterSetIdentifierToStandardNameL(0x000eb205, fileServerSession);
	TEST(*standardName5==_L8("Dummy character set"));
	delete standardName5;
	HBufC8* const standardName6=characterSetConverter->ConvertCharacterSetIdentifierToStandardNameL(0xFFFFFFFF, fileServerSession);
	TEST(standardName6==NULL);
	delete standardName6;
	CleanupStack::PopAndDestroy(1); // characterSetConverter


	//Add more test steps for DEF085268. When a related charset ID with MibEnum is not found in rom drive
	//and system hasn't been scanned yet, it will rescan the system. Otherwise, it will return 0.
	characterSetConverter=CCnvCharacterSetConverter::NewLC();
	TEST(characterSetConverter->ConvertMibEnumOfCharacterSetToIdentifierL(9999998, fileServerSession)==0);
	TEST(characterSetConverter->ConvertMibEnumOfCharacterSetToIdentifierL(9415824, fileServerSession)==0x000eb205);
	TEST(characterSetConverter->ConvertMibEnumOfCharacterSetToIdentifierL(9999999, fileServerSession)==0);
	CleanupStack::PopAndDestroy(1); // characterSetConverter

	//Add more test steps for DEF085268. When a related charset MibEnum with ID is not found in rom drive
	//and system hasn't been scanned yet, it will rescan the system. Otherwise, it will return 0.
	characterSetConverter=CCnvCharacterSetConverter::NewLC();
	TEST(characterSetConverter->ConvertCharacterSetIdentifierToMibEnumL(0xFFFFFFFE, fileServerSession)==0);
	TEST(characterSetConverter->ConvertCharacterSetIdentifierToMibEnumL(0x000eb205, fileServerSession)==9415824);
	TEST(characterSetConverter->ConvertCharacterSetIdentifierToMibEnumL(0xFFFFFFFF, fileServerSession)==0);
	CleanupStack::PopAndDestroy(2); // characterSetConverter and file session

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

