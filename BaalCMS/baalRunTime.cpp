// baalRunTime.cpp

#include "stdafx.h"
#include <conio.h>
#include <list>
#include <CSStdlibs/cslib.h>

// This defines the Data Queue and work order releasing library interface to 
// Solarsoft. 
#include <libCMS/CMSBOMRTE.h>
#include "BaalV2.h"

/***********************************************************************
 *
 * Borrowed from WINE sources!! (http://www.winehq.com)
 * Converts a Win32 FILETIME structure to a UNIX time_t value
 */

/***********************************************************************
 *           DOSFS_FileTimeToUnixTime
 *
 * Convert a FILETIME format to Unix time.
 * If not NULL, 'remainder' contains the fractional part of the filetime,
 * in the range of [0..9999999] (even if time_t is negative).
 */
time_t FileTimeToUnixTime( const FILETIME *filetime, DWORD *remainder )
{
    /* Read the comment in the function DOSFS_UnixTimeToFileTime. */
#if USE_LONG_LONG
    long long int t = filetime->dwHighDateTime;
    t <<= 32;
    t += (UINT32)filetime->dwLowDateTime;
    t -= 116444736000000000LL;
    if (t < 0)
    {
	if (remainder) *remainder = 9999999 - (-t - 1) % 10000000;
	return -1 - ((-t - 1) / 10000000);
    }
    else
    {
	if (remainder) *remainder = t % 10000000;
	return t / 10000000;
    }

#else  /* ISO version */

    UINT32 a0;			/* 16 bit, low    bits */
    UINT32 a1;			/* 16 bit, medium bits */
    UINT32 a2;			/* 32 bit, high   bits */
    UINT32 r;			/* remainder of division */
    unsigned int carry;		/* carry bit for subtraction */
    int negative;		/* whether a represents a negative value */

    /* Copy the time values to a2/a1/a0 */
    a2 =  (UINT32)filetime->dwHighDateTime;
    a1 = ((UINT32)filetime->dwLowDateTime ) >> 16;
    a0 = ((UINT32)filetime->dwLowDateTime ) & 0xffff;

    /* Subtract the time difference */
    if (a0 >= 32768           ) a0 -=             32768        , carry = 0;
    else                        a0 += (1 << 16) - 32768        , carry = 1;

    if (a1 >= 54590    + carry) a1 -=             54590 + carry, carry = 0;
    else                        a1 += (1 << 16) - 54590 - carry, carry = 1;

    a2 -= 27111902 + carry;
    
    /* If a is negative, replace a by (-1-a) */
    negative = (a2 >= ((UINT32)1) << 31);
    if (negative)
    {
	/* Set a to -a - 1 (a is a2/a1/a0) */
	a0 = 0xffff - a0;
	a1 = 0xffff - a1;
	a2 = ~a2;
    }

    /* Divide a by 10000000 (a = a2/a1/a0), put the rest into r.
       Split the divisor into 10000 * 1000 which are both less than 0xffff. */
    a1 += (a2 % 10000) << 16;
    a2 /=       10000;
    a0 += (a1 % 10000) << 16;
    a1 /=       10000;
    r   =  a0 % 10000;
    a0 /=       10000;

    a1 += (a2 % 1000) << 16;
    a2 /=       1000;
    a0 += (a1 % 1000) << 16;
    a1 /=       1000;
    r  += (a0 % 1000) * 10000;
    a0 /=       1000;

    /* If a was negative, replace a by (-1-a) and r by (9999999 - r) */
    if (negative)
    {
	/* Set a to -a - 1 (a is a2/a1/a0) */
	a0 = 0xffff - a0;
	a1 = 0xffff - a1;
	a2 = ~a2;

        r  = 9999999 - r;
    }

    if (remainder) *remainder = r;

    /* Do not replace this by << 32, it gives a compiler warning and it does
       not work. */
    return ((((time_t)a2) << 16) << 16) + (a1 << 16) + a0;
#endif
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


// Note for a backer or feeder only type SD job, this will fail to match up the 
// parts correctly, but in that case all that happens is we end up with an extra 
// 10151 record, which should be safe, even though it isn't as clean.  
bool PartsMatch(csString &cmspart, char *decadepart)
{
    if (cmspart.Left(2) == "BA" && decadepart[0] == 'B')
        return true ; 
    else if (cmspart.Left(2) == "BO" && decadepart[0] == 'O')
        return true ; 
    else if (cmspart.Left(2) == "SB" && decadepart[0] == 'S')
        return true ; 
    else if (cmspart.Left(2) == "FD" && decadepart[0] == 'F')
        return true ; 
    else if (cmspart.Left(2) == "RI" && decadepart[0] == 'R')
        return true ; 
    else if (cmspart.Left(2) == "SD" && 
            (decadepart[0] == 'P' || decadepart[0] == 'G'))
    {
        return true ; 
    }
    else if (cmspart.Left(2) == "HD") 
    {
        switch(decadepart[0])
        {
            case 'G' :
                if (cmspart.FindOneOfIDX("MPB", 5) < 0)
                    return true ; 
                break ; 
            case 'M' :
                if (cmspart.FindIDX("M", 5) >= 0)
                    return true ; 
                break ; 
            case 'P' :
                if (cmspart.FindIDX("P", 5) >= 0)
                    return true ; 
                break ; 
            case 'B' :
                if (cmspart.FindIDX("B", 5) >= 0)
                    return true ; 
                break ; 
        }
    }
    return false ; // unknown part
}

int BaalFileProcessor::GetEndTimeFromSolarSoft(RunParms &rparms, 
                                               TaskRec &endtask, 
                                               time_t taskfiletime, 
                                               TaskRec &starttask)
{
    /*
        If we want to query based on the sales order number could do the following:

        SELECT Q4PART,Q4CDAT,Q4CTIM FROM
                PRODTEST.CJOBH AS A
                LEFT JOIN PRODTEST.SFTX AS B ON A.DNJOB=B.Q4JOBN 
                WHERE A.DNORD#=215849 AND B.Q4SEQ#= 10 AND B.Q4PART LIKE 'HD 18 X 9%' 
                AND B.Q4FTCD IN (10000, 10151, 40005)
                ORDER BY Q4CDAT,Q4CTIM  
     */

    TaskMapItr itm = FindTaskMatch(rparms.evp.taskMap, endtask.task, endtask.part) ;
    if (itm == rparms.evp.taskMap.end())
        return -1 ; 

    char qry[1024] ; 
    
    // But the task mapping already extracts the work order / job order number
    // so we can directly reference the records from SFTX
    _snprintf(qry, 1024,
        "SELECT Q4PART,Q4CDAT,Q4CTIM,Q4FTCD FROM"
        " %s.SFTX WHERE Q4JOBN=%s AND Q4SEQ#=%s AND Q4PART LIKE '%s%%' "
        " AND Q4FTCD IN (10001, 10151, 40005) "
        " ORDER BY Q4CDAT DESC,Q4CTIM DESC", 
            gCMSparms.dbname, 
            rparms.evp.evd.jobnum,
            rparms.evp.evd.seqnum,
            rparms.evp.evd.partnum) ; 

    
    CDateTime starttime(0,0,0,0,0,0) ; 
    starttask.sonum = 0 ; 

    int retcode = 0 ; 

    time_t t ; 
    time_t firststart = 0 ; 
    time_t laststart = 0 ; 
    time_t lastfinish = 0 ; 

    try
    {
        CSQLRecordset rs(rparms.evp.m_db) ; 
        rs << qry ; 

        rs.SQLExec();
        while (rs.SQLFetch())
        {
            int fldnum = 1 ; 
            csString part, datestr, timestr ; 
            int event ; 

            part = rs.SQLGetData(fldnum++).c_str() ; 
            part.Trim() ; 
            
            // Field 2,3 - DATE AND TIME
            csString datetime = csString(rs.SQLGetData(fldnum++).c_str()) + " " ; 
            datetime += csString(rs.SQLGetData(fldnum++).c_str()) ; 

            struct tm tmval ; 
            CSQL_ConvertTime(datetime.c_str(), tmval) ; 
            CDateTime dt ; 
            dt.SetDateTime(&tmval) ; 
            t = dt.GetTimeT() ; 

            event = atoi(rs.SQLGetData(fldnum++).c_str()) ; 

            if (!PartsMatch(part, endtask.part))
                continue ; 

            switch(event)
            {
                case 10001 :
                        // DON'T KNOW WHAT TO DO HERE YET
                    break ; 
                case 10151 :
                    if (!firststart)
                        firststart = t ; 
                    laststart = t ; 
                    break ; 
                case 40005:
                    lastfinish = t ; 
                    break ; 
            }
        }
    }
    catch (CSQLException* e)
    {
        if (fplog)
        {
            fprintf(fplog, "SQL error %d loading department codes:\n%s\n",
                        (int)e->m_nRetCode, e->m_strError.c_str()) ;
            fflush(fplog) ; 
        }
        retcode = -2 ; 
    }

    time_t endtime = 0 ; 

    if (firststart > 0)
    {   // Then we have a valid start task time for this runtime record. 
        time_t tsysnow ; 
        time(&tsysnow) ; 
        endtime = firststart + endtask.secs ;
        endtask.tasktime = endtime ; 
        if (endtask.tasktime > tsysnow)
            endtask.tasktime = tsysnow ; // can't have a time in the future
        CDateTime dt(endtime) ; 
        endtask.hour  = dt.m_nHours ; 
        endtask.mins  = dt.m_nMins ;
        endtask.secs  = dt.m_nSecs; 
        endtask.day   = dt.m_nDay ; 
        endtask.month = dt.m_nMonth ; 
        endtask.year  = dt.m_nYear ; 
        // Done since we only need to track the endtask event after this.
    }
    else
    {   // Use the file time as end end time and then the start time is calculated
        // from the runtime. Here we also need to track an extra event. 

        // THIS IS AN ERROR CONDITION WHICH SOLARSOFT CANNOT CURRENTLY DEAL WITH
        // Simply set them to one second after one another
        endtask.tasktime = taskfiletime ; // 
        starttask = endtask ; // copy all pertinent task data over
        endtask.tasktime += 1 ; 
        
        CDateTime dt(endtask.tasktime) ; 
        endtask.hour  = dt.m_nHours ; 
        endtask.mins  = dt.m_nMins ;
        endtask.secs  = dt.m_nSecs; 
        endtask.day   = dt.m_nDay ; 
        endtask.month = dt.m_nMonth ; 
        endtask.year  = dt.m_nYear ; 

        dt.SetTime(starttask.tasktime) ; 
        starttask.hour  = dt.m_nHours ; 
        starttask.mins  = dt.m_nMins ;
        starttask.secs  = dt.m_nSecs; 
        starttask.day   = dt.m_nDay ; 
        starttask.month = dt.m_nMonth ; 
        starttask.year  = dt.m_nYear ; 
    }

    return retcode ; 
}


int BaalFileProcessor::GetEndTimeFromDecade(RunParms &rparms, 
                                            TaskRec &endtask, 
                                            time_t taskfiletime, 
                                            TaskRec &starttask) 
{
    char qry[1024] ;
    
    // First get the start task for this end task 
    TaskMapItr itm = FindTaskMatch(rparms.evp.taskMap, endtask.task, endtask.part) ;
    if (itm == rparms.evp.taskMap.end())
        return -1 ; 

    if ((itm->second.itmstart == rparms.evp.taskMap.end()) ||
        (stricmp(itm->second.stopTask, endtask.task)) != 0)
    {
        return -10 ; // no matching task record. 
    }

    // Shoudl now have the proper stop task record. 

    // Here we want to grab the first start time since this is arguably when the job
    // was first initiated (except for the condition where the operator entered in 
    // the wrong SO# and we tracked invalid data. 
    
    sprintf(qry, 
        "SELECT ordernumber, employeenumber, task, part, subpart, station, tasktime FROM d_task WHERE"
        " ordernumber=%d AND task='%s' AND part='%c' AND subpart='%c'"
        " ORDER BY tasktime", 
            endtask.mappedSO, 
            itm->second.task,       // want the start task here. 
            endtask.part[0], endtask.part[1]) ; 

    if (fpsql)
    {
        fprintf(fpsql, "%s\n", qry) ; 
        fflush(fpsql) ; 
    }

    int retcode = 0 ; 
    int count = 0 ; 
    bool bFound = false ; 
    CDateTime dtStart; 
    try
    {
        while (count++ < 4 && !bFound) 
        {
            CSQLRecordset rs(*pdb) ;
            rs << qry ; 
            rs.SQLExec() ;
            while (rs.SQLFetch())
            {
                // starttask.sonum     = atoi(  rs.SQLGetData(1).c_str() ) ; 
                starttask.sonum = 0 ; // only set if we need to create a
                // start task record, otherwise the only thing we really 
                // need is the actual start time. 
                starttask.empnum    = atoi(  rs.SQLGetData(2).c_str() ) ; 
                CS_strmaxcpy(starttask.task, rs.SQLGetData(3).c_str(), 2) ; 
                starttask.part[0] = rs.SQLGetData(4)[0] ;
                starttask.part[1] = rs.SQLGetData(5)[0] ;
                starttask.part[2] = 0 ; 
                CS_strmaxcpy(starttask.station, rs.SQLGetData(6).c_str(), 5) ; 
                SQL_ConvertTime(rs.SQLGetData(7).c_str(), dtStart) ; ; 
                starttask.year = dtStart.m_nYear ; 
                starttask.month = dtStart.m_nMonth ; 
                starttask.day = dtStart.m_nDay ; 
                starttask.hour = dtStart.m_nHours ; 
                starttask.mins = dtStart.m_nMins ; 
                starttask.secs = dtStart.m_nSecs ; 

                bFound = true ; 
                break ; 
            }
        }
    }
    catch (CSQLException* e)
    {
        csString str = e->m_strError.c_str() ;
        char msg[4096] ; 
        _snprintf(msg, 4096, "SQL error %d reading records to calc runtime\n MSG: %s\n", 
                                (int)e->m_nRetCode, e->m_strError.c_str()) ; 
        if (fplog)
        {
            fprintf(fplog, msg) ; 
            fflush(fplog) ; 
        }
        retcode = -1 ; 
    }

    time_t starttime = dtStart.GetTimeT() ; 
    time_t endtime = 0 ; 

    if (bFound)
    {   // Then we have a valid start task time for this runtime record. 
        endtime = starttime + endtask.secs ;
        endtask.tasktime = endtime ; 
        CDateTime dt(endtime) ; 
        endtask.hour  = dt.m_nHours ; 
        endtask.mins  = dt.m_nMins ;
        endtask.secs  = dt.m_nSecs; 
        endtask.day   = dt.m_nDay ; 
        endtask.month = dt.m_nMonth ; 
        endtask.year  = dt.m_nYear ; 
        // Done since we only need to track the endtask event after this.
    }
    else
    {   // Use the file time as end end time and then the start time is calculated
        // from the runtime. Here we also need to track an extra event. 
        endtask.tasktime = taskfiletime ; // 
        starttask = endtask ; // copy all pertinent task data over
        starttask.tasktime = endtask.tasktime - endtask.secs ; 
        
        CDateTime dt(endtime) ; 
        endtask.hour  = dt.m_nHours ; 
        endtask.mins  = dt.m_nMins ;
        endtask.secs  = dt.m_nSecs; 
        endtask.day   = dt.m_nDay ; 
        endtask.month = dt.m_nMonth ; 
        endtask.year  = dt.m_nYear ; 

        dt.SetTime(starttask.tasktime) ; 
        starttask.hour  = dt.m_nHours ; 
        starttask.mins  = dt.m_nMins ;
        starttask.secs  = dt.m_nSecs; 
        starttask.day   = dt.m_nDay ; 
        starttask.month = dt.m_nMonth ; 
        starttask.year  = dt.m_nYear ; 
    }

    return retcode ; 
}
