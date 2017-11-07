//-------------------------------------------------------------------------------
// Module:  eclflist.hpp
//-------------------------------------------------------------------------------
//
// Description:  ECLFieldList class header file.
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
#ifndef _ECLFLIST_HPP_
#define _ECLFLIST_HPP_

//#include "eclbase.hpp"                                                         
//#include "eclps.hpp"                        // Need PS object definitions      
#define MODIFIED_FIELD           0x0001                                          
#define ALPHANUM_FIELD           0x0002                                          
#define HILIGHT_FIELD            0x0010                                          
#define PROTECTED_FIELD          0x0020                                          
#define DISPLAYABLE_FIELD        0x0040                                          
#define PENDETECTABLE_FIELD      0x0080                                          

#define UNMODIFIED_FIELD         0x0100                                          
#define NUMERIC_FIELD            0x0200                                          
#define LOLIGHT_FIELD            0x1000                                          
#define UNPROTECTED_FIELD        0x2000                                          
#define NON_DISPLAYABLE_FIELD    0x4000                                          
#define NON_PENDETECTABLE_FIELD  0x8000                                          

// Flags for field attributes in GetFirstField() and GetNextField().
// These can be logically OR-ed to get fields with only the specified
// set of attributes (e.g. "GetDisplay|GetUnprotected" would return
// ONLY the fields which are visible input fields -- e.g. meet all criteria
// specified by the set of bit flags).
const unsigned int GetAll         = 0x0000; // Get all fields

const unsigned int GetModified    = 0x0001;
const unsigned int GetHilight     = 0x0010;
const unsigned int GetProtected   = 0x0020;
const unsigned int GetDisplay     = 0x0040;

const unsigned int GetUnmodified  = 0x0100; // "Not" flags are shifted to upper byte
const unsigned int GetLolight     = 0x1000;
const unsigned int GetUnprotected = 0x2000;
const unsigned int GetNondisplay  = 0x4000;

class ECLFieldListData;                     // Forward declaration 
class DllExport ECLFieldList: public ECLBase
{

  private: // Class private data
    ECLFieldListData *pd;                    

  public:

    // Constructor/destructor -- note that a copy constructor and
    // assignment operator are define for this object.  See the
    // ECL documentation for proper usage.

    ECLFieldList();                          // Default constructor 
    ECLFieldList(const ECLFieldList &From);  // Copy constructor
    ECLFieldList& operator= (const ECLFieldList &From); // Assignment operator
    ~ECLFieldList();                 // Destructor          

    void        Refresh(PS_PLANE Planes=TextPlane);
    ULONG       GetFieldCount() const;
    ECLField    *GetFirstField(unsigned int Attrb = GetAll) const;
    ECLField    *GetNextField(ECLField *PrevField, unsigned int Attrib = GetAll) const;
    ECLField    *FindField(ULONG Pos) const;                           
    ECLField    *FindField(ULONG Row, ULONG Col) const;  
    ECLField    *FindField(const char * const text, PS_DIR Dir=SrchForward) const;                       
    ECLField    *FindField(const char * const text, ULONG Pos, PS_DIR Dir=SrchForward) const;            
    ECLField    *FindField(const char * const text, ULONG Row, ULONG Col, PS_DIR Dir=SrchForward) const; 
    void        Refresh(BOOL bShowZeroLengthFields, PS_PLANE Planes=TextPlane);
};

typedef ECLFieldList * PECLFieldList;

#endif //_ECLFLIST_HPP_
