
// invoiceDlg.h : header file
//

#pragma once


// CinvoiceDlg dialog
class CinvoiceDlg : public CDialogEx
{
// Construction
public:
	CinvoiceDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_INVOICE_DIALOG };

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
	CListBox m_yearListCtrl;
	CListBox m_monthListCtrl;
	CString m_month;
	CString m_year;
};
