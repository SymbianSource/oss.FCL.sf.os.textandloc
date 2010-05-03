/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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

/**
 @file
 @test
 @internalComponent Internal Symbian test code
*/

#include "FNTSTORE.H"
#include "OPENFONT.H"
#include "FNTBODY.H"
#include "FNTSTD.H"
#include "t_fontsessioncache.h"
#include <hal.h>
#include <s32file.h>
#include <graphics/shapeimpl.h>

_LIT(KWorkerProcess,"tfontsessioncacheproc");

const TInt KNumOfProc = 4;
const TInt KRunningTime = 1000 * 1000 * 5;

class CTFontSessionCache : public CTGraphicsBase
    {
public:
    CTFontSessionCache(CTestStep* aStep);
    ~CTFontSessionCache();
    
    static void TimerCleanup(TAny *);
protected:
// From CTGraphicsStep
    virtual void RunTestCaseL(TInt aCurTestCase);
private:
    void TestOpenFontForQtL();
    void RunMultiWorkerProcessL();
    };

// This class is a data mirror to CBitmapFont in order to check its private 
// member iOpenFont. It is only used by TestOpenFontForQtL().
class CBitmapFontDummy:public CFont
    {
public:
    TFontSpec iFontSpecInTwips;
    TAlgStyle iAlgStyle;        
    RHeap* iHeap;
    TInt iFontBitmapOffset;
    COpenFont* iOpenFont; 
    TUint32 iReserved;
    TUint32 iUniqueFontId;     
    };

class CFbsFontUtil:public CFbsFont
    {
public:
    static CBitmapFontDummy *getBitmapFont(CFbsFont *aFbsfont)
        {
        return reinterpret_cast<CBitmapFontDummy*>(static_cast<CFbsFontUtil*>(aFbsfont)->Address());
        }
    };


CTFontSessionCache::CTFontSessionCache(CTestStep* aStep)
 :  CTGraphicsBase(aStep)
    {

    }

CTFontSessionCache::~CTFontSessionCache()
    {
    // no action needed
    }

void CTFontSessionCache::TimerCleanup(TAny *aTimer)
    {
    ((RTimer*)aTimer)->Cancel();
    }

/**
Qt needs the last bit of iOpenFont to be set 1 as a workaround to maintain
its compatibility across difference Symbian OS versions.
*/
void CTFontSessionCache::TestOpenFontForQtL()
    {
    _LIT(KTypefaceName, "DejaVu Sans Condensed");
    TFontSpec spec(KTypefaceName, 15);   
    CFbsTypefaceStore *tfs = CFbsTypefaceStore::NewL(NULL);
    
    CFont* font = NULL;
    TInt ret = tfs->GetNearestFontToDesignHeightInPixels(font,spec);
    TEST(ret == KErrNone);
    
    CFbsFont *fbs_font = static_cast<CFbsFont*>(font);
    TEST(reinterpret_cast<TInt>((CFbsFontUtil::getBitmapFont(fbs_font))->iOpenFont) & 1);
    
    tfs->ReleaseFont(font);
    delete tfs;
    }

/*
 * Launch 4 worker processes running with random latency at beginning. 
 * Each one lasts about 1 sec. Within duration of 5 sec, if one terminates, 
 * re-launch it.
 * 
 */
void CTFontSessionCache::RunMultiWorkerProcessL()
    {
    RProcess ProcArray[KNumOfProc];
    TRequestStatus *completeStatus[KNumOfProc];

    for (TInt i = 0; i < KNumOfProc; i++)
        {                    
        RDebug::Print(_L(">>> Launching %d..."),i);
        TInt err;
        err = ProcArray[i].Create(KWorkerProcess, KNullDesC);
        User::LeaveIfError(err);

        completeStatus[i] = new(ELeave) TRequestStatus; 
        CleanupStack::PushL(completeStatus[i]);
        *completeStatus[i] = KRequestPending;
        
        ProcArray[i].Logon(*completeStatus[i]);
        ProcArray[i].Resume(); //start the process
        }
      
    RTimer timer;
    timer.CreateLocal();
    TRequestStatus timerStatus = KRequestPending;
    TTimeIntervalMicroSeconds32 timeout(KRunningTime);
    timer.After(timerStatus, timeout);
    
    do
        {     
        User::WaitForNRequest(completeStatus, KNumOfProc);
        TInt i = 0;
        for(;i < KNumOfProc;i++ )
            {
                if (*completeStatus[i] != KRequestPending)
                {
                break;
                }
            }

        TExitType exit = ProcArray[i].ExitType();
        TEST(exit == EExitKill);
        TInt reason = ProcArray[i].ExitReason();
        TEST (reason == 0);

        RDebug::Print(_L("<<< Close %d..."), i);
        ProcArray[i].Close();

        RDebug::Print(_L(">>> Launching %d..."), i);
        TInt err;
        err = ProcArray[i].Create(KWorkerProcess, KNullDesC);
        User::LeaveIfError(err);

        //run process 1
        *completeStatus[i] = KRequestPending;
        ProcArray[i].Logon(*completeStatus[i]);
        ProcArray[i].Resume(); //start the process
        }
    while (timerStatus == KRequestPending);
    
    for (TInt i = 0; i < KNumOfProc; i++)
        {
        if(*completeStatus[i] == KRequestPending)
            {
            User::WaitForRequest(*completeStatus[i]);
            }       
        RDebug::Print(_L("<<< Tear down Close %d..."),i);
        ProcArray[i].Close(); //tear down
        }        
    CleanupStack::PopAndDestroy(4);
    }

void CTFontSessionCache::RunTestCaseL( TInt aCurTestCase )
    {
#if defined __WINS__ || defined __WINSCW__
    aCurTestCase = aCurTestCase;  //to avoid unused warning
 //   TestComplete(); //only run test on hardware, always passes on winscw
 //   return;
#endif
    ((CTFontSessionCacheStep*) iStep)->SetTestStepID(KUnknownSYMTestCaseIDName);

    switch (aCurTestCase)
        {
        case 1:
            ((CTFontSessionCacheStep*) iStep)->SetTestStepID(_L("TI18N-FNTSTORE-UT--4003"));
            INFO_PRINTF1(_L("Test CBitmapFont::iOpenFont last bit for Qt\n"));
            TestOpenFontForQtL();
            break;

        case 2:
            ((CTFontSessionCacheStep*) iStep)->SetTestStepID(_L("TI18N-FNTSTORE-CIT-4002"));
            INFO_PRINTF1(_L("Test GetCharacterData() in muti-process client\n"));
            RunMultiWorkerProcessL();
            break;
            
        case 3:
            ((CTFontSessionCacheStep*) iStep)->SetTestStepID(KNotATestSYMTestCaseIDName);
            ((CTFontSessionCacheStep*) iStep)->CloseTMSGraphicsStep();
            TestComplete();
            break;
        }
    ((CTFontSessionCacheStep*)iStep)->RecordTestResultL();
    }

// --------------
__CONSTRUCT_STEP__(FontSessionCache)
