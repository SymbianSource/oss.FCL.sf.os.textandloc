/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies). 
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

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SIndexedTable16::SEntry indexedTable16_foreignToUnicode_1[]=
	{
		{
		0x2500
		},
		{
		0x2502
		},
		{
		0x250c
		},
		{
		0x2510
		},
		{
		0x2514
		},
		{
		0x2518
		},
		{
		0x251c
		},
		{
		0x2524
		},
		{
		0x252c
		},
		{
		0x2534
		},
		{
		0x253c
		},
		{
		0x2580
		},
		{
		0x2584
		},
		{
		0x2588
		},
		{
		0x258c
		},
		{
		0x2590
		},
		{
		0x2591
		},
		{
		0x2592
		},
		{
		0x2593
		},
		{
		0x2320
		},
		{
		0x25a0
		},
		{
		0x2219
		},
		{
		0x221a
		},
		{
		0x2248
		},
		{
		0x2264
		},
		{
		0x2265
		},
		{
		0x00a0
		},
		{
		0x2321
		},
		{
		0x00b0
		},
		{
		0x00b2
		},
		{
		0x00b7
		},
		{
		0x00f7
		},
		{
		0x2550
		},
		{
		0x2551
		},
		{
		0x2552
		},
		{
		0x0451
		},
		{
		0x0454
		},
		{
		0x2554
		},
		{
		0x0456
		},
		{
		0x0457
		},
		{
		0x2557
		},
		{
		0x2558
		},
		{
		0x2559
		},
		{
		0x255a
		},
		{
		0x255b
		},
		{
		0x0491
		},
		{
		0x255d
		},
		{
		0x255e
		},
		{
		0x255f
		},
		{
		0x2560
		},
		{
		0x2561
		},
		{
		0x0401
		},
		{
		0x0404
		},
		{
		0x2563
		},
		{
		0x0406
		},
		{
		0x0407
		},
		{
		0x2566
		},
		{
		0x2567
		},
		{
		0x2568
		},
		{
		0x2569
		},
		{
		0x256a
		},
		{
		0x0490
		},
		{
		0x256c
		},
		{
		0x00a9
		},
		{
		0x044e
		},
		{
		0x0430
		},
		{
		0x0431
		},
		{
		0x0446
		},
		{
		0x0434
		},
		{
		0x0435
		},
		{
		0x0444
		},
		{
		0x0433
		},
		{
		0x0445
		},
		{
		0x0438
		},
		{
		0x0439
		},
		{
		0x043a
		},
		{
		0x043b
		},
		{
		0x043c
		},
		{
		0x043d
		},
		{
		0x043e
		},
		{
		0x043f
		},
		{
		0x044f
		},
		{
		0x0440
		},
		{
		0x0441
		},
		{
		0x0442
		},
		{
		0x0443
		},
		{
		0x0436
		},
		{
		0x0432
		},
		{
		0x044c
		},
		{
		0x044b
		},
		{
		0x0437
		},
		{
		0x0448
		},
		{
		0x044d
		},
		{
		0x0449
		},
		{
		0x0447
		},
		{
		0x044a
		},
		{
		0x042e
		},
		{
		0x0410
		},
		{
		0x0411
		},
		{
		0x0426
		},
		{
		0x0414
		},
		{
		0x0415
		},
		{
		0x0424
		},
		{
		0x0413
		},
		{
		0x0425
		},
		{
		0x0418
		},
		{
		0x0419
		},
		{
		0x041a
		},
		{
		0x041b
		},
		{
		0x041c
		},
		{
		0x041d
		},
		{
		0x041e
		},
		{
		0x041f
		},
		{
		0x042f
		},
		{
		0x0420
		},
		{
		0x0421
		},
		{
		0x0422
		},
		{
		0x0423
		},
		{
		0x0416
		},
		{
		0x0412
		},
		{
		0x042c
		},
		{
		0x042b
		},
		{
		0x0417
		},
		{
		0x0428
		},
		{
		0x042d
		},
		{
		0x0429
		},
		{
		0x0427
		},
		{
		0x042a
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SIndexedTable16::SEntry indexedTable16_unicodeToForeign_1[]=
	{
		{
		0xe1
		},
		{
		0xe2
		},
		{
		0xf7
		},
		{
		0xe7
		},
		{
		0xe4
		},
		{
		0xe5
		},
		{
		0xf6
		},
		{
		0xfa
		},
		{
		0xe9
		},
		{
		0xea
		},
		{
		0xeb
		},
		{
		0xec
		},
		{
		0xed
		},
		{
		0xee
		},
		{
		0xef
		},
		{
		0xf0
		},
		{
		0xf2
		},
		{
		0xf3
		},
		{
		0xf4
		},
		{
		0xf5
		},
		{
		0xe6
		},
		{
		0xe8
		},
		{
		0xe3
		},
		{
		0xfe
		},
		{
		0xfb
		},
		{
		0xfd
		},
		{
		0xff
		},
		{
		0xf9
		},
		{
		0xf8
		},
		{
		0xfc
		},
		{
		0xe0
		},
		{
		0xf1
		},
		{
		0xc1
		},
		{
		0xc2
		},
		{
		0xd7
		},
		{
		0xc7
		},
		{
		0xc4
		},
		{
		0xc5
		},
		{
		0xd6
		},
		{
		0xda
		},
		{
		0xc9
		},
		{
		0xca
		},
		{
		0xcb
		},
		{
		0xcc
		},
		{
		0xcd
		},
		{
		0xce
		},
		{
		0xcf
		},
		{
		0xd0
		},
		{
		0xd2
		},
		{
		0xd3
		},
		{
		0xd4
		},
		{
		0xd5
		},
		{
		0xc6
		},
		{
		0xc8
		},
		{
		0xc3
		},
		{
		0xde
		},
		{
		0xdb
		},
		{
		0xdd
		},
		{
		0xdf
		},
		{
		0xd9
		},
		{
		0xd8
		},
		{
		0xdc
		},
		{
		0xc0
		},
		{
		0xd1
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_unicodeToForeign_1[]=
	{
		{
		0x00a0,
		0x9a
		},
		{
		0x00a9,
		0xbf
		},
		{
		0x00b0,
		0x9c
		},
		{
		0x00b2,
		0x9d
		},
		{
		0x00b7,
		0x9e
		},
		{
		0x00f7,
		0x9f
		},
		{
		0x0401,
		0xb3
		},
		{
		0x0404,
		0xb4
		},
		{
		0x0406,
		0xb6
		},
		{
		0x0407,
		0xb7
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_unicodeToForeign_2[]=
	{
		{
		0x0451,
		0xa3
		},
		{
		0x0454,
		0xa4
		},
		{
		0x0456,
		0xa6
		},
		{
		0x0457,
		0xa7
		},
		{
		0x0490,
		0xbd
		},
		{
		0x0491,
		0xad
		},
		{
		0x2219,
		0x95
		},
		{
		0x221a,
		0x96
		},
		{
		0x2248,
		0x97
		},
		{
		0x2264,
		0x98
		},
		{
		0x2265,
		0x99
		},
		{
		0x2320,
		0x93
		},
		{
		0x2321,
		0x9b
		},
		{
		0x2500,
		0x80
		},
		{
		0x2502,
		0x81
		},
		{
		0x250c,
		0x82
		},
		{
		0x2510,
		0x83
		},
		{
		0x2514,
		0x84
		},
		{
		0x2518,
		0x85
		},
		{
		0x251c,
		0x86
		},
		{
		0x2524,
		0x87
		},
		{
		0x252c,
		0x88
		},
		{
		0x2534,
		0x89
		},
		{
		0x253c,
		0x8a
		},
		{
		0x2550,
		0xa0
		},
		{
		0x2551,
		0xa1
		},
		{
		0x2552,
		0xa2
		},
		{
		0x2554,
		0xa5
		},
		{
		0x2557,
		0xa8
		},
		{
		0x2558,
		0xa9
		},
		{
		0x2559,
		0xaa
		},
		{
		0x255a,
		0xab
		},
		{
		0x255b,
		0xac
		},
		{
		0x255d,
		0xae
		},
		{
		0x255e,
		0xaf
		},
		{
		0x255f,
		0xb0
		},
		{
		0x2560,
		0xb1
		},
		{
		0x2561,
		0xb2
		},
		{
		0x2563,
		0xb5
		},
		{
		0x2566,
		0xb8
		},
		{
		0x2567,
		0xb9
		},
		{
		0x2568,
		0xba
		},
		{
		0x2569,
		0xbb
		},
		{
		0x256a,
		0xbc
		},
		{
		0x256c,
		0xbe
		},
		{
		0x2580,
		0x8b
		},
		{
		0x2584,
		0x8c
		},
		{
		0x2588,
		0x8d
		},
		{
		0x258c,
		0x8e
		},
		{
		0x2590,
		0x8f
		},
		{
		0x2591,
		0x90
		},
		{
		0x2592,
		0x91
		},
		{
		0x2593,
		0x92
		},
		{
		0x25a0,
		0x94
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
		0x80,
		0xff,
		SCnvConversionData::SOneDirectionData::SRange::EIndexedTable16,
		0,
		0,
			{
			UData_SIndexedTable16(indexedTable16_foreignToUnicode_1)
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
		0x0407,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		1,
		0,
			{
			UData_SKeyedTable1616(keyedTable1616_unicodeToForeign_1)
			}
		},
		{
		0x0410,
		0x044f,
		SCnvConversionData::SOneDirectionData::SRange::EIndexedTable16,
		1,
		0,
			{
			UData_SIndexedTable16(indexedTable16_unicodeToForeign_1)
			}
		},
		{
		0x0451,
		0x25a0,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		1,
		0,
			{
			UData_SKeyedTable1616(keyedTable1616_unicodeToForeign_2)
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

