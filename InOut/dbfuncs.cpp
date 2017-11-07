// dbfuncs.cpp

#include "stdafx.h"
#include "InOut.h"
#include "InOutDlg.h"
#include "Configuration.h"
#include <comdef.h>
#include <sstream>
#include "Trace.h"

char sonummapstr[256] ; 

char *Exco100kMapSONUM(char *sonum)
{
    int i = atoi(sonum) ; 
    if ( i < 100000)
        i = i + 200000 ;

    sprintf(sonummapstr, "%d", i) ;
    return sonummapstr ; 
}


bool ValidEmpNum(CString csEmpNum)
{
    std::stringstream ss;
    ss << "SELECT * FROM d_user WHERE employeenumber = " << static_cast<LPCTSTR>(csEmpNum);
    
    try
    {
        _CommandPtr pCommand;
        pCommand.CreateInstance(__uuidof(Command));
        pCommand->ActiveConnection = m_pConn;
        pCommand->CommandText = _bstr_t(ss.str().c_str());
        
        _RecordsetPtr pRecordset;
        pRecordset.CreateInstance(__uuidof(Recordset));
        pRecordset->CursorLocation = adUseClient;
        pRecordset->Open(static_cast<IDispatch *>(pCommand), vtMissing, adOpenStatic, adLockBatchOptimistic, adCmdUnknown);
        
        if (pRecordset->GetRecordCount() == 0)
            return false;
    }
    catch (_com_error &e)
    {
        g_Trace.Error("CInOutDlg::ValidEmployeeNumber", static_cast<char *>(e.Description()));
        return false;
    }

    return true;
}

bool ValidSONUMs(CString csSONUM, char sos[][32], int &nsos)
{
    nsos = ExtractSONUMs((LPCTSTR)csSONUM, sos) ;

    std::stringstream ss;
    ss << "SELECT * FROM d_order WHERE ordernumber = " << Exco100kMapSONUM(sos[0]) ;
    for (int i=1; i < nsos ; i++)
    {
        ss << " OR ordernumber = " << Exco100kMapSONUM(sos[i]) ;
    }
    
    try
    {
        _CommandPtr pCommand;
        pCommand.CreateInstance(__uuidof(Command));
        pCommand->ActiveConnection = m_pConn;
        pCommand->CommandText = _bstr_t(ss.str().c_str());
        
        _RecordsetPtr pRecordset;
        pRecordset.CreateInstance(__uuidof(Recordset));
        pRecordset->CursorLocation = adUseClient;
        pRecordset->Open(static_cast<IDispatch *>(pCommand), vtMissing, adOpenStatic, adLockBatchOptimistic, adCmdUnknown);

        if (pRecordset->GetRecordCount() != nsos)
            return false ; 
    }
    catch (_com_error &e)
    {
        g_Trace.Error("CInOutDlg::ValidSONumber", static_cast<char *>(e.Description()));
        return false;
    }
    return true ; 
}