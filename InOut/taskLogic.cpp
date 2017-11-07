// taskLogic.cpp 


#include "stdafx.h"
#include "InOut.h"
#include "InOutDlg.h"
#include "TaskTypeDlg.h"
#include "Configuration.h"
#include <comdef.h>
#include <sstream>
#include "Trace.h"
#include "ErrorDlg.h"

#define MAXTASKHISTORY      15

static bool IsOfficeTask(CString task)
{
    if ((task == "SI") || (task == "SH") || (task == "SR") ||  
        (task == "DI") || (task == "DD") || (task == "DR") ||  
        (task == "CI") || (task == "CO") || (task == "CR") ||  
        (task == "SX"))
        return true ; 
    return false ; 
}

static bool ShapeIsOpen(TaskRec *ptasks, int ntasks) 
{
    // If we find a SW or SH first then shape is closed,
    // If we find a SI or SR first then shape is open
    // else shape is closed
    for (int i=0 ;i < ntasks; i++)
    {   
        if (ptasks[i].task == "SH" || ptasks[i].task == "SW")
            return false ; 
        
        if (ptasks[i].task == "SI" || ptasks[i].task == "SR")
            return true ; 
    }
    return false ; 
}

static bool DesignIsOpen(TaskRec *ptasks, int ntasks) 
{
    // If we find a DW or DD first then design is closed,
    // If we find a DI or DR first then design is open
    // else design is closed
    for (int i=0 ;i < ntasks; i++)
    {   
        if (ptasks[i].task == "DD" || ptasks[i].task == "DW")
            return false ; 
        
        if (ptasks[i].task == "DI" || ptasks[i].task == "DR")
            return true ; 
    }
    return false ; 
}

static bool CAMIsOpen(TaskRec *ptasks, int ntasks) 
{    
    // If we find a CW or CO first then CAM is closed,
    // If we find a CI or CR first then CAM is open
    // else design is closed
    for (int i=0 ;i < ntasks; i++)
    {   
        if (ptasks[i].task == "CO" || ptasks[i].task == "CW")
            return false ; 
        
        if (ptasks[i].task == "CI" || ptasks[i].task == "CR")
            return true ; 
    }
    return false ; 
}

int CInOutDlg::LaunchErrorTrack(const char *errtask, const char *sostr, int emp) 
{
    // This is a logic design kludge here. Basically, the entire logic structure
    // should be changed. This is the result of this program undergoing 3 major 
    // re-writes. Too lazy to fix this properly (and can't justify the time required)
    int nLast ; 
    TaskRec lastTask[MAXTASKHISTORY+1] ;
    nLast = LoadPrevTasks(atoi(sostr), lastTask) ; 

    CErrorDlg edlg ; 
    edlg.piod = this ; 
    edlg.saved = 0 ; 
    edlg.m_strErrTask = errtask ; 
    edlg.m_strEmpNum.Format("%d", emp) ; 
    edlg.m_strSONUM = sostr ;
    edlg.pLastTasks = lastTask ; 
    edlg.nLastTasks = nLast ; 

    edlg.DoModal() ;  

    // If the user clicked save, then we want to generate an error tracking
    // task record. Thus return true 
    return edlg.saved ; 
}


//! This is not used anymore. 
CString CInOutDlg::GetTaskFromUser(const char *msg, 
                                   const char *task1, const char *desc1,
                                   const char *task2, const char *desc2,
                                   const char *task3, const char *desc3)
{
    CTaskTypeDlg dlg ; 
    
    dlg.usermsg = msg ; 
    dlg.rettask = "" ; 

    dlg.b1task = task1 ; 
    dlg.b1desc = desc1 ;

    dlg.b2task = task2 ; 
    dlg.b2desc = desc2 ;

    dlg.b3task = task3 ; 
    dlg.b3desc = desc3 ; 

    dlg.DoModal() ; 

    return dlg.rettask ; 
}



// Returns the number of tasks found
int CInOutDlg::LoadPrevTasks(int so, TaskRec lastTask[])
{

    CString soStr ; 
    char tmpstr[32] ; 

    sprintf(tmpstr, "%d", so) ; 
    soStr = tmpstr ; 

    CString oldFeedback ; 
    m_txtFeedback.GetWindowText(oldFeedback) ; 
    Feedback("WAIT...") ; 
    
    std::stringstream ss ;
    ss << "SELECT * FROM d_task WHERE ordernumber = " << Exco100kMapSONUM(soStr.GetBuffer(0)) ;
    ss << " ORDER BY tasktime DESC" ;
    
    int nLast = 0 ; 

    try
    {
        _CommandPtr pCommand;
        pCommand.CreateInstance(__uuidof(Command)) ;
        pCommand->ActiveConnection = m_pConn ;
        pCommand->CommandText = _bstr_t(ss.str().c_str()) ;
        
        _RecordsetPtr pRecordset ;
        pRecordset.CreateInstance(__uuidof(Recordset)) ;
        pRecordset->CursorLocation = adUseClient ;
        pRecordset->Open(static_cast<IDispatch *>(pCommand), vtMissing, adOpenForwardOnly,
                                    adLockBatchOptimistic, adCmdUnknown) ;

        while(!pRecordset->adoEOF && nLast < MAXTASKHISTORY)
        {
            CString task ; 
            _variant_t var;
            var = pRecordset->Fields->GetItem("task")->GetValue() ;
            task = static_cast<char *>(_bstr_t(var.bstrVal)) ;

            if (IsOfficeTask(task))
            {
                lastTask[nLast].task = task ;     

                var = pRecordset->Fields->GetItem("employeenumber")->GetValue() ;
                lastTask[nLast].emp = var.lVal ; 
                nLast++ ; 
            }

            pRecordset->MoveNext();
        } 
    }
    catch (_com_error &e)
    {
        g_Trace.Error("CInOutDlg::LoadPrevTasks", static_cast<char *>(e.Description())) ;
        Prompt("Error loading old tasks.") ; 
        return -1 ;
    }

    Feedback(oldFeedback) ; 

    return nLast ; 
}


//! Only standard processing is dealt with in this section
int CInOutDlg::StandardTaskLogic(int so,                         // so number
                                 int emp,                        // employee number
                                 TaskRec retTask[])              // output task(s)
{   
    int nLast ; 
    TaskRec lastTask[MAXTASKHISTORY+1] ;
    nLast = LoadPrevTasks(so, lastTask) ; 

    if (nLast == 0)
    {
        retTask[0].task = "SI" ;
        retTask[0].emp = emp ; 
    }
    else if (lastTask[0].task == "SI")
    {
        retTask[0].task = "SH" ; 
        retTask[0].emp = emp ; 
    }
    else if (lastTask[0].task == "SW")
    {
        retTask[0].task = "SI" ; 
        retTask[0].emp = emp ; 
    }
    else if (lastTask[0].task == "SH")
    {
        retTask[0].task = "DI" ; 
        retTask[0].emp = emp ; 
    }
    else if (lastTask[0].task == "DI")
    {
        retTask[0].task = "DD" ; 
        retTask[0].emp = emp ; 
    }
    else if (lastTask[0].task == "DW")
    {
        retTask[0].task = 
            GetTaskFromUser(
                    "The last task is a design wait.\r\n"
                    "Select task where this job is\r\n"
                    "being restarted.",
                    "SI", "Shape IN", 
                    "DI", "Design IN", 
                    "", "") ; 
        retTask[0].emp = emp ; 
    }
    else if (lastTask[0].task == "DD")
    {
        retTask[0].task = "CI" ; 
        retTask[0].emp = emp ; 
    }
    else if (lastTask[0].task == "CI")
    {
        retTask[0].task = "CO" ; 
        retTask[0].emp = emp ; 
    }
    else if (lastTask[0].task == "CW")
    {
        retTask[0].task = GetTaskFromUser(
                                "The last task is a CAM wait.\r\n"
                                "Select task where this job is\r\n"
                                "being restarted.",
                                "SI", "Shape IN", 
                                "DI", "Design IN", 
                                "CI", "CAM IN") ; 
        retTask[0].emp = emp ; 
    }
    else if (lastTask[0].task == "SX")
    {
        retTask[0].task = GetTaskFromUser(
                                "The last task is a sales return.\r\n"
                                "Select task where this job is\r\n"
                                "being restarted.",
                                "SI", "Shape IN", 
                                "DI", "Design IN", 
                                "CI", "CAM IN") ; 
        retTask[0].emp = emp ; 
    }
    else
    {
        AfxMessageBox("This job has already completed standard\nprocessing, so you have to manually select a task", MB_OK) ; 
    }

    return 0 ; 
}


int CInOutDlg::ErrorTaskLogic(CString errTask, 
                              int so,             // so number
                              int emp,            // employee number
                              TaskRec retTask[])  // output task(s)
{   
    int nLast ;
    TaskRec lastTasks[MAXTASKHISTORY+1] ;
    nLast = LoadPrevTasks(so, lastTasks) ;

    int n = 0 ; 
    retTask[n].task = errTask ; 
    retTask[n++].emp = emp ; 

    if (errTask == "SX")
    {   
        if (ShapeIsOpen(lastTasks, nLast))
        {
            retTask[n].task = "SW" ; 
            retTask[n++].emp = emp ; 
        }

        if (DesignIsOpen(lastTasks, nLast))
        {
            retTask[n].task = "DW" ; 
            retTask[n++].emp = emp ; 
        }

        if (CAMIsOpen(lastTasks, nLast))
        {
            retTask[n].task = "CW" ; 
            retTask[n++].emp = emp ; 
        }
    }
    else if (errTask == "SR")
    {
        if (ShapeIsOpen(lastTasks, nLast))
        {
            AfxMessageBox("This is currently open in Shape") ; 
        }
        
        if (DesignIsOpen(lastTasks, nLast))
        {
            retTask[n].task = "DW" ; 
            retTask[n++].emp = emp ; 
        }

        if (CAMIsOpen(lastTasks, nLast))
        {
            retTask[n].task = "CW" ; 
            retTask[n++].emp = emp ; 
        }
    }
    else if (errTask == "DR")
    {
        if (ShapeIsOpen(lastTasks, nLast))
        {   // Close shape out
            retTask[n].task = "SH" ; 
            retTask[n++].emp = emp ; 
        }

        if (DesignIsOpen(lastTasks, nLast))
        {
            AfxMessageBox("This is currently open in Design") ; 
        }

        if (CAMIsOpen(lastTasks, nLast))
        {
            retTask[n].task = "CW" ; 
            retTask[n++].emp = emp ; 
        }
    }
    else if (errTask == "CR")
    {
        if (ShapeIsOpen(lastTasks, nLast))
        {   // Close shape out
            retTask[n].task = "SH" ; 
            retTask[n++].emp = emp ; 
        }

        if (DesignIsOpen(lastTasks, nLast))
        {
            retTask[n].task = "DW" ; 
            retTask[n++].emp = emp ; 
        }

        if (CAMIsOpen(lastTasks, nLast))
        {
            AfxMessageBox("This is currently open in CAM") ; 
        }
    }
    else if (errTask == "PX")
    {   // Close out all the office operations if required
        if (ShapeIsOpen(lastTasks, nLast))
        {   // Close shape out
            retTask[n].task = "SH" ; 
            retTask[n++].emp = emp ; 
        }

        if (DesignIsOpen(lastTasks, nLast))
        {
            retTask[n].task = "DW" ; 
            retTask[n++].emp = emp ; 
        }

        if (CAMIsOpen(lastTasks, nLast))
        {
            retTask[n].task = "CO" ; 
            retTask[n++].emp = emp ; 
        }
    }
    
    return 0 ; 
}
