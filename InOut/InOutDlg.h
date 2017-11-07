// InOutDlg.h
//
//
//


#include "Disable4786.h"
#include <string>
#include <queue>
#include <CSStdlibs/cslib.h>
#include <IBM/cwbdq.h>
#include <IBM/cwbcosys.h>

using namespace std ; 

#ifndef _INOUTDLG_H_
#define _INOUTDLG_H_

//{{AFX_INCLUDES()
#include "mscomm.h"
//}}AFX_INCLUDES

#define DEFAULTMESSAGESTRING    "Ready"
#define DEFAULTPROMPTSTRING     "Scan SO# or EMP# to start..."

#define RESETTIMERCOUNT         20 
#define EMPNUMVALIDTIMEOUT      20
#define SONUMVALIDTIMEOUT       20 



struct TaskRec
{
    TaskRec() : task(""), emp(0) {} ; 
    TaskRec(const char *tsk, int en) : task(tsk), emp(en) {} ;
    CString task ; 
    int     emp ; 
} ;

//void BuildDateName(char *nameouttmpname, char *basein) ; 
// CInOutDlg Class
//
//
class CInOutDlg : public CDialog
{

public:

    CString m_stationType ; 
    CString m_stationName ; 
    CString m_csList1Name ; 
    CString m_csList2Name ; 
    CString m_CAMstationName ; 
    CString m_taskdir ; 

    bool m_bBypassDB;

private:

    UINT m_hTimer ; 
    CFont m_font12pt;
    CFont m_font14pt;
    CFont m_font24pt;

    CString b1Task, b1Desc ; 
    CString b2Task, b2Desc ; 
    CString b3Task, b3Desc ; 
    CString b4Task, b4Desc ; 

    int m_lastCtrl ; 

    // input buffer
    CString m_strBuffer;

    
    // database
    
    void OnScan();
    int CheckBolster(char sos[][32]);
	int CheckRework(char *sos);

    void ProcessTask(CString task, int ordernumber, int empnum) ;
    
    // Test if data is valid and if so process it
    int TestAndProcess(CString task) ;

    int OutputTaskFile(CString &task, int ordernumber, int empnum) ;

    // Figure out which task to generate based on current data state
    // int DetermineTask(int so, int empNumber, TaskRec tskrec[]) ;

    void SetState(int nInput);
    
    void Prompt(CString strFormat, ...);
    
    void Feedback(CString strFormat, ...);
    
    bool ValidEmployeeNumber(CString strEmployeeNumber);
    
    bool ValidSONumbers();
    
    void SetEmployeeNumber(CString strEmployeeNumber);
    
    void SetSONumber(CString strSONumber);

    CString GetTaskFromUser(const char *msg, 
                            const char *task1, const char *desc1,
                            const char *task2, const char *desc2,
                            const char *task3, const char *desc3) ;

    //! Returns the number of tasks read
    int LoadPrevTasks(int so, TaskRec lastTask[]) ;
   
    int StandardTaskLogic(int so, int emp, TaskRec retTask[]) ;
    int ErrorTaskLogic(CString errtask, int so, int emp, TaskRec retTask[]) ;

    // int GSCN_TaskLogic(int so, int emp, TaskRec retTasks[]) ; // geom check
    // int DSCN_TaskLogic(int so, int emp, TaskRec retTasks[]) ; // design 
    // int CSCN_TaskLogic(int so, int emp, TaskRec retTasks[]) ; // cam 
    // int MSCN_TaskLogic(int so, int emp, TaskRec retTasks[]) ; // cam return shop
    // int SSCN_TaskLogic(int so, int emp, TaskRec retTasks[]) ; // sales return

    int LaunchErrorTrack(const char *errtask, const char *sostr, int emp) ; 
                            // TaskRec *lastTask, int nLast) ;

    int CheckForNCFiles() ; // calls TestForFile for each of the NC files
    // that are to be searched for. 

    // Prefix must include the full file path.
    int TestForFile(char *prefix, int sonum) ;
    
	int CheckSoNum (CString strSONumber);
	BOOL SalesCode (CString strSONumber);
	BOOL CadUpdateStatus(CString strSONumber);
	int CheckSoNumCUpdate(CString strSONumber);
	int TestSO(CString task);
	CString SONumber;
	int SalesNumber[128];
	int nSO;
	int SONumber2;
public:
    CInOutDlg(CWnd* pParent = NULL);

    char sonums[MAXNUMSONUMS][32] ;
    int nsonums ; 
    int CAMsonum ; // used for testing CAM jobs

    /////////////////////////////////////////////////////////////
    // These Variables must be accessed within a CritSection lock
    /////////////////////////////////////////////////////////////
    // Countdown timers
    int pauseTimers ; 
    int soValidTmr ; 
    int empValidTmr ; 
    int resetTmr ; 
    int bSOResetOnEMP ; 
    
    // CMutex *psyncobj ;

    int m_bStopMsgQThread ; 
    int m_bMsgQThreadRunning ;
    CWinThread *m_pMsgQThread ; // point to the message Q thread

    //////////////////////////////////////////////////////////////
    // End of Crit section vars
    //////////////////////////////////////////////////////////////

    void OnPrompt() ; 
    void OnFBMsg() ; 

    void ResetAll() ; 
    void ResetSONumber() ;
    void ResetEMPNumber() ;

    //{{AFX_DATA(CInOutDlg)
    enum { IDD = IDD_INOUT_DIALOG };
    CButton	m_bSX;
    CButton	m_bSR;
    CButton	m_bSI;
    CButton	m_bSH;
    CButton	m_bDR;
    CButton	m_bDI;
    CButton	m_bCR;
    CButton	m_bDD;
    CButton	m_bCO;
    CButton	m_bCI;
    CEdit	m_txtPrompt;
    CEdit	m_txtFeedback;
    CStatic	m_lblSO;
    CStatic	m_lblEmp;
    CEdit	m_txtSONumber;
    CEdit	m_txtEmployeeNumber;
    CMSComm	m_Comm1;
    CMSComm	m_Comm2;
    //}}AFX_DATA
    
    //{{AFX_VIRTUAL(CInOutDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
    //}}AFX_VIRTUAL
    
    virtual void OnOK();
    virtual void OnCancel();
    


protected:
    HICON m_hIcon;
    
    //{{AFX_MSG(CInOutDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnComm1();
    afx_msg void OnComm2();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnChangeEmployeeNumber();
    afx_msg void OnChangeSONumber();
    afx_msg void OnSetFocusEmployeeNumber();
    afx_msg void OnSetFocusSONumber();
    afx_msg void OnSxButton();
    afx_msg void OnSiButton();
    afx_msg void OnSrButton();
    afx_msg void OnShButton();
    afx_msg void OnDiButton();
    afx_msg void OnDrButton();
    afx_msg void OnDdButton();
    afx_msg void OnCiButton();
    afx_msg void OnCrButton();
    afx_msg void OnCoButton();
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnSaButton();
    afx_msg void OnPxButton();
    afx_msg void OnCustButton();
	afx_msg void OnOnePercentInButton();
	afx_msg void OnOnePercentOutButton();
	afx_msg void OnShpPauseButton();
	afx_msg void OnDesPauseButton();
	afx_msg void OnCAMPauseButton();
    DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif
