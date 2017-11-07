// SQLBaseWhere.h
// 
// Revision Log
//
// Date       Who SAR     Notes
// ========== === ======= =====================================
// 1999-10-30 mph 00069   Initial coding
// 
//
#ifndef _SQLBASEWHERE_H__
#define _SQLBASEWHERE_H__

#include "SQLBase.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSQLBaseWhere : public CSQLBase
{
public:
	CSQLBaseWhere();
	virtual ~CSQLBaseWhere();

	void SetWhere( const char* a_szWhere );
	void SetWhere( const char* columnName, int value );
	void SetWhere( const char* columnName, long value, char a_DataType=LONG );
	void SetWhere( const char* columnName, double value );
	void SetWhere( const char* columnName, bool isValidTime, int month, int day, int year );
	void SetWhere( const char* columnName, const char* value, char a_DataType=STRING, bool a_bUseLike=false, bool a_bUseOr=false );
	void SetWhere( const char* columnName, const std::string& value, char a_DataType=STRING, bool a_bUseLike=false, bool a_bUseOr=false );

	void SetWhereOr( const char* a_szWhere );
	void SetWhereParenthesis();

	void SetOrderBy( const char* a_szOrderBy );

	std::string GetWhere() { return _where.c_str(); }
	std::string GetStatement( bool includeWhereLiteral=true );
	void ResetContent();
protected:
	std::string _where;
	std::string _orderby;
};

#endif // !defined _SQLBASEWHERE_H__
