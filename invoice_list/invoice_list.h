
// invoice_list.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Cinvoice_listApp:
// See invoice_list.cpp for the implementation of this class
//

class Cinvoice_listApp : public CWinApp
{
public:
	Cinvoice_listApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Cinvoice_listApp theApp;