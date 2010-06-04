# ISO88591.CTL
#
# Copyright (c) 1997-2000 Nokia Corporation and/or its subsidiary(-ies).
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

Endianness															FixedBigEndian
ReplacementForUnconvertibleUnicodeCharacters						0x1a # ASCII "substitute" character - must be a single character, and must be little-endian if the "Endianness" above is "Unspecified", otherwise in the same endianness as specified

StartForeignVariableByteData
#	FirstInitialByteValueInRange	LastInitialByteValueInRange		NumberOfSubsequentBytes
	0x00							0xff							0
EndForeignVariableByteData

StartForeignToUnicodeData
#	IncludePriority	SearchPriority	FirstInputCharacterCodeInRange	LastInputCharacterCodeInRange	Algorithm						Parameters
	2				2				0x00							0x7f							Direct							{}		# ASCII
	1				1				0x80							0x80							Offset							{}		# Euro Character
	1				1				0x81							0xff							Direct							{}	
EndForeignToUnicodeData

StartUnicodeToForeignData
#	IncludePriority	SearchPriority	FirstInputCharacterCodeInRange	LastInputCharacterCodeInRange	Algorithm			SizeOfOutputCharacterCodeInBytes	Parameters
	2				2				0x0000							0x007f							Direct				1									{}		# ASCII
	1				1				0x0081							0x00ff							Direct				1									{}
EndUnicodeToForeignData

