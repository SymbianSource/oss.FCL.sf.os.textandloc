/*
* Copyright (c) 1997-2004 Nokia Corporation and/or its subsidiary(-ies). 
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

#define ARRAY_LENGTH(aArray) (sizeof(aArray)/sizeof((aArray)[0]))

LOCAL_D const TUint16 keyedTables16OfIndexedTables16_indexedEntries_sms7BitToUnicode_1[]=
	{
	0x0040,
	0x00a3,
	0x0024,
	0x00a5,
	0x00e8,
	0x00e9,
	0x00f9,
	0x00ec,
	0x00f2,
	0x00e7,
	0x000a,
	0x00d8,
	0x00f8,
	0x000d,
	0x00c5,
	0x00e5,
	0x0394,
	0x005f,
	0x03a6,
	0x0393,
	0x039b,
	0x03a9,
	0x03a0,
	0x03a8,
	0x03a3,
	0x0398,
	0x039e
	};

LOCAL_D const TUint16 keyedTables16OfIndexedTables16_indexedEntries_sms7BitToUnicode_2[]=
	{
	0x00c6,
	0x00e6,
	0x00df,
	0x00c9,
	0x0020,
	0x0021,
	0x0022,
	0x0023,
	0x00a4
	};

LOCAL_D const TUint16 keyedTables16OfIndexedTables16_indexedEntries_sms7BitToUnicode_3[]=
	{
	0x00c4,
	0x00d6,
	0x00d1,
	0x00dc,
	0x00a7,
	0x00bf
	};

LOCAL_D const TUint16 keyedTables16OfIndexedTables16_indexedEntries_sms7BitToUnicode_4[]=
	{
	0x00e4,
	0x00f6,
	0x00f1,
	0x00fc,
	0x00e0
	};

LOCAL_D const TUint16 keyedTables16OfIndexedTables16_indexedEntries_sms7BitToUnicode_5[]=
	{
	0x0040,
	0x00a3,
	0x0024,
	0x00a5,
	0x00e8,
	0x00e9,
	0x00f9,
	0x00ec,
	0x00f2,
	0x00c7,
	0x000c, // meant to be a "Page Break" - a FORM FEED character is the nearest thing in Unicode to this
	0x00d8,
	0x00f8,
	0x000d,
	0x00c5,
	0x00e5,
	0x0394,
	0x005f,
	0x03a6,
	0x0393,
	0x005e, // '^'
	0x03a9,
	0x03a0,
	0x03a8,
	0x03a3,
	0x0398,
	0x039e
	};

LOCAL_D const TUint16 keyedTables16OfIndexedTables16_indexedEntries_sms7BitToUnicode_6[]=
	{
	0x00c6,
	0x00e6,
	0x00df,
	0x00c9,
	0x0020,
	0x0021,
	0x0022,
	0x0023,
	0x00a4,
	0x0025,
	0x0026,
	0x0027,
	0x007b, // '{'
	0x007d, // '}'
	0x002a,
	0x002b,
	0x002c,
	0x002d,
	0x002e,
	0x005c, // '\'
	0x0030,
	0x0031,
	0x0032,
	0x0033,
	0x0034,
	0x0035,
	0x0036,
	0x0037,
	0x0038,
	0x0039,
	0x003a,
	0x003b,
	0x005b, // '['
	0x007e, // '~'
	0x005d, // ']'
	0x003f,
	0x007c  // '|'
	};

LOCAL_D const TUint16 keyedTables16OfIndexedTables16_indexedEntries_sms7BitToUnicode_7[]=
	{
	0x00c4,
	0x00d6,
	0x00d1,
	0x00dc,
	0x00a7,
	0x00bf,
	0x0061,
	0x0062,
	0x0063,
	0x0064,
	0x20ac  // Euro symbol
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable16OfIndexedTables16::SKeyedEntry keyedTables16OfIndexedTables16_keyedEntries_sms7BitToUnicode_1[]=
	{
		{
		0x00,
		0x1a,
		keyedTables16OfIndexedTables16_indexedEntries_sms7BitToUnicode_1
		},
		{
		0x1c,
		0x24,
		keyedTables16OfIndexedTables16_indexedEntries_sms7BitToUnicode_2
		},
		{
		0x5b,
		0x60,
		keyedTables16OfIndexedTables16_indexedEntries_sms7BitToUnicode_3
		},
		{
		0x7b,
		0x7f,
		keyedTables16OfIndexedTables16_indexedEntries_sms7BitToUnicode_4
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable16OfIndexedTables16::SKeyedEntry keyedTables16OfIndexedTables16_keyedEntries_sms7BitToUnicode_2[]=
	{
		{
		0x1b00,
		0x1b1a,
		keyedTables16OfIndexedTables16_indexedEntries_sms7BitToUnicode_5
		},
		{
		0x1b1c,
		0x1b40,
		keyedTables16OfIndexedTables16_indexedEntries_sms7BitToUnicode_6
		},
		{
		0x1b5b,
		0x1b65,
		keyedTables16OfIndexedTables16_indexedEntries_sms7BitToUnicode_7
		},
		{
		0x1b7b,
		0x1b7f,
		keyedTables16OfIndexedTables16_indexedEntries_sms7BitToUnicode_4
		}
	};

#if 0
LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_sms7BitToUnicode_1[]=
	{
		{
		0x1b0a,
		0x000c
		},
		{
		0x1b14,
		0x005e
		},
		{
		0x1b28,
		0x007b
		},
		{
		0x1b29,
		0x007d
		},
		{
		0x1b2f,
		0x005c
		},
		{
		0x1b3c,
		0x005b
		},
		{
		0x1b3d,
		0x007e
		},
		{
		0x1b3e,
		0x005d
		},
		{
		0x1b40,
		0x007c
		},
		{
		0x1b65,
		0x20ac
		}
	};
#endif //0

LOCAL_D const TUint16 keyedTables16OfIndexedTables16_indexedEntries_unicodeToSms7Bit_1[]=
	{
	0x60,
	0x41,
	0x41,
	0x41,
	0x41,
	0x5b,
	0x0e,
	0x1c,
	0x09,
	0x45,
	0x1f,
	0x45,
	0x45,
	0x49,
	0x49,
	0x49,
	0x49
	};

LOCAL_D const TUint16 keyedTables16OfIndexedTables16_indexedEntries_unicodeToSms7Bit_2[]=
	{
	0x5d,
	0x4f,
	0x4f,
	0x4f,
	0x4f,
	0x5c
	};

LOCAL_D const TUint16 keyedTables16OfIndexedTables16_indexedEntries_unicodeToSms7Bit_3[]=
	{
	0x0b,
	0x55,
	0x55,
	0x55,
	0x5e,
	0x59
	};

LOCAL_D const TUint16 keyedTables16OfIndexedTables16_indexedEntries_unicodeToSms7Bit_4[]=
	{
	0x1e,
	0x7f,
	0x61,
	0x61,
	0x61,
	0x7b,
	0x0f,
	0x1d,
	0x09,
	0x04,
	0x05,
	0x65,
	0x65,
	0x07,
	0x69,
	0x69,
	0x69
	};

LOCAL_D const TUint16 keyedTables16OfIndexedTables16_indexedEntries_unicodeToSms7Bit_5[]=
	{
	0x7d,
	0x08,
	0x6f,
	0x6f,
	0x6f,
	0x7c
	};

LOCAL_D const TUint16 keyedTables16OfIndexedTables16_indexedEntries_unicodeToSms7Bit_6[]=
	{
	0x0c,
	0x06,
	0x75,
	0x75,
	0x7e,
	0x79
	};

LOCAL_D const TUint16 keyedTables16OfIndexedTables16_indexedEntries_unicodeToSms7Bit_7[]=
	{
	0x49,
	0x41,
	0x42,
	0x13,
	0x10,
	0x45,
	0x5a,
	0x48,
	0x19,
	0x49,
	0x4b,
	0x14,
	0x4d,
	0x4e,
	0x1a,
	0x4f
	};

LOCAL_D const TUint16 keyedTables16OfIndexedTables16_indexedEntries_unicodeToSms7Bit_8[]=
	{
	0x18,
	0x54,
	0x59,
	0x12,
	0x58,
	0x17,
	0x15,
	0x49,
	0x59,
	0x41,
	0x45,
	0x48,
	0x49
	};

LOCAL_D const TUint16 keyedTables16OfIndexedTables16_indexedEntries_unicodeToSms7Bit_9[]=
	{
	0x59,
	0x41,
	0x42,
	0x13,
	0x10,
	0x45,
	0x5a,
	0x48,
	0x19,
	0x49,
	0x4b,
	0x14,
	0x4d,
	0x4e,
	0x1a,
	0x4f
	};

LOCAL_D const TUint16 keyedTables16OfIndexedTables16_indexedEntries_unicodeToSms7Bit_10[]=
	{
	0x16,
	0x50,
	0x18,
	0x18,
	0x54,
	0x59,
	0x12,
	0x58,
	0x17,
	0x15,
	0x49,
	0x59,
	0x4f,
	0x59,
	0x15
	};

LOCAL_D const TUint16 keyedTables16OfIndexedTables16_indexedEntries_unicodeToSms7Bit_11[]=
	{
	0x42,
	0x19,
	0x59,
	0x59,
	0x59,
	0x12
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable16OfIndexedTables16::SKeyedEntry keyedTables16OfIndexedTables16_keyedEntries_unicodeToSms7Bit_1[]=
	{
		{
		0x00bf,
		0x00cf,
		keyedTables16OfIndexedTables16_indexedEntries_unicodeToSms7Bit_1
		},
		{
		0x00d1,
		0x00d6,
		keyedTables16OfIndexedTables16_indexedEntries_unicodeToSms7Bit_2
		},
		{
		0x00d8,
		0x00dd,
		keyedTables16OfIndexedTables16_indexedEntries_unicodeToSms7Bit_3
		},
		{
		0x00df,
		0x00ef,
		keyedTables16OfIndexedTables16_indexedEntries_unicodeToSms7Bit_4
		},
		{
		0x00f1,
		0x00f6,
		keyedTables16OfIndexedTables16_indexedEntries_unicodeToSms7Bit_5
		},
		{
		0x00f8,
		0x00fd,
		keyedTables16OfIndexedTables16_indexedEntries_unicodeToSms7Bit_6
		},
		{
		0x0390,
		0x039f,
		keyedTables16OfIndexedTables16_indexedEntries_unicodeToSms7Bit_7
		},
		{
		0x03a3,
		0x03af,
		keyedTables16OfIndexedTables16_indexedEntries_unicodeToSms7Bit_8
		},
		{
		0x03b0,
		0x03bf,
		keyedTables16OfIndexedTables16_indexedEntries_unicodeToSms7Bit_9
		},
		{
		0x03c0,
		0x03ce,
		keyedTables16OfIndexedTables16_indexedEntries_unicodeToSms7Bit_10
		},
		{
		0x03d0,
		0x03d5,
		keyedTables16OfIndexedTables16_indexedEntries_unicodeToSms7Bit_11
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_unicodeToSms7Bit_1[]=
	{
		{
		0x000a,
		0x0a
		},
		{
		0x000d,
		0x0d
		},
		{
		0x001b,
		0x1b
		},
		{
		0x0020,
		0x20
		},
		{
		0x0021,
		0x21
		},
		{
		0x0022,
		0x22
		},
		{
		0x0023,
		0x23
		},
		{
		0x0024,
		0x02
		},
		{
		0x0040,
		0x00
		},
		{
		0x005f,
		0x11
		},
		{
		0x0072,
		0x72
		},
		{
		0x00a1,
		0x40
		},
		{
		0x00a3,
		0x01
		},
		{
		0x00a4,
		0x24
		},
		{
		0x00a5,
		0x03
		},
		{
		0x00a7,
		0x5f
		},
		{
		0x00a8,
		0x22
		},
		{
		0x00b4,
		0x27
		},
		{
		0x00C0,
		0x41
		},
		{
		0x00C1,
		0x41
		},
		{
		0x00C2,	0x41
		},
		{
		0x00C3,	0x41
		},
		{
		0x00C8,
		0x45
		},
		{
		0x00CA,
		0x45
		},
		{
		0x00CB,
		0x45
		},
		{
		0x00CC,
		0x49
		},
		{
		0x00CD,
		0x49
		},
		{
		0x00CE,
		0x49
		},
		{
		0x00CF,
		0x49
		},
		{
		0x00D0,
		0x44
		},
		{
		0x00D2,
		0x4F
		},
		{
		0x00D3,
		0x4F
		},
		{
		0x00D4,
		0x4F
		},
		{
		0x00D5,
		0x4F
		},
		{
		0x00D7,
		0x2A
		},
		{
		0x00D9,
		0x55
		},
		{
		0x00DA,
		0x55
		},
		{
		0x00DB,
		0x55
		},
		{
		0x00DD,
		0x59
		},
		{
		0x00DE,
		0x54
		},
		{
		0x00E1,
		0x61
		},
		{
		0x00E2,
		0x61
		},
		{
		0x00E3,
		0x61
		},
		{
		0x00E7,	
		0x09
		},
		{
		0x00EA,
		0x65
		},
		{
		0x00EB,	
		0x65
		},
		{
		0x00ED,	
		0x69
		},
		{
		0x00EE,	
		0x69
		},
		{
		0x00EF,
		0x69
		},
		{
		0x00F0,
		0x64
		},
		{
		0x00F3,	
		0x6F
		},
		{
		0x00F4,	
		0x6F
		},
		{
		0x00F5,
		0x6F
		},
		{
		0x00F7,	
		0x6F
		},
		{
		0x00FA,
		0x75
		},
		{
		0x00FB,
		0x75
		},
		{
		0x00FD,	
		0x79
		},
		{
		0x00FE,	
		0x74
		},
		{
		0x00ff,
		0x79
		},
		{
		0x0100,	
		0x41
		},
		{
		0x0101,	
		0x61
		},
		{
		0x0102,	
		0x41
		},
		{
		0x0103,
		0x61
		},
		///////////////// A with ogonek
	    {
		0x0104,
		0x41  
		},
		/////////////////
	    ///////////////// a with ogonek
	    {
		0x0105,
		0x61  
		},
		/////////////////
		///////////////// C with acute
	    {
		0x0106,
		0x43  
		},
	    ///////////////// c with acute
	    {
		0x0107,
		0x63  
		},
		{
		0x0108,
		0x43
		},
		{
		0x0109,
		0x63
		},
		{
		0x010A,
		0x43
		},
		{
		0x010B,
		0x63
		},
		{
		0x010C,
		0x43
		},
		{
		0x010D,
		0x63
		},
		{
		0x010E,
		0x44
		},
		{
		0x010F,
		0x64
		},
		{
		0x0110,
		0x44
		},
		{
		0x0111,
		0x64
		},
		{
		0x0112,
		0x45
		},
		{
		0x0113,
		0x65
		},
		{
		0x0114,
		0x45
		},
		{
		0x0115,
		0x65
		},
		{
		0x0116,
		0x45
		},
		{
		0x0117,
		0x65
		},
		/////////////////
		///////////////// E with ogonek
	    {
		0x0118,
		0x45  
		},
		/////////////////
		///////////////// e with ogonek
	    {
		0x0119,
		0x65  
		},
		{
		0x011A,
		0x45
		},
		{
		0x011B,
		0x65
		},
		{
		0x011C,
		0x47
		},
		{
		0x011D,
		0x67
		},
		/////////////////
		///////////////// Turkish G with breve
	    {
		0x011E,
		0x47  
		},
		/////////////////
		///////////////// Turkish g with breve
	    {
		0x011F,
		0x67  
		},
		{
		0x0120,
		0x47
		},
		{
		0x0121,
		0x67
		},
		{
		0x0122,
		0x47
		},
		{
		0x0123,
		0x67
		},
		{
		0x0124,
		0x48
		},
		{
		0x0125,	
		0x68
		},
		{
		0x0126,	
		0x48
		},
		{
		0x0127,	
		0x68
		},
		{
		0x0128,	
		0x49
		},
		{
		0x0129,	
		0x69
		},
		{
		0x012A,	
		0x49
		},
		{
		0x012B,	
		0x69
		},
		{
		0x012C,	
		0x49
		},
		{
		0x012D,	
		0x69
		},
		{
		0x012E,
		0x49
		},
		{
		0x012F,	
		0x69
		},
		/////////////////
		///////////////// Turkish I with dot above
	    {
		0x0130,
		0x49  
		},
		/////////////////
		///////////////// Turkish dotless i
	    {
		0x0131,
		0x69  
		},
		{
		0x0134,
		0x4A
		},
		{
		0x0135,
		0x6A
		},
		{
		0x0136,
		0x4B
		},
		{
		0x0137,
		0x6B
		},
		{
		0x0139,
		0x4C
		},
		{
		0x013A,
		0x6C
		},
		{
		0x013B,
		0x4C
		},
		{
		0x013C,
		0x6C
		},
		{
		0x013D,
		0x4C
		},
		{
		0x013E,
		0x6C
		},
		{
		0x013F,
		0x4C
		},
		{
		0x0140,
		0x6C
		},
		/////////////////
		///////////////// L with stroke
	    {
		0x0141,
		0x4c  
		},
		/////////////////
		///////////////// l with stroke
	    {
		0x0142,
		0x6c 
		},
		/////////////////
		/////////////////POL N with acute
	    {
		0x0143,
		0x4E  
		},
		/////////////////
		/////////////////POL n with acute
	    {
		0x0144,
		0x6e  
		},
		{
		0x0145,
		0x4E
		},
		{
		0x0146,
		0x6E
		},
		{
		0x0147,
		0x4E
		},
		{
		0x0148,
		0x6E
		},
		{
		0x014C,
		0x4F
		},
		{
		0x014D,
		0x6F
		},
		{
		0x014E,
		0x4F
		},
		{
		0x014F,
		0x6F
		},
		/////////////////
		///////////////// O with double acute
	    {
		0x0150,
		0x4f  
		},
		/////////////////
		///////////////// o with double acute
	    {
		0x0151,
		0x6f  
		},
		{
		0x0154,
		0x52
		},
		{
		0x0155,
		0x72
		},
		{
		0x0156,
		0x52
		},
		{
		0x0157,
		0x72
		},
		{
		0x0158,
		0x52
		},
		{
		0x0159,
		0x72
		},
		/////////////////
		///////////////// S with acute
	    {
		0x015a,
		0x53  
		},
		/////////////////
		///////////////// s with acute
	    {
		0x015b,
		0x73  
		},
		{
		0x015C,
		0x53
		},
		{
		0x015D,
		0x73  
		},
		/////////////////
		///////////////// Turkish S with cedilla
	    {
		0x015E,
		0x53  
		},
		/////////////////
		///////////////// Turkish s with cedilla
	    {
		0x015F,
		0x73  
		},
		/////////////////	
		///////////////// S with caron
	    {
		0x0160,
		0x53  
		},
		/////////////////
		///////////////// s with caron
	    {
		0x0161,
		0x73  
		},
		{
		0x0162,
		0x54
		},
		{
		0x0163,
		0x74
		},
		{
		0x0164,
		0x54
		},
		{
		0x0165,
		0x74
		},
		{
		0x0166,
		0x54
		},
		{
		0x0167,
		0x74
		},
		{
		0x0168,
		0x55
		},
		{
		0x0169,
		0x75
		},
		{
		0x016A,
		0x55
		},
		{
		0x016B,
		0x75
		},
		{
		0x016C,
		0x55
		},
		{
		0x016D,
		0x75
		},
		{
		0x016E,
		0x55
		},
		{
		0x016F,
		0x75
		},
		/////////////////
		/////////////////Hungarian U with double acute
	    {
		0x0170,
		0x55  
		},
		/////////////////
		/////////////////Hungarian u with double acute
	    {
		0x0171,
		0x75  
		},
		{
		0x0172,
		0x55
		},
		{
		0x0173,
		0x75  
		},
		/////////////////
		/////////////////POL Z with acute
	    {
		0x0179,
		0x5a  
		},
		/////////////////
		/////////////////POL z with acute
	    {
		0x017a,
		0x7a  
		},
		/////////////////
		/////////////////POL Z with dot above
	    {
		0x017b,
		0x5a  
		},
		/////////////////
		/////////////////POL z with dot above
	    {
		0x017c,
		0x7a  
		},
		/////////////////
		///////////////// Z with caron
	    {
		0x017d,
		0x5a  
		},
		/////////////////
		///////////////// z with caron
	    {
		0x017e,
		0x7a  
		},
		/////////////////
		{
		0x0386,
		0x41
		},
		{
		0x0388,
		0x45
		},
		{
		0x0389,
		0x48
		},
		{
		0x038a,
		0x49
		},
		{
		0x038c,
		0x4f
		},
		{
		0x038e,
		0x59
		},
		{
		0x038f,
		0x15
		},
		{
		0x0390,
		0x49
		},
		{
		0x0391,
		0x41
		},
		{
		0x0392,
		0x42
		},
		{
		0x0395,
		0x45
		},
		{
		0x0396,
		0x5A
		},
		{
		0x0397,
		0x48
		},
		{
		0x0399,
		0x49
		},
		{
		0x039A,
		0x4B
		},
		{
		0x039C,
		0x4D
		},
		{
		0x039D,
		0x4E
		},
		{
		0x039F,
		0x4F
		},
		{
		0x03a0,
		0x16
		},
		{
		0x03a1,
		0x50
		},
		{
		0x03A4,
		0x54
		},
		{
		0x03A5,
		0x59
		},
		{
		0x03A7,
		0x58
		},
		{
		0x03AA,
		0x49
		},
		{
		0x03AB,
		0x59
		},
		{
		0x03AC,
		0x41
		},
		{
		0x03AD,
		0x45
		},
		{
		0x03AE,
		0x48
		},
		{
		0x03AF,
		0x49
		},
		{
		0x03B0,
		0x59
		},
		{
		0x03B1,
		0x41
		},
		{
		0x03B2,
		0x42
		},
		{
		0x03B3,
		0x13
		},
		{
		0x03B4,
		0x10
		},
		{
		0x03B5,
		0x45
		},
		{
		0x03B6,
		0x5A
		},
		{
		0x03B7,
		0x48
		},
		{
		0x03B8,
		0x19
		},
		{
		0x03B9,
		0x49
		},
		{
		0x03BA,
		0x4B
		},
		{
		0x03BB,
		0x14
		},
		{
		0x03BC,
		0x4D
		},
		{
		0x03BD,
		0x4E
		},
		{
		0x03BE,
		0x1A
		},
		{
		0x03BF,
		0x4F
		},
		{
		0x03C0,
		0x16
		},
		{
		0x03C1,
		0x50
		},
		{
		0x03C2,
		0x18
		},
		{
		0x03C3,
		0x18
		},
		{
		0x03C4,
		0x54
		},
		{
		0x03C5,
		0x59
		},
		{
		0x03C6,
		0x12
		},
		{
		0x03C7,
		0x58
		},
		{
		0x03C8,
		0x17
		},
		{
		0x03C9,
		0x15
		},
		{
		0x03CA,
		0x49
		},
		{
		0x03CB,
		0x59
		},
		{
		0x03CC,
		0x4F
		},
		{
		0x03CD,
		0x59
		},
		{
		0x03CE,
		0x15
		},
		{
		0x2126,
		0x15
		},
		{
		0x220f,
		0x16
		},
		{
		0x2211,
		0x18
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry keyedTable1616_unicodeToSms7Bit_2[]=
	{
		{
		0x000c,
		0x1b0a
		},
		{
		0x005b,
		0x1b3c
		},
		{
		0x005c,
		0x1b2f
		},
		{
		0x005d,
		0x1b3e
		},
		{
		0x005e,
		0x1b14
		},
		{
		0x007b,
		0x1b28
		},
		{
		0x007c,
		0x1b40
		},
		{
		0x007d,
		0x1b29
		},
		{
		0x007e,
		0x1b3d
		},
		{
		0x20ac,
		0x1b65
		}
	};

LOCAL_D const SCnvConversionData::SVariableByteData::SRange sms7BitVariableByteDataRanges[]=
	{
		{
		0x00,
		0x1a,
		0,
		0
		},
		{
		0x1b,
		0x1b,
		1,
		0
		},
		{
		0x1c,
		0xff,
		0,
		0
		}
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange sms7BitToUnicodeDataRanges[]=
	{
		{
		0x25,
		0x3f,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		0,
		0,
			{
			0,
			0
			}
		},
		{
		0x41,
		0x5a,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		0,
		0,
			{
			0,
			0
			}
		},
		{
		0x61,
		0x7a,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		0,
		0,
			{
			0,
			0
			}
		},
		{
		0x40,
		0x40,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			STATIC_CAST(TUint, 97),
			0
			}
		},
		{
		0x00,
		0x7f,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable16OfIndexedTables16,
		0,
		0,
			{
			UData_SKeyedTable16OfIndexedTables16(keyedTables16OfIndexedTables16_keyedEntries_sms7BitToUnicode_1)
			}
		},
#if 0
		{
		0x1b0a,
		0x1b65,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		0,
		0,
			{
			UData_KeyedTable(keyedTable1616_sms7BitToUnicode_1)
			}
		}
#else
		{
		0x1b41,
		0x1b5a,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			(TUint)-0x1b00,
			0
			}
		},
		{
		0x1b66,
		0x1b7a,
		SCnvConversionData::SOneDirectionData::SRange::EOffset,
		0,
		0,
			{
			(TUint)-0x1b00,
			0
			}
		},
		{
		0x1b00,
		0x1b7f,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable16OfIndexedTables16,
		0,
		0,
			{
			UData_SKeyedTable16OfIndexedTables16(keyedTables16OfIndexedTables16_keyedEntries_sms7BitToUnicode_2)
			}
		}
#endif
	};

LOCAL_D const SCnvConversionData::SOneDirectionData::SRange unicodeToSms7BitDataRanges[]=
	{
		{
		0x0025,
		0x003f,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		1,
		0,
			{
			0,
			0
			}
		},
		{
		0x0041,
		0x005a,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		1,
		0,
			{
			0,
			0
			}
		},
		{
		0x0061,
		0x007a,
		SCnvConversionData::SOneDirectionData::SRange::EDirect,
		1,
		0,
			{
			0,
			0
			}
		},
		{
		0x00bf,
		0x03d5,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable16OfIndexedTables16,
		1,
		0,
			{
			UData_SKeyedTable16OfIndexedTables16(keyedTables16OfIndexedTables16_keyedEntries_unicodeToSms7Bit_1)
			}
		},
		{
		0x000a,
		0x2211,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		1,
		0,
			{
			UData_SKeyedTable1616(keyedTable1616_unicodeToSms7Bit_1)
			}
		},
		{
		0x000c,
		0x20ac,
		SCnvConversionData::SOneDirectionData::SRange::EKeyedTable1616,
		2,
		0,
			{
			UData_SKeyedTable1616(keyedTable1616_unicodeToSms7Bit_2)
			}
		}
	};

GLREF_D const SCnvConversionData sms7BitConversionData=
	{
	SCnvConversionData::EFixedBigEndian,
		{
		ARRAY_LENGTH(sms7BitVariableByteDataRanges),
		sms7BitVariableByteDataRanges
		},
		{
		ARRAY_LENGTH(sms7BitToUnicodeDataRanges),
		sms7BitToUnicodeDataRanges
		},
		{
		ARRAY_LENGTH(unicodeToSms7BitDataRanges),
		unicodeToSms7BitDataRanges
		},
	NULL,
	NULL
	};

GLREF_C void IsCharacterSetSMS7Bit(TInt& aConfidenceLevel, const TDesC8& aSample)
	{
	_LIT8(KHz1Esc,"\x7e\x7e");
	_LIT8(KHz2Esc,"\x7e\x7b");
	_LIT8(KHz3Esc,"\x7e\x7d");
	_LIT8(KLit8EscapeSequenceForJisRoman, "\x1b\x28\x4a");
	_LIT8(KLit8EscapeSequenceForAscii, "\x1b\x28\x42");
//	_LIT8(KLit8EscapeSequenceForHalfWidthKatakana, "\x1b\x28\x49");
	_LIT8(KLit8EscapeSequenceForJisC6226_1978, "\x1b\x24\x40");
	_LIT8(KLit8EscapeSequenceForJisX0208_1983, "\x1b\x24\x42");
	_LIT8(KLit8EscapeSequenceForJisX0208_199x, "\x1b\x26\x40\x1b\x24\x42");
	_LIT8(KLit8EscapeSequenceForJisX0212_1990, "\x1b\x24\x28\x44");

	TInt hz1Result=0;
	TInt hz2Result=0;
	TInt hz3Result=0;
	TInt JisRomanResult = 0;
	TInt AsciiResult = 0;
	TInt JisCResult = 0;
	TInt JisX0208Result = 0;
	TInt JisX0212Result = 0;
	TInt JisX0208XResult = 0;

	TInt sampleLength = aSample.Length();
	aConfidenceLevel =70;
	if (sampleLength == 0)
		return;

	TInt HzEscSequences = 0;
	TInt JISEscSequences = 0;

	for (TInt i = 0; i < sampleLength; ++i)
		{

		if (i > hz1Result)
			{
			hz1Result=(aSample.Right(sampleLength-i)).Find(KHz1Esc);
			if (hz1Result!=KErrNotFound) //aConfidenceLevel-=2;
				HzEscSequences += 5;
			}

		if (i > hz2Result)
			{
			hz2Result=(aSample.Right(sampleLength-i)).Find(KHz2Esc);
			if (hz2Result!=KErrNotFound) //aConfidenceLevel-=2;
				HzEscSequences += 5;
			}

		if (i > hz3Result)
			{
			hz3Result=(aSample.Right(sampleLength-i)).Find(KHz3Esc);
			if (hz3Result!=KErrNotFound) //aConfidenceLevel-=2;
				HzEscSequences += 5;
			}

		if (i > JisRomanResult)
			{
			JisRomanResult = (aSample.Right(sampleLength-i)).Find(KLit8EscapeSequenceForJisRoman);
			if (JisRomanResult!=KErrNotFound)
				JISEscSequences +=10;
			}

		if (i > AsciiResult)
			{
			AsciiResult = (aSample.Right(sampleLength-i)).Find(KLit8EscapeSequenceForAscii);
			if (AsciiResult!=KErrNotFound)
				JISEscSequences +=10;
			}

		if (i > JisCResult)
			{
			JisCResult = (aSample.Right(sampleLength-i)).Find(KLit8EscapeSequenceForJisC6226_1978);
			if (JisCResult!=KErrNotFound)
				JISEscSequences +=5;
			}

		if (i > JisX0208Result)
			{
			JisX0208Result = (aSample.Right(sampleLength-i)).Find(KLit8EscapeSequenceForJisX0208_1983);
			if (JisX0208Result!=KErrNotFound)
				JISEscSequences +=5;
			}

		if (i > JisX0212Result)
			{
			JisX0212Result = (aSample.Right(sampleLength-i)).Find(KLit8EscapeSequenceForJisX0212_1990);
			if (JisX0212Result!=KErrNotFound)
				JISEscSequences +=5;
			}

		if (i > JisX0208XResult)
			{
			JisX0208XResult = (aSample.Right(sampleLength-i)).Find(KLit8EscapeSequenceForJisX0208_199x);
			if (JisX0208XResult!=KErrNotFound)
				JISEscSequences +=5;
			}

		if ((aSample[i]&0x80)!=0x00)
			{
			aConfidenceLevel = 0;
			break;
			}
		else
			{
			TInt increment1 = i+1;
			if (aSample[i] == 0x1b)
				{
				static const TInt defaultExtensionTable[10] = 
					{0x0a, 0x14, 0x1b, 0x29, 0x2f, 0x3c, 0x3d, 0x3e, 0x40, 0x65};
				if (increment1 >= sampleLength)
					break;
				for (TInt j =0; j < 10; j++)
					{
					if (aSample[increment1] == defaultExtensionTable[j])
						{
						aConfidenceLevel+=5;
						break;
						}
					}
				}
			else if ((aSample[i]==0x01)||(aSample[i]==0x02)||(aSample[i]==0x03))
				{
				if (increment1 >= sampleLength)
					break;
				if ((aSample[increment1] >= 0x30) && (aSample[increment1] <= 0x39))
					{
					aConfidenceLevel+=5; 
					}
				}
			//next test the occurance of values 00-2f (except 0a & 0d) next to another character
			// These are the ASCII control codes and therefore low chances of these values occuring
			// next to the ASCII value
			else if ((aSample[i] < 0x20) && 
			   ((aSample[i] != 0x0a)||(aSample[i] != 0x0d)))
				{
				if (increment1 >= sampleLength)
					break;
				if (((aSample[increment1] >= 0x20) && (aSample[increment1] <= 0x5a)) ||
					((aSample[increment1] >= 0x61) && (aSample[increment1] <= 0x7a)))	
					{
					aConfidenceLevel+=2;
					}
				}
			// other possible tests to include... Greek matching...
			}
		} // for loop
	aConfidenceLevel = aConfidenceLevel - ((HzEscSequences*100)/sampleLength);
	aConfidenceLevel = aConfidenceLevel - ((JISEscSequences*100)/sampleLength);
	aConfidenceLevel =(aConfidenceLevel >0)? ((aConfidenceLevel > 100)? 100: aConfidenceLevel): 0;
	}

