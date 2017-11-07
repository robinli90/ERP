/***************************************************************************
    Copyright (C) 1981-2009 Cadamation Systems Inc., Ontario, Canada 
            All Rights Reserved Worldwide

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
    SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
    FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*****************************************************************************/
// #ifdef _WIN32
#include <windows.h>


#include "sysProc.h"
//! Calls a command line process and retrieves the stdout and stderr output
/*!
    \param strCmdLine actual command line string to be executed. 
    \param outdata the output to stdout or stderr
    \param mode 1=stdout, 2=stderr
    \return 0=OK else an error code is returned. 
        
     Returns:
         0  OK, 
        -1  couldn't create pipe
        -2  bad mode, must be 1=stdout or 2=stderr
        -3  error creating process
      -100  insufficient memory for output data (memory allocation error)


    You must call free(outdata) on return. The memory for the output data 
    is allocated as required using re-alloc. outdata is set to null at 
    startup before anything else happens so make sure it is free'd if 
    required before calling this function. 

    The function waits for up to 10 seconds for the called process to finish 
    before returning. If the called process hangs, then this function will return
    after 10 seconds, but no attempt will be made to kill the still running 
    cmdline process. 

    If the error is > -99 then no attempt was made to start the process. 
    
*/
int CS_GetStdOut(char *strCmdLine, char **outdata, int mode, char *workdir)
{
    PROCESS_INFORMATION piProcInfo = {0};
#if (_MSC_VER > 8)
    STARTUPINFOA siStartInfo = {0};
#else 
    STARTUPINFO siStartInfo = {0};
#endif 

    *outdata = 0 ; 
    char *so = 0 ; 
    so = 0 ; 


    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

    HANDLE hRead;
    HANDLE hWrite;
    BOOL bRet = CreatePipe(&hRead, &hWrite, &sa, 0);
    if (bRet != TRUE)
    {
        return -1 ; // error creating the PIPE
    }

    HANDLE hTemp ; 
    switch(mode)
    {
        case 1 :
            hTemp = GetStdHandle(STD_OUTPUT_HANDLE);
            break ; 
        case 2 :
            hTemp = GetStdHandle(STD_ERROR_HANDLE);
            break ; 
        default:
            CloseHandle(hRead) ; 
            CloseHandle(hWrite) ; 
            return -2 ; 
    }

    SetStdHandle(STD_OUTPUT_HANDLE, hWrite);
    GetStartupInfoA(&siStartInfo);
    siStartInfo.hStdError = hWrite;
    siStartInfo.hStdOutput = hWrite;
    siStartInfo.wShowWindow = SW_HIDE;
    siStartInfo.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

    BOOL bSucceeded = CreateProcessA(NULL,
                                    strCmdLine,
                                    NULL,                   // process security attributes
                                    NULL,                   // primary thread security attributes
                                    TRUE,                   // handles are inherited
                                    NULL,                   // creation flags
                                    NULL,                   // use parent's environment
                                    workdir,                // use parent's current directory
                                    &siStartInfo,           // STARTUPINFO pointer
                                    &piProcInfo);           // receives PROCESS_INFORMATION

    DWORD derr = GetLastError() ; 

    if (!bSucceeded)
    {
        // int nErrCode = GetLastError() ;
        CloseHandle(hWrite) ; 
        CloseHandle(hRead) ; 
        return -3 ; 
    }

     // capture the output 
    switch(mode)
    {
        case 1 :
            SetStdHandle(STD_OUTPUT_HANDLE, hTemp) ;
            break ; 
        case 2 :
            SetStdHandle(STD_ERROR_HANDLE, hTemp) ; 
            break ; 
    }
    
    CloseHandle(hWrite) ;

    char readBuf[2048] ;
    readBuf[0] = 0 ; 

    int retcode = 0 ; 
    int outlen = 0 ; 
    DWORD nbytesRead ;
    while (ReadFile(hRead, readBuf, 2000, &nbytesRead, NULL))
    {
        if (nbytesRead)
        {
            char *stmp = (char *)realloc(so, outlen + nbytesRead + 4) ; 
            if (!stmp)
            {
                retcode = -101 ; 
                break ; 
            }
            so = stmp ; 
            memcpy(so + outlen, readBuf, nbytesRead) ; 
            outlen += nbytesRead ; 
            so[outlen] = 0 ; 
            so[outlen+1] = 0 ; 
        }
    }

    // Now wait for the process to end
    WaitForSingleObject(piProcInfo.hProcess, 100);
    
    CloseHandle(hRead) ; 

    CloseHandle(piProcInfo.hProcess) ; 
    CloseHandle(piProcInfo.hThread) ; 
    *outdata = so ; 

    return 0 ;
}

// ***************************** CALLBACK VERSION ***************************
// This version monitors the output data and sends it to the callback 
// function
int CS_GetStdOut(char *strCmdLine, CmdCallbackProc prcfunc, void *pUserData, int mode, char *workdir) 
{
    PROCESS_INFORMATION piProcInfo = {0};

#if (_MSC_VER > 8)
    STARTUPINFOA siStartInfo = {0};
#else 
    STARTUPINFO siStartInfo = {0};
#endif 

    char *so = 0 ; 
    so = 0 ; 

    SECURITY_ATTRIBUTES sa ;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES) ;
    sa.lpSecurityDescriptor = NULL ;
    sa.bInheritHandle = TRUE ;

    HANDLE hRead ;
    HANDLE hWrite ;
    BOOL bRet = CreatePipe(&hRead, &hWrite, &sa, 0) ;
    if (bRet != TRUE)
    {
        return -1 ; // error creating the PIPE
    }

    HANDLE hTemp ; 
    switch(mode)
    {
        case 1 :
            hTemp = GetStdHandle(STD_OUTPUT_HANDLE) ;
            break ; 
        case 2 :
            hTemp = GetStdHandle(STD_ERROR_HANDLE) ;
            break ; 
        default:
            CloseHandle(hRead) ;
            CloseHandle(hWrite) ;
            return -2 ;
    }

    SetStdHandle(STD_OUTPUT_HANDLE, hWrite) ;
    GetStartupInfoA(&siStartInfo) ;
    siStartInfo.hStdError = hWrite ;
    siStartInfo.hStdOutput = hWrite ;
    siStartInfo.wShowWindow = SW_HIDE ;
    siStartInfo.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES ;

    BOOL bSucceeded = CreateProcessA(NULL,
                                    strCmdLine,     
                                    NULL,          // process security attributes
                                    NULL,          // primary thread security attributes
                                    TRUE,          // handles are inherited
                                    NULL,          // creation flags
                                    NULL,          // use parent's environment
                                    workdir,       // use parent's current directory
                                    &siStartInfo,  // STARTUPINFO pointer
                                    &piProcInfo) ; // receives PROCESS_INFORMATION


    if (!bSucceeded)
    {
        // int nErrCode = GetLastError() ;
        CloseHandle(hWrite) ; 
        CloseHandle(hRead) ; 
        return -3 ; 
    }

     // capture the output 
    switch(mode)
    {
        case 1 :
            SetStdHandle(STD_OUTPUT_HANDLE, hTemp) ;
            break ; 
        case 2 :
            SetStdHandle(STD_ERROR_HANDLE, hTemp) ; 
            break ; 
    }

    CloseHandle(hWrite) ;

    char readBuf[2048] ;
    readBuf[0] = 0 ;

    int retcode = 0 ;
    int outlen = 0 ;
    DWORD nbytesRead ;
    while (ReadFile(hRead, readBuf, 2000, &nbytesRead, NULL))
    {
        if (nbytesRead)
        {
            char *stmp = (char *)realloc(so, outlen + nbytesRead + 4) ; 
            if (!stmp)
            {
                retcode = -101 ;
                break ;
            }
            so = stmp ; 
            memcpy(so + outlen, readBuf, nbytesRead) ; 
            outlen += nbytesRead ; 
            so[outlen] = 0 ; 
            so[outlen+1] = 0 ; 
        }
    }

    // Now wait for the process to end
    WaitForSingleObject(piProcInfo.hProcess, 100);
    
    CloseHandle(hRead) ; 

    CloseHandle(piProcInfo.hProcess) ; 
    CloseHandle(piProcInfo.hThread) ; 

    return 0 ;
}


void CS_PrintLastError(FILE *fp)
{
    DWORD errnum = GetLastError () ; 
    printf("Invalid File Handle. Get Last Error reports %d\n", errnum) ;
    LPVOID lpMsgBuf;
    FormatMessage( 
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM | 
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errnum,
        0, // Default language
        (LPTSTR) &lpMsgBuf,
        0,
        NULL 
        );
    // Process any inserts in lpMsgBuf.
    // ...
    // Display the string.
    fprintf(fp, "%s\n", lpMsgBuf) ; 

    // Free the buffer.
    LocalFree( lpMsgBuf );
}


int CS_GetFileTime(char *filename, time_t &t)
{
    HANDLE hFile; 
 
    hFile = CreateFile(filename,           // open MYFILE.TXT 
                    GENERIC_READ,              // open for reading 
                    FILE_SHARE_READ,           // share for reading 
                    NULL,                      // no security 
                    OPEN_EXISTING,             // existing file only 
                    FILE_ATTRIBUTE_NORMAL,     // normal file 
                    NULL);                     // no attr. template 
 
    if (hFile == INVALID_HANDLE_VALUE) 
        return -1 ; // file not found

    FILETIME ftCreate, ftAccess, ftWrite;
    SYSTEMTIME stUTC, stLocal;

    // Retrieve the file times for the file.
    if (!GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite))
    {
        CloseHandle(hFile) ; 
        return FALSE;
    }

    // Convert the last-write time to local time.
    FileTimeToSystemTime(&ftWrite, &stUTC);
    SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

    // Build a string showing the date and time.
    struct tm stm ; 
    memset(&stm, 0, sizeof(stm)) ; 
    stm.tm_year = stLocal.wYear - 1900 ; 
    stm.tm_mon  = stLocal.wMonth - 1 ; 
    stm.tm_mday = stLocal.wDay ; 
    stm.tm_hour = stLocal.wHour ; 
    stm.tm_min  = stLocal.wMinute ; 
    stm.tm_sec  = stLocal.wSecond ; 

    t = mktime(&stm) ;

    CloseHandle(hFile) ; 

    return 0 ; 
}


#ifndef UINT32 
typedef unsigned int UINT32 ; 
#endif

/***********************************************************************
 *           DOSFS_FileTimeToUnixTime
 *
 * Convert a FILETIME format to Unix time.
 * If not NULL, 'remainder' contains the fractional part of the filetime,
 * in the range of [0..9999999] (even if time_t is negative).
 */
time_t CS_FileTimeToUnixTime( const FILETIME *filetime, DWORD *remainder )
{
    UINT32 a0;			/* 16 bit, low    bits */
    UINT32 a1;			/* 16 bit, medium bits */
    UINT32 a2;			/* 32 bit, high   bits */
    UINT32 r;			/* remainder of division */
    unsigned int carry;		/* carry bit for subtraction */
    int negative;		/* whether a represents a negative value */

    /* Copy the time values to a2/a1/a0 */
    a2 =  (UINT32)filetime->dwHighDateTime;
    a1 = ((UINT32)filetime->dwLowDateTime ) >> 16;
    a0 = ((UINT32)filetime->dwLowDateTime ) & 0xffff;

    /* Subtract the time difference */
    if (a0 >= 32768           ) a0 -=             32768        , carry = 0;
    else                        a0 += (1 << 16) - 32768        , carry = 1;

    if (a1 >= 54590    + carry) a1 -=             54590 + carry, carry = 0;
    else                        a1 += (1 << 16) - 54590 - carry, carry = 1;

    a2 -= 27111902 + carry;
    
    /* If a is negative, replace a by (-1-a) */
    negative = (a2 >= ((UINT32)1) << 31);
    if (negative)
    {
	/* Set a to -a - 1 (a is a2/a1/a0) */
	a0 = 0xffff - a0;
	a1 = 0xffff - a1;
	a2 = ~a2;
    }

    /* Divide a by 10000000 (a = a2/a1/a0), put the rest into r.
       Split the divisor into 10000 * 1000 which are both less than 0xffff. */
    a1 += (a2 % 10000) << 16;
    a2 /=       10000;
    a0 += (a1 % 10000) << 16;
    a1 /=       10000;
    r   =  a0 % 10000;
    a0 /=       10000;

    a1 += (a2 % 1000) << 16;
    a2 /=       1000;
    a0 += (a1 % 1000) << 16;
    a1 /=       1000;
    r  += (a0 % 1000) * 10000;
    a0 /=       1000;

    /* If a was negative, replace a by (-1-a) and r by (9999999 - r) */
    if (negative)
    {
	/* Set a to -a - 1 (a is a2/a1/a0) */
	a0 = 0xffff - a0;
	a1 = 0xffff - a1;
	a2 = ~a2;

        r  = 9999999 - r;
    }

    if (remainder) *remainder = r;

    /* Do not replace this by << 32, it gives a compiler warning and it does
       not work. */
    return ((((time_t)a2) << 16) << 16) + (a1 << 16) + a0;
}

int UnicodeToAnsi(void *pszW, char *ppszA, int maxlen)
{
    DWORD dwError;

    // If input is null then just return the same.
    if (pszW == NULL)
    {
        *ppszA = NULL ;
        return NOERROR ;
    }

    ULONG cCharacters;
    // ULONG cbAnsi ;
    cCharacters = (ULONG)wcslen((LPCWSTR)pszW)+1;
    // Determine number of bytes to be allocated for ANSI string. An
    // ANSI string can have at most 2 bytes per character (for Double
    // Byte Character Strings.)
    //  cbAnsi = cCharacters*2 ;

    // Convert to ANSI.
    if (0 == WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)pszW, cCharacters, ppszA,
                  maxlen, NULL, NULL))
    {
        dwError = GetLastError();
        *ppszA = NULL;
        return HRESULT_FROM_WIN32(dwError);
    }
    return NOERROR;

}


bool CS_FileExists(const char *filename)
{
    FILE *fp;
	fopen_s(&fp, filename, "r") ; 
    if (fp)
    {
        fclose(fp) ; 
        return true ; 
    }
    return false ; 
}


#if defined(_MSC_VER) && (_MSC_VER > 1200)


bool CS_DirExists(char *path, DWORD *errorcode)
{
    DWORD dwAttr = GetFileAttributes(path);
    if(dwAttr == INVALID_FILE_ATTRIBUTES)   // 0xffffffff
    {
        DWORD dwError = GetLastError();
        if (errorcode)
            *errorcode = dwError ; 
        return false ; 
    }

    if(dwAttr & FILE_ATTRIBUTE_DIRECTORY)
        return true ; 

    if (errorcode)
        *errorcode = dwAttr ; 
    return false ; 
}

#endif

// #endif
