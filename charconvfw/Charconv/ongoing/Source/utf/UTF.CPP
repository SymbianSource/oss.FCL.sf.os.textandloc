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
#include <e32base.h>
#include <utf.h>

const TUint KNotInBase64Alphabet=KMaxTUint;

enum TPanic
	{
	EPanicBad6BitNumber=1,
	EPanicBadUtf7Pointers1,
	EPanicBadUtf7Pointers2,
	EPanicBadUtf7Pointers3,
	EPanicBadUtf7Pointers4,
	EPanicBadUtf7Pointers5,
	EPanicBadUtf7Pointers6,
	EPanicBadUtf7Pointers7,
	EPanicBadUtf7Pointers8,
	EPanicBadUtf7Pointers9,
	EPanicBadUtf7Pointers10,
	EPanicBadUtf7Pointers11,
	EPanicNotInBase64Block,
	EPanicBadUnicodePointers1,
	EPanicBadUnicodePointers2,
	EPanicBadUnicodePointers3,
	EPanicBadUnicodePointers4,
	EPanicBadUnicodePointers5,
	EPanicBadUnicodePointers6,
	EPanicBadUnicodePointers7,
	EPanicBadUnicodePointers8,
	EPanicBadUnicodePointers9,
	EPanicBadUnicodePointers10,
	EPanicBadBitBufferState1,
	EPanicBadBitBufferState2,
	EPanicBadBitBufferState3,
	EPanicBadBitBufferState4,
	EPanicBadBitBufferState5,
	EPanicBadBitBufferState6,
	EPanicBadBitBufferState7,
	EPanicBadBitBufferState8,
	EPanicBadBitBufferState9,
	EPanicBadBitBufferState10,
	EPanicBadBitBufferState11,
	EPanicBadBitBufferState12,
	EPanicBadBitBufferState13,
	EPanicBadBitBufferState14,
	EPanicBadBitBufferState15,
	EPanicBadBitBufferState16,
	EPanicBadBitBufferState17,
	EPanicUnexpectedNumberOfLoopIterations,
	EPanicInitialEscapeCharacterButNoBase64,
	EPanicBase64SequenceDoesNotFallOnUnicodeCharacterBoundary,
	EPanicBadUtf8Pointers1,
	EPanicBadUtf8Pointers2,
	EPanicBadUtf8Pointers3,
	EPanicBadUtf8Pointers4,
	EPanicBadUtf8Pointers5,
	EPanicBadUtf8Pointers6,
	EPanicBadUtf8Pointers7,
	EPanicOutOfSyncUtf7Byte1,
	EPanicOutOfSyncUtf7Byte2,
	EPanicOutOfSyncBase64Decoding
	};

_LIT(KLitPanicText, "CHARCONV-UTF");

LOCAL_C void Panic(TPanic aPanic)
	{
	User::Panic(KLitPanicText, aPanic);
	}

inline TUint EscapeCharacterForStartingBase64Block(TBool aIsImapUtf7) {return aIsImapUtf7? '&': '+';}

LOCAL_C TUint Base64Decoding(TUint aMemberOfBase64Alphabet, TBool aIsImapUtf7)
	{
	if ((aMemberOfBase64Alphabet>='A') && (aMemberOfBase64Alphabet<='Z'))
		{
		return aMemberOfBase64Alphabet-'A';
		}
	if ((aMemberOfBase64Alphabet>='a') && (aMemberOfBase64Alphabet<='z'))
		{
		return aMemberOfBase64Alphabet-('a'-26);
		}
	if ((aMemberOfBase64Alphabet>='0') && (aMemberOfBase64Alphabet<='9'))
		{
		return aMemberOfBase64Alphabet+((26*2)-'0');
		}
	if (aMemberOfBase64Alphabet=='+')
		{
		return 62;
		}
	if (aMemberOfBase64Alphabet==STATIC_CAST(TUint, aIsImapUtf7? ',': '/'))
		{
		return 63;
		}
	return KNotInBase64Alphabet;
	}

LOCAL_C TUint Base64Encoding(TUint a6BitNumber, TBool aIsImapUtf7)
	{
	__ASSERT_DEBUG(a6BitNumber<64, Panic(EPanicBad6BitNumber));
	if ((a6BitNumber==63) && aIsImapUtf7)
		{
		return ',';
		}
	static const TUint8 base64Alphabet[64]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
	return base64Alphabet[a6BitNumber];
	}

LOCAL_C TUint8* PointerToEscapeCharacterStartingBase64Block(TUint8* aPointerToUtf7Byte, const TUint8* aPointerToFirstUtf7Byte, TBool aIsImapUtf7)
	{
	__ASSERT_DEBUG(aPointerToUtf7Byte>=aPointerToFirstUtf7Byte, Panic(EPanicBadUtf7Pointers1));
	TUint8* pointerToCandidateEscapeCharacter=NULL;
	FOREVER
		{
		const TUint utf7Byte=*aPointerToUtf7Byte;
		if (utf7Byte==EscapeCharacterForStartingBase64Block(aIsImapUtf7))
			{
			pointerToCandidateEscapeCharacter=aPointerToUtf7Byte;
			}
		else if (Base64Decoding(utf7Byte, aIsImapUtf7)==KNotInBase64Alphabet)
			{
			break;
			}
		__ASSERT_DEBUG(aPointerToUtf7Byte>=aPointerToFirstUtf7Byte, Panic(EPanicBadUtf7Pointers2));
		if (aPointerToUtf7Byte<=aPointerToFirstUtf7Byte)
			{
			break;
			}
		--aPointerToUtf7Byte;
		}
	__ASSERT_DEBUG(pointerToCandidateEscapeCharacter!=NULL, Panic(EPanicNotInBase64Block));
	return pointerToCandidateEscapeCharacter;
	}

LOCAL_C TBool EncodeInUtf7Directly(TUint aUnicodeCharacter, TBool aIsImapUtf7, TBool aEncodeOptionalDirectCharactersInBase64)
	{
	if (aIsImapUtf7)
		{
		return (aUnicodeCharacter>=0x0020) && (aUnicodeCharacter<=0x007e);
		}
	if ((aUnicodeCharacter>=0x0021) && (aUnicodeCharacter<=0x007d))
		{
		if (aEncodeOptionalDirectCharactersInBase64)
			{
			return (((aUnicodeCharacter>=0x0041) && (aUnicodeCharacter<=0x005a)) ||
					((aUnicodeCharacter>=0x0061) && (aUnicodeCharacter<=0x007a)) ||
					((aUnicodeCharacter>=0x0027) && (aUnicodeCharacter<=0x0029)) ||
					((aUnicodeCharacter>=0x002b) && (aUnicodeCharacter<=0x003a)) ||
					(aUnicodeCharacter==0x003f));
			}
		return aUnicodeCharacter!=0x005c;
		}
	return (aUnicodeCharacter==0x0020) || (aUnicodeCharacter==0x0009) || (aUnicodeCharacter==0x000d) || (aUnicodeCharacter==0x000a);
	}

inline TBool BitBufferContainsNonZeroBits(TUint aBitBuffer, TInt aNumberOfBitsInBuffer)
	{
	return (aBitBuffer&((1<<aNumberOfBitsInBuffer)-1))!=0;
	}



/**  Converts Unicode text into UTF-7 encoding. The fucntion leaves with 
KErrCorrupt if the input string is corrupt.

@param aUnicode A UCS-2 encoded input string.
@param aEncodeOptionalDirectCharactersInBase64  If ETrue then 
characters from UTF-7 set O (optional direct characters) are encoded in 
Modified Base64. If EFalse the characters are encoded directly, 
as their ASCII equivalents.
@return A descriptor containing the UTF-7 encoded output string. */
EXPORT_C HBufC8* CnvUtfConverter::ConvertFromUnicodeToUtf7L(
										const TDesC16& aUnicode, 
										TBool aEncodeOptionalDirectCharactersInBase64)
	{
	// If aUnicode is  Null string, return an empty HBufC
	if (aUnicode.Length() == 0)
		{
		HBufC8* hBuf8 = HBufC8::NewL(1);
		return hBuf8;
		}

	// Otherwise, convert and store result in a buffer, reallocating that buffer if needed.
	TInt length = aUnicode.Length();
	const TInt bufsize = 100;
	
	TPtrC16 unicode (aUnicode);
	TBuf8<bufsize> buf;
	HBufC8* hBuf8 = HBufC8::NewLC(length);
	TPtr8 utf7 = hBuf8->Des();

	FOREVER
		{
		TInt unconverted = ConvertFromUnicodeToUtf7(buf, unicode, aEncodeOptionalDirectCharactersInBase64);
		if( unconverted == EErrorIllFormedInput || unconverted < 0)
			User::Leave(KErrCorrupt);

		if (utf7.Length() + buf.Length() > utf7.MaxLength())
			{
			// Reallocate the hBuf8
			hBuf8 = hBuf8->ReAllocL(utf7.Length() + buf.Length());
			CleanupStack::Pop();
			CleanupStack::PushL(hBuf8);
			utf7.Set(hBuf8->Des());
			}
		utf7.Append(buf);
		if (unconverted ==0) 
			break;
		unicode.Set(unicode.Right(unconverted));
		}
	CleanupStack::Pop();
	return hBuf8;

	}

/** Converts Unicode text into UTF-7 encoding.

@param aUtf7 On return, contains the UTF-7 encoded output string.
@param aUnicode A UCS-2 encoded input string.
@param aEncodeOptionalDirectCharactersInBase64 If ETrue then characters from 
UTF-7 set O (optional direct characters) are encoded in Modified Base64. If 
EFalse the characters are encoded directly, as their ASCII equivalents.
@return The number of unconverted characters left at the end of the input 
descriptor, or one of the error values defined in TError. */
EXPORT_C TInt CnvUtfConverter::ConvertFromUnicodeToUtf7(
										TDes8& aUtf7, 
										const TDesC16& aUnicode, 
										TBool aEncodeOptionalDirectCharactersInBase64)
	{
	return ConvertFromUnicodeToUtf7(aUtf7, aUnicode, EFalse, aEncodeOptionalDirectCharactersInBase64);
	}

TInt CnvUtfConverter::ConvertFromUnicodeToUtf7(TDes8& aUtf7, 
											   const TDesC16& aUnicode, 
											   TBool aIsImapUtf7, 
											   TBool aEncodeOptionalDirectCharactersInBase64)
	{
	if (aUnicode.Length()==0)
		{
		aUtf7.SetLength(0);
		return 0;
		}
	if (aUtf7.MaxLength()==0)
		{
		return aUnicode.Length();
		}
	const TUint escapeCharacterForStartingBase64Block=EscapeCharacterForStartingBase64Block(aIsImapUtf7);
	TUint8* pointerToPreviousUtf7Byte=CONST_CAST(TUint8*, aUtf7.Ptr()-1);
	const TUint8* const pointerToLastUtf7Byte=pointerToPreviousUtf7Byte+aUtf7.MaxLength();
	const TUint16* pointerToPreviousUnicodeCharacter=aUnicode.Ptr()-1;
	const TUint16* const pointerToLastUnicodeCharacter=pointerToPreviousUnicodeCharacter+aUnicode.Length();
	const TUint KIsInBase64Block=0x80000000u;
	TUint bitBuffer=0;
	TInt numberOfBitsInBuffer=0;
	FOREVER
		{
		__ASSERT_DEBUG(pointerToPreviousUtf7Byte<=pointerToLastUtf7Byte, Panic(EPanicBadUtf7Pointers3));
		__ASSERT_DEBUG(pointerToPreviousUnicodeCharacter<=pointerToLastUnicodeCharacter, Panic(EPanicBadUnicodePointers1));
		TUint currentUnicodeCharacter=(pointerToPreviousUnicodeCharacter==pointerToLastUnicodeCharacter)? 0: *(pointerToPreviousUnicodeCharacter+1);
		if ((pointerToPreviousUnicodeCharacter==pointerToLastUnicodeCharacter) || EncodeInUtf7Directly(currentUnicodeCharacter, aIsImapUtf7, aEncodeOptionalDirectCharactersInBase64))
			{
			__ASSERT_DEBUG((bitBuffer&KIsInBase64Block) || (numberOfBitsInBuffer==0), Panic(EPanicBadBitBufferState1));
			__ASSERT_DEBUG((numberOfBitsInBuffer==0) || (numberOfBitsInBuffer==2) || (numberOfBitsInBuffer==4), Panic(EPanicBadBitBufferState2));
			if (bitBuffer&KIsInBase64Block)
				{
				if (numberOfBitsInBuffer!=0)
					{
					if (pointerToLastUtf7Byte-pointerToPreviousUtf7Byte<2) // make sure there is enough space for the trailing '-' as well as the remains of the bitBuffer as the KIsInBase64Block flag is about to turned off, thus the trailing '-' may never get written
						{
						break;
						}
					++pointerToPreviousUtf7Byte;
					*pointerToPreviousUtf7Byte=STATIC_CAST(TUint8, Base64Encoding((bitBuffer<<(6-numberOfBitsInBuffer))&0x3f, aIsImapUtf7));
					}
				else
					{
					if (pointerToPreviousUtf7Byte==pointerToLastUtf7Byte)
						{
						break;
						}
					}
				++pointerToPreviousUtf7Byte;
				*pointerToPreviousUtf7Byte='-';
				bitBuffer=0;
				numberOfBitsInBuffer=0;
				}
			__ASSERT_DEBUG(pointerToPreviousUnicodeCharacter<=pointerToLastUnicodeCharacter, Panic(EPanicBadUnicodePointers2));
			if (pointerToPreviousUnicodeCharacter>=pointerToLastUnicodeCharacter)
				{
				break;
				}
			__ASSERT_DEBUG(pointerToPreviousUtf7Byte<=pointerToLastUtf7Byte, Panic(EPanicBadUtf7Pointers4));
			if (pointerToLastUtf7Byte-pointerToPreviousUtf7Byte<((currentUnicodeCharacter==escapeCharacterForStartingBase64Block)? 2: 1))
				{
				break;
				}
			++pointerToPreviousUtf7Byte;
			*pointerToPreviousUtf7Byte=STATIC_CAST(TUint8, currentUnicodeCharacter);
			++pointerToPreviousUnicodeCharacter;
			if (currentUnicodeCharacter==escapeCharacterForStartingBase64Block)
				{
				++pointerToPreviousUtf7Byte;
				*pointerToPreviousUtf7Byte='-';
				}
			}
		else
			{
			{
			TInt numberOfUtf7BytesRequired=(numberOfBitsInBuffer+16)/6; // "(numberOfBitsInBuffer+16)/6" is the number of iterations that will happen in the while loop below
			if (~bitBuffer&KIsInBase64Block)
				{
				++numberOfUtf7BytesRequired; // for the initial escapeCharacterForStartingBase64Block
				}
			if (pointerToLastUtf7Byte-pointerToPreviousUtf7Byte<numberOfUtf7BytesRequired)
				{
				break;
				}
			}
			if (~bitBuffer&KIsInBase64Block)
				{
				__ASSERT_DEBUG(pointerToPreviousUtf7Byte<pointerToLastUtf7Byte, Panic(EPanicBadUtf7Pointers5));
				++pointerToPreviousUtf7Byte;
				*pointerToPreviousUtf7Byte=STATIC_CAST(TUint8, escapeCharacterForStartingBase64Block);
				}
			bitBuffer<<=16;
			bitBuffer|=currentUnicodeCharacter;
			numberOfBitsInBuffer+=16;
			++pointerToPreviousUnicodeCharacter;
			__ASSERT_DEBUG(numberOfBitsInBuffer<=20, Panic(EPanicBadBitBufferState3));
			while (numberOfBitsInBuffer>=6)
				{
				numberOfBitsInBuffer-=6;
				__ASSERT_DEBUG(pointerToPreviousUtf7Byte<pointerToLastUtf7Byte, Panic(EPanicBadUtf7Pointers6));
				++pointerToPreviousUtf7Byte;
				*pointerToPreviousUtf7Byte=STATIC_CAST(TUint8, Base64Encoding((bitBuffer>>numberOfBitsInBuffer)&0x3f, aIsImapUtf7));
				}
			bitBuffer&=((1<<numberOfBitsInBuffer)-1); // zero all the consumed bits - not strictly necessary but it leaves the buffer in a cleaner state
			bitBuffer|=KIsInBase64Block;
			}
		}
	__ASSERT_DEBUG((bitBuffer&KIsInBase64Block) || (numberOfBitsInBuffer==0), Panic(EPanicBadBitBufferState4));
	__ASSERT_DEBUG((numberOfBitsInBuffer==0) || (numberOfBitsInBuffer==2) || (numberOfBitsInBuffer==4), Panic(EPanicBadBitBufferState5));
	if (bitBuffer&KIsInBase64Block)
		{
#if defined(_DEBUG)
		TInt numberOfLoopIterations=1;
#endif
		FOREVER // there should never be more than 2 iterations of this loop - the first "if" should always succeed the second time if it doesn't succeed the first time
			{
			__ASSERT_DEBUG(pointerToPreviousUtf7Byte<=pointerToLastUtf7Byte, Panic(EPanicBadUtf7Pointers7));
			__ASSERT_DEBUG((numberOfBitsInBuffer==0) || (numberOfBitsInBuffer==2) || (numberOfBitsInBuffer==4), Panic(EPanicBadBitBufferState6));
			__ASSERT_DEBUG(numberOfLoopIterations<=2, Panic(EPanicUnexpectedNumberOfLoopIterations));
#if defined(_DEBUG)
			++numberOfLoopIterations;
#endif
			if (pointerToLastUtf7Byte-pointerToPreviousUtf7Byte>=((numberOfBitsInBuffer==0)? 1: 2)) // if there's room to finish off the base-64 sequence by (i) flushing the bit-buffer and (ii) appending the trailing '-'
				{
				if (numberOfBitsInBuffer!=0)
					{
					__ASSERT_DEBUG(pointerToPreviousUtf7Byte<pointerToLastUtf7Byte, Panic(EPanicBadUtf7Pointers8));
					++pointerToPreviousUtf7Byte;
					*pointerToPreviousUtf7Byte=STATIC_CAST(TUint8, Base64Encoding((bitBuffer<<(6-numberOfBitsInBuffer))&0x3f, aIsImapUtf7));
					}
				__ASSERT_DEBUG(pointerToPreviousUtf7Byte<pointerToLastUtf7Byte, Panic(EPanicBadUtf7Pointers9));
				++pointerToPreviousUtf7Byte;
				*pointerToPreviousUtf7Byte='-';
				break;
				}
			// it is now necessary to move back pointerToPreviousUtf7Byte so that the base-64 sequence can be terminated - note it must be terminated on a Unicode character boundary hence the reason why pointerToPreviousUnicodeCharacter may be moved back too
			TUint8* pointerToEscapeCharacterStartingBase64Block=PointerToEscapeCharacterStartingBase64Block(pointerToPreviousUtf7Byte, aUtf7.Ptr(), aIsImapUtf7);
			const TInt oldNumberOfBase64Characters=pointerToPreviousUtf7Byte-pointerToEscapeCharacterStartingBase64Block;
			__ASSERT_DEBUG(oldNumberOfBase64Characters>0, Panic(EPanicInitialEscapeCharacterButNoBase64));
			__ASSERT_DEBUG(((oldNumberOfBase64Characters*6)+numberOfBitsInBuffer)%16==0, Panic(EPanicBase64SequenceDoesNotFallOnUnicodeCharacterBoundary));
			pointerToPreviousUnicodeCharacter-=((oldNumberOfBase64Characters*6)+numberOfBitsInBuffer)/16; // move back pointerToPreviousUnicodeCharacter to before the equivalent of the base-64 sequence
			pointerToPreviousUtf7Byte=pointerToEscapeCharacterStartingBase64Block;
			__ASSERT_DEBUG(*pointerToPreviousUtf7Byte==escapeCharacterForStartingBase64Block, Panic(EPanicBadUtf7Pointers10));
			if (oldNumberOfBase64Characters<4) // if the new base-64 sequence will be so short that it won't even be able to contain the UTF-7 encoding of a single Unicode character
				{
				--pointerToPreviousUtf7Byte; // move back pointerToPreviousUtf7Byte to before the escapeCharacterForStartingBase64Block
				break;
				}
			const TInt newNumberOfUnicodeCharacters=((oldNumberOfBase64Characters-1)*3)/8;
			pointerToPreviousUnicodeCharacter+=newNumberOfUnicodeCharacters;
			pointerToPreviousUtf7Byte+=((newNumberOfUnicodeCharacters*8)+2)/3;
			const TInt numberOfBitsToBeZeroedInLastBase64Character=(newNumberOfUnicodeCharacters%3)*2;
			if (numberOfBitsToBeZeroedInLastBase64Character!=0)
				{
				*pointerToPreviousUtf7Byte=STATIC_CAST(TUint8, Base64Encoding(Base64Decoding(*pointerToPreviousUtf7Byte, aIsImapUtf7)&0x3f&~((1<<numberOfBitsToBeZeroedInLastBase64Character)-1), aIsImapUtf7));
				}
			bitBuffer=KIsInBase64Block;
			numberOfBitsInBuffer=0;
			}
		}
	aUtf7.SetLength((pointerToPreviousUtf7Byte-aUtf7.Ptr())+1);
	return pointerToLastUnicodeCharacter-pointerToPreviousUnicodeCharacter;
	}

 

/** Converts Unicode text into UTF-8 encoding.

@param aUtf8 On return, contains the UTF-8 encoded output string.
@param aUnicode The Unicode-encoded input string.
@return The number of unconverted characters left at the end of the input 
descriptor, or one of the error values defined in TError. */
EXPORT_C TInt CnvUtfConverter::ConvertFromUnicodeToUtf8(TDes8& aUtf8, const TDesC16& aUnicode)
	{
	return ConvertFromUnicodeToUtf8(aUtf8, aUnicode, EFalse);
	}


/**  Converts Unicode text into UTF-8 encoding.

The variant of UTF-8 used internally by Java differs slightly from
standard UTF-8. The TBool argument controls the UTF-8
variant generated by this function. This function leaves with a 
KErrCorrupt if the input string is corrupt. 

@param aUnicode A UCS-2 encoded input string.
@return A pointer to an HBufC8 containing the converted UTF8. */	
EXPORT_C HBufC8* CnvUtfConverter::ConvertFromUnicodeToUtf8L(const TDesC16& aUnicode)
 	{
	// If aUnicode is  Null string, return an empty HBufC
	if (aUnicode.Length() == 0)
		{
		HBufC8* hBuf8 = HBufC8::NewL(1);
		return hBuf8;
		}

	// Otherwise, convert and store result in a buffer, reallocating that buffer if needed.
	const TInt length = aUnicode.Length();
	const TInt bufsize = 100;
	
	TPtrC16 unicode (aUnicode);
	TBuf8<bufsize> buf;
	HBufC8* hBuf8 = HBufC8::NewLC(length);
	TPtr8 utf8 = hBuf8->Des();

	FOREVER
		{
		TInt unconverted = ConvertFromUnicodeToUtf8(buf, unicode);
		if( unconverted == EErrorIllFormedInput || unconverted < 0)
			User::Leave(KErrCorrupt);

		if (utf8.Length() + buf.Length() > utf8.MaxLength())
			{
			// Reallocate the hBuf8
			hBuf8 = hBuf8->ReAllocL(utf8.Length() + buf.Length());
			CleanupStack::Pop();
			CleanupStack::PushL(hBuf8);
			utf8.Set(hBuf8->Des());
			}
		utf8.Append(buf);
		if (unconverted ==0) 
			break;
		unicode.Set(unicode.Right(unconverted));
		}
	CleanupStack::Pop();
	return hBuf8;
	}

/** Converts Unicode text into UTF-8 encoding. 

The variant of UTF-8 used internally by Java differs slightly from standard 
UTF-8. The TBool argument controls the UTF-8 variant generated by this function.

@param aUtf8 On return, contains the UTF-8 encoded output string.
@param aUnicode A UCS-2 encoded input string.
@param aGenerateJavaConformantUtf8 EFalse for orthodox UTF-8. ETrue for Java 
UTF-8. The default is EFalse.
@return The number of unconverted characters left at the end of the input descriptor, 
or one of the error values defined in TError. */
TInt CnvUtfConverter::ConvertFromUnicodeToUtf8(TDes8& aUtf8, 
											   const TDesC16& aUnicode, 
											   TBool aGenerateJavaConformantUtf8)
	{
	if (aUnicode.Length()==0)
		{
		aUtf8.SetLength(0);
		return 0;
		}
	if (aUtf8.MaxLength()==0)
		{
		return aUnicode.Length();
		}
	TUint8* pointerToCurrentUtf8Byte=CONST_CAST(TUint8*, aUtf8.Ptr());
	const TUint8* pointerToLastUtf8Byte=pointerToCurrentUtf8Byte+(aUtf8.MaxLength()-1);
	const TUint16* pointerToCurrentUnicodeCharacter=aUnicode.Ptr();
	const TUint16* pointerToLastUnicodeCharacter=pointerToCurrentUnicodeCharacter+(aUnicode.Length()-1);
	TBool inputIsTruncated=EFalse;
	FOREVER
		{
		__ASSERT_DEBUG(pointerToCurrentUtf8Byte<=pointerToLastUtf8Byte, Panic(EPanicBadUtf8Pointers1));
		__ASSERT_DEBUG(pointerToCurrentUnicodeCharacter<=pointerToLastUnicodeCharacter, Panic(EPanicBadUnicodePointers3));
		TUint currentUnicodeCharacter=*pointerToCurrentUnicodeCharacter;
		if (((currentUnicodeCharacter&0xff80)==0x0000) && ((currentUnicodeCharacter!=0x0000) || !aGenerateJavaConformantUtf8))
			{
			*pointerToCurrentUtf8Byte=STATIC_CAST(TUint8, currentUnicodeCharacter);
			}
		else if ((currentUnicodeCharacter&0xf800)==0x0000)
			{
			if (pointerToCurrentUtf8Byte==pointerToLastUtf8Byte)
				{
				--pointerToCurrentUtf8Byte;
				--pointerToCurrentUnicodeCharacter;
				break;
				}
			*pointerToCurrentUtf8Byte=STATIC_CAST(TUint8, 0xc0|(currentUnicodeCharacter>>6));
			++pointerToCurrentUtf8Byte;
			*pointerToCurrentUtf8Byte=STATIC_CAST(TUint8, 0x80|(currentUnicodeCharacter&0x3f));
			}
		else if (((currentUnicodeCharacter&0xfc00)==0xd800) && !aGenerateJavaConformantUtf8)
			{
			__ASSERT_DEBUG(pointerToCurrentUtf8Byte<=pointerToLastUtf8Byte, Panic(EPanicBadUtf8Pointers2));
			if (pointerToLastUtf8Byte-pointerToCurrentUtf8Byte<3)
				{
				--pointerToCurrentUtf8Byte;
				--pointerToCurrentUnicodeCharacter;
				break;
				}
			__ASSERT_DEBUG(pointerToCurrentUnicodeCharacter<=pointerToLastUnicodeCharacter, Panic(EPanicBadUnicodePointers4));
			if (pointerToCurrentUnicodeCharacter>=pointerToLastUnicodeCharacter)
				{
				--pointerToCurrentUtf8Byte;
				--pointerToCurrentUnicodeCharacter;
				inputIsTruncated=ETrue;
				break;
				}
			currentUnicodeCharacter+=0x0040;
			*pointerToCurrentUtf8Byte=STATIC_CAST(TUint8, 0xf0|((currentUnicodeCharacter>>8)&0x07));
			++pointerToCurrentUtf8Byte;
			*pointerToCurrentUtf8Byte=STATIC_CAST(TUint8, 0x80|((currentUnicodeCharacter>>2)&0x3f));
			{
			TUint currentUtf8Byte=(0x80|((currentUnicodeCharacter&0x03)<<4));
			++pointerToCurrentUnicodeCharacter;
			currentUnicodeCharacter=*pointerToCurrentUnicodeCharacter;
			if ((currentUnicodeCharacter&0xfc00)!=0xdc00)
				{
				return EErrorIllFormedInput;
				}
			currentUtf8Byte|=((currentUnicodeCharacter>>6)&0x0f);
			++pointerToCurrentUtf8Byte;
			*pointerToCurrentUtf8Byte=STATIC_CAST(TUint8, currentUtf8Byte);
			}
			++pointerToCurrentUtf8Byte;
			*pointerToCurrentUtf8Byte=STATIC_CAST(TUint8, 0x80|(currentUnicodeCharacter&0x3f));
			}
		else
			{
			if (pointerToLastUtf8Byte-pointerToCurrentUtf8Byte<2)
				{
				--pointerToCurrentUtf8Byte;
				--pointerToCurrentUnicodeCharacter;
				break;
				}
			*pointerToCurrentUtf8Byte=STATIC_CAST(TUint8, 0xe0|(currentUnicodeCharacter>>12));
			++pointerToCurrentUtf8Byte;
			*pointerToCurrentUtf8Byte=STATIC_CAST(TUint8, 0x80|((currentUnicodeCharacter>>6)&0x3f));
			++pointerToCurrentUtf8Byte;
			*pointerToCurrentUtf8Byte=STATIC_CAST(TUint8, 0x80|(currentUnicodeCharacter&0x3f));
			}
		if ((pointerToCurrentUnicodeCharacter==pointerToLastUnicodeCharacter) || (pointerToCurrentUtf8Byte==pointerToLastUtf8Byte))
			{
			break;
			}
		++pointerToCurrentUtf8Byte;
		++pointerToCurrentUnicodeCharacter;
		}
	if ((pointerToCurrentUnicodeCharacter<aUnicode.Ptr()) && inputIsTruncated)
		{
		return EErrorIllFormedInput;
		}
	aUtf8.SetLength((pointerToCurrentUtf8Byte-aUtf8.Ptr())+1);
	return pointerToLastUnicodeCharacter-pointerToCurrentUnicodeCharacter;
	}



/**  Converts text encoded using the Unicode transformation format UTF-7
into the Unicode UCS-2 character set.

@param aUtf7 The UTF-7 encoded input string.
@return A pointer to an HBufC16 containing the converted Unicode string */	
EXPORT_C HBufC16* CnvUtfConverter::ConvertToUnicodeFromUtf7L(const TDesC8& aUtf7)
	{
		// If aUtf8 is an empty string return 
	if (aUtf7.Length()==0)
		{
		HBufC16* hBuf = HBufC16::NewL(1);
		return hBuf;
		}

	// else convert aUtf8 to Unicode storing the result in a buffer, reallocating
	// it when needed.
	TInt length = aUtf7.Length();
	const TInt bufsize = 100;
	TInt state = KStateDefault;

	TPtrC8 utf7 (aUtf7);
	TBuf<bufsize> buf;
	HBufC16* hBuf = HBufC16::NewLC(length);
	TPtr unicode = hBuf->Des();

	FOREVER
		{
		TInt unconverted = ConvertToUnicodeFromUtf7(buf, utf7, state);
		if( unconverted == EErrorIllFormedInput || unconverted < 0)
			User::Leave(KErrCorrupt);

		if (unicode.Length() + buf.Length() > unicode.MaxLength())
			{
			// Reallocate hBuf
			hBuf = hBuf->ReAllocL(unicode.Length() + buf.Length());
			CleanupStack::Pop();
			CleanupStack::PushL(hBuf);
			unicode.Set(hBuf->Des());
			}
		unicode.Append(buf);
		if (unconverted ==0) 
			break;
		utf7.Set(utf7.Right(unconverted));
		}
	CleanupStack::Pop();
	return hBuf;
	}

 

/** Converts text encoded using the Unicode transformation format UTF-7 into the 
Unicode UCS-2 character set.

If the conversion is achieved using a series of calls to this function, where 
each call starts off where the previous call reached in the input descriptor, 
the state of the conversion is stored. The initial value of the state variable 
should be set as KStateDefault when the conversion is started, and afterwards 
simply passed unchanged into each function call.

@param aUnicode On return, contains the Unicode encoded output string.
@param aUtf7 The UTF-7 encoded input string.
@param aState For the first call of the function set to KStateDefault. For 
subsequent calls, pass in the variable unchanged.
@return The number of unconverted bytes left at the end of the input descriptor, 
or one of the error values defined in TError. */
EXPORT_C TInt CnvUtfConverter::ConvertToUnicodeFromUtf7(TDes16& aUnicode, 
														const TDesC8& aUtf7, 
														TInt& aState)
	{
	return ConvertToUnicodeFromUtf7(aUnicode, aUtf7, EFalse, aState);
	}

TInt CnvUtfConverter::ConvertToUnicodeFromUtf7(TDes16& aUnicode, 
											   const TDesC8& aUtf7, 
											   TBool aIsImapUtf7, 
											   TInt& aState)
	{
	if (aUtf7.Length()==0)
		{
		aUnicode.SetLength(0);
		return 0;
		}
	if (aUnicode.MaxLength()==0)
		{
		return aUtf7.Length();
		}
	const TUint escapeCharacterForStartingBase64Block=EscapeCharacterForStartingBase64Block(aIsImapUtf7);
	TUint16* pointerToPreviousUnicodeCharacter=CONST_CAST(TUint16*, aUnicode.Ptr()-1);
	const TUint16* pointerToLastUnicodeCharacter=pointerToPreviousUnicodeCharacter+aUnicode.MaxLength();
	const TUint8* pointerToCurrentUtf7Byte=aUtf7.Ptr();
	const TUint8* pointerToLastUtf7Byte=pointerToCurrentUtf7Byte+(aUtf7.Length()-1);
	TUint currentUtf7Byte=*pointerToCurrentUtf7Byte;
	const TUint KIsInBase64Block=0x80000000u;
	TUint bitBuffer=STATIC_CAST(TUint, aState);
	TInt numberOfBitsInBuffer=((bitBuffer&0xf0)>>4);
	bitBuffer&=~0xf0; // turn off the bits that stored numberOfBitsInBuffer
	if (bitBuffer&KIsInBase64Block)
		{
		__ASSERT_ALWAYS((numberOfBitsInBuffer==0) || (numberOfBitsInBuffer==2) || (numberOfBitsInBuffer==4) || ((numberOfBitsInBuffer<16) && (numberOfBitsInBuffer%2==0) && !BitBufferContainsNonZeroBits(bitBuffer, numberOfBitsInBuffer)), Panic(EPanicBadBitBufferState7));
		__ASSERT_ALWAYS((bitBuffer&~(KIsInBase64Block|0x0000000f))==0, Panic(EPanicBadBitBufferState8));
		}
	else
		{
		__ASSERT_ALWAYS(bitBuffer==0, Panic(EPanicBadBitBufferState9));
		__ASSERT_ALWAYS(numberOfBitsInBuffer==0, Panic(EPanicBadBitBufferState10));
		}
	aState=KStateDefault;
	if (bitBuffer&KIsInBase64Block)
		{
		currentUtf7Byte=Base64Decoding(currentUtf7Byte, aIsImapUtf7);
		}
	TBool inputIsTruncated=EFalse;
	FOREVER
		{
		__ASSERT_DEBUG(pointerToPreviousUnicodeCharacter<pointerToLastUnicodeCharacter, Panic(EPanicBadUnicodePointers5));
		__ASSERT_DEBUG(pointerToCurrentUtf7Byte<=pointerToLastUtf7Byte, Panic(EPanicBadUtf7Pointers11));
		__ASSERT_DEBUG((bitBuffer&KIsInBase64Block) || (currentUtf7Byte==*pointerToCurrentUtf7Byte), Panic(EPanicOutOfSyncUtf7Byte1));
		__ASSERT_DEBUG((~bitBuffer&KIsInBase64Block) || (currentUtf7Byte==Base64Decoding(*pointerToCurrentUtf7Byte, aIsImapUtf7)), Panic(EPanicOutOfSyncUtf7Byte2));
		__ASSERT_DEBUG((bitBuffer&KIsInBase64Block) || ((bitBuffer==0) && (numberOfBitsInBuffer==0)), Panic(EPanicBadBitBufferState11));
		if ((~bitBuffer&KIsInBase64Block) && (currentUtf7Byte==escapeCharacterForStartingBase64Block))
			{
			if (pointerToCurrentUtf7Byte==pointerToLastUtf7Byte)
				{
				--pointerToCurrentUtf7Byte;
				inputIsTruncated=ETrue;
				goto end;
				}
			++pointerToCurrentUtf7Byte;
			currentUtf7Byte=*pointerToCurrentUtf7Byte;
			if (currentUtf7Byte=='-')
				{
				currentUtf7Byte=escapeCharacterForStartingBase64Block;
				}
			else
				{
				currentUtf7Byte=Base64Decoding(currentUtf7Byte, aIsImapUtf7);
				if (currentUtf7Byte==KNotInBase64Alphabet)
					{
					return EErrorIllFormedInput;
					}
				bitBuffer=KIsInBase64Block;
				}
			}
		if (bitBuffer&KIsInBase64Block)
			{
			FOREVER
				{
				__ASSERT_DEBUG(currentUtf7Byte==Base64Decoding(*pointerToCurrentUtf7Byte, aIsImapUtf7), Panic(EPanicOutOfSyncBase64Decoding));
				__ASSERT_DEBUG((numberOfBitsInBuffer<16) || (BitBufferContainsNonZeroBits(bitBuffer, numberOfBitsInBuffer-16) && (numberOfBitsInBuffer<16+6)), Panic(EPanicBadBitBufferState12));
				if (currentUtf7Byte==KNotInBase64Alphabet)
					{
					if (BitBufferContainsNonZeroBits(bitBuffer, numberOfBitsInBuffer))
						{
						return EErrorIllFormedInput;
						}
					bitBuffer=0;
					numberOfBitsInBuffer=0;
					currentUtf7Byte=*pointerToCurrentUtf7Byte;
					if (currentUtf7Byte=='-')
						{
						if (pointerToCurrentUtf7Byte==pointerToLastUtf7Byte)
							{
							goto end;
							}
						++pointerToCurrentUtf7Byte;
						currentUtf7Byte=*pointerToCurrentUtf7Byte;
						}
					break;
					}
				bitBuffer<<=6;
				bitBuffer|=currentUtf7Byte;
				bitBuffer|=KIsInBase64Block;
				numberOfBitsInBuffer+=6;
				// only flush the buffer if it contains a whole Unicode character and the remainder is either all zero-bits (hence would be a legal point to end the base-64 sequence) or at least 6 bits long (therefore would leave at least one UTF-7 byte unconverted at the end of the input descriptor)
				if ((numberOfBitsInBuffer>=16+6) || ((numberOfBitsInBuffer>=16) && !BitBufferContainsNonZeroBits(bitBuffer, numberOfBitsInBuffer-16)))
					{
					numberOfBitsInBuffer-=16;
					__ASSERT_DEBUG(pointerToPreviousUnicodeCharacter<pointerToLastUnicodeCharacter, Panic(EPanicBadUnicodePointers6));
					++pointerToPreviousUnicodeCharacter;
					*pointerToPreviousUnicodeCharacter=STATIC_CAST(TUint16, bitBuffer>>numberOfBitsInBuffer);
					bitBuffer&=((1<<numberOfBitsInBuffer)-1); // zero all the consumed bits - must be done as bitBuffer is stored along with numberOfBitsInBuffer in aState if the output descriptor runs out of space or if the input descriptor was truncated
					bitBuffer|=KIsInBase64Block; // turn it back on as the line above turned it off
					if (pointerToPreviousUnicodeCharacter==pointerToLastUnicodeCharacter)
						{
						goto end;
						}
					}
				if (pointerToCurrentUtf7Byte==pointerToLastUtf7Byte)
					{
					inputIsTruncated=ETrue;
					goto end;
					}
				++pointerToCurrentUtf7Byte;
				currentUtf7Byte=Base64Decoding(*pointerToCurrentUtf7Byte, aIsImapUtf7);
				}
			}
		else
			{
			__ASSERT_DEBUG(pointerToPreviousUnicodeCharacter<pointerToLastUnicodeCharacter, Panic(EPanicBadUnicodePointers7));
			++pointerToPreviousUnicodeCharacter;
			*pointerToPreviousUnicodeCharacter=STATIC_CAST(TUint16, currentUtf7Byte);
			if ((pointerToPreviousUnicodeCharacter==pointerToLastUnicodeCharacter) || (pointerToCurrentUtf7Byte==pointerToLastUtf7Byte))
				{
				goto end;
				}
			++pointerToCurrentUtf7Byte;
			currentUtf7Byte=*pointerToCurrentUtf7Byte;
			}
		}
end:
	if (bitBuffer&KIsInBase64Block)
		{
		__ASSERT_DEBUG((numberOfBitsInBuffer<16) || (BitBufferContainsNonZeroBits(bitBuffer, numberOfBitsInBuffer-16) && (numberOfBitsInBuffer<16+6)), Panic(EPanicBadBitBufferState13));
		if (BitBufferContainsNonZeroBits(bitBuffer, numberOfBitsInBuffer))
			{
			// rewind how far we've got in the UTF-7 descriptor to indicate to the user (by returning a value greater than zero) that not all of the input could be converted as it ended with a truncated base-64 sequence
			__ASSERT_DEBUG(numberOfBitsInBuffer>=6, Panic(EPanicBadBitBufferState14));
			pointerToCurrentUtf7Byte-=numberOfBitsInBuffer/6;
			const TInt newNumberOfBitsInBuffer=numberOfBitsInBuffer%6;
			bitBuffer&=~KIsInBase64Block; // temporarily turn off the KIsInBase64Block for the right-shift
			bitBuffer>>=(numberOfBitsInBuffer-newNumberOfBitsInBuffer);
			bitBuffer|=KIsInBase64Block; // must be turned back on again as the bit-buffer is packed into aState
			numberOfBitsInBuffer=newNumberOfBitsInBuffer;
			__ASSERT_DEBUG((numberOfBitsInBuffer==0) || (numberOfBitsInBuffer==2) || (numberOfBitsInBuffer==4), Panic(EPanicBadBitBufferState15));
			}
		__ASSERT_DEBUG((numberOfBitsInBuffer<16) && (numberOfBitsInBuffer%2==0), Panic(EPanicBadBitBufferState16));
		aState=STATIC_CAST(TInt, bitBuffer);
		aState|=(numberOfBitsInBuffer<<4);
		__ASSERT_DEBUG(aState&KIsInBase64Block, Panic(EPanicBadBitBufferState17));
		bitBuffer=0;
		numberOfBitsInBuffer=0;
		}
	if ((pointerToCurrentUtf7Byte<aUtf7.Ptr()) && inputIsTruncated)
		{
		return EErrorIllFormedInput;
		}
	aUnicode.SetLength((pointerToPreviousUnicodeCharacter+1)-aUnicode.Ptr());
	return pointerToLastUtf7Byte-pointerToCurrentUtf7Byte;
	}



/** Converts text encoded using the Unicode transformation format UTF-8
into the Unicode UCS-2 character set. This function leaves with an 
error code of the input string is corrupted. 

@param aUtf8 The UTF-8 encoded input string
@return A pointer to an HBufC16 with the converted Unicode string. */	
EXPORT_C HBufC16* CnvUtfConverter::ConvertToUnicodeFromUtf8L(const TDesC8& aUtf8)
 	{
	// If aUtf8 is an empty string return 
	if (aUtf8.Length()==0)
		{
		HBufC16* hBuf = HBufC16::NewL(1);
		return hBuf;
		}

	// else convert aUtf8 to Unicode storing the result in a buffer, reallocating
	// it when needed.
	TInt length = aUtf8.Length();
	const TInt bufsize = 100;

	TPtrC8 utf8 (aUtf8);
	TBuf<bufsize> buf;
	HBufC16* hBuf = HBufC16::NewLC(length);
	TPtr unicode = hBuf->Des();

	FOREVER
		{
		TInt unconverted = ConvertToUnicodeFromUtf8(buf, utf8);
		if( unconverted == EErrorIllFormedInput || unconverted < 0)
			User::Leave(KErrCorrupt);

		if (unicode.Length() + buf.Length() > unicode.MaxLength())
			{
			// Reallocate hBuf
			hBuf = hBuf->ReAllocL(unicode.Length() + buf.Length());
			CleanupStack::Pop();
			CleanupStack::PushL(hBuf);
			unicode.Set(hBuf->Des());
			}
		unicode.Append(buf);
		if (unconverted ==0) 
			break;
		utf8.Set(utf8.Right(unconverted));
		}
	CleanupStack::Pop();
	return hBuf;
	}

/** Converts text encoded using the Unicode transformation format UTF-8 into the 
Unicode UCS-2 character set.

@param aUnicode On return, contains the Unicode encoded output string.
@param aUtf8 The UTF-8 encoded input string
@return The number of unconverted bytes left at the end of the input descriptor, 
or one of the error values defined in TError. */
EXPORT_C TInt CnvUtfConverter::ConvertToUnicodeFromUtf8(TDes16& aUnicode, const TDesC8& aUtf8)
	{
	return ConvertToUnicodeFromUtf8(aUnicode, aUtf8, EFalse);
	}

static void UpdateUnconvertibleInfo(TInt& aNumberOfUnconvertibleCharacters,
		TInt& aIndexOfFirstByteOfFirstUnconvertibleCharacter, TUint8 aIndex)
	{
	if (aNumberOfUnconvertibleCharacters<=0)
		{
		aIndexOfFirstByteOfFirstUnconvertibleCharacter = aIndex;
		}
	++aNumberOfUnconvertibleCharacters;
	}

/** Converts text encoded using the Unicode transformation format UTF-8 into the 
Unicode UCS-2 character set.

@param aUnicode On return, contains the Unicode encoded output string.
@param aUtf8 The UTF-8 encoded input string
@param aGenerateJavaConformantUtf8 EFalse for orthodox UTF-8. ETrue for Java 
@return The number of unconverted bytes left at the end of the input descriptor, 
or one of the error values defined in TError. */
TInt CnvUtfConverter::ConvertToUnicodeFromUtf8(TDes16& aUnicode, const TDesC8& aUtf8, TBool aGenerateJavaConformantUtf8)
	{
	TInt dummyUnconverted, dummyUnconvertedIndex;
	return ConvertToUnicodeFromUtf8(aUnicode, aUtf8, aGenerateJavaConformantUtf8, dummyUnconverted, dummyUnconvertedIndex);
	}

/** Converts text encoded using the Unicode transformation format UTF-8 into the 
Unicode UCS-2 character set. Surrogate pairs can be created when a valid 4 byte UTF-8 is input.

The variant of UTF-8 used internally by Java differs slightly from standard 
UTF-8. The TBool argument controls the UTF-8 variant generated by this function.

@param aUnicode On return, contains the Unicode encoded output string.
@param aUtf8 The UTF-8 encoded input string
@param aGenerateJavaConformantUtf8 EFalse for orthodox UTF-8. ETrue for Java 
UTF-8. The default is EFalse.
@param aNumberOfUnconvertibleCharacters On return, contains the number of bytes 
which were not converted.
@param aIndexOfFirstByteOfFirstUnconvertibleCharacter On return, the index 
of the first byte of the first unconvertible character. For instance if the 
first character in the input descriptor (aForeign) could not be converted, 
then this parameter is set to the first byte of that character, i.e. zero. 
A negative value is returned if all the characters were converted.
@return The number of unconverted bytes left at the end of the input descriptor, 
or one of the error values defined in TError. */

/* of note: conformance.  Unicode standard 5.0 section 3.9, table 3-7
 * Well formed UTF-8 Byte Sequences, full table.
 * +----------------------------------------------------------------+
 * | Code Points        | 1st byte | 2nd byte | 3rd byte | 4th byte |
 * +--------------------+----------+----------+----------+----------+
 * | U+0000..U+007F     | 00..7D   |          |          |          |  1 byte, ascii
 * | U+0080..U+07FF     | C2..DF   | 80..BF   |          |          |  2 bytes, error if 1st < 0xC2 
 * | U+0800..U+0FFF     | E0       | A0..BF   | 80..BF   |          |  3 bytes, 1st == 0xE0, error if 2nd < 0xA0
 * | U+1000..U+CFFF     | E1..EC   | 80..BF   | 80..BF   |          |  normal
 * | U+D000..U+D7FF     | ED       | 80..9F   | 80..BF   |          |  3 bytes, 1st == 0xED, error if 2nd > 0x9F
 * | U+E000..U+FFFF     | EE..EF   | 80..BF   | 80..BF   |          |  normal
 * | U+10000..U+3FFFF   | F0       | 90..BF   | 80..BF   | 80..BF   |  4 bytes, 1st == 0xf0, error if 2nd < 0x90
 * | U+40000..U+FFFFF   | F1..F3   | 80..BF   | 80..BF   | 80..BF   |  normal
 * | U+100000..U+10FFFF | F4       | 80..8F   | 80..BF   | 80..BF   |  4 bytes, 1st == 0xF4, error if 2nd > 0x8F
 * +--------------------+----------+----------+----------+----------+
 * 
 * As a consequence of the well-formedness conditions specified in table 3-7,
 * the following byte values are disallowed in UTF-8: C0-C1, F5-FF.
 */
TInt CnvUtfConverter::ConvertToUnicodeFromUtf8(TDes16& aUnicode, const TDesC8& aUtf8, TBool aGenerateJavaConformantUtf8,
		TInt& aNumberOfUnconvertibleCharacters, TInt& aIndexOfFirstByteOfFirstUnconvertibleCharacter)
	{	
	aUnicode.SetLength(0);
	if (aUtf8.Length()==0)
		{
		return 0;
		}
	if (aUnicode.MaxLength()==0)
		{
		return aUtf8.Length();
		}

	TUint16* pointerToCurrentUnicodeCharacter=CONST_CAST(TUint16*, aUnicode.Ptr());
	const TUint16* pointerToLastUnicodeCharacter=pointerToCurrentUnicodeCharacter+(aUnicode.MaxLength()-1);
	const TUint8* pointerToCurrentUtf8Byte=aUtf8.Ptr();
	const TUint8* pointerToPendingUtf8Byte=aUtf8.Ptr();
	const TUint8* pointerToLastUtf8Byte=pointerToCurrentUtf8Byte+(aUtf8.Length()-1);
	TUint16 replacementcharacter = 0xFFFD;
	TUint8 currentUtf8Byte;
	TUint currentUnicodeCharacter;
	TInt sequenceLength;		
	
	FOREVER
		{
		__ASSERT_DEBUG(pointerToCurrentUnicodeCharacter<=pointerToLastUnicodeCharacter, Panic(EPanicBadUnicodePointers8));
		__ASSERT_DEBUG(pointerToCurrentUtf8Byte<=pointerToLastUtf8Byte, Panic(EPanicBadUtf8Pointers3));
		currentUtf8Byte=*pointerToCurrentUtf8Byte;
		pointerToPendingUtf8Byte = pointerToCurrentUtf8Byte;
		sequenceLength=100;
		
		for(TInt i=0;i<7;i++)
			{
			if ((currentUtf8Byte&(0xf8<<i))==(STATIC_CAST(TUint8,(0xF0<<i))))
				{
				sequenceLength = 4-i;
				break;
				}
			}

		if ((sequenceLength<2 || sequenceLength>6) && sequenceLength!=0)
			{
			currentUnicodeCharacter=replacementcharacter;
				UpdateUnconvertibleInfo(aNumberOfUnconvertibleCharacters,
						aIndexOfFirstByteOfFirstUnconvertibleCharacter,	pointerToCurrentUtf8Byte-aUtf8.Ptr());
			}
		else
			{		
			if ((pointerToLastUtf8Byte-pointerToCurrentUtf8Byte+1)<sequenceLength)
				{
					if((pointerToCurrentUnicodeCharacter-aUnicode.Ptr())==0)
						return EErrorIllFormedInput;
					
					break;
				}			
				
			currentUnicodeCharacter = currentUtf8Byte&(0x7F>>sequenceLength);
			
			for(TInt i=sequenceLength;i>1; i--)
				{
				currentUtf8Byte = *(++pointerToCurrentUtf8Byte);
				if ((currentUtf8Byte&0xc0)==0x80)
					{
					currentUnicodeCharacter = (currentUnicodeCharacter<<6)|(currentUtf8Byte&0x3F);
					}
				else
					{
					currentUnicodeCharacter=replacementcharacter;
						UpdateUnconvertibleInfo(aNumberOfUnconvertibleCharacters,
								aIndexOfFirstByteOfFirstUnconvertibleCharacter,	pointerToCurrentUtf8Byte-aUtf8.Ptr());
					--pointerToCurrentUtf8Byte;
					}
				}
			}
			
		if (currentUnicodeCharacter > 0xFFFF)
			{
			if(pointerToCurrentUnicodeCharacter>=pointerToLastUnicodeCharacter)
				{
				pointerToCurrentUtf8Byte=pointerToPendingUtf8Byte;
				break;
				}
			
			TUint surrogate = (currentUnicodeCharacter>>10) + 0xD7C0;
			*pointerToCurrentUnicodeCharacter=STATIC_CAST(TUint16, surrogate);			
			++pointerToCurrentUnicodeCharacter;
					
			surrogate = (currentUnicodeCharacter&0x3FF)+0xDC00;
			*pointerToCurrentUnicodeCharacter=STATIC_CAST(TUint16, surrogate);			
			++pointerToCurrentUnicodeCharacter;
			++pointerToCurrentUtf8Byte;
			}
		else
			{
			*pointerToCurrentUnicodeCharacter=STATIC_CAST(TUint16, currentUnicodeCharacter);			
			++pointerToCurrentUnicodeCharacter;
			++pointerToCurrentUtf8Byte;
			}
	
		if ((pointerToCurrentUtf8Byte>pointerToLastUtf8Byte) || (pointerToCurrentUnicodeCharacter>pointerToLastUnicodeCharacter))
			{
			break;
			}
		}

		aUnicode.SetLength(pointerToCurrentUnicodeCharacter-aUnicode.Ptr());
		return pointerToLastUtf8Byte-pointerToCurrentUtf8Byte+1;
	}


GLREF_C void IsCharacterSetUTF8 (TInt& aConfidenceLevel, const TDesC8& aSample)
	{

	TInt sampleLength = aSample.Length();
	if (sampleLength == 0)
		{
		aConfidenceLevel = 89;
		return;
		}
	aConfidenceLevel=sampleLength;
	TInt bytesRemaining=0;

	const TUint8* buffer=&aSample[0];
	for(TInt index=0; index!=sampleLength; ++index)
		{
		if(bytesRemaining>0)
			{
			// bytesRemaining > 0, means that a byte representing the start of a 
			// multibyte sequence was encountered and the bytesRemaining is the 
			// number of bytes to follow. The remaining bytes have to conform to 
			// values within the range 0x80 and 0xbf
			if((buffer[index]&0xc0)==0x80) // the value is within range
				{
				--bytesRemaining;
				continue;
				}
			else
				{
				bytesRemaining=0;
				aConfidenceLevel=0;
				break;
				}
			}
		if (bytesRemaining==0)
			{
			if((buffer[index]&0x80)==0x00)
				{
				// The value of aSample[index] is in the range 0x00-0x7f
				//UTF8 maintains ASCII transparency. So it's a valid
				//UTF8. Do nothing, check next value.
				}
			else if((buffer[index]&0xe0)==0xc0)
				{
				bytesRemaining=1;
				}
			else if((buffer[index]&0xf0)==0xe0)
				{
				bytesRemaining=2;
				}
			else if((buffer[index]&0xf8)==0xf0)
				{
				bytesRemaining=3;
				}
			else
				{
				// wasn't anything expected so must be an illegal/irregular UTF8 coded value
				aConfidenceLevel=0;
				break;
				}
			}
		} // for 
	aConfidenceLevel = (aConfidenceLevel > 0)?100:0;
	}

GLREF_C void IsCharacterSetUTF7(TInt& aConfidenceLevel, const TDesC8& aSample)
	{
	TInt sampleLength = aSample.Length();
	aConfidenceLevel = 70;
	for (TInt i=0; i<sampleLength; ++i)
		{
		// UTF-7 value ranges only 7 bits 
		if((aSample[i]&0x80)!=0x00)
			{
			aConfidenceLevel= 0;
			break;
			}
	
		// there is no "~" in UTF-7 encoding. So if find either, it's not UTF-7
		else if (char(aSample[i])=='~')
			{
			aConfidenceLevel = 0; 
			break;
			}

		// The SMS7Bit escape char value is 0x1b. Reduce confidence if it follows the following format
		else if ( (aSample[i]==0x1b) && (i <sampleLength-1) )
			{
			static const TInt smsExtensionTable[11] = 
				{0x0a, 0x14, 0x1b, 0x28, 0x29, 0x2f, 0x3c, 0x3d, 0x3e, 0x40, 0x65};
			TInt increment1 = i+1;
			if (increment1>= sampleLength)
				break;
			for (TInt j=0; j < 11; ++j)
				{
				if (aSample[increment1] == smsExtensionTable[j])
					{
					aConfidenceLevel-=10;
					}
				}
			}
		// The UTF-7 escape char is 0x2b. The values that follow the escape sequence
		// the values following the escape char value must belong to the modified base64
		// or '-' else it is an ill-formed sequence, so probably not UTF-7
		else if ( (aSample[i]==0x2b)  && (i <sampleLength-1) )
			{
			TInt increment1 = i+1;
			if ((aSample[increment1] == 0x2b) || (aSample[increment1] == 0x2d) || (aSample[increment1] == 0x2f) ||
				((aSample[increment1] >= 0x41) && (aSample[increment1] <= 0x5a)) ||
				((aSample[increment1] >= 0x61) && (aSample[increment1] <= 0x7a))) 
				{
				aConfidenceLevel+=5;
				}
			else
				{
				aConfidenceLevel-=15;
				}
			i++; // should this be here or up in the if loop ??
			}
		} //for
	aConfidenceLevel =(aConfidenceLevel >0)? ((aConfidenceLevel > 100)? 100: aConfidenceLevel): 0;
	}
