//-------------------------------------------------------------------------------
// Module:  eclscdsc.hpp
//-------------------------------------------------------------------------------
//
// Description:  ECLSreenDesc header file. 
//
//-------------------------------------------------------------------------------
// Copyright Notice: IBM Personal Communications
//                   Licensed Materials - Property of IBM
//                   5639-I70
//                   (c) Copyright IBM Corp. 1991, 2002 All Rights Reserved.
//                   US Government Users Restricted Rights - Use, duplication
//                   or disclosure restricted by GSA ADP Schedule Contract
//                   with IBM Corp.
//-------------------------------------------------------------------------------
#include "eclall.hpp"                                                  
#ifndef _SCREN_DESC_H
#define _SCREN_DESC_H

typedef enum{DONTCARE=0x00, NOTINHIBITED}OIAStatus;

class ECLSDData;
class ECLScreenReco;

class DllExport ECLScreenDesc
{
private: // Class private data
    ECLSDData* pd;

protected:
    //Implementation, Not for publication
    void AddStringPos(LPCSTR s, UINT pos = 0, BOOL CaseSensitive = TRUE);

public:
    ECLScreenDesc();
    ~ECLScreenDesc();

    void AddCursorPos(UINT row, UINT col);
    void AddAttrib(BYTE attrib, UINT pos, PS_PLANE plane = FieldPlane);
    void AddAttrib(BYTE attrib, UINT row, UINT col, PS_PLANE plane = FieldPlane);
    void AddString(LPCSTR s,UINT row, UINT col, BOOL CaseSensitive = TRUE);
    void AddStringInRect(LPCSTR s,int top, int left, int bottom, int right, BOOL CaseSensitive = TRUE);
    void AddOIAInhibitStatus(OIAStatus type = NOTINHIBITED);
    void AddNumFields(UINT n);
    void AddNumInputFields(UINT n);
    void Clear();

    friend class ECLScreenReco;
};

#endif
