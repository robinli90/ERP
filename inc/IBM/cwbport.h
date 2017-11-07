/********************************************************************/
/*                                                                  */
/* 5722-XE1                                                         */
/* (C) Copyright IBM Corp. 1995,2005                                */
/* All rights reserved.                                             */
/* US Government Users Restricted Rights -                          */
/* Use, duplication or disclosure restricted                        */
/* by GSA ADP Schedule Contract with IBM Corp.                      */
/*                                                                  */
/* Licensed Materials-Property of IBM                               */
/*                                                                  */
/********************************************************************/
/*                                                                  */
/* Module:                                                          */
/*   CWBPORT.H                                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   This module helps with portability among C and C++ compilers.  */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use the keywords defined below to help enable porting from one */
/*   compiler to another.                                           */
/*                                                                  */
/*   Follow this example to pack structures for most compilers.     */
/*                                                                  */
/*     #include "cwbpack1.h"                                        */
/*      struct a                                                    */
/*      {                                                           */
/*        char a1;                                                  */
/*        char a2;                                                  */
/*      };                                                          */
/*     #include "cwbpack0.h"                                        */
/*                                                                  */
/********************************************************************/

/* Prevent multiple includes */
#if !defined( _CWBPORT_H_ )
  #define     _CWBPORT_H_

/*********************************************************************

   IBM C Set++

   The following are mainfest constants defined for IBM C Set++
   (names marked with * appear in more than one compiler)
   * __cplusplus     defined for C++ compilation
   * __DATE__        defined as the date of compilation
   * __DLL__         defined when compiling for DLLs
   * __FILE__        defined as the current source file
   * __LINE__        defined as the current line in the current file
   * __OS2__         defined when compiling for OS/2
   * __STDC__        defined when compiling using ANSI C
   * __TIME__        defined as the time of compilation

     _CHAR_UNSIGNED default character type is unsigned.
     _CHAR_SIGNED   default character type is signed.
     __COMPAT__     language constructs compatible with earlier versions
     __DBCS__       DBCS support is enabled.
     __DDNAMES__    ddnames are supported.
     __FUNCTION__   the name of the function currently being compiled.
     __IBMC__       the version number of the C/C++ Tools C compiler.
     __IBMCPP__     the version number of the C/C++ Tools C++ compiler.
     _M_I386        code is being compiled for a 386 chip or higher.
     __MULTI__      multithread code is being generated. (See __MT__)
     __SPC__        the subsystem libraries are being used.
     __TEMPINC__    the template-implementation file method of
                    resolving template
     __TILED__      tiled memory is being used.
     __32BIT__      the product is a 32-bit compiler.
     __TIMESTAMP__  the date and time when the source file was last
                    modified.
     __ANSI__       Allows only language constructs that conform
                    to ANSI C standard
     __SAA__        Allows only language constructs that conform
                    to the most recent level of SAA C standards.
     __SAAL2__      Allows only language constructs that conform
                    to SAA Level 2 C standards.
     __EXTENDED__   Allows additional language constructs provided
                    by the implementation.

   The following are keywords valid within IBM C Set++

     _Seg16     Segmented pointer (syntax= "* _Seg16")
     _Export    Export the class or function from a DLL
     _Optlink   IBM C/C++ Tools default linkage
     _System    OS/2 system linkage
     _Pascal    pascal linkage
     _Far16     16-bit linkage (use with _Pascal, _Cdecl, ...)
     _Far32     32-bit linkage (use with _Pascal, _Cdecl, ...)
     _Cdecl
     _Inline
     _Fastcall

*********************************************************************/

#if defined( __IBMC__ ) || defined( __IBMCPP__ )
  #if defined( __MULTI__ )
    #define __MT__
  #endif

  #define __export _Export
  #define  _export _Export
  #define __pascal _Pascal
  #define  _pascal _Pascal
  #define _syscall EXPENTRY

  #if ! defined( CwbExport )
    #define CwbExport   __declspec( dllexport )
  #endif
  #if ! defined( CwbImport )
    #define CwbImport   __declspec( dllimport )
  #endif

  #define SEG16PTR * _Seg16

#endif
/*********************************************************************

 IBM C Set++ for AIX/6000

 The following are mainfest constants defined for IBM C Set++
 (names marked with * appear in more than one compiler)

   __xlC__         defined when compiling for AIX
 * __cplusplus     defined for C++ compilation
 * __DATE__        defined as the date of compilation
 * __FILE__        defined as the current source file
 * __LINE__        defined as the current line in the current file
 * __STDC__        defined when compiling using ANSI C
 * __TIME__        defined as the time of compilation

   _CHAR_UNSIGNED default character type is unsigned.
   _CHAR_SIGNED   default character type is signed.
   __COMPAT__     language constructs compatible with earlier versions
   __DBCS__       DBCS support is enabled.
   __DDNAMES__    ddnames are supported.
   __FUNCTION__   the name of the function currently being compiled.
   __IBMC__       the version number of the C/C++ Tools C compiler.
   __IBMCPP__     the version number of the C/C++ Tools C++ compiler.
   _M_I386        code is being compiled for a 386 chip or higher.
   __MULTI__      multithread code is being generated. (See __MT__)
   __SPC__        the subsystem libraries are being used.
   __TEMPINC__    the template-implementation file method of
                  resolving templates
   __TILED__      tiled memory is being used.
   __32BIT__      the product is a 32-bit compiler.
   __TIMESTAMP__  the date and time when the source file was last modified.
   __ANSI__       Allows only language constructs that conform
                  to ANSI C standards.
   __SAA__        Allows only language constructs that conform
                  to the most recent level of SAA C standards.
   __SAAL2__      Allows only language constructs that conform
                  to SAA Level 2 C standards.
   __EXTENDED__   Allows additional language constructs provided
                  by the implementation.

 The following are keywords valid within IBM C Set++


   _Seg16     Segmented pointer (syntax= "* _Seg16")
   _Export    Export the class or function from a DLL
   _Optlink   IBM C/C++ Tools default linkage
   _System    OS/2 system linkage
   _Pascal    pascal linkage
   _Far16     16-bit linkage (use with _Pascal, _Cdecl, ...)
   _Far32     32-bit linkage (use with _Pascal, _Cdecl, ...)
   _Cdecl
   _Inline
   _Fastcall

*********************************************************************/

#if defined( __xlC__ )

/*  if multi-threaded capability
  #define __MT__
  endif  */

  #define _Pascal
  #define _Export
  #define _Far16

  #define __export _Export
  #define  _export _Export
  #define __pascal _Pascal
  #define  _pascal _Pascal
  #define _syscall EXPENTRY

  #define SEG16PTR *

#endif

/********************************************************************

  Borland C++ for OS/2


  The following are mainfest constants defined for Borland's products
  (names marked with * appear in more than one compiler)

  * __cplusplus     defined for C++ compilation
  * __DATE__        defined as the date of compilation
  * __DLL__         defined when compiling for DLLs
  * __FILE__        defined as the current source file
  * __LINE__        defined as the current line in the current file
  * __OS2__         defined when compiling for OS/2
  * __STDC__        defined when compiling using ANSI C
  * __TIME__        defined as the time of compilation

    __BCPLUSPLUS__  defined for Borland C++ compilation
    __BORLANDC__    defined for Borland C or Borland C++ compilation
    __CDECL__       defined when compiling for C calling convention
    __MT__          defined for multi-threaded compilation
    __PASCAL__      defined when compiling for PASCAL calling convention
    __TCPLUSPLUS__  defined for Borland C++ compilation
    __TEMPLATES__   defined if C++ templates are supported
    __TURBOC__      defined for Borland C or Borland C++ compilation

  The following are keywords valid within Borland's products
  (all have both one-underscore and two-underscore forms)
    __asm
    __cdecl
    __export
    __far16
    __fastcall
    __pascal
    __stdcall
    __syscall

*********************************************************************/

#if defined( __BORLANDC__ )
  #if defined( __MT__ )
    #define __MULTI__
  #endif
  #if defined( __OS2__ )
    #define __32BIT__
    #define _Export   __export
    #define _System   __syscall
    #define _RTLENTRY __stdcall
    #define _Cdecl    _RTLENTRY
    #define _Far16    __far16
    #define _Pascal   __pascal
    #define _Seg16    __far16
    /* _Seg16  keyword follows  the '*' as in 'char * _Seg16 ptr;'
     __far16 keyword precedes the '*' as in 'char __far16 * ptr;'
     so this may not be adequate.  Use SEG16PTR instead. */
    #define SEG16PTR  __far16 *
    #define CM_PTR    __far16 *
    #define CM_ENTRY  extern void __far16 __pascal
    #define CM_INT32  signed int
  #endif /* __OS2__ */
 #endif /* __BCPLUSPLUS__  */

/********************************************************************

  Visual C++


  The following are mainfest constants defined for Microsoft's products

    __cplusplus     defined for C++ compilation
    __DATE__        defined as the date of compilation
    __FILE__        defined as the current source file
    __LINE__        defined as the current line in the current file
    __STDC__        defined when compiling using ANSI C
    __TIME__        defined as the time of compilation
        __TIMESTAMP__   defined as the last modification of current source

        _CHAR_UNSIGNED  defined when default char is unsigned
        _CPPUNWIND              defined when exception handling is enabled
    _DLL                        defined when compiling for multithreaded using DLL
        _M_IX86                 defined for processor target
        _MSC_VER                defined for Visual C++ compilation
        _MT                             defined when compiling for multithreaded
        _WIN32                  defined for Win32

  The following are keywords valid within Microsoft's products

*********************************************************************/

#if defined( _MSC_VER )
  #if defined( _MT )
    #define __MULTI__
  #endif
  #if defined( _WIN32 )
    #define __32BIT__
    #define _Export
        #if ! defined( CwbExport )
          #define CwbExport __declspec( dllexport )
        #endif
        #if ! defined( CwbImport )
          #define CwbImport __declspec( dllimport )
        #endif

    /* _System needs to be APIENTRY, but including windows.h causes
       the resource compiler (RC.EXE) because the include nesting
       level gets to deep (more than 10).  APIENTRY is defined to
       be WINAPI which is defined to be __stdcall (see windef.h),
       so I am directly doing the definition to __stdcall here. */
    #define _System __stdcall
    #define _RTLENTRY
    #define _Cdecl
    #define _Far16
    #define _Pascal
    #define _Seg16
    /* _Seg16  keyword follows  the '*' as in 'char * _Seg16 ptr;'
     __far16 keyword precedes the '*' as in 'char __far16 * ptr;'
     so this may not be adequate.  Use SEG16PTR instead. */
    #define SEG16PTR
  #endif /* _WIN32 */
#endif /* __MSC_VER */

/********************************************************************

  GNU C/C++


  The following are mainfest constants defined for the GNU compiler

    __cplusplus     defined for C++ compilation
    __DATE__        defined as the date of compilation
    __FILE__        defined as the current source file
    __LINE__        defined as the current line in the current file
    __STDC__        defined when compiling using ANSI C
    __TIME__        defined as the time of compilation

  The following are keywords valid within GNU

*********************************************************************/

#if defined( __GNUC__ )
    #define _Export
    #define CwbExport
    #define CwbImport

    #define __stdcall
    #define _System
    #define _RTLENTRY
    #define _Cdecl
    #define _Far16
    #define _Pascal
    #define _Seg16
    #define SEG16PTR
#endif /* __GNUC__ */

#endif /* _CWBPORT_H_ */

