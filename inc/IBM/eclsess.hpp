//-------------------------------------------------------------------------------
// Module:  eclsess.hpp
//-------------------------------------------------------------------------------
//
// Description:  Declaration of ECLSession class 
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
#ifndef _ECLSESS_HPP_
#define _ECLSESS_HPP_

class ECLSessionData;                       // Forward declarations

class DllExport ECLSession : public ECLConnection
{

  private: // Class private data
    ECLSessionData   *pd;                    

  private: // Constructors and operators not allowed on this object
    ECLSession();
    ECLSession(const ECLSession &From);
    ECLSession& operator= (const ECLSession &From);

  public:
    // Constructor/destructor
    ECLSession(char ConnName);
    ECLSession(long ConnHandle);
    ~ECLSession();

    // ECLSession property access methods
    ECLWinMetrics  *GetWinMetrics() const;
    ECLPS          *GetPS() const;
    ECLOIA         *GetOIA() const;
    ECLXfer        *GetXfer() const;
    ECLPageSettings *GetPageSettings() const;         
    ECLPrinterSettings *GetPrinterSettings() const;   

    // Events
    // These Events are no longer implemented and should not be used. These calls are deprecated
    void RegisterUpdateEvent(UPDATETYPE Type, ECLUpdateNotify *UpdateNotifyClass, BOOL InitEvent=TRUE);
    void UnregisterUpdateEvent(ECLUpdateNotify *UpdateNotifyClass);

};

typedef ECLSession * PECLSession;

#endif //_ECLSESS_HPP_
