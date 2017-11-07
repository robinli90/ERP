#pragma once

#ifndef _CMSBOMRTE_H_
#define _CMSBOMRTE_H_

#include <CSstdlibs/cslib.h>
// #include <ugutils.h>
#include <vector>
#include "CMSDatabase.h"
#include "routeUpdDef.h"
#include "flatfile.h"

// Include the necessary DQ Classes
#include <IBM/cwbdq.h>
#include <IBM/cwbsv.h>
#include <IBM/cwbrc.h>

#define EVENTS_OUTPUT_DECADE    0x01
#define EVENTS_OUTPUT_SOLARSOFT 0x02

// Basic part definitions
#define TYPE_FDR        0x0001
#define TYPE_MND        0x0002
#define TYPE_PLT        0x0004
#define TYPE_BKR        0x0008
#define TYPE_BOL        0x0010
#define TYPE_SUB        0x0020
#define TYPE_RNG        0x0040
#define TYPE_HOLLOW     0x0100

/*
    NOTE: the current Solarsoft part naming convention does not allow
    for sub-backers or sub-bolsters, but they are included here for the 
    future just in case that level of detail will be required. 
 */

#define GLOBAL_MASTER_PARTCODE  'G' 
#define FEEDER_PARTCODE         'F' 
#define MANDREL_PARTCODE        'M' 
#define PLATE_PARTCODE          'P' 
#define BACKER_PARTCODE         'B' 
#define SUBBACKER_PARTCODE      'K' 
#define BOLSTER_PARTCODE        'L' 
#define SUBBOLSTER_PARTCODE     'S' 
#define RING_PARTCODE           'R' 
#define INSERT_PARTCODE         'I' 
#define BOLT_PARTCODE           'T' 
#define PLATEINSERT_PARTCODE    'A' 
#define MANDRELINSERT_PARTCODE  'C' 
#define VALID_PARTCODES         "FMPBKLSRITAC"

#define STEEL_H13       1
#define STEEL_2714      2

// These are the prefix strings for these steel types. These two types are 
// always listed 1-2 in the combo. The remainders are loaded based on the 
// database ordering. 
#define STEEL_H13_STR    "H-13"
#define STEEL_2714_STR   "2714"

struct SteelType
{
    csString prefix ; 
} ; 

typedef vector<SteelType> SteelTypeVec ; 

#define IS_METRIC    0x01
#define IS_IMPERIAL  0x02

// How much extra steel is added to allow for cutting and turning finishing. 
// TODO - make into parameter 
#define STEEL_CUTALLOWANCE  9.65 

#define STATE_ADD       1
#define STATE_UPDATE    2
#define STATE_DELETE    3

#define RUNMODE_DBERR   -2
#define RUNMODE_ERROR   -1
#define RUNMODE_ACTIVE  1
#define RUNMODE_DOWN    2
#define RUNMODE_NONE    3

#define EVENT_10000     0x0001
#define EVENT_10001     0x0002
#define EVENT_10002     0x0004
#define EVENT_10100     0x0008
#define EVENT_10151     0x0010
#define EVENT_20000     0x0020
#define EVENT_20009     0x0040
#define EVENT_40005     0x0080
#define EVENT_30000     0x0100

class CMSEventProcessing ; 

//! Globally defined connection parameters to CMS
/*!
    To use this first copy a string into cfgfile, and then call LoadConfigFile(...)

 */
struct CMSConnectionParms
{
    FILE *logfp ; 
    char cfgfile[4096] ; // filename where this data is loaded from. 
    int status ; // 0x80000000 = don't process
    char decDBname[128] ; 
    char decDBusr[128] ; 
    char decDBpwd[128] ; 
    char dbname[128] ; // the overall active database (EXCOPHASE1 for example)
    char dbusr[128] ; 
    char dbpwd[128] ; 
    char odbc[256] ; 
    char ibmhost[128] ; // usually the machine IP
    char DQusr[128] ; // Data Q user name
    char DQpwd[128] ; // Data Q password
    char inputQ[128] ; // default SF223DQI
    char outputQ[128] ; // deffault SF223DQO
    char batchDir[256] ; 

    char plantID[16] ; 

    char NCTimeDir[128] ; 

    bool bDoVerification ; 
    CRITICAL_SECTION chkqSection ;
    time_t lastCheckTime ;

    //! The sequence numbers can vary amoung the plants. These must be defined specific
    //! to the appropriate plant. 
    int seqSplit ; // this is the sequence 040 number
    int seqMerge ; // this is the sequence 500 number

    CMSEventProcessing *pevp ; 

    // Default constructor
    CMSConnectionParms() ; 
    ~CMSConnectionParms() ; 

    // Creates the critical section and initializes data members used to maintain 
    // the verification queue that handles readback of the SFTX table to make sure 
    // that the data Q record is processed. 
    int InitVerification() ;
    
    //! Load configuration data from file
    /*!

         The cfgfile must follow this example:


            # Lines starting with hashes (pound sign) are ignored as comments
            # The parameter names in front of the '=' sign are case sensitive.
            DECodbc=<odbc name>
            DECusr=<username>
            DECpwd=<password>
            CMSIP=<iSeries Machine IP>   example: 10.0.0.35
            CMSodbc=<CMS ODBC name>
            CMSDBusr=<username>
            CMSDBpwd=<password>
            CMSQusr=<username>
            CMSQpwd=<password>
            CMSInQ=SF223DQI
            CMSOutQ=SF223DQO
            CMSDBName=<database name>  example: EXCOPHASE1
            CMSPlant=<plantid>    For Markham is 001 for example, this is a string
            SEQSPLIT=40         (Probably different for Michigan and possible Alu'Die)
            SEQMERG=500

        Parameters that are ommitted in the file are not modified. No test is
        done to make sure all parameters are loaded. 
     */
    int LoadConfigFile(const char *configfile, FILE *fpmsg) ;
} ; 


void PrintSampleCMSConfig(FILE *fp) ; 

// TODO - go through all functions and pass this as a parameter instead
// of directly calling the parameters. 
extern CMSConnectionParms gCMSparms ; // the global CMS parameters connection set. 

// Used to store station to resource and department mapping codes. 
/*!
    
 */
struct StationMapRec
{
    char station[8] ; 
    char device[8] ; 
    char depts[8] ;
    char resre[8] ; 
} ;

typedef map<csString, StationMapRec> StationMap ; 
typedef map<csString, StationMapRec>::iterator StationMapItr ; 

struct TaskMapRec ; 

typedef map<csString, TaskMapRec> TaskMap ; 
typedef map<csString, TaskMapRec>::iterator TaskMapItr ; 

// The task needs to map to a specific sequence number in the
// tracking process. 
struct TaskMapRec
{
    /*!
        Note: for the START-STOP pair tasks, the STOP task record is stored in the 
        map with the STOP task as the key prefix, and the key prefix will match the 
        stopTask field, whereas the START task keys will match the task field. This
        is how you can distinguish between START and STOP task pairs. For standard
        non-paired tasks, the stopTask is null. 
     */
    char task[6] ;
    char stopTask[6] ; 
    char part[6] ; 
    char opcode[8] ; 
    char seqnum[16] ; 
    int  eventMode ; 
    char trackTo ; // 0=default both, B=force both with error msg, S=solarsoft only, D=decade only

    // If this is a terminating task, then the itmstart record points back to the start task 
    // definition record for this pair. 
    TaskMapItr itmstart ; 

    TaskMapRec() 
    {
        task[0] = 0 ; 
        stopTask[0] = 0 ; 
        part[0] = 0 ;  
        opcode[0] = 0 ; 
        seqnum[0] = 0 ;  
        eventMode = 0 ; 
        trackTo = 0 ; 
    }

    csString BuildKey()
    {
        csString key(task) ; 
        if (toupper(part[0]) != 'G' && part[0] != '*')
            key += part ; 
        return key ; 
    }

    csString BuildStopKey()
    {
        csString key(stopTask) ; 
        if (toupper(part[0]) != 'G' && part[0] != '*')
            key += part ; 
        return key ; 
    }

} ; 




// We need to temporarily load work orders while doing BAAL processing
// and determining which work orders to track against. 
struct CMSWorkOrderRec
{
    int orderNumber ; 
    int itemNumber ; 
    char partnum[32] ; 
    char controlID[16] ;
    char jobnum[16] ; 
    char seqnum[16] ; 
    char deviceID[16] ; 
    char opCode[16] ; 
    char deptCode[16] ; 
    char resCode[16] ; 
    char empTag[20] ; 
    char dateStr[16] ; 
    char timeStr[16] ; 
    char eventCode[16] ; 
} ; 

typedef vector<CMSWorkOrderRec>  CMSWorkOrderRecVec ; 

struct EventData
{
    // Internal Processing parameters
    int sendcount ; // retry count during DataQ sends
    time_t timeLastSend ; 
    char partCode ; 

    // ======================================================
    //                       Decade Data
    // When tracking these 5 fields must be defined when the 
    // track processing is called. The remainder of the fields
    // are looked up by the tracking logic. Once all the needed
    // data is collected, it is then use to create the data 
    // queue string and finally the message is sent. 
    // ======================================================
    int sonum ;
    int empnum ;
    char part[133] ; 
    char task[133] ; 
    char station[133] ;
    time_t tasktime ; 
    int bIsHollowDie ; 

    // ======================================================
    //                          CMS Data
    // These are the fields that are filled in through lookups
    // and/or internal processing logic. 
    // ======================================================
    int orderNumber ; 
    int itemNumber ; 
    char partnum[32] ; 
    char controlID[16] ;
    char jobnum[16] ; 
    char seqnum[16] ; 
    char deviceID[16] ; 
    char opCode[16] ; 
    char deptCode[16] ; 
    char resCode[16] ; 
    char empTag[20] ; 
    char dateStr[16] ; 
    char timeStr[16] ; 
    char eventCode[16] ; 
    char serialNumber[32] ; // lot serial number

    int nMatRecs ; // number of sub-parts
    int nRouteRecs ; // number of routing step records

    int batchID ; // temp storage during processing

    // CMSWorkOrderRecVec workOrders ; 

    // This is the buffer that is actually sent to the data Q
    char eventData[600] ; 
    int dataLength ; // initialized to 577 for SF223DQI

    int year ; 
    int month ; 
    int day ; 
    
    int hour ; 
    int mins ; 
    int secs ; 

    // ======================================================
    //                      Status Variables        
    // ======================================================
    enum {
        EVD_OUTPUT_RUN      = 0x01, 
        EVD_OUTPUT_DOWN     = 0x02,
        EVD_OUTPUT_PROD     = 0x04, 
        EVD_OUTPUT_LOTSER   = 0x08, 
    } ; 
    int eventMode ; // one of EVD_xxx defined above. 

    csString BuildResKey(char *plant)
    {
        csString key(deptCode) ; 
        key += resCode ; 
        return key ; 
    }

    //! Generate a unique control ID number to associate back with the 
    //! response data Q message. 
    void GenControlID(time_t &seed, char lastChar=0) ;

    void SetBaseFields(char *dbname, time_t  &seed, char idChar=0) ;
    void SetBaseTime(CDateTime &dt) ; 

    // Note: call TestAndSet10151Time(...) after this function - 
    //    not any more - revised OCT 10, 2009. There was still a problem.
    void Set10151(int rerun=0) ; 
    void Set10151Time(CDateTime &dt) ; 
    void Set40000() ;
    void Set10000() ;
    void Set10001() ;
    void Set10002() ;
    void Set10003() ;
    void Set10004() ;
    void Set10100() ;
    void Set20000() ;
    void Set20009() ;
    void Set20006() ;
    void Set30000() ;
    void Set40005() ;

} ;

extern int EVMAX_RETRIES ; 

/*!
    Events are processed as sets since previous events must be processed successfully
    before other events will be accepted by the Solarsoft system. 20000 events will not
    be accepted for example if 10151 has not been issued. 10151 cannot be done unless
    10000 or 10001 is done first. So when a [10000], 10151, 20000 set is output they 
    need to be grouped together so that the 20000 is done after the other 2 are processed
    correctly. 

    A maximum of 4 events can be grouped together as a single atomic operation (the most 
    that should be needed under normal processing is 3). 

    Dec 3, 2009 - Another new twist to this collosal data management behomoth is that
    Solarsoft requires that only a single work order is active on a resource at any
    given time. The initial thought was to maintain the state of the Solarsoft database
    so that no erroneous data would be sent through the queue, but in reality this 
    would server no real usefull purpose since the data queue process runs blind and
    nobody would be around to deal with the error. Thus a shop manager will have to 
    deal with the issue of correcting bad data when it occurs. As a minimum requirement
    though, a separate queue is required for each resource so that events are pumped 
    through a single resource one at a time and do not overlap. Thus in heat treat for
    example, if 20 parts are processed, then they have to go through that single resource
    one at a time sequentially with no overlap. 

 */
struct CMSEventSet
{
    int retry ; // do a max of N retries at one minute intervals
    time_t processTime ; // system time when this record was originally created. 
    // This is used only by the verification readback logic if it is enabled. 
    time_t timeLastSend ; // time the last event sent from this set. 

    int eidx ; 
    int nEVs ; 
    EventData ev[12] ; 

    void NextEvent() ; 
} ; 

// This is used as a FIFO processing stack
typedef list<CMSEventSet> CMSEventSetList ; 
typedef list<CMSEventSet>::iterator CMSEventSetListItr ; 

//! A resource node is a unqiue node in the overall event processing queue. 
//! Within each node is an event set which must be processed sequentially. 
//! This is stored in a map. The map key is 'PPPDDRRRRR' where:
//!    PPP = plant code
//!    DD  = department code
//!    RRRRR = resource code. 
struct CMSResourceNode
{
    csString key ; 
    CMSEventSetList evlist ; 
} ;

typedef map<csString, CMSResourceNode> CMSResourceMap ;
typedef map<csString, CMSResourceNode>::iterator CMSResourceMapItr ;


// This map is stored in terms of the control ID field for the 
// event which will be unique for each event. Note that for this 
// to work there cannot be more than 1 event per second. 
// No longer used since superceded by the CMSResourceMap
// typedef map<csString, CMSEventSet> EDataMap ; 
// typedef map<csString, CMSEventSet>::iterator EDataMapItr ; 


typedef map<int,int> IntMap ; 
typedef map<int,int>::iterator IntMapItr ; 

class CMSEventProcessing
{
public:
    FILE *fpLOG ; 
    CCMSDatabase  m_db;

    char plantID[16] ; 
    StationMap stationMap ;
    TaskMap    taskMap ;

    //! Bypass data queue, and process data in batch mode.
    bool bBatchMode ;  

    bool bUseCJOBDRRes ; 
    bool bDisable10100 ;
    bool bDoEmpTracking ; // do 20000/20009 when true
    time_t idseed ; 

    IntMap  empMap ; 

    EventData evd ; 

    // This stores the event queue required to handle handshaking and 
    // reliable transfer of data to the Queue. 
    // EDataMap evdmap ; 
    CMSResourceMap evresmap ; 

    CMSEventProcessing() ; 

    bool OpenDatabase(void)
    {
        return m_db.Open();
    }

    // Loads the mapping files. 
    int LoadMaps(char *plant)
    {
        strncpy(plantID, plant, 10) ; 
        plantID[10] = 0 ; 

        int retcode = 0 ; 
        retcode |= LoadStationMap("c:\\CMS\\stationMap.txt") ; 
        retcode |= LoadTaskMap("c:\\CMS\\taskMap.txt") ; 
        return retcode ; 
    }

    // Returns number of records loaded. 
    int LoadStationMap(char *filename) ;

    // Returns number of records loaded. 
    int LoadTaskMap(char *filename) ;

    //! Maps the task code and station to the appropriate CMS values
    /*!
        The decade data must be defined on entry. This data is used
        to look up the required CMS data and set the values for 
        the various fileds. 

        returns an error code, 0=OK. 
     */
    int MapDecadeData(TaskMapItr &mappeditm, bool mapSO=true) ; 

    //! Load the actual sequence number for the specific work order and task
    /*!
        \return 0=ok, else an error code

        evd.jobnum, evd.opCode, evd.deptCode must be defined since the data 
        is looked up in the CJOBDR table. 

        Return Error Codes:
        -1 : database error
        -100 : the sequence number record could not be found

     */
    int LookupSeqNumber() ; 

    // Lookup resource code and sequence number if required.
    int LookupResource() ;
    
    // Lookup resource code and sequence number if required.
    int LookupResourceCJOBDR() ;

    /*!
        \return as status code indicating what events were tracked. 

        To track an event the following must be done:

        This class must first be initialized which is required only 
        once. To initialize do 
            OpenDatabase()
            LoadMaps("PPP") ; 

            where PPP is the plant designation string. 

        Then to track these steps must be repeated. 

            1. set the evd Decade variables (the first 5 parameters)
            2. call MapDecadeData()
            3) call Track event

        The version that takes a file pointer does additional logging. 

        Return code 
            0x0001  - 10000 event tracked
            0x0002  - 10151 event tracked
            0x0004  - 40005 event tracked
            0x0008  - 10100 event tracked
     */
    int TrackEvent() ; 

    // Similar to above, but uses an existing data queue handle
    int TrackEvent(cwbDQ_QueueHandle qhandle) ; 

    int PostEvent()
    {
        TaskMapItr itm ; 
        int retcode = 0 ; 
        retcode |= MapDecadeData(itm) ; 
        retcode |= TrackEvent() ; 
        return retcode ; 
    }

    // Returns true if there is no open 10000 event code for the 
    // resource and dept that is currently defined in the evd member
    // variable. 
    /*! 
        RETURN CODES:
            RUNMODE_DBERR   -2  database error 
            RUNMODE_ERROR   -1  other error
            RUNMODE_ACTIVE  1   last runmode was a 10000 event
            RUNMODE_DOWN    2   last run mode was 10100 down 
            RUNMODE_NONE    3   there is no runmode defined for current day 
     */
    int ActiveBatchShift(EventData *pevd=0) ; 

    // Sees if the 10100 event was successfully writtent to the SFTX table
    //! returns EVENT_10100 if found, the eventTime is also returned 
    int Get10100Status(EventData &evd, time_t &eventTime) ; 

    // Sees if the 10151 event has been tracked in the SFTX table
    int Get10151Status(EventData &evd, time_t &eventTime) ; 
    int TestAndSet10151Time(EventData &evd) ; 
    
    int GetLast10151Status(EventData &evd, time_t &eventTime) ;


    // Returns > 0 if the sequence number is valid and exists. 
    int TestValidSeqnum(EventData &evd) ;

    // Sees if the 10151 or 20000 event has been tracked in the SFTX table
    //! returns EVENT_10151 and/or EVENT_20000 flags if found. 
    int Get20000Status(EventData &evd, time_t &eventTime) ; 

    // Sees if the 20009 event was tracked
    int Get20009Status(EventData &evd, time_t &eventTime) ;

    // Test if the 30000 event was tracked, returns EVENT_30000 flag if found.
    int Get30000Status(EventData &evd, time_t &eventTime) ;

    // Sees if the 10151 event has been tracked in the SFTX table
    int Get40005Status(EventData &evd, time_t &eventTime) ; 

    // Returns true if the 40005 has been done for this sequence step. 
    int Event40005Done(EventData &evd, time_t &eventTime) ;

    //! When sending the 40005, we want to make sure that the last event for the 
    //! resource was the 10151 with the same JOB number. If not, then an additional
    //! 10151 needs to be output before sending the 40005 (but only needed if the 
    //! 40005 for this job has never been sent. Also a 10001 can be ignored in 
    //! this process. 
    int Last10151Matches(EventData &evd) ;


    // Returns the task trackTo definition within the TaskMap.txt file 
    // for the given taskcode 
    char GetTaskMode(char *taskcode) ;
} ;

/*
These are the current features and options. 
Note search the FOMO table and specify "EXTRA CHRG" to match the FIFCDE field. 

HD 8 X 9  EXTRA CHRG	TRIPLE SKIM CUT     	1	TRIPLE SKIM CUT               	
HD 8 X 9  EXTRA CHRG	SHUT OFF DIE - NORMA	2	SHUT OFF DIE - NORMAL         	
HD 8 X 9  EXTRA CHRG	SHUT OFF DIE - NEW D	3	SHUT OFF DIE - NEW DOVETAIL   	
HD 8 X 9  EXTRA CHRG	CENTRE FEED DESIGN  	4	CENTRE FEED DESIGN            	
HD 8 X 9  EXTRA CHRG	KEYWAYS             	5	KEYWAYS                       	
HD 8 X 9  EXTRA CHRG	BOLTS               	6	BOLTS HARDENED H13            	
HD 8 X 9  EXTRA CHRG	HARDENED BLANK      	7	HARDENED BLANK                	
HD 8 X 9  EXTRA CHRG	DOME DIES           	8	DOME DIES                     	
HD 8 X 9  EXTRA CHRG	EXTENDED FIXED MANDR	9	EXTENDED FIXED MANDRELS       	
HD 8 X 9  EXTRA CHRG	INSERTS             	10	INSERT FOR PLATE OR MANDREL   	
HD 8 X 9  EXTRA CHRG	INSERTS - PER PIECE 	11	COST PER PIECE OF REPLACEABLE 	
HD 8 X 9  EXTRA CHRG	MANDREL FOR PLATE   	12	MANDREL TO SUIT EXISTING PLATE	
HD 8 X 9  EXTRA CHRG	MICRO BRIDGE        	13	MICRO BRIDGE CHARGE           	
HD 8 X 9  EXTRA CHRG	N2 GROOVES BA       	14	NITROGEN GROOVES BACKER       	
HD 8 X 9  EXTRA CHRG	N2 GROOVES BO       	15	NITROGEN GROOVES BOLSTER      	
HD 8 X 9  EXTRA CHRG	ONE PIECE-SH-FC     	16	ONE PIECE-SEMI-HOLLOW-FAKE COR	
HD 8 X 9  EXTRA CHRG	PIN CORES           	17	REPLACEABLE PIN CORES         	
HD 8 X 9  EXTRA CHRG	PLATE FOR MANDREL   	18	PLATE TO SUIT EXISTING MANDREL	
HD 8 X 9  EXTRA CHRG	PLATE/MANDREL ONLY  	19	PLATE & MANDREL NO BACKER     	
HD 8 X 9  EXTRA CHRG	POCKET CHARGE       	20	POCKET CHARGE                 	
HD 8 X 9  EXTRA CHRG	RE-NITRIDING        	21	RE-NITRIDING                  	
HD 8 X 9  EXTRA CHRG	REWORK              	22	REWORK                        	
HD 8 X 9  EXTRA CHRG	WELD & REPAIR       	23	WELD & REPAIR                 	
HD 8 X 9  EXTRA CHRG	WIRE RELIEF-CHOKE-NC	24	WIRE RELIEF-CHOKE-NCB         	
HD 8 X 9  EXTRA CHRG	HEAT SINK           	25	HEAT SINK                     	
HD 8 X 9  EXTRA CHRG	MULTI - MANDREL     	26	MULTI - MANDREL               	
HD 8 X 9  EXTRA CHRG	NITRIDE - FLAT RATE 	27	NITRIDE - FLAT RATE           	

 */

struct CMSOption
{
    csString opttype ; 
    csString optname ; 
    int qty ; 

    // Test functions on features and options
    int IsTripleSkim() ; 
    int IsHeatSink() ; 
    int IsSparkBrgs() ; 
    int IsMultiCore() ; 
    int IsOnePiece() ; 
    int IsCentreFeed() ; 

} ; 

typedef vector<CMSOption> CMSOptionVec ; 



// There are multiple types of job records and not all fields are valid for 
// all record types. 
struct CMSJob
{
    //! One of TYPE_FDR, TYPE_MND etc...  not realy used yet. 
    int parttype ; 

    //! character code defining the part, see RouteParmRec definition.  
    int partcode ; 

    csString ordNum ; // parent order number, not always used.
    csString jobnum ;   // the actual work order number for the part. 
    csString tmpjobnum ; // used during actual processing. 
    csString partname ; // this is the part number really. "HD 9 X 5 MANDREL" for example  EFPART
    csString mattype ;  // the material type EFMTLP
    double length ;     // thickness of the part. 
    double diam ;       // diameter of the part in inches. 
    
    // seq num for the record. This will be the seqMerge or seqSplit value 
    // and defines the sequence step where the part is initially created
    int seqnum ;  
    
    int subCount ;  // for master parts that contain sub assemblies this is > 1
    int linenum ; 
    int steel ; // the type of material used to make the part STEEL_H13, STEEL_2714
    int bSteelIsActual ; // 
    int bIsRequired ; // set to false when part is not used or is being deleted. 
    int processState ; 
    int nCavities ; 
    int bAddedRecord ; 

    char jobstatus ; // DNSTAT field value

    // Special conditions specific to the job. 
    /*!
        Hardened blanks and turned blanks are mutually exclusive. The hardened blank has 
        precedence if both are defined. 
     */
    enum {
        TURNED_BLANK    = 0x0001, // manufactured from a pre-turned blank
        HARDENED_BLANK  = 0x0002, // Manufactured from a pre-turned hardened blank
        PART_BLANK      = TURNED_BLANK | HARDENED_BLANK, 
    } ; 
    int statFlags ; 


    int bOutOfStock ; // set true if the diameter specified maps to a 
    // stock size which is unavailable. 

    int bStockOverride ; // set to true if we want to ignore the fact that 
    // the material is out of stock. 

    // This is the existing data from the CJOBDR table. For hollow die
    // sub parts, where no CJOBDR records exist, the METHDR table is 
    // loaded with the standard routing data as well. 
    // The methdr records are only loaded for MANDREL sub parts 
    // and only if no existing sub-parts are defined within the CJOBDR
    // table. In this case the cjobdrVec will contain only records 
    // where the CAD/CAM and inspection routing steps are defined. 
    // All the sub steps would be defined in the methdrVec data.
    RouteDataRecVec cjobdrVec ; // all operations for this job.
    RouteDataRecVec methdrVec ; // all operations for this job.

    // This is the index into the cjobdrVec of the last active sequence 
    // number step where time has been recorded against the sequence in the
    // routing. This is the last active routing step effectively. 
    int iLastSeq ; 
    int ilastActiveSeq ;

    // this is the first sequence step with zero time associated with it
    // if iFirstZSeg < iLastSeq then there are gaps in the routing. 
    int iFirstZSeq ; 

    CMSJob() ; 
    ~CMSJob() ; 

    // All of these return the steel type 0=not that part. 
    // Note that for the backer and bolster the steel type
    // is determined by the name itself. The overriding name 
    // is not returned here. All of the IsXXXXX() functions
    // set the partcode character as well. 
    int IsFeeder() ;
    int IsMandrel() ;
    char IsSubPlate() ;
    int IsPlate() ;
    char IsSubBacker() ;
    int IsBacker() ;
    int IsBolster() ;
    int IsSubBolster() ; 
    int IsDieRing() ; 

    bool IsPartBlank() { return (statFlags & PART_BLANK ? true : false) ;  } 

    csString &GetTmpJobNumber(int &count) ; 

    //! Set the partcode character based on partname string
    /*!
        \return the partcode value

        If the part code type cannot be determined, then the part code is 
        set to 0 (null char) 
     */
    char SetPartCode() ; 

    // Set the default steel type for this part, returns 'steel' value
    int DefaultSteelType(SteelTypeVec &stv, csString &deftype) ; 

    // The options specific to each job 
    CMSOptionVec optvec ; // all the options for the order. 
    int AppendOpt(CMSOption &opt) ; 

    //! Load the CJOBDR routing data for this part. 
    /*! 
        \param m_db (input) database connection to use for the query 
        \param fplog (input) log file pointer for any error messages 
        \return 0=ok, else error code. 
     */
    int LoadRouting(CCMSDatabase &m_db, FILE *fplog) ;

} ; 

typedef vector<CMSJob> CMSJobVec ; 
typedef map<csString, CMSJob> CMSJobMap ; 
typedef map<csString, CMSJob>::iterator CMSJobMapItr ; 

//! This data structure record is used to store the UG runtime data which 
//! is loaded all at once and then reference later during processing. 
struct CMSRoutingStep
{
    int seqnum ; // the routing method sequence number 
    char part ; // must be a valid part character within VALID_PARTCODES

    //! For timemap processing this flag holds the time data for the 
    //! specific part. 
    double ncTime ; 

    // This means that the time was already applied to a record and does
    // not need to be dealt with any further. 
    bool bProcessed ; 
} ; 

typedef vector<CMSRoutingStep> CMSRoutingStepVec ; 


struct CMSOrder
{
    csString orderNumber ; 
    char status ; 
    char jobStatus ; 

    csString custCode ; 
    csString custName ; 
    CDateTime orderDate ; 
    CDateTime reqdDate ; 

    // These are defined for the respective matching parts. If the part doesn't exist
    // then the pointer is null (0)
    CMSJob *jobFDR() {if(ijobFDR < 0) return 0 ; else return &jobvec[ijobFDR] ; } ;
    CMSJob *jobMND() {if(ijobMND < 0) return 0 ; else return &jobvec[ijobMND] ; } ; 
    CMSJob *jobPLT() {if(ijobPLT < 0) return 0 ; else return &jobvec[ijobPLT] ; } ; 
    CMSJob *jobBKR() {if(ijobBKR < 0) return 0 ; else return &jobvec[ijobBKR] ; } ; 
    CMSJob *jobBOL() {if(ijobBOL < 0) return 0 ; else return &jobvec[ijobBOL] ; } ; 
    CMSJob *jobSUB() {if(ijobSUB < 0) return 0 ; else return &jobvec[ijobSUB] ; } ; 
    CMSJob *jobRNG() {if(ijobRNG < 0) return 0 ; else return &jobvec[ijobRNG] ; } ; 

    int ijobFDR ; 
    int ijobMND ; 
    int ijobPLT ; 
    int ijobBKR ; 
    int ijobBOL ; 
    int ijobSUB ; 
    int ijobRNG ; 

    // 0=actual part, 1=master part, 2=?
    int feederCount[3] ; 
    int mandrelCount[3] ; 
    int plateCount[3] ; 
    int backerCount[3] ; 
    int bolsterCount[3] ; 
    int subbolsterCount[3] ; 
    int ringCount[3] ; 

    int nCavities ; 

    double fdrThk ; 
    double mndThk ; 
    double pltThk ; 
    double bkrThk ; 
    double bolThk ; 
    double subThk ; 
    double rngThk ; 

    double fdrDia ; 
    double mndDia ; 
    double pltDia ; 
    double bkrDia ; 
    double bolDia ; 
    double subDia ; 
    double rngDia ; 

    int bHollowDie ; // set true if this is a hollow die. 
    // Must he set to TYPE_HOLLOW only

    int bHasFDR ; 
    int bHasMND ; 
    int bHasPLT ; 
    int bHasBKR ; 
    int bHasBOL ; 
    int bHasSUB ; 
    int bHasRNG ; 

    int bCentreFeed ; 
    int bMultiCore ; 
    int bOnePiece ; 
    int bTripleSkim ; 
    int bSparkPlate ;
    int bHeatSink ; 
    
    CMSJobVec jobvec ; // all jobs(or parts) with this order

    // -------- MEMBER FUNCTIONS --------

    CMSOrder() ; 
    CMSOrder(const CMSOrder &ord); 
    CMSOrder& operator=(const CMSOrder &ord) ; 
    ~CMSOrder() ; 

    void clear() ; 

    //! Load order details such as customer name and dates. 
    int LoadDetails(CCMSDatabase &db); 

    // Returns true if the condition matches
    int IsPartRec(CMSJob &job) ; 

    int AppendJob(CMSJob &job, char **msg=0) ; 

    // Returns the index for the jobvec[] entry that matches the part 
    // if the bSteelIsActual is true. 
    int PartIDXActual(char parttype) ; 
    
    // Sets the features and options flags based on the opt data
    int SetOptState(CMSOption &opt) ;

    double GetDiam(csString &part) ; 

    //! returns true if part dims are found.
    int GetPartDims(CMSJob &job, double &dia, double &thk) ; 

    //! returns true if a job with the matching part type exists in a sequence
    //! number 40 record (where the parts split . 
    int FindSeqSplitPart(int parttype) ;
    int FindSeqMergePart(int parttype) ;

    // Returns true if this order contains a part with sub component records
    // which for now is exclusively for hollow dies. 
    //  Returns the jobvec index of the first record with a subCount > 1
    int HasMasterComponents() ; 

    // Used by WasReleased for sub component type records. 
    /*
        For master-sub assemblies, the master records have subcounts > 1, but
        once the order is released and the work orders for the sub-components
        are generated by the flat file processor (or manually), then there
        will be part records with a subcount of 1 as well. Thus if an order
        has records with subcount > 1 and work order records with subcount==1
        then it must be a master hollow die assembly that was already released. 
     */
    //  Returns the jobvec index of the first record with a subCount == 1
    int HasSubWorkOrders() ; 

    //! Returns the part character for for the job if it is a single hollow
    //! die sub-assembly part with no master assembly defined. 
    char SingleSubPartType(int i) ; 

    // Returns the job vector index of the top priority CAD/CAM etc.. record
    int TopPriorityPartIndex() ;

    // Returns true if this is not the TOP priority single tracking record. 
    bool SingleSubIsNotTopPriority(int i) ;

    // Returns true if this order has already been released fully to the shop. 
    bool WasReleased() ;

    //! Load all the METHDR records
    int LoadMETHDR(CCMSDatabase &m_db, char *plant, FILE *fplog) ;

} ; 

typedef vector<CMSOrder> CMSOrderVec ;
typedef std::vector<char*> CS_CharPtrVec; 

class CMSBOMRTE
{
    typedef std::vector<char*>  CharArray;
    char dbName[128] ; // required for all queries as tablename prefix
public:

    char szFlatFileDir[512] ; // directory where the flat file should be output
    char szFlatFilePrefix[128] ; // station prefix to use when outputting flat file. 
    char NCTimesDir[128] ; 
    char plant[16] ; 
    int ncFileDigits ; // number of Order number digitis to use when searching
    // for any type of NC file (part or time)

    // Used to indicate that this is the initial run through of the 
    // InitOrderList() processing. 
    int firstRun ; 

    csString steelStockMsg ; 

    // Contains a list of steel types. 
    SteelTypeVec steelvec ; 

    int oIDX ; // currently selected order index
    CMSOrderVec activeOrders ;

    //! Routing update records vector.
    RoutingCondRecVec rcondvec ;

    //! Routing update records for standalone single subparts. 
    /*!
        When a plate to suit and existing mandrel is order sales typically selects
        the plate sub part instead of the master assembly for the hollow die. In this
        situation, there is not CAD/CAM and Inspection routing data defined since these
        come from the master part typically. Thus we have to add the sub-part data in 
        this example. This is the vector which contains the rules for doing so. 
     */
    RoutingCondRecVec rsingvec ;

    /*
        Used for parts on an order where no master part exists. Thus any part
        that has a sub count of 1 will have this rule applied to it unless it
        is the top priority part ranked by:
            PLT, MND, FDR, BKR, BOL, SUBBOL, SUB BKR, RING
     */
    RoutingCondRecVec rnomastvec ; 

    //! NC Run time mapping update records vector.
    RouteDataRecMap timemap ;

    // this is the temporary ID number used to sync records in the flat file
    // that don't have a valid work order number yet. 
    int FFtmpnum ;

    CCMSDatabase        m_db ;

    //! When true it skips the logic which checks material stock. Used for debug
    //! and testing. 
    int skipStockCheck ;

    CMSBOMRTE(void) ;
    virtual ~CMSBOMRTE(void) ;

    bool OpenDatabase(char *CMSDBName)
    {
        strcpy(dbName, CMSDBName) ;
        return m_db.Open(dbName) ;
    }

    CCMSDatabase& GetDatabase(void)
    {
        return m_db ;
    }
    
    // Load the master steel type prefixes
    bool InitSteelTypes() ;
    bool InitOrderList(const char *ordernumber=0) ;
    void CorrectSteelTypes(CMSOrder &ord) ;
    int LoadFeaturesAndOptions() ;

    CS_CharPtrVec CMSBOMRTE::ActiveOrdersList(void) ;
    void FreeOrderList(void) ;

private:

    CharArray           m_vecWorkOrderList ;

public : 

    // Find the smallest appropriate bar stock. 
    csString FindBarStock(int steeltype, double dia, double thk, int flags) ;
    csString FindBarStock(char *steeltype, double dia, double thk, int flags) ;

    //! Returns the full partname designation 
    int FindPart(char *prefix, char *subpart, 
                 double dia, double thk, csString &part) ;

    //! return true if any job in the order had been previously released. 
    int PartsAlreadyExist(CMSOrder &ord) ;

    int FindMatchingPartRec(CMSJob &job, CMSOrder &ord) ;

    //! Returns the number of records to be modified, either updated
    //! added or deleted through the flat file. 
    int OutputLengthUpdateRecs(FILE *fp, CMSOrder &oldord, CMSOrder &neword) ;

    int OutputMaterialRecs(FILE *fp, CMSOrder &ord) ;

    int TestAddMandrel(FILE *fp, CMSOrder &oldord, CMSOrder &neword) ; 
    int TestAddPlate  (FILE *fp, CMSOrder &oldord, CMSOrder &neword) ; 
    int TestAddBacker (FILE *fp, CMSOrder &oldord, CMSOrder &neword) ; 
    // The FDR, BOL, SUB, and RNG TestAdd... functions do nothing right now
    // since these should be defined in the sales order if required. CAD/CAM
    // will not be adding these on their own. 
    int TestAddFeeder (FILE *fp, CMSOrder &oldord, CMSOrder &neword) ; 
    int TestAddBolster(FILE *fp, CMSOrder &oldord, CMSOrder &neword) ; 
    int TestAddSub(FILE *fp, CMSOrder &oldord, CMSOrder &neword) ; 
    int TestAddRing   (FILE *fp, CMSOrder &oldord, CMSOrder &neword) ; 

    int CreatePartAddRecord(FILE *fp, CMSJob &job) ; 

    //! Output add sub part record (backer plate or mandrel for HDxxxx parts)
    /*!
        \param fp output file pointer
        \param ord current order for part
        \param i jobvec index for the part being added. 
        \return 0=ok, else error code
     */
    int CreateAddSubPart(FILE *fp, CMSOrder &ord, int i) ;


    //! By comparing the previous value to the new we can create the proper flat file
    //! for final processing. 
    int ProcessFlatFile(FILE *fp, CMSOrder &origOrd, CMSOrder &updOrd) ;

    //! Last step in process of outputing RTE records to flat file
    int ProcessRoutingRecords(FILE *fp, CMSOrder &ord) ; 

    // Returns the matching job/workorder record for the designated timemap. 
    int GetJobNumberData(CMSOrder &ord, RouteDataRecMapItr &rmi) ;

    //! Loads the UG run times for the job, returns number of tiem files 
    //! that were loaded. The times are stored directly in the timemap
    //! data structure which is reset each time this function is called. 
    //! The actualRunTime is -1 if no data was read. 
    int LoadNCTimes(CMSOrder &ord) ;


    inline void WriteRTEChanges(FILE *fpout,
                                CMSOrder &ord, 
                                int ijob, 
                                int iopt, 
                                RoutingCondRec &rcrec,
                                int mode) ;

    // Returns true if the material is in stock or is overridden, else false 
    int MaterialInStock(CMSJob &job, csString &barPartNum) ;

    csString FindBestPart(CMSJob &job, csString &basePart, double &actThk) ;


};

// =================================================
//              Function Prototypes
// =================================================

// The qhandle returned can be used to send messages with
//  CMS_SendEventToQ(cwbDQ_QueueHandle qhandle, EventData &evd)
int IBM_OpenDataQ(cwbCO_SysHandle &isys, cwbDQ_QueueHandle &qhandle, char *qname) ;
int IBM_CloseDataQ(cwbCO_SysHandle &isys, cwbDQ_QueueHandle &qhandle) ;

// Send command to the iSeries
int IBM_RunCommand(csString &cmd) ;


// Opens a system handle and data Q and then sends the data
int CMS_SendEventToQ(EventData &evd, int *perror=0) ; 
// Sends the data through an existing data Q 
int CMS_SendEventToQ(cwbDQ_QueueHandle qhandle, EventData &evd) ;

//! Determine best match based on the mapping definition data
/*!
    \param partstr part match condition from mapping file
    \return ranking of 0,1 or 2

    The higher the ranking return value, the better the match meaning that
    this is a more exact match and is to be preferred over a different 
    matching record. For example, if there is a task entery for *, M, and 
    MB then MB has priority since it is most precise. 

    This is not really important right now but can be extended in the future
    to deal with cases where it actually matters. 
 */
int PartRank(char *partstr) ; 

//! Returns the number of characters that match between the two strings
int PartCharsThatMatch(char *taskdefpart, char *trackpart) ;

// Find best match for the task in the task map 
TaskMapItr FindTaskMatch(TaskMap &tmap, char *task, char *part) ;

// Find best match for the station code. The heat treat data at Markham 
// has unique process data coded into the station code so only the first
// two characters for example are required in mapping. This means we need
// to specify a wildcard for station maps and thus this search is neede.
StationMapItr FindStationMatch(StationMap &stationMap, csString &station) ;

// extern FILE *fplog ; // default
void LogError(char *) ; 
void Log2Error(char *estr, int noStdOut) ;


//! Returns the prefix and suffix strings based on the part type. 
bool PartNames(int dietype, char *prefix, char *suffix) ;

int NormalizeFraction(int n) ; // 0,25,50,75

//! Puts together standard part names based on type, diam, and thickness
/*! 
    \param prefix part prefix, FDR, HD, SD, ...
    \param subpart only defined for HD types one of {MANDREL, PLATE, BACKER}
    \param dia diameter of the part
    \param thk thickness of the part
    \return the closest string matching the partname

    Part naming convention assumed to be:  
        
        AAA N[.NN] X N[.NN] [MANDREL|PLATE|BACKER]

    The first number is the diameter, and the second number is the thickness. 
    For HD type parts, the thickness is for the overall stack and not the 
    individual parts. If we are adding a backer to an HD type order, then 
    the backer should be taken from the HD sub parts list. If the backer
    is being deleted then again it should only happen when deleting from 
    an HD type order. 

    The ability to add and delete other types of parts will be enabled 
    later on if required, but for now it will be assumed that sales will
    be responsible for adding all the necessary components and that all 
    we really need to do is delete parts. 

    The reason for adding a part would be if a component of a hollow die
    was deleted when in reality it shouldn't have been, and the user needs
    to add it back. 
    */
csString BuildPartName(char *prefix, char *subpart, double dia, double thk) ;

//! Calls the above function using the given input data. 
csString BuildPartName(int parttype, CMSOrder &order, CMSJob &job) ; 

//! Converts the finish size given in mm to the actual stock thickness
//! defined in inches within solarsoft. 
double Thick_FinMM2StkIN(double finsize) ; 

// Compares the two run times to 2 decimal places with rounding for equality. 
bool RunTimesDifferent(double a, double b) ;

//! Returns the character if it is valid, else returns null 
int ValidPartCharacter(char c) ;

int CMSSQL_GetDate(CDateTime &dt, const char *datestr) ;
int CMSSQL_GetTime(CDateTime &dt, const char *timestr) ;

char PartCodeCharFromCMSPart(csString &partname) ;
int GetPartPriorityValue(char partCode) ;
int IsOldPartHigherPriority(char oldpart, char newpart) ;

// Directly append a FEATURE-OPTION record to the specific job. Initially 
// created to handle TURNED and HARDENED BLANKS. 
int AddTurnedBlank(CMSJob *pjob) ;
int AddHardenedBlank(CMSJob *pjob) ;

// Enforce mutually exclusive rules etc... for CMSJob records
void SetStatFlags(int newStat, int &destFlags) ;

// Returns cut allowance, IS_IMPERIAL or IS_METRIC are the modes
double SawCutAllowance(double thk, int mode=IS_METRIC) ;

#endif
