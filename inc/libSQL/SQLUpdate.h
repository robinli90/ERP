// SQLUpdate.h
// 
// Revision Log
//
// Date       Who SAR     Notes
// ========== === ======= =====================================
// 1999-10-30 mph 00069   Initial coding
// 
//
#ifndef CSQLUPDATE_H
#define CSQLUPDATE_H

#include "SQLBaseWhere.h"
#include <string>

class CSQLUpdate : public CSQLBaseWhere {
public:
    CSQLUpdate();
    CSQLUpdate( const char* table );
    CSQLUpdate(CSQLUpdate& o);
    ~CSQLUpdate();

    std::string GetStatement();
    bool HasColumns() { return (_columns.length() > 0); }

    void SetColumn( const char* a_csAssignment );
    void SetColumn( const char* columnName, const char* a_chValue, char a_DataType=CSQLBase::STRING );
    void SetColumn( const char* columnName, const std::string& a_sValue, char a_DataType=CSQLBase::STRING );
    void SetColumn( const char* columnName, long a_lValue, char a_DataType=CSQLBase::LONG );
    void SetColumn( const char* columnName, double value );
    void SetColumn( const char* columnName, int value );
    //void SetColumn( const char* columnName, COleDateTime& value );
    void SetColumn( const char* columnName, bool isValidTime, int month=0, int day=0, int year=0 );

    void ResetContent();
protected:
private:
    std::string _columns;
};

#endif
