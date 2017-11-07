//-------------------------------------------------------------------------------
// Module:  eclnotfy.hpp
//-------------------------------------------------------------------------------
//
// Description:  ECL event class header file.  
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
#ifndef _ECLNOTIFY_HPP_
#define _ECLNOTIFY_HPP_

//#include "eclbase.hpp"                      // Need ECLBase class definitions  
//#include "eclerr.hpp"                       // ECLErr object                   

//----------------- Enumerations ------------------
enum UPDATETYPE 
{ 
  PSUpdate = 'P',                            // Just PS update
  OIAUpdate = 'O',                           // Just OIA update
  PSOIAUpdate = 'B',                         // PS and OIA update
  CursorUpdate = 'C',                        // Cursor update            
  CursorPSUpdate = 'Q',                      // Cursor and PS update     
  CursorOIAUpdate = 'R',                     // Cursor and OIA update    
  CursorPSOIAUpdate = 'S'                    // Cursor, PS and OIA update
};


//-------------------------------------------------------------------------------
// Base class for all ECL event classes.
//-------------------------------------------------------------------------------
class DllExport ECLNotify: public ECLBase
{

  public:
    ECLNotify();
    ~ECLNotify();

};


//-------------------------------------------------------------------------------
// Keystroke event class (implemented by user application).  User application
// must implement all functions.  Register an object of this class with the
// ECLPS object to be notified of keystrokes.
//-------------------------------------------------------------------------------
class DllExport ECLKeyNotify: public ECLNotify
{

  public:
    ECLKeyNotify();
    ~ECLKeyNotify();

    // Pure virtual functions all derived classes must implement
    virtual int  NotifyEvent (ECLPS *PSObj, char const KeyType[2], const char * const KeyString) = 0;

    // Virtual functions derived classes can override
    virtual void NotifyError (ECLPS *PSObj, ECLErr ErrObject); // Displays error message
    virtual void NotifyStop  (ECLPS *PSObj, int Reason); // Does nothing

};


//-------------------------------------------------------------------------------
// Dis/connect event class (implemented by user application).  User application
// must implement all functions.  Register an object of this class with the
// ECLConnection object to be notified of host communication connect/disconnects.
//-------------------------------------------------------------------------------
class DllExport ECLCommNotify: public ECLNotify
{

  public:
    ECLCommNotify();
    ~ECLCommNotify();

    // Pure virtual functions all derived classes must implement
    virtual void NotifyEvent (ECLConnection *ConnObj, BOOL Connected) = 0;

    // Virtual functions derived classes can override
    virtual void NotifyError (ECLConnection *ConnObj, ECLErr ErrObject); // Displays error message
    virtual void NotifyStop  (ECLConnection *ConnObj, int Reason); // Does nothing

};


//-------------------------------------------------------------------------------
// Session start/stop event class (implemented by user application).  User application
// must implement all functions.  Register an object of this class with the
// ECLConnMgr object to be notified of all connection start/stop events.
//-------------------------------------------------------------------------------
class DllExport ECLStartNotify: public ECLNotify
{

  public:
    ECLStartNotify();
    ~ECLStartNotify();

    // Pure virtual functions all derived classes must implement
    virtual void NotifyEvent (ECLConnMgr *CMObj, long ConnHandle, BOOL Started) = 0;

    // Virtual functions derived classes can override
    virtual void NotifyError (ECLConnMgr *CMObj, long ConnHandle, ECLErr ErrObject); // Displays error message
    virtual void NotifyStop  (ECLConnMgr *CMObj, int Reason); // Does nothing

};


// Events using ECLUpdateNotify are no longer supported
class DllExport ECLUpdateNotify: public ECLNotify
{
  public:
    ECLUpdateNotify();
    ~ECLUpdateNotify();

    // Pure virtual functions all derived classes must implement
    virtual void NotifyEvent (ECLSession *SessObj, UPDATETYPE Type) = 0;

    // Virtual functions derived classes can override
    virtual void NotifyError (ECLSession *SessObj, ECLErr ErrObject); // Displays error message
    virtual void NotifyStop  (ECLSession *SessObj, int Reason); // Does nothing

};

//-------------------------------------------------------------------------------
// Update event class for PS (implemented by user application).  User application
// must implement all functions.  Register an object of this class with the
// ECLPS object to be notified of PS updates.
//-------------------------------------------------------------------------------
class DllExport ECLPSNotify: public ECLNotify                             
{
  public:
    ECLPSNotify();                                                        
    ~ECLPSNotify();                                                       

    // Pure virtual functions all derived classes must implement
    virtual void NotifyEvent (ECLPS *Obj) = 0;

    // Virtual functions derived classes can override
    virtual void NotifyError (ECLPS *Obj, ECLErr ErrObject); // Displays error message
    virtual void NotifyStop  (ECLPS *Obj, int Reason); // Does nothing

};

//-------------------------------------------------------------------------------
// Update event class for OIA (implemented by user application).  User application
// must implement all functions.  Register an object of this class with the
// ECLPS object to be notified of PS updates.
//-------------------------------------------------------------------------------
class DllExport ECLOIANotify: public ECLNotify                             
{
  public:
    ECLOIANotify();                                                        
    ~ECLOIANotify();                                                       

    // Pure virtual functions all derived classes must implement
    virtual void NotifyEvent (ECLOIA *Obj) = 0;

    // Virtual functions derived classes can override
    virtual void NotifyError (ECLOIA *Obj, ECLErr ErrObject); // Displays error message
    virtual void NotifyStop  (ECLOIA *Obj, int Reason); // Does nothing

};

class ECLRecoNotify:public ECLNotify                                        
{
public:
    ECLRecoNotify(){}
    ~ECLRecoNotify(){}

    virtual void NotifyEvent(ECLPS* ps, ECLScreenDesc* sd) = 0;
    virtual void NotifyStop(ECLScreenDesc* sd, int reason){}            
    virtual void NotifyError(ECLPS* ps, ECLScreenDesc* sd, ECLErr* e){}
};

#endif // _ELCNOTIFY_HPP_

