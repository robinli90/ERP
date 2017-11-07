// routeUpdDef.h Routing modifications text definition file 

#ifndef __ROUTEUPDDEF_H__
#define __ROUTEUPDDEF_H__


#define ROUTE_ADD       1
#define ROUTE_MOD       2
#define ROUTE_DEL       3 


struct EventRef
{
    csString reskey ; 
    int idx ; 
} ; 


typedef vector<EventRef> EventRefVec ; 

// #define ACTION_ADD      '1'
// #define ACTION_UPDATE   '2'
// #define ACTION_DELETE   '3'

#define PRCF_SET_TIME_STAMP      0x01

/*! 
    For time map records the key to look up these records is 
    SEQ#Part concatenated as a single string. Thus all matching
    sequence numbers will be grouped together in the map. This 
    also means that SEQ# and Part type must define mutually 
    exclusive pairs. 

 */
struct RouteDataRec
{
    int command ; // 0=ROUTE_DEL, 1=ROUTE_MOD, 2=ROUTE_ADD

    // This is the actual solarsoft routing operation data
    int seqno ; 
    int linenum ; // not really used
    csString plant ; 
    csString dept ; 
    csString resource ; 
    csString operation ; 
    double runstd ; // defined in hours
    csString status ; // N/H/C/? (check this)
    csString reporting ; // Y/N
    double fut5 ; // not sure what this is for. 

    char  decadeTask[128] ; 

	csString stationET[1024];
	char tasktimetempET[128];
	csString tasktimeET[1024];
	csString prtcodeET[1024];
	csString taskET;
	int empnumET[1024];	
	int sonumET[1024];
	csString rtypeET[1024];


    csString material ; 
    double mtlqty ; 
    csString mtlunits ; 
    csString mtlStkLoc ; // stock location

    int serialnum ; 
    int assignedSerial ; // serial number automatically assigned by system. 
    int processedSerial ; // 0=nothing, 1=processed/assigned, 3=processed and overridden operator data

    // ------------------------------------------------------------
    // This is a work variable used when loading routing records
    bool bSubExists ; 

    // True if this is a CAM step just before the SAW step where the CAM material also needs
    // to be tracked. This will always be tracked when the SAW is physically tracked with a
    // qunatity of 1 unit, and so many inches. 
    bool bTrackCAMmtl ; 

    // ============================================================
    // These fields are used for storing NC machine time adjustment 
    // data records. 
    // ============================================================
    char partCode ; 
    
    //! Defined if a prefix string should be prepended to the order 
    //! number when searching for the time record file.
    csStringVec preList ; 

    //! Defined if a suffix string should be appended to the order
    //! number when searching for the time record file.
    csStringVec postList ; 

    //! How many ailing digits in the order to output for the NC time
    //! record file name. If zero then all digits are output. 
    int ndigits ; 

    //! The actual run times are the values loaded from the 
    //! UG run time data. Multiple program operations could 
    //! be included in this overall total. 
    double actualRunTime ; 
    bool bRunTimeProcessed ; // true if the time data was processed

    // These are set to indicate the types of TASK records found against 
    // this job and routing step. 
    int bEventFound ; 
    int bRuntimeFound ; 
    int statflags ; 

    //! run time running total when loading from RPRR file
    double totalRunTime ; // in hours
    int bModified ; 
    double qtydone ; // number of parts produced for this sequence number
    double pendingRunTime ; // in hours
    double finalQty ; // resultant final quantity after this run.

    double maxQty ; // used to control qty logic during final processing

    // The number of times this step was scrapped. See prevScrapCount below. 
    double qtyscrap ; 

    // Required so we know that an additional part has been reported. 
    double qtysaw ; 

    // This is incremented as a maintenance step to indicate how many scrap events occured 
    // after this point in the sequencing. Thus the total qtygood allowed at this step
    // is (1 + prevScrapCount + qtyscrap)
    double prevScrapCount ; 

    int bWasStillInRunState ; 
    int bSetStdRunIfBlank ; 
    
    int bProcFlags ; // processing indicator flags
    // 0x01 - PRCF_SET_TIME_STAMP this is a time stamp event which needs to be recorded

    // time the job was started
    CDateTime starttime ; 
    CDateTime lastEventTime ; 

    //! This key is used in batch mode only - it matches the key used to store this
    //! event in the resmap structure 
    csString reskey ; 

    //! Since we are processing through the routing conditions multiple 
    //! times searching for different things, for global wildcard type 
    //! items, we will get multiple hits. This flag is set and then 
    //! prevents future hits.
    bool bProcessed ; // means that a record was written to the output file


    // This is used only in the batch mode processor
    // This is an array of references to the actual events that occured for
    // this particular sequence step. The actual event data is stored with 
    // the resource record. 
    EventRefVec erv ; 

    RouteDataRec() ; 

    int TimeFileMatch(csString &jobnumstr, char *filename) ;
    double RunTime() { return pendingRunTime + totalRunTime ; }


} ; 

typedef vector<RouteDataRec>  RouteDataRecVec ; 

//! The key for these records is a string which is built as a the 
//! concatenation of the part code character and sequence#
typedef map<csString, RouteDataRec>  RouteDataRecMap ; 
typedef map<csString, RouteDataRec>::iterator  RouteDataRecMapItr ; 


struct RoutingCondRec
{
    bool inverted ; //! true if this rule should apply if the feature/option
    //! does not exist. 

    //! During processing of each job, this flag is reset. Then all features
    //! and options are searched and for each one that is found, this flag
    //! is set. If this condition is inverted and bDefined is not set at 
    //! the end of processing, then the rules for this condition then need
    //! to be applied. 
    bool bDefined ; 

    csString feature ; //! a unique string pattern which matches the 
    //! feature string. * is a wildcard value for this field, so if a '*' 
    //! value is defined then only the option will be used to match 
    //! the record. The feature and option cannot both be *

    csString option ; //! a string portion to uniquely identify the option
    
    csString customer ; //! *, or the actual customer code as stored in the 
    //! solarsoft database. A value of * means match any customer

    double diaFrom, diaTo ; //! diameter range for this part, a 0.01 tolerance
    //! is used on this value which is stored in mm. The default input value
    //! is in inches. 

    //! If the condition is non-terminating, then when searching for and 
    //! assigning RTE records, if a match is found in a non-terminating
    //! set, all those RTE records will be included, but instead of stopping
    //! the program will continue to search for other matching conditions. 
    //! Thus multiple matching conditions could occur. 
    bool bNonTerminating ; 
    
    csString parts ; //! could be * meaning match all parts, or a string
    //! logic. 

    /*! 
        The characters are capitalized before processing. 
        
        F - feeder
        M - mandrel 
        P - plate 
        B - backer 
        L - bolster 
        S - sub bolster 
        R - ring 
        K - sub backer
        I - insert (generic)
        A - plate insert
        C - mandrel insert
        T - bolt. 

        In the future if we need to expand the part definition set we can make parts
        case sensitive, thus it is a good idea to define all parts capitalized. 

        If a * is defined then no other parts should be included since they will
        be ignored. 

        Note: if this defines a special condition record then parts is the only 
        parameter that will matter. 
     */
    
    RouteDataRecVec drecs ; 

    // **************************************
    // ********** MEMBER FUNCTIONS ********** 
    // **************************************

    // Default constructor. 
    RoutingCondRec() : 
        bNonTerminating(false),
        inverted(false) {} ; 

    //! Split the Feature,option strings
    int ParseFeatureOption(csString &tok) ; 

    //! Extract the from and to diameters
    /*!
        \param tok string containing "12.0 - 30in" for example
        \return 0=error, 0x01=first value found, 0x02 second, 0x04=wildcard
     */
    int ParseDiams(csString &tok) ; 

    //! returns true if diaFrom-0.01 < dia < diaTo+0.01
    bool DiaInRange(double dia)
    {
        if ((diaFrom - 0.01) < dia  && 
             dia < (diaTo + 0.01))
             return true ;
        return false ; 
    } ; 

    //! See if the input parameters match this record
    /*!
        \param szFeat if null or * then matches always, else searches for string
        \param szOpt  must be defined, searches for string
        \param szCust if null or * then matches always, else searches for string
        \param dia diameter to compare against
        \param part the part code to test against, if null or * the always matches
        \return 1=found match, 0=no match

        Case is ignored when searching for strings (not case sensitive) 
     */
    int Matches(char *szFeat,            // feature to match    
                char *szOpt,             // option to match
                char *szCust,            // customer code
                double dia,              // part diameter
                char part) ;             // part type character

} ; 


typedef vector<RoutingCondRec>  RoutingCondRecVec ; 

//! Load the routing table records as defined above. 
/*!
    \param filename name of file that contains the RTE to time record filename map
    \param rcondvec where the routing condition records 
    \param rsingvec single subpart routing condition records stored here 
    \param fplog open handle to a log file for error and status messages
    \return number of records loaded. 
 */
int LoadRoutingTable(char *filename, 
                     RoutingCondRecVec &rcondvec, 
                     RoutingCondRecVec &rsingvec,
                     RoutingCondRecVec &rnomastvec,
                     FILE *fplog) ;


//! Based on input record find the best matching routing parameter record. 
/*!
    \param recvec the records to be searched 
    \param szFeat the feature to test for
    \param szOpt the specific option to test for
    \param szCust customer specific record
    \param dia diameter of the part to check for
    \param part the part to test for
    \return -1=record not found, index into the RouteParmRecVec 

    The algorithm is brute force, it works it's way through the list of records
    and attempts to match the input parameter set to each record. As soon as 
    a match is found it returns that record. This is not optimized since it
    will be run on local client machines and should be fairly quick. If required
    each of the search parameters can be loaded into maps and optimized. 
 */
int FindRoutingRec(RoutingCondRecVec &recvec, 
                   char *szFeat, char *szOpt, char *szCust, double dia, char part) ; 


//! Load the NC machine time mapping data
/*!
    \param filename name of file that contains the RTE to time record filename map
    \param timemap map where the records are loaded 
    \param fplog open handle to a log file for error and status messages
    \return number of records loaded. <= 0 indicates an error condition

    The structure of the timing records file is a text file where each line in the 
    file defines one mapping definition. Lines starting with # are ignored. 
    The format of the lines read must be as follows:

        SEQ#;PART;DEPT;RES;PREFIX[,PREF2,PREF3...];SUFFIX[,SUFF2,SUFF3,...];NDIGITS

    For a record that defines how to process a wire edm process in the Markham 
    plant, for example, a valid line might look like:

    152;P;WI;*;WX;;5

    The '*' character in the RES position means that we can ignore the resource
    when matching the record within Solarsoft. For now the RES field must always
    be * since it is ignored in the logic, it is simply defined, in case we need 
    to added another level of detail, so that the parameter file does not have 
    to be completely changed. Only those records requiring additional detail 
    will need the * changed to an actual resource string. 

    The PART designator indicates the type of part that we are talking about. The
    part mapping characters are the same as those defined in RoutingCondRec

        F - feeder
        M - mandrel 
        P - plate 
        B - backer 
        L - bolster 
        S - sub bolster 
        R - ring 
        K - sub backer
        I - insert (generic)
        A - plate insert
        C - mandrel insert
        T - bolt. 

    Again these should always be defined uppercase, as we may need to introduce 
    more part conditions in the future and then case may be important. The reason
    part must be defined is because in Markham's methods for example, SEQ# can be
    used to plate or mandrel milling so there is no way to separate the two 
    without this extra character definition. 

    You can also substitute a '*' (without the quotes) in the DEPT field which 
    means that only the Sequence number needs to match in this case. If the 
    method data is set up cleanly then the sequence number should be all that 
    is required to uniquely identify an operation, but the Markham plant for 
    example is not setup this way. 

    During processing, for each METHDR entry this map file is scanned to grab 
    the must restrictive matching record, and then a test of the TIMEDIR directory
    (the directory where UG generated machine run time files are output), is done
    to see if there is a matching file name. 

    The UG runtime files must have the following format:

    AAn...n[.txt]
    n...nAA[.txt]

    
    The n...n matches the order number for the job, and based on a runtime parameter
    the program will try to match up to NDIGITS=k trailing digits. Thus if the trailing
    digits parameter is 5 and the order number is 214702, then when the directory 
    is searched, for a prefix of WX with 5 digits, the search string would be 
    'WX14702*' where only the trailing 5 sigits are used. If K=0, then the string
    would be 'WX214702*' (note that the file extension and trailing characters are
    always ignored because a trailing * is always added to the search strign.)

    Also there can be multiple suffix or prefix definitions, which will be combined
    for the total time required. 

    In Markham for example, the mandrel back operation can be split across multiple 
    programs in certain cases. These are all defined by the same sequence number in 
    the method however. Thus multiple operations must be summed together to get the 
    time for the actual sequence number. 

    NOTE: You can only define a suffix OR a prefix, but not both. If both are defined
    then only the prefix will be used. 

    For a search pattern of suffix WX and K=5 the string would be '14702WX*' and 
    so on. The prefix and suffix and 

 */
int LoadNCTimingMap(char *filename, RouteDataRecMap &timemap, FILE *fplog) ;



#endif 