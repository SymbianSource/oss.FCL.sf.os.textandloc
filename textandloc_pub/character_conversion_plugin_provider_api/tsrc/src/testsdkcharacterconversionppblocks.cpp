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
* Description:    test CONVUTILS.H
*
*/





// [INCLUDE FILES]
#include <e32svr.h>
#include <StifParser.h>
#include <StifTestInterface.h>
#include <convutils.h>

#include "testsdkcharacterconversionpp.h"

const TInt KLength = 20;
// -----------------------------------------------------------------------------
// Fuction ConvertFromIntermediateBufferInPlace() for 
// initialize sturct SCharacterSet
// -----------------------------------------------------------------------------
//
void ConvertFromIntermediateBufferInPlace( TInt /*aStartPositionInDescriptor*/, 
                                           TDes8& /*aDescriptor*/, 
                                           TInt& /*aNumberOfCharactersThatDroppedOut*/ )
    {
    
    }

// -----------------------------------------------------------------------------
// Fuction ConvertToIntermediateBufferInPlace() for 
// initialize sturct SMethod
// -----------------------------------------------------------------------------
//
void ConvertToIntermediateBufferInPlace( TDes8& /*aDescriptor*/ )
    {
    
    }

// -----------------------------------------------------------------------------
// Fuction NumberOfBytesAbleToConvert() for 
// initialize sturct SMethod
// -----------------------------------------------------------------------------
//
TInt NumberOfBytesAbleToConvert(const TDesC8& aDescriptor)
    {
    if( aDescriptor.Length() == 0 )
        {
        return 0;
        }
    else
        {
        return 1;
        }
    }

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKCharacterConversionPP::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKCharacterConversionPP::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  

        ENTRY( "TestCCPPConvertFromUnicodeL", 
                CTestSDKCharacterConversionPP::TestCCPPConvertFromUnicodeL ),
        ENTRY( "TestCCPPConvertFromUnicodeFlagL", 
                CTestSDKCharacterConversionPP::TestCCPPConvertFromUnicodeFlagL ),
        ENTRY( "TestCCPPConvertFromIntermediateBufferInPlace", 
                CTestSDKCharacterConversionPP::TestCCPPConvertFromIntermediateBufferInPlace ),
        ENTRY( "TestCCPPConvertToUnicodeFromModalForeignL", 
                CTestSDKCharacterConversionPP::TestCCPPConvertToUnicodeFromModalForeignL ),
        ENTRY( "TestCCPPConvertToUnicodeFromModalForeignFlagL", 
                CTestSDKCharacterConversionPP::TestCCPPConvertToUnicodeFromModalForeignFlagL ),
        ENTRY( "TestCCPPConvertToUnicodeFromHeterogeneousForeignL", 
                CTestSDKCharacterConversionPP::TestCCPPConvertToUnicodeFromHeterogeneousForeignL ),
        ENTRY( "TestCCPPConvertToUnicodeFromHeterogeneousForeignFlagL", 
                CTestSDKCharacterConversionPP::TestCCPPConvertToUnicodeFromHeterogeneousForeignFlagL ),

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// ============================ MEMBER FUNCTIONS ===============================
// =========================== CLASS CnvUtilities===============================
// -----------------------------------------------------------------------------
// CTestSDKCharacterConversionPP::TestCCPPConvertFromUnicodeL 
// -----------------------------------------------------------------------------
TInt CTestSDKCharacterConversionPP::TestCCPPConvertFromUnicodeL( CStifItemParser& /*aItem*/ )
    {
    CnvUtilities::SCharacterSet characterSet;
    characterSet.iConversionData = &( CCnvCharacterSetConverter::AsciiConversionData() );
    characterSet.iConvertFromIntermediateBufferInPlace = ConvertFromIntermediateBufferInPlace;
    CArrayFix<CnvUtilities::SCharacterSet>* array = new(ELeave) CArrayFixFlat<CnvUtilities::SCharacterSet>( 1 );
    CleanupStack::PushL( array );
    array->AppendL( characterSet );
    
    _LIT8( KForeign, "converter" );
    _LIT( KUnicode, "converter" );
    TBuf8<KLength> foreign;
    TBuf<KLength> unicode( KUnicode );

    TBuf8<KLength> replace( KForeign );
    CCnvCharacterSetConverter::TArrayOfAscendingIndices indice;
    
    TInt num = CnvUtilities::ConvertFromUnicode( CCnvCharacterSetConverter::ELittleEndian, replace, foreign, unicode, indice, array->Array() );
    STIF_ASSERT_TRUE( 0 == num );
    STIF_ASSERT_TRUE( 0 == foreign.Compare( KForeign ) );
    
    CleanupStack::PopAndDestroy( array );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKCharacterConversionPP::TestCCPPConvertFromUnicodeFlagL 
// -----------------------------------------------------------------------------
TInt CTestSDKCharacterConversionPP::TestCCPPConvertFromUnicodeFlagL( CStifItemParser& /*aItem*/ )
    {
    CnvUtilities::SCharacterSet characterSet;
    characterSet.iConversionData = &( CCnvCharacterSetConverter::AsciiConversionData() );
    characterSet.iConvertFromIntermediateBufferInPlace = ConvertFromIntermediateBufferInPlace;
    CArrayFix<CnvUtilities::SCharacterSet>* array = new(ELeave) CArrayFixFlat<CnvUtilities::SCharacterSet>( 1 );
    CleanupStack::PushL( array );
    array->AppendL( characterSet );
    
    _LIT8( KForeign, "converter" );
    _LIT( KUnicode, "converter" );
    TBuf8<KLength> foreign;
    TBuf<KLength> unicode( KUnicode );

    TBuf8<KLength> replace( KForeign );
    CCnvCharacterSetConverter::TArrayOfAscendingIndices indice;
    TUint inputFlag = CCnvCharacterSetConverter::EInputConversionFlagAppend;
    TUint outputFlag;
    
    TInt num = CnvUtilities::ConvertFromUnicode( CCnvCharacterSetConverter::ELittleEndian, replace, foreign, 
                                                 unicode, indice, array->Array(), outputFlag, inputFlag );
    STIF_ASSERT_TRUE( 0 == num );
    STIF_ASSERT_TRUE( 0 == foreign.Compare( KForeign ) );
    
    CleanupStack::PopAndDestroy( array );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKCharacterConversionPP::TestCCPPConvertFromIntermediateBufferInPlace 
// -----------------------------------------------------------------------------
TInt CTestSDKCharacterConversionPP::TestCCPPConvertFromIntermediateBufferInPlace( CStifItemParser& /*aItem*/ )
    {
    
    _LIT8( KForeign, "converter" );
    _LIT( KUnicode, "converter" );
    TBuf8<KLength> foreign( KForeign );
    TBuf<KLength> unicode( KUnicode );

    TBuf8<KLength> replace( KForeign );
    TInt dropOut;
    
    CnvUtilities::ConvertFromIntermediateBufferInPlace( 0, foreign, dropOut, replace, foreign.Length() );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKCharacterConversionPP::TestCCPPConvertToUnicodeFromModalForeignL 
// -----------------------------------------------------------------------------
TInt CTestSDKCharacterConversionPP::TestCCPPConvertToUnicodeFromModalForeignL( CStifItemParser& /*aItem*/ )
    {
    CnvUtilities::SState sstate;
    sstate.iConversionData = &( CCnvCharacterSetConverter::AsciiConversionData() );
    TBuf8<KLength> sequence;
    const TUint KControlCharacterEscape=0x1b;
    sequence.Append( KControlCharacterEscape );
    sstate.iEscapeSequence = &sequence;
    CArrayFix<CnvUtilities::SState>* array = new(ELeave) CArrayFixFlat<CnvUtilities::SState>( 1 );
    CleanupStack::PushL( array );
    array->AppendL( sstate );
    
    _LIT8( KForeign, "converter" );
    _LIT( KUnicode, "converter" );
    TBuf8<KLength> foreign( KForeign );
    TBuf<KLength> unicode;

    TInt state = 0;
    TInt unconversion;
    TInt index;
    
    TInt num = CnvUtilities::ConvertToUnicodeFromModalForeign( CCnvCharacterSetConverter::ELittleEndian, unicode, 
                                                               foreign, state, unconversion, index, array->Array() );
    STIF_ASSERT_TRUE( 0 == num );
    STIF_ASSERT_TRUE( 0 == unicode.Compare( KUnicode ) );
    
    CleanupStack::PopAndDestroy( array );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKCharacterConversionPP::TestCCPPConvertToUnicodeFromModalForeignFlagL 
// -----------------------------------------------------------------------------
TInt CTestSDKCharacterConversionPP::TestCCPPConvertToUnicodeFromModalForeignFlagL( CStifItemParser& /*aItem*/ )
    {
    CnvUtilities::SState sstate;
    sstate.iConversionData = &( CCnvCharacterSetConverter::AsciiConversionData() );
    TBuf8<KLength> sequence;
    const TUint KControlCharacterEscape=0x1b;
    sequence.Append( KControlCharacterEscape );
    sstate.iEscapeSequence = &sequence;
    CArrayFix<CnvUtilities::SState>* array = new(ELeave) CArrayFixFlat<CnvUtilities::SState>( 1 );
    CleanupStack::PushL( array );
    array->AppendL( sstate );
    
    _LIT8( KForeign, "converter" );
    _LIT( KUnicode, "converter" );
    TBuf8<KLength> foreign( KForeign );
    TBuf<KLength> unicode;

    TUint inputFlag = CCnvCharacterSetConverter::EInputConversionFlagAppend;
    TUint outputFlag;
    TInt state = 0;
    TInt unconversion;
    TInt index;
    
    TInt num = CnvUtilities::ConvertToUnicodeFromModalForeign( CCnvCharacterSetConverter::ELittleEndian, unicode, 
                                                               foreign, state, unconversion, index, array->Array(), 
                                                               outputFlag, inputFlag );
    STIF_ASSERT_TRUE( 0 == num );
    STIF_ASSERT_TRUE( 0 == unicode.Compare( KUnicode ) );
    
    CleanupStack::PopAndDestroy( array );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKCharacterConversionPP::TestCCPPConvertToUnicodeFromHeterogeneousForeignL 
// -----------------------------------------------------------------------------
TInt CTestSDKCharacterConversionPP::TestCCPPConvertToUnicodeFromHeterogeneousForeignL( CStifItemParser& /*aItem*/ )
    {
    CArrayFix<CnvUtilities::SMethod>* array = new(ELeave) CArrayFixFlat<CnvUtilities::SMethod>( 1 );
    CleanupStack::PushL( array );
    
    CnvUtilities::SMethod method;
    method.iConversionData = &( CCnvCharacterSetConverter::AsciiConversionData() );
    method.iNumberOfBytesPerCharacter = 1;
    method.iNumberOfCoreBytesPerCharacter = 1;
    method.iConvertToIntermediateBufferInPlace = ConvertToIntermediateBufferInPlace;
    method.iNumberOfBytesAbleToConvert = NumberOfBytesAbleToConvert;
    
    array->AppendL( method );
    
    _LIT8( KForeign, "c" );
    _LIT( KUnicode, "c" );
    TBuf8<KLength> foreign( KForeign );
    TBuf<KLength> unicode;

    TInt unconversion;
    TInt index;
    
    TInt num = CnvUtilities::ConvertToUnicodeFromHeterogeneousForeign( CCnvCharacterSetConverter::ELittleEndian, unicode, 
                                                                       foreign, unconversion, index, array->Array() );
    STIF_ASSERT_TRUE( 0 == num );
    STIF_ASSERT_TRUE( 0 == unicode.Compare( KUnicode ) );
    
    CleanupStack::PopAndDestroy( array );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKCharacterConversionPP::TestCCPPConvertToUnicodeFromHeterogeneousForeignFlagL 
// -----------------------------------------------------------------------------
TInt CTestSDKCharacterConversionPP::TestCCPPConvertToUnicodeFromHeterogeneousForeignFlagL( CStifItemParser& /*aItem*/ )
    {
    CArrayFix<CnvUtilities::SMethod>* array = new(ELeave) CArrayFixFlat<CnvUtilities::SMethod>( 1 );
    CleanupStack::PushL( array );
    
    CnvUtilities::SMethod method;
    method.iConversionData = &( CCnvCharacterSetConverter::AsciiConversionData() );
    method.iNumberOfBytesPerCharacter = 1;
    method.iNumberOfCoreBytesPerCharacter = 1;
    method.iConvertToIntermediateBufferInPlace = ConvertToIntermediateBufferInPlace;
    method.iNumberOfBytesAbleToConvert = NumberOfBytesAbleToConvert;
    
    array->AppendL( method );
    
    _LIT8( KForeign, "converte" );
    _LIT( KUnicode, "converte" );
    TBuf8<KLength> foreign( KForeign );
    TBuf<KLength> unicode;

    TUint inputFlag = CCnvCharacterSetConverter::EInputConversionFlagAppend;
    TUint outputFlag;
    TInt unconversion;
    TInt index;
    
    TInt num = CnvUtilities::ConvertToUnicodeFromHeterogeneousForeign( CCnvCharacterSetConverter::ELittleEndian, unicode, 
                                                                       foreign, unconversion, index, array->Array(), 
                                                                       outputFlag, inputFlag );
    STIF_ASSERT_TRUE( 0 == num );
    STIF_ASSERT_TRUE( 0 == unicode.Compare( KUnicode ) );
    
    CleanupStack::PopAndDestroy( array );
    
    return KErrNone;
    
    }

//  [End of File]
