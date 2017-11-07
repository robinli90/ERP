// BatchUPDDlg.h : header file
//

#pragma once
#include "afxwin.h"

#include "batchsup.h"
#include "EditGrid.h"


/*!
    the job number is stored as a string because there are leading 
    zeroes in this number within the CMS database which can be significant
    when trying to find records in the database. 


 */
struct JobRec
{
    csString jobnum ; // work order number (i.e. job number) this is the key
    CDateTime startTime ; // first RUN time for this record
    CDateTime lasttime ; // last job start time
    double totalTime ; // total time in minutes
    char res[16] ; // resource last loaded on - key into ResRecMap. 
    int evtid ; // last event id number

    int sonum ; // sales order number (shop order number)
    char part[32] ; 
    int seqnum ; 
    char opname[16] ; 
    int batchid ; 
    char dept[8] ; // includes the 3 digit plant prefix

    int state ;  
    int b40005 ; // has a 40005 production record. 

    int bModified ; 
    double actualTime ; // this is the user entered value
    
} ; 

typedef map<csString, JobRec>  JobRecMap ; 
typedef map<csString, JobRec>::iterator  JobRecMapItr ; 

struct ResRec
{
    csString res ; // matches the key

    csString  lastJob ; 
    CDateTime lastTime ; 
    int lastEvent ; // last event number

    BEventRecVec evvec ; // sequential list of events based on time
    // for this resource. 
} ; 


typedef map<csString, ResRec>  ResRecMap ; 
typedef map<csString, ResRec>::iterator  ResRecMapItr ; 

struct ResRecRef
{
    ResRec *prr ; 
    int irr ; 
} ;

typedef vector<ResRecRef> ResRecRefVec ; 


// To group all the jobs by resource, this key table is built after 
// the fact and links the ResMap records to the JobMap records so 
// that all the job data can be read sorted by resource. The key for 
// this will be the resource string for 8 characters left justified 
// and blank filled and then the job number for 20 characters left 
// justified and blank filled. 

struct ResJobXRef
{
    csString key ; 
    csString res ; 
    csString job ; 

    // The index of this specific job reference in the cjobdrVec[] array
    int idx ; // used in master mode

    JobRecMapItr ijm ; 
    CMSJobMapItr ijob ; 

    void SetKey(int seqnum=0) ; 
} ; 


typedef map<csString, ResJobXRef>  ResJobMap ; 
typedef map<csString, ResJobXRef>::iterator  ResJobMapItr ; 

// CBatchUPDDlg dialog
class CBatchUPDDlg : public CDialog
{
    // Construction
public:
    CBatchUPDDlg(CWnd* pParent = NULL);	// standard constructor

    int deptMode ; // if 0 then do full master mode processing

    // Dialog Data
    enum { IDD = IDD_BATCHUPD_DIALOG };
    CComboBox deptCombo;

    // This is the master event map 
    JobRecMap jobmap ; 
    ResRecMap resmap ; 
    BEventRecVec processedTasks ; // these tasks were processed. 

    BlanksRecVec bkvec ;
    SerialRecMap sermap ; 
    MaterialRecMap mtlmap ; 

    // This is the master jobs map 
    CMSJobMap jobsmap ; 
    int numRows ; 
	int NitridS;
	int NitridArc;
	int ProgressCount;
	csString NitridPrtCode;
    JobRec *InitJobRec(BEventRec &evrec) ;

    //! start the job clock running, and initialize record if required
    /*!
        Returns 
            0 - set run state OK
            1 - RUN when in RUN state
     */
    int StartJobClock(BEventRec &evrec) ;
    //int GetNitridInfor(ResRecRefVec &rrr);
    //! Stop the clock and return status
    /*!
        Returns values: 
            1 = if the clock was updated
            2 = error, stop time is before current start time.
            3 = job was not in run state, no start defined
           -1 = job never initialized yet (doesn't exist yet)

     */
    int StopJobClock(csString &lastJob, BEventRec &evrec) ;

    //! Loads the mtlmap and sermap member variables
    int LoadSerialNumbers() ; 

    int Split(char *input, char *delimiter, char output[][256]);

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


    // Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    void LoadJobListMaster() ;
    void LoadJobListByDept(csString &batchIDlist) ;

    int SaveBatchFlatFile() ;

    int UpdateArcFlag() ; 
    int SaveUpdateArcFlag() ; 

    void FindMatchingSerial(CMSJobMapItr &ijm, RouteDataRec *prr) ;
    
    // Returns a valid serial number (usually == sernum)
    int ValidateSerialNumber(CMSJobMapItr &ijm, RouteDataRec *prr, int sernum) ;

    int GetStopTime(ResRecRefVec &rrv, CDateTime &stoptime) ;
    
    int LoadBlankRecord(csString &sonum, csString &empnum, csString &prtcode, 
                        csString &task, csString &station, csString &N1, 
                        csString &S1, csString &S2, csString &tasktime)  ;

    int LoadPickBlankRec(csString &sonum, csString &empnum,  csString &prtcode, 
                         csString &task, csString &station, 
                         csString &S1, csString &S2, csString &tasktime) ;


    CEditGrid m_grid ; 
    afx_msg void OnBnClickedSave();
    DECLARE_EVENTSINK_MAP()
    void DblClickMsflexgrid1();

    int ProcessEvent(EventData *ped, 
                    csString &rtype,
                    csString &sonum, 
                    csString &task, 
                    csString &empnum, 
                    csString &station, 
                    time_t   &eventTime,
                    csString &prtcode, 
                    csString &arc,
                    csString &R1,
                    csString &S1) ;

    afx_msg void OnBnClickedButtonStart();
	CProgressCtrl m_Progress;
	COleDateTime m_ToTime;
	COleDateTime m_FromTime;
} ;
