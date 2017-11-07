/********************************************************************/
/* Copyright = 5763-XE1 (C) Copyright IBM Corp 1994, 2005.          */
/*  All rights reserved.                                            */
/*  Licensed Material - Program property of IBM                     */
/*  Refer to copyright instructions form number G120-2083.          */
/********************************************************************/
//********************************************************************
//
// File:
//   CWBA4SVL.H
//
// Purpose:
//   Contains system value IDs for the cwbUN_GetSystemValue
//   service that is provided to assist in the implementation of
//   Operations Navigator extensions.
//
// Usage Notes:
//   See CWBUN.H for details about the cwbUN_GetSystemValue API.
//
//********************************************************************

#ifndef _CWBA4SVL_H_
#define _CWBA4SVL_H_

//*****************************************************************************
// System value IDs
//*****************************************************************************

#define CWBSO_SVL_SysValNumber                           0x0000
#define CWBSO_SVL_StatusOfQSRTSEQ                        0x0001
#define CWBSO_SVL_SortSequenceTableName                  0x0002
#define CWBSO_SVL_SortSequenceTableLibrary               0x0003
#define CWBSO_SVL_StatusOfQSETJOBATR                     0x0004
#define CWBSO_SVL_SetJobAttributesFromLocale             0x0005
#define CWBSO_SVL_StatusOfQSECURITY                      0x0006
#define CWBSO_SVL_SecurityLevel                          0x0007
#define CWBSO_SVL_StatusOfQRMTSIGN                       0x0008
#define CWBSO_SVL_RemoteSignOnName                       0x0009
#define CWBSO_SVL_RemoteSignOnLibrary                    0x000a
#define CWBSO_SVL_StatusOfQRMTSRVATR                     0x000b
#define CWBSO_SVL_RemoteServiceAttribute                 0x000c
#define CWBSO_SVL_StatusOfQRETSVRSEC                     0x000d
#define CWBSO_SVL_RetainServerSecurity                   0x000e
#define CWBSO_SVL_StatusOfQPWDVLDPGM                     0x000f
#define CWBSO_SVL_PasswordValidationProgramName          0x0010
#define CWBSO_SVL_PasswordValidationProgramLibrary       0x0011
#define CWBSO_SVL_StatusOfQPWDRQDDIF                     0x0012
#define CWBSO_SVL_DuplicatePassword                      0x0013
#define CWBSO_SVL_StatusOfQPWDRQDDGT                     0x0014
#define CWBSO_SVL_RequiredPasswordDigits                 0x0015
#define CWBSO_SVL_StatusOfQPWDPOSDIF                     0x0016
#define CWBSO_SVL_LimitCharacterPositions                0x0017
#define CWBSO_SVL_StatusOfQPWDMINLEN                     0x0018
#define CWBSO_SVL_MinPasswordLength                      0x0019
#define CWBSO_SVL_StatusOfQPWDMAXLEN                     0x001a
#define CWBSO_SVL_MaxPasswordLength                      0x001b
#define CWBSO_SVL_StatusOfQPWDLMTREP                     0x001c
#define CWBSO_SVL_LimitRepeatCharacters                  0x001d
#define CWBSO_SVL_StatusOfQPWDLMTCHR                     0x001e
#define CWBSO_SVL_LimitCharacters                        0x001f
#define CWBSO_SVL_StatusOfQPWDLMTAJC                     0x0020
#define CWBSO_SVL_LimitAdjacentDigits                    0x0021
#define CWBSO_SVL_StatusOfQPWDEXPITV                     0x0022
#define CWBSO_SVL_DaysPasswordValid                      0x0023
#define CWBSO_SVL_StatusOfQPRTDEV                        0x0024
#define CWBSO_SVL_PrinterDevice                          0x0025
#define CWBSO_SVL_StatusOfQMAXSIGN                       0x0026
#define CWBSO_SVL_MaxNotValidSignOn                      0x0027
#define CWBSO_SVL_StatusOfQMAXSGNACN                     0x0028
#define CWBSO_SVL_MaxSignOnAction                        0x0029
#define CWBSO_SVL_StatusOfQCLOCALE                       0x002a
#define CWBSO_SVL_LocalePathNameDelimiter                0x002b
#define CWBSO_SVL_LocalePathName                         0x002c
#define CWBSO_SVL_StatusOfQLMTSECOFR                     0x002d
#define CWBSO_SVL_LimitSecurityOfficer                   0x002e
#define CWBSO_SVL_StatusOfQLMTDEVSSN                     0x002f
#define CWBSO_SVL_LimitDeviceSession                     0x0030
#define CWBSO_SVL_StatusOfQLANGID                        0x0031
#define CWBSO_SVL_LanguageID                             0x0032
#define CWBSO_SVL_StatusOfQKBDBUF                        0x0033
#define CWBSO_SVL_KeyboardBuffer                         0x0034
#define CWBSO_SVL_StatusOfQINACTMSGQ                     0x0035
#define CWBSO_SVL_InactiveMessageQueueName               0x0036
#define CWBSO_SVL_InactiveMessageQueueLibrary            0x0037
#define CWBSO_SVL_StatusOfQINACTITV                      0x0038
#define CWBSO_SVL_InactiveJobTimeOut                     0x0039
#define CWBSO_SVL_StatusOfQDSPSGNINF                     0x003a
#define CWBSO_SVL_SignOnInfo                             0x003b
#define CWBSO_SVL_StatusOfQDSCJOBITV                     0x003c
#define CWBSO_SVL_DisconnectJobInterval                  0x003d
#define CWBSO_SVL_StatusOfQDEVRCYACN                     0x003e
#define CWBSO_SVL_DeviceRecoveryAction                   0x003f
#define CWBSO_SVL_StatusOfQCRTOBJAUD                     0x0040
#define CWBSO_SVL_CreateObjectAuditing                   0x0041
#define CWBSO_SVL_StatusOfQCRTAUT                        0x0042
#define CWBSO_SVL_CreateAuthority                        0x0043
#define CWBSO_SVL_StatusOfQCNTRYID                       0x0044
#define CWBSO_SVL_CountryID                              0x0045
#define CWBSO_SVL_StatusOfQCCSID                         0x0046
#define CWBSO_SVL_CodedCharSetID                         0x0047
#define CWBSO_SVL_StatusOfQAUTOVRT                       0x0048
#define CWBSO_SVL_AutoConfigVirtualDevices               0x0049
#define CWBSO_SVL_StatusOfQAUTOCFG                       0x004a
#define CWBSO_SVL_AutoConfigIndicator                    0x004b
#define CWBSO_SVL_StatusOfQAUDLVL                        0x004c
#define CWBSO_SVL_AuditingLevel                          0x004d
#define CWBSO_SVL_StatusOfQAUDCTL                        0x004e
#define CWBSO_SVL_AuditingControl                        0x004f
#define CWBSO_SVL_StatusOfQATNPGM                        0x0050
#define CWBSO_SVL_AttentionProgramName                   0x0051
#define CWBSO_SVL_AttentionProgramLibrary                0x0052
#define CWBSO_SVL_StatusOfQASTLVL                        0x0053
#define CWBSO_SVL_AssistanceLevel                        0x0054
#define CWBSO_SVL_StatusOfQALWUSRDMN                     0x0055
#define CWBSO_SVL_AllowUserDomain                        0x0056
#define CWBSO_SVL_StatusOfQALWOBJRST                     0x0057
#define CWBSO_SVL_AllowObjectRestore                     0x0058

#define CWBSO_SVL_LastAttribute                          0x0058

#endif
