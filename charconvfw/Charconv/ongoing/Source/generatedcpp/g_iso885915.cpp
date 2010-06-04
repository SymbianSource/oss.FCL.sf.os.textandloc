/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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

LOCAL_D const TUint16 keyedTables16OfIndexedTables16_indexedEntries_foreignToUnicode_1[]=
	{
	0x00a0,
	0x00a1,
	0x00a2,
	0x00a3,
	0x20ac,
	0x00a5,
	0x0160,
	0x00a7,
	0x0161,
	0x00a9,
	0x00aa,
	0x00ab,
	0x00ac,
	0x00ad,
	0x00ae,
	0x00af,
	0x00b0,
	0x00b1,
	0x00b2,
	0x00b3,
	0x017d,
	0x00b5,
	0x00b6,
	0x00b7,
	0x017e,
	0x00b9,
	0x00ba,
	0x00bb,
	0x0152,
	0x0153,
	0x0178
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable16OfIndexedTables16::SKeyedEntry keyedTables16OfIndexedTables16_keyedEntries_foreignToUnicode_1[]=
	{
		{
		0xa0,
		0xbe,
		keyedTables16OfIndexedTables16_indexedEntries_foreignToUnicode_1
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_unicodeToForeign_1[]=
	{
		{
		0x00a0,
		0xa0
		},
		{
		0x00a1,
		0xa1
		},
		{
		0x00a2,
		0xa2
		},
		{
		0x00a3,
		0xa3
		},
		{
		0x00a5,
		0xa5
		},
		{
		0x00a7,
		0xa7
		},
		{
		0x00a9,
		0xa9
		},
		{
		0x00aa,
		0xaa
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
		0x00ae,
		0xae
		},
		{
		0x00af,
		0xaf
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
		0x00b5,
		0xb5
		},
		{
		0x00b6,
		0xb6
		},
		{
		0x00b7,
		0xb7
		},
		{
		0x00b9,
		0xb9
		},
		{
		0x00ba,
		0xba
		},
		{
		0x00bb,
		0xbb
		},
		{
		0x0152,
		0xbc
		},
		{
		0x0153,
		0xbd
		},
		{
		0x0160,
		0xa6
		},
		{
		0x0161,
		0xa8
		},
		{
		0x0178,
		0xbe
		},
		{
		0x017d,
		0xb4
		},
		{
		0x017e,
		0xb8
		},
		{
		0x20ac,
		0xa4
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
		0xa0,
		0xbe,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable16OfIndexedTables16,
		0,
		0,
			{
			UData_SKeyedTable16OfIndexedTables16(keyedTables16OfIndexedTables16_keyedEntries_foreignToUnicode_1)
			}
		},
		{
		0xbf,
		0xff,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		0,
		0,
			{
			0
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
		0x00bf,
		0x00ff,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		1,
		0,
			{
			0
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

