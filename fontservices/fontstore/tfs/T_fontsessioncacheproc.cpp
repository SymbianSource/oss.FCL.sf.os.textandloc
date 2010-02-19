/*
* Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of the License "Eclipse Public License v1.0"
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

/**
 @file
 @test
 @internalComponent - Internal Symbian test code
*/

#include <e32base.h>
#include <e32cons.h>
#include <e32test.h>
#include <e32std.h>
#include <e32debug.h>
#include "FNTSTORE.H"
#include "FNTBODY.H"
#include "FNTSTD.H"
#include <fbs.h>
#include <bitstd.h>
#include <bitdev.h>
#include <e32math.h>

_LIT(KOpenFont, "DejaVu Sans Condensed");

#ifdef __WINSCW__
//this is used for winscw breakpoints
#define BR _asm( int 3);
#endif

const TInt KTimeOut = 1000 * 1000;
//make sure that the font is large enough to ensure that the session
//cache is used.
const TInt KTextHight = 220;

/* it is expected that the main in this file will be called to test multiple 
process output at the same time a process is being deleted (font and bitmap server
disconnection.  There are  normally two instances of this process.  Two virtually
identical processes are required to ensure that the session ID is the same.

The first is with aThirdProcess set. This sets output to run in a loop until
the timeout is completed.  These values  are input via program arguments.

If aThirdProcess is false then only one font creation, draw text,
font deletion cycle is completed. The test code will then repeatedly run
this process with aThirdProcess set to false.
*/


class TRunProc: public CBase
    {
public:
    static TRunProc* NewL();
    void RunTestL();
    ~TRunProc();
private:
    TRunProc(){};
    void ConstructL();
    void DrawText();
    void CreateFontL();

private:
    RFbsSession* iFbs;
    CFbsBitGc* iGc;
    CFbsScreenDevice* iDev;
    CFbsFont   *iFbsFont;
    };

TRunProc::~TRunProc()
    {
    delete iGc;
    delete iDev;
    iFbs->Disconnect();
    }

void TRunProc::ConstructL()
    {
    TInt err = RFbsSession::Connect();
    User::LeaveIfError(err);
    iFbs = RFbsSession::GetSession();
    User::LeaveIfNull(iFbs);
    
    const TInt KDisplayMode = 3;
    TDisplayMode mode[KDisplayMode];
    mode[0] = EColor16MA;
    mode[1] = EColor16MU;
    mode[2] = EColor64K;

    TInt count;
    for (count = 0; count < KDisplayMode; count++)
        {
        TRAP(err, iDev = CFbsScreenDevice::NewL(KNullDesC, mode[count]));
        if (err != KErrNotSupported)
            {
            break;
            }
        }

    User::LeaveIfNull(iDev);

    if(err == KErrNone)
        {
        iDev->ChangeScreenDevice(NULL);
        iDev->SetAutoUpdate(ETrue);
        iDev->CreateContext(iGc);
        }
    User::LeaveIfNull(iGc);
    }

TRunProc* TRunProc::NewL()
    {
    TRunProc *ptr = new (ELeave) TRunProc;
    CleanupStack::PushL(ptr);
    ptr->ConstructL();
    CleanupStack::Pop();
    return ptr;
    }

void TRunProc::CreateFontL()
    {
    TOpenFontSpec openFontSpec;
    openFontSpec.SetName(KOpenFont);
    openFontSpec.SetHeight(KTextHight);
    openFontSpec.SetItalic(EFalse);
    openFontSpec.SetBold(EFalse);

    TTypeface Typeface;
    Typeface.iName = KOpenFont;
    TFontSpec fs;
    fs.iTypeface = Typeface;

    fs.iHeight = KTextHight;
    CFbsFont* font = NULL;
    TInt err = iDev->GetNearestFontToDesignHeightInPixels(font, fs);

    User::LeaveIfNull(font);

    // Use the font
    iFbsFont = font;
    iGc->UseFont(font);
    iGc->Clear();
    }

void TRunProc::RunTestL()
    {
    TTime theTime;
    theTime.UniversalTime();
    TInt64 randSeed(theTime.Int64());
    TInt random(Math::Rand(randSeed) % (1000 * 1000));
    User::After(random);

    RTimer timer;
    timer.CreateLocal();
    TRequestStatus timerStatus = KRequestPending;
    TTimeIntervalMicroSeconds32 timeout(KTimeOut);
    timer.After(timerStatus, timeout);

    CreateFontL();
    RDebug::Print(_L("DrawText()random=%d"), random);
    DrawText();

    TText ch;
    const TUint8 *bitmap;
    TSize bitmapsize;
    TOpenFontCharMetrics Metrics;
    do
        {
        for (ch = 'A'; ch <= 'Z'; ch++)
            {
            iFbsFont->GetCharacterData((TInt) ch, Metrics, bitmap,bitmapsize);
            }
        }
    while (timerStatus == KRequestPending);

    timer.Cancel();
    iGc->DiscardFont();
    timer.Close();
    }
    

void TRunProc::DrawText()
    {
    TText ch[2];
    ch[1] = '\0';
    for (ch[0] = 'A';ch[0] <= 'Z';ch[0]++)
        {
        TBufC<2> buf(ch);
        iGc->DrawText(buf,TPoint(10,100));
        }
    for (ch[0] = 'a';ch[0] <= 'z';ch[0]++)
        {
        TBufC<2> buf(ch);
        iGc->DrawText(buf,TPoint(10,100));
        }
    }
    
  

void MainL()
    {
    TRunProc* test = TRunProc::NewL();
    CleanupStack::PushL(test);

    RDebug::Print(_L("T_fontsessioncacheproc MainL()"));
    test->RunTestL();

    CleanupStack::PopAndDestroy();
    }

// Cleanup stack harness
GLDEF_C TInt E32Main()
    {
    __UHEAP_MARK;
    CTrapCleanup* cleanupStack = CTrapCleanup::New();
    TRAPD(error, MainL());
    _LIT(KTCacheDeletionProcess,"T_fontsessioncacheproc");
    __ASSERT_ALWAYS(!error, User::Panic(KTCacheDeletionProcess, error));
    delete cleanupStack;
    __UHEAP_MARKEND;
    return 0;
    }
