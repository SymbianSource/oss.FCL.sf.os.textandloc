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


#include <e32test.h>
#include <e32svr.h>

#include <txtrich.h>
#include <txtglobl.h>

/* this fixes a MSVC link warning */
#ifdef __VC32__
#pragma comment (linker, "/opt:noref") 
#endif

#define UNUSED_VAR(a) a = a

#ifdef NDEBUG
const TInt KGlobalTextATest1=100000;
const TInt KGlobalTextATest2=100000;
const TInt KGlobalTextATest3=1000;
const TInt KRichTextTest1=10000;
const TInt KRichTextTest2=10000;
const TInt KRichTextTest3=1000;
const TInt KGlobalTextBTest1=10000;
const TInt KGlobalTextBTest2=10000;
const TInt KGlobalTextBTest3=1000;
const TInt KCharFormatLayerTest=100000;
#else
const TInt KGlobalTextATest1=100000;
const TInt KGlobalTextATest2=100000;
const TInt KGlobalTextATest3=1000;
const TInt KRichTextTest1=5000;
const TInt KRichTextTest2=5000;
const TInt KRichTextTest3=100;
const TInt KGlobalTextBTest1=5000;
const TInt KGlobalTextBTest2=5000;
const TInt KGlobalTextBTest3=100;
const TInt KCharFormatLayerTest=100000;
#endif


LOCAL_D CTrapCleanup* TheTrapCleanup;
LOCAL_D RTest test(_L("CRichText Document"));
LOCAL_D CGlobalText* TheText;
LOCAL_D CParaFormatLayer* TheParaFormatLayer;
LOCAL_D CCharFormatLayer* TheCharFormatLayer;
LOCAL_D const TInt KTestCleanupStack=0x200;

LOCAL_C void GenerateGlobalLayersL()
// Provides the base layers for globl text and below
//
	{
	TParaFormatMask paraMask;
	TheParaFormatLayer=CParaFormatLayer::NewL((CParaFormat*)NULL,paraMask);
	TCharFormat charFormat;
	TCharFormatMask charMask;
	TheCharFormatLayer=CCharFormatLayer::NewL(charFormat,charMask);
	}

LOCAL_C void GenerateGlobalTextL()
// Provide an instantiated global text object
//
	{
	GenerateGlobalLayersL();
	TheText=CGlobalText::NewL(TheParaFormatLayer,TheCharFormatLayer);
	}

LOCAL_C void GenerateBasicRichTextL()
// Provide a default instantiated rich text object
//
	{TheText=CRichText::NewL(TheParaFormatLayer,TheCharFormatLayer);}

LOCAL_C void KillGlobalLayers()
// Destroy the base layers for global text and below
//
	{
	delete TheParaFormatLayer;
	delete TheCharFormatLayer;
	TheParaFormatLayer=NULL;
	TheCharFormatLayer=NULL;
	}

LOCAL_C void KillText()
	{
	delete TheText;
	TheText=NULL;
	}


LOCAL_C void LoadLongDocument()
//
	{
	TFileName file;

	file=(_L("z:\\test\\app-framework\\etext\\climb.txt"));
	TheText->Reset();
	TInt count=0;
	TRAPD(ret,
	count=TheText->ImportTextFileL(0,file,CPlainText::EOrganiseByParagraph));
	test(ret==KErrNone);
	test(count>0); // check for equality later
	}


LOCAL_C void CallGetChars(TInt aStartPos,TInt aCharacterCount,TInt aLineLength)
//
	{
	TPtrC view;
	TCharFormat charFormat;
	TInt consumed=aStartPos;
	while (consumed<=aStartPos+aCharacterCount)
		{
		TheText->GetChars(view,charFormat,consumed);
		consumed+=Min(view.Length(),aLineLength);
		}
	}

LOCAL_C void GetTimesForGetChars(TInt aLoopCount,TInt aStartPos,TInt aCharacterCount,TInt aLineLength)
//
//
	{
	//
	for (TInt loop=0;loop<aLoopCount;loop++)
		{
		CallGetChars(aStartPos,aCharacterCount,aLineLength);
		}
	}


LOCAL_C void DoLongDocumentTestL(TInt aTest1Count,TInt aTest2Count,TInt aTest3Count)
//
//
	{
	LoadLongDocument();
	TCharFormat charFormat;
	TCharFormatMask mask;
	mask.SetAttrib(EAttFontStrokeWeight);
	TheText->ApplyCharFormatL(charFormat,mask,100,2);
	TInt documentLength=TheText->DocumentLength();
	TInt paraCount=TheText->ParagraphCount();
	TInt wordCount=TheText->WordCount();
	TBuf<80> stats;
	stats.Format(_L("Document Stats:\nChars: %d\nWords: %d\nParas: %d\n"),documentLength,wordCount,paraCount);
	test.Printf(stats);
	RDebug::Print(_L("%S"),&stats);
	TBuf<80> testTitle;
	//
	testTitle.Format(_L("Pos: 0-100  %d times"),aTest1Count);
	test.Start(testTitle);
	GetTimesForGetChars(aTest1Count,0,100,50);
	//
	testTitle.Format(_L("Pos: 18200-18300 %d times"),aTest2Count);
	test.Next(testTitle);
	GetTimesForGetChars(aTest2Count,18200,100,50);
	//
	testTitle.Format(_L("Pos: all %d times"),aTest3Count);
	test.Next(testTitle);
	GetTimesForGetChars(aTest3Count,0,documentLength,50);
	//
	test.End();
	}


LOCAL_C void DoGetCharFormatLayerReadTimesL(TInt aLoopCount)
//
	{
	//
	// Now take some times.
	TCharFormat charFormat;
	TCharFormatMask charMask;
	for (TInt loop=0;loop<aLoopCount;loop++)
		{
		charMask.ClearAll();  // this is used for readings.

		TheCharFormatLayer->Sense(charFormat,charMask);

		}
	// Display the metric
	TBuf<60> context;
	context.Format(_L("10 att X %d loops=%d atts\n"),aLoopCount,10*aLoopCount);
	test.Printf(context);
	RDebug::Print(_L("%S"),&context);
	}


LOCAL_C void DoEmptyCharFormatLayerReadL(TInt aLoopCount)
//	
	{DoGetCharFormatLayerReadTimesL(aLoopCount);}


LOCAL_C void DoCharFormatLayerReadL(TInt aLoopCount)
// tests times of reading attributes from a CCharFormatLayer
//
	{
	// Fill the character format layer
	TCharFormat charFormat(_L("Times New Roman"),180);
	TCharFormatMask charMask;
	charMask.SetAll();
	TheCharFormatLayer->SetL(charFormat,charMask);
	//
	// Take times
	DoGetCharFormatLayerReadTimesL(aLoopCount);
	}


LOCAL_C void FormatLayerTestL()
// Time tests on format layer access.
//
	{
	test.Start(_L("CCharFormatLayer - Attribute reads"));
	GenerateGlobalLayersL();
	//
	TBuf<80> testTitle;
	testTitle.Format(_L("Reading empty char format layer %d times"),KCharFormatLayerTest);
	test.Next(testTitle);
	DoEmptyCharFormatLayerReadL(KCharFormatLayerTest);
	//
	testTitle.Format(_L("Read 10 attributes from layer %d times"),KCharFormatLayerTest);
	test.Next(testTitle);
	TRAPD(ret, DoCharFormatLayerReadL(KCharFormatLayerTest));
	test(ret==KErrNone);
	//
	KillGlobalLayers();
	test.End();
	}


LOCAL_C void LongDocumentTestL()
//
	{
	//
	test.Start(_L("Global text - Empty layers"));
	GenerateGlobalTextL();
	DoLongDocumentTestL(KGlobalTextATest1,KGlobalTextATest2,KGlobalTextATest3);
	KillText();
	//
	test.Next(_L("Rich text - Empty layers"));
	GenerateBasicRichTextL();
	DoLongDocumentTestL(KRichTextTest1,KRichTextTest2,KRichTextTest3);
	KillText();
	KillGlobalLayers();
	//
	test.Next(_L("Global text - 2 character attributes stored"));
	GenerateGlobalTextL();
	TBuf<5> name=_L("SWiss");
	TCharFormat charFormat(name,178);
	TCharFormatMask charMask;
	charMask.SetAttrib(EAttFontTypeface);
	charMask.SetAttrib(EAttFontHeight);
	TRAPD(ret,
	TheCharFormatLayer->SetL(charFormat,charMask));
	test(ret==KErrNone);
	DoLongDocumentTestL(KGlobalTextBTest1,KGlobalTextBTest2,KGlobalTextBTest3);
	KillText();
	//
	test.Next(_L("Rich text - 2 charcter attributes stored"));
	GenerateBasicRichTextL();
	DoLongDocumentTestL(KRichTextTest1,KRichTextTest2,KRichTextTest3);
	KillText();
	//
	KillGlobalLayers();
	test.End();
	}
	

LOCAL_C void DoTestsL()
//
	{
	test.Start(_L(" @SYMTestCaseID:SYSLIB-TTEXT-LEGACY-T_TIMES-0001 Long document tests "));
	LongDocumentTestL();
	//
	test.Next(_L("Format layer tests"));
	FormatLayerTestL();
	//
	}


LOCAL_C void setupCleanup()
//
// Initialise the cleanup stack.
//
    {

	TheTrapCleanup=CTrapCleanup::New();
	TRAPD(r,\
		{\
		for (TInt i=KTestCleanupStack;i>0;i--)\
			CleanupStack::PushL((TAny*)1);\
		test(r==KErrNone);\
		CleanupStack::Pop(KTestCleanupStack);\
		});
	}



GLDEF_C TInt E32Main()
//
// Test the Document Model Services.
//
    {
	setupCleanup();
	test.Title();	
	__UHEAP_MARK;
	
	TRAPD(ret,DoTestsL());
    test(ret == KErrNone);
	
	test.End();
	test.Close();
	__UHEAP_MARKEND;
	delete TheTrapCleanup;
	return(0);
    }
