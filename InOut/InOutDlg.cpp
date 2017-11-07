// InOutDlg.cpp
//
//
//

#include "stdafx.h"
#include "InOut.h"
#include "InOutDlg.h"
#include "Configuration.h"
#include <comdef.h>
#include <sstream>
#include "Trace.h"

//#include "cmsConnectParms.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


UINT MessageQThread(void *pData) ;
// Constructor
CInOutDlg::CInOutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInOutDlg::IDD, pParent),
	m_bBypassDB(false)
{
    // psyncobj = 0 ; 
    m_bStopMsgQThread = 0; 
    m_bMsgQThreadRunning = 0 ;

    b1Desc = "Shape Out" ; 
    b1Task = "SH" ;

    b2Desc = "Design In" ; 
    b2Task = "DI" ;

    b3Desc = "Design Ret" ; 
    b3Task = "DR" ;

    b4Desc = "" ; 
    b4Task = "" ;

    nsonums = 0 ;

    pauseTimers = 0 ;
    resetTmr = 0 ; 
    soValidTmr = 0 ; 
    empValidTmr = 0 ; 

   
    m_lastCtrl = 0 ; 

    //{{AFX_DATA_INIT(CInOutDlg)
	//}}AFX_DATA_INIT

    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

// DoDataExchange()
//
void CInOutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CInOutDlg)
    DDX_Control(pDX, IDC_SX_BUTTON, m_bSX);
    DDX_Control(pDX, IDC_SR_BUTTON, m_bSR);
    DDX_Control(pDX, IDC_SI_BUTTON, m_bSI);
    DDX_Control(pDX, IDC_SH_BUTTON, m_bSH);
    DDX_Control(pDX, IDC_DR_BUTTON, m_bDR);
    DDX_Control(pDX, IDC_DI_BUTTON, m_bDI);
    DDX_Control(pDX, IDC_CR_BUTTON, m_bCR);
    DDX_Control(pDX, IDC_DD_BUTTON, m_bDD);
    DDX_Control(pDX, IDC_CO_BUTTON, m_bCO);
    DDX_Control(pDX, IDC_CI_BUTTON, m_bCI);
    DDX_Control(pDX, IDC_PROMPT, m_txtPrompt);
    DDX_Control(pDX, IDC_FEEDBACK, m_txtFeedback);
    DDX_Control(pDX, IDC_SO_LABEL, m_lblSO);
    DDX_Control(pDX, IDC_EMP_LABEL, m_lblEmp);
    DDX_Control(pDX, IDC_SONUMBER, m_txtSONumber);
    DDX_Control(pDX, IDC_EMPLOYEENUMBER, m_txtEmployeeNumber);
    DDX_Control(pDX, IDC_MSCOMM1, m_Comm1);
    DDX_Control(pDX, IDC_MSCOMM2, m_Comm2);
    //}}AFX_DATA_MAP
}

// Message Map
//
BEGIN_MESSAGE_MAP(CInOutDlg, CDialog)
    //{{AFX_MSG_MAP(CInOutDlg)
    ON_WM_SYSCOMMAND()
    ON_EN_CHANGE(IDC_EMPLOYEENUMBER, OnChangeEmployeeNumber)
    ON_EN_CHANGE(IDC_SONUMBER, OnChangeSONumber)
    ON_EN_SETFOCUS(IDC_EMPLOYEENUMBER, OnSetFocusEmployeeNumber)
    ON_EN_SETFOCUS(IDC_SONUMBER, OnSetFocusSONumber)
    ON_BN_CLICKED(IDC_SX_BUTTON, OnSxButton)
    ON_BN_CLICKED(IDC_SI_BUTTON, OnSiButton)
    ON_BN_CLICKED(IDC_SR_BUTTON, OnSrButton)
    ON_BN_CLICKED(IDC_SH_BUTTON, OnShButton)
    ON_BN_CLICKED(IDC_DI_BUTTON, OnDiButton)
    ON_BN_CLICKED(IDC_DR_BUTTON, OnDrButton)
    ON_BN_CLICKED(IDC_DD_BUTTON, OnDdButton)
    ON_BN_CLICKED(IDC_CI_BUTTON, OnCiButton)
    ON_BN_CLICKED(IDC_CR_BUTTON, OnCrButton)
    ON_BN_CLICKED(IDC_CO_BUTTON, OnCoButton)
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_SA_BUTTON, OnSaButton)
    ON_BN_CLICKED(IDC_PX_BUTTON, OnPxButton)
    ON_BN_CLICKED(IDC_CUST_BUTTON, OnCustButton)
	ON_BN_CLICKED(IDC_1PCTIN_BUTTON, OnOnePercentInButton)
	ON_BN_CLICKED(IDC_1PCTOUT_BUTTON, OnOnePercentOutButton)
	ON_BN_CLICKED(IDC_SHPAUSE_BUTTON2, OnShpPauseButton)
	ON_BN_CLICKED(IDC_DIPAUSE_BUTTON, OnDesPauseButton)
	//ON_MESSAGE(WM_USER_PLAY,(LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM))OnPlay)
    ON_MESSAGE(WM_MESSAGE_RESETSONUM,  (LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM)) ResetSONumber)
    ON_MESSAGE(WM_MESSAGE_RESETEMPNUM, (LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM)) ResetEMPNumber)
    ON_MESSAGE(WM_MESSAGE_RESETALL,   (LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM))  ResetAll)
	ON_BN_CLICKED(IDC_CIPAUSE_BUTTON, OnCAMPauseButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Event Sink Map
//
BEGIN_EVENTSINK_MAP(CInOutDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CInOutDlg)
    ON_EVENT(CInOutDlg, IDC_MSCOMM1,      1 /* OnComm */, OnComm1,  VTS_NONE)
    ON_EVENT(CInOutDlg, IDC_MSCOMM2,      1 /* OnComm */, OnComm2,  VTS_NONE)
    //}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

// Returns the number of SO numbers found
// sonums must be long enough to accept all 
int ExtractSONUMs(const char *sostr, char sonums[MAXNUMSONUMS][32]) 
{
    int i ; 
    int sonumCount = 0 ; 

    char lastSONUM[16] ; 
    lastSONUM[0] = 0 ; 

    char wrkstr[64] ; 
    strncpy(wrkstr, sostr, 62) ; 

    wrkstr[63] = 0 ; 
    char *tok = strtok(wrkstr, "/ ") ; 
    while (tok != 0)
    {
        if (atoi(tok) > 9999)
        {   // Then this is a complete SO number definition.
            strcpy(sonums[sonumCount], tok) ; 
            strcpy(lastSONUM, sonums[sonumCount++]) ; 
        }
        else
        {   // We have a partial token with an extension
            if (lastSONUM[0] && strlen(tok) < MAXSONUMLEN)
            {   // Then we can build a new tok value
                char sostr[16] ; 
                int toklen = strlen(tok) ; 
                int baselen = strlen(lastSONUM) ;
                for (i=0; i < baselen - toklen; i++)
                    sostr[i] = lastSONUM[i] ; 
                for (i=0; i < toklen; i++)
                {
                    sostr[baselen - toklen + i] = tok[i] ; 
                }
                sostr[baselen] = 0 ; 

                strcpy(sonums[sonumCount], sostr) ; 
                strcpy(lastSONUM, sonums[sonumCount++]) ; 
            }
        }
        tok = strtok(0, "/ ") ; 
    }

    return sonumCount ; 
}

// Scan event from the serial port
void CInOutDlg::OnScan()
{
    // Bring application to the top of the Z Level 
    SetWindowPos(&wndTop, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE) ; 
    // fetch scanned message
    // Check to make sure the full scan string has been read
    if (m_strBuffer.Right(1) != "\n")
        return ; // ignore data for now

    CString strMessage = m_strBuffer ;
    strMessage.TrimLeft();
    strMessage.TrimRight();
    
    // empty buffers can be skipped
    if (strMessage.IsEmpty())
        return;
    
    // check message length
    int nLength = strMessage.GetLength();
    char cMode = strMessage.GetAt(0);

    // CSingleLock lock(psyncobj) ; 

    if (strMessage.GetAt(0) == 'E')
    {   
        CString strEmployeeNumber = strMessage.Mid(1);
        
        Feedback("WAIT...") ; 
        if (ValidEmployeeNumber(strEmployeeNumber))
        {
            SetEmployeeNumber(strEmployeeNumber) ;
            Feedback("Emp# OK") ; 
            if (soValidTmr <= 1)
            {
                m_txtSONumber.SetFocus() ; 
                Prompt("Waiting for SO# ...") ;
            }
            else
            {
                // TestAndProcess("") ; 
                Prompt("Click operation type...") ; 
            }
        }
        else
        {
            Feedback("BAD Emp#") ; 
            Prompt("Re-scan your employee number") ; 
            // lock.Lock() ; 
            m_txtEmployeeNumber.SetFocus() ; 
            resetTmr = EMPNUMVALIDTIMEOUT ; 
            // lock.Unlock() ; 
        }
    }
    else
    {
        CString strSONumber = strMessage ;
        nsonums = ExtractSONUMs(static_cast<LPCTSTR>(strSONumber), sonums) ; 
		SONumber = strSONumber;
        Feedback("WAIT...") ; 
        if (ValidSONumbers())
        {
            SetSONumber(strSONumber) ;
            Feedback("SO# OK") ; 
            if (empValidTmr <= 1)
            {
                m_txtEmployeeNumber.SetFocus() ; 
                Prompt("Waiting for EMP#...") ;
            }
            else
            {
                // TestAndProcess("") ; 
                Prompt("Click operation type...") ; 
            }
        }
        else
        {
            ResetSONumber() ; 
            Feedback("BAD SO#") ; 
            m_txtSONumber.SetFocus() ; 
            Prompt("Re-scan the shop order number") ; 
            // lock.Lock() ; 
            resetTmr = EMPNUMVALIDTIMEOUT ; 
            // lock.Unlock() ; 
        }
    }

    
    // empty the buffer
    m_strBuffer.Empty();
}

int CInOutDlg::TestAndProcess(CString task)
{
    resetTmr = RESETTIMERCOUNT ; // make sure we reset everything

    // CSingleLock lock(psyncobj) ; 

    CString empNumStr ; 
    m_txtEmployeeNumber.GetWindowText(empNumStr) ;

    CString soStr ; 
    m_txtSONumber.GetWindowText(soStr) ; 


	//AfxMessageBox("yes here");
    // Must test the employee number first
    if (empValidTmr <= 1)
    {   // Test if there's a valid EMP# from a manual entry
        Feedback("WAIT...") ; 
        if (ValidEmployeeNumber(empNumStr))
        {
            Feedback("EMP# OK") ; 
            m_txtSONumber.SetFocus() ; 
        }
        else
        {
            Feedback("BAD EMP#") ;
            m_txtEmployeeNumber.SetFocus() ; 
            resetTmr = RESETTIMERCOUNT ; 
            return -1 ;
        }
    }

    if (soValidTmr <= 1)
    {   // Test if there's a valid SO# from a manual entry
        Feedback("WAIT...") ; 
        nsonums = ExtractSONUMs(static_cast<LPCTSTR>(soStr), sonums) ; 
        if (ValidSONumbers())
        {
            Feedback("SO# OK") ; 
            m_txtEmployeeNumber.SetFocus() ; 
        }
        else
        {
            Feedback("BAD SO#") ; 
            // lock.Lock() ;
            resetTmr = RESETTIMERCOUNT ; 
            m_txtSONumber.SetFocus() ; 
            // lock.Unlock() ; 
            return -1 ; 
        }
    } 

	

    if (nsonums == 0)
        return 0 ; // nothing to do
    
    int nsos ; 
    int *soNumbers = new int[nsonums] ; 
    int empNumber ; 
	
	//int bolster ;

    // lock.Lock() ; 

    int retval = 0 ; 
    pauseTimers = 1 ; 

    // Store all the multi thread variables
    int sot = soValidTmr ; 
    int empt = empValidTmr ; 
    nsos = nsonums ; 
    CAMsonum = 0 ; 
    for (int i=0; i < nsos; i++)
    {
        soNumbers[i] = atoi(sonums[i]) ; 
        if (!CAMsonum)
            CAMsonum = soNumbers[i] ;
    }
    empNumber = atoi(static_cast<LPCTSTR>(empNumStr)) ; 

    // lock.Unlock() ; 




    if (task == "CQ" || task == "SX" || task == "SR" || 
        task == "DR" || task == "CR" || task == "PX")
    {
        if (!LaunchErrorTrack(static_cast<LPCTSTR>(task), soStr, empNumber))
        {
            resetTmr = RESETTIMERCOUNT ; 
            pauseTimers = 0 ;
            return -1 ; // user cancelled.
        }
    }


    Feedback("WAIT...") ; 

    // note the user could key in something at the same time and corrupt the 
    // sonums or empnum values, but if they do that, they deserve what's coming
    TaskRec taskrec[8] ; 
    if (sot > 1 && empt > 1)
    {   // Then both are valid, process the scan
        for (int i=0; i < nsos; i++)
        {
			CString tempSO =  sonums[i];

			//AfxMessageBox(tempSO);

            int n ; 
            for (n=0; n < 8; n++)
                taskrec[n].task = "" ; 

            if (task.GetLength() == 0)
            {   // This never gets called anymore since the task is always specified on entry
                // This is left here in case we want to add automatic task determination
                // type processing based on the previous tasks entered. 
                StandardTaskLogic(soNumbers[i], empNumber, taskrec) ; // Then in scan autologic mode
            }
            else if (task == "SX" || task == "SR" || task == "DR" || task == "CR" || task == "PX")
            {   // Then do the error processing logic
                ErrorTaskLogic(task, soNumbers[i], empNumber, taskrec) ; 
            }
            else
            {   // Else simply set the task. 
                taskrec[0].task = task ;
                taskrec[1].task = "" ;
            }
            
            for (n = 0 ; n < 8; n++)
            {
                if (taskrec[n].task.GetLength() > 0)
				{
						

                      if(task == "DD")
					  {
					
	   	                  CFileFind finder, finderBO, finderL;
		                  BOOL bFound,dFound;

                          CString filename, filenameL, filepath, filepath2, filepathL;

						  filepathL = _T("\\\\10.0.0.6\\shopdata\\LiftingHoles\\");

                          filename = tempSO.Right(5);
	                      filename = filename + _T(".dwg");
						  
						  filenameL = tempSO.Right(5);
	                      filenameL = filenameL + _T(".txt");
				
                          bFound = FALSE;
						  dFound = FALSE;

						  filepath = _T("\\\\10.0.0.4\\sdrive\\CADDRAWING\\");
						  filepath2 = _T("\\\\10.0.0.4\\sdrive\\CADDRAWINGBOL\\");

							   
	                           if(finder.FindFile(filepath + filename) || finderBO.FindFile(filepath2 + filename))
							   {
								   
								   if(CheckRework(sonums[i]) == 0)
								   {
								      if(finderL.FindFile(filepathL + filenameL))
									  {
								         ProcessTask(taskrec[n].task, soNumbers[i], taskrec[n].emp) ;
									  }
								      else
									  {
									     if(AfxMessageBox("Are you sure there are no Lifting holes for\n" + tempSO.Right(5), MB_YESNO) == IDYES)
										 {
										    ProcessTask(taskrec[n].task, soNumbers[i], taskrec[n].emp) ;

										 }

									  }
								   }
								   else
								   {
									   ProcessTask(taskrec[n].task, soNumbers[i], taskrec[n].emp) ;

								   }
							   }
							   else
							   {
								   AfxMessageBox("Design file not found.\n Please make sure that file has been saved properly");

							   }


					  }
					  else if (task == "CI")
					  {
	   	                  CFileFind finder, finderBO, finderL;
		                  BOOL bFound,dFound;

                          CString filename, filenameL, filepath, filepath2, filepathL;

						  filepathL = _T("\\\\10.0.0.6\\shopdata\\LiftingHoles\\");

                          filename = tempSO.Right(5);
	                      filename = filename + _T(".dwg");
						  
						  filenameL = tempSO.Right(5);
	                      filenameL = filenameL + _T(".txt");
				
                          bFound = FALSE;
						  dFound = FALSE;

						  filepath = _T("\\\\10.0.0.4\\sdrive\\CADDRAWING\\");
						  filepath2 = _T("\\\\10.0.0.4\\sdrive\\CADDRAWINGBOL\\");



							   
	                      if(finder.FindFile(filepath + filename) || finderBO.FindFile(filepath2 + filename))
						  {	   
		
				     		  ProcessTask(taskrec[n].task, soNumbers[i], taskrec[n].emp) ;
						  }
						  else
						  {
							  AfxMessageBox("Design file not found.\n Please make sure that file has been saved properly");
						  }

						  
					  }
					  else
					  {
                         ProcessTask(taskrec[n].task, soNumbers[i], taskrec[n].emp) ;
					  }
				}
                else
                    break ;
            }
        }

        char tmpso[32] ; 
        sprintf(tmpso, "%s %d",(LPCTSTR)taskrec[0].task, soNumbers[0]) ; 
        // visual feedback
        Feedback(tmpso);
        Prompt("Scan more SO#'s or, scan Emp# to restart... ", EMPNUMVALIDTIMEOUT);

        // lock.Lock() ; 
        bSOResetOnEMP = 1 ; 
        empValidTmr = EMPNUMVALIDTIMEOUT ; // allow more SO#'s to be scanned. 
        // lock.Unlock() ;
        
        ResetSONumber() ; 
        m_txtSONumber.SetFocus() ; 

        retval = 1 ; 
    }
    delete[] soNumbers ; 
    
    pauseTimers = 0 ; // allow thread processing to continue
    return retval ; 
}

int CInOutDlg::TestSO(CString task)
{
	resetTmr = RESETTIMERCOUNT ; // make sure we reset everything

    // CSingleLock lock(psyncobj) ; 

    CString empNumStr ; 
    m_txtEmployeeNumber.GetWindowText(empNumStr) ;

    CString soStr ; 
    m_txtSONumber.GetWindowText(soStr) ; 

    // Must test the employee number first
    if (empValidTmr <= 1)
    {   // Test if there's a valid EMP# from a manual entry
        Feedback("WAIT...") ; 
        if (ValidEmployeeNumber(empNumStr))
        {
            Feedback("EMP# OK") ; 
            m_txtSONumber.SetFocus() ; 
        }
        else
        {
            Feedback("BAD EMP#") ;
            m_txtEmployeeNumber.SetFocus() ; 
            resetTmr = RESETTIMERCOUNT ; 
            return -1 ;
        }
    }

    if (soValidTmr <= 1)
    {   // Test if there's a valid SO# from a manual entry
        Feedback("WAIT...") ; 
        nsonums = ExtractSONUMs(static_cast<LPCTSTR>(soStr), sonums) ; 
        if (ValidSONumbers())
        {
            Feedback("SO# OK") ; 
            m_txtEmployeeNumber.SetFocus() ; 
        }
        else
        {
            Feedback("BAD SO#") ; 
            // lock.Lock() ;
            resetTmr = RESETTIMERCOUNT ; 
            m_txtSONumber.SetFocus() ; 
            // lock.Unlock() ; 
            return -1 ; 
        }
    } 

    if (nsonums == 0)
        return 0 ; // nothing to do
    
    int nsos ; 
    int *soNumbers = new int[nsonums] ; 
    int empNumber ; 

    // lock.Lock() ; 

    int retval = 0 ; 
    pauseTimers = 1 ; 

    // Store all the multi thread variables
    int sot = soValidTmr ; 
    int empt = empValidTmr ; 
    nsos = nsonums ; 
	nSO = nsos;
    CAMsonum = 0 ; 
    for (int i=0; i < nsos; i++)
    {
        soNumbers[i] = atoi(sonums[i]) ; 
		SalesNumber[i] = soNumbers[i];
        if (!CAMsonum)
            CAMsonum = soNumbers[i] ;
    }
    empNumber = atoi(static_cast<LPCTSTR>(empNumStr)) ; 

	return 1;
}


void CInOutDlg::ProcessTask(CString task, int ordernumber, int empnum)
{
    // Make sure the task string is reasonable.
    if (task.GetLength() != 2)
        return ; 

    CString strEmployeeNumber;
    m_txtEmployeeNumber.GetWindowText(strEmployeeNumber);
    
    CString strSONumber;
    m_txtSONumber.GetWindowText(strSONumber);
    
    // write task
    char tmpso[32] ; 
    sprintf(tmpso, "%d", ordernumber) ; 

    if (!m_bBypassDB)
    {
        std::stringstream ss;
        ss << "INSERT INTO d_task (ordernumber, employeenumber, task, part, subpart, station, tasktime, flags) VALUES (";
        ss << Exco100kMapSONUM(tmpso) << ", ";
        ss << static_cast<LPCTSTR>(strEmployeeNumber) << ", ";
        ss << "'" << static_cast<LPCTSTR>(task) << "', ";
        ss << "'G', 'L', ";
        ss << "'" << static_cast<LPCTSTR>(g_Configuration.GetString("station", "DSCN")) << "', ";
        ss << "GETDATE(), ";
        ss << "0";
        ss << ")";
    
        // trace if necessary
        if (g_Configuration.GetBoolean("traceTasks", false))
            g_Trace.Trace("CInOutDlg::ProcessTask", ss.str().c_str());
    
        try
        {
            m_pConn->Execute(_bstr_t(ss.str().c_str()), NULL, adCmdText);
        }
        catch (_com_error &e)
        {
            g_Trace.Error("CInOutDlg::ProcessTask", static_cast<char *>(e.Description()));
            Prompt("Error writing task. Please scan again.");
        }

        
        // Solarsoft tracking
        int empnumber = atoi(strEmployeeNumber) ; 
        if (empnumber == 0 && empnum != 0)
            empnumber = empnum ; 
        else if (empnumber == 0)
            g_Trace.Error("CInOutDlg::Outputtask", "employee number is zero");
        
        if (ordernumber && empnumber)
            OutputTaskFile(task, ordernumber, empnumber) ; 
    }
}

int CInOutDlg::OutputTaskFile(CString &task, int ordernumber, int empnum)
{
    char maptask[8] ; // task conversion
    char stationCode[16] ; 

    if (task == "SI" || task == "P1")
    {
        strcpy(maptask, "C1") ; 
        strcpy(stationCode, (LPCTSTR)m_stationName) ; 
    }
    else if (task == "SH" || task == "SW" || task == "P0")
    {
        strcpy(maptask, "C2") ; 
        strcpy(stationCode, (LPCTSTR)m_stationName) ; 
    }
    else if (task == "DI")
    {
        strcpy(maptask, "C3") ; 
        strcpy(stationCode, (LPCTSTR)m_stationName) ; 
    }
    else if (task == "DD" || task == "DW")
    {
        strcpy(maptask, "C4") ; 
        strcpy(stationCode, (LPCTSTR)m_stationName) ; 
    }
    else if (task == "CI")
    {
        strcpy(maptask, "C5") ; 
        strcpy(stationCode, (LPCTSTR)m_CAMstationName) ; 
    }
    else if (task == "CO" || task == "CW")
    {
        strcpy(maptask, "C6") ; 
        strcpy(stationCode, (LPCTSTR)m_CAMstationName) ; 
    }
    else
    {
        return 0 ; 
    }
    
    int retcode = 0 ; 
    
    if (maptask[0]) 
    {
        CString tfilename = m_taskdir ; 
        tfilename += "\\" ; 
        tfilename += stationCode ; 
        
        time_t tt ; 
        time(&tt) ; 
        struct tm *ptm = localtime(&tt) ;
        char timestr[128] ; 
        sprintf(timestr, "%04d%02d%02d_%02d%02d%02d", 
            ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday, 
            ptm->tm_hour, ptm->tm_min, ptm->tm_sec) ; 
        
        tfilename += timestr ; 
        tfilename += ".txt" ; 
        
        FILE *fp = fopen((LPCTSTR)tfilename, "wt") ; 
        fprintf(fp, "TASK|%d|%d|%sGL|%02d/%02d/%04d %02d:%02d:%02d|%s\n",
            ordernumber, empnum, maptask, 
            ptm->tm_mon + 1, ptm->tm_mday, ptm->tm_year + 1900,
            ptm->tm_hour, ptm->tm_min, ptm->tm_sec, 
            stationCode) ; 
        fclose(fp) ; 
        
    }

    return retcode ; 
}


void CInOutDlg::Prompt(CString strFormat, ...)
{
    va_list marker;
    va_start(marker, strFormat);
    CString strFormatted;
    strFormatted.FormatV(strFormat, marker);
    
    m_txtPrompt.SetWindowText(strFormatted);
}

void CInOutDlg::Feedback(CString strFormat, ...)
{
    va_list marker;
    va_start(marker, strFormat);
    CString strFormatted;
    strFormatted.FormatV(strFormat, marker);
    
    m_txtFeedback.SetWindowText(strFormatted);
}


bool CInOutDlg::ValidEmployeeNumber(CString strEmployeeNumber)
{
    
    if (!m_bBypassDB)
    {
        
        if (!ValidEmpNum(strEmployeeNumber))
        {
            Prompt("Error validating EMP#. Please scan again.");
            return false ; 
        }

        if (bSOResetOnEMP)
            ResetSONumber(); 

        // CSingleLock lock(psyncobj) ; 
        // lock.Lock() ;
        empValidTmr = EMPNUMVALIDTIMEOUT ; 
        // lock.Unlock() ; 
    }

    return true;
}

// ValidSONumber()
//
bool CInOutDlg::ValidSONumbers()
{
    if (nsonums == 0)
        return false ; 
    
    if (!m_bBypassDB)
    {
        std::stringstream ss;
        ss << "SELECT * FROM d_order WHERE ordernumber = " << Exco100kMapSONUM(sonums[0]) ;
        for (int i=1; i < nsonums ; i++)
        {
            ss << " OR ordernumber = " << Exco100kMapSONUM(sonums[i]) ;
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

            if (pRecordset->GetRecordCount() != nsonums)
                return false ; 
        }
        catch (_com_error &e)
        {
            g_Trace.Error("CInOutDlg::ValidSONumber", static_cast<char *>(e.Description()));
            Prompt("Error validating SO#. Please scan again.", 10);
            return false;
        }

        // CSingleLock lock(psyncobj) ; 
        // lock.Lock() ;
        soValidTmr = SONUMVALIDTIMEOUT ; 
        // lock.Unlock() ; 
    }
    
    return true;
}

// SetEmployeeNumber()
//
void CInOutDlg::SetEmployeeNumber(CString strEmployeeNumber)
{
    m_txtEmployeeNumber.SetWindowText(strEmployeeNumber) ;
}

// SetSONumber()
//
void CInOutDlg::SetSONumber(CString strSONumber)
{
    m_txtSONumber.SetWindowText(strSONumber);
}

void CInOutDlg::ResetAll()
{
    // CSingleLock synclock(psyncobj);
    // synclock.Lock() ; 
    empValidTmr = 0 ; 
    nsonums = 0 ; 
    soValidTmr = 0 ; 
    // synclock.Unlock() ; 

    m_txtSONumber.SetWindowText(CString(""));
    m_txtEmployeeNumber.SetWindowText(CString("")) ; 

    Feedback(DEFAULTMESSAGESTRING) ; 
    Prompt(DEFAULTPROMPTSTRING) ; 
    m_txtEmployeeNumber.SetFocus() ; 
}

void CInOutDlg::ResetSONumber()
{
    // CSingleLock synclock(psyncobj);
    // synclock.Lock() ; 
    nsonums = 0 ; 
    soValidTmr = 0 ; 
    // synclock.Unlock() ; 

    m_txtSONumber.SetWindowText(CString(""));
}


void CInOutDlg::ResetEMPNumber()
{

    // CSingleLock synclock(psyncobj);
    // synclock.Lock() ; 
    empValidTmr = 0 ; 
    // synclock.Unlock() ; 
    
    m_txtEmployeeNumber.SetWindowText(CString(""));
    Feedback(DEFAULTMESSAGESTRING) ; 
    Prompt(DEFAULTPROMPTSTRING) ; 
}


// OnOK()
//
// Overridden - traps the Enter key 
//
void CInOutDlg::OnOK()
{
    // See where we were typing
    if (m_lastCtrl == IDC_EMPLOYEENUMBER)
    {
        CString strEmployeeNumber ;
        m_txtEmployeeNumber.GetWindowText(strEmployeeNumber) ;

        // Now check the employee number 
        Feedback("WAIT...") ; 
        if (ValidEmployeeNumber(strEmployeeNumber))
        {
            Feedback("Emp# OK") ; 
            if (soValidTmr <= 1)
            {
                Prompt("Waiting for SO# scan...") ; 
                m_txtSONumber.SetFocus() ;
            }
            else
            {
                Prompt("Emp# and SO# OK, select task type to finish ...") ; 
                m_bSX.SetFocus() ; 
            }
        }
        else
        {
            Feedback("BAD Emp#") ; 
            Prompt("Please re-enter your employee number...") ; 
            // CSingleLock lock(psyncobj) ; 
            // lock.Lock() ;
            resetTmr = RESETTIMERCOUNT ; 
            // lock.Unlock() ; 
            m_txtEmployeeNumber.SetFocus() ; 
        }
    }
    else if (m_lastCtrl == IDC_SONUMBER)
    {
        CString strSONumber ;
        m_txtSONumber.GetWindowText(strSONumber) ;
		SONumber = strSONumber;
        nsonums = ExtractSONUMs(static_cast<LPCTSTR>(strSONumber), sonums) ; 
        Feedback("WAIT...") ; 
        if (ValidSONumbers())
        {
            SetSONumber(strSONumber) ;
            Feedback("SO# OK") ; 
            if (empValidTmr <= 1)
            {
                Prompt("Waiting for EMP#...") ;
                m_txtEmployeeNumber.SetFocus() ; 
            }
            else
            {
                Prompt("Emp# and SO# OK, select task type to finish ...") ; 
                m_bSX.SetFocus() ; 
            }
        }
        else
        {
            Feedback("BAD SO#") ; 
            Prompt("Invalid SO#, re-scan ...");
            // CSingleLock lock(psyncobj) ; 
            // lock.Lock() ;
            resetTmr = RESETTIMERCOUNT ; 
            // lock.Unlock() ; 
            m_txtSONumber.SetFocus() ; 
        }
    }
}

// Overridden to reset state.
void CInOutDlg::OnCancel()
{
}

BOOL CInOutDlg::OnInitDialog()
{

    m_hTimer = SetTimer(1,1000,0) ; 
    
    CDialog::OnInitDialog();
    
    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);
    
    // create and set larger font
    m_font14pt.CreatePointFont(140, "Arial");
    m_font24pt.CreatePointFont(240, "Arial");
    m_lblEmp.SetFont(&m_font14pt);
    m_txtEmployeeNumber.SetFont(&m_font14pt);
    m_lblSO.SetFont(&m_font14pt);
    m_txtSONumber.SetFont(&m_font14pt);
    m_txtFeedback.SetFont(&m_font24pt);
    m_txtPrompt.SetFont(&m_font14pt);

    m_stationType = g_Configuration.GetString("stationtype", "STD") ;  
    m_stationName = g_Configuration.GetString("station", "DSCN") ; 
    m_CAMstationName = g_Configuration.GetString("camstation", "CM01") ; 
    m_csList1Name = g_Configuration.GetString("list1name", "Error") ; 
    m_csList2Name = g_Configuration.GetString("list2name", "Action Taken") ; 
    m_taskdir = g_Configuration.GetString("taskdir", "s:\\acct\\cmds") ; 

    // open database
    m_bBypassDB = g_Configuration.GetBoolean("bypassDB", false);
    
    if (!m_bBypassDB)
    {
        try
        {
            m_pConn.CreateInstance(__uuidof(Connection));
            m_pConn->Open(
                _bstr_t(g_Configuration.GetString("dataSourceName", "decade")),
                _bstr_t(g_Configuration.GetString("dataSourceUser", "jamie")),
                _bstr_t(g_Configuration.GetString("dataSourcePassword", "jamie")),
                adModeUnknown);
        }
        catch(_com_error &e)
        {
            g_Trace.Error("CInOutDlg::OnInitDialog", static_cast<char *>(e.Description()));
            MessageBox("Unable to connect to database.");
            PostQuitMessage(0);
            return FALSE;
        }
    }
    else
    {
        SetWindowText("InOut - DATABASE BYPASSED");
    }
    
    // open com1
    if (g_Configuration.GetBoolean("enableCOM1"))
    {
        
        // m_Comm1.SetSettings(g_Configuration.GetString("com1Settings", "9600,n,7,2"));
        m_Comm1.SetCommPort(1);
        m_Comm1.SetPortOpen(true);
    }
    
    // open com2
    if (g_Configuration.GetBoolean("enableCOM2"))
    {
        
        // m_Comm2.SetSettings(g_Configuration.GetString("com2Settings", "9600,n,7,2"));
        m_Comm2.SetCommPort(2);
        m_Comm2.SetPortOpen(true);
    }

    // Start the message queue and  state timing thread

    /*
    psyncobj = new CMutex(FALSE, NULL) ; 

    m_bStopMsgQThread = 0 ; 
    m_bMsgQThreadRunning = 0 ; 
    m_pMsgQThread = AfxBeginThread((AFX_THREADPROC) MessageQThread, this,
                                    THREAD_PRIORITY_NORMAL, 0, 0, NULL) ;

    if (! m_pMsgQThread)
    {
        AfxMessageBox("Thread start failed, reboot the computer and try again") ; 
    }
    */

    Feedback(DEFAULTMESSAGESTRING) ; 
    Prompt(DEFAULTPROMPTSTRING) ;
    m_txtEmployeeNumber.SetFocus() ;
   
    return FALSE ;
}

// OnComm1()
//
void CInOutDlg::OnComm1()
{
    // append message to buffer
    CString str, str2 ; 
    str = static_cast<char *>(_bstr_t(_variant_t(m_Comm1.GetInput())));
    for (int i=0; i < str.GetLength(); i++)
    {
        if (str[i] != 0x7f)
            str2 += CString(str[i]) ; 
    }
    m_strBuffer += str2 ;
    OnScan() ; 
}

// OnComm2()
//
void CInOutDlg::OnComm2() 
{
    // append message to buffer
    CString str, str2 ; 
    str = static_cast<char *>(_bstr_t(_variant_t(m_Comm2.GetInput())));
    for (int i=0; i < str.GetLength(); i++)
    {
        if (str[i] != 0x7f)
            str2 += CString(str[i]) ; 
    }
    m_strBuffer += str2 ;
    OnScan() ; 
}    


// OnSysCommand()
//
void CInOutDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if (nID == SC_CLOSE)
    {
        PostQuitMessage(0);

        m_bStopMsgQThread = 1 ; 
        int waitcount = 30 ; 
        BeginWaitCursor() ; 

        while (m_bMsgQThreadRunning && waitcount--)
            Sleep(250) ; 

        if (m_bMsgQThreadRunning && !waitcount)
        {
            TerminateThread(m_pMsgQThread->m_hThread, 0) ; 
            m_pMsgQThread->m_hThread = 0 ; 
        }
        EndWaitCursor() ; 

        // delete psyncobj ; 
        return;
    }


    CDialog::OnSysCommand(nID, lParam);
}

// OnChangeEmployeeNumber()
//
void CInOutDlg::OnChangeEmployeeNumber() 
{
    m_lastCtrl = IDC_EMPLOYEENUMBER ;
}

// OnChangeSONumber()
//
void CInOutDlg::OnChangeSONumber() 
{
    m_lastCtrl = IDC_SONUMBER ;
}


// OnSetFocusEmployeeNumber()
//
void CInOutDlg::OnSetFocusEmployeeNumber() 
{
    m_txtEmployeeNumber.SetSel(0, -1);
}

// OnSetFocusSONumber()
//
void CInOutDlg::OnSetFocusSONumber() 
{
    m_txtSONumber.SetSel(0, -1);
}


void CInOutDlg::OnSaButton() 
{
    if (!TestAndProcess("SA"))
        AfxMessageBox("Enter Emp# and SO# first") ; 
    ResetSONumber() ; 
}

void CInOutDlg::OnSxButton() 
{
    if (!TestAndProcess("SX"))
        AfxMessageBox("Enter Emp# and SO# first") ; 
    ResetSONumber() ; 
}

void CInOutDlg::OnOnePercentInButton() 
{
    if (!TestAndProcess("P1"))
        AfxMessageBox("Enter Emp# and SO# first") ; 
    ResetSONumber() ; 
}

void CInOutDlg::OnOnePercentOutButton() 
{
    if (!TestAndProcess("P0"))
        AfxMessageBox("Enter Emp# and SO# first") ; 
    ResetSONumber() ; 
}

void CInOutDlg::OnSiButton() 
{
    if (!TestAndProcess("SI"))
        AfxMessageBox("Enter Emp# and SO# first") ; 
    ResetSONumber() ; 
}

void CInOutDlg::OnSrButton() 
{
    if (!TestAndProcess("SR"))
        AfxMessageBox("Enter Emp# and SO# first") ; 
    ResetSONumber() ; 
}

void CInOutDlg::OnShpPauseButton() 
{
    if (!TestAndProcess("SW"))
        AfxMessageBox("Enter Emp# and SO# first") ; 
    ResetSONumber() ; 
}

void CInOutDlg::OnShButton() 
{
    if (!TestAndProcess("SH"))
        AfxMessageBox("Enter Emp# and SO# first") ; 

	
	 
    ResetSONumber() ; 
}

void CInOutDlg::OnDiButton() 
{
    if (!TestAndProcess("DI"))
        AfxMessageBox("Enter Emp# and SO# first") ; 
    ResetSONumber() ; 
}

void CInOutDlg::OnDrButton() 
{
    if (!TestAndProcess("DR"))
        AfxMessageBox("Enter Emp# and SO# first") ; 
    ResetSONumber() ; 
}

void CInOutDlg::OnDesPauseButton() 
{
    if (!TestAndProcess("DW"))
        AfxMessageBox("Enter Emp# and SO# first") ; 
    ResetSONumber() ; 
}


void CInOutDlg::OnDdButton() 
{
	if(!TestSO("DD"))
		AfxMessageBox("Enter Emp# and SO# first") ; 
	int test = SalesNumber[0];
	for(int i = 0; i<nSO; i++)
	{
		if(SalesNumber[i]>0)
		{
			SONumber.Format("%d", SalesNumber[i]);
			if(CInOutDlg::SalesCode(SONumber))
			{
				if(CInOutDlg::CheckSoNumCUpdate(SONumber)>0)
				{

				}
				else
				{
					AfxMessageBox("Didn't run CadUpdate. Please run CadUpdate first for SO#:"+SONumber) ;
					exit(0);
				}
			}
			
		}
		else
			break;
	}


    if (!TestAndProcess("DD"))
        AfxMessageBox("Enter Emp# and SO# first") ; 
    ResetSONumber() ; 
}

void CInOutDlg::OnCiButton() 
{

	if(!TestSO("CI"))
		AfxMessageBox("Enter Emp# and SO# first") ; 

	for(int i = 0; i<nSO; i++)
	{
		if(SalesNumber[i]>0)
		{
			SONumber.Format("%d", SalesNumber[i]);
			if(CInOutDlg::SalesCode(SONumber))
			{
				if(CInOutDlg::CheckSoNumCUpdate(SONumber)>0)
				{
					//if(CInOutDlg::CadUpdateStatus(SONumber))
					//{

					//}
					//else
					//{
					//	AfxMessageBox("CadUpdate was run but failed at iSeries side for SO#:"+SONumber+" Please see your IT for support") ;
					//	exit(0);
					//}
				}
				else
				{
					AfxMessageBox("Didn't run CadUpdate. Please ask CAD Dept. to run CadUpdate for SO#:"+SONumber) ;
					exit(0);
				}
			}
			
		}
		else
			break;
	}

    if (!TestAndProcess("CI"))
        AfxMessageBox("Enter Emp# and SO# first") ; 

    ResetSONumber() ; 
}

void CInOutDlg::OnCrButton() 
{
    if (!TestAndProcess("CR"))
        AfxMessageBox("Enter Emp# and SO# first") ; 
    ResetSONumber() ; 
}

void CInOutDlg::OnCAMPauseButton() 
{
    if (!TestAndProcess("CW"))
        AfxMessageBox("Enter Emp# and SO# first") ; 
    ResetSONumber() ; 
}


void CInOutDlg::OnCoButton() 
{
    if (!TestAndProcess("CO"))
    {
        AfxMessageBox("Enter Emp# and SO# first") ; 
    }
    else
    {   // Now see if there are any cam jobs posted for this SO# and 
        // if not warn the user that they didn't post any jobs related
        // to this SO#. 
        if (!CheckForNCFiles()) 
        {
            AfxMessageBox("WARNING - there were no NC files found for\n"
                "MF,MB,PF,PB,WX,BF,BB,OF,OB\n"
                "make sure you posted the needed files.") ; 
        }
    }
    
    ResetSONumber() ; 
}

int CInOutDlg::CheckForNCFiles()
{
    int retval = 0 ; 

    // note the user could key in something at the same time and corrupt the 
    // sonums or empnum values, but if they do that, they deserve what's coming
    // Only check the first so number for any jobs

    retval += TestForFile("S:\\CURJOBS\\MILL\\MF", CAMsonum) ; 
    retval += TestForFile("S:\\CURJOBS\\MILL\\MB", CAMsonum) ; 
    retval += TestForFile("S:\\CURJOBS\\MILL\\PF", CAMsonum) ; 
    retval += TestForFile("S:\\CURJOBS\\MILL\\PB", CAMsonum) ; 
    retval += TestForFile("S:\\CURJOBS\\MILL\\BF", CAMsonum) ; 
    retval += TestForFile("S:\\CURJOBS\\MILL\\BB", CAMsonum) ; 
    retval += TestForFile("S:\\CURJOBS\\MILL\\OF", CAMsonum) ; 
    retval += TestForFile("S:\\CURJOBS\\MILL\\OB", CAMsonum) ; 
    retval += TestForFile("S:\\CURJOBS\\EDM\\WX", CAMsonum) ; 

    return retval ; 
}

int CInOutDlg::TestForFile(char *prefix, int sonum)
{
    char searchstr[256] ; 
    sprintf(searchstr, "%s%d*", prefix, sonum) ; 

    CFileFind ff ; 
    ff.FindFile(searchstr) ; 
    BOOL bWorking = ff.FindFile(searchstr);
    if (bWorking)
    {   // Then found something
        return 1 ; 
    }
    // Else no match 
    return 0 ; 
}

void CInOutDlg::OnPxButton() 
{
    if (!TestAndProcess("PX"))
        AfxMessageBox("Enter Emp# and SO# first") ; 
    ResetSONumber() ; 
}

void CInOutDlg::OnCustButton() 
{
    if (!TestAndProcess("CQ"))
        AfxMessageBox("Enter Emp# and SO# first") ; 
    ResetSONumber() ; 
}


void CInOutDlg::OnTimer(UINT nIDEvent) 
{
    CInOutApp *pApp = static_cast<CInOutApp *>(AfxGetApp()) ; 
    CInOutDlg *piod = this ; 

    // CSingleLock synclock(psyncobj);

    if (!pauseTimers)
    {
        /////////////////////////////////////////////////////
        //  SO Number Valid
        /////////////////////////////////////////////////////
        if (soValidTmr > 1)
        {
            soValidTmr-- ; 
        }
        else if (soValidTmr == 1)
        {   // Fire off the event for this timer
            soValidTmr = 0 ; // leave forever. 
            // piod->PostMessage(WM_MESSAGE_RESETSONUM) ;
            // AfxMessageBox("RESETSO Message") ; 
            ResetSONumber() ; 
            // ::PostMessage(piod->m_hWnd, WM_MESSAGE_RESETSONUM, 0, 0) ; 
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
            ResetEMPNumber() ; 
            // ::PostMessage(piod->m_hWnd, WM_MESSAGE_RESETEMPNUM, 0, 0) ; 
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
            ResetAll() ; 
            // ::PostMessage(piod->m_hWnd, WM_MESSAGE_RESETALL, 0, 0) ; 
        }
    }
    CDialog::OnTimer(nIDEvent);
}

//if return 1,only has bolster; retunr 2, only has dies; retunr 3 , has both 
int CInOutDlg:: CheckBolster(char sos[][32])
{
    std::stringstream ss;
    ss << "SELECT prefix FROM d_orderitem WHERE ordernumber = " << Exco100kMapSONUM(sos[0]);
    
	int bBolster, bOther;
	CString BolStr;

     bBolster = 0;
     bOther = 0;
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
		{
			return 0;
		}
		
		while (!pRecordset->adoEOF)
		{
			BolStr = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect("prefix"));
			BolStr.TrimLeft();
			BolStr.TrimRight();
			
		   if( BolStr == "BO" ||BolStr == "NG" ||BolStr == "RI"||BolStr== "SB")
              bBolster = 1;
		   else
			  bOther = 2;

		   pRecordset->MoveNext();

		}
    }
    catch (_com_error &e)
    {
        g_Trace.Error("CInOutDlg::ValidEmployeeNumber", static_cast<char *>(e.Description()));
        return 0;
    }

    return bBolster + bOther;

	//return 1;
}


int CInOutDlg:: CheckRework(char *sos)
{
    std::stringstream ss;
    ss << "SELECT * FROM d_rework WHERE ordernumber = " << Exco100kMapSONUM(sos);
    
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
		{
			return 0;
		}
		else
		{
			return 1;
		}
		

    }
    catch (_com_error &e)
    {
        g_Trace.Error("CInOutDlg::ValidEmployeeNumber", static_cast<char *>(e.Description()));
        return 0;
    }

}


