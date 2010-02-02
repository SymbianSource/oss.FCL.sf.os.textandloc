/*
* Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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


#include <e32test.h>
#include <bitdev.h>
#include <graphics/shapeimpl.h>
#include <badesca.h>
#include "testData.h"
#include <ecom/ecom.h>
#include <ecom/implementationproxy.h>
#include <e32math.h>
#include <graphics/openfontrasterizer.h>
#include <graphics/openfontconstants.h>

//add filenames for any test data here
const TText16* KTestFilenames[] =
	{
	//created from original iculayoutengine test data
	(const TText16*) L"z:\\test\\data\\tnr_dev_otshaperdata1.dat",
	//created from input data provided by licensee
	(const TText16*) L"z:\\test\\data\\tnr_dev_otshaperdata2.dat",
	//created from input data provided by licensee
	(const TText16*) L"z:\\test\\data\\tnr_dev_otshaperdata3.dat",
	//created from input data provided by licensee
	(const TText16*) L"z:\\test\\data\\tnr_dev_otshaperdata4.dat",
	// Data to test defect fix DEF078032
	(const TText16*) L"z:\\test\\data\\tnr_dev_otshaperdata5.dat",
	//created from input data provided by licensee
	(const TText16*) L"z:\\test\\data\\shaperkannadadata1.dat",
	// created from Kannada sample text
	(const TText16*) L"z:\\test\\data\\shaperkannadadata2.dat",
	// created from Kannada sample text
	(const TText16*) L"z:\\test\\data\\shaperkannadadata3.dat",
	// created from Gujarati sample text taken from the web
	(const TText16*) L"z:\\test\\data\\shapergujaratidata1.dat",
	// created from Gujarati sample text taken from the web
	(const TText16*) L"z:\\test\\data\\shapergujaratidata2.dat",
	// created from Gujarati sample text given by the licensee
	(const TText16*) L"z:\\test\\data\\shapergujaratidata3.dat",
	// created from Bengali sample text given by the licensee
	(const TText16*) L"z:\\test\\data\\shaperbengalidata1.dat",
	// created from Bengali sample text given by the licensee
	(const TText16*) L"z:\\test\\data\\shaperbengalidata2.dat",
	// created from Bengali sample text given by the licensee
	(const TText16*) L"z:\\test\\data\\shaperbengalidata3.dat",
	// created from Tamil sample text given by the licensee
	(const TText16*) L"z:\\test\\data\\shapertamildata1.dat",
	// created from Tamil sample text given by the licensee
	(const TText16*) L"z:\\test\\data\\shapertamildata2.dat",
	// created from Tamil sample text given by the licensee
	(const TText16*) L"z:\\test\\data\\shapertamildata3.dat",
	// created from Telugu sample text given by the licensee
	(const TText16*) L"z:\\test\\data\\shapertelugudata1.dat",
	// created from Telugu sample text given by the licensee
	(const TText16*) L"z:\\test\\data\\shapertelugudata2.dat",
	// created from Telugu sample text given by the licensee
	(const TText16*) L"z:\\test\\data\\shapertelugudata3.dat",
	//	Test for Gurmukhi digit
	(const TText16*) L"z:\\test\\data\\shapergurmukhi1.dat",
	(const TText16*) L"z:\\test\\data\\shapergurmukhi2.dat",
	(const TText16*) L"z:\\test\\data\\shapergurmukhi3.dat",
	(const TText16*) L"z:\\test\\data\\shapergurmukhi4.dat",
	(const TText16*) L"z:\\test\\data\\shapergurmukhi5.dat",
	//	Test for Malayalam digit
	(const TText16*) L"z:\\test\\data\\shapermalayalam1.dat",
	(const TText16*) L"z:\\test\\data\\shapermalayalam2.dat",
	(const TText16*) L"z:\\test\\data\\shapermalayalam3.dat",
	(const TText16*) L"z:\\test\\data\\shapermalayalam4.dat",
	(const TText16*) L"z:\\test\\data\\shapermalayalam5.dat"
	};

/**
Number of test data files of each of the scripts/languages bein tests.
Must change these if KTestFilnames[] above is changed
*/
const TInt KHindiTestDataIndex = 0;
const TInt KNumberOfHindiTestDataFiles = 5;
const TInt KKannadaTestDataIndex = 5;
const TInt KNumberOfKannadaTestDataFiles = 3;
const TInt KGujaratiTestDataIndex = 8;
const TInt KNumberOfGujaratiTestDataFiles = 3;
const TInt KBengaliTestDataIndex = 11;
const TInt KNumberOfBengaliTestDataFiles = 3;
const TInt KTamilTestDataIndex = 14;
const TInt KNumberOfTamilTestDataFiles = 3;
const TInt KTeluguTestDataIndex = 17;
const TInt KNumberOfTeluguTestDataFiles = 3;
const TInt KGurmukhiTestDataIndex = 20;
const TInt KNumberOfGurmukhiTestDataFiles = 5;
const TInt KMalayalamTestDataIndex = 25;
const TInt KNumberOfMalayalamTestDataFiles = 5;
	
const TUint32 KDevanagariScriptCode = 0x64657661;
const TUint32 KKannadaScriptCode = 0x6B6E6461;
const TUint32 KHindiLanguageCode = 0x48494E20;
const TUint32 KKannadaLanguageCode = 0x4B414E20;
const TUint32 KGujaratiScriptCode = 0x67756A72;
const TUint32 KGujaratiLanguageCode = 0x47554A20;
const TUint32 KBengaliScriptCode = 0x62656E67;
const TUint32 KBengaliLanguageCode = 0x42454E20;
const TUint32 KTamilScriptCode = 0x74616D6C;
const TUint32 KTamilLanguageCode = 0x54414D20;
const TUint32 KTeluguScriptCode = 0x74656C75;
const TUint32 KTeluguLanguageCode = 0x54454C20;
const TUint32 KGurmukhiScriptCode = 0x67757275;
const TUint32 KGurmukhiLanguageCode = 0;
const TUint32 KMalayalamScriptCode = 0x6d6c796d;
const TUint32 KMalayalamLanguageCode = 0x4d4c5220;


// For RTest
//**************************************************************************************
static RTest TheTest(_L("TC_SHAP_shapeText"));
static void Check(TInt aValue, TInt aLine)
	{
	if(!aValue)
		{
		TheTest(EFalse, aLine);
		}
	}

static  void Check(TInt aValue, TInt aExpected, TInt aLine)
	{
	if(aValue != aExpected)
		{
		RDebug::Print(_L("*** Expected error: %d, got: %d\r\n"), aExpected, aValue);
		TheTest(EFalse, aLine);
		}
	}

#define TEST2(aValue, aExpected) ::Check(aValue, aExpected, __LINE__)	
#define TEST(arg) ::Check((arg), __LINE__)

// Convenience methods
//**************************************************************************************

/* 
Used for cleanup of RImplInfoArray implementationArray below 
This method is stolen from FbsTop.cpp
*/
LOCAL_C void ResetAndDestroyRImplInfoPtrArray(TAny* aPtr)
	{
	RImplInfoPtrArray* array = reinterpret_cast <RImplInfoPtrArray*> (aPtr);
	array->ResetAndDestroy();
	}
	
/*
Load all ECOM implemented rasterizer DLLs. 
This method is stolen from CFbTop::LoadOpenFontLibraries()
*/
LOCAL_C void LoadOpenFontLibraries(CFontStore* aFontStore)
	{

	RImplInfoPtrArray implementationArray;
	TCleanupItem cleanup(ResetAndDestroyRImplInfoPtrArray, &implementationArray);
	CleanupStack::PushL(cleanup);
	TInt error;
	TInt ecomerror;
	TInt ecomnotready;
	TUid uid = {KUidOpenFontRasterizerPlunginInterface};

	// Making sure that no race situation arises
	// If ECom is not ready, give it another chance and try again. if it still doesn't work 
	// after the third try, then it just carries on quietly and fails... 
	for (ecomnotready =0; ecomnotready <3; ecomnotready++)
		{
		TRAP(ecomerror,REComSession::ListImplementationsL(uid,implementationArray));
		if (!ecomerror)
			{
			break;
			}
		else
			{
			ecomerror = 0; 	
			User::After(0);
			}
		}

	const TInt availCount = implementationArray.Count();
	for (TInt count=0;count<availCount;++count)
		{
		const CImplementationInformation* info = implementationArray[count];
		TUid rasterizerUid = info->ImplementationUid();
 		// Create a rasterizer
 		COpenFontRasterizer* rasterizer=0;
 		TRAP(error,rasterizer = COpenFontRasterizer::NewL(rasterizerUid));
 		if (!error)
   			{
   			// Install it in the font store.
   			TRAP(error,aFontStore->InstallRasterizerL(rasterizer));
   			if (error)
   				delete rasterizer;
   			}
		}
	CleanupStack::PopAndDestroy(&implementationArray); 	

	}
	
LOCAL_C RPointerArray<CTestData> SetupTestData(CDesC16ArrayFlat* aFilenames)	
	{
	RPointerArray<CTestData> testDataArr(1);// = new(ELeave) CArrayFixFlat<CTestData>(1);

	for (TInt i = 0; i<aFilenames->Count(); i++)
		{
		CTestData* temp = new(ELeave) CTestData;
		temp->Internalize((*aFilenames)[i]);
		testDataArr.AppendL(temp);	
		}
	
	return testDataArr;
	}
	
	
// test methods
//**************************************************************************************

/**
@file
@SYMTestCaseID				GRAPHICS-SYSLIB-ICULAYOUTENGINE-CT-1479
@SYMTestCaseDesc 			Simple test of the shaper
@SYMTestPriority 			High
@SYMTestActions  			Simple test to shape some text using the shaper, and test that the output is as expected. Does not perform any OOM testing.
@SYMTestExpectedResults		The test must exit cleanly and there should not be any User:84 errors, KERN-EXEC's or any memory leaks.
@SYMPREQ					PREQ18
*/
void doShapeText(CBitmapFont* font, CTestData& aTestData, const TUint32 aScript, 
				const TUint32 aLang, TBool aCheckOutput = EFalse)
	{
	TheTest.Next(_L("GRAPHICS-SYSLIB-ICULAYOUTENGINE-CT-1479 "));
	TInt err;

	//set up the shaper
	CShaper* theShaper = NULL;
	CShaperFactory* shaperFactory = NULL;

	RImplInfoPtrArray implementationArray;
	TCleanupItem cleanup(ResetAndDestroyRImplInfoPtrArray, &implementationArray);
	CleanupStack::PushL(cleanup);
	TInt error;
	TInt ecomerror;
	TInt ecomnotready;
	TUid uid = {KUidShaperFactoryPlunginInterface};

	// Making sure that no race situation arises between FBserv and Ecom
	// If ECom is not ready, give it another chance and try again. if it still doesn't work 
	// after the third try, then it just carries on quietly and fails... 
	for (ecomnotready =0; ecomnotready <3; ecomnotready++)
		{

       		TRAP(ecomerror,REComSession::ListImplementationsL(uid,implementationArray));
		if (!ecomerror)
			{
			break;
			}
		else
			{
			ecomerror = 0; 	
			User::After(0);
			}
		}

	const TInt availCount = implementationArray.Count();
	for (TInt count=0;count<availCount;++count)
		{
		const CImplementationInformation* info = implementationArray[count];
		TUid shaperFactoryUid = info->ImplementationUid();
 		// Create a shaper factory
 		TRAP(error,shaperFactory = CShaperFactory::NewL(shaperFactoryUid));
   		TEST2(error, KErrNone);
   		// Create a shaper
   		TRAPD(err, theShaper = shaperFactory->NewShaperL(font, aScript, aLang, &User::Heap()));
   		TEST2(err, KErrNone);
    	}
	CleanupStack::PopAndDestroy(&implementationArray); 	

	CleanupStack::PushL(shaperFactory);
	CleanupStack::PushL(theShaper);

	// create the data to be shaped
  	// this uses hindiTestData, defined in testData.h
  	CShaper::TInput input;
	input.iText = aTestData.iTextInput;
	input.iStart = aTestData.iStart;
	input.iEnd = aTestData.iEnd;

	TInt textLength = input.iText->Length();

	//create shape header, and shape the text
	TShapeHeader* output = NULL;
	err = theShaper->ShapeText(output, input, &User::Heap());
	TEST2(err,KErrNone);
	CleanupStack::PopAndDestroy(theShaper);
	CleanupStack::PopAndDestroy(shaperFactory);
	REComSession::FinalClose();

	CleanupStack::PushL(output);	
	
	if (aCheckOutput)
		{
		// check the contents of output
		TEST(output->iGlyphCount == aTestData.iGlyphCount);
		TEST(output->iCharacterCount == aTestData.iCharacterCount);

		// First iGlyphCount * 4 bytes of the output buffer contain the glyph codes as 2byte values
		// Compare against expected.
		TInt i=0;
		TUint32* shapePtr32 = (reinterpret_cast<TUint32*>(&output->iBuffer[0]));
		for (i=0; i < output->iGlyphCount; i++)
			{
			TEST2(*shapePtr32, (*aTestData.iGlyphs)[i]);
			shapePtr32++;
			}

		// next iGlyphCount * 4 bytes contain the postions in which the glyphs should be drawn, x and y axes.
		// Compare against expected
		TUint16* shapePtr16 = (reinterpret_cast<TUint16*>(shapePtr32));
		for (i=0; i < output->iGlyphCount*2; i++)
			{
			//check X or Y position
			TEST2(*shapePtr16,(*aTestData.iPositions)[i]);
			shapePtr16++;
			}

		// check advance
		TEST(*shapePtr16 == aTestData.iAdvance.iX);
		shapePtr16++;
		TEST(*shapePtr16 == aTestData.iAdvance.iY);
		shapePtr16++;

		// next iGlyphCount * 2 bytes contain the coresponding indices of this character in the original string.
		// Compare against expected
		for (i=0; i < output->iGlyphCount; i++)
			{
			TEST2(*shapePtr16, (*aTestData.iIndices)[i]);
			shapePtr16++;
			}
		}

	
	CleanupStack::PopAndDestroy(output);
	}

void shapeText(CBitmapFont* font, CTestData& aTestData, const TUint32 aScript, 
				const TUint32 aLang, TBool aCheckOutput = EFalse)
	{
	__UHEAP_MARK;
	TInt heapSizeAtStart = 0;
 	User::Heap().AllocSize(heapSizeAtStart);
 	
 	RDebug::Print(_L("Heap memory utilized is now %d\n"), heapSizeAtStart);

	doShapeText(font, aTestData, aScript, aLang, aCheckOutput);
 	// check the heap used by the shaper
 	RHeap* heap = &User::Heap();
 	heap->Check();
	TInt heapSizeAtEnd = 0;
	TInt heapCellsUsed = heap->AllocSize(heapSizeAtEnd);
 	if (heapCellsUsed)
 		{
 		TheTest.Printf(_L("This test leaked %d\n"), heapSizeAtEnd - heapSizeAtStart);
		}
	__UHEAP_MARKEND;	
	}

void doOomShapeText(CBitmapFont* font, CTestData& aTestData, const TUint32 aScript, const TUint32 aLang);
/**
@file
@SYMTestCaseID				GRAPHICS-SYSLIB-ICULAYOUTENGINE-CT-1480
@SYMTestCaseDesc 			Simple OOM test of shaper
@SYMTestPriority 			High
@SYMTestActions  			OOM testing for the shaper. Also ensures no leaks.
@SYMTestExpectedResults		The test must exit cleanly and there should not be any User:84 errors, KERN-EXEC's or any memory leaks.
@SYMPREQ					PREQ18
*/
void oomShapeText(CBitmapFont* font, CTestData& aTestData, const TUint32 aScript, const TUint32 aLang)
	{
	__UHEAP_MARK;
	TheTest.Next(_L("GRAPHICS-SYSLIB-ICULAYOUTENGINE-CT-1480 "));
	doOomShapeText(font,aTestData, aScript, aLang);		
	__UHEAP_MARKEND;
	}

void doOomShapeText(CBitmapFont* font, CTestData& aTestData, const TUint32 aScript, const TUint32 aLang)
	{
	TInt count = 0;
	TInt err = KErrNone;
	TInt heapCellsUsed, heapSizeAtEnd, heapSizeAtStart;
	CShaper* theShaper = NULL;	
	CShaperFactory* shaperFactory = NULL;
	TShapeHeader* output = NULL;
		
	User::Heap().AllocSize(heapSizeAtStart);

	// create the data to be shaped
	CShaper::TInput input;
	input.iText = aTestData.iTextInput;
	input.iStart = aTestData.iStart;
	input.iEnd = aTestData.iEnd;

	//set up shaper, shape, delete shaper in oom loop
	RImplInfoPtrArray implementationArray;
	TCleanupItem cleanup(ResetAndDestroyRImplInfoPtrArray, &implementationArray);
	CleanupStack::PushL(cleanup);
	TInt error;
	TInt ecomerror;
	TInt ecomnotready;
	TUid uid = {KUidShaperFactoryPlunginInterface};

	// Making sure that no race situation arises between FBserv and Ecom
	// If ECom is not ready, give it another chance and try again. if it still doesn't work 
	// after the third try, then it just carries on quietly and fails... 
	for (ecomnotready =0; ecomnotready <3; ecomnotready++)
		{

       		TRAP(ecomerror,REComSession::ListImplementationsL(uid,implementationArray));
		if (!ecomerror)
			{
			break;
			}
		else
			{
			ecomerror = 0; 	
			User::After(0);
			}
		}

	const TInt availCount = implementationArray.Count();
	for (TInt count=0;count<availCount;++count)
		{
		const CImplementationInformation* info = implementationArray[count];
		TUid shaperFactoryUid = info->ImplementationUid();
 		// Create a shaper factory
 		//CShaperFactory* shaperFactory = 0;
 		TRAP(error,shaperFactory = CShaperFactory::NewL(shaperFactoryUid));
   		TEST2(error, KErrNone);
   		//CleanupStack::PushL(shaperFactory);
		}
	CleanupStack::PopAndDestroy(&implementationArray); 	

	do
		{
		count += 1;
		__UHEAP_FAILNEXT(count);
	
		// Create a shaper
   		TRAPD(err, theShaper = shaperFactory->NewShaperL(font, aScript, aLang, &User::Heap()));
   		
		//shape text
		if (theShaper)
			{
			err = theShaper->ShapeText(output, input, &User::Heap());
			TEST2(err,KErrNone);
			}

		//free output; to be done by the caller of ShapeText
		delete output;
		output = NULL;		
			
		//does not check the output for now
		delete theShaper;
		delete shaperFactory;
		REComSession::FinalClose();
		
		}while ((err==KErrNoMemory)||(err==KErrGeneral));
	__UHEAP_RESET;

 	// check the heap used by the shaper
 	RHeap* heap = &User::Heap();
 	heap->Check();
 	heapCellsUsed = heap->AllocSize(heapSizeAtEnd);
 	if (heapCellsUsed)
 		{
 		TheTest.Printf(_L("This test leaked %d.\n"), heapSizeAtEnd - heapSizeAtStart);
		}
	}

void doRepeatShapeText(CBitmapFont* font, CTestData& aTestData, const TUint32 aScript, const TUint32 aLang);

/**
@file
@SYMTestCaseID				GRAPHICS-SYSLIB-ICULAYOUTENGINE-CT-1481
@SYMTestCaseDesc 			Tests that the shaper can handle multiple calls to ShapeText
@SYMTestPriority 			High
@SYMTestActions  			Makes multiple calls to CShaper::ShapeText with small amounts of text to be shaped
@SYMTestExpectedResults		The test must exit cleanly and there should not be any User:84 errors, KERN-EXEC's or any memory leaks.
@SYMPREQ					PREQ18
*/
void repeatShapeText(CBitmapFont* aFont, CTestData& aTestData, const TUint32 aScript, const TUint32 aLang)
	{
	__UHEAP_MARK;
	TheTest.Next(_L("GRAPHICS-SYSLIB-ICULAYOUTENGINE-CT-1481 "));
	doRepeatShapeText(aFont, aTestData, aScript, aLang);
	__UHEAP_MARKEND;
	}

void doRepeatShapeText(CBitmapFont* font, CTestData& aTestData, const TUint32 aScript, const TUint32 aLang)
	{
	TInt err;

	//set up the shaper
	CShaper* theShaper = NULL;
	CShaperFactory* shaperFactory = NULL;

	RImplInfoPtrArray implementationArray;
	TCleanupItem cleanup(ResetAndDestroyRImplInfoPtrArray, &implementationArray);
	CleanupStack::PushL(cleanup);
	TInt error;
	TInt ecomerror;
	TInt ecomnotready;
	TUid uid = {KUidShaperFactoryPlunginInterface};

	// Making sure that no race situation arises between FBserv and Ecom
	// If ECom is not ready, give it another chance and try again. if it still doesn't work 
	// after the third try, then it just carries on quietly and fails... 
	for (ecomnotready =0; ecomnotready <3; ecomnotready++)
		{

	   		TRAP(ecomerror,REComSession::ListImplementationsL(uid,implementationArray));
		if (!ecomerror)
			{
			break;
			}
		else
			{
			ecomerror = 0; 	
			User::After(0);
			}
		}

	const TInt availCount = implementationArray.Count();
	for (TInt count=0;count<availCount;++count)
		{
		const CImplementationInformation* info = implementationArray[count];
		TUid shaperFactoryUid = info->ImplementationUid();
		// Create a shaper factory
		TRAP(error,shaperFactory = CShaperFactory::NewL(shaperFactoryUid));
		TEST2(error, KErrNone);
		
		// Create a shaper
		TRAPD(err, theShaper = shaperFactory->NewShaperL(font, aScript, aLang, &User::Heap()));
		TEST2(err, KErrNone);
		}
	CleanupStack::PopAndDestroy(&implementationArray); 	

	CleanupStack::PushL(shaperFactory);
	CleanupStack::PushL(theShaper);

	// create the data to be shaped
	// this uses CTestData, defined in testData.h
	CShaper::TInput input;
	input.iText = aTestData.iTextInput;

	//create shape header, and shape the text
	TShapeHeader* output = NULL;

	for(TInt i=aTestData.iStart; i<aTestData.iEnd -10; i++)
		{
		//indicate which 10 chars to be shaped
		input.iStart = i;
		input.iEnd = i + 10;
		
		//shape text
		err = theShaper->ShapeText(output, input, &User::Heap());
		TEST2(err,KErrNone);

		//free output; to be done by the caller of ShapeText
		delete(output);
		output = NULL;		
		
		//does not check the output for now
		}

	//cleanup the shaper
	CleanupStack::PopAndDestroy(theShaper);
	CleanupStack::PopAndDestroy(shaperFactory);
	REComSession::FinalClose();
	}
	
/*
@file
@SYMTestCaseID				GRAPHICS-SYSLIB-ICULAYOUTENGINE-CT-3401
@SYMTestCaseDesc 			Tests that the shaper can handle calls to shapeText with multiple font sizes
@SYMTestPriority 			High
@SYMTestActions  			Makes multiple calls to CShaper::ShapeText with small amounts of text to be shaped and incremental font sizes
@SYMTestExpectedResults		The test must not show a memory leak at any font size
@SYMPREQ					DEF103042: TC_SHAP_shapeText test failing with alloc failure
**/	
void doRepeatShapeUsingVariousFontSizesTest(CFontStore* aFontStore, const TDesC aTypefaceName, const TDesC &aText1, 
												const TDesC &aText2, const TDesC &aText3, const TUint32 aScript, 
												const TUint32 aLang)
	{
    TheTest.Next(_L("GRAPHICS-SYSLIB-ICULAYOUTENGINE-CT-3401 "));
	TInt heapCellsUsed, heapSizeAtEnd, heapSizeAtStart;
	User::Heap().AllocSize(heapSizeAtStart);
	
	// Set up shaper factory
	// Set up the shaper
	CShaper* theShaper = NULL;
	CShaperFactory* shaperFactory = NULL;

	RImplInfoPtrArray implementationArray;
	TCleanupItem cleanup(ResetAndDestroyRImplInfoPtrArray, &implementationArray);
	CleanupStack::PushL(cleanup);
	TInt error;
	TInt ecomerror;
	TInt ecomnotready;
	TUid uid = {KUidShaperFactoryPlunginInterface};

	// Making sure that no race situation arises between FBserv and Ecom
	// If ECom is not ready, give it another chance and try again. if it still doesn't work 
	// after the third try, then it just carries on quietly and fails... 
	for (ecomnotready =0; ecomnotready <3; ecomnotready++)
		{
       	TRAP(ecomerror,REComSession::ListImplementationsL(uid,implementationArray));
		if (!ecomerror)
			{
			break;
			}
		else
			{
			ecomerror = 0; 	
			User::After(0);
			}
		}

	const TInt availCount = implementationArray.Count();
	for (TInt count=0;count<availCount;++count)
		{
		const CImplementationInformation* info = implementationArray[count];
		TUid shaperFactoryUid = info->ImplementationUid();
 		// Create a shaper factory
 		TRAP(error,shaperFactory = CShaperFactory::NewL(shaperFactoryUid));
   		TEST2(error, KErrNone);
		}
	
	CleanupStack::PopAndDestroy(&implementationArray); 	
	CleanupStack::PushL(shaperFactory);
	
	// create the data to be shaped
  	// this explicitely uses hindiTestData, defined in testData.h
  	CShaper::TInput input;
	input.iStart = 0;
	
	//create shape header, and shape the text
	TShapeHeader* output = NULL;
	
	CBitmapFont* font;
	
	// Test shaping for the Hindi texts for various font sizes
	TheTest.Printf(_L("Generating a random initial font size between 0 and 1 for this test\n"));
	TInt random = (Math::Random()>>11)%2;
	TheTest.Printf(_L("Random initial font size is %d. Testing upto size 300 with increments of 2\n"), random);
	for (TInt i = random; i <= 300; i+=2)
		{
		RDebug::Print(_L("Font Size: %d\n"), i);
		TFontSpec fontSpec(aTypefaceName,i*20);	
		aFontStore->GetNearestFontInTwips((CFont*&)font, fontSpec);	
		CleanupStack::PushL(font);	

		TRAPD(err, theShaper = shaperFactory->NewShaperL(font, aScript, aLang, &User::Heap()));
   		TEST2(err, KErrNone);
   		CleanupStack::PushL(theShaper);
   		
   		// Call the shaper twice because the first time the rasterizer uses memory to cache the tables
   		// We can then check the heap in the second call
   		input.iText = &aText1;
   		input.iEnd = aText1.Length();
   		err = theShaper->ShapeText(output, input, &User::Heap());
   		delete output;
   		TEST2(err,KErrNone);
   		__UHEAP_MARK;
   		err = theShaper->ShapeText(output, input, &User::Heap());
   		delete output;
   		__UHEAP_MARKEND;
		TEST2(err,KErrNone);
				
		input.iText = &aText2;
		input.iEnd = aText2.Length();
   		err = theShaper->ShapeText(output, input, &User::Heap());
   		delete output;
   		TEST2(err,KErrNone);
   		__UHEAP_MARK;
   		err = theShaper->ShapeText(output, input, &User::Heap());
   		delete output;
   		__UHEAP_MARKEND;
		TEST2(err,KErrNone);
		
		input.iText = &aText3;
		input.iEnd = aText3.Length();
   		err = theShaper->ShapeText(output, input, &User::Heap());
   		delete output;
   		TEST2(err,KErrNone);
   		__UHEAP_MARK;
   		err = theShaper->ShapeText(output, input, &User::Heap());
   		delete output;
   		__UHEAP_MARKEND;
		TEST2(err,KErrNone);
		
		CleanupStack::PopAndDestroy(theShaper);
		CleanupStack::Pop(font);   
		aFontStore->ReleaseFont(font);
		}
		
	CleanupStack::PopAndDestroy(shaperFactory);

	//close the ecom session opened by LoadOpenFontLibraries()
	REComSession::FinalClose();
	
	// check the heap used by the shaper
	RHeap* heap = &User::Heap();
	heap->Check();
	heapCellsUsed = heap->AllocSize(heapSizeAtEnd);
	if (heapCellsUsed)
		{
 		TheTest.Printf(_L("This test utilised %d bytes\n"), heapSizeAtEnd - heapSizeAtStart);
		}
	}
	
/**
@file
@SYMTestCaseID				GRAPHICS-SYSLIB-ICULAYOUTENGINE-CT-3403
@SYMTestCaseDesc 			Tests the shaper using Devanagari Unicode. Test include OOM tests (oomShapeText), repeated 
							calls to the shaper (repeatShapeText), simple shaping tests (shapeText), and repeatedly 
							calling the shaper with incremental font sizes.
@SYMTestPriority 			High
@SYMTestActions  			Performs various tests of the the shaper, calling CShaper::ShapeText in various use cases
@SYMTestExpectedResults		The test must exit cleanly and there should not be any User:84 errors, KERN-EXEC's or any memory leaks.
@SYMPREQ					PREQ19
*/
void HindiTestsL(RPointerArray<CTestData> aTestDataArr)
	{
	TheTest.Next(_L("GRAPHICS-SYSLIB-ICULAYOUTENGINE-CT-3403 "));
	TInt i;
	CBitmapFont* font;
	TInt err=KErrNone;	
	//the font store can use the normal user heap
	CFontStore* fontStore = CFontStore::NewL(&User::Heap());    
	fontStore->iKPixelWidthInTwips = 11860;
	fontStore->iKPixelHeightInTwips = 11860;
	CleanupStack::PushL(fontStore);

	//load all ecom implemented rasterizer dlls. installs the rasterizer.
	LoadOpenFontLibraries(fontStore);
	
	//add the required Hindi font file
	TRAP(err,fontStore->AddFileL(aTestDataArr[KHindiTestDataIndex]->iFilename));
	TEST(err==KErrNone);		
	
	
	//run all tests for TNR_Dev_OT test, which is at position 0 in the aTestDataArr
	TFontSpec fontSpec(aTestDataArr[KHindiTestDataIndex]->iTypeFaceName,12);	
	fontStore->GetNearestFontToDesignHeightInPixels((CFont*&)font, fontSpec);	
	CleanupStack::PushL(font);	
	
	TheTest.Next(_L("Repeat Hindi text shaping test\n"));
	doRepeatShapeText(font, *aTestDataArr[KHindiTestDataIndex], KDevanagariScriptCode, KHindiLanguageCode);
	repeatShapeText(font, *aTestDataArr[KHindiTestDataIndex], KDevanagariScriptCode, KHindiLanguageCode);
	
	TheTest.Next(_L("OOM Hindi text shaping test\n"));
#if defined(_DEBUG)
	doOomShapeText(font, *aTestDataArr[KHindiTestDataIndex], KDevanagariScriptCode, KHindiLanguageCode);
	oomShapeText(font, *aTestDataArr[KHindiTestDataIndex], KDevanagariScriptCode, KHindiLanguageCode);
#else
    TheTest.Printf(_L("This test is ignored for release version\n"));
#endif
	
	TheTest.Next(_L("Run simple Hindi shape test\n"));
	doShapeText(font, *aTestDataArr[KHindiTestDataIndex], KDevanagariScriptCode, KHindiLanguageCode, ETrue);
	shapeText(font, *aTestDataArr[KHindiTestDataIndex], KDevanagariScriptCode, KHindiLanguageCode, ETrue);
	
	CleanupStack::Pop(font);   
	fontStore->ReleaseFont(font);
	
	//for any other test data we have, run the simple shape text test only
	for(i=KHindiTestDataIndex+1; i<KHindiTestDataIndex+KNumberOfHindiTestDataFiles; i++)
		{
		TFontSpec fontSpec(aTestDataArr[i]->iTypeFaceName,12);	
		fontStore->GetNearestFontToDesignHeightInPixels((CFont*&)font, fontSpec);	

		// First run does not check heap... this ensures that any memory
		// stashed by the rasterizer does not show up as a leak.
		doShapeText(font, *aTestDataArr[i], KDevanagariScriptCode, KHindiLanguageCode, ETrue);
		shapeText(font, *aTestDataArr[i], KDevanagariScriptCode, KHindiLanguageCode, ETrue);

		fontStore->ReleaseFont(font);
		}
		
	// Now do the last test, the shaping test using various font sizes
	_LIT16(KHindi1,"\x0915\x094D\x0937\x0924\x094D\x0930\x093F\x092F\x0020\x0909\x0926\x094D\x0926\x0947\x0936\x094D\x0020\x0915\x094D\x0937\x093F\x092A\x094D\x0930");
	_LIT16(KHindi2,"\x092d\x0942\x0930\x094d\x092d\x0941\x0935\x0903\x0020\x0938\x094d\x0935\x0903\x0020\x0924\x0924\x094d\x0938\x0935\x093f\x0924\x0941\x0930\x094d\x0935\x0930\x0947\x0923\x094d\x092f\x0902");
	_LIT16(KHindi3,"\x092d\x0930\x094d\x0917\x094b\x0020\x0926\x0947\x0935\x0938\x094d\x092f\x0020\x0927\x0940\x092e\x0939\x093f\x0020\x0927\x093f\x092f\x094b\x0020\x092f\x094b\x0928\x0903\x0020\x092a\x094d\x0930\x091a\x094b\x0926\x092f\x093e\x0924\x094d\x0020");
	
	TheTest.Next(_L("Repeat Hindi shaping test using font sizes 20 to 6000\n"));  
	doRepeatShapeUsingVariousFontSizesTest(fontStore, aTestDataArr[0]->iTypeFaceName, KHindi1, KHindi2, KHindi3, KDevanagariScriptCode, KHindiLanguageCode);
		
	CleanupStack::PopAndDestroy(fontStore);
	}
	
/**
@file
@SYMTestCaseID				GRAPHICS-SYSLIB-ICULAYOUTENGINE-CT-3383-0001
@SYMTestCaseDesc 			Tests the shaper using Kannada Unicode. Test include OOM tests (oomShapeText), repeated 
							calls to the shaper (repeatShapeText), simple shaping tests (shapeText), and repeatedly 
							calling the shaper with incremental font sizes.
@SYMTestPriority 			High
@SYMTestActions  			Performs various tests of the the shaper, calling CShaper::ShapeText in various use cases
@SYMTestExpectedResults		The test must exit cleanly and there should not be any User:84 errors, KERN-EXEC's or any memory leaks.
@SYMPREQ					PREQ19
*/	
void KannadaTestsL(RPointerArray<CTestData> aTestDataArr)
	{
	TheTest.Next(_L("GRAPHICS-SYSLIB-ICULAYOUTENGINE-CT-3383-0001 "));
	TInt i;
	CBitmapFont* font;
	TInt err=KErrNone;	
	//the font store can use the normal user heap
	CFontStore* fontStore = CFontStore::NewL(&User::Heap());    
	fontStore->iKPixelWidthInTwips = 11860;
	fontStore->iKPixelHeightInTwips = 11860;
	CleanupStack::PushL(fontStore);

	//load all ecom implemented rasterizer dlls. installs the rasterizer.
	LoadOpenFontLibraries(fontStore);
	
	//add the required Kannada font file
	TRAP(err,fontStore->AddFileL(aTestDataArr[KKannadaTestDataIndex]->iFilename));
	TEST(err==KErrNone);		
	
	
	//run all tests for TNR_Dev_OT test, which is at position 0 in the aTestDataArr
	TFontSpec fontSpec(aTestDataArr[KKannadaTestDataIndex]->iTypeFaceName,12);	
	fontStore->GetNearestFontToDesignHeightInPixels((CFont*&)font, fontSpec);	
	CleanupStack::PushL(font);	
	
	TheTest.Next(_L("Repeat Kannada text shaping test\n"));
	doRepeatShapeText(font, *aTestDataArr[KKannadaTestDataIndex], KKannadaScriptCode, KKannadaLanguageCode);
	repeatShapeText(font, *aTestDataArr[KKannadaTestDataIndex], KKannadaScriptCode, KKannadaLanguageCode);
	
	TheTest.Next(_L("OOM Kannada text shaping test\n"));
#if defined(_DEBUG)
	doOomShapeText(font, *aTestDataArr[KKannadaTestDataIndex], KKannadaScriptCode, KKannadaLanguageCode);
	oomShapeText(font, *aTestDataArr[KKannadaTestDataIndex], KKannadaScriptCode, KKannadaLanguageCode);
#else
    TheTest.Printf(_L("This test is ignored for release version\n"));
#endif
	
	TheTest.Next(_L("Run simple Kannada shape test\n"));
	doShapeText(font, *aTestDataArr[KKannadaTestDataIndex], KKannadaScriptCode, KKannadaLanguageCode, ETrue);
	shapeText(font, *aTestDataArr[KKannadaTestDataIndex], KKannadaScriptCode, KKannadaLanguageCode, ETrue);
	
	//for any other test data we have, run the simple shape text test only
	for(i=KKannadaTestDataIndex+1; i<KKannadaTestDataIndex+KNumberOfKannadaTestDataFiles; i++)
		{
		TFontSpec fontSpec(aTestDataArr[i]->iTypeFaceName,12);	
		fontStore->GetNearestFontToDesignHeightInPixels((CFont*&)font, fontSpec);	

		// First run does not check heap... this ensures that any memory
		// stashed by the rasterizer does not show up as a leak.
		doShapeText(font, *aTestDataArr[i], KKannadaScriptCode, KKannadaLanguageCode, ETrue);
		shapeText(font, *aTestDataArr[i], KKannadaScriptCode, KKannadaLanguageCode, ETrue);

		fontStore->ReleaseFont(font);
		}
		
	// Now do the last test, the shaping test using various font sizes
	_LIT16(KKannada1,"\x0CB6\x0CCD\x0CB0\x0CC0\x0020\x0CAD\x0C97\x0CB5\x0CBE\x0CA8\x0CC1\x0CB5\x0CBE\x0C9A\x0C95\x0CC1\x0CA4\x0CB8\x0CCD\x0CA4\x0CCD\x0CB5\x0CBE\x0020\x0C95\x0CB6\x0CCD\x0CAE\x0CB2\x0CAE\x0CBF\x0CA6\x0C82\x0020\x0CB5\x0CBF\x0CB7\x0CAE\x0020\x0CB8\x0CAE\x0CC1\x0CAA\x0CB8\x0CCD\x0CA5\x0CBF\x0CA4\x0CAE\x0CCD");
	_LIT16(KKannada2,"\x0C85\x0CA8\x0CBE\x0CB0\x0CCD\x0CAF\x0C9C\x0CC1\x0CB7\x0CCD\x0CA0\x0CAE\x0CB8\x0CCD\x0CB5\x0CB0\x0CCD\x0C97\x0CCD\x0CAF\x0CAE\x0C95\x0CC0\x0CB0\x0CCD\x0CA4\x0CBF\x0C95\x0CB0\x0CAE\x0CB0\x0CCD\x0C9C\x0CC1\x0CA8");
	_LIT16(KKannada3,"\x0C95\x0CCD\x0CB2\x0CC8\x0CAC\x0CCD\x0CAF\x0C82\x0020\x0CAE\x0CBE\x0020\x0CB8\x0CCD\x0CAE\x0020\x0C97\x0CAE\x0C83\x0020\x0CAA\x0CBE\x0CB0\x0CCD\x0CA5\x0020\x0CA8\x0CC8\x0CA4\x0CA4\x0CCD\x0CA4\x0CCD\x0CB5\x0CAF\x0CCD\x0CAF\x0CC1\x0CAA\x0CAA\x0CA7\x0CCD\x0CAF\x0CA4\x0CC7");
	
	TheTest.Next(_L("Repeat Kannada shaping test using font sizes 20 to 6000\n"));  
	doRepeatShapeUsingVariousFontSizesTest(fontStore, aTestDataArr[5]->iTypeFaceName, KKannada1, KKannada2, KKannada3, KKannadaScriptCode, KKannadaLanguageCode);

	CleanupStack::Pop(font);   
	fontStore->ReleaseFont(font);

	
	CleanupStack::PopAndDestroy(fontStore);
	}
	
/**
@file
@SYMTestCaseID				GRAPHICS-SYSLIB-ICULAYOUTENGINE-CT-3383-0002
@SYMTestCaseDesc 			Tests the shaper using Kannada Unicode. Test include OOM tests (oomShapeText), repeated 
							calls to the shaper (repeatShapeText), simple shaping tests (shapeText), and repeatedly 
							calling the shaper with incremental font sizes.
@SYMTestPriority 			High
@SYMTestActions  			Performs various tests of the the shaper, calling CShaper::ShapeText in various use cases
@SYMTestExpectedResults		The test must exit cleanly and there should not be any User:84 errors, KERN-EXEC's or any memory leaks.
@SYMPREQ					PREQ19
*/	
void GujaratiTestsL(RPointerArray<CTestData> aTestDataArr)
	{
	TheTest.Next(_L("GRAPHICS-SYSLIB-ICULAYOUTENGINE-CT-3383-0002 "));
	TInt i;
	CBitmapFont* font;
	TInt err=KErrNone;	
	//the font store can use the normal user heap
	CFontStore* fontStore = CFontStore::NewL(&User::Heap());    
	fontStore->iKPixelWidthInTwips = 11860;
	fontStore->iKPixelHeightInTwips = 11860;
	CleanupStack::PushL(fontStore);

	//load all ecom implemented rasterizer dlls. installs the rasterizer.
	LoadOpenFontLibraries(fontStore);
	
	//add the required Gujarati font file
	TRAP(err,fontStore->AddFileL(aTestDataArr[KGujaratiTestDataIndex]->iFilename));
	TEST(err==KErrNone);		
	
	
	//run all tests for TNR_Dev_OT test, which is at position 0 in the aTestDataArr
	TFontSpec fontSpec(aTestDataArr[KGujaratiTestDataIndex]->iTypeFaceName,12);	
	fontStore->GetNearestFontToDesignHeightInPixels((CFont*&)font, fontSpec);	
	CleanupStack::PushL(font);	
	
	TheTest.Next(_L("Repeat Gujarati text shaping test\n"));
	doRepeatShapeText(font, *aTestDataArr[KGujaratiTestDataIndex], KGujaratiScriptCode, KGujaratiLanguageCode);
	repeatShapeText(font, *aTestDataArr[KGujaratiTestDataIndex], KGujaratiScriptCode, KGujaratiLanguageCode);
	
	TheTest.Next(_L("OOM Gujarati text shaping test\n"));
#if defined(_DEBUG)
	doOomShapeText(font, *aTestDataArr[KGujaratiTestDataIndex], KGujaratiScriptCode, KGujaratiLanguageCode);
	oomShapeText(font, *aTestDataArr[KGujaratiTestDataIndex], KGujaratiScriptCode, KGujaratiLanguageCode);
#else
    TheTest.Printf(_L("This test is ignored for release version\n"));
#endif
	
	TheTest.Next(_L("Run simple Gujarati shape test\n"));
	doShapeText(font, *aTestDataArr[KGujaratiTestDataIndex], KGujaratiScriptCode, KGujaratiLanguageCode, ETrue);
	shapeText(font, *aTestDataArr[KGujaratiTestDataIndex], KGujaratiScriptCode, KGujaratiLanguageCode, ETrue);
	
	//for any other test data we have, run the simple shape text test only
	for(i=KGujaratiTestDataIndex+1; i<KGujaratiTestDataIndex+KNumberOfGujaratiTestDataFiles; i++)
		{
		TFontSpec fontSpec(aTestDataArr[i]->iTypeFaceName,12);	
		fontStore->GetNearestFontToDesignHeightInPixels((CFont*&)font, fontSpec);	

		// First run does not check heap... this ensures that any memory
		// stashed by the rasterizer does not show up as a leak.
		doShapeText(font, *aTestDataArr[i], KGujaratiScriptCode, KGujaratiLanguageCode, ETrue);
		shapeText(font, *aTestDataArr[i], KGujaratiScriptCode, KGujaratiLanguageCode, ETrue);

		fontStore->ReleaseFont(font);
		}
		
	// Now do the last test, the shaping test using various font sizes
	_LIT16(KGujarati1,"\x0AAD\x0ABE\x0AB5\x0ABE\x0AA4\x0ACD\x0AAE\x0A95\x0020\x0AAA\x0AA6\x0ACD\x0AAF\x0ABE\x0AA8\x0AC1\x0AB5\x0ABE\x0AA6\x0020\x0020\x002D\x0020\x0AB6\x0ACD\x0AB0\x0AC0\x0020\x0AAF\x0ACB\x0A97\x0AC7\x0AB6\x0ACD\x0AB5\x0AB0\x0A9C\x0AC0");
	_LIT16(KGujarati2,"\x0AB5\x0ABF\x0AA8\x0ACD\x0AA1\x0ACB\x0A9D\x0020\x0AB5\x0ABF\x0AB8\x0ACD\x0A9F\x0ABE\x0020\x002D\x0020\x0A86\x0A82\x0AA4\x0AB0\x0AB0\x0ABE\x0AB7\x0ACD\x0A9F\x0ACD\x0AB0\x0ABF\x0AAF\x0A95\x0AB0\x0AA3\x0020\x0AB5\x0ABF\x0AB6\x0AC7\x0AA8\x0AC0\x0020\x0A9C\x0ABE\x0AA3\x0A95\x0ABE\x0AB0\x0AC0");
	_LIT16(KGujarati3,"\x0AAE\x0ABE\x0A88\x0A95\x0ACD\x0AB0\x0ACB\x0AB8\x0ACB\x0AAB\x0ACD\x0A9F\x0AA8\x0ABE\x0020\x0A86\x0020\x0A86\x0A82\x0AA4\x0AB0\x0AB0\x0ABE\x0AB7\x0ACD\x0A9F\x0ACD\x0AB0\x0ABF\x0AAF\x0020\x0AAA\x0ACB\x0AB0\x0ACD\x0A9F\x0AB2\x0020\x0AB5\x0ABF\x0AB6\x0AC7\x0020\x0AB5\x0AA7\x0AC1\x0020\x0A9C\x0ABE\x0AA3\x0ACB\x002E\x0020\x0AB5\x0ABF\x0AB8\x0ACD\x0A9F\x0ABE\x0A8F\x0020\x0AA6\x0AC1\x0AA8\x0ABF\x0AAF\x0ABE\x0AAD\x0AB0\x0AA8\x0AC0\x0020\x0AAD\x0ABE\x0AB7\x0ABE\x0A93\x0020\x0AAE\x0ABE\x0A9F\x0AC7\x0020\x0AA6\x0ACD\x0AB5\x0ABE\x0AB0\x0020\x0A96\x0ACB\x0AB2\x0AC0\x0020\x0AA8\x0ABE\x0A96\x0ACD\x0AAF\x0ABE\x0020\x0A9B\x0AC7");
	
	TheTest.Next(_L("Repeat Gujarati shaping test using font sizes 20 to 6000\n"));  
	doRepeatShapeUsingVariousFontSizesTest(fontStore, aTestDataArr[8]->iTypeFaceName, KGujarati1, KGujarati2, KGujarati3, KGujaratiScriptCode, KGujaratiLanguageCode);

	CleanupStack::Pop(font);   
	fontStore->ReleaseFont(font);

	
	CleanupStack::PopAndDestroy(fontStore);
	}

/**
@SYMTestCaseID          GRAPHICS-TI18N-ICULAYOUTENGINE-CT-4007
@SYMTestCaseDesc        Case to do Gurmukhi component test
						It covers all Iculayout components cases
@SYMTestPriority        High
@SYMTestActions         Iterate Gurmukhi test data, each test data corresponds with a case
@SYMTestExpectedResults No error returned
@SYMPREQ 1922: Gurmukhi support
*/
void GurmukhiTestsL(RPointerArray<CTestData> aTestDataArr)
	{
	
	TInt i;
	CBitmapFont* font;
	TInt err=KErrNone;	
	//the font store can use the normal user heap
	CFontStore* fontStore = CFontStore::NewL(&User::Heap());    
	fontStore->iKPixelWidthInTwips = 11860;
	fontStore->iKPixelHeightInTwips = 11860;
	CleanupStack::PushL(fontStore);

	//load all ecom implemented rasterizer dlls. installs the rasterizer.
	LoadOpenFontLibraries(fontStore);
	
	//add the required Gurmukhi font file
	TRAP(err,fontStore->AddFileL(aTestDataArr[KGurmukhiTestDataIndex]->iFilename));
	TEST(err==KErrNone);		
	
	
	TFontSpec fontSpec(aTestDataArr[KGurmukhiTestDataIndex]->iTypeFaceName,12);	
	fontStore->GetNearestFontToDesignHeightInPixels((CFont*&)font, fontSpec);	
	CleanupStack::PushL(font);	
	
	TheTest.Next(_L("@SYMTestCaseID GRAPHICS-TI18N-ICULAYOUTENGINE-CT-4007 Repeat Gurmukhi text shaping test\n"));
	doRepeatShapeText(font, *aTestDataArr[KGurmukhiTestDataIndex], KGurmukhiScriptCode, KGurmukhiLanguageCode);
	repeatShapeText(font, *aTestDataArr[KGurmukhiTestDataIndex], KGurmukhiScriptCode, KGurmukhiLanguageCode);
	
	TheTest.Next(_L("OOM Gurmukhi text shaping test\n"));
#if defined(_DEBUG)
	doOomShapeText(font, *aTestDataArr[KGurmukhiTestDataIndex], KGurmukhiScriptCode, KGurmukhiLanguageCode);
	oomShapeText(font, *aTestDataArr[KGurmukhiTestDataIndex], KGurmukhiScriptCode, KGurmukhiLanguageCode);
#else
	TheTest.Printf(_L("This test is ignored for release version\n"));
#endif

	TheTest.Next(_L("Run simple Gurmukhi shape test\n"));
	doShapeText(font, *aTestDataArr[KGurmukhiTestDataIndex], KGurmukhiScriptCode, KGurmukhiLanguageCode, ETrue);
	shapeText(font, *aTestDataArr[KGurmukhiTestDataIndex], KGurmukhiScriptCode, KGurmukhiLanguageCode, ETrue);
	
	//for any other test data we have, run the simple shape text test only
	for(i=KGurmukhiTestDataIndex+1; i<KGurmukhiTestDataIndex+KNumberOfGurmukhiTestDataFiles; i++)
		{
		TFontSpec fontSpec(aTestDataArr[i]->iTypeFaceName,12);	
		fontStore->GetNearestFontToDesignHeightInPixels((CFont*&)font, fontSpec);	

		// First run does not check heap... this ensures that any memory
		// stashed by the rasterizer does not show up as a leak.
		doShapeText(font, *aTestDataArr[i], KGurmukhiScriptCode, KGurmukhiLanguageCode, ETrue);
		shapeText(font, *aTestDataArr[i], KGurmukhiScriptCode, KGurmukhiLanguageCode, ETrue);

		fontStore->ReleaseFont(font);
		}
		
	// Now do the last test, the shaping test using various font sizes
	_LIT16(KGurmukhi1,"\x0a28\x0a2e\x0a38\x0a15\x0a3e\x0a30\x0a26\x0a\x3e\x0a28\x0a3f\x0a1a\x0a3f\x0a70\x0a26\x0a41\x0020\x0a28\x0a3f\x0a17\x0a4d\x0a30\x0a39\x0a3f\x0a2a\x0a70\x0a16\x0a40\x0a05\x0a32\x0a4b\x0a2a\x0a70\x0a16\x0a40\x0a05\x0a32\x0a4b\x0a2a\x0a30\x0a09\x0a2a\x0a15\x0a3e\x0a30\x0a3f\x0a06\x0a2a\x0a4d\x0a30\x0a24\x0a3e\x0a2a\x0a3f");
	_LIT16(KGurmukhi2,"\x0a2a\x0a4d\x0a30\x0a24\x0a3f\x0a2a\x0a3e\x0a32\x0a47\x0020\x0a2a\x0a4d\x0a30\x0a2c\x0a32\x0a1a\x0a70\x0a21\x0a2b\x0a3f\x0a30\x0a70\x0a28\x0a4d\x0a39\x0a4d\x0a39\x0a3f\x0020\x0a2b\x0a41\x0a32\x0a35\x0a24\x0a2c\x0a4d\x0a30\x0a3f\x0a25\x0a3e\x0a2c\x0a4d\x0a30\x0a39\x0a2e\x0a3e\x0a26\x0a3f\x0020\x0a2c\x0a3e\x0a1b\x0a30\x0a2c\x0a3f\x0a38\x0a4d\x0a35\x0a70\x0a2d\x0a30\x0a2d\x0a4d\x0a30\x0a2e\x0a39\x0a41\x0a2d\x0a2f\x0a4b\x0a2d\x0a17\x0a35\x0a70\x0a24");
	_LIT16(KGurmukhi3,"\x0a2e\x0a3e\x0a23\x0a40\x0a06\x0a2e\x0a4b\x0a24\x0a38\x0a30\x0a40\x0a06\x0a2f\x0a3e\x0a28\x0a5c\x0a40\x0a0f\x0a2f\x0a15\x0a40\x0a28\x0a3e\x0a30\x0a35\x0a3f\x0a70\x0a26\x0a41\x0020\x0a30\x0a2a\x0a38\x0a40\x0a32\x0a17\x0a3e\x0a35\x0a23\x0a3f\x0a06\x0a32\x0a4b\x0a5c\x0a40\x0a05\x0a39\x0a3f\x0a35\x0a30\x0a28\x0a41\x0a35\x0a40\x0a06\x0a39\x0a3f\x0a06\x0a5c\x0a5c\x0a15\x0a3f\x0a28\x0a2e\x0a38\x0a15\x0a3e\x0a30\x0a26\x0a3e\x0a28\x0a3f\x0a1a\x0a3f\x0a70\x0a26\x0a41\x0020");

	TheTest.Next(_L("Repeat Gurmukhi shaping test using font sizes 20 to 6000\n"));  
	doRepeatShapeUsingVariousFontSizesTest(fontStore, aTestDataArr[KGurmukhiTestDataIndex]->iTypeFaceName, KGurmukhi1, KGurmukhi2, KGurmukhi3, KGurmukhiScriptCode, KGurmukhiLanguageCode);

	CleanupStack::Pop(font);   
	fontStore->ReleaseFont(font);

	
	CleanupStack::PopAndDestroy(fontStore);
	}


/**
@SYMTestCaseID          GRAPHICS-TI18N-ICULAYOUTENGINE-CT-4008
@SYMTestCaseDesc        Case to do Malayalam component test
						It covers all Iculayout components cases
@SYMTestPriority        High
@SYMTestActions         Iterate Malayalam test data, each test data corresponds with a case
@SYMTestExpectedResults No error returned
@SYMPREQ 1922: Malayalam support
*/
void MalayalamTestsL(RPointerArray<CTestData> aTestDataArr)
	{
	
	TInt i;
	CBitmapFont* font;
	TInt err=KErrNone;	
	//the font store can use the normal user heap
	CFontStore* fontStore = CFontStore::NewL(&User::Heap());    
	fontStore->iKPixelWidthInTwips = 11860;
	fontStore->iKPixelHeightInTwips = 11860;
	CleanupStack::PushL(fontStore);

	//load all ecom implemented rasterizer dlls. installs the rasterizer.
	LoadOpenFontLibraries(fontStore);
	
	//add the required Malayalam font file
	TRAP(err,fontStore->AddFileL(aTestDataArr[KMalayalamTestDataIndex]->iFilename));
	TEST(err==KErrNone);		
	
	
	TFontSpec fontSpec(aTestDataArr[KMalayalamTestDataIndex]->iTypeFaceName,12);	
	fontStore->GetNearestFontToDesignHeightInPixels((CFont*&)font, fontSpec);	
	CleanupStack::PushL(font);	
	
	TheTest.Next(_L("@SYMTestCaseID GRAPHICS-TI18N-ICULAYOUTENGINE-CT-4008 Repeat Malayalam text shaping test\n"));
	doRepeatShapeText(font, *aTestDataArr[KMalayalamTestDataIndex], KMalayalamScriptCode, KMalayalamLanguageCode);
	repeatShapeText(font, *aTestDataArr[KMalayalamTestDataIndex], KMalayalamScriptCode, KMalayalamLanguageCode);
	
	TheTest.Next(_L("OOM Malayalam text shaping test\n"));
#if defined(_DEBUG)
	doOomShapeText(font, *aTestDataArr[KMalayalamTestDataIndex], KMalayalamScriptCode, KMalayalamLanguageCode);
	oomShapeText(font, *aTestDataArr[KMalayalamTestDataIndex], KMalayalamScriptCode, KMalayalamLanguageCode);
#else
	TheTest.Printf(_L("This test is ignored for release version\n"));
#endif

	TheTest.Next(_L("Run simple Malayalam shape test\n"));
	doShapeText(font, *aTestDataArr[KMalayalamTestDataIndex], KMalayalamScriptCode, KMalayalamLanguageCode, ETrue);
	shapeText(font, *aTestDataArr[KMalayalamTestDataIndex], KMalayalamScriptCode, KMalayalamLanguageCode, ETrue);
	
	//for any other test data we have, run the simple shape text test only
	for(i=KMalayalamTestDataIndex+1; i<KMalayalamTestDataIndex+KNumberOfMalayalamTestDataFiles; i++)
		{
		TFontSpec fontSpec(aTestDataArr[i]->iTypeFaceName,12);	
		fontStore->GetNearestFontToDesignHeightInPixels((CFont*&)font, fontSpec);	

		// First run does not check heap... this ensures that any memory
		// stashed by the rasterizer does not show up as a leak.
		doShapeText(font, *aTestDataArr[i], KMalayalamScriptCode, KMalayalamLanguageCode, ETrue);
		shapeText(font, *aTestDataArr[i], KMalayalamScriptCode, KMalayalamLanguageCode, ETrue);

		fontStore->ReleaseFont(font);
		}
		
	// Now do the last test, the shaping test using various font sizes
	_LIT16(KMalayalam1,"\xd09\xd28\xd4d\xd28\xd2f\xd3f\xd1a\xd4d\xd1a\xd4d\x200c\xd26\xd47\xd36\xd40\xd2f\xd07\xd1f\xd24\xd41\xd2a\xd15\xd4d\xd37\xd1f\xd4d\xd30\xd47\xd21\xd4d\x200c\xd2f\xd42\xd23\xd3f\xd2f\xd28\xd4d\x200d\xd05\xd2d\xd3f\xd28\xd28\xd4d");
	_LIT16(KMalayalam2,"\xd2a\xd23\xd3f\xd2e\xd41\xd1f\xd15\xd4d\xd15\xd4d\x200c\xd2a\xd42\xd30\xd4d\x200d");
	_LIT16(KMalayalam3,"\xd23\xd02\xd24\xd40\xd35\xd23\xd4d\xd1f\xd3f\xd15\xd33\xd4d\x200d\xd31\xd26\xd4d\xd26\xd3e\xd15\xd4d\xd15\xd3f\xd15\xd4b\xd34\xd3f\xd15\xd4d\xd15\xd4b\xd1f\xd4d\x200c\xd35\xd3f\xd35\xd3f\xd27\xd06\xd35\xd36\xd4d\xd2f\xd19\xd4d\xd19\xd33\xd4d\x200d");

	TheTest.Next(_L("Repeat Malayalam shaping test using font sizes 20 to 6000\n"));  
	doRepeatShapeUsingVariousFontSizesTest(fontStore, aTestDataArr[KMalayalamTestDataIndex]->iTypeFaceName, KMalayalam1, KMalayalam2, KMalayalam3, KMalayalamScriptCode, KMalayalamLanguageCode);

	CleanupStack::Pop(font);   
	fontStore->ReleaseFont(font);

	
	CleanupStack::PopAndDestroy(fontStore);
	}

/**
@file
@SYMTestCaseID				GRAPHICS-SYSLIB-ICULAYOUTENGINE-CT-4001
@SYMTestCaseDesc 			Tests the shaper using Bengali Unicode. Test include OOM tests (oomShapeText), repeated 
							calls to the shaper (repeatShapeText), simple shaping tests (shapeText), and repeatedly 
							calling the shaper with incremental font sizes.
@SYMTestPriority 			High
@SYMTestActions  			Performs various tests of the the shaper, calling CShaper::ShapeText in various use cases
@SYMTestExpectedResults		The test must exit cleanly and there should not be any User:84 errors, KERN-EXEC's or any memory leaks.
@SYMPREQ					PREQ1766
@SYMREQ						REQ8741
*/	
void BengaliTestsL(RPointerArray<CTestData> aTestDataArr)
	{
	TheTest.Next(_L("GRAPHICS-SYSLIB-ICULAYOUTENGINE-CT-4001 "));
	TInt i;
	CBitmapFont* font;
	TInt err=KErrNone;	
	//the font store can use the normal user heap
	CFontStore* fontStore = CFontStore::NewL(&User::Heap());    
	fontStore->iKPixelWidthInTwips = 11860;
	fontStore->iKPixelHeightInTwips = 11860;
	CleanupStack::PushL(fontStore);

	//load all ecom implemented rasterizer dlls. installs the rasterizer.
	LoadOpenFontLibraries(fontStore);
	
	//add the required Bengali font file
	TRAP(err,fontStore->AddFileL(aTestDataArr[KBengaliTestDataIndex]->iFilename));
	TEST(err==KErrNone);		
	
	
	//run all tests for TNR_Dev_OT test, which is at position 0 in the aTestDataArr
	TFontSpec fontSpec(aTestDataArr[KBengaliTestDataIndex]->iTypeFaceName,12);	
	fontStore->GetNearestFontToDesignHeightInPixels((CFont*&)font, fontSpec);	
	CleanupStack::PushL(font);	
	
	TheTest.Next(_L("Repeat Bengali text shaping test\n"));
	doRepeatShapeText(font, *aTestDataArr[KBengaliTestDataIndex], KBengaliScriptCode, KBengaliLanguageCode);
	repeatShapeText(font, *aTestDataArr[KBengaliTestDataIndex], KBengaliScriptCode, KBengaliLanguageCode);
	
	TheTest.Next(_L("OOM Bengali text shaping test\n"));
#if defined(_DEBUG)
	doOomShapeText(font, *aTestDataArr[KBengaliTestDataIndex], KBengaliScriptCode, KBengaliLanguageCode);
	oomShapeText(font, *aTestDataArr[KBengaliTestDataIndex], KBengaliScriptCode, KBengaliLanguageCode);
#else
    TheTest.Printf(_L("This test is ignored for release version\n"));
#endif
	
	TheTest.Next(_L("Run simple Bengali shape test\n"));
	doShapeText(font, *aTestDataArr[KBengaliTestDataIndex], KBengaliScriptCode, KBengaliLanguageCode, ETrue);
	shapeText(font, *aTestDataArr[KBengaliTestDataIndex], KBengaliScriptCode, KBengaliLanguageCode, ETrue);
	
	//for any other test data we have, run the simple shape text test only
	for(i=KBengaliTestDataIndex+1; i<KBengaliTestDataIndex+KNumberOfBengaliTestDataFiles; i++)
		{
		TFontSpec fontSpec(aTestDataArr[i]->iTypeFaceName,12);	
		fontStore->GetNearestFontToDesignHeightInPixels((CFont*&)font, fontSpec);	

		// First run does not check heap... this ensures that any memory
		// stashed by the rasterizer does not show up as a leak.
		doShapeText(font, *aTestDataArr[i], KBengaliScriptCode, KBengaliLanguageCode, ETrue);
		shapeText(font, *aTestDataArr[i], KBengaliScriptCode, KBengaliLanguageCode, ETrue);

		fontStore->ReleaseFont(font);
		}
		
	// Now do the last test, the shaping test using various font sizes
	_LIT16(KBengali1,"\x099C\x09A8\x0997\x09A3\x09AE\x09A8\x0020\x0985\x09A7\x09BF\x09A8\x09BE\x09AF\x09BC\x0995\x0020\x099C\x09AF\x09BC\x0020\x09B9\x09C7\x0020\x09AD\x09BE\x09B0\x09A4\x0020\x09AD\x09BE\x0997\x09CD\x09AF\x0020\x09AC\x09BF\x09A7\x09BE\x09A4\x09BE\x0020\x09AA\x099E\x09CD\x099C\x09BE\x09AC\x0020\x09B8\x09BF\x09A8\x09CD\x09A7\x09C1\x0020");
	_LIT16(KBengali2,"\x0997\x09C1\x099C\x09B0\x09BE\x099F\x0020\x09AE\x09B0\x09BE\x09A0\x09BE\x0020\x09A6\x09CD\x09B0\x09BE\x09AC\x09BF\x09A1\x09BC\x0020\x0989\x09A4\x09CD\x0995\x09B2\x0020\x09AC\x0999\x09CD\x0997\x0020\x09AC\x09BF\x09A8\x09CD\x09A7\x09CD\x09AF\x0020\x09B9\x09BF\x09AE\x09BE\x099A\x09B2\x0020\x09AF\x09AE\x09C1\x09A8\x09BE\x0020\x0997\x0999\x09CD\x0997\x09BE\x0020");
	_LIT16(KBengali3,"\x0989\x099A\x09CD\x099B\x09B2\x0020\x099C\x09B2\x09A7\x09BF\x0020\x09A4\x09B0\x0999\x09CD\x0997\x0020\x09A4\x09AC\x0020\x09B6\x09C1\x09AD\x0020\x09A8\x09BE\x09AE\x09C7\x0020\x099C\x09BE\x0997\x09C7\x0020\x09A4\x09AC\x0020\x09B6\x09C1\x09AD\x0020\x0986\x09B6\x09BF\x09B8\x0020\x09AE\x09BE\x0997\x09C7\x0020\x0997\x09BE\x09B9\x09C7\x0020\x09A4\x09AC\x0020\x099C\x09AF\x09BC\x0020");

	TheTest.Next(_L("Repeat Bengali shaping test using font sizes 20 to 6000\n"));  
	doRepeatShapeUsingVariousFontSizesTest(fontStore, aTestDataArr[KBengaliTestDataIndex]->iTypeFaceName, KBengali1, KBengali2, KBengali3, KBengaliScriptCode, KBengaliLanguageCode);

	CleanupStack::Pop(font);   
	fontStore->ReleaseFont(font);

	
	CleanupStack::PopAndDestroy(fontStore);
	}

/**
@file
@SYMTestCaseID				GRAPHICS-SYSLIB-ICULAYOUTENGINE-CT-4002
@SYMTestCaseDesc 			Tests the shaper using Tamil Unicode. Test include OOM tests (oomShapeText), repeated 
							calls to the shaper (repeatShapeText), simple shaping tests (shapeText), and repeatedly 
							calling the shaper with incremental font sizes.
@SYMTestPriority 			High
@SYMTestActions  			Performs various tests of the the shaper, calling CShaper::ShapeText in various use cases
@SYMTestExpectedResults		The test must exit cleanly and there should not be any User:84 errors, KERN-EXEC's or any memory leaks.
@SYMPREQ					PREQ1766
@SYMREQ						REQ8742
*/	
void TamilTestsL(RPointerArray<CTestData> aTestDataArr)
	{
	TheTest.Next(_L("GRAPHICS-SYSLIB-ICULAYOUTENGINE-CT-4002 "));
	TInt i;
	CBitmapFont* font;
	TInt err=KErrNone;	
	//the font store can use the normal user heap
	CFontStore* fontStore = CFontStore::NewL(&User::Heap());    
	fontStore->iKPixelWidthInTwips = 11860;
	fontStore->iKPixelHeightInTwips = 11860;
	CleanupStack::PushL(fontStore);

	//load all ecom implemented rasterizer dlls. installs the rasterizer.
	LoadOpenFontLibraries(fontStore);
	
	//add the required Tamil font file
	TRAP(err,fontStore->AddFileL(aTestDataArr[KTamilTestDataIndex]->iFilename));
	TEST(err==KErrNone);		
	
	
	//run all tests for TNR_Dev_OT test, which is at position 0 in the aTestDataArr
	TFontSpec fontSpec(aTestDataArr[KTamilTestDataIndex]->iTypeFaceName,12);	
	fontStore->GetNearestFontToDesignHeightInPixels((CFont*&)font, fontSpec);	
	CleanupStack::PushL(font);	
	
	TheTest.Next(_L("Repeat Tamil text shaping test\n"));
	doRepeatShapeText(font, *aTestDataArr[KTamilTestDataIndex], KTamilScriptCode, KTamilLanguageCode);
	repeatShapeText(font, *aTestDataArr[KTamilTestDataIndex], KTamilScriptCode, KTamilLanguageCode);
	
	TheTest.Next(_L("OOM Tamil text shaping test\n"));
#if defined(_DEBUG)
	doOomShapeText(font, *aTestDataArr[KTamilTestDataIndex], KTamilScriptCode, KTamilLanguageCode);
	oomShapeText(font, *aTestDataArr[KTamilTestDataIndex], KTamilScriptCode, KTamilLanguageCode);
#else
    TheTest.Printf(_L("This test is ignored for release version\n"));
#endif
	
	TheTest.Next(_L("Run simple Tamil shape test\n"));
	doShapeText(font, *aTestDataArr[KTamilTestDataIndex], KTamilScriptCode, KTamilLanguageCode, ETrue);
	shapeText(font, *aTestDataArr[KTamilTestDataIndex], KTamilScriptCode, KTamilLanguageCode, ETrue);
	
	//for any other test data we have, run the simple shape text test only
	for(i=KTamilTestDataIndex+1; i<KTamilTestDataIndex+KNumberOfTamilTestDataFiles; i++)
		{
		TFontSpec fontSpec(aTestDataArr[i]->iTypeFaceName,12);	
		fontStore->GetNearestFontToDesignHeightInPixels((CFont*&)font, fontSpec);	

		// First run does not check heap... this ensures that any memory
		// stashed by the rasterizer does not show up as a leak.
		doShapeText(font, *aTestDataArr[i], KTamilScriptCode, KTamilLanguageCode, ETrue);
		shapeText(font, *aTestDataArr[i], KTamilScriptCode, KTamilLanguageCode, ETrue);

		fontStore->ReleaseFont(font);
		}
		
	// Now do the last test, the shaping test using various font sizes
	_LIT16(KTamil1,"\x0B89\x0BA3\x0BCD\x0BA3\x0020\x0BAE\x0BC1\x0B9F\x0BBF\x0BAF\x0BBE\x0BA4\x0020\x0BB5\x0BCB\x0BA4\x0BA8\x0BC0\x0BB0\x0BCD\x0020\x0BB5\x0BBE\x0BA9\x0BCD\x0BB5\x0BBE\x0BAF\x0BCD\x0BAA\x0BCD\x0BAA\x0B9F\x0BCD\x0020");
	_LIT16(KTamil2,"\x0B86\x0BA9\x0BCD\x0BB1\x0BB5\x0BC1\x0BAF\x0BBF\x0BB0\x0BCD\x0020\x0B88\x0BB0\x0BBE\x0BB1\x0BC1\x0BAE\x0BCD\x0020\x0B90\x0B99\x0BCD\x0B95\x0BC1\x0BB1\x0BBF\x0BB2\x0BCD\x0020\x0B8F\x0BB4\x0BCD\x0BA8\x0BC6\x0B9F\x0BBF\x0BB2\x0BBE\x0BAE\x0BCD\x0020");
	_LIT16(KTamil3,"\x0BAE\x0BC1\x0BAE\x0BCD\x0BAE\x0BC8\x0BAF\x0BBF\x0B9F\x0BA4\x0BCD\x0020\x0BA4\x0BC8\x0BAF\x0BCC\x0BB5\x0BC1\x0B99\x0BCD\x0020\x0B95\x0BC1\x0BA9\x0BCD\x0BB1\x0BC1\x0BAE\x0BC1\x0BA9\x0BCD\x0020\x0BA9\x0BCA\x0BB1\x0BCD\x0BB1\x0BC1\x0BA3\x0BCD\x0B9F\x0BC7\x0BB1\x0BCD");

	TheTest.Next(_L("Repeat Tamil shaping test using font sizes 20 to 6000\n"));  
	doRepeatShapeUsingVariousFontSizesTest(fontStore, aTestDataArr[KTamilTestDataIndex]->iTypeFaceName, KTamil1, KTamil2, KTamil3, KTamilScriptCode, KTamilLanguageCode);

	CleanupStack::Pop(font);   
	fontStore->ReleaseFont(font);

	
	CleanupStack::PopAndDestroy(fontStore);
	}

/**
@file
@SYMTestCaseID				GRAPHICS-SYSLIB-ICULAYOUTENGINE-CT-4003
@SYMTestCaseDesc 			Tests the shaper using Telugu Unicode. Test include OOM tests (oomShapeText), repeated 
							calls to the shaper (repeatShapeText), simple shaping tests (shapeText), and repeatedly 
							calling the shaper with incremental font sizes.
@SYMTestPriority 			High
@SYMTestActions  			Performs various tests of the the shaper, calling CShaper::ShapeText in various use cases
@SYMTestExpectedResults		The test must exit cleanly and there should not be any User:84 errors, KERN-EXEC's or any memory leaks.
@SYMPREQ					PREQ1766
@SYMREQ						REQ8743
*/	
void TeluguTestsL(RPointerArray<CTestData> aTestDataArr)
	{
	TheTest.Next(_L("GRAPHICS-SYSLIB-ICULAYOUTENGINE-CT-4003 "));
	TInt i;
	CBitmapFont* font;
	TInt err=KErrNone;	
	//the font store can use the normal user heap
	CFontStore* fontStore = CFontStore::NewL(&User::Heap());    
	fontStore->iKPixelWidthInTwips = 11860;
	fontStore->iKPixelHeightInTwips = 11860;
	CleanupStack::PushL(fontStore);

	//load all ecom implemented rasterizer dlls. installs the rasterizer.
	LoadOpenFontLibraries(fontStore);
	
	//add the required Telugu font file
	TRAP(err,fontStore->AddFileL(aTestDataArr[KTeluguTestDataIndex]->iFilename));
	TEST(err==KErrNone);		
	
	
	//run all tests for TNR_Dev_OT test, which is at position 0 in the aTestDataArr
	TFontSpec fontSpec(aTestDataArr[KTeluguTestDataIndex]->iTypeFaceName,12);	
	fontStore->GetNearestFontToDesignHeightInPixels((CFont*&)font, fontSpec);	
	CleanupStack::PushL(font);	
	
	TheTest.Next(_L("Repeat Telugu text shaping test\n"));
	doRepeatShapeText(font, *aTestDataArr[KTeluguTestDataIndex], KTeluguScriptCode, KTeluguLanguageCode);
	repeatShapeText(font, *aTestDataArr[KTeluguTestDataIndex], KTeluguScriptCode, KTeluguLanguageCode);
	
	TheTest.Next(_L("OOM Telugu text shaping test\n"));
#if defined(_DEBUG)
	doOomShapeText(font, *aTestDataArr[KTeluguTestDataIndex], KTeluguScriptCode, KTeluguLanguageCode);
	oomShapeText(font, *aTestDataArr[KTeluguTestDataIndex], KTeluguScriptCode, KTeluguLanguageCode);
#else
    TheTest.Printf(_L("This test is ignored for release version\n"));
#endif
	
	TheTest.Next(_L("Run simple Telugu shape test\n"));
	doShapeText(font, *aTestDataArr[KTeluguTestDataIndex], KTeluguScriptCode, KTeluguLanguageCode, ETrue);
	shapeText(font, *aTestDataArr[KTeluguTestDataIndex], KTeluguScriptCode, KTeluguLanguageCode, ETrue);
	
	//for any other test data we have, run the simple shape text test only
	for(i=KTeluguTestDataIndex+1; i<KTeluguTestDataIndex+KNumberOfTeluguTestDataFiles; i++)
		{
		TFontSpec fontSpec(aTestDataArr[i]->iTypeFaceName,12);	
		fontStore->GetNearestFontToDesignHeightInPixels((CFont*&)font, fontSpec);	

		// First run does not check heap... this ensures that any memory
		// stashed by the rasterizer does not show up as a leak.
		doShapeText(font, *aTestDataArr[i], KTeluguScriptCode, KTeluguLanguageCode, ETrue);
		shapeText(font, *aTestDataArr[i], KTeluguScriptCode, KTeluguLanguageCode, ETrue);

		fontStore->ReleaseFont(font);
		}
		
	// Now do the last test, the shaping test using various font sizes
	_LIT16(KTelugu1,"\x0C05\x0C2A\x0C4D\x0C30\x0C15\x0C3E\x0C36\x0C4B\x093D\x0C2A\x0C4D\x0C30\x0C35\x0C43\x0C24\x0C4D\x0C24\x0C3F\x0C36\x0C4D\x0C1A\x0020\x0C2A\x0C4D\x0C30\x0C2E\x0C3E\x0C26\x0C4B\x0020\x0C0A\x0C30\x0C4D\x0C27\x0C4D\x0C35\x0C02");
	_LIT16(KTelugu2,"\x0C15\x0C48\x0C30\x0C4D\x0C32\x0C3F\x0C19\x0C4D\x0C17\x0C48\x0C38\x0C4D\x0C24\x0C4D\x0C30\x0C40\x0C28\x0C4D\x0C17\x0C41\x0C23\x0C3E\x0C28\x0C47\x0C24\x0C3E\x0C28\x0C24\x0C40\x0C24\x0C4B\x0020\x0C17\x0C41\x0C23\x0C48\x0C30\x0C4D\x0C2F");
	_LIT16(KTelugu3,"\x0020\x0C2C\x0C4D\x0C30\x0C39\x0C4D\x0C2E\x0C23\x0C4B\x0020\x0C39\x0C3F\x0020\x0C2A\x0C4D\x0C30\x0C24\x0C3F\x0C37\x0C4D\x0C20\x0C3E\x0C39\x0C2E\x0C2E\x0C43\x0C24\x0C38\x0C4D\x0C2F\x0C3E\x0C35\x0C4D\x0C2F\x0C2F\x0C38\x0C4D\x0C2F");

	TheTest.Next(_L("Repeat Telugu shaping test using font sizes 20 to 6000\n"));  
	doRepeatShapeUsingVariousFontSizesTest(fontStore, aTestDataArr[KTeluguTestDataIndex]->iTypeFaceName, KTelugu1, KTelugu2, KTelugu3, KTeluguScriptCode, KTeluguLanguageCode);

	CleanupStack::Pop(font);   
	fontStore->ReleaseFont(font);

	
	CleanupStack::PopAndDestroy(fontStore);
	}

static void MainL()
	{
	TInt i=0;
		
	TheTest.Start(_L("TC_SHAP_shapeText tests\n"));
	
	//set up the testData variables
	CDesC16ArrayFlat* testDataFilenames = new CDesC16ArrayFlat(2);
	CleanupStack::PushL(testDataFilenames);
	for (i = 0; i != sizeof(KTestFilenames)/sizeof(KTestFilenames[0]); ++i)
		{
		TPtrC16 d(KTestFilenames[i]);
		testDataFilenames->AppendL(d);
		}
	RPointerArray<CTestData> testDataArr = SetupTestData(testDataFilenames);
	// Run Hindi Tests
	TheTest.Next(_L("Hindi Shaping Tests\n"));
	TRAPD(err, HindiTestsL(testDataArr));
	TEST2(err, KErrNone);
	// Run Kannada Tests
	TheTest.Next(_L("Kannada Shaping Tests\n"));
	TRAP(err, KannadaTestsL(testDataArr));
	TEST2(err, KErrNone);
	// Run Gujarati Tests
	TheTest.Next(_L("Gujarati Shaping Tests\n"));
	TRAP(err, GujaratiTestsL(testDataArr));
	TEST2(err, KErrNone);
	// Run Bengali Tests
	TheTest.Next(_L("Bengali Shaping Tests\n"));
	TRAP(err, BengaliTestsL(testDataArr));
	TEST2(err, KErrNone);
	// Run Tamil Tests
	TheTest.Next(_L("Tamil Shaping Tests\n"));
	TRAP(err, TamilTestsL(testDataArr));
	TEST2(err, KErrNone);
	// Run Telugu Tests
	TheTest.Next(_L("Telugu Shaping Tests\n"));
	TRAP(err, TeluguTestsL(testDataArr));
	TEST2(err, KErrNone);
	
	//	Run Gurmukhi Tests
	TheTest.Next( _L("Gurmukhi Shaping Tests\n") );
	TRAP(err, GurmukhiTestsL(testDataArr) );
	TEST2(err, KErrNone);

	//	Run Malayalam Tests
	TheTest.Next( _L("Malayalam Shaping Tests\n") );
	TRAP(err, MalayalamTestsL(testDataArr) );
	TEST2(err, KErrNone);

	
	testDataArr.ResetAndDestroy();

	CleanupStack::PopAndDestroy(1);		//testDataFilenames
	
	//close the ecom session opened by LoadOpenFontLibraries()
	REComSession::FinalClose();	 
	
	TheTest.End();
	TheTest.Close();		
			
	}

TInt E32Main()
	{
	__UHEAP_MARK;

	CTrapCleanup* tc = CTrapCleanup::New();
    TEST(tc != NULL);

	TheTest.Title();
  	TRAPD(err, ::MainL());
	TEST2(err, KErrNone);

	delete tc;
	CloseSTDLIB();	

	__UHEAP_MARKEND;

	User::Heap().Check();
	return KErrNone;
	}
