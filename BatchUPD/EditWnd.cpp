// EditWnd.cpp : implementation file
//

#include "stdafx.h"
#include "BatchUPD.h"
#include "BatchUPDDlg.h"
#include "EditWnd.h"
#include "EditGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


int SQL_TestBackerNC(int sonum, int &bBKRNC) ;


int IsAlphaNum(UINT n)
{
    if ((n >= '0' && n <= '9') ||
        (n >= 'A' && n <= 'Z') ||
        (n >= 'a' && n <= 'z') ||
        (n == 8) || (n == '.') || (n == '-'))
        return 1 ; 
    return 0 ; 
}

/////////////////////////////////////////////////////////////////////////////
// CEditWnd

CEditWnd::CEditWnd()
{
    oldnewMode = -1 ; 
    maxRowNum = -1; 
}

CEditWnd::~CEditWnd()
{
}


BEGIN_MESSAGE_MAP(CEditWnd, CEdit)
    //{{AFX_MSG_MAP(CEditWnd)
    ON_WM_CHAR()
    ON_WM_KEYDOWN()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditWnd message handlers

void CEditWnd::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if (IsAlphaNum(nChar))  // != 13) // Ignore ENTER key.
        CEdit::OnChar(nChar, nRepCnt, nFlags);
}

void CEditWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if (nChar == 27) // Esc means "Cancel".
    {
        SetWindowText("");
        ShowWindow(SW_HIDE);
        GetParent()->SetFocus();
    }
    else if (nChar == 13)  // Enter means "OK".
    {
        CString txt ; 
        int row, col ; 
        row = pegrid->get_Row() ; 
        col = pegrid->get_Col() ; 

        ShowWindow(SW_HIDE);
        GetWindowText(txt) ; 
        txt.MakeUpper() ; 
        pegrid->put_Text(txt) ; // update the text in the current grid box

        CBatchUPDApp *pApp = (CBatchUPDApp *)AfxGetApp() ; 
        col = 11 ;
        row += 1 ; 

        if (row >= (int)pApp->pdlg->numRows)
            row = 1 ; 
        
        // Move to next position
        pegrid->put_Row(row) ; 
        pegrid->put_Col(col) ; 
        GetParent()->SetFocus() ;
    }
    else 
    {
        CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
    }
    // else ignore the character
}



// the END key does not get to here if the cell isn't in edit mode. 
BOOL CEditWnd::PreTranslateMessage(MSG* pMsg) 
{
    // TODO: Add your specialized code here and/or call the base class
    return CEdit::PreTranslateMessage(pMsg);
}
