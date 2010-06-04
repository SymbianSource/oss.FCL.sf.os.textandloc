/*
* Copyright (c) 2004-2005 Nokia Corporation and/or its subsidiary(-ies). 
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
#include <convdata.h>
#include <utf.h>


///////////////////////////////////////////////////////////////////////////////////////

RTest TheTest(_L("T_Memory"));
	
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
	
class CSimple : public CBase
	{
public:
	CSimple(){};
	static CSimple* NewLC();
	};


CSimple* CSimple::NewLC()
	{
	CSimple* This = new (ELeave) CSimple;
	CleanupStack::PushL(This);
	return This;
	}


/**
 * CreateAndDestroyConverterL is run for increasing values of __UHEAP_FAILNEXT 
 */
void CreateAndDestroyConverterL(void)
	{
	// put some dummy items on the stack
	TInt numDummies=5;
	for (TInt i=0; i<numDummies; i++) 
		{
		CSimple* obj = CSimple::NewLC();
		
		// use to obj to fix compilier warning	
		obj = (CSimple *)NULL;
		}
	
	CCnvCharacterSetConverter* charConverter2 = 0; 
	charConverter2 = CCnvCharacterSetConverter::NewLC();

	CleanupStack::PopAndDestroy(charConverter2); 
	CleanupStack::PopAndDestroy(numDummies);
	}

/**
Test code for DEF041901 see teamtrack for more details 
Description of DEF041901:
If a memory allocation fails during CleanupStack::PushL in the NewLC, then
the destructor will be called. The destructor calls 
TTlsData::CharacterSetConverterIsBeingDestroyed(); which incorrectly frees
the thread local storage

@SYMTestCaseID          SYSLIB-CHARCONV-CT-0561
@SYMTestCaseDesc        Tests for defect number DEF041901
@SYMTestPriority        Medium
@SYMTestActions        	Tests for memory allocation failure.
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void TestDef41901L()
	{
	RFs fileServerSession;
	CleanupClosePushL(fileServerSession);
	User::LeaveIfError(fileServerSession.Connect());
	TheTest.Start(_L("T_memory Charconv test for DEF041901\n"));

	// create an instance of CCnvCharacterSetConverter
	CCnvCharacterSetConverter* charConverter1; 
	charConverter1 = CCnvCharacterSetConverter::NewLC();

	// conversion from native
	_LIT(KSourceString, "Skookumchuck");
	TBuf8<80> outputString; 
	CCnvCharacterSetConverter::TAvailability availability;
	TInt unconvertedCount;

	outputString.SetLength(0);
	availability = charConverter1->PrepareToConvertToOrFromL(KCharacterSetIdentifierSms7Bit, fileServerSession);
	TEST(availability == CCnvCharacterSetConverter::EAvailable);
	unconvertedCount = charConverter1->ConvertFromUnicode(outputString, KSourceString);
	TEST(unconvertedCount == 0);
	TheTest.Printf(_L("After first charConverter1 conversion.\n"));

	// perfrom heap checking on a second instance of CCnvCharacterSetConverter
	TInt pass=1;
	TInt ret=KErrNoMemory;
 	while (ret != KErrNone)
		{
		__UHEAP_FAILNEXT(pass); 
		TRAP(ret,CreateAndDestroyConverterL()); 
		__UHEAP_RESET;
		TheTest.Printf(_L("CCnvCharacterSetConverter OOM test: pass[%d] ret[%d]\n"),pass,ret); 
		pass++;
		} 
 
 	// now testing of charConverter2 is complete, test that charConverter1 is still ok.
 	// Note: this is the test code DEF041901 see teamtrack for more details.
	availability = charConverter1->PrepareToConvertToOrFromL(KCharacterSetIdentifierSms7Bit, fileServerSession);
	TEST(availability == CCnvCharacterSetConverter::EAvailable);
	unconvertedCount = charConverter1->ConvertFromUnicode(outputString, KSourceString);
	TEST(unconvertedCount == 0);
	
	TheTest.Printf(_L("Charconv test for DEF041901 passed ok\n")); 

	CleanupStack::PopAndDestroy(charConverter1);
	CleanupStack::PopAndDestroy();	// RFs
	}


LOCAL_C void DoE32MainL()
	{
	TestDef41901L();
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
