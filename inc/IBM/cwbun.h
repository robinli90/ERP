/********************************************************************/
/* Copyright = 5722-XE1 (C) Copyright IBM Corp 1994, 2005.          */
/*  All rights reserved.                                            */
/*  Licensed Material - Program property of IBM                     */
/*  Refer to copyright instructions form number G120-2083.          */
/********************************************************************/
//********************************************************************
//
// File:
//   CWBUN.H
//
// Purpose:
//   Contains function prototypes for Client Access services that
//   are provided to assist in the implementation of Operations
//   Navigator extensions.
//
//		cwbUN_CheckAS400Name
//		cwbUN_CheckObjectAuthority
//		cwbUN_CheckSpecialAuthority
//		cwbUN_ConvertPidlToString
//		cwbUN_DisplaySOAList
//		cwbUN_EndODBCConnections
//		cwbUN_GetDisplayNameFromItemId
//		cwbUN_GetDisplayNameFromName
//		cwbUN_GetDisplayPathFromName
//		cwbUN_GetIconIndex
//		cwbUN_GetIndexFromItemId
//		cwbUN_GetIndexFromName
//		cwbUN_GetIndexFromPidl
//		cwbUN_GetListObject
//		cwbUN_GetODBCConnection
//		cwbUN_GetParentFolderNameFromName
//		cwbUN_GetParentFolderPathFromName
//		cwbUN_GetParentFolderPidl
//		cwbUN_GetSharedImageList
//		cwbUN_GetSystemNameFromName
//		cwbUN_GetSystemNameFromPidl
//		cwbUN_GetSystemValue
//		cwbUN_GetSystemHandle
//		cwbUN_ReleaseSystemHandle
//		cwbUN_GetTypeFromItemId
//		cwbUN_GetTypeFromName
//		cwbUN_GetTypeFromPidl
//		cwbUN_GetUserAttribute
//		cwbUN_IsConnectionTypeTCPIP
//		cwbUN_IsSubcomponentInstalled
//		cwbUN_RefreshAll
//		cwbUN_RefreshList
//		cwbUN_RefreshListItems
//		cwbUN_RefreshListHidden
//		cwbUN_UpdateStatusBar
//		cwbUN_getJVM
//		cwbUN_BrowseURL
//      cwbUN_DisplayAPIError
//      cwbUN_GetJVM
//      cwbUN_DisplayCommandPrompter
//      cwbUN_DisplayProperties
//      cwbUN_GetPublicListObject
//
// The following APIs provide information about the Directory Services
// (LDAP) server on an AS/400.
//
// Functions that use strings are available in ANSI and Unicode
// versions.
//
// Functions that return distinguished names and other strings for
// use with LDAP client APIs are also provided in a UTF-8 version
// for use with LDAP version 3 servers.
//
//      cwbUN_OpenLocalLdapServer
//      cwbUN_FreeLocalLdapServer
//      cwbUN_GetLdapSvrPort
//      cwbUN_GetLdapSvrSuffixCount
//      cwbUN_GetLdapSuffixName
//      cwbUN_OpenLdapPublishing
//      cwbUN_FreeLdapPublishing
//      cwbUN_GetLdapPublishCount
//      cwbUN_GetLdapPublishType
//      cwbUN_GetLdapPublishServer
//      cwbUN_GetLdapPublishPort
//      cwbUN_GetLdapPublishParentDn
//
//
// Usage Notes:
//   Link with the CWBUNAPI.LIB import library.
//   This module is to be used in conjunction with CWBUNAPI.DLL.
//
//********************************************************************
 
#ifndef _CWBUN_H_
#define _CWBUN_H_
 
#include <afx.h>
#include <shlobj.h>
#include <sql.h>
#include "cwb.h"
#include "cwbcosys.h"

// For proper export declarations
#undef CWBAPI
#ifndef __CWBUN__
   #define CWBAPI  CwbImport
#else
   #define CWBAPI  CwbExport
#endif

#if defined( __cplusplus )
  extern "C"
 {
#endif

/////////////////////////////////////////////////////////////////////////////
// Define the common return codes
 
#define CWB_OK						0			// Success
#define CWBUN                       CWB_LAST+1  // Start of CWBUN return codes
#define CWBUN_BAD_PARAMETER			CWBUN		// An input parameter was not valid
#define CWBUN_FORMAT_NOT_VALID		CWBUN+1		// The input object name was not valid
#define CWBUN_WINDOW_NOTAVAIL		CWBUN+2		// View window not found
#define CWBUN_INTERNAL_ERROR		CWBUN+3		// Processing error occurred
#define CWBUN_USER_NOT_AUTHORIZED	CWBUN+4		// User does not have spec'd authority
#define CWBUN_OBJECT_NOT_FOUND		CWBUN+5		// Object not found on the AS/400
#define CWBUN_INVALID_ITEM_ID       CWBUN+6		// invalid item ID parameter
#define CWBUN_NULL_PARM             CWBUN+7		// NULL parameter passed
#define CWBUN_RTN_STR_TOO_LONG      CWBUN+8		// string too long for return buffer 
#define CWBUN_INVALID_OBJ_NAME      CWBUN+9		// invalid object name parameter
#define CWBUN_INVALID_PIDL          CWBUN+10	// invalid PIDL parameter
#define CWBUN_NULL_PIDL_RETURNED    CWBUN+11	// parent folder PIDL was NULL
#define CWBUN_REFRESH_FAILED        CWBUN+12	// refresh list failed
#define CWBUN_UPDATE_FAILED         CWBUN+12	// update toolbar failed
#define CWBUN_INVALID_NAME_TYPE     CWBUN+13	// invalid AS/400 name type
#define CWBUN_INVALID_AUTH_TYPE     CWBUN+14	// invalid authority type
#define CWBUN_HOST_COMM_ERROR       CWBUN+16	// AS/400 communications error
#define CWBUN_INVALID_NAME_PARM     CWBUN+17	// invalid name parameter
#define CWBUN_NULL_DISPLAY_STRING   CWBUN+18    // Null display string returned
#define CWBUN_GENERAL_FAILURE       CWBUN+19    // general AS/400 operation failure
#define CWBUN_INVALID_SYSVAL_ID     CWBUN+20    // invalid system value ID
#define CWBUN_INVALID_LIST_OBJECT   CWBUN+21    // can't get list object from name
#define CWBUN_INVALID_IFS_PATH      CWBUN+22    // invalid IFS path specified
#define CWBUN_LANG_NOT_FOUND        CWBUN+23    // extension doesn't support any of the languages installed on client
#define CWBUN_INVALID_USER_ATTR_ID  CWBUN+24    // invalid user attribute ID
#define CWBUN_GET_USER_ATTR_FAILED  CWBUN+25    // unable to retrieve user attribute
#define CWBUN_INVALID_FLAG_VALUE    CWBUN+26    // invalid flag parameter value set
#define CWBUN_CANT_GET_IMAGELIST    CWBUN+27    // can't get icon image list
#define CWBUN_PROPERTIES_NOT_DEFINED CWBUN+28   // properties action not defined on object

// Name check errors
#define CWBUN_NAME_CHECK            CWBUN+50
#define CWBUN_NAME_TOO_LONG         CWBUN_NAME_CHECK	// name is too long
#define CWBUN_NAME_NULLSTRING       CWBUN_NAME_CHECK+1  // string in empty - no chars at all 
#define CWBUN_NAME_INVALIDCHAR      CWBUN_NAME_CHECK+4  // invalid character    
#define CWBUN_NAME_STRINGTOOLONG    CWBUN_NAME_CHECK+5  // string too long       
#define CWBUN_NAME_MISSINGENDQUOTE  CWBUN_NAME_CHECK+6  // end quote missing
#define CWBUN_NAME_INVALIDQUOTECHAR CWBUN_NAME_CHECK+7  // char invalid for quote string
#define CWBUN_NAME_ONLYBLANKS       CWBUN_NAME_CHECK+8  // a string of only blanks found  
#define CWBUN_NAME_STRINGTOOSHORT   CWBUN_NAME_CHECK+9  // string is too short.
#define CWBUN_NAME_TOOLONGFORIBM    CWBUN_NAME_CHECK+10 // string OK, too long for IBM cmd
#define CWBUN_NAME_INVALIDFIRSTCHAR CWBUN_NAME_CHECK+11 // the first char is invalid
#define CWBUN_NAME_CHECK_LAST       CWBUN_NAME_CHECK+20	// reserved range 

// LDAP related API errors
#define CWBUN_LDAP              CWBUN+100
#define CWBUN_LDAP_NOT_AVAIL    CWBUN_LDAP+1   // Not installed or configured

// BS File related errors
typedef cwb_Handle      cwb_BS_FileHandle;
typedef cwb_Handle      cwb_BS_FindHandle;

#define CWBUN_BS                         CWBUN+150

// user access intent
#define CWBUN_BS_FILE_READ_ACCESS        1
#define CWBUN_BS_FILE_WRITE_ACCESS       2
#define CWBUN_BS_FILE_READWRITE_ACCESS   3

// other user's access
#define CWBUN_BS_FILE_DENYNONE           1
#define CWBUN_BS_FILE_DENYREAD           2
#define CWBUN_BS_FILE_DENYWRITE          3
#define CWBUN_BS_FILE_DENYALL            4

// create/replace options
#define CWBUN_BS_FILE_OPEN_CREATE        0x1
#define CWBUN_BS_FILE_REPLACE_CREATE     0x2
#define CWBUN_BS_FILE_NO_OPEN_CREATE     0x4
#define CWBUN_BS_FILE_OPEN_NO_CREATE     0x8
#define CWBUN_BS_FILE_REPLACE_NO_CREATE  0x10

// file attributes and flags
#define CWBUN_BS_FILE_HIDDEN             0x1
#define CWBUN_BS_FILE_SYSTEM             0x2
#define CWBUN_BS_FILE_READONLY           0x4
#define CWBUN_BS_FILE_ARCHIVE            0x8
#define CWBUN_BS_FILE_DIRECTORY          0x10

// file commit options
#define CWBUN_BS_FILE_BUFFERED           0
#define CWBUN_BS_FILE_SYNC               1

// create file results
#define CWBUN_BS_FILE_WAS_OPENED         1
#define CWBUN_BS_FILE_WAS_REPLACED       2
#define CWBUN_BS_FILE_WAS_CREATED        3

// Data conversion
#define CWBUN_BS_NO_DATA_CONVERSION      0
#define CWBUN_BS_CONVERT_DATA            1

//********************************************************************
// return codes
//********************************************************************
#define CWBUN_BS_START                 CWB_LAST+1
#define CWBUN_BS_DIRECTORY_NOT_EMPTY   CWBUN_BS_START
#define CWBUN_BS_MUST_ATTACH           CWBUN_BS_START+1
#define CWBUN_BS_ALREADY_ATTACHED      CWBUN_BS_START+2
#define CWBUN_BS_DIFFERENT_HOSTS       CWBUN_BS_START+3

// cwbUN_BrowseURL  API errors
#define CWBUN_BROWSER_ERR		CWBUN+200
#define CWBUN_BROWSER_GETPORTNUM_ERR	CWBUN_BROWSER_ERR		// Failed to get port number.
#define CWBUN_BROWSER_LAUNCH_ERR	CWBUN_BROWSER_ERR+1		// Failed to launch browser



// cwbUN_GetJVM API errors 
#define CWBUN_GETJVM_ERR		CWBUN+300
#define CWBUN_GETVM_FAILED		CWBUN_GETJVM_ERR		// Failed to get Java VM 
 
// Command prompter API errors 
#define CWBUN_COMMAND_PROMPTER		CWBUN+400 
#define CWBUN_PROMPT_CANCEL		CWBUN_COMMAND_PROMPTER+1	// The user cancelled the prompt dialog. 
#define CWBUN_PROMPT_ERROR		CWBUN_COMMAND_PROMPTER+2	// The prompt dialog ended because of error.
#define CWBUN_MISSING_PTF		CWBUN_COMMAND_PROMPTER+3	// The V4R4 or V4R5 system does not have the
															// required PTFs.
	 
///////////////////////////////////////////////////////////////////////////// 
// Define the type constants for DisplayCommandPrompter 
 
#define CWBUN_PROMPT_INTERACTIVE	1		// Allow prompting of interactive commands.
#define CWBUN_PROMPT_NO_PROGRAMS    	2		// Prompt override and change exit programs
							// should not be called.
 
#define CWBUN_PROMPT_NODATES		0		// Dates not prompted or returned.
#define CWBUN_PROMPT_DAYMONTHYEAR	1		// DDMMYY format used for dates.
#define CWBUN_PROMPT_JULIAN		2		// Julian format used for dates.
#define CWBUN_PROMPT_MONTHDAYYEAR	3		// MMDDYY format used for dates.
#define CWBUN_PROMPT_YEARMONTHDAY	4		// YYMMDD format used for dates.

/////////////////////////////////////////////////////////////////////////////
// Define the type constants for CheckAS400Name
 
#define CWBUN_LONG_NAME				1		// 256-character AS/400 name
#define CWBUN_SHORT_NAME			2		// 10-character AS/400 name
#define CWBUN_LONG_SNAME			3		// 256-character AS/400 simple name
#define CWBUN_SHORT_SNAME			4		// 10-character AS/400 simple name
#define CWBUN_COMMNAME				5		// 256-character system name
#define CWBUN_STRING				6		// 256-character character string
 
// cwbUN_GetSharedImageList flag settings
#define GSIL_ICON                   1
#define GSIL_SMALLICON              2

// cwbUN_GetIconIndex flag settings
#define GII_ICON                    1
#define GII_SMALLICON               2
#define GII_OPENICON                4

// cwbUN_IsSubcomponentInstalled Operations Navigator Install Option Constants
#define CWBUN_OPNAV_BASE                 1   // OpNav Base option
#define CWBUN_OPNAV_BASIC_OPERATIONS     2   // OpNav Basic Operations option
#define CWBUN_OPNAV_JOB_MANAGEMENT       3   // OpNav Job Management option (Renamed in V5R1 to 'Work Management')
#define CWBUN_OPNAV_SYSTEM_CONFIGURATION 4   // OpNav System Configuration option (Configuration and Service)
#define CWBUN_OPNAV_NETWORK              5   // OpNav Network option
#define CWBUN_OPNAV_SECURITY             6   // OpNav Security option
#define CWBUN_OPNAV_USERS_GROUPS         7   // OpNav Users and Groups option
#define CWBUN_OPNAV_DATABASE             8   // OpNav Database option
#define CWBUN_OPNAV_FILESYSTEMS          9   // OpNav File Systems option
#define CWBUN_OPNAV_MULTIMEDIA          10   // OpNav Multimedia option (removed in V5R1)
#define CWBUN_OPNAV_BACKUP              11   // OpNav Backup option
#define CWBUN_OPNAV_APP_DEV             12   // OpNav Application Development option
#define CWBUN_OPNAV_SYSTEM_MGMT         13   // OpNav Management Central option (No longer exists in V5R1)
#define CWBUN_OPNAV_ADMINISTRATION      14   // OpNav Administration option
#define CWBUN_OPNAV_COMMANDS		    15   // OpNav Commands option
#define CWBUN_OPNAV_PACKAGES_PRODS	    16   // OpNav Packages and Products option
#define CWBUN_OPNAV_MONITORS		    17   // OpNav Monitors option
#define CWBUN_OPNAV_LOGICAL_SYSTEMS	    18   // OpNav Logical Systems option
#define CWBUN_OPNAV_ADV_FUNC_PRESENTATION 19 // OpNav Advanced Function Presentation option
#define CWBUN_OPNAV_NETWORK_RESOURCES   20   // OpNav Network Resources option

// LDAP API typedefs/symbols

typedef void * cwbUN_ldapSvrHandle;
typedef void * cwbUN_ldapPubHandle;

typedef int cwbUN_LdapPubCategories;

#define CWBUN_LDAP_PUBLISH_USER_DEFINED (-1)
#define CWBUN_LDAP_PUBLISH_USERS 1
#define CWBUN_LDAP_PUBLISH_COMPUTERS 2
#define CWBUN_LDAP_PUBLISH_NETWORK_INVENTORY 3

typedef int cwbUN_LdapCnnSecurity;

#define CWBUN_LDAP_CNN_NORMAL 1
#define CWBUN_LDAP_CNN_SSL 2


/////////////////////////////////////////////////////////////////////////////
// Declare the service APIs

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_CheckAS400Name                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   <purpose>                                                      */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * szAS400Name - input                               */
/*     The AS/400 name whose validity is to be checked              */
/*                                                                  */
/*   const char * szSystemName - input                              */
/*     The name of the AS/400 system on which to perform the check  */
/*                                                                  */
/*   USHORT usTypeId - input                                        */
/*     A numeric value which indicates the how the input string     */
/*     should be interpreted as a long object name, a short object  */
/*     name, a communications name, or a string (type constants     */
/*     are defined above)                                           */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion                                 */
/*   CWBUN_NAME_TOO_LONG - name is too long                         */
/*   CWBUN_NAME_NULLSTRING - string in empty - no chars at all      */
/*   CWBUN_NAME_INVALIDCHAR - invalid character                     */
/*   CWBUN_NAME_STRINGTOOLONG - string too long                     */
/*   CWBUN_NAME_MISSINGENDQUOTE - end quote missing                 */
/*   CWBUN_NAME_INVALIDQUOTECHAR - char invalid for quote string    */
/*   CWBUN_NAME_ONLYBLANKS - a string of only blanks found          */
/*   CWBUN_NAME_STRINGTOOSHORT - string is too short                */
/*   CWBUN_NAME_TOOLONGFORIBM - string OK, too long for IBM cmd     */
/*   CWBUN_NAME_INVALIDFIRSTCHAR - the first char is invalid        */
/*                                                                  */
/* Usage Notes:                                                     */
/*   <usage notes>                                                  */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_CheckAS400Name(
    const char * szAS400Name,	
	const char * szSystemName,	
    USHORT usTypeId
    );


CWBAPI unsigned int WINAPI cwbUN_CheckAS400NameW(
    const wchar_t * szAS400Name,	
	const wchar_t * szSystemName,	
    USHORT usTypeId
    );
                             
#if ( defined(CWB_UNICODE) )
   #define cwbUN_CheckAS400Name       cwbUN_CheckAS400NameW
#endif

 
/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_CheckObjectAuthority                                     */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns an indication of whether the Operations Navigator user */
/*   has authority to a particular object on the AS/400             */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * szObjectPath - input                              */
/*     The AS/400 object path for which authority is to be checked  */
/*                                                                  */
/*   const char * szObjectType - input                              */
/*     The AS/400 object type for the object for which authority    */
/*     is to be checked, for example *DTAQ                          */
/*                                                                  */
/*   const char * szAuthorityType - input                           */
/*     The AS/400 object authority to be checked.  Possible values  */
/*     are:                                                         */
/*     - EXCLUDE                                                    */
/*     - CHANGE                                                     */
/*     - USE                                                        */
/*     - AUTLMGT                                                    */
/*     - OBJALTER                                                   */
/*     - OBJOPR                                                     */
/*     - OBJMGT                                                     */
/*     - OBJEXIST                                                   */
/*     - OBJREF                                                     */
/*     - READ                                                       */
/*     - ADD                                                        */
/*     - UPD                                                        */
/*     - DLT                                                        */
/*     - EXECUTE                                                    */
/*     If more than one authority is to be checked, the authorities */
/*     should be concatenated, i.e. *OBJMGT*OBJEXIST..  Up to       */
/*     eleven authority types may be specified on a single call;    */
/*     the function will return CWB_OK only if the user has all of  */
/*     the specified authorities to the object.                     */
/*                                                                  */
/*   const char * szSystemName - input                              */
/*     The name of the AS/400 system on which to perform the check  */ 
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - the user has the specified authority to the object    */
/*   CWBUN_USER_NOT_AUTHORIZED - the user does not have the         */
/*                               specified authority                */
/*   CWBUN_OBJECT_NOT_FOUND - the specified object could not be     */
/*                            found on the AS/400                   */
/*   CWBUN_INTERNAL_ERROR - object authority could not be checked   */
/*                                                                  */
/* Usage Notes:                                                     */
/*   If *EXCLUDE is specified as an authority no other authority    */
/*   types may be specified.  *AUTLMGT is only valid if             */
/*   'szObjectType' is *AUTL.                                       */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_CheckObjectAuthority(
    const char * szObjectPath,	
    const char * szObjectType,	
    const char * szAuthorityType,	
	const char * szSystemName	
    );
 
CWBAPI unsigned int WINAPI cwbUN_CheckObjectAuthorityW(
    const wchar_t * szObjectPath,	
    const wchar_t * szObjectType,	
    const wchar_t * szAuthorityType,	
	const wchar_t * szSystemName	
    );

#if ( defined(CWB_UNICODE) )
   #define cwbUN_CheckObjectAuthority       cwbUN_CheckObjectAuthorityW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_CheckSpecialAuthority                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns an indication of whether the Operations Navigator user */
/*   has a particular special authority on the AS/400               */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * szSpecialAuthority - input                        */
/*     The AS/400 special authority to be checked.  Possible        */
/*     values are:                                                  */
/*     - *ALLOBJ                                                    */
/*     - *AUDIT                                                     */
/*     - *IOSYSCFG                                                  */
/*     - *JOBCTL                                                    */
/*     - *SAVSYS                                                    */
/*     - *SECADM                                                    */
/*     - *SERVICE                                                   */
/*     - *SPLCTL                                                    */
/*                                                                  */
/*   const char * szSystemName - input                              */
/*     The name of the AS/400 system on which to perform the check  */ 
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - the user has the specified special authority          */
/*   CWBUN_USER_NOT_AUTHORIZED - the user does not have the         */
/*                               specified authority                */
/*   CWBUN_INTERNAL_ERROR - special authority could not be checked  */
/*                                                                  */
/* Usage Notes:                                                     */
/*   <usage notes>                                                  */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_CheckSpecialAuthority(
    const char * szSpecialAuthority,	
	const char * szSystemName			
    );
 
CWBAPI unsigned int WINAPI cwbUN_CheckSpecialAuthorityW(
    const wchar_t * szSpecialAuthority,	
	const wchar_t * szSystemName			
    );

#if ( defined(CWB_UNICODE) )
   #define cwbUN_CheckSpecialAuthority       cwbUN_CheckSpecialAuthorityW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetDisplayNameFromItemId                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   Converts an Unity item identifier list to a fully-qualified    */
/*   object name                                                    */
/*                                                                  */
/* Parameters:                                                      */
/*   LPCITEMIDLIST pidl - input                                     */
/*     Pointer to the ITEMIDLIST (item identifier list) structure   */
/*     that is to be converted                                      */
/*                                                                  */
/*   char * szObjectName - output                                   */
/*     Address of the buffer that will receive the null-terminated  */
/*     object name                                                  */
/*                                                                  */
/*   UINT cchMax - input                                            */
/*     Size of the buffer that will receive the null-terminated     */
/*     object name                                                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_FORMAT_NOT_VALID - the specified item identifier list is */
/*                            not valid                             */
/*   CWB_BUFFER_OVERFLOW - the buffer is too small to contain the   */
/*                         returned string                          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   <usage notes>                                                  */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_ConvertPidlToString(
    LPCITEMIDLIST pidl,
    char * szObjectName,	
    UINT cchMax
    );

CWBAPI unsigned int WINAPI cwbUN_ConvertPidlToStringW(
    LPCITEMIDLIST pidl,
    wchar_t * szObjectName,	
    UINT cchMax
    );


#if ( defined(CWB_UNICODE) )
   #define cwbUN_ConvertPidlToString       cwbUN_ConvertPidlToStringW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_EndODBCConnections()                                     */
/*                                                                  */
/* Purpose:                                                         */
/*   Ends all ODBC connections previously opened by                 */
/*   cwbUN_GetODBCConnection().                                     */
/*                                                                  */
/* Parameters:                                                      */
/*   NA                                                             */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*                                                                  */
/* Usage Notes:                                                     */
/*	It's very important to remember that the EndODBCConnections     */
/*	function only closes connections that were opened using the     */
/*	GetODBCConnection function.  The EndODBCConnections             */
/*	function is unaware of ODBC connections opened directly or      */
/*	using other interfaces.                                         */
/*                                                                      */
/*	You also want to be sure that the destructor for the folder of  */
/*	your application extension invokes the EndODBCConnections if    */
/*	any code in your extension uses GetODBCConnection.              */ 
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     See cwbUN_GetODBCConnection()	                            */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_EndODBCConnections();

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetDisplayNameFromItemId                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   Extracts the item name field from a Unity item identifier      */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * szItemId - input                                  */
/*     The Unity item identifier from which the item name will be   */
/*     extracted                                                    */
/*                                                                  */
/*   char * szItemName - output                                     */
/*     Address of the buffer that will receive the null-terminated  */
/*     item name                                                    */
/*                                                                  */
/*   UINT cchMax - input                                            */
/*     Size of the buffer that will receive the null-terminated     */
/*     item name                                                    */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_FORMAT_NOT_VALID - specified item identifier not valid   */  
/*   CWB_BUFFER_OVERFLOW - the buffer is too small to contain the   */
/*                         returned string                          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   <usage notes>                                                  */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_GetDisplayNameFromItemId(
    const char * szItemId,	
    char * szItemName,	
    UINT cchMax
    );
 
CWBAPI unsigned int WINAPI cwbUN_GetDisplayNameFromItemIdW(
    const wchar_t * szItemId,	
    wchar_t * szItemName,	
    UINT cchMax
    );


#if ( defined(CWB_UNICODE) )
   #define cwbUN_GetDisplayNameFromItemId       cwbUN_GetDisplayNameFromItemIdW
#endif
/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetDisplayNameFromName                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Extracts the item name field from a fully-qualified Unity      */
/*   object name                                                    */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * szObjectName - input                              */
/*     The Unity object name from which the item name will be       */
/*     extracted                                                    */
/*                                                                  */
/*   char * szItemName - output                                     */
/*     Address of the buffer that will receive the null-terminated  */
/*     item name                                                    */
/*                                                                  */
/*   UINT cchMax - input                                            */
/*     Size of the buffer that will receive the null-terminated     */
/*     item name                                                    */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_FORMAT_NOT_VALID - specified object name is not valid    */
/*   CWB_BUFFER_OVERFLOW - the buffer is too small to contain the   */
/*                         returned string                          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   <usage notes>                                                  */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_GetDisplayNameFromName(
    const char * szObjectName,	
    char * szItemName,	
    UINT cchMax
    );
 
CWBAPI unsigned int WINAPI cwbUN_GetDisplayNameFromNameW(
    const wchar_t  * szObjectName,	
    wchar_t * szItemName,	
    UINT cchMax
    );

#if ( defined(CWB_UNICODE) )
   #define cwbUN_GetDisplayNameFromName       cwbUN_GetDisplayNameFromNameW
#endif


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetDisplayPathFromName                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Converts a fully-qualified Unity object name to a              */
/*   fully-qualified pathname suitable for displaying to the user   */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * szObjectName - input                              */
/*     The Unity object name from which the pathname will be        */
/*     derived                                                      */
/*                                                                  */
/*   char * szPathName - output                                     */
/*     Address of the buffer that will receive the null-terminated  */
/*     pathname                                                     */
/*                                                                  */
/*   UINT cchMax - input                                            */
/*     Size of the buffer that will receive the null-terminated     */
/*     pathname                                                     */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_FORMAT_NOT_VALID - specified object name is not valid    */
/*   CWB_BUFFER_OVERFLOW - the buffer is too small to contain the   */
/*                         returned string                          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   <usage notes>                                                  */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_GetDisplayPathFromName(
    const char * szObjectName,	
    char * szPathName,	
    UINT cchMax
    );

CWBAPI unsigned int WINAPI cwbUN_GetDisplayPathFromNameW(
    const wchar_t * szObjectName,	
    wchar_t * szPathName,	
    UINT cchMax
    );

#if ( defined(CWB_UNICODE) )
   #define cwbUN_GetDisplayPathFromName       cwbUN_GetDisplayPathFromNameW
#endif



/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetIconIndex                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the index in the image list of the specified icon          */
/*                                                                  */
/* Parameters:                                                      */
/*   LPCITEMIDLIST pidl - input                                     */
/*     Pointer to the ITEMIDLIST (item identifier list) structure   */
/*     that is used to identify the icon to be referenced.          */
/*                                                                  */
/*   UINT uFlags - input                                            */
/*     Specification of the type of icon index to retrieve (defined */
/*     above). The following flag types are allowed:                */
/*                                                                  */
/*                     GII_ICON                                     */
/*                     GII_SMALLICON                                */
/*                     GII_OPENICON                                 */
/*                                                                  */
/*   int* piIndex - output                                          */
/*     Address of the integer that will receive the icon index      */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_INVALID_FLAG_VALUE - not a valid supported flag value    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   <usage notes>                                                  */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_GetIconIndex(
    LPCITEMIDLIST pidl,
	UINT uFlags,
    int* piIndex
    ); 

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetIndexFromItemId                                       */
/*                                                                  */
/* Purpose:                                                         */
/*   Extracts the item index field from a Unity item identifier     */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * szItemId - input                                  */
/*     The Unity item identifier from which the item index will be  */
/*     extracted                                                    */
/*                                                                  */
/*   ULONG* piIndex - output                                        */
/*     Address of an unsigned long integer that will receive the    */
/*     item index                                                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_FORMAT_NOT_VALID - specified item identifier not valid   */
/*                                                                  */
/* Usage Notes:                                                     */
/*   <usage notes>                                                  */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_GetIndexFromItemId(
    const char * szItemId,	
    ULONG* piIndex
    );
 
CWBAPI unsigned int WINAPI cwbUN_GetIndexFromItemIdW(
    const wchar_t * szItemId,	
    ULONG* piIndex
    );

#if ( defined(CWB_UNICODE) )
   #define cwbUN_GetIndexFromItemId       cwbUN_GetIndexFromItemIdW
#endif


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetIndexFromName                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Extracts the item index field from a fully-qualified Unity     */
/*   object name                                                    */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * szObjectName - input                              */
/*     The Unity object name from which the item index will be      */
/*     extracted                                                    */
/*                                                                  */
/*   ULONG* piIndex - output                                        */
/*     Address of an unsigned long integer that will receive the    */
/*     item index                                                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_FORMAT_NOT_VALID - specified object name is not valid    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   <usage notes>                                                  */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_GetIndexFromName(
    const char * szObjectName,	
    ULONG* piIndex
    );
 
CWBAPI unsigned int WINAPI cwbUN_GetIndexFromNameW(
    const wchar_t * szObjectName,	
    ULONG* piIndex
    );

#if ( defined(CWB_UNICODE) )
   #define cwbUN_GetIndexFromName       cwbUN_GetIndexFromNameW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetIndexfromPidl                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Extracts the item index field from a fully-qualified Unity     */
/*   item identifier list                                           */
/*                                                                  */
/* Parameters:                                                      */
/*   LPCITEMIDLIST pidl - input                                     */
/*     Pointer to an ITEMIDLIST (item identifier list) structure    */
/*     from which the item index will be extracted                  */
/*                                                                  */
/*   ULONG* piIndex - output                                        */
/*     Address of an unsigned long integer that will receive the    */
/*     item index                                                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_FORMAT_NOT_VALID - the specified item identifier list is */
/*                            not valid                             */
/*                                                                  */
/* Usage Notes:                                                     */
/*   <usage notes>                                                  */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_GetIndexFromPidl(
    LPCITEMIDLIST pidl,
    ULONG* piIndex
    );
 
/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetListObject                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Get a pointer to the object associated with the specified      */
/*   list object name                                               */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * szObjectName - input                              */
/*     The Unity object name from which the object pointer will be  */
/*     found and returned                                           */
/*                                                                  */
/*   LPVOID pListObject - output                                    */
/*     Address of a pointer to the request Unity object             */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_NULL_PARM - object name or object pointer is NULL        */
/*   CWBUN_INVALID_OBJ_NAME - invalid object name format            */
/*   CWBUN_INVALID_LIST_OBJECT - could not find an object           */
/*            associated with the specified object name             */
/*                                                                  */
/* Usage Notes:                                                     */
/*   <usage notes>                                                  */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_GetListObject(
    const char * szFileName,	
	LPVOID *pListObject
    );

CWBAPI unsigned int WINAPI cwbUN_GetListObjectW(
    const wchar_t * szFileName,	
	LPVOID *pListObject
    );


#if ( defined(CWB_UNICODE) )
   #define cwbUN_GetListObject       cwbUN_GetListObjectW
#endif


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetODBCConnection                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Return the handle to an ODBC connection on the specified       */
/*   AS/400 server system                                           */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * szSystemName - input                              */
/*     The name of the AS/400 system on which to retrieve an        */
/*     ODBC connection                                              */
/*                                                                  */
/*   HDBC *phDBC - output                                           */
/*     Address to return the ODBC connection handle                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*                                                                  */
/* Usage Notes:                                                     */
/*   <usage notes>                                                  */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     See cwbUN_EndODBCConnections()                               */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_GetODBCConnection(
    const char * szSystemName,	
	HDBC *phDBC
    );

CWBAPI unsigned int WINAPI cwbUN_GetODBCConnectionW(
    const wchar_t * szSystemName,	
	HDBC *phDBC
    );

#if ( defined(CWB_UNICODE) )
   #define cwbUN_GetODBCConnection       cwbUN_GetODBCConnectionW
#endif
/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetParentFolderNameFromName                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Extracts the name of an object's parent folder from a          */
/*   fully-qualified Unity object name                              */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * szObjectName - input                              */
/*     The Unity object name from which the parent folder name      */
/*     will be extracted                                            */
/*                                                                  */
/*   char * szParentFolderPath - output                             */
/*     Address of the buffer that will receive the null-terminated  */
/*     parent folder name                                           */
/*                                                                  */
/*   UINT cchMax - input                                            */
/*     Size of the buffer that will receive the null-terminated     */
/*     parent folder name                                           */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_FORMAT_NOT_VALID - specified object name is not valid    */
/*   CWB_BUFFER_OVERFLOW - the buffer is too small to contain the   */
/*                         returned string                          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   <usage notes>                                                  */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_GetParentFolderNameFromName(
    const char * szObjectName,	
    char * szParentFolderName,	
    UINT cchMax
    );
 
CWBAPI unsigned int WINAPI cwbUN_GetParentFolderNameFromNameW(
    const wchar_t * szObjectName,	
    wchar_t * szParentFolderName,	
    UINT cchMax
    );

#if ( defined(CWB_UNICODE) )
   #define cwbUN_GetParentFolderNameFromName       cwbUN_GetParentFolderNameFromNameW
#endif
/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetParentFolderPathFromName                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Given a fully-qualified Unity object name, returns the         */
/*   fully-qualified object name of the object's parent folder      */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * szObjectName - input                              */
/*     The Unity object name from which the parent folder object    */
/*     name will be extracted                                       */
/*                                                                  */
/*   char * szParentFolderPath - output                             */
/*     Address of the buffer that will receive the null-terminated  */
/*     parent folder object name                                    */
/*                                                                  */
/*   UINT cchMax - input                                            */
/*     Size of the buffer that will receive the null-terminated     */
/*     parent folder object name                                    */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_FORMAT_NOT_VALID - specified object name is not valid    */
/*   CWB_BUFFER_OVERFLOW - the buffer is too small to contain the   */
/*                         returned string                          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   <usage notes>                                                  */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_GetParentFolderPathFromName(
    const char * szObjectName,	
    char * szParentFolderPath,	
    UINT cchMax
    );
 
CWBAPI unsigned int WINAPI cwbUN_GetParentFolderPathFromNameW(
    const wchar_t * szObjectName,	
    wchar_t * szParentFolderPath,	
    UINT cchMax
    );

#if ( defined(CWB_UNICODE) )
   #define cwbUN_GetParentFolderPathFromName       cwbUN_GetParentFolderPathFromNameW
#endif
/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetParentFolderPidl                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Given a fully-qualified Unity item identifier list, returns    */
/*   the fully-qualified item identifier list of the object's       */
/*   parent folder                                                  */
/*                                                                  */
/* Parameters:                                                      */
/*   LPCITEMIDLIST pidl - input                                     */
/*     Pointer to an ITEMIDLIST (item identifier list) structure    */
/*     from which the parent folder item identifier list will be    */
/*     extracted                                                    */
/*                                                                  */
/*   LPITEMIDLIST* ppidl - output                                   */
/*     Address of an item identifier list pointer that will receive */
/*     the parent folder item identifier list                       */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_FORMAT_NOT_VALID - the specified item identifier list is */
/*                            not valid                             */
/*                                                                  */
/* Usage Notes:                                                     */
/*   <usage notes>                                                  */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_GetParentFolderPidl(
    LPCITEMIDLIST pidl,
    LPITEMIDLIST *ppidl
    );
 
/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetResourceLibraryPath                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Determines which of the installed languages is supported by    */
/*   the specified Operations Navigator extension, and returns the  */
/*   directory pathname of the subdirectory containing the          */
/*   extension's NLS resources for the currently active language.   */
/*   If the extension does not support the active language, the     */
/*   pathname for a related language that is supported will be      */
/*   returned, if one can be found.                                 */
/*                                                                  */
/*   Extension developers should use this API to determine which    */
/*   directory to load their NLS resources from.                    */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * pszProgID - input                                 */
/*     The programmatic identifier which uniquely identifies an     */
/*     Operations Navigator extension.  It should be of the form    */
/*     <vendor>.<component>.                                        */
/*                                                                  */
/*   char * pszLibraryPath - output                                 */
/*     Address of the buffer that will receive the fully-qualified  */
/*     pathname of the NLS directory                                */
/*                                                                  */
/*   UINT cchMax - input                                            */
/*     Size of the buffer that will receive the fully-qualified     */
/*     pathname of the NLS directory                                */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_FORMAT_NOT_VALID - specified ProgID is not valid         */ 
/*   CWBUN_RTN_STR_TOO_LONG - the buffer is too small to contain    */
/*                            the returned string                   */
/*   CWBUN_LANG_NOT_FOUND - the specified extension does not        */
/*                          support any of the languages currently  */
/*                          installed on the client                 */
/*                                                                  */
/* Usage Notes:                                                     */
/*   <usage notes>                                                  */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_GetResourceLibraryPath(
    const char * pszProgID,	
    char * pszLibraryPath,	
    UINT cchMax
    );
 
CWBAPI unsigned int WINAPI cwbUN_GetResourceLibraryPathW(
    const wchar_t * pszProgID,	
    wchar_t * pszLibraryPath,	
    UINT cchMax
    );

#if ( defined(CWB_UNICODE) )
   #define cwbUN_GetResourceLibraryPath       cwbUN_GetResourceLibraryPathW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetSharedImageList                                       */
/*                                                                  */
/* Purpose:                                                         */
/*   Retrieve the icon image list associated with Operations        */
/*   Navigator.                                                     */
/*                                                                  */
/* Parameters:                                                      */
/*   UINT uFlags - input                                            */
/*     Specification of the type of image list to retrieve (defined */
/*     above) The following flag types are allowed:                 */
/*                                                                  */
/*                     GSIL_ICON                                    */
/*                     GSIL_SMALLICON                               */
/*                                                                  */
/*   HIMAGELIST* phImageList -                                      */
/*     Address of the variable that will receive the image list     */
/*     handle.                                                      */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_INVALID_FLAG_VALUE - not a valid supported flag value    */
/*   CWBUN_CANT_GET_IMAGELIST - a failure occurred while attempting */
/*                               to get the icon image list         */
/*                                                                  */
/* Usage Notes:                                                     */
/*   <usage notes>                                                  */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_GetSharedImageList(
    UINT uFlags,
    HIMAGELIST* phImageList
    );

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetSystemNameFromName                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   Extracts the AS/400 system name from a fully-qualified Unity   */
/*   object name                                                    */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * szObjectName - input                              */
/*     The Unity object name from which the system name will be     */
/*     extracted                                                    */
/*                                                                  */
/*   char * szSystemName - output                                   */
/*     Address of the buffer that will receive the null-terminated  */
/*     system name                                                  */
/*                                                                  */
/*   UINT cchMax - input                                            */
/*     Size of the buffer that will receive the null-terminated     */
/*     system name                                                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_FORMAT_NOT_VALID - specified object name is not valid    */ 
/*   CWB_BUFFER_OVERFLOW - the buffer is too small to contain the   */
/*                         returned string                          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   <usage notes>                                                  */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_GetSystemNameFromName(
    const char * szObjectName,	
    char * szSystemName,	
    UINT cchMax
    );
 
CWBAPI unsigned int WINAPI cwbUN_GetSystemNameFromNameW(
    const wchar_t * szObjectName,	
    wchar_t * szSystemName,	
    UINT cchMax
    );

#if ( defined(CWB_UNICODE) )
   #define cwbUN_GetSystemNameFromName       cwbUN_GetSystemNameFromNameW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetSystemNameFromPidl                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   Extracts the AS/400 system name from a fully-qualified         */
/*   Unity item identifier list                                     */
/*                                                                  */
/* Parameters:                                                      */
/*   LPCITEMIDLIST pidl - input                                     */
/*     Pointer to an ITEMIDLIST (item identifier list) structure    */
/*     from which the system name will be extracted                 */
/*                                                                  */
/*   char * szSystemName - output                                   */
/*     Address of the buffer that will receive the null-terminated  */
/*     system name                                                  */
/*                                                                  */
/*   UINT cchMax - input                                            */
/*     Size of the buffer that will receive the null-terminated     */
/*     system name                                                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_FORMAT_NOT_VALID - the specified item identifier list is */
/*                            not valid                             */
/*   CWB_BUFFER_OVERFLOW - the buffer is too small to contain the   */
/*                         returned string                          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   <usage notes>                                                  */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_GetSystemNameFromPidl(
    LPCITEMIDLIST pidl,
    char * szSystemName,	
    UINT cchMax
    );
 
CWBAPI unsigned int WINAPI cwbUN_GetSystemNameFromPidlW(
    LPCITEMIDLIST pidl,
    wchar_t * szSystemName,	
    UINT cchMax
    );
 

#if ( defined(CWB_UNICODE) )
   #define cwbUN_GetSystemNameFromPidl       cwbUN_GetSystemNameFromPidlW
#endif
/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetSystemValue                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns a string containing the value of an AS/400 system      */
/*   value                                                          */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * szSystemValueId - input                           */
/*     A numeric value which identifies the AS/400 system value to  */
/*     be retrieved.  The system value constants are defined in the */
/*     header file 'cwba4svl.h'                                     */
/*                                                                  */
/*   char * szSystemValue - output                                  */
/*     Address of the buffer that will receive the null-terminated  */
/*     system value string                                          */
/*                                                                  */
/*   UINT cchMax - input                                            */
/*     Size of the buffer that will receive the null-terminated     */
/*     value string                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_INTERNAL_ERROR - the system value could not be retrieved */
/*   CWB_BUFFER_OVERFLOW - the buffer is too small to contain the   */
/*                         returned string                          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The value returned by this API is NOT an NLS string and is not */
/*   translated.  For example, '*NONE' will be returned instead of  */
/*   'None'.                                                        */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_GetSystemValue(
    USHORT usSystemValueId,
	const char * szSystemName,	
    char * szSystemValue,	
    UINT cchMax
    );
 
CWBAPI unsigned int WINAPI cwbUN_GetSystemValueW(
    USHORT usSystemValueId,
	const wchar_t * szSystemName,	
    wchar_t * szSystemValue,	
    UINT cchMax
    );


#if ( defined(CWB_UNICODE) )
   #define cwbUN_GetSystemValue       cwbUN_GetSystemValueW
#endif


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetSystemHandle                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns a system handle which contains the security            */
/*   (SSL) settings to be used for this AS/400 system               */
/*   The system handle will have the settings that were configured  */
/*   in Operations Navigator for the input AS/400 system name       */
/*                                                                  */
/*   If the application name is set to NULL, the returned system    */
/*   handle will be unique. If the application name is set, the     */ 
/*   same system handle that matches the application name           */
/*   will be returned.                                              */
/*                                                                  */
/*   If an application desires to have a unique AS/400 job for a    */
/*   system, then NULL or a unique name should be passed in for     */
/*   the application name.                                          */
/*                                                                  */
/*   If an application desires to share an AS/400 job, then all     */
/*   callers of this function should pass in the same application   */
/*   name.                                                          */ 
/*                                                                  */
/*                                                                  */
/* Parameters:                                                      */
/*   char *  szSystemName - input                                   */
/*     Pointer to an ASCIIZ string that contains the name           */
/*     of the system that you want a system handle to be created    */ 
/*                                                                  */
/*   char *  szAppName - input                                      */
/*     Pointer to an ASCIIZ string of no more than 12               */
/*     characters.  This uniquely identifies the application        */
/*     that will share a single system handle.                      */
/*                                                                  */
/*   cwbCO_SysHandle * systemHandle - output                          */
/*     Pointer to the handle of the system for this system name     */
/*                                                                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_NULL_PARM     - System name was NULL                     */
/*   CWBUN_INVALID_NAME_PARM - The system name is not valid         */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        code page being used.     */
/*   CWB_API_ERROR - the system handle could not be returned        */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This function must be used by all third party applications     */
/*   that wish to support SSL using the Client Access APIs.         */
/*                                                                  */
/*   For example all of the Client Access communications APIs need  */
/*   a system handle to support SSL.                                */
/*                                                                  */
/*   When the caller of this function no longer needs the           */
/*   system handle for communictions the handle can be released     */
/*   by calling function cwbUN_ReleaseSystemHandle.                 */            
/*   All handles will be released when the Operations Navigator     */ 
/*   application (cwbunnav.exe) terminates                          */ 
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_GetSystemHandle(
    char * szSystemName,	
    char * szAppName,	
    cwbCO_SysHandle * systemHandle
    );

CWBAPI unsigned int WINAPI cwbUN_GetSystemHandleW(
    wchar_t * szSystemName,	
    wchar_t * szAppName,	
    cwbCO_SysHandle * systemHandle
    );


#if ( defined(CWB_UNICODE) )
   #define cwbUN_GetSystemHandle       cwbUN_GetSystemHandleW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_ReleaseSystemHandle                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Releases a system handle which contains the security           */
/*   (SSL) settings to be used for this AS/400 system               */
/*   The system handle is obtained using the cwbUN_GetSystemHandle  */
/*   function                                                       */
/*                                                                  */
/*   If the caller of this function has the last reference to the   */
/*   handle, the handle resources will actually be destroyed        */
/*                                                                  */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle * systemHandle - input                         */
/*     Pointer to the handle of the system that was obtained        */
/*     on a cwbUN_GetSystemHandle call                              */
/*                                                                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_API_ERROR - the system handle could not be released        */
/*                                                                  */
/* Usage Notes:                                                     */
/*   When the caller of this function no longer needs the           */
/*   system handle for communictions the handle can be released     */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_ReleaseSystemHandle(cwbCO_SysHandle * systemHandle);



/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_DisplaySOAList                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Displays a System Object Access (SOA) list in a separate       */
/*   window.  Possible lists include:                               */
/*   - jobs                                                         */
/*   - server jobs                                                  */
/*   - job log                                                      */
/*   - printer output                                               */
/*   - printers                                                     */
/*   - messages                                                     */
/*                                                                  */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * szSystemName - input                              */
/*     The name of the AS/400 system where the requested list       */
/*     resides                                                      */
/*                                                                  */
/*   const char * szCommand - input                                 */
/*     The complete command containing the path, list command name, */
/*     and parameters:                                              */
/*                                                                  */
/*     ex: c:\Program Files\IBM\Client Access\lstjob.exe            */
/*         /system Rchasp04 /jobtype I                              */
/*                                                                  */
/*                                                                  */
/*     -----------------------------------------------------        */
/*     The following parameters are supported by lstjob.exe:        */
/*                                                                  */    
/*      /system system-name                                         */
/*                                                                  */
/*          Specifies the name of the AS/400 system from which      */ 
/*          the list of jobs will be built.                         */
/*                                                                  */  
/*          Examples: /system ROCH                                  */
/*                                                                  */
/*                                                                  */
/*      /job jobname                                                */
/*                                                                  */
/*          Specifies a qualified OS/400 job name in the form       */ 
/*          jobnbr/user/jobname.  Only jobs whos job name match     */
/*          the specified job name will be included in the list.    */
/*                                                                  */
/*          Job number special values for job number:               */
/*                                                                  */ 
/*              *ALL means all jobs are included in the list        */
/*                  regardless of the job number value.             */
/*                                                                  */
/*          User name special values for user name:                 */
/*                                                                  */ 
/*              *CURRENT means jobs whose user name matches the     */ 
/*                  current user profile name are included in       */
/*                  the list.                                       */
/*              *ALL means all jobs are included in the list        */  
/*                  regardless of the user name value.              */
/*                                                                  */
/*          Job name special values for job name:                   */
/*                                                                  */
/*              *ALL means all jobs are included in the list        */
/*                  regardless of the job name value.               */
/*                                                                  */
/*                                                                  */
/*          Examples: /job *ALL/RWATERS/*ALL                        */
/*                    /job *ALL/*CURRENT/*ALL                       */ 
/*                    /job *ALL/*ALL/DSP01                          */
/*                                                                  */
/*          If this parameter is not specified, all jobs for the    */
/*          current user are included in the list.                  */
/*                                                                  */
/*      /jobtype type-value                                         */
/*                                                                  */
/*          Specifies the type of jobs to be included in the        */
/*          list.  One of the following special values must be      */
/*          specified.                                              */
/*                                                                  */
/*          *   Jobs are included in the list regardless of type.   */
/*          A   Only autostart jobs are included in the list.       */
/*          B   Only batch jobs are included in the list.           */   
/*          I   Only interactive jobs are included in the list.     */
/*          M   Only subsystem monitor jobs are included in list.   */
/*          R   Only spooled reader jobs are included in the list.  */ 
/*          S   Only system jobs are included in the list.          */ 
/*          W   Only spooled writer jobs are included in the list.  */
/*          X   Only the SCPF job is included in the list.          */
/*                                                                  */
/*          Examples: /jobtype *                                    */
/*                    /jobtype B                                    */
/*                                                                  */
/*          If this parameter is not specified, B is used for a     */
/*          default.                                                */ 
/*                                                                  */
/*      /queued queued-jobs-value                                   */
/*                                                                  */
/*          Specifies whether jobs on job queues are to be          */
/*          included in the list.                                   */
/*                                                                  */
/*          One of the following special values must be specified.  */ 
/*                                                                  */
/*              *ALL   Jobs on job queues are included in the list. */
/*              *NONE  Jobs on job queues are not included in list. */
/*                                                                  */
/*          Examples: /queued    *ALL                               */
/*                    /queued    *NONE                              */
/*                                                                  */
/*          If this parameter is not specified, *ALL is used for    */
/*          a default.                                              */
/*                                                                  */
/*      /active active-jobs-value                                   */
/*                                                                  */
/*          Specifies whether active jobs are to be included in     */
/*          the list.                                               */  
/*                                                                  */
/*          One of the following special values must be specified.  */
/*                                                                  */
/*              *ALL   Active jobs are included in the list.        */  
/*              *NONE  Active jobs are not included in the list.    */
/*                                                                  */
/*          Examples: /active    *ALL                               */
/*                    /active    *NONE                              */
/*                                                                  */
/*          If this parameter is not specified, *ALL is used for    */
/*          a default.                                              */
/*                                                                  */
/*      /completed completed-jobs-value                             */
/*                                                                  */
/*          Specifies whether completed jobs (with output           */
/*          waiting to print) are to be included in the list.       */ 
/*                                                                  */ 
/*          One of the following special values must be             */
/*          specified                                               */
/*                                                                  */  
/*              *ALL   Completed jobs are included in the list.     */
/*              *NONE  Completed jobs are not included in the list. */ 
/*                                                                  */
/*          Examples: /completed *ALL                               */
/*                    /completed *NONE                              */
/*                                                                  */  
/*          If this parameter is not specified, *NONE is used       */
/*          for a default.                                          */
/*                                                                  */ 
/*      /jobq <library/>jobq<,<libary/>jobq,...>                    */
/*                                                                  */ 
/*          Specifies one or more job queses whose jobs are to      */
/*          be included in the list.                                */ 
/*                                                                  */
/*          Examples: /jobq QBATCH                                  */ 
/*                    /jobq QGPL/QBATCH,*LIBL/QBATCH2               */
/*                    /jobq *ALL                                    */ 
/*                                                                  */
/*          If this parameter is not specified, *ALL is used for    */ 
/*          a default.                                              */
/*                                                                  */ 
/*      /sort column1,column2,column3...                            */
/*                                                                  */ 
/*          Specifies one or more column names by which to sort     */
/*          the list.  Column names must be one of the following    */ 
/*          names or integers.                                      */
/*                                                                  */ 
/*              Name            Integer for shorthand               */
/*                                                                  */ 
/*              NAME            1                                   */
/*              USER            2                                   */ 
/*              NUMBER          3                                   */
/*              TYPE            4                                   */ 
/*              SUBTYPE         5                                   */
/*              STATUS          6                                   */ 
/*              DATE            7                                   */
/*              TIME            8                                   */ 
/*              JOBQ            9                                   */
/*              JOBQLIB         10                                  */ 
/*              JOBQPTY         11                                  */
/*              OUTQPTY         12                                  */ 
/*              RUNPTY          13                                  */
/*              SBS             14                                  */ 
/*              SBSLIB          15                                  */
/*              POOLID          16                                  */ 
/*              CPUUSED         17                                  */
/*              AUXIO           18                                  */ 
/*              TRANS           19                                  */
/*              RESPONSE        20                                  */ 
/*                                                                  */
/*          If multiple column names are provided they must be      */ 
/*          separated by commas with no intervening blanks.         */
/*                                                                  */ 
/*          Examples: /sort USER,TYPE,DATE                          */
/*                    /sort 2,4,7                                   */ 
/*                                                                  */
/*          If this parameter is not specified, the jobs will be    */ 
/*          displayed in the default order created by OS/400.       */
/*                                                                  */ 
/*      /disallowactions action1,action2,action3...                 */
/*                                                                  */ 
/*          Specifies one or more action names the user will NOT    */
/*          be allowed to perform on the jobs in the list.          */ 
/*          Action names must be one of the following names or      */
/*          integers.                                               */ 
/*                                                                  */
/*              Name            Integer for shorthand               */ 
/*                                                                  */
/*              HOLD            1                                   */ 
/*              DELETE          2                                   */
/*              RELEASE         3                                   */ 
/*              PROPERTIES      4                                   */
/*              REPLYMSG        5                                   */ 
/*              HELP            6                                   */
/*              MOVE            7                                   */ 
/*              OUTPUT          8                                   */
/*              JOBLOG          9                                   */ 
/*                                                                  */
/*          If multiple action names are provided they must be      */ 
/*          separated by commas with no intervening blanks.         */
/*                                                                  */ 
/*          Examples: /disallowactions DELETE,JOBLOG                */
/*                    /disallowactions 2,9                          */ 
/*                                                                  */
/*          If this parameter is not specified, the user will be    */ 
/*          allowed to perform all of the actions (unless the       */
/*          user is prohibited through OS/400 authority values).    */ 
/*                                                                  */
/*      /disallowfilter  Y | N                                      */ 
/*                                                                  */
/*          Disallows the user from changing the filter values      */ 
/*          via the "Include..." item of the "View" pull-down       */
/*          menu.                                                   */ 
/*                                                                  */
/*          Examples: /disallowfilter Y                             */ 
/*                                                                  */
/*      /listtype type-value                                        */ 
/*                                                                  */
/*          Specifies the type of jobs list to be displayed. One    */ 
/*          of the following special values must be specified.      */
/*                                                                  */ 
/*              A   All jobs                                        */
/*              S   Server jobs                                     */ 
/*                                                                  */
/*          Examples: /listtype A                                   */ 
/*                    /listtype S                                   */
/*                                                                  */ 
/*          If this parameter is not specified, A is used for a     */
/*          default.                                                */ 
/*                                                                  */
/*      /currentuser type-value                                     */ 
/*                                                                  */
/*          Specifies the current user(s) for the jobs in the list. */ 
/*          This parameter is only allowed if /listtype S is        */
/*          specified (Server jobs)                                 */ 
/*                                                                  */
/*          Examples: /currentuser TLK                              */ 
/*                    /currentuser TLK,JRSMITH                      */
/*                                                                  */ 
/*          If this parameter is not specified, server jobs for all */
/*          current users are shown.                                */ 
/*                                                                  */
/*      /primarystatus type-value                                   */ 
/*                                                                  */
/*          Specifies the primary status(s) for the jobs in the     */ 
/*          list. This parameter is only allowed if /listtype S is  */
/*          specified (Server jobs)                                 */ 
/*                                                                  */
/*          Examples: /primarystatus *ACTIVE                        */ 
/*                    /primarystatus *ACTIVE,*JOBQ                  */
/*      		      /primarystatus *OUTQ                          */ 
/*      		      /primarystatus *ALL                           */
/*                                                                  */ 
/*          If this parameter is not specified, only *ACTIVE server */
/*          jobs are shown                                          */ 
/*                                                                  */
/*                                                                  */ 
/*                                                                  */
/*     ------------------------------------------------------       */ 
/*     The following parameters are supported by lstsplf.exe:       */
/*                                                                  */    
/*      /system system-name                                         */
/*                                                                  */
/*          Specifies the name of the AS/400 system from which      */
/*          the list of spooled files will be built.                */
/*                                                                  */    
/*          Examples: /system ROCH                                  */
/*                                                                  */
/*      /user user1,user2,user3...                                  */
/*                                                                  */
/*          Specifies one or more user profile names whose          */    
/*          spooled files will be included in the list.  If         */
/*          multiple user names are provided they must be           */
/*          separated by commas with no intervening blanks.         */
/*                                                                  */
/*          Examples: /user RWATERS                                 */    
/*                    /user DGILMOUR,NMASON,RWRIGHT,RWATERS         */
/*                    /user *ALL                                    */
/*                    /user *CURRENT    (default)                   */
/*                                                                  */
/*      /outq outq1,outq2,outq3...                                  */    
/*                                                                  */
/*          Specifies one or more output queue names whose          */
/*          spooled files will be included in the list.  The        */
/*          output queue name must be in the form                   */
/*          "library/queue" (without the quotes).  If multiple      */    
/*          queue names are provided they must be separated by      */
/*          commas with no intervening blanks.                      */
/*                                                                  */
/*          Examples: /outq *LIBL/PRT01                             */
/*                    /outq QUSRSYS/PRT01,QUSRSYS/PRT02             */    
/*                    /outq *ALL        (default)                   */
/*                                                                  */
/*      /formtype formtype                                          */
/*                                                                  */
/*          Specifies a formtype value.  Only spooled files with    */    
/*          a matching form type will be included in the list.      */
/*                                                                  */
/*          Examples: /formtype 1040A                               */
/*                    /formtype *ALL    (default)                   */
/*                                                                  */    
/*      /usrdta userdata                                            */
/*                                                                  */
/*          Specifies a user-specified data value.  Only spooled    */
/*          files with a matching user-specified data will be       */
/*          included in the list.                                   */    
/*                                                                  */
/*          Examples: /usrdta CLASSLIST                             */
/*                    /usrdta *ALL      (default)                   */
/*                                                                  */
/*      /status status1,status2,status3...                          */    
/*                                                                  */
/*          Specifies one or more spooled file status values.       */
/*          Only spooled files with a matching status will be       */
/*          included in the list.  If multiple status values are    */
/*          provided they must be separated by commas with no       */    
/*          intervening blanks.                                     */
/*                                                                  */
/*          Examples: /status *READY,*HELD                          */
/*                    /status *ALL      (default)                   */
/*                                                                  */    
/*      /printer printer1,printer2,printer3...                      */
/*                                                                  */
/*          Specifies one or more printer names.  Only spooled      */
/*          files assigned to one of the specified printers will    */
/*          be included in the list.  If multiple printers are      */    
/*          provided they must be separated by commas with no       */
/*          intervening blanks.                                     */
/*                                                                  */
/*          Examples: /printer ACCTNG,PAYROLL                       */
/*                    /printer *ALL     (default)                   */    
/*                                                                  */
/*      /job jobname                                                */
/*                                                                  */
/*          Specifies a qualified OS/400 job name.  Only spooled    */
/*          files created by the specified job name will be         */    
/*          included in the list.                                   */
/*                                                                  */
/*          Examples: /job 012345/RWATERS/DSP01                     */
/*                    /job *            (current job)               */
/*                                                                  */    
/*          If this parameter is not specified, spooled files       */
/*          are included in the list regardless of the creating     */
/*          job.                                                    */
/*                                                                  */
/*      /sort column1,column2,column3...                            */    
/*                                                                  */
/*          Specifies one or more column names by which to sort     */
/*          the list.  Column names must be one of the following    */
/*          names or integers.                                      */
/*                                                                  */    
/*              Name            Integer for shorthand               */
/*                                                                  */
/*              FILENAME        1                                   */
/*              JOBNAME         2                                   */
/*              USERNAME        3                                   */    
/*              JOBNUMBER       4                                   */
/*              FILENUMBER      5                                   */
/*              OUTQ            6                                   */
/*              OUTQLIB         7                                   */
/*              PRINTER         8                                   */    
/*              USERDATA        9                                   */
/*              STATUS          10                                  */
/*              PAGES           11                                  */
/*              COPIES          12                                  */
/*              FORMTYPE        13                                  */    
/*              PRIORITY        14                                  */
/*              DATE            15                                  */
/*              TIME            16                                  */
/*                                                                  */
/*          If multiple column names are provided they must be      */    
/*          separated by commas with no intervening blanks.         */
/*                                                                  */
/*          Examples: /sort USERNAME,DATE,TIME                      */
/*                    /sort 3,15,16                                 */
/*                                                                  */    
/*          If this parameter is not specified, they spooled        */
/*          files will be displayed in the default order created    */
/*          by OS/400.                                              */
/*                                                                  */
/*      /disallowactions action1,action2,action3...                 */    
/*                                                                  */
/*          Specifies one or more action names the user will NOT    */
/*          be allowed to perform on the spooled files in the       */
/*          list.  Action names must be one of the following        */
/*          names or integers.                                      */    
/*                                                                  */
/*              Name            Integer for shorthand               */
/*                                                                  */
/*              PRINTNEXT       1                                   */
/*              SEND            2                                   */    
/*              HOLD            3                                   */
/*              DELETE          4                                   */
/*              OPEN            5                                   */
/*              RELEASE         6                                   */
/*              PROPERTIES      7                                   */    
/*              REPLYMSG        8                                   */
/*              HELP            9                                   */
/*              MOVE            10                                  */
/*              RESTART         11                                  */
/*                                                                  */    
/*          If multiple action names are provided they must be      */
/*          separated by commas with no intervening blanks.         */
/*                                                                  */
/*          Examples: /disallowactions DELETE,PRINTNEXT,MOVE        */
/*                    /disallowactions 4,1,10,7                     */    
/*                                                                  */
/*          If this parameter is not specified, the user will be    */
/*          allowed to perform all of the actions (unless the       */
/*          user is prohibited through OS/400 authority values).    */
/*                                                                  */    
/*      /disallowfilter  Y | N                                      */
/*                                                                  */
/*          Disallows the user from changing the filter values      */
/*          via the "Include..." item of the "View" pull-down       */
/*          menu.                                                   */    
/*                                                                  */
/*          Examples: /disallowfilter Y                             */
/*                                                                  */
/*                                                                  */
/*                                                                  */
/*     -----------------------------------------------------        */ 
/*     The following parameters are supported by lstmsg.exe:        */
/*                                                                  */    
/*      /system system-name                                         */
/*                                                                  */
/*          Specifies the name of the AS/400 system from which      */
/*          the list of messages will be built.                     */
/*                                                                  */    
/*          Examples: /system ROCH                                  */
/*                                                                  */
/*      /severity severity-value                                    */
/*                                                                  */
/*          Specifies the minimum severity of a message to be       */    
/*          included in the list.  The value specified must be      */
/*          between 0 and 99, inclusive.                            */
/*                                                                  */
/*          Examples: /severity 10                                  */
/*                                                                  */    
/*          If this parameter is not specified, 0 will be used      */
/*          as a default.                                           */
/*                                                                  */
/*      /user user-name | *CURRENT                                  */
/*                                                                  */    
/*          Specifies a user name whose messages will be            */
/*          included in the list.                                   */
/*                                                                  */
/*          Special values for user name:                           */
/*                                                                  */    
/*              *CURRENT means messages for the current             */
/*                  user profile name are included in the list.     */
/*                                                                  */
/*                                                                  */
/*          Examples: /user *CURRENT                                */    
/*                    /user RWATERS                                 */
/*                                                                  */
/*          If this parameter is not specified, *CURRENT will be    */
/*          used as a default.                                      */
/*                                                                  */    
/*      /disallowactions action1,action2,action3...                 */
/*                                                                  */
/*          Specifies one or more action names the user will NOT    */
/*          be allowed to perform on the messages in the list.      */
/*          Action names must be one of the following names or      */    
/*          integers.                                               */
/*                                                                  */
/*              Name            Integer for shorthand               */
/*                                                                  */
/*              DELETE          1                                   */    
/*              OPEN            2                                   */
/*              PROPERTIES      3                                   */
/*              REPLYMSG        4                                   */
/*              HELP            5                                   */
/*                                                                  */    
/*          If multiple action names are provided they must be      */
/*          separated by commas with no intervening blanks.         */
/*                                                                  */
/*          Examples: /disallowactions HELP                         */
/*                    /disallowactions 1                            */    
/*                                                                  */
/*          If this parameter is not specified, the user will be    */
/*          allowed to perform all of the actions (unless the       */
/*          user is prohibited through OS/400 authority values).    */
/*                                                                  */    
/*      /disallowfilter  Y | N                                      */
/*                                                                  */
/*          Disallows the user from changing the filter values      */
/*          via the "Include..." item of the "View" pull-down       */
/*          menu.                                                   */    
/*                                                                  */
/*          Examples: /disallowfilter Y                             */
/*                                                                  */
/*                                                                  */
/*                                                                  */
/*     -----------------------------------------------------        */
/*     The following parameters are supported by lstprt.exe:        */
/*                                                                  */    
/*      /system system-name                                         */
/*                                                                  */
/*          Specifies the name of the AS/400 system from which the  */
/*          list of printers will be built.                         */
/*                                                                  */
/*          Examples: /system ROCH                                  */
/*                                                                  */
/*      /printer printer1,printer2,printer3...                      */
/*                                                                  */
/*          Specifies one or more printer names to be included      */
/*          in the list.  If multiple printers are provided they    */
/*          must be separated by commas with no intervening         */
/*          blanks.                                                 */
/*                                                                  */
/*          Examples: /printer ACCTNG,PAYROLL                       */
/*                    /printer *ALL     (default)                   */
/*                                                                  */
/*      /disallowactions action1,action2,action3...                 */
/*                                                                  */
/*          Specifies one or more action names the user will NOT    */
/*          be allowed to perform on the printers in the list.      */
/*          Action names must be one of the following names or      */
/*          integers.                                               */
/*                                                                  */
/*              Name            Integer for shorthand               */
/*                                                                  */
/*              HOLD            1                                   */
/*              RELEASE         2                                   */
/*              PROPERTIES      3                                   */
/*              REPLYMSG        4                                   */
/*              HELP            5                                   */
/*              RESTART         6                                   */
/*              OUTPUT          7                                   */
/*              START           8                                   */
/*              STOP            9                                   */
/*              AVAIL           10                                  */
/*              UNAVAIL         11                                  */
/*                                                                  */
/*          If multiple action names are provided they must be      */
/*          separated by commas with no intervening blanks.         */
/*                                                                  */
/*          Examples: /disallowactions AVAIL,UNAVAIL                */
/*                    /disallowactions 9,10                         */
/*                                                                  */
/*          If this parameter is not specified, the user will be    */
/*          allowed to perform all of the actions (unless the       */
/*          user is prohibited through OS/400 authority values).    */
/*                                                                  */
/*      /disallowfilter   Y | N                                     */
/*                                                                  */
/*          Disallows the user from changing the filter values      */
/*          via the "Include..." item of the "View" pull-down       */
/*          menu.                                                   */
/*                                                                  */
/*          Examples: /disallowfilter Y                             */
/*                                                                  */
/*                                                                  */
/*                                                                  */
/*     -----------------------------------------------------        */
/*     The following parameters are supported by lstjbl.exe:        */
/*                                                                  */    
/*      /system system-name                                         */
/*                                                                  */
/*          Specifies the name of the AS/400 system on which the    */
/*          job resides                                             */
/*                                                                  */
/*          Examples: /system RCHAS1                                */
/*                                                                  */
/*                                                                  */
/*      /job jobname                                                */
/*                                                                  */
/*          Specifies a qualified OS/400 job name in the form       */
/*          jobnbr/user/jobname.                                    */
/*                                                                  */
/*                                                                  */
/*          Example: /job 014369/QUSER/DSP01                        */
/*                                                                  */
/*                                                                  */
/*                                                                  */
/*                                                                  */
/*   BOOL bDisplayErrorMsg - input                                  */
/*     Indicator of whether or not this code should display an      */
/*     error message if an error occurs on the CreateProcess API.   */
/*                                                                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   Returns a boolean value.                                       */
/*                                                                  */
/*    TRUE   - If the CreateProcess call to invoke the command is   */
/*             successful.                                          */
/*    FALSE  - If the CreateProcess call to invoke the command is   */
/*             NOT successful.                                      */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
CWBAPI BOOL WINAPI cwbUN_DisplaySOAList(const char *  szSystemName,	
								        const char *  szCommand,	
								        BOOL          bDisplayErrorMsg);


CWBAPI BOOL WINAPI cwbUN_DisplaySOAListW(const wchar_t *  szSystemName,	
								        const wchar_t *  szCommand,	
								        BOOL          bDisplayErrorMsg);


#if ( defined(CWB_UNICODE) )
   #define cwbUN_DisplaySOAList       cwbUN_DisplaySOAListW
#endif


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetTypeFromItemId                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Extracts the item type field from a Unity item identifier      */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * szItemId - input                                  */
/*     The Unity item identifier from which the item type will be   */
/*     extracted                                                    */
/*                                                                  */
/*   char * szType - output                                         */
/*     Address of the buffer that will receive the null-terminated  */
/*     item type                                                    */
/*                                                                  */
/*   UINT cchMax - input                                            */
/*     Size of the buffer that will receive the null-terminated     */
/*     item type                                                    */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_FORMAT_NOT_VALID - specified item identifier not valid   */
/*   CWB_BUFFER_OVERFLOW - the buffer is too small to contain the   */
/*                         returned string                          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   <usage notes>                                                  */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_GetTypeFromItemId(
    const char * szItemId,	
    char * szType,	
    UINT cchMax
    );
 
CWBAPI unsigned int WINAPI cwbUN_GetTypeFromItemIdW(
    const wchar_t * szItemId,	
    wchar_t * szType,	
    UINT cchMax
    );


#if ( defined(CWB_UNICODE) )
   #define cwbUN_GetTypeFromItemId       cwbUN_GetTypeFromItemIdW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetTypeFromName                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   Extracts the item type field from a fully-qualified Unity      */
/*   object name                                                    */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * szObjectName - input                              */
/*     The Unity object name from which the item index will be      */
/*     extracted                                                    */
/*                                                                  */
/*   char * szType - output                                         */
/*     Address of the buffer that will receive the null-terminated  */
/*     item type                                                    */
/*                                                                  */
/*   UINT cchMax - input                                            */
/*     Size of the buffer that will receive the null-terminated     */
/*     item type                                                    */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_FORMAT_NOT_VALID - specified object name is not valid    */
/*   CWB_BUFFER_OVERFLOW - the buffer is too small to contain the   */
/*                         returned string                          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   <usage notes>                                                  */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_GetTypeFromName(
    const char * szObjectName,	
    char * szType,	
    UINT cchMax
    );
 
CWBAPI unsigned int WINAPI cwbUN_GetTypeFromNameW(
    const wchar_t * szObjectName,	
    wchar_t * szType,	
    UINT cchMax
    );

#if ( defined(CWB_UNICODE) )
   #define cwbUN_GetTypeFromName       cwbUN_GetTypeFromNameW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetTypeFromPidl                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   Extracts the item index field from a fully-qualified Unity     */
/*   item identifier list                                           */
/*                                                                  */
/* Parameters:                                                      */
/*   LPCITEMIDLIST pidl - input                                     */
/*     Pointer to an ITEMIDLIST (item identifier list) structure    */
/*     from which the item index will be extracted                  */
/*                                                                  */
/*   char * szType - output                                         */
/*     Address of the buffer that will receive the null-terminated  */
/*     item type                                                    */
/*                                                                  */
/*   UINT cchMax - input                                            */
/*     Size of the buffer that will receive the null-terminated     */
/*     item type                                                    */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_FORMAT_NOT_VALID - the specified item identifier list is */
/*                            not valid                             */
/*   CWB_BUFFER_OVERFLOW - the buffer is too small to contain the   */
/*                         returned string                          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   <usage notes>                                                  */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_GetTypeFromPidl(
    LPCITEMIDLIST pidl,
    char * szType,	
    UINT cchMax
    );
 
CWBAPI unsigned int WINAPI cwbUN_GetTypeFromPidlW(
    LPCITEMIDLIST pidl,
    wchar_t * szType,	
    UINT cchMax
    );

#if ( defined(CWB_UNICODE) )
   #define cwbUN_GetTypeFromPidl       cwbUN_GetTypeFromPidlW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetUserAttribute                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns a string containing the value of a user profile        */
/*   attribute for the current Operations Navigator user            */
/*                                                                  */
/* Parameters:                                                      */
/*   USHORT usAttributeId - input                                   */
/*     A numeric value which identifies the user attribute value to */
/*     be retrieved.  The user attribute constants are defined in   */
/*     the header file 'cwba4usr.h'.                                */
/*                                                                  */
/*   const char * szSystemName - input                              */
/*     The name of the AS/400 system on which to retrieve the user  */
/*     attribute                                                    */ 
/*                                                                  */
/*   char * szValue - output                                        */
/*     Address of the buffer that will receive the null-terminated  */
/*     attribute value string                                       */
/*                                                                  */
/*   UINT cchMax - input                                            */
/*     Size of the buffer that will receive the null-terminated     */
/*     value string                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_INTERNAL_ERROR - attribute value could not be retrieved  */
/*   CWB_BUFFER_OVERFLOW - the buffer is too small to contain the   */
/*                         returned string                          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The value returned by this API is NOT an NLS string and is not */
/*   translated.  For example, '*NONE' will be returned instead of  */
/*   'None'.                                                        */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_GetUserAttribute(
	USHORT usAttributeId,
    const char * szSystemName,	
    char * szValue,	
    UINT cchMax
    );

CWBAPI unsigned int WINAPI cwbUN_GetUserAttributeW(
	USHORT usAttributeId,
    const wchar_t * szSystemName,	
    wchar_t * szValue,	
    UINT cchMax
    );

#if ( defined(CWB_UNICODE) )
   #define cwbUN_GetUserAttribute       cwbUN_GetUserAttributeW
#endif
/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_IsConnectionTypeTCPIP                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   Determine if the system connection is using TCP/IP for         */
/*   communications                                                 */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * szSystemName - input                              */
/*     The name of the AS/400 system which will be checked to       */
/*     determine if a TCP/IP connection is being used               */ 
/*                                                                  */
/* Return Codes:                                                    */
/*   Returns a boolean value (type cwb_Boolean)   .                 */
/*                                                                  */
/*    CWB_TRUE   - If the connection is TCP/IP                      */
/*    CWB_FALSE  - If the connection is not TCP/IP                  */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI BOOL WINAPI cwbUN_IsConnectionTypeTCPIP(
    const char * szSystemName	
    );

CWBAPI BOOL WINAPI cwbUN_IsConnectionTypeTCPIPW(
    const wchar_t * szSystemName	
    );

#if ( defined(CWB_UNICODE) )
   #define cwbUN_IsConnectionTypeTCPIP       cwbUN_IsConnectionTypeTCPIPW
#endif


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_IsSubcomponentInstalled                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   Determines if a specified Operations Navigator Install option  */
/*   is installed.                                                  */
/*                                                                  */
/* Parameters:                                                      */
/*   UINT uOption - input                                           */
/*     Specification of the Operations Navigator option to check.   */
/*     The following values are supported:                          */
/*       CWBUN_OPNAV_BASE                                           */
/*       CWBUN_OPNAV_BASIC_OPERATIONS                               */
/*       CWBUN_OPNAV_JOB_MANAGEMENT                                 */
/*       CWBUN_OPNAV_SYSTEM_CONFIGURATION                           */
/*       CWBUN_OPNAV_NETWORK                                        */
/*       CWBUN_OPNAV_SECURITY                                       */
/*       CWBUN_OPNAV_USERS_GROUPS                                   */
/*       CWBUN_OPNAV_DATABASE                                       */
/*       CWBUN_OPNAV_FILESYSTEMS                                    */
/*       CWBUN_OPNAV_MULTIMEDIA                                     */
/*       CWBUN_OPNAV_BACKUP                                         */
/*       CWBUN_OPNAV_APP_DEV                                        */
/*       CWBUN_OPNAV_SYSTEM_MGMT         	    	    		    */
/*       CWBUN_OPNAV_ADMINISTRATION                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   Returns a boolean value.                                       */
/*                                                                  */
/*    TRUE   - If the subcomponent is installed.                    */
/*    FALSE  - If the subcomponent is not installed.                */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use this function to determine if an Operations Navigator      */
/*   install option is currently installed.                         */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI BOOL WINAPI cwbUN_IsSubcomponentInstalled(
    UINT uOption
    );
 


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_RefreshAll                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Refreshes the contents of both the tree and list windows of    */
/*   the Operations Navigator                                       */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * pszStatusText - input                             */
/*     A null-terminated string to be placed in the status bar      */
/*     window upon completion.  This parameter may be NULL.         */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_WINDOW_NOTAVAIL - the view windows could not be found    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use this function to refresh the entire contents of the        */
/*   Operations Navigator after performing an action requested      */
/*   by the user.                                                   */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_RefreshAll(
    const char * pszStatusText	
    );

CWBAPI unsigned int WINAPI cwbUN_RefreshAllW(
    const wchar_t * pszStatusText	
    );

#if ( defined(CWB_UNICODE) )
   #define cwbUN_RefreshAll       cwbUN_RefreshAllW
#endif
 
/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_RefreshList                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Refreshes the contents of the list view window of the          */
/*   Operations Navigator                                           */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * pszStatusText - input                             */
/*     A null-terminated string to be placed in the status bar      */
/*     window upon completion.  This parameter may be NULL.         */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_WINDOW_NOTAVAIL - list view window could not be found    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use this function to refresh the contents of the list window   */
/*   after performing an action requested by the user.              */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_RefreshList(
    const char * pszStatusText	
    );

CWBAPI unsigned int WINAPI cwbUN_RefreshListW(
    const wchar_t * pszStatusText	
    );

#if ( defined(CWB_UNICODE) )
   #define cwbUN_RefreshList       cwbUN_RefreshListW
#endif
/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_RefreshListItems                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Refreshes the currently selected item(s) in the list view      */
/*   window of the Operations Navigator                             */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * pszStatusText - input                             */
/*     A null-terminated string to be placed in the status bar      */
/*     window upon completion.  This parameter may be NULL.         */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_WINDOW_NOTAVAIL - list view window could not be found    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use this function to refresh the selected items in the list    */
/*   window after performing an action requested by the user.       */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_RefreshListItems(
    const char * pszStatusText	
    );

CWBAPI unsigned int WINAPI cwbUN_RefreshListItemsW(
    const wchar_t * pszStatusText	
    );

#if ( defined(CWB_UNICODE) )
   #define cwbUN_RefreshListItems       cwbUN_RefreshListItemsW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_RefreshListHidden                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Refreshes one or more items in the list view window of         */
/*   the Operations Navigator. If the list is not being displayed   */
/*   it is removed from the cache of active lists. The next time    */
/*   the user selects the list it will be retrieved from the        */
/*   server.                                                        */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * szObjectName - input                              */
/*     The object name of the list to refresh.                      */
/*                                                                  */
/*   const char * szStatusText - input                              */
/*     A null-terminated string to be placed in the status bar      */
/*     window upon completion.  This parameter may be NULL.         */
/*                                                                  */
/*   const int nIndices[] - input                                   */
/*     An array of zero-based indices to update in the list.        */
/*                                                                  */
/*   const int nItems - input                                       */
/*     The number of items in the input array.                      */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - successful completion.                                */
/*   CWBUN_BAD_PARAMETER - an input parameter was not valid.        */
/*   CWBUN_REFRESH_FAILED - failed to update the items.             */
/*   CWBUN_FORMAT_NOT_VALID - specified object name is not valid.   */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use this function to refresh one or more items in the          */
/*   list window after performing an action requested by the user.  */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_RefreshListHidden(
    const char * szObjectName,	
    const char * szStatusText,	
    const int nIndices[],
    const int nItems
);
 
CWBAPI unsigned int WINAPI cwbUN_RefreshListHiddenW(
    const wchar_t * szObjectName,	
    const wchar_t * szStatusText,	
    const int nIndices[],
    const int nItems
);

#if ( defined(CWB_UNICODE) )
   #define cwbUN_RefreshListHidden       cwbUN_RefreshListHiddenW
#endif
/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_UpdateStatusBar                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   Inserts a text string into the status bar of the Operations    */
/*   Navigator window                                               */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * pszStatusText - input                             */
/*     A null-terminated string to be placed in the status bar      */
/*     window upon completion.                                      */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_WINDOW_NOTAVAIL - status bar window could not be found   */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use this function to inform the user that an action requested  */
/*   by clicking the OK button on a dialog has completed            */
/*   successfully.                                                  */
/*                                                                  */
/*   The following APIs are affected by this call:                  */
/*     <API list>                                                   */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_UpdateStatusBar(
    const char * pszStatusText	
    );

CWBAPI unsigned int WINAPI cwbUN_UpdateStatusBarW(
    const wchar_t * pszStatusText	
    );

#if ( defined(CWB_UNICODE) )
   #define cwbUN_UpdateStatusBar       cwbUN_UpdateStatusBarW
#endif



/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_OpenLocalLdapServer                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Creates a handle which can be used to access configuration     */
/*   information about the Directory Services (LDAP) server on the  */
/*   AS/400.                                                        */
/*                                                                  */
/* Parameters:                                                      */
/*   LPCSTR system - input                                          */
/*     pointer to AS/400 system name.                               */
/*                                                                  */
/*   cwbUN_ldapSvrHandle *pHandle - output                          */
/*     On return, contains a handle that can be used with the       */
/*     following APIs:                                              */
/*       cwbUN_FreeLocalLdapServer                                  */
/*       cwbUN_GetLdapSvrPort                                       */
/*       cwbUN_GetLdapSvrSuffixCount                                */
/*       cwbUN_GetLdapSuffixName                                    */
/*                                                                  */
/*     This handle should be released with a call to                */
/*       cwbUN_FreeLocalLdapServer                                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_PARAMETER  - Invalid parameter specified.      */
/*   CWB_INVALID_POINTER - A NULL pointer was specified.            */
/*   CWBUN_LDAP_NOT_AVAIL - Directory services is not installed     */
/*                          or the server has not been configured.  */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/

int cwbUN_OpenLocalLdapServerW
    ( LPCWSTR              system,
      cwbUN_ldapSvrHandle  *pHandle
    );

int cwbUN_OpenLocalLdapServerA
    ( LPCSTR               system,	
      cwbUN_ldapSvrHandle  *pHandle
    );

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbUN_OpenLocalLdapServer cwbUN_OpenLocalLdapServerW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbUN_OpenLocalLdapServer cwbUN_OpenLocalLdapServerA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_FreeLocalLdapServer                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Free resources associated with the input handle.               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbUN_ldapSvrHandle handle - input                             */
/*     The handle for which resources should be freed.              */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - handle was not created by             */
/*                            cwbUN_OpenLocalLdapServer()           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The handle is obtained by a call to cwbUN_OpenLocalLdapServer. */
/*                                                                  */
/********************************************************************/

int cwbUN_FreeLocalLdapServer
    ( cwbUN_ldapSvrHandle  handle
    );

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetLdapSvrPort                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the port number used by the LDAP server.               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbUN_ldapSvrHandle handle - input                             */
/*     A handle previously obtained by a call to                    */
/*     cwbUN_OpenLocalLdapServer()                                  */
/*                                                                  */
/*   int * port - output                                            */
/*     The port number used for LDAP connections.                   */
/*                                                                  */
/*   int * sslPort - output                                         */
/*     The port number used for SSL connections                     */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid handle.                       */
/*   CWB_INVALID_POINTER - A NULL pointer was specified.            */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/

int cwbUN_GetLdapSvrPort
    ( cwbUN_ldapSvrHandle  handle,
      int                  *port,
	  int                  *sslPort
    );

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetLdapSvrSuffixCount                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the number of suffixes configured for this server.     */
/*   A suffix is the distinguighed name (DN) of a starting point    */
/*   in the directory tree.                                         */
/*                                                                  */
/*   This count includes a special suffix, cn=localhost, which      */
/*   is used only by the server for purposes such as replication.   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbUN_ldapSvrHandle handle - input                             */
/*     A handle previously obtained by a call to                    */
/*     cwbUN_OpenLocalLdapServer()                                  */
/*                                                                  */
/*   int * count - output                                           */
/*     The number of suffixes present on the server.                */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid handle.                       */
/*   CWB_INVALID_POINTER - A NULL pointer was specified.            */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/

int cwbUN_GetLdapSvrSuffixCount
    ( cwbUN_ldapSvrHandle  handle,
      int                  *count
    );

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetLdapSuffixName                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the distinguished name of the suffix.                  */
/*                                                                  */
/*   A special suffix, cn=localhost, could be returned which        */
/*   is used only by the server for purposes such as replication.   */
/*                                                                  */
/*   Versions of this API can return results in the following       */
/*   formats:                                                       */
/*     ANSI                                                         */
/*     Unicode                                                      */
/*     UTF-8 (for use with version 3 LDAP servers)                  */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbUN_ldapSuffixHandle handle - input                          */
/*     A handle previously obtained by a call to                    */
/*     cwbUN_OpenLocalLdapServer()                                  */
/*                                                                  */
/*   int index - input                                              */
/*     zero-based index of the suffix.  This value must be less     */
/*     than the count returned by cwbUN_GetLdapSvrSuffixCount().    */
/*                                                                  */
/*   LPSTR suffix - output                                          */
/*     Pointer to the buffer that will contain the distinguished    */
/*     name of the suffix.                                          */
/*                                                                  */
/*   int * length - input/output                                    */
/*     Pointer to the length of the suffix buffer.  If the buffer   */
/*     is too small to hold the string, including space for the     */
/*     terminating NULL, the size of the buffer needed will be      */
/*     filled into this parameter.                                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid handle.                       */
/*   CWB_INVALID_API_PARAMETER - Invalid index.                     */
/*   CWB_INVALID_POINTER - A NULL pointer was specified.            */
/*   CWB_BUFFER_OVERFLOW - The suffix buffer is not large enough    */
/*                         to hold the entire result.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/

int cwbUN_GetLdapSuffixNameA
    ( cwbUN_ldapSvrHandle      handle,
      int                      index,
      LPSTR                    suffix,	
      int                      *length
    );

int cwbUN_GetLdapSuffixNameW
    ( cwbUN_ldapSvrHandle      handle,
      int                      index,
      LPWSTR                   suffix,
      int                      *length
    );

int cwbUN_GetLdapSuffixName8 /* returns suffix in UTF-8 */
    ( cwbUN_ldapSvrHandle      handle,
      int                      index,
      LPSTR                    suffix,	
      int                      *length
    );

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbUN_GetLdapSuffixName cwbUN_GetLdapSuffixNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbUN_GetLdapSuffixName cwbUN_GetLdapSuffixNameA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_OpenLdapPublishing                                       */
/*                                                                  */
/* Purpose:                                                         */
/*   Creates a handle which can be used to access configuration     */
/*   information about information published by this AS/400 to      */
/*   LDAP directories.                                              */
/*                                                                  */
/*   This handle is used to access a set of "publish records".      */
/*   Each publish record identifies a type of information that      */
/*   is published by the AS/400 (for example, users), and how/where */
/*   the information is published.                                  */
/*                                                                  */
/* Parameters:                                                      */
/*   LPCSTR system - input                                          */
/*     pointer to AS/400 system name.                               */
/*                                                                  */
/*   cwbUN_ldapPubHandle * pHandle - output                         */
/*     On return, contains a handle that can be used with the       */
/*     following APIs:                                              */
/*       cwbUN_FreeLdapPublishing                                   */
/*       cwbUN_GetLdapPublishCount                                  */
/*       cwbUN_GetLdapPublishType                                   */
/*       cwbUN_GetLdapPublishParentDn                               */
/*       cwbUN_GetLdapPublishServer                                 */
/*       cwbUN_GetLdapPublishPort                                   */
/*                                                                  */
/*     This handle should be released with a call to                */
/*     cwbUN_FreeLdapPublishing().                                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_PARAMETER - Index is out of range.             */
/*   CWB_INVALID_API_HANDLE - Invalid handle.                       */
/*   CWB_INVALID_POINTER - A NULL pointer was specified.            */
/*   CWBUN_LDAP_NOT_AVAIL - Directory services is not installed     */
/*                          or the server has not been configured.  */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/

int cwbUN_OpenLdapPublishingW
    ( LPCWSTR              system,
      cwbUN_ldapPubHandle  *pHandle
    );

int cwbUN_OpenLdapPublishingA
    ( LPCSTR               system,	
      cwbUN_ldapPubHandle  *pHandle
    );

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbUN_OpenLdapPublishing cwbUN_OpenLdapPublishingW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbUN_OpenLdapPublishing cwbUN_OpenLdapPublishingA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_FreeLdapPublishing                                       */
/*                                                                  */
/* Purpose:                                                         */
/*   Free resources associated with the input handle.               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbUN_ldapPubHandle handle - input                             */
/*     The handle for which resources should be freed.              */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - handle was not created by             */
/*                            cwbUN_OpenLdapPublishing()            */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The handle is obtained by a call to                            */
/*    cwbUN_OpenLdapPublishing().                                   */
/*                                                                  */
/********************************************************************/

int cwbUN_FreeLdapPublishing
    ( cwbUN_ldapPubHandle  handle
    );

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetLdapPublishCount                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the number of publishing records configured for this   */
/*   AS/400.  A publish record identifies a category of information */
/*   to be published, and how/where it is to be published.          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbUN_ldapPubHandle handle - input                             */
/*     A handle previously obtained by a call to                    */
/*     cwbUN_OpenLdapPublishing().                                  */
/*                                                                  */
/*   int * count - output                                           */
/*     The number of publish records configured on the AS/400.      */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid handle.                       */
/*   CWB_INVALID_POINTER - A NULL pointer was specified.            */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/

int cwbUN_GetLdapPublishCount
    ( cwbUN_ldapPubHandle  handle,
      int                  *count
    );

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetLdapPublishType                                       */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the type of information this publish record is for.    */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbUN_ldapPubHandle handle - input                             */
/*     A handle previously obtained by a call to                    */
/*     cwbUN_OpenLdapPublishing().                                  */
/*                                                                  */
/*   int index - input                                              */
/*     zero-based index of the publish record. This value must be   */
/*     less than the count returned by cwbUN_GetLdapPublishCount(). */
/*                                                                  */
/*   cwbUN_LdapPubCategories * information - output                 */
/*     The type of information this publish record is for.          */
/*                                                                  */
/*     Possible values include:                                     */
/*       CWBUN_LDAP_PUBLISH_USER_DEFINED                            */
/*       CWBUN_LDAP_PUBLISH_USERS                                   */
/*       CWBUN_LDAP_PUBLISH_COMPUTERS                               */
/*       CWBUN_LDAP_PUBLISH_NETWORK_INVENTORY                       */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid handle.                       */
/*   CWB_INVALID_API_PARAMETER - Invalid index.                     */
/*   CWB_INVALID_POINTER - A NULL pointer was specified.            */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/

int cwbUN_GetLdapPublishType
    ( cwbUN_ldapPubHandle      handle,
      int                      index,
      cwbUN_LdapPubCategories  *information
    );

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetLdapPublishAgentName                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the name of publishing agent this record is for.       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbUN_ldapPubHandle handle - input                             */
/*     A handle previously obtained by a call to                    */
/*     cwbUN_OpenLdapPublishing().                                  */
/*                                                                  */
/*   int index - input                                              */
/*     zero-based index of the publish record. This value must be   */
/*     less than the count returned by cwbUN_GetLdapPublishCount(). */
/*                                                                  */
/*   LPSTR agent - output                                           */
/*     Pointer to the buffer that will contain the name of the      */
/*     agent.                                                       */
/*                                                                  */
/*     The following strings are used by AS/400:                    */
/*         "*AS400_USERS"                                           */
/*         "*AS400_COMPUTERS"                                       */
/*     Other strings may be defined by other applications installed */
/*     on the AS/400.                                               */
/*                                                                  */
/*   int * length - input/output                                    */
/*     Pointer to the length of the agent buffer.  If the buffer    */
/*     is too small to hold the string, including space for the     */
/*     terminating NULL, the size of the buffer needed will be      */
/*     filled into this parameter.                                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid handle.                       */
/*   CWB_INVALID_API_PARAMETER - Invalid index.                     */
/*   CWB_INVALID_POINTER - A NULL pointer was specified.            */
/*   CWB_BUFFER_OVERFLOW - The suffix buffer is not large enough    */
/*                         to hold the entire result.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/

int cwbUN_GetLdapPublishAgentNameA
    ( cwbUN_ldapPubHandle      handle,
      int                      index,
      LPSTR                    agent,	
      int                      *length
    );

int cwbUN_GetLdapPublishAgentNameW
    ( cwbUN_ldapPubHandle      handle,
      int                      index,
      LPWSTR                   agent,
      int                      *length
    );

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbUN_GetLdapPublishAgentName cwbUN_GetLdapPublishAgentNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbUN_GetLdapPublishAgentName cwbUN_GetLdapPublishAgentNameA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetLdapPublishEnabled                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns a boolean flag indicating whether the selected         */
/*   publishing agent is enabled.                                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbUN_ldapPubHandle handle - input                             */
/*     A handle previously obtained by a call to                    */
/*     cwbUN_OpenLdapPublishing().                                  */
/*                                                                  */
/*   int index - input                                              */
/*     zero-based index of the publish record. This value must be   */
/*     less than the count returned by cwbUN_GetLdapPublishCount(). */
/*                                                                  */
/*   BOOL * enabled - output                                        */
/*     Flag indicating whether this publishing agent is enabled.    */
/*                                                                  */
/*     Possible values include:                                     */
/*        FALSE - publishing is not enabled                         */
/*        TRUE - publishing is enabled                              */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid handle.                       */
/*   CWB_INVALID_API_PARAMETER - Invalid index.                     */
/*   CWB_INVALID_POINTER - A NULL pointer was specified.            */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/

int cwbUN_GetLdapPublishEnabled
    ( cwbUN_ldapPubHandle      handle,
      int                      index,
      BOOL                     *enabled
    );

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetLdapPublishServer                                     */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the name of server this information is published to.   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbUN_ldapPubHandle handle - input                             */
/*     A handle previously obtained by a call to                    */
/*     cwbUN_OpenLdapPublishing().                                  */
/*                                                                  */
/*   int index - input                                              */
/*     zero-based index of the publish record. This value must be   */
/*     less than the count returned by cwbUN_GetLdapPublishCount(). */
/*                                                                  */
/*   LPSTR server - output                                          */
/*     Pointer to the buffer that will contain the name of the      */
/*     server.                                                      */
/*                                                                  */
/*   int * length - input/output                                    */
/*     Pointer to the length of the server buffer.  If the buffer   */
/*     is too small to hold the string, including space for the     */
/*     terminating NULL, the size of the buffer needed will be      */
/*     filled into this parameter.                                  */
/*                                                                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid handle.                       */
/*   CWB_INVALID_API_PARAMETER - Invalid index.                     */
/*   CWB_INVALID_POINTER - A NULL pointer was specified.            */
/*   CWB_BUFFER_OVERFLOW - The suffix buffer is not large enough    */
/*                         to hold the entire result.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/

int cwbUN_GetLdapPublishServerW
    ( cwbUN_ldapPubHandle  handle,
      int                  index,
      LPWSTR               server,
      int                  *length
    );

int cwbUN_GetLdapPublishServerA
    ( cwbUN_ldapPubHandle  handle,
      int                  index,
      LPSTR                server,	
      int                  *length
    );

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbUN_GetLdapPublishServer cwbUN_GetLdapPublishServerW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbUN_GetLdapPublishServer cwbUN_GetLdapPublishServerA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetLdapPublishPort                                       */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the port number of the server used to publish this     */
/*   information.                                                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbUN_ldapPubHandle handle - input                             */
/*     A handle previously obtained by a call to                    */
/*     cwbUN_OpenLdapPublishing().                                  */
/*                                                                  */
/*   int index - input                                              */
/*     zero-based index of the publish record. This value must be   */
/*     less than the count returned by cwbUN_GetLdapPublishCount(). */
/*                                                                  */
/*   int * port - output                                            */
/*     The port number used to connect to the server.               */
/*                                                                  */
/*   cwbUN_LdapCnnSecurity * connectionSecurity - output            */
/*     The type of connection used to connect to the server. This   */
/*     indicates the type of connection that can be established     */
/*     over the associated port.                                    */
/*                                                                  */
/*     Possible values include:                                     */
/*       CWBUN_LDAP_CNN_NORMAL - a normal connection is used         */
/*       CWBUN_LDAP_CNN_SSL - a SSL connection is used.              */
/*                                                                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid handle.                       */
/*   CWB_INVALID_API_PARAMETER - Invalid index.                     */
/*   CWB_INVALID_POINTER - A NULL pointer was specified.            */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/

int cwbUN_GetLdapPublishPort
    ( cwbUN_ldapPubHandle      handle,
      int                      index,
      int                      *port,
      cwbUN_LdapCnnSecurity    *connectionSecurity
    );

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetLdapPublishParentDn                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the parent distinguished name of the published         */
/*   objects.  For example, if the parentDN for publishing users    */
/*   was cn=users,o=ace industry,c=us, and user information was     */
/*   published for John Smith, the dn of the published object could */
/*   be cn=john smith,cn=users,ou=ace industry,c=us.                */
/*                                                                  */
/*   Versions of this API can return results in the following       */
/*   formats:                                                       */
/*     ANSI                                                         */
/*     Unicode                                                      */
/*     UTF-8 (for use with version 3 LDAP servers)                  */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbUN_ldapPubHandle handle - input                             */
/*     A handle previously obtained by a call to                    */
/*     cwbUN_OpenLdapPublishing().                                  */
/*                                                                  */
/*   int index - input                                              */
/*     zero-based index of the publish record. This value must be   */
/*     less than the count returned by cwbUN_GetLdapPublishCount(). */
/*                                                                  */
/*   LPSTR parentDn - output                                        */
/*     Pointer to the buffer that will contain the name of the      */
/*     parentDn.                                                    */
/*                                                                  */
/*   int * length - input/output                                    */
/*     Pointer to the length of the parentDn buffer.  If the buffer */
/*     is too small to hold the string, including space for the     */
/*     terminating NULL, the size of the buffer needed will be      */
/*     filled into this parameter.                                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid handle.                       */
/*   CWB_INVALID_API_PARAMETER - Invalid index.                     */
/*   CWB_INVALID_POINTER - A NULL pointer was specified.            */
/*   CWB_BUFFER_OVERFLOW - The suffix buffer is not large enough    */
/*                         to hold the entire result.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/

int cwbUN_GetLdapPublishParentDnW
    ( cwbUN_ldapPubHandle  handle,
      int                  index,
      LPWSTR               parentDn,
      int                  *length
    );

int cwbUN_GetLdapPublishParentDnA
    ( cwbUN_ldapPubHandle  handle,
      int                  index,
      LPSTR                parentDn,	
      int                  *length
    );

int cwbUN_GetLdapPublishParentDn8 /* return parentDn in UTF-8 */
    ( cwbUN_ldapPubHandle  handle,
      int                  index,
      LPSTR                parentDn,	
      int                  *length
    );

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbUN_GetLdapPublishParentDn cwbUN_GetLdapPublishParentDnW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbUN_GetLdapPublishParentDn cwbUN_GetLdapPublishParentDnA
#endif // of UNICODE/ANSI selection


CWBAPI unsigned int cwbUN_BS_Attach( cwbCO_SysHandle systemHandle, const char * hostPath);	
CWBAPI unsigned int cwbUN_BS_AttachW( cwbCO_SysHandle systemHandle, const wchar_t * hostPath);	
#if ( defined(CWB_UNICODE) )
   #define cwbUN_BS_Attach       cwbUN_BS_AttachW
#endif

CWBAPI unsigned int cwbUN_BS_Detach( cwbCO_SysHandle systemHandle);

CWBAPI unsigned int cwbUN_BS_CreateFile( 
						cwbCO_SysHandle			systemHandle,
                        const char *		    fileName,	
                        const unsigned int      accessIntent,
                        const unsigned int      shareMode,
                        const unsigned int      disposition,
                        const unsigned int      attributes,
                        const unsigned int      commit,
                        const unsigned int      dataConversion,
                        cwb_BS_FileHandle       *fileHandle,
                        unsigned int            *openResult);

CWBAPI unsigned int cwbUN_BS_CreateFileW( 
						cwbCO_SysHandle			systemHandle,
                        const wchar_t *		    fileName,	
                        const unsigned int      accessIntent,
                        const unsigned int      shareMode,
                        const unsigned int      disposition,
                        const unsigned int      attributes,
                        const unsigned int      commit,
                        const unsigned int      dataConversion,
                        cwb_BS_FileHandle       *fileHandle,
                        unsigned int            *openResult);
#if ( defined(CWB_UNICODE) )
   #define cwbUN_BS_CreateFile       cwbUN_BS_CreateFileW
#endif


CWBAPI unsigned int cwbUN_BS_ReadFile(
						cwb_BS_FileHandle		fileHandle,
                        CONST DWORD				baseOffset,
                        CONST DWORD				offset,
                        CONST DWORD				length,
                        LPVOID					buffer,
                        LPDWORD					bytesRead);

CWBAPI unsigned int cwbUN_BS_WriteFile(
						cwb_BS_FileHandle		fileHandle,
						CONST DWORD				baseOffset,
						CONST DWORD				offset,
						CONST DWORD				length,
						LPVOID					buffer);

CWBAPI unsigned int cwbUN_BS_FindFirstFile(
						cwbCO_SysHandle			systemHandle,
						LPCSTR					fileName,	
						UINT                    *attributes,
						LPFILETIME              createTime,
						LPFILETIME              lastAccessTime,
						LPFILETIME              lastChangeTime,
						PDWORD                  fileSizeHigh,
						PDWORD                  fileSizeLow,
						LPSTR                   objectName,	
						cwb_BS_FindHandle       *findHandle);

CWBAPI unsigned int cwbUN_BS_FindFirstFileW(
						cwbCO_SysHandle			systemHandle,
						LPCWSTR					fileName,	
						UINT                    *attributes,
						LPFILETIME              createTime,
						LPFILETIME              lastAccessTime,
						LPFILETIME              lastChangeTime,
						PDWORD                  fileSizeHigh,
						PDWORD                  fileSizeLow,
						LPWSTR                   objectName,	
						cwb_BS_FindHandle       *findHandle);
#if ( defined(CWB_UNICODE) )
   #define cwbUN_BS_FindFirstFile       cwbUN_BS_FindFirstFileW
#endif

CWBAPI unsigned int cwbUN_BS_FindNextFile(
						cwb_BS_FindHandle       findHandle,
						UINT                    *attributes,
						LPFILETIME              createTime,
						LPFILETIME              lastAccessTime,
						LPFILETIME              lastChangeTime,
						PDWORD                  fileSizeHigh,
						PDWORD                  fileSizeLow,
						LPSTR                   objectName);	

CWBAPI unsigned int cwbUN_BS_FindNextFileW(
						cwb_BS_FindHandle       findHandle,
						UINT                    *attributes,
						LPFILETIME              createTime,
						LPFILETIME              lastAccessTime,
						LPFILETIME              lastChangeTime,
						PDWORD                  fileSizeHigh,
						PDWORD                  fileSizeLow,
						LPWSTR                   objectName);	
#if ( defined(CWB_UNICODE) )
   #define cwbUN_BS_FindNextFile       cwbUN_BS_FindNextFileW
#endif

CWBAPI unsigned int cwbUN_BS_FindClose( cwb_BS_FindHandle findHandle );

CWBAPI unsigned int cwbUN_BS_DeleteFile( cwbCO_SysHandle systemHandle, LPCSTR fileName);	
CWBAPI unsigned int cwbUN_BS_DeleteFileW( cwbCO_SysHandle systemHandle, LPCWSTR fileName);	
#if ( defined(CWB_UNICODE) )
   #define cwbUN_BS_DeleteFile       cwbUN_BS_DeleteFileW
#endif

CWBAPI unsigned int cwbUN_BS_CloseFile( cwb_BS_FileHandle fileHandle);


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_BrowseURL											    */
/*                                                                  */
/* Purpose:                                                         */
/*   Browses an input URL by launching either the windows default   */
/*   browser or by using a browser provided on input.               */
/*                                                                  */
/* Parameters:                                                      */
/*   const char * szSystemName - input                              */
/*     The name of the AS/400 system.  If this is NULL, then the    */
/*     URL specified by szURL is a fully qualified URL              */
/*     (ie. http://www.ibm.com/)                                    */
/*                                                                  */
/*     If this value is not NULL, then the URL specified by szURL   */
/*     is a relative URL that should be appended to the AS/400 name */ 
/*     and port number of the system specified by szSystemName.     */
/*                                                                  */
/*     For example, if the input values are:                        */
/*         szSystemName = 'SystemA'                                 */
/*         szURL = "/dirone/intro.html"                             */
/*                                                                  */
/*     Then the URL launched by cwbUN_BrowseURL will be:            */
/*			Non-SSL, Admin => http://SystemA:2001/dirone/intro.html */
/*          Non-SSL, NonAdm=> http://SystemA:80/dirone/intro.html   */
/*     or,                                                          */
/*          SSL, Admin	   => https://SystemA:2010/dirone/intro.html*/
/*          SSL, Non-Admin => https://SystemA:143/dirone/intro.html */
/*																	*/
/*		Note:  The port numbers ('2001'/'2010'/'80'/'143') listed   */
/*             are the default port numbers, based on whether the   */
/*             admin http server (specified by the bAdminServer) and*/
/*			   SSL is being used.                                   */
/*																	*/ 
/*                                                                  */
/*   char * szURL - input                                           */
/*     Address of the buffer that will contain the null-terminated  */
/*     URL.                                                         */
/*                                                                  */
/*   char * szBrowserPath - input                                   */
/*     Fully qualified path of the web browser to use.  If set to   */
/*     NULL, the default Windows browser will be used (if it does   */
/*     not exist, an error will be displayed).                      */ 
/*                                                                  */
/*	 BOOL   bAdminServer - input         							*/
/*	   Indicates whether the Admin server should be used.  The port */
/*     number used when szSystemName is non-null depends on whether */  
/*     the Admin or normal http server is being used.  If TRUE,     */
/*	   the Admin http server will be used, otherwise, the normal    */
/*     http server is used. This value is ignored is szSystemName   */
/*     is NULL.                                                     */
/*                                                                  */
/*                                                                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_BROWSER_GETPORTNUM_ERR - Failed to obtain port number for*/
/*                         input AS/400.                            */ 
/*   CWBUN_BROWSER_LAUNCH_ERR - Failed to launch the web browser    */
/*                                                                  */
/* Usage Notes:                                                     */
/*    This API requires the Operations Navigator-Network component  */
/*    be installed in order to function properly.                   */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_BrowseURL(
	const char * szSystemName,	
    const char * szURL,	
    const char * szBrowserPath, 	
	const BOOL bAdminServer
    );

CWBAPI unsigned int WINAPI cwbUN_BrowseURLW(
	const wchar_t * szSystemName,	
    const wchar_t * szURL,	
    const wchar_t * szBrowserPath, 	
	const BOOL bAdminServer
    );


#if ( defined(CWB_UNICODE) )
   #define cwbUN_BrowseURL       cwbUN_BrowseURLW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_DisplayAPIError                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   Display an error message dialog box for Client Access/400 API  */
/*   errors.  If the function error has online help with cause      */
/*   recovery information, a details button will be enabled in      */
/*   the error dialog.   This details button can be used to see     */
/*   the online help.   If the function error has no associated     */
/*   online help, the details button will be grayed out.                 */
/*                                                                  */
/*                                                                  */
/* Parameters:                                                      */
/*  LPCTSTR szAPI  - input                                          */
/*    The Client Access/400 API that failed                         */
/*    for example: cwbCO_Connect                                    */
/*                                                                  */  
/*  LPCTSTR szContextMessage - input                                */
/*     This can be message text that is user defined and will be    */
/*     displayed in the message box.  It should be a translated     */
/*     string that will help the user understand the context of the */
/*     error.                                                       */
/*                                                                  */
/*  LPCTSTR szCaptionMessage - input                                */
/*     This is a user defined caption to be used on the message box */
/*     It must be translated text or NULL.  If you specify NULL     */
/*     The caption will be Client Access/400 Operations Navigator   */
/*                                                                  */
/*  UINT returnCode       - input                                   */
/*     This is the return code of API specifed in the szAPI         */
/*     parameter.                                                   */
/*                                                                  */
/*  cwbSV_ErrHandle * errorHandle - input                           */
/*     This is the errorHandle that was returned from the API       */
/*     specified in the szAPI parameter                             */
/*                                                                  */
/*  cwbCO_SysHandle systemHandle -  input                           */
/*     This is the system handle that was used for the connection   */
/*     You can use the API cwbUN_GetSystemHandle to retrieve find   */
/*     this value                                                   */
/*                                                                  */
/*  HWND windowHandle - input                                       */
/*     This is the window handle of the calling program             */
/*     that will be the parent of the error message dialog box      */
/*     If you pass in NULL, the desktop will be the parent          */
/*                                                                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/*   Most of the Client Access/400 APIs will have a  cwbSV_ErrHandle   */
/*   If your API does, you must pass it in to this function         */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_DisplayAPIError(
  				    LPCSTR szAPI,
  			  	    LPCSTR szContextMessage,
					LPCSTR szCaptionMessage,
				    UINT    returnCode,
                    cwbSV_ErrHandle * errorHandle,
				    cwbCO_SysHandle systemHandle,
  		  		    HWND    windowHandle);

CWBAPI unsigned int WINAPI cwbUN_DisplayAPIErrorW(
  				    LPCWSTR szAPI,
  			  	    LPCWSTR szContextMessage,
					LPCWSTR szCaptionMessage,
				    UINT    returnCode,
                    cwbSV_ErrHandle * errorHandle,
				    cwbCO_SysHandle systemHandle,
  		  		    HWND    windowHandle);


#if ( defined(CWB_UNICODE) )
   #define cwbUN_DisplayAPIError       cwbUN_DisplayAPIErrorW
#endif


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetJVM					 	    */
/*								    */
/* Purpose:                                                         */
/*   Starts the Java Virtual Machine and returns info needed by     */
/*   a C++ plugin that is attempting to invoke Java methods.        */
/*                                                                  */
/* Parameters:                                                      */
/*   void **	jvm  - output  			                    */
/*     If successful, *jvm will be a				    */
/*     pointer to the started JVM. NULL if the api failed.	    */
/*     Caller's should cast this value to the 'JavaVM*' type        */
/*     defined in the java header 'jni.h'.                          */
/*                                                                  */
/*   void ** env  - output                                          */
/*     If successful, *env will be a pointer			    */
/*     to the java environment.  NULL if the api failed.	    */
/*     Caller's should cast this value to the 'JNIEnv*' type        */
/*     defined in the java header 'jni.h'.                          */
/*                                                                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*	 CWBUN_GETVM_FAILED - failed to obtain java VM.             */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_GetJVM(
    void ** jvm,
    void ** env); 
 
 
/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_DisplayCommandPrompter                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Display a prompter for a given command string similar to the   */
/*   prompting done by the AS/400 command line.  The command string */
/*   may be a command name, a full command string, or a partial     */
/*   command name such as crt*.  Any errors encountered during      */
/*   prompting will be handled by the API.  The prompter requires   */
/*   the AS/400 to be at release V4R4M0 or above.                   */
/*                                                                  */
/*                                                                  */
/* Parameters:                                                      */
/*  cwbCO_SysHandle systemHandle - input                            */
/*     Handle to a system object.                                   */
/*                                                                  */
/*  UINT promptFlags - input                                        */
/*     An integer value which specifies the prompting options for   */
/*     the prompter.  Multiple values may be OR'd together:         */
/*                                                                  */
/*        CWBUN_PROMPT_INTERACTIVE - Also prompt interactive        */
/*                                 commands.                        */
/*        CWBUN_PROMPT_NO_PROGRAMS - Prompt override and change     */
/*                                 exit programs for the command    */
/*                                 should not be called.            */
/*                                                                  */
/*  LPSTR commandString - input / output                            */
/*     A pointer to a string which contains the command string      */
/*     to prompt.  This string may be a command name, partial       */ 
/*     command string, or a partial commandn ame such as crt*.      */
/*     After the API, this parameter will contain the resulting     */
/*     command string.  This command string returned will be the    */
/*     input command string if the user canceled the dialog or an   */
/*     error occurred.                                              */
/*                                                                  */
/*  UINT * dateFormat - output                                      */
/*     Returns the date format used when prompting the command.     */
/*     Possible values are:                                         */
/*                                                                  */
/*        CWBUN_PROMPT_YEARMONTHDAY - The date format used was      */
/*                                  year, month, and day.           */
/*        CWBUN_PROMPT_MONTHDAYYEAR - The date format used was      */
/*                                  month, day, and year.           */
/*        CWBUN_PROMPT_DAYMONTHYEAR - The date format used was day, */
/*                                  month, and year.                */
/*        CWBUN_PROMPT_JULIAN       - The date format used was      */
/*                                  Julian.                         */
/*        CWBUN_PROMPT_NODATES      - A date format was not used    */
/*                                  due to no date parameters       */
/*                                  specified in the command.       */
/*                                                                  */
/*  BOOL * batchCommand - output                                    */
/*     Returns whether the command which was prompted can be        */
/*     executed in batch.                                           */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*	 CWBUN_GETVM_FAILED - Failed to obtain Java VM.			        */
/*   CWBUN_PROMPT_CANCEL - The user dismissed the dialog by         */
/*                       pressing the cancel button.                */
/*   CWBUN_PROMPT_ERROR - The dialog was dismissed due to an error  */
/*                       while prompting.                           */
/*   CWBUN_MISSING_PTF - The system does not have the required V4R4 */
/*                       or V4R5 PTF to use the prompter.           */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/*   The commandString parameter must always be large enough to     */
/*   hold the resulting command string.  This means the buffer      */
/*   should be at least 32KB.                                       */
/*                                                                  */
/*   An example of the usage would be as follows:                   */
/*                                                                  */
/*      char commandString[32768];                                  */
/*      strcpy(commandString, "crtusrprf");                         */
/*                                                                  */
/*      // Prompt on crtusrprf.  Turn off prompt override call.     */
/*      int rc = cwbUN_DisplayCommandPrompter(systemHandle,         */
/*                                        CWBUN_PROMPT_NO_PROGRAMS, */
/*                                        commandString,            */
/*                                        NULL);                    */
/*                                                                  */
/*      // If success, return the new command string.               */
/*      if(rc == CWB_OK)                                            */
/*         return commandString;                                    */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_DisplayCommandPrompter(
				cwbCO_SysHandle systemHandle,
				UINT promptFlags,
				LPSTR commandString,	
				UINT * dateFormat,
				BOOL * batchCommand);


CWBAPI unsigned int WINAPI cwbUN_DisplayCommandPrompterW(
				cwbCO_SysHandle systemHandle,
				UINT promptFlags,
				LPWSTR commandString,	
				UINT * dateFormat,
				BOOL * batchCommand);

#if ( defined(CWB_UNICODE) )
   #define cwbUN_DisplayCommandPrompter       cwbUN_DisplayCommandPrompterW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_DisplayProperties                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Displays the OpNav property sheet for the specified object.    */
/*                                                                  */
/* Parameters:                                                      */
/*  HWND windowHandle - input                                       */
/*     This is the window handle of the calling program that will   */
/*     be the parent of the property sheet dialog. If you pass in   */
/*     NULL, the desktop will be the parent.                        */
/*                                                                  */  
/*  LPCSTR pszObjectName - input                                    */
/*     Address of the buffer that contains a fully-qualified Unity  */
/*     object name which identifies the object whose properties     */
/*     are to be displayed.                                         */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_PROPERTIES_NOT_DEFINED - Properties action not supported */
/*                                  on the specified object.        */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_DisplayProperties(
                HWND hwndOwner,
                LPCSTR pszObjectName);	

CWBAPI unsigned int WINAPI cwbUN_DisplayPropertiesW(
                HWND hwndOwner,
                LPCWSTR pszObjectName);	

#if ( defined(CWB_UNICODE) )
   #define cwbUN_DisplayProperties      cwbUN_DisplayPropertiesW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_GetPublicListObject                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Get a pointer to the public list object identified by the      */
/*   specified object name.  Public list objects are list objects   */
/*   that are documented for use by other components.               */
/*                                                                  */
/* Parameters:                                                      */
/*   UINT nReserved - input                                         */
/*     Reserved, must be 0.                                         */
/*                                                                  */
/*   const char * szObjectName - input                              */
/*     The Unity object name which identifies the desired           */
/*     public object.                                               */
/*                                                                  */
/*   LPVOID pListObject - output                                    */
/*     Address of the pointer to the requested Unity object.        */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBUN_NULL_PARM - object name or object pointer is NULL        */
/*   CWBUN_INVALID_OBJ_NAME - invalid object name format            */
/*   CWBUN_INVALID_LIST_OBJECT - could not find an object           */
/*            associated with the specified object name             */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_GetPublicListObject(
    UINT nReserved,
    const char * szFileName,	
	LPVOID *pListObject
    );

CWBAPI unsigned int WINAPI cwbUN_GetPublicListObjectW(
    UINT nReserved,
    const wchar_t * szFileName,	
	LPVOID *pListObject
    );


#if ( defined(CWB_UNICODE) )
   #define cwbUN_GetPublicListObject      cwbUN_GetPublicListObjectW
#endif
/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbUN_StartAddConnectionWizard                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   Launches the Add Connection wizard                             */
/*                                                                  */
/* Parameters:                                                      */
/*   none                                                           */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   other - error occurred                                         */
/*                                                                  */
/********************************************************************/
CWBAPI unsigned int WINAPI cwbUN_StartAddConnectionWizard();


#if defined( __cplusplus )
}
#endif

#endif //_CWBUN_H_

