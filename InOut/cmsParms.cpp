// cmsParms.cpp


#include "stdafx.h"
#include <csstdlibs/cslib.h>
#include <libCMS\CMSBOMRTE.h>

CMSConnectionParms::CMSConnectionParms() 
{
}

CMSConnectionParms::~CMSConnectionParms() 
{
}


int CMSConnectionParms::LoadConfigFile(const char *configname, FILE *fpmsg)
{
    cfgfile[0] = 0 ; 
    FILE *fp = fopen(configname, "rt") ; 
    if (!fp)
    {
        if (fpmsg)
        {
            fprintf(fpmsg, "Error opengin CMScfg.ini file '%s'\n", configname) ; 
            fflush(fpmsg) ; 
        }
        return -1 ; 
    }

    strcpy(cfgfile, configname) ; // save this filename

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
            CS_strmaxcpy(decDBname, val.c_str(), 60) ; 
        }
        else if(name == "DECusr") 
        {
            CS_strmaxcpy(decDBusr, val.c_str(), 60) ; 
        }
        else if(name == "DECpwd") 
        {
            CS_strmaxcpy(decDBpwd, val.c_str(), 60) ; 
        }
        else if(name == "CMSIP") 
        {
            CS_strmaxcpy(ibmhost, val.c_str(), 60) ; 
        }
        else if(name == "CMSodbc") 
        {
            CS_strmaxcpy(odbc, val.c_str(), 60) ; 
        }
        else if(name == "CMSDBusr") 
        {
            CS_strmaxcpy(dbusr, val.c_str(), 60) ; 
        }
        else if(name == "CMSDBpwd") 
        {
            CS_strmaxcpy(dbpwd, val.c_str(), 60) ; 
        }
        else if(name == "CMSQusr") 
        {
            CS_strmaxcpy(DQusr, val.c_str(), 60) ; 
        }
        else if(name == "CMSQpwd") 
        {
            CS_strmaxcpy(DQpwd, val.c_str(), 60) ; 
        }
        else if(name == "CMSInQ") 
        {
            CS_strmaxcpy(inputQ, val.c_str(), 60) ; 
        }
        else if(name == "CMSOutQ") 
        {
            CS_strmaxcpy(outputQ, val.c_str(), 60) ; 
        }
        else if(name == "CMSDBName") 
        {
            CS_strmaxcpy(dbname, val.c_str(), 60) ; 
        }
        else if(name == "CMSPlant") 
        {
            CS_strmaxcpy(plantID, val.c_str(), 60) ; 
            int plant = atoi(plantID) ; 
            if (plant < 1 || plant > 3)
            {
                if (fpmsg)
                {
                    fprintf(fpmsg, "Error, unknown plant# = %d in the config file\n", plant) ; 
                    fflush(fpmsg) ; 
                }
            }
        }
        else if(name == "SEQSPLIT") 
        {
            seqSplit = atoi(val.c_str()) ; 
        }
        else if(name == "SEQMERGE") 
        {
            seqMerge= atoi(val.c_str()) ; 
        }
         else if(name == "BATCH") 
        {
            CS_strmaxcpy(batchDir, val.c_str(), 250) ; 
        }
        else
        {
            if (fpmsg)
            {
                fprintf(fpmsg, "ERROR: unknown parameter type '%s' in config file '%s'\n", name.c_str(), cfgfile) ; 
                fflush(fpmsg) ; 
            }
            retcode = -2 ; 
            break ; 
        }
    }
    
    fclose(fp) ; 
    return retcode ; 
}
