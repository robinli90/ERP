// SQLInsert.cpp
// 
// Revision Log
//
// Date       Who SAR     Notes
// ========== === ======= =====================================
// 1999-10-30 mph 00069   Initial coding
// 
//
#include "SQLInsert.h"

#include "dt.h"
#include <string>

CSQLInsert::CSQLInsert()
:CSQLBase()
{
}

CSQLInsert::CSQLInsert( const char* tableName )
:CSQLBase()
{
	SetTable( tableName );
}

CSQLInsert::~CSQLInsert()
{
}

//////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////

void CSQLInsert::SetColumn( const char* columnName, const char* a_chValue, char a_DataType )
{
	if ( _columns != "" )
		_columns += ", ";
	_columns += columnName;

	if ( _values != "" )
		_values += ", ";

	if ( a_chValue[0] == '\0' || stricmp( a_chValue, "NULL" ) == 0 )
	{
		_values += "NULL";
	}
	else if ( strlen( a_chValue ) >= 3 && a_chValue[0] == '{' && a_chValue[1] == 'd' 
		&& a_chValue[2] == '\'' ) // {d'1972-01-15'} etc.
	{
		_values += a_chValue;
	}
	else if ( stricmp( a_chValue, "now()" ) == 0 ) // now()
	{
		_values += a_chValue;
	}
	else // otherwise single quote all strings
	{
		if ( a_DataType == STRING )
		{
			std::string value = a_chValue;
			ConvertQuotes( value );
			_values += "'";
			_values += value;
			_values += "'";
		}
		else if ( a_DataType == ORACLE_DATE )
		{
			TDt dt( a_chValue );
			std::string cs = dt.Format( TDt::ORACLE );
			_values += "'";
			_values += cs;
			_values += "'";
		}
		else if ( a_DataType == ODBC_DATE 
			|| a_DataType == DATE_MMDDYYYY )
		{
			TDt dt( a_chValue );
			std::string cs = dt.Format( TDt::ODBC );
			_values += cs;
		}
		else if ( a_DataType == DOUBLE )
		{
			_values += a_chValue;
		}
		else if ( a_DataType == INTEGER )
		{
			_values += a_chValue;
		}
		else if ( a_DataType == LONG )
		{
			_values += a_chValue;
		}
		else
		{
			std::string value = a_chValue;
			ConvertQuotes( value );
			_values += "'";
			_values += value;
			_values += "'";
		}
	}
}

void CSQLInsert::SetColumn( const char* columnName, const std::string& a_sValue, char a_DataType )
{
	SetColumn( columnName, a_sValue.c_str(), a_DataType );
}

void CSQLInsert::SetColumn( const char* columnName, double value )
{
	if ( _columns != "" )
		_columns += ", ";
	_columns += columnName;

	if ( value > 10000000000000.0 || value < -10000000000000.0 )
		value = 0.0;

	char ach[32];
	sprintf( ach, "%.2f", value );
	if ( _values != "" )
		_values += ", ";
	_values += ach;
}

void CSQLInsert::SetColumn( const char* columnName, int value )
{
	if ( _columns != "" )
		_columns += ", ";
	_columns += columnName;

	char ach[32];
	sprintf( ach, "%d", value );
	if ( _values != "" )
		_values += ", ";
	_values += ach;
}

/*
void CSQLInsert::SetColumn( const char* columnName, COleDateTime& value )
{
if ( _columns != "" )
_columns += ", ";
_columns += columnName;

std::string cs;
if ( value.GetStatus() == COleDateTime::valid )
cs = value.Format( "{d'%Y-%m-%d'}" );
else
cs = "NULL";

if ( _values != "" )
_values += ", ";
_values += cs;
}
*/

void CSQLInsert::SetColumn( const char* columnName, bool isValidTime, int month, int day, int year )
{
	if ( _columns != "" )
		_columns += ", ";
	_columns += columnName;

	std::string cs;
	if ( isValidTime )
	{
		TDt dt( month, day, year );
		cs = dt.Format( TDt::ODBC );
	}
	else
		cs = "NULL";

	if ( _values != "" )
		_values += ", ";
	_values += cs;
}

// strTime¸ñÊ½ yyyy-mm-dd 00:00:00
void CSQLInsert::SetTimeColumn(const char* columnName, const std::string &strTime)
{
	if ( _columns != "" )
		_columns += ", ";
	_columns += columnName;

	std::string cs("{ts\'");
	cs += strTime;
	cs += "\'}";

	if ( _values != "" )
		_values += ", ";
	_values += cs;
}

void CSQLInsert::SetColumn( const char* columnName, long value, char a_DataType )
{
	if ( _columns != "" )
		_columns += ", ";
	_columns += columnName;

	if ( a_DataType == LONG )
	{
		char ach[32];
		sprintf( ach, "%d", value );
		if ( _values != "" )
			_values += ", ";
		_values += ach;
	}
	else if ( a_DataType == ODBC_DATE
		|| a_DataType == JULIAN_DATE )
	{
		TDt dt( value );
		std::string cs = dt.Format( TDt::ODBC );
		if ( _values != "" )
			_values += ", ";
		_values += cs;

	}
}

std::string CSQLInsert::GetStatement()
{
	_stmt = "insert into " + _table + "( ";
	_stmt += _columns;
	_stmt += " ) values ( ";
	_stmt += _values;
	_stmt += " )";
	return _stmt.c_str();
}

void CSQLInsert::ResetContent()
{
	CSQLBase::ResetContent();

	_columns = "";
	_values = "";
}

