/********************************************************************/
/* 5769-XE1                                                         */         
/* (C) Copyright IBM Corp. 1995,2005                                */         
/* All rights reserved.                                             */         
/* US Government Users Restricted Rights -                          */         
/* Use, duplication or disclosure restricted                        */         
/* by GSA ADP Schedule Contract with IBM Corp.                      */         
/*                                                                  */         
/* Licensed Materials-Property of IBM                               */         
/*                                                                  */         
/********************************************************************/
/********************************************************************/
/*                                                                  */
/* Module:                                                          */
/*   CWBSOAPI.H                                                     */
/*                                                                  */
/* Purpose:                                                         */
/*   It contains the declarations for the following API's:          */
/*     CWBSO_CloseList                                              */
/*     CWBSO_CopyObjHandle                                          */
/*     CWBSO_CreateErrorHandle                                      */
/*     CWBSO_CreateListHandle                                       */
/*     CWBSO_CreateParmObjHandle                                    */
/*     CWBSO_DeleteErrorHandle                                      */
/*     CWBSO_DeleteListHandle                                       */
/*     CWBSO_DeleteObjHandle                                        */
/*     CWBSO_DeleteParmObjHandle                                    */
/*     CWBSO_DisallowListActions                                    */
/*     CWBSO_DisallowListFilter                                     */
/*     CWBSO_DisplayErrMsg                                          */
/*     CWBSO_DisplayList                                            */
/*     CWBSO_DisplayObjAttr                                         */
/*     CWBSO_GetErrMsgText                                          */
/*     CWBSO_GetListSize                                            */
/*     CWBSO_GetObjAttr                                             */
/*     CWBSO_GetObjHandle                                           */
/*     CWBSO_OpenList                                               */
/*     CWBSO_ReadListProfile                                        */
/*     CWBSO_RefreshObj                                             */
/*     CWBSO_ResetParmObj                                           */
/*     CWBSO_SetListFilter                                          */
/*     CWBSO_SetListProfile                                         */
/*     CWBSO_SetListSortFields                                      */
/*     CWBSO_SetListTitle                                           */
/*     CWBSO_SetObjAttr                                             */
/*     CWBSO_SetParameter                                           */
/*     CWBSO_WaitForObj                                             */
/*     CWBSO_WriteListProfile                                       */
/*     CWBSO_DisplaySplf                                            */
/*                                                                  */
/*   System Object Access provides a viewing capability which allows*/
/*   users to work with common OS/400 objects on the client using   */
/*   graphical interfaces.  OS/400 objects which can be accessed    */
/*   include printers, spooled files, jobs, job logs, and messages. */
/*   System Object Access also includes enablers (APIs) which       */
/*   applications can use to access data in AS/400 objects or       */
/*   request graphical lists and attribute views of the object data.*/
/*                                                                  */
/* API flow for lists                                               */
/*                                                                  */
/*   The APIs for manipulating lists of objects must be called in   */
/*   the correct order.  The basic flow is as follows:              */
/*     CreateErrorHandle -- Creates a handle to an "error" object   */
/*                          to be passed to other APIs              */
/*     CreateListHandle -- Instantiates a list object on the client */
/*     OpenList -- Builds list on AS/400 associated with client     */
/*                 list                                             */
/*     (Manipulate the list and its objects using various generic   */
/*      and subclass APIs)                                          */
/*     CloseList -- Closes list and release resource on AS/400      */
/*     DeleteListHandle -- Destroys list object on the client       */
/*                                                                  */
/*   The CreateListHandle API must be called to create a list before*/
/*   any other list APIs can be called.  The CreateListHandle API   */
/*   returns a list handle to the caller.  The list handle must be  */
/*   passed as input to all other list APIs.                        */
/*                                                                  */
/*   After the list is allocated, the SetListFilter API can be      */
/*   called to change the filter criteria for the list.             */
/*   SetListFilter is optional; if it is not called the list will be*/
/*   built with the default filter criteria.                        */
/*                                                                  */
/*   Similarly, the SetListSortFields API can be called to define   */
/*   the attributes that the list will be sorted on.  If it is not  */
/*   called the list will not be sorted.                            */
/*                                                                  */
/*   The OpenList API must be called to build the list of objects.  */
/*   This will result in a request to be sent to the AS/400.  The   */
/*   list will be built on the AS/400 and some or all of the objects*/
/*   (records) in the list will be buffered down to the list on the */
/*   client.  Although all objects in the list are not necessarily  */
/*   cached on the client, the APIs will behave as if they are.     */
/*                                                                  */
/*   Once the OpenList API has been called successfully, the        */
/*   following APIs can be called:                                  */
/*                                                                  */
/*     - GetObjHandle to retrieve a handle to a specific object in  */
/*       the list.  The object handle can then be used to manipulate*/
/*       the specific object.                                       */
/*     - DeleteObjHandle to release the handle returned by          */
/*       GetObjHandle.                                              */
/*     - DisplayList to display the "spreadsheet" view of the list. */
/*     - GetListSize to retrieve the number of objects in the list. */
/*     - CloseList to close the list on the AS/400 and destroy all  */
/*       client objects in the list.  All object handles returned by*/
/*       GetListObject are not longer valid after the list is closed*/
/*       After the list is closed, the APIs in this list cannot be  */
/*       called until the OpenList API is called again.             */
/*                                                                  */
/*   The DeleteListHandle API should be called to destroy the list  */
/*   object.                                                        */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Link with CWBSOAPI.LIB import library.                         */
/*   This module is to be used in conjunction with CWBSOAPI.DLL.    */
/*                                                                  */
/********************************************************************/

#ifndef _CWBSOAPI_H_
    #define _CWBSOAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <windows.h>
#include "cwbsojob.h"
#include "cwbsomsg.h"
#include "cwbsoprt.h"
#include "cwbsosfl.h"
#include "cwbsotif.h"
#include "cwbsolet.h"
#include "cwbsoltr.h"
#include "cwbsohwr.h"
#include "cwbsohw2.h"
#include "cwbsohw3.h"
#include "cwbsohw4.h"
#include "cwbsohw5.h"
#include "cwbsohw6.h"
#include "cwbsohw7.h"
#include "cwbsohw8.h"
#include "cwbsohwa.h"
#include "cwbsohwb.h"
#include "cwbsoswp.h"
#include "cwbsorte.h"
#include "cwbsoprf.h"
#include "cwbsotca.h"
#include "cwbsousr.h"
#include "cwbsousg.h"
#include "cwbsoprf.h"
//BTW#include "cwbsosmp.h"
#include "cwb.h"
#include "cwbcosys.h"


/* Handle typedefs */
typedef unsigned long CWBSO_HANDLE_T;
typedef CWBSO_HANDLE_T CWBSO_ERR_HANDLE;
typedef CWBSO_HANDLE_T CWBSO_LIST_HANDLE;
typedef CWBSO_HANDLE_T CWBSO_OBJ_HANDLE;
typedef CWBSO_HANDLE_T CWBSO_PARMOBJ_HANDLE;
#define CWBSO_NULL_HANDLE           0	/* Null handle (returned in low memory  */
										/*   conditions)                        */


/* Generic APIs for lists of objects */

/* Types of lists allowed */
typedef enum CWBSO_LISTTYPE {
   CWBSO_LIST_PRT  = 0x0001,			/* list printer devices          */
   CWBSO_LIST_SFL  = 0x0002,			/* list spooled files            */
   CWBSO_LIST_MSG  = 0x0003,			/* list messages                 */
   CWBSO_LIST_JOB  = 0x0004,			/* list jobs                     */
   CWBSO_LIST_SJOB = 0x0005,			/* list server jobs              */
   CWBSO_LIST_IFC  = 0x0006,			/* list interfaces               */
   CWBSO_LIST_ELN  = 0x0007,			/* list ethernet lines           */
   CWBSO_LIST_TLN  = 0x0008,			/* list token ring lines         */
   CWBSO_LIST_HW   = 0x0009,			/* list hardware resources       */
   CWBSO_LIST_SW   = 0x000A,			/* list software products        */
   CWBSO_LIST_RTE  = 0x000B,			/* list TCP/IP routes            */
   CWBSO_LIST_PRF  = 0x000C,			/* list user profiles            */
   CWBSO_LIST_SMP  = 0x000D,              /* list libraries in QSYS	   */
   CWBSO_LIST_DUMMY= 0x7FFF			/* Force two bytes               */
} CWBSO_LISTTYPE;

/* Types of objects allowed */										  
typedef enum CWBSO_OBJTYPE {										  
   CWBSO_OBJ_TCA  = 0x0011			/* TCPIP Attributes              */
} CWBSO_OBJTYPE;													


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_CloseList                                                */
/*                                                                  */
/* Purpose:                                                         */
/*   Closes the list of objects and frees up resources allocated    */
/*   on the AS/400.                                                 */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_LIST_HANDLE listHandle - input                           */
/*           A handle to a list returned by a previous call to      */
/*           "CWBSO_CreateListHandle."                              */
/*                                                                  */
/*   CWBSO_ERR_HANDLE errorHandle - input                           */
/*           A handle to an error returned by a previous call to    */
/*           "CWBSO_CreateErrorHandle." When the value returned     */
/*           by this API is CWBSO_ERROR_OCCURRED, the error handle  */
/*           may be used to retrieve the error message text or      */
/*           display the error to the user.                         */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_LIST_HANDLE - The list handle specified is not       */
/*                           valid.                                 */
/*   CWBSO_BAD_ERR_HANDLE - The error handle specified is not       */
/*                          valid.                                  */
/*   CWBSO_ERROR_OCCURRED - An error occurred.  Use the error       */
/*                          handle for more information.            */
/*   CWBSO_LOW_MEMORY - Not enough memory is available for the      */
/*                      request.                                    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   "CWBSO_CreateListHandle" must be called prior to calling       */
/*   this API.  The list handle returned by CWBSO_CreateListHandle  */
/*   must be passed as input to this API.                           */
/*                                                                  */
/*   "CWBSO_CreateErrorHandle" must be called prior to calling      */
/*   this API.  The error handle returned by                        */
/*   CWBSO_CreateErrorHandle must be passed as input to this API.   */
/*                                                                  */
/*   The list must currently be open.  The list is opened by        */
/*   calling "CWBSO_OpenList."                                      */
/*                                                                  */
/*   This API will not end the conversation with the AS/400.  For   */
/*   the conversation to be ended the list must be deleted using    */
/*   "CWBSO_DeleteListHandle."                                      */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_CloseList(
                CWBSO_LIST_HANDLE listHandle,           
                CWBSO_ERR_HANDLE errorHandle);          

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_CopyObjHandle                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Creates an new instance of an object and returns a handle to   */
/*   the new instance.  This does not create a new object on the    */
/*   AS/400.  It merely creates an additional instance of an AS/400 */
/*   object on the client.                                          */
/*                                                                  */
/*   Object handles returned by "CWBSO_GetObjHandle" are always     */
/*   destroyed when the list containing the object is closed.  This */
/*   API allows the creation of an instance of the object that will */
/*   persist after the list is closed.                              */
/*                                                                  */
/*   The object instance created by this API is kept in sync with   */
/*   the object in the list.  In other words, if one of the objects */
/*   is changed, the changes will be apparent in the other object.  */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_OBJ_HANDLE objectHandle - input                          */
/*           A handle to an object returned by a previous call to   */
/*           "CWBSO_GetObjHandle" or "CWBSO_CopyObjHandle."         */
/*                                                                  */
/*   CWBSO_OBJ_HANDLE * lpNewObjectHandle - output               */
/*           A long pointer to a handle which will be set to a new  */
/*           handle for the same AS/400 object.  This handle may be */
/*           used with any other API that accepts an object handle  */
/*           with the exception that some APIs only operate on      */
/*           specific types of objects.                             */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_LOW_MEMORY - Not enough memory is available for the      */
/*                      request.                                    */
/*   CWBSO_BAD_OBJ_HANDLE - The object handle specified is not      */
/*                          valid.                                  */
/*                                                                  */
/* Usage Notes:                                                     */
/*   "CWBSO_GetObjHandle" or "CWBSO_CopyObjHandle"  must be called  */
/*   prior to calling this API.  The object handle returned by      */
/*   CWBSO_GetObjHandle or CWBSO_CopyObjHandle must be passed as    */
/*   input to this API.                                             */
/*                                                                  */
/*   When the object is no longer needed the calling program is     */
/*   responsible for doing the following:                           */
/*                                                                  */
/*   -  Call "CWBSO_DeleteObjHandle" to free up resources allocated */
/*      on the client.                                              */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_CopyObjHandle(
                CWBSO_OBJ_HANDLE objectHandle,          
                CWBSO_OBJ_HANDLE * lpNewObjectHandle); 

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_CreateErrorHandle                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Creates an error handle.  An error handle is used to contain   */
/*   error messages returned from other APIs.  The error handle may */
/*   be used to display the error in a dialog or retreive the       */
/*   associated error message text.                                 */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_ERR_HANDLE * lpErrorHandle - output                   */
/*           A long pointer to a handle which will be set to the    */
/*           handle for an error.                                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_LOW_MEMORY - Not enough memory is available for the      */
/*                      request.                                    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   When the error handle is no longer needed the calling program  */
/*   is responsible for doing the following:                        */
/*                                                                  */
/*   -  Call "CWBSO_DeleteErrorHandle" to free up resources         */
/*      allocated on the client.                                    */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_CreateErrorHandle(
                CWBSO_ERR_HANDLE * lpErrorHandle);   

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_CreateListHandle                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Creates a new list and returns a handle to the list.           */
/*                                                                  */
/* Parameters:                                                      */
/*   char * lpszSystemName - input                               */
/*           The name of the AS/400 system on which the list will   */
/*           be built.  The name specified must be a configured     */
/*           AS/400.  If the client is not currently connected to   */
/*           the AS/400, a connection will be established when the  */
/*           list is opened.   If NULL is specified for the system  */
/*           name, the current Client Access/400 default system     */
/*           will be used.                                          */
/*                                                                  */
/*   char * lpszApplicationName - input                          */
/*           A character string that identifies the application     */
/*           that will be interacting with the list.  The maximum   */
/*           length of this string is 10 characters excluding the   */
/*           NULL terminator.                                       */
/*                                                                  */
/*   CWBSO_LISTTYPE type - input                                    */
/*           The type of list to be built.                          */
/*                                                                  */
/*           Specify one of the following:                          */
/*                                                                  */
/*           CWBSO_LIST_JOB           List of jobs                  */
/*           CWBSO_LIST_SJOB          List of server jobs           */
/*           CWBSO_LIST_MSG           List of messages              */
/*           CWBSO_LIST_PRT           List of printers              */
/*           CWBSO_LIST_SFL           List of spooled files         */
/*		 CWBSO_LIST_IFC		  List interfaces               */
/*		 CWBSO_LIST_ELN		  List ethernet lines           */
/*		 CWBSO_LIST_TLN		  List token ring lines         */
/*		 CWBSO_LIST_HWL		  List hardware resources       */
/*		 CWBSO_LIST_SW		  List software products        */
/*		 CWBSO_LIST_RTE		  List TCP/IP routes            */
/*		 CWBSO_LIST_PRF		  List user profiles            */
/*		 CWBSO_LIST_SMP		  List libraries in QSYS        */
/*                                                                  */
/*   CWBSO_LIST_HANDLE * lpListHandle - output                   */
/*           A long pointer to a handle which will be set to        */
/*           the handle for the newly created list.  This handle    */
/*           may be used with any other API that accepts a list     */
/*           handle.                                                */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_LISTTYPE - The value specified for type of list is   */
/*                        not valid.                                */
/*   CWBSO_LOW_MEMORY - Not enough memory is available for the      */
/*                      request.                                    */
/*   CWBSO_BAD_SYSTEM_NAME - The system name specified is not a     */
/*                           valid AS/400 system name.              */
/*                                                                  */
/* Usage Notes:                                                     */
/*   When the list is no longer needed the calling program          */
/*   is responsible for doing the following:                        */
/*                                                                  */
/*   -  Call "CWBSO_DeleteListHandle" to free up resources          */
/*      allocated on the client.                                    */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_CreateListHandle(char*              lpszSystemName,
                                              char*              lpszApplicationName,
                                              CWBSO_LISTTYPE     type,
                                              CWBSO_LIST_HANDLE* lpListHandle);   

unsigned int CWB_ENTRY CWBSO_CreateListHandleW(wchar_t *           lpszSystemName,
                                               wchar_t *           lpszApplicationName,
                                               CWBSO_LISTTYPE      type,
                                               CWBSO_LIST_HANDLE * lpListHandle);   
#if ( defined(CWB_UNICODE) )
   #define CWBSO_CreateListHandle CWBSO_CreateListHandleW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_CreateListHandleEx                                       */
/*                                                                  */
/* Purpose:                                                         */
/*   Creates a new list and returns a handle to the list.           */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle  systemObjectHandle - input                    */
/*           A handle to the system object that represents the      */
/*           AS/400 system on which the list will be built.         */
/*           The handle specified must be for a configured          */
/*           AS/400.                                                */
/*                                                                  */
/*   CWBSO_LISTTYPE type - input                                    */
/*           The type of list to be built.                          */
/*                                                                  */
/*           Specify one of the following:                          */
/*                                                                  */
/*           CWBSO_LIST_JOB           List of jobs                  */
/*           CWBSO_LIST_SJOB          List of server jobs           */
/*           CWBSO_LIST_MSG           List of messages              */
/*           CWBSO_LIST_PRT           List of printers              */
/*           CWBSO_LIST_SFL           List of spooled files         */
/*		 CWBSO_LIST_IFC		  List interfaces               */
/*		 CWBSO_LIST_ELN		  List ethernet lines           */
/*		 CWBSO_LIST_TLN		  List token ring lines         */
/*		 CWBSO_LIST_HWL		  List hardware resources       */
/*		 CWBSO_LIST_SW		  List software products        */
/*		 CWBSO_LIST_RTE		  List TCP/IP routes            */
/*		 CWBSO_LIST_PRF		  List user profiles            */
/*		 CWBSO_LIST_SMP		  List libraries in QSYS        */
/*                                                                  */
/*   CWBSO_LIST_HANDLE * lpListHandle - output                   */
/*           A long pointer to a handle which will be set to        */
/*           the handle for the newly created list.  This handle    */
/*           may be used with any other API that accepts a list     */
/*           handle.                                                */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_LISTTYPE - The value specified for type of list is   */
/*                        not valid.                                */
/*   CWBSO_LOW_MEMORY - Not enough memory is available for the      */
/*                      request.                                    */
/*   CWBSO_BAD_SYSTEM_NAME - The system object handle specified is  */
/*                           not a valid system object handle.      */
/*                                                                  */
/* Usage Notes:                                                     */
/*   When the list is no longer needed the calling program          */
/*   is responsible for doing the following:                        */
/*                                                                  */
/*   -  Call "CWBSO_DeleteListHandle" to free up resources          */
/*      allocated on the client.                                    */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_CreateListHandleEx(
                cwbCO_SysHandle systemObjectHandle,             
                CWBSO_LISTTYPE type,                    
                CWBSO_LIST_HANDLE * lpListHandle);                      

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_CreateObjHandle                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   Creates a new object handle and returns a handle to the object.*/
/*   Use this API to access remote objects that do not conform the  */
/*   list format.                                                   */ 
/*                                                                  */
/* Parameters:                                                      */
/*   char * lpszSystemName - input                                  */
/*           The name of the AS/400 system on which the object will */
/*           be built.  The name specified must be a configured     */
/*           AS/400.  If the client is not currently connected to   */
/*           the AS/400, a connection will be established when the  */
/*           object is created. If NULL is specified for the system */
/*           name, the current Client Access/400 default system     */
/*           will be used.                                          */
/*                                                                  */
/*   char* lpszApplicationName - input                              */
/*           A character string that identifies the application     */
/*           that will be interacting with the object.  The maximum */
/*           length of this string is 10 characters excluding the   */
/*           NULL terminator.                                       */
/*                                                                  */
/*   CWBSO_OBJTYPE type - input                                     */
/*           The type of object to be built.                        */
/*                                                                  */
/*           Specify one of the following:                          */
/*                                                                  */
/*           CWBSO_OBJ_TCPIPATTR      TCP/IP Attributes             */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_LOW_MEMORY - Not enough memory is available for the      */
/*                      request.                                    */
/*   CWBSO_BAD_SYSTEM_NAME - The system name specified is not a     */
/*                           valid AS/400 system name.              */
/*                                                                  */
/* Usage Notes:                                                     */
/*   When the list is no longer needed the calling program          */
/*   is responsible for doing the following:                        */
/*                                                                  */
/*   -  Call "CWBSO_DeleteObjHandle" to free up resources          */
/*      allocated on the client.                                    */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_CreateObjHandle(char *             lpszSystemName ,
                                             char *             lpszApplicationName ,
                                             CWBSO_OBJTYPE      type,
                                             CWBSO_OBJ_HANDLE * lpObjHandle);

unsigned int CWB_ENTRY CWBSO_CreateObjHandleW(wchar_t *          lpszSystemName ,
                                              wchar_t *          lpszApplicationName ,
                                              CWBSO_OBJTYPE      type,
                                              CWBSO_OBJ_HANDLE * lpObjHandle);
#if ( defined(CWB_UNICODE) )
   #define CWBSO_CreateObjHandle CWBSO_CreateObjHandleW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_CreateParmObjHandle                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Creates a parameter object and returns a handle to the         */
/*   object.  A parameter object contains a set of parameter        */
/*   IDs and values which may be passed as input to other APIs.     */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_PARMOBJ_HANDLE * lpParmObjHandle - output             */
/*           A long pointer to a handle which will be set to        */
/*           the handle for the new parameter object.               */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_LOW_MEMORY - Not enough memory is available for the      */
/*                      request.                                    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   When the parameter object is no longer needed the calling      */
/*   program is responsible for doing the following:                */
/*                                                                  */
/*   -  Call "CWBSO_DeleteParmObjHandle" to free up resources       */
/*      allocated on the client.                                    */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_CreateParmObjHandle(
                CWBSO_PARMOBJ_HANDLE * lpParmObjHandle); 

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_DeleteErrorHandle                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Deletes an error handle and frees up resources allocated       */
/*   on the client.                                                 */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_ERR_HANDLE errorHandle - input                           */
/*           An error handle returned by a previous call to         */
/*           "CWBSO_CreateErrorHandle."                             */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_ERR_HANDLE - The error handle specified is not       */
/*                          valid.                                  */
/*                                                                  */
/* Usage Notes:                                                     */
/*   "CWBSO_CreateErrorHandle" must be called prior to calling      */
/*   this API.  The error handle returned by                        */
/*   CWBSO_CreateErrorHandle must be passed as input to this API.   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_DeleteErrorHandle(
                CWBSO_ERR_HANDLE errorHandle);          

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_DeleteListHandle                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Deletes the list of objects and frees up resources             */
/*   allocated on the client.                                       */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_LIST_HANDLE listHandle - input                           */
/*           A handle to a list returned by a previous call to      */
/*           "CWBSO_CreateListHandle."                              */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_LIST_HANDLE - The list handle specified is not       */
/*                           valid.                                 */
/*                                                                  */
/* Usage Notes:                                                     */
/*   "CWBSO_CreateListHandle" must be called prior to calling       */
/*   this API.  The list handle returned by                         */
/*   CWBSO_CreateListHandle must be passed as input to this API.    */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_DeleteListHandle(
                CWBSO_LIST_HANDLE listHandle);          

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_DeleteObjHandle                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   Deletes an object handle returned from a previous call to      */
/*   "CWBSO_GetObjHandle" or "CWBSO_CopyObjHandle."                 */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_OBJ_HANDLE objectHandle - input                          */
/*           A handle to an object returned by a previous call to   */
/*           "CWBSO_GetObjHandle" or "CWBSO_CopyObjHandle."         */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_OBJ_HANDLE - The object handle specified is not      */
/*                          valid.                                  */
/*                                                                  */
/* Usage Notes:                                                     */
/*   "CWBSO_GetObjHandle" or "CWBSO_CopyObjHandle"  must be called  */
/*   prior to calling this API.  The object handle returned by      */
/*   CWBSO_GetObjHandle or CWBSO_CopyObjHandle must be passed       */
/*   as input to this API.                                          */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_DeleteObjHandle(
                CWBSO_OBJ_HANDLE objectHandle);         

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_DeleteParmObjHandle                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Deletes a parameter object handle and frees up resources       */
/*   allocated on the client.                                       */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_PARMOBJ_HANDLE parmObjHandle - input                     */
/*           A handle to a parameter object returned by a previous  */
/*           call to "CWBSO_CreateParmObjHandle."                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_PARMOBJ_HANDLE - The parameter object handle         */
/*                              specified is not valid.             */
/*                                                                  */
/* Usage Notes:                                                     */
/*   "CWBSO_CreateParmObjHandle" must be called prior to calling    */
/*   this API.  The parameter object handle returned by             */
/*   CWBSO_CreateParmObjHandle must be passed as input to this API. */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_DeleteParmObjHandle(
                CWBSO_PARMOBJ_HANDLE parmObjHandle);    

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_DisallowListActions                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Sets actions the user is not allowed to perform on objects     */
/*   in a list. This affects the actions available when the list    */
/*   is displayed by calling "CWBSO_DisplayList."  Disallowed       */
/*   actions do not appear in the menu bar, tool bar, or object     */
/*   pop-up menus.                                                  */
/*                                                                  */
/*   This API can only be called once for a list and it must be     */
/*   called prior to displaying the list.                           */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_LIST_HANDLE listHandle - input                           */
/*           A handle to a list returned by a previous call to      */
/*           "CWBSO_CreateListHandle."                              */
/*                                                                  */
/*   unsigned short * lpusActionIDs - input                      */
/*           A long pointer to an array of action identifier values.*/
/*           These values identify which actions the user will not  */
/*           be allowed to perform.                                 */
/*                                                                  */
/*           The valid values for this parameter depend on the type */
/*           of objects in the list.  See the appropriate header    */
/*           files for the valid values:                            */
/*                                                                  */
/*             cwbsojob.h                                           */
/*             cwbsomsg.h                                           */
/*             cwbsoprt.h                                           */
/*             cwbsosfl.h                                           */
/*                                                                  */
/*   unsigned short usCount - input                                 */
/*           The number of action identifier values specified.      */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_LIST_HANDLE - The list handle specified is not valid.*/
/*   CWBSO_BAD_ACTION_ID - An action ID specified is not valid for  */
/*                         the type of list.                        */
/*   CWBSO_LOW_MEMORY - Not enough memory is available for the      */
/*                      request.                                    */
/*   CWBSO_NOT_ALLOWED_NOW - The action requested is not allowed at */
/*                           this time.                             */
/*                                                                  */
/* Usage Notes:                                                     */
/*   "CWBSO_CreateListHandle" must be called prior to calling       */
/*   this API.  The list handle returned by                         */
/*   CWBSO_CreateListHandle must be passed as input to this API.    */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_DisallowListActions(
                CWBSO_LIST_HANDLE listHandle,           
                unsigned short * lpusActionIDs,      
                unsigned short usCount);                

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_DisallowListFilter                                       */
/*                                                                  */
/* Purpose:                                                         */
/*   Sets the list to disallow the user from changing the filter    */
/*   values for the list.  This disables the INCLUDE choice from    */
/*   the VIEW pull-down menu when the list is displayed.  The list  */
/*   is displayed by calling "CWBSO_DisplayList." This API is only  */
/*   meaningful for lists which are displayed by using the          */
/*   CWBSO_DisplayList API.                                         */
/*                                                                  */
/*   This API can only be called once for a list and it must be     */
/*   called prior to displaying the list.                           */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_LIST_HANDLE listHandle - input                           */
/*           A handle to a list returned by a previous call to      */
/*           "CWBSO_CreateListHandle."                              */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_LIST_HANDLE - The list handle specified is not valid.*/
/*                                                                  */
/* Usage Notes:                                                     */
/*   "CWBSO_CreateListHandle" must be called prior to calling this  */
/*   API.  The list handle returned by CWBSO_CreateListHandle must  */
/*   be passed as input to this API.                                */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_DisallowListFilter(
                CWBSO_LIST_HANDLE listHandle);          

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_DisplayErrMsg                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Displays an error message in a dialog box.                     */
/*                                                                  */
/*   This API should only be called when CWBSO_ERROR_OCCURRED       */
/*   is the return value from a call to another API.  In this case, */
/*   there is an error message associated with the error handle.    */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_ERR_HANDLE errorHandle - input                           */
/*           A handle to an error.                                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_ERR_HANDLE - The error handle specified is not valid.*/
/*   CWBSO_NO_ERROR_MESSAGE - The error handle specified contains   */
/*                            no error message.                     */
/*   CWBSO_DISP_MSG_FAILED - The request to display the message     */
/*                           failed.                                */
/*                                                                  */
/* Usage Notes:                                                     */
/*   "CWBSO_CreateErrorHandle" must be called prior to calling this */
/*   API.  The error handle returned by CWBSO_CreateErrorHandle     */
/*   must be passed as input to this API.                           */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_DisplayErrMsg(
                CWBSO_ERR_HANDLE errorHandle);          

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_DisplayList                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Displays the list in a window.  From this window, the user     */
/*   is allowed to perform actions on the objects in the list.      */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_LIST_HANDLE listHandle - input                           */
/*           A handle to a list returned by a previous call to      */
/*           "CWBSO_CreateListHandle."                              */
/*                                                                  */
/*   HINSTANCE hInstance - input                                    */
/*           The program instance passed to the calling program's   */
/*           WinMain procedure.                                     */
/*                                                                  */
/*   int nCmdShow - input                                           */
/*           The show window parameter passed to the calling        */
/*           program's WinMain procedure.  Alternatively, any of    */
/*           the constants defined for the Windows API ShowWindow() */
/*           may be used.                                           */
/*                                                                  */
/*   HWND * lphWnd - output                                      */
/*           A long pointer to a window handle.  This will be set   */
/*           to the handle of the window in which the list is       */
/*           displayed.                                             */
/*                                                                  */
/*   CWBSO_ERR_HANDLE errorHandle - input                           */
/*           A handle to an error object.  If an error occurs that  */
/*           there is error text for, this handle may be used to    */
/*           retreive the error message text or display the error   */
/*           to the user.                                           */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_LIST_HANDLE - The list handle specified is not valid.*/
/*   CWBSO_BAD_ERR_HANDLE - The error handle specified is not       */
/*                          valid.                                  */
/*   CWBSO_DISPLAY_FAILED - The window could not be created.        */
/*   CWBSO_LOW_MEMORY - Not enough memory is available for the      */
/*                      request.                                    */
/*   CWBSO_ERROR_OCCURRED - An error occurred.  Use error handle    */
/*                          for more information.                   */
/*   CWBSO_DISPLAY_NOT_SUPPORTED - Display is not support for this  */
/*                                 list type.                       */
/*                                                                  */
/* Usage Notes:                                                     */
/*   "CWBSO_CreateListHandle" must be called prior to calling       */
/*   this API.  The list handle returned by CWBSO_CreateListHandle  */
/*   must be passed as input to this API.                           */
/*                                                                  */
/*   "CWBSO_CreateErrorHandle" must be called prior to calling      */
/*   this API.  The error handle returned by                        */
/*   CWBSO_CreateErrorHandle must be passed as input to this API.   */
/*                                                                  */
/*   It is not necessary to call CWBSO_OpenList or CWBSO_CloseList  */
/*   when using this API.  CWBSO_DisplayList handles both the       */
/*   opening and closing of the list.                               */
/*                                                                  */
/*   Your program must have a message loop to receive the Windows   */
/*   messages that will be sent during the use of the system        */
/*   object list.                                                   */
/*                                                                  */
/*   Display is supported for printer devices, spooled files, jobs, */
/*   and message only.  Calling CWBSO_DisplayList for other list    */
/*   type will return CWBSO_DISPLAY_NOT_SUPPORTED).                 */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_DisplayList(
                CWBSO_LIST_HANDLE listHandle,           
                HINSTANCE hInstance,                    
                int nCmdShow,                           
                HWND * lphWnd ,                      
                CWBSO_ERR_HANDLE errorHandle);          

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_DisplayObjAttr                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Displays the attributes window for an object.  From this       */
/*   window, the user is allowed to view the object attributes      */
/*   and change attributes that are changeable.                     */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_OBJ_HANDLE objectHandle - input                          */
/*           A handle to an object returned by a previous call to   */
/*           "CWBSO_GetObjHandle or CWBSO_CopyObjHandle."           */
/*                                                                  */
/*   HINSTANCE hInstance - input                                    */
/*           The program instance passed to the calling program's   */
/*           WinMain procedure.                                     */
/*                                                                  */
/*   int nCmdShow - input                                           */
/*           The show window parameter passed to the calling        */
/*           program's WinMain procedure.  Alternatively, any of    */
/*           the constants defined for the Windows API ShowWindow() */
/*           may be used.                                           */
/*                                                                  */
/*   HWND * lphWnd - output                                      */
/*           A long pointer to a window handle.  This will be set   */
/*           to the handle of the window in which the object        */
/*           attributes are displayed.                              */
/*                                                                  */
/*   CWBSO_ERR_HANDLE errorHandle - input                           */
/*           A handle to an error object.  If an error occurs that  */
/*           there is error text for, this handle may be used to    */
/*           retreive the error message and secondary help text.    */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_OBJ_HANDLE - The object handle specified is not      */
/*                          valid.                                  */
/*   CWBSO_BAD_ERR_HANDLE - The error handle specified is not       */
/*                          valid.                                  */
/*   CWBSO_DISPLAY_FAILED - The window could not be created.        */
/*   CWBSO_LOW_MEMORY - Not enough memory is available for the      */
/*                      request.                                    */
/*   CWBSO_ERROR_OCCURRED - An error occurred.  Use error handle    */
/*                          for more information.                   */
/*                                                                  */
/* Usage Notes:                                                     */
/*   "CWBSO_GetObjHandle" or "CWBSO_CopyObjHandle"  must be called  */
/*   prior to calling this API.  The object handle returned by      */
/*   CWBSO_GetObjHandle or CWBSO_CopyObjHandle must be passed as    */
/*   input to this API.                                             */
/*                                                                  */
/*   "CWBSO_CreateErrorHandle" must be called prior to calling      */
/*   this API.  The error handle returned by                        */
/*   CWBSO_CreateErrorHandle must be passed as input to this API.   */
/*                                                                  */
/*   Your program must have a message loop to receive the Windows   */
/*   messages that will be sent during the use of the system        */
/*   object attributes window.                                      */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_DisplayObjAttr(
                CWBSO_OBJ_HANDLE objectHandle,          
                HINSTANCE hInstance,                    
                int nCmdShow,                           
                HWND * lphWnd ,                      
                CWBSO_ERR_HANDLE errorHandle);          

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_GetErrMsgText                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Retrieves the message text from an error handle.               */
/*                                                                  */
/*   This API should only be called when CWBSO_ERROR_OCCURRED       */
/*   is the return value from a call to another API.  In this       */
/*   case there is an error message associated with the error       */
/*   handle.                                                        */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_ERR_HANDLE errorHandle - input                           */
/*           A handle to an error object.  If an error occurs that  */
/*           there is error text for, this handle may be used to    */
/*           retreive the error message and secondary help text.    */
/*                                                                  */
/*   char * lpszMsgBuffer - output                               */
/*           A long pointer to the output buffer where the message  */
/*           text will be placed.                                   */
/*                                                                  */
/*           The message text returned by this API will be          */
/*           translated text.                                       */
/*                                                                  */
/*           The output buffer is not modified when the return code */
/*           is not set to CWBSO_NO_ERROR.                          */
/*                                                                  */
/*   unsigned long ulBufferLength - input                           */
/*           The size, in bytes, of the output buffer argument.     */
/*                                                                  */
/*   unsigned long * lpulBytesNeeded - output                    */
/*           A long pointer to an unsigned long that will be set    */
/*           to the number of bytes needed to place the entire      */
/*           message text in the output buffer.  When this value    */
/*           is less than or equal to the size of output buffer     */
/*           specified, the entire message text is placed in the    */
/*           output buffer.  When this value is greater than the    */
/*           size of output buffer specified, the output buffer     */
/*           contains a null string.  The output buffer is not      */
/*           modified beyond the bytes needed for the message text. */
/*                                                                  */
/*           This value is set to zero when the return code is not  */
/*           set to CWBSO_NO_ERROR.                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_ERR_HANDLE - The error handle specified is not       */
/*                          valid.                                  */
/*   CWBSO_NO_ERROR_MESSAGE - The error handle specified contains   */
/*                            no error message.                     */
/*   CWBSO_GET_MSG_FAILED - The error message text could not be     */
/*                          retrieved.                              */
/*                                                                  */
/* Usage Notes:                                                     */
/*   "CWBSO_CreateErrorHandle" must be called prior to calling      */
/*   this API.  The error handle returned by                        */
/*   CWBSO_CreateErrorHandle must be passed as input to this API.   */
/*                                                                  */
/*   For errors which occurred on the AS/400, the message text      */
/*   will be in the language specified for the user's execution     */
/*   environment.  All other message text will be in the language   */
/*   specified in the Windows Control Panel on the user's           */
/*   personal computer.                                             */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_GetErrMsgText(CWBSO_ERR_HANDLE errorHandle,
                                           char *           lpszMsgBuffer,
                                           unsigned long    ulBufferLength,
                                           unsigned long *  lpulBytesNeeded);    

unsigned int CWB_ENTRY CWBSO_GetErrMsgTextW(CWBSO_ERR_HANDLE errorHandle,
                                            wchar_t *        lpszMsgBuffer,
                                            unsigned long    ulBufferLength,
                                            unsigned long *  lpulBytesNeeded);    

#if ( defined(CWB_UNICODE) )
   #define CWBSO_GetErrMsgText CWBSO_GetErrMsgTextW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_GetListSize                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Retrieves the number of objects in a list.                     */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_LIST_HANDLE listHandle - input                           */
/*           A handle to a list returned by a previous call to      */
/*           "CWBSO_CreateListHandle."                              */
/*                                                                  */
/*   unsigned long  * lpulSize - output                          */
/*           A long pointer to an unsigned long that will be set    */
/*           to the number of entries currently in the list.        */
/*                                                                  */
/*           If the list status indicates the list is complete,     */
/*           this value represents the total number of objects      */
/*           for the list.                                          */
/*                                                                  */
/*           If the list status indicates the list is not           */
/*           completely built, this value represents the number     */
/*           of objects currently available from the host and a     */
/*           subsequent call to this API may indicate that more     */
/*           entries are available.                                 */
/*                                                                  */
/*   unsigned short * lpusStatus - output                        */
/*           A long pointer to an unsigned short that will          */
/*           be set to indicate whether or not the list is          */
/*           completely built.  The value will be set to            */
/*           0 if the list is not completely built or it will       */
/*           be set to 1 if the list is completely built.           */
/*                                                                  */
/*   CWBSO_ERR_HANDLE errorHandle - input                           */
/*           A handle to an error object.  If an error occurs that  */
/*           there is error text for, this handle may be used to    */
/*           retreive the error message and secondary help text.    */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_LIST_HANDLE - The list handle specified is not       */
/*                           valid.                                 */
/*   CWBSO_BAD_ERR_HANDLE - The error handle specified is not       */
/*                          valid.                                  */
/*   CWBSO_LOW_MEMORY - Not enough memory is available for the      */
/*                      request.                                    */
/*   CWBSO_ERROR_OCCURRED - An error occurred.  Use error handle    */
/*                          for more information.                   */
/*                                                                  */
/* Usage Notes:                                                     */
/*   "CWBSO_CreateListHandle" must be called prior to calling       */
/*   this API.  The list handle returned by CWBSO_CreateListHandle  */
/*   must be passed as input to this API.                           */
/*                                                                  */
/*   "CWBSO_CreateErrorHandle" must be called prior to calling      */
/*   this API.  The error handle returned by                        */
/*   CWBSO_CreateErrorHandle must be passed as input to this API.   */
/*                                                                  */
/*   The list must currently be open.  The list is opened by        */
/*   calling "CWBSO_OpenList."  If "CWBSO_CloseList" is called      */
/*   to close a list, CWBSO_OpenList must be called again           */
/*   before this API can be called.                                 */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_GetListSize(
                CWBSO_LIST_HANDLE listHandle,           
                unsigned long  * lpulSize,           
                unsigned short * lpusStatus,         
                CWBSO_ERR_HANDLE errorHandle);          

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_GetObjAttr                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Retrieves the value of an attribute from an object.            */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_OBJ_HANDLE objectHandle - input                          */
/*           A handle to an object returned by a previous call to   */
/*           "CWBSO_GetObjHandle or CWBSO_CopyObjHandle."           */
/*                                                                  */
/*   unsigned short usAttributeID - input                           */
/*           The identifier of the attribute to be retrieved.       */
/*                                                                  */
/*           The valid values for this parameter depend on the      */
/*           type of object.  See the appropriate header files      */
/*           for the valid values:                                  */
/*                                                                  */
/*               cwbsojob.h                                         */
/*               cwbsomsg.h                                         */
/*               cwbsoprt.h                                         */
/*               cwbsosfl.h                                         */
/*                                                                  */
/*   char * lpszBuffer - output                                  */
/*           A long pointer to the output buffer where the          */
/*           attribute value will be placed.                        */
/*                                                                  */
/*           The value returned by this API is NOT a translated     */
/*           string. For instance, "*END" would be returned instead */
/*           of "Ending page" for the ending page attribute of a    */
/*           spooled file.  See the Appendix, "Attribute Special    */
/*           Values" for information on special values that may be  */
/*           returned for each type of object.                      */
/*                                                                  */
/*           The output buffer is not modified when the return code */
/*           is not set to CWBSO_NO_ERROR.                          */
/*                                                                  */
/*   unsigned long ulBufferLength - input                           */
/*           The size, in bytes, of the output buffer argument.     */
/*                                                                  */
/*   unsigned long * lpulBytesNeeded - output                    */
/*           A long pointer to an unsigned long that will be set    */
/*           to the number of bytes needed to place the entire      */
/*           attribute value in the output buffer.  When this       */
/*           value is less than or equal to the size of output      */
/*           buffer specified, the entire attribute value is placed */
/*           in the output buffer.  When this value is greater than */
/*           the size of output buffer specified, the output buffer */
/*           contains a null string.  The output buffer is not      */
/*           modified beyond the bytes needed for the attribute     */
/*           value.                                                 */
/*                                                                  */
/*           This value is set to zero when the return code is not  */
/*           set to CWBSO_NO_ERROR.                                 */
/*                                                                  */
/*   CWBSO_ERR_HANDLE errorHandle - input                           */
/*           A handle to an error object.  If an error occurs that  */
/*           there is error text for, this handle may be used to    */
/*           retreive the error message and secondary help text.    */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_OBJ_HANDLE - The object handle specified is not      */
/*                          valid.                                  */
/*   CWBSO_BAD_ERR_HANDLE - The error handle specified is not       */
/*                          valid.                                  */
/*   CWBSO_BAD_ATTRIBUTE_ID - The attribute key is not valid for    */
/*                            this object.                          */
/*   CWBSO_LOW_MEMORY - Not enough memory is available for the      */
/*                      request.                                    */
/*   CWBSO_ERROR_OCCURRED - An error occurred.  Use error handle    */
/*                          for more information.                   */
/*                                                                  */
/* Usage Notes:                                                     */
/*   "CWBSO_GetObjHandle" or "CWBSO_CopyObjHandle"  must be called  */
/*   prior to calling this API.  The object handle returned by      */
/*   CWBSO_GetObjHandle or CWBSO_CopyObjHandle must be passed as    */
/*   input to this API.                                             */
/*                                                                  */
/*   "CWBSO_CreateErrorHandle" must be called prior to calling      */
/*   this API.  The error handle returned by                        */
/*   CWBSO_CreateErrorHandle must be passed as input to this API.   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_GetObjAttr(CWBSO_OBJ_HANDLE objectHandle,
                                        unsigned short   usAttributeID,
                                        char *           lpszBuffer,
                                        unsigned long    ulBufferLength,
                                        unsigned long *  lpulBytesNeeded,
                                        CWBSO_ERR_HANDLE errorHandle);

unsigned int CWB_ENTRY CWBSO_GetObjAttrW(CWBSO_OBJ_HANDLE objectHandle,
                                         unsigned short   usAttributeID,
                                         wchar_t *        lpszBuffer,
                                         unsigned long    ulBufferLength,
                                         unsigned long *  lpulBytesNeeded,
                                         CWBSO_ERR_HANDLE errorHandle);

#if ( defined(CWB_UNICODE) )
   #define CWBSO_GetObjAttr CWBSO_GetObjAttrW
#endif
/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_GetObjHandle                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Gets a handle to an object in a list.  The object handle       */
/*   returned by this API is valid until the list is closed or      */
/*   until the object handle is deleted.  The object handle may     */
/*   be used to call the following APIs:                            */
/*                                                                  */
/*   -   "CWBSO_CopyObjHandle"                                      */
/*   -   "CWBSO_DeleteObjHandle"                                    */
/*   -   "CWBSO_DisplayObjAttr"                                     */
/*   -   "CWBSO_GetObjAttr"                                         */
/*   -   "CWBSO_RefreshObj"                                         */
/*   -   "CWBSO_SetObjAttr"                                         */
/*   -   "CWBSO_WaitForObj"                                         */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_LIST_HANDLE listHandle - input                           */
/*           A handle to a list returned by a previous call to      */
/*           "CWBSO_CreateListHandle."                              */
/*                                                                  */
/*   unsigned long ulPosition - input                               */
/*           The position of the object within the list for which a */
/*           handle is needed.                                      */
/*                                                                  */
/*           NOTE:  The first object in a list is considered        */
/*                  position 0.                                     */
/*                                                                  */
/*   CWBSO_OBJ_HANDLE * lpObjectHandle - output                  */
/*           A long pointer to a handle which will be set to the    */
/*           handle for the AS/400 object.  This handle may be used */
/*           with any other API that accepts an object handle with  */
/*           the exception that some APIs only operate on specific  */
/*           types of objects.                                      */
/*                                                                  */
/*   CWBSO_ERR_HANDLE errorHandle - input                           */
/*           A handle to an error object.  If an error occurs that  */
/*           there is error text for, this handle may be used to    */
/*           retreive the error message and secondary help text.    */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_LIST_HANDLE - The list handle specified is not       */
/*                           valid.                                 */
/*   CWBSO_BAD_ERR_HANDLE - The error handle specified is not       */
/*                          valid.                                  */
/*   CWBSO_BAD_LIST_POSITION - The position in list specified is    */
/*                             not valid.                           */
/*   CWBSO_LOW_MEMORY - Not enough memory is available for the      */
/*                      request.                                    */
/*   CWBSO_ERROR_OCCURRED - An error occurred.  Use error handle    */
/*                          for more information.                   */
/*                                                                  */
/* Usage Notes:                                                     */
/*   "CWBSO_CreateListHandle" must be called prior to calling       */
/*   this API.  The list handle returned by CWBSO_CreateListHandle  */
/*   must be passed as input to this API.                           */
/*                                                                  */
/*   "CWBSO_CreateErrorHandle" must be called prior to calling      */
/*   this API.  The error handle returned by                        */
/*   CWBSO_CreateErrorHandle must be passed as input to this API.   */
/*                                                                  */
/*   The list must currently be open.  The list is opened by        */
/*   calling "CWBSO_OpenList."  If "CWBSO_CloseList" is called      */
/*   to close a list, CWBSO_OpenList must be called again           */
/*   before this API can be called.                                 */
/*                                                                  */
/*   You cannot access an object using this API until that          */
/*   object has been included in the list.  For example, if         */
/*   you issue this API to get the object in position 100           */
/*   immediately after calling CWBSO_OpenList, the object may       */
/*   not immediately available.  In such instances, use             */
/*   "CWBSO_WaitForObj" to wait until an object is available.       */
/*                                                                  */
/*   The object handle returned by this API must be deleted         */
/*   by a subsequent call to "CWBSO_DeleteObjHandle."               */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_GetObjHandle(
                CWBSO_LIST_HANDLE listHandle,           
                unsigned long ulPosition,               
                CWBSO_OBJ_HANDLE * lpObjectHandle,   
                CWBSO_ERR_HANDLE errorHandle);          

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_OpenList                                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   Opens the list.  A request is sent to the AS/400 system to     */
/*   build the list.                                                */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_LIST_HANDLE listHandle - input                           */
/*           A handle to a list returned by a previous call to      */
/*           "CWBSO_CreateListHandle."                              */
/*                                                                  */
/*   CWBSO_ERR_HANDLE errorHandle - input                           */
/*           A handle to an error returned by a previous call to    */
/*           "CWBSO_CreateErrorHandle." When the value returned     */
/*           by this API is CWBSO_ERROR_OCCURRED, the error handle  */
/*           may be used to retrieve the error message text or      */
/*           display the error to the user.                         */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_LIST_HANDLE - The list handle specified is not       */
/*                           valid.                                 */
/*   CWBSO_BAD_ERR_HANDLE - The error handle specified is not       */
/*                          valid.                                  */
/*   CWBSO_LOW_MEMORY - Not enough memory is available for the      */
/*                      request.                                    */
/*   CWBSO_ERROR_OCCURRED - An error occurred.  Use the error       */
/*                          handle for more information.            */
/*                                                                  */
/* Usage Notes:                                                     */
/*   "CWBSO_CreateListHandle" must be called prior to calling       */
/*   this API.  The list handle returned by CWBSO_CreateListHandle  */
/*   must be passed as input to this API.                           */
/*                                                                  */
/*   "CWBSO_CreateErrorHandle" must be called prior to calling      */
/*   this API.  The error handle returned by                        */
/*   CWBSO_CreateErrorHandle must be passed as input to this API.   */
/*                                                                  */
/*   When the list is no longer needed the calling program          */
/*   is responsible for doing the following:                        */
/*                                                                  */
/*   -   Call "CWBSO_CloseList" to close the list and free          */
/*       up resources allocated on the AS/400.                      */
/*   -   Call "CWBSO_DeleteListHandle" to free up resources         */
/*       allocated on the client.                                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_OpenList(
                CWBSO_LIST_HANDLE listHandle,           
                CWBSO_ERR_HANDLE errorHandle);          

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_ReadListProfile                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   Reads the filter information for the list from the             */
/*   Windows 95 Registry.  The application name must have           */
/*   been set using the CWBSO_SetListProfile API.                   */
/*                                                                  */
/*   This API should be called prior to opening the list using      */
/*   the CWBSO_OpenList or CWBSO_DisplayList APIs.                  */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_LIST_HANDLE listHandle - input                           */
/*           A handle to a list returned by a previous call to      */
/*           "CWBSO_CreateListHandle."                              */
/*                                                                  */
/*   CWBSO_ERR_HANDLE errorHandle - input                           */
/*           A handle to an error object created by a previous call */
/*           to "CWBSO_CreateErrorHandle." When the value returned  */
/*           by this API is CWBSO_ERROR_OCCURRED, the error handle  */
/*           may be used to retrieve the error message text or      */
/*           display the error to the user.                         */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_LIST_HANDLE - The list handle specified is not       */
/*                           valid.                                 */
/*   CWBSO_BAD_ERR_HANDLE - The error handle specified is not       */
/*                          valid.                                  */
/*   CWBSO_SYSTEM_NAME_DEFAULTED - No system name was specified     */
/*                                 on the "CWBSO_CreateListHandle"  */
/*                                 call for the list.               */
/*   CWBSO_LOW_MEMORY - Not enough memory is available for the      */
/*                      request.                                    */
/*   CWBSO_ERROR_OCCURRED - An error occurred.  Use the error       */
/*                          handle for more information.            */
/*                                                                  */
/* Usage Notes:                                                     */
/*   "CWBSO_CreateListHandle" must be called prior to calling       */
/*   this API.  The list handle returned by CWBSO_CreateListHandle  */
/*   must be passed as input to this API.                           */
/*                                                                  */
/*   "CWBSO_SetListProfile" must be called prior to calling         */
/*   this API.                                                      */
/*                                                                  */
/*   This API has no effect on a list that has been opened.         */
/*   In order for the filter criteria in the profile to take        */
/*   effect, the list must be opened after calling this API.        */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_ReadListProfile(
                CWBSO_LIST_HANDLE listHandle,           
                CWBSO_ERR_HANDLE errorHandle);          

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_RefreshObj                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Refreshes an object's attributes from the AS/400.              */
/*   Refreshes all open System Object Access views of the object.   */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_OBJ_HANDLE objectHandle - input                          */
/*           A handle to an object returned by a previous call to   */
/*           "CWBSO_GetObjHandle or CWBSO_CopyObjHandle."           */
/*                                                                  */
/*   HWND hWnd - input                                              */
/*           Handle of window to receive the focus after the        */
/*           refresh is complete.  This parameter may be NULL.      */
/*           If this API is being called from an application window */
/*           procedure, then the current window handle should be    */
/*           supplied.  Otherwise, focus will shift to the most     */
/*           recently opened System Object Access window if one     */
/*           is open.                                               */
/*                                                                  */
/*   CWBSO_ERR_HANDLE errorHandle - input                           */
/*           A handle to an error object.  If an error occurs that  */
/*           there is error text for, this handle may be used to    */
/*           retreive the error message and secondary help text.    */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_OBJ_HANDLE - The object handle specified is not      */
/*                          valid.                                  */
/*   CWBSO_BAD_ERR_HANDLE - The error handle specified is not       */
/*                          valid.                                  */
/*   CWBSO_LOW_MEMORY - Not enough memory is available for the      */
/*                      request.                                    */
/*   CWBSO_ERROR_OCCURRED - An error occurred.  Use error handle    */
/*                          for more information.                   */
/*                                                                  */
/* Usage Notes:                                                     */
/*   "CWBSO_GetObjHandle" or "CWBSO_CopyObjHandle"  must be called  */
/*   prior to calling this API.  The object handle returned by      */
/*   CWBSO_GetObjHandle or CWBSO_CopyObjHandle must be passed as    */
/*   input to this API.                                             */
/*                                                                  */
/*   "CWBSO_CreateErrorHandle" must be called prior to calling      */
/*   this API.  The error handle returned by                        */
/*   CWBSO_CreateErrorHandle must be passed as input to this API.   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_RefreshObj(
                CWBSO_OBJ_HANDLE objectHandle,          
                HWND hWnd ,                             
                CWBSO_ERR_HANDLE errorHandle);          

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_ResetParmObj                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Resets a parameter object to remove any attribute values       */
/*   from the object.                                               */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_PARMOBJ_HANDLE parmObjHandle - input                     */
/*           A handle to a parameter object returned by a previous  */
/*           call to "CWBSO_CreateParmObjHandle."                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_PARMOBJ_HANDLE - The parameter object handle         */
/*                              specified is not valid.             */
/*                                                                  */
/* Usage Notes:                                                     */
/*   "CWBSO_CreateParmObjHandle" must be called prior to calling    */
/*   this API.  The parameter object handle returned by             */
/*   CWBSO_CreateParmObjHandle must be passed as input to this API. */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_ResetParmObj(
                CWBSO_PARMOBJ_HANDLE parmObjHandle);    

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_SetListFilter                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Sets a filter value for a list.  Depending on the type of      */
/*   list, various filter values may be set.  The filter values     */
/*   control which objects will be included in the list when the    */
/*   list is built by a call to "CWBSO_OpenList."                   */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_LIST_HANDLE listHandle - input                           */
/*           A handle to a list returned by a previous call to      */
/*           "CWBSO_CreateListHandle."                              */
/*                                                                  */
/*   unsigned short usFilterID - input                              */
/*           The filter identifier specifies which portion of       */
/*           the filter to set.                                     */
/*                                                                  */
/*           The valid values for this parameter depend on the      */
/*           type of objects in the list.  See the appropriate      */
/*           header files for the valid values:                     */
/*                                                                  */
/*               cwbsojob.h                                         */
/*               cwbsomsg.h                                         */
/*               cwbsoprt.h                                         */
/*               cwbsosfl.h                                         */
/*                                                                  */
/*   char * lpszValue - input                                    */
/*           The value for the filter attribute.  If multiple items */
/*           are specified, they must be separated by commas.       */
/*                                                                  */
/*           Filter value items specifying AS/400 object names must */
/*           be in uppercase.  Qualified object names must be in    */
/*           the form of library/object.  Qualified job names must  */
/*           be in the form of job-number/user/job-name.            */
/*                                                                  */
/*           Filter value items specifying special values           */
/*           (beginning with asterisk) must be specified in upper   */
/*           case.  See the Appendix, "Attribute Special Values"    */
/*           for information on the special values that may be      */
/*           supplied for each type of object.                      */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_LIST_HANDLE - The list handle specified is not valid.*/
/*   CWBSO_BAD_FILTER_ID - The filter ID specified is not valid     */
/*                         for the type of list.                    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   "CWBSO_CreateListHandle" must be called prior to calling this  */
/*   API.  The list handle returned by CWBSO_CreateListHandle must  */
/*   be passed as input to this API.                                */
/*                                                                  */
/*   This API has no effect on a list that has been opened.         */
/*   In order for the filter criteria to take effect, the list      */
/*   must be opened after calling this API.                         */
/*                                                                  */
/*   Caution should be used when requesting complex filters         */
/*   as list performance may be adversely affected.                 */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_SetListFilter(CWBSO_LIST_HANDLE listHandle,
                                           unsigned short    usFilterID,              
                                           char *            lpszValue);                   

unsigned int CWB_ENTRY CWBSO_SetListFilterW(CWBSO_LIST_HANDLE listHandle,
                                            unsigned short    usFilterID,
                                            wchar_t *         lpszValue); 

#if ( defined(CWB_UNICODE) )
   #define CWBSO_SetListFilter CWBSO_SetListFilterW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_SetListProfile                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Sets the profile name by adding the application name into      */
/*   the Windows 95 Registry.                                       */
/*                                                                  */
/*   Use "CWBSO_ReadListProfile" to read the filter information     */
/*   from the Registry  prior to displaying a list.  Use            */
/*   "CWBSO_WriteListProfile" to write the updated filter           */
/*   information to the Registry before deleting the list.          */
/*                                                                  */
/*   If this API is not called, CWBSO_ReadListProfile and           */
/*   CWBSO_WriteListProfile will have no effect.                    */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_LIST_HANDLE listHandle - input                           */
/*           A handle to a list returned by a previous call to      */
/*           "CWBSO_CreateListHandle."                              */
/*						                                */
/*   char * lpszKey - input	                                */
/*           A long pointer to a string that will be used as the    */
/*           key in the Windows 95 Registry for the list.           */
/*           This name could be the name of the application.        */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_LIST_HANDLE - The list handle specified is not valid.*/
/*   CWBSO_BAD_PROFILE_NAME - The profile name specified is not     */
/*                            valid.                                */
/*                                                                  */
/* Usage Notes:                                                     */
/*   "CWBSO_CreateListHandle" must be called prior to calling this  */
/*   API.  The list handle returned by CWBSO_CreateListHandle must  */
/*   be passed as input to this API.                                */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_SetListProfile(CWBSO_LIST_HANDLE listHandle,
                                            char *            lpszKey);                     

unsigned int CWB_ENTRY CWBSO_SetListProfileW(CWBSO_LIST_HANDLE listHandle,
                                             wchar_t *         lpszKey); 

#if ( defined(CWB_UNICODE) )
   #define CWBSO_SetListProfile CWBSO_SetListProfileW
#endif
/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_SetListSortFields                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Sets the sort criteria for a list.  The sort criteria          */
/*   determines the order objects will appear in the list when      */
/*   the list is built by a call to "CWBSO_OpenList."               */
/*                                                                  */
/*   This API is only valid for lists of jobs and lists of          */
/*   spooled files.  This API is not allowed for lists of           */
/*   messages and lists of printers.                                */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_LIST_HANDLE listHandle - input                           */
/*           A handle to a list returned by a previous call to      */
/*           "CWBSO_CreateListHandle."                              */
/*                                                                  */
/*   unsigned short * lpusSortIDs - input                        */
/*           A long pointer to an array of sort column identifiers. */
/*           The sort IDs specified will replace the current sort   */
/*           criteria for the list.                                 */
/*                                                                  */
/*           The valid values for this parameter depend on the      */
/*           type of objects in the list.  See the appropriate      */
/*           header files for the valid values:                     */
/*                                                                  */
/*               cwbsojob.h                                         */
/*               cwbsosfl.h                                         */
/*                                                                  */
/*           NOTE:  If multiple sort IDs are specified, the order   */
/*           in which they appear in the array defines the order    */
/*           in which sorting will take place.                      */
/*                                                                  */
/*   unsigned short usCount - input                                 */
/*           The number of sort column identifiers specified.       */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_LIST_HANDLE - The list handle specified is not valid.*/
/*   CWBSO_BAD_SORT_ID - A sort ID specified is not valid for the   */
/*                       type of list.                              */
/*   CWBSO_LOW_MEMORY - Not enough memory is available for the      */
/*                      request.                                    */
/*   CWBSO_SORT_NOT_ALLOWED - Sorting is not allowed for this       */
/*                            type of list.                         */
/*                                                                  */
/* Usage Notes:                                                     */
/*   "CWBSO_CreateListHandle" must be called prior to calling this  */
/*   API.  The list handle returned by CWBSO_CreateListHandle must  */
/*   be passed as input to this API.                                */
/*                                                                  */
/*   This API has no effect on a list that has been opened.         */
/*   In order for the sort criteria to take effect, the list        */
/*   must be opened after calling this API.                         */
/*                                                                  */
/*   Caution should be used when requesting complex sorts as        */
/*   list performance may be adversely affected.                    */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_SetListSortFields(
                CWBSO_LIST_HANDLE listHandle,           
                unsigned short * lpusSortIDs,        
                unsigned short usCount);                

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_SetListTitle                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Sets the title for a list.  The title is displayed in the      */
/*   title bar of the window when the list is displayed by a        */
/*   call to "CWBSO_DisplayList."                                   */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_LIST_HANDLE listHandle - input                           */
/*           A handle to a list returned by a previous call to      */
/*           "CWBSO_CreateListHandle."                              */
/*                                                                  */
/*   char * lpszTitle - input                                       */
/*           A long pointer to a string to be used for the list     */
/*           title.  The length of the string must be less than or  */
/*           equal to 79.                                           */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_LIST_HANDLE - The list handle specified is not valid.*/
/*   CWBSO_BAD_TITLE - The title specified is not valid.            */
/*                                                                  */
/* Usage Notes:                                                     */
/*   "CWBSO_CreateListHandle" must be called prior to calling this  */
/*   API.  The list handle returned by CWBSO_CreateListHandle must  */
/*   be passed as input to this API.                                */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_SetListTitle(CWBSO_LIST_HANDLE listHandle ,
                                          char *            lpszTitle);                   

unsigned int CWB_ENTRY CWBSO_SetListTitleW(CWBSO_LIST_HANDLE listHandle,
                                           wchar_t *         lpszTitle); 

#if ( defined(CWB_UNICODE) )
   #define CWBSO_SetListTitle CWBSO_SetListTitleW
#endif
/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_SetObjAttr                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Sets the value of one or more attributes of an object.         */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_OBJ_HANDLE objectHandle - input                          */
/*           A handle to an object returned by a previous call to   */
/*           "CWBSO_GetObjHandle" or "CWBSO_CopyObjHandle."         */
/*                                                                  */
/*   CWBSO_PARMOBJ_HANDLE parmObjHandle - input                     */
/*           A handle to a parameter object returned by a previous  */
/*           call to "CWBSO_CreateParmObjHandle."  The parameter    */
/*           object contains the attributes that are to be modified */
/*           for the object.                                        */
/*                                                                  */
/*   unsigned short * lpusErrorIndex - output                    */
/*           If an error occurred, this value will be set to the    */
/*           index of the parameter item that caused the error.     */
/*           The first parameter item is 1.  This value will be     */
/*           set to 0 if none of the parameter items were in error. */
/*                                                                  */
/*   CWBSO_ERR_HANDLE errorHandle - input                           */
/*           A handle to an error object.  If an error occurs that  */
/*           there is error text for, this handle may be used to    */
/*           retreive the error message and secondary help text.    */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_OBJECT_HANDLE - The object handle specified is not   */
/*                             valid.                               */
/*   CWBSO_BAD_PARMOBJ_HANDLE - The parameter object handle         */
/*                              specified is not valid.             */
/*   CWBSO_BAD_ERR_HANDLE - The error handle specified is not       */
/*                          valid.                                  */
/*   CWBSO_CANNOT_CHANGE_ATTRIBUTE - Attribute is not changeable at */
/*                                   this time.                     */
/*   CWBSO_LOW_MEMORY - Not enough memory is available for the      */
/*                      request.                                    */
/*   CWBSO_ERROR_OCCURRED - An error occurred.  Use error handle    */
/*                          for more information.                   */
/*                                                                  */
/* Usage Notes:                                                     */
/*   "CWBSO_GetObjHandle" or "CWBSO_CopyObjHandle"  must be         */
/*   called prior to calling this API.  The object handle           */
/*   returned by CWBSO_GetObjHandle or CWBSO_CopyObjHandle          */
/*   must be passed as input to this API.                           */
/*                                                                  */
/*   "CWBSO_CreateErrorHandle" must be called prior to calling      */
/*   this API.  The error handle returned by                        */
/*   CWBSO_CreateErrorHandle must be passed as input to this API.   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_SetObjAttr(
                CWBSO_OBJ_HANDLE objectHandle,          
                CWBSO_PARMOBJ_HANDLE parmObjHandle,     
                unsigned short * lpusErrorIndex,     
                CWBSO_ERR_HANDLE errorHandle);          

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_SetParameter                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Sets the value of an attribute of an object.                   */
/*                                                                  */
/*   Multiple calls may be made to this API prior to calling        */
/*   "CWBSO_SetObjAttr."  This allows you to change several         */
/*   attributes for a specific object with one call to              */
/*   CWBSO_SetObjAttr.                                              */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_PARMOBJ_HANDLE parmObjHandle - input                     */
/*           A handle to a parameter object returned by a previous  */
/*           call to "CWBSO_CreateParmObjHandle."                   */
/*                                                                  */
/*   unsigned short usAttributeID - input                           */
/*           The attribute ID for the parameter to be set.          */
/*                                                                  */
/*           The valid values for this parameter depend on the type */
/*           of object.  See the appropriate header files for the   */
/*           valid values:                                          */
/*                                                                  */
/*               cwbsojob.h                                         */
/*               cwbsomsg.h                                         */
/*               cwbsoprt.h                                         */
/*               cwbsosfl.h                                         */
/*                                                                  */
/*   char * lpszValue - input                                    */
/*           A long pointer to an attribute value.  Note that only  */
/*           ASCIIZ strings are accepted.  Binary values must be    */
/*           converted to strings using the appropriate library     */
/*           function.  See the Appendix, "Attribute Special Values"*/
/*           for information on the special values that may be      */
/*           supplied for each type of object.                      */
/*                                                                  */
/*   CWBSO_ERR_HANDLE errorHandle - input                           */
/*           A handle to an error object.  If an error occurs that  */
/*           there is error text for, this handle may be used to    */
/*           retreive the error message and secondary help text.    */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_PARMOBJ_HANDLE - The parameter object handle         */
/*                              specified is not valid.             */
/*   CWBSO_BAD_ERR_HANDLE - The error handle specified is not       */
/*                          valid.                                  */
/*   CWBSO_LOW_MEMORY - Not enough memory is available for the      */
/*                      request.                                    */
/*   CWBSO_ERROR_OCCURRED - An error occurred.  Use error handle    */
/*                          for more information.                   */
/*                                                                  */
/* Usage Notes:                                                     */
/*   "CWBSO_CreateParmObjHandle" must be called prior to            */
/*   calling this API.  The parameter object handle returned        */
/*   by CWBSO_CreateParmObjHandle must be passed as input to        */
/*   this API.                                                      */
/*                                                                  */
/*   "CWBSO_CreateErrorHandle" must be called prior to calling      */
/*   this API.  The error handle returned by                        */
/*   CWBSO_CreateErrorHandle must be passed as input to this API.   */
/*                                                                  */
/*   Calling this API does NOT update an object's attributes        */
/*   on the AS/400.  You must call "CWBSO_SetObjAttr" to            */
/*   actually update the attribute value(s) on the AS/400 for       */
/*   the specified object.                                          */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_SetParameter(CWBSO_PARMOBJ_HANDLE parmObjHandle,
                                          unsigned short       usAttributeID,
                                          char *               lpszValue,
                                          CWBSO_ERR_HANDLE     errorHandle);

unsigned int CWB_ENTRY CWBSO_SetParameterW(CWBSO_PARMOBJ_HANDLE parmObjHandle,
                                           unsigned short       usAttributeID,
                                           wchar_t *            lpszValue,
                                           CWBSO_ERR_HANDLE     errorHandle);

#if ( defined(CWB_UNICODE) )
   #define CWBSO_SetParameter CWBSO_SetParameterW
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_WaitForObj                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Waits until an object is available in a list that is being     */
/*   built asynchronously.                                          */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_LIST_HANDLE listHandle - input                           */
/*           A handle to a list returned by a previous call to      */
/*           "CWBSO_CreateListHandle."                              */
/*                                                                  */
/*   unsigned long ulPosition - input                               */
/*           The position of the desired object within the list.    */
/*                                                                  */
/*           NOTE:  The first object in a list is considered        */
/*           position 0.                                            */
/*                                                                  */
/*   CWBSO_ERR_HANDLE errorHandle - input                           */
/*           A handle to an error object.  If an error occurs that  */
/*           there is error text for, this handle may be used to    */
/*           retreive the error message and secondary help text.    */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_LIST_HANDLE - The list handle specified is not valid.*/
/*   CWBSO_BAD_ERR_HANDLE - The error handle specified is not       */
/*                          valid.                                  */
/*   CWBSO_BAD_LIST_POSITION - The position in list specified       */
/*                             does not exist.                      */
/*   CWBSO_LOW_MEMORY - Not enough memory is available for the      */
/*                      request.                                    */
/*   CWBSO_ERROR_OCCURRED - An error occurred.  Use error handle    */
/*                          for more information.                   */
/*                                                                  */
/* Usage Notes:                                                     */
/*   "CWBSO_CreateListHandle" must be called prior to calling this  */
/*   API.  The list handle returned by CWBSO_CreateListHandle must  */
/*   be passed as input to this API.                                */
/*                                                                  */
/*   "CWBSO_CreateErrorHandle" must be called prior to calling      */
/*   this API.  The error handle returned by                        */
/*   CWBSO_CreateErrorHandle must be passed as input to this API.   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_WaitForObj(
                CWBSO_LIST_HANDLE listHandle,           
                unsigned long ulPosition,               
                CWBSO_ERR_HANDLE errorHandle);          

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_WriteListProfile                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Writes the filter information for the list to the              */
/*   specified key in the Windows 95 registry.  The key name        */
/*   must previously have been set using the                        */
/*   CWBSO_SetListProfile API.                                      */
/*                                                                  */
/*   This API should be called before deleting the list.  This      */
/*   will save any filter criteria changed by the user during       */
/*   the CWBSO_DisplayList API.                                     */
/*                                                                  */
/*   Filter information is saved in the registry by AS/400          */
/*   system and by type of list.  For example, if your              */
/*   application accesses objects from two different AS/400         */
/*   systems, and displays all four types of lists, you would       */
/*   have 8 different sections in the registry that specify         */
/*   filter information.                                            */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_LIST_HANDLE listHandle - input                           */
/*           A handle to a list returned by a previous call to      */
/*           "CWBSO_CreateListHandle."                              */
/*                                                                  */
/*   CWBSO_ERR_HANDLE errorHandle - input                           */
/*           A handle to an error object created by a previous call */
/*           to "CWBSO_CreateErrorHandle." When the value returned  */
/*           by this API is CWBSO_ERROR_OCCURRED, the error handle  */
/*           may be used to retrieve the error message text or      */
/*           display the error to the user.                         */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_LIST_HANDLE - The list handle specified is not       */
/*                           valid.                                 */
/*   CWBSO_BAD_ERR_HANDLE - The error handle specified is not       */
/*                          valid.                                  */
/*   CWBSO_SYSTEM_NAME_DEFAULTED - No system name was specified     */
/*                                 on the "CWBSO_CreateListHandle"  */
/*                                 call for the list.               */
/*   CWBSO_LOW_MEMORY - Not enough memory is available for the      */
/*                      request.                                    */
/*   CWBSO_ERROR_OCCURRED - An error occurred.  Use the error       */
/*                          handle for more information.            */
/*                                                                  */
/* Usage Notes:                                                     */
/*   "CWBSO_CreateListHandle" must be called prior to calling       */
/*   this API.  The list handle returned by CWBSO_CreateListHandle  */
/*   must be passed as input to this API.                           */
/*                                                                  */
/*   "CWBSO_SetListProfile" must be called prior to calling         */
/*   this API.                                                      */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_WriteListProfile(
                CWBSO_LIST_HANDLE listHandle,           
                CWBSO_ERR_HANDLE errorHandle);          

/* Spooled file object specific APIs */

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   CWBSO_DisplaySplf                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Displays a window showing the contents of a spooled file.      */
/*                                                                  */
/*   The AFP Viewer is integrated into System Object Access         */
/*   to provide a high function viewing capability.                 */
/*                                                                  */
/* Parameters:                                                      */
/*   CWBSO_OBJ_HANDLE objectHandle - input                          */
/*           A handle to a spooled file object returned by a        */
/*           previous call to "CWBSO_GetObjHandle" or               */
/*           "CWBSO_CopyObjHandle."                                 */
/*                                                                  */
/*   char * lpszView - input                                     */
/*           A long pointer to a string that specifies the AFP      */
/*           view to be used when this spooled file is displayed.   */
/*           Set to NULL to use the default view.                   */
/*                                                                  */
/*           If a view is specified, it must be an existing view    */
/*           that is stored in the EHNSPORT.INI file.  A view is    */
/*           stored in this file when you take the "Save view"      */
/*           option while using the AFP viewer.                     */
/*                                                                  */
/*   CWBSO_ERR_HANDLE errorHandle - input                           */
/*           A handle to an error object created by a previous call */
/*           to "CWBSO_CreateErrorHandle." When the value returned  */
/*           by this API is CWBSO_ERROR_OCCURRED, the error handle  */
/*           may be used to retrieve the error message text or      */
/*           display the error to the user.                         */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWBSO_NO_ERROR - No error occurred.                            */
/*   CWBSO_BAD_OBJ_HANDLE - The object handle specified is not      */
/*                          valid.                                  */
/*   CWBSO_BAD_ERR_HANDLE - The error handle specified is not       */
/*                          valid.                                  */
/*   CWBSO_LOW_MEMORY - Not enough memory is available for the      */
/*                      request.                                    */
/*   CWBSO_ERROR_OCCURRED - An error occurred.  Use the error       */
/*                          handle for more information.            */
/*                                                                  */
/* Usage Notes:                                                     */
/*   "CWBSO_GetObjHandle" or "CWBSO_CopyObjHandle"  must be         */
/*   called prior to calling this API.  The object handle           */
/*   returned by CWBSO_GetObjHandle or CWBSO_CopyObjHandle          */
/*   must be passed as input to this API.                           */
/*                                                                  */
/*   "CWBSO_CreateErrorHandle" must be called prior to calling      */
/*   this API.  The error handle returned by                        */
/*   CWBSO_CreateErrorHandle must be passed as input to this API.   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY CWBSO_DisplaySplf(CWBSO_OBJ_HANDLE objectHandle,
                                         char *           lpszView,
                                         CWBSO_ERR_HANDLE errorHandle);

unsigned int CWB_ENTRY CWBSO_DisplaySplfW(CWBSO_OBJ_HANDLE objectHandle,
                                          wchar_t *        lpszView,
                                          CWBSO_ERR_HANDLE errorHandle);

#if ( defined(CWB_UNICODE) )
   #define CWBSO_DisplaySplf CWBSO_DisplaySplfW
#endif

#ifdef __cplusplus
}
#endif

#endif /* _CWBSOAPI_H_ */
