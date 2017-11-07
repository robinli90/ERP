// BatchUPD.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "BatchUPD.h"
#include "BatchUPDDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBatchUPDApp

BEGIN_MESSAGE_MAP(CBatchUPDApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CBatchUPDApp construction

CBatchUPDApp::CBatchUPDApp()
{
    // TODO: add construction code here,
    // Place all significant initialization in InitInstance
    fplog = fopen("batchupd.log", "at") ; 
}

CBatchUPDApp::~CBatchUPDApp()
{
    if (fplog)
        fclose(fplog) ; 
}
 

// The one and only CBatchUPDApp object
CBatchUPDApp theApp;

CMSConnectionParms gCMSparms ;

// CBatchUPDApp initialization

BOOL CBatchUPDApp::InitInstance()
{
    // InitCommonControls() is required on Windows XP if an application
    // manifest specifies use of ComCtl32.dll version 6 or later to enable
    // visual styles.  Otherwise, any window creation will fail.
    InitCommonControls();

    CWinApp::InitInstance();

    AfxEnableControlContainer();

    // Standard initialization
    // If you are not using these features and wish to reduce the size
    // of your final executable, you should remove from the following
    // the specific initialization routines you do not need
    // Change the registry key under which our settings are stored
    // TODO: You should modify this string to be something appropriate
    // such as the name of your company or organization
    SetRegistryKey(_T("Local AppWizard-Generated Applications"));

    CDateTime dt ; 
    dt.SetNow() ; 
    char timestr[256] ; 
    dt.FormatDateTimeSecs(timestr) ; 
    fprintf(fplog, "\n--------------------------------------------\n"
                   "LOG OPENED: %s\n", timestr) ; 

    CMSEventProcessing evp ; 
    
    gCMSparms.pevp = &evp ; 
    gCMSparms.logfp = fplog ; 
    gCMSparms.pevp->fpLOG = fplog  ; 

    if (gCMSparms.LoadConfigFile("cmscfg.ini", fplog) < 0)
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

    CBatchUPDDlg dlg;
    dlg.deptMode = 0 ; 
    pdlg = &dlg ; 
    m_pMainWnd = &dlg;
    INT_PTR nResponse = dlg.DoModal();
    if (nResponse == IDOK)
    {
        // TODO: Place code here to handle when the dialog is
        //  dismissed with OK
    }
    else if (nResponse == IDCANCEL)
    {
        // TODO: Place code here to handle when the dialog is
        //  dismissed with Cancel
    }

    // Since the dialog has been closed, return FALSE so that we exit the
    //  application, rather than start the application's message pump.
    return FALSE;
}
