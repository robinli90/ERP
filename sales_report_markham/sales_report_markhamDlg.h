
// sales_report_markhamDlg.h : header file
//

#pragma once
#include "afxwin.h"


// Csales_report_markhamDlg dialog
class Csales_report_markhamDlg : public CDialogEx
{
// Construction
public:
	Csales_report_markhamDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SALES_REPORT_MARKHAM_DIALOG };

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
};
