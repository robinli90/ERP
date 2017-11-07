// SQLBase.h
//
// Create an SQL update statement
// 
// Revision Log
//
// Date       Who SAR     Notes
// ========== === ======= =====================================
// 1999-10-30 mph 00069   Initial coding
// 
//

/*

  Here is a simple example of how to use this class. 


    CSQLDatabase m_sql ; 
    m_sql.OpenEx("ODBC_name", "username", "password") ;

    try {
        CSQLRecordset rs(m_sql) ;
        rs << "SELECT * FROM users" ; 

        csString firstName, lastName ; 
        rs.SQLExecDirect() ;
        while (rs.SQLFetch())
        {
            firstName = rs.SQLGetData(1).c_str() ;
            lastName  = rs.SQLGetData(2).c_str() ;

            ProcessUser(......) ; 
        }
    }
    catch (CSQLException* e)
    {
        char msgnum[32] ; 
        sprintf(msgnum, "%d: %s", e->m_nRetCode, e->m_strError.c_str()) ; 
        e->Delete(); 
    }

    m_sql.Close() ; 


 */
#ifndef CSQLBASE_H
#define CSQLBASE_H

#pragma warning(disable : 4996)

// use like this: .SetColumn( "postedon", SQLBASE_OLEDATETIME( dtObject ) );
#define SQLBASE_OLEDATETIME(o) ((o).GetStatus()==COleDateTime::valid), (o).GetMonth(), (o).GetDay(), (o).GetYear()
#define SQLBASE_SYSTEMDATETIME(o) ((o).GetYear() != 0), (o).GetMonth(), (o).GetDay(), (o).GetYear()

#include <string>

class CSQLBase 
{
public:
    CSQLBase();
    ~CSQLBase();
    
    void SetStmt( const char* a_szStmt );
    std::string GetStatement();
    
    enum enDataType
    {
    /*  
        static const char STRING;
        static const char JULIAN_DATE;
        static const char ODBC_DATE;
        static const char ORACLE_DATE;
        static const char DATE_YYYY_MM_DD;
        static const char DATETIME;
        static const char DATE_YYYYMMDDHHMMSS;
        static const char DATE_MMDDYYYY;
        static const char DOUBLE;
        static const char INTEGER;
        static const char LONG;
        static const char DATE_YYYYMMDD;
        static const char TIME_HHMMSS;
    */
    STRING,
        JULIAN_DATE,
        ODBC_DATE,
        ORACLE_DATE,
        DATE_YYYY_MM_DD,
        DATETIME,
        DATE_YYYY_MM_DD_HH_MM_SS,
        DATE_YYYYMMDDHHMMSS,
        DATE_MMDDYYYY,
        DOUBLE,
        INTEGER,
        LONG,
        DATE_YYYYMMDD,
        TIME_HH_MM_SS,
        TIME_HHMMSS,
    };
    
    void SetTable( const char* tableName );
    CSQLBase& operator=(const char* );
    void ResetContent();
    
    bool m_bConvertQuotes;
    
    std::string _table;
    std::string _stmt;
    
protected:
    bool ConvertQuotes( std::string& a_cs );
private:
    CSQLBase(CSQLBase& o) {;}
};

// Support function prototypes

int CSQL_ConvertTime(const char *str, struct tm &tmval) ;

#endif
