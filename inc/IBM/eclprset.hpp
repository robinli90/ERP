//-------------------------------------------------------------------------------
// Module:  eclprset.hpp
//-------------------------------------------------------------------------------
//
// Description:  Declaration of ECLPrinterSettings class.  This object
//               represents the Printer Setup Dialog of the emulator window.
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
#ifndef _ECLPRSET_HPP_
#define _ECLPRSET_HPP_


class ECLPrtSetData;                        // Forward declaration
class DllExport ECLPrinterSettings : public ECLConnection
{
  private: // Class private data
    ECLPrtSetData *pd;

  private: // Constructors and operators not allowed on this object
    ECLPrinterSettings();
    ECLPrinterSettings(const ECLPrinterSettings &From);
    ECLPrinterSettings& operator= (const ECLPrinterSettings &From);

  public:

    // GetPrintMode returns one of the following enum constants.
    enum PrintMode
    { 
      PrtToDskAppend = 1,  // Print To Disk Append Mode
      PrtToDskSeparate,    // Print To Disk Separate Mode
      SpecificPrinter,     // Specific Printer Mode
      WinDefaultPrinter    // Windows Default Printer Mode
    };

  public:

    // Constructor/destructor
    ECLPrinterSettings(char ConnName);         
    ECLPrinterSettings(long ConnHandle);                            
    ~ECLPrinterSettings();

    // ECLPrinterSettings property access functions
    void SetPDTMode(BOOL PDTMode=TRUE, const char* const PDTFile = NULL);
    const char * GetPDTFile() const;
    BOOL IsPDTMode() const;
    ECLPrinterSettings::PrintMode GetPrintMode() const;
    void SetPrtToDskAppend(const char* const FileName = NULL);
    const char * GetPrtToDskAppendFile();
    void SetPrtToDskSeparate(const char* const FileName = NULL);
    const char *GetPrtToDskSeparateFile();
    void SetSpecificPrinter(const char* const PrinterName);    
    void SetWinDefaultPrinter();
    const char * GetPrinterName();
    void SetPromptDialog(BOOL Prompt=TRUE);
    BOOL IsPromptDialogEnabled();
};


typedef ECLPrinterSettings * PECLPrinterSettings;

#endif //_ECLPRSET_HPP_

