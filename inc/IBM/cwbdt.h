/********************************************************************/
/*                                                                  */
/* 5769-XE1                                                         */
/* (C) Copyright IBM Corp. 1995,1998                                */
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
/*   CWBDT.H                                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Contains the declarations for the following API's:             */
/*                                                                  */
/*    cwbDT_ASCII11ToBin4                                           */
/*    cwbDT_Wide11ToBin4                                            */
/*    cwbDT_ASCII6ToBin2                                            */
/*    cwbDT_Wide6ToBin2                                             */
/*    cwbDT_ASCIIPackedToPacked                                     */
/*    cwbDT_ASCIIToHex                                              */
/*    cwbDT_WideToHex                                               */
/*    cwbDT_ASCIIToPacked                                           */
/*    cwbDT_WideToPacked                                            */
/*    cwbDT_ASCIIToZoned                                            */
/*    cwbDT_WideToZoned                                             */
/*    cwbDT_ASCIIZonedToZoned                                       */
/*    cwbDT_Bin2ToASCII6                                            */
/*    cwbDT_Bin2ToWide6                                             */
/*    cwbDT_Bin2ToBin2                                              */
/*    cwbDT_Bin4ToASCII11                                           */
/*    cwbDT_Bin4ToWide11                                            */
/*    cwbDT_Bin4ToBin4                                              */
/*    cwbDT_EBCDICToEBCDIC                                          */
/*    cwbDT_HexToASCII                                              */
/*    cwbDT_HexToWide                                               */
/*    cwbDT_PackedToASCII                                           */
/*    cwbDT_PackedToWide                                            */
/*    cwbDT_PackedToASCIIPacked                                     */
/*    cwbDT_PackedToPacked                                          */
/*    cwbDT_ZonedToASCII                                            */
/*    cwbDT_ZonedToWide                                             */
/*    cwbDT_ZonedToASCIIZoned                                       */
/*    cwbDT_ZonedToZoned                                            */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Link with CWBAPI.LIB import library.                           */
/*   This module is to be used in conjunction with CWBDT.DLL.       */
/*                                                                  */
/*  This module includes the translation functions that need data   */
/*  conversions for transferring numeric data from the AS/400 to the*/
/*  personal computer, and vice versa.  For both types of           */
/*  transfers, the necessary conversion depends on the              */
/*  type of data being transferred.                                 */
/*                                                                  */
/*   In addition to the return codes listed for APIs additional     */
/*   operating system specific return codes may also appear.  The   */
/*   precise meaning of these return codes can be found in the      */
/*   operating system manuals or relevant header files.             */
/*                                                                  */
/********************************************************************/

/* Prevent multiple includes */
#ifndef _CWBDT_H_
#define _CWBDT_H_


/*------------------------------------------------------------------*/
/* INCLUDES:                                                        */
/*------------------------------------------------------------------*/
#include <windows.h>

/* Common Client Access/400 API include */
#include "CWB.H"


#if defined(__cplusplus)
 extern "C" {
#endif


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDT_ASCII11ToBin4                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Translates (exactly) 11 ASCII numeric characters               */
/*   to a 4-byte integer stored most significant byte first.        */
/*   (The source string is not expected to be zero-terminated.)     */
/*   This function can be used for translating ASCII numeric data   */
/*   to the AS/400 integer format.                                  */
/*                                                                  */
/* Parameters:                                                      */
/*   char * target - output                                         */
/*    Pointer to the target (4 byte integer).                       */
/*                                                                  */
/*   const char * source - input                                    */
/*    Pointer to the source (11 character ASCII).                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_INVALID_POINTER - NULL pointer was passed by caller.       */
/*   CWB_BUFFER_OVERFLOW - Overflow error.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*   other - Offset of the first untranslated                       */
/*           character plus one.                                    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The target data will be stored with the Most Significant       */
/*   Byte first. This is the format that the AS/400 uses and        */
/*   is the opposite of the format used by the Intel x86 processors.*/
/*                                                                  */
/*   Valid formats for the ASCII source data are as follows:        */
/*                                                                  */
/*      [blankspaces][sign][blankspaces][digits]                    */
/*   or [sign][blankspaces][digits][blankspaces]                    */
/*                                                                  */
/*   examples:                                                      */
/*     "   +    123"                                                */
/*     "-    123   "                                                */
/*     "     +123  "                                                */
/*     "        123"                                                */
/*     "       -123"                                                */
/*     "+123       "                                                */
/*                                                                  */
/********************************************************************/
#if (  ( !( defined(CWB_ANSI_ONLY) && defined(CWB_OEM_ONLY) ) ) && \
       ( !( defined(CWB_UNICODE_ONLY) ) )  )
unsigned int CWB_ENTRY cwbDT_ASCII11ToBin4(
                             char *target,
                             const char *source);
#endif  // OEM-only/ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDT_Wide11ToBin4(
                                            char          *target
                                          , const wchar_t *source
                                        );
#endif   // UNICODE-only selection

// UNICODE API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDT_String11ToBin4            cwbDT_Wide11ToBin4
#else
   #define  cwbDT_String11ToBin4            cwbDT_ASCII11ToBin4
#endif // of UNICODE selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDT_ASCII6ToBin2                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Translates (exactly) 6 ASCII numeric characters                */
/*   to a 2-byte integer stored most significant byte first.        */
/*   (The source string is not expected to be zero-terminated.)     */
/*   This function can be used for translating ASCII numeric data   */
/*   to the AS/400 integer format.                                  */
/*                                                                  */
/* Parameters:                                                      */
/*   char * target - output                                         */
/*    Pointer to the target (2 byte integer).                       */
/*                                                                  */
/*   const char * source - input                                    */
/*    Pointer to the source (6 character ASCII).                    */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_INVALID_POINTER - NULL pointer was passed by caller.       */
/*   CWB_BUFFER_OVERFLOW - Overflow error.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*   other - Offset of the first untranslated                       */
/*           character plus one.                                    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The target data will be stored with the Most Significant       */
/*   Byte first. This is the format that the AS/400 uses and        */
/*   is the opposite of the format used by the Intel x86 processors.*/
/*                                                                  */
/*   Valid formats for the ASCII source data are as follows:        */
/*                                                                  */
/*      [blankspaces][sign][blankspaces][digits]                    */
/*   or [sign][blankspaces][digits][blankspaces]                    */
/*                                                                  */
/*   examples:                                                      */
/*     " + 123"                                                     */
/*     "- 123 "                                                     */
/*     " +123 "                                                     */
/*     "   123"                                                     */
/*     "  -123"                                                     */
/*     "+123  "                                                     */
/*                                                                  */
/********************************************************************/
#if (  ( !( defined(CWB_ANSI_ONLY) && defined(CWB_OEM_ONLY) ) ) && \
       ( !( defined(CWB_UNICODE_ONLY) ) )  )
unsigned int CWB_ENTRY cwbDT_ASCII6ToBin2(
                             char *target,
                             const char *source);
#endif  // OEM-only/ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDT_Wide6ToBin2(
                                           char          *target
                                         , const wchar_t *source
                                       );
#endif   // UNICODE-only selection

// UNICODE API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDT_String6ToBin2             cwbDT_Wide6ToBin2
#else
   #define  cwbDT_String6ToBin2             cwbDT_ASCII6ToBin2
#endif // of UNICODE selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDT_ASCIIPackedToPacked                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Translates data from ASCII packed format to packed             */
/*   decimal. This function can be used for translating data from   */
/*   ASCII files to the AS/400 system format.                       */
/*                                                                  */
/* Parameters:                                                      */
/*   char * target - output                                         */
/*    Pointer to the target data.                                   */
/*                                                                  */
/*   const char * source - input                                    */
/*    Pointer to the source data.                                   */
/*                                                                  */
/*   unsigned long length - input                                   */
/*    Number of bytes of source data to translate.                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_INVALID_POINTER - NULL pointer was passed by caller.       */
/*   other - Offset of the first untranslated                       */
/*           character plus one.                                    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The caller must make sure that there is adequate space to      */
/*   hold the target information.                                   */
/*                                                                  */
/*  This function checks that each half-byte of the packed decimal  */
/*   data is in the range of 0 to 9.  The only exception is the     */
/*   last half-byte which contains the sign indicator (which can    */
/*   be 0x3 or 0xb).                                                */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDT_ASCIIPackedToPacked(
                             char         *target,
                             const char   *source,
                             unsigned long length);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDT_ASCIIToHex                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Translates data from ASCII (hex representation) to binary.     */
/*   One byte is stored in the target for each character in the     */
/*   source.                                                        */
/*                                                                  */
/* Parameters:                                                      */
/*   char * target - output                                         */
/*    Pointer to the target data.                                   */
/*                                                                  */
/*   const char * source - input                                    */
/*    Pointer to the source (ASCII hex) data.                       */
/*                                                                  */
/*   unsigned long length - input                                   */
/*    Number of characters of source data to translate/2.           */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_INVALID_POINTER - NULL pointer was passed by caller.       */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*   other - Offset of the first untranslated                       */
/*           character plus one.                                    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   For 'length' characters of source data 'length'/2 bytes of     */
/*   target data will be stored.  The caller must make sure that    */
/*   there is adequate space to hold the target information.        */
/*                                                                  */
/********************************************************************/
#if (  ( !( defined(CWB_ANSI_ONLY) && defined(CWB_OEM_ONLY) ) ) && \
       ( !( defined(CWB_UNICODE_ONLY) ) )  )
unsigned int CWB_ENTRY cwbDT_ASCIIToHex(
                             char         *target,
                             const char   *source,
                             unsigned long length);
#endif  // OEM-only/ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDT_WideToHex(
                                         char            *target
                                       , const wchar_t   *source
                                       , ULONG            length
                                     );
#endif   // UNICODE-only selection

// UNICODE API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDT_StringToHex               cwbDT_WideToHex
#else
   #define  cwbDT_StringToHex               cwbDT_ASCIIToHex
#endif // of UNICODE selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDT_ASCIIToPacked                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Translates ASCII numeric data to packed decimal format.        */
/*   This function can be used for translating ASCII text data      */
/*   for use on the AS/400.                                         */
/*                                                                  */
/* Parameters:                                                      */
/*   char * target - output                                         */
/*    Pointer to the target data.                                   */
/*                                                                  */
/*   const char * source - input                                    */
/*    Pointer to the source data.  Must be zero terminated.         */
/*                                                                  */
/*   unsigned long length - input                                   */
/*    Number of bytes of target data.                               */
/*                                                                  */
/*   unsigned long decimalPosition - input                          */
/*    Position of the decimal point.                                */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_INVALID_POINTER - NULL pointer was passed by caller.       */
/*   CWB_BUFFER_OVERFLOW - Overflow error.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*   other - Offset of the first untranslated                       */
/*           character plus one.                                    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The caller must make sure that there is adequate space         */
/*   to hold the target information.                                */
/*                                                                  */
/*   The sign half-byte will be set to 0xd to indicate a negative   */
/*   number and hex 0xc to indicate a positive number.              */
/*                                                                  */
/*   0 <= decimalPosition < (length * 2).                           */
/*                                                                  */
/*   Valid formats for the ASCII numeric data are as follows:       */
/*                                                                  */
/*      [blankspaces][sign][blankspaces][digits]                    */
/*   or [sign][blankspaces][digits][blankspaces]                    */
/*   or [sign][digits][.digits][blankspaces]                        */
/*   or [blankspaces][sign][digits][.digits][blankspaces]           */
/*                                                                  */
/*  examples:                                                       */
/*    "   +  123\0"                                                 */
/*    "- 123   \0"                                                  */
/*    "     +123  \0"                                               */
/*    "    123\0"                                                   */
/*    "       -12.3\0"                                              */
/*    "+1.23       \0"                                              */
/*                                                                  */
/********************************************************************/
#if (  ( !( defined(CWB_ANSI_ONLY) && defined(CWB_OEM_ONLY) ) ) && \
       ( !( defined(CWB_UNICODE_ONLY) ) )  )
unsigned int CWB_ENTRY cwbDT_ASCIIToPacked(
                             char         *target,
                             const char   *source,
                             unsigned long length,
                             unsigned long decimalPosition);
#endif  // OEM-only/ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDT_WideToPacked(
                                            char          *target
                                          , LPCWSTR        source
                                          , ULONG          length
                                          , ULONG          decimalPosition
                                        );
#endif   // UNICODE-only selection

// UNICODE API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDT_StringToPacked            cwbDT_WideToPacked
#else
   #define  cwbDT_StringToPacked            cwbDT_ASCIIToPacked
#endif // of UNICODE selection


/********************************************************************/
/* API:                                                             */
/*   cwbDT_ASCIIToZoned                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Translates ASCII numeric data to EBCDIC zoned decimal format.  */
/*   This function can be used for translating ASCII text data for  */
/*   for use on the AS/400.                                         */
/*                                                                  */
/* Parameters:                                                      */
/*   char * target - output                                         */
/*    Pointer to the target data.                                   */
/*                                                                  */
/*   const char * source - input                                    */
/*    Pointer to the source data.  Must be zero terminated.         */
/*                                                                  */
/*   unsigned long length - input                                   */
/*    Number of bytes of target data.                               */
/*                                                                  */
/*   unsigned long decimalPosition - input                          */
/*    Position of the decimal point.                                */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_INVALID_POINTER - NULL pointer was passed by caller.       */
/*   CWB_BUFFER_OVERFLOW - Overflow error.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*   other - Offset of the first untranslated                       */
/*           character plus one.                                    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The caller must make sure that there is adequate space         */
/*   to hold the information.                                       */
/*                                                                  */
/*   The sign half-byte will be set to 0xd to indicate a negative   */
/*   number and hex 0xc to indicate a positive number.              */
/*                                                                  */
/*   0 <= decimalPosition <= length.                                */
/*                                                                  */
/*   Valid formats for the ASCII numeric data are as follows:       */
/*                                                                  */
/*      [blankspaces][sign][blankspaces][digits]                    */
/*   or [sign][blankspaces][digits][blankspaces]                    */
/*   or [sign][digits][.digits][blankspaces]                        */
/*   or [blankspaces][sign][digits][.digits][blankspaces]           */
/*                                                                  */
/*  examples:                                                       */
/*    "   +  123\0"                                                 */
/*    "- 123   \0"                                                  */
/*    "     +123  \0"                                               */
/*    "    123\0"                                                   */
/*    "       -12.3\0"                                              */
/*    "+1.23       \0"                                              */
/*                                                                  */
/********************************************************************/
#if (  ( !( defined(CWB_ANSI_ONLY) && defined(CWB_OEM_ONLY) ) ) && \
       ( !( defined(CWB_UNICODE_ONLY) ) )  )
unsigned int CWB_ENTRY cwbDT_ASCIIToZoned(
                             char         *target,
                             const char   *source,
                             unsigned long length,
                             unsigned long decimalPosition);
#endif  // OEM-only/ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDT_WideToZoned(
                                           char            *target
                                         , LPCWSTR          source
                                         , ULONG            length
                                         , ULONG            decimalPosition
                                       );
#endif   // UNICODE-only selection

// UNICODE API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDT_StringToZoned             cwbDT_WideToZoned
#else
   #define  cwbDT_StringToZoned             cwbDT_ASCIIToZoned
#endif // of UNICODE selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDT_ASCIIZonedToZoned                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Translates data from ASCII zoned decimal format to             */
/*   EBCDIC zoned decimal.                                          */
/*   This function can be used for translating data from ASCII      */
/*   files for use on the AS/400.                                   */
/*                                                                  */
/* Parameters:                                                      */
/*   char * target - output                                         */
/*    Pointer to the target data.                                   */
/*                                                                  */
/*   const char * source - input                                    */
/*    Pointer to the source data.                                   */
/*                                                                  */
/*   unsigned long length - input                                   */
/*    Number of bytes of source data to translate.                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_INVALID_POINTER - NULL pointer was passed by caller.       */
/*   other - Offset of the first untranslated                       */
/*           character plus one.                                    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The left half of each byte (0x3) in the ASCII zoned            */
/*   decimal format will be converted to 0xf in the left half-byte  */
/*   of the EBCDIC zoned data except for the last byte (sign).      */
/*                                                                  */
/*   This function checks that the left half of each byte           */
/*   in the ASCII zoned decimal data must be 0x3 except for         */
/*   the last byte. The high half of the last byte must be 0x3      */
/*   or 0xb. The right half of each byte in the ASCII zoned         */
/*   decimal data must be in the range 0-9.                         */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDT_ASCIIZonedToZoned(
                             char         *target,
                             const char   *source,
                             unsigned long length);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBDT_Bin2ToASCII6                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Translates a 2-byte integer stored most significant byte       */
/*   first to (exactly) 6 ASCII numeric characters.                 */
/*   (The target will not be zero terminated.)                      */
/*   This function can be used for translating numeric data from an */
/*   AS/400 to ASCII.                                               */
/*                                                                  */
/* Parameters:                                                      */
/*   char * target - output                                         */
/*    Pointer to the target (6 character) area.                     */
/*                                                                  */
/*   const char * source - input                                    */
/*    Pointer to the source (2 byte integer).                       */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_INVALID_POINTER - NULL pointer was passed by caller.       */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The source data is assumed to be stored with the Most          */
/*   significant Byte first.  This is the format that the AS/400    */
/*   uses and is the opposite of the format used by the Intel x86   */
/*   processes                                                      */
/*                                                                  */
/********************************************************************/
#if (  ( !( defined(CWB_ANSI_ONLY) && defined(CWB_OEM_ONLY) ) ) && \
       ( !( defined(CWB_UNICODE_ONLY) ) )  )
unsigned int CWB_ENTRY cwbDT_Bin2ToASCII6(
                             char *target,
                             const char *source);
#endif  // OEM-only/ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDT_Bin2ToWide6(
                                           wchar_t        *target
                                         , const char     *source
                                       );
#endif   // UNICODE-only selection

// UNICODE API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDT_Bin2ToString6             cwbDT_Bin2ToWide6
#else
   #define  cwbDT_Bin2ToString6             cwbDT_Bin2ToASCII6
#endif // of UNICODE selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBDT_Bin2ToBin2                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Reverses the order of bytes in a 2-byte integer.               */
/*   This function can be used for translating a 2-byte integer to  */
/*   or from the AS/400 format.                                     */
/*                                                                  */
/* Parameters:                                                      */
/*   char * target - output                                         */
/*    Pointer to the target (2 byte integer).                       */
/*                                                                  */
/*   const char * source - input                                    */
/*    Pointer to the source (2 byte integer).                       */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_INVALID_POINTER - NULL pointer was passed by caller.       */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The source data and the target data must not overlap.          */
/*   The following example shows the result of the translation:     */
/*     Source data: 0x1234                                          */
/*     Target data: 0x3412                                          */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDT_Bin2ToBin2(
                             char *target,
                             const char *source);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDT_Bin4ToASCII11                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Translates a 4-byte integer stored most significant byte       */
/*   first to (exactly) 11 ASCII numeric characters.                */
/*   (The target will not be zero terminated.)                      */
/*   This function can be used for translating numeric data from an */
/*   AS/400 to ASCII.                                               */
/*                                                                  */
/* Parameters:                                                      */
/*   char * target - output                                         */
/*    Pointer to the target (11 byte) area.                         */
/*                                                                  */
/*   const char * source - input                                    */
/*    Pointer to the source (4 byte integer).                       */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_INVALID_POINTER - NULL pointer was passed by caller.       */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The source data is assumed to be stored with the Most          */
/*   Significant Byte first.  This is the format that the AS/400    */
/*   uses and is the opposite of the format used by the Intel x86   */
/*   processors.                                                    */
/*                                                                  */
/********************************************************************/
#if (  ( !( defined(CWB_ANSI_ONLY) && defined(CWB_OEM_ONLY) ) ) && \
       ( !( defined(CWB_UNICODE_ONLY) ) )  )
unsigned int CWB_ENTRY cwbDT_Bin4ToASCII11(
                             char *target,
                             const char *source );
#endif  // OEM-only/ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDT_Bin4ToWide11(
                                            wchar_t     *target
                                          , const char  *source
                                        );
#endif   // UNICODE-only selection

// UNICODE API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDT_Bin4ToString11            cwbDT_Bin4ToWide11
#else
   #define  cwbDT_Bin4ToString11            cwbDT_Bin4ToASCII11
#endif // of UNICODE selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBDT_Bin4ToBin4                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Reverses the order of bytes in a 4-byte integer.               */
/*   This function can be used for translating a 4-byte integer to  */
/*   or from the AS/400 format.                                     */
/*                                                                  */
/* Parameters:                                                      */
/*   char * target - output                                         */
/*    Pointer to the target (4 byte integer).                       */
/*                                                                  */
/*   const char * source - input                                    */
/*    Pointer to the source (4 byte integer).                       */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_INVALID_POINTER - NULL pointer was passed by caller.       */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The source data and the target data must not overlap.          */
/*   The following example shows the result of the translation:     */
/*     Source data: 0x12345678                                      */
/*     Target data: 0x78563412                                      */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDT_Bin4ToBin4(
                             char *target,
                             const char *source);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDT_EBCDICToEBCDIC                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   'Translates' (copies unless character value less than          */
/*   0x40 is encountered) EBCDIC data to EBCDIC.                    */
/*                                                                  */
/* Parameters:                                                      */
/*   char * target - output                                         */
/*    Pointer to the target data.                                   */
/*                                                                  */
/*   const char * source - input                                    */
/*    Pointer to the source data.                                   */
/*                                                                  */
/*   unsigned long length - input                                   */
/*    Number of bytes of target data to translate.                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_INVALID_POINTER - NULL pointer was passed by caller.       */
/*   other - Offset of the first untranslated                       */
/*           character plus one.                                    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The caller must make sure that there is adequate space         */
/*   to hold the target information.                                */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDT_EBCDICToEBCDIC(
                             char         *target,
                             const char   *source,
                             unsigned long length);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*  cwbDT_HexToASCII                                                */
/*                                                                  */
/* Purpose:                                                         */
/*   Translates binary data to the ASCII hex representation.        */
/*   Two ASCII characters are stored in the target for each byte    */
/*   of source data.                                                */
/*                                                                  */
/* Parameters:                                                      */
/*   char * target - output                                         */
/*    Pointer to the target (ASCII hex) data.                       */
/*                                                                  */
/*   const char * source - input                                    */
/*    Pointer to the source data.                                   */
/*                                                                  */
/*   unsigned long length - input                                   */
/*    Number of bytes of source data to translate.                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_INVALID_POINTER - NULL pointer was passed by caller.       */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*    For 'length' bytes of source data 'length'*2 bytes of target  */
/*    data will be stored.  The caller must make sure that there    */
/*    is adequate space to hold the target information.             */
/*                                                                  */
/********************************************************************/
#if (  ( !( defined(CWB_ANSI_ONLY) && defined(CWB_OEM_ONLY) ) ) && \
       ( !( defined(CWB_UNICODE_ONLY) ) )  )
unsigned int CWB_ENTRY cwbDT_HexToASCII(
                             char         *target,
                             const char   *source,
                             unsigned long length);
#endif  // OEM-only/ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDT_HexToWide(
                                         wchar_t         *target
                                       , const char      *source
                                       , ULONG            length
                                     );
#endif   // UNICODE-only selection

// UNICODE API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDT_HexToString               cwbDT_HexToWide
#else
   #define  cwbDT_HexToString               cwbDT_HexToASCII
#endif // of UNICODE selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDT_PackedToASCII                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Translates data from packed decimal format to ASCII numeric    */
/*   data. This function can be used for translating data from the  */
/*   the AS/400 for use in ASCII text format.                       */
/*                                                                  */
/* Parameters:                                                      */
/*   char * target - output                                         */
/*    Pointer to the target data.                                   */
/*                                                                  */
/*   const char * source - input                                    */
/*    Pointer to the source data.                                   */
/*                                                                  */
/*   unsigned long length - input                                   */
/*    Number of bytes of source data to translate.                  */
/*                                                                  */
/*   unsigned long decimalPosition - input                          */
/*    Position of the decimal point.                                */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_INVALID_POINTER - NULL pointer was passed by caller.       */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_API_ERROR - General API failure.                           */
/*   other - Offset of the first untranslated                       */
/*           character plus one.                                    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The caller must make sure that there is adequate space to      */
/*   hold the target information.                                   */
/*                                                                  */
/*   This function checks that each half-byte of the packed decimal */
/*   data is in the range of 0 to 9.  The only exception is the     */
/*   last half-byte which contains the sign indicator.              */
/*                                                                  */
/*   0 <= decimalPosition < (length * 2).                           */
/*                                                                  */
/********************************************************************/
#if (  ( !( defined(CWB_ANSI_ONLY) && defined(CWB_OEM_ONLY) ) ) && \
       ( !( defined(CWB_UNICODE_ONLY) ) )  )
unsigned int CWB_ENTRY cwbDT_PackedToASCII(
                             char         *target,
                             const char   *source,
                             unsigned long length,
                             unsigned long decimalPosition);
#endif  // OEM-only/ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDT_PackedToWide(
                                            wchar_t      *target
                                          , const char   *source
                                          , ULONG         length
                                          , ULONG         decimalPosition
                                        );
#endif   // UNICODE-only selection

// UNICODE API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDT_PackedToString            cwbDT_PackedToWide
#else
   #define  cwbDT_PackedToString            cwbDT_PackedToASCII
#endif // of UNICODE selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDT_PackedToASCIIPacked                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Translates data from packed decimal format to ASCII            */
/*   packed format. This function can be used for translating data  */
/*   from the AS/400 for use in ASCII format.                       */
/*                                                                  */
/* Parameters:                                                      */
/*   char * target - output                                         */
/*    Pointer to the target data.                                   */
/*                                                                  */
/*   const char * source - input                                    */
/*    Pointer to the source data.                                   */
/*                                                                  */
/*   unsigned long length - input                                   */
/*    Number of bytes of source data to translate.                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_INVALID_POINTER - NULL pointer was passed by caller.       */
/*   other - Offset of the first untranslated                       */
/*           character plus one.                                    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The caller must make sure that there is adequate space to      */
/*   hold the target information.                                   */
/*                                                                  */
/*   This function checks that each half-byte of the packed decimal */
/*   data is in the range of 0 to 9.  The only exception is the     */
/*   last half-byte which contains the sign indicator (which can    */
/*   be 0-9, 0xd, or 0xb).                                          */
/********************************************************************/
unsigned int CWB_ENTRY cwbDT_PackedToASCIIPacked(
                             char         *target,
                             const char   *source,
                             unsigned long length);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDT_PackedToPacked                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Translates packed decimal data to packed decimal.              */
/*   This function can be used for transferring data from the       */
/*   AS/400 system to no-conversion files, and vice versa.          */
/*                                                                  */
/* Parameters:                                                      */
/*   char * target - output                                         */
/*    Pointer to the target data.                                   */
/*                                                                  */
/*   const char * source - input                                    */
/*    Pointer to the source data.                                   */
/*                                                                  */
/*   unsigned long length - input                                   */
/*    Number of bytes of source data to translate.                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_INVALID_POINTER - NULL pointer was passed by caller.       */
/*   other - Offset of the first untranslated                       */
/*           character plus one.                                    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The caller must make sure that there is adequate space to      */
/*   hold the target information.                                   */
/*                                                                  */
/*   This function checks that each half-byte of the packed         */
/*   decimal data is in the range of 0 to 9.  The only exception is */
/*   the last half-byte which contains the sign indicator.          */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDT_PackedToPacked(
                             char         *target,
                             const char   *source,
                             unsigned long length);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDT_ZonedToASCII                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Translates EBCDIC zoned decimal data to ASCII numeric format.  */
/*   This function can be used for translating data from            */
/*   the AS/400 for use in ASCII text format.                       */
/*                                                                  */
/* Parameters:                                                      */
/*   char * target - output                                         */
/*    Pointer to the target data.                                   */
/*                                                                  */
/*   const char * source - input                                    */
/*    Pointer to the source data.                                   */
/*                                                                  */
/*   unsigned long length - input                                   */
/*    Number of bytes of source data to translate.                  */
/*   unsigned long decimalPosition - input                          */
/*    Position of the decimal point.                                */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_INVALID_POINTER - NULL pointer was passed by caller.       */
/*   CWB_BUFFER_OVERFLOW - Overflow error.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_API_ERROR - General API failure.                           */
/*   other - Offset of the first untranslated                       */
/*           character plus one.                                    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The caller must make sure that there is adequate space         */
/*   to hold the target information.                                */
/*                                                                  */
/*   The high half of the last byte of the zoned data indicates     */
/*   the sign of the number.  If the high half-byte is 0xb or 0xb   */
/*   then a negative number is indicated, any other value           */
/*   indicates a positive number.                                   */
/*                                                                  */
/*   This function checks that the high half of each byte of        */
/*   zoned data must be 0xf except for the last byte.  The low      */
/*   half of each byte of zoned data must be in the range 0-9.      */
/*                                                                  */
/*   0 <= decimalPosition < length.                                 */
/*                                                                  */
/********************************************************************/
#if (  ( !( defined(CWB_ANSI_ONLY) && defined(CWB_OEM_ONLY) ) ) && \
       ( !( defined(CWB_UNICODE_ONLY) ) )  )
unsigned int CWB_ENTRY cwbDT_ZonedToASCII(
                             char         *target,
                             const char   *source,
                             unsigned long length,
                             unsigned long decimalPosition);
#endif  // OEM-only/ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDT_ZonedToWide(
                                           wchar_t      *target
                                         , const char   *source
                                         , ULONG         length
                                         , ULONG         decimalPosition
                                       );
#endif   // UNICODE-only selection

// UNICODE API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDT_ZonedToString             cwbDT_ZonedToWide
#else
   #define  cwbDT_ZonedToString             cwbDT_ZonedToASCII
#endif // of UNICODE selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDT_ZonedToASCIIZoned                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Translates data from EBCDIC zoned decimal format to ASCII      */
/*   zoned decimal format.                                          */
/*   This function can be used for translating data from            */
/*   the AS/400 for use in ASCII files.                             */
/*                                                                  */
/* Parameters:                                                      */
/*   char * target - output                                         */
/*    Pointer to the target data.                                   */
/*                                                                  */
/*   const char * source - input                                    */
/*    Pointer to the source data.                                   */
/*                                                                  */
/*   unsigned long length - input                                   */
/*    Number of bytes of source data to translate.                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_INVALID_POINTER - NULL pointer was passed by caller.       */
/*   other - Offset of the first untranslated                       */
/*           character plus one.                                    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The caller must make sure that there is adequate space to      */
/*   hold the target information.                                   */
/*                                                                  */
/*   The left half-byte (0xf) in the EBCDIC zoned decimal data      */
/*   will be converted to 0x3 in the left half-byte of the ASCII    */
/*   zoned decimal data except for the last byte (sign).            */
/*                                                                  */
/*   The high half of the last byte of the EBCDIC zoned decimal     */
/*   data indicates the sign of the number.  If the high half-byte  */
/*   is 0xb or 0xb then a negative number is indicated, any         */
/*   other value indicates a positive number.                       */
/*                                                                  */
/*   This function checks that the high half of each byte of        */
/*   EBCDIC zoned decimal data must be 0xf except for the last      */
/*   byte. The low half of each byte of EBCDIC zoned decimal        */
/*   data must be in the range 0-9.                                 */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDT_ZonedToASCIIZoned(
                             char         *target,
                             const char   *source,
                             unsigned long length);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDT_ZonedToZoned                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Translates data from zoned decimal format to zoned decimal.    */
/*   This function can be used for translating data from the        */
/*   AS/400 for use in no-conversion files and vice-versa.          */
/*                                                                  */
/* Parameters:                                                      */
/*   char * target - output                                         */
/*    Pointer to the target data.                                   */
/*                                                                  */
/*   const char * source - input                                    */
/*    Pointer to the source data.                                   */
/*                                                                  */
/*   unsigned long length - input                                   */
/*    Number of bytes of source data to translate.                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_INVALID_POINTER - NULL pointer was passed by caller.       */
/*   other - Offset of the first untranslated                       */
/*           character plus one.                                    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The caller must make sure that there is adequate space         */
/*   to hold the target information.                                */
/*                                                                  */
/*   The high half of the last byte of the zoned data indicates     */
/*   the sign of the number.  If the high half-byte is 0xb          */
/*   or 0xb then a number is indicated, any other value             */
/*   indicates a positive number.                                   */
/*                                                                  */
/*   This function checks that the high half of each byte of        */
/*   zoned data must be 0xf except for the last byte.  The low      */
/*   half of each byte of zoned data must be in the range 0-9.      */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDT_ZonedToZoned(
                             char         *target,
                             const char   *source,
                             unsigned long length);


#if defined(__cplusplus)
 }
#endif


#endif /* _CWBDT_H_ */

