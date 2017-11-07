// BaalV2.h

// See readme.txt also
// New version without the --XDOWN option since we need to track the down event. 
// --RTER -v --tship -c cfgfile.ini -d t:\acct\PRODcmds -r -l c:\cms\log\baallog -s c:\cms\log\baalsql -t c:\cms\log\taskarc -m c:\cms\taskdone 
// --RTER -v --tship -c cfgfile.ini -d c:\cms\cmds -r -l c:\cms\log\baallog -s c:\cms\log\baalsql -t c:\cms\log\taskarc -m c:\cms\taskdone 
//
// Based on Chris Braznick's description of the 10100 down code, the clock doesn't stop until
// the system sees the down event. This contradicts what Joey (and others) have described but
// should be better overall if this can be made to work with the down events included. 
// --RTER -v --tship --XDOWN -c cfgfile.ini -d t:\acct\PRODcmds -r -l c:\cms\log\baallog -s c:\cms\log\baalsql -t c:\cms\log\taskarc -m c:\cms\taskdone 
// --RTER -v --tship --XDOWN -c cfgfile.ini -d c:\cms\cmds -r -l c:\cms\log\baallog -s c:\cms\log\baalsql -t c:\cms\log\taskarc -m c:\cms\taskdone 
// --RTER -v --tship -c cfgfile.ini -d --RTER -v --tship -c cfgfile.ini -d c:\cms\cmds -r -l c:\cms\log\baallog -s c:\cms\log\baalsql -t c:\cms\log\taskarc -m c:\cms\taskdone 
// --RTER -XS -v --tship -c cfgfile.ini -d --RTER -v --tship -c cfgfile.ini -d c:\cms\cmds -r -l c:\cms\log\baallog -s c:\cms\log\baalsql -t c:\cms\log\taskarc -m c:\cms\taskdone 


/*

M	0067296   	500	1	HD 8 X 5            	HD 8 X 5 BACKER     	HOLLOW 8 X 5 BACKER           	1.0000	EA 	1.00	            	M	1	   	                  	Y	Y	0.0	R	001PRD	         	0.00000	         	0	 	Y	N	          	          	          	                    	0.00000	0.00000	 	 	 	 	 	     	     	                    	0.00000	   	
M	0067296   	500	2	HD 8 X 5            	HD 8 X 5 MANDREL    	HOLLOW 8 X 5 MANDREL          	1.0000	EA 	1.00	            	M	1	   	                  	Y	Y	0.0	R	001PRD	         	0.00000	         	0	 	Y	N	          	          	          	                    	0.00000	0.00000	 	 	 	 	 	     	     	                    	0.00000	   	
M	0067296   	500	3	HD 8 X 5            	HD 8 X 5 PLATE      	HOLLOW 8 X 5 PLATE            	1.0000	EA 	1.00	            	M	1	   	                  	Y	Y	0.0	R	001PRD	         	0.00000	         	0	 	Y	N	          	          	          	                    	0.00000	0.00000	 	 	 	 	 	     	     	                    	0.00000	   	
M	0068015   	500	1	HD 11 X 6           	HD 11 X 6 BACKER    	HOLLOW 11 X 6 - BACKER        	1.0000	EA 	1.00	            	M	0	   	                  	Y	Y	0.0	R	001PRD	         	0.00000	         	0	 	Y	N	          	          	          	                    	0.00000	0.00000	 	 	 	 	 	     	     	                    	0.00000	   	
M	0068015   	500	2	HD 11 X 6           	HD 11 X 6 MANDREL   	HOLLOW 11 X 6 - MANDREL       	1.0000	EA 	1.00	            	M	0	   	                  	Y	Y	0.0	R	001PRD	         	0.00000	         	0	 	Y	N	          	          	          	                    	0.00000	0.00000	 	 	 	 	 	     	     	                    	0.00000	   	
M	0068015   	500	3	HD 11 X 6           	HD 11 X 6 PLATE     	HOLLOW 11 X 6 - PLATE         	1.0000	EA 	1.00	            	M	0	   	                  	Y	Y	0.0	R	001PRD	         	0.00000	         	0	 	Y	N	          	          	          	                    	0.00000	0.00000	 	 	 	 	 	     	     	                    	0.00000	   	
M	0068017   	500	1	HD 11 X 6           	HD 11 X 6 BACKER    	HOLLOW 11 X 6 - BACKER        	1.0000	EA 	1.00	            	M	0	   	                  	Y	Y	0.0	R	001PRD	         	0.00000	         	0	 	Y	N	          	          	          	                    	0.00000	0.00000	 	 	 	 	 	     	     	                    	0.00000	   	
M	0068017   	500	2	HD 11 X 6           	HD 11 X 6 MANDREL   	HOLLOW 11 X 6 - MANDREL       	1.0000	EA 	1.00	            	M	0	   	                  	Y	Y	0.0	R	001PRD	         	0.00000	         	0	 	Y	N	          	          	          	                    	0.00000	0.00000	 	 	 	 	 	     	     	                    	0.00000	   	
M	0068017   	500	3	HD 11 X 6           	HD 11 X 6 PLATE     	HOLLOW 11 X 6 - PLATE         	1.0000	EA 	1.00	            	M	0	   	                  	Y	Y	0.0	R	001PRD	         	0.00000	         	0	 	Y	N	          	          	          	                    	0.00000	0.00000	 	 	 	 	 	     	     	                    	0.00000	   	

-- select * from prodtest.cjobdr where edjob# = '0068017'
-- select * from prodtest.cjobdr 
-- select * from prodtest.cjobdm where efjob# = '0068017'
-- select * from prodtest.cjobh where DNJOB = '0068017'
-- select * from prodtest.cjobdr where edjob# = '0067296' or edjob# = '0068016'

-- select * from prodtest.sftx where Q4ftcd = 10002   
select * from prodtest.sftx where Q4JOBN = '0068017' order by q4cdat desc, q4ctim desc 
-- select * from prodtest.cjobdm where efjob# = '0068017' or efjob# = '0067296' or efjob# = '0068015'
-- select eftype, efjob#,efseq#, eflin#, efpart, efmtlp, eflead from prodtest.cjobdm where efjob# = '0068017' or efjob# = '0067296' or efjob# = '0068015'


*/

// #include "SQLDatabase.h"
// #include "SQLRecordset.h"

// Constants 

#define BATCH_MODE      1 

#define DB_ERROR                -1
#define BAD_TASK_DATA           -2
#define ALREADY_SHIPPED         -3
#define HARDNESS_ERROR          -20
#define BAD_ORDER_NUMBER        -4 
#define BAD_TASK_SONUM          -5
#define TASK_ERR_TYPE           -100
#define TASK_ERR_SONUM          -101
#define TASK_ERR_TASKCODE       -102
#define TASK_ERR_TIME           -103
#define TASK_ERR_STATION        -104
#define TASK_ERR_STATION2       -105
#define TASK_ERR_NOFILE         -106
#define TASK_ERR_TB_EMP        -107
#define TASK_ERR_TB_PART       -108
#define TASK_ERR_TB_QTY        -109
#define TASK_ERR_TB_SERNUM     -110
#define TASK_ERR_TB_TIME       -111
#define TASK_ERR_TB_STATION    -112
#define TASK_ERR_TB_MTL        -113


/*!
 A standard task file line looks like:

TASK|49192|10178|DSPL|10/15/2008 15:28:12|DSTP

  Where:
    TASK indicates that it is a standard task
    FORCE indicates that this record should be tracked no matter what 
          even if the order has already been shipped or invoiced.
          Or in other words force the record to be processed. 

    49192 is the SO#
    10178 is the employee number
    Within DSPL
        DS is the task
        PL is the part 
    The date/time is in MM/DD/YYYY HH:MM:SS format 
    DSTP is the station code. 

    Fields are delimited with the vertical bar character |        

Runtime records look like:

RUNTIME|24639|10072|WOPL|030:00|WOUT
RUNTIME|so#|emp#|TTPP|runtime-hours|station

    where the runtime is in HHH:MM format meaning that you can have [0,999] 
    total job hours (thus a maximum of just over 41.6 days for a single job)


Saw records look like:

SAW|25195|10095|SWPL|66|08/05/2010 10:30:38|SAW1
SAW|so#|emp#|TTPP|ser#|datetime|station


   Turned blanks lines look like 

TBLANK|emp#|part#|qty|ser#|station|datetime

Where part# is the actual CMS part# of the turned or hardened blank. 
datetime must be in YYYYMMDDHHMMSS format as a single string


PICK|emp#|jobpart|part#|ser#|station|datetime

For example, the actual part:

PICK|10100|28435P|HB 10 X 2|123|PPRT|YYYYMMDDHHMMSS


 */

struct TaskRec
{
    //! Bit states within mode. 
    enum {
        STANDARD    = 0x01,  // standard TASK type events
        FORCE       = 0x02,  // Add to d_task even if shipped
        RUNTIME     = 0x04,  // RUNTIME events where the end time is calculated. 
        SAWMODE     = 0x08,  // SAW Mode where we need a 30000 + Serial number
        TBLANKS     = 0x10,  // turned blanks
        PICKPRT     = 0x20,  // pick part from stock
    } ; 
    int mode ; 

    char plant[8] ; // used only for Solarsoft/CMS mode processing

    int sonum ; 
    int empnum ; 
    char task[6] ;
    char station[16] ; 
    char part[32] ; 
    int year ; 
    int month ; 
    int day ; 
    int hour ; 
    int mins ; 
    int secs ; 
    char serNumStr[32] ; 
    int qty ; 
    char mtl[48] ; 

    time_t tasktime ; // same as the time defined above. 
    time_t filetime ; // time stamp on the task file that contained task. 

    double runtime ; 
    double length ; // material length - not used currently. 


    int mappedSO ; 

    int ParseString(char *buf) ; 
    bool IsForced()   { return mode & FORCE ? true : false ; } ; 
    bool IsStandard() { return mode & STANDARD ? true : false ; } ; 

    int SaveToDB(CSQLDatabase &db, FILE *fp) ; 
    int SaveToCMSDB(CCMSDatabase &db, FILE *fplog) ;


    //! Returns true if the task was read back successfully from the Database. 
    bool VerifyDBRecord(CSQLDatabase &db, FILE *fplog) ; 

    //! Returns -1 if there is no next token or it contains invalid characters
    /*!
        if len != 0  then the token must be exactly that many characters 
        long. 
     */
    int NextTaskToken(csString &line, csString &tok, int len=0) ; 
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

struct FileRef
{
    char filename[256] ; // name of the file. 
    time_t fltime ; // time the file was found in the directory. 
    time_t flsystime ; // last write time for file from OS
} ; 

typedef list<FileRef> FileRefList ; 
typedef list<FileRef>::iterator FileRefListItr ; 
 
// Resource window records
struct ResWinRec {
    int stopEvent ; // the associated stop event to the fromstop time
    int startEvent ; // the event associated with the tostart time. 
    time_t fromstop ; // this is the start of the free time window 
    time_t tostart ;  // this is the end of the free time window. If none exists then it is
    // loaded with the current system time. 
} ;

typedef vector<ResWinRec> ResWinRecVec ; 
typedef vector<ResWinRec>::iterator ResWinRecVecItr ; 


class BaalFileProcessor
{
public: 
    CCMSDatabase *pdb ;
    csString taskfile ;
    csString taskstr ; 
    csString msg ;
    FILE *fpsql ;
    FILE *fplog ;
    FILE *fparchive ;

    //! Data queue processing
    int ProcessFile(csString &taskfilename, time_t filetime) ; 
    
    //! Batch mode processing
    int ProcessFileBatch(csString &taskfilename, time_t filetime) ; 

    int GetEndTimeFromSolarSoft(RunParms &rparms, TaskRec &task, time_t taskfiletime, TaskRec &taskstart) ; 
    int GetEndTimeFromDecade(RunParms &rparms, TaskRec &task, time_t taskfiletime, TaskRec &taskstart) ; 
    int SaveTaskToDecade(TaskRec &task, csString &taskline) ;

    int LoadResourceWindows(RunParms &rparms, TaskRec &endtask) ;

} ; 

extern RunParms gParms ; // global parameters definition
extern BaalFileProcessor bfp ; 

extern int noDecadeTracking ; 
extern int noCMSTracking ; 


// Function prototypes

int MappedSONUM(CSQLDatabase &db, int inputSO) ; 
int MappedSONUM(int inputSO) ; 

// Order exists and shipdate is NULL
//! Returns 0 no record found or DB error, 0x01=read record, 0x02=shipdate is set. 
int ValidActiveOrder(CSQLDatabase &db, TaskRec &task, int outputMode) ;

csString BuildMoveDir(char *baseToDir, char *moveName, FILE *fplog) ; 

time_t FileTimeToUnixTime( const FILETIME *filetime, DWORD *remainder) ;

int LogToFileAndStdout(FILE *fp, const char *formatstr, ...) ;
int LogToFileAndStdoutNT(FILE *fp, const char *formatstr, ...)  ;

void BAALPrintLastError(FILE *fp) ;

int ArchiveTaskFile(csString &fileName, FILE *fplog) ;

int CMSMappedSONUM(int inputSO) ;
int ProcessHardnessRec(CCMSDatabase &db, char *buffer, csString &msg, FILE *fpsql, int batchMode=0, time_t=0) ;
int LogTask(int nResult, FILE *fparchive, FILE *fplog, csString &taskString, csString &msg) ;

