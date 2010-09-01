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


#ifndef C_TESTSDKDIRLOC_H
#define C_TESTSDKDIRLOC_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <coemain.h>
#include <coeaui.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdkdirlocLogPath, "\\logs\\testframework\\testsdkdirloc\\" );
// Log file
_LIT( KtestsdkdirlocLogFile, "testsdkdirloc.txt" );
_LIT( KtestsdkdirlocLogFileWithTitle, "testsdkdirloc_[%S].txt" );

// FORWARD DECLARATIONS
class CTestSDKDirLoc;
class CDirectoryLocalizer;

/**
 *  CTestSDKDirLoc test class for STIF Test Framework TestScripter.
 *  ?other_description_lines
 *
 *  @lib ?library
 *  @since ?Series60_version
 */
NONSHARABLE_CLASS( CTestSDKDirLoc ) : public CScriptBase
    {
public: // Constructors and destructor

    /**
     * Two-phased constructor.
     */
    static CTestSDKDirLoc* NewL( CTestModuleIf& aTestModuleIf );

    /**
     * Destructor.
     */
    virtual ~CTestSDKDirLoc();

public: // Functions from base classes

    /**
     * From CScriptBase Runs a script line.
     * @since ?Series60_version
     * @param aItem Script line containing method name and parameters
     * @return Symbian OS error code
     */
    virtual TInt RunMethodL( CStifItemParser& aItem );

private:

    /**
     * C++ default constructor.
     */
    CTestSDKDirLoc( CTestModuleIf& aTestModuleIf );

    /**
     * By default Symbian 2nd phase constructor is private.
     */
    void ConstructL();

    /**
     * Frees all resources allocated from test methods.
     * @since ?Series60_version
     */
    void Delete();

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

private: // Test CDirectoryLocalizer.h
    /**
     * TestDLNewL test function for testing the NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDLNewL( CStifItemParser& /*aItem*/ );

    /**
     * TestDLNewLReaderL test function for testing the NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDLNewLResReaderL( CStifItemParser& /*aItem*/ );

    /**
     * TestDLNewLResIDL test function for testing the NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDLNewLResIDL( CStifItemParser& /*aItem*/ );

    /**
     * TestDLAddFromResourceL test function for testing the AddFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDLAddFromResourceL( CStifItemParser& /*aItem*/ );

    /**
     * TestDLAddFromResourceLResIDL test function for testing the AddFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDLAddFromResourceLResIDL( CStifItemParser& /*aItem*/ );

    /**
     * TestDLSetFullPath test function for testing the SetFullPath function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDLSetFullPath( CStifItemParser& /*aItem*/ );

    /**
     * TestDLIsLocalized test function for testing the IsLocalized function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDLIsLocalized( CStifItemParser& /*aItem*/ );

    /**
     * TestDLLocalizedName test function for testing the LocalizedName function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDLLocalizedName( CStifItemParser& /*aItem*/ );

    /**
     * TestDLExtraData test function for testing the ExtraData function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDLExtraData( CStifItemParser& /*aItem*/ );

    /**
     * TestDLIcon test function for testing the Icon function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDLIcon( CStifItemParser& /*aItem*/ );

    /**
     * TestDLDelete test function for testing the destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDLDelete( CStifItemParser& /*aItem*/ );

private: // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    //Own : test functions in CDirectoryLocalizer.h
    CDirectoryLocalizer* iDirLocalizer;
    };

#endif      // C_TESTSDKDIRLOC_H
// End of File
