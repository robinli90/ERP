#ifndef _TRACE_H_
#define _TRACE_H_

// CTrace2
//
class CTrace2 {

	CRITICAL_SECTION m_csAccess;

	CString m_strFilename;

	void WriteString(CString strLevel, CString strContext, CString strMessage);

public:
	CTrace2();
	virtual ~CTrace2();

	void SetFilename(CString strFilename);

	void Write(CString strMessage, ...);
	void Trace(CString strContext, CString strMessage, ...);
	void Warn(CString strContext, CString strMessage, ...);
	void Error(CString strContext, CString strMessage, ...);
};

extern CTrace2 g_Trace;

#endif
