//-------------------------------------------------------------------------------
// Module:  eclcinfo.hpp
//-------------------------------------------------------------------------------
//
// Description:  ECLConnection class header file.  Base class for all PCOMM 
//               session-specific objects (e.g. PS, OIA, etc).  Can also be 
//               used stand-alone to query the status of a particular host 
//               connection.
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
#ifndef _HSINFO_HPP_
#define _HSINFO_HPP_

#define ENCRYPTION_NONE       0x00                                         
#define ENCRYPTION_NOKEY      0x01                                         
#define ENCRYPTION_40BIT      0x02                                         
#define ENCRYPTION_56BIT      0x04                                         
#define ENCRYPTION_128BIT     0x08                                         
#define ENCRYPTION_168BIT     0x10                                         

class ECLConnData;                          // Forward declaration 
class DllExport ECLConnection: public ECLBase
{

  private: // Class private data
    ECLConnData *ConnPd;                


  private: // Constructors and operators not allowed on this object
    ECLConnection();
    ECLConnection(const ECLConnection &From);
    ECLConnection& operator= (const ECLConnection &From);

  public:

    ECLConnection(long ConnHandle);         // Construct from connection handle
    ECLConnection(char ConnName);           // Construct from connection name
    ~ECLConnection();

    // Information functions
    long  GetHandle() const;                // Connection handle
    int   GetConnType() const;              // Connection type (HOSTTYPE_* constant)
    char  GetName() const;                  // EHLLAPI short name
    unsigned int GetCodePage() const;       // Connection code page
    BOOL  IsStarted() const;                // Connection is running?
    BOOL  IsCommStarted() const;            // Connection connected to a host?
    BOOL  IsAPIEnabled() const;             // Connection is enabled for APIs?
    BOOL  IsReady() const;                  // Started & CommStarted & APIEnabled?
    BOOL  IsDBCSHost() const;               // Host code page is known DBCS code page

    // Communications functions
    void StartCommunication();              // Start communications with host
    void StopCommunication();               // Stop communications with host
    void RegisterCommEvent(ECLCommNotify *CommNotifyClass, BOOL InitEvent=TRUE);
    void UnregisterCommEvent(ECLCommNotify *CommNotifyClass);
    int GetEncryptionLevel()const;                                         
};

typedef ECLConnection * PECLConnection;

#endif //_HSINFO_HPP_
