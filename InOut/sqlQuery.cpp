#include "stdafx.h"
#include "InOut.h"
#include "InOutDlg.h"
#include <libCMS\CMSBOMRTE.h>

int CInOutDlg::CheckSoNum(CString strSONumber)
{
	//select (*) count against this SONumber if 
	int SONumCount = atoi(strSONumber);
	if (SONumCount < 100000)
        SONumCount += 200000 ; 
	char uqry[256] ; 
	//int temp = 232695;
	 //SO[0] = 123456;
	 sprintf(uqry, "select count(*) from %s.CADUPDATE WHERE SONUM = '%d'", 
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

BOOL CInOutDlg::SalesCode(CString strSONumber)
{
	int SONumCount = atoi(strSONumber);
	char uqry[256] ; 
	if (SONumCount < 100000)
        SONumCount += 200000 ; 
	//int temp = 232695;
	 //SO[0] = 123456;
	//select DDMAJS, DDORD# FROM CMSDAT.OCRI where DDORD#='210059'
	sprintf(uqry, "select DDMAJS, DDORD# from %s.OCRI WHERE DDORD# = '%d'", 
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
            CString TEST = rs.SQLGetData(1).c_str() ; 
			TEST = TEST.Trim();
			CString TEST2 = rs.SQLGetData(2).c_str() ;
			TEST2 = TEST2.Trim();
			if(TEST.Find("RI",0)>-1||TEST.Find("MIS", 0)>-1||TEST.Find("REP",0)>-1||TEST.Find("FRT",0)>-1)
				return false;
			else
				return true;
			//if Test has string MIS, REP, RI then return false; skip check RunCadUpdate
			//else 
			//break;
        }
			
           
    }
    catch (CSQLException* e)
    {
        char msg[4096] ; 
        _snprintf(msg, 4000, "CMSBOMRTE::Check SalsesCode errorcode = %d, msg = %s\r\n", 
                        e->m_nRetCode, e->m_strError.c_str());
        msg[4000] = 0 ; 
        msg[4001] = 0 ; 
        LogError(msg) ; 
        e->Delete();

    }
	return false;
}

BOOL CInOutDlg::CadUpdateStatus(CString strSONumber)
{
	int SONumCount = atoi(strSONumber);
	char uqry[256] ; 
	if (SONumCount < 100000)
        SONumCount += 200000 ; 
	//int temp = 232695;
	 //SO[0] = 123456;
	//select DDMAJS, DDORD# FROM CMSDAT.OCRI where DDORD#='210059'
	sprintf(uqry, "select SONUM, STATUS from %s.CADUPDATE WHERE SONUM = '%d'", 
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
            CString TEST = rs.SQLGetData(1).c_str() ; 
			TEST = TEST.Trim();
			CString TEST2 = rs.SQLGetData(2).c_str() ;
			TEST2 = TEST2.Trim();
			if(TEST2.Find("F",0)>-1||TEST2.Find("f", 0)>-1)
				return false;
			else
				return true;
			//if Test has string MIS, REP, RI then return false; skip check RunCadUpdate
			//else 
			//break;
        }
			
           
    }
    catch (CSQLException* e)
    {
        char msg[4096] ; 
        _snprintf(msg, 4000, "CMSBOMRTE::Check Cadupdate Status errorcode = %d, msg = %s\r\n", 
                        e->m_nRetCode, e->m_strError.c_str());
        msg[4000] = 0 ; 
        msg[4001] = 0 ; 
        LogError(msg) ; 
        e->Delete();

    }
	return false;
}

int CInOutDlg::CheckSoNumCUpdate(CString strSONumber)
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