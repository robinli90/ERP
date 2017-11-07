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
*   CWBSOSFL.H - Declares for Spooled File Object and Spooled File List
*
*   Flg=Reason   Vers yymmdd UserID     Description
*   ------------ ---- ------ --------   -----------
*   $A1=D97260.5 5D20 011108 rakling  : Support decoupled spooled files
******************************************************************************/

#ifndef _CWBSOSFL_H_
#define _CWBSOSFL_H_

/******************************************************************************
* Bring in common declares
******************************************************************************/
#include "cwbsocmn.h"

/******************************************************************************
*   Spooled File Attribute IDs
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
                                                             /*  API       Name of field (if different)                */
                                                             /* --------   ----------------------------                */
#define CWBSO_SFL_SpooledFileName                   0x0000   /* QUSRSPLA                                               */
#define CWBSO_SFL_JobName                           0x0001   /* QUSRSPLA                                               */
#define CWBSO_SFL_UserName                          0x0002   /* QUSRSPLA                                               */
#define CWBSO_SFL_JobNumber                         0x0003   /* QUSRSPLA                                               */
#define CWBSO_SFL_SpooledFileNumber                 0x0004   /* QUSRSPLA                                               */
#define CWBSO_SFL_OutputQueueName                   0x0005   /* QUSRSPLA                                               */
#define CWBSO_SFL_OutputQueueLibraryName            0x0006   /* QUSRSPLA                                               */
#define CWBSO_SFL_DeviceNames                       0x0007   /* See the appendix of the System Object Access API Guide
                                                                and Reference, Printer Output section                  */
#define CWBSO_SFL_UserSpecifiedData                 0x0008   /* QUSRSPLA                                               */
#define CWBSO_SFL_Status                            0x0009   /* QUSRSPLA                                               */
#define CWBSO_SFL_TotalPages                        0x000A   /* QUSRSPLA                                               */
#define CWBSO_SFL_CurrentPage                       0x000B   /* QUSRSPLA   Page or record being written                */
#define CWBSO_SFL_CopiesLeftToProduce               0x000C   /* QUSRSPLA                                               */
#define CWBSO_SFL_FormType                          0x000D   /* QUSRSPLA                                               */
#define CWBSO_SFL_OutputPriority                    0x000E   /* QUSRSPLA                                               */
#define CWBSO_SFL_DateFileOpened                    0x000F   /* QUSRSPLA                                               */
#define CWBSO_SFL_TimeFileOpened                    0x0010   /* QUSRSPLA                                               */
#define CWBSO_SFL_DeviceType                        0x0011   /* QUSRSPLA                                               */
#define CWBSO_SFL_FileAvailable                     0x0012   /* QUSRSPLA                                               */
#define CWBSO_SFL_HoldFileBeforeWritten             0x0013   /* QUSRSPLA                                               */
#define CWBSO_SFL_SaveFileAfterWritten              0x0014   /* QUSRSPLA                                               */
#define CWBSO_SFL_StartingPage                      0x0015   /* QUSRSPLA                                               */
#define CWBSO_SFL_EndingPage                        0x0016   /* QUSRSPLA                                               */
#define CWBSO_SFL_LastPagePrinted                   0x0017   /* QUSRSPLA                                               */
#define CWBSO_SFL_RestartPrinting                   0x0018   /* QUSRSPLA                                               */
#define CWBSO_SFL_TotalCopies                       0x0019   /* QUSRSPLA                                               */
#define CWBSO_SFL_LinesPerInch                      0x001A   /* QUSRSPLA                                               */
#define CWBSO_SFL_CharactersPerInch                 0x001B   /* QUSRSPLA                                               */
#define CWBSO_SFL_DeviceFileName                    0x001C   /* QUSRSPLA                                               */
#define CWBSO_SFL_DeviceFileLibraryName             0x001D   /* QUSRSPLA                                               */
#define CWBSO_SFL_ProgramThatOpenedFileName         0x001E   /* QUSRSPLA                                               */
#define CWBSO_SFL_ProgramThatOpenedFileLibraryName  0x001F   /* QUSRSPLA                                               */
#define CWBSO_SFL_AccountingCode                    0x0020   /* QUSRSPLA                                               */
#define CWBSO_SFL_RecordLength                      0x0021   /* QUSRSPLA                                               */
#define CWBSO_SFL_MaximumRecords                    0x0022   /* QUSRSPLA                                               */
#define CWBSO_SFL_PrinterDeviceType                 0x0023   /* QUSRSPLA                                               */
#define CWBSO_SFL_PrintFidelity                     0x0024   /* QUSRSPLA                                               */
#define CWBSO_SFL_ReplaceUnprintableCharacters      0x0025   /* QUSRSPLA                                               */
#define CWBSO_SFL_ReplacementCharacter              0x0026   /* QUSRSPLA                                               */
#define CWBSO_SFL_PageLength                        0x0027   /* QUSRSPLA                                               */
#define CWBSO_SFL_PageWidth                         0x0028   /* QUSRSPLA                                               */
#define CWBSO_SFL_NumberOfSeparators                0x0029   /* QUSRSPLA                                               */
#define CWBSO_SFL_OverflowLineNumber                0x002A   /* QUSRSPLA                                               */
#define CWBSO_SFL_DbcsData                          0x002B   /* QUSRSPLA                                               */
#define CWBSO_SFL_DbcsExtensionCharacters           0x002C   /* QUSRSPLA                                               */
#define CWBSO_SFL_DbcsShiftOutShiftIn               0x002D   /* QUSRSPLA   DBCS shift-out shift-in (SO/SI) spacing     */
#define CWBSO_SFL_DbcsCharacterRotation             0x002E   /* QUSRSPLA                                               */
#define CWBSO_SFL_DbcsCharactersPerInch             0x002F   /* QUSRSPLA                                               */
#define CWBSO_SFL_GraphicCharacterSet               0x0030   /* QUSRSPLA                                               */
#define CWBSO_SFL_CodePage                          0x0031   /* QUSRSPLA                                               */
#define CWBSO_SFL_FormDefinitionName                0x0032   /* QUSRSPLA                                               */
#define CWBSO_SFL_FormDefinitionLibraryName         0x0033   /* QUSRSPLA                                               */
#define CWBSO_SFL_SourceDrawer                      0x0034   /* QUSRSPLA                                               */
#define CWBSO_SFL_PrinterFont                       0x0035   /* QUSRSPLA                                               */
#define CWBSO_SFL_PageRotation                      0x0036   /* QUSRSPLA                                               */
#define CWBSO_SFL_Justification                     0x0037   /* QUSRSPLA                                               */
#define CWBSO_SFL_PrintOnBothSides                  0x0038   /* QUSRSPLA   Print on both sides (duplex)                */
#define CWBSO_SFL_FoldRecords                       0x0039   /* QUSRSPLA                                               */
#define CWBSO_SFL_ControlCharacter                  0x003A   /* QUSRSPLA                                               */
#define CWBSO_SFL_AlignForms                        0x003B   /* QUSRSPLA                                               */
#define CWBSO_SFL_PrintQuality                      0x003C   /* QUSRSPLA                                               */
#define CWBSO_SFL_FormFeed                          0x003D   /* QUSRSPLA                                               */
#define CWBSO_SFL_PagesPerSide                      0x003E   /* QUSRSPLA   Multiple up (pages per side)                */
#define CWBSO_SFL_FrontOverlayName                  0x003F   /* QUSRSPLA                                               */
#define CWBSO_SFL_FrontOverlayLibraryName           0x0040   /* QUSRSPLA                                               */
#define CWBSO_SFL_FrontOverlayOffsetDown            0x0041   /* QUSRSPLA                                               */
#define CWBSO_SFL_FrontOverlayOffsetAcross          0x0042   /* QUSRSPLA                                               */
#define CWBSO_SFL_BackOverlayName                   0x0043   /* QUSRSPLA                                               */
#define CWBSO_SFL_BackOverlayLibraryName            0x0044   /* QUSRSPLA                                               */
#define CWBSO_SFL_BackOverlayOffsetDown             0x0045   /* QUSRSPLA                                               */
#define CWBSO_SFL_BackOverlayOffsetAcross           0x0046   /* QUSRSPLA                                               */
#define CWBSO_SFL_UnitOfMeasure                     0x0047   /* QUSRSPLA                                               */
#define CWBSO_SFL_PageDefinitionName                0x0048   /* QUSRSPLA                                               */
#define CWBSO_SFL_PageDefinitionLibraryName         0x0049   /* QUSRSPLA                                               */
#define CWBSO_SFL_LineSpacing                       0x004A   /* QUSRSPLA                                               */
#define CWBSO_SFL_PointSize                         0x004B   /* QUSRSPLA                                               */
#define CWBSO_SFL_FrontMarginOffsetDown             0x004C   /* QUSRSPLA                                               */
#define CWBSO_SFL_FrontMarginOffsetAcross           0x004D   /* QUSRSPLA                                               */
#define CWBSO_SFL_BackMarginOffsetDown              0x004E   /* QUSRSPLA                                               */
#define CWBSO_SFL_BackMarginOffsetAcross            0x004F   /* QUSRSPLA                                               */
#define CWBSO_SFL_LengthOfPage                      0x0050   /* QUSRSPLA                                               */
#define CWBSO_SFL_WidthOfPage                       0x0051   /* QUSRSPLA                                               */
#define CWBSO_SFL_MeasurementMethod                 0x0052   /* QUSRSPLA                                               */
#define CWBSO_SFL_CharacterSetName                  0x0053   /* QUSRSPLA                                               */
#define CWBSO_SFL_CharacterSetLibraryName           0x0054   /* QUSRSPLA                                               */
#define CWBSO_SFL_CodePageName                      0x0055   /* QUSRSPLA                                               */
#define CWBSO_SFL_CodePageLibraryName               0x0056   /* QUSRSPLA                                               */
#define CWBSO_SFL_CodedFontName                     0x0057   /* QUSRSPLA                                               */
#define CWBSO_SFL_CodedFontLibraryName              0x0058   /* QUSRSPLA                                               */
#define CWBSO_SFL_DbcsCodedFontName                 0x0059   /* QUSRSPLA                                               */
#define CWBSO_SFL_DbcsCodedFontLibraryName          0x005A   /* QUSRSPLA                                               */
#define CWBSO_SFL_UserDefinedFile                   0x005B   /* QUSRSPLA                                               */
#define CWBSO_SFL_ReduceOutput                      0x005C   /* QUSRSPLA                                               */
#define CWBSO_SFL_OutputBin                         0x005D   /* QUSRSPLA                                               */
#define CWBSO_SFL_CodedCharacterSetId               0x005E   /* QUSRSPLA   CCSID                                       */
#define CWBSO_SFL_UserSpecifiedText                 0x005F   /* QUSRSPLA   User-defined text                           */
#define CWBSO_SFL_SystemWhereCreated                0x0060   /* QUSRSPLA                                               */
#define CWBSO_SFL_NetworkIdWhereCreated             0x0061   /* QUSRSPLA                                               */
#define CWBSO_SFL_UserWhoCreated                    0x0062   /* QUSRSPLA                                               */
#define CWBSO_SFL_AS400CreatedAFPDS                 0x0063   /* QUSRSPLA                                               */
#define CWBSO_SFL_AdvancedFunctionPrintingResource  0x0064   /* QUSRSPLA   Advanced Function Printing (AFP) resource   */
#define CWBSO_SFL_DefineCharacters                  0x0065   /* QUSRSPLA                                               */
#define CWBSO_SFL_CharacterPerInchChanges           0x0066   /* QUSRSPLA                                               */
#define CWBSO_SFL_Transparency                      0x0067   /* QUSRSPLA                                               */
#define CWBSO_SFL_DoubleWideCharacters              0x0068   /* QUSRSPLA                                               */
#define CWBSO_SFL_DbcsCharacterRotationCommands     0x0069   /* QUSRSPLA                                               */
#define CWBSO_SFL_Extended3812Font                  0x006A   /* QUSRSPLA   3812 SCS                                    */
#define CWBSO_SFL_FieldOutlining                    0x006B   /* QUSRSPLA                                               */
#define CWBSO_SFL_FinalFormText                     0x006C   /* QUSRSPLA                                               */
#define CWBSO_SFL_BarCode                           0x006D   /* QUSRSPLA                                               */
#define CWBSO_SFL_DrawerChange                      0x006E   /* QUSRSPLA                                               */
#define CWBSO_SFL_CharacterId                       0x006F   /* QUSRSPLA                                               */
#define CWBSO_SFL_LinesPerInchChanges               0x0070   /* QUSRSPLA                                               */
#define CWBSO_SFL_VariableFont                      0x0071   /* QUSRSPLA   Font                                        */
#define CWBSO_SFL_Highlight                         0x0072   /* QUSRSPLA                                               */
#define CWBSO_SFL_PageRotate                        0x0073   /* QUSRSPLA                                               */
#define CWBSO_SFL_Subscript                         0x0074   /* QUSRSPLA                                               */
#define CWBSO_SFL_Superscript                       0x0075   /* QUSRSPLA                                               */
#define CWBSO_SFL_Graphics                          0x0076   /* QUSRSPLA                                               */
#define CWBSO_SFL_ASCIITransparency                 0x0077   /* QUSRSPLA                                               */
#define CWBSO_SFL_IPDSTransparentData               0x0078   /* QUSRSPLA                                               */
#define CWBSO_SFL_PrinterAssigned                   0x0079   /* Not documented                                         */
#define CWBSO_SFL_PrinterGroup                      0x007A   /* Not documented                                         */
#define CWBSO_SFL_DateLastAccessed                  0x007B   /*                                                        */
#define CWBSO_SFL_PageCountEstimated                0x007C   /*                                                        */
#define CWBSO_SFL_FileSize                          0x007D   /*                                                        */
#define CWBSO_SFL_SpooledFileSizeMultiplier         0x007E   /*                                                        */
#define CWBSO_SFL_AuxilliaryStoragePool             0x007F   /*                                                        */
#define CWBSO_SFL_CornerStapling                    0x0080   /*                                                        */
#define CWBSO_SFL_ReferenceEdge                     0x0081   /* Edge stitching                                         */
#define CWBSO_SFL_ReferenceEdgeOffset               0x0082   /* Edge stitching                                         */
#define CWBSO_SFL_NumberOfStaples                   0x0083   /* Edge stitching                                         */
                                                             /* 84 - 89 not used                                       */
#define CWBSO_SFL_ReplacementFontResolution         0x008A   /*                                                        */
#define CWBSO_SFL_CodedFontPointSize                0x008B   /*                                                        */
#define CWBSO_SFL_FontCharacterSetPointSize         0x008C   /*                                                        */
#define CWBSO_SFL_DbcsCodedFontPointSize            0x008D   /*                                                        */
                                                             /* 8E - 90 not used                                       */
#define CWBSO_SFL_UserDefinedObject                 0x0091   /*                                                        */
#define CWBSO_SFL_UserDefinedObjectLib              0x0092   /*                                                        */
#define CWBSO_SFL_UserDefinedObjectType             0x0093   /*                                                        */
#define CWBSO_SFL_UserDefinedData                   0x0094   /*                                                        */
#define CWBSO_SFL_AFPCharacters                     0x0095   /*                                                        */
#define CWBSO_SFL_DecimalFormat                     0x0096   /*                                                        */
#define CWBSO_SFL_TableReferenceCharacter           0x0097   /*                                                        */
#define CWBSO_SFL_IPDSPassThrough                   0x0098   /*                                                        */
#define CWBSO_SFL_UserDefinedOptions                0x0099   /*                                                        */
#define CWBSO_SFL_UserResourceLibrary               0x009A   /*                                                        */
#define CWBSO_SFL_StapleOffsets                     0x009B   /*                                                        */
#define CWBSO_SFL_ConstantBack                      0x009C   /*                                                        */
#define CWBSO_SFL_SaddleReferenceEdge               0x009D   /*                                                        */
#define CWBSO_SFL_SaddleNumberOfStaples             0x009E   /*                                                        */
#define CWBSO_SFL_JobSystemName                     0x009F   /*   //@A1A                                                    */


/******************************************************************************
*   Spooled File Sort IDs
*
*   Valid values for:
*       - CWBSO_SetListSortFields API
******************************************************************************/
#define CWBSO_SFL_SORT_FileName                CWBSO_SFL_SpooledFileName
#define CWBSO_SFL_SORT_JobName                 CWBSO_SFL_JobName
#define CWBSO_SFL_SORT_UserName                CWBSO_SFL_UserName
#define CWBSO_SFL_SORT_JobNumber               CWBSO_SFL_JobNumber
#define CWBSO_SFL_SORT_FileNumber              CWBSO_SFL_SpooledFileNumber
#define CWBSO_SFL_SORT_OutQ                    CWBSO_SFL_OutputQueueName
#define CWBSO_SFL_SORT_OutQLib                 CWBSO_SFL_OutputQueueLibraryName
#define CWBSO_SFL_SORT_Printer                 CWBSO_SFL_DeviceNames
#define CWBSO_SFL_SORT_UserData                CWBSO_SFL_UserSpecifiedData
#define CWBSO_SFL_SORT_Status                  CWBSO_SFL_Status
#define CWBSO_SFL_SORT_Pages                   CWBSO_SFL_TotalPages
#define CWBSO_SFL_SORT_Copies                  CWBSO_SFL_CopiesLeftToProduce
#define CWBSO_SFL_SORT_FormType                CWBSO_SFL_FormType
#define CWBSO_SFL_SORT_Priority                CWBSO_SFL_OutputPriority
#define CWBSO_SFL_SORT_Date                    CWBSO_SFL_DateFileOpened
#define CWBSO_SFL_SORT_Time                    CWBSO_SFL_TimeFileOpened

/******************************************************************************
*   Spooled File List Filter Attribute IDs
*
*   Valid values for:
*       - CWBSO_SetListFilter API
*
******************************************************************************/
#define CWBSO_SFLF_UserFilter                       0x0001
#define CWBSO_SFLF_OutputQueueFilter                0x0003
#define CWBSO_SFLF_FormTypeFilter                   0x0004
#define CWBSO_SFLF_UserDataFilter                   0x0005
#define CWBSO_SFLF_StatusFilter                     0x0007
#define CWBSO_SFLF_DeviceFilter                     0x0009
#define CWBSO_SFLF_JobNameFilter                    0x000A

#endif
