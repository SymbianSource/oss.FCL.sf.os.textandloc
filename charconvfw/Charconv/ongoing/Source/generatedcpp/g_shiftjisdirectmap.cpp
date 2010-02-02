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

_LIT8(KLit8ReplacementForUnconvertibleUnicodeCharacters, "\x81\x48");

GLDEF_C const TDesC8& ReplacementForUnconvertibleUnicodeCharacters_internal()
	{
	return KLit8ReplacementForUnconvertibleUnicodeCharacters;
	}

LOCAL_D const SCnvConversionData::SVariableByteData::SRange foreignVariableByteDataRanges[]=
	{
		{
		0xf0,
		0xf9,
		1,
		0
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange foreignToUnicodeDataRanges[]=
	{
		{
		0xf040,
		0xf07e,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, -4160)
			}
		},
		{
		0xf080,
		0xf0fc,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, -4161)
			}
		},
		{
		0xf140,
		0xf17e,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, -4228)
			}
		},
		{
		0xf180,
		0xf1fc,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, -4229)
			}
		},
		{
		0xf240,
		0xf27e,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, -4296)
			}
		},
		{
		0xf280,
		0xf2fc,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, -4297)
			}
		},
		{
		0xf340,
		0xf37e,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, -4364)
			}
		},
		{
		0xf380,
		0xf3fc,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, -4365)
			}
		},
		{
		0xf440,
		0xf47e,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, -4432)
			}
		},
		{
		0xf480,
		0xf4fc,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, -4433)
			}
		},
		{
		0xf540,
		0xf57e,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, -4500)
			}
		},
		{
		0xf580,
		0xf5fc,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, -4501)
			}
		},
		{
		0xf640,
		0xf67e,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, -4568)
			}
		},
		{
		0xf680,
		0xf6fc,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, -4569)
			}
		},
		{
		0xf740,
		0xf77e,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, -4636)
			}
		},
		{
		0xf780,
		0xf7fc,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, -4637)
			}
		},
		{
		0xf840,
		0xf87e,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, -4704)
			}
		},
		{
		0xf880,
		0xf89e,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, -4705)
			}
		},
		{
		0xf89f,
		0xf8fc,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, -4705)
			}
		},
		{
		0xf940,
		0xf97e,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, -4772)
			}
		},
		{
		0xf980,
		0xf9fc,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, -4773)
			}
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange unicodeToForeignDataRanges[]=
	{
		{
		0xe000,
		0xe03e,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		2,
		0,
			{
			STATIC_CAST(TUint, 4160)
			}
		},
		{
		0xe03f,
		0xe0bb,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		2,
		0,
			{
			STATIC_CAST(TUint, 4161)
			}
		},
		{
		0xe0bc,
		0xe0fa,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		2,
		0,
			{
			STATIC_CAST(TUint, 4228)
			}
		},
		{
		0xe0fb,
		0xe177,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		2,
		0,
			{
			STATIC_CAST(TUint, 4229)
			}
		},
		{
		0xe178,
		0xe1b6,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		2,
		0,
			{
			STATIC_CAST(TUint, 4296)
			}
		},
		{
		0xe1b7,
		0xe233,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		2,
		0,
			{
			STATIC_CAST(TUint, 4297)
			}
		},
		{
		0xe234,
		0xe272,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		2,
		0,
			{
			STATIC_CAST(TUint, 4364)
			}
		},
		{
		0xe273,
		0xe2ef,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		2,
		0,
			{
			STATIC_CAST(TUint, 4365)
			}
		},
		{
		0xe2f0,
		0xe32e,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		2,
		0,
			{
			STATIC_CAST(TUint, 4432)
			}
		},
		{
		0xe32f,
		0xe3ab,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		2,
		0,
			{
			STATIC_CAST(TUint, 4433)
			}
		},
		{
		0xe3ac,
		0xe3ea,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		2,
		0,
			{
			STATIC_CAST(TUint, 4500)
			}
		},
		{
		0xe3eb,
		0xe467,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		2,
		0,
			{
			STATIC_CAST(TUint, 4501)
			}
		},
		{
		0xe468,
		0xe4a6,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		2,
		0,
			{
			STATIC_CAST(TUint, 4568)
			}
		},
		{
		0xe4a7,
		0xe523,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		2,
		0,
			{
			STATIC_CAST(TUint, 4569)
			}
		},
		{
		0xe524,
		0xe562,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		2,
		0,
			{
			STATIC_CAST(TUint, 4636)
			}
		},
		{
		0xe563,
		0xe5df,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		2,
		0,
			{
			STATIC_CAST(TUint, 4637)
			}
		},
		{
		0xe5e0,
		0xe61e,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		2,
		0,
			{
			STATIC_CAST(TUint, 4704)
			}
		},
		{
		0xe61f,
		0xe63d,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		2,
		0,
			{
			STATIC_CAST(TUint, 4705)
			}
		},
		{
		0xe63e,
		0xe69b,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		2,
		0,
			{
			STATIC_CAST(TUint, 4705)
			}
		},
		{
		0xe69c,
		0xe6da,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		2,
		0,
			{
			STATIC_CAST(TUint, 4772)
			}
		},
		{
		0xe6db,
		0xe757,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		2,
		0,
			{
			STATIC_CAST(TUint, 4773)
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

