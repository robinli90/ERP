#pragma once
#ifndef _CCMSDATABASE_H_
#define _CCMSDATABASE_H_

#include <libSQL/SQLDatabase.h>
#include <libSQL/SQLRecordset.h>

class CCMSDatabase :
    public CSQLDatabase
{
public:

    char odbcName[256] ; 
    char userName[256] ; 
    char password[256] ; 
    char dbname[256] ; // the actual CMS LIBRARY (database) name 
    // such as EXCOPHASE1

    CCMSDatabase(void)
    {
        strcpy(odbcName, "cms1") ; 
        strcpy(userName, "cms") ; 
        strcpy(password, "smc") ; 
    }

    virtual ~CCMSDatabase(void)
    {
        Close();
    }

    bool Open(char *setdbname=0)
    {
        if (setdbname)
            strncpy(dbname, setdbname, 250) ; 
        dbname[250] = 0 ; 
        dbname[251] = 0 ; 

        try
        {   // cms1 is the ODBC name pointing to the database EXCOPHASE1 or 
            // the actual live database CMSDAT (or other, change as required). 
            OpenEx(odbcName, userName, password) ;
        }
        catch (CSQLException* e)
        {
            // LogMsg2("CCMSDatabase::Open database errorcode = %d, msg = %s", e->m_nRetCode, e->m_strError.c_str());
            e->Delete() ;
            return false ;
        }

        return true;
    }
} ;

/*

Query to select all the active order numbers. Then a secondary query has to be used with these
order numbers to grab the actual work order numbers that we are intersted in. 
SELECT distinct a.dcstat,a.dcord# FROM excophase1.ocrh AS a LEFT JOIN excophase1.cjobh AS b ON a.dcord# = b.dnord# WHERE a.dcstat <> 'C' AND b.dnord# IS NOT NULL

Query to grab the matching reocrds in the order table
SELECT a.DNJOB,a.DNPART,b.DCORD# FROM EXCOPHASE1.CJOBH AS a LEFT JOIN EXCOPHASE1.OCRH AS b ON a.DNORD#=b.DCORD# WHERE a.DNSTAT <> 'C'

Grab all the active job records including all information we are interested in for the BOM data
select dnjob,a.dnstat,dnpart,dnord#,efseq#,efqppc,c.awdes1  from excophase1.cjobh AS a LEFT JOIN excophase1.cjobdm AS b ON a.dnjob = b.efjob# LEFT JOIN excophase1.stkmp AS c ON b.efmtlp = c.awpart WHERE a.dnstat <> 'C' ORDER BY dnord# 

*/

#endif
