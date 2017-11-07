
// invoiceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "invoice.h"
#include "invoiceDlg.h"
#include "afxdialogex.h"
#include <afxdb.h>
#include <vector>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CinvoiceDlg dialog




CinvoiceDlg::CinvoiceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CinvoiceDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CinvoiceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_YEAR, m_yearListCtrl);
	DDX_Control(pDX, IDC_LIST_MONTH, m_monthListCtrl);
	DDX_LBString(pDX, IDC_LIST_MONTH, m_month);
	DDX_LBString(pDX, IDC_LIST_YEAR, m_year);
}

BEGIN_MESSAGE_MAP(CinvoiceDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CinvoiceDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CinvoiceDlg message handlers

BOOL CinvoiceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// add year list
	m_yearListCtrl.InsertString(0, L"2009");
	m_yearListCtrl.InsertString(1, L"2010");
	m_yearListCtrl.InsertString(2, L"2011");
	m_yearListCtrl.InsertString(3, L"2012");
	// add month list
	m_monthListCtrl.InsertString(0, L"01");
	m_monthListCtrl.InsertString(1, L"02");
	m_monthListCtrl.InsertString(2, L"03");
	m_monthListCtrl.InsertString(3, L"04");
	m_monthListCtrl.InsertString(4, L"05");
	m_monthListCtrl.InsertString(5, L"06");
	m_monthListCtrl.InsertString(6, L"07");
	m_monthListCtrl.InsertString(7, L"08");
	m_monthListCtrl.InsertString(8, L"09");
	m_monthListCtrl.InsertString(9, L"10");
	m_monthListCtrl.InsertString(10, L"11");
	m_monthListCtrl.InsertString(11, L"12");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CinvoiceDlg::OnPaint()
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
HCURSOR CinvoiceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



struct Invoice
{
	CString invNum;
	CString soNum;
	CString custName;
	CString custNum;
	CString date;
	CString currency;
	CString netSale;
	CString freight;
	CString fastTrack;
	CString surcharge;
	CString tax;
	CString other;
	CString cost;
	CString profit;
	CString rate;
	CString invTotal;
};

void CinvoiceDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	// get start and end date
	CString startDate;
	CString endDate;
	startDate = m_year + L"-" + m_month + L"-" + L"01";
	endDate = m_year + L"-" + m_month + L"-";
	if (m_year==L"2012" && m_month==L"02") endDate += L"29";
	else if (m_month==L"01" || m_month==L"03" || m_month==L"05" || m_month==L"07" || m_month==L"08" || m_month==L"10" || m_month==L"12") endDate += L"31";
	else endDate += "30";
	// get record
	vector<Invoice> vecInvoice;
	CString query;
	CDatabase ibm;
	if (0==ibm.OpenEx(L"DSN=cms1;UID=RROSSETTI;PWD=RROSSETTI"))
	{
		AfxMessageBox(L"Failed to open database!");
		return;
	} else
	{
		CRecordset ibm_set(&ibm);
		query = L"select a.dhinv#, a.dhord#, a.dhbnam, a.dhbcs#, a.dhidat, d.dccurr, d.dcttax, c.net_sale-d.dctfrt as sale, d.dctfrt, a.dhtotd, a.dhtoti, a. dhtcst+d.dctfrt as cost, c.net_sale-d.dctfrt-a.dhtcst as profit, (c.net_sale-d.dctfrt-a.dhtcst)*100.0/(c.net_sale-d.dctfrt) as rate from cmsdat.oih as a, (select diinv#, sum(dipric) as net_sale, sum(dimlct) as m_cost, sum(dibrct) as b_cost from cmsdat.oid group by diinv#) as c, cmsdat.ocrh as d where a.dhinv#=c.diinv# and a.dhord#=d.dcord# and a.dhplnt='001' and (a.dhidat>='";
		query += startDate;
		query += L"' and a.dhidat<='";
		query += endDate;
		query += L"') order by a.dhbnam";
		ibm.SetQueryTimeout(9999);
		if (0==ibm_set.Open(CRecordset::forwardOnly, query) || ibm_set.IsEOF())
		{
			AfxMessageBox(L"No Record!");
			return;
		} else
		{
			while (!ibm_set.IsEOF())
			{
				Invoice invoice;
				ibm_set.GetFieldValue(L"DHINV#", invoice.invNum);
				invoice.invNum = invoice.invNum.Trim();
				ibm_set.GetFieldValue(L"DHORD#", invoice.soNum);
				invoice.soNum = invoice.soNum.Trim();
				ibm_set.GetFieldValue(L"DHIDAT", invoice.date);
				invoice.date = invoice.date.Trim();
				ibm_set.GetFieldValue(L"DCCURR", invoice.currency);
				invoice.currency = invoice.currency.Trim();
				ibm_set.GetFieldValue(L"DHBNAM", invoice.custName);
				invoice.custName = invoice.custName.Trim();
				ibm_set.GetFieldValue(L"DHBCS#", invoice.custNum);
				invoice.custNum = invoice.custNum.Trim();
				ibm_set.GetFieldValue(L"SALE", invoice.netSale);
				invoice.netSale = invoice.netSale.Trim();
				ibm_set.GetFieldValue(L"DCTFRT", invoice.freight);
				invoice.freight = invoice.freight.Trim();
				ibm_set.GetFieldValue(L"DHTOTI", invoice.invTotal);
				invoice.invTotal = invoice.invTotal.Trim();
				ibm_set.GetFieldValue(L"DCTTAX", invoice.tax);
				invoice.tax = invoice.tax.Trim();
				ibm_set.GetFieldValue(L"COST", invoice.cost);
				invoice.cost = invoice.cost.Trim();
				ibm_set.GetFieldValue(L"PROFIT", invoice.profit);
				invoice.profit = invoice.profit.Trim();
				ibm_set.GetFieldValue(L"RATE", invoice.rate);
				invoice.rate = invoice.rate.Trim();
				if (invoice.rate.IsEmpty()) invoice.rate = L"0.0";
				// process free dies
				if ((-1!=invoice.invTotal.Find(L"0.00")||invoice.invTotal==L"0") && -1==invoice.profit.Find(L"0.00"))
				{
					invoice.profit = L"-" + invoice.cost;
					invoice.rate = L"0.00";
				}
				vecInvoice.push_back(invoice);
				ibm_set.MoveNext();
			}
		}
		ibm_set.Close();
		// get discount
		CRecordset discount(&ibm);
		for (vector<Invoice>::iterator iter=vecInvoice.begin(); iter!=vecInvoice.end(); iter++)
		{
			double dbFastTrack = 0.0;
			double dbSurcharge = 0.0;
			double dbOther = 0.0;
			query = L"select ffdisc, ffdext from cmsdat.ocrs where fford#=";
			query += iter->soNum;
			if (0!=discount.Open(CRecordset::forwardOnly, query))
			{
				CString code;
				CString value;
				while (!discount.IsEOF())
				{
					discount.GetFieldValue(L"FFDISC", code);
					discount.GetFieldValue(L"FFDEXT", value);
					code = code.Trim();
					value = value.Trim();
					// fast track
					if (L'F' == code[0])
					{
						dbFastTrack += _wtof((LPCWSTR)value);
					} else if (0 == code.Compare(L"S01"))	// steel surcharge
					{
						dbSurcharge += _wtof((LPCWSTR)value);
					} else // other
					{
						dbOther += _wtof((LPCWSTR)value);
					}
					discount.MoveNext();
				}
				iter->fastTrack.Format(L"%.2f", dbFastTrack);
				iter->surcharge.Format(L"%.2f", dbSurcharge);
				iter->other.Format(L"%.2f", dbOther);
			}
			discount.Close();
		}
		ibm.Close();
	}
	// write to temp table
	CDatabase decade;
	if (0==decade.OpenEx(L"DSN=decade;UID=jamie;PWD=jamie"))
	{
		AfxMessageBox(L"Failed to open database!");
		return;
	} else
	{
		CRecordset decade_set(&decade);
		// check profit_temp
		decade_set.Open(CRecordset::forwardOnly, L"select * from dbo.sysobjects where name='invoice_temp'");
		if (!decade_set.IsEOF()) 
		{
			decade_set.Close();
			decade.ExecuteSQL(L"drop table invoice_temp");
		} else
		{
			decade_set.Close();
		}
		decade.ExecuteSQL(L"create table invoice_temp(custName varchar(32), custNum varchar(32), currency varchar(32), date varchar(32), invoiceNum varchar(32), dieSale decimal(18,2), surcharge decimal(18,2), fastTrack decimal(18,2), freight decimal(18,2), GST decimal(18,2), other decimal(18,2), invTotal decimal(18,2))");
		for each(Invoice invoice in vecInvoice)
		{
			query = L"insert into invoice_temp values ('";
			query += invoice.custName + L"', '";
			query += invoice.custNum + L"', '";
			query += invoice.currency + L"', '";
			query += invoice.date + L"', '";
			query += invoice.invNum + L"', '";
			query += invoice.netSale + L"', '";
			query += invoice.surcharge + L"', '";
			query += invoice.fastTrack + L"', '";
			query += invoice.freight + L"', '";
			query += invoice.tax + L"', '";
			query += invoice.other + L"', '";
			query += invoice.invTotal + L"')";
			decade.ExecuteSQL(query);
		}
		// check profit_date_temp
		decade_set.Open(CRecordset::forwardOnly, L"select * from dbo.sysobjects where name='invoice_date_temp'");
		if (!decade_set.IsEOF()) 
		{
			decade_set.Close();
			decade.ExecuteSQL(L"drop table invoice_date_temp");
		} else
		{
			decade_set.Close();
		}
		decade.ExecuteSQL(L"create table invoice_date_temp(plant varchar(32),date varchar(32))");
		query = L"insert into invoice_date_temp values ('ETS','";
		query += m_year;
		query += L"/";
		query += m_month;
		query += L"')";
		decade.ExecuteSQL(query);
		decade.Close();
	}
	ShellExecute(NULL, NULL, L"\\\\10.0.0.6\\shopdata\\development\\tiger\\report\\invoice.rpt", NULL, NULL, SW_SHOW);
	OnOK();
}