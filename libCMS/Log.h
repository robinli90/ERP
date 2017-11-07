#pragma once

#ifndef _CLOG_H_
#define _CLOG_H_

#include <assert.h>

class CLog
{
public:
    static CLog& GetInstance(void)
    {
        if (sm_pInstance == NULL)
        {
            sm_pInstance = new CLog;
        }

        assert(sm_pInstance != NULL);

        return *sm_pInstance;
    }

    static void DeleteInstance(void)
    {
        delete sm_pInstance;
        sm_pInstance = NULL;
    }

    void SetLogFileName(const char * szFileName)
    {
        ::strcpy_s(m_szFileName, szFileName);
    }

    void WriteLog(const char * fmt,...);
private:
    CLog(void);

    ~CLog(void);

    FILE    *m_pFile;
    char    m_szFileName[ 260 ];

    static CLog *sm_pInstance;
};

#endif
