// SQLBaseWhere.cpp
// 
// Revision Log
//
// Date       Who SAR     Notes
// ========== === ======= =====================================
// 10/07/2001 mph         Remove '*' wildcard conversion and T_Str
//            mph         Initial coding
// 
//
#include "SQLBaseWhere.h"

#include <sstream>
#include <iomanip>
using namespace std;

#include "Dt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSQLBaseWhere::CSQLBaseWhere() : CSQLBase()
{
}

CSQLBaseWhere::~CSQLBaseWhere()
{
}

std::string CSQLBaseWhere::GetStatement( bool includeWhereLiteral )
{
	std::string temp = _stmt;
	if ( _where.length() > 0 )
	{
		if ( includeWhereLiteral )
			temp += " where ";
		temp += _where;
	}
	if ( _orderby.length() > 0 )
	{
		temp += " order by ";
		temp += _orderby;
	}
	return temp;
}

void CSQLBaseWhere::ResetContent()
{
	_where = "";
	CSQLBase::ResetContent();
}

void CSQLBaseWhere::SetWhereParenthesis()
{
	if ( _where == "" )
		return;

	string s = _where;
	_where = "(";
	_where += s;
	_where += ")";
}

void CSQLBaseWhere::SetOrderBy( const char* a_szOrderBy )
{
	_orderby = a_szOrderBy;
}

void CSQLBaseWhere::SetWhere(const char * a_szWhere)
{
	if ( _where != "" )
		_where += " and ";
	_where += a_szWhere;
}

void CSQLBaseWhere::SetWhereOr(const char * a_szWhere)
{
	if ( _where != "" )
		_where += " or ";
	_where += a_szWhere;
}

void CSQLBaseWhere::SetWhere( const char* columnName, int value )
{
	if ( _where != "" )
		_where += " and ";
	_where += columnName;
	_where += "=";

	/* char ach[32]; wsprintf( ach, "%d", value ); _where += ach; */
	ostringstream ss;
	ss << fixed << setprecision(2) << value;
	_where += ss.str(); // unfinished: test this
}

void CSQLBaseWhere::SetWhere( const char* columnName, const std::string& value, char a_DataType, bool a_bUseLike, bool a_bUseOr )
{
	SetWhere( columnName, value.c_str(), a_DataType, a_bUseLike, a_bUseOr );
}

void CSQLBaseWhere::SetWhere( const char* columnName, long value, char a_DataType )
{
	//assert( a_DataType == CSQLBaseWhere::LONG || a_DataType == CSQLBaseWhere::ODBC_DATE || a_DataType == CSQLBaseWhere::JULIAN_DATE);
	if ( _where != "" )
		_where += " and ";
	_where += columnName;
	_where += "=";

	if ( a_DataType == CSQLBaseWhere::LONG )
	{
		/* char ach[32]; wsprintf( ach, "%ld", value ); _where += ach; */
		ostringstream ss;
		ss << dec << value;
		_where += ss.str(); // unfinished: test this
	}
	else if ( a_DataType == CSQLBaseWhere::ODBC_DATE 
		|| a_DataType == CSQLBaseWhere::JULIAN_DATE )
	{
		TDt dt( value );
		string cs = dt.Format( TDt::ODBC );
		_where += cs;
	}
}

void CSQLBaseWhere::SetWhere( const char* columnName, double value )
{
	if ( _where != "" )
		_where += " and ";
	_where += columnName;
	_where += "=";

	/* char ach[32]; wsprintf( ach, "%.2f", value ); _where += ach; */
	ostringstream ss;
	ss << fixed << setprecision(2) << value;
	_where += ss.str(); // unfinished: test this
}

void CSQLBaseWhere::SetWhere( const char* columnName, bool isValidTime, int month, int day, int year )
{
	if ( _where != "" )
		_where += " and ";

	string cs;
	if ( ! isValidTime )
	{
		cs = "isnull(";
		cs += columnName;
		cs += ")";
	}
	else
	{
		TDt dt( month, day, year );
		cs = columnName;
		cs += "=";
		cs += dt.Format( TDt::ODBC );
	}

	_where += cs;
}

void CSQLBaseWhere::SetWhere( const char* columnName, const char* a_value, 
			     char a_DataType, bool a_bUseLike, bool a_bUseOr )
{
	if ( _where != "" )
		_where += (a_bUseOr)?" or ":" and ";

	// Test for NULL immediately because it has to have 
	// a different syntax
	string value = a_value;
	if ( value == "" || value == "NULL" || value == "null" )
	{
		_where += "isnull(";
		_where += columnName;
		_where += ")";
		return;
	}

	// add the column name to the conditional
	_where += columnName;

	// handle a wildcard match
	if ( a_bUseLike && a_DataType == CSQLBaseWhere::STRING )
		_where += " like ";
	else
		_where += "=";

	//
	// Add the remaining data to the right side of the 
	// comparison.  Check if it's an ODBC date string 
	// and process it as is.
	if ( value[0] == '{' && value[1] == 'd' && value[2] == '\'' ) 
	{  
		_where += value; // {d'1972-01-15'} etc.
		return;
	}

	if ( a_DataType == CSQLBaseWhere::STRING )
	{
		ConvertQuotes( value );
		_where += "'";
		_where += value;
		_where += "'";
		return;
	}

	if ( a_DataType == CSQLBaseWhere::ORACLE_DATE )
	{
		TDt dt( value.c_str() );
		string cs = dt.Format( TDt::ORACLE );
		_where += "'";
		_where += cs;
		_where += "'";
		return;
	}

	if ( a_DataType == CSQLBaseWhere::ODBC_DATE )
	{
		TDt dt( value.c_str() );
		string cs = dt.Format( TDt::ODBC );
		_where += cs;
		return;
	}

	_where += value;
}

