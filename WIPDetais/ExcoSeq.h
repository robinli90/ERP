#pragma once

struct ExcoSeq
{
	ExcoSeq(CString in_csID, CString in_csCost);
	~ExcoSeq();
	CString csID;
    double dCost;
};