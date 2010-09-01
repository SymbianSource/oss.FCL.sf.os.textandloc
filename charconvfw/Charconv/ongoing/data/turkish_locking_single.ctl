# turkish_locking_single.ctl
#
# Copyright (c) 1997-2000 Nokia Corporation and/or its subsidiary(-ies).
# All rights reserved.
# This component and the accompanying materials are made available
# under the terms of the License "Eclipse Public License v1.0"
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

Endianness															FixedBigEndian
ReplacementForUnconvertibleUnicodeCharacters						0x3f

StartForeignVariableByteData
#	FirstInitialByteValueInRange	LastInitialByteValueInRange		NumberOfSubsequentBytes
	0x00							0x1a							0
	0x1b							0x1b							1
    0x1c							0xff							0
EndForeignVariableByteData

StartForeignToUnicodeData
#	IncludePriority	SearchPriority	FirstInputCharacterCodeInRange	LastInputCharacterCodeInRange	Algorithm						Parameters
	21				19				0x25							0x3f							Direct							{}		# ASCII
	20				18				0x41							0x5a							Direct							{}		# ASCII
	19				17				0x61							0x7a							Direct							{}		# ASCII
	18				16				0x40							0x40							Offset							{}		# 
	1				100				0x00							0x7f							KeyedTable16OfIndexedTables16	{5}
	17				15				0x1b30							0x1b3b							Offset							{}		# 
	16				14				0x1b41							0x1b46							Offset							{}		# 
	15				13				0x1b47							0x1b47							Offset							{}		# 
	14				12				0x1b48							0x1b48							Offset							{}		# 
	13				11				0x1b49							0x1b49							Offset							{}		# 
	12				10				0x1b4a							0x1b52							Offset							{}		# 
	11				9				0x1b53							0x1b53							Offset							{}		# 
	10				8				0x1b54							0x1b5a							Offset							{}		# 
	9				7				0x1b6a							0x1b72							Offset							{}		# 
	8				6				0x1b73							0x1b73							Offset							{}		# 
	7				5				0x1b74							0x1b7a							Offset							{}		# 
	2				200				0x1b00							0x1b7f							KeyedTable16OfIndexedTables16	{5}

ConflictResolution
#	ForeignCharacterCodeToResolve	UnicodeCharacterCodePreferred
0x0B	0x011E	#	LATIN CAPITAL LETTER G WITH BREVE
0x0C	0x011F	#	LATIN SMALL LETTER G WITH BREVE
0x10	0x0394		
0x12	0x03A6		
0x13	0x0393		
0x14	0x039B		
0x15	0x03A9		
0x16	0x03A0		
0x17	0x03A8		
0x18	0x03A3		
0x19	0x0398		
0x1A	0x039E		
0x41	0x0041	#	LATIN CAPITAL LETTER A
0x42	0x0042	#	LATIN CAPITAL LETTER B
0x45	0x0045	#	LATIN CAPITAL LETTER E
0x48	0x0048	#	LATIN CAPITAL LETTER H
0x49	0x0049	#	LATIN CAPITAL LETTER I
0x4B	0x004B	#	LATIN CAPITAL LETTER K
0x4D	0x004D	#	LATIN CAPITAL LETTER M
0x4E	0x004E	#	LATIN CAPITAL LETTER N
0x4F	0x004F	#	LATIN CAPITAL LETTER O
0x50	0x0050	#	LATIN CAPITAL LETTER P
0x54	0x0054	#	LATIN CAPITAL LETTER T
0x55	0x0055	#	LATIN CAPITAL LETTER U
0x58	0x0058	#	LATIN CAPITAL LETTER X
0x59	0x0059	#	LATIN CAPITAL LETTER Y
0x5A	0x005A	#	LATIN CAPITAL LETTER Z
0x61	0x0061	#	LATIN SMALL LETTER A
0x65	0x0065	#	LATIN SMALL LETTER E
0x69	0x0069	#	LATIN SMALL LETTER I
0x6F	0x006F	#	LATIN SMALL LETTER O
0x75	0x0075	#	LATIN SMALL LETTER U
0x79	0x0079	#	LATIN SMALL LETTER Y
	
EndForeignToUnicodeData

StartUnicodeToForeignData
#	IncludePriority	SearchPriority	FirstInputCharacterCodeInRange	LastInputCharacterCodeInRange	Algorithm						SizeOfOutputCharacterCodeInBytes	Parameters
	21				20				0x0025							0x003f							Direct							1									{}		# ASCII
	20				19				0x0041							0x005a							Direct							1									{}		# ASCII
	19				18				0x0061							0x007a							Direct							1									{}		# ASCII
	18				17				0x000c							0x000c							Offset							2									{}
	17				16				0x005b							0x005e							KeyedTable16OfIndexedTables16	2									{4}
	16				15				0x007b							0x007e							KeyedTable16OfIndexedTables16	2									{4}
	1				100				0x000a							0x2211							KeyedTable1616					1									{}

ConflictResolution
#	UnicodeCharacterCodeToResolve	ForeignCharacterCodePreferred
0x000D	0x0D	#	CARRIAGE RETURN	
0x0020	0x20	#	SPACE	
0x0021	0x21	#	EXCLAMATION MARK	
0x0022	0x22	#	QUOTATION MARK	
0x0023	0x23	#	NUMBER SIGN	
0x0024	0x02	#	DOLLAR SIGN	
0x0025	0x25	#	PERCENT SIGN	
0x0026	0x26	#	AMPERSAND	
0x0027	0x27	#	APOSTROPHE	
0x002A	0x2A	#	ASTERISK	
0x002B	0x2B	#	PLUS SIGN	
0x002C	0x2C	#	COMMA	
0x002D	0x2D	#	HYPHEN-MINUS	
0x002E	0x2E	#	FULL STOP	
0x0030	0x30	#	DIGIT ZERO	
0x0031	0x31	#	DIGIT ONE	
0x0032	0x32	#	DIGIT TWO	
0x0033	0x33	#	DIGIT THREE	
0x0034	0x34	#	DIGIT FOUR	
0x0035	0x35	#	DIGIT FIVE	
0x0036	0x36	#	DIGIT SIX	
0x0037	0x37	#	DIGIT SEVEN	
0x0038	0x38	#	DIGIT EIGHT	
0x0039	0x39	#	DIGIT NINE	
0x003A	0x3A	#	COLON	
0x003B	0x3B	#	SEMICOLON	
0x003F	0x3F	#	QUESTION MARK	
0x0040	0x00	#	COMMERCIAL AT	
0x0041	0x41	#	LATIN CAPITAL LETTER A	
0x0042	0x42	#	LATIN CAPITAL LETTER B	
0x0043	0x43	#	LATIN CAPITAL LETTER C	
0x0044	0x44	#	LATIN CAPITAL LETTER D	
0x0045	0x45	#	LATIN CAPITAL LETTER E	
0x0046	0x46	#	LATIN CAPITAL LETTER F	
0x0048	0x48	#	LATIN CAPITAL LETTER H	
0x004A	0x4A	#	LATIN CAPITAL LETTER J	
0x004B	0x4B	#	LATIN CAPITAL LETTER K	
0x004C	0x4C	#	LATIN CAPITAL LETTER L	
0x004D	0x4D	#	LATIN CAPITAL LETTER M	
0x004E	0x4E	#	LATIN CAPITAL LETTER N	
0x004F	0x4F	#	LATIN CAPITAL LETTER O	
0x0050	0x50	#	LATIN CAPITAL LETTER P	
0x0051	0x51	#	LATIN CAPITAL LETTER Q	
0x0052	0x52	#	LATIN CAPITAL LETTER R	
0x0054	0x54	#	LATIN CAPITAL LETTER T	
0x0055	0x55	#	LATIN CAPITAL LETTER U	
0x0056	0x56	#	LATIN CAPITAL LETTER V	
0x0057	0x57	#	LATIN CAPITAL LETTER W	
0x0058	0x58	#	LATIN CAPITAL LETTER X	
0x0059	0x59	#	LATIN CAPITAL LETTER Y	
0x005A	0x5A	#	LATIN CAPITAL LETTER Z	
0x005F	0x11	#	LOW LINE	
0x0061	0x61	#	LATIN SMALL LETTER A	
0x0062	0x62	#	LATIN SMALL LETTER B	
0x0064	0x64	#	LATIN SMALL LETTER D	
0x0066	0x66	#	LATIN SMALL LETTER F	
0x0068	0x68	#	LATIN SMALL LETTER H	
0x006A	0x6A	#	LATIN SMALL LETTER J	
0x006B	0x6B	#	LATIN SMALL LETTER K	
0x006C	0x6C	#	LATIN SMALL LETTER L	
0x006D	0x6D	#	LATIN SMALL LETTER M	
0x006E	0x6E	#	LATIN SMALL LETTER N	
0x006F	0x6F	#	LATIN SMALL LETTER O	
0x0070	0x70	#	LATIN SMALL LETTER P	
0x0071	0x71	#	LATIN SMALL LETTER Q	
0x0072	0x72	#	LATIN SMALL LETTER R	
0x0074	0x74	#	LATIN SMALL LETTER T	
0x0075	0x75	#	LATIN SMALL LETTER U	
0x0076	0x76	#	LATIN SMALL LETTER V	
0x0077	0x77	#	LATIN SMALL LETTER W	
0x0078	0x78	#	LATIN SMALL LETTER X	
0x0079	0x79	#	LATIN SMALL LETTER Y	
0x007A	0x7A	#	LATIN SMALL LETTER Z	
0x00A3	0x01	#	POUND SIGN	
0x00A4	0x24	#	CURRENCY SIGN	
0x00A5	0x03	#	YEN SIGN	
0x00A7	0x5F	#	SECTION SIGN	
0x00C4	0x5B	#	LATIN CAPITAL LETTER A WITH DIAERESIS	
0x00C5	0x0E	#	LATIN CAPITAL LETTER A WITH RING ABOVE	
0x00C7	0x09	#	LATIN CAPITAL LETTER C WITH CEDILLA	
0x00C9	0x1F	#	LATIN CAPITAL LETTER E WITH ACUTE	
0x00D1	0x5D	#	LATIN CAPITAL LETTER N WITH TILDE	
0x00D6	0x5C	#	LATIN CAPITAL LETTER O WITH DIAERESIS	
0x00DC	0x5E	#	LATIN CAPITAL LETTER U WITH DIAERESIS	
0x00DF	0x1E	#	LATIN SMALL LETTER SHARP S (German)	
0x00E0	0x7F	#	LATIN SMALL LETTER A WITH GRAVE	
0x00E4	0x7B	#	LATIN SMALL LETTER A WITH DIAERESIS	
0x00E5	0x0F	#	LATIN SMALL LETTER A WITH RING ABOVE	
0x00E7	0x60	#	LATIN SMALL LETTER C WITH CEDILLA	
0x00E9	0x05	#	LATIN SMALL LETTER E WITH ACUTE	
0x00F1	0x7D	#	LATIN SMALL LETTER N WITH TILDE	
0x00F2	0x08	#	LATIN SMALL LETTER O WITH GRAVE	
0x00F6	0x7C	#	LATIN SMALL LETTER O WITH DIAERESIS	
0x00F9	0x06	#	LATIN SMALL LETTER U WITH GRAVE	
0x00FC	0x7E	#	LATIN SMALL LETTER U WITH DIAERESIS	
0x011E	0x0B	#	LATIN CAPITAL LETTER G WITH BREVE	
0x011F	0x0C	#	LATIN SMALL LETTER G WITH BREVE	
0x0130	0x40	#	LATIN CAPITAL LETTER I WITH DOT ABOVE	
0x0131	0x07	#	LATIN SMALL LETTER DOTLESS I	
0x015E	0x1C	#	LATIN CAPITAL LETTER S WITH CEDILLA *	
0x015F	0x1D	#	LATIN SMALL LETTER S WITH CEDILLA *	
0x0393	0x13	#	GREEK CAPITAL LETTER GAMMA	
0x0394	0x10	#	GREEK CAPITAL LETTER DELTA	
0x0398	0x19	#	GREEK CAPITAL LETTER THETA	
0x039E	0x1A	#	GREEK CAPITAL LETTER XI	
0x03A0	0x16	#	GREEK CAPITAL LETTER PI	
0x03A3	0x18	#	GREEK CAPITAL LETTER SIGMA	
0x03A6	0x12	#	GREEK CAPITAL LETTER PHI	
0x03A8	0x17	#	GREEK CAPITAL LETTER PSI	
0x03A9	0x15	#	GREEK CAPITAL LETTER OMEGA	
0x20AC	0x04	#	EURO SIGN	

EndUnicodeToForeignData
