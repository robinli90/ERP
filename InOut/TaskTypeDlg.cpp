// TaskTypeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "inout.h"
#include "TaskTypeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTaskTypeDlg dialog


CTaskTypeDlg::CTaskTypeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTaskTypeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTaskTypeDlg)
	//}}AFX_DATA_INIT
}


void CTaskTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTaskTypeDlg)
	DDX_Control(pDX, IDC_MSG_EDIT, m_msg);
	DDX_Control(pDX, IDC_TASK3_BUT, m_button3);
	DDX_Control(pDX, IDC_TASK2_BUT, m_button2);
	DDX_Control(pDX, IDC_TASK1_BUT, m_button1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTaskTypeDlg, CDialog)
	//{{AFX_MSG_MAP(CTaskTypeDlg)
	ON_BN_CLICKED(IDC_TASK1_BUT, OnTask1But)
	ON_BN_CLICKED(IDC_TASK2_BUT, OnTask2But)
	ON_BN_CLICKED(IDC_TASK3_BUT, OnTask3But)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTaskTypeDlg message handlers

void CTaskTypeDlg::OnTask1But() 
{
    rettask = b1task ; 
    SendMessage(WM_CLOSE) ; 
}

void CTaskTypeDlg::OnTask2But() 
{
    rettask = b2task ; 
    SendMessage(WM_CLOSE) ; 
}

void CTaskTypeDlg::OnTask3But() 
{
    rettask = b3task ; 
    SendMessage(WM_CLOSE) ; 
}

BOOL CTaskTypeDlg::OnInitDialog() 
{
    CDialog::OnInitDialog();

    m_font.CreatePointFont(110, "Arial");
    m_msg.SetFont(&m_font) ; 

    m_msg.SetWindowText(usermsg) ; 

    return TRUE;  // return TRUE unless you set the focus to a control
	          // EXCEPTION: OCX Property Pages should return FALSE
}
