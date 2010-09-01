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



#ifndef C_TESTDOMJAPANESELANGUAGEUTILITIES_H
#define C_TESTDOMJAPANESELANGUAGEUTILITIES_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestdomjapaneselanguageutilitiesLogPath, "\\logs\\testframework\\testdomjapaneselanguageutilities\\" ); 
// Log file
_LIT( KtestdomjapaneselanguageutilitiesLogFile, "testdomjapaneselanguageutilities.txt" ); 
_LIT( KtestdomjapaneselanguageutilitiesLogFileWithTitle, "testdomjapaneselanguageutilities_[%S].txt" );

/**
*  CTestDOMJapaneseLanguageUtilities test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDOMJapaneseLanguageUtilities ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDOMJapaneseLanguageUtilities* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDOMJapaneseLanguageUtilities();

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
    CTestDOMJapaneseLanguageUtilities( CTestModuleIf& aTestModuleIf );

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

private: // [TestMethods]

    /**
    * TestJLUConvertHalfToFullWidth test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestJLUConvertHalfToFullWidth( CStifItemParser& aItem );
    /**
    * TestJLUConvertFullToHalfWidth test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestJLUConvertFullToHalfWidth( CStifItemParser& aItem );
    /**
    * TestJLUConvertHalfToFullWidthKatakana test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestJLUConvertHalfToFullWidthKatakana( CStifItemParser& aItem );
    /**
    * TestJLUConvertFullToHalfWidthKatakana test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestJLUConvertFullToHalfWidthKatakana( CStifItemParser& aItem );
    /**
    * TestJLUConvertFullHiragnaToFullKatakana test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestJLUConvertFullHiragnaToFullKatakana( CStifItemParser& aItem );
    /**
    * TestJLUIsKatakana test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestJLUIsKatakana( CStifItemParser& aItem );
    /**
    * TestJLUIsHiragana test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestJLUIsHiragana( CStifItemParser& aItem );
    /**
    * TestJLUIsKanji test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestJLUIsKanji( CStifItemParser& aItem );
    /**
    * TestJLUIsHalfWidth test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestJLUIsHalfWidth( CStifItemParser& aItem );
    /**
    * TestJLUIsFullWidth test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestJLUIsFullWidth( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    /**
     * ?description_of_pointer_member
     * Not own.
     */
    //?type* ?member_name;

    };

#endif      // C_TESTDOMJAPANESELANGUAGEUTILITIES_H

// End of File
