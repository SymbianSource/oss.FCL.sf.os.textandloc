/*
* Copyright (c) 2002-2004 Nokia Corporation and/or its subsidiary(-ies). 
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

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SIndexedTable16::SEntry indexedTable16_foreignToUnicode_1[]=
	{
		{
		0x090e
		},
		{
		0x090f
		},
		{
		0x0910
		},
		{
		0x090d
		},
		{
		0x0912
		},
		{
		0x0913
		},
		{
		0x0914
		},
		{
		0x0911
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SIndexedTable16::SEntry indexedTable16_foreignToUnicode_2[]=
	{
		{
		0x0946
		},
		{
		0x0947
		},
		{
		0x0948
		},
		{
		0x0945
		},
		{
		0x094a
		},
		{
		0x094b
		},
		{
		0x094c
		},
		{
		0x0949
		},
		{
		0x094d
		},
		{
		0x093c
		},
		{
		0x0964
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_foreignToUnicode_1[]=
	{
		{
		0x80,
		0x0960
		},
		{
		0x81,
		0x0961
		},
		{
		0x82,
		0x0962
		},
		{
		0x83,
		0x0963
		},
		{
		0x84,
		0x090c
		},
		{
		0x85,
		0x0944
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_foreignToUnicode_2[]=
	{
		{
		0xa1,
		0x0901
		},
		{
		0xa2,
		0x0902
		},
		{
		0xa3,
		0x0903
		},
		{
		0xa4,
		0x0905
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_foreignToUnicode_3[]=
	{
		{
		0xce,
		0x095f
		},
		{
		0xcf,
		0x0930
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_foreignToUnicode_4[]=
	{
		{
		0xd9,
		0x00a0
		},
		{
		0xda,
		0x093e
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_foreignToUnicode_5[]=
	{
		{
		0xfc,
		0x200c
		},
		{
		0xfd,
		0x200d
		},
		{
		0xfe,
		0x0950
		},
		{
		0xff,
		0x093d
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_foreignToUnicode_6[]=
	{
		{
		0xa1e9,
		0x0950
		},
		{
		0xa6e9,
		0x090c
		},
		{
		0xa7e9,
		0x0961
		},
		{
		0xaae9,
		0x0960
		},
		{
		0xb3e9,
		0x0958
		},
		{
		0xb4e9,
		0x0959
		},
		{
		0xb5e9,
		0x095a
		},
		{
		0xbae9,
		0x095b
		},
		{
		0xbfe9,
		0x095c
		},
		{
		0xc0e9,
		0x095d
		},
		{
		0xc9e9,
		0x095e
		},
		{
		0xdbe9,
		0x0962
		},
		{
		0xdce9,
		0x0963
		},
		{
		0xdfe9,
		0x0944
		},
		{
		0xeae9,
		0x093d
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SIndexedTable16::SEntry indexedTable16_unicodeToForeign_1[]=
	{
		{
		0xae
		},
		{
		0xab
		},
		{
		0xac
		},
		{
		0xad
		},
		{
		0xb2
		},
		{
		0xaf
		},
		{
		0xb0
		},
		{
		0xb1
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SIndexedTable16::SEntry indexedTable16_unicodeToForeign_2[]=
	{
		{
		0xe3
		},
		{
		0xe0
		},
		{
		0xe1
		},
		{
		0xe2
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
		0xe6
		},
		{
		0xe8
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_unicodeToForeign_1[]=
	{
		{
		0x0901,
		0xa1
		},
		{
		0x0902,
		0xa2
		},
		{
		0x0903,
		0xa3
		},
		{
		0x0905,
		0xa4
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_unicodeToForeign_2[]=
	{
		{
		0x0930,
		0xcf
		},
		{
		0x0931,
		0xd0
		},
		{
		0x0932,
		0xd1
		},
		{
		0x0933,
		0xd2
		},
		{
		0x0934,
		0xd3
		},
		{
		0x0935,
		0xd4
		},
		{
		0x0936,
		0xd5
		},
		{
		0x0937,
		0xd6
		},
		{
		0x0938,
		0xd7
		},
		{
		0x0939,
		0xd8
		},
		{
		0x093c,
		0xe9
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_unicodeToForeign_3[]=
	{
		{
		0x095f,
		0xce
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_unicodeToForeign_4[]=
	{
		{
		0x0964,
		0xea
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_unicodeToForeign_5[]=
	{
		{
		0x200c,
		0xe8
		},
		{
		0x200d,
		0xe9
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_unicodeToForeign_6[]=
	{
		{
		0x00a0,
		0xd9
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_unicodeToForeign_7[]=
	{
		{
		0x0960,
		0xaae9
		},
		{
		0x0961,
		0xa7e9
		},
		{
		0x0962,
		0xdbe9
		},
		{
		0x0963,
		0xdce9
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_unicodeToForeign_8[]=
	{
		{
		0x0950,
		0xa1e9
		},
		{
		0x0958,
		0xb3e9
		},
		{
		0x0959,
		0xb4e9
		},
		{
		0x095a,
		0xb5e9
		},
		{
		0x095b,
		0xbae9
		},
		{
		0x095c,
		0xbfe9
		},
		{
		0x095d,
		0xc0e9
		},
		{
		0x095e,
		0xc9e9
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_unicodeToForeign_9[]=
	{
		{
		0x093d,
		0xeae9
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_unicodeToForeign_10[]=
	{
		{
		0x0944,
		0xdfe9
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_unicodeToForeign_11[]=
	{
		{
		0x090c,
		0xa6e9
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
		0x85,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		0,
		0,
			{
			UData_SKeyedTable1616(keyedTable1616_foreignToUnicode_1)
			}
		},
		{
		0xa1,
		0xa4,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		0,
		0,
			{
			UData_SKeyedTable1616(keyedTable1616_foreignToUnicode_2)
			}
		},
		{
		0xa5,
		0xaa,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, 2145)
			}
		},
		{
		0xab,
		0xb2,
		SCnvConversionData::SOneDirectionData::SRange::EIndexedTable16,
		0,
		0,
			{
			UData_SIndexedTable16(indexedTable16_foreignToUnicode_1)
			}
		},
		{
		0xb3,
		0xcd,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, 2146)
			}
		},
		{
		0xce,
		0xcf,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		0,
		0,
			{
			UData_SKeyedTable1616(keyedTable1616_foreignToUnicode_3)
			}
		},
		{
		0xd0,
		0xd8,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, 2145)
			}
		},
		{
		0xd9,
		0xda,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		0,
		0,
			{
			UData_SKeyedTable1616(keyedTable1616_foreignToUnicode_4)
			}
		},
		{
		0xdb,
		0xdf,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, 2148)
			}
		},
		{
		0xe0,
		0xea,
		SCnvConversionData::SOneDirectionData::SRange::EIndexedTable16,
		0,
		0,
			{
			UData_SIndexedTable16(indexedTable16_foreignToUnicode_2)
			}
		},
		{
		0xf1,
		0xfa,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, 2165)
			}
		},
		{
		0xfc,
		0xff,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		0,
		0,
			{
			UData_SKeyedTable1616(keyedTable1616_foreignToUnicode_5)
			}
		},
		{
		0xa1e9,
		0xeae9,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		0,
		0,
			{
			UData_SKeyedTable1616(keyedTable1616_foreignToUnicode_6)
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
		0x0901,
		0x0905,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		1,
		0,
			{
			UData_SKeyedTable1616(keyedTable1616_unicodeToForeign_1)
			}
		},
		{
		0x0906,
		0x090b,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		1,
		0,
			{
			STATIC_CAST(TUint, -2145)
			}
		},
		{
		0x090d,
		0x0914,
		SCnvConversionData::SOneDirectionData::SRange::EIndexedTable16,
		1,
		0,
			{
			UData_SIndexedTable16(indexedTable16_unicodeToForeign_1)
			}
		},
		{
		0x0915,
		0x092f,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		1,
		0,
			{
			STATIC_CAST(TUint, -2146)
			}
		},
		{
		0x0930,
		0x093c,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		1,
		0,
			{
			UData_SKeyedTable1616(keyedTable1616_unicodeToForeign_2)
			}
		},
		{
		0x093e,
		0x0943,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		1,
		0,
			{
			STATIC_CAST(TUint, -2148)
			}
		},
		{
		0x0945,
		0x094d,
		SCnvConversionData::SOneDirectionData::SRange::EIndexedTable16,
		1,
		0,
			{
			UData_SIndexedTable16(indexedTable16_unicodeToForeign_2)
			}
		},
		{
		0x095f,
		0x095f,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		1,
		0,
			{
			UData_SKeyedTable1616(keyedTable1616_unicodeToForeign_3)
			}
		},
		{
		0x0964,
		0x0964,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		1,
		0,
			{
			UData_SKeyedTable1616(keyedTable1616_unicodeToForeign_4)
			}
		},
		{
		0x0966,
		0x096f,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		1,
		0,
			{
			STATIC_CAST(TUint, -2165)
			}
		},
		{
		0x200c,
		0x200d,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		1,
		0,
			{
			UData_SKeyedTable1616(keyedTable1616_unicodeToForeign_5)
			}
		},
		{
		0x00a0,
		0x00a0,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		1,
		0,
			{
			UData_SKeyedTable1616(keyedTable1616_unicodeToForeign_6)
			}
		},
		{
		0x0960,
		0x0963,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		2,
		0,
			{
			UData_SKeyedTable1616(keyedTable1616_unicodeToForeign_7)
			}
		},
		{
		0x0950,
		0x095e,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		2,
		0,
			{
			UData_SKeyedTable1616(keyedTable1616_unicodeToForeign_8)
			}
		},
		{
		0x093d,
		0x093d,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		2,
		0,
			{
			UData_SKeyedTable1616(keyedTable1616_unicodeToForeign_9)
			}
		},
		{
		0x0944,
		0x0944,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		2,
		0,
			{
			UData_SKeyedTable1616(keyedTable1616_unicodeToForeign_10)
			}
		},
		{
		0x090c,
		0x090c,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		2,
		0,
			{
			UData_SKeyedTable1616(keyedTable1616_unicodeToForeign_11)
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

