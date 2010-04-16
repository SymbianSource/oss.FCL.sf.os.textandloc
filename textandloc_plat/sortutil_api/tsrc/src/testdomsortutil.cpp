/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies). 
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
* Description:    test sortutil.h
*
*/





// INCLUDE FILES
#include <stiftestinterface.h>
#include <settingserverclient.h>
#include <screensaverinternalpskeys.h>
#include <e32property.h>

#include "testdomsortutil.h"

// CONSTANTS
_LIT( KModuleName, "testdomsortutil.dll" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMSortUtil::CTestDOMSortUtil
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestDOMSortUtil::CTestDOMSortUtil( CTestModuleIf& aTestModuleIf ):
    CScriptBase( aTestModuleIf )
    {
    }

// -----------------------------------------------------------------------------
// CTestDOMSortUtil::~CTestDOMSortUtil
// Destructor.
// -----------------------------------------------------------------------------
//
CTestDOMSortUtil::~CTestDOMSortUtil()
    {
    // Delete logger
    delete iLog; 

    }

// -----------------------------------------------------------------------------
// CTestDOMSortUtil::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTestDOMSortUtil::ConstructL()
    {
    //Read logger settings to check whether test case name is to be
    //appended to log file name.
    RSettingServer settingServer;
    CleanupClosePushL( settingServer );
    TInt ret = settingServer.Connect();
    if ( ret != KErrNone )
        {
        User::Leave(ret);
        }
    // Struct to StifLogger settigs.
    TLoggerSettings loggerSettings; 
    // Parse StifLogger defaults from STIF initialization file.
    ret = settingServer.GetLoggerSettings( loggerSettings );
    if ( ret != KErrNone )
        {
        User::Leave( ret );
        } 
    // Close Setting server session
    settingServer.Close();
    CleanupStack::PopAndDestroy( &settingServer );

    TFileName logFileName;
    
    if ( loggerSettings.iAddTestCaseTitle )
        {
        TName title;
        TestModuleIf().GetTestCaseTitleL( title );
        logFileName.Format( KtestdomsortutilLogFileWithTitle, &title );
        }
    else
        {
        logFileName.Copy( KtestdomsortutilLogFile );
        }

    iLog = CStifLogger::NewL( KtestdomsortutilLogPath, 
                          logFileName,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
    
    SendTestClassVersion();
    
    TurnOffScreenSaver();
    }

// -----------------------------------------------------------------------------
// CTestDOMSortUtil::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestDOMSortUtil* CTestDOMSortUtil::NewL( CTestModuleIf& aTestModuleIf )
    {
    CTestDOMSortUtil* self = new( ELeave ) CTestDOMSortUtil( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );

    return self;

    }

//-----------------------------------------------------------------------------
// CTestDOMSortUtil::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CTestDOMSortUtil::SendTestClassVersion()
    {
    TVersion moduleVersion;
    moduleVersion.iMajor = TEST_CLASS_VERSION_MAJOR;
    moduleVersion.iMinor = TEST_CLASS_VERSION_MINOR;
    moduleVersion.iBuild = TEST_CLASS_VERSION_BUILD;

    TFileName moduleName;
    moduleName = KModuleName;

    TBool newVersionOfMethod = ETrue;
    TestModuleIf().SendTestModuleVersion( moduleVersion, moduleName, 
        newVersionOfMethod );
    }

// ========================== OTHER EXPORTED FUNCTIONS =========================

// -----------------------------------------------------------------------------
// LibEntryL is a polymorphic Dll entry point.
// Returns: CScriptBase: New CScriptBase derived object
// -----------------------------------------------------------------------------
//
EXPORT_C CScriptBase* LibEntryL( 
    CTestModuleIf& aTestModuleIf ) // Backpointer to STIF Test Framework
    {
    return ( CScriptBase* ) CTestDOMSortUtil::NewL( aTestModuleIf );
    }

// -----------------------------------------------------------------------------
// Turn off ScreenSaver
// -----------------------------------------------------------------------------
//
void CTestDOMSortUtil::TurnOffScreenSaver()
    {
    TInt err1 = RProperty::Get( KPSUidScreenSaver, KScreenSaverAllowScreenSaver, 
        iOldScreenSaverProperty );
    TInt err2 = RProperty::Set( KPSUidScreenSaver, KScreenSaverAllowScreenSaver, 
        KScreenSaverAllowScreenSaver );    
    RDebug::Printf( "screensaver property=%d err1=%d err2=%d\n", 
        iOldScreenSaverProperty, err1, err2 );
    }

// -----------------------------------------------------------------------------
// Restore ScreenSaver
// -----------------------------------------------------------------------------
//
void CTestDOMSortUtil::RestoreScreenSaver()
    {
    RProperty::Set( KPSUidScreenSaver, KScreenSaverAllowScreenSaver, 
        iOldScreenSaverProperty );
    User::ResetInactivityTime();
    }


//  End of File
