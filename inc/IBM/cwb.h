/*                                                                   */
/* 5722-XE1                                                          */
/* (C) Copyright IBM Corp. 1995,2005                                 */
/* All rights reserved.                                              */
/* US Government Users Restricted Rights -                           */
/* Use, duplication or disclosure restricted                         */
/* by GSA ADP Schedule Contract with IBM Corp.                       */
/*                                                                   */
/* Licensed Materials-Property of IBM                                */
/*                                                                   */

/*********************************************************************/
/*                                                                   */
/* Module:                                                           */
/*   CWB.H                                                           */
/*                                                                   */
/* Purpose:                                                          */
/*   Common declarations for Client Access/400 APIs                  */
/*                                                                   */
/* Usage Notes:                                                      */
/*                                                                   */
/*********************************************************************/

/*********************************************************************/
/* Prevent multiple includes                                         */
/*********************************************************************/
#if !defined( _CWB_H_ )
  #define     _CWB_H_

/*********************************************************************/
/* Enable multiple compilers                                         */
/*********************************************************************/
#include "cwbport.h"

/*********************************************************************/
/* Common definitions                                                */
/*********************************************************************/

#define CWB_ENTRY _System

/*********************************************************************/
/* Note that basetsd.h included must contain the declaractions of    */
/* the polymorphic types that are used to support writing of code    */
/* that is common between Win32 and Win64.  Older versions of that   */
/* file may not include these declarations. These types are such as: */
/*   ULONG_PTR                                                       */
/*   INT_PTR                                                         */
/*   DWORD_PTR                                                       */
/* If, when you compile your application, an error occurs below      */
/* because ULONG_PTR is not defined, you must install a recent       */
/* version of the Microsoft Platform SDK (or equivalent) and         */
/* configure the search order for include files so that the SDK      */
/* path comes before the compiler path.                              */
/*********************************************************************/
#include <basetsd.h>

typedef ULONG_PTR cwb_Handle;

typedef cwb_Handle cwbSV_ErrHandle;

typedef unsigned long cwb_Boolean;

#if defined(__cplusplus)
  const cwb_Boolean CWB_FALSE = (0 == 1);
  const cwb_Boolean CWB_TRUE  = (1 == 1);
#else
  #define CWB_FALSE      (0 == 1)
  #define CWB_TRUE       (1 == 1)
#endif

/*********************************************************************/
/* Client Access/400 return codes fall into the following            */
/* categories:                                                       */
/* - Global return codes corresponding to operating system errors    */
/* - Global return codes unique to Client Access/400                 */
/* - Specific return codes for each Client Access/400 function       */
/*                                                                   */
/* The global return codes are defined in this file.  The function   */
/* specific return codes are defined in the function specific        */
/* header files.                                                     */
/*********************************************************************/

/*********************************************************************/
/* Global return codes corresponding to operating system errors      */
/*********************************************************************/

  #define CWB_OK                         0
  #define CWB_INVALID_FUNCTION           1
  #define CWB_FILE_NOT_FOUND             2
  #define CWB_PATH_NOT_FOUND             3
  #define CWB_TOO_MANY_OPEN_FILES        4
  #define CWB_ACCESS_DENIED              5
  #define CWB_INVALID_HANDLE             6
  #define CWB_NOT_ENOUGH_MEMORY          8
  #define CWB_INVALID_DRIVE             15
  #define CWB_NO_MORE_FILES             18
  #define CWB_DRIVE_NOT_READY           21
  #define CWB_GENERAL_FAILURE           31
  #define CWB_SHARING_VIOLATION         32
  #define CWB_LOCK_VIOLATION            33
  #define CWB_END_OF_FILE               38
  #define CWB_NOT_SUPPORTED             50
  #define CWB_BAD_NETWORK_PATH          53
  #define CWB_NETWORK_BUSY              54
  #define CWB_DEVICE_NOT_EXIST          55
  #define CWB_UNEXPECTED_NETWORK_ERROR  59
  #define CWB_NETWORK_ACCESS_DENIED     65
  #define CWB_FILE_EXISTS               80
  #define CWB_ALREADY_ASSIGNED          85
  #define CWB_INVALID_PARAMETER         87
  #define CWB_NETWORK_WRITE_FAULT       88
  #define CWB_OPEN_FAILED              110
  #define CWB_BUFFER_OVERFLOW          111
  #define CWB_DISK_FULL                112
  #define CWB_PROTECTION_VIOLATION     115
  #define CWB_INVALID_LEVEL            124
  #define CWB_BUSY_DRIVE               142
  #define CWB_INVALID_FSD_NAME         252
  #define CWB_INVALID_PATH             253

/*********************************************************************/
/* Global return codes unique to Client Access/400                   */
/*********************************************************************/
  #define CWB_START   4000
  #define CWB_LAST    5999

  #define CWB_USER_CANCELLED_COMMAND            (CWB_START)
  #define CWB_CONFIG_ERROR                      (CWB_START+1)
  #define CWB_LICENSE_ERROR                     (CWB_START+2)
  #define CWB_PROD_OR_COMP_NOT_SET              (CWB_START+3)
  #define CWB_SECURITY_ERROR                    (CWB_START+4)
  #define CWB_GLOBAL_CFG_FAILED                 (CWB_START+5)
  #define CWB_PROD_RETRIEVE_FAILED              (CWB_START+6)
  #define CWB_COMP_RETRIEVE_FAILED              (CWB_START+7)
  #define CWB_COMP_CFG_FAILED                   (CWB_START+8)
  #define CWB_COMP_FIX_LEVEL_UPDATE_FAILED      (CWB_START+9)
  #define CWB_INVALID_API_HANDLE                (CWB_START+10)
  #define CWB_INVALID_API_PARAMETER             (CWB_START+11)
  #define CWB_HOST_NOT_FOUND                    (CWB_START+12)
  #define CWB_NOT_COMPATIBLE                    (CWB_START+13)
  #define CWB_INVALID_POINTER                   (CWB_START+14)
  #define CWB_SERVER_PROGRAM_NOT_FOUND          (CWB_START+15)
  #define CWB_API_ERROR                         (CWB_START+16)
  #define CWB_CA_NOT_STARTED                    (CWB_START+17)
  #define CWB_FILE_IO_ERROR                     (CWB_START+18)
  #define CWB_COMMUNICATIONS_ERROR              (CWB_START+19)
  #define CWB_RUNTIME_CONSTRUCTOR_FAILED        (CWB_START+20)
  #define CWB_DIAGNOSTIC                        (CWB_START+21)
  #define CWB_COMM_VERSION_ERROR                (CWB_START+22)
  #define CWB_NO_VIEWER                         (CWB_START+23)
  #define CWB_MODULE_NOT_LOADABLE               (CWB_START+24)
  #define CWB_ALREADY_SETUP                     (CWB_START+25)
  #define CWB_CANNOT_START_PROCESS              (CWB_START+26)
  #define CWB_NON_REPRESENTABLE_UNICODE_CHAR    (CWB_START+27)
  #define CWB_ENTRY_NOT_FOUND                   (CWB_START+28)


/*********************************************************************/
/* Global return codes unique to Client Access/400 that are new      */
/*   as of first release of Client Access Express, start at 8000     */
/*********************************************************************/
  #define CWB_EXPRESSBASE       (8000L)

/*

  Security Errors  (8000 - 8299)

*/

  #define CWB_EXPRESS_SEC_BASE      (CWB_EXPRESSBASE)
  #define CWB_EXPRESS_SEC_END       (CWB_EXPRESS_SEC_BASE+299L)

  #define CWB_UNKNOWN_USERID                    (CWB_EXPRESS_SEC_BASE+1L)
  #define CWB_WRONG_PASSWORD                    (CWB_EXPRESS_SEC_BASE+2L)
  #define CWB_PASSWORD_EXPIRED                  (CWB_EXPRESS_SEC_BASE+3L)
  #define CWB_INVALID_PASSWORD                  (CWB_EXPRESS_SEC_BASE+4L)
  #define CWB_PASSWORD_TO_EXPIRE                (CWB_EXPRESS_SEC_BASE+5L)
  #define CWB_INCORRECT_DATA_FORMAT             (CWB_EXPRESS_SEC_BASE+6L)
  #define CWB_GENERAL_SECURITY_ERROR            (CWB_EXPRESS_SEC_BASE+7L)
  #define CWB_USER_PROFILE_DISABLED             (CWB_EXPRESS_SEC_BASE+11L)
  #define CWB_USER_CANCELLED                    (CWB_EXPRESS_SEC_BASE+13L)
  #define CWB_INVALID_SYSNAME                   (CWB_EXPRESS_SEC_BASE+14L)
  #define CWB_INVALID_USERID                    (CWB_EXPRESS_SEC_BASE+15L)
  #define CWB_LIMITED_CAPABILITIES_USERID       (CWB_EXPRESS_SEC_BASE+16L)
  #define CWB_WINDOWS_USERID_NOT_FOUND          (CWB_EXPRESS_SEC_BASE+17L)
  #define CWB_WINDOWS_PASSWORD_NOT_FOUND        (CWB_EXPRESS_SEC_BASE+18L)
  #define CWB_INVALID_TP_ON_HOST                (CWB_EXPRESS_SEC_BASE+19L)
  #define CWB_NOT_LOGGED_ON                     (CWB_EXPRESS_SEC_BASE+22L)
  #define CWB_EXIT_PGM_ERROR                    (CWB_EXPRESS_SEC_BASE+26L)
  #define CWB_EXIT_PGM_DENIED_REQUEST           (CWB_EXPRESS_SEC_BASE+27L)
  #define CWB_TIMESTAMPS_NOT_SET                (CWB_EXPRESS_SEC_BASE+50L)
  #define CWB_KERB_CLIENT_CREDENTIALS_NOT_FOUND (CWB_EXPRESS_SEC_BASE+51L)
  #define CWB_KERB_SERVICE_TICKET_NOT_FOUND     (CWB_EXPRESS_SEC_BASE+52L)
  #define CWB_KERB_SERVER_CANNOT_BE_CONTACTED   (CWB_EXPRESS_SEC_BASE+53L)
  #define CWB_KERB_UNSUPPORTED_BY_HOST          (CWB_EXPRESS_SEC_BASE+54L)
  #define CWB_KERB_NOT_AVAILABLE                (CWB_EXPRESS_SEC_BASE+55L)
  #define CWB_KERB_SERVER_NOT_CONFIGURED        (CWB_EXPRESS_SEC_BASE+56L)
  #define CWB_KERB_CREDENTIALS_NOT_VALID        (CWB_EXPRESS_SEC_BASE+57L)
  #define CWB_KERB_MAPPED_USERID_FAILURE        (CWB_EXPRESS_SEC_BASE+58L)
  #define CWB_KERB_MAPPED_USERID_SUCCESS        (CWB_EXPRESS_SEC_BASE+59L)
  #define CWB_PROFILE_TOKEN_INVALID             (CWB_EXPRESS_SEC_BASE+70L)
  #define CWB_PROFILE_TOKEN_MAXIMUM             (CWB_EXPRESS_SEC_BASE+71L)
  #define CWB_PROFILE_TOKEN_NOT_REGENERABLE     (CWB_EXPRESS_SEC_BASE+72L)
  #define CWB_PW_TOO_LONG                       (CWB_EXPRESS_SEC_BASE+257L)
  #define CWB_PW_TOO_SHORT                      (CWB_EXPRESS_SEC_BASE+258L)
  #define CWB_PW_REPEAT_CHARACTER               (CWB_EXPRESS_SEC_BASE+259L)
  #define CWB_PW_ADJACENT_DIGITS                (CWB_EXPRESS_SEC_BASE+260L)
  #define CWB_PW_CONSECUTIVE_CHARS              (CWB_EXPRESS_SEC_BASE+261L)
  #define CWB_PW_PREVIOUSLY_USED                (CWB_EXPRESS_SEC_BASE+262L)
  #define CWB_PW_DISALLOWED_CHAR                (CWB_EXPRESS_SEC_BASE+263L)
  #define CWB_PW_NEED_NUMERIC                   (CWB_EXPRESS_SEC_BASE+264L)
  #define CWB_PW_MATCHES_OLD                    (CWB_EXPRESS_SEC_BASE+266L)
  #define CWB_PW_NOT_ALLOWED                    (CWB_EXPRESS_SEC_BASE+267L)
  #define CWB_PW_CONTAINS_USERID                (CWB_EXPRESS_SEC_BASE+268L)
  #define CWB_PW_LAST_INVALID_PWD               (CWB_EXPRESS_SEC_BASE+270L)
  #define CWB_PW_STAR_NONE                      (CWB_EXPRESS_SEC_BASE+271L)
  #define CWB_PW_QPWDVLDPGM                     (CWB_EXPRESS_SEC_BASE+272L)

/*

  Communications Errors (8400 - 8499)

*/

  #define CWB_EXPRESS_COMM_BASE      (CWB_EXPRESSBASE+400L)
  #define CWB_EXPRESS_COMM_END       (CWB_EXPRESS_COMM_BASE+99L)

  #define CWB_INV_AFTER_SIGNON                  (CWB_EXPRESS_COMM_BASE)
  #define CWB_INV_WHEN_CONNECTED                (CWB_EXPRESS_COMM_BASE+1L)
  #define CWB_INV_BEFORE_VALIDATE               (CWB_EXPRESS_COMM_BASE+2L)
  #define CWB_SECURE_SOCKETS_NOTAVAIL           (CWB_EXPRESS_COMM_BASE+3L)
  #define CWB_RESERVED1                         (CWB_EXPRESS_COMM_BASE+4L)
  #define CWB_RECEIVE_ERROR                     (CWB_EXPRESS_COMM_BASE+5L)
  #define CWB_SERVICE_NAME_ERROR                (CWB_EXPRESS_COMM_BASE+6L)
  #define CWB_GETPORT_ERROR                     (CWB_EXPRESS_COMM_BASE+7L)
  #define CWB_SUCCESS_WARNING                   (CWB_EXPRESS_COMM_BASE+8L)
  #define CWB_NOT_CONNECTED                     (CWB_EXPRESS_COMM_BASE+9L)
  #define CWB_DEFAULT_HOST_CCSID_USED           (CWB_EXPRESS_COMM_BASE+10L)
  #define CWB_USER_TIMEOUT                      (CWB_EXPRESS_COMM_BASE+11L)
  #define CWB_SSL_JAVA_ERROR                    (CWB_EXPRESS_COMM_BASE+12L)
  #define CWB_USER_TIMEOUT_SENDRCV              (CWB_EXPRESS_COMM_BASE+13L)
  #define CWB_FIPS_UNAVAILABLE                  (CWB_EXPRESS_COMM_BASE+14L)

/*

  Configuration Errors  (8500 - 8599)

*/

  #define CWB_EXPRESS_CFG_BASE       (CWB_EXPRESSBASE+500L)
  #define CWB_EXPRESS_CFG_END        (CWB_EXPRESS_CFG_BASE+99L)

  #define CWB_RESTRICTED_BY_POLICY              (CWB_EXPRESS_CFG_BASE)
  #define CWB_POLICY_MODIFY_MANDATED_ENV        (CWB_EXPRESS_CFG_BASE+1L)
  #define CWB_POLICY_MODIFY_CURRENT_ENV         (CWB_EXPRESS_CFG_BASE+2L)
  #define CWB_POLICY_MODIFY_ENV_LIST            (CWB_EXPRESS_CFG_BASE+3L)
  #define CWB_SYSTEM_NOT_FOUND                  (CWB_EXPRESS_CFG_BASE+4L)
  #define CWB_ENVIRONMENT_NOT_FOUND             (CWB_EXPRESS_CFG_BASE+5L)
  #define CWB_ENVIRONMENT_EXISTS                (CWB_EXPRESS_CFG_BASE+6L)
  #define CWB_SYSTEM_EXISTS                     (CWB_EXPRESS_CFG_BASE+7L)
  #define CWB_NO_SYSTEMS_CONFIGURED             (CWB_EXPRESS_CFG_BASE+8L)
  #define CWB_CONFIGERR_RESERVED_START          (CWB_EXPRESS_CFG_BASE+80L)
  #define CWB_CONFIGERR_RESERVED_END            (CWB_EXPRESS_CFG_BASE+99L)

/*

  Automation Object Errors  (8600 - 8699)

*/

  #define CWB_INVALID_METHOD_PARM               (CWB_EXPRESSBASE+600L)
  #define CWB_INVALID_PROPERTY_PARM             (CWB_EXPRESSBASE+601L)
  #define CWB_INVALID_PROPERTY_VALUE            (CWB_EXPRESSBASE+602L)
  #define CWB_OBJECT_NOT_INITIALIZED            (CWB_EXPRESSBASE+603L)
  #define CWB_OBJECT_ALREADY_INITIALIZED        (CWB_EXPRESSBASE+604L)
  #define CWB_INVALID_DQ_ORDER                  (CWB_EXPRESSBASE+605L)
  #define CWB_DATA_TRANSFER_REQUIRED            (CWB_EXPRESSBASE+606L)
  #define CWB_UNSUPPORTED_XFER_REQUEST          (CWB_EXPRESSBASE+607L)
  #define CWB_ASYNC_REQUEST_ACTIVE              (CWB_EXPRESSBASE+608L)
  #define CWB_REQUEST_TIMED_OUT                 (CWB_EXPRESSBASE+609L)
  #define CWB_CANNOT_SET_PROP_NOW               (CWB_EXPRESSBASE+610L)
  #define CWB_OBJ_STATE_NO_LONGER_VALID         (CWB_EXPRESSBASE+611L)


  #define CWB_UNSUPPORTED_FUNCTION              (CWB_EXPRESSBASE+998L)
  #define CWB_INTERNAL_ERROR                    (CWB_EXPRESSBASE+999L)

/*

  10000 - 11004 -- WINSOCK errors (see winsock.h / winsock2.h)

*/

  #define CWB_SOCKBASE          (10000L)

  #define CWB_TOO_MANY_OPEN_SOCKETS                     (CWB_SOCKBASE+24L)
  #define CWB_RESOURCE_TEMPORARILY_UNAVAILABLE          (CWB_SOCKBASE+35L)
  #define CWB_SOCKET_OPERATION_ON_NON_SOCKET            (CWB_SOCKBASE+38L)
  #define CWB_PROTOCOL_NOT_INSTALLED                    (CWB_SOCKBASE+47L)
  #define CWB_NETWORK_IS_DOWN                           (CWB_SOCKBASE+50L)
  #define CWB_NETWORK_IS_UNREACHABLE                    (CWB_SOCKBASE+51L)
  #define CWB_NETWORK_DROPPED_CONNECTION_ON_RESET       (CWB_SOCKBASE+52L)
  #define CWB_SOFTWARE_CAUSED_CONNECTION_ABORT          (CWB_SOCKBASE+53L)
  #define CWB_CONNECTION_RESET_BY_PEER                  (CWB_SOCKBASE+54L)
  #define CWB_NO_BUFFER_SPACE_AVAILABLE                 (CWB_SOCKBASE+55L)
  #define CWB_SOCKET_IS_NOT_CONNECTED                   (CWB_SOCKBASE+57L)
  #define CWB_CANNOT_SEND_AFTER_SOCKET_SHUTDOWN         (CWB_SOCKBASE+58L)
  #define CWB_CONNECTION_TIMED_OUT                      (CWB_SOCKBASE+60L)
  #define CWB_CONNECTION_REFUSED                        (CWB_SOCKBASE+61L)
  #define CWB_HOST_IS_DOWN                              (CWB_SOCKBASE+64L)
  #define CWB_NO_ROUTE_TO_HOST                          (CWB_SOCKBASE+65L)
  #define CWB_NETWORK_SUBSYSTEM_IS_UNAVAILABLE          (CWB_SOCKBASE+91L)
  #define CWB_WINSOCK_VERSION_NOT_SUPPORTED             (CWB_SOCKBASE+92L)
  #define CWB_HOST_DEFINITELY_NOT_FOUND                 (CWB_SOCKBASE+1001L)
  #define CWB_HOST_NOT_FOUND_BUT_WE_ARE_NOT_SURE        (CWB_SOCKBASE+1002L)
  #define CWB_VALID_NAME_BUT_NO_DATA_RECORD             (CWB_SOCKBASE+1004L)

/*

  20000 - 20999 -- SSL return codes
  NOTE: These are obsolete in V5R1M0.
  NOTE: In V5R1M0 and beyond, SSL return codes will only be documented in
        the online Express User's Guide under CWBCO1034.

*/

  #define CWB_SSLBASE1          (20000L)
  #define CWB_SSLEND1           (CWB_SSLBASE1+999L)

  #define CWB_SSL_KEYFILE_IO_ERROR                      (CWB_SSLBASE1+1)
  #define CWB_SSL_KEYFILE_OPEN_FAILED                   (CWB_SSLBASE1+2)
  #define CWB_SSL_KEYFILE_BAD_FORMAT                    (CWB_SSLBASE1+3)
  #define CWB_SSL_KEYFILE_BAD_PASSWORD                  (CWB_SSLBASE1+4)
  #define CWB_SSL_KEYFILE_BAD_MALLOC                    (CWB_SSLBASE1+5)
  #define CWB_SSL_KEYFILE_NOTHING_TO_WRITE              (CWB_SSLBASE1+6)
  #define CWB_SSL_KEYFILE_WRITE_FAILED                  (CWB_SSLBASE1+7)
  #define CWB_SSL_KEYFILE_NOT_FOUND                     (CWB_SSLBASE1+8)
  #define CWB_SSL_KEYFILE_BAD_DNAME                     (CWB_SSLBASE1+9)
  #define CWB_SSL_KEYFILE_BAD_KEY                       (CWB_SSLBASE1+10)
  #define CWB_SSL_KEYFILE_KEY_EXISTS                    (CWB_SSLBASE1+11)
  #define CWB_SSL_KEYFILE_BAD_LABEL                     (CWB_SSLBASE1+12)
  #define CWB_SSL_KEYFILE_DUPLICATE_NAME                (CWB_SSLBASE1+13)
  #define CWB_SSL_KEYFILE_DUPLICATE_KEY                 (CWB_SSLBASE1+14)
  #define CWB_SSL_KEYFILE_DUPLICATE_LABEL               (CWB_SSLBASE1+15)
  #define CWB_SSL_BAD_FORMAT_OR_INVALID_PW              (CWB_SSLBASE1+16)
  #define CWB_SSL_WARNING_INVALID_SERVER_CERT           (CWB_SSLBASE1+98)
  #define CWB_SSL_WARNING_INVALID_SERVER_PRIV_KEY       (CWB_SSLBASE1+99)
  #define CWB_SSL_ERR_INIT_PARM_NOT_VALID               (CWB_SSLBASE1+100)
  #define CWB_SSL_INIT_SEC_TYPE_NOT_VALID               (CWB_SSLBASE1+102)
  #define CWB_SSL_INIT_V2_TIMEOUT_NOT_VALID             (CWB_SSLBASE1+103)
  #define CWB_SSL_INIT_V3_TIMEOUT_NOT_VALID             (CWB_SSLBASE1+104)
  #define CWB_SSL_KEYFILE_CERT_EXPIRED                  (CWB_SSLBASE1+105)

/*

  25000 - 25999 -- More SSL return codes
  NOTE: These are obsolete in V5R1M0.
  NOTE: In V5R1M0 and beyond, SSL return codes will only be documented in
        the online Express User's Guide under CWBCO1034.

*/

  #define CWB_SSLBASE2          (CWB_SSLBASE1+5000L)
  #define CWB_SSLEND2           (CWB_SSLBASE2+999L)

  #define CWB_SSL_ERROR_NO_CIPHERS                      (CWB_SSLBASE2+1)
  #define CWB_SSL_ERROR_NO_CERTIFICATE                  (CWB_SSLBASE2+2)
  #define CWB_SSL_ERROR_BAD_CERTIFICATE                 (CWB_SSLBASE2+4)
  #define CWB_SSL_ERROR_UNSUPPORTED_CERTIFICATE_TYPE    (CWB_SSLBASE2+6)
  #define CWB_SSL_ERROR_IO                              (CWB_SSLBASE2+10)
  #define CWB_SSL_ERROR_BAD_MESSAGE                     (CWB_SSLBASE2+11)
  #define CWB_SSL_ERROR_BAD_MAC                         (CWB_SSLBASE2+12)
  #define CWB_SSL_ERROR_UNSUPPORTED                     (CWB_SSLBASE2+13)
  #define CWB_SSL_ERROR_BAD_CERT_SIG                    (CWB_SSLBASE2+14)
  #define CWB_SSL_ERROR_BAD_CERT                        (CWB_SSLBASE2+15)
  #define CWB_SSL_ERROR_BAD_PEER                        (CWB_SSLBASE2+16)
  #define CWB_SSL_ERROR_PERMISSION_DENIED               (CWB_SSLBASE2+17)
  #define CWB_SSL_ERROR_SELF_SIGNED                     (CWB_SSLBASE2+18)
  #define CWB_SSL_ERROR_BAD_MALLOC                      (CWB_SSLBASE2+20)
  #define CWB_SSL_ERROR_BAD_STATE                       (CWB_SSLBASE2+21)
  #define CWB_SSL_ERROR_SOCKET_CLOSED                   (CWB_SSLBASE2+22)
  #define CWB_SSL_ERROR_INITIALIZATION_FAILED           (CWB_SSLBASE2+23)
  #define CWB_SSL_ERROR_HANDLE_CREATION_FAILED          (CWB_SSLBASE2+24)
  #define CWB_SSL_ERROR_BAD_DATE                        (CWB_SSLBASE2+25)
  #define CWB_SSL_ERROR_BAD_KEY_LEN_FOR_EXPORT          (CWB_SSLBASE2+26)
  #define CWB_SSL_ERROR_NO_PRIVATE_KEY                  (CWB_SSLBASE2+27)
  #define CWB_SSL_BAD_PARAMETER                         (CWB_SSLBASE2+28)
  #define CWB_SSL_ERROR_INTERNAL                        (CWB_SSLBASE2+29)
  #define CWB_SSL_ERROR_WOULD_BLOCK                     (CWB_SSLBASE2+30)
  #define CWB_SSL_ERROR_LOAD_GSKLIB                     (CWB_SSLBASE2+31)
  #define CWB_SSL_SOC_BAD_V2_CIPHER                     (CWB_SSLBASE2+40)
  #define CWB_SSL_SOC_BAD_V3_CIPHER                     (CWB_SSLBASE2+41)
  #define CWB_SSL_SOC_BAD_SEC_TYPE                      (CWB_SSLBASE2+42)
  #define CWB_SSL_SOC_NO_READ_FUNCTION                  (CWB_SSLBASE2+43)
  #define CWB_SSL_SOC_NO_WRITE_FUNCTION                 (CWB_SSLBASE2+44)
  #define CWB_SSL_ERROR_NOT_SERVER                      (CWB_SSLBASE2+50)
  #define CWB_SSL_ERROR_NOT_SSLV3                       (CWB_SSLBASE2+51)
  #define CWB_SSL_ERROR_NOT_SSLV3_CLIENT                (CWB_SSLBASE2+52)
  #define CWB_SSL_ERROR_UNKNOWN_ERROR                   (CWB_SSLBASE2+99)
  #define CWB_SSL_ERROR_BAD_BUFFER_SIZE                 (CWB_SSLBASE2+100)
  #define CWB_SSL_ERROR_BAD_SSL_HANDLE                  (CWB_SSLBASE2+101)
  #define CWB_SSL_ERROR_TIMEOUT                         (CWB_SSLBASE2+102)

/*

  30000 - 30999 -- internal return codes

*/

  #define CWB_RESERVED2_BASE    (30000L)
  #define CWB_RESERVED2_END     (CWB_RESERVED2_BASE+999L)


#endif /* _CWB_H_  */
