// Dt.cpp
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
// 1998-06-04 mha         Convert to the new library and make
//                        it use current C++ conventions
// 2001-11-15 mph         remove commented out code
//
#include "dt.h"

#include <windows.h>

#include <sstream>
#include <iomanip>
using namespace std;

#include <math.h>
#include <time.h>

/*
const int TDt::FULL       =  1;
const int TDt::EUROPEAN   =  2;
const int TDt::MMDDYYYY   =  3;
const int TDt::MMMDDD     =  4;
const int TDt::DDDW       =  5;
const int TDt::YYYY_MM_DD =  6;
const int TDt::CRWFORMULA =  7;
const int TDt::LETTER     =  8;
const int TDt::ODBC       =  9;
const int TDt::MMMYYYY    = 10;
const int TDt::DAY        = 11;
const int TDt::MONTH      = 12;
const int TDt::ORACLE     = 13;
const int TDt::DDMMMYY    = 14;
const int TDt::DD         = 15;
const int TDt::MM         = 16;
const int TDt::YYYY       = 17;
const int TDt::DTH        = 18;
const int TDt::D          = 19;
const int TDt::M          = 20;
const int TDt::YYYYMMDD   = 21;
*/

int TDt::m_nDisplayFormat = TDt::MMDDYYYY;

// Constructors
TDt::TDt() 
{ // Set to today
    Set();
    SetFormat( TDt::MMDDYYYY );
}

TDt::TDt( long j ) 
{
    Set( j );
    SetFormat( TDt::MMDDYYYY );
}

TDt::TDt( int m, int d, int y ) 
{
    Set( m, d, y );
    SetFormat( TDt::MMDDYYYY );
}

TDt::TDt( const char *lpszDate ) 
{
    Set( lpszDate );
    SetFormat( TDt::MMDDYYYY );
}

TDt::TDt( TDt& dt ) 
{
    Set( dt );
    SetFormat( TDt::MMDDYYYY );
}

//
// Magic conversion routines
//
long TDt::Julian()
{
    return GetJulian( m_month, m_day, m_year );
}

//
// Assignment operators
//
TDt& TDt::operator = ( const TDt& dt ) 
{
    return Set( dt );
}

TDt& TDt::operator = ( const char* p ) 
{
    return Set( p );
}

TDt& TDt::operator = ( long l ) 
{
    return Set( l );
}

//
// Incremental operators
//
TDt& TDt::operator += ( int i ) 
{
    long j = GetJulian( m_month, m_day, m_year );
    j += i;
    GetMDY( m_month, m_day, m_year, j );
    return *this;
}

TDt& TDt::operator -= ( int i ) 
{
    long j = GetJulian( m_month, m_day, m_year );
    j -= i;
    GetMDY( m_month, m_day, m_year, j );
    return *this;
}

TDt& TDt::operator ++() 
{
    long j = GetJulian( m_month, m_day, m_year );
    j++;
    GetMDY( m_month, m_day, m_year, j );
    return *this;
}

TDt TDt::operator ++( int ) 
{
    long j = GetJulian( m_month, m_day, m_year );
    j++;
    GetMDY( m_month, m_day, m_year, j );
    return *this;
}

TDt& TDt::operator --() 
{
    long j = GetJulian( m_month, m_day, m_year );
    j--;
    GetMDY( m_month, m_day, m_year, j );
    return *this;
}

TDt TDt::operator --( int ) 
{
    long j = GetJulian( m_month, m_day, m_year );
    j--;
    GetMDY( m_month, m_day, m_year, j );
    return *this;
}

//
// comparison operators
//
bool operator <( long l, TDt& dt2 ) 
{
    return l < dt2.Julian();
}

bool operator <= ( long l, TDt& dt2 ) 
{
    return( l == dt2.Julian() ) ||( l < dt2.Julian() );
}

bool operator >( long l, TDt& dt2 ) 
{
    return( l > dt2.Julian() );
}

bool operator >= ( long l, TDt& dt2 ) 
{
    return( l == dt2.Julian() ) ||( l > dt2.Julian() );
}

bool operator == ( long l, TDt& dt2 ) 
{
    return l == dt2.Julian();
}

bool operator != ( long l, TDt& dt2 ) 
{
    return l != dt2.Julian();
}

//
// Ostream operations
//
/*
ostream& operator <<( ostream &os, TDt& dt ) 
{
dt.Format();
os << dt.m_dsDate;
return os;
}

ostream& operator <<( ostream &os, const TDt& dt ) 
{
TDt& ndt = const_cast<TDt&>( dt );
ndt.Format();
os << ndt.m_dsDate;
return os;
}
*/

//
// Format routine
//
std::string TDt::Format( const char* fs )
{
    string s;
    char ach[128];
    tm time;
    memset( &time, 0, sizeof( tm ) );
    time.tm_year = m_year - 1900;
    time.tm_mon  = m_month - 1; // jan==0
    time.tm_mday = m_day;

    //#pragma MESSAGE( Add day of week week of year etc to this )

    strftime( ach, sizeof( ach ), fs, &time );
    ach[sizeof( ach )-1] = 0; // insurance
    s = ach;

    // add st nd rd th where appropriate
    // change case also?

    return s.c_str();
}

void TDt::Format(  char* ach, int size, int a_nDisplayFormat ) 
{
    string s = Format( a_nDisplayFormat );
    strncpy( ach, s.c_str(), size-1 );
    ach[size-1] = 0; // buffer safety
}

std::string TDt::Format(  int a_nDisplayFormat ) 
{
    string s;
    //
    // this stuff needs to be moved into a resource area( bug )
    //
    static const char *DayName[] = {"Sunday", "Monday",
        "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"} ;
    static const char *MonthName[] = {"January","February","March","April","May",
        "June","July","August","September","October","November","December"};

    int nDisplayFormat; 
    if ( a_nDisplayFormat == -1 )
        nDisplayFormat = m_nDisplayFormat;
    else
        nDisplayFormat = a_nDisplayFormat;

    switch ( nDisplayFormat )
    {
    case TDt::DD:
        {
            ostringstream os;
            os << dec << setfill( '0' ) << setw( 2 ) << setiosflags( ios::right ) << m_day;
            s = os.str();
        }
        break;

    case TDt::D:
        {
            ostringstream os;
            os << dec << m_day;
            s = os.str();
        }
        break;

    case TDt::MM:
        {
            ostringstream os;
            os << dec << setfill( '0' ) << setw( 2 ) << setiosflags( ios::right ) << m_month;
            s = os.str();
        }
        break;

    case TDt::M:
        {
            ostringstream os;
            os << dec << m_month;
            s = os.str();
        }
        break;

    case TDt::YYYY:
        {
            ostringstream os;
            os << dec << m_year;
            s = os.str();
        }
        break;

    case TDt::DTH:
        s = Format( TDt::D );
        s += GetNumberSuffix( m_day );
        break;

    case TDt::DAY:
        if ( ! IsNull() )
            s = DayName[DOW()];
        break;

    case TDt::MONTH:
        if ( ! IsNull() )
            s = MonthName[Month()-1];
        break;

    case TDt::FULL: // Monday, January 2nd, 1998
        if ( ! IsNull() )
        {
            string csSuffix = GetNumberSuffix( Day() );
            string csDayName = DayName[DOW()];
            string csMonthName = MonthName[Month()-1];
            s = csDayName;
            s += ", ";
            s += csMonthName;
            s += " ";
            s += Format( TDt::D );
            s += csSuffix;
            s += ", ";
            s += Format( TDt::YYYY );
        }
        break;

    case TDt::LETTER: // March 23rd, 2001
        if ( ! IsNull() )
        {
            string csSuffix = GetNumberSuffix( Day() );
            string csMonthName = MonthName[Month()-1];
            s += csMonthName;
            s += " ";
            s += Format( TDt::D );
            s += csSuffix;
            s += ", ";
            s += Format( TDt::YYYY );
        }
        break;

    case TDt::EUROPEAN: // 23 March, 2001
        if ( ! IsNull() )
        {   
            string csMonthName = MonthName[Month()-1];
            s += Format( TDt::D );
            s += " ";
            s += csMonthName;
            s += " ";
            s += Format( TDt::YYYY );
        }
        break;

    case TDt::MMMYYYY: // March 1999
        if ( ! IsNull() )
        {
            string csMonthName = MonthName[Month()-1];
            s += csMonthName;
            s += " ";
            s += Format( TDt::YYYY );
        }
        break;
    case TDt::ORACLE: // 02-JUL-2001
        if ( ! IsNull() )
        {
            string csMonthName = MonthName[Month()-1];
            csMonthName.erase( 3, 50 );
            s += Format( TDt::DD );
            s += "-";
            s += csMonthName;
            s += "-";
            s += Format( TDt::YYYY );
        }
        break;

    case TDt::ODBC:
        if ( ! IsNull() )
        {
            ostringstream os;
            os << "{d'";
            os << dec << setfill( '0' ) << setw( 4 ) << setiosflags( ios::right ) << m_year;
            os << "-";
            os << dec << setfill( '0' ) << setw( 2 ) << setiosflags( ios::right ) << m_month;
            os << "-";
            os << dec << setfill( '0' ) << setw( 2 ) << setiosflags( ios::right ) << m_day;
            os << "'}";
            s = os.str();
        }
        break;

    case TDt::CRWFORMULA:
        if ( ! IsNull() )
        {
            ostringstream os;
            os << "date( ";
            os << dec << setfill( '0' ) << setw( 4 ) << setiosflags( ios::right ) << m_year;
            os << ",";
            os << dec << setfill( '0' ) << setw( 2 ) << setiosflags( ios::right ) << m_month;
            os << ",";
            os << dec << setfill( '0' ) << setw( 2 ) << setiosflags( ios::right ) << m_day;
            os << " )";
            s = os.str();
        }
        break;

    case TDt::YYYY_MM_DD:
        if ( ! IsNull() )
        {
            ostringstream os;
            os << dec << setfill( '0' ) << setw( 4 ) << setiosflags( ios::right ) << m_year;
            os << "-";
            os << dec << setfill( '0' ) << setw( 2 ) << setiosflags( ios::right ) << m_month;
            os << "-";
            os << dec << setfill( '0' ) << setw( 2 ) << setiosflags( ios::right ) << m_day;
            s = os.str();
        }
        break;
    case TDt::YYYYMMDD:
        if ( ! IsNull() )
        {
            ostringstream os;
            os << dec << setfill( '0' ) << setw( 4 ) << setiosflags( ios::right ) << m_year;
            os << dec << setfill( '0' ) << setw( 2 ) << setiosflags( ios::right ) << m_month;
            os << dec << setfill( '0' ) << setw( 2 ) << setiosflags( ios::right ) << m_day;
            s = os.str();
        }
        break;

    case TDt::MMDDYYYY:
        if ( ! IsNull() )
        {
            ostringstream os;
            os << dec << setfill( '0' ) << setw( 2 ) << setiosflags( ios::right ) << m_month;
            os << "-";
            os << dec << setfill( '0' ) << setw( 2 ) << setiosflags( ios::right ) << m_day;
            os << "-";
            os << dec << setfill( '0' ) << setw( 4 ) << setiosflags( ios::right ) << m_year;
            s = os.str();
        }
        break;
    default:
        s = "??-??-????";
    }

    return s.c_str(); // alive as long as the object is
}

void TDt::SetFormat( int format ) 
{
    m_nDisplayFormat = format;
}

//
// Assignment methods
//
TDt& TDt::Set()  // Get today's date
{
#if _MSC_VER < 1100
    /*
    time_t osBinaryTime;     // C run-time time( defined in <time.h> )
    time( &osBinaryTime ) ;  // Get the current time from the
    // operating system.
    CTime time3( osBinaryTime );  // CTime from C run-time time
    return Set( osBinaryTime.Format( "%m/%d/%y" ) );
    */
    dosdate_t ddt;
    _dos_getdate( &ddt );
    return Set( ddt.month, ddt.day, ddt.year );

#else
    SYSTEMTIME st;
    GetLocalTime( &st );
    return Set( st.wMonth, st.wDay, st.wYear );
#endif
}

// Possible formats--
//   mm/dd/yy
//   mm/dd/yyyy
//   mm/d/yy
//   m/d/yy
//   mddyy
//   mmddyy
//   mmddyyyy
//     *also with dashes "-"
TDt& TDt::Set( const char* a_p ) 
{
    if ( a_p == NULL || a_p[0] == 0 ) // null or zero string
        return Set( 0L ); // default to null

    int len = (int)strlen( a_p );

    // check for ODBC timestamp 'yyyy-mm-dd' or 'yyyy-mm-dd 00:00:00'
    //if ( len == 10 )
    if ( a_p[4] == '-' && a_p[7] == '-' )
        return Set( atoi( &( a_p[5] ) ), atoi( &( a_p[8] ) ), atoi( a_p ) );

    // test if the user entered mmddyy
    bool bIsNumeric = TRUE;
    int n ; 
    for (n=0; n < len; n++ )
        if ( a_p[n] < '0' || a_p[n] > '9' )
        {
            bIsNumeric = false;
            break;
        }

    char p[16];
    strncpy( p, a_p, sizeof( p ) );

    if ( bIsNumeric &&( len == 6 || len == 8 ) ) // 'mm-dd-yy' or 'mm-dd-yyyy'
    {
        int Year = atoi( &( p[6] ) );
        p[5] = 0;
        int Day = atoi( &( p[3] ) );
        p[2] = 0;
        int Month = atoi( p );
        return Set( Month, Day, Get4DigitYear( Year ) );
    }

    for (n=0; n < len; n++ )
        if ( p[n] == '-' )
            p[n] = '/';

    int month = atoi( p );
    if ( month == 0 || month < 1 || month > 12 ) // somethings wrong
        return Set(); // default to today

    char* i = strchr( p, '/' );
    if ( i == NULL )
        return Set();

    int day = atoi( ++i );
    if ( day < 1 || day > 31 ) 
    {
        Set();
        return Set( month, Day(), Year() ); // use the month arg
    }

    i = strchr( i, '/' );
    if ( i == NULL )
        return Set();

    int year = atoi( ++i );
    //if ( year == 0 ) 
    //{
    //   Set();
    //   return Set( month, day, Year() );
    //}

    return Set( month, day, Get4DigitYear( year ) );
}

/*
#ifndef WIN32
TDt& TDt::Set( const dosdate_t& ddt ) 
{
return Set( ddt.month, ddt.day, ddt.year );
}
#endif
*/

// Convert mdy into a number that is the days since 1/1/0001 a.d.
TDt& TDt::Set( int am, int ad, int ay ) 
{
    m_month = am;
    m_day = ad;
    m_year = ay;
    if ( m_month && m_day ) // non zero
        Get4DigitYear( ay );

    return *this;
}

TDt& TDt::Set( long j ) 
{
    GetMDY( m_month, m_day, m_year, j );
    return *this;
}

TDt& TDt::Set( TDt& dt ) 
{
    m_month = dt.Month();
    m_day = dt.Day();
    m_year = dt.Year();
    return *this;
}

TDt& TDt::Set( const TDt& dt ) 
{
#if _MSC_VER < 1100
    TDt& ndt = ( TDt& )( dt );
    m_month = ndt.Month();
    m_day = ndt.Day();
    m_year = ndt.Year();
    return *this;
#else
    TDt& ndt = const_cast<TDt&>( dt );
    m_month = ndt.Month();
    m_day = ndt.Day();
    m_year = ndt.Year();
    return *this;
#endif
}

//
//  Miscellaneous Routines
//
int TDt::IsLeap() 
{
    return( ( m_year >= 1582 ) ?
        ( m_year % 4 == 0  &&  m_year % 100 != 0  ||  m_year % 400 == 0 ):
    ( m_year % 4 == 0 ) );
}

int TDt::Day()  
{
    return m_day;
}

int TDt::Month()  
{
    return m_month;
}

int TDt::Year()  
{
    return m_year;
}

TDt& TDt::SetBOM() 
{
    Set( Month(), 1, Year() );
    return *this;
}

TDt& TDt::SetEOM() 
{
    AddMonths( 1 );
    SetBOM();
    ( *this )--;
    return *this;
}

TDt& TDt::SetBOY() 
{
    Set( 1, 1, Year() );
    return *this;
}

TDt& TDt::SetEOY() 
{
    Set( 12, 31, Year() );
    return *this;
}

// This is not an accurate idea( ????? )
int TDt::YYMM()  
{      // integer yymm ( 9201 )
    int nY = Year();
    if ( nY > 1999 ) {
        nY -= 2000;
    } else if ( nY > 1900 ) {
        nY -= 1900;
    }
    return( nY * 100 ) + Month();
}

int TDt::DOY() 
{
    TDt temp( 1, 1, Year() );

    return( int )( Julian() - temp.Julian() + 1 );
}

int TDt::DaysInMonth() 
{
    static int GauDays[] = { 31, 28, 31, 30,
        31, 30, 31, 31, 30, 31, 30, 31 };
    return GauDays[Month()-1] +( Month()==2 && IsLeap() );
}

int TDt::FirstDOM() 
{
    TDt dt( Month(), 1, Year() );
    int i = dt.DOW() + 1;
    return i;
}

int TDt::DOW() 
{
    return( int )( ( Julian() % 7 ) ); // Sun == 0 .. Sat == 6
}

// 3rd Wednesday etc...
int TDt::DOM()  
{
    return( ( Day() - 1 ) / 7 ) + 1;
}

int TDt::WOM() 
{
    // Abs day includes the days from previous month that fills up
    // the begin. of the week.
    int nAbsDay = Day() + FirstDOM()-1;
    return( nAbsDay-( DOW() ) )/7 + 1;
}

int TDt::WOY() 
{
    TDt dt( 1, 1, Year() );
    return( int )( (( Julian() - dt.Julian() + 1 ) / 7 ) + 1 );
}

TDt& TDt::AddWeeks( int nCount ) 
{
    long j = GetJulian( m_month, m_day, m_year );
    j += ( nCount * 7 );
    GetMDY( m_month, m_day, m_year, j );
    return *this;
}

TDt& TDt::AddMonths( int nCount ) 
{
    m_month += nCount;

    while ( m_month < 1 ) {
        m_month += 12;
        m_year--;
    }

    while ( m_month > 12 ) {
        m_month -= 12;
        m_year++;
    }
    return *this;
}

// Possible bug on leap year 2-29-??
TDt& TDt::AddYears( int nCount ) 
{
    int m = Month();
    int d = Day();
    int y = Year() + nCount;
    Set( m, d, y );
    return *this;
}

std::string TDt::DayName() 
{
    return Format( TDt::DAY );
}

std::string TDt::MonthName() 
{
    return Format( TDt::MONTH );
}

// d1 - d2 = result
int TDt::DifferenceInYears( long d1, long d2 ) 
{
    TDt dt1 = d1;
    TDt dt2 = d2;
    return dt1.Year() - dt2.Year();
}

// d1 - d2 = result
int TDt::DifferenceInMonths( long d1, long d2 ) 
{
    TDt dt1 = d1;
    TDt dt2 = d2;
    double dbl1 = ( ( dt1.Year() * 12 ) + dt1.Month() );
    double dbl2 = ( ( dt2.Year() * 12 ) + dt2.Month() );
    double dbl = dbl1 - dbl2;
    int n = ( int )dbl;
    return n;
}

int TDt::Age() 
{

    if ( Julian() == 0 )
        return 0;

    TDt dtToday;
    int nAge = ( int )( dtToday.Julian() - Julian() );
    nAge = nAge / 365;
    return nAge;
}

void TDt::GetMDY( int& nm, int &nd, int& ny, long jul )
{
    if ( jul == 0 )
    {
        nm = 0;
        nd = 0;
        ny = 0;
        return;
    }
    double m, d, y, dayno;
    dayno = jul;
    dayno += 443;
    y = floor( ( dayno - 122.1 ) / 365.25 );
    m = floor( ( dayno - floor( 365.25 * y ) ) / 30.6001 );
    d = dayno - floor( 365.25 * y ) - floor( 30.6001 * m );
    m = ( m < 14 ) ? m - 1 : m - 13;
    y = ( m < 3 ) ? y + 1 : y;

    nm = ( int )m; // verify this; use new casting methods
    nd = ( int )d;
    ny = ( int )y;
}

long TDt::GetJulian( int am, int ad, int ay )
{
    double m, y;
    long jul;

    if ( am == 0 && ad == 0 && ay == 0 )
        return 0L;

    y = Get4DigitYear( ay );

    if ( am > 2 ) {
        m = am + 1.0;
        y = ay;
    } else {
        m = am + 13.0;
        y = ay - 1;
    }
    jul = ( long )( floor( 365.25 *( y ) ) + floor( 30.6001 * m ) + ad );
    jul -= 443;

    return jul;
}

int TDt::Get4DigitYear( int yy )
{
    // Use the Oracle convention breaking on 2049/1950
    if ( yy >= 0 && yy < 50 ) {
        yy += 2000;
    } else if ( yy >= 50 && yy <= 99 ) {
        yy += 1900;
    }
    return yy;
}

bool TDt::IsNull()
{
    return m_month == 0 && m_day == 0 && m_year == 0;
}

// 1st 2nd 3rd 4th 20th 21st 22nd 23rd 24th 30th 31st
string TDt::GetNumberSuffix( int day )
{
    static string s;

    if ( day == 1 || day == 21 || day == 31 )
        s = "st";
    else if ( day == 2 || day == 22 )
        s = "nd";
    else if ( day == 3 || day == 23 )
        s = "rd";
    else
        s = "th";
    return s.c_str();
}

