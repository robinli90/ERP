
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
****************************************************************************/ 
 
// strings.cpp

#ifdef _WIN32
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include "datefunc.h"
#include "cs_filelog.h"

int LogToFile(FILE *fp, const char *formatstr, ...) 
{
    if (!fp)
        return -1 ; // can't, file doesn't exist. 

    int retcode = 0 ; 
    va_list marker;
    va_start(marker, formatstr);     // Initialize variable arguments
    try {
        CDateTime dt ; 
        dt.SetNow() ; 
        char timestr[64] ; 
        dt.FormatDateTimeSecs(timestr) ; 
        fprintf(fp, "%s:", timestr) ; 
        vfprintf(fp, formatstr, marker) ;
        fflush(fp) ; 
    }
    catch(...)
    {
        retcode = -2 ; 
    }
    va_end(marker) ; 

    return retcode ; 
}


int LogToFile2(FILE *fp, FILE *fp2, const char *formatstr, ...) 
{
    if (!fp)
        return -1 ; // can't, file doesn't exist. 

    int retcode = 0 ; 
    va_list marker;
    va_start(marker, formatstr);     // Initialize variable arguments
    try {
        CDateTime dt ; 
        dt.SetNow() ; 
        char timestr[64] ; 
        dt.FormatDateTimeSecs(timestr) ; 
        fprintf(fp, "%s:", timestr) ; 

        vfprintf(fp, formatstr, marker) ;
        fflush(fp) ; 
        if (fp2)
        {
            fprintf(fp2, "%s:", timestr) ; 
            vfprintf(fp2, formatstr, marker) ;
            fflush(fp2) ; 
        }
    }
    catch(...)
    {
        retcode = -2 ; 
    }
    va_end(marker) ; 

    return retcode ; 
}


// ======================================================================
// ======================================================================
// ====================    CS_FileLog Member Functions   ================
// ======================================================================
// ======================================================================

CS_FileLog::CS_FileLog()
{
    clear() ; 
}

CS_FileLog::CS_FileLog(char *filename)
{
    clear() ; 
    SetPathName(filename) ; 
}

void CS_FileLog::clear()
{
    fp = 0 ; 
    mode = 0 ; 
    lastLog = 0 ; 
    lastSec = 0 ; 
    lastMin = 0 ; 
    lastHour = 0 ; 
    lastDay = 0 ; 
    lastMonth = 0 ; 
    lastYear = 0 ; 
}

CS_FileLog::~CS_FileLog()
{
    if (fp)
        fclose(fp) ; 
    fp = 0 ; 
}

int CS_FileLog::SetPathName(char *pathname)
{
    if (fp)
        fclose(fp) ; 
    csBasePathName = pathname ; 
    csString flname ; 
    SplitPathAndFile(csBasePathName, csBasePath, flname) ; 
    SplitFileAndExtension(flname, csBaseName, csBaseExt) ; 
    return 0 ; 
}

int CS_FileLog::CurrentFileName()
{
    time_t tnow ; 
    time(&tnow); 
    struct tm *ptm ; 
    ptm = localtime(&tnow) ; 

    if (!mode)
    {   // nothing to do, the log file name is static
        if (!fp)
            fp = fopen(csBasePathName.c_str(), "wt") ; 
        lastLog   = tnow ; // just save the current time
        lastSec   = ptm->tm_sec ; 
        lastMin   = ptm->tm_min ; 
        lastHour  = ptm->tm_hour ; 
        lastDay   = ptm->tm_mday ; 
        lastMonth = ptm->tm_mon + 1 ; 
        lastYear  = ptm->tm_year + 1900 ; 
        return 0 ; 
    }
    
    // Else continue to work out what the current file name should be
    unsigned int timestat = 0 ; 
    unsigned int nowSec     = ptm->tm_sec ; 
    unsigned int nowMin     = ptm->tm_min ; 
    unsigned int nowHour    = ptm->tm_hour ; 
    unsigned int nowDay     = ptm->tm_mday ; 
    unsigned int nowMonth   = ptm->tm_mon + 1 ; 
    unsigned int nowYear    = ptm->tm_year + 1900 ; 

    if (nowYear != lastYear)
    {
        timestat |= YEAR_CHANGED ; 
        timestat |= MONTH_CHANGED ; 
        timestat |= DAY_CHANGED ; 
        timestat |= HOUR_CHANGED ; 
        timestat |= NAME_CHANGED ; 
    }
    else if (nowMonth != lastMonth)
    {
        timestat |= MONTH_CHANGED ; 
        timestat |= DAY_CHANGED ; 
        timestat |= HOUR_CHANGED ; 
        if (mode & (ROLLOVER_MONTHLY | ROLLOVER_DAILY | ROLLOVER_HOURLY))
            timestat |= NAME_CHANGED ; 
    }
    else if (nowDay != lastDay)
    {
        timestat |= DAY_CHANGED ; 
        timestat |= HOUR_CHANGED ; 
        if (mode & (ROLLOVER_DAILY | ROLLOVER_HOURLY))
            timestat |= NAME_CHANGED ; 
    }
    else if (nowHour != lastHour)
    {
        timestat |= HOUR_CHANGED ; 
        if (mode & ROLLOVER_HOURLY)
            timestat |= NAME_CHANGED ; 
    }


    if (timestat & NAME_CHANGED) 
    {
        char tmpstr[256] ; 

        if ((mode & APPEND_DATE) && (mode & APPEND_TIME))
        {   // Want both date and time
            if (csBaseExt.size())
            {
                sprintf(tmpstr, "%s_%04d-%02d-%02d_%02d%02d%02d.%s", 
                        csBaseName.c_str(), 
                        nowYear, nowMonth, nowDay, 
                        nowHour, nowMin, nowSec, 
                        csBaseExt.c_str()) ; 
            }
            else
            {   // no extension
                sprintf(tmpstr, "%s_%04d-%02d-%02d_%02d%02d%02d", 
                        csBaseName.c_str(), 
                        nowYear, nowMonth, nowDay, 
                        nowHour, nowMin, nowSec) ; 
            }
        }
        else if (mode & APPEND_DATE)
        {
            if (csBaseExt.size())
            {
                sprintf(tmpstr, "%s_%04d-%02d-%02d.%s", 
                        csBaseName.c_str(), 
                        nowYear, nowMonth, nowDay, 
                        csBaseExt.c_str()) ; 
            }
            else
            {   // no extension
                sprintf(tmpstr, "%s_%04d-%02d-%02d", 
                        csBaseName.c_str(), 
                        nowYear, nowMonth, nowDay) ; 
            }
        }
        else if (mode & APPEND_TIME)
        {
            if (csBaseExt.size())
            {
                sprintf(tmpstr, "%s_%02d%02d%02d.%s", 
                        csBaseName.c_str(), 
                        nowHour, nowMin, nowSec, 
                        csBaseExt.c_str()) ; 
            }
            else
            {   // no extension
                sprintf(tmpstr, "%s_%02d%02d%02d", 
                        csBaseName.c_str(), 
                        nowHour, nowMin, nowSec) ; 
            }
        }

        csString newfilename = tmpstr ; 
        if (csBaseExt.size())
        {
            newfilename += "." ; 
            newfilename += csBaseExt ; 
        }

        tmpstr[0] = 0 ; 
        if (mode & SUBDIR_HOURLY)
            sprintf(tmpstr, "%04d%02d%02d%02d", nowYear, nowMonth, nowDay, nowHour) ; 
        else if (mode & SUBDIR_DAILY)
            sprintf(tmpstr, "%04d%02d%02d", nowYear, nowMonth, nowDay) ; 
        else if (mode & SUBDIR_MONTHLY)
            sprintf(tmpstr, "%04d%02d", nowYear, nowMonth) ; 
        else if (mode & SUBDIR_YEARLY)
            sprintf(tmpstr, "%04d", nowYear) ; 

        if (tmpstr[0])
        {
            csCurFileName = AddFile2Path(csBasePath, tmpstr) ; 
            DWORD dwAttr = GetFileAttributesA(csCurFileName.c_str());
            int dirExists = false ; 
            if(dwAttr != INVALID_FILE_ATTRIBUTES && 
               dwAttr & FILE_ATTRIBUTE_DIRECTORY)
            {   // this is a directory
                dirExists = true ; 
            }

            if (!dirExists)
                CreateDirectoryA(csCurFileName.c_str(), 0) ;
        }

        csCurFileName = AddFile2Path(csCurFileName, newfilename) ; 
        fclose(fp) ; 
        fp = fopen(csCurFileName.c_str(), "wt") ; 
    }

    lastLog   = tnow ; 
    lastSec   = nowSec ;
    lastMin   = nowHour ;
    lastHour  = nowHour ; 
    lastDay   = nowDay ; 
    lastMonth = nowMonth ; 
    lastYear  = nowYear ; 

    return timestat ; 
}

int CS_FileLog::Write(const char *formatstr, ...) 
{
    CurrentFileName() ; // make sure the file name is valid and do
    // rollovers as required

    if (!fp)
        return -1 ; // can't, file doesn't exist. 

    int retcode = 0 ; 
    va_list marker;
    va_start(marker, formatstr);     // Initialize variable arguments
    try {
        CDateTime dt(lastYear, lastMonth, lastDay, lastHour, lastMin, lastSec) ; 
        char timestr[64] ; 
        dt.FormatDateTimeSecs(timestr) ; 
        fprintf(fp, "%s:", timestr) ; 
        vfprintf(fp, formatstr, marker) ;
        fflush(fp) ; 
    }
    catch(...)
    {
        retcode = -2 ; 
    }
    va_end(marker) ; 

    return retcode ; 
}

