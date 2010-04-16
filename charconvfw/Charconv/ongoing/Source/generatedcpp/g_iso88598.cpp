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
	0x00a0
	};

LOCAL_D const TUint16 keyedTables16OfIndexedTables16_indexedEntries_foreignToUnicode_2[]=
	{
	0x00a2,
	0x00a3,
	0x00a4,
	0x00a5,
	0x00a6,
	0x00a7,
	0x00a8,
	0x00a9,
	0x00d7,
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
	0x00f7,
	0x00bb,
	0x00bc,
	0x00bd,
	0x00be
	};

LOCAL_D const TUint16 keyedTables16OfIndexedTables16_indexedEntries_foreignToUnicode_3[]=
	{
	0x2017
	};

LOCAL_D const TUint16 keyedTables16OfIndexedTables16_indexedEntries_foreignToUnicode_4[]=
	{
	0x200e,
	0x200f
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable16OfIndexedTables16::SKeyedEntry keyedTables16OfIndexedTables16_keyedEntries_foreignToUnicode_1[]=
	{
		{
		0xa0,
		0xa0,
		keyedTables16OfIndexedTables16_indexedEntries_foreignToUnicode_1
		},
		{
		0xa2,
		0xbe,
		keyedTables16OfIndexedTables16_indexedEntries_foreignToUnicode_2
		},
		{
		0xdf,
		0xdf,
		keyedTables16OfIndexedTables16_indexedEntries_foreignToUnicode_3
		},
		{
		0xfd,
		0xfe,
		keyedTables16OfIndexedTables16_indexedEntries_foreignToUnicode_4
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_unicodeToForeign_1[]=
	{
		{
		0x00a0,
		0xa0
		},
		{
		0x00bb,
		0xbb
		},
		{
		0x00bc,
		0xbc
		},
		{
		0x00bd,
		0xbd
		},
		{
		0x00be,
		0xbe
		},
		{
		0x00d7,
		0xaa
		},
		{
		0x00f7,
		0xba
		},
		{
		0x200e,
		0xfd
		},
		{
		0x200f,
		0xfe
		},
		{
		0x2017,
		0xdf
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
		0xe0,
		0xfa,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, 1264)
			}
		},
		{
		0xa0,
		0xfe,
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
		0x00a2,
		0x00a9,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		1,
		0,
			{
			0
			}
		},
		{
		0x00ab,
		0x00b9,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		1,
		0,
			{
			0
			}
		},
		{
		0x05d0,
		0x05ea,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		1,
		0,
			{
			STATIC_CAST(TUint, -1264)
			}
		},
		{
		0x00a0,
		0x2017,
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

