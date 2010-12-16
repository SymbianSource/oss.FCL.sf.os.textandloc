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

LOCAL_D const TUint16 keyedTables16OfIndexedTables16_indexedEntries_foreignToUnicode_1[]=
	{
	0x00a0,
	0x1e02,
	0x1e03,
	0x00a3,
	0x010a,
	0x010b,
	0x1e0a,
	0x00a7,
	0x1e80,
	0x00a9,
	0x1e82,
	0x1e0b,
	0x1ef2,
	0x00ad,
	0x00ae,
	0x0178,
	0x1e1e,
	0x1e1f,
	0x0120,
	0x0121,
	0x1e40,
	0x1e41,
	0x00b6,
	0x1e56,
	0x1e81,
	0x1e57,
	0x1e83,
	0x1e60,
	0x1ef3,
	0x1e84,
	0x1e85,
	0x1e61,
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
	0x0174,
	0x00d1,
	0x00d2,
	0x00d3,
	0x00d4,
	0x00d5,
	0x00d6,
	0x1e6a,
	0x00d8,
	0x00d9,
	0x00da,
	0x00db,
	0x00dc,
	0x00dd,
	0x0176,
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
	0x0175,
	0x00f1,
	0x00f2,
	0x00f3,
	0x00f4,
	0x00f5,
	0x00f6,
	0x1e6b,
	0x00f8,
	0x00f9,
	0x00fa,
	0x00fb,
	0x00fc,
	0x00fd,
	0x0177,
	0x00ff
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable16OfIndexedTables16::SKeyedEntry keyedTables16OfIndexedTables16_keyedEntries_foreignToUnicode_1[]=
	{
		{
		0xa0,
		0xff,
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
		0x00a3,
		0xa3
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
		0x00ad,
		0xad
		},
		{
		0x00ae,
		0xae
		},
		{
		0x00b6,
		0xb6
		},
		{
		0x00c0,
		0xc0
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
		0x00c3,
		0xc3
		},
		{
		0x00c4,
		0xc4
		},
		{
		0x00c5,
		0xc5
		},
		{
		0x00c6,
		0xc6
		},
		{
		0x00c7,
		0xc7
		},
		{
		0x00c8,
		0xc8
		},
		{
		0x00c9,
		0xc9
		},
		{
		0x00ca,
		0xca
		},
		{
		0x00cb,
		0xcb
		},
		{
		0x00cc,
		0xcc
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
		0x00cf,
		0xcf
		},
		{
		0x00d1,
		0xd1
		},
		{
		0x00d2,
		0xd2
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
		0x00d5,
		0xd5
		},
		{
		0x00d6,
		0xd6
		},
		{
		0x00d8,
		0xd8
		},
		{
		0x00d9,
		0xd9
		},
		{
		0x00da,
		0xda
		},
		{
		0x00db,
		0xdb
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
		0x00e0,
		0xe0
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
		0x00e3,
		0xe3
		},
		{
		0x00e4,
		0xe4
		},
		{
		0x00e5,
		0xe5
		},
		{
		0x00e6,
		0xe6
		},
		{
		0x00e7,
		0xe7
		},
		{
		0x00e8,
		0xe8
		},
		{
		0x00e9,
		0xe9
		},
		{
		0x00ea,
		0xea
		},
		{
		0x00eb,
		0xeb
		},
		{
		0x00ec,
		0xec
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
		0x00ef,
		0xef
		},
		{
		0x00f1,
		0xf1
		},
		{
		0x00f2,
		0xf2
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
		0x00f5,
		0xf5
		},
		{
		0x00f6,
		0xf6
		},
		{
		0x00f8,
		0xf8
		},
		{
		0x00f9,
		0xf9
		},
		{
		0x00fa,
		0xfa
		},
		{
		0x00fb,
		0xfb
		},
		{
		0x00fc,
		0xfc
		},
		{
		0x00fd,
		0xfd
		},
		{
		0x00ff,
		0xff
		},
		{
		0x010a,
		0xa4
		},
		{
		0x010b,
		0xa5
		},
		{
		0x0120,
		0xb2
		},
		{
		0x0121,
		0xb3
		},
		{
		0x0174,
		0xd0
		},
		{
		0x0175,
		0xf0
		},
		{
		0x0176,
		0xde
		},
		{
		0x0177,
		0xfe
		},
		{
		0x0178,
		0xaf
		},
		{
		0x1e02,
		0xa1
		},
		{
		0x1e03,
		0xa2
		},
		{
		0x1e0a,
		0xa6
		},
		{
		0x1e0b,
		0xab
		},
		{
		0x1e1e,
		0xb0
		},
		{
		0x1e1f,
		0xb1
		},
		{
		0x1e40,
		0xb4
		},
		{
		0x1e41,
		0xb5
		},
		{
		0x1e56,
		0xb7
		},
		{
		0x1e57,
		0xb9
		},
		{
		0x1e60,
		0xbb
		},
		{
		0x1e61,
		0xbf
		},
		{
		0x1e6a,
		0xd7
		},
		{
		0x1e6b,
		0xf7
		},
		{
		0x1e80,
		0xa8
		},
		{
		0x1e81,
		0xb8
		},
		{
		0x1e82,
		0xaa
		},
		{
		0x1e83,
		0xba
		},
		{
		0x1e84,
		0xbd
		},
		{
		0x1e85,
		0xbe
		},
		{
		0x1ef2,
		0xac
		},
		{
		0x1ef3,
		0xbc
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
		0xff,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable16OfIndexedTables16,
		0,
		0,
			{
			UData_SKeyedTable16OfIndexedTables16(keyedTables16OfIndexedTables16_keyedEntries_foreignToUnicode_1)
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
		0x00a0,
		0x1ef3,
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
