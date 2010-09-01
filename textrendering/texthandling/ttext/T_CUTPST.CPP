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
#include <txtglobl.h>
#include <s32mem.h>
#include <s32file.h>
#include <e32test.h>

#define UNUSED_VAR(a) a = a

const TInt KTestCleanupStack=0x40;


LOCAL_D RTest test(_L("Cut & Paste"));
LOCAL_D CTrapCleanup* TheTrapCleanup=NULL;
LOCAL_D CPlainText* TheTextObject=NULL;
LOCAL_D CClipboard* TheWriteBoard=NULL;
LOCAL_D CClipboard* TheReadBoard=NULL;
LOCAL_D RFs TheSession;


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


LOCAL_C void testPlainTextCutPaste2()
	{
	TheTextObject=CPlainText::NewL();
	CleanupStack::PushL(TheTextObject);
	OpenWriteClipboardLC(); // delete the system clipboard file if it exists.

	// Copy zero-length text to the clipboard.
	test.Next(_L("Copy zero-length text to the clipboard"));
	TheTextObject->CopyToStoreL(TheWriteBoard->Store(),TheWriteBoard->StreamDictionary(),0,0);

	OpenReadClipboardLC();
	test(TheTextObject->DocumentLength()==0);

	// Paste zero-length text from the clipboard.
	test.Next(_L("Paste zero-length text from the clipboard"));
	TheTextObject->PasteFromStoreL(TheReadBoard->Store(),TheReadBoard->StreamDictionary(),0);

	// Copy multiple paragraphs to the clipboard
	test.Next(_L("PasteFromStoreL(aPos,aMaxPasteLength)"));
	TBuf<512> buf(_L("Here is para one."));
	buf.Append(CEditableText::EParagraphDelimiter);
	buf.Append(_L("This is paragraph two."));
	buf.Append(CEditableText::EParagraphDelimiter);
	TheTextObject->InsertL(0,buf);
	int text_length = TheTextObject->DocumentLength();

	OpenWriteClipboardLC();
	TheTextObject->CopyToStoreL(TheWriteBoard->Store(),TheWriteBoard->StreamDictionary(),0,TheTextObject->DocumentLength());
	TheTextObject->Reset();
	test(TheTextObject->DocumentLength()==0);

	// Now paste the text.
	OpenReadClipboardLC();
	TheTextObject->PasteFromStoreL(TheReadBoard->Store(),TheReadBoard->StreamDictionary(),TheTextObject->DocumentLength());
	test(TheTextObject->DocumentLength()==text_length);
	TInt fieldCount=TheTextObject->FieldCount();
	test(fieldCount==0);

	CleanupStack::PopAndDestroy();  // Last clipboard object
	CleanupStack::PopAndDestroy();  // TheTextObject
	TheWriteBoard=NULL;
	TheReadBoard=NULL;
	}

LOCAL_C void testPlainTextCutPaste()
// 
//
    {
	test.Start(_L(" @SYMTestCaseID:SYSLIB-ETEXT-LEGACY-CPLAIN-0001 Cut&Paste - with plainText "));
	TheTextObject=CPlainText::NewL();
	CleanupStack::PushL(TheTextObject);
	OpenWriteClipboardLC(); // delete the system clipboard file if it exists.
	test(TheTextObject->DocumentLength()==0);
	//
	test.Next(_L("Paste from empty store"));
	OpenReadClipboardLC();
	TInt charCount=0;
	TRAPD(ret,
	charCount=TheTextObject->PasteFromStoreL(TheReadBoard->Store(),TheReadBoard->StreamDictionary(),TheTextObject->DocumentLength()));
    UNUSED_VAR(ret);
	if (charCount<=0)
		test.Printf(_L("        No recognised data to paste or clipboard empty\n\r"));
	TInt fieldCount=TheTextObject->FieldCount();
	test(fieldCount==0);
	//
//	test.Next(_L("Paste from clipboard with no recognised types"));
//	WriteForeignDataToClipboardL();
	//
	test.Next(_L("Paste into empty PlainText"));
	TheTextObject->InsertL(TheTextObject->DocumentLength(),_L("SomeData"));
	OpenWriteClipboardLC();
	TheTextObject->CopyToStoreL(TheWriteBoard->Store(),TheWriteBoard->StreamDictionary(),0,TheTextObject->DocumentLength());
	TheTextObject->Reset();
		test(TheTextObject->DocumentLength()==0);
	OpenReadClipboardLC();
	TheTextObject->PasteFromStoreL(TheReadBoard->Store(),TheReadBoard->StreamDictionary(),TheTextObject->DocumentLength());
		test(TheTextObject->DocumentLength()==_L("SomeData").Length());
	fieldCount=TheTextObject->FieldCount();
	test(fieldCount==0);
	//
	test.Next(_L("Paste @ start (pos=0)"));
	TheTextObject->PasteFromStoreL(TheReadBoard->Store(),TheReadBoard->StreamDictionary(),0);
		test(TheTextObject->DocumentLength()==_L("SomeDataSomeData").Length());
	fieldCount=TheTextObject->FieldCount();
	test(fieldCount==0);
	//
	test.Next(_L("Paste @ end   (DocumentLength())"));
	TheTextObject->PasteFromStoreL(TheReadBoard->Store(),TheReadBoard->StreamDictionary(),TheTextObject->DocumentLength());
		test(TheTextObject->DocumentLength()==_L("SomeDataSomeDataSomeData").Length());
	fieldCount=TheTextObject->FieldCount();
	test(fieldCount==0);
	//
	test.Next(_L("Paste @ middle"));
	TheTextObject->PasteFromStoreL(TheReadBoard->Store(),TheReadBoard->StreamDictionary(),4);
	fieldCount=TheTextObject->FieldCount();
	test(fieldCount==0);
	TBuf<33> buf(_L("SomeSomeDataDataSomeDataSomeData"));
		test(TheTextObject->DocumentLength()==buf.Length());
		buf.Append(CEditableText::EParagraphDelimiter);
		test(TheTextObject->Read(0)==buf);
	//
	CleanupStack::PopAndDestroy();  // Last clipboard object
	CleanupStack::PopAndDestroy();  // TheTextObject
	TheWriteBoard=NULL;
	TheReadBoard=NULL;
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
// Test the streaming framework.
//
    {

	test.Title();
	__UHEAP_MARK;
	setupCleanup();
	TRAPD(r,testPlainTextCutPaste());
    test(r == KErrNone);
	TRAP(r,testPlainTextCutPaste2());
    test(r == KErrNone);

	delete TheTrapCleanup;
	
	__UHEAP_MARKEND;
	test.End();
	test.Close();
	return 0;
    }
