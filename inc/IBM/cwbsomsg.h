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
*   CWBSOMSG.H - Declares for Message Object and Message List
*
******************************************************************************/

#ifndef _CWBSOMSG_H_
#define _CWBSOMSG_H_

/******************************************************************************
*   Bring in common declares
******************************************************************************/
#include "cwbsocmn.h"

/******************************************************************************
*   Message Attribute IDs
*
*   Valid values for:
*       - CWBSO_GetObjAttr API
*       - CWBSO_SetParameter
*         (The above is to set an attribute ID and value in a parameter
*         object which is subsequently passed as input to CWBSO_SetObjAttr.)
*
*   The comment after each attribute contains the API name where the attribute is  
*   described, along with the name of the field as it appears in the API document 
*   if it is different than the name of the attribute in this file.                                          
******************************************************************************/  
                                                            /*  API      Name of field (if different)                */
                                                            /* --------  ----------------------------                */         
#define CWBSO_MSG_MessageSeverity                  0x0000   /* QMHLSTM                                               */
#define CWBSO_MSG_MessageIdentifier                0x0001   /* QMHLSTM                                               */
#define CWBSO_MSG_MessageType                      0x0002   /* QMHLSTM                                               */
#define CWBSO_MSG_MessageKey                       0x0003   /* QMHLSTM                                               */
#define CWBSO_MSG_MessageFileName                  0x0004   /* QMHLSTM                                               */
#define CWBSO_MSG_MessageFileLibrary               0x0005   /* QMHLSTM   Message file library specified at send time */
#define CWBSO_MSG_MessageQueueName                 0x0006   /* QMHLSTM                                               */
#define CWBSO_MSG_MessageQueueLibrary              0x0007   /* QMHLSTM                                               */
#define CWBSO_MSG_DateSent                         0x0008   /* QMHLSTM                                               */
#define CWBSO_MSG_TimeSent                         0x0009   /* QMHLSTM                                               */
#define CWBSO_MSG_MessageText                      0x000A   /* QMHLSTM   Message with replacement data               */
#define CWBSO_MSG_SenderJobName                    0x000B   /* QMHLSTM   Qualified sender job name                   */
#define CWBSO_MSG_SenderUserName                   0x000C   /* QMHLSTM   Qualified sender job name                   */
#define CWBSO_MSG_SenderJobNumber                  0x000D   /* QMHLSTM   Qualified sender job name                   */
#define CWBSO_MSG_SendingProgramName               0x000E   /* QMHLSTM                                               */
#define CWBSO_MSG_ReplyStatus                      0x000F   /* QMHLSTM                                               */
#define CWBSO_MSG_DefaultReply                     0x0010   /* QMHLSTM                                               */
#define CWBSO_MSG_MessageHelp                      0x0011   /* QMHLSTM   Message help with replacement data          */

/******************************************************************************
*   Message List Filter Attribute IDs
*
*   Valid values for:
*   - CWBSO_SetListFilter API
*
******************************************************************************/
#define  CWBSO_MSGF_SeverityCriteria               0x0002
#define  CWBSO_MSGF_UserName                       0x0010


#endif
