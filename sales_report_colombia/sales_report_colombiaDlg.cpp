
// sales_report_colombiaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "sales_report_colombia.h"
#include "sales_report_colombiaDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Csales_report_colombiaDlg dialog




Csales_report_colombiaDlg::Csales_report_colombiaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Csales_report_colombiaDlg::IDD, pParent)
	, m_year(_T(""))
	, m_month(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Csales_report_colombiaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_YEAR, m_yearListCtrl);
	DDX_LBString(pDX, IDC_LIST_YEAR, m_year);
	DDX_Control(pDX, IDC_LIST_MONTH, m_monthListCtrl);
	DDX_LBString(pDX, IDC_LIST_MONTH, m_month);
}

BEGIN_MESSAGE_MAP(Csales_report_colombiaDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &Csales_report_colombiaDlg::OnBnClickedOk)
    ON_BN_CLICKED(IDC_CUMULATIVE, &Csales_report_colombiaDlg::OnBnClickedCumulative)
END_MESSAGE_MAP()


// Csales_report_colombiaDlg message handlers

BOOL Csales_report_colombiaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// add year list
	m_yearListCtrl.InsertString(0, L"09");
	m_yearListCtrl.InsertString(1, L"10");
	m_yearListCtrl.InsertString(2, L"11");
	m_yearListCtrl.InsertString(3, L"12");
	m_yearListCtrl.InsertString(4, L"13");
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

void Csales_report_colombiaDlg::OnPaint()
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
HCURSOR Csales_report_colombiaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

struct Inv
{
	CString creditNote;
	CString invNum;
	CString soNum;
	CString invDate;
	CString custName;
	CString custTerr;
	CString custId;
	CString ref;
	CString currency;
	CString originalSale;
	CString discount;
	CString fastTrack;
	CString totalSale; // totalSale = originalSale + discount + fastTrack
	CString surcharge;
	CString freight;
	CString scrapSale;
	CString tax101;
	CString tax102;
	CString tax103;
	CString totalInv;
	CString posted;

	Inv()
	{
		creditNote = L"I";
		invNum = L"0";
		soNum = L"0";
		custName = L"";
		custTerr = L"";
		custId = L"";
		ref = L"";
		currency = L"";
		originalSale = L"0.0";
		invDate = L"0000-00-00";
		discount = L"0.0";
		fastTrack = L"0.0";
		totalSale = L"0.0";
		surcharge = L"0.0";
		freight = L"0.0";
		scrapSale = L"0.0";
		tax101 = L"0.0";
		tax102 = L"0.0";
		tax103 = L"0.0";
		totalInv = L"0.0";
		posted = L"";
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

void Csales_report_colombiaDlg::OnBnClickedOk()
{
	vector<Inv> invoice;
	UpdateData(TRUE);
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
		query = L"select dhincr as creditNote, dhinv# as invNum, dhidat as invDate, dhbnam as custName, dhbcs# as custId, dhord# as soNum, dhterr as custTerr, dhcurr as currency, dhpost as posted, dhtoti as total from cmsdat.oih where dhplnt='004' and ((dharyr=" + m_year;
		query += " and dharpr=";
		query += m_month;
		query += ") or (dhidat>='20";
		query += m_year;
		query += "-";
		query += m_month;
		query += "-01' and dhidat<'20";
		query += m_year;
		query += "-";
		CString temp;
		temp.Format(L"%02d", _wtoi(m_month.GetBuffer())+1);
		query += temp;
		query += "-01' and dharyr=0 and dharpr=0)) order by dhinv#";
		if (0==ibm_set.Open(CRecordset::forwardOnly, query) || ibm_set.IsEOF())
		{
			AfxMessageBox(L"No Record!");
			return;
		} else
		{
			while (!ibm_set.IsEOF())
			{
				Inv inv;
				ibm_set.GetFieldValue(L"CREDITNOTE", inv.creditNote);
				inv.creditNote = inv.creditNote.Trim();
				ibm_set.GetFieldValue(L"INVNUM", inv.invNum);
				inv.invNum = inv.invNum.Trim();
				ibm_set.GetFieldValue(L"INVDATE", inv.invDate);
				inv.invDate = inv.invDate.Trim();
				ibm_set.GetFieldValue(L"CUSTNAME", inv.custName);
				inv.custName = inv.custName.Trim();
				ibm_set.GetFieldValue(L"CUSTID", inv.custId);
				inv.custId = inv.custId.Trim();
				ibm_set.GetFieldValue(L"SONUM", inv.soNum);
				inv.soNum = inv.soNum.Trim();
				ibm_set.GetFieldValue(L"CUSTTERR", inv.custTerr);
				inv.custTerr = inv.custTerr.Trim();
				ibm_set.GetFieldValue(L"CURRENCY", inv.currency);
				inv.currency = inv.currency.Trim();
				ibm_set.GetFieldValue(L"POSTED", inv.posted);
				inv.posted = inv.posted.Trim();
				ibm_set.GetFieldValue(L"TOTAL", inv.totalInv);
				inv.posted = inv.posted.Trim();
				invoice.push_back(inv);
				ibm_set.MoveNext();
			}
		}
		ibm_set.Close();
		for (vector<Inv>::iterator iter=invoice.begin(); iter!=invoice.end(); iter++)
		{
			/*
			original sale
			*/
			query = L"select sum(dipric*diqtsp) as originalSale from cmsdat.oid where diglcd='SAL' and diinv#=";
			query += iter->invNum;
			if (0!=ibm_set.Open(CRecordset::forwardOnly, query) && !ibm_set.IsEOF())
			{
				ibm_set.GetFieldValue(L"ORIGINALSALE", iter->originalSale);
				if (iter->originalSale.IsEmpty())
				{
					iter->originalSale = L"0.0";
				}
			}
			ibm_set.Close();
			/*
			ref
			*/
			query = L"select diran as ref from cmsdat.oid where dilin#='1' and diinv#=";
			query += iter->invNum;
			if (0!=ibm_set.Open(CRecordset::forwardOnly, query) && !ibm_set.IsEOF())
			{
				ibm_set.GetFieldValue(L"REF", iter->ref);
			}
			ibm_set.Close();
			/*
			discount
			*/
			query = L"select sum(fldext) as value from cmsdat.ois where flinv#=";
			query += iter->invNum;
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
			/*
			fast track
			*/
			query = L"select sum(fldext) as value from cmsdat.ois where flinv#=";
			query += iter->invNum;
			query += " and fldisc like 'F%'";
			if (0!=ibm_set.Open(CRecordset::forwardOnly, query) && !ibm_set.IsEOF())
			{
				ibm_set.GetFieldValue(L"VALUE", iter->fastTrack);
				if (iter->fastTrack.IsEmpty())
				{
					iter->fastTrack = L"0.0";
				}
			}
			ibm_set.Close();
			/*
			freight
			*/
			query = L"select sum(dipric*diqtsp) as freight from cmsdat.oid where diglcd='FRT' and diinv#=";
			query += iter->invNum;
			if (0!=ibm_set.Open(CRecordset::forwardOnly, query) && !ibm_set.IsEOF())
			{
				ibm_set.GetFieldValue(L"FREIGHT", iter->freight);
				if (iter->freight.IsEmpty())
				{
					iter->freight = L"0.0";
				}
			}
			ibm_set.Close();
			/*
			scrapSale
			*/
			query = L"select sum(dipric*diqtsp) as scr from cmsdat.oid where diglcd='SCR' and diinv#=";
			query += iter->invNum;
			if (0!=ibm_set.Open(CRecordset::forwardOnly, query) && !ibm_set.IsEOF())
			{
				ibm_set.GetFieldValue(L"SCR", iter->scrapSale);
				if (iter->scrapSale.IsEmpty())
				{
					iter->scrapSale = L"0.0";
				}
			}
			ibm_set.Close();
			/*
			surcharge
			*/
			query = L"select sum(fldext) as value from cmsdat.ois where flinv#=";
			query += iter->invNum;
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
			/*
			tax101
			*/
			query = L"select notxam from cmsdat.oix where noinv#=";
			query += iter->invNum;
			query += L" and notxtp=101";
			if (0!=ibm_set.Open(CRecordset::forwardOnly, query) && !ibm_set.IsEOF())
			{
				ibm_set.GetFieldValue(L"NOTXAM", iter->tax101);
				if (iter->tax101.IsEmpty())
				{
					iter->tax101 = L"0.0";
				}
			}
			ibm_set.Close();
			/*
			tax102
			*/
			query = L"select notxam from cmsdat.oix where noinv#=";
			query += iter->invNum;
			query += L" and notxtp=102";
			if (0!=ibm_set.Open(CRecordset::forwardOnly, query) && !ibm_set.IsEOF())
			{
				ibm_set.GetFieldValue(L"NOTXAM", iter->tax102);
				if (iter->tax102.IsEmpty())
				{
					iter->tax102 = L"0.0";
				}
			}
			ibm_set.Close();
			/*
			tax103
			*/
			query = L"select notxam from cmsdat.oix where noinv#=";
			query += iter->invNum;
			query += L" and notxtp=103";
			if (0!=ibm_set.Open(CRecordset::forwardOnly, query) && !ibm_set.IsEOF())
			{
				ibm_set.GetFieldValue(L"NOTXAM", iter->tax103);
				if (iter->tax103.IsEmpty())
				{
					iter->tax103 = L"0.0";
				}
			}
			ibm_set.Close();
			/*
			totalSale
			*/
			double originalSale = _wtof(iter->originalSale.GetBuffer());
			double discount = _wtof(iter->discount.GetBuffer());
			double fastTrack = _wtof(iter->fastTrack.GetBuffer());
			double surcharge = _wtof(iter->surcharge.GetBuffer());
			double freight = _wtof(iter->freight.GetBuffer());
			iter->totalSale.Format(L"%.2f", originalSale+discount+fastTrack+surcharge+freight);
			// reverse credit sign
			if (0 == iter->creditNote.Compare(L"C"))
			{
				ReverseSign(iter->freight);
				ReverseSign(iter->discount);
				ReverseSign(iter->fastTrack);
				ReverseSign(iter->totalSale);
				ReverseSign(iter->originalSale);
				ReverseSign(iter->scrapSale);
				ReverseSign(iter->surcharge);
				ReverseSign(iter->tax101);
				ReverseSign(iter->tax102);
				ReverseSign(iter->tax103);
				ReverseSign(iter->totalInv);
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
			decade_set.Open(CRecordset::forwardOnly, L"select * from dbo.sysobjects where name='sale_report_colombia_temp'");
			if (!decade_set.IsEOF()) 
			{
				decade_set.Close();
				decade.ExecuteSQL(L"drop table sale_report_colombia_temp");
			} else
			{
				decade_set.Close();
			}
			decade.ExecuteSQL(L"create table sale_report_colombia_temp(creditNote char, INV# varchar(32), INVDATE varchar(32), SONUM# varchar(32), custName varchar(32), custId varchar(32), custTerr varchar(32), REF varchar(32), currency varchar(32), originalSALE decimal(18,2), discount decimal(18,2), fastTrack decimal(18,2), totalSale decimal(18,2), SURCHARGE decimal(18,2), FREIGHT decimal(18,2), scrapSale decimal(18,2), \"RET 3.5%\" decimal(18,2), \"IVA RET 8%\" decimal(18,2), \"IVA 16%\" decimal(18,2), TOTALinv decimal(18,2), POST char)");
			for each(Inv inv in invoice)
			{
				query = L"insert into sale_report_colombia_temp values ('";
				query += inv.creditNote + L"', '";
				query += inv.invNum + L"', '";
				query += inv.invDate + L"', '";
				query += inv.soNum + L"', '";
				query += inv.custName + L"', '";
				query += inv.custId + L"', '";
				query += inv.custTerr + L"', '";
				query += inv.ref + L"', '";
				query += inv.currency + L"', '";
				query += inv.originalSale + L"', '";
				query += inv.discount + L"', '";
				query += inv.fastTrack + L"', '";
				query += inv.totalSale + L"', '";
				query += inv.surcharge + L"', '";
				query += inv.freight + L"', '";
				query += inv.scrapSale + L"', '";
				query += inv.tax103 + L"', '";
				query += inv.tax102 + L"', '";
				query += inv.tax101 + L"', '";
				query += inv.totalInv + L"', '";
				query += inv.posted + L"')";
				decade.ExecuteSQL(query);
			}
		}
	}
	ShellExecute(NULL, NULL, L"D:\\\\ERP_Workspace\\\\ERP\\\\Documents\\\\sales_report_colombia.rpt", NULL, NULL, SW_SHOW);
}

void Csales_report_colombiaDlg::OnBnClickedCumulative()
{
	vector<Inv> invoice;
	UpdateData(TRUE);
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
		/*
		creditNote
		invNum
		invDate
		soNum
		custName
		custId
		custTerr
		currency
		posted
		*/
		CRecordset ibm_set(&ibm);
		query = L"select dhincr as creditNote, dhinv# as invNum, dhidat as invDate, dhbnam as custName, dhbcs# as custId, dhord# as soNum, dhterr as custTerr, dhcurr as currency, dhpost as posted, dhtoti as total from cmsdat.oih where dhplnt='004' and ((dharyr=year(current timestamp)-2000 and dharpr=month(current timestamp)) or (dhidat>='2013-04-01' and dhidat<=date(current timestamp) and dharyr=0 and dharpr=0)) order by dhinv#";
		if (0==ibm_set.Open(CRecordset::forwardOnly, query) || ibm_set.IsEOF())
		{
			AfxMessageBox(L"No Record!");
			return;
		} else
		{
			while (!ibm_set.IsEOF())
			{
				Inv inv;
				ibm_set.GetFieldValue(L"CREDITNOTE", inv.creditNote);
				inv.creditNote = inv.creditNote.Trim();
				ibm_set.GetFieldValue(L"INVNUM", inv.invNum);
				inv.invNum = inv.invNum.Trim();
				ibm_set.GetFieldValue(L"INVDATE", inv.invDate);
				inv.invDate = inv.invDate.Trim();
				ibm_set.GetFieldValue(L"CUSTNAME", inv.custName);
				inv.custName = inv.custName.Trim();
				ibm_set.GetFieldValue(L"CUSTID", inv.custId);
				inv.custId = inv.custId.Trim();
				ibm_set.GetFieldValue(L"SONUM", inv.soNum);
				inv.soNum = inv.soNum.Trim();
				ibm_set.GetFieldValue(L"CUSTTERR", inv.custTerr);
				inv.custTerr = inv.custTerr.Trim();
				ibm_set.GetFieldValue(L"CURRENCY", inv.currency);
				inv.currency = inv.currency.Trim();
				ibm_set.GetFieldValue(L"POSTED", inv.posted);
				inv.posted = inv.posted.Trim();
				ibm_set.GetFieldValue(L"TOTAL", inv.totalInv);
				inv.posted = inv.posted.Trim();
				invoice.push_back(inv);
				ibm_set.MoveNext();
			}
		}
		ibm_set.Close();
		for (vector<Inv>::iterator iter=invoice.begin(); iter!=invoice.end(); iter++)
		{
			/*
			original sale
			*/
			query = L"select sum(dipric*diqtsp) as originalSale from cmsdat.oid where diglcd='SAL' and diinv#=";
			query += iter->invNum;
			if (0!=ibm_set.Open(CRecordset::forwardOnly, query) && !ibm_set.IsEOF())
			{
				ibm_set.GetFieldValue(L"ORIGINALSALE", iter->originalSale);
				if (iter->originalSale.IsEmpty())
				{
					iter->originalSale = L"0.0";
				}
			}
			ibm_set.Close();
			/*
			ref
			*/
			query = L"select diran as ref from cmsdat.oid where dilin#='1' and diinv#=";
			query += iter->invNum;
			if (0!=ibm_set.Open(CRecordset::forwardOnly, query) && !ibm_set.IsEOF())
			{
				ibm_set.GetFieldValue(L"REF", iter->ref);
			}
			ibm_set.Close();
			/*
			discount
			*/
			query = L"select sum(fldext) as value from cmsdat.ois where flinv#=";
			query += iter->invNum;
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
			/*
			fast track
			*/
			query = L"select sum(fldext) as value from cmsdat.ois where flinv#=";
			query += iter->invNum;
			query += " and fldisc like 'F%'";
			if (0!=ibm_set.Open(CRecordset::forwardOnly, query) && !ibm_set.IsEOF())
			{
				ibm_set.GetFieldValue(L"VALUE", iter->fastTrack);
				if (iter->fastTrack.IsEmpty())
				{
					iter->fastTrack = L"0.0";
				}
			}
			ibm_set.Close();
			/*
			freight
			*/
			query = L"select sum(dipric*diqtsp) as freight from cmsdat.oid where diglcd='FRT' and diinv#=";
			query += iter->invNum;
			if (0!=ibm_set.Open(CRecordset::forwardOnly, query) && !ibm_set.IsEOF())
			{
				ibm_set.GetFieldValue(L"FREIGHT", iter->freight);
				if (iter->freight.IsEmpty())
				{
					iter->freight = L"0.0";
				}
			}
			ibm_set.Close();
			/*
			scrapSale
			*/
			query = L"select sum(dipric*diqtsp) as scr from cmsdat.oid where diglcd='SCR' and diinv#=";
			query += iter->invNum;
			if (0!=ibm_set.Open(CRecordset::forwardOnly, query) && !ibm_set.IsEOF())
			{
				ibm_set.GetFieldValue(L"SCR", iter->scrapSale);
				if (iter->scrapSale.IsEmpty())
				{
					iter->scrapSale = L"0.0";
				}
			}
			ibm_set.Close();
			/*
			surcharge
			*/
			query = L"select sum(fldext) as value from cmsdat.ois where flinv#=";
			query += iter->invNum;
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
			/*
			tax101
			*/
			query = L"select notxam from cmsdat.oix where noinv#=";
			query += iter->invNum;
			query += L" and notxtp=101";
			if (0!=ibm_set.Open(CRecordset::forwardOnly, query) && !ibm_set.IsEOF())
			{
				ibm_set.GetFieldValue(L"NOTXAM", iter->tax101);
				if (iter->tax101.IsEmpty())
				{
					iter->tax101 = L"0.0";
				}
			}
			ibm_set.Close();
			/*
			tax102
			*/
			query = L"select notxam from cmsdat.oix where noinv#=";
			query += iter->invNum;
			query += L" and notxtp=102";
			if (0!=ibm_set.Open(CRecordset::forwardOnly, query) && !ibm_set.IsEOF())
			{
				ibm_set.GetFieldValue(L"NOTXAM", iter->tax102);
				if (iter->tax102.IsEmpty())
				{
					iter->tax102 = L"0.0";
				}
			}
			ibm_set.Close();
			/*
			tax103
			*/
			query = L"select notxam from cmsdat.oix where noinv#=";
			query += iter->invNum;
			query += L" and notxtp=103";
			if (0!=ibm_set.Open(CRecordset::forwardOnly, query) && !ibm_set.IsEOF())
			{
				ibm_set.GetFieldValue(L"NOTXAM", iter->tax103);
				if (iter->tax103.IsEmpty())
				{
					iter->tax103 = L"0.0";
				}
			}
			ibm_set.Close();
			/*
			totalSale
			*/
			double originalSale = _wtof(iter->originalSale.GetBuffer());
			double discount = _wtof(iter->discount.GetBuffer());
			double fastTrack = _wtof(iter->fastTrack.GetBuffer());
			double surcharge = _wtof(iter->surcharge.GetBuffer());
			double freight = _wtof(iter->freight.GetBuffer());
			iter->totalSale.Format(L"%.2f", originalSale+discount+fastTrack+surcharge+freight);
			// reverse credit sign
			if (0 == iter->creditNote.Compare(L"C"))
			{
				ReverseSign(iter->freight);
				ReverseSign(iter->discount);
				ReverseSign(iter->fastTrack);
				ReverseSign(iter->totalSale);
				ReverseSign(iter->originalSale);
				ReverseSign(iter->scrapSale);
				ReverseSign(iter->surcharge);
				ReverseSign(iter->tax101);
				ReverseSign(iter->tax102);
				ReverseSign(iter->tax103);
				ReverseSign(iter->totalInv);
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
			decade_set.Open(CRecordset::forwardOnly, L"select * from dbo.sysobjects where name='sale_report_colombia_temp'");
			if (!decade_set.IsEOF()) 
			{
				decade_set.Close();
				decade.ExecuteSQL(L"drop table sale_report_colombia_temp");
			} else
			{
				decade_set.Close();
			}
			decade.ExecuteSQL(L"create table sale_report_colombia_temp(creditNote char, INV# varchar(32), INVDATE varchar(32), SONUM# varchar(32), custName varchar(32), custId varchar(32), custTerr varchar(32), REF varchar(32), currency varchar(32), originalSALE decimal(18,2), discount decimal(18,2), fastTrack decimal(18,2), totalSale decimal(18,2), SURCHARGE decimal(18,2), FREIGHT decimal(18,2), scrapSale decimal(18,2), \"RET 3.5%\" decimal(18,2), \"IVA RET 8%\" decimal(18,2), \"IVA 16%\" decimal(18,2), TOTALinv decimal(18,2), POST char)");
			for each(Inv inv in invoice)
			{
				query = L"insert into sale_report_colombia_temp values ('";
				query += inv.creditNote + L"', '";
				query += inv.invNum + L"', '";
				query += inv.invDate + L"', '";
				query += inv.soNum + L"', '";
				query += inv.custName + L"', '";
				query += inv.custId + L"', '";
				query += inv.custTerr + L"', '";
				query += inv.ref + L"', '";
				query += inv.currency + L"', '";
				query += inv.originalSale + L"', '";
				query += inv.discount + L"', '";
				query += inv.fastTrack + L"', '";
				query += inv.totalSale + L"', '";
				query += inv.surcharge + L"', '";
				query += inv.freight + L"', '";
				query += inv.scrapSale + L"', '";
				query += inv.tax103 + L"', '";
				query += inv.tax102 + L"', '";
				query += inv.tax101 + L"', '";
				query += inv.totalInv + L"', '";
				query += inv.posted + L"')";
				decade.ExecuteSQL(query);
			}
		}
	}
	ShellExecute(NULL, NULL, L"D:\\\\ERP_Workspace\\\\ERP\\\\Documents\\\\sales_report_colombia.rpt", NULL, NULL, SW_SHOW);
}