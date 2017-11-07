//-------------------------------------------------------------------------------
// Module:  errorids.hpp
//-------------------------------------------------------------------------------
//
// Description:  Emulator Class Library (ECL) internal error IDs and related 
//               macros.
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

#ifndef _ERRORIDS_HPP_
#define _ERRORIDS_HPP_

#define  IDS_STR_ECL_FIRST              37100                    
#define  IDS_STR_ECL_HLLAPI_ERR         (IDS_STR_ECL_FIRST)      // "ECL37100:  Emulator interface (EHLLAPI) error."
#define  IDS_STR_ECL_CHLLAPI_ERR        (IDS_STR_ECL_FIRST+10)   // "ECL37110:  Emulator interface initialization failed."
#define  IDS_STR_ECL_CHLLAPI_ERRLIB     (IDS_STR_ECL_FIRST+11)   // "  Emulator library not found."
#define  IDS_STR_ECL_CHLLAPI_ERRENTRY   (IDS_STR_ECL_FIRST+12)   // "  Emulator entry point not found."
#define  IDS_STR_ECL_CHLLAPI_ERRUNAVAIL (IDS_STR_ECL_FIRST+13)   // "  Emulator interface not available."
#define  IDS_STR_ECL_CHLLAPI_ERRSYS     (IDS_STR_ECL_FIRST+14)   // "  EHLLAPI system error"
#define  IDS_STR_ECL_SYSCALL_ERR        (IDS_STR_ECL_FIRST+20)   // "ECL37120:  System call failed. "
#define  IDS_STR_ECL_SYSCALL_ERRTHREAD  (IDS_STR_ECL_FIRST+21)   // "  _beginthread failure."
#define  IDS_STR_ECL_SYSCALL_ERRSEM     (IDS_STR_ECL_FIRST+22)   // "  Unexpected semaphore timeout."
#define  IDS_STR_ECL_SYSCALL_ERRCWIN    (IDS_STR_ECL_FIRST+23)   // "  CreateWindow failure."
#define  IDS_STR_ECL_SYSCALL_RWINMGS    (IDS_STR_ECL_FIRST+24)   // "  RegisterWindowMessage failure."
#define  IDS_STR_ECL_SYSCALL_RCLASS     (IDS_STR_ECL_FIRST+25)   // "  RegisterClass failure."
#define  IDS_STR_ECL_SESSION_ERR        (IDS_STR_ECL_FIRST+30)   // "ECL37130:  Invalid host session specified. "
#define  IDS_STR_ECL_SESSION_ERRBUSY    (IDS_STR_ECL_FIRST+40)   // "ECL37140:  Host session is busy or in use."
#define  IDS_STR_ECL_SESSION_ERRLOCKED  (IDS_STR_ECL_FIRST+50)   // "ECL37150:  Host session is locked."
#define  IDS_STR_ECL_MEMORY_ERR         (IDS_STR_ECL_FIRST+60)   // "ECL37160:  Out of memory or system resources. "
#define  IDS_STR_ECL_PARM_ERR           (IDS_STR_ECL_FIRST+70)   // "ECL37170:  Invalid parameters. "
#define  IDS_STR_ECL_PARM_ERRNULLPTR    (IDS_STR_ECL_FIRST+71)   // "  Null pointer."
#define  IDS_STR_ECL_PARM_ERRDATA       (IDS_STR_ECL_FIRST+72)   // "  Invalid data."
#define  IDS_STR_ECL_PARM_ERRBUFFSIZE   (IDS_STR_ECL_FIRST+73)   // "  Invalid buffer size."
#define  IDS_STR_ECL_PARM_ERRBADDELIM   (IDS_STR_ECL_FIRST+74)   // "  Unmatched keyword delimiters."
#define  IDS_STR_ECL_PARM_ERRBADKEYWD   (IDS_STR_ECL_FIRST+75)   // "  Invalid keyword."
#define  IDS_STR_ECL_INTERNAL_ERR       (IDS_STR_ECL_FIRST+80)   // "ECL37180:  Internal Emulator Class Library program error. "
#define  IDS_STR_ECL_REASON_CODE        (IDS_STR_ECL_FIRST+81)   // "   Reason code:"                                                                                                                  
#define  IDS_STR_ECL_SESS_ERRUNAVAIL    (IDS_STR_ECL_FIRST+90)   // "ECL37190:  The host session is not available.  It may be in use by another application or system function. "
#define  IDS_STR_ECL_EVENT_ERR          (IDS_STR_ECL_FIRST+100)  // "ECL37200:  Emulator Class Library event error"                                                              
#define  IDS_STR_ECL_EVENT_ERRREG       (IDS_STR_ECL_FIRST+110)  // "ECL37210:  A notify object is already registered for the event. "                                           
#define  IDS_STR_ECL_PS_ERRUNDEFKEY     (IDS_STR_ECL_FIRST+120)  // "ECL37220:  Undefined key was pressed (keystroke notify). "                                                  
#define  IDS_STR_ECL_PS_ERRKEYOVERFLOW  (IDS_STR_ECL_FIRST+130)  // "ECL37230:  Keystroke buffer overflow. "                                                                     
#define  IDS_STR_ECL_CMGR_INVPROFILE    (IDS_STR_ECL_FIRST+140)  // "ECL37240:  Invalid WS profile name. "                                                                       
#define  IDS_STR_AUTECL_SYSTEM_ERR      (IDS_STR_ECL_FIRST+170)  // "AUTECL:  A general system error has occurred."
#define  IDS_STR_AUTECL_SESS_ERRSET     (IDS_STR_ECL_FIRST+171)  // "AUTECL:  The session has already been set for this object.  You can set the session for an object instance only once."
#define  IDS_STR_AUTECL_SESS_ERRNOSET   (IDS_STR_ECL_FIRST+172)  // "AUTECL:  The session has not been set for this object.  You need to call SetConnectionByName or SetConnectionByHandle once for this object."
#define  IDS_STR_AUTECL_REG_ERR         (IDS_STR_ECL_FIRST+173)  // "AUTECL:  Couldn't get object from the registry."
#define  IDS_STR_AUTECL_PARM_ERRINPUT   (IDS_STR_ECL_FIRST+174)  // "AUTECL:  Invalid input parameter passed."
#define  IDS_STR_AUTECL_ITEM_ERRRET     (IDS_STR_ECL_FIRST+175)  // "AUTECL:  Item retrieval failed."
#define  IDS_STR_AUTECL_ITEM_ERRINDTYPE (IDS_STR_ECL_FIRST+176)  // "AUTECL:  Index type for item retrieval must be integer."
#define  IDS_STR_AUTECL_ITEM_ERRINDBND  (IDS_STR_ECL_FIRST+177)  // "AUTECL:  Index out of bounds."
#define  IDS_STR_AUTECL_COLL_ERRENUMCR  (IDS_STR_ECL_FIRST+178)  // "AUTECL:  Error creating enumerator."
#define  IDS_STR_AUTECL_COLL_ERRENUMSUP (IDS_STR_ECL_FIRST+179)  // "AUTECL:  Enumerator interface not supported."
#define  IDS_STR_AUTECL_COLL_ERRDEST    (IDS_STR_ECL_FIRST+180)  // "AUTECL:  Failed to destroy collection."
#define  IDS_STR_AUTECL_COLL_ERRINIT    (IDS_STR_ECL_FIRST+181)  // "AUTECL:  Failed to initialize collection."
#define  IDS_STR_AUTECL_COLL_ERRINITEV  (IDS_STR_ECL_FIRST+182)  // "AUTECL:  Failed to initiliaze event handling."
#define  IDS_STR_AUTECL_COLL_ERREVENT   (IDS_STR_ECL_FIRST+183)  // "AUTECL:  Event handler is in error."
#define  IDS_STR_LSXECL_PARM_ERR        (IDS_STR_ECL_FIRST+190)  // "LSXECL:  Bad parameter on method."
#define  IDS_STR_LSXECL_ATTR_ERRRO      (IDS_STR_ECL_FIRST+191)  // "LSXECL:  Attempt to set a read-only field."
#define  IDS_STR_AUTECL_SESS_EVNTSET    (IDS_STR_ECL_FIRST+192)  // "AUTECL:  Event has already been registered."  
//#define  IDS_STR_AUTECL_SESS_EVNTNOSET  (IDS_STR_ECL_FIRST+193)  // "AUTECL:  Event has not been registered."      

#endif //_ERRORIDS_HPP_
