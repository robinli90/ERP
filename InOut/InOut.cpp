// InOut.cpp
//
//
//

#include "stdafx.h"
#include "InOut.h"
#include "InOutDlg.h"
#include "Configuration.h"
#include "Trace.h"
#include <libCMS\CMSBOMRTE.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// Message Map
//
BEGIN_MESSAGE_MAP(CInOutApp, CWinApp)
	//{{AFX_MSG_MAP(CInOutApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

// Constructor
//
CInOutApp::CInOutApp()
{
}

// The one and only CInOutApp object
CInOutApp theApp;

_ConnectionPtr m_pConn ;
CMSConnectionParms gCMSparms ;
// InitInstance()
//
BOOL CInOutApp::InitInstance()
{
    
    AfxEnableControlContainer();
    Enable3dControls();
    
    // load configuration file
    try
    {
        g_Configuration.Load("InOut.cfg");
    }
    catch(CString e)
    {
        
        MessageBox(NULL, e, "Error", MB_OK);
        return FALSE;
    }

    CMSEventProcessing evp ; 
    
    gCMSparms.pevp = &evp ; 
    gCMSparms.logfp = fplog ; 
    gCMSparms.pevp->fpLOG = fplog  ; 
#ifdef NDEBUG
    if (gCMSparms.LoadConfigFile("C:\\inout-winxp\\cmscfg.ini", fplog) < 0)
#else
	if (gCMSparms.LoadConfigFile("cmscfg.ini", fplog) < 0)
#endif
    {
        AfxMessageBox("Error loading Solarsoft parameters from cmscfg.ini", MB_OK) ; 
        return FALSE ; 
    }

    strcpy(cmsdata.m_db.odbcName, gCMSparms.odbc) ; 
    strcpy(cmsdata.m_db.userName, gCMSparms.dbusr) ; 
    strcpy(cmsdata.m_db.password, gCMSparms.dbpwd) ; 

    strcpy(gCMSparms.pevp->m_db.odbcName, gCMSparms.odbc) ; 
    strcpy(gCMSparms.pevp->m_db.userName, gCMSparms.dbusr) ; 
    strcpy(gCMSparms.pevp->m_db.password, gCMSparms.dbpwd) ; 

    strcpy(gCMSparms.pevp->m_db.dbname, gCMSparms.dbname) ; 

    gCMSparms.pevp->OpenDatabase() ; 

    strcpy(evp.plantID, gCMSparms.plantID) ; 
    time(&evp.idseed) ;

    cmsdata.OpenDatabase(gCMSparms.dbname) ;

    evp.LoadMaps(evp.plantID) ; // Required for task map operations. 

    // initialize trace
    g_Trace.SetFilename(g_Configuration.GetString("traceFile", "C:\\inout.log"));
    g_Trace.Trace("CInOutApp::InitInstance", "*** STARTED ***");
    
    CInOutDlg dlg;
    m_pMainWnd = &dlg;
    dlg.DoModal();
    
    return FALSE;
}
