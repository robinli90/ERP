// SQLRecordset.h
// 
// Encapsulates the basic ODBC API select statement eliminating
// the need to remember to free handles and other generic arguments.
//
// Revision Log
//
// Date       Who SAR     Notes
// ========== === ======= =====================================
// 1999-10-30 mph 00069   Initial coding
// 
// Revision log
//
// Sample

/*
#ifdef SAMPLE_CODE
try 
{
	CSQLRecordset rs = g_db;
	rs << "";
	rs.SetWhere( "" );
	rs.SQLExecDirect();
	while ( rs.SQLFetch() )
	{
		int n = 1;
		string sPatient = rs.SQLGetData( n++ );
	}
}
catch ( CSQLException* e )
{
	//HANDLEEXCEPTION( e ); // part of CByteRiteRules::HandleException( ... )
	AfxMessageBox( e->m_strError );
	e->Delete();
}
#endif

*/
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_SQLRECORDSET_H
#define AFX_SQLRECORDSET_H

#include "sqldatabase.h"
#include "sqlbasewhere.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CSQLRecordset : public CSQLBaseWhere
{
	// constructor/destructor
public:
	CSQLRecordset();
	CSQLRecordset( SQLHDBC a_hdbc );
	CSQLRecordset( CSQLDatabase& db );
	virtual ~CSQLRecordset();
	void Connect( CSQLDatabase& db );
	void ResetContent();

	void operator <<( const char* statement );
	void operator <<( const std::string& statement );

	bool SQLExec();
	bool SQLExec( const char* a_szStmt );
	bool SQLExec( const std::string& stmt ) { return SQLExec( stmt.c_str() ); }
	bool SQLFetch();
	std::string SQLGetData( int a_uRow, int a_eDataType=CSQLBase::STRING );

	void     SetOrderBy( const char * a_szOrderBy );
	void     SetGroupBy( const char* a_szGroupBy );

public:
	double   dblSQLGetData( int column );
        float fSQLGetData(int column);
	int      nSQLGetData( int column );
	bool     bSQLGetData( int column );
	long     lSQLGetData( int column, int a_eDataType );
	int      GetColumnType( int a_nColumn );
	int      GetColumns();
	void     SetHDBC( HDBC* a_hdbc );
	bool     SQLAllocStmt();
	void     SQLFreeStmt( SQLUSMALLINT a_uType=SQL_DROP, bool throwOnError=true );
        SQLHDBC GetHDBC(void) const
        {
            return _hdbc;
        }
protected:
	void ThrowError( bool useDbHandle=false ); // [2001-12-03]
private:

	SQLRETURN _rc;

	SQLHDBC   _hdbc;
	SQLHSTMT  _hstmt;

	std::string   _orderBy;
	std::string   _groupBy;

	std::string _result;
};

#endif // !defined( AFX_SQLRECORDSET_H__D1794F02_8E5C_11D3_A73F_004F4904ABE2__INCLUDED_ )
