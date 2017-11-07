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
*   CWBSOJOB.H - Declares for Job Object and Job List
*
******************************************************************************/

#ifndef _CWBSOJOB_H_
#define _CWBSOJOB_H_

/******************************************************************************
*   Bring in common declares
******************************************************************************/
#include "cwbsocmn.h"

/******************************************************************************
*   Job Attribute IDs
*
*   Valid values for:
*       - CWBSO_GetObjAttr API
*       - CWBSO_SetParameter
*         (The above is to set an attribute ID and value in a
*         parameter object which is subsequently passed as input to
*         CWBSO_SetObjAttr.)
*
*   The comment after each attribute contains the API name where the attribute is
*   described, along with the name of the field as it appears in the API document
*   if it is different than the name of the attribute in this file.
******************************************************************************/
                                                            /*  API      Name of field (if different)                */
                                                            /* --------  ----------------------------                */
#define CWBSO_JOB_JobName                           0x0000  /* QUSRJOBI                                              */
#define CWBSO_JOB_UserName                          0x0001  /* QUSRJOBI                                              */
#define CWBSO_JOB_JobNumber                         0x0002  /* QUSRJOBI                                              */
#define CWBSO_JOB_JobType                           0x0003  /* QUSRJOBI                                              */
#define CWBSO_JOB_JobSubtype                        0x0004  /* QUSRJOBI                                              */
#define CWBSO_JOB_JobStatus                         0x0005  /* QUSRJOBI                                              */
#define CWBSO_JOB_DateEnteredSystem                 0x0006  /* QUSRJOBI  Date and time job entered system            */
#define CWBSO_JOB_TimeEnteredSystem                 0x0007  /* QUSRJOBI  Date and time job entered system            */
#define CWBSO_JOB_DateStarted                       0x0008  /* QUSRJOBI  Date and time job became active             */
#define CWBSO_JOB_TimeStarted                       0x0009  /* QUSRJOBI  Date and time job became active             */
#define CWBSO_JOB_JobDescriptionName                0x000A  /* QUSRJOBI                                              */
#define CWBSO_JOB_JobDescriptionLibrary             0x000B  /* QUSRJOBI                                              */
#define CWBSO_JOB_SubmittedByJobName                0x000C  /* QUSRJOBI  Submitter's job name                        */
#define CWBSO_JOB_SubmittedByUser                   0x000D  /* QUSRJOBI  Submitter's user name                       */
#define CWBSO_JOB_SubmittedByJobNumber              0x000E  /* QUSRJOBI  Submitter's job number                      */
#define CWBSO_JOB_JobQueueName                      0x000F  /* QUSRJOBI                                              */
#define CWBSO_JOB_JobQueueLibrary                   0x0010  /* QUSRJOBI                                              */
#define CWBSO_JOB_PriorityOnJobQueue                0x0011  /* QUSRJOBI  Job queue priority                          */
#define CWBSO_JOB_JobQueueDate                      0x0013  /* QUSRJOBI  Date and time the job was put on this job queue */
#define CWBSO_JOB_JobQueueTime                      0x0014  /* QUSRJOBI  Date and time the job was put on this job queue */
#define CWBSO_JOB_PriorityOnOutputQueue             0x0015  /* QUSRJOBI  Output queue priority                        */
#define CWBSO_JOB_Printer                           0x0016  /* QUSRJOBI  Printer device name                         */
#define CWBSO_JOB_OutputQueueName                   0x0017  /* QUSRJOBI                                              */
#define CWBSO_JOB_OutputQueueLibrary                0x0018  /* QUSRJOBI                                              */
#define CWBSO_JOB_PrintText                         0x0019  /* QUSRJOBI                                              */
#define CWBSO_JOB_PrintKeyFormat                    0x001A  /* QUSRJOBI                                              */
#define CWBSO_JOB_RunPriority                       0x001B  /* QUSRJOBI                                              */
#define CWBSO_JOB_SubsystemName                     0x001C  /* QUSRJOBI  Subsystem description name                  */
#define CWBSO_JOB_SubsystemLibrary                  0x001D  /* QUSRJOBI  Subsystem description library name          */
#define CWBSO_JOB_SystemPoolId                      0x001E  /* QUSRJOBI                                              */
#define CWBSO_JOB_CurrentUser                       0x001F  /* QUSRJOBI  Current user profile                        */
#define CWBSO_JOB_SpecialEnvironment                0x0020  /* QUSRJOBI                                              */
#define CWBSO_JOB_MaxCpuTime                        0x0021  /* QUSRJOBI  Maximum processing unit time                */
#define CWBSO_JOB_CpuTimeUsed                       0x0022  /* QUSRJOBI  Processing unit used                        */
#define CWBSO_JOB_MaxTempStorage                    0x0023  /* QUSRJOBI  Maximum temporary storage                   */
#define CWBSO_JOB_TempStorageUsed                   0x0024  /* QUSRJOBI  Temporary storage used                      */
#define CWBSO_JOB_AuxiliaryIORequests               0x0025  /* QUSRJOBI  Number of auxiliary I/O requests            */
#define CWBSO_JOB_InteractiveTransactions           0x0026  /* QUSRJOBI  Number of interactive transactions          */
#define CWBSO_JOB_TotalResponseTime                 0x0027  /* QUSRJOBI  Response time total                         */
#define CWBSO_JOB_TimeSlice                         0x0028  /* QUSRJOBI                                              */
#define CWBSO_JOB_TimeSliceEndPool                  0x0029  /* QUSRJOBI                                              */
#define CWBSO_JOB_EligibleForPurge                  0x002A  /* QUSRJOBI  Purge                                       */
#define CWBSO_JOB_DefaultWaitTime                   0x002B  /* QUSRJOBI  Default wait                                */
#define CWBSO_JOB_ProductReturnCode                 0x002C  /* QUSRJOBI                                              */
#define CWBSO_JOB_UserReturnCode                    0x002D  /* QUSRJOBI                                              */
#define CWBSO_JOB_ProgramReturnCode                 0x002E  /* QUSRJOBI                                              */
#define CWBSO_JOB_ControlledEndRequested            0x002F  /* QUSRJOBI  End status                                  */
#define CWBSO_JOB_SwitchSettings                    0x0030  /* QUSRJOBI  Job switches                                */
#define CWBSO_JOB_BreakMessageHandling              0x0031  /* QUSRJOBI                                              */
#define CWBSO_JOB_StatusMessageHandling             0x0032  /* QUSRJOBI                                              */
#define CWBSO_JOB_InquiryMessageReply               0x0033  /* QUSRJOBI                                              */
#define CWBSO_JOB_EndSeverity                       0x0034  /* QUSRJOBI                                              */
#define CWBSO_JOB_LogCLPrograms                     0x0035  /* QUSRJOBI  Logging of CL programs                      */
#define CWBSO_JOB_MessageLoggingLevel               0x0036  /* QUSRJOBI  Logging level                               */
#define CWBSO_JOB_MessageSeverityLevel              0x0037  /* QUSRJOBI  Logging severity                            */
#define CWBSO_JOB_MessageInfoLogged                 0x0038  /* QUSRJOBI  Logging text                                */
#define CWBSO_JOB_MessageQueueMaxSize               0x0039  /* QUSRJOBI  Job message queue maximum size              */
#define CWBSO_JOB_MessageQueueAction                0x003A  /* QUSRJOBI  Job message queue full action               */
#define CWBSO_JOB_JobDate                           0x003B  /* QUSRJOBI                                              */
#define CWBSO_JOB_DateFormat                        0x003C  /* QUSRJOBI                                              */
#define CWBSO_JOB_DateSeparator                     0x003D  /* QUSRJOBI                                              */
#define CWBSO_JOB_TimeSeparator                     0x003E  /* QUSRJOBI                                              */
#define CWBSO_JOB_ScheduleDate                      0x0040  /* QUSRJOBI  Date and time job is scheduled to run       */
#define CWBSO_JOB_ScheduleTime                      0x0041  /* QUSRJOBI  Date and time job is scheduled to run       */
#define CWBSO_JOB_LanguageId                        0x0042  /* QUSRJOBI                                              */
#define CWBSO_JOB_CountryId                         0x0043  /* QUSRJOBI                                              */
#define CWBSO_JOB_SortSequenceTable                 0x0044  /* QUSRJOBI                                              */
#define CWBSO_JOB_SortSequenceLibrary               0x0045  /* QUSRJOBI                                              */
#define CWBSO_JOB_CCSID                             0x0046  /* QUSRJOBI  Coded character set ID                      */
#define CWBSO_JOB_DefaultCCSID                      0x0047  /* QUSRJOBI  Default coded character set identifier      */
#define CWBSO_JOB_DbcsCapable                       0x0048  /* QUSRJOBI                                              */
#define CWBSO_JOB_NetworkId                         0x0049  /* QUSRJOBI  Unit of work ID                             */
#define CWBSO_JOB_LocationName                      0x004A  /* QUSRJOBI  Unit of work ID                             */
#define CWBSO_JOB_Instance                          0x004B  /* QUSRJOBI  Unit of work ID                             */
#define CWBSO_JOB_SequenceNumber                    0x004C  /* QUSRJOBI  Unit of work ID                             */
#define CWBSO_JOB_Mode                              0x004D  /* QUSRJOBI  Mode name                                   */
#define CWBSO_JOB_DeviceRecoveryAction              0x004E  /* QUSRJOBI                                              */
#define CWBSO_JOB_KeepDDMConnectionsActive          0x004F  /* QUSRJOBI  DDM conversation handling                   */
#define CWBSO_JOB_AccountingCode                    0x0050  /* QUSRJOBI  Job accounting code                         */
#define CWBSO_JOB_ActiveJobStatus                   0x0051  /* QUSRJOBI                                              */
#define CWBSO_JOB_FunctionType                      0x0052  /* QUSRJOBI                                              */
#define CWBSO_JOB_FunctionName                      0x0053  /* QUSRJOBI                                              */
#define CWBSO_JOB_JobQueueStatus                    0x0054  /* QUSRJOBI  Status of job on the job queue              */
#define CWBSO_JOB_JobInformationStatus              0x0055  /* QUSLJOB                                               */
#define CWBSO_JOB_RoutingData                       0x0056  /* QUSRJOBI				                                 */
#define CWBSO_JOB_CurrentSystemPoolId               0x0057  /* QUSRJOBI                                              */
#define CWBSO_JOB_ThreadCount                       0x0058  /* QUSRJOBI                                              */
#define CWBSO_JOB_DecimalFormat                     0x0059  /* QUSRJOBI                                              */
#define CWBSO_JOB_ServerType                        0x005A  /* QUSRJOBI                                              */

/******************************************************************************
*   Job Sort IDs
*
*   Valid values for:
*       - CWBSO_SetListSortFields API
******************************************************************************/
#define CWBSO_JOB_SORT_Name                       CWBSO_JOB_JobName
#define CWBSO_JOB_SORT_User                       CWBSO_JOB_UserName
#define CWBSO_JOB_SORT_Number                     CWBSO_JOB_JobNumber
#define CWBSO_JOB_SORT_Type                       CWBSO_JOB_JobType
#define CWBSO_JOB_SORT_Subtype                    CWBSO_JOB_JobSubtype
#define CWBSO_JOB_SORT_Status                     CWBSO_JOB_JobStatus
#define CWBSO_JOB_SORT_Date                       CWBSO_JOB_DateEnteredSystem
#define CWBSO_JOB_SORT_Time                       CWBSO_JOB_TimeEnteredSystem
#define CWBSO_JOB_SORT_JobQ                       CWBSO_JOB_JobQueueName
#define CWBSO_JOB_SORT_JobQLib                    CWBSO_JOB_JobQueueLibrary
#define CWBSO_JOB_SORT_JobQPriority               CWBSO_JOB_PriorityOnJobQueue
#define CWBSO_JOB_SORT_OutQPriority               CWBSO_JOB_PriorityOnOutputQueue
#define CWBSO_JOB_SORT_RunPriority                CWBSO_JOB_RunPriority
#define CWBSO_JOB_SORT_Sbs                        CWBSO_JOB_SubsystemName
#define CWBSO_JOB_SORT_SbsLib                     CWBSO_JOB_SubsystemLibrary
#define CWBSO_JOB_SORT_PoolId                     CWBSO_JOB_SystemPoolId
#define CWBSO_JOB_SORT_CpuUsed                    CWBSO_JOB_CpuTimeUsed
#define CWBSO_JOB_SORT_AuxIO                      CWBSO_JOB_AuxiliaryIORequests
#define CWBSO_JOB_SORT_Transactions               CWBSO_JOB_InteractiveTransactions
#define CWBSO_JOB_SORT_ResponseTime               CWBSO_JOB_TotalResponseTime

/******************************************************************************
*   Job List Filter Attribute IDs
*
*   Valid values for:
*       - CWBSO_SetListFilter API
*
******************************************************************************/
#define CWBSO_JOBF_JobNameFilter                    0x0000
#define CWBSO_JOBF_JobUserFilter                    0x0001
#define CWBSO_JOBF_JobNumberFilter                  0x0002
#define CWBSO_JOBF_JobTypeFilter                    0x0003
#define CWBSO_JOBF_JobQueueFilter                   0x0006
#define CWBSO_JOBF_JobsOnJobQueueFilter             0x000A
#define CWBSO_JOBF_ActiveJobsFilter                 0x000C
#define CWBSO_JOBF_CompletedJobsFilter              0x000E

// Server Job filter IDs
#define CWBSO_SJOBF_JobNameFilter                   0x0000
#define CWBSO_SJOBF_JobUserFilter                   0x0001
#define CWBSO_SJOBF_JobNumberFilter                 0x0002
#define CWBSO_SJOBF_JobTypeFilter                   0x0003
#define CWBSO_SJOBF_PrimaryStatusFilter             0x0019
#define CWBSO_SJOBF_CurrentUserFilter               0x001D
#define CWBSO_SJOBF_ServerTypeFilter                0x001E
#endif
