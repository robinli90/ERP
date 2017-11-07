// baalBatch.cpp

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





int BaalFileProcessor::ProcessFileBatch(csString &taskfile, time_t taskfiletime) 
{
    int retcode = 0 ; 

    msg.clear() ; 

    csString filePath = AddFile2Path(gParms.taskdir, taskfile) ; 
    char buffer[256] ; 

    time_t fileTime = 0 ; 
    CS_GetFileTime(filePath.c_str(), fileTime) ;


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

    //////////////////////////////////////////////////////////////////////
    // Process the file. 
    // 
    // This is now very straight forward as all the heavy lifting is done 
    // in the BatchUPD program which runs later
    //////////////////////////////////////////////////////////////////////
    //

    buffer[0] = 0 ; 
    csString ln ; 
    int bReadSomeData = false ; 
    try {

        ln.clear() ; 

        while (fgets(buffer, 254, fp))
        {
            ln = buffer ; 
            ln.Trim() ; // input line

            csString tok ; 
            tok = ln.NextToken("|", 0) ; 
            tok.Trim() ; 
            tok.ToUpper() ; 

            if (tok == "HARD")
            {   // For files where the first line is the word HARD, simply suck up all 
                // the remaining lines in the file. 
                do {
                    if (strncmp(buffer, "HARD", 4) != 0)
                        break ; // done

                    csString msg ; 
                    int hardret = 0 ; 
                    if ((hardret=ProcessHardnessRec(*pdb, buffer, msg, fpsql, BATCH_MODE, fileTime)) != 0)
                    {
                        retcode |= 0x04 ; // hardness processing error occured
                        fprintf(fplog, "Error %d processing hardness file '%s'\r\n", 
                                        hardret, filePath.c_str()) ; 
                    }
                    else
                    {   // did something
                        bReadSomeData = 1 ;
                    }
                } while (fgets(buffer, 255, fp)) ;

                break ; // done
            }

            // If we get to here it is some kind of task record
            // Extract out the fields. 
            TaskRec task ; 
            csString line = buffer ; 
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
                    printf("%s\r\n", tmpstr) ; 

                throw BAD_TASK_DATA ; // error processing record
            }


            ///////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////
            // Save task record to the Decade and CMS database as required. 
            ///////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////

            if (!(task.mode & TaskRec::TBLANKS))
            {
                if (task.sonum == 0)
                {
                    char tmpstr[256] ; 
                    _snprintf(tmpstr, 250, "ERROR: invalid SO# processing '%s'", line.c_str()) ; 
                    msg = tmpstr ; 

                    if (!gParms.bNoEcho)
                        printf("%s\r\n", tmpstr) ; 

                    if (fplog)
                    {
                        fprintf(fplog, "%s\r\n", tmpstr) ; 
                        fflush(fplog) ; 
                    }
                    continue ; 
                }

                task.mappedSO = MappedSONUM(*pdb, task.sonum) ; 

                // We now have a valid task record. The next stage is to load it into the database. 
                // If the --tship is set, then ignore shipped records. 
				///use to be valStat = 0
                int valStat = 1 ; 
                if (!task.IsForced())
                {   // Make sure it hasn't been shipped and that it exists as a valid 
                    // order number in the database. 
                    char tmpstr[1024] ; 

                   // valStat = ValidActiveOrder(*pdb, task, EVENTS_OUTPUT_SOLARSOFT) ;

                    if (!valStat)
                    {
                        _snprintf(tmpstr, 250, "ERROR: bad order number processing '%s'", line.c_str()) ; 
                        if (!gParms.bNoEcho)
                            printf("%s\r\n", tmpstr) ; 
                        if (fplog)
                        {
                            fprintf(fplog, "%s\r\n", tmpstr) ; 
                            fflush(fplog) ; 
                        }
                        
                        continue ; 
                    }
                    else if (valStat & 0x02)
                    {
                        if (!gParms.bTrackAfterShipped)
                        {
                            _snprintf(tmpstr, 250, "ERROR: order already shipped processing '%s'", line.c_str()) ; 
                            if (!gParms.bNoEcho)
                                printf("%s\r\n", tmpstr) ; 
                            if (fplog)
                            {
                                fprintf(fplog, "%s\r\n", tmpstr) ; 
                                fflush(fplog) ; 
                            }
                            
                            continue ; 
                        }
                        // else  continue to track the records. 
                        _snprintf(tmpstr,1000, "WARNING (tracking with error): order already shipped processing '%s'", line.c_str()) ; 

                        if (!gParms.bNoEcho)
                            printf("%s\r\n", tmpstr) ; 
                        if (fplog)
                        {
                            fprintf(fplog, "%s\r\n", tmpstr) ; 
                            fflush(fplog) ; 
                        }
                    }
                }
            }


            ////////////////////////////////////////////////////////////////
            //       SAVE RECORD TO DATABASE
            ////////////////////////////////////////////////////////////////
            if (task.mode == TaskRec::RUNTIME)
            {
                task.tasktime = fileTime ; 
                task.filetime = fileTime ; 
            }

            bReadSomeData = 2 ; 
            CS_strmaxcpy(task.plant, gParms.evp.plantID, 7) ; 
            if (!task.SaveToCMSDB(gParms.evp.m_db, fplog))
            {
                printf("Saved '%s' to EXCOTASK\n", ln.c_str()) ; 
                fprintf(fplog, "Saved '%s' to EXCOTASK\n", ln.c_str()) ; 
                fflush(fplog) ; 
            }
            else
            {
                printf("ERROR attempting to write '%s' to EXCOTASK\n", ln.c_str()) ; 
                fprintf(fplog, "ERROR attempting to write '%s' to EXCOTASK\n", ln.c_str()) ; 
                fflush(fplog) ; 
                retcode |= 0x100 ; 
            }
            
            LogTask(retcode, fparchive, fplog, line, msg) ;
        }
    }
    catch(int err)
    {
        printf("Caught Error %x trying to save '%s'\n", err, ln.c_str()) ; 
    }


    if (!bReadSomeData)
    {
        char tmpstr[256] ; 
        _snprintf(tmpstr, 250, "ERROR: empty file '%s'\r\n", filePath.c_str()) ; 
        LogError(tmpstr) ; 
        retcode |= 0x02 ; 
    }

    fclose(fp) ; 

    ArchiveTaskFile(filePath, fplog) ;
    return retcode ; 
}