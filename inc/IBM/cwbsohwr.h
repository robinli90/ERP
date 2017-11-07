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
*   cwbsohwr.h
*
* Purpose:
*   Define the attribute ids for the HardwareResource subclass.
*
******************************************************************************/

#ifndef _CWBSOHWR_H_
#define _CWBSOHWR_H_

/******************************************************************************
* Bring in common error codes and action codes
******************************************************************************/
#include "cwbsocmn.h"

/******************************************************************************
* Attribute ids
******************************************************************************/
#define CWBSO_HWR_ResourceCategory             0x0000
#define CWBSO_HWR_FamilyLevel                  0x0001
#define CWBSO_HWR_LineType                     0x0002
#define CWBSO_HWR_ResourceName                 0x0003
#define CWBSO_HWR_Type                         0x0004
#define CWBSO_HWR_Model                        0x0005
#define CWBSO_HWR_Status                       0x0006
#define CWBSO_HWR_SystemConnectedTo            0x0007
#define CWBSO_HWR_AdapterAdress                0x0008
#define CWBSO_HWR_Description                  0x0009
#define CWBSO_HWR_Kind1                        0x000a
#define CWBSO_HWR_Kind2                        0x000b
#define CWBSO_HWR_Kind3                        0x000c

#define CWBSO_HWR_LastAttribute                0x000c

/******************************************************************************
*   HardwareResource Filter Attribute IDs
*
*   Valid values for:
*       - CWBSO_SetListFilter API
*
******************************************************************************/
#define CWBSO_HWRF_ResourceCategory            0x0000

#endif
