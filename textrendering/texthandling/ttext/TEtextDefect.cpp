/*
* Copyright (c) 2004-2009 Nokia Corporation and/or its subsidiary(-ies).
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
#include <charconv.h>
#include <gdi.h>
#include <conpics.h>
#include <txtrich.h>
#include <apadef.h>

#include "TXTPLAIN.H"
#include "TxtWriter.h"

//Used for supressing warning in OOM tests
 #define __UNUSED_VAR(var) var = var

// this fixes a MSVC link warning
#ifdef __VC32__
#pragma comment (linker, "/opt:noref") 
#endif

_LIT(KTestName, "Start of Tests...");
RTest theTest(KTestName);

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//Test macroses and functions
LOCAL_C void Check(TInt aValue, TInt aLine)
	{
	if(!aValue)
		{
		theTest(EFalse, aLine);
		}
	}
LOCAL_C void Check(TInt aValue, TInt aExpected, TInt aLine)
	{
	if(aValue != aExpected)
		{
		theTest.Printf(_L("*** Expected error: %d, got: %d\r\n"), aExpected, aValue);
		theTest(EFalse, aLine);
		}
	}
#define TEST(arg) ::Check((arg), __LINE__)
#define TEST2(aValue, aExpected) ::Check(aValue, aExpected, __LINE__)


LOCAL_C void Inc049456L()
	{
   	theTest.Next(_L("Inc049456L"));

	CPlainTextConverter* converter = CPlainTextConverter::NewLC();
	CleanupStack::PopAndDestroy(converter);
	}
	
LOCAL_C void OOM049456L()
	{
   	theTest.Next(_L("OOM049456L"));

	TInt tryCount=0;
 	TInt error = KErrNone;
 	__UNUSED_VAR(tryCount);
 	
 	do
 		{
 		__UHEAP_MARK;
 
 		// find out the number of open handles
 		TInt startProcessHandleCount;
 		TInt startThreadHandleCount;
 		RThread().HandleCount(startProcessHandleCount, startThreadHandleCount);
 		
 		__UHEAP_SETFAIL(RHeap::EDeterministic, ++tryCount);
 	
 		TRAP(error,Inc049456L()); 	
 								
 		__UHEAP_SETFAIL(RHeap::ENone,0);
 		
 		// check that no handles have leaked
 		TInt endProcessHandleCount;
 		TInt endThreadHandleCount;
 		RThread().HandleCount(endProcessHandleCount, endThreadHandleCount);
 
 		TEST(startProcessHandleCount == endProcessHandleCount);
 		TEST(startThreadHandleCount  == endThreadHandleCount);
 				
 		__UHEAP_MARKEND;
 		
 		}while(error==KErrNoMemory);
 		
 	TEST2(error, KErrNone);
 	theTest.Printf(_L("- server succeeded at heap failure rate of %i\n"),tryCount);		
	}




LOCAL_C void Inc051360L()
	{
   	theTest.Next(_L("Inc051360L"));
   	
	// Test data to force a remainder of 2 from the charconv unicode conversion.
	// The etext buffer is 1024 bytes that truncates the last utf-8 character.
	// It needs three bytes but only has two, hence remainder 2.
	const TUint8 KUtf8TextJapanese [] = 
	{
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, // 1000 bytes
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, // 1020
	0x20, 0x20, 0xE3, 0x81, 0x82, 0xE3, 0x81, 0x8B, // total 1028
	}; //                   ^ 1025, will not be read on first pass
	
	// Need to know the data length for our buffers.
	const TUint KBufferSize = 1028;

	// Copy the raw data into an 8-bit descriptor
	TBuf8<KBufferSize> textBuffer;
	textBuffer.Copy (KUtf8TextJapanese, KBufferSize);

	// The unicode conversion of the result expected
	const TUint16 KUnicodeTextJapaneseResult [] = {0x3042, 0x304B,};

	TBuf16 <2> unicodeConversion;
	unicodeConversion.Copy (KUnicodeTextJapaneseResult, 2);
		
	// The converter
	CPlainTextConverter* plainText = CPlainTextConverter::NewLC();

	// The input buffer
	CBufFlat* inbuffer = CBufFlat::NewL(KBufferSize);
	CleanupStack::PushL (inbuffer);
	
	inbuffer->InsertL (0, textBuffer);
	
	// The input stream
	RBufReadStream inputStr (*inbuffer, 0);
	CleanupClosePushL (inputStr);

	// The output buffer
	CBufFlat* outbuffer = CBufFlat::NewL(KBufferSize);
	CleanupStack::PushL (outbuffer);
	
	// The output stream
	RBufWriteStream outputStr (*outbuffer, 0);
	CleanupClosePushL (outputStr);
	
	// Input specifications
	CPlainText::TImportExportParam param;
	param.iOutputInternal  = TRUE; // force output to internal format
	param.iForeignEncoding = KCharacterSetIdentifierUtf8;
	
	// The result of the operation
	CPlainText::TImportExportResult result;
	
	// Translate the data
	TPlainTextReader::TranslateL(param, result, outputStr, inputStr);
	
	// Get the 8-bit data into a 16-bit buffer.
	// Can't use Copy as this will store each byte on a word boundary!
	TPtr8 ptr8 (outbuffer->Ptr(outbuffer->Size()-4));
	const TUint16* ptr = (TUint16*) (ptr8.Ptr());
	TPtrC16 des16 (ptr, 2);

	TEST(unicodeConversion == des16);
	
	CleanupStack::PopAndDestroy (&outputStr);	
	CleanupStack::PopAndDestroy (outbuffer);	
	CleanupStack::PopAndDestroy (&inputStr);	
	CleanupStack::PopAndDestroy (inbuffer);	
	CleanupStack::PopAndDestroy (plainText);
	}
	
LOCAL_C void OOM051360L()
	{
   	theTest.Next(_L("OOM051360L"));

	TInt tryCount=0;
 	TInt error = KErrNone;
 	__UNUSED_VAR(tryCount);
 	
 	do
 		{
 		__UHEAP_MARK;
 
 		// find out the number of open handles
 		TInt startProcessHandleCount;
 		TInt startThreadHandleCount;
 		RThread().HandleCount(startProcessHandleCount, startThreadHandleCount);
 		
 		__UHEAP_SETFAIL(RHeap::EDeterministic, ++tryCount);
 	
 		TRAP(error,Inc051360L()); 	
 								
 		__UHEAP_SETFAIL(RHeap::ENone,0);
 		
 		// check that no handles have leaked
 		TInt endProcessHandleCount;
 		TInt endThreadHandleCount;
 		RThread().HandleCount(endProcessHandleCount, endThreadHandleCount);
 
 		TEST(startProcessHandleCount == endProcessHandleCount);
 		TEST(startThreadHandleCount  == endThreadHandleCount);
 				
 		__UHEAP_MARKEND;
 		
 		}while(error==KErrNoMemory);
 		
 	TEST2(error, KErrNone);
 	theTest.Printf(_L("- server succeeded at heap failure rate of %i\n"),tryCount);		
	}
	
LOCAL_C void OOM056552L()
	{
	theTest.Next(_L("OOM056552L"));

	TInt tryCount=0;
 	TInt error = KErrNone;
 	__UNUSED_VAR(tryCount);
 	
 	do
 		{
 		__UHEAP_MARK;
 	
 	    CParaFormatLayer* paraLayer=CParaFormatLayer::NewL();
	    CCharFormatLayer* charLayer=CCharFormatLayer::NewL();
   	    CRichText* richText = CRichText::NewL(paraLayer,charLayer);
   	    CXzePicture* pic=CXzePicture::NewL('x');
   	    TPictureHeader header;
   	    header.iPictureType = KUidPictureTypeDoor;
   	    header.iPicture=pic;
 		
 		__UHEAP_SETFAIL(RHeap::EDeterministic, ++tryCount);
 	
 		TRAP(error,	richText->InsertL(richText->DocumentLength(), header)); 	
 								
 		__UHEAP_SETFAIL(RHeap::ENone,0);
 		
 		delete paraLayer; paraLayer = NULL;
 		delete charLayer; charLayer = NULL;
 		delete richText; richText = NULL;	
 		
 		__UHEAP_MARKEND;
 		
 		}while(error==KErrNoMemory);
 		
 	theTest(error==KErrNone);
 	theTest.Printf(_L("	richText->InsertL - succeeded at heap failure rate of %i\n"),tryCount);	
	}
/////////////////////////////////////////////////////////////////////////////////////////////////
// Testing the fix for
// "INC055971  NTT - Received MMS with line break "CR" set does not cause line feed."
// In order to make the testing easier, MOutputChar, MTextWriter, TSLBTransaltor, 
// TParagraphTextWriter, TLineTextWriter production classes are used outside their environment.
// TOutputChar test class implements MOutputChar interface. It is used to collect the character
// output from the processing of the imput character sequences. Then, the output is tested against
// the expected set of output characters.
//
// The follwing translation rules are tested:
// 1) Organising by paragraph
//    - 0x0D      - line break;
//    - 0x0A      - line break;
//    - 0x0D 0x0A - line break;
// 2) Organising by line
//    - single line break - space;
//    - double line break - paragraph delimiter;

TBuf<32> TheOutputTestBuf;//Here the output is collected and then asserted

class TOutputChar : public MOutputChar
	{
public:
	virtual void OutputCharL(TText aChar)
		{
		TheOutputTestBuf.Append(aChar);
		}
	};

static void TranslateToEofTestL(TSLBTransaltor& aSLBTranslator, const TDesC& aTestBuf)
	{
	for(TInt i=0;i<aTestBuf.Length();++i)
		{
		TText c = aTestBuf[i];
		aSLBTranslator.ProcessL(c);
		}
	aSLBTranslator.FlushL();
	}

static void INC055971L()
	{
	TBuf<32> testBuf;
	TOutputChar outputChar;

   	theTest.Next(_L("INC055971L - OrganiseByParagraph test"));

		{
		TParagraphTextWriter paragraphTextWriter(outputChar);
		TSLBTransaltor slbTranslator(paragraphTextWriter);

		testBuf = _L("\xD");
		TheOutputTestBuf.Zero();
		::TranslateToEofTestL(slbTranslator, testBuf);
		TEST(TheOutputTestBuf.Length() == 1);
		TEST(TheOutputTestBuf[0] == CEditableText::EParagraphDelimiter);

		testBuf = _L("\xA");
		TheOutputTestBuf.Zero();
		::TranslateToEofTestL(slbTranslator, testBuf);
		TEST(TheOutputTestBuf.Length() == 1);
		TEST(TheOutputTestBuf[0] == CEditableText::EParagraphDelimiter);

		testBuf = _L("\xD\xA");
		TheOutputTestBuf.Zero();
		::TranslateToEofTestL(slbTranslator, testBuf);
		TEST(TheOutputTestBuf.Length() == 1);
		TEST(TheOutputTestBuf[0] == CEditableText::EParagraphDelimiter);

		testBuf = _L("zz\xD\xA\xD\xA\xAz\xD");
		TheOutputTestBuf.Zero();
		::TranslateToEofTestL(slbTranslator, testBuf);
		TEST(TheOutputTestBuf.Length() == 7);
		TEST(TheOutputTestBuf[0] == 'z');
		TEST(TheOutputTestBuf[1] == 'z');
		TEST(TheOutputTestBuf[2] == CEditableText::EParagraphDelimiter);
		TEST(TheOutputTestBuf[3] == CEditableText::EParagraphDelimiter);
		TEST(TheOutputTestBuf[4] == CEditableText::EParagraphDelimiter);
		TEST(TheOutputTestBuf[5] == 'z');
		TEST(TheOutputTestBuf[6] == CEditableText::EParagraphDelimiter);

		testBuf = _L("This\xDIs\xATest\xD\xAMessage");
		TheOutputTestBuf.Zero();
		::TranslateToEofTestL(slbTranslator, testBuf);
		TEST(TheOutputTestBuf.Length() == 20);
		TEST(TheOutputTestBuf[4] == CEditableText::EParagraphDelimiter);
		TEST(TheOutputTestBuf[7] == CEditableText::EParagraphDelimiter);
		TEST(TheOutputTestBuf[12] == CEditableText::EParagraphDelimiter);
		}

   	theTest.Next(_L("INC055971L - OrganiseByLine test"));

		{
		TLineTextWriter lineTextWriter(outputChar);
		TSLBTransaltor slbTranslator(lineTextWriter);

		testBuf = _L("\xD");
		TheOutputTestBuf.Zero();
		::TranslateToEofTestL(slbTranslator, testBuf);
		TEST(TheOutputTestBuf.Length() == 1);
		TEST(TheOutputTestBuf[0] == ' ');

		testBuf = _L("\xA");
		TheOutputTestBuf.Zero();
		::TranslateToEofTestL(slbTranslator, testBuf);
		TEST(TheOutputTestBuf.Length() == 1);
		TEST(TheOutputTestBuf[0] == ' ');

		testBuf = _L("\xD\xA");
		TheOutputTestBuf.Zero();
		::TranslateToEofTestL(slbTranslator, testBuf);
		TEST(TheOutputTestBuf.Length() == 1);
		TEST(TheOutputTestBuf[0] == ' ');

		testBuf = _L("\xD\xA\xD\xA");
		TheOutputTestBuf.Zero();
		::TranslateToEofTestL(slbTranslator, testBuf);
		TEST(TheOutputTestBuf.Length() == 1);
		TEST(TheOutputTestBuf[0] == CEditableText::EParagraphDelimiter);

		testBuf = _L("\xD\xD");
		TheOutputTestBuf.Zero();
		::TranslateToEofTestL(slbTranslator, testBuf);
		TEST(TheOutputTestBuf.Length() == 1);
		TEST(TheOutputTestBuf[0] == CEditableText::EParagraphDelimiter);

		testBuf = _L("\xA\xA");
		TheOutputTestBuf.Zero();
		::TranslateToEofTestL(slbTranslator, testBuf);
		TEST(TheOutputTestBuf.Length() == 1);
		TEST(TheOutputTestBuf[0] == CEditableText::EParagraphDelimiter);

		testBuf = _L("\xA\xD");
		TheOutputTestBuf.Zero();
		::TranslateToEofTestL(slbTranslator, testBuf);
		TEST(TheOutputTestBuf.Length() == 1);
		TEST(TheOutputTestBuf[0] == CEditableText::EParagraphDelimiter);

		testBuf = _L("\xD\xA\xA");
		TheOutputTestBuf.Zero();
		::TranslateToEofTestL(slbTranslator, testBuf);
		TEST(TheOutputTestBuf.Length() == 1);
		TEST(TheOutputTestBuf[0] == CEditableText::EParagraphDelimiter);

		testBuf = _L("\xD\xAz\xAzz\xA\xD");
		TheOutputTestBuf.Zero();
		::TranslateToEofTestL(slbTranslator, testBuf);
		TEST(TheOutputTestBuf.Length() == 6);
		TEST(TheOutputTestBuf[0] == ' ');
		TEST(TheOutputTestBuf[1] == 'z');
		TEST(TheOutputTestBuf[2] == ' ');
		TEST(TheOutputTestBuf[3] == 'z');
		TEST(TheOutputTestBuf[4] == 'z');
		TEST(TheOutputTestBuf[5] == CEditableText::EParagraphDelimiter);
		}
	}

/**
@SYMTestCaseID SYSLIB-ETEXT-CT-3346
@SYMTestCaseDesc Tests the fix for the problem where EOD character was not getting
formatted when ApplyCharFormatL() function called, caused text to appear clipped on 
MOAP devices.
@SYMTestPriority High
@SYMTestActions Create CRichText object and insert some text.  Apply font and size
formatting to entire text.  Check that EOD character formatting is consistant with rest
of the text formatting.
@SYMTestExpectedResults Formatting for EOD character should be the same as the rest of
the text formatting.
@SYMDEF INC097216: When font size is set as small, bottom of a text is clipped on wk38 (MOAP)
*/
LOCAL_C void INC097216L()
	{
	theTest.Next(_L(" @SYMTestCaseID:SYSLIB-ETEXT-CT-3346 INC097216L - Test EOD character is formatted with rest of text "));
	
	__UHEAP_MARK;

    CParaFormatLayer* paraLayer=CParaFormatLayer::NewL();
    CCharFormatLayer* charLayer=CCharFormatLayer::NewL();
    CRichText* richText = CRichText::NewL(paraLayer,charLayer);
	
	_LIT(KTestText, "The quick brown fox jumped over the lazy dog");
	
	richText->InsertL(0, KTestText);
	TCharFormat charFormat(_L("Times"), 100);
	TCharFormatMask formatMask;
	
	formatMask.SetAttrib(EAttFontHeight);
	
	TInt textLength = richText->DocumentLength();
	richText->ApplyCharFormatL(charFormat, formatMask, 0, textLength); 			
	
	richText->GetCharFormat(charFormat, formatMask, textLength-1, 1); // get format info for last text character
	TInt characterFontHeight = charFormat.iFontSpec.iHeight; 
	
	richText->GetCharFormat(charFormat, formatMask, textLength, 1); // get format info for EOD character
	TInt EodFontHeight = charFormat.iFontSpec.iHeight;	
	
	TEST(characterFontHeight == EodFontHeight);
	
	delete paraLayer; paraLayer = NULL;
	delete charLayer; charLayer = NULL;
	delete richText; richText = NULL;	
	
	__UHEAP_MARKEND;	
	}
	
/**
@SYMTestCaseID SYSLIB-ETEXT-CT-3386
@SYMTestCaseDesc Tests the fix INC101996:CEikRichTextEditor control don’t support anti-aliasing font 
@SYMTestPriority High
@SYMTestActions Create CRichText object and insert some text.  Apply  formatting to entire string 
				then apply antialiasing formatting to part of the string.
				Ensure that the anti-aliasing formatting information is applied as expected.
@SYMTestExpectedResults Antialiasing formatting should be applied to the correct part of the string
 				and the rest of the string should remain unchanged 
@SYMDEF INC101996
*/
LOCAL_C void INC101996L()
	{
	theTest.Next(_L("@SYMTestCaseID:SYSLIB-ETEXT-CT-3386 INC101996 CEikRichTextEditor control don't support anti-aliasing font"));

	__UHEAP_MARK;

    CParaFormatLayer* paraLayer=CParaFormatLayer::NewL();
    CCharFormatLayer* charLayer=CCharFormatLayer::NewL();
    CRichText* richText = CRichText::NewL(paraLayer,charLayer);
	
	_LIT(KTestText, "The quick brown fox jumped over the lazy dog");
	_LIT(KDefaulFormattedText, "The quick brown fox ju");
	_LIT(KAntiAliasedText, "mped over the lazy dog\x2029");
	
	//insert the test text into the string
	richText->InsertL(0, KTestText);
	
	TCharFormat defaultCharFormat(_L("Times"), 100);
	TCharFormat antiAliasedCharFormat(_L("Times"), 100);
	
	//Set up antiAliasedCharFormat to allow anti-aliasing 
	antiAliasedCharFormat.iFontSpec.iFontStyle.SetBitmapType(EAntiAliasedGlyphBitmap);
	
	TCharFormatMask formatMask;
	formatMask.SetAttrib(EAttFontTypeface);
	
	//Format the entire string using default formatting
	TInt textLength = richText->DocumentLength();
	richText->ApplyCharFormatL(defaultCharFormat, formatMask, 0, textLength); 
	
	//Change the formatting of the second half of the string to anti-aliased
	TInt halfLength = textLength/2;	
	richText->ApplyCharFormatL(antiAliasedCharFormat, formatMask, halfLength, halfLength);
	
	//Get the string portion with default formatting
	TPtrC defaultString;
	richText->GetChars(defaultString, defaultCharFormat,0);
	
	TGlyphBitmapType startBitmapType = defaultCharFormat.iFontSpec.iFontStyle.BitmapType(); 
	
	//Verify the formatting and the contents of the string
	TEST2(startBitmapType, EDefaultGlyphBitmap);
	TEST(defaultString == KDefaulFormattedText);
		
	//Get the string portion with antialiased formatting
	TPtrC antialiasedString;
	richText->GetChars(antialiasedString, antiAliasedCharFormat,halfLength);		

	TGlyphBitmapType endBitmapType = antiAliasedCharFormat.iFontSpec.iFontStyle.BitmapType(); 	
	
	//Verify the formatting and the contents of the string
	TEST2(endBitmapType,EAntiAliasedGlyphBitmap);
	TEST(antialiasedString == KAntiAliasedText);
	
	delete paraLayer; paraLayer = NULL;
	delete charLayer; charLayer = NULL;
	delete richText; richText = NULL;	
	
	__UHEAP_MARKEND;	
	}		

	
/***
Invoke the tests
*/
LOCAL_C void DoTestsL()
	{
	__UHEAP_MARK;
		
	OOM049456L();
	Inc051360L();
	OOM051360L();
    OOM056552L();
	INC055971L();
	INC097216L();
	INC101996L();
	
	__UHEAP_MARKEND;	
   	}
   
/***
Main
*/
GLDEF_C TInt E32Main()
	{
   	CTrapCleanup* trapCleanup=CTrapCleanup::New();
   
   	theTest.Start(KTestName);
	TRAPD(error, DoTestsL());
	TEST2(error, KErrNone);
 	
	delete trapCleanup;
 	
	theTest.End();
	theTest.Close();

   	return KErrNone;
   	}
   	
   	
   	



