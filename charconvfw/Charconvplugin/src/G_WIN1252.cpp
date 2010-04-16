/*
* Copyright (c) 1252 Nokia Corporation and/or its subsidiary(-ies). 
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
	0x20ac
	};

LOCAL_D const TUint16 keyedTables16OfIndexedTables16_indexedEntries_foreignToUnicode_2[]=
	{
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
	0x0152
	};

LOCAL_D const TUint16 keyedTables16OfIndexedTables16_indexedEntries_foreignToUnicode_3[]=
	{
	0x017d
	};

LOCAL_D const TUint16 keyedTables16OfIndexedTables16_indexedEntries_foreignToUnicode_4[]=
	{
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
	0x0153
	};

LOCAL_D const TUint16 keyedTables16OfIndexedTables16_indexedEntries_foreignToUnicode_5[]=
	{
	0x017e,
	0x0178
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable16OfIndexedTables16::SKeyedEntry keyedTables16OfIndexedTables16_keyedEntries_foreignToUnicode_1[]=
	{
		{
		0x80,
		0x80,
		keyedTables16OfIndexedTables16_indexedEntries_foreignToUnicode_1
		},
		{
		0x82,
		0x8c,
		keyedTables16OfIndexedTables16_indexedEntries_foreignToUnicode_2
		},
		{
		0x8e,
		0x8e,
		keyedTables16OfIndexedTables16_indexedEntries_foreignToUnicode_3
		},
		{
		0x91,
		0x9c,
		keyedTables16OfIndexedTables16_indexedEntries_foreignToUnicode_4
		},
		{
		0x9e,
		0x9f,
		keyedTables16OfIndexedTables16_indexedEntries_foreignToUnicode_5
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_unicodeToForeign_1[]=
	{
		{
		0x0152,
		0x8c
		},
		{
		0x0153,
		0x9c
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
		0x017d,
		0x8e
		},
		{
		0x017e,
		0x9e
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
			0
			}
		},
		{
		0xa0,
		0xff,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		0,
		0,
			{
			0
			}
		},
		{
		0x80,
		0x9f,
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
		0x007f,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		1,
		0,
			{
			0
			}
		},
		{
		0x00a0,
		0x00ff,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		1,
		0,
			{
			0
			}
		},
		{
		0x0152,
		0x2122,
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

