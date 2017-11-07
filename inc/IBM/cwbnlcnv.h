/********************************************************************/
/*                                                                  */
/* 5722-XE1                                                         */
/* (C) Copyright IBM Corp. 1995,2003                                */
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
/*   CWBNLCNV.H                                                     */
/*                                                                  */
/* Purpose:                                                         */
/*   It contains the declarations for the following API's:          */
/*                                                                  */
/*     cwbNL_CCSIDToCodePage                                        */
/*     cwbNL_CodePageToCCSID                                        */
/*     cwbNL_Convert                                                */
/*     cwbNL_ConvertCodePages                                       */
/*     cwbNL_CreateConverter                                        */
/*     cwbNL_DeleteConverter                                        */
/*     cwbNL_GetCodePage                                            */
/*     cwbNL_GetANSICodePage                                        */
/*     cwbNL_GetHostCCSID                                           */
/*     cwbNL_GetHostCCSIDW                                          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Link with the CWBAPI.LIB import library.                       */
/*   This module is to be used in conjunction with CWBNL.DLL.       */
/*                                                                  */
/********************************************************************/

/* Prevent multiple includes */
#if !defined( _CWBNLCNV_H_ )
  #define     _CWBNLCNV_H_

/* Include global declarations */
#include "cwb.h"
#include "cwbnl.h"

#if defined( __cplusplus )
extern "C" {
#endif

/*------------------------------------------------------------------*/
/* typedefs:                                                        */
/*------------------------------------------------------------------*/
typedef cwb_Handle cwbNL_Converter;
typedef cwb_Handle cwbNL_Conversion_Table;

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbNL_CCSIDToCodePage                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   Map CCSIDs to code pages.                                      */
/*                                                                  */
/* Parameters:                                                      */
/*   unsigned long CCSID - input                                    */
/*     CCSID to convert to a code page.                             */
/*                                                                  */
/*   unsigned long * codePage - output                              */
/*     The resulting code page.                                     */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Handle to an error object.                                   */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle API.            */
/*     The messages may be retrieved with the cwbSV_GetErrText API. */
/*     If the parameter is set to zero, no messages will be         */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbNL_CCSIDToCodePage(
                             unsigned long   CCSID,
                             unsigned long  *codePage,
                             cwbSV_ErrHandle errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbNL_CodePageToCCSID                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   Map code pages to CCSIDs.                                      */
/*                                                                  */
/* Parameters:                                                      */
/*   unsigned long codePage - input                                 */
/*     Code page to convert to a CCSID.                             */
/*                                                                  */
/*   unsigned long * CCSID - output                                 */
/*     The resulting CCSID.                                         */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Handle to an error object.                                   */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle API.            */
/*     The messages may be retrieved with the cwbSV_GetErrText API. */
/*     If the parameter is set to zero, no messages will be         */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbNL_CodePageToCCSID(
                             unsigned long   codePage,
                             unsigned long  *CCSID,
                             cwbSV_ErrHandle errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbNL_Convert                                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   Convert strings using a previously opened converter.           */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbNL_Converter theConverter                                   */
/*     Handle to the previously opened converter.                   */
/*                                                                  */
/*   unsigned long sourceLength - input                             */
/*     Length of the source buffer.                                 */
/*                                                                  */
/*   unsigned long targetLength - input                             */
/*     Length of the target buffer.  If converting from an ASCII    */
/*     code page that contains DBCS characters, note that the       */
/*     resulting data could contain shift-out and shift-in bytes.   */
/*     Therefore the targetBuffer may need to be larger than the    */
/*     sourceBuffer.                                                */
/*                                                                  */
/*   char * sourceBuffer - input                                    */
/*     Buffer containing the data to convert.                       */
/*                                                                  */
/*   char * targetBuffer - output                                   */
/*     Buffer to contain the converted data.                        */
/*                                                                  */
/*   unsigned long * requiredLen - output                           */
/*     Actual length of the result.  If requiredLen > resultLen,    */
/*     the return value will be CWB_BUFFER_OVERFLOW.                */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Handle to an error object.                                   */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle API.            */
/*     The messages may be retrieved with the cwbSV_GetErrText API. */
/*     If the parameter is set to zero, no messages will be         */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_BUFFER_OVERFLOW - Output buffer too small, data truncated. */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbNL_Convert(
                             cwbNL_Converter theConverter,
                             unsigned long   sourceLength,
                             unsigned long   targetLength,
                             char           *sourceBuffer,
                             char           *targetBuffer,
                             unsigned long  *numberOfErrors,
                             unsigned long  *firstErrorIndex,
                             unsigned long  *requiredLen,
                             cwbSV_ErrHandle errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbNL_ConvertCodePages                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Convert strings from one code page to another.  This API       */
/*   combines the three converter APIs for the default conversion.  */
/*     cwbNL_CreateConverter                                        */
/*     cwbNL_Convert                                                */
/*     cwbNL_DeleteConverter                                        */
/*                                                                  */
/* Parameters:                                                      */
/*   unsigned long sourceCodePage - input                           */
/*     Code page of the data in the source buffer.                  */
/*                                                                  */
/*   unsigned long targetCodePage - input                           */
/*     Code page to which the data should be converted.             */
/*                                                                  */
/*   unsigned long sourceLength - input.                            */
/*     Length of the source buffer                                  */
/*                                                                  */
/*   unsigned long targetLength - input.                            */
/*     Length of the target buffer                                  */
/*                                                                  */
/*   char * sourceBuffer - input                                    */
/*     Buffer containing the data to convert.                       */
/*                                                                  */
/*   char * targetBuffer - output                                   */
/*     Buffer to contain the converted data.                        */
/*                                                                  */
/*   unsigned long * requiredLen - output                           */
/*     Actual length of the result.  If requiredLen > resultLen,    */
/*     the return value will be CWB_BUFFER_OVERFLOW.                */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Handle to an error object.                                   */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle API.            */
/*     The messages may be retrieved with the cwbSV_GetErrText API. */
/*     If the parameter is set to zero, no messages will be         */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Instead of calling cwbNL_ConvertCodePages multiple times with  */
/*   the same code pages:                                           */
/*                                                                  */
/*     cwbNL_ConvertCodePages(850, 500, ...);                       */
/*     cwbNL_ConvertCodePages(850, 500, ...);                       */
/*     cwbNL_ConvertCodePages(850, 500, ...);                       */
/*                                                                  */
/*   It is more efficient to create a converter and use it          */
/*   multiple times:                                                */
/*                                                                  */
/*     cwbNL_CreateConverter(850, 500, &conv, ...);                 */
/*     cwbNL_Convert(conv, ...);                                    */
/*     cwbNL_Convert(conv, ...);                                    */
/*     cwbNL_Convert(conv, ...);                                    */
/*     cwbNL_DeleteConverter(conv, ...);                            */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbNL_ConvertCodePages(
                             unsigned long   sourceCodePage,
                             unsigned long   targetCodePage,
                             unsigned long   sourceLength,
                             unsigned long   targetLength,
                             char           *sourceBuffer,
                             char           *targetBuffer,
                             unsigned long  *numberOfErrors,
                             unsigned long  *positionOfFirstError,
                             unsigned long  *requiredLen,
                             cwbSV_ErrHandle errorHandle);

unsigned int CWB_ENTRY cwbNL_ConvertCodePagesEx(
                             unsigned long   sourceCodePage,
                             unsigned long   targetCodePage,
                             unsigned long   sourceLength,
                             unsigned long   targetLength,
                             char           *sourceBuffer,
                             char           *targetBuffer,
                             unsigned long  *numberOfErrors,
                             unsigned long  *positionOfFirstError,
                             unsigned long  *requiredLen,
                             cwbSV_ErrHandle errorHandle);

#define cwbNL_ConvertCodePages cwbNL_ConvertCodePagesEx

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbNL_CreateConverter                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   Create a cwbNL_Converter to be used on subsequent calls to     */
/*   cwbNL_Convert().                                               */
/*                                                                  */
/* Parameters:                                                      */
/*   unsigned long sourceCodePage - input                           */
/*     Code page of the source data.                                */
/*                                                                  */
/*   unsigned long targetCodePage - input                           */
/*     Code page to which the data should be converted.             */
/*                                                                  */
/*   cwbNL_Converter * theConverter - output                        */
/*     The newly created converter.                                 */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Handle to an error object.                                   */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle API.            */
/*     The messages may be retrieved with the cwbSV_GetErrText API. */
/*     If the parameter is set to zero, no messages will be         */
/*     retrievable.                                                 */
/*                                                                  */
/*   unsigned long shiftInShiftOutStatus - input                    */
/*     Indicates whether the shift-in and shift-out bytes are part  */
/*     of the input or output data.                                 */
/*     0 - False, no shift-in and shift-out bytes are part          */
/*         of the data string.                                      */
/*     1 - True, shift-in and shift-out characters are part of the  */
/*         data string.                                             */
/*                                                                  */
/*   unsigned long padLength - input                                */
/*     Length of pad characters.                                    */
/*     0 - No pad characters for this conversion request            */
/*     1 - 1 byte of pad character. This is valid for only if       */
/*         the target code page is either SBCS or DBCS code page    */
/*     2 - 2 bytes of pad characters. This is valid only if the     */
/*         code page is not a single-byte code page.                */
/*                                                                  */
/*   char * pad - input                                             */
/*     The character or characters for padding.                     */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Instead of calling cwbNL_ConvertCodePages multiple times with  */
/*   the same code pages:                                           */
/*                                                                  */
/*     cwbNL_ConvertCodePages(850, 500, ...);                       */
/*     cwbNL_ConvertCodePages(850, 500, ...);                       */
/*     cwbNL_ConvertCodePages(850, 500, ...);                       */
/*                                                                  */
/*   It is more efficient to create a converter and use it          */
/*   multiple times:                                                */
/*                                                                  */
/*     cwbNL_CreateConverter(850, 500, &conv, ...);                 */
/*     cwbNL_Convert(conv, ...);                                    */
/*     cwbNL_Convert(conv, ...);                                    */
/*     cwbNL_Convert(conv, ...);                                    */
/*     cwbNL_DeleteConverter(conv, ...);                            */
/*                                                                  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbNL_CreateConverter(
                             unsigned long    sourceCodePage,
                             unsigned long    targetCodePage,
                             cwbNL_Converter *theConverter,
                             cwbSV_ErrHandle  errorHandle,
                             unsigned long    shiftInShiftOutStatus,
                             unsigned long    padLength,
                             char            *pad);

unsigned int CWB_ENTRY cwbNL_CreateConverterEx(
                             unsigned long    sourceCodePage,
                             unsigned long    targetCodePage,
                             cwbNL_Converter *theConverter,
                             cwbSV_ErrHandle  errorHandle,
                             unsigned long    shiftInShiftOutStatus,
                             unsigned long    padLength,
                             char            *pad);

#define cwbNL_CreateConverter cwbNL_CreateConverterEx

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbNL_DeleteConverter                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   Delete a cwbNL_Converter.                                      */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbNL_Converter theConverter - input                           */
/*     A previously created converter.                              */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Handle to an error object.                                   */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle API.            */
/*     The messages may be retrieved with the cwbSV_GetErrText API. */
/*     If the parameter is set to zero, no messages will be         */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbNL_DeleteConverter(
                             cwbNL_Converter theConverter,
                             cwbSV_ErrHandle errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbNL_GetCodePage                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the code page of the current process.                      */
/*                                                                  */
/* Parameters:                                                      */
/*   unsigned long * codePage - output                              */
/*     Code page of the current process.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Handle to an error object.                                   */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle API.            */
/*     The messages may be retrieved with the cwbSV_GetErrText API. */
/*     If the parameter is set to zero, no messages will be         */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbNL_GetCodePage(
                             unsigned long  *codePage,
                             cwbSV_ErrHandle errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbNL_GetANSICodePage                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the ANSI code page of the current process.                 */
/*                                                                  */
/* Parameters:                                                      */
/*   unsigned long * codePage - output                              */
/*     Code page of the current process.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Handle to an error object.                                   */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle API.            */
/*     The messages may be retrieved with the cwbSV_GetErrText API. */
/*     If the parameter is set to zero, no messages will be         */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbNL_GetANSICodePage(
                             unsigned long  *codePage,
                             cwbSV_ErrHandle errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbNL_GetHostCCSID                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the associated CCSID of a given system or the managing */
/*   system.                                                        */
/*                                                                  */
/* Parameters:                                                      */
/*   char * system - input                                          */
/*     The name of the system. If NULL, the managing system is used.*/
/*                                                                  */
/*   unsigned * CCSID - output                                      */
/*     Length of the result buffer.                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWBNL_DEFAULT_HOST_CCSID_USED - Host CCSID 500 is returned     */
/*                                   because this API is unable to  */
/*                                   determine the host CCSID.      */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API does not make or require an active connection to the  */
/*   host system to retrieve the associated CCSID value. However,   */
/*   it does depend on a prior successful connection to the host    */
/*   system. If no prior successful connection was made to the host */
/*   system, the API determines the most appropiate associated host */
/*   CCSID using an internal mapping table.                         */
/*                                                                  */
/********************************************************************/
unsigned long CWB_ENTRY cwbNL_GetHostCCSID(
                              char * system,
                              unsigned long * CCSID );

unsigned long CWB_ENTRY cwbNL_GetHostCCSIDW(
                              wchar_t * system,
                              unsigned long * CCSID );

#if ( defined(CWB_UNICODE) )
   #define cwbNL_GetHostCCSID cwbNL_GetHostCCSIDW
#endif


/* JRH */
#if defined( __cplusplus )
}
#endif
/* JRH */

#endif /* _CWBNLCNV_H_ */
