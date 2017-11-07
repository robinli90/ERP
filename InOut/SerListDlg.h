#if !defined(AFX_SERLISTDLG_H__5E135BC6_6ADE_436D_92C5_E035748115D6__INCLUDED_)
#define AFX_SERLISTDLG_H__5E135BC6_6ADE_436D_92C5_E035748115D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SerListDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSerListDlg dialog

class CSerListDlg : public CDialog
{
// Construction
public:
	CSerListDlg(CWnd* pParent = NULL);   // standard constructor

        SerialDataVec *pservec ;
        csString sersel ; 
// Dialog Data
	//{{AFX_DATA(CSerListDlg)
	enum { IDD = IDD_SERLISTDLG };
	CListBox	m_serNum;
	CString	m_mtl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSerListDlg)
	afx_msg void OnDblclkSerlist();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERLISTDLG_H__5E135BC6_6ADE_436D_92C5_E035748115D6__INCLUDED_)
