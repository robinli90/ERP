/* begin_generated_IBM_copyright_prolog                             */
/*                                                                  */
/* This is an automatically generated copyright prolog.             */
/* After initializing,  DO NOT MODIFY OR MOVE                       */
/* ---------------------------------------------------------------- */
/* IBM Confidential                                                 */
/*                                                                  */
/* OCO Source Materials                                             */
/*                                                                  */
/* Product(s):                                                      */
/*     5722-XE1                                                     */
/*                                                                  */
/* (C)Copyright IBM Corp.  1995, 2005                               */
/*                                                                  */
/* The Source code for this program is not published  or otherwise  */
/* divested of its trade secrets,  irrespective of what has been    */
/* deposited with the U.S. Copyright Office.                        */
/*  --------------------------------------------------------------- */
/*                                                                  */
/* end_generated_IBM_copyright_prolog                               */

/*******************************************************************************
*
* File:
*   cwbsotif.h
*
* Purpose:
*   Define the attribute ids for the CTCPIPInterfaces subclass.
*
* CHANGE ACTIVITY:
*   This change flag section must follow a specific format to allow
*   the change flag utilities to count lines of code.  Each line
*   must have both comment delimiters.  All three special symbols
*   are required (dollar sign, equal sign and colon).
*
* Flg=Reason    Vers yymmdd UserID   Description
* ------------- ---- ------ ------   -----------
* $A0=P9A84250  5W4Y 041122 CESARROM:Alias name support
* $A1=P9A92018  5W4Y 050319 CESARROM:Alias name support corrections
*
******************************************************************************/

#ifndef _CWBSOTIF_H_
#define _CWBSOTIF_H_

/******************************************************************************
* Bring in common error codes and action codes
******************************************************************************/
#include "cwbsocmn.h"

/******************************************************************************
* Attribute ids
******************************************************************************/
#define CWBSO_TIF_TCPIPNetworkName               0x0000
#define CWBSO_TIF_InternetAddress                0x0001
#define CWBSO_TIF_BinaryInternetAddress          0x0002
#define CWBSO_TIF_SubnetMask                     0x0003
#define CWBSO_TIF_BinarySubnetMask               0x0004
#define CWBSO_TIF_AssociatedLocalInterface       0x0005
#define CWBSO_TIF_BinaryLocalIP                  0x0006
#define CWBSO_TIF_LineDescriptionName            0x0007
#define CWBSO_TIF_TypeOfLine                     0x0008
#define CWBSO_TIF_MaximumTransmissionUnit        0x0009
#define CWBSO_TIF_TypeOfService                  0x000a
#define CWBSO_TIF_AutomaticStart                 0x000b
#define CWBSO_TIF_TokenRingBitSequence           0x000c
#define CWBSO_TIF_Status                         0x000d
#define CWBSO_TIF_InterfaceName                  0x000e
#define CWBSO_TIF_PPPProfile                     0x000f
#define CWBSO_TIF_PPPRemoteIP                    0x0010
#define CWBSO_TIF_ApplicationDefined             0x0011 //@A1C
#define CWBSO_TIF_AllowProxyARP                  0x0012 //@A1C
#define CWBSO_TIF_AliasName						 0x0013 //@A0A
#define CWBSO_TIF_AliasNameCCSID                 0x0014 //@A0A

#define CWBSO_TIF_LastAttribute                  0x0014 //@A0C

#endif
