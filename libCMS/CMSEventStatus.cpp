// #include CMSEventStatus.cpp

#include <CSstdlibs/cslib.h>

#include "Log.h"
#include "CMSBOMRTE.h"

// TODO - add date and time to these queries in case we double track some data. 

int EVMAX_RETRIES = 5 ; 

int CMSEventProcessing::Get10100Status(EventData &evd, time_t &eventTime)
{
    char qry[512] ; 

    _snprintf(qry, 511, "SELECT Q4BTID,Q4FTCD,Q4CDAT,Q4CTIM FROM  %s.SFTX WHERE"
        " Q4DEPT = '%s' AND Q4RESC = '%s' AND "
        " (Q4FTCD = '10100' OR Q4FTCD = '40005' OR Q4FTCD = '10151')"
        " ORDER BY Q4CDAT DESC, Q4CTIM DESC FETCH FIRST 1 ROWS ONLY",
            m_db.dbname, evd.deptCode, evd.resCode) ; 

    int retcode = 0 ; 
    int batchID = 0 ; 
    int event = 0 ; 

    eventTime = 0 ; 

    try
    {
        CSQLRecordset rs(m_db) ;
        rs << qry ; 
        rs.SQLExec();
        while (rs.SQLFetch())
        {
            CDateTime dt ; 
            batchID = atoi(rs.SQLGetData(1).c_str()) ; 
            event   = atoi(rs.SQLGetData(2).c_str()) ; 
            CMSSQL_GetDate(dt, rs.SQLGetData(3).c_str()) ;
            CMSSQL_GetTime(dt, rs.SQLGetData(4).c_str()) ;

            eventTime = dt.GetTimeT() ; 
            break ;
        }

        if (event == 10100)
            retcode = EVENT_10100 ; 
    }
    catch (CSQLException* e)
    {
        char msg[2048] ;
        _snprintf(msg, 2048, "SQL error %d getting max SO number\r\n MSG: %.1000s\r\n",
                        (int)e->m_nRetCode, e->m_strError.c_str()) ;
        LogError(msg) ;
        retcode = 0x80000000 ; 
    }

    return retcode ; 
}


// Returns >0 if the record exists. 0 if not,  <0 if error
int CMSEventProcessing::Get10151Status(EventData &evd, time_t &eventTime)
{
    char qry[512] ; 

    _snprintf(qry, 511, "SELECT Q4BTID,Q4FTCD,Q4CDAT,Q4CTIM FROM  %s.SFTX WHERE"
        " Q4DEPT = '%s' AND Q4RESC = '%s' AND "
        " (Q4FTCD = '10151' OR Q4FTCD = '40005' OR Q4FTCD = '10100')"
        " AND Q4JOBN='%s' AND Q4SEQ#='%s'"
        " ORDER BY Q4CDAT DESC, Q4CTIM DESC FETCH FIRST 1 ROWS ONLY",
            m_db.dbname, evd.deptCode, evd.resCode, evd.jobnum, evd.seqnum) ; 

    int retcode = 0 ; 
    int batchID = 0 ; 
    int event = 0 ; 
    eventTime = 0 ; 

    try
    {
        CSQLRecordset rs(m_db) ;
        rs << qry ; 
        rs.SQLExec();
        while (rs.SQLFetch())
        {
            CDateTime dt ; 
            batchID = atoi(rs.SQLGetData(1).c_str()) ; 
            event   = atoi(rs.SQLGetData(2).c_str()) ; 
            CMSSQL_GetDate(dt, rs.SQLGetData(3).c_str()) ;
            CMSSQL_GetTime(dt, rs.SQLGetData(4).c_str()) ;

            eventTime = dt.GetTimeT() ; 
            break ;
        }

        if (event == 10151)
            retcode = EVENT_10151 ;

    }
    catch (CSQLException* e)
    {
        char msg[2048] ;
        _snprintf(msg, 2048, "SQL error %d getting max SO number\r\n MSG: %.1000s\r\n",
                        (int)e->m_nRetCode, e->m_strError.c_str()) ;
        LogError(msg) ;
        retcode = 0x80000000 ; 
    }

    return retcode ; 
}

int CMSEventProcessing::GetLast10151Status(EventData &evd, time_t &eventTime)
{
    char qry[512] ; 

    _snprintf(qry, 510, 
        "SELECT Q4BTID,Q4FTCD,Q4CDAT,Q4CTIM,Q4JOBN,Q4SEQ# FROM  %s.SFTX WHERE"
        " Q4DEPT = '%s' AND Q4RESC = '%s' AND "
        "(Q4FTCD = '10151' OR Q4FTCD = '40005' OR Q4FTCD = '10100' OR Q4FTCD like '1000%')"
        " ORDER BY Q4CDAT DESC, Q4CTIM DESC FETCH FIRST 1 ROWS ONLY",
            m_db.dbname, evd.deptCode, evd.resCode) ; 

    int retcode = 0 ; 
    int batchID = 0 ; 
    int event = 0 ; 
    eventTime = 0 ; 

    try
    {
        CSQLRecordset rs(m_db) ;
        rs << qry ; 
        rs.SQLExec();

        csString jobNumStr ; 
        csString seqNumStr ;

        while (rs.SQLFetch())
        {
            CDateTime dt ; 
            batchID = atoi(rs.SQLGetData(1).c_str()) ; 
            event   = atoi(rs.SQLGetData(2).c_str()) ; 
            CMSSQL_GetDate(dt, rs.SQLGetData(3).c_str()) ;
            CMSSQL_GetTime(dt, rs.SQLGetData(4).c_str()) ;
            jobNumStr = rs.SQLGetData(5).c_str() ;
            seqNumStr = rs.SQLGetData(6).c_str() ;

            eventTime = dt.GetTimeT() ; 
            break ;
        }

        if (event == 10151 && 
            jobNumStr == evd.jobnum &&
            seqNumStr == evd.seqnum)
        {
            retcode = EVENT_10151 ;
        }

    }
    catch (CSQLException* e)
    {
        char msg[2048] ;
        _snprintf(msg, 2048, "SQL error %d getting max SO number\r\n MSG: %.1000s\r\n",
                        (int)e->m_nRetCode, e->m_strError.c_str()) ;
        LogError(msg) ;
        retcode = 0x80000000 ; 
    }

    return retcode ; 
}


int CMSEventProcessing::TestValidSeqnum(EventData &evd)
{
    char qry[256] ; 

    _snprintf(qry, 255, "SELECT EDSEQ# FROM %s.CJOBDR WHERE"
        " EDJOB#='%s' AND EDSEQ#=%s", 
            m_db.dbname, evd.jobnum, evd.seqnum) ; 

    int retcode = 0 ; 

    try
    {
        CSQLRecordset rs(m_db) ;
        rs << qry ; 
        rs.SQLExec();
        while (rs.SQLFetch())
        {
            int fldnum = 1 ; 

            csString csseq = rs.SQLGetData(1).c_str() ; 
            csseq.Trim() ; 
            if (atoi(csseq.c_str()) == atoi(evd.seqnum))
                retcode = 1 ; 
        }
    }
    catch (CSQLException* e)
    {
        char msg[2048] ;
        _snprintf(msg, 2048, "SQL error %d getting max SO number\r\n MSG: %.1000s\r\n",
                        (int)e->m_nRetCode, e->m_strError.c_str()) ;
        LogError(msg) ;
        retcode = -1 ; 
    }

    return retcode ; 
}



// The times for 10151 events must be sequential otherwise Solarsoft will reject 
// the event. The stored time in the system is generated internally by Solarsoft, 
// but the time that is tested is taken from the time data that is passed in this 
// operation (go figure). This didn't work since the Solarsoft system ignores the 
// time, all it ends up accomplishing is to produce error messages. The time 
// on the iSeries server could be different than the computer and this seems
// to create the problem. 
int CMSEventProcessing::TestAndSet10151Time(EventData &evd)
{
    char qry[512] ; 

    _snprintf(qry, 511, "SELECT Q4CDAT, Q4CTIM FROM  %s.SFTX WHERE"
        " Q4DEPT = '%s' AND Q4RESC = '%s' AND Q4FTCD = '10151'"
        " ORDER BY Q4CDAT DESC, Q4CTIM DESC FETCH FIRST 1 ROWS ONLY", 
            m_db.dbname, evd.deptCode, evd.resCode) ; // , evd.jobnum, evd.seqnum

    int retcode = 0 ; 
    int batchID = 0 ; 

    try
    {
        CSQLRecordset rs(m_db) ;
        rs << qry ; 
        rs.SQLExec();
        while (rs.SQLFetch())
        {
            int fldnum = 1 ; 

            csString datetime = csString(rs.SQLGetData(fldnum++).c_str()) + " " ; 
            datetime += csString(rs.SQLGetData(fldnum++).c_str()) ; 

            struct tm tmval ; 
            CSQL_ConvertTime(datetime.c_str(), tmval) ; 
            CDateTime dt ; 
            dt.SetDateTime(&tmval) ; 
            time_t tlast = dt.GetTimeT() ; 

            CDateTime eventtime(evd.year, evd.month, evd.day, evd.hour, evd.mins, evd.secs) ; 
            time_t tevent = eventtime.GetTimeT() ; 

            if (tevent <= tlast)
            {   // Then we need to adjust this time to be 1 second after tlast. 
                eventtime.SetTime(tlast + 1) ; 
                evd.year  = eventtime.m_nYear ; 
                evd.month = eventtime.m_nMonth ; 
                evd.day   = eventtime.m_nDay ; 
                evd.hour  = eventtime.m_nHours ; 
                evd.mins  = eventtime.m_nMins ; 
                evd.secs  = eventtime.m_nSecs ; 
                evd.SetBaseTime(eventtime) ; 
                evd.Set10151Time(eventtime) ; 
            }
        }

        if (batchID > 0)
            retcode = 1 ; 

    }
    catch (CSQLException* e)
    {
        char msg[2048] ;
        _snprintf(msg, 2048, "SQL error %d getting max SO number\r\n MSG: %.1000s\r\n",
                        (int)e->m_nRetCode, e->m_strError.c_str()) ;
        LogError(msg) ;
        retcode = -1 ; 
    }

    return retcode ; 
}



// Returns 0x01=found 10151
//         0x02=found 20000
int CMSEventProcessing::Get20000Status(EventData &evd, time_t &eventTime)
{
    char qry[512] ; 

    _snprintf(qry, 511, "SELECT Q4BTID,Q4FTCD,Q4CDAT,Q4CTIM FROM %s.SFTX WHERE"
        " Q4DEPT = '%s' AND Q4RESC = '%s' AND (Q4FTCD = '10151' OR Q4FTCD = '20000') "
        " AND Q4JOBN='%s' AND Q4SEQ#='%s'",
            m_db.dbname, evd.deptCode, evd.resCode, evd.jobnum, evd.seqnum) ; 

    int retcode = 0 ; 
    int batchID = 0 ; 
    int event = 0 ; 

    eventTime = 0 ; 

    try
    {
        CSQLRecordset rs(m_db) ;
        rs << qry ; 
        rs.SQLExec();
        while (rs.SQLFetch())
        {
            CDateTime dt ; 
            batchID = atoi(rs.SQLGetData(1).c_str()) ; 
            event   = atoi(rs.SQLGetData(2).c_str()) ; 
            CMSSQL_GetDate(dt, rs.SQLGetData(3).c_str()) ;
            CMSSQL_GetTime(dt, rs.SQLGetData(4).c_str()) ;

            if (event == 10151)
            {
                retcode |= EVENT_10151 ; 
            }
            else if (event == 20000)
            {   // Looking for these events specifically. 
                retcode |= EVENT_20000 ; 
                eventTime = dt.GetTimeT() ; 
            }
        }
    }
    catch (CSQLException* e)
    {
        char msg[2048] ;
        _snprintf(msg, 2048, "SQL error %d getting max SO number\r\n MSG: %.1000s\r\n",
                        (int)e->m_nRetCode, e->m_strError.c_str()) ;
        LogError(msg) ;
        retcode = 0x80000000 ; 
    }

    return retcode ; 
}


int CMSEventProcessing::Get20009Status(EventData &evd, time_t &eventTime)
{
    char qry[512] ; 

    _snprintf(qry, 511, "SELECT Q4BTID,Q4FTCD,Q4CDAT,Q4CTIM FROM %s.SFTX WHERE"
        " Q4DEPT = '%s' AND Q4RESC = '%s' AND Q4FTCD = '20009'"
        " AND Q4JOBN='%s' AND Q4SEQ#='%s'",
            m_db.dbname, evd.deptCode, evd.resCode, evd.jobnum, evd.seqnum) ; 

    int retcode = 0 ; 
    int batchID = 0 ; 
    int event = 0 ; 

    eventTime = 0 ; 

    try
    {
        CSQLRecordset rs(m_db) ;
        rs << qry ; 
        rs.SQLExec();
        while (rs.SQLFetch())
        {
            CDateTime dt ; 
            batchID = atoi(rs.SQLGetData(1).c_str()) ; 
            event   = atoi(rs.SQLGetData(2).c_str()) ; 
            CMSSQL_GetDate(dt, rs.SQLGetData(3).c_str()) ;
            CMSSQL_GetTime(dt, rs.SQLGetData(4).c_str()) ;

            eventTime = dt.GetTimeT() ; 

            if (event == 20009)
                retcode |= EVENT_20009 ; 
        }
    }
    catch (CSQLException* e)
    {
        char msg[2048] ;
        _snprintf(msg, 2048, "SQL error %d getting max SO number\r\n MSG: %.1000s\r\n",
                        (int)e->m_nRetCode, e->m_strError.c_str()) ;
        LogError(msg) ;
        retcode = 0x80000000 ; 
    }

    return retcode ; 
}

int CMSEventProcessing::Get30000Status(EventData &evd, time_t &eventTime)
{
    char qry[512] ; 

    // Once a 30000 is executed against a machine with a specific serial number,
    // a record with that matching serial number can not be sent to the same 
    // machine again. Thus If the 30000 for the specific serial number is the 
    // last record, then the material is already loaded, and Solarsoft will 
    // error out if your try to do it again. 

    /* 
        This is in fact wrong sort of, the "Clear Load List" flag in the 10151 
        record, when set to 2 requires the above statement, but a 30000 has to 
        be set after the 10151 to be valid (why - who knows). Thus to make things 
        work, set the 10151 clear load list flag to '1' so that the load list 
        is cleared on each 40005, then a 30000 can be done after every single 
        10151 even if the serial number is the same because the previous 
        serial number has now been 'unloaded' (cleared)
     */
       

    //*****************************************************************************
    //       SFTX version where multiple records are read and then tied together
    //           to attach a 30000 event to the 10151 event and thus extract the 
    //           job# for verification purposes. 
    //*****************************************************************************

    _snprintf(qry, 255, "SELECT Q4BTID,Q4FTCD,Q4CDAT,Q4CTIM FROM %s.SFTX WHERE"
        " Q4DEPT = '%s' AND Q4RESC = '%s' "
        " AND ((Q4JOBN='%s' AND Q4FTCD = '10151' AND Q4SEQ#='%s') OR Q4FTCD = '30000')"
        " ORDER BY Q4CDAT DESC, Q4CTIM DESC FETCH FIRST 1 ROWS ONLY",
            m_db.dbname, evd.deptCode, evd.resCode, evd.jobnum, evd.seqnum) ; 

    int retcode = 0 ; 
    int batchID = 0 ; 
    int event = 0 ;

    eventTime = 0 ; 

    try
    {
        CSQLRecordset rs(m_db) ;
        rs << qry ; 
        rs.SQLExec();
        // Stop reading once we get the first 10151 record, the 30000 must occur 
        // after the 10151 for this to be a valid entry.  
        while (rs.SQLFetch() && !(retcode & EVENT_10151))
        {
            CDateTime dt ; 
            batchID = atoi(rs.SQLGetData(1).c_str()) ; 
            event   = atoi(rs.SQLGetData(2).c_str()) ; 
            CMSSQL_GetDate(dt, rs.SQLGetData(3).c_str()) ;
            CMSSQL_GetTime(dt, rs.SQLGetData(4).c_str()) ;

            if (event == 30000)
            {
                eventTime = dt.GetTimeT() ; 
                evd.batchID = batchID ; 
                retcode |= EVENT_30000 ; 
            }
            else if (event == 10151)
            {
                retcode |= EVENT_10151 ; 
            }
        }
    }
    catch (CSQLException* e)
    {
        char msg[2048] ;
        _snprintf(msg, 2048, "SQL error %d getting max SO number\r\n MSG: %.1000s\r\n",
                        (int)e->m_nRetCode, e->m_strError.c_str()) ;
        LogError(msg) ;
        retcode = 0x80000000 ; 
    }

    /*
        This is the version which attempts to allow only a single 30000 by serial# 
        at a time. This is for reference only, since this entire concept will not
        work due to Solarsoft logic.

    _snprintf(qry, 511, "SELECT Q4BTID,Q4FTCD,Q4CDAT,Q4CTIM,Q4SERN FROM %s.SFTX WHERE"
        " Q4DEPT = '%s' AND Q4RESC = '%s' AND Q4FTCD = '30000'"
        " ORDER BY Q4CDAT DESC, Q4CTIM DESC FETCH FIRST 1 ROWS ONLY",
            m_db.dbname, evd.deptCode, evd.resCode, evd.jobnum, evd.seqnum) ; 

    int retcode = 0 ; 
    int batchID = 0 ; 
    int event = 0 ;

    eventTime = 0 ; 

    try
    {
        CSQLRecordset rs(m_db) ;
        rs << qry ; 
        rs.SQLExec();
        // Stop reading once we get the first 10151 record, the 30000 must occur 
        // after the 10151 for this to be a valid entry.  
        while (rs.SQLFetch() && !(retcode & EVENT_10151))
        {
            CDateTime dt ; 
            batchID = atoi(rs.SQLGetData(1).c_str()) ; 
            event   = atoi(rs.SQLGetData(2).c_str()) ; 
            CMSSQL_GetDate(dt, rs.SQLGetData(3).c_str()) ;
            CMSSQL_GetTime(dt, rs.SQLGetData(4).c_str()) ;
            csString serNumStr = rs.SQLGetData(5).c_str() ;

            if (event == 30000)
            {
                if (serNumStr == evd.serialNumber)
                {   // Then the event we want exists
                    eventTime = dt.GetTimeT() ; 
                    evd.batchID = batchID ; 
                    retcode |= EVENT_30000 ; 
                }
            }
        }
    }
    catch (CSQLException* e)
    {
        char msg[2048] ;
        _snprintf(msg, 2048, "SQL error %d getting max SO number\r\n MSG: %.1000s\r\n",
                        (int)e->m_nRetCode, e->m_strError.c_str()) ;
        LogError(msg) ;
        retcode = 0x80000000 ; 
    }

    */

    /* 
        RPRM version - RPRM is not updated until 40005 occurs so this does not work. 

    _snprintf(qry, 255, "SELECT UIBTID,UIENT#,UISER#,UICDAT,UICTIM FROM %s.RPRM WHERE"
        " UIDEPT = '%s' AND UIRESC = '%s' AND UIJOB#='%s' AND UISEQ#='%s' AND UIUNMT='IN'",
            m_db.dbname, evd.deptCode, evd.resCode, evd.jobnum, evd.seqnum) ; 

    int retcode = 0 ; 
    int batchID = 0 ; 
    int entry = 0 ;
    int sernum = 0 ; 

    // time(&eventTime) ; 
    eventTime = 0 ; 

    try
    {
        CSQLRecordset rs(m_db) ;
        rs << qry ; 
        rs.SQLExec();
        while (rs.SQLFetch())
        {
            CDateTime dt ; 
            batchID = atoi(rs.SQLGetData(1).c_str()) ; 
            entry   = atoi(rs.SQLGetData(2).c_str()) ; 
            sernum  = atoi(rs.SQLGetData(3).c_str()) ; 
            CMSSQL_GetDate(dt, rs.SQLGetData(4).c_str()) ;
            CMSSQL_GetTime(dt, rs.SQLGetData(5).c_str()) ;

            eventTime = dt.GetTimeT() ; 

            if (sernum == atoi(evd.serialNumber))
                retcode |= EVENT_30000 ; 
        }
    }
    catch (CSQLException* e)
    {
        char msg[2048] ;
        _snprintf(msg, 2048, "SQL error %d getting max SO number\r\n MSG: %.1000s\r\n",
                        (int)e->m_nRetCode, e->m_strError.c_str()) ;
        LogError(msg) ;
        retcode = 0x80000000 ; 
    }

    */

    return retcode ; 
}


// TODO - update this logic to get the last of the 40005 and 10151's and if another
// 10151 is issued then also output the second 40005. This is in case there is 
// rework and the job need's to be run through the same step a second time. 
int CMSEventProcessing::Get40005Status(EventData &evd, time_t &eventTime)
{
    char qry[512] ; 

    _snprintf(qry, 511, "SELECT Q4BTID,Q4FTCD,Q4CDAT,Q4CTIM FROM  %s.SFTX WHERE"
        " Q4DEPT = '%s' AND Q4RESC = '%s' AND (Q4FTCD = '10151' OR Q4FTCD = '40005')"
        " AND Q4JOBN='%s' AND Q4SEQ#='%s'",
            m_db.dbname, evd.deptCode, evd.resCode, evd.jobnum, evd.seqnum) ; 

    int retcode = 0 ; 
    int batchID = 0 ; 
    int event ; 

    eventTime = 0 ; 

    try
    {
        CSQLRecordset rs(m_db) ;
        rs << qry ; 
        rs.SQLExec();
        while (rs.SQLFetch())
        {
            CDateTime dt ; 
            batchID = atoi(rs.SQLGetData(1).c_str()) ; 
            event   = atoi(rs.SQLGetData(2).c_str()) ; 
            CMSSQL_GetDate(dt, rs.SQLGetData(3).c_str()) ;
            CMSSQL_GetTime(dt, rs.SQLGetData(4).c_str()) ;

            if (event == 10151)
            {
                retcode |= EVENT_10151 ; 
            }
            else if (event == 40005)
            {
                retcode |= EVENT_40005 ; 
                eventTime = dt.GetTimeT() ; 
            }
        }
    }
    catch (CSQLException* e)
    {
        char msg[2048] ;
        _snprintf(msg, 2048, "SQL error %d getting max SO number\r\n MSG: %.1000s\r\n",
                        (int)e->m_nRetCode, e->m_strError.c_str()) ;
        LogError(msg) ;
        retcode = -1 ; 
    }

    return retcode ; 
}


int CMSEventProcessing::Last10151Matches(EventData &evd)
{
    char qry[512] ; 

    _snprintf(qry, 511, "SELECT Q4BTID,Q4JOBN,Q4FTCD,Q4CDAT,Q4CTIM FROM %s.SFTX WHERE"
        " Q4DEPT = '%s' AND Q4RESC = '%s' ORDER BY Q4CDAT DESC, Q4CTIM DESC"
        " FETCH FIRST 5 ROWS ONLY",
            m_db.dbname, evd.deptCode, evd.resCode) ; 

    int batchID = 0 ; 
    int event ; 
    int foundMatching10151 = 0 ; 
    
    try
    {
        CSQLRecordset rs(m_db) ;
        rs << qry ; 
        rs.SQLExec();
        while (rs.SQLFetch())
        {
            CDateTime dt ; 
            csString jobn ; 
            batchID = atoi(    rs.SQLGetData(1).c_str()) ; 
            jobn =             rs.SQLGetData(2).c_str() ; 
            event   = atoi(    rs.SQLGetData(3).c_str()) ; 
            CMSSQL_GetDate(dt, rs.SQLGetData(4).c_str()) ;
            CMSSQL_GetTime(dt, rs.SQLGetData(5).c_str()) ;
            jobn.Trim() ; 

            if (event == 10001 || event == 30000)
            {
                continue ; // keep searching
            }
            else if (event == 10151)
            {
                if (atoi(jobn.c_str()) == atoi(evd.jobnum))
                    foundMatching10151 = 1 ;
                break ; // else doesn't match
            }
            else 
            {   // Any other event means that the clock has been stopped
                // against this resource so we need to output the 10151
                // again, thus we don't have a match
                break ; // else doesn't match
            }
        }
    }
    catch (CSQLException* e)
    {
        char msg[2048] ;
        _snprintf(msg, 2048, "SQL error %d getting max SO number\r\n MSG: %.1000s\r\n",
                        (int)e->m_nRetCode, e->m_strError.c_str()) ;
        LogError(msg) ;
    }

    return foundMatching10151 ; 
}


int CMSEventProcessing::Event40005Done(EventData &evd, time_t &eventTime)
{
    char qry[512] ; 

    _snprintf(qry, 511, "SELECT Q4BTID,Q4FTCD,Q4CDAT,Q4CTIM FROM  %s.SFTX WHERE"
        " Q4FTCD = '40005' AND Q4JOBN='%s' AND Q4SEQ#='%s'"
        " FETCH FIRST 1 ROWS ONLY",
            m_db.dbname, evd.jobnum, evd.seqnum) ; 

    int batchID = 0 ; 
    int event ; 

    eventTime = 0 ; 

    int bFound40005 = 0 ; 

    try
    {
        CSQLRecordset rs(m_db) ;
        rs << qry ; 
        rs.SQLExec();
        while (rs.SQLFetch())
        {
            CDateTime dt ; 
            batchID = atoi(rs.SQLGetData(1).c_str()) ; 
            event   = atoi(rs.SQLGetData(2).c_str()) ; 
            CMSSQL_GetDate(dt, rs.SQLGetData(3).c_str()) ;
            CMSSQL_GetTime(dt, rs.SQLGetData(4).c_str()) ;

            if (event == 40005)
                bFound40005 = 1 ;
        }
    }
    catch (CSQLException* e)
    {
        char msg[2048] ;
        _snprintf(msg, 2048, "SQL error %d getting max SO number\r\n MSG: %.1000s\r\n",
                        (int)e->m_nRetCode, e->m_strError.c_str()) ;
        LogError(msg) ;
    }

    return bFound40005 ; 
}
