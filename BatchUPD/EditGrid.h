#if !defined(AFX_EDITGRID_H__5538D775_FCDA_11D5_AA34_00A0CC2D5E32__INCLUDED_)
#define AFX_EDITGRID_H__5538D775_FCDA_11D5_AA34_00A0CC2D5E32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditGrid.h : header file
//

#include "msflexgrid1.h"
#include "EditWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CEditGrid window

class CEditGrid : public CMsflexgrid1
{
    // Construction
public:
    CEditGrid();
    
    // Attributes
public:
    CEditWnd m_edit;
    long m_lBorderWidth;
    long m_lBorderHeight;
    int m_nLogX;
    int m_nLogY;
    
    // Operations
public:
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CEditGrid)
    //}}AFX_VIRTUAL
    
    // Implementation
public:
    virtual ~CEditGrid();
    
    // Generated message map functions
protected:
    virtual void PreSubclassWindow() ;

    afx_msg void OnKeyPressGrid(short FAR* KeyAscii);
    afx_msg void OnDblClickGrid();
    afx_msg void OnUpdateGrid();
    DECLARE_EVENTSINK_MAP()

    //{{AFX_MSG(CEditGrid)
    afx_msg UINT OnGetDlgCode();
    afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITGRID_H__5538D775_FCDA_11D5_AA34_00A0CC2D5E32__INCLUDED_)
