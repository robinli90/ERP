
// monthly_report_by_customer.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Cmonthly_report_by_customerApp:
// See monthly_report_by_customer.cpp for the implementation of this class
//

class Cmonthly_report_by_customerApp : public CWinApp
{
public:
	Cmonthly_report_by_customerApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Cmonthly_report_by_customerApp theApp;