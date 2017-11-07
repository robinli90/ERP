
// sales_report_texasDlg.cpp : implementation file
//

#include "stdafx.h"
#include "sales_report_texas.h"
#include "sales_report_texasDlg.h"
#include "afxdialogex.h"
#include <afxdb.h>
#include <vector>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;

// Csales_report_texasDlg dialog




Csales_report_texasDlg::Csales_report_texasDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Csales_report_texasDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Csales_report_texasDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Csales_report_texasDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDOK, &Csales_report_texasDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_LAST_MONTH, &Csales_report_texasDlg::OnBnClickedButtonLastMonth)
END_MESSAGE_MAP()


// Csales_report_texasDlg message handlers

BOOL Csales_report_texasDlg::OnInitDialog()
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

void Csales_report_texasDlg::OnPaint()
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
HCURSOR Csales_report_texasDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

struct Inv
{
	CString credit_note;
    CString sonum;
	CString num;
	CString date;
	CString cust_name;
	CString cust_id;
    CString cust_terr;
	CString ref;
	CString sale;
	CString currency;
	CString fast_track;
	CString discount;
	CString surcharge;
	CString freight;
	CString tax;
	CString total;
	CString post;

	Inv()
	{
		credit_note = L"I";
        sonum = L"0";
		sale = L"0.0";
		date = L"0000-00-00";
		surcharge = L"0.0";
		freight = L"0.0";
		tax = L"0.0";
		total = L"0.0";
		fast_track = L"0.0";
		discount = L"0.0";
	}
};

void ReverseSign(CString &str)
{
	if (str[0] == L'-')
	{
		str.Delete(0, 1);
	} else if (str[0]!=L'0' || fabs(_wtof(str.GetString()))>0.000001)
	{
		str.Insert(0, L'-');
	}
}

void Csales_report_texasDlg::OnBnClickedOk()
{
    CString year = L"13";
    CString month = L"07";

	vector<Inv> invoice;
	UpdateData(TRUE);
	// get record
	CString query;
	CDatabase ibm;
	ibm.SetQueryTimeout(0);
	if (0==ibm.OpenEx(L"DSN=cms1;UID=JXU;PWD=qwpo555"))
	//if (0==ibm.OpenEx(L"DSN=cms1;UID=ZWANG;PWD=ZWANG"))
	{
		AfxMessageBox(L"Failed to open database!");
		return;
	} else
	{
		// get main data
		CRecordset ibm_set(&ibm);
		query = L"select dhincr as cn, dhinv# as inv, dhcurr as currency, dhidat as date, dhbnam as customer_name, dhord# as soNum, dhbcs# as customer_id, dhterr as custTerr, dhtoti as invoice, dhpost as posted from cmsdat.oih where dhplnt='005' and (dharyr=";
		query += year;
		query += L" and dharpr=";
		query += month;
		query += L" or (dhidat>='2013-04-01' and dhidat<=date(current timestamp) and dharyr=0 and dharpr=0)) order by dhinv#";
		if (0==ibm_set.Open(CRecordset::forwardOnly, query) || ibm_set.IsEOF())
		{
			AfxMessageBox(L"No Record!");
			return;
		} else
		{
			while (!ibm_set.IsEOF())
			{
				Inv inv;
				ibm_set.GetFieldValue(L"INV", inv.num);
				inv.num = inv.num.Trim();
				ibm_set.GetFieldValue(L"DATE", inv.date);
				inv.date = inv.date.Trim();
				ibm_set.GetFieldValue(L"CURRENCY", inv.currency);
				inv.currency = inv.currency.Trim();
				ibm_set.GetFieldValue(L"CUSTOMER_NAME", inv.cust_name);
				inv.cust_name = inv.cust_name.Trim();
				ibm_set.GetFieldValue(L"CUSTOMER_ID", inv.cust_id);
				inv.cust_id = inv.cust_id.Trim();
				ibm_set.GetFieldValue(L"CN", inv.credit_note);
				inv.credit_note = inv.credit_note.Trim();
				ibm_set.GetFieldValue(L"INVOICE", inv.total);
				if (inv.total.IsEmpty())
				{
					inv.total = L"0.0";
				}
                ibm_set.GetFieldValue(L"SONUM", inv.sonum);
                inv.sonum = inv.sonum.Trim();
                ibm_set.GetFieldValue(L"CUSTTERR", inv.cust_terr);
                inv.cust_terr = inv.cust_terr.Trim();
				ibm_set.GetFieldValue(L"POSTED", inv.post);
				inv.post = inv.post.Trim();
				invoice.push_back(inv);
				ibm_set.MoveNext();
			}
		}
		ibm_set.Close();
		// get tax and sales
		for (vector<Inv>::iterator iter=invoice.begin(); iter!=invoice.end(); iter++)
		{
			// sale
			query = L"select sum(dipric*diqtsp) as sale from cmsdat.oid where diglcd='SAL' and diinv#=";
			query += iter->num;
			if (0!=ibm_set.Open(CRecordset::forwardOnly, query) && !ibm_set.IsEOF())
			{
				ibm_set.GetFieldValue(L"SALE", iter->sale);
				if (iter->sale.IsEmpty())
				{
					iter->sale = L"0.0";
				}
			}
			ibm_set.Close();
			// discount
			query = L"select sum(fldext) as value from cmsdat.ois where flinv#=";
			query += iter->num;
			query += " and (fldisc like 'D%' or fldisc like 'M%')";
			if (0!=ibm_set.Open(CRecordset::forwardOnly, query) && !ibm_set.IsEOF())
			{
				ibm_set.GetFieldValue(L"VALUE", iter->discount);
				if (iter->discount.IsEmpty())
				{
					iter->discount = L"0.0";
				}
			}
			ibm_set.Close();
			// fast track
			query = L"select sum(fldext) as value from cmsdat.ois where flinv#=";
			query += iter->num;
			query += " and fldisc like 'F%'";
			if (0!=ibm_set.Open(CRecordset::forwardOnly, query) && !ibm_set.IsEOF())
			{
				ibm_set.GetFieldValue(L"VALUE", iter->fast_track);
				if (iter->fast_track.IsEmpty())
				{
					iter->fast_track = L"0.0";
				}
			}
			ibm_set.Close();
			// surcharge
			query = L"select sum(fldext) as value from cmsdat.ois where flinv#=";
			query += iter->num;
			query += " and (fldisc like 'S%' or fldisc like 'P%')";
			if (0!=ibm_set.Open(CRecordset::forwardOnly, query) && !ibm_set.IsEOF())
			{
				ibm_set.GetFieldValue(L"VALUE", iter->surcharge);
				if (iter->surcharge.IsEmpty())
				{
					iter->surcharge = L"0.0";
				}
			}
			ibm_set.Close();
			// freight
			query = L"select sum(dipric*diqtsp) as frt from cmsdat.oid where diglcd='FRT' and diinv#=";
			query += iter->num;
			if (0!=ibm_set.Open(CRecordset::forwardOnly, query) && !ibm_set.IsEOF())
			{
				ibm_set.GetFieldValue(L"FRT", iter->freight);
				if (iter->freight.IsEmpty())
				{
					iter->freight = L"0.0";
				}
			}
			ibm_set.Close();
			// tax
			query = L"select notxam from cmsdat.oix where noinv#=";
			query += iter->num;
			if (0!=ibm_set.Open(CRecordset::forwardOnly, query) && !ibm_set.IsEOF())
			{
				ibm_set.GetFieldValue(L"NOTXAM", iter->tax);
				if (iter->tax.IsEmpty())
				{
					iter->tax = L"0.0";
				}
			}
			ibm_set.Close();
			if (0 == iter->credit_note.Compare(L"C"))
			{
				ReverseSign(iter->freight);
				ReverseSign(iter->sale);
				ReverseSign(iter->surcharge);
				ReverseSign(iter->tax);
				ReverseSign(iter->total);
			}
		}
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
		decade_set.Open(CRecordset::forwardOnly, L"select * from dbo.sysobjects where name='sale_report_texas_temp'");
		if (!decade_set.IsEOF()) 
		{
			decade_set.Close();
			decade.ExecuteSQL(L"drop table sale_report_texas_temp");
		} else
		{
			decade_set.Close();
		}
		decade.ExecuteSQL(L"create table sale_report_texas_temp(CREDIT_NOTE char, INVOICE# varchar(32), DATE varchar(32), SONUM varchar(32), CUST_NAME varchar(32), CUST_ID varchar(32), custTerr varchar(32), CURRENCY varchar(32), SALE decimal(18,2), DISCOUNT decimal(18,2), FAST_TRACK decimal(18,2), SURCHARGE decimal(18,2), FREIGHT decimal(18,2), TAX decimal(18,2), TOTAL decimal(18,2), POST char)");
		for each(Inv inv in invoice)
		{
			query = L"insert into sale_report_texas_temp values ('";
			query += inv.credit_note + L"', '";
			query += inv.num + L"', '";
			query += inv.date + L"', '";
			query += inv.sonum + L"', '";
			query += inv.cust_name + L"', '";
			query += inv.cust_id + L"', '";
            query += inv.cust_terr + L"', '";
            query += inv.currency + L"', '";
			query += inv.sale + L"', '";
			query += inv.discount + L"', '";
			query += inv.fast_track + L"', '";
			query += inv.surcharge + L"', '";
			query += inv.freight + L"', '";
			query += inv.tax + L"', '";
			query += inv.total + L"', '";
			query += inv.post + L"')";
			decade.ExecuteSQL(query);
		}
	}
}

void Csales_report_texasDlg::OnBnClickedButtonLastMonth()
{
    CString year = L"13";
    CString month = L"06";

	vector<Inv> invoice;
	UpdateData(TRUE);
	// get record
	CString query;
	CDatabase ibm;
	ibm.SetQueryTimeout(0);
	if (0==ibm.OpenEx(L"DSN=cms1;UID=JXU;PWD=qwpo555"))
	//if (0==ibm.OpenEx(L"DSN=cms1;UID=ZWANG;PWD=ZWANG"))
	{
		AfxMessageBox(L"Failed to open database!");
		return;
	} else
	{
		// get main data
		CRecordset ibm_set(&ibm);
		query = L"select dhincr as cn, dhinv# as inv, dhcurr as currency, dhidat as date, dhbnam as customer_name, dhord# as soNum, dhbcs# as customer_id, dhterr as custTerr, dhtoti as invoice, dhpost as posted from cmsdat.oih where dhplnt='005' and (dharyr=";
		query += year;
		query += L" and dharpr=";
		query += month;
		query += L" or (dhidat>='2013-03-01' and dhidat<='2013-03-31' and dharyr=0 and dharpr=0)) order by dhinv#";
		if (0==ibm_set.Open(CRecordset::forwardOnly, query) || ibm_set.IsEOF())
		{
			AfxMessageBox(L"No Record!");
			return;
		} else
		{
			while (!ibm_set.IsEOF())
			{
				Inv inv;
				ibm_set.GetFieldValue(L"INV", inv.num);
				inv.num = inv.num.Trim();
				ibm_set.GetFieldValue(L"DATE", inv.date);
				inv.date = inv.date.Trim();
				ibm_set.GetFieldValue(L"CURRENCY", inv.currency);
				inv.currency = inv.currency.Trim();
				ibm_set.GetFieldValue(L"CUSTOMER_NAME", inv.cust_name);
				inv.cust_name = inv.cust_name.Trim();
				ibm_set.GetFieldValue(L"CUSTOMER_ID", inv.cust_id);
				inv.cust_id = inv.cust_id.Trim();
				ibm_set.GetFieldValue(L"CN", inv.credit_note);
				inv.credit_note = inv.credit_note.Trim();
				ibm_set.GetFieldValue(L"INVOICE", inv.total);
				if (inv.total.IsEmpty())
				{
					inv.total = L"0.0";
				}
                ibm_set.GetFieldValue(L"SONUM", inv.sonum);
                inv.sonum = inv.sonum.Trim();
                ibm_set.GetFieldValue(L"CUSTTERR", inv.cust_terr);
                inv.cust_terr = inv.cust_terr.Trim();
				ibm_set.GetFieldValue(L"POSTED", inv.post);
				inv.post = inv.post.Trim();
				invoice.push_back(inv);
				ibm_set.MoveNext();
			}
		}
		ibm_set.Close();
		// get tax and sales
		for (vector<Inv>::iterator iter=invoice.begin(); iter!=invoice.end(); iter++)
		{
			// sale
			query = L"select sum(dipric*diqtsp) as sale from cmsdat.oid where diglcd='SAL' and diinv#=";
			query += iter->num;
			if (0!=ibm_set.Open(CRecordset::forwardOnly, query) && !ibm_set.IsEOF())
			{
				ibm_set.GetFieldValue(L"SALE", iter->sale);
				if (iter->sale.IsEmpty())
				{
					iter->sale = L"0.0";
				}
			}
			ibm_set.Close();
			// discount
			query = L"select sum(fldext) as value from cmsdat.ois where flinv#=";
			query += iter->num;
			query += " and (fldisc like 'D%' or fldisc like 'M%')";
			if (0!=ibm_set.Open(CRecordset::forwardOnly, query) && !ibm_set.IsEOF())
			{
				ibm_set.GetFieldValue(L"VALUE", iter->discount);
				if (iter->discount.IsEmpty())
				{
					iter->discount = L"0.0";
				}
			}
			ibm_set.Close();
			// fast track
			query = L"select sum(fldext) as value from cmsdat.ois where flinv#=";
			query += iter->num;
			query += " and fldisc like 'F%'";
			if (0!=ibm_set.Open(CRecordset::forwardOnly, query) && !ibm_set.IsEOF())
			{
				ibm_set.GetFieldValue(L"VALUE", iter->fast_track);
				if (iter->fast_track.IsEmpty())
				{
					iter->fast_track = L"0.0";
				}
			}
			ibm_set.Close();
			// surcharge
			query = L"select sum(fldext) as value from cmsdat.ois where flinv#=";
			query += iter->num;
			query += " and (fldisc like 'S%' or fldisc like 'P%')";
			if (0!=ibm_set.Open(CRecordset::forwardOnly, query) && !ibm_set.IsEOF())
			{
				ibm_set.GetFieldValue(L"VALUE", iter->surcharge);
				if (iter->surcharge.IsEmpty())
				{
					iter->surcharge = L"0.0";
				}
			}
			ibm_set.Close();
			// freight
			query = L"select sum(dipric*diqtsp) as frt from cmsdat.oid where diglcd='FRT' and diinv#=";
			query += iter->num;
			if (0!=ibm_set.Open(CRecordset::forwardOnly, query) && !ibm_set.IsEOF())
			{
				ibm_set.GetFieldValue(L"FRT", iter->freight);
				if (iter->freight.IsEmpty())
				{
					iter->freight = L"0.0";
				}
			}
			ibm_set.Close();
			// tax
			query = L"select notxam from cmsdat.oix where noinv#=";
			query += iter->num;
			if (0!=ibm_set.Open(CRecordset::forwardOnly, query) && !ibm_set.IsEOF())
			{
				ibm_set.GetFieldValue(L"NOTXAM", iter->tax);
				if (iter->tax.IsEmpty())
				{
					iter->tax = L"0.0";
				}
			}
			ibm_set.Close();
			if (0 == iter->credit_note.Compare(L"C"))
			{
				ReverseSign(iter->freight);
				ReverseSign(iter->sale);
				ReverseSign(iter->surcharge);
				ReverseSign(iter->tax);
				ReverseSign(iter->total);
			}
		}
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
		decade_set.Open(CRecordset::forwardOnly, L"select * from dbo.sysobjects where name='sale_report_texas_temp'");
		if (!decade_set.IsEOF()) 
		{
			decade_set.Close();
			decade.ExecuteSQL(L"drop table sale_report_texas_temp");
		} else
		{
			decade_set.Close();
		}
		decade.ExecuteSQL(L"create table sale_report_texas_temp(CREDIT_NOTE char, INVOICE# varchar(32), DATE varchar(32), SONUM varchar(32), CUST_NAME varchar(32), CUST_ID varchar(32), custTerr varchar(32), CURRENCY varchar(32), SALE decimal(18,2), DISCOUNT decimal(18,2), FAST_TRACK decimal(18,2), SURCHARGE decimal(18,2), FREIGHT decimal(18,2), TAX decimal(18,2), TOTAL decimal(18,2), POST char)");
		for each(Inv inv in invoice)
		{
			query = L"insert into sale_report_texas_temp values ('";
			query += inv.credit_note + L"', '";
			query += inv.num + L"', '";
			query += inv.date + L"', '";
			query += inv.sonum + L"', '";
			query += inv.cust_name + L"', '";
			query += inv.cust_id + L"', '";
            query += inv.cust_terr + L"', '";
            query += inv.currency + L"', '";
			query += inv.sale + L"', '";
			query += inv.discount + L"', '";
			query += inv.fast_track + L"', '";
			query += inv.surcharge + L"', '";
			query += inv.freight + L"', '";
			query += inv.tax + L"', '";
			query += inv.total + L"', '";
			query += inv.post + L"')";
			decade.ExecuteSQL(query);
		}
	}
}
