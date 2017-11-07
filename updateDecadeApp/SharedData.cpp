// SharedData.cpp: implementation of the SharedData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SharedData.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SharedData::SharedData()
{
    InitializeCriticalSection(&csSharedData);
	EnterCriticalSection(&csSharedData);
        command = 0;
	LeaveCriticalSection(&csSharedData);
}

SharedData::~SharedData()
{
    DeleteCriticalSection(&csSharedData);
}

void SharedData::SetCommand(int value)
{
    EnterCriticalSection(&csSharedData);
	    command = value;
	LeaveCriticalSection(&csSharedData);    
}

void SharedData::GetCommand(int *value)
{
    EnterCriticalSection(&csSharedData);
	    *value = command;
	LeaveCriticalSection(&csSharedData);    
}
