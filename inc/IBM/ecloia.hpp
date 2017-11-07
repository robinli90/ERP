//-------------------------------------------------------------------------------
// Module:  ecloia.hpp
//-------------------------------------------------------------------------------
//
// Description:  ECLOIA class definitions.
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
#ifndef _ECLOIA_HPP_
#define _ECLOIA_HPP_

#define    HL_OIA_SYSAPP_AVAILABLE                                3                    


// Enumeration for InputInhibited method
enum INHIBIT_REASON {
  NotInhibited   = 0,
  SystemWait     = 1,
  CommCheck      = 2,
  ProgCheck      = 3,
  MachCheck      = 4,
  OtherInhibit   = 5
};

// Definition of GetStatusFlags bit flags
const ULONG OIAFLAG_ALPHANUM =   0x80000000;
const ULONG OIAFLAG_APL      =   0x40000000;
const ULONG OIAFLAG_KATAKANA =   0x20000000;
const ULONG OIAFLAG_HIRAGANA =   0x10000000;
const ULONG OIAFLAG_DBCS     =   0x08000000;
const ULONG OIAFLAG_UPSHIFT  =   0x04000000;
const ULONG OIAFLAG_NUMERIC  =   0x02000000;  
const ULONG OIAFLAG_CAPSLOCK =   0x01000000;
const ULONG OIAFLAG_INSERT   =   0x00800000;
const ULONG OIAFLAG_COMMERR  =   0x00400000;
const ULONG OIAFLAG_MSGWAIT  =   0x00200000;
const ULONG OIAFLAG_ENCRYPTED =  0x00100000;  // SSL indicator          
const ULONG OIAFLAG_INHIBMASK=   0x0000000F;  // Mask for inhibit reason
const ULONG HODSTATE_SCREEN_REVERSE   = 0x00800000;
const ULONG HODSTATE_LANGUAGE_LAYER   = 0x01000000;
const ULONG HODSTATE_CURSOR_DIRECTION = 0x02000000;
const ULONG HODSTATE_AUTOREVERSE      = 0x04000000;
const ULONG HODSTATE_NUMFIELD         = 0x08000000;
const ULONG HODSTATE_AUTOPUSH         = 0x10000000;
const ULONG HODSTATE_AUTOSHAPE        = 0x20000000;
const ULONG HODSTATE_PUSH             = 0x40000000;

const ULONG HODSTATE_BASE       =  2;                     
const ULONG HODSTATE_CSD        =  1;                     
const ULONG HODSTATE_ISOLATED   =  2;
const ULONG HODSTATE_INITIAL    =  3;
const ULONG HODSTATE_MIDDLE     =  4;
const ULONG HODSTATE_FINAL      =  5;

// Definition for GetOwner return values @sm4
const int OIAOWNER_MYJOB = 1; 
const int OIAOWNER_NVT = 2; 
const int OIAOWNER_UNOWNED = 3; 
const int OIAOWNER_SSCP = 4; 
const int OIAOWNER_UNKNOWN = -1; 


class ECLOIAData;                           // Foreward declaration 
class DllExport ECLOIA : public ECLConnection
{
  private: // Class private data
    ECLOIAData   *pd;                           

  private: // Constructors and operators not allowed on this object
    ECLOIA();
    ECLOIA(const ECLOIA &From);
    ECLOIA& operator= (const ECLOIA &From);
    char operator[](BYTE nPos)const;                    

  public:

    // Constructor/destructor
    ECLOIA(char ConnName);
    ECLOIA(long ConnHandle);
    ~ECLOIA();

    // ECLOIA property access methods
    BOOL IsAlphanumeric() const;
    BOOL IsAPL() const;
    BOOL IsKatakana() const;
    BOOL IsHiragana() const;
    BOOL IsDBCS() const;
    BOOL IsUpperShift() const;
    BOOL IsNumeric() const;
    BOOL IsCapsLock() const;
    BOOL IsInsertMode() const;
    BOOL IsCommErrorReminder() const;
    BOOL IsMessageWaiting() const;
    INHIBIT_REASON InputInhibited() const;
    ULONG GetStatusFlags() const;
    ULONG GetBidiStatusFlags() const;                    

    // New methods in PComm Version 4.3
    void RegisterOIAEvent(ECLOIANotify *Observer, BOOL InitEvent=TRUE);
    void UnregisterOIAEvent(ECLOIANotify *Observer);
    // Implementation Not for documentation
    BOOL IsApplicationAvailable() const;                
    // Implementation Not for documentation
    BOOL IsSystemAvailable() const;                     
    BOOL WaitForInputReady(long nTimeOut = INFINITE);
    BOOL WaitForSystemAvailable(long nTimeOut = INFINITE);
    BOOL WaitForAppAvailable(long nTimeOut = INFINITE);
    BOOL WaitForTransition(BYTE nIndex = HL_OIA_SYSAPP_AVAILABLE, long nTimeOut = INFINITE);
    // Implementation Not for documentation
    void CancelWait();                                                  

  protected:
    // Implementation Not for documentation
    HANDLE m_hWaitEvent;                                                
    // Implementation Not for documentation
    BOOL DoWait(ULONG nTrigger, BYTE nIndex = 0xFF, 
        long nTimeOut = INFINITE);
    // Implementation Not for documentation
    char GetCharAt(BYTE nPos) const;                    

  // Methods for status codes
  public:
    // Implementation Not for documentation
    int GetProgCheckCode() const;         
    int GetCommCheckCode() const;         
    int GetMachineCheckCode() const;      
    int GetCommRemindCode() const;        

    // Implementation Not for documentation
    int GetOwner() const;		  

    // Implementation Not for documentation
    friend class OIAWaitNotify;
};

typedef ECLOIA * PECLOIA;

// Implementation Not for documentation
class OIAWaitNotify:public ECLOIANotify
{
protected:
    ECLOIA* m_pOIA;
    BOOL m_bCondMet;
    ULONG m_nTrigger;
    char m_cPosValue;
    BYTE m_nPosToWatch;
    HANDLE m_hEvent;

public:
    OIAWaitNotify(ECLOIA* OIAObj, ULONG nTrigger, BYTE nPos = 0xFF);
    ~OIAWaitNotify();                                   

    void NotifyEvent(ECLOIA* OIAObj);
    void NotifyStop(ECLOIA* OIAObj, int Reason);
    void NotifyError(ECLOIA* OIAObj, ECLErr ErrObj);

    HANDLE GetEvent(){return m_hEvent;}
    BOOL   IsCondMet(){return m_bCondMet;}
};

#endif //_ECLOIA_HPP_
