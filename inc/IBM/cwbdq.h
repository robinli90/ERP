/********************************************************************/
/*                                                                  */
/* 5722-XE1                                                         */
/* (C) Copyright IBM Corp. 1995,2001                                */
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
/*   CWBDQ.h                                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   The functions listed in this file can be used to access AS/400 */
/*   data queues.  They are useful for developing client/server     */
/*   applications without requiring the use of communications APIs. */
/*                                                                  */
/*   The following APIs are the preferred APIs for creating,        */
/*   deleting, and opening a data queue.  These APIs are to be used */
/*   in conjunction with the cwbCO_SysHandle System Object handle.  */
/*      cwbDQ_CreateEx()                                            */
/*      cwbDQ_CreateExA()                                           */
/*      cwbDQ_CreateExW()                                           */
/*      cwbDQ_DeleteEx()                                            */
/*      cwbDQ_DeleteExA()                                           */
/*      cwbDQ_DeleteExW()                                           */
/*      cwbDQ_OpenEx()                                              */
/*      cwbDQ_OpenExA()                                             */
/*      cwbDQ_OpenExW()                                             */
/*                                                                  */
/*   The following APIs can be used to start and stop a connection  */
/*   to an AS/400 system.  Using cwbDQ_StartSystem() to start a     */
/*   connection to a system before using other APIs which use this  */
/*   system may improve application performance.  Use the           */
/*   cwbDQ_StopSystem() API to close the connection created by      */
/*   the cwbDQ_StartSystem() API when the connection to a system is */
/*   no longer necessary.                                           */
/*      cwbDQ_StartSystem()                                         */
/*      cwbDQ_StartSystemA()                                        */
/*      cwbDQ_StartSystemW()                                        */
/*      cwbDQ_StopSystem()                                          */
/*                                                                  */
/*   The following APIs can be used to access the AS/400 data queue.*/
/*   After the cwbDQ_Open() API is used to create a connection to a */
/*   specific data queue the other APIs can be used to utilize it.  */
/*   Use the cwbDQ_Close() API when the connection is no longer     */
/*   needed.                                                        */
/*      cwbDQ_Create()                                              */
/*      cwbDQ_CreateA()                                             */
/*      cwbDQ_CreateW()                                             */
/*      cwbDQ_Delete()                                              */
/*      cwbDQ_DeleteA()                                             */
/*      cwbDQ_DeleteW()                                             */
/*                                                                  */
/*      cwbDQ_AsyncRead()                                           */
/*      cwbDQ_Cancel()                                              */
/*      cwbDQ_CheckData()                                           */
/*      cwbDQ_Clear()                                               */
/*      cwbDQ_Close()                                               */
/*      cwbDQ_GetLibName()                                          */
/*      cwbDQ_GetLibNameA()                                         */
/*      cwbDQ_GetLibNameW()                                         */
/*      cwbDQ_GetQueueAttr()                                        */
/*      cwbDQ_GetQueueName()                                        */
/*      cwbDQ_GetQueueNameA()                                       */
/*      cwbDQ_GetQueueNameW()                                       */
/*      cwbDQ_GetSysName()                                          */
/*      cwbDQ_GetSysNameA()                                         */
/*      cwbDQ_GetSysNameW()                                         */
/*      cwbDQ_Open()                                                */
/*      cwbDQ_OpenA()                                               */
/*      cwbDQ_OpenW()                                               */
/*      cwbDQ_Peek()                                                */
/*      cwbDQ_Read()                                                */
/*      cwbDQ_Write()                                               */
/*                                                                  */
/*   Following are the declarations for the attributes of a data    */
/*   queue.  The attribute object is used when creating a data      */
/*   queue or when getting or setting the data queue attributes.    */
/*      cwbDQ_CreateAttr()                                          */
/*      cwbDQ_SetMaxRecLen()                                        */
/*      cwbDQ_SetOrder()                                            */
/*      cwbDQ_SetAuthority()                                        */
/*      cwbDQ_SetForceToStorage()                                   */
/*      cwbDQ_SetSenderID()                                         */
/*      cwbDQ_SetKeySize()                                          */
/*      cwbDQ_SetDesc()                                             */
/*      cwbDQ_SetDescA()                                            */
/*      cwbDQ_SetDescW()                                            */
/*      cwbDQ_GetMaxRecLen()                                        */
/*      cwbDQ_GetOrder()                                            */
/*      cwbDQ_GetAuthority()                                        */
/*      cwbDQ_GetForceToStorage()                                   */
/*      cwbDQ_GetSenderID()                                         */
/*      cwbDQ_GetKeySize()                                          */
/*      cwbDQ_GetDesc()                                             */
/*      cwbDQ_GetDescA()                                            */
/*      cwbDQ_GetDescW()                                            */
/*      cwbDQ_DeleteAttr()                                          */
/*                                                                  */
/*   After creation an attribute object will have the default       */
/*   values of:                                                     */
/*      - maximum record length - 1000                              */
/*      - order - FIFO                                              */
/*      - public authority - *LIBCRTAUT                             */
/*      - force to auxiliary storage - FALSE                        */
/*      - sender ID - FALSE                                         */
/*      - key size - 0                                              */
/*      - description - NONE                                        */
/*                                                                  */
/*   Following are the declarations for the functions that use the  */
/*   data object for writing to and reading from a data queue:      */
/*      cwbDQ_CreateData()                                          */
/*      cwbDQ_DeleteData()                                          */
/*      cwbDQ_GetConvert()                                          */
/*      cwbDQ_GetData()                                             */
/*      cwbDQ_GetDataAddr()                                         */
/*      cwbDQ_GetDataLen()                                          */
/*      cwbDQ_GetKey()                                              */
/*      cwbDQ_GetKeyLen()                                           */
/*      cwbDQ_GetRetDataLen()                                       */
/*      cwbDQ_GetRetKey()                                           */
/*      cwbDQ_GetRetKeyLen()                                        */
/*      cwbDQ_GetSearchOrder()                                      */
/*      cwbDQ_GetSenderInfo()                                       */
/*      cwbDQ_GetSenderInfoA()                                      */
/*      cwbDQ_GetSenderInfoW()                                      */
/*      cwbDQ_SetConvert()                                          */
/*      cwbDQ_SetConvertA()                                         */
/*      cwbDQ_SetConvertW()                                         */
/*      cwbDQ_SetData()                                             */
/*      cwbDQ_SetDataAddr()                                         */
/*      cwbDQ_SetKey()                                              */
/*      cwbDQ_SetSearchOrder()                                      */
/*                                                                  */
/*   After creation a data object will have the default values of:  */
/*      - data - NULL and length 0                                  */
/*      - key - NULL and length 0                                   */
/*      - sender ID info - NULL                                     */
/*      - search order - NONE                                       */
/*      - convert - FALSE                                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Link with CWBAPI.LIB import library.                           */
/*   This module is to be used in conjunction with CWBDQ.DLL.       */
/*                                                                  */
/*   In addition to the return codes listed for APIs additional     */
/*   operating system specific return codes may also appear.  The   */
/*   precise meaning of these return codes can be found in the      */
/*   operating system manuals or relevant header files.             */
/*                                                                  */
/********************************************************************/

/* Prevent multiple includes */
#if !defined( _CWBDQ_H_ )
  #define     _CWBDQ_H_

#include <windows.h>

/* Common Client Access/400 API include */
#include "CWB.H"

/* Common Include for System Object APIs */
#include "CWBCOSYS.H"


#ifdef __cplusplus
extern "C" {
#endif


/*------------------------------------------------------------------*/
/* TYPEDEFS:                                                        */
/*------------------------------------------------------------------*/

typedef cwb_Handle cwbDQ_QueueHandle;
typedef cwb_Handle cwbDQ_Attr;
typedef cwb_Handle cwbDQ_Data;
typedef cwb_Handle cwbDQ_ReadHandle;
typedef cwb_Handle cwbDQ_SystemHandle;

/*------------------------------------------------------------------*/
/*                                                                  */
/* Definitions for data queue constants for authority               */
/*                                                                  */
/*------------------------------------------------------------------*/
#define CWBDQ_ALL        0
#define CWBDQ_EXCLUDE    1
#define CWBDQ_CHANGE     2
#define CWBDQ_USE        3
#define CWBDQ_LIBCRTAUT  4

/*------------------------------------------------------------------*/
/*                                                                  */
/* Definitions for data queue constants for order                   */
/*                                                                  */
/*------------------------------------------------------------------*/
#define CWBDQ_SEQ_LIFO   0
#define CWBDQ_SEQ_FIFO   1
#define CWBDQ_SEQ_KEYED  2

/*------------------------------------------------------------------*/
/*                                                                  */
/* Definitions for data queue constants for search order            */
/*                                                                  */
/*------------------------------------------------------------------*/
#define CWBDQ_NONE        0
#define CWBDQ_EQUAL       1
#define CWBDQ_NOT_EQUAL   2
#define CWBDQ_GT_OR_EQUAL 3
#define CWBDQ_GREATER     4
#define CWBDQ_LT_OR_EQUAL 5
#define CWBDQ_LESS        6

/*------------------------------------------------------------------*/
/* Component DQ errors based on CWB_LAST (in CWB.H)                 */
/*------------------------------------------------------------------*/

 #define CWBDQ_START CWB_LAST+1

/*------------------------------------------------------------------*/
/* Invalid attributes handle                                        */
/*------------------------------------------------------------------*/
#define CWBDQ_INVALID_ATTRIBUTE_HANDLE CWBDQ_START

/*------------------------------------------------------------------*/
/* Invalid data handle                                              */
/*------------------------------------------------------------------*/
#define CWBDQ_INVALID_DATA_HANDLE      CWBDQ_START+1

/*------------------------------------------------------------------*/
/* Invalid queue handle                                             */
/*------------------------------------------------------------------*/
#define CWBDQ_INVALID_QUEUE_HANDLE     CWBDQ_START+2

/*------------------------------------------------------------------*/
/* Invalid data queue read handle                                   */
/*------------------------------------------------------------------*/
#define CWBDQ_INVALID_READ_HANDLE      CWBDQ_START+3

/*------------------------------------------------------------------*/
/* Invalid maximum record length for a data queue                   */
/*------------------------------------------------------------------*/
#define CWBDQ_INVALID_QUEUE_LENGTH     CWBDQ_START+4

/*------------------------------------------------------------------*/
/* Invalid key length                                               */
/*------------------------------------------------------------------*/
#define CWBDQ_INVALID_KEY_LENGTH       CWBDQ_START+5

/*------------------------------------------------------------------*/
/* Invalid queue order                                              */
/*------------------------------------------------------------------*/
#define CWBDQ_INVALID_ORDER            CWBDQ_START+6

/*------------------------------------------------------------------*/
/* Invalid queue authority                                          */
/*------------------------------------------------------------------*/
#define CWBDQ_INVALID_AUTHORITY        CWBDQ_START+7

/*------------------------------------------------------------------*/
/* Queue title (description) is too long or cannot be converted     */
/*------------------------------------------------------------------*/
#define CWBDQ_INVALID_QUEUE_TITLE      CWBDQ_START+8

/*------------------------------------------------------------------*/
/* Queue name is too long or cannot be converted                    */
/*------------------------------------------------------------------*/
#define CWBDQ_BAD_QUEUE_NAME           CWBDQ_START+9

/*------------------------------------------------------------------*/
/* Library name is too long or cannot be converted                  */
/*------------------------------------------------------------------*/
#define CWBDQ_BAD_LIBRARY_NAME         CWBDQ_START+10

/*------------------------------------------------------------------*/
/* System name is too long or cannot be converted                   */
/*------------------------------------------------------------------*/
#define CWBDQ_BAD_SYSTEM_NAME          CWBDQ_START+11

/*------------------------------------------------------------------*/
/* Length of key is not correct for this data queue                 */
/* or key length is greater than 0 for a LIFO or FIFO data queue    */
/*------------------------------------------------------------------*/
#define CWBDQ_BAD_KEY_LENGTH           CWBDQ_START+12

/*------------------------------------------------------------------*/
/* Length of data is not correct for this data queue.  Either the   */
/* data length is zero or it is greater than the maximum allowed    */
/* of 31744 bytes (64512 bytes for V4R5M0 and later versions of     */
/* OS/400).                                                         */
/*                                                                  */
/* Note: The maximum allowed data length when connected to          */
/*       OS/400 V4R5M0 and later with Client Access Express V4R5M0  */
/*       and later has been increased to 64512 bytes.  When         */
/*       connected to earlier releases of OS/400 using V4R5M0 of    */
/*       CA Express, 64512 bytes of data may be written to a data   */
/*       queue, but the maximum length of data that may be read     */
/*       from a data queue is 31744 bytes.                          */
/*------------------------------------------------------------------*/
#define CWBDQ_BAD_DATA_LENGTH          CWBDQ_START+13

/*------------------------------------------------------------------*/
/* Wait time is not correct                                         */
/*------------------------------------------------------------------*/
#define CWBDQ_INVALID_TIME             CWBDQ_START+14

/*------------------------------------------------------------------*/
/* Search order is not correct                                      */
/*------------------------------------------------------------------*/
#define CWBDQ_INVALID_SEARCH           CWBDQ_START+15

/*------------------------------------------------------------------*/
/* Returned data was truncated                                      */
/*------------------------------------------------------------------*/
#define CWBDQ_DATA_TRUNCATED           CWBDQ_START+16

/*------------------------------------------------------------------*/
/* Wait time has expired and no data has been returned              */
/*------------------------------------------------------------------*/
#define CWBDQ_TIMED_OUT                CWBDQ_START+17

/*------------------------------------------------------------------*/
/* Command rejected by user exit program                            */
/*------------------------------------------------------------------*/
#define CWBDQ_REJECTED_USER_EXIT       CWBDQ_START+18

/*------------------------------------------------------------------*/
/* Error in user exit program or invalid number of exit programs    */
/*------------------------------------------------------------------*/
#define CWBDQ_USER_EXIT_ERROR          CWBDQ_START+19

/*------------------------------------------------------------------*/
/* Library not found on system                                      */
/*------------------------------------------------------------------*/
#define CWBDQ_LIBRARY_NOT_FOUND        CWBDQ_START+20

/*------------------------------------------------------------------*/
/* Queue not found on system                                        */
/*------------------------------------------------------------------*/
#define CWBDQ_QUEUE_NOT_FOUND          CWBDQ_START+21

/*------------------------------------------------------------------*/
/* No authority to library or data queue                            */
/*------------------------------------------------------------------*/
#define CWBDQ_NO_AUTHORITY             CWBDQ_START+22

/*------------------------------------------------------------------*/
/* Data queue is in an unusable state                               */
/*------------------------------------------------------------------*/
#define CWBDQ_DAMAGED_QUEUE            CWBDQ_START+23

/*------------------------------------------------------------------*/
/* Data queue already exists                                        */
/*------------------------------------------------------------------*/
#define CWBDQ_QUEUE_EXISTS             CWBDQ_START+24

/*------------------------------------------------------------------*/
/* Invalid message length - exceeds queue maximum record length     */
/*------------------------------------------------------------------*/
#define CWBDQ_INVALID_MESSAGE_LENGTH   CWBDQ_START+25

/*------------------------------------------------------------------*/
/* Queue destroyed while waiting to read or peek a record           */
/*------------------------------------------------------------------*/
#define CWBDQ_QUEUE_DESTROYED          CWBDQ_START+26

/*------------------------------------------------------------------*/
/* No data was received                                             */
/*------------------------------------------------------------------*/
#define CWBDQ_NO_DATA                  CWBDQ_START+27

/*------------------------------------------------------------------*/
/* Data cannot be converted for this data queue.  The data queue    */
/* can be used but data cannot be converted between ASCII and       */
/* EBCDIC.  The convert flag on the data object will be ignored.    */
/*------------------------------------------------------------------*/
#define CWBDQ_CANNOT_CONVERT           CWBDQ_START+28

/*------------------------------------------------------------------*/
/* Syntax of the data queue name is incorrect.  Queue name must     */
/* follow AS/400 object syntax.   First character must be           */
/* alphabetic and all following characters alphanumeric             */
/*------------------------------------------------------------------*/
#define CWBDQ_QUEUE_SYNTAX             CWBDQ_START+29

/*------------------------------------------------------------------*/
/* Syntax of the library name is incorrect.  Library name must      */
/* follow AS/400 object syntax.   First character must be           */
/* alphabetic and all following characters alphanumeric             */
/*------------------------------------------------------------------*/
#define CWBDQ_LIBRARY_SYNTAX           CWBDQ_START+30

/*------------------------------------------------------------------*/
/* Address not set.  The data object was not set with with          */
/* cwbDQ_SetDataAddr(), so the address cannot be retrieved.         */
/* Use cwbDQ_GetData() instead of cwbDQ_GetDataAddr().              */
/*------------------------------------------------------------------*/
#define CWBDQ_ADDRESS_NOT_SET          CWBDQ_START+31

/*------------------------------------------------------------------*/
/* Host error occurred for which no return is defined.              */
/* See the error handle for the message text.                       */
/*------------------------------------------------------------------*/
#define CWBDQ_HOST_ERROR               CWBDQ_START+32

/*------------------------------------------------------------------*/
/* Invalid system handle.                                           */
/*------------------------------------------------------------------*/
#define CWBDQ_INVALID_SYSTEM_HANDLE    CWBDQ_START+33

/*------------------------------------------------------------------*/
/* Unexpected error                                                 */
/*------------------------------------------------------------------*/
#define CWBDQ_UNEXPECTED_ERROR         CWBDQ_START+99

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_AsyncRead                                                */
/*                                                                  */
/* Purpose:                                                         */
/*   Read a record from the AS/400 data queue object that is        */
/*   identified by the specified handle.  The AsyncRead will return */
/*   control to the caller immediately.  This call is used in       */
/*   conjunction with the CheckData API.  When a record is read     */
/*   from a data queue it is removed from the data queue.  If the   */
/*   data queue is empty for more than the specified wait time, the */
/*   read is aborted and the CheckData API will return a value of   */
/*   CWBDQ_TIMED_OUT.  You may specifying a wait time from 0 to     */
/*   99,999 or forever (-1).  A wait time of zero will cause the    */
/*   CheckData API to return a value of CWBDQ_TIMED_OUT on it's     */
/*   initial call if there is no data in the data queue.            */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_QueueHandle queueHandle - input                          */
/*     Handle that was returned by a previous call to the           */
/*     cwbDQ_OpenEx of cwbDQ_Open function.  This identifies the    */
/*     AS/400 data queue object.                                    */
/*                                                                  */
/*   cwbDQ_Data data - input                                        */
/*     The data object to be read from the AS/400 data queue.       */
/*                                                                  */
/*   signed long waitTime - input                                   */
/*     Length of time in seconds to wait for data, if the data      */
/*     queue is empty.  A wait time of -1 indicates to wait forever.*/
/*                                                                  */
/*   cwbDQ_ReadHandle * readHandle - output                         */
/*     Pointer to where the cwbDQ_ReadHandle will be written.       */
/*     This handle will be used in subsequent calls to the          */
/*     cwbDQ_CheckData API.                                         */
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
/*   CWBDQ_INVALID_TIME - Invalid wait time.                        */
/*   CWBDQ_INVALID_QUEUE_HANDLE - Invalid queue handle.             */
/*   CWBDQ_INVALID_SEARCH - Invalid search order.                   */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This function requires that you have previously issued:        */
/*     cwbDQ_OpenEx() or cwbDQ_Open()                               */
/*     cwbDQ_CreateData()                                           */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_AsyncRead(
                             cwbDQ_QueueHandle   queueHandle,
                             cwbDQ_Data          data,
                             signed long         waitTime,
                             cwbDQ_ReadHandle   *readHandle,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_Cancel                                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Cancel a previously issued AsyncRead.  This will end the read  */
/*   on the AS/400 data queue.                                      */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_ReadHandle readHandle - input                            */
/*     The handle that was returned by the AsyncRead API.           */
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
/*   CWBDQ_INVALID_READ_HANDLE - Invalid read handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This function requires that you have previously issued:        */
/*     cwbDQ_OpenEx() or cwbDQ_Open()                               */
/*     cwbDQ_CreateData()                                           */
/*     cwbDQ_AsyncRead()                                            */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_Cancel(
                             cwbDQ_ReadHandle    readHandle,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_CheckData                                                */
/*                                                                  */
/* Purpose:                                                         */
/*   Check if data was returned from a previously issued AsyncRead  */
/*   API.  This API can be issued multiple times for a single       */
/*   AsyncRead call.  It will return 0 when the data has actually   */
/*   been returned.                                                 */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_ReadHandle readHandle - input                            */
/*     The handle that was returned by the AsyncRead API.           */
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
/*   CWBDQ_INVALID_READ_HANDLE - Invalid read handle.               */
/*   CWBDQ_DATA_TRUNCATED - Data truncated.                         */
/*   CWBDQ_TIMED_OUT - Wait time expired and no data returned.      */
/*   CWBDQ_REJECTED_USER_EXIT - Command rejected by user exit       */
/*                              program.                            */
/*   CWBDQ_QUEUE_DESTROYED - Queue was destroyed.                   */
/*   CWBDQ_NO_DATA - No data.                                       */
/*   CWBDQ_CANNOT_CONVERT - Unable to convert data.                 */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This function requires that you have previously issued:        */
/*     cwbDQ_OpenEx() or cwbDQ_Open()                               */
/*     cwbDQ_CreateData()                                           */
/*     cwbDQ_AsyncRead()                                            */
/*                                                                  */
/*   If a time limit was specified on the AsyncRead, this API will  */
/*   return CWBDQ_NO_DATA until data is returned (return code will  */
/*   be CWB_OK) or the time limit expires (return code will be      */
/*   CWBDQ_TIMED_OUT).                                              */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_CheckData(
                             cwbDQ_ReadHandle    readHandle,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_Clear                                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   Remove all messages from the AS/400 data queue object that is  */
/*   identified by the specified handle.  If the queue is keyed,    */
/*   messages for a particular key may be removed by specifying     */
/*   the key and key length.  These values should be set to         */
/*   NULL and zero, respectively, if you want to clear all messages */
/*   from the queue.                                                */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_QueueHandle queueHandle - input                          */
/*     Handle that was returned by a previous call to the           */
/*     cwbDQ_OpenEx or cwbDQ_Open function.  This identifies the    */
/*     AS/400 data queue object.                                    */
/*                                                                  */
/*   const unsigned char * key - input                              */
/*     Pointer to the key.  The key may contain embedded NULLs,     */
/*     so it is not an ASCIIZ string.                               */
/*                                                                  */
/*   unsigned short keyLength - input                               */
/*     Length of the key in bytes.                                  */
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
/*   CWBDQ_INVALID_QUEUE_HANDLE - Invalid queue handle.             */
/*   CWBDQ_BAD_KEY_LENGTH - Length of key is not correct.           */
/*   CWBDQ_REJECTED_USER_EXIT - Command rejected by user exit       */
/*                              program.                            */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This function requires that you have previously issued:        */
/*     cwbDQ_OpenEx() or cwbDQ_Open()                               */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_Clear(
                             cwbDQ_QueueHandle     queueHandle,
                             const unsigned char  *key,
                             unsigned short        keyLength,
                             cwbSV_ErrHandle       errorHandle);


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_Close                                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   End the connection with the AS/400 data queue object that is   */
/*   identified by the specified handle.  This will end the         */
/*   conversation with the AS/400 system.                           */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_QueueHandle queueHandle - input                          */
/*     Handle that was returned by a previous call to the           */
/*     cwbDQ_OpenEx or cwbDQ_Open function.  This identifies the    */
/*     AS/400 data queue object.                                    */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBDQ_INVALID_QUEUE_HANDLE - Invalid queue handle.             */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This function requires that you have previously issued:        */
/*     cwbDQ_OpenEx() or cwbDQ_Open()                               */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_Close(
                             cwbDQ_QueueHandle   queueHandle);


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_Create                                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Create an AS/400 data queue object.  After the object is       */
/*   created it can be opened using the cwbDQ_Open API.  It will    */
/*   have the attributes that you specify in the attributes handle. */
/*                                                                  */
/*   This API has been provided for compatibility with previous     */
/*   versions of Client Access.  The cwbDQ_CreateEx API should be   */
/*   used in new applications to provide for greater control over   */
/*   system properties and connection sharing.                      */
/*                                                                  */
/* Parameters:                                                      */
/*   const char *queue - input                                      */
/*     Pointer to the data queue name contained in an ASCIIZ string.*/
/*                                                                  */
/*   const char *library - input                                    */
/*     Pointer to the library name contained in an ASCIIZ string.   */
/*     If this pointer is NULL then the current library will be     */
/*     used (set library to "*CURLIB").                             */
/*                                                                  */
/*   const char *systemName - input                                 */
/*     Pointer to the system name contained in an ASCIIZ string.    */
/*                                                                  */
/*   cwbDQ_Attr queueAttributes - input                             */
/*     Handle to the attributes for the data queue.                 */
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
/*   CWB_COMMUNICATIONS_ERROR - A communications error occurred.    */
/*   CWB_SERVER_PROGRAM_NOT_FOUND - AS/400 application not found.   */
/*   CWB_HOST_NOT_FOUND - AS/400 system inactive or does not exist. */
/*   CWB_INVALID_POINTER - Bad or null pointer.                     */
/*   CWB_SECURITY_ERROR - A security error has occurred.            */
/*   CWB_LICENSE_ERROR - A license error has occurred.              */
/*   CWB_CONFIG_ERROR - A configuration error has occurred.         */
/*   CWBDQ_INVALID_ATTRIBUTE_HANDLE - Invalid attributes handle.    */
/*   CWBDQ_BAD_QUEUE_NAME - Queue name is incorrect.                */
/*   CWBDQ_BAD_LIBRARY_NAME - Library name is incorrect.            */
/*   CWBDQ_BAD_SYSTEM_NAME - System name is incorrect.              */
/*   CWBDQ_REJECTED_USER_EXIT - Command rejected by user exit       */
/*                              program.                            */
/*   CWBDQ_USER_EXIT_ERROR - Error in user exit program.            */
/*   CWBDQ_LIBRARY_NOT_FOUND - Library not found on system.         */
/*   CWBDQ_NO_AUTHORITY - No authority to library.                  */
/*   CWBDQ_QUEUE_EXISTS - Queue already exists.                     */
/*   CWBDQ_QUEUE_SYNTAX - Queue syntax is incorrect.                */
/*   CWBDQ_LIBRARY_SYNTAX - Library syntax is incorrect.            */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This function requires that you have previously issued:        */
/*     cwbDQ_CreateAttr()                                           */
/*     cwbDQ_SetMaxRecLen()                                         */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDQ_Create(
                             const char         *queue,
                             const char         *library,
                             const char         *systemName,
                             cwbDQ_Attr          queueAttributes,
                             cwbSV_ErrHandle     errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDQ_CreateA(
                            LPCSTR               queue,
                            LPCSTR               library,
                            LPCSTR               systemName,
                            cwbDQ_Attr           queueAttributes,
                            cwbSV_ErrHandle      errorHandle);
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDQ_CreateW(
                            LPCWSTR         queue,
                            LPCWSTR         library,
                            LPCWSTR         systemName,
                            cwbDQ_Attr      queueAttributes,
                            cwbSV_ErrHandle errorHandle);
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDQ_Create                    cwbDQ_CreateW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDQ_Create                    cwbDQ_CreateA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_CreateEx                                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   Create an AS/400 data queue object.  After the object is       */
/*   created it can be opened using the cwbDQ_OpenEx API.  It will  */
/*   have the attributes that you specify in the attributes handle. */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle sysHandle - input                              */
/*     Handle to a system object.                                   */
/*                                                                  */
/*   const char *queue - input                                      */
/*     Pointer to the data queue name contained in an ASCIIZ string.*/
/*                                                                  */
/*   const char *library - input                                    */
/*     Pointer to the library name contained in an ASCIIZ string.   */
/*     If this pointer is NULL then the current library will be     */
/*     used (set library to "*CURLIB").                             */
/*                                                                  */
/*   cwbDQ_Attr queueAttributes - input                             */
/*     Handle to the attributes for the data queue.                 */
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
/*   CWB_COMMUNICATIONS_ERROR - A communications error occurred.    */
/*   CWB_SERVER_PROGRAM_NOT_FOUND - AS/400 application not found.   */
/*   CWB_HOST_NOT_FOUND - AS/400 system inactive or does not exist. */
/*   CWB_INVALID_POINTER - Bad or null pointer.                     */
/*   CWB_SECURITY_ERROR - A security error has occurred.            */
/*   CWB_LICENSE_ERROR - A license error has occurred.              */
/*   CWB_CONFIG_ERROR - A configuration error has occurred.         */
/*   CWBDQ_INVALID_ATTRIBUTE_HANDLE - Invalid attributes handle.    */
/*   CWBDQ_BAD_QUEUE_NAME - Queue name is incorrect.                */
/*   CWBDQ_BAD_LIBRARY_NAME - Library name is incorrect.            */
/*   CWBDQ_REJECTED_USER_EXIT - Command rejected by user exit       */
/*                              program.                            */
/*   CWBDQ_USER_EXIT_ERROR - Error in user exit program.            */
/*   CWBDQ_LIBRARY_NOT_FOUND - Library not found on system.         */
/*   CWBDQ_NO_AUTHORITY - No authority to library.                  */
/*   CWBDQ_QUEUE_EXISTS - Queue already exists.                     */
/*   CWBDQ_QUEUE_SYNTAX - Queue syntax is incorrect.                */
/*   CWBDQ_LIBRARY_SYNTAX - Library syntax is incorrect.            */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*   CWB_INVALID_HANDLE - Invalid system handle.                    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This function requires that you have previously issued:        */
/*     cwbCO_CreateSystem()                                         */
/*     cwbDQ_CreateAttr()                                           */
/*     cwbDQ_SetMaxRecLen()                                         */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDQ_CreateEx(
                             cwbCO_SysHandle     sysHandle,
                             const char         *queue,
                             const char         *library,
                             cwbDQ_Attr          queueAttributes,
                             cwbSV_ErrHandle     errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDQ_CreateExA(
                            cwbCO_SysHandle sysHandle,
                            LPCSTR          queue,
                            LPCSTR          library,
                            cwbDQ_Attr      queueAttributes,
                            cwbSV_ErrHandle errorHandle);
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDQ_CreateExW(
                            cwbCO_SysHandle sysHandle,
                            LPCWSTR         queue,
                            LPCWSTR         library,
                            cwbDQ_Attr      queueAttributes,
                            cwbSV_ErrHandle errorHandle);
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDQ_CreateEx                  cwbDQ_CreateExW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDQ_CreateEx                  cwbDQ_CreateExA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_CreateAttr                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Create a data queue attribute object.  The handle returned     */
/*   by this API can be used to set the specific attributes you     */
/*   want for a data queue prior to using it as input for the       */
/*   cwbDQ_Create API.  It may also be used to examine specific     */
/*   attributes of a data queue after using it as input for the     */
/*   cwbDQ_GetQueueAttr API.                                        */
/*                                                                  */
/* Parameters:                                                      */
/*   None.                                                          */
/*                                                                  */
/* Return Value:                                                    */
/*   cwbDQ_Attr - A handle to a cwbDQ_Attr object.                  */
/*                You can use this handle to                        */
/*                get and set attributes.                           */
/*                After creation an attribute object will have      */
/*                the default values of:                            */
/*                    - Maximum Record Length - 1000                */
/*                    - Order - FIFO                                */
/*                    - Authority - LIBCRTAUT                       */
/*                    - Force to Storage - FALSE                    */
/*                    - Sender ID - FALSE                           */
/*                    - Key Length - 0                              */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
cwbDQ_Attr CWB_ENTRY cwbDQ_CreateAttr(void);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_CreateData                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Create the data object.  This data object can be used for      */
/*   both reading and writing data to a data queue.                 */
/*                                                                  */
/* Parameters:                                                      */
/*   None.                                                          */
/*                                                                  */
/* Return Value:                                                    */
/*   cwbDQ_Data - A handle to the data object.                      */
/*                After creation a data object will have            */
/*                the default values of:                            */
/*                    - data - NULL and length 0                    */
/*                    - key - NULL and length 0                     */
/*                    - sender ID info - NULL                       */
/*                    - search order - NONE                         */
/*                    - convert - FALSE                             */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
cwbDQ_Data CWB_ENTRY cwbDQ_CreateData(void);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_Delete                                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Remove all data from an AS/400 data queue and delete           */
/*   the data queue object.                                         */
/*                                                                  */
/*   This API has been provided for compatibility with previous     */
/*   versions of Client Access.  The cwbDQ_DeleteEx API should be   */
/*   used in new applications to provide for greater control over   */
/*   system properties and connection sharing.                      */
/*                                                                  */
/* Parameters:                                                      */
/*   const char *queue - input                                      */
/*     Pointer to the data queue name contained in an ASCIIZ string.*/
/*                                                                  */
/*   const char *library - input                                    */
/*     Pointer to the library name contained in an ASCIIZ string.   */
/*     If this pointer is NULL then the current library will be     */
/*     used (set library to "*CURLIB").                             */
/*                                                                  */
/*   const char *systemName - input                                 */
/*     Pointer to the system name contained in an ASCIIZ string.    */
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
/*   CWB_COMMUNICATIONS_ERROR - A communications error occurred.    */
/*   CWB_SERVER_PROGRAM_NOT_FOUND - AS/400 application not found.   */
/*   CWB_HOST_NOT_FOUND - AS/400 system inactive or does not exist. */
/*   CWB_INVALID_POINTER - Bad or null pointer.                     */
/*   CWB_SECURITY_ERROR - A security error has occurred.            */
/*   CWB_LICENSE_ERROR - A license error has occurred.              */
/*   CWB_CONFIG_ERROR - A configuration error has occurred.         */
/*   CWBDQ_BAD_QUEUE_NAME - Queue name is too long.                 */
/*   CWBDQ_BAD_LIBRARY_NAME - Library name is too long.             */
/*   CWBDQ_BAD_SYSTEM_NAME - System name is too long.               */
/*   CWBDQ_REJECTED_USER_EXIT - Command rejected by user exit       */
/*                              program.                            */
/*   CWBDQ_USER_EXIT_ERROR - Error in user exit program.            */
/*   CWBDQ_LIBRARY_NOT_FOUND - Library not found on system.         */
/*   CWBDQ_QUEUE_NOT_FOUND - Queue not found on system.             */
/*   CWBDQ_NO_AUTHORITY - No authority to queue.                    */
/*   CWBDQ_QUEUE_SYNTAX - Queue syntax is incorrect.                */
/*   CWBDQ_LIBRARY_SYNTAX - Library syntax is incorrect.            */
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
unsigned int CWB_ENTRY cwbDQ_Delete(
                             const char         *queue,
                             const char         *library,
                             const char         *systemName,
                             cwbSV_ErrHandle     errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDQ_DeleteA(
                            LPCSTR               queue,
                            LPCSTR               library,
                            LPCSTR               systemName,
                            cwbSV_ErrHandle      errorHandle);
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDQ_DeleteW(
                            LPCWSTR              queue,
                            LPCWSTR              library,
                            LPCWSTR              systemName,
                            cwbSV_ErrHandle      errorHandle);
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDQ_Delete                    cwbDQ_DeleteW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDQ_Delete                    cwbDQ_DeleteA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_DeleteEx                                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   Remove all data from an AS/400 data queue and delete           */
/*   the data queue object.                                         */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle sysHandle - input                              */
/*     Handle to a system object.                                   */
/*                                                                  */
/*   const char *queue - input                                      */
/*     Pointer to the data queue name contained in an ASCIIZ string.*/
/*                                                                  */
/*   const char *library - input                                    */
/*     Pointer to the library name contained in an ASCIIZ string.   */
/*     If this pointer is NULL then the current library will be     */
/*     used (set library to "*CURLIB").                             */
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
/*   CWB_COMMUNICATIONS_ERROR - A communications error occurred.    */
/*   CWB_SERVER_PROGRAM_NOT_FOUND - AS/400 application not found.   */
/*   CWB_HOST_NOT_FOUND - AS/400 system inactive or does not exist. */
/*   CWB_INVALID_POINTER - Bad or null pointer.                     */
/*   CWB_SECURITY_ERROR - A security error has occurred.            */
/*   CWB_LICENSE_ERROR - A license error has occurred.              */
/*   CWB_CONFIG_ERROR - A configuration error has occurred.         */
/*   CWBDQ_BAD_QUEUE_NAME - Queue name is too long.                 */
/*   CWBDQ_BAD_LIBRARY_NAME - Library name is too long.             */
/*   CWBDQ_REJECTED_USER_EXIT - Command rejected by user exit       */
/*                              program.                            */
/*   CWBDQ_USER_EXIT_ERROR - Error in user exit program.            */
/*   CWBDQ_LIBRARY_NOT_FOUND - Library not found on system.         */
/*   CWBDQ_QUEUE_NOT_FOUND - Queue not found on system.             */
/*   CWBDQ_NO_AUTHORITY - No authority to queue.                    */
/*   CWBDQ_QUEUE_SYNTAX - Queue syntax is incorrect.                */
/*   CWBDQ_LIBRARY_SYNTAX - Library syntax is incorrect.            */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*   CWB_INVALID_HANDLE - Invalid system handle.                    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This function requires that you have previously issued         */
/*     cwbCO_CreateSystem()                                         */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDQ_DeleteEx(
                             cwbCO_SysHandle     sysHandle,
                             const char         *queue,
                             const char         *library,
                             cwbSV_ErrHandle     errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDQ_DeleteExA(
                            cwbCO_SysHandle      sysHandle,
                            LPCSTR               queue,
                            LPCSTR               library,
                            cwbSV_ErrHandle      errorHandle);
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDQ_DeleteExW(
                            cwbCO_SysHandle      sysHandle,
                            LPCWSTR              queue,
                            LPCWSTR              library,
                            cwbSV_ErrHandle      errorHandle);
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDQ_DeleteEx                   cwbDQ_DeleteExW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDQ_DeleteEx                   cwbDQ_DeleteExA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_DeleteAttr                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Delete the data queue attributes.                              */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Attr queueAttributes - input                             */
/*     Handle of the data queue attributes returned by a previous   */
/*     call to cwbDQ_CreateAttr.                                    */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBDQ_INVALID_ATTRIBUTE_HANDLE - Invalid attributes handle.    */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_DeleteAttr(
                             cwbDQ_Attr          queueAttributes);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_DeleteData                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Delete the data object.                                        */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Data data - input                                        */
/*     Handle of the data object that was returned by a previous    */
/*     call to cwbDQ_CreateData.                                    */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBDQ_INVALID_DATA_HANDLE - Invalid data handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_DeleteData(
                             cwbDQ_Data          data);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_GetAuthority                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the attribute for the authority that other users will have */
/*   to the data queue.                                             */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Attr queueAttributes - input                             */
/*     Handle of the data queue attributes returned by a previous   */
/*     call to cwbDQ_CreateAttr.                                    */
/*                                                                  */
/*   unsigned short * authority - output                            */
/*     Pointer to an unsigned short where the authority will        */
/*     be written.  This value will be one of the defined           */
/*     types:                                                       */
/*         CWBDQ_ALL                                                */
/*         CWBDQ_EXCLUDE                                            */
/*         CWBDQ_CHANGE                                             */
/*         CWBDQ_USE                                                */
/*         CWBDQ_LIBCRTAUT                                          */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or null pointer.                     */
/*   CWBDQ_INVALID_ATTRIBUTE_HANDLE - Invalid attributes handle.    */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_GetAuthority(
                             cwbDQ_Attr          queueAttributes,
                             unsigned short     *authority);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_GetConvert                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the value of the convert flag for a data handle.  The      */
/*   convert flag determines if data sent to and recieved from      */
/*   the host is CCSID converted (eg between ASCII and EBCDIC).     */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Data data - input                                        */
/*     Handle of the data object that was returned by a previous    */
/*     call to cwbDQ_CreateData.                                    */
/*                                                                  */
/*   cwb_Boolean * convert - output                                 */
/*     Pointer to a Boolean where the convert flag will be written. */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or null pointer.                     */
/*   CWBDQ_INVALID_DATA_HANDLE - Invalid data handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_GetConvert(
                             cwbDQ_Data          data,
                             cwb_Boolean        *convert);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_GetData                                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the data attribute of the data object.                     */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Data data - input                                        */
/*     Handle of the data object that was returned by a previous    */
/*     call to cwbDQ_CreateData.                                    */
/*                                                                  */
/*   unsigned char * data - output                                  */
/*     Pointer to the data.  The data may contain embedded NULLs,   */
/*     so it is not an ASCIIZ string.                               */
/*                                                                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or null pointer.                     */
/*   CWBDQ_INVALID_DATA_HANDLE - Invalid data handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_GetData(
                             cwbDQ_Data          data,
                             unsigned char      *dataBuffer);


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_GetDataAddr                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the address of where the data buffer is.                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Data data - input                                        */
/*     Handle of the data object that was returned by a previous    */
/*     call to cwbDQ_CreateData.                                    */
/*                                                                  */
/*   unsigned char * * data - output                                */
/*     Pointer to where the buffer address will be written.         */
/*                                                                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or null pointer.                     */
/*   CWBDQ_INVALID_DATA_HANDLE - Invalid data handle.               */
/*   CWBDQ_ADDRESS_NOT_SET - Address not set with cwbDQ_SetDataAddr.*/
/*                                                                  */
/* Usage Notes:                                                     */
/*    Use this function to retrieve the address of where the data   */
/*    is stored.  The data addess must be set with the API          */
/*    cwbDQ_SetDataAddr(), otherwise the return code                */
/*    CWBDQ_ADDRESS_NOT_SET will be returned.                       */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_GetDataAddr(
                             cwbDQ_Data          data,
                             unsigned char     **dataBuffer);


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_GetDataLen                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the data length attribute of the data object.  This is the */
/*   total length of the data object.  To obtain the length of data */
/*   that was read use the cwbDQ_GetRetDataLen() API.               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Data data - input                                        */
/*     Handle of the data object that was returned by a previous    */
/*     call to cwbDQ_CreateData.                                    */
/*                                                                  */
/*   unsigned long * dataLength - output                            */
/*     Pointer to an unsigned long where the length of the data     */
/*     will be written.                                             */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or null pointer.                     */
/*   CWBDQ_INVALID_DATA_HANDLE - Invalid data handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_GetDataLen(
                             cwbDQ_Data          data,
                             unsigned long      *dataLength);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_GetDesc                                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the attribute for the description of the data queue.       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Attr queueAttributes - input                             */
/*     Handle of the data queue attributes returned by a previous   */
/*     call to cwbDQ_CreateAttr.                                    */
/*                                                                  */
/*   char * description - output                                    */
/*     Pointer to a 51 character buffer where the description will  */
/*     be written.  The description is an ASCIIZ string.            */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or NULL pointer.                     */
/*   CWBDQ_INVALID_ATTRIBUTE_HANDLE - Invalid attributes handle.    */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDQ_GetDesc(
                             cwbDQ_Attr          queueAttributes,
                             char               *description);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDQ_GetDescA(
                                        cwbDQ_Attr   queueAttributes
                                      , LPSTR        description
                                    );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDQ_GetDescW(
                                        cwbDQ_Attr   queueAttributes
                                      , LPWSTR       description
                                    );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDQ_GetDesc                   cwbDQ_GetDescW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDQ_GetDesc                   cwbDQ_GetDescA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_GetForceToStorage                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the attribute for whether or not records will be forced to */
/*   auxiliary storage when they are enqueued.                      */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Attr queueAttributes - input                             */
/*     Handle of the data queue attributes returned by a previous   */
/*     call to cwbDQ_CreateAttr.                                    */
/*                                                                  */
/*   cwb_Boolean * forceToStorage - output                          */
/*     Pointer to a Boolean where the force to storage indicator    */
/*     will be written.                                             */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or null pointer.                     */
/*   CWBDQ_INVALID_ATTRIBUTE_HANDLE - Invalid attributes handle.    */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_GetForceToStorage(
                             cwbDQ_Attr          queueAttributes,
                             cwb_Boolean        *forceToStorage);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_GetKey                                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the key attribute of the data object, previously set by    */
/*   the cwbDQ_SetKey API.  This is the key that is used for        */
/*   writing data to a keyed data queue.  Along with the search     */
/*   order, this key is also used to read data from a keyed data    */
/*   queue.  The key that is associated with the record retrieved   */
/*   can be obtained by calling the cwbDQ_GetRetKey API.            */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Data data - input                                        */
/*     Handle of the data object that was returned by a previous    */
/*     call to cwbDQ_CreateData.                                    */
/*                                                                  */
/*   unsigned char * key - output                                   */
/*     Pointer to the key.  The key may contain embedded NULLS,     */
/*     so it is not an ASCIIZ string.                               */
/*                                                                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or null pointer.                     */
/*   CWBDQ_INVALID_DATA_HANDLE - Invalid data handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_GetKey(
                             cwbDQ_Data          data,
                             unsigned char      *key);


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_GetKeyLen                                                */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the key length attribute of the data object.               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Data data - input                                        */
/*     Handle of the data object that was returned by a previous    */
/*     call to cwbDQ_CreateData.                                    */
/*                                                                  */
/*   unsigned short * keyLength - output                            */
/*     Pointer to an unsigned short where the length of the key     */
/*     will be written.                                             */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or null pointer.                     */
/*   CWBDQ_INVALID_DATA_HANDLE - Invalid data handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_GetKeyLen(
                             cwbDQ_Data          data,
                             unsigned short     *keyLength);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_GetKeySize                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the attribute for the key size in bytes.                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Attr queueAttributes - input                             */
/*     Handle of the data queue attributes returned by a previous   */
/*     call to cwbDQ_CreateAttr.                                    */
/*                                                                  */
/*   unsigned short * keySize - output                              */
/*     Pointer to an unsigned short where the key size will         */
/*     written.                                                     */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or null pointer.                     */
/*   CWBDQ_INVALID_ATTRIBUTE_HANDLE - Invalid attributes handle.    */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_GetKeySize(
                             cwbDQ_Attr          queueAttributes,
                             unsigned short     *keySize);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_GetLibName                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Retrieve the library name used with the cwbDQ_OpenEx or        */
/*   cwbDQ_Open API.                                                */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_QueueHandle queueHandle - input                          */
/*     Handle that was returned by a previous call to the           */
/*     cwbDQ_Open function.  This identifies the AS/400 data        */
/*     queue object.                                                */
/*                                                                  */
/*   char * libName - output                                        */
/*     Pointer to a buffer where the library name will be written.  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBDQ_INVALID_QUEUE_HANDLE - Invalid queue handle.             */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This function requires that you have previously issued:        */
/*     cwbDQ_OpenEx() or cwbDQ_Open()                               */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDQ_GetLibName(
                             cwbDQ_QueueHandle   queueHandle,
                             char               *libName);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDQ_GetLibNameA(
                                    cwbDQ_QueueHandle   queueHandle
                                  , LPSTR               libName
                                       );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDQ_GetLibNameW(
                                    cwbDQ_QueueHandle   queueHandle
                                  , LPWSTR              libName
                                       );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDQ_GetLibName                cwbDQ_GetLibNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDQ_GetLibName                cwbDQ_GetLibNameA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_GetMaxRecLen                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the maximum record length for the data queue.              */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Attr queueAttributes - input                             */
/*     Handle of the data queue attributes returned by a            */
/*     call to cwbDQ_CreateAttr.                                    */
/*                                                                  */
/*   unsigned long * maxRecordLength - output                       */
/*     Pointer to an unsigned long where the maximum record length  */
/*     will be written.                                             */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or null pointer.                     */
/*   CWBDQ_INVALID_ATTRIBUTE_HANDLE - Invalid attributes handle.    */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_GetMaxRecLen(
                             cwbDQ_Attr          queueAttributes,
                             unsigned long      *maxRecordLength);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_GetOrder                                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the attribute for the queue order.  If the order is        */
/*   CWBDQ_SEQ_LIFO, the last record written is the first record    */
/*   read (Last In First Out).  If the order is CWBDQ_SEQ_FIFO,     */
/*   the first record written is the first record read (First In    */
/*   First Out).  If the order is CWBDQ_SEQ_KEYED, the order in     */
/*   which records are read from the data queue depends on the      */
/*   value of the search order attribute of the data object and     */
/*   the key value specified for the cwbDQ_SetKey API.  If          */
/*   multiple records contain the key which satisfies the search    */
/*   order, a FIFO scheme is used among those records.              */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Attr queueAttributes - input                             */
/*     Handle of the data queue attributes returned by a previous   */
/*     call to cwbDQ_CreateAttr.                                    */
/*                                                                  */
/*   unsigned short * order - output                                */
/*     Pointer to an unsigned short where the order will be         */
/*     written. Possible values are:                                */
/*         CWBDQ_SEQ_LIFO                                           */
/*         CWBDQ_SEQ_FIFO                                           */
/*         CWBDQ_SEQ_KEYED                                          */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or null pointer.                     */
/*   CWBDQ_INVALID_ATTRIBUTE_HANDLE - Invalid attributes handle.    */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_GetOrder(
                             cwbDQ_Attr          queueAttributes,
                             unsigned short     *order);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_GetQueueAttr                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Retrieve the attributes of the AS/400 data queue object that   */
/*   is identified by the specified handle.  A handle to the data   */
/*   queue attributes will be returned.  The attributes can then    */
/*   be retrieved individually.                                     */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_QueueHandle queueHandle - input                          */
/*     Handle that was returned by a previous call to the           */
/*     cwbDQ_OpenEx or cwbDQ_Open function.  This identifies the    */
/*     AS/400 data queue object.                                    */
/*                                                                  */
/*   cwbDQ_Attr queueAttributes - input/output                      */
/*     The attribute object.  This was the output from the          */
/*     cwbDQ_CreateAttr call.  The attributes will be filled in by  */
/*     this function, and you should call the cwbDQ_DeleteAttr      */
/*     function to delete this object when you have retrieved       */
/*     the attributes from it.                                      */
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
/*   CWBDQ_INVALID_QUEUE_HANDLE - Invalid queue handle.             */
/*   CWBDQ_REJECTED_USER_EXIT - Command rejected by user exit       */
/*                              program.                            */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This function requires that you have previously issued:        */
/*     cwbDQ_OpenEx() or cwbDQ_Open()                               */
/*     cwbDQ_CreateAttr()                                           */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_GetQueueAttr(
                             cwbDQ_QueueHandle   queueHandle,
                             cwbDQ_Attr          queueAttributes,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_GetQueueName                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Retrieve the queue name used with the cwbDQ_Open API.          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_QueueHandle queueHandle - input                          */
/*     Handle that was returned by a previous call to the           */
/*     cwbDQ_Open function.  This identifies the AS/400 data        */
/*     queue object.                                                */
/*                                                                  */
/*   char * queueName - output                                      */
/*     Pointer to a buffer where the queue name will be written.    */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBDQ_INVALID_QUEUE_HANDLE - Invalid queue handle.             */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This function requires that you have previously issued         */
/*   cwbDQ_Open()                                                   */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDQ_GetQueueName(
                             cwbDQ_QueueHandle   queueHandle,
                             char               *queueName);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDQ_GetQueueNameA(
                                      cwbDQ_QueueHandle   queueHandle
                                    , LPSTR               queueName
                                         );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDQ_GetQueueNameW(
                                      cwbDQ_QueueHandle   queueHandle
                                    , LPWSTR              queueName
                                         );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDQ_GetQueueName              cwbDQ_GetQueueNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDQ_GetQueueName              cwbDQ_GetQueueNameA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_GetRetDataLen                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the length of data that was returned.  The returned data   */
/*   length will be zero until a cwbDQ_Read() or cwbDQ_Peek() API   */
/*   is called, then it will have the length of the data that was   */
/*   actually returned.                                             */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Data data - input                                        */
/*     Handle of the data object that was returned by a previous    */
/*     call to cwbDQ_CreateData.                                    */
/*                                                                  */
/*   unsigned long * retDataLength - output                         */
/*     Pointer to an unsigned long where the length of the data     */
/*     returned will be written.                                    */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or null pointer.                     */
/*   CWBDQ_INVALID_DATA_HANDLE - Invalid data handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_GetRetDataLen(
                             cwbDQ_Data          data,
                             unsigned long      *retDataLength);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_GetRetKey                                                */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the returned key of the data object.  This is the key      */
/*   that is associated with the messages that is retrieved from    */
/*   a keyed data queue.  If the search order is a value other than */
/*   CWBDQ_EQUAL, this key may be different than the key used to    */
/*   retrieve the message.                                          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Data data - input                                        */
/*     Handle of the data object that was returned by a previous    */
/*     call to cwbDQ_CreateData.                                    */
/*                                                                  */
/*   unsigned char * retKey - output                                */
/*     Pointer to the returned key.  The key may contain embedded   */
/*     NULLs, so it is not an ASCIIZ string.                        */
/*                                                                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or null pointer.                     */
/*   CWBDQ_INVALID_DATA_HANDLE - Invalid data handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_GetRetKey(
                             cwbDQ_Data          data,
                             unsigned char      *key);


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_GetRetKeyLen                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the returned key length attribute of the data object.      */
/*   This is the length of the key returned by the cwbDQ_GetKey     */
/*   API.                                                           */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Data data - input                                        */
/*     Handle of the data object that was returned by a previous    */
/*     call to cwbDQ_CreateData.                                    */
/*                                                                  */
/*   unsigned short * retKeyLength - output                         */
/*     Pointer to an unsigned short where the length of the key     */
/*     will be written.                                             */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or null pointer.                     */
/*   CWBDQ_INVALID_DATA_HANDLE - Invalid data handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_GetRetKeyLen(
                             cwbDQ_Data          data,
                             unsigned short     *retKeyLength);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_GetSearchOrder                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the search order of the open attributes.  The search       */
/*   order is used when reading or peeking a keyed data queue to    */
/*   identify the relationship between the key of the record to     */
/*   retrieve and the key value specified on the cwbDQ_SetKey API.  */
/*   If the data queue order attribute is not CWBDQ_SEQ_KEYED this  */
/*   property is ignored.                                           */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Data data - input                                        */
/*     Handle of the data object that was returned by a previous    */
/*     call to cwbDQ_CreateData.                                    */
/*                                                                  */
/*   unsigned short * searchOrder - output                          */
/*     Pointer to an unsigned short where the order will be         */
/*     written.  Possible values are:                               */
/*         CWBDQ_NONE                                               */
/*         CWBDQ_EQUAL                                              */
/*         CWBDQ_NOT_EQUAL                                          */
/*         CWBDQ_GT_OR_EQUAL                                        */
/*         CWBDQ_GREATER                                            */
/*         CWBDQ_LT_OR_EQUAL                                        */
/*         CWBDQ_LESS                                               */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or null pointer.                     */
/*   CWBDQ_INVALID_DATA_HANDLE - Invalid data handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_GetSearchOrder(
                             cwbDQ_Data          data,
                             unsigned short     *searchOrder);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_GetSenderID                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the attribute for whether or not information about the     */
/*   sender is kept with each record on the queue.                  */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Attr queueAttributes - input                             */
/*     Handle of the data queue attributes returned by a previous   */
/*     call to cwbDQ_CreateAttr.                                    */
/*                                                                  */
/*   cwb_Boolean * senderID - output                                */
/*     Pointer to a Boolean where the sender ID indicator will be   */
/*     written.                                                     */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or null pointer.                     */
/*   CWBDQ_INVALID_ATTRIBUTE_HANDLE - Invalid attributes handle.    */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_GetSenderID(
                             cwbDQ_Attr         queueAttributes,
                             cwb_Boolean       *senderID);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_GetSenderInfo                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the Sender Information attribute of the open attributes.   */
/*   This information is only available if the senderID attribute   */
/*   of the Data Queue was set on creation.                         */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Data data - input                                        */
/*     Handle of the data object that was returned by a previous    */
/*     call to cwbDQ_CreateData.                                    */
/*                                                                  */
/*   unsigned char * senderInfo - output                            */
/*     Pointer to a 36 character buffer where the sender            */
/*     information will be written. This buffer contains:           */
/*         Job Name     (10 bytes)                                  */
/*         User Name    (10 bytes)                                  */
/*         Job ID       ( 6 bytes)                                  */
/*         User Profile (10 bytes)                                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or NULL pointer.                     */
/*   CWBDQ_INVALID_DATA_HANDLE - Invalid data handle.               */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDQ_GetSenderInfo(
                             cwbDQ_Data          data,
                             unsigned char      *senderInfo);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDQ_GetSenderInfoA(
                                              cwbDQ_Data      data
                                            , unsigned char  *senderInfo
                                          );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDQ_GetSenderInfoW(
                                              cwbDQ_Data   data
                                            , wchar_t     *senderInfo
                                          );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDQ_GetSenderInfo             cwbDQ_GetSenderInfoW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDQ_GetSenderInfo             cwbDQ_GetSenderInfoA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_GetSysName                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Retrieve the system name used with the cwbDQ_Open API.         */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_QueueHandle queueHandle -input                           */
/*     Handle that was returned by a previous call to the           */
/*     cwbDQ_Open function.  This identifies the AS/400 data        */
/*     queue object.                                                */
/*                                                                  */
/*   char * systemName - output                                     */
/*     Pointer to a buffer where the system name will be written.   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or NULL pointer.                     */
/*   CWBDQ_INVALID_QUEUE_HANDLE - Invalid queue handle.             */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This function requires that you have previously issued         */
/*     cwbDQ_OpenEx() or cwbDQ_Open()                               */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDQ_GetSysName(
                             cwbDQ_QueueHandle   queueHandle,
                             char               *systemName);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDQ_GetSysNameA(
                                   cwbDQ_QueueHandle   queueHandle
                                 , LPSTR               systemName
                                       );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDQ_GetSysNameW(
                                   cwbDQ_QueueHandle   queueHandle
                                 , LPWSTR              systemName
                                       );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDQ_GetSysName                cwbDQ_GetSysNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDQ_GetSysName                cwbDQ_GetSysNameA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_Open                                                     */
/*                                                                  */
/* Purpose:                                                         */
/*   Start a connection to the specified data queue.  This will     */
/*   start a conversation with the AS/400 system.  If the           */
/*   connection is not successful, a non-zero handle will be        */
/*   returned.                                                      */
/*                                                                  */
/*   This API has been provided for compatibility with previous     */
/*   versions of Client Access.  The cwbDQ_OpenEx API should be     */
/*   used in new applications to provide for greater control over   */
/*   system properties and connection sharing.                      */
/*                                                                  */
/* Parameters:                                                      */
/*   const char *queue - input                                      */
/*     Pointer to the data queue name contained in an ASCIIZ string.*/
/*                                                                  */
/*   const char *library - input                                    */
/*     Pointer to the library name contained in an ASCIIZ string.   */
/*     If this pointer is NULL then the library list will be        */
/*     used (set library to "*LIBL").                               */
/*                                                                  */
/*   const char *systemName - input                                 */
/*     Pointer to the system name contained in an ASCIIZ string.    */
/*                                                                  */
/*   cwbDQ_QueueHandle * queueHandle - output                       */
/*     Pointer to a cwbDQ_QueueHandle where the handle will be      */
/*     returned.  This handle should be used in all subsequent      */
/*     calls.                                                       */
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
/*   CWB_COMMUNICATIONS_ERROR - A communications error occurred.    */
/*   CWB_SERVER_PROGRAM_NOT_FOUND - AS/400 application not found.   */
/*   CWB_HOST_NOT_FOUND - AS/400 system inactive or does not exist. */
/*   CWB_COMM_VERSION_ERROR - Data Queues will not run with this    */
/*                            version of communications.            */
/*   CWB_INVALID_POINTER - Bad or null pointer.                     */
/*   CWB_SECURITY_ERROR - a security error has occurred.            */
/*   CWB_LICENSE_ERROR - a license error has occurred.              */
/*   CWB_CONFIG_ERROR - a configuration error has occurred.         */
/*   CWBDQ_BAD_QUEUE_NAME - Queue name is too long.                 */
/*   CWBDQ_BAD_LIBRARY_NAME - library name is too long.             */
/*   CWBDQ_BAD_SYSTEM_NAME - system name is too long.               */
/*   CWBDQ_REJECTED_USER_EXIT - Command rejected by user exit       */
/*                              program.                            */
/*   CWBDQ_USER_EXIT_ERROR - error in user exit program.            */
/*   CWBDQ_LIBRARY_NOT_FOUND - library not found on system.         */
/*   CWBDQ_QUEUE_NOT_FOUND - Queue not found on system.             */
/*   CWBDQ_NO_AUTHORITY - No authority to queue or library.         */
/*   CWBDQ_DAMAGED_QUE - Queue is in unusable state.                */
/*   CWBDQ_CANNOT_CONVERT - Data cannot be converted for this queue.*/
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
unsigned int CWB_ENTRY cwbDQ_Open(
                             const char         *queue,
                             const char         *library,
                             const char         *systemName,
                             cwbDQ_QueueHandle  *queueHandle,
                             cwbSV_ErrHandle     errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDQ_OpenA(
                            LPCSTR               queue,
                            LPCSTR               library,
                            LPCSTR               systemName,
                            cwbDQ_QueueHandle   *queueHandle,
                            cwbSV_ErrHandle      errorHandle);
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDQ_OpenW(
                            LPCWSTR              queue,
                            LPCWSTR              library,
                            LPCWSTR              systemName,
                            cwbDQ_QueueHandle   *queueHandle,
                            cwbSV_ErrHandle      errorHandle);
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDQ_Open                      cwbDQ_OpenW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDQ_Open                      cwbDQ_OpenA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_OpenEx                                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Start a connection to the specified data queue.  This will     */
/*   start a conversation with the AS/400 system.  If the           */
/*   connection is not successful, a non-zero handle will be        */
/*   returned.                                                      */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle sysHandle - input                              */
/*     Handle to a system object.                                   */
/*                                                                  */
/*   const char *queue - input                                      */
/*     Pointer to the data queue name contained in an ASCIIZ string.*/
/*                                                                  */
/*   const char *library - input                                    */
/*     Pointer to the library name contained in an ASCIIZ string.   */
/*     If this pointer is NULL then the library list will be        */
/*     used (set library to "*LIBL").                               */
/*                                                                  */
/*   cwbDQ_QueueHandle * queueHandle - output                       */
/*     Pointer to a cwbDQ_QueueHandle where the handle will be      */
/*     returned.  This handle should be used in all subsequent      */
/*     calls.                                                       */
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
/*   CWB_COMMUNICATIONS_ERROR - A communications error occurred.    */
/*   CWB_SERVER_PROGRAM_NOT_FOUND - AS/400 application not found.   */
/*   CWB_HOST_NOT_FOUND - AS/400 system inactive or does not exist. */
/*   CWB_COMM_VERSION_ERROR - Data Queues will not run with this    */
/*                            version of communications.            */
/*   CWB_INVALID_POINTER - Bad or null pointer.                     */
/*   CWB_SECURITY_ERROR - a security error has occurred.            */
/*   CWB_LICENSE_ERROR - a license error has occurred.              */
/*   CWB_CONFIG_ERROR - a configuration error has occurred.         */
/*   CWBDQ_BAD_QUEUE_NAME - Queue name is too long.                 */
/*   CWBDQ_BAD_LIBRARY_NAME - library name is too long.             */
/*   CWBDQ_BAD_SYSTEM_NAME - system name is too long.               */
/*   CWBDQ_REJECTED_USER_EXIT - Command rejected by user exit       */
/*                              program.                            */
/*   CWBDQ_USER_EXIT_ERROR - error in user exit program.            */
/*   CWBDQ_LIBRARY_NOT_FOUND - library not found on system.         */
/*   CWBDQ_QUEUE_NOT_FOUND - Queue not found on system.             */
/*   CWBDQ_NO_AUTHORITY - No authority to queue or library.         */
/*   CWBDQ_DAMAGED_QUE - Queue is in unusable state.                */
/*   CWBDQ_CANNOT_CONVERT - Data cannot be converted for this queue.*/
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*   CWB_INVALID_HANDLE - Invalid system handle.                    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This function requires that you have previously issued         */
/*     cwbCO_CreateSystem()                                         */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDQ_OpenEx(
                             cwbCO_SysHandle     sysHandle,
                             const char         *queue,
                             const char         *library,
                             cwbDQ_QueueHandle  *queueHandle,
                             cwbSV_ErrHandle     errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDQ_OpenExA(
                            cwbCO_SysHandle      sysHandle,
                            LPCSTR               queue,
                            LPCSTR               library,
                            cwbDQ_QueueHandle   *queueHandle,
                            cwbSV_ErrHandle      errorHandle);
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDQ_OpenExW(
                            cwbCO_SysHandle      sysHandle,
                            LPCWSTR              queue,
                            LPCWSTR              library,
                            cwbDQ_QueueHandle   *queueHandle,
                            cwbSV_ErrHandle      errorHandle);
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDQ_OpenEx                      cwbDQ_OpenExW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDQ_OpenEx                      cwbDQ_OpenExA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_Peek                                                     */
/*                                                                  */
/* Purpose:                                                         */
/*   Read a record from the AS/400 data queue object that is        */
/*   identified by the specified handle.  When a record is peeked   */
/*   from a data queue it remains in the data queue.  You may       */
/*   wait for a record if the data queue is empty by specifying a   */
/*   wait time from 0 to 99,999 or forever (-1).  A wait time of    */
/*   zero will return immediately if there is no data in the data   */
/*   queue.                                                         */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_QueueHandle queueHandle - input                          */
/*     Handle that was returned by a previous call to the           */
/*     cwbDQ_Open API.  This identifies the AS/400 data             */
/*     queue object.                                                */
/*                                                                  */
/*   cwbDQ_Data data - input                                        */
/*     The data object to be read from the AS/400 data queue.       */
/*                                                                  */
/*   signed long waitTime - input                                   */
/*     Length of time in seconds to wait for data, if the data      */
/*     queue is empty.  A wait time of -1 indicates to wait forever.*/
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
/*   CWBDQ_INVALID_TIME - Invalid wait time.                        */
/*   CWBDQ_INVALID_QUEUE_HANDLE - Invalid queue handle.             */
/*   CWBDQ_INVALID_SEARCH - Invalid search order.                   */
/*   CWBDQ_DATA_TRUNCATED - Data truncated.                         */
/*   CWBDQ_TIMED_OUT - Wait time expired and no data returned.      */
/*   CWBDQ_REJECTED_USER_EXIT - Command rejected by user exit       */
/*                              program.                            */
/*   CWBDQ_QUEUE_DESTROYED - Queue was destroyed.                   */
/*   CWBDQ_CANNOT_CONVERT - Unable to convert data.                 */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This function requires that you have previously issued:        */
/*     cwbDQ_Open()                                                 */
/*     cwbDQ_CreateData()                                           */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_Peek(
                             cwbDQ_QueueHandle   queueHandle,
                             cwbDQ_Data          data,
                             signed long         waitTime,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_Read                                                     */
/*                                                                  */
/* Purpose:                                                         */
/*   Read a record from the AS/400 data queue object that is        */
/*   identified by the specified handle.  When a record is read     */
/*   from a data queue it is removed from the data queue.  You may  */
/*   wait for a record if the data queue is empty by specifying a   */
/*   wait time from 0 to 99,999 or forever (-1).  A wait time of    */
/*   zero will return immediately if there is no data in the data   */
/*   queue.                                                         */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_QueueHandle queueHandle - input                          */
/*     Handle that was returned by a previous call to the           */
/*     cwbDQ_Open function.  This identifies the AS/400 data        */
/*     queue object.                                                */
/*                                                                  */
/*   cwbDQ_Data data - input                                        */
/*      The data object to be read from the AS/400 data queue.      */
/*                                                                  */
/*   long waitTime - input                                          */
/*     Length of time in seconds to wait for data, if the data      */
/*     queue is empty.  A wait time of -1 indicates to wait forever.*/
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
/*   CWBDQ_INVALID_TIME - Invalid wait time.                        */
/*   CWBDQ_INVALID_QUEUE_HANDLE - Invalid queue handle.             */
/*   CWBDQ_INVALID_SEARCH - Invalid search order.                   */
/*   CWBDQ_DATA_TRUNCATED - Data truncated.                         */
/*   CWBDQ_TIMED_OUT - Wait time expired and no data returned.      */
/*   CWBDQ_REJECTED_USER_EXIT - Command rejected by user exit       */
/*                              program.                            */
/*   CWBDQ_QUEUE_DESTROYED - Queue was destroyed.                   */
/*   CWBDQ_CANNOT_CONVERT - Unable to convert data.                 */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This function requires that you have previously issued         */
/*     cwbDQ_OpenEx() or cwbDQ_Open()                               */
/*     cwbDQ_CreateData()                                           */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_Read(
                             cwbDQ_QueueHandle   queueHandle,
                             cwbDQ_Data          data,
                             long                waitTime,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_SetAuthority                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the attribute for the authority that other users will have */
/*   to the data queue.                                             */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Attr queueAttributes - input                             */
/*     Handle of the data queue attributes returned by a previous   */
/*     call to cwbDQ_CreateAttr.                                    */
/*                                                                  */
/*   unsigned short authority - input                               */
/*     Authority that other users on the AS/400 system have to      */
/*     access the data queue.  Use one of the defined types for     */
/*     authority:                                                   */
/*         CWBDQ_ALL                                                */
/*         CWBDQ_EXCLUDE                                            */
/*         CWBDQ_CHANGE                                             */
/*         CWBDQ_USE                                                */
/*         CWBDQ_LIBCRTAUT                                          */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBDQ_INVALID_ATTRIBUTE_HANDLE - Invalid attributes handle.    */
/*   CWBDQ_INVALID_AUTHORITY - Invalid queue authority.             */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_SetAuthority(
                             cwbDQ_Attr          queueAttributes,
                             unsigned short      authority);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_SetConvert                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the convert flag.  If the flag is set then all data being  */
/*   written will be converted from PC CCSID (eg ASCII) to host     */
/*   CCSID (eg EBCDIC) and all data being read will be converted    */
/*   from host CCSID (eg EBCDIC) to PC CCSID (eg ASCII).  Default   */
/*   behavior is no conversion of data.                             */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Data data - input                                        */
/*     Handle of the data object that was returned by a previous    */
/*     call to cwbDQ_CreateData.                                    */
/*                                                                  */
/*   cwb_Boolean convert - input                                    */
/*     Flag indicating if data written to and read from the queue   */
/*     will be CCSID converted.                                     */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBDQ_INVALID_DATA_HANDLE - Invalid data handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/*   When sharing Unicode data between Windows and the AS/400, data */
/*   may first be converted to the Windows ANSI code page and then  */
/*   to the AS/400 CCSID; therefore, characters which are not       */
/*   supported by both of these might be replaced by substitute     */
/*   characters.                                                    */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDQ_SetConvert(
                             cwbDQ_Data          data,
                             cwb_Boolean         convert);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDQ_SetConvertA(
                             cwbDQ_Data          data,
                             cwb_Boolean         convert);

#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDQ_SetConvertW(
                             cwbDQ_Data          data,
                             cwb_Boolean         convert);
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDQ_SetConvert                cwbDQ_SetConvertW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDQ_SetConvert                cwbDQ_SetConvertA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_SetData                                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the data and data length attributes of the data object.    */
/*   The default is to have no data with zero length.  This         */
/*   function will make a copy of the data.                         */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Data data - input                                        */
/*     Handle of the data object that was returned by a previous    */
/*     call to cwbDQ_CreateData.                                    */
/*                                                                  */
/*   const unsigned char * dataBuffer - input                       */
/*     Pointer to the data.  The data may contain embedded  NULLS,  */
/*     so it is not an ASCIIZ string.                               */
/*                                                                  */
/*   unsigned long dataLength - input                               */
/*     Length of the data in bytes.                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or null pointer.                     */
/*   CWBDQ_INVALID_DATA_HANDLE - Invalid data handle.               */
/*   CWBDQ_BAD_DATA_LENGTH - Length of data is not correct.         */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use this function if you want to write a small amount of data  */
/*   or you do not want to manage the memory for the data in your   */
/*   application.  Data will be copied and this may affect your     */
/*   application's performance.                                     */
/*                                                                  */
/*   When using the cwbDQ_Write API with a data object with the     */
/*   convert flag set, be certain to set dataLength to the exact    */
/*   size of the data to be converted or cwbDQ_Write may fail with  */
/*   a return code of CWBDQ_CANNOT_CONVERT.                         */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_SetData(
                             cwbDQ_Data            data,
                             const unsigned char  *dataBuffer,
                             unsigned long         dataLength);


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_SetDataAddr                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the data and data length attributes of the data object.    */
/*   The default is to have no data with zero length.  This         */
/*   function will not copy the data.                               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Data data - input                                        */
/*     Handle of the data object that was returned by a previous    */
/*     call to cwbDQ_CreateData.                                    */
/*                                                                  */
/*   const unsigned char * dataBuffer - input                       */
/*     Pointer to the data.  The data may contain embedded  NULLS,  */
/*     so it is not an ASCIIZ string.                               */
/*                                                                  */
/*   unsigned long dataLength - input                               */
/*     Length of the data in bytes.                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or null pointer.                     */
/*   CWBDQ_INVALID_DATA_HANDLE - Invalid data handle.               */
/*   CWBDQ_BAD_DATA_LENGTH - Length of data is not correct.         */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This function is better for large amounts of data, or if you   */
/*   want to manage memory in your application.  Data will not be   */
/*   copied so performance will be improved.                        */
/*                                                                  */
/*   When using the cwbDQ_Write API with a data object with the     */
/*   convert flag set, be certain to set dataLength to the exact    */
/*   size of the data to be converted or cwbDQ_Write may fail with  */
/*   a return code of CWBDQ_CANNOT_CONVERT.                         */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_SetDataAddr(
                             cwbDQ_Data            data,
                             const unsigned char  *dataBuffer,
                             unsigned long         dataLength);


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_SetDesc                                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the attribute for the description of the data queue.       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Attr queueAttributes - input                             */
/*     Handle of the data queue attributes returned by a  previous  */
/*     call to cwbDQ_CreateAttr.                                    */
/*                                                                  */
/*   const char * description - input                               */
/*     Pointer to an ASCIIZ string that contains the  description   */
/*     for the data queue.  The maximum length for the              */
/*     description is 50 characters.                                */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - Bad or null pointer.                     */
/*   CWBDQ_INVALID_ATTRIBUTE_HANDLE - Invalid attributes handle.    */
/*   CWBDQ_INVALID_QUEUE_TITLE - Queue title is too long.           */
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
unsigned int CWB_ENTRY cwbDQ_SetDesc(
                             cwbDQ_Attr          queueAttributes,
                             const char         *description);
#endif   // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDQ_SetDescA(
                                        cwbDQ_Attr       queueAttributes
                                      , LPCSTR           description
                                    );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDQ_SetDescW(
                                        cwbDQ_Attr       queueAttributes
                                      , LPCWSTR          description
                                    );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDQ_SetDesc                   cwbDQ_SetDescW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDQ_SetDesc                   cwbDQ_SetDescA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_SetForceToStorage                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the attribute for whether or not records will be forced to */
/*   auxiliary storage when they are enqueued.                      */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Attr queueAttributes - input                             */
/*     Handle of the data queue attributes returned by a previous   */
/*     call to cwbDQ_CreateAttr.                                    */
/*                                                                  */
/*   cwb_Boolean forceToStorage - input                             */
/*     Boolean indicator of whether or not each record is forced    */
/*     to auxiliary storage when it is enqueued.                    */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBDQ_INVALID_ATTRIBUTE_HANDLE - Invalid attributes handle.    */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_SetForceToStorage(
                             cwbDQ_Attr          queueAttributes,
                             cwb_Boolean         forceToStorage);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_SetKey                                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the key and key length attributes of the data attributes.  */
/*   This is the key that is used for writing data to a keyed data  */
/*   queue.  Along with the search order, this key is also used to  */
/*   read data from a keyed data queue.                             */
/*   The default is to have no key with zero length;  this is the   */
/*   correct value for a non-keyed (LIFO or FIFO) data queue.       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Data data - input                                        */
/*     Handle of the data object that was returned by a previous    */
/*     call to cwbDQ_CreateData.                                    */
/*                                                                  */
/*   const unsigned char * key - input                              */
/*     Pointer to the key.  The key may contain embedded NULLS,     */
/*     so it is not an ASCIIZ string.                               */
/*                                                                  */
/*   unsigned short keyLength - input                               */
/*     Length of the key in bytes.                                  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBDQ_INVALID_DATA_HANDLE - Invalid data handle.               */
/*   CWBDQ_BAD_KEY_LENGTH - Length of key is not correct.           */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_SetKey(
                             cwbDQ_Data            data,
                             const unsigned char  *key,
                             unsigned short        keyLength);


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_SetKeySize                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the attribute for the key size in bytes.                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Attr queueAttributes - input                             */
/*     Handle of the data queue attributes returned by a previous   */
/*     call to cwbDQ_CreateAttr.                                    */
/*                                                                  */
/*   unsigned short keySize - input                                 */
/*     Size in bytes of the key.  This value should be zero if      */
/*     the order is LIFO or FIFO, and between 1 and 256 for KEYED.  */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBDQ_INVALID_KEY_LENGTH - Invalid key length.                 */
/*   CWBDQ_INVALID_ATTRIBUTE_HANDLE - Invalid attributes handle.    */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_SetKeySize(
                             cwbDQ_Attr          queueAttributes,
                             unsigned short      keySize);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_SetMaxRecLen                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the maximum record length for the data queue.              */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Attr queueAttributes - input                             */
/*     Handle of the data queue attributes returned by a  previous  */
/*     call to cwbDQ_CreateAttr.                                    */
/*                                                                  */
/*   unsigned long maxLength - input                                */
/*     Maximum length for a data queue record.  This value must     */
/*     be between 1 and 31744.                                      */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBDQ_INVALID_ATTRIBUTE_HANDLE - Invalid attributes handle.    */
/*   CWBDQ_INVALID_QUEUE_LENGTH - Invalid queue record length.      */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_SetMaxRecLen(
                             cwbDQ_Attr          queueAttributes,
                             unsigned long       maxRecordLength);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_SetOrder                                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the attribute for the queue order.  If the order is        */
/*   CWBDQ_SEQ_LIFO, the last record written is the first record    */
/*   read (Last In First Out).  If the order is CWBDQ_SEQ_FIFO,     */
/*   the first record written is the first record read (First In    */
/*   First Out).  If the order is CWBDQ_SEQ_KEYED, the order in     */
/*   which records are read from the data queue depends on the      */
/*   value of the search order attribute of the data object and     */
/*   the key value specified for the cwbDQ_SetKey API.  If          */
/*   multiple records contain the key which satisfies the search    */
/*   order, a FIFO scheme is used among those records.              */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Attr queueAttributes - input                             */
/*     Handle of the data queue attributes returned by a previous   */
/*     call to cwbDQ_CreateAttr.                                    */
/*                                                                  */
/*   unsigned short order - input                                   */
/*     Order in which new entries will be enqueued.  Use one of     */
/*     the defined types for order:                                 */
/*         CWBDQ_SEQ_LIFO                                           */
/*         CWBDQ_SEQ_FIFO                                           */
/*         CWBDQ_SEQ_KEYED                                          */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBDQ_INVALID_ATTRIBUTE_HANDLE - Invalid attributes handle.    */
/*   CWBDQ_INVALID_ORDER - Invalid queue order.                     */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_SetOrder(
                             cwbDQ_Attr          queueAttributes,
                             unsigned short      order);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_SetSearchOrder                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the search order of the open attributes.  The default is   */
/*   no search order.  If the cwbDQ_SetKey API is called, the       */
/*   search order is changed to equal.  Use this API to set it to   */
/*   something else.  The search order is used when reading or      */
/*   peeking a keyed data queue to identify the relationship        */
/*   between the key of the record to retrieve and the key value    */
/*   specified on the cwbDQ_SetKey API.  If the data queue order    */
/*   attribute is not CWBDQ_SEQ_KEYED this property is ignored.     */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Data data - input                                        */
/*     Handle of the data object that was returned by a previous    */
/*     call to cwbDQ_CreateData.                                    */
/*                                                                  */
/*   unsigned short searchOrder - input                             */
/*     Order to use when reading from a keyed queue.                */
/*     Possible values are:                                         */
/*         CWBDQ_NONE                                               */
/*         CWBDQ_EQUAL                                              */
/*         CWBDQ_NOT_EQUAL                                          */
/*         CWBDQ_GT_OR_EQUAL                                        */
/*         CWBDQ_GREATER                                            */
/*         CWBDQ_LT_OR_EQUAL                                        */
/*         CWBDQ_LESS                                               */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBDQ_INVALID_DATA_HANDLE - Invalid data handle.               */
/*   CWBDQ_INVALID_SEARCH - Invalid search order.                   */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_SetSearchOrder(
                             cwbDQ_Data          data,
                             unsigned short      searchOrder);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_SetSenderID                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the attribute for whether or not information about the     */
/*   sender is kept with each record on the queue.                  */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_Attr queueAttributes - input                             */
/*     Handle of the data queue attributes returned by a previous   */
/*     call to cwbDQ_CreateAttr.                                    */
/*                                                                  */
/*   cwb_Boolean senderID - input                                   */
/*     Boolean indicator of whether or not information about the    */
/*     sender is kept with record on the queue.                     */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBDQ_INVALID_ATTRIBUTE_HANDLE - Invalid attributes handle.    */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_SetSenderID(
                             cwbDQ_Attr          queueAttributes,
                             cwb_Boolean         senderID);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_StartSystem                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Start a connection to the specified AS/400 system.  If the     */
/*   connection is successful, a non-zero handle will be            */
/*   returned.                                                      */
/*                                                                  */
/* Parameters:                                                      */
/*   const char *systemName - input                                 */
/*     Pointer to the system name contained in an ASCIIZ string.    */
/*                                                                  */
/*   cwbDQ_SystemHandle * systemHandle - output                     */
/*     Pointer to a cwbDQ_SystemHandle where the handle will be     */
/*     returned.  This handle should be used in the call            */
/*     cwbDQ_StopSystem to cease the connection to a system created */
/*     with this API.                                               */
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
/*   CWB_COMMUNICATIONS_ERROR - A communications error occurred.    */
/*   CWB_SERVER_PROGRAM_NOT_FOUND - AS/400 application not found.   */
/*   CWB_HOST_NOT_FOUND - AS/400 system inactive or does not exist. */
/*   CWB_COMM_VERSION_ERROR - Data Queues will not run with this    */
/*                            version of communications.            */
/*   CWB_INVALID_POINTER - Bad or null pointer.                     */
/*   CWB_SECURITY_ERROR - a security error has occurred.            */
/*   CWB_LICENSE_ERROR - a license error has occurred.              */
/*   CWB_CONFIG_ERROR - a configuration error has occurred.         */
/*   CWBDQ_BAD_SYSTEM_NAME - system name is too long.               */
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
/*   This API may help improve application performance by           */
/*   maintaining a system, instead of queue based, connection to an */
/*   AS/400 system.  Use this API before calling cwbDQ_Delete,      */
/*   cwbDQ_Create, or cwbDQ_Open, which use the same system, to     */
/*   prevent from unnecessarily starting and stopping a connection  */
/*   to the AS/400.                                                 */
/*                                                                  */
/*   Usage of this API to start a connection to a system is not     */
/*   required, does not effect the functionality of the other       */
/*   connection based APIs and will not interfere in how they are   */
/*   used.                                                          */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDQ_StartSystem(
                             const char         *systemName,
                             cwbDQ_SystemHandle *systemHandle,
                             cwbSV_ErrHandle     errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDQ_StartSystemA(
                                     LPCSTR              systemName
                                   , cwbDQ_SystemHandle  *systemHandle
                                   , cwbSV_ErrHandle     errorHandle
                                 );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDQ_StartSystemW(
                                     LPCWSTR             systemName
                                   , cwbDQ_SystemHandle  *systemHandle
                                   , cwbSV_ErrHandle     errorHandle
                                 );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDQ_StartSystem               cwbDQ_StartSystemW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDQ_StartSystem               cwbDQ_StartSystemA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_StopSystem                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   End the connection with the AS/400 system object that is       */
/*   identified by the specified handle.  This will end the         */
/*   connection to the AS/400 system created with the               */
/*   cwbDQ_StartSystem API.                                         */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_SystemHandle systemHandle - input                        */
/*     Handle that was returned by a previous call to the           */
/*     cwbDQ_StartSystem API.  This identifies the AS/400 system    */
/*     object.                                                      */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWBDQ_INVALID_SYSTEM_HANDLE - Invalid system handle.           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This function requires that you have previously issued:        */
/*     cwbDQ_StartSystem()                                          */
/*                                                                  */
/*   Issuing this call will not terminate queue based connections   */
/*   to the AS/400 which have been opened with cwbDQ_Open, and not  */
/*   yet closed with the cwbDQ_Close API.                           */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_StopSystem(
                             cwbDQ_SystemHandle   systemHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDQ_Write                                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   Write a record to the AS/400 data queue object that is         */
/*   identified by the specified handle.                            */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDQ_QueueHandle queueHandle - input                          */
/*     Handle that was returned by a previous call to the           */
/*     cwbDQ_Open function.  This identifies the AS/400 data        */
/*     queue object.                                                */
/*                                                                  */
/*   cwbDQ_Data data - input                                        */
/*     The data object to be written to the AS/400 data queue.      */
/*                                                                  */
/*   cwb_Boolean commit - input                                     */
/*     This flag has been retired and will be ignored.              */
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
/*   CWBDQ_BAD_DATA_LENGTH - Length of data is not correct.         */
/*   CWBDQ_INVALID_MESSAGE_LENGTH - Invalid message length.         */
/*   CWBDQ_INVALID_QUEUE_HANDLE - Invalid queue handle.             */
/*   CWBDQ_REJECTED_USER_EXIT - Command rejected by user exit       */
/*                              program.                            */
/*   CWBDQ_CANNOT_CONVERT - Unable to convert data.                 */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used. Data */
/*                                        is written with the       */
/*                                        default system replace-   */
/*                                        ment character.           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This function requires that you have previously issued:        */
/*     cwbDQ_Open()                                                 */
/*     cwbDQ_CreateData()                                           */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDQ_Write(
                             cwbDQ_QueueHandle   queueHandle,
                             cwbDQ_Data          data,
                             cwb_Boolean         commit,
                             cwbSV_ErrHandle     errorHandle);



#ifdef __cplusplus
}
#endif

#endif /* _CWBDQ_H_ */
