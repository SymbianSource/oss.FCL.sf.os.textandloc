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

const TUint KCharacterSetIdentifier=KCharacterSetIdentifierIscii;
//  Local Functions
///////////////////////////////////////////////////////////////////////////////////////
RTest TheTest(_L("TestISCII"));
	
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

LOCAL_C void TestConversionToUnicodeFromISCII(CCnvCharacterSetConverter& aCharacterSetConverter, const TDesC16& aExpectedUnicode, const TDesC8& aOriginalISCII, TInt aExpectedResult = 0)
    {
    TInt state=CCnvCharacterSetConverter::KStateDefault;
    TBuf16<KBufferLength> generatedUnicode;
    const TInt returnValue=aCharacterSetConverter.ConvertToUnicode(generatedUnicode, aOriginalISCII, state);
    TEST(returnValue == aExpectedResult );
    TEST(generatedUnicode==aExpectedUnicode);
    }

LOCAL_C void TestConversionToUnicodeFromTruncatedISCII(CCnvCharacterSetConverter& aCharacterSetConverter, const TDesC16&, const TDesC8& aOriginalISCII, TInt aExpectedResult = 0)
    {
    TInt state=CCnvCharacterSetConverter::KStateDefault;
    TBuf16<KBufferLength> generatedUnicode;
    const TInt returnValue=aCharacterSetConverter.ConvertToUnicode(generatedUnicode, aOriginalISCII, state);
    TEST(returnValue != aExpectedResult );
    }

LOCAL_C void TestConversionFromUnicodeToISCII(CCnvCharacterSetConverter& aCharacterSetConverter, const TDesC16& aOriginalUnicode, const TDesC8& aExpectedISCII, TInt aExpectedResult = 0)
    {
    TBuf8<KBufferLength> generatedISCII;
    const TInt returnValue=aCharacterSetConverter.ConvertFromUnicode(generatedISCII, aOriginalUnicode);
    TEST(returnValue == aExpectedResult);
    TEST(generatedISCII==aExpectedISCII);
    }

LOCAL_C void TestConversion( CCnvCharacterSetConverter& aCharacterSetConverter )
{
    TestConversionFromUnicodeToISCII(aCharacterSetConverter, _L16("\x0079"), _L8("\xef\x42\x79"));
    TestConversionToUnicodeFromISCII(aCharacterSetConverter, _L16("\x0079"), _L8("\x79"));

    TestConversionFromUnicodeToISCII(aCharacterSetConverter, _L16("\x0079\x007a\x0070\x0071\x0072\x0073\x0074\x0075"), _L8("\xef\x42\x79\x7a\x70\x71\x72\x73\x74\x75"));
    TestConversionToUnicodeFromISCII(aCharacterSetConverter, _L16("\x0079\x007a\x0070\x0071\x0072\x0073\x0074\x0075"), _L8("\x79\x7a\x70\x71\x72\x73\x74\x75"));
    TestConversionToUnicodeFromISCII(aCharacterSetConverter, _L16("\x0079\x007a\x0070\x0071\x0072\x0073\x0074\x0075\x0901"), _L8("\x79\x7a\x70\x71\x72\x73\x74\x75\xa1"));
    TestConversionToUnicodeFromISCII(aCharacterSetConverter, _L16("\x0079\x007a\x0070\x0071\x0072\x0073\x0074\x0075\x0901\x093d"), _L8("\x79\x7a\x70\x71\x72\x73\x74\x75\xa1\xea\xe9"));
    
    TestConversionFromUnicodeToISCII(aCharacterSetConverter, _L16("\x0901"), _L8("\xef\x42\xa1"));
    TestConversionToUnicodeFromISCII(aCharacterSetConverter, _L16("\x0901\x0079"), _L8("\xa1\x79"));
    TestConversionToUnicodeFromTruncatedISCII(aCharacterSetConverter, _L16("\x0901"), _L8("\xa1"));
    
    TestConversionFromUnicodeToISCII(aCharacterSetConverter, _L16("\x094d"), _L8("\xef\x42\xe8"));
    TestConversionFromUnicodeToISCII(aCharacterSetConverter, _L16("\x200c"), _L8("\xef\x42\xe8"));
    TestConversionToUnicodeFromISCII(aCharacterSetConverter, _L16("\x094d\x0079"), _L8("\xe8\x79"));
    
    TestConversionFromUnicodeToISCII(aCharacterSetConverter, _L16("\x0950"), _L8("\xef\x42\xa1\xe9"));
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
		
	characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifier, *arrayOfCharacterSetsAvailable, fileServerSession);

    TestConversion( *characterSetConverter );
    
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
