// msgQThread.cpp


#include "stdafx.h"
#include "InOut.h"
#include "InOutDlg.h"


// This thread should run forever so no real need to worry about
// stopping it nicely. 
UINT MessageQThread(void *pData)
{
    CInOutApp *pApp = static_cast<CInOutApp *>(AfxGetApp()) ; 
    CInOutDlg *piod = static_cast<CInOutDlg *>(pData) ; 
    piod->m_bMsgQThreadRunning = 1 ; 

    // CSingleLock synclock(piod->psyncobj);

    piod->soValidTmr = 0 ; 
    piod->empValidTmr = 0 ; 
    piod->resetTmr = 0 ; 

    int soValidTmr, empValidTmr, resetTmr, bSOResetOnEMP ;

    while (!piod->m_bStopMsgQThread)
    {
        Sleep(1000) ; // wait one second
        // Clock tick, see if there's anything we need to do. 

        if (piod->pauseTimers)
            continue ; // do nothing while the timer is paused. 


        /////////////////////////////////////////////////////
        //  SO Number Valid
        /////////////////////////////////////////////////////
        // synclock.Lock() ; 
        soValidTmr      = piod->soValidTmr ; 
        empValidTmr     = piod->empValidTmr ; 
        resetTmr        = piod->resetTmr ; 
        bSOResetOnEMP   = piod->bSOResetOnEMP ; 
        // synclock.Unlock() ; 

        if (soValidTmr > 1)
        {
            soValidTmr-- ; 
        }
        else if (soValidTmr == 1)
        {   // Fire off the event for this timer
            soValidTmr = 0 ; // leave forever. 
            // piod->PostMessage(WM_MESSAGE_RESETSONUM) ;
            // AfxMessageBox("RESETSO Message") ; 
            ::PostMessage(piod->m_hWnd, WM_MESSAGE_RESETSONUM, 0, 0) ; 
        }

        /////////////////////////////////////////////////////
        //  Employee Number Valid
        /////////////////////////////////////////////////////
        if (empValidTmr > 1)
        {
            empValidTmr-- ; 
        }
        else if (empValidTmr == 1)
        {   // Fire off the event for this timer
            empValidTmr = 0 ; // leave forever. 
            bSOResetOnEMP = 0 ; 

            // piod->PostMessage(WM_MESSAGE_RESETEMPNUM) ; 
            // AfxMessageBox("RESET Emp Message") ; 
            ::PostMessage(piod->m_hWnd, WM_MESSAGE_RESETEMPNUM, 0, 0) ; 
        }

        /////////////////////////////////////////////////////
        //  Reset Timer
        /////////////////////////////////////////////////////
        if (resetTmr > 1)
        {
            resetTmr-- ; 
        }
        else if (resetTmr == 1)
        {   // Fire off the event for this timer
            resetTmr = 0 ; // leave forever. 
            // piod->PostMessage(WM_MESSAGE_RESETALL) ; 
            // AfxMessageBox("RESET All Message") ; 
            ::PostMessage(piod->m_hWnd, WM_MESSAGE_RESETALL, 0, 0) ; 
        }

        // synclock.Lock() ; 
        piod->soValidTmr    = soValidTmr ; 
        piod->empValidTmr   = empValidTmr ; 
        piod->resetTmr      = resetTmr ;
        piod->bSOResetOnEMP = bSOResetOnEMP ;
        // synclock.Unlock() ; 
    }

    piod->m_bMsgQThreadRunning = 0 ; 
    return 0 ; 
}