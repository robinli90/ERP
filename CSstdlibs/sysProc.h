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

#ifndef __sysProc_h__
#define __sysProc_h__

#ifndef FILETIME
#include <windows.h>
#endif 

#include <stdio.h>
#include <time.h>

//! Calls a command line process and retrieves the stdout and stderr output
/*!
    \param strCmdLine actual command line string to be executed. 
    \param outdata the output to stdout or stderr, double null terminated on return
    \param mode 1=stdout(default), 2=stderr
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
int CS_GetStdOut(char *strCmdLine, char **outdata, int mode=1, char *workdir=0) ; 



#define CMDPRC_CONTINUEPROCESSING       0x0001
#define CMDPRC_STOPMONITORING           0x0002
#define CMDPRC_ABORTPROCESSING          0x0004


//! Callback function to process data output from the system command 
/*!
    \param pdata pointer to a user data structure pass 
    \param pstd pointer to string data output to stdout 
    \param nstdbytes number of bytes read from the stdout stream
    \param perr pointer to the string data output to stderr
    \param nerrbytes number of bytes read from the stderr stream
    \return status codes see notes

    The return value indicates what should happen. 

            CMDPRC_CONTINUEPROCESSING - continue processing
            CMDPRC_STOPMONITORING     - stop monitoring, wait for process to stop
            CMDPRC_ABORTPROCESSING    - abort processing immediately. 

    You must call free(pstd) and/or perr if there is data defined for 
    either of the pointers. Data will only be returned if the stream 
    was requested. 


 */
typedef int (*CmdCallbackProc)(void *pdata,
                               char *pstd, int nstdbytes,
                               char *perr, int nerrbytes) ;



//! Calls a command line process and retrieves the stdout and stderr output
/*!
    \param strCmdLine actual command line string to be executed. 
    \param outdata the output to stdout or stderr
    \param pUserData pointer to user data passed to the callback function
    \param mode 0x01=stdout(default), 0x02=stderr, 0x03=both, default=1
    \return 0=OK else an error code is returned. 
        
     Returns:
         0  OK, 
        -1  couldn't create pipe
        -2  bad mode, must be 1=stdout or 2=stderr, or 0x03 = both
        -3  error creating process
      -100  insufficient memory for output data (memory allocation error)



    The function waits for up to 10 seconds for the called process to finish 
    before returning. If the called process hangs, then this function will return
    after 10 seconds, but no attempt will be made to kill the still running 
    cmdline process. 

    If the error is > -99 then no attempt was made to start the process. 
    
*/
int CS_GetStdOut(char *strCmdLine, CmdCallbackProc prcfunc, void *pUserData, int mode=1, char *workdir=0) ; 


//! From MSDN site
int UnicodeToAnsi(void *pszW, char *ppszA, int maxlen) ;


//! Print out the windows system error information
void CS_PrintLastError(FILE *fp) ;



// Convert the windows system file time stamp to a time_t value
time_t CS_FileTimeToUnixTime( const FILETIME *filetime, DWORD *remainder ) ;

// The time the file was last written
int CS_GetFileTime(char *filename, time_t &t) ;

//! Returns true if the directory exists 
/*!
    \param path  full path of directory to test for
    \param errorcode optional pointer to error code result
    \return \a true if directory exists, else returns \a false

    Calls:

        DWORD attrs = GetFileAttributes(path) ;

    And if (attrs & FILE_ATTRIBUTE_DIRECTORY) is true, then the function returns true. 
    If this flag is not set and no error results, then the path specified is probably 
    a file. Thus if the function returns false and errorcode is zero then instead of 
    being a directory the path passed in is likely an existing  file. 

    Possible errorcode return values are 

        ERROR_FILE_NOT_FOUND
        ERROR_PATH_NOT_FOUND
        ERROR_ACCESS_DENIED
        FILE_ATTRIBUTE_ARCHIVE
        FILE_ATTRIBUTE_TEMPORARY

    Look at Windows SDK help for GetFileAttributes(...) for more information.

 */
bool CS_DirExists(char *path, DWORD *errorcode=0) ;

#endif 