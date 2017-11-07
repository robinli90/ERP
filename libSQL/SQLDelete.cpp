// SQLDelete.cpp
// 
// Revision Log
//
// Date       Who SAR     Notes
// ========== === ======= =====================================
// 1999-10-30 mph 00069   Initial coding
// 
//
#include "SQLDelete.h"

CSQLDelete::CSQLDelete()
:CSQLBaseWhere()
{
}

CSQLDelete::CSQLDelete( const char* table )
:CSQLBaseWhere()
{
	SetTable( table );
}

CSQLDelete::~CSQLDelete()
{
}

//////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////
std::string CSQLDelete::GetStatement()
{
	_stmt = "delete from " + _table;
	if ( _where != "" )
	{
		_stmt += " where ";
		_stmt += _where;
	}
	return _stmt.c_str();
}

