#
# Copyright (c) 1997-2004 Nokia Corporation and/or its subsidiary(-ies).
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


# TARGET_DIRECTORY2 and TARGET_FILES2

!if "$(PLATFORM)"=="WINS" || "$(PLATFORM)"=="WINSCW"
TARGET_DIRECTORY=$(EPOCROOT)epoc32\$(PLATFORM)\c\resource\charconv
!else
TARGET_DIRECTORY=$(EPOCROOT)epoc32\data\z\resource\charconv
!endif

TARGET_FILES=$(TARGET_DIRECTORY)\TSNM.SNM

SOURCE_DIRECTORY=..\..\..\test\data\main

TOOLS=\
	$(EPOCROOT)epoc32\tools\UIDCRC.EXE \
	$(EPOCROOT)epoc32\tools\PARSER.PM \
	$(EPOCROOT)epoc32\tools\WRITER.PM \
	$(EPOCROOT)epoc32\tools\SNMTOOL.PL

$(TARGET_DIRECTORY) :
	@perl -S emkdir.pl "$@\\"

$(TARGET_DIRECTORY)\TSNM.SNM : $(SOURCE_DIRECTORY)\TSNM.TXT $(TOOLS)
	@call SNMTOOL $(SOURCE_DIRECTORY)\TSNM.TXT $@

DO_NOTHING :
	@rem do nothing

# the targets below are the public ones

MAKMAKE : DO_NOTHING

BLD : $(TARGET_DIRECTORY) $(TARGET_FILES)

SAVESPACE : BLD

FREEZE : DO_NOTHING

LIB : DO_NOTHING

CLEANLIB : DO_NOTHING

RESOURCE : DO_NOTHING

CLEAN : 
	-@erase $(TARGET_FILES)

RELEASABLES : 
	@echo $(TARGET_FILES)

FINAL : DO_NOTHING

