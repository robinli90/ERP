// Dt.h
// 
// A date object with lots of special features necessary for business.
//
// Revision Log
//
// Date       Who SAR     Notes
// ========== === ======= =====================================
// 1992-06-27 cdp         Initial coding by Charles D. Price
// 1994-03-17 mph         Supplemental coding by Mark Henri of
//                        MPH Software - markhenri@attbi.com
// 1994-03-17 mph         Initial coding( port to current model )
// 1998-06-04 mph         Convert to the new library and make it
//                        use current C++ conventions
// 2001-08-01 mph         Eliminate all MFC references
//
//
// formatting codes--
//    %a  Abbreviated weekday name
//    %A  Full weekday name
//    %b  Abbreviated month name
//    %B  Full month name
//    %c  Date and time representation appropriate for locale
//    %d  Day of month as decimal number( 01 - 31 )
//    %H  Hour in 24-hour format( 00 - 23 )
//    %I  Hour in 12-hour format( 01 - 12 )
//    %j  Day of year as decimal number( 001 - 366 )
//    %m  Month as decimal number( 01 - 12 )
//    %M  Minute as decimal number( 00 - 59 )
//    %p  Current locale’s A.M./P.M. indicator for 12-hour clock
//    %S  Second as decimal number( 00 - 59 )
//    %U  Week of year as decimal number, with Sunday as first day of week( 00 - 53 )
//    %w  Weekday as decimal number( 0 - 6; Sunday is 0 )
//    %W  Week of year as decimal number, with Monday as first day of week( 00 - 53 )
//    %x  Date representation for current locale
//    %X  Time representation for current locale
//    %y  Year without century, as decimal number( 00 - 99 )
//    %Y  Year with century, as decimal number
//    %z, %Z  Time-zone name or abbreviation; no characters if time zone is unknown
//    %%  Percent sign
//
//    %#I removes leading zero if any
//    
//    non-standard ones that I need...
//    %t  [st,nd,rd,th] as in 1st 2nd 3rd 4th etc...
//
// examples--
//    "{d'2001-12-13'}"  is  "{d'%Y-%m-%d'}"

#ifndef DT_H
#define DT_H

#pragma warning(disable : 4996)

#include <string>
using namespace std;

// Display Format

class TDt
{
public:
    TDt();
    TDt( long jul );
    TDt( int m, int d, int y );
    TDt( const char* lpszDate );
    TDt( TDt& dt );  // copy constructor
    
    enum enFormatType
    {
    /*
    static const int FULL;
    static const int EUROPEAN;
    static const int MMDDYYYY;
    static const int MMMDDD;
    static const int DDDW;
    static const int YYYY_MM_DD;
    static const int CRWFORMULA;
    static const int LETTER;
    static const int ODBC;
    static const int MMMYYYY;
    static const int DAY;
    static const int MONTH;
    static const int ORACLE;
    static const int DDMMMYY;
    static const int DD;
    static const int MM;
    static const int YYYY;
    static const int DTH;
    static const int D;
    static const int M;
    static const int YYYYMMDD;
        */
        
        FULL,
            EUROPEAN,
            MMDDYYYY,
            MMMDDD,
            DDDW,
            YYYY_MM_DD,
            YYYYMMDD,
            DDMMMYY,
            MMMYYYY,
            CRWFORMULA,
            LETTER,
            ODBC,
            DAY,
            MONTH,
            ORACLE,
            DD,
            MM,
            YYYY,
            DTH,
            D,
            M
    };
    
    TDt& operator = ( const TDt& dt );
    TDt& operator = ( const char* lpsz );  // dt = "03-01-1993"
    TDt& operator = ( long lJulian );      // dt = 36525 is 12-31-1999
    
    std::string Format( const char* fs );
    std::string Format( int a_nDisplayFormat = MMDDYYYY );
    void Format( char* ach, int size, int a_nDisplayFormat = MMDDYYYY );
    
    TDt& operator += ( int i );
    TDt& operator -= ( int i );
    TDt& operator ++();
    TDt  operator ++( int );
    TDt& operator --();
    TDt  operator --( int );
    
    bool operator <  ( TDt& dt2 ) { return Julian() <  dt2.Julian(); }
    bool operator <= ( TDt& dt2 ) { return Julian() <= dt2.Julian(); }
    bool operator >  ( TDt& dt2 ) { return Julian() >  dt2.Julian(); }
    bool operator >= ( TDt& dt2 ) { return Julian() >= dt2.Julian(); }
    bool operator == ( TDt& dt2 ) { return Julian() == dt2.Julian(); }
    bool operator != ( TDt& dt2 ) { return Julian() != dt2.Julian(); }
    
    friend bool operator < ( long dt1, TDt& dt2 );
    friend bool operator <= ( long dt1, TDt& dt2 );
    friend bool operator > ( long dt1, TDt& dt2 );
    friend bool operator >= ( long dt1, TDt& dt2 );
    friend bool operator == ( long dt1, TDt& dt2 );
    friend bool operator != ( long dt1, TDt& dt2 );
    
    bool operator < ( long l ) { return Julian() <  l; }
    bool operator <= ( long l ) { return Julian() <= l; }
    bool operator > ( long l ) { return Julian() >  l; }
    bool operator >= ( long l ) { return Julian() >= l; }
    bool operator == ( long l ) { return Julian() == l; }
    bool operator != ( long l ) { return Julian() != l; }
    
    //friend ostream& operator <<( ostream &os, TDt& dt );
    //friend ostream& operator <<( ostream &os, const TDt& dt );
    
    void  SetFormat( int format = MMDDYYYY );
    bool  IsNull();
    long  Julian();           // returns julian date
    int   DOY();              // returns relative day since Jan 1
    int   IsLeap();           // returns 1 if leap year, 0 if not
    
    TDt& Set();               // Sets to current system date
    TDt& Set( const char* p );
    TDt& Set( long lJulian );
    TDt& Set( int nMonth, int nDay, int nYear );
    TDt& Set( TDt& dt );
    TDt& Set( const TDt& dt );
    
    TDt& AddWeeks( int nCount = 1 );  //
    TDt& AddMonths( int nCount = 1 ); // May also pass neg# to decrement
    TDt& AddYears( int nCount = 1 );  //
    
    std::string DayName();   // const string pointer to "Monday" etc...    // potential error
    std::string DOWName();   // Day Of Week( 'Sunday'..'Saturday' )        // potential error
    std::string MonthName(); // Character month name                       // potential error
    
    int Day();          // Day number( day of month 1..[28]..[31] )
    int Month();        // [1..12]
    int Year();         // e.g. 1992
    
    int DOW();          //( Sunday=0..Saturday=6 )
    int DOM();          // 2nd tuesday, 3rd wed, etc...
    int WOM();          // Numeric week Of month ( 1..6 )
    int WOY();          // Numeric week Of year  ( 1..52 )
    int DaysInMonth();  // [1..31]
    int FirstDOM();     // First Day Of Month ( 0..6 )
    
    int Age();          // The age of person in years
    int YYMM();         // integer yymm ( 9201 )
    
    TDt& SetBOM();      // First day of Month
    TDt& SetEOM();      // Last day of Month
    TDt& SetBOY();      // First day Of Year
    TDt& SetEOY();      // Last day Of Year
    
    int DifferenceInYears( long d1, long d2 );  // result = d1 - d2
    int DifferenceInMonths( long d1, long d2 );
    
    static int m_nDisplayFormat;
    
private:
    void GetMDY( int& m, int &d, int& y, long jul );
    long GetJulian( int m, int d, int y );
    int  Get4DigitYear( int yy );
    string GetNumberSuffix( int day );
    int m_month;
    int m_day;
    int m_year;
    
    //string _s; // a place to put results from stuff
};
#endif
