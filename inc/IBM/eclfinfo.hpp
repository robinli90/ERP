//-------------------------------------------------------------------------------
// Module:  eclfinfo.hpp
//-------------------------------------------------------------------------------
//
// Description:  ECLField class header file
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
#ifndef _ECLFINFO_HPP_
#define _ECLFINFO_HPP_

//#include "eclbase.hpp"
//#include "eclps.hpp"                        // Need PS object
//#include "eclflist.hpp"                     // FieldList object

class ECLFieldData;                         // Forward declaration 
class DllExport ECLField: public ECLBase
{

  private: // Class private data
    ECLFieldData *pd;                        

  public:

    // Constructors/destructors -- note ECLField objects can be
    // copied and assigned (see documentation for proper usage
    // of copy construtors and assignment of ECLField objects).

    ECLField();                             // Default constructor
    ECLField(const ECLField &c);            // Copy constructor
    ECLField& operator= (const ECLField &From);      // ECLField assignment operator
    ECLField& operator= (const char * const String); // String assignment operator
    ECLField& operator= (const LONG Value);          // Numeric assignment operator

    ~ECLField();                            // Destructor

    // Field data access members
    ULONG            GetStart() const;            // field start position
    ULONG            GetStartRow() const;         // field start row
    ULONG            GetStartCol() const;         // field start col
    void             GetStart(ULONG *Row, ULONG *Col) const; // field start row/column
                                            
    ULONG            GetEnd() const;              // field end position
    ULONG            GetEndRow() const;           // field end row
    ULONG            GetEndCol() const;           // field end col
    void             GetEnd(ULONG *Row, ULONG *Col) const; // field end row/column

    ULONG            GetLength() const;           // field length

    // Only Text, ExtAttr, and Color planes are valid for GetScreen()
    ULONG            GetScreen(char *Buff, ULONG BuffLen, PS_PLANE Plane = TextPlane) const; // pointer to text, extfield, or color buffer
    ULONG            GetScreen(WCHAR *Buff, ULONG BuffLen, PS_PLANE Plane = TextPlane) const; // pointer to text, extfield, or color buffer for Unicode 
    void             SetText(const char * const text) const; // Erase field, set new text
    void             SetText(const WCHAR* const text) const; // Erase field, set new text

    BOOL             IsModified() const;          // field has been modified?
    BOOL             IsProtected() const;         // field is protected?
    BOOL             IsNumeric() const;           // field is numeric only?
    BOOL             IsHighIntensity() const;     // field is high intensity?
    BOOL             IsPenDetectable() const;     // field is pen detectable?
    BOOL             IsDisplay() const;           // field is displayable?
    unsigned char    GetAttribute() const;        // field attribute byte in raw form (see FATTR_* in ECLPS.HPP)

};

typedef ECLField * PECLField;

#endif //_ECLFINFO_HPP_
