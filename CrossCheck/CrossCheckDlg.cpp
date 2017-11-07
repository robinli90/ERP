
// CrossCheckDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CrossCheck.h"
#include "CrossCheckDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCrossCheckDlg dialog




CCrossCheckDlg::CCrossCheckDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCrossCheckDlg::IDD, pParent)
	, m_input(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCrossCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INPUT, m_input);
	DDX_Control(pDX, IDC_RESULT, m_resultCtrl);
}

BEGIN_MESSAGE_MAP(CCrossCheckDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_CHECK, &CCrossCheckDlg::OnBnClickedCheck)
END_MESSAGE_MAP()


// CCrossCheckDlg message handlers

BOOL CCrossCheckDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCrossCheckDlg::OnPaint()
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
HCURSOR CCrossCheckDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCrossCheckDlg::OnBnClickedCheck()
{
	UpdateData(TRUE);
	// open database
	CDatabase db;
	if (0==db.OpenEx(L"DSN=cms1;UID=RROSSETTI;PWD=RROSSETTI"))
	{
		AfxMessageBox(L"Failed to open database!");
		return;
	}
	// get input
	CRecordset set(&db);
	CString query;
	m_wo_vec.clear();
	if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck())
	{
		// get so
		m_so = m_input;
		// get inv
		query = L"select dhinv# from cmsdat.oih where dhord#=";
		query += m_so;
		if (0==set.Open(CRecordset::forwardOnly, query) || set.IsEOF())
		{
			m_inv = "No Invoice Number";
		} else
		{
			set.GetFieldValue(L"DHINV#", m_inv);
			set.Close();
		}
        set.Close();
		// get wo
		query = L"select dnjob, dnpart from cmsdat.cjobh where dnord#=";
		query += m_so;
		if (0 == set.Open(CRecordset::forwardOnly, query))
		{
			AfxMessageBox(L"Invalid so#!");
			return;
		} 
		else
		{
			while (!set.IsEOF())
			{
				CString wo;
				CString part;
				set.GetFieldValue(L"DNPART", part);
				set.GetFieldValue(L"DNJOB", wo);
				m_wo_vec.push_back(wo+"\t"+part);
				set.MoveNext();
			}
			set.Close();
			query = L"select dnjob, dnpart from cmsdat.hjobh where dnord#=";
			query += m_so;
			if (0==set.Open(CRecordset::forwardOnly, query))
			{
				while (!set.IsEOF())
				{
					CString wo;
					CString part;
					set.GetFieldValue(L"DNPART", part);
					set.GetFieldValue(L"DNJOB", wo);
					m_wo_vec.push_back(wo+"\t"+part);
					set.MoveNext();
				}
			}
			set.Close();
		}
	} else if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_RADIO2))->GetCheck())
	{
		// get inv
		m_inv = m_input;
		// get so
		query = L"select dhord# from cmsdat.oih where dhinv#=";
		query += m_inv;
		if (0==set.Open(CRecordset::forwardOnly, query) || set.IsEOF())
		{
			AfxMessageBox(L"Invalid inv#!");
			return;
		} else
		{
			set.GetFieldValue(L"DHORD#", m_so);
			set.Close();
		}
		// get wo
		query = L"select dnjob, dnpart from cmsdat.cjobh where dnord#=";
		query += m_so;
		if (0 == set.Open(CRecordset::forwardOnly, query))
		{
			AfxMessageBox(L"Invalid inv#!");
			return;
		} 
		else
		{
			while (!set.IsEOF())
			{
				CString wo;
				CString part;
				set.GetFieldValue(L"DNPART", part);
				set.GetFieldValue(L"DNJOB", wo);
				m_wo_vec.push_back(wo+"\t"+part);
				set.MoveNext();
			}
			set.Close();
			query = L"select dnjob, dnpart from cmsdat.hjobh where dnord#=";
			query += m_so;
			if (0==set.Open(CRecordset::forwardOnly, query))
			{
				while (!set.IsEOF())
				{
					CString wo;
					CString part;
					set.GetFieldValue(L"DNPART", part);
					set.GetFieldValue(L"DNJOB", wo);
					m_wo_vec.push_back(wo+"\t"+part);
					set.MoveNext();
				}
			}
			set.Close();
		}
	} else if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_RADIO3))->GetCheck())
	{
		// get so
		query = L"select dnord# from cmsdat.cjobh where dnjob=";
		query += m_input;
		if (0 == set.Open(CRecordset::forwardOnly, query))
		{
			AfxMessageBox(L"Invalid inv#!");
			return;
		} else if (set.IsEOF())
		{
			set.Close();
			query = L"select dnord# from cmsdat.hjobh where dnjob=";
			query += m_input;
			if (0==set.Open(CRecordset::forwardOnly, query) || set.IsEOF())
			{
				AfxMessageBox(L"Invalid inv#!");
				return;
			}
		}
		set.GetFieldValue(L"DNORD#", m_so);
		set.Close();
		// get inv
		query = L"select dhinv# from cmsdat.oih where dhord#=";
		query += m_so;
		if (0==set.Open(CRecordset::forwardOnly, query) || set.IsEOF())
		{
			m_inv = "No Invoice Number";
		} else
		{
			set.GetFieldValue(L"DHINV#", m_inv);			
		}
        set.Close();
		// get wo
		query = L"select dnjob, dnpart from cmsdat.cjobh where dnord#=";
		query += m_so;
		if (0 == set.Open(CRecordset::forwardOnly, query))
		{
			AfxMessageBox(L"Invalid inv#!");
			return;
		}
		else
		{
			while (!set.IsEOF())
			{
				CString wo;
				CString part;
				set.GetFieldValue(L"DNPART", part);
				set.GetFieldValue(L"DNJOB", wo);
				m_wo_vec.push_back(wo+"\t"+part);
				set.MoveNext();
			}
			set.Close();
			query = L"select dnjob, dnpart from cmsdat.hjobh where dnord#=";
			query += m_so;
			if (0==set.Open(CRecordset::forwardOnly, query))
			{
				while (!set.IsEOF())
				{
					CString wo;
					CString part;
					set.GetFieldValue(L"DNPART", part);
					set.GetFieldValue(L"DNJOB", wo);
					m_wo_vec.push_back(wo+"\t"+part);
					set.MoveNext();
				}
			}
			set.Close();
		}
	} else
	{
		AfxMessageBox(L"Error when categorizing input!");
		return;
	}

	// display data
	m_resultCtrl.ResetContent();
	int index = 0;
	m_resultCtrl.InsertString(index++, L"Sales Order #:");
	m_resultCtrl.InsertString(index++, m_so);
	m_resultCtrl.InsertString(index++, L"");
	m_resultCtrl.InsertString(index++, L"Invoice #:");
	m_resultCtrl.InsertString(index++, m_inv);
	m_resultCtrl.InsertString(index++, L"");
	m_resultCtrl.InsertString(index++, L"Work Order #:");
	for each (CString wo in m_wo_vec)
	{
		m_resultCtrl.InsertString(index++, wo);
	}
	UpdateData(FALSE);
}
