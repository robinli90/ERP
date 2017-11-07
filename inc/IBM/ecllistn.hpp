//-------------------------------------------------------------------------------
// Module:  ecllistn.hpp
//-------------------------------------------------------------------------------
//
// Description:  ECL listener classes header file.  
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
#ifndef _ECLLISTENER_HPP_
#define _ECLLISTENER_HPP_


//-------------------------------------------------------------------------------
// Base class for all ECL listener classes.
//-------------------------------------------------------------------------------
class DllExport ECLListener: public ECLBase
{

  public:
    ECLListener();
    ~ECLListener();

};

//-------------------------------------------------------------------------------
// PS Update listener class (implemented by user application).  User application
// must implement all functions.  Register an object of this class with the
// ECLPS object to be notified of PS updates.
//-------------------------------------------------------------------------------
class DllExport ECLPSListener: public ECLListener
{
  public:
    ECLPSListener();
    ~ECLPSListener();

    // Pure virtual functions all derived classes must implement
    virtual void PSNotifyEvent(ECLPSEvent *Event) = 0;
    virtual void PSNotifyError(ECLPS *Ps, ECLErr ErrObject) = 0;
    virtual void PSNotifyStop(ECLPS *Ps, int Reason) = 0;

};


#endif // _ELCLISTENER_HPP_

