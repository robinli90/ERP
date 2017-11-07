#include "StdAfx.h"

ExcoPiece::ExcoPiece(CString in_csID, CString in_csDesc, CString in_csCurrentDate)
	:csID(in_csID), csDesc(in_csDesc), csCurrentDate(in_csCurrentDate), dSteelCost(0.0), bHasNitride(true), bIsWIP(true)
{
	ExcoODBC *pDatabase = ExcoODBC::GetInstance();	pDatabase->Open(Solarsoft);	CString csQuery;	// get steel cost
	csQuery.Format(L"select coalesce(sum(fztcos),0.0) as s from cmsdat.jcstt where fzjobn='%s' and fzdate<='%s'", csID, csCurrentDate);	CRecordset* pRecordSet = pDatabase->RunQuery(csQuery);
	if (!pRecordSet->IsEOF())
	{
		CString csValue;
		pRecordSet->GetFieldValue(L"S", csValue);
		dSteelCost = _wtof(csValue.Trim().GetBuffer());
	}
	pRecordSet->Close();
	// get sequences
	csQuery.Format(L"select fwoseq, fwcost from cmsdat.jcsta where fwjobn='%s' and fwdate<='%s order by fwoseq", csID, csCurrentDate);	pRecordSet = pDatabase->RunQuery(csQuery);
	while (!pRecordSet->IsEOF())
	{
		CString csSeqID;
		CString csSeqCost;
		pRecordSet->GetFieldValue(L"FWOSEQ", csSeqID);
		csSeqID = csSeqID.Trim();
		pRecordSet->GetFieldValue(L"FWCOST", csSeqCost);
		csSeqCost = csSeqCost.Trim();
		v_pSeq.push_back(new ExcoSeq(csSeqID, csSeqCost));
		pRecordSet->MoveNext();
	}
	pRecordSet->Close();
	// check if it has nitride
	csQuery.Format(L"select * from cmsdat.cjobdr where edjob#='%s' and edseq#=790", csID);	pRecordSet = pDatabase->RunQuery(csQuery);
	if (pRecordSet->IsEOF())
	{
		pRecordSet->Close();
		csQuery.Format(L"select * from cmsdat.hjobdr where edjob#='%s' and edseq#=790", csID);		pRecordSet = pDatabase->RunQuery(csQuery);
		if (pRecordSet->IsEOF())
		{
			bHasNitride = false;
		}
	}
	pRecordSet->Close();
	// check if WIP or FG
	if (bHasNitride)
	{
		if (_wtoi(v_pSeq.back()->csID) >= 790)
		{
			bIsWIP = false;
		}
	}
	else
	{
		if (_wtoi(v_pSeq.back()->csID) >= 780)
		{
			bIsWIP = false;
		}
	}
}


ExcoPiece::~ExcoPiece()
{
	for each (ExcoSeq *pSeq in v_pSeq)
	{
		delete pSeq;
	}
}