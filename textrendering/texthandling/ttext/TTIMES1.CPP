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

#include <s32mem.h>

#include <txtrich.h>
#include <txtglobl.h>

#include "../incp/T_PMLPAR.H"

#define UNUSED_VAR(a) a = a

LOCAL_D CTrapCleanup* TheTrapCleanup;
LOCAL_D RTest test(_L("CRichText Document"));
LOCAL_D CParaFormatLayer* TheGlobalParaFormatLayer;
LOCAL_D CCharFormatLayer* TheGlobalCharFormatLayer;
LOCAL_D CParser* TheParser;

LOCAL_D const TInt KTestCleanupStack=0x200;
LOCAL_D const TInt KCreateRichTextCount=1000;

LOCAL_D CRichText* TheText[KCreateRichTextCount];

LOCAL_C void GenerateGlobalLayersL()
// Provides the base layers for globl text and below
//
	{
	TParaFormatMask paraMask;
	TheGlobalParaFormatLayer=CParaFormatLayer::NewL((CParaFormat*)NULL,paraMask);
	TCharFormat charFormat;
	TCharFormatMask charMask;
	TheGlobalCharFormatLayer=CCharFormatLayer::NewL(charFormat,charMask);
	}


LOCAL_C void KillGlobalLayers()
// Destroy the base layers for global text and below
//
	{
	delete TheGlobalParaFormatLayer;
	delete TheGlobalCharFormatLayer;
	TheGlobalParaFormatLayer=NULL;
	TheGlobalCharFormatLayer=NULL;
	}

LOCAL_C void KillText()
	{
	for (TInt ii=0; ii<KCreateRichTextCount;ii++)
		{
		delete TheText[ii];
		TheText[ii]=NULL;
		}
	}


struct TNow : public TTime 
	{
	TNow() { HomeTime(); }
	};

LOCAL_C void CreationTestsL()
//
	{
	GenerateGlobalLayersL();

	TNow start;
	TInt ii = 0;
	for (ii=0; ii<KCreateRichTextCount;ii++)
		{
		TheText[ii]=CRichText::NewL(TheGlobalParaFormatLayer,TheGlobalCharFormatLayer);			
		}
	TNow finish;
	KillText();
	test(ii==KCreateRichTextCount);
	//
	// Display the metric
	TBuf<60> context;
	context.Format(_L("        Create rich text %d times: %d\n"),KCreateRichTextCount,finish.MicroSecondsFrom(start).Int64());
	test.Printf(context);
	//
	// Tidy up
	KillText();
	KillGlobalLayers();
	}


LOCAL_C CRichText* LoadIntoTextL(TFileName& aFileName)
//
	{
	TRAPD(ret,
	TheParser=CParser::NewL());
	CRichText* text=NULL;
	TRAP(ret,
	text=TheParser->ParseL(aFileName));
	TheGlobalParaFormatLayer=(CParaFormatLayer*)text->GlobalParaFormatLayer();
	TheGlobalCharFormatLayer=(CCharFormatLayer*)text->GlobalCharFormatLayer();
	delete TheParser;
	TheParser=NULL;
	return text;
	}


LOCAL_C void GetAppendTestTimeL(const CRichText* aSource,TInt aTestLoopCount)
	{
	CRichText* target=CRichText::NewL(TheGlobalParaFormatLayer,TheGlobalCharFormatLayer);
	test(target->DocumentLength()==0);
	test(!target->HasMarkupData());

	TNow start;
	TInt ii = 0;
	for (ii=0;ii<aTestLoopCount;ii++)
		{
		target->AppendTakingSolePictureOwnershipL(*aSource);
		}
	TNow finish;
	TInt charSum=aTestLoopCount*(aSource->DocumentLength()+1)-1;
	test(target->DocumentLength()==charSum);
	//
	// Calculate and display result
	test(ii==aTestLoopCount);
	TBuf<60> context;
	context.Format(_L("        Append %d rich text's: %d\n"),aTestLoopCount,finish.MicroSecondsFrom(start).Int64());
	test.Printf(context);
	delete target;
	}


LOCAL_C void GetBenchmarkAppendTestTimeL(const CRichText* aSource,TInt aTestLoopCount)
	{
	CRichText** target=new CRichText*[aTestLoopCount];
	CBufStore** store=new CBufStore*[aTestLoopCount];	
	TInt ii = 0;
	for (ii=0;ii<aTestLoopCount;ii++)
		{
		target[ii]=CRichText::NewL(TheGlobalParaFormatLayer,TheGlobalCharFormatLayer);
		store[ii]=CBufStore::NewL(128);	
		test(target[ii]->DocumentLength()==0);
		test(!target[ii]->HasMarkupData());
		}
	TNow start;
	for (ii=0;ii<aTestLoopCount;ii++)
		{
		TStreamId id=aSource->StoreL(*store[ii]);
		target[ii]->RestoreL(*store[ii],id);
		}
	TNow finish;

	for (ii=0;ii<aTestLoopCount;ii++)
		{
		delete target[ii];
		delete store[ii];
		}
	delete []target;
	delete []store;
	//
	// Calculate and display result
	test(ii==aTestLoopCount);
	TBuf<70> context2;
	context2.Format(_L("        Benchmark              : %d\n"),finish.MicroSecondsFrom(start).Int64());
	test.Printf(context2);
	}


LOCAL_C void AppendTest1L()
//
	{
	TInt testLoopCount=900;
	CRichText* source=CRichText::NewL(TheGlobalParaFormatLayer,TheGlobalCharFormatLayer);
	source->InsertL(source->DocumentLength(),_L("A bit of text that pretends to be an entry's title"));
	test(!source->HasMarkupData());
	GetAppendTestTimeL(source,testLoopCount);
	//
	// Now the benchmark against which we should measure.
	GetBenchmarkAppendTestTimeL(source,testLoopCount);
	//
	// tidy up
	delete source;
	}


LOCAL_C void AppendTest2L()
//
	{
	KillGlobalLayers();  // they are replaced by the ones read in from the PML file.
	TInt testLoopCount=266;
	TFileName file=_L("z:\\test\\app-framework\\etext\\ttimes1.pml");
	CRichText* source=LoadIntoTextL(file);
	test(source->HasMarkupData());
	GetAppendTestTimeL(source,testLoopCount);
	//
	// Now the benchmark against which we should measure.
	GetBenchmarkAppendTestTimeL(source,testLoopCount);
	//
	// tidy up
	delete source;
	}


LOCAL_C void AppendTestsL()
//
	{
	GenerateGlobalLayersL();
	//
	test.Start(_L("Plain Text Component Only"));
	TRAPD(ret,
	AppendTest1L());
	test(ret==KErrNone);
	//
	test.Next(_L("Plain Text with limited Markup - no pictures"));
	TRAP(ret,
	AppendTest2L());
	test(ret==KErrNone);
	//
	KillGlobalLayers();
	test.End();
	}
	
	
LOCAL_C void DoTestsL()
//
	{
	test.Start(_L(" @SYMTestCaseID:SYSLIB-TTEXT-LEGACY-T_TTIMES1-0001 Creation Tests "));
	CreationTestsL();
	test.Next(_L("Appending Tests"));
	AppendTestsL();
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
