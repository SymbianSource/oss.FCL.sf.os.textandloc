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





// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <sortutil.h>

#include "testdomsortutil.h"
#include "csortkeyarray.h"

enum TReturnType
    {
    EErrExtraParamaters = KErrGeneral,
    EErrBadParamaters = KErrGeneral,
    EErrFailed = KErrGeneral
    };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMSortUtil::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMSortUtil::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 

        // test functions of TSortKey class
        ENTRY( "TestSortKeyConstruct", CTestDOMSortUtil::TestSortKeyConstruct ),
        ENTRY( "TestSortKeyText", CTestDOMSortUtil::TestSortKeyText ),
        ENTRY( "TestSortKeyType", CTestDOMSortUtil::TestSortKeyType ),

        // test functions of CSortUtil class
        ENTRY( "TestSortUtilNewL", CTestDOMSortUtil::TestSortUtilNewL ),

        // test functions of MSortUtil class
        ENTRY( "TestSortUtilCompareItems", 
                CTestDOMSortUtil::TestSortUtilCompareItemsL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDOMSortUtil::TestSortKeyConstruct
// -----------------------------------------------------------------------------
//
TInt CTestDOMSortUtil::TestSortKeyConstruct( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMSortUtil, "testdomsortutil" );
    _LIT( KTestSortKeyConstruct, "In SortKey Construct" );
    TestModuleIf().Printf( 0, KTestDOMSortUtil, KTestSortKeyConstruct );
    // Print to log file
    iLog->Log( KTestSortKeyConstruct );

    _LIT( KText, "SoftKey" );
    TSortKey sortKey( KText, ESortKeyBasic );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMSortUtil::TestSortKeyText
// -----------------------------------------------------------------------------
//
TInt CTestDOMSortUtil::TestSortKeyText( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMSortUtil, "testdomsortutil" );
    _LIT( KTestSortKeyText, "In SortKey Text" );
    TestModuleIf().Printf( 0, KTestDOMSortUtil, KTestSortKeyText );
    // Print to log file
    iLog->Log( KTestSortKeyText );

    _LIT( KText, "text" );
    TSortKey sortKey( KText, ESortKeyBasic );

    TDesC text = sortKey.Text();
    STIF_ASSERT_NOT_EQUALS( 0, text.Length() );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMSortUtil::TestSortKeyType
// -----------------------------------------------------------------------------
//
TInt CTestDOMSortUtil::TestSortKeyType( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMSortUtil, "testdomsortutil" );
    _LIT( KTestSortKeyType, "In SortKey Type" );
    TestModuleIf().Printf( 0, KTestDOMSortUtil, KTestSortKeyType );
    // Print to log file
    iLog->Log( KTestSortKeyType );

    _LIT( KText, "text" );
    TSortKey sortKey( KText, ESortKeyBasic );

    TSortKeyType type = sortKey.Type();
    STIF_ASSERT_EQUALS( ESortKeyBasic, type );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMSortUtil::TestSortUtilNewL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSortUtil::TestSortUtilNewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMSortUtil, "testdomsortutil" );
    _LIT( KTestSortUtilNewL, "In SortUtil NewL" );
    TestModuleIf().Printf( 0, KTestDOMSortUtil, KTestSortUtilNewL );
    // Print to log file
    iLog->Log( KTestSortUtilNewL );

    CSortUtil* sortUtil = CSortUtil::NewL();
    CleanupStack::PushL( sortUtil );
    STIF_ASSERT_NOT_NULL( sortUtil );

    CleanupStack::PopAndDestroy( sortUtil );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMSortUtil::TestSortUtilCompareItemsL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSortUtil::TestSortUtilCompareItemsL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KSortUtilsTestClass, "testdomsortutil" );
    _LIT( KTestSortUtilCompareItems, "In MSortUtil CompareItems" );
    TestModuleIf().Printf( 0, KSortUtilsTestClass, KTestSortUtilCompareItems );
    // Print to log file
    iLog->Log( KTestSortUtilCompareItems );

    TInt numLhs = 0;
    TInt numRhs = 0;
    User::LeaveIfError(aItem.GetNextInt (numLhs));
    __ASSERT_ALWAYS(numLhs > 0, User::Leave(EErrBadParamaters));
    
    User::LeaveIfError(aItem.GetNextInt (numRhs));
    __ASSERT_ALWAYS(numRhs > 0, User::Leave(EErrBadParamaters));

    TPtrC lhs, rhs, extra;

    CSortUtil* sortUtil = CSortUtil::NewL();
    CleanupStack::PushL( sortUtil );
    CSortKeyArray* leftSortKeyArray = CSortKeyArray::NewL();
    CleanupStack::PushL( leftSortKeyArray );
    CSortKeyArray* rightSortKeyArray = CSortKeyArray::NewL();
    CleanupStack::PushL( rightSortKeyArray );

    leftSortKeyArray->Reset();
    rightSortKeyArray->Reset();

    aItem.SetParsingType( CStifItemParser::EQuoteStyleParsing );
    TInt i = 0;
    while( i != numLhs )
    {
        User::LeaveIfError( aItem.GetNextString( lhs ) );
        leftSortKeyArray->AppendL( TSortKey( KNullDesC, ESortKeyBasic ) );
        leftSortKeyArray->SetText( lhs, i );
        i++;
    }

    i = 0;
    while( i != numRhs )
    {
        User::LeaveIfError( aItem.GetNextString( rhs ) );
        rightSortKeyArray->AppendL( TSortKey( KNullDesC, ESortKeyBasic ) );
        rightSortKeyArray->SetText( rhs, i );
        i++;
    }

    TInt expectedResult;
    User::LeaveIfError( aItem.GetNextInt( expectedResult ) );

    __ASSERT_ALWAYS( aItem.GetNextString( extra ) != KErrNone, User::Leave( EErrExtraParamaters ) );
    
    TInt actualResult;
    actualResult = sortUtil->Interface()->CompareItems( *leftSortKeyArray, *rightSortKeyArray );

    leftSortKeyArray->Reset();
    rightSortKeyArray->Reset();

    CleanupStack::PopAndDestroy( rightSortKeyArray );
    CleanupStack::PopAndDestroy( leftSortKeyArray );
    CleanupStack::PopAndDestroy( sortUtil );

    if( ( expectedResult > 0 && actualResult > 0 ) ||
       ( expectedResult < 0 && actualResult < 0 ) ||
       ( expectedResult == 0 && actualResult == 0 ) )
        return KErrNone;
    else
        return EErrFailed;
    }


//  [End of File]
