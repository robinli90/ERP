// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600
#endif

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

// Windows Header Files:
#include <windows.h>
#include <Windowsx.h>
#include <commctrl.h>
#include <Shellapi.h>
#include <Shlwapi.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include "resource.h"

// Application Configuration Defines
#define MARKHAM 1
#define WRITE_CAM_FILE	1
#define CMS_DATABASE_NAME "CMSDAT" 
#define DECADE_DATABASE_NAME "decade"  
#define PLANT_CODE "001"
#define DB_INTERUPDATE_INTERVAL 30000 // milliseconds.
#define CMS_USER "UD1"
#define CMS_PASSWORD "UD1"
#define ERROR_EMAIL_SUBJECT			"UpdateDecade error report (Markham)"
#define TARGET_PLANT	0	// 0 == Markham, 1 == AluDie, 2 == MI, 3 == Colombia
							// THIS SETTING MATTERS AGAIN. It
							// is used for cmsPrefix[][], which
							// differs for Colombia.

#define CAM_FILE_LOCATION "\\\\filesrv\\rdrive\\shoporders\\" // for Markham, but part of everyone's build
//#define CAM_FILE_LOCATION "R:\\shoporders\\" // for Markham, but part of everyone's build
#define CUSTOMER_MAP_FILE "C:\\Program Files\\updateDecade\\DecadeUpdate.cmp"
#define ALTERNATE_CUSTOMER_MAP_FILE "DecadeUpdate.cmp"

// Mapping from CMS shipping customer codes to Decade customer codes
#	define DECADE_CODE_LENGTH 6
#   define CMS_CODE_LENGTH 8
#	define MAX_CODES_AND_HASH_MODULUS	1021

struct codeMappingEntry 
{
	char CMSCode[CMS_CODE_LENGTH+1];
	char DecadeCode[DECADE_CODE_LENGTH+1];
};