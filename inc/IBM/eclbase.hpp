//-------------------------------------------------------------------------------
// Module:  eclbase.hpp
//-------------------------------------------------------------------------------
//
// Description:  Base class for all ECL classes.  The members and methods defined 
//               in this class are available in any of the ECL classes.
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

#ifndef _ECLBASE_HPP_
#define _ECLBASE_HPP_

#include "eclopsys.hpp"

// Check for supported compiler and make compiler-specific mappings

#if defined(__IBMCPP__)  // IBM VisualAge C++
  #define DllExport   _Export
#elif defined(_MSC_VER)  // Microsoft Visual C++
  #define DllExport   __declspec( dllexport )
#else
  #error Unsupported compiler for the IBM Emulator Class Library.
#endif

#define HOSTTYPE_3270DISPLAY 'D'            // ECLConnection::GetConnType() values     
#define HOSTTYPE_3270PRINTER 'E'
#define HOSTTYPE_5250DISPLAY 'F'
#define HOSTTYPE_5250PRINTER 'G'
#define HOSTTYPE_VT          'H'
#define HOSTTYPE_PC          'P'            // ...obsolete "PC" session
#define HOSTTYPE_UNKNOWN     'U'            // Unknown, unable to query session

#define HOSTTYPE_MAXSTRLEN    20            // Max length required by ConvertTypeToString()

class ECLBaseData;                          // Forward declaration 
class DllExport ECLBase
{

  private: // Class private data
    ECLBaseData *pd;                        

  public:
    ECLBase();                              // Constructor
    ~ECLBase();                             // Destructor

    // ECL handle/shortname conversion
    char ConvertHandle2ShortName(long ConnHandle) const; // Convert numeric connection ID to EHLLAPI short name
    long ConvertShortName2Handle(char ShortName) const;  // Ditto, in reverse

    // Static utilities
    static int GetVersion(void);            // Get version number * 100 of ECL
    static void ConvertTypeToString(int ConnType, char *TypeString); // Convert type integer to descriptive string (non-NLS)

    // Handy inline function to get row/col from pos given #of cols in PS.
    // This is much faster then ECLPS::ConvertPosToRowCol() if the app 
    // already knows the number of columns in the PS.
    static inline void ConvertPos(ULONG Pos, ULONG *Row, ULONG *Col, ULONG PSCols) 
    {
      if(PSCols != 0)
      {
         *Col = ((Pos-1) % PSCols) + 1;        // Column number, 1-based
         *Row = (Pos / (PSCols));              // Row number, 1-based
         if (*Col != PSCols)                   // Not full line?
           (*Row)++;                           // Row number, 1-based
      }
      else
      {
         *Col = *Row = 0L;
      }
    }

};

typedef ECLBase * PECLBase;

#endif //_ECLBASE_HPP_
