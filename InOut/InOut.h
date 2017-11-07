// InOut.h
//
//
//



#ifndef _INOUT_H_
#define _INOUT_H_

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include <afxmt.h>

#include "resource.h"
#include <libCMS\CMSBOMRTE.h>
#define WM_MESSAGE_UPDATEPROMPT     WM_USER + 1 
#define WM_MESSAGE_UPDATEMSG        WM_USER + 2 
#define WM_MESSAGE_RESETSONUM       WM_USER + 3
#define WM_MESSAGE_RESETEMPNUM      WM_USER + 4
#define WM_MESSAGE_RESETALL         WM_USER + 5


// CInOutApp Class
//
//
class CInOutApp : public CWinApp
{

public:
    CInOutApp();
    
    //{{AFX_VIRTUAL(CInOutApp)
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL
    FILE *fplog ;
	CMSBOMRTE cmsdata ;
    //{{AFX_MSG(CInOutApp)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


// Global Functions
extern _ConnectionPtr m_pConn ;

#define MAXSONUMLEN             7 
#define MAXNUMSONUMS            30

bool ValidEmpNum(CString csEmpNum) ;
bool ValidSONUMs(CString csSONUM, char sos[][32], int &nsos) ;
int ExtractSONUMs(const char *sostr, char sonums[][32]) ;

// The following converts the standard 5 digit sonumber string to 
// 6 digits for database access operations
char *Exco100kMapSONUM(char *sonum) ;



//{{AFX_INSERT_LOCATION}}


#endif

