/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Test to verify that a single charconv plugin with mulitple implementations
* can be built.
*
*/


#include <e32std.h>
#include <e32base.h>
#include <e32test.h>
#include <charconv.h>
#include <charactersetconverter.h>
#include "tis1620.h"

///////////////////////////////////////////////////////////////////////////////////////

RTest TheTest(_L("test multi plugins"));

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
@SYMTestCaseID          SYSLIB-CharConv-UT-1882
@SYMTestCaseDesc        Verify a charconv plugin with multiple implementations can be built.
@SYMTestPriority        Normal
@SYMTestActions         Load the two implementations in tis1620.dll which is
a charconv plugin that has two implementations.
@SYMTestExpectedResults Both implementations loaded successfully.
@SYMDEF                 DEF088036
*/
LOCAL_C void DoE32MainL()
	{
	TheTest.Start(_L(" @SYMTestCaseID:SYSLIB-CHARCONV-UT-1882 test DEF088036 started.\r\n "));
	CActiveScheduler* scheduler = new(ELeave) CActiveScheduler;
	CleanupStack::PushL(scheduler);
	CActiveScheduler::Install(scheduler);

	// load 2nd plug in

    TUid ImpId2={KTIS1620bImplUid};

    CCharacterSetConverterPluginInterface* ex =
    	CCharacterSetConverterPluginInterface::NewL(ImpId2);
	TEST(ex != NULL);
	delete ex;
	ex = NULL;

	// load 1st plugin
    TUid ImpId1={KTIS1620aImplUid};
    ex = CCharacterSetConverterPluginInterface::NewL(ImpId1);
	TEST(ex != NULL);
	delete ex;

	REComSession::FinalClose();

	CleanupStack::PopAndDestroy(scheduler);
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
