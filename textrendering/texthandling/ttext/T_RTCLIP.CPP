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


#include "TSTCLIPB.H"
#include <txtrich.h>
#include "TXTMRTSR.H"
#include <s32mem.h>
#include <s32file.h>
#include <gdi.h>
#include <conpics.h>
#include <e32test.h>
#include "../incp/T_PMLPAR.H"

#define UNUSED_VAR(a) a = a

const TInt KTestCleanupStack=0x80;


LOCAL_D RTest test(_L("Cut & Paste"));
LOCAL_D CTrapCleanup* TheTrapCleanup=NULL;
LOCAL_D CRichText* TheText=NULL;
LOCAL_D CParaFormatLayer* TheGlobalParaLayer=NULL;
LOCAL_D CCharFormatLayer* TheGlobalCharLayer=NULL;
LOCAL_D CClipboard* TheWriteBoard=NULL;
LOCAL_D CClipboard* TheReadBoard=NULL;
LOCAL_D TFileName TheFileName = _L("z:\\test\\app-framework\\etext\\rtclipb.pml");
LOCAL_D RFs TheSession;


class TDemStoreResolver : public MRichTextStoreResolver
	{
public:
	TDemStoreResolver(CStreamStore& aStore);
	//
	virtual const CStreamStore& StreamStoreL(TInt aPos)const;
private:
	CStreamStore* iStore;
	};


TDemStoreResolver::TDemStoreResolver(CStreamStore& aStore)
: iStore(&aStore)
	{}

const CStreamStore& TDemStoreResolver::StreamStoreL(TInt /*aPos*/)const
	{return *iStore;}


LOCAL_C void OpenWriteClipboardLC()
// Initialize a new write clipboard, after
// deleting any existing read clipboard.
//
	{
	if (TheReadBoard)
		{
		CleanupStack::PopAndDestroy();
		TheReadBoard=NULL;
		TheSession.Close();
		}
	User::LeaveIfError(TheSession.Connect());
	TheWriteBoard=CClipboard::NewForWritingLC(TheSession);
	}


LOCAL_C void OpenReadClipboardLC()
// Initialize a new read clipboard, after
// deleting any existing write clipboard.
//
	{
	if (TheWriteBoard)
		{
		TheWriteBoard->CommitL();
		CleanupStack::PopAndDestroy();
		TheWriteBoard=NULL;
		TheSession.Close();
		}
	User::LeaveIfError(TheSession.Connect());
	TheReadBoard=CClipboard::NewForReadingLC(TheSession);
	}


LOCAL_C void ParseRichTextDocumentLC()
//
	{
	CParser* myParser=CParser::NewL();
	CleanupStack::PushL(myParser);
	TheText=myParser->ParseL(TheFileName);
	TheGlobalParaLayer=(CParaFormatLayer*)TheText->GlobalParaFormatLayer();
	TheGlobalCharLayer=(CCharFormatLayer*)TheText->GlobalCharFormatLayer();
	CleanupStack::PopAndDestroy();
	//
	CleanupStack::PushL(TheText);
	}


LOCAL_C void testRichTextCutPaste1a()
//
//
	{
	test.Next(_L("Cut & paste, preserving formatting into non-empty document"));
	TheFileName=_L("z:\\test\\app-framework\\etext\\rtclipb2.pml");
	ParseRichTextDocumentLC();
	TheText->DeleteL(0,TheText->DocumentLength());
	TPtrC buf1(_L("ab"));
	TheText->InsertL(0,buf1);
	TheText->InsertL(1,CEditableText::EParagraphDelimiter);
	TheReadBoard=NULL;
	TheWriteBoard=NULL;
	OpenWriteClipboardLC();
	TheText->CopyToStoreL(TheWriteBoard->Store(),TheWriteBoard->StreamDictionary(),0,TheText->DocumentLength());
	TheText->DeleteL(1,2);  // Just leaves the single character 'a' as content.
	//
	OpenReadClipboardLC();
	TheText->PasteFromStoreL(TheReadBoard->Store(),TheReadBoard->StreamDictionary(),1);
	//
	CleanupStack::PopAndDestroy();  // Last clipboard object
	CleanupStack::PopAndDestroy();  // TheTextObject
	delete TheGlobalParaLayer;
	delete TheGlobalCharLayer;
	}

_LIT(KOutputFile, "c:\\etext\\t_rtclip.doc");
LOCAL_C void testRichTextCutPaste1b()
//
//
	{
	TheReadBoard=NULL;
	TheWriteBoard=NULL;
	test.Next(_L("Copy to Clipboard with pictures, with missing host applications."));
	TheFileName=_L("z:\\test\\app-framework\\etext\\rtclipb2.pml");  // dummy - just to get global layers
	ParseRichTextDocumentLC();
	TheText->Reset();
	//
	CXzeDoor* pic1=CXzeDoor::NewL('1',EFalse);  // never fail to detach
	CXzePicture* pic2=CXzePicture::NewL('2');
	CXzeDoor* pic3=CXzeDoor::NewL('1',EFalse);  // never fail to detach
	CXzePicture* pic4=CXzePicture::NewL('2');
	//
	TPictureHeader hdr1;
	TPictureHeader hdr2;
	TPictureHeader hdr3;
	TPictureHeader hdr4;
	//
	hdr1.iPictureType=KUidXzeDoorType;
	hdr2.iPictureType=KUidXzePictureType;
	hdr3.iPictureType=KUidXzeDoorType;
	hdr4.iPictureType=KUidXzePictureType;
	//
	hdr1.iPicture=pic1;
	hdr2.iPicture=pic2;
	hdr3.iPicture=pic3;
	hdr4.iPicture=pic4;
	//
	TheText->InsertL(0,hdr4);
	TheText->InsertL(0,hdr3);
	TheText->InsertL(0,hdr2);
	TheText->InsertL(0,hdr1);
	test(TheText->PictureCount()==4);
	//
	// Now save and reload this to get the pictures into a deferred picture store.
	RFs session;
	session.Connect();
	session.Delete(KOutputFile);
	session.MkDirAll(KOutputFile);
	CFileStore* store=CDirectFileStore::CreateLC(session,KOutputFile,EFileRead|EFileWrite);
	store->SetTypeL(KDirectFileStoreLayoutUid);
	TStreamId id=KNullStreamId;
	TRAPD(r,	
	id=TheText->StoreL(*store));
		test(r==KErrNone);
	//
	TheText->Reset();
	TheText->RestoreL(*store,id);
	MDemPictureFactory* factory=new(ELeave) MDemPictureFactory;
	TDemStoreResolver resolver(*store);
	TheText->SetPictureFactory(factory,&resolver);
	//
	// Now the tests.
	OpenWriteClipboardLC();
	TInt documentLength=TheText->DocumentLength();
	TRAP(r,
	TheText->DetachFromStoreL(CPicture::EDetachFull,0,documentLength));
	if (r==KErrNotSupported)
		test.Printf(_L("    SIMULATION: Some picture data has been removed\n"));
	else if (r!=KErrNone)
		User::Leave(r);
	TheText->CopyToStoreL(TheWriteBoard->Store(),TheWriteBoard->StreamDictionary(),0,documentLength);
	//
	TheText->Reset();
	TheText->SetPictureFactory(factory,&resolver);
	documentLength=TheText->DocumentLength();
	test(documentLength==0);
	OpenReadClipboardLC();
	TheText->PasteFromStoreL(TheReadBoard->Store(),TheReadBoard->StreamDictionary(),documentLength);
		test(TheText->DocumentLength()==4);
		test(TheText->ParagraphCount()==1);
		test(TheText->PictureCount()==4);
	/////////////////////////////////////////////////////////////////////////////
	CleanupStack::PopAndDestroy();  // Last clipboard object
	CleanupStack::PopAndDestroy();  // store
	CleanupStack::PopAndDestroy();  // TheTextObject
	delete factory;
	delete TheGlobalParaLayer;
	delete TheGlobalCharLayer;
	session.Close();
	}
	

	LOCAL_C void testRichTextCutPaste1()
//
//
	{
	test.Next(_L("Cut&Paste - preserving formatting"));
	TheFileName=_L("z:\\test\\app-framework\\etext\\rtclipb2.pml");
	ParseRichTextDocumentLC();
	//
	CRichText* copiedText=CRichText::NewL(TheGlobalParaLayer,TheGlobalCharLayer);
	////////////////////////////////////////////////////////////////////////////
	TheReadBoard=NULL;
	TheWriteBoard=NULL;
	//
	// Scenario 1
	test.Start(_L("multiple partial phrases"));
	OpenWriteClipboardLC();
	TheText->CopyToStoreL(TheWriteBoard->Store(),TheWriteBoard->StreamDictionary(),36,73);
	OpenReadClipboardLC();
	copiedText->Reset();
	TInt pasted=0;
	TRAPD(ret,
	pasted=copiedText->PasteFromStoreL(TheReadBoard->Store(),TheReadBoard->StreamDictionary(),0));
	test(ret==KErrNone);
	test(pasted==73);
	test(copiedText->DocumentLength()==73);
	test(copiedText->ParagraphCount()==3);
	//
	// Scenario 2
	test.Next(_L("multiple whole phrases"));
	OpenWriteClipboardLC();
	TheText->CopyToStoreL(TheWriteBoard->Store(),TheWriteBoard->StreamDictionary(),51,60);
	copiedText->Reset();
	OpenReadClipboardLC();
	pasted=copiedText->PasteFromStoreL(TheReadBoard->Store(),TheReadBoard->StreamDictionary(),0);
	test(pasted==60);
	test(copiedText->DocumentLength()==60);
	test(copiedText->ParagraphCount()==3);
	//
	// Scenario 3
	test.Next(_L("single middle portion of a phrase"));
	OpenWriteClipboardLC();
	TheText->CopyToStoreL(TheWriteBoard->Store(),TheWriteBoard->StreamDictionary(),53,2);
	copiedText->Reset();
	OpenReadClipboardLC();
	pasted=copiedText->PasteFromStoreL(TheReadBoard->Store(),TheReadBoard->StreamDictionary(),0);
	test(pasted==2);
	test(copiedText->DocumentLength()==2);
	test(copiedText->ParagraphCount()==1);
	//
	// Scenario 4
	test.Next(_L("multiple phrases, starting/ending on shared paragraphs"));
	OpenWriteClipboardLC();
	TheText->CopyToStoreL(TheWriteBoard->Store(),TheWriteBoard->StreamDictionary(),0,140);
	copiedText->Reset();
	OpenReadClipboardLC();
	pasted=copiedText->PasteFromStoreL(TheReadBoard->Store(),TheReadBoard->StreamDictionary(),0);
	test(pasted==140);
	test(copiedText->DocumentLength()==140);
	test(copiedText->ParagraphCount()==5);

	//
	// Scenario 5
	test.Next(_L("zero phrases"));
	OpenWriteClipboardLC();
	TheText->CopyToStoreL(TheWriteBoard->Store(),TheWriteBoard->StreamDictionary(),70,10);
	copiedText->Reset();
	OpenReadClipboardLC();
	pasted=copiedText->PasteFromStoreL(TheReadBoard->Store(),TheReadBoard->StreamDictionary(),0);
	test(pasted==10);
	test(copiedText->DocumentLength()==10);
	test(copiedText->ParagraphCount()==1);

	//
	CleanupStack::PopAndDestroy();  // Last clipboard object
	CleanupStack::PopAndDestroy();  // TheTextObject
	delete copiedText;
	delete TheGlobalParaLayer;
	delete TheGlobalCharLayer;
	test.End();
	}


/**
@SYMTestCaseID          SYSLIB-ETEXT-CT-4001
@SYMTestCaseDesc        Pasted final paragraph formatting should match copied final paragraph
                        formatting.
@SYMTestPriority        High
@SYMTestActions         Enter three paragraphs into an empty document with the last paragraph
                        *not* terminated by a paragraph delimiter.  Apply some custom
                        formatting to the last paragraph then copy and paste all of the text
                        into a new empty document.
@SYMTestExpectedResults The formatting in the pasted final paragraph should match the copied.
@SYMDEF                 INC115783
*/
LOCAL_C void testRichTextCutPaste2()
	{
	test.Next(_L(" @SYMTestCaseID:SYSLIB-ETEXT-CT-4001 Pasted final paragraph format should match copied final paragraph format "));	
	TheReadBoard=NULL;
	TheWriteBoard=NULL;
	TheFileName=_L("z:\\test\\app-framework\\etext\\rtclipb2.pml");  // dummy - just to get global layers
	ParseRichTextDocumentLC();
	TheText->Reset();
	TheText->InsertL(0,_L("\x2029\x2029SomeData")); //3 paras, last has no ending para delimiter);

	//create paragraph formatting (yellow bkg, indent & bullets)
	CParaFormat* paraFormatIn = CParaFormat::NewLC();
	paraFormatIn->iBullet=new(ELeave)TBullet;  
	paraFormatIn->iBullet->iHeightInTwips=240;
	paraFormatIn->iFillColor = 0xffffff00;
	paraFormatIn->iIndentInTwips = 600;
	TParaFormatMask paraFormatMask;
	paraFormatMask.SetAttrib(EAttBullet);
	paraFormatMask.SetAttrib(EAttFillColor);
	paraFormatMask.SetAttrib(EAttIndent);

	TheText->ApplyParaFormatL(paraFormatIn,paraFormatMask,3,0); //Apply format to last para only
	
	OpenWriteClipboardLC();
	TheText->CopyToStoreL(TheWriteBoard->Store(),TheWriteBoard->StreamDictionary(),0,TheText->DocumentLength());

	TheText->Reset();
	test(TheText->DocumentLength()==0);
	OpenReadClipboardLC();
	TheText->PasteFromStoreL(TheReadBoard->Store(),TheReadBoard->StreamDictionary(),TheText->DocumentLength());
	test(TheText->DocumentLength()==_L("\x2029\x2029SomeData").Length());
	test(TheText->ParagraphCount()==3);
	
	CParaFormat* paraFormatOut = CParaFormat::NewLC();
	TheText->GetParagraphFormatL(paraFormatOut,3);
	
	test(paraFormatOut->IsEqual(*paraFormatIn,paraFormatMask));// in and out should match

	CleanupStack::PopAndDestroy(4);
	delete TheGlobalParaLayer;
	delete TheGlobalCharLayer;
	}


LOCAL_C void testRichTextCutPaste3()
// 
//
    {
	test.Next(_L("Cutting paragraph of constant character formatting"));
	TheFileName=_L("z:\\test\\app-framework\\etext\\rtclipb3.pml");
	ParseRichTextDocumentLC();
	//
	TheReadBoard=NULL;
	TheWriteBoard=NULL;
	//
	test.Start(_L("Copying to clipboard"));
	OpenWriteClipboardLC();
	TheText->CopyToStoreL(TheWriteBoard->Store(),TheWriteBoard->StreamDictionary(),4,3);
	//
	CleanupStack::PopAndDestroy();  // Last clipboard object
	CleanupStack::PopAndDestroy();  // TheTextObject
	delete TheGlobalParaLayer;
	delete TheGlobalCharLayer;
	test.End();
	}



LOCAL_C void testRichTextCutPaste()
// 
//
    {
	test.Start(_L("Cut&Paste - with Rich Text"));
	ParseRichTextDocumentLC();
	OpenWriteClipboardLC();
	test.Next(_L("Copy zero-length text to the clipboard"));
	TheText->CopyToStoreL(TheWriteBoard->Store(),TheWriteBoard->StreamDictionary(),0,0);

	OpenReadClipboardLC();
	test.Next(_L("Paste from empty clipboard"));
	TInt err=0;
	TRAPD(ret,
	err=TheText->PasteFromStoreL(TheReadBoard->Store(),TheReadBoard->StreamDictionary(),TheText->DocumentLength()));
    UNUSED_VAR(ret);
	if (err==KErrNotFound)
		test.Printf(_L("        No recognised data to paste or clipboard empty\n\r"));
	TInt fieldCount=TheText->FieldCount();
	test(fieldCount==0);
	////////////////////////////////////////////////////////////////////////////
	test.Next(_L("Paste into empty RichText"));
	TheText->Reset();
	TheText->InsertL(TheText->DocumentLength(),_L("SomeData"));
	OpenWriteClipboardLC();
	TheText->CopyToStoreL(TheWriteBoard->Store(),TheWriteBoard->StreamDictionary(),0,TheText->DocumentLength());
	TheText->Reset();
		test(TheText->DocumentLength()==0);
	OpenReadClipboardLC();
	TheText->PasteFromStoreL(TheReadBoard->Store(),TheReadBoard->StreamDictionary(),TheText->DocumentLength());
		test(TheText->DocumentLength()==_L("SomeData").Length());
		test(TheText->ParagraphCount()==1);
		fieldCount=TheText->FieldCount();
		test(fieldCount==0);
	/////////////////////////////////////////////////////////////////////////////
	test.Next(_L("Pasting text only - no paragraph delimiter"));
	TheText->Reset();
	TheText->InsertL(0,_L("the  end"));
	TheText->PasteFromStoreL(TheReadBoard->Store(),TheReadBoard->StreamDictionary(),4);
	test(TheText->DocumentLength()==16);
	//////////////////////////////////////////////////////////////////////////
	test.Next(_L("Paste @ start (pos=0)"));
	TheText->Reset();
	TheText->InsertL(TheText->DocumentLength(),_L("SomeData"));
	TheText->PasteFromStoreL(TheReadBoard->Store(),TheReadBoard->StreamDictionary(),0);
		test(TheText->DocumentLength()==_L("SomeDataSomeData").Length());
		test(TheText->ParagraphCount()==1);
		fieldCount=TheText->FieldCount();
		test(fieldCount==0);
	////////////////////////////////////////////////////////////////////////////
	test.Next(_L("Paste @ end   (DocumentLength())"));
	TheText->PasteFromStoreL(TheReadBoard->Store(),TheReadBoard->StreamDictionary(),TheText->DocumentLength());
		test(TheText->DocumentLength()==_L("SomeDataSomeDataSomeData").Length());
		test(TheText->ParagraphCount()==1);
		fieldCount=TheText->FieldCount();
		test(fieldCount==0);
	////////////////////////////////////////////////////////////////////////////
	test.Next(_L("Paste @ middle"));
	TheText->PasteFromStoreL(TheReadBoard->Store(),TheReadBoard->StreamDictionary(),4);
	fieldCount=TheText->FieldCount();
		test(fieldCount==0);
		TBuf<33> buf(_L("SomeSomeDataDataSomeDataSomeData"));
		test(TheText->DocumentLength()==buf.Length());
		buf.Append(CEditableText::EParagraphDelimiter);
		test(TheText->Read(0)==buf);
		test(TheText->ParagraphCount()==1);
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	test.Next(_L("Pasting rich text inbetween 2 pictures"));
	TheText->Reset();
	//
	CXzePicture* pic1=CXzePicture::NewL('1');
	CXzePicture* pic2=CXzePicture::NewL('2');
	//
	TPictureHeader hdr1;
	TPictureHeader hdr2;
	//
	hdr1.iPictureType=KUidXzePictureType;
	hdr2.iPictureType=KUidXzePictureType;
	//
	hdr1.iPicture=pic1;
	hdr2.iPicture=pic2;
	//
	TheText->InsertL(0,hdr2);
	TheText->InsertL(0,hdr1);
	//
	OpenWriteClipboardLC();
	TheText->CopyToStoreL(TheWriteBoard->Store(),TheWriteBoard->StreamDictionary(),0,TheText->DocumentLength());
	//
	OpenReadClipboardLC();

	TheText->PasteFromStoreL(TheReadBoard->Store(),TheReadBoard->StreamDictionary(),1);
		test(TheText->DocumentLength()==4);
		test(TheText->ParagraphCount()==1);
	/////////////////////////////////////////////////////////////////////////////
	test.Next(_L("Pasting rich text with para delimiters"));
	TheText->InsertL(1,CEditableText::EParagraphDelimiter);
	//
	OpenWriteClipboardLC();
	TheText->CopyToStoreL(TheWriteBoard->Store(),TheWriteBoard->StreamDictionary(),0,TheText->DocumentLength());
	//
	OpenReadClipboardLC();
	TheText->PasteFromStoreL(TheReadBoard->Store(),TheReadBoard->StreamDictionary(),1);
		test(TheText->DocumentLength()==10);
		test(TheText->ParagraphCount()==3);
		
	/////////////////////////////////////////////////////////////////////////////	
	CleanupStack::PopAndDestroy();  // Last clipboard object
	CleanupStack::PopAndDestroy();  // TheTextObject
	delete TheGlobalParaLayer;
	delete TheGlobalCharLayer;
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
// Test the streaming framework.
//
    {

	test.Title();
	
	__UHEAP_MARK;
	setupCleanup();

	TRAPD(r, testRichTextCutPaste());
    test(r == KErrNone);

	TRAP(r, testRichTextCutPaste1());
    test(r == KErrNone);

	TRAP(r, testRichTextCutPaste1a());
    test(r == KErrNone);

	TRAP(r, testRichTextCutPaste1b());
    test(r == KErrNone);

	TRAP(r, testRichTextCutPaste2());
    test(r == KErrNone);

	TRAP(r, testRichTextCutPaste3());
    test(r == KErrNone);

	delete TheTrapCleanup;
	
	__UHEAP_MARKEND;
	
	::DeleteDataFile(KOutputFile);		//deletion of data files must be before call to End() - DEF047652
	
	test.End();
	test.Close();

	return 0;
    }
