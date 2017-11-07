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
*   CWBSOCMN.H - SOF Common Declares
*
*               This header file should not be #included directly because
*               it is included by the following object header files:
*                   cwbsojob.h - Job Object and Job List
*                   cwbsomsg.h - Message Object and Message List
*                   cwbsoprt.h - Printer Object and Printer List
*                   cwbsosfl.h - Spoooled File Object and Spooled File List
*
*
*******************************************************************************
* $PB=D98163   5D10 991118 TLK      : Support Publish/Unpublish printers   
*
******************************************************************************/

#ifndef _CWBSOCMN_H_
#define _CWBSOCMN_H_


/******************************************************************************
*
*   Error codes from APIs
*
******************************************************************************/
#define CWBSO_NO_ERROR              0       /* No error occurred */
#define CWBSO_ERROR_OCCURRED        1       /* Check errorHandle parameter */
#define CWBSO_LOW_MEMORY            2       /* Cannot allocate enough memory */
#define CWBSO_BAD_LISTTYPE          3       /* List type specified not valid */
#define CWBSO_BAD_HANDLE            4       /* Handle specified is not valid */
#define CWBSO_BAD_LIST_HANDLE       5       /* Handle specified is not valid
                                               list handle */
#define CWBSO_BAD_OBJ_HANDLE        6       /* Handle specified is not valid
                                               object handle */
#define CWBSO_BAD_PARMOBJ_HANDLE    7       /* Handle specified is not valid
                                               parameter object handle */
#define CWBSO_BAD_ERR_HANDLE        8       /* Handle specified is not valid
                                               error handle */
#define CWBSO_BAD_LIST_POSITION     9       /* List position is not valid.
                                               Either less than zero or
                                               greater than liust size */
#define CWBSO_BAD_ACTION_ID         10      /* Action ID specified is not
                                               valid for this list */
#define CWBSO_NOT_ALLOWED_NOW       11      /* Function is not allowed at
                                               this time for this object */
#define CWBSO_BAD_INCLUDE_ID        12      /* Filter ID specified is not
                                               valid for this list */
#define CWBSO_DISP_MSG_FAILED       13      /* Display of error message
                                               failed */
#define CWBSO_GET_MSG_FAILED        14      /* Get error message text failed */
#define CWBSO_BAD_SORT_ID           15      /* Attribute ID for sorting is not
                                               valid for this list */
#define CWBSO_INTERNAL_ERROR        16      /* Internal processing error */
#define CWBSO_NO_ERROR_MESSAGE      17      /* There is no error message for
                                               the error handle specified */
#define CWBSO_BAD_ATTRIBUTE_ID      18      /* Attribute ID specified
                                               is not valid */
#define CWBSO_BAD_TITLE             19      /* Title specified is not valid */
#define CWBSO_BAD_FILTER_VALUE      20      /* Filter value is not valid */
#define CWBSO_BAD_PROFILE_NAME      21      /* Profile name is not valid */
#define CWBSO_DISPLAY_FAILED        22      /* Display request failed */
#define CWBSO_SORT_NOT_ALLOWED      23      /* List can not be sorted */
#define CWBSO_CANNOT_CHANGE_ATTR    24      /* Object attribute cannot be changed */
#define CWBSO_CANNOT_READ_PROFILE   25      /* Cannot read from profile */
#define CWBSO_CANNOT_WRITE_PROFILE  26      /* Cannot write to profile */
#define CWBSO_BAD_SYSTEM_NAME       27      /* System name specified is not valid */
#define CWBSO_SYSTEM_NAME_DEFAULTED 28      /* Default system name was used */
#define CWBSO_BAD_FILTER_ID         29      /* Filter id is not valid */
#define CWBSO_BAD_OBJTYPE           30      /* Object type not valid */
#define CWBSO_DISPLAY_NOT_SUPPORTED 31      /* Display is not valid for this list type */

/******************************************************************************
*   Menu action IDs (for pulldown and toolbar actions)
*
*   Valid action ID values for the CWBSO_DisallowListActions API
*
******************************************************************************/
                                        /* Object:      sfl job prt msg      */
#define CWBSO_ACTN_PRINTNEXT        301 /*               Y                   */
#define CWBSO_ACTN_SEND             302 /*               Y                   */
#define CWBSO_ACTN_HOLD             303 /*               Y   Y   Y           */
#define CWBSO_ACTN_DELETE           304 /*               Y   Y       Y       */
#define CWBSO_ACTN_OPEN             305 /*               Y           Y       */
#define CWBSO_ACTN_RELEASE          306 /*               Y   Y   Y           */
#define CWBSO_ACTN_PROPERTIES       307 /*               Y   Y   Y   Y       */
#define CWBSO_ACTN_MSGWTG           308 /*               Y   Y   Y   Y       */
#define CWBSO_ACTN_HELP             309 /*               Y   Y   Y   Y       */
#define CWBSO_ACTN_MOVE             310 /*               Y   Y               */
#define CWBSO_ACTN_RESTART          311 /*               Y       Y           */
#define CWBSO_ACTN_PRINTEROUTPUT    312 /*                   Y   Y           */
#define CWBSO_ACTN_JOBLOG           313 /*                   Y               */
#define CWBSO_ACTN_START            315 /*                       Y           */
#define CWBSO_ACTN_STOP             316 /*                       Y           */
#define CWBSO_ACTN_MAKEAVAILABLE    317 /*                       Y           */
#define CWBSO_ACTN_MAKEUNAVAILABLE  318 /*                       Y           */
#define CWBSO_ACTN_PUBLISH          319 /*                       Y           */
#define CWBSO_ACTN_UNPUBLISH        320 /*                       Y           */

#endif
