/*
* Copyright (c) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
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
#include <charconv.h>
#include <convgeneratedcpp.h>
#include <ecom/implementationproxy.h>
#include <charactersetconverter.h>

class CTurkish_locking_gsm7extConverterImpl : public CCharacterSetConverterPluginInterface
	{

public:
	virtual const TDesC8& ReplacementForUnconvertibleUnicodeCharacters();

	virtual TInt ConvertFromUnicode(
		CCnvCharacterSetConverter::TEndianness aDefaultEndiannessOfForeignCharacters, 
		const TDesC8& aReplacementForUnconvertibleUnicodeCharacters, 
		TDes8& aForeign, 
		const TDesC16& aUnicode, 
		CCnvCharacterSetConverter::TArrayOfAscendingIndices& aIndicesOfUnconvertibleCharacters);

	virtual TInt ConvertToUnicode(
		CCnvCharacterSetConverter::TEndianness aDefaultEndiannessOfForeignCharacters, 
		TDes16& aUnicode, 
		const TDesC8& aForeign, 
		TInt& aState, 
		TInt& aNumberOfUnconvertibleCharacters, 
		TInt& aIndexOfFirstByteOfFirstUnconvertibleCharacter);

	virtual TBool IsInThisCharacterSetL(
		TBool& aSetToTrue, 
		TInt& aConfidenceLevel, 
		const TDesC8& aSample);

	static CTurkish_locking_gsm7extConverterImpl* NewL();
	virtual ~CTurkish_locking_gsm7extConverterImpl();

private:
	CTurkish_locking_gsm7extConverterImpl();

	};


const TDesC8& CTurkish_locking_gsm7extConverterImpl::ReplacementForUnconvertibleUnicodeCharacters()
	{
	return ReplacementForUnconvertibleUnicodeCharacters_internal();
	}

TInt CTurkish_locking_gsm7extConverterImpl::ConvertFromUnicode(
		CCnvCharacterSetConverter::TEndianness aDefaultEndiannessOfForeignCharacters, 
		const TDesC8& aReplacementForUnconvertibleUnicodeCharacters, 
		TDes8& aForeign, 
		const TDesC16& aUnicode, 
		CCnvCharacterSetConverter::TArrayOfAscendingIndices& aIndicesOfUnconvertibleCharacters)
	{
	return CCnvCharacterSetConverter::DoConvertFromUnicode(conversionData, aDefaultEndiannessOfForeignCharacters, aReplacementForUnconvertibleUnicodeCharacters, aForeign, aUnicode, aIndicesOfUnconvertibleCharacters);
	}

TInt CTurkish_locking_gsm7extConverterImpl::ConvertToUnicode(
		CCnvCharacterSetConverter::TEndianness aDefaultEndiannessOfForeignCharacters, 
		TDes16& aUnicode, 
		const TDesC8& aForeign, 
		TInt& /*aState*/, 
		TInt& aNumberOfUnconvertibleCharacters, 
		TInt& aIndexOfFirstByteOfFirstUnconvertibleCharacter)
	{
	return CCnvCharacterSetConverter::DoConvertToUnicode(conversionData, aDefaultEndiannessOfForeignCharacters, aUnicode, aForeign, aNumberOfUnconvertibleCharacters, aIndexOfFirstByteOfFirstUnconvertibleCharacter);
	}

TBool CTurkish_locking_gsm7extConverterImpl::IsInThisCharacterSetL(
		TBool& aSetToTrue, 
		TInt& aConfidenceLevel, 
		const TDesC8& /*aSample*/)
	{
	aSetToTrue=ETrue;
	aConfidenceLevel=0;
	return EFalse;
	}

CTurkish_locking_gsm7extConverterImpl* CTurkish_locking_gsm7extConverterImpl::NewL()
	{
	CTurkish_locking_gsm7extConverterImpl* self = new(ELeave) CTurkish_locking_gsm7extConverterImpl();
	return self;
	}

CTurkish_locking_gsm7extConverterImpl::~CTurkish_locking_gsm7extConverterImpl()
	{
	}

CTurkish_locking_gsm7extConverterImpl::CTurkish_locking_gsm7extConverterImpl()
	{
	}

const TImplementationProxy ImplementationTable[] = 
	{
		IMPLEMENTATION_PROXY_ENTRY(KCharacterSetIdentifierTurkishLockingSms7Bit,	CTurkish_locking_gsm7extConverterImpl::NewL)
	};

EXPORT_C const TImplementationProxy* ImplementationGroupProxy(TInt& aTableCount)
	{
	aTableCount = sizeof(ImplementationTable) / sizeof(TImplementationProxy);

	return ImplementationTable;
	}

 
