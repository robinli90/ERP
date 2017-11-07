#include "stdafx.h"

CMSBOMRTE cmsdata;
int CCADupdateDlg::CheckSoNum(CString strSONumber)
{
	//select (*) count against this SONumber if 
	int SONumCount = atoi(strSONumber);
	if (SONumCount < 100000)
        SONumCount += 200000 ; 
	char uqry[256] ; 
	//int temp = 232695;
	 //SO[0] = 123456;
	 sprintf(uqry, "select count(*) from %s.CUPDATE WHERE SONUM = '%d'", 
					 gCMSparms.dbname, SONumCount) ; 
	int retry = 0 ; 
	
    
    try
    {
        CSQLRecordset rs(gCMSparms.pevp->m_db);
        rs << uqry ; 
        rs.SQLExec();
		//bool test = rs.SQLFetch();
        while (rs.SQLFetch())
        {
            SONumCount = atoi(rs.SQLGetData(1).c_str()) ; 
			//break;
        }
			
           
    }
    catch (CSQLException* e)
    {
        char msg[4096] ; 
        _snprintf(msg, 4000, "CMSBOMRTE::Check SO Number = %d, msg = %s\r\n", 
                        e->m_nRetCode, e->m_strError.c_str());
        msg[4000] = 0 ; 
        msg[4001] = 0 ; 
        LogError(msg) ; 
        e->Delete();

    }
	return SONumCount;

}

int CCADupdateDlg::UpdateRecord (CString sonum)
{
	
	/*SYSTEMTIME st;
    GetSystemTime(&st);
	char timestring[128] ; 
    sprintf(timestring, "%4d-%02d-%02d %02d:%02d:%02d", 
                st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);*/
	int SONumCount = atoi(sonum);
	if (SONumCount < 100000)
        SONumCount += 200000 ; 
	char datestr[64] ;
	csString time;
    CDateTime dtime ; 
    dtime.SetNow() ; 
    dtime.FormatDateTimeSecs(datestr, 0) ;

	time = datestr;
	char uqry[512] ; 
    try
    {
		//INSERT INTO %s.CADUPDATE (SONUM, STATUS, TASKTIME) values ('%d', '%c', '%s')
        sprintf(uqry, "INSERT INTO %s.CUPDATE (SONUM, TASKTIME) values ('%d', '%s')", 
                    gCMSparms.dbname, SONumCount , datestr);

        CSQLRecordset rsu(gCMSparms.pevp->m_db) ;
        rsu << uqry ; 
        rsu.SQLExec();
    }
    catch (CSQLException* e)
    {
        char msg[4096] ; 
        _snprintf(msg, 4000, "CMSBOMRTE::InitSteelTypes errorcode = %d, msg = %s\r\n", 
                        e->m_nRetCode, e->m_strError.c_str());
        msg[4000] = 0 ; 
        msg[4001] = 0 ; 
        LogError(msg) ; 
        e->Delete();

        //gParms.evp.m_db.Reconnect() ; 

    }
	return 0;
}


int CCADupdateDlg::CheckSoNumDec(CString strSONumber, CString prtcode)
{
	//select (*) count against this SONumber if 
	int SONumCount = atoi(strSONumber);
	if (SONumCount < 100000)
        SONumCount += 200000 ; 
	char uqry[256] ; 
	//int temp = 232695;
	 //SO[0] = 123456;
	 sprintf(uqry, "select count(*) from  SteelTypeStamp WHERE SONUM = '%d' AND prtcode = '%s'", 
			 SONumCount, prtcode) ; 
	int retry = 0 ; 
	
    
    try
    {
        CSQLRecordset rs(m_sql);
        rs << uqry ; 
        rs.SQLExec();
		//bool test = rs.SQLFetch();
        while (rs.SQLFetch())
        {
            SONumCount = atoi(rs.SQLGetData(1).c_str()) ; 
			//break;
        }
			
           
    }
    catch (CSQLException* e)
    {
        char msg[4096] ; 
        _snprintf(msg, 4000, "CMSBOMRTE::Check SO Number = %d, msg = %s\r\n", 
                        e->m_nRetCode, e->m_strError.c_str());
        msg[4000] = 0 ; 
        msg[4001] = 0 ; 
        LogError(msg) ; 
        e->Delete();

    }
	return SONumCount;

}

int CCADupdateDlg::InsertRecordDec (CString sonum, CString prtcode, CString steel)
{
	
	/*SYSTEMTIME st;
    GetSystemTime(&st);
	char timestring[128] ; 
    sprintf(timestring, "%4d-%02d-%02d %02d:%02d:%02d", 
                st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);*/
	int SONumCount = atoi(sonum);
	if (SONumCount < 100000)
        SONumCount += 200000 ; 
	/*char datestr[64] ;
	csString time;
    CDateTime dtime ; 
    dtime.SetNow() ; 
    dtime.FormatDateTimeSecs(datestr, 0) ;

	time = datestr;*/
	char uqry[512] ; 
    try
    {
		
		//INSERT INTO %s.CADUPDATE (SONUM, STATUS, TASKTIME) values ('%d', '%c', '%s')
        sprintf(uqry, "INSERT INTO SteelTypeStamp (SONUM, PRTCODE,STEELTYPE) values ('%d', '%s','%s')", 
                SONumCount , prtcode, steel);

        CSQLRecordset rsu(m_sql) ;
        rsu << uqry ; 
        rsu.SQLExec();
    }
    catch (CSQLException* e)
    {
        char msg[4096] ; 
        _snprintf(msg, 4000, "CMSBOMRTE::InitSteelTypes errorcode = %d, msg = %s\r\n", 
                        e->m_nRetCode, e->m_strError.c_str());
        msg[4000] = 0 ; 
        msg[4001] = 0 ; 
        LogError(msg) ; 
        e->Delete();

        //gParms.evp.m_db.Reconnect() ; 

    }
	return 0;
}

int CCADupdateDlg::UpdateRecordDec (CString sonum, CString prtcode, CString steel)
{
	
	/*SYSTEMTIME st;
    GetSystemTime(&st);
	char timestring[128] ; 
    sprintf(timestring, "%4d-%02d-%02d %02d:%02d:%02d", 
                st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);*/
	int SONumCount = atoi(sonum);
	if (SONumCount < 100000)
        SONumCount += 200000 ; 
	/*char datestr[64] ;
	csString time;
    CDateTime dtime ; 
    dtime.SetNow() ; 
    dtime.FormatDateTimeSecs(datestr, 0) ;

	time = datestr;*/
	char uqry[512] ; 
    try
    {
		//UPDATE %s.CADUPDATE SET STATUS='%c', TASKTIME='%s' WHERE " "SONUM='%d'"
        sprintf(uqry, "UPDATE SteelTypeStamp SET STEELTYPE = '%s' WHERE SONUM = '%d' and prtcode = '%s'", 
                steel, SONumCount , prtcode);

        CSQLRecordset rsu(m_sql) ;
        rsu << uqry ; 
        rsu.SQLExec();
    }
    catch (CSQLException* e)
    {
        char msg[4096] ; 
        _snprintf(msg, 4000, "CMSBOMRTE::InitSteelTypes errorcode = %d, msg = %s\r\n", 
                        e->m_nRetCode, e->m_strError.c_str());
        msg[4000] = 0 ; 
        msg[4001] = 0 ; 
        LogError(msg) ; 
        e->Delete();

        //gParms.evp.m_db.Reconnect() ; 
		
    }
	return 0;
}

CString CCADupdateDlg::SteelType (int steel)
{
	CString steelNumber = "";
	if(steel==1)
	{
		steelNumber = "H-13";
	}
	else if(steel==2)
	{
		steelNumber = "2714";
	}
	else if(steel==3)
	{
		steelNumber = "EK38";
	}
	else if(steel==4)
	{
		steelNumber = "HTVR";
	}
	else if(steel==5)
	{
		steelNumber = "M2";
	}
	else if(steel==6)
	{
		steelNumber = "DIVAR";
	}
	else
	{
		steelNumber = "H-13";
	}
	
	
	return steelNumber;
}