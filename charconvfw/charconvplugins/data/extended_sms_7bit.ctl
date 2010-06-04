# Copyright (c) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
# All rights reserved.
# This component and the accompanying materials are made available
# under the terms of "Eclipse Public License v1.0"
# which accompanies this distribution, and is available
# at the URL "http://www.eclipse.org/legal/epl-v10.html".
#
# Initial Contributors:
# Nokia Corporation - initial contribution.
#
# Contributors:
#
# Description:
#

Endianness								FixedBigEndian
ReplacementForUnconvertibleUnicodeCharacters				0x3F

StartForeignVariableByteData
#	FirstInitialByteValueInRange	LastInitialByteValueInRange		NumberOfSubsequentBytes
	0x00				0x1A					0
	0x1B				0x1B					1
	0x1C				0xFF					0
EndForeignVariableByteData

StartForeignToUnicodeData
#			First	Last	Algorithm		Parameters
	2	2	0x0A	0x0A	Direct	{}
	2	2	0x0D	0x0D	Direct	{}
	2	2	0x20	0x23	Direct	{}
	2	2	0x25	0x3F	Direct	{}
	2	2	0x41	0x5A	Direct	{}
	2	2	0x61	0x7A	Direct	{}
	1	1	0x00	0x7F	KeyedTable16OfIndexedTables16	{1}
	2	2	0x1B20	0x1B23	Offset	{}
	2	2	0x1B25	0x1B27	Offset	{}
	2	2	0x1B2A	0x1B2E	Offset	{}
	2	2	0x1B30	0x1B3B	Offset	{}
	2	2	0x1B41	0x1B5A	Offset	{}
	2	2	0x1B61	0x1B64	Offset	{}
	2	2	0x1B66	0x1B7A	Offset	{}
	1	1	0x1B00	0x1B7F	KeyedTable16OfIndexedTables16	{1}		
ConflictResolution
#	ForeignCharacterCodeToResolve	UnicodeCharacterCodePreferred
0x0009    0x00E7
0x0010    0x0394
0x0012    0x03A6
0x0013    0x0393
0x0014    0x039B
0x0015    0x03A9
0x0016    0x03A0
0x0017    0x03A8
0x0018    0x03A3
0x0019    0x0398
0x001A    0x039E
0x0020    0x0020
0x0022    0x0022
0x0027    0x0027
0x002A    0x002A
0x002C    0x002C
0x002D    0x002D
0x002E    0x002E
0x002F    0x002F
0x0031    0x0031
0x0032    0x0032
0x0033    0x0033
0x003B    0x003B
0x0041    0x0041
0x0042    0x0042
0x0043    0x0043
0x0044    0x0044
0x0045    0x0045
0x0047    0x0047
0x0048    0x0048
0x0049    0x0049
0x004A    0x004A
0x004B    0x004B
0x004C    0x004C
0x004D    0x004D
0x004E    0x004E
0x004F    0x004F
0x0050    0x0050
0x0052    0x0052
0x0053    0x0053
0x0054    0x0054
0x0055    0x0055
0x0057    0x0057
0x0058    0x0058
0x0059    0x0059
0x005A    0x005A
0x005C    0x00D6
0x005E    0x00DC
0x0061    0x0061
0x0063    0x0063
0x0064    0x0064
0x0065    0x0065
0x0067    0x0067
0x0068    0x0068
0x0069    0x0069
0x006A    0x006A
0x006B    0x006B
0x006C    0x006C
0x006E    0x006E
0x006F    0x006F
0x0072    0x0072
0x0073    0x0073
0x0074    0x0074
0x0075    0x0075
0x0077    0x0077
0x0079    0x0079
0x007A    0x007A
0x007C    0x00F6
0x007E    0x00FC
EndForeignToUnicodeData

StartUnicodeToForeignData
#			First	Last	Algorithm	Parameters
2	2	0x0025	0x003F	Direct	1	{}
2	2	0x0041	0x005A	Direct	1	{}
2	2	0x0061	0x007A	Direct	1	{}
2	2	0x000C	0x000C	Offset	2	{}
2	2	0x005B	0x005E	IndexedTable16	2	{}
2	2	0x007B	0x007E	IndexedTable16	2	{}
2	2	0x0020	0x0023	Direct	1	{}
2	2	0x000A	0x000A	Direct	1	{}
2	2	0x000D	0x000D	Direct	1	{}
2	2	0x0024	0x0024	Offset	1	{}
2	2	0x0040	0x0040	Offset	1	{}
2	2	0x20AC	0x20AC	Offset	2	{}
1	1	0x005F	0x03CE	KeyedTable16OfIndexedTables16	1	{1}
ConflictResolution
#	UnicodeCharacterCodeToResolve	ForeignCharacterCodePreferred
0x0040	0x00
0x00A3	0x01
0x0024	0x02
0x00A5	0x03
0x00E8	0x04
0x00E9	0x05
0x00F9	0x06
0x00EC	0x07
0x00F2	0x08
0x00E7	0x09
0x00D8	0x0B
0x00F8	0x0C
0x000D	0x0D
0x00C5	0x0E
0x00E5	0x0F
0x0394	0x10
0x005F	0x11
0x03A6	0x12
0x0393	0x13
0x03A9	0x15
0x03A0	0x16
0x03A8	0x17
0x03A3	0x18
0x0398	0x19
0x039E	0x1A
0x00C6	0x1C
0x00E6	0x1D
0x00DF	0x1E
0x00C9	0x1F
0x0020	0x20
0x0021	0x21
0x0022	0x22
0x0023	0x23
0x00A4	0x24
0x0025	0x25
0x0026	0x26
0x0027	0x27
0x002A	0x2A
0x002B	0x2B
0x002C	0x2C
0x002D	0x2D
0x002E	0x2E
0x0030	0x30
0x0031	0x31
0x0032	0x32
0x0033	0x33
0x0034	0x34
0x0035	0x35
0x0036	0x36
0x0037	0x37
0x0038	0x38
0x0039	0x39
0x003A	0x3A
0x003B	0x3B
0x003F	0x3F
0x0041	0x41
0x0042	0x42
0x0043	0x43
0x0044	0x44
0x0045	0x45
0x0046	0x46
0x0047	0x47
0x0048	0x48
0x0049	0x49
0x004A	0x4A
0x004B	0x4B
0x004C	0x4C
0x004D	0x4D
0x004E	0x4E
0x004F	0x4F
0x0050	0x50
0x0051	0x51
0x0052	0x52
0x0053	0x53
0x0054	0x54
0x0055	0x55
0x0056	0x56
0x0057	0x57
0x0058	0x58
0x0059	0x59
0x005A	0x5A
0x00C4	0x5B
0x00D6	0x5C
0x00D1	0x5D
0x00DC	0x5E
0x00A7	0x5F
0x00BF	0x60
0x0061	0x61
0x0062	0x62
0x0063	0x63
0x0064	0x64
0x0066	0x66
0x0067	0x67
0x0068	0x68
0x0069	0x69
0x006A	0x6A
0x006B	0x6B
0x006C	0x6C
0x006D	0x6D
0x006E	0x6E
0x006F	0x6F
0x0070	0x70
0x0071	0x71
0x0072	0x72
0x0073	0x73
0x0074	0x74
0x0075	0x75
0x0076	0x76
0x0077	0x77
0x0078	0x78
0x0079	0x79
0x007A	0x7A
0x00E4	0x7B
0x00F6	0x7C
0x00F1	0x7D
0x00FC	0x7E
0x00E0	0x7F
EndUnicodeToForeignData
