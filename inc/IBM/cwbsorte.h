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
/* (C)Copyright IBM Corp.  2005, 2005                               */
/*                                                                  */
/* The Source code for this program is not published  or otherwise  */
/* divested of its trade secrets,  irrespective of what has been    */
/* deposited with the U.S. Copyright Office.                        */
/*  --------------------------------------------------------------- */
/*                                                                  */
/* end_generated_IBM_copyright_prolog                               */
/*******************************************************************************
* 5769-XE1                                                                  
* (C) Copyright IBM Corp. 1995,1998, 1999                                         
* All rights reserved.                                                      
* US Government Users Restricted Rights -                                   
* Use, duplication or disclosure restricted                                 
* by GSA ADP Schedule Contract with IBM Corp.                               
*                                                                           
* Licensed Materials-Property of IBM                                        
*                                                                           
*******************************************************************************
*******************************************************************************
*
* File:
*   cwbsorte.h
*
* Purpose:
*   Define the attribute ids for the CTCPIPRoutes subclass.
*
******************************************************************************/

#ifndef _CWBSORTE_H_
#define _CWBSORTE_H_

/******************************************************************************
* Bring in common error codes and action codes
******************************************************************************/
#include "cwbsocmn.h"

/******************************************************************************
* Attribute ids
******************************************************************************/
#define CWBSO_RTE_TCPIPNetworkName            0x0000
#define CWBSO_RTE_InternetAddress             0x0001
#define CWBSO_RTE_BinaryInternetAddress       0x0002
#define CWBSO_RTE_SubnetMask                  0x0003
#define CWBSO_RTE_BinarySubnetMask            0x0004
#define CWBSO_RTE_NextHopAddress              0x0005
#define CWBSO_RTE_BinaryNextHop               0x0006
#define CWBSO_RTE_BindingInterface            0x0007
#define CWBSO_RTE_BinaryBindingIP             0x0008
#define CWBSO_RTE_MaximumTransmissionUnit     0x0009
#define CWBSO_RTE_TypeOfService               0x000a
#define CWBSO_RTE_RoutePrecedence             0x000b
#define CWBSO_RTE_RIPMetric                   0x000c
#define CWBSO_RTE_RIPRedistribution           0x000d
#define CWBSO_RTE_PPPProfile                  0x000e
#define CWBSO_RTE_PPPCallerUserid             0x000f
#define CWBSO_RTE_PPPCallerIP                 0x0010
#define CWBSO_RTE_ApplicationDefined          0x0011
#define CWBSO_RTE_DependentDODProfile         0x0012

#define CWBSO_RTE_LastAttribute               0x0012

#endif
