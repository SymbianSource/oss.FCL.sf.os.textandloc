#
# Copyright (c) 2000 Nokia Corporation and/or its subsidiary(-ies).
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


TARGET_DIRECTORY=..\Source\generatedcpp
TARGET_DIRECTORY2=..\data\generateddat\charconv
SOURCE_DIRECTORY=..\data

TARGET_CPP_FILES=\
	$(TARGET_DIRECTORY)\g_gb2312.cpp \
	$(TARGET_DIRECTORY)\g_gb12345.cpp \
	$(TARGET_DIRECTORY)\g_gbk.cpp \
	$(TARGET_DIRECTORY)\g_big5.cpp \
	$(TARGET_DIRECTORY)\g_jisx0201.cpp \
	$(TARGET_DIRECTORY)\g_jisx0208.cpp \
	$(TARGET_DIRECTORY)\g_jisx0212.cpp \
	$(TARGET_DIRECTORY)\g_iso88592.cpp \
	$(TARGET_DIRECTORY)\g_iso88593.cpp \
	$(TARGET_DIRECTORY)\g_iso88594.cpp \
	$(TARGET_DIRECTORY)\g_iso88595.cpp \
	$(TARGET_DIRECTORY)\g_iso88596.cpp \
	$(TARGET_DIRECTORY)\g_iso88597.cpp \
	$(TARGET_DIRECTORY)\g_iso88598.cpp \
	$(TARGET_DIRECTORY)\g_iso88599.cpp \
	$(TARGET_DIRECTORY)\g_iso885910.cpp \
	$(TARGET_DIRECTORY)\g_iso885913.cpp \
	$(TARGET_DIRECTORY)\g_iso885914.cpp \
	$(TARGET_DIRECTORY)\g_iso885915.cpp \
	$(TARGET_DIRECTORY)\g_shiftjisdirectmap.cpp \
	$(TARGET_DIRECTORY)\g_turkish_locking_gsm7ext.cpp \
	$(TARGET_DIRECTORY)\g_turkish_locking_single.cpp \
	$(TARGET_DIRECTORY)\g_gsm7_turkish_single.cpp

TARGET_DAT_FILES=\
	$(TARGET_DIRECTORY2)\big5.dat \
	$(TARGET_DIRECTORY2)\gb2312.dat \
	$(TARGET_DIRECTORY2)\gbk.dat \
	$(TARGET_DIRECTORY2)\gb12345.dat \
	$(TARGET_DIRECTORY2)\cp1252.dat \
	$(TARGET_DIRECTORY2)\iso88591.dat \
	$(TARGET_DIRECTORY2)\iso88592.dat \
	$(TARGET_DIRECTORY2)\iso88593.dat \
	$(TARGET_DIRECTORY2)\iso88594.dat \
	$(TARGET_DIRECTORY2)\iso88595.dat \
	$(TARGET_DIRECTORY2)\iso88596.dat \
	$(TARGET_DIRECTORY2)\iso88597.dat \
	$(TARGET_DIRECTORY2)\iso88598.dat \
	$(TARGET_DIRECTORY2)\iso88599.dat \
	$(TARGET_DIRECTORY2)\iso885910.dat \
	$(TARGET_DIRECTORY2)\iso885913.dat \
	$(TARGET_DIRECTORY2)\iso885914.dat \
	$(TARGET_DIRECTORY2)\iso885915.dat \
	$(TARGET_DIRECTORY2)\shiftjis.dat \
	$(TARGET_DIRECTORY2)\shiftjisdirectmap.dat \
	$(TARGET_DIRECTORY2)\turkish_locking_gsm7ext.dat \
	$(TARGET_DIRECTORY2)\turkish_locking_single.dat \
	$(TARGET_DIRECTORY2)\gsm7_turkish_single.dat

TARGET_FILES=\
	$(TARGET_CPP_FILES) \
	$(TARGET_DAT_FILES)

TOOLS=\
	$(EPOCROOT)epoc32\tools\uidcrc.exe \
	$(EPOCROOT)epoc32\tools\parser.pm \
	$(EPOCROOT)epoc32\tools\writer.pm \
	$(EPOCROOT)epoc32\tools\cnvtool.pl

$(TARGET_DIRECTORY) :
	@perl -S emkdir.pl "$(TARGET_DIRECTORY)"

$(TARGET_DIRECTORY2) :
	@perl -S emkdir.pl "$(TARGET_DIRECTORY2)"

$(TARGET_DIRECTORY)\g_gb2312.cpp : $(SOURCE_DIRECTORY)\gb2312.ctl $(SOURCE_DIRECTORY)\gb2312.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\gb2312.ctl $(SOURCE_DIRECTORY)\gb2312.txt $@ -generateSourceCode

$(TARGET_DIRECTORY)\g_gb12345.cpp : $(SOURCE_DIRECTORY)\gb12345.ctl $(SOURCE_DIRECTORY)\gb12345.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\gb12345.ctl $(SOURCE_DIRECTORY)\gb12345.txt $@ -generateSourceCode

$(TARGET_DIRECTORY)\g_gbk.cpp : $(SOURCE_DIRECTORY)\gbk.ctl $(SOURCE_DIRECTORY)\gbk.txt $(TOOLS) $(SOURCE_DIRECTORY)\gb2312.txt
	@call cnvtool $(SOURCE_DIRECTORY)\gbk.ctl $(SOURCE_DIRECTORY)\gbk.txt $@ -generateSourceCode -cutOutAnyPrivateUseUnicodeCharacterSlotsBeingUsed -sourceFilesToSubtract($(SOURCE_DIRECTORY)\gb2312.txt)

$(TARGET_DIRECTORY)\g_big5.cpp : $(SOURCE_DIRECTORY)\big5.ctl $(SOURCE_DIRECTORY)\BIG5.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\big5.ctl $(SOURCE_DIRECTORY)\big5.txt $@ -generateSourceCode

$(TARGET_DIRECTORY)\g_jisx0201.cpp : $(SOURCE_DIRECTORY)\jisx0201.ctl $(SOURCE_DIRECTORY)\jisx0201.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\jisx0201.ctl $(SOURCE_DIRECTORY)\jisx0201.txt $@ -generateSourceCode -omitReplacementForUnconvertibleUnicodeCharacters

$(TARGET_DIRECTORY)\g_jisx0208.cpp : $(SOURCE_DIRECTORY)\jisx0208.ctl $(SOURCE_DIRECTORY)\jisx0208.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\jisx0208.ctl $(SOURCE_DIRECTORY)\jisx0208.txt $@ -generateSourceCode -columns(3: 2, 3) -omitReplacementForUnconvertibleUnicodeCharacters

$(TARGET_DIRECTORY)\g_jisx0212.cpp : $(SOURCE_DIRECTORY)\jisx0212.ctl $(SOURCE_DIRECTORY)\jisx0212.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\jisx0212.ctl $(SOURCE_DIRECTORY)\jisx0212.txt $@ -generateSourceCode -omitReplacementForUnconvertibleUnicodeCharacters

$(TARGET_DIRECTORY)\g_iso88592.cpp : $(SOURCE_DIRECTORY)\iso88592.ctl $(SOURCE_DIRECTORY)\iso88592.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\iso88592.ctl $(SOURCE_DIRECTORY)\iso88592.txt $@ -generateSourceCode

$(TARGET_DIRECTORY)\g_iso88593.cpp : $(SOURCE_DIRECTORY)\iso88593.ctl $(SOURCE_DIRECTORY)\iso88593.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\iso88593.ctl $(SOURCE_DIRECTORY)\iso88593.txt $@ -generateSourceCode

$(TARGET_DIRECTORY)\g_iso88594.cpp : $(SOURCE_DIRECTORY)\iso88594.ctl $(SOURCE_DIRECTORY)\iso88594.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\iso88594.ctl $(SOURCE_DIRECTORY)\iso88594.txt $@ -generateSourceCode

$(TARGET_DIRECTORY)\g_iso88595.cpp : $(SOURCE_DIRECTORY)\iso88595.ctl $(SOURCE_DIRECTORY)\iso88595.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\iso88595.ctl $(SOURCE_DIRECTORY)\iso88595.txt $@ -generateSourceCode

$(TARGET_DIRECTORY)\g_iso88596.cpp : $(SOURCE_DIRECTORY)\iso88596.ctl $(SOURCE_DIRECTORY)\iso88596.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\iso88596.ctl $(SOURCE_DIRECTORY)\iso88596.txt $@ -generateSourceCode

$(TARGET_DIRECTORY)\g_iso88597.cpp : $(SOURCE_DIRECTORY)\iso88597.ctl $(SOURCE_DIRECTORY)\iso88597.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\iso88597.ctl $(SOURCE_DIRECTORY)\iso88597.txt $@ -generateSourceCode

$(TARGET_DIRECTORY)\g_iso88598.cpp : $(SOURCE_DIRECTORY)\iso88598.ctl $(SOURCE_DIRECTORY)\iso88598.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\iso88598.ctl $(SOURCE_DIRECTORY)\iso88598.txt $@ -generateSourceCode

$(TARGET_DIRECTORY)\g_iso88599.cpp : $(SOURCE_DIRECTORY)\iso88599.ctl $(SOURCE_DIRECTORY)\iso88599.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\iso88599.ctl $(SOURCE_DIRECTORY)\iso88599.txt $@ -generateSourceCode

$(TARGET_DIRECTORY)\g_iso885910.cpp : $(SOURCE_DIRECTORY)\iso885910.ctl $(SOURCE_DIRECTORY)\iso885910.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\iso885910.ctl $(SOURCE_DIRECTORY)\iso885910.txt $@ -generateSourceCode

$(TARGET_DIRECTORY)\g_iso885913.cpp : $(SOURCE_DIRECTORY)\iso885913.ctl $(SOURCE_DIRECTORY)\iso885913.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\iso885913.ctl $(SOURCE_DIRECTORY)\iso885913.txt $@ -generateSourceCode

$(TARGET_DIRECTORY)\g_iso885914.cpp : $(SOURCE_DIRECTORY)\iso885914.ctl $(SOURCE_DIRECTORY)\iso885914.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\iso885914.ctl $(SOURCE_DIRECTORY)\iso885914.txt $@ -generateSourceCode

$(TARGET_DIRECTORY)\g_iso885915.cpp : $(SOURCE_DIRECTORY)\iso885915.ctl $(SOURCE_DIRECTORY)\iso885915.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\iso885915.ctl $(SOURCE_DIRECTORY)\iso885915.txt $@ -generateSourceCode

$(TARGET_DIRECTORY)\g_shiftjisdirectmap.cpp : $(SOURCE_DIRECTORY)\shiftjisdirectmap.ctl $(SOURCE_DIRECTORY)\shiftjisdirectmap.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\shiftjisdirectmap.ctl $(SOURCE_DIRECTORY)\shiftjisdirectmap.txt $@ -generateSourceCode

$(TARGET_DIRECTORY)\g_turkish_locking_gsm7ext.cpp : $(SOURCE_DIRECTORY)\turkish_locking_gsm7ext.ctl $(SOURCE_DIRECTORY)\turkish_locking_gsm7ext.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\turkish_locking_gsm7ext.ctl $(SOURCE_DIRECTORY)\turkish_locking_gsm7ext.txt $@ -generateSourceCode

$(TARGET_DIRECTORY)\g_turkish_locking_single.cpp : $(SOURCE_DIRECTORY)\turkish_locking_single.ctl $(SOURCE_DIRECTORY)\turkish_locking_single.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\turkish_locking_single.ctl $(SOURCE_DIRECTORY)\turkish_locking_single.txt $@ -generateSourceCode

$(TARGET_DIRECTORY)\g_gsm7_turkish_single.cpp : $(SOURCE_DIRECTORY)\gsm7_turkish_single.ctl $(SOURCE_DIRECTORY)\gsm7_turkish_single.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\gsm7_turkish_single.ctl $(SOURCE_DIRECTORY)\gsm7_turkish_single.txt $@ -generateSourceCode

$(TARGET_DIRECTORY2)\big5.dat : $(SOURCE_DIRECTORY)\big5.ctl $(SOURCE_DIRECTORY)\big5.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\big5.ctl $(SOURCE_DIRECTORY)\big5.txt $@ -flattenHashAndSave

$(TARGET_DIRECTORY2)\gb2312.dat : $(SOURCE_DIRECTORY)\gb2312.ctl $(SOURCE_DIRECTORY)\gb2312.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\gb2312.ctl $(SOURCE_DIRECTORY)\gb2312.txt $@ -flattenHashAndSave

$(TARGET_DIRECTORY2)\gbk.dat : $(SOURCE_DIRECTORY)\gbkf.ctl $(SOURCE_DIRECTORY)\gbk.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\gbkf.ctl $(SOURCE_DIRECTORY)\gbk.txt $@ -flattenHashAndSave -cutOutAnyPrivateUseUnicodeCharacterSlotsBeingUsed

$(TARGET_DIRECTORY2)\gb12345.dat : $(SOURCE_DIRECTORY)\gb12345.ctl $(SOURCE_DIRECTORY)\gb12345.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\gb12345.ctl $(SOURCE_DIRECTORY)\gb12345.txt $@ -flattenHashAndSave

$(TARGET_DIRECTORY2)\iso885910.dat : $(SOURCE_DIRECTORY)\iso885910.ctl $(SOURCE_DIRECTORY)\iso885910.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\iso885910.ctl $(SOURCE_DIRECTORY)\iso885910.txt $@ -flattenHashAndSave

$(TARGET_DIRECTORY2)\iso885913.dat : $(SOURCE_DIRECTORY)\iso885913.ctl $(SOURCE_DIRECTORY)\iso885913.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\iso885913.ctl $(SOURCE_DIRECTORY)\iso885913.txt $@ -flattenHashAndSave

$(TARGET_DIRECTORY2)\iso885914.dat : $(SOURCE_DIRECTORY)\iso885914.ctl $(SOURCE_DIRECTORY)\iso885914.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\iso885914.ctl $(SOURCE_DIRECTORY)\iso885914.txt $@ -flattenHashAndSave

$(TARGET_DIRECTORY2)\iso885915.dat : $(SOURCE_DIRECTORY)\iso885915.ctl $(SOURCE_DIRECTORY)\iso885915.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\iso885915.ctl $(SOURCE_DIRECTORY)\iso885915.txt $@ -flattenHashAndSave

$(TARGET_DIRECTORY2)\cp1252.dat : $(SOURCE_DIRECTORY)\cp1252.ctl $(SOURCE_DIRECTORY)\cp1252.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\cp1252.ctl $(SOURCE_DIRECTORY)\cp1252.txt $@ -flattenHashAndSave

$(TARGET_DIRECTORY2)\iso88591.dat : $(SOURCE_DIRECTORY)\iso88591.ctl $(SOURCE_DIRECTORY)\iso88591.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\iso88591.ctl $(SOURCE_DIRECTORY)\iso88591.txt $@ -flattenHashAndSave

$(TARGET_DIRECTORY2)\iso88592.dat : $(SOURCE_DIRECTORY)\iso88592.ctl $(SOURCE_DIRECTORY)\iso88592.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\iso88592.ctl $(SOURCE_DIRECTORY)\iso88592.txt $@ -flattenHashAndSave

$(TARGET_DIRECTORY2)\iso88593.dat : $(SOURCE_DIRECTORY)\iso88593.ctl $(SOURCE_DIRECTORY)\iso88593.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\iso88593.ctl $(SOURCE_DIRECTORY)\iso88593.txt $@ -flattenHashAndSave

$(TARGET_DIRECTORY2)\iso88594.dat : $(SOURCE_DIRECTORY)\iso88594.ctl $(SOURCE_DIRECTORY)\iso88594.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\iso88594.ctl $(SOURCE_DIRECTORY)\iso88594.txt $@ -flattenHashAndSave

$(TARGET_DIRECTORY2)\iso88595.dat : $(SOURCE_DIRECTORY)\iso88595.ctl $(SOURCE_DIRECTORY)\iso88595.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\iso88595.ctl $(SOURCE_DIRECTORY)\iso88595.txt $@ -flattenHashAndSave

$(TARGET_DIRECTORY2)\iso88596.dat : $(SOURCE_DIRECTORY)\iso88596.ctl $(SOURCE_DIRECTORY)\iso88596.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\iso88596.ctl $(SOURCE_DIRECTORY)\iso88596.txt $@ -flattenHashAndSave

$(TARGET_DIRECTORY2)\iso88597.dat : $(SOURCE_DIRECTORY)\iso88597.ctl $(SOURCE_DIRECTORY)\iso88597.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\iso88597.ctl $(SOURCE_DIRECTORY)\iso88597.txt $@ -flattenHashAndSave

$(TARGET_DIRECTORY2)\iso88598.dat : $(SOURCE_DIRECTORY)\iso88598.ctl $(SOURCE_DIRECTORY)\iso88598.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\iso88598.ctl $(SOURCE_DIRECTORY)\iso88598.txt $@ -flattenHashAndSave

$(TARGET_DIRECTORY2)\iso88599.dat : $(SOURCE_DIRECTORY)\iso88599.ctl $(SOURCE_DIRECTORY)\iso88599.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\iso88599.ctl $(SOURCE_DIRECTORY)\iso88599.txt $@ -flattenHashAndSave

$(TARGET_DIRECTORY2)\shiftjis.dat : $(SOURCE_DIRECTORY)\shiftjis.ctl $(SOURCE_DIRECTORY)\shiftjis.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\shiftjis.ctl $(SOURCE_DIRECTORY)\shiftjis.txt $@ -flattenHashAndSave

$(TARGET_DIRECTORY2)\shiftjisdirectmap.dat : $(SOURCE_DIRECTORY)\shiftjisdirectmap.ctl $(SOURCE_DIRECTORY)\shiftjisdirectmap.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\shiftjisdirectmap.ctl $(SOURCE_DIRECTORY)\shiftjisdirectmap.txt $@ -flattenHashAndSave

$(TARGET_DIRECTORY2)\turkish_locking_gsm7ext.dat : $(SOURCE_DIRECTORY)\turkish_locking_gsm7ext.ctl $(SOURCE_DIRECTORY)\turkish_locking_gsm7ext.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\turkish_locking_gsm7ext.ctl $(SOURCE_DIRECTORY)\turkish_locking_gsm7ext.txt $@ -flattenHashAndSave

$(TARGET_DIRECTORY2)\turkish_locking_single.dat : $(SOURCE_DIRECTORY)\turkish_locking_single.ctl $(SOURCE_DIRECTORY)\turkish_locking_single.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\turkish_locking_single.ctl $(SOURCE_DIRECTORY)\turkish_locking_single.txt $@ -flattenHashAndSave

$(TARGET_DIRECTORY2)\gsm7_turkish_single.dat : $(SOURCE_DIRECTORY)\gsm7_turkish_single.ctl $(SOURCE_DIRECTORY)\gsm7_turkish_single.txt $(TOOLS)
	@call cnvtool $(SOURCE_DIRECTORY)\gsm7_turkish_single.ctl $(SOURCE_DIRECTORY)\gsm7_turkish_single.txt $@ -flattenHashAndSave

DO_NOTHING :
	@rem do nothing

# the targets below are the public ones

MAKMAKE : $(TARGET_DIRECTORY) $(TARGET_DIRECTORY2) $(TARGET_FILES)

BLD : $(TARGET_DIRECTORY) $(TARGET_DIRECTORY2) $(TARGET_FILES)

SAVESPACE : BLD

FREEZE : DO_NOTHING

LIB : DO_NOTHING

CLEANLIB : DO_NOTHING

RESOURCE : DO_NOTHING

CLEAN :
	-@erase $(TARGET_CPP_FILES)
	-@erase $(TARGET_DAT_FILES)

RELEASABLES : 
	@echo $(TARGET_DAT_FILES)

FINAL : DO_NOTHING

