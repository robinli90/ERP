/********************************************************************/
/*                                                                  */
/* 5722-XE1                                                         */
/* (C) Copyright IBM Corp. 1995,2002                                */
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
/*   CWBCO.H                                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   The functions listed in this file can be used to get           */
/*   information about environments and connections configured      */
/*   using Client Access.                                           */
/*                                                                  */
/*   The APIs can be broken down into three groups:                 */
/*                                                                  */
/*   The following APIs can be used to create a list of configured  */
/*   systems, either in the currently active environment or a       */
/*   different environment.  The size (number of entries) in the    */
/*   list, and each entry in succession, can be retrieved:          */
/*     cwbCO_CreateSysListHandle()                                  */
/*     cwbCO_CreateSysListHandleEnv()                               */
/*     cwbCO_CreateSysListHandleEnvA()                              */
/*     cwbCO_CreateSysListHandleEnvW()                              */
/*     cwbCO_GetSysListSize()                                       */
/*     cwbCO_GetNextSysName()                                       */
/*     cwbCO_GetNextSysNameA()                                      */
/*     cwbCO_GetNextSysNameW()                                      */
/*     cwbCO_DeleteSysListHandle()                                  */
/*                                                                  */
/*   The following APIs can be used to get information about        */
/*   individual systems that are configured or connected.  Unless   */
/*   environment name is passed as a parameter, these APIs work     */
/*   only with the currently active environment:                    */
/*     cwbCO_GetDefaultSysName()                                    */
/*     cwbCO_GetDefaultSysNameA()                                   */
/*     cwbCO_GetDefaultSysNameW()                                   */
/*     cwbCO_GetConnectedSysName()                                  */
/*     cwbCO_GetConnectedSysNameA()                                 */
/*     cwbCO_GetConnectedSysNameW()                                 */
/*     cwbCO_IsSystemConfigured()                                   */
/*     cwbCO_IsSystemConfiguredA()                                  */
/*     cwbCO_IsSystemConfiguredW()                                  */
/*     cwbCO_IsSystemConfiguredEnv()                                */
/*     cwbCO_IsSystemConfiguredEnvA()                               */
/*     cwbCO_IsSystemConfiguredEnvW()                               */
/*     cwbCO_IsSystemConnected()                                    */
/*     cwbCO_IsSystemConnectedA()                                   */
/*     cwbCO_IsSystemConnectedW()                                   */
/*     cwbCO_GetUserID()                                            */
/*     cwbCO_GetUserIDA()                                           */
/*     cwbCO_GetUserIDW()                                           */
/*     cwbCO_GetActiveConversations()                               */
/*     cwbCO_GetActiveConversationsA()                              */
/*     cwbCO_GetActiveConversationsW()                              */
/*     cwbCO_GetHostVersion()                                       */
/*     cwbCO_GetHostVersionA()                                      */
/*     cwbCO_GetHostVersionW()                                      */
/*                                                                  */
/*   The following APIs can be used to get names of environments    */
/*   that have been configured:                                     */
/*     cwbCO_GetNumberOfEnvironments()                              */
/*     cwbCO_GetEnvironmentName()                                   */
/*     cwbCO_GetEnvironmentNameA()                                  */
/*     cwbCO_GetEnvironmentNameW()                                  */
/*     cwbCO_GetActiveEnvironment()                                 */
/*     cwbCO_GetActiveEnvironmentA()                                */
/*     cwbCO_GetActiveEnvironmentW()                                */
/*                                                                  */
/*   The following APIs can be used to determine if the calling     */
/*   application can modify/change environments and connection      */
/*   information.                                                   */
/*     cwbCO_CanConnectNewSystem()                                  */
/*     cwbCO_CanSetActiveEnvironment()                              */
/*     cwbCO_CanModifyEnvironmentList()                             */
/*     cwbCO_CanModifySystemList()                                  */
/*     cwbCO_CanModifySystemListEnv()                               */
/*     cwbCO_CanModifySystemListEnvA()                              */
/*     cwbCO_CanModifySystemListEnvW()                              */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Some or all of the APIs can return CWBCO_INTERNAL_ERROR,       */
/*   though this indicates a problem with Client Access and should  */
/*   not be common.                                                 */
/*   Link with CWBAPI.LIB import library.                           */
/*   This module is to be used in conjunction with CWBCO.DLL.       */
/*                                                                  */
/*   In addition to the return codes listed for APIs additional     */
/*   operating system specific return codes may also appear.  The   */
/*   precise meaning of these return codes can be found in the      */
/*   operating system manuals or relevant header files.             */
/*                                                                  */
/********************************************************************/

/* Prevent multiple includes */
#if !defined( _CWBCO_H_ )
  #define     _CWBCO_H_

#include <windows.h>

/* Common Client Access/400 API include */
#include "cwb.h"


#if defined( __cplusplus )
extern "C" {
#endif


/*------------------------------------------------------------------*/
/* Component CO errors based on CWB_LAST (in CWB.H)                 */
/*------------------------------------------------------------------*/
#define CWBCO_START   CWB_LAST+1

#define CWBCO_END_OF_LIST                     CWBCO_START+1
#define CWBCO_DEFAULT_SYSTEM_NOT_DEFINED      CWBCO_START+2
#define CWBCO_DEFAULT_SYSTEM_NOT_CONFIGURED   CWBCO_START+3
#define CWBCO_SYSTEM_NOT_CONNECTED            CWBCO_START+4
#define CWBCO_SYSTEM_NOT_CONFIGURED           CWBCO_START+5
#define CWBCO_NO_USER_ID                      CWBCO_START+6
#define CWBCO_INTERNAL_ERROR                  CWBCO_START+7
#define CWBCO_NO_SUCH_ENVIRONMENT             CWBCO_START+8
#define CWBCO_RESERVED_START                  CWBCO_START+100

/*------------------------------------------------------------------*/
/* Definitions to use when specifying which User ID you mean        */
/*------------------------------------------------------------------*/
#define CWBCO_DEFAULT_USER_ID                 0
#define CWBCO_CURRENT_USER_ID                 1

/*------------------------------------------------------------------*/
/* TYPEDEFS:                                                        */
/*------------------------------------------------------------------*/
typedef cwb_Handle cwbCO_SysListHandle;


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_CreateSysListHandle                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Creates a handle to list of configured system names in the     */
/*   environment currently in use.                                  */
/*                                                                  */
/* Parameters:                                                      */
/*                                                                  */
/*   cwbCO_SysListHandle *listHandle - output                       */
/*     Pointer to a list handle that will be passed back on output. */
/*     This handle is needed for other calls using the list.        */
/*                                                                  */
/*   cwbSV_ErrorHandle errorHandle - input                          */
/*     If the API call fails, the message object associated with    */
/*     this handle will be filled in with message text that         */
/*     describes the error.  If this parameter is zero, no messages */
/*     will be available.                                           */
/*                                                                  */
/* Return Codes:                                                    */
/*  The following list shows common return values.                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_POINTER - Pointer to the list handle is NULL       */
/*                                                                  */
/* Usage Notes:                                                     */
/*   cwbCO_DeleteSysListHandle() must be called to free             */
/*   resources allocated with this API.                             */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbCO_CreateSysListHandle(
                             cwbCO_SysListHandle *listHandle,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_CreateSysListHandleEnv                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Creates a handle to list of configured system names of the     */
/*   specified environment.                                         */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysListHandle *listHandle - output                       */
/*     Pointer to a list handle that will be passed back on output. */
/*     This handle is needed for other calls using the list.        */
/*                                                                  */
/*   cwbSV_ErrorHandle errorHandle - input                          */
/*     If the API call fails, the message object associated with    */
/*     this handle will be filled in with message text that         */
/*     describes the error.  If this parameter is zero, no messages */
/*     will be available.                                           */
/*                                                                  */
/*   LPCSTR pEnvironment - input                                    */
/*     Pointer to a string containing the desired environment name. */
/*     If pEnvironment is the NULL pointer, or points to the NULL   */
/*     string ("\0"), the system list of the current active         */
/*     environment is returned.                                     */
/*                                                                  */
/* Return Codes:                                                    */
/*  The following list shows common return values.                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_INVALID_POINTER - Pointer to the list handle is NULL.      */
/*   CWBCO_NO_SUCH_ENVIRONMENT - The specified environment does not */
/*                               exist.                             */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   cwbCO_DeleteSysListHandle() must be called to free             */
/*   resources allocated with this API.                             */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbCO_CreateSysListHandleEnv(
                             cwbCO_SysListHandle *listHandle,
                             cwbSV_ErrHandle      errorHandle,
                             LPCSTR               pEnvironment );
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_CreateSysListHandleEnvA(
                             cwbCO_SysListHandle *listHandle
                           , cwbSV_ErrHandle      errorHandle
                           , LPCSTR               pEnvironment
                                                   );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbCO_CreateSysListHandleEnvW(
                             cwbCO_SysListHandle *listHandle
                           , cwbSV_ErrHandle      errorHandle
                           , LPCWSTR              pEnvironment
                                                   );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbCO_CreateSysListHandleEnv    cwbCO_CreateSysListHandleEnvW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbCO_CreateSysListHandleEnv    cwbCO_CreateSysListHandleEnvA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_DeleteSysListHandle                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Deletes a handle to a list of configured system names.  This   */
/*   must be done last when finished using the system name list.    */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysListHandle - listHandle                               */
/*     A handle to the system name list to delete.                  */
/*                                                                  */
/* Return Codes:                                                    */
/*  The following list shows common return values.                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_INVALID_HANDLE - The list handle is not valid.             */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use this API to delete the list created with the               */
/*   cwbCO_CreateSysListHandle or cwbCO_CreateSysListHandleEnv API. */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbCO_DeleteSysListHandle(
                             cwbCO_SysListHandle listHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_GetDefaultSysName                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the name of the default system in the active environment.  */
/*                                                                  */
/* Parameters:                                                      */
/*                                                                  */
/*   char *defaultSystemName - output                               */
/*     Pointer to a buffer that will contain the NULL-terminated    */
/*     system name.                                                 */
/*                                                                  */
/*   unsigned long bufferSize - input                               */
/*     Size of input buffer.                                        */
/*                                                                  */
/*   unsigned long *needed - output                                 */
/*     Number of bytes needed to hold entire system name including  */
/*     the terminating NULL.                                        */
/*                                                                  */
/*   cwbSV_ErrorHandle errorhandle - input                          */
/*     If the API call fails, the message object associated with    */
/*     this handle will be filled in with message text that         */
/*     describes the error.  If this parameter is zero, no messages */
/*     will be available.                                           */
/*                                                                  */
/* Return Codes:                                                    */
/*  The following list shows common return values.                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_INVALID_POINTER - Pointer to the system name or pointer    */
/*                         to buffer size needed is NULL.           */
/*                         Check messages in the History Log to     */
/*                         determine which are NULL.                */
/*   CWB_BUFFER_OVERFLOW - Not enough room in output buffer to      */
/*                         hold the entire system name.  Use        */
/*                         *needed to determine the correct         */
/*                         size.  No error message is logged to the */
/*                         History Log since the caller is expected */
/*                         to recover from this error and continue. */
/*   CWBCO_DEFAULT_SYSTEM_NOT_DEFINED - The setting for the default */
/*                                      system has not been         */
/*                                      defined in the active       */
/*                                      environment.                */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbCO_GetDefaultSysName(
                             char               *defaultSystemName,
                             unsigned long       bufferSize,
                             unsigned long      *needed,
                             cwbSV_ErrHandle     errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_GetDefaultSysNameA(
                                 LPSTR             defaultSystemName
                               , ULONG             bufferSize
                               , ULONG            *needed
                               , cwbSV_ErrHandle   errorHandle
                                              );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbCO_GetDefaultSysNameW(
                                 LPWSTR            defaultSystemName
                               , ULONG             bufferSize
                               , ULONG            *needed
                               , cwbSV_ErrHandle   errorHandle
                                              );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbCO_GetDefaultSysName         cwbCO_GetDefaultSysNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbCO_GetDefaultSysName         cwbCO_GetDefaultSysNameA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_GetNextSysName                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the name of the next system from a list of systems.        */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysListHandle handleList - input                         */
/*     Handle to a list of systems.                                 */
/*                                                                  */
/*   char *systemName - output                                      */
/*     Pointer to a buffer that will contain the system name.       */
/*                                                                  */
/*   unsigned long bufferSize - input                               */
/*     Size of the buffer pointed to by systemName.                 */
/*                                                                  */
/*   unsigned long *needed - output                                 */
/*     Number of bytes needed to hold entire system name.           */
/*                                                                  */
/* Return Codes:                                                    */
/*  The following list shows common return values.                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_INVALID_HANDLE - The list handle is not valid.             */
/*   CWB_INVALID_POINTER - Pointer to system name or pointer to     */
/*                         buffer size needed is NULL.              */
/*                         Check messages in the History Log to     */
/*                         determine which are NULL.                */
/*   CWB_BUFFER_OVERFLOW - Not enough room in output buffer to hold */
/*                         entire system name.  Use *needed to      */
/*                         determine the correct size.              */
/*                         No error message is logged to the        */
/*                         History Log since the caller is expected */
/*                         to recover from this error and continue. */
/*   CWBCO_END_OF_LIST   - The end of the system list has been      */
/*                         reached. No system name was returned.    */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   If the system list passed in was created using the API         */
/*   cwbCO_CreateSystemListHandle then the system returned is       */
/*   configured in the currently active environment, unless between */
/*   these API calls the user has removed it or switched to a       */
/*   different environment.  If cwbCO_CreateSysListHandleEnv was    */
/*   called to create the system list, then the system returned is  */
/*   configured in the environment passed to that API, unless the   */
/*   user has since removed it.                                     */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbCO_GetNextSysName(
                             cwbCO_SysListHandle listHandle,
                             char               *systemName,
                             unsigned long       bufferSize,
                             unsigned long      *needed);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_GetNextSysNameA(
                             cwbCO_SysListHandle listHandle
                           , LPSTR               systemName
                           , ULONG               bufferSize
                           , ULONG              *needed
                                           );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbCO_GetNextSysNameW(
                             cwbCO_SysListHandle listHandle
                           , LPWSTR              systemName
                           , ULONG               bufferSize
                           , ULONG              *needed
                                           );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbCO_GetNextSysName            cwbCO_GetNextSysNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbCO_GetNextSysName            cwbCO_GetNextSysNameA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_GetSysListSize                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Gets the number of system names in the list.                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysListHandle listHandle - input                         */
/*     Handle of the list of systems.                               */
/*                                                                  */
/*   unsigned long *listSize - output                               */
/*     On output this will be set to the number of systems in the   */
/*     the list.                                                    */
/*                                                                  */
/* Return Codes:                                                    */
/*  The following list shows common reuturn values.                 */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_INVALID_HANDLE - The list handle is not valid.             */
/*   CWB_INVALID_POINTER - Pointer to the list size is NULL.        */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbCO_GetSysListSize(
                             cwbCO_SysListHandle  listHandle,
                             unsigned long       *listSize);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_GetConnectedSysName                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the name of the connected system corresponding to the      */
/*   index.                                                         */
/* Parameters:                                                      */
/*   char *systemName - output                                      */
/*     Pointer to a buffer that will contain the system name.       */
/*                                                                  */
/*   unsigned long * bufferSize - input/output                      */
/*     input: Size of the buffer pointed to by *systemName.         */
/*     output: Size of buffer needed.                               */
/*                                                                  */
/*   unsigned long index                                            */
/*     0 corresponds to the first connected system.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*  The following list shows common return values.                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_INVALID_POINTER - Pointer to system name or pointer to     */
/*                         buffer size needed is NULL.              */
/*                         Check messages in the History Log to     */
/*                         determine which are NULL.                */
/*   CWB_BUFFER_OVERFLOW - Not enough room in output buffer to hold */
/*                         entire system name.  Use *bufferSize to  */
/*                         determine the correct size.              */
/*                         No error message is logged to the        */
/*                         History Log since the caller is expected */
/*                         to recover from this error and continue. */
/*   CWBCO_END_OF_LIST   - The end of connected system list has     */
/*                         been reached.  No system name was        */
/*                         returned.                                */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Systems can only be connected when in the currently active     */
/*   environment, so system names returned will only be from that   */
/*   environment.                                                   */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbCO_GetConnectedSysName(
                             char               *systemName,
                             unsigned long      *bufferSize,
                             unsigned long       index);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_GetConnectedSysNameA(
                                         LPSTR      systemName
                                       , ULONG     *bufferSize
                                       , ULONG      index
                                                );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbCO_GetConnectedSysNameW(
                                         LPWSTR     systemName
                                       , ULONG     *bufferSize
                                       , ULONG      index
                                                );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbCO_GetConnectedSysName       cwbCO_GetConnectedSysNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbCO_GetConnectedSysName       cwbCO_GetConnectedSysNameA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_IsSystemConfigured                                       */
/*                                                                  */
/* Purpose:                                                         */
/*   Check if the input system is configured in the environment     */
/*   currently in use.                                              */
/* Parameters:                                                      */
/*   LPCSTR systemName - input                                     */
/*     Pointer to a buffer that contains the system name.           */
/*                                                                  */
/* Return Codes:                                                    */
/*  The following list shows common return values.                  */
/*   CWB_TRUE: system is configured.                                */
/*   CWB_FALSE: system is not configured, systemName is NULL, or    */
/*              system name contains one or more UNICODE characters */
/*              which cannot be converted.                          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   None                                                           */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
cwb_Boolean CWB_ENTRY cwbCO_IsSystemConfigured(
                                              LPCSTR    systemName);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
cwb_Boolean CWB_ENTRY cwbCO_IsSystemConfiguredA(
                                              LPCSTR    systemName
                                                      );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
cwb_Boolean CWB_ENTRY cwbCO_IsSystemConfiguredW(
                                              LPCWSTR   systemName
                                                      );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbCO_IsSystemConfigured        cwbCO_IsSystemConfiguredW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbCO_IsSystemConfigured        cwbCO_IsSystemConfiguredA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_IsSystemConfiguredEnv                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   Check if the input system is configured in the environment     */
/*   specified.                                                     */
/* Parameters:                                                      */
/*   LPCSTR systemName - input                                      */
/*     Pointer to a buffer that contains the system name.           */
/*                                                                  */
/*   LPCSTR pEnvironment - input                                    */
/*     Pointer to a buffer that contains the environment name.      */
/*     If pEnvironment is NULL, or if it points to an empty string, */
/*     the environment currently in use is checked.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*  The following list shows common return values.                  */
/*   CWB_TRUE: system is configured.                                */
/*   CWB_FALSE: system is not configured, environment does not      */
/*              exist, systemName is NULL, or system name or        */
/*              environment contains one or more UNICODE characters */
/*              which cannot be converted.                          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   None                                                           */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
cwb_Boolean CWB_ENTRY cwbCO_IsSystemConfiguredEnv(
                             LPCSTR    systemName,
                             LPCSTR    pEnvironment);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
cwb_Boolean CWB_ENTRY cwbCO_IsSystemConfiguredEnvA(
                             LPCSTR    systemName,
                             LPCSTR    pEnvironment
                                                         );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
cwb_Boolean CWB_ENTRY cwbCO_IsSystemConfiguredEnvW(
                             LPCWSTR   systemName,
                             LPCWSTR   pEnvironment
                                                         );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbCO_IsSystemConfiguredEnv     cwbCO_IsSystemConfiguredEnvW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbCO_IsSystemConfiguredEnv     cwbCO_IsSystemConfiguredEnvA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_IsSystemConnected                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Check if the input system is currently connected.              */
/* Parameters:                                                      */
/*   LPCSTR systemName - input                                      */
/*     Pointer to a buffer that contains the system name.           */
/*                                                                  */
/* Return Codes:                                                    */
/*  The following list shows common return values.                  */
/*   CWB_TRUE: system is currently connected.                       */
/*   CWB_FALSE: system is not connected, systemName is NULL, or     */
/*              system name contains one or more UNICODE characters */
/*              which cannot be converted.                          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Only systems configured in the currently active environment    */
/*   can be connected to, so the system name passed in must be      */
/*   configured in the currently active environment.                */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
cwb_Boolean CWB_ENTRY cwbCO_IsSystemConnected(
                                             LPCSTR systemName);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
cwb_Boolean CWB_ENTRY cwbCO_IsSystemConnectedA(
                                             LPCSTR systemName);
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
cwb_Boolean CWB_ENTRY cwbCO_IsSystemConnectedW(
                                             LPCWSTR systemName);
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbCO_IsSystemConnected    cwbCO_IsSystemConnectedW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbCO_IsSystemConnected    cwbCO_IsSystemConnectedA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_GetUserID                                                */
/*                                                                  */
/* Purpose:                                                         */
/*   Get signon or default user ID of the input system as it is     */
/*   configured and possibly connected in the currently active      */
/*   environment.                                                   */
/* Parameters:                                                      */
/*   LPCSTR systemName - input                                      */
/*     Pointer to a buffer that contains the system name.           */
/*   char *userID - output                                          */
/*     Pointer to a buffer where the desired userID of the system   */
/*     is returned.                                                 */
/*   unsigned int userID_Type - input                               */
/*     Specify whether current user ID of connected system          */
/*     (CWBCO_CURRENT_USER_ID) or default user ID of configured     */
/*     system (CWBCO_DEFAULT_USER_ID) is to be returned.            */
/*   unsigned long * bufferSize - input/output                      */
/*     Pointer to a value that indicates the size of the userID     */
/*     buffer. If the buffer is not big enough, the value needed    */
/*     is returned.                                                 */
/* Return Codes:                                                    */
/*  The following list shows common return values.                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_INVALID_POINTER - One or more input pointers are invalid.  */
/*                         Check messages in the History Log to     */
/*                         determine which are invalid.             */
/*   CWB_INVALID_PARAMETER - The value for userID_Type is invalid.  */
/*   CWB_BUFFER_OVERFLOW - Not enough room in userID buffer to      */
/*                         store the user ID.  Use *bufferSize to   */
/*                         determine the correct size.              */
/*                         No error message is logged to the        */
/*                         History Log since the caller is expected */
/*                         to recover from this error and continue. */
/*   CWBCO_SYSTEM_NOT_CONNECTED - The system of the "current user   */
/*                                ID" is not connected.             */
/*   CWBCO_SYSTEM_NOT_CONFIGURED - The system of the "default user  */
/*                                 ID" is not configured in the     */
/*                                 currently active environment.    */
/*   CWBCO_NO_USER_ID - No user ID for this system could be found,  */
/*                      not even an empty one; this indicates a     */
/*                      severe error, possibly registry corruption. */
/*   CWBCO_INTERNAL_ERROR - internal error.                         */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   If the default user ID is specified, and none was entered      */
/*   when the connection was configured, CWB_OK will be returned    */
/*   and the user ID sent back to the caller will be the empty      */
/*   string, "\0".                                                  */
/*                                                                  */
/*   The user ID retrieved will be that of the specified system     */
/*   from the currently active environment.                         */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbCO_GetUserID(
                             LPCSTR              systemName,
                             char               *userID,
                             unsigned int        userID_Type,
                             unsigned long      *bufferSize);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_GetUserIDA(
                             LPCSTR      systemName
                           , LPSTR       userID
                           , UINT        userID_Type
                           , ULONG      *bufferSize
                                      );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbCO_GetUserIDW(
                             LPCWSTR     systemName
                           , LPWSTR      userID
                           , UINT        userID_Type
                           , ULONG      *bufferSize
                                      );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbCO_GetUserID                 cwbCO_GetUserIDW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbCO_GetUserID                 cwbCO_GetUserIDA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/* API:                                                             */
/*   cwbCO_GetActiveConversations                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the number of active conversations of the system.          */
/* Parameters:                                                      */
/*   LPCSTR systemName - input                                      */
/*     Pointer to a buffer that contains the system name.           */
/* Return Codes:                                                    */
/*  The number of active conversations, if any, is returned.        */
/*  If the systemName pointer is NULL, points to an empty string,   */
/*  the system is not currently connected, or system name contains  */
/*  one or more UNICODE characters which cannot be converted,       */
/*  0 will be returned.                                             */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Since only systems configured in the currently active          */
/*   environment may be connected to, it is invalid to pass the     */
/*   name of a system not configured in the currently active        */
/*   environment; in this case, 0 is returned.                      */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
int CWB_ENTRY cwbCO_GetActiveConversations(
                                          LPCSTR systemName);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
INT CWB_ENTRY cwbCO_GetActiveConversationsA(
                                          LPCSTR systemName);
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
INT CWB_ENTRY cwbCO_GetActiveConversationsW(
                                          LPCWSTR systemName);
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbCO_GetActiveConversations    cwbCO_GetActiveConversationsW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbCO_GetActiveConversations    cwbCO_GetActiveConversationsA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_GetHostVersion                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the version and release level of the host.                 */
/*                                                                  */
/* Parameters:                                                      */
/*   LPCSTR systemName - input                                      */
/*     Pointer to a buffer that contains the system name.           */
/*   unsigned int * version - output                                */
/*     Pointer to a buffer where the version level of the system    */
/*     is returned.                                                 */
/*   unsigned int * release - output                                */
/*     Pointer to a buffer where the release level of the system    */
/*     is returned.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*  The following list shows common return values.                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWBCO_SYSTEM_NOT_CONFIGURED - The system is not configured in  */
/*                                 the currently active environment.*/
/*   CWBCO_SYSTEM_NOT_CONNECTED - The system has never been         */
/*                                connected to when using the       */
/*                                currently active environment.     */
/*   CWB_INVALID_POINTER - The pointer to the system name is NULL.  */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The host version is retrieved and saved whenever a connection  */
/*   is made to the system; this API does not go to the host to     */
/*   get it on each call.  The system must have been connected      */
/*   previously, though not necessarily at the time the API is      */
/*   called.  Host information can only be retrieved for systems    */
/*   configured in the currently active environment.                */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbCO_GetHostVersion(
                             LPCSTR         system,
                             unsigned int * version,
                             unsigned int * release );
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_GetHostVersionA(
                                               LPCSTR    system
                                             , UINT     *version
                                             , UINT     *release
                                           );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbCO_GetHostVersionW(
                                               LPCWSTR   system
                                             , UINT     *version
                                             , UINT     *release
                                           );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbCO_GetHostVersion            cwbCO_GetHostVersionW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbCO_GetHostVersion            cwbCO_GetHostVersionA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_GetNumberOfEnvironments                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the number of Client Access environments that exist.  This */
/*   includes both the active and all non-active environments.      */
/* Parameters:                                                      */
/*                                                                  */
/*   unsigned long *numberOfEnv - output                            */
/*     On output this will be set to the number of environments.    */
/*                                                                  */
/* Return Codes:                                                    */
/*  The following list shows common return values.                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_INVALID_POINTER - The numberOfEnv pointer parameter        */
/*                         is NULL.                                 */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbCO_GetNumberOfEnvironments(
                             unsigned long      *numberOfEnv);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_GetEnvironmentName                                       */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the name of the environment corresponding to the index.    */
/* Parameters:                                                      */
/*                                                                  */
/*   char *environmentName - output                                 */
/*     Pointer to a buffer that will contain the environment name.  */
/*                                                                  */
/*   unsigned long * bufferSize - input/output                      */
/*     input: Size of the buffer pointed to by *environmentName.    */
/*     output: Size of buffer needed, if the buffer provided was    */
/*             too small.                                           */
/*                                                                  */
/*   unsigned long index - input                                    */
/*     0 corresponds to the first environment.                      */
/*                                                                  */
/* Return Codes:                                                    */
/*  The following list shows common return values.                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_INVALID_POINTER - One or more pointer parameters are NULL. */
/*                         Check messages in the History Log to     */
/*                         determine which are invalid.             */
/*   CWB_BUFFER_OVERFLOW - Not enough room in output buffer to hold */
/*                         entire environment name.  Use *bufferSize*/
/*                         to determine the correct size.           */
/*                         No error message is logged to the        */
/*                         History Log since the caller is expected */
/*                         to recover from this error and continue. */
/*   CWBCO_END_OF_LIST   - The end of the environments list has     */
/*                         been reached.  No environment name was   */
/*                         returned.                                */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbCO_GetEnvironmentName(
                             char               *environmentName,
                             unsigned long      *bufferSize,
                             unsigned long       index);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_GetEnvironmentNameA(
                                      LPSTR       environmentName
                                    , ULONG      *bufferSize
                                    , ULONG       index
                                               );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbCO_GetEnvironmentNameW(
                                      LPWSTR      environmentName
                                    , ULONG      *bufferSize
                                    , ULONG       index
                                               );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbCO_GetEnvironmentName        cwbCO_GetEnvironmentNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbCO_GetEnvironmentName        cwbCO_GetEnvironmentNameA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_GetActiveEnvironment                                     */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the name of the environment currently active.              */
/* Parameters:                                                      */
/*                                                                  */
/*   char *environmentName - output                                 */
/*     Pointer to a buffer that contains the environment name.      */
/*                                                                  */
/*   unsigned long * bufferSize - input/output                      */
/*     input: Size of the buffer pointed to by *environmentName.    */
/*     output: Size of buffer needed.                               */
/*                                                                  */
/* Return Codes:                                                    */
/*  The following list shows common return values.                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_INVALID_POINTER - One or more pointer parameters are NULL. */
/*                         Check messages in the History Log to     */
/*                         determine which are NULL.                */
/*   CWB_BUFFER_OVERFLOW - Not enough room in output buffer to hold */
/*                         entire environment name.  Use *bufferSize*/
/*                         to determine the correct size.           */
/*                         No error message is logged to the        */
/*                         History Log since the caller is expected */
/*                         to recover from this error and continue. */
/*   CWBCO_NO_SUCH_ENVIRONMENT - No environments have been          */
/*                               configured, so there is no active  */
/*                               environment.                       */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbCO_GetActiveEnvironment(
                             char               *environmentName,
                             unsigned long      *bufferSize);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_GetActiveEnvironmentA(
                                         LPSTR     environmentName
                                       , ULONG    *bufferSize
                                                 );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbCO_GetActiveEnvironmentW(
                                         LPWSTR    environmentName
                                       , ULONG    *bufferSize
                                                 );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbCO_GetActiveEnvironment      cwbCO_GetActiveEnvironmentW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbCO_GetActiveEnvironment      cwbCO_GetActiveEnvironmentA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_CanConnectNewSystem                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Indicates whether or not the user can dynamically connect to   */
/*   a system.  If not, cwbCO_CreateSystem will fail if the         */
/*   system being connected to does not exist in the active         */
/*   environment.                                                   */
/*                                                                  */
/* Parameters:                                                      */
/*   None                                                           */
/*                                                                  */
/* Return Codes:                                                    */
/*  The following list shows common return values.                  */
/*   CWB_TRUE - Can connect to systems not already configured       */
/*   CWB_FALSE - Cannot connect to systems not already configured   */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
cwb_Boolean CWB_ENTRY cwbCO_CanConnectNewSystem();


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_CanSetActiveEnvironment                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   Indicates whether or not the user can set an environment to be */
/*   the active environment.                                        */
/*                                                                  */
/* Parameters:                                                      */
/*   None                                                           */
/*                                                                  */
/* Return Codes:                                                    */
/*  The following list shows common return values.                  */
/*   CWB_TRUE - Can set the active environment                      */
/*   CWB_FALSE - Cannot set the active environment                  */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
cwb_Boolean CWB_ENTRY cwbCO_CanSetActiveEnvironment();


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_CanModifyEnvironmentList                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   Indicates whether or not the user can create/remove/rename     */
/*   environments.                                                  */
/*                                                                  */
/* Parameters:                                                      */
/*   None                                                           */
/*                                                                  */
/* Return Codes:                                                    */
/*  The following list shows common return values.                  */
/*   CWB_TRUE - Can create/remove/rename/delete environments        */
/*   CWB_FALSE - Cannot create/remove/rename/delete environments    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API indicates whether environments can be manipulated.    */
/*   To see if systems within an environment may be manipulated,    */
/*   use the cwbCO_CanModifySystemList and                          */
/*   cwbCO_CanModifySystemListEnv APIs.                             */
/*                                                                  */
/********************************************************************/
cwb_Boolean CWB_ENTRY cwbCO_CanModifyEnvironmentList();


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_CanModifySystemList                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Indicates whether or not the user can add/remove/delete        */
/*   systems within the active environment.  Note that systems      */
/*  "suggested" by the administrator via policies cannot be removed.*/
/*                                                                  */
/* Parameters:                                                      */
/*   None                                                           */
/*                                                                  */
/* Return Codes:                                                    */
/*  The following list shows common return values.                  */
/*   CWB_TRUE - Can modify system list                              */
/*   CWB_FALSE - Cannot modify system list                          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API indicates whether systems within an environment can   */
/*   be manipulated.  To see if environments can be manipulated     */
/*   see the cwbCO_CanModifyEnvironmentList API.                    */
/*                                                                  */
/********************************************************************/
cwb_Boolean CWB_ENTRY cwbCO_CanModifySystemList();


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_CanModifySystemListEnv                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Indicates whether or not the user can add/remove/delete        */
/*   systems within an input environment.  Note that systems        */
/*  "suggested" by the administrator via policies cannot be removed.*/
/*                                                                  */
/* Parameters:                                                      */
/*   LPCSTR pEnvironment - input                                    */
/*     Pointer to a buffer that contains the environment name.      */
/*     If pEnvironment is NULL, or if it points to an empty string, */
/*     the active environment is assumed.                           */
/*                                                                  */
/* Return Codes:                                                    */
/*  The following list shows common return values.                  */
/*   CWB_TRUE - Can modify system list                              */
/*   CWB_FALSE - Cannot modify system list, error occurred.         */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API indicates whether systems within an environment can   */
/*   be manipulated.  To see if environments can be manipulated     */
/*   see the cwbCO_CanModifyEnvironmentList API.                    */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
cwb_Boolean CWB_ENTRY cwbCO_CanModifySystemListEnv(
                             char               *environmentName);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
cwb_Boolean CWB_ENTRY cwbCO_CanModifySystemListEnvA(
                                                           LPSTR  environmentName);
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
cwb_Boolean CWB_ENTRY cwbCO_CanModifySystemListEnvW(
                                                           LPWSTR environmentName);
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbCO_CanModifySystemListEnv        cwbCO_CanModifySystemListEnvW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbCO_CanModifySystemListEnv        cwbCO_CanModifySystemListEnvA
#endif // of UNICODE/ANSI selection




#if defined( __cplusplus )
}
#endif

#endif /* _CWBCO_H_ */
