
// sales_report_colombiaDlg.h : header file
//

#pragma once
#include "afxwin.h"


// Csales_report_colombiaDlg dialog
class Csales_report_colombiaDlg : public CDialogEx
{
// Construction
public:
	Csales_report_colombiaDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SALES_REPORT_COLOMBIA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_yearListCtrl;
	CString m_year;
	CListBox m_monthListCtrl;
	CString m_month;
	afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCumulative();
};
