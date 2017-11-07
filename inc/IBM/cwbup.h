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
/*   CWBUP.H                                                        */
/*                                                                  */
/* NOTE: It is essential that cwbUP_FreeLock is called when your    */
/*       application is no longer accessing the update entries.  If */
/*       cwbUP_FreeLock is not called, other applications will not  */
/*       be able to access or modify the update entries.            */
/*                                                                  */
/* Purpose:                                                         */
/*   It contains the declarations for the following API's:          */
/*                                                                  */
/*     APIs for creating an update entry:                           */
/*         cwbUP_CreateUpdateEntry                                  */
/*                                                                  */
/*     APIs for deleting an update entry:                           */
/*         cwbUP_DeleteEntry                                        */
/*                                                                  */
/*     APIs for getting access to an update entry:                  */
/*         cwbUP_FindEntry                                          */
/*         cwbUP_GetEntryHandle                                     */
/*                                                                  */
/*     APIs for freeing resources associated with an entry handle:  */
/*         cwbUP_FreeEntryHandle                                    */
/*                                                                  */
/*     APIs for modifying an update entry:                          */
/*         cwbUP_AddPackageFile                                     */
/*         cwbUP_RemovePackageFile                                  */
/*         cwbUP_SetCallbackDLL                                     */
/*         cwbUP_SetDescription                                     */
/*         cwbUP_SetEntryAttributes                                 */
/*         cwbUP_SetSourcePath                                      */
/*         cwbUP_SetTargetPath                                      */
/*                                                                  */
/*     APIs for getting information from an update entry:           */
/*         cwbUP_GetCallbackDLL                                     */
/*         cwbUP_GetDescription                                     */
/*         cwbUP_GetEntryAttributes                                 */
/*         cwbUP_GetSourcePath                                      */
/*         cwbUP_GetTargetPath                                      */
/*                                                                  */
/*     APIs for retrieving general update function information:     */
/*         cwbUP_GetLockHolderName                                  */
/*                                                                  */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Link with the CWBAPI.LIB import library.                       */
/*   This module is to be used in conjunction with CWBUP.DLL.       */
/*                                                                  */
/********************************************************************/

/* Prevent multiple includes */
#if !defined( _CWBUP_H_ )
  #define     _CWBUP_H_

#if defined( __cplusplus )
extern "C" {
#endif

/* Common Client Access/400 API include */
#include "CWB.H"


typedef cwb_Handle cwbUP_EntryHandle;

#define CWBUP_START   CWB_LAST+1

/*********************************************************/
/* Client Access/400 Update specific error codes         */
/*********************************************************/
#define CWBUP_ENTRY_NOT_FOUND           CWBUP_START
#define CWBUP_SEARCH_POSITION_ERROR     CWBUP_START+1
#define CWBUP_PACKAGE_NOT_FOUND         CWBUP_START+2
#define CWBUP_POSITION_INVALID          CWBUP_START+3
#define CWBUP_TOO_MANY_ENTRIES          CWBUP_START+4
#define CWBUP_TOO_MANY_PACKAGES         CWBUP_START+5
#define CWBUP_STRING_TOO_LONG           CWBUP_START+6
#define CWBUP_ENTRY_IS_LOCKED           CWBUP_START+7
#define CWBUP_UNLOCK_WARNING            CWBUP_START+8


/*********************************************************/
/* Attribute values for cwbUP_SetEntryAttributes API.    */
/*********************************************************/
#define CWBUP_FILE_DRIVEN       0x0001
#define CWBUP_PACKAGE_DRIVEN    0x0004
#define CWBUP_SUBDIRECTORY      0x0008
#define CWBUP_ONEPASS           0x0010
#define CWBUP_BACKLEVEL_OK      0x0100


/*************************************************************************/
/* CWBUP_FILE_DRIVEN:                                                    */
/*   Updates are based on file date comparisons between target and       */
/*   source files.                                                       */
/*                                                                       */
/* CWBUP_PACKAGE_DRIVEN:                                                 */
/*   Updates are based on contents of the package file(s), and           */
/*   comparisons of their file's dates between target and source.        */
/*                                                                       */
/* CWBUP_SUBDIRECTORY:                                                   */
/*   Update compares and updates directories under the given path.       */
/*                                                                       */
/* CWBUP_ONEPASS:                                                        */
/*   Updates occur directory in one pass.  If this isn't specified,      */
/*   updates occur in two passes.  The first pass copies the files to be */
/*   updated to a temporary directory, and then when the PC is rebooted, */
/*   the files are copied to the target directory.                       */
/*                                                                       */
/* CWBUP_BACKLEVELOK:                                                    */
/*   If this is set, updates will occur if the dates of the files on the */
/*   source and target don't match.  If this is not set, updates will    */
/*   only occur if the source file is more recent than the target file   */
/*************************************************************************/


/*********************************************************/
/* Miscellaneous constants                               */
/*********************************************************/
#define CWBUP_SEARCH_FROM_BEGINNING          1
#define CWBUP_MAX_ENTRIES                   99
#define CWBUP_MAX_PACKAGE_FILES             99
#define CWBUP_MAX_LENGTH                   256


/*********************************************************************/
/*                                                                   */
/* API:                                                              */
/*   cwbUP_AddPackageFile                                            */
/*                                                                   */
/* Purpose:                                                          */
/*   Adds a package file to the package file list in the update      */
/*   entry.                                                          */
/*                                                                   */
/* Parameters:                                                       */
/*   cwbUP_EntryHandle  entryHandle - input                          */
/*       Handle that was returned by a previous call to              */
/*       cwbUP_CreateUpdateEntryHandle, cwbUP_GetUpdateEntryHandle,  */
/*       or cwbUP_FindEntry.                                         */
/*                                                                   */
/*   char * entryPackage - input                                     */
/*       Pointer to a null-terminated string that contains the name  */
/*       of a package file to be added to the update entry.  Do not  */
/*       include the path for this file.  The package file must      */
/*       exist in the source and target paths.                       */
/*                                                                   */
/* Return Codes:                                                     */
/*   The following list shows common return values.                  */
/*                                                                   */
/*   CWB_OK - Successful completion.                                 */
/*   CWB_INVALID_HANDLE - Update entry handle is not valid.          */
/*   CWB_INVALID_POINTER - NULL was passed as an address.            */
/*   CWBUP_TOO_MANY_PACKAGES - Maximum number of package files       */
/*                             already exist for this entry.         */
/*   CWBUP_STRING_TOO_LONG - The package file name is longer than    */
/*                            CWBUP_MAX_LENGTH.                      */
/*   CWBUP_ENTRY_IS_LOCKED - Another application is currently        */
/*                           modifying the update entry list.  No    */
/*                           changes are allowed at this time.       */
/*                                                                   */
/* NOTE: It is essential that cwbUP_FreeLock is called when your     */
/*       application is no longer accessing the update entries.  If  */
/*       cwbUP_FreeLock is not called, other applications will not   */
/*       be able to access or modify the update entries.             */
/*                                                                   */
/* Usage Notes:                                                      */
/*                                                                   */
/*********************************************************************/
unsigned int CWB_ENTRY cwbUP_AddPackageFile(
                             cwbUP_EntryHandle entryHandle,
                             char *entryPackage);


/*********************************************************************/
/*                                                                   */
/* API:                                                              */
/*   cwbUP_CreateUpdateEntry                                         */
/*                                                                   */
/* Purpose:                                                          */
/*   Creates a new update entry and passes back a handle to it.      */
/*                                                                   */
/* Parameters:                                                       */
/*   char * entryDescription - input                                 */
/*       Points to a null-terminated string that contains a          */
/*       description to identify the update entry.                   */
/*                                                                   */
/*   char * entrySource - input                                      */
/*       Points to a null-terminated string that contains the        */
/*       source for the update entry.  This can be a drive and path  */
/*       or a UNC name.                                              */
/*                                                                   */
/*   char * entryTarget - input                                      */
/*       Points to a null-terminated strings that contains the       */
/*       target for the update entry.  This can be a drive and path  */
/*       or a UNC name.                                              */
/*                                                                   */
/*   cwbUP_EntryHandle * entryHandle - input/output                  */
/*       Pointer to a cwbUP_EntryHandle where the handle will be     */
/*       returned.  This handle must be used in subsequent calls     */
/*       to the update entry APIs.                                   */
/*                                                                   */
/* Return Codes:                                                     */
/*   The following list shows common return values.                  */
/*                                                                   */
/*   CWB_OK - Successful completion.                                 */
/*   CWB_INVALID_POINTER - NULL passed as an address                 */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory to create handle.   */
/*   CWBUP_TOO_MANY_ENTRIES - The maximum number of update entries   */
/*                            already exist.  No more can be created.*/
/*   CWBUP_STRING_TOO_LONG - An input string is longer than the      */
/*                           maximum of CWBUP_MAX_LENGTH.            */
/*   CWBUP_ENTRY_IS_LOCKED - Another application is currently        */
/*                           modifying the update entry list.  No    */
/*                           changes are allowed at this time.       */
/*                                                                   */
/* NOTE: It is essential that cwbUP_FreeLock is called when your     */
/*       application is no longer accessing the update entries.  If  */
/*       cwbUP_FreeLock is not called, other applications will not   */
/*       be able to access or modify the update entries.             */
/*                                                                   */
/* Usage Notes:                                                      */
/*                                                                   */
/*   When you use this call, and have completed your processing of   */
/*   the update entry, you must call cwbUP_FreeEntryHandle.          */
/*   This call will "unlock" the entry, and free resources           */
/*   associated with it.                                             */
/*                                                                   */
/*********************************************************************/
unsigned int CWB_ENTRY cwbUP_CreateUpdateEntry(
                             char * entryDescription,
                             char * entrySource,
                             char * entryTarget,
                             cwbUP_EntryHandle *entryHandle);


/*********************************************************************/
/*                                                                   */
/* API:                                                              */
/*   cwbUP_DeleteEntry                                               */
/*                                                                   */
/* Purpose:                                                          */
/*   Deletes the update entry from the update entry list.            */
/*                                                                   */
/* Parameters:                                                       */
/*   cwbUP_EntryHandle  entryHandle - input                          */
/*       Handle that was returned by a previous call to              */
/*       cwbUP_CreateUpdateEntryHandle, cwbUP_GetUpdateEntryHandle   */
/*       or cwbUP_FindEntry.                                         */
/*                                                                   */
/* Return Codes:                                                     */
/*   The following list shows common return values.                  */
/*                                                                   */
/*   CWB_OK - Successful completion.                                 */
/*   CWB_INVALID_HANDLE - Update entry handle is not valid.          */
/*   CWBUP_ENTRY_IS_LOCKED - Another application is currently        */
/*                           modifying the update entry list.  No    */
/*                           changes are allowed at this time.       */
/*                                                                   */
/* NOTE: It is essential that cwbUP_FreeLock is called when your     */
/*       application is no longer accessing the update entries.  If  */
/*       cwbUP_FreeLock is not called, other applications will not   */
/*       be able to access or modify the update entries.             */
/*                                                                   */
/* Usage Notes:                                                      */
/*                                                                   */
/*   After this call, you do not need to call cwbUP_FreeEntryHandle. */
/*   The entry is "freed" when the entry is successfully deleted.    */
/*                                                                   */
/*   If you retrieved the first update entry using the cwbUP_        */
/*   GetEntryHandle API, and then called this API to delete the      */
/*   entry, all of the update entries would then slide one position  */
/*   to fill the slot left by the delete.  So, if you then wanted to */
/*   get the next update item, you would pass the same index that    */
/*   you did on the previous cwbUP_GetEntryHandle API call.          */
/*                                                                   */
/*********************************************************************/
unsigned int CWB_ENTRY cwbUP_DeleteEntry(
                             cwbUP_EntryHandle entryHandle);


/*********************************************************************/
/*                                                                   */
/* API:                                                              */
/*   cwbUP_FindEntry                                                 */
/*                                                                   */
/* Purpose:                                                          */
/*   Gets a handle to an existing update entry using entrySource     */
/*   and entryTarget as the search parameters.                       */
/*                                                                   */
/* Parameters:                                                       */
/*   char * entrySource - input                                      */
/*       Points to a null-terminated string that contains the        */
/*       source for the update entry.  This can be a drive and path  */
/*       or a UNC name.  This string will be used to search for a    */
/*       matching update entry.                                      */
/*                                                                   */
/*   char * entryTarget - input                                      */
/*       Points to a null-terminated string that contains the        */
/*       target for the update entry.  This can be a drive and path  */
/*       or a UNC name.  This string will be used to search for a    */
/*       matching update entry.                                      */
/*                                                                   */
/*   unsigned long * searchStart - input/output                      */
/*       Pointer to an index into the list of update entries to      */
/*       begin the search at.  This would be used in cases where     */
/*       multiple update entries may have matching source and        */
/*       targets.  You would use this parameter to "skip" over       */
/*       entries in the search, and continue on searching for a      */
/*       matching update entry that is after searchStart in the      */
/*       list.                                                       */
/*                                                                   */
/*       On successful return, searchStart will be set to the        */
/*       position in the list where the update entry was found.      */
/*                                                                   */
/*       This should be set to CWBUP_SEARCH_FROM_BEGINNING if        */
/*       you want to search all update entries.                      */
/*                                                                   */
/*   cwbUP_EntryHandle * entryHandle - input/output                  */
/*       Pointer to a cwbUP_EntryHandle where the handle will be     */
/*       returned.  This handle must be used in subsequent calls     */
/*       to the update entry APIs.                                   */
/*                                                                   */
/* Return Codes:                                                     */
/*   The following list shows common return values.                  */
/*                                                                   */
/*   CWB_OK - Successful completion.                                 */
/*   CWB_INVALID_POINTER - NULL passed as an address                 */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory to create handle.   */
/*   CWBUP_SEARCH_POSITION_ERROR - Search starting position is not   */
/*                                 valid.                            */
/*   CWBUP_ENTRY_NOT_FOUND - No update entry matched search          */
/*                           criteria.                               */
/*   CWBUP_STRING_TOO_LONG - An input string is longer than the      */
/*                           maximum of CWBUP_MAX_LENGTH.            */
/*                                                                   */
/* NOTE: It is essential that cwbUP_FreeLock is called when your     */
/*       application is no longer accessing the update entries.  If  */
/*       cwbUP_FreeLock is not called, other applications will not   */
/*       be able to access or modify the update entries.             */
/*                                                                   */
/* Usage Notes:                                                      */
/*   The handle returned from this call will be used for accessing   */
/*   the update entry with other Update APIs.                        */
/*                                                                   */
/*   When you use this call, and have completed your processing of   */
/*   the update entry, you must call cwbUP_FreeEntryHandle.          */
/*   This call will "unlock" the entry, and free resources           */
/*   associated with it.                                             */
/*                                                                   */
/*********************************************************************/
unsigned int CWB_ENTRY cwbUP_FindEntry(
                             char * entrySource,
                             char * entryTarget,
                             unsigned long *searchStart,
                             cwbUP_EntryHandle *entryHandle);

/*********************************************************************/
/*                                                                   */
/* API:                                                              */
/*   cwbUP_FreeEntryHandle                                           */
/*                                                                   */
/* Purpose:                                                          */
/*   Frees an entry handle and all resources associated with it.     */
/*                                                                   */
/* Parameters:                                                       */
/*   cwbUP_EntryHandle entryHandle - input                           */
/*       The entry handle that is to be freed.                       */
/*                                                                   */
/* Return Codes:                                                     */
/*   The following list shows common return values.                  */
/*                                                                   */
/*   CWB_OK - Successful completion.                                 */
/*   CWB_INVALID_HANDLE - Handle is not valid or has already been    */
/*                        freed.                                     */
/*                                                                   */
/* NOTE: It is essential that cwbUP_FreeLock is called when your     */
/*       application is no longer accessing the update entries.  If  */
/*       cwbUP_FreeLock is not called, other applications will not   */
/*       be able to access or modify the update entries.             */
/*                                                                   */
/* Usage Notes:                                                      */
/*                                                                   */
/*   After this call you can no longer access the update entry.  To  */
/*   access the update entry or another update entry, you would need */
/*   to get a new entry handle.                                      */
/*                                                                   */
/*********************************************************************/
unsigned int CWB_ENTRY cwbUP_FreeEntryHandle(
                             cwbUP_EntryHandle entryHandle);

/*********************************************************************/
/*                                                                   */
/* API:                                                              */
/*   cwbUP_FreeLock                                                  */
/*                                                                   */
/* Purpose:                                                          */
/*   Frees the lock to the update entries.  This should be called    */
/*   when the application is done accessing the update entries.  If  */
/*   this is not called, other applications will not be able to      */
/*   access the update entries.                                      */
/*                                                                   */
/* Parameters:                                                       */
/*   None.                                                           */
/*                                                                   */
/* Return Codes:                                                     */
/*   CWB_OK - Successful completion.                                 */
/*   CWBUP_UNLOCK_WARNING - Application did not have the update      */
/*                          entries locked.                          */
/*                                                                   */
/* Usage Notes:                                                      */
/*   A lock to the update entries is obtained whenever an            */
/*   application accesses or modifies and update entry.  When the    */
/*   application no longer needs to access the update entries,       */
/*   the application should call this API.                           */
/*                                                                   */
/*********************************************************************/
unsigned int CWB_ENTRY cwbUP_FreeLock();


/*********************************************************************/
/*                                                                   */
/* API:                                                              */
/*   cwbUP_GetCallbackDLL                                            */
/*                                                                   */
/* Purpose:                                                          */
/*   Gets the fully qualified name of the callback DLL for an        */
/*   update entry.                                                   */
/*                                                                   */
/* Parameters:                                                       */
/*   cwbUP_EntryHandle  entryHandle - input                          */
/*       Handle that was returned by a previous call to              */
/*       cwbUP_CreateUpdateEntryHandle, cwbUP_GetUpdateEntryHandle,  */
/*       or cwbUP_FindEntry.                                         */
/*                                                                   */
/*   char * dllPath - input/output                                   */
/*       Pointer to a buffer that will receive the fully qualified   */
/*       name of the DLL that will be called when individual stages  */
/*       of the update occur.                                        */
/*                                                                   */
/*   unsigned long bufferLength - input                              */
/*       Length of the dllPath buffer.  Space should be included     */
/*       for the null termination character.  If the buffer is not   */
/*       large enough to hold the entire DLL name, an error will be  */
/*       returned and the actualLength parameter will be set to the  */
/*       number of bytes the dllPath buffer needs to be.             */
/*                                                                   */
/*   unsigned long * actualLength - input/output                     */
/*       Pointer to a length variable that will be set to the size   */
/*       of the buffer needed to contain the fully qualified DLL     */
/*       name.                                                       */
/*                                                                   */
/* Return Codes:                                                     */
/*   The following list shows common return values.                  */
/*                                                                   */
/*   CWB_OK - Successful completion.                                 */
/*   CWB_INVALID_HANDLE - Update entry handle is not valid.          */
/*   CWB_INVALID_POINTER - NULL passed as an address parameter.      */
/*   CWB_BUFFER_OVERFLOW - Buffer is too small to hold return data.  */
/*                                                                   */
/* Usage Notes:                                                      */
/*                                                                   */
/*********************************************************************/
unsigned int CWB_ENTRY  cwbUP_GetCallbackDLL(
                              cwbUP_EntryHandle entryHandle,
                              char *dllPath,
                              unsigned long bufferLength,
                              unsigned long *actualLength);


/*********************************************************************/
/*                                                                   */
/* API:                                                              */
/*   cwbUP_GetDescription                                            */
/*                                                                   */
/* Purpose:                                                          */
/*   Gets the description of the update entry.                       */
/*                                                                   */
/* Parameters:                                                       */
/*   cwbUP_EntryHandle  entryHandle - input                          */
/*       Handle that was returned by a previous call to              */
/*       cwbUP_CreateUpdateEntryHandle, cwbUP_GetUpdateEntryHandle,  */
/*       or cwbUP_FindEntry.                                         */
/*                                                                   */
/*   char * entryDescription - input/output                          */
/*       Pointer to a buffer that will receive the description of    */
/*       the update entry.                                           */
/*                                                                   */
/*   unsigned long bufferLength - input                              */
/*       Length of the buffer.  An extra byte should be included     */
/*       for the null termination character.  If the buffer is not   */
/*       large enough to hold the entire description, an error will  */
/*       be returned and the actualLength parameter will be set to   */
/*       the number of bytes the entryDescription buffer needs to    */
/*       be to contain the data.                                     */
/*                                                                   */
/*   unsigned long * actualLength - input/output                     */
/*       Pointer to a length variable that will be set to the size   */
/*       of the buffer needed to contain the description.            */
/*                                                                   */
/* Return Codes:                                                     */
/*   The following list shows common return values.                  */
/*                                                                   */
/*   CWB_OK - Successful completion.                                 */
/*   CWB_INVALID_HANDLE - Update entry handle is not valid.          */
/*   CWB_INVALID_POINTER - NULL passed as an address parameter.      */
/*   CWB_BUFFER_OVERFLOW - Buffer is too small to hold return data.  */
/*                                                                   */
/* NOTE: It is essential that cwbUP_FreeLock is called when your     */
/*       application is no longer accessing the update entries.  If  */
/*       cwbUP_FreeLock is not called, other applications will not   */
/*       be able to access or modify the update entries.             */
/*                                                                   */
/* Usage Notes:                                                      */
/*                                                                   */
/*********************************************************************/
unsigned int CWB_ENTRY cwbUP_GetDescription(
                             cwbUP_EntryHandle entryHandle,
                             char *entryDescription,
                             unsigned long bufferLength,
                             unsigned long *actualLength);


/*********************************************************************/
/*                                                                   */
/* API:                                                              */
/*   cwbUP_GetEntryAttributes                                        */
/*                                                                   */
/* Purpose:                                                          */
/*   Gets the attributes of the update entry.  These include:        */
/*   one pass update, file driven update, package driven update, and */
/*   update subdirectories.  Any combination of these is valid.      */
/*                                                                   */
/* Parameters:                                                       */
/*   cwbUP_EntryHandle  entryHandle - input                          */
/*       Handle that was returned by a previous call to              */
/*       cwbUP_CreateUpdateEntryHandle, cwbUP_GetUpdateEntryHandle,  */
/*       or cwbUP_FindEntry.                                         */
/*                                                                   */
/*   unsigned long * entryAttributes - input/output                  */
/*       Pointer to area to receive the attribute values.            */
/*       (See defines section for values)                            */
/*                                                                   */
/* Return Codes:                                                     */
/*   The following list shows common return values.                  */
/*                                                                   */
/*   CWB_OK - Successful completion.                                 */
/*   CWB_INVALID_HANDLE - Update entry handle is not valid.          */
/*   CWB_INVALID_POINTER - NULL passed as an address parameter.      */
/*                                                                   */
/* NOTE: It is essential that cwbUP_FreeLock is called when your     */
/*       application is no longer accessing the update entries.  If  */
/*       cwbUP_FreeLock is not called, other applications will not   */
/*       be able to access or modify the update entries.             */
/*                                                                   */
/* Usage Notes:                                                      */
/*   The value contained in entryAttributes after this call is made  */
/*   may be a combination of the attribute flags listed near the top */
/*   of this file.                                                   */
/*********************************************************************/
unsigned int CWB_ENTRY cwbUP_GetEntryAttributes(
                             cwbUP_EntryHandle entryHandle,
                             unsigned long *entryAttributes);


/*********************************************************************/
/*                                                                   */
/* API:                                                              */
/*   cwbUP_GetEntryHandle                                            */
/*                                                                   */
/* Purpose:                                                          */
/*   Gets a handle to an existing update entry at a given position   */
/*   in the list.                                                    */
/*                                                                   */
/* Parameters:                                                       */
/*   unsigned long entryPosition - input                             */
/*       Index into the update entry list of the entry you want to   */
/*       retrieve a handle for.  (Pass in 1 if you wish to retrieve  */
/*       the first update entry)                                     */
/*                                                                   */
/*   cwbUP_EntryHandle * entryHandle - input/output                  */
/*       Pointer to a cwbUP_EntryHandle where the handle will be     */
/*       returned.  This handle must be used in subsequent calls     */
/*       to the update entry APIs.                                   */
/*                                                                   */
/* Return Codes:                                                     */
/*   The following list shows common return values.                  */
/*                                                                   */
/*   CWB_OK - Successful completion.                                 */
/*   CWB_INVALID_POINTER - NULL was passed as an address.            */
/*   CWBUP_ENTRY_NOT_FOUND - No update entry at the given position.  */
/*   CWBUP_POSITION_INVALID - Position given is not in range.        */
/*                                                                   */
/* NOTE: It is essential that cwbUP_FreeLock is called when your     */
/*       application is no longer accessing the update entries.  If  */
/*       cwbUP_FreeLock is not called, other applications will not   */
/*       be able to access or modify the update entries.             */
/*                                                                   */
/* Usage Notes:                                                      */
/*   The handle returned from this call will be used for accessing   */
/*   the update entry with other Update APIs.                        */
/*                                                                   */
/*   When you use this call, and have completed your processing of   */
/*   the update entry, you must call cwbUP_FreeEntryHandle.          */
/*   This call will "unlock" the entry, and free resources           */
/*   associated with it.  You must call cwbUP_FreeEntryHandle        */
/*   once for each time that you call an API that returns an entry   */
/*   handle.                                                         */
/*                                                                   */
/*********************************************************************/
unsigned int CWB_ENTRY cwbUP_GetEntryHandle(
                             unsigned long entryPosition,
                             cwbUP_EntryHandle *entryHandle);


/*********************************************************************/
/*                                                                   */
/* API:                                                              */
/*   cwbUP_GetLockHolderName                                         */
/*                                                                   */
/* Purpose:                                                          */
/*   Gets the name of the program that currently has the update      */
/*   entries in a locked state.                                      */
/*                                                                   */
/* Parameters:                                                       */
/*   char * lockHolder - input/output                                */
/*       Pointer to a buffer that will receive the name of the       */
/*       application that is currently locking the update entries.   */
/*                                                                   */
/*   unsigned long bufferLength - input                              */
/*       Length of the buffer.  An extra byte should be included     */
/*       for the null termination character.  If the buffer is not   */
/*       large enough to hold the entire name, an error will         */
/*       be returned and the actualLength parameter will be set to   */
/*       the number of bytes the lockHolder buffer needs to be to    */
/*       contain the data.                                           */
/*                                                                   */
/*   unsigned long * actualLength - input/output                     */
/*       Pointer to a length variable that will be set to the size   */
/*       of the buffer needed to contain the application name.       */
/*                                                                   */
/* Return Codes:                                                     */
/*   The following list shows common return values.                  */
/*                                                                   */
/*   CWB_OK - Successful completion.                                 */
/*   CWB_INVALID_POINTER - NULL passed as an address parameter.      */
/*   CWB_BUFFER_OVERFLOW - Buffer is too small to hold return data.  */
/*                                                                   */
/* NOTE: It is essential that cwbUP_FreeLock is called when your     */
/*       application is no longer accessing the update entries.  If  */
/*       cwbUP_FreeLock is not called, other applications will not   */
/*       be able to access or modify the update entries.             */
/*                                                                   */
/* Usage Notes:                                                      */
/*                                                                   */
/*********************************************************************/
unsigned int CWB_ENTRY cwbUP_GetLockHolderName(char *lockHolder,
                                               unsigned long bufferLength,
                                               unsigned long *actualLength);


/*********************************************************************/
/*                                                                   */
/* API:                                                              */
/*   cwbUP_GetSourcePath                                             */
/*                                                                   */
/* Purpose:                                                          */
/*   Gets the source path of the update entry.                       */
/*                                                                   */
/* Parameters:                                                       */
/*   cwbUP_EntryHandle  entryHandle - input                          */
/*       Handle that was returned by a previous call to              */
/*       cwbUP_CreateUpdateEntryHandle, cwbUP_GetUpdateEntryHandle,  */
/*       or cwbUP_FindEntry.                                         */
/*                                                                   */
/*   char * entrySource - input/output                               */
/*       Pointer to a buffer that will receive the source path of    */
/*       the update entry.                                           */
/*                                                                   */
/*   unsigned long bufferLength - input                              */
/*       Length of the buffer.  An extra byte should be included     */
/*       for the null termination character.  If the buffer is not   */
/*       large enough to hold the entire source path, an error will  */
/*       be returned and the actualLength parameter will be set to   */
/*       the number of bytes the entrySource buffer needs to be to   */
/*       contain the data.                                           */
/*                                                                   */
/*   unsigned long * actualLength - input/output                     */
/*       Pointer to a length variable that will be set to the size   */
/*       of the buffer needed to contain the source path.            */
/*                                                                   */
/* Return Codes:                                                     */
/*   The following list shows common return values.                  */
/*                                                                   */
/*   CWB_OK - Successful completion.                                 */
/*   CWB_INVALID_HANDLE - Update entry handle is not valid.          */
/*   CWB_INVALID_POINTER - NULL passed as an address parameter.      */
/*   CWB_BUFFER_OVERFLOW - Buffer is too small to hold return data.  */
/*                                                                   */
/* NOTE: It is essential that cwbUP_FreeLock is called when your     */
/*       application is no longer accessing the update entries.  If  */
/*       cwbUP_FreeLock is not called, other applications will not   */
/*       be able to access or modify the update entries.             */
/*                                                                   */
/* Usage Notes:                                                      */
/*                                                                   */
/*********************************************************************/
unsigned int CWB_ENTRY cwbUP_GetSourcePath(
                             cwbUP_EntryHandle entryHandle,
                             char *entrySource,
                             unsigned long bufferLength,
                             unsigned long *actualLength);


/*********************************************************************/
/*                                                                   */
/* API:                                                              */
/*   cwbUP_GetTargetPath                                             */
/*                                                                   */
/* Purpose:                                                          */
/*   Gets the target path of the update entry.                       */
/*                                                                   */
/* Parameters:                                                       */
/*   cwbUP_EntryHandle  entryHandle - input                          */
/*       Handle that was returned by a previous call to              */
/*       cwbUP_CreateUpdateEntryHandle, cwbUP_GetUpdateEntryHandle,  */
/*       or cwbUP_FindEntry.                                         */
/*                                                                   */
/*   char * entryTarget - input/output                               */
/*       Pointer to a buffer that will receive the target path of    */
/*       the update entry.                                           */
/*                                                                   */
/*   unsigned long bufferLength - input                              */
/*       Length of the buffer.  An extra byte should be included     */
/*       for the null termination character.  If the buffer is not   */
/*       large enough to hold the entire target path, an error will  */
/*       be returned and the actualLength parameter will be set to   */
/*       the number of bytes the entryTarget buffer needs to be to   */
/*       contain the data.                                           */
/*                                                                   */
/*   unsigned long * actualLength - input/output                     */
/*       Pointer to a length variable that will be set to the size   */
/*       of the buffer needed to contain the target path.            */
/*                                                                   */
/* Return Codes:                                                     */
/*   The following list shows common return values.                  */
/*                                                                   */
/*   CWB_OK - Successful completion.                                 */
/*   CWB_INVALID_HANDLE - Update entry handle is not valid.          */
/*   CWB_INVALID_POINTER - NULL passed as an address parameter.      */
/*   CWB_BUFFER_OVERFLOW - Buffer is too small to hold return data.  */
/*                                                                   */
/* NOTE: It is essential that cwbUP_FreeLock is called when your     */
/*       application is no longer accessing the update entries.  If  */
/*       cwbUP_FreeLock is not called, other applications will not   */
/*       be able to access or modify the update entries.             */
/*                                                                   */
/* Usage Notes:                                                      */
/*                                                                   */
/*********************************************************************/
unsigned int CWB_ENTRY cwbUP_GetTargetPath(
                             cwbUP_EntryHandle entryHandle,
                             char *entryTarget,
                             unsigned long bufferLength,
                             unsigned long *actualLength);



/*********************************************************************/
/*                                                                   */
/* API:                                                              */
/*   cwbUP_RemovePackageFile                                         */
/*                                                                   */
/* Purpose:                                                          */
/*   Removes a package file from the list of package files belonging */
/*   to an update entry.                                             */
/*                                                                   */
/* Parameters:                                                       */
/*   cwbUP_EntryHandle  entryHandle - input                          */
/*       Handle that was returned by a previous call to              */
/*       cwbUP_CreateUpdateEntryHandle, cwbUP_GetUpdateEntryHandle,  */
/*       or cwbUP_FindEntry.                                         */
/*                                                                   */
/*   char * entryPackage - input                                     */
/*       Pointer to a null-terminated string containing the package  */
/*       file name to be removed from the package file list.         */
/*                                                                   */
/* Return Codes:                                                     */
/*   The following list shows common return values.                  */
/*                                                                   */
/*   CWB_OK - Successful completion.                                 */
/*   CWB_INVALID_HANDLE - Update entry handle is not valid.          */
/*   CWB_INVALID_POINTER - NULL passed as an address parameter.      */
/*   CWBUP_PACKAGE_NOT_FOUND - The package file was not found.       */
/*   CWBUP_STRING_TOO_LONG - The package file string is longer than  */
/*                           the maximum of CWBUP_MAX_LENGTH.        */
/*   CWBUP_ENTRY_IS_LOCKED - Another application is currently        */
/*                           modifying the update entry list.  No    */
/*                           changes are allowed at this time.       */
/*                                                                   */
/* NOTE: It is essential that cwbUP_FreeLock is called when your     */
/*       application is no longer accessing the update entries.  If  */
/*       cwbUP_FreeLock is not called, other applications will not   */
/*       be able to access or modify the update entries.             */
/*                                                                   */
/* Usage Notes:                                                      */
/*                                                                   */
/*********************************************************************/
unsigned int CWB_ENTRY cwbUP_RemovePackageFile(
                             cwbUP_EntryHandle entryHandle,
                             char *entryPackage);


/*********************************************************************/
/*                                                                   */
/* API:                                                              */
/*   cwbUP_SetCallbackDLL                                            */
/*                                                                   */
/* Purpose:                                                          */
/*   Sets the fully qualified name of the callback DLL for an        */
/*   update entry.                                                   */
/*                                                                   */
/* Parameters:                                                       */
/*   cwbUP_EntryHandle  entryHandle - input                          */
/*       Handle that was returned by a previous call to              */
/*       cwbUP_CreateUpdateEntryHandle, cwbUP_GetUpdateEntryHandle,  */
/*       or cwbUP_FindEntry.                                         */
/*                                                                   */
/*   char * dllPath - input                                          */
/*       Pointer to a null-terminated string containing the fully    */
/*       qualified name of the DLL that will be called when          */
/*       individual stages of the update occur.                      */
/*                                                                   */
/* Return Codes:                                                     */
/*   The following list shows common return values.                  */
/*                                                                   */
/*   CWB_OK - Successful completion.                                 */
/*   CWB_INVALID_HANDLE - Update entry handle is not valid.          */
/*   CWB_INVALID_POINTER - NULL passed as an address parameter.      */
/*   CWBUP_STRING_TOO_LONG - The callback DLL string is longer than  */
/*                           the maximum of CWBUP_MAX_LENGTH.        */
/*   CWBUP_ENTRY_IS_LOCKED - Another application is currently        */
/*                           modifying the update entry list.  No    */
/*                           changes are allowed at this time.       */
/*                                                                   */
/* NOTE: It is essential that cwbUP_FreeLock is called when your     */
/*       application is no longer accessing the update entries.  If  */
/*       cwbUP_FreeLock is not called, other applications will not   */
/*       be able to access or modify the update entries.             */
/*                                                                   */
/* Usage Notes:                                                      */
/*                                                                   */
/*********************************************************************/
unsigned int CWB_ENTRY  cwbUP_SetCallbackDLL(
                              cwbUP_EntryHandle entryHandle,
                              char *dllPath);


/*********************************************************************/
/*                                                                   */
/* API:                                                              */
/*   cwbUP_SetDescription                                            */
/*                                                                   */
/* Purpose:                                                          */
/*   Sets the description of the update entry.                       */
/*                                                                   */
/* Parameters:                                                       */
/*   cwbUP_EntryHandle  entryHandle - input                          */
/*       Handle that was returned by a previous call to              */
/*       cwbUP_CreateUpdateEntryHandle, cwbUP_GetUpdateEntryHandle,  */
/*       or cwbUP_FindEntry.                                         */
/*                                                                   */
/*   char * entryDescription - input                                 */
/*       Pointer to a null-terminated string containing the full     */
/*       description to be associated with the update entry.         */
/*                                                                   */
/* Return Codes:                                                     */
/*   The following list shows common return values.                  */
/*                                                                   */
/*   CWB_OK - Successful completion.                                 */
/*   CWB_INVALID_HANDLE - Update entry handle is not valid.          */
/*   CWB_INVALID_POINTER - NULL passed as an address parameter.      */
/*   CWBUP_STRING_TOO_LONG - The description string is longer than   */
/*                           the maximum of CWBUP_MAX_LENGTH.        */
/*   CWBUP_ENTRY_IS_LOCKED - Another application is currently        */
/*                           modifying the update entry list.  No    */
/*                           changes are allowed at this time.       */
/*                                                                   */
/* NOTE: It is essential that cwbUP_FreeLock is called when your     */
/*       application is no longer accessing the update entries.  If  */
/*       cwbUP_FreeLock is not called, other applications will not   */
/*       be able to access or modify the update entries.             */
/*                                                                   */
/* Usage Notes:                                                      */
/*                                                                   */
/*********************************************************************/
unsigned int CWB_ENTRY cwbUP_SetDescription(
                             cwbUP_EntryHandle entryHandle,
                             char *entryDescription);


/*********************************************************************/
/*                                                                   */
/* API:                                                              */
/*   cwbUP_SetEntryAttributes                                        */
/*                                                                   */
/* Purpose:                                                          */
/*   Sets the attributes of the update entry.  These include:        */
/*   one pass update, file driven update, package driven update, and */
/*   update subdirectories.  Any combination of these is valid.      */
/*                                                                   */
/* Parameters:                                                       */
/*   cwbUP_EntryHandle  entryHandle - input                          */
/*       Handle that was returned by a previous call to              */
/*       cwbUP_CreateUpdateEntryHandle, cwbUP_GetUpdateEntryHandle,  */
/*       or cwbUP_FindEntry.                                         */
/*                                                                   */
/*   unsigned long entryAttributes - input                           */
/*       Combination of the attribute values.                        */
/*       (See defines section for values)                            */
/*                                                                   */
/* Return Codes:                                                     */
/*   The following list shows common return values.                  */
/*                                                                   */
/*   CWB_OK - Successful completion.                                 */
/*   CWB_INVALID_HANDLE - Update entry handle is not valid.          */
/*   CWBUP_ENTRY_IS_LOCKED - Another application is currently        */
/*                           modifying the update entry list.  No    */
/*                           changes are allowed at this time.       */
/*                                                                   */
/* NOTE: It is essential that cwbUP_FreeLock is called when your     */
/*       application is no longer accessing the update entries.  If  */
/*       cwbUP_FreeLock is not called, other applications will not   */
/*       be able to access or modify the update entries.             */
/*                                                                   */
/* Usage Notes:                                                      */
/*   An example of this call follows:                                */
/*      rc = cwbUP_SetEntryAttributes(entryHandle,                   */
/*                                    CWBUP_FILEDRIVEN |             */
/*                                       CWBUP_ONEPASS  );           */
/*                                                                   */
/*   This call would result in the update entry being file driven    */
/*   and the update would occur in one pass.                         */
/*                                                                   */
/*********************************************************************/
unsigned int CWB_ENTRY cwbUP_SetEntryAttributes(
                             cwbUP_EntryHandle entryHandle,
                             unsigned long entryAttributes);


/*********************************************************************/
/*                                                                   */
/* API:                                                              */
/*   cwbUP_SetSourcePath                                             */
/*                                                                   */
/* Purpose:                                                          */
/*   Sets the source path of the update entry.                       */
/*                                                                   */
/* Parameters:                                                       */
/*   cwbUP_EntryHandle  entryHandle - input                          */
/*       Handle that was returned by a previous call to              */
/*       cwbUP_CreateUpdateEntryHandle, cwbUP_GetUpdateEntryHandle,  */
/*       or cwbUP_FindEntry.                                         */
/*                                                                   */
/*   char * entrySource - input                                      */
/*       Pointer to a null-terminated string containing the full     */
/*       source path for the update entry.                           */
/*                                                                   */
/* Return Codes:                                                     */
/*   The following list shows common return values.                  */
/*                                                                   */
/*   CWB_OK - Successful completion.                                 */
/*   CWB_INVALID_HANDLE - Update entry handle is not valid.          */
/*   CWB_INVALID_POINTER - NULL passed as an address parameter.      */
/*   CWBUP_STRING_TOO_LONG - The source path string is longer than   */
/*                           the maximum of CWBUP_MAX_LENGTH.        */
/*   CWBUP_ENTRY_IS_LOCKED - Another application is currently        */
/*                           modifying the update entry list.  No    */
/*                           changes are allowed at this time.       */
/*                                                                   */
/* NOTE: It is essential that cwbUP_FreeLock is called when your     */
/*       application is no longer accessing the update entries.  If  */
/*       cwbUP_FreeLock is not called, other applications will not   */
/*       be able to access or modify the update entries.             */
/*                                                                   */
/* Usage Notes:                                                      */
/*                                                                   */
/*********************************************************************/
unsigned int CWB_ENTRY cwbUP_SetSourcePath(
                             cwbUP_EntryHandle entryHandle,
                             char *entrySource);


/*********************************************************************/
/*                                                                   */
/* API:                                                              */
/*   cwbUP_SetTargetPath                                             */
/*                                                                   */
/* Purpose:                                                          */
/*   Sets the target path of the update entry.                       */
/*                                                                   */
/* Parameters:                                                       */
/*   cwbUP_EntryHandle  entryHandle - input                          */
/*       Handle that was returned by a previous call to              */
/*       cwbUP_CreateUpdateEntryHandle, cwbUP_GetUpdateEntryHandle,  */
/*       or cwbUP_FindEntry.                                         */
/*                                                                   */
/*   char * entryTarget - input                                      */
/*       Pointer to a null-terminated string containing the full     */
/*       target path for the update entry.                           */
/*                                                                   */
/* Return Codes:                                                     */
/*   The following list shows common return values.                  */
/*                                                                   */
/*   CWB_OK - Successful completion.                                 */
/*   CWB_INVALID_HANDLE - Update entry handle is not valid.          */
/*   CWB_INVALID_POINTER - NULL passed as an address parameter.      */
/*   CWBUP_STRING_TOO_LONG - The target path string is longer than   */
/*                           the maximum of CWBUP_MAX_LENGTH.        */
/*   CWBUP_ENTRY_IS_LOCKED - Another application is currently        */
/*                           modifying the update entry list.  No    */
/*                           changes are allowed at this time.       */
/*                                                                   */
/* NOTE: It is essential that cwbUP_FreeLock is called when your     */
/*       application is no longer accessing the update entries.  If  */
/*       cwbUP_FreeLock is not called, other applications will not   */
/*       be able to access or modify the update entries.             */
/*                                                                   */
/* Usage Notes:                                                      */
/*                                                                   */
/*********************************************************************/
unsigned int CWB_ENTRY cwbUP_SetTargetPath(
                             cwbUP_EntryHandle entryHandle,
                             char *entryTarget);



/*********************************************************************/
/* Callback section:                                                 */
/*********************************************************************/
/*                                                                   */
/*   Description of what this is about.                              */
/*                                                                   */
/*********************************************************************/

/***********************************************************************/
/* Callback prototypes                                                 */
/***********************************************************************/
unsigned long _declspec(dllexport) cwbUP_PreUpdateCallback();
unsigned long _declspec(dllexport) cwbUP_PostUpdateCallback();
unsigned long _declspec(dllexport) cwbUP_PreMigrationCallback();
unsigned long _declspec(dllexport) cwbUP_PostMigrationCallback();



#if defined( __cplusplus )
}
#endif

#endif /* _CWBUP_H_ */
