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
*   cwbsohw4.h
*
* Purpose:
*   Define the attribute ids for the ProcessorResource subclass.
*
******************************************************************************/

#ifndef _CWBSOHW4_H_
#define _CWBSOHW4_H_

/******************************************************************************
* Bring in common error codes and action codes
******************************************************************************/
#include "cwbsocmn.h"
#include "cwbsohwr.h"

/******************************************************************************
* Attribute ids
******************************************************************************/
#define CWBSO_HW4_ResourceCategory             CWBSO_HWR_ResourceCategory
#define CWBSO_HW4_FamilyLevel                  CWBSO_HWR_FamilyLevel
#define CWBSO_HW4_LineType                     CWBSO_HWR_LineType
#define CWBSO_HW4_ResourceName                 CWBSO_HWR_ResourceName
#define CWBSO_HW4_Type                         CWBSO_HWR_Type
#define CWBSO_HW4_Model                        CWBSO_HWR_Model
#define CWBSO_HW4_Status                       CWBSO_HWR_Status
#define CWBSO_HW4_SystemConnectedTo            CWBSO_HWR_SystemConnectedTo
#define CWBSO_HW4_AdapterAdress                CWBSO_HWR_AdapterAdress
#define CWBSO_HW4_Description                  CWBSO_HWR_Description
#define CWBSO_HW4_Kind1                        CWBSO_HWR_Kind1
#define CWBSO_HW4_Kind2                        CWBSO_HWR_Kind2
#define CWBSO_HW4_Kind3                        CWBSO_HWR_Kind3
#define CWBSO_HW4_SystemBusNumber              0x000d
#define CWBSO_HW4_SystemBoardNumber            0x000e
#define CWBSO_HW4_SystemCardNumber             0x000f
#define CWBSO_HW4_SerialNumber                 0x0010
#define CWBSO_HW4_PartNumber                   0x0011
#define CWBSO_HW4_FrameID                      0x0012
#define CWBSO_HW4_CardPosition                 0x0013
#define CWBSO_HW4_ProcessorFeatureCode         0x0014
#define CWBSO_HW4_ProcessorFeature             0x0015
#define CWBSO_HW4_InteractiveFeatureCode       0x0016

#define CWBSO_HW4_LastAttribute                0x0016

#endif
