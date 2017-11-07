// masterList.cpp

#include "stdafx.h"
#include "BatchUPD.h"
#include "BatchUPDDlg.h"
#include <iostream>
#include <fstream>
using namespace std;


int LoadJobDetails(CMSJob *pjob, CCMSDatabase &db, FILE *fplog)
{
    char qry[512] ; 
    try
    {
        _snprintf(qry, 500, 
            "SELECT DNPART,DNNMAT,DNCUST,DNSTAT FROM %s.CJOBH WHERE DNJOB='%s'", 
                db.dbname, pjob->jobnum.c_str()) ; 

        CSQLRecordset rs(db) ;
        rs << qry ; 
        rs.SQLExec();
        while (rs.SQLFetch())
        {
            csString nmat, cust ; 

            pjob->partname  = rs.SQLGetData(1).c_str()  ;  
            pjob->partname.Trim() ; 

            nmat = rs.SQLGetData(2).c_str() ;  
            nmat.Trim() ; 

            cust = rs.SQLGetData(3).c_str() ;  
            cust.Trim() ;  // not used

            pjob->jobstatus = rs.SQLGetData(4).c_str()[0] ; 

            pjob->subCount = atoi(nmat.c_str()) ; 
            
            break ; 
        }

    }
    catch (CSQLException* e)
    {
        if (gCMSparms.pevp->fpLOG)
        {
            fprintf(gCMSparms.pevp->fpLOG, "SQL error %d loading job details for job '%s' \r\n  %s\r\n",
                        (int)e->m_nRetCode, pjob->jobnum.c_str(), e->m_strError.c_str()) ;
            fprintf(gCMSparms.pevp->fpLOG, "        qry = '%s'\n", qry) ;
            fflush(gCMSparms.pevp->fpLOG) ; 
        }
    }
    return 0 ; 
}

int CBatchUPDDlg::LoadBlankRecord(csString &sonum ,
                                  csString &empnum, 
                                  csString &prtcode, 
                                  csString &task, 
                                  csString &station, 
                                  csString &N1, 
                                  csString &S1, 
                                  csString &S2, 
                                  csString &tasktime) 
{
    BlankBatchRec brec ; 
    brec.station = station ; 
    brec.qty = atoi(N1.c_str()) ; 
    brec.serial = atoi(S2.c_str()) ; 
    brec.part = S1 ; 
    brec.empnum = atoi(empnum.c_str()) ;  ; 
    brec.prtcode = prtcode ; 
    brec.sonum = sonum ; 
    brec.taskcode = task ; 
    brec.tasktime = tasktime ; 
    brec.pickRec = false ; 

    CBatchUPDApp *pApp = (CBatchUPDApp *)AfxGetApp() ; 

    try {
        char qry[256] ; 
        sprintf(qry, "SELECT AQMTLP,AQSEQ#,AODEPT,AORESC,AQQPPC,AQUNIT FROM %s.METHDM "
                     " LEFT JOIN %s.METHDR ON AOPART=AQPART WHERE AQPART='%s' AND AQPLNT='%s'", 
                         gCMSparms.dbname, gCMSparms.dbname, S1.c_str(), gCMSparms.plantID) ; 
        CSQLRecordset rs(pApp->cmsdata.m_db) ;
        rs << qry ; 
        rs.SQLExec();
        while (rs.SQLFetch())
        {
            brec.mtl        = rs.SQLGetData(1).c_str() ; brec.mtl.Trim() ;
            csString ts     = rs.SQLGetData(2).c_str() ; 
            ts.Trim() ;  
            brec.seqnum     = atoi(ts.c_str()) ; 
            brec.dept       = rs.SQLGetData(3).c_str() ; brec.dept.Trim() ; 
            brec.res        = rs.SQLGetData(4).c_str() ; brec.res.Trim() ;
            brec.mtlqty     = rs.SQLGetData(5).c_str() ; brec.mtlqty.Trim()  ;
            brec.mtlunit    = rs.SQLGetData(6).c_str() ; brec.mtlunit.Trim()  ;
            break ; 
        }
    }
    catch (CSQLException* e)
    {
        if (gCMSparms.pevp->fpLOG)
        {
            fprintf(gCMSparms.pevp->fpLOG, "SQL error %d getting first 'N' type EXCOTASK record:\n%s\n",
                        (int)e->m_nRetCode, e->m_strError.c_str()) ;
            fflush(gCMSparms.pevp->fpLOG) ; 
        }
    }

    if (brec.mtl.size())
        bkvec.push_back(brec) ; // add this record. 
    
    return 0 ; 
}

int CBatchUPDDlg::LoadPickBlankRec(csString &sonum ,
                                   csString &empnum, 
                                   csString &prtcode, 
                                   csString &task, 
                                   csString &station, 
                                   csString &S1, 
                                   csString &S2, 
                                   csString &tasktime) 
{
    CBatchUPDApp *pApp = (CBatchUPDApp *)AfxGetApp() ; 
    BlankBatchRec brec ; 
    
    int foundPart = 0 ; 
    try {
        char qry[256] ; 
        sprintf(qry, "SELECT EFMTLP,EFSEQ#,EFQPPC,EFUNIT,EFPART FROM %s.CJOBH"
            " LEFT JOIN %s.CJOBDM ON DNJOB=EFJOB# WHERE DNORD#='%s'", 
                         gCMSparms.dbname, gCMSparms.dbname, sonum.c_str()) ; 
        CSQLRecordset rs(pApp->cmsdata.m_db) ;
        rs << qry ; 
        rs.SQLExec();
        while (rs.SQLFetch())
        {
            brec.mtl        = rs.SQLGetData(1).c_str() ; brec.mtl.Trim() ;
            csString ts     = rs.SQLGetData(2).c_str() ; 
            ts.Trim() ;  
            brec.seqnum     = atoi(ts.c_str()) ; 
            brec.dept       = csString(gCMSparms.plantID) + "LP" ;
            brec.res        = "LP" ; 
            brec.mtlqty     = rs.SQLGetData(3).c_str() ; brec.mtlqty.Trim()  ;
            brec.mtlunit    = rs.SQLGetData(4).c_str() ; brec.mtlunit.Trim()  ;
            csString cmspart = rs.SQLGetData(5).c_str() ;
            cmspart.Trim() ; 
            brec.part = cmspart ; 
            char partCode = PartCodeCharFromCMSPart(cmspart) ;
            
            if (partCode == prtcode[0])
            {
                foundPart = 1 ; 
                break ; 
            }
        }
    }
    catch (CSQLException* e)
    {
        if (gCMSparms.pevp->fpLOG)
        {
            fprintf(gCMSparms.pevp->fpLOG, "SQL error %d getting first 'N' type EXCOTASK record:\n%s\n",
                        (int)e->m_nRetCode, e->m_strError.c_str()) ;
            fflush(gCMSparms.pevp->fpLOG) ; 
        }
    }


    if (foundPart)
    {
        brec.station = station ; 
        brec.mtl = S1 ; 
        brec.serial = atoi(S2.c_str()) ; 
        brec.empnum = atoi(empnum.c_str()) ;  ; 
        brec.prtcode = prtcode ; 
        brec.sonum = sonum ; 
        brec.taskcode = task ; 
        brec.tasktime = tasktime ; 
        brec.pickRec = true ; 
        brec.seqnum = 100 ; 

        bkvec.push_back(brec) ; // add this record. 
    }
    
    return 0 ; 
}



int SQL_ConvertTime(const char *str, CDateTime &dt)
{
    if (!str || !str[0])
    {
        memset(&dt, 0, sizeof(CDateTime)) ; 
        return -1 ; 
    }

    // SQL datetime string returned as follows: 
    //      2007-10-20 17:35:14.920
    //      YYYY-MM-DD HH:MM:SS.SSS
    //      012345678901234567890123
    //                1         2   

    dt.m_nSecs  = atoi(str+17) ;  /* seconds after the minute - [0,59] */
    dt.m_nMins  = atoi(str+14) ;  /* minutes after the hour - [0,59] */
    dt.m_nHours = atoi(str+11) ; /* hours since midnight - [0,23] */
    dt.m_nDay   = atoi(str+8) ;  /* day of the month - [1,31] */
    dt.m_nMonth = atoi(str+5) ;  /* months since January - [1,12] */
    dt.m_nYear  = atoi(str) ;

    return 0 ; 
}

int CreateResKey(csString &reskey, csString &task, csString &empnum, csString &station)
{
	 //(task[0] == 'IS') || (task == "IC") 
    if ((task[0] == 'C' && task[1] >= '1' && task[1] <= '6')
		|| (task == "MM") || (task == "DU") )
    {   // This is an employee specific type task so set to employee number
        reskey = empnum ; 
    }
    else if (task == "N0" || task == "N1" ||
             task == "L1" || task == "L0" || (task == 'IS') || (task == "IC") || (task == 'IB') || (task == "IF"))
    {
        reskey = station ; 
    }
    else if (task == "RK"  || task == "PH" || 
             task == "HC" || task == "HD" ||
             task == "D1" || task == "D2" || task == "D3" ||
             task == "HT") 
    {   // The default is also the STATION + EMPNUM for now. 
        reskey = "HEAT" ; 
    }
    else
    {   // For everything else simply default to the station. 
        reskey = station ; 
    }

    return 0 ; 
}


/* 
    Currently this process runs based on the decade style tracking data. All the data
    from the current batches is loaded, and then all the task event records are loaded
    into the resource map vectors. Once that is done each resource map is scanned to 
    determine the updated run times based on the occurence of Start/Stop event pairs
    or possibly Start/Start type event pairs where events chain one after the other. 

    The key to the resource map table will needs to be broken done into resources that
    can process one job at a time. For areas like heat treat that run parts in a batch 
    this is irrelevant. 

    resmap keys are as follows:
    
        For all RTM=RTYPE records these are not loaded in resmap, runtime is stored directly         
        For all SAW=RTYPE records the material data is saved. 
        For tasks C[1-6]        key = EMPNUM
        For Zn, N[J-R], MCxx    key = STATION
        For IS and IC tasks     key = EMPNUM
        For MM tasks            key = EMPNUM

 */



int CBatchUPDDlg::ProcessEvent(EventData *ped, 
                               csString &rtype,
                               csString &sonum, 
                               csString &task, 
                               csString &empnum, 
                               csString &station, 
                               time_t   &eventTime,
                               csString &prtcode, 
                               csString &arc,
                               csString &R1,
                               csString &S1)
{
    CBatchUPDApp *pApp = (CBatchUPDApp *)AfxGetApp() ; 
    csString jobnum(133) ; 
        
    jobnum.len = CS_strmaxcat(jobnum.str, ped->jobnum, 15) ; 

    CMSJobMapItr ijm ; 
    ijm = jobsmap.find(jobnum) ;
	
	if (jobnum.str == "0241266")
	{
		int xxxx = 0;
	}

    if (ijm == jobsmap.end())
    {   // Add the job to the map

        char tmpstr[64] ; 

        CMSJob jobrec ; 
        jobrec.jobnum = jobnum ; 
        jobrec.partname = ped->partnum ; 
        sprintf(tmpstr, "%d", ped->orderNumber) ; 
        jobrec.ordNum = tmpstr ;  


        // When loading the job, if the status is complete, then mark it as complete
        //    but skip processing it further. Complete means that it has been moved
        //    to history. 

        LoadJobDetails(&jobrec, pApp->cmsdata.m_db, pApp->fplog) ;

        pair<CMSJobMapItr, bool> ijpair ;
        ijpair = jobsmap.insert(make_pair(jobnum, jobrec)) ; 
        if (ijpair.second)
        {
            ijm = ijpair.first ;
            ijm->second.LoadRouting(pApp->cmsdata.m_db, pApp->fplog) ; 
        }
    }

    if (ijm == jobsmap.end())
    {
        fprintf(pApp->fplog, "ERROR loading job record for '%s'\n", jobnum.c_str()) ;
        return -1 ; 
    }

    
    int seq = atoi(ped->seqnum) ; 

    // Find the current record in the cjobdr list
    int markAsProcessed = 0 ; 
    int foundSeq = 0 ;

    RouteDataRecVec &drvec = ijm->second.cjobdrVec ;
    int i ; 
    for (i=0; i < (int)drvec.size(); i++)
    {
        RouteDataRec *prec = &(drvec[i]) ; 
		
        if (seq == prec->seqno)
        {   // Load this data into the resmap data store as required. 

            if (rtype == "RTM" && arc != "Y")
            {   // Just add in the runtime directly 
                prec->pendingRunTime += atof(R1.c_str()) ;
                prec->bRuntimeFound |= 0x01 ; 
                prec->statflags |= RUNTIME_RECORD ;
                markAsProcessed = 1 ; 
            }
	    else if (rtype == "EVT" &&  (strncmp(ped->task, "WO", 2) != 0)
				    &&  (strncmp(ped->task, "WE", 2) != 0)
				    &&  (strncmp(ped->task, "W0", 2) != 0)
				    &&  (strncmp(ped->task, "SE", 2) != 0))
            {   // Standard event
                /*
                    For tasks C[1-6]        key = EMPNUM
                    For Zn, N[J-R], MCxx    key = STATION
                    For IS and IC tasks     key = EMPNUM
                    For MM tasks            key = EMPNUM
                */
                csString reskey ; 
                CreateResKey(reskey, task, empnum, station) ;

                ResRecMapItr irm ; 
                irm = resmap.find(reskey); 
                if (irm == resmap.end())
                {   // Add this to the resource map
                    
                    ResRec rr ; 
                    rr.res = reskey ; 
                    rr.lastEvent = 0 ; 

                    pair<ResRecMapItr, bool> ins ; 
                    ins = resmap.insert(make_pair(reskey, rr)) ; 

                    if (ins.second)
                    {
                        irm = ins.first ; 
                    }
                }

                
                if (irm != resmap.end())
                {   // append the record event to the resource
                    prec->bEventFound |= 0x01 ; 
                    prec->statflags |= EVENT_RECORD ;


                    BEventRec evrec ; 
                    evrec.ordnum = ped->orderNumber ; 
                    evrec.jobnum = ped->jobnum ; 
                    evrec.dept   = ped->deptCode ; 
                    evrec.cmspart = ped->partCode ; 
                    evrec.dt.SetTime(eventTime) ; 
                    evrec.resource = ped->resCode ; 
                    evrec.opercode = ped->opCode ; 
                    evrec.empnum = atoi(empnum.c_str()) ; 
                    evrec.batchID = 0 ;
                    evrec.seqnum = atoi(ped->seqnum) ; 
                    evrec.event = 0  ; 
                    evrec.part   = prtcode ; 
                    evrec.task = task ; 
                    evrec.station = station ; 
                    evrec.setArcState = 0 ; 
                    evrec.arcState = arc[0] ; 

                    if (prec->reskey.size())
                    {   // They should match, if they don't then flag an error

                        // There are many times when one person starts a job and another person finishes
                        // it which causes a resource mapping problem since the resource can't be found

                        // TODO - extend the logic so that when this happens the other person is taken
                        // off the current job. 

                        if (prec->reskey != reskey)
                        {
                            fprintf(gCMSparms.pevp->fpLOG, "TASK reskey error, key='%s' != reskey='%s' for so=%s part=%s task=%s station=%s emp=%s\r\n",
                                prec->reskey.c_str(), 
                                reskey.c_str(), 
                                sonum.c_str(), prtcode.c_str(), task.c_str(), station.c_str(), empnum.c_str()) ; 

                            fflush(gCMSparms.pevp->fpLOG) ; 
                        }
                    }
                    else
                    {   // save this so we can look it up later
                        prec->reskey = reskey ;
                    }

                    int idx = (int)irm->second.evvec.size() ; 
                    irm->second.evvec.push_back(evrec) ; 

                    EventRef eref ; 
                    eref.reskey = reskey ; 
                    eref.idx = idx ; 

                    prec->erv.push_back(eref) ; 
                }
                else
                {   // else an error occured - TODO deal with it
                    fprintf(gCMSparms.pevp->fpLOG, "TASK error, couldn't create a resmap entry for key='%s'  so=%s part=%s task=%s station=%s emp=%s\r\n",
                                reskey.c_str(), sonum.c_str(), prtcode.c_str(), task.c_str(), station.c_str(), empnum.c_str()) ; 
                    fflush(gCMSparms.pevp->fpLOG) ; 
                }
            }
            else if (rtype == "SAW")
            {   //  For all SAW=RTYPE records the material data is saved. 
                // Add about one minute to runtime and make sure QTY == 1
                prec->bRuntimeFound |= 0x02 ; 

				/* REMOVE SERIAL NUMBER

                int sernum = atoi(S1.c_str()) ; 
                
                // Verify that the serial number is valid and if not then simply pick one
                // that is. This should always be valid since the saw data is being 
                // verified before the tracking records are created. 
                int valser = ValidateSerialNumber(ijm, prec, sernum) ; 
                
                if (valser != sernum)
                {
                    fprintf(gCMSparms.pevp->fpLOG, "Serial number error, received %d but forcing to %d for job %s, part=%s\r\n",
                                        sernum, valser, sonum.c_str(), prtcode.c_str()) ; 
                    fflush(gCMSparms.pevp->fpLOG) ; 
                }
                else if (valser == 0)
                {
                    fprintf(gCMSparms.pevp->fpLOG, "Serial number error, none found for job %s, part=%s\r\n",
                                        sonum.c_str(), prtcode.c_str()) ; 
                    fflush(gCMSparms.pevp->fpLOG) ; 

                    char tmpmsg[256] ; 
                    sprintf(tmpmsg, "Serial Number Error for %s %s", 
                                    sonum.c_str(), prtcode.c_str()) ; 
                            
                    AfxMessageBox(tmpmsg) ; 
                }

                prec->serialnum = valser ; 
				*/ //REMOVE SERIALNUM END

				int valser = 1;//remove to reuse serialnum
				prec->serialnum = 001;//remove to reuse serialnum
//				
				//prec->serialnum = sernum;
               // prec->pendingRunTime += 0.02 ; // rounding for 1 minute in CMS
                
                prec->qtysaw = 1.0 ; // only allow one saw record at a time. 
                // NOTE: if two parts are cut on the same day then this logic will screw
                // up. The reason for it being here is to allow for producing a part after
                // something is scrapped. Since the scrap record may not exist before the 
                // saw part is cut, there is no real way to be sure what to do at this 
                // point. Typically when a part is scapped, it is not on the same day that 
                // it came of the saw. TODO - allow for same day occurences. In fact if this
                // batch routine is run multiple times per day, then it only becomes a
                // problem if the saw cuts the same part twice between runs of this 
                // batch routine. 

                prec->statflags |= SAW_RECORD ;
                markAsProcessed = 1 ; 
            }

            foundSeq = 1 ; 
            break ; // done with it, don't need to keep looping
        }
    }

    if (!foundSeq || markAsProcessed)
    {
        // Indicate that Y state is pending. 

        BEventRec evrec ; 
        evrec.ordnum = ped->orderNumber ; 
        evrec.jobnum = ped->jobnum ; 
        evrec.dept   = ped->deptCode ; 
        evrec.cmspart = ped->partCode ; 
        evrec.dt.SetTime(eventTime) ; 
        evrec.resource = ped->resCode ; 
        evrec.opercode = ped->opCode ; 
        evrec.empnum = atoi(empnum.c_str()) ; 
        evrec.batchID = 0 ;
        evrec.seqnum = atoi(ped->seqnum) ; 
        evrec.event = 0  ; 
        evrec.part = prtcode ; 
        evrec.task = task ; 
        evrec.station = station ; 
        evrec.setArcState = 'Y' ; 
        evrec.rtype = rtype ; 

        processedTasks.push_back(evrec) ; 

    }
    return 0 ; 
}

void CBatchUPDDlg::LoadJobListMaster()
{

    CBatchUPDApp *pApp = (CBatchUPDApp *)AfxGetApp() ; 
    char tmpstr[256] ; 

    // Reset all pending task records
    CDateTime dtw ; 
    dtw.SetNow() ; 
    time_t tt ;  
    tt = dtw.GetTimeT() ; 
    tt -= 1000000 ; // go back 10 days max, anything more than that and things officially break. 
	dtw.SetTime(tt) ; 
    dtw.FormatDateTimeSecs(tmpstr) ; 

    ResRecMapItr irr ; 

    int i ; 
    CMSJobMapItr ijm ; 

    char msg1[1024] ;  
    char msg2[1024] ; 
    char *msgstrs[2] ; 
    msgstrs[0] = msg1 ; 
    msgstrs[1] = msg2 ; 
    strcpy(msg1, "None") ; 
    strcpy(msg2, "None") ; 

    csString jobnum(64) ;
    csString deptstr(64)   ; 
    csString resc(64)   ;
    csString rdate(64)  ;
    csString part(64)   ;
    csString seqnum(64) ;
    csString qtyg(64)   ;
    csString qtys(64)   ;
    csString runtm(64)  ;
    csString posted(64) ;
    csString ordnum(64) ;
	int test = 0;

    // Need to redo this to the following:
    // 1) Load all active batch IDs
    // 2) Build map of all the work orders (JOB#) for those active batches
    // 3) Query the RPRR table by JOB# to get the total time and quantity good
    // 4) Record this data and then proceed.

    //    MODIFY HERE ;

    char qry[0x4000] ; 
    int count = 0 ; 

    jobsmap.clear() ; 


    csString sonum(64) ;
    csString empnum(64)   ; 
    csString prtcode(16)   ;
    csString task(16)   ;
    csString tasktime(64)  ;
    csString station(64) ;
    csString rtype(16)   ;
    csString arc(16) ; 
    csString N1(32) ; 
    csString N2(32) ; 
    csString R1(64) ; 
    csString R2(64) ; 
    csString S1(128) ; 
    csString S2(128) ; 

    CCMSDatabase ddb ; 
    bool decOpen = true ;
    try {
        ddb.OpenEx("decade", "jamie", "jamie") ; 
    }
    catch(...)
    {
        decOpen = false ; 
    }


    /************************************************************************
      Stage 3 - load the EXCOTASK records and merge this data into the 
      current data set. For SO#'s that don't currently exist within the 
      jobsmap data store, those routings will have to be loaded as well 
      and initialized with the new data. This will likely happen for 
      most of the records. 

      To do this step the task codes and parts have to be mapped to job numbers
      within Solarsoft, thus a map will have to be maintained to allow for 
      this which will pull from the CADUpdate logic. 

      The resmap will contain a list of events for each unique resource to 
      facilitate grouping the start/stop time pairs. The query below must 
      be order by tasktime to keep everything synched correctly. 

     ************************************************************************/

	
	CString FromTime;
	CString ToTime;
	FromTime.Format("%d-%d-%d", m_FromTime.GetYear(), m_FromTime.GetMonth(), m_FromTime.GetDay());
	ToTime.Format("%d-%d-%d", m_ToTime.GetYear(), m_ToTime.GetMonth(), m_ToTime.GetDay());
	_snprintf(qry, 0x3FF0,
        "SELECT SONUM,EMPNUM,PRTCODE,TASK,TASKTIME,STATION,RTYPE,ARC,N1,N2,R1,R2,S1,S2, REWORK FROM"
        " %s.EXCOTASK WHERE ARC IN('N','A','I','Y','S','T') AND PLANT='%s'"
        " AND CTIME >= '%s 00:00:01' AND CTIME < '%s 23:59:59' ORDER BY TASKTIME", 
		gCMSparms.dbname, gCMSparms.plantID, FromTime, ToTime) ;

	/*_snprintf(qry, 0x3FF0,
        "SELECT SONUM,EMPNUM,PRTCODE,TASK,TASKTIME,STATION,RTYPE,ARC,N1,N2,R1,R2,S1,S2, REWORK FROM"
        " %s.EXCOTASK WHERE ARC IN('N','A','I','Y','S','T') AND PLANT='%s'"
        " AND CTIME >= '2011-11-30 00:00:01' AND CTIME < '2011-11-30 23:59:59' ORDER BY TASKTIME", 
            gCMSparms.dbname, gCMSparms.plantID, firstTimeStr.c_str()) ; */
	//AND CTIME < '2011-07-31 23:59:59'
     // NEED TO LOAD 'I' and 'Y' jobs also. Then when processing Y and I records add them into the 
     // data set and indicate that they have already been processed. 
	 // CTIME < '2011-07-31 23:59:59'
    
     // SKIP over all processed records until the first 'N' type record and then proceed 
     // normally with some updated logic to factor in processed records.


	ProgressCount = 10000;
	m_Progress.SetRange(0,ProgressCount);

    resmap.clear() ; 

    int taskcount = 0 ; 
    int skippedcount = 0 ;
    int firstN = 0 ; 
	int tests = 0;
    try
    {
        CSQLRecordset rs(pApp->cmsdata.m_db) ;
        rs << qry ; 
        rs.SQLExec();
        while (rs.SQLFetch())
        {
            int fldnum = 1 ; 
			tests = tests + 1;
            sonum.len       = CS_strmaxcat(sonum.str    , rs.SQLGetData(fldnum++).c_str(), 60) ; 
            empnum.len      = CS_strmaxcat(empnum.str   , rs.SQLGetData(fldnum++).c_str(), 60) ; 
            prtcode.len     = CS_strmaxcat(prtcode.str  , rs.SQLGetData(fldnum++).c_str(), 14) ;  
            task.len        = CS_strmaxcat(task.str     , rs.SQLGetData(fldnum++).c_str(), 14) ;  
            tasktime.len    = CS_strmaxcat(tasktime.str , rs.SQLGetData(fldnum++).c_str(), 60) ; 
            station.len     = CS_strmaxcat(station.str  , rs.SQLGetData(fldnum++).c_str(), 32) ;  
            rtype.len       = CS_strmaxcat(rtype.str    , rs.SQLGetData(fldnum++).c_str(), 8) ;  
            arc.len         = CS_strmaxcat(arc.str      , rs.SQLGetData(fldnum++).c_str(), 8) ;  
            N1.len          = CS_strmaxcat(N1.str       , rs.SQLGetData(fldnum++).c_str(), 16) ;  
            N2.len          = CS_strmaxcat(N2.str       , rs.SQLGetData(fldnum++).c_str(), 16) ;  
            R1.len          = CS_strmaxcat(R1.str       , rs.SQLGetData(fldnum++).c_str(), 32) ;  
            R2.len          = CS_strmaxcat(R2.str       , rs.SQLGetData(fldnum++).c_str(), 32) ;  
            S1.len          = CS_strmaxcat(S1.str       , rs.SQLGetData(fldnum++).c_str(), 120) ;  
            S2.len          = CS_strmaxcat(S2.str       , rs.SQLGetData(fldnum++).c_str(), 120) ;  

            sonum.Trim() ;
            empnum.Trim() ;
            prtcode.Trim() ;
            task.Trim() ;
            tasktime.Trim() ;
            station.Trim() ;
            rtype.Trim() ;
            arc.Trim() ; 
            N1.Trim() ;
            N2.Trim() ;
            R1.Trim() ;
            R2.Trim() ;
            S1.Trim() ;
            S2.Trim() ;

            int soNumber = atoi(sonum.c_str()) ; 
            if (soNumber == 100)
            {
                LoadBlankRecord(sonum, empnum, prtcode, task, station, N1, S1, S2, tasktime) ; 
                continue ; 
            }
            else if (rtype == "PPT")
            {
                LoadPickBlankRec(sonum, empnum, prtcode,  task, station,S1, S2, tasktime) ;
                continue ; 
            }
			else if(rtype == "SAW")
			{
				int testsaw = 0;
				
			}
            if (!firstN)
            {
                if (arc == "N")
                    firstN = 1 ; 
                else
                    continue ; 
            }
			/*if(task == "NS"&& arc == "N")
			{
				NitridS = 1;
				NitridArc = 1;
				if(prtcode.FindIDX("P")>-1)
					NitridPrtCode = "P";
				else if(prtcode.FindIDX("M")>-1)
					NitridPrtCode = "M";
				else if(prtcode.FindIDX("F")>-1)
					NitridPrtCode = "F";
				else if(prtcode.FindIDX("BA")>-1||prtcode.FindIDX("BB")>-1||prtcode.FindIDX("BF")>-1)
					NitridPrtCode = "BA";
				else if(prtcode.FindIDX("BO")>-1||prtcode.FindIDX("OF")>-1||prtcode.FindIDX("OL")>-1||prtcode.FindIDX("OB")>-1)
					NitridPrtCode = "BO";
			}*/
            gCMSparms.pevp->evd.sonum = atoi(sonum.c_str()) ; 
            gCMSparms.pevp->evd.empnum = atoi(empnum.c_str()) ; 
            CS_strmaxcpy(gCMSparms.pevp->evd.part, prtcode.c_str(), 8) ;   ; 
            CS_strmaxcpy(gCMSparms.pevp->evd.task, task.c_str(), 8) ;   ; 
            CS_strmaxcpy(gCMSparms.pevp->evd.station, station.c_str(), 16) ;
            
            CDateTime dt ;  
            SQL_ConvertTime(tasktime.c_str(), dt) ; 
            time_t eventTime = dt.GetTimeT() ; 
            gCMSparms.pevp->evd.tasktime = eventTime ; 

            // Look up all the relevant routing information for this task record
            TaskMapItr itm ; 
            int maperr = 0 ; 

			if( sonum == "241540")
				{
					int xxxx = 0;
				}
            EventData &evt = gCMSparms.pevp->evd ; 
            if (strncmp(evt.task, "IC", 2) == 0 ||strncmp(evt.task, "IF", 2) == 0) //USED TO BE IC
            {   // Then we mapped the SO number, so don't worry about the task map
                // Will force all the task data as required
                // Create records for each of the FEEDER, PLATE, MANDREL, BACKER. BOLSTER, and RING
                // and if those record don't exist then they should error out

                // This is a severe kludge to get the inspection tracking data stored

                strcpy(evt.part, "FD") ; 
                prtcode.len = CS_strmaxcat(prtcode.str, "FD", 14) ;  
                if (!gCMSparms.pevp->MapDecadeData(itm, true))
                {
                    ProcessEvent(&(gCMSparms.pevp->evd),
                                rtype, sonum, task, empnum, station, eventTime,
                                prtcode, arc, R1, S1) ;
                }


                strcpy(evt.part, "MN") ; 
                prtcode.len = CS_strmaxcat(prtcode.str, "MN", 14) ;  
                if (!gCMSparms.pevp->MapDecadeData(itm, true))
                {
                    ProcessEvent(&(gCMSparms.pevp->evd),
                                rtype, sonum, task, empnum, station, eventTime,
                                prtcode, arc, R1, S1) ;
                }


                strcpy(evt.part, "PL") ; 
                prtcode.len = CS_strmaxcat(prtcode.str, "PL", 14) ;  
                if (!gCMSparms.pevp->MapDecadeData(itm, true))
                {
                    ProcessEvent(&(gCMSparms.pevp->evd),
                                rtype, sonum, task, empnum, station, eventTime,
                                prtcode, arc, R1, S1) ;
                }

                strcpy(evt.part, "BA") ; 
                prtcode.len = CS_strmaxcat(prtcode.str, "BA", 14) ;  
                if (!gCMSparms.pevp->MapDecadeData(itm, true))
                {
                    ProcessEvent(&(gCMSparms.pevp->evd),
                                rtype, sonum, task, empnum, station, eventTime,
                                prtcode, arc, R1, S1) ;
                }

                strcpy(evt.part, "OL") ; 
                prtcode.len = CS_strmaxcat(prtcode.str, "OL", 14) ;  
                if (!gCMSparms.pevp->MapDecadeData(itm, true))
                {
                    ProcessEvent(&(gCMSparms.pevp->evd),
                                rtype, sonum, task, empnum, station, eventTime,
                                prtcode, arc, R1, S1) ;
                }

                strcpy(evt.part, "SB") ; 
                prtcode.len = CS_strmaxcat(prtcode.str, "SB", 14) ;  
                if (!gCMSparms.pevp->MapDecadeData(itm, true))
                {
                    ProcessEvent(&(gCMSparms.pevp->evd),
                                rtype, sonum, task, empnum, station, eventTime,
                                prtcode, arc, R1, S1) ;
                }

                strcpy(evt.part, "RI") ; 
                prtcode.len = CS_strmaxcat(prtcode.str, "RI", 14) ;  
                if (!gCMSparms.pevp->MapDecadeData(itm, true))
                {
                    ProcessEvent(&(gCMSparms.pevp->evd),
                                rtype, sonum, task, empnum, station, eventTime,
                                prtcode, arc, R1, S1) ;
                }

            }
            else
            {   // Process normally 
				//ASSERT(AfxCheckMemory());
                maperr = gCMSparms.pevp->MapDecadeData(itm, true) ; 

				if( sonum == "241540")
				{
					int xxxx = 0;
				}
                if (maperr)
                {
                    char errcode = 'E' ; 
                    switch(maperr)
                    {
                        case -2 :
                            errcode = '1' ; 
                            break ;
                        case -22 :
                            errcode = '2' ; 
                            break ;
                        case -23 :
                            errcode = '3' ; 
                            break ;
                        case -25 :
                            errcode = '4' ; 
                            break ;
                        case -100 :
                            errcode = '5' ; 
                            break ;
                        case -122 :
                            errcode = '6' ; 
                            break ; 
						case -20 :
							errcode = '7';
							break;
                    }

                    char uqry[256] ; 
                    try
                    {
						
							sprintf(uqry, "UPDATE %s.EXCOTASK SET ARC='%c' WHERE"
										" PLANT='%s' AND SONUM='%s' AND EMPNUM='%s' AND PRTCODE='%s' AND"
										" TASK='%s' AND TASKTIME='%s' AND STATION='%s'", 
										gCMSparms.dbname, errcode, 
										gCMSparms.plantID, 
										sonum.c_str(), empnum.c_str(), prtcode.c_str(), 
										task.c_str(), tasktime.c_str(), station.c_str() ); 

							CSQLRecordset rsu(pApp->cmsdata.m_db) ;
							rsu << uqry ; 
							rsu.SQLExec();

                    }
                    catch (CSQLException* e)
                    {
                        if (gCMSparms.pevp->fpLOG)
                        {
                            fprintf(gCMSparms.pevp->fpLOG, 
                                            "SQL error %d loading job record details:\n"
                                            "   %s\n"
                                            "   QRY=>'%s'\n", 
                                        (int)e->m_nRetCode, e->m_strError.c_str(), uqry) ;
                            fflush(gCMSparms.pevp->fpLOG) ; 
                        }
                        throw 1 ; 
                    }

                    sprintf(msg1, "Skipped task %d", skippedcount++) ; 
//                    ppdlg->SendMessage(WM_STATUPD, (WPARAM)msgstrs, 0 ) ; 
                }
                else
                {
                    // See if the job is already loaded. 

                    if (ProcessEvent(&(gCMSparms.pevp->evd),
                                    rtype, sonum, task, empnum, station, eventTime,
                                    prtcode, arc, R1, S1))
                    {
                        continue ; 
                    }

                    
        
                }
            }

            sprintf(msg2, "Task Record %d", taskcount++) ; 
			m_Progress.StepIt();
//            ppdlg->SendMessage(WM_STATUPD, (WPARAM)msgstrs, 0 ) ; 
			//CBatchUPDDlg m_ctlProgress;
		//	m_ctlProgress.OnNMCustomdrawProgress1(

            if (taskcount >= 83)
            {
                int xx = 0 ;
                xx++ ; 

            }

            // DEBUG PURPOSES ONLY. 
            // if (taskcount - skippedcount > 50)
            //     break ; 
			if(test>16000)
				int i = 0;
			test = test+1;
        }
		
    }
    catch(int err)
    {
        if (gCMSparms.pevp->fpLOG)
        {
            fprintf(gCMSparms.pevp->fpLOG, "ERROR %d while loading tasks\n", err) ; 
            fflush(gCMSparms.pevp->fpLOG) ; 
        }
    }
    catch (CSQLException* e)
    {
        if (gCMSparms.pevp->fpLOG)
        {
            fprintf(gCMSparms.pevp->fpLOG, "SQL error %d loading job record details:\n"
                            "   %s\n"
                            "   QRY=>'%s'\n", 
                        (int)e->m_nRetCode, e->m_strError.c_str(), qry) ;
            fflush(gCMSparms.pevp->fpLOG) ; 
        }
        
        AfxMessageBox("ERROR LOADING EXCOTASK DATA - ABORTING", MB_OK) ; 

        return ; 
    }


    // *************************************************************************************
    // add any jobs from CJOBH that have a status of A or N that are not currently in the 
    // jobsmap. These are all the active jobs that have no activity currently in EXCOTASK
    // This ensures that we see all the required data. 
    // *************************************************************************************
    _snprintf(qry, 0x3FF0,
        //         1         2       3         4        5       6         7       8        9        10      11
        "SELECT A.OAJOB#,A.OADEPT,A.OARESC,A.OARDAT,A.OAPART,A.OASEQ#,A.OAQTYG,A.OAQTYS,A.OATIME,A.OAPOST,B.DNORD# FROM"
        " %s.CJOBH AS B"
        " LEFT JOIN %s.RPRR AS A ON A.OAJOB# = B.DNJOB "
        " WHERE  (B.DNSTAT = 'N' OR B.DNSTAT = 'A') AND B.DNPLNT = '%s'", 
            gCMSparms.dbname, gCMSparms.dbname, gCMSparms.plantID) ;

    //     B.DNORD# = '225771' AND 

    try
    {
        CSQLRecordset rs(pApp->cmsdata.m_db) ;
        rs << qry ; 
        rs.SQLExec();

        while (rs.SQLFetch())
        {
            int fldnum = 1 ; 

            jobnum.len  = CS_strmaxcat(jobnum.str  , rs.SQLGetData(fldnum++).c_str(), 60) ;  // 1
            deptstr.len = CS_strmaxcat(deptstr.str , rs.SQLGetData(fldnum++).c_str(), 60) ;  // 2
            resc.len    = CS_strmaxcat(resc.str    , rs.SQLGetData(fldnum++).c_str(), 60) ;  // 3
            rdate.len   = CS_strmaxcat(rdate.str   , rs.SQLGetData(fldnum++).c_str(), 60) ;  // 4
            part.len    = CS_strmaxcat(part.str    , rs.SQLGetData(fldnum++).c_str(), 60) ;  // 5
            seqnum.len  = CS_strmaxcat(seqnum.str  , rs.SQLGetData(fldnum++).c_str(), 60) ;  // 6
            qtyg.len    = CS_strmaxcat(qtyg.str    , rs.SQLGetData(fldnum++).c_str(), 60) ;  // 7
            qtys.len    = CS_strmaxcat(qtys.str    , rs.SQLGetData(fldnum++).c_str(), 60) ;  // 8
            runtm.len   = CS_strmaxcat(runtm.str   , rs.SQLGetData(fldnum++).c_str(), 60) ;  // 9
            posted.len  = CS_strmaxcat(posted.str  , rs.SQLGetData(fldnum++).c_str(), 60) ;  // 10
            ordnum.len  = CS_strmaxcat(ordnum.str  , rs.SQLGetData(fldnum++).c_str(), 60) ;  // 11

            jobnum.Trim() ; 
			//001010024,  
#ifdef _DEBUG
			// jobnum is work order
			if(jobnum!="0273254")
				continue;
#endif

		
            deptstr.Trim() ; 
            resc.Trim() ; 
            rdate.Trim() ;
			part.Trim() ;    
            seqnum.Trim() ;  
            qtyg.Trim() ;    
            qtys.Trim() ;    
            runtm.Trim() ;   
            posted.Trim() ;  
            ordnum.Trim() ;  

            if (atoi(jobnum.c_str()) == 0)
            {   // There is no job data for this sales order, thus the jobnumber is null
                continue ; // null record
            }

            // now see if this job number already exists

            CMSJobMapItr ijm = jobsmap.find(jobnum) ;
            if (ijm == jobsmap.end())
            {   // Then add this record to the overall data set
                CMSJob jobrec ; 
                jobrec.jobnum = jobnum ; 
                jobrec.partname = part ; 
                jobrec.ordNum = ordnum ;  

                LoadJobDetails(&jobrec, pApp->cmsdata.m_db, pApp->fplog) ;

                pair<CMSJobMapItr, bool> ijpair ; 
                ijpair = jobsmap.insert(make_pair(jobnum, jobrec)) ; 
                if (ijpair.second)
                {
                    ijm = ijpair.first ;
                    ijm->second.LoadRouting(pApp->cmsdata.m_db, pApp->fplog) ;
                }

                sprintf(msg2, "Added job %s", jobnum.c_str()) ; 
				m_Progress.StepIt();
//                ppdlg->SendMessage(WM_STATUPD, (WPARAM)msgstrs, 0 ) ; 

            }
        }
    }
    catch (CSQLException* e)
    {
        if (gCMSparms.pevp->fpLOG)
        {
            fprintf(gCMSparms.pevp->fpLOG, "SQL error %d loading job record details for posted batches:\n%s\n",
                        (int)e->m_nRetCode, e->m_strError.c_str()) ;
            fflush(gCMSparms.pevp->fpLOG) ; 
        }
    }



    // Now go through all the jobs and load all the previously posted batches
    // and add that data into the current run times and quantities. 
    for (ijm = jobsmap.begin(); ijm != jobsmap.end(); ijm++)
    {
        CMSJob *pjob = &(ijm->second) ; 

        char qry[0x4000] ; 
        _snprintf(qry, 0x3FF0,
            "SELECT A.OAJOB#,A.OADEPT,A.OARESC,A.OARDAT,A.OAPART,A.OASEQ#,A.OAQTYG,A.OAQTYS,A.OATIME,A.OAPOST,B.DNORD# FROM"
            " %s.RPRR AS A"
            " LEFT JOIN %s.CJOBH AS B ON A.OAJOB# = B.DNJOB "
            " WHERE A.OAJOB# = '%s' AND A.OAPOST = 'Y'", 
                gCMSparms.dbname, gCMSparms.dbname, pjob->jobnum.c_str()) ;

        try
        {
            CSQLRecordset rs(pApp->cmsdata.m_db) ;
            rs << qry ; 
            rs.SQLExec();
			int dummy = 0;
            while (rs.SQLFetch())
            {
                int fldnum = 1 ; 

                jobnum.len  = CS_strmaxcat(jobnum.str  , rs.SQLGetData(fldnum++).c_str(), 60) ; 
                deptstr.len = CS_strmaxcat(deptstr.str , rs.SQLGetData(fldnum++).c_str(), 60) ; 
                resc.len    = CS_strmaxcat(resc.str    , rs.SQLGetData(fldnum++).c_str(), 60) ;  
                rdate.len   = CS_strmaxcat(rdate.str   , rs.SQLGetData(fldnum++).c_str(), 60) ;  
                part.len    = CS_strmaxcat(part.str    , rs.SQLGetData(fldnum++).c_str(), 60) ; 
                seqnum.len  = CS_strmaxcat(seqnum.str  , rs.SQLGetData(fldnum++).c_str(), 60) ;  
                qtyg.len    = CS_strmaxcat(qtyg.str    , rs.SQLGetData(fldnum++).c_str(), 60) ;  
                qtys.len    = CS_strmaxcat(qtys.str    , rs.SQLGetData(fldnum++).c_str(), 60) ;  
                runtm.len   = CS_strmaxcat(runtm.str   , rs.SQLGetData(fldnum++).c_str(), 60) ;  
                posted.len  = CS_strmaxcat(posted.str  , rs.SQLGetData(fldnum++).c_str(), 60) ;  
                ordnum.len  = CS_strmaxcat(ordnum.str  , rs.SQLGetData(fldnum++).c_str(), 60) ;  

                jobnum.Trim() ; 
                deptstr.Trim() ; 
                resc.Trim() ; 
                rdate.Trim() ;
                part.Trim() ;    
                seqnum.Trim() ;  
                qtyg.Trim() ;    
                qtys.Trim() ;    
                runtm.Trim() ;   
                posted.Trim() ;  
                ordnum.Trim() ;  

                int seq = atoi(seqnum.c_str()) ; 

                // Find the current record in the cjobdr list
                RouteDataRecVec *prv = &(ijm->second.cjobdrVec) ;
                for (i=0; i < (int)prv->size(); i++)
                {
                    if (seq == (*prv)[i].seqno)
                    {
                        if ((*prv)[i].starttime.m_nYear == 0)
                        {   // Then initialize the start time record. 
                            CDate dt ;
                            dt.SetDate(atoi(rdate.c_str()), atoi(rdate.str+5), atoi(rdate.str+8)) ; 
                            (*prv)[i].starttime.SetDate(dt.m_nYear, dt.m_nMonth, dt.m_nDay)  ; 
                            (*prv)[i].starttime.m_nHours = 0 ; 
                            (*prv)[i].starttime.m_nMins  = 0 ; 
                            (*prv)[i].starttime.m_nSecs  = 0 ; 
                        }
                        
                        (*prv)[i].totalRunTime += atof(runtm.c_str()) ; 
                        (*prv)[i].qtydone += atof(qtyg.c_str()) ; 
                        (*prv)[i].qtyscrap += atof(qtys.c_str()) ; 

                        break ; // found it. 
                    }
                }

                sprintf(msg1, "Update Prev Record %d", count++) ; 
                msg2[0] = 0 ; 
				//m_Progress.StepIt();
//                ppdlg->SendMessage(WM_STATUPD, (WPARAM)msgstrs, 0 ) ; 
				dummy = dummy+1;
            }
        }
        catch (CSQLException* e)
        {
            if (gCMSparms.pevp->fpLOG)
            {
                fprintf(gCMSparms.pevp->fpLOG, "SQL error %d loading job record details for posted batches:\n%s\n",
                            (int)e->m_nRetCode, e->m_strError.c_str()) ;
                fflush(gCMSparms.pevp->fpLOG) ; 
            }
            return ; 
        }
    }

    // final step is to load all orphaned HD master parts that have no tracking against them but exist
    // as current jobs because there is saw or other part specific tracking that has occured.


    // Now that all the task data is loaded, extract out the various runtimes for 
    // each of the jobs. To do this we need to first go through each resource and 
    // extract out the start/stop times based on events that occured on a specific
    // resource. 
    // TODO - match up erroneously reported station codes and employee numbers. 

    // To simplify the processing, this will be handled on a job by job basis. 

    ResRecRefVec rrr ; 

    for (ijm = jobsmap.begin(); ijm != jobsmap.end(); ijm++)
    {
        RouteDataRecVec *prv = &(ijm->second.cjobdrVec) ;
        ijm->second.iLastSeq = -1 ; 
        ijm->second.iFirstZSeq = -1 ; 

        if (ijm->second.jobnum == "0241266")
        {
            int xx = 0 ; 
            xx++ ; 
        }

        // state bits are
        //     0    - idle
        //  0x01    - RUN_STATE

        for (i=0; i < (int)(prv->size()) ; i++)
        {
            //////////////////////////////////////////////////////////
            // This loop works through all the routing sequence steps. 
            //////////////////////////////////////////////////////////

            int state = 0 ; 
            CDateTime starttime = 0 ;
    
            // For each event type routing, walk through all the resource
            // records to accumulate the total probable runtime for this 
            // event task. 

            rrr.clear() ; 

            RouteDataRec *prec = &((*prv)[i]) ; 
			
			//ResRecMapItr icm = resmap.find(prec->erv[i].reskey) ; 

            for (unsigned int j=0; j < prec->erv.size(); j++)
            {
                ResRecMapItr irm = resmap.find(prec->erv[j].reskey) ; 

				if(prec->seqno == 780)
				{
					ResRec *preic = &(irm->second);
					csString taskIC = "";
					int iric = prec->erv[j].idx ; 
					taskIC = preic->evvec[iric].task;
					if(taskIC == "IC")
					{
						int test = 0;
						prec->taskET = taskIC;
					}
				}

                if (irm == resmap.end())
                {
                    fprintf(gCMSparms.pevp->fpLOG, 
                        "Resource key '%s' not found processing task events, job=%s, part=%c\r\n",
                                prec->erv[j].reskey.c_str(), 
                                ijm->second.jobnum.c_str(), 
                                prec->partCode) ; 

                    fflush(gCMSparms.pevp->fpLOG) ; 
                    continue ; // skip to the next record since there is no way to process
                    // this current record. No task records exist to scan.
                }

                ResRec *pres = &(irm->second) ; 
                int ires = prec->erv[j].idx ; 

                // 0x01=start 0x02 = stop, 0x03=pulse
                int tasktype = pres->evvec[ires].TaskType() ;  

				//When Task = "IC" it's a special case
				
                if (tasktype & (TASK_STATUS | TASK_EVENT))
                {
                    prec->lastEventTime = pres->evvec[ires].dt ; 
                    prec->bProcFlags |= PRCF_SET_TIME_STAMP ; 
                    pres->evvec[ires].setArcState = 'I' ; // information only record
                }
                else if (state == 0 && (tasktype & START_TASK) && 
                         (pres->evvec[ires].arcState == 'N' || pres->evvec[ires].arcState == 'A'))
                {   
                    // When idle we need to see a start time from one
                    // of the records
                    // The erv member variable within the RouteDataRec contains
                    // all the task events that occured against this work order. 

                    state = RUN_STATE ;
                    starttime = pres->evvec[ires].dt ; 
                    if (prec->starttime.m_nYear == 0)
                        prec->starttime = starttime ; 

                    ResRecRef rrrec ; 
                    rrrec.prr = pres ; 
                    rrrec.irr = ires ; 
                    rrr.push_back(rrrec) ; 
                }
                else if ((state & RUN_STATE) && (tasktype & START_TASK))
                {   // Log that we got two start events for the job. 
                    char timestr[128] ; 
                    pres->evvec[ires].dt.FormatDateTimeSecs(timestr) ; 
                    fprintf(gCMSparms.pevp->fpLOG, "Warning 0x000A, start while in run state for job=%s, part=%c, time=%s\r\n",
                                    ijm->second.jobnum.c_str(), prec->partCode, timestr) ; 
                    fflush(gCMSparms.pevp->fpLOG) ; 

                    ResRecRef rrrec ; 
                    rrrec.prr = pres ; 
                    rrrec.irr = ires ; 
                    rrr.push_back(rrrec) ; 
                }
                else if ((state & RUN_STATE) && (tasktype & STOP_TASK))
                {
                    CDateTime t1, t0 ; 
                    if (pres->evvec[ires].ManualTask(t1, t0))
                    {
                        if (starttime.m_nHours > pres->evvec[ires].dt.m_nHours)
                        {   // Then the job has run overnight ( since the events
                            // are sorted by time to gein with). This could be because
                            // the user forgot to log the job out. Whatever the case may
                            // be simply record the stop top but subtract out the over-
                            // night time period. This will always assume that the 
                            // day shift is from 7AM to 4PM

                            char timestr1[128] ; 
                            char timestr2[128] ; 

                            starttime.FormatDateTimeSecs(timestr1) ; 
                            pres->evvec[ires].dt.FormatDateTimeSecs(timestr2) ; 
                            fprintf(gCMSparms.pevp->fpLOG, 
                                "Warning 0x000B, manual overnight, job=%s, part=%c, timestart=%s, timeend=%s\r\n",
                                            ijm->second.jobnum.c_str(), 
                                            prec->partCode, 
                                            timestr1, timestr2) ; 

                            fflush(gCMSparms.pevp->fpLOG) ; 

                            int startsecs = starttime.DaySeconds() ; 
                            int stopsecs  = pres->evvec[ires].dt.DaySeconds() ; 

                            double runsecs = max(0, (16.0 * 3600) - startsecs) ; 
                            runsecs += max(0, stopsecs - (7.0 * 3600)) ; 

                            prec->pendingRunTime += runsecs / 3600.0 ; // convert to hours
                        }
                        else
                        {   // Then assume that they ran on the same day. 
                            double runsecs = 
                                pres->evvec[ires].dt.DaySeconds() - starttime.DaySeconds() ; 
                            prec->pendingRunTime += (runsecs / 3600.0) ; // convert to hours
                        }
                    }
                    else
                    {   // This is an automated NC task which could run overnight so
                        // don't apply any special logic, just use the start and stop
                        // times as given. 


                        time_t startsecs = starttime.GetTimeT() ; 
                        time_t stopsecs  = pres->evvec[ires].dt.GetTimeT() ; 

                        double runsecs = (int)(stopsecs - startsecs) ; 
                        prec->pendingRunTime += (runsecs / 3600.0) ; // convert to hours
                    }

                    // Mark all the start tasks 
                    for (unsigned int k=0; k < rrr.size(); k++)
                        rrr[k].prr->evvec[rrr[k].irr].setArcState = 'Y' ; 
                    rrr.clear() ; 
                    pres->evvec[ires].setArcState = 'Y' ; 

                    state = 0 ; 
                }
                else if ((state == 0) && (tasktype & STOP_TASK))
                {   // ignore any other types of task records
                    // If the current runtime for the job is zero, then apply the standard run time 
                    // from CMS. If there is already time recorded against this job, then ignore 
                    // the extra time but log the warning
                    char timestr[100] ; 
                    pres->evvec[ires].dt.FormatDateTimeSecs(timestr) ; 

                    fprintf(gCMSparms.pevp->fpLOG, 
                      "Warning 0x000C, STOP while not running, job=%s, part=%c, task=%s, station=%s, time=%s\r\n",
                                    ijm->second.jobnum.c_str(), 
                                    pres->evvec[ires].part[0], 
                                    pres->evvec[ires].task.c_str(), 
                                    pres->evvec[ires].station.c_str(), 
                                    timestr) ; 

                    fflush(gCMSparms.pevp->fpLOG) ; 

                    if (prec->totalRunTime == 0.0)
                    {
						if(prec->pendingRunTime == 0.0 && prec->seqno != 460)
						{
							prec->pendingRunTime += prec->runstd ; 
							fprintf(gCMSparms.pevp->fpLOG, "     ---> was zero so applying standard run time\r\n" ) ; 
							fflush(gCMSparms.pevp->fpLOG) ; 
						}
                    }
                    else
                    {
                        fprintf(gCMSparms.pevp->fpLOG, 
                            "     ---> time already recorded so ignoring STOP event\r\n" ) ; 
                        fflush(gCMSparms.pevp->fpLOG) ; 
                    }

                    // mark as processed but indicate that it had no starttime. 
                    pres->evvec[ires].setArcState = 'S' ; 
                    
                }
            }
			//&&prec->seqno != 780
			// Search the logic to find scrap quantity
			bool MatchScrap;
			int seqtemp;
			int seqtime;
			seqtemp = 0;
			seqtime = 0;
			MatchScrap = false;

			for (int x = 0; x<(int)(prv->size()); x++)
			{
				RouteDataRec *pnxtrecS = &((*prv)[x]) ; 
				if (pnxtrecS->qtyscrap>0)
				{
					 MatchScrap= true;
					 seqtemp = pnxtrecS->seqno;
					 seqtime = seqtime + 1;
				}
			}
			//(pnxtrec2->qtydone > 1&&prec->qtydone<=1)
			// newQty = (int)(pjob->cjobdrVec[i].prevScrapCount + 1 - pjob->cjobdrVec[i].qtydone) ; 
			if(i<(int)(prv->size())-1&&prec->seqno != 780)
			{
				RouteDataRec *pnxtrec2 = &((*prv)[i+1]) ; 
				if(prec->seqno<seqtemp&&MatchScrap)
				{
					for(int z = i+1; z>0; z--)
					{
						RouteDataRec *prec = &((*prv)[z-1]) ; 
						if(prec->pendingRunTime == 0&&prec->qtydone<=seqtime+1 - prec->qtydone)
						{
							if(prec->seqno!=100&&(prec->seqno==20||prec->seqno==30||prec->seqno==10))
								prec->pendingRunTime += 0.02  ;
							else if(prec->seqno!=100)
								prec->pendingRunTime += 0.02;
							//prec->runstd
						}
					}
				}
			}
			
            if (state & RUN_STATE)
            {   // Then the job is still running 
                prec->bWasStillInRunState = 1 ; 

                // If there are events after this one, then we are likely missing the stop event 
                // record. In this case we want to use the run standard, or the next event time
                // for the same resource. Even if there is another event time on the same resource
                // it may not accurately indicate the stop time, so we need to issue a warning
                // that this time may not be accurate. 


                if (rrr.size())
                {   // Then the first event is the start time record
                    int bSetStopTime = 0 ; 

                    ResRec *pres = rrr[0].prr ; 
                    int irr = rrr[0].irr ; 

                    
                    CDateTime stoptime(0,0,0,0,0,0) ; 
                    if (GetStopTime(rrr, stoptime))
                    {
                        time_t startsecs = starttime.GetTimeT() ; 
                        time_t stopsecs  = stoptime.GetTimeT() ; 

                        double runsecs = (int)(stopsecs - startsecs) ; 
                        prec->pendingRunTime += (runsecs / 3600.0) ; // convert to hours
                        bSetStopTime = 1 ; 
                    }
                    else 
                    {   // Didn't find a stop time
                        size_t ii ; 
                        for (ii = irr+1; ii < pres->evvec.size(); ii++)
                        {
                            int tasktype = pres->evvec[ii].TaskType() ;  
                            if (pres->evvec[ii].jobnum != ijm->second.jobnum)
                            {   // Then this is equivalent to a stop time, no matter
                                // what type of event this is (start or stop) 

                                CDateTime t1, t0 ; 
                                if (pres->evvec[ii].ManualTask(t1, t0))
                                {
                                    if (starttime.m_nHours > pres->evvec[ii].dt.m_nHours)
                                    {   // Then the job has run overnight ( since the events
                                        // are sorted by time to gein with). This could be because
                                        // the user forgot to log the job out. Whatever the case may
                                        // be simply record the stop top but subtract out the over-
                                        // night time period. This will always assume that the 
                                        // day shift is from 7AM to 4PM

                                        char timestr1[128] ; 
                                        char timestr2[128] ; 

                                        starttime.FormatDateTimeSecs(timestr1) ; 
                                        pres->evvec[ii].dt.FormatDateTimeSecs(timestr2) ; 
                                        fprintf(gCMSparms.pevp->fpLOG, 
                                            "Warning 0x000B, manual overnight, job=%s, part=%c, timestart=%s, timeend=%s\r\n",
                                                        ijm->second.jobnum.c_str(), 
                                                        prec->partCode, 
                                                        timestr1, timestr2) ; 

                                        fflush(gCMSparms.pevp->fpLOG) ; 

                                        int startsecs = starttime.DaySeconds() ; 
                                        int stopsecs  = pres->evvec[ii].dt.DaySeconds() ; 

                                        double runsecs = max(0, (16.0 * 3600) - startsecs) ; 
                                        runsecs += max(0, stopsecs - (7.0 * 3600)) ; 

                                        prec->pendingRunTime += runsecs / 3600.0 ; // convert to hours
                                    }
                                    else
                                    {   // Then assume that they ran on the same day. 
                                        double runsecs = 
                                            pres->evvec[ii].dt.DaySeconds() - starttime.DaySeconds() ; 
                                        prec->pendingRunTime += (runsecs / 3600.0) ; // convert to hours
                                    }
                                }
                                else
                                {   // This is an automated NC task which could run overnight so
                                    // don't apply any special logic, just use the start and stop
                                    // times as given. 


                                    time_t startsecs = starttime.GetTimeT() ; 
                                    time_t stopsecs  = pres->evvec[ii].dt.GetTimeT() ; 

                                    double runsecs = (int)(stopsecs - startsecs) ; 
                                    prec->pendingRunTime += (runsecs / 3600.0) ; // convert to hours
                                }

                                // mark as processed but indicate that it had no stoptime. 
                                pres->evvec[ii].setArcState = 'T' ; 
                                bSetStopTime = 1 ; 
                            }
                        }
                    }

					//If seq = 780 skip this
					RouteDataRec *pcrinsp = &((*prv)[i]) ;

                    if (!bSetStopTime && (i >= (int)prv->size()-1)&&pcrinsp->seqno != 780)
                    {   // Check if the next sequence step has been counted and if so then
                        // set this time to the standard runtime. 

                        RouteDataRec *pnxtrec = &((*prv)[i+1]) ; 
						RouteDataRec *pcr = &((*prv)[i]) ;
						RouteDataRec *pres = &((*prv)[i-1]) ;
                        if ((pnxtrec->RunTime() > 0) || (pnxtrec->qtydone > 0))
                        {   // Next step already done, so mark all start times as done

                            fprintf(gCMSparms.pevp->fpLOG, "Warning 0x000C, START without STOP for, job=%s, part=%c\r\n",
                                            ijm->second.jobnum.c_str(), 
                                            prec->partCode) ;
                            fflush(gCMSparms.pevp->fpLOG) ; 

                            prec->pendingRunTime += prec->runstd ; 
                            
                            fprintf(gCMSparms.pevp->fpLOG, "     ---> applying standard run time\r\n" ) ; 
                            fflush(gCMSparms.pevp->fpLOG) ; 

                            for (size_t  ii=0; ii < rrr.size(); ii++)
                            {

                                ResRec *pres = rrr[0].prr ; 
                                int ires = rrr[0].irr ; 
                                char timestr[128] ; 
                                
                                // mark as processed but indicate that it had no starttime. 
                                pres->evvec[ii].setArcState = 'S' ; 

                                fprintf(gCMSparms.pevp->fpLOG, "        ... task=%s part=%s station=%s time=%s\r\n",
                                                pres->evvec[ii].task.c_str(), 
                                                pres->evvec[ii].part.c_str(), 
                                                pres->evvec[ii].station.c_str(), 
                                                pres->evvec[ii].dt.FormatDateTimeSecs(timestr)) ; 
                                fflush(gCMSparms.pevp->fpLOG) ; 
                            }
                        }
						
                    }
                    else
                    {   // A stop time was set, so make sure the state is marked as completed
                        // for all start records ( because we got to here a dangling start exists)
                        for (size_t ii=0; ii < rrr.size(); ii++)
                        {
                            ResRec *pres = rrr[ii].prr ; 
                            int irr = rrr[ii].irr ; 
                            pres->evvec[irr].setArcState = 'T' ; 
                        }
                    }
                }
            }
            else
            {
                prec->bWasStillInRunState = 0 ; 
            }
        } 
    }

    /************************************************************************
        Go through all jobs and see which ones have gaps in the routing
        and list these for the manager to fill in the required run times. 
        Highlight the 0 time routing steps in yellow. 
     ************************************************************************/

    for (ijm = jobsmap.begin(); ijm != jobsmap.end(); ijm++)
    {
        RouteDataRecVec *prv = &(ijm->second.cjobdrVec) ;
        ijm->second.iLastSeq = -1 ; 
        ijm->second.iFirstZSeq = -1 ; 
        for (i=0; i < (int)(prv->size()) ; i++)
        {
            RouteDataRec *prec = &((*prv)[i]) ; 

            if ((ijm->second.iFirstZSeq < 0) &&   
                ((prec->RunTime() == 0.0) && (prec->lastEventTime.m_nYear == 0))
               )
            {
                ijm->second.iFirstZSeq = i ; 
            }

            // Remember the last active sequence number for the job
            if ((prec->RunTime() > 0.001) ||
                (prec->lastEventTime.m_nYear != 0))
            {
                ijm->second.iLastSeq = i ; 
            }
        }

        // if (ijm->second.iLastSeq >= 0)
        // {   // Add 1 for the 0 index counting and 1 more for the extra blank line 
        //     // after each job
        //     numRows += (ijm->second.iLastSeq + 2) ; 
        // }

    }


    /************************************************************************
        Need to verify all the serial numbers based on quantity available

     ************************************************************************/
	// remove serialnum
    //LoadSerialNumbers() ;
    numRows = 0 ;

    // Assign default serial numbers as required
    for (ijm = jobsmap.begin(); ijm != jobsmap.end(); ijm++)
    {
        if (ijm->second.jobstatus == 'C') 
            continue ; // skip completed jobs

        RouteDataRecVec &rdrv = ijm->second.cjobdrVec ;

        numRows += (int)rdrv.size() + 1 ; 

        // TODO - MAY NEED TO ADD THIS IF BACK
        // if (ijm->second.iFirstZSeq >= ijm->second.iLastSeq)
        //      continue ; // don't output this job reecord

        for (i=0; i < (int)rdrv.size() ; i++)
        {
            RouteDataRec *prr = &rdrv[i] ; 

            // The logic here is convoluted. TODO - fix this.
            if (prr->RunTime() == 0 && prr->lastEventTime.m_nYear == 0)
            {
				
                if (prr->serialnum == 0 && prr->seqno == 100 && (i < ijm->second.iLastSeq))
                {   // Then this is a saw operation with a zero quantity, so we are also
                    // going to fill in the serial number to the first in available 
                    // material that matches. 
                    
                    // If this is the last active sequence step for the part then do not 
                    // fill in the default serial# - the (ijm->second.iLastSeq > i) in the if
					//remove serialnum
                 //   FindMatchingSerial(ijm, prr) ; 
                    prr->assignedSerial = 1 ; // set to true
					prr->serialnum = 001; // REMOVE SERIALNUM
                }
            }
        }
    }

    // At this point we have to verify that there is sufficient material for the 
    // serial number that is defined for the saw operation. If the serial number
    // was assigned, then these are mapped to different materials first. In other 
    // words, saw records that had actual serial numbers are given priority and 
    // an attempt is made to preserve those serial numbers. Then once all material 
    // is consumed for the !assignedSerial records, the processing continues 
    // and assigns serial numbers to all records which have not been processed yet. 
    // assignedSerial = true = the operator didn't enter a value and the system
    //                         assigned a serial number value for the record
    // 
    // This process will work in two stages. 
    //   1) Go through and flag all !assignedSerial records that have sufficient material
    //   2) Go through and flag all remaining !processedSerial records


    // The serialnum field will have already been defaulted in the cjobdrVec[] data 
    // by this point, so we can now scan to verify available material quantities
    // --------------------------------------------------------------------------
    //                          STAGE 1
    // --------------------------------------------------------------------------
	/*//Remove Serialnum

    for (ijm = jobsmap.begin(); ijm != jobsmap.end(); ijm++)
    {
        if (ijm->second.subCount > 1)
            continue ; // ignore master records. 

        // See if there is a SEQ# 100 or 105 consumption step here. 
        RouteDataRecVec &drvec = ijm->second.cjobdrVec ; 
        int iSeq = -1 ;
        for (i=0; i < (int)drvec.size(); i++)
        {
            if (drvec[i].seqno == 100 || drvec[i].seqno == 105)
            {
                if (drvec[i].serialnum > 0)
                    iSeq = i ; // then we are processing this material record
                break ; 
            }
        }

		

        if (iSeq < 0 || drvec[i].assignedSerial)
        {   // Skip assignedSerial records in this stage of processing
            continue ; // no material consumption records in this job
        }

        MaterialRecMapItr imm = mtlmap.find(drvec[i].material) ; 
        if (imm == mtlmap.end())
        {   // Error
            fprintf(gCMSparms.pevp->fpLOG, "ERROR %s not found in mtlmap, job=%s\r\n",
                            ijm->second.mattype.c_str(), ijm->second.jobnum.c_str()) ; 
            fflush(gCMSparms.pevp->fpLOG) ; 
            continue ; 
        }


        // Work through the serial numbers to see which one has available material
        // First see if the serial number selected has material available. 
		
        SerialRecMapItr isr = imm->second.sermap.find(drvec[i].serialnum) ;
        if (isr != imm->second.sermap.end())
        {   // See if we're OK
            SerialRec &srec = isr->second ;
            // TODO - there may be floating point rounding issues here between how 
            // Solarsoft calculates material. If it is a problem then might have to 
            // include a tolerance factor in the comparison.
            if (srec.seriqty - srec.usedqty - srec.consqty >= drvec[i].mtlqty)
            {   // Then this serial is good to use
                srec.usedqty += drvec[i].mtlqty ;
                drvec[i].processedSerial = 1 ;
            }
            else
            {
                fprintf(gCMSparms.pevp->fpLOG,
                        "WARNING: serial# %d entered at SAW has insufficient material=%s for job=%s, next available serial will be assigned automatically.\r\n",
                                drvec[i].serialnum,
                                ijm->second.mattype.c_str(),
                                ijm->second.jobnum.c_str()) ;
                fflush(gCMSparms.pevp->fpLOG) ;
            }
        }
        else
        {
            fprintf(gCMSparms.pevp->fpLOG, "ERROR: serial# %d not found in serial map for MTL=%s, job=%s\r\n",
                            drvec[i].serialnum,
                            ijm->second.mattype.c_str(),
                            ijm->second.jobnum.c_str()) ;
            fflush(gCMSparms.pevp->fpLOG) ;
        }
    }

    // --------------------------------------------------------------------------
    //                          STAGE 2
    // --------------------------------------------------------------------------
    // For all the assigned serial numbers, or for actual SAW records where there 
    // was insufficient material, simply assign serials based on availability. 
    for (ijm = jobsmap.begin(); ijm != jobsmap.end(); ijm++)
    {
        if (ijm->second.subCount > 1)
            continue ; // ignore master records. 

        // See if there is a SEQ# 100 or 105 consumption step here. 
        RouteDataRecVec &drvec = ijm->second.cjobdrVec ; 
        int iSeq = -1 ;
        for (i=0; i < (int)drvec.size(); i++)
        {
            if (drvec[i].seqno == 100 || drvec[i].seqno == 105)
            {
                if (drvec[i].serialnum > 0)
                    iSeq = i ; // then we are processing this material record
                break ; 
            }
        }

        if (iSeq < 0 || drvec[i].processedSerial)
        {   // Skip processedSerial records in this stage of processing
            continue ; // or no material consumption records in this job (iSeq<0 condition)
        }

        MaterialRecMapItr imm = mtlmap.find(drvec[i].material) ; 
        if (imm == mtlmap.end())
        {   // Error
            fprintf(gCMSparms.pevp->fpLOG, "ERROR %s not found in mtlmap, job=%s\r\n",
                            ijm->second.mattype.c_str(), ijm->second.jobnum.c_str()) ; 
            fflush(gCMSparms.pevp->fpLOG) ; 
            continue ; 
        }


        // Work through the serial numbers to see which one has available material
        // First see if the serial number selected has material available. 
        SerialRecMapItr isr = imm->second.sermap.find(drvec[i].serialnum) ; 
        if (isr != imm->second.sermap.end())
        {   // See if we're OK
            SerialRec &srec = isr->second ; 
            // TODO - there may be floating point rounding issues here between how 
            // Solarsoft calculates material. If it is a problem then might have to 
            // include a tolerance factor in the comparison. 
            if (srec.seriqty - srec.usedqty - srec.consqty >= drvec[i].mtlqty) 
            {   // Then this serial is good to use
                srec.usedqty += drvec[i].mtlqty ; 
                drvec[i].processedSerial = 1 ;
                continue ; 
            }
        }
        else
        {   
            fprintf(gCMSparms.pevp->fpLOG, "ERROR: serial# %d not found in serial map for MTL=%s, job=%s\r\n",
                            drvec[i].serialnum, 
                            ijm->second.mattype.c_str(), 
                            ijm->second.jobnum.c_str()) ; 
            fflush(gCMSparms.pevp->fpLOG) ; 
        }

        // If we get to here then need to search for available material
        isr = imm->second.sermap.begin() ; 
        while (isr != imm->second.sermap.end() )
        {
            SerialRec &srec = isr->second ; 
            if (srec.seriqty - srec.usedqty - srec.consqty > drvec[i].mtlqty) 
            {   // Then use this serial number
                drvec[i].serialnum = srec.sernum ; 
                srec.usedqty += drvec[i].mtlqty ; 
                if (drvec[i].assignedSerial)
                    drvec[i].processedSerial = 1 ; 
                else
                    drvec[i].processedSerial = 3 ; // indicate that it had a valid value which was overwritten
                break ; 
            }

            isr++ ;  
        }
    }
	 *///Remove Serialnum


    // Now go through and list those jobs which are still active. 
    // Set the time to 5:00 AM, anything before this is considered to have happened in the 
    // previous shift. 
    CDateTime dtnow ; 
    dtnow.SetNow() ; 
    dtnow.SetTime(4,0,0) ; 

    // Initialize the grid
    //int nCols = 10 ;
    int nCols = 8 ;
    m_grid.Clear() ; 

    for(i = 0; i < nCols; i++)
    {   // Set the text alignment in the columns
        m_grid.put_ColAlignment(i, CMsflexgrid1::flexAlignLeftCenter) ;
    }

    m_grid.put_ColWidth(0,8000); //Combined Field
    m_grid.put_ColWidth(1,450) ;  // qty
    m_grid.put_ColWidth(2,450) ;  // scrap
    m_grid.put_ColWidth(3,500) ;  // serial 
    m_grid.put_ColWidth(4,650) ;  // runtime
    m_grid.put_ColWidth(5,650) ;  // pending 
    m_grid.put_ColWidth(6,600) ;  // actual time
    m_grid.put_ColWidth(7,500) ;  // Serial
    m_grid.put_ColWidth(8,2800) ;  // decade track info

    // m_grid.put_ColWidth(0,750) ; // width in pico points or something like that
    // m_grid.put_ColWidth(1,1800) ; // part
    // m_grid.put_ColWidth(2,700) ;  // resource
    // m_grid.put_ColWidth(3,600) ; // SEQ#
    // m_grid.put_ColWidth(4,1100) ; // Job#
    // m_grid.put_ColWidth(5,1200) ; // start time
    //m_grid.put_ColWidth(6,600) ;  // qty
    //m_grid.put_ColWidth(7,900) ;  // serial#
    //m_grid.put_ColWidth(8,800) ;  // runtime 
    // m_grid.put_ColWidth(9,800) ;  // runstd
    //m_grid.put_ColWidth(10,900) ;  // pending 
    //m_grid.put_ColWidth(11,900) ;  // actual time
    //m_grid.put_ColWidth(12,900) ;  // serial#

    // Order#, Part#, Machine, Status, Start Time, RunTime, Actual
    // Row, column, text

    char combinedHeader[256] ; 
    sprintf(combinedHeader, 
        "%-6s; %-20s; %-5s; %-3s; %-10s; %-13s; %-5s", 
        "SO#", "Part", "Res", "SEQ", "Job#", "StartTime", "RunStd") ; 

    m_grid.put_TextMatrix(0,0,combinedHeader) ;
    m_grid.put_TextMatrix(0,1,"Qty") ;
    m_grid.put_TextMatrix(0,2,"Scrp") ;
    m_grid.put_TextMatrix(0,3,"Ser#") ;
    m_grid.put_TextMatrix(0,4,"RunTime") ;
    m_grid.put_TextMatrix(0,5,"Pend'g") ;
    m_grid.put_TextMatrix(0,6,"Actual") ;
    m_grid.put_TextMatrix(0,7,"Ser#") ;
    m_grid.put_TextMatrix(0,8,"Decade Trk Info") ;

    /*m_grid.put_TextMatrix(0,0,"SO#") ;
    m_grid.put_TextMatrix(0,1,"PART") ;
    m_grid.put_TextMatrix(0,2,"RES") ;
    m_grid.put_TextMatrix(0,3,"Seq#") ;
    m_grid.put_TextMatrix(0,4,"Job#") ;
    m_grid.put_TextMatrix(0,5,"StartTime") ;
    m_grid.put_TextMatrix(0,6,"Qty") ;
    m_grid.put_TextMatrix(0,7,"Scrap") ;
    m_grid.put_TextMatrix(0,8,"Serial#") ;
    m_grid.put_TextMatrix(0,9,"RunTime") ;
    m_grid.put_TextMatrix(0,10,"RunStd") ;
    m_grid.put_TextMatrix(0,11,"Pending") ;
    m_grid.put_TextMatrix(0,12,"Actual") ;
    m_grid.put_TextMatrix(0,13,"Ser#") ;*/

    m_grid.put_Rows((long)numRows + 1) ;

    char soNum[16] ; //
    char seqnumstr[16] ; 
    char sernumstr[16] ; 
    char *pstat ; 
    char combinedField[2048];

	int iQT = 1 ; // index of quantity column
    int iAC = 6 ; // index of actual column
    int iPG = 0 ;  // run std column
	int iSC = 2 ; //Scrap Column

    //int iQT = 6 ; // index of quantity column
    //int iAC = 12 ; // index of actual column
    //int iPG = 10 ;  // run std column

    int nrow = 1 ; 
    // CMSJob


    for (ijm = jobsmap.begin(); ijm != jobsmap.end(); ijm++)
    {
        if (ijm->second.jobstatus == 'C') 
            continue ; // skip completed jobs

        char timestr[64] ;
        char runtime[64] ; 
        char runtimestd[64] ; 
        char qtystr[64] ; 
        char qtysstr[64] ; 
        char pending[64] ; 
		
        RouteDataRecVec *prv = &(ijm->second.cjobdrVec) ;

        // TODO - MAY NEED TO ADD THIS IF BACK
        // if (ijm->second.iFirstZSeq >= ijm->second.iLastSeq)
        //      continue ; // don't output this job reecord

		CMSJob *pjob = &(ijm->second) ; 
		if (decOpen)
			LoadDecadeEvents(pjob, &ddb) ; 

		for (i=0; i < (int)ijm->second.cjobdrVec.size() ; i++)
		{
			RouteDataRec *prr = &(*prv)[i] ; 

			CDate d ;

			if (prr->starttime.m_nYear == 0 && 
				prr->lastEventTime.m_nYear != 0)
			{
				sprintf(timestr, "%s-%d,%02d:%02d",
					d.MonthStringShort(prr->lastEventTime.m_nMonth),
					prr->lastEventTime.m_nDay, 
					prr->lastEventTime.m_nHours,
					prr->lastEventTime.m_nMins) ;
			}
			else
			{
				sprintf(timestr, "%s-%d,%02d:%02d",
					d.MonthStringShort(prr->starttime.m_nMonth),
					prr->starttime.m_nDay, 
					prr->starttime.m_nHours,
					prr->starttime.m_nMins) ;
			}

			if (strncmp(timestr, "Err", 3) == 0)
				strcpy(timestr, "------") ; 


			sprintf(soNum, "%s", ijm->second.ordNum.c_str()) ; 
			sprintf(seqnumstr, "%03d", prr->seqno) ; 

			pstat = "???" ; 

			sprintf(runtime,    "%.2f", prr->totalRunTime) ; 
			sprintf(pending,    "%.2f", prr->pendingRunTime) ; 
			sprintf(runtimestd, "%.2f", prr->runstd) ; 

			sprintf(qtystr, "%d", (int)(prr->qtydone)) ; 
			sprintf(qtysstr, "%d", (int)(prr->qtyscrap)) ; 


			if (prr->serialnum != 0)
			{   // Display the serial number for this position
				sprintf(sernumstr, "%d", prr->serialnum) ; 
			}
			else
			{   // blank out the serial number
				sernumstr[0] = 0x20 ; 
				sernumstr[1] = 0 ; 
			}

			sprintf(combinedField, 
				"%-6s; %-20s; %-5s; %-3s; %-10s; %-13s; %-5s", 
						soNum, 
						ijm->second.partname.c_str(), 
						(*prv)[i].resource.c_str(), 
						seqnumstr,
						ijm->second.jobnum.c_str(),
						timestr, 
						runtimestd);


			/*combineField = soNum+ijm->second.partname.c_str()+(*prv)[i].resource.c_str();*/
			// soNum+ijm->second.partname.c_str()+(*prv)[i].resource.c_str()+seqnumstr+ijm->second.jobnum.c_str()+timestr+runtimestd
			//m_grid.put_TextMatrix(

			m_grid.put_TextMatrix(nrow, 0, combinedField) ; 
			m_grid.put_TextMatrix(nrow, 1,  qtystr) ; 
			m_grid.put_TextMatrix(nrow, 2,  qtysstr) ; 
			m_grid.put_TextMatrix(nrow, 3,  sernumstr) ; 
			m_grid.put_TextMatrix(nrow, 4,  runtime) ; 
			m_grid.put_TextMatrix(nrow, 5, pending) ; 
			m_grid.put_TextMatrix(nrow, 6, "") ; 
			m_grid.put_TextMatrix(nrow, 7, "") ; 

			if (pjob->cjobdrVec[i].decadeTask[0])
				m_grid.put_TextMatrix(nrow, 8, pjob->cjobdrVec[i].decadeTask) ; 

			/*m_grid.put_TextMatrix(nrow, 0,  soNum) ;
			m_grid.put_TextMatrix(nrow, 1,  ijm->second.partname.c_str()) ; 
			m_grid.put_TextMatrix(nrow, 2,  (*prv)[i].resource.c_str()) ; 
			m_grid.put_TextMatrix(nrow, 3,  seqnumstr) ; 
			m_grid.put_TextMatrix(nrow, 4,  ijm->second.jobnum.c_str()) ; 
			m_grid.put_TextMatrix(nrow, 5,  timestr) ; 
			m_grid.put_TextMatrix(nrow, 6,  qtystr) ; 
			m_grid.put_TextMatrix(nrow, 7,  qtysstr) ; 
			m_grid.put_TextMatrix(nrow, 8,  sernumstr) ; 
			m_grid.put_TextMatrix(nrow, 9,  runtime) ; 
			m_grid.put_TextMatrix(nrow, 10, runtimestd) ; 
			m_grid.put_TextMatrix(nrow, 11, pending) ; 
			m_grid.put_TextMatrix(nrow, 12, "") ; 
			m_grid.put_TextMatrix(nrow, 13, "") ; */

			// The logic here is convoluted. TODO - fix this.
			if (prr->RunTime() == 0 && prr->lastEventTime.m_nYear == 0)
			{
				m_grid.put_Row(nrow) ; 
				m_grid.put_Col(iAC) ; 
				m_grid.put_CellBackColor(RGB(255,255,0)) ; // yellow
				prr->bSetStdRunIfBlank = 0x01 ;
				if (prr->assignedSerial)
				{   // Then this is a saw operation with a zero quantity, so we are also
					// going to fill in the serial number to the first in available 
					// material that matches. 

					// If this is the last active sequence step for the part then do not 
					// fill in the default serial# - the (ijm->second.iLastSeq > i) in the if

					csString serNumStr ; 
					if (prr->serialnum != 0)
					{   // Then fill in the serial number and highlight in red.
						sprintf(sernumstr, "%d", prr->serialnum) ; 
						m_grid.put_TextMatrix(nrow, 3,  sernumstr) ;
						m_grid.put_Row(nrow) ; 
						m_grid.put_Col(3) ; 

						m_grid.put_CellBackColor(RGB(255,128,128)) ; // light red
					}
				}
			}

			if (i > ijm->second.iLastSeq)
			{   // gray out the box since the user doesn't need to deal with this
				// one
				m_grid.put_Row(nrow) ;
				m_grid.put_Col(iAC) ; 
				m_grid.put_CellBackColor(RGB(175,175,175)) ; // gray 
				prr->bSetStdRunIfBlank = 0 ;
			}
			else 
			{
				if (fabs(prr->qtydone) < 0.01 && (i <= ijm->second.iLastSeq))
				{   // Then highlight to the user in red that it will be updated to qty = 1
					m_grid.put_Row(nrow) ;
					m_grid.put_Col(iQT) ; 
					m_grid.put_CellBackColor(RGB(255,75,75)) ; // light red
				}
			}

			//if blue has been loooked at ignore this.
			if (prr->totalRunTime + prr->pendingRunTime >  (3.0 * prr->runstd))
			{
				m_grid.put_Row(nrow) ;
				m_grid.put_Col(iPG) ; 
				m_grid.put_CellBackColor(RGB(155,155,255)) ; // blue
				//Update database otherinfor to 1.
			}

			if(prr->qtyscrap>0)
			{
				m_grid.put_Row(nrow) ;
                m_grid.put_Col(iSC) ; 
                m_grid.put_CellBackColor(RGB(50,205,50)); //green
			}

			nrow++ ; 
		}
		nrow++ ; // leave a blank line
	}

	m_Progress.SetPos(0);
	numRows = nrow ; 
	int tetprogress = 0;

		//	ppdlg->SendMessage(WM_CLOSE, 0, 0) ; 

}



void CBatchUPDDlg::FindMatchingSerial(CMSJobMapItr &ijm, RouteDataRec *prr)
{
    CBatchUPDApp *pApp = (CBatchUPDApp *)AfxGetApp() ; 
    char qry[1024] ; 

    _snprintf(qry, 0x3FF0,
        "SELECT HTSERN,HTQTY,HTQTYC FROM %s.SERI WHERE HTPLNT='%s' AND HTPART = '%s' AND HTSTS IN ('A')"
        " ORDER BY HTADAT",
        gCMSparms.dbname, gCMSparms.plantID, prr->material.c_str()) ;

    //     B.DNORD# = '226737' AND 

    try
    {
        csString sern(100), qty(100), qtyc(100) ; 

        CSQLRecordset rs(pApp->cmsdata.m_db) ;
        rs << qry ; 
        rs.SQLExec();
        while (rs.SQLFetch())
        {
            int fldnum = 1 ; 

            sern.len    = CS_strmaxcat(sern.str    , rs.SQLGetData(fldnum++).c_str(), 60) ;
            qty.len     = CS_strmaxcat(qty.str     , rs.SQLGetData(fldnum++).c_str(), 60) ;
            qtyc.len    = CS_strmaxcat(qtyc.str    , rs.SQLGetData(fldnum++).c_str(), 60) ;

            sern.Trim() ; 
            qty.Trim() ; 

            double Q = atof(qty.c_str()) ; 
            double QC = atof(qtyc.c_str()) ; 

            if ((Q - QC) >= prr->mtlqty)
            {
                prr->serialnum = atoi(sern.c_str()) ; 
                break ; 
            }
        }
    }
    catch (CSQLException* e)
    {
        if (gCMSparms.pevp->fpLOG)
        {
            fprintf(gCMSparms.pevp->fpLOG, "SQL error %d trying to find best serial number match:\n%s\n",
                (int)e->m_nRetCode, e->m_strError.c_str()) ;
            fflush(gCMSparms.pevp->fpLOG) ; 
        }
    }
}


int CBatchUPDDlg::ValidateSerialNumber(CMSJobMapItr &ijm, RouteDataRec *prr, int sernum)
{

	CBatchUPDApp *pApp = (CBatchUPDApp *)AfxGetApp() ; 
	char qry[1024] ; 
	//Changed HTSTS IN ('A') to HTSTS IN ('N') on 2011/03/21
	_snprintf(qry, 0x3FF0,
		"SELECT HTSERN,HTQTY,HTQTYC FROM %s.SERI WHERE HTPLNT='%s' AND HTPART = '%s'"
		" AND (HTQTY - HTQTYC) > %.2f AND HTSTS IN ('A')"
		" ORDER BY HTADAT",
		gCMSparms.dbname, gCMSparms.plantID, 
		prr->material.c_str(), prr->mtlqty) ;

	//     B.DNORD# = '226737' AND 

	try
	{
		csString sern(100), qty(100), qtyc(100) ; 

		CSQLRecordset rs(pApp->cmsdata.m_db) ;
		rs << qry ; 
		rs.SQLExec();

		int foundSerial = 0 ; 
		int firstGoodSerial = 0 ; 
		int foundSerial2 = 0;
		while (rs.SQLFetch())
		{
			int fldnum = 1 ; 

			sern.len    = CS_strmaxcat(sern.str    , rs.SQLGetData(fldnum++).c_str(), 60) ;
			qty.len     = CS_strmaxcat(qty.str     , rs.SQLGetData(fldnum++).c_str(), 60) ;
			qtyc.len    = CS_strmaxcat(qtyc.str    , rs.SQLGetData(fldnum++).c_str(), 60) ;

			sern.Trim() ; 
			qty.Trim() ; 
			qtyc.Trim() ; 

			int snum = atoi(sern.c_str()) ; 

			if (sernum == snum)
			{
				foundSerial = 1 ; 
				break ;
			}

			if (firstGoodSerial == 0)
				firstGoodSerial = snum ; 
		}
		if(!foundSerial)
		{
			char qry2[1024] ; 
			//Changed HTSTS IN ('A') to HTSTS IN ('N') on 2011/03/21
			_snprintf(qry2, 0x3FF0,
				"SELECT HTSERN,HTQTY,HTQTYC FROM %s.SERI WHERE HTPLNT='%s' AND HTPART = '%s'"
				" AND (HTQTY - HTQTYC) > %.2f AND HTSTS IN ('N')"
				" ORDER BY HTADAT",
			gCMSparms.dbname, gCMSparms.plantID, 
			prr->material.c_str(), prr->mtlqty) ;
			try
			{
				csString sern(100), qty(100), qtyc(100) ; 

				CSQLRecordset rs(pApp->cmsdata.m_db) ;
				rs << qry2 ; 
				rs.SQLExec();

				
				while (rs.SQLFetch())
				{
					int fldnum = 1 ; 

					sern.len    = CS_strmaxcat(sern.str    , rs.SQLGetData(fldnum++).c_str(), 60) ;
					qty.len     = CS_strmaxcat(qty.str     , rs.SQLGetData(fldnum++).c_str(), 60) ;
					qtyc.len    = CS_strmaxcat(qtyc.str    , rs.SQLGetData(fldnum++).c_str(), 60) ;

					sern.Trim() ; 
					qty.Trim() ; 
					qtyc.Trim() ; 

					int snum = atoi(sern.c_str()) ; 

					if (sernum == snum)
					{
						foundSerial2 = 1 ; 
						break ;
					}

					if (firstGoodSerial == 0)
						firstGoodSerial = snum ; 
				}
			}
			catch (CSQLException* e)
			{
				if (gCMSparms.pevp->fpLOG)
				{
					fprintf(gCMSparms.pevp->fpLOG, "SQL error %d trying to find best serial number match:\n%s\n",
						(int)e->m_nRetCode, e->m_strError.c_str()) ;
					fflush(gCMSparms.pevp->fpLOG) ; 
				}
			}
		}
		if (!foundSerial&&!foundSerial2)
			sernum = firstGoodSerial ; 
	}
	catch (CSQLException* e)
	{
		if (gCMSparms.pevp->fpLOG)
		{
			fprintf(gCMSparms.pevp->fpLOG, "SQL error %d trying to find best serial number match:\n%s\n",
				(int)e->m_nRetCode, e->m_strError.c_str()) ;
			fflush(gCMSparms.pevp->fpLOG) ; 
		}
	}

	return sernum ; 
}



int CBatchUPDDlg::LoadSerialNumbers()
{

	CBatchUPDApp *pApp = (CBatchUPDApp *)AfxGetApp() ; 
	char qry[1024] ; 



	_snprintf(qry, 0x3FF0,
		"SELECT HTSERN,HTPART,HTQTY,HTQTYC FROM %s.SERI WHERE HTPLNT='%s' "
		" AND (HTQTY - HTQTYC) > 0.0 AND HTSTS IN ('A')"
		" ORDER BY HTSERN",
		gCMSparms.dbname, gCMSparms.plantID) ;

	//     B.DNORD# = '226737' AND 

	try
	{
		csString sern(100), part(100), qty(100), qtyc(100) ; 

		CSQLRecordset rs(pApp->cmsdata.m_db) ;
		rs << qry ; 
		rs.SQLExec();

		sermap.clear() ; 
		mtlmap.clear() ; 

		while (rs.SQLFetch())
		{
			int fldnum = 1 ; 

			sern.len    = CS_strmaxcat(sern.str    , rs.SQLGetData(fldnum++).c_str(), 60) ;
			part.len    = CS_strmaxcat(part.str    , rs.SQLGetData(fldnum++).c_str(), 60) ;
			qty.len     = CS_strmaxcat(qty.str     , rs.SQLGetData(fldnum++).c_str(), 60) ;
			qtyc.len    = CS_strmaxcat(qtyc.str    , rs.SQLGetData(fldnum++).c_str(), 60) ;

			sern.Trim() ; 
			part.Trim() ; 
			qty.Trim() ; 
			qtyc.Trim() ; 


			MaterialRecMapItr imm = mtlmap.find(part) ; 
			if (imm == mtlmap.end())
			{   // Then add this record to the map
				MaterialRec mrec ; 
				mrec.mtl = part ; 

				pair<MaterialRecMapItr, bool> ins = mtlmap.insert(make_pair(part, mrec)) ; 
				if (ins.second)
				{   // Then we have a valid material record
					imm = ins.first ; 
				}
				else
				{
					fprintf(gCMSparms.pevp->fpLOG, "SERIAL MAP ERROR, failed to create entry for '%s'\n",
						part.c_str()) ; 
					fflush(gCMSparms.pevp->fpLOG) ; 
					continue ; 
				}
			}

			int sernum = atoi(sern.c_str()) ; 
			SerialRecMapItr isr = sermap.find(sernum) ; 
			if (isr == sermap.end())
			{
				SerialRec srec ;
				srec.imm = imm ; 
				srec.seriqty = atof(qty.c_str()) ; 
				srec.consqty = atof(qtyc.c_str()) ; 
				srec.usedqty = 0 ; // initialize to zero. 
				srec.sernum = sernum ; 

				pair<SerialRecMapItr, bool> iser = sermap.insert(make_pair(sernum, srec)) ; 

				// Now add this record to the material map record also
				imm->second.sermap.insert(make_pair(sernum, srec)) ; 
			}
			else
			{
				fprintf(gCMSparms.pevp->fpLOG, "SERIAL MAP ERROR, serial number %d already exists\n",
					sernum) ; 
				fflush(gCMSparms.pevp->fpLOG) ; 
				continue ; 
			}
		}
	}
	catch (CSQLException* e)
	{
		if (gCMSparms.pevp->fpLOG)
		{
			fprintf(gCMSparms.pevp->fpLOG, "SQL error %d trying to find best serial number match:\n%s\n",
				(int)e->m_nRetCode, e->m_strError.c_str()) ;
			fflush(gCMSparms.pevp->fpLOG) ; 
		}
	}

	return 0 ; 
}