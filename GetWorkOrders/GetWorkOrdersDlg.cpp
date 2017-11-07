// GetWorkOrdersDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GetWorkOrders.h"
#include "GetWorkOrdersDlg.h"
#include ".\getworkordersdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

    // Dialog Data
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Implementation
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CGetWorkOrdersDlg dialog



CGetWorkOrdersDlg::CGetWorkOrdersDlg(CWnd* pParent /*=NULL*/)
: CDialog(CGetWorkOrdersDlg::IDD, pParent)
, m_strSONUM(_T(""))
, m_strMsg(_T(""))
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGetWorkOrdersDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_SONUM_EDIT, m_strSONUM);
    DDX_Text(pDX, IDC_MSG_EDIT, m_strMsg);
}

BEGIN_MESSAGE_MAP(CGetWorkOrdersDlg, CDialog)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


// CGetWorkOrdersDlg message handlers

BOOL CGetWorkOrdersDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    // TODO: Add extra initialization here

    GetDlgItem(IDC_SONUM_EDIT)->SetFocus() ; 

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGetWorkOrdersDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGetWorkOrdersDlg::OnPaint() 
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGetWorkOrdersDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}


void CGetWorkOrdersDlg::OnBnClickedButton1()
{
    UpdateData(TRUE) ; 

    BeginWaitCursor() ; 

    FILE *fplog = fopen("GetWorkOrders.log", "wt") ; 

    CFileParameters cfp ; 
    cfp.TestInitParm("ODBCNAME", "cms1") ; 
    cfp.TestInitParm("USER", "RROSSETTI") ; 
    cfp.TestInitParm("PWD",  "RROSSETTI") ; 
    cfp.TestInitParm("DBNAME", "PRODTEST") ; 
    cfp.LoadParms("GetWorkOrders") ;

    CMSBOMRTE cms ; 
    strcpy(cms.m_db.odbcName, cfp.GetString("ODBCNAME")) ; 
    strcpy(cms.m_db.userName, cfp.GetString("USER")) ; 
    strcpy(cms.m_db.password, cfp.GetString("PWD")) ; 
    cms.m_db.Open(cfp.GetString("DBNAME")) ; 

    gCMSparms.LoadConfigFile("CMScfg.ini", fplog) ; 

    cms.InitOrderList((LPCTSTR)m_strSONUM) ; 

    if (fplog)
        fclose(fplog) ; 

    cfp.SaveParms() ; 

    csString msg((LPCTSTR)m_strSONUM) ; 
    
    if (cms.activeOrders.size() == 0)
    {
        msg += "\r\n" ; 
        msg += "NO ORDER FOUND" ; 
    }
    else
    {
        CMSOrder *pord = &cms.activeOrders[0] ; 
        msg += " - " ; 
        msg += pord->custName.c_str() ; 
        msg += "\r\n" ; 

        for (int i=0; i < (int)pord->jobvec.size(); i++)
        {
            CMSJob *pj = &pord->jobvec[i] ; 
            char tmpstr[1024] ; 
            sprintf(tmpstr, "WO#=%s  PART=%s  MAT=%s\r\n", 
                    pj->jobnum.c_str(), pj->partname.c_str(), pj->mattype.c_str()) ; 
            msg += tmpstr ; 
        }
    }
    
    m_strMsg = msg.c_str() ; 

    EndWaitCursor() ; 

    m_strSONUM = "" ; 
    UpdateData(FALSE) ; 
    GetDlgItem(IDC_SONUM_EDIT)->SetFocus() ; 
}
