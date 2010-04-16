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





#ifndef C_TESTSDKCHARACTERCONVERSIONPP_H
#define C_TESTSDKCHARACTERCONVERSIONPP_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>
#include <TestclassAssert.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdkcharacterconversionppLogPath, "\\logs\\testframework\\testsdkcharacterconversionpp\\" ); 
// Log file
_LIT( KtestsdkcharacterconversionppLogFile, "testsdkcharacterconversionpp.txt" ); 
_LIT( KtestsdkcharacterconversionppLogFileWithTitle, "testsdkcharacterconversionpp_[%S].txt" );

/**
*  CTestSDKCharacterConversionPP test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestSDKCharacterConversionPP ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKCharacterConversionPP* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKCharacterConversionPP();

public: // Functions from base classes

    /**
    * From CScriptBase Runs a script line.
    * @since S60 5.0
    * @param aItem Script line containing method name and parameters
    * @return Symbian OS error code
    */
    virtual TInt RunMethodL( CStifItemParser& aItem );

private:

    /**
    * C++ default constructor.
    */
    CTestSDKCharacterConversionPP( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();
    
        /**
     * Turn off ScreenSaver
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    void TurnOffScreenSaver();

    /**
     * Restore ScreenSaver
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    void RestoreScreenSaver();

private: // Test CONVUTILS.h
/*                               class CnvUtilities                         */
    /**
     * TestCCPPConvertFromUnicodeL test function for testing the 
     *     ConvertFromUnicode function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCPPConvertFromUnicodeL( CStifItemParser& aItem );
    
    /**
     * TestCCPPConvertFromUnicodeFlagL test function for testing the 
     *     ConvertFromUnicode function with flag 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCPPConvertFromUnicodeFlagL( CStifItemParser& aItem );
    
    /**
     * TestCCPPConvertFromIntermediateBufferInPlace test function for testing the 
     *     ConvertFromIntermediateBufferInPlace function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCPPConvertFromIntermediateBufferInPlace( CStifItemParser& aItem );
    
    /**
     * TestCCPPConvertToUnicodeFromModalForeignL test function for testing the 
     *     ConvertToUnicodeFromModalForeign function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCPPConvertToUnicodeFromModalForeignL( CStifItemParser& aItem );
    
    /**
     * TestCCPPConvertToUnicodeFromModalForeignFlagL test function for testing the 
     *     ConvertToUnicodeFromModalForeign function with flag
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCPPConvertToUnicodeFromModalForeignFlagL( CStifItemParser& aItem );
    
    /**
     * TestCCPPConvertToUnicodeFromHeterogeneousForeignL test function for testing the 
     *     ConvertToUnicodeFromHeterogeneousForeign function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCPPConvertToUnicodeFromHeterogeneousForeignL( CStifItemParser& aItem );
    
    /**
     * TestCCPPConvertToUnicodeFromHeterogeneousForeignFlagL test function for testing the 
     *     ConvertToUnicodeFromHeterogeneousForeign function with flag
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCPPConvertToUnicodeFromHeterogeneousForeignFlagL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    };

#endif      // C_TESTSDKCHARACTERCONVERSIONPP_H

// End of File
