#include "StdAfx.h"

ExcoDie::ExcoDie(CString in_csID, CString in_csCurrentDate)
	:csID(in_csID), csCurrentDate(in_csCurrentDate)
{
	// get order date, customer id and customer name
	CString csQuery;	csQuery.Format(L"select dcodat, dcbcus, dcbnam from cmsdat.ocrh where dcord#='%s'", in_csID);	ExcoODBC *pDatabase = ExcoODBC::GetInstance();	pDatabase->Open(Solarsoft);	CRecordset* pRecordSet = pDatabase->RunQuery(csQuery);
	if (!pRecordSet->IsEOF())
	{
		CString csValue;
		pRecordSet->GetFieldValue(L"DCODAT", csValue);
		csOrderDate = csValue.Trim();
		pRecordSet->GetFieldValue(L"DCBCUS", csValue);
		csCustID = csValue.Trim();
		pRecordSet->GetFieldValue(L"DCBNAM", csValue);
		csCustName = csValue.Trim();
	}
	pRecordSet->Close();
	// get ExcoPiece list, generate new ExcoPiece objects	csQuery.Format(L"select dnjob, dnpart from cmsdat.cjobh where dnord#='%s'", csID);	pRecordSet = pDatabase->RunQuery(csQuery);
	if (pRecordSet->IsOpen() && !pRecordSet->IsEOF())
	{
		CString csPartID;
		CString csPartDesc;
		pRecordSet->GetFieldValue(L"DNJOB", csPartID);
		pRecordSet->GetFieldValue(L"DNPART", csPartDesc);
		v_pPiece.push_back(new ExcoPiece(csPartID.Trim(), csPartDesc.Trim(), csCurrentDate));
	}
	pRecordSet->Close();
	csQuery.Format(L"select dnjob, dnpart from cmsdat.hjobh where dnord#='%s'", csID);	pRecordSet = pDatabase->RunQuery(csQuery);
	if (pRecordSet->IsOpen() && !pRecordSet->IsEOF())
	{
		CString csPartID;
		CString csPartDesc;
		pRecordSet->GetFieldValue(L"DNJOB", csPartID);
		pRecordSet->GetFieldValue(L"DNPART", csPartDesc);
		v_pPiece.push_back(new ExcoPiece(csPartID.Trim(), csPartDesc.Trim(), csCurrentDate));
	}	pRecordSet->Close();}


ExcoDie::~ExcoDie()
{
	// delete all pieces
	for each (ExcoPiece* pPiece in v_pPiece)
	{
		delete pPiece;
	}
}