/********************************************************************/
/*                                                                  */
/* 5769-XE1                                                         */
/* (C) Copyright IBM Corp. 1995,2000.                               */
/* All rights reserved.                                             */
/* US Government Users Restricted Rights -                          */
/* Use, duplication or disclosure restricted                        */
/* by GSA ADP Schedule Contract with IBM Corp.                      */
/*                                                                  */
/* Licensed Materials-Property of IBM                               */
/*                                                                  */
/********************************************************************/
/*                                                                  */
/* Module:                                                          */
/*   CWBNL.H                                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   It contains the declarations for the following API's:          */
/*                                                                  */
/*     cwbNL_GetLang                                                */
/*     cwbNL_GetLangA                                               */
/*     cwbNL_GetLangW                                               */
/*     cwbNL_GetLangName                                            */
/*     cwbNL_GetLangNameA                                           */
/*     cwbNL_GetLangNameW                                           */
/*     cwbNL_GetLangPath                                            */
/*     cwbNL_GetLangPathA                                           */
/*     cwbNL_GetLangPathW                                           */
/*     cwbNL_FindFirstLang                                          */
/*     cwbNL_FindFirstLangA                                         */
/*     cwbNL_FindFirstLangW                                         */
/*     cwbNL_FindNextLang                                           */
/*     cwbNL_FindNextLangA                                          */
/*     cwbNL_FindNextLangW                                          */
/*     cwbNL_SaveLang                                               */
/*     cwbNL_SaveLangA                                              */
/*     cwbNL_SaveLangW                                              */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Link with the CWBAPI.LIB import library.                       */
/*   This module is to be used in conjunction with CWBNL.DLL.       */
/*                                                                  */
/*   In addition to the return codes listed for APIs additional     */
/*   operating system specific return codes may also appear.  The   */
/*   precise meaning of these return codes can be found in the      */
/*   operating system manuals or relevant header files.             */
/*                                                                  */
/********************************************************************/
/* Prevent multiple includes */
#if !defined( _CWBNL_H_ )
  #define     _CWBNL_H_

#include <windows.h>

/* Include global declarations */
#include "cwb.h"


#if defined( __cplusplus )
  extern "C"
 {
#endif


/*------------------------------------------------------------------*/
/* Declare CWBNL-specific constants                                 */
/*------------------------------------------------------------------*/

#define CWBNL_START CWB_LAST+1         /* CWB_LAST defined in CWB.H */

#define CWBNL_MAX_NAME_SIZE 256
#define CWBNL_MAX_PATH_SIZE 256
#ifdef CWB_UNICODE
    #define CWBNL_MAX_LANG_SIZE   16
#else
    #define CWBNL_MAX_LANG_SIZE   9
#endif

/*------------------------------------------------------------------*/
/* Declare code page constants                                      */
/*------------------------------------------------------------------*/

#ifndef CWBNL_CP_UNICODE_F200
#define CWBNL_CP_UNICODE_F200 0x0000F200  // UCS2 Version 1.1
#define CWBNL_CP_UNICODE      0x000034B0  // UCS2 Current Version
#endif
#define CWBNL_CP_AS400                 1  // host code page
#define CWBNL_CP_CLIENT_OEM            2  // OEM client code page
#define CWBNL_CP_CLIENT_ANSI           3  // ANSI client code page

#define CWBNL_CP_UTF8               1208  // UTF-8
#define CWBNL_CP_UTF16BE            1200  // UTF-16 (Big-Endian)
#define CWBNL_CP_UTF16LE            1202  // UTF-16 (Little-Endian)
#define CWBNL_CP_UTF32BE            1232  // UTF-32 (Big-Endian)
#define CWBNL_CP_UTF32LE            1234  // UTF-34 (Little-Endian)

#ifdef _BIG_ENDIAN
  #define CWBNL_CP_UTF16 CWBNL_CP_UTF16BE
  #define CWBNL_CP_UTF32 CWBNL_CP_UTF32BE
#else
  #define CWBNL_CP_UTF16 CWBNL_CP_UTF16LE
  #define CWBNL_CP_UTF32 CWBNL_CP_UTF32LE
#endif

#define CWBNL_CP_CLIENT_UNICODE ( sizeof(wchar_t) == 2 ? CWBNL_CP_UTF16 : CWBNL_CP_UTF32 )

// CWBNL_CP_CLIENT is the generic client code page. It is defaulted
//                 to the OEM client code page.
#ifdef   CWB_ANSI
  #define   CWBNL_CP_CLIENT   CWBNL_CP_CLIENT_ANSI
#else
  #ifdef CWB_UNICODE
    #define CWBNL_CP_CLIENT   CWBNL_CP_CLIENT_UNICODE
  #else
    #define CWBNL_CP_CLIENT   CWBNL_CP_CLIENT_OEM
  #endif
#endif

/*------------------------------------------------------------------*/
/* Error messages for conversion APIs                               */
/*------------------------------------------------------------------*/

#define CWBNL_ERR_CNV_UNSUPPORTED    CWBNL_START+101
#define CWBNL_ERR_CNV_TBL_INVALID    CWBNL_START+102
#define CWBNL_ERR_CNV_TBL_MISSING    CWBNL_START+103
#define CWBNL_ERR_CNV_ERR_GET        CWBNL_START+104
#define CWBNL_ERR_CNV_ERR_COMM       CWBNL_START+105
#define CWBNL_ERR_CNV_ERR_SERVER     CWBNL_START+106
#define CWBNL_ERR_CNV_ERR_STATUS     CWBNL_START+107
#define CWBNL_ERROR_CONVERSION_INCOMPLETE_MULTIBYTE_INPUT_CHARACTER CWBNL_START+108
#define CWBNL_ERR_CNV_INVALID_SISO_STATUS   CWBNL_START+109
#define CWBNL_ERR_CNV_INVALID_PAD_LENGTH    CWBNL_START+110

/*------------------------------------------------------------------*/
/* Error messages for language APIs                                 */
/*------------------------------------------------------------------*/

#define CWBNL_ERR_STR_TBL_INVALID    CWBNL_START+201
#define CWBNL_ERR_STR_TBL_MISSING    CWBNL_START+202
#define CWBNL_ERR_STR_NOT_FOUND      CWBNL_START+203
#define CWBNL_ERR_NLV_NO_CONFIG      CWBNL_START+204
#define CWBNL_ERR_NLV_NO_SUBDIR      CWBNL_START+205
#define CWBNL_DEFAULT_HOST_CCSID_USED  CWBNL_START+206

/*------------------------------------------------------------------*/
/* Error messages for locale APIs                                   */
/*------------------------------------------------------------------*/

#define CWBNL_ERR_LOC_TBL_INVALID    CWBNL_START+301
#define CWBNL_ERR_LOC_TBL_MISSING    CWBNL_START+302
#define CWBNL_ERR_LOC_NO_CONFIG      CWBNL_START+303
#define CWBNL_ERR_LOC_NO_LOCPATH     CWBNL_START+304

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbNL_GetLang                                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the current language setting.                              */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * mriBasePath - input                               */
/*     Pointer to the mriBasePath.                                  */
/*     e.g. C:\Program Files\IBM\ClientAccess/400                   */
/*     If NULL, the mriBasePath of the ClinetAccess/400 product is  */
/*     used.                                                        */
/*                                                                  */
/*   char * resultPtr - output                                      */
/*     Pointer to the buffer to contain the result.                 */
/*                                                                  */
/*   unsigned short resultLen - input                               */
/*     Length of the result buffer.                                 */
/*     Recommended size is CWBNL_MAX_LANG_SIZE.                     */
/*                                                                  */
/*   unsigned short * requiredLen - output                          */
/*     Actual length of the result.  If requiredLen > resultLen,    */
/*     the return value will be CWB_BUFFER_OVERFLOW.                */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_BUFFER_OVERFLOW - Buffer too small to contain result.      */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The result buffer will contain the name of the language        */
/*   subdirectory.  This language subdirectory contains the         */
/*   language-specific files.  This language subdirectory name      */
/*   can also be passed to cwbNL_GetLangName.                       */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbNL_GetLang(
                             const char     *mriBasePath,
                             char           *resultPtr,
                             unsigned short  resultLen,
                             unsigned short *requiredLen,
                             cwbSV_ErrHandle errorHandle);
#endif   // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbNL_GetLangA(
                                        LPCSTR          mriBasePath
                                      , LPSTR           resultPtr
                                      , USHORT          resultLen
                                      , USHORT         *requiredLen
                                      , cwbSV_ErrHandle errorHandle
                                    );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbNL_GetLangW(
                                        LPCWSTR         mriBasePath
                                      , LPWSTR          resultPtr
                                      , USHORT          resultLen
                                      , USHORT         *requiredLen
                                      , cwbSV_ErrHandle errorHandle
                                    );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbNL_GetLang                   cwbNL_GetLangW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbNL_GetLang                   cwbNL_GetLangA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbNL_SaveLang                                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   Save the language setting in the product registry.             */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * lang - input                                      */
/*     Address of the ASCIIZ string representing the language.      */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The language must be a value returned from one of these APIs:  */
/*     cwbNL_GetLang                                                */
/*     cwbNL_FindFirstLang                                          */
/*     cwbNL_FindNextLang                                           */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     cwbNL_GetLang                                                */
/*     cwbNL_GetLangPath                                            */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbNL_SaveLang(
                             const char      *lang,
                             cwbSV_ErrHandle  errorHandle);
#endif   // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbNL_SaveLangA(
                                         LPCSTR           lang
                                       , cwbSV_ErrHandle  errorHandle
                                     );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbNL_SaveLangW(
                                         LPCWSTR          lang
                                       , cwbSV_ErrHandle  errorHandle
                                     );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbNL_SaveLang                  cwbNL_SaveLangW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbNL_SaveLang                  cwbNL_SaveLangA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbNL_GetLangName                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Return the descriptive name of a language setting.             */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * lang - input                                      */
/*     Address of the ASCIIZ string representing the language.      */
/*                                                                  */
/*   char * resultPtr - output                                      */
/*     Pointer to the buffer to contain the result.                 */
/*                                                                  */
/*   unsigned short resultLen - input                               */
/*     Length of the result buffer.                                 */
/*     Recommended size is CWBNL_MAX_NAME_SIZE.                     */
/*                                                                  */
/*   unsigned short * requiredLen - output                          */
/*     Actual length of the result.  If requiredLen > resultLen,    */
/*     the return value will be CWB_BUFFER_OVERFLOW.                */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_BUFFER_OVERFLOW - Output buffer too small, data truncated. */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The language must be a value returned from one of these APIs:  */
/*     cwbNL_GetLang                                                */
/*     cwbNL_FindFirstLang                                          */
/*     cwbNL_FindNextLang                                           */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbNL_GetLangName(
                             const char     *lang,
                             char           *resultPtr,
                             unsigned short  resultLen,
                             unsigned short *requiredLen,
                             cwbSV_ErrHandle errorHandle);
#endif   // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbNL_GetLangNameA(
                                            LPCSTR          lang
                                          , LPSTR           resultPtr
                                          , USHORT          resultLen
                                          , USHORT         *requiredLen
                                          , cwbSV_ErrHandle errorHandle
                                        );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbNL_GetLangNameW(
                                            LPCWSTR         lang
                                          , LPWSTR          resultPtr
                                          , USHORT          resultLen
                                          , USHORT         *requiredLen
                                          , cwbSV_ErrHandle errorHandle
                                        );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbNL_GetLangName               cwbNL_GetLangNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbNL_GetLangName               cwbNL_GetLangNameA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbNL_GetLangPath                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Return the complete path for language files.                   */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * mriBasePath - input                               */
/*     Pointer to the mriBasePath.                                  */
/*     e.g. C:\Program Files\IBM\ClientAccess/400                   */
/*     If NULL, the mriBasePath of the ClinetAccess/400 product is  */
/*     used.                                                        */
/*                                                                  */
/*   char * resultPtr - output                                      */
/*     Pointer to the buffer to contain the result.                 */
/*                                                                  */
/*   unsigned short resultLen - input                               */
/*     Length of the result buffer.                                 */
/*     Recommended size is CWBNL_MAX_PATH_SIZE.                     */
/*                                                                  */
/*   unsigned short * requiredLen - output                          */
/*     Actual length of the result.  If requiredLen > resultLen,    */
/*     the return value will be CWB_BUFFER_OVERFLOW.                */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_PATH_NOT_FOUND - Path not found.                           */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_BUFFER_OVERFLOW - Output buffer too small, data truncated. */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The result buffer will contain the complete path of the        */
/*   language subdirectory.  Language files should be loaded from   */
/*   this path.                                                     */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbNL_GetLangPath(
                             const char      *mriBasePath,
                             char            *resultPtr,
                             unsigned short   resultLen,
                             unsigned short  *requiredLen,
                             cwbSV_ErrHandle  errorHandle);
#endif   // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbNL_GetLangPathA(
                                            LPCSTR           mriBasePath
                                          , LPSTR            resultPtr
                                          , USHORT           resultLen
                                          , USHORT          *requiredLen
                                          , cwbSV_ErrHandle  errorHandle
                                        );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbNL_GetLangPathW(
                                            LPCWSTR          mriBasePath
                                          , LPWSTR           resultPtr
                                          , USHORT           resultLen
                                          , USHORT          *requiredLen
                                          , cwbSV_ErrHandle  errorHandle
                                        );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbNL_GetLangPath               cwbNL_GetLangPathW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbNL_GetLangPath               cwbNL_GetLangPathA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbNL_FindFirstLang                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the first available language.                          */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * mriBasePath - input                               */
/*     Pointer to the mriBasePath.                                  */
/*     e.g. C:\Program Files\IBM\ClientAccess/400                   */
/*     If NULL, the mriBasePath of the ClinetAccess/400 product is  */
/*     used.                                                        */
/*                                                                  */
/*   char * resultPtr - output                                      */
/*     Pointer to the buffer to contain the result.                 */
/*                                                                  */
/*   unsigned short resultLen - input                               */
/*     Length of the result buffer.                                 */
/*     Recommended size is CWBNL_MAX_LANG_SIZE.                     */
/*                                                                  */
/*   unsigned short * requiredLen - output                          */
/*     Actual length of the result.  If requiredLen > resultLen,    */
/*     the return value will be CWB_BUFFER_OVERFLOW.                */
/*                                                                  */
/*   unsigned long * searchHandle - output                          */
/*     Search handle to be passed on subsequent calls to            */
/*     cwbNL_FindNextLang.                                          */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_FILE_NOT_FOUND - File not found.                           */
/*   CWB_PATH_NOT_FOUND - Path not found.                           */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_BUFFER_OVERFLOW - Output buffer too small, data truncated. */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The result buffer will contain a language.                     */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbNL_FindFirstLang(
                             const char      *mriBasePath,
                             char            *resultPtr,
                             unsigned short   resultLen,
                             unsigned short  *requiredLen,
                             ULONG_PTR       *searchHandle,
                             cwbSV_ErrHandle  errorHandle);
#endif   // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbNL_FindFirstLangA(
                                              LPCSTR           mriBasePath
                                            , LPSTR            resultPtr
                                            , USHORT           resultLen
                                            , USHORT          *requiredLen
                                            , ULONG_PTR       *searchHandle
                                            , cwbSV_ErrHandle  errorHandle
                                          );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbNL_FindFirstLangW(
                                              LPCWSTR          mriBasePath
                                            , LPWSTR           resultPtr
                                            , USHORT           resultLen
                                            , USHORT          *requiredLen
                                            , ULONG_PTR       *searchHandle
                                            , cwbSV_ErrHandle  errorHandle
                                          );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbNL_FindFirstLang             cwbNL_FindFirstLangW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbNL_FindFirstLang             cwbNL_FindFirstLangA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbNL_FindNextLang                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the next available language.                           */
/*                                                                  */
/* Parameters:                                                      */
/*   char * resultPtr - output                                      */
/*     Pointer to the buffer to contain the result.                 */
/*                                                                  */
/*   unsigned short resultLen - input                               */
/*     Length of the result buffer.                                 */
/*     Recommended size is CWBNL_MAX_LANG_SIZE.                     */
/*                                                                  */
/*   unsigned short * requiredLen - output                          */
/*     Actual length of the result.  If requiredLen > resultLen,    */
/*     the return value will be CWB_BUFFER_OVERFLOW.                */
/*                                                                  */
/*   unsigned long * searchHandle - output                          */
/*     Search handle to be passed on subsequent calls to            */
/*     cwbNL_FindNextLang.                                          */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_NO_MORE_FILES - No more files are found.                   */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_BUFFER_OVERFLOW - Output buffer too small, data truncated. */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The result buffer will contain a language.                     */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbNL_FindNextLang(
                             char            *resultPtr,
                             unsigned short   resultLen,
                             unsigned short  *requiredLen,
                             ULONG_PTR       *searchHandle,
                             cwbSV_ErrHandle  errorHandle);
#endif   // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbNL_FindNextLangA(
                                             LPSTR             resultPtr
                                           , USHORT            resultLen
                                           , USHORT           *requiredLen
                                           , ULONG_PTR        *searchHandle
                                           , cwbSV_ErrHandle   errorHandle
                                         );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbNL_FindNextLangW(
                                             LPWSTR            resultPtr
                                           , USHORT            resultLen
                                           , USHORT           *requiredLen
                                           , ULONG_PTR        *searchHandle
                                           , cwbSV_ErrHandle   errorHandle
                                         );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbNL_FindNextLang              cwbNL_FindNextLangW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbNL_FindNextLang              cwbNL_FindNextLangA
#endif // of UNICODE/ANSI selection




#if defined( __cplusplus )
 }
#endif

#endif /* _CWBNL_H_ */
