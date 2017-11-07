
// CrossCheckDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include <vector>
#include <afxdb.h>

using namespace std;


// CCrossCheckDlg dialog
class CCrossCheckDlg : public CDialogEx
{
// Construction
public:
	CCrossCheckDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CROSSCHECK_DIALOG };

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
	CString m_input;
	CString m_so;
	CString m_inv;
	vector<CString> m_wo_vec;
	afx_msg void OnBnClickedCheck();
	CListBox m_resultCtrl;
};
