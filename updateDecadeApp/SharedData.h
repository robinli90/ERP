// SharedData.h: interface for the SharedData class.
// This is presently unused, because there are no
// controls in the interface requiring communication
// between the GUI and update threads.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAREDDATA_H__F1D99022_2A94_480D_89D2_1F556251B8EF__INCLUDED_)
#define AFX_SHAREDDATA_H__F1D99022_2A94_480D_89D2_1F556251B8EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class SharedData  
{
public:
	SharedData();
	virtual ~SharedData();
	void GetCommand(int *value);
	void SetCommand(int value);

private:
	CRITICAL_SECTION csSharedData;
	int command;
};

#endif // !defined(AFX_SHAREDDATA_H__F1D99022_2A94_480D_89D2_1F556251B8EF__INCLUDED_)
