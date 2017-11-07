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
/*   CWBCOSYS.H                                                     */
/*                                                                  */
/* Purpose:                                                         */
/*   The functions listed in this file can be used to get, use,     */
/*   and delete an AS/400 System Object.  A system object is        */
/*   needed by various other Client Access APIs.  It holds          */
/*   information related to connecting to and validating security   */
/*   (user ID and password) on an AS/400 system.  Attributes of the */
/*   system object and their defaults are listed in the comments    */
/*   associated with the cwbCO_CreateSystem() declaration.          */
/*                                                                  */
/*   The APIs can be broken down into four groups:                  */
/*                                                                  */
/*   The following APIs can be used to create and delete a system   */
/*   object:                                                        */
/*     cwbCO_CreateSystem()                                         */
/*     cwbCO_CreateSystemA()                                        */
/*     cwbCO_CreateSystemW()                                        */
/*     cwbCO_CreateSystemLike()                                     */
/*     cwbCO_CreateSystemLikeA()                                    */
/*     cwbCO_CreateSystemLikeW()                                    */
/*     cwbCO_DeleteSystem()                                         */
/*                                                                  */
/*   The following APIs are related to connecting to and            */
/*   disconnecting from the AS/400 system, and related behavior:    */
/*     cwbCO_Connect()                                              */
/*     cwbCO_Verify()                                               */
/*     cwbCO_Disconnect()                                           */
/*     cwbCO_IsConnected()                                          */
/*     cwbCO_SetPersistenceMode()                                   */
/*     cwbCO_GetPersistenceMode()                                   */
/*     cwbCO_SetConnectTimeout()                                    */
/*     cwbCO_GetConnectTimeout()                                    */
/*                                                                  */
/*   The following APIs deal with security validation and data:     */
/*     cwbCO_SetUserIDEx()                                          */
/*     cwbCO_SetUserIDExA()                                         */
/*     cwbCO_SetUserIDExW()                                         */
/*     cwbCO_GetUserIDEx()                                          */
/*     cwbCO_GetUserIDExA()                                         */
/*     cwbCO_GetUserIDExW()                                         */
/*     cwbCO_SetPassword()                                          */
/*     cwbCO_SetPasswordA()                                         */
/*     cwbCO_SetPasswordW()                                         */
/*     cwbCO_SetValidateMode()                                      */
/*     cwbCO_GetValidateMode()                                      */
/*     cwbCO_SetDefaultUserMode()                                   */
/*     cwbCO_GetDefaultUserMode()                                   */
/*     cwbCO_SetPromptMode()                                        */
/*     cwbCO_GetPromptMode()                                        */
/*     cwbCO_SetWindowHandle()                                      */
/*     cwbCO_GetWindowHandle()                                      */
/*     cwbCO_Signon()                                               */
/*     cwbCO_HasSignedOn()                                          */
/*     cwbCO_VerifyUserIDPassword()                                 */
/*     cwbCO_VerifyUserIDPasswordA()                                */
/*     cwbCO_VerifyUserIDPasswordW()                                */
/*     cwbCO_GetSignonDate()                                        */
/*     cwbCO_GetPrevSignonDate()                                    */
/*     cwbCO_GetPasswordExpireDate()                                */
/*     cwbCO_GetFailedSignons()                                     */
/*     cwbCO_ChangePassword()                                       */
/*     cwbCO_ChangePasswordA()                                      */
/*     cwbCO_ChangePasswordW()                                      */
/*                                                                  */
/*   The following APIs can be used to get and set other            */
/*   system object attributes, or to see if they can be set         */
/*   (i.e. if they are restricted by policies):                     */
/*     cwbCO_GetSystemName()                                        */
/*     cwbCO_GetSystemNameA()                                       */
/*     cwbCO_GetSystemNameW()                                       */
/*     cwbCO_GetDescription()                                       */
/*     cwbCO_GetDescriptionA()                                      */
/*     cwbCO_GetDescriptionW()                                      */
/*     cwbCO_UseSecureSockets()                                     */
/*     cwbCO_IsSecureSockets()                                      */
/*     cwbCO_SetPortLookupMode()                                    */
/*     cwbCO_GetPortLookupMode()                                    */
/*     cwbCO_SetIPAddressLookupMode()                               */
/*     cwbCO_GetIPAddressLookupMode()                               */
/*     cwbCO_SetIPAddress()                                         */
/*     cwbCO_SetIPAddressA()                                        */
/*     cwbCO_SetIPAddressW()                                        */
/*     cwbCO_GetIPAddress()                                         */
/*     cwbCO_GetIPAddressA()                                        */
/*     cwbCO_GetIPAddressW()                                        */
/*     cwbCO_CanModifyDefaultUserMode()                             */
/*     cwbCO_CanModifyIPAddressLookupMode()                         */
/*     cwbCO_CanModifyIPAddress()                                   */
/*     cwbCO_CanModifyPortLookupMode()                              */
/*     cwbCO_CanModifyPersistenceMode()                             */
/*     cwbCO_CanModifyUseSecureSockets()                            */
/*     cwbCO_GetHostCCSID()                                         */
/*     cwbCO_GetHostVersionEx()                                     */
/*                                                                  */
/* Usage Notes:                                                     */
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
#if !defined( _CWBCOSYS_H_ )
  #define     _CWBCOSYS_H_

#include <windows.h>

/* Common Client Access/400 API include */
#include "cwb.h"


/*  If defined, the following flags inhibit definition
 *     of the indicated items.
 *
 *  NOCWBCOSYSAPI     - cwbCO System APIs
 */


/*------------------------------------------------------------------*/
/* TYPEDEFS:                                                        */
/*------------------------------------------------------------------*/
typedef cwb_Handle cwbCO_SysHandle;

typedef ULONG cwbCO_Service;

typedef ULONG cwbCO_PromptMode;
typedef ULONG cwbCO_ValidateMode;
typedef ULONG cwbCO_DefaultUserMode;
typedef ULONG cwbCO_IPAddressLookupMode;
typedef ULONG cwbCO_PortLookupMode;
typedef ULONG cwbCO_PersistenceMode;

#include "cwbpack1.h"

typedef struct  _cwb_DateTime
{
  USHORT year;
  UCHAR  month;
  UCHAR  day;
  UCHAR  hour;
  UCHAR  minute;
  UCHAR  second;
  UCHAR  mseconds;
}  cwb_DateTime;

#include "cwbpack0.h"


/*------------------------------------------------------------------*/
/* DEFINES: for cwbCO_Service                                       */
/*------------------------------------------------------------------*/
#define CWBCO_SERVICE_CENTRAL           (1)
#define CWBCO_SERVICE_NETFILE           (2)
#define CWBCO_SERVICE_NETPRINT          (3)
#define CWBCO_SERVICE_DATABASE          (4)
#define CWBCO_SERVICE_ODBC              (5)
#define CWBCO_SERVICE_DATAQUEUES        (6)
#define CWBCO_SERVICE_REMOTECMD         (7)
#define CWBCO_SERVICE_SECURITY          (8)
#define CWBCO_SERVICE_DDM               (9)
#define CWBCO_SERVICE_MAPI              (10)
#define CWBCO_SERVICE_USF               (11)
#define CWBCO_SERVICE_WEB_ADMIN         (12)
#define CWBCO_SERVICE_TELNET            (13)
#define CWBCO_SERVICE_MGMT_CENTRAL      (14)
#define CWBCO_SERVICE_ANY               (100)         // Apply to ANY service
#define CWBCO_SERVICE_ALL               (101)         // Apply to ALL services

/*------------------------------------------------------------------*/
/* DEFINES: for cwbCO_PromptMode                                    */
/*------------------------------------------------------------------*/
#define CWBCO_PROMPT_IF_NECESSARY       (0L)
#define CWBCO_PROMPT_ALWAYS             (1L)
#define CWBCO_PROMPT_NEVER              (2L)
#define CWBCO_PROMPT_DEFAULT            CWBCO_PROMPT_IF_NECESSARY

/*------------------------------------------------------------------*/
/* DEFINES: for cwbCO_ValidateMode                                  */
/*------------------------------------------------------------------*/
#define CWBCO_VALIDATE_IF_NECESSARY     (0L)
#define CWBCO_VALIDATE_ALWAYS           (1L)
#define CWBCO_VALIDATE_DEFAULT          CWBCO_VALIDATE_IF_NECESSARY

/*------------------------------------------------------------------*/
/* DEFINES: for cwbCO_DefaultUserMode                               */
/*------------------------------------------------------------------*/
#define CWBCO_DEFAULT_USER_MODE_NOT_SET (0L)  // not set, user may be prompted
#define CWBCO_DEFAULT_USER_USE          (1L)
#define CWBCO_DEFAULT_USER_IGNORE       (2L)
#define CWBCO_DEFAULT_USER_USEWINLOGON  (3L)
#define CWBCO_DEFAULT_USER_USE_KERBEROS (4L)
#define CWBCO_DEFAULT_USER_DEFAULT      CWBCO_DEFAULT_USER_MODE_NOT_SET

/*------------------------------------------------------------------*/
/* DEFINES: for cwbCO_IPAddressLookupMode                           */
/*------------------------------------------------------------------*/
#define CWBCO_IPADDR_LOOKUP_ALWAYS        (0L)
#define CWBCO_IPADDR_LOOKUP_1HOUR         (1L)
#define CWBCO_IPADDR_LOOKUP_1DAY          (2L)
#define CWBCO_IPADDR_LOOKUP_1WEEK         (3L)
#define CWBCO_IPADDR_LOOKUP_NEVER         (4L)
#define CWBCO_IPADDR_LOOKUP_AFTER_STARTUP (5L)
#ifdef WIN32
  #define CWBCO_IPADDR_LOOKUP_DEFAULT       CWBCO_IPADDR_LOOKUP_ALWAYS
#else
  #define CWBCO_IPADDR_LOOKUP_DEFAULT       CWBCO_IPADDR_LOOKUP_1DAY
#endif

/*------------------------------------------------------------------*/
/* DEFINES: for cwbCO_PortLookupMode                                */
/*------------------------------------------------------------------*/
#define CWBCO_PORT_LOOKUP_SERVER        (0L)   // ask AS/400 server mapper
#define CWBCO_PORT_LOOKUP_LOCAL         (1L)   // look in PC services file
#define CWBCO_PORT_LOOKUP_STANDARD      (2L)   // use standard port
#ifdef WIN32
  #define CWBCO_PORT_LOOKUP_DEFAULT       CWBCO_PORT_LOOKUP_SERVER
#else
  #define CWBCO_PORT_LOOKUP_DEFAULT       CWBCO_PORT_LOOKUP_STANDARD
#endif

/*------------------------------------------------------------------*/
/* DEFINES: for cwbCO_PersistenceMode                               */
/*------------------------------------------------------------------*/
#define CWBCO_MAY_MAKE_PERSISTENT       (0L)
#define CWBCO_MAY_NOT_MAKE_PERSISTENT   (1L)
#define CWBCO_PERSISTENCE_DEFAULT       CWBCO_MAY_MAKE_PERSISTENT

/*------------------------------------------------------------------*/
/* DEFINES: for secure sockets enablement                           */
/*------------------------------------------------------------------*/
#define CWBCO_USE_SECURE_SOCKETS        (CWB_TRUE)
#define CWBCO_DO_NOT_USE_SECURE_SOCKETS (CWB_FALSE)
#define CWBCO_SECURE_SOCKETS_DEFAULT    CWBCO_DO_NOT_USE_SECURE_SOCKETS

/*------------------------------------------------------------------*/
/* DEFINES: for string lengths (does NOT include room for a         */
/*          terminating NULL!) These lengths are number of          */
/*          characters, not bytes.                                  */
/*------------------------------------------------------------------*/
#define CWBCO_MAX_USER_ID               (10)
#define CWBCO_MAX_SYS_NAME              (255)
#define CWBCO_MAX_SYS_DESCRIPTION       (256)
#define CWBCO_MAX_ENV_NAME              (50)
#define CWBCO_MAX_SERVICE_NAME          (32)
#define CWBCO_MAX_IP_ADDRESS            (15)   // Format: "nnn.nnn.nnn.nnn"
#define CWBCO_MAX_SSL_PASSWORD          (128)

/*------------------------------------------------------------------*/
/* DEFINES: for maximum password length (does NOT include room for  */
/*          a terminating NULL!) This length is number of bytes,    */
/*          not characters. The maximum number of characters        */
/*          allowed in a password is based on the AS/400 password   */
/*          level system value.                                     */
/*            - Password levels 0 and 1: 10-character maximum       */
/*            - Password levels 2 and 3: 128-character maximum      */
/*          Note: A second constant was added with BYTES explicitly */
/*          included in the name; use of this constant may help     */
/*          someone reading the code understand it more clearly.    */
/*------------------------------------------------------------------*/
#define CWBCO_MAX_PASSWORD              (256)
#define CWBCO_MAX_PASSWORD_BYTES        (CWBCO_MAX_PASSWORD)


/*------------------------------------------------------------------*/
/* DEFINES: for connection timeout attribute                        */
/*------------------------------------------------------------------*/
#define CWBCO_CONNECT_TIMEOUT_MIN       (1)    // Minimum is 1 second
#define CWBCO_CONNECT_TIMEOUT_MAX       (3600) // Maximum is 1 hour
#define CWBCO_CONNECT_TIMEOUT_DEFAULT   (30)   // Default is 30 seconds
#define CWBCO_CONNECT_TIMEOUT_NONE      (0)    // 0 means do not timeout



#ifndef NOCWBCOSYSAPI

#ifdef __cplusplus
extern "C" {
#endif


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_CreateSystem                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Create a new system object and return a handle to it that      */
/*   can be used with subsequent calls.  The system object has      */
/*   many attributes that can be set or retrieved; see 'System      */
/*   Object Attributes' below.                                      */
/*                                                                  */
/* Parameters:                                                      */
/*   LPCSTR systemName - input                                      */
/*     Pointer to a buffer that contains the NULL-terminated name   */
/*     of the AS/400 system.  This can be its host name, or         */
/*     the AS/400 system's dotted-decimal IP address itself.  It    */
/*     must not be zero length and must not contain blanks.  If the */
/*     name specified is not a valid AS/400 system host name or IP  */
/*     address string (in the form "nnn.nnn.nnn.nnn"), any          */
/*     connection attempt or security validation attempt will fail. */
/*                                                                  */
/*   cwbCO_SysHandle *system - output                               */
/*     The system object handle is returned in this parameter.      */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - One of the pointer parameters is NULL.   */
/*   CWB_INVALID_SYSNAME - The system name is not valid.            */
/*   CWB_RESTRICTED_BY_POLICY - A policy exists that prohibits      */
/*                              the user from creating a system     */
/*                              object for a system not already     */
/*                              defined in the persistent systems   */
/*                              list.                               */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*                                                                  */
/* Usage Notes:                                                     */
/*   When you are done using the system object, you must call       */
/*   cwbCO_DeleteSystem() to free resources the system object is    */
/*   using.                                                         */
/*                                                                  */
/*   If you want to create a system object that is like one you     */
/*   already have, use cwbCO_CreateSystemLike().                    */
/*                                                                  */
/* System Object Attributes:                                        */
/*   Below are listed the attributes of a system object that affect */
/*   the behavior of signing on and communicating with the AS/400   */
/*   system this object represents.  With each attribute are listed */
/*   the APIs you can use to get and set it, and what its default   */
/*   value is when the system object is created.  Note that the     */
/*   attribute's settings apply only to the system object they are  */
/*   set for, NOT to any other system objects, even if other system */
/*   objects have the same AS/400 system name.                      */
/*                                                                  */
/*   Most attributes can be changed until a successful signon has   */
/*   occurred, either as the result of a successful call to         */
/*   cwbCO_Signon() or to cwbCO_Connect().  After the signon has    */
/*   successfully taken place, calling the cwbCO_Set___() API to    */
/*   try to change the value of such an attribute will fail with    */
/*   return code CWB_INV_AFTER_SIGNON.  The attributes that         */
/*   can be changed any time, even after a successful signon,       */
/*   are Validate Mode and Prompt Mode.                             */
/*                                                                  */
/*   Finally, some values below and the ability to change them may  */
/*   be controlled via policies.  Policies are controls that a      */
/*   systems administrator can set up to mandate default attribute  */
/*   values and to prohibit changes to attributes.  The default     */
/*   values specified below are those that will be used if policies */
/*   do not mandate or suggest different ones, and if a value for   */
/*   such an attribute has not been explicitly configured for this  */
/*   AS/400 system in the persistent systems list.  If an           */
/*   attribute's default value may be set by policy, this is noted  */
/*   below.  If changing an attribute's value can be prohibited     */
/*   by policy, an API is provided to check for the attribute's     */
/*   modifiability, and a specific return code is provided by the   */
/*   attribute's set method if the set fails because of such a      */
/*   policy.                                                        */
/*                                                                  */
/*     AS/400 System Name: the host name or IP address of the       */
/*       AS/400 system to communicate with and use by way of this   */
/*       instance of a system object.  This can be set only at      */
/*       the time cwbCO_CreateSystem() or cwbCO_CreateSystemLike()  */
/*       is called.  Note that the system name is used as the       */
/*       unique identifier when validating security information     */
/*       for a specific user ID.  That is, if two different system  */
/*       objects contain different system names (e.g. "SYS1" and    */
/*       "SYS1.ACME.COM") which represent the same physical AS/400  */
/*       system, user ID and password will require separate         */
/*       validation for the two system objects, which may result    */
/*       in double prompting and use of different default user      */
/*       IDs when connecting.                                       */
/*         * get using cwbCO_GetSystemName()                        */
/*        >> Default: There is no default, since this is explicitly */
/*                    set when the system object is created.        */
/*                                                                  */
/*     AS/400 Description: a description of the configured          */
/*       connection to the AS/400 system.  This can be set only     */
/*       using Operations Navigator, and can be retrieved using     */
/*       cwbCO_GetDescription().  The description is stored with    */
/*       each system object, and never changed for that system      */
/*       object.  If the description is changed using Operations    */
/*       Navigator, system objects for that system that existed     */
/*       before the change was made are not changed -- only new     */
/*       system objects will contain the new description.           */
/*         * get using cwbCO_GetDescription()                       */
/*        >> Default: blank                                         */
/*             ** THE DEFAULT MAY BE OVERRIDDEN BY POLICIES! **     */
/*                                                                  */
/*     User ID: the user ID used to logon to the AS/400 system      */
/*         * get using cwbCO_GetUserIDEx()                          */
/*         * set using cwbCO_SetUserIDEx()                          */
/*        >> Default: The first time you connect to the AS/400      */
/*                    system named in the system object, you may    */
/*                    be prompted to specify a default user ID or   */
/*                    specify that the default user ID should be    */
/*                    the same as your Windows user ID, or that     */
/*                    no default will be used.  On subsequent       */
/*                    connection attempts, the default user ID      */
/*                    used will depend on which option you chose    */
/*                    when prompted during the first connection     */
/*                    attempt.                                      */
/*                                                                  */
/*     Password: the password used to signon to the AS/400 system   */
/*         * set using cwbCO_SetPassword()                          */
/*        >> Default: blank (no password set) if the user ID set    */
/*                    in the system object has never signed on to   */
/*                    the AS/400 system named in the system object. */
/*                    If a previous successful signon or connection */
/*                    has been made to the AS/400 system as named   */
/*                    in the system object, that password may be    */
/*                    used for the next signon or connection        */
/*                    attempt.                                      */
/*                                                                  */
/*     Default User Mode: controls behavior associated with the     */
/*       default user ID, including where to get it from and        */
/*       whether or not to use it.  If not set (i.e. if the value   */
/*       is CWBCO_DEFAULT_USER_MODE_NOT_SET), the user may be       */
/*       prompted to choose which behavior is desired at the time   */
/*       a signon is attempted.                                     */
/*         * get using cwbCO_GetDefaultUserMode()                   */
/*         * set using cwbCO_SetDefaultUserMode()                   */
/*         * check for modify restriction using                     */
/*             cwbCO_CanModifyDefaultUserMode()                     */
/*        >> Default: CWBCO_DEFAULT_USER_MODE_NOT_SET               */
/*             ** THE DEFAULT MAY BE OVERRIDDEN BY POLICIES! **     */
/*                                                                  */
/*     Prompt Mode: controls when Client Access will prompt the     */
/*       user for user ID and password.  See the declaration        */
/*       comments for cwbCO_SetPromptMode() for possible values     */
/*       and associated behaviors.                                  */
/*         * get using cwbCO_GetPromptMode()                        */
/*         * set using cwbCO_SetPromptMode()                        */
/*        >> Default: CWBCO_PROMPT_IF_NECESSARY                     */
/*                                                                  */
/*     Window Handle: the window handle of the calling application. */
/*       If this is set, any prompting that Client Access does      */
/*       related to AS/400 signon will use the window handle and    */
/*       thus be 'modal' to the associated window.  This means that */
/*       the prompt will not ever be hidden UNDER the main          */
/*       application window if its handle is associated with the    */
/*       system object.  If no window handle is set, the prompt     */
/*       might get hidden behind the main application window, if    */
/*       one exists.                                                */
/*         * get using cwbCO_GetWindowHandle()                      */
/*         * set using cwbCO_SetWindowHandle()                      */
/*        >> Default: NULL (not set)                                */
/*                                                                  */
/*     Validate Mode: whether when validating user ID and password, */
/*       communication with the AS/400 system to perform this       */
/*       validation actually occurs.  See the declaration comments  */
/*       for cwbCO_SetValidateMode() and cwbCO_GetValidateMode()    */
/*       for possible values and associated behaviors.              */
/*         * get using cwbCO_GetValidateMode()                      */
/*         * set using cwbCO_SetValidateMode()                      */
/*        >> Default: CWBCO_VALIDATE_IF_NECESSARY                   */
/*                                                                  */
/*     Use Secure Sockets: whether Client Access will use secure    */
/*       sockets to authenticate the server (AS/400 system) and to  */
/*       encrypt data sent and received.  Since there are some      */
/*       cases where secure sockets cannot be used, for example     */
/*       when the software support for secure sockets has not       */
/*       been installed on the PC, an application or user request   */
/*       for secure sockets use may fail, either at the time the    */
/*       cwbCO_UseSecureSocktes() API is called or at connect time. */
/*       If no such failure occurs, then secure sockets is being    */
/*       used, and cwbCO_IsSecureSockets() will return CWB_TRUE.    */
/*         * get using cwbCO_IsSecureSockets()                      */
/*         * set using cwbCO_UseSecureSockets()                     */
/*         * check for modify restriction using                     */
/*             cwbCO_CanModifyUseSecureSockets()                    */
/*        >> Default: Whatever has been configured for this AS/400  */
/*                    system in the persistent system list will be  */
/*                    used.  If no configuration for this AS/400    */
/*                    system exists or if the configuration         */
/*                    specifies to use the Client Access default,   */
/*                    then secure sockets will not be used          */
/*                    (CWB_FALSE).                                  */
/*             ** THE DEFAULT MAY BE OVERRIDDEN BY POLICIES! **     */
/*                                                                  */
/*     IP Address Lookup Mode: when, if ever, dynamic lookup of     */
/*       the AS/400 system's IP address will occur.  See comments   */
/*       where cwbCO_SetIPAddressLookupMode() is declared for more  */
/*       information and possible values.                           */
/*         * get using cwbCO_GetIPAddressLookupMode()               */
/*         * set using cwbCO_SetIPAddressLookupMode()               */
/*         * check for modify restriction using                     */
/*             cwbCO_CanModifyIPAddressLookupMode()                 */
/*        >> Default: Whatever has been configured for this AS/400  */
/*                    system in Client Access Properties will be    */
/*                    used.  If no configuration for this AS/400    */
/*                    system exists, the default is                 */
/*                    CWBCO_IPADDR_LOOKUP_ALWAYS.                   */
/*             ** THE DEFAULT MAY BE OVERRIDDEN BY POLICIES! **     */
/*                                                                  */
/*     Port Lookup Mode: how to retrieve the remote port for an     */
/*       AS/400 host service -- whether to look it up locally (on   */
/*       the PC), on the AS/400 system itself, or to simply use the */
/*       default ("standard") port for the specified service.  If   */
/*       local lookup is selected, the standard TCP/IP method of    */
/*       lookup in the SERVICES file on the PC is used.  If server  */
/*       lookup is specified, a connection to the AS/400 system     */
/*       server mapper is made to retrieve the port number by       */
/*       lookup from the AS/400 system service table.  If either    */
/*       the local or server lookup method fails, then connecting   */
/*       to the service will fail.  For more information and        */
/*       possible values, see the API declaration for               */
/*       cwbCO_SetPortLookupMode().                                 */
/*         * get using cwbCO_GetPortLookupMode()                    */
/*         * set using cwbCO_SetPortLookupMode()                    */
/*         * check for modify restriction using                     */
/*             cwbCO_CanModifyPortLookupMode()                      */
/*        >> Default: Whatever has been configured for this AS/400  */
/*                    system in the persistent systems list will be */
/*                    used.  If no configuration for this AS/400    */
/*                    system exists, the default is                 */
/*                    CWBCO_PORT_LOOKUP_SERVER.                     */
/*             ** THE DEFAULT MAY BE OVERRIDDEN BY POLICIES! **     */
/*                                                                  */
/*     Persistence Mode: whether or not the AS/400 system named     */
/*       in this system object may be added to the persistent       */
/*       systems list (if not already in the list) once a           */
/*       successful call to cwbCO_Connect() has completed.  See     */
/*       comments where cwbCO_SetPersistenceMode() is declared for  */
/*       more information and possible values.                      */
/*         * get using cwbCO_GetPersistenceMode()                   */
/*         * set using cwbCO_SetPersistenceMode()                   */
/*         * check for modify restriction using                     */
/*             cwbCO_CanModifyPersistenceMode()                     */
/*        >> Default: CWBCO_MAY_MAKE_PERSISTENT                     */
/*             ** THE DEFAULT MAY BE OVERRIDDEN BY POLICIES! **     */
/*                                                                  */
/*     Connection Timeout: how long Client Access will wait for     */
/*       a connection attempt to complete.  This setting does not   */
/*       affect how long the TCP/IP communications stack will wait  */
/*       before giving up, only how long Client Access will wait.   */
/*       The TCP/IP communications stack might timeout before the   */
/*       Client Access connection timeout has expired.  See         */
/*       comments where cwbCO_SetConnectTimeout() is declared for   */
/*       more information and possible values.  This value may be   */
/*       changed for a system object at any time.                   */
/*         * get using cwbCO_GetConnectTimeout()                    */
/*         * set using cwbCO_SetConnectTimeout()                    */
/*        >> Default: CWBCO_CONNECT_TIMEOUT_DEFAULT                 */
/*             ** THE DEFAULT MAY BE OVERRIDDEN BY POLICIES! **     */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_CreateSystem(
                             LPCSTR              systemName,
                             cwbCO_SysHandle    *system);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_CreateSystemA(
                             LPCSTR              systemName,
                             cwbCO_SysHandle    *system);
#endif    // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbCO_CreateSystemW(
                             LPCWSTR             systemName,
                             cwbCO_SysHandle    *system);
#endif    // UNICODE-only selection


// UNICODE/ANSI API Selection
#if  (  defined(CWB_UNICODE)  && (!( defined(CWB_OEM) || defined(CWB_ANSI)  ))  )
   #define cwbCO_CreateSystem          cwbCO_CreateSystemW
#elif (  defined(CWB_ANSI)  &&  (!( defined(CWB_OEM)  || defined(CWB_UNICODE)  )) )
   #define cwbCO_CreateSystem          cwbCO_CreateSystemA
#endif  // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_CreateSystemLike                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Create a new system object that is "like" a given system       */
/*   object.  You may either provide a specific system name for     */
/*   the new system object, or specify NULL to use the given system */
/*   object's name.  All attributes of the given system object are  */
/*   copied into the new one, with the following exceptions:        */
/*     - User ID                                                    */
/*     - Password                                                   */
/*     - System name, if a different one is specified               */
/*     - IP address, when the system names are different            */
/*   (See documentation for cwbCO_CreateSystem for a list of        */
/*   system object attributes.)                                     */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle systemToCopy - input                           */
/*     Handle that was returned by a previous call to either        */
/*     cwbCO_CreateSystem() or cwbCO_CreateSystemLike().  It        */
/*     identifies the AS/400 system.  This is the object that       */
/*     will be "copied."                                            */
/*                                                                  */
/*   LPCSTR systemName - input                                      */
/*     Pointer to a buffer that contains the NULL-terminated name   */
/*     of the AS/400 system to use in the new system object.  If    */
/*     NULL or the empty string is passed, the name from the given  */
/*     system object is copied into the new system object.  If a    */
/*     system name is specified, it can be the host name, or        */
/*     the AS/400 system's dotted-decimal IP address.  If the       */
/*     name specified is not a valid AS/400 system host name or IP  */
/*     address string (in the form "nnn.nnn.nnn.nnn"), any          */
/*     connection attempt or security validation attempt will fail. */
/*                                                                  */
/*   cwbCO_SysHandle *newSystem - output                            */
/*     The system object handle of the new system object is         */
/*     returned in this parameter.                                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - The systemToCopy handle is invalid.   */
/*   CWB_INVALID_POINTER - The newSystem pointer is NULL.           */
/*   CWB_INVALID_SYSNAME - the system name is not valid.            */
/*   CWB_RESTRICTED_BY_POLICY - A policy exists that prohibits      */
/*                              the user from creating a system     */
/*                              object for a system not already     */
/*                              defined in the persistent systems   */
/*                              list.                               */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*                                                                  */
/* Usage Notes:                                                     */
/*   When you are done using the new system object, you must call   */
/*   cwbCO_DeleteSystem() to free resources the system object is    */
/*   using.                                                         */
/*                                                                  */
/*   The state of the new system object might not be the same as    */
/*   that of the given system object, since user ID and password    */
/*   validation has not yet been performed for the new one.  Also,  */
/*   the new system object has no connections associated with it,   */
/*   whereas the given system object may.  Because of this, even    */
/*   though you might not be able to change attributes of the       */
/*   given system object because of its state, you might be able    */
/*   to change these attributes of the new system object because of */
/*   its possibly different state.                                  */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_CreateSystemLike(
                             cwbCO_SysHandle     systemToCopy,
                             LPCSTR              systemName,
                             cwbCO_SysHandle    *system);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_CreateSystemLikeA(
                             cwbCO_SysHandle     systemToCopy,
                             LPCSTR              systemName,
                             cwbCO_SysHandle    *system);
#endif    // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbCO_CreateSystemLikeW(
                             cwbCO_SysHandle     systemToCopy,
                             LPCWSTR             systemName,
                             cwbCO_SysHandle    *system);
#endif    // UNICODE-only selection


// UNICODE/ANSI API Selection
#if  (  defined(CWB_UNICODE)  && (!( defined(CWB_OEM) || defined(CWB_ANSI)  ))  )
   #define cwbCO_CreateSystemLike      cwbCO_CreateSystemLikeW
#elif (  defined(CWB_ANSI)  &&  (!( defined(CWB_OEM)  || defined(CWB_UNICODE)  )) )
   #define cwbCO_CreateSystemLike      cwbCO_CreateSystemLikeA
#endif  // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_DeleteSystem                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Deletes the system object specified by its handle and frees    */
/*   all resources the system object used.                          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle that was returned by a previous call to either        */
/*     cwbCO_CreateSystem() or cwbCO_CreateSystemLike().  It        */
/*     identifies the AS/400 system.                                */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Before the system object resources are freed, if there are     */
/*   any connections that were made using the specified system      */
/*   object, they will be ended, forcefully if need be.  To         */
/*   determine if there are active connections, call                */
/*   cwbCO_IsConnected().  If you wish to know whether or not       */
/*   disconnecting any existing connections was successful, call    */
/*   cwbCO_Disconnect() explicitly before calling this API.         */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_DeleteSystem(
                             cwbCO_SysHandle     system);


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_Connect                                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   Connect to the specified AS/400 host service.                  */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously by cwbCO_CreateSystem() or        */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system   */
/*     to connect to.                                               */
/*                                                                  */
/*   cwbCO_Service service - input                                  */
/*     The service to connect to on the AS/400 system.  Valid       */
/*     values are listed at the start of this header file, except   */
/*     for the values CWBCO_SERVICE_ANY and CWBCO_SERVICE_ALL.      */
/*     Only one service may be specified for this API, unlike       */
/*     cwbCO_Disconnect, which can disconnect multiple services     */
/*     at once.                                                     */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input/output                     */
/*     Any returned messages will be written to this object.  It    */
/*     is created with the cwbSV_CreateErrHandle API.  The          */
/*     messages may be retrieved through the cwbSV_GetErrText API.  */
/*     If the parameter is set to zero, or if the errorHandle is    */
/*     invalid, no messages will be retrieved.                      */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_SERVICE_NAME_ERROR - The service identifier is not a valid */
/*                            value, or was a combination of values */
/*                            (only a single value is allowed for   */
/*                            this API).                            */
/*   CWB_CONNECTION_TIMED_OUT - It took too long to find the AS/400 */
/*                              system, so the attempt timed out.   */
/*   CWB_CONNECTION_REFUSED - The AS/400 system refused to accept   */
/*                            our connection attempt.               */
/*   CWB_NETWORK_IS_DOWN - A network error occurred, or TCP/IP is   */
/*                         not configured correctly on the PC.      */
/*   CWB_NETWORK_IS_UNREACHABLE - The network segment the AS/400    */
/*                                system is connected to is         */
/*                                currently not reachable from the  */
/*                                segment the PC is connected to.   */
/*   CWB_USER_TIMEOUT - The connect timeout value associated with   */
/*               the system object expired before the connection    */
/*               attempt completed, so we stopped waiting.          */
/*                                                                  */
/*   Other return codes may be commonly returned as the result of   */
/*   a failed security validation attempt.  See the list of common  */
/*   return codes in the comments for cwbCO_Signon.                 */
/*                                                                  */
/* Usage Notes:                                                     */
/*   If signon to the AS/400 system has not yet occurred, the       */
/*   signon will be performed first when cwbCO_Connect is called.   */
/*   If you want the signon to occur at a separate time, call       */
/*   cwbCO_Signon first, then call cwbCO_Connect at a later time.   */
/*   For more information about signon and its behavior, see        */
/*   comments for cwbCO_Signon.  If the signon attempt fails, a     */
/*   connection to the specified service will not be established.   */
/*                                                                  */
/*   If the AS/400 system as named in the specified system object   */
/*   does not exist in the global persistent systems list, and      */
/*   the system object Persistence Mode is set appropriately,       */
/*   then when cwbCO_Connect or cwbCO_Signon is first successfully  */
/*   called, the AS/400 system, as named in the system object,      */
/*   will be added to the global persistent systems list.  For      */
/*   more information about the Persistence Mode, see the comments  */
/*   for cwbCO_SetPersistenceMode.                                  */
/*                                                                  */
/*   If a connection to the specified service already exists, no    */
/*   new connection will be established, and CWB_OK will be         */
/*   returned.  Each time this API is successfully called, the      */
/*   usage count for the connection to the specified service will   */
/*   be incremented. Each time cwbCO_Disconnect() is called for     */
/*   the same service, the usage count will be decremented.  When   */
/*   the usage count reaches zero, the actual connection is ended.  */
/*   Therefore, it is VERY IMPORTANT that for every call to the     */
/*   cwbCO_Connect() API there is a later paired call to the        */
/*   cwbCO_Disconnect() API, so that the connection can be ended    */
/*   at the appropriate time.  The alternative is to call the       */
/*   cwbCO_Disconnect() API, specifying CWBCO_SERVICE_ALL, which    */
/*   will disconnect all existing connections to ALL services made  */
/*   through the specified system object, and reset all usage       */
/*   counts to 0.                                                   */
/*                                                                  */
/*   If the return code is CWB_USER_TIMEOUT, try increasing         */
/*   the connect timeout value for this system object, by calling   */
/*   cwbCO_SetConnectTimeout, and try connecting again.  If you     */
/*   want Client Access to not give up until the TCP/IP             */
/*   communication stack itself does, set the connect timeout to    */
/*   CWBCO_CONNECT_TIMEOUT_NONE, and try connecting again.          */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_Connect(
                             cwbCO_SysHandle     system,
                             cwbCO_Service       service,
                             cwbSV_ErrHandle     errorHandle );


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_Verify                                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Verify that a connection can be made to a specific host        */
/*   service on an AS/400 system.                                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system   */
/*     to verify connectability to.                                 */
/*                                                                  */
/*   cwbCO_Service service - input                                  */
/*     The service to verify connectability to on the AS/400        */
/*     system.  Valid values are those listed at the start of this  */
/*     file, except for the value CWBCO_SERVICE_ANY.  To verify     */
/*     connectability of ALL services, specify CWBCO_SERVICE_ALL.   */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input/output                     */
/*     Any returned messages will be written to this object.  It    */
/*     is created with the cwbSV_CreateErrHandle API.  The          */
/*     messages may be retrieved through the cwbSV_GetErrText API.  */
/*     If the parameter is set to zero, or if the errorHandle is    */
/*     invalid, no messages will be retrieved.                      */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_SERVICE_NAME_ERROR - The service identifier is invalid.    */
/*   CWB_COMMUNICATIONS_ERROR - An error occurred attempting to     */
/*                              verify a connection to the service. */
/*   CWB_USER_TIMEOUT - The connect timeout value associated with   */
/*               the system object expired before the connection    */
/*               verification attempt completed, so we stopped      */
/*               waiting.                                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API does not require user ID and password to be set, nor  */
/*   will it cause a signon to occur, thus it will never prompt for */
/*   this information.  It does not change the state of the system  */
/*   object in any way.                                             */
/*                                                                  */
/*   Even if a connection to the specified service already exists   */
/*   for the given system object, a new connection is attempted.    */
/*   The attributes of the given system object, such as whether     */
/*   to use secure sockets, are used for this connection attempt.   */
/*   It is therefore possible that connection verification may fail */
/*   given the passed system object, but might succeed to the same  */
/*   system given a system object whose attributes are set          */
/*   differently.  The most obvious example of this is where        */
/*   secure sockets use is concerned, since the non-secure-sockets  */
/*   version of the service may be running on the AS/400 system,    */
/*   while the secure-sockets version of the service might not be   */
/*   running, or vice-versa.                                        */
/*                                                                  */
/*   If CWBCO_SERVICE_ALL is specified for verification, the        */
/*   return code will be CWB_OK only if ALL services can be         */
/*   connected to.  If any one verification attempt fails, the      */
/*   return code will be that from the first failure, although      */
/*   verification of the other services will still be attempted.    */
/*                                                                  */
/*   Since this API does not establish a usable connection, it will */
/*   automatically disconnect when the verification is complete;    */
/*   therefore do NOT call cwbCO_Disconnect() to end the            */
/*   connection.                                                    */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_Verify(
                             cwbCO_SysHandle     system,
                             cwbCO_Service       service,
                             cwbSV_ErrHandle     errorHandle );


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_Disconnect                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Disconnect from the specified AS/400 host service.             */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system   */
/*     to disconnect from.                                          */
/*                                                                  */
/*   cwbCO_Service service - input                                  */
/*     The service to disconnect from on the AS/400 system.  Valid  */
/*     values are those listed at the start of this file, except    */
/*     for the value CWBCO_SERVICE_ANY.  If CWBCO_SERVICE_ALL is    */
/*     specified, the connections to ALL connected services will    */
/*     be ended, and all connection usage counts reset back to 0.   */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input/output                     */
/*     Any returned messages will be written to this object.  It    */
/*     is created with the cwbSV_CreateErrHandle API.  The          */
/*     messages may be retrieved through the cwbSV_GetErrText API.  */
/*     If the parameter is set to zero, or if the errorHandle is    */
/*     invalid, no messages will be retrieved.                      */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_SERVICE_NAME_ERROR - The service identifier is invalid.    */
/*   CWB_NOT_CONNECTED - The single service was not connected.      */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This function should be called when a connection established   */
/*   using cwbCO_Connect() is no longer needed.                     */
/*                                                                  */
/*   If any service specified cannot be disconnected, the return    */
/*   code will indicate this error.  If more than one error occurs, */
/*   only the first will be returned as the API return code.        */
/*                                                                  */
/* Usage Notes for individual service disconnect:                   */
/*   This function will cause the usage count for this system       */
/*   object's specified service to be decremented, and may or may   */
/*   not end the actual connection.  For more information please    */
/*   read the Usage Notes for the cwbCO_Connect() API.              */
/*                                                                  */
/*   Disconnecting a service that is not currently connected        */
/*   results in CWB_NOT_CONNECTED.                                  */
/*                                                                  */
/*   An individual service is gracefully disconnected.              */
/*                                                                  */
/* Usage Notes for CWBCO_SERVICE_ALL:                               */
/*   The return code CWB_NOT_CONNECTED is not returned when         */
/*   CWBCO_SERVICE_ALL is specified, regardless of the number of    */
/*   connected services.                                            */
/*                                                                  */
/*   Requesting that all active services be disconnected may        */
/*   generate messages on the AS/400.                               */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_Disconnect(
                             cwbCO_SysHandle     system,
                             cwbCO_Service       service,
                             cwbSV_ErrHandle     errorHandle );


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_IsConnected                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Find out if any, and/or how many, connections to the AS/400    */
/*   system using the specified system object currently exist.      */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   cwbCO_Service service - input                                  */
/*     The service to check for a connection.  Any of the           */
/*     cwbCO_Service values listed at the start of this file        */
/*     is valid.  To find out if ANY service is connected,          */
/*     specify CWBCO_SERVICE_ANY.  To find out how many services    */
/*     are connected using this system object, specify              */
/*     CWBCO_SERVICE_ALL.                                           */
/*                                                                  */
/*   PULONG numberOfConnections - output                            */
/*     Used to return the number of connections active for the      */
/*     service(s) specified.  If the service specified is not       */
/*     CWBCO_SERVICE_ALL, the value returned will be either 0 or    */
/*     1, since there can be at most 1 active connection per        */
/*     service per system object.  If CWBCO_SERVICE_ALL is          */
/*     specified, this could be from 0 to the possible number of    */
/*     services, since one connection per service might be active.  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion, all services specified are     */
/*            connected, or if CWBCO_SERVICE_ANY is specified, at   */
/*            least one service is connected.                       */
/*   CWB_NOT_CONNECTED - If a single service was specified, that    */
/*                       service is not connected.  If the value    */
/*                       CWBCO_SERVICE_ANY was specified, there are */
/*                       NO active connections.  If the value       */
/*                       CWBCO_SERVICE_ALL was specified, there is  */
/*                       at least one service that is NOT           */
/*                       connected.                                 */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_SERVICE_NAME_ERROR - The service identifier is invalid.    */
/*   CWB_INVALID_POINTER - The numberOfConnections parameter is     */
/*                         NULL.                                    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   If CWBCO_SERVICE_ALL was specified and CWB_NOT_CONNECTED is    */
/*   returned, there may be some active connections -- the count    */
/*   of active connections will still be passed back.  Thus,        */
/*   to find out how many connections through the specified system  */
/*   object exist, call this API specifying CWBCO_SERVICE_ALL.  If  */
/*   the return code is either CWB_OK or CWB_NOT_CONNECTED, the     */
/*   number of connections that exist is stored in                  */
/*   numberOfConnections.                                           */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_IsConnected(
                            cwbCO_SysHandle     system,
                            cwbCO_Service       service,
                            PULONG              numberOfConnections );



/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_SetPersistenceMode                                       */
/*                                                                  */
/* Purpose:                                                         */
/*   This function sets, for the specified system object, if the    */
/*   system it represents (as named in the system object), along    */
/*   with its attributes, may be added to the persistent systems    */
/*   list (if not already in the list) once a signon has            */
/*   successfully occurred.                                         */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   cwbCO_PersistenceMode mode - input                             */
/*     Specifies the persistence mode.  Possible values are:        */
/*            CWBCO_MAY_MAKE_PERSISTENT                             */
/*                If the system named in the specified system       */
/*                object is not yet in the persistent systems list, */
/*                add it to the list once a successful signon       */
/*                has completed.  This will make the system, as     */
/*                defined by this system object, available for      */
/*                selection by this AND other applications running  */
/*                now or in the future on this personal computer    */
/*                (until the system is deleted from this list).     */
/*            CWBCO_MAY_NOT_MAKE_PERSISTENT                         */
/*                The system named in the specified system object   */
/*                (along with its attributes) may NOT be added to   */
/*                the persistent systems list.                      */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_PARAMETER - The mode parameter is an invalid       */
/*                           value.                                 */
/*   CWB_RESTRICTED_BY_POLICY - A policy exists that prohibits      */
/*                              the user from changing this value.  */
/*   CWB_INV_AFTER_SIGNON - Signon has successfully occurred using  */
/*                          the specified system object, so this    */
/*                          setting may no longer be changed.       */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API cannot be used after a successful signon has occurred */
/*   for the specified system object.  A signon has occurred if     */
/*   either cwbCO_Signon() or cwbCO_Connect() has been called       */
/*   successfully for this system object.                           */
/*                                                                  */
/*   If the system as named in the system object is already in      */
/*   the persistent systems list, this setting has no effect.       */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_SetPersistenceMode(
                             cwbCO_SysHandle        system,
                             cwbCO_PersistenceMode  mode );


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_GetPersistenceMode                                       */
/*                                                                  */
/* Purpose:                                                         */
/*   This function gets, for the specified system object, if the    */
/*   system it represents, along with its attributes, will be added */
/*   to the persistent systems list (if not already in the list)    */
/*   once a successful signon has occurred.                         */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   cwbCO_PersistenceMode * mode - output                          */
/*     Returns the persistence mode.                                */
/*     See comments for cwbCO_SetPersistenceMode() for possible     */
/*     values and their meanings.                                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - The mode pointer is NULL.                */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_GetPersistenceMode(
                             cwbCO_SysHandle        system,
                             cwbCO_PersistenceMode *mode );


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_GetDescription                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   This function gets the text description associated with a      */
/*   specified system object.                                       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   LPSTR description - output                                     */
/*     Pointer to a buffer that will contain the NULL-terminated    */
/*     description.  The description will be at most                */
/*     CWBCO_MAX_SYS_DESCRIPTION characters long, not including the */
/*     terminating NULL.                                            */
/*                                                                  */
/*   PULONG length - input/output                                   */
/*     Pointer to the length of the description buffer.  If the     */
/*     buffer is too small to hold the description, including space */
/*     for the terminating NULL, the size of the buffer needed will */
/*     be filled into this parameter.                               */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - One of the pointer parameters passed     */
/*                         in is NULL.                              */
/*   CWB_BUFFER_OVERFLOW - The description buffer is not large      */
/*                         anough to hold the entire description.   */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_GetDescription(
                              cwbCO_SysHandle    system,
                              LPSTR              description,
                              PULONG             length );
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_GetDescriptionA(
                              cwbCO_SysHandle    system,
                              LPSTR              description,
                              PULONG             length );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbCO_GetDescriptionW(
                              cwbCO_SysHandle    system,
                              LPWSTR             description,
                              PULONG             length );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbCO_GetDescription                   cwbCO_GetDescriptionW
#elif (  defined(CWB_ANSI) &&  (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbCO_GetDescription                   cwbCO_GetDescriptionA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_SetUserIDEx                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   This function sets the user ID to associate with the           */
/*   specified system object. This user ID will be used when        */
/*   connecting to the AS/400 with either the cwbCO_Signon() or     */
/*   cwbCO_Connect() call.                                          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   LPCSTR userID - input                                          */
/*     Pointer to a buffer that contains the NULL-terminated        */
/*     user ID.  The user ID must not be longer than                */
/*     CWBCO_MAX_USER_ID characters.                                */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - The userID pointer is NULL.              */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_INV_AFTER_SIGNON - Signon has successfully occurred using  */
/*                          the specified system object, so this    */
/*                          setting may no longer be changed.       */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API cannot be used after a successful signon has occurred */
/*   for the specified system object.  A signon has occurred if     */
/*   either cwbCO_Signon() or cwbCO_Connect() has been called       */
/*   successfully for this system object.                           */
/*                                                                  */
/*   Setting a user ID explicitly with this API will cause any      */
/*   default user mode set with the cwbCO_SetDefaultUserMode()      */
/*   API to be ignored.                                             */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_SetUserIDEx(
                              cwbCO_SysHandle    system,
                              LPCSTR             userID );
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_SetUserIDExA(
                              cwbCO_SysHandle    system,
                              LPCSTR             userID );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbCO_SetUserIDExW(
                              cwbCO_SysHandle    system,
                              LPCWSTR            userID );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbCO_SetUserIDEx                   cwbCO_SetUserIDExW
#elif (  defined(CWB_ANSI) &&  (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbCO_SetUserIDEx                   cwbCO_SetUserIDExA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_GetUserIDEx                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   This function gets the current user ID associated with a       */
/*   specified system object. This is the user ID that is being     */
/*   used for connections to the AS/400.                            */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   LPSTR userID - output                                          */
/*     Pointer to a buffer that will contain the NULL-terminated    */
/*     user ID.  The user ID will be at most CWBCO_MAX_USER_ID      */
/*     characters long.                                             */
/*                                                                  */
/*   PULONG length - input/output                                   */
/*     Pointer to the length of the userID buffer.  If the buffer   */
/*     is too small to hold the user ID, including space for the    */
/*     terminating NULL, the size of the buffer needed will be      */
/*     filled into this parameter.                                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - One of the pointer parameters passed     */
/*                         in is NULL.                              */
/*   CWB_BUFFER_OVERFLOW - The userID buffer is not large enough    */
/*                         to hold the entire user ID name.         */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The user ID may or may not have been validated on the AS/400   */
/*   system yet.  To make sure it has been, call cwbCO_Signon()     */
/*   or cwbCO_Connect() before calling this API.                    */
/*                                                                  */
/*   If no user ID has been set and a signon has not occurred for   */
/*   the system object, the returned user ID will be the empty      */
/*   string, even if a default user ID has been configured for the  */
/*   AS/400 system.                                                 */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_GetUserIDEx(
                              cwbCO_SysHandle    system,
                              LPSTR              userID,
                              PULONG             length );
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_GetUserIDExA(
                              cwbCO_SysHandle    system,
                              LPSTR              userID,
                              PULONG             length );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbCO_GetUserIDExW(
                              cwbCO_SysHandle    system,
                              LPWSTR             userID,
                              PULONG             length );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbCO_GetUserIDEx                   cwbCO_GetUserIDExW
#elif (  defined(CWB_ANSI) &&  (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbCO_GetUserIDEx                   cwbCO_GetUserIDExA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_SetPassword                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   This function sets the password to associate with the          */
/*   specified system object. This password will be used when       */
/*   connecting to the AS/400 with either the cwbCO_Signon() or     */
/*   cwbCO_Connect() call and a user ID has been set with the       */
/*   cwbCO_SetUserIDEx() call.                                      */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   LPCSTR password - input                                        */
/*     A pointer to a buffer that contains the NULL-terminated      */
/*     password. The maximum length is CWBCO_MAX_PASSWORD + 1       */
/*     bytes in length, including the NULL terminator.              */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - The password pointer is NULL.            */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_INV_AFTER_SIGNON - Signon has successfully occurred using  */
/*                          the specified system object, so this    */
/*                          setting may no longer be changed.       */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API cannot be used after a successful signon has occurred */
/*   for the specified system object.  A signon has occurred if     */
/*   either cwbCO_Signon() or cwbCO_Connect() has been called       */
/*   successfully for this system object.                           */
/*                                                                  */
/*   A password set with this API will not be used unless a         */
/*   corresponding user ID has been set with cwbCO_SetUserIDEx().   */
/*                                                                  */
/*   Valid password lengths depend on the current setting of the    */
/*   AS/400 system password level.  Password levels 0 and 1 allow   */
/*   passwords up to 10 characters in length. Password levels 2     */
/*   and 3 allow passwords up to 128 characters in length.          */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_SetPassword(
                              cwbCO_SysHandle    system,
                              LPCSTR             password );
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_SetPasswordA(
                              cwbCO_SysHandle    system,
                              LPCSTR             password );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbCO_SetPasswordW(
                              cwbCO_SysHandle    system,
                              LPCWSTR            password );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbCO_SetPassword                 cwbCO_SetPasswordW
#elif (  defined(CWB_ANSI) &&  (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbCO_SetPassword                 cwbCO_SetPasswordA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_SetValidateMode                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   This function sets, for the specified system object, the       */
/*   validate mode, which affects behavior when validating the      */
/*   user ID and password.                                          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   cwbCO_ValidateMode mode - input                                */
/*     Specifies the validate mode.  Possible values are:           */
/*        CWBCO_VALIDATE_IF_NECESSARY                               */
/*          If validation of this user ID on this AS/400            */
/*          system has occurred from this PC within the last        */
/*          24 hours, and the validation was successful, then       */
/*          use the results of the last validation and do not       */
/*          connect to validate at this time.  There may be         */
/*          other scenarios where re-validation will occur;         */
/*          Client Access will re-validate as needed.               */
/*        CWBCO_VALIDATE_ALWAYS                                     */
/*          Communication with the AS/400 system to validate        */
/*          user ID and password will occur every time this         */
/*          validation is requested or required. Setting this mode  */
/*          forces the validation to occur (when the system object  */
/*          is not signed on yet).  Once a system object is signed  */
/*          on, this setting is ignored.                            */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_PARAMETER - The mode parameter is an invalid       */
/*                           value.                                 */
/*   CWB_RESTRICTED_BY_POLICY - A policy exists that prohibits      */
/*                              the user from changing this value.  */
/*   CWB_INV_AFTER_SIGNON - Signon has successfully occurred using  */
/*                          the specified system object, so this    */
/*                          setting may no longer be changed.       */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API cannot be used after a successful signon has occurred */
/*   for the specified system object.  A signon has occurred if     */
/*   either cwbCO_Signon() or cwbCO_Connect() has been called       */
/*   successfully for this system object.                           */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_SetValidateMode(
                             cwbCO_SysHandle     system,
                             cwbCO_ValidateMode  mode );


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_GetValidateMode                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   This function gets, for the specified system object, the       */
/*   validate mode currently set.                                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   cwbCO_ValidateMode * mode - output                             */
/*     Returns the validate mode.                                   */
/*     See comments for cwbCO_SetValidateMode() for possible values */
/*     and their meanings.                                          */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - The mode pointer is NULL.                */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_GetValidateMode(
                             cwbCO_SysHandle      system,
                             cwbCO_ValidateMode  *mode );


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_SetDefaultUserMode                                       */
/*                                                                  */
/* Purpose:                                                         */
/*   This function sets, for the specified system object, the       */
/*   behavior with respect to any configured default user ID.       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   cwbCO_DefaultUserMode mode - input                             */
/*     Specifies what will be done with the default user ID.        */
/*       Possible values are:                                       */
/*         CWBCO_DEFAULT_USER_MODE_NOT_SET                          */
/*           No default user mode is currently in use.  When        */
/*           this mode is active, and the Prompt Mode setting       */
/*           does not prohibit prompting, the user will be          */
/*           prompted at signon or connect time to select           */
/*           which of the remaining default user modes should       */
/*           be used from then on.  The signon or connect           */
/*           cannot succeed until one of these other mode           */
/*           values is selected.  Setting the Default User          */
/*           Mode back to this value will cause the prompt to       */
/*           appear the next time a default user id is              */
/*           needed by Client Access.                               */
/*         CWBCO_DEFAULT_USER_USE                                   */
/*           When no user ID has explicitly been set (using         */
/*           cwbCO_SetUserIDEx) and a signon is to occur,           */
/*           use the default user ID configured for the             */
/*           AS/400 system as named in the system object.           */
/*         CWBCO_DEFAULT_USER_IGNORE                                */
/*           Never use a default user ID.  When a signon takes      */
/*           place and no user ID has explicitly been set for       */
/*           this system object instance, the user will be          */
/*           prompted to enter a user ID if the Prompt Mode         */
/*           allows it (see cwbCO_SetPromptMode() comments),        */
/*           and no initial value for the user ID will be           */
/*           filled in in the prompt.                               */
/*         CWBCO_DEFAULT_USER_USEWINLOGON                           */
/*           The user ID used when logging on to Windows will       */
/*           be used as the default if no user ID has               */
/*           explicitly been set for this system object             */
/*           (using cwbCO_SetUserIDEx).                             */
/*         CWBCO_DEFAULT_USER_USE_KERBEROS                          */
/*           The kerberos principal created when logging into a     */
/*           Windows domain will be used as the default if no user  */
/*           ID has explicitly been set for this system object      */
/*           (using cwbCO_SetUserIDEx).                             */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_PARAMETER - The mode parameter is an invalid       */
/*                           value.                                 */
/*   CWB_RESTRICTED_BY_POLICY - A policy exists that prohibits      */
/*                              the user from changing this value.  */
/*   CWB_INV_AFTER_SIGNON - Signon has successfully occurred using  */
/*                          the specified system object, so this    */
/*                          setting may no longer be changed.       */
/*   CWB_KERB_NOT_AVAILABLE - Kerberos security package not         */
/*                            available on this version of Windows. */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API cannot be used after a successful signon has occurred */
/*   for the specified system object.  A signon has occurred if     */
/*   either cwbCO_Signon() or cwbCO_Connect() has been called       */
/*   successfully for this system object.                           */
/*                                                                  */
/*   The default user mode set with this API will be ignored if a   */
/*   user ID has been explicitly set with the cwbCO_SetUserIDEx()   */
/*   API.                                                           */
/*                                                                  */
/*   Error code CWB_KERB_NOT_AVAILABLE will be returned if you      */
/*   attempt to set CWBCO_DEFAULT_USER_USE_KERBEROS on a Windows    */
/*   platform that doesn't support Kerberos.                        */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_SetDefaultUserMode(
                             cwbCO_SysHandle         system,
                             cwbCO_DefaultUserMode   mode );


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_GetDefaultUserMode                                       */
/*                                                                  */
/* Purpose:                                                         */
/*   This function gets, for the specified system object, the       */
/*   default user mode currently set.                               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   cwbCO_DefaultUserMode * mode - output                          */
/*     Returns the default user mode for this system object.        */
/*     See comments for cwbCO_SetDefaultUserMode() for the list     */
/*     of possible values and their meanings.                       */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - The mode pointer is NULL.                */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_GetDefaultUserMode(
                             cwbCO_SysHandle         system,
                             cwbCO_DefaultUserMode  *mode );


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_SetPromptMode                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   This function sets, for the specified system object, the       */
/*   prompt mode, which specifies when and if the user should be    */
/*   prompted for user ID and password when a signon is performed.  */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   cwbCO_PromptMode - input                                       */
/*     Specifies the prompt mode.  Possible values are:             */
/*        CWBCO_PROMPT_IF_NECESSARY                                 */
/*          Client Access will prompt if either the user ID         */
/*          or password have not been explicitly set or             */
/*          cannot be retrieved from the persistent                 */
/*          configuration for this system, the password             */
/*          cache (if enabled), or by some other means.             */
/*        CWBCO_PROMPT_ALWAYS                                       */
/*          Client Access will always prompt when a signon          */
/*          is to occur for the specified system object,            */
/*          even if a successful signon using the same user         */
/*          ID to the same AS/400 system has occurred using         */
/*          a different system object.  Since a signon can          */
/*          occur only once for a system object, this means         */
/*          exactly one prompt per system object will occur.        */
/*          Further explicit signon calls will do nothing           */
/*          (including prompt). See two exceptions to using this    */
/*          mode in the usage notes below.                          */
/*        CWBCO_PROMPT_NEVER                                        */
/*          Client Access will never prompt for user ID and         */
/*          password.  When this mode is used, a call to            */
/*          any API that requires a signon for completion           */
/*          (e.g. cwbCO_Signon() or cwbCO_Connect()) will           */
/*          fail if either the user ID or password have not         */
/*          been set and cannot be programmatically retrieved       */
/*          (e.g. from the AS/400 password cache).  This mode       */
/*          should be used when Client Access is running on         */
/*          a PC that is unattended or for some other reason        */
/*          cannot support end-user interaction, or when            */
/*          the application itself is prompting for or              */
/*          otherwise fetching the user ID and password, and        */
/*          explicitly setting them using cwbCO_SetUserIDEx         */
/*          and cwbCO_SetPassword.                                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_PARAMETER - The mode parameter is an invalid       */
/*                           value.                                 */
/*   CWB_RESTRICTED_BY_POLICY - A policy exists that prohibits      */
/*                              the user from changing this value.  */
/*   CWB_INV_AFTER_SIGNON - Signon has successfully occurred using  */
/*                          the specified system object, so this    */
/*                          setting may no longer be changed.       */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API cannot be used after a successful signon has occurred */
/*   for the specified system object.  A signon has occurred if     */
/*   either cwbCO_Signon() or cwbCO_Connect() has been called       */
/*   successfully for this system object.                           */
/*                                                                  */
/*   Setting the prompt mode to CWBCO_PROMPT_ALWAYS will not        */
/*   prompt the user in the following two cases:                    */
/*                                                                  */
/*     - a user ID and password have been explicitly set with the   */
/*       cwbCO_setUserIDEx() and cwbCO_SetPassword() API's.         */
/*                                                                  */
/*     - use Windows logon info (CWBCO_DEFAULT_USER_USEWINLOGON)    */
/*       has been set with the cwbCO_SetDefaultUserMode() API.      */
/*                                                                  */
/*   PLEASE NOTE that the Prompt Mode of a system object is NOT     */
/*   EVER saved persistently in the system list, like most other    */
/*   system object attributes are.  If a certain prompt mode is     */
/*   desired, the application itself must call this API to set      */
/*   it, since it will always be initialized to the default         */
/*   value, CWBCO_PROMPT_IF_NECESSARY, when the system object is    */
/*   created.                                                       */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_SetPromptMode(
                             cwbCO_SysHandle     system,
                             cwbCO_PromptMode    mode );


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_GetPromptMode                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   This function gets, for the specified system object, the       */
/*   prompt mode currently set.                                     */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   cwbCO_PromptMode * mode - output                               */
/*     Returns the prompt mode.                                     */
/*     See comments for cwbCO_SetPromptMode() for possible values   */
/*     and their meanings.                                          */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - The mode pointer is NULL.                */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_GetPromptMode(
                             cwbCO_SysHandle       system,
                             cwbCO_PromptMode     *mode );


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_SetWindowHandle                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   This function sets, for the specified system object, the       */
/*   window handle to use if any prompting is to be done associated */
/*   with the system object, for example prompting for user ID and  */
/*   password.  When so set (to a non-NULL window handle), such     */
/*   a prompt would appear 'modal' to the main application window   */
/*   and so would not ever get hidden behind that window.           */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   HWND windowHandle - input                                      */
/*     Specifies the window handle to associate with the system     */
/*     object.  If NULL, no window handle is associated with the    */
/*     system object.                                               */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API may be used any time to change the window handle for  */
/*   the specified system object, even after a successful signon.   */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_SetWindowHandle(
                             cwbCO_SysHandle     system,
                             HWND                windowHandle );


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_GetWindowHandle                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   This function gets, for the specified system object, the       */
/*   window handle, if any, currently associated with it.           */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   HWND * pWindowHandle - output                                  */
/*     Returns the window handle associated with the system object, */
/*     or NULL if no window handle is associated with it.           */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - The windowHandle pointer is NULL.        */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_GetWindowHandle(
                             cwbCO_SysHandle       system,
                             HWND                 *windowHandle );


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_Signon                                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Sign the user on to the AS/400 system represented by the       */
/*   specified system object using user ID and password.            */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input/output                     */
/*     Any returned messages will be written to this object.  It    */
/*     is created with the cwbSV_CreateErrHandle API.  The          */
/*     messages may be retrieved through the cwbSV_GetErrText API.  */
/*     If the parameter is set to zero, or if the errorHandle is    */
/*     invalid, no messages will be retrieved.                      */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_UNKNOWN_USERID - The supplied user ID is not               */
/*                        known to this system.                     */
/*   CWB_WRONG_PASSWORD - Password is not correct.                  */
/*   CWB_PASSWORD_EXPIRED - Password has expired.                   */
/*   CWB_USER_PROFILE_DISABLED - The user ID has been disabled.     */
/*   CWB_INVALID_PASSWORD - One or more characters in the           */
/*                          password is invalid or the password     */
/*                          is too long.                            */
/*   CWB_INVALID_USERID - One or more characters in the user ID     */
/*                        is invalid or the user ID is too long.    */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_USER_CANCELLED - The user cancelled the signon process.    */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/*   Other return codes may be commonly returned as the result of   */
/*   a failed attempt to connect to the signon server.  For a list  */
/*   of such return codes see comments for cwbCO_Connect.           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Both whether or not the user is prompted for user ID and       */
/*   password, and whether or not the AS/400 system is actually     */
/*   contacted during user validation, are influenced by current    */
/*   system object settings, such as user ID, password, Prompt Mode,*/
/*   Default User Mode, and Validate Mode.  See declarations for    */
/*   the get/set APIs of these attributes for more information.     */
/*                                                                  */
/*   If the AS/400 system as named in the specified system object   */
/*   does not exist in the global persistent systems list, and      */
/*   the system object Persistence Mode is set appropriately,       */
/*   then when cwbCO_Connect or cwbCO_Signon is first successfully  */
/*   called, the AS/400 system, as named in the system object,      */
/*   will be added to the global persistent systems list.  For      */
/*   more information about the Persistence Mode, see the comments  */
/*   for cwbCO_SetPersistenceMode.                                  */
/*                                                                  */
/*   If successful, and AS/400 password caching is enabled, the     */
/*   password will be stored for the resulting user ID in the PC's  */
/*   AS/400 password cache.                                         */
/*                                                                  */
/* Differences between this and cwbCO_VerifyUserIDPassword()        */
/* ---------------------------------------------------------        */
/* - cwbCO_VerifyUserIDPassword() requires that a user ID and       */
/*     password be passed-in (system object values for these will   */
/*     NOT be used), and will not prompt for this information.      */
/*     cwbCO_Signon() may use prompting, depending on other system  */
/*     object settings, and in that case will use whatever values   */
/*     are supplied by the user for user ID and password in its     */
/*     validation attempt.                                          */
/* - Since cwbCO_VerifyUserIDPassword() will never prompt for       */
/*     user ID and password, these settings in the specified        */
/*     system object will not be changed as a result of that        */
/*     call.  A call to cwbCO_Signon(), however, may change the     */
/*     user ID and/or password of the system object as the          */
/*     result of possible prompting for this information.           */
/* - cwbCO_VerifyUserIDPassword() will ALWAYS result in a           */
/*     connection to the AS/400 system being established to         */
/*     perform user ID and password validation, and to retrieve     */
/*     current values (such as date and time of last successful     */
/*     signon) related to signon attempts.  cwbCO_Signon(),         */
/*     however, might not connect to validate the user ID and       */
/*     password, but instead may use recent results of a previous   */
/*     validation.  This is affected by recency of previous         */
/*     validation results as well as by the Validation Mode         */
/*     attribute of the given system object.                        */
/* - The password will be cached in the AS/400 password cache       */
/*     only in the case of the successful completion of             */
/*     cwbCO_Signon(), never as the result of a call to             */
/*     cwbCO_VerifyUserIDPassword().                                */
/* - cwbCO_VerifyUserIDPassword() will NEVER set the system object  */
/*     state to 'signed on', whereas a successful cwbCO_Signon()    */
/*     WILL change the state to 'signed on'.  This is important     */
/*     because when a system object is in a 'signed on' state, most */
/*     of its attributes may no longer be changed.                  */
/*                                                                  */
/* Similarities between this and cwbCO_VerifyUserIDPassword()       */
/* ----------------------------------------------------------       */
/*   - Both APIs, when using a connection to validate the user      */
/*     ID and password, also retrieve current data related to       */
/*     signon attempts.  This data can then be retrieved using      */
/*     the following APIs:                                          */
/*         cwbCO_GetSignonDate()                                    */
/*         cwbCO_GetPrevSignonDate()                                */
/*         cwbCO_GetPasswordExpireDate()                            */
/*         cwbCO_GetFailedSignons()                                 */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_Signon(
                             cwbCO_SysHandle       system,
                             cwbSV_ErrHandle       errorHandle );


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_HasSignedOn                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns an indication of whether or not the specified system   */
/*   object has "signed on" -- i.e. whether or not the user ID and  */
/*   password have been validated at some point in the life of the  */
/*   specified system object.                                       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   cwb_Boolean * signedOn - output                                */
/*     A pointer to a cwb_Boolean into which is stored the          */
/*     indication of signed-on-ness.  If the specified system       */
/*     object has signed on, it will be set to CWB_TRUE, otherwise  */
/*     it will be set to CWB_FALSE.  (On error it will be set to    */
/*     CWB_FALSE as well.)                                          */
/*                                                                  */
/* Return codes:                                                    */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - The signedOn pointer is NULL.            */
/*                                                                  */
/* Usage notes:                                                     */
/*   A returned indication of CWB_TRUE does not mean that the user  */
/*   ID and password have been validated within a certain time      */
/*   period, only that since the system object's creation a signon  */
/*   has occurred.  That signon may not have caused or included a   */
/*   connection and security validation flow to the AS/400 system.  */
/*   This means that, even if CWB_TRUE is returned, the next call   */
/*   to the system object that requires a successful signon might   */
/*   connect and attempt to re-validate the user ID and password,   */
/*   and that validation, and hence the signon, may fail.           */
/*                                                                  */
/*   The signedOn indicator reflects the results of the most        */
/*   recent user ID and password validation.  If user ID and        */
/*   password validation (signon) has occurred successfully at      */
/*   one time, but since then this validation has failed, signedOn  */
/*   will be set to CWB_FALSE.                                      */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_HasSignedOn(
                             cwbCO_SysHandle       system,
                             cwb_Boolean          *signedOn );



/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_VerifyUserIDPassword                                     */
/*                                                                  */
/* Purpose:                                                         */
/*   This function verifies the correctness of the user ID and      */
/*   password passed in, on the AS/400 system the specified system  */
/*   object represents.  If the user ID and password are correct,   */
/*   it also retrieves data related to signon attempts and password */
/*   expiration.                                                    */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   LPCSTR userID - input                                          */
/*     A pointer to a buffer that contains the NULL-terminated      */
/*     user ID. The maximum length is CWBCO_MAX_USER_ID + 1         */
/*     characters in length, including the NULL terminator.         */
/*                                                                  */
/*   LPCSTR password - input                                        */
/*     A pointer to a buffer that contains the NULL-terminated      */
/*     password. The maximum length is CWBCO_MAX_PASSWORD + 1       */
/*     bytes in length, including the NULL terminator.              */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input/output                     */
/*     Any returned messages will be written to this object.  It    */
/*     is created with the cwbSV_CreateErrHandle API.  The          */
/*     messages may be retrieved through the cwbSV_GetErrText API.  */
/*     If the parameter is set to zero, or if the errorHandle is    */
/*     invalid, no messages will be retrieved.                      */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - A pointer supplied to the API is not     */
/*                         valid.                                   */
/*   CWB_UNKNOWN_USERID - The supplied user ID is not               */
/*                        known to this system.                     */
/*   CWB_WRONG_PASSWORD - Password is not correct.                  */
/*   CWB_PASSWORD_EXPIRED - Password has expired.                   */
/*   CWB_USER_PROFILE_DISABLED - The user ID has been disabled.     */
/*   CWB_INVALID_PASSWORD - One or more characters in the           */
/*                          password is invalid or the password     */
/*                          is too long.                            */
/*   CWB_INVALID_USERID - One or more characters in the user ID     */
/*                        is invalid or the user ID is too long.    */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/*   Other return codes may be commonly returned as the result of   */
/*   a failed attempt to connect to the signon server.  For a list  */
/*   of such return codes see comments for cwbCO_Connect.           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   See comments for cwbCO_Signon() for information on how         */
/*   cwbCO_VerifyUserIDPassword() is different from and similar to  */
/*   that API.                                                      */
/*                                                                  */
/*   Valid password lengths depend on the current setting of the    */
/*   AS/400 system password level.  Password levels 0 and 1 allow   */
/*   passwords up to 10 characters in length. Password levels 2     */
/*   and 3 allow passwords up to 128 characters in length.          */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_VerifyUserIDPassword(
                             cwbCO_SysHandle       system,
                             LPCSTR                userID,
                             LPCSTR                password,
                             cwbSV_ErrHandle       errorHandle );
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_VerifyUserIDPasswordA(
                             cwbCO_SysHandle       system,
                             LPCSTR                userID,
                             LPCSTR                password,
                             cwbSV_ErrHandle       errorHandle );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbCO_VerifyUserIDPasswordW(
                              cwbCO_SysHandle       system,
                              LPCWSTR               userID,
                              LPCWSTR               password,
                              cwbSV_ErrHandle       errorHandle );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbCO_VerifyUserIDPassword            cwbCO_VerifyUserIDPasswordW
#elif (  defined(CWB_ANSI) &&  (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbCO_VerifyUserIDPassword            cwbCO_VerifyUserIDPasswordA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_GetSignonDate                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Retrieves the date and time of the current successful security */
/*   validation.                                                    */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   cwb_DateTime * signonDateTime - output                         */
/*     A pointer to a structure that will contain the date and time */
/*     the current signon occurred.                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - The pointer to the cwb_DateTime          */
/*                         structure is NULL.                       */
/*   CWB_INV_BEFORE_VALIDATE - The user ID and password set in the  */
/*                             specified system object have not     */
/*                             yet been validated, so this          */
/*                             information is not available.        */
/*                                                                  */
/* Usage Notes:                                                     */
/*   You must have successfully called                              */
/*   cwbCO_VerifyUserIDPassword(), cwbCO_Signon(), or               */
/*   cwbCO_Connect() before using this API.  If you want to         */
/*   guarantee that the value returned is recent, you must either   */
/*   call cwbCO_VerifyUserIDPassword() explicitly, or set the       */
/*   Validate Mode to CWBCO_VALIDATE_ALWAYS before you call         */
/*   cwbCO_Signon() or cwbCO_Connect().                             */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_GetSignonDate(
                             cwbCO_SysHandle       system,
                             cwb_DateTime         *signonDateTime);


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_GetPrevSignonDate                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Retrieves the date and time of the previous successful         */
/*   security validation.                                           */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   cwb_DateTime * signonDateTime - output                         */
/*     A pointer to a structure that will contain the date and time */
/*     the previous signon occurred.                                */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - The pointer to the cwb_DateTime          */
/*                         structure is NULL.                       */
/*   CWB_INV_BEFORE_VALIDATE - The user ID and password set in the  */
/*                             specified system object have not     */
/*                             yet been validated, so this          */
/*                             information is not available.        */
/*                                                                  */
/* Usage Notes:                                                     */
/*   You must have successfully called                              */
/*   cwbCO_VerifyUserIDPassword(), cwbCO_Signon(), or               */
/*   cwbCO_Connect() before using this API.  If you want to         */
/*   guarantee that the value returned is recent, you must either   */
/*   call cwbCO_VerifyUserIDPassword() explicitly, or set the       */
/*   Validate Mode to CWBCO_VALIDATE_ALWAYS before you call         */
/*   cwbCO_Signon() or cwbCO_Connect().                             */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_GetPrevSignonDate(
                             cwbCO_SysHandle       system,
                             cwb_DateTime         *signonDateTime);


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_GetPasswordExpireDate                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   Retrieves the date and time the password will expire for the   */
/*   current user on the AS/400 system.                             */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   cwb_DateTime * expirationDateTime - output                     */
/*     A pointer to a structure that will contain the date and time */
/*     when the password will expire for the current user ID.       */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - The pointer to the cwb_DateTime          */
/*                         structure is NULL.                       */
/*   CWB_INV_BEFORE_VALIDATE - The user ID and password that were   */
/*                             set in the specified system object   */
/*                             have not been validated (so the      */
/*                             password expire date is not          */
/*                             available), or validation has        */
/*                             occurred and the user profile        */
/*                             password expiration interval is set  */
/*                             to *NOMAX.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   You must have successfully called                              */
/*   cwbCO_VerifyUserIDPassword(), cwbCO_Signon(), or               */
/*   cwbCO_Connect() before using this API.  If you want to         */
/*   guarantee that the value returned is recent, you must either   */
/*   call cwbCO_VerifyUserIDPassword() explicitly, or set the       */
/*   Validate Mode to CWBCO_VALIDATE_ALWAYS before you call         */
/*   cwbCO_Signon() or cwbCO_Connect().                             */
/*                                                                  */
/*   If the user profile password expiration interval is set to     */
/*   *NOMAX, a password expire date does not exist.  To             */
/*   detect this case, first validate the user ID and password as   */
/*   noted above, and then, if successful, call                     */
/*   cwbCO_GetPasswordExpireDate.  A return code of                 */
/*   CWBCO_INV_BEFORE_VALIDATE means that the password expiration   */
/*   interval is set to *NOMAX.                                     */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_GetPasswordExpireDate(
                             cwbCO_SysHandle       system,
                             cwb_DateTime         *expirationDateTime);


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_GetFailedSignons                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Retrieves the number of unsuccessful security validation       */
/*   attempts since the last successful attempt.                    */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   PUSHORT numberFailedAttempts - output                          */
/*       A pointer to a short which will contain the number of      */
/*       failed logon attempts if this call is successful.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - The numberFailedAttempts pointer is      */
/*                         NULL.                                    */
/*   CWB_INV_BEFORE_VALIDATE - The user ID and password set in the  */
/*                             specified system object have not     */
/*                             yet been validated, so this          */
/*                             information is not available.        */
/*                                                                  */
/* Usage Notes:                                                     */
/*   You must have successfully called                              */
/*   cwbCO_VerifyUserIDPassword(), cwbCO_Signon(), or               */
/*   cwbCO_Connect() before using this API.  If you want to         */
/*   guarantee that the value returned is recent, you must either   */
/*   call cwbCO_VerifyUserIDPassword() explicitly, or set the       */
/*   Validate Mode to CWBCO_VALIDATE_ALWAYS before you call         */
/*   cwbCO_Signon() or cwbCO_Connect().                             */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_GetFailedSignons(
                             cwbCO_SysHandle       system,
                             PUSHORT               numberFailedAttempts);


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_ChangePassword                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Changes the password of the specified user on the AS/400       */
/*   system from a specified old to a specified new value.  This    */
/*   API does NOT use the user ID and password currently set in     */
/*   the given system object, nor does it change these values.      */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   LPCSTR userID - input                                          */
/*       A pointer to a buffer which contains the user ID.          */
/*       The maximum length is CWBCO_MAX_USER_ID + 1 characters,    */
/*       including the null terminator.                             */
/*                                                                  */
/*   LPCSTR oldPassword - input                                     */
/*       A pointer to a buffer which contains the old password.     */
/*       The maximum length is CWBCO_MAX_PASSWORD + 1 bytes,        */
/*       including the null terminator.                             */
/*                                                                  */
/*   LPCSTR newPassword - input                                     */
/*       A pointer to a buffer which contains the new password.     */
/*       The maximum length is CWBCO_MAX_PASSWORD + 1 bytes,        */
/*       including the null terminator.                             */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input/output                     */
/*     Any returned messages will be written to this object.  It    */
/*     is created with the cwbSV_CreateErrHandle API.  The          */
/*     messages may be retrieved through the cwbSV_GetErrText API.  */
/*     If the parameter is set to zero, or if the errorHandle is    */
/*     invalid, no messages will be retrieved.                      */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - A pointer parameter is NULL.             */
/*   CWB_GENERAL_SECURITY_ERROR - A general security error          */
/*                                occurred.  The user profile       */
/*                                does not have a password or the   */
/*                                password validation program       */
/*                                found an error in the password.   */
/*   CWB_INVALID_PASSWORD - One or more characters in the new       */
/*                          password is invalid or the password     */
/*                          is too long.                            */
/*   CWB_INVALID_USERID - One or more characters in the user ID     */
/*                        is invalid or the user ID is too long.    */
/*   CWB_UNKNOWN_USERID - The supplied user ID is not               */
/*                        known to this system.                     */
/*   CWB_WRONG_PASSWORD - Password is not correct.                  */
/*   CWB_USER_PROFILE_DISABLED - The user ID has been disabled.     */
/*   CWB_PW_TOO_LONG - New password longer than maximum             */
/*                     accepted length.                             */
/*   CWB_PW_TOO_SHORT - New password shorter than minimum           */
/*                      accepted length.                            */
/*   CWB_PW_REPEAT_CHARACTER - New password contains a character    */
/*                             used more than once.                 */
/*   CWB_PW_ADJACENT_DIGITS - New password has adjacent digits.     */
/*   CWB_PW_CONSECUTIVE_CHARS - New password contains a character   */
/*                              repeated consecutively.             */
/*   CWB_PW_PREVIOUSLY_USED - New password was previously used.     */
/*   CWB_PW_DISALLOWED_CHAR - New password uses an installation     */
/*                            disallowed character.                 */
/*   CWB_PW_NEED_NUMERIC - New password must contain at             */
/*                         least one numeric.                       */
/*   CWB_PW_MATCHES_OLD - New password matches old password         */
/*                        in one or more character positions.       */
/*   CWB_PW_NOT_ALLOWED - New password exists in a dictionary of    */
/*                        disallowed passwords.                     */
/*   CWB_PW_CONTAINS_USERID - New password contains user ID as      */
/*                            part of the password.                 */
/*   CWB_PW_LAST_INVALID_PWD - The next invalid password            */
/*                             will disable the user profile.       */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/*   Other return codes may be commonly returned as the result of   */
/*   a failed attempt to connect to the signon server.  For a list  */
/*   of such return codes see comments for cwbCO_Connect.           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Valid password lengths depend on the current setting of the    */
/*   AS/400 system password level.  Password levels 0 and 1 allow   */
/*   passwords up to 10 characters in length. Password levels 2     */
/*   and 3 allow passwords up to 128 characters in length.          */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_ChangePassword(
                             cwbCO_SysHandle       system,
                             LPCSTR                userID,
                             LPCSTR                oldPassword,
                             LPCSTR                newPassword,
                             cwbSV_ErrHandle       errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_ChangePasswordA(
                             cwbCO_SysHandle       system,
                             LPCSTR                userID,
                             LPCSTR                oldPassword,
                             LPCSTR                newPassword,
                             cwbSV_ErrHandle       errorHandle);
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbCO_ChangePasswordW(
                             cwbCO_SysHandle       system,
                             LPCWSTR               userID,
                             LPCWSTR               oldPassword,
                             LPCWSTR               newPassword,
                             cwbSV_ErrHandle       errorHandle);
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbCO_ChangePassword                 cwbCO_ChangePasswordW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbCO_ChangePassword                 cwbCO_ChangePasswordA
#endif // of UNICODE/ANSI selection



/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_GetSystemName                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   This function gets the AS/400 system name associated with      */
/*   the specified system object.                                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   LPSTR sysName - output                                         */
/*     Pointer to a buffer that will contain the NULL-terminated    */
/*     system name.  The name will be CWBCO_MAX_SYS_NAME characters */
/*     long at most, not including the NULL terminator.             */
/*                                                                  */
/*   PULONG length - input/output                                   */
/*     Pointer to the length of the sysName buffer.  If the buffer  */
/*     is too small to hold the system name, including room for the */
/*     terminating NULL, the size of the buffer needed will be      */
/*     filled into this parameter and CWB_BUFFER_OVERFLOW will be   */
/*     returned.                                                    */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - One of the pointer parameters passed     */
/*                         in is NULL.                              */
/*   CWB_BUFFER_OVERFLOW - The sysName buffer is not large enough   */
/*                         to hold the entire system name.          */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_GetSystemName(
                              cwbCO_SysHandle    system,
                              LPSTR              sysName,
                              PULONG             length );
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_GetSystemNameA(
                              cwbCO_SysHandle    system,
                              LPSTR              sysName,
                              PULONG             length );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbCO_GetSystemNameW(
                              cwbCO_SysHandle    system,
                              LPWSTR             sysName,
                              PULONG             length );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbCO_GetSystemName                   cwbCO_GetSystemNameW
#elif (  defined(CWB_ANSI) &&  (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbCO_GetSystemName                   cwbCO_GetSystemNameA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_UseSecureSockets                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Specify that all communication to the AS/400 system using the  */
/*   specified system object either must use secure sockets or      */
/*   must not.                                                      */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   cwb_Boolean useSecureSockets - input                           */
/*     Specifies whether or not to require secure sockets use when  */
/*     communicating with the AS/400 system the specified system    */
/*     object handle represents.  Use the appropriate value:        */
/*        CWB_TRUE  - require secure sockets use for communication  */
/*        CWB_FALSE - do not use secure sockets for communication   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_SECURE_SOCKETS_NOTAVAIL - Secure sockets is not            */
/*                                 available.  It may not be        */
/*                                 installed on the PC, it may      */
/*                                 be prohibited for this user,     */
/*                                 or it may not be available on    */
/*                                 the AS/400 system.               */
/*   CWB_RESTRICTED_BY_POLICY - A policy exists that prohibits      */
/*                              the user from changing this value.  */
/*   CWB_INV_AFTER_SIGNON - Signon has successfully occurred using  */
/*                          the specified system object, so this    */
/*                          setting may no longer be changed.       */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API cannot be used after a successful signon has occurred */
/*   for the specified system object.  A signon has occurred if     */
/*   either cwbCO_Signon() or cwbCO_Connect() has been called       */
/*   successfully for this system object.                           */
/*                                                                  */
/*   If you specify that secure sockets must be used, any attempt   */
/*   to communicate with the AS/400 system that cannot be completed */
/*   using secure sockets will fail.  Client Access may or may not  */
/*   be able to detect at the time this API is called if Secure     */
/*   Sockets will be available for use at connect time for this     */
/*   AS/400 system.                                                 */
/*                                                                  */
/*   Even if CWB_SECURE_SOCKETS_NOTAVAIL is NOT returned, it may    */
/*   be determined at a later time that secure sockets is not       */
/*   available.                                                     */
/*                                                                  */
/*   Although iSeries Access for Windows can, with limitations,     */
/*   enforce Federal Information Processing Standards (FIPS)        */
/*   compliance when SSL is used, this API does not control whether */
/*   it will be enforced or not.  The FIPS-compliance setting is    */
/*   not controllable programmatically.  It can be turned on or off */
/*   only using the checkbox in iSeries Access for Windows          */
/*   Properties by a user with Administrator privileges on the PC.  */
/*   For more information about FIPS and its use, see the User's    */
/*   Guide installed with iSeries Access for Windows.               */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_UseSecureSockets(
                             cwbCO_SysHandle    system,
                             cwb_Boolean        useSecureSockets );


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_IsSecureSockets                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   This function gets, for the specified system object, whether   */
/*   or not Secure Sockets is being used (if connected), or would   */
/*   be attempted (if not currently connected) for a connection.    */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   cwb_Boolean * inUse - output                                   */
/*     Returns whether or not Client Access is using, or will try   */
/*     to use, secure sockets for communication:                    */
/*       CWB_TRUE  - is in use or would be if connections active    */
/*       CWB_FALSE - NOT in use, would not try to use it            */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - The inUse pointer is NULL.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This flag is an indication of what Client Access will TRY to   */
/*   do for any future communications.  If CWB_TRUE is returned,    */
/*   then any attempt to communicate to the AS/400 system that      */
/*   cannot be performed using secure sockets will fail.            */
/*                                                                  */
/*   Although iSeries Access for Windows can, with limitations,     */
/*   enforce Federal Information Processing Standards (FIPS)        */
/*   compliance when SSL is used, this API does not return an       */
/*   indication of whether FIPS compliance is turned on or not.     */
/*   The FIPS-compliance switch cannot be checked programmatically. */
/*   It can be checked only by visually inspecting the FIPS         */
/*   compliance checkbox in iSeries Access for Windows Properties.  */
/*   For more information about FIPS and its use, see the User's    */
/*   Guide installed with iSeries Access for Windows.               */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_IsSecureSockets(
                             cwbCO_SysHandle    system,
                             cwb_Boolean       *inUse );


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_SetPortLookupMode                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   This function sets, for the specified system object, how       */
/*   a host server port lookup will be done.                        */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously by cwbCO_CreateSystem() or        */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   cwbCO_PortLookupMode mode - input                              */
/*     Specifies port lookup method.  Possible values are:          */
/*            CWBCO_PORT_LOOKUP_SERVER                              */
/*                Lookup of a host server port will be done by      */
/*                contacting the host (AS/400) server mapper each   */
/*                time the connection of a service is to be made    */
/*                when one does not yet exist.  The server mapper   */
/*                returns the port number that is then used to      */
/*                connect to the desired service on the AS/400      */
/*                system.                                           */
/*            CWBCO_PORT_LOOKUP_LOCAL                               */
/*                Lookup of a host server port will be done by      */
/*                lookup in the SERVICES file on the PC itself.     */
/*            CWBCO_PORT_LOOKUP_STANDARD                            */
/*                The "standard" port -- that set by default for    */
/*                a given host server and in use if no one has      */
/*                changed the services table on the AS/400 system   */
/*                for that service -- will be used to connect to    */
/*                the desired service.                              */
/*                                                                  */
/*     The latter two modes eliminate the AS/400 server mapper      */
/*     connection and its associated delay, network traffic, and    */
/*     load on the AS/400 system.                                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_PARAMETER - The mode parameter is an invalid       */
/*                           value.                                 */
/*   CWB_RESTRICTED_BY_POLICY - A policy exists that prohibits      */
/*                              the user from changing this value.  */
/*   CWB_INV_AFTER_SIGNON - Signon has successfully occurred using  */
/*                          the specified system object, so this    */
/*                          setting may no longer be changed.       */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API cannot be used after a successful signon has occurred */
/*   for the specified system object.  A signon has occurred if     */
/*   either cwbCO_Signon() or cwbCO_Connect() has been called       */
/*   successfully for this system object.                           */
/*                                                                  */
/*   Use CWBCO_PORT_LOOKUP_SERVER to be most certain of the         */
/*   accuracy of the port number for a service; however, this       */
/*   requires an extra connection to the server mapper on the       */
/*   AS/400 system every time a new connection to a service is      */
/*   to be made.                                                    */
/*                                                                  */
/*   Use CWBCO_PORT_LOOKUP_STANDARD to achieve the best             */
/*   performance, although if the system administrator has          */
/*   changed the ports of any Client Access host service in the     */
/*   service table on that AS/400 system, this mode will not work.  */
/*                                                                  */
/*   Use CWBCO_PORT_LOOKUP_LOCAL for best performance when the      */
/*   port for a Client Access host service has been changed on      */
/*   the AS/400 system represented by the system object.  For       */
/*   this to work, entries for each host service port must be       */
/*   added to a file on the PC named SERVICES.  Each such entry     */
/*   must contain first the standard name of the host service       */
/*   (for example, "as-rmtcmd" without the quotes) followed by      */
/*   spaces and the port number for that service.  The SERVICES     */
/*   file should be located in the Windows install directory in     */
/*   Windows 95/98, or in subdirectory system32\drivers\etc under   */
/*   the Windows NT install directory in Windows NT.                */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_SetPortLookupMode(
                             cwbCO_SysHandle       system,
                             cwbCO_PortLookupMode  mode );


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_GetPortLookupMode                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   This function gets, for the specified system object, the       */
/*   mode or method by which host service ports are looked up when  */
/*   needed by Client Access to establish a service connection.     */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously by cwbCO_CreateSystem() or        */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   cwbCO_PortLookupMode * mode - output                           */
/*     Returns the host service port lookup mode.                   */
/*     See comments for cwbCO_SetPortLookupMode() for possible      */
/*     values and their meanings.                                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - The mode pointer is NULL.                */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_GetPortLookupMode(
                             cwbCO_SysHandle         system,
                             cwbCO_PortLookupMode   *mode );


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_SetIPAddressLookupMode                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   This function sets, for the specified system object, when      */
/*   Client Access will dynamically lookup the AS/400 system's      */
/*   IP address when a connection is to be made.  If the system     */
/*   name specified when cwbCO_CreateSystem() or                    */
/*   cwbCO_CreateSystemLike() was called is an actual IP address    */
/*   itself, this setting is ignored, since Client Access never     */
/*   needs to lookup the address.                                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   cwbCO_IPAddressLookupMode mode - input                         */
/*     Specifies when the dynamic address lookup can occur.         */
/*     Possible values are:                                         */
/*            CWBCO_IPADDR_LOOKUP_ALWAYS                            */
/*                Every time a connection is to occur, dynamically  */
/*                lookup the AS/400 system's IP address.            */
/*            CWBCO_IPADDR_LOOKUP_1HOUR                             */
/*                Lookup the IP address dynamically if it has been  */
/*                at least 1 hour since the last lookup for         */
/*                this AS/400 system.                               */
/*            CWBCO_IPADDR_LOOKUP_1DAY                              */
/*                Lookup the IP address dynamically if it has been  */
/*                at least 1 day since the last lookup for this     */
/*                AS/400 system.                                    */
/*            CWBCO_IPADDR_LOOKUP_1WEEK                             */
/*                Lookup the IP address dynamically if it has been  */
/*                at least 1 week since the last lookup for this    */
/*                AS/400 system.                                    */
/*            CWBCO_IPADDR_LOOKUP_NEVER                             */
/*                Never dynamically lookup the IP address of this   */
/*                AS/400 system, always use the IP address that was */
/*                last used for this AS/400 system on this PC.      */
/*            CWBCO_IPADDR_LOOKUP_AFTER_STARTUP                     */
/*                Lookup the IP address dynamically if Windows has  */
/*                been re-started since the last lookup for this    */
/*                AS/400 system.                                    */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_PARAMETER - The mode parameter is an invalid       */
/*                           value.                                 */
/*   CWB_RESTRICTED_BY_POLICY - A policy exists that prohibits      */
/*                              the user from changing this value.  */
/*   CWB_INV_AFTER_SIGNON - Signon has successfully occurred using  */
/*                          the specified system object, so this    */
/*                          setting may no longer be changed.       */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API cannot be used after a successful signon has occurred */
/*   for the specified system object.  A signon has occurred if     */
/*   either cwbCO_Signon() or cwbCO_Connect() has been called       */
/*   successfully for this system object.                           */
/*                                                                  */
/*   Setting this to a value other than CWB_IPADDR_LOOKUP_ALWAYS    */
/*   could shorten the time to connect to the AS/400 system, since  */
/*   the dynamic lookup may cause network traffic and take many     */
/*   seconds to complete.  If the dynamic lookup is not performed,  */
/*   there is a risk that the IP address of the AS/400 system will  */
/*   have changed and a connection will either fail or will be made */
/*   to the wrong AS/400 system.                                    */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_SetIPAddressLookupMode(
                             cwbCO_SysHandle            system,
                             cwbCO_IPAddressLookupMode  mode );


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_GetIPAddressLookupMode                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   This function gets, for the specified system object, the       */
/*   indication of when, if ever, the AS/400 system's IP address    */
/*   will be dynamically looked up.                                 */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously by cwbCO_CreateSystem() or        */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   cwbCO_IPAddressLookupMode * mode - output                      */
/*     Returns the IP address lookup mode currently in use.         */
/*     See comments for cwbCO_SetIpAddressLookupMode() for          */
/*     possible values and their meanings.                          */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - The mode pointer is NULL.                */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_GetIPAddressLookupMode(
                             cwbCO_SysHandle              system,
                             cwbCO_IPAddressLookupMode   *mode );


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_SetConnectTimeout                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   This function sets, for the specified system object, the       */
/*   number of seconds Client Access will wait before giving up     */
/*   on a connection attempt and returning an error.                */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   ULONG timeout - input                                          */
/*     Specifies the connection timeout value, in seconds.          */
/*     The value must be from CWBCO_CONNECT_TIMEOUT_MIN to          */
/*     CWBCO_CONNECT_TIMEOUT_MAX, or if no timeout is desired,      */
/*     use CWBCO_CONNECT_TIMEOUT_NONE.  If the value is below the   */
/*     minimum, then CWBCO_CONNECT_TIMEOUT_MIN will be used; if it  */
/*     is above the maximum, CWBCO_CONNECT_TIMEOUT_MAX will be      */
/*     used.                                                        */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*                                                                  */
/* Usage Notes:                                                     */
/*   If no timeout value has been suggested by policy, and none     */
/*   has been explicitly set using this API, the connect timeout    */
/*   used is CWBCO_CONNECT_TIMEOUT_DEFAULT.                         */
/*                                                                  */
/*   The TCP/IP stack itself might give up on a connection attempt  */
/*   before Client Access would.  In this case, Client Access will  */
/*   not wait any longer, but will report the error.                */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_SetConnectTimeout(
                             cwbCO_SysHandle            system,
                             ULONG                      timeout );


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_GetConnectTimeout                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   This function gets, for the specified system object, the       */
/*   connection timeout value, in seconds, currently set.           */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously by cwbCO_CreateSystem() or        */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   PULONG timeout - output                                        */
/*     Returns the timeout value, in seconds.  This value will be   */
/*     from CWBCO_CONNECT_TIMEOUT_MIN to CWBCO_CONNECT_TIMEOUT_MAX, */
/*     or will be CWBCO_CONNECT_TIMEOUT_NONE if no connection       */
/*     timeout is desired.                                          */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - The timeout pointer is NULL.             */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_GetConnectTimeout(
                             cwbCO_SysHandle              system,
                             PULONG                       timeout );


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_SetIPAddress                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   This function sets, for the specified system object, the       */
/*   IP address that will be used to connect to the AS/400 system,  */
/*   and changes the IP Address Lookup Mode for the system object   */
/*   to CWBCO_IPADDR_LOOKUP_NEVER.  These changes will NOT affect   */
/*   any other system object that exists or is created later.       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   LPCSTR IPAddress - input                                       */
/*     Specifies the IP address as a character string, in dotted    */
/*     decimal notation ("nnn.nnn.nnn.nnn"), where each "nnn" is    */
/*     a decimal value ranging from 0 to 255.  The IPAddress must   */
/*     not be longer than CWBCO_MAX_IP_ADDRESS characters.          */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_PARAMETER - The IPAddress parameter does not       */
/*                           contain a valid IP address.            */
/*   CWB_RESTRICTED_BY_POLICY - A policy exists that prohibits      */
/*                              the user from changing this value.  */
/*   CWB_INV_AFTER_SIGNON - Signon has successfully occurred using  */
/*                          the specified system object, so this    */
/*                          setting may no longer be changed.       */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API cannot be used after a successful signon has occurred */
/*   for the specified system object.  A signon has occurred if     */
/*   either cwbCO_Signon() or cwbCO_Connect() has been called       */
/*   successfully for this system object.                           */
/*                                                                  */
/*   Use this API to force use of a specific IP address whenever    */
/*   any connection is made using the specified system object.      */
/*   Since the IP Address Lookup Mode is set to NEVER lookup the    */
/*   IP address, the address specified will always be used, unless  */
/*   before a connect or signon occurs, the IP Address Lookup Mode  */
/*   is changed by calling cwbCO_SetIPAddressLookupMode().          */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_SetIPAddress(
                              cwbCO_SysHandle    system,
                              LPCSTR             IPAddress );
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_SetIPAddressA(
                              cwbCO_SysHandle    system,
                              LPCSTR             IPAddress );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbCO_SetIPAddressW(
                              cwbCO_SysHandle    system,
                              LPCWSTR            IPAddress );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbCO_SetIPAddress                   cwbCO_SetIPAddressW
#elif (  defined(CWB_ANSI) &&  (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbCO_SetIPAddress                   cwbCO_SetIPAddressA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_GetIPAddress                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   This function gets, for the specified system object, the       */
/*   IP address of the AS/400 system it represents.  This is the    */
/*   IP address that was used to connect to the AS/400 system       */
/*   (or set some other way, such as by using cwbCO_SetIPAddress)   */
/*   and will be used for later connections, when using the         */
/*   specified system object.                                       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously by cwbCO_CreateSystem() or        */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   LPSTR IPAddress - output                                       */
/*     Pointer to a buffer that will contain the NULL-terminated    */
/*     IP address in dotted-decimal notation -- that is, in the     */
/*     form "nnn.nnn.nnn.nnn" where each "nnn" is in the range      */
/*     0 to 255.                                                    */
/*                                                                  */
/*   PULONG length - input/output                                   */
/*     Pointer to the length of the IPAddress buffer.  If the       */
/*     buffer is too small to hold the output, including room for   */
/*     the terminating NULL, the size of the buffer needed will be  */
/*     filled into this parameter and CWB_BUFFER_OVERFLOW will be   */
/*     returned.                                                    */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - One of the input pointers is NULL.       */
/*   CWB_BUFFER_OVERFLOW - The IPAddress buffer is not large enough */
/*                         to hold the entire IPAddress string.     */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_GetIPAddress(
                              cwbCO_SysHandle    system,
                              LPSTR              IPAddress,
                              PULONG             length );
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbCO_GetIPAddressA(
                              cwbCO_SysHandle    system,
                              LPSTR              IPAddress,
                              PULONG             length );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbCO_GetIPAddressW(
                              cwbCO_SysHandle    system,
                              LPWSTR             IPAddress,
                              PULONG             length );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbCO_GetIPAddress                   cwbCO_GetIPAddressW
#elif (  defined(CWB_ANSI) &&  (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbCO_GetIPAddress                   cwbCO_GetIPAddressA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_CanModifyDefaultUserMode                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   Indicates whether or not the default user mode for the         */
/*   specified system object may be modified.                       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   cwb_Boolean *canModify - output                                */
/*     Set to CWB_TRUE if this mode may be modified, otherwise      */
/*     set to CWB_FALSE.                                            */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - The canModify pointer is NULL.           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This value may not be modified if policy settings prohibit     */
/*   its modification, or if a successful signon or connection      */
/*   using the specified system object has already occurred.  In    */
/*   these cases, canModify will be set to CWB_FALSE.               */
/*                                                                  */
/*   The results returned from this API are correct only at the     */
/*   time of the call.  If policy settings are changed or a signon  */
/*   or connection is performed using this system object, the       */
/*   results of this API could become incorrect.  This must be      */
/*   considered and managed, especially in a multi-threaded         */
/*   application.                                                   */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_CanModifyDefaultUserMode(
                             cwbCO_SysHandle         system,
                             cwb_Boolean            *canModify );


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_CanModifyIPAddressLookupMode                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Indicates whether or not the IP Address Lookup Mode may be     */
/*   modified for this system object.                               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   cwb_Boolean *canModify - output                                */
/*     Set to CWB_TRUE if this mode may be modified, otherwise      */
/*     set to CWB_FALSE.                                            */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - The canModify pointer is NULL.           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This value may not be modified if policy settings prohibit     */
/*   its modification, or if a successful signon or connection      */
/*   using the specified system object has already occurred.  In    */
/*   these cases, canModify will be set to CWB_FALSE.               */
/*                                                                  */
/*   The results returned from this API are correct only at the     */
/*   time of the call.  If policy settings are changed or a signon  */
/*   or connection is performed using this system object, the       */
/*   results of this API could become incorrect.  This must be      */
/*   considered and managed, especially in a multi-threaded         */
/*   application.                                                   */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_CanModifyIPAddressLookupMode(
                             cwbCO_SysHandle         system,
                             cwb_Boolean            *canModify );


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_CanModifyIPAddress                                       */
/*                                                                  */
/* Purpose:                                                         */
/*   Indicates whether or not the IP Address used to connect may    */
/*   be modified for this system object.                            */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   cwb_Boolean *canModify - output                                */
/*     Set to CWB_TRUE if the IP Address may be modified, otherwise */
/*     set to CWB_FALSE.                                            */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - The canModify pointer is NULL.           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This value may not be modified if policy settings prohibit     */
/*   its modification, or if a successful signon or connection      */
/*   using the specified system object has already occurred.  In    */
/*   these cases, canModify will be set to CWB_FALSE.               */
/*                                                                  */
/*   This value may not be modified if the IP Address Lookup Mode   */
/*   is not CWBCO_IPADDR_LOOKUP_NEVER, and policy settings          */
/*   prohibit modification of the IP Address Lookup Mode.  In       */
/*   that case, canModify will be set to CWB_FALSE.                 */
/*                                                                  */
/*   The results returned from this API are correct only at the     */
/*   time of the call.  If policy settings are changed or a signon  */
/*   or connection is performed using this system object, the       */
/*   results of this API could become incorrect.  This must be      */
/*   considered and managed, especially in a multi-threaded         */
/*   application.                                                   */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_CanModifyIPAddress(
                             cwbCO_SysHandle         system,
                             cwb_Boolean            *canModify );


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_CanModifyPortLookupMode                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   Indicates whether or not the port lookup mode for the          */
/*   specified system object may be modified.                       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   cwb_Boolean *canModify - output                                */
/*     Set to CWB_TRUE if this mode may be modified, otherwise      */
/*     set to CWB_FALSE.                                            */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - The canModify pointer is NULL.           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This value may not be modified if policy settings prohibit     */
/*   its modification, or if a successful signon or connection      */
/*   using the specified system object has already occurred.  In    */
/*   these cases, canModify will be set to CWB_FALSE.               */
/*                                                                  */
/*   The results returned from this API are correct only at the     */
/*   time of the call.  If policy settings are changed or a signon  */
/*   or connection is performed using this system object, the       */
/*   results of this API could become incorrect.  This must be      */
/*   considered and managed, especially in a multi-threaded         */
/*   application.                                                   */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_CanModifyPortLookupMode(
                             cwbCO_SysHandle         system,
                             cwb_Boolean            *canModify );


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_CanModifyPersistenceMode                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   Indicates whether or not the persistence mode for the          */
/*   specified system object may be modified.                       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   cwb_Boolean *canModify - output                                */
/*     Set to CWB_TRUE if this mode may be modified, otherwise      */
/*     set to CWB_FALSE.                                            */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - The canModify pointer is NULL.           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This value may not be modified if policy settings prohibit     */
/*   its modification, or if a successful signon or connection      */
/*   using the specified system object has already occurred.  In    */
/*   these cases, canModify will be set to CWB_FALSE.               */
/*                                                                  */
/*   The results returned from this API are correct only at the     */
/*   time of the call.  If policy settings are changed or a signon  */
/*   or connection is performed using this system object, the       */
/*   results of this API could become incorrect.  This must be      */
/*   considered and managed, especially in a multi-threaded         */
/*   application.                                                   */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_CanModifyPersistenceMode(
                             cwbCO_SysHandle         system,
                             cwb_Boolean            *canModify );


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_CanModifyUseSecureSockets                                */
/*                                                                  */
/* Purpose:                                                         */
/*   Indicates whether or not the secure sockets use setting may    */
/*   be modified for this system object.                            */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   cwb_Boolean *canModify - output                                */
/*     Set to CWB_TRUE if the secure sockets use setting may be     */
/*     modified, otherwise set to CWB_FALSE.                        */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - The canModify pointer is NULL.           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This value may not be modified if policy settings prohibit     */
/*   its modification, or if a successful signon or connection      */
/*   using the specified system object has already occurred.  In    */
/*   these cases, canModify will be set to CWB_FALSE.               */
/*                                                                  */
/*   The results returned from this API are correct only at the     */
/*   time of the call.  If policy settings are changed or a signon  */
/*   or connection is performed using this system object, the       */
/*   results of this API could become incorrect.  This must be      */
/*   considered and managed, especially in a multi-threaded         */
/*   application.                                                   */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_CanModifyUseSecureSockets(
                             cwbCO_SysHandle         system,
                             cwb_Boolean            *canModify );



/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_GetHostCCSID                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the associated CCSID of the AS/400 system represented  */
/*   by the given system object, that was in use when the signon    */
/*   to the AS/400 system occurred, and is associated with the      */
/*   user ID set in the sytem object.                               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   PULONG pCCSID - output                                         */
/*     The host CCSID is copied into here if successful.            */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid system handle.                */
/*   CWB_INVALID_POINTER - the CCSID pointer is NULL.               */
/*   CWB_DEFAULT_HOST_CCSID_USED - Host CCSID 500 is returned       */
/*                                 because this API is unable to    */
/*                                 determine the host CCSID         */
/*                                 appropriate for the userid as    */
/*                                 set in the system object.        */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API does not make or require an active connection to the  */
/*   host system to retrieve the associated CCSID value. However,   */
/*   it does depend on a prior successful connection to the host    */
/*   system using the same user ID as is set in the specified       */
/*   system object.  This is because the CCSID returned is the one  */
/*   from the specific user profile, NOT the AS/400 system's        */
/*   default CCSID.  To retrieve a host CCSID without requiring     */
/*   a user ID, call cwbNL_GetHostCCSID.                            */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_GetHostCCSID(
                             cwbCO_SysHandle         system,
                             PULONG                  pCCSID );



/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbCO_GetHostVersionEx                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the version and release level of the host.                 */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle system - input                                 */
/*     Handle returned previously from cwbCO_CreateSystem() or      */
/*     cwbCO_CreateSystemLike().  It identifies the AS/400 system.  */
/*                                                                  */
/*   PULONG version - output                                        */
/*     Pointer to a buffer where the version level of the system    */
/*     is returned.                                                 */
/*                                                                  */
/*   PULONG release - output                                        */
/*     Pointer to a buffer where the release level of the system    */
/*     is returned.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*  The following list shows common return values.                  */
/*   CWB_OK - Successful Completion.                                */
/*   CWB_NOT_CONNECTED - The system has never been connected to     */
/*                       when using the currently active            */
/*                       environment.                               */
/*   CWB_INVALID_POINTER - One of the pointers passed in is NULL.   */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                to allocate a temporary buffer.                   */
/*                                                                  */
/*   Other return codes may be commonly returned as the result of   */
/*   a failed attempt to connect to the AS/400 system if CWB_TRUE   */
/*   was specified for the refresh parameter.  For a list of        */
/*   such common return codes, see the comments for cwbCO_Connect.  */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The host version is retrieved and saved whenever a connection  */
/*   is made to the AS/400 system.  If no connection has been made  */
/*   yet to this AS/400 system in the currently-active enrironment, */
/*   this information will not be available, and the error code     */
/*   CWB_NOT_CONNECTED will be returned.  If you know that a        */
/*   connection to the AS/400 system was recently made              */
/*   successfully, it is likely that the version and release        */
/*   levels returned are current.  If you want to make sure that    */
/*   the values are available and have been retrieved recently,     */
/*   call cwbCO_Signon or cwbCO_Connect for this system object      */
/*   first, then call cwbCO_GetHostVersionEx.                       */
/*                                                                  */
/********************************************************************/
UINT CWB_ENTRY cwbCO_GetHostVersionEx(
                             cwbCO_SysHandle         system,
                             PULONG                  version,
                             PULONG                  release);


#ifdef __cplusplus
}
#endif


#endif /* NOCWBCOSYSAPI */


#endif /* _CWBCOSYS_H_ */


