#pragma once

// define database types
enum DbType{Solarsoft=1, Decade=2};

class ExcoODBC
{
public:
	~ExcoODBC();
	static ExcoODBC* GetInstance();
	void Open(DbType in_eDb);
	CRecordset* RunQuery(CString in_csQuery);
	void RunQueryNoOutput(CString in_csRuery);
private:
	ExcoODBC();
	CString* pConnString;
	CDatabase* pDb;
	static ExcoODBC* pInstance;
	DbType* pDbType;
	CRecordset* pRecordSet;
};
