#include "StdAfx.h"


ExcoSeq::ExcoSeq(CString in_csID, CString in_csCost)
	:csID(in_csID), dCost(_wtof(in_csCost.GetBuffer()))
{
}


ExcoSeq::~ExcoSeq()
{
}
