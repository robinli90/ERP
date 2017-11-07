//-------------------------------------------------------------------------------
// Module:  eclps.hpp
//-------------------------------------------------------------------------------
//
// Description:  ECLPS class header file
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
#ifndef _CHOSTPS_HPP_
#define _CHOSTPS_HPP_


#define  PS_WAIT_FOR_STRING           0x00000000                          
#define  PS_WAIT_WHILE_STRING         0x00000001                          
#define  PS_WAIT_FOR_FATTR            0x00000002                          
#define  PS_WAIT_WHILE_FATTR          0x00000003                          
#define  PS_WAIT_FOR_CURSOR           0x00000004                          
#define  PS_WAIT_WHILE_CURSOR         0x00000005                          
#define  PS_WAIT_FOR_STRING_IN_RECT   0x00000006                          
#define  PS_WAIT_WHILE_STRING_IN_RECT 0x00000007                          
#define  PS_WAIT_FOR_SCRDSC           0x00000008                          
#define  PS_WAIT_WHILE_SCRDSC         0x00000009                          

#define  FATTR_MDT                0x01                                   
#define  FATTR_PEN_MASK           0x0C                                   
#define  FATTR_BRIGHT             0x08                                   
#define  FATTR_DISPLAY            0x0C                                   
#define  FATTR_ALPHA              0x10                                   
#define  FATTR_NUMERIC            0x10                                   
#define  FATTR_PROTECTED          0x20                                   
#define  FATTR_PRESENT            0x80                                   

#define  FATTR_52_BRIGHT          0x10                                   
#define  FATTR_52_DISP            0x40                                   

#define  FATTR_52_MASK            0x0E                                   
                                            // 5250 Field attribute format:
                                            // 0000 xxx0  bit 4-6
                                            //
                                            // 000 = 0 = alpha shift
                                            // 001 = 1 = alpha only
                                            // 010 = 2 = numeric shift
                                            // 011 = 3 = numeric only
                                            // 100 = 4 = katakana shift
                                            // 101 = 5 = digits only
                                            // 110 = 6 = i/o - mag stripe
                                            // 111 = 7 = signed numeric
#define  DBCS_SO                  0x0E      

//------------------- Enumerations
enum PS_PLANE {                             // Presentation Space data planes
  NoPlane      = 0x00,                      // No data
  TextPlane    = 0x01,                      // Text plane (NULL terminated)
  ColorPlane   = 0x02,                      // Color plane
  FieldPlane   = 0x04,                      // Field attribute plane
  ExfieldPlane = 0x08,                      // Extended field (character) attribute plane
  DBCSPlane    = 0x10,                      // DBCS character plane
  GridPlane    = 0x20,                      // DBCS grid line plane
  AllPlanes    = 0x3F,                      // All planes
  HostPlane    = 0x80                       // Raw EBCDIC Data. Host Plane has specific usage and is not included in All Planes
};                                                                               

typedef struct tagRect
{
   ULONG Left;
   ULONG Top;
   ULONG Right;
   ULONG Bottom;
}ECLRECT;

enum PS_DIR {                               // Search direction                  
  SrchForward,                              // Search forward                    
  SrchBackward                              // Search backward                   
};
class ECLPSData;                            // Foreward declaration 
class DllExport ECLPS: public ECLConnection
{
  private: // Class private data
    ECLPSData   *pd;                            

  private: // Constructors and operators not allowed on this object
    ECLPS();
    ECLPS(const ECLPS &From);
    ECLPS& operator= (const ECLPS &From);

  public:

    // Constructor/destructor
    ECLPS(char ConnName);
    ECLPS(long ConnHandle);
    ECLPS& operator= (const char * const String);  // String assignment
    ECLPS& operator= (const LONG Value);           // Numeric assignment
    ~ECLPS();

    ULONG GetSize() const;
    ULONG GetSizeRows() const;
    ULONG GetSizeCols() const;
    void  GetSize(ULONG * Row, ULONG * Col) const;

    ULONG GetCursorPos() const;
    ULONG GetCursorPosRow() const;
    ULONG GetCursorPosCol() const;
    void  GetCursorPos(ULONG * Row, ULONG * Col) const;

    void  SetCursorPos(ULONG Pos);
    int   SetBIDICursorPos(ULONG Pos, int flag);             
    void  SetCursorPos(ULONG Row, ULONG Col);

    void  SendKeys(const char * const text);
    void  SendKeys(const WCHAR* const text);                          
    void  SendKeys(const char * const text, ULONG AtPos);
    void  SendKeys(const WCHAR* const text, ULONG AtPos);             
    void  SendKeys(const char * const text, ULONG AtRow, ULONG AtCol);
    void  SendKeys(const WCHAR* const text, ULONG AtRow, ULONG AtCol);
    void  StartMacro(const char * const MacroName);

    ULONG SearchText(const char * const text, PS_DIR Dir=SrchForward, BOOL FoldCase=FALSE) const;
    ULONG SearchText(const WCHAR* const text, PS_DIR Dir=SrchForward, BOOL FoldCase=FALSE) const;                                  
    ULONG SearchText(const char * const text, ULONG StartPos, PS_DIR Dir=SrchForward, BOOL FoldCase=FALSE) const;
    ULONG SearchText(const WCHAR* const text, ULONG StartPos, PS_DIR Dir=SrchForward, BOOL FoldCase=FALSE) const;                  
    ULONG SearchTextLength(const char * const text, ULONG StartPos, ULONG length, PS_DIR Dir=SrchForward, BOOL FoldCase=FALSE) const; 
    ULONG SearchTextLength(const char * const text, ULONG StartRow, ULONG StartCol, ULONG length, PS_DIR Dir=SrchForward, BOOL FoldCase=FALSE) const; 
    ULONG SearchText(const char * const text, ULONG StartRow, ULONG StartCol, PS_DIR Dir=SrchForward, BOOL FoldCase=FALSE) const;
    ULONG SearchText(const WCHAR * const text, ULONG StartRow, ULONG StartCol, PS_DIR Dir=SrchForward, BOOL FoldCase=FALSE) const;  

    ULONG GetScreen(char * Buff, ULONG BuffLen, PS_PLANE Plane=TextPlane) const;
    ULONG GetScreen(WCHAR* Buff, ULONG BuffLen, PS_PLANE Plane=TextPlane) const;                                                   
    ULONG GetScreen(char * Buff, ULONG BuffLen, ULONG StartPos, ULONG Length, PS_PLANE Plane=TextPlane) const;
    ULONG GetScreen(WCHAR* Buff, ULONG BuffLen, ULONG StartPos, ULONG Length, PS_PLANE Plane=TextPlane) const;                     
    ULONG GetScreen(char * Buff, ULONG BuffLen, ULONG StartRow, ULONG StartCol, ULONG Length, PS_PLANE Plane=TextPlane) const;
    ULONG GetScreen(WCHAR* Buff, ULONG BuffLen, ULONG StartRow, ULONG StartCol, ULONG Length, PS_PLANE Plane=TextPlane) const;     
    ULONG GetScreenRect(char * Buff, ULONG BuffLen, ULONG StartPos, ULONG EndPos, PS_PLANE Plane=TextPlane) const;
    ULONG GetScreenRect(char * Buff, ULONG BuffLen, ULONG StartRow, ULONG StartCol, ULONG EndRow, ULONG EndCol, PS_PLANE Plane=TextPlane) const;

    // Implementation Not for documentation
    BOOL IsDataInPosition(const unsigned char* pTestData, ULONG nPos, PS_PLANE Plane=TextPlane, BOOL bString=TRUE, BOOL bCaseSensitive = TRUE,
        unsigned char cMask = 0xFF);                                    
    // Implementation Not for documentation
    BOOL IsDataInRect(const unsigned char* pTestData, ECLRECT Rect, PS_PLANE Plane, BOOL bString, BOOL bCaseSensitive); 

    void  SetText(const char * const text);                            
    void  SetText(const WCHAR* const text);                            
    void  SetText(const char * const text, ULONG AtPos);               
    void  SetText(const WCHAR* const text, ULONG AtPos);               
    void  SetText(const char * const text, ULONG AtRow, ULONG AtCol);  
    void  SetText(const WCHAR* const text, ULONG AtRow, ULONG AtCol);  

    ULONG ConvertPosToRow(ULONG Pos) const;
    ULONG ConvertPosToCol(ULONG Pos) const;
    void  ConvertPosToRowCol(ULONG Pos, ULONG * Row, ULONG * Col) const;
    ULONG ConvertRowColToPos(ULONG Row, ULONG Col) const;
    // Implementation Not for documentation
    ULONG ConvertRowColToPos(int Row, int Col) const;                   

    ECLFieldList *   GetFieldList() const;

    // Functions to register interest in various events
    void RegisterKeyEvent(ECLKeyNotify *NotifyObject);
    void UnregisterKeyEvent(ECLKeyNotify *NotifyObject);

    // New functions for PComm Version 4.3
    void RegisterPSEvent(ECLPSNotify *Observer, BOOL InitEvent=FALSE);  
    void UnregisterPSEvent(ECLPSNotify *Observer);                      
    void RegisterPSEvent(ECLPSListener *Listener, int Type = ALL_EVENTS, BOOL InitEvent=FALSE);
    BOOL UnregisterPSEvent(ECLPSListener *Listener, int Type = ALL_EVENTS);      

    BOOL WaitWhileCursor(int nRow, int nCol, long nTimeOut = INFINITE, BOOL bWaitForInput = TRUE);
    BOOL WaitForCursor(int nRow, int nCol, long nTimeOut = INFINITE, BOOL bWaitForInput = TRUE);
    BOOL WaitWhileString(const char* szWaitString, int nRow = 0, int nCol = 0, 
        long nTimeOut = INFINITE, BOOL bWaitForInput = TRUE, BOOL bCaseSensitive = TRUE);
    BOOL WaitForString(const char* szWaitString, int nRow = 0, int nCol = 0, 
        long nTimeOut = INFINITE, BOOL bWaitForInput = TRUE, BOOL bCaseSensitive = TRUE);
    BOOL WaitWhileAttrib(int nRow, int nCol, unsigned char cWaitData, unsigned char cMask = 0xFF, PS_PLANE Plane = FieldPlane, 
        long nTimeOut = INFINITE, BOOL bWaitForInput = TRUE);           
    BOOL WaitForAttrib(int nRow, int nCol, unsigned char cWaitData, unsigned char cMask = 0xFF, PS_PLANE Plane = FieldPlane, 
        long nTimeOut = INFINITE, BOOL bWaitForInput = TRUE);            
    BOOL WaitForStringInRect(const char* szWaitString, ULONG nTop, ULONG nLeft, 
               ULONG nBottom, ULONG nRight, long nTimeOut = INFINITE, BOOL bWaitForInput = TRUE, 
               BOOL bCaseSensitive = TRUE);                              
    BOOL WaitWhileStringInRect(const char* szWaitString, ULONG nTop, ULONG nLeft, 
               ULONG nBottom, ULONG nRight, long nTimeOut = INFINITE, BOOL bWaitForInput = TRUE, 
               BOOL bCaseSensitive = TRUE);                             
    BOOL WaitForScreen(ECLScreenDesc* pScrDesc, long nTimeOut);         
    BOOL WaitWhileScreen(ECLScreenDesc* pScrDesc, long nTimeOut);       

    void CancelWait();                                                  
    ECLFieldList *   CreateFieldList(PS_PLANE Plane) const;  // Create new ECLFieldList object 
    int  GetPCCodePage();                                               
    int  GetHostCodePage();                                             
    int  GetOSCodePage();                                               
    BOOL IsDBCS();                                                      
    ULONG  GetFieldText(ULONG pos, char *Buff, ULONG length) const;     


  protected:
    // Implementation Not for documentation
    HANDLE m_hWaitEvent;                                                
    // Implementation Not for documentation
    BOOL DoWait(ULONG nTrigger, int nRow1, int nCol1, const unsigned char* pWaitData1 = NULL, BOOL bCaseSensitive = TRUE, 
        BOOL bWaitForInput = TRUE, long nTimeOut = 0xFFFFFFFF, PS_PLANE Plane = TextPlane, unsigned char cMask = 0xFF);
    // Implementation Not for documentation
    BOOL DoWait(ULONG nTrigger, ECLRECT Rect, const unsigned char* pWaitData, BOOL bCaseSensitive, 
        BOOL bWaitForInput = TRUE, long nTimeOut = 0xFFFFFFFF, PS_PLANE Plane = TextPlane);
    // Implementation Not for documentation
    BOOL DoWait(ULONG nTrigger, ECLScreenDesc* pSD, long nTimeOut);     
    // Implementation Not for documentation
};

typedef ECLPS * PECLPS;

// Implementation Not for documentation
class PSWaitNotify:public ECLPSNotify                                   
{
protected:
    ECLPS* m_pPS;
    BOOL m_bCondMet;
    ULONG m_nTrigger;
    ULONG m_nWatchPos1;
    ECLRECT m_Rect;
    const unsigned char* m_pWatchData1;
    PS_PLANE m_Plane;
    BOOL m_bCaseSensitive;
    unsigned char m_cMask;                                              
    ECLScreenDesc* m_pSD;                                               

    HANDLE m_hEvent;

public:
    PSWaitNotify(ECLPS* pPSObj, ULONG nTrigger, ULONG nPos1, 
        const unsigned char* pWatchData, PS_PLANE Plane, BOOL m_bCaseSensitive, 
        unsigned char cMask = 0xFF);
    PSWaitNotify(ECLPS* pPSObj, ULONG nTrigger, ECLRECT Rect, 
        const unsigned char* pWatchData, PS_PLANE Plane, BOOL m_bCaseSensitive);

    PSWaitNotify(ECLPS* pPSObj, ULONG nTrigger, ECLScreenDesc* pSD);    

    ~PSWaitNotify();                                                    

    void NotifyEvent(ECLPS* PSObj);

    HANDLE GetEvent(){return m_hEvent;}
    BOOL   IsCondMet(){return m_bCondMet;}
};

#endif //_CHOSTPS_HPP_
