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
*   cwbsousg.h
*
* Purpose:
*   Define the attribute ids for the UserGroup subclass.
*
******************************************************************************/

#ifndef _CWBSOUSG_H_
#define _CWBSOUSG_H_

/******************************************************************************
* Bring in common error codes and action codes
******************************************************************************/
#include "cwbsocmn.h"
#include "cwbsoprf.h"

/******************************************************************************
* Attribute ids
******************************************************************************/
#define CWBSO_USG_ProfileName                            CWBSO_PRF_ProfileName
#define CWBSO_USG_ProfileOrGroupIndicator                CWBSO_PRF_ProfileOrGroupIndicator
#define CWBSO_USG_GroupHasMembers                        CWBSO_PRF_GroupHasMembers
#define CWBSO_USG_TextDescription                        CWBSO_PRF_TextDescription
#define CWBSO_USG_UserClassName                          0x0004
#define CWBSO_USG_AllObjectAccess                        0x0005
#define CWBSO_USG_SecurityAdministration                 0x0006
#define CWBSO_USG_JobControl                             0x0007
#define CWBSO_USG_SpoolControl                           0x0008
#define CWBSO_USG_SaveAndRestore                         0x0009
#define CWBSO_USG_SystemServiceAccess                    0x000a
#define CWBSO_USG_AuditingControl                        0x000b
#define CWBSO_USG_SystemConfiguration                    0x000c
#define CWBSO_USG_GroupProfileName                       0x000d
#define CWBSO_USG_GroupIDNumber                          0x000e
#define CWBSO_USG_GroupUIDNumber                         0x000f
#define CWBSO_USG_LastAttribute                          0x000f

#endif
