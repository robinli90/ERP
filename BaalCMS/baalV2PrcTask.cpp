// baalV2PrcTask.cpp

#include "stdafx.h"
#include <fcntl.h>
#include <io.h>
#include <conio.h>
#include <sys/stat.h>
#include <list>
#include <CSStdlibs/cslib.h>

// This defines the Data Queue and work order releasing library interface to 
// Solarsoft. 
#include <libCMS/CMSBOMRTE.h>

#include "BaalV2.h"



char ValidPartCode(char p)
{
    switch(p)
    {
        case 'P' :
        case 'M' :
        case 'F' :
        case 'B' :
        case 'O' :
        case 'S' :
        case 'R' :
        case 'I' :
            return p ; 
    }
    return 0 ; 
}


char ValidPartBatch(char p)
{
    if (strchr(VALID_PARTCODES, p))
        return p ; 
    else if (p == 'O')
        return 'L' ; 
    return 0 ; 
}


int ProcessHardnessRec(CCMSDatabase &db, char *buffer, csString &msg, FILE *fpsql, int batchMode, time_t fileTime)
{
    csString buf(buffer) ; 
    buf.Trim() ; 
    csString sotok ; 
    csString partlist ; 
    csString h1tok, h2tok ; 
    csString so1tok, so2tok, part1tok, part2tok ; 

    sotok = buf.NextToken("|", 0) ; 
    sotok.Trim().ToUpper() ; 
    if (sotok != "HARD")
        return HARDNESS_ERROR ; 

    sotok    = buf.NextToken("|") ; 
    partlist = buf.NextToken("|") ; 
    h1tok    = buf.NextToken("|") ; 
    h2tok    = buf.NextToken("|") ; 
    so1tok   = buf.NextToken("|") ; 
    part1tok = buf.NextToken("|") ; 
    so2tok   = buf.NextToken("|") ; 
    part2tok = buf.NextToken("|") ; 

    if (!sotok.size() || !partlist.size() || !h1tok.size() || !h2tok.size() ||
        !so1tok.size() || !part1tok.size() || !so2tok.size() || !part2tok.size())
    {
        msg.Format("ERROR extracting hardness data from: '%s'\n", buffer) ; 
        return HARDNESS_ERROR ; 
    }

    double h1 = atof(h1tok.c_str()) ; 
    double h2 = atof(h2tok.c_str()) ; 

    int retcode = 0 ; 
    int mappedSO = MappedSONUM(db, atoi(sotok.c_str())) ; 

    so1tok.Trim() ; 
    so2tok.Trim() ; 
    part1tok.Trim() ; 
    part2tok.Trim() ; 

    int soRef1 = atoi(so1tok.c_str()) ; 
    int soRef2 = atoi(so2tok.c_str()) ; 
    char partRef1 = part1tok[0] ; 
    char partRef2 = part2tok[0] ;

    for (int i=0; i < partlist.size(); i++)
    {
        char qry[1024] ;
    
        char part = 0 ; 
        
        if (batchMode)
        {
            if ((part=ValidPartBatch(partlist[i])) == 0)
                continue ; 

            // Make sure the reference parts are mapped correctly. 
            partRef1 = ValidPartBatch(part1tok[0]) ; 
            partRef2 = ValidPartBatch(part2tok[0]) ;

            struct tm *pfltm, fltm ; 
            pfltm = localtime(&fileTime) ; 
            fltm = *pfltm ; 

            char timestring[128] ; 
            sprintf(timestring, "%4d-%02d-%02d %02d:%02d:%02d", 
                        fltm.tm_year + 1900, 
                        fltm.tm_mon + 1,
                        fltm.tm_mday, 
                        fltm.tm_hour, 
                        fltm.tm_min, 
                        fltm.tm_sec) ; 

            sprintf(qry, 
                "INSERT INTO %s.EXCOTASK(PLANT,SONUM,EMPNUM,PRTCODE,TASK,TASKTIME,STATION"
                ",ARC,RTYPE,FLAGS,N1,N2,R1,R2,S1,S2)"
                " VALUES('%s','%d','99999','%c','RR','%s','QCH','N','HRD',0"
                ",%d,%d,%.3f,%.3f,'%c','%c')", 
                    db.dbname, 
                    gParms.evp.plantID, 
                    mappedSO, part, timestring, 
                    soRef1, soRef2, h1, h2, partRef1, partRef2) ; 
        }
        else
        {
            if ((part=ValidPartCode(partlist[i])) == 0)
                continue ; 

            sprintf(qry, 
                "INSERT INTO d_hardness(ordernumber, part, hard1, hard2, ctime, soref1, partref1, soref2, partref2)" 
                " VALUES(%d, '%c', '%.1f', '%.1f', GETDATE(),%d,'%c',%d,'%c')", 
                        mappedSO, part, h1, h2, soRef1, partRef1, soRef2, partRef2 ) ; 
        }
            
        if (fpsql)
        {
            fprintf(fpsql, "%s\n", qry) ; 
            fflush(fpsql) ; 
        }

        bool bDone = false ; 
        int count = 0 ; 
        while (count++ < 4 && !bDone) 
        {
            retcode = 0 ; 

            try
            {
                CSQLRecordset rs(db) ;
                rs << qry ; 
                rs.SQLExec() ;
                bDone = true ; 
            }
            catch (CSQLException* e)
            {
                csString str = e->m_strError.c_str() ;
                // char msg[4096] ; 
                // _snprintf(msg, 4096, "SQL error %d getting max SO number\n MSG: %s\n", 
                //     (int)e->m_nRetCode, e->m_strError.c_str()) ; 
                // LogError(msg) ; 
                db.Reconnect() ; 
                retcode = HARDNESS_ERROR - 1 ;
            }
        }
    }

    return retcode ; 
}

int LogTask(int nResult, FILE *fparchive, FILE *fplog, csString &taskString, csString &msg)
{
    // Only Delete if Processing was successful.
    if (nResult != DB_ERROR) 
    {   // Then archive the task record
        if (fparchive) 
        {
            fprintf(fparchive, "%s\n", taskString.c_str()) ; 
            fflush(fparchive) ; 
        }
        
        printf("%s\n", msg.c_str()) ; 
        if (fplog) 
        {
            if (nResult == ALREADY_SHIPPED)
            {   // Record the error 

            }
            else if (nResult == BAD_ORDER_NUMBER)
            {

            }

            if (!fparchive)
            {   // Only output to the log file if there is no archive. 
                fprintf(fplog, "MSG-LG1: %s\n", msg.c_str()) ; 
                fflush(fplog) ; 
            }
        }
    }
    else 
    {   // Log the error condition
        if (fplog)
        {   // Error 
            fprintf(fplog, "DATABASE_ERROR: %s\n", msg.c_str()) ; 
            fflush(fplog) ; 
        }

        if (!gParms.bNoEcho)
        {
            printf("DATABASE_ERROR: %s\n", msg.c_str()) ; 
        }
    }
    return 0 ; 
}


int ArchiveTaskFile(csString &fileName, FILE *fplog)
{
    if (gParms.moveToDir[0])
    {   // Then move the task file to this archive directory
        csString movePath ; 
        csString timePrefix ; 
        
        char datestr[64] ; 
        CDateTime dtime ; 
        dtime.SetNow() ; 
        dtime.FormatDateTimeSecs(datestr, 1) ; // mode == 2
        csString filebase, pathStr ; 
        SplitPathAndFile(fileName, pathStr, filebase) ; 
        csString moveName = csString(datestr) + "_" + filebase ; 
        movePath = BuildMoveDir(gParms.moveToDir, moveName.c_str(), fplog) ; 

        if (!MoveFile(fileName.c_str(), movePath.c_str()))
        {
            int fh = _open(fileName.c_str(), O_RDONLY) ; 
            if (fh != -1)
            {
                struct __stat64 fileData ; 
                _fstat64(fh, &fileData) ; 
                close(fh) ; 
                if (fileData.st_size == 0)
                {   // Then just delete the file
                    if (!gParms.bNoEcho)
                        printf("Deleting zero byte file %s\n", fileName.c_str()) ; 
                    if (!DeleteFileA(fileName.c_str()))
                    {
                        BAALPrintLastError(fplog) ; 
                        BAALPrintLastError(stdout) ; 
                    }
                }
            } 
            else if (!gParms.bNoEcho)
            {
                printf("ERR: Couldn't move '%s' to '%s'\n\n", 
                        fileName.c_str(), movePath.c_str()) ; 
            }
        }
        
    }
    else
    {   // Simply delete the file. 
        DeleteFile(fileName.c_str()) ;
    }

    return 0 ; 
}

bool DB_ReConnect(CSQLDatabase &db, FILE *fplog)
{
    int attemptCount = 0 ; 
    while (true)
    {
        try {
            db.Close() ; 
            Sleep(250) ; 
            if (db.OpenEx(gParms.odbcName, gParms.user, gParms.pwd))
            {
                if (!gParms.bNoEcho)
                    printf("   *** DATABASE RECONNECT SUCCESSFUL ***\n") ; 
                return true ; // success
            }
            break ; 
        }
        catch (...)
        {   
            if (fplog)
            {
                fprintf(fplog, "Error connecting to Decade database ODBC=%s\n", gParms.odbcName) ; 
                fflush(fplog) ; 
            }
        }

        if (attemptCount++ > 20)
        {
            if (!gParms.bNoEcho)
            printf("Database connection error, aborting.....\n") ; 
            if (fplog)
            {
                fprintf(fplog, "Database connection error, aborting.....\n") ; 
                fflush(fplog) ; 
            }

            exit(2) ; 
        }

        if (!gParms.bNoEcho)
            printf("   ==>> attempting database re-connect in 30 seconds....\n") ; 

        Sleep(30000) ; 
    }
    return false ; 
}


int BaalFileProcessor::SaveTaskToDecade(TaskRec &task, csString &taskline)
{
    int retcode = 0 ; 
    int dbSaveCount = 0; // number of write attempts to the database
    bool bVerified = false ; 
    int maxCount = 0 ; 

    while (dbSaveCount++ < 4 && !bVerified)
    {   // Make sure the record is processed as required
        if (maxCount++ > 1000)
        {
            printf("Aborting, lost DB connection to Decade\n") ; 
            exit(1) ; 
        }

        if (task.SaveToDB(*pdb, fpsql))
        {   // Display error to console. 
            if (!gParms.bNoEcho)
                printf("DBERR: %s\n", taskline.c_str()) ; 
            char msgwrk[1024] ; 
            sprintf(msgwrk, "ERROR: DB: saving '%s' data to Decade\n", taskline.c_str()) ;
            msg = msgwrk ; 
            retcode = DB_ERROR ; 
        }
        else
        {   // Display status on console
            if (!gParms.bNoEcho)
                printf("PROC: %s\n", taskline.c_str()) ; 
            char msgwrk[1024] ; 
            sprintf(msgwrk, "PROC-OK: '%s'\n", taskline.c_str()) ; 
            msg = msgwrk ; 
            if (!gParms.bVerification)
            {
                bVerified = true ; 
                retcode = NO_ERROR ; 
            }
        }

        if (retcode == DB_ERROR || dbSaveCount > 2)
        {   // else we try 5 more times to re-connect
            fprintf(fplog, "  ==> Attempting Database Reconnect....") ; 
            fflush(fplog) ; 
            // If  the database reconnect fails, the program aborts. 
            DB_ReConnect(*pdb, fplog) ;
            dbSaveCount = 0 ; 
        }

        if (!bVerified)
        {   // Read back the record to make sure everything worked OK. 
            if (task.VerifyDBRecord(*pdb, fpsql))
            {
                bVerified = true ; 
                retcode = NO_ERROR ; 
            }
            else
            {
                char msgwrk[1024] ; 
                sprintf(msgwrk, "Verify ERR(#%d): %s\r\n", dbSaveCount, taskline.c_str()) ; 
                if (!gParms.bNoEcho)
                    printf(msgwrk) ; 
                LogError(msgwrk) ; 
                Sleep(1000) ; // backoff a little
            }
        }
    }
    return retcode ; 
}

void BAALPrintLastError(FILE *fp)
{
    DWORD errnum = GetLastError () ; 
    fprintf(fp, "Get Last Error reports %d\n", errnum) ;
    LPVOID lpMsgBuf;
    FormatMessage( 
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM | 
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errnum,
        0, // Default language
        (LPTSTR) &lpMsgBuf,
        0,
        NULL 
        );
    // Process any inserts in lpMsgBuf.
    // ...
    // Display the string.
    fprintf(fp, "%s\n", lpMsgBuf) ; 

    // Free the buffer.
    LocalFree( lpMsgBuf );
}


//! taskpath is the full path name of the task file 
//! taskstr is the one line contents of the taskpath file
//! msg is the feedback response message of processing for logging. 
int BaalFileProcessor::ProcessFile(csString &taskfile, time_t taskfiletime) 
{
    int retcode = 0 ; 

    // Convert file name to full path name
    csString filePath = AddFile2Path(gParms.taskdir, taskfile) ; 
    char buffer[256] ; 

    FILE *fp = fopen(filePath.c_str(), "rt") ; 
    if (fp)
    {
        taskfile = filePath ; 
    }
    else
    {
        char tmpstr[256] ; 
        _snprintf(tmpstr, 250, "ERROR: couldn't open task file '%s'\r\n", 
                            filePath.c_str()) ; 
        LogError(tmpstr) ; 
        BAALPrintLastError(gCMSparms.pevp->fpLOG) ;
        return TASK_ERR_NOFILE ; 
    }

    buffer[0] = 0 ; 
    if (!fgets(buffer, 254, fp))
    {
        fclose(fp) ; 

        char tmpstr[256] ; 
        _snprintf(tmpstr, 250, "ERROR: empty file '%s'\r\n", 
                            filePath.c_str()) ; 
        LogError(tmpstr) ; 
        ArchiveTaskFile(filePath, fplog) ;
        return 0 ; // no data so just assume it has been processed
    }

    if (buffer[0] == 'H' && buffer[1] == 'A' && 
        buffer[2] == 'R' && buffer[3] == 'D')
    {   // Special processing for hardness
        int done = 0 ;
        do {
            if ((retcode = ProcessHardnessRec(*pdb, buffer, msg, fpsql)) == 0) 
            {
                if (fplog)
                {
                    fprintf(fplog, "HARD-OK: %s\n", buffer) ; 
                    fflush(fplog) ; 
                }

                buffer[0] = 0 ; 
                fgets(buffer, 100, fp) ; 
                if (buffer[0] != 'H' || buffer[1] != 'A' ||
                    buffer[2] != 'R' || buffer[3] != 'D')
                {
                    done = 1 ; 
                }
            }
        } while (!retcode && !done) ; 
        
        fclose(fp) ;
        ArchiveTaskFile(filePath, fplog) ;
        return retcode ; 
    }

    LogToFileAndStdoutNT(fplog, "--------------------------------------------------") ; 
    LogToFileAndStdout(fplog, "LINE:  %s", buffer) ; 

    // -----------------------------------
    // Read task record so now process it. 
    // -----------------------------------
    int maperr = 0 ; 
    msg.clear() ; // reset the message passing variable.

    bool done = false ; // not used, break on end of file
    csString line ; 
    do {
        try 
        {
            taskstr = buffer ; 
            taskstr.Trim() ; // Clean up string

            // Extract out the fields. 
            TaskRec task ; 
            line = buffer ; 
            line.Trim() ; 

            int errcode = task.ParseString(buffer) ; 
            if (errcode)
            {   // Error in the actual data string, thus it cannot be processed. 
                char tmpstr[512] ; 
                if (errcode == -10)
                    _snprintf(tmpstr, 250, "ERROR: RUNTIME record exceeded maximum runtime of 10+ days...") ; 
                else
                    _snprintf(tmpstr, 250, "ERROR: %d processing '%s'", errcode, line.c_str()) ; 
                msg = tmpstr ; 

                if (!gParms.bNoEcho)
                    printf("%s\n", tmpstr) ; 

                throw BAD_TASK_DATA ; // error processing record
            }

            if (task.sonum == 0)
            {
                char tmpstr[256] ; 
                _snprintf(tmpstr, 250, "ERROR: invalid SO# processing '%s'", line.c_str()) ; 
                msg = tmpstr ; 

                if (!gParms.bNoEcho)
                    printf("%s\n", tmpstr) ; 

                throw BAD_TASK_SONUM ; 
            }

            task.mappedSO = MappedSONUM(*pdb, task.sonum) ; 

            // We now have a valid task record. The next stage is to load it into the database. 
            // If the --tship is set, then ignore shipped records. 

            int outputMode = 0 ; 
            int processMode = 0 ; 
            switch((processMode = gParms.evp.GetTaskMode(task.task)))
            {
                case 0 :
                case 'B' :
                    outputMode = EVENTS_OUTPUT_DECADE | EVENTS_OUTPUT_SOLARSOFT ; 
                    break ;
                case 'S' :
                    outputMode = EVENTS_OUTPUT_SOLARSOFT ; 
                    break ;
                case 'D' :
                    outputMode = EVENTS_OUTPUT_DECADE ; 
                    break ;
            }
			//use to be valstat = 0
            int valStat = 1 ; 
            if (!task.IsForced())
            {   // Make sure it hasn't been shipped and that it exists as a valid 
                // order number in the database. 
                char tmpstr[1024] ; 

             //   valStat = ValidActiveOrder(*pdb, task, outputMode) ;

                if (!valStat)
                {
                    if (outputMode & EVENTS_OUTPUT_SOLARSOFT)
                    {
                        _snprintf(tmpstr, 250, "ERROR: bad order number processing '%s'", line.c_str()) ; 
                        msg = tmpstr ; 
                        if (!gParms.bNoEcho)
                            printf("%s\n", msg) ; 

                        throw BAD_ORDER_NUMBER ; 
                        // else continue to track the records. 
                    }
                    else
                    {
                        _snprintf(tmpstr, 250, "WARNING: no order exists in decade processing '%s'", line.c_str()) ; 
                        msg = tmpstr ; 
                        if (!gParms.bNoEcho)
                            printf("%s\n", msg) ; 

                        fprintf(fplog, "%s\r\n", tmpstr) ; 
                        fflush(fplog) ; 
                    }
                }
                else if (valStat & 0x02)
                {
                    if (!gParms.bTrackAfterShipped)
                    {
                        _snprintf(tmpstr, 250, "ERROR: order already shipped processing '%s'", line.c_str()) ; 
                        msg = tmpstr ; 

                        if (!gParms.bNoEcho)
                            printf("%s\n", msg) ; 

                        throw ALREADY_SHIPPED ; 
                    }
                    // else  continue to track the records. 

                    _snprintf(tmpstr,1000, "WARNING: order already shipped processing '%s'", line.c_str()) ; 

                    if (!gParms.bNoEcho)
                        printf("%s\n", tmpstr) ; 

                    fprintf(fplog, "%s\r\n", tmpstr) ; 
                    fflush(fplog) ; 
                }
            }


            ////////////////////////////////////////////////////////////////
            //       RUN TIME LOGIC
            ////////////////////////////////////////////////////////////////
            // Runtime records need to be matched against existing data. 

            // Save the Solarsoft data just in case
            gParms.evp.evd.sonum = task.mappedSO ; 
            gParms.evp.evd.empnum = task.empnum ;
            strcpy(gParms.evp.evd.part, task.part) ; 
            strcpy(gParms.evp.evd.task, task.task) ; 
            strcpy(gParms.evp.evd.station, task.station) ; 
            gParms.evp.evd.tasktime = task.tasktime ; 

            bool bDidTaskMap = false ; 
            TaskMapItr imapped ; 

            // For runtime operations we need to do the taskmap processing in advance
            // because we need the task mapped to read Solarsoft and get the data
            // required to add the d_task record if required. 
            
            // If in the runtime calculation there was no start time record, then 
            // we have to add the start time record as an extra tracking event. 
            TaskRec starttask ; 
            starttask.sonum = 0 ; 

            if (task.mode == TaskRec::RUNTIME)
            {   // Then work out the actual stop time based on this runtime. 
                // If this is a dual or Solarsoft only task then use Solarsoft to calculate
                // the time. If this is a Decade only task, then use decade to calculate
                // the time. If there is no start time, then we will create start and stop
                // times based on the timestamp for the file as the stop time, and then
                // use the runtime to calculate when the stop time was. This will not be
                // accurate but will generate valid costing data. 

                CDateTime startTime(0) ; 
                if (outputMode & EVENTS_OUTPUT_SOLARSOFT)
                {   // Then extract runtime from Solarsoft
                    // Now try to map the data to Solarsoft. 
                    maperr = 0 ;
                    if ((maperr = gParms.evp.MapDecadeData(imapped)) != 0)
                    {
                        if (maperr == -22)
                        {
                            LogToFile(fplog, "ERROR TO SOLARSOFT: could not do station map TASKFILE='%s'\r\n", 
                                                    buffer) ; 
                            if (!gParms.bNoEcho)
                            {
                                printf("ERROR TO SOLARSOFT: could not do station map TASKFILE='%s'\n", 
                                                    buffer) ; 
                            }
                        }
                        else if (maperr == -25)
                        {
                            LogToFile(fplog, "ERROR TO SOLARSOFT: SO#=%d, no associated work order so could not map task '%s', err=%d\n",
                                                gParms.evp.evd.sonum, buffer, maperr) ; 
                            if (!gParms.bNoEcho)
                            {
                                printf("ERROR TO SOLARSOFT: SO#=%d, no associated work order so could not map task '%s', err=%d\n", 
                                            gParms.evp.evd.sonum, buffer, maperr) ; 
                            }
                        }
                        else
                        {
                            LogToFile(fplog, "ERROR TO SOLARSOFT: could not map task '%s', err=%d\n", buffer, maperr) ; 
                            if (!gParms.bNoEcho)
                            {
                                printf("ERROR TO SOLARSOFT: could not map task '%s', err=%d\n", buffer, maperr) ; 
                            }
                        }
                    }
                    else
                    {
                        bDidTaskMap = true ; 
                        GetEndTimeFromSolarSoft(gParms, task, taskfiletime, starttask) ;
                    }
                }
                else
                {   // Get the runtime based on the d_task table in Decade
                    if (!GetEndTimeFromDecade(gParms, task, taskfiletime, starttask))
                        bDidTaskMap = true ; 
                }

                if (!bDidTaskMap && starttask.sonum == 0)
                {   // Then couldn't find a start time record. Need to use the file time
                    // as the end and create a start record from that for decade. For 
                    // Solarsoft there is no way to effectively track this easily (can try
                    // to send a time in the future for the 40005 which may work). 
                    
                    task.tasktime = taskfiletime ; // 
                    starttask = task ; // copy all pertinent task data over
                    starttask.tasktime = task.tasktime - task.secs ; 
                    
                    CDateTime dt(taskfiletime) ; 
                    task.hour  = dt.m_nHours ; 
                    task.mins  = dt.m_nMins ;
                    task.secs  = dt.m_nSecs; 
                    task.day   = dt.m_nDay ; 
                    task.month = dt.m_nMonth ; 
                    task.year  = dt.m_nYear ; 

                    dt.SetTime(starttask.tasktime) ; 
                    starttask.hour  = dt.m_nHours ; 
                    starttask.mins  = dt.m_nMins ;
                    starttask.secs  = dt.m_nSecs; 
                    starttask.day   = dt.m_nDay ; 
                    starttask.month = dt.m_nMonth ; 
                    starttask.year  = dt.m_nYear ; 
                }

                CDateTime dt(task.tasktime) ; 
                gParms.evp.evd.year  = dt.m_nYear ; 
                gParms.evp.evd.month = dt.m_nMonth ; 
                gParms.evp.evd.day   = dt.m_nDay ; 
                gParms.evp.evd.hour  = dt.m_nHours ; 
                gParms.evp.evd.mins  = dt.m_nMins ; 
                gParms.evp.evd.secs  = dt.m_nSecs ; 

                struct tm *ptm ;
                ptm = localtime(&(task.tasktime)) ;

                sprintf(gParms.evp.evd.dateStr, "%04d%02d%02d",
                                    ptm->tm_year + 1900,
                                    ptm->tm_mon + 1,
                                    ptm->tm_mday) ;

                sprintf(gParms.evp.evd.timeStr, "%02d%02d%02d", 
                                    ptm->tm_hour,
                                    ptm->tm_min,
                                    ptm->tm_sec) ;
            }

            ////////////////////////////////////////////////////////////////
            //       TRACK THIS RECORD
            ////////////////////////////////////////////////////////////////

            retcode = NO_ERROR ; 
            if (!noDecadeTracking && (outputMode & EVENTS_OUTPUT_DECADE))
            {   // ---------------------------------------
                // -------- DECADE PROCESSING ------------
                // ---------------------------------------
                if (starttask.sonum)
                    SaveTaskToDecade(starttask, line + ";MISSING RUNTIME START") ;
                SaveTaskToDecade(task, line) ;
            }

            LogTask(retcode, fparchive, fplog, line, msg) ;

            if (!noCMSTracking && (outputMode & EVENTS_OUTPUT_SOLARSOFT))
            {   // ---------------------------------------
                // -------- SOLARSOFT PROCESSING ---------
                // ---------------------------------------

                if (!(gCMSparms.status & 0x80000000))
                {   // Process to solarsoft
                    if (gParms.isys && gParms.qhandle)
                    {
                        if (!bDidTaskMap)
                        {
                            if ((maperr = gParms.evp.MapDecadeData(imapped)) != 0)
                            {
                                if (maperr == -22)
                                {
                                    LogToFile(fplog, "ERROR TO SOLARSOFT: could not do station map TASKFILE='%s'\r\n", 
                                                            buffer) ; 
                                    if (!gParms.bNoEcho)
                                    {
                                        printf("ERROR TO SOLARSOFT: could not do station map TASKFILE='%s'\n", 
                                                            buffer) ; 
                                    }
                                }
                                else if (maperr == -25)
                                {
                                    LogToFile(fplog, "ERROR TO SOLARSOFT: SO#=%d, no associated work order so could not map task '%s', err=%d\n",
                                                        gParms.evp.evd.sonum, buffer, maperr) ; 
                                    if (!gParms.bNoEcho)
                                    {
                                        printf("ERROR TO SOLARSOFT: SO#=%d, no associated work order so could not map task '%s', err=%d\n", 
                                                    gParms.evp.evd.sonum, buffer, maperr) ; 
                                    }
                                }
                                else
                                {
                                    LogToFile(fplog, "ERROR TO SOLARSOFT: SO#=%d, could not map task '%s', err=%d\n",
                                                    gParms.evp.evd.sonum,  buffer, maperr) ; 
                                    if (!gParms.bNoEcho)
                                    {
                                        printf("ERROR TO SOLARSOFT: SO#=%d, could not map task '%s', err=%d\n", 
                                                    gParms.evp.evd.sonum, buffer, maperr) ; 
                                    }
                                }
                            }
                            else
                            {
                                bDidTaskMap = true ; 
                            }
                        }

                        if (!bDidTaskMap)
                        {
                            LogToFileAndStdout(fplog, "Task map failed for SO#=%d, TASK=%s, PART=%s", 
                                                            task.sonum, task.task, task.part) ; 
                        }
                        else
                        {
                            int qret = 0 ;
                            if (starttask.sonum)
                            {   // ONLY RUNTIME type records will ever have a starttask.sonum != 0
                                if (atoi(gParms.evp.evd.seqnum) != 0 &&
                                    (gParms.evp.evd.resCode[0] != ')'))
                                {
                                    gParms.evp.evd.sonum = starttask.mappedSO ;
                                    gParms.evp.evd.empnum = starttask.empnum ;
                                    strcpy(gParms.evp.evd.part, starttask.part) ;
                                    strcpy(gParms.evp.evd.task, starttask.task) ;
                                    strcpy(gParms.evp.evd.station, starttask.station) ;
                                    gParms.evp.evd.tasktime = starttask.tasktime ;

                                    qret = gParms.evp.TrackEvent() ;

                                    if (qret & 0x01)
                                    {
                                        char msgwrk[1024] ;
                                        csString csemp(gParms.evp.evd.empTag) ;
                                        int emptagnum = atoi(csemp.c_str()) ;
                                        sprintf(msgwrk, "ERROR: empTag=%d not defined", emptagnum) ;
                                        msg = msgwrk ;

                                        if (!gParms.bNoEcho)
                                            printf("%s\n", msgwrk) ;
                                    }
                                    else if (qret & 0x02)
                                    {
                                        char msgwrk[1024] ;
                                        sprintf(msgwrk, "ERROR: seq#=%s undefined for job=%s", 
                                                gParms.evp.evd.seqnum, 
                                                gParms.evp.evd.jobnum) ;
                                        msg = msgwrk ;
                                        LogToFile(fplog, "%s\r\n", msgwrk) ; 

                                        if (!gParms.bNoEcho)
                                            printf("%s\n", msgwrk) ;
                                    }
                                }
                                else
                                {   // Error
                                    char tmpstr[1024] ; 
                                    _snprintf(tmpstr, 1000, "ERROR: (runtime, starttask) Map error or SEQ# not found in taskMap lookup for task='%s'",
                                                    gParms.evp.evd.task ) ; 
                                    LogToFile(fplog, "%s\r\n", tmpstr) ; 
                                    if (!gParms.bNoEcho)
                                        printf("%s\n", tmpstr) ; 
                                    qret = 0x01 ; 
                                }
                            }

                            if (atoi(gParms.evp.evd.seqnum) != 0 &&
                                (gParms.evp.evd.resCode[0] != ')'))
                            {
                                gParms.evp.evd.sonum = task.mappedSO ; 
                                gParms.evp.evd.empnum = task.empnum ;
                                strcpy(gParms.evp.evd.part, task.part) ; 
                                strcpy(gParms.evp.evd.task, task.task) ; 
                                strcpy(gParms.evp.evd.station, task.station) ; 
                                gParms.evp.evd.tasktime = task.tasktime ; 

                                if (task.mode & TaskRec::SAWMODE)
                                {
                                    gParms.evp.evd.eventMode |= 
                                        (EventData::EVD_OUTPUT_LOTSER | 
                                         EventData::EVD_OUTPUT_DOWN) ; 
                                    CS_strmaxcpy(gParms.evp.evd.serialNumber, task.serNumStr, 14) ; 
                                }

                                qret |= gParms.evp.TrackEvent() ; 

                                if (qret & 0x01)
                                {
                                    char msgwrk[1024] ; 
                                    csString csemp(gParms.evp.evd.empTag) ; 
                                    int emptagnum = atoi(csemp.c_str()) ; 
                                    sprintf(msgwrk, "ERROR: empTag=%d not defined", emptagnum) ; 
                                    msg = msgwrk ; 

                                    if (!gParms.bNoEcho)
                                        printf("%s\n", msgwrk) ; 
                                }
                                else if (qret & 0x02)
                                {
                                    char msgwrk[1024] ;
                                    sprintf(msgwrk, "ERROR(2): seq#=%s undefined for job=%s", 
                                                        gParms.evp.evd.seqnum, 
                                                        gParms.evp.evd.jobnum) ;

                                    msg = msgwrk ;
                                    LogToFile(fplog, "%s\r\n", msgwrk) ; 

                                    if (!gParms.bNoEcho)
                                        printf("%s\n", msgwrk) ;
                                }
                                if (qret & ~0x03) 
                                {
                                    char msgwrk[1024] ; 
                                    sprintf(msgwrk, "ERROR: error# %04x while sending task '%s' to data Q", 
                                                qret, line.c_str()) ; 
                                    msg = msgwrk ; 

                                    if (!gParms.bNoEcho)
                                        printf("%s\n", msgwrk) ; 
                                }
                            }
                            else
                            {   // Error
                                char tmpstr[1024] ; 
                                _snprintf(tmpstr, 1000, "ERROR: (std, endtask) Map error or SEQ# not found in taskMap lookup for task='%s'",
                                                gParms.evp.evd.task ) ; 
                                LogToFile(fplog, "%s\r\n", tmpstr) ; 
                                if (!gParms.bNoEcho)
                                    printf("%s\n", tmpstr) ; 
                                qret = 0x02 ; 
                            }
                        }
                    }
                    else
                    {   // Error - no connection to data queue
                        char tmpstr[256] ;
                        _snprintf(tmpstr, 250, "ERROR: no data queue connection to iSeries\r\n") ; 
                        LogError(tmpstr) ;
                        printf("ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR\n") ; 
                        printf("ERROR --------- No Data-Queue Connection to iSeries -------\n") ; 
                        printf("ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR\n") ; 
                    }
                }
            }
        }
        catch(int err)
        {
            char tmpstr[256] ;
            _snprintf(tmpstr, 250, "ERROR %d in file '%s' processing task line: '%s'\r\n",
                                err, filePath.c_str(), line.c_str()) ;
            LogError(tmpstr) ;
        }

        if (!fgets(buffer, 254, fp))
            break ; // exit on end of file. 
    } while (!done) ;

    fclose(fp) ;

    // move the task file so we don't process it again. 
    ArchiveTaskFile(filePath, fplog) ;

    LogToFileAndStdoutNT(fplog, "==================================================") ; 

    return 0 ;
}


int TaskRec::SaveToCMSDB(CCMSDatabase &db, FILE *fplog)
{
    char qry[2048] ;
    int qlen = 0 ; 

    char datestr[64] ; // this is the tasktime for the event

    if (mode == SAWMODE)
    {   // Save material serial number
        sprintf(datestr, "%04d-%02d-%02d %02d:%02d:%02d",
                        year, month, day, hour, mins, secs) ;

        qlen = _snprintf(qry, 2000,  "INSERT INTO %s.EXCOTASK(PLANT,SONUM,EMPNUM,TASK,PRTCODE,STATION,TASKTIME,S1,RTYPE,ARC)"
                            " VALUES('%s','%d','%d','%s','%s','%s','%s','%s','SAW','N')", 
                db.dbname, gParms.evp.plantID, mappedSO, empnum, task, part, station, datestr, serNumStr) ; 
    }
    else if (mode == RUNTIME)
    {   // Set runtime record fields
        struct tm *pstm = localtime(&filetime) ; 

        sprintf(datestr, "%04d-%02d-%02d %02d:%02d:%02d",
                    pstm->tm_year + 1900, pstm->tm_mon + 1, pstm->tm_mday, 
                    pstm->tm_hour, pstm->tm_min, pstm->tm_sec) ; 

        // runtime is saved in decimal hours
        double rtime = secs / 3600.0 ; 

        qlen = _snprintf(qry, 2000, "INSERT INTO %s.EXCOTASK(PLANT, SONUM, EMPNUM, TASK, PRTCODE, STATION, TASKTIME, R1, RTYPE, ARC)"
                            " VALUES('%s','%d','%d','%s','%s','%s','%s','%.4f','RTM','N')", 
                db.dbname, gParms.evp.plantID, mappedSO, empnum, task, part, station, datestr, rtime) ; 

    }
    else if (mode == TBLANKS)
    {   // This is a turned blank record, which can be processed through the batch 
        // mode processor directly without consideration
        sprintf(datestr, "%04d-%02d-%02d %02d:%02d:%02d",
                        year, month, day, hour, mins, secs) ;

        qlen = _snprintf(qry, 2000, "INSERT INTO %s.EXCOTASK(PLANT,SONUM,EMPNUM,TASK,PRTCODE,STATION,TASKTIME,N1,S1,S2,RTYPE,ARC)"
                            " VALUES('%s','100','%d','TB','BL','%s','%s',%d,'%s','%s','TBL','N')", 
                db.dbname, gParms.evp.plantID, empnum, station, datestr, qty, part, serNumStr) ; 

    }
    else if (mode == PICKPRT)
    {   // This is a turned blank record, which can be processed through the batch 
        // mode processor directly without consideration
        sprintf(datestr, "%04d-%02d-%02d %02d:%02d:%02d",
                        year, month, day, hour, mins, secs) ;

        qlen = _snprintf(qry, 2000, "INSERT INTO %s.EXCOTASK(PLANT,SONUM,EMPNUM,TASK,PRTCODE,STATION,TASKTIME,S1,S2,RTYPE,ARC)"
                            " VALUES('%s','%d','%d','PP','%s','%s','%s','%s','%s','PPT','N')", 
                db.dbname, gParms.evp.plantID, mappedSO, empnum, part, station, datestr, mtl, serNumStr) ; 

    }
    else
    {   // Normal task event
        sprintf(datestr, "%04d-%02d-%02d %02d:%02d:%02d",
                        year, month, day, hour, mins, secs) ;

        qlen = _snprintf(qry, 2000, "INSERT INTO %s.EXCOTASK(PLANT,SONUM,EMPNUM,TASK,PRTCODE,STATION,TASKTIME,RTYPE,ARC)"
                                    " VALUES('%s','%d', '%d', '%s', '%s', '%s', '%s', 'EVT', 'N')", 
                db.dbname, gParms.evp.plantID, mappedSO, empnum, task, part, station, datestr) ; 
    }

    bool bDone = false ; 
    int count = 0 ; 
    while (count++ < 4 && !bDone) 
    {
        if (fplog)
        {
            fprintf(fplog, "%s\n", qry) ; 
            fflush(fplog) ; 
        }

        try
        {
            CSQLRecordset rs(db) ;
            rs << qry ; 
            rs.SQLExec() ;
            bDone = true ; 
        }
        catch (CSQLException* e)
        {
            csString str = e->m_strError.c_str() ;
            // char msg[4096] ; 
            // _snprintf(msg, 4096, "SQL error %d getting max SO number\n MSG: %s\n", 
            //     (int)e->m_nRetCode, e->m_strError.c_str()) ; 
            // LogError(msg) ; 
            db.Reconnect() ; 
        }
    }

    if (!bDone)
        return -1 ; // an error occured

    return 0 ; 
}


int TaskRec::SaveToDB(CSQLDatabase &db, FILE *fplog)
{
    char qry[2048] ;
    
    char datestr[64] ;
    sprintf(datestr, "%04d-%02d-%02d %02d:%02d:%02d",
                year, month, day, hour, mins, secs) ;
    sprintf(qry, 
        "INSERT INTO d_task(ordernumber, employeenumber, task, part, subpart, station, tasktime, flags)"
        " VALUES(%d, %d, '%s', '%c', '%c', '%s', '%s', 0)", 
                mappedSO, empnum, task, part[0], part[1], station, datestr) ; 
    
    bool bDone = false ; 
    int count = 0 ; 
    while (count++ < 4 && !bDone) 
    {
        if (fplog)
        {
            fprintf(fplog, "%s\n", qry) ; 
            fflush(fplog) ; 
        }

        try
        {
            CSQLRecordset rs(db) ;
            rs << qry ; 
            rs.SQLExec() ;
            bDone = true ; 
        }
        catch (CSQLException* e)
        {
            csString str = e->m_strError.c_str() ;
            // char msg[4096] ; 
            // _snprintf(msg, 4096, "SQL error %d getting max SO number\n MSG: %s\n", 
            //     (int)e->m_nRetCode, e->m_strError.c_str()) ; 
            // LogError(msg) ; 
            db.Reconnect() ; 
        }
    }

    if (!bDone)
        return -1 ; // an error occured

    return 0 ; 
}


bool TaskRec::VerifyDBRecord(CSQLDatabase &db, FILE *fplog) 
{
    bool bFound = false ; 

    char qry[2048] ;
    
    char datestr[64] ; 
    sprintf(datestr, "%04d-%02d-%02d %02d:%02d:%02d", 
                year, month, day, hour, mins, secs) ; 
    sprintf(qry, 
        "SELECT ordernumber FROM d_task WHERE"
        " ordernumber=%d AND employeenumber=%d AND task='%s' AND part='%c' AND subpart='%c'"
        " AND station='%s' AND tasktime='%s'", 
                mappedSO, empnum, task, part[0], part[1], station, datestr) ; 
    
    int count = 0 ; 
    while (count++ < 4 && !bFound) 
    {
        if (fplog)
        {
            fprintf(fplog, "%s\n", qry) ; 
            fflush(fplog) ; 
        }

        try
        {
            CSQLRecordset rs(db) ;
            rs << qry ; 
            rs.SQLExec() ;
            while (rs.SQLFetch())
            {
                csString shopnum = rs.SQLGetData(1).c_str() ; 
                shopnum.Trim() ;

                if (atoi(shopnum.c_str()) == mappedSO)
                    bFound = true ; 
            }
        }
        catch (CSQLException* e)
        {
            csString str = e->m_strError.c_str() ;
            // char msg[4096] ; 
            // _snprintf(msg, 4096, "SQL error %d getting max SO number\n MSG: %s\n", 
            //     (int)e->m_nRetCode, e->m_strError.c_str()) ; 
            // LogError(msg) ; 
        }
    }

    return bFound  ; 
}

//! Returns 0 no record read, 0x01=read record, 0x02, shipdate is set. 
int ValidActiveOrder(CSQLDatabase &db, TaskRec &task, int outputMode)
{
    int retcode = 0 ; 

    if (outputMode & EVENTS_OUTPUT_SOLARSOFT)
    {   // Then check against the solarsoft database
        char qry[2048] ; 
        sprintf(qry, "SELECT DCORD#,DCSTAT FROM %s.OCRH WHERE DCORD#=%d", 
                            gCMSparms.dbname, task.mappedSO) ; 
        
        int count = 0 ; 
        int wasShipped = 0 ; 

        bool bDone = false ; 
        while (count++ < 4 && !bDone) 
        {
            try
            {
                CSQLRecordset rs(gParms.evp.m_db) ;
                rs << qry ; 
                rs.SQLExec() ;
                while (rs.SQLFetch())
                {
                    retcode |= 0x01 ; 
                    csString ordnum   = rs.SQLGetData(1).c_str() ;
                    csString status = rs.SQLGetData(2).c_str() ;
                    ordnum.Trim() ;
                    status.Trim() ; 

                    if (ordnum.size() == 0)
                    {
                        wasShipped = -1 ; // error condition
                    }
                    else 
                    {
                        if (status[0] == 'C')
                        {
                            retcode |= 0x02 ; 
                            wasShipped = 1 ; 
                        }
                    }
                    bDone = true ; 
                }
            }
            catch (CSQLException* e)
            {
                csString str = e->m_strError.c_str() ;
                // char msg[4096] ; 
                // _snprintf(msg, 4096, "SQL error %d getting max SO number\n MSG: %s\n", 
                //     (int)e->m_nRetCode, e->m_strError.c_str()) ; 
                // LogError(msg) ; 
            }
            
            if (!bDone)
                Sleep(250) ; 
        }
    }
    else
    {

        char qry[2048] ; 
        sprintf(qry, "SELECT ordernumber, shipdate FROM d_order WHERE ordernumber=%d", task.mappedSO) ; 
        
        int count = 0 ; 
        int wasShipped = 0 ; 

        bool bDone = false ; 
        while (count++ < 4 && !bDone) 
        {

            try
            {
                CSQLRecordset rs(db) ;
                rs << qry ; 
                rs.SQLExec() ;
                while (rs.SQLFetch())
                {
                    retcode |= 0x01 ; 
                    csString ordnum   = rs.SQLGetData(1).c_str() ;
                    csString shipdate = rs.SQLGetData(2).c_str() ;
                    ordnum.Trim() ;
                    shipdate.Trim() ; 

                    if (ordnum.size() == 0)
                    {
                        wasShipped = -1 ; // error condition
                    }
                    else 
                    {
                        if (shipdate.size() > 0)
                        {
                            retcode |= 0x02 ; 
                            wasShipped = 1 ; 
                        }
                    }
                    bDone = true ; 
                }
            }
            catch (CSQLException* e)
            {
                csString str = e->m_strError.c_str() ;
                // char msg[4096] ; 
                // _snprintf(msg, 4096, "SQL error %d getting max SO number\n MSG: %s\n", 
                //     (int)e->m_nRetCode, e->m_strError.c_str()) ; 
                // LogError(msg) ; 
            }
            
            if (!bDone)
                Sleep(250) ; 
        }
    }

    return retcode ;
}

int ValidTokChars(char *ts)
{
    if (!ts)
        return 0 ; // error
    while (*ts)
    {
        if (*ts >= 32 && *ts < 123)
            ts++ ; 
        else
            return 0 ;  // bad character
    }
    return 1; // OK
}

int TaskRec::NextTaskToken(csString &line, csString &tok, int len) 
{
    tok = line.NextToken("|") ; 
    if (!ValidTokChars(tok.str))
        return -1 ; 
    tok.Trim() ;
    tok.ToUpper() ; 

    if (tok.size() == 0 || 
        (len > 0 && tok.size() != len))
    {   // Cannot be zero length, or if len defined, 
        // must be exactly len characters long 
        return -1 ; 
    }

    return 0 ; 
}

int TaskRec::ParseString(char *buf)
{
    memset(this, 0, sizeof(TaskRec)) ; 

    csString line(buf) ; 
    line.Trim() ; 
    line.idx = 0 ;
    csString tok ; 
    
    if (NextTaskToken(line, tok))
        return -22 ; 

    if (tok == "TASK")
        mode = STANDARD ; 
    else if (tok == "FORCE") 
        mode = FORCE ; 
    else if (tok == "RUNTIME") 
        mode = RUNTIME ; 
    else if (tok == "TBLANK") 
        mode = TBLANKS ; 
    else if (tok == "PICK") 
        mode = PICKPRT ; 
    else if (tok == "SAW") 
        mode = SAWMODE ; 
    else 
        return TASK_ERR_TYPE ; // error in the data line. 


    if (mode & TBLANKS)
    {
        // ------------ EMPLOYEE NUMBER ------------
        if (NextTaskToken(line, tok, 5))
        {
            if (tok.size() == 0)
                return TASK_ERR_TB_EMP ;
            empnum = 99999 ; // else default to the anybody employee number
        }
        else 
        {   // Then the number is possibly valid so use it
            empnum = atoi(tok.c_str()) ; 
        }

        // ------------    PART NUMBER  ------------
        if (NextTaskToken(line, tok))
            return TASK_ERR_TB_PART ;
        strncpy(part, tok.c_str(), 30) ; 

        // ------------    QUANTITY     ------------
        if (NextTaskToken(line, tok))
            return TASK_ERR_TB_QTY ;
        qty = atoi(tok.c_str()) ; 

        // ------------    SERIAL #     ------------
        if (NextTaskToken(line, tok))
            return TASK_ERR_TB_SERNUM ;
        strncpy(serNumStr, tok.c_str(), 30) ; 

        // ------------    STATION      ------------
        if (NextTaskToken(line, tok))
            return TASK_ERR_TB_STATION ; 
        strncpy(station, tok.c_str(), 12) ; 

        // ------------    DATE TIME ------------
        if (NextTaskToken(line, tok, 14))
            return TASK_ERR_TB_TIME ;

        CDateTime dt ; 
        dt.SetDateTime(tok.c_str()) ; 
        year    = dt.m_nYear ; 
        month   = dt.m_nMonth ;
        day     = dt.m_nDay ; 
        hour    = dt.m_nHours ; 
        mins    = dt.m_nMins ; 
        secs    = dt.m_nSecs ; 
        
        return 0 ;
    }
    else if (mode & PICKPRT)
    {
        // ------------ EMPLOYEE NUMBER ------------
        if (NextTaskToken(line, tok, 5))
        {
            if (tok.size() == 0)
                return TASK_ERR_TB_EMP ;
            empnum = 99999 ; // else default to the anybody employee number
        }
        else 
        {   // Then the number is possibly valid so use it
            empnum = atoi(tok.c_str()) ; 
        }

        // ------------    PART NUMBER  ------------
        if (NextTaskToken(line, tok))
            return TASK_ERR_TB_PART ;
        sonum = atoi(tok.c_str()) ; 
        part[0] = tok.Right(1)[0] ; 
        part[1] = 'P' ; 
        part[2] = 0 ; 

        // ------------    MATERIAL STOCK ------------
        if (NextTaskToken(line, tok))
            return TASK_ERR_TB_MTL ;
        strncpy(mtl, tok.c_str(), 40) ; 

        // ------------    SERIAL #     ------------
        if (NextTaskToken(line, tok))
            return TASK_ERR_TB_SERNUM ;
        strncpy(serNumStr, tok.c_str(), 30) ; 

        // ------------    STATION      ------------
        if (NextTaskToken(line, tok))
            return TASK_ERR_TB_STATION ; 
        strncpy(station, tok.c_str(), 12) ; 

        // ------------    DATE TIME ------------
        if (NextTaskToken(line, tok, 14))
            return TASK_ERR_TB_TIME ;

        CDateTime dt ; 
        dt.SetDateTime(tok.c_str()) ; 
        year    = dt.m_nYear ; 
        month   = dt.m_nMonth ;
        day     = dt.m_nDay ; 
        hour    = dt.m_nHours ; 
        mins    = dt.m_nMins ; 
        secs    = dt.m_nSecs ; 
        
        return 0 ;
    }


    tok = line.NextToken("|") ; 
    if (!ValidTokChars(tok.str))
        return -22; 
    tok.Trim() ;
    if (tok.size())
    {   // Must be at least 5 characters long for the SO#
        if (tok.size() < 5)
            return -20 ; // ignore this record. Test or bad data.
        sonum = atoi(tok.c_str()) ; 
    }
    else
        return TASK_ERR_SONUM ; // SO# error

    tok = line.NextToken("|") ; 
    if (!ValidTokChars(tok.str))
        return -22; 
    tok.Trim() ;

    if (tok.size())
        empnum = atoi(tok.c_str()) ; 
    else
    {
        empnum = 99999 ; // 
        // return -3 ; // Emp# error
    }

    tok = line.NextToken("|") ; 
    if (!ValidTokChars(tok.str))
        return -22; 
    tok.Trim() ;

    if (tok.size() != 4)
        return TASK_ERR_TASKCODE ; // error in the length of the task and part code combination
    task[0] = tok[0] ; 
    task[1] = tok[1] ; 
    task[2] = 0 ; 

    part[0] = tok[2] ; 
    part[1] = tok[3] ; 
    part[2] = 0 ; 

    if (mode & SAWMODE)
    {
        tok = line.NextToken("|") ; 
        if (!ValidTokChars(tok.str))
            return -22; 
        tok.Trim() ;

        if (tok.size() == 0)
            return -22 ; // data error

        CS_strmaxcpy(serNumStr, tok.c_str(), 16) ; 
    }

    tok = line.NextToken("|") ; 
    if (!ValidTokChars(tok.str))
        return -22; 
    tok.Trim() ;

    if (mode == RUNTIME)
    {   // Then extract the hours and minutes values
        /* 
            The format is either 
                    HHHMM  or HHH:MM  or HHH.MM
            
            where any number of leading characters is possible. 

            If the colon or period separate exists then the leading digits
            are taken as hours no matter how many characters are present. 

            The final total runtime is saved in seconds in the secs variable. 
            All the other values can be ignored. 
         */
        month = day  = year = 0 ; 
        hour = mins = secs = 0 ; 

        tok.RemoveSpaces() ; 
        char *psep = tok.FindOneOf(":.,;") ; // allow for any type of realistic separator
        if (psep)
        {   // Then we have a separator character
            *psep = 0 ; 
            psep++ ; 
            hour = atoi(tok.str) ; 
            mins = atoi(psep) ; 
        }
        else
        {   // Just one long number
            mins = atoi(tok.str) ; 
            hour = mins / 100 ; 
            mins = mins % 100 ; 
        }
        secs = hour * 3600 + mins * 60 ; 
        if (secs > 1000000)
            return -10 ; 
    }
    else if (tok.size() >= 16)
    {
        month = atoi(tok.str) ; 
        day   = atoi(tok.str + 3) ;   
        year  = atoi(tok.str + 6) ;   

        hour  = atoi(tok.str + 11) ;   
        mins  = atoi(tok.str + 14) ;   
        secs = 0 ; 
        if (tok.size() == 19)
        {
            secs = atoi(tok.str + 17) ;   
        }

        CDateTime dtime(year, month, day, hour, mins, secs) ; 
        tasktime = dtime.GetTimeT() ; 

        if ((month < 0) || 
            (month > 12) || 
            (year < 2000) || (year > 3000) ||
             (day < 1) || (day > 31) || 
             (hour < 0) || (hour > 23) || 
             (mins > 60) || (secs > 60))
        {
            return TASK_ERR_TIME ;// time erroro
        }
    }
    else if (tok == "NOW")
    {   // Then simply use the current machine time. 
        CDateTime dtime ; 
        dtime.SetNow() ; 
        tasktime = dtime.GetTimeT() ; 

        year  = dtime.m_nYear ; 
        month = dtime.m_nMonth ; 
        day   = dtime.m_nDay ; 
 
        hour  = dtime.m_nHours ; 
        mins  = dtime.m_nMins ; 
        secs =  dtime.m_nSecs ;
    }
    else
    {
        return -5 ; // error in the date time string
    }

    tok = line.NextToken("|") ; 
    if (!ValidTokChars(tok.str))
        return -22; 
    tok.Trim() ;

    if (tok.size())
        CS_strmaxcpy(station, tok.c_str(), 5) ; 
    else
        return TASK_ERR_STATION ; // Station error

    if (tok.size() > 5)
        return TASK_ERR_STATION2 ; // station code is too long. 

    return 0 ; 

}

// NOTE THIS FUNCTION CAN BE REMOVED ONCE THE DECADE ORDERS HAVE ALL BEEN 
// CLEARED OUT OF THE SYSTEM
void TransitionCheck(int &mappedSO)
{
    /*
    if (gParms.plantMode == PLANT_EXCO)
    {
        if (mappedSO > 250000)
        {
            mappedSO -= 100000 ; 
        }
    }
    else if (gParms.plantMode == PLANT_ALUDIE)
    {
        if (mappedSO > 270000 && mappedSO < 400000)
        {
            mappedSO -= 300000 ; 
        }
    }
    else if (gParms.plantMode == PLANT_USA)
    {
        if (mappedSO > 530000 && mappedSO < 600000)
        {
            mappedSO -= 500000 ; 
        }
        else if (mappedSO > 630000)
        {   // Not sure if we need this if statement since not really sure 
            // what current Michigan SO#'s are. 
            mappedSO -= 600000 ; 
        }
    }
    */
}

//! Don't do database check, simply map the record. 
int MappedSONUM(int inputSO) 
{
    if (gParms.plantMode == PLANT_ALUDIE)
    {   // Do not map AluDie data. 
        return inputSO ; 
    }


    if (gParms.evp.bBatchMode)
    {
        return CMSMappedSONUM(inputSO) ; 
    }

    if (inputSO > 210000 && inputSO < 900000)
        return inputSO ; 

    int retcode = 0 ; 
    int mappedSO = inputSO ; 

    int maxSO = gParms.nLastMax ; 

    // TODO - optimize this 
        
    if (maxSO > 0)
    {   // Then we read back a valid order number so map things based 
        // on the value of this order number
    
        /*
        If N is the shop order number and M  = N % 100000 such that
        M is the modulo value that the shop enters and uses to track
        the job, then we have the following:
        */
    
        int SON = 0 ; 
        int M = mappedSO % 100000 ; // get it in range just in case. 
        int maxPRE = maxSO - (maxSO % 100000) ; // this is the current prefix 
        
        int modMax = maxSO % 100000 ; 
        if (modMax < 50000)
        {   // Then we may have just wrapped to the next 
            // set of 100k values
            if (M < 50000)
            {   // Then map it normally
                SON = maxPRE + M ; // use the same base prefix
            }
            else 
            {   // The working SO hasn't ticked up to next 100k block yet. 
                if (maxPRE > 0)
                {   // Thus shift it back one block
                    SON = maxPRE - 100000 + M ; 
                }
                else
                {   // This would be an error condition
                    // sprintf(qry, "SO# %d is out of range since current max order#=%d\n", 
                    //     evd.sonum, maxSO) ; 
                    // LogError(qry) ; 
                    retcode = -10 ; 
                }
            }
        }
        else
        {   // Else the current number is closer to the high end. 
            if (modMax < 50000)
            {   // This would be an error condition, should never get an
                // S.O. number in this range. 
                // sprintf(qry, "SO# %d is out of range since current max order#=%d\n", 
                //     evd.sonum, maxSO) ; 
                // LogError(qry) ; 
                retcode = -20 ; 
            }
            else
            {   // Just have to map normally. 
                SON = maxPRE + M ; 
            }
        }
    
        mappedSO = SON ; 
    }

    TransitionCheck(mappedSO) ;
    return mappedSO ; 
}

//! Do full database lookup during mapping. 
int MappedSONUM(CSQLDatabase &db, int inputSO) 
{
    // note on the first run through soMaxCount must be 0 so that the full
    // database processing is done. 
    if ((gParms.soMaxCount++ & 0x00ff))
    {   // Then don't hit the database
        return MappedSONUM(inputSO) ; 
    }

    if (gParms.plantMode == PLANT_ALUDIE)
    {   // Do not map AluDie data. 
        return inputSO ; 
    }

    if (gParms.evp.bBatchMode)
    {
        return CMSMappedSONUM(inputSO) ; 
    }

    if (inputSO > 210000 && inputSO < 900000)
        return inputSO ; 

    char qry[2048] ; 
    sprintf(qry, "SELECT TOP 1 ordernumber FROM d_order ORDER BY ordernumber DESC") ; 
    
    int retcode = 0 ; 
    int mappedSO = inputSO ; 

    bool bNotDone = true ; 
    int count = 0 ; 
    while (count++ < 4 && bNotDone) 
    {

        try
        {
            CSQLRecordset rs(db) ;
            rs << qry ; 
            int maxSO = 0 ;
            rs.SQLExec() ;
            while (rs.SQLFetch())
            {
                csString ordnum = rs.SQLGetData(1).c_str() ;
                ordnum.Trim() ;
                maxSO = atoi(ordnum.c_str()) ; 
                
                // Save the current maximum SO#
                gParms.nLastMax = maxSO ; 

                bNotDone = false ; 
            }
        
            if (maxSO > 0)
            {   // Then we read back a valid order number so map things based 
                // on the value of this order number
            
                /*
                If N is the shop order number and M  = N % 100000 such that
                M is the modulo value that the shop enters and uses to track
                the job, then we have the following:
                */
            
                int SON = 0 ; 
                int M = mappedSO % 100000 ; // get it in range just in case. 
                int maxPRE = maxSO - (maxSO % 100000) ; // this is the current prefix 
                
                //! Save the prefix for processing later. 
                gParms.nLastPrefix = maxPRE ; 

                int modMax = maxSO % 100000 ; 
                if (modMax < 50000)
                {   // Then we may have just wrapped to the next 
                    // set of 100k values
                    if (M < 50000)
                    {   // Then map it normally
                        SON = maxPRE + M ; // use the same base prefix
                    }
                    else 
                    {   // The working SO hasn't ticked up to next 100k block yet. 
                        if (maxPRE > 0)
                        {   // Thus shift it back one block
                            SON = maxPRE - 100000 + M ; 
                        }
                        else
                        {   // This would be an error condition
                            // sprintf(qry, "SO# %d is out of range since current max order#=%d\n", 
                            //     evd.sonum, maxSO) ; 
                            // LogError(qry) ; 
                            retcode = -10 ; 
                        }
                    }
                }
                else
                {   // Else the current number is closer to the high end. 
                    if (modMax < 50000)
                    {   // This would be an error condition, should never get an
                        // S.O. number in this range. 
                        // sprintf(qry, "SO# %d is out of range since current max order#=%d\n", 
                        //     evd.sonum, maxSO) ; 
                        // LogError(qry) ; 
                        retcode = -20 ; 
                    }
                    else
                    {   // Just have to map normally. 
                        SON = maxPRE + M ; 
                    }
                }
            
                mappedSO = SON ; 
            }
            break ; 
        }
        catch (CSQLException* e)
        {
            csString str = e->m_strError.c_str() ;
            // char msg[4096] ; 
            // _snprintf(msg, 4096, "SQL error %d getting max SO number\n MSG: %s\n", 
            //     (int)e->m_nRetCode, e->m_strError.c_str()) ; 
            // LogError(msg) ; 
            db.Reconnect() ; 
        }
    }

    TransitionCheck(mappedSO) ;
    return mappedSO ; 
}


int CMSMappedSONUM(int inputSO) 
{
    if (inputSO > 210000 && inputSO < 900000)
        return inputSO ; 

    char qry[2048] ; 
    sprintf(qry, "select DCORD#  from prodtest.ocrh  where DCORD# < 400000 ORDER BY DCORD# DESC FETCH FIRST 1 ROWS ONLY ") ; 
    
    int retcode = 0 ; 
    int mappedSO = inputSO ; 

    CSQLDatabase *pdb = &(gParms.evp.m_db) ; 

    bool bNotDone = true ; 
    int count = 0 ; 
    while (count++ < 4 && bNotDone) 
    {

        try
        {
            CSQLRecordset rs(*pdb) ;
            rs << qry ; 
            int maxSO = 0 ;
            rs.SQLExec() ;
            while (rs.SQLFetch())
            {
                csString ordnum = rs.SQLGetData(1).c_str() ;
                ordnum.Trim() ;
                maxSO = atoi(ordnum.c_str()) ; 
                
                // Save the current maximum SO#
                gParms.nLastMax = maxSO ; 

                bNotDone = false ; 
            }
        
            if (maxSO > 0)
            {   // Then we read back a valid order number so map things based 
                // on the value of this order number
            
                /*
                If N is the shop order number and M  = N % 100000 such that
                M is the modulo value that the shop enters and uses to track
                the job, then we have the following:
                */
            
                int SON = 0 ; 
                int M = mappedSO % 100000 ; // get it in range just in case. 
                int maxPRE = maxSO - (maxSO % 100000) ; // this is the current prefix 
                
                //! Save the prefix for processing later. 
                gParms.nLastPrefix = maxPRE ; 

                int modMax = maxSO % 100000 ; 
                if (modMax < 50000)
                {   // Then we may have just wrapped to the next 
                    // set of 100k values
                    if (M < 50000)
                    {   // Then map it normally
                        SON = maxPRE + M ; // use the same base prefix
                    }
                    else 
                    {   // The working SO hasn't ticked up to next 100k block yet. 
                        if (maxPRE > 0)
                        {   // Thus shift it back one block
                            SON = maxPRE - 100000 + M ; 
                        }
                        else
                        {   // This would be an error condition
                            // sprintf(qry, "SO# %d is out of range since current max order#=%d\n", 
                            //     evd.sonum, maxSO) ; 
                            // LogError(qry) ; 
                            retcode = -10 ; 
                        }
                    }
                }
                else
                {   // Else the current number is closer to the high end. 
                    if (modMax < 50000)
                    {   // This would be an error condition, should never get an
                        // S.O. number in this range. 
                        // sprintf(qry, "SO# %d is out of range since current max order#=%d\n", 
                        //     evd.sonum, maxSO) ; 
                        // LogError(qry) ; 
                        retcode = -20 ; 
                    }
                    else
                    {   // Just have to map normally. 
                        SON = maxPRE + M ; 
                    }
                }
            
                mappedSO = SON ; 
            }
            break ; 
        }
        catch (CSQLException* e)
        {
            csString str = e->m_strError.c_str() ;
            // char msg[4096] ; 
            // _snprintf(msg, 4096, "SQL error %d getting max SO number\n MSG: %s\n", 
            //     (int)e->m_nRetCode, e->m_strError.c_str()) ; 
            // LogError(msg) ; 
            pdb->Reconnect() ; 
        }
    }

    TransitionCheck(mappedSO) ;
    return mappedSO ; 
}


