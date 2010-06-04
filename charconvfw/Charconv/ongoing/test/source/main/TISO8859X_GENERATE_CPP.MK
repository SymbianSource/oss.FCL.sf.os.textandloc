#
# Copyright (c) 8859 Nokia Corporation and/or its subsidiary(-ies).
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

TARGET_DIRECTORY=..\..\..\test\source\main

TEXT_FILE_DIRECTORY=..\..\..\data

TARGET_CPP_FILES=\
	$(TARGET_DIRECTORY)\G_TISO8859X.CPP

TOOLS=\
	..\..\..\test\source\main\TISO8859X_GENERATE_CPP.PL

$(TARGET_DIRECTORY) :
	@if not exist "..\..\..\test" md "..\..\..\test"
	@if not exist "..\..\..\test\source" md "..\..\..\test\source"
	@if not exist "..\..\..\test\source\main" md "..\..\..\test\source\main"

$(TARGET_DIRECTORY)\G_TISO8859X.CPP : $(TOOLS) $(TEXT_FILE_DIRECTORY)\ISO88592.TXT $(TEXT_FILE_DIRECTORY)\ISO88593.TXT $(TEXT_FILE_DIRECTORY)\ISO88594.TXT $(TEXT_FILE_DIRECTORY)\ISO88595.TXT $(TEXT_FILE_DIRECTORY)\ISO88596.TXT $(TEXT_FILE_DIRECTORY)\ISO88597.TXT $(TEXT_FILE_DIRECTORY)\ISO88598.TXT $(TEXT_FILE_DIRECTORY)\ISO88599.TXT $(TEXT_FILE_DIRECTORY)\ISO885910.TXT $(TEXT_FILE_DIRECTORY)\ISO885913.TXT $(TEXT_FILE_DIRECTORY)\ISO885914.TXT $(TEXT_FILE_DIRECTORY)\ISO885915.TXT
	@perl -w ..\..\..\test\source\main\TISO8859X_GENERATE_CPP.PL

DO_NOTHING :
	@rem do nothing

# the targets below are the public ones

MAKMAKE : $(TARGET_DIRECTORY) $(TARGET_CPP_FILES)

BLD : $(TARGET_DIRECTORY) $(TARGET_CPP_FILES)

SAVESPACE : BLD

FREEZE : DO_NOTHING

LIB : DO_NOTHING

CLEANLIB : DO_NOTHING

RESOURCE : DO_NOTHING

CLEAN : 
	-@erase $(TARGET_CPP_FILES)

RELEASABLES : 
	@echo $(TARGET_CPP_FILES)

FINAL : DO_NOTHING

