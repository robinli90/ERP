// BaalV2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <list>
#include <CSStdlibs/cslib.h>

#include <libCMS/CMSBOMRTE.h>
// #include "SQLDatabase.h"
// #include "SQLRecordset.h"

#include "BaalV2.h"

int ProcessArgs(int argc, char* argv[]) ; 

void printusage() 
{
printf(
"Usage: \n"
" baal  -c cfgfile [-d <monitor_directory>] [-r] [-s] [--tship] [-l <logfile>]\n"
"       [-XD] [-t <taskfiles>] [-n] [-m movedir] [--RTER] [--XDOWN] [--SSEMP]\n"
"       [--BATCH]\n"
"  --BATCH turns on batch mode processing within CMS. No data is sent through\n"
"     the data queue. Instead, all data is uploaded through batch files for\n"
"     processing through the BatchUPD program. When BATCH is set all data is.\n"
"     written to the EXCOTASK table within the active CMS database.\n"
"  -d the path of the directory to monitor for task files\n"
"  -t file name where the processed task strings should be archived to.\n"
"     All the input task data is saved to a file which is built from the\n"
"     parameter given. The full path and the prefix of the file name should be\n"
"     defined. Thus 'c:\\logs\tasks' will expand to a series of file names with\n"
"     the following format:\n"
"         c:\\logs\\tasks_YYYY-MM-DD.log\n"
"  -l the full path name and prefix of the log file to output status information\n"   
"     to this behaves in the same way that the -t archive works.\n"
"  -m instead of deleting the task file, move to this directory after processing\n"
"     The file will have the date and time prepended to the original task file\n"
"     name in this case. The pattern is YYYYMMDD_HHMMSS_<original_file_name>\n"
"  -n no echo, disables echoing of status information to the command window\n"
"     (this is not fully implemented correctly, there are likely some debug\n"
"      strings which will still be output even if this is turned on. These\n"
"      will be fixed as the program stabilizes)\n"
"  -c the full path name to the file that defines the database connection\n"
"  -r enables readback verification within decade\n" 
"  -v enables readback verification within Solarsoft (this is now forced ON)\n" 
"     Data Queue processing within Solarsoft has proved to be very unreliable\n"
"     and thus the logic is designed in a way that means it is now impossible\n"
"     to turn off readback verification on Solarsoft.\n"
"  --tship track even after shipped and invoiced\n"
"  --RTER routing resource to be read from CJOBDR and ignore the StationMap.txt\n"
"    resource definition. This means that the actual resource will not be \n"
"    tracked in Solarsoft. A warning is logged to indicate the resource\n"
"    discrepancy however.\n"
"  --XDOWN disable sending the 10100 resource down events\n"
"  --SSEMP turn on the 20000/20009 event pair data\n"
"    Turning this on can cause problems when attempting to post job data\n"
"    each day since any error will cause a labour error exception in the \n"
"    posting process.\n"
"  -XD do not track to Decade. Note that the taskMap.txt file can also be used\n"
"    to control which data base various tasks should be sent to. This is a\n"
"    global flag to completely disable decade d_task writes.\n"
"  -XS do not track to Solarsoft. Note that the taskMap.txt file can also be used\n"
"    to control which data base various tasks should be sent to. This is a\n"
"    global flag to completely disable Solarsoft data queue output.\n"
"  If the -d parameter is not specified then the current working directory\n"
"  is used. If the -l log file is not specified then no logging is generated,\n"
"  and similarily if the -t parameter is not specified then no task lines\n"
"  are achived. For the log and archive files, the date is automatically appended\n"
"  to the filename plus a .log extension. Every day a new archive and\n"
"  log file will be created.\n\n"
"  If the CMSIP or ODBC are null then no CMS tracking will take place\n\n"
"  IMPORTANT: all of the parameters are case sensitive.\n\n"
"  The cfgfile must follow this example:\n\n"
"     # Lines starting with hashes (pound sign) are ignored as comments\n"
"     # The parameter names in front of the '=' sign are case sensitive.\n"
"     DECodbc=<odbc name>\n"
"     DECusr=<username>\n"
"     DECpwd=<password>\n"
"     CMSIP=<iSeries Machine IP>   example: 10.0.0.35\n"
"     CMSodbc=<CMS ODBC name>\n"
"     CMSDBusr=<username>\n"
"     CMSDBpwd=<password>\n"
"     CMSQusr=<username>\n"
"     CMSQpwd=<password>\n"
"     CMSInQ=SF223DQI\n"
"     CMSOutQ=SF223DQO\n"
"     CMSDBName=<database name>  example: EXCOPHASE1\n"
"     CMSPlant=<plantid>    For Markham is 001 for example, this is a string\n\n"
" If the -c parameter is not defined and no config file is specified, then\n"
" no database access to the old Decade system, and no data queue output to\n"
" to CMS will occur.\n\n"
" To stop the processing of records cleanly type CTRL+C with the cmd window\n"
" active (click on command window and then type CTRL+C).Or make sure there\n"
" are no records in the process directory wait for 5 seconds and then kill\n"
" the process. This way no records will be partially processed.\n"
) ;

}

// Function prototypes and data definitions

void BuildDateName(char *nameouttmpname, char *basein) ; 
void DoDataQVerification() ;
int LoadEmployeeTags() ;


int noDecadeTracking = 0 ; 
int noCMSTracking = 0 ; 


// --------------------------------------------------------------------------
// ------------------------ MAIN PROGRAM START ------------------------------
// --------------------------------------------------------------------------

BaalFileProcessor bfp ; 

int main(int argc, char* argv[])
{
	

    gParms.evp.fpLOG = 0 ; 
    gCMSparms.pevp = &gParms.evp ; 


    // Loop until CTRL+C
    printf("Starting....\n") ; 
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE) ; 

    SetConsoleMode(hStdin, 0) ; 
    // SetConsoleCtrlHandler( (PHANDLER_ROUTINE)CtrlHandler, TRUE ).

    if (ProcessArgs(argc, argv))
    {
        printusage() ; 
        return 0 ; // error on startup
    }

    SetCurrentDirectory(gParms.taskdir) ;

    CCMSDatabase m_sql ;
    try {
        m_sql.OpenEx(gParms.odbcName, gParms.user, gParms.pwd) ;
    }
    catch (...)
    {
        printf("Error connecting to Decade database ODBC=%s\n", gParms.odbcName) ;
        exit(1) ; 
    }

    FileRefList frl ; 

    FILE *fparchive = 0 ; 
    FILE *fpsql = 0 ; 
    FILE *fplog = 0 ;

    static char curArchive[512] ; 
    curArchive[0] = 0 ; 
    if (gParms.taskarchive[0])
    {
        BuildDateName(curArchive, gParms.taskarchive) ; 
        fparchive = fopen(curArchive, "ab") ; 
    }

    static char curLog[512] ; 
    curLog[0] = 0 ; 
    if (gParms.logfile[0]) 
    {
        BuildDateName(curLog, gParms.logfile) ; 
        fplog = fopen(curLog, "ab") ; 
        gParms.evp.fpLOG = fplog ; 
        CDateTime dt ; 
        dt.SetNow() ; 
        char dtstr[64] ; 
        dt.FormatDateTimeSecs(dtstr, 0) ; 
        LogError("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+- \r\n") ; 
        LogError("OPENED LOG:") ; LogError(dtstr) ; LogError("\r\n") ; 
        LogError("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+- \r\n") ; 
    }

    static char curSQLLog[512] ; 
    curSQLLog[0] = 0 ; 
    if (gParms.sqllogname[0]) 
    {
        BuildDateName(curSQLLog, gParms.sqllogname) ; 
        fpsql = fopen(curSQLLog, "ab") ; 
    }

    gCMSparms.status = 0 ; 

    strcpy(gCMSparms.ibmhost, gParms.CMSIP) ; 
    strcpy(gCMSparms.dbname,  gParms.CMSDBName) ; 
    strcpy(gCMSparms.odbc,    gParms.CMSodbc) ; 
    strcpy(gCMSparms.dbusr,   gParms.CMSDBusr) ; 
    strcpy(gCMSparms.dbpwd,   gParms.CMSDBpwd) ; 
    strcpy(gCMSparms.DQpwd,   gParms.CMSQpwd) ; 
    strcpy(gCMSparms.DQusr,   gParms.CMSQusr) ; 
    strcpy(gCMSparms.inputQ,  gParms.CMSInQ) ; 
    strcpy(gCMSparms.outputQ, gParms.CMSOutQ) ; 
    strcpy(gCMSparms.plantID, gParms.CMSPlant) ; 

    if (gCMSparms.ibmhost[0] == 0 || gCMSparms.odbc[0] == 0)
        gCMSparms.status = 0x80000000 ; 
        
    if (!gParms.evp.bBatchMode && !(gCMSparms.status & 0x80000000))
    {
       ///////* if (IBM_OpenDataQ(gParms.isys, gParms.qhandle, gCMSparms.inputQ))
       ////// {
       //////     char *pmsg =
       //////             "ERROR: error opening a data queue connection to the iSeries,\n"
       //////             "   check your config file parameter settings for the IBM iSeries\n"
       //////             "   data Q and try running the program again. The decade processing\n"
       //////             "   will still process normally even with this error.\n" ; 

       //////     if (fplog)
       //////     {
       //////         fprintf(fplog, pmsg) ; 
       //////         fflush(fplog) ; 
       //////     }
       //////     else
       //////     {
       //////         printf(pmsg) ; 
       //////     }
       ////// }*/
    }



    strcpy(gParms.evp.m_db.odbcName, gParms.CMSodbc) ; 
    strcpy(gParms.evp.m_db.userName, gParms.CMSDBusr) ; 
    strcpy(gParms.evp.m_db.password, gParms.CMSDBpwd) ; 
    strcpy(gParms.evp.m_db.dbname,   gParms.CMSDBName) ; 
    strcpy(gParms.evp.plantID,       gParms.CMSPlant) ; 

    ////////if (!gParms.evp.OpenDatabase())
    ////////{
    ////////    printf ("Error opening connection to CMS database, check IBM parameters and ODBC setup\n") ; 
    ////////    return -1 ; // error out. 
    ////////}

    gParms.evp.LoadMaps(gParms.evp.plantID) ; 

    printf("Processing....\n") ; 
    static char tmpname[512] ; 

    // *****************************************************************
    //  IBM DATA QUEUE HANDLING

    cwbCO_SysHandle isysread = 0 ; 
    cwbDQ_QueueHandle hqread = 0 ; 
    cwbSV_ErrHandle     hErr = 0 ; 
    cwbDQ_Data qData = 0; 
    unsigned char readBuf[4096] ; 
    int readBufLen = 4000 ; 

    ////////if (!gParms.evp.bBatchMode)
    ////////{
    ////////    IBM_OpenDataQ(isysread, hqread, gCMSparms.outputQ) ;

    ////////    // Create a data object
    ////////    if ( (qData = cwbDQ_CreateData()) == 0 )
    ////////    {   // Error occured
    ////////        IBM_CloseDataQ(isysread, hqread) ; 
    ////////        isysread = 0 ; 
    ////////        hqread = 0 ; 
    ////////    }

    ////////    // Set the data length and the data
    ////////    cwb_Boolean cvrt = 1 ; 
    ////////    unsigned int retval = 0 ; 
    ////////    if ((retval = cwbDQ_SetConvert(qData, cvrt)) != CWB_OK)
    ////////    {   // Error occured
    ////////        IBM_CloseDataQ(isysread, hqread) ; 
    ////////        isysread = 0 ; 
    ////////        hqread = 0 ; 
    ////////    }

    ////////    if ( cwbDQ_SetData(qData, readBuf, readBufLen) != CWB_OK )
    ////////    {   // Error occured
    ////////        IBM_CloseDataQ(isysread, hqread) ; 
    ////////        isysread = 0 ; 
    ////////        hqread = 0 ; 
    ////////    }
    ////////}

    // *****************************************************************


 ///////*   time(&gParms.evp.idseed) ; 
 //////   gParms.evp.bUseCJOBDRRes = gParms.bUseRoutingResource ? true : false ; 
 //////   if (gParms.bVerifySolarsoft)
 //////       gCMSparms.InitVerification() ; */

    time_t lastEmpRead = 0 ; 


    // cwbDQ_GetRetDataLen
    // cwbDQ_Read

    while (true)
    {
        time_t curTime  ; 
        time(&curTime) ; 
        ////////if ((lastEmpRead + 600) < curTime)
        ////////{
        ////////    // Make sure the times on the machines match exactly.
        ////////    system("net time \\\\10.0.0.35 /set /y") ; 
        ////////    LoadEmployeeTags() ; 
        ////////    lastEmpRead = curTime ; 
        ////////}

        if (kbhit()) 
        {
            if (_getch() == 0x03)
                break ; 
        }

        // ----------------------- Cycle the output files ----------------------
        if (gParms.taskarchive[0])
        {
            BuildDateName(tmpname, gParms.taskarchive) ; 
            if (strcmp(curArchive, tmpname) != 0)
            {
                fclose(fparchive) ; 
                strcpy(curArchive, tmpname) ; 
                fparchive = fopen(curArchive, "ab") ; 
            }
        }

        if (gParms.logfile[0])
        {
            BuildDateName(tmpname, gParms.logfile) ; 
            if (strcmp(curLog, tmpname) != 0)
            {
                fclose(fplog) ; 
                strcpy(curLog, tmpname) ; 
                fplog = fopen(curLog, "ab") ;
                gParms.evp.fpLOG = fplog ; 
            }
        }

        if (gParms.sqllogname[0])
        {
            BuildDateName(tmpname, gParms.sqllogname) ; 
            if (strcmp(curSQLLog, tmpname) != 0)
            {
                fclose(fpsql) ; 
                strcpy(curSQLLog, tmpname) ; 
                fpsql = fopen(curSQLLog, "ab") ; 
            }
        }

        // ----------------------- End cycle the output files ----------------------


        // *********************** READ DATA Q *********************************
        // Dump any data response from the IBM 
        hErr = 0 ; 
        if (!noCMSTracking && !gParms.evp.bBatchMode)
        {
            int retcode = cwbDQ_Read(hqread, qData, 0, hErr) ;
            // CWBDQ_CANNOT_CONVERT  CWBDQ_QUEUE_DESTROYED
            // CWB_OK  CWBDQ_INVALID_TIME CWBDQ_INVALID_QUEUE_HANDLE 
            // CWBDQ_INVALID_SEARCH  CWBDQ_DATA_TRUNCATED CWBDQ_TIMED_OUT 
            //  CWBDQ_REJECTED_USER_EXIT
            if (retcode == CWB_OK)
            {   // Then keep checking
                unsigned long dlen = 0 ; 

                if (cwbDQ_GetRetDataLen(qData, &dlen) == CWB_OK)
                {
                    if (dlen > 4000)
                    {   
                        unsigned char *preadbuf = new unsigned char[dlen+2] ; 
                        if (cwbDQ_GetData(qData, preadbuf) == CWB_OK)
                        {
                            preadbuf[dlen] = 0 ; 
                            if (fplog)
                            {
                                fprintf(fplog, "SF223DQO: %s\r\n", preadbuf) ; 
                                fflush(fplog) ; 
                            }
                            printf("SF223DQO: %s\n", preadbuf) ; 

                        }
                        delete[] preadbuf ; 
                    }
                    else
                    {
                        if (cwbDQ_GetData(qData, readBuf) == CWB_OK)
                        {
                            readBuf[dlen] = 0 ; 
                            if (fplog)
                            {
                                fprintf(fplog, "SF223DQO: %s\r\n", readBuf) ; 
                                fflush(fplog) ; 
                            }
                            printf("SF223DQO: %s\n", readBuf) ; 

                        }
                    }
                }
            }
        }

        // *********************** END READ DATA Q *********************************


        // *************************************************************************
        // ******************** SOLARSOFT VERIFICATION *****************************               
        // *************************************************************************
        // Read back and verify that the data queue actually processed the record 
        // correctly
        // if (gCMSparms.bDoVerification) - no longer an option we have to do this
        if (!noCMSTracking && !gParms.evp.bBatchMode)
            DoDataQVerification() ;
        // *************************************************************************

        // grab the next file from the queue - if the queue is empty
	// refill it from the tasks directory

        if(frl.empty()) 
        {   // refill queue from tasks directory
            WIN32_FIND_DATA findData ; 
            HANDLE hFind = FindFirstFile("*", &findData) ; 
            
            if (hFind == INVALID_HANDLE_VALUE)
            {
                if (fplog) 
                {
                    fprintf(fplog, "Invalid File Handle. Get Last Error reports %d\n", GetLastError ()) ;
                    fflush(fplog) ; 
                }
            } 
            else 
            {
                FileRef fref ; 

                do {                  
                    if (!CS_IsDots(findData.cFileName) && 
                        !(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                    {
                        strcpy(fref.filename, findData.cFileName) ;
                        DWORD remainder ; 
                        fref.flsystime = FileTimeToUnixTime(&findData.ftLastWriteTime, &remainder) ;
                        time(&(fref.fltime)) ; 
                        frl.push_back(fref) ; 
                    }
                } while (FindNextFile(hFind, &findData)) ;

                FindClose(hFind);
            }
        }
        
        // only proceed if there are files available to be processed
        if(!frl.empty()) 
        {
            int nResult ;
            
            // get files and remove from queue
            time(&curTime) ; 

            FileRefListItr ifr ; 

            while (!frl.empty()) 
            {
                ifr = frl.begin() ; 

                csString fileName = ifr->filename ; 
                time_t readtime = ifr->fltime ; 
                time_t filetime = ifr->flsystime ; 

                // Only process files after they have been waiting in the directory 
                // for 3 seconds to make sure that the remote app has finished 
                // writing to the file. 
                if (curTime - readtime > 3)
                {   // Then process the file. 
                    frl.pop_front() ; // delete from the front of the list
                
                    // process and delete task file
                    bfp.fplog = fplog ; 
                    bfp.fpsql = fpsql ; 
                    bfp.fparchive = fparchive ; 

                    if (gParms.evp.bBatchMode)
                    {   // batch mode processing. 
                        bfp.pdb = &(gParms.evp.m_db) ; 
                        nResult = bfp.ProcessFileBatch(fileName, filetime) ;
                    }
                    else
                    {   // data queue based processing
                        bfp.pdb = &m_sql ; 
                        nResult = bfp.ProcessFile(fileName, filetime) ;
                    }
                }
                else
                {   // Done working through the list of records that are old enough
                    Sleep(2000) ; // wait two seconds and continue
                    break ; 

                }
            }
        }
        else
        {
            Sleep(200) ; // wait 200 milliseconds and continue
            if (fpsql) 
                fflush(fpsql) ; 
        }
    }

    if (isysread)
        IBM_CloseDataQ(isysread, hqread) ; 

    if (fparchive)
        fclose(fparchive) ; 
    if (fplog)
        fclose(fplog) ; 
    if (fpsql)
        fclose(fpsql) ; 

    return 0;
}


RunParms::RunParms()
{
    plantMode = PLANT_EXCO ; 
    odbcName[0] = 0 ; 
    user[0] = 0 ; 
    pwd[0] = 0 ; 
    logfile[0] = 0 ; 
    taskdir[0] = 0 ; 
    taskarchive[0] = 0 ;
    bNoEcho = false ; 
    bVerification = false ; 
    bTrackAfterShipped = false ; 
    cfgfile[0] = 0 ; 
    sqllogname[0] = 0 ; 

    bVerifySolarsoft = false ; 
    bUseRoutingResource = 0 ; 

    soMaxCount = 0 ; 
    nLastMax = 0 ; 
    nLastPrefix = 0 ; 

    moveToDir[0] = 0 ; 

    memset(&isys, 0, sizeof(cwbCO_SysHandle)) ; 
    memset(&qhandle, 0, sizeof(cwbDQ_QueueHandle)) ; 
}


int LoadEmployeeTags()
{
    char qry[512] ; 
 
    // so we can directly reference the records from SFTX
    _snprintf(qry, 500, "SELECT ZMTAG# FROM %s.TAZM", gCMSparms.dbname) ; 

    try
    {
        CSQLRecordset rs(gParms.evp.m_db) ; 
        rs << qry ; 
        rs.SQLExec();
        while (rs.SQLFetch())
        {
            int empnum = atoi(rs.SQLGetData(1).c_str()) ; 
            gParms.evp.empMap[empnum] = empnum ; 
        }
    }
   catch (CSQLException* e)
    {
        if (bfp.fplog)
        {
            fprintf(bfp.fplog, "SQL error %d loading employee tags: %s\r\n",
                        (int)e->m_nRetCode, e->m_strError.c_str()) ;
            fflush(bfp.fplog) ; 
        }
    }

    return (int)gParms.evp.empMap.size() ; 
 }


//! This is the single definition for all CMS connections
CMSConnectionParms gCMSparms ; 

// Define a global run parameter set
RunParms gParms ; 

int LoadConfigFile()
{
    FILE *fp = fopen(gParms.cfgfile, "rt") ; 
    if (!fp)
        return -1 ; 

    int retcode = 0; 
    char buf[1024] ; 
    while (fgets(buf, 1024, fp))
    {
        csString line(buf) ; 
        line.Trim() ; 

        if (line[0] == '#' || line.size() == 0)
            continue ; 

        csString name, val ; 
        name = line.NextToken("=", 0) ; 
        val = line.NextToken("=") ; 

        name.Trim() ; 
        val.Trim() ; 
        if (name == "DECodbc")
        {
            CS_strmaxcpy(gParms.odbcName, val.c_str(), 60) ; 
        }
        else if(name == "DECusr") 
        {
            CS_strmaxcpy(gParms.user, val.c_str(), 60) ; 
        }
        else if(name == "DECpwd") 
        {
            CS_strmaxcpy(gParms.pwd, val.c_str(), 60) ; 
        }
        else if(name == "CMSIP") 
        {
            CS_strmaxcpy(gParms.CMSIP, val.c_str(), 60) ; 
        }
        else if(name == "CMSodbc") 
        {
            CS_strmaxcpy(gParms.CMSodbc, val.c_str(), 60) ; 
        }
        else if(name == "CMSDBusr") 
        {
            CS_strmaxcpy(gParms.CMSDBusr, val.c_str(), 60) ; 
        }
        else if(name == "CMSDBpwd") 
        {
            CS_strmaxcpy(gParms.CMSDBpwd, val.c_str(), 60) ; 
        }
        else if(name == "CMSQusr") 
        {
            CS_strmaxcpy(gParms.CMSQusr, val.c_str(), 60) ; 
        }
        else if(name == "CMSQpwd") 
        {
            CS_strmaxcpy(gParms.CMSQpwd, val.c_str(), 60) ; 
        }
        else if(name == "CMSInQ") 
        {
            CS_strmaxcpy(gParms.CMSInQ, val.c_str(), 60) ; 
        }
        else if(name == "CMSOutQ") 
        {
            CS_strmaxcpy(gParms.CMSOutQ, val.c_str(), 60) ; 
        }
        else if(name == "CMSDBName") 
        {
            CS_strmaxcpy(gParms.CMSDBName, val.c_str(), 60) ; 
        }
        else if(name == "CMSPlant") 
        {
            CS_strmaxcpy(gParms.CMSPlant, val.c_str(), 60) ; 
            int plant = atoi(gParms.CMSPlant) ; 
            gParms.plantMode = plant ; 
            if (gParms.plantMode < 1 || gParms.plantMode > 3)
                printf("Error, unkown plant# = %d in the config file\n", plant) ; 
        }
        else
        {
            printf("ERROR: unknown parameter type '%s' in config file '%s'\n", name.c_str(), gParms.cfgfile) ; 
            retcode = -1 ; 
            break ; 
        }
    }
    
    fclose(fp) ; 
    return retcode ; 
}

int ProcessArgs(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("ERROR:  too few arguments \n") ; 
        return -1 ; 
    }

    for (int i=1; i < argc; i++)
    {
        switch(argv[i][0]) 
        {
            case '-' :
                switch (argv[i][1]) 
                {
                    case 'd' :
                        if ((i + 1) >= argc)
                        {   
                            printf("ERROR: no directory after -d parameter.\n") ; 
                            printusage() ; 
                            return -1 ; 
                        }
                        CS_strmaxcpy(gParms.taskdir, argv[i+1], 250) ; 
                        i++ ; 
                        break ; 
                    case 'l' :
                        if ((i + 1) >= argc)
                        {   
                            printf("ERROR: no logfile defined after -l parameter.\n") ; 
                            printusage() ; 
                            return -1 ; 
                        }
                        CS_strmaxcpy(gParms.logfile, argv[i+1], 250) ; 
                        i++ ; 
                        break ; 
                    case 't' :
                        if ((i + 1) >= argc)
                        {   
                            printf("ERROR: no task archive file defined after -t parameter.\n") ; 
                            printusage() ; 
                            return -1 ; 
                        }
                        CS_strmaxcpy(gParms.taskarchive, argv[i+1], 250) ; 
                        i++ ; 
                        break ; 
                    case 'n' :
                        gParms.bNoEcho = true ; 
                        break ; 
                    case 'r' :
                        gParms.bVerification = true ; 
                        break ; 
                    case 'v' :
                        gParms.bVerifySolarsoft = true ; 
                        break ; 
                    case 'm' :
                        if ((i + 1) >= argc)
                        {   
                            printf("ERROR: no move to file directory defined after -m parameter.\n") ; 
                            printusage() ; 
                            return -1 ; 
                        }
                        CS_strmaxcpy(gParms.moveToDir, argv[i+1], 250) ; 
                        i++ ; 
                        break ; 
                    case 'c' :
                        if ((i + 1) >= argc)
                        {   
                            printf("ERROR: no config file name defined after -c parameter.\n") ; 
                            printusage() ; 
                            return -1 ; 
                        }
                        CS_strmaxcpy(gParms.cfgfile, argv[i+1], 250) ; 
                        if (LoadConfigFile())
                            return -2 ; 
                        i++ ; 
                        break ; 
                    case 's' :
                        if ((i + 1) >= argc)
                        {   
                            printf("ERROR: no file name defined after -s parameter.\n") ; 
                            printusage() ; 
                            return -1 ; 
                        }
                        CS_strmaxcpy(gParms.sqllogname, argv[i+1], 250) ; 
                        i++ ; 
                        break ; 
                    case 'X' :
                        if (argv[i][2] == 'D')
                            noDecadeTracking = 1 ; 
                        else if (argv[i][2] == 'S')
                            noCMSTracking = 1 ; 
                        else
                        {
                            printf("ERROR: only D or S can follow -X parameter.\n") ; 
                            printusage() ; 
                            return -1 ; 
                        }
                        break ; 
                    case '-' : 
                        if (strcmp(&argv[i][2], "tship") == 0)
                            gParms.bTrackAfterShipped = true ; 
                        else if (strcmp(&argv[i][2], "RTER") == 0)
                            gParms.bUseRoutingResource = 1 ; 
                        else if (strcmp(&argv[i][2], "XDOWN") == 0)
                            gParms.evp.bDisable10100 = true ; 
                        else if (strcmp(&argv[i][2], "BATCH") == 0)
                            gParms.evp.bBatchMode = true ; 
                        else if (strcmp(&argv[i][2], "SSEMP") == 0)
                            gParms.evp.bDoEmpTracking = true ; 
                        break ; 
                }
                break ; 
            default:
                printf("ERROR: unexpected parameter: '%s'\n", argv[i]) ; 
                printusage() ; 
                return -1 ; 

        }
    }

    return 0 ; 
}

void BuildDateName(char *nameouttmpname, char *basein) 
{
    time_t tnow ; // Year 2038 issue hear. 
    time(&tnow); 
    struct tm *ptm; 

    ptm = localtime(&tnow) ; 
    sprintf(nameouttmpname, "%s_%04d-%02d-%02d.log", 
                basein,
                ptm->tm_year + 1900, 
                ptm->tm_mon + 1, 
                ptm->tm_mday) ; 

}

csString BuildMoveDir(char *baseToDir, char *moveName, FILE *fplog)
{
    CDateTime dt ; 
    dt.SetNow() ; 
    char subdir[1024] ; 
    sprintf(subdir, "%s\\%04d%02d", gParms.moveToDir, dt.m_nYear, dt.m_nMonth) ; 

    DWORD dwAttr = GetFileAttributes(subdir);
    int dirExists = false ; 
    if(dwAttr != INVALID_FILE_ATTRIBUTES && 
       dwAttr & FILE_ATTRIBUTE_DIRECTORY)
    {   // this is a directory
        dirExists = true ; 
    }

    if (!dirExists && !CreateDirectory(subdir, 0))
    {
        if (fplog)
        {
            fprintf(fplog, 
                "ERROR: could not create directory '%s', moving to base directory\n", 
                        subdir) ; 
            fflush(fplog) ; 
        }
        strcpy(subdir, baseToDir) ; 
    }
    return AddFile2Path(subdir, moveName) ; 
}
                      
                      
                      


int LogToFileAndStdout(FILE *fp, const char *formatstr, ...) 
{
    if (!fp)
        return -1 ; // can't, file doesn't exist. 

    int retcode = 0 ; 
    va_list marker;
    va_start(marker, formatstr);     // Initialize variable arguments
    try {
        CDateTime dt ; 
        dt.SetNow() ; 
        char timestr[64] ; 
        dt.FormatDateTimeSecs(timestr) ; 
        fprintf(stdout, "%s:", timestr) ; 
        vfprintf(stdout, formatstr, marker) ;
        fprintf(stdout, "\n") ; 

        if (fp)
        {
            fprintf(fp, "%s:", timestr) ; 
            vfprintf(fp, formatstr, marker) ;
            fprintf(fp, "\r\n") ;
            fflush(fp) ; 
        }
    }
    catch(...)
    {
        retcode = -2 ; 
    }
    va_end(marker) ; 

    return retcode ; 
}


int LogToFileAndStdoutNT(FILE *fp, const char *formatstr, ...) 
{
    if (!fp)
        return -1 ; // can't, file doesn't exist. 

    int retcode = 0 ; 
    va_list marker;
    va_start(marker, formatstr);     // Initialize variable arguments
    try {

        vfprintf(stdout, formatstr, marker) ;
        fprintf(stdout, "\n") ; 

        if (fp)
        {
            vfprintf(fp, formatstr, marker) ;
            fprintf(fp, "\r\n", marker) ;
            fflush(fp) ; 
        }
    }
    catch(...)
    {
        retcode = -2 ; 
    }
    va_end(marker) ; 

    return retcode ; 
}
