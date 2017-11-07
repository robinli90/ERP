
// budget_salesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "budget_sales.h"
#include "budget_salesDlg.h"
#include "afxdialogex.h"
#include <vector>
#include <afxdb.h>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cbudget_salesDlg dialog




Cbudget_salesDlg::Cbudget_salesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cbudget_salesDlg::IDD, pParent)
	, m_year(_T(""))
	, m_plant(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cbudget_salesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_YEAR, m_yearCtrl);
	DDX_Control(pDX, IDC_LIST_PLANT, m_plantCtrl);
	DDX_LBString(pDX, IDC_LIST_YEAR, m_year);
	DDX_LBString(pDX, IDC_LIST_PLANT, m_plant);
}

BEGIN_MESSAGE_MAP(Cbudget_salesDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &Cbudget_salesDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Cbudget_salesDlg message handlers

BOOL Cbudget_salesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// add year list
	m_yearCtrl.InsertString(0, L"2007");
	m_yearCtrl.InsertString(1, L"2008");
	m_yearCtrl.InsertString(2, L"2009");
	m_yearCtrl.InsertString(3, L"2010");
	m_yearCtrl.InsertString(4, L"2011");
	m_yearCtrl.InsertString(5, L"2012");
	m_yearCtrl.InsertString(6, L"2013");
	// add plant list
	m_plantCtrl.InsertString(0, L"001");
	m_plantCtrl.InsertString(1, L"002");
	m_plantCtrl.InsertString(2, L"003");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Cbudget_salesDlg::OnPaint()
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
HCURSOR Cbudget_salesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


struct Data
{
	// canada
	CString CA1;
	CString CA2;
	CString CA3;
	CString CA4;
	// canada with us dollar
	CString CU1;
	CString CU2;
	CString CU3;
	CString CU4;
	// usa
	CString US1;
	CString US2;
	CString US3;
	CString US4;
	// mexico
	CString MX1;
	CString MX2;
	CString MX3;
	CString MX4;
	// south america
	CString SA1;
	CString SA2;
	CString SA3;
	CString SA4;
	// europe
	CString EU1;
	CString EU2;
	CString EU3;
	CString EU4;
	// pacific rim
	CString PR1;
	CString PR2;
	CString PR3;
	CString PR4;
	// other (inter-division)
	CString OT1;
	CString OT2;
	CString OT3;
	CString OT4;

	Data()
	{
		CA1 = CA2 = CA3 = CA4 = L"0.0";
		CU1 = CU2 = CU3 = CU4 = L"0.0";
		US1 = US2 = US3 = US4 = L"0.0";
		MX1 = MX2 = MX3 = MX4 = L"0.0";
		SA1 = SA2 = SA3 = SA4 = L"0.0";
		EU1 = EU2 = EU3 = EU4 = L"0.0";
		PR1 = PR2 = PR3 = PR4 = L"0.0";
		OT1 = OT2 = OT3 = OT4 = L"0.0";
	}
} budget, sales;

void Cbudget_salesDlg::f1()
{
	CDatabase ibm;
	if (0==ibm.OpenEx(L"DSN=cms1;UID=RROSSETTI;PWD=RROSSETTI"))
	{
		AfxMessageBox(L"Failed to open database!");
		return;
	}
	ibm.SetLoginTimeout(9999);
	CRecordset bg(&ibm);
	CString query;
	query = L"select aj4tt01+aj4tt02+aj4tt03 as Q1, aj4tt04+aj4tt05+aj4tt06 as Q2, aj4tt07+aj4tt08+aj4tt09 as Q3, aj4tt10+aj4tt11+aj4tt12 as Q4 from cmsdat.glmt where aj4comp=";
	query += m_plant + L" and aj4gl#1=100 and aj4gl#2=300000 and aj4ccyy=" + m_year;
	if (0!=bg.Open(CRecordset::forwardOnly, query) && !bg.IsEOF())
	{
		bg.GetFieldValue(L"Q1", budget.CA1);
		if (budget.CA1.IsEmpty()) budget.CA1 = L"0.0";
		bg.GetFieldValue(L"Q2", budget.CA2);
		if (budget.CA2.IsEmpty()) budget.CA2 = L"0.0";
		bg.GetFieldValue(L"Q3", budget.CA3);
		if (budget.CA3.IsEmpty()) budget.CA3 = L"0.0";
		bg.GetFieldValue(L"Q4", budget.CA4);
		if (budget.CA4.IsEmpty()) budget.CA4 = L"0.0";
	}
	bg.Close();
	ibm.Close();
}

void Cbudget_salesDlg::f2()
{
	CDatabase ibm;
	if (0==ibm.OpenEx(L"DSN=cms1;UID=RROSSETTI;PWD=RROSSETTI"))
	{
		AfxMessageBox(L"Failed to open database!");
		return;
	}
	ibm.SetLoginTimeout(9999);
	CRecordset bg(&ibm);
	CString query;
	query = L"select aj4tt01+aj4tt02+aj4tt03 as Q1, aj4tt04+aj4tt05+aj4tt06 as Q2, aj4tt07+aj4tt08+aj4tt09 as Q3, aj4tt10+aj4tt11+aj4tt12 as Q4 from cmsdat.glmt where aj4comp=";
	query += m_plant + L" and aj4gl#1=100 and aj4gl#2=304000 and aj4ccyy=" + m_year;
	if (0!=bg.Open(CRecordset::forwardOnly, query) && !bg.IsEOF())
	{
		bg.GetFieldValue(L"Q1", budget.US1);
		if (budget.US1.IsEmpty()) budget.US1 = L"0.0";
		bg.GetFieldValue(L"Q2", budget.US2);
		if (budget.US2.IsEmpty()) budget.US2 = L"0.0";
		bg.GetFieldValue(L"Q3", budget.US3);
		if (budget.US3.IsEmpty()) budget.US3 = L"0.0";
		bg.GetFieldValue(L"Q4", budget.US4);
		if (budget.US4.IsEmpty()) budget.US4 = L"0.0";	}
	bg.Close();
	ibm.Close();
}
 
void Cbudget_salesDlg::f3()
{
	CDatabase ibm;
	if (0==ibm.OpenEx(L"DSN=cms1;UID=RROSSETTI;PWD=RROSSETTI"))
	{
		AfxMessageBox(L"Failed to open database!");
		return;
	}
	ibm.SetLoginTimeout(9999);
	CRecordset bg(&ibm);
	CString query;
	query = L"select aj4tt01+aj4tt02+aj4tt03 as Q1, aj4tt04+aj4tt05+aj4tt06 as Q2, aj4tt07+aj4tt08+aj4tt09 as Q3, aj4tt10+aj4tt11+aj4tt12 as Q4 from cmsdat.glmt where aj4comp=";
	query += m_plant + L" and aj4gl#1=100 and aj4gl#2=303000 and aj4ccyy=" + m_year;
	if (0!=bg.Open(CRecordset::forwardOnly, query) && !bg.IsEOF())
	{
		bg.GetFieldValue(L"Q1", budget.MX1);
		if (budget.MX1.IsEmpty()) budget.MX1 = L"0.0";
		bg.GetFieldValue(L"Q2", budget.MX2);
		if (budget.MX2.IsEmpty()) budget.MX2 = L"0.0";
		bg.GetFieldValue(L"Q3", budget.MX3);
		if (budget.MX3.IsEmpty()) budget.MX3 = L"0.0";
		bg.GetFieldValue(L"Q4", budget.MX4);
		if (budget.MX4.IsEmpty()) budget.MX4 = L"0.0";	}
	bg.Close();
	ibm.Close();
}
void Cbudget_salesDlg::f4()
{
	CDatabase ibm;
	if (0==ibm.OpenEx(L"DSN=cms1;UID=RROSSETTI;PWD=RROSSETTI"))
	{
		AfxMessageBox(L"Failed to open database!");
		return;
	}
	ibm.SetLoginTimeout(9999);
	CRecordset bg(&ibm);
	CString query;
	query = L"select aj4tt01+aj4tt02+aj4tt03 as Q1, aj4tt04+aj4tt05+aj4tt06 as Q2, aj4tt07+aj4tt08+aj4tt09 as Q3, aj4tt10+aj4tt11+aj4tt12 as Q4 from cmsdat.glmt where aj4comp=";
	query += m_plant + L" and aj4gl#1=100 and aj4gl#2=305000 and aj4ccyy=" + m_year;
	if (0!=bg.Open(CRecordset::forwardOnly, query) && !bg.IsEOF())
	{
		bg.GetFieldValue(L"Q1", budget.SA1);
		if (budget.SA1.IsEmpty()) budget.SA1 = L"0.0";
		bg.GetFieldValue(L"Q2", budget.SA2);
		if (budget.SA2.IsEmpty()) budget.SA2 = L"0.0";
		bg.GetFieldValue(L"Q3", budget.SA3);
		if (budget.SA3.IsEmpty()) budget.SA3 = L"0.0";
		bg.GetFieldValue(L"Q4", budget.SA4);
		if (budget.SA4.IsEmpty()) budget.SA4 = L"0.0";
	}
	bg.Close();
	ibm.Close();
}
void Cbudget_salesDlg::f5()
{
	CDatabase ibm;
	if (0==ibm.OpenEx(L"DSN=cms1;UID=RROSSETTI;PWD=RROSSETTI"))
	{
		AfxMessageBox(L"Failed to open database!");
		return;
	}
	ibm.SetLoginTimeout(9999);
	CRecordset bg(&ibm);
	CString query;
	query = L"select aj4tt01+aj4tt02+aj4tt03 as Q1, aj4tt04+aj4tt05+aj4tt06 as Q2, aj4tt07+aj4tt08+aj4tt09 as Q3, aj4tt10+aj4tt11+aj4tt12 as Q4 from cmsdat.glmt where aj4comp=";
	query += m_plant + L" and aj4gl#1=100 and aj4gl#2=303300 and aj4ccyy=" + m_year;
	if (0!=bg.Open(CRecordset::forwardOnly, query) && !bg.IsEOF())
	{
		bg.GetFieldValue(L"Q1", budget.EU1);
		if (budget.EU1.IsEmpty()) budget.EU1 = L"0.0";
		bg.GetFieldValue(L"Q2", budget.EU2);
		if (budget.EU2.IsEmpty()) budget.EU2 = L"0.0";
		bg.GetFieldValue(L"Q3", budget.EU3);
		if (budget.EU3.IsEmpty()) budget.EU3 = L"0.0";
		bg.GetFieldValue(L"Q4", budget.EU4);
		if (budget.EU4.IsEmpty()) budget.EU4 = L"0.0";
	}
	bg.Close();
	ibm.Close();
}
void Cbudget_salesDlg::f6()
{
	CDatabase ibm;
	if (0==ibm.OpenEx(L"DSN=cms1;UID=RROSSETTI;PWD=RROSSETTI"))
	{
		AfxMessageBox(L"Failed to open database!");
		return;
	}
	ibm.SetLoginTimeout(9999);
	CRecordset bg(&ibm);
	CString query;
	query = L"select aj4tt01+aj4tt02+aj4tt03 as Q1, aj4tt04+aj4tt05+aj4tt06 as Q2, aj4tt07+aj4tt08+aj4tt09 as Q3, aj4tt10+aj4tt11+aj4tt12 as Q4 from cmsdat.glmt where aj4comp=";
	query += m_plant + L" and aj4gl#1=100 and aj4gl#2=305500 and aj4ccyy=" + m_year;
	if (0!=bg.Open(CRecordset::forwardOnly, query) && !bg.IsEOF())
	{
		bg.GetFieldValue(L"Q1", budget.PR1);
		if (budget.PR1.IsEmpty()) budget.PR1 = L"0.0";
		bg.GetFieldValue(L"Q2", budget.PR2);
		if (budget.PR2.IsEmpty()) budget.PR2 = L"0.0";
		bg.GetFieldValue(L"Q3", budget.PR3);
		if (budget.PR3.IsEmpty()) budget.PR3 = L"0.0";
		bg.GetFieldValue(L"Q4", budget.PR4);
		if (budget.PR4.IsEmpty()) budget.PR4 = L"0.0";
	}
	bg.Close();
	ibm.Close();
}
void Cbudget_salesDlg::f7()
{
	CDatabase ibm;
	if (0==ibm.OpenEx(L"DSN=cms1;UID=RROSSETTI;PWD=RROSSETTI"))
	{
		AfxMessageBox(L"Failed to open database!");
		return;
	}
	ibm.SetLoginTimeout(9999);
	CRecordset bg(&ibm);
	CString query;
	query = L"select aj4tt01+aj4tt02+aj4tt03 as Q1, aj4tt04+aj4tt05+aj4tt06 as Q2, aj4tt07+aj4tt08+aj4tt09 as Q3, aj4tt10+aj4tt11+aj4tt12 as Q4 from cmsdat.glmt where aj4comp=";
	query += m_plant + L" and aj4gl#1=100 and aj4gl#2=306000 and aj4ccyy=" + m_year;
	if (0!=bg.Open(CRecordset::forwardOnly, query) && !bg.IsEOF())
	{
		bg.GetFieldValue(L"Q1", budget.OT1);
		if (budget.OT1.IsEmpty()) budget.OT1 = L"0.0";
		bg.GetFieldValue(L"Q2", budget.OT2);
		if (budget.OT2.IsEmpty()) budget.OT2 = L"0.0";
		bg.GetFieldValue(L"Q3", budget.OT3);
		if (budget.OT3.IsEmpty()) budget.OT3 = L"0.0";
		bg.GetFieldValue(L"Q4", budget.OT4);
		if (budget.OT4.IsEmpty()) budget.OT4 = L"0.0";
	}
	bg.Close();
	ibm.Close();
}
void Cbudget_salesDlg::f8()
{
	CDatabase ibm;
		ibm.SetLoginTimeout(0);

	if (0==ibm.OpenEx(L"DSN=cms1;UID=RROSSETTI;PWD=RROSSETTI"))
	{
		AfxMessageBox(L"Failed to open database!");
		return;
	}
	CRecordset sl(&ibm);
	CString query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	int year = _wtoi(m_year.GetString()) - 1;
	CString lastYear;
	lastYear.Format(L"%d", year);
	query += lastYear + L"-10-01' and dhidat<'" + m_year + L"-01-01' and (dhterr='CDN' or dhterr='CUS') and dhcurr='CA' and dhplnt='";
	query += m_plant + L"'";
	sl.Open(CRecordset::forwardOnly, query);
	if (!sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.CA1);
		if (sales.CA1.IsEmpty()) sales.CA1 = L"0.0";

	}
	sl.Close();
	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-01-01' and dhidat<'" + m_year + L"-04-01' and (dhterr='CDN' or dhterr='CUS') and dhcurr='CA' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.CA2);
		if (sales.CA2.IsEmpty()) sales.CA2 = L"0.0";
	}
	sl.Close();
	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-04-01' and dhidat<'" + m_year + L"-07-01' and (dhterr='CDN' or dhterr='CUS') and dhcurr='CA' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.CA3);
		if (sales.CA3.IsEmpty()) sales.CA3 = L"0.0";
	}
	sl.Close();
	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-08-01' and dhidat<'" + m_year + L"-11-01' and (dhterr='CDN' or dhterr='CUS') and dhcurr='CA' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.CA4);
		if (sales.CA4.IsEmpty()) sales.CA4 = L"0.0";
	}
	sl.Close();

	ibm.Close();
}
void Cbudget_salesDlg::f9()
{
	CDatabase ibm;
	if (0==ibm.OpenEx(L"DSN=cms1;UID=RROSSETTI;PWD=RROSSETTI"))
	{
		AfxMessageBox(L"Failed to open database!");
		return;
	}
	ibm.SetLoginTimeout(9999);
	CRecordset sl(&ibm);
	CString query;
		int year = _wtoi(m_year.GetString()) - 1;
	CString lastYear;
	lastYear.Format(L"%d", year);

	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-10-01' and dhidat<'" + m_year + L"-01-01' and (dhterr='CDN' or dhterr='CUS') and dhcurr='US' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.CU1);
		if (sales.CU1.IsEmpty()) sales.CU1 = L"0.0";
	}
	sl.Close();
	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-01-01' and dhidat<'" + m_year + L"-04-01' and (dhterr='CDN' or dhterr='CUS') and dhcurr='US' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.CU2);
		if (sales.CU2.IsEmpty()) sales.CU2 = L"0.0";
	}
	sl.Close();
	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-04-01' and dhidat<'" + m_year + L"-07-01' and (dhterr='CDN' or dhterr='CUS') and dhcurr='US' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.CU3);
		if (sales.CU3.IsEmpty()) sales.CU3 = L"0.0";
	}
	sl.Close();
	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-08-01' and dhidat<'" + m_year + L"-11-01' and (dhterr='CDN' or dhterr='CUS') and dhcurr='US' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.CU4);
		if (sales.CU4.IsEmpty()) sales.CU4 = L"0.0";
	}
	sl.Close();
	ibm.Close();
}
void Cbudget_salesDlg::f10()
{
	CDatabase ibm;
	if (0==ibm.OpenEx(L"DSN=cms1;UID=RROSSETTI;PWD=RROSSETTI"))
	{
		AfxMessageBox(L"Failed to open database!");
		return;
	}
	ibm.SetLoginTimeout(9999);
	CRecordset sl(&ibm);
	CString query;
		int year = _wtoi(m_year.GetString()) - 1;
	CString lastYear;
	lastYear.Format(L"%d", year);

	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-10-01' and dhidat<'" + m_year + L"-01-01' and dhterr='USA' and dhcurr='US' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.US1);
		if (sales.US1.IsEmpty()) sales.US1 = L"0.0";
	}
	sl.Close();
	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-01-01' and dhidat<'" + m_year + L"-04-01' and dhterr='USA' and dhcurr='US' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.US2);
		if (sales.US2.IsEmpty()) sales.US2 = L"0.0";
	}
	sl.Close();
	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-04-01' and dhidat<'" + m_year + L"-07-01' and dhterr='USA' and dhcurr='US' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.US3);
		if (sales.US3.IsEmpty()) sales.US3 = L"0.0";
	}
	sl.Close();
	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-08-01' and dhidat<'" + m_year + L"-11-01' and dhterr='USA' and dhcurr='US' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.US4);
		if (sales.US4.IsEmpty()) sales.US4 = L"0.0";
	}
	sl.Close();
	ibm.Close();
}
void Cbudget_salesDlg::f11()
{
	CDatabase ibm;
	if (0==ibm.OpenEx(L"DSN=cms1;UID=RROSSETTI;PWD=RROSSETTI"))
	{
		AfxMessageBox(L"Failed to open database!");
		return;
	}
	ibm.SetLoginTimeout(9999);
	CRecordset sl(&ibm);
	CString query;
		int year = _wtoi(m_year.GetString()) - 1;
	CString lastYear;
	lastYear.Format(L"%d", year);

	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-10-01' and dhidat<'" + m_year + L"-01-01' and dhterr='MEX' and dhcurr='US' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.MX1);
		if (sales.MX1.IsEmpty()) sales.MX1 = L"0.0";
	}
	sl.Close();
	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-01-01' and dhidat<'" + m_year + L"-04-01' and dhterr='MEX' and dhcurr='US' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.MX2);
		if (sales.MX2.IsEmpty()) sales.MX2 = L"0.0";
	}
	sl.Close();
	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-04-01' and dhidat<'" + m_year + L"-07-01' and dhterr='MEX' and dhcurr='US' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.MX3);
		if (sales.MX3.IsEmpty()) sales.MX3 = L"0.0";
	}
	sl.Close();
	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-08-01' and dhidat<'" + m_year + L"-11-01' and dhterr='MEX' and dhcurr='US' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.MX4);
		if (sales.MX4.IsEmpty()) sales.MX4 = L"0.0";
	}
	sl.Close();

	ibm.Close();}
void Cbudget_salesDlg::f12()
{
	CDatabase ibm;
	if (0==ibm.OpenEx(L"DSN=cms1;UID=RROSSETTI;PWD=RROSSETTI"))
	{
		AfxMessageBox(L"Failed to open database!");
		return;
	}
	ibm.SetLoginTimeout(9999);
	CRecordset sl(&ibm);
	CString query;
		int year = _wtoi(m_year.GetString()) - 1;
	CString lastYear;
	lastYear.Format(L"%d", year);

	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-10-01' and dhidat<'" + m_year + L"-01-01' and dhterr='SAM' and dhcurr='US' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.SA1);
		if (sales.SA1.IsEmpty()) sales.SA1 = L"0.0";
	}
	sl.Close();
	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-01-01' and dhidat<'" + m_year + L"-04-01' and dhterr='SAM' and dhcurr='US' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.SA2);
		if (sales.SA2.IsEmpty()) sales.SA2 = L"0.0";
	}
	sl.Close();
	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-04-01' and dhidat<'" + m_year + L"-07-01' and dhterr='SAM' and dhcurr='US' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.SA3);
		if (sales.SA3.IsEmpty()) sales.SA3 = L"0.0";
	}
	sl.Close();
	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-08-01' and dhidat<'" + m_year + L"-11-01' and dhterr='SAM' and dhcurr='US' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.SA4);
		if (sales.SA4.IsEmpty()) sales.SA4 = L"0.0";
	}
	sl.Close();

	ibm.Close();
}
void Cbudget_salesDlg::f13()
{
	CDatabase ibm;
		int year = _wtoi(m_year.GetString()) - 1;
	CString lastYear;
	lastYear.Format(L"%d", year);

	if (0==ibm.OpenEx(L"DSN=cms1;UID=RROSSETTI;PWD=RROSSETTI"))
	{
		AfxMessageBox(L"Failed to open database!");
		return;
	}
	ibm.SetLoginTimeout(9999);
	CRecordset sl(&ibm);
	CString query;
	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-10-01' and dhidat<'" + m_year + L"-01-01' and (dhterr='EUR' or dhterr='RUS') and dhcurr='US' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.EU1);
		if (sales.EU1.IsEmpty()) sales.EU1 = L"0.0";
	}
	sl.Close();
	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-01-01' and dhidat<'" + m_year + L"-04-01' and (dhterr='EUR' or dhterr='RUS') and dhcurr='US' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.EU2);
		if (sales.EU2.IsEmpty()) sales.EU2 = L"0.0";
	}
	sl.Close();
	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-04-01' and dhidat<'" + m_year + L"-07-01' and (dhterr='EUR' or dhterr='RUS') and dhcurr='US' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.EU3);
		if (sales.EU3.IsEmpty()) sales.EU3 = L"0.0";
	}
	sl.Close();
	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-08-01' and dhidat<'" + m_year + L"-11-01' and (dhterr='EUR' or dhterr='RUS') and dhcurr='US' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.EU4);
		if (sales.EU4.IsEmpty()) sales.EU4 = L"0.0";
	}
	sl.Close();

	ibm.Close();
}
void Cbudget_salesDlg::f14()
{
		int year = _wtoi(m_year.GetString()) - 1;
	CString lastYear;
	lastYear.Format(L"%d", year);

	CDatabase ibm;
	if (0==ibm.OpenEx(L"DSN=cms1;UID=RROSSETTI;PWD=RROSSETTI"))
	{
		AfxMessageBox(L"Failed to open database!");
		return;
	}
	ibm.SetLoginTimeout(9999);
	CRecordset sl(&ibm);
	CString query;
	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-10-01' and dhidat<'" + m_year + L"-01-01' and dhterr='ASA' and dhcurr='US' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.PR1);
		if (sales.PR1.IsEmpty()) sales.PR1 = L"0.0";
	}
	sl.Close();
	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-01-01' and dhidat<'" + m_year + L"-04-01' and dhterr='ASA' and dhcurr='US' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.PR2);
		if (sales.PR2.IsEmpty()) sales.PR2 = L"0.0";
	}
	sl.Close();
	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-04-01' and dhidat<'" + m_year + L"-07-01' and dhterr='ASA' and dhcurr='US' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.PR3);
		if (sales.PR3.IsEmpty()) sales.PR3 = L"0.0";
	}
	sl.Close();
	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-08-01' and dhidat<'" + m_year + L"-11-01' and dhterr='ASA' and dhcurr='US' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.PR4);
		if (sales.PR4.IsEmpty()) sales.PR4 = L"0.0";
	}
	sl.Close();

	ibm.Close();
}
void Cbudget_salesDlg::f15()
{
	CDatabase ibm;
	if (0==ibm.OpenEx(L"DSN=cms1;UID=RROSSETTI;PWD=RROSSETTI"))
	{
		AfxMessageBox(L"Failed to open database!");
		return;
	}
	ibm.SetLoginTimeout(9999);
	CRecordset sl(&ibm);
	CString query;
		int year = _wtoi(m_year.GetString()) - 1;
	CString lastYear;
	lastYear.Format(L"%d", year);

	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-10-01' and dhidat<'" + m_year + L"-01-01' and (dhterr='ICA' or dhterr='IUS') and dhcurr='US' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.OT1);
		if (sales.OT1.IsEmpty()) sales.OT1 = L"0.0";
	}
	sl.Close();
	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-01-01' and dhidat<'" + m_year + L"-04-01' and (dhterr='ICA' or dhterr='IUS') and dhcurr='US' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.OT2);
		if (sales.OT2.IsEmpty()) sales.OT2 = L"0.0";
	}
	sl.Close();
	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-04-01' and dhidat<'" + m_year + L"-07-01' and (dhterr='ICA' or dhterr='IUS') and dhcurr='US' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.OT3);
		if (sales.OT3.IsEmpty()) sales.OT3 = L"0.0";
	}
	sl.Close();
	query = L"select sum(dhtoti-dhtotd) as s from cmsdat.oih where dhidat>='";
	query += lastYear + L"-08-01' and dhidat<'" + m_year + L"-11-01' and (dhterr='ICA' or dhterr='IUS') and dhcurr='US' and dhplnt='";
	query += m_plant + L"'";
	if (0!=sl.Open(CRecordset::forwardOnly, query) && !sl.IsEOF())
	{
		sl.GetFieldValue(L"S", sales.OT4);
		if (sales.OT4.IsEmpty()) sales.OT4 = L"0.0";
	}
	sl.Close();
	ibm.Close();
}
void Cbudget_salesDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	// budget
	// canada with CAD
	f1();
	// usa
	f2();
	// mexico
	f3();
	// south america
	f4();
	// europe
	f5();
	// pacific rim
	f6();
	// other (inter-division)
	f7();

	// sales

	// canada with CAD
	f8();
	// canada with usd
	f9();
	// usa
	f10();
	// mexico
	f11();
	// south america
	f12();
	// europe
	f13();
	// pacific rim
	f14();
	// other (inter-division)
	f15();

	// write to decade
	CDatabase decade;
	CString query;
	if (0==decade.OpenEx(L"DSN=decade;UID=jamie;PWD=jamie"))
	{
		AfxMessageBox(L"Failed to open database!");
		return;
	} else
	{
		CRecordset decade_set(&decade);
		// check profit_temp
		decade_set.Open(CRecordset::forwardOnly, L"select * from dbo.sysobjects where name='budget_sales_temp'");
		if (!decade_set.IsEOF()) 
		{
			decade_set.Close();
			decade.ExecuteSQL(L"drop table budget_sales_temp");
		} else
		{
			decade_set.Close();
		}
		decade.ExecuteSQL(L"create table budget_sales_temp(terr varchar(32), bq1 decimal(18,2), bq2 decimal(18,2), bq3 decimal(18,2), bq4 decimal(18,2), sq1 decimal(18,2), sq2 decimal(18,2), sq3 decimal(18,2), sq4 decimal(18,2))");
		query = L"insert into budget_sales_temp values ('Canada with CAD', '";
		query += budget.CA1 + L"', '";
		query += budget.CA2 + L"', '";
		query += budget.CA3 + L"', '";
		query += budget.CA4 + L"', '";
		query += sales.CA1 + L"', '";
		query += sales.CA2+ L"', '";
		query += sales.CA3+ L"', '";
		query += sales.CA4+ L"')";
		decade.ExecuteSQL(query);
		query = L"insert into budget_sales_temp values ('Canada with USD', '";
		query += budget.CU1 + L"', '";
		query += budget.CU2 + L"', '";
		query += budget.CU3 + L"', '";
		query += budget.CU4 + L"', '";
		query += sales.CU1 + L"', '";
		query += sales.CU2+ L"', '";
		query += sales.CU3+ L"', '";
		query += sales.CU4+ L"')";
		decade.ExecuteSQL(query);
		query = L"insert into budget_sales_temp values ('US', '";
		query += budget.US1 + L"', '";
		query += budget.US2 + L"', '";
		query += budget.US3 + L"', '";
		query += budget.US4 + L"', '";
		query += sales.US1 + L"', '";
		query += sales.US2+ L"', '";
		query += sales.US3+ L"', '";
		query += sales.US4+ L"')";
		decade.ExecuteSQL(query);
		query = L"insert into budget_sales_temp values ('Mexico', '";
		query += budget.MX1 + L"', '";
		query += budget.MX2 + L"', '";
		query += budget.MX3 + L"', '";
		query += budget.MX4 + L"', '";
		query += sales.MX1 + L"', '";
		query += sales.MX2+ L"', '";
		query += sales.MX3+ L"', '";
		query += sales.MX4+ L"')";
		decade.ExecuteSQL(query);
				query = L"insert into budget_sales_temp values ('South America', '";
		query += budget.SA1 + L"', '";
		query += budget.SA2 + L"', '";
		query += budget.SA3 + L"', '";
		query += budget.SA4 + L"', '";
		query += sales.SA1 + L"', '";
		query += sales.SA2+ L"', '";
		query += sales.SA3+ L"', '";
		query += sales.SA4+ L"')";
		decade.ExecuteSQL(query);
		query = L"insert into budget_sales_temp values ('Europe', '";
		query += budget.EU1 + L"', '";
		query += budget.EU2 + L"', '";
		query += budget.EU3 + L"', '";
		query += budget.EU4 + L"', '";
		query += sales.EU1 + L"', '";
		query += sales.EU2+ L"', '";
		query += sales.EU3+ L"', '";
		query += sales.EU4+ L"')";
		decade.ExecuteSQL(query);

				query = L"insert into budget_sales_temp values ('Pacific Rim', '";
		query += budget.PR1 + L"', '";
		query += budget.PR2 + L"', '";
		query += budget.PR3 + L"', '";
		query += budget.PR4 + L"', '";
		query += sales.PR1 + L"', '";
		query += sales.PR2+ L"', '";
		query += sales.PR3+ L"', '";
		query += sales.PR4+ L"')";
		decade.ExecuteSQL(query);
				query = L"insert into budget_sales_temp values ('Other', '";
		query += budget.OT1 + L"', '";
		query += budget.OT2 + L"', '";
		query += budget.OT3 + L"', '";
		query += budget.OT4 + L"', '";
		query += sales.OT1 + L"', '";
		query += sales.OT2+ L"', '";
		query += sales.OT3+ L"', '";
		query += sales.OT4+ L"')";
		decade.ExecuteSQL(query);

		decade.Close();
	}
}