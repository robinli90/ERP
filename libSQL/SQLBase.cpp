// SQLBase.cpp
// 
// Revision Log
//
// Date       Who SAR     Notes
// ========== === ======= =====================================
// 1999-10-30 mph         Initial coding by Mark Henri of
//                        MPH Software - markhenri@attbi.com
// 2001/10/07 mph         Remove T_Str class
// 2001-10-30 mph         Fix string substitution logic (p != s.npos)
//
//

#include <windows.h>
#include <assert.h>

#include "SQLBase.h"

using namespace std;

//////////////////////////////////////////////////////////////////////
// CSQLBase Class
//////////////////////////////////////////////////////////////////////

/*
const char CSQLBase::STRING         = 1;
const char CSQLBase::JULIAN_DATE    = 2;
const char CSQLBase::ODBC_DATE      = 3;
const char CSQLBase::ORACLE_DATE    = 4;
const char CSQLBase::DATE_YYYY_MM_DD  = 5;
const char CSQLBase::DATE_MMDDYYYY  = 6;
const char CSQLBase::DOUBLE         = 7;
const char CSQLBase::INTEGER        = 8;
const char CSQLBase::LONG           = 9;
const char CSQLBase::DATE_YYYYMMDDHHMMSS= 10;
const char CSQLBase::DATE_YYYYMMDD  = 11;
const char CSQLBase::TIME_HHMMSS    = 12;
*/


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSQLBase::CSQLBase()
{
	m_bConvertQuotes = true;
}

CSQLBase::~CSQLBase()
{
}

//////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////

void CSQLBase::SetTable( const char* tableName )
{
	_table = tableName;
}

CSQLBase& CSQLBase::operator= ( const char* tableName )
{
	_table = tableName;
	return *this;
}


void CSQLBase::ResetContent()
{
	_table = "";
	_stmt  = "";
}


bool CSQLBase::ConvertQuotes( string & s )
{
	if ( ! m_bConvertQuotes )
		return false;

	if ( s.find( '\'' ) == s.npos )
		return false;

	// [20011007]
	string substr1 = "'";
	string substr2 = "''";  // odbc accepts two single quotes as one
	for ( size_t p=s.find( "'" ); p != s.npos ; p=s.find( "'", p ) )
	{
		s.replace( p, 1, "''" );
		p += 2;
	}
	return true;
}

std::string CSQLBase::GetStatement()
{
	return _stmt;
}

void CSQLBase::SetStmt( const char *a_szStmt )
{
	_stmt = a_szStmt;
}
