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





#ifndef C_TESTDOMSORTUTIL_H
#define C_TESTDOMSORTUTIL_H

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
_LIT( KtestdomsortutilLogPath, "\\logs\\testframework\\testdomsortutil\\" ); 
// Log file
_LIT( KtestdomsortutilLogFile, "testdomsortutil.txt" ); 
_LIT( KtestdomsortutilLogFileWithTitle, "testdomsortutil_[%S].txt" );

/**
*  CTestDOMSortUtil test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDOMSortUtil ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDOMSortUtil* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDOMSortUtil();

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
    CTestDOMSortUtil( CTestModuleIf& aTestModuleIf );

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

private: // test functions of TSortKey class

    /**
    * test default constructor method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSortKeyConstruct( CStifItemParser& aItem );

    /**
    * test Text method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSortKeyText( CStifItemParser& aItem );

    /**
    * test Type method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSortKeyType( CStifItemParser& aItem );

private: // test functions of CSortUtil class

    /**
    * test NewL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSortUtilNewL( CStifItemParser& aItem );

private: // test functions of MSortUtil class

    /**
    * test CompareItems method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSortUtilCompareItemsL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    };

#endif      // C_TESTDOMSORTUTIL_H

// End of File
