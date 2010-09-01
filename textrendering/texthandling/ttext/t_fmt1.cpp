/*
* Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* T_FMT.CPP
*
*/


#include <e32test.h>
#include <txtfmlyr.h>
#include <txtrich.h>
#include <txtfrmat.h>
#include <gdi.h>
#include "TXTSTD.H"


LOCAL_D RTest test(_L("TFormat Test Code for DEF047316"));

LOCAL_C void TestDEF047316L()
// Test CParaFormat stack definition leave protection
//
	{

	
	test.Start(_L(" @SYMTestCaseID:SYSLIB-ETEXT-LEGACY-t_fmt1-0001 CParaFormat - DEF047316 - stack definition leave protection "));
	CParaFormat paraFormat;
	
	// Allocate resources for paraFormat
	TTabStop tabStop;
	paraFormat.StoreTabL(tabStop);
	
	TParaBorder border;
	paraFormat.SetParaBorderL(CParaFormat::EParaBorderTop,border);

	paraFormat.iBullet=new(ELeave)TBullet;
	
	// Push cleanup method for paraFormat
	ResetOnCleanupL( &paraFormat);
	
	// Force cleanup method to be called
	CleanupStack::PopAndDestroy();

	// Note that test end is when paraFormat's destructor is called when 
	// this function terminates. The destructor should not cause any problems
	// even though we have already called the cleanup method
	
	test.End();
	}

GLDEF_C TInt E32Main()
//
// Tests TFORMAT.
//
	{
	CTrapCleanup* cleanup=CTrapCleanup::New();
	test.Title();
	
	__UHEAP_MARK;
	TRAPD(ret,TestDEF047316L());
	test(ret==KErrNone);

	__UHEAP_MARKEND;
		
	test.Close();

	delete cleanup;

	return(0);
	}
