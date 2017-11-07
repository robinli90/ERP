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


// datefunc.cpp - date functions

// These date functions are accurate from Oct 15, 1582
// through to Feb 28, 4000
// #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>

#include "datefunc.h"


static int daysinmonthSTD[] = 
{
    31,    // 1
    28,    // 2
    31,    // 3
    30,    // 4
    31,    // 5
    30,    // 6
    31,    // 7
    31,    // 8
    30,    // 9
    31,    // 10
    30,    // 11
    31     // 12
} ; 

//////////////////////////////////////////////////////////////////////
// TO DO - add processing capability to allow for holiday skipping
//   since we don't want to include Christmas and New Years for 
//   example as work days
//////////////////////////////////////////////////////////////////////



CDate::CDate()
{
    // initialize date to Jan 1, 1996.
    m_nYear = 0 ;    
    m_nMonth = 0 ;
    m_nDay = 0 ;
}

CDate::CDate(int year, int month, int day) 
{
    m_nYear = year ;    
    m_nMonth = month ;
    m_nDay = day ;
}

CDate::CDate(time_t t) 
{
    SetDate(&t) ; 
}



// Expects a string in YYYYMMDD format 
//                     01234567 
void CDate::SetDate(const char *datestr)
{
    char wrkstr[17] ; 
    memset(wrkstr, 0, 16) ; 

    strncpy(wrkstr, datestr, 9) ; 
    wrkstr[8] = 0 ; 

    m_nDay = atoi(&wrkstr[6]) ; 
    wrkstr[6] = 0 ; 
    m_nMonth = atoi(&wrkstr[4]) ; 
    wrkstr[4] = 0 ; 
    m_nYear = atoi(wrkstr) ; 
}

int CDate::SetDate(const char *datestr, const char *pattern, int yearbase, int yearsplit)
{
    int retcode = 0 ; 
    char pat[256] ; 
    unsigned char *s = (unsigned char *)pattern ; 
    int i = 0 ; 

    while (s && *s)
        pat[i++] = (unsigned char)toupper(*s++) ; 
    pat[i] = 0 ; 

    int yidx = -1 ; 
    int midx = -1 ; 
    int didx = -1 ; 

    char ystr[8] ; 
    char mstr[8] ; 
    char dstr[8] ; 

    ystr[0] = 0 ; 
    mstr[0] = 0 ; 
    dstr[0] = 0 ; 

    i = 0 ; 
    int len = (int)strlen(pattern) ;
    while (i < len)
    {
        if (yidx == -1 && pat[i] == 'Y') 
            yidx = i ; 
        else if (midx == -1 && pat[i] == 'M') 
            midx = i ; 
        else if (didx == -1 && pat[i] == 'D') 
            didx = i ; 
        i++ ; 
    }

    // number of year month and day digitis
    int ny = 0 ; 
    int nm = 0 ; 
    int nd = 0 ; 

    m_nYear  = 0 ; 
    m_nMonth = 0 ; 
    m_nDay   = 0 ; 

    int n ; 

    if (yidx >= 0) 
    {
        i = yidx ;
        n = 0 ; 
        while (pat[i] == 'Y') 
        {
            ystr[n++] = datestr[i] ; 
            ystr[n] = 0 ; 
            i++ ; 
        }
        ny = i - yidx ; 
        
        m_nYear = atoi(ystr) ;
        if (ny < 4)
        {
            if (m_nYear < yearsplit)
                m_nYear += yearbase ; 
            else
                m_nYear += yearbase - 100 ; 
        }
    }

    if (midx >= 0) 
    {
        i = midx ;
        n = 0 ; 
        while (pat[i] == 'M') 
        {
            mstr[n++] = datestr[i] ; 
            mstr[n] = 0 ; 
            i++ ; 
        }
        nm = i - midx ; 

        m_nMonth = atoi(mstr) ; 
    }

    if (didx >= 0) 
    {
        i = didx ;
        n = 0 ; 
        while (pat[i] == 'D') 
        {
            dstr[n++] = datestr[i] ; 
            dstr[n] = 0 ; 
            i++ ; 
        }
        nd = i - didx ; 

        m_nDay = atoi(dstr) ; 
    }

    return retcode ; 
}



csString CDate::ToString(const char *pattern)
{
    char tmpstr[16] ; 
    csString resStr ; 
    
    if (pattern == 0)
    {
        sprintf(tmpstr, "%4d%02d%02d", m_nYear, m_nMonth, m_nDay) ; 
        resStr = tmpstr ; 
    }
    else
    {
        int i ; 
        char pat[256] ; 
        unsigned char *s = (unsigned char *)pattern ; 
        i = 0 ; 
        while (s && *s)
            pat[i++] = (unsigned char)toupper(*s++) ; 
        pat[i] = 0 ; 

        int yidx = -1 ; 
        int midx = -1 ; 
        int didx = -1 ; 

        i = 0 ; 
        int len = (int)strlen(pattern) ;
        while (i < len)
        {
            if (yidx == -1 && pat[i] == 'Y') 
                yidx = i ; 
            else if (midx == -1 && pat[i] == 'M') 
                midx = i ; 
            else if (didx == -1 && pat[i] == 'D') 
                didx = i ; 
            i++ ; 
        }

        // number of year month and day digitis
        int ny = 0 ; 
        int nm = 0 ; 
        int nd = 0 ; 

        if (yidx >= 0) 
        {
            i = yidx ;
            while (pat[i] == 'Y') i++ ; 
            ny = i - yidx ; 
        }

        if (midx >= 0) 
        {
            i = midx ;
            while (pat[i] == 'M') i++ ; 
            nm = i - midx ; 
        }

        if (didx >= 0) 
        {
            i = didx ;
            while (pat[i] == 'D') i++ ; 
            nd = i - didx ; 
        }

        // Now convert to output pattern
        char tmpstr[64] ; 
        char formatstr[64] ; 
        i = 0; 
        while (i < len)
        {
            if (i == yidx)
            {
                int year ; 
                if (ny == 4)
                {
                    strcpy(formatstr, "%4d") ; 
                    year = m_nYear ; 
                }
                else
                {   // must be less than 4 digits
                    sprintf(formatstr, "%%0%dd", ny) ; 
                    switch(ny)
                    {
                        case 3:
                            year = m_nYear % 10 ; 
                            break ; 
                        case 2:
                            year = m_nYear % 100 ; 
                            break ; 
                        case 1:
                            year = m_nYear % 1000 ; 
                            break ; 
                    }
                }

                sprintf(tmpstr, formatstr, year) ; 

                resStr += tmpstr ; 
                i += ny ; 
            }
            else if (i == midx) 
            {
                if (nm == 2)
                    sprintf(tmpstr, "%02d", m_nMonth) ; 
                else 
                    sprintf(tmpstr, "%d", m_nMonth) ; 

                resStr += tmpstr ; 
                i += nm ; 
            }
            else if (i == didx) 
            {
                if (nd == 2)
                    sprintf(tmpstr, "%02d", m_nDay) ; 
                else 
                    sprintf(tmpstr, "%d", m_nDay) ; 

                resStr += tmpstr ; 
                i += nd ; 
            }
            else
            {
                resStr += pat[i++] ; 
            }
        }
    }
    return resStr ; 
}

// if ptm=NULL then the date is set to now (current time)
void CDate::SetDate(time_t *ptm) 
{
    struct tm *pstm ; 
    time_t timetosetto ; 

    if (!ptm)
    {
        time(&timetosetto) ; 
    }
    else
    {
        timetosetto = *ptm ; 
    }
    pstm = localtime(&timetosetto) ; 
    m_nYear = pstm->tm_year + 1900 ;
    m_nMonth = pstm->tm_mon + 1 ;
    m_nDay = pstm->tm_mday ;
}

void CDate::SetDate(time_t t) 
{
    SetDate(&t) ; 
}

// Sets the date based on the days variable which is the number of days
// since Jan 1, 1970 (multiply by 86400 to get a time_t value)
void CDate::SetDateNDays(int days) 
{
    time_t t = days * 86400 ; 
    SetDate(&t) ; 
}


void CDate::SetNow()
{
    struct tm *pstm ; 
    time_t timetosetto ; 

    time(&timetosetto) ; 

    pstm = localtime(&timetosetto) ; 
    m_nYear = pstm->tm_year + 1900 ;
    m_nMonth = pstm->tm_mon + 1 ;
    m_nDay = pstm->tm_mday ;
}


void CDate::SetDate(int year, int month, int day) 
{
    m_nYear = year ; 
    m_nMonth = month ; 
    m_nDay = day ; 
}

time_t CDate::GetTimeT(int hour, int min, int secs)
{
    struct tm datetime ; 

    datetime.tm_sec = secs ; 
    datetime.tm_min = min ; 
    datetime.tm_hour = hour ; 
    datetime.tm_mday = m_nDay ; 
    datetime.tm_mon = m_nMonth - 1 ; 
    datetime.tm_year = m_nYear - 1900 ; 
    datetime.tm_wday = 0 ; 
    datetime.tm_yday = 0 ; 
    datetime.tm_isdst = -1 ; 

    return  mktime(&datetime);
}

void CDate::PrevDay()
{
    m_nDay -= 1 ;
    if (m_nDay <= 0)
    {
        m_nMonth -= 1 ;
        if (m_nMonth <= 0)
        {
            m_nMonth = 12 ; // set to december
            m_nYear -= 1 ; // rolled back to previous year
        } 
        m_nDay = DaysinMonth() ;
    }
}

void CDate::PrevWorkDay()
{
    do {
        m_nDay -= 1 ;
        if (m_nDay <= 0)
        {
            m_nMonth -= 1 ;
            if (m_nMonth <= 0)
            {
                m_nMonth = 12 ; // set to december
                m_nYear -= 1 ; // rolled back to previous year
            } 
            m_nDay = DaysinMonth() ;
        }
    } while (DayofWeek() > 4) ;
}



void CDate::NextDay()
{
    m_nDay += 1 ;
    if (m_nDay > DaysinMonth())
    {
        m_nMonth += 1 ;
        m_nDay = 1 ;
        if (m_nMonth > 12)
        {
            m_nMonth = 1 ; // set to december
            m_nYear += 1 ;
        }
    }
}

void CDate::NextWorkDay()
{
    do {
        m_nDay += 1 ;
        if (m_nDay > DaysinMonth())
        {
            m_nMonth += 1 ;
            m_nDay = 1 ;
            if (m_nMonth > 12)
            {
                m_nMonth = 1 ; // set to december
                m_nYear += 1 ;
            }
        }
    } while (DayofWeek() > 4) ; 
}



int CDate::LeapYear()
{
    if ((m_nYear % 100) == 0)
    {   // Then we are on a century year
        // Only centuries devivisble by 400 are leap years
        if ((m_nYear % 400) == 0)
            return 1 ;
        else
            return 0 ;
    }
    
    if ((m_nYear % 4) == 0) 
        return 1 ;
    else
        return 0 ;
}



int CDate::DaysinMonth()
{
    switch(m_nMonth)
    {
        case 1 : // Jan
            return 31 ;
        case 2 : // Feb
            if (LeapYear())
                return 29 ;
            else
                return 28 ;
        case 3 : // Mar
            return 31 ;
        case 4 :  // Apr
            return 30 ;
        case 5 :  // May
            return 31 ;
        case 6 :  // June
            return 30 ;
        case 7 :  // July
            return 31 ;
        case 8 :  // Aug
            return 31 ;
        case 9 : // Sept
            return 30 ;
        case 10 : // Oct
            return 31 ;
        case 11 : // Nov
            return 30 ;
        case 12 : // Dec
        default :
            return 31 ; // Dec or month was out of range
    }
}


// Returns the day of the week with mon=0, tues=1, ...
// Note that the standard calculation generates sunday = 0 
// but we subtract one from the result to shift things over
// Since we are only interested in trading days (0-4) this
// gives us the index we want.
int CDate::DayofWeek() 
{
    int w ; 
    
    /*

    // Method 1

    // Not sure of the validity range for this method
    struct tm *ptm ; 
    time_t tmt = GetTimeT(12,0,0) ; // get time for today
    ptm = localtime(&tmt) ; 
    w = ptm->tm_wday ; // 0=sun, 1=mon, ...
    */

    /*

    // Method 2
    // Valid from Oct 1582 to Year 32767

    int day = m_nDay ; 
    int month = m_nMonth ;
    int year = m_nYear ; 
    
    if (month > 2)
    {
        month -= 2;
    }
    else
    {
        month += 10;
        year--;
    }
    
    w = ((13 * month - 1) / 5) + day + (year % 100) 
        + ((year % 100) / 4) + ((year / 100) / 4) 
        - 2 * (year / 100) + 77;
    
    w = w - 7 * (w / 7);

    if (w == 7)
        w = 0;

    */


    // Method 3 good from Year -4712 to year 32767

    w = JulianDayOfWeekIndex(JulianDay()) ; 

    w -= 1 ;
    if (w < 0) 
        w = 6 ; // then it is sunday 
    
    return w ;
}

char *CDate::DayStringLong(int idx)
{
    if (idx < 0)
        idx = DayofWeek() ; 
    switch(idx)
    {
        case 0 :
            return "Monday" ;
        case 1 :
            return "Tuesday" ;
        case 2 :
            return "Wednesday" ;
        case 3 :
            return "Thursday" ;
        case 4 :
            return "Friday" ;
        case 5 :
            return "Saturday" ;
        case 6 :
            return "Sunday" ;
    }
    return "Bad_Day" ;
}


// These can be used to directly access strings from the 
// struct tm values returned by localtime() 
char *CS_DAYSTRSHORT[] = 
{
    "Sun", 
    "Mon", 
    "Tue", 
    "Wed",
    "Thu", 
    "Fri", 
    "Sat"
} ; 

char *CS_MONTHSTRSHORT[] = 
{
    "Jan", 
    "Feb", 
    "Mar", 
    "Apr",
    "May", 
    "Jun", 
    "Jul",
    "Aug",
    "Sep",
    "Oct",
    "Nov",
    "Dec"
} ; 
      

char *CDate::DayStringShort(int idx)
{
    if (idx < 0)
        idx = DayofWeek() ; 
    switch(idx)
    {
        case 0 :
            return "Mon" ;
        case 1 :
            return "Tue" ;
        case 2 :
            return "Wed" ;
        case 3 :
            return "Thu" ;
        case 4 :
            return "Fri" ;
        case 5 :
            return "Sat" ;
        case 6 :
            return "Sun" ;
    }
    return "Bad_Day" ;
}


// This equation is off of wikipedia
int CDate::JulianDayWiki()
{
    int Y = m_nYear ; 
    int M = m_nMonth ; 
    int D = m_nDay ; 
    return (1461 * (Y + 4800 + (M - 14) / 12)) / 4 
              + (367 * (M - 2 - 12 * ((M - 14) / 12))) / 12 
              - (3 * ((Y + 4900 + (M - 14)/12)/100)) / 4 + D - 32075 ;
}

int CDate::DayOfYear()
{
    CDate dsoy(m_nYear, 1, 1) ; 
    int soy = dsoy.JulianDayWiki() ; 
    int jd = JulianDayWiki() ; 
    return jd - soy + 1 ; 
}


int CDate::IsLeapYear()
{
    if (m_nYear % 4 == 0)
    {   // Then this might be a leap year
        if (m_nYear % 400 == 0)
            return 1 ; 

        if (m_nYear % 100 == 0)
            return 0 ; 

        return 1 ; 
    }
    return 0 ; 
}

/*
    Yet another code sample on how to go from YMD to a Julian Date
    note sure where this came from, is GNU licensed though. 

    long jul_day; 
    int a,b; 
    int year = iYear, month = iMonth, day = iDay;
    float year_corr;
    if ( year < 0 ) 
        year++;
    year_corr = ( year > 0 ? 0.0 : 0.75 );
    if ( month <= 2 ) 
    { 
        year--; 
        month += 12; 
    }
    b = 0;
    if ( year * 10000.0 + month * 100.0 + day >= 15821015.0 ) 
    { 
        a = year / 100;
        b = 2 - a + a / 4;
    } 
    jul_day = (long)( 365.25 * year - year_corr ) 
            + (long)( 30.6001 * ( month + 1 ) ) + day + 1720995L + b ;

*/


/*
Returns the Julian Day number (JD#) for a given date in the Western
   (Julian and Gregorian) calendar, given as day, month and year. Returns 
   valid numbers for dates in both the Julian and Gregorian calendars.
   
   Valid inputs are:
   
   1. Julian calendar    : from 01 JAN -4712 to 04 OCT  1582.
   2. Gregorian calendar : from 15 OCT  1582 to 31 DEC 32767.
*/
int CDate::JulianDay()
{
    double jd, x, d1, m1, y1;
    int d2, m2, y2;
    
    d2 = m_nDay ;
    m2 = m_nMonth ;
    y2 = m_nYear ;
    
    if (y2 == 1582)
    {
        if (m2 == 10)
        {
            if (d2 > 4 && d2 < 15)
                d2 = 15;
        }
    }
    
    d1 = (double) d2;
    m1 = (double) m2;
    y1 = (double) y2;
    
    x = 12 * (y1 + 4800) + m1 - 3;
    jd = (2 * (x - floor (x / 12) * 12) + 7 + (365 * x)) / 12;
    jd = floor (jd) + d1 + floor (x / 48) - 32083;
    
    if (jd > 2299170)
        jd = jd + floor (x / 4800) - floor (x / 1200) + 38;
    
    // double whole, fract ; 
    // fract = modf(jd, &whole) ; 

    int julday = (int)jd ; 

    // if (fract < -0.5)
    // {
    //     // printf("-ve fractional part = %f\n", fract) ; 
    //     julday -= 1 ; 
    // }
    // else if(fract > 0.5)
    // {
    //     // printf("+ve fractional part = %f\n", fract) ; 
    //     julday += 1 ; 
    // }

    return (julday); // fmod
}




// returns reference to this date. Sets the date based on the 
// Julian day passed in. 
CDate &CDate::SetDateToJulianDay(int julianDay)
{
   double q, n, x;
   double d, m, y;

   q = floor (julianDay + 0.5) + 68569.0;
   n = floor (4 * q / 146097.0);
   q -= floor ((146097.0 * n + 3) / 4);
   x = floor (4000 * (q + 1) / 1461001.0);
   q -= floor (1461 * x / 4) + 31;
   m = floor (80 * q / 2447);
   d = q - floor (2447 * m / 80);
   q = floor (m / 11);
   m += 2 - 12 * q;
   y = 100 * (n - 49) + x + q;

   m_nYear = (int) y;
   m_nMonth = (int) m;
   m_nDay = (int) d;

   return *this ;
}


// Returns the day of the week given the julian day
// 0=Sunday
/*!
 */
int CDate::JulianDayOfWeekIndex (int jd0)
{
   int j;
   int index; 
   
   j = jd0 ;
   index = (int) ((j % 7) + 1);
   
   if (index == 7)
      index = 0;
   
   return index;
}

void CDate::AddDays(int ndays) 
{
    int dim ; 
    if (ndays < 0)
    {
        ndays = -ndays ; // make positive
        while (ndays > 0)
        {
            dim = DaysinMonth() ; 
            if (m_nDay > ndays)
            {
                m_nDay -= ndays ;
                    return ; 
            }

            if (m_nMonth == 1)
            {
                m_nYear -= 1 ;
                m_nMonth = 12 ; 
            }
            else
            {
                m_nMonth -= 1 ; 
            }

            ndays -= m_nDay ; 
            m_nDay = DaysinMonth() ; 
        }
    }
    else if (ndays > 0)
    {
        while (ndays > 0)
        {
            dim = DaysinMonth() ; 
            if (dim - m_nDay <= ndays)
            {
                m_nDay += ndays ;
                return ; 
            }

            if (m_nMonth == 12)
            {
                m_nYear += 1 ;
                m_nMonth  = 1 ; 
            }
            else
            {
                m_nMonth += 1 ; 
            }

            ndays -= (dim - m_nDay) + 1 ; 
            m_nDay = 1 ; 
        }
    }
}

int CDate::QuarterIndex() 
{
    int quarter = Quarter() ;
    // month that starts the quarter                                    
    CDate wd ; // work date
    
    wd.m_nMonth = quarter * 3 + 1 ;
    wd.m_nYear = m_nYear ;
    wd.m_nDay = 1 ; 
    
    int idx = 0 ;        
    // loop while we haven't reached the current date
    while (wd < *this) 
    {
        if (wd.DayofWeek() < 5)
            idx += 1 ; // increment since it's a workday
        wd.NextDay() ; // increment to the next day
    }
    return idx ;
}

// returns quarter for the current date
int CDate::Quarter() 
{
    int quarter ;
  
    if (m_nMonth >= 1 && m_nMonth <= 3)
        quarter = 0 ;     
    else if (m_nMonth >= 4 && m_nMonth <= 6)
        quarter = 1 ;     
    else if (m_nMonth >= 7 && m_nMonth <= 9)
        quarter = 2 ;     
    else 
        quarter = 3 ;     

    return quarter ;
}


bool CDate::operator< (const CDate& d2)
{
    if (m_nYear < d2.m_nYear)
        return 1 ;
    if (m_nYear > d2.m_nYear)
        return 0 ;

    // else Years must be equal 
    if (m_nMonth < d2.m_nMonth)
        return 1 ;
    if (m_nMonth > d2.m_nMonth)
        return 0 ;

    // else months must be equal
    if (m_nDay < d2.m_nDay)
        return 1 ;
    return 0 ; // else > or ==
}

bool CDate::operator<= (const CDate& d2)
{
    if (m_nYear < d2.m_nYear)
        return 1 ;
    if (m_nYear > d2.m_nYear)
        return 0 ;

    // else Years must be equal 
    if (m_nMonth < d2.m_nMonth)
        return 1 ;
    if (m_nMonth > d2.m_nMonth)
        return 0 ;

    // else months must be equal
    if (m_nDay < d2.m_nDay)
        return 1 ;
    if (m_nDay > d2.m_nDay)
        return 0 ; // else > or ==
    return 1 ; // dates were equal
}

bool CDate::operator> (const CDate& d2)
{
    if (m_nYear > d2.m_nYear)
        return 1 ;
    if (m_nYear < d2.m_nYear)
        return 0 ;

    // else Years must be equal 
    if (m_nMonth > d2.m_nMonth)
        return 1 ;
    if (m_nMonth < d2.m_nMonth)
        return 0 ;

    // else months must be equal
    if (m_nDay > d2.m_nDay)
        return 1 ;
    return 0 ; // else > or ==
}

bool CDate::operator>= (const CDate& d2)
{
    if (m_nYear > d2.m_nYear)
        return 1 ;
    if (m_nYear < d2.m_nYear)
        return 0 ;

    // else Years must be equal 
    if (m_nMonth > d2.m_nMonth)
        return 1 ;
    if (m_nMonth < d2.m_nMonth)
        return 0 ;

    // else months must be equal
    if (m_nDay > d2.m_nDay)
        return 1 ;
    if (m_nDay < d2.m_nDay)
        return 0 ; // else > or ==
    return 1 ; // dates were equal
}


bool CDate::operator== (const CDate& d2)
{
    if ((m_nYear == d2.m_nYear) &&
        (m_nMonth == d2.m_nMonth) &&
        (m_nDay == d2.m_nDay))
        return 1 ;
    return 0 ;
}

bool CDate::operator!= (const CDate& d2)
{
    if ((m_nYear != d2.m_nYear) ||
        (m_nMonth != d2.m_nMonth) ||
        (m_nDay != d2.m_nDay))
        return 1 ;
    return 0 ;
}

char *CDate::MonthStringLong(int idx)
{
    if (idx < 0)
        idx = m_nMonth ; 
    switch(idx)
    { 
    case 1 :
        return "January" ; 
    case 2 :
        return "February" ; 
    case 3 :
        return "March" ; 
    case 4 :
        return "April" ; 
    case 5 :
        return "May" ; 
    case 6 :
        return "June" ; 
    case 7 :
        return "July" ; 
    case 8 :
        return "August" ; 
    case 9 :
        return "September" ; 
    case 10 :
        return "October" ; 
    case 11 :
        return "November" ; 
    case 12 :
        return "Decmeber" ; 
    }
    return "BadMonth" ; 
}

char *CDate::MonthStringShort(int idx)
{
    if (idx < 0)
        idx = m_nMonth ; 
    switch(idx)
    {
    case 1 :
        return "Jan" ; 
    case 2 :
        return "Feb" ; 
    case 3 :
        return "Mar" ; 
    case 4 :
        return "Apr" ; 
    case 5 :
        return "May" ; 
    case 6 :
        return "Jun" ; 
    case 7 :
        return "Jul" ; 
    case 8 :
        return "Aug" ; 
    case 9 :
        return "Sep" ; 
    case 10 :
        return "Oct" ; 
    case 11 :
        return "Nov" ; 
    case 12 :
        return "Dec" ; 
    }
    return "Err" ; 
}

CDate &CDate::EasterSunday(int y) 
{
    /* ========================================================

     From:  http://www.assa.org.au/edm.html#List20

     EASTER DATE CALCULATION FOR YEARS 1583 TO 4099

     y is a 4 digit year 1583 to 4099
     d returns the day of the month of Easter
     m returns the month of Easter

     Easter Sunday is the Sunday following the Paschal Full Moon
     (PFM) date for the year

     This algorithm is an arithmetic interpretation of the 3 step
     Easter Dating Method developed by Ron Mallen 1985, as a vast
     improvement on the method described in the Common Prayer Book

     Because this algorithm is a direct translation of the
     official tables, it can be easily proved to be 100% correct

     This algorithm derives values by sequential inter-dependent
     calculations, so ... DO NOT MODIFY THE ORDER OF CALCULATIONS!

     The \ operator may be unfamiliar - it means integer division
     for example, 30 \ 7 = 4 (the remainder is ignored)

     All variables are integer data types

     It's free!  Please do not modify code or comments!
     ========================================================== */

    if (y == 0)
        y = m_nYear ; 

    int FirstDig, Remain19, temp    ; // intermediate results
    int tA, tB, tC, tD, tE          ; // table A to E results

    double dtmp, dint ; 
    dtmp = y / 100.0 ; 
    modf(dtmp, &dint) ; 
    FirstDig = (int)dint ; 
    Remain19 = y % 19 ;          // remainder of year / 19

    // calculate PFM date
    temp = ((FirstDig - 15) >> 1) + 202 - 11 * Remain19 ; 
        
    switch(FirstDig)
    {
        case 21 : 
        case 24 :
        case 25 :
        case 27 :
        case 32 :
        case 34 :
        case 35 :
        case 38 :
            temp = temp - 1 ;
            break ; 
        case 33 :
        case 36 :
        case 37 :
        case 39 :
        case 40 :
            temp = temp - 2 ;
            break ; 
        default: 
            break ; 
    }
    
    temp = temp % 30 ;

    tA = temp + 21 ; 
    if (temp == 29)
        tA = tA - 1 ;

    if (temp == 28 && Remain19 > 10)
        tA = tA - 1 ; 

    // find the next Sunday
    tB = (tA - 19) % 7 ; 
        
    tC = (40 - FirstDig) % 4 ; 
    if (tC == 3)
        tC = tC + 1 ;
    if (tC > 1)
        tC = tC + 1 ;
            
    temp = y % 100 ;
    tD = (temp + (temp >> 2)) % 7 ;
        
    tE = ((20 - tB - tC - tD) % 7) + 1 ;
    
    int d = tA + tE ;
    int m = 0 ; 

    // return the date
    if (d > 31)
    {
        d = d - 31 ;
        m = 4 ;
    }
    else
    {
        m = 3 ;
    }

    m_nDay = d ; 
    m_nMonth = m ; 

    return *this ; 
}



///////////////////////////////////////////////////////////////
// Simliar to the CDate class except that we include the time 
// as well

CDateTime::CDateTime()
{
    // initialize date to Jan 1, 1996.
    m_nYear = 0 ;    
    m_nMonth = 0 ;
    m_nDay = 0 ;
    m_nHours = 0 ; 
    m_nMins = 0 ; 
    m_nSecs = 0 ; 
}

CDateTime::CDateTime(short year, short month, short day,
                     short hour, short mins, short secs) 
{
    m_nYear = year ;    
    m_nMonth = month ;
    m_nDay = day ;
    m_nHours = hour ; 
    m_nMins = mins ; 
    m_nSecs = secs ; 
}

CDateTime::CDateTime(time_t t) 
{
    SetDateTime(&t) ; 
}



// Expects a string in YYYYMMDDHHMMSS format 
//                     01234567890123
void CDateTime::SetDateTime(const char *datestr)
{
    char wrkstr[17] ; 
    memset(wrkstr, 0, 16) ; 

    strncpy(wrkstr, datestr, 15) ; 
    wrkstr[14] = 0 ; 

    m_nSecs = atoi(&wrkstr[12]) ;
    wrkstr[12] = 0 ;
    m_nMins = atoi(&wrkstr[10]) ; 
    wrkstr[10] = 0 ; 
    m_nHours = atoi(&wrkstr[8]) ; 
    wrkstr[8] = 0 ; 
    m_nDay = atoi(&wrkstr[6]) ; 
    wrkstr[6] = 0 ; 
    m_nMonth = atoi(&wrkstr[4]) ; 
    wrkstr[4] = 0 ; 
    m_nYear = atoi(wrkstr) ; 
}

// if ptm=NULL then the date is set to now (current time)
void CDateTime::SetDateTime(time_t *ptm) 
{
    struct tm *pstm ; 
    time_t timetosetto ; 

    if (!ptm)
    {
        time(&timetosetto) ; 
    }
    else
    {
        timetosetto = *ptm ; 
    }
    pstm = localtime(&timetosetto) ; 
    m_nYear = pstm->tm_year + 1900 ;
    m_nMonth = pstm->tm_mon + 1 ;
    m_nDay = pstm->tm_mday ;
    m_nHours = pstm->tm_hour ; 
    m_nMins = pstm->tm_min ; 
    m_nSecs = pstm->tm_sec ; 
}

void CDateTime::SetDateTime(struct tm *ptm)
{
    m_nYear = ptm->tm_year + 1900 ;
    m_nMonth = ptm->tm_mon + 1 ;
    m_nDay = ptm->tm_mday ;
    m_nHours = ptm->tm_hour ; 
    m_nMins = ptm->tm_min ; 
    m_nSecs = ptm->tm_sec ; 
}


void CDateTime::SetNow()
{
    struct tm *pstm ; 
    time_t timetosetto ; 
    time(&timetosetto) ; 

    pstm = localtime(&timetosetto) ; 
    m_nYear = pstm->tm_year + 1900 ;
    m_nMonth = pstm->tm_mon + 1 ;
    m_nDay = pstm->tm_mday ;
    m_nHours = pstm->tm_hour ; 
    m_nMins = pstm->tm_min ; 
    m_nSecs = pstm->tm_sec ; 
}

void CDateTime::SetNow(time_t &timetosetto)
{
    struct tm *pstm ; 
    time(&timetosetto) ; 

    pstm = localtime(&timetosetto) ; 
    m_nYear = pstm->tm_year + 1900 ;
    m_nMonth = pstm->tm_mon + 1 ;
    m_nDay = pstm->tm_mday ;
    m_nHours = pstm->tm_hour ; 
    m_nMins = pstm->tm_min ; 
    m_nSecs = pstm->tm_sec ; 
}


void CDateTime::SetTime(const time_t &timetosetto)
{
    struct tm *pstm ; 
    pstm = localtime(&timetosetto) ; 
    m_nYear = pstm->tm_year + 1900 ;
    m_nMonth = pstm->tm_mon + 1 ;
    m_nDay = pstm->tm_mday ;
    m_nHours = pstm->tm_hour ; 
    m_nMins = pstm->tm_min ; 
    m_nSecs = pstm->tm_sec ; 
}

time_t CDateTime::GetTimeT() const
{
    struct tm datetime ; 

    datetime.tm_sec = m_nSecs ; 
    datetime.tm_min = m_nMins ; 
    datetime.tm_hour = m_nHours ; 
    datetime.tm_mday = m_nDay ; 
    datetime.tm_mon = m_nMonth - 1 ; 
    datetime.tm_year = m_nYear - 1900 ; 
    datetime.tm_wday = 0 ; 
    datetime.tm_yday = 0 ; 
    datetime.tm_isdst = -1 ; 

    return  mktime(&datetime);
}

void CDateTime::GetStructTM(struct tm &datetime)
{
    datetime.tm_sec = m_nSecs ; 
    datetime.tm_min = m_nMins ; 
    datetime.tm_hour = m_nHours ; 
    datetime.tm_mday = m_nDay ; 
    datetime.tm_mon = m_nMonth - 1 ; 
    datetime.tm_year = m_nYear - 1900 ; 
    datetime.tm_wday = 0 ; 
    datetime.tm_yday = 0 ; 
    datetime.tm_isdst = -1 ; 

    time_t tt = mktime(&datetime) ;
    struct tm *pstm = localtime(&tt) ; 
	if (!pstm)
        memset(&datetime, 0, sizeof(datetime)) ; 
    else
	    datetime = *pstm ; 
}


bool CDateTime::operator< (const CDateTime& d2)
{
    if (m_nYear < d2.m_nYear)
        return 1 ;
    if (m_nYear > d2.m_nYear)
        return 0 ;

    // else Years must be equal 
    if (m_nMonth < d2.m_nMonth)
        return 1 ;
    if (m_nMonth > d2.m_nMonth)
        return 0 ;

    // else months must be equal
    if (m_nDay < d2.m_nDay)
        return 1 ;
    if (m_nDay > d2.m_nDay)
        return 0 ;

    // else days are equal, check hours
    if (m_nHours < d2.m_nHours)
        return 1 ;
    if (m_nHours > d2.m_nHours)
        return 0 ;

    // else hours are equal, check minutes
    if (m_nMins < d2.m_nMins)
        return 1 ;
    if (m_nMins > d2.m_nMins)
        return 0 ;

    // else minutes are equal, check seconds
    if (m_nSecs < d2.m_nSecs)
        return 1 ;
    return 0 ; // else > or ==
}

bool CDateTime::operator<= (const CDateTime& d2)
{
    if (m_nYear < d2.m_nYear)
        return 1 ;
    if (m_nYear > d2.m_nYear)
        return 0 ;

    // else Years must be equal 
    if (m_nMonth < d2.m_nMonth)
        return 1 ;
    if (m_nMonth > d2.m_nMonth)
        return 0 ;

    // else months must be equal
    if (m_nDay < d2.m_nDay)
        return 1 ;
    if (m_nDay > d2.m_nDay)
        return 0 ; // else > or ==

    // else days are equal, check hours
    if (m_nHours < d2.m_nHours)
        return 1 ;
    if (m_nHours > d2.m_nHours)
        return 0 ;

    // else hours are equal, check minutes
    if (m_nMins < d2.m_nMins)
        return 1 ;
    if (m_nMins > d2.m_nMins)
        return 0 ;

    // else minutes are equal, check seconds
    if (m_nSecs < d2.m_nSecs)
        return 1 ;
    if (m_nSecs > d2.m_nSecs)
        return 0 ;
    return 1 ; // they are equal 
}

bool CDateTime::operator> (const CDateTime& d2)
{
    if (m_nYear > d2.m_nYear)
        return 1 ;
    if (m_nYear < d2.m_nYear)
        return 0 ;

    // else Years must be equal 
    if (m_nMonth > d2.m_nMonth)
        return 1 ;
    if (m_nMonth < d2.m_nMonth)
        return 0 ;

    // else months must be equal
    if (m_nDay > d2.m_nDay)
        return 1 ;
    if (m_nDay < d2.m_nDay)
        return 0 ;

    // else days are equal, check hours
    if (m_nHours > d2.m_nHours)
        return 1 ;
    if (m_nHours < d2.m_nHours)
        return 0 ;

    // else hours are equal, check minutes
    if (m_nMins > d2.m_nMins)
        return 1 ;
    if (m_nMins < d2.m_nMins)
        return 0 ;

    // else minutes are equal, check seconds
    if (m_nSecs > d2.m_nSecs)
        return 1 ;
    return 0 ; // must be < or == 
}

bool CDateTime::operator>= (const CDateTime& d2)
{
    if (m_nYear > d2.m_nYear)
        return 1 ;
    if (m_nYear < d2.m_nYear)
        return 0 ;

    // else Years must be equal 
    if (m_nMonth > d2.m_nMonth)
        return 1 ;
    if (m_nMonth < d2.m_nMonth)
        return 0 ;

    // else months must be equal
    if (m_nDay > d2.m_nDay)
        return 1 ;
    if (m_nDay < d2.m_nDay)
        return 0 ; // else > or ==

    // else days are equal, check hours
    if (m_nHours > d2.m_nHours)
        return 1 ;
    if (m_nHours < d2.m_nHours)
        return 0 ;

    // else hours are equal, check minutes
    if (m_nMins > d2.m_nMins)
        return 1 ;
    if (m_nMins < d2.m_nMins)
        return 0 ;

    // else minutes are equal, check seconds
    if (m_nSecs > d2.m_nSecs)
        return 1 ;
    if (m_nSecs < d2.m_nSecs)
        return 0 ;
    return 1 ; // they were equal
}


bool CDateTime::operator== (const CDateTime& d2)
{
    if ((m_nSecs == d2.m_nSecs) &&
        (m_nMins == d2.m_nMins) &&
        (m_nHours == d2.m_nHours) &&
        (m_nDay == d2.m_nDay) &&        
        (m_nMonth == d2.m_nMonth) &&
        (m_nYear == d2.m_nYear))
        return 1 ;
    return 0 ;
}

bool CDateTime::operator!= (const CDateTime& d2)
{
    if ((m_nSecs != d2.m_nSecs) || 
        (m_nMins != d2.m_nMins) ||
        (m_nHours != d2.m_nHours) ||
        (m_nDay != d2.m_nDay) ||         
        (m_nMonth != d2.m_nMonth) ||
        (m_nYear != d2.m_nYear))
        return 1 ;
    return 0 ;
}


char *CDateTime::FormatDate(char *dst)
{
    sprintf(dst, "%04d-%02d-%02d", m_nYear, m_nMonth, m_nDay) ; 
    return dst ; 
}

/*
    mode = 0      Mmm D, YYYY.
    mode = 1      
 */
char *CDateTime::FormatDate(char *dst, int mode)
{
    if (mode == 0)
    {
        sprintf(dst, "%s %d, %04d.", 
            CS_MONTHSTRSHORT[m_nMonth-1], m_nDay, m_nYear) ; 
    }

    return dst ; 
}


char *CDateTime::FormatDate(char *dst, char sepchar)
{
    sprintf(dst, "%04d%c%02d%c%02d", m_nYear, sepchar, m_nMonth, sepchar, m_nDay) ; 
    return dst ; 
}

char *CDateTime::FormatDateTime(char *dst)
{
    sprintf(dst, "%04d-%02d-%02d %02d:%02d", 
            m_nYear, m_nMonth, m_nDay,
            m_nHours, m_nMins) ; 
    return dst ; 
}


// This is the time format for MySQL datatime fields. 
// mode=0 (default) YYYY-MM-DD HH:MM:SS
// mode=1           YYYYMMDD_HHMMSS
// mode=2           YYYYMMDDHHMMSS
// mode=3	HHMMSS
char *CDateTime::FormatDateTimeSecs(char *dst, int mode)
{
    if (mode == 0)
    {
        sprintf(dst, "%04d-%02d-%02d %02d:%02d:%02d", 
                    m_nYear, m_nMonth, m_nDay,
                    m_nHours, m_nMins, m_nSecs) ; 
    }        
    else if (mode == 1)
    {
        sprintf(dst, "%04d%02d%02d_%02d%02d%02d", 
            m_nYear, m_nMonth, m_nDay, m_nHours, m_nMins, m_nSecs) ; 
    }
    else if (mode == 2)
    {
        sprintf(dst, "%04d%02d%02d%02d%02d%02d", 
            m_nYear, m_nMonth, m_nDay, m_nHours, m_nMins, m_nSecs) ; 
    }
	else if(mode == 3)
	{
		sprintf(dst, "%02d%02d%02d", 
            m_nHours, m_nMins, m_nSecs) ; 
	}
    return dst ; 
}

/* 
    mode = 0      Mmm D, YYYY, HH:MM{AM|PM} extstring
    mode = 1      Mmm D, YYYY.
 */
char *CDateTime::FormatDateTime(char *dst, char *ext, int mode, int *len)
{
    int slen = 0 ; 
    if (mode == 0)
    {
        int hour = m_nHours ; 
        char apm[6] ; 

        if (hour == 0)
        {
            hour = 12 ; 
            strcpy(apm, "AM") ; 
        }
        else if (hour < 12)
        {
            strcpy(apm, "AM") ; 
        }
        else if (hour == 12)
        {
            strcpy(apm, "PM") ; 
        }
        else
        {
            hour -= 12 ; 
            strcpy(apm, "PM") ; 
        }

        slen = sprintf(dst, "%s %d, %04d, %d:%02d%s %s", 
            CS_MONTHSTRSHORT[m_nMonth-1], m_nDay, m_nYear, 
            hour, m_nMins, apm, (ext ? ext : "")) ; 
    }
    else if (mode == 1)
    {
        slen = sprintf(dst, "%s %d, %04d.", 
            CS_MONTHSTRSHORT[m_nMonth-1], m_nDay, m_nYear) ; 
    }
    if (len)
        *len = slen ; 
    return dst ; 
}

int CDateTime::IsLeapYear()
{
    if (m_nYear % 4 == 0)
    {   // Then this might be a leap year
        if (m_nYear % 400 == 0)
            return 1 ; 

        if (m_nYear % 100 == 0)
            return 0 ; 

        return 1 ; 
    }
    return 0 ; 
}


time_t CDateTime::DeltaSecs(time_t t) 
{
    time_t tt = GetTimeT() ; 
    return tt - t ;
}

int CDateTime::DaysinMonth(int m)
{
    if (m < 1 || m > 12)
        return 31 ;
    int d = daysinmonthSTD[m-1] ; 
    if (IsLeapYear() && m == 2)
        d++ ; // 29 days in 
    return d ; 
}



int CDateTime::operator-(const CDateTime &dt)
{
    time_t ta, tb ; 
    ta = GetTimeT() ; 
    tb = dt.GetTimeT() ; 
    return (int)(ta - tb) ; 
}


int operator-(const CDateTime &dta, const CDateTime &dtb)
{
    time_t ta, tb ; 
    ta = dta.GetTimeT() ; 
    tb = dtb.GetTimeT() ; 
    return (int)(ta - tb) ; 
}


int CDateTime::DaySeconds()
{
    return m_nHours * 3600 + m_nMins * 60 + m_nSecs ;
}


