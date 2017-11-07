// SQLUpdate.cpp
// 
// Revision Log
//
// Date       Who SAR     Notes
// ========== === ======= =====================================
// 1999-10-30 mph 00069   Initial coding
// 
//
#include "SQLUpdate.h"
#include <sstream>
#include <iomanip>
using namespace std;

#include "dt.h"


CSQLUpdate::CSQLUpdate()
:CSQLBaseWhere()
{
}

CSQLUpdate::CSQLUpdate( const char* table )
:CSQLBaseWhere()
{
    SetTable( table );
}

CSQLUpdate::~CSQLUpdate()
{
}

//////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////
void CSQLUpdate::SetColumn( const char* columnName, const std::string& a_sValue, char a_DataType )
{
    SetColumn( columnName, a_sValue.c_str(), a_DataType );
}

void CSQLUpdate::SetColumn( const char* columnName, const char* a_chValue, char a_DataType )
{
    if ( _columns != "" )
        _columns += ", ";
    _columns += columnName;

    // if there's already an equal sign then don't add one.  This makes
    // it possible for the user to enter "column=column+"
    std::string cs = columnName;
    if ( cs.find( '=' ) == cs.npos )
        _columns += "=";

    if ( a_chValue[0] == '\0' || _stricmp( a_chValue, "NULL" ) == 0)
    {
        _columns += "NULL";
    }
    else if ( strlen( a_chValue ) >= 3 && a_chValue[0] == '{' && a_chValue[1] == 'd' 
        && a_chValue[2] == '\'' ) // {d'1972-01-15'} etc.
    {
        _columns += a_chValue;
    }
    else if ( stricmp( a_chValue, "now()" ) == 0)
    {
        _columns += a_chValue; //[09-18-2001]
    }
    else
    {
        if ( a_DataType == CSQLBase::STRING )
        {
            std::string value = a_chValue;
            ConvertQuotes( value );
            _columns += "'";
            _columns += value;
            _columns += "'";
        }
        else if ( a_DataType == CSQLBase::ORACLE_DATE )
        {
            TDt dt( a_chValue );
            std::string cs = dt.Format( TDt::ORACLE );
            _columns += "'";
            _columns += cs;
            _columns += "'";
        }
        else if ( a_DataType == CSQLBase::ODBC_DATE )
        {
            TDt dt( a_chValue );
            std::string cs = dt.Format( TDt::ODBC );
            _columns += cs;
        }
        else if ( a_DataType == CSQLBase::DOUBLE )
        {
            _columns += a_chValue;
        }
        else if ( a_DataType == CSQLBase::INTEGER )
        {
            _columns += a_chValue;
        }
        else if ( a_DataType == CSQLBase::LONG )
        {
            _columns += a_chValue;
        }
    }
}

void CSQLUpdate::SetColumn( const char* columnName, double value )
{
    if ( _columns != "" )
        _columns += ", ";

    _columns += columnName;

    // if there's already an equal sign then don't add one.  This makes
    // it possible for the user to enter "column=column+"
    std::string cs = columnName;
    if ( cs.find( '=' ) == cs.npos )
        _columns += "=";

    ostringstream os;
    os << fixed << setprecision( 2 ) << value;
    _columns += os.str();
}

void CSQLUpdate::SetColumn( const char* columnName, bool isValidTime, int month, int day, int year )
{
    if ( _columns != "" )
        _columns += ", ";

    _columns += columnName;

    // if there's already an equal sign then don't add one.  This makes
    // it possible for the user to enter "column=column+"
    std::string cs = columnName;
    if ( cs.find( '=' ) == cs.npos )
        _columns += "=";

    if ( isValidTime )
    {
        TDt dt( month, day, year );
        cs = dt.Format( TDt::ODBC );
    }
    else
        cs = "NULL";

    _columns += cs;
}

void CSQLUpdate::SetColumn( const char* columnName, int value )
{
    if ( _columns != "" )
        _columns += ", ";
    _columns += columnName;

    // if there's already an equal sign then don't add one.  This makes
    // it possible for the user to enter "column=column+"
    std::string cs = columnName;
    if ( cs.find( '=' ) == cs.npos )
        _columns += "=";

    ostringstream os;
    os << dec << value;
    _columns += os.str();
}

void CSQLUpdate::SetColumn( const char* columnName, long a_lValue, char a_DataType )
{
    if ( _columns != "" )
        _columns += ", ";
    _columns += columnName;

    // if there's already an equal sign then don't add one.  This makes
    // it possible for the user to enter "column=column+"
    std::string cs = columnName;
    if ( cs.find( '=' ) == cs.npos )
        _columns += "=";

    if ( a_DataType == CSQLBase::ODBC_DATE )
    {
        if ( a_lValue != 0L )
        {
            TDt dt( a_lValue );
            cs = dt.Format( TDt::ODBC );
            _columns += cs;
        }
        else
        {
            _columns += "NULL";
        }
    }
    else
    {
        char ach[32];
        sprintf( ach, "%ld", a_lValue );
        _columns += ach;
    }
}

void CSQLUpdate::SetColumn(const char *a_csAssignment)
{
    if ( _columns != "" )
        _columns += ", ";
    _columns += a_csAssignment;
}

std::string CSQLUpdate::GetStatement()
{
    _stmt = "update " + _table + " set ";
    _stmt += _columns;
    if ( _where != "" )
    {
        _stmt += " where ";
        _stmt += _where;
    }
    return _stmt.c_str();
}

void CSQLUpdate::ResetContent()
{
    CSQLBase::ResetContent();
    CSQLBaseWhere::ResetContent();

    _columns = "";
}

