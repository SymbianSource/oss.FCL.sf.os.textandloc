/*
* Copyright (c) 1997-2005 Nokia Corporation and/or its subsidiary(-ies). 
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
#include <e32test.h>
#include <utf.h>
#include <UTF7.H>

///////////////////////////////////////////////////////////////////////////////////////

RTest TheTest(_L("TComp7"));
	
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//Tests macroses and functions.
static void Check(TInt aValue, TInt aLine)
	{
	if(!aValue)
		{
		TheTest(EFalse, aLine);
		}
	}
#define TEST(arg) ::Check((arg), __LINE__)

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
	
enum TPanic
	{
	EPanicNoFreeSpaceAtEndOfBuffer1=1,
	EPanicNoFreeSpaceAtEndOfBuffer2
	};

LOCAL_C void Panic(TPanic aPanic)
	{
	User::Panic(_L("TCOMP7"), aPanic);
	}
/**
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0565
@SYMTestCaseDesc        Comparing behaviour with the Unicode CD-ROM UTF-7 sample code
@SYMTestPriority        Medium
@SYMTestActions        	Tests for CnvUtfConverter::ConvertToUnicodeFromUtf7() function
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
GLDEF_C TInt E32Main()
	{
	TheTest.Start(_L("Comparing behaviour with the Unicode CD-ROM UTF-7 sample code"));
	TDes16* originalUnicode=new TBuf16<512>;
	TDes8* generatedUtf7=new TBuf8<1024>;
	TDes8* otherGeneratedUtf7=new TBuf8<1024>;
	TDes16* generatedUnicode=new TBuf16<512>;
	TDes16* otherGeneratedUnicode=new TBuf16<512>;
	TInt state=CnvUtfConverter::KStateDefault;
	//
	*originalUnicode=_L16("");
	originalUnicode->AppendFormat(_L16("Here are some European letters: %c%c%c%c%c%c%c%c%c%c. "), 0x0117, 0x010d, 0x00f1, 0x00df, 0x00d8, 0x0142, 0x0151, 0x016f, 0x0131, 0x00c9);
	originalUnicode->AppendFormat(_L16("Here are some Greek letters: %c%c%c%c%c%c%c%c%c%c. "),    0x03a3, 0x03bf, 0x03bc, 0x03b4, 0x03b5, 0x0345, 0x03a9, 0x0392, 0x0395, 0x03a1);
	originalUnicode->AppendFormat(_L16("Here are some Cyrillic letters: %c%c%c%c%c%c%c%c%c%c. "), 0x0437, 0x0430, 0x0440, 0x0435, 0x0438, 0x0306, 0x0411, 0x041e, 0x0423, 0x0416);
	originalUnicode->AppendFormat(_L16("Here are some Georgian letters: %c%c%c%c%c%c%c%c%c%c. "), 0x10da, 0x10e0, 0x10e9, 0x10ef, 0x10d2, 0x10d7, 0x10e2, 0x10d0, 0x10ed, 0x10e8);
	originalUnicode->AppendFormat(_L16("Here are some Japanese kana: %c%c%c%c%c%c%c%c%c%c. "),    0x30a2, 0x30c0, 0x30d5, 0x30b7, 0x30ba, 0x3091, 0x3093, 0x3055, 0x3074, 0x3080);
	originalUnicode->AppendFormat(_L16("Here are some Han characters: %c%c%c%c%c%c%c%c%c%c. "),   0x7f0c, 0x7a92, 0x6d90, 0x6272, 0x5934, 0x5973, 0x55ce, 0x516c, 0x4ec0, 0x4e00);
	originalUnicode->AppendFormat(_L16("Here are some surrogate pairs: %c%c%c%c%c%c%c%c%c%c. "),   0xd800, 0xdc00, 0xdbff, 0xdfff, 0xdb80, 0xdddd, 0xdbff, 0xdcba, 0xdbeb, 0xdeb0);
	originalUnicode->AppendFormat(_L16("Here are some odd bits and pieces: =+-/*?#~'@!\"$%%^&\\|()[]{}<>_;:,. "));
	enum TUtf7Flags
		{
		EUtf7FlagOptional		=0x00000001,
		EUtf7FlagOtherOptional	=0x00000002,
		EUtf7FlagOtherVerbose	=0x00000004,
		EUtf7FlagCrossOver		=0x00000008,
		EUtf7FlagDone			=0x00000010
		};
	TheTest.Next(_L("Round-trips via UTF-7"));
	for (TInt i=0; ~i&EUtf7FlagDone; ++i)
		{
		TEST(CnvUtfConverter::ConvertFromUnicodeToUtf7(*generatedUtf7, *originalUnicode, i&EUtf7FlagOptional)==0);
		{__ASSERT_ALWAYS(originalUnicode->Length()<originalUnicode->MaxLength(), Panic(EPanicNoFreeSpaceAtEndOfBuffer1));
		TUint16* sourceStart=CONST_CAST(TUint16*, originalUnicode->Ptr());
		TUint16* sourceEnd=sourceStart+originalUnicode->Length();
		char* targetStart=REINTERPRET_CAST(char*, CONST_CAST(TUint8*, otherGeneratedUtf7->Ptr()));
		char* targetEnd=targetStart+(otherGeneratedUtf7->MaxLength()-1);
		TEST(ConvertUCS2toUTF7(&sourceStart, sourceEnd, &targetStart, targetEnd, i&EUtf7FlagOtherOptional, i&EUtf7FlagOtherVerbose)==ok);
		otherGeneratedUtf7->SetLength(targetStart-REINTERPRET_CAST(char*, CONST_CAST(TUint8*, otherGeneratedUtf7->Ptr())));}
		TDes8& sourceForReturnTrip=(i&EUtf7FlagCrossOver)? *otherGeneratedUtf7: *generatedUtf7;
		TDes8& otherSourceForReturnTrip=(i&EUtf7FlagCrossOver)? *generatedUtf7: *otherGeneratedUtf7;
		TEST(CnvUtfConverter::ConvertToUnicodeFromUtf7(*generatedUnicode, sourceForReturnTrip, state)==0);
		TEST(state==CnvUtfConverter::KStateDefault);
		{__ASSERT_ALWAYS(otherSourceForReturnTrip.Length()<otherSourceForReturnTrip.MaxLength(), Panic(EPanicNoFreeSpaceAtEndOfBuffer2));
		char* sourceStart=REINTERPRET_CAST(char*, CONST_CAST(TUint8*, otherSourceForReturnTrip.Ptr()));
		char* sourceEnd=sourceStart+otherSourceForReturnTrip.Length();
		TUint16* targetStart=CONST_CAST(TUint16*, otherGeneratedUnicode->Ptr());
		TUint16* targetEnd=targetStart+(otherGeneratedUnicode->MaxLength()-1);
		TEST(ConvertUTF7toUCS2(&sourceStart, sourceEnd, &targetStart, targetEnd)==ok);
		otherGeneratedUnicode->SetLength(targetStart-otherGeneratedUnicode->Ptr());}
		TEST(*generatedUnicode==*originalUnicode);
		TEST(*generatedUnicode==*otherGeneratedUnicode);
		}
	//
	delete originalUnicode;
	delete generatedUtf7;
	delete otherGeneratedUtf7;
	delete generatedUnicode;
	delete otherGeneratedUnicode;

	TheTest.End();
	TheTest.Close();

	return KErrNone;
	}

