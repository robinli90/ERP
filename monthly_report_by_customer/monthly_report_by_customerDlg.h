
// monthly_report_by_customerDlg.h : header file
//

#pragma once


// Cmonthly_report_by_customerDlg dialog
class Cmonthly_report_by_customerDlg : public CDialogEx
{
// Construction
public:
	Cmonthly_report_by_customerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MONTHLY_REPORT_BY_CUSTOMER_DIALOG };

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
	afx_msg void OnBnClickedOk();
};
