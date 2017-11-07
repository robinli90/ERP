

#define     START_TASK          0x01 
#define     STOP_TASK           0x02
#define     TASK_EVENT          0x04
#define     TASK_STATUS         0x08

#define     RUN_STATE           0x01

struct EventKey
{
    csString resre ; 
    int ordnum ; 
    int seqnum ; 
    csString part ; 
    int sonum ; 

    bool operator<(const EventKey &b) 
    {
        if (resre < b.resre)
            return true ; 
        else if (resre == b.resre)
        {   // Test sub fields
            if (ordnum < b.ordnum) 
                return true ; 
            else if (ordnum == b.ordnum)
            {
                if (seqnum < b.seqnum)
                    return true ; 
            }
        }
        return false ; 
    }
} ; 

struct BlankBatchRec
{
    csString sonum ; 
    double qty ; 
    int empnum ; 
    csString prtcode ; 
    csString taskcode ; 
    csString part ; 
    int serial ; 
    int seqnum ; 
    csString tasktime ; 
    csString mtl ; 
    csString station ; 
    csString res ; 
    csString dept ; 
    csString mtlqty ; 
    csString mtlunit ; 
    bool pickRec ; 
} ; 

typedef vector<BlankBatchRec> BlanksRecVec ; 

bool operator<(const EventKey &a, const EventKey &b) ; 

struct BEventRec
{
    int ordnum ; 
    int event ; // the last event 
    int seqnum ; 
    int bHas40005 ; // true if 40005 is recorded.
    csString cmspart ; 
    csString dept ; 
    CDateTime dt ; 
    csString jobnum ; 
    csString resource ; 
    csString opercode ; 
    CDateTime dtLastShift ; 
    int itemNumber ; 
    int empnum ; 
    int batchID ; 
    int serialNum ; // in case there are multiple serial number records

    // Used for batch mode processing
    csString part ; 
    csString task ; 
    csString station ; 

    csString rtype ; 

    char arcState ; // initial ARC field status when record was read.
    // used to set the ARC field state during processing
    char setArcState ; 

    //! Returns the task event type
    //!         : 0x01=start 
    //!         : 0x02=stop
    //!         : 0x03=pulse (start+stop)
    int TaskType() ; 

    //! Returns true if this is a manual task, and sets the 
    //! day shift start-stop times
    int ManualTask(CDateTime &shiftStart, CDateTime &shiftStop) ; 

} ; 


typedef vector<CMSJob*> CMSJobPtrVec ; 

struct CMSOrdXRef
{
    csString ordernum ; 
    CMSJobPtrVec jv ; 
} ; 


struct SerialRec ;
typedef map<int, SerialRec> SerialRecMap ; 
typedef map<int, SerialRec>::iterator SerialRecMapItr ; 

// contains all records for a particular material type so that we can reference 
// serial number data
struct MaterialRec
{
    csString mtl ; // H-13 9 DIA for example, this is the map key
    SerialRecMap sermap ; // all serials for this material type. 
} ; 

typedef map<csString, MaterialRec> MaterialRecMap ; 
typedef map<csString, MaterialRec>::iterator MaterialRecMapItr ; 

struct SerialRec 
{
    int sernum ; 
    MaterialRecMapItr imm ; 
    double seriqty ; // current quantity as defined in the SERI table at start of run
    double consqty ; // current consumed quantity defined in the SERI table
    double usedqty ; // the amount consumed during this run, cannot exceed seriqty
} ;




typedef map<csString, CMSOrdXRef> CMSOrdXRefMap ; 
typedef map<csString, CMSOrdXRef>::iterator CMSOrdXRefMapItr ; 


// typedef map<EventKey, BEventRec> EventMap ; 
// typedef map<EventKey, BEventRec>::iterator EventMapItr ; 
typedef map<csString , BEventRec> EventMap ; 
typedef map<csString , BEventRec>::iterator EventMapItr ; 

typedef vector<BEventRec> BEventRecVec ; 

typedef map<csString , csString> StringMap ; 
typedef map<csString , csString>::iterator StringMapItr ; 




