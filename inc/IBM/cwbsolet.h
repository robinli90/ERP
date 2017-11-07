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
// (C) Copyright IBM Corp. 1995,1998, 1999                                         
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
//   cwbsolet.h
//
// Purpose:
//   Define the attribute ids for the CEthernetLine subclass.
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
// $A1=D97576    4W5Y 990523 TIMON:   V4R5 additions for 1Gb/second Ethernet.
//******************************************************************************

#ifndef _CWBSOLET_H_
#define _CWBSOLET_H_

//******************************************************************************
// Bring in common error codes and action codes
//******************************************************************************
#include "cwbsocmn.h"

//******************************************************************************
// Attribute ids
//******************************************************************************
#define CWBSO_LET_CurrentStatusCode                             0x0000
#define CWBSO_LET_ConfigurationDescriptionName                  0x0001
#define CWBSO_LET_ConfigurationDescriptionCategory              0x0002
#define CWBSO_LET_CurrentStatus                                 0x0003
#define CWBSO_LET_Description                                   0x0004
#define CWBSO_LET_JobName                                       0x0005
#define CWBSO_LET_JobUser                                       0x0006
#define CWBSO_LET_JobNumber                                     0x0007
#define CWBSO_LET_PassThroughDevice                             0x0008
#define CWBSO_LET_NumberOfAttachedControllers                   0x0009
#define CWBSO_LET_RetrieveDate                                  0x000a
#define CWBSO_LET_RetrieveTime                                  0x000b
#define CWBSO_LET_OnlineAtIPL                                   0x000c
#define CWBSO_LET_VaryOnWait                                    0x000d
#define CWBSO_LET_MaximumControllers                            0x000e
#define CWBSO_LET_LinkSpeed                                     0x000f
#define CWBSO_LET_CostPerConnectTime                            0x0010
#define CWBSO_LET_CostPerByte                                   0x0011
#define CWBSO_LET_UserDefined1                                  0x0012
#define CWBSO_LET_UserDefined2                                  0x0013
#define CWBSO_LET_UserDefined3                                  0x0014
#define CWBSO_LET_AutodeleteController                          0x0015
#define CWBSO_LET_RecoveryLimitsCountLimit                      0x0016
#define CWBSO_LET_RecoveryLimitsTimeInterval                    0x0017
#define CWBSO_LET_ResourceName                                  0x0018
#define CWBSO_LET_NetworkController                             0x0019
#define CWBSO_LET_LocalAdapterAddress                           0x001a
#define CWBSO_LET_ExchangeID                                    0x001b
#define CWBSO_LET_EthernetStandard                              0x001c
#define CWBSO_LET_ErrorThresholdLevel                           0x001d
#define CWBSO_LET_SecurityForLine                               0x001e
#define CWBSO_LET_PropagationDelay                              0x001f
#define CWBSO_LET_AutocreateController                          0x0020
#define CWBSO_LET_PortNumber                                    0x0021
#define CWBSO_LET_AttachedNonswitchedNWI                        0x0022
#define CWBSO_LET_NetworkInterfaceDLCIdentifier                 0x0023
#define CWBSO_LET_NetworkServerDescription                      0x0024
#define CWBSO_LET_Duplex                                        0x0025
#define CWBSO_LET_LineSpeed                                     0x0026
#define CWBSO_LET_GenerateTestFrame                             0x0027
#define CWBSO_LET_LECCacheAgingTime                             0x0028
#define CWBSO_LET_ARPRetryCount                                 0x0029
#define CWBSO_LET_ARPRetryTimer                                 0x002a
#define CWBSO_LET_MaximumARPEntries                             0x002b
#define CWBSO_LET_LECDisconnectTimeOut                          0x002c
#define CWBSO_LET_ATMAccessType                                 0x002d
#define CWBSO_LET_EmulatedLANName                               0x002e
#define CWBSO_LET_LocalATMAddressNetworkPrefix                  0x002f
#define CWBSO_LET_LocalATMAddressEndSystemID                    0x0030
#define CWBSO_LET_LocalATMAddressLECSelectorByte                0x0031
#define CWBSO_LET_LESATMAddressNetworkPrefix                    0x0032
#define CWBSO_LET_LESATMAddressEndSystemID                      0x0033
#define CWBSO_LET_LESATMAddressLECSelectorByte                  0x0034
#define CWBSO_LET_LastContactedLESATMAddressNetworkPrefix       0x0035
#define CWBSO_LET_LastContactedLESATMAddressEndSystemID         0x0036
#define CWBSO_LET_LastContactedLESATMAddressLECSelectorByte     0x0037
#define CWBSO_LET_UseLECSAddress                                0x0038
#define CWBSO_LET_NetworkInterfaceType                          0x0039
#define CWBSO_LET_ReportedEmulatedLANName                       0x003a
#define CWBSO_LET_MaxTransmissionUnitSize                       0x003b
#define CWBSO_LET_LinkSpeedMultiplier                           0x003c  
#define CWBSO_LET_MessageQueueName                              0x003d   
#define CWBSO_LET_MessageQueueLibrary                           0x003e   
#define CWBSO_LET_CurrentMessageQueueName                       0x003f   
#define CWBSO_LET_CurrentMessageQueueLibrary                    0x0040   
#define CWBSO_LET_EnableTCPOnly                                 0x0041   
#define CWBSO_LET_MaximumFrameSize                              0x0042
#define CWBSO_LET_CurrentLineSpeed                              0x0043
#define CWBSO_LET_CurrentDuplex                                 0x0044       

#define CWBSO_LET_LastAttribute                                 0x0044

#endif
