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
* 5722-XE1                                                                  
* (C) Copyright IBM Corp. 1995, 2000                                         
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
*   cwbsoprf.h
*
* Purpose:
*   Define the attribute ids for the UserProfile subclass.
*
******************************************************************************/

#ifndef _CWBSOPRF_H_
#define _CWBSOPRF_H_

/******************************************************************************
* Bring in common error codes and action codes
******************************************************************************/
#include "cwbsocmn.h"

/******************************************************************************
* Attribute ids
******************************************************************************/
#define CWBSO_PRF_ProfileName                                 0x0000
#define CWBSO_PRF_ProfileOrGroupIndicator                     0x0001
#define CWBSO_PRF_GroupHasMembers                             0x0002
#define CWBSO_PRF_TextDescription                             0x0003

#define CWBSO_PRF_LastAttribute                               0x0003

/******************************************************************************
*   UserProfileList Filter Attribute IDs
*
*   Valid values for:
*       - CWBSO_SetListFilter API
*
******************************************************************************/
#define CWBSO_PRFF_Profile                                    0x0001    // Selection Criteria 
#define CWBSO_PRFF_GroupName                                  0x0002    // Group Profile Name
// Reserved                                                   0x0003
#define CWBSO_PRFF_ProfileMatch                               0x0004    // Profile Name (for profile pattern matching)

#endif
