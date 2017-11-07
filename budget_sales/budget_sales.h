
// budget_sales.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Cbudget_salesApp:
// See budget_sales.cpp for the implementation of this class
//

class Cbudget_salesApp : public CWinApp
{
public:
	Cbudget_salesApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Cbudget_salesApp theApp;