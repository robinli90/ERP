//-------------------------------------------------------------------------------
// Module:  eclwmet.hpp
//-------------------------------------------------------------------------------
//
// Description:  Declaration of ECLWinMetrics class.  This object
//               represents the physical characteristics of an emulator window.
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
#ifndef _ECLWMET_HPP_
#define _ECLWMET_HPP_

//#include "eclbase.hpp"                                                         
//#include "eclcinfo.hpp"                                                        

class ECLWinMetData;                        // Foreward declaration 
class DllExport ECLWinMetrics : public ECLConnection
{
  private: // Class private data
    ECLWinMetData   *pd;                    

  private: // Constructors and operators not allowed on this object
    ECLWinMetrics();
    ECLWinMetrics(const ECLWinMetrics &From);
    ECLWinMetrics& operator= (const ECLWinMetrics &From);

  public:

    // Constructor/destructor
    ECLWinMetrics(char ConnName);         
    ECLWinMetrics(long ConnHandle);                            
    ~ECLWinMetrics();

    // ECLWinMetrics property access functions
    const char *GetWindowTitle() const;
    void  SetWindowTitle(const char * const NewTitle);             
    long  GetXpos() const;                    
    void  SetXpos(long XPos);                      
    long  GetYpos() const;                    
    void  SetYpos(long YPos);                      
    long  GetWidth() const;                   
    void  SetWidth(long Width);                     
    long  GetHeight() const;                  
    void  SetHeight(long Height);                    
    void  SetWindowRect(long XPos,  long YPos,  long Width,  long Height);                    
    void  GetWindowRect(long *XPos, long *YPos, long *Width, long *Height) const;                    
    BOOL  IsVisible() const;               
    void  SetVisible(BOOL MakeVisible);                   
    BOOL  IsActive() const;               
    void  SetActive(BOOL MakeActive);                   
    BOOL  IsMinimized() const;                   
    void  SetMinimized();                     
    BOOL  IsMaximized() const;                   
    void  SetMaximized();                     
    BOOL  IsRestored() const;                   
    void  SetRestored();                     
};

typedef ECLWinMetrics * PECLWinMetrics;

#endif //_ECLWMET_HPP_
