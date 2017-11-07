
// monthly_report_by_customerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "monthly_report_by_customer.h"
#include "monthly_report_by_customerDlg.h"
#include "afxdialogex.h"
#include <vector>
#include <math.h>
#include <afxdb.h>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cmonthly_report_by_customerDlg dialog




Cmonthly_report_by_customerDlg::Cmonthly_report_by_customerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cmonthly_report_by_customerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cmonthly_report_by_customerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cmonthly_report_by_customerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &Cmonthly_report_by_customerDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Cmonthly_report_by_customerDlg message handlers

BOOL Cmonthly_report_by_customerDlg::OnInitDialog()
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

void Cmonthly_report_by_customerDlg::OnPaint()
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
HCURSOR Cmonthly_report_by_customerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

struct Cust
{
	CString id;
	CString name;
	CString cur;
	double oct11;
	double nov11;
	double dec11;
	double jan12;
	double feb12;
	double mar12;
	double apr12;
	double may12;
	double jun12;
};

void Cmonthly_report_by_customerDlg::OnBnClickedOk()
{
	vector<Cust> custVec;
	CString query;
	CDatabase ibm;
	if (0==ibm.OpenEx(L"DSN=cms1;UID=RROSSETTI;PWD=RROSSETTI"))
	{
		AfxMessageBox(L"Failed to open solarsoft db!");
		return;
	} else
	{
		ibm.SetQueryTimeout(9999);
		// get customer list
		CRecordset custSet(&ibm);
		/*query = L"select a.bvcust, a.bvname, a.bvcurr, sum(b.dipric) as s from (select a.dhinv#, b.bvcust, b.bvname, b.bvcurr from cmsdat.oih as a, cmsdat.cust as b where a.dhplnt='001' and (a.dhidat>='2011-10-01' and a.dhidat<='2011-10-31') and b.bvcust=a.dhbcs#) as a, cmsdat.oid as b where a.dhinv#=b.diinv# group by a.bvcust, a.bvname, a.bvcurr";*/
		query = L"select bvcust, bvname, bvcurr from cmsdat.cust";
		if (0==custSet.Open(CRecordset::forwardOnly, query) || custSet.IsEOF())
		{
			AfxMessageBox(L"DB ERR!");
			return;
		} else
		{
			while (!custSet.IsEOF())
			{
				Cust cust;
				CString value;
				double sum = 0.0;
				custSet.GetFieldValue(L"BVCUST", cust.id);
				cust.id = cust.id.Trim();
				custSet.GetFieldValue(L"BVNAME", cust.name);
				cust.name = cust.name.Trim();
				cust.name.Replace(L"'", L"''");
				custSet.GetFieldValue(L"BVCURR", cust.cur);
				cust.cur = cust.cur.Trim();
				custVec.push_back(cust);
				custSet.MoveNext();
			}
		}
		custSet.Close();
		// get sales data for every customer
		CRecordset saleSet(&ibm);
		for (vector<Cust>::iterator iter=custVec.begin(); iter!=custVec.end(); iter++)
		{
			CString value;
			// Oct 2011
			query = L"select sum(b.dipric) as s from (select dhinv# from cmsdat.oih where dhplnt='001' and (dhidat>='2011-10-01' and dhidat<='2011-10-31') and dhbcs#='";
			query += iter->id + L"') as a, cmsdat.oid as b where a.dhinv#=b.diinv#";
			if (0==saleSet.Open(CRecordset::forwardOnly, query))
			{
				AfxMessageBox(L"DB ERR!");
				return;
			} else if (saleSet.IsEOF())
			{
				iter->oct11 = 0.0;
			} else
			{
				CString value;
				saleSet.GetFieldValue(L"S", value);
				value = value.Trim();
				iter->oct11 = _wtof(value.GetBuffer());
			}
			saleSet.Close();
			// Nov 2011
			query = L"select sum(b.dipric) as s from (select dhinv# from cmsdat.oih where dhplnt='001' and (dhidat>='2011-11-01' and dhidat<='2011-11-30') and dhbcs#='";
			query += iter->id + L"') as a, cmsdat.oid as b where a.dhinv#=b.diinv#";
			if (0==saleSet.Open(CRecordset::forwardOnly, query))
			{
				AfxMessageBox(L"DB ERR!");
				return;
			} else if (saleSet.IsEOF())
			{
				iter->nov11 = 0.0;
			} else
			{
				CString value;
				saleSet.GetFieldValue(L"S", value);
				value = value.Trim();
				iter->nov11 = _wtof(value.GetBuffer());
			}
			saleSet.Close();
			// Dec 2011
			query = L"select sum(b.dipric) as s from (select dhinv# from cmsdat.oih where dhplnt='001' and (dhidat>='2011-12-01' and dhidat<='2011-12-31') and dhbcs#='";
			query += iter->id + L"') as a, cmsdat.oid as b where a.dhinv#=b.diinv#";
			if (0==saleSet.Open(CRecordset::forwardOnly, query))
			{
				AfxMessageBox(L"DB ERR!");
				return;
			} else if (saleSet.IsEOF())
			{
				iter->dec11 = 0.0;
			} else
			{
				CString value;
				saleSet.GetFieldValue(L"S", value);
				value = value.Trim();
				iter->dec11 = _wtof(value.GetBuffer());
			}
			saleSet.Close();
			// Jan 2012
			query = L"select sum(b.dipric) as s from (select dhinv# from cmsdat.oih where dhplnt='001' and (dhidat>='2012-01-01' and dhidat<='2012-01-31') and dhbcs#='";
			query += iter->id + L"') as a, cmsdat.oid as b where a.dhinv#=b.diinv#";
			if (0==saleSet.Open(CRecordset::forwardOnly, query))
			{
				AfxMessageBox(L"DB ERR!");
				return;
			} else if (saleSet.IsEOF())
			{
				iter->jan12 = 0.0;
			} else
			{
				CString value;
				saleSet.GetFieldValue(L"S", value);
				value = value.Trim();
				iter->jan12 = _wtof(value.GetBuffer());
			}
			saleSet.Close();
			// Feb 2012
			query = L"select sum(b.dipric) as s from (select dhinv# from cmsdat.oih where dhplnt='001' and (dhidat>='2012-02-01' and dhidat<='2012-02-29') and dhbcs#='";
			query += iter->id + L"') as a, cmsdat.oid as b where a.dhinv#=b.diinv#";
			if (0==saleSet.Open(CRecordset::forwardOnly, query))
			{
				AfxMessageBox(L"DB ERR!");
				return;
			} else if (saleSet.IsEOF())
			{
				iter->feb12 = 0.0;
			} else
			{
				CString value;
				saleSet.GetFieldValue(L"S", value);
				value = value.Trim();
				iter->feb12 = _wtof(value.GetBuffer());
			}
			saleSet.Close();
			// Mar 2012
			query = L"select sum(b.dipric) as s from (select dhinv# from cmsdat.oih where dhplnt='001' and (dhidat>='2012-03-01' and dhidat<='2012-03-31') and dhbcs#='";
			query += iter->id + L"') as a, cmsdat.oid as b where a.dhinv#=b.diinv#";
			if (0==saleSet.Open(CRecordset::forwardOnly, query))
			{
				AfxMessageBox(L"DB ERR!");
				return;
			} else if (saleSet.IsEOF())
			{
				iter->mar12 = 0.0;
			} else
			{
				CString value;
				saleSet.GetFieldValue(L"S", value);
				value = value.Trim();
				iter->mar12 = _wtof(value.GetBuffer());
			}
			saleSet.Close();
			// Apr 2012
			query = L"select sum(b.dipric) as s from (select dhinv# from cmsdat.oih where dhplnt='001' and (dhidat>='2012-04-01' and dhidat<='2012-04-30') and dhbcs#='";
			query += iter->id + L"') as a, cmsdat.oid as b where a.dhinv#=b.diinv#";
			if (0==saleSet.Open(CRecordset::forwardOnly, query))
			{
				AfxMessageBox(L"DB ERR!");
				return;
			} else if (saleSet.IsEOF())
			{
				iter->apr12 = 0.0;
			} else
			{
				CString value;
				saleSet.GetFieldValue(L"S", value);
				value = value.Trim();
				iter->apr12 = _wtof(value.GetBuffer());
			}
			saleSet.Close();
			// May 2012
			query = L"select sum(b.dipric) as s from (select dhinv# from cmsdat.oih where dhplnt='001' and (dhidat>='2012-05-01' and dhidat<='2012-05-31') and dhbcs#='";
			query += iter->id + L"') as a, cmsdat.oid as b where a.dhinv#=b.diinv#";
			if (0==saleSet.Open(CRecordset::forwardOnly, query))
			{
				AfxMessageBox(L"DB ERR!");
				return;
			} else if (saleSet.IsEOF())
			{
				iter->may12 = 0.0;
			} else
			{
				CString value;
				saleSet.GetFieldValue(L"S", value);
				value = value.Trim();
				iter->may12 = _wtof(value.GetBuffer());
			}
			saleSet.Close();
			// Jun 2012
			query = L"select sum(b.dipric) as s from (select dhinv# from cmsdat.oih where dhplnt='001' and (dhidat>='2012-06-01' and dhidat<='2012-06-30') and dhbcs#='";
			query += iter->id + L"') as a, cmsdat.oid as b where a.dhinv#=b.diinv#";
			if (0==saleSet.Open(CRecordset::forwardOnly, query))
			{
				AfxMessageBox(L"DB ERR!");
				return;
			} else if (saleSet.IsEOF())
			{
				iter->jun12 = 0.0;
			} else
			{
				CString value;
				saleSet.GetFieldValue(L"S", value);
				value = value.Trim();
				iter->jun12 = _wtof(value.GetBuffer());
			}
			saleSet.Close();
		}
	}
	ibm.Close();
	// check decade
	CDatabase decade;
	if (0==decade.OpenEx(L"DSN=decade;UID=jamie;PWD=jamie"))
	{
		AfxMessageBox(L"Failed to open decade db!");
		return;
	} else
	{
		// check month_by_cust_temp
		CRecordset decadeSet;
		decadeSet.Open(CRecordset::forwardOnly, L"select * from dbo.sysobjects where name='month_by_cust_temp'");
		if (!decadeSet.IsEOF()) 
		{
			decadeSet.Close();
			decade.ExecuteSQL(L"drop table month_by_cust_temp");
		} else
		{
			decadeSet.Close();
		}
		decade.ExecuteSQL(L"create table month_by_cust_temp(id varchar(32), name varchar(32), cur varchar(32), oct11 decimal(18,2), nov11 decimal(18,2), dec11 decimal(18,2), jan12 decimal(18,2), feb12 decimal(18,2), mar12 decimal(18,2), apr12 decimal(18,2), may12 decimal(18,2), jun12 decimal(18,2))");
	}
	// write to decade
	for each(Cust cust in custVec)
	{
		// pass inactive customer
		if (fabs(cust.oct11)<0.1 && fabs(cust.nov11)<0.1 && fabs(cust.dec11)<0.1 && fabs(cust.jan12)<0.1 && fabs(cust.feb12)<0.1 && fabs(cust.mar12)<0.1 && fabs(cust.apr12)<0.1 && fabs(cust.may12)<0.1 && fabs(cust.jun12)<0.1)
		{
			continue;
		}
		// process decade
		query = L"insert into month_by_cust_temp values ('";
		query += cust.id + L"', '";
		query += cust.name + L"', '";
		query += cust.cur + L"', ";
		CString dbVal;
		dbVal.Format(L"%.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f)", cust.oct11, cust.nov11, cust.dec11, cust.jan12, cust.feb12, cust.mar12, cust.apr12, cust.may12, cust.jun12);
		query += dbVal;
		decade.ExecuteSQL(query);
	}
	decade.Close();
}
