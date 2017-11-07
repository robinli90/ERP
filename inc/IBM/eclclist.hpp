//-------------------------------------------------------------------------------
// Module:  eclclist.hpp
//-------------------------------------------------------------------------------
//
// Description:  ECLConnList class header file.  This class provides an 
//               enumeration of the currently available host sessions.  When 
//               created and when the Refresh() function is invoked, a snap-shot 
//               of the currently available sessions is made.  The connection 
//               list is not updated if connections are started or stopped.  When 
//               destroyed, all the ECLConnection objects created by this class 
//               are deleted.
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
#ifndef _ECLCLIST_HPP_
#define _ECLCLIST_HPP_

//#include "eclbase.hpp"                                                         
//#include "eclcinfo.hpp"                                                        

class ECLConnListData;                      // Forward declaration 
class DllExport ECLConnList: public ECLBase
{
  private: // Class private data
    ECLConnListData *pd;                    

  private: // Constructors and operators not allowed on this object
    ECLConnList(const ECLConnList &From);
    ECLConnList& operator= (const ECLConnList &From);

  public:
    ECLConnList();                          // Constructor
    ~ECLConnList();                         // Destructor

    ECLConnection *GetFirstConnection() const;    // Get first connection in the list; reset enumeration
    ECLConnection *GetNextConnection(ECLConnection *Prev) const; // Get next connection in the enumeration
    ECLConnection *FindConnection(long ConnHandle) const; // Find connection by handle
    ECLConnection *FindConnection(char ConnName) const; // Find connection by name
    ULONG GetCount() const;                       // Number of connections in the list
    void Refresh();                               // Get new list of connections and reset enumeration

};

typedef ECLConnList * PECLConnList;

#endif //_ECLCLIST_HPP_
