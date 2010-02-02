/*
* Copyright (c) 1996-2009 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef __FNTSTD_H__
#define __FNTSTD_H__

#include <e32std.h>
#include <graphics/shapeimpl.h>

/**
@internalComponent
*/
enum TFntStorePanic
	{
	EFntTypefaceIndexOutOfRange,
	EFntHeightIndexOutOfRange,
	EFntNoTypefaces,
	EFntNoTypefaceFontBitmaps,
	EFntTypefaceHasNoFontBitmaps,
	EFntFontBitmapNotLoaded,
	EFntFontAccessCountNonZero,
	EFntFontStoreFileInUse,
	EFntKPixelHeightInTwipsZero,
	EFntSessionCacheIndexOutOfRange,
	EFntMetricsIndexOutOfBounds,
	EFntNoFontFound,
	EFntRemovingAlreadyDeletedLinkedFont,
	EFntOverFlow,
	};

/**
@internalComponent
*/
GLREF_C void Panic(TFntStorePanic aPanic);

// COpenFontSessionCacheList is placed here rather than openfont.cpp because it is used in fntstore.cpp as well.

class COpenFontSessionCacheListItem;
class COpenFont;

#ifdef FNTSTORE_SUPPORT_FMM
class COpenFontSessionCacheList
/**
@internalComponent
*/
	{
public:
	inline COpenFontSessionCacheList();
	void Delete(RHeap* aHeap);
	void DeleteCache(RHeap* aHeap,TInt aSessionHandle);

	COpenFontSessionCacheListItem* Start();
	void SetStart(COpenFontSessionCacheListItem* aItem);

	void DeleteFontGlyphs(RHeap* aHeap,const COpenFont* aFont);

	TInt iStartOffset;
	};

inline COpenFontSessionCacheList::COpenFontSessionCacheList():
	iStartOffset(0)
	{
	}
#else
class COpenFontSessionCacheList
/**
@internalComponent
*/
	{
	friend class COpenFont;

	public:
	inline COpenFontSessionCacheList();
	void Delete(RHeap* aHeap);
	void DeleteCache(RHeap* aHeap,TInt aSessionHandle);

	private:
	void DeleteFontGlyphs(RHeap* aHeap,const COpenFont* aFont);

	COpenFontSessionCacheListItem* iStart;
	};

inline COpenFontSessionCacheList::COpenFontSessionCacheList():
	iStart(NULL)
	{
	}
#endif // FNTSTORE_SUPPORT_FMM

/**
@internalComponent
*/
#ifdef __GCC32__
#define PACKED_STRUCTURE_PREFIX
#define PACKED_STRUCTURE_SUFFIX __attribute__(( __packed__))
#elif defined(__ARMCC__)
#define PACKED_STRUCTURE_PREFIX __packed
#define PACKED_STRUCTURE_SUFFIX
#else
#define PACKED_STRUCTURE_PREFIX
#define PACKED_STRUCTURE_SUFFIX
#endif

PACKED_STRUCTURE_PREFIX class TBitmapFontCharacterOffset
/**
Class to store an offset to the given position of a characters binary data in the 
bitmap section of the font file.
@internalComponent
*/

	{
public:
	TBitmapFontCharacterOffset();
	void InternalizeL(RReadStream& aStream);
public:
	TUint16 iBitmapOffset;  // restricts bitmap to 64k
	} PACKED_STRUCTURE_SUFFIX;

PACKED_STRUCTURE_PREFIX class TBitmapFontCharacterMetrics
/**
Character metrics stored in .GDR files.

This structure cannot be changed without changing the format of bitmap font
files (.GDR files). This is because a pointer to TBitmapFontCharacterMetrics is made to point
to part of the .GDR file in ROM.
@internalComponent
*/

	{
	public:
	TBitmapFontCharacterMetrics();
	void InternalizeL(RReadStream& aStream);

	TInt8 iAscentInPixels;
	TInt8 iHeightInPixels;
	TInt8 iLeftAdjustInPixels;
	TInt8 iMoveInPixels;
	TInt8 iRightAdjustInPixels;
	} PACKED_STRUCTURE_SUFFIX;

#endif
