//-------------------------------------------------------------------------------
// Module:  eclerr.hpp
//-------------------------------------------------------------------------------
//
// Description:  ECLErr class definitions.
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
#ifndef _ECLERR_HPP_
#define _ECLERR_HPP_

class ECLErrData;                          // Forward declaration 
class DllExport ECLErr : public ECLBase
{
  private: // Class private data
    ECLErrData *pd;                       // Class private data 

  public:

    // Constructor/destructor
    ECLErr();                                 // Default constructor
    ECLErr(const ECLErr &From);               // Copy constructor  
    ECLErr& operator= (const ECLErr &From);   // Assignment operator
    ~ECLErr();                                // Destructor

    // ECLErr access functions
    const int GetMsgNumber() const;
    const int GetReasonCode() const;
    const char *GetMsgText();
};

typedef ECLErr * PECLErr;

#endif //_ECLERR_HPP_
