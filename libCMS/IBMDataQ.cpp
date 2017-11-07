// IBMDataQ.cpp - interface to IBM's iSeries data queue. 

// #include <ugutils.h>
#include "CMSBOMRTE.h"

#ifdef UNICODE
   #define _UNICODE
#endif
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <errno.h>
#include <tchar.h>
 


// The isys and qhandle should be maintained by the caller until processing
// is finished and then closed. 
int IBM_OpenDataQ(cwbCO_SysHandle &isys, cwbDQ_QueueHandle &qhandle, char *qname)
{
    isys = 0 ; 
    int ret = cwbCO_CreateSystem(gCMSparms.ibmhost, &isys) ;

    if (ret != CWB_OK)
    {   // Log error
        return -1 ; 
    }

    ret = cwbCO_SetUserIDEx(isys, gCMSparms.DQusr);
    ret = cwbCO_SetPassword(isys, gCMSparms.DQpwd);

    cwbDQ_Attr          qattrs ; 
    cwbSV_ErrHandle     herr = 0 ; 

    // Create an attribute object
    if ( (qattrs = cwbDQ_CreateAttr()) == 0 )
        return -2 ;

    // Set the maximum record length to 100
    if ( cwbDQ_SetMaxRecLen(qattrs, 580) != 0 )
        return -3 ;

    // Set the order to First-In-First-Out
    if (cwbDQ_SetOrder(qattrs, CWBDQ_SEQ_FIFO) != 0 )
        return-4 ;

    int retcode ; 
    retcode = cwbDQ_CreateEx(isys, 
                    qname,   // SF223DQI
                    gCMSparms.dbname,   // EXCOPHASE1
                    qattrs, herr) ;
    if (retcode != 0 && retcode != CWBDQ_QUEUE_EXISTS)
    {   
        char msg[8192] ;
        unsigned long retlen = 0 ;
        msg[0] = 0 ;
        unsigned int errcode = cwbSV_GetErrText(herr, msg, 8000, &retlen);
        printf("ERROR: %d\n", retcode) ;
        printf("  MSG: %s\n", msg) ;
        return -10 ;
    }

    // Don;'t need the attribute definition anymore. 
    if ( cwbDQ_DeleteAttr(qattrs) != 0 )
        return -11 ;


    retcode = cwbDQ_OpenEx(isys, 
                    gCMSparms.inputQ,   // SF223DQI
                    gCMSparms.dbname,   // EXCOPHASE1
                    &qhandle, herr) ;

    if (retcode != 0)
    {
        return -20 ;
    }

    return 0 ; 
}

// Returns 0 if no errors, else error falgs
int IBM_CloseDataQ(cwbCO_SysHandle &isys, cwbDQ_QueueHandle &qhandle)
{
    // Close the data queue
    int retcode = 0 ; 
    if ( cwbDQ_Close(qhandle) != 0 )
        retcode |= 0x01 ;
    cwbCO_DeleteSystem(isys) ; 

    return retcode ; 
}



/**********************************************************************/
// Send event with a pre-defined data Q handle. 
int CMS_SendEventToQ(cwbDQ_QueueHandle qhandle, EventData &evd)
{
    
    // Create a data object
    cwbDQ_Data qData ; 
    if ( (qData = cwbDQ_CreateData()) == 0 )
        return -1 ;

    // Set the data length and the data
    cwb_Boolean cvrt = 1 ; 
    if (cwbDQ_SetConvert(qData, cvrt) != 0)
        return -6 ; 

    if ( cwbDQ_SetData(qData, (unsigned char *)evd.eventData, evd.dataLength) != 0 )
        return -2 ;

    // Write the data to the data queue
    if ( cwbDQ_Write(qhandle, qData, CWB_TRUE, NULL) != 0 )
        return -3 ;

    // Delete the data object
    if ( cwbDQ_DeleteData(qData) != 0 )
        return -4 ;

    return 0 ; 
}


int CMS_SendEventToQ(EventData &evd, int *errcode)
{
    cwbCO_SysHandle isys = 0 ; 
    int ret = cwbCO_CreateSystem(gCMSparms.ibmhost, &isys) ;

    char logbuf[1024] ; 
    memcpy(logbuf, evd.eventData, 580) ; 
    logbuf[575] = 0 ; 
    logbuf[576] = 0 ; 

    if (ret != CWB_OK)
    {   // Log error
        return -1 ; 
    }

    ret = cwbCO_SetUserIDEx(isys, gCMSparms.DQusr);
    ret = cwbCO_SetPassword(isys, gCMSparms.DQpwd);

    cwbDQ_Attr          qattrs ; 
    cwbSV_ErrHandle     herr = 0 ; 

    // Create an attribute object
    if ( (qattrs = cwbDQ_CreateAttr()) == 0 )
    {
        if (errcode)
            *errcode = 1 ; 
        return -2 ;
    }

    // Set the maximum record length to 100
    if ( cwbDQ_SetMaxRecLen(qattrs, 580) != 0 )
    {
        if (errcode)
            *errcode = 1 ; 
        return -3 ;
    }

    // Set the order to First-In-First-Out
    if (cwbDQ_SetOrder(qattrs, CWBDQ_SEQ_FIFO) != 0 )
    {
        if (errcode)
            *errcode = 1 ; 
        return-4 ;
    }

    int retcode ; 
    retcode = cwbDQ_CreateEx(isys, 
                    gCMSparms.inputQ,   // SF223DQI
                    gCMSparms.dbname,   // EXCOPHASE1
                    qattrs, herr) ;
    if (retcode != 0 && retcode != CWBDQ_QUEUE_EXISTS)
    {   
        char msg[8192] ;
        unsigned long retlen = 0 ;
        msg[0] = 0 ;
        unsigned int errcode = cwbSV_GetErrText(herr, msg, 8000, &retlen);
        printf("ERROR: %d\n", retcode) ;
        printf("  MSG: %s\n", msg) ;
        return -10 ;
    }

    // Don;'t need the attribute definition anymore. 
    if ( cwbDQ_DeleteAttr(qattrs) != 0 )
        return -11 ;

    cwbDQ_QueueHandle qhandle ;

    retcode = cwbDQ_OpenEx(isys, 
                    gCMSparms.inputQ,   // SF223DQI
                    gCMSparms.dbname,   // EXCOPHASE1
                    &qhandle, herr) ;

    if (retcode != 0)
    {
        if (errcode)
            *errcode = retcode ; 
        return -20 ;
    }
    
    // Create a data object
    cwbDQ_Data qData ; 
    if ( (qData = cwbDQ_CreateData()) == 0 )
    {
        return -1 ;
    }

    // Set the data length and the data
    cwb_Boolean cvrt = 1 ; 
    unsigned int retval = 0 ; 
    if ((retval = cwbDQ_SetConvert(qData, cvrt)) != 0)
    {
        if (errcode)
            *errcode = retval ; 
        return -6 ; 
    }

    if ( (retval = cwbDQ_SetData(qData, (unsigned char *)evd.eventData, evd.dataLength)) != 0 )
    {
        if (errcode)
            *errcode = retval ; 
        return -2 ;
    }

    // Write the data to the data queue 
    if ( (retval = cwbDQ_Write(qhandle, qData, CWB_TRUE, NULL)) != 0 )
    {
        // CWBDQ_BAD_DATA_LENGTH  CWB_OK CWBDQ_INVALID_MESSAGE_LENGTH 
        // CWBDQ_INVALID_QUEUE_HANDLE  CWBDQ_REJECTED_USER_EXIT 
        // CWBDQ_CANNOT_CONVERT = 5999+29 = 6028
        if (errcode)
            *errcode = retval ; 
        return -3 ; 
    }

    // Log the data Q send string
    fprintf(gCMSparms.pevp->fpLOG, "DQ: JOBN=%s SEQ=%s EMP=%d: %s\n", 
                evd.jobnum, evd.seqnum, evd.empnum, logbuf) ; 
    fflush(gCMSparms.pevp->fpLOG) ; 

    // Delete the data object
    if ( (retval = cwbDQ_DeleteData(qData)) != 0 )
    {
        if (errcode)
            *errcode = retval ; 
        return -4 ;
    }

    // Close the data queue
    if ( (retval = cwbDQ_Close(qhandle)) != 0 )
    {
        if (errcode)
            *errcode = retval ; 
        return -5 ;
    }

    cwbCO_DeleteSystem(isys) ; 

    return 0 ; 
}

void TestDataQueue()
{
    cwbDQ_Attr queueAttributes;
    cwbDQ_QueueHandle queueHandle;
    cwbDQ_Data queueData;

    // Create an attribute object
    if ( (queueAttributes = cwbDQ_CreateAttr()) == 0 )
        return;

    // Set the maximum record length to 100
    if ( cwbDQ_SetMaxRecLen(queueAttributes,
        100) != 0 )
        return;

    // Set the order to First-In-First-Out
    if (cwbDQ_SetOrder(queueAttributes, CWBDQ_SEQ_FIFO) != 0 )
        return;

    // Create the data queue DTAQ in library QGPL on system SYS1

    if ( cwbDQ_Create(_TEXT("DTAQ"),
        _TEXT("QGPL"),
        _TEXT("SYSNAMEXXX"),
        queueAttributes,
        NULL) != 0 )
        return;

   // Delete the attributes
   if ( cwbDQ_DeleteAttr( queueAttributes ) != 0 )
      return;
 
   // Open the data queue
   if ( cwbDQ_Open(_TEXT("DTAQ"),
                   _TEXT("QGPL"),
                   _TEXT("SYSNAMEXXX"),
                   &queueHandle,
                   NULL) != 0 )
 
       return;
 
   // Create a data object
   if ( (queueData = cwbDQ_CreateData()) == 0 )
      return;
 
   // Set the data length and the data
   if ( cwbDQ_SetData(queueData, (unsigned char*)"Test Data!", 10) != 0 )
      return;
 
   // Write the data to the data queue
   if ( cwbDQ_Write(queueHandle, queueData, CWB_TRUE, NULL) != 0 )
      return;
 
   // Delete the data object
   if ( cwbDQ_DeleteData(queueData) != 0 )
      return;
 
   // Close the data queue
   if ( cwbDQ_Close(queueHandle) != 0 )
      return;
}