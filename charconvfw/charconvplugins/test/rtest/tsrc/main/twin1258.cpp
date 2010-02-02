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

const TUint KCharacterSetIdentifier=KCharacterSetIdentifierWin1258;

#ifdef __WINS__
_LIT(KInputUnicodeFilename, "c:\\test\\data\\win1258_uni_input.dat");
_LIT(KInputForeignFilename, "c:\\test\\data\\win1258_for_input.dat");
_LIT(KExpectUnicodeFilename, "c:\\test\\data\\win1258_uni_expect.dat");
_LIT(KExpectForeignFilename, "c:\\test\\data\\win1258_for_expect.dat");
#else
_LIT(KInputUnicodeFilename, "z:\\test\\data\\win1258_uni_input.dat");
_LIT(KInputForeignFilename, "z:\\test\\data\\win1258_for_input.dat");
_LIT(KExpectUnicodeFilename, "z:\\test\\data\\win1258_uni_expect.dat");
_LIT(KExpectForeignFilename, "z:\\test\\data\\win1258_for_expect.dat");
#endif

//  Local Functions
///////////////////////////////////////////////////////////////////////////////////////
RTest TheTest(_L("TestWin1258"));
	
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

static void ReadDescL(TDes8& aDes, const TDesC& aFilename, RFs& aFs)
	{
	RFile file;
	TInt err = file.Open(aFs, aFilename, EFileRead);
	TEST2(err, KErrNone);
	CleanupClosePushL(file);	
	err = file.Read(aDes);
	TEST2(err, KErrNone);
	CleanupStack::PopAndDestroy(&file);
	}
      
static void Merge_Big(TDesC8& aSource, TDes16& aTarget)
	{
	TInt length = aSource.Length();
	TInt i = 0;
	for(i=0;i<length-1;i++)
		{
		TInt64 temp = *(aSource.Ptr()+(i))*16*16 + *(aSource.Ptr()+i+1);
		aTarget.Append(temp);
		i++;
		}	
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
	
	TheTest.Next(_L("Encoding from Unicode to Foreign"));
	characterSetConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifier, *arrayOfCharacterSetsAvailable, fileServerSession);
	TBuf8<512> temp;
	TBuf16<256> originalUnicode;
	TBuf8<256> generatedForeign;
	TBuf16<256> generatedUnicode;
	ReadDescL(temp, KInputUnicodeFilename, fileServerSession);
	Merge_Big(temp, originalUnicode);
    TEST(characterSetConverter->ConvertFromUnicode(generatedForeign, originalUnicode) == 0);
	ReadDescL(temp, KExpectForeignFilename, fileServerSession);
	TEST(generatedForeign == temp);

	TheTest.Next(_L("Encoding from Foreign to Unicode"));	
	ReadDescL(generatedForeign, KInputForeignFilename, fileServerSession);
	TInt state=CCnvCharacterSetConverter::KStateDefault;
	TEST( 0 == characterSetConverter->ConvertToUnicode(generatedUnicode, generatedForeign, state));
	ReadDescL(temp, KExpectUnicodeFilename, fileServerSession);
	originalUnicode.Zero();
	Merge_Big(temp, originalUnicode); 
	TEST(generatedUnicode == originalUnicode);
	
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
