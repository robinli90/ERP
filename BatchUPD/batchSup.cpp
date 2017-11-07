
#include "stdafx.h"
#include "BatchUPD.h"
#include "BatchUPDDlg.h"


/*
    int ordnum ; 
    int event ; // the last event 
    int seqnum ; 
    int bHas40005 ; // true if 40005 is recorded.
    csString part ; 
    csString dept ; 
    CDateTime dt ; 
    csString jobnum ; 
    csString resource ; 
    csString opercode ; 
    CDateTime dtLastShift ; 
    int itemNumber ; 
    int empnum ; 
    int batchID ; 

    // Used for batch mode processing
    csString task ; 
    csString station ; 

 */

//  Returns the task event type
//    0x01=start 
//    0x02=stop
//    0x04=pulse (start+stop, not used yet)
int BEventRec::TaskType()
{
	//add code for ISM
    if (task == "C1" || task == "C3" || task == "C5"||task == "IS"||
		task == "IB")
        return START_TASK ; 

    if (task == "C2" || task == "C4" || task == "C6"||task == "IC"||
		task == "IF")
        return STOP_TASK ; 

    if (task == "RK"  || task == "PH" || 
        task == "HC" || task == "HD" ||
        task == "D1" || task == "D2" || task == "D3" ||
        task == "HT" ||
        task == "DS" ||
        task == "NS"
       ) 
    {
        return TASK_EVENT ; 
    }

    // The next two handle N1/N0, L1/L0, and S1/S0
    if (task[1] == '1') 
        return START_TASK ; 

    if (task[1] == '0')
        return STOP_TASK ; 

    return TASK_STATUS ; 
}


int BEventRec::ManualTask(CDateTime &shiftStart, CDateTime &shiftStop)
{
	//|| 
        //(task == "IC" || task == "IS")
    if ((task == "MM") || 
        (task[0] == 'C' && task[1] >= '1' && task[1] <= '6') || 
        (task == "DU") ) 
    {
        shiftStart.m_nYear  = 0 ; 
        shiftStart.m_nMonth = 0 ; 
        shiftStart.m_nDay   = 0 ; 
        shiftStart.m_nHours = 7 ; 
        shiftStart.m_nMins  = 0 ; 
        shiftStart.m_nSecs  = 0 ; 

        shiftStop.m_nYear   = 0 ; 
        shiftStop.m_nMonth  = 0 ; 
        shiftStop.m_nDay    = 0 ; 
        shiftStop.m_nHours  = 16 ; 
        shiftStop.m_nMins   = 0 ; 
        shiftStop.m_nSecs   = 0 ; 
        
        return 1 ; 
    }

    return 0 ; 

}
