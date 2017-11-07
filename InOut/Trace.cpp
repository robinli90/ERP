#include "stdafx.h"
#include "Trace.h"

CTrace2 g_Trace;

// Constructor
//
CTrace2::CTrace2() :
m_strFilename("trace.txt")
{
    
    InitializeCriticalSection(&m_csAccess);
}

// Destructor
//
CTrace2::~CTrace2() {
    
    DeleteCriticalSection(&m_csAccess);
}

// SetFilename()
//
void CTrace2::SetFilename(CString strFilename) {
    
    EnterCriticalSection(&m_csAccess);
    m_strFilename = strFilename;
    LeaveCriticalSection(&m_csAccess);
}

// WriteString()
//
void CTrace2::WriteString(CString strLevel, CString strContext, CString strMessage) {
    
    CString strTimeStamp;
    CString strLine;
    CStdioFile fOut;
    CTime tNow;
    
    tNow = CTime::GetCurrentTime();
    strLine.Format("%s ", tNow.Format("%y/%m/%d %H:%M:%S"));
    
    if(strLevel.GetLength() != 0) {
        strLine += strLevel;
        strLine += " ";
    }
    
    if(strContext.GetLength() != 0) {
        strLine += "[";
        strLine += strContext;
        strLine += "] ";
    }
    
    strLine += strMessage;
    strLine += "\n";
    
    EnterCriticalSection(&m_csAccess);
    if(fOut.Open(m_strFilename, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
        fOut.SeekToEnd();
        fOut.WriteString(strLine);
        fOut.Close();
    }
    LeaveCriticalSection(&m_csAccess);
}

// Write()
//
void CTrace2::Write(CString strMessage, ...) {
    
    va_list marker;
    CString strOut;
    
    va_start(marker, strMessage);
    strOut.FormatV(strMessage, marker);
    
    WriteString("", "", strOut);
}

// Trace()
//
void CTrace2::Trace(CString strContext, CString strMessage, ...) {
    
    va_list marker;
    CString strOut;
    
    va_start(marker, strMessage);
    strOut.FormatV(strMessage, marker);
    
    WriteString("", strContext, strOut);
}

// Warn()
//
void CTrace2::Warn(CString strContext, CString strMessage, ...) {
    
    va_list marker;
    CString strOut;
    
    va_start(marker, strMessage);
    strOut.FormatV(strMessage, marker);
    
    WriteString("WARNING", strContext, strOut);
}

// Error()
//
void CTrace2::Error(CString strContext, CString strMessage, ...) {
    
    va_list marker;
    CString strOut;
    
    va_start(marker, strMessage);
    strOut.FormatV(strMessage, marker);
    
    WriteString("ERROR", strContext, strOut);
}
