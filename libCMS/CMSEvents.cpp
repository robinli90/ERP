// CMSEvents.cpp 

// #include <ugutils.h>

#include <CSstdlibs/cslib.h>

#include "Log.h"
#include "CMSBOMRTE.h"


// FILE *fplog = stdout ; 

void LogError(char *estr)
{
    if (gCMSparms.pevp->fpLOG)
    {
        CDateTime dt ; 
        dt.SetNow() ; 
        fprintf(gCMSparms.pevp->fpLOG, "%02d-%02d-%02d:", 
                (int)dt.m_nHours, (int)dt.m_nMins, (int)dt.m_nSecs) ; 
        fprintf(gCMSparms.pevp->fpLOG, "%s", estr) ;  
        fflush(gCMSparms.pevp->fpLOG) ; 
    }
}

void Log2Error(char *estr, int noStdOut)
{
    if (gCMSparms.pevp->fpLOG)
    {
        fprintf(gCMSparms.pevp->fpLOG, "%s\r\n", estr) ;  
        fflush(gCMSparms.pevp->fpLOG) ; 
    }
    if (!noStdOut)
        printf("%s\n", estr) ; 
}

// ==============================================================
//          EventData Class
// ==============================================================
/*!
    Generate a unique control ID so that we can match this record
    up with the response data queue message. 

    WARNING TODO WARNING TODO WARNING TODO WARNING TODO 
    WARNING TODO WARNING TODO WARNING TODO WARNING TODO 
    WARNING TODO WARNING TODO WARNING TODO WARNING TODO 

    After the 32 bit timer roles over 2,000,000,000 in 25 years or so
    the key in the RPRA table won't be unique and collisions will start to 
    occur in the Data queue processor. Sometime before that, a 64 bit 
    ASCII encoding of this field will be required to ensure that it remains 
    unique. 

    There is a problem here if 100 or so records are run all at once. Then
    the process is stopped and then run again. At this point there could 
    be duplicate RPRA record key errors since the key is using timet for 
    synchronizing itself. 

    "Duplicate record key in member RPRA"

    Seems that what the Solarsoft guys originally told me was wrong, here 
    is the correct info:

        RPRA duplicate error means you are trying to write same record in RPRA..
        Key fields are; (line 46.00 to 51.00)
         
         
        0023.00      A*================================================================          
        0024.00      A                                      UNIQUE                               
        0025.00      A          R RPRAR                                                          
        0026.00      A            ULBTID         9S 0       COLHDG('Batch ID')                   
        0027.00      A            ULPART        20A         COLHDG('Part #')                     
        0028.00      A            ULSEQ#         3S 0       COLHDG('Seq #')                      
        0029.00      A                                      EDTCDE(3)                            
        0030.00      A            ULJOB#        10A         COLHDG('Job #')                      
        0031.00      A            ULSDAT          L         COLHDG('Starting' 'Date')            
        0032.00      A                                      DFT('0001-01-01')                    
        0033.00      A            ULSTIM          T         COLHDG('Starting' 'Time')            
        0034.00      A                                      DFT('00.00.00')                      
        0035.00      A            ULEDAT          L         COLHDG('Ending' 'Date')              
        0036.00      A                                      DFT('0001-01-01')                    
        0037.00      A            ULETIM          T         COLHDG('Ending' 'Time')              
        0038.00      A                                      DFT('00.00.00')                      
        0039.00      A            ULTMZN         4A         COLHDG('Time' 'Zone' 'Code')         
        0040.00      a*  qualifies all dates/times                                               
        0041.00      a*  key to TMZN                                                             
        0042.00      A            ULENT1         5S 0       COLHDG('Entry #' 'Level 1')          
        0043.00      A                                      EDTCDE(3)                         
        0044.00      A            ULENT2         5S 0       COLHDG('Entry #' 'Level 2')       
        0045.00      A                                      EDTCDE(3)                         
        0046.00      A          K ULBTID                                                      
        0047.00      A          K ULPART                                                      
        0048.00      A          K ULSEQ#                                                      
        0049.00      A          K ULJOB#                                                      
        0050.00      A          K ULSDAT                                                      
        0051.00      A          K ULSTIM                                                      
                    ****************** End of data ***********************************************

    Note: this references the RPRA table (there is no RPRAR table so not sure what 
    the extra R is for in the first line (line 25.00)

 */
void EventData::GenControlID(time_t &seed, char lastChar)
{
    seed++ ; 
    char timestr[32] ; 
    sprintf(timestr, "%u", (unsigned long)seed % 1000000000) ; 
    // controlID[0] = task[0] ; 
    // controlID[1] = task[1] ;
    if (lastChar)
        controlID[0] = lastChar ; 
    else 
        controlID[0] = gCMSparms.plantID[2] ; 
    StrCpyBlankFill(controlID + 1, timestr, 9) ;
    controlID[10] = 0 ; 
}



// Make sure the sonum, empnum task, and station are set before calling this
void EventData::SetBaseFields(char *dbname, time_t &seed, char idChar)
{
    dataLength = 577 ; 

    GenControlID(seed, idChar) ;
    StrCpyBlankFill(eventData,      controlID, 10) ;
    sprintf(empTag, "%u", empnum) ;

    StrCpyBlankFill(eventData + 10, deviceID, 5) ;
    StrCpyBlankFill(eventData + 15, dbname, 10) ;
    StrCpyBlankFill(eventData + 25, "SF223DQO", 10) ;
    StrCpyBlankFill(eventData + 35, deptCode, 5) ;
    StrCpyBlankFill(eventData + 40, resCode, 5) ;
    StrCpyBlankFill(eventData + 45, empTag, 15) ;
    StrCpyBlankFill(eventData + 60, dateStr+2, 6) ;
    StrCpyBlankFill(eventData + 66, timeStr, 6) ;
}

void EventData::SetBaseTime(CDateTime &dt)
{
    sprintf(dateStr, "%04d%02d%02d", dt.m_nYear, dt.m_nMonth, dt.m_nDay) ; 
    sprintf(timeStr, "%02d%02d%02d", dt.m_nHours, dt.m_nMins, dt.m_nSecs) ; 

    StrCpyBlankFill(eventData + 60, dateStr+2, 6) ;
    StrCpyBlankFill(eventData + 66, timeStr, 6) ;
}

void EventData::Set10000(void)
{
    strcpy(eventCode, "10000") ; 
    StrCpyBlankFill(eventData + 72, eventCode, 5) ;

    // set the entire data payload to blanks. 
    char *pbuf = eventData + 77 ;
    memset(pbuf, 0x20, 500) ;

    pbuf[ 0 ] = '2';    // 1 - Based on System Time, 2=entered time
    sprintf(pbuf + 1, "%04d-%02d-%02d", year, month, day);      //Shift Date
    pbuf[ 11 ] = '1' ;  // Shift
    //pbuf[ 12 ] = ;    // Shift Group
    pbuf[ 13 ] = '2';   // Clear Loading List(2 - Do not Clear loading list)
    pbuf[ 14 ] = '2';   // Edit Mode(2 - Do not allow the user to edit the information)
    pbuf[ 15 ] = '2';   // Display Verification(2 - Do not display verification)
    pbuf[ 16 ] = '2';   // Check Load List(2 - No Check)
    pbuf[ 17 ] = '2';   // Check Batch is Shifted Out(2 - No Check)
}

void EventData::Set10001(void)
{
    strcpy(eventCode, "10001") ; 
    StrCpyBlankFill(eventData + 72, eventCode, 5) ;

    // set the entire data payload to blanks. 
    char *pbuf = eventData + 77;
    memset(pbuf, 0x20, 500);

    pbuf[ 0 ] = '2';        // 1-check capacity, 2-do not check capacity
    pbuf[ 1 ] = '1';        // 1-allow date/shift edit, 2-do not allow edit
    pbuf[ 2 ] = '2';        // 2 - Do not display verification
    pbuf[ 3 ] = '1';        // 1-from dept shift/time,2-from current system,3-manually
    //Reporting date, only used in batch mode, setting anyways
    // sprintf(pbuf + 4, "%04d-%02d-%02d", year, month, day) ;
    sprintf(pbuf + 4, "%04d-%02d-%02d", 1, 1, 1) ;
    pbuf[ 14 ] = ' ' ;      // optional
    //pbuf[ 16 ] = ' ';     // New Shift Group
    // Start date, probably ignored but setting this anyways
    // sprintf(pbuf + 16, "%04d-%02d-%02d", year, month, day) ;
    sprintf(pbuf + 16, "%04d-%02d-%02d", 1, 1, 1) ;
    // Start time, probably ignored but setting this anyways
    sprintf(pbuf + 26, "%02d.%02d.%02d", 0, 0, 0) ;
    pbuf[ 34 ] = '2' ;  // check load list 1-must not contain active serial, 2-nocheck
    pbuf[ 35 ] = ' ' ;  // mattec shift 2 code characters
    pbuf[ 36 ] = ' ' ;  // 
    pbuf[ 37 ] = '1';   // 1 - logout all multi logins, 2-do not logout multi's
}


void EventData::Set10002(void)
{
    strcpy(eventCode, "10002") ; 
    StrCpyBlankFill(eventData + 72, eventCode, 5) ;

    // set the entire data payload to blanks. 
    char *pbuf = eventData + 77;
    memset(pbuf, 0x20, 500);

    pbuf[ 0 ] = '2';        // 2 - Use next report date/shift (Do not check Capacity)
    pbuf[ 1 ] = '2';        // 2 - Allow no changes
    pbuf[ 2 ] = '2';        // 2 - Do not display verification
    pbuf[ 3 ] = '2';        // 1 - create new batch, 2 - will not create new batch
    pbuf[ 4 ] = '2';        // 2 - Will not prompt for create new Batch
    sprintf(pbuf + 5, "%04d-%02d-%02d", year, month, day);      // New Shift Date
    pbuf[ 15 ] = '1' ;       // New Shift
    //pbuf[ 16 ] = ' ';     // New Shift Group
    pbuf[ 17 ] = '2';       // 2 - No Check
    //pbuf[ 18 ] = pbuf[ 19 ] = ' '; // Mattec Shift
}

// Set all resources inactive
void EventData::Set10003(void)
{
    strcpy(eventCode, "10003") ; 
    StrCpyBlankFill(eventData + 72, eventCode, 5) ;

    // set the entire data payload to blanks. 
    char *pbuf = eventData + 77;
    memset(pbuf, 0x20, 500);

    pbuf[ 0 ] = '2';        // 1-system time, 2-reporting date, 3-(reporting date + 1)
    pbuf[ 1 ] = '2';        // 1-create new batch, 2-do not create new batch
    pbuf[ 2 ] = '2';        // 1-prompt create new batch, 2-do not prompt
}

// Set all resources continue
void EventData::Set10004(void)
{
    strcpy(eventCode, "10004") ; 
    StrCpyBlankFill(eventData + 72, eventCode, 5) ;

    // set the entire data payload to blanks. 
    char *pbuf = eventData + 77;
    memset(pbuf, 0x20, 500);

    pbuf[ 0 ] = '2';        // 1-system time, 2-reporting date, 3-(reporting date + 1)
}

void EventData::Set10100(void)
{
    strcpy(eventCode, "10100") ; 
    StrCpyBlankFill(eventData + 72, eventCode, 5) ;

    // set the entire data payload to blanks. 
    char *pbuf = eventData + 77;
    memset(pbuf, 0x20, 500);

    StrCpyBlankFill(pbuf, "DONE", 10) ; // Down Time Code
    pbuf[ 10 ] = '1';       // 1 - No Check
    pbuf[ 11 ] = '1';       // 1 - Edit is allowed
    pbuf[ 12 ] = '2';       // 2 - Do not display verification

    sprintf(pbuf + 13, "%04d-%02d-%02d", year, month, day);     // Down Date
    sprintf(pbuf + 23, "%02d.%02d.%02d", hour, mins, secs);     // Down Time
    pbuf[ 31 ] = '2';       // 2 - Down reason code is mandatory during event 10100
    pbuf[ 32 ] = '4';       // 4 - no: Current logic will be used & the labour records will not be stamped with part number.
    // 34 -53               // Do not prompt in feature detail maintenance.
}

// When rerun mode is set, then we are specifying the reporting date
// and time to replay previous data. 
void EventData::Set10151(int rerunMode)
{
    strcpy(eventCode, "10151") ; 
    StrCpyBlankFill(eventData + 72, eventCode, 5) ;

    char *pbuf = eventData+77 ;
    memset(pbuf, 0x20, 500) ;  // set the entire data payload to blanks. 
    StrCpyBlankFill(pbuf, jobnum, 10) ;
    char seqnumStr[10] ; 
    sprintf(seqnumStr, "%3d", atoi(seqnum)) ; 
    StrCpyBlankFill(pbuf + 10, seqnumStr, 3) ;
    pbuf[13] = '1' ; // entry edit time check
    pbuf[14] = '1' ; // edit date time allowed (allowed)
    pbuf[15] = '2' ; // check schedule (1=yes, 2= do not)
    pbuf[16] = '2' ; // display verification (2=do not)
    pbuf[17] = '2' ; // do not reset part counter
    // ZeroPadInt(pbuf + 18, orderNumber, 9) ;
    // ZeroPadInt(pbuf + 27, itemNumber, 3) ;
    pbuf[30] = '1' ; // Master label mode (1=manual)
    pbuf[31] = '1' ; // clear loading list (2=do not clear)

    if (rerunMode)
    {
        sprintf(pbuf+32, "%04d-%02d-%02d", year, month, day) ;
        sprintf(pbuf+42, "%02d.%02d.%02d", hour, mins, secs) ;
    }
    else
    {
        sprintf(pbuf+32, "0001-01-01") ;
        sprintf(pbuf+42, "00.00.00") ;
    }
    StrCpyBlankFill(pbuf + 50, "010", 3) ;

    // Event password is blank 54 for 10 chars

    pbuf[63] = '1' ; // input mode: 1=default, 2=serial, 
    pbuf[64] = '1' ; // default input mode: 1=scanned, 2=keyed, 
    pbuf[65] = '2' ; // check for rework 1=yes, 2=no
    // event ID for 10152 (default = blank) 66 for 20
    pbuf[86] = '2' ; // maintain recieve to location, 1=yes, 2=no
    // FG receive location 87 for 6 bytes
    // WIP rcv location, 93 for 6
    pbuf[99] = '2' ; // check load list 1=yes, 2=no
    pbuf[100] = '2' ; // view method notes 1=Y  2=N
    // ID for 70002, 101 for 20
}

void EventData::Set10151Time(CDateTime &dt)
{
    char *pbuf = eventData+77 ;
    char tmpstr[32] ; 
    sprintf(tmpstr, "%04d-%02d-%02d", dt.m_nYear, dt.m_nMonth, dt.m_nDay) ; 
    StrCpyBlankFill(pbuf + 32, tmpstr, 10) ;

    sprintf(tmpstr, "%02d.%02d.%02d", dt.m_nHours, dt.m_nMins, dt.m_nSecs) ; 
    StrCpyBlankFill(pbuf + 42, tmpstr, 8) ;
}

void EventData::Set20000(void)
{
    strcpy(eventCode, "20000") ; 
    StrCpyBlankFill(eventData + 72, eventCode, 5) ;

    // set the entire data payload to blanks. 
    char *pbuf = eventData + 77;
    memset(pbuf, 0x20, 500);

    pbuf[ 0 ] = '2';        // 3 - Use System Time
    pbuf[ 1 ] = '1';        // 1 - Edit is allowed
    pbuf[ 2 ] = '1';        // 1 - Edit is allowed
    pbuf[ 3 ] = '2';        // 2 - Do not display verification
    pbuf[ 4 ] = '1';        // 1 - Run once and Exit Program
    pbuf[ 5 ] = '2';        // 2 - Signal-Resource Signin
    // 7 - 18               // Allow Blank If Enter, Code Must Be Valid From SFMRH
    pbuf[ 18 ] = '2';       // 2 - Do Not Use Multi-Resource Ref Code
    pbuf[ 19 ] = '2';       // 2 - Do Not Snap to Shift start time, use the actual time
    // 24 - 38              // This is an optional field and is only used for batch execute mode. Do not prompt in feature detail maintenance.
    StrCpyBlankFill(pbuf + 23, empTag, 15) ;
    sprintf(pbuf + 38, "%04d-%02d-%02d", 0001, 01, 01);     // Reporting Date
    pbuf[48] = 0x20 ;
    //pbuf[ 48 ] =          // This is an optional field and is only used for batch
                            // execute mode. Required when X1MULT = '1' and X1REFF = '2'
                            // Do not prompt in feature detail maintenance.
    //pbuf[ 53 ] =          // This is an optional field and is only used for batch
                            // execute mode. Required when X1MULT = '1' and X1REFF = '2'
                            // Do not prompt in feature detail maintenance.
    //pbuf[ 58 ] =          // This is an optional field and is only used for batch
                            // execute mode to allow overriding the reporting shift.
                            // Do not prompt in feature detail maintenance.
    // sprintf(pbuf + 59, "%04d-%02d-%02d", year, month, day);     // Login Date
    // sprintf(pbuf + 69, "%02d.%02d.%02d", hour, mins, secs);     // Login Time
    sprintf(pbuf + 59, "%04d-%02d-%02d", 1, 1, 1);     // Login Date
    sprintf(pbuf + 69, "%02d.%02d.%02d", 0, 0, 0);     // Login Time
    pbuf[77] = 0x20 ; 
}

void EventData::Set20006(void)
{
    strcpy(eventCode, "20006") ; 
    StrCpyBlankFill(eventData + 72, eventCode, 5) ;

    // set the entire data payload to blanks. 
    char *pbuf = eventData + 77;
    memset(pbuf, 0x20, 500);

    StrCpyBlankFill(pbuf, jobnum, 10);
    StrCpyBlankFill(pbuf + 10, seqnum, 3);
    pbuf[ 13 ] = '1';       // 1 - Edit is allowed
    pbuf[ 14 ] = '1';       // 1 - No checks are performed
    pbuf[ 15 ] = '2';       // 2 - Do not check Production Schedule
    pbuf[ 16 ] = '2';       // 2 - Do not display verification
}

void EventData::Set20009(void)
{
    strcpy(eventCode, "20009") ; 
    StrCpyBlankFill(eventData + 72, eventCode, 5) ;

    // set the entire data payload to blanks. 
    char *pbuf = eventData + 77;
    memset(pbuf, 0x20, 500);

    pbuf[ 0 ] = '1';        // 1 - Edit is allowed
    pbuf[ 1 ] = '1';        // 1 - No checks are performed
    pbuf[ 2 ] = '2';        // 2 - Do not display verification
    StrCpyBlankFill(pbuf + 3, empTag, 15);
    // pbuf 4 - 18          // This is a REQUIRED field used for batch execute mode
                            // Do not prompt in feature detail maintenance.
}


void EventData::Set30000(void)
{
    strcpy(eventCode, "30000") ; 
    StrCpyBlankFill(eventData + 72, eventCode, 5) ;

    // set the entire data payload to blanks. 
    char *pbuf = eventData + 77;
    memset(pbuf, 0x20, 500);

    pbuf[ 0 ] = '1';        // 1 - Serial #
    pbuf[ 1 ] = '2';        // 1 - Scanned
    pbuf[ 2 ] = '1';        // 1 - Yes, no other changes made
    pbuf[ 3 ] = '2';        // 2 - Do not display verification
    pbuf[ 4 ] = '1';        // 1 - No check
    pbuf[ 5 ] = '1';        // 1 - Consumed Status is allowed
    pbuf[ 6 ] = '1';        // 1 - Run once and Exit Program
    pbuf[ 7 ] = '1';        // 1 - Exit Batch after pgm execute

    // Left justified blank padding
    // StrCpyBlankFill(pbuf + 8, serialNumber, 11); // this didn't work, failed without any error message
    // 
    // Integer right justified, leading zero fill
    // int serialNum = atoi(serialNumber) ; 
    // ZeroPadInt(pbuf + 8, serialNum, 11); // this didn't work, failed without any error message

    // Right justified leading blank padding
    StrCpyBlankFillRight(pbuf + 8, serialNumber, 11);

    /*
    Serial Number 11 9 19 11.0 S X1SERN
    label serial number used only for batch execute mode
    Required when X1VIEW=1
    Do not prompt in feature detail maintenance
    Supplier Serial Number 30 20 49 30 A X1SSRN
    Supplier serial number used only for batch execute mode
    Required when X1VIEW=2
    Do not prompt in feature detail maintenance
    Part Number 20 50 69 20 A X1PART
    Part number used only for batch execute mode
    Optional require when X1VIEW=3
    Do not prompt in feature detail maintenance
    Sequence Number 3 70 72 3.0 S X1SEQN
    Sequence number used only for batch execute mode
    Optional require when X1VIEW=3
    Do not prompt in feature detail maintenance
    Job Number 10 73 82 10 A X1JOBN
    Job number used only for batch execute mode
    Optional require when X1VIEW=3
    Do not prompt in feature detail maintenance
    Lot Number 15 83 97 15 A X1LOTN
    Lot number used only for batch execute mode
    Optional require when X1VIEW=3
    Do not prompt in feature detail maintenance
    */ 

    pbuf[ 97 ] = '1';       // 1 - Perform Serial Inventory Transfer
    pbuf[ 98 ] = '2';       // 1 - Perform Validation on Serial's Location
    pbuf[ 99 ] = '2';       // 2 - No
    pbuf[ 100 ] = '2';      // 2 - Do not set material lot number to production lot number.
    pbuf[ 101 ] = '3';      // 3 - Do Not Create
    /*
    Default Label Format 3 103 105 3 A X1LFMT
    Default Stock Room 6 106 111 6 A X1STKR
    Quantity 15 112 126 15.5 S X1QTY
    Quantity used only for batch execute mode
    Optional require when X1VIEW=3 and XCRTS = '1' or '2'
    Do not prompt in feature detail maintenance
    Out queue 10 127 136 10 A X1OUTQ
    Output queue used only for batch execute mode
    Optional require when XCRTS = '1'
    Do not prompt in feature detail maintenance
    */
    
    pbuf[ 136 ] = '2';      // 1 - Allow for part/ot input with blank lot#
    // This is the blow thru part, and has to be set to 2 otherwise an error message occurs
    // as follows: 
    //          "Response: 126866689202720272 - The input mode (1) must be set as part/lot"
    //          "when event option for blow thru part is set as allowed                   " 

    //pbuf[ 138 ]           // Fix Number to Run 2 138 139 2.0 S X1FIXR
                            // Fix Number to Run
                            // Optional, Required when X1EXEC=3
    pbuf[ 139 ] = '2';      // 2 - Do Not Allow Print Mas/Mix
    pbuf[ 140 ] = '1';      // 1 - No check serial earlier activation
    pbuf[ 141 ] = '2';      // 2 - Do not verify resource
    pbuf[ 142 ] = '2';      // 2 - Load all serial in Draw-From location, 2=No, 1=yes, 3=yes but ignore load list

}


void EventData::Set40000()
{
    strcpy(eventCode, "40000") ; 
    StrCpyBlankFill(eventData + 72, eventCode, 5) ;

    char *pbuf = eventData+77 ; 
    memset(pbuf, 0x20, 500) ;  
    pbuf[0] = '3' ; // set quantity
    StrCpyBlankFill(pbuf + 9, "EA", 3) ; // units
    pbuf[12] = '2' ; // edit quantity Y/N
    pbuf[13] = '2' ; // verification Y/N
    pbuf[14] = '2' ; // check material loading ????
    pbuf[15] = '1' ; // entry time edit check 1=no, 2=warn, 3=must be valid
    pbuf[16] = '2' ; // display lot association screen Y=1/N=2
    pbuf[17] = '2' ; // create employee audits Y/N
    pbuf[18] = '1' ; // execution mode 1=one time, 2=continuous
    pbuf[19] = '2' ; // check labour list, 1=Y, 2=N
    ZeroPadDbl(pbuf + 20, 0, 3, 1) ;
    pbuf[24] = '2' ; // employee ID on labels 
    StrCpyBlankFill(pbuf + 25, empTag, 15) ; // default employee tag#
    ZeroPadDbl(pbuf + 40, 1.0, 10, 5) ; // set quantity
    pbuf[55] = '2' ; // verify part sequence Y=1,2=N
    pbuf[56] = '2' ; // verify weight
    pbuf[57] = '2' ; // weight tolerance type, 1=quantity, 2=percentage
    ZeroPadDbl(pbuf + 58, 1.0, 4, 2) ; // weight tolerance

    pbuf[77] = '1' ; // allow work order over production ??
    pbuf[112] = '3' ; // check standard pack size 3=not required
    // 113 for 10) ; // output queue ???
    pbuf[123] = '1' ; // allow blank unit of measure

    // remainder not sure, have to look for the definitions for these. 

}

void EventData::Set40005(void)
{
    strcpy(eventCode, "40005") ; 
    StrCpyBlankFill(eventData + 72, eventCode, 5) ;

    // set the entire data payload to blanks. 
    char *pbuf = eventData + 77;
    memset(pbuf, 0x20, 500);

    pbuf[ 0 ] = '3';        // 1 - Zero, 2=std pack, 3=set quantity
                            // Set Quantity Obsolete 8 2 9 8.0 S X1RQTYX
                            // size changed: former field of X1RQTY

    StrCpyBlankFill(pbuf + 9, "EA", 3) ; // units
    pbuf[ 12 ] = '1';       // Edit quantity 1 - Yes Enabled, 2=no
    pbuf[ 13 ] = '2';       // display verification 1=yes, 2 - Do not display verification
    pbuf[ 14 ] = '3';       // 1 - Check Material Loading backflush only
                            // 2 - Check material loading list (all)
                            // 3 - Check backflush material loading with lot control
                            // 4 - Check all material with lot control

    pbuf[ 15 ] = '1';       // 1 - edit time No Check=1, 2=warn out of range, 3=error out of range
    pbuf[ 16 ] = '2';       // Display lot association, 1=yes, 2 - Do not display
    pbuf[ 17 ] = '2';       // create employee audits, 1=yes, 2 - Do not create
    pbuf[ 18 ] = '1';       // Execution mode, 1 - One Time, 2= continuous
    pbuf[ 19 ] = '2';       // Check labour list, 1=yes, 2 - Do not Check

    
    ZeroPadDbl(pbuf + 20, 1.0, 3, 1) ;     // Material Tolerance 4 21 24 4.1 S X1MTTL
    ZeroPadDbl(pbuf + 24, 1.0, 10, 5) ;     // Set Quantity 15 25 39 15.5 S X1RQTY
    pbuf[ 39 ] = '1';       // Allow Blank Unit of Measure 1 40 40 1 A X1BUNT
                            // 1 - Allow
                            // 2 - Do not Allow

    StrCpyBlankFill(pbuf + 40, partnum, 20) ;
    char tmpstr[64] ; 
    sprintf(tmpstr, "%3d", atoi(seqnum)) ; 
    StrCpyBlankFill(pbuf + 60, tmpstr, 3) ;
    StrCpyBlankFill(pbuf + 63, jobnum, 10) ;
    pbuf[88] = '2' ;
    pbuf[89] = '2' ;
    pbuf[90] = '1' ; // data collection date/time 1=yes, 2=no

    // Lot number, not sure what this is used for. 
    // sprintf(tmpstr, "%15d", 1) ; 
    // StrCpyBlankFill(pbuf + 73, jobnum, 15) ;
}

// ==============================================================
//          CMSEventProcessing Class Member Functions
// ==============================================================


CMSEventProcessing::CMSEventProcessing()
{
    bDisable10100 = false ; 
    bDoEmpTracking = false ; 
} 

//! CMSEventProcessing is the global data container for dealing with the event data queue
int CMSEventProcessing::LoadStationMap(char *filename) 
{
    char errmsg[1024] ;

    FILE *fp = fopen(filename, "rt") ; 
    if (!fp)
    {
        _snprintf(errmsg, 1000, "Error opening file %s\r\n", filename) ; 
        LogError(errmsg) ; 
        return -1 ; 
    }

    char buf[256] ; 
    int linenum = 0 ; 
    int reccount = 0 ; 
    while (fgets(buf, 255, fp))
    {
        linenum++ ; 
        csString ln(buf) ; 
        ln.Trim() ; 
        if (ln[0] == '#' || !ln.size())
            continue ; 

        StationMapRec srec ; 
        csString tok = ln.NextToken(",", 0) ; 
        tok.Trim() ; 
        if (!tok.size())
        {
            sprintf(errmsg, 
                "Null station code (1st field) reading %s, line %d\r\n", 
                filename, linenum) ; 
            LogError(errmsg) ; 
            continue ; 
        } ; 
        // Save the value
        CS_strmaxcpy(srec.station, tok.c_str(), 5) ; 

        tok = ln.NextToken(",") ; 
        tok.Trim() ; 
        if (!tok.size())
        {
            sprintf(errmsg, 
                "Null device id (field 2) reading %s, line %d\r\n", 
                filename, linenum) ; 
            LogError(errmsg) ; 
            continue ; 
        } ; 
        CS_strmaxcpy(srec.device, tok.c_str(), 5) ; 

        tok = ln.NextToken(",") ; 
        tok.Trim() ; 
        if (!tok.size())
        {
            sprintf(errmsg, 
                "Null department code (field 3) reading %s, line %d\r\n", 
                filename, linenum) ; 
            LogError(errmsg) ; 
            continue ; 
        } ; 
        CS_strmaxcpy(srec.depts, tok.c_str(), 5) ; 

        tok = ln.NextToken(",") ; 
        tok.Trim() ; 
        if (!tok.size())
        {
            sprintf(errmsg, 
                "Null resource code (field 4) reading %s, line %d\r\n", 
                filename, linenum) ; 
            LogError(errmsg) ; 
            continue ; 
        } ; 
        CS_strmaxcpy(srec.resre, tok.c_str(), 5) ; 

        
        // Save the record. 
        csString sreckey(srec.station) ; 
        stationMap.insert(pair<csString, StationMapRec>(sreckey, srec)) ; 
        reccount++ ; 
    }

    return reccount ;
}


int CMSEventProcessing::LoadTaskMap(char *filename) 
{
    char errmsg[1024] ;

    FILE *fp = fopen(filename, "rt") ; 
    if (!fp)
    {
        _snprintf(errmsg, 1000, "Error opening file %s\r\n", filename) ; 
        LogError(errmsg) ; 
        return -1 ; 
    }

    char buf[256] ; 
    int linenum = 0 ; 
    int reccount = 0 ; 
    while (fgets(buf, 255, fp))
    {
        linenum++ ; 
        csString ln(buf) ; 
        ln.Trim() ; 
        if (ln[0] == '#' || !ln.size())
            continue ; 

        TaskMapRec trec ; 

        // ===================================================
        //                      TASK CODE
        // ===================================================
        csString tok = ln.NextToken(",", 0) ; 
        tok.Trim() ; 
        if (!tok.size())
        {
            sprintf(errmsg, 
                "Null task code (1st field) reading %s, line %d\r\n", 
                filename, linenum) ; 
            LogError(errmsg) ; 
            continue ; 
        } ; 
        // Save the value
        csString toka = tok.NextToken("-", 0) ; 
        csString tokb = tok.NextToken("-") ; 
        if (tokb.size())
        {   // This is a start-stop pair
            CS_strmaxcpy(trec.task, toka.c_str(), 5) ; 
            CS_strmaxcpy(trec.stopTask, tokb.c_str(), 5) ; 
        }
        else
        {   // Just a standard task.
            CS_strmaxcpy(trec.task, tok.c_str(), 5) ; 
            trec.stopTask[0] = 0 ; 
        }


        // ===================================================
        //                      PART CODE
        // ===================================================
        tok = ln.NextToken(",") ; 
        tok.Trim() ; 
        if (!tok.size())
        {
            sprintf(errmsg, 
                "Null part code (field 2) reading %s, line %d\r\n", 
                filename, linenum) ; 
            LogError(errmsg) ; 
            continue ; 
        } ; 
        CS_strmaxcpy(trec.part, tok.c_str(), 4) ; 

        // ===================================================
        //                      MODE FLAGS
        // ===================================================
        // EVD_OUTPUT_RUN      = 0x01, 
        // EVD_OUTPUT_DOWN     = 0x02,
        // EVD_OUTPUT_PROD     = 0x04, 
        tok = ln.NextToken(",") ; 
        tok.Trim() ; 
        if (!tok.size())
        {
            sprintf(errmsg, 
                "Null mode (field 3) reading %s, line %d, ", 
                filename, linenum) ; 
            LogError(errmsg) ; 
            LogError("must be one of START NEXT STOP COMPLETE or TRACK\r\n") ; 
            continue ; 
        } ; 
        tok.ToUpper() ; 
        if (tok == "START")
        {
            trec.eventMode = EventData::EVD_OUTPUT_RUN ; 
        }
        else if (tok == "NEXT")
        {
            trec.eventMode = EventData::EVD_OUTPUT_RUN |
                             EventData::EVD_OUTPUT_PROD ; 
        }
        else if (tok == "STOP")
        {
            trec.eventMode = EventData::EVD_OUTPUT_DOWN ; 
        }
        else if (tok == "COMPLETE")
        {
            trec.eventMode = EventData::EVD_OUTPUT_DOWN | 
                             EventData::EVD_OUTPUT_PROD ; 
        }
        else if (tok == "TRACK")
        {
            trec.eventMode = EventData::EVD_OUTPUT_PROD ; 
        }
        else
        {
            sprintf(errmsg, 
                "Bad mode (field 3) reading %s, line %d, ", 
                filename, linenum) ; 
            LogError(errmsg) ; 
            LogError("must be one of START NEXT STOP COMPLETE or TRACK\r\n") ; 
            continue ; 
        }

        // ===================================================
        //                      OPCODE 
        // ===================================================
        tok = ln.NextToken(",") ; 
        tok.Trim() ; 
        if (!tok.size())
        {
            sprintf(errmsg, 
                "Null opcode id (field 4) reading %s, line %d\r\n", 
                filename, linenum) ; 
            LogError(errmsg) ; 
            continue ; 
        } ; 
        CS_strmaxcpy(trec.opcode, tok.c_str(), 5) ; 

        // ===================================================
        //                      SEQ#
        // ===================================================
        tok = ln.NextToken(",") ;
        tok.Trim() ;
        if (!tok.size())
        {
            sprintf(errmsg,
                "Null seq num id (field 5) reading %s, line %d\r\n", 
                filename, linenum) ; 
            LogError(errmsg) ; 
            continue ; 
        } ; 
        CS_strmaxcpy(trec.seqnum, tok.c_str(), 5) ; 

        // ===================================================
        //                      WHERE (optional)
        // ===================================================
        tok = ln.NextToken(",") ; 
        tok.Trim() ; 
        if (tok.size())
        {   // Then the optional WHERE field is defined
            switch(toupper(tok[0]))
            {
                case 'B' : 
                case 'D' : 
                case 'S' : 
                    trec.trackTo = tok[0] ; 
                    break ; 
                default :
                    sprintf(errmsg, 
                        "Unkown WHERE location of %c (field 6) reading %s, line %d\r\n", 
                        tok[0], filename, linenum) ; 
                    LogError(errmsg) ; 
                    break ; 
            }
        } 

        // Save the record. 
        csString treckey = trec.BuildKey() ; 

        pair<TaskMapItr, bool> inspair ; 
        inspair = taskMap.insert(pair<csString, TaskMapRec>(treckey, trec)) ;
        if (!inspair.second)
        {   // Then there was an error add this task, duplicate record
            sprintf(errmsg, "Duplicate TASK+PART key pair in taskmap file %s, line %d\r\n",
                        filename, linenum) ;
        }
        else
        {   // See if there is a matching stop task record that needs to be added
            // to the map as well. These are the SS-EE start/end task pairs. 
            if (trec.stopTask[0])
            {   // Then we need to save the stop task record also
                trec.eventMode = EventData::EVD_OUTPUT_DOWN |
                                EventData::EVD_OUTPUT_PROD ;

                treckey = trec.BuildStopKey() ; 
                trec.itmstart = inspair.first ; 
                taskMap.insert(pair<csString, TaskMapRec>(treckey, trec)) ; 
                reccount++ ; 
            }
            reccount++ ; 
        }
    }

    return reccount ;
}

int CMSEventProcessing::LookupSeqNumber() 
{
    int retcode = 0 ; 
    char qry[2048] ; 

    sprintf(qry, "SELECT EDSEQ# FROM %s.CJOBDR"
                 " WHERE EDJOB#='%s' and EDOPNM = '%s' and EDDEPT='%s'", 
                 m_db.dbname, evd.jobnum, evd.opCode, evd.deptCode) ; 

    int retry = 0 ; 
    while (retry++ < 4)
    {
        retcode = 0 ; 
        try
        {
            CSQLRecordset rs(m_db) ;
            rs << qry ; 
            int seq = 0 ;
            rs.SQLExec() ;
            while (rs.SQLFetch())
            {
                seq = atoi(rs.SQLGetData(1).c_str()) ;
                sprintf(evd.seqnum, "%03d", seq) ; 
            }

            if (seq == 0)
                retcode = -100 ; 
            break ; 
        }
        catch (CSQLException* e)
        {
            char msg[4096] ; 
            _snprintf(msg, 4096, 
                "SQL error %d getting doing SEQ# lookup for %s, %s, %s\n MSG: %s\r\n", 
                            (int)e->m_nRetCode, 
                            evd.jobnum, evd.opCode, evd.deptCode, 
                            e->m_strError.c_str()) ; 
            LogError(msg) ; 

            m_db.Reconnect() ; 
            retcode = -1 ; 
        }
    }

    return retcode ; 
}

/*
    Originally this was setup to map back to the resource defined in the routing, 
    because resources were being defined from the decade side that didn't exist 
    in the Solarsoft definitions, and solarsoft errored out on the data and thus 
    those tracking steps that referenced an non-existant resource in Solarsoft 
    were rejected. To work around this, the LookupResource() function was defined
    to grab the resource defined in the routing regardless of what the taskmap and
    stationmap definition files stated. This doesn't work though because the routing
    always uses the primary resource and there can't be any resource overlap in the
    use of resources (a resource of EMPL cannot be working on two jobs at the same
    time). 

    This creates a problem however, since a user may inadvertently enter a different
    resource to stop a job than the one used to start the job, and Solarsoft expects
    them to be the same. Thus the resource lookup varies depending on the situation.

    For 10151 events, the system simply uses the resource as defined in the taskmap 
    and stationmap files. If it is a 40005 event however, the resource is verified 
    against the SFTX table to make sure that is matches the resource in the 10151 
    start event, and if not logs an error, and maps the resource back to match the
    10151 resource to make Solarsoft happy. 
 */
int CMSEventProcessing::LookupResource() 
{
    int retcode = 0 ; 
    char qry[2048] ; 

    if (!(evd.eventMode & EventData::EVD_OUTPUT_PROD))
    {
        if (strlen(evd.resCode) == 0)
        {
            char msg[4096] ; 
            _snprintf(msg, 4096, "ERROR: For SEQ#=%s, DEPT=%s, JOB#=%s no resource code is defined.\r\n", 
                                    evd.seqnum, evd.deptCode, evd.jobnum) ; 
            LogError(msg) ; 
        }
        return 0 ; // no need to do this since it will not generate a 40005. 
    }

    // This event will report production so it needs to be matched to a 40005. 
    if (evd.seqnum[0] && atoi(evd.seqnum) > 0)
    {
        sprintf(qry, "SELECT Q4SEQ#,Q4RESC,Q4DEPT FROM %s.SFTX"
            " WHERE Q4JOBN='%s' AND Q4SEQ#='%s' AND Q4FTCD = '10151'"
            " ORDER BY Q4CDAT DESC, Q4CTIM DESC FETCH FIRST 1 ROWS ONLY" , 
                 m_db.dbname, evd.jobnum, evd.seqnum) ; 
    }
    else
    {
        sprintf(qry, "SELECT Q4SEQ#,Q4RESC,Q4DEPT FROM %s.SFTX"
            " WHERE Q4JOBN='%s' AND Q4DEPT = '%s' AND Q4FTCD = '10151'"
            " ORDER BY Q4CDAT DESC, Q4CTIM DESC FETCH FIRST 1 ROWS ONLY" , 
                 m_db.dbname, evd.jobnum, evd.deptCode) ; 
    }

    int retry = 0 ; 
    while (retry++ < 4)
    {
        try
        {
            CSQLRecordset rs(m_db) ;
            rs << qry ; 
            int seq = 0 ;
            csString res, dept ; 
            rs.SQLExec() ;
            while (rs.SQLFetch())
            {
                seq = atoi(rs.SQLGetData(1).c_str()) ;
                sprintf(evd.seqnum, "%03d", seq) ; 
                
                res = rs.SQLGetData(2).c_str() ;
                res.Trim() ; 

                dept = rs.SQLGetData(3).c_str() ;
                dept.Trim() ; 
            }

            if (seq == 0 && evd.seqnum[0])
                retcode = -100 ; // no record found
            else
            {
                if (evd.seqnum[0] == 0 || atoi(evd.seqnum) == 0)
                    sprintf(evd.seqnum, "%03d", seq) ; 
                else if (atoi(evd.seqnum) != seq)
                {
                    char msg[4096] ; 
                    _snprintf(msg, 4096, "WARNING: taskmap sequence=%s did not match CJOBDR seq3=%d for %s\r\n", 
                                    evd.seqnum, seq, evd.jobnum) ; 
                    LogError(msg) ; 
                }
                if (strcmp(evd.deptCode, dept.c_str()) != 0)
                {   // Then the department codes don't match
                    char msg[4096] ; 
                    _snprintf(msg, 4096, "WARNING: For SEQ#=%s mapped DEPT=%s but CJOBDR DEPT=%s, JOB#=%s, forcing to CJOBDR value\r\n", 
                                    evd.seqnum, evd.deptCode, dept.c_str(), evd.jobnum) ; 
                    LogError(msg) ; 
                    CS_strmaxcpy(evd.deptCode, dept.c_str(), 5) ; 
                }
                CS_strmaxcpy(evd.resCode, res.c_str(), 5) ; 
            }

            break ; 
        }
        catch (CSQLException* e)
        {
            char msg[4096] ; 
            _snprintf(msg, 4096, "SQL error %d getting max SO number\r\n MSG: %s\r\n", 
                            (int)e->m_nRetCode, e->m_strError.c_str()) ; 
            LogError(msg) ; 


            m_db.Reconnect() ; 
            retcode = -1 ; 
        }
    }

    return retcode ; 
}


//! Old function to map back the resource to the CJOBDR resource. 
int CMSEventProcessing::LookupResourceCJOBDR() 
{
    int retcode = 0 ; 
    char qry[2048] ; 

    if (evd.seqnum[0] && atoi(evd.seqnum) > 0)
    {
        sprintf(qry, "SELECT EDSEQ#,EDRESC,EDDEPT FROM %s.CJOBDR"
            " WHERE EDJOB#='%s' AND EDSEQ#='%s' AND EDOPNM = '%s'", 
                 m_db.dbname, evd.jobnum, evd.seqnum, evd.opCode) ; 
    }
    else
    {
        sprintf(qry, "SELECT EDSEQ#,EDRESC,EDDEPT FROM %s.CJOBDR"
                 " WHERE EDJOB#='%s' and EDOPNM = '%s' and EDDEPT='%s'", 
                 m_db.dbname, evd.jobnum, evd.opCode, evd.deptCode) ;
    }

    int retry = 0 ; 
    while (retry++ < 4)
    {
        try
        {
            CSQLRecordset rs(m_db) ;
            rs << qry ; 
            int seq = 0 ;
            csString res, dept ; 
            rs.SQLExec() ;
            while (rs.SQLFetch())
            {
                seq = atoi(rs.SQLGetData(1).c_str()) ;
                sprintf(evd.seqnum, "%03d", seq) ; 
                
                res = rs.SQLGetData(2).c_str() ;
                res.Trim() ; 

                dept = rs.SQLGetData(3).c_str() ;
                dept.Trim() ; 
            }

            if (seq == 0 && evd.seqnum[0])
                retcode = -100 ; // no record found
            else
            {
                if (evd.seqnum[0] == 0 || atoi(evd.seqnum) == 0)
                    sprintf(evd.seqnum, "%03d", seq) ; 
                else if (atoi(evd.seqnum) != seq)
                {
                    char msg[4096] ; 
                    _snprintf(msg, 4096, "WARNING: taskmap sequence=%s did not match CJOBDR seq3=%d for %s\r\n", 
                                    evd.seqnum, seq, evd.jobnum) ; 
                    LogError(msg) ; 
                }
                if (strcmp(evd.deptCode, dept.c_str()) != 0)
                {   // Then the department codes don't match
                    char msg[4096] ; 
                    _snprintf(msg, 4096, "WARNING: For SEQ#=%s mapped DEPT=%s but CJOBDR DEPT=%s, JOB#=%s, forcing to CJOBDR value\r\n", 
                                    evd.seqnum, evd.deptCode, dept.c_str(), evd.jobnum) ; 
                    LogError(msg) ; 
                    CS_strmaxcpy(evd.deptCode, dept.c_str(), 5) ; 
                }
                CS_strmaxcpy(evd.resCode, res.c_str(), 5) ; 
            }

            break ; 
        }
        catch (CSQLException* e)
        {
            char msg[4096] ; 
            _snprintf(msg, 4096, "SQL error %d getting max SO number\r\n MSG: %s\r\n", 
                            (int)e->m_nRetCode, e->m_strError.c_str()) ; 
            LogError(msg) ; 


            m_db.Reconnect() ; 
            retcode = -1 ; 
        }
    }

    return retcode ; 
}


int CMSEventProcessing::MapDecadeData(TaskMapItr &mappeditm, bool mapSO) 
{
    int retcode = 0 ; 
    char qry[2048] ; 
    int qlen ; 

    // Must map the modulo SO# back to an actual SO# 
    int mappedSO = evd.sonum ; // the default is to use the raw shop order number

    // SELECT DCORD# FROM EXCOPHASE1.OCRH WHERE DCPLNT='001' ORDER BY DCORD# DESC FETCH FIRST 1 ROWS ONLY
    if (mapSO)
    {
        sprintf(qry, "SELECT DCORD# FROM %s.OCRH WHERE DCPLNT='%s'"
                     " ORDER BY DCORD# DESC FETCH FIRST 1 ROWS ONLY", m_db.dbname, plantID) ; 


        int retry = 0 ; 
        while (retry++ < 4)
        {

            try
            {
                CSQLRecordset rs(m_db) ;
                rs << qry ; 
                int maxSO = 0 ;
                rs.SQLExec() ;
                while (rs.SQLFetch())
                {
                    csString ordnum = rs.SQLGetData(1).c_str() ;
                    ordnum.Trim() ;
                    maxSO = atoi(ordnum.c_str()) ; 
                }

                if (maxSO > 0)
                {   // Then we read back a valid order number so map things based 
                    // on the value of this order number
                    
                    /*
                        If N is the shop order number and M  = N % 100000 such that
                        M is the modulo value that the shop enters and uses to track
                        the job, then we have the following:
                    */

                    int SON = 0 ; 
                    int M = mappedSO % 100000 ; // get it in range just in case. 
                    int maxPRE = maxSO - (maxSO % 100000) ; // this is the current prefix 
                    int modMax = maxSO % 100000 ; 
                    if (modMax < 50000)
                    {   // Then we may have just wrapped to the next 
                        // set of 100k values
                        if (M < 50000)
                        {   // Then map it normally
                            SON = maxPRE + M ; // use the same base prefix
                        }
                        else 
                        {   // The working SO hasn't ticked up to next 100k block yet. 
                            if (maxPRE > 0)
                            {   // Thus shift it back one block
                                SON = maxPRE - 100000 + M ; 
                            }
                            else
                            {   // This would be an error condition
                                sprintf(qry, "SO# %d is out of range since current max order#=%d\r\n", 
                                                evd.sonum, maxSO) ; 
                                LogError(qry) ; 
                                retcode = -5 ; 
                            }
                        }
                    }
                    else
                    {   // Else the current number is closer to the high end. 
                        if (modMax < 50000)
                        {   // This would be an error condition, should never get an
                            // S.O. number in this range. 
                            sprintf(qry, "SO# %d is out of range since current max order#=%d\r\n", 
                                            evd.sonum, maxSO) ; 
                            LogError(qry) ; 
                            retcode = -6 ; 
                        }
                        else
                        {   // Just have to map normally. 
                            SON = maxPRE + M ; 
                        }
                    }

                    mappedSO = SON ; 
                }
                break ; 
           }
            catch (CSQLException* e)
            {
                char msg[4096] ; 
                _snprintf(msg, 4096, "SQL error %d getting max SO number\r\n MSG: %s\r\n", 
                                (int)e->m_nRetCode, e->m_strError.c_str()) ; 
                LogError(msg) ; 

                m_db.Reconnect() ; 
                retcode = -2 ; 
            }
        }
    }

    if (retcode)
        return retcode ; // some error occured. 

    qry[0] = 0 ;

    // We need to take the S.O. number as entered and map this to a work order 
    // number within the CMS system. To do the mapping the part code is used
    // to know what specific part to look for to back track to the work
    // order number. 

    // Also, we need to load all work orders associated with the sales order and 
    // then track against all relevant work orders as required. 
    // GL records for sequence numbers >30 AND <500 must be expanded and tracked
    // for each individual part. If between 30 and 500 and part specific, then
    // just that single work order should be processed. If <=30 OR >=500, then 
    // tracking should apply only to the master work order record. 


    // dnjob = JOB/WORK ORDER NUMBER 
    // dnitm# = ORDER ITEM #
    // dnpart = PART NUMBER (HD 9 X 3 MANDREL) 
    // dnnmat = NUMBER OF MATERIAL RECS (if > 1 then this is a master to an assembly)
    // dnnrot = number of routing records (could be useful)

    evd.orderNumber = mappedSO ; 
    evd.partCode = 0 ; // reset the best match part code variable

    char selectStr[256] ; 
    strcpy(selectStr, "SELECT dnjob,dnitm#,dnpart,dnnmat,dnnrot FROM ") ; 
    strcat(selectStr, m_db.dbname) ; 
    strcat(selectStr, ".cjobh" ) ;  
    
    if (evd.part[0] == 'G')
    {   // Entire part
        qlen = _snprintf(qry, 2000, "%s WHERE dnord# = '%d'", selectStr, mappedSO) ;
    }
    else if (evd.part[0] == 'F')
    {   // Feeder
        qlen = _snprintf(qry, 2000, "%s WHERE dnord# = '%d' AND dnpart like 'FDR%%'", 
                        selectStr, mappedSO) ; 
    }
    else if (evd.part[0] == 'M')
    {   // Mandrel
        qlen = _snprintf(qry, 2000, "%s WHERE dnord# = '%d' AND dnpart like 'H_%%M%%'", 
                        selectStr, mappedSO) ; 
    }
    else if (evd.part[0] == 'P')
    {   // Plate
        qlen = _snprintf(qry, 2000, "%s WHERE dnord# = '%d' AND"
                    " (dnpart like 'H_%%P%%' OR dnpart like 'SD%%')", selectStr, mappedSO) ; 
    }
    else if (evd.part[0] == 'B')
    {   // Backer
        qlen = _snprintf(qry, 2000, "%s WHERE dnord# = '%d' AND"
                    " (dnpart like 'H_%%B%%' OR dnpart like 'BA%%')", selectStr, mappedSO) ; 
    }
    else if (evd.part[0] == 'O')
    {   // Bolster
        qlen = _snprintf(qry, 2000, "%s WHERE dnord# = '%d' AND dnpart like 'BO%%'", 
                        selectStr, mappedSO) ;
    }
    else if (evd.part[0] == 'S')
    {   // Sub bolster
        qlen = _snprintf(qry, 2000, "%s WHERE dnord# = '%d' AND dnpart like 'SB%%'", 
                        selectStr, mappedSO) ;
    }
    else if (evd.part[0] == 'R')
    {   // dir ring
        qlen = _snprintf(qry, 2000, "%s WHERE dnord# = '%d' AND dnpart like 'R%%'", 
                        selectStr, mappedSO) ;
    }
    else
    {   // Error unknown part code. 
        char msg[2048] ;
        _snprintf(msg, 2000, "Unknown part type in MapDecade data, part='%c'\r\n", evd.part[0]) ; 
        LogError(msg) ; 
    }

    int retry = 0 ; 

    char lastPartCode = 0 ; 
    while (retry++ < 4)
    {
        retcode = 0 ; 
        try
        {
            /*
                For parts that have sub-assemblies (hollow dies only at this point), we  
                need to find the job record that best matches the part that was passed in. 
                the filtering above already does this, with the exception of 'G' type 
                parts which indicate global. 'G' type global records can only be passed
                to Solarsoft for tracking (and by extension at this point in the logic)
                for the master parts in assemblies. Master parts will only exist with
                hollow dies, and in that case the dnnmat record will be greater than 
                one to indicate the master job. Another check is that there will be 
                no MAND.., BACK..., PLATE... string at the end of the part designator. 
                Thus we need to loop through all the returned records and extract out
                the exact one that we need for tracking purposes. 
            */
            
            // Reset the part number which is used as record indicator. 
            evd.partnum[0] = 0 ; 
            evd.bIsHollowDie = 0 ; 
            evd.partCode = 0 ; 

            /*  WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
                
                If two identical parts are entered on the same order then this logic
                will break. The assumption is that there will only be a single part 
                of any one type on any individual order. 
            */

            int bReadRecord = 0 ; 

            CSQLRecordset rs(m_db) ;
            rs << qry ; 

            rs.SQLExec();

            // Set true if a master part record is read when tracking a GL type event
            bool bFoundMaster = false ; 

            while (rs.SQLFetch())
            {
                csString jobnum = rs.SQLGetData(1).c_str() ;
                jobnum.Trim() ;

                if (jobnum.size())
                {   // Then save the job record. 
                    csString item = rs.SQLGetData(2).c_str() ; 
                    item.Trim() ;

                    csString part = rs.SQLGetData(3).c_str() ; 
                    part.Trim() ; 

                    csString nmat = rs.SQLGetData(4).c_str() ; 
                    nmat.Trim() ; 

                    int numSubs = atoi(nmat.c_str()) ; 

                    csString nroute = rs.SQLGetData(5).c_str() ; 
                    nroute.Trim() ; 

                    /*
                        For GL tracking there are several possibilites. 

                        1) HD master parts exist
                            In this case we want to track the master part only, regardless
                            of whatever sub components may also exist. 
                        2) HD where no master parts exist
                            Here we must rank the parts and track the event against
                            the most significant part. These parts are ordered as follows
                             
                                PLATE    - rated higher for consistency since this is always present
                                MANDREL  - most complicated component so ranks next
                                FEEDER   - contains surfaceing potentially
                                BACKER   - next most common, with engraving etc...
                                BOLSTER  - from here on down it is arbitrary. 
                                SUB-BOLSTER
                                SUB-BACKER
                                RING

                        3) Solid die where no HD parts exists. Similar to above, in fact 
                            identical priority logic can be used since the mandrel will be skipped
                            and thus ignored. 

                     */
                  
                    if (evd.part[0] == 'G')
                    {   // Then we need to decide if this record is better than
                        // the others that have been read so far. 
                        
                        char partCode = PartCodeCharFromCMSPart(part) ;

                        // If the previous part code has a higher priority then 
                        // just continue and ignore this current part. 
                        if (IsOldPartHigherPriority(lastPartCode, partCode))
                            continue ; 

                        lastPartCode = partCode ; 

                        // Else use this part


                        /*
                            This was the original logic 

                        // Need to change this to prioritize the best part
                        if (evd.partnum[0])
                        {   // Then must test if the new record is better than the 
                            // existing record 
                            if (numSubs == 1 ||
                                (part.Left(2) == "HD" &&
                                (part.Find("MA", 4) || part.Right(1) == "M" ||
                                part.Find("PL", 4) || part.Right(1) == "P" ||
                                part.Find("BA", 4) || part.Right(1) == "B")))
                            {   // then ignore this part, since the part that is stored 
                                // should have been the master part of 'HD 9 X 5' for
                                // example. This one is then 'HD 9 X 5 MANDREL' which 
                                // is the sub-part and in this case we actually want 
                                // the master part. 
                                continue ; 
                            }
                        }
                        // else just save the current record

                        */
                    }

                    // Save the job number and other data
                    CS_strmaxcpy(evd.jobnum, jobnum.c_str(), 12) ; 
                    evd.itemNumber = atoi(item.c_str()) ; 
                    CS_strmaxcpy(evd.partnum, part.c_str(), 20) ; 
                    evd.nMatRecs = atoi(nmat.c_str()) ; 
                    if (evd.nMatRecs > 1)
                        evd.bIsHollowDie |= 0x01 ; 

                    evd.nRouteRecs = atoi(nroute.c_str()) ; 
                    if (!lastPartCode)
                        lastPartCode = part[0] ; 
                    evd.partCode = lastPartCode ; 

                    bReadRecord = 1 ; 
                }
            }

            if (!bReadRecord)
            {   // Then there is no work order for this job
                LogToFile(fpLOG, "No work order for order number %d\r\n", mappedSO) ; 
                char msgstr[1024] ;
                sprintf(msgstr, "No work order for order number %d\r\n", mappedSO) ; 
                LogError(msgstr) ; 
                throw -25 ; 
            }

            // Now have the job order number. Look up the task map record.
            
            // When searching for the task, a best choice match on the 
            // part designator must be done in order to select the proper
            // task record. This is to ensure that the correct sequence 
            // number record is retrieved. 

            TaskMapItr itm = FindTaskMatch(taskMap, evd.task, evd.part) ;
            if (itm == taskMap.end())
            {
                LogToFile(fpLOG, "Couldn't find CMS task for decade task='%s'\n", evd.task) ; 
                throw -20 ; 
            }

            // Now have the task which gives us the sequence number and opcode.
            CS_strmaxcpy(evd.seqnum, itm->second.seqnum, 5) ;
            CS_strmaxcpy(evd.opCode, itm->second.opcode, 5) ;
            evd.eventMode = itm->second.eventMode ; 

            csString station(evd.station) ;
            station.Trim().ToUpper() ;

            if (csString(evd.task ) == "CI" || csString(evd.task) == "CO" || 
                csString(evd.task ) == "C5" || csString(evd.task) == "C6")
            {   // Do a custom remap for EXCO, since this is likely 
                // the DSCN task. 
                station = "CM01" ; 
            }

            StationMapItr ism = FindStationMatch(stationMap, station) ; 
            if (ism == stationMap.end())
            {   // Then error out since we can't define proper station code. 
                throw -22 ;
            }

            if (csString(ism->second.device) == "IGNOR")
                throw -122 ;

            CS_strmaxcpy(evd.deviceID, ism->second.device, 5) ;
            CS_strmaxcpy(evd.deptCode, ism->second.depts, 5) ;
            CS_strmaxcpy(evd.resCode,  ism->second.resre, 5) ;

            // Next we have to get the Station Records data
            if (_stricmp(evd.resCode, "*EMPL") == 0)
            {   // Use the employee number as the resource ID
                _snprintf(evd.resCode, 6, "%d", evd.empnum) ; 
            }
            else if (bUseCJOBDRRes)
            {   // LookupResource also sets the sequence number so the second
                // part of this if is handled within the LookupResource() call. 
                LookupResource() ; 
            }

            if (atoi(evd.seqnum) == 0)
            {   // Then we need to lookup the sequence number from the 
                // operation code since it could vary for this task 
                // This typically happens on large parts where there are extra 
                // steps inserted in the standard routing. This data inconsistency
                // should be eliminated in the future which would render this code
                // pointless. 
                if (LookupSeqNumber())
                    throw -23 ; 
            }
            
            struct tm *ptm ;
            // time_t tnow ;
            // time(&tnow) ;
            // ptm = localtime(&tnow) ;
            ptm = localtime(&(evd.tasktime)) ;

            evd.year = ptm->tm_year + 1900 ; 
            evd.month = ptm->tm_mon + 1 ; 
            evd.day = ptm->tm_mday ; 
            
            evd.hour = ptm->tm_hour ; 
            evd.mins = ptm->tm_min ; 
            evd.secs = ptm->tm_sec ; 

            sprintf(evd.dateStr, "%04d%02d%02d", ptm->tm_year + 1900,
                                            ptm->tm_mon + 1,
                                            ptm->tm_mday) ;

            sprintf(evd.timeStr, "%02d%02d%02d", ptm->tm_hour,
                                            ptm->tm_min,
                                            ptm->tm_sec) ;
            break ; 
        }
        catch (CSQLException* e)
        {
            char msg[4096] ; 
            _snprintf(msg, 4000, "CMSBOMRTE::MapDecadeData  database errorcode = %d, msg = %s\r\n", e->m_nRetCode, e->m_strError.c_str()) ;
            msg[4000] = 0 ; 
            msg[4001] = 0 ; 
            LogError(msg) ; 
            e->Delete();

            LogError(qry) ; 
            LogError("\r\n") ; 

            m_db.Reconnect() ; 
            retcode = -100 ; 
        }
        catch(int err) 
        {
            sprintf(qry, "Error %d in CMSEventProcessing::MapDecadeData(...)\r\n", err) ; 
            LogError(qry) ; 
            retcode = err ; 
            break ; 
        }
    }

    return retcode ; 
}

/*
    Note: the concept of a batch presents a problem for the system since only
    a single active shift can occur for any given day. Thus a 10000 or 10001 
    should start the day and we should never shift out, EVER. Screw up a shift
    in terms of the dates and everything starts to break. It becomes a real 
    nightmare to try and repair the data after the fact.

    There is also the issue of forgetting to shift out, or the more common condition
    of weekends and holidays when no manager is present to shift out the previous
    day's jobs. In these cases the simplest thing is to allow the batch to span 
    several days, and then shift things out when everyone comes back to work on
    Monday (or whenever the holiday is over). 

    Thus this logic looks for a batch start that has not be shifted out to be 
    active and if that condition exists, then it returns true, otherwise it returns
    false, and a 10000 needs to be issued. This will almost always return false
    once normal operations have commenced. 


 */
int CMSEventProcessing::ActiveBatchShift(EventData *pevd)
{
    char qry[512] ; 

    if (!pevd)
        pevd = &evd ; 

    csString batchid ; 
    // First load all the respective batches that need to be considered
    _snprintf(qry, 500, "SELECT NWBTID FROM %s.RPRH  WHERE NWLABL = '%s%s' AND NWPOST = 'N'"
                        " ORDER BY NWCDAT DESC, NWCTIM DESC FETCH FIRST 1 ROWS ONLY", 
            m_db.dbname, pevd->deptCode, pevd->resCode) ; 

    int retcode = RUNMODE_ERROR ;  // unless we find what we are looking for then there is
    // not an active batch 

    int retry = 0 ; 
    while (retry++ < 4)
    {
        try
        {
            CSQLRecordset rs(m_db) ;
            rs << qry ; 
            rs.SQLExec();
            while (retcode == RUNMODE_ERROR && rs.SQLFetch())
            {
                batchid = rs.SQLGetData(1).c_str() ; 
                break ; // success, will only be one record
            }

            if (batchid.size())
                break ; 
        }
        catch (CSQLException* e)
        {
            char msg[2048] ;
            _snprintf(msg, 2048, "SQL error %d getting max SO number\r\n MSG: %.1000s\r\n",
                            (int)e->m_nRetCode, e->m_strError.c_str()) ;
            LogError(msg) ;

            m_db.Reconnect() ; 
            retcode = RUNMODE_DBERR ; 
        }
    }

    if (batchid.size() == 0)
        return  RUNMODE_NONE ; // nothing for this resource.

    /*
    _snprintf(qry, 255, "SELECT Q4BTID,Q4FTCD FROM %s.SFTX"
        " WHERE Q4DEPT = '%s' AND Q4RESC = '%s'"
        " AND (Q4FTCD = '10000' OR Q4FTCD = '10001' OR Q4FTCD = '10002' OR Q4FTCD = '10100')"
        " AND Q4CDAT = '%04d-%02d-%02d' ORDER BY Q4CDAT DESC, Q4CTIM DESC",
            m_db.dbname, 
            pevd->deptCode, pevd->resCode, pevd->year, pevd->month, pevd->day) ; 
    */

    // The "dept AND resc" on the where condition is redundant but left in for now. 
    _snprintf(qry, 500, "SELECT Q4BTID,Q4FTCD FROM %s.SFTX"
        " WHERE Q4BTID = %s AND Q4DEPT = '%s' AND Q4RESC = '%s'"  
        " AND Q4FTCD IN ('10000','10001','10002','10003','10004')"
        " ORDER BY Q4CDAT DESC, Q4CTIM DESC FETCH FIRST 1 ROWS ONLY",
            m_db.dbname, batchid.c_str(), pevd->deptCode, pevd->resCode) ; 

    // TODO verify what happens with 10003 and 10004 events, if unique records are created for 
    // each batch or if it is a single global record. 

    retcode = RUNMODE_ERROR ;  // unless we find what we are looking for then there is
    // not an active batch 

    retry = 0 ; 
    while (retry++ < 4)
    {
        try
        {
            CSQLRecordset rs(m_db) ;
            rs << qry ; 
            rs.SQLExec();
            while (rs.SQLFetch())
            {
                csString bid   = rs.SQLGetData(1).c_str() ; 
                bid.Trim() ; 
                csString event = rs.SQLGetData(2).c_str() ; 
                event.Trim() ; 

                int e = atoi(event.c_str()) ; 
                if (e == 10000 || e == 10001 || e == 10004)
                    retcode = RUNMODE_ACTIVE ; // there is an actve batch 
                if (e == 10002)
                    retcode = RUNMODE_DOWN ; 
                else if (e == 10003)
                {   // This is actually an error condition of sorts which we need
                    // to signal 
                    char msg[2048] ;
                    CDateTime dt ; 
                    dt.SetNow() ; 
                    char timestr[64] ; 
                    dt.FormatDateTimeSecs(timestr) ; 
                    _snprintf(msg, 2048, 
                            "WARNING: %s : BATCH shifted out with 10003. THIS SHOULD NEVER HAPPEN\r\n",
                                    timestr) ; 
                    LogError(msg) ;

                    // no active batch exists, or the parts have been shifted out.  
                    retcode = RUNMODE_DOWN ; 
                }
                else
                {
                    char msg[2048] ;
                    CDateTime dt ; 
                    dt.SetNow() ; 
                    char timestr[64] ; 
                    dt.FormatDateTimeSecs(timestr) ; 
                    _snprintf(msg, 2048, 
                            "ERROR: %s : ActiveBatchShift with event = %d. THIS SHOULD NEVER HAPPEN\r\n",
                                    timestr, e) ; 
                }
                break ; // this shouldn't be needed
            }

            if (retcode == RUNMODE_ERROR)
            {   // No DB error but we didn't read a record
                retcode = RUNMODE_NONE ; 
            }

            break ; 
        }
        catch (CSQLException* e)
        {
            char msg[2048] ;
            _snprintf(msg, 2048, "SQL error %d getting max SO number\r\n MSG: %.1000s\r\n",
                            (int)e->m_nRetCode, e->m_strError.c_str()) ;
            LogError(msg) ;

            m_db.Reconnect() ; 
            retcode = RUNMODE_DBERR ; 
        }
    }

    return retcode ; 
}

/*
int CMSEventProcessing::LoadActiveBatches(EventData *pevd)
{
    //     Determine whether an active batch exists for this PLANT/DEPT/RESOURCE combination.
    //     Returns NO, only in the situation 
    //     Grab the set of all batches that have been shifted out this morning in a time 
    //     window of 4AM to Now (so greater than 4AM today, where 4AM defines the earliest
    //     possible start time for a new day). Also ignore any new jobs started today, there
    //     really shouldn't be any of these but just in case. 
    // 
    //     Then any record that is included in those batches can be ignored for the purposes
    //     of the second query which will produce the list of all active batch records. 
    // 
    //  

    CDateTime dtfrom, dtto; 
    dtto.SetNow() ; 
    time_t t ;
    t = dtto.GetTimeT() ;
    t -= 2500000 ; 
    dtfrom.SetTime(t) ; 
    
    char qry[256] ;

    char datefrom[64], timefrom[64] ;
    char dateto[64],   timeto[64] ;

    dtfrom.FormatDate(datefrom) ; 
    strcpy(timefrom, "00.00.01") ;

    dtto.FormatDate(dateto) ; 
    strcpy(timeto, "04.00.00") ; 

    // This query will load all the 10001 events for the currently active batches
    // 
    //     This is the old method based on SFTX which potentially would miss 
    //     certain batches 
    // 
    // _snprintf(qry, 16000,
    //     "SELECT Q4BTID FROM %s.SFTX"
    //     " WHERE Q4CDAT >= '%s' AND Q4CTIM > '%s'"
    //     " AND Q4FTCD IN(10000,10001,10002,10003,10004,10005,10100)",
    //         gCMSparms.dbname, datestr, timestr) ;
    // 

    // Load all batches that have not been posted yet
    _snprintf(qry, 250,
        "SELECT NWBTID,NWLABL FROM %s.RPRH WHERE NWPOST = 'N'"
        " AND ((NWCDAT > '%s' AND NWCDAT < '%s') OR (NWCDAT = '%s' AND NWCTIM < '%s'))"
        " AND NWPLNT = '%s'",
                    gCMSparms.dbname, datefrom, dateto, dateto, timeto, 
                    gCMSparms.plantID) ;

    int retcode = 0 ; 

    try
    {
        CSQLRecordset rs(pApp->cmsdata.m_db) ;
        rs << qry ; 
        rs.SQLExec();
        while (rs.SQLFetch())
        {
            int fldnum = 1 ; 
            // Field 1 - DEPARTMENT
            csString bid = rs.SQLGetData(fldnum++).c_str() ; 
            bid.Trim() ; 

            if (batchIDlist.size())
                batchIDlist += "," + bid ; 
            else
                batchIDlist += bid ; 
        }
    }
    catch (CSQLException* e)
    {
        if (gCMSparms.pevp->fpLOG)
        {
            fprintf(gCMSparms.pevp->fpLOG, "SQL error %d reading back the active batch list:\n%s\n",
                        (int)e->m_nRetCode, e->m_strError.c_str()) ;
            fflush(gCMSparms.pevp->fpLOG) ;
        }
        batchIDlist.clear() ; 
        retcode = -1 ; 
    }


    return retcode ; 
}
*/

// Returns the task trackTo definition within the TaskMap.txt file 
// for the given taskcode 
// Returns 
// 0 (zero)=default both,
// B=force both with error msg
// S=solarsoft only
// D=decade only
char CMSEventProcessing::GetTaskMode(char *taskcode)
{
    csString tsk(taskcode) ; 
    TaskMapItr itm = taskMap.find(tsk) ; 
    if (itm != taskMap.end())
        return itm->second.trackTo ;
    return 0 ; 
}


/*! 
    When creating these event data records, the goal is to map decade
    baal file records into solarsoft event data. To do this a mapping
    table will be required. This will allow the differents plants to 
    set up there own custom tracking of the data. 

    The current baal tracks as follows:

        TASK|12345|99999|DDMF|09/08/2008 21:43:00|TEST

    The word TASK can be dropped

    12345 is the shop order number. This needs to be mapped to an actual 
    CMS work order number
    99999 is the employee tag# in CMS  (TAZMX1) 
    DD is the task code. This will have to be mapped to 
        an event and resource
    MF is the part designator
    Date and Time
    Station

    JOB# is the work order number, must read the OCRH

    We are tracking 
        10000 - start shift
        10151 - RUN START
        20000 - Attach User (Login)
        40005 - Report Task
        20009 - Detach User )Logout)
        10100 - RUN STOP
        10002 - end shift


 */

int CMSEventProcessing::TrackEvent()
{
    int ret = ActiveBatchShift() ; 
    int retcode = 0 ; 

    int outmode = evd.eventMode ; 

    CMSEventSet eset ; 
    eset.retry = 0 ; 
    eset.eidx = 0 ; 
    eset.nEVs = 0 ; 
    time(&eset.processTime) ; 

    if (empMap.find(evd.empnum) == empMap.end())
    {
        LogToFile(fpLOG, "ERROR: unknown employee number=%d, setting to 99999\r\n", 
                            evd.empnum) ; 
        evd.empnum = 99999 ; 
    }

    _snprintf(evd.empTag, 8,  "%05d", evd.empnum) ; 

    if (ret == RUNMODE_DOWN || ret == RUNMODE_NONE)
    {   // Then we are down or no active batch was sent
        
        LogToFile(fpLOG, "NO ACTIVE BATCH: Queuing 10000, starting batch for SO=%d, TSK=%s, PRT=%s, STA=%s\r\n",
                    evd.sonum, evd.task, evd.part, evd.station) ;

        evd.SetBaseFields(m_db.dbname, idseed) ;
        evd.Set10000() ; // Set mode to RUN
        evd.sendcount = 0 ; 
        evd.timeLastSend = 0 ; 
        eset.ev[eset.nEVs++] = evd ; 
        // CMS_SendEventToQ(evd) ; 

        // Sleep(1000) ; 

        if (outmode & EventData::EVD_OUTPUT_PROD)
            outmode |= EventData::EVD_OUTPUT_RUN ; // need to set this
        // the above if should only be needed in testing. If the data is 
        // accurate the this shouldn't happen.
    }
    // else an error occured or we have an active batch. 
    // If an error occured, still try to do the rest of the event tracking. 

    int b10151InSet = false ; 

    if (TestValidSeqnum(evd) > 0) 
    {
        if (outmode& EventData::EVD_OUTPUT_RUN)
        {
            LogToFile(fpLOG, " Queuing 10151: for SO=%d, TSK=%s, PRT=%s, STA=%s, WO#=%s\r\n",   
                        evd.sonum, evd.task, evd.part, evd.station, evd.jobnum) ; 

            evd.SetBaseFields(m_db.dbname, idseed) ; 
            evd.Set10151() ; 
            TestAndSet10151Time(evd) ;
            evd.sendcount = 0 ; 
            evd.timeLastSend = 0 ; 
            eset.ev[eset.nEVs++] = evd ; 
            b10151InSet = true ; 

            // Simply log the user on and off the machine so that we know who did the 
            // job. Other than that we will not assume that the employee is standing 
            // at the machine after it is setup. May need to extend this later to 
            // accurately track labour for manual operations such as DUMORE, manual mill,
            // manual lathe, welding, etc....
            if (bDoEmpTracking)
            {
                LogToFile(fpLOG, " Queuing 20000, 20009: for SO=%d, TSK=%s, PRT=%s, STA=%s, WO#=%s\r\n",   
                            evd.sonum, evd.task, evd.part, evd.station, evd.jobnum) ; 

                evd.SetBaseFields(m_db.dbname, idseed) ; 
                evd.Set20000() ; 
                evd.sendcount = 0 ; 
                evd.timeLastSend = 0 ; 
                eset.ev[eset.nEVs++] = evd ; 
                // CMS_SendEventToQ(evd) ; 

                // Log the user off the machine. 
                evd.SetBaseFields(m_db.dbname, idseed) ; 
                evd.Set20009() ; 
                evd.sendcount = 0 ; 
                evd.timeLastSend = 0 ; 
                eset.ev[eset.nEVs++] = evd ; 
                // CMS_SendEventToQ(evd) ; 
            }
        }

        if (b10151InSet && (outmode & EventData::EVD_OUTPUT_LOTSER))
        {
            LogToFile(fpLOG, " Queuing 30000: for SO=%d, TSK=%s, PRT=%s, STA=%s, WO#=%s\r\n",   
                        evd.sonum, evd.task, evd.part, evd.station, evd.jobnum) ; 

            evd.SetBaseFields(m_db.dbname, idseed) ; 
            evd.Set30000() ; 
            evd.sendcount = 0 ; 
            evd.timeLastSend = 0 ; 
            eset.ev[eset.nEVs++] = evd ; 
        }

        if (outmode & EventData::EVD_OUTPUT_PROD)
        {
            // If the last event for this resource is not 10151, then we must also output 
            // the 10151 if it isn't already in the event set
            time_t evtTime = 0 ; 
            // EventData evdtmp ;
            // evd.deptCode = ;
            // evd.resCode ;
            // evd.jobnum ; 
            // evd.seqnum ; 
            // if (GetLast10151Status(evd, evtTime) != EVENT_10151)
            if (!b10151InSet)
            {
                LogToFile(fpLOG, " Queuing 10151: for SO=%d, TSK=%s, PRT=%s, STA=%s, WO#=%s\r\n",
                            evd.sonum, evd.task, evd.part, evd.station, evd.jobnum) ;

                if (!Last10151Matches(evd))
                {
                    LogToFile(fpLOG, " Queuing 10151: for SO=%d, TSK=%s, PRT=%s, STA=%s, WO#=%s\r\n",   
                                evd.sonum, evd.task, evd.part, evd.station, evd.jobnum) ; 

                    evd.SetBaseFields(m_db.dbname, idseed) ;
                    evd.Set10151() ;
                    evd.sendcount = 0 ;
                    evd.timeLastSend = 0 ;
                    eset.ev[eset.nEVs++] = evd ;
                    b10151InSet = true ;
                }

                if (outmode & EventData::EVD_OUTPUT_LOTSER)
                {
                    LogToFile(fpLOG, " Queuing 30000: for SO=%d, TSK=%s, PRT=%s, STA=%s, WO#=%s\r\n",
                                evd.sonum, evd.task, evd.part, evd.station, evd.jobnum) ;

                    evd.SetBaseFields(m_db.dbname, idseed) ;
                    evd.Set30000() ;
                    evd.sendcount = 0 ;
                    evd.timeLastSend = 0 ;
                    eset.ev[eset.nEVs++] = evd ;
                }
            }

            if (!Event40005Done(evd, evtTime))
            {
                LogToFile(fpLOG, " Queuing 40005: for SO=%d, TSK=%s, PRT=%s, STA=%s, WO#=%s\r\n",   
                            evd.sonum, evd.task, evd.part, evd.station, evd.jobnum) ; 

                evd.SetBaseFields(m_db.dbname, idseed) ; 
                evd.Set40005() ; 
                evd.sendcount = 0 ; 
                evd.timeLastSend = 0 ; 
                eset.ev[eset.nEVs++] = evd ; 
                // CMS_SendEventToQ(evd) ; 
            }
        }
    }
    else
    {
        LogToFile(fpLOG, "ERROR: invalid sequence number for job=%s, seq=%s\r\n",
                        evd.jobnum, evd.seqnum) ;
        retcode = 0x02 ; 
    }


    // The down mode should always be called on its own, so we add the nEVs test
    // just to be safe
    if (!bDisable10100 && eset.nEVs < 7 && (outmode & EventData::EVD_OUTPUT_DOWN))
    {
        LogToFile(fpLOG, " Queuing 10100: for SO=%d, TSK=%s, PRT=%s, STA=%s, WO#=%s\r\n",   
                    evd.sonum, evd.task, evd.part, evd.station, evd.jobnum) ; 

        // evd.SetBaseFields(m_db.dbname, idseed) ; 
        // evd.Set20009() ; 
        // evd.sendcount = 0 ; 
        // evd.timeLastSend = 0 ; 
        // eset.ev[eset.nEVs++] = evd ; 
        // CMS_SendEventToQ(evd) ; 

        evd.SetBaseFields(m_db.dbname, idseed) ; 
        evd.Set10100() ; 
        evd.sendcount = 0 ; 
        evd.timeLastSend = 0 ; 
        eset.ev[eset.nEVs++] = evd ; 
        // CMS_SendEventToQ(evd) ; 
    }

    if (eset.nEVs > 0)
    {
        csString reskey = evd.BuildResKey(plantID) ; 
        evresmap[reskey].evlist.push_back(eset) ;
        if (evresmap[reskey].key.size() == 0)
            evresmap[reskey].key = reskey ; 

        // csString evkey(eset.ev[0].controlID) ; 
        // evdmap.insert(make_pair(evkey, eset)) ; 
    }

    return 0 ; 
}

/*
int CMSEventProcessing::Queue10001(char *dept, char *res)
{   
    CMSEventSet eset ; 
    eset.retry = 0 ; 
    eset.eidx = 0 ; 
    eset.nEVs = 0 ; 
    time(&eset.processTime) ; 

    LogToFile(fpLOG, "SHIFT OUT AND CONTINUE: starting batch for SO=%d, TSK=%s, PRT=%s, STA=%s\r\n",
                evd.sonum, evd.task, evd.part, evd.station) ;

    evd.SetBaseFields(m_db.dbname, idseed) ;
    evd.Set10001() ; // Set mode to RUN
    evd.sendcount = 0 ; 
    evd.timeLastSend = 0 ; 
    eset.ev[eset.nEVs++] = evd ; 

}
*/

int CMSEventProcessing::TrackEvent(cwbDQ_QueueHandle qhandle)
{
    int retcode = 0 ; 
    evd.SetBaseFields(m_db.dbname, idseed) ; 

    if (ActiveBatchShift() == 0)
    {
        evd.Set10000() ; 
        if (CMS_SendEventToQ(qhandle, evd))
            retcode |= 0x0001 ; 
        Sleep(1000) ; 
    }

    if (evd.eventMode & EventData::EVD_OUTPUT_RUN)
    {
        evd.Set10151() ; 
        TestAndSet10151Time(evd) ;

        if (CMS_SendEventToQ(qhandle, evd))
            retcode |= 0x0002 ; 
        Sleep(1000) ; 
    }

    if (evd.eventMode & EventData::EVD_OUTPUT_PROD)
    {
        evd.Set40005() ; 
        if (CMS_SendEventToQ(qhandle, evd))
            retcode |= 0x0004 ; 
    }

    if (evd.eventMode & EventData::EVD_OUTPUT_DOWN)
    {
        evd.Set10100() ; 
        if (CMS_SendEventToQ(qhandle, evd))
            retcode |= 0x0008 ; 
    }

    return retcode ; 
}


