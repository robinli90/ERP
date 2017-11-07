
// sales_report_michiganDlg.h : header file
//

#pragma once
#include "afxwin.h"


// Csales_report_michiganDlg dialog
class Csales_report_michiganDlg : public CDialogEx
{
// Construction
public:
	Csales_report_michiganDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SALES_REPORT_MICHIGAN_DIALOG };

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
    CString m_year;
    CString m_month;
    CListBox m_yearListCtrl;
    CListBox m_monthListCtrl;
    afx_msg void OnBnClickedOk();
};
