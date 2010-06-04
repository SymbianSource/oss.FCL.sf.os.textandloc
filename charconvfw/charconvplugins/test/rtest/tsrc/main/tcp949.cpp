/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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

//  Local Functions
///////////////////////////////////////////////////////////////////////////////////////
/*
Below four plugins all use cp949table.dll, and first three are same converter.
cp949 (code page 949) 0x200100FF
ksc5601 (Korean) 0x200113CD
EUCKR (EUC-KR) 0x2000E526
iso2022kr (Korean) 0x20010101
 */
RTest TheTest(_L("TestCP949"));

	
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

const TInt KBufferLength=100;

LOCAL_C void TestConversionToUnicodeFromCP949(CCnvCharacterSetConverter& aCharacterSetConverter, const TDesC16& aExpectedUnicode, const TDesC8& aOriginalCP949, TInt aExpectedResult = 0)
    {
    TInt state=CCnvCharacterSetConverter::KStateDefault;
    TBuf16<KBufferLength> generatedUnicode;
    const TInt returnValue=aCharacterSetConverter.ConvertToUnicode(generatedUnicode, aOriginalCP949, state);
    TEST(returnValue == aExpectedResult );
    TEST(generatedUnicode==aExpectedUnicode);
    }

LOCAL_C void TestConversionFromUnicodeToCP949(CCnvCharacterSetConverter& aCharacterSetConverter, const TDesC16& aOriginalUnicode, const TDesC8& aExpectedCP949, TInt aExpectedResult = 0)
    {
    TBuf8<KBufferLength> generatedCP949;
    const TInt returnValue=aCharacterSetConverter.ConvertFromUnicode(generatedCP949, aOriginalUnicode);
    TEST(returnValue == aExpectedResult);
    TEST(generatedCP949==aExpectedCP949);
    }

LOCAL_C void TestConversion( CCnvCharacterSetConverter& aCharacterSetConverter )
{
    TestConversionFromUnicodeToCP949(aCharacterSetConverter, _L16("\x0079"), _L8("\x79"));
    TestConversionToUnicodeFromCP949(aCharacterSetConverter, _L16("\x0079"), _L8("\x79"));

    TestConversionFromUnicodeToCP949(aCharacterSetConverter, _L16("\xAC02"), _L8("\x81\x41"));
    TestConversionToUnicodeFromCP949(aCharacterSetConverter, _L16("\xAC02"), _L8("\x81\x41"));
}

LOCAL_C void TestConversionIso2022kr( CCnvCharacterSetConverter& aCharacterSetConverter )
{
    TestConversionFromUnicodeToCP949(aCharacterSetConverter, _L16("\x0079"), _L8("\x1b\x24\x43\x0f\x79"));
    TestConversionToUnicodeFromCP949(aCharacterSetConverter, _L16("\x0079"), _L8("\x1b\x24\x43\x0f\x79"));

    TestConversionFromUnicodeToCP949(aCharacterSetConverter, _L16("\xc7b8"), _L8("\x1b\x24\x43\x0e\x20\x0f\x41"));
    TestConversionToUnicodeFromCP949(aCharacterSetConverter, _L16("\xc7b8\x0079"), _L8("\x1b\x24\x43\x0f\xa0\x41\x79"));

    TestConversionFromUnicodeToCP949(aCharacterSetConverter, _L16("\xAC02"), _L8("\x1b\x24\x43\x0f\x81\x41"));
    TestConversionToUnicodeFromCP949(aCharacterSetConverter, _L16("\xAC02"), _L8("\x1b\x24\x43\x0f\x81\x41"));
}

LOCAL_C void DoE32MainL()
	{
	RFs fileServerSession;
	CleanupClosePushL(fileServerSession);
	User::LeaveIfError(fileServerSession.Connect());
	CCnvCharacterSetConverter* characterSetConverter=CCnvCharacterSetConverter::NewLC();
	CArrayFix<CCnvCharacterSetConverter::SCharacterSet>* arrayOfCharacterSetsAvailable=\
		CCnvCharacterSetConverter::CreateArrayOfCharacterSetsAvailableLC(fileServerSession);
	
	TheTest.Start(_L("Available:\n"));
	for (TInt i=arrayOfCharacterSetsAvailable->Count()-1; i>=0; --i)
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
		
	TheTest.Next(_L("Testing CP949"));
	characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierCP949, *arrayOfCharacterSetsAvailable, fileServerSession);
    TestConversion( *characterSetConverter );

    TheTest.Next(_L("Testing ksc5601"));
    characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierKsc5601, *arrayOfCharacterSetsAvailable, fileServerSession);
    TestConversion( *characterSetConverter );

    TheTest.Next(_L("Testing EUCKR"));
    characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierEUCKR, *arrayOfCharacterSetsAvailable, fileServerSession);
    TestConversion( *characterSetConverter );

    TheTest.Next(_L("Testing Iso2022kr"));
    characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierIso2022kr, *arrayOfCharacterSetsAvailable, fileServerSession);
    TestConversionIso2022kr( *characterSetConverter );

 	CleanupStack::PopAndDestroy(3);
        }

//  Global Functions

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
