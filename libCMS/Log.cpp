#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include "Log.h"

CLog *CLog::sm_pInstance = NULL;

CLog::CLog(void)
{
    m_pFile = NULL;

    ::strcpy_s(m_szFileName, "c:\\libCMS_error.log");
}

CLog::~CLog(void)
{
    if (m_pFile != NULL) ::fclose(m_pFile);
}

void CLog::WriteLog(const char * fmt,...)
{
    va_list argptr;
    va_start(argptr, fmt);

    char szBuff[ 1024 ] = {0};

    ::vsprintf_s(szBuff, fmt, argptr);

    va_end(argptr);

    if (m_pFile == NULL)
    {
        fopen_s(&m_pFile, m_szFileName, "a");
    }

    SYSTEMTIME lt;
    ::GetLocalTime(&lt);

    ::fprintf(m_pFile, "%04d-%02d-%02d %02d:%02d:%02d |%s\n", lt.wYear, lt.wMonth, lt.wDay, lt.wHour, lt.wMinute, lt.wSecond, szBuff);
    ::fflush(m_pFile);
}