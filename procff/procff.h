// procff.h - variable and function prototypes for the FlatFile merge processor 

//  -w c:\cms\ff  -i q:\RTEBOMP1 -f FF.txt -l c:\cms\log\FF  -m c:\cms\FFdone
//  -w c:\cms\ff  -i C:\RTEBOMP1 -f FF.txt -l c:\cms\log\FF  -m c:\cms\FFdone


#pragma once
#ifndef __PROCFF_H__
#define __PROCFF_H__

#include <CSStdlibs/cslib.h>
#include <IBM/cwbdq.h>
#include <IBM/cwbcosys.h>
#include <libCMS/CMSBOMRTE.h>
#define FFTEMPNAME "procFF_tempfile.txt"

// Error messages are output to the log file which is named procff_YYYYMMDD.log

// If defined then the processed files are copied to the directory ARCHIVEDIR\YYYYMM
// where a subdirectory is created with the current date (year and month). Thus all 
// files for one month are stored in a single directory (should be a couple thousand
// files or so per plant.). The files are not renamed, they should already have a
// timestamp and unique name coding. 


// ===========================
// Data structure definitions
// ===========================
struct ProcFFSetup
{
    csString watchDir ; 
    csString IBMdir ; 
    csString IBMfile ; 
    csString logDirPrefix ; 
    csString moveToDir ; 
    csString errorDir ; 
    int continueOnError ; 
	char ffDone[256];

	//bool rerun;

    FILE *fplog ; 
    char curLog[1024] ; 

    int tmpCount ; 

    // Constructor. 
    ProcFFSetup() 
    {
        fplog = 0 ; 
        continueOnError = 0 ;
        curLog[0] = 0 ; 
        Reset() ; 
    }

    void Reset() 
    {
        tmpCount = 1 ;
    }
} ; 

struct FileRef
{
    char filename[512] ; // name of the file. 
    time_t fltime ; // time the file was found in the directory. 
    int ordernumber ;
} ; 


struct TmpVar
{
    char srctmp[16] ; // value of temp var in the input file
    int count ; // TMPn count in the output file that it was mapped to. 
} ; 

typedef vector<TmpVar> TmpVarVec ; 

struct FileRefSort
{
    int order ; 
    time_t rectime ; 

    // Needed for the multimap
    friend bool operator<(const FileRefSort &a, const FileRefSort &b)
    {
        if (a.order < b.order)
            return true ; 
        if (a.order > b.order)
            return false ; 
       
        // Want to reverse the time sort
        if (a.rectime > b.rectime)
            return true ; 
        if (a.rectime < b.rectime)
            return false ; 
        return false ; // they are equal. 
    }

} ;

#define PLANT_EXCO              1
#define PLANT_ALUDIE            2
#define PLANT_USA               3

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

typedef multimap<FileRefSort, FileRef> FileRefMap ; 
typedef multimap<FileRefSort, FileRef>::iterator FileRefMapItr ; 


extern ProcFFSetup procParms ; 
extern RunParms gParms ;

// ===========================
// Function Prototypes
// ===========================
void printusage() ; 
int ProcessArgs(int argc, char* argv[]) ;

//! Append the _YYYY-MM-DD.log to prefix string
void BuildDateName(char *nameouttmpname, char *basein) ; 
//! Make sure sub dir YYYYMM exists within the base to dir. And then 
//! append the move name to the sub directory  
csString BuildMoveDir(char *baseToDir, char *moveName, FILE *fplog) ;
csString MoveFailedFile(char *dirname, csString path);
// Retreives a list of all files in the dirname directory, 
// Returns number of files found. 
int GetDirectoryList(char *dirname, FileRefMap &frl) ;

//! Process the current list of files
int ProcessFileSet(FileRefMap &frl) ;
int ProcessFileSet2(FileRefMap &frl) ;
int LoadConfigFile();
int GetSOName(char *dirname);
//! Return index of tvar within tmpv, returns -1 if not found. 
int FindTmpCount(TmpVarVec &tmpv, TmpVar &tvar) ;

int CheckRecord(int sonum);

int UpdateRecord (int sonum, char condition);
int InsertRecord (int sonum, char condition);

int SOToFile(FILE *fp, const char *formatstr, ...);
int GetSO(FILE *fp);
int CheckProcess (int sonum);
void reRun();
//! Create the moveToDir path name
/*!
    \param prefix this string is pre-pended to the output filename
    \param mode if 1 then don't append the date_time.txt extension
    \return the resultant file pathname

    The input RTE/BOM file or the merged temporary flat file is moved or 
    copied to the same directory. The naming of the merged file is a constant
    format whereas the CAD/CAM workstation names will typically be used
    and then have the current date and time appended. 

    The format of the file name returned is:

        <moveToDir>\<prefix>_YYYYMMDD_HHMMSS.txt

 */
csString BuildMoveToName(char *prefix, int mode=0) ;
csString BuildMoveToName2(char *prefix, int mode=0) ;

#endif
