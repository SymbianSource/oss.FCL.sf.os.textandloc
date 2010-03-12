/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef __OPENFONTS_PRIVATE_H__
#define __OPENFONTS_PRIVATE_H__

class COpenFontShaperCacheEntry;

/* MSB is set to indicate a glyph code rather than a unicode value
   This is used for extracting the code value */
#define GLYPH_CODE(code) (code & 0x7fffffff)

/** COpenFontFile owned container for extra data. May be extended without affecting Binary Compatibility.

 @internalComponent
 */

class TOpenFontFileData
	{
public:
	CFontStore* iFontStore;			// pointer to the CFontStore instance that loaded the COpenFontFile
	};

/**
 @internalComponent
 */
class COpenFontGlyph
	{
public:
	COpenFontGlyph(TInt aCode, TInt aGlyphIndex, const TOpenFontCharMetrics& aMetrics):
		iCode(aCode), iGlyphIndex(aGlyphIndex), iMetrics(aMetrics), iBitmapOffset(0) { }
	
	static COpenFontGlyph* NewL(RHeap* aHeap, TInt aCode, TInt aGlyphIndex,
								const TOpenFontCharMetrics& aMetrics, const TDesC8& aBitmap);

	static void Delete(RHeap* aHeap, COpenFontGlyph* aGlyph);	
	TUint8* Bitmap() const;	

	TInt iCode;						// the Unicode value of the character
	TInt iGlyphIndex;				// the glyph index
	TOpenFontCharMetrics iMetrics;	// the metrics	

protected:
	TBool SetBitmap(RHeap* aHeap, const TDesC8& aBitmap);
	~COpenFontGlyph();
	
private:
	// an offset from this COpenFontGlyph object to a pointer to the run-length-encoded bitmap, 
	// calculated as (bitmapPointer)-(this)
	TInt iBitmapOffset;				
	};
/**
 Binary tree of glyphs. Each glyph can have left and right child nodes which are added
 depending on the value of their glyph code relative to the parent's glyph code.

 @internalComponent
 */
class COpenFontGlyphTreeEntry: public COpenFontGlyph
	{
	friend class COpenFont;
	
public:
	static COpenFontGlyphTreeEntry* New(RHeap* aHeap, TInt aCode, TInt aGlyphIndex,
										const TOpenFontCharMetrics& aMetrics, const TDesC8& aBitmap);

private:
	/** The left COpenFontGlyphTreeEntry from this entry. Represented by an offset from the
     current heap base. Use COpenFont::ThisOffsetToPointer() to convert to a valid 
     COpenFontGlyphTreeEntry pointer. */
    TInt iLeftOffset;
    /** The right COpenFontGlyphTreeEntry from this entry. Represented by an offset from the
     current heap base. Use COpenFont::ThisOffsetToPointer() to convert to a valid 
     COpenFontGlyphTreeEntry pointer. */
    TInt iRightOffset;
    /** Pointer to next glyph that was added to the glyph cache.  This enables 
     non-recursive deletion of the cache. This is only ever accessed from server
     process, so can be a direct pointer, not an offset. */
    COpenFontGlyphTreeEntry* iNext;

private:
	COpenFontGlyphTreeEntry(TInt aCode, TInt aGlyphIndex, const TOpenFontCharMetrics& aMetrics)
	 :	COpenFontGlyph(aCode, aGlyphIndex, aMetrics), iLeftOffset(0), iRightOffset(0),iNext(NULL){}

	~COpenFontGlyphTreeEntry();
	};

/**
 * Template for offset implementation of pointer to pointer
 @internalComponent
 */
template<class T>
class ROffsetArray
    {
public:
    ROffsetArray();
    TInt Create(RHeap* aHeap, TInt aCount);
    void Close(RHeap* aHeap);
    TInt Count() const;
    T* operator[](TInt aIndex) const;
    void SetAt(TInt aIndex, T* aEntry);
private:
    TInt iOffset;
    TInt iCount;
    };


/**
 The per-font glyph cache. For now, just the members that used to be directly in
 COpenFont. Now it is a private class it can be elaborated to do character-to-glyph-index
 mapping when that is needed.

 @internalComponent
 */
class COpenFontGlyphCache
	{
public:
	COpenFontGlyphCache(): iGlyphTreeOffset(0), iGlyphCacheMemory(0),iGlyphList(NULL),iShaperCacheSentinel(NULL), iShapingInfoCacheMemory(0), iNumberOfShaperCacheEntries(0) { }
	TShapeHeader* SearchShaperCache(TInt aSessionHandle, TFontShapeFunctionParameters*& aParams);
	TShapeHeader* Insert(TInt aSessionHandle, RHeap* aHeap, CShaper::TInput aInput, TShapeHeader* aShapeHeader, TInt& aAddedBytes);
	TInt DeleteLeastRecentlyUsedEntry(RHeap* aHeap);
	TBool ShaperCacheIsEmpty();
	
public:
	TInt iGlyphTreeOffset;									// an offset to root of the glyph cache; a binary tree
	TInt iGlyphCacheMemory;									// memory used by the glyph tree in bytes
	COpenFontGlyphTreeEntry* iGlyphList;                   // the glyphs, organized as a list
	COpenFontShaperCacheEntry* iShaperCacheSentinel;
	TInt iShapingInfoCacheMemory;
	TInt iNumberOfShaperCacheEntries;	
	};

/**
 @internalComponent
 */

class COpenFontSessionCacheEntry: public COpenFontGlyph
	{
public:
	static COpenFontSessionCacheEntry* New(RHeap* aHeap, const COpenFont* aFont, TInt aCode, TInt aGlyphIndex,
										   const TOpenFontCharMetrics& aMetrics, const TDesC8& aBitmap);
	inline const COpenFont* Font()const;

private:
	inline COpenFontSessionCacheEntry(const COpenFont* aFont, TInt aCode, TInt aGlyphIndex, const TOpenFontCharMetrics& aMetrics);
	~COpenFontSessionCacheEntry();
public:
    TInt iLastAccess;               // serial number of the last access to the glyph

private: 
    TInt iFontOffset;          // offset of the font that contains this glyph, (not owned by this class!)    
	};

/**
 A glyph cache for a particular session.
 Because session caches are not shared they can shrink as well as grow.

 @internalComponent
 */
class COpenFontSessionCache
    {
public:
    static COpenFontSessionCache* NewL(RHeap* aHeap, TInt aSessionHandle, TInt aEntries);
    void Delete(RHeap* aHeap);
    
    TInt SessionHandle() { return iSessionHandle; }
    const COpenFontGlyph* Glyph(const COpenFont* aFont, TInt aCode, TInt& aIndex);
    void Insert(RHeap* aHeap, COpenFontSessionCacheEntry* aEntry, TInt aIndex);
    
private:
    COpenFontSessionCache(TInt aSessionHandle);
    ~COpenFontSessionCache();
public:
    TInt iSessionHandle;    
    TInt iLastAccess;
    ROffsetArray<COpenFontSessionCacheEntry> iEntryArray;
    };

/**
 @internalComponent
 */
class COpenFontSessionCacheListItem
	{
public:
	COpenFontSessionCacheListItem(COpenFontSessionCache* aCache);

	COpenFontSessionCacheListItem* Next();
	void SetNext(COpenFontSessionCacheListItem* aNext);
	COpenFontSessionCache* Cache(); 

	void Delete(RHeap* aHeap);
private:
	~COpenFontSessionCacheListItem();
private:
	TInt iNextOffset;
	TInt iCacheOffset;
	};


// inline functions
inline COpenFontSessionCacheEntry::COpenFontSessionCacheEntry(const COpenFont* aFont, TInt aCode, TInt aGlyphIndex,const TOpenFontCharMetrics& aMetrics) :
    COpenFontGlyph(aCode, aGlyphIndex, aMetrics)
    {
    iFontOffset = aFont ? reinterpret_cast<TInt>(aFont) - reinterpret_cast<TInt>(this) : 0;
    }


inline const COpenFont* COpenFontSessionCacheEntry::Font() const
    {
    if (iFontOffset)
        {
        return reinterpret_cast<const COpenFont*> (PtrAdd(this, iFontOffset));
        }
    else
        {
        return NULL;
        }
    }

#endif	// __OPENFONTSPRIVATE_H__
