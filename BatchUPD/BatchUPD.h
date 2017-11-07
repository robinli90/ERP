// BatchUPD.h : main header file for the PROJECT_NAME application
//


#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include <libCMS/CMSBOMRTE.h>
#include <libCMS/batchdata.h>

// CBatchUPDApp:
// See BatchUPD.cpp for the implementation of this class
//

class CBatchUPDDlg ;

class CBatchUPDApp : public CWinApp
{
public:

    FILE *fplog ; 

    HWND m_hWndEdit ; 

    CMSBOMRTE cmsdata ; // interface to CMS and databases

    CBatchUPDDlg *pdlg ; 

    CBatchUPDApp();
    ~CBatchUPDApp();

    // Member functions
    int LoadBatchIDList(csString &batchIDlist)  ;

    // Overrides
public:
    virtual BOOL InitInstance();

    // Implementation

    DECLARE_MESSAGE_MAP()


};

extern CBatchUPDApp theApp;

#define RUNTIME_RECORD      0x0001
#define EVENT_RECORD        0x0002
#define SAW_RECORD          0x0004

#define WM_STATUPD      WM_USER+1

int LoadDecadeEvents(CMSJob *pjob, CCMSDatabase *pdb) ;
