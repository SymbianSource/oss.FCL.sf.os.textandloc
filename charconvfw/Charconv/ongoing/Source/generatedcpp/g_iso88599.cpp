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

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_foreignToUnicode_1[]=
	{
		{
		0xd0,
		0x011e
		},
		{
		0xdd,
		0x0130
		},
		{
		0xde,
		0x015e
		},
		{
		0xf0,
		0x011f
		},
		{
		0xfd,
		0x0131
		},
		{
		0xfe,
		0x015f
		},
		{
		0xff,
		0x00ff
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_unicodeToForeign_1[]=
	{
		{
		0x00ff,
		0xff
		},
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
		0x015e,
		0xde
		},
		{
		0x015f,
		0xfe
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
		0xcf,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		0,
		0,
			{
			0
			}
		},
		{
		0xd1,
		0xdc,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		0,
		0,
			{
			0
			}
		},
		{
		0xdf,
		0xef,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		0,
		0,
			{
			0
			}
		},
		{
		0xf1,
		0xfc,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		0,
		0,
			{
			0
			}
		},
		{
		0xd0,
		0xff,
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
		0x00a0,
		0x00cf,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		1,
		0,
			{
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
			0
			}
		},
		{
		0x00ff,
		0x015f,
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

