/*
* Copyright (c) 1250 Nokia Corporation and/or its subsidiary(-ies). 
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
	0x0083,
	0x201e,
	0x2026,
	0x2020,
	0x2021,
	0x0088,
	0x2030,
	0x0160,
	0x2039,
	0x015a,
	0x0164,
	0x017d,
	0x0179,
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
	0x0161,
	0x203a,
	0x015b,
	0x0165,
	0x017e,
	0x017a,
	0x00a0,
	0x02c7,
	0x02d8,
	0x0141,
	0x00a4,
	0x0104,
	0x00a6,
	0x00a7,
	0x00a8,
	0x00a9,
	0x015e,
	0x00ab,
	0x00ac,
	0x00ad,
	0x00ae,
	0x017b,
	0x00b0,
	0x00b1,
	0x02db,
	0x0142,
	0x00b4,
	0x00b5,
	0x00b6,
	0x00b7,
	0x00b8,
	0x0105,
	0x015f,
	0x00bb,
	0x013d,
	0x02dd,
	0x013e,
	0x017c,
	0x0154,
	0x00c1,
	0x00c2,
	0x0102,
	0x00c4,
	0x0139,
	0x0106,
	0x00c7,
	0x010c,
	0x00c9,
	0x0118,
	0x00cb,
	0x011a,
	0x00cd,
	0x00ce,
	0x010e,
	0x0110,
	0x0143,
	0x0147,
	0x00d3,
	0x00d4,
	0x0150,
	0x00d6,
	0x00d7,
	0x0158,
	0x016e,
	0x00da,
	0x0170,
	0x00dc,
	0x00dd,
	0x0162,
	0x00df,
	0x0155,
	0x00e1,
	0x00e2,
	0x0103,
	0x00e4,
	0x013a,
	0x0107,
	0x00e7,
	0x010d,
	0x00e9,
	0x0119,
	0x00eb,
	0x011b,
	0x00ed,
	0x00ee,
	0x010f,
	0x0111,
	0x0144,
	0x0148,
	0x00f3,
	0x00f4,
	0x0151,
	0x00f6,
	0x00f7,
	0x0159,
	0x016f,
	0x00fa,
	0x0171,
	0x00fc,
	0x00fd,
	0x0163,
	0x02d9
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable16OfIndexedTables16::SKeyedEntry keyedTables16OfIndexedTables16_keyedEntries_foreignToUnicode_1[]=
	{
		{
		0x80,
		0xff,
		keyedTables16OfIndexedTables16_indexedEntries_foreignToUnicode_1
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SIndexedTable16::SEntry indexedTable16_unicodeToForeign_1[]=
	{
		{
		0xc3
		},
		{
		0xe3
		},
		{
		0xa5
		},
		{
		0xb9
		},
		{
		0xc6
		},
		{
		0xe6
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SIndexedTable16::SEntry indexedTable16_unicodeToForeign_2[]=
	{
		{
		0xc8
		},
		{
		0xe8
		},
		{
		0xcf
		},
		{
		0xef
		},
		{
		0xd0
		},
		{
		0xf0
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SIndexedTable16::SEntry indexedTable16_unicodeToForeign_3[]=
	{
		{
		0xaa
		},
		{
		0xba
		},
		{
		0x8a
		},
		{
		0x9a
		},
		{
		0xde
		},
		{
		0xfe
		},
		{
		0x8d
		},
		{
		0x9d
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SIndexedTable16::SEntry indexedTable16_unicodeToForeign_4[]=
	{
		{
		0x8f
		},
		{
		0x9f
		},
		{
		0xaf
		},
		{
		0xbf
		},
		{
		0x8e
		},
		{
		0x9e
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_unicodeToForeign_1[]=
	{
		{
		0x0081,
		0x81
		},
		{
		0x0083,
		0x83
		},
		{
		0x0088,
		0x88
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
		0x00a0,
		0xa0
		},
		{
		0x00a4,
		0xa4
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
		0x00ae,
		0xae
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
		0x00b4,
		0xb4
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
		0x00b8,
		0xb8
		},
		{
		0x00bb,
		0xbb
		},
		{
		0x00c1,
		0xc1
		},
		{
		0x00c2,
		0xc2
		},
		{
		0x00c4,
		0xc4
		},
		{
		0x00c7,
		0xc7
		},
		{
		0x00c9,
		0xc9
		},
		{
		0x00cb,
		0xcb
		},
		{
		0x00cd,
		0xcd
		},
		{
		0x00ce,
		0xce
		},
		{
		0x00d3,
		0xd3
		},
		{
		0x00d4,
		0xd4
		},
		{
		0x00d6,
		0xd6
		},
		{
		0x00d7,
		0xd7
		},
		{
		0x00da,
		0xda
		},
		{
		0x00dc,
		0xdc
		},
		{
		0x00dd,
		0xdd
		},
		{
		0x00df,
		0xdf
		},
		{
		0x00e1,
		0xe1
		},
		{
		0x00e2,
		0xe2
		},
		{
		0x00e4,
		0xe4
		},
		{
		0x00e7,
		0xe7
		},
		{
		0x00e9,
		0xe9
		},
		{
		0x00eb,
		0xeb
		},
		{
		0x00ed,
		0xed
		},
		{
		0x00ee,
		0xee
		},
		{
		0x00f3,
		0xf3
		},
		{
		0x00f4,
		0xf4
		},
		{
		0x00f6,
		0xf6
		},
		{
		0x00f7,
		0xf7
		},
		{
		0x00fa,
		0xfa
		},
		{
		0x00fc,
		0xfc
		},
		{
		0x00fd,
		0xfd
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_unicodeToForeign_2[]=
	{
		{
		0x0118,
		0xca
		},
		{
		0x0119,
		0xea
		},
		{
		0x011a,
		0xcc
		},
		{
		0x011b,
		0xec
		},
		{
		0x0139,
		0xc5
		},
		{
		0x013a,
		0xe5
		},
		{
		0x013d,
		0xbc
		},
		{
		0x013e,
		0xbe
		},
		{
		0x0141,
		0xa3
		},
		{
		0x0142,
		0xb3
		},
		{
		0x0143,
		0xd1
		},
		{
		0x0144,
		0xf1
		},
		{
		0x0147,
		0xd2
		},
		{
		0x0148,
		0xf2
		},
		{
		0x0150,
		0xd5
		},
		{
		0x0151,
		0xf5
		},
		{
		0x0154,
		0xc0
		},
		{
		0x0155,
		0xe0
		},
		{
		0x0158,
		0xd8
		},
		{
		0x0159,
		0xf8
		},
		{
		0x015a,
		0x8c
		},
		{
		0x015b,
		0x9c
		},
		{
		0x016e,
		0xd9
		},
		{
		0x016f,
		0xf9
		},
		{
		0x0170,
		0xdb
		},
		{
		0x0171,
		0xfb
		},
		{
		0x02c7,
		0xa1
		},
		{
		0x02d8,
		0xa2
		},
		{
		0x02d9,
		0xff
		},
		{
		0x02db,
		0xb2
		},
		{
		0x02dd,
		0xbd
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
			REINTERPRET_CAST( TUint, CONST_CAST(SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable16OfIndexedTables16::SKeyedEntry*, keyedTables16OfIndexedTables16_keyedEntries_foreignToUnicode_1))
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
		0x0102,
		0x0107,
		SCnvConversionData::SOneDirectionData::SRange::EIndexedTable16,
		1,
		0,
			{
		    REINTERPRET_CAST(TUint, CONST_CAST( SCnvConversionData::SOneDirectionData::SRange::UData::SIndexedTable16::SEntry*, indexedTable16_unicodeToForeign_1)),
			0
			}
		},
		{
		0x010c,
		0x0111,
		SCnvConversionData::SOneDirectionData::SRange::EIndexedTable16,
		1,
		0,
			{
			REINTERPRET_CAST( TUint, CONST_CAST( SCnvConversionData::SOneDirectionData::SRange::UData::SIndexedTable16::SEntry*, indexedTable16_unicodeToForeign_2)),
			0
			}
		},
		{
		0x015e,
		0x0165,
		SCnvConversionData::SOneDirectionData::SRange::EIndexedTable16,
		1,
		0,
			{
			REINTERPRET_CAST(TUint, CONST_CAST( SCnvConversionData::SOneDirectionData::SRange::UData::SIndexedTable16::SEntry*, indexedTable16_unicodeToForeign_3)),
			0
			}
		},
		{
		0x0179,
		0x017e,
		SCnvConversionData::SOneDirectionData::SRange::EIndexedTable16,
		1,
		0,
			{
			REINTERPRET_CAST(TUint, CONST_CAST( SCnvConversionData::SOneDirectionData::SRange::UData::SIndexedTable16::SEntry*, indexedTable16_unicodeToForeign_4)),
			0
			}
		},
		{
		0x0081,
		0x00fd,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		1,
		0,
			{
			STATIC_CAST(TUint, ARRAY_LENGTH(keyedTable1616_unicodeToForeign_1)),
			REINTERPRET_CAST(TUint, CONST_CAST( SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry*, keyedTable1616_unicodeToForeign_1))
			}
		},
		{
		0x0118,
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

