#include "StdAfx.h"

ExcoODBC::ExcoODBC()
{
	pConnString = new CString();
	pDb = new CDatabase();
	pDbType = new DbType();
	pRecordSet = new CRecordset();
}


ExcoODBC::~ExcoODBC()
{
	pRecordSet->Close();
	pDb->Close();
	delete pConnString;
	delete pDb;
	delete pDbType;
	delete pRecordSet;
}


ExcoODBC* ExcoODBC::pInstance = NULL;


ExcoODBC* ExcoODBC::GetInstance()
{
	if(!pInstance)
    {
        pInstance = new ExcoODBC();
    }
    return pInstance;
}


// be able to open and swith database connections
void ExcoODBC::Open(DbType in_eDatabase)
{
	// open database
	if (in_eDatabase != *pDbType)
	{
		*pDbType = in_eDatabase;
		switch (*pDbType)
		{
		case Solarsoft:
			pConnString->SetString(L"DSN=cms1;UID=ZWANG;PWD=ZWANG");
			break;
		case Decade:
			pConnString->SetString(L"DSN=decade;UID=jamie;PWD=jamie");
			break;
		default:
			throw runtime_error("Unknown database");
		}
		if (NULL != pDb->IsOpen())
		{
			pDb->Close();
		}
		if (NULL == pDb->OpenEx(*pConnString))
		{
			throw runtime_error("Failed to open database");
		}
		pRecordSet->m_pDatabase = pDb;
		pDb->SetQueryTimeout(0);
	}
}


// execute query with record set output
CRecordset* ExcoODBC::RunQuery(CString csQuery)
{
	if (TRUE == pRecordSet->IsOpen())
	{
		throw runtime_error("Failed to close record set before executing a new query");
	}
	if (FALSE == pRecordSet->Open(CRecordset::forwardOnly, csQuery))
	{
		throw runtime_error("Failed to get record set");
	}
	return pRecordSet;
}


// execute query without output
void ExcoODBC::RunQueryNoOutput(CString csQuery)
{
	if (pDb->IsOpen())
	{
		pDb->ExecuteSQL(csQuery);
	}
}