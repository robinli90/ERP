// CADupdate.h : main header file for the PROJECT_NAME application
//

#pragma once

#include <CSStdlibs/cslib.h>

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


#define CADUPDATE_CONFIG    "CADUpdate.cfg"

// CCADupdateApp:
// See CADupdate.cpp for the implementation of this class
//

class CCADupdateApp : public CWinApp
{
public:
    CCADupdateApp();

    // Overrides
public:
    virtual BOOL InitInstance();

    // Implementation

    DECLARE_MESSAGE_MAP()
};

extern CCADupdateApp theApp;

bool CompEQ(double a, double b) ;


/*

GENERAL NOTES:

To find standalone subparts do:
 select * from prodtest.ocri where ddpart like '%MA%' and ddord# < 400000
 */



