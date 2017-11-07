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
/*   CWBRC.h                                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   The functions listed in this file can be used to run commands  */
/*   or call programs on the iSeries system.  They can be used to   */
/*   access any iSeries command or program, including iSeries APIs. */
/*                                                                  */
/*   The APIs can be broken down into three groups:                 */
/*                                                                  */
/*   The following APIs can be used to access the remote command    */
/*   server program on the iSeries system.  The system handle is    */
/*   used to run commands and call programs:                        */
/*     cwbRC_StartSys()                                             */
/*     cwbRC_StartSysA()                                            */
/*     cwbRC_StartSysW()                                            */
/*     cwbRC_StartSysEx()                                           */
/*     cwbRC_StartSysExA()                                          */
/*     cwbRC_StartSysExW()                                          */
/*     cwbRC_GetClientCCSID()                                       */
/*     cwbRC_GetHostCCSID()                                         */
/*     cwbRC_GetSysName()                                           */
/*     cwbRC_GetSysNameA()                                          */
/*     cwbRC_GetSysNameW()                                          */
/*     cwbRC_StopSys()                                              */
/*                                                                  */
/*   The following APIs will run an iSeries command:                */
/*     cwbRC_RunCmd()                                               */
/*     cwbRC_RunCmdA()                                              */
/*     cwbRC_RunCmdW()                                              */
/*                                                                  */
/*   The following APIs can be used to access programs and their    */
/*   parameters:                                                    */
/*     cwbRC_CreatePgm()                                            */
/*     cwbRC_CreatePgmA()                                           */
/*     cwbRC_CreatePgmW()                                           */
/*     cwbRC_AddParm()                                              */
/*     cwbRC_AddParmA()                                             */
/*     cwbRC_AddParmW()                                             */
/*     cwbRC_CallPgm()                                              */
/*     cwbRC_GetParmCount()                                         */
/*     cwbRC_GetParm()                                              */
/*     cwbRC_GetPgmName()                                           */
/*     cwbRC_GetPgmNameA()                                          */
/*     cwbRC_GetPgmNameW()                                          */
/*     cwbRC_GetLibName()                                           */
/*     cwbRC_GetLibNameA()                                          */
/*     cwbRC_GetLibNameW()                                          */
/*     cwbRC_SetParm()                                              */
/*     cwbRC_SetPgmName()                                           */
/*     cwbRC_SetPgmNameA()                                          */
/*     cwbRC_SetPgmNameW()                                          */
/*     cwbRC_SetLibName()                                           */
/*     cwbRC_SetLibNameA()                                          */
/*     cwbRC_SetLibNameW()                                          */
/*     cwbRC_DeletePgm()                                            */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Link with CWBAPI.LIB import library.                           */
/*   This module is to be used in conjunction with CWBRC.DLL.       */
/*                                                                  */
/*   In addition to the return codes listed for APIs additional     */
/*   operating system specific return codes may also appear.  The   */
/*   precise meaning of these return codes can be found in the     */
/*   operating system manuals or relevant header files.             */
/*                                                                  */
/********************************************************************/

/* Prevent multiple includes */
#if !defined( _CWBRC_H_ )
  #define     _CWBRC_H_

#include <windows.h>

/* Common Client Access/400 API include */
#include "cwb.h"
#include "cwbcosys.h"


#ifdef __cplusplus
extern "C" {
#endif


/*------------------------------------------------------------------*/
/* TYPEDEFS:                                                        */
/*------------------------------------------------------------------*/

typedef cwb_Handle cwbRC_SysHandle;
typedef cwb_Handle cwbRC_PgmHandle;

/*------------------------------------------------------------------*/
/*                                                                  */
/* Definitions for parameter types                                  */
/*                                                                  */
/*------------------------------------------------------------------*/
#define CWBRC_INPUT      1
#define CWBRC_OUTPUT     2
#define CWBRC_INOUT      3

#define CWBRC_TEXT_CONVERT          0x0030
#define CWBRC_TEXT_CONVERT_INPUT    0x0010
#define CWBRC_TEXT_CONVERT_OUTPUT   0x0020

/*-------------------------------------------------------------------*/
/* Component RC errors based on CWB_LAST (in CWB.H)                  */
/*-------------------------------------------------------------------*/

#define CWBRC_START CWB_LAST+1

/*------------------------------------------------------------------*/
/* Invalid system handle                                            */
/*------------------------------------------------------------------*/
#define CWBRC_INVALID_SYSTEM_HANDLE    CWBRC_START

/*------------------------------------------------------------------*/
/* Invalid program handle                                           */
/*------------------------------------------------------------------*/
#define CWBRC_INVALID_PROGRAM          CWBRC_START+1

/*------------------------------------------------------------------*/
/* System name is too long or cannot be converted                   */
/*------------------------------------------------------------------*/
#define CWBRC_SYSTEM_NAME              CWBRC_START+2

/*------------------------------------------------------------------*/
/* Command string is too long or cannot be converted                */
/*------------------------------------------------------------------*/
  #define CWBRC_COMMAND_STRING         CWBRC_START+3

/*------------------------------------------------------------------*/
/* program name is too long or cannot be converted                  */
/*------------------------------------------------------------------*/
  #define CWBRC_PROGRAM_NAME           CWBRC_START+4

/*------------------------------------------------------------------*/
/* Library name is too long or cannot be converted                  */
/*------------------------------------------------------------------*/
 #define CWBRC_LIBRARY_NAME            CWBRC_START+5

/*------------------------------------------------------------------*/
/* Invalid parameter type specified                                 */
/*------------------------------------------------------------------*/
#define CWBRC_INVALID_TYPE             CWBRC_START+6

/*------------------------------------------------------------------*/
/* Invalid parameter length                                         */
/*------------------------------------------------------------------*/
#define CWBRC_INVALID_PARM_LENGTH      CWBRC_START+7

/*------------------------------------------------------------------*/
/* Invalid parameter specified                                      */
/*------------------------------------------------------------------*/
#define CWBRC_INVALID_PARM             CWBRC_START+8

/*------------------------------------------------------------------*/
/* Attempt to add too many parameters to a program                  */
/*------------------------------------------------------------------*/
#define CWBRC_TOO_MANY_PARMS           CWBRC_START+9

/*------------------------------------------------------------------*/
/* Index is out of range for this program                           */
/*------------------------------------------------------------------*/
#define CWBRC_INDEX_RANGE_ERROR        CWBRC_START+10

/*------------------------------------------------------------------*/
/* Command rejected by user exit program                            */
/*------------------------------------------------------------------*/
#define CWBRC_REJECTED_USER_EXIT       CWBRC_START+11

/*------------------------------------------------------------------*/
/* Error in user exit program                                       */
/*------------------------------------------------------------------*/
#define CWBRC_USER_EXIT_ERROR          CWBRC_START+12

/*------------------------------------------------------------------*/
/* Command failed                                                   */
/*------------------------------------------------------------------*/
#define CWBRC_COMMAND_FAILED           CWBRC_START+13

/*------------------------------------------------------------------*/
/* Program not found or could not be accessed                       */
/*------------------------------------------------------------------*/
#define CWBRC_PROGRAM_NOT_FOUND        CWBRC_START+14

/*------------------------------------------------------------------*/
/* Error occurred when calling the program                          */
/*------------------------------------------------------------------*/
#define CWBRC_PROGRAM_ERROR            CWBRC_START+15

/*------------------------------------------------------------------*/
/* Command string is too long                                       */
/*------------------------------------------------------------------*/
#define CWBRC_COMMAND_TOO_LONG         CWBRC_START+16

/*------------------------------------------------------------------*/
/* Unexpected error                                                 */
/*------------------------------------------------------------------*/
#define CWBRC_UNEXPECTED_ERROR         CWBRC_START+99

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbRC_AddParm                                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   Add a parameter to the program that is identified by the       */
/*   handle.  This function should be called once for each          */
/*   parameter that is to be added to the program.  When the        */
/*   program is called the parameters will be in the same order     */
/*   that they are added using this function.                       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbRC_PgmHandle program - input                                */
/*     Handle that was returned by a previous call to the           */
/*     cwbRC_CreatePgm API.  It identifies the program object.      */
/*                                                                  */
/*   unsigned short type - input                                    */
/*     The type of parameter this is.  Use one of the defined       */
/*     parameter types: CWBRC_INPUT, CWBRC_OUTPUT, CWBRC_INOUT.     */
/*     If you want to automatically convert between local CCSID     */
/*     and host CCSID, add the appropriate convert flag to this     */
/*     field with a bitwise-OR.  Use one of the defined parameter   */
/*     types: CWBRC_TEXT_CONVERT, CWBRC_TEXT_CONVERT_INPUT,         */
/*     CWBRC_TEXT_CONVERT_OUTPUT.  The latter two are intended for  */
/*     use with CWBRC_INOUT when conversion is only needed in one   */
/*     direction.                                                   */
/*                                                                  */
/*   unsigned long length - input                                   */
/*     The length of the parameter.  If this is an CWBRC_OUTPUT     */
/*     parameter, the length should be the length of the buffer     */
/*     where the returned parameter will be written.                */
/*                                                                  */
/*   const unsigned char * parameter - input                        */
/*     Pointer to a buffer that will contain:  the value if the     */
/*     type is CWBRC_INPUT or CWBRC_INOUT or the place where the    */
/*     returned parameter is to be written if the type is           */
/*     CWBRC_OUTPUT or CWBRC_INOUT.                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBRC_INVALID_PROGRAM - Invalid program handle.                */
/*   CWBRC_INVALID_TYPE - Invalid type specified.                   */
/*   CWBRC_INVALID_PARM_LENGTH - Invalid parameter length.          */
/*   CWBRC_INVALID_PARM - Invalid parameter.                        */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Parameter data is assumed to be binary.  No conversion will    */
/*   be performed on the parameter data unless one of the           */
/*   conversion flags is set.  For example:                         */
/*      cwbRC_AddParm( hPgm,                                        */
/*                     CWBRC_INOUT | CWBRC_TEXT_CONVERT_OUTPUT,     */
/*                     bufferSize,                                  */
/*                     buffer );                                    */
/*   will use the buffer as is to send to the host, and will        */
/*   convert the output (eg to ASCII) before putting the result     */
/*   into the buffer.                                               */
/*                                                                  */
/********************************************************************/

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )

unsigned int CWB_ENTRY cwbRC_AddParm(
                             cwbRC_PgmHandle       program,
                             unsigned short        type,
                             unsigned long         length,
                             const unsigned char  *parameter);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbRC_AddParmA(
                             cwbRC_PgmHandle       program,
                             unsigned short        type,
                             unsigned long         length,
                             const unsigned char  *parameter);
#endif    // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbRC_AddParmW(
                             cwbRC_PgmHandle       program,
                             unsigned short        type,
                             unsigned long         length,
                             const unsigned char  *parameter);
#endif    // UNICODE-only selection


// UNICODE/ANSI API Selection
#if  (  defined(CWB_UNICODE)  && (!( defined(CWB_OEM) || defined(CWB_ANSI)  ))  )
   #define cwbRC_AddParm             cwbRC_AddParmW
#elif (  defined(CWB_ANSI)  &&  (!( defined(CWB_OEM)  || defined(CWB_UNICODE)  )) )
   #define cwbRC_AddParm             cwbRC_AddParmA
#endif  // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbRC_CallPgm                                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   Calls the program identified by the handle.  The return code   */
/*   will indicate the success or failure of the program.           */
/*   Additional messages can be returned by using the message       */
/*   handle that is returned.                                       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbRC_SysHandle system - input                                 */
/*     Handle that was returned by a previous call to the           */
/*     cwbRC_StartSys function.  It identifies the iSeries          */
/*     system.                                                      */
/*                                                                  */
/*   cwbRC_PgmHandle program - input                                */
/*     Handle that was returned by a previous call to the           */
/*     cwbRC_CreatePgm API.  It identifies the program object.      */
/*     object.                                                      */
/*                                                                  */
/*   cwbSV_ErrHandle msgHandle - output                             */
/*     Any returned messages will be written to this object.  It    */
/*     is created with the cwbSV_CreateErrHandle API.  The          */
/*     messages may be retrieved through the cwbSV_GetErrTextIndexed*/
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrieved.                                                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_COMMUNICATIONS_ERROR - A communications error occurred.    */
/*   CWBRC_INVALID_SYSTEM_HANDLE - Invalid system handle.           */
/*   CWBRC_INVALID_PROGRAM - Invalid program handle.                */
/*   CWBRC_REJECTED_USER_EXIT - Command rejected by user exit       */
/*                              program.                            */
/*   CWBRC_USER_EXIT_ERROR - Error in user exit program.            */
/*   CWBRC_PROGRAM_NOT_FOUND - Program not found.                   */
/*   CWBRC_PROGRAM_ERROR - Error when calling program.              */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbRC_CallPgm(
                             cwbRC_SysHandle     system,
                             cwbRC_PgmHandle     program,
                             cwbSV_ErrHandle     msgHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbRC_CreatePgm                                                */
/*                                                                  */
/* Purpose:                                                         */
/*   This function creates a program object given a program and     */
/*   library name.  The handle that is returned can be used to      */
/*   add parameters to the program and then call the program.       */
/*                                                                  */
/* Parameters:                                                      */
/*   const char *programName - input                                */
/*     Pointer to an ASCIIZ string that contains the name of the    */
/*     program that you want to call.                               */
/*                                                                  */
/*   const char *libraryName - input                                */
/*     Pointer to an ASCIIZ string that contains the name of the    */
/*     library where the program resides.                           */
/*                                                                  */
/*   cwbRC_PgmHandle * program - output                             */
/*     Pointer to a cwbRC_PgmHandle where the handle of the         */
/*     program will be returned.                                    */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or NULL pointer.                     */
/*   CWBRC_PROGRAM_NAME - Program name is too long.                 */
/*   CWBRC_LIBRARY_NAME - Library name is too long.                 */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   You should create a separate program object for each program   */
/*   you want to call on the iSeries.  You can use the functions    */
/*   described in this file to change the vaules of the parameters  */
/*   being sent to the program, but cannot change the number of     */
/*   parameters being sent.                                         */
/*   The programName and libraryName will be uppercased unless      */
/*   enclosed in double quotes.                                     */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbRC_CreatePgm(
                              const char         *programName,
                              const char         *libraryName,
                              cwbRC_PgmHandle    *program);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbRC_CreatePgmA(
                                          LPCSTR            programName
                                        , LPCSTR            libraryName
                                        , cwbRC_PgmHandle  *program
                                      );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbRC_CreatePgmW(
                                          LPCWSTR           programName
                                        , LPCWSTR           libraryName
                                        , cwbRC_PgmHandle  *program
                                      );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbRC_CreatePgm                 cwbRC_CreatePgmW
#elif (  defined(CWB_ANSI) &&  (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbRC_CreatePgm                 cwbRC_CreatePgmA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbRC_DeletePgm                                                */
/*                                                                  */
/* Purpose:                                                         */
/*   This function deletes the program object that is identified    */
/*   by the handle provided.                                        */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbRC_PgmHandle program - input                                */
/*     Handle that was returned by a previous call to the           */
/*     cwbRC_CreatePgm API.  It identifies the program object.      */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBRC_INVALID_PROGRAM - Invalid program handle.                */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbRC_DeletePgm(
                             cwbRC_PgmHandle     program);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbRC_GetClientCCSID                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the coded character set identifier (CCSID) associated with */
/*   the current process.  This CCSID along with the host CCSID can */
/*   be used to convert EBCDIC data returned by some iSeries        */
/*   programs to ASCII data that can be used in client applications.*/
/*                                                                  */
/* Parameters:                                                      */
/*   cwbRC_SysHandle system - input                                 */
/*     Handle that was returned by a previous call to the           */
/*     cwbRC_StartSys function.  It identifies the iSeries          */
/*     system.                                                      */
/*                                                                  */
/*   unsigned long * clientCCSID - output                           */
/*     Pointer to an unsigned long where the client CCSID will be   */
/*     written.                                                     */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or NULL pointer.                     */
/*   CWBRC_INVALID_SYSTEM_HANDLE - Invalid system handle.           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   See related APIs in the CWBNLCNV.H file.                       */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbRC_GetClientCCSID(
                             cwbRC_SysHandle     system,
                             unsigned long      *clientCCSID);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbRC_GetHostCCSID                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the coded character set identifier (CCSID) associated with */
/*   the iSeries server job.  This CCSID along with the client CCSID*/
/*   can be used to convert EBCDIC data returned by some iSeries    */
/*   programs to ASCII data that can be used in client applications.*/
/*                                                                  */
/* Parameters:                                                      */
/*   cwbRC_SysHandle system - input                                 */
/*     Handle that was returned by a previous call to the           */
/*     cwbRC_StartSys function.  It identifies the iSeries          */
/*     system.                                                      */
/*                                                                  */
/*   unsigned long * hostCCSID - output                             */
/*     Pointer to an unsigned long where the host CCSID will be     */
/*     written.                                                     */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or NULL pointer.                     */
/*   CWBRC_INVALID_SYSTEM_HANDLE - Invalid system handle.           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   See related APIs in the CWBNLCNV.H file.                       */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbRC_GetHostCCSID(
                             cwbRC_SysHandle     system,
                             unsigned long      *hostCCSID);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbRC_GetLibName                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the name of the library that was used when creating this   */
/*   program object.                                                */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbRC_PgmHandle program - input                                */
/*     Handle that was returned by a previous call to the           */
/*     cwbRC_CreatePgm API.  It identifies the program object.      */
/*                                                                  */
/*   char * libraryName - output                                    */
/*     Pointer to a ten character buffer where the name of the      */
/*     library will be written.                                     */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or NULL pointer.                     */
/*   CWBRC_INVALID_PROGRAM - Invalid program handle.                */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbRC_GetLibName(
                             cwbRC_PgmHandle     program,
                             char               *libraryName);
#endif   // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbRC_GetLibNameA(
                                           cwbRC_PgmHandle   program
                                         , LPSTR             libraryName
                                       );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbRC_GetLibNameW(
                                           cwbRC_PgmHandle   program
                                         , LPWSTR            libraryName
                                       );
#endif    // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbRC_GetLibName                cwbRC_GetLibNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbRC_GetLibName                cwbRC_GetLibNameA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbRC_GetParm                                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   Retrieve the parameter identified by the index.  The index     */
/*   will range from 0 to the total number of parameters - 1.  This */
/*   number can be obtained by calling the cwbRC_GetParmCount       */
/*   API.                                                           */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbRC_PgmHandle handle - input                                 */
/*     Handle that was returned by a previous call to the           */
/*     cwbRC_CreatePgm API.  It identifies the program object.      */
/*                                                                  */
/*   unsigned short index - input                                   */
/*     The number of the specific parameter in this program that    */
/*     should be retrieved.  This index is zero based.              */
/*                                                                  */
/*   unsigned short * type - output                                 */
/*     Pointer to the type of parameter this is.  The value will be */
/*     one of the defined parameter types: CWBRC_INPUT,             */
/*     CWBRC_OUTPUT, CWBRC_INOUT.                                   */
/*                                                                  */
/*   unsigned long * length - input                                 */
/*     Pointer to the length of the parameter.                      */
/*                                                                  */
/*   unsigned char * * parameter - output                           */
/*     Pointer to a buffer that will contain the address of the     */
/*     actual parameter.                                            */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or NULL pointer.                     */
/*   CWBRC_INVALID_PROGRAM - Invalid program handle.                */
/*   CWBRC_INDEX_RANGE_ERROR - Index is out of range.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbRC_GetParm(
                             cwbRC_PgmHandle     program,
                             unsigned short      index,
                             unsigned short     *type,
                             unsigned long      *length,
                             unsigned char     **parameter);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbRC_GetParmCount                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the number of parameters for this program object.          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbRC_PgmHandle handle - input                                 */
/*     Handle that was returned by a previous call to the           */
/*     cwbRC_CreatePgm API.  It identifies the program object.      */
/*                                                                  */
/*   unsigned short * count - output                                */
/*     Pointer to an unsigned short where the parameter count will  */
/*     be written.                                                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or NULL pointer.                     */
/*   CWBRC_INVALID_PROGRAM - Invalid program handle.                */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbRC_GetParmCount(
                             cwbRC_PgmHandle     program,
                             unsigned short     *count);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbRC_GetPgmName                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the name of the program that was used when creating this   */
/*   program.                                                       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbRC_PgmHandle program - input                                */
/*     Handle that was returned by a previous call to the           */
/*     cwbRC_CreatePgm API.  It identifies the program object.      */
/*                                                                  */
/*   char * programName - output                                    */
/*     Pointer to a ten character buffer where the name of the      */
/*     program will be written.                                     */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or NULL pointer.                     */
/*   CWBRC_INVALID_PROGRAM - Invalid program handle.                */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbRC_GetPgmName(
                             cwbRC_PgmHandle     program,
                             char               *programName);
#endif   // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbRC_GetPgmNameA(
                                           cwbRC_PgmHandle   program
                                         , LPSTR             programName
                                       );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbRC_GetPgmNameW(
                                           cwbRC_PgmHandle   program
                                         , LPWSTR            programName
                                       );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbRC_GetPgmName                cwbRC_GetPgmNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbRC_GetPgmName                cwbRC_GetPgmNameA
#endif // of UNICODE/ANSI selection

//********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbRC_GetSysName                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the name of the system that was used when starting this    */
/*   system.                                                        */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbRC_SysHandle system - input                                 */
/*     Handle that was returned by a previous call to the           */
/*     cwbRC_StartSys function.  It identifies the iSeries          */
/*     system.                                                      */
/*                                                                  */
/*   char * systemName - output                                     */
/*     Pointer to an 256 character buffer where the name of the     */
/*     system will be written.                                      */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or NULL pointer.                     */
/*   CWBRC_INVALID_SYSTEM_HANDLE - Invalid system handle.           */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbRC_GetSysName(
                             cwbRC_SysHandle     system,
                             char               *systemName);
#endif   // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbRC_GetSysNameA(
                                           cwbRC_SysHandle  system
                                         , LPSTR            systemName
                                       );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbRC_GetSysNameW(
                                           cwbRC_SysHandle  system
                                         , LPWSTR           systemName
                                       );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbRC_GetSysName                cwbRC_GetSysNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbRC_GetSysName                cwbRC_GetSysNameA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbRC_RunCmd                                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Issues the command on the system identified by the handle.     */
/*   The return code will indicate success or failure of the        */
/*   command.  Additional messages can be returned by using the     */
/*   message handle that is returned.                               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbRC_SysHandle system - input                                 */
/*     Handle that was returned by a previous call to the           */
/*     cwbRC_StartSys function.  It identifies the iSeries          */
/*     system.                                                      */
/*                                                                  */
/*   const char *commandString - input                              */
/*     Pointer to a string that contains the command to be issued   */
/*     on the iSeries system.  This is an ASCIIZ string.            */
/*                                                                  */
/*   cwbSV_ErrHandle msgHandle - output                             */
/*     Any messages returned from the iSeries will be written to    */
/*     this object.  It is created with the cwbSV_CreateErrHandle   */
/*     API.  The messages may be retrieved through the              */
/*     cwbSV_GetErrTextIndexed API.  If the parameter is set to     */
/*     zero, no messages will be retrieved.                         */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_COMMUNICATIONS_ERROR - A communications error occurred.    */
/*   CWB_INVALID_POINTER - Bad or NULL pointer.                     */
/*   CWBRC_INVALID_SYSTEM_HANDLE - Invalid system handle.           */
/*   CWBRC_REJECTED_USER_EXIT - Command rejected by user exit       */
/*                              program.                            */
/*   CWBRC_USR_EXIT_ERROR - Error in user exit program.             */
/*   CWBRC_COMMAND_FAILED - Command failed.                         */
/*   CWBRC_COMMAND_TOO_LONG - Command string is too long.           */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbRC_RunCmd(
                             cwbRC_SysHandle     system,
                             const char         *commandString,
                             cwbSV_ErrHandle     msgHandle);
#endif   // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbRC_RunCmdA(
                                       cwbRC_SysHandle   system
                                     , LPCSTR            commandString
                                     , cwbSV_ErrHandle   msgHandle
                                   );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbRC_RunCmdW(
                                       cwbRC_SysHandle   system
                                     , LPCWSTR           commandString
                                     , cwbSV_ErrHandle   msgHandle
                                   );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbRC_RunCmd                    cwbRC_RunCmdW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbRC_RunCmd                    cwbRC_RunCmdA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbRC_SetLibName                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the name of the library for this program object.           */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbRC_PgmHandle program - input                                */
/*     Handle that was returned by a previous call to the           */
/*     cwbRC_CreatePgm API.  It identifies the program object.      */
/*                                                                  */
/*   const char *libraryName - input                                */
/*     Pointer to an ASCIIZ string that contains the name of the    */
/*     library where the program resides.                           */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBRC_INVALID_PROGRAM - Invalid program handle.                */
/*   CWBRC_LIBRARY_NAME - Library name is too long.                 */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use this function to change the name of the name of the library*/
/*   that contains the program you want to call.  This function     */
/*   should not be used to call a different program with different  */
/*   parameters.                                                    */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbRC_SetLibName(
                             cwbRC_PgmHandle     program,
                             const char         *libraryName);
#endif   // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbRC_SetLibNameA(
                                           cwbRC_PgmHandle  program
                                         , LPCSTR           libraryName
                                       );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbRC_SetLibNameW(
                                           cwbRC_PgmHandle  program
                                         , LPCWSTR          libraryName
                                       );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbRC_SetLibName                cwbRC_SetLibNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbRC_SetLibName                cwbRC_SetLibNameA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbRC_SetParm                                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the parameter value identified by the index.  The index    */
/*   will range from 0 to the total number of parameters - 1.  This */
/*   number can be obtained by calling the cwbRC_GetParmCount       */
/*   API.  Note that this function is to be used to change a        */
/*   parameter.  Use cwbRC_AddParm to create the parameter.         */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbRC_PgmHandle handle - input                                 */
/*     Handle that was returned by a previous call to the           */
/*     cwbRC_CreatePgm API.  It identifies the program object.      */
/*                                                                  */
/*   unsigned short index - input                                   */
/*     The number of the specific parameter in this program that    */
/*     should be changed.  This index is zero based.                */
/*                                                                  */
/*   unsigned short type - input                                    */
/*     The type of parameter this is.  Use one of the defined       */
/*     parameter types: CWBRC_INPUT, CWBRC_OUTPUT, CWBRC_INOUT.     */
/*     If you want to automatically convert between local CCSID     */
/*     and host CCSID, add the appropriate convert flag to this     */
/*     field with a bitwise-OR.  Use one of the defined parameter   */
/*     types: CWBRC_TEXT_CONVERT, CWBRC_TEXT_CONVERT_INPUT,         */
/*     CWBRC_TEXT_CONVERT_OUTPUT.  The latter two are intended for  */
/*     use with CWBRC_INOUT when conversion is only needed in one   */
/*     direction.                                                   */
/*                                                                  */
/*   unsigned long length - input                                   */
/*     The length of the parameter.  If this is an CWBRC_OUT        */
/*     parameter, the length should be the length of the buffer     */
/*     where the returned parameter will be written.                */
/*                                                                  */
/*   const unsigned char * parameter - input                        */
/*     Pointer to a buffer that will contain:  the value if the     */
/*     type is CWBRC_INPUT or CWBRC_INOUT or the place where the    */
/*     return parameter is to be written if the type is             */
/*     CWBRC_OUTPUT or CWBRC_INOUT.                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBRC_INVALID_PROGRAM - Invalid program handle.                */
/*   CWBRC_INVALID_TYPE - Invalid type specified.                   */
/*   CWBRC_INVALID_PARM_LENGTH - Invalid parameter length.          */
/*   CWBRC_INVALID_PARM - Invalid parameter.                        */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Parameter data is assumed to be binary.  No conversion will    */
/*   be performed on the parameter data unless one of the           */
/*   conversion flags is set.  For example:                         */
/*      cwbRC_SetParm( hPgm,                                        */
/*                     CWBRC_INOUT | CWBRC_TEXT_CONVERT_OUTPUT,     */
/*                     bufferSize,                                  */
/*                     buffer );                                    */
/*   will use the buffer as is to send to the host, and will        */
/*   convert the output (eg to ASCII) before putting the result     */
/*   into the buffer.                                               */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbRC_SetParm(
                             cwbRC_PgmHandle       program,
                             unsigned short        index,
                             unsigned short        type,
                             unsigned long         length,
                             const unsigned char  *parameter);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbRC_SetPgmName                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the name of the program for this program object.           */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbRC_PgmHandle program - input                                */
/*     Handle that was returned by a previous call to the           */
/*     cwbRC_CreatePgm API.  It identifies the program object.      */
/*                                                                  */
/*   const char *programName - input                                */
/*     Pointer to an ASCIIZ string that contains the name of the    */
/*     program that you want to call.                               */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBRC_INVALID_PROGRAM - Invalid program handle.                */
/*   CWBRC_PROGRAM_NAME - Program name is too long.                 */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use this function to change the name of the program that you   */
/*   want to call.  This function should not be used to change the  */
/*   program object to call a different program with different      */
/*   parameters.                                                    */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbRC_SetPgmName(
                             cwbRC_PgmHandle     program,
                             const char         *programName);
#endif   // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbRC_SetPgmNameA(
                                           cwbRC_PgmHandle   program
                                         , LPCSTR            programName
                                       );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbRC_SetPgmNameW(
                                           cwbRC_PgmHandle   program
                                         , LPCWSTR           programName
                                       );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbRC_SetPgmName                cwbRC_SetPgmNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbRC_SetPgmName                cwbRC_SetPgmNameA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbRC_StartSys                                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   This function starts a conversation with the specified system. */
/*   If the conversation is successfully started, a handle is       */
/*   returned.  Use this handle with all subsequent calls to        */
/*   issue commands or call programs.  When the conversation is     */
/*   no longer needed, use the handle with the API,                 */
/*   cwbRC_StopSys to end the conversation.                         */
/*   The cwbRC_StartSys API may be called multiple times within an  */
/*   application.  If the application name is set to NULL, a new    */
/*   conversation is started each time the API is called.  If the   */
/*   application name is set, the same system handle is returned    */
/*   each time this function is called.                             */
/*                                                                  */
/* Parameters:                                                      */
/*   const char *systemName - input                                 */
/*           Pointer to an ASCIIZ string that contains the name     */
/*           of the system that you want programs and commands      */
/*           to be executed on.                                     */
/*                                                                  */
/*   const char *appName - input                                    */
/*           Pointer to an ASCIIZ string of no more than 12         */
/*           characters.  This uniquely identifies the application  */
/*           that will share a single conversation for running.     */
/*           commands and calling programs.                         */
/*                                                                  */
/*   cwbRC_SysHandle * system - output                              */
/*           Pointer to a cwbRC_SysHandle where the handle of       */
/*           the system will be returned.                           */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_COMMUNICATIONS_ERROR - A communications error occurred.    */
/*   CWB_SERVER_PROGRAM_NOT_FOUND - iSeries application not found.  */
/*   CWB_HOST_NOT_FOUND - iSeries system inactive or does not exist.*/
/*   CWB_SECURITY_ERROR - A security error has occurred.            */
/*   CWB_LICENSE_ERROR - A license error has occurred.              */
/*   CWB_CONFIG_ERROR - A configuration error has occurred.         */
/*   CWBRC_SYSTEM_NAME - System name is too long.                   */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The application name will typically be set to NULL unless you  */
/*   have a specific need to share a conversation between several   */
/*   threads within the same process.                               */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbRC_StartSys(
                             const char         *systemName,
                             const char         *appName,
                             cwbRC_SysHandle    *system);
#endif   // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbRC_StartSysA(
                                         LPCSTR            systemName
                                       , LPCSTR            appName
                                       , cwbRC_SysHandle  *system
                                     );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbRC_StartSysW(
                                         LPCWSTR           systemName
                                       , LPCWSTR           appName
                                       , cwbRC_SysHandle  *system
                                     );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbRC_StartSys                  cwbRC_StartSysW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbRC_StartSys                  cwbRC_StartSysA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbRC_StartSysEx                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   This function starts a conversation with the specified system. */
/*   If the conversation is successfully started, a handle is       */
/*   returned.  Use this handle with all subsequent calls to        */
/*   issue commands or call programs.  When the conversation is     */
/*   no longer needed, use the handle with the API,                 */
/*   cwbRC_StopSys to end the conversation.                         */
/*   The cwbRC_StartSys API may be called multiple times within an  */
/*   application.  If the application name is set to NULL, a new    */
/*   conversation is started each time the API is called.  If the   */
/*   application name is set, the same system handle is returned    */
/*   each time this function is called.                             */
/*                                                                  */
/* Parameters:                                                      */
/*   const cwbCO_SysHandle systemObj - input                        */
/*           Handle to an existing system object of                 */
/*           the system that you want programs and commands         */
/*           to be executed on.                                     */
/*                                                                  */
/*   cwbRC_SysHandle * system - output                              */
/*           Pointer to a cwbRC_SysHandle where the handle of       */
/*           the system will be returned.                           */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_COMMUNICATIONS_ERROR - A communications error occurred.    */
/*   CWB_SERVER_PROGRAM_NOT_FOUND - iSeries application not found.  */
/*   CWB_HOST_NOT_FOUND - iSeries system inactive or does not exist.*/
/*   CWB_SECURITY_ERROR - A security error has occurred.            */
/*   CWB_LICENSE_ERROR - A license error has occurred.              */
/*   CWB_CONFIG_ERROR - A configuration error has occurred.         */
/*   CWBRC_SYSTEM_NAME - System name is too long.                   */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The application name will typically be set to NULL unless you  */
/*   have a specific need to share a conversation between several   */
/*   threads within the same process.                               */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbRC_StartSysEx(
                             const cwbCO_SysHandle systemObj,
                             cwbRC_SysHandle    *system);

#endif   // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbRC_StartSysExA(
                                         const cwbCO_SysHandle  systemObj
                                       , cwbRC_SysHandle  *system
                                     );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbRC_StartSysExW(
                                         const cwbCO_SysHandle   systemObj
                                       , cwbRC_SysHandle  *system
                                     );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbRC_StartSysEx                  cwbRC_StartSysExW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbRC_StartSysEx                  cwbRC_StartSysExA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbRC_StopSys                                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   This function stops a conversation with the system specified   */
/*   by the handle.  This handle can no longer be used to issue     */
/*   program calls or commands.                                     */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbRC_SysHandle system - input                                 */
/*     Handle that was returned by a previous call to the           */
/*     cwbRC_StartSys function.  It identifies the iSeries          */
/*     system.                                                      */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBRC_INVALID_SYSTEM_HANDLE - Invalid system handle.           */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbRC_StopSys(
                             cwbRC_SysHandle     system);


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbRC_LimitedUser                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   This function checks to see if the user profile associated     */
/*   with system handle has limited capabilities.                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbRC_SysHandle system - input                                 */
/*     Handle that was returned by a previous call to the           */
/*     cwbRC_StartSys function.  It identifies the iSeries          */
/*     system.                                                      */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion, user is NOT limited            */
/*   CWBRC_INVALID_SYSTEM_HANDLE - Invalid system handle.           */
/*   CWB_LIMITED_CAPABILITIES_USERID - User is limited              */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/*   The user will be prevented from running iSeries commands via   */
/*   the command line RmtCmd.exe program when their user profile    */
/*   has Limit Capabilities (LMTCPB) enabled.                       */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbRC_LimitedUser(
                             cwbRC_SysHandle     system);


#ifdef __cplusplus
}
#endif

#endif /* _CWBRC_H_ */
