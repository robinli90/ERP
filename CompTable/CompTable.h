#include <CSStdlibs/cslib.h>
#include <IBM/cwbdq.h>
#include <IBM/cwbcosys.h>
#include <libCMS/CMSBOMRTE.h>

#pragma once
#ifndef __COMPTABLE_H__
#define __COMPTABLE_H__
#define PLANT_EXCO              1
#define FFTEMPNAME "tempfile.txt"
struct RunParms
{
    int plantMode ; // PLANT_EXCO,PLANT_ALUDIE, or PLANT_USA
    char odbcName[64] ; // decade DB name 
    char user[64] ;     // decade DB user
    char pwd[64] ;      // decade DB pwd
    char CMSIP[64] ; 
    char CMSodbc[64] ; 
    char CMSDBusr[128] ; 
    char CMSDBpwd[128] ; 
    char CMSQusr[128] ; 
    char CMSQpwd[128] ; 
    char CMSInQ[128] ; 
    char CMSOutQ[128] ; 
    char CMSDBName[128] ; 
    char CMSPlant[128] ; 
    char logfile[256] ; 
    char taskdir[256] ; 
    char taskarchive[256] ; 
    bool bNoEcho ; 
    bool bVerification ; 
    bool bTrackAfterShipped ; 
    char cfgfile[256] ; 
    char sqllogname[256] ; 

    char moveToDir[256] ; // when null then deletes the task file
    // otherwise the taskfile is moved to this directory. 
	char ffDone[256];
    int soMaxCount ; // number of records processed since the last 
    // maximum SO# was extracted. 
    int nLastMax ; // actual maximum SO# on the last run through. 
    int nLastPrefix ; 

    bool bVerifySolarsoft ; 

    // If true then the resource is mapped to what is in CJOBDR and the station
    // map value is ignored. 
    int bUseRoutingResource ; 
    bool bDisable10100 ; 

    CMSEventProcessing evp ; // used to maintain a database connection to iSeries

    cwbCO_SysHandle isys ; 
    cwbDQ_QueueHandle qhandle ; 

    RunParms() ; 
} ;
extern RunParms gParms ;
#endif
	struct FileRef
	{
		char filename[512] ; // name of the file. 
		time_t fltime ; // time the file was found in the directory. 
		int ordernumber ;
	} ; 

csString cs_fileName;
int sonum;
csString cs_archiveFullPath;
csString cs_archiveName;
void ReProcessErrorArc();
int SQL_ConvertTime(const char *str, CDateTime &dt);
int BatchUpdChk();
int CadCompare();
int get_file_size(const char *file_name) ;
int GetFileName(char *dirname);
int CheckDirectory(char *subdir);
csString BuildMoveToName(char *prefix, int mode);