
// sales_report_colombia.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Csales_report_colombiaApp:
// See sales_report_colombia.cpp for the implementation of this class
//

class Csales_report_colombiaApp : public CWinApp
{
public:
	Csales_report_colombiaApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Csales_report_colombiaApp theApp;