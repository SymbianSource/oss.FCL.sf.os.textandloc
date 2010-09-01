/*
* Copyright (c) 2004-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* TFormat.cpp tests for TTmCharFormat and CTmParFormat
*
*/


#include "TAGMA.H"
#include <txtfrmat.h>
#include <e32test.h>

#define UNUSED_VAR(a) a = a

CTrapCleanup* TrapCleanup;
RTest test(_L("TFormat - TTmCharFormat and CTmParFormat"));

void INC041190()
	{
	TTmCharFormat tmcf;
	TCharFormat cf;
	cf.iFontPresentation.iHighlightStyle
		= TFontPresentation::EFontHighlightNoMatchesIndicator;
	tmcf.iEffects = 0;
	tmcf = cf;
	test(tmcf.iEffects == TTmCharFormat::ENoMatchesIndicator);
	cf.iFontPresentation.iHighlightStyle
		= TFontPresentation::EFontHighlightNone;
	tmcf.GetTCharFormat(cf);
	test(cf.iFontPresentation.iHighlightStyle
		== TFontPresentation::EFontHighlightNoMatchesIndicator);
	}

void RunTestsL()
	{
	__UHEAP_MARK;

	test.Title();
	test.Start(_L(" @SYMTestCaseID:SYSLIB-FORM-LEGACY-TFORMAT-0001 INC041190 - EText's EFontHighlightNoMatchesIndicator isn't mappd to anythng in TTmCharFormat "));
	INC041190();

	test.End();
	test.Close();

	__UHEAP_MARKENDC(0);
	}

TInt E32Main()
	{
	TrapCleanup = CTrapCleanup::New();
	TRAPD(err, RunTestsL());
    test(err == KErrNone);
	delete TrapCleanup;
	return 0;
	}
