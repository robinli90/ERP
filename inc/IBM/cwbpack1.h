/********************************************************************/
/*                                                                  */
/* 5722-XE1                                                         */
/* (C) Copyright IBM Corp. 1995,2002                                */
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
/*   CWBPACK1.H                                                     */
/*                                                                  */
/* Purpose:                                                         */
/*   This module is used to pack structures, and is to be used with */
/*   other cwbpack?.h files.                                        */
/*   See Usage Notes (below).                                       */
/*                                                                  */
/* Usage Notes:                                                     */
/*   //------------------------------------------------------------ */
/*   // structure to be packed on a 1 byte boundary                 */
/*   //------------------------------------------------------------ */
/*   #include "CWBPACK1.H"  // pack on 1-byte boundary              */
/*   struct a                                                       */
/*   {                                                              */
/*     char c1;                                                     */
/*     long w1;                                                     */
/*     char c2;                                                     */
/*   };                                                             */
/*   #include "CWBPACK0.H"  // restore to default                   */
/*                                                                  */
/********************************************************************/

#if defined (__IBMCPP__)  || defined(__IBMC__)
  #pragma pack(1)
#elif defined(__BCPLUSPLUS__) || defined(__BORLANDC__)
  #pragma option -a-
#elif defined (__MSC__) || defined(__GNUC__)
  #pragma pack(1)
#elif defined (__xlC__)
  #pragma options align=packed
#else
  #pragma pack(1)
//  #error Compiler is not recognized.  Please update this file.
#endif

