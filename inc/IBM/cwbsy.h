/********************************************************************/
/*                                                                  */
/* 5722-XE1                                                         */
/* (C) Copyright IBM Corp. 1995,2000                                */
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
/*   CWBSY.H                                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   It contains the declarations for the following API's:          */
/*                                                                  */
/*   cwbSY_CreateSecurityObj                                        */
/*   cwbSY_DeleteSecurityObj                                        */
/*                                                                  */
/*   cwbSY_SetSys                                                   */
/*   cwbSY_SetSysA                                                  */
/*   cwbSY_SetSysW                                                  */
/*                                                                  */
/*   cwbSY_VerifyUserIDPwd                                          */
/*   cwbSY_VerifyUserIDPwdA                                         */
/*   cwbSY_VerifyUserIDPwdW                                         */
/*                                                                  */
/*   cwbSY_ChangePwd                                                */
/*   cwbSY_ChangePwdA                                               */
/*   cwbSY_ChangePwdW                                               */
/*                                                                  */
/*   cwbSY_GetUserID                                                */
/*   cwbSY_GetUserIDA                                               */
/*   cwbSY_GetUserIDW                                               */
/*                                                                  */
/*   cwbSY_Logon                                                    */
/*                                                                  */
/*   cwbSY_LogonUser                                                */
/*   cwbSY_LogonUserA                                               */
/*   cwbSY_LogonUserW                                               */
/*                                                                  */
/*   cwbSY_GetDateTimeCurrentSignon                                 */
/*   cwbSY_GetDateTimeLastSignon                                    */
/*   cwbSY_GetDateTimePwdExpires                                    */
/*   cwbSY_GetFailedAttempts                                        */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/*   Important note:                                                */
/*   ---------------                                                */
/*   If you developing an application using the Client Access       */
/*   Express toolkit (v4r4m0 or greater), use the security related  */
/*   API's defined in the cwbcosys.h header (System Object API's)   */
/*   instead of the API's defined in this header. These API's are   */
/*   only provided to maintain compatibility with older versions    */
/*   of Client Access, and should not be used when developing a     */
/*   new application.                                               */
/*                                                                  */
/*   Link with the CWBAPI.LIB import library.                       */
/*   This module is to be used in conjunction with CWBSY.DLL.       */
/*                                                                  */
/*   The Security Function allows you to manage the Security of     */
/*   your information through password control.  The Security APIs  */
/*   allow you to:                                                  */
/*     Logon to an AS/400 system                                    */
/*     Verify your user ID and password on an AS/400 system         */
/*     Change your password on an AS/400 system                     */
/*     Retrieve information about your user ID, such as:            */
/*     - Date and time your password will expire                    */
/*     - Date and time of the last successful logon attempt         */
/*     - Date and time of the current signon                        */
/*     - Number of failed signon attempts                           */
/*                                                                  */
/*   In addition to the return codes listed for APIs additional     */
/*   operating system specific return codes may also appear.  The   */
/*   precise meaning of these return codes can be found in the      */
/*   operating system manuals or relevant header files.             */
/*                                                                  */
/********************************************************************/

/* Prevent multiple includes */
#if !defined( _CWBSY_H_ )
  #define     _CWBSY_H_

#include <windows.h>

#include "cwb.h"

#if defined( __cplusplus )
extern "C" {
#endif


/*------------------------------------------------------------------*/
/* TYPEDEFS                                                         */
/*------------------------------------------------------------------*/
typedef cwb_Handle cwbSY_SecurityHandle;

/*------------------------------------------------------------------*/
/* DEFINES: for string lengths (includes room for terminating null) */
/*                                                                  */
/*  Note: To take advantage of the longer passwords allowed on      */
/*        v5r1m0 (or greater) systems, use the API's defined in     */
/*        cwbcosys.h                                                */
/*------------------------------------------------------------------*/
#define CWBSY_MAX_SYSTEM_NAME   255+1
#define CWBSY_MAX_USER_ID       10+1
#define CWBSY_MAX_PASSWORD      10+1 

/*------------------------------------------------------------------*/
/* DEFINES: for date/time return values                             */
/*------------------------------------------------------------------*/
#define CWBSY_DATE_TIME_LEN         8

/*------------------------------------------------------------------*/
/* RETURN CODES: start at CWB_LAST+1 which is defined in CWB.H      */
/*------------------------------------------------------------------*/
#define CWBSY_START CWB_LAST+1

/*------------------------------------------------------------------*/
/*   User ID does not exist.                                        */
/*------------------------------------------------------------------*/
#define CWBSY_UNKNOWN_USERID           CWBSY_START

/*------------------------------------------------------------------*/
/*   Password is not correct for specified user ID.                 */
/*------------------------------------------------------------------*/
#define CWBSY_WRONG_PASSWORD           CWBSY_START+2

/*------------------------------------------------------------------*/
/*   Password has expired.                                          */
/*------------------------------------------------------------------*/
#define CWBSY_PASSWORD_EXPIRED         CWBSY_START+3

/*------------------------------------------------------------------*/
/*   One or more characters in the password is not valid or the     */
/*   password is too long.                                          */
/*------------------------------------------------------------------*/
#define CWBSY_INVALID_PASSWORD         CWBSY_START+4

/*------------------------------------------------------------------*/
/*   A general security error occurred.  The user profile does not  */
/*   have a password or the password validation program found an    */
/*   error in the password.                                         */
/*------------------------------------------------------------------*/
#define CWBSY_GENERAL_SECURITY_ERROR   CWBSY_START+7

/*------------------------------------------------------------------*/
/*   The AS/400 user profile is not valid.                          */
/*  ----------------------------------------------------------------*/
#define CWBSY_INVALID_PROFILE          CWBSY_START+9

/*------------------------------------------------------------------*/
/*   The AS/400 user profile (user ID) has been set to disabled.    */
/*------------------------------------------------------------------*/
#define CWBSY_USER_PROFILE_DISABLED    CWBSY_START+11

/*------------------------------------------------------------------*/
/*   The user canceled from the user ID/password prompt.            */
/*------------------------------------------------------------------*/
#define CWBSY_USER_CANCELLED           CWBSY_START+13

/*------------------------------------------------------------------*/
/*   One or more characters in the user ID is not valid or the      */
/*   user ID is too long.                                           */
/*------------------------------------------------------------------*/
#define CWBSY_INVALID_USERID           CWBSY_START+15

/*------------------------------------------------------------------*/
/*   The system specified is unknown.                               */
/*------------------------------------------------------------------*/
#define CWBSY_UNKNOWN_SYSTEM           CWBSY_START+16

/*------------------------------------------------------------------*/
/*   The PC could not validate the AS/400 security server.  This    */
/*   could indicate tampering with the IBM supplied security server */
/*   program on the AS/400.                                         */
/*------------------------------------------------------------------*/
#define CWBSY_TP_NOT_VALID             CWBSY_START+19

/*------------------------------------------------------------------*/
/*   There is no user currently logged on for the specified system. */
/*------------------------------------------------------------------*/
#define CWBSY_NOT_LOGGED_ON            CWBSY_START+22

/*------------------------------------------------------------------*/
/*   The system specified in the security object has not been       */
/*   configured.                                                    */
/*------------------------------------------------------------------*/
#define CWBSY_SYSTEM_NOT_CONFIGURED    CWBSY_START+25

/*------------------------------------------------------------------*/
/*   The user ID and password defined in the object has not yet     */
/*   been verified.   You must verify using cwbSY_verifyUserIDPwd   */
/*   API.                                                           */
/*------------------------------------------------------------------*/
#define CWBSY_NOT_VERIFIED             CWBSY_START+26

/*------------------------------------------------------------------*/
/*   Internal error. Contact IBM Service.                           */
/*------------------------------------------------------------------*/
#define CWBSY_INTERNAL_ERROR           CWBSY_START+255

/*------------------------------------------------------------------*/
/*   Change password errors                                         */
/*------------------------------------------------------------------*/

/*------------------------------------------------------------------*/
/*   The new password contains too many characters.  The maximum    */
/*   number of characters allowed is defined by the AS/400 system   */
/*   value, QPWDMAXLEN.                                             */
/*------------------------------------------------------------------*/
#define CWBSY_PWD_TOO_LONG             CWBSY_START+257

/*------------------------------------------------------------------*/
/*   The new password does not contain enough characters. The       */
/*   The minimum number of characters allowed is defined by the     */
/*   AS/400 system value, QPWDMINLEN.                               */
/*------------------------------------------------------------------*/
#define CWBSY_PWD_TOO_SHORT            CWBSY_START+258

/*------------------------------------------------------------------*/
/*   The new password contains a character used more than once.     */
/*   The AS/400 configuration (system value QPWDLMTREP) does not    */
/*   allow passwords to contain a repeat character.                 */
/*------------------------------------------------------------------*/
#define CWBSY_PWD_REPEAT_CHARACTER     CWBSY_START+259

/*------------------------------------------------------------------*/
/*   The new password contains two numbers next to each other.  The */
/*   The AS/400 configuration (system value QPWDLMTAJC) does not    */
/*   allow passwords to contain consecutive digits.                 */
/*------------------------------------------------------------------*/
#define CWBSY_PWD_ADJACENT_DIGITS      CWBSY_START+260

/*------------------------------------------------------------------*/
/*   The new password contains a character repeated consecutively.  */
/*   The AS/400 configuration (system value QPWDLMTREP) does not    */
/*   allow a password to contain a character repeated consecutively.*/
/*------------------------------------------------------------------*/
#define CWBSY_PWD_CONSECUTIVE_CHARS    CWBSY_START+261

/*------------------------------------------------------------------*/
/*   The new password matches a previously used password.  The      */
/*   AS/400 configuration (system value QPWDRQDDIF) requires new    */
/*   passwords to be different than any previous password.          */
/*------------------------------------------------------------------*/
#define CWBSY_PWD_PREVIOUSLY_USED      CWBSY_START+262

/*------------------------------------------------------------------*/
/*   The new password uses an installation disallowed character.    */
/*   AS/400 configuration (system value QPWDLMTCHR) restricts       */
/*   certain characters from being used in new passwords.           */
/*------------------------------------------------------------------*/
#define CWBSY_PWD_DISALLOWED_CHAR      CWBSY_START+263

/*------------------------------------------------------------------*/
/*   The new password must contain a number.   The AS/400           */
/*   configuration (system value QPWDRQDDGT) requires new passwords */
/*   contain one or more numeric digits.                            */
/*------------------------------------------------------------------*/
#define CWBSY_PWD_NEED_NUMERIC         CWBSY_START+264

/*------------------------------------------------------------------*/
/*   The new password matches an old password in one or more        */
/*   character positions.  The AS/400 configuration (system value   */
/*   QPWDPOSDIF) does not allow the same character to be in the     */
/*   same position as a previous password.                          */
/*------------------------------------------------------------------*/
#define CWBSY_PWD_MATCHES_OLD          CWBSY_START+266

/*------------------------------------------------------------------*/
/*   The password was rejected                                      */
/*------------------------------------------------------------------*/
#define CWBSY_PWD_NOT_ALLOWED          CWBSY_START+267

/*------------------------------------------------------------------*/
/*   The password matches the user ID.                              */
/*------------------------------------------------------------------*/
#define CWBSY_PWD_MATCHES_USERID       CWBSY_START+268

/*------------------------------------------------------------------*/
/*   The old password was created on a pre-V3 system which used a   */
/*   different encryption technique.  Password must be changed      */
/*   manually on the AS/400.                                        */
/*------------------------------------------------------------------*/
#define CWBSY_PWD_PRE_V3               CWBSY_START+269

/*------------------------------------------------------------------*/
/*   The next invalid will disable the user profile.                */
/*------------------------------------------------------------------*/
#define CWBSY_LAST_INVALID_PASSWORD    CWBSY_START+270


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSY_ChangePwd                                                */
/*                                                                  */
/* Purpose:                                                         */
/*   Changes the password on the specified AS/400 system.           */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSY_SecurityHandle securityHandle - input                    */
/*       A valid handle to a security object.  The handle           */
/*       is obtained using cwbSY_CreateSecurityObj.                 */
/*                                                                  */
/*   const char * userID - input                                    */
/*       A pointer to an ASCIIZ string which contains the user ID.  */
/*       The maximum length allowed is defined by CWBSY_MAX_USER_ID.*/
/*                                                                  */
/*   const char * oldPassword - input                               */
/*       A pointer to an ASCIIZ string which contains the current   */
/*       password.  The maximum length allowed is defined by        */
/*       CWBSY_MAX_PASSWORD.                                        */
/*                                                                  */
/*   const char * newPassword - input                               */
/*       A pointer to an ASCIIZ string which contains the new       */
/*       password.  The maximum length allowed is defined by        */
/*       CWBSY_MAX_PASSWORD.                                        */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
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
/*   CWB_INVALID_HANDLE - The security handle supplied is           */
/*                        not valid.                                */
/*   CWB_INVALID_POINTER - A pointer supplied to the API is not     */
/*                         valid.                                   */
/*   CWB_COMMUNICATIONS_ERROR - A communication error occurred      */
/*                              when attempting to contact the      */
/*                              system.                             */
/*   CWBSY_SYSTEM_NOT_CONFIGURED - The system has not been          */
/*                                 configured.                      */
/*   CWBSY_GENERAL_SECURITY_ERROR - A general security error        */
/*                                  occurred.  The user profile     */
/*                                  does not have a password or the */
/*                                  password validation program     */
/*                                  found an error in the password. */
/*   CWBSY_INVALID_PASSWORD - One or more characters in the         */
/*                            password is invalid or the password   */
/*                            is too long.                          */
/*   CWBSY_INVALID_USERID - One or more characters in the user ID   */
/*                          is invalid or the user ID is too long.  */
/*   CWBSY_UNKNOWN_USERID - The supplied user ID is not             */
/*                          known to this system.                   */
/*   CWBSY_WRONG_PASSWORD - Password is not correct.                */
/*   CWBSY_USER_PROFILE_DISABLED - The user ID has been disabled.   */
/*   CWBSY_PWD_TOO_LONG - New password longer than maximum          */
/*                       accepted length.                           */
/*   CWBSY_PWD_TOO_SHORT - New password shorter than minimum        */
/*                        accepted length.                          */
/*   CWBSY_PWD_REPEAT_CHARACTER - New password contains a character */
/*                               used more than once.               */
/*   CWBSY_PWD_ADJACENT_DIGITS - New password has adjacent digits.  */
/*   CWBSY_PWD_CONSECUTIVE_CHARS - New password contains a character*/
/*                                repeated consecutively.           */
/*   CWBSY_PWD_PREVIOUSLY_USED - New password was previously used.  */
/*   CWBSY_PWD_DISALLOWED_CHAR - New password uses an installation  */
/*                              disallowed character.               */
/*   CWBSY_PWD_NEED_NUMERIC - New password must contain at          */
/*                           least one numeric.                     */
/*   CWBSY_PWD_MATCHES_OLD - New password matches old password      */
/*                          in one or more character positions.     */
/*   CWBSY_PWD_NOT_ALLOWED - New password exists in a dictionary of */
/*                          disallowed passwords.                   */
/*   CWBSY_PWD_MATCHES_USERID - New password matches the user ID.   */
/*   CWBSY_PWD_PRE_V3 - The old password was created on a pre-V3    */
/*                      system which used a different encryption    */
/*                      technique.  Password must be changed        */
/*                      manually on the AS/400.                     */
/*   CWBSY_LAST_INVALID_PASSWORD - The next invalid password        */
/*                                 will disable the user profile.   */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The system name must be set prior to calling this API by using */
/*   the cwbSY_SetSys API.                                          */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbSY_ChangePwd(
                             cwbSY_SecurityHandle  securityHandle,
                             const char           *userID,
                             const char           *oldPassword,
                             const char           *newPassword,
                             cwbSV_ErrHandle       errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbSY_ChangePwdA(
                     cwbSY_SecurityHandle  securityHandle,
                     LPCSTR                userID,
                     LPCSTR                oldPassword,
                     LPCSTR                newPassword,
                     cwbSV_ErrHandle       errorHandle);
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbSY_ChangePwdW(
                     cwbSY_SecurityHandle  securityHandle,
                     LPCWSTR               userID,
                     LPCWSTR               oldPassword,
                     LPCWSTR               newPassword,
                     cwbSV_ErrHandle       errorHandle);
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbSY_ChangePwd                 cwbSY_ChangePwdW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbSY_ChangePwd                 cwbSY_ChangePwdA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSY_CreateSecurityObj                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Creates a security object.  When you are finished using the    */
/*   object you should delete it using the cwbSY_DeleteSecurityObj  */
/*   API.                                                           */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSY_SecurityHandle securityHandle - output                   */
/*        Pointer to a cwbSY_SecurityHandle.  If the create is      */
/*        successful this will contain a handle to the newly        */
/*        created security object.  This handle is required on the  */
/*        other security APIs.                                      */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - A pointer supplied to the API is not     */
/*                         valid.                                   */
/*   CWB_NOT_ENOUGH_MEMORY - Not enough memory available to create  */
/*                           object.                                */
/*                                                                  */
/* Usage Notes:                                                     */
/*   None                                                           */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSY_CreateSecurityObj(
                             cwbSY_SecurityHandle *securityHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSY_DeleteSecurityObj                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Deletes a security object.                                     */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSY_SecurityHandle securityHandle - input                    */
/*       A valid handle to a security object.  The handle           */
/*       is obtained using cwbSY_CreateSecurityObj.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - The security handle supplied is not       */
/*                        valid.                                    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   None                                                           */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSY_DeleteSecurityObj(
                             cwbSY_SecurityHandle SecurityHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSY_GetDateTimeCurrentSignon                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   Retrieves the date and time of the current successful signon.  */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSY_SecurityHandle securityHandle - input                    */
/*       A valid handle to a security object.  The handle           */
/*       is obtained using cwbSY_CreateSecurityObj.                 */
/*                                                                  */
/*   unsigned char * lastSignonDateTime - output                    */
/*       A pointer to 8 bytes which will contain the date and time  */
/*       when the current signon occurred. Use CWBSY_DATE_TIME_LEN  */
/*       to allocate the buffer. Output format is as follows:       */
/*                                                                  */
/*       Bytes     Content                                          */
/*       --------  -----------------------------------------------  */
/*       1 - 2     Year (Example: 1998 = 0x07CE)                    */
/*       3         Month (January = 0x01)                           */
/*       4         Day   (First day = 0x01;31st day = 0x1F)         */
/*       5         Hour  (Midnight = 0x01;23rd hour = 0x17)         */
/*       6         Minute (On the hour = 0x00; 59th minute = 0x3B)  */
/*       7         Second (On the minute = 0x00; 59th second = 0x3B)*/
/*       8         One-hundredth of a second (on the second = 0x00; */
/*                 maximum = 0x63)                                  */
/*                                                                  */
/*   Note: On a given day, the maximum time is 23 hours, 59         */
/*         minutes, and 59.99 seconds.  Midnight is 0 hours, 0      */
/*         minutes and 0.0 seconds on the following day.            */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - A pointer supplied to the API is not     */
/*                         valid.                                   */
/*   CWB_INVALID_HANDLE - The security handle supplied is not       */
/*                        valid.                                    */
/*   CWBSY_NOT_VERIFIED - The user ID and password defined in       */
/*                        object has not been verified.  Make sure  */
/*                        you have first called                     */
/*                        cwbSY_verifyUserIDPwd before using        */
/*                        this API.                                 */
/*                                                                  */
/* Usage Notes:                                                     */
/*   You must have successfully called cwbSY_VerifyUserIDPwd,       */
/*   cwbSY_Logon, or cwbSY_LogonUser before using this API.         */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSY_GetDateTimeCurrentSignon(
                             cwbSY_SecurityHandle  securityHandle,
                             unsigned char        *currentSignonDateTime);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSY_GetDateTimeLastSignon                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   Retrieves the date and time of the previous successful signon. */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSY_SecurityHandle securityHandle - input                    */
/*       A valid handle to a security object.  The handle           */
/*       is obtained using cwbSY_CreateSecurityObj.                 */
/*                                                                  */
/*   unsigned char * lastSignonDateTime - output                    */
/*       A pointer to 8 bytes which will contain the date and time  */
/*       of the last successful signon. Use CWBSY_DATE_TIME_LEN     */
/*       to allocate the buffer. Output format is as follows:       */
/*                                                                  */
/*       Bytes     Content                                          */
/*       --------  -----------------------------------------------  */
/*       1 - 2     Year (Example: 1998 = 0x07CE)                    */
/*       3         Month (January = 0x01)                           */
/*       4         Day   (First day = 0x01;31st day = 0x1F)         */
/*       5         Hour  (Midnight = 0x01;23rd hour = 0x17)         */
/*       6         Minute (On the hour = 0x00; 59th minute = 0x3B)  */
/*       7         Second (On the minute = 0x00; 59th second = 0x3B)*/
/*       8         One-hundredth of a second (on the second = 0x00; */
/*                 maximum = 0x63                                   */
/*                                                                  */
/*   Note: On a given day, the maximum time is 23 hours, 59         */
/*         minutes, and 59.99 seconds.  Midnight is 0 hours, 0      */
/*         minutes and 0.0 seconds on the following day.            */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - A pointer supplied to the API is not     */
/*                         valid.                                   */
/*   CWB_INVALID_HANDLE - The security handle supplied is not       */
/*                        valid.                                    */
/*   CWBSY_NOT_VERIFIED - The user ID and password defined in       */
/*                        object has not been verified.  Make sure  */
/*                        you have first called                     */
/*                        cwbSY_verifyUserIDPwd before using        */
/*                        this API.                                 */
/*                                                                  */
/* Usage Notes:                                                     */
/*   You must have successfully called cwbSY_VerifyUserIDPwd,       */
/*   cwbSY_Logon, or cwbSY_LogonUser before using this API.         */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSY_GetDateTimeLastSignon(
                             cwbSY_SecurityHandle  securityHandle,
                             unsigned char        *lastSignonDateTime);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSY_GetDateTimePwdExpires                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   Retrieves the date and time the password will expire for the   */
/*   given system.                                                  */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSY_SecurityHandle securityHandle - input                    */
/*       A valid handle to a security object.  The handle           */
/*       is obtained using cwbSY_CreateSecurityObj.                 */
/*                                                                  */
/*   unsigned char * expirationDateTime - output                    */
/*       A pointer to 8 bytes which will contain the date and time  */
/*       the password expires.  Use CWBSY_DATE_TIME_LEN to allocate */
/*       the buffer. Output format is as follows:                   */
/*                                                                  */
/*       Bytes     Content                                          */
/*       --------  -----------------------------------------------  */
/*       1 - 2     Year (Example: 1998 = 0x07CE)                    */
/*       3         Month (January = 0x01)                           */
/*       4         Day   (First day = 0x01;31st day = 0x1F)         */
/*       5         Hour  (Midnight = 0x01;23rd hour = 0x17)         */
/*       6         Minute (On the hour = 0x00; 59th minute = 0x3B)  */
/*       7         Second (On the minute = 0x00; 59th second = 0x3B)*/
/*       8         One-hundredth of a second (on the second = 0x00; */
/*                 maximum = 0x63)                                  */
/*                                                                  */
/*   Note: On a given day, the maximum time is 23 hours, 59         */
/*         minutes, and 59.99 seconds.  Midnight is 0 hours, 0      */
/*         minutes and 0.0 seconds on the following day.            */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - A pointer supplied to the API is not     */
/*                         valid.                                   */
/*   CWB_INVALID_HANDLE - The security handle supplied is not       */
/*                        valid.                                    */
/*   CWBSY_NOT_VERIFIED - The user ID and password defined in       */
/*                        object has not been verified.  Make sure  */
/*                        you have first called                     */
/*                        cwbSY_verifyUserIDPwd before using        */
/*                        this API.                                 */
/*                                                                  */
/* Usage Notes:                                                     */
/*   You must have successfully called cwbSY_VerifyUserIDPwd,       */
/*   cwbSY_Logon, or cwbSY_LogonUser before using this API.         */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSY_GetDateTimePwdExpires(
                             cwbSY_SecurityHandle securityHandle,
                             unsigned char       *expirationDateTime);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSY_GetFailedAttempts                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Retrieves the number of unsuccessful logon attempts.           */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSY_SecurityHandle securityHandle - input                    */
/*       A valid handle to a security object.  The handle           */
/*       is obtained using cwbSY_CreateSecurityObj.                 */
/*                                                                  */
/*   unsigned short * numberFailedAttempts - output                 */
/*       A pointer to a short which will contain the number of      */
/*       failed logon attempts.                                     */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - A pointer supplied to the API is not     */
/*                         valid.                                   */
/*   CWB_INVALID_HANDLE - The security handle supplied is not       */
/*                        valid.                                    */
/*   CWBSY_NOT_VERIFIED - The user ID and password defined in       */
/*                        object has not been verified.  Make sure  */
/*                        you have first called                     */
/*                        cwbSY_verifyUserIDPwd before using        */
/*                        this API.                                 */
/*                                                                  */
/* Usage Notes:                                                     */
/*   You must have successfully called cwbSY_VerifyUserIDPwd,       */
/*   cwbSY_Logon, or cwbSY_LogonUser before using this API.         */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSY_GetFailedAttempts(
                             cwbSY_SecurityHandle  securityHandle,
                             unsigned short       *numberFailedAttempts);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSY_GetUserID                                                */
/*                                                                  */
/* Purpose:                                                         */
/*   The API retrieves the currently logged on user ID for the      */
/*   specified system.                                              */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSY_SecurityHandle securityHandle - input                    */
/*       A valid handle to a security object.  The handle           */
/*       is obtained using cwbSY_CreateSecurityObj.                 */
/*                                                                  */
/*   const char * systemName - input                                */
/*       A pointer to an ASCIIZ string containing the name of the   */
/*       AS/400 system. NOTE: System name should not be longer      */
/*       than CWBSY_MAX_SYSTEM_NAME characters.                     */
/*                                                                  */
/*   char * userID - output                                         */
/*       A pointer to an ASCIIZ string to receive the user ID.      */
/*       NOTE: Buffer size should be at least CWBSY_MAX_USER_ID     */
/*       characters in length.                                      */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - The security handle supplied is not       */
/*                        valid.                                    */
/*   CWB_INVALID_POINTER - One of the pointers supplied as a        */
/*                         parameter is not valid.                  */
/*   CWBSY_SYSTEM_NOT_CONFIGURED - The system has not been          */
/*                                 configured.                      */
/*   CWBSY_NOT_LOGGED_ON - There is currently no user logged on     */
/*                         for the specified system.                */
/*   CWB_INVALID_PARAMETER - One of the parameters specified is     */
/*                           invalid.                               */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   None                                                           */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbSY_GetUserID(
                             cwbSY_SecurityHandle  securityHandle,
                             const char           *systemName,
                             char                 *userID);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbSY_GetUserIDA(
                     cwbSY_SecurityHandle  securityHandle,
                     LPCSTR                systemName,
                     LPSTR                 userID);
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbSY_GetUserIDW(
                     cwbSY_SecurityHandle  securityHandle,
                     LPCWSTR               systemName,
                     LPWSTR                userID);
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbSY_GetUserID                 cwbSY_GetUserIDW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbSY_GetUserID                 cwbSY_GetUserIDA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSY_Logon                                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   This procedure prompts for and validates user ID and password. */
/*   If they are valid, the information is stored and subsequent    */
/*   sign-ons and requests for other functions are not prompted     */
/*   for.                                                           */
/*                                                                  */
/*   A sign-on prompt may not be presented if the following are all */
/*   true:                                                          */
/*   - There is a default user ID configured for the system being   */
/*     used (see cwbSY_setSys).                                     */
/*   - A previous sign-on prompt was displayed where the default    */
/*     user ID and password were used and the sign-on was           */
/*     successful.                                                  */
/*   In this case, the user ID and password are used again and no   */
/*   prompt occurs.                                                 */
/*                                                                  */
/*   Note:  If the 'Enable caching of AS/400 passwords' option on   */
/*          the Client Access tab of the Passwords control panel is */
/*          not checked, you will be prompted to sign-on each time  */
/*          the PC is restarted.  This is because the user ID and   */
/*          password are not saved.                                 */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSY_SecurityHandle securityHandle - input                    */
/*       A valid handle to a security object.  The handle           */
/*       is obtained using cwbSY_CreateSecurityObj.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion                                 */
/*   CWB_INVALID_HANDLE  - The security handle is not valid.        */
/*   CWBSY_PASSWORD_EXPIRED - Password has expired.                 */
/*   CWBSY_USER_CANCELLED - The user cancelled the user ID and      */
/*                          password prompt.                        */
/*   CWB_COMMUNICATIONS_ERROR - A communication error occurred      */
/*                              when attempting to contact the      */
/*                              system.                             */
/*   CWBSY_SYSTEM_NOT_CONFIGURED - The system has not been          */
/*                                 configured.                      */
/*   CWBSY_LAST_INVALID_PASSWORD - The next invalid password        */
/*                                 will disable the user profile.   */
/*   CWBSY_USER_PROFILE_DISABLED - The user ID has been disabled.   */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The system name must be set prior to calling this API by using */
/*   the cwbSY_SetSys API.                                          */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbSY_Logon(
                             cwbSY_SecurityHandle securityHandle);


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSY_LogonUser                                                */
/*                                                                  */
/* Purpose:                                                         */
/*   The API validates the supplied user ID and password without    */
/*   presenting a sign-on prompt. If they are valid, the            */
/*   information is stored and subsequent sign-ons and requests for */
/*   other functions are not prompted for.                          */
/*                                                                  */
/*   Note: This API differs from cwbSY_Logon() in that a sign-on    */
/*         prompt will not be presented because the user ID and     */
/*         password information is being passed in on the call.     */
/*         Also, any message dialogs (e.g. password expired) will   */
/*         not be displayed. The return code will be set to         */
/*         indicate these type of conditions.                       */
/*                                                                  */
/*   This API can be used to ensure that subsequent API function    */
/*   calls in your program that establish connections to an AS/400  */
/*   system will not prompt for sign-on information.                */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSY_SecurityHandle securityHandle - input                    */
/*       A valid handle to a security object.  The handle           */
/*       is obtained using cwbSY_CreateSecurityObj.                 */
/*                                                                  */
/*   const char * userID - input                                    */
/*       A pointer to an ASCIIZ string which contains the user ID.  */
/*       The maximum length allowed is defined by CWBSY_MAX_USER_ID.*/
/*                                                                  */
/*   const char * password - input                                  */
/*       A pointer to an ASCIIZ string which contains the current   */
/*       password.  The maximum length allowed is defined by        */
/*       CWBSY_MAX_PASSWORD.                                        */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
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
/*   CWB_INVALID_HANDLE - The security handle is not valid.         */
/*   CWB_INVALID_POINTER - A pointer supplied to the API is not     */
/*                         valid.                                   */
/*   CWB_COMMUNICATIONS_ERROR - A communication error occurred      */
/*                              when attempting to contact the      */
/*                              system.                             */
/*   CWBSY_SYSTEM_NOT_CONFIGURED - The system has not been          */
/*                                 configured.                      */
/*   CWBSY_UNKNOWN_USERID - The supplied user ID is not             */
/*                          known to this system.                   */
/*   CWBSY_WRONG_PASSWORD - Password is not correct.                */
/*   CWBSY_PASSWORD_EXPIRED - Password has expired.                 */
/*   CWBSY_LAST_INVALID_PASSWORD - The next invalid password        */
/*                                 will disable the user profile.   */
/*   CWBSY_USER_PROFILE_DISABLED - The user ID has been disabled.   */
/*   CWBSY_INVALID_PASSWORD - One or more characters in the         */
/*                            password is invalid or the password   */
/*                            is too long.                          */
/*   CWBSY_INVALID_USERID - One or more characters in the user ID   */
/*                          is invalid or the user ID is too long.  */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The system name must set prior to calling this API by using    */
/*   the cwbSY_SetSys API.                                          */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbSY_LogonUser(
                             cwbSY_SecurityHandle  securityHandle,
                             const char           *userID,
                             const char           *password,
                             cwbSV_ErrHandle       errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbSY_LogonUserA(
                     cwbSY_SecurityHandle  securityHandle,
                     LPCSTR                userID,
                     LPCSTR                password,
                     cwbSV_ErrHandle       errorHandle);
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbSY_LogonUserW(
                     cwbSY_SecurityHandle  securityHandle,
                     LPCWSTR               userID,
                     LPCWSTR               password,
                     cwbSV_ErrHandle       errorHandle);
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbSY_LogonUser                 cwbSY_LogonUserW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbSY_LogonUser                 cwbSY_LogonUserA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSY_SetSys                                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   The API sets the name of the system in the specified security  */
/*   object.  No validation of the system name is done.  The system */
/*   name is checked when the user ID and password are verified     */
/*   in the cwbSY_ChangePwd, cwbSY_VerifyUserIDPwd, cwbSY_Logon or  */
/*   cwbSY_LogonUser APIs.                                          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSY_SecurityHandle securityHandle - input                    */
/*       A valid handle to a security object.  The handle           */
/*       is obtained using cwbSY_CreateSecurityObj.                 */
/*                                                                  */
/*   const char * systemName - input                                */
/*       A pointer to an ASCIIZ string containing the name of the   */
/*       AS/400 system. NOTE: System name should not be longer      */
/*       than CWBSY_MAX_SYSTEM_NAME characters.                     */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_HANDLE - The security handle supplied is not       */
/*                        valid.                                    */
/*   CWB_INVALID_POINTER - A pointer supplied to the API is not     */
/*                         valid.                                   */
/*   CWB_INVALID_PARAMETER - One of the parameters specified is     */
/*                           invalid.                               */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   None                                                           */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbSY_SetSys(
                             cwbSY_SecurityHandle  securityHandle,
                             const char           *systemName);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbSY_SetSysA(
                     cwbSY_SecurityHandle  securityHandle,
                     LPCSTR                systemName);
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbSY_SetSysW(
                     cwbSY_SecurityHandle  securityHandle,
                     LPCWSTR               systemName);
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbSY_SetSys                    cwbSY_SetSysW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbSY_SetSys                    cwbSY_SetSysA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbSY_VerifyUserIDPwd                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   Verifies the user ID and password are valid for the given      */
/*   system.                                                        */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSY_SecurityHandle securityHandle - input                    */
/*       A valid handle to a security object.  The handle           */
/*       is obtained using cwbSY_CreateSecurityObj.                 */
/*                                                                  */
/*   const char * userID - input                                    */
/*       A pointer to an ASCIIZ string which contains the user ID.  */
/*       The maximum length allowed is defined by CWBSY_MAX_USER_ID.*/
/*                                                                  */
/*   const char * password - input                                  */
/*       A pointer to an ASCIIZ string which contains the current   */
/*       password.  The maximum length allowed is defined by        */
/*       CWBSY_MAX_PASSWORD.                                        */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
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
/*   CWB_INVALID_HANDLE - The security handle is not valid.         */
/*   CWB_INVALID_POINTER - A pointer supplied to the API is not     */
/*                         valid.                                   */
/*   CWB_COMMUNICATIONS_ERROR - A communication error occurred      */
/*                              when attempting to contact the      */
/*                              system.                             */
/*   CWBSY_SYSTEM_NOT_CONFIGURED - The system has not been          */
/*                                 configured.                      */
/*   CWBSY_UNKNOWN_USERID - The supplied user ID is not             */
/*                          known to this system.                   */
/*   CWBSY_WRONG_PASSWORD - Password is not correct.                */
/*   CWBSY_PASSWORD_EXPIRED - Password has expired.                 */
/*   CWBSY_USER_PROFILE_DISABLED - The user ID has been disabled.   */
/*   CWBSY_INVALID_PASSWORD - One or more characters in the         */
/*                            password is invalid or the password   */
/*                            is too long.                          */
/*   CWBSY_INVALID_USERID - One or more characters in the user ID   */
/*                          is invalid or the user ID is too long.  */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The system name must set prior to calling this API by using    */
/*   the cwbSY_SetSys API.                                          */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbSY_VerifyUserIDPwd(
                             cwbSY_SecurityHandle  securityHandle,
                             const char           *userID,
                             const char           *password,
                             cwbSV_ErrHandle       errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbSY_VerifyUserIDPwdA(
                     cwbSY_SecurityHandle  securityHandle,
                     LPCSTR                userID,
                     LPCSTR                password,
                     cwbSV_ErrHandle       errorHandle);
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbSY_VerifyUserIDPwdW(
                     cwbSY_SecurityHandle  securityHandle,
                     LPCWSTR               userID,
                     LPCWSTR               password,
                     cwbSV_ErrHandle       errorHandle);
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbSY_VerifyUserIDPwd           cwbSY_VerifyUserIDPwdW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbSY_VerifyUserIDPwd           cwbSY_VerifyUserIDPwdA
#endif // of UNICODE/ANSI selection


#if defined( __cplusplus )
}
#endif

#endif /* _CWBSY_H_ */

