//-------------------------------------------------------------------------------
// Module:  eclcmgr.hpp
//-------------------------------------------------------------------------------
//
// Description:  ECLConnMgr class definition.  This class is used to manage the 
//               connections on a given system.  It provides connection 
//               management routines such as start/stop connection. The 
//               ECLConnMgr maintains a list of available connections on a system 
//               (ECLConnList).  The list is initialized at construction and can 
//               be refreshed explicitly using the refresh method on the 
//               ECLConnList class.  The list is a static snapshot of the 
//               available sessions at the time of the snapshot.
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
#ifndef _ECLCMGR_HPP_
#define _ECLCMGR_HPP_

//#include "eclbase.hpp"                      // ECLBase class definition        
//#include "eclclist.hpp"                     // ECLConnList class definition    
//#include "eclnotfy.hpp"                     // Notify event stuff              
//#include "errorids.hpp"                     // Error stuff                     
//#include "eclerr.hpp"                       // ECLErr class definitions        


class ECLConnMgrData;                       // Forward declaration 
class DllExport ECLConnMgr: public ECLBase
{

  private: // Class private data
    ECLConnMgrData *pd;                     

  private: // Constructors and operators not allowed on this object
    ECLConnMgr(const ECLConnMgr &From);
    ECLConnMgr& operator= (const ECLConnMgr &From);

  public:
    ECLConnMgr();                           // Constructor
    ~ECLConnMgr();                          // Destructor

    ECLConnList *GetConnList() const;       // Get the HostList object 

                                            // Start a new session
    void StartConnection(const char * const ConfigParms);

                                            // Stop a session
    void StopConnection(ULONG ConnHandle, const char * const StopParms);

                                            // Session start/stop event notification
    void RegisterStartEvent(ECLStartNotify *AppNotifyClass);
    void UnregisterStartEvent(ECLStartNotify *AppNotifyClass);

};

typedef ECLConnMgr * PECLConnMgr;

#endif // _ECLCMGR_HPP_
