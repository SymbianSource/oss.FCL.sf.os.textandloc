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
		0x5b,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		0,
		0,
			{
			0
			}
		},
		{
		0x5c,
		0x5c,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, 73)
			}
		},
		{
		0x5d,
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
		0xdf,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, 65216)
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
		0x00a5,
		0x00a5,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		1,
		0,
			{
			STATIC_CAST(TUint, -73)
			}
		},
		{
		0xff61,
		0xff9f,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		1,
		0,
			{
			STATIC_CAST(TUint, -65216)
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

GLREF_D const SCnvConversionData jisRomanConversionData;
GLDEF_D const SCnvConversionData jisRomanConversionData=
	{
	SCnvConversionData::EFixedBigEndian,
		{
		ARRAY_LENGTH(foreignVariableByteDataRanges),
		foreignVariableByteDataRanges
		},
		{
		3-0,
		foreignToUnicodeDataRanges+0
		},
		{
		2-0,
		unicodeToForeignDataRanges+0
		}
	};

GLREF_D const SCnvConversionData halfWidthKatakana8ConversionData;
GLDEF_D const SCnvConversionData halfWidthKatakana8ConversionData=
	{
	SCnvConversionData::EFixedBigEndian,
		{
		ARRAY_LENGTH(foreignVariableByteDataRanges),
		foreignVariableByteDataRanges
		},
		{
		4-3,
		foreignToUnicodeDataRanges+3
		},
		{
		3-2,
		unicodeToForeignDataRanges+2
		}
	};

