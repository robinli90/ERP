// Configuration.h
//
//
//

#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#include "Disable4786.h"
#include <map>

// CConfiguration Class
//
//
class CConfiguration  
{

	std::map<CString, bool> m_mapBooleans;
	std::map<CString, int> m_mapIntegers;
	std::map<CString, float> m_mapFloats;
	std::map<CString, CString> m_mapStrings;

public:
	CConfiguration();
	virtual ~CConfiguration();

	// Clear()
	//
	void Clear();

	// Load()
	//
	void Load(const char *szFilename);

	// GetBoolean()
	//
	bool GetBoolean(const char *szKey, bool bDefault = false) const;

	// GetInteger()
	//
	int GetInteger(const char *szKey, int nDefault = -1) const;

	// GetFloat()
	//
	float GetFloat(const char *szKey, float fDefault = -1.0f) const;

	// GetString()
	//
	CString GetString(const char *szKey, const char *szDefault = "") const;
};

extern CConfiguration g_Configuration;

#endif
