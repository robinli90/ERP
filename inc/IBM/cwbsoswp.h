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
*   cwbsoswp.h
*
* Purpose:
*   Define the attribute ids for the SoftwareProduct subclass.
*
******************************************************************************/

#ifndef _CWBSOSWP_H_
#define _CWBSOSWP_H_

/******************************************************************************
* Bring in common error codes and action codes
******************************************************************************/
#include "cwbsocmn.h"

/******************************************************************************
* Attribute ids
******************************************************************************/
#define CWBSO_SWP_ProductID                                      0x0000
#define CWBSO_SWP_ProductOption                                  0x0001
#define CWBSO_SWP_ReleaseLevel                                   0x0002
#define CWBSO_SWP_MessageID                                      0x0003
#define CWBSO_SWP_MessageFileName                                0x0004
#define CWBSO_SWP_DescriptionText                                0x0005
#define CWBSO_SWP_LoadID                                         0x0006
#define CWBSO_SWP_LoadType                                       0x0007
#define CWBSO_SWP_SymbolicLoadState                              0x0008
#define CWBSO_SWP_LoadErrorIndicator                             0x0009
#define CWBSO_SWP_LoadState                                      0x000a
#define CWBSO_SWP_SupportedFlag                                  0x000b
#define CWBSO_SWP_RegistrationType                               0x000c
#define CWBSO_SWP_RegistrationValue                              0x000d
#define CWBSO_SWP_PrimaryLanguageLoadID                          0x000e
#define CWBSO_SWP_MinimumTargetRelease                           0x000f
#define CWBSO_SWP_MinimumVRMOfBaseRequiredByOption               0x0010
#define CWBSO_SWP_RequirementsMetBetweenBaseAndOptionValue       0x0011
#define CWBSO_SWP_Level                                          0x0012
#define CWBSO_SWP_SecondaryLanguageLibraryName                   0x0013
#define CWBSO_SWP_PrimaryLibraryName                             0x0014
#define CWBSO_SWP_InstalledLibraryName                           0x0015
#define CWBSO_SWP_LibraryType                                    0x0016
#define CWBSO_SWP_LibraryAuthority                               0x0017
#define CWBSO_SWP_LibraryCreateAuthority                         0x0018

#define CWBSO_SWP_LastAttribute                                  0x0018

/******************************************************************************
*   SoftwareProduct Filter Attribute IDs
*
*   Valid values for:
*       - CWBSO_SetListFilter API
*
******************************************************************************/
#define CWBSO_SWPF_ProductOptions                                0x0000
#define CWBSO_SWPF_Product                                       0x0001

#endif
