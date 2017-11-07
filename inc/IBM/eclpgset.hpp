//-------------------------------------------------------------------------------
// Module:  eclpgset.hpp
//-------------------------------------------------------------------------------
//
// Description:  Declaration of ECLPageSettings class.  This object
//               represents the Page Setup Dialog of the emulator window.
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
#ifndef _ECLPGSET_HPP_
#define _ECLPGSET_HPP_

//Definition for SetCPI method
const ULONG FONT_CPI = 0;

//Definition for SetLPI method
const ULONG FONT_LPI = 0;

//Flag(s) to be used for RestoreDefaults method.
const ULONG PAGE_TEXT = 0x00000001;

class ECLPgSetData;                        // Forward declaration
class DllExport ECLPageSettings : public ECLConnection
{
  private: // Class private data
    ECLPgSetData *pd;

  private: // Constructors and operators not allowed on this object
    ECLPageSettings();
    ECLPageSettings(const ECLPageSettings &From);
    ECLPageSettings& operator= (const ECLPageSettings &From);

  public:

    // Constructor/destructor
    ECLPageSettings(char ConnName);
    ECLPageSettings(long ConnHandle);
    ~ECLPageSettings();

    // ECLPageSettings property access functions
    void  SetCPI(ULONG CPI=FONT_CPI);
    ULONG GetCPI() const;
    BOOL  IsFontCPI();
    void  SetLPI(ULONG LPI=FONT_LPI);
    ULONG GetLPI() const;
    BOOL  IsFontLPI();
    void  SetFontFaceName(const char* const FaceName);
    const char *GetFontFaceName() const;
    void  SetFontSize(ULONG FontSize);
    ULONG GetFontSize();
    void  SetMaxLinesPerPage(ULONG MPL);
    ULONG GetMaxLinesPerPage() const;
    void  SetMaxCharsPerLine(ULONG MPP);
    ULONG GetMaxCharsPerLine() const;
    void  RestoreDefaults(ULONG Tabs=PAGE_TEXT) const;
};

typedef ECLPageSettings * PECLPageSettings;

#endif //_ECLPGSET_HPP_

