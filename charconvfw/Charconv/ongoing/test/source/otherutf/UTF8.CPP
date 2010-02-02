/*
* Copyright (c) 2000-2005 Nokia Corporation and/or its subsidiary(-ies). 
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
/* ================================================================ */
/*
File:	ConvertUTF.C
Author: Mark E. Davis
Copyright (C) 1994 Taligent, Inc. All rights reserved.

This code is copyrighted. Under the copyright laws, this code may not
be copied, in whole or part, without prior written consent of Taligent. 

Taligent grants the right to use or reprint this code as long as this
ENTIRE copyright notice is reproduced in the code or reproduction.
The code is provided AS-IS, AND TALIGENT DISCLAIMS ALL WARRANTIES,
EITHER EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  IN
NO EVENT WILL TALIGENT BE LIABLE FOR ANY DAMAGES WHATSOEVER (INCLUDING,
WITHOUT LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS
INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY
LOSS) ARISING OUT OF THE USE OR INABILITY TO USE THIS CODE, EVEN
IF TALIGENT HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
BECAUSE SOME STATES DO NOT ALLOW THE EXCLUSION OR LIMITATION OF
LIABILITY FOR CONSEQUENTIAL OR INCIDENTAL DAMAGES, THE ABOVE
LIMITATION MAY NOT APPLY TO YOU.

RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the
government is subject to restrictions as set forth in subparagraph
(c)(l)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 252.227-7013 and FAR 52.227-19.

This code may be protected by one or more U.S. and International
Patents.

TRADEMARKS: Taligent and the Taligent Design Mark are registered
trademarks of Taligent, Inc.
*/
/* ================================================================ */

// #include "CVTUTF.H" // commented out by DPB
#include "UTF8.H" // added by DPB

/* ================================================================ */

const int halfShift				= 10;
const UCS4 halfBase				= 0x0010000UL;
const UCS4 halfMask				= 0x3FFUL;
const UCS4 kSurrogateHighStart	= 0xD800UL;
const UCS4 kSurrogateHighEnd	= 0xDBFFUL;
const UCS4 kSurrogateLowStart	= 0xDC00UL;
const UCS4 kSurrogateLowEnd		= 0xDFFFUL;

/* ================================================================ */

EXPORT_C // added by DPB
ConversionResult	ConvertUCS4toUTF16 (
		UCS4** sourceStart, const UCS4* sourceEnd, 
		UTF16** targetStart, const UTF16* targetEnd) {
	ConversionResult result = ok;
	register UCS4* source = *sourceStart;
	register UTF16* target = *targetStart;
	while (source < sourceEnd) {
		register UCS4 ch;
		if (target >= targetEnd) {
			result = targetExhausted; break;
		};
		ch = *source++;
		if (ch <= kMaximumUCS2) {
			*target++ = (UTF16)ch; // cast added by DPB
		} else if (ch > kMaximumUTF16) {
			*target++ = kReplacementCharacter;
		} else {
			if (target + 1 >= targetEnd) {
				result = targetExhausted; break;
			};
			ch -= halfBase;
			*target++ = (UTF16)((ch >> halfShift) + kSurrogateHighStart); // cast added by DPB
			*target++ = (UTF16)((ch & halfMask) + kSurrogateLowStart); // cast added by DPB
		};
	};
	*sourceStart = source;
	*targetStart = target;
	return result;
};

/* ================================================================ */

EXPORT_C // added by DPB
ConversionResult	ConvertUTF16toUCS4 (
		UTF16** sourceStart, UTF16* sourceEnd, 
		UCS4** targetStart, const UCS4* targetEnd) {
	ConversionResult result = ok;
	register UTF16* source = *sourceStart;
	register UCS4* target = *targetStart;
	while (source < sourceEnd) {
		register UCS4 ch;
		ch = *source++;
		if (ch >= kSurrogateHighStart && ch <= kSurrogateHighEnd && source < sourceEnd) {
			register UCS4 ch2 = *source;
			if (ch2 >= kSurrogateLowStart && ch2 <= kSurrogateLowEnd) {
				ch = ((ch - kSurrogateHighStart) << halfShift)
					+ (ch2 - kSurrogateLowStart) + halfBase;
				++source;
			};
		};
		if (target >= targetEnd) {
			result = targetExhausted; break;
		};
		*target++ = ch;
	};
	*sourceStart = source;
	*targetStart = target;
	return result;
};

/* ================================================================ */

const UCS4 offsetsFromUTF8[6] =	{0x00000000UL, 0x00003080UL, 0x000E2080UL, // "const" added by DPB
					 	 	 0x03C82080UL, 0xFA082080UL, 0x82082080UL};
const char bytesFromUTF8[256] = { // "const" added by DPB
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5};

const UTF8 firstByteMark[7] = {0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC}; // "const" added by DPB

/* ================================================================ */
/*	This code is similar in effect to making successive calls on the
mbtowc and wctomb routines in FSS-UTF. However, it is considerably
different in code:
* it is adapted to be consistent with UTF16,
* the interface converts a whole buffer to avoid function-call overhead
* constants have been gathered.
* loops & conditionals have been removed as much as possible for
efficiency, in favor of drop-through switch statements.
*/

/* ================================================================ */
EXPORT_C // added by DPB
ConversionResult	ConvertUTF16toUTF8 (
		UTF16** sourceStart, const UTF16* sourceEnd, 
		UTF8** targetStart, const UTF8* targetEnd)
{
	ConversionResult result = ok;
	register UTF16* source = *sourceStart;
	register UTF8* target = *targetStart;
	while (source < sourceEnd) {
		register UCS4 ch;
		register unsigned short bytesToWrite = 0;
		register const UCS4 byteMask = 0xBF;
		register const UCS4 byteMark = 0x80; 
		ch = *source++;
		if (ch >= kSurrogateHighStart && ch <= kSurrogateHighEnd
				&& source < sourceEnd) {
			register UCS4 ch2 = *source;
			if (ch2 >= kSurrogateLowStart && ch2 <= kSurrogateLowEnd) {
				ch = ((ch - kSurrogateHighStart) << halfShift)
					+ (ch2 - kSurrogateLowStart) + halfBase;
				++source;
			};
		};
		if (ch < 0x80) {				bytesToWrite = 1;
		} else if (ch < 0x800) {		bytesToWrite = 2;
		} else if (ch < 0x10000) {		bytesToWrite = 3;
		} else if (ch < 0x200000) {		bytesToWrite = 4;
		} else if (ch < 0x4000000) {	bytesToWrite = 5;
		} else if (ch <= kMaximumUCS4){	bytesToWrite = 6;
		} else {						bytesToWrite = 2;
										ch = kReplacementCharacter;
		}; /* I wish there were a smart way to avoid this conditional */
		
		target += bytesToWrite;
		if (target > targetEnd) {
			target -= bytesToWrite; result = targetExhausted; break;
		};
		switch (bytesToWrite) {	/* note: code falls through cases! */
			case 6:	*--target = (UTF8)((ch | byteMark) & byteMask); ch >>= 6; // cast added by DPB
			case 5:	*--target = (UTF8)((ch | byteMark) & byteMask); ch >>= 6; // cast added by DPB
			case 4:	*--target = (UTF8)((ch | byteMark) & byteMask); ch >>= 6; // cast added by DPB
			case 3:	*--target = (UTF8)((ch | byteMark) & byteMask); ch >>= 6; // cast added by DPB
			case 2:	*--target = (UTF8)((ch | byteMark) & byteMask); ch >>= 6; // cast added by DPB
			case 1:	*--target = (UTF8)(ch | firstByteMark[bytesToWrite]); // cast added by DPB
		};
		target += bytesToWrite;
	};
	*sourceStart = source;
	*targetStart = target;
	return result;
};

/* ================================================================ */

EXPORT_C // added by DPB
ConversionResult	ConvertUTF8toUTF16 (
		UTF8** sourceStart, UTF8* sourceEnd, 
		UTF16** targetStart, const UTF16* targetEnd)
{
	ConversionResult result = ok;
	register UTF8* source = *sourceStart;
	register UTF16* target = *targetStart;
	while (source < sourceEnd) {
		register UCS4 ch = 0;
		register unsigned short extraBytesToWrite = bytesFromUTF8[*source];
		if (source + extraBytesToWrite > sourceEnd) {
			result = sourceExhausted; break;
		};
		switch(extraBytesToWrite) {	/* note: code falls through cases! */
			case 5:	ch += *source++; ch <<= 6;
			case 4:	ch += *source++; ch <<= 6;
			case 3:	ch += *source++; ch <<= 6;
			case 2:	ch += *source++; ch <<= 6;
			case 1:	ch += *source++; ch <<= 6;
			case 0:	ch += *source++;
		};
		ch -= offsetsFromUTF8[extraBytesToWrite];

		if (target >= targetEnd) {
			result = targetExhausted; break;
		};
		if (ch <= kMaximumUCS2) {
			*target++ = (UTF16)ch;
		} else if (ch > kMaximumUTF16) {
			*target++ = kReplacementCharacter;
		} else {
			if (target + 1 >= targetEnd) {
				result = targetExhausted; break;
			};
			ch -= halfBase;
			*target++ = (UTF16)((ch >> halfShift) + kSurrogateHighStart);
			*target++ = (UTF16)((ch & halfMask) + kSurrogateLowStart);
		};
	};
	*sourceStart = source;
	*targetStart = target;
	return result;
};

/* ================================================================ */
EXPORT_C // added by DPB
ConversionResult	ConvertUCS4toUTF8 (
		UCS4** sourceStart, const UCS4* sourceEnd, 
		UTF8** targetStart, const UTF8* targetEnd)
{
	ConversionResult result = ok;
	register UCS4* source = *sourceStart;
	register UTF8* target = *targetStart;
	while (source < sourceEnd) {
		register UCS4 ch;
		register unsigned short bytesToWrite = 0;
		register const UCS4 byteMask = 0xBF;
		register const UCS4 byteMark = 0x80; 
		ch = *source++;
		if (ch >= kSurrogateHighStart && ch <= kSurrogateHighEnd
				&& source < sourceEnd) {
			register UCS4 ch2 = *source;
			if (ch2 >= kSurrogateLowStart && ch2 <= kSurrogateLowEnd) {
				ch = ((ch - kSurrogateHighStart) << halfShift)
					+ (ch2 - kSurrogateLowStart) + halfBase;
				++source;
			};
		};
		if (ch < 0x80) {				bytesToWrite = 1;
		} else if (ch < 0x800) {		bytesToWrite = 2;
		} else if (ch < 0x10000) {		bytesToWrite = 3;
		} else if (ch < 0x200000) {		bytesToWrite = 4;
		} else if (ch < 0x4000000) {	bytesToWrite = 5;
		} else if (ch <= kMaximumUCS4){	bytesToWrite = 6;
		} else {						bytesToWrite = 2;
										ch = kReplacementCharacter;
		}; /* I wish there were a smart way to avoid this conditional */
		
		target += bytesToWrite;
		if (target > targetEnd) {
			target -= bytesToWrite; result = targetExhausted; break;
		};
		switch (bytesToWrite) {	/* note: code falls through cases! */
			case 6:	*--target = (UTF8)((ch | byteMark) & byteMask); ch >>= 6; // cast added by DPB
			case 5:	*--target = (UTF8)((ch | byteMark) & byteMask); ch >>= 6; // cast added by DPB
			case 4:	*--target = (UTF8)((ch | byteMark) & byteMask); ch >>= 6; // cast added by DPB
			case 3:	*--target = (UTF8)((ch | byteMark) & byteMask); ch >>= 6; // cast added by DPB
			case 2:	*--target = (UTF8)((ch | byteMark) & byteMask); ch >>= 6; // cast added by DPB
			case 1:	*--target = (UTF8)(ch | firstByteMark[bytesToWrite]); // cast added by DPB
		};
		target += bytesToWrite;
	};
	*sourceStart = source;
	*targetStart = target;
	return result;
};

/* ================================================================ */

EXPORT_C // added by DPB
ConversionResult	ConvertUTF8toUCS4 (
		UTF8** sourceStart, UTF8* sourceEnd, 
		UCS4** targetStart, const UCS4* targetEnd)
{
	ConversionResult result = ok;
	register UTF8* source = *sourceStart;
	register UCS4* target = *targetStart;
	while (source < sourceEnd) {
		register UCS4 ch = 0;
		register unsigned short extraBytesToWrite = bytesFromUTF8[*source];
		if (source + extraBytesToWrite > sourceEnd) {
			result = sourceExhausted; break;
		};
		switch(extraBytesToWrite) {	/* note: code falls through cases! */
			case 5:	ch += *source++; ch <<= 6;
			case 4:	ch += *source++; ch <<= 6;
			case 3:	ch += *source++; ch <<= 6;
			case 2:	ch += *source++; ch <<= 6;
			case 1:	ch += *source++; ch <<= 6;
			case 0:	ch += *source++;
		};
		ch -= offsetsFromUTF8[extraBytesToWrite];

		if (target >= targetEnd) {
			result = targetExhausted; break;
		};
		if (ch <= kMaximumUCS2) {
			*target++ = ch;
		} else if (ch > kMaximumUCS4) {
			*target++ = kReplacementCharacter;
		} else {
			if (target + 1 >= targetEnd) {
				result = targetExhausted; break;
			};
			ch -= halfBase;
			*target++ = (ch >> halfShift) + kSurrogateHighStart;
			*target++ = (ch & halfMask) + kSurrogateLowStart;
		};
	};
	*sourceStart = source;
	*targetStart = target;
	return result;
};
