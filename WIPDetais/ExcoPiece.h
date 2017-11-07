#pragma once

struct ExcoPiece
{
	ExcoPiece(CString in_csID, CString in_csDesc, CString in_csCurrentDate);
	~ExcoPiece();
    CString csID;
    CString csDesc;
	CString csCurrentDate;
    double dSteelCost;
	bool bIsWIP;
    bool bHasNitride;
    vector<ExcoSeq*> v_pSeq;
};