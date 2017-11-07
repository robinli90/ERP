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
* (C) Copyright IBM Corp. 1995, 2005                                         
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
*   cwbsousr.h
*
* Purpose:
*   Define the attribute ids for the User subclass.
*
******************************************************************************/

#ifndef _CWBSOUSR_H_
#define _CWBSOUSR_H_

/******************************************************************************
* Bring in common error codes and action codes
******************************************************************************/
#include "cwbsocmn.h"
#include "cwbsoprf.h"

/******************************************************************************
* Attribute ids
******************************************************************************/
#define CWBSO_USR_ProfileName                                 CWBSO_PRF_ProfileName
#define CWBSO_USR_ProfileOrGroupIndicator                     CWBSO_PRF_ProfileOrGroupIndicator
#define CWBSO_USR_GroupHasMembers                             CWBSO_PRF_GroupHasMembers
#define CWBSO_USR_TextDescription                             CWBSO_PRF_TextDescription
#define CWBSO_USR_PreviousSignonDate                          0x0004
#define CWBSO_USR_PreviousSignonTime                          0x0005
#define CWBSO_USR_SignonAttemptsNotValid                      0x0006
#define CWBSO_USR_Status                                      0x0007
// Obsolete								                      0x0008
#define CWBSO_USR_NoPasswordIndicator                         0x0009
#define CWBSO_USR_PasswordExpirationInterval                  0x000a
// Obsolete													  0x000b
#define CWBSO_USR_DaysUntilPasswordExpires                    0x000c
#define CWBSO_USR_SetPasswordToExpire                         0x000d
#define CWBSO_USR_DisplaySignonInformation                    0x000e
#define CWBSO_USR_UserClassName                               0x000f
#define CWBSO_USR_AllObjectAccess                             0x0010
#define CWBSO_USR_SecurityAdministration                      0x0011
#define CWBSO_USR_JobControl                                  0x0012
#define CWBSO_USR_SpoolControl                                0x0013
#define CWBSO_USR_SaveAndRestore                              0x0014
#define CWBSO_USR_SystemServiceAccess                         0x0015
#define CWBSO_USR_AuditingControl                             0x0016
#define CWBSO_USR_SystemConfiguration                         0x0017
#define CWBSO_USR_GroupProfileName                            0x0018
#define CWBSO_USR_Owner                                       0x0019
#define CWBSO_USR_GroupAuthority                              0x001a
#define CWBSO_USR_LimitCapabilities                           0x001b
#define CWBSO_USR_GroupAuthorityType                          0x001c
#define CWBSO_USR_SupplementalGroups                          0x001d
#define CWBSO_USR_AssistanceLevel                             0x001e
#define CWBSO_USR_CurrentLibraryName                          0x001f
#define CWBSO_USR_InitialMenuName                             0x0020
#define CWBSO_USR_InitialMenuLibraryName                      0x0021
#define CWBSO_USR_InitialProgramName                          0x0022
#define CWBSO_USR_InitialProgramLibraryName                   0x0023
#define CWBSO_USR_LimitDeviceSessions                         0x0024
#define CWBSO_USR_KeyboardBuffering                           0x0025
#define CWBSO_USR_MaximumAllowedStorage                       0x0026
#define CWBSO_USR_StorageUsed                                 0x0027
#define CWBSO_USR_HighestSchedulingPriority                   0x0028
#define CWBSO_USR_JobDescriptionName                          0x0029
#define CWBSO_USR_JobDescriptionNameLibrary                   0x002a
#define CWBSO_USR_AccountingCode                              0x002b
#define CWBSO_USR_MessageQueueName                            0x002c
#define CWBSO_USR_MessageQueueLibraryName                     0x002d
#define CWBSO_USR_MessageQueueDeliveryMethod                  0x002e
#define CWBSO_USR_MessageQueueSeverity                        0x002f
#define CWBSO_USR_OutputQueue                                 0x0030
#define CWBSO_USR_OutputQueueLibrary                          0x0031
#define CWBSO_USR_PrintDevice                                 0x0032
#define CWBSO_USR_SpecialEnvironment                          0x0033
#define CWBSO_USR_AttentionKeyHandlingProgramName             0x0034
#define CWBSO_USR_AttentionKeyHandlingProgramLibrary          0x0035
#define CWBSO_USR_LanguageID                                  0x0036
#define CWBSO_USR_CountryID                                   0x0037
#define CWBSO_USR_CharacterCodeSetID                          0x0038
#define CWBSO_USR_ShowParameterKeywords                       0x0039
#define CWBSO_USR_ShowAllDetails                              0x003a
#define CWBSO_USR_DisplayHelpOnFullScreen                     0x003b
#define CWBSO_USR_ShowStatusMessages                          0x003c
#define CWBSO_USR_DoNotShowStatusMessages                     0x003d
#define CWBSO_USR_ChangeDirectionOfRollkey                    0x003e
#define CWBSO_USR_SendMessageToSpoolFileOwner                 0x003f
#define CWBSO_USR_SortSequenceTableName                       0x0040
#define CWBSO_USR_SortSequenceTableLibraryName                0x0041
#define CWBSO_USR_DigitalCertificateIndicator			      0x0042	
#define CWBSO_USR_CharacterIDControl			              0x0043	
#define CWBSO_USR_ObjectAuditValue                            0x0044
#define CWBSO_USR_CommandUsage                                0x0045
#define CWBSO_USR_ObjectCreation                              0x0046
#define CWBSO_USR_ObjectDeletion                              0x0047
#define CWBSO_USR_JobTasks                                    0x0048
#define CWBSO_USR_ObjectManagement                            0x0049
#define CWBSO_USR_OfficeTasks                                 0x004a
#define CWBSO_USR_ProgramAdoption                             0x004b
#define CWBSO_USR_SaveAndRestoreTasks                         0x004c
#define CWBSO_USR_SecurityTasks                               0x004d
#define CWBSO_USR_ServiceTasks                                0x004e
#define CWBSO_USR_SpoolManagement                             0x004f
#define CWBSO_USR_SystemManagement                            0x0050
#define CWBSO_USR_OpticalTasks                                0x0051
#define CWBSO_USR_UserIDNumber                                0x0052
#define CWBSO_USR_GroupIDNumber                               0x0053 
#define CWBSO_USR_DoNotSetAnyJobAttributes                    0x0054
#define CWBSO_USR_UseSystemValue                              0x0055
#define CWBSO_USR_CodedCharacterSetID                         0x0056
#define CWBSO_USR_DateFormat                                  0x0057
#define CWBSO_USR_DateSeparator                               0x0058
#define CWBSO_USR_SortSequenceTable                           0x0059
#define CWBSO_USR_TimeSeparator                               0x005a
#define CWBSO_USR_DecimalFormat                               0x005b
#define CWBSO_USR_HomeDirectoryDelimiter                      0x005c
#define CWBSO_USR_HomeDirectory                               0x005d
#define CWBSO_USR_Locale                                      0x005e
#define CWBSO_USR_IndirectUser                                0x005f
#define CWBSO_USR_PrintCoverPage                              0x0060
#define CWBSO_USR_MailNotification                            0x0061
#define CWBSO_USR_UserID                                      0x0062
#define CWBSO_USR_LocalDataIndicator                          0x0063
#define CWBSO_USR_UserAddress                                 0x0064
#define CWBSO_USR_SystemName                                  0x0065
#define CWBSO_USR_SystemGroup                                 0x0066
#define CWBSO_USR_UserDescription                             0x0067
#define CWBSO_USR_FirstName                                   0x0068
#define CWBSO_USR_PreferredName                               0x0069
#define CWBSO_USR_MiddleName                                  0x006a
#define CWBSO_USR_LastName                                    0x006b
#define CWBSO_USR_FullName                                    0x006c
#define CWBSO_USR_JobTitle                                    0x006d
#define CWBSO_USR_CompanyName                                 0x006e
#define CWBSO_USR_DepartmentName                              0x006f
#define CWBSO_USR_NetworkUserID                               0x0070
#define CWBSO_USR_PrimaryTelephoneNumber                      0x0071
#define CWBSO_USR_SecondaryTelephoneNumber                    0x0072
#define CWBSO_USR_FaxNumber                                   0x0073
#define CWBSO_USR_Location                                    0x0074
#define CWBSO_USR_BuildingNumber                              0x0075
#define CWBSO_USR_OfficeNumber                                0x0076
#define CWBSO_USR_MailingAddress                              0x0077
#define CWBSO_USR_MailingAddress2                             0x0078
#define CWBSO_USR_MailingAddress3                             0x0079
#define CWBSO_USR_MailingAddress4                             0x007a
#define CWBSO_USR_CCMailAddress                               0x007b
#define CWBSO_USR_CCMailComment                               0x007c
#define CWBSO_USR_MailServerFrameworkServiceLevel             0x007d
#define CWBSO_USR_PreferredAddressFieldName                   0x007e
#define CWBSO_USR_PreferredAddressProductID                   0x007f
#define CWBSO_USR_PreferredAddressTypeValue                   0x0080
#define CWBSO_USR_PreferredAddressTypeName                    0x0081
#define CWBSO_USR_PreferredAddress                            0x0082
#define CWBSO_USR_ManagerCode                                 0x0083
#define CWBSO_USR_SMTPUserID                                  0x0084
#define CWBSO_USR_SMTPDomain                                  0x0085
#define CWBSO_USR_SMTPRoute                                   0x0086
/*******************************************************************
* NOTE: 
* 
* In release/version V4R4 and above, the following attributes are
* only meaningful when Lotus Notes is installed on the AS/400:
* 
* 0x0087 -- 0x0099
*
*******************************************************************/
#define CWBSO_USR_NotesServerName                             0x0087
#define CWBSO_USR_NotesCertifierID                            0x0088
#define CWBSO_USR_MailType                                    0x0089
#define CWBSO_USR_NotesMailFileName                           0x008a
#define CWBSO_USR_CreateMailFiles                             0x008b
#define CWBSO_USR_NotesForwardingAddress                      0x008c
#define CWBSO_USR_SecurityType                                0x008d
#define CWBSO_USR_LicenseType                                 0x008e
#define CWBSO_USR_MinimumNotesPasswordLength                  0x008f
#define CWBSO_USR_UpdateExistingNotesUser                     0x0090
#define CWBSO_USR_NotesMailServer                             0x0091
#define CWBSO_USR_LocationWhereUserIDIsStored                 0x0092
#define CWBSO_USR_ReplaceExistingNotesID                      0x0093
#define CWBSO_USR_NotesComment                                0x0094
#define CWBSO_USR_NotesUserLocation                           0x0095
#define CWBSO_USR_UserPassword                                0x0096
#define CWBSO_USR_NotesUserPassword                           0x0097
#define CWBSO_USR_NotesCertifierPassword                      0x0098
#define CWBSO_USR_ShortName                                   0x0099
/*******************************************************************
* END NOTE: 
*******************************************************************/
#define CWBSO_USR_PasswordChangeDate                          0x009a
#define CWBSO_USR_PasswordChangeDateFmt                       0x009b
#define CWBSO_USR_PasswordChangeTimeFmt                       0x009c
#define CWBSO_USR_DatePasswordExpires			              0x009d
#define CWBSO_USR_DatePasswordExpiresFmt                      0x009e
#define CWBSO_USR_TimePasswordExpiresFmt                      0x009f

#define CWBSO_USR_LocalPasswordManagement					  0x00A0


#define CWBSO_USR_LastAttribute                               0x00A0

#endif
