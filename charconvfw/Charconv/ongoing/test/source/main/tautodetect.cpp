/*
* Copyright (c) 2000-2004 Nokia Corporation and/or its subsidiary(-ies). 
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
#include <e32base.h>
#include <e32test.h>
#include <f32file.h>
#include <charconv.h>

_LIT8(KUnicode,"��Hi there");
_LIT8(KUnicode2, "\xff\xfe\x48\x00\x69\x00\x20\x00\x74\x00\x68\x00\x65\x00\x72\x00\x65\x00");
_LIT8(KUnicode3, "\xfe\xff\x48\x00\x69\x00\x20\x00\x74\x00\x68\x00\x65\x00\x72\x00\x65\x00");
_LIT8(KSJISPhrase, "\x81@\x81y\x83o\x83\x93\x83R\x83N\x82Q\x82T\x93\xfa\x81\x81\x89\xaa\x93""c\x8e\xa0\x8ds\x81z\x83\x84\x83\x93\x83S\x83\x93\x82\xa9\x82\xe7\x82\xcc\x8f\xee\x95\xf1\x82\xc9\x82\xe6\x82\xe9\x82\xc6\x81""A\x83~\x83\x83\x83\x93\x83}\x81[\x82\xcc\x96\xaf\x8e\xe5\x89\xbb\x89^\x93\xae\x8ew\x93\xb1\x8e\xd2\x83""A\x83""E\x83\x93\x81""E\x83T\x83\x93\x81""E\x83X\x81[\x81""E\x83`\x81[\x82\xb3\x82\xf1\x82\xe7\x8d\x91\x96\xaf\x96\xaf\x8e\xe5\x98""A\x96\xbf\x81i\x82m\x82k\x82""c\x81j\x82\xcc\x83\x81\x83\x93\x83o\x81[\x82\xaa\x93\xf1\x8f\\x8el\x93\xfa\x81""A\x8e\xd4\x82\xc5\x83\x84\x83\x93\x83S\x83\x93\x8dx\x8aO\x82\xc9\x8fo\x82\xbd\x82\xc6\x82\xb1\x82\xeb\x81""A\x8cR\x90\xad\x93\x96\x8b\xc7\x82\xc9\x90\xa7\x8e~\x82\xb3\x82\xea\x82\xbd\x82\xbd\x82\xdf\x81""A\x93\xb9\x98H\x82\xed\x82\xab\x82\xc9\x88\xda\x82\xb3\x82\xea\x82\xbd\x8e\xd4\x93\xf1\x91\xe4\x82\xcc\x92\x86\x82\xc5\x82\xeb\x82\xa4\x8f\xe9\x82\xf0\x8en\x82\xdf\x82\xbd\x81""B\x83X\x81[\x81""E\x83`\x81[\x82\xb3\x82\xf1\x82\xaa\x81""A\x93\x96\x8b\xc7\x82\xcc\x8ds\x93\xae\x90\xa7\x8c\xc0\x82\xf0\x94j\x82\xc1\x82\xc4\x8dx\x8aO\x82\xc9\x8fo\x82\xbd\x82\xcc\x82\xcd\x8b\xe3\x94\xaa\x94N\x94\xaa\x8c\x8e\x88\xc8\x97\x88\x81""A\x93\xf1\x94N\x82\xd4\x82\xe8\x81""B\x96\xaf\x8e\xe5\x89\xbb\x89^\x93\xae\x82\xd6\x82\xcc\x8d\x91\x8d\xdb\x93I\x82\xc8\x8ex\x8e\x9d\x8fW\x82\xdf\x82\xf0\x91_\x82\xc1\x82\xc4\x92\xb7\x8a\xfa\x82\xeb\x82\xa4\x8f\xe9\x82\xf0\x8ds\x82\xa4\x89\xc2\x94\\x90\xab\x82\xe0\x82\xa0\x82\xe8\x81""A\x8cR\x90\xad\x91\xa4\x82\xcd\x91\xce\x89\x9e\x82\xc9\x8b\xea\x97\xb6\x82\xb5\x82\xc4\x82\xa2\x82\xe9\x81""B<p>");
_LIT8(KBig5, "\xa1@\xa1@\xa5\xbb\xb3\xf8\xb0T\xa1]\xb0O\xaa\xcc\xb1\xe4\xd9y\xa1^\xac\xb0\xb3""e\xb9\xfd\xb8\xa8\xb9\xea\xa4\xa4\xa5\xa1\xa6\xe8\xb3\xa1\xa4j\xb6}\xb5o\xbe\xd4\xb2\xa4\xa9M\xa7\xf5\xb4P\xb2M\xb0\xc6\xc1`\xb2z\xc3\xf6\xa4_\xb1\xd0\xa8|\xb9\xef\xa4""f\xa4\xe4\xb4\xa9\xab\xfc\xa5\xdc\xba\xeb\xaf\xab\xa1""A\xa5\xbb\xa5\xab\xb1N\xb2\xd5\xc2\xb4\xb1\xd0\xaev\xb9\xce\xadu\xa4\xba\xbbX\xa5j\xb6}\xaei\xb9\xef\xa4""f\xa4\xe4\xb4\xa9\xa1""A\xad\xba\xa7\xe5""115\xa6W\xb1\xd0\xaev\xb1N\xa6""b\xb7s\xbe\xc7\xb4\xc1\xb6}\xbe\xc7\xa4\xa7\xbb\xda\xb1\xd2\xb5{\xadu\xa4\xba\xbbX\xa5j\xa1""C\xacQ\xa4\xd1\xa4W\xa4\xc8\xa1""A\xa5\xab\xa9""e\xae\xd1\xb0O");
_LIT8(KEUP, "\xa1\xcb\xa1\xa3\xa4\xb3\xa4\xec\xa4\xcf\xa1\xa4\xb9\xe2\xc9\xe9\xb2\xd9\xa4\xce\xa5\xd9\xa5\xf3\xa5\xc1\xa5\xde\xa1\xbc\xa5\xaf\xa4\xe4\xa5\xa2\xa5\xd7\xa5\xea\xa5\xb1\xa1\xbc\xa5\xb7\xa5\xe7\xa5\xf3\xa4\xf2\xbc\xc2\xb9\xd4\xa4\xb9\xa4\xeb\xa4\xc8\xa1\xa4\xbd\xe8\xcd\xfd\xa4\xac\xb4\xb0\xce\xbb\xa4\xb9\xa4\xeb\xc1\xb0\xa4\xcb\xa5\xd5\xa5\xea\xa1\xbc\xa5\xba\xa4\xb9\xa4\xeb\xc9\xd4\xb6\xf1\xb9\xe7\xa4\xac\xb3\xce\xc7\xa7\xa4\xb5\xa4\xec\xa4\xbf\xa4\xbf\xa4\xe1\xa1\xa3\xa4\xb7\xa4\xab\xa4\xb7\xcc\xe4\xc2\xea\xa4\xcf\xa1\xa4\xa4\xbd\xa4\xce\xb8\xb6\xb0\xf8\xa4\xac\xa1\xd6\xa5\xb7\xa5\xea\xa5\xb3\xa5\xf3\xa4\xce\xa5\xde\xa1\xbc\xa5\xb8\xa5\xf3\xc9\xd4\xc2\xad\xa1\xd7\xa4\xc0\xa4\xc3\xa4\xbf\xc5\xc0\xa4\xc0\xa1\xa3");
_LIT8(KEUC2, "Enlightenment\xa4\xce\xa5\xc6\xa1\xbc\xa5\xde\xa4\xc8\xa4\xcf\xa1\xa2\xa5\xa6\xa5\xa3\xa5\xf3\xa5\xc9\xa5\xa6\xa5\xde\xa5\xcd\xa1\xbc\xa5\xb8\xa5\xe3\xa4\xce\xb3\xb0\xb4\xd1\xc9\xf4\xca\xac\xa4\xce\xcd\xd7\xc1\xc7\xa4\xf2\xa4\xd2\xa4\xc8\xa4\xde\xa4\xc8\xa4\xe1\xa4\xcb\xa4\xb7\xa4\xc6\xc0\xda\xa4\xea\xc2\xd8\xa4\xa8\xa4\xe9\xa4\xec\xa4\xeb\xa4\xe8\xa4\xa6\xa4\xcb\xa4\xb7\xa4\xbf\xa4\xe2\xa4\xce\xa1\xa2\xa4\xc8\xb9\xcd\xa4\xa8\xa4\xeb\xa4\xb3\xa4\xc8\xa4\xac\xa4\xc7\xa4\xad\xa4\xde\xa4\xb9\xa1\xa3\xa4\xc4\xa4\xde\xa4\xea\xa1\xa2""1\xa4\xc4\xa4\xce\xa5\xa6\xa5\xa3\xa5\xf3\xa5\xc9\xa5\xa6\xa5\xde\xa5\xcd\xa1\xbc\xa5\xb8\xa5\xe3\xa4\xca\xa4\xce\xa4\xcb\xa1\xa2Windows\xc9\xf7\xa4\xcb\xa4\xe2\xa1\xa2Mac\xc9\xf7\xa4\xcb\xa4\xe2\xa1\xa2\xa4\xb5\xa4\xde\xa4\xb6\xa4\xde\xa4\xcb\xa5\xab\xa5\xb9\xa5\xbf\xa5\xde\xa5\xa4\xa5\xba\xa4\xb9\xa4\xeb\xa4\xb3\xa4\xc8\xa4\xac\xa4\xc7\xa4\xad\xa4\xde\xa4\xb9\xa1\xa3");
_LIT8(KSJIS, "\x82\xb1\x82\xcc\x83z\x81[\x83\x80\x83y\x81[\x83W\x82\xcd\x81""A\x82\xa9\x82\xed\x82\xa2\x82\xa2\x83L\x83\x83\x83\x89\x83N\x83^\x81[\x81g\x83s\x83\x93\x83O\x81[\x81h\x82\xf0\x82\xbd\x82\xad\x82\xb3\x82\xf1\x82\xcc\x90l\x82\xbd\x82\xbf\x82\xc9\x8f\xd0\x89\xee\x82\xb5\x81""A\x82\xdc\x82\xbd\x81""A\x8c\xf0\x97\xac\x82\xf0\x8e\x9d\x82\xc1\x82\xc4\x82\xa2\x82\xbd\x82\xbe\x82\xab\x82\xbd\x82\xa2\x82\xc6\x8ev\x82\xc1\x82\xc4\x8d\xec\x90\xac\x82\xb3\x82\xea\x82\xbd\x83y\x81[\x83W\x82\xc5\x82\xb7\x81""B<B>\x82\xb1\x82\xcc\x83z\x81[\x83\x80\x83y\x81[\x83W\x82\xcd\x8a""F\x82\xb3\x82\xf1\x82\xcc\x81g\x83N\x83`\x83R\x83~\x81h\x82\xc5\x90\xac\x82\xe8\x97\xa7\x82\xc1\x82\xc4\x82\xa2\x82\xdc\x82\xb7\x81""B</B>\x82\xba\x82\xd0\x8f\xee\x95\xf1\x82\xf0\x82\xa8\x8a\xf1\x82\xb9\x89\xba\x82\xb3\x82\xa2\x81I");
_LIT8(SJISNET, "20\x94NTRUSTe\x93\xfa\x96{\x82\xcd\x81""A\x8f\xee\x95\xf1\x82\xcc\x8aJ\x8e\xa6\x82\xc6\x8d\x90\x92m\x8b`\x96\xb1\x82\xc9\x8a\xd6\x82\xb7\x82\xe9\x8c\xb4\x91\xa5\x82\xf0\x8dL\x82\xdf\x82\xe9\x82\xb1\x82\xc6\x82\xc9\x82\xe6\x82\xe8\x81""A\x83""C\x83\x93\x83^\x81[\x83l\x83""b\x83g\x8f\xe3\x82\xc9\x82\xa8\x82\xaf\x82\xe9\x83\x86\x81[\x83U\x81[\x82\xc6\x82\xcc\x8f\xee\x95\xf1\x8aJ\x8e\xa6\x82\xc9\x8a\xd6\x82\xb7\x82\xe9\x90M\x97\x8a\x8a\xd6\x8cW\x82\xf0\x91\xc5\x82\xbf\x97\xa7\x82\xc4\x82\xe9\x82\xb1\x82\xc6\x82\xf0\x8eg\x96\xbd\x82\xc6\x82\xb7\x82\xe9\x81""A\x93\xc6\x97\xa7\x82\xcc\x94\xf1\x89""c\x97\x98\x91g\x90""D\x82\xc5\x82\xb7\x81""B\x82\xb1\x82\xcc\x83""E\x83""F\x83u\x83T\x83""C\x83g\x82\xcd\x8bM\x93""a\x82\xcc\x83v\x83\x89\x83""C\x83o\x83V\x81[\x82\xc9\x91\xce\x82\xb7\x82\xe9\x82\xbb\x82\xcc\x8c\xf6\x96\xf1\x82\xf0\x8e\xc0\x8f\xd8\x82\xb7\x82\xe9\x88\xd3\x96\xa1\x82\xc5\x81""A\x82\xb1\x82\xb1\x82\xc9\x8f\xee\x95\xf1\x82\xcc\x8e\xe6\x82\xe8\x88\xb5\x82\xa2\x8a\xee\x8f\x80\x82\xf0\x8aJ\x8e\xa6\x82\xb5\x82\xbd\x82\xe0\x82\xcc\x82\xc5\x81""A\x82\xb1\x82\xcc\x83v\x83\x89\x83""C\x83o\x83V\x81[\x8e\xe6\x82\xe8\x88\xb5\x82\xa2\x8a\xee\x8f\x80\x82\xc9\x82\xc2\x82\xa2\x82\xc4\x82\xcd\x81""ATRUSTe\x82\xc9\x82\xe6\x82\xe8\x81""A\x82\xbb\x82\xcc\x8f\x87\x8e\xe7\x82\xc9\x8a\xd6\x82\xb7\x82\xe9\x8c\x9f\x93\xa2\x82\xc6\x8a\xc4\x8d\xb8\x82\xc6\x82\xf0\x8e\xf3\x82\xaf\x82\xbd\x82\xe0\x82\xcc\x82\xc5\x82\xb7\x81""B");
_LIT8(BIG5A, "\xb0\xea\xae""a\xbcs\xbc\xbd\xb9q\xb5\xf8\xbd\xe8\xb6q\xba\xca\xb7\xfe\xc0\xcb\xc5\xe7\xb4\xfa\xb8\xd5\xa4\xa4\xa4\xdf</a> - \xb9\xef\xad\xb5\xb5\xf8\xc0W\xb2\xa3\xab~\xaa\xba\xb1`\xb7\xc5\xb9q\xa9\xca\xaf\xe0\xa1""B\xa6w\xa5\xfe\xa1""B\xb9q\xba\xcf\xad\xdd\xae""e\xa7@\xc0\xf4\xb9\xd2\xb4\xfa\xb8\xd5\xa9M\xba\xca\xb7\xfe\xa9\xe2\xac""d");
_LIT8(BIG5C, "\xac\xfc \xb0\xea \xb0\xc8 \xb0| \xa8\xc8 \xa4\xd3 \xb0\xc6 \xa7U \xad\xeb \xc1\xc2 \xb2Q \xc4R \xa4\xb5 \xa4\xe9 \xa6""b \xa6\xb9 \xb6\xa1 \xa4@ \xa6\xb8 \xbcy \xaf\xac \xa4\xa4 \xa6@ \xab\xd8 \xac""F \xa4\xad \xa4Q \xa9P \xa6~ \xaa\xba \xa4j \xab\xac \xac\xe3 \xb0Q \xb7| \xa4\xa4 \xaa\xed \xa5\xdc \xa1""A \xa4\xa4 \xa6@ \xc0\xb3 \xb8\xd3 \xb9\xef \xa5x \xc6W \xb1\xc4");
_LIT8(GB2312B, "\xd0\xc2\xce\xc5, \xd0\xa1\xcb\xb5\xa3\xac\xd4\xd3\xd6\xbe\xa3\xac\xb6\xc1\xd5\xdf\xa3\xac\xc2\xdb\xcc\xb3\xa3\xac\xce\xc4\xd5\xaa\xa3\xac\xb1\xa8\xd6\xbd\xa3\xac\xd0\xa6\xbb\xb0\xa3\xac\xcc\xe5\xd3\xfd\xa3\xac\xc7\xe9\xb8\xd0\xa3\xac\xc1\xf4\xd1\xa7\xa3\xac\xbf\xe1\xd5\xbe\xa3\xac");
_LIT8(GB2312C,       "\xa1\xa1\xa1\xf1\xcd\xf5\xbb\xdb\xa3\xa8\xb1\xbe\xb1\xa8\xcc\xd8\xd4\xbc\xa3\xa9\xb1\xb1\xbe\xa9\xb1\xa8\xb5\xc0<p>\xa1\xa1\xa1\xa1\xc0\xfa\xbd\xec\xb0\xc2\xd4\xcb\xbb\xe1\xca\xd7");
_LIT8(GB2312Corrupt, "\xa1\xa1\xa1\xf1\xcd\xf5\xbb\xdb\xa3""fff\xb1\xbe\xb1\xa8\xcc\xd8\xd4\xbc\xa3\xa9""ff\xb1\xb1\xbe\xa9\xb1\xa8\xb5\xc0<pddd>\xa1\xa1\xa1\xa1\xc0\xfa\xbd\xec\xb0\xc2\xd4\xcb\xbb\xe1\xca\xd7");//FAILED
_LIT8(BIG5Corrupt, "\xac\xfc \xb0\xea \xb0\xc8 \xb0| \xa8\xc8 \xa4\xd3 \xb0\xc6 \xa7U ddd\xad\xeb \xc1\xc2 \xb2Q \xc4R \xa4""ddd\xb5 \xa4\xe9 \xa6""b \xa6\xb9 \xb6\xa1 \xa4@ \xa6\xb8 \xbcy \xaf\xac \xa4\xa4 \xa6@ \xab\xd8 \xac""F \xa4\xad \xa4Q \xa9P \xa6~ \xaa\xba \xa4j \xab\xac \xac\xe3 \xb0Q \xb7| \xa4\xa4 \xaa\xed \xa5\xdc \xa1""A \xa4\xa4 \xa6@ddd \xc0\xb3 \xb8\xd3 \xb9\xef \xa5x \xc6W \xb1\xc4");
_LIT8(BIG5Ahalf, "this is to test the data with ASCII mixured \xea\xae""a\xbcs\xbc\xbd\xb9q\xb5\xf8\xbd\xe8\xb6q\xba\xca\xb7\xfe\xc0\xcb\xc5\xe7\xb4\xfa\xb8\xd5\xa4\xa4\xa4\xdf</a> - \xb9\xef\xad\xb5\xb5\xf8\xc0W\xb2\xa3\xab~\xaa\xba\xb1`\xb7\xc5\xb9q\xa9\xca\xaf\xe0\xa1""B\xa6w\xa5\xfe\xa1""B\xb9q\xba\xcf\xad\xdd\xae""e\xa7@\xc0\xf4\xb9\xd2\xb4\xfa\xb8\xd5\xa9M\xba\xca\xb7\xfe\xa9\xe2\xac""d");
_LIT8(KASCII, "SO what result do I get for a text that is pure Ascii and nothing else. Not something stupid I hope!");
_LIT8(KUTF8, "\xe4\xbc\x80\xe6\xac\x80\xe2\x80\x80\xe5\x8c\x80\xe6\xbc\x80\xe2\x80\x80\xe4\xa0\x80\xe6\x94\x80\xe7\x88\x80\xe6\x94\x80\xe2\x80\x80\xe6\xa4\x80\xe7\x8c\x80\xe2\x80\x80\xe6\x84\x80\xe2\x80\x80\xe7\x90\x80\xe6\x94\x80\xe7\xa0\x80\xe7\x90\x80\xe2\x80\x80\xe7\x90\x80\xe6\xa0\x80\xe6\x84\x80\xe7\x90\x80\xe2\x80\x80\xe7\x9c\x80\xe6\xa4\x80\xe6\xb0\x80\xe6\xb0\x80\xe2\x80\x80\xe6\x88\x80\xe6\x94\x80\xe2\x80\x80\xe6\x8c\x80\xe6\xbc\x80\xe6\xb8\x80\xe7\x98\x80\xe6\x94\x80\xe7\x88\x80\xe7\x90\x80\xe6\x94\x80\xe6\x90\x80\xe2\x80\x80\xe6\xa4\x80\xe6\xb8\x80\xe7\x90\x80\xe6\xbc\x80\xe2\x80\x80\xe6\x84\x80\xe2\x80\x80\xe5\x94\x80\xe5\x90\x80\xe4\x98\x80\xe2\xb4\x80\xe3\x9c\x80\xe2\x80\x80\xe7\xb8\x80\xe2\x80\x80\xe5\x90\x80\xe6\x94\x80\xe7\xa0\x80\xe7\x90\x80");
_LIT8(KDodgyShiftJIS,"�����͒a�������悤�ꂵ���Ȃ��`����");
_LIT8(KDodgyShiftJIS2,"20000222T100000Z;;;\x92\xa9\x82\xbe\x82\xe6\x8b\x4e\x82\xab\x82\xeb\x82\xa7\x81\x60\x81\x60\x81\x49\x81\x49\x81\x49");
_LIT8(KDodgyShiftJIS3,"\x83\x5c\x83\x5c\x83\x5c\x82\xa0\x82\xa2\x82\xa4\x82\xa6\x82\xa8\x83\x5c\x83\x5c\x83\x5c\x82\xa9\x82\xab\x82\xad\x82\xaf\x82\xb1\x82\x5c");
_LIT8(KISO,"\x6d\x6f\x72\x6f\x0d\x0a\x6d\x69\x74\xe4\x20\x6b\x75\x75\x6c\x75\x75\x3f");
_LIT8(KSomeISO, "\x48\x65\x6a\x21\x20\x0d\x0a\x0d\x0a\x68\xe4\x72\x20\x6b\x6f\x6d\x6d\x65\x72\x20\x65\x74\x74\x20\x6d\x61\x69\x6c\x20\x6d\x65\x64\x20\x6d\x61\x73\x73\x61\x20\x74\x65\x78\x74\x20\x6f\x63\x68\x20\x65\x74\x74\x20\x61\x74\x74\x61\x63\x68\x6d\x65\x6e\x74\x2e\x20\x44\x65\x74\x74\x61\x20\x6c\x69\x6c\x6c\x61\x20\x6d\x61\x69\x6c");
_LIT8(KUnicodeFail,"\x0d");
_LIT8(KISODEF,"\xd7\x6d\x30\xf7"); // Test for defect raised in 6.1 (EXT-5HLEKN)

/**
* Work around for DEF063276.
* These literals are now loaded from a z:\test\data\KLittleEndian.dat and
* z:\test\data\KBigEndian.dat respectivly.
* Bullseye Coverage corrupts these literals to avoid this they are stored in files as to not be touched by Bullseye Coverage.
*/	

// Test for defect INC037743 - Charconv recognises Little Endian as Big Endian
/*_LIT8(KLittleEndian,
	"\x43\x00\x68\x00\x61\x00\x74\x00\x20\x00\x68\x00\x69\x00\x73\x00"
	"\x74\x00\x6F\x00\x72\x00\x79\x00\x20\x00\x32\x00\x0A\x00\x43\x00" 
	"\x68\x00\x61\x00\x74\x00\x20\x00\x72\x00\x6F\x00\x6F\x00\x6D\x00"
	"\x20\x00\x27\x00\x77\x00\x76\x00\x3A\x00\x6A\x00\x75\x00\x68\x00"
	"\x61\x00\x75\x00\x74\x00\x69\x00\x6F\x00\x2F\x00\x32\x00\x30\x00"
	"\x70\x00\x6D\x00\x74\x00\x40\x00\x6E\x00\x6F\x00\x6B\x00\x69\x00"
	"\x61\x00\x2E\x00\x63\x00\x6F\x00\x6D\x00\x27\x00\x0A\x00\x53\x00"
	"\x74\x00\x61\x00\x72\x00\x74\x00\x3A\x00\x20\x00\x30\x00\x31\x00" 
	"\x2F\x00\x30\x00\x39\x00\x2F\x00\x32\x00\x30\x00\x30\x00\x33\x00"
	"\x20\x00\x32\x00\x32\x00\x3A\x00\x34\x00\x33\x00\x3A\x00\x32\x00"
	"\x38\x00\x0A\x00\x49\x00\x76\x00\x61\x00\x6E\x00\x20\x00\x57\x00"
	"\x65\x00\x6C\x00\x63\x00\x6F\x00\x6D\x00\x65\x00\x20\x00\x74\x00"
	"\x6F\x00\x20\x00\x63\x00\x68\x00\x61\x00\x74\x00\x20\x00\x72\x00" 
	"\x6F\x00\x6F\x00\x6D\x00\x21\x00\x20\x00\x54\x00\x6F\x00\x70\x00"
	"\x69\x00\x63\x00\x20\x00\x69\x00\x73\x00\x20\x00\x59\x00\x6C\x00" 
	"\x65\x00\x69\x00\x73\x00\x74\x00\xE4\x00\x20\x00\x76\x00\x65\x00"
	"\x6C\x00\x6C\x00\x6F\x00\x6E\x00\x74\x00\x61\x00\x61\x00\x2E\x00"
	"\x0A\x00\x4D\x00\x69\x00\x6B\x00\x61\x00\x54\x00\x20\x00\x6A\x00"
	"\x6F\x00\x69\x00\x6E\x00\x65\x00\x64\x00\x0A\x00");		 
	
_LIT8(KBigEndian,
	"\x00\x43\x00\x68\x00\x61\x00\x74\x00\x20\x00\x68\x00\x69\x00\x73"
	"\x00\x74\x00\x6F\x00\x72\x00\x79\x00\x20\x00\x32\x00\x0A\x00\x43" 
	"\x00\x68\x00\x61\x00\x74\x00\x20\x00\x72\x00\x6F\x00\x6F\x00\x6D"
	"\x00\x20\x00\x27\x00\x77\x00\x76\x00\x3A\x00\x6A\x00\x75\x00\x68"
	"\x00\x61\x00\x75\x00\x74\x00\x69\x00\x6F\x00\x2F\x00\x32\x00\x30"
	"\x00\x70\x00\x6D\x00\x74\x00\x40\x00\x6E\x00\x6F\x00\x6B\x00\x69"
	"\x00\x61\x00\x2E\x00\x63\x00\x6F\x00\x6D\x00\x27\x00\x0A\x00\x53"
	"\x00\x74\x00\x61\x00\x72\x00\x74\x00\x3A\x00\x20\x00\x30\x00\x31" 
	"\x00\x2F\x00\x30\x00\x39\x00\x2F\x00\x32\x00\x30\x00\x30\x00\x33"
	"\x00\x20\x00\x32\x00\x32\x00\x3A\x00\x34\x00\x33\x00\x3A\x00\x32"
	"\x00\x38\x00\x0A\x00\x49\x00\x76\x00\x61\x00\x6E\x00\x20\x00\x57"
	"\x00\x65\x00\x6C\x00\x63\x00\x6F\x00\x6D\x00\x65\x00\x20\x00\x74"
	"\x00\x6F\x00\x20\x00\x63\x00\x68\x00\x61\x00\x74\x00\x20\x00\x72" 
	"\x00\x6F\x00\x6F\x00\x6D\x00\x21\x00\x20\x00\x54\x00\x6F\x00\x70"
	"\x00\x69\x00\x63\x00\x20\x00\x69\x00\x73\x00\x20\x00\x59\x00\x6C" 
	"\x00\x65\x00\x69\x00\x73\x00\x74\x00\xE4\x00\x20\x00\x76\x00\x65"
	"\x00\x6C\x00\x6C\x00\x6F\x00\x6E\x00\x74\x00\x61\x00\x61\x00\x2E"
	"\x00\x0A\x00\x4D\x00\x69\x00\x6B\x00\x61\x00\x54\x00\x20\x00\x6A"
	"\x00\x6F\x00\x69\x00\x6E\x00\x65\x00\x64\x00\x0A\x00");*/

// test file for INC037705 - SS66 - Charconv autodetect recognises Swedish as Shift-JIS 
// These tests currently fail as the test detects KCharacterSetIdentifierShiftJis. 
/* This defect was rejected, so the test code has been commented out
_LIT8(KInc037705,
  	"\x0d\x0a\x2A\x8E\x99\x99\x20\x53\x99\x46\x8F\x53\x8F\x20\x94\x73"
  	"\x64\x66\x84\x73\x64\x94\x73\x64\x20\x53\x8F\x99\x99\x20\x73\x99"
    "\x46\x8f\x8e\x99\x20\x73\x46\x99\x8f\x53\x44\x0D\x0A\x53\x8F\x46"
    "\x4C\x99\x20\x50\x8F\x4C\x84\x20\x4C\x50\x8F\x53\x46\x8F\x8E\x20"
  	"\x4C\x50\x53\x46\x44\x8E\x20\x50\x4C\x53\x44\x46\x20\x50\x4C\x53"
  	"\x4C\x50\x6C\x84\x84\x73\x6C\x84\x6C\x84\x94\x84\x0D\x0A\x20\x53"
  	"\x46\x99\x6C\x73\x86\x70\x94\x66\x84\x0D\x0A\x27\x86\x27\x22\x94"
  	"\x20\x94\x27\x84\x20\x94\x8F\x53\x46\x20\x84\x27\x94\x27\x86\x73" 
  	"\x94\x20\x86\x94\x73\x27\x0D\x0A\x0D\x0A\x0D\x0A\x0D\x0A"); 
*/  	

// Swedish test file for INC037705, This is "test2.txt" from the defect
_LIT8(KSwedish,
	"\x55\x74\x61\x6E\x73\x6B\x72\x69\x66\x74\x65\x6E\x3A\x0D\x0A\x53"	
	"\x65\x72\x65\x6E\x69\x73\x73\x69\x6D\x6F\x20\x65\x74\x20\x43\x6C"	
	"\x61\x72\x69\x73\x73\x69\x6D\x6F\x20\x44\x6F\x6D\x69\x6E\x6F\x0D"	
	"\x0A\x44\x6F\x6D\x69\x6E\x6F\x20\x47\x75\x73\x74\x61\x66\x66\x6F"	
	"\x20\x53\x75\x65\x63\x6F\x72\x75\x6D\x0D\x0A\x65\x74\x20\x47\x6f"	
	"\x74\x68\x6F\x72\x75\x6D\x20\x52\x65\x67\x69\x20\x44\x6F\x6D\x69"	
	"\x6E\x6F\x20\x53\x75\x6F\x0D\x0A\x43\x6C\x65\x6D\x65\x6E\x74\x69"	
	"\x70\x70\x69\x6D\x6F\x0D\x0A\x0D\x0A\x4E\xE5\x64\x20\x6F\x63\x68"	
	); 

// Finnish test file for INC037705, This is "test3.txt" from the defect
_LIT8(KFinnish,
	"\x59\x68\x64\x65\x73\x74\x6F\x69\x73\x74\x61\x20\x72\x75\x6E\x6F"
	"\x0D\x0A\x0D\x0A\x56\x69\x6B\x61\x20\x6F\x6E\x20\x41\x68\x74\x69"
	"\x61\x20\x73\x61\x6E\x6F\x61\x2C\x20\x76\x65\x69\x74\x69\x6B\x6B"
	"\xE4\x74\xE4\x20\x76\x69\x65\x72\x65\x74\x65\x6C\x6C\xE4\x2E\x20"
	"\x0D\x0A\x0D\x0A\x41\x68\x74\x69\x20\x70\x6F\x69\x6B\x61\x20\x53"
	"\x61\x61\x72\x65\x6C\x61\x69\x6E\x65\x6E\x2C\x20\x74\x75\x6F\x20"
	"\x6F\x6E\x20\x6C\x69\x65\x74\x6F\x20\x4C\x65\x6D\x6D\x69\x6E\x20"
	"\x70\x6F\x69\x6B\x61\x2C\x20\x0D\x0A\x6B\x61\x73\x76\x6F\x69\x20"
	); 

// This is the last two lines from GotchaLog.txt 
// from INC043016 - AV21 via BTH received TXT file could not be opened
// Which is enough to reproduce the defect
_LIT8(KGotcha,
	"\x0A\x0D\x0A\x4D\x65\x6D\x6F\x72\x79\x20\x74\x65\x73\x74\x20\x2D"
	"\x6F\x64\x75\x6C\x65\x20\x65\x6E\x64\x0D\x0A\x2B\x2B\x2B\x2B\x2B"
	); 
	
///////////////////////////////////////////////////////////////////////////////////////

RTest TheTest(_L("TAutoDetect"));
	
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//Tests macroses and functions.
//If (!aValue) then the test will be panicked, the test data files will be deleted.
static void Check(TInt aValue, TInt aLine)
	{
	if(!aValue)
		{
		TheTest(EFalse, aLine);
		}
	}
//If (aValue != aExpected) then the test will be panicked, the test data files will be deleted.
static void Check(TInt aValue, TInt aExpected, TInt aLine)
	{
	if(aValue != aExpected)
		{
		RDebug::Print(_L("*** Expected error: %d, got: %d\r\n"), aExpected, aValue);
		TheTest(EFalse, aLine);
		}
	}
//Use these to test conditions.
#define TEST(arg) ::Check((arg), __LINE__)
#define TEST2(aValue, aExpected) ::Check(aValue, aExpected, __LINE__)

/**
* Utility for DEF063276 fix.
*/

_LIT(KLittleEndianFilename, "z:\\test\\data\\KLittleEndian.dat");
_LIT(KBigEndianFilename, "z:\\test\\data\\KBigEndian.dat");

static void ReadDesc(TDes8& aDes, const TDesC& aFilename, RFs& aFs)
	{
	RFile file;
	TInt err = file.Open(aFs, aFilename, EFileRead);
	TEST2(err, KErrNone);
	CleanupClosePushL(file);
	
	err = file.Read(aDes);
	TEST2(err, KErrNone);
	CleanupStack::PopAndDestroy(&file);
	}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
		
const TInt KMinimumThresholdForConvertableCharacter=70;

/**
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0548
@SYMTestCaseDesc        Tests for auto detecting the character set
						Test for CCnvCharacterSetConverter::AutoDetectCharacterSetL() 
@SYMTestPriority        Medium
@SYMTestActions         Attempt to determine the character set of the sample text from those supported on the phone
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void TestAutodetectL(const CArrayFix<CCnvCharacterSetConverter::SCharacterSet>& aArrayOfCharacterSetsAvailable, const TDesC8& aSample, const TUint& aResult)
	{
	TInt Confidence = 0;
	TUint Character = 0;
	CCnvCharacterSetConverter::AutoDetectCharacterSetL (Confidence,Character, aArrayOfCharacterSetsAvailable,aSample);
	TEST(Character==aResult);
	TheTest.Printf(_L("."));
	}

/**
@SYMTestCaseID          SYSLIB-CHARCONV-CT-1307
@SYMTestCaseDesc        Tests for auto detecting the character set
@SYMTestPriority        Medium
@SYMTestActions         Tests for CCnvCharacterSetConverter::AutoDetectCharSetL() 
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void TestAutodetect1L( 
                              const CArrayFix<CCnvCharacterSetConverter::SCharacterSet>& aArrayOfCharacterSetsAvailable,
                              const TDesC8& aSample, 
                              const TUint& aResult,
                              CCnvCharacterSetConverter* aConverter)
	{
	TInt Confidence = 0;
	TUint Character = 0;
	aConverter->AutoDetectCharSetL(Confidence,Character, aArrayOfCharacterSetsAvailable,aSample);
	TEST(Character==aResult);
	TheTest.Printf(_L("."));
	}
/**
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0549
@SYMTestCaseDesc        Tests for CCnvCharacterSetConverter::ConvertibleToCharacterSetL() function
@SYMTestPriority        Medium
@SYMTestActions         Tests the likelihood that a sample is encoded in a CharacterSetIdentifier
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void TestConvertibleToCharacterL(const TUint aCharsetIdentifier, const CArrayFix<CCnvCharacterSetConverter::SCharacterSet>& aArrayOfCharacterSetsAvailable, const TDesC8& aSample, const TInt flag)
	{
	TInt confidence = 0;
	CCnvCharacterSetConverter::ConvertibleToCharacterSetL(confidence,aCharsetIdentifier, aArrayOfCharacterSetsAvailable, aSample);
	if (flag)
		TEST(confidence >= KMinimumThresholdForConvertableCharacter );
	else
		TEST(confidence < KMinimumThresholdForConvertableCharacter );
	}

const TInt KMaxSampleLengthForAutoDetection = 1024;

/**
This test code uses the method as is used by notepad in \Notepad\LibSrc\NpdUtil.cpp

@SYMTestCaseID          SYSLIB-CHARCONV-CT-0550
@SYMTestCaseDesc        Tests to autodetect a character read from file 
@SYMTestPriority        Medium
@SYMTestActions         Tests to determine the character set of the sample text read from a file 
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void TestAutoDetectFromFileL(const TDesC16& aFileName, const TUint& aResult )
	{
	// get file server session and open file
    RFile file;
	RFs fileServerSession;
	CleanupClosePushL(fileServerSession);
	User::LeaveIfError(fileServerSession.Connect());
    User::LeaveIfError(file.Open(fileServerSession, aFileName, EFileRead));
 
	// get up to KMaxSampleLengthForAutoDetection bytes of file for autodetect
	TInt size(0);
    User::LeaveIfError( file.Size(size) );

    TBuf8<KMaxSampleLengthForAutoDetection> sample;
    User::LeaveIfError( file.Read(sample, 
    			size > KMaxSampleLengthForAutoDetection ?  KMaxSampleLengthForAutoDetection : size) );
     
    TInt confidence(0);
    TUint charset(0);
   
    // if the first two bytes say unicode, don't bother with autodetect            
    if ( size >= 2 && 
                ( ( sample[0] == 0xfe && sample[1] == 0xff ) || 
                    ( sample[0] == 0xff && sample[1] == 0xfe ) ) )
    	{
        charset = 0; // Unicode
        }
    else
        {
        //ok, try autodetect, first get available character sets
        CArrayFix<CCnvCharacterSetConverter::SCharacterSet>* newlists =
                    new(ELeave) CArrayFixFlat<CCnvCharacterSetConverter::SCharacterSet> (10);
        CleanupStack::PushL(newlists);
                
        const CArrayFix<CCnvCharacterSetConverter::SCharacterSet>* 
                    lists = CCnvCharacterSetConverter::
                        CreateArrayOfCharacterSetsAvailableLC( fileServerSession );
        
        // for some reason? remove Sms7bit from the list
        const TInt count( lists->Count() );
        for ( TInt i(0); i < count; i++ )
        	{
                    switch ( (*lists)[i].Identifier() )
                        {
                        case KCharacterSetIdentifierSms7Bit:
                            // remove Sms7Bit from newlists
                            break;
                        default:
                            newlists->AppendL((*lists)[i]);
                            break;
                        }
                    }
                    
        // now try AutoDetect            
      	CCnvCharacterSetConverter::AutoDetectCharacterSetL(confidence, charset, *newlists, sample);

	    CleanupStack::PopAndDestroy(2); // filserver, lists	
  		}

 	TheTest.Printf(_L("file %S charset = 0x%x confidence %d expected 0x%x\n"), 
 				&aFileName, charset, confidence, aResult );
   	                
	// check the character set expected was the one autodetected
	TEST(charset==aResult);
               
    CleanupStack::PopAndDestroy(1); // fileserver
	}
/**
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0551
@SYMTestCaseDesc        Tests for conversion of characters read from a file to Unicode
@SYMTestPriority        Medium
@SYMTestActions         Logs out number  of uncoverted bytes left at end,number of uncovertable characters,
						index of first byte of first unconvertible character
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void TestConvertFromFileL(const TDesC16& aFileName, const TUint& aCharacterSetIdentifier )
	{
		// get file server session and open file
    RFile file;
	RFs fileServerSession;
	CleanupClosePushL(fileServerSession);
	User::LeaveIfError(fileServerSession.Connect());
    User::LeaveIfError(file.Open(fileServerSession, aFileName, EFileRead));
 
	// get up to KMaxSampleLengthForAutoDetection bytes of file for autodetect
	TInt size(0);
    User::LeaveIfError( file.Size(size) );

    TBuf8<KMaxSampleLengthForAutoDetection> sample;
    User::LeaveIfError( file.Read(sample, 
    			size > KMaxSampleLengthForAutoDetection ?  KMaxSampleLengthForAutoDetection : size) );
    
 	TheTest.Printf(_L("Comnverting to unicode file %S size = %d \n"), 
 				&aFileName, size );
 				
    TInt NumberOfUnconvertibleCharacters=0;
    TInt IndexOfFirstByteOfFirstUnconvertibleCharacter=0;
    TInt state = CCnvCharacterSetConverter::KStateDefault;
    TBuf16<KMaxSampleLengthForAutoDetection> result;

    CCnvCharacterSetConverter *Converter = CCnvCharacterSetConverter::NewLC();
    TRAPD( ConverterErr, Converter->PrepareToConvertToOrFromL( aCharacterSetIdentifier, fileServerSession)); 
	if ( ConverterErr!= KErrNone )
		{
	 	TheTest.Printf(_L("PrepareToConvertToOrFromL left on file %S ConverterErr = 0x%x \n"), 
 				&aFileName, ConverterErr );
		}
		
	TInt bytesLeft = Converter->ConvertToUnicode( result,
										    sample, 
										    state,
											NumberOfUnconvertibleCharacters,
											IndexOfFirstByteOfFirstUnconvertibleCharacter); 
	 	
	TheTest.Printf(_L("ConvertToUnicode returned %d unconverted bytes left at the end\n"),bytesLeft );
	TheTest.Printf(_L("NumberOfUnconvertibleCharacters=%d \n"),NumberOfUnconvertibleCharacters);
	TheTest.Printf(_L("IndexOfFirstByteOfFirstUnconvertibleCharacter=%d \n"),IndexOfFirstByteOfFirstUnconvertibleCharacter);
	
    CleanupStack::PopAndDestroy(2); // fileserver, CCnvCharacterSetConverter
}

/**
INC056019 	SS NTT - Character set recognition is not optimized.
To improve a performace old static autodetection method was deprecated 
and a new AutoDetectCharSet method introduced. 

@SYMTestCaseID          SYSLIB-CHARCONV-CT-1308
@SYMTestCaseDesc        Performance test for auto detection of characters set
@SYMTestPriority        Medium
@SYMTestActions         Tests for the new AutoDetectCharSet() function
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void TestAutoDetectionPerformanceL(
                const CArrayFix<CCnvCharacterSetConverter::SCharacterSet>* aArrayOfCharacterSetsAvailable)
	{	
	TInt i;	

	/////////////////////////////////////////////////////////////////
	TheTest.Next(_L("Testing ten calls to Static AutoDetection"));
	TTime starttime;
	starttime.UniversalTime();
	for (i=0; i<10; i++)
	    {
	    TheTest.Printf(_L("\n%d run "),i+1);
        TestAutodetectL(*aArrayOfCharacterSetsAvailable,KSomeISO, KCharacterSetIdentifierIso88591);
	    }   
	TTime endtime;
	endtime.UniversalTime();
	TTimeIntervalMicroSeconds difftime=endtime.MicroSecondsFrom(starttime);
	TheTest.Printf(_L("\nTen Static calls duration =%d  microseconds\n\n"), difftime.Int64());

	/////////////////////////////////////////////////////////////////
	TInt charsetCnvCount = aArrayOfCharacterSetsAvailable->Count();
	TInt dllCharsetCnvCount = 0;
	//Count the number of character set converter dlls.
	for(i=0;i<charsetCnvCount;++i)
		{
		const CCnvCharacterSetConverter::SCharacterSet& charset = aArrayOfCharacterSetsAvailable->At(i);
		if(charset.NameIsFileName())
			{
			++dllCharsetCnvCount;
			}
		}
	if(dllCharsetCnvCount == 0)
		{
		TheTest.Printf(_L("No character set converter dlls! Exit subtest.\n"));
		return;
		}

	/////////////////////////////////////////////////////////////////
	CCnvCharacterSetConverter* converter = CCnvCharacterSetConverter::NewLC();

	/////////////////////////////////////////////////////////////////
    TheTest.Next(_L("Testing ten calls to optimized AutoDetection. Non-optimal cache size."));
	converter->SetMaxCacheSize(dllCharsetCnvCount / 2 + 1);
	//Fill the cache
	TestAutodetect1L(*aArrayOfCharacterSetsAvailable,KSomeISO, KCharacterSetIdentifierIso88591,converter);
	//
	starttime.UniversalTime();
    for (i=0; i<10; i++)
	    {
	    TheTest.Printf(_L("\n%d run "),i+1);
        TestAutodetect1L(*aArrayOfCharacterSetsAvailable,KSomeISO, KCharacterSetIdentifierIso88591,converter);
	    }
    endtime.UniversalTime();
	difftime=endtime.MicroSecondsFrom(starttime);
    TheTest.Printf(_L("\nTen non-static calls duration =%d  microseconds\n\n"), difftime.Int64());

	/////////////////////////////////////////////////////////////////
    TheTest.Next(_L("Testing ten calls to optimized AutoDetection. Optimal cache size."));
	converter->SetMaxCacheSize(dllCharsetCnvCount + 1);
	//Fill the cache
	TestAutodetect1L(*aArrayOfCharacterSetsAvailable,KSomeISO, KCharacterSetIdentifierIso88591,converter);
	//
	starttime.UniversalTime();
    for (i=0; i<10; i++)
	    {
	    TheTest.Printf(_L("\n%d run "),i+1);
        TestAutodetect1L(*aArrayOfCharacterSetsAvailable,KSomeISO, KCharacterSetIdentifierIso88591,converter);
	    }
    endtime.UniversalTime();
	difftime=endtime.MicroSecondsFrom(starttime);
    TheTest.Printf(_L("\nTen non-static calls duration =%d  microseconds\n\n"), difftime.Int64());

	/////////////////////////////////////////////////////////////////
    CleanupStack::PopAndDestroy(converter);
	}
/**
@SYMTestCaseID          SYSLIB-CHARCONV-CT-0552
@SYMTestCaseDesc        AutoDetection of character tests  
@SYMTestPriority        Medium
@SYMTestActions         Calls up auto detection conversion test functions
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void DoE32MainL()
	{
	RFs fileServerSession;
	CleanupClosePushL(fileServerSession);
	User::LeaveIfError(fileServerSession.Connect());
	const CArrayFix<CCnvCharacterSetConverter::SCharacterSet>* arrayOfCharacterSetsAvailable=CCnvCharacterSetConverter::CreateArrayOfCharacterSetsAvailableLC(fileServerSession);

	TheTest.Start(_L("About to start the AutoDetection\n"));

	TestConvertibleToCharacterL(KCharacterSetIdentifierUtf8,*arrayOfCharacterSetsAvailable,KUTF8,1);
	TestConvertibleToCharacterL(KCharacterSetIdentifierAscii,*arrayOfCharacterSetsAvailable,KASCII,1);
	TestConvertibleToCharacterL(KCharacterSetIdentifierUnicodeBig,*arrayOfCharacterSetsAvailable,KUnicode,1);
	TestConvertibleToCharacterL(KCharacterSetIdentifierUnicodeBig,*arrayOfCharacterSetsAvailable,KUnicode3,1);
	TestConvertibleToCharacterL(KCharacterSetIdentifierShiftJis,*arrayOfCharacterSetsAvailable,KSJISPhrase,1);
	TestConvertibleToCharacterL(KCharacterSetIdentifierShiftJis,*arrayOfCharacterSetsAvailable,KSJISPhrase,1);
	TestConvertibleToCharacterL(KCharacterSetIdentifierGb2312,*arrayOfCharacterSetsAvailable,GB2312B,1);
	TestConvertibleToCharacterL(KCharacterSetIdentifierEucJpPacked,*arrayOfCharacterSetsAvailable,KEUC2,1);
	TestConvertibleToCharacterL(KCharacterSetIdentifierEucJpPacked,*arrayOfCharacterSetsAvailable,KEUP,1);
	TestConvertibleToCharacterL(KCharacterSetIdentifierIso88591,*arrayOfCharacterSetsAvailable,KSomeISO,1);
	TestConvertibleToCharacterL(KCharacterSetIdentifierIso88591,*arrayOfCharacterSetsAvailable,KISODEF,1);
	TestConvertibleToCharacterL(KCharacterSetIdentifierCodePage1252,*arrayOfCharacterSetsAvailable,KISODEF,0);


	TestConvertibleToCharacterL(KCharacterSetIdentifierEucJpPacked,*arrayOfCharacterSetsAvailable,KUTF8,0);
	TestConvertibleToCharacterL(KCharacterSetIdentifierHz,*arrayOfCharacterSetsAvailable,KASCII,0);
	TestConvertibleToCharacterL(KCharacterSetIdentifierCodePage1252,*arrayOfCharacterSetsAvailable,KUnicode,0);
	TestConvertibleToCharacterL(KCharacterSetIdentifierSms7Bit,*arrayOfCharacterSetsAvailable,KUnicode3,0);
	TestConvertibleToCharacterL(KCharacterSetIdentifierSms7Bit,*arrayOfCharacterSetsAvailable,KSJISPhrase,0);
	TestConvertibleToCharacterL(KCharacterSetIdentifierIso2022Jp,*arrayOfCharacterSetsAvailable,KSJISPhrase,0);
	TestConvertibleToCharacterL(KCharacterSetIdentifierIso2022Jp,*arrayOfCharacterSetsAvailable,GB2312B,0);
	TestConvertibleToCharacterL(KCharacterSetIdentifierIso2022Jp,*arrayOfCharacterSetsAvailable,KEUC2,0);
	TestConvertibleToCharacterL(KCharacterSetIdentifierIso2022Jp,*arrayOfCharacterSetsAvailable,KEUP,0);
	TestConvertibleToCharacterL(KCharacterSetIdentifierEucJpPacked,*arrayOfCharacterSetsAvailable,KSomeISO,0);
	TestConvertibleToCharacterL(KCharacterSetIdentifierEucJpPacked,*arrayOfCharacterSetsAvailable,KUnicodeFail,0);

	TestAutodetectL(*arrayOfCharacterSetsAvailable,KEUP,KCharacterSetIdentifierEucJpPacked);
	TestAutodetectL(*arrayOfCharacterSetsAvailable,KEUC2,KCharacterSetIdentifierEucJpPacked);
	TestAutodetectL(*arrayOfCharacterSetsAvailable,KUnicode,KCharacterSetIdentifierUnicodeLittle);
	TestAutodetectL(*arrayOfCharacterSetsAvailable,KUnicode2,KCharacterSetIdentifierUnicodeLittle);
	TestAutodetectL(*arrayOfCharacterSetsAvailable,KUnicode3,KCharacterSetIdentifierUnicodeBig);
	TestAutodetectL(*arrayOfCharacterSetsAvailable,KSJISPhrase,KCharacterSetIdentifierShiftJis);
	TestAutodetectL(*arrayOfCharacterSetsAvailable,KDodgyShiftJIS,KCharacterSetIdentifierShiftJis);
	TestAutodetectL(*arrayOfCharacterSetsAvailable,KDodgyShiftJIS2,KCharacterSetIdentifierShiftJis);
	TestAutodetectL(*arrayOfCharacterSetsAvailable,KDodgyShiftJIS3,KCharacterSetIdentifierShiftJis);
	TestAutodetectL(*arrayOfCharacterSetsAvailable,KBig5,KCharacterSetIdentifierBig5);
	TestAutodetectL(*arrayOfCharacterSetsAvailable,KSJIS,KCharacterSetIdentifierShiftJis);
	TestAutodetectL(*arrayOfCharacterSetsAvailable,KASCII,KCharacterSetIdentifierAscii);
	TestAutodetectL(*arrayOfCharacterSetsAvailable,SJISNET,KCharacterSetIdentifierShiftJis);
	TestAutodetectL(*arrayOfCharacterSetsAvailable,BIG5A,KCharacterSetIdentifierBig5);
	TestAutodetectL(*arrayOfCharacterSetsAvailable,BIG5C,KCharacterSetIdentifierBig5);
	TestAutodetectL(*arrayOfCharacterSetsAvailable,KUTF8,KCharacterSetIdentifierUtf8);
	TestAutodetectL(*arrayOfCharacterSetsAvailable,BIG5Corrupt,KCharacterSetIdentifierBig5);
	TestAutodetectL(*arrayOfCharacterSetsAvailable,BIG5Ahalf,KCharacterSetIdentifierBig5);
	TestAutodetectL(*arrayOfCharacterSetsAvailable,GB2312B,KCharacterSetIdentifierGbk);
	TestAutodetectL(*arrayOfCharacterSetsAvailable,GB2312C,KCharacterSetIdentifierGbk);
	TestAutodetectL(*arrayOfCharacterSetsAvailable,GB2312Corrupt,KCharacterSetIdentifierGbk);
	TestAutodetectL(*arrayOfCharacterSetsAvailable,KISO, KCharacterSetIdentifierIso88591);
	TestAutodetectL(*arrayOfCharacterSetsAvailable,KSomeISO, KCharacterSetIdentifierIso88591);

	//test for INC037743 - Charconv recognises Little Endian as Big Endian
	
	// Fix for DEF063276.
		
	TBuf8<300> buf;
	
	ReadDesc(buf, KLittleEndianFilename, fileServerSession);	
	TestAutodetectL(*arrayOfCharacterSetsAvailable,buf, KCharacterSetIdentifierUnicodeLittle);
	
	ReadDesc(buf, KBigEndianFilename, fileServerSession);
	TestAutodetectL(*arrayOfCharacterSetsAvailable,buf, KCharacterSetIdentifierUnicodeBig);

	// End fix
	
  	// test for INC037705 - SS66 - Charconv autodetect recognises Swedish as Shift-JIS
  	// These tests currently fail as the test detects KCharacterSetIdentifierShiftJis. 
  	// This defect was rejected, so the test code has been commented out
  	// TestAutodetectL(test,*arrayOfCharacterSetsAvailable,KInc037705, KCharacterSetIdentifierShiftJis);

	// tests for INC037581 - SS66 - Long .txt note fails to open in msg centre inbox
	TestAutodetectL(*arrayOfCharacterSetsAvailable,KFinnish, KCharacterSetIdentifierIso88591);
	TestAutodetectL(*arrayOfCharacterSetsAvailable,KSwedish, KCharacterSetIdentifierIso88591);

	// tests for INC043016 - AV21 via BTH received TXT file could not be opened
	TestAutodetectL(*arrayOfCharacterSetsAvailable,KGotcha, KCharacterSetIdentifierUtf8);
	
	//test for INC037705 read in file and try to autodetect()
#ifdef __WINS__
	TestAutoDetectFromFileL(_L("C:\\test\\data\\finnish.txt"), KCharacterSetIdentifierIso88591);
	TestAutoDetectFromFileL(_L("C:\\test\\data\\swedish.txt"), KCharacterSetIdentifierIso88591);
#else
	TestAutoDetectFromFileL(_L("Z:\\test\\data\\finnish.txt"), KCharacterSetIdentifierIso88591);
	TestAutoDetectFromFileL(_L("Z:\\test\\data\\swedish.txt"), KCharacterSetIdentifierIso88591);
#endif

	
	//test for INC037705: read in file and try to convertToUnicode()
#ifdef __WINS__
	TestConvertFromFileL(_L("C:\\test\\data\\finnish.txt"), KCharacterSetIdentifierIso88591);
	TestConvertFromFileL(_L("C:\\test\\data\\swedish.txt"), KCharacterSetIdentifierIso88591);
#else
	TestConvertFromFileL(_L("Z:\\test\\data\\finnish.txt"), KCharacterSetIdentifierIso88591);
	TestConvertFromFileL(_L("Z:\\test\\data\\swedish.txt"), KCharacterSetIdentifierIso88591);
#endif

    TestAutoDetectionPerformanceL(arrayOfCharacterSetsAvailable);
	
	TheTest.Printf(_L("\n"));
	CleanupStack::PopAndDestroy(2);
	}


GLDEF_C TInt E32Main()
	{
	__UHEAP_MARK;

	TheTest.Title();

	CTrapCleanup* trapCleanup=CTrapCleanup::New();
	TEST(trapCleanup != NULL);

	TRAPD(error, DoE32MainL());
	TEST2(error, KErrNone);

	delete trapCleanup;

	TheTest.End();
	TheTest.Close();

	__UHEAP_MARKEND;
	return KErrNone;
	}
