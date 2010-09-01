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
* Description:  japanese_language_utilities_api
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <jplangutil.h>

#include "testdomjapaneselanguageutilities.h"

//CONSTANTS
const TInt KDesLength = 24;
_LIT( KText, "Text" );
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMJapaneseLanguageUtilities::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMJapaneseLanguageUtilities::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestJLUConvertHalfToFullWidth", 
                CTestDOMJapaneseLanguageUtilities::TestJLUConvertHalfToFullWidth ),
        ENTRY( "TestJLUConvertFullToHalfWidth", 
                CTestDOMJapaneseLanguageUtilities::TestJLUConvertFullToHalfWidth ),
        ENTRY( "TestJLUConvertHalfToFullWidthKatakana", 
                CTestDOMJapaneseLanguageUtilities::TestJLUConvertHalfToFullWidthKatakana ),
        ENTRY( "TestJLUConvertFullToHalfWidthKatakana", 
                CTestDOMJapaneseLanguageUtilities::TestJLUConvertFullToHalfWidthKatakana ),
        ENTRY( "TestJLUConvertFullHiragnaToFullKatakana", 
                CTestDOMJapaneseLanguageUtilities::TestJLUConvertFullHiragnaToFullKatakana ),   
        ENTRY( "TestJLUIsKatakana", CTestDOMJapaneseLanguageUtilities::TestJLUIsKatakana ), 
        ENTRY( "TestJLUIsHiragana", CTestDOMJapaneseLanguageUtilities::TestJLUIsHiragana ), 
        ENTRY( "TestJLUIsKanji", CTestDOMJapaneseLanguageUtilities::TestJLUIsKanji ), 
        ENTRY( "TestJLUIsHalfWidth", CTestDOMJapaneseLanguageUtilities::TestJLUIsHalfWidth ), 
        ENTRY( "TestJLUIsFullWidth", CTestDOMJapaneseLanguageUtilities::TestJLUIsFullWidth ),

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDOMJapaneseLanguageUtilities::TestJLUConvertHalfToFullWidth
// -----------------------------------------------------------------------------
//
TInt CTestDOMJapaneseLanguageUtilities::TestJLUConvertHalfToFullWidth( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomjapaneselanguageutilities, "testdomjapaneselanguageutilities" );
    _LIT( KTestJLUConvertHalfToFullWidth, "In TestJLUConvertHalfToFullWidth" );
    TestModuleIf().Printf( 0, Ktestdomjapaneselanguageutilities, KTestJLUConvertHalfToFullWidth );
    // Print to log file
    iLog->Log( KTestJLUConvertHalfToFullWidth );
    TBuf<KDesLength> unisrc( KText );
    TBuf<KDesLength> unides; 
    TInt status = JPLangUtil::ConvertHalfToFullWidth( unisrc, unides );

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestDOMJapaneseLanguageUtilities::TestJLUConvertFullToHalfWidth
// -----------------------------------------------------------------------------
//
TInt CTestDOMJapaneseLanguageUtilities::TestJLUConvertFullToHalfWidth( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomjapaneselanguageutilities, "testdomjapaneselanguageutilities" );
    _LIT( KTestJLUConvertFullToHalfWidth, "In TestJLUConvertFullToHalfWidth" );
    TestModuleIf().Printf( 0, Ktestdomjapaneselanguageutilities, KTestJLUConvertFullToHalfWidth );
    // Print to log file
    iLog->Log( KTestJLUConvertFullToHalfWidth );
    TBuf<KDesLength> unisrc( KText );
    TBuf<KDesLength> unides; 
    TInt status = JPLangUtil::ConvertFullToHalfWidth( unisrc, unides );

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestDOMJapaneseLanguageUtilities::TestJLUConvertHalfToFullWidthKatakana
// -----------------------------------------------------------------------------
//
TInt CTestDOMJapaneseLanguageUtilities::TestJLUConvertHalfToFullWidthKatakana( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomjapaneselanguageutilities, "testdomjapaneselanguageutilities" );
    _LIT( KTestJLUConvertHalfToFullWidthKatakana, "In TestJLUConvertHalfToFullWidthKatakana" );
    TestModuleIf().Printf( 0, Ktestdomjapaneselanguageutilities, KTestJLUConvertHalfToFullWidthKatakana );
    // Print to log file
    iLog->Log( KTestJLUConvertHalfToFullWidthKatakana );
    TBuf<KDesLength> unisrc( KText );
    TBuf<KDesLength> unides; 
    TInt status = JPLangUtil::ConvertHalfToFullWidthKatakana( unisrc, unides );

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestDOMJapaneseLanguageUtilities::TestJLUConvertFullToHalfWidthKatakana
// -----------------------------------------------------------------------------
//
TInt CTestDOMJapaneseLanguageUtilities::TestJLUConvertFullToHalfWidthKatakana( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomjapaneselanguageutilities, "testdomjapaneselanguageutilities" );
    _LIT( KTestJLUConvertFullToHalfWidthKatakana, "In TestJLUConvertFullToHalfWidthKatakana" );
    TestModuleIf().Printf( 0, Ktestdomjapaneselanguageutilities, KTestJLUConvertFullToHalfWidthKatakana );
    // Print to log file
    iLog->Log( KTestJLUConvertFullToHalfWidthKatakana );
    TBuf<KDesLength> unisrc( KText );
    TBuf<KDesLength> unides; 
    TInt status = JPLangUtil::ConvertFullToHalfWidthKatakana( unisrc, unides );

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestDOMJapaneseLanguageUtilities::TestJLUConvertFullHiragnaToFullKatakana
// -----------------------------------------------------------------------------
//
TInt CTestDOMJapaneseLanguageUtilities::TestJLUConvertFullHiragnaToFullKatakana( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomjapaneselanguageutilities, "testdomjapaneselanguageutilities" );
    _LIT( KTestJLUConvertFullHiragnaToFullKatakana, "In TestJLUConvertFullHiragnaToFullKatakana" );
    TestModuleIf().Printf( 0, Ktestdomjapaneselanguageutilities, KTestJLUConvertFullHiragnaToFullKatakana );
    // Print to log file
    iLog->Log( KTestJLUConvertFullHiragnaToFullKatakana );
    TBuf<KDesLength> unisrc( KText );
    TBuf<KDesLength> unides; 
    TInt status = JPLangUtil::ConvertFullHiragnaToFullKatakana( unisrc, unides );

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestDOMJapaneseLanguageUtilities::TestJLUIsKatakana
// -----------------------------------------------------------------------------
//
TInt CTestDOMJapaneseLanguageUtilities::TestJLUIsKatakana( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomjapaneselanguageutilities, "testdomjapaneselanguageutilities" );
    _LIT( KTestJLUIsKatakana, "In TestJLUIsKatakana" );
    TestModuleIf().Printf( 0, Ktestdomjapaneselanguageutilities, KTestJLUIsKatakana );
    // Print to log file
    iLog->Log( KTestJLUIsKatakana );
    TBuf<KDesLength> unisrc( KText );
    TBool status = JPLangUtil::IsKatakana( *unisrc.Ptr() );

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestDOMJapaneseLanguageUtilities::TestJLUIsHiragana
// -----------------------------------------------------------------------------
//
TInt CTestDOMJapaneseLanguageUtilities::TestJLUIsHiragana( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomjapaneselanguageutilities, "testdomjapaneselanguageutilities" );
    _LIT( KTestJLUIsHiragana, "In TestJLUIsHiragana" );
    TestModuleIf().Printf( 0, Ktestdomjapaneselanguageutilities, KTestJLUIsHiragana );
    // Print to log file
    iLog->Log( KTestJLUIsHiragana );
    TBuf<KDesLength> unisrc( KText );
    TBool status = JPLangUtil::IsHiragana( *unisrc.Ptr() );

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestDOMJapaneseLanguageUtilities::TestJLUIsKanji
// -----------------------------------------------------------------------------
//
TInt CTestDOMJapaneseLanguageUtilities::TestJLUIsKanji( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomjapaneselanguageutilities, "testdomjapaneselanguageutilities" );
    _LIT( KTestJLUIsKanji, "In TestJLUIsKanji" );
    TestModuleIf().Printf( 0, Ktestdomjapaneselanguageutilities, KTestJLUIsKanji );
    // Print to log file
    iLog->Log( KTestJLUIsKanji );
    TBuf<KDesLength> unisrc( KText );
    TBool status = JPLangUtil::IsKanji( *unisrc.Ptr() );

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestDOMJapaneseLanguageUtilities::TestJLUIsHalfWidth
// -----------------------------------------------------------------------------
//
TInt CTestDOMJapaneseLanguageUtilities::TestJLUIsHalfWidth( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomjapaneselanguageutilities, "testdomjapaneselanguageutilities" );
    _LIT( KTestJLUIsHalfWidth, "In TestJLUIsHalfWidth" );
    TestModuleIf().Printf( 0, Ktestdomjapaneselanguageutilities, KTestJLUIsHalfWidth );
    // Print to log file
    iLog->Log( KTestJLUIsHalfWidth );
    TBuf<KDesLength> unisrc( KText );
    TBool status = JPLangUtil::IsHalfWidth( *unisrc.Ptr() );

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestDOMJapaneseLanguageUtilities::TestJLUIsFullWidth
// -----------------------------------------------------------------------------
//
TInt CTestDOMJapaneseLanguageUtilities::TestJLUIsFullWidth( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomjapaneselanguageutilities, "testdomjapaneselanguageutilities" );
    _LIT( KTestJLUIsFullWidth, "In TestJLUIsFullWidth" );
    TestModuleIf().Printf( 0, Ktestdomjapaneselanguageutilities, KTestJLUIsFullWidth );
    // Print to log file
    iLog->Log( KTestJLUIsFullWidth );
    TBuf<KDesLength> unisrc( KText );
    TBool status = JPLangUtil::IsFullWidth( *unisrc.Ptr() );

    return KErrNone;

    }
//  [End of File]
