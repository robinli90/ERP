// UpdateThread.h: interface for the UpdateThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UPDATETHREAD_H__9CAC59F5_A195_4163_B6A2_8055C4A33775__INCLUDED_)
#define AFX_UPDATETHREAD_H__9CAC59F5_A195_4163_B6A2_8055C4A33775__INCLUDED_

#include "SharedData.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

class UpdateThread  
{
public:
	void Stop(void);
	int Start();
	UpdateThread();
	virtual ~UpdateThread();

private:
	int stopExecution;
	SQLHENV	env;
	static DWORD WINAPI UpdateThread::LaunchUpdateThread(void *pInstance);
	void UpdateThread::UpdateThreadLoop(void);
};

#endif // !defined(AFX_UPDATETHREAD_H__9CAC59F5_A195_4163_B6A2_8055C4A33775__INCLUDED_)
