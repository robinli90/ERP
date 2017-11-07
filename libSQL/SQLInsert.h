// SQLInsert.h
// 
// Revision Log
//
// Date       Who SAR     Notes
// ========== === ======= =====================================
// 1999-10-30 mph 00069   Initial coding
// 
//
#ifndef CSQLINSERT_H
#define CSQLINSERT_H

#include "SQLBase.h"
#include <string>

class CSQLInsert :public CSQLBase 
{
public:
	CSQLInsert();
	CSQLInsert( const char* table );
	CSQLInsert( CSQLInsert& o );
	~CSQLInsert();

	std::string GetStatement();
	bool HasColumns() { return( _columns.length() > 0 ); }
	void SetColumn( const char* columnName, const char* a_chValue, char a_DataType=STRING );
	void SetColumn( const char* columnName, const std::string& a_sValue, char a_DataType=STRING );
	void SetColumn( const char* columnName, double value );
	void SetColumn( const char* columnName, long value, char a_DataType=CSQLBase::LONG );
	void SetColumn( const char* columnName, int value );
	void SetColumn( const char* columnName, bool isValidTime, int month, int day, int year ); // use CSQLBASE_OLEDATETIME( o ) as 2nd arg

	// strTime∏Ò Ω yyyy-mm-dd 00:00:00
	void SetTimeColumn(const char* columnName, const std::string &strTime);

	void ResetContent();
protected:
private:
	std::string _columns;
	std::string _values;
};

#endif
