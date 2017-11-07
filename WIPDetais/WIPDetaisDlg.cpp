#include "stdafx.h"


CWIPDetaisDlg::CWIPDetaisDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWIPDetaisDlg::IDD, pParent)
    , mDate(COleDateTime::GetCurrentTime())
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWIPDetaisDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_MonthCalCtrl(pDX, IDC_MONTHCALENDAR1, mDate);
}

BEGIN_MESSAGE_MAP(CWIPDetaisDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDOK, &CWIPDetaisDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CWIPDetaisDlg message handlers

BOOL CWIPDetaisDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWIPDetaisDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWIPDetaisDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool bNeedWIP = 0;

void CWIPDetaisDlg::OnBnClickedOk()
{
	vector<ExcoDie*> v_pDie;
	vector<CString> v_csSO;
	UpdateData(TRUE);
	int iYear = mDate.GetYear();
	int iMonth = mDate.GetMonth();
	int iDay = mDate.GetDay();
	CString csDate;
	csDate.Format(L"%d-%02d-%02d", iYear, iMonth, iDay);
	// get order list
	CString csQuery;
	csQuery.Format(L"select distinct dcord# from cmsdat.ocrh left join cmsdat.oih on dcord#=dhord# where dcplnt='001' and (dhsdat is null and (dhidat>'%s' or (dhidat is null and dcstat<>'C')) or dhsdat>'%s') and dcodat<='%s' order by dcord# desc", csDate, csDate, csDate);
	ExcoODBC *pDatabase = ExcoODBC::GetInstance();
	pDatabase->Open(Solarsoft);
	CRecordset* pRecordSet = pDatabase->RunQuery(csQuery);
	while (!pRecordSet->IsEOF())
	{
		CString csValue;
		// get order number
		pRecordSet->GetFieldValue(L"DCORD#", csValue);
		v_csSO.push_back(csValue);
		pRecordSet->MoveNext();
	}
	pRecordSet->Close();
	// add new ExcoDie to vector
	for each(CString csSO in v_csSO)
	{
		v_pDie.push_back(new ExcoDie(csSO.Trim(), csDate));
	}
	// write to decade
	pDatabase->Open(Decade);
	csQuery = L"select * from dbo.sysobjects where name='wip_temp'";
	pRecordSet = pDatabase->RunQuery(csQuery);
	if (!pRecordSet->IsEOF()) 
	{
		csQuery = L"drop table wip_temp";
		pDatabase->RunQueryNoOutput(csQuery);
	}
	pRecordSet->Close();
	csQuery = L"create table wip_temp(SONUM varchar(32), CUSTID varchar(32), CUSTNAME varchar(32), DATE varchar(32), DIETOTAL decimal(18,2), WONUM varchar(32), \"DESC\" varchar(32), ITEMTOTAL decimal(18,2), STEEL decimal(18,2), ExcoSeq varchar(32), SEQCOST decimal(18,2))";
	pDatabase->RunQueryNoOutput(csQuery);
	for each(ExcoDie* pDie in v_pDie)
	{
		for each(ExcoPiece* pPiece in pDie->v_pPiece)
		{
			if (bNeedWIP == pPiece->bIsWIP)
			{
				for each(ExcoSeq* pSeq in pPiece->v_pSeq)
				{
					csQuery.Format(L"insert into wip_temp values ('%s', '%s', '%s', '%s', 0.0, '%s', '%s', 0.0, %.2f, %s, %.2f", pDie->csID, pDie->csCustID, pDie->csCustName, pDie->csOrderDate, pPiece->csID, pPiece->csDesc, pPiece->dSteelCost, pSeq->csID, pSeq->dCost);
					pDatabase->RunQueryNoOutput(csQuery);
				}
			}
		}
	}
	// clean up
	for each (ExcoDie* pDie in v_pDie)
	{
		delete pDie;
	}
}