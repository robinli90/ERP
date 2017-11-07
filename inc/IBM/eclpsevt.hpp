//-------------------------------------------------------------------------------
// Module:  eclpsevt.hpp
//-------------------------------------------------------------------------------
//
// Description:  ECLPSEvent classes header file.
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
#ifndef _ECLPSEVENT_HPP_
#define _ECLPSEVENT_HPP_

class ECLPSEventData;
class HACLEventMgr;

class DllExport ECLPSEvent: public ECLEvent
{

  private: // Class private data
    ECLPSEventData *pd;

  private: // Constructors and operators not allowed on this object
    ECLPSEvent();
    ECLPSEvent(ECLPS *, int);
    ECLPSEvent(const ECLPSEvent &From);
    ECLPSEvent& operator= (const ECLPSEvent &From);

  public:

    ~ECLPSEvent();                 // Destructor          

    int         GetType();
    ECLPS *     GetPS();
    int         GetStart();
    int         GetStartRow();
    int         GetStartCol();
    int         GetEnd();
    int         GetEndRow();
    int         GetEndCol();
    BOOL        IsDirty();
};

typedef ECLPSEvent * PECLPSEvent;

#endif //_ECLPSEVENT_HPP_
