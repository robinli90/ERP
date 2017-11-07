
// quotationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "quotation.h"
#include "quotationDlg.h"
#include "afxdialogex.h"
#include <afxdb.h>
#include <fstream>
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// CquotationDlg dialog




CquotationDlg::CquotationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CquotationDlg::IDD, pParent)
	, m_num(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CquotationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NUMBER, m_num);
}

BEGIN_MESSAGE_MAP(CquotationDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CquotationDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CquotationDlg message handlers

BOOL CquotationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	GetDlgItem(IDC_NUMBER)->SetFocus();

	return FALSE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CquotationDlg::OnPaint()
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
HCURSOR CquotationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

struct Record
{
	CString item;
	CString line;
	CString die_num;
	CString desc;
	CString qty;
	CString price;
	Record()
	{
		price = L"0.00";
	}
};

void CquotationDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	// check input
	if (m_num.GetLength() != 5)
	{
		AfxMessageBox(L"Invalid Quotation Number!");
		m_num.Empty();
		UpdateData(FALSE);
		GetDlgItem(IDC_NUMBER)->SetFocus();
	} else
	{
		CDatabase db;
		if (0==db.OpenEx(L"DSN=cms1;UID=RROSSETTI;PWD=RROSSETTI"))
		{
			AfxMessageBox(L"Failed to open database!");
			return;
		} else
		{
			CRecordset set(&db);
			CString query = L"select b.dgitm#, a.ddran#, b.dglin#, b.dgdesc, a.ddqtoi, a.ddtotb from cmsdat.qcri as a, cmsdat.qcrd as b where a.ddord#=b.dgord# and a.dditm#=b.dgitm# and a.ddord#=";
			query += m_num;			
			if (0==set.Open(CRecordset::forwardOnly, query) || set.IsEOF())
			{
				AfxMessageBox(L"Invalid Quotation Number!");
				return;
			} else
			{
				// get data
				vector<Record> vec_rec;
				while (!set.IsEOF())
				{
					Record rec;
					set.GetFieldValue(L"DGITM#", rec.item);
					rec.item = rec.item.Trim();
					set.GetFieldValue(L"DDRAN#", rec.die_num);
					rec.die_num = rec.die_num.Trim();
					set.GetFieldValue(L"DGLIN#", rec.line);
					rec.line = rec.line.Trim();
					set.GetFieldValue(L"DGDESC", rec.desc);
					rec.desc = rec.desc.Trim();
					if (rec.desc==L"Fake core 5%" || rec.desc==L"Wire support" || rec.desc==L"PKT CHRG")
					{
						set.MoveNext();
						continue;
					}
					set.GetFieldValue(L"DDQTOI", rec.qty);
					rec.qty = rec.qty.Trim();
					if (rec.line==L"1" || (rec.line!=L"1"&&rec.desc==L"POCKET CHARGE"))
					{
						set.GetFieldValue(L"DDTOTB", rec.price);
						rec.price = rec.price.Trim();
					}
					vec_rec.push_back(rec);
					set.MoveNext();
				}
				// get steel surcharge (or other discount)
				set.Close();
				query = L"select ffitm#, ffddes, ffdext from cmsdat.qcrs where fford#=";
				query += m_num;
				if (0==set.Open(CRecordset::forwardOnly, query) || set.IsEOF())
				{
					AfxMessageBox(L"Invalid Quotation Number!");
					return;
				} else
				{
					while (!set.IsEOF())
					{
						Record rec;
						set.GetFieldValue(L"FFITM#", rec.item);
						rec.item = rec.item.Trim();
						set.GetFieldValue(L"FFDDES", rec.desc);
						rec.desc = rec.desc.Trim();
						set.GetFieldValue(L"FFDEXT", rec.price);
						rec.price = rec.price.Trim();
						// find place to insert
						for (vector<Record>::iterator iter=vec_rec.begin(); iter!=vec_rec.end(); iter++)
						{
							while (iter->item == rec.item)
							{
								iter++;
								if (iter == vec_rec.end())
								{
									iter--;
									break;
								} else if (iter->item != rec.item)
								{
									// insert
									rec.die_num = (iter-1)->die_num;
									vec_rec.insert(iter, rec);
									iter = vec_rec.end() - 1;
									break;
								}
							}
						}
						set.MoveNext();
					}
					set.Close();
				}
				// get customer infomation
				query = L"select b.dcodat, a.bvname, a.bvadr1, a.bvadr2, a.bvadr3, a.bvadr4, a.bvcity from cmsdat.cust as a, cmsdat.qcrh as b where a.bvcust=b.dcbcus and b.dcord#=";
				query += m_num;
				CString date;
				CString name;
				CString add1;
				CString add2;
				CString add3;
				CString add4;
				CString city;
				if (0==set.Open(CRecordset::forwardOnly, query) || set.IsEOF())
				{
					AfxMessageBox(L"Invalid Customer Number!");
					return;
				} else
				{
					set.GetFieldValue(L"DCODAT", date);
					date = date.Trim();
					set.GetFieldValue(L"BVNAME", name);
					name = name.Trim();
					set.GetFieldValue(L"BVADR1", add1);
					add1 = add1.Trim();
					set.GetFieldValue(L"BVADR2", add2);
					add2 = add2.Trim();
					set.GetFieldValue(L"BVADR3", add3);
					add3 = add3.Trim();
					set.GetFieldValue(L"BVADR4", add4);
					add4 = add4.Trim();
					set.GetFieldValue(L"BVCITY", city);
					city = city.Trim();
					set.Close();
				}
				// write to decade
				CDatabase decade;
				if (0==decade.OpenEx(L"DSN=decade;UID=jamie;PWD=jamie"))
				{
					AfxMessageBox(L"Failed to open database!");
					return;
				} else
				{
					// ensure table exists
					CRecordset decade_set(&decade);
					decade_set.Open(CRecordset::forwardOnly, L"select * from dbo.sysobjects where name='quot_temp'");
					if (!decade_set.IsEOF()) 
					{
						decade_set.Close();
						decade.ExecuteSQL(L"drop table quot_temp");
					} else
					{
						decade_set.Close();
					}
					decade.ExecuteSQL(L"create table quot_temp(item int,die_num varchar(32),detail varchar(255),price decimal(18,2))");
					for each(Record rec in vec_rec)
					{
						query = L"insert into quot_temp values ('";
						query += rec.item;
						query += L"', '";
						query += rec.die_num;
						query += L"', '";
						query += rec.desc;
						query += L"', '";
						query += rec.price;
						query += L"')";
						decade.ExecuteSQL(query);
					}
					// cutm_temp
					decade.ExecuteSQL(L"drop table cutm_temp");
					decade.ExecuteSQL(L"create table cutm_temp(num int,input_date datetime,name varchar(255),add1 varchar(255),add2 varchar(255),add3 varchar(255),add4 varchar(255),city varchar(255))");
					query = L"insert into cutm_temp values ('";
					query += m_num;
					query += L"', '";
					query += date;
					query += L"', '";
					query += name;
					query += L"', '";
					query += add1;
					query += L"', '";
					query += add2;
					query += L"', '";
					query += add3;
					query += L"', '";
					query += add4;
					query += L"', '";
					query += city;
					query += L"')";
					decade.ExecuteSQL(query);
				}
				decade.Close();
			}
		}
		db.Close();
	}
	ShellExecute(NULL, NULL, L"\\\\10.0.0.6\\shopdata\\development\\tiger\\report\\quotation.rpt", NULL, NULL, SW_SHOW);
	OnOK();
}