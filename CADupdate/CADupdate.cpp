// CADupdate.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

// CCADupdateApp

BEGIN_MESSAGE_MAP(CCADupdateApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()



// CCADupdateApp construction
CCADupdateApp::CCADupdateApp()
{
    EnableHtmlHelp();

    // TODO: add construction code here,
    // Place all significant initialization in InitInstance
}


// The one and only CCADupdateApp object

CCADupdateApp theApp;

CMSConnectionParms gCMSparms ; 


char *usageString = 
    "The configuration file should have the following contents\n\n"
    " ------------------ SAMPE CONFIG FILE STARTS HERE (WITHOUT THIS LINE) -----------------\n"
    "# Lines starting with has marks are comments\n"
    "# The ROUTING data file contains the conditional parameters used to update\n"
    "# the RTE (METHDR) entries within Solarsoft for jobs based on job conditions\n"
    "# and various features and options. Refer to the sample RoutingUpdateSample.dat\n"
    "# file for the structure and layout. The CMS parameter points to the config file\n"
    "# which contains the Decade and Solarsoft connection parameters to both the\n"
    "# Decade database and the IBM database, as well as the IBM data queues.\n"
    "# Refer to the file CMScfg.INI for an example of the required layout.\n"
    "ROUTING=<filename>\n"
    "CMSCFG=<filename>\n"
    "FFDIR=<output_flat_file_directory>\n"
    "FFPREFIX=<outputfile_prefix>\n"
    "TIMEDIR=<UG RUNTIMES DIR>\n"
    "TIMEMAP=<timemap_file>\n"
    "NDIGITS=N\n"
    "PLANT=001\n"
    "# Do not include quotes around the filenames.\n"
    "# The FFPREFIX should be a unique station ID string so that as files\n"
    "# are output to the flat file directory, there is no naming collision\n"
    "# with other workstations. CAD1, CAD2, CAD3, etc... could be used as\n"
    "# stations name prefixes, or the actual users name. A time stamp is\n"
    "# automatically added to this name.\n"
    "# TIMEDIR is the directory where UG runtimes are stored\n"
    "# TIMEMAP is the file that indicates how runtime files are\n"
    "# associated to sequence numbers within Solarsoft routings.\n"
    "# NDIGITS indicates how many digits to consider in the UG runtime\n"
    "# filename to map to an actual order number. For Markham for example\n"
    "# NDIGITS is 5 since the leading digit is truncated, the system will\n"
    "# automatically insert the leading digit.\n"
    " ------------------ SAMPE CONFIG FILE ENDS HERE (WITHOUT THIS LINE) -----------------\n"
    ;



// CCADupdateApp initialization

BOOL CCADupdateApp::InitInstance()
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

    CCADupdateDlg dlg;
	//Decide you want to use Flatfile input or GUI
	dlg.ready = false;
	dlg.regCADUpdate = false;
	dlg.pass = false;
	dlg.multiSO = false;
	dlg.multiSO1 = false;
	dlg.Enter = false;
	dlg.errord = false;
	dlg.countMultiSO = 0;
	dlg.MultiSoCAD = false;
	dlg.SOCount = 0;
	dlg.stage = -1;
    CMSBOMRTE cmsdata ;
    CMSEventProcessing evp ; // event processing data structure

    FILE *fplog = fopen("CADupdate_LogFile.txt", "at") ; 
    FILE *fp = 0 ; 
    evp.fpLOG = fplog ; 
    gCMSparms.pevp = &evp ; 
    try {
        static char configName[1024] ; 
        strcpy(configName, CADUPDATE_CONFIG) ;
		dlg.regCADUpdate = true;
		
        fp = fopen(configName, "rt") ; 
        if (!fp)
        {
            LogToFile(fplog, 
                "ERROR: couldn't open the config file '%s'\n"
                "   make sure the config file is in the same directory as the application.\n"
                    ,CADUPDATE_CONFIG) ; 
            
            LogToFile(fplog, usageString) ; 

            AfxMessageBox("ERROR: couldn't opent the default configuration file\n"
                        CADUPDATE_CONFIG " which can either be defined in the\n"
                        "same directory as the application, or passed as a\n"
                        "file name parameter on the command line when the app\n"
                        "is launched. There is a log file created called\n"
                        "CADupdate_LogFile.txt which has more information.\n", MB_OK) ; 

            throw -1 ; 
        }

        static char buf[1024] ; 
        
        csString routingFile ; 
        csString cmsFile ; 
        csString timeMapFile ; 
        csString csPlant ; 

        int linecount = 0 ; 
        while (fgets(buf, 1000, fp))
        {
            linecount++ ; 
            csString ln(buf) ; 
            ln.Trim() ; 
            if (ln.size() == 0 || ln[0] == '#')
                continue ; 
            
            csString tok = ln.NextToken("=", 0) ; 
            tok.Trim() ; 
            if (tok == "ROUTING")
            {
                tok = ln.NextToken("=") ; 
                tok.Trim() ; 
                routingFile = tok ; 
            }
            else if (tok == "CMSCFG")
            {
                tok = ln.NextToken("=") ;
                tok.Trim() ;
                cmsFile = tok ;
            }
            else if (tok == "FFDIR")
            {
                tok = ln.NextToken("=") ;
                tok.Trim() ;
                CS_strmaxcpy(cmsdata.szFlatFileDir, tok.c_str(), 250) ; 
            }
            else if (tok == "FFPREFIX")
            {
                tok = ln.NextToken("=") ;
                tok.Trim() ;
                CS_strmaxcpy(cmsdata.szFlatFilePrefix, tok.c_str(), 100) ; 
            }
            else if (tok == "TIMEDIR")
            {
                tok = ln.NextToken("=") ;
                tok.Trim() ;
                CS_strmaxcpy(cmsdata.NCTimesDir, tok.c_str(), 126) ; 
            }
            else if (tok == "TIMEMAP")
            {
                tok = ln.NextToken("=") ;
                tok.Trim() ;
                timeMapFile = tok ; 
            }
            else if (tok == "NDIGITS")
            {
                tok = ln.NextToken("=") ;
                tok.Trim() ;
                cmsdata.ncFileDigits = atoi(tok.c_str()) ; 
            }
            else if (tok == "PLANT")
            {
                tok = ln.NextToken("=") ;
                tok.Trim() ;
                CS_strmaxcpy(cmsdata.plant, tok.c_str(), 15) ; 
            }
            else
            {
                LogToFile(fplog, "Warning: unknown parameter in config startup file line %d\n", 
                                linecount) ; 
            }
        }

        fclose(fp) ; 

        if (routingFile.size() == 0 || cmsFile.size() == 0)
        {   // These have to exist so abort 
            throw -2 ; 
        }

        int errcode ; 
        if ((errcode=LoadRoutingTable(routingFile.c_str(), 
                                      cmsdata.rcondvec, 
                                      cmsdata.rsingvec, 
                                      cmsdata.rnomastvec, 
                                      fplog)) < 0)
        {
            LogToFile(fplog, "ERROR# %d, trying to load routing conditions file '%s'\n", 
                            errcode, routingFile.c_str()) ; 
            AfxMessageBox(
                "ERROR loading routing condition file. See log file for more details.\n",
                 MB_OK) ; 
            throw -3 ; 
        }

        if ((errcode=LoadNCTimingMap(timeMapFile.c_str(), cmsdata.timemap, fplog)) < 0)
        {
            LogToFile(fplog, "ERROR# %d, trying to load time map file '%s'\n", 
                            errcode, timeMapFile.c_str()) ; 
            AfxMessageBox(
                "ERROR loading time map file. See log file for more details.\n",
                 MB_OK) ; 
            throw -3 ; 
        }

        dlg.pcms = &cmsdata ; 
        dlg.pevp = &evp ; 

        gCMSparms.logfp = fplog ; 
        if ((errcode=gCMSparms.LoadConfigFile(cmsFile.c_str(), fplog)) != 0)
        {
            LogToFile(fplog, "ERROR# %d, trying to load CMS config file '%s'\n", 
                            errcode, cmsFile.c_str()) ; 
            AfxMessageBox(
                "ERROR loading CMS configuration file. See log file for more details.\n",
                 MB_OK) ; 
            throw -4 ; 
        }

        // TODO - clean up these duplicate parameter requirements. 
        strcpy(cmsdata.m_db.odbcName, gCMSparms.odbc) ; 
        strcpy(cmsdata.m_db.userName, gCMSparms.dbusr) ; 
        strcpy(cmsdata.m_db.password, gCMSparms.dbpwd) ; 
		strcpy(gCMSparms.pevp->m_db.odbcName, gCMSparms.odbc) ; 
		strcpy(gCMSparms.pevp->m_db.userName, gCMSparms.dbusr) ; 
		strcpy(gCMSparms.pevp->m_db.password, gCMSparms.dbpwd) ; 
		strcpy(gCMSparms.pevp->m_db.dbname, gCMSparms.dbname) ;
        // Work Order Flat File Processing
        cmsdata.OpenDatabase(gCMSparms.dbname) ;
        gCMSparms.pevp->OpenDatabase() ; 

		
		dlg.m_strODBC = CString(gCMSparms.decDBname) ; 
		dlg.m_strODBCusr = CString(gCMSparms.decDBusr) ; 
		dlg.m_strODBCpwd = CString(gCMSparms.decDBpwd) ; 
		dlg.m_sql.OpenEx((LPCTSTR)dlg.m_strODBC,
                 (LPCTSTR)dlg.m_strODBCusr,
                 (LPCTSTR)dlg.m_strODBCpwd) ; 

        // only have to do this once. 
        if (!cmsdata.InitSteelTypes())
        {
            AfxMessageBox("Error loading the steel types") ; 
            throw -5 ; 
        }

        m_pMainWnd = &dlg;	
		dlg.regCADUpdate = true;
		INT_PTR nResponse = dlg.DoModal();

		AfxMessageBox("Process Done! \nIf you see any error message please correct your input and try again.", MB_OK) ; 

        fclose(fp) ; // close the log file. 
    }
    catch(int errnum)
    {
        LogToFile(fplog, "ERROR #%d, aborting\n", errnum) ; 
        if (fplog)
            fclose(fplog) ; 
        if (fp)
            fclose(fp) ; 
    }
    catch(...)
    {
        LogToFile(fplog, "TRAPPING UNKOWN FATAL ERROR\r\n  ==> possibly STLTYPES is not defined") ; 
        AfxMessageBox("UNKOWN FATAL ERROR\r\npossibly STLTYPES is not defined", MB_OK) ; 

        if (fplog)
        {
            fclose(fplog) ; 
            fplog = 0 ; 
        }

        if (fp)
            fclose(fp) ; 
    }

    if (fplog)
        fclose(fplog) ; 

	return FALSE;
}


bool CompEQ(double a, double b)
{
    if ((a - 0.01) < b && (a + 0.01) > b)
	{
        return true ; 
	}
    return false ; 
}
