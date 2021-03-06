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
*
*/


#if !defined(__WPMAIN_H__)
#define __WPMAIN_H_

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__EIKAPP_H__)
#include <eikapp.h>
#endif


class CWordApplication : public CEikApplication
/**
CWordApplication
@internalComponent
*/
	{
private: // from CApaApplication
	CApaDocument* CreateDocumentL();
	TUid AppDllUid() const;
	};



#endif
