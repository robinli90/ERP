//-------------------------------------------------------------------------------
// Module:  eclopsys.hpp
//-------------------------------------------------------------------------------
//
// Description:  Operating system compatibility definitions and macros.  Allows
//               common ECL header files across platforms.
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
#if !defined(ECLOPSYS_INCLUDED)
#define ECLOPSYS_INCLUDED

#if defined(__OS2__)  // OS/2 compiler?
  #define OS2
#else         
  #define WIN
#endif

// Load operating system headers

#if defined(WIN)
  #include <windows.h>
#endif

#if defined(OS2)
  #define INCL_DOSMODULEMGR
  #define INCL_DOSERRORS
  #include <os2.h>
#endif

#endif // ECLOPSYS_INCLUDED
