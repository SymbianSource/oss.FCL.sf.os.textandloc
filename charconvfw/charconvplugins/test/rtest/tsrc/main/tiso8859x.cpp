/*
* Copyright (c) 2000-2009 Nokia Corporation and/or its subsidiary(-ies).
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
#include "tiso8859x.h"

///////////////////////////////////////////////////////////////////////////////////////

RTest TheTest(_L("TISO8859X"));

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
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0541
@SYMTestCaseDesc        Tests for conversion from ISO 8859 to Unicode
@SYMTestPriority        Medium
@SYMTestActions         Tests for a filename and then convert to Unicode from ISO8859X
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void test1L()
	{
	TheTest.Next(_L(" @SYMTestCaseID:SYSLIB-CHARCONV-CT-0541 "));
	RFs fileServerSession;
	CleanupClosePushL(fileServerSession);
	User::LeaveIfError(fileServerSession.Connect());
	CCnvCharacterSetConverter* characterSetConverter=CCnvCharacterSetConverter::NewLC();
	CArrayFix<CCnvCharacterSetConverter::SCharacterSet>* arrayOfCharacterSetsAvailable=CCnvCharacterSetConverter::CreateArrayOfCharacterSetsAvailableLC(fileServerSession);
	TheTest.Printf(_L("Available:\n"));
	TInt i;
	for (i=arrayOfCharacterSetsAvailable->Count()-1; i>=0; --i)
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
	TInt state=CCnvCharacterSetConverter::KStateDefault;
	for (i=0; i<iso8859TestData.iNumberOfItems; ++i)
		{
		TBuf<50> message;
		message.Format(_L("Testing ISO 8859-%d"), iso8859TestData.iItems[i].iX);
		TheTest.Next(message);
		characterSetConverter->PrepareToConvertToOrFromL(iso8859TestData.iItems[i].iCharacterSetIdentifier, *arrayOfCharacterSetsAvailable, fileServerSession);
		TPtrC16 originalUnicode(iso8859TestData.iItems[i].iUnicode, iso8859TestData.iItems[i].iTextLength);
		TPtrC8 expectedIso8859(iso8859TestData.iItems[i].iIso8859, iso8859TestData.iItems[i].iTextLength);
		TBuf16<256> generatedUnicode;
		TEST(characterSetConverter->ConvertToUnicode(generatedUnicode, expectedIso8859, state)==0);
		TEST(generatedUnicode==originalUnicode);
		TBuf8<256> generatedIso8859;
		TEST(characterSetConverter->ConvertFromUnicode(generatedIso8859, originalUnicode)==0);
		TEST(state==CCnvCharacterSetConverter::KStateDefault);
		TEST(generatedIso8859==expectedIso8859);
		}
	CleanupStack::PopAndDestroy(3); // arrayOfCharacterSetsAvailable and characterSetConverter and fileServerSession
	}

/**
Test code for INC042690 - Bi-directional MIME types are not supported in Charconv
The bi-directional MIME types only indicate how to treat the layout of the mail,
the actual character conversion should be the same as for the exisiting ISO-8859-6/ISO-8859-8 plugins

@SYMTestCaseID          SYSLIB-CHARCONV-CT-0542
@SYMTestCaseDesc        Tests the Bi-directional MIME
@SYMTestPriority        Medium
@SYMTestActions         Tests for conversions of ISO_8859-6 UID to MIB
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void testInc042690L()
	{
	TheTest.Next(_L(" @SYMTestCaseID:SYSLIB-CHARCONV-CT-0542 Test for INC042690 "));

	RFs fileServerSession;
	CleanupClosePushL(fileServerSession);
	User::LeaveIfError(fileServerSession.Connect());
	CCnvCharacterSetConverter* characterSetConverter=CCnvCharacterSetConverter::NewLC();

	// check that the character set value of '81' is converted to the ISO_8859-6 UID (0x10008a29)
	TEST(characterSetConverter->ConvertMibEnumOfCharacterSetToIdentifierL(81,fileServerSession)==KCharacterSetIdentifierIso88596);
	TheTest.Printf(_L("\nMIB 81->Char Set ISO_8859-6 UID - OK"));

	// check that the character set value of '82' is converted to the ISO_8859-6 UID (0x10008a29)
	TEST(characterSetConverter->ConvertMibEnumOfCharacterSetToIdentifierL(82,fileServerSession)==KCharacterSetIdentifierIso88596);
	TheTest.Printf(_L("\nMIB 82->Char Set ISO_8859-6 UID - OK"));

	// check that the character set value of '84' is converted to the ISO_8859-8 UID (0x10008a2a)
	TEST(characterSetConverter->ConvertMibEnumOfCharacterSetToIdentifierL(84,fileServerSession)==KCharacterSetIdentifierIso88598);
	TheTest.Printf(_L("\nMIB 84->Char Set ISO_8859-8 UID - OK"));

	// check that the character set value of '85' is converted to the ISO_8859-8 UID (0x10008a2a)
	TEST(characterSetConverter->ConvertMibEnumOfCharacterSetToIdentifierL(85,fileServerSession)==KCharacterSetIdentifierIso88598);
	TheTest.Printf(_L("\nMIB 85->Char Set ISO_8859-8 UID - OK"));

	// check that the ISO_8859-6 UID (0x10008a29) is converted to the character set value of '9'
	TEST(characterSetConverter->ConvertCharacterSetIdentifierToMibEnumL(KCharacterSetIdentifierIso88596,fileServerSession)==9);
	TheTest.Printf(_L("\nChar Set ISO_8859-6 UID->MIB - OK"));

	// check that the ISO_8859-8 UID (0x10008a2a) is converted to the character set value of '11'
	TEST(characterSetConverter->ConvertCharacterSetIdentifierToMibEnumL(KCharacterSetIdentifierIso88598,fileServerSession)==11);
	TheTest.Printf(_L("\nChar Set ISO_8859-8 UID->MIB - OK"));

	TheTest.Printf(_L("\nTest for INC042690 complete:\n"));
	CleanupStack::PopAndDestroy(2); // characterSetConverter and fileServerSession
	}
/**
Test code for INC043911 - IANAMib 1014 not supported

@SYMTestCaseID          SYSLIB-CHARCONV-CT-0543
@SYMTestCaseDesc        Tests for CCnvCharacterSetConverter::ConvertMibEnumOfCharacterSetToIdentifierL() function
@SYMTestPriority        Medium
@SYMTestActions         Tests for a conversions of MIB to UTF-16BE UID
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void testInc043911L()
	{
	TheTest.Next(_L(" @SYMTestCaseID:SYSLIB-CHARCONV-CT-0543 Test for INC043911 "));

	RFs fileServerSession;
	CleanupClosePushL(fileServerSession);
	User::LeaveIfError(fileServerSession.Connect());
	CCnvCharacterSetConverter* characterSetConverter=CCnvCharacterSetConverter::NewLC();

	// check that the character set value of '1013' is converted to the UTF-16BE UID (0x101f4052)
	TEST(characterSetConverter->ConvertMibEnumOfCharacterSetToIdentifierL(1013,fileServerSession)==KCharacterSetIdentifierUnicodeBig);
	TheTest.Printf(_L("\nMIB 1013->Char Set UTF-16BE UID - OK"));

	// check that the character set value of '1014' is converted to the UTF-16LE UID (0x101f3fae)
	TEST(characterSetConverter->ConvertMibEnumOfCharacterSetToIdentifierL(1014,fileServerSession)==KCharacterSetIdentifierUnicodeLittle);
	TheTest.Printf(_L("\nMIB 1014->Char Set UTF-16LE UID - OK"));

	// check that the character set value of '1015' is converted to the UTF-16 UID (0x101ff492)
	TEST(characterSetConverter->ConvertMibEnumOfCharacterSetToIdentifierL(1015,fileServerSession)==KCharacterSetIdentifierUcs2);
	TheTest.Printf(_L("\nMIB 1015->Char Set UTF-16 UID - OK"));


	TheTest.Printf(_L("\nTest for INC043911 complete:\n"));
	CleanupStack::PopAndDestroy(2); // characterSetConverter and fileServerSession
	}
/**
Test code for DEF050040 - Propagated: Baltic (ISO8859-13) missing in Basic.txt

@SYMTestCaseID          SYSLIB-CHARCONV-CT-0544
@SYMTestCaseDesc        Tests for defect number DEF050040
@SYMTestPriority        Medium
@SYMTestActions         Tests for CCnvCharacterSetConverter::ConvertMibEnumOfCharacterSetToIdentifierL()
                        Tests for a conversions of MIB to ISO-8859-13 UID
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void testDef050040L()
	{
	TheTest.Next(_L(" @SYMTestCaseID:SYSLIB-CHARCONV-CT-0544 Test for DEF050040 "));

	RFs fileServerSession;
	CleanupClosePushL(fileServerSession);
	User::LeaveIfError(fileServerSession.Connect());
	CCnvCharacterSetConverter* characterSetConverter=CCnvCharacterSetConverter::NewLC();

	// check that the character set value of '109' is converted to the ISO-8859-13 UID (0x10008a2c)
	TEST(characterSetConverter->ConvertMibEnumOfCharacterSetToIdentifierL(109,fileServerSession)==KCharacterSetIdentifierIso885913);
	TheTest.Printf(_L("\nMIB 109->Char Set ISO-8859-13 UID - OK"));

	TheTest.Printf(_L("\nTest for DEF050040 complete:\n"));
	CleanupStack::PopAndDestroy(2); // characterSetConverter and fileServerSession
	}
/**
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0545
@SYMTestCaseDesc        Tests for conversion of  ISO8859 to Unicode
@SYMTestPriority        Medium
@SYMTestActions         Calls up conversion test functions of ISO8859 to Unicode
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void DoE32MainL()
	{
	TheTest.Start(_L("@SYMTestCaseID:SYSLIB-CHARCONV-CT-0545 Tests for conversion of  ISO8859 to Unicode"));
	test1L();
	testInc042690L();
	testInc043911L();
	testDef050040L();	
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

