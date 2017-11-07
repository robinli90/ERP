// SQLRecordset.cpp
// 
// Revision Log
//
// Date       Who SAR     Notes
// ========== === ======= =====================================
// 1999-10-30 mph 00069   Initial coding
// 2001-12-03 mph         Initialize error buffers
// 2003-09-06 mph         Disable throw logic
//

#include <windows.h>
#include <stdlib.h>
#include "SQLRecordset.h"
#include <sqlext.h>
#include "dt.h"
#include <assert.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSQLRecordset::CSQLRecordset()
:CSQLBaseWhere(),
_rc( SQL_SUCCESS ),
_hdbc( NULL ),
_hstmt( NULL )
{
}

CSQLRecordset::CSQLRecordset( SQLHDBC a_hdbc )
:CSQLBaseWhere(),
_rc( SQL_SUCCESS ),
_hdbc( a_hdbc ),
_hstmt( NULL )
{
    assert( a_hdbc != NULL );
}

CSQLRecordset::~CSQLRecordset()
{
    SQLFreeStmt(SQL_DROP, false); // false==don't throw on error
}

CSQLRecordset::CSQLRecordset( CSQLDatabase& db )
:CSQLBaseWhere(),
_rc( SQL_SUCCESS ),
_hdbc( db._hdbc ),
_hstmt( NULL )
{
}

void CSQLRecordset::Connect( CSQLDatabase& db )
{
    SQLFreeStmt();
    _hdbc = db._hdbc; 
}

void CSQLRecordset::operator << ( const char* statement )
{
    _stmt = statement;
}

void CSQLRecordset::operator << ( const std::string& statement )
{
    _stmt = statement;
}

bool CSQLRecordset::SQLAllocStmt()
{
    if ( _hdbc == NULL )
        return false;

    SQLFreeStmt();

    _rc = ::SQLAllocStmt( _hdbc, &_hstmt );
    if ( _rc != SQL_SUCCESS && _rc != SQL_SUCCESS_WITH_INFO )
        ThrowError( true ); // use db handle      // [2001-12-03]

    return true;
}

bool CSQLRecordset::SQLExec( const char * a_szStmt )
{
    _stmt = a_szStmt;
    return SQLExec();
}

void CSQLRecordset::ResetContent()
{
    CSQLBaseWhere::ResetContent();
    CSQLBase::ResetContent();
    _groupBy = "";
    _orderBy = "";
    _result  = "";
}

bool CSQLRecordset::SQLExec()
{
    if ( _where != "" )
    {
        _stmt += " where ";
        _stmt += _where;
    }

    if ( _orderBy != "" )
    {
        _stmt += " order by ";
        _stmt += _orderBy;
    }

    if ( _groupBy != "" )
    {
        _stmt += " group by ";
        _stmt += _groupBy;
    }

    if ( ! SQLAllocStmt() )
        return false;

    _rc = ::SQLExecDirectA( _hstmt,( unsigned char* )( const char* )_stmt.c_str(), SQL_NTS );
    if ( _rc != SQL_SUCCESS && _rc != SQL_SUCCESS_WITH_INFO )
        ThrowError();

    return true;
}

bool CSQLRecordset::SQLFetch()
{
    _rc = ::SQLFetch( _hstmt );

    if ( _rc == SQL_NO_DATA_FOUND )
        return false;

    if ( _rc != SQL_SUCCESS && _rc != SQL_SUCCESS_WITH_INFO )
        ThrowError();

    return true;
}

// [2003-09-06]
// Note: since this method gets called from a destructor, we've got to 
// be able to turn of the throw on error logic or else serious program
// errors will result.
void CSQLRecordset::SQLFreeStmt( SQLUSMALLINT a_uType, bool throwOnError )
{
    _rc = SQL_SUCCESS_WITH_INFO; // in case it's null
    if ( _hstmt == NULL )
        return;

    _rc = ::SQLFreeStmt( _hstmt, a_uType );
    _hstmt = NULL;
    if ( _rc != SQL_SUCCESS && _rc != SQL_SUCCESS_WITH_INFO )
        if (throwOnError) // you don't want to throw from a destructor
            ThrowError();
}

void CSQLRecordset::SetHDBC( HDBC* a_hdbc )
{
    SQLFreeStmt();
    _hdbc = a_hdbc;
}

std::string CSQLRecordset::SQLGetData( int a_uRow, int a_eDataType )
{
    _result = "";

    SDWORD cbData;
    // unfinished: rewrite this for pointer to buffer and dynamically allocate it )
    char ach[2024];
    ach[0] = 0;
    _rc = ::SQLGetData( _hstmt,( UWORD )a_uRow, SQL_C_CHAR, ach, sizeof( ach ), &cbData );
    if ( _rc != SQL_SUCCESS && _rc != SQL_SUCCESS_WITH_INFO )
        ThrowError();

    _result = ach;

    if ( a_eDataType == DOUBLE )
    {
        char ach1[32];
        sprintf( ach1, "%.6f", atof( ach ) );
        _result = ach1;
        return _result;
    }
    else if ( a_eDataType == ODBC_DATE )
    {
        TDt dt = ach;
        _result = dt.Format( TDt::ODBC );
        return _result;
    }
    else if ( a_eDataType == DATE_YYYY_MM_DD )
    {
        TDt dt = ach;
        _result = dt.Format( TDt::YYYY_MM_DD );
        return _result;
    }
    else if ( a_eDataType == DATE_YYYYMMDD )
    {
        TDt dt = ach;
        _result = dt.Format( TDt::YYYYMMDD );
        return _result;
    }
    else if ( a_eDataType == DATE_YYYY_MM_DD_HH_MM_SS/* || a_eDataType == DATETIME */)
    {
        return ach;
    }
    else if (a_eDataType == DATE_YYYYMMDDHHMMSS)
    {
        std::string str = ach;
        std::string::iterator it = str.begin();
        while (it != str.end())
        {
            if (!::isalnum(*it))
            {
                it = str.erase(it);
            }
            else
            {
                ++it;
            }
        }
        
        if (str.size() > 14) str.resize(14);

        return str;
    }
    else if ( a_eDataType == DATE_MMDDYYYY )
    {
        TDt dt = ach;
        _result = dt.Format( TDt::MMDDYYYY );
        return _result;
    }
    else if (a_eDataType == TIME_HH_MM_SS)
    {
        return ach;
    }
    else if (a_eDataType == TIME_HHMMSS)
    {
        std::string str = ach;
        std::string::size_type pos;
        while ((pos = str.find(':')) != std::string::npos)
        {
            str.erase(pos, 1);
        }

        return str;
    }
    else
        return _result;
}

int CSQLRecordset::nSQLGetData( int column )
{
    return atoi( SQLGetData( column ).c_str() );
}

bool CSQLRecordset::bSQLGetData( int column )
{
    return( atoi( SQLGetData( column ).c_str() ) != 0 );
}

long CSQLRecordset::lSQLGetData( int column, int a_eDataType )
{
    if ( a_eDataType == JULIAN_DATE || a_eDataType == ODBC_DATE )
    {
        TDt dt = SQLGetData( column ).c_str();
        return dt.Julian();
    }

    return atol( SQLGetData( column ).c_str() );
}

double CSQLRecordset::dblSQLGetData( int column )
{
    return ::atof(SQLGetData(column).c_str());
}

float CSQLRecordset::fSQLGetData(int column)
{
    return (float)::atof(SQLGetData(column).c_str());
}

void CSQLRecordset::SetOrderBy( const char * a_szOrderBy )
{
    _orderBy = a_szOrderBy;
}

void CSQLRecordset::SetGroupBy( const char * a_szGroupBy )
{
    _groupBy = a_szGroupBy;
}

int CSQLRecordset::GetColumns()
{
    char ach[32];
    SDWORD dwDesc;
    SWORD cbDesc;
    _rc = ::SQLColAttributes( _hstmt, 1, SQL_COLUMN_COUNT, ach, sizeof( ach ), &cbDesc, &dwDesc );
    if ( _rc != SQL_SUCCESS && _rc != SQL_SUCCESS_WITH_INFO )
        ThrowError();

    return dwDesc;
}

void CSQLRecordset::ThrowError( bool useDbHandle )
{
    SQLCHAR     szSQLState[6];
    SQLINTEGER  nNativeError = 0;
    SQLCHAR     szErrorMsg[SQL_MAX_MESSAGE_LENGTH];
    SQLSMALLINT cbErrorMsgMax = sizeof( szErrorMsg ) - 1;
    SQLSMALLINT cbErrorMsg = 0;
    SQLRETURN   rc;

    szSQLState[0] = 0; // [2001-12-03]
    szErrorMsg[0] = 0; // [2001-12-03]

    if ( useDbHandle )
    {
        rc = SQLGetDiagRecA( SQL_HANDLE_DBC, _hdbc, 1, szSQLState, 
            &nNativeError, szErrorMsg, cbErrorMsgMax, &cbErrorMsg );
    }
    else
    {
        rc = SQLGetDiagRecA( SQL_HANDLE_STMT, _hstmt, 1, szSQLState, 
            &nNativeError, szErrorMsg, cbErrorMsgMax, &cbErrorMsg );
    }
    szSQLState[sizeof( szSQLState )-1]=0; // insurance

    CSQLException* pException = new CSQLException();
    pException->m_nRetCode = static_cast<SQLRETURN>(nNativeError) ;
    pException->m_strError = ( const char* )szErrorMsg;
    pException->m_strStateNativeOrigin = ( const char* )szSQLState;
    pException->_statement = _stmt;
    throw pException;
}


// the recordset must be active for this to work in
// other words a select must have been done and waiting
// for fetch statements.  Here's a case block--
#if ( 0 )
switch ( n ) {
   case SQL_UNKNOWN_TYPE: break;
   case SQL_CHAR:         break;
   case SQL_NUMERIC:      break;
   case SQL_DECIMAL:      break;
   case SQL_INTEGER:      break;
   case SQL_SMALLINT:     break;
   case SQL_FLOAT:        break;
   case SQL_REAL:         break;
   case SQL_DOUBLE:       break;
   case SQL_DATETIME:     break;
   case SQL_VARCHAR:      break;
   case SQL_DATE:         break;
   case SQL_TIME:         break;
   case SQL_TIMESTAMP:    break;
   default:               break;
}
#endif

int CSQLRecordset::GetColumnType( int a_nColumn )
{
    unsigned char achColName[SQL_MAX_COLUMN_NAME_LEN+1];
    SWORD cbColName;
    SWORD fSQLType;
    UDWORD cbPrecision;
    SWORD cbScale;
    SWORD fNullable;
    _rc = ::SQLDescribeColA( _hstmt, a_nColumn, achColName,
        SQL_MAX_COLUMN_NAME_LEN, &cbColName, &fSQLType, &cbPrecision, 
        &cbScale, &fNullable );
    if ( !( _rc == SQL_SUCCESS || _rc == SQL_SUCCESS_WITH_INFO ) )
    {
        return 0;
    }
    return fSQLType;
}
