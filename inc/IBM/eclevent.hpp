//-------------------------------------------------------------------------------
// Module:  eclevent.hpp
//-------------------------------------------------------------------------------
//
// Description:  ECLEvent classes header file.
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
#ifndef _ECLEVENT_HPP_
#define _ECLEVENT_HPP_

class ECLEventData;
class DllExport ECLEvent: public ECLBase
{

  private: // Class private data
    ECLEventData *pd;

  private: // Constructors and operators not allowed on this object
    ECLEvent();
    ECLEvent(void *);
    ECLEvent(const ECLEvent &From);
    ECLEvent& operator= (const ECLEvent &From);

  public:

    ~ECLEvent();                 // Destructor          

    void *      GetSource();

};

typedef ECLEvent * PECLEvent;

#endif //_ECLEVENT_HPP_
