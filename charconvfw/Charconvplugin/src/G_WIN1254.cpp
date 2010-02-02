/*
* Copyright (c) 1254 Nokia Corporation and/or its subsidiary(-ies). 
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

LOCAL_D const TUint16 keyedTables16OfIndexedTables16_indexedEntries_foreignToUnicode_1[]=
	{
	0x20ac,
	0x0081,
	0x201a,
	0x0192,
	0x201e,
	0x2026,
	0x2020,
	0x2021,
	0x02c6,
	0x2030,
	0x0160,
	0x2039,
	0x0152,
	0x008d,
	0x008e,
	0x008f,
	0x0090,
	0x2018,
	0x2019,
	0x201c,
	0x201d,
	0x2022,
	0x2013,
	0x2014,
	0x02dc,
	0x2122,
	0x0161,
	0x203a,
	0x0153,
	0x009d,
	0x009e,
	0x0178,
	0x00a0,
	0x00a1,
	0x00a2,
	0x00a3,
	0x00a4,
	0x00a5,
	0x00a6,
	0x00a7,
	0x00a8,
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
	0x00b4,
	0x00b5,
	0x00b6,
	0x00b7,
	0x00b8,
	0x00b9,
	0x00ba,
	0x00bb,
	0x00bc,
	0x00bd,
	0x00be,
	0x00bf,
	0x00c0,
	0x00c1,
	0x00c2,
	0x00c3,
	0x00c4,
	0x00c5,
	0x00c6,
	0x00c7,
	0x00c8,
	0x00c9,
	0x00ca,
	0x00cb,
	0x00cc,
	0x00cd,
	0x00ce,
	0x00cf,
	0x011e,
	0x00d1,
	0x00d2,
	0x00d3,
	0x00d4,
	0x00d5,
	0x00d6,
	0x00d7,
	0x00d8,
	0x00d9,
	0x00da,
	0x00db,
	0x00dc,
	0x0130,
	0x015e,
	0x00df,
	0x00e0,
	0x00e1,
	0x00e2,
	0x00e3,
	0x00e4,
	0x00e5,
	0x00e6,
	0x00e7,
	0x00e8,
	0x00e9,
	0x00ea,
	0x00eb,
	0x00ec,
	0x00ed,
	0x00ee,
	0x00ef,
	0x011f,
	0x00f1,
	0x00f2,
	0x00f3,
	0x00f4,
	0x00f5,
	0x00f6,
	0x00f7,
	0x00f8,
	0x00f9,
	0x00fa,
	0x00fb,
	0x00fc,
	0x0131,
	0x015f,
	0x00ff
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable16OfIndexedTables16::SKeyedEntry keyedTables16OfIndexedTables16_keyedEntries_foreignToUnicode_1[]=
	{
		{
		0x80,
		0xff,
		keyedTables16OfIndexedTables16_indexedEntries_foreignToUnicode_1
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_unicodeToForeign_1[]=
	{
		{
		0x0081,
		0x81
		},
		{
		0x008d,
		0x8d
		},
		{
		0x008e,
		0x8e
		},
		{
		0x008f,
		0x8f
		},
		{
		0x0090,
		0x90
		},
		{
		0x009d,
		0x9d
		},
		{
		0x009e,
		0x9e
		},
		{
		0x00ff,
		0xff
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_unicodeToForeign_2[]=
	{
		{
		0x011e,
		0xd0
		},
		{
		0x011f,
		0xf0
		},
		{
		0x0130,
		0xdd
		},
		{
		0x0131,
		0xfd
		},
		{
		0x0152,
		0x8c
		},
		{
		0x0153,
		0x9c
		},
		{
		0x015e,
		0xde
		},
		{
		0x015f,
		0xfe
		},
		{
		0x0160,
		0x8a
		},
		{
		0x0161,
		0x9a
		},
		{
		0x0178,
		0x9f
		},
		{
		0x0192,
		0x83
		},
		{
		0x02c6,
		0x88
		},
		{
		0x02dc,
		0x98
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
		0x201a,
		0x82
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
		0x201e,
		0x84
		},
		{
		0x2020,
		0x86
		},
		{
		0x2021,
		0x87
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
		0x2030,
		0x89
		},
		{
		0x2039,
		0x8b
		},
		{
		0x203a,
		0x9b
		},
		{
		0x20ac,
		0x80
		},
		{
		0x2122,
		0x99
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
		0x7f,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		0,
		0,
			{
			0,
			0
			}
		},
		{
		0x80,
		0xff,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable16OfIndexedTables16,
		0,
		0,
			{
			STATIC_CAST(TUint, ARRAY_LENGTH(keyedTables16OfIndexedTables16_keyedEntries_foreignToUnicode_1)),
			REINTERPRET_CAST(TUint, CONST_CAST( SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable16OfIndexedTables16::SKeyedEntry*, keyedTables16OfIndexedTables16_keyedEntries_foreignToUnicode_1))
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
			0,
			0
			}
		},
		{
		0x00a0,
		0x00cf,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		1,
		0,
			{
			0,
			0
			}
		},
		{
		0x00d1,
		0x00dc,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		1,
		0,
			{
			0,
			0
			}
		},
		{
		0x00df,
		0x00ef,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		1,
		0,
			{
			0,
			0
			}
		},
		{
		0x00f1,
		0x00fc,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		1,
		0,
			{
			0,
			0
			}
		},
		{
		0x0081,
		0x00ff,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		1,
		0,
			{
			STATIC_CAST(TUint, ARRAY_LENGTH(keyedTable1616_unicodeToForeign_1)),
			REINTERPRET_CAST(TUint, CONST_CAST( SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry*, keyedTable1616_unicodeToForeign_1))
			}
		},
		{
		0x011e,
		0x2122,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		1,
		0,
			{
			STATIC_CAST(TUint, ARRAY_LENGTH(keyedTable1616_unicodeToForeign_2)),
			REINTERPRET_CAST(TUint, CONST_CAST( SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry*, keyedTable1616_unicodeToForeign_2))
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

