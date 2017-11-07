
// trail_balanceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "trail_balance.h"
#include "trail_balanceDlg.h"
#include "afxdialogex.h"
#include <afxdb.h>
#include <vector>
#include <map>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ctrail_balanceDlg dialog




Ctrail_balanceDlg::Ctrail_balanceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Ctrail_balanceDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ctrail_balanceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Ctrail_balanceDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &Ctrail_balanceDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Ctrail_balanceDlg message handlers

BOOL Ctrail_balanceDlg::OnInitDialog()
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

void Ctrail_balanceDlg::OnPaint()
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
HCURSOR Ctrail_balanceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

struct Account
{
	int no1;
	int no2;
	CString name;
	// markham
	CString trans01;
    // michigan
    CString trans03;
    // colombia
    CString trans04;
	CString trans41;
	CString trans48;
	CString trans49;
    // texas
    CString trans05;

	Account()
	{
		no1 = no2 = 0;
		name = L"";
        trans01 = L"0.0";
        trans03 = L"0.0";
		trans04 = L"0.0";
        trans05 = L"0.0";
		trans41 = L"0.0";
		trans48 = L"0.0";
		trans49 = L"0.0";
	}
};

int fiscalYear = 2014;
int fiscalMonth = 1;
int calendarYear = 2013;
int calendarMonth = 10;

bool needMarkham = 0;
bool needMichigan = 0;
bool needTexas = 0;
bool needColombia = 1;

void Ctrail_balanceDlg::OnBnClickedOk()
{	
	map<int, Account> pool;

	// get record
	CString query;
	CDatabase ibm;
	ibm.SetQueryTimeout(0);
	if (0==ibm.OpenEx(L"DSN=cms1;UID=RROSSETTI;PWD=RROSSETTI"))
	{
		AfxMessageBox(L"Failed to open database!");
		return;
	} else
	{
		CRecordset ibm_set(&ibm);
		if (needMarkham)
		{
			// get plant 01
			query.Format(L"select a.aj4gl#1 as no1, a.aj4gl#2 as no2, b.aztitl as name, b.azatyp as account_type, (a.aj4tt%02d+aj4ob%02d) as end_balance from cmsdat.glmt as a, cmsdat.mast as b where a.aj4comp=1 and a.aj4ccyy=%d and a.aj4gl#1=b.azgl#1 and a.aj4gl#2=b.azgl#2 and b.azcomp=1 and a.aj4gl#1!=200", fiscalMonth, fiscalMonth, fiscalYear);
			if (0==ibm_set.Open(CRecordset::forwardOnly, query) || ibm_set.IsEOF())
			{
				AfxMessageBox(L"No Record!");
				return;
			} else
			{
				while (!ibm_set.IsEOF())
				{
					Account account;
					CString value;
					ibm_set.GetFieldValue(L"NO1", value);
					value.Trim();
					account.no1 = _wtoi(value.GetString())%100;
					ibm_set.GetFieldValue(L"NO2", value);
					value.Trim();
					account.no2 = _wtoi(value.GetString());
					ibm_set.GetFieldValue(L"NAME", account.name);
					account.name.Trim();
					ibm_set.GetFieldValue(L"END_BALANCE", account.trans01);
					account.trans01.Trim();
					ibm_set.MoveNext();
					int key = account.no1*1000000+account.no2;
					pool[key] = account;
				}
			}
			ibm_set.Close();
		}
		if (needMichigan)
		{
			// plant 03
			query.Format(L"select a.aj4gl#1 as no1, a.aj4gl#2 as no2, b.aztitl as name, b.azatyp as account_type, (a.aj4tt%02d+aj4ob%02d) as end_balance from cmsdat.glmt as a, cmsdat.mast as b where a.aj4comp=3 and a.aj4ccyy=%d and a.aj4gl#1=b.azgl#1 and a.aj4gl#2=b.azgl#2 and b.azcomp=3", fiscalMonth, fiscalMonth, fiscalYear);
			if (0==ibm_set.Open(CRecordset::forwardOnly, query) || ibm_set.IsEOF())
			{
				AfxMessageBox(L"No Record!");
				return;
			} else
			{
				while (!ibm_set.IsEOF())
				{
					Account account;
					CString value;
					ibm_set.GetFieldValue(L"NO1", value);
					value.Trim();
					account.no1 = _wtoi(value.GetString())%100;
					ibm_set.GetFieldValue(L"NO2", value);
					value.Trim();
					account.no2 = _wtoi(value.GetString());
					ibm_set.GetFieldValue(L"NAME", account.name);
					account.name.Trim();
					ibm_set.GetFieldValue(L"END_BALANCE", account.trans03);
					account.trans03.Trim();
					ibm_set.MoveNext();
					int key = account.no1*1000000+account.no2;
					if (pool.end() == pool.find(key))
					{
						pool[key] = account;
					} else
					{
						pool[key].trans03 = account.trans03;
					}
				}
			}
			ibm_set.Close();
		}
		if (needTexas)
		{
			// plant 05
			query.Format(L"select a.aj4gl#1 as no1, a.aj4gl#2 as no2, b.aztitl as name, b.azatyp as account_type, (a.aj4tt%02d+aj4ob%02d) as end_balance from cmsdat.glmt as a, cmsdat.mast as b where a.aj4comp=5 and a.aj4ccyy=%d and a.aj4gl#1=b.azgl#1 and a.aj4gl#2=b.azgl#2 and b.azcomp=5", fiscalMonth, fiscalMonth, fiscalYear);
			if (0==ibm_set.Open(CRecordset::forwardOnly, query) || ibm_set.IsEOF())
			{
				AfxMessageBox(L"No Record!");
				return;
			} else
			{
				while (!ibm_set.IsEOF())
				{
					Account account;
					CString value;
					ibm_set.GetFieldValue(L"NO1", value);
					value.Trim();
					account.no1 = _wtoi(value.GetString())%100;
					ibm_set.GetFieldValue(L"NO2", value);
					value.Trim();
					account.no2 = _wtoi(value.GetString());
					ibm_set.GetFieldValue(L"NAME", account.name);
					account.name.Trim();
					ibm_set.GetFieldValue(L"END_BALANCE", account.trans05);
					account.trans05.Trim();
					ibm_set.MoveNext();
					int key = account.no1*1000000+account.no2;
					if (pool.end() == pool.find(key))
					{
						pool[key] = account;
					} else
					{
						pool[key].trans05 = account.trans05;
					}
				}
			}
			ibm_set.Close();
		}
		if (needColombia)
		{
			// plant 04
			query.Format(L"select a.aj4gl#1 as no1, a.aj4gl#2 as no2, b.aztitl as name, b.azatyp as account_type, (a.aj4tt%02d+aj4ob%02d) as end_balance from cmsdat.glmt as a, cmsdat.mast as b where a.aj4comp=4 and a.aj4ccyy=%d and a.aj4gl#1=b.azgl#1 and a.aj4gl#2=b.azgl#2 and b.azcomp=4", calendarMonth, calendarMonth, calendarYear);
			if (0==ibm_set.Open(CRecordset::forwardOnly, query) || ibm_set.IsEOF())
			{
				AfxMessageBox(L"No Record!");
				return;
			} else
			{
				while (!ibm_set.IsEOF())
				{
					Account account;
					CString value;
					ibm_set.GetFieldValue(L"NO1", value);
					value.Trim();
					account.no1 = _wtoi(value.GetString())%100;
					ibm_set.GetFieldValue(L"NO2", value);
					value.Trim();
					account.no2 = _wtoi(value.GetString());
					ibm_set.GetFieldValue(L"NAME", account.name);
					account.name.Trim();
					ibm_set.GetFieldValue(L"END_BALANCE", account.trans04);
					account.trans04.Trim();
					ibm_set.MoveNext();
					int key = account.no1*1000000+account.no2;
					if (pool.end() == pool.find(key))
					{
						pool[key] = account;
					} else
					{
						pool[key].trans04 = account.trans04;
					}
				}
			}
			ibm_set.Close();
			// plant 41
			query.Format(L"select a.aj4gl#1 as no1, a.aj4gl#2 as no2, b.aztitl as name, b.azatyp as account_type, (a.aj4tt%02d+aj4ob%02d) as end_balance from cmsdat.glmt as a, cmsdat.mast as b where a.aj4comp=41 and a.aj4ccyy=%d and a.aj4gl#1=b.azgl#1 and a.aj4gl#2=b.azgl#2 and b.azcomp=41", fiscalMonth, fiscalMonth, fiscalYear);
			if (0==ibm_set.Open(CRecordset::forwardOnly, query) || ibm_set.IsEOF())
			{
				AfxMessageBox(L"No Record!");
				return;
			} else
			{
				while (!ibm_set.IsEOF())
				{
					Account account;
					CString value;
					ibm_set.GetFieldValue(L"NO1", value);
					value.Trim();
					account.no1 = _wtoi(value.GetString())%100;
					ibm_set.GetFieldValue(L"NO2", value);
					value.Trim();
					account.no2 = _wtoi(value.GetString());
					ibm_set.GetFieldValue(L"NAME", account.name);
					account.name.Trim();
					ibm_set.GetFieldValue(L"END_BALANCE", account.trans41);
					account.trans41.Trim();
					ibm_set.MoveNext();
					int key = account.no1*1000000+account.no2;
					if (pool.end() == pool.find(key))
					{
						pool[key] = account;
					} else
					{
						pool[key].trans41 = account.trans41;
					}
				}
			}
			ibm_set.Close();
			// plant 48
			query.Format(L"select a.aj4gl#1 as no1, a.aj4gl#2 as no2, b.aztitl as name, b.azatyp as account_type, (a.aj4tt%02d+aj4ob%02d) as end_balance from cmsdat.glmt as a, cmsdat.mast as b where a.aj4comp=48 and a.aj4ccyy=%d and a.aj4gl#1=b.azgl#1 and a.aj4gl#2=b.azgl#2 and b.azcomp=48", calendarMonth, calendarMonth, calendarYear);
			if (0==ibm_set.Open(CRecordset::forwardOnly, query) || ibm_set.IsEOF())
			{
				AfxMessageBox(L"No Record!");
				return;
			} else
			{
				while (!ibm_set.IsEOF())
				{
					Account account;
					CString value;
					ibm_set.GetFieldValue(L"NO1", value);
					value.Trim();
					account.no1 = _wtoi(value.GetString())%100;
					ibm_set.GetFieldValue(L"NO2", value);
					value.Trim();
					account.no2 = _wtoi(value.GetString());
					ibm_set.GetFieldValue(L"NAME", account.name);
					account.name.Trim();
					ibm_set.GetFieldValue(L"END_BALANCE", account.trans48);
					account.trans48.Trim();
					ibm_set.MoveNext();
					int key = account.no1*1000000+account.no2;
					if (pool.end() == pool.find(key))
					{
						pool[key] = account;
					} else
					{
						pool[key].trans48 = account.trans48;
					}
				}
			}
			ibm_set.Close();
			// plant 49
			query.Format(L"select a.aj4gl#1 as no1, a.aj4gl#2 as no2, b.aztitl as name, b.azatyp as account_type, (a.aj4tt%02d+aj4ob%02d) as end_balance from cmsdat.glmt as a, cmsdat.mast as b where a.aj4comp=49 and a.aj4ccyy=%d and a.aj4gl#1=b.azgl#1 and a.aj4gl#2=b.azgl#2 and b.azcomp=49", fiscalMonth, fiscalMonth, fiscalYear);
			if (0==ibm_set.Open(CRecordset::forwardOnly, query) || ibm_set.IsEOF())
			{
				AfxMessageBox(L"No Record!");
				return;
			} else
			{
				while (!ibm_set.IsEOF())
				{
					Account account;
					CString value;
					ibm_set.GetFieldValue(L"NO1", value);
					value.Trim();
					account.no1 = _wtoi(value.GetString())%100;
					ibm_set.GetFieldValue(L"NO2", value);
					value.Trim();
					account.no2 = _wtoi(value.GetString());
					ibm_set.GetFieldValue(L"NAME", account.name);
					account.name.Trim();
					ibm_set.GetFieldValue(L"END_BALANCE", account.trans49);
					account.trans49.Trim();
					ibm_set.MoveNext();
					int key = account.no1*1000000+account.no2;
					if (pool.end() == pool.find(key))
					{
						pool[key] = account;
					} else
					{
						pool[key].trans49 = account.trans49;
					}
				}
			}
			ibm_set.Close();
		}
	}
	ibm.Close();
	// write to temp table
	CDatabase decade;
	if (0==decade.OpenEx(L"DSN=decadeMar;UID=jamie;PWD=jamie"))
	{
		AfxMessageBox(L"Failed to open database!");
		return;
	} else
	{
		CRecordset decade_set(&decade);
		// check profit_temp
		decade_set.Open(CRecordset::forwardOnly, L"select * from dbo.sysobjects where name='trail_balance_temp'");
		if (!decade_set.IsEOF()) 
		{
			decade_set.Close();
			decade.ExecuteSQL(L"drop table trail_balance_temp");
		} else
		{
			decade_set.Close();
		}
		decade.ExecuteSQL(L"create table trail_balance_temp(ACCOUNT varchar(32), NAME varchar(32), TRANS01 decimal(18,2), TRANS03 decimal(18,2), TRANS05 decimal(18,2), TRANS04 decimal(18,2), TRANS41 decimal(18,2), TRANS48 decimal(18,2), TRANS49 decimal(18,2))");
		for each(pair<int, Account> e in pool)
		{
			
			CString id;
			id.Format(L"%02d-%06d", e.second.no1, e.second.no2);
			id.Insert(id.GetLength()-2, L'-');
			// process acount
			e.second.name.Replace(L"'", L"''");
			query = L"insert into trail_balance_temp values ('";
			query += id + L"', '";
			query += e.second.name + L"', '";
			query += e.second.trans01 + L"', '";
			query += e.second.trans03 + L"', '";
			query += e.second.trans05 + L"', '";
			query += e.second.trans04 + L"', '";
			query += e.second.trans41 + L"', '";
			query += e.second.trans48 + L"', '";
			query += e.second.trans49 + L"')";
			decade.ExecuteSQL(query);
		}
		decade.Close();
	}
	OnOK();
}