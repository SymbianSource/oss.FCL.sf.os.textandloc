rem
rem Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
rem All rights reserved.
rem This component and the accompanying materials are made available
rem under the terms of the License "Eclipse Public License v1.0"
rem which accompanies this distribution, and is available
rem at the URL "http://www.eclipse.org/legal/epl-v10.html".
rem
rem Initial Contributors:
rem Nokia Corporation - initial contribution.
rem
rem Contributors:
rem
rem Description:      
rem

@echo off

rem TEST.BAT
rem
rem Copyright (c) 2000 Symbian Ltd.  All rights reserved.
rem

if not "%1"=="" goto %1

call %0 testall unicode \charconv\test\data\tool\LE.UNI utf8 \charconv\test\data\tool\UNICODE.UT8 -little
call %0 testall unicode \charconv\test\data\tool\LE_BOM.UNI utf8 \charconv\test\data\tool\UNICODE.UT8 -little -byteordermark
call %0 testall unicode \charconv\test\data\tool\BE.UNI utf8 \charconv\test\data\tool\UNICODE.UT8 -big
call %0 testall unicode \charconv\test\data\tool\BE_BOM.UNI utf8 \charconv\test\data\tool\UNICODE.UT8 -big -byteordermark

call %0 testall shiftjis \charconv\test\data\tool\SHIFTJIS.TXT utf8 \charconv\test\data\tool\SHIFTJIS.UT8

call %0 testoneway cp1252 \charconv\test\data\tool\ALL_BYTES.TXT unicode \charconv\test\data\tool\CP1252.UNI -little
call %0 testoneway iso88591 \charconv\test\data\tool\ALL_BYTES.TXT unicode \charconv\test\data\tool\ISO88591.UNI -little
call %0 testoneway iso88592 \charconv\test\data\tool\ALL_BYTES.TXT unicode \charconv\test\data\tool\ISO88592.UNI -little
call %0 testoneway iso88593 \charconv\test\data\tool\ALL_BYTES.TXT unicode \charconv\test\data\tool\ISO88593.UNI -little
call %0 testoneway iso88594 \charconv\test\data\tool\ALL_BYTES.TXT unicode \charconv\test\data\tool\ISO88594.UNI -little
call %0 testoneway iso88595 \charconv\test\data\tool\ALL_BYTES.TXT unicode \charconv\test\data\tool\ISO88595.UNI -little
call %0 testoneway iso88596 \charconv\test\data\tool\ALL_BYTES.TXT unicode \charconv\test\data\tool\ISO88596.UNI -little
call %0 testoneway iso88597 \charconv\test\data\tool\ALL_BYTES.TXT unicode \charconv\test\data\tool\ISO88597.UNI -little
call %0 testoneway iso88598 \charconv\test\data\tool\ALL_BYTES.TXT unicode \charconv\test\data\tool\ISO88598.UNI -little
call %0 testoneway iso88599 \charconv\test\data\tool\ALL_BYTES.TXT unicode \charconv\test\data\tool\ISO88599.UNI -little
call %0 testoneway iso885910 \charconv\test\data\tool\ALL_BYTES.TXT unicode \charconv\test\data\tool\ISO885910.UNI -little
call %0 testoneway iso885913 \charconv\test\data\tool\ALL_BYTES.TXT unicode \charconv\test\data\tool\ISO885913.UNI -little
call %0 testoneway iso885914 \charconv\test\data\tool\ALL_BYTES.TXT unicode \charconv\test\data\tool\ISO885914.UNI -little
call %0 testoneway iso885915 \charconv\test\data\tool\ALL_BYTES.TXT unicode \charconv\test\data\tool\ISO885915.UNI -little

goto end

:testoneway

call charconv -input=%2 %3 -output=%4 \charconv\test\data\tool\_._ %6 %7 %8 %9 2> NUL
fc /b %5 \charconv\test\data\tool\_._
del \charconv\test\data\tool\_._

call charconv -input=%2 -output=%4 \charconv\test\data\tool\_._ %6 %7 %8 %9 <%3 2> NUL
fc /b %5 \charconv\test\data\tool\_._
del \charconv\test\data\tool\_._

call charconv -input=%2 %3 -output=%4 %6 %7 %8 %9 >\charconv\test\data\tool\_._ 2> NUL
fc /b %5 \charconv\test\data\tool\_._
del \charconv\test\data\tool\_._

call charconv -input=%2 -output=%4 %6 %7 %8 %9 <%3 >\charconv\test\data\tool\_._ 2> NUL
fc /b %5 \charconv\test\data\tool\_._
del \charconv\test\data\tool\_._

goto end

:testall

call %0 testoneway %2 %3 %4 %5 %6 %7 %8 %9
call %0 testoneway %4 %5 %2 %3 %6 %7 %8 %9

goto end

:end

