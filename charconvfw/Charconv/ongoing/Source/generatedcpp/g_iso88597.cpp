/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
		0xa0,
		0x00a0
		},
		{
		0xa1,
		0x2018
		},
		{
		0xa2,
		0x2019
		},
		{
		0xa3,
		0x00a3
		},
		{
		0xa6,
		0x00a6
		},
		{
		0xa7,
		0x00a7
		},
		{
		0xa8,
		0x00a8
		},
		{
		0xa9,
		0x00a9
		},
		{
		0xab,
		0x00ab
		},
		{
		0xac,
		0x00ac
		},
		{
		0xad,
		0x00ad
		},
		{
		0xaf,
		0x2015
		},
		{
		0xb0,
		0x00b0
		},
		{
		0xb1,
		0x00b1
		},
		{
		0xb2,
		0x00b2
		},
		{
		0xb3,
		0x00b3
		},
		{
		0xb4,
		0x0384
		},
		{
		0xb5,
		0x0385
		},
		{
		0xb6,
		0x0386
		},
		{
		0xb7,
		0x00b7
		},
		{
		0xb8,
		0x0388
		},
		{
		0xb9,
		0x0389
		},
		{
		0xba,
		0x038a
		},
		{
		0xbb,
		0x00bb
		},
		{
		0xbc,
		0x038c
		},
		{
		0xbd,
		0x00bd
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_unicodeToForeign_1[]=
	{
		{
		0x00a0,
		0xa0
		},
		{
		0x00a3,
		0xa3
		},
		{
		0x00a6,
		0xa6
		},
		{
		0x00a7,
		0xa7
		},
		{
		0x00a8,
		0xa8
		},
		{
		0x00a9,
		0xa9
		},
		{
		0x00ab,
		0xab
		},
		{
		0x00ac,
		0xac
		},
		{
		0x00ad,
		0xad
		},
		{
		0x00b0,
		0xb0
		},
		{
		0x00b1,
		0xb1
		},
		{
		0x00b2,
		0xb2
		},
		{
		0x00b3,
		0xb3
		},
		{
		0x00b7,
		0xb7
		},
		{
		0x00bb,
		0xbb
		},
		{
		0x00bd,
		0xbd
		},
		{
		0x0384,
		0xb4
		},
		{
		0x0385,
		0xb5
		},
		{
		0x0386,
		0xb6
		},
		{
		0x0388,
		0xb8
		},
		{
		0x0389,
		0xb9
		},
		{
		0x038a,
		0xba
		},
		{
		0x038c,
		0xbc
		},
		{
		0x2015,
		0xaf
		},
		{
		0x2018,
		0xa1
		},
		{
		0x2019,
		0xa2
		}
	};

LOCAL_D const SCnvConversionData::SVariableByteData::SRange foreignVariableByteDataRanges[]=
	{
		{
		0x00,
		0xff,
		0,
		0
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange foreignToUnicodeDataRanges[]=
	{
		{
		0x00,
		0x9f,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		0,
		0,
			{
			0
			}
		},
		{
		0xbe,
		0xd1,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, 720)
			}
		},
		{
		0xd3,
		0xfe,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, 720)
			}
		},
		{
		0xa0,
		0xbd,
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
		0x009f,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		1,
		0,
			{
			0
			}
		},
		{
		0x038e,
		0x03a1,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		1,
		0,
			{
			STATIC_CAST(TUint, -720)
			}
		},
		{
		0x03a3,
		0x03ce,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		1,
		0,
			{
			STATIC_CAST(TUint, -720)
			}
		},
		{
		0x00a0,
		0x2019,
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

