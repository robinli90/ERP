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
//*******************************************************************************
// 5769-XE1                                                                  
// (C) Copyright IBM Corp. 1995,1998                                         
// All rights reserved.                                                      
// US Government Users Restricted Rights -                                   
// Use, duplication or disclosure restricted                                 
// by GSA ADP Schedule Contract with IBM Corp.                               
//                                                                           
// Licensed Materials-Property of IBM                                        
//                                                                           
//******************************************************************************
//******************************************************************************
//
// File:
//   cwbsotca.h
//
// Purpose:
//   Define the attribute ids for the CTCPIPAttributes subclass.
//
// CHANGE ACTIVITY:
//   This change flag section must follow a specific format to allow
//   the change flag utilities to count lines of code.  Each line
//   must have both comment delimiters.  All three special symbols
//   are required (dollar sign, equal sign and colon).
//
// Flg=Reason    Vers yymmdd UserID   Description
// ------------- ---- ------ ------   -----------
// $A0=D97225    4C4Y 980906 SOAGEN:  Created.
//********************************************************************

#ifndef _CWBSOTCA_H_
#define _CWBSOTCA_H_

//******************************************************************************
//* Bring in common error codes and action codes
//******************************************************************************
#include "cwbsocmn.h"

//******************************************************************************
//* Attribute ids
//******************************************************************************
#define CWBSO_TCA_IPDatagramForwarding       0x0000
#define CWBSO_TCA_UDPChecks                  0x0001
#define CWBSO_TCA_LogProtocolErrors          0x0002
#define CWBSO_TCA_IPSourceRouting            0x0003
#define CWBSO_TCA_TCPUrgentPointer           0x0004
#define CWBSO_TCA_IPReassemblyTimeout        0x0005
#define CWBSO_TCA_IPTimeToLive               0x0006
#define CWBSO_TCA_TCPKeepAlive               0x0007
#define CWBSO_TCA_TCPReceiveBuffer           0x0008
#define CWBSO_TCA_TCPSendBuffer              0x0009
#define CWBSO_TCA_ARPCacheTimeout            0x000a
#define CWBSO_TCA_MTUPathDiscovery           0x000b     
#define CWBSO_TCA_MTUDiscoveryInterval       0x000c     
#define CWBSO_TCA_HostName                   0x000d
#define CWBSO_TCA_DomainName                 0x000e
#define CWBSO_TCA_InternetAddress1           0x000f
#define CWBSO_TCA_InternetAddress2           0x0010
#define CWBSO_TCA_InternetAddress3           0x0011
#define CWBSO_TCA_DNSProtocol                0x0012
#define CWBSO_TCA_Retries                    0x0013
#define CWBSO_TCA_TimeInterval               0x0014
#define CWBSO_TCA_SearchOrder                0x0015
#define CWBSO_TCA_DNSListeningPort           0x0016

// new ones for V5R1
#define CWBSO_TCA_QOSEnablement						0x0017
#define CWBSO_TCA_QOSTimerResolution				0x0018
#define CWBSO_TCA_QOSDataPathOptimization			0x0019
#define CWBSO_TCA_DeadGatewayDetectionEnablement	0x001a
#define CWBSO_TCA_DeadGatewayDetectionInterval		0x001b
#define CWBSO_TCA_TCPTimeWaitTimeout				0x001c
#define CWBSO_TCA_TCPR1RetransmissionCount			0x001d
#define CWBSO_TCA_TCPR2RetransmissionCount			0x001e
#define CWBSO_TCA_InitialDomainNameServer			0x001f
#define CWBSO_TCA_DomainSearchList					0x0020

#define CWBSO_TCA_LastAttribute              0x0020

#endif
