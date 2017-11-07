
// budget_salesDlg.h : header file
//

#pragma once
#include "afxwin.h"


// Cbudget_salesDlg dialog
class Cbudget_salesDlg : public CDialogEx
{
// Construction
public:
	Cbudget_salesDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_BUDGET_SALES_DIALOG };

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
	CListBox m_yearCtrl;
	CListBox m_plantCtrl;
	afx_msg void OnBnClickedOk();
	CString m_year;
	CString m_plant;
	void f1();
	void f2();
	void f3();
	void f4();
	void f5();
	void f6();
	void f7();
	void f8();
	void f9();
	void f10();
	void f11();
	void f12();
	void f13();
	void f14();
	void f15();
};
