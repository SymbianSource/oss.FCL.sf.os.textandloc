/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test for CDirectoryLocalizer.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <barsread.h>
#include <pathinfo.h>
#include <cdirectorylocalizer.h>
#include <testsdkdirloc.rsg>

#include "testsdkdirloc.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestsdkdirloc::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKDirLoc::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctestsdkdirloc::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKDirLoc::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestDLNewL", CTestSDKDirLoc::TestDLNewL ),
        ENTRY( "TestDLNewLReaderL", CTestSDKDirLoc::TestDLNewLResReaderL ),
        ENTRY( "TestDLNewLResIDL", CTestSDKDirLoc::TestDLNewLResIDL ),
        ENTRY( "TestDLAddFromResourceL", CTestSDKDirLoc::TestDLAddFromResourceL ),
        ENTRY( "TestDLAddFromResourceLResIDL", CTestSDKDirLoc::TestDLAddFromResourceLResIDL ),
        ENTRY( "TestDLSetFullPath", CTestSDKDirLoc::TestDLSetFullPath ),
        ENTRY( "TestDLIsLocalized", CTestSDKDirLoc::TestDLIsLocalized ),
        ENTRY( "TestDLLocalizedName", CTestSDKDirLoc::TestDLLocalizedName ),
        ENTRY( "TestDLExtraData", CTestSDKDirLoc::TestDLExtraData ),
        ENTRY( "TestDLIcon", CTestSDKDirLoc::TestDLIcon ),
        ENTRY( "TestDLDelete", CTestSDKDirLoc::TestDLDelete ),
        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestSDKDirLoc::TestDLNewL
// -----------------------------------------------------------------------------
//

TInt CTestSDKDirLoc::TestDLNewL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDLModule, "TestDLModule" );
    _LIT( KTestDLNewL, "In TestDLNewL" );
    TestModuleIf().Printf( 0, KTestDLModule, KTestDLNewL );
    // Print to log file
    iLog->Log( KTestDLNewL );

    TInt err = KErrNone;
    TRAP( err, iDirLocalizer = CDirectoryLocalizer::NewL() );
    
    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKDirLoc::TestDLNewLReaderL
// -----------------------------------------------------------------------------
//

TInt CTestSDKDirLoc::TestDLNewLResReaderL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDLModule, "TestDLModule" );
    _LIT( KTestDLNewLReaderL, "In TestDLNewLReaderL" );
    TestModuleIf().Printf( 0, KTestDLModule, KTestDLNewLReaderL );
    // Print to log file
    iLog->Log( KTestDLNewLReaderL );

    TInt err = KErrNone;
    TResourceReader resReader;
    CCoeEnv::Static()->CreateResourceReaderLC( resReader, R_EXAMPLE_LOCALIZER_ENTRIES );
    TRAP( err, iDirLocalizer = CDirectoryLocalizer::NewL( resReader ) );
    CleanupStack::PopAndDestroy();

    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKDirLoc::TestDLNewLResIDL
// -----------------------------------------------------------------------------
//

TInt CTestSDKDirLoc::TestDLNewLResIDL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDLModule, "TestDLModule" );
    _LIT( KTestDLNewLReaderL, "In TestDLNewLReaderL" );
    TestModuleIf().Printf( 0, KTestDLModule, KTestDLNewLReaderL );
    // Print to log file
    iLog->Log( KTestDLNewLReaderL );

    TInt err = KErrNone;
    TRAP( err, iDirLocalizer = CDirectoryLocalizer::NewL( R_EXAMPLE_LOCALIZER_ENTRIES ) );

    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKDirLoc::TestDLAddFromResourceL
// -----------------------------------------------------------------------------
//

TInt CTestSDKDirLoc::TestDLAddFromResourceL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDLModule, "TestDLModule" );
    _LIT( KTestDLAddFromResourceL, "In TestDLAddFromResourceL" );
    TestModuleIf().Printf( 0, KTestDLModule, KTestDLAddFromResourceL );
    // Print to log file
    iLog->Log( KTestDLAddFromResourceL );

    TInt err = KErrNone;
    TResourceReader resReader;
    CCoeEnv::Static()->CreateResourceReaderLC( resReader, R_EXAMPLE_LOCALIZER_ENTRIES );
    TRAP( err, iDirLocalizer->AddFromResourceL( resReader ) );
    CleanupStack::PopAndDestroy();

    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKDirLoc::TestDLAddFromResourceLResIDL
// -----------------------------------------------------------------------------
//

TInt CTestSDKDirLoc::TestDLAddFromResourceLResIDL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDLModule, "TestDLModule" );
    _LIT( KTestDLAddFromResourceLResIDL, "In TestDLAddFromResourceLResIDL" );
    TestModuleIf().Printf( 0, KTestDLModule, KTestDLAddFromResourceLResIDL );
    // Print to log file
    iLog->Log( KTestDLAddFromResourceLResIDL );

    TInt err = KErrNone;
    TRAP( err, iDirLocalizer->AddFromResourceL( R_EXAMPLE_LOCALIZER_ENTRIES ) );

    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKDirLoc::TestDLSetFullPath
// -----------------------------------------------------------------------------
//

TInt CTestSDKDirLoc::TestDLSetFullPath( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDLModule, "TestDLModule" );
    _LIT( KTestDLSetFullPath, "In TestDLSetFullPath" );
    TestModuleIf().Printf( 0, KTestDLModule, KTestDLSetFullPath );
    // Print to log file
    iLog->Log( KTestDLSetFullPath );

    TInt err = KErrNone;
    TFileName path = PathInfo::GetPath( PathInfo::EPhoneMemoryRootPath );
    TRAP( err, iDirLocalizer->SetFullPath( path ) );

    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKDirLoc::TestDLIsLocalized
// -----------------------------------------------------------------------------
//

TInt CTestSDKDirLoc::TestDLIsLocalized( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDLModule, "TestDLModule" );
    _LIT( KTestDLIsLocalized, "In TestDLIsLocalized" );
    TestModuleIf().Printf( 0, KTestDLModule, KTestDLIsLocalized );
    // Print to log file
    iLog->Log( KTestDLIsLocalized );

    TInt err = KErrNone;
    TRAP( err, iDirLocalizer->IsLocalized() );

    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKDirLoc::TestDLLocalizedName
// -----------------------------------------------------------------------------
//

TInt CTestSDKDirLoc::TestDLLocalizedName( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDLModule, "TestDLModule" );
    _LIT( KTestDLLocalizedName, "In TestDLLocalizedName" );
    TestModuleIf().Printf( 0, KTestDLModule, KTestDLLocalizedName );
    // Print to log file
    iLog->Log( KTestDLLocalizedName );

    TInt err = KErrNone;
    TRAP( err, iDirLocalizer->LocalizedName() );

    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKDirLoc::TestDLExtraData
// -----------------------------------------------------------------------------
//

TInt CTestSDKDirLoc::TestDLExtraData( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDLModule, "TestDLModule" );
    _LIT( KTestDLExtraData, "In TestDLExtraData" );
    TestModuleIf().Printf( 0, KTestDLModule, KTestDLExtraData );
    // Print to log file
    iLog->Log( KTestDLExtraData );

    TInt err = KErrNone;
    TRAP( err, iDirLocalizer->ExtraData() );

    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKDirLoc::TestDLIcon
// -----------------------------------------------------------------------------
//

TInt CTestSDKDirLoc::TestDLIcon( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDLModule, "TestDLModule" );
    _LIT( KTestDLIcon, "In TestDLIcon" );
    TestModuleIf().Printf( 0, KTestDLModule, KTestDLIcon );
    // Print to log file
    iLog->Log( KTestDLIcon );

    TInt err = KErrNone;
    TRAP( err, iDirLocalizer->Icon() );

    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKDirLoc::TestDLDelete
// -----------------------------------------------------------------------------
//
TInt CTestSDKDirLoc::TestDLDelete( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( KTestDLModule, "TestDLModule" );
    _LIT( KTestDLDelete, "In TestDLDelete" );
    TestModuleIf().Printf( 0, KTestDLModule, KTestDLDelete );
    // Print to log file
    iLog->Log( KTestDLDelete );

    if ( iDirLocalizer )
        {
        delete iDirLocalizer;
        iDirLocalizer = NULL;
        }

    return KErrNone;
    }

//  [End of File]
