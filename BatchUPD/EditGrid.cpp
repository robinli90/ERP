// EditGrid.cpp : implementation file
//

#include "stdafx.h"
#include "BatchUPD.h"
#include "msflexgrid1.h"
#include "EditGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditGrid

CEditGrid::CEditGrid()
{
}

CEditGrid::~CEditGrid()
{
}


BEGIN_MESSAGE_MAP(CEditGrid, CMsflexgrid1)
    //{{AFX_MSG_MAP(CEditGrid)
    ON_WM_GETDLGCODE()
    ON_WM_SETFOCUS()
    ON_WM_KILLFOCUS()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()




BEGIN_EVENTSINK_MAP(CEditGrid, CMsflexgrid1)
// {{AFX_EVENTSINK_MAP(CEditGrid)
// }}AFX_EVENTSINK_MAP
   ON_EVENT_REFLECT(CEditGrid, -603 /* KeyPress */, OnKeyPressGrid, VTS_PI2)
   ON_EVENT_REFLECT(CEditGrid, -601 /* DblClick */, OnDblClickGrid, VTS_NONE)
   ON_EVENT_REFLECT(CEditGrid, 72 /* LeaveCell */, OnUpdateGrid, VTS_NONE)
END_EVENTSINK_MAP()



/////////////////////////////////////////////////////////////////////////////
// CEditGrid message handlers

void CEditGrid::PreSubclassWindow()
{

    put_Row(0);
    put_Col(0) ;
    m_lBorderWidth = get_CellLeft() ;
    m_lBorderHeight = get_CellTop() ;


    // To convert grid rect from twips to DC units you need
    // pixels per inch.
    CDC* pDC = GetDC();
    m_nLogX = pDC->GetDeviceCaps(LOGPIXELSX);
    m_nLogY = pDC->GetDeviceCaps(LOGPIXELSY);
    ReleaseDC(pDC);

    m_edit.pegrid = this ; 
    // Create invisible edit control.
    m_edit.Create(WS_CHILD|ES_MULTILINE|ES_WANTRETURN,
                  CRect(0,0,0,0), this, GetDlgCtrlID());

    CBatchUPDApp *pApp = (CBatchUPDApp *)AfxGetApp() ; 
    pApp->m_hWndEdit = m_edit.m_hWnd ; 
}


void CEditGrid::OnDblClickGrid()
{
    short i = 13;
    OnKeyPressGrid(&i); // Simulate a return.
}

void CEditGrid::OnKeyPressGrid(short FAR* KeyAscii)
{
    
    ASSERT (KeyAscii != NULL);
    
    // Retrieve text from the currently active grid location
    CString txt = get_Text() ; 
    m_edit.SetWindowText(txt);
    
    // 13 == 0x0d == 'CR'
    if (*KeyAscii == 13)  
        m_edit.SetSel(0,-1);
    else
    {
        char buf[] = " ";
        buf[0] = (char)*KeyAscii;
        m_edit.SetSel(0,-1);
        m_edit.ReplaceSel(buf);
    }
    
    // Adjust for border height and convert from twips to screen units.
    m_edit.MoveWindow(((get_CellLeft() - m_lBorderWidth) *
        m_nLogX)/1440,
        ((get_CellTop() - m_lBorderHeight) * m_nLogY)/1440,
        (get_CellWidth()* m_nLogX)/1440,
        (get_CellHeight()* m_nLogY)/1440, FALSE);
    
    m_edit.ShowWindow(SW_SHOW);
    m_edit.SetFocus();
}

void CEditGrid::OnUpdateGrid()
{
    // Check to see if edit is visible.
    BOOL bVisible = ::GetWindowLong(m_edit.GetSafeHwnd(), GWL_STYLE)
        & WS_VISIBLE;
    if (bVisible)
    {
        CString cStr;
        m_edit.GetWindowText(cStr);
        cStr.MakeUpper() ;
        put_Text(cStr);
        m_edit.SetWindowText("");
        m_edit.ShowWindow(SW_HIDE);
    }
}


UINT CEditGrid::OnGetDlgCode()
{
    return DLGC_WANTALLKEYS;
}

void CEditGrid::OnSetFocus(CWnd* pOldWnd)
{
    CMsflexgrid1::OnSetFocus(pOldWnd);
    
    OnUpdateGrid();
}


void CEditGrid::OnKillFocus(CWnd* pNewWnd) 
{
    CMsflexgrid1::OnKillFocus(pNewWnd);
    // Save all the data 
	
}
