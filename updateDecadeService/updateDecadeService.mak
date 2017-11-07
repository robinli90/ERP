# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.

TARGETOS=WINNT

!include <ntwin32.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

cflags = $(cflags) -I"C:\Program Files\Microsoft SDK\include"

all: updateDecadeService.exe

.c.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsmt) $*.cpp


## updateDecadeService dependencies

updateDecadeService.obj: updateDecadeService.cpp service.h

service.obj: service.cpp service.h

updateDecadeService_objs = updateDecadeService.obj service.obj

service_libs = $(conlibsmt) advapi32.lib shell32.lib user32.lib "C:\Program Files\Microsoft SDK\lib\psapi.lib" odbc32.lib odbccp32.lib 

updateDecadeService.exe: $(updateDecadeService_objs)
    $(link) $(linkdebug) $(conflags) -out:.\updateDecadeService.exe $(updateDecadeService_objs) $(service_libs)

