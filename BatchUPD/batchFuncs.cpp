// batchFuncs.cpp - support functions for the batch update processor.

#include "stdafx.h"
#include "BatchUPD.h"
#include "BatchUPDDlg.h"



int CBatchUPDDlg::StopJobClock(csString &lastjobnum, BEventRec &evrec) 
{
    CBatchUPDApp *pApp = (CBatchUPDApp *)AfxGetApp() ; 
    int retcode = 0 ; 

    JobRecMapItr ijm = jobmap.find(lastjobnum) ; 
    if (ijm != jobmap.end())
    {
        JobRec *pj = &(ijm->second) ; 
        if (pj->state & JOBSTATE_RUN)
        {   // This is expected normal state. 
            if (pj->lasttime < evrec.dt) 
            {   // Then calculate the difference and stop the clock
                int ds = evrec.dt - pj->lasttime ;
                double mins = (double)ds / 60.0 ; 
                pj->totalTime += mins ; 
                pj->state = JOBSTATE_DOWN ; 
            }
            else
            {   // Stop occurs before start time so something wrong. 
                char tmpstr[128] ; 
                fprintf(pApp->fplog, 
                    "STOP before START, job=%s, time=%s, part=%s, ord=%d\n", 
                            evrec.jobnum.c_str(), 
                            evrec.dt.FormatDateTimeSecs(tmpstr),
                            evrec.part.c_str(), 
                            evrec.ordnum) ; 

                retcode = 2 ; 
            }
        }
        else if (pj->state & (JOBSTATE_DOWN | JOBSTATE_IDLE))
        {
            char tmpstr[128] ;
            char tmpstr2[128] ; 
            fprintf(pApp->fplog, 
                "Already in STOP state, job=%s, time=%s, laststop=%s, part=%s, ord=%d\n", 
                        evrec.jobnum.c_str(), 
                        evrec.dt.FormatDateTimeSecs(tmpstr),
                        ijm->second.lasttime.FormatDateTimeSecs(tmpstr2),
                        evrec.part.c_str(), 
                        evrec.ordnum) ; 
            retcode = 3 ; 
        }
    }
    else
    {   // No job exists
        // Can't really get here since the 10100 event doesn't have a jobnumber
        // associated with it. 
        retcode = 4 ;
    }

    return retcode ; 
}


int CBatchUPDDlg::StartJobClock(BEventRec &evrec) 
{
    CBatchUPDApp *pApp = (CBatchUPDApp *)AfxGetApp() ;

    // BEventRec
    int retcode = 0 ;
    JobRecMapItr ijm = jobmap.find(evrec.jobnum) ;
    if (ijm != jobmap.end())
    {
        JobRec *pj = &(ijm->second) ;
        if (pj->state & JOBSTATE_RUN)
        {   // Ignore this, but log the duplicate logging
            char tmpstr[128] ;
            char tmpstr2[128] ;

            fprintf(pApp->fplog, 
                "RUN when in RUN state, job=%s, time=%s, laststop=%s, part=%s, ord=%d\n", 
                    evrec.jobnum.c_str(), 
                    evrec.dt.FormatDateTimeSecs(tmpstr),
                    ijm->second.lasttime.FormatDateTimeSecs(tmpstr2),
                    evrec.part.c_str(), 
                    evrec.ordnum) ; 
            retcode = 2 ; 
        }
        else 
        {   // No matter what the state is simply start things. This 
            // is normal behaviour. 
            pj->state = JOBSTATE_RUN ; 
            pj->lasttime = evrec.dt ; 
            pj->evtid = evrec.event ; 
            if (pj->startTime.m_nYear == 0)
                pj->startTime = evrec.dt ; 

            CS_strmaxcpy(pj->res, evrec.resource.c_str(), 12) ; 
            if (pj->batchid != evrec.batchID)
            {
                char tmpstr[128] ; 
                fprintf(pApp->fplog,
                    "BATCHID mistmatch, job=%s, time=%s, ord=%d, batch1=%d  batch2=%d\n", 
                        evrec.jobnum.c_str(), 
                        evrec.dt.FormatDateTimeSecs(tmpstr),
                        evrec.ordnum,
                        pj->batchid, 
                        evrec.batchID) ; 

            }
                
            retcode = 0 ; 
        }
    }
    else
    {   // No job exists
        // So add it to the jobmap
        JobRec *pj = InitJobRec(evrec) ; 
        pj->state = JOBSTATE_RUN ; 
        pj->lasttime = evrec.dt ; 
        pj->evtid = evrec.event ; 

        retcode = 0 ;
    }

    return retcode ; 
}


JobRec *CBatchUPDDlg::InitJobRec(BEventRec &evrec) 
{
    JobRec jr ; 
    jr.batchid      = evrec.batchID ; 
    jr.evtid        = evrec.event ; 
    jr.jobnum       = evrec.jobnum ; 
    CS_strmaxcpy(jr.res,  evrec.resource.c_str(), 12) ;
    jr.seqnum       = evrec.seqnum ; 
    jr.sonum        = evrec.ordnum ; 
    jr.lasttime     = evrec.dt ; 
    CS_strmaxcpy(jr.dept, evrec.dept.c_str(), 6) ;
    CS_strmaxcpy(jr.part, evrec.part.c_str(), 20) ; 
    jr.totalTime    = 0.0 ;
    jr.startTime.m_nYear = 0 ; // initialize to undefined.
    jr.b40005 = 0 ; 
    jr.bModified = 0 ; 
    jr.actualTime = 0.0 ; 
    
    jr.state = JOBSTATE_UNKNOWN ; 
    if (evrec.event == 10151)
    {
        jr.state = JOBSTATE_RUN ; 
        jr.startTime = evrec.dt ; 
    }
    else if (evrec.event == 10100)
    {
        jr.state = JOBSTATE_DOWN ; 
    }

    pair<JobRecMapItr, bool> ijm ; 
    
    ijm = jobmap.insert(make_pair(evrec.jobnum, jr)) ; 
    if (ijm.second)
    {
        return &(ijm.first->second) ; 
    }
    return 0 ; 
}


void ResJobXRef::SetKey(int seqnum)
{
    char tmpstr[128] ; 
    memset(tmpstr, 0x20, 100) ; 

    if (seqnum > 0)
    {   //            1111111111222222222233333333334444444444
        //  01234567890123456789012345678901234567890123456789
        //  RRRRRRRRSSSJJJJJJJJJJJJJJJJJJJJ
        StrCpyBlankFill(tmpstr,  res.c_str(), 8) ; 
        sprintf(tmpstr+8, "%03d", seqnum) ; 
        StrCpyBlankFill(tmpstr+11,  job.c_str(), 20) ; 
        tmpstr[31] = 0 ; 
    }
    else
    {
        StrCpyBlankFill(tmpstr,  res.c_str(), 8) ; 
        StrCpyBlankFill(tmpstr+8,  job.c_str(), 20) ; 
        tmpstr[28] = 0 ; 
    }

    key = tmpstr ; 
}


