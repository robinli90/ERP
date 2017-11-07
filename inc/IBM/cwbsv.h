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
/*   CWBSV.H                                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   It contains the declarations for the following API's:          */
/*                                                                  */
/*     Writing message text to the history log                      */
/*        cwbSV_CreateMessageTextHandle()                           */
/*        cwbSV_CreateMessageTextHandleW()                          */
/*        cwbSV_DeleteMessageTextHandle()                           */
/*        cwbSV_SetMessageProduct()                                 */
/*        cwbSV_SetMessageComponent()                               */
/*        cwbSV_SetMessageClass()                                   */
/*        cwbSV_LogMessageText()                                    */
/*        cwbSV_LogMessageTextW()                                   */
/*                                                                  */
/*     Writing trace data to a detail trace file                    */
/*        cwbSV_CreateTraceDataHandle()                             */
/*        cwbSV_CreateTraceDataHandleW()                            */
/*        cwbSV_DeleteTraceDataHandle()                             */
/*        cwbSV_SetTraceProduct()                                   */
/*        cwbSV_SetTraceComponent()                                 */
/*        cwbSV_LogTraceData()                                      */
/*        cwbSV_LogTraceDataW()                                     */
/*                                                                  */
/*     Writing trace points to an entry/exit trace file             */
/*        cwbSV_CreateTraceAPIHandle()                              */
/*        cwbSV_CreateTraceAPIHandleW()                             */
/*        cwbSV_DeleteTraceAPIHandle()                              */
/*        cwbSV_SetAPIProduct()                                     */
/*        cwbSV_SetAPIComponent()                                   */
/*        cwbSV_LogAPIEntry()                                       */
/*        cwbSV_LogAPIEntryW()                                      */
/*        cwbSV_LogAPIExit()                                        */
/*        cwbSV_LogAPIExitW()                                       */
/*        cwbSV_CreateTraceSPIHandle()                              */
/*        cwbSV_CreateTraceSPIHandleW()                             */
/*        cwbSV_DeleteTraceSPIHandle()                              */
/*        cwbSV_SetSPIProduct()                                     */
/*        cwbSV_SetSPIComponent()                                   */
/*        cwbSV_LogSPIEntry()                                       */
/*        cwbSV_LogSPIEntryW()                                      */
/*        cwbSV_LogSPIExit()                                        */
/*        cwbSV_LogSPIExitW()                                       */
/*                                                                  */
/*     Check log/trace status, start log/trace, stop log/trace      */
/*        cwbSV_IsLogActive()                                       */
/*        cwbSV_StartLog()                                          */
/*        cwbSV_StopLog()                                           */
/*                                                                  */
/*     Reading service files                                        */
/*        cwbSV_GetServiceFileName()                                */
/*        cwbSV_GetServiceFileNameW()                               */
/*        cwbSV_OpenServiceFile()                                   */
/*        cwbSV_CloseServiceFile()                                  */
/*        cwbSV_ClearServiceFile()                                  */
/*        cwbSV_GetRecordCount()                                    */
/*        cwbSV_GetMaxRecordSize()                                  */
/*                                                                  */
/*     Reading service file records                                 */
/*        cwbSV_CreateServiceRecHandle()                            */
/*        cwbSV_DeleteServiceRecHandle()                            */
/*        cwbSV_ReadOldestRecord()                                  */
/*        cwbSV_ReadNewestRecord()                                  */
/*        cwbSV_ReadPrevRecord()                                    */
/*        cwbSV_ReadNextRecord()                                    */
/*                                                                  */
/*     Reading service record header information                    */
/*        cwbSV_GetProduct()                                        */
/*        cwbSV_GetProductW()                                       */
/*        cwbSV_GetComponent()                                      */
/*        cwbSV_GetComponentW()                                     */
/*        cwbSV_GetServiceType()                                    */
/*        cwbSV_GetDateStamp()                                      */
/*        cwbSV_GetDateStampW()                                     */
/*        cwbSV_GetTimeStamp()                                      */
/*        cwbSV_GetTimeStampW()                                     */
/*                                                                  */
/*     Reading history log service records                          */
/*        cwbSV_GetMessageText()                                    */
/*        cwbSV_GetMessageTextW()                                   */
/*                                                                  */
/*     Reading detail trace file service records                    */
/*        cwbSV_GetTraceData()                                      */
/*                                                                  */
/*     Reading entry/exit trace file service records                */
/*        cwbSV_GetTraceAPIID()                                     */
/*        cwbSV_GetTraceAPIType()                                   */
/*        cwbSV_GetTraceAPIData()                                   */
/*        cwbSV_GetTraceSPIID()                                     */
/*        cwbSV_GetTraceSPIType()                                   */
/*        cwbSV_GetTraceSPIData()                                   */
/*                                                                  */
/*     Retrieving message attributes associated with error handles  */
/*        cwbSV_CreateErrHandle()                                   */
/*        cwbSV_DeleteErrHandle()                                   */
/*        cwbSV_GetErrCount()                                       */
/*        cwbSV_GetErrText()                                        */
/*        cwbSV_GetErrTextW()                                       */
/*        cwbSV_GetErrTextIndexed()                                 */
/*        cwbSV_GetErrTextIndexedW()                                */
/*        cwbSV_GetErrClass()                                       */
/*        cwbSV_GetErrClassIndexed()                                */
/*        cwbSV_GetErrFileName()                                    */
/*        cwbSV_GetErrFileNameW()                                   */
/*        cwbSV_GetErrFileNameIndexed()                             */
/*        cwbSV_GetErrFileNameIndexedW()                            */
/*        cwbSV_GetErrLibName()                                     */
/*        cwbSV_GetErrLibNameW()                                    */
/*        cwbSV_GetErrLibNameIndexed()                              */
/*        cwbSV_GetErrLibNameIndexedW()                             */
/*        cwbSV_GetErrSubstText()                                   */
/*        cwbSV_GetErrSubstTextIndexed()                            */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Link with the CWBAPI.LIB import library.                       */
/*   This module is to be used in conjunction with CWBSV.DLL.       */
/*                                                                  */
/*   Distinction between API & SPI trace points:                    */
/*   ------------------------------------------                     */
/*     Definitions:                                                 */
/*       - API (Application Programming Interface)                  */
/*       - SPI (System Programming Interface)                       */
/*                                                                  */
/*   The recommended convention is that API entry/exit trace        */
/*   points should be put in routines that you externalize (export) */
/*   to your users. SPI entry/exit trace points should be used in   */
/*   key internal (non-exported) routines that you want to trace.   */
/*                                                                  */
/********************************************************************/

/* Prevent multiple includes */
#if !defined( _CWBSV_H_ )
  #define     _CWBSV_H_

/* Common Client Access/400 API include */
#include "cwb.h"

#if defined( __cplusplus )
extern "C" {
#endif

/*------------------------------------------------------------------*/
/* TYPEDEFS:                                                        */
/*------------------------------------------------------------------*/
typedef cwb_Handle cwbSV_MessageTextHandle;
typedef cwb_Handle cwbSV_TraceDataHandle;
typedef cwb_Handle cwbSV_TraceAPIHandle;
typedef cwb_Handle cwbSV_TraceSPIHandle;
typedef cwb_Handle cwbSV_ServiceFileHandle;
typedef cwb_Handle cwbSV_ServiceRecHandle;

typedef unsigned long cwbSV_ServiceFileType;
typedef unsigned long cwbSV_ServiceRecType;
typedef unsigned long cwbSV_MessageClass;
typedef unsigned long cwbSV_EventType;
typedef unsigned long cwbSV_ProblemType;
typedef unsigned char cwbSV_CreatedBy;
typedef unsigned long cwbSV_ProblemSeverity;
typedef unsigned char cwbSV_ProblemStatus;

/*------------------------------------------------------------------*/
/* DEFINES: for cwbSV_ServiceFileType                               */
/*------------------------------------------------------------------*/
#define CWBSV_HISTORY_LOG            0L
#define CWBSV_PROBLEM_LOG            1L  /* no longer supported */
#define CWBSV_DETAIL_TRACE_FILE      2L
#define CWBSV_ENTRY_EXIT_TRACE_FILE  3L

/*------------------------------------------------------------------*/
/* DEFINES: for cwbSV_ServiceRecType                                */
/*------------------------------------------------------------------*/
#define CWBSV_MESSAGE_REC     0L
#define CWBSV_PROBLEM_REC     1L  /* no longer supported */
#define CWBSV_DATA_TRACE_REC  2L
#define CWBSV_API_TRACE_REC   3L
#define CWBSV_SPI_TRACE_REC   4L

/*------------------------------------------------------------------*/
/* DEFINES: for cwbSV_EventType                                     */
/*------------------------------------------------------------------*/
#define CWBSV_ENTRY_POINT  0L
#define CWBSV_EXIT_POINT   1L

/*------------------------------------------------------------------*/
/* DEFINES: for cwbSV_ProblemType                                   */
/*------------------------------------------------------------------*/
#define CWBSV_APP_DETECTED   0L
#define CWBSV_USER_DETECTED  1L

/*------------------------------------------------------------------*/
/* DEFINES: for cwbSV_CreatedBy                                     */
/*------------------------------------------------------------------*/
#define CWBSV_OWNER_CLIENTACCESS  'P'

/*------------------------------------------------------------------*/
/* DEFINES: for cwbSV_ProblemSeverity                               */
/*------------------------------------------------------------------*/
#define CWBSV_SEV_HIGH    1L
#define CWBSV_SEV_MEDIUM  2L
#define CWBSV_SEV_LOW     3L
#define CWBSV_SEV_NONE    4L

/*------------------------------------------------------------------*/
/* DEFINES: for cwbSV_ProblemStatus                                 */
/*------------------------------------------------------------------*/
#define CWBSV_STATUS_READY  'R'
#define CWBSV_STATUS_SENT   'S'

/*------------------------------------------------------------------*/
/* DEFINES: for cwbSV_MessageClass                                  */
/*  - Use first 3 on cwbSV_SetMessageClass()                        */
/*  - Also returned from cwbSV_GetErrClass()                        */
/*                       cwbSV_GetErrClassIndexed()                 */
/*------------------------------------------------------------------*/
#define CWBSV_CLASS_INFORMATIONAL   0L
#define CWBSV_CLASS_WARNING         1L
#define CWBSV_CLASS_ERROR           2L

#define CWBSV_CLASS_ERROR_RETRY     1L  /* same as CWBSV_CLASS_WARNING */
#define CWBSV_CLASS_ERROR_ABORT     2L  /* same as CWBSV_CLASS_ERROR   */

/*------------------------------------------------------------------*/
/* Possibly returned by cwbSV_GetErrClass() and                     */
/*                      cwbSV_GetErrClassIndexed()                  */
/* Do not use on cwbSV_SetMessageClass()                            */
/*------------------------------------------------------------------*/
#define CWBSV_CLASS_HOST_WARNING          10L
#define CWBSV_CLASS_HOST_ERORR            20L  /* misspelled, don't use */
#define CWBSV_CLASS_HOST_ERROR            20L  /* use this one instead  */
#define CWBSV_CLASS_HOST_SEV_ERROR        30L
#define CWBSV_CLASS_HOST_SEV_ERROR_ABEND  40L
#define CWBSV_CLASS_HOST_JOB_ABEND        50L
#define CWBSV_CLASS_HOST_SYS_STATUS       60L
#define CWBSV_CLASS_HOST_DEVICE_INTEGRITY 70L
#define CWBSV_CLASS_HOST_SYS_ALERT        80L
#define CWBSV_CLASS_HOST_SYS_INTEGRITY    90L
#define CWBSV_CLASS_HOST_ACTION_REQUIRED  99L


/*------------------------------------------------------------------*/
/* DEFINES: for maximum string lengths                              */
/*------------------------------------------------------------------*/

/********************************************************************/
/*                                                                  */
/* When CWB_UNICODE is defined, the Unicode versions of APIs (i.e.  */
/* those that end with a 'W') are always called if they exist.      */
/* The input buffer length parameter that some of these APIs take   */
/* is the count of bytes, not characters, in the input buffer.  To  */
/* account for this difference, the maximum length constants are    */
/* computed by multiplying the number of characters maximum by the  */
/* number of bytes in one Unicode character.  This gives the        */
/* correct number of bytes the maximum length data item could be.   */
/*                                                                  */
/* To use these constants, define the input buffer in terms of the  */
/* number of characters needed, then pass the maximum byte count    */
/* as the buffer length when calling the API.  For example:         */
/*                                                                  */
/*   TCHAR historyFileName[ CWBSV_MAX_FILE_PATH_CHARS ] ;           */
/*   unsigned long returnLengthBytes ;                              */
/*           .                                                      */
/*           .                                                      */
/*           .                                                      */
/*   unsigned int rc = cwbSV_GetServiceFileName(                    */
/*                        CWBSV_HISTORY_LOG ,                       */
/*                        historyFileName ,                         */
/*                        CWBSV_MAX_FILE_PATH_BYTES ,               */
/*                        &returnLengthBytes ) ;                    */
/*                                                                  */
/********************************************************************/
#define CWBSV_MAX_FILE_PATH_CHARS         (260)  /* Service file path                 */
#define CWBSV_MAX_PRODUCT_ID_CHARS       (32+1)  /* Service Rec: Product ID           */
#define CWBSV_MAX_COMP_ID_CHARS          (32+1)  /* Service Rec: Component ID         */
#define CWBSV_MAX_DATE_VALUE_CHARS       (24+1)  /* Service Rec: Date (locale format) */
#define CWBSV_MAX_TIME_VALUE_CHARS       (24+1)  /* Service Rec: Time (locale format) */
#define CWBSV_MAX_PROBLEM_ID_CHARS       (10+1)  /* Problem Rec: Problem ID           */
#define CWBSV_MAX_PROBLEM_TEXT_CHARS      (7+1)  /* Problem Rec: Problem text         */
#define CWBSV_MAX_FAIL_PRODUCT_ID_CHARS  (64+1)  /* Problem Rec: Failing product ID   */
#define CWBSV_MAX_FAIL_VERSION_CHARS     (64+1)  /* Problem Rec: Failing version      */
#define CWBSV_MAX_CURRENT_FIX_CHARS       (8+1)  /* Problem Rec: Current fix level    */
#define CWBSV_MAX_PREVIOUS_FIX_CHARS      (8+1)  /* Problem Rec: Previous fix level   */
#define CWBSV_MAX_FAIL_PATH_CHARS      (1024+1)  /* Problem Rec: Failing path         */
#define CWBSV_MAX_FAIL_MODULE_CHARS      (64+1)  /* Problem Rec: Failing module name  */
#define CWBSV_MAX_FAIL_METHOD_CHARS      (32+1)  /* Problem Rec: Failing method name  */
#define CWBSV_MAX_SYMPTOM_STRING_CHARS  (256+1)  /* Problem Rec: Symptom string       */
#define CWBSV_MAX_ORIGIN_SYS_ID_CHARS   (256+1)  /* Problem Rec: Origin system ID     */
#define CWBSV_MAX_ORIGIN_IP_ADDR_CHARS   (15+1)  /* Problem Rec: Origin IP address    */
#define CWBSV_MAX_MSGFILE_NAME_CHARS     (10+1)  /* Error handle: Msg file name       */
#define CWBSV_MAX_MSGFILE_LIBR_CHARS     (10+1)  /* Error handle: Msg file library    */

#if ( defined(CWB_UNICODE) )
  #define CWBSV_MAX_FILE_PATH_BYTES            ( CWBSV_MAX_FILE_PATH_CHARS       * sizeof( wchar_t ) )
  #define CWBSV_MAX_PRODUCT_ID_BYTES           ( CWBSV_MAX_PRODUCT_ID_CHARS      * sizeof( wchar_t ) )
  #define CWBSV_MAX_COMP_ID_BYTES              ( CWBSV_MAX_COMP_ID_CHARS         * sizeof( wchar_t ) )
  #define CWBSV_MAX_DATE_VALUE_BYTES           ( CWBSV_MAX_DATE_VALUE_CHARS      * sizeof( wchar_t ) )
  #define CWBSV_MAX_TIME_VALUE_BYTES           ( CWBSV_MAX_TIME_VALUE_CHARS      * sizeof( wchar_t ) )
  #define CWBSV_MAX_PROBLEM_ID_BYTES           ( CWBSV_MAX_PROBLEM_ID_CHARS      * sizeof( wchar_t ) )
  #define CWBSV_MAX_PROBLEM_TEXT_BYTES         ( CWBSV_MAX_PROBLEM_TEXT_CHARS    * sizeof( wchar_t ) )
  #define CWBSV_MAX_FAIL_PRODUCT_ID_BYTES      ( CWBSV_MAX_FAIL_PRODUCT_ID_CHARS * sizeof( wchar_t ) )
  #define CWBSV_MAX_FAIL_VERSION_BYTES         ( CWBSV_MAX_FAIL_VERSION_CHARS    * sizeof( wchar_t ) )
  #define CWBSV_MAX_CURRENT_FIX_BYTES          ( CWBSV_MAX_CURRENT_FIX_CHARS     * sizeof( wchar_t ) )
  #define CWBSV_MAX_PREVIOUS_FIX_BYTES         ( CWBSV_MAX_PREVIOUS_FIX_CHARS    * sizeof( wchar_t ) )
  #define CWBSV_MAX_FAIL_PATH_BYTES            ( CWBSV_MAX_FAIL_PATH_CHARS       * sizeof( wchar_t ) )
  #define CWBSV_MAX_FAIL_MODULE_BYTES          ( CWBSV_MAX_FAIL_MODULE_CHARS     * sizeof( wchar_t ) )
  #define CWBSV_MAX_FAIL_METHOD_BYTES          ( CWBSV_MAX_FAIL_METHOD_CHARS     * sizeof( wchar_t ) )
  #define CWBSV_MAX_SYMPTOM_STRING_BYTES       ( CWBSV_MAX_SYMPTOM_STRING_CHARS  * sizeof( wchar_t ) )
  #define CWBSV_MAX_ORIGIN_SYS_ID_BYTES        ( CWBSV_MAX_ORIGIN_SYS_ID_CHARS   * sizeof( wchar_t ) )
  #define CWBSV_MAX_ORIGIN_IP_ADDR_BYTES       ( CWBSV_MAX_ORIGIN_IP_ADDR_CHARS  * sizeof( wchar_t ) )
  #define CWBSV_MAX_MSGFILE_NAME_BYTES         ( CWBSV_MAX_MSGFILE_NAME_CHARS    * sizeof( wchar_t ) )
  #define CWBSV_MAX_MSGFILE_LIBR_BYTES         ( CWBSV_MAX_MSGFILE_LIBR_CHARS    * sizeof( wchar_t ) )
#else
  #define CWBSV_MAX_FILE_PATH_BYTES            CWBSV_MAX_FILE_PATH_CHARS
  #define CWBSV_MAX_PRODUCT_ID_BYTES           CWBSV_MAX_PRODUCT_ID_CHARS
  #define CWBSV_MAX_COMP_ID_BYTES              CWBSV_MAX_COMP_ID_CHARS
  #define CWBSV_MAX_DATE_VALUE_BYTES           CWBSV_MAX_DATE_VALUE_CHARS
  #define CWBSV_MAX_TIME_VALUE_BYTES           CWBSV_MAX_TIME_VALUE_CHARS
  #define CWBSV_MAX_PROBLEM_ID_BYTES           CWBSV_MAX_PROBLEM_ID_CHARS
  #define CWBSV_MAX_PROBLEM_TEXT_BYTES         CWBSV_MAX_PROBLEM_TEXT_CHARS
  #define CWBSV_MAX_FAIL_PRODUCT_ID_BYTES      CWBSV_MAX_FAIL_PRODUCT_ID_CHARS
  #define CWBSV_MAX_FAIL_VERSION_BYTES         CWBSV_MAX_FAIL_VERSION_CHARS
  #define CWBSV_MAX_CURRENT_FIX_BYTES          CWBSV_MAX_CURRENT_FIX_CHARS
  #define CWBSV_MAX_PREVIOUS_FIX_BYTES         CWBSV_MAX_PREVIOUS_FIX_CHARS
  #define CWBSV_MAX_FAIL_PATH_BYTES            CWBSV_MAX_FAIL_PATH_CHARS
  #define CWBSV_MAX_FAIL_MODULE_BYTES          CWBSV_MAX_FAIL_MODULE_CHARS
  #define CWBSV_MAX_FAIL_METHOD_BYTES          CWBSV_MAX_FAIL_METHOD_CHARS
  #define CWBSV_MAX_SYMPTOM_STRING_BYTES       CWBSV_MAX_SYMPTOM_STRING_CHARS
  #define CWBSV_MAX_ORIGIN_SYS_ID_BYTES        CWBSV_MAX_ORIGIN_SYS_ID_CHARS
  #define CWBSV_MAX_ORIGIN_IP_ADDR_BYTES       CWBSV_MAX_ORIGIN_IP_ADDR_CHARS
  #define CWBSV_MAX_MSGFILE_NAME_BYTES         CWBSV_MAX_MSGFILE_NAME_CHARS
  #define CWBSV_MAX_MSGFILE_LIBR_BYTES         CWBSV_MAX_MSGFILE_LIBR_CHARS
#endif

#define CWBSV_MAX_FILE_PATH                    CWBSV_MAX_FILE_PATH_BYTES
#define CWBSV_MAX_PRODUCT_ID                   CWBSV_MAX_PRODUCT_ID_BYTES
#define CWBSV_MAX_COMP_ID                      CWBSV_MAX_COMP_ID_BYTES
#define CWBSV_MAX_DATE_VALUE                   CWBSV_MAX_DATE_VALUE_BYTES
#define CWBSV_MAX_TIME_VALUE                   CWBSV_MAX_TIME_VALUE_BYTES
#define CWBSV_MAX_PROBLEM_ID                   CWBSV_MAX_PROBLEM_ID_BYTES
#define CWBSV_MAX_PROBLEM_TEXT                 CWBSV_MAX_PROBLEM_TEXT_BYTES
#define CWBSV_MAX_FAIL_PRODUCT_ID              CWBSV_MAX_FAIL_PRODUCT_ID_BYTES
#define CWBSV_MAX_FAIL_VERSION                 CWBSV_MAX_FAIL_VERSION_BYTES
#define CWBSV_MAX_CURRENT_FIX                  CWBSV_MAX_CURRENT_FIX_BYTES
#define CWBSV_MAX_PREVIOUS_FIX                 CWBSV_MAX_PREVIOUS_FIX_BYTES
#define CWBSV_MAX_FAIL_PATH                    CWBSV_MAX_FAIL_PATH_BYTES
#define CWBSV_MAX_FAIL_MODULE                  CWBSV_MAX_FAIL_MODULE_BYTES
#define CWBSV_MAX_FAIL_METHOD                  CWBSV_MAX_FAIL_METHOD_BYTES
#define CWBSV_MAX_SYMPTOM_STRING               CWBSV_MAX_SYMPTOM_STRING_BYTES
#define CWBSV_MAX_ORIGIN_SYS_ID                CWBSV_MAX_ORIGIN_SYS_ID_BYTES
#define CWBSV_MAX_ORIGIN_IP_ADDR               CWBSV_MAX_ORIGIN_IP_ADDR_BYTES
#define CWBSV_MAX_MSGFILE_NAME                 CWBSV_MAX_MSGFILE_NAME_BYTES
#define CWBSV_MAX_MSGFILE_LIBR                 CWBSV_MAX_MSGFILE_LIBR_BYTES



/*------------------------------------------------------------------*/
/* DEFINES: CWBSV.H specific return codes                           */
/*------------------------------------------------------------------*/
#define CWBSV_START CWB_LAST+1         /* CWB_LAST defined in CWB.H */

#define CWBSV_INVALID_FILE_TYPE        CWBSV_START
#define CWBSV_INVALID_RECORD_TYPE      CWBSV_START+1
#define CWBSV_INVALID_EVENT_TYPE       CWBSV_START+2
#define CWBSV_NO_ERROR_MESSAGES        CWBSV_START+3
#define CWBSV_ATTRIBUTE_NOT_SET        CWBSV_START+4
#define CWBSV_INVALID_MSG_CLASS        CWBSV_START+5
#define CWBSV_LOG_NOT_STARTED          CWBSV_START+6

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_ClearServiceFile                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Clears the service file identified by the handle provided.     */
/*   This means all service records are deleted and the service     */
/*   file will be empty.                                            */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ServiceFileHandle serviceFileHandle - input              */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_OpenServiceFile() API.                               */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*     Any returned messages will be written to this object.  It    */
/*     is created with the cwbSV_CreateErrHandle API.  The          */
/*     messages may be retrieved through the cwbSV_GetErrText API.  */
/*     If the parameter is set to zero, no messages will be         */
/*     retrieved.                                                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_FILE_IO_ERROR - File could not be cleared.                 */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_ClearServiceFile(
                             cwbSV_ServiceFileHandle serviceFileHandle,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_CloseServiceFile                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Closes the service file identified by the handle provided.     */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ServiceFileHandle serviceFileHandle - input              */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_OpenServiceFile() function.                          */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*     Any returned messages will be written to this object.  It    */
/*     is created with the cwbSV_CreateErrHandle API.  The          */
/*     messages may be retrieved through the cwbSV_GetErrText API.  */
/*     If the parameter is set to zero, no messages will be         */
/*     retrieved.                                                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_FILE_IO_ERROR - File could not be closed.                  */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_CloseServiceFile(
                             cwbSV_ServiceFileHandle serviceFileHandle,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_CreateErrHandle                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   This function creates an error message object and returns a    */
/*   handle to it. This error handle can be passed to Client        */
/*   Access/400 API's that support it. If an error occurs on one    */
/*   of these API's, the error handle can be used to retrieve the   */
/*   error messages associated with the API error.                  */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ErrHandle * errorHandle - output                         */
/*       Pointer to a cwbSV_ErrHandle where the handle will be      */
/*       returned.                                                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - NULL passed as handle address            */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory to create handle.  */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_CreateErrHandle(
                             cwbSV_ErrHandle *errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_CreateMessageTextHandle                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   This function creates a message text object and returns a      */
/*   handle to it. This message handle can be used in your program  */
/*   to write message text to the currently active history log.     */
/*   The message text is supplied in a buffer passed on the         */
/*   cwbSV_LogMessageText() API.                                    */
/*                                                                  */
/* Parameters:                                                      */
/*   char * productID - input                                       */
/*       Points to a null-terminated string that contains a         */
/*       product identifier to be used on this message entry.       */
/*       Parameter is optional, if null, no productID is set.       */
/*       NOTE: A maximum of CWBSV_MAX_PRODUCT_ID_CHARS characters   */
/*             will be logged for the product ID. Larger strings    */
/*             will be truncated.                                   */
/*                                                                  */
/*   char * componentID - input                                     */
/*       Points to a null-terminated string that contains a         */
/*       component identifier to be used on this message entry.     */
/*       Parameter is optional, if null, no componentID is set.     */
/*       NOTE: A maximum of CWBSV_MAX_COMP_ID_CHARS characters will */
/*             be logged for the component ID. Larger strings       */
/*             will be truncated.                                   */
/*                                                                  */
/*   cwbSV_MessageTextHandle * messageTextHandle - output           */
/*       Pointer to a cwbSV_MessageTextHandle where the handle      */
/*       will be returned. This handle should be used in            */
/*       subsequent calls to the message text functions.            */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory to create handle.  */
/*                                                                  */
/* Usage Notes:                                                     */
/*   It is recommended that you set a unique product ID and         */
/*   component ID in the message handle before using it to log      */
/*   message text. These ID's will distinguish your messages from   */
/*   other messages in the history log.                             */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_CreateMessageTextHandle(
                             char                    *productID,
                             char                    *componentID,
                             cwbSV_MessageTextHandle *messageTextHandle);

unsigned int CWB_ENTRY cwbSV_CreateMessageTextHandleW(
                             const wchar_t           *productID,
                             const wchar_t           *componentID,
                             cwbSV_MessageTextHandle *messageTextHandle);

#if ( defined(CWB_UNICODE) )
   #define cwbSV_CreateMessageTextHandle cwbSV_CreateMessageTextHandleW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_CreateServiceRecHandle                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   This function creates a service record object and returns a    */
/*   handle to it. This handle is used to access information        */
/*   contained in service file records.                             */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ServiceRecHandle * serviceRecHandle - output             */
/*       Pointer to a cwbSV_ServiceRecordHandle where the handle    */
/*       will be returned. This handle should be used in            */
/*       subsequent calls to the service record functions.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - NULL passed as handle address.           */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory to create handle.  */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This handle can be used in your program to read records from   */
/*   an open service file and extract information from the record.  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_CreateServiceRecHandle(
                             cwbSV_ServiceRecHandle *serviceRecHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_CreateTraceAPIHandle                                     */
/*                                                                  */
/* Purpose:                                                         */
/*   This function creates a trace API object and returns a handle  */
/*   to it. This trace API handle can be used in your program to    */
/*   log entry into and exit from an API entry point.               */
/*                                                                  */
/* Parameters:                                                      */
/*   char * productID - input                                       */
/*       Points to a null-terminated string that contains a         */
/*       product identifier to be used on this message entry.       */
/*       Parameter is optional, if null, no productID is set.       */
/*       NOTE: A maximum of CWBSV_MAX_PRODUCT_ID_CHARS characters   */
/*             will be logged for the product ID. Larger strings    */
/*             will be truncated.                                   */
/*                                                                  */
/*   char * componentID - input                                     */
/*       Points to a null-terminated string that contains a         */
/*       component identifier to be used on this message entry.     */
/*       Parameter is optional, if null, no componentID is set.     */
/*       NOTE: A maximum of CWBSV_MAX_COMP_ID_CHARS characters will */
/*             be logged for the component ID. Larger strings       */
/*             will be truncated.                                   */
/*                                                                  */
/*   cwbSV_TraceAPIHandle * traceAPIHandle - output                 */
/*       Pointer to a cwbSV_TraceAPIHandle where the handle         */
/*       will be returned. This handle should be used in            */
/*       subsequent calls to the trace API functions.               */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory to create handle.  */
/*                                                                  */
/* Usage Notes:                                                     */
/*   It is recommended that you set a unique product ID and         */
/*   component ID in the trace data handle before using it to log   */
/*   trace entries. These ID's will distinguish your trace entries  */
/*   from other entries in the trace file.                          */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_CreateTraceAPIHandle(
                             char                 *productID,
                             char                 *componentID,
                             cwbSV_TraceAPIHandle *traceAPIHandle);

unsigned int CWB_ENTRY cwbSV_CreateTraceAPIHandleW(
                             const wchar_t        *productID,
                             const wchar_t        *componentID,
                             cwbSV_TraceAPIHandle *traceAPIHandle);

#if ( defined(CWB_UNICODE) )
   #define cwbSV_CreateTraceAPIHandle cwbSV_CreateTraceAPIHandleW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_CreateTraceDataHandle                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   This function creates a trace data object and returns a        */
/*   handle to it. This trace handle can be used in your program to */
/*   log trace information to trace files. The trace information is */
/*   supplied in a buffer passed on the cwbSV_LogTraceData() API.   */
/*                                                                  */
/* Parameters:                                                      */
/*   char * productID - input                                       */
/*       Points to a null-terminated string that contains a         */
/*       product identifier to be used on this message entry.       */
/*       Parameter is optional, if null, no productID is set.       */
/*       NOTE: A maximum of CWBSV_MAX_PRODUCT_ID_CHARS characters   */
/*             will be logged for the product ID. Larger strings    */
/*             will be truncated.                                   */
/*                                                                  */
/*   char * componentID - input                                     */
/*       Points to a null-terminated string that contains a         */
/*       component identifier to be used on this message entry.     */
/*       Parameter is optional, if null, no componentID is set.     */
/*       NOTE: A maximum of CWBSV_MAX_COMP_ID_CHARS characters      */
/*             will be logged for the component ID. Larger strings  */
/*             will be truncated.                                   */
/*                                                                  */
/*   cwbSV_TraceDataHandle * traceDataHandle - output               */
/*       Pointer to a cwbSV_TraceDataHandle where the handle        */
/*       will be returned. This handle should be used in            */
/*       subsequent calls to the trace data functions.              */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory to create handle.  */
/*                                                                  */
/* Usage Notes:                                                     */
/*   It is recommended that you set a unique product ID and         */
/*   component ID in the trace data handle before using it to log   */
/*   trace entries. These ID's will distinguish your trace entries  */
/*   from other entries in the trace file.                          */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_CreateTraceDataHandle(
                             char                  *productID,
                             char                  *componentID,
                             cwbSV_TraceDataHandle *traceDataHandle);

unsigned int CWB_ENTRY cwbSV_CreateTraceDataHandleW(
                             const wchar_t         *productID,
                             const wchar_t         *componentID,
                             cwbSV_TraceDataHandle *traceDataHandle);

#if ( defined(CWB_UNICODE) )
   #define  cwbSV_CreateTraceDataHandle cwbSV_CreateTraceDataHandleW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_CreateTraceSPIHandle                                     */
/*                                                                  */
/* Purpose:                                                         */
/*   This function creates a trace SPI object and returns a handle  */
/*   to it. This trace SPI handle can be used in your program to    */
/*   log entry into and exit from an SPI entry point.               */
/*                                                                  */
/* Parameters:                                                      */
/*   char * productID - input                                       */
/*       Points to a null-terminated string that contains a         */
/*       product identifier to be used on this message entry.       */
/*       Parameter is optional, if null, no productID is set.       */
/*       NOTE: A maximum of CWBSV_MAX_PRODUCT_ID_CHARS characters   */
/*             will be logged for the product ID. Larger strings    */
/*             will be truncated.                                   */
/*                                                                  */
/*   char * componentID - input                                     */
/*       Points to a null-terminated string that contains a         */
/*       component identifier to be used on this message entry.     */
/*       Parameter is optional, if null, no componentID is set.     */
/*       NOTE: A maximum of CWBSV_MAX_COMP_ID_CHARS characters will */
/*             be logged for the component ID. Larger strings       */
/*             will be truncated.                                   */
/*                                                                  */
/*   cwbSV_TraceSPIHandle * traceSPIHandle - output                 */
/*       Pointer to a cwbSV_TraceSPIHandle where the handle         */
/*       will be returned. This handle should be used in            */
/*       subsequent calls to the trace SPI functions.               */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory to create handle.  */
/*                                                                  */
/* Usage Notes:                                                     */
/*   It is recommended that you set a unique product ID and         */
/*   component ID in the trace data handle before using it to log   */
/*   trace entries. These ID's will distinguish your trace entries  */
/*   from other entries in the trace file.                          */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_CreateTraceSPIHandle(
                             char                 *productID,
                             char                 *componentID,
                             cwbSV_TraceSPIHandle *traceSPIHandle);

unsigned int CWB_ENTRY cwbSV_CreateTraceSPIHandleW(
                             const wchar_t        *productID,
                             const wchar_t        *componentID,
                             cwbSV_TraceSPIHandle *traceSPIHandle);

#if ( defined(CWB_UNICODE) )
   #define  cwbSV_CreateTraceSPIHandle cwbSV_CreateTraceSPIHandleW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_DeleteErrHandle                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   This function deletes the error message object that is         */
/*   identified by the handle provided.                             */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateErrHandle() API.                               */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This call should be made when the handle is no longer needed.  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_DeleteErrHandle(
                             cwbSV_ErrHandle errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_DeleteMessageTextHandle                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   This function deletes the message text object that is          */
/*   identified by the handle provided.                             */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_MessageTextHandle messageTextHandle - input              */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateMessageTextHandle() API.                       */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle passed in on request.      */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This call should be made when the handle is no longer needed.  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_DeleteMessageTextHandle(
                             cwbSV_MessageTextHandle messageTextHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_DeleteServiceRecHandle                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   This function deletes the service record object that is        */
/*   identified by the handle provided.                             */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ServiceRecHandle serviceRecHandle - input                */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateServiceRecHandle() API.                        */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This call should be made when the handle is no longer needed.  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_DeleteServiceRecHandle(
                             cwbSV_ServiceRecHandle serviceRecHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_DeleteTraceAPIHandle                                     */
/*                                                                  */
/* Purpose:                                                         */
/*   This function deletes the trace API object that is             */
/*   identified by the handle provided.                             */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_TraceAPIHandle traceAPIHandle - input                    */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateTraceAPIHandle() API.                          */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This call should be made when the handle is no longer needed.  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_DeleteTraceAPIHandle(
                             cwbSV_TraceAPIHandle traceAPIHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_DeleteTraceDataHandle                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   This function deletes the trace data object that is            */
/*   identified by the trace handle provided.                       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_TraceDataHandle traceDataHandle - input                  */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateTraceDataHandle() API.                         */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This call should be made when the handle is no longer needed.  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_DeleteTraceDataHandle(
                             cwbSV_TraceDataHandle traceDataHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_DeleteTraceSPIHandle                                     */
/*                                                                  */
/* Purpose:                                                         */
/*   This function deletes the trace SPI object that is             */
/*   identified by the handle provided.                             */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_TraceSPIHandle traceSPIHandle - input                    */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateTraceSPIHandle() API.                          */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This call should be made when the handle is no longer needed.  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_DeleteTraceSPIHandle(
                             cwbSV_TraceSPIHandle traceSPIHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetComponent                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the component ID for the service record handle         */
/*   provided.                                                      */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ServiceRecHandle serviceRecHandle - input                */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateServiceRecHandle() API.                        */
/*                                                                  */
/*   char * componentID - output                                    */
/*       Pointer to a buffer that will receive the component ID     */
/*       stored in the record identified by the handle.             */
/*                                                                  */
/*   unsigned long componentIDLength - input                        */
/*       Length, in bytes, of the componentID buffer. It should     */
/*       include space for the terminating null character. If the   */
/*       buffer is too small, the value will be truncated and       */
/*       CWB_BUFFER_OVERFLOW will be returned.                      */
/*       NOTE: The recommended size is CWBSV_MAX_COMP_ID bytes.     */
/*                                                                  */
/*   unsigned long * returnLength - output                          */
/*       Optional, may be NULL. A return address to store the       */
/*       number of bytes needed to hold the output string.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_BUFFER_OVERFLOW - Output buffer too small, data truncated. */
/*   CWB_INVALID_POINTER - NULL passed on output parm               */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The service record handle needs to be filled in by a call to   */
/*   a "read" function before calling this routine, otherwise a     */
/*   NULL string will be returned.                                  */
/*                                                                  */
/*   This function is valid for all service record types.           */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetComponent(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             char                   *componentID,
                             unsigned long           componentIDLength,
                             unsigned long          *returnLength);

unsigned int CWB_ENTRY cwbSV_GetComponentW(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             wchar_t                *componentID,
                             unsigned long           componentIDLength,
                             unsigned long          *returnLength);

#if ( defined(CWB_UNICODE) )
   #define  cwbSV_GetComponent cwbSV_GetComponentW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetCreatedBy                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   This is an obsolete API, there is no replacement API.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   CWB_NOT_SUPPORTED - Function no longer supported.              */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetCreatedBy(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             cwbSV_CreatedBy        *createdBy);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetCurrentFix                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   This is an obsolete API, there is no replacement API.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   CWB_NOT_SUPPORTED - Function no longer supported.              */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetCurrentFix(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             char                   *currentFix,
                             unsigned long           currentFixLength,
                             unsigned long          *returnLength);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetDateStamp                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the datestamp (in localized format) for the service    */
/*   record handle provided.                                        */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ServiceRecHandle serviceRecHandle - input                */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateServiceRecHandle() API.                        */
/*                                                                  */
/*   char * dateStamp - output                                      */
/*       Pointer to a buffer that will receive the datestamp        */
/*       stored in the record identified by the handle.             */
/*                                                                  */
/*   unsigned long dateStampLength - input                          */
/*       Length, in bytes, of the dateStamp buffer. It should       */
/*       include space for the terminating null character. If the   */
/*       buffer is too small, the value will be truncated and       */
/*       CWB_BUFFER_OVERFLOW will be returned.                      */
/*       NOTE: The recommended size is CWBSV_MAX_DATE_VALUE bytes.  */
/*                                                                  */
/*   unsigned long * returnLength - output                          */
/*       Optional, may be NULL. A return address to store the       */
/*       number of bytes needed to hold the output string.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_BUFFER_OVERFLOW - Output buffer too small, data truncated. */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The service record handle needs to be filled in by a call to   */
/*   a "read" function before calling this routine, otherwise a     */
/*   NULL string will be returned.                                  */
/*                                                                  */
/*   This function is valid for all service record types.           */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetDateStamp(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             char                   *dateStamp,
                             unsigned long           dateStampLength,
                             unsigned long          *returnLength);

unsigned int CWB_ENTRY cwbSV_GetDateStampW(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             wchar_t                *dateStamp,
                             unsigned long           dateStampLength,
                             unsigned long          *returnLength);

#if ( defined(CWB_UNICODE) )
   #define  cwbSV_GetDateStamp cwbSV_GetDateStampW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetErrClass                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the message class for the top-level (i.e. most recent) */
/*   message added to the error handle provided. This attribute     */
/*   indicates the message severity level.                          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateErrHandle() API.                               */
/*                                                                  */
/*   unsigned long * errorClass - output                            */
/*       Pointer to a variable that will receive the message        */
/*       severity stored in the message identified by the handle.   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWBSV_NO_ERROR_MESSAGES - No messages are in the error handle. */
/*                                                                  */
/* Usage Notes:                                                     */
/*   See #define's in cwbsv.h for errorClass return values.         */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetErrClass(
                             cwbSV_ErrHandle  errorHandle,
                             unsigned long   *errorClass);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetErrClassIndexed                                       */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the message class for the message identified by the    */
/*   index provided. This attribute indicates the message severity  */
/*   level.                                                         */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateErrHandle() API.                               */
/*                                                                  */
/*   unsigned long index - input                                    */
/*       Index value indicating which error class to return if      */
/*       multiple errors are associated with the error handle.      */
/*       The valid index range is from 1 to the number of messages  */
/*       contained in the error handle. The number of messages      */
/*       can be obtained by calling the cwbSV_GetErrCount() API.    */
/*                                                                  */
/*   unsigned long * errorClass - output                            */
/*       Pointer to a variable that will receive the message        */
/*       severity stored in the message identified by the index.    */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWBSV_NO_ERROR_MESSAGES - No messages are in the error handle. */
/*                                                                  */
/* Usage Notes:                                                     */
/*   An index value of 1 works with the lowest-level (i.e. oldest)  */
/*   message in the error handle. An index value equal to the count */
/*   returned by the cwbSV_GetErrCount() API works with the         */
/*   top-level (i.e. most recent) message in the error handle.      */
/*                                                                  */
/*   Index values less than 1 act as if 1 was passed in. Index      */
/*   values greater than the number of messages contained in the    */
/*   error handle act as if the returned count value from the       */
/*   cwbSV_GetErrCount() API was passed in.                         */
/*                                                                  */
/*   See #define's in cwbsv.h for errorClass return values.         */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetErrClassIndexed(
                             cwbSV_ErrHandle  errorHandle,
                             unsigned long    index,
                             unsigned long   *errorClass);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetErrCount                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the number of messages associated with the error       */
/*   handle provided.                                               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateErrHandle() API.                               */
/*                                                                  */
/*   unsigned long * count - output                                 */
/*       Pointer to variable that receives the number of messages   */
/*       associated with this error handle. If zero is returned,    */
/*       no errors are associated with the error handle.            */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetErrCount(
                             cwbSV_ErrHandle  errorHandle,
                             unsigned long   *count);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetErrFileName                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the message file name for the top-level                */
/*   (i.e. most recent) message added to the error handle provided. */
/*   This message attribute only pertains to messages returned from */
/*   the AS/400. The file name is the name of the AS/400 message    */
/*   file containing the message.                                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateErrHandle() API.                               */
/*                                                                  */
/*   char * fileName - output                                       */
/*       Pointer to a buffer that will receive the message file     */
/*       name stored in the error identified by the handle.         */
/*       The value returned is an ASCIIZ string.                    */
/*                                                                  */
/*   unsigned long fileNameLength - input                           */
/*       Length, in bytes, of the fileName buffer. It should        */
/*       include space for the terminating null character. If the   */
/*       buffer is too small, the value will be truncated and       */
/*       CWB_BUFFER_OVERFLOW will be returned.                      */
/*       NOTE: The recommended size is CWBSV_MAX_MSGFILE_NAME bytes.*/
/*                                                                  */
/*   unsigned long * returnLength - output                          */
/*       Optional, may be NULL. A return address to store the       */
/*       number of bytes needed to hold the output string.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_BUFFER_OVERFLOW - Output buffer too small, data truncated. */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWBSV_NO_ERROR_MESSAGES - No messages are in the error handle. */
/*   CWBSV_ATTRIBUTE_NOT_SET - Attribute not set in current message.*/
/*                                                                  */
/* Usage Notes:                                                     */
/*   AS/400 messages may be added to the error handle when using    */
/*   the cwbRC_CallPgm() and cwbRC_RunCmd() API's. In these cases,  */
/*   you can use this API to retrieve the message file name for     */
/*   the AS/400 messages contained in the error handle.             */
/*                                                                  */
/*   If there is no message file name attribute for the message,    */
/*   return code CWBSV_ATTRIBUTE_NOT_SET will be returned.          */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetErrFileName(
                             cwbSV_ErrHandle  errorHandle,
                             char            *fileName,
                             unsigned long    fileNameLength,
                             unsigned long   *returnLength);

unsigned int CWB_ENTRY cwbSV_GetErrFileNameW(
                             cwbSV_ErrHandle  errorHandle,
                             wchar_t         *fileName,
                             unsigned long    fileNameLength,
                             unsigned long   *returnLength);

#if ( defined(CWB_UNICODE) )
   #define  cwbSV_GetErrFileName cwbSV_GetErrFileNameW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetErrFileNameIndexed                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the message file name for the message identified by    */
/*   the index provided. This message attribute only pertains to    */
/*   messages returned from the AS/400. The file name is the name   */
/*   of the AS/400 message file containing the message.             */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateErrHandle() API.                               */
/*                                                                  */
/*   unsigned long index - input                                    */
/*       Index value indicating which message file name to return   */
/*       if multiple errors are associated with the error handle.   */
/*       The valid index range is from 1 to the number of messages  */
/*       contained in the error handle. The number of messages      */
/*       can be obtained by calling the cwbSV_GetErrCount() API.    */
/*                                                                  */
/*   char * fileName - output                                       */
/*       Pointer to a buffer that will receive the message file     */
/*       name stored in the error identified by the index.          */
/*       The value returned is an ASCIIZ string.                    */
/*                                                                  */
/*   unsigned long fileNameLength - input                           */
/*       Length, in bytes, of the fileName buffer. It should        */
/*       include space for the terminating null character. If the   */
/*       buffer is too small, the value will be truncated and       */
/*       CWB_BUFFER_OVERFLOW will be returned.                      */
/*       NOTE: The recommended size is CWBSV_MAX_MSGFILE_NAME bytes.*/
/*                                                                  */
/*   unsigned long * returnLength - output                          */
/*       Optional, may be NULL. A return address to store the       */
/*       number of bytes needed to hold the output string.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_BUFFER_OVERFLOW - Output buffer too small, data truncated. */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWBSV_NO_ERROR_MESSAGES - No messages are in the error handle. */
/*   CWBSV_ATTRIBUTE_NOT_SET - Attribute not set in current message.*/
/*                                                                  */
/* Usage Notes:                                                     */
/*   AS/400 messages may be added to the error handle when using    */
/*   the cwbRC_CallPgm() and cwbRC_RunCmd() API's. In these cases,  */
/*   you can use this API to retrieve the message file name for     */
/*   the AS/400 messages contained in the error handle.             */
/*                                                                  */
/*   If there is no message file name attribute for the message,    */
/*   return code CWBSV_ATTRIBUTE_NOT_SET will be returned.          */
/*                                                                  */
/*   An index value of 1 works with the lowest-level (i.e. oldest)  */
/*   message in the error handle. An index value equal to the count */
/*   returned by the cwbSV_GetErrCount() API works with the         */
/*   top-level (i.e. most recent) message in the error handle.      */
/*                                                                  */
/*   Index values less than 1 act as if 1 was passed in. Index      */
/*   values greater than the number of messages contained in the    */
/*   error handle act as if the returned count value from the       */
/*   cwbSV_GetErrCount() API was passed in.                         */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetErrFileNameIndexed(
                             cwbSV_ErrHandle  errorHandle,
                             unsigned long    index,
                             char            *fileName,
                             unsigned long    fileNameLength,
                             unsigned long   *returnLength);

unsigned int CWB_ENTRY cwbSV_GetErrFileNameIndexedW(
                             cwbSV_ErrHandle  errorHandle,
                             unsigned long    index,
                             wchar_t         *fileName,
                             unsigned long    fileNameLength,
                             unsigned long   *returnLength);

#if ( defined(CWB_UNICODE) )
   #define  cwbSV_GetErrFileNameIndexed cwbSV_GetErrFileNameIndexedW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetErrLibName                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the message file library name for the top-level        */
/*   (i.e. most recent) message added to the error handle provided. */
/*   This message attribute only pertains to messages returned      */
/*   from the AS/400. The library name is the  name of the AS/400   */
/*   library containing the message file for the message.           */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateErrHandle() API.                               */
/*                                                                  */
/*   char * libraryName - output                                    */
/*       Pointer to a buffer that will receive the message file     */
/*       library name stored in the error identified by the handle. */
/*       The value returned is an ASCIIZ string.                    */
/*                                                                  */
/*   unsigned long libraryNameLength - input                        */
/*       Length, in bytes, of the libraryName buffer. It should     */
/*       include space for the terminating null character. If the   */
/*       buffer is too small, the value will be truncated and       */
/*       CWB_BUFFER_OVERFLOW will be returned.                      */
/*       NOTE: The recommended size is CWBSV_MAX_MSGFILE_LIBR bytes.*/
/*                                                                  */
/*   unsigned long * returnLength - output                          */
/*       Optional, may be NULL. A return address to store the       */
/*       number of bytes needed to hold the output string.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_BUFFER_OVERFLOW - Output buffer too small, data truncated. */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWBSV_NO_ERROR_MESSAGES - No messages are in the error handle. */
/*   CWBSV_ATTRIBUTE_NOT_SET - Attribute not set in current message.*/
/*                                                                  */
/* Usage Notes:                                                     */
/*   AS/400 messages may be added to the error handle when using    */
/*   the cwbRC_CallPgm() and cwbRC_RunCmd() API's. In these cases,  */
/*   you can use this API to retrieve the message file library      */
/*   name for the AS/400 messages contained in the error handle.    */
/*                                                                  */
/*   If there is no message file library name attribute for the     */
/*   message, return code CWBSV_ATTRIBUTE_NOT_SET will be returned. */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetErrLibName(
                             cwbSV_ErrHandle  errorHandle,
                             char            *libraryName,
                             unsigned long    libraryNameLength,
                             unsigned long   *returnLength);

unsigned int CWB_ENTRY cwbSV_GetErrLibNameW(
                             cwbSV_ErrHandle  errorHandle,
                             wchar_t         *libraryName,
                             unsigned long    libraryNameLength,
                             unsigned long   *returnLength);

#if ( defined(CWB_UNICODE) )
   #define  cwbSV_GetErrLibName cwbSV_GetErrLibNameW
#endif


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetErrLibNameIndexed                                     */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the message file library name for the message          */
/*   identified by the index provided. This message attribute only  */
/*   pertains to messages returned from the AS/400. The library     */
/*   name is the name of the AS/400 library containing the message  */
/*   file for the message.                                          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateErrHandle() API.                               */
/*                                                                  */
/*   unsigned long index - input                                    */
/*       Index value indicating which message file library name to  */
/*       return if multiple errors are associated with the error    */
/*       handle. The valid index range is from 1 to the number of   */
/*       messages contained in the error handle. The number of      */
/*       messages can be obtained by calling the                    */
/*       cwbSV_GetErrCount() API.                                   */
/*                                                                  */
/*   char * libraryName - output                                    */
/*       Pointer to a buffer that will receive the message file     */
/*       library name stored in the error identified by the index.  */
/*       The value returned is an ASCIIZ string.                    */
/*                                                                  */
/*   unsigned long libraryNameLength - input                        */
/*       Length, in bytes, of the libraryName buffer. It should     */
/*       include space for the terminating null character. If the   */
/*       buffer is too small, the value will be truncated and       */
/*       CWB_BUFFER_OVERFLOW will be returned.                      */
/*       NOTE: The recommended size is CWBSV_MAX_MSGFILE_LIBR bytes.*/
/*                                                                  */
/*   unsigned long * returnLength - output                          */
/*       Optional, may be NULL. A return address to store the       */
/*       number of bytes needed to hold the output string.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_BUFFER_OVERFLOW - Output buffer too small, data truncated. */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWBSV_NO_ERROR_MESSAGES - No messages are in the error handle. */
/*   CWBSV_ATTRIBUTE_NOT_SET - Attribute not set in current message.*/
/*                                                                  */
/* Usage Notes:                                                     */
/*   AS/400 messages may be added to the error handle when using    */
/*   the cwbRC_CallPgm() and cwbRC_RunCmd() API's. In these cases,  */
/*   you can use this API to retrieve the message file library      */
/*   name for the AS/400 messages contained in the error handle.    */
/*                                                                  */
/*   If there is no message file library name attribute for the     */
/*   message, return code CWBSV_ATTRIBUTE_NOT_SET will be returned. */
/*                                                                  */
/*   An index value of 1 works with the lowest-level (i.e. oldest)  */
/*   message in the error handle. An index value equal to the count */
/*   returned by the cwbSV_GetErrCount() API works with the         */
/*   top-level (i.e. most recent) message in the error handle.      */
/*                                                                  */
/*   Index values less than 1 act as if 1 was passed in. Index      */
/*   values greater than the number of messages contained in the    */
/*   error handle act as if the returned count value from the       */
/*   cwbSV_GetErrCount() API was passed in.                         */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetErrLibNameIndexed(
                             cwbSV_ErrHandle  errorHandle,
                             unsigned long    index,
                             char            *libraryName,
                             unsigned long    libraryNameLength,
                             unsigned long   *returnLength);

unsigned int CWB_ENTRY cwbSV_GetErrLibNameIndexedW(
                             cwbSV_ErrHandle  errorHandle,
                             unsigned long    index,
                             wchar_t         *libraryName,
                             unsigned long    libraryNameLength,
                             unsigned long   *returnLength);

#if ( defined(CWB_UNICODE) )
   #define  cwbSV_GetErrLibNameIndexed cwbSV_GetErrLibNameIndexedW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetErrSubstText                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the message substitution data for the top-level        */
/*   (i.e. most recent) message identified by the error handle      */
/*   provided. This message attribute only pertains to messages     */
/*   returned from the AS/400. The substitution data is             */
/*   inserted into the substitution variable fields defined for     */
/*   the message.                                                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateErrHandle() API.                               */
/*                                                                  */
/*   char * substitutionData - output                               */
/*       Pointer to a buffer that will receive the substitution     */
/*       data for the message identified by the handle.             */
/*                                                                  */
/*       Note: The data returned is binary, hence it is NOT         */
/*             returned as an ASCIIZ string. Any character strings  */
/*             contained in the substitution text are returned      */
/*             as EBCDIC values.                                    */
/*                                                                  */
/*   unsigned long substitutionDataLength - input                   */
/*       Length of the substitutionData buffer.  If the buffer      */
/*       is too small, the value will be truncated and              */
/*       CWB_BUFFER_OVERFLOW will be returned.                      */
/*                                                                  */
/*   unsigned long * returnLength - output                          */
/*       Optional, may be NULL. A return address to store the       */
/*       number of bytes needed to hold the output data if the      */
/*       receive buffer is too small. It will also be set to the    */
/*       actual number of bytes of output data returned upon        */
/*       successful completion.                                     */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_BUFFER_OVERFLOW - Output buffer too small, data truncated. */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWBSV_NO_ERROR_MESSAGES - No messages are in the error handle. */
/*   CWBSV_ATTRIBUTE_NOT_SET - Attribute not set in current message.*/
/*                                                                  */
/* Usage Notes:                                                     */
/*   AS/400 messages may be added to the error handle when using    */
/*   the cwbRC_CallPgm() and cwbRC_RunCmd() API's. In these cases,  */
/*   you can use this API to retrieve the substitution data for     */
/*   the AS/400 messages contained in the error handle.             */
/*                                                                  */
/*   If there is no substitution data for the message, return code  */
/*   CWBSV_ATTRIBUTE_NOT_SET will be returned.                      */
/*                                                                  */
/*   Use the returnLength parameter to determine the actual number  */
/*   of bytes returned in the substitution data when the return     */
/*   code is CWB_OK.                                                */
/*                                                                  */
/*   The substitution data returned on this API could be used on    */
/*   a subsequent host retrieve message API call (QSYS/QMHRTVM)     */
/*   to retrieve the format of the substitution data or to return   */
/*   secondary help text with the substitution data added in.       */
/*   Host API's are called using the cwbRC_CallPgm() API.           */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetErrSubstText(
                             cwbSV_ErrHandle  errorHandle,
                             char            *substitutionData,
                             unsigned long    substitutionDataLength,
                             unsigned long   *returnLength);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetErrSubstTextIndexed                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the message substitution data for the message          */
/*   identified by the index provided. This message attribute only  */
/*   pertains to messages returned from the AS/400. The             */
/*   substitution data is inserted into the substitution            */
/*   variable fields defined for the message.                       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateErrHandle() API.                               */
/*                                                                  */
/*   unsigned long index - input                                    */
/*       Index value indicating which substitution text to return   */
/*       if multiple errors are associated with the error handle.   */
/*       The valid index range is from 1 to the number of messages  */
/*       contained in the error handle. The number of messages can  */
/*       be obtained by calling the cwbSV_GetErrCount() API.        */
/*                                                                  */
/*   char * substitutionData - output                               */
/*       Pointer to a buffer that will receive the substitution     */
/*       data stored in the error identified by the index.          */
/*                                                                  */
/*       Note: The data returned is binary, hence it is NOT         */
/*             returned as an ASCIIZ string. Any character strings  */
/*             contained in the substitution data are returned      */
/*             as EBCDIC values.                                    */
/*                                                                  */
/*   unsigned long substitutionDataLength - input                   */
/*       Length of the receive buffer passed in. If the buffer      */
/*       is too small, the value will be truncated and              */
/*       CWB_BUFFER_OVERFLOW will be returned.                      */
/*                                                                  */
/*   unsigned long * returnLength - output                          */
/*       Optional, may be NULL. A return address to store the       */
/*       number of bytes needed to hold the output data if the      */
/*       receive buffer is too small. It will also be set to the    */
/*       actual number of bytes of output data returned upon        */
/*       successful completion.                                     */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_BUFFER_OVERFLOW - Output buffer too small, data truncated. */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWBSV_NO_ERROR_MESSAGES - No messages are in the error handle. */
/*   CWBSV_ATTRIBUTE_NOT_SET - Attribute not set in current message.*/
/*                                                                  */
/* Usage Notes:                                                     */
/*   AS/400 messages may be added to the error handle when using    */
/*   the cwbRC_CallPgm() and cwbRC_RunCmd() API's. In these cases,  */
/*   you can use this API to retrieve the substitution data for     */
/*   the AS/400 messages contained in the error handle.             */
/*                                                                  */
/*   If there is no substitution data for the message, return code  */
/*   CWBSV_ATTRIBUTE_NOT_SET will be returned.                      */
/*                                                                  */
/*   An index value of 1 works with the lowest-level (i.e. oldest)  */
/*   message in the error handle. An index value equal to the count */
/*   returned by the cwbSV_GetErrCount() API works with the         */
/*   top-level (i.e. most recent) message in the error handle.      */
/*                                                                  */
/*   Index values less than 1 act as if 1 was passed in. Index      */
/*   values greater than the number of messages contained in the    */
/*   error handle act as if the returned count value from the       */
/*   cwbSV_GetErrCount() API was passed in.                         */
/*                                                                  */
/*   Use the returnLength parameter to determine the actual number  */
/*   of bytes returned in the substitution text when the return     */
/*   code is CWB_OK.                                                */
/*                                                                  */
/*   The substitution data returned on this API could be used on    */
/*   a subsequent host retrieve message API call (QSYS/QMHRTVM)     */
/*   to retrieve the format of the substitution data or to return   */
/*   secondary help text with the substitution data added in.       */
/*   Host API's are called using the cwbRC_CallPgm() API.           */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetErrSubstTextIndexed(
                             cwbSV_ErrHandle  errorHandle,
                             unsigned long    index,
                             char            *substitutionText,
                             unsigned long    substitutionTextLength,
                             unsigned long   *returnLength);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetErrText                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the message text for the top-level (i.e. most recent)  */
/*   error identified by the error handle provided.                 */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateErrHandle() API.                               */
/*                                                                  */
/*   char * messageText - output                                    */
/*       Pointer to a buffer that will receive the message text     */
/*       stored in the error identified by the handle.              */
/*       The value returned is an ASCIIZ string.                    */
/*                                                                  */
/*   unsigned long messageTextLength - input                        */
/*       Length, in bytes, of the messageText buffer. It should     */
/*       include space for the terminating null character. If the   */
/*       buffer is too small, the value will be truncated and       */
/*       CWB_BUFFER_OVERFLOW will be returned.                      */
/*                                                                  */
/*   unsigned long * returnLength - output                          */
/*       Optional, may be NULL. A return address to store the       */
/*       number of bytes needed to hold the output string.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_BUFFER_OVERFLOW - Output buffer too small, data truncated. */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWBSV_NO_ERROR_MESSAGES - No messages are in the error handle. */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetErrText(
                             cwbSV_ErrHandle  errorHandle,
                             char            *messageText,
                             unsigned long    messageTextLength,
                             unsigned long   *returnLength);

unsigned int CWB_ENTRY cwbSV_GetErrTextW(
                             cwbSV_ErrHandle  errorHandle,
                             wchar_t         *messageText,
                             unsigned long    messageTextLength,
                             unsigned long   *returnLength);

#if ( defined(CWB_UNICODE) )
   #define  cwbSV_GetErrText cwbSV_GetErrTextW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetErrTextIndexed                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the message text for the message identified by the     */
/*   index provided.                                                */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateErrHandle() API.                               */
/*                                                                  */
/*   unsigned long index - input                                    */
/*       Index value indicating which message text to return if     */
/*       multiple errors are associated with the error handle.      */
/*       The valid index range is from 1 to the number of messages  */
/*       contained in the error handle. The number of messages can  */
/*       be obtained by calling the cwbSV_GetErrCount() API.        */
/*                                                                  */
/*   char * messageText - output                                    */
/*       Pointer to a buffer that will receive the message text     */
/*       stored in the error identified by the index.               */
/*       The value returned is an ASCIIZ string.                    */
/*                                                                  */
/*   unsigned long messageTextLength - input                        */
/*       Length, in bytes, of the messageText buffer. It should     */
/*       include space for the terminating null character. If the   */
/*       buffer is too small, the value will be truncated and       */
/*       CWB_BUFFER_OVERFLOW will be returned.                      */
/*                                                                  */
/*   unsigned long * returnLength - output                          */
/*       Optional, may be NULL. A return address to store the       */
/*       number of bytes needed to hold the output string.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_BUFFER_OVERFLOW - Output buffer too small, data truncated. */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWBSV_NO_ERROR_MESSAGES - No messages are in the error handle. */
/*                                                                  */
/* Usage Notes:                                                     */
/*   An index value of 1 works with the lowest-level (i.e. oldest)  */
/*   message in the error handle. An index value equal to the count */
/*   returned by the cwbSV_GetErrCount() API works with the         */
/*   top-level (i.e. most recent) message in the error handle.      */
/*                                                                  */
/*   Index values less than 1 act as if 1 was passed in. Index      */
/*   values greater than the number of messages contained in the    */
/*   error handle act as if the returned count value from the       */
/*   cwbSV_GetErrCount() API was passed in.                         */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetErrTextIndexed(
                             cwbSV_ErrHandle  errorHandle,
                             unsigned long    index,
                             char            *messageText,
                             unsigned long    messageTextLength,
                             unsigned long   *returnLength);

unsigned int CWB_ENTRY cwbSV_GetErrTextIndexedW(
                             cwbSV_ErrHandle  errorHandle,
                             unsigned long    index,
                             wchar_t         *messageText,
                             unsigned long    messageTextLength,
                             unsigned long   *returnLength);

#if ( defined(CWB_UNICODE) )
   #define  cwbSV_GetErrTextIndexed  cwbSV_GetErrTextIndexedW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetFailMethod                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   This is an obsolete API, there is no replacement API.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   CWB_NOT_SUPPORTED - Function no longer supported.              */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetFailMethod(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             char                   *failMethod,
                             unsigned long           failMethodLength,
                             unsigned long          *returnLength);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetFailModule                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   This is an obsolete API, there is no replacement API.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   CWB_NOT_SUPPORTED - Function no longer supported.              */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetFailModule(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             char                   *failModule,
                             unsigned long           failModuleLength,
                             unsigned long          *returnLength);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetFailPathName                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   This is an obsolete API, there is no replacement API.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   CWB_NOT_SUPPORTED - Function no longer supported.              */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetFailPathName(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             char                   *failPath,
                             unsigned long           failPathLength,
                             unsigned long          *returnLength);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetFailProductID                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   This is an obsolete API, there is no replacement API.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   CWB_NOT_SUPPORTED - Function no longer supported.              */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetFailProductID(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             char                   *failProductID,
                             unsigned long           failProductIDLength,
                             unsigned long          *returnLength);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetFailVersion                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   This is an obsolete API, there is no replacement API.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   CWB_NOT_SUPPORTED - Function no longer supported.              */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetFailVersion(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             char                   *failVersion,
                             unsigned long           failVersionLength,
                             unsigned long          *returnLength);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetMaxRecordSize                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the size (in bytes) of the largest record in the       */
/*   service file identified by the file handle provided.           */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ServiceFileHandle serviceFileHandle - input              */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_OpenServiceFile() API.                               */
/*                                                                  */
/*   unsigned long * maxRecordSize - output                         */
/*       Pointer to variable that receives the size of the          */
/*       largest record in the file.                                */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetMaxRecordSize(
                             cwbSV_ServiceFileHandle  serviceFile,
                             unsigned long           *maxRecordSize);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetMessageText                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the message text portion of the service record object  */
/*   identified by the handle provided.                             */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ServiceRecHandle serviceRecHandle - input                */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateServiceRecHandle() API.                        */
/*                                                                  */
/*   char * messageText - output                                    */
/*       Pointer to a buffer that will receive the message text     */
/*       stored in the record identified by the handle.             */
/*                                                                  */
/*   unsigned long messageTextLength - input                        */
/*       Length of the messageText buffer, in bytes. If the buffer  */
/*       is too small, the value will be truncated and              */
/*       CWB_BUFFER_OVERFLOW will be returned.                      */
/*                                                                  */
/*   unsigned long * returnLength - output                          */
/*       Optional, may be NULL. A return address to store the       */
/*       number of bytes needed to hold the output data.            */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_BUFFER_OVERFLOW - Output buffer too small, data truncated. */
/*   CWB_INVALID_POINTER - NULL passed on output parm               */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWBSV_INVALID_RECORD_TYPE - Type is not CWBSV_MESSAGE_REC.     */
/*                                                                  */
/* Usage Notes:                                                     */
/*   If the record type is not CWBSV_MESSAGE_REC, a return code of  */
/*   CWBSV_INVALID_RECORD_TYPE will be returned.                    */
/*   (note: cwbSV_GetServiceType() returns the current record type) */
/*                                                                  */
/*   The message text returned is NOT guaranteed to be NULL-        */
/*   terminated.  It will be if it was when it was logged.          */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetMessageText(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             char                   *messageText,
                             unsigned long           messageTextLength,
                             unsigned long          *returnLength);

unsigned int CWB_ENTRY cwbSV_GetMessageTextW(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             wchar_t                *messageText,
                             unsigned long           messageTextLength,
                             unsigned long          *returnLength);

#if ( defined(CWB_UNICODE) )
   #define  cwbSV_GetMessageText cwbSV_GetMessageTextW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetOriginSystemID                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   This is an obsolete API, there is no replacement API.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   CWB_NOT_SUPPORTED - Function no longer supported.              */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetOriginSystemID(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             char                   *originSystemID,
                             unsigned long           originSystemIDLength,
                             unsigned long          *returnLength);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetOriginSystemIPAddr                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   This is an obsolete API, there is no replacement API.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   CWB_NOT_SUPPORTED - Function no longer supported.              */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetOriginSystemIPAddr(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             char                   *originIPAddr,
                             unsigned long           originIPAddrLength,
                             unsigned long          *returnLength);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetPreviousFix                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   This is an obsolete API, there is no replacement API.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   CWB_NOT_SUPPORTED - Function no longer supported.              */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetPreviousFix(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             char                   *previousFix,
                             unsigned long           previousFixLength,
                             unsigned long          *returnLength);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetProblemID                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   This is an obsolete API, there is no replacement API.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   CWB_NOT_SUPPORTED - Function no longer supported.              */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetProblemID(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             char                   *problemID,
                             unsigned long           problemIDLength,
                             unsigned long          *returnLength);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetProblemStatus                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   This is an obsolete API, there is no replacement API.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   CWB_NOT_SUPPORTED - Function no longer supported.              */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetProblemStatus(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             cwbSV_ProblemStatus    *problemStatus);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetProblemText                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   This is an obsolete API, there is no replacement API.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   CWB_NOT_SUPPORTED - Function no longer supported.              */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetProblemText(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             char                   *problemText,
                             unsigned long           problemTextLength,
                             unsigned long          *returnLength);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetProblemType                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   This is an obsolete API, there is no replacement API.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   CWB_NOT_SUPPORTED - Function no longer supported.              */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetProblemType(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             cwbSV_ProblemType      *problemType);

/********************************************************************/
/* API:                                                             */
/*   cwbSV_GetProduct                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the product ID value for the service record object     */
/*   identified by the handle provided.                             */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ServiceRecHandle serviceRecHandle - input                */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateServiceRecHandle() API.                        */
/*                                                                  */
/*   char * productID - output                                      */
/*       Pointer to a buffer that will receive the product ID       */
/*       stored in the record identified by the handle.             */
/*                                                                  */
/*   unsigned long productIDLength - input                          */
/*       Length, in bytes, of the productID buffer. It should       */
/*       include space for the terminating null character. If the   */
/*       buffer is too small, the value will be truncated and       */
/*       CWB_BUFFER_OVERFLOW will be returned.                      */
/*       NOTE: The recommended size is CWBSV_MAX_PRODUCT_ID bytes.  */
/*                                                                  */
/*   unsigned long * returnLength - output                          */
/*       Optional, may be NULL. A return address to store the       */
/*       number of bytes needed to hold the output string.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_BUFFER_OVERFLOW - Output buffer too small, data truncated. */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_INVALID_HANDLE  - Invalid handle.                          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The service record handle needs to be filled in by a call to   */
/*   a "read" function before calling this routine, otherwise a     */
/*   NULL string will be returned.                                  */
/*                                                                  */
/*   This function is valid for all service record types.           */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetProduct(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             char                   *productID,
                             unsigned long           productIDLength,
                             unsigned long          *returnLength);

unsigned int CWB_ENTRY cwbSV_GetProductW(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             wchar_t                *productID,
                             unsigned long           productIDLength,
                             unsigned long          *returnLength);

#if ( defined(CWB_UNICODE) )
   #define  cwbSV_GetProduct cwbSV_GetProductW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetRecordCount                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the total numbers of records in the service file       */
/*   identified by the file handle provided.                        */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ServiceFileHandle serviceFileHandle - input              */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_OpenServiceFile() API.                               */
/*                                                                  */
/*   unsigned long * recordCount - output                           */
/*       Pointer to variable that receives the total number of      */
/*       records in the file.                                       */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetRecordCount(
                             cwbSV_ServiceFileHandle  serviceFile,
                             unsigned long           *recordCount);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetServiceFileName                                       */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the fully-qualified path and file name of where        */
/*   the service records are being logged to for a particular       */
/*   file type.                                                     */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ServiceFileType serviceFileType - input                  */
/*      Value indicating which service file name you want returned. */
/*        - CWBSV_HISTORY_LOG                                       */
/*        - CWBSV_DETAIL_TRACE_FILE                                 */
/*        - CWBSV_ENTRY_EXIT_TRACE_FILE                             */
/*                                                                  */
/*   char * fileName - output                                       */
/*       Pointer to a buffer that will receive the service file     */
/*       name associated with the one requested.                    */
/*                                                                  */
/*   unsigned long fileNameLength - input                           */
/*       Length, in bytes, of the fileName buffer. It should        */
/*       include space for the terminating null character. If the   */
/*       buffer is too small, the value will be truncated and       */
/*       CWB_BUFFER_OVERFLOW will be returned.                      */
/*       NOTE: The recommended size is CWBSV_MAX_FILE_PATH bytes.   */
/*                                                                  */
/*   unsigned long * returnLength - output                          */
/*       Optional, may be NULL. A return address to store the       */
/*       number of bytes needed to hold the output string.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_BUFFER_OVERFLOW - Output buffer too small, data truncated. */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWBSV_INVALID_FILE_TYPE - Invalid file type passed-in.         */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The filename string returned could be used as input to the     */
/*   cwbSV_OpenServiceFile() routine.                               */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetServiceFileName(
                             cwbSV_ServiceFileType  serviceFileType,
                             char                  *fileName,
                             unsigned long          fileNameLength,
                             unsigned long         *returnLength);

unsigned int CWB_ENTRY cwbSV_GetServiceFileNameW(
                             cwbSV_ServiceFileType  serviceFileType,
                             wchar_t               *fileName,
                             unsigned long          fileNameLength,
                             unsigned long         *returnLength);

#if ( defined(CWB_UNICODE) )
   #define  cwbSV_GetServiceFileName cwbSV_GetServiceFileNameW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetServiceType                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the type of record (trace, message, entry/exit, etc..) */
/*   for the service record identified by the handle provided.      */
/*                                                                  */
/*   Note: The service record needs to be filled in by a call to    */
/*         a "read" function before calling this function.          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ServiceRecHandle serviceRecHandle - input                */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateServiceRecHandle() API.                        */
/*                                                                  */
/*   cwbSV_ServiceRecType * serviceType - output                    */
/*       Pointer to a cwbSV_ServiceRecType where the serviceType    */
/*       will be returned.                                          */
/*           - CWBSV_MESSAGE_REC                                    */
/*           - CWBSV_DATA_TRACE_REC                                 */
/*           - CWBSV_API_TRACE_REC                                  */
/*           - CWBSV_SPI_TRACE_REC                                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*     Any returned messages will be written to this object.  It    */
/*     is created with the cwbSV_CreateErrHandle API.  The          */
/*     messages may be retrieved through the cwbSV_GetErrText API.  */
/*     If the parameter is set to zero, no messages will be         */
/*     retrieved.                                                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWBSV_INVALID_RECORD_TYPE - Invalid record type detected.      */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The service record handle needs to be filled in by a call to   */
/*   a "read" function before calling this routine, otherwise       */
/*   CWBSV_INVALID_RECORD_TYPE will be returned.                    */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetServiceType(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             cwbSV_ServiceRecType   *serviceType,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetSeverity                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   This is an obsolete API, there is no replacement API.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   CWB_NOT_SUPPORTED - Function no longer supported.              */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetSeverity(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             cwbSV_ProblemSeverity  *severity);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetSymptomString                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   This is an obsolete API, there is no replacement API.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   CWB_NOT_SUPPORTED - Function no longer supported.              */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetSymptomString(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             char                   *symptomString,
                             unsigned long           symptomStringLength,
                             unsigned long          *returnLength);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetTimeStamp                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the timestamp (in localized format) for the service    */
/*   record identified by the handle provided.                      */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ServiceRecHandle serviceRecHandle - input                */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateServiceRecHandle() API.                        */
/*                                                                  */
/*   char * timeStamp - output                                      */
/*       Pointer to a buffer that will receive the timestamp        */
/*       stored in the record identified by the handle.             */
/*                                                                  */
/*   unsigned long timeStampLength - input                          */
/*       Length, in bytes, of the timeStamp buffer. It should       */
/*       include space for the terminating null character. If the   */
/*       buffer is too small, the value will be truncated and       */
/*       CWB_BUFFER_OVERFLOW will be returned.                      */
/*       NOTE: The recommended size is CWBSV_MAX_TIME_VALUE bytes.  */
/*                                                                  */
/*   unsigned long * returnLength - output                          */
/*       Optional, may be NULL. A return address to store the       */
/*       number of bytes needed to hold the output string.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_BUFFER_OVERFLOW - Output buffer too small, data truncated. */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The service record handle needs to be filled in by a call to   */
/*   a "read" function before calling this routine, otherwise a     */
/*   NULL string will be returned.                                  */
/*                                                                  */
/*   This function is valid for all service record types.           */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetTimeStamp(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             char                   *timeStamp,
                             unsigned long           timeStampLength,
                             unsigned long          *returnLength);

unsigned int CWB_ENTRY cwbSV_GetTimeStampW(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             wchar_t                *timeStamp,
                             unsigned long           timeStampLength,
                             unsigned long          *returnLength);

#if ( defined(CWB_UNICODE) )
   #define  cwbSV_GetTimeStamp cwbSV_GetTimeStampW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetTraceAPIData                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the API trace data portion of the service record       */
/*   identified by the handle provided.                             */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ServiceRecHandle serviceRecHandle - input                */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateServiceRecHandle() API.                        */
/*                                                                  */
/*   char * apiData - output                                        */
/*       Pointer to a buffer that will receive the API trace data   */
/*       stored in the record identified by the handle.             */
/*                                                                  */
/*       Note: The data returned is binary, hence it is NOT         */
/*             returned as an ASCIIZ string.                        */
/*                                                                  */
/*   unsigned long apiDataLength - input                            */
/*       Length of the receive buffer passed in. If the buffer      */
/*       is too small, the value will be truncated and              */
/*       CWB_BUFFER_OVERFLOW will be returned.                      */
/*                                                                  */
/*   unsigned long * returnLength - output                          */
/*       Optional, may be NULL. A return address to store the       */
/*       number of bytes needed to hold the output data if the      */
/*       receive buffer is too small. It will also be set to the    */
/*       actual number of bytes of output data returned upon        */
/*       successful completion.                                     */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_BUFFER_OVERFLOW - Output buffer too small, data truncated. */
/*   CWB_INVALID_POINTER - NULL passed on output paraemter.         */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWBSV_INVALID_RECORD_TYPE - Type is not CWBSV_API_TRACE_REC.   */
/*                                                                  */
/* Usage Notes:                                                     */
/*   If the record type is not CWBSV_API_TRACE_REC, a return code   */
/*   of CWBSV_INVALID_RECORD_TYPE will be returned.                 */
/*   (note: cwbSV_GetServiceType() returns the current record type) */
/*                                                                  */
/*   Use the returnLength parameter to determine the actual number  */
/*   of bytes returned in apiData when the return code is CWB_OK.   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetTraceAPIData(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             char                   *apiData,
                             unsigned long           apiDataLength,
                             unsigned long          *returnLength);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetTraceAPIID                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the API event ID of the service record object          */
/*   identified by the handle provided.                             */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ServiceRecHandle serviceRecHandle - input                */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateServiceRecHandle() API.                        */
/*                                                                  */
/*   char * apiID - output                                          */
/*       Pointer to one-byte field that receives the API event ID.  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWBSV_INVALID_RECORD_TYPE - Type is not CWBSV_API_TRACE_REC.   */
/*                                                                  */
/* Usage Notes:                                                     */
/*   If the record type is not CWBSV_API_TRACE_REC, a return code   */
/*   of CWBSV_INVALID_RECORD_TYPE will be returned.                 */
/*   (note: cwbSV_GetServiceType() returns the current record type) */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetTraceAPIID(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             char                   *apiID);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetTraceAPIType                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the API event type of the service record object        */
/*   identified by the handle provided.                             */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ServiceRecHandle serviceRecHandle - input                */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateServiceRecHandle() API.                        */
/*                                                                  */
/*   cwbSV_EventType * eventType - output                           */
/*       Pointer to a cwbSV_EventType where the eventType           */
/*       will be returned.                                          */
/*           - CWBSV_ENTRY_POINT                                    */
/*           - CWBSV_EXIT_POINT                                     */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*     Any returned messages will be written to this object.  It    */
/*     is created with the cwbSV_CreateErrHandle API.  The          */
/*     messages may be retrieved through the cwbSV_GetErrText API.  */
/*     If the parameter is set to zero, no messages will be         */
/*     retrieved.                                                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWBSV_INVALID_RECORD_TYPE - Type is not CWBSV_API_TRACE_REC.   */
/*   CWBSV_INVALID_EVENT_TYPE - Invalid event type detected.        */
/*                                                                  */
/* Usage Notes:                                                     */
/*   If the record type is not CWBSV_API_TRACE_REC, a return code   */
/*   of CWBSV_INVALID_RECORD_TYPE will be returned.                 */
/*   (note: cwbSV_GetServiceType() returns the current record type) */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetTraceAPIType(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             cwbSV_EventType        *eventType,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetTraceData                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the trace data portion of the service record object    */
/*   identified by the handle provided.                             */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ServiceRecHandle serviceRecHandle - input                */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateServiceRecHandle() API.                        */
/*                                                                  */
/*   char * traceData - output                                      */
/*       Pointer to a buffer that will receive the trace data       */
/*       stored in the record identified by the handle.             */
/*                                                                  */
/*       Note: The data returned is binary, hence it is NOT         */
/*             returned as an ASCIIZ string.                        */
/*                                                                  */
/*   unsigned long traceDataLength - input                          */
/*       Length of the receive buffer passed in. If the buffer      */
/*       is too small, the value will be truncated and              */
/*       CWB_BUFFER_OVERFLOW will be returned.                      */
/*                                                                  */
/*   unsigned long * returnLength - output                          */
/*       Optional, may be NULL. A return address to store the       */
/*       number of bytes needed to hold the output data if the      */
/*       receive buffer is too small. It will also be set to the    */
/*       actual number of bytes of output data returned upon        */
/*       successful completion.                                     */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_BUFFER_OVERFLOW - Output buffer too small, data truncated. */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWBSV_INVALID_RECORD_TYPE - Type is not CWBSV_DATA_TRACE_REC.  */
/*                                                                  */
/* Usage Notes:                                                     */
/*   If the record type is not CWBSV_TRACE_DATA_REC, a return code  */
/*   of CWBSV_INVALID_RECORD_TYPE will be returned.                 */
/*   (note: cwbSV_GetServiceType() returns the current record type) */
/*                                                                  */
/*   Use the returnLength parameter to determine the actual number  */
/*   of bytes returned in traceData when the return code is CWB_OK. */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetTraceData(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             char                   *traceData,
                             unsigned long           traceDataLength,
                             unsigned long          *returnLength);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetTraceSPIData                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the SPI trace data portion of the service record       */
/*   identified by the handle provided.                             */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ServiceRecHandle serviceRecHandle - input                */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateServiceRecHandle() API.                        */
/*                                                                  */
/*   char * spiData - output                                        */
/*       Pointer to a buffer that will receive the SPI trace data   */
/*       stored in the record identified by the handle.             */
/*                                                                  */
/*       Note: The data returned is binary, hence it is NOT         */
/*             returned as an ASCIIZ string.                        */
/*                                                                  */
/*   unsigned long spiDataLength - input                            */
/*       Length of the receive buffer passed in. If the buffer      */
/*       is too small, the value will be truncated and              */
/*       CWB_BUFFER_OVERFLOW will be returned.                      */
/*                                                                  */
/*   unsigned long * returnLength - output                          */
/*       Optional, may be NULL. A return address to store the       */
/*       number of bytes needed to hold the output data if the      */
/*       receive buffer is too small. It will also be set to the    */
/*       actual number of bytes of output data returned upon        */
/*       successful completion.                                     */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_BUFFER_OVERFLOW - Output buffer too small, data truncated. */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWBSV_INVALID_RECORD_TYPE - Type is not CWBSV_SPI_TRACE_REC.   */
/*                                                                  */
/* Usage Notes:                                                     */
/*   If the record type is not CWBSV_SPI_TRACE_REC, a return code   */
/*   of CWBSV_INVALID_RECORD_TYPE will be returned.                 */
/*   (note: cwbSV_GetServiceType() returns the current record type) */
/*                                                                  */
/*   Use the returnLength parameter to determine the actual number  */
/*   of bytes returned in spidata when the return code is CWB_OK.   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetTraceSPIData(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             char                   *spiData,
                             unsigned long           spiDataLength,
                             unsigned long          *returnLength);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetTraceSPIID                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the SPI event ID of the service record object          */
/*   identified by the handle provided.                             */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ServiceRecHandle serviceRecHandle - input                */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateServiceRecHandle() API.                        */
/*                                                                  */
/*   char * spiID - output                                          */
/*       Pointer to one-byte field that receives the SPI event ID.  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_INVALID_HANDLE  - Invalid handle.                          */
/*   CWBSV_INVALID_RECORD_TYPE - Type is not CWBSV_SPI_TRACE_REC.   */
/*                                                                  */
/* Usage Notes:                                                     */
/*   If the record type is not CWBSV_SPI_TRACE_REC, a return code   */
/*   of CWBSV_INVALID_RECORD_TYPE will be returned.                 */
/*   (note: cwbSV_GetServiceType() returns the current record type) */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetTraceSPIID(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             char                   *spiID);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_GetTraceSPIType                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the SPI event type of the service record object        */
/*   identified by the handle provided.                             */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ServiceRecHandle serviceRecHandle - input                */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateServiceRecHandle() API.                        */
/*                                                                  */
/*   cwbSV_EventType * eventType - output                           */
/*       Pointer to a cwbSV_EventType where the eventType           */
/*       will be returned.                                          */
/*           - CWBSV_ENTRY_POINT                                    */
/*           - CWBSV_EXIT_POINT                                     */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*     Any returned messages will be written to this object.  It    */
/*     is created with the cwbSV_CreateErrHandle API.  The          */
/*     messages may be retrieved through the cwbSV_GetErrText API.  */
/*     If the parameter is set to zero, no messages will be         */
/*     retrieved.                                                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - NULL passed on output parameter.         */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*   CWBSV_INVALID_RECORD_TYPE - Type is not CWBSV_SPI_TRACE_REC.   */
/*   CWBSV_INVALID_EVENT_TYPE - Invalid event type detected.        */
/*                                                                  */
/* Usage Notes:                                                     */
/*   If the record type is not CWBSV_SPI_TRACE_REC, a return code   */
/*   of CWBSV_INVALID_RECORD_TYPE will be returned.                 */
/*   (note: cwbSV_GetServiceType() returns the current record type) */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_GetTraceSPIType(
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             cwbSV_EventType        *eventType,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_IsLogActive                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Indicates whether the requested log or trace function type is  */
/*   currently active.                                              */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ServiceFileType serviceFileType - input                  */
/*      Value indicating which service file you want checked        */
/*        - CWBSV_HISTORY_LOG                                       */
/*        - CWBSV_DETAIL_TRACE_FILE                                 */
/*        - CWBSV_ENTRY_EXIT_TRACE_FILE                             */
/*                                                                  */
/*   cwb_Boolean *logActive - output                                */
/*      Value indicating if the log is active or not                */
/*        CWB_TRUE  - log or trace function is currently active     */
/*        CWB_FALSE - log or trace function is not active           */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Invalid pointer sent to the function     */
/*   CWBSV_INVALID_FILE_TYPE - Invalid file type passed-in.         */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_IsLogActive(
                             cwbSV_ServiceFileType  serviceFileType,
                             cwb_Boolean           *logActive);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_LogAPIEntry                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   This function will log an API entry point to the currently     */
/*   active entry/exit trace file. The product and component ID's   */
/*   set in the entry will be written along with the date and time  */
/*   of the when the data was logged. The apiID along with any      */
/*   optional data passed on the request will also be logged.       */
/*                                                                  */
/* Parameters:                                                      */
/*                                                                  */
/*   cwbSV_TraceAPIHandle traceAPIHandle - input                    */
/*       Handle that was returned by a previous call to             */
/*       cwbSV_CreateTraceAPIHandle() API.                          */
/*                                                                  */
/*   unsigned char apiID - input                                    */
/*       A unique one-character code that will distinguish this     */
/*       API trace point from others logged by your program.        */
/*       Definition of these codes are left up to the caller of     */
/*       this API. The recommended approach is to use the defined   */
/*       range (0x00 - 0xFF) for each unique component in your      */
/*       product (i.e. start at 0x00 for each component)            */
/*                                                                  */
/*   char * apiData - input                                         */
/*       Points to a buffer that contains additional data           */
/*       (e.g. input parameter values from your caller) that        */
/*       you want to log along with this entry point.               */
/*       Parameter is optional, it is ignored if the address is     */
/*       NULL or the data length is zero. This buffer can           */
/*       contain binary data because the length parameter is        */
/*       used in determining the amount to trace.                   */
/*                                                                  */
/*   unsigned long apiDataLength - input                            */
/*       Specifies the number of bytes in the API data buffer       */
/*       to log for this trace entry.                               */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This call should allows be used in conjunction with a          */
/*   corresponding "cwbSV_LogAPIExit()". It is recommended that     */
/*   these calls would be put at the beginning and end of an API    */
/*   routine that you write. The other method would be to use these */
/*   log functions around calls to external routines not written    */
/*   by you.                                                        */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_LogAPIEntry(
                             cwbSV_TraceAPIHandle  traceAPIHandle,
                             unsigned char         apiID,
                             char                 *apiData,
                             unsigned long         apiDataLength);

unsigned int CWB_ENTRY cwbSV_LogAPIEntryW(
                             cwbSV_TraceAPIHandle  traceAPIHandle,
                             unsigned char         apiID,
                             const wchar_t        *apiData,
                             unsigned long         apiDataLength);

#if ( defined(CWB_UNICODE) )
   #define  cwbSV_LogAPIEntry cwbSV_LogAPIEntryW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_LogAPIExit                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   This function will log an API exit point to the currently      */
/*   active entry/exit trace file. The product and component ID's   */
/*   set in the entry will be written along with the date and time  */
/*   of the when the data was logged. The API ID along with any     */
/*   optional data passed on the request will also be logged.       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_TraceAPIHandle traceAPIHandle - input                    */
/*       Handle that was returned by a previous call to             */
/*       cwbSV_CreateTraceAPIHandle() API.                          */
/*                                                                  */
/*   unsigned char apiID - input                                    */
/*       A unique one-byte code that will distinguish this          */
/*       API trace point from others logged by your program.        */
/*       Definition of these codes are left up to the caller of     */
/*       this API. The recommended approach is to use the defined   */
/*       range (0x00 - 0xFF) for each unique component in your      */
/*       product (i.e. start at 0x00 for each component)            */
/*                                                                  */
/*   char * apiData - input                                         */
/*       Points to a buffer that contains additional data           */
/*       (e.g. output parameter values passed back to your caller)  */
/*       that you want to log along with this exit point.           */
/*       Parameter is optional, it is ignored if the address is     */
/*       NULL or the data length is zero. This buffer can           */
/*       contain binary data because the length parameter is        */
/*       used in determining the amount to trace.                   */
/*                                                                  */
/*   unsigned long apiDataLength - input                            */
/*       Specifies the number of bytes in the API data buffer       */
/*       to log for this trace entry.                               */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This call should allows be used in conjunction with a          */
/*   corresponding "cwbSV_LogAPIEntry()". It is recommended that    */
/*   these calls would be put at the beginning and end of an API    */
/*   routine that you write. The other method would be to use these */
/*   log functions around calls to external routines not written    */
/*   by you.                                                        */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_LogAPIExit(
                             cwbSV_TraceAPIHandle  traceAPIHandle,
                             unsigned char         apiID,
                             char                 *apiData,
                             unsigned long         apiDataLength);

unsigned int CWB_ENTRY cwbSV_LogAPIExitW(
                             cwbSV_TraceAPIHandle  traceAPIHandle,
                             unsigned char         apiID,
                             const wchar_t        *apiData,
                             unsigned long         apiDataLength);

#if ( defined(CWB_UNICODE) )
   #define  cwbSV_LogAPIExit cwbSV_LogAPIExitW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_LogMessageText                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   This function will log the supplied message text to the        */
/*   currently active history log. The product and component ID's   */
/*   set in the entry will be written along with the date and time  */
/*   of the when the text was logged.                               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_MessageTextHandle messageTextHandle - input              */
/*       Handle that was returned by a previous call to             */
/*       cwbSV_CreateMessageTextHandle() API.                       */
/*                                                                  */
/*   char *  messageText - input                                    */
/*       Points to a buffer that contains the message text you      */
/*       want to log.                                               */
/*                                                                  */
/*   unsigned long messageTextLength - input                        */
/*       Specifies the number of bytes in the message text buffer   */
/*       to log for this message entry.                             */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle passed in on request.      */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_LogMessageText(
                             cwbSV_MessageTextHandle  messageTextHandle,
                             char                    *messageText,
                             unsigned long            messageTextLength);

unsigned int CWB_ENTRY cwbSV_LogMessageTextW(
                             cwbSV_MessageTextHandle  messageTextHandle,
                             const wchar_t           *messageText,
                             unsigned long            messageTextLength);

#if ( defined(CWB_UNICODE) )
   #define  cwbSV_LogMessageText cwbSV_LogMessageTextW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_LogSPIEntry                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   This function will log an SPI entry point to the currently     */
/*   active entry/exit trace file. The product and component ID's   */
/*   set in the entry will be written along with the date and time  */
/*   of the when the data was logged. The spiID along with any      */
/*   optional data passed on the request will also be logged.       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_TraceSPIHandle traceSPIHandle - input                    */
/*       Handle that was returned by a previous call to             */
/*       cwbSV_CreateTraceSPIHandle() API.                          */
/*                                                                  */
/*   unsigned char spiID - input                                    */
/*       A unique one-byte code that will distinguish this          */
/*       SPI trace point from others logged by your program.        */
/*       Definition of these codes are left up to the caller of     */
/*       this API. The recommended approach is to use the defined   */
/*       range (0x00 - 0xFF) for each unique component in your      */
/*       product (i.e. start at 0x00 for each component)            */
/*                                                                  */
/*   char * spiData - input                                         */
/*       Points to a buffer that contains additional data           */
/*       (e.g. input parameter values from your caller) that        */
/*       you want to log along with this entry point.               */
/*       Parameter is optional, it is ignored if the address is     */
/*       NULL or the data length is zero. This buffer can           */
/*       contain binary data because the length parameter is        */
/*       used in determining the amount to trace.                   */
/*                                                                  */
/*   unsigned long  spiDataLength - input                           */
/*       Specifies the number of bytes in the SPI data buffer       */
/*       to log for this trace entry.                               */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This call should allows be used in conjunction with a          */
/*   corresponding "cwbSV_LogSPIExit()". It is recommended that     */
/*   these calls would be put at the beginning and end of an API    */
/*   routine that you write. The other method would be to use these */
/*   log functions around calls to external routines not written    */
/*   by you.                                                        */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_LogSPIEntry(
                             cwbSV_TraceSPIHandle  traceSPIHandle,
                             unsigned char         spiID,
                             char                 *spiData,
                             unsigned long         spiDataLength);

unsigned int CWB_ENTRY cwbSV_LogSPIEntryW(
                             cwbSV_TraceSPIHandle  traceSPIHandle,
                             unsigned char         spiID,
                             const wchar_t        *spiData,
                             unsigned long         spiDataLength);

#if ( defined(CWB_UNICODE) )
   #define  cwbSV_LogSPIEntry cwbSV_LogSPIEntryW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_LogSPIExit                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   This function will log an SPI exit point to the currently      */
/*   active entry/exit trace file. The product and component ID's   */
/*   set in the entry will be written along with the date and time  */
/*   of the when the data was logged. The spiID along with any      */
/*   optional data passed on the request will also be logged.       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_TraceSPIHandle traceSPIHandle - input                    */
/*       Handle that was returned by a previous call to             */
/*       cwbSV_CreateTraceSPIHandle() API.                          */
/*                                                                  */
/*   unsigned char spiID - input                                    */
/*       A unique one-byte code that will distinguish this          */
/*       SPI trace point from others logged by your program.        */
/*       Definition of these codes are left up to the caller of     */
/*       this API. The recommended approach is to use the defined   */
/*       range (0x00 - 0xFF) for each unique component in your      */
/*       product (i.e. start at 0x00 for each component)            */
/*                                                                  */
/*   char * spiData - input                                         */
/*       Points to a buffer that contains additional data           */
/*       (e.g. output parameter values passed back to your caller)  */
/*       that you want to log along with this exit point.           */
/*       Parameter is optional, it is ignored if the address is     */
/*       NULL or the data length is zero. This buffer can           */
/*       contain binary data because the length parameter is        */
/*       used in determining the amount to trace.                   */
/*                                                                  */
/*   unsigned long spiDataLength - input                            */
/*       Specifies the number of bytes in the SPI data buffer       */
/*       to log for this trace entry.                               */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This call should allows be used in conjunction with a          */
/*   corresponding "cwbSV_LogSPIEntry()". It is recommended that    */
/*   these calls would be put at the beginning and end of an API    */
/*   routine that you write. The other method would be to use these */
/*   log functions around calls to external routines not written    */
/*   by you.                                                        */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_LogSPIExit(
                             cwbSV_TraceSPIHandle  traceSPIHandle,
                             unsigned char         spiID,
                             char                 *spiData,
                             unsigned long         spiDataLength);

unsigned int CWB_ENTRY cwbSV_LogSPIExitW(
                             cwbSV_TraceSPIHandle  traceSPIHandle,
                             unsigned char         spiID,
                             const wchar_t        *spiData,
                             unsigned long         spiDataLength);

#if ( defined(CWB_UNICODE) )
   #define  cwbSV_LogSPIExit cwbSV_LogSPIExitW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_LogTraceData                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   This function will log the supplied trace data to the          */
/*   currently active trace file. The product and component ID's    */
/*   set in the entry will be written along with the date and time  */
/*   of the when the data was logged.                               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_TraceDataHandle traceDataHandle - input                  */
/*       Handle that was returned by a previous call to             */
/*       cwbSV_CreateTraceDataHandle() API.                         */
/*                                                                  */
/*   char * traceData - input                                       */
/*       Points to a buffer that contains the trace data you want   */
/*       to log. The buffer can contain binary data because the     */
/*       length parameter is used in determining the amount to      */
/*       trace.                                                     */
/*                                                                  */
/*   unsigned long traceDataLength - input                          */
/*       Specifies the number of bytes in the trace data buffer     */
/*       to log for this trace entry.                               */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_LogTraceData(
                             cwbSV_TraceDataHandle  traceDataHandle,
                             char                  *traceData,
                             unsigned long          traceDataLength);

unsigned int CWB_ENTRY cwbSV_LogTraceDataW(
                             cwbSV_TraceDataHandle  traceDataHandle,
                             const wchar_t         *traceData,
                             unsigned long          traceDataLength);

#if ( defined(CWB_UNICODE) )
   #define  cwbSV_LogTraceData cwbSV_LogTraceDataW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_OpenServiceFile                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   Opens the specified service file for READ access (history log, */
/*   trace file, etc..) and returns a handle to it.                 */
/*                                                                  */
/* Parameters:                                                      */
/*   char * serviceFileName - input                                 */
/*       Points to a buffer that contains the fully-qualified       */
/*       name (e.g. c:\path\filename.ext) of the service file       */
/*       to open.                                                   */
/*                                                                  */
/*   cwbSV_ServiceFileHandle * serviceFileHandle - output           */
/*       Pointer to a cwbSV_ServiceFileHandle where the handle      */
/*       will be returned. This handle should be used in            */
/*       subsequent calls to the service file functions.            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*     Any returned messages will be written to this object.  It    */
/*     is created with the cwbSV_CreateErrHandle API.  The          */
/*     messages may be retrieved through the cwbSV_GetErrText API.  */
/*     If the parameter is set to zero, no messages will be         */
/*     retrieved.                                                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - NULL passed as handle address.           */
/*   CWB_FILE_IO_ERROR - File could not be opened.                  */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory to create handle.  */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_OpenServiceFile(
                             char                    *serviceFileName,
                             cwbSV_ServiceFileHandle *serviceFileHandle,
                             cwbSV_ErrHandle          errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_ReadNewestRecord                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Reads the newest record in the service file into the record    */
/*   handle provided. Subsequent calls can be made to retrieve      */
/*   the information stored in this record (e.g. cwbSV_GetProduct(),*/
/*   cwbSV_GetDateStamp(), etc...).                                 */
/*                                                                  */
/*   Note: This record is the one with the newest time and          */
/*         date stamp in the file.                                  */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ServiceFileHandle serviceFileHandle - input              */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_OpenServiceFile() API.                               */
/*                                                                  */
/*   cwbSV_ServiceRecHandle serviceRecHandle - input                */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateServiceRecHandle function.                     */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*     Any returned messages will be written to this object.  It    */
/*     is created with the cwbSV_CreateErrHandle API.  The          */
/*     messages may be retrieved through the cwbSV_GetErrText API.  */
/*     If the parameter is set to zero, no messages will be         */
/*     retrieved.                                                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_END_OF_FILE - End of file has been reached.                */
/*   CWB_FILE_IO_ERROR - Record could not be read.                  */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This read would be used as a "priming-type" read before        */
/*   issuing a series of cwbsv_ReadPrevRecord() calls until the     */
/*   the end-of-file indicator is returned.                         */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_ReadNewestRecord(
                             cwbSV_ServiceFileHandle serviceFileHandle,
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_ReadNextRecord                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Reads the next record in the service file into the record      */
/*   handle provided. Subsequent calls can be made to retrieve      */
/*   the information stored in this record (e.g. cwbSV_GetProduct(),*/
/*   cwbSV_GetDateStamp(), etc...).                                 */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ServiceFileHandle serviceFileHandle - input              */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_OpenServiceFile() API.                               */
/*                                                                  */
/*   cwbSV_ServiceRecHandle serviceRecHandle - input                */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateServiceRecHandle function.                     */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*     Any returned messages will be written to this object.  It    */
/*     is created with the cwbSV_CreateErrHandle API.  The          */
/*     messages may be retrieved through the cwbSV_GetErrText API.  */
/*     If the parameter is set to zero, no messages will be         */
/*     retrieved.                                                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_END_OF_FILE - End of file has been reached.                */
/*   CWB_FILE_IO_ERROR - Record could not be read.                  */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This read would normally be used once the priming read,        */
/*   "ReadOldestRecord()" is performed.                             */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_ReadNextRecord(
                             cwbSV_ServiceFileHandle serviceFileHandle,
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_ReadOldestRecord                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Reads the oldest record in the service file into the record    */
/*   handle provided. Subsequent calls can be made to retrieve      */
/*   the information stored in this record (e.g. cwbSV_GetProduct(),*/
/*   cwbSV_GetDateStamp(), etc...).                                 */
/*                                                                  */
/*   Note: This record is the one with the oldest time and          */
/*         date stamp in the file.                                  */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ServiceFileHandle serviceFileHandle - input              */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_OpenServiceFile() API.                               */
/*                                                                  */
/*   cwbSV_ServiceRecHandle serviceRecHandle - input                */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateServiceRecHandle function.                     */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*     Any returned messages will be written to this object.  It    */
/*     is created with the cwbSV_CreateErrHandle API.  The          */
/*     messages may be retrieved through the cwbSV_GetErrText API.  */
/*     If the parameter is set to zero, no messages will be         */
/*     retrieved.                                                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_END_OF_FILE - End of file has been reached.                */
/*   CWB_FILE_IO_ERROR - Record could not be read.                  */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This read would be used as a "priming-type" read before        */
/*   issuing a series of cwbsv_ReadNextRecord() calls until the     */
/*   the end-of-file indicator is returned.                         */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_ReadOldestRecord(
                             cwbSV_ServiceFileHandle serviceFileHandle,
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_ReadPrevRecord                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Reads the previous record in the service file into the record  */
/*   handle provided. Subsequent calls can be made to retrieve      */
/*   the information stored in this record (e.g. cwbSV_GetProduct(),*/
/*   cwbSV_GetDateStamp(), etc...).                                 */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ServiceFileHandle serviceFileHandle - input              */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_OpenServiceFile() API.                               */
/*                                                                  */
/*   cwbSV_ServiceRecHandle serviceRecHandle - input                */
/*       Handle that was returned by a previous call to the         */
/*       cwbSV_CreateServiceRecHandle function.                     */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*     Any returned messages will be written to this object.  It    */
/*     is created with the cwbSV_CreateErrHandle API.  The          */
/*     messages may be retrieved through the cwbSV_GetErrText API.  */
/*     If the parameter is set to zero, no messages will be         */
/*     retrieved.                                                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_END_OF_FILE - End of file has been reached.                */
/*   CWB_FILE_IO_ERROR - Record could not be read.                  */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This read would normally be used once the priming read,        */
/*   "ReadNewestRecord()" is performed.                             */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_ReadPrevRecord(
                             cwbSV_ServiceFileHandle serviceFileHandle,
                             cwbSV_ServiceRecHandle  serviceRecHandle,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_SetMessageClass                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   This function allows setting of the message class (severity)   */
/*   to associate with the message being written to the history     */
/*   log.                                                           */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_MessageTextHandle messageTextHandle - input              */
/*       Handle that was returned by a previous call to             */
/*       cwbSV_CreateMessageTextHandle() API.                       */
/*                                                                  */
/*   cwbSV_MessageClass messageClass - input                        */
/*       One of the following:                                      */
/*         - CWBSV_CLASS_INFORMATIONAL                              */
/*         - CWBSV_CLASS_WARNING                                    */
/*         - CWBSV_CLASS_ERROR                                      */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle passed in on request.      */
/*   CWBSV_INVALID_MSG_CLASS - Invalid message class passed in.     */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This value should be set before calling the corresponding      */
/*   log function, "cwbSV_LogMessageText()".                        */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_SetMessageClass(
                             cwbSV_MessageTextHandle  messageTextHandle,
                             cwbSV_MessageClass       messageClass);


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_SetMessageComponent                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   This function allows setting of a unique component identifier  */
/*   in the message handle provided. Along with setting the         */
/*   product ID (see cwbSV_SetMessageProduct), this call should     */
/*   be used to distinguish your message entries from other         */
/*   product's entries in the history log.                          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_MessageTextHandle messageTextHandle - input              */
/*       Handle that was returned by a previous call to             */
/*       cwbSV_CreateMessageTextHandle() API.                       */
/*                                                                  */
/*   char * componentID - input                                     */
/*       Points to a null-terminated string that contains a         */
/*       component identifier to be used on this message entry.     */
/*       NOTE: A maximum of CWBSV_MAX_COMP_ID_CHARS characters will */
/*             be logged for the component ID. Larger strings       */
/*             will be truncated.                                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle passed in on request.      */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This value should be set before calling the corresponding      */
/*   log function, "cwbSV_LogMessageText()".                        */
/*   The suggested hierarchy is that you would define a product ID  */
/*   with one or many components defined under it.                  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_SetMessageComponent(
                             cwbSV_MessageTextHandle  messageTextHandle,
                             char                    *componentID);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_SetMessageProduct                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   This function allows setting of a unique product identifier in */
/*   the message handle provided. Along with setting the component  */
/*   ID (see cwbSV_SetMessageComponent), this call should be used   */
/*   to distinguish your message entries from other product's       */
/*   entries in the history log.                                    */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_MessageTextHandle messageTextHandle - input              */
/*       Handle that was returned by a previous call to             */
/*       cwbSV_CreateMessageTextHandle() API.                       */
/*                                                                  */
/*   char * productID - input                                       */
/*       Points to a null-terminated string that contains a         */
/*       product identifier to be used on this message entry.       */
/*       NOTE: A maximum of CWBSV_MAX_PRODUCT_ID_CHARS characters   */
/*             will be logged for the product ID. Larger strings    */
/*             will be truncated.                                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle passed in on request.      */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This value should be set before calling the corresponding      */
/*   log function, "cwbSV_LogMessageText()".                        */
/*   The suggested hierarchy is that you would define a product ID  */
/*   with one or many components defined under it.                  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_SetMessageProduct(
                             cwbSV_MessageTextHandle  messageTextHandle,
                             char                    *productID);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_SetAPIComponent                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   This function allows setting of a unique component identifier  */
/*   in trace entry provided. Along with setting the product        */
/*   ID (see cwbSV_SetAPIProduct), this call should be used to      */
/*   distinguish your trace entries from other product's entries in */
/*   the trace file.                                                */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_TraceAPIHandle traceAPIHandle - input                    */
/*       Handle that was returned by a previous call to             */
/*       cwbSV_CreateTraceAPIHandle() API.                          */
/*                                                                  */
/*   char * componentID - input                                     */
/*       Points to a null-terminated string that contains a         */
/*       component identifier to be used on this trace entry.       */
/*                                                                  */
/*       NOTE: A maximum of CWBSV_MAX_COMP_ID_CHARS characters will */
/*             be logged for the component ID. Larger strings       */
/*             will be truncated.                                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This value should be set before calling the corresponding      */
/*   log functions, "cwbSV_LogAPIEntry()" or "cwbSV_LogAPIExit().   */
/*   The suggested hierarchy is that you would define a product ID  */
/*   with one or many components defined under it.                  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_SetAPIComponent(
                             cwbSV_TraceAPIHandle  traceAPIHandle,
                             char                 *componentID);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_SetAPIProduct                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   This function allows setting of a unique product identifier in */
/*   the trace handle provided. Along with setting the component    */
/*   ID (see cwbSV_SetAPIComponent), this call should be used to    */
/*   distinguish your trace entries from other product's entries in */
/*   the trace file.                                                */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_TraceAPIHandle traceAPIHandle - input                    */
/*       Handle that was returned by a previous call to             */
/*       cwbSV_CreateTraceAPIHandle() API.                          */
/*                                                                  */
/*   char * productID - input                                       */
/*       Points to a null-terminated string that contains a         */
/*       product identifier to be used on this trace entry.         */
/*                                                                  */
/*       NOTE: A maximum of CWBSV_MAX_PRODUCT_ID_CHARS characters   */
/*             will be logged for the product ID. Larger strings    */
/*             will be truncated.                                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This value should be set before calling the corresponding      */
/*   log functions, "cwbSV_LogAPIEntry()" or "cwbSV_LogAPIExit().   */
/*   The suggested hierarchy is that you would define a product ID  */
/*   with one or many components defined under it.                  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_SetAPIProduct(
                             cwbSV_TraceAPIHandle  traceAPIHandle,
                             char                 *productID);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_SetSPIComponent                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   This function allows setting of a unique component identifier  */
/*   in trace entry provided. Along with setting the product        */
/*   ID (see cwbSV_SetSPIProduct), this call should be used to      */
/*   distinguish your trace entries from other product's entries in */
/*   the trace file.                                                */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_TraceSPIHandle traceSPIHandle - input                    */
/*       Handle that was returned by a previous call to             */
/*       cwbSV_CreateTraceSPIHandle() API.                          */
/*                                                                  */
/*   char * componentID - input                                     */
/*       Points to a null-terminated string that contains a         */
/*       component identifier to be used on this trace entry.       */
/*                                                                  */
/*       NOTE: A maximum of CWBSV_MAX_COMP_ID_CHARS characters will */
/*             be logged for the component ID. Larger strings       */
/*             will be truncated.                                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This value should be set before calling the corresponding      */
/*   log functions, "cwbSV_LogAPIEntry()" or "cwbSV_LogAPIExit().   */
/*   The suggested hierarchy is that you would define a product ID  */
/*   with one or many components defined under it.                  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_SetSPIComponent(
                             cwbSV_TraceSPIHandle  traceSPIHandle,
                             char                 *componentID);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_SetSPIProduct                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   This function allows setting of a unique product identifier in */
/*   the trace handle provided. Along with setting the component    */
/*   ID (see cwbSV_SetSPIComponent), this call should be used to    */
/*   distinguish your trace entries from other product's entries in */
/*   the trace file.                                                */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_TraceSPIHandle traceSPIHandle - input                    */
/*       Handle that was returned by a previous call to             */
/*       cwbSV_CreateTraceSPIHandle() API.                          */
/*                                                                  */
/*   char * productID - input                                       */
/*       Points to a null-terminated string that contains a         */
/*       product identifier to be used on this trace entry.         */
/*                                                                  */
/*       NOTE: A maximum of CWBSV_MAX_PRODUCT_ID_CHARS characters   */
/*             will be logged for the product ID. Larger strings    */
/*             will be truncated.                                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This value should be set before calling the corresponding      */
/*   log functions, "cwbSV_LogAPIEntry()" or "cwbSV_LogAPIExit().   */
/*   The suggested hierarchy is that you would define a product ID  */
/*   with one or many components defined under it.                  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_SetSPIProduct(
                             cwbSV_TraceSPIHandle  traceSPIHandle,
                             char                 *productID);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_SetTraceComponent                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   This function allows setting of a unique component identifier  */
/*   in service entry provided. Along with setting the product      */
/*   ID (see cwbSV_SetTraceProduct), this call should be used to    */
/*   distinguish your trace entries from other product's entries in */
/*   the trace file.                                                */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_TraceDataHandle traceDataHandle - input                  */
/*       Handle that was returned by a previous call to             */
/*       cwbSV_CreateTraceDataHandle() API.                         */
/*                                                                  */
/*   char * componentID - input                                     */
/*       Points to a null-terminated string that contains a         */
/*       component identifier to be used on this trace entry.       */
/*                                                                  */
/*       NOTE: A maximum of CWBSV_MAX_COMP_ID_CHARS characters will */
/*             be logged for the component ID. Larger strings       */
/*             will be truncated.                                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This value should be set before calling the corresponding      */
/*   log function, "cwbSV_LogTraceData()".                          */
/*   The suggested hierarchy is that you would define a product ID  */
/*   with one or many components defined under it.                  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_SetTraceComponent(
                             cwbSV_TraceDataHandle  traceDataHandle,
                             char                  *componentID);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_SetTraceProduct                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   This function allows setting of a unique product identifier in */
/*   the trace handle provided. Along with setting the component    */
/*   ID (see cwbSV_SetTraceComponent), this call should be used to  */
/*   distinguish your trace entries from other product's entries in */
/*   the trace file.                                                */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_TraceDataHandle traceDataHandle - input                  */
/*       Handle that was returned by a previous call to             */
/*       cwbSV_CreateTraceDataHandle() API.                         */
/*                                                                  */
/*   char * productID - input                                       */
/*       Points to a null-terminated string that contains a         */
/*       product identifier to be used on this trace entry.         */
/*                                                                  */
/*       NOTE: A maximum of CWBSV_MAX_PRODUCT_ID_CHARS characters   */
/*             will be logged for the product ID. Larger strings    */
/*             will be truncated.                                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - Invalid handle.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This value should be set before calling the corresponding      */
/*   log function, "cwbSV_LogTraceData()".                          */
/*   The suggested hierarchy is that you would define a product ID  */
/*   with one or many components defined under it.                  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_SetTraceProduct(
                             cwbSV_TraceDataHandle  traceDataHandle,
                             char                  *productID);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_StartLog                                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   This function will start the requested log or trace.           */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ServiceFileType serviceFileType - input                  */
/*      Value indicating which service function you want started    */
/*        - CWBSV_HISTORY_LOG                                       */
/*        - CWBSV_DETAIL_TRACE_FILE                                 */
/*        - CWBSV_ENTRY_EXIT_TRACE_FILE                             */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_FILE_IO_ERROR - Log file could not be opened.              */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory to start log.      */
/*   CWBSV_INVALID_FILE_TYPE - Invalid file type passed-in.         */
/*   CWBSV_LOG_NOT_STARTED - Diagnostic tools could not be started. */
/*                                                                  */
/* Usage Notes:                                                     */
/*  A corresponding cwbSV_StopLog() API call should be made before  */
/*  terminating your program. If not, the log or trace function     */
/*  will remain active after your program terminates.               */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_StartLog(
                             cwbSV_ServiceFileType  serviceFileType);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSV_StopLog                                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   This function will stop the requested log or trace.            */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ServiceFileType serviceFileType - input                  */
/*      Value indicating which service function you want stopped    */
/*        - CWBSV_HISTORY_LOG                                       */
/*        - CWBSV_DETAIL_TRACE_FILE                                 */
/*        - CWBSV_ENTRY_EXIT_TRACE_FILE                             */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBSV_INVALID_FILE_TYPE - Invalid file type passed-in.         */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSV_StopLog(
                             cwbSV_ServiceFileType  serviceFileType);


#if defined( __cplusplus )
}
#endif

#endif /* _CWBSV_H_ */

