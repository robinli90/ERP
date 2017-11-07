#include "stdafx.h"
#include "BatchUPD.h"
#include "BatchUPDDlg.h"



int CBatchUPDApp::LoadBatchIDList(csString &batchIDlist) 
{
    batchIDlist.clear() ; 

    /* 
        Grab the set of all batches that have been shifted out this morning in a time 
        window of 4AM to Now (so greater than 4AM today, where 4AM defines the earliest
        possible start time for a new day). Also ignore any new jobs started today, there
        really shouldn't be any of these but just in case. 

        Then any record that is included in those batches can be ignored for the purposes
        of the second query which will produce the list of all active batch records. 

     */

    CDateTime dtfrom, dtto; 
	//dtto= CDate(m_FromTime.GetYear(), m_FromTime.GetMonth(), m_FromTime.GetDay());
    dtto.SetNow() ; 
    time_t t ;
    t = dtto.GetTimeT() ;
    t -= 2500000 ; 
    dtfrom.SetTime(t) ; 
    
    char qry[256] ;

    char datefrom[64], timefrom[64] ;
    char dateto[64],   timeto[64] ;

    dtfrom.FormatDate(datefrom) ; 
    strcpy(timefrom, "00.00.01") ;

    dtto.FormatDate(dateto) ; 
    strcpy(timeto, "04.00.00") ; 

    // This query will load all the 10001 events for the currently active batches
    /*
        This is the old method based on SFTX which potentially would miss 
        certain batches 

    _snprintf(qry, 16000,
        "SELECT Q4BTID FROM %s.SFTX"
        " WHERE Q4CDAT >= '%s' AND Q4CTIM > '%s'"
        " AND Q4FTCD IN(10000,10001,10002,10003,10004,10005,10100)",
            gCMSparms.dbname, datestr, timestr) ;
        */

    // Load all batches that have not been posted yet
    // _snprintf(qry, 250,
    //     "SELECT NWBTID FROM %s.RPRH WHERE NWPOST = 'N'"
    //     " AND ((NWCDAT > '%s' AND NWCDAT < '%s') OR (NWCDAT = '%s' AND NWCTIM < '%s'))"
    //     " AND NWPLNT = '%s'",
    //                 gCMSparms.dbname, datefrom, dateto, dateto, timeto, 
    //                 gCMSparms.plantID) ;

    _snprintf(qry, 250,
            "SELECT NWBTID FROM %s.RPRH WHERE NWPOST = 'N' AND NWCDAT > '%s'"
            " AND NWPLNT = '%s'",
                    gCMSparms.dbname, datefrom, gCMSparms.plantID) ;


    int retcode = 0 ; 

    try
    {
        CSQLRecordset rs(cmsdata.m_db) ;
        rs << qry ; 
        rs.SQLExec();
        while (rs.SQLFetch())
        {
            int fldnum = 1 ; 
            // Field 1 - DEPARTMENT
            csString bid = rs.SQLGetData(fldnum++).c_str() ; 
            bid.Trim() ; 

            if (batchIDlist.size())
                batchIDlist += "," + bid ; 
            else
                batchIDlist += bid ; 
        }
    }
    catch (CSQLException* e)
    {
        if (gCMSparms.pevp->fpLOG)
        {
            fprintf(gCMSparms.pevp->fpLOG, "SQL error %d reading back the active batch list:\n%s\n",
                        (int)e->m_nRetCode, e->m_strError.c_str()) ;
            fflush(gCMSparms.pevp->fpLOG) ;
        }
        batchIDlist.clear() ; 
        retcode = -1 ; 
    }

    return retcode ; 
}

    
// This isn't used anymore
void CBatchUPDDlg::LoadJobListByDept(csString &batchIDlist)
{

    CBatchUPDApp *pApp = (CBatchUPDApp *)AfxGetApp() ; 
    char tmpstr[256] ; 

    // CCombBox
    int n = deptCombo.GetCurSel() ;
    csString dept ; 
    if (n >= 0)
    {
        deptCombo.GetLBText(n, tmpstr) ; 
        dept = tmpstr ; 
        dept.Trim() ; 
    }
  
    pApp->LoadBatchIDList(batchIDlist) ;
    ResRecMapItr irr ; 

    if (batchIDlist.size())
    {
        resmap.clear() ; 

        char qry[0x4000] ; 
        _snprintf(qry, 0x3FF0,
            "SELECT Q4DEPT,Q4FTCD,Q4RESC,Q4EMPN,Q4PART,Q4SEQ#,DNORD#,DNJOB,EDOPNM,DNITM#,Q4CDAT,Q4CTIM,Q4BTID FROM"
            " %s.SFTX AS B"
            " LEFT JOIN %s.CJOBH AS A ON B.Q4JOBN = A.DNJOB "
            " LEFT JOIN %s.CJOBDR AS C ON (C.EDJOB# = B.Q4JOBN AND B.Q4SEQ#=C.EDSEQ#) "
            " WHERE B.Q4BTID IN (%s) AND Q4DEPT LIKE '%s%s%%' ORDER BY Q4CDAT,Q4CTIM", 
                gCMSparms.dbname, gCMSparms.dbname, gCMSparms.dbname, 
                batchIDlist.c_str(),
                gCMSparms.plantID,  dept.c_str()) ;

        try
        {
            CSQLRecordset rs(pApp->cmsdata.m_db) ;
            rs << qry ; 
            rs.SQLExec();
            while (rs.SQLFetch())
            {
                BEventRec erec ; 
                erec.empnum = 0 ; 
                erec.bHas40005 = 0 ; 

                int fldnum = 1 ; 
                // Field 1 - DEPARTMENT
                erec.dept = rs.SQLGetData(fldnum++).c_str() ; 
                erec.dept.Trim() ; 
                // Field 2 - EVENT CODE
                erec.event = atoi(rs.SQLGetData(fldnum++).c_str()) ; 
                // Field 3 - RESOURCE CODE
                erec.resource = rs.SQLGetData(fldnum++).c_str() ; 
                erec.resource.Trim() ; 
                // Field 4 - EMPLOYEE NUMBER
                erec.empnum = atoi(rs.SQLGetData(fldnum++).c_str()) ; 
                // Field 5 - PART CODE
                erec.part = rs.SQLGetData(fldnum++).c_str() ; 
                erec.part.Trim() ; 
                // Field 6 - SEQUENCE NUMBER
                erec.seqnum = atoi(rs.SQLGetData(fldnum++).c_str()) ; 
                // Field 7 - ORDER NUMBER
                erec.ordnum = atoi(rs.SQLGetData(fldnum++).c_str()) ; 
                // Field 8 - JOB NUMBER
                erec.jobnum = rs.SQLGetData(fldnum++).c_str() ; 
                erec.jobnum.Trim() ; 
                // Field 9 - JOB NUMBER
                erec.opercode = rs.SQLGetData(fldnum++).c_str() ; 
                erec.opercode.Trim() ; 
                // Field 10 - ITEM NUMBER
                erec.itemNumber = atoi(rs.SQLGetData(fldnum++).c_str()) ; 

                // Field 11 - DATE AND TIME
                csString datetime = csString(rs.SQLGetData(fldnum++).c_str()) + " " ; 
                datetime += csString(rs.SQLGetData(fldnum++).c_str()) ; 

                struct tm tmval ; 
                CSQL_ConvertTime(datetime.c_str(), tmval) ; 
                erec.dt.SetDateTime(&tmval) ; 

                // Field 12 - BATCH ID NUMBER
                erec.batchID = atoi(rs.SQLGetData(fldnum++).c_str()) ; 

                irr = resmap.find(erec.resource) ; 
                if (irr == resmap.end())
                {   // Then add the resource to the map
                    ResRec rr ; 
                    rr.res = erec.resource ; 
                    rr.lastEvent = erec.event ; 

                    pair<ResRecMapItr, bool> ins ; 
                    ins = resmap.insert(make_pair(erec.resource, rr)) ; 

                    if (ins.second)
                    {
                        irr = ins.first ; 
                        irr->second.evvec.push_back(erec) ; 
                    }
                    
                }
                else
                {
                    irr->second.evvec.push_back(erec) ; 
                }

            }
        }
        catch (CSQLException* e)
        {
            if (gCMSparms.pevp->fpLOG)
            {
                fprintf(gCMSparms.pevp->fpLOG, "SQL error %d loading department codes:\n%s\n",
                            (int)e->m_nRetCode, e->m_strError.c_str()) ;
                fflush(gCMSparms.pevp->fpLOG) ; 
            }
            return ; 
        }
    }


    // For each resource work through all the active jobs on that resource 
    // and collect the start/stop times against the resource. 

    int i ; 
    jobmap.clear() ; 
    for (irr = resmap.begin(); irr != resmap.end(); irr++)
    {
        ResRec *prr = &(irr->second) ; 
        prr->lastJob = 0 ; // initialize 

        for (i=0; i < (int)prr->evvec.size(); i++)
        {
            if (prr->evvec[i].event == 10151)
            {   // Must stop the clock on the current job if one exists
                // See what the current job is on this resource
                if (prr->lastJob != prr->evvec[i].jobnum)
                {
                    JobRecMapItr ijm = jobmap.find(prr->lastJob) ; 
                    if (ijm != jobmap.end())
                    {
                        if (ijm->second.state & JOBSTATE_RUN)
                        {   // Then stop the previous job
                            ijm->second.state = JOBSTATE_DOWN ; 
                            int secs = prr->evvec[i].dt - ijm->second.lasttime ;
                            double mins = secs / 60.0 ; 
                            ijm->second.totalTime +=  mins ; 
                            ijm->second.lasttime = prr->evvec[i].dt ; 
                        }
                    }
                }

                prr->lastJob = prr->evvec[i].jobnum ; 
                StartJobClock(prr->evvec[i]) ;
            }
            else if (prr->evvec[i].event == 10100)
            {
                StopJobClock(prr->lastJob, prr->evvec[i]) ;
            }
            else if (prr->evvec[i].event == 40005)
            {
                JobRecMapItr ijm = jobmap.find(prr->evvec[i].jobnum) ; 
                if (ijm != jobmap.end())
                {
                    ijm->second.b40005 = 1 ;
                }
                else
                {   // Initialize a job record, but attach zero time to it despite
                    // reporting production of one unit. 
                    JobRec *pj = InitJobRec(prr->evvec[i]) ; 
                    pj->state = JOBSTATE_UNKNOWN ; 
                    pj->lasttime = prr->evvec[i].dt ; 
                    pj->evtid = prr->evvec[i].event ; 
                    ijm->second.b40005 = 1 ;
                }
                // else error
            }

            // Theoretically the 40005 should stop the clock as well, but according 
            // to Chris Braznick it will not. Still need to verify this for certain. 
            // If Chris is right, then the 40005 enhancement was a complete waste of
            // money since that was the entire point behind the enhancement, and it
            // could be argued that Solarsoft could be sued for wasting our time and
            // money. 
        }
    }
    


    // Now go through and list those jobs which are still active. 
    // Set the time to 5:00 AM, anything before this is considered to have happened in the 
    // previous shift. 
    CDateTime dtnow ; 
	
    dtnow.SetNow() ; 
    dtnow.SetTime(4,0,0) ; 

    // Initialize the grid
    int nCols = 7 ;
    m_grid.Clear() ; 

    for(i = 0; i < nCols; i++)
    {   // Set the text alignment in the columns
        m_grid.put_ColAlignment(i, CMsflexgrid1::flexAlignLeftCenter) ;
    }


    m_grid.put_ColWidth(0,750) ; // width in pico points or something like that
    m_grid.put_ColWidth(1,1500) ;
    m_grid.put_ColWidth(2,700) ;
    m_grid.put_ColWidth(3,700) ;
    m_grid.put_ColWidth(4,600) ; // SEQ#
    m_grid.put_ColWidth(5,900) ; // Job#
    m_grid.put_ColWidth(6,1200) ;
    m_grid.put_ColWidth(7,900) ;
    m_grid.put_ColWidth(8,900) ;

    // Order#, Part#, Machine, Status, Start Time, RunTime, Actual
    // Row, column, text
    m_grid.put_TextMatrix(0,0,"SO#") ;
    m_grid.put_TextMatrix(0,1,"PART") ;
    m_grid.put_TextMatrix(0,2,"RES") ;
    m_grid.put_TextMatrix(0,3,"Status") ;
    m_grid.put_TextMatrix(0,4,"Seq#") ;
    m_grid.put_TextMatrix(0,5,"Job#") ;
    m_grid.put_TextMatrix(0,6,"StartTime") ;
    m_grid.put_TextMatrix(0,7,"RunTime") ;
    m_grid.put_TextMatrix(0,8,"Actual") ;

    m_grid.put_Rows((long)jobmap.size() + 1) ;

    char soNum[16] ; 
    char seqnum[16] ; 
    char *pstat ; 
    int nrow = 1 ; 

    JobRecMapItr ijm ;
    for (ijm = jobmap.begin(); ijm != jobmap.end(); ijm++)
    {
        char timestr[64] ;
        char runtime[64] ; 
        CDate d ;
        sprintf(timestr, "%s-%d,%02d:%02d",
            d.MonthStringShort(ijm->second.startTime.m_nMonth),
                               ijm->second.startTime.m_nDay, 
                               ijm->second.startTime.m_nHours,
                               ijm->second.startTime.m_nMins) ;

        sprintf(soNum, "%d", ijm->second.sonum) ; 
        sprintf(seqnum, "%03d", ijm->second.seqnum) ; 
        if (ijm->second.state & JOBSTATE_RUN)
            pstat = "RUN" ;
        else if (ijm->second.state & JOBSTATE_DOWN)
            pstat = "DOWN" ; 
        else 
            pstat = "???" ; 

        sprintf(runtime, "%.2f", ijm->second.totalTime) ; 

        m_grid.put_TextMatrix(nrow, 0, soNum) ; 
        m_grid.put_TextMatrix(nrow, 1, ijm->second.part) ; 
        m_grid.put_TextMatrix(nrow, 2, ijm->second.res) ; 
        m_grid.put_TextMatrix(nrow, 3, pstat) ; 
        m_grid.put_TextMatrix(nrow, 4, seqnum) ; 
        m_grid.put_TextMatrix(nrow, 5, ijm->second.jobnum.c_str()) ; 
        m_grid.put_TextMatrix(nrow, 6, timestr) ; 
        m_grid.put_TextMatrix(nrow, 7, runtime) ; 
        m_grid.put_TextMatrix(nrow, 8, "") ; 

        nrow++ ; 
    }

    numRows = nrow ; 
}
