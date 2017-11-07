// cs_filelog.h

#ifndef __CS_FILELOG_H__
#define __CS_FILELOG_H__


#ifdef WIN32
#if _MSC_VER < 1201
#define INVALID_FILE_ATTRIBUTES 0xffffffff
#endif 
#endif


//! Output to log file if the file is open
/*!
    \param fp open file pointer
    \param formatstr standard printf style format string
    \param ... arguments to the printf function 
    \return 0=OK, -1=file not open, -2=printf fault
 */
int LogToFile(FILE *fp, const char *formatstr, ...) ;


//! Output to log file if the file is open
/*!
    \param fp open file pointer
    \param fp2 secondary log file
    \param formatstr standard printf style format string
    \param ... arguments to the printf function 
    \return 0=OK, -1=file not open, -2=printf fault

    If fp is null then nothing happens. If fp is open to a valid file then 
    data is logged to fp, and only if fp2 is valid is data logged to fp2. 
    By setting fp2=stdout it is possible to log the same data to the console
    as well as the log file, thus the two can be a mirror image of one
    another. 
 */
int LogToFile2(FILE *fp, FILE *fp2, const char *formatstr, ...) ; 


/*!
    Handles basic logging output to a file. 

    The log file is initially defined by a fulll pathname and extension
    which is then parsed and saved in component parts. If the SUBDIR_...
    mode options are used, then the final destination directory will
    have that particular date or time pattern inserted just before the 
    final log file name as a sub directory. The base sub-directory
    must already exist when the function starts. 



    TODO - add message Q handling for multi-threaded apps so that they
    can pump messages to a common log efficiently. 


 */
class CS_FileLog
{
public:
    
    //! The current open log file to write to. 
    FILE *fp ; 
    
    //! This is the base directory and file name to output to
    csString csBasePathName ; 
    
    //! These are extracted from the BasePathName
    csString csBasePath ; //! The output directory only, no trailing slash
    csString csBaseName ; //! the output file name only
    csString csBaseExt ; //! output file name extension

    //! The actual file name being output to.
    csString csCurFileName ;

    time_t lastLog ; // last log event time
    int lastSec ; 
    int lastMin ; 
    int lastHour ; 
    int lastDay ; 
    int lastMonth ; 
    int lastYear ; 

    /*!
        For the SUBDIR_... settings each are mutually exclusive. The priority
        in which they are used is hourly, daily, monthly, yearly. Thus for 
        example if SUBDIR_DAILY and SUBDIR_MONTHLY are both defined then the 
        SUBDIR_MONTHLY setting has no real effect. 

     */
    enum {
        ROLLOVER_HOURLY     = 0x0001,
        ROLLOVER_DAILY      = 0x0002,
        ROLLOVER_MONTHLY    = 0x0004,
        SUBDIR_HOURLY       = 0x0010,   // creates YYYYMMDDHH sub dir names
        SUBDIR_DAILY        = 0x0020,   // creates YYYYMMDD sub dir names
        SUBDIR_MONTHLY      = 0x0040,   // creates YYYYMM sub dir name
        SUBDIR_YEARLY       = 0x0080,   // creates YYYY sub dir name
        APPEND_DATE         = 0x0100,   // implied with rollover daily
        APPEND_TIME         = 0x0200    // implied with rollover hourly
    } ; 
    int mode ; //! operation definition based on above enum
    //! default is 0 (zero)

    enum {
        HOUR_CHANGED        = 0x0001,
        DAY_CHANGED         = 0x0002,
        MONTH_CHANGED       = 0x0004,
        YEAR_CHANGED        = 0x0008,
        NAME_CHANGED        = 0x0010 
    } ; 


    // =============================================================
    //                  MEMBER FUNCTIONS
    // =============================================================

    CS_FileLog() ; 
    CS_FileLog(char *filename) ; 
    ~CS_FileLog() ; 

    void clear() ; // resets all the member variables

    int SetPathName(char *pathname) ; 
    int Write(const char *formatstr, ...) ;
    
    //! Create the new current log file name
    /*!
        \param newfilename output buffer for the current new filename
        \return true if there was a name rollover, else false. 
     */
    int CurrentFileName() ;

    void RolloverHourly() { mode |= ROLLOVER_HOURLY; } ;
    void RolloverDaily() { mode |= ROLLOVER_DAILY; } ;
    void RolloverMonthly() { mode |= ROLLOVER_MONTHLY; } ;
    void SubDirHourly() { mode |= SUBDIR_HOURLY; } ;
    void SubDirDaily() { mode |= SUBDIR_DAILY; } ;
    void SubDirMonthly() { mode |= SUBDIR_MONTHLY; } ;
    void AppendDateTime() { mode |= APPEND_DATE | APPEND_TIME ; } ; 

    //! set mode to append date/time to filename, create monthly subdirs and rollover daily
    void StdModeSubMonthDaily() 
    { 
        AppendDateTime() ; 
        RolloverDaily() ; 
        SubDirMonthly() ; 
    }

} ; 

#endif 