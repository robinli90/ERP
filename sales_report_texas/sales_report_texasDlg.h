
// sales_report_texasDlg.h : header file
//

#pragma once


// Csales_report_texasDlg dialog
class Csales_report_texasDlg : public CDialogEx
{
// Construction
public:
	Csales_report_texasDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SALES_REPORT_TEXAS_DIALOG };

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
	afx_msg void OnBnClickedButtonLastMonth();
};
