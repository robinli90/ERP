
#include "stdafx.h"
#include <windows.h>
#include <conio.h>
#include "procff.h"

int GetDirectoryList(char *dirname, FileRefMap &frl)
{
    frl.clear() ; 

    csString listDir(dirname) ; 
    listDir += "\\*" ; 

    int filecount = 0 ; 
    WIN32_FIND_DATA findData ; 
    HANDLE hFind = FindFirstFile(listDir.c_str(), &findData) ; 
    if (hFind == INVALID_HANDLE_VALUE)
    {   // OUTOFMEMORY
        DWORD errnum = GetLastError() ; 
        if (errnum != ERROR_FILE_NOT_FOUND)
        {
            LogToFile(procParms.fplog, 
                "Invalid File Handle. Get Last Error reports %d\n", errnum) ;
        }
    } 
    else 
    {
        FileRef fref ; 
        do {
            if (!CS_IsDots(findData.cFileName) && 
                !(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                && !strstr(findData.cFileName, FFTEMPNAME))
            {
                strcpy(fref.filename, findData.cFileName) ;
                time(&(fref.fltime)) ; 
                char *pls = strrchr(fref.filename, '\\') ; 
                if (pls)
                    pls++ ; 
                else
                    pls = fref.filename ; 
                fref.ordernumber = atoi(pls) ; 
                FileRefSort frsort ; 
                
                frsort.order = fref.ordernumber ; 
                frsort.rectime = 0 ; 
                
                char *pus1 = strrchr(fref.filename, '_') ; 
                char *pus2 = 0 ; 
                if (pus1)
                {
                    pus2 = pus1 ;
                    pus2-- ; 
                    while (pus2 >= fref.filename)
                    {
                        if (*pus2 == '_')
                            break ; 
                        pus2-- ; 
                    }

                    pus1++ ; 
                    pus2++ ; 

                    if (isdigit(*pus1) && isdigit(*pus2))
                    {
                        struct tm t ; 
                        memset(&t, 0, sizeof(struct tm)) ; 
                        sscanf(pus1, "%02d%02d%02d", &t.tm_hour, &t.tm_min, &t.tm_sec) ; 
                        sscanf(pus2, "%04d%02d%02d", &t.tm_year, &t.tm_mon, &t.tm_mday) ; 
                        t.tm_year -= 1900 ; 
                        t.tm_mon -=1 ; 
                        frsort.rectime = mktime(&t) ; 
                    }
                }

                frl.insert(make_pair(frsort, fref)) ; 
            }
        } while (FindNextFile(hFind, &findData)) ;

        FindClose(hFind);
    }

    return (int)frl.size() ; 
}

int FindTmpCount(TmpVarVec &tmpv, TmpVar &tvar)
{
    int i = 0 ; 
    while (i < (int)tmpv.size()) 
    {
        if (strcmp(tmpv[i].srctmp, tvar.srctmp) == 0)
            return i ; 
        i++ ; 
    }

    return - 1 ; 
}

int CheckDirectory(char *subdir)
{
    DWORD dwAttr = GetFileAttributes(subdir);
    int dirExists = false ; 
    if(dwAttr != INVALID_FILE_ATTRIBUTES && 
       dwAttr & FILE_ATTRIBUTE_DIRECTORY)
    {   // this is a directory
        dirExists = true ; 
    }

    int ret = 0 ; 
    if (!dirExists && !CreateDirectory(subdir, 0))
    {
        LogToFile(procParms.fplog, 
            "ERROR: could not create directory '%s', moving to base directory\n", subdir) ; 
        strcpy(subdir, procParms.moveToDir.c_str()) ; 
        ret = -1 ;
    }
    return ret ; 
}

//! Create the moveToDir path name
csString BuildMoveToName(char *prefix, int mode)
{
    csString movename(prefix) ;

    char datestr[64] ; 
    CDateTime dtime ; 
    dtime.SetNow() ; 
    dtime.FormatDateTimeSecs(datestr, 1) ;
    if (mode == 0)
        movename += datestr + csString(".txt") ; 
    else if (mode == 2)
        movename = "IGNORED_" + movename  ;

    csString movedir(procParms.moveToDir) ; 
    CDateTime dt ; 
    dt.SetNow() ; 
    char subdir[1024] ; 
    sprintf(subdir, "%s\\%04d%02d", movedir.c_str(), 
                        dt.m_nYear, dt.m_nMonth) ; 
	sprintf(procParms.ffDone, "%s",subdir);
    // INVALID_FILE_ATTRIBUTES

    CheckDirectory(subdir) ; 

    return AddFile2Path(subdir, movename) ; 
}

csString BuildMoveToName2(char *prefix, int mode)
{
    csString movename(prefix) ;

    char datestr[64] ; 
    CDateTime dtime ; 
    dtime.SetNow() ; 
    dtime.FormatDateTimeSecs(datestr, 1) ;
    if (mode == 0)
        movename += datestr + csString(".txt") ; 
    else if (mode == 2)
        movename = "IGNORED_" + movename  ;

    csString movedir = "ReRunDone\\"; 
    CDateTime dt ; 
    dt.SetNow() ; 
    char subdir[1024] ; 
    sprintf(subdir, "%s\\%04d%02d", movedir.c_str(), 
                        dt.m_nYear, dt.m_nMonth) ; 
	sprintf(procParms.ffDone, "%s",subdir);
    // INVALID_FILE_ATTRIBUTES

    CheckDirectory(subdir) ; 

    return AddFile2Path(subdir, movename) ; 
}
// Transfer failed invidual SO# to another folder
csString MoveFailedFile(char *dirname, csString path)
{
	return AddFile2Path(dirname, path) ; 
}
