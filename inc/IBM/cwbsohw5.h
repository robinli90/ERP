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
* (C) Copyright IBM Corp. 1995,1998                                         
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
*   cwbsohw5.h
*
* Purpose:
*   Define the attribute ids for the StorageDeviceResource subclass.
*
******************************************************************************/

#ifndef _CWBSOHW5_H_
#define _CWBSOHW5_H_

/******************************************************************************
* Bring in common error codes and action codes
******************************************************************************/
#include "cwbsocmn.h"
#include "cwbsohwr.h"

/******************************************************************************
* Attribute ids
******************************************************************************/
#define CWBSO_HW5_ResourceCategory             CWBSO_HWR_ResourceCategory
#define CWBSO_HW5_FamilyLevel                  CWBSO_HWR_FamilyLevel
#define CWBSO_HW5_LineType                     CWBSO_HWR_LineType
#define CWBSO_HW5_ResourceName                 CWBSO_HWR_ResourceName
#define CWBSO_HW5_Type                         CWBSO_HWR_Type
#define CWBSO_HW5_Model                        CWBSO_HWR_Model
#define CWBSO_HW5_Status                       CWBSO_HWR_Status
#define CWBSO_HW5_SystemConnectedTo            CWBSO_HWR_SystemConnectedTo
#define CWBSO_HW5_AdapterAdress                CWBSO_HWR_AdapterAdress
#define CWBSO_HW5_Description                  CWBSO_HWR_Description
#define CWBSO_HW5_Kind1                        CWBSO_HWR_Kind1
#define CWBSO_HW5_Kind2                        CWBSO_HWR_Kind2
#define CWBSO_HW5_Kind3                        CWBSO_HWR_Kind3
#define CWBSO_HW5_SystemBusNumber              0x000d
#define CWBSO_HW5_SystemBoardNumber            0x000e
#define CWBSO_HW5_SystemCardNumber             0x000f
#define CWBSO_HW5_IOBusAddress                 0x0010
#define CWBSO_HW5_ControllerAddress            0x0011
#define CWBSO_HW5_DeviceAddress                0x0012
#define CWBSO_HW5_DevicePosition               0x0013
#define CWBSO_HW5_SerialNumber                 0x0014
#define CWBSO_HW5_PartNumber                   0x0015
#define CWBSO_HW5_FrameID                      0x0016
#define CWBSO_HW5_CardPosition                 0x0017

#define CWBSO_HW5_LastAttribute                0x0017

#endif
