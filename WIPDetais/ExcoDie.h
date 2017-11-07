#pragma once

struct ExcoDie
{
	ExcoDie(CString in_csID, CString in_csCurrentDate);
	~ExcoDie();
    CString csID;
    CString csCustID;
    CString csCustName;
    CString csOrderDate;
	CString csCurrentDate;
    vector<ExcoPiece*> v_pPiece;
};