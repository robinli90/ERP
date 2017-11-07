/*****************************************************************************/
/*                                                                           */
/*  Module Name     : HAPI_C.H                                               */
/*                                                                           */
/*  Description     : 16/32 Bit HLLAPI Structure, Return Codes and Routines  */
/*                                                                           */
/*  Copyright Notice: IBM Personal Communication/3270 Version 4.1            */
/*                    (C) COPYRIGHT IBM CORP. 1989,1996 - PROGRAM PROPERTY   */
/*                    OF IBM ALL RIGHTS RESERVED                             */
/*                                                                           */
/*****************************************************************************/
#undef __HLLAPI_32BIT_SUPPORT__
#undef __HLLAPI_16BIT_SUPPORT__

#   if (__IBMC__ >= 100 || __IBMCPP__ >=200 || __IBMCM2C__ == 12 || _LE_PPC || WIN32 || _WIN32)
    /* __IBMC__   >= 100    indicates  C Set/2 or C Set++   */
    /* __IBMCPP__           indicates  C Set++              */
    /* WIN32 || _WIN32      indicates  MSVC                 */
#   define __HLLAPI_32BIT_SUPPORT__

#     elif defined(__BORLANDC__)
      /* Borland C++ for OS/2 */
#     define __HLLAPI_32BIT_SUPPORT__

#       elif (_MSC_VER >= 600) || __IBMC__
        /* Microsoft C 6.0 or IBM C/2 */
#       define __HLLAPI_16BIT_SUPPORT__

#   else

/*
 * If we have gotten this far, a supported compiler has not been
 * recognized.  We will produce a syntax error on the next
 * line that should help the user identify the problem.
 */
INTENTIONAL_SYNTAX_ERROR hllapi_does_not_recognize_compiler();

#   endif


#if ( defined(__HLLAPI_32BIT_SUPPORT__) && \
      defined(__HLLAPI_16BIT_SUPPORT__) )
INTENTIONAL_SYNTAX_ERROR hllapi_error_processing_include_files();
#   endif


#    if defined(__HLLAPI_32BIT_SUPPORT__)
#      include "HAPI_C32.H"
#    endif

#   if defined(__HLLAPI_16BIT_SUPPORT__)
#     include "HAPI_C16.H"
#   endif
