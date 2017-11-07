#if !defined(AFX_TASKTYPEDLG_H__BA4EFEAC_4693_439F_B5A3_F0C3CF200F71__INCLUDED_)
#define AFX_TASKTYPEDLG_H__BA4EFEAC_4693_439F_B5A3_F0C3CF200F71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TaskTypeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTaskTypeDlg dialog

class CTaskTypeDlg : public CDialog
{
    // Construction
public:

    CFont m_font ;

    CString usermsg ; 
    CString rettask ; 
    CString b1desc, b2desc, b3desc ;
    CString b1task, b2task, b3task ;
    
    CTaskTypeDlg(CWnd* pParent = NULL);   // standard constructor
    
    // Dialog Data
    //{{AFX_DATA(CTaskTypeDlg)
    enum { IDD = IDD_TASKTYPE_DLG };
    CEdit	m_msg;
    CButton	m_button3;
    CButton	m_button2;
    CButton	m_button1;
    //}}AFX_DATA
    
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CTaskTypeDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL
    
    // Implementation
protected:
    
    // Generated message map functions
    //{{AFX_MSG(CTaskTypeDlg)
    afx_msg void OnTask1But();
    afx_msg void OnTask2But();
    afx_msg void OnTask3But();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TASKTYPEDLG_H__BA4EFEAC_4693_439F_B5A3_F0C3CF200F71__INCLUDED_)
