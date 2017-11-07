// Execute a command remotely

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
 

int IBM_RunCommand(csString &cmd)
{
    int retcode = 0 ; 
    cwbCO_SysHandle system;
    cwbRC_SysHandle request;
    cwbSV_ErrHandle errorHandle ;


    unsigned long errorIndex ;
    char errorText[4096] ;
    unsigned long  errorTextLength ;
    unsigned long  returnLength = 0 ; 
    unsigned long i ; 

    int bStopSys = 0 ; 

    int ret = cwbCO_CreateSystem(gCMSparms.ibmhost, &system) ;
    if (ret != CWB_OK)
        return -1 ; 

    ret = cwbCO_SetUserIDEx(system, gCMSparms.DQusr);
    ret = cwbCO_SetPassword(system, gCMSparms.DQpwd);

    try {
        // Start the system
        if ( (cwbRC_StartSysEx(system, &request)) != CWB_OK )
            throw -2 ; 

        bStopSys = 1 ; 

        char dblibcmd[256] ; 
        char chgplant[256] ; 
        sprintf(dblibcmd, "CHGCURLIB %s", gCMSparms.dbname) ; 
        sprintf(chgplant, "CHGPLNT %s", gCMSparms.plantID) ; 
        
        // Call the command to create a library
        cwbSV_CreateErrHandle(&errorHandle) ; 
        ret = cwbRC_RunCmd(request, "ADDLIBLE CMSPD",       errorHandle) ;
        ret = cwbRC_RunCmd(request, "ADDLIBLE CMSSYSTEM",   errorHandle) ;
        ret = cwbRC_RunCmd(request, "ADDLIBLE CMSMAIN",     errorHandle) ;
        ret = cwbRC_RunCmd(request, "ADDLIBLE CMSINV",      errorHandle) ;
        ret = cwbRC_RunCmd(request, "ADDLIBLE CMSNOE",      errorHandle) ;
        ret = cwbRC_RunCmd(request, dblibcmd, errorHandle) ;
        ret = cwbRC_RunCmd(request, chgplant, errorHandle) ;

        ret = cwbRC_RunCmd(request, cmd.c_str(), errorHandle) ;

        errorTextLength = 4090 ; 
        ret = cwbSV_GetErrCount(errorHandle, &errorIndex) ; 
        for (i=0; i < errorIndex; i++)
        {
            ret = cwbSV_GetErrTextIndexed(errorHandle,
                                i, errorText, errorTextLength,
                                &returnLength); 
        }

        if (ret != CWB_OK)
            throw -3 ;

        bStopSys = 0 ; 
        // Stop the system
        if ( cwbRC_StopSys(request) != CWB_OK )
            throw -4 ;
    }
    catch (int errnum)
    {
        if (bStopSys)
        if ( cwbCO_DeleteSystem(system) != CWB_OK )
            return -10 ;
        return errnum ; 
    }

    // Delete the system object
    if ( cwbCO_DeleteSystem(system) != CWB_OK )
        retcode = -5 ;

    return retcode ; 
}
