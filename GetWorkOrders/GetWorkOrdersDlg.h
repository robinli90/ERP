// GetWorkOrdersDlg.h : header file
//

#pragma once


#include <CSStdlibs/cslib.h>
#include <libSQL/SQLDatabase.h>
#include <libSQL/SQLRecordset.h>
#include <libCMS/CMSBOMRTE.h>



// CGetWorkOrdersDlg dialog
class CGetWorkOrdersDlg : public CDialog
{
    // Construction
public:
    CGetWorkOrdersDlg(CWnd* pParent = NULL);	// standard constructor

    // Dialog Data
    enum { IDD = IDD_GETWORKORDERS_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


    // Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButton1();
    CString m_strSONUM;
    CString m_strMsg;
};
