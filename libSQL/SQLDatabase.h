// SQLDatabase.h
// 
// Revision Log
//
// Date       Who SAR     Notes
// ========== === ======= =====================================
// 10/08/2001 mph         Add Commit() and Rollback()
// 1999-10-30 mph 00069   Initial coding
// 
//
#ifndef _SQLDATABASE_H__
#define _SQLDATABASE_H__

#pragma warning(disable : 4996)

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _WIN32
#include <windows.h>
// #pragma comment(lib, "odbc32.lib")
#endif
#include <sql.h>
#include <string>
using namespace std;

class CSQLException
{
public:
	CSQLException() :m_nRetCode( 0 ) {;}
	CSQLException( SQLRETURN r ) { m_nRetCode = r; }
	~CSQLException() {;}

	SQLRETURN m_nRetCode;
	string m_strError;
	string m_strStateNativeOrigin;
	string _statement;

	void Delete() { delete this; }
private:
	CSQLException( const CSQLException& o ) {;} // don't allow copy
	//operator = ( CSQLException& ) {;}
};

class CSQLDatabase
{
public:
	CSQLDatabase();
	virtual ~CSQLDatabase();
	bool ConnectSQL( const char* dsn, const char* user="", const char* password="" );
	
        bool Open( const char* dsn, const char* user="", const char* password="" );
	bool OpenEx( const char* dsn, const char* user="", const char* password="" );
        
        //! Attempt to reset the database connection
        /*!
            \return true=successfully reopened connection

            If a query throw's an acception, one of the reasons may be that a network 
            error has occured and the TCP/IP, or PIPE connection to the database has
            suffered an error. Say somebody has reset the power on a main switch for 
            example. Then calling this function will close the existing connection, 
            and attempt to re-open it. If it is successful then true is returned, 
            otherwise it returns false. 
         */
        bool Reconnect() ; 

	bool Close();
	bool ExecuteSQL( const char* a_szStmt );
	bool ExecuteSQL( const std::string& s ) { return ExecuteSQL( s.c_str() ); }
	bool IsOpen(){ return _isOpen;}
	void ThrowError( SQLSMALLINT handleType=SQL_HANDLE_STMT );

	std::string GetSQLString( const char* stmt, const char* sDefault="" );
	int GetSQLInt( const char* stmt, int nDefault=0 );
	SQLRETURN GetRetCode() { return _rc; }


	bool SupportsTransactions();   // supports ROLLBACK and COMMIT
	void SetAutoCommit( bool tf ); // makes all transactions COMMIT immediately
	bool GetAutoCommit();
	bool Commit();
	bool Rollback();
	string& dbmsName();

	SQLRETURN _rc;    // void*
	SQLHENV   _henv;  // void*
	SQLHDBC   _hdbc;  // void*
	HSTMT     _hstmt; // void*

private:
	bool     _isOpen;
	string   _dsn;
	string   _user;
	string   _pswd;
	string   _sResult; // for GetSQL... functions
	bool     _autoCommit;
	string   _dbmsName;  // reset at each open
};

#endif // !defined _SQLDATABASE_H__
