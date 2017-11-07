#if !defined(AFX_ERRORDLG_H__E9ED78A4_27A7_46BD_813D_08F3D419D9C7__INCLUDED_)
#define AFX_ERRORDLG_H__E9ED78A4_27A7_46BD_813D_08F3D419D9C7__INCLUDED_


#include "Disable4786.h"
#include <vector>

using namespace std ; 

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ErrorDlg.h : header file
//

struct ListMapRec
{
    CString noteid ; 
    CString subid ; 
    CString desctxt ; 
    CString bmapname ;
    double perfind ; 
    int bmapidx ; 
} ;

typedef ListMapRec* ListMapRecPtr ;


class BitMapRec
{
public:
    CString name ; 
    HBITMAP hbmap ; 
    CBitmap bmap ; 

    BitMapRec() ; 
    BitMapRec &operator=(const BitMapRec &bmr) ;
    BitMapRec(const BitMapRec &bmr) ;
    // BitMapRec &operator=(const BitMapRec &bmr) ;
    int operator==(BitMapRec &b) ;
    int operator<(BitMapRec &b) ;
} ;


typedef vector<BitMapRec> BitMapVec ; 
typedef vector<BitMapRec>::iterator BitMapVecItr ; 


/////////////////////////////////////////////////////////////////////////////
// CErrorDlg dialog

class CErrorDlg : public CDialog
{
    // Construction
public:
    CErrorDlg(CWnd* pParent = NULL) ;   // standard constructor
    ~CErrorDlg() ; 

    BitMapVec bmvec ; 

    CInOutDlg *piod ;

    HBITMAP hblankimg ; 

    // Allocated when the database is read
    ListMapRecPtr m_pList1 ;
    ListMapRecPtr m_pList2 ;
    int nList1, nList2 ;

    int saved ;
    TaskRec *pLastTasks ;
    int nLastTasks ;

    CString m_strErrTask ; 
    CString m_strSONUM ;
    CString m_strEmpNum ;
    CString m_strErrEmpNum ;

    CImageList m_imglst ;

    int GetLastEmpNum(const char *taskstr) ;
    int FindErrEmpNum() ;

    int GetBitMapIDX(CString &bmapname) ;
    int LoadBitmaps() ;
    int BuildBitMapList() ;

    int LoadList(const char *station, const char *listdes, 
                 ListMapRecPtr &precs, int &nrecs) ;

    int InitListCtrl(ListMapRecPtr precs, int nrecs, 
                     CListCtrl &lstctrl, CString &listname) ;
    
    int SetPartStr(CString &partstr) ;


    // Dialog Data
    //{{AFX_DATA(CErrorDlg)
    enum { IDD = IDD_ERROR_DLG };
    CEdit	m_editErrEmp;
    CEdit	m_editSONUM;
    CEdit	m_editEmpNum;
    CListCtrl   m_listErrors;
    CListCtrl   m_listActions;
    CEdit       m_ePart;
    int	        m_nAllRadio;
    double	m_dSeverity;
    CString     m_csNotes;
    //}}AFX_DATA
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CErrorDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL
    
    // Implementation
protected:
    
    // Generated message map functions
    //{{AFX_MSG(CErrorDlg)
    afx_msg void OnAllRadio();
    afx_msg void OnBkrRadio();
    afx_msg void OnBolRadio();
    afx_msg void OnClear();
    afx_msg void OnCustomRadio();
    afx_msg void OnDringRadio();
    afx_msg void OnFdrRadio();
    afx_msg void OnInsRadio();
    afx_msg void OnMndRadio();
    afx_msg void OnPltRadio();
    afx_msg void OnSave();
    afx_msg void OnSbolRadio();
    virtual BOOL OnInitDialog();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERRORDLG_H__E9ED78A4_27A7_46BD_813D_08F3D419D9C7__INCLUDED_)
