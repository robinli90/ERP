//-------------------------------------------------------------------------------
// Module:  eclscrec.hpp
//-------------------------------------------------------------------------------
//
// Description:  ECLSreenReco header file. 
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
#ifndef _SCREN_RECO_H
#define _SCREN_RECO_H

class ECLScreenDesc;
class ECLRecoNotify;
class ECLScreenNotify;
class ECLSRData;

class DllExport ECLScreenReco
{
private: // Class private data
    ECLSRData* pd;
protected:
    void AnalyzeEvent(ECLPS* ps);
    void GenerateStops(ECLPS* ps, int reason);
    void GenerateErrors(ECLPS* ps, ECLErr* e);
    friend class ECLScreenNotify;

public:
    ECLScreenReco();
    ~ECLScreenReco();

    static BOOL IsMatch(ECLPS& ps, ECLScreenDesc& sd);                  
    static BOOL IsMatch(ECLPS* ps, ECLScreenDesc* sd);                  
    void RegisterScreen(ECLScreenDesc* sd, ECLRecoNotify* notify);
    void UnregisterScreen(ECLScreenDesc* sd, ECLRecoNotify* notify);    
    void AddPS(ECLPS* ps);
    void RemovePS(ECLPS* ps);
};

#endif
