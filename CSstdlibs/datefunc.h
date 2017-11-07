/***************************************************************************
    Copyright (C) 1981-2009 Cadamation Systems Inc., Ontario, Canada 
            All Rights Reserved Worldwide

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
    SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
    FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*****************************************************************************/

// datefunc.h - date functions header file 

#ifndef __DATEFUNC_H__
#define __DATEFUNC_H__

#ifdef WIN32
#pragma warning( disable : 4996 )
#endif

#include <time.h>
#include <stdio.h>

#include "csstring.h"

extern char *CS_DAYSTRSHORT[] ; 
extern char *CS_MONTHSTRSHORT[] ; 

class CDate {

 public:
    int m_nYear ;   // actual year 1995 for example
    int m_nMonth ;  // 1=Jan, 2=Feb, ...
    int m_nDay ;    // 1,2,..., {28,29,30,31}

    CDate() ;
    CDate(int year, int month, int day) ; 
    CDate(time_t t) ; 

    void SetDate(const char *datestr) ; // must be in format YYYYMMDD

    //! Set date based on the pattern definition using YYYY MM DD
    /*!
        \param datestr input date string definition
        \param pattern YYYYMMDD, MMDDYY etc... defining the datestr pattern
        \param yearbase default number added to 2 digit years
        \param yearsplit if 2 digit year and value is > yearsplit then add yearbase - 100
        \return 0=ok, else error or warning code. 
     */
    int SetDate(const char *datestr, const char *pattern, int yearbase=2000, int yearsplit=80) ;

    void SetDate(time_t *ptm=NULL) ; // NULL=set to today

    void SetDate(time_t t) ;

    void SetDateNDays(int days) ;

    void SetDate(int year, int month, int day) ;

    void SetNow() ;

    //! Convert the date to string in format YYYYMMDD
    /*!
        \param formatstr if not NULL then used to define output
        \return the string definition of the year. 

        The format string can be made up of 
     */
    csString ToString(const char *formatstr=0) ;

    //! returns true if the year is a leap year. 
    int IsLeapYear() ; 

    int DayofWeek() ;  // 0=mon, 1=tue, ..., 5=sat, 6=sun
    
    //! JulianDay stuff doesn't work right
    int JulianDay() ;  
    int JulianDayOfWeekIndex (int jd0) ;
    CDate &SetDateToJulianDay(int julianDay) ;

    // This is from Wikipedia and is tested. 
    int JulianDayWiki() ;
    int DayOfYear() ; 

    //! Add the specified number of days to the date
    /*!
        \param ndays number of days to add to the date
        
        If the ndays parameter is negative then it goes backward in time that 
        many days. If the ndays value is > 0 then it moves forward by that 
        many days. It does this simply by stepping through each month counting
        days until the correct month is found and then sets the date. Thus the
        larger ndays is the longer it takes to perform this operation. Or in 
        other words it runs in O(ndays/30.4) time. 
     */
    void AddDays(int ndays) ; 

    int DaysinMonth() ;
    int LeapYear() ;

    char *MonthStringLong(int idx=-1) ;
    char *MonthStringShort(int idx=-1) ;
    char *DayStringLong(int idx=-1) ;
    char *DayStringShort(int idx=-1) ;

    // return TimeT value for date, note the default of 12 noon
    time_t GetTimeT(int hour=12, int min=0, int sec=0) ;

    void NextDay() ;   // increment date to next day
    void NextWorkDay() ;   // increment date to next work day
    void PrevDay() ;   // decrement date to the previous day
    void PrevWorkDay() ;   // decrement date to the previous work day
    // returns the working date index from start of current quarter
    int Quarter() ;  // indexed from 0-3
    int QuarterIndex() ; 
    bool operator< (const CDate&) ;
    bool operator> (const CDate&) ;
    bool operator<= (const CDate&) ;
    bool operator>= (const CDate&) ;
    bool operator== (const CDate&) ;
    bool operator!= (const CDate&) ;

    //! Sets the date to Easter Sunday for the specified year.
    /*!
        \param year the year to calculate Easter Sunday on
        return reference to this object

        If the year is not specified, then the date is changed to Easter 
        for the currently defined year. This will return a valid result for 
        years from 1583 to 4099

     */
    CDate &EasterSunday(int year=0) ; 

} ;

class CDateTime {

 public:
    short m_nYear ;   // actual year 1995 for example
    short m_nMonth ;  // 1=Jan, 2=Feb, ...
    short m_nDay ;    // 1,2,..., {28,29,30,31}
    short m_nHours ; 
    short m_nMins ;
    short m_nSecs ; 
    // time_t tt ; TODO - add this and maintain it on the fly. 

    CDateTime() ;
    CDateTime(short year, short month, short day, 
              short hours, short minutes, short secs) ; 
    CDateTime(time_t t) ; 

    void clear()
    {
        m_nYear = m_nMonth  = m_nDay = m_nHours = m_nMins = m_nSecs = 0 ;
    }

    void SetDateTime(const char *datestr) ; // must be in format YYYYMMDDHHMMSS
    void SetDateTime(time_t *ptm=NULL) ; // NULL=set to today
    void SetDateTime(short year, short month, short day, 
                     short hours=12, short minutes=0, short seconds=0) ;
    void SetDateTime(struct tm *ptm) ; 
    void SetNow() ;
    void SetNow(time_t &timetosetto) ; 
    void SetTime(const time_t &t) ;
    void SetDate(int y, int m, int d) { m_nYear = y; m_nMonth = m;  m_nDay = d ; }
    void SetTime(int h, int m, int s) { m_nHours = h; m_nMins = m;  m_nSecs = s ; }

    bool operator< (const CDateTime&) ;
    bool operator> (const CDateTime&) ;
    bool operator<= (const CDateTime&) ;
    bool operator>= (const CDateTime&) ;
    bool operator== (const CDateTime&) ;
    bool operator!= (const CDateTime&) ;

    // The difference in seconds between the two times. 
    int  operator-(const CDateTime&) ;
    friend int operator-(const CDateTime &dta, const CDateTime &dtb) ; 

    // return TimeT value for date, note the default of 12 noon
    time_t GetTimeT() const ;

    // Fills the datetime variable based on current dt member variables. 
    // It calls mktime and then localtime so that the wday should be valid on return.
    void GetStructTM(struct tm &datetime) ;

    // Output the time int he following formatted string for 
    //  HTTP Expires: header definitions
    //     "Thu, 01 Dec 1994 16:00:00 GMT"
    // returns pointer to the null character at the end of the string
    char *FormatExpires(char *pdst) ; 

    // Set date in YYYY-MM-DD format
    char *FormatDate(char *dst) ; 
    char *FormatDate(char *dst, char sepchar) ;

    // Allows custom formatting modes. 
    char *FormatDate(char *dst, int mode) ; 

    
    // Set date in YYYY-MM-DD HH:MM format
    char *FormatDateTime(char *dst) ; 

    //! Set date in YYYY-MM-DD HH:MM:SS format (default)
    /*!
        \param dst the output string, must be pre-allocated with sufficient space
        \param mode 0=default 
        \return the dst pointer

        Modes: 
            0 = YYYY-MM-DD HH:MM:SS
            1 = YYYYMMDD_HHMMSS
            2 = YYYYMMDDHHMMSS
     */
    char *FormatDateTimeSecs(char *dst, int mode=0) ; 

    //     mode = 0      Mmm D, YYYY, H:MM{AM|PM} extstring
    char *FormatDateTime(char *dst, char *ext, int mode, int *len=0) ;

    // Returns this->time_t - t 
    time_t DeltaSecs(time_t t) ;

    //! returns true if the year is a leap year. 
    int IsLeapYear() ; 

    //! References the m_nYear member variable only. 
    int DaysinMonth(int m) ;

    //! Returns the number of seconds into the day
    /*!
        \return returns 3600*hours + 60*minutes + seconds
     */ 
    int DaySeconds() ; 
} ;



#endif


