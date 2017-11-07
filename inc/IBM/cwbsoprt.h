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
*   ClientAccess/400
*   System Object Access
*
*   CWBSOPRT.H - Declares for Printer Object and Printer List
*
******************************************************************************/

#ifndef _CWBSOPRT_H_
#define _CWBSOPRT_H_

/******************************************************************************
*   Bring in common declares
******************************************************************************/
#include "cwbsocmn.h"

/************************************************************************************
*   Printer Attribute IDs
*
*   Valid values for:
*       - CWBSO_GetObjAttr API
*       - CWBSO_SetParameter
*           (The above is to set an attribute ID and value in a parameter
*           object which is subsequently passed as input to CWBSO_SetObjAttr.)
*
*   These attributes are described in the appendix of this document:
*     Client Access/400 for Windows 3.1:  System Object Access API Guide and Reference
************************************************************************************/
#define CWBSO_PRT_DeviceName                       0x0000
#define CWBSO_PRT_PrinterDeviceType                0x0001
#define CWBSO_PRT_Description                      0x0002
#define CWBSO_PRT_Status                           0x0003
#define CWBSO_PRT_StartedByUser                    0x0004
#define CWBSO_PRT_ChangesTakeEffect                0x0005
#define CWBSO_PRT_MessageQueueName                 0x0006
#define CWBSO_PRT_MessageQueueLibrary              0x0007
#define CWBSO_PRT_FileName                         0x0008
#define CWBSO_PRT_FileNumber                       0x0009
#define CWBSO_PRT_UserSpecifiedData                0x000A
#define CWBSO_PRT_JobName                          0x000B
#define CWBSO_PRT_User                             0x000C
#define CWBSO_PRT_JobNumber                        0x000D
#define CWBSO_PRT_TotalPages                       0x000E
#define CWBSO_PRT_CurrentPage                      0x000F
#define CWBSO_PRT_TotalCopies                      0x0010
#define CWBSO_PRT_CopiesLeftToProduce              0x0011
#define CWBSO_PRT_FormType                         0x0012
#define CWBSO_PRT_NextFormType                     0x0013
#define CWBSO_PRT_FormsAlignment                   0x0014
#define CWBSO_PRT_FormTypeNotification             0x0015
#define CWBSO_PRT_NextFormTypeNotification         0x0016
#define CWBSO_PRT_NumberOfSeparators               0x0017
#define CWBSO_PRT_NextSeparators                   0x0018
#define CWBSO_PRT_SeparatorDrawer                  0x0019
#define CWBSO_PRT_NextSeparatorDrawer              0x001A
#define CWBSO_PRT_OutputQueueName                  0x001B
#define CWBSO_PRT_OutputQueueLibrary               0x001C
#define CWBSO_PRT_OutputQueueStatus                0x001D
#define CWBSO_PRT_NextOutputQueueName              0x001E
#define CWBSO_PRT_NextOutputQueueLibrary           0x001F
#define CWBSO_PRT_WriterJobName                    0x0020
#define CWBSO_PRT_WriterJobUser                    0x0021
#define CWBSO_PRT_WriterJobNumber                  0x0022
#define CWBSO_PRT_WriterStatus                     0x0023
#define CWBSO_PRT_AllowDirectPrinting              0x0024
#define CWBSO_PRT_EndAutomatically                 0x0025
#define CWBSO_PRT_DeviceStatus                     0x0026
#define CWBSO_PRT_MessageKey                       0x0027
#define CWBSO_PRT_WriterStarted                    0x0028
#define CWBSO_PRT_WritingStatus                    0x0029
#define CWBSO_PRT_MessageWaitingStatus             0x002A
#define CWBSO_PRT_HeldStatus                       0x002B
#define CWBSO_PRT_EndPendingStatus                 0x002C
#define CWBSO_PRT_HoldPendingStatus                0x002D
#define CWBSO_PRT_BetweenFilesStatus               0x002E
#define CWBSO_PRT_BetweenCopiesStatus              0x002F
#define CWBSO_PRT_WaitingForDataStatus             0x0030
#define CWBSO_PRT_WaitingForDeviceStatus           0x0031
#define CWBSO_PRT_OnJobQueueStatus                 0x0032
#define CWBSO_PRT_AdvancedFunctionPrinting         0x0033
#define CWBSO_PRT_PublishingStatus                 0x0034                   //@PPA

/******************************************************************************
*   Printer List Filter Attribute IDs
*
*   Valid values for:
*       - CWBSO_SetListFilter API
*
******************************************************************************/
#define CWBSO_PRTF_PrinterNameFilter               0x0001

#endif
