// used to laod Decade task lists


#include "stdafx.h"
#include "BatchUPD.h"
#include "BatchUPDDlg.h"


int LoadDecadeEvents(CMSJob *pjob, CCMSDatabase *pdb) 
{

    char qry[4096] ; 

    try
    {
        char partcode = 0 ; 
        int nevents = 0 ; 
        if (pjob->subCount > 1)
        {
            partcode = 'G' ; 
        }
        else
        {
            partcode = PartCodeCharFromCMSPart(pjob->partname) ;
        }

        sprintf(qry, "SELECT task,station,tasktime FROM d_task WHERE ordernumber=%s AND part='%c' ORDER BY tasktime DESC", 
                pjob->ordNum.c_str(), partcode) ;

        CSQLRecordset rs(*pdb) ;
        rs << qry ; 
        rs.SQLExec();
        while (rs.SQLFetch())
        {
            if ((nevents >= (int)pjob->cjobdrVec.size())  ||
                (nevents > 8))
            {
                break ; // exit
            }

            csString task       =  rs.SQLGetData(1).c_str()  ;
            csString station    =  rs.SQLGetData(2).c_str()  ;
            csString tasktime   =  rs.SQLGetData(3).c_str()  ;

            task.Trim() ; 
            station.Trim() ; 
            tasktime.Trim() ; 

            sprintf(pjob->cjobdrVec[nevents++].decadeTask, 
                        "%-3s %-5s %s", 
                        task.c_str(), 
                        station.c_str(), 
                        tasktime.c_str()) ; 
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