// SQLDatabase.cpp
// 
// Revision Log
//
// Date       Who SAR     Notes
// ========== === ======= =====================================
// 1999-10-30 mph 00069   Initial coding
// 10/08/2001 mph         Add Commit() and Rollback()
// 
// 2002-04-20 mph         Fix memory leak on fail to close
// 2003-09-06 mph         Add Kirya (mailto:zkv@mail.ru) and
//                        Tom R. (mailto:tom.ritsema@wxs.nl)
//                        changes. (Special thanks for this debug code)
//                        Set values to null in closing and destructor called methods
//
#include "SQLRecordset.h"

#include "SQLDatabase.h"
#include <sqlext.h>

#include <string>
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CSQLDatabase::CSQLDatabase()
:
_isOpen( false ),
_rc( SQL_SUCCESS ),
_henv( 0 ),
_hdbc( 0 ),
_autoCommit( true ),
_hstmt(NULL)
{
    //[2003-09-06] remove connection code and move below
}

CSQLDatabase::~CSQLDatabase()
{
    Close();
}

string& CSQLDatabase::dbmsName()
{
    if ( _dbmsName != "" )
        return _dbmsName;

    char         InfoValuePtr[64];
    SQLSMALLINT  BufferLength = sizeof( InfoValuePtr );
    SQLSMALLINT  StringLengthPtr;

    _rc = SQLGetInfo( _hdbc, SQL_DBMS_NAME, InfoValuePtr,
        BufferLength, &StringLengthPtr );

    if ( !( _rc == SQL_SUCCESS || _rc == SQL_SUCCESS_WITH_INFO ) )
        ThrowError( SQL_HANDLE_DBC );

    _dbmsName = (char*)InfoValuePtr;
    return _dbmsName;
}

bool CSQLDatabase::Open( const char* dsn, const char* user, const char* password ) 
{ 
    _dbmsName  = ""; // reset at each open

    return this->ConnectSQL( dsn, user, password ); 
}

// throws on error
bool CSQLDatabase::OpenEx( const char* dsn, const char* user, const char* password ) 
{ 
    _dbmsName  = ""; // reset at each open

    if ( ! Open( dsn, user, password ) )
        ThrowError( SQL_HANDLE_DBC );

    return true;
}

bool CSQLDatabase::Reconnect()
{
    if ( _isOpen ) 
        Close() ; 

    _dbmsName  = ""; // reset at each open
    return this->ConnectSQL(_dsn.c_str(), _user.c_str(), _pswd.c_str()); 
}

bool CSQLDatabase::Close()
{
    if ( ! _isOpen ) //[2002-04-20] courtesy of bt(2002/01/30); thanks
        return false;

    if ( _hdbc )
    {
        _rc = ::SQLDisconnect( _hdbc );
        if ( _rc == SQL_SUCCESS || _rc == SQL_SUCCESS_WITH_INFO ) 
            _rc = ::SQLFreeHandle( SQL_HANDLE_DBC, _hdbc );
        _hdbc = NULL; //[2003-09-06]
    }

    if ( _henv )
    {
        _rc = ::SQLFreeHandle( SQL_HANDLE_ENV, _henv );
        _henv = NULL; //[2003-09-06]
    }

    _isOpen = false;
    return true;
}

bool CSQLDatabase::ConnectSQL( const char * a_szDSN, 
                              const char* a_szUserName, const char* a_szPassword )
{
    //[2003-09-06] This was in the constructor
    // see: 
    //     http://www.codeguru.com/mfc/comments/44221.shtml 
    // --for details
    ////////////////// start former constructor code ////////////////// 
    _isOpen     = false;
    _rc         = SQL_SUCCESS;
    _henv       = 0;
    _hdbc       = 0;
    _autoCommit = true;

    // Allocate environment handle 
    _rc = SQLAllocHandle( SQL_HANDLE_ENV, SQL_NULL_HANDLE, &_henv ); 
    if ( !( _rc == SQL_SUCCESS || _rc == SQL_SUCCESS_WITH_INFO ) ) 
        return false; 
    _rc = SQLSetEnvAttr( _henv, SQL_ATTR_ODBC_VERSION,( void* )SQL_OV_ODBC3, 0 ); 
    if ( !( _rc == SQL_SUCCESS || _rc == SQL_SUCCESS_WITH_INFO ) ) 
        return false; 
    _rc = SQLAllocHandle( SQL_HANDLE_DBC, _henv, &_hdbc ); 
    if ( !( _rc == SQL_SUCCESS || _rc == SQL_SUCCESS_WITH_INFO ) ) 
        return false; 

    _rc = SQLSetConnectAttr( _hdbc, SQL_LOGIN_TIMEOUT,( void* )7, 0 ); 
    if ( !( _rc == SQL_SUCCESS || _rc == SQL_SUCCESS_WITH_INFO ) ) 
        return false; 

    // _rc = SQLSetConnectAttr( _hdbc, SQL_CONNECTION_TIMEOUT, 0, 0 ); 
    // if ( !( _rc == SQL_SUCCESS || _rc == SQL_SUCCESS_WITH_INFO ) ) 
    //     return false; 

    //////////////////// end former constructor code ////////////////// 

    _rc = ::SQLConnectA( _hdbc,( SQLCHAR* )a_szDSN, SQL_NTS, 
        ( SQLCHAR* )a_szUserName, SQL_NTS,( SQLCHAR* )a_szPassword, SQL_NTS );
    _isOpen = ( _rc == SQL_SUCCESS || _rc == SQL_SUCCESS_WITH_INFO );

    _dsn = a_szDSN ; 
    _user = a_szUserName ; 
    _pswd = a_szPassword ; 

    return _isOpen;
}

bool CSQLDatabase::ExecuteSQL( const char* a_szStmt )
{
    _rc = ::SQLAllocHandle( SQL_HANDLE_STMT, _hdbc, &_hstmt );
    if ( !( _rc == SQL_SUCCESS || _rc == SQL_SUCCESS_WITH_INFO ) )
        ThrowError( SQL_HANDLE_DBC );

    // returns: SQL_SUCCESS, SQL_SUCCESS_WITH_INFO, SQL_NEED_DATA, 
    // SQL_STILL_EXECUTING, SQL_ERROR, SQL_NO_DATA, or SQL_INVALID_HANDLE   
    _rc = ::SQLExecDirectA( _hstmt,( unsigned char* )a_szStmt, SQL_NTS );
    if ( _rc == SQL_SUCCESS || _rc == SQL_SUCCESS_WITH_INFO )
    {
        // COMMIT the transaction
        if ( _autoCommit )
        {
            _rc = ::SQLEndTran( SQL_HANDLE_DBC, _hdbc, SQL_COMMIT );
            if ( !( _rc == SQL_SUCCESS || _rc == SQL_SUCCESS_WITH_INFO ) )
                ThrowError( SQL_HANDLE_DBC );
        }
    }
    else
    {
        if ( _rc != SQL_NO_DATA )
            ThrowError();
    }

    if ( _hstmt != NULL )
    {
        SQLRETURN rc = ::SQLFreeHandle( SQL_HANDLE_STMT, _hstmt );
        _hstmt = NULL;
    }

    bool retVal = _rc == SQL_SUCCESS || _rc == SQL_SUCCESS_WITH_INFO;
    return retVal;
}

int CSQLDatabase::GetSQLInt( const char * a_szStmt, int a_nDefault )
{
    try 
    {
        CSQLRecordset rs( _hdbc );
        if ( rs.SQLExec( a_szStmt ) )
        {
            if ( rs.SQLFetch() ) 
            {
                _sResult = rs.SQLGetData( 1 );
                return atoi( _sResult.c_str() );
            }
        }
        return a_nDefault;
    }
    catch ( CSQLException* e )
    {
        e->Delete(); // must do if not using MFC catch () macro
        return a_nDefault;
    }
}

std::string CSQLDatabase::GetSQLString( const char * a_szStmt, const char* a_szDefault )
{
    static string sDefault;
    sDefault = a_szDefault;
    try 
    {
        CSQLRecordset rs( _hdbc );
        if ( rs.SQLExec( a_szStmt ) )
        {
            if ( rs.SQLFetch() ) 
            {
                _sResult = rs.SQLGetData( 1 );
                return _sResult.c_str();
            }
        }
    }
    catch ( CSQLException* e )
    {
        e->Delete(); // must do if not using MFC catch () macro
    }
    return sDefault.c_str();
}

// see CSQLRecordset::ThrowError(); code is same.  Make a base class?
void CSQLDatabase::ThrowError( SQLSMALLINT handleType )
{
    SQLCHAR     szSQLState[6];
    SQLINTEGER  nNativeError = 0;
    SQLCHAR     szErrorMsg[SQL_MAX_MESSAGE_LENGTH];
    SQLSMALLINT cbErrorMsgMax = sizeof( szErrorMsg ) - 1;
    SQLSMALLINT cbErrorMsg = 0;

    SQLRETURN   rc;
    SQLHANDLE   theHandle = _hstmt; // the default
    switch ( handleType )
    {
    case SQL_HANDLE_ENV:  theHandle = _henv;  break;
    case SQL_HANDLE_DBC:  theHandle = _hdbc;  break;
    case SQL_HANDLE_STMT: theHandle = _hstmt; break;
        //case SQL_HANDLE_DESC: theHandle =       break;
    }

    rc = SQLGetDiagRecA( handleType, theHandle, 1 /*recnumber?*/, szSQLState, 
        &nNativeError, szErrorMsg, cbErrorMsgMax, &cbErrorMsg );
    szSQLState[sizeof( szSQLState )-1]=0; // insurance
    szErrorMsg[cbErrorMsg] = 0;         // more insurance

    CSQLException* pException = new CSQLException();
    pException->m_nRetCode = static_cast<SQLRETURN>(nNativeError) ;
    pException->m_strError = ( const char* )szErrorMsg;
    pException->m_strStateNativeOrigin = ( const char* )szSQLState;

    if ( _hstmt != NULL )
    {
        SQLRETURN rc = ::SQLFreeHandle( SQL_HANDLE_STMT, _hstmt );
        _hstmt = NULL;
    }

    throw pException;
}

bool CSQLDatabase::SupportsTransactions()    // supports ROLLBACK and COMMIT
{
    SQLUINTEGER result;
    SQLRETURN rc = ::SQLGetInfo( _hdbc, SQL_TXN_CAPABLE,( SQLPOINTER )&result, 0, 0 );
    return result != SQL_TC_NONE;
}

void CSQLDatabase::SetAutoCommit( bool tf ) // makes all transactions COMMIT immediately
{
    _autoCommit = tf;

    if ( _autoCommit == true )
        return;

    if ( ! SupportsTransactions() )
        _autoCommit = true;
}

bool CSQLDatabase::GetAutoCommit()
{
    return _autoCommit;
}

bool CSQLDatabase::Commit()
{
    _rc = ::SQLEndTran( SQL_HANDLE_DBC, _hdbc, SQL_COMMIT );
    if ( !( _rc == SQL_SUCCESS || _rc == SQL_SUCCESS_WITH_INFO ) )
        ThrowError( SQL_HANDLE_DBC );
    return true;
}

bool CSQLDatabase::Rollback()
{
    _rc = ::SQLEndTran( SQL_HANDLE_DBC, _hdbc, SQL_ROLLBACK );
    if ( !( _rc == SQL_SUCCESS || _rc == SQL_SUCCESS_WITH_INFO ) )
        ThrowError( SQL_HANDLE_DBC );
    return true;
}
