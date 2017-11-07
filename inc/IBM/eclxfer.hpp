//-------------------------------------------------------------------------------
// Module:  eclxfer.hpp
//-------------------------------------------------------------------------------
//
// Description:  Declaration of the ECLXfer class
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
#ifndef _ECLXFER_HPP_
#define _ECLXFER_HPP_

//#include "eclbase.hpp"                                                         
//#include "eclcinfo.hpp"                                                        

class ECLXferData;                              // Foreward declaration 
class DllExport ECLXfer : public ECLConnection
{
  private: // Class private data
    ECLXferData   *pd;                          

  private: // Constructors and operators not allowed on this object
    ECLXfer();
    ECLXfer(const ECLXfer &From);
    ECLXfer& operator= (const ECLXfer &From);

  public:

    // Constructor/destructor
    ECLXfer(char ConnName);
    ECLXfer(long ConnHandle);
    ~ECLXfer();

    // ECLXfer methods
    int SendFile(const char * const LocalFileName,
                 const char * const HostFileName,
                 const char * const SendParms);

    int ReceiveFile(const char * const LocalFileName,
                    const char * const HostFileName,
                    const char * const RecvParms);

    void SetTimeout(int nTimeout);                                              // @w4a
	int  GetTimeout(void);                                                      // @w4a
	void SetClear(BOOL bClear);                                                 // @w4a
	BOOL IsClear(void);                                                         // @w4a
	void Cancel(void);                                                          // @w5a
};

typedef ECLXfer * PECLXfer;

#endif //_ECLXFER_HPP_
