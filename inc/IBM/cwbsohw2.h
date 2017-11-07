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
*   cwbsohw2.h
*
* Purpose:
*   Define the attribute ids for the CommunicationsResource subclass.
*
******************************************************************************/

#ifndef _CWBSOHW2_H_
#define _CWBSOHW2_H_

/******************************************************************************
* Bring in common error codes and action codes
******************************************************************************/
#include "cwbsocmn.h"
#include "cwbsohwr.h"

/******************************************************************************
* Attribute ids
******************************************************************************/
#define CWBSO_HW2_ResourceCategory             CWBSO_HWR_ResourceCategory
#define CWBSO_HW2_FamilyLevel                  CWBSO_HWR_FamilyLevel
#define CWBSO_HW2_LineType                     CWBSO_HWR_LineType
#define CWBSO_HW2_ResourceName                 CWBSO_HWR_ResourceName
#define CWBSO_HW2_Type                         CWBSO_HWR_Type
#define CWBSO_HW2_Model                        CWBSO_HWR_Model
#define CWBSO_HW2_Status                       CWBSO_HWR_Status
#define CWBSO_HW2_SystemConnectedTo            CWBSO_HWR_SystemConnectedTo
#define CWBSO_HW2_AdapterAdress                CWBSO_HWR_AdapterAdress
#define CWBSO_HW2_Description                  CWBSO_HWR_Description
#define CWBSO_HW2_Kind1                        CWBSO_HWR_Kind1
#define CWBSO_HW2_Kind2                        CWBSO_HWR_Kind2
#define CWBSO_HW2_Kind3                        CWBSO_HWR_Kind3
#define CWBSO_HW2_SystemBusNumber              0x000d
#define CWBSO_HW2_SystemBoardNumber            0x000e
#define CWBSO_HW2_SystemCardNumber             0x000f
#define CWBSO_HW2_IOBusAddress                 0x0010
#define CWBSO_HW2_AdapterAddress               0x0011
#define CWBSO_HW2_PortNumber                   0x0012
#define CWBSO_HW2_SerialNumber                 0x0013
#define CWBSO_HW2_PartNumber                   0x0014
#define CWBSO_HW2_FrameID                      0x0015
#define CWBSO_HW2_CardPosition                 0x0016

#define CWBSO_HW2_LastAttribute                0x0016

#endif
