/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies). 
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
* Description:  
*
*/




#include <e32std.h>
#include <convdata.h>
#include <convgeneratedcpp.h>

#define ARRAY_LENGTH(aArray) (sizeof(aArray)/sizeof((aArray)[0]))

#pragma warning (disable: 4049) // compiler limit : terminating line number emission

_LIT8(KLit8ReplacementForUnconvertibleUnicodeCharacters, "\x1a");

GLDEF_C const TDesC8& ReplacementForUnconvertibleUnicodeCharacters_internal()
	{
	return KLit8ReplacementForUnconvertibleUnicodeCharacters;
	}

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_foreignToUnicode_1[]=
	{
		{
		0x80,
		0x20ac
		},
		{
		0x85,
		0x2026
		},
		{
		0x91,
		0x2018
		},
		{
		0x92,
		0x2019
		},
		{
		0x93,
		0x201c
		},
		{
		0x94,
		0x201d
		},
		{
		0x95,
		0x2022
		},
		{
		0x96,
		0x2013
		},
		{
		0x97,
		0x2014
		},
		{
		0xa0,
		0x00a0
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_unicodeToForeign_1[]=
	{
		{
		0x00a0,
		0xa0
		},
		{
		0x2013,
		0x96
		},
		{
		0x2014,
		0x97
		},
		{
		0x2018,
		0x91
		},
		{
		0x2019,
		0x92
		},
		{
		0x201c,
		0x93
		},
		{
		0x201d,
		0x94
		},
		{
		0x2022,
		0x95
		},
		{
		0x2026,
		0x85
		},
		{
		0x20ac,
		0x80
		}
	};

LOCAL_D const SCnvConversionData::SVariableByteData::SRange foreignVariableByteDataRanges[]=
	{
		{
		0x00,
		0xfb,
		0,
		0
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange foreignToUnicodeDataRanges[]=
	{
		{
		0x00,
		0x7f,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		0,
		0,
			{
			0
			}
		},
		{
		0xa1,
		0xda,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, 3424)
			}
		},
		{
		0xdf,
		0xfb,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, 3424)
			}
		},
		{
		0x80,
		0xa0,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		0,
		0,
			{
			UData_SKeyedTable1616(keyedTable1616_foreignToUnicode_1)
			}
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange unicodeToForeignDataRanges[]=
	{
		{
		0x0000,
		0x007f,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		1,
		0,
			{
			0
			}
		},
		{
		0x0e01,
		0x0e3a,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		1,
		0,
			{
			STATIC_CAST(TUint, -3424)
			}
		},
		{
		0x0e3f,
		0x0e5b,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		1,
		0,
			{
			STATIC_CAST(TUint, -3424)
			}
		},
		{
		0x00a0,
		0x20ac,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		1,
		0,
			{
			UData_SKeyedTable1616(keyedTable1616_unicodeToForeign_1)
			}
		}
	};

GLDEF_D const SCnvConversionData conversionData=
	{
	SCnvConversionData::EFixedBigEndian,
		{
		ARRAY_LENGTH(foreignVariableByteDataRanges),
		foreignVariableByteDataRanges
		},
		{
		ARRAY_LENGTH(foreignToUnicodeDataRanges),
		foreignToUnicodeDataRanges
		},
		{
		ARRAY_LENGTH(unicodeToForeignDataRanges),
		unicodeToForeignDataRanges
		},
	NULL,
	NULL
	};

