// SQLDelete.h
// 
// Revision Log
//
// Date       Who SAR     Notes
// ========== === ======= =====================================
// 1999-10-30 mph 00069   Initial coding
// 
//
#ifndef CSQLDELETE_H
#define CSQLDELETE_H

#include "SQLBaseWhere.h"

class CSQLDelete : public CSQLBaseWhere 
{
public:
   CSQLDelete();
   CSQLDelete( const char* table );
   CSQLDelete( CSQLDelete& o );
   ~CSQLDelete();

   std::string GetStatement();
};

#endif
