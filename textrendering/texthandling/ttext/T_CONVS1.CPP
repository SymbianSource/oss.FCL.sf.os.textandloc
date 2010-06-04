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


#include <txtglobl.h>
#include <txtfmlyr.h>
#include <s32mem.h>
#include <s32file.h>
#include <e32test.h>
#include <flddef.h>
#include <fldbltin.h>

const TInt KTestCleanupStack=0x20;

LOCAL_D CTrapCleanup* TheTrapCleanup;
LOCAL_D RTest test(_L("T_CONVS1 - GlobalText Persistence"));

LOCAL_D	TPtrC bigBuf(_L("This is a very big buffer indeed, containing text and special characters,\
 big enough to fill a segment of an editable text component that employs segmented storage"));

////////////////////////////////////////////////////////////////////////////////////////////
class TTestFieldFactory : public MTextFieldFactory
	{
public:
	// from MTextFieldFactory
	virtual CTextField* NewFieldL(TUid aFieldType); 
	// Creates a field of the type specified
	// Returns NULL if it does not recognise/support the field type
	};

CTextField* TTestFieldFactory::NewFieldL(TUid aFieldType)
// Creates a field (in aHeader) of the type specified in aHeader
// 
	{
	CTextField* field=NULL;
	if (aFieldType==KDateTimeFieldUid)
		field = (CTextField*)new(ELeave) CDateTimeField();
	return field;
	}
/////////////////////////////////////////////////////////////////////////////////////////////

_LIT(KOutputFile, "c:\\etext\\t_convs1.tst");
template <class T>
void testStoreRestoreL(T& aCopy,const T& aOriginal)
// Test document persistance.
//
    {
	// set up the store
	RFs	theFs;
	theFs.Connect();
	//
	theFs.Delete(KOutputFile);
	theFs.MkDirAll(KOutputFile);
	CFileStore* theStore=CDirectFileStore::CreateL(theFs,KOutputFile,EFileRead|EFileWrite);
	CleanupStack::PushL(theStore);
	theStore->SetTypeL(KDirectFileStoreLayoutUid);
	//
	// store the original
	TStreamId id(0);
	TRAPD(ret,id=aOriginal.StoreL(*theStore));
		test(ret==KErrNone);
	//
	// restore into the copy
	TRAP(ret,aCopy.RestoreL(*theStore,id));
		test(ret==KErrNone);
	//
	// tidy up
	CleanupStack::PopAndDestroy();  // theStore
	theFs.Close();
    }

LOCAL_C TInt IsEqual(const CPlainText* aCopy,const CPlainText* aOriginal)
//
// Tests for equality of plain text components.
// Takes account of multiple segments of a segmented text component.
//
	{
	TInt lengthOfOriginal=aOriginal->DocumentLength();
	TInt lengthOfCopy=aCopy->DocumentLength();
	test(lengthOfOriginal==lengthOfCopy);
//
	TPtrC copy,orig;
//
	TInt lengthRead=0;
	while(lengthRead<=lengthOfOriginal)
		{
		copy.Set((aCopy->Read(lengthRead)));
		orig.Set((aOriginal->Read(lengthRead)));
		for (TInt offset=0; offset<orig.Length(); offset++)
			test(copy[offset]==orig[offset]);
		lengthRead+=orig.Length();
		}
	test(lengthRead==lengthOfOriginal+1);
	test.Next(_L("Restored plain text component matches original"));
	TInt copyFieldCount=aCopy->FieldCount();
	TInt origFieldCount=aOriginal->FieldCount();
	test(copyFieldCount==origFieldCount);
	return 1;
	}


LOCAL_C TInt DocsEqual(const CGlobalText* aCopy,const CGlobalText* aOrig)
//
//
//
	{
	test(IsEqual(aCopy,aOrig));
	return 1;
	}


void GenerateGlobalTextL()
//
// Create a global text documnet.
//
	{
//	Set up the character format layer.
	CCharFormatLayer* cl1=CCharFormatLayer::NewL();
	TCharFormat charFormat;	TCharFormatMask charMask;
	charMask.ClearAll();
	charFormat.iFontSpec.iFontStyle.SetStrokeWeight(EStrokeWeightBold);	charMask.SetAttrib(EAttFontStrokeWeight);
	charFormat.iFontSpec.iFontStyle.SetPosture(EPostureItalic);	charMask.SetAttrib(EAttFontPosture);
	charFormat.iFontPresentation.iUnderline=EUnderlineOn;	charMask.SetAttrib(EAttFontUnderline);
	cl1->SetL(charFormat,charMask);
	charMask.ClearAll();
//	Set up the paragraph format layer.
	CParaFormatLayer* l1=CParaFormatLayer::NewL();
	CParaFormat* paraFormat=CParaFormat::NewL();	TParaFormatMask paraMask;
	paraMask.ClearAll();
	TTabStop tab1,tab2;
	tab1.iTwipsPosition=5000;	tab2.iTwipsPosition=5001;
	tab1.iType=TTabStop::ERightTab;	tab2.iType=TTabStop::ECenteredTab;
	paraFormat->StoreTabL(tab1);
	paraFormat->StoreTabL(tab2);
	paraMask.SetAttrib(EAttTabStop);
	paraFormat->iLeftMarginInTwips=666; paraMask.SetAttrib(EAttLeftMargin);
	l1->SetL(paraFormat,paraMask);
	paraMask.ClearAll();
//	Now create the global text component.
	CGlobalText* globalDoc=CGlobalText::NewL(l1,cl1,CEditableText::ESegmentedStorage);
	globalDoc->InsertL(0,bigBuf);
//	Now create the global text that will be the restored one.
	CCharFormatLayer* cr1=CCharFormatLayer::NewL();
	TCharFormat ff;TCharFormatMask mm;cr1->SetL(ff,mm);
	CParaFormatLayer* r1=CParaFormatLayer::NewL();
	TParaFormatMask nn; r1->SetL((CParaFormat*)NULL,nn);
	CGlobalText* restoredDoc=CGlobalText::NewL(r1,cr1,CEditableText::ESegmentedStorage);
//	Store a text field in the global text.
	TTestFieldFactory factory;
	globalDoc->SetFieldFactory(&factory);
	restoredDoc->SetFieldFactory(&factory);
	CTextField* field=NULL;
	TRAPD(ret,
	field=factory.NewFieldL(KDateTimeFieldUid));
 	test(ret==KErrNone);
	TRAP(ret,
	globalDoc->InsertFieldL(0,field,KDateTimeFieldUid));
	test(ret==KErrNone);
//	And do the streaming/restore.
	test.Start(_L("Storing global text with field record"));
	test.Next(_L("Restoring global text"));
	testStoreRestoreL(*restoredDoc,*globalDoc);
	test(DocsEqual(restoredDoc,globalDoc));
	test.End();
//	Now clean up.
	TInt restoredCharChain=cr1->ChainCount();
	TInt restoredParaChain=r1->ChainCount();
	CCharFormatLayer* chCurrent=cr1;
	CCharFormatLayer* chNext=(CCharFormatLayer*)cr1->SenseBase();
	delete chCurrent;
	for (TInt loop=0;loop<restoredCharChain-1;loop++)	
		{
		chCurrent=chNext;
		chNext=(CCharFormatLayer*)chCurrent->SenseBase();
		delete chCurrent;
		}
	CParaFormatLayer* paCurrent=r1;
	CParaFormatLayer* paNext=(CParaFormatLayer*)r1->SenseBase();
	delete paCurrent ;
	for (TInt ploop=0;ploop<restoredParaChain-1;ploop++)	
		{
		paCurrent=paNext;
		paNext=(CParaFormatLayer*)paCurrent->SenseBase();
		delete paCurrent;
		}
	delete l1;
	delete cl1;
	delete paraFormat;
	delete restoredDoc;
	delete globalDoc;
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


LOCAL_C void DeleteDataFile(const TDesC& aFullName)
	{
	RFs fsSession;
	TInt err = fsSession.Connect();
	if(err == KErrNone)
		{
		TEntry entry;
		if(fsSession.Entry(aFullName, entry) == KErrNone)
			{
			RDebug::Print(_L("Deleting \"%S\" file.\n"), &aFullName);
			err = fsSession.SetAtt(aFullName, 0, KEntryAttReadOnly);
			if(err != KErrNone) 
				{
				RDebug::Print(_L("Error %d changing \"%S\" file attributes.\n"), err, &aFullName);
				}
			err = fsSession.Delete(aFullName);
			if(err != KErrNone) 
				{
				RDebug::Print(_L("Error %d deleting \"%S\" file.\n"), err, &aFullName);
				}
			}
		fsSession.Close();
		}
	else
		{
		RDebug::Print(_L("Error %d connecting file session. File: %S.\n"), err, &aFullName);
		}
	}

GLDEF_C TInt E32Main()
//
// Test streaming conversions.
//
    {
	setupCleanup();
	test.Title();
	__UHEAP_MARK;

	test.Start(_L("Generate global text"));
	test.Next(_L(" @SYMTestCaseID:SYSLIB-ETEXT-LEGACY-T_CONVS1-0001 "));
	TRAPD(r,GenerateGlobalTextL());
	test(r==KErrNone);
	
	__UHEAP_MARKEND;
	
	::DeleteDataFile(KOutputFile);	//deletion of data files must be before call to End() - DEF047652
	test.End();
	test.Close();
	delete TheTrapCleanup;

	

	return 0;
    }

