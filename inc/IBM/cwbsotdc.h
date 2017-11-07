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
//
// IBM Confidential
//
// OCO Source Materials
//
// The Source code for this program is not published or otherwise
// divested of its trade secrets, irrespective of what has been
// deposited with the U.S. Copyright Office
//
// 5722-XE1
// (C) Copyright IBM Corp. 1999, 2000

//********************************************************************
//
// ** This file was generated by SOAGEN version 1.3
// ** Generated on 06/16/00 at 10:11:28
//
//********************************************************************
//********************************************************************
//
// File:
//   cwbsotdc.h
//
// Purpose:
//   Define the attribute ids for the CTapeDeviceCapabilities subclass.
//
// CHANGE ACTIVITY:
//   This change flag section must follow a specific format to allow
//   the change flag utilities to count lines of code.  Each line
//   must have both comment delimiters.  All three special symbols
//   are required (dollar sign, equal sign and colon).
//
// Flg=Reason    Vers yymmdd UserID   Description
// ------------- ---- ------ ------   -----------
// $A0=P9926783  5D10 000616 SOAGEN : Created

//********************************************************************
#ifndef _CWBSOTDC_H_
#define _CWBSOTDC_H_

//*****************************************************************************
// Bring in common error codes and action codes
//*****************************************************************************
#include "cwbsocmn.h"

//*****************************************************************************
// Attribute ids
//*****************************************************************************

#define CWBSO_TDC_ResourceName                          0x0000
#define CWBSO_TDC_ResourceIndicator                     0x0001
#define CWBSO_TDC_DeviceResourceName                    0x0002
#define CWBSO_TDC_DeviceRelationshipMediaLibraryDevice  0x0003
#define CWBSO_TDC_TypeMediaLibraryDevice                0x0004
#define CWBSO_TDC_SelfConfiguredDevice                  0x0005
#define CWBSO_TDC_DeviceType                            0x0006
#define CWBSO_TDC_DeviceModel                           0x0007
#define CWBSO_TDC_MaxBlockSize                          0x0008
#define CWBSO_TDC_LogicalBlockID                        0x0009
#define CWBSO_TDC_AssignCapability                      0x000a
#define CWBSO_TDC_OverwriteCapability                   0x000b
#define CWBSO_TDC_ReadBackwardCapability                0x000c
#define CWBSO_TDC_CartridgeCheckingCapability           0x000d
#define CWBSO_TDC_DeviceClass                           0x000e
#define CWBSO_TDC_HardwareDataCompressionCapability     0x000f
#define CWBSO_TDC_LabelCompactionSupported              0x0010
#define CWBSO_TDC_OptimumBlockSize                      0x0011
#define CWBSO_TDC_SpaceEndData                          0x0012
#define CWBSO_TDC_SpaceBackwardAllowed                  0x0013
#define CWBSO_TDC_MediaLibraryDeviceBarScanner          0x0014
#define CWBSO_TDC_IDRCSupported                         0x0015
#define CWBSO_TDC_AutomaticCartridgeSupported           0x0016
#define CWBSO_TDC_BitMappingIDRCDensities               0x0017
#define CWBSO_TDC_BitMappingWriteDensities              0x0018
#define CWBSO_TDC_BitMappingReadDensities               0x0019
#define CWBSO_TDC_BitMappingHighestDensities            0x001a
#define CWBSO_TDC_BitMappingAllDensities                0x001b
#define CWBSO_TDC_QTACTLDVAPISupported                  0x001c
#define CWBSO_TDC_MediaLibraryDeviceDoor                0x001d
#define CWBSO_TDC_AcceptableReadErrorThreshold          0x001e
#define CWBSO_TDC_AcceptableWriteErrorThreshold         0x001f
#define CWBSO_TDC_InstantaneousPerformance              0x0020

#define CWBSO_TDC_LastAttribute                         0x0020

#endif
