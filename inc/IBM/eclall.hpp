//-------------------------------------------------------------------------------
// Module:  eclall.hpp
//-------------------------------------------------------------------------------
//
// Description:  Includes all Emulator Class Library header files.
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

#ifndef _ECLALL_HPP_
#define _ECLALL_HPP_

// PSListener event filters
#define HOST_EVENTS             0x10                                    
#define USER_EXPLICIT_EVENTS    0x20                                    
#define API_EVENTS              0x40                                    
#define USER_EVENTS API_EVENTS|USER_EXPLICIT_EVENTS                     
#define ALL_EVENTS  API_EVENTS|USER_EXPLICIT_EVENTS|HOST_EVENTS         

// Forward declaration of all classes
class   ECLBase;
class   ECLErr;
class   ECLConnMgr;
class   ECLConnList;
class   ECLFieldList;
class   ECLField;
class   ECLNotify;
class   ECLKeyNotify;
class   ECLStartNotify;
class   ECLCommNotify;
// Events using ECLUpdateNotify are no longer supported
class   ECLUpdateNotify;
class   ECLPSNotify;                                                            
class   ECLOIANotify;                                                           
class   ECLRecoNotify;                                                          
class   ECLListener;                                                            
class   ECLPSListener;                                                          
class   ECLEvent;                                                               
class   ECLPSEvent;                                                             
class   ECLConnection;
class   ECLSession;
class   ECLPS;
class   ECLOIA;
class   ECLWinMetrics;
class   ECLXfer;
class   ECLScreenDesc;                                                          
class   ECLScreenReco;                                                          
class   ECLPageSettings;                                                        
class   ECLPrinterSettings;                                                     

#include "eclbase.hpp"        // ECLBase class (base class for all ECL classes)
#include "eclevent.hpp"       // ECLEvent class                                 
#include "eclpsevt.hpp"       // ECLPSEvent class                               
#include "eclnotfy.hpp"       // ECLNotify class (ECL event classes)
#include "ecllistn.hpp"       // ECLListener class (ECL event classes)          
#include "eclcmgr.hpp"        // ECLConnMgr class (Connection Manager)
#include "eclclist.hpp"       // ECLConnList class (a collection of connections)
#include "eclcinfo.hpp"       // ECLConnection class (an ECL connection)
#include "eclps.hpp"          // ECLPS class (presentation space)
#include "ecloia.hpp"         // ECLOIA class (OIA area)
#include "eclwmet.hpp"        // ECLWinMetrics class (window metrics)
#include "eclxfer.hpp"        // ECLXfer class (file transfer)
#include "eclsess.hpp"        // ECLSession class (contains PS, OIA, WinMetrics, and Xfer objects)
#include "eclflist.hpp"       // ECLFieldList class (a collection of PS fields)
#include "eclfinfo.hpp"       // ECLField class (a PS field)
#include "eclerr.hpp"         // ECLErr class (error messages)
#include "errorids.hpp"       // ECL error defines
#include "eclscdsc.hpp"       // ECLScreenDesc Screen Desciption class          
#include "ECLScRec.hpp"       // ECLScreenReco Screen Recognition class         
#include "eclpgset.hpp"       // ECLPageSettings class                          
#include "eclprset.hpp"       // ECLPrinterSettings class                       


#endif //_ECLALL_HPP_

