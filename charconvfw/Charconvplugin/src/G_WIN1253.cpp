/*
* Copyright (c) 1253 Nokia Corporation and/or its subsidiary(-ies). 
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
	0x0088,
	0x2030,
	0x008a,
	0x2039,
	0x008c,
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
	0x0098,
	0x2122,
	0x009a,
	0x203a,
	0x009c,
	0x009d,
	0x009e,
	0x009f,
	0x00a0,
	0x0385,
	0x0386,
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
	0x2015,
	0x00b0,
	0x00b1,
	0x00b2,
	0x00b3,
	0x0384,
	0x00b5,
	0x00b6,
	0x00b7,
	0x0388,
	0x0389,
	0x038a,
	0x00bb,
	0x038c,
	0x00bd,
	0x038e,
	0x038f,
	0x0390,
	0x0391,
	0x0392,
	0x0393,
	0x0394,
	0x0395,
	0x0396,
	0x0397,
	0x0398,
	0x0399,
	0x039a,
	0x039b,
	0x039c,
	0x039d,
	0x039e,
	0x039f,
	0x03a0,
	0x03a1,
	0x00d2,
	0x03a3,
	0x03a4,
	0x03a5,
	0x03a6,
	0x03a7,
	0x03a8,
	0x03a9,
	0x03aa,
	0x03ab,
	0x03ac,
	0x03ad,
	0x03ae,
	0x03af,
	0x03b0,
	0x03b1,
	0x03b2,
	0x03b3,
	0x03b4,
	0x03b5,
	0x03b6,
	0x03b7,
	0x03b8,
	0x03b9,
	0x03ba,
	0x03bb,
	0x03bc,
	0x03bd,
	0x03be,
	0x03bf,
	0x03c0,
	0x03c1,
	0x03c2,
	0x03c3,
	0x03c4,
	0x03c5,
	0x03c6,
	0x03c7,
	0x03c8,
	0x03c9,
	0x03ca,
	0x03cb,
	0x03cc,
	0x03cd,
	0x03ce,
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
		0x0088,
		0x88
		},
		{
		0x008a,
		0x8a
		},
		{
		0x008c,
		0x8c
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
		0x0098,
		0x98
		},
		{
		0x009a,
		0x9a
		},
		{
		0x009c,
		0x9c
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
		0x009f,
		0x9f
		},
		{
		0x00a0,
		0xa0
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
		0x00bb,
		0xbb
		},
		{
		0x00bd,
		0xbd
		},
		{
		0x00d2,
		0xd2
		},
		{
		0x00ff,
		0xff
		},
		{
		0x0192,
		0x83
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_unicodeToForeign_2[]=
	{
		{
		0x0384,
		0xb4
		},
		{
		0x0385,
		0xa1
		},
		{
		0x0386,
		0xa2
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
		0x2013,
		0x96
		},
		{
		0x2014,
		0x97
		},
		{
		0x2015,
		0xaf
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
			REINTERPRET_CAST(TUint, CONST_CAST(SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable16OfIndexedTables16::SKeyedEntry*, keyedTables16OfIndexedTables16_keyedEntries_foreignToUnicode_1))
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
		0x00a3,
		0x00ae,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		1,
		0,
			{
			0,
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
			STATIC_CAST(TUint, -720),
			0
			}
		},
		{
		0x03a3,
		0x03ce,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		1,
		0,
			{
			STATIC_CAST(TUint, -720),
			0
			}
		},
		{
		0x0081,
		0x0192,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		1,
		0,
			{
			STATIC_CAST(TUint, ARRAY_LENGTH(keyedTable1616_unicodeToForeign_1)),
			REINTERPRET_CAST(TUint, CONST_CAST(SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry*, keyedTable1616_unicodeToForeign_1))
			}
		},
		{
		0x0384,
		0x2122,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		1,
		0,
			{
			STATIC_CAST(TUint, ARRAY_LENGTH(keyedTable1616_unicodeToForeign_2)),
			REINTERPRET_CAST(TUint, CONST_CAST( SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry*,keyedTable1616_unicodeToForeign_2))
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

