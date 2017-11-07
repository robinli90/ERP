// procArgs.cpp - procff arguments and support functions. 

#include "stdafx.h"
#include <windows.h>
#include "procff.h"
#include <libCMS/CMSBOMRTE.h>
#include <conio.h>
#include <list>
#include <CSstdlibs/cslib.h>

//CMSConnectionParms gCMSparms ;

RunParms::RunParms()
{
    plantMode = PLANT_EXCO ; 
    odbcName[0] = 0 ; 
    user[0] = 0 ; 
    pwd[0] = 0 ; 
    logfile[0] = 0 ; 
    taskdir[0] = 0 ; 
    taskarchive[0] = 0 ;
    bNoEcho = false ; 
    bVerification = false ; 
    bTrackAfterShipped = false ; 
    cfgfile[0] = 0 ; 
    sqllogname[0] = 0 ; 

    bVerifySolarsoft = false ; 
    bUseRoutingResource = 0 ; 

    soMaxCount = 0 ; 
    nLastMax = 0 ; 
    nLastPrefix = 0 ; 

    moveToDir[0] = 0 ; 

    memset(&isys, 0, sizeof(cwbCO_SysHandle)) ; 
    memset(&qhandle, 0, sizeof(cwbDQ_QueueHandle)) ; 
}
int ProcessArgs(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("ERROR:  too few arguments \n") ; 
        return -1 ; 
    }

    for (int i=1; i < argc; i++)
    {
        switch(argv[i][0]) 
        {
            case '-' :
                switch (argv[i][1]) 
                {
                    case 'w' :
                        if ((i + 1) >= argc)
                        {   
                            printf("ERROR: no watchdir after -w parameter.\n") ; 
                            printusage() ; 
                            return -1 ; 
                        }
                        procParms.watchDir = argv[i+1] ; 
                        i++ ; 
                        break ; 
                    case 'i' :
                        if ((i + 1) >= argc)
                        {   
                            printf("ERROR: no iSeries dir defined after -i parameter.\n") ; 
                            printusage() ; 
                            return -1 ; 
                        }
                        procParms.IBMdir = argv[i+1] ; 
                        i++ ; 
                        break ; 
                    case 'f' :
                        if ((i + 1) >= argc)
                        {   
                            printf("ERROR: no iSeries file defined after -f parameter.\n") ; 
                            printusage() ; 
                            return -1 ; 
                        }
                        procParms.IBMfile = argv[i+1] ; 
                        i++ ; 
                        break ; 
                    case 'l' :
                        if ((i + 1) >= argc)
                        {   
                            printf("ERROR: no log file defined after -l parameter.\n") ; 
                            printusage() ; 
                            return -1 ; 
                        }
                        procParms.logDirPrefix = argv[i+1] ; 
                        i++ ; 
                        break ; 
                    case 'm' :
                        if ((i + 1) >= argc)
                        {   
                            printf("ERROR: no move to file directory defined after -m parameter.\n") ; 
                            printusage() ; 
                            return -1 ; 
                        }
                        procParms.moveToDir = argv[i+1] ; 
                        i++ ; 
                        break ;
                    case 'e' :
                        if ((i + 1) >= argc)
                        {   
                            printf("ERROR: no move to error directory defined after -e parameter.\n") ; 
                            printusage() ; 
                            return -1 ; 
                        }
                        procParms.errorDir = argv[i+1] ; 
                        i++ ; 
                        break ;
                    case 'c' :
                        procParms.continueOnError = 1 ; 
                        break ; 
					case 'z' :
						if ((i + 1) >= argc)
                        {   
                            printf("ERROR: no config file name defined after -c parameter.\n") ; 
                            printusage() ; 
                            return -1 ; 
                        }
						
                        CS_strmaxcpy(gParms.cfgfile, argv[i+1], 250) ; 
                        if (LoadConfigFile())
                            return -2 ; 
                        i++ ; 
                        break ; 
                    case '-' : 
                    default :
                        printf("Unknown parameter '%s'\n", argv[i]) ; 
                        printusage() ; 
                        return -1 ; 
                        break ; 
                }
                break ; 
            default:
                printf("ERROR: unexpected parameter: '%s'\n", argv[i]) ; 
                printusage() ; 
                return -1 ; 

        }
    }

    return 0 ; 
}



int LoadConfigFile()
{
    FILE *fp = fopen(gParms.cfgfile, "rt") ; 
    if (!fp)
        return -1 ; 

    int retcode = 0; 
    char buf[1024] ; 
    while (fgets(buf, 1024, fp))
    {
        csString line(buf) ; 
        line.Trim() ; 

        if (line[0] == '#' || line.size() == 0)
            continue ; 

        csString name, val ; 
        name = line.NextToken("=", 0) ; 
        val = line.NextToken("=") ; 

        name.Trim() ; 
        val.Trim() ; 
        if (name == "DECodbc")
        {
            CS_strmaxcpy(gParms.odbcName, val.c_str(), 60) ; 
        }
        else if(name == "DECusr") 
        {
            CS_strmaxcpy(gParms.user, val.c_str(), 60) ; 
        }
        else if(name == "DECpwd") 
        {
            CS_strmaxcpy(gParms.pwd, val.c_str(), 60) ; 
        }
        else if(name == "CMSIP") 
        {
            CS_strmaxcpy(gParms.CMSIP, val.c_str(), 60) ; 
        }
        else if(name == "CMSodbc") 
        {
            CS_strmaxcpy(gParms.CMSodbc, val.c_str(), 60) ; 
        }
        else if(name == "CMSDBusr") 
        {
            CS_strmaxcpy(gParms.CMSDBusr, val.c_str(), 60) ; 
        }
        else if(name == "CMSDBpwd") 
        {
            CS_strmaxcpy(gParms.CMSDBpwd, val.c_str(), 60) ; 
        }
        else if(name == "CMSQusr") 
        {
            CS_strmaxcpy(gParms.CMSQusr, val.c_str(), 60) ; 
        }
        else if(name == "CMSQpwd") 
        {
            CS_strmaxcpy(gParms.CMSQpwd, val.c_str(), 60) ; 
        }
        else if(name == "CMSInQ") 
        {
            CS_strmaxcpy(gParms.CMSInQ, val.c_str(), 60) ; 
        }
        else if(name == "CMSOutQ") 
        {
            CS_strmaxcpy(gParms.CMSOutQ, val.c_str(), 60) ; 
        }
        else if(name == "CMSDBName") 
        {
            CS_strmaxcpy(gParms.CMSDBName, val.c_str(), 60) ; 
        }
        else if(name == "CMSPlant") 
        {
            CS_strmaxcpy(gParms.CMSPlant, val.c_str(), 60) ; 
            int plant = atoi(gParms.CMSPlant) ; 
            gParms.plantMode = plant ; 
            if (gParms.plantMode < 1 || gParms.plantMode > 3)
                printf("Error, unkown plant# = %d in the config file\n", plant) ; 
        }
        else
        {
            printf("ERROR: unknown parameter type '%s' in config file '%s'\n", name.c_str(), gParms.cfgfile) ; 
            retcode = -1 ; 
            break ; 
        }
    }
    
    fclose(fp) ; 
    return retcode ; 
}

void BuildDateName(char *nameouttmpname, char *basein) 
{
    time_t tnow ; // Year 2038 issue hear. 
    time(&tnow); 
    struct tm *ptm; 

    ptm = localtime(&tnow) ; 
    sprintf(nameouttmpname, "%s_%04d-%02d-%02d.log", 
                basein,
                ptm->tm_year + 1900, 
                ptm->tm_mon + 1, 
                ptm->tm_mday) ; 

}

csString BuildMoveDir(char *baseToDir, char *moveName, FILE *fplog)
{
    CDateTime dt ; 
    dt.SetNow() ; 
    char subdir[1024] ; 
    sprintf(subdir, "%s\\%04d%02d", procParms.moveToDir, dt.m_nYear, dt.m_nMonth) ; 
	sprintf(procParms.ffDone, "%s",subdir);
    DWORD dwAttr = GetFileAttributes(subdir);
    int dirExists = false ; 
    if(dwAttr != INVALID_FILE_ATTRIBUTES && 
       dwAttr & FILE_ATTRIBUTE_DIRECTORY)
    {   // this is a directory
        dirExists = true ; 
    }

    if (!dirExists && !CreateDirectory(subdir, 0) && fplog)
    {
        LogToFile(fplog, "ERROR: could not create directory '%s', moving to base directory\n", subdir) ; 
        strcpy(subdir, baseToDir) ; 
    }
    return AddFile2Path(subdir, moveName) ; 
}
                      


