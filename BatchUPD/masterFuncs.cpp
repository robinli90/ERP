// masterFuncs.cpp

#include "stdafx.h"
#include "BatchUPD.h"
#include "BatchUPDDlg.h"

int SQL_ConvertTime(const char *str, CDateTime &dt) ;


int CBatchUPDDlg::GetStopTime(ResRecRefVec &rrr, CDateTime &stoptime)
{
    CBatchUPDApp *pApp = (CBatchUPDApp *)AfxGetApp() ; 


    ResRec *pres = rrr[0].prr ; 
    int irr = rrr[0].irr ;  // index into the resource events
    // pres is the resource reference.
    
    BEventRec *prec = &(pres->evvec[irr]) ;

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

    int foundStop = 0 ;

    char qry[1024] ; 
    try
    {
        char timestr[64] ; 
        prec->dt.FormatDateTimeSecs(timestr) ; 

        _snprintf(qry, 0x3FF0,
            "SELECT SONUM,EMPNUM,PRTCODE,TASK,TASKTIME,STATION,RTYPE,ARC,N1,N2,R1,R2,S1,S2 FROM"
            " %s.EXCOTASK WHERE PLANT='%s' AND STATION = '%s' AND TASKTIME > '%s' ORDER BY TASKTIME"
            " FETCH FIRST 30 ROWS ONLY", 
                gCMSparms.dbname, gCMSparms.plantID, prec->station.c_str(), timestr) ; 

        //   SONUM = '225689' AND 

        CSQLRecordset rs(pApp->cmsdata.m_db) ;
        rs << qry ; 
        rs.SQLExec();
        
        int count = 0 ; 

        while (rs.SQLFetch())
        {
            int fldnum = 1 ; 

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

            CDateTime dt ; 
            SQL_ConvertTime(tasktime.c_str(), dt) ; 
            time_t eventTime = dt.GetTimeT() ; 

            // This only matters on N1/N0 type operations, so any N1 record with different SO# will
            // be a stop, or any N0 period. 
            
            int son = atoi(sonum.c_str()) ; 
            if ((task == "N0") || 
                (task == "N1" && (son != prec->ordnum || prec->part != prtcode)) 
               )
            {   // If any of these hold true then the job is probably done.  
                stoptime = dt ; 
                foundStop = 1 ; 
                break ; 
            }
            if (son != prec->ordnum && (count > 15))
            {   // This is a last ditch attempt at trapping bad data 
                stoptime = prec->dt ; 
                time_t tt = stoptime.GetTimeT() ; 
				//tt += 60 //set to one minute
                tt += 0 ; // set to 0 minute
                stoptime.SetTime(tt) ; 
                foundStop = 1 ; 
                break ; 
            }

            count++ ; 
        }
    }
    catch (CSQLException* e)
    {
        if (gCMSparms.pevp->fpLOG)
        {
            fprintf(gCMSparms.pevp->fpLOG, "SQL error executing '%s' \r\n '%d' \r\n  %s\r\n",
                        qry, (int)e->m_nRetCode, e->m_strError.c_str()) ;
            fflush(gCMSparms.pevp->fpLOG) ; 
        }
    }

    return foundStop ; 
}


/*int CBatchUPDDlg::GetNitridInfor(ResRecRefVec &rrr)
{
	CBatchUPDApp *pApp = (CBatchUPDApp *)AfxGetApp() ; 


    ResRec *pres = rrr[0].prr ; 
    int irr = rrr[0].irr ;  // index into the resource events
    // pres is the resource reference.
    
    BEventRec *prec = &(pres->evvec[irr]) ;

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

    int foundNI = -1 ;

    char qry[1024] ; 
    try
    {
        char timestr[64] ; 
        prec->dt.FormatDateTimeSecs(timestr) ; 

        _snprintf(qry, 0x3FF0,
            "SELECT SONUM,EMPNUM,PRTCODE,TASK,TASKTIME,STATION,RTYPE,ARC,N1,N2,R1,R2,S1,S2 FROM"
            " %s.EXCOTASK WHERE PLANT='%s' AND STATION = '%s' AND TASKTIME > '%s' ORDER BY TASKTIME"
            " FETCH FIRST 30 ROWS ONLY", 
                gCMSparms.dbname, gCMSparms.plantID, prec->station.c_str(), timestr) ; 

        //   SONUM = '225689' AND 

        CSQLRecordset rs(pApp->cmsdata.m_db) ;
        rs << qry ; 
        rs.SQLExec();
        
        int count = 0 ; 

        while (rs.SQLFetch())
        {
            int fldnum = 1 ; 

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

            
			if(task == "NS"&& arc == "N")
			{
				NitridS = 1;
				NitridArc = 1;
				foundNI = 1;
			}
            
            count++ ; 
        }
    }
    catch (CSQLException* e)
    {
        if (gCMSparms.pevp->fpLOG)
        {
            fprintf(gCMSparms.pevp->fpLOG, "SQL error executing '%s' \r\n '%d' \r\n  %s\r\n",
                        qry, (int)e->m_nRetCode, e->m_strError.c_str()) ;
            fflush(gCMSparms.pevp->fpLOG) ; 
        }
    }

    return foundNI ; 
}*/