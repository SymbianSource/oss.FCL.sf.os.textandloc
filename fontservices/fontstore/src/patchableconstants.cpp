/*
* Copyright (c) 1995-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include <e32def.h>

/**
@internalTechnology

The drive that is used by fontstore to Generate, Update and Load linked fonts
to/from.
 */
EXPORT_C extern const TInt8 KLinkedFontDrive = 0x63; //c in ASCII

#if (__ARMCC_VERSION <= 310000)
#include "FNTSTORE.H"
#endif
