
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Fri Mar 02 16:46:46 2007
 */
/* Compiler settings for cwbx.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __cwbx_h__
#define __cwbx_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IcwbxDatabaseDownloadRequest_FWD_DEFINED__
#define __IcwbxDatabaseDownloadRequest_FWD_DEFINED__
typedef interface IcwbxDatabaseDownloadRequest IcwbxDatabaseDownloadRequest;
#endif 	/* __IcwbxDatabaseDownloadRequest_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseUploadRequest_FWD_DEFINED__
#define __IcwbxDatabaseUploadRequest_FWD_DEFINED__
typedef interface IcwbxDatabaseUploadRequest IcwbxDatabaseUploadRequest;
#endif 	/* __IcwbxDatabaseUploadRequest_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseUploadBIFFOptions_FWD_DEFINED__
#define __IcwbxDatabaseUploadBIFFOptions_FWD_DEFINED__
typedef interface IcwbxDatabaseUploadBIFFOptions IcwbxDatabaseUploadBIFFOptions;
#endif 	/* __IcwbxDatabaseUploadBIFFOptions_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadPCOptions_FWD_DEFINED__
#define __IcwbxDatabaseDownloadPCOptions_FWD_DEFINED__
typedef interface IcwbxDatabaseDownloadPCOptions IcwbxDatabaseDownloadPCOptions;
#endif 	/* __IcwbxDatabaseDownloadPCOptions_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadASCIIOptions_FWD_DEFINED__
#define __IcwbxDatabaseDownloadASCIIOptions_FWD_DEFINED__
typedef interface IcwbxDatabaseDownloadASCIIOptions IcwbxDatabaseDownloadASCIIOptions;
#endif 	/* __IcwbxDatabaseDownloadASCIIOptions_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadTabDelimitedOptions_FWD_DEFINED__
#define __IcwbxDatabaseDownloadTabDelimitedOptions_FWD_DEFINED__
typedef interface IcwbxDatabaseDownloadTabDelimitedOptions IcwbxDatabaseDownloadTabDelimitedOptions;
#endif 	/* __IcwbxDatabaseDownloadTabDelimitedOptions_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadBIFFOptions_FWD_DEFINED__
#define __IcwbxDatabaseDownloadBIFFOptions_FWD_DEFINED__
typedef interface IcwbxDatabaseDownloadBIFFOptions IcwbxDatabaseDownloadBIFFOptions;
#endif 	/* __IcwbxDatabaseDownloadBIFFOptions_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadWK4Options_FWD_DEFINED__
#define __IcwbxDatabaseDownloadWK4Options_FWD_DEFINED__
typedef interface IcwbxDatabaseDownloadWK4Options IcwbxDatabaseDownloadWK4Options;
#endif 	/* __IcwbxDatabaseDownloadWK4Options_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseDownload123Options_FWD_DEFINED__
#define __IcwbxDatabaseDownload123Options_FWD_DEFINED__
typedef interface IcwbxDatabaseDownload123Options IcwbxDatabaseDownload123Options;
#endif 	/* __IcwbxDatabaseDownload123Options_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadHTMLOptions_FWD_DEFINED__
#define __IcwbxDatabaseDownloadHTMLOptions_FWD_DEFINED__
typedef interface IcwbxDatabaseDownloadHTMLOptions IcwbxDatabaseDownloadHTMLOptions;
#endif 	/* __IcwbxDatabaseDownloadHTMLOptions_FWD_DEFINED__ */


#ifndef __IcwbxSystem_FWD_DEFINED__
#define __IcwbxSystem_FWD_DEFINED__
typedef interface IcwbxSystem IcwbxSystem;
#endif 	/* __IcwbxSystem_FWD_DEFINED__ */


#ifndef __IcwbxSystemNames_FWD_DEFINED__
#define __IcwbxSystemNames_FWD_DEFINED__
typedef interface IcwbxSystemNames IcwbxSystemNames;
#endif 	/* __IcwbxSystemNames_FWD_DEFINED__ */


#ifndef __IcwbxClientInfo_FWD_DEFINED__
#define __IcwbxClientInfo_FWD_DEFINED__
typedef interface IcwbxClientInfo IcwbxClientInfo;
#endif 	/* __IcwbxClientInfo_FWD_DEFINED__ */


#ifndef __IcwbxDataQueue_FWD_DEFINED__
#define __IcwbxDataQueue_FWD_DEFINED__
typedef interface IcwbxDataQueue IcwbxDataQueue;
#endif 	/* __IcwbxDataQueue_FWD_DEFINED__ */


#ifndef __IcwbxKeyedDataQueue_FWD_DEFINED__
#define __IcwbxKeyedDataQueue_FWD_DEFINED__
typedef interface IcwbxKeyedDataQueue IcwbxKeyedDataQueue;
#endif 	/* __IcwbxKeyedDataQueue_FWD_DEFINED__ */


#ifndef __IcwbxDataQueueAttributes_FWD_DEFINED__
#define __IcwbxDataQueueAttributes_FWD_DEFINED__
typedef interface IcwbxDataQueueAttributes IcwbxDataQueueAttributes;
#endif 	/* __IcwbxDataQueueAttributes_FWD_DEFINED__ */


#ifndef __IcwbxDataQueueSenderInfo_FWD_DEFINED__
#define __IcwbxDataQueueSenderInfo_FWD_DEFINED__
typedef interface IcwbxDataQueueSenderInfo IcwbxDataQueueSenderInfo;
#endif 	/* __IcwbxDataQueueSenderInfo_FWD_DEFINED__ */


#ifndef __IcwbxProgram_FWD_DEFINED__
#define __IcwbxProgram_FWD_DEFINED__
typedef interface IcwbxProgram IcwbxProgram;
#endif 	/* __IcwbxProgram_FWD_DEFINED__ */


#ifndef __IcwbxProgramParameter_FWD_DEFINED__
#define __IcwbxProgramParameter_FWD_DEFINED__
typedef interface IcwbxProgramParameter IcwbxProgramParameter;
#endif 	/* __IcwbxProgramParameter_FWD_DEFINED__ */


#ifndef __IcwbxProgramParameters_FWD_DEFINED__
#define __IcwbxProgramParameters_FWD_DEFINED__
typedef interface IcwbxProgramParameters IcwbxProgramParameters;
#endif 	/* __IcwbxProgramParameters_FWD_DEFINED__ */


#ifndef __IcwbxCommand_FWD_DEFINED__
#define __IcwbxCommand_FWD_DEFINED__
typedef interface IcwbxCommand IcwbxCommand;
#endif 	/* __IcwbxCommand_FWD_DEFINED__ */


#ifndef __IcwbxPackedConverter_FWD_DEFINED__
#define __IcwbxPackedConverter_FWD_DEFINED__
typedef interface IcwbxPackedConverter IcwbxPackedConverter;
#endif 	/* __IcwbxPackedConverter_FWD_DEFINED__ */


#ifndef __IcwbxZonedConverter_FWD_DEFINED__
#define __IcwbxZonedConverter_FWD_DEFINED__
typedef interface IcwbxZonedConverter IcwbxZonedConverter;
#endif 	/* __IcwbxZonedConverter_FWD_DEFINED__ */


#ifndef __IcwbxShortConverter_FWD_DEFINED__
#define __IcwbxShortConverter_FWD_DEFINED__
typedef interface IcwbxShortConverter IcwbxShortConverter;
#endif 	/* __IcwbxShortConverter_FWD_DEFINED__ */


#ifndef __IcwbxLongConverter_FWD_DEFINED__
#define __IcwbxLongConverter_FWD_DEFINED__
typedef interface IcwbxLongConverter IcwbxLongConverter;
#endif 	/* __IcwbxLongConverter_FWD_DEFINED__ */


#ifndef __IcwbxDoubleConverter_FWD_DEFINED__
#define __IcwbxDoubleConverter_FWD_DEFINED__
typedef interface IcwbxDoubleConverter IcwbxDoubleConverter;
#endif 	/* __IcwbxDoubleConverter_FWD_DEFINED__ */


#ifndef __IcwbxFloatConverter_FWD_DEFINED__
#define __IcwbxFloatConverter_FWD_DEFINED__
typedef interface IcwbxFloatConverter IcwbxFloatConverter;
#endif 	/* __IcwbxFloatConverter_FWD_DEFINED__ */


#ifndef __IcwbxStringConverter_FWD_DEFINED__
#define __IcwbxStringConverter_FWD_DEFINED__
typedef interface IcwbxStringConverter IcwbxStringConverter;
#endif 	/* __IcwbxStringConverter_FWD_DEFINED__ */


#ifndef __IcwbxCodePageConverter_FWD_DEFINED__
#define __IcwbxCodePageConverter_FWD_DEFINED__
typedef interface IcwbxCodePageConverter IcwbxCodePageConverter;
#endif 	/* __IcwbxCodePageConverter_FWD_DEFINED__ */


#ifndef __IcwbxStructure_FWD_DEFINED__
#define __IcwbxStructure_FWD_DEFINED__
typedef interface IcwbxStructure IcwbxStructure;
#endif 	/* __IcwbxStructure_FWD_DEFINED__ */


#ifndef __IcwbxBinaryData_FWD_DEFINED__
#define __IcwbxBinaryData_FWD_DEFINED__
typedef interface IcwbxBinaryData IcwbxBinaryData;
#endif 	/* __IcwbxBinaryData_FWD_DEFINED__ */


#ifndef __IcwbxStructureField_FWD_DEFINED__
#define __IcwbxStructureField_FWD_DEFINED__
typedef interface IcwbxStructureField IcwbxStructureField;
#endif 	/* __IcwbxStructureField_FWD_DEFINED__ */


#ifndef __IcwbxStructureFields_FWD_DEFINED__
#define __IcwbxStructureFields_FWD_DEFINED__
typedef interface IcwbxStructureFields IcwbxStructureFields;
#endif 	/* __IcwbxStructureFields_FWD_DEFINED__ */


#ifndef __IcwbxError_FWD_DEFINED__
#define __IcwbxError_FWD_DEFINED__
typedef interface IcwbxError IcwbxError;
#endif 	/* __IcwbxError_FWD_DEFINED__ */


#ifndef __IcwbxErrors_FWD_DEFINED__
#define __IcwbxErrors_FWD_DEFINED__
typedef interface IcwbxErrors IcwbxErrors;
#endif 	/* __IcwbxErrors_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseTransfer_FWD_DEFINED__
#define __IcwbxDatabaseTransfer_FWD_DEFINED__
typedef interface IcwbxDatabaseTransfer IcwbxDatabaseTransfer;
#endif 	/* __IcwbxDatabaseTransfer_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadRequest2_FWD_DEFINED__
#define __IcwbxDatabaseDownloadRequest2_FWD_DEFINED__
typedef interface IcwbxDatabaseDownloadRequest2 IcwbxDatabaseDownloadRequest2;
#endif 	/* __IcwbxDatabaseDownloadRequest2_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadRequestEvents_FWD_DEFINED__
#define __IcwbxDatabaseDownloadRequestEvents_FWD_DEFINED__
typedef interface IcwbxDatabaseDownloadRequestEvents IcwbxDatabaseDownloadRequestEvents;
#endif 	/* __IcwbxDatabaseDownloadRequestEvents_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseUploadRequest2_FWD_DEFINED__
#define __IcwbxDatabaseUploadRequest2_FWD_DEFINED__
typedef interface IcwbxDatabaseUploadRequest2 IcwbxDatabaseUploadRequest2;
#endif 	/* __IcwbxDatabaseUploadRequest2_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseUploadRequestEvents_FWD_DEFINED__
#define __IcwbxDatabaseUploadRequestEvents_FWD_DEFINED__
typedef interface IcwbxDatabaseUploadRequestEvents IcwbxDatabaseUploadRequestEvents;
#endif 	/* __IcwbxDatabaseUploadRequestEvents_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseQuerySettings_FWD_DEFINED__
#define __IcwbxDatabaseQuerySettings_FWD_DEFINED__
typedef interface IcwbxDatabaseQuerySettings IcwbxDatabaseQuerySettings;
#endif 	/* __IcwbxDatabaseQuerySettings_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseFormatOptions_FWD_DEFINED__
#define __IcwbxDatabaseFormatOptions_FWD_DEFINED__
typedef interface IcwbxDatabaseFormatOptions IcwbxDatabaseFormatOptions;
#endif 	/* __IcwbxDatabaseFormatOptions_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseAS400File_FWD_DEFINED__
#define __IcwbxDatabaseAS400File_FWD_DEFINED__
typedef interface IcwbxDatabaseAS400File IcwbxDatabaseAS400File;
#endif 	/* __IcwbxDatabaseAS400File_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseUploadPCFile_FWD_DEFINED__
#define __IcwbxDatabaseUploadPCFile_FWD_DEFINED__
typedef interface IcwbxDatabaseUploadPCFile IcwbxDatabaseUploadPCFile;
#endif 	/* __IcwbxDatabaseUploadPCFile_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseUploadPCOptions_FWD_DEFINED__
#define __IcwbxDatabaseUploadPCOptions_FWD_DEFINED__
typedef interface IcwbxDatabaseUploadPCOptions IcwbxDatabaseUploadPCOptions;
#endif 	/* __IcwbxDatabaseUploadPCOptions_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseUploadASCIIOptions_FWD_DEFINED__
#define __IcwbxDatabaseUploadASCIIOptions_FWD_DEFINED__
typedef interface IcwbxDatabaseUploadASCIIOptions IcwbxDatabaseUploadASCIIOptions;
#endif 	/* __IcwbxDatabaseUploadASCIIOptions_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseUploadUnicodeOptions_FWD_DEFINED__
#define __IcwbxDatabaseUploadUnicodeOptions_FWD_DEFINED__
typedef interface IcwbxDatabaseUploadUnicodeOptions IcwbxDatabaseUploadUnicodeOptions;
#endif 	/* __IcwbxDatabaseUploadUnicodeOptions_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseUploadBIFFOptions2_FWD_DEFINED__
#define __IcwbxDatabaseUploadBIFFOptions2_FWD_DEFINED__
typedef interface IcwbxDatabaseUploadBIFFOptions2 IcwbxDatabaseUploadBIFFOptions2;
#endif 	/* __IcwbxDatabaseUploadBIFFOptions2_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseUploadWK4Options_FWD_DEFINED__
#define __IcwbxDatabaseUploadWK4Options_FWD_DEFINED__
typedef interface IcwbxDatabaseUploadWK4Options IcwbxDatabaseUploadWK4Options;
#endif 	/* __IcwbxDatabaseUploadWK4Options_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseUploadExcelXMLOptions_FWD_DEFINED__
#define __IcwbxDatabaseUploadExcelXMLOptions_FWD_DEFINED__
typedef interface IcwbxDatabaseUploadExcelXMLOptions IcwbxDatabaseUploadExcelXMLOptions;
#endif 	/* __IcwbxDatabaseUploadExcelXMLOptions_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseUpload123Options_FWD_DEFINED__
#define __IcwbxDatabaseUpload123Options_FWD_DEFINED__
typedef interface IcwbxDatabaseUpload123Options IcwbxDatabaseUpload123Options;
#endif 	/* __IcwbxDatabaseUpload123Options_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadPCFile_FWD_DEFINED__
#define __IcwbxDatabaseDownloadPCFile_FWD_DEFINED__
typedef interface IcwbxDatabaseDownloadPCFile IcwbxDatabaseDownloadPCFile;
#endif 	/* __IcwbxDatabaseDownloadPCFile_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadPCOptions2_FWD_DEFINED__
#define __IcwbxDatabaseDownloadPCOptions2_FWD_DEFINED__
typedef interface IcwbxDatabaseDownloadPCOptions2 IcwbxDatabaseDownloadPCOptions2;
#endif 	/* __IcwbxDatabaseDownloadPCOptions2_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadASCIIOptions2_FWD_DEFINED__
#define __IcwbxDatabaseDownloadASCIIOptions2_FWD_DEFINED__
typedef interface IcwbxDatabaseDownloadASCIIOptions2 IcwbxDatabaseDownloadASCIIOptions2;
#endif 	/* __IcwbxDatabaseDownloadASCIIOptions2_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadTabDelimitedOptions2_FWD_DEFINED__
#define __IcwbxDatabaseDownloadTabDelimitedOptions2_FWD_DEFINED__
typedef interface IcwbxDatabaseDownloadTabDelimitedOptions2 IcwbxDatabaseDownloadTabDelimitedOptions2;
#endif 	/* __IcwbxDatabaseDownloadTabDelimitedOptions2_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadBIFFOptions2_FWD_DEFINED__
#define __IcwbxDatabaseDownloadBIFFOptions2_FWD_DEFINED__
typedef interface IcwbxDatabaseDownloadBIFFOptions2 IcwbxDatabaseDownloadBIFFOptions2;
#endif 	/* __IcwbxDatabaseDownloadBIFFOptions2_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadWK4Options2_FWD_DEFINED__
#define __IcwbxDatabaseDownloadWK4Options2_FWD_DEFINED__
typedef interface IcwbxDatabaseDownloadWK4Options2 IcwbxDatabaseDownloadWK4Options2;
#endif 	/* __IcwbxDatabaseDownloadWK4Options2_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseDownload123Options2_FWD_DEFINED__
#define __IcwbxDatabaseDownload123Options2_FWD_DEFINED__
typedef interface IcwbxDatabaseDownload123Options2 IcwbxDatabaseDownload123Options2;
#endif 	/* __IcwbxDatabaseDownload123Options2_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadExcelXMLOptions_FWD_DEFINED__
#define __IcwbxDatabaseDownloadExcelXMLOptions_FWD_DEFINED__
typedef interface IcwbxDatabaseDownloadExcelXMLOptions IcwbxDatabaseDownloadExcelXMLOptions;
#endif 	/* __IcwbxDatabaseDownloadExcelXMLOptions_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseTransferResults_FWD_DEFINED__
#define __IcwbxDatabaseTransferResults_FWD_DEFINED__
typedef interface IcwbxDatabaseTransferResults IcwbxDatabaseTransferResults;
#endif 	/* __IcwbxDatabaseTransferResults_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseDataError_FWD_DEFINED__
#define __IcwbxDatabaseDataError_FWD_DEFINED__
typedef interface IcwbxDatabaseDataError IcwbxDatabaseDataError;
#endif 	/* __IcwbxDatabaseDataError_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseDataErrors_FWD_DEFINED__
#define __IcwbxDatabaseDataErrors_FWD_DEFINED__
typedef interface IcwbxDatabaseDataErrors IcwbxDatabaseDataErrors;
#endif 	/* __IcwbxDatabaseDataErrors_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseUserLibraryList_FWD_DEFINED__
#define __IcwbxDatabaseUserLibraryList_FWD_DEFINED__
typedef interface IcwbxDatabaseUserLibraryList IcwbxDatabaseUserLibraryList;
#endif 	/* __IcwbxDatabaseUserLibraryList_FWD_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadUnicodeOptions_FWD_DEFINED__
#define __IcwbxDatabaseDownloadUnicodeOptions_FWD_DEFINED__
typedef interface IcwbxDatabaseDownloadUnicodeOptions IcwbxDatabaseDownloadUnicodeOptions;
#endif 	/* __IcwbxDatabaseDownloadUnicodeOptions_FWD_DEFINED__ */


#ifndef __AS400System_FWD_DEFINED__
#define __AS400System_FWD_DEFINED__

#ifdef __cplusplus
typedef class AS400System AS400System;
#else
typedef struct AS400System AS400System;
#endif /* __cplusplus */

#endif 	/* __AS400System_FWD_DEFINED__ */


#ifndef __ClientInfo_FWD_DEFINED__
#define __ClientInfo_FWD_DEFINED__

#ifdef __cplusplus
typedef class ClientInfo ClientInfo;
#else
typedef struct ClientInfo ClientInfo;
#endif /* __cplusplus */

#endif 	/* __ClientInfo_FWD_DEFINED__ */


#ifndef __DataQueue_FWD_DEFINED__
#define __DataQueue_FWD_DEFINED__

#ifdef __cplusplus
typedef class DataQueue DataQueue;
#else
typedef struct DataQueue DataQueue;
#endif /* __cplusplus */

#endif 	/* __DataQueue_FWD_DEFINED__ */


#ifndef __KeyedDataQueue_FWD_DEFINED__
#define __KeyedDataQueue_FWD_DEFINED__

#ifdef __cplusplus
typedef class KeyedDataQueue KeyedDataQueue;
#else
typedef struct KeyedDataQueue KeyedDataQueue;
#endif /* __cplusplus */

#endif 	/* __KeyedDataQueue_FWD_DEFINED__ */


#ifndef __DataQueueAttributes_FWD_DEFINED__
#define __DataQueueAttributes_FWD_DEFINED__

#ifdef __cplusplus
typedef class DataQueueAttributes DataQueueAttributes;
#else
typedef struct DataQueueAttributes DataQueueAttributes;
#endif /* __cplusplus */

#endif 	/* __DataQueueAttributes_FWD_DEFINED__ */


#ifndef __Program_FWD_DEFINED__
#define __Program_FWD_DEFINED__

#ifdef __cplusplus
typedef class Program Program;
#else
typedef struct Program Program;
#endif /* __cplusplus */

#endif 	/* __Program_FWD_DEFINED__ */


#ifndef __ProgramParameter_FWD_DEFINED__
#define __ProgramParameter_FWD_DEFINED__

#ifdef __cplusplus
typedef class ProgramParameter ProgramParameter;
#else
typedef struct ProgramParameter ProgramParameter;
#endif /* __cplusplus */

#endif 	/* __ProgramParameter_FWD_DEFINED__ */


#ifndef __Command_FWD_DEFINED__
#define __Command_FWD_DEFINED__

#ifdef __cplusplus
typedef class Command Command;
#else
typedef struct Command Command;
#endif /* __cplusplus */

#endif 	/* __Command_FWD_DEFINED__ */


#ifndef __PackedConverter_FWD_DEFINED__
#define __PackedConverter_FWD_DEFINED__

#ifdef __cplusplus
typedef class PackedConverter PackedConverter;
#else
typedef struct PackedConverter PackedConverter;
#endif /* __cplusplus */

#endif 	/* __PackedConverter_FWD_DEFINED__ */


#ifndef __ZonedConverter_FWD_DEFINED__
#define __ZonedConverter_FWD_DEFINED__

#ifdef __cplusplus
typedef class ZonedConverter ZonedConverter;
#else
typedef struct ZonedConverter ZonedConverter;
#endif /* __cplusplus */

#endif 	/* __ZonedConverter_FWD_DEFINED__ */


#ifndef __Structure_FWD_DEFINED__
#define __Structure_FWD_DEFINED__

#ifdef __cplusplus
typedef class Structure Structure;
#else
typedef struct Structure Structure;
#endif /* __cplusplus */

#endif 	/* __Structure_FWD_DEFINED__ */


#ifndef __BinaryData_FWD_DEFINED__
#define __BinaryData_FWD_DEFINED__

#ifdef __cplusplus
typedef class BinaryData BinaryData;
#else
typedef struct BinaryData BinaryData;
#endif /* __cplusplus */

#endif 	/* __BinaryData_FWD_DEFINED__ */


#ifndef __ShortConverter_FWD_DEFINED__
#define __ShortConverter_FWD_DEFINED__

#ifdef __cplusplus
typedef class ShortConverter ShortConverter;
#else
typedef struct ShortConverter ShortConverter;
#endif /* __cplusplus */

#endif 	/* __ShortConverter_FWD_DEFINED__ */


#ifndef __LongConverter_FWD_DEFINED__
#define __LongConverter_FWD_DEFINED__

#ifdef __cplusplus
typedef class LongConverter LongConverter;
#else
typedef struct LongConverter LongConverter;
#endif /* __cplusplus */

#endif 	/* __LongConverter_FWD_DEFINED__ */


#ifndef __DoubleConverter_FWD_DEFINED__
#define __DoubleConverter_FWD_DEFINED__

#ifdef __cplusplus
typedef class DoubleConverter DoubleConverter;
#else
typedef struct DoubleConverter DoubleConverter;
#endif /* __cplusplus */

#endif 	/* __DoubleConverter_FWD_DEFINED__ */


#ifndef __FloatConverter_FWD_DEFINED__
#define __FloatConverter_FWD_DEFINED__

#ifdef __cplusplus
typedef class FloatConverter FloatConverter;
#else
typedef struct FloatConverter FloatConverter;
#endif /* __cplusplus */

#endif 	/* __FloatConverter_FWD_DEFINED__ */


#ifndef __StringConverter_FWD_DEFINED__
#define __StringConverter_FWD_DEFINED__

#ifdef __cplusplus
typedef class StringConverter StringConverter;
#else
typedef struct StringConverter StringConverter;
#endif /* __cplusplus */

#endif 	/* __StringConverter_FWD_DEFINED__ */


#ifndef __CodePageConverter_FWD_DEFINED__
#define __CodePageConverter_FWD_DEFINED__

#ifdef __cplusplus
typedef class CodePageConverter CodePageConverter;
#else
typedef struct CodePageConverter CodePageConverter;
#endif /* __cplusplus */

#endif 	/* __CodePageConverter_FWD_DEFINED__ */


#ifndef __StructureField_FWD_DEFINED__
#define __StructureField_FWD_DEFINED__

#ifdef __cplusplus
typedef class StructureField StructureField;
#else
typedef struct StructureField StructureField;
#endif /* __cplusplus */

#endif 	/* __StructureField_FWD_DEFINED__ */


#ifndef __Error_FWD_DEFINED__
#define __Error_FWD_DEFINED__

#ifdef __cplusplus
typedef class Error Error;
#else
typedef struct Error Error;
#endif /* __cplusplus */

#endif 	/* __Error_FWD_DEFINED__ */


#ifndef __SystemNames_FWD_DEFINED__
#define __SystemNames_FWD_DEFINED__

#ifdef __cplusplus
typedef class SystemNames SystemNames;
#else
typedef struct SystemNames SystemNames;
#endif /* __cplusplus */

#endif 	/* __SystemNames_FWD_DEFINED__ */


#ifndef __ProgramParameters_FWD_DEFINED__
#define __ProgramParameters_FWD_DEFINED__

#ifdef __cplusplus
typedef class ProgramParameters ProgramParameters;
#else
typedef struct ProgramParameters ProgramParameters;
#endif /* __cplusplus */

#endif 	/* __ProgramParameters_FWD_DEFINED__ */


#ifndef __StructureFields_FWD_DEFINED__
#define __StructureFields_FWD_DEFINED__

#ifdef __cplusplus
typedef class StructureFields StructureFields;
#else
typedef struct StructureFields StructureFields;
#endif /* __cplusplus */

#endif 	/* __StructureFields_FWD_DEFINED__ */


#ifndef __Errors_FWD_DEFINED__
#define __Errors_FWD_DEFINED__

#ifdef __cplusplus
typedef class Errors Errors;
#else
typedef struct Errors Errors;
#endif /* __cplusplus */

#endif 	/* __Errors_FWD_DEFINED__ */


#ifndef __DataQueueSenderInfo_FWD_DEFINED__
#define __DataQueueSenderInfo_FWD_DEFINED__

#ifdef __cplusplus
typedef class DataQueueSenderInfo DataQueueSenderInfo;
#else
typedef struct DataQueueSenderInfo DataQueueSenderInfo;
#endif /* __cplusplus */

#endif 	/* __DataQueueSenderInfo_FWD_DEFINED__ */


#ifndef __DatabaseTransfer_FWD_DEFINED__
#define __DatabaseTransfer_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseTransfer DatabaseTransfer;
#else
typedef struct DatabaseTransfer DatabaseTransfer;
#endif /* __cplusplus */

#endif 	/* __DatabaseTransfer_FWD_DEFINED__ */


#ifndef __DatabaseDownloadRequest_FWD_DEFINED__
#define __DatabaseDownloadRequest_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseDownloadRequest DatabaseDownloadRequest;
#else
typedef struct DatabaseDownloadRequest DatabaseDownloadRequest;
#endif /* __cplusplus */

#endif 	/* __DatabaseDownloadRequest_FWD_DEFINED__ */


#ifndef __DatabaseUploadRequest_FWD_DEFINED__
#define __DatabaseUploadRequest_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseUploadRequest DatabaseUploadRequest;
#else
typedef struct DatabaseUploadRequest DatabaseUploadRequest;
#endif /* __cplusplus */

#endif 	/* __DatabaseUploadRequest_FWD_DEFINED__ */


#ifndef __DatabaseQuerySettings_FWD_DEFINED__
#define __DatabaseQuerySettings_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseQuerySettings DatabaseQuerySettings;
#else
typedef struct DatabaseQuerySettings DatabaseQuerySettings;
#endif /* __cplusplus */

#endif 	/* __DatabaseQuerySettings_FWD_DEFINED__ */


#ifndef __DatabaseFormatOptions_FWD_DEFINED__
#define __DatabaseFormatOptions_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseFormatOptions DatabaseFormatOptions;
#else
typedef struct DatabaseFormatOptions DatabaseFormatOptions;
#endif /* __cplusplus */

#endif 	/* __DatabaseFormatOptions_FWD_DEFINED__ */


#ifndef __DatabaseAS400File_FWD_DEFINED__
#define __DatabaseAS400File_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseAS400File DatabaseAS400File;
#else
typedef struct DatabaseAS400File DatabaseAS400File;
#endif /* __cplusplus */

#endif 	/* __DatabaseAS400File_FWD_DEFINED__ */


#ifndef __DatabaseUploadPCFile_FWD_DEFINED__
#define __DatabaseUploadPCFile_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseUploadPCFile DatabaseUploadPCFile;
#else
typedef struct DatabaseUploadPCFile DatabaseUploadPCFile;
#endif /* __cplusplus */

#endif 	/* __DatabaseUploadPCFile_FWD_DEFINED__ */


#ifndef __DatabaseUploadPCOptions_FWD_DEFINED__
#define __DatabaseUploadPCOptions_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseUploadPCOptions DatabaseUploadPCOptions;
#else
typedef struct DatabaseUploadPCOptions DatabaseUploadPCOptions;
#endif /* __cplusplus */

#endif 	/* __DatabaseUploadPCOptions_FWD_DEFINED__ */


#ifndef __DatabaseUploadBIFFOptions_FWD_DEFINED__
#define __DatabaseUploadBIFFOptions_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseUploadBIFFOptions DatabaseUploadBIFFOptions;
#else
typedef struct DatabaseUploadBIFFOptions DatabaseUploadBIFFOptions;
#endif /* __cplusplus */

#endif 	/* __DatabaseUploadBIFFOptions_FWD_DEFINED__ */


#ifndef __DatabaseUploadWK4Options_FWD_DEFINED__
#define __DatabaseUploadWK4Options_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseUploadWK4Options DatabaseUploadWK4Options;
#else
typedef struct DatabaseUploadWK4Options DatabaseUploadWK4Options;
#endif /* __cplusplus */

#endif 	/* __DatabaseUploadWK4Options_FWD_DEFINED__ */


#ifndef __DatabaseUpload123Options_FWD_DEFINED__
#define __DatabaseUpload123Options_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseUpload123Options DatabaseUpload123Options;
#else
typedef struct DatabaseUpload123Options DatabaseUpload123Options;
#endif /* __cplusplus */

#endif 	/* __DatabaseUpload123Options_FWD_DEFINED__ */


#ifndef __DatabaseUploadExcelXMLOptions_FWD_DEFINED__
#define __DatabaseUploadExcelXMLOptions_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseUploadExcelXMLOptions DatabaseUploadExcelXMLOptions;
#else
typedef struct DatabaseUploadExcelXMLOptions DatabaseUploadExcelXMLOptions;
#endif /* __cplusplus */

#endif 	/* __DatabaseUploadExcelXMLOptions_FWD_DEFINED__ */


#ifndef __DatabaseDownloadPCFile_FWD_DEFINED__
#define __DatabaseDownloadPCFile_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseDownloadPCFile DatabaseDownloadPCFile;
#else
typedef struct DatabaseDownloadPCFile DatabaseDownloadPCFile;
#endif /* __cplusplus */

#endif 	/* __DatabaseDownloadPCFile_FWD_DEFINED__ */


#ifndef __DatabaseDownloadPCOptions_FWD_DEFINED__
#define __DatabaseDownloadPCOptions_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseDownloadPCOptions DatabaseDownloadPCOptions;
#else
typedef struct DatabaseDownloadPCOptions DatabaseDownloadPCOptions;
#endif /* __cplusplus */

#endif 	/* __DatabaseDownloadPCOptions_FWD_DEFINED__ */


#ifndef __DatabaseDownloadASCIIOptions_FWD_DEFINED__
#define __DatabaseDownloadASCIIOptions_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseDownloadASCIIOptions DatabaseDownloadASCIIOptions;
#else
typedef struct DatabaseDownloadASCIIOptions DatabaseDownloadASCIIOptions;
#endif /* __cplusplus */

#endif 	/* __DatabaseDownloadASCIIOptions_FWD_DEFINED__ */


#ifndef __DatabaseDownloadTabDelimitedOptions_FWD_DEFINED__
#define __DatabaseDownloadTabDelimitedOptions_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseDownloadTabDelimitedOptions DatabaseDownloadTabDelimitedOptions;
#else
typedef struct DatabaseDownloadTabDelimitedOptions DatabaseDownloadTabDelimitedOptions;
#endif /* __cplusplus */

#endif 	/* __DatabaseDownloadTabDelimitedOptions_FWD_DEFINED__ */


#ifndef __DatabaseDownloadBIFFOptions_FWD_DEFINED__
#define __DatabaseDownloadBIFFOptions_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseDownloadBIFFOptions DatabaseDownloadBIFFOptions;
#else
typedef struct DatabaseDownloadBIFFOptions DatabaseDownloadBIFFOptions;
#endif /* __cplusplus */

#endif 	/* __DatabaseDownloadBIFFOptions_FWD_DEFINED__ */


#ifndef __DatabaseDownloadWK4Options_FWD_DEFINED__
#define __DatabaseDownloadWK4Options_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseDownloadWK4Options DatabaseDownloadWK4Options;
#else
typedef struct DatabaseDownloadWK4Options DatabaseDownloadWK4Options;
#endif /* __cplusplus */

#endif 	/* __DatabaseDownloadWK4Options_FWD_DEFINED__ */


#ifndef __DatabaseDownload123Options_FWD_DEFINED__
#define __DatabaseDownload123Options_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseDownload123Options DatabaseDownload123Options;
#else
typedef struct DatabaseDownload123Options DatabaseDownload123Options;
#endif /* __cplusplus */

#endif 	/* __DatabaseDownload123Options_FWD_DEFINED__ */


#ifndef __DatabaseDownloadUnicodeOptions_FWD_DEFINED__
#define __DatabaseDownloadUnicodeOptions_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseDownloadUnicodeOptions DatabaseDownloadUnicodeOptions;
#else
typedef struct DatabaseDownloadUnicodeOptions DatabaseDownloadUnicodeOptions;
#endif /* __cplusplus */

#endif 	/* __DatabaseDownloadUnicodeOptions_FWD_DEFINED__ */


#ifndef __DatabaseDownloadExcelXMLOptions_FWD_DEFINED__
#define __DatabaseDownloadExcelXMLOptions_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseDownloadExcelXMLOptions DatabaseDownloadExcelXMLOptions;
#else
typedef struct DatabaseDownloadExcelXMLOptions DatabaseDownloadExcelXMLOptions;
#endif /* __cplusplus */

#endif 	/* __DatabaseDownloadExcelXMLOptions_FWD_DEFINED__ */


#ifndef __DatabaseDownloadHTMLOptions_FWD_DEFINED__
#define __DatabaseDownloadHTMLOptions_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseDownloadHTMLOptions DatabaseDownloadHTMLOptions;
#else
typedef struct DatabaseDownloadHTMLOptions DatabaseDownloadHTMLOptions;
#endif /* __cplusplus */

#endif 	/* __DatabaseDownloadHTMLOptions_FWD_DEFINED__ */


#ifndef __DatabaseTransferResults_FWD_DEFINED__
#define __DatabaseTransferResults_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseTransferResults DatabaseTransferResults;
#else
typedef struct DatabaseTransferResults DatabaseTransferResults;
#endif /* __cplusplus */

#endif 	/* __DatabaseTransferResults_FWD_DEFINED__ */


#ifndef __DatabaseDataError_FWD_DEFINED__
#define __DatabaseDataError_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseDataError DatabaseDataError;
#else
typedef struct DatabaseDataError DatabaseDataError;
#endif /* __cplusplus */

#endif 	/* __DatabaseDataError_FWD_DEFINED__ */


#ifndef __DatabaseDataErrors_FWD_DEFINED__
#define __DatabaseDataErrors_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseDataErrors DatabaseDataErrors;
#else
typedef struct DatabaseDataErrors DatabaseDataErrors;
#endif /* __cplusplus */

#endif 	/* __DatabaseDataErrors_FWD_DEFINED__ */


#ifndef __DatabaseUserLibraryList_FWD_DEFINED__
#define __DatabaseUserLibraryList_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseUserLibraryList DatabaseUserLibraryList;
#else
typedef struct DatabaseUserLibraryList DatabaseUserLibraryList;
#endif /* __cplusplus */

#endif 	/* __DatabaseUserLibraryList_FWD_DEFINED__ */


#ifndef __DatabaseUploadASCIIOptions_FWD_DEFINED__
#define __DatabaseUploadASCIIOptions_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseUploadASCIIOptions DatabaseUploadASCIIOptions;
#else
typedef struct DatabaseUploadASCIIOptions DatabaseUploadASCIIOptions;
#endif /* __cplusplus */

#endif 	/* __DatabaseUploadASCIIOptions_FWD_DEFINED__ */


#ifndef __DatabaseUploadUnicodeOptions_FWD_DEFINED__
#define __DatabaseUploadUnicodeOptions_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseUploadUnicodeOptions DatabaseUploadUnicodeOptions;
#else
typedef struct DatabaseUploadUnicodeOptions DatabaseUploadUnicodeOptions;
#endif /* __cplusplus */

#endif 	/* __DatabaseUploadUnicodeOptions_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_cwbx_0000 */
/* [local] */ 
























































extern RPC_IF_HANDLE __MIDL_itf_cwbx_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_cwbx_0000_v0_0_s_ifspec;


#ifndef __cwbx_LIBRARY_DEFINED__
#define __cwbx_LIBRARY_DEFINED__

/* library cwbx */
/* [helpfile][helpcontext][helpstring][version][uuid] */ 

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2120-1A8F-11d2-849C-0004AC94E175") 
enum cwbReturnCodeEnum
    {	cwbOK	= 0,
	cwbInvalidFunction	= 1,
	cwbFileNotFound	= 2,
	cwbPathNotFound	= 3,
	cwbTooManyOpenFiles	= 4,
	cwbAccessDenied	= 5,
	cwbInvalidHandle	= 6,
	cwbNotEnoughMemory	= 8,
	cwbInvalidDrive	= 15,
	cwbNoMoreFiles	= 18,
	cwbDriveNotReady	= 21,
	cwbGeneralFailure	= 31,
	cwbSharingViolation	= 32,
	cwbLockViolation	= 33,
	cwbEndOfFile	= 38,
	cwbNotSupported	= 50,
	cwbBadNetworkPath	= 53,
	cwbNetworkBusy	= 54,
	cwbDeviceNotExist	= 55,
	cwbUnexpectedNetworkError	= 59,
	cwbNetworkAccessDenied	= 65,
	cwbFileExists	= 80,
	cwbAlreadyAssigned	= 85,
	cwbInvalidParameter	= 87,
	cwbNetworkWriteFault	= 88,
	cwbOpenFailed	= 110,
	cwbBufferOverflow	= 111,
	cwbDiskFull	= 112,
	cwbProtectionViolation	= 115,
	cwbInvalidLevel	= 124,
	cwbBusyDrive	= 142,
	cwbInvalidFSDName	= 252,
	cwbInvalidPath	= 253,
	cwbUserCancelledCommand	= 4000,
	cwbConfigError	= 4001,
	cwbLicenseError	= 4002,
	cwbProdOrCompNotSet	= 4003,
	cwbSecurityError	= 4004,
	cwbGlobalCfgFailed	= 4005,
	cwbProdRetrieveFailed	= 4006,
	cwbCompRetrieveFailed	= 4007,
	cwbCompCfgFailed	= 4008,
	cwbCompFixLevelUpdateFailed	= 4009,
	cwbInvalidAPIHandle	= 4010,
	cwbInvalidAPIParameter	= 4011,
	cwbHostNotFound	= 4012,
	cwbNotCompatible	= 4013,
	cwbInvalidPointer	= 4014,
	cwbServerProgramNotFound	= 4015,
	cwbAPIError	= 4016,
	cwbCANotStarted	= 4017,
	cwbFileIOError	= 4018,
	cwbCommunicationsError	= 4019,
	cwbRuntimeConstructorFailed	= 4020,
	cwbDiagnostic	= 4021,
	cwbCommVersionError	= 4022,
	cwbNoViewer	= 4023,
	cwbModuleNotLoadable	= 4024,
	cwbAlreadySetup	= 4025,
	cwbCannotStartProcess	= 4026,
	cwbNonRepresentableUnicodeChar	= 4027,
	cwbEntryNotFound	= 4028,
	cwbUnknownUserid	= 8001,
	cwbWrongPassword	= 8002,
	cwbPasswordExpired	= 8003,
	cwbInvalidPassword	= 8004,
	cwbPasswordToExpire	= 8005,
	cwbIncorrectDataFormat	= 8006,
	cwbGeneralSecurityError	= 8007,
	cwbUserProfileDisabled	= 8011,
	cwbUserCancelled	= 8013,
	cwbInvalidSysname	= 8014,
	cwbInvalidUserid	= 8015,
	cwbLimitedCapabilitiesUserid	= 8016,
	cwbWindowsUserIDNotFound	= 8017,
	cwbWindowsPasswordNotFound	= 8018,
	cwbInvalidTPOnHost	= 8019,
	cwbNotLoggedOn	= 8022,
	cwbExitPgmError	= 8026,
	cwbExitPgmDeniedRequest	= 8027,
	cwbTimestampsNotSet	= 8050,
	cwbKerbClientCredentialsNotFound	= 8051,
	cwbKerbServiceTicketNotFound	= 8052,
	cwbKerbServerCannotBeContacted	= 8053,
	cwbKerbUnsupportedByHost	= 8054,
	cwbKerbNotAvailable	= 8055,
	cwbKerbServerNotConfigured	= 8056,
	cwbKerbCredentialsNotValid	= 8057,
	cwbKerbMappedUseridFailure	= 8058,
	cwbKerbMappedUseridSuccess	= 8059,
	cwbProfileTokenInvalid	= 8070,
	cwbProfileTokenMaximum	= 8071,
	cwbProfileTokenCannotBeRegenerated	= 8072,
	cwbPWTooLong	= 8257,
	cwbPWTooShort	= 8258,
	cwbPWRepeatCharacter	= 8259,
	cwbPWAdjacentDigits	= 8260,
	cwbPWConsecutiveChars	= 8261,
	cwbPWPreviouslyUsed	= 8262,
	cwbPWDisallowedChar	= 8263,
	cwbPWNeedNumeric	= 8264,
	cwbPWMatchesOld	= 8266,
	cwbPWNotAllowed	= 8267,
	cwbPWContainsUserid	= 8268,
	cwbPWLastInvalidPwd	= 8270,
	cwbInvAfterSignon	= 8400,
	cwbInvWhenConnected	= 8401,
	cwbInvBeforeValidate	= 8402,
	cwbSecureSocketsNotavail	= 8403,
	cwbReserved1	= 8404,
	cwbReceiveError	= 8405,
	cwbServiceNameError	= 8406,
	cwbGetPortError	= 8407,
	cwbSuccessWarning	= 8408,
	cwbNotConnected	= 8409,
	cwbDefaultHostCodePageUsed	= 8410,
	cwbUserTimeout	= 8411,
	cwbSSLJavaError	= 8412,
	cwbUserTimeoutSendReceive	= 8413,
	cwbRestrictedByPolicy	= 8500,
	cwbPolicyModifyMandatedEnv	= 8501,
	cwbPolicyModifyCurrentEnv	= 8502,
	cwbPolicyModifyEnvList	= 8503,
	cwbSystemNotFound	= 8504,
	cwbEnvironmentNotFound	= 8505,
	cwbEnvironmentExists	= 8506,
	cwbSystemExists	= 8507,
	cwbNoSystemsConfigured	= 8508,
	cwbInvalidMethodParm	= 8600,
	cwbInvalidPropertyParm	= 8601,
	cwbInvalidPropertyValue	= 8602,
	cwbObjectNotInitialized	= 8603,
	cwbObjectAlreadyInitialized	= 8604,
	cwbInvalidDQOrder	= 8605,
	cwbDataTransferRequired	= 8606,
	cwbUnsupportedXferRequest	= 8607,
	cwbAsyncRequestActive	= 8608,
	cwbRequestTimedOut	= 8609,
	cwbCannotSetPropNow	= 8610,
	cwbObjStateNoLongerValid	= 8611,
	cwbUnsupportedFunction	= 8998,
	cwbInternalError	= 8999,
	cwbTooManyOpenSockets	= 10024,
	cwbResourceTemporarilyUnavailable	= 10035,
	cwbSocketOperationOnNonSocket	= 10038,
	cwbProtocolNotInstalled	= 10047,
	cwbNetworkIsDown	= 10050,
	cwbNetworkIsUnreachable	= 10051,
	cwbNetworkDroppedConnectionOnReset	= 10052,
	cwbSoftwareCausedConnectionAbort	= 10053,
	cwbConnectionResetByPeer	= 10054,
	cwbNoBufferSpaceAvailable	= 10055,
	cwbSocketIsNotConnected	= 10057,
	cwbCannotSendAfterSocketShutdown	= 10058,
	cwbConnectionTimedOut	= 10060,
	cwbConnectionRefused	= 10061,
	cwbHostIsDown	= 10064,
	cwbNoRouteToHost	= 10065,
	cwbNetworkSubsystemIsUnavailable	= 10091,
	cwbWinsockVersionNotSupported	= 10092,
	cwbHostDefinitelyNotFound	= 11001,
	cwbHostNotFoundButWeAreNotSure	= 11002,
	cwbValidNameButNoDataRecord	= 11004,
	cwbSSLKeyfileIOError	= 20001,
	cwbSSLKeyfileOpenFailed	= 20002,
	cwbSSLKeyfileBadFormat	= 20003,
	cwbSSLKeyfileBadPassword	= 20004,
	cwbSSLKeyfileBadMalloc	= 20005,
	cwbSSLKeyfileNothingToWrite	= 20006,
	cwbSSLKeyfileWriteFailed	= 20007,
	cwbSSLKeyfileNotFound	= 20008,
	cwbSSLKeyfileBadDName	= 20009,
	cwbSSLKeyfileBadKey	= 20010,
	cwbSSLKeyfileKeyExists	= 20011,
	cwbSSLKeyfileBadLabel	= 20012,
	cwbSSLKeyfileDuplicateName	= 20013,
	cwbSSLKeyfileDuplicateKey	= 20014,
	cwbSSLKeyfileDuplicateLabel	= 20015,
	cwbSSLBadFormatOrInvalidPW	= 20016,
	cwbSSLWarningInvalidServerCert	= 20098,
	cwbSSLWarningInvalidServerPrivKey	= 20099,
	cwbSSLErrInitParmNotValid	= 20100,
	cwbSSLInitSecTypeNotValid	= 20102,
	cwbSSLInitV2TimeoutNotValid	= 20103,
	cwbSSLInitV3TimeoutNotValid	= 20104,
	cwbSSLKeyfileCertExpired	= 20105,
	cwbSSLErrorNoCiphers	= 25001,
	cwbSSLErrorNoCertificate	= 25002,
	cwbSSLErrorBadCertificate	= 25004,
	cwbSSLErrorUnsupportedCertificateType	= 25006,
	cwbSSLErrorIO	= 25010,
	cwbSSLErrorBadMessage	= 25011,
	cwbSSLErrorBadMac	= 25012,
	cwbSSLErrorUnsupported	= 25013,
	cwbSSLErrorBadCertSig	= 25014,
	cwbSSLErrorBadCert	= 25015,
	cwbSSLErrorBadPeer	= 25016,
	cwbSSLErrorPermissionDenied	= 25017,
	cwbSSLErrorSelfSigned	= 25018,
	cwbSSLErrorBadMalloc	= 25020,
	cwbSSLErrorBadState	= 25021,
	cwbSSLErrorSocketClosed	= 25022,
	cwbSSLErrorSSLInitializationFailed	= 25023,
	cwbSSLErrorHandleCreationFailed	= 25024,
	cwbSSLErrorBadDate	= 25025,
	cwbSSLErrorBadKeyLenForExport	= 25026,
	cwbSSLErrorNoPrivateKey	= 25027,
	cwbSSLBadParameter	= 25028,
	cwbSSLErrorInternal	= 25029,
	cwbSSLErrorWouldBlock	= 25030,
	cwbSSLErrorLoadGsklib	= 25031,
	cwbSSLSocBadV2Cipher	= 25040,
	cwbSSLSocBadV3Cipher	= 25041,
	cwbSSLSocBadSecType	= 25042,
	cwbSSLSocNoReadFunction	= 25043,
	cwbSSLSocNoWriteFunction	= 25044,
	cwbSSLErrorNotServer	= 25050,
	cwbSSLErrorNotSSLV3	= 25051,
	cwbSSLErrorNotSSLV3Client	= 25052,
	cwbSSLErrorUnknownError	= 25099,
	cwbSSLErrorBadBufferSize	= 25100,
	cwbSSLErrorBadSSLHandle	= 25101,
	cwbSSLErrorTimeout	= 25102
    } 	cwbReturnCodeEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2133-1A8F-11d2-849C-0004AC94E175") 
enum cwbHResultEnum
    {	cwbxEInvalidMethodParm	= 0x80042198,
	cwbxEInvalidPropertyParm	= 0x80042199,
	cwbxEInvalidPropertyValue	= 0x8004219a,
	cwbxEObjectNotInitialized	= 0x8004219b,
	cwbxEObjectAlreadyInitialized	= 0x8004219c,
	cwbxEInvalidDQOrder	= 0x8004219d,
	cwbxEDataTransferRequired	= 0x8004219e,
	cwbxEUnsupportedXferRequest	= 0x8004219f,
	cwbxEAsyncRequestActive	= 0x800421a0,
	cwbxEPolicyRestriction	= 0x80042134,
	cwbxERequestTimedOut	= 0x800421a1,
	cwbxECannotSetPropNow	= 0x800421a2,
	cwbxEObjStateNoLongerValid	= 0x800421a3
    } 	cwbHResultEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2121-1A8F-11d2-849C-0004AC94E175") 
enum cwbcoServiceEnum
    {	cwbcoServiceCentral	= 1,
	cwbcoServiceNetFile	= 2,
	cwbcoServiceNetPrint	= 3,
	cwbcoServiceDatabase	= 4,
	cwbcoServiceODBC	= 5,
	cwbcoServiceDataQueues	= 6,
	cwbcoServiceRemoteCmd	= 7,
	cwbcoServiceSecurity	= 8,
	cwbcoServiceDDM	= 9,
	cwbcoServiceMAPI	= 10,
	cwbcoServiceUSF	= 11,
	cwbcoServiceWebAdmin	= 12,
	cwbcoServiceTelnet	= 13,
	cwbcoServiceMgmtCentral	= 14,
	cwbcoServiceAny	= 100,
	cwbcoServiceAll	= 101
    } 	cwbcoServiceEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2122-1A8F-11d2-849C-0004AC94E175") 
enum cwbcoPromptModeEnum
    {	cwbcoPromptIfNecessary	= 0,
	cwbcoPromptAlways	= 1,
	cwbcoPromptNever	= 2,
	cwbcoPromptDefault	= 0
    } 	cwbcoPromptModeEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2123-1A8F-11d2-849C-0004AC94E175") 
enum cwbcoValidateModeEnum
    {	cwbcoValidateIfNecessary	= 0,
	cwbcoValidateAlways	= 1,
	cwbcoValidateDefault	= 0
    } 	cwbcoValidateModeEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2124-1A8F-11d2-849C-0004AC94E175") 
enum cwbcoDefaultUserModeEnum
    {	cwbcoDefaultUserModeNotSet	= 0,
	cwbcoDefaultUserUse	= 1,
	cwbcoDefaultUserIgnore	= 2,
	cwbcoDefaultUserUseWinlogon	= 3,
	cwbcoDefaultUserUseKerberos	= 4,
	cwbcoDefaultUserDefault	= 0
    } 	cwbcoDefaultUserModeEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2125-1A8F-11d2-849C-0004AC94E175") 
enum cwbcoIPAddrLookupModeEnum
    {	cwbcoIPAddrLookupAlways	= 0,
	cwbcoIPAddrLookup1Hour	= 1,
	cwbcoIPAddrLookup1Day	= 2,
	cwbcoIPAddrLookup1Week	= 3,
	cwbcoIPAddrLookupNever	= 4,
	cwbcoIPAddrLookupAfterStartup	= 5,
	cwbcoIPAddrLookupDefault	= 0
    } 	cwbcoIPAddrLookupModeEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2126-1A8F-11d2-849C-0004AC94E175") 
enum cwbcoPortLookupModeEnum
    {	cwbcoPortLookupServer	= 0,
	cwbcoPortLookupLocal	= 1,
	cwbcoPortLookupStandard	= 2,
	cwbcoPortLookupDefault	= 0
    } 	cwbcoPortLookupModeEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2127-1A8F-11d2-849C-0004AC94E175") 
enum cwbcoPersistenceModeEnum
    {	cwbcoMayMakePersistent	= 0,
	cwbcoMayNotMakePersistent	= 1,
	cwbcoPersistenceDefault	= 0
    } 	cwbcoPersistenceModeEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2129-1A8F-11d2-849C-0004AC94E175") 
enum cwbcoMaxStringSizeEnum
    {	cwbcoMaxUserID	= 10,
	cwbcoMaxPassword	= 256,
	cwbcoMaxSysName	= 255,
	cwbcoMaxEnvName	= 50,
	cwbcoMaxServiceName	= 32,
	cwbcoMaxIPAddress	= 15,
	cwbcoMaxSSLPassword	= 128
    } 	cwbcoMaxStringSizeEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2128-1A8F-11d2-849C-0004AC94E175") 
enum cwbadClientComponentEnum
    {	cwbadCompBaseSupport	= 1,
	cwbadCompOptionalComponents	= 2,
	cwbadCompDirectoryUpdate	= 3,
	cwbadCompIRC	= 4,
	cwbadCompMAPI	= 5,
	cwbadCompOnlineUsersGuide	= 6,
	cwbadCompOpNav	= 7,
	cwbadCompDataAccess	= 8,
	cwbadCompDataTransfer	= 9,
	cwbadCompDataTransferBase	= 10,
	cwbadCompDataTransferExcelAddin	= 11,
	cwbadCompDataTransferWK4Support	= 12,
	cwbadCompODBC	= 13,
	cwbadCompOLEDB	= 14,
	cwbadCompAFPViewer	= 15,
	cwbadCompJavaToolbox	= 16,
	cwbadCompPC5250	= 17,
	cwbadCompPrinterDrivers	= 18,
	cwbadCompAFPDriver	= 19,
	cwbadCompSCSDriver	= 20,
	cwbadCompOpConsole	= 21,
	cwbadCompToolkit	= 22,
	cwbadCompToolkitBase	= 23,
	cwbadCompToolkitOLEDBWizards	= 24,
	cwbadCompEZSetup	= 25,
	cwbadCompToolkitJavaTools	= 26,
	cwbadCompScreenCustomizerEnablement	= 27,
	cwbadCompOpNavBaseSupport	= 100,
	cwbadCompOpNavBasicOperations	= 101,
	cwbadCompOpNavJobManagement	= 102,
	cwbadCompOpNavSystemConfiguration	= 103,
	cwbadCompOpNavNetwork	= 104,
	cwbadCompOpNavSecurity	= 105,
	cwbadCompOpNavUsersAndGroups	= 106,
	cwbadCompOpNavDatabase	= 107,
	cwbadCompOpNavMultimedia	= 108,
	cwbadCompOpNavBackup	= 109,
	cwbadCompOpNavAppDevelopment	= 110,
	cwbadCompOpNavAppAdministration	= 111,
	cwbadCompOpNavFileSystems	= 112,
	cwbadCompOpNavMgmtCentral	= 113,
	cwbadCompOpNavMgmtCommands	= 114,
	cwbadCompOpNavMgmtPackProd	= 115,
	cwbadCompOpNavMgmtMonitors	= 116,
	cwbadCompOpNavLogicalSys	= 117,
	cwbadCompOpNavAdvFuncPres	= 118,
	cwbadCompPC5250KoreanBase	= 150,
	cwbadCompPC5250KoreanPDFPDTFiles	= 151,
	cwbadCompPC5250SimpChinBase	= 152,
	cwbadCompPC5250SimpChinPDFPDTFiles	= 153,
	cwbadCompPC5250TradChinBase	= 154,
	cwbadCompPC5250TradChinPDFPDTFiles	= 155,
	cwbadCompPC5250StandardBase	= 156,
	cwbadCompPC5250StandardPDFPDTFiles	= 157,
	cwbadCompPC5250FontArabic	= 158,
	cwbadCompPC5250FontBaltic	= 159,
	cwbadCompPC5250FontLatin2	= 160,
	cwbadCompPC5250FontCyrillic	= 161,
	cwbadCompPC5250FontGreek	= 162,
	cwbadCompPC5250FontHebrew	= 163,
	cwbadCompPC5250FontLao	= 164,
	cwbadCompPC5250FontThai	= 165,
	cwbadCompPC5250FontTurkish	= 166,
	cwbadCompPC5250FontVietnamese	= 167,
	cwbadCompPC5250FontHindi	= 168,
	cwbadCompSSL	= 200,
	cwbadCompSSL128Bit	= 201,
	cwbadCompSSL56Bit	= 202,
	cwbadCompSSL40Bit	= 203
    } 	cwbadClientComponentEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA212A-1A8F-11d2-849C-0004AC94E175") 
enum cwbdqAuthorityEnum
    {	cwbdqAll	= 0,
	cwbdqExclude	= 1,
	cwbdqChange	= 2,
	cwbdqUse	= 3,
	cwbdqLibcrtaut	= 4
    } 	cwbdqAuthorityEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA212B-1A8F-11d2-849C-0004AC94E175") 
enum cwbdqRetrievalOrderEnum
    {	cwbdqSeqLifo	= 0,
	cwbdqSeqFifo	= 1,
	cwbdqSeqKeyed	= 2
    } 	cwbdqRetrievalOrderEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA212C-1A8F-11d2-849C-0004AC94E175") 
enum cwbdqSearchOrderEnum
    {	cwbdqEqual	= 1,
	cwbdqNotEqual	= 2,
	cwbdqGtOrEqual	= 3,
	cwbdqGreater	= 4,
	cwbdqLtOrEqual	= 5,
	cwbdqLess	= 6
    } 	cwbdqSearchOrderEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA212D-1A8F-11d2-849C-0004AC94E175") 
enum cwbdqReturnCodeEnum
    {	cwbdqInvalidAttributeHandle	= 6000,
	cwbdqInvalidDataHandle	= 6001,
	cwbdqInvalidQueueHandle	= 6002,
	cwbdqInvalidReadHandle	= 6003,
	cwbdqInvalidQueueLength	= 6004,
	cwbdqInvalidKeyLength	= 6005,
	cwbdqInvalidOrder	= 6006,
	cwbdqInvalidAuthority	= 6007,
	cwbdqInvalidQueueTitle	= 6008,
	cwbdqBadQueueName	= 6009,
	cwbdqBadLibraryName	= 6010,
	cwbdqBadSystemName	= 6011,
	cwbdqBadKeyLength	= 6012,
	cwbdqBadDataLength	= 6013,
	cwbdqInvalidTime	= 6014,
	cwbdqInvalidSearch	= 6015,
	cwbdqDataTruncated	= 6016,
	cwbdqTimedOut	= 6017,
	cwbdqRejectedUserExit	= 6018,
	cwbdqUserExitError	= 6019,
	cwbdqLibraryNotFound	= 6020,
	cwbdqQueueNotFound	= 6021,
	cwbdqNoAuthority	= 6022,
	cwbdqDamagedQueue	= 6023,
	cwbdqQueueExists	= 6024,
	cwbdqInvalidMessageLength	= 6025,
	cwbdqQueueDestroyed	= 6026,
	cwbdqNoData	= 6027,
	cwbdqCannotConvert	= 6028,
	cwbdqQueueSyntax	= 6029,
	cwbdqLibrarySyntax	= 6030,
	cwbdqAddressNotSet	= 6031,
	cwbdqHostError	= 6032,
	cwbdqInvalidSystemHandle	= 6033,
	cwbdqUnexpectedError	= 6099
    } 	cwbdqReturnCodeEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA212E-1A8F-11d2-849C-0004AC94E175") 
enum cwbrcParameterTypeEnum
    {	cwbrcInput	= 1,
	cwbrcOutput	= 2,
	cwbrcInout	= 3
    } 	cwbrcParameterTypeEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA212F-1A8F-11d2-849C-0004AC94E175") 
enum cwbsvErrorClassEnum
    {	cwbsvClassInformational	= 0,
	cwbsvClassWarning	= 1,
	cwbsvClassError	= 2,
	cwbsvClassErrorRetry	= 1,
	cwbsvClassErrorAbort	= 2,
	cwbsvClassHostWarning	= 10,
	cwbsvClassHostError	= 20,
	cwbsvClassHostSevError	= 30,
	cwbsvClassHostSevErrorAbend	= 40,
	cwbsvClassHostJobAbend	= 50,
	cwbsvClassHostSysStatus	= 60,
	cwbsvClassHostDeviceIntegrity	= 70,
	cwbsvClassHostSysAlert	= 80,
	cwbsvClassHostSysIntegrity	= 90,
	cwbsvClassHostActionRequired	= 99
    } 	cwbsvErrorClassEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2131-1A8F-11d2-849C-0004AC94E175") 
enum cwbrcReturnCodeEnum
    {	cwbrcInvalidSystemHandle	= 6000,
	cwbrcInvalidProgram	= 6001,
	cwbrcSystemName	= 6002,
	cwbrcCommandString	= 6003,
	cwbrcProgramName	= 6004,
	cwbrcLibraryName	= 6005,
	cwbrcInvalidType	= 6006,
	cwbrcInvalidParmLength	= 6007,
	cwbrcInvalidParm	= 6008,
	cwbrcTooManyParms	= 6009,
	cwbrcIndexRangeError	= 6010,
	cwbrcRejectedUserExit	= 6011,
	cwbrcUserExitError	= 6012,
	cwbrcCommandFailed	= 6013,
	cwbrcProgramNotFound	= 6014,
	cwbrcProgramError	= 6015,
	cwbrcCommandTooLong	= 6016,
	cwbrcUnexpectedError	= 6099
    } 	cwbrcReturnCodeEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2132-1A8F-11d2-849C-0004AC94E175") 
enum cwbnlReturnCodeEnum
    {	cwbnlCnvUnsupported	= 6101,
	cwbnlCnvTblInvalid	= 6102,
	cwbnlCnvTblMissing	= 6103,
	cwbnlCnvErrGet	= 6104,
	cwbnlCnvErrComm	= 6105,
	cwbnlCnvErrServer	= 6106,
	cwbnlCnvErrStatus	= 6107,
	cwbnlCnvIncompleteMultibyteInputChar	= 6108,
	cwbnlCnvInvalidSISOStatus	= 6109,
	cwbnlCnvInvalidPadLength	= 6110
    } 	cwbnlReturnCodeEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2134-1A8F-11d2-849C-0004AC94E175") 
enum cwbnlCodePageEnum
    {	cwbnlCodePageAS400	= 1,
	cwbnlCodePageClientOEM	= 2,
	cwbnlCodePageClientANSI	= 3,
	cwbnlCodePageUnicodeBigEndian	= 1200,
	cwbnlCodePageClientUnicode	= 1202,
	cwbnlCodePageUTF8	= 1208,
	cwbnlCodePageUnicode	= 13488,
	cwbnlCodePageUnicodeF200	= 61952
    } 	cwbnlCodePageEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2135-1A8F-11d2-849C-0004AC94E175") 
enum cwbdtTimeSeparatorEnum
    {	cwbdtTimeSepNotSpecified	= 0,
	cwbdtTimeSepColon	= 1,
	cwbdtTimeSepPeriod	= 2,
	cwbdtTimeSepComma	= 3,
	cwbdtTimeSepBlank	= 4
    } 	cwbdtTimeSeparatorEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2136-1A8F-11d2-849C-0004AC94E175") 
enum cwbdtTimeFormatEnum
    {	cwbdtTimeFmtHourMinSec	= 0,
	cwbdtTimeFmtUSA	= 1,
	cwbdtTimeFmtISO	= 2,
	cwbdtTimeFmtEUR	= 3,
	cwbdtTimeFmtJIS	= 4
    } 	cwbdtTimeFormatEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2137-1A8F-11d2-849C-0004AC94E175") 
enum cwbdtDateSeparatorEnum
    {	cwbdtDateSepNotSpecified	= 0,
	cwbdtDateSepSlash	= 1,
	cwbdtDateSepDash	= 2,
	cwbdtDateSepPeriod	= 3,
	cwbdtDateSepComma	= 4,
	cwbdtDateSepBlank	= 5
    } 	cwbdtDateSeparatorEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2138-1A8F-11d2-849C-0004AC94E175") 
enum cwbdtDateFormatEnum
    {	cwbdtDateFmtJulian	= 0,
	cwbdtDateFmtMonDayYr	= 1,
	cwbdtDateFmtDayMonYr	= 2,
	cwbdtDateFmtYrMonDay	= 3,
	cwbdtDateFmtUSA	= 4,
	cwbdtDateFmtISO	= 5,
	cwbdtDateFmtEUR	= 6,
	cwbdtDateFmtJIS	= 7
    } 	cwbdtDateFormatEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2139-1A8F-11d2-849C-0004AC94E175") 
enum cwbdtDecimalSeparatorEnum
    {	cwbdtDecSepPeriod	= 0,
	cwbdtDecSepComma	= 1
    } 	cwbdtDecimalSeparatorEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA213A-1A8F-11d2-849C-0004AC94E175") 
enum cwbdtAS400FileCreateEnum
    {	cwbdtCreateMember	= 0,
	cwbdtCreateFileAndMember	= 1,
	cwbdtReplaceMember	= 2,
	cwbdtAppendToMember	= 3
    } 	cwbdtAS400FileCreateEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA213B-1A8F-11d2-849C-0004AC94E175") 
enum cwbdtObjectAuthorityEnum
    {	cwbdtObjAuthReadWrite	= 0,
	cwbdtObjAuthReadOnly	= 1,
	cwbdtObjAuthAll	= 2,
	cwbdtObjAuthNone	= 3
    } 	cwbdtObjectAuthorityEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA213C-1A8F-11d2-849C-0004AC94E175") 
enum cwbdtFileTypeEnum
    {	cwbdtFileTypeNotSet	= 0,
	cwbdtASCIIText	= 1,
	cwbdtDosRandom	= 2,
	cwbdtBasicSequential	= 3,
	cwbdtBasicRandom	= 4,
	cwbdtDIF	= 5,
	cwbdtNoConversion	= 6,
	cwbdtDosRandomType2	= 8,
	cwbdtBIFF4	= 9,
	cwbdtBIFF3	= 10,
	cwbdtBIFF5	= 11,
	cwbdtCSV	= 12,
	cwbdtWK4	= 13,
	cwbdtTabDelimitedText	= 14,
	cwbdtBIFF7	= 15,
	cwbdtBIFF8	= 16,
	cwbdt123	= 17,
	cwbdt123v9	= 19,
	cwbdtUnicodeText	= 20,
	cwbdtExcelXML	= 21,
	cwbdtHTML	= 100
    } 	cwbdtFileTypeEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA213D-1A8F-11d2-849C-0004AC94E175") 
enum cwbdtExistingOutputFileEnum
    {	cwbdtOverwriteOutFile	= 0,
	cwbdtAppendOutFile	= 1,
	cwbdtFailDownload	= 2,
	cwbdtCreateOverwriteOutFileEvenWhenEmptyResultsSet	= 3
    } 	cwbdtExistingOutputFileEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA213F-1A8F-11d2-849C-0004AC94E175") 
enum cwbdtHTMLConversionTypeEnum
    {	cwbdtHTMLConvANSI	= 0,
	cwbdtHTMLConvASCII	= 1,
	cwbdtHTMLConvUTF8	= 2
    } 	cwbdtHTMLConversionTypeEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2140-1A8F-11d2-849C-0004AC94E175") 
enum cwbdtDateTimeLocationEnum
    {	cwbdtDateTimeDoNotInclude	= 0,
	cwbdtDateTimeUpperLeft	= 1,
	cwbdtDateTimeLowerLeft	= 2,
	cwbdtDateTimeUpperRight	= 3,
	cwbdtDateTimeLowerRight	= 4
    } 	cwbdtDateTimeLocationEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2141-1A8F-11d2-849C-0004AC94E175") 
enum cwbdtTableAlignmentEnum
    {	cwbdtTableAlignLeft	= 0,
	cwbdtTableAlignCenter	= 1,
	cwbdtTableAlignRight	= 2
    } 	cwbdtTableAlignmentEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2142-1A8F-11d2-849C-0004AC94E175") 
enum cwbdtSizeUnitsEnum
    {	cwbdtSizePercentOfWindow	= 0,
	cwbdtSizePixels	= 1
    } 	cwbdtSizeUnitsEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2143-1A8F-11d2-849C-0004AC94E175") 
enum cwbdtCaptionAlignmentEnum
    {	cwbdtCaptionAlignBrowserDefault	= 0,
	cwbdtCaptionAlignTop	= 1,
	cwbdtCaptionAlignBottom	= 2,
	cwbdtCaptionAlignLeft	= 3,
	cwbdtCaptionAlignRight	= 4
    } 	cwbdtCaptionAlignmentEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2144-1A8F-11d2-849C-0004AC94E175") 
enum cwbdtTextSizeEnum
    {	cwbdtTextNormal	= 0,
	cwbdtTextSmall	= 1,
	cwbdtTextLarge	= 2
    } 	cwbdtTextSizeEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2145-1A8F-11d2-849C-0004AC94E175") 
enum cwbdtVerticalAlignEnum
    {	cwbdtVertAlignBrowserDefault	= 0,
	cwbdtVertAlignTop	= 1,
	cwbdtVertAlignMiddle	= 2,
	cwbdtVertAlignBottom	= 3
    } 	cwbdtVerticalAlignEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2146-1A8F-11d2-849C-0004AC94E175") 
enum cwbdtHorizontalAlignEnum
    {	cwbdtHorizAlignBrowserDefault	= 0,
	cwbdtHorizAlignLeft	= 1,
	cwbdtHorizAlignCenter	= 2,
	cwbdtHorizAlignRight	= 3
    } 	cwbdtHorizontalAlignEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2147-1A8F-11d2-849C-0004AC94E175") 
enum cwbdtCellDataAlignEnum
    {	cwbdtCellDataAlignSameAsRow	= 0,
	cwbdtCellDataAlignLeft	= 1,
	cwbdtCellDataAlignCenter	= 2,
	cwbdtCellDataAlignRight	= 3
    } 	cwbdtCellDataAlignEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2148-1A8F-11d2-849C-0004AC94E175") 
enum cwbdtExtraRowsActionEnum
    {	cwbdtTruncExtraRows	= 0,
	cwbdtGenerateMultTables	= 1,
	cwbdtGenerateMultDocs	= 2
    } 	cwbdtExtraRowsActionEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2149-1A8F-11d2-849C-0004AC94E175") 
enum cwbdtFewerRowsActionEnum
    {	cwbdtIgnoreExtraRows	= 0,
	cwbdtGenerateBlankRows	= 1
    } 	cwbdtFewerRowsActionEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA214A-1A8F-11d2-849C-0004AC94E175") 
enum cwbdtTextStyleEnum
    {	cwbdtTextBrowserDefaultStyle	= 0,
	cwbdtTextBold	= 1,
	cwbdtTextItalic	= 2,
	cwbdtTextUnderline	= 4,
	cwbdtTextFixedWidth	= 8
    } 	cwbdtTextStyleEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA214B-1A8F-11d2-849C-0004AC94E175") 
enum cwbdtConstants
    {	cwbdtNoMaximum	= 0xffffffff,
	cwbdtBrowserDefault	= 0xfffffffe
    } 	cwbdtConstants;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA214C-1A8F-11d2-849C-0004AC94E175") 
enum cwbdtTransferStatusEnum
    {	cwbdtStatusCompletedOK	= 0,
	cwbdtStatusCompletedWithWarning	= 1,
	cwbdtStatusCompletedWithError	= 2,
	cwbdtStatusConnectingToAS400	= 3,
	cwbdtStatusPerformingQuery	= 4,
	cwbdtStatusReceivingData	= 5,
	cwbdtStatusPerformingFileSetup	= 6,
	cwbdtStatusSendingData	= 7,
	cwbdtStatusRowsTransferred	= 8,
	cwbdtStatusUpdatingPCFile	= 9
    } 	cwbdtTransferStatusEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA214D-1A8F-11d2-849C-0004AC94E175") 
enum cwbdtDataErrorEnum
    {	cwbdtWarningTruncation	= 1,
	cwbdtWarningRounding	= 2,
	cwbdtWarningMissingData	= 3,
	cwbdtWarningUntranslatableField	= 4,
	cwbdtErrorTruncation	= 5,
	cwbdtErrorRounding	= 6,
	cwbdtErrorMissingData	= 7,
	cwbdtErrorUntranslatableField	= 8
    } 	cwbdtDataErrorEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA214E-1A8F-11d2-849C-0004AC94E175") 
enum cwbdtSortSequenceTypeEnum
    {	cwbdtSortAS400Default	= 0,
	cwbdtSortHexadecimal	= 1,
	cwbdtSortUserSpecifiedTable	= 2,
	cwbdtSortSharedWeightTable	= 3,
	cwbdtSortUniqueWeightTable	= 4
    } 	cwbdtSortSequenceTypeEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA214F-1A8F-11d2-849C-0004AC94E175") 
enum cwbdtReturnCodeEnum
    {	cwbdtFileAlreadyExists	= 7002,
	cwbdtTooManyRecords	= 7003,
	cwbdtNoMatchingData	= 7004,
	cwbdtIncorrectData	= 7005,
	cwbdtInvalidFieldType	= 7006,
	cwbdtDataRounded	= 7007,
	cwbdtTooManyDigits	= 7008,
	cwbdtPCDataTruncated	= 7009,
	cwbdtDataPadded	= 7010,
	cwbdtAS400DataTruncated	= 7011,
	cwbdtUnexpectedError	= 7012,
	cwbdtInvalidRecordLength	= 7013,
	cwbdtErrorClosingFile	= 7014,
	cwbdtErrorOpeningFile	= 7015,
	cwbdtErrorWritingFile	= 7016,
	cwbdtDiskFull	= 7017,
	cwbdtNoRecordsToTransfer	= 7018,
	cwbdtDataMissing	= 7019,
	cwbdtExtraDataNotTransferred	= 7020,
	cwbdtFDFRequired	= 7021,
	cwbdtFileNotFound	= 7022,
	cwbdtFDFEmpty	= 7023,
	cwbdtTooManyFields	= 7024,
	cwbdtIncorrectFieldLength	= 7025,
	cwbdtInvalidPCFile	= 7026,
	cwbdtInvalidPCType	= 7027,
	cwbdtInvalidFDF	= 7028,
	cwbdtFieldTypeNotCompat	= 7029,
	cwbdtFieldNameTooLong	= 7030,
	cwbdtInvalidDecPosition	= 7031,
	cwbdtNotEnoughMemory	= 7032,
	cwbdtHostFileNameRequired	= 7033,
	cwbdtPCFileNameRequired	= 7034,
	cwbdtInvalidHostFile	= 7035,
	cwbdtNoFilesInLibrary	= 7036,
	cwbdtCantTransferSourceAndDB	= 7037,
	cwbdtInvalidLibFileName	= 7038,
	cwbdtInvalidFRFFile	= 7039,
	cwbdtHostFileDoesntExist	= 7040,
	cwbdtFilesDontMatch	= 7041,
	cwbdtInvalidColumnType	= 7042,
	cwbdtInvalidSortSequence	= 7043,
	cwbdtAppendFileDoesntExist	= 7044,
	cwbdtLibraryDoesntExist	= 7045,
	cwbdtLibListEntryRemoved	= 7046,
	cwbdtAppendSourceWarning	= 7047,
	cwbdtUploadFDFRequired	= 7048,
	cwbdtTemplateDoesntExist	= 7049,
	cwbdtTemplateTagRequired	= 7050,
	cwbdtInvalidTemplateTag	= 7051,
	cwbdtCreateInitFailure	= 7052,
	cwbdtCantLoadWK4ConvFile	= 7053,
	cwbdtNoValidData	= 7054,
	cwbdtInvalidPCFileFormat	= 7055,
	cwbdtInvalidWorksheet	= 7056,
	cwbdtAS400File	= 7057,
	cwbdtSSLNotAvailable	= 7058,
	cwbdtCantChangeSecurity	= 7059,
	cwbdtCantSetMember	= 7060,
	cwbdtSQLStatementTooLong	= 7061,
	cwbdtDatalinkNotSupported	= 7062,
	cwbdtMemberNameRequired	= 7063,
	cwbdtRequestAlreadyExists	= 7064,
	cwbdtRowTooLong	= 7065,
	cwbdtBadValueDefaulted	= 7066,
	cwbdtExpressPathNotFound	= 7067,
	cwbdtWK4NotEnoughMemory	= 7068,
	cwbdtWK4MappingNotFound	= 7069,
	cwbdtWK4InvalidConvTable	= 7070,
	cwbdtWK4ConvInitError	= 7071,
	cwbdtWK4FilesWrongLevels	= 7072,
	cwbdtTooManyFiles	= 7073,
	cwbdtErrorAddingLibToList	= 7074,
	cwbdtWK4ConversionError	= 7075,
	cwbdtBadTransferRequest	= 7400,
	cwbdtUnicodeConversionError	= 7401,
	cwbdtPCFileSameAsFDFFile	= 7402,
	cwbdtTransferRequestNotExist	= 7403,
	cwbdtTransferRequestExists	= 7404,
	cwbdtWK4NoTranslationDLL	= 7405,
	cwbdtWK4NonMatchingLevels	= 7406,
	cwbdtWK4OpenInitializationError	= 7407,
	cwbdtWK4InvalidTable	= 7408,
	cwbdtWK4NoMappingForCCSID	= 7409,
	cwbdtBadLibraryListIndex	= 7410,
	cwbdtMemberNameNotSpecified	= 7411,
	cwbdtDatabaseServerError	= 7412,
	cwbdtLibraryAlreadyInList	= 7463,
	cwbdtLibraryNotFoundInList	= 7464,
	cwbdtLibraryNameNotValid	= 7465,
	cwbdtGeneralLibListFailure	= 7466,
	cwbdtDBStartError	= 7467,
	cwbdtSystemConfigFailure	= 7468,
	cwbdtCancelTimedOut	= 7470,
	cwbdtCancelInProgress	= 7471,
	cwbdtCancelProcessedSuccessfully	= 7472,
	cwbdtInvalidMemberName	= 7474,
	cwbdtUnsupportedFieldType	= 7475,
	cwbdtCannotUseExcelFDF	= 7476
    } 	cwbdtReturnCodeEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("B1EA2150-1A8F-11d2-849C-0004AC94E175") 
enum cwbdbReturnCodeEnum
    {	cwbdbCannotContactServer	= 6001,
	cwbdbAttributesFailure	= 6002,
	cwbdbServerAlreadyStarted	= 6003,
	cwbdbInvalidDRDAPackageSize	= 6004,
	cwbdbRequestMemoryAllocationFailure	= 6005,
	cwbdbRequestInvalidConversion	= 6006,
	cwbdbServerNotActive	= 6007,
	cwbdbParameterError	= 6008,
	cwbdbCloneCreationError	= 6009,
	cwbdbInvalidDataFormatForConnection	= 6010,
	cwbdbDataFormatInUse	= 6011,
	cwbdbInvalidDataFormatForData	= 6012,
	cwbdbStringArgumentTooLong	= 6013,
	cwbdbInvalidInternalArgument	= 6014,
	cwbdbInvalidNumericArgument	= 6015,
	cwbdbInvalidArgument	= 6016,
	cwbdbStatementNotSelect	= 6017,
	cwbdbStreamFetchNotComplete	= 6018,
	cwbdbStreamFetchNotActive	= 6019,
	cwbdbMissingDataProcessor	= 6020,
	cwbdbIllegalCloneRequestType	= 6021,
	cwbdbUnsolicitedData	= 6022,
	cwbdbMissingData	= 6023,
	cwbdbParameterInvalidBitstream	= 6024,
	cwbdbConsistencyTokenError	= 6025,
	cwbdbInvalidFunction	= 6026,
	cwbdbFormatInvalidArgument	= 6027,
	cwbdbInvalidColumnPosition	= 6028,
	cwbdbInvalidColumnType	= 6029,
	cwbdbRowVectorNotEmpty	= 6030,
	cwbdbRowVectorEmpty	= 6031,
	cwbdbMemoryAllocationFailure	= 6032,
	cwbdbInvalidConversion	= 6033,
	cwbdbDatastreamTooShort	= 6034,
	cwbdbSQLWarning	= 6035,
	cwbdbSQLError	= 6036,
	cwbdbSQLParameterWarning	= 6037,
	cwbdbSQLParameterError	= 6038,
	cwbdbListServerWarning	= 6039,
	cwbdbListServerError	= 6040,
	cwbdbListParameterWarning	= 6041,
	cwbdbListParameterError	= 6042,
	cwbdbNDBFileServerWarning	= 6043,
	cwbdbNDBFileServerError	= 6044,
	cwbdbFileParameterWarning	= 6045,
	cwbdbFileParameterError	= 6046,
	cwbdbGeneralServerWarning	= 6047,
	cwbdbGeneralServerError	= 6048,
	cwbdbExitProgramWarning	= 6049,
	cwbdbExitProgramError	= 6050,
	cwbdbDataBufferTooSmall	= 6051,
	cwbdbNLConversionError	= 6052,
	cwbdbCommunicationsError	= 6053,
	cwbdbInvalidArgumentAPI	= 6054,
	cwbdbMissingDataHandler	= 6055,
	cwbdbRequestDatastreamNotValid	= 6056,
	cwbdbServerUnable	= 6057,
	cwbdbWorkQueueStartError	= 6058,
	cwbdbWorkQueueCreateError	= 6059,
	cwbdbInitializationError	= 6060,
	cwbdbServerAttributesError	= 6061,
	cwbdbClientLevelError	= 6062,
	cwbdbClientLangFeatureCodeError	= 6063,
	cwbdbClientCCSIDError	= 6064,
	cwbdbTranslationIndicatorError	= 6065,
	cwbdbReturnServerAttributesError	= 6066,
	cwbdbServerAttributesRequest	= 6067,
	cwbdbReturnAttributesError	= 6068,
	cwbdbServerAttributesMissing	= 6069,
	cwbdbServerLangFeatureCodeConvError	= 6070,
	cwbdbServerLevelConversionError	= 6071,
	cwbdbServerLanguageTableError	= 6072,
	cwbdbServerLanguageLibraryError	= 6073,
	cwbdbServerLanguageIDError	= 6074,
	cwbdbCommDequeueError	= 6075,
	cwbdbCommEnqueueError	= 6076,
	cwbdbUnsupportedColumnType	= 6077,
	cwbdbServerInUse	= 6078,
	cwbdbServerRelationalDBConvError	= 6079,
	cwbdbServerFunctionNotAvailable	= 6080,
	cwbdbFunctionNotValidAfterConnect	= 6081,
	cwbdbLastStreamChunk	= 6099
    } 	cwbdbReturnCodeEnum;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("4F89D944-AEE9-4173-8D6f-AB58EE836F56") 
enum cwbdtFDFFormatEnum
    {	cwbdtStandardFDF	= 0,
	cwbdtEnhancedFDF	= 1
    } 	cwbdtFDFFormatEnum;












EXTERN_C const IID LIBID_cwbx;

#ifndef __IcwbxDatabaseDownloadRequest_INTERFACE_DEFINED__
#define __IcwbxDatabaseDownloadRequest_INTERFACE_DEFINED__

/* interface IcwbxDatabaseDownloadRequest */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][hidden][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseDownloadRequest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("35DD1AA2-0CAB-11D3-8392-C4CC6678F234")
    IcwbxDatabaseDownloadRequest : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AS400File( 
            /* [retval][out] */ IcwbxDatabaseAS400File **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Convert65535( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Convert65535( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Errors( 
            /* [retval][out] */ IcwbxErrors **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Format( 
            /* [retval][out] */ IcwbxDatabaseFormatOptions **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LogDataErrorPositions( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LogDataErrorPositions( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_pcFile( 
            /* [retval][out] */ IcwbxDatabaseDownloadPCFile **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Query( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Query( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StopOnTruncation( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StopOnTruncation( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_System( 
            /* [retval][out] */ IcwbxSystem **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_System( 
            /* [in] */ IcwbxSystem *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StopOnUntranslatableField( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StopOnUntranslatableField( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Cancel( 
            /* [defaultvalue][optional][in] */ VARIANT_BOOL force = 0,
            /* [defaultvalue][optional][in] */ long timeOut = 10) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Download( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE DownloadAsync( 
            /* [defaultvalue][optional][in] */ long rowStatusInterval = 0) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadRequest( 
            /* [in] */ BSTR fileName) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveRequest( 
            /* [in] */ BSTR fileName,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL overwriteIfExists = -1) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UserLibraryList( 
            /* [retval][out] */ IcwbxDatabaseUserLibraryList **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_QueryDataTransferSyntax( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_QueryDataTransferSyntax( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UseFieldAlias( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UseFieldAlias( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TransferResults( 
            /* [retval][out] */ IcwbxDatabaseTransferResults **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseDownloadRequestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseDownloadRequest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseDownloadRequest * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AS400File )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [retval][out] */ IcwbxDatabaseAS400File **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Convert65535 )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Convert65535 )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Errors )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [retval][out] */ IcwbxErrors **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Format )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [retval][out] */ IcwbxDatabaseFormatOptions **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LogDataErrorPositions )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LogDataErrorPositions )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_pcFile )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [retval][out] */ IcwbxDatabaseDownloadPCFile **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Query )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Query )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StopOnTruncation )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StopOnTruncation )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_System )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [retval][out] */ IcwbxSystem **pVal);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_System )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [in] */ IcwbxSystem *newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StopOnUntranslatableField )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StopOnUntranslatableField )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Cancel )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL force,
            /* [defaultvalue][optional][in] */ long timeOut);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Download )( 
            IcwbxDatabaseDownloadRequest * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DownloadAsync )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [defaultvalue][optional][in] */ long rowStatusInterval);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadRequest )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [in] */ BSTR fileName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveRequest )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [in] */ BSTR fileName,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL overwriteIfExists);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UserLibraryList )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [retval][out] */ IcwbxDatabaseUserLibraryList **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_QueryDataTransferSyntax )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_QueryDataTransferSyntax )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UseFieldAlias )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UseFieldAlias )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TransferResults )( 
            IcwbxDatabaseDownloadRequest * This,
            /* [retval][out] */ IcwbxDatabaseTransferResults **pVal);
        
        END_INTERFACE
    } IcwbxDatabaseDownloadRequestVtbl;

    interface IcwbxDatabaseDownloadRequest
    {
        CONST_VTBL struct IcwbxDatabaseDownloadRequestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseDownloadRequest_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseDownloadRequest_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseDownloadRequest_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseDownloadRequest_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseDownloadRequest_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseDownloadRequest_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseDownloadRequest_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseDownloadRequest_get_AS400File(This,pVal)	\
    (This)->lpVtbl -> get_AS400File(This,pVal)

#define IcwbxDatabaseDownloadRequest_get_Convert65535(This,pVal)	\
    (This)->lpVtbl -> get_Convert65535(This,pVal)

#define IcwbxDatabaseDownloadRequest_put_Convert65535(This,newVal)	\
    (This)->lpVtbl -> put_Convert65535(This,newVal)

#define IcwbxDatabaseDownloadRequest_get_Errors(This,pVal)	\
    (This)->lpVtbl -> get_Errors(This,pVal)

#define IcwbxDatabaseDownloadRequest_get_Format(This,pVal)	\
    (This)->lpVtbl -> get_Format(This,pVal)

#define IcwbxDatabaseDownloadRequest_get_LogDataErrorPositions(This,pVal)	\
    (This)->lpVtbl -> get_LogDataErrorPositions(This,pVal)

#define IcwbxDatabaseDownloadRequest_put_LogDataErrorPositions(This,newVal)	\
    (This)->lpVtbl -> put_LogDataErrorPositions(This,newVal)

#define IcwbxDatabaseDownloadRequest_get_pcFile(This,pVal)	\
    (This)->lpVtbl -> get_pcFile(This,pVal)

#define IcwbxDatabaseDownloadRequest_get_Query(This,pVal)	\
    (This)->lpVtbl -> get_Query(This,pVal)

#define IcwbxDatabaseDownloadRequest_put_Query(This,newVal)	\
    (This)->lpVtbl -> put_Query(This,newVal)

#define IcwbxDatabaseDownloadRequest_get_StopOnTruncation(This,pVal)	\
    (This)->lpVtbl -> get_StopOnTruncation(This,pVal)

#define IcwbxDatabaseDownloadRequest_put_StopOnTruncation(This,newVal)	\
    (This)->lpVtbl -> put_StopOnTruncation(This,newVal)

#define IcwbxDatabaseDownloadRequest_get_System(This,pVal)	\
    (This)->lpVtbl -> get_System(This,pVal)

#define IcwbxDatabaseDownloadRequest_putref_System(This,newVal)	\
    (This)->lpVtbl -> putref_System(This,newVal)

#define IcwbxDatabaseDownloadRequest_get_StopOnUntranslatableField(This,pVal)	\
    (This)->lpVtbl -> get_StopOnUntranslatableField(This,pVal)

#define IcwbxDatabaseDownloadRequest_put_StopOnUntranslatableField(This,newVal)	\
    (This)->lpVtbl -> put_StopOnUntranslatableField(This,newVal)

#define IcwbxDatabaseDownloadRequest_Cancel(This,force,timeOut)	\
    (This)->lpVtbl -> Cancel(This,force,timeOut)

#define IcwbxDatabaseDownloadRequest_Download(This)	\
    (This)->lpVtbl -> Download(This)

#define IcwbxDatabaseDownloadRequest_DownloadAsync(This,rowStatusInterval)	\
    (This)->lpVtbl -> DownloadAsync(This,rowStatusInterval)

#define IcwbxDatabaseDownloadRequest_LoadRequest(This,fileName)	\
    (This)->lpVtbl -> LoadRequest(This,fileName)

#define IcwbxDatabaseDownloadRequest_SaveRequest(This,fileName,overwriteIfExists)	\
    (This)->lpVtbl -> SaveRequest(This,fileName,overwriteIfExists)

#define IcwbxDatabaseDownloadRequest_get_UserLibraryList(This,pVal)	\
    (This)->lpVtbl -> get_UserLibraryList(This,pVal)

#define IcwbxDatabaseDownloadRequest_get_QueryDataTransferSyntax(This,pVal)	\
    (This)->lpVtbl -> get_QueryDataTransferSyntax(This,pVal)

#define IcwbxDatabaseDownloadRequest_put_QueryDataTransferSyntax(This,newVal)	\
    (This)->lpVtbl -> put_QueryDataTransferSyntax(This,newVal)

#define IcwbxDatabaseDownloadRequest_get_UseFieldAlias(This,pVal)	\
    (This)->lpVtbl -> get_UseFieldAlias(This,pVal)

#define IcwbxDatabaseDownloadRequest_put_UseFieldAlias(This,newVal)	\
    (This)->lpVtbl -> put_UseFieldAlias(This,newVal)

#define IcwbxDatabaseDownloadRequest_get_TransferResults(This,pVal)	\
    (This)->lpVtbl -> get_TransferResults(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest_get_AS400File_Proxy( 
    IcwbxDatabaseDownloadRequest * This,
    /* [retval][out] */ IcwbxDatabaseAS400File **pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest_get_AS400File_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest_get_Convert65535_Proxy( 
    IcwbxDatabaseDownloadRequest * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest_get_Convert65535_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest_put_Convert65535_Proxy( 
    IcwbxDatabaseDownloadRequest * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest_put_Convert65535_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest_get_Errors_Proxy( 
    IcwbxDatabaseDownloadRequest * This,
    /* [retval][out] */ IcwbxErrors **pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest_get_Errors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest_get_Format_Proxy( 
    IcwbxDatabaseDownloadRequest * This,
    /* [retval][out] */ IcwbxDatabaseFormatOptions **pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest_get_Format_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest_get_LogDataErrorPositions_Proxy( 
    IcwbxDatabaseDownloadRequest * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest_get_LogDataErrorPositions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest_put_LogDataErrorPositions_Proxy( 
    IcwbxDatabaseDownloadRequest * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest_put_LogDataErrorPositions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest_get_pcFile_Proxy( 
    IcwbxDatabaseDownloadRequest * This,
    /* [retval][out] */ IcwbxDatabaseDownloadPCFile **pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest_get_pcFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest_get_Query_Proxy( 
    IcwbxDatabaseDownloadRequest * This,
    /* [retval][out] */ VARIANT *pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest_get_Query_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest_put_Query_Proxy( 
    IcwbxDatabaseDownloadRequest * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest_put_Query_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest_get_StopOnTruncation_Proxy( 
    IcwbxDatabaseDownloadRequest * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest_get_StopOnTruncation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest_put_StopOnTruncation_Proxy( 
    IcwbxDatabaseDownloadRequest * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest_put_StopOnTruncation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest_get_System_Proxy( 
    IcwbxDatabaseDownloadRequest * This,
    /* [retval][out] */ IcwbxSystem **pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest_get_System_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest_putref_System_Proxy( 
    IcwbxDatabaseDownloadRequest * This,
    /* [in] */ IcwbxSystem *newVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest_putref_System_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest_get_StopOnUntranslatableField_Proxy( 
    IcwbxDatabaseDownloadRequest * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest_get_StopOnUntranslatableField_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest_put_StopOnUntranslatableField_Proxy( 
    IcwbxDatabaseDownloadRequest * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest_put_StopOnUntranslatableField_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest_Cancel_Proxy( 
    IcwbxDatabaseDownloadRequest * This,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL force,
    /* [defaultvalue][optional][in] */ long timeOut);


void __RPC_STUB IcwbxDatabaseDownloadRequest_Cancel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest_Download_Proxy( 
    IcwbxDatabaseDownloadRequest * This);


void __RPC_STUB IcwbxDatabaseDownloadRequest_Download_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest_DownloadAsync_Proxy( 
    IcwbxDatabaseDownloadRequest * This,
    /* [defaultvalue][optional][in] */ long rowStatusInterval);


void __RPC_STUB IcwbxDatabaseDownloadRequest_DownloadAsync_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest_LoadRequest_Proxy( 
    IcwbxDatabaseDownloadRequest * This,
    /* [in] */ BSTR fileName);


void __RPC_STUB IcwbxDatabaseDownloadRequest_LoadRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest_SaveRequest_Proxy( 
    IcwbxDatabaseDownloadRequest * This,
    /* [in] */ BSTR fileName,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL overwriteIfExists);


void __RPC_STUB IcwbxDatabaseDownloadRequest_SaveRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest_get_UserLibraryList_Proxy( 
    IcwbxDatabaseDownloadRequest * This,
    /* [retval][out] */ IcwbxDatabaseUserLibraryList **pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest_get_UserLibraryList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest_get_QueryDataTransferSyntax_Proxy( 
    IcwbxDatabaseDownloadRequest * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest_get_QueryDataTransferSyntax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest_put_QueryDataTransferSyntax_Proxy( 
    IcwbxDatabaseDownloadRequest * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest_put_QueryDataTransferSyntax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest_get_UseFieldAlias_Proxy( 
    IcwbxDatabaseDownloadRequest * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest_get_UseFieldAlias_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest_put_UseFieldAlias_Proxy( 
    IcwbxDatabaseDownloadRequest * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest_put_UseFieldAlias_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest_get_TransferResults_Proxy( 
    IcwbxDatabaseDownloadRequest * This,
    /* [retval][out] */ IcwbxDatabaseTransferResults **pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest_get_TransferResults_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseDownloadRequest_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseUploadRequest_INTERFACE_DEFINED__
#define __IcwbxDatabaseUploadRequest_INTERFACE_DEFINED__

/* interface IcwbxDatabaseUploadRequest */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][hidden][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseUploadRequest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("35DD1AA5-0CAB-11D3-8392-C4CC6678F234")
    IcwbxDatabaseUploadRequest : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AS400File( 
            /* [retval][out] */ IcwbxDatabaseAS400File **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Convert65535( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Convert65535( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Errors( 
            /* [retval][out] */ IcwbxErrors **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LogDataErrorPositions( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LogDataErrorPositions( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_pcFile( 
            /* [retval][out] */ IcwbxDatabaseUploadPCFile **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StopOnMissingData( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StopOnMissingData( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StopOnRounding( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StopOnRounding( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StopOnTruncation( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StopOnTruncation( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_System( 
            /* [retval][out] */ IcwbxSystem **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_System( 
            /* [in] */ IcwbxSystem *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Cancel( 
            /* [defaultvalue][optional][in] */ VARIANT_BOOL force = 0,
            /* [defaultvalue][optional][in] */ long timeOut = 10) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadRequest( 
            /* [in] */ BSTR fileName) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveRequest( 
            /* [in] */ BSTR fileName,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL overwriteIfxists = -1) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Upload( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE UploadAsync( 
            /* [defaultvalue][optional][in] */ long rowStatusInterval = 0) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UserLibraryList( 
            /* [retval][out] */ IcwbxDatabaseUserLibraryList **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TransferResults( 
            /* [retval][out] */ IcwbxDatabaseTransferResults **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseUploadRequestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseUploadRequest * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseUploadRequest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseUploadRequest * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseUploadRequest * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseUploadRequest * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseUploadRequest * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseUploadRequest * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AS400File )( 
            IcwbxDatabaseUploadRequest * This,
            /* [retval][out] */ IcwbxDatabaseAS400File **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Convert65535 )( 
            IcwbxDatabaseUploadRequest * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Convert65535 )( 
            IcwbxDatabaseUploadRequest * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Errors )( 
            IcwbxDatabaseUploadRequest * This,
            /* [retval][out] */ IcwbxErrors **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LogDataErrorPositions )( 
            IcwbxDatabaseUploadRequest * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LogDataErrorPositions )( 
            IcwbxDatabaseUploadRequest * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_pcFile )( 
            IcwbxDatabaseUploadRequest * This,
            /* [retval][out] */ IcwbxDatabaseUploadPCFile **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StopOnMissingData )( 
            IcwbxDatabaseUploadRequest * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StopOnMissingData )( 
            IcwbxDatabaseUploadRequest * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StopOnRounding )( 
            IcwbxDatabaseUploadRequest * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StopOnRounding )( 
            IcwbxDatabaseUploadRequest * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StopOnTruncation )( 
            IcwbxDatabaseUploadRequest * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StopOnTruncation )( 
            IcwbxDatabaseUploadRequest * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_System )( 
            IcwbxDatabaseUploadRequest * This,
            /* [retval][out] */ IcwbxSystem **pVal);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_System )( 
            IcwbxDatabaseUploadRequest * This,
            /* [in] */ IcwbxSystem *newVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Cancel )( 
            IcwbxDatabaseUploadRequest * This,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL force,
            /* [defaultvalue][optional][in] */ long timeOut);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadRequest )( 
            IcwbxDatabaseUploadRequest * This,
            /* [in] */ BSTR fileName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveRequest )( 
            IcwbxDatabaseUploadRequest * This,
            /* [in] */ BSTR fileName,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL overwriteIfxists);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Upload )( 
            IcwbxDatabaseUploadRequest * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UploadAsync )( 
            IcwbxDatabaseUploadRequest * This,
            /* [defaultvalue][optional][in] */ long rowStatusInterval);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UserLibraryList )( 
            IcwbxDatabaseUploadRequest * This,
            /* [retval][out] */ IcwbxDatabaseUserLibraryList **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TransferResults )( 
            IcwbxDatabaseUploadRequest * This,
            /* [retval][out] */ IcwbxDatabaseTransferResults **pVal);
        
        END_INTERFACE
    } IcwbxDatabaseUploadRequestVtbl;

    interface IcwbxDatabaseUploadRequest
    {
        CONST_VTBL struct IcwbxDatabaseUploadRequestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseUploadRequest_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseUploadRequest_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseUploadRequest_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseUploadRequest_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseUploadRequest_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseUploadRequest_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseUploadRequest_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseUploadRequest_get_AS400File(This,pVal)	\
    (This)->lpVtbl -> get_AS400File(This,pVal)

#define IcwbxDatabaseUploadRequest_get_Convert65535(This,pVal)	\
    (This)->lpVtbl -> get_Convert65535(This,pVal)

#define IcwbxDatabaseUploadRequest_put_Convert65535(This,newVal)	\
    (This)->lpVtbl -> put_Convert65535(This,newVal)

#define IcwbxDatabaseUploadRequest_get_Errors(This,pVal)	\
    (This)->lpVtbl -> get_Errors(This,pVal)

#define IcwbxDatabaseUploadRequest_get_LogDataErrorPositions(This,pVal)	\
    (This)->lpVtbl -> get_LogDataErrorPositions(This,pVal)

#define IcwbxDatabaseUploadRequest_put_LogDataErrorPositions(This,newVal)	\
    (This)->lpVtbl -> put_LogDataErrorPositions(This,newVal)

#define IcwbxDatabaseUploadRequest_get_pcFile(This,pVal)	\
    (This)->lpVtbl -> get_pcFile(This,pVal)

#define IcwbxDatabaseUploadRequest_get_StopOnMissingData(This,pVal)	\
    (This)->lpVtbl -> get_StopOnMissingData(This,pVal)

#define IcwbxDatabaseUploadRequest_put_StopOnMissingData(This,newVal)	\
    (This)->lpVtbl -> put_StopOnMissingData(This,newVal)

#define IcwbxDatabaseUploadRequest_get_StopOnRounding(This,pVal)	\
    (This)->lpVtbl -> get_StopOnRounding(This,pVal)

#define IcwbxDatabaseUploadRequest_put_StopOnRounding(This,newVal)	\
    (This)->lpVtbl -> put_StopOnRounding(This,newVal)

#define IcwbxDatabaseUploadRequest_get_StopOnTruncation(This,pVal)	\
    (This)->lpVtbl -> get_StopOnTruncation(This,pVal)

#define IcwbxDatabaseUploadRequest_put_StopOnTruncation(This,newVal)	\
    (This)->lpVtbl -> put_StopOnTruncation(This,newVal)

#define IcwbxDatabaseUploadRequest_get_System(This,pVal)	\
    (This)->lpVtbl -> get_System(This,pVal)

#define IcwbxDatabaseUploadRequest_putref_System(This,newVal)	\
    (This)->lpVtbl -> putref_System(This,newVal)

#define IcwbxDatabaseUploadRequest_Cancel(This,force,timeOut)	\
    (This)->lpVtbl -> Cancel(This,force,timeOut)

#define IcwbxDatabaseUploadRequest_LoadRequest(This,fileName)	\
    (This)->lpVtbl -> LoadRequest(This,fileName)

#define IcwbxDatabaseUploadRequest_SaveRequest(This,fileName,overwriteIfxists)	\
    (This)->lpVtbl -> SaveRequest(This,fileName,overwriteIfxists)

#define IcwbxDatabaseUploadRequest_Upload(This)	\
    (This)->lpVtbl -> Upload(This)

#define IcwbxDatabaseUploadRequest_UploadAsync(This,rowStatusInterval)	\
    (This)->lpVtbl -> UploadAsync(This,rowStatusInterval)

#define IcwbxDatabaseUploadRequest_get_UserLibraryList(This,pVal)	\
    (This)->lpVtbl -> get_UserLibraryList(This,pVal)

#define IcwbxDatabaseUploadRequest_get_TransferResults(This,pVal)	\
    (This)->lpVtbl -> get_TransferResults(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest_get_AS400File_Proxy( 
    IcwbxDatabaseUploadRequest * This,
    /* [retval][out] */ IcwbxDatabaseAS400File **pVal);


void __RPC_STUB IcwbxDatabaseUploadRequest_get_AS400File_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest_get_Convert65535_Proxy( 
    IcwbxDatabaseUploadRequest * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseUploadRequest_get_Convert65535_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest_put_Convert65535_Proxy( 
    IcwbxDatabaseUploadRequest * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadRequest_put_Convert65535_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest_get_Errors_Proxy( 
    IcwbxDatabaseUploadRequest * This,
    /* [retval][out] */ IcwbxErrors **pVal);


void __RPC_STUB IcwbxDatabaseUploadRequest_get_Errors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest_get_LogDataErrorPositions_Proxy( 
    IcwbxDatabaseUploadRequest * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseUploadRequest_get_LogDataErrorPositions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest_put_LogDataErrorPositions_Proxy( 
    IcwbxDatabaseUploadRequest * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadRequest_put_LogDataErrorPositions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest_get_pcFile_Proxy( 
    IcwbxDatabaseUploadRequest * This,
    /* [retval][out] */ IcwbxDatabaseUploadPCFile **pVal);


void __RPC_STUB IcwbxDatabaseUploadRequest_get_pcFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest_get_StopOnMissingData_Proxy( 
    IcwbxDatabaseUploadRequest * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseUploadRequest_get_StopOnMissingData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest_put_StopOnMissingData_Proxy( 
    IcwbxDatabaseUploadRequest * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadRequest_put_StopOnMissingData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest_get_StopOnRounding_Proxy( 
    IcwbxDatabaseUploadRequest * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseUploadRequest_get_StopOnRounding_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest_put_StopOnRounding_Proxy( 
    IcwbxDatabaseUploadRequest * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadRequest_put_StopOnRounding_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest_get_StopOnTruncation_Proxy( 
    IcwbxDatabaseUploadRequest * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseUploadRequest_get_StopOnTruncation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest_put_StopOnTruncation_Proxy( 
    IcwbxDatabaseUploadRequest * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadRequest_put_StopOnTruncation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest_get_System_Proxy( 
    IcwbxDatabaseUploadRequest * This,
    /* [retval][out] */ IcwbxSystem **pVal);


void __RPC_STUB IcwbxDatabaseUploadRequest_get_System_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest_putref_System_Proxy( 
    IcwbxDatabaseUploadRequest * This,
    /* [in] */ IcwbxSystem *newVal);


void __RPC_STUB IcwbxDatabaseUploadRequest_putref_System_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest_Cancel_Proxy( 
    IcwbxDatabaseUploadRequest * This,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL force,
    /* [defaultvalue][optional][in] */ long timeOut);


void __RPC_STUB IcwbxDatabaseUploadRequest_Cancel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest_LoadRequest_Proxy( 
    IcwbxDatabaseUploadRequest * This,
    /* [in] */ BSTR fileName);


void __RPC_STUB IcwbxDatabaseUploadRequest_LoadRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest_SaveRequest_Proxy( 
    IcwbxDatabaseUploadRequest * This,
    /* [in] */ BSTR fileName,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL overwriteIfxists);


void __RPC_STUB IcwbxDatabaseUploadRequest_SaveRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest_Upload_Proxy( 
    IcwbxDatabaseUploadRequest * This);


void __RPC_STUB IcwbxDatabaseUploadRequest_Upload_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest_UploadAsync_Proxy( 
    IcwbxDatabaseUploadRequest * This,
    /* [defaultvalue][optional][in] */ long rowStatusInterval);


void __RPC_STUB IcwbxDatabaseUploadRequest_UploadAsync_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest_get_UserLibraryList_Proxy( 
    IcwbxDatabaseUploadRequest * This,
    /* [retval][out] */ IcwbxDatabaseUserLibraryList **pVal);


void __RPC_STUB IcwbxDatabaseUploadRequest_get_UserLibraryList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest_get_TransferResults_Proxy( 
    IcwbxDatabaseUploadRequest * This,
    /* [retval][out] */ IcwbxDatabaseTransferResults **pVal);


void __RPC_STUB IcwbxDatabaseUploadRequest_get_TransferResults_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseUploadRequest_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseUploadBIFFOptions_INTERFACE_DEFINED__
#define __IcwbxDatabaseUploadBIFFOptions_INTERFACE_DEFINED__

/* interface IcwbxDatabaseUploadBIFFOptions */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][hidden][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseUploadBIFFOptions;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4A8AFC51-A8D9-11D3-91F5-002035AE9B5D")
    IcwbxDatabaseUploadBIFFOptions : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UploadExtraSheets( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UploadExtraSheets( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_SendInfo( 
            /* [in] */ long newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseUploadBIFFOptionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseUploadBIFFOptions * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseUploadBIFFOptions * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseUploadBIFFOptions * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseUploadBIFFOptions * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseUploadBIFFOptions * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseUploadBIFFOptions * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseUploadBIFFOptions * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UploadExtraSheets )( 
            IcwbxDatabaseUploadBIFFOptions * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UploadExtraSheets )( 
            IcwbxDatabaseUploadBIFFOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseUploadBIFFOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SendInfo )( 
            IcwbxDatabaseUploadBIFFOptions * This,
            /* [in] */ long newVal);
        
        END_INTERFACE
    } IcwbxDatabaseUploadBIFFOptionsVtbl;

    interface IcwbxDatabaseUploadBIFFOptions
    {
        CONST_VTBL struct IcwbxDatabaseUploadBIFFOptionsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseUploadBIFFOptions_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseUploadBIFFOptions_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseUploadBIFFOptions_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseUploadBIFFOptions_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseUploadBIFFOptions_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseUploadBIFFOptions_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseUploadBIFFOptions_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseUploadBIFFOptions_get_UploadExtraSheets(This,pVal)	\
    (This)->lpVtbl -> get_UploadExtraSheets(This,pVal)

#define IcwbxDatabaseUploadBIFFOptions_put_UploadExtraSheets(This,newVal)	\
    (This)->lpVtbl -> put_UploadExtraSheets(This,newVal)

#define IcwbxDatabaseUploadBIFFOptions_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#define IcwbxDatabaseUploadBIFFOptions_put_SendInfo(This,newVal)	\
    (This)->lpVtbl -> put_SendInfo(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadBIFFOptions_get_UploadExtraSheets_Proxy( 
    IcwbxDatabaseUploadBIFFOptions * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseUploadBIFFOptions_get_UploadExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadBIFFOptions_put_UploadExtraSheets_Proxy( 
    IcwbxDatabaseUploadBIFFOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadBIFFOptions_put_UploadExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadBIFFOptions_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseUploadBIFFOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadBIFFOptions_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadBIFFOptions_put_SendInfo_Proxy( 
    IcwbxDatabaseUploadBIFFOptions * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseUploadBIFFOptions_put_SendInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseUploadBIFFOptions_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadPCOptions_INTERFACE_DEFINED__
#define __IcwbxDatabaseDownloadPCOptions_INTERFACE_DEFINED__

/* interface IcwbxDatabaseDownloadPCOptions */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][hidden][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseDownloadPCOptions;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("35DD1AB0-0CAB-11D3-8392-C4CC6678F234")
    IcwbxDatabaseDownloadPCOptions : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CodePage( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CodePage( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExistingFileOption( 
            /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ExistingFileOption( 
            /* [in] */ cwbdtExistingOutputFileEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_fileDescriptionFile( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_fileDescriptionFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReceiveInfo( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseDownloadPCOptionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseDownloadPCOptions * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseDownloadPCOptions * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseDownloadPCOptions * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseDownloadPCOptions * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseDownloadPCOptions * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseDownloadPCOptions * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseDownloadPCOptions * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CodePage )( 
            IcwbxDatabaseDownloadPCOptions * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CodePage )( 
            IcwbxDatabaseDownloadPCOptions * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExistingFileOption )( 
            IcwbxDatabaseDownloadPCOptions * This,
            /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExistingFileOption )( 
            IcwbxDatabaseDownloadPCOptions * This,
            /* [in] */ cwbdtExistingOutputFileEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fileDescriptionFile )( 
            IcwbxDatabaseDownloadPCOptions * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fileDescriptionFile )( 
            IcwbxDatabaseDownloadPCOptions * This,
            /* [in] */ BSTR newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ReceiveInfo )( 
            IcwbxDatabaseDownloadPCOptions * This,
            /* [in] */ long newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseDownloadPCOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IcwbxDatabaseDownloadPCOptionsVtbl;

    interface IcwbxDatabaseDownloadPCOptions
    {
        CONST_VTBL struct IcwbxDatabaseDownloadPCOptionsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseDownloadPCOptions_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseDownloadPCOptions_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseDownloadPCOptions_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseDownloadPCOptions_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseDownloadPCOptions_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseDownloadPCOptions_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseDownloadPCOptions_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseDownloadPCOptions_get_CodePage(This,pVal)	\
    (This)->lpVtbl -> get_CodePage(This,pVal)

#define IcwbxDatabaseDownloadPCOptions_put_CodePage(This,newVal)	\
    (This)->lpVtbl -> put_CodePage(This,newVal)

#define IcwbxDatabaseDownloadPCOptions_get_ExistingFileOption(This,pVal)	\
    (This)->lpVtbl -> get_ExistingFileOption(This,pVal)

#define IcwbxDatabaseDownloadPCOptions_put_ExistingFileOption(This,newVal)	\
    (This)->lpVtbl -> put_ExistingFileOption(This,newVal)

#define IcwbxDatabaseDownloadPCOptions_get_fileDescriptionFile(This,pVal)	\
    (This)->lpVtbl -> get_fileDescriptionFile(This,pVal)

#define IcwbxDatabaseDownloadPCOptions_put_fileDescriptionFile(This,newVal)	\
    (This)->lpVtbl -> put_fileDescriptionFile(This,newVal)

#define IcwbxDatabaseDownloadPCOptions_put_ReceiveInfo(This,newVal)	\
    (This)->lpVtbl -> put_ReceiveInfo(This,newVal)

#define IcwbxDatabaseDownloadPCOptions_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadPCOptions_get_CodePage_Proxy( 
    IcwbxDatabaseDownloadPCOptions * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxDatabaseDownloadPCOptions_get_CodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadPCOptions_put_CodePage_Proxy( 
    IcwbxDatabaseDownloadPCOptions * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownloadPCOptions_put_CodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadPCOptions_get_ExistingFileOption_Proxy( 
    IcwbxDatabaseDownloadPCOptions * This,
    /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadPCOptions_get_ExistingFileOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadPCOptions_put_ExistingFileOption_Proxy( 
    IcwbxDatabaseDownloadPCOptions * This,
    /* [in] */ cwbdtExistingOutputFileEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadPCOptions_put_ExistingFileOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadPCOptions_get_fileDescriptionFile_Proxy( 
    IcwbxDatabaseDownloadPCOptions * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseDownloadPCOptions_get_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadPCOptions_put_fileDescriptionFile_Proxy( 
    IcwbxDatabaseDownloadPCOptions * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseDownloadPCOptions_put_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadPCOptions_put_ReceiveInfo_Proxy( 
    IcwbxDatabaseDownloadPCOptions * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownloadPCOptions_put_ReceiveInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadPCOptions_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseDownloadPCOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadPCOptions_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseDownloadPCOptions_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadASCIIOptions_INTERFACE_DEFINED__
#define __IcwbxDatabaseDownloadASCIIOptions_INTERFACE_DEFINED__

/* interface IcwbxDatabaseDownloadASCIIOptions */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][hidden][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseDownloadASCIIOptions;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("35DD1AB2-0CAB-11D3-8392-C4CC6678F234")
    IcwbxDatabaseDownloadASCIIOptions : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AppendEOFIndicator( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AppendEOFIndicator( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CodePage( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CodePage( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExistingFileOption( 
            /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ExistingFileOption( 
            /* [in] */ cwbdtExistingOutputFileEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_fileDescriptionFile( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_fileDescriptionFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IncludeLeadingZeros( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IncludeLeadingZeros( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TruncateSpaces( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TruncateSpaces( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReceiveInfo( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseDownloadASCIIOptionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseDownloadASCIIOptions * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseDownloadASCIIOptions * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseDownloadASCIIOptions * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseDownloadASCIIOptions * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseDownloadASCIIOptions * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseDownloadASCIIOptions * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseDownloadASCIIOptions * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AppendEOFIndicator )( 
            IcwbxDatabaseDownloadASCIIOptions * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AppendEOFIndicator )( 
            IcwbxDatabaseDownloadASCIIOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CodePage )( 
            IcwbxDatabaseDownloadASCIIOptions * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CodePage )( 
            IcwbxDatabaseDownloadASCIIOptions * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExistingFileOption )( 
            IcwbxDatabaseDownloadASCIIOptions * This,
            /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExistingFileOption )( 
            IcwbxDatabaseDownloadASCIIOptions * This,
            /* [in] */ cwbdtExistingOutputFileEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fileDescriptionFile )( 
            IcwbxDatabaseDownloadASCIIOptions * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fileDescriptionFile )( 
            IcwbxDatabaseDownloadASCIIOptions * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IncludeLeadingZeros )( 
            IcwbxDatabaseDownloadASCIIOptions * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IncludeLeadingZeros )( 
            IcwbxDatabaseDownloadASCIIOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TruncateSpaces )( 
            IcwbxDatabaseDownloadASCIIOptions * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TruncateSpaces )( 
            IcwbxDatabaseDownloadASCIIOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ReceiveInfo )( 
            IcwbxDatabaseDownloadASCIIOptions * This,
            /* [in] */ long newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseDownloadASCIIOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IcwbxDatabaseDownloadASCIIOptionsVtbl;

    interface IcwbxDatabaseDownloadASCIIOptions
    {
        CONST_VTBL struct IcwbxDatabaseDownloadASCIIOptionsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseDownloadASCIIOptions_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseDownloadASCIIOptions_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseDownloadASCIIOptions_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseDownloadASCIIOptions_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseDownloadASCIIOptions_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseDownloadASCIIOptions_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseDownloadASCIIOptions_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseDownloadASCIIOptions_get_AppendEOFIndicator(This,pVal)	\
    (This)->lpVtbl -> get_AppendEOFIndicator(This,pVal)

#define IcwbxDatabaseDownloadASCIIOptions_put_AppendEOFIndicator(This,newVal)	\
    (This)->lpVtbl -> put_AppendEOFIndicator(This,newVal)

#define IcwbxDatabaseDownloadASCIIOptions_get_CodePage(This,pVal)	\
    (This)->lpVtbl -> get_CodePage(This,pVal)

#define IcwbxDatabaseDownloadASCIIOptions_put_CodePage(This,newVal)	\
    (This)->lpVtbl -> put_CodePage(This,newVal)

#define IcwbxDatabaseDownloadASCIIOptions_get_ExistingFileOption(This,pVal)	\
    (This)->lpVtbl -> get_ExistingFileOption(This,pVal)

#define IcwbxDatabaseDownloadASCIIOptions_put_ExistingFileOption(This,newVal)	\
    (This)->lpVtbl -> put_ExistingFileOption(This,newVal)

#define IcwbxDatabaseDownloadASCIIOptions_get_fileDescriptionFile(This,pVal)	\
    (This)->lpVtbl -> get_fileDescriptionFile(This,pVal)

#define IcwbxDatabaseDownloadASCIIOptions_put_fileDescriptionFile(This,newVal)	\
    (This)->lpVtbl -> put_fileDescriptionFile(This,newVal)

#define IcwbxDatabaseDownloadASCIIOptions_get_IncludeLeadingZeros(This,pVal)	\
    (This)->lpVtbl -> get_IncludeLeadingZeros(This,pVal)

#define IcwbxDatabaseDownloadASCIIOptions_put_IncludeLeadingZeros(This,newVal)	\
    (This)->lpVtbl -> put_IncludeLeadingZeros(This,newVal)

#define IcwbxDatabaseDownloadASCIIOptions_get_TruncateSpaces(This,pVal)	\
    (This)->lpVtbl -> get_TruncateSpaces(This,pVal)

#define IcwbxDatabaseDownloadASCIIOptions_put_TruncateSpaces(This,newVal)	\
    (This)->lpVtbl -> put_TruncateSpaces(This,newVal)

#define IcwbxDatabaseDownloadASCIIOptions_put_ReceiveInfo(This,newVal)	\
    (This)->lpVtbl -> put_ReceiveInfo(This,newVal)

#define IcwbxDatabaseDownloadASCIIOptions_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions_get_AppendEOFIndicator_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions_get_AppendEOFIndicator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions_put_AppendEOFIndicator_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions_put_AppendEOFIndicator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions_get_CodePage_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions_get_CodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions_put_CodePage_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions_put_CodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions_get_ExistingFileOption_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions * This,
    /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions_get_ExistingFileOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions_put_ExistingFileOption_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions * This,
    /* [in] */ cwbdtExistingOutputFileEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions_put_ExistingFileOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions_get_fileDescriptionFile_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions_get_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions_put_fileDescriptionFile_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions_put_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions_get_IncludeLeadingZeros_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions_get_IncludeLeadingZeros_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions_put_IncludeLeadingZeros_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions_put_IncludeLeadingZeros_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions_get_TruncateSpaces_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions_get_TruncateSpaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions_put_TruncateSpaces_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions_put_TruncateSpaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions_put_ReceiveInfo_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions_put_ReceiveInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseDownloadASCIIOptions_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadTabDelimitedOptions_INTERFACE_DEFINED__
#define __IcwbxDatabaseDownloadTabDelimitedOptions_INTERFACE_DEFINED__

/* interface IcwbxDatabaseDownloadTabDelimitedOptions */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][hidden][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseDownloadTabDelimitedOptions;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("092EA4E1-1E84-11D3-9159-002035AE9B5D")
    IcwbxDatabaseDownloadTabDelimitedOptions : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CodePage( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CodePage( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExistingFileOption( 
            /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ExistingFileOption( 
            /* [in] */ cwbdtExistingOutputFileEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_fileDescriptionFile( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_fileDescriptionFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RemoveLeadingNumericSpaces( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RemoveLeadingNumericSpaces( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RemoveTrailingCharSpaces( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RemoveTrailingCharSpaces( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReceiveInfo( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseDownloadTabDelimitedOptionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseDownloadTabDelimitedOptions * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseDownloadTabDelimitedOptions * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseDownloadTabDelimitedOptions * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseDownloadTabDelimitedOptions * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseDownloadTabDelimitedOptions * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseDownloadTabDelimitedOptions * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseDownloadTabDelimitedOptions * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CodePage )( 
            IcwbxDatabaseDownloadTabDelimitedOptions * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CodePage )( 
            IcwbxDatabaseDownloadTabDelimitedOptions * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExistingFileOption )( 
            IcwbxDatabaseDownloadTabDelimitedOptions * This,
            /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExistingFileOption )( 
            IcwbxDatabaseDownloadTabDelimitedOptions * This,
            /* [in] */ cwbdtExistingOutputFileEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fileDescriptionFile )( 
            IcwbxDatabaseDownloadTabDelimitedOptions * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fileDescriptionFile )( 
            IcwbxDatabaseDownloadTabDelimitedOptions * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RemoveLeadingNumericSpaces )( 
            IcwbxDatabaseDownloadTabDelimitedOptions * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RemoveLeadingNumericSpaces )( 
            IcwbxDatabaseDownloadTabDelimitedOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RemoveTrailingCharSpaces )( 
            IcwbxDatabaseDownloadTabDelimitedOptions * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RemoveTrailingCharSpaces )( 
            IcwbxDatabaseDownloadTabDelimitedOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ReceiveInfo )( 
            IcwbxDatabaseDownloadTabDelimitedOptions * This,
            /* [in] */ long newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseDownloadTabDelimitedOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IcwbxDatabaseDownloadTabDelimitedOptionsVtbl;

    interface IcwbxDatabaseDownloadTabDelimitedOptions
    {
        CONST_VTBL struct IcwbxDatabaseDownloadTabDelimitedOptionsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseDownloadTabDelimitedOptions_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseDownloadTabDelimitedOptions_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseDownloadTabDelimitedOptions_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseDownloadTabDelimitedOptions_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseDownloadTabDelimitedOptions_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseDownloadTabDelimitedOptions_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseDownloadTabDelimitedOptions_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseDownloadTabDelimitedOptions_get_CodePage(This,pVal)	\
    (This)->lpVtbl -> get_CodePage(This,pVal)

#define IcwbxDatabaseDownloadTabDelimitedOptions_put_CodePage(This,newVal)	\
    (This)->lpVtbl -> put_CodePage(This,newVal)

#define IcwbxDatabaseDownloadTabDelimitedOptions_get_ExistingFileOption(This,pVal)	\
    (This)->lpVtbl -> get_ExistingFileOption(This,pVal)

#define IcwbxDatabaseDownloadTabDelimitedOptions_put_ExistingFileOption(This,newVal)	\
    (This)->lpVtbl -> put_ExistingFileOption(This,newVal)

#define IcwbxDatabaseDownloadTabDelimitedOptions_get_fileDescriptionFile(This,pVal)	\
    (This)->lpVtbl -> get_fileDescriptionFile(This,pVal)

#define IcwbxDatabaseDownloadTabDelimitedOptions_put_fileDescriptionFile(This,newVal)	\
    (This)->lpVtbl -> put_fileDescriptionFile(This,newVal)

#define IcwbxDatabaseDownloadTabDelimitedOptions_get_RemoveLeadingNumericSpaces(This,pVal)	\
    (This)->lpVtbl -> get_RemoveLeadingNumericSpaces(This,pVal)

#define IcwbxDatabaseDownloadTabDelimitedOptions_put_RemoveLeadingNumericSpaces(This,newVal)	\
    (This)->lpVtbl -> put_RemoveLeadingNumericSpaces(This,newVal)

#define IcwbxDatabaseDownloadTabDelimitedOptions_get_RemoveTrailingCharSpaces(This,pVal)	\
    (This)->lpVtbl -> get_RemoveTrailingCharSpaces(This,pVal)

#define IcwbxDatabaseDownloadTabDelimitedOptions_put_RemoveTrailingCharSpaces(This,newVal)	\
    (This)->lpVtbl -> put_RemoveTrailingCharSpaces(This,newVal)

#define IcwbxDatabaseDownloadTabDelimitedOptions_put_ReceiveInfo(This,newVal)	\
    (This)->lpVtbl -> put_ReceiveInfo(This,newVal)

#define IcwbxDatabaseDownloadTabDelimitedOptions_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadTabDelimitedOptions_get_CodePage_Proxy( 
    IcwbxDatabaseDownloadTabDelimitedOptions * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxDatabaseDownloadTabDelimitedOptions_get_CodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadTabDelimitedOptions_put_CodePage_Proxy( 
    IcwbxDatabaseDownloadTabDelimitedOptions * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownloadTabDelimitedOptions_put_CodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadTabDelimitedOptions_get_ExistingFileOption_Proxy( 
    IcwbxDatabaseDownloadTabDelimitedOptions * This,
    /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadTabDelimitedOptions_get_ExistingFileOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadTabDelimitedOptions_put_ExistingFileOption_Proxy( 
    IcwbxDatabaseDownloadTabDelimitedOptions * This,
    /* [in] */ cwbdtExistingOutputFileEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadTabDelimitedOptions_put_ExistingFileOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadTabDelimitedOptions_get_fileDescriptionFile_Proxy( 
    IcwbxDatabaseDownloadTabDelimitedOptions * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseDownloadTabDelimitedOptions_get_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadTabDelimitedOptions_put_fileDescriptionFile_Proxy( 
    IcwbxDatabaseDownloadTabDelimitedOptions * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseDownloadTabDelimitedOptions_put_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadTabDelimitedOptions_get_RemoveLeadingNumericSpaces_Proxy( 
    IcwbxDatabaseDownloadTabDelimitedOptions * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadTabDelimitedOptions_get_RemoveLeadingNumericSpaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadTabDelimitedOptions_put_RemoveLeadingNumericSpaces_Proxy( 
    IcwbxDatabaseDownloadTabDelimitedOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadTabDelimitedOptions_put_RemoveLeadingNumericSpaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadTabDelimitedOptions_get_RemoveTrailingCharSpaces_Proxy( 
    IcwbxDatabaseDownloadTabDelimitedOptions * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadTabDelimitedOptions_get_RemoveTrailingCharSpaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadTabDelimitedOptions_put_RemoveTrailingCharSpaces_Proxy( 
    IcwbxDatabaseDownloadTabDelimitedOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadTabDelimitedOptions_put_RemoveTrailingCharSpaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadTabDelimitedOptions_put_ReceiveInfo_Proxy( 
    IcwbxDatabaseDownloadTabDelimitedOptions * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownloadTabDelimitedOptions_put_ReceiveInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadTabDelimitedOptions_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseDownloadTabDelimitedOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadTabDelimitedOptions_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseDownloadTabDelimitedOptions_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadBIFFOptions_INTERFACE_DEFINED__
#define __IcwbxDatabaseDownloadBIFFOptions_INTERFACE_DEFINED__

/* interface IcwbxDatabaseDownloadBIFFOptions */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][hidden][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseDownloadBIFFOptions;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("35DD1AB4-0CAB-11D3-8392-C4CC6678F234")
    IcwbxDatabaseDownloadBIFFOptions : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CreateExtraSheets( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CreateExtraSheets( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExistingFileOption( 
            /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ExistingFileOption( 
            /* [in] */ cwbdtExistingOutputFileEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_fileDescriptionFile( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_fileDescriptionFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HeadingsOnExtraSheets( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HeadingsOnExtraSheets( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HeadingsOnFirstSheet( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HeadingsOnFirstSheet( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReceiveInfo( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseDownloadBIFFOptionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseDownloadBIFFOptions * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseDownloadBIFFOptions * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseDownloadBIFFOptions * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseDownloadBIFFOptions * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseDownloadBIFFOptions * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseDownloadBIFFOptions * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseDownloadBIFFOptions * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CreateExtraSheets )( 
            IcwbxDatabaseDownloadBIFFOptions * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CreateExtraSheets )( 
            IcwbxDatabaseDownloadBIFFOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExistingFileOption )( 
            IcwbxDatabaseDownloadBIFFOptions * This,
            /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExistingFileOption )( 
            IcwbxDatabaseDownloadBIFFOptions * This,
            /* [in] */ cwbdtExistingOutputFileEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fileDescriptionFile )( 
            IcwbxDatabaseDownloadBIFFOptions * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fileDescriptionFile )( 
            IcwbxDatabaseDownloadBIFFOptions * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HeadingsOnExtraSheets )( 
            IcwbxDatabaseDownloadBIFFOptions * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HeadingsOnExtraSheets )( 
            IcwbxDatabaseDownloadBIFFOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HeadingsOnFirstSheet )( 
            IcwbxDatabaseDownloadBIFFOptions * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HeadingsOnFirstSheet )( 
            IcwbxDatabaseDownloadBIFFOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ReceiveInfo )( 
            IcwbxDatabaseDownloadBIFFOptions * This,
            /* [in] */ long newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseDownloadBIFFOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IcwbxDatabaseDownloadBIFFOptionsVtbl;

    interface IcwbxDatabaseDownloadBIFFOptions
    {
        CONST_VTBL struct IcwbxDatabaseDownloadBIFFOptionsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseDownloadBIFFOptions_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseDownloadBIFFOptions_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseDownloadBIFFOptions_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseDownloadBIFFOptions_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseDownloadBIFFOptions_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseDownloadBIFFOptions_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseDownloadBIFFOptions_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseDownloadBIFFOptions_get_CreateExtraSheets(This,pVal)	\
    (This)->lpVtbl -> get_CreateExtraSheets(This,pVal)

#define IcwbxDatabaseDownloadBIFFOptions_put_CreateExtraSheets(This,newVal)	\
    (This)->lpVtbl -> put_CreateExtraSheets(This,newVal)

#define IcwbxDatabaseDownloadBIFFOptions_get_ExistingFileOption(This,pVal)	\
    (This)->lpVtbl -> get_ExistingFileOption(This,pVal)

#define IcwbxDatabaseDownloadBIFFOptions_put_ExistingFileOption(This,newVal)	\
    (This)->lpVtbl -> put_ExistingFileOption(This,newVal)

#define IcwbxDatabaseDownloadBIFFOptions_get_fileDescriptionFile(This,pVal)	\
    (This)->lpVtbl -> get_fileDescriptionFile(This,pVal)

#define IcwbxDatabaseDownloadBIFFOptions_put_fileDescriptionFile(This,newVal)	\
    (This)->lpVtbl -> put_fileDescriptionFile(This,newVal)

#define IcwbxDatabaseDownloadBIFFOptions_get_HeadingsOnExtraSheets(This,pVal)	\
    (This)->lpVtbl -> get_HeadingsOnExtraSheets(This,pVal)

#define IcwbxDatabaseDownloadBIFFOptions_put_HeadingsOnExtraSheets(This,newVal)	\
    (This)->lpVtbl -> put_HeadingsOnExtraSheets(This,newVal)

#define IcwbxDatabaseDownloadBIFFOptions_get_HeadingsOnFirstSheet(This,pVal)	\
    (This)->lpVtbl -> get_HeadingsOnFirstSheet(This,pVal)

#define IcwbxDatabaseDownloadBIFFOptions_put_HeadingsOnFirstSheet(This,newVal)	\
    (This)->lpVtbl -> put_HeadingsOnFirstSheet(This,newVal)

#define IcwbxDatabaseDownloadBIFFOptions_put_ReceiveInfo(This,newVal)	\
    (This)->lpVtbl -> put_ReceiveInfo(This,newVal)

#define IcwbxDatabaseDownloadBIFFOptions_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadBIFFOptions_get_CreateExtraSheets_Proxy( 
    IcwbxDatabaseDownloadBIFFOptions * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadBIFFOptions_get_CreateExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadBIFFOptions_put_CreateExtraSheets_Proxy( 
    IcwbxDatabaseDownloadBIFFOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadBIFFOptions_put_CreateExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadBIFFOptions_get_ExistingFileOption_Proxy( 
    IcwbxDatabaseDownloadBIFFOptions * This,
    /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadBIFFOptions_get_ExistingFileOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadBIFFOptions_put_ExistingFileOption_Proxy( 
    IcwbxDatabaseDownloadBIFFOptions * This,
    /* [in] */ cwbdtExistingOutputFileEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadBIFFOptions_put_ExistingFileOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadBIFFOptions_get_fileDescriptionFile_Proxy( 
    IcwbxDatabaseDownloadBIFFOptions * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseDownloadBIFFOptions_get_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadBIFFOptions_put_fileDescriptionFile_Proxy( 
    IcwbxDatabaseDownloadBIFFOptions * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseDownloadBIFFOptions_put_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadBIFFOptions_get_HeadingsOnExtraSheets_Proxy( 
    IcwbxDatabaseDownloadBIFFOptions * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadBIFFOptions_get_HeadingsOnExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadBIFFOptions_put_HeadingsOnExtraSheets_Proxy( 
    IcwbxDatabaseDownloadBIFFOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadBIFFOptions_put_HeadingsOnExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadBIFFOptions_get_HeadingsOnFirstSheet_Proxy( 
    IcwbxDatabaseDownloadBIFFOptions * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadBIFFOptions_get_HeadingsOnFirstSheet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadBIFFOptions_put_HeadingsOnFirstSheet_Proxy( 
    IcwbxDatabaseDownloadBIFFOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadBIFFOptions_put_HeadingsOnFirstSheet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadBIFFOptions_put_ReceiveInfo_Proxy( 
    IcwbxDatabaseDownloadBIFFOptions * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownloadBIFFOptions_put_ReceiveInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadBIFFOptions_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseDownloadBIFFOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadBIFFOptions_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseDownloadBIFFOptions_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadWK4Options_INTERFACE_DEFINED__
#define __IcwbxDatabaseDownloadWK4Options_INTERFACE_DEFINED__

/* interface IcwbxDatabaseDownloadWK4Options */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][hidden][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseDownloadWK4Options;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("35DD1AB6-0CAB-11D3-8392-C4CC6678F234")
    IcwbxDatabaseDownloadWK4Options : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CreateExtraSheets( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CreateExtraSheets( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExistingFileOption( 
            /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ExistingFileOption( 
            /* [in] */ cwbdtExistingOutputFileEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_fileDescriptionFile( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_fileDescriptionFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HeadingsOnExtraSheets( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HeadingsOnExtraSheets( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HeadingsOnFirstSheet( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HeadingsOnFirstSheet( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReceiveInfo( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseDownloadWK4OptionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseDownloadWK4Options * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseDownloadWK4Options * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseDownloadWK4Options * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseDownloadWK4Options * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseDownloadWK4Options * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseDownloadWK4Options * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseDownloadWK4Options * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CreateExtraSheets )( 
            IcwbxDatabaseDownloadWK4Options * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CreateExtraSheets )( 
            IcwbxDatabaseDownloadWK4Options * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExistingFileOption )( 
            IcwbxDatabaseDownloadWK4Options * This,
            /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExistingFileOption )( 
            IcwbxDatabaseDownloadWK4Options * This,
            /* [in] */ cwbdtExistingOutputFileEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fileDescriptionFile )( 
            IcwbxDatabaseDownloadWK4Options * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fileDescriptionFile )( 
            IcwbxDatabaseDownloadWK4Options * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HeadingsOnExtraSheets )( 
            IcwbxDatabaseDownloadWK4Options * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HeadingsOnExtraSheets )( 
            IcwbxDatabaseDownloadWK4Options * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HeadingsOnFirstSheet )( 
            IcwbxDatabaseDownloadWK4Options * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HeadingsOnFirstSheet )( 
            IcwbxDatabaseDownloadWK4Options * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ReceiveInfo )( 
            IcwbxDatabaseDownloadWK4Options * This,
            /* [in] */ long newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseDownloadWK4Options * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IcwbxDatabaseDownloadWK4OptionsVtbl;

    interface IcwbxDatabaseDownloadWK4Options
    {
        CONST_VTBL struct IcwbxDatabaseDownloadWK4OptionsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseDownloadWK4Options_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseDownloadWK4Options_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseDownloadWK4Options_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseDownloadWK4Options_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseDownloadWK4Options_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseDownloadWK4Options_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseDownloadWK4Options_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseDownloadWK4Options_get_CreateExtraSheets(This,pVal)	\
    (This)->lpVtbl -> get_CreateExtraSheets(This,pVal)

#define IcwbxDatabaseDownloadWK4Options_put_CreateExtraSheets(This,newVal)	\
    (This)->lpVtbl -> put_CreateExtraSheets(This,newVal)

#define IcwbxDatabaseDownloadWK4Options_get_ExistingFileOption(This,pVal)	\
    (This)->lpVtbl -> get_ExistingFileOption(This,pVal)

#define IcwbxDatabaseDownloadWK4Options_put_ExistingFileOption(This,newVal)	\
    (This)->lpVtbl -> put_ExistingFileOption(This,newVal)

#define IcwbxDatabaseDownloadWK4Options_get_fileDescriptionFile(This,pVal)	\
    (This)->lpVtbl -> get_fileDescriptionFile(This,pVal)

#define IcwbxDatabaseDownloadWK4Options_put_fileDescriptionFile(This,newVal)	\
    (This)->lpVtbl -> put_fileDescriptionFile(This,newVal)

#define IcwbxDatabaseDownloadWK4Options_get_HeadingsOnExtraSheets(This,pVal)	\
    (This)->lpVtbl -> get_HeadingsOnExtraSheets(This,pVal)

#define IcwbxDatabaseDownloadWK4Options_put_HeadingsOnExtraSheets(This,newVal)	\
    (This)->lpVtbl -> put_HeadingsOnExtraSheets(This,newVal)

#define IcwbxDatabaseDownloadWK4Options_get_HeadingsOnFirstSheet(This,pVal)	\
    (This)->lpVtbl -> get_HeadingsOnFirstSheet(This,pVal)

#define IcwbxDatabaseDownloadWK4Options_put_HeadingsOnFirstSheet(This,newVal)	\
    (This)->lpVtbl -> put_HeadingsOnFirstSheet(This,newVal)

#define IcwbxDatabaseDownloadWK4Options_put_ReceiveInfo(This,newVal)	\
    (This)->lpVtbl -> put_ReceiveInfo(This,newVal)

#define IcwbxDatabaseDownloadWK4Options_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadWK4Options_get_CreateExtraSheets_Proxy( 
    IcwbxDatabaseDownloadWK4Options * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadWK4Options_get_CreateExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadWK4Options_put_CreateExtraSheets_Proxy( 
    IcwbxDatabaseDownloadWK4Options * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadWK4Options_put_CreateExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadWK4Options_get_ExistingFileOption_Proxy( 
    IcwbxDatabaseDownloadWK4Options * This,
    /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadWK4Options_get_ExistingFileOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadWK4Options_put_ExistingFileOption_Proxy( 
    IcwbxDatabaseDownloadWK4Options * This,
    /* [in] */ cwbdtExistingOutputFileEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadWK4Options_put_ExistingFileOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadWK4Options_get_fileDescriptionFile_Proxy( 
    IcwbxDatabaseDownloadWK4Options * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseDownloadWK4Options_get_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadWK4Options_put_fileDescriptionFile_Proxy( 
    IcwbxDatabaseDownloadWK4Options * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseDownloadWK4Options_put_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadWK4Options_get_HeadingsOnExtraSheets_Proxy( 
    IcwbxDatabaseDownloadWK4Options * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadWK4Options_get_HeadingsOnExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadWK4Options_put_HeadingsOnExtraSheets_Proxy( 
    IcwbxDatabaseDownloadWK4Options * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadWK4Options_put_HeadingsOnExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadWK4Options_get_HeadingsOnFirstSheet_Proxy( 
    IcwbxDatabaseDownloadWK4Options * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadWK4Options_get_HeadingsOnFirstSheet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadWK4Options_put_HeadingsOnFirstSheet_Proxy( 
    IcwbxDatabaseDownloadWK4Options * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadWK4Options_put_HeadingsOnFirstSheet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadWK4Options_put_ReceiveInfo_Proxy( 
    IcwbxDatabaseDownloadWK4Options * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownloadWK4Options_put_ReceiveInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadWK4Options_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseDownloadWK4Options * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadWK4Options_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseDownloadWK4Options_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseDownload123Options_INTERFACE_DEFINED__
#define __IcwbxDatabaseDownload123Options_INTERFACE_DEFINED__

/* interface IcwbxDatabaseDownload123Options */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][hidden][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseDownload123Options;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("092EA4E3-1E84-11D3-9159-002035AE9B5D")
    IcwbxDatabaseDownload123Options : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CreateExtraSheets( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CreateExtraSheets( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExistingFileOption( 
            /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ExistingFileOption( 
            /* [in] */ cwbdtExistingOutputFileEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_fileDescriptionFile( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_fileDescriptionFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HeadingsOnExtraSheets( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HeadingsOnExtraSheets( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HeadingsOnFirstSheet( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HeadingsOnFirstSheet( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReceiveInfo( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseDownload123OptionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseDownload123Options * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseDownload123Options * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseDownload123Options * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseDownload123Options * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseDownload123Options * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseDownload123Options * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseDownload123Options * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CreateExtraSheets )( 
            IcwbxDatabaseDownload123Options * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CreateExtraSheets )( 
            IcwbxDatabaseDownload123Options * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExistingFileOption )( 
            IcwbxDatabaseDownload123Options * This,
            /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExistingFileOption )( 
            IcwbxDatabaseDownload123Options * This,
            /* [in] */ cwbdtExistingOutputFileEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fileDescriptionFile )( 
            IcwbxDatabaseDownload123Options * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fileDescriptionFile )( 
            IcwbxDatabaseDownload123Options * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HeadingsOnExtraSheets )( 
            IcwbxDatabaseDownload123Options * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HeadingsOnExtraSheets )( 
            IcwbxDatabaseDownload123Options * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HeadingsOnFirstSheet )( 
            IcwbxDatabaseDownload123Options * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HeadingsOnFirstSheet )( 
            IcwbxDatabaseDownload123Options * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ReceiveInfo )( 
            IcwbxDatabaseDownload123Options * This,
            /* [in] */ long newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseDownload123Options * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IcwbxDatabaseDownload123OptionsVtbl;

    interface IcwbxDatabaseDownload123Options
    {
        CONST_VTBL struct IcwbxDatabaseDownload123OptionsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseDownload123Options_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseDownload123Options_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseDownload123Options_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseDownload123Options_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseDownload123Options_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseDownload123Options_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseDownload123Options_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseDownload123Options_get_CreateExtraSheets(This,pVal)	\
    (This)->lpVtbl -> get_CreateExtraSheets(This,pVal)

#define IcwbxDatabaseDownload123Options_put_CreateExtraSheets(This,newVal)	\
    (This)->lpVtbl -> put_CreateExtraSheets(This,newVal)

#define IcwbxDatabaseDownload123Options_get_ExistingFileOption(This,pVal)	\
    (This)->lpVtbl -> get_ExistingFileOption(This,pVal)

#define IcwbxDatabaseDownload123Options_put_ExistingFileOption(This,newVal)	\
    (This)->lpVtbl -> put_ExistingFileOption(This,newVal)

#define IcwbxDatabaseDownload123Options_get_fileDescriptionFile(This,pVal)	\
    (This)->lpVtbl -> get_fileDescriptionFile(This,pVal)

#define IcwbxDatabaseDownload123Options_put_fileDescriptionFile(This,newVal)	\
    (This)->lpVtbl -> put_fileDescriptionFile(This,newVal)

#define IcwbxDatabaseDownload123Options_get_HeadingsOnExtraSheets(This,pVal)	\
    (This)->lpVtbl -> get_HeadingsOnExtraSheets(This,pVal)

#define IcwbxDatabaseDownload123Options_put_HeadingsOnExtraSheets(This,newVal)	\
    (This)->lpVtbl -> put_HeadingsOnExtraSheets(This,newVal)

#define IcwbxDatabaseDownload123Options_get_HeadingsOnFirstSheet(This,pVal)	\
    (This)->lpVtbl -> get_HeadingsOnFirstSheet(This,pVal)

#define IcwbxDatabaseDownload123Options_put_HeadingsOnFirstSheet(This,newVal)	\
    (This)->lpVtbl -> put_HeadingsOnFirstSheet(This,newVal)

#define IcwbxDatabaseDownload123Options_put_ReceiveInfo(This,newVal)	\
    (This)->lpVtbl -> put_ReceiveInfo(This,newVal)

#define IcwbxDatabaseDownload123Options_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownload123Options_get_CreateExtraSheets_Proxy( 
    IcwbxDatabaseDownload123Options * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownload123Options_get_CreateExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownload123Options_put_CreateExtraSheets_Proxy( 
    IcwbxDatabaseDownload123Options * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownload123Options_put_CreateExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownload123Options_get_ExistingFileOption_Proxy( 
    IcwbxDatabaseDownload123Options * This,
    /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownload123Options_get_ExistingFileOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownload123Options_put_ExistingFileOption_Proxy( 
    IcwbxDatabaseDownload123Options * This,
    /* [in] */ cwbdtExistingOutputFileEnum newVal);


void __RPC_STUB IcwbxDatabaseDownload123Options_put_ExistingFileOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownload123Options_get_fileDescriptionFile_Proxy( 
    IcwbxDatabaseDownload123Options * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseDownload123Options_get_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownload123Options_put_fileDescriptionFile_Proxy( 
    IcwbxDatabaseDownload123Options * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseDownload123Options_put_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownload123Options_get_HeadingsOnExtraSheets_Proxy( 
    IcwbxDatabaseDownload123Options * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownload123Options_get_HeadingsOnExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownload123Options_put_HeadingsOnExtraSheets_Proxy( 
    IcwbxDatabaseDownload123Options * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownload123Options_put_HeadingsOnExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownload123Options_get_HeadingsOnFirstSheet_Proxy( 
    IcwbxDatabaseDownload123Options * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownload123Options_get_HeadingsOnFirstSheet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownload123Options_put_HeadingsOnFirstSheet_Proxy( 
    IcwbxDatabaseDownload123Options * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownload123Options_put_HeadingsOnFirstSheet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownload123Options_put_ReceiveInfo_Proxy( 
    IcwbxDatabaseDownload123Options * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownload123Options_put_ReceiveInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownload123Options_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseDownload123Options * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownload123Options_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseDownload123Options_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadHTMLOptions_INTERFACE_DEFINED__
#define __IcwbxDatabaseDownloadHTMLOptions_INTERFACE_DEFINED__

/* interface IcwbxDatabaseDownloadHTMLOptions */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseDownloadHTMLOptions;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("35DD1AB8-0CAB-11D3-8392-C4CC6678F234")
    IcwbxDatabaseDownloadHTMLOptions : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BorderWidth( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BorderWidth( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Caption( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Caption( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CaptionAlignment( 
            /* [retval][out] */ cwbdtCaptionAlignmentEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CaptionAlignment( 
            /* [in] */ cwbdtCaptionAlignmentEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CaptionIncludeTableNumber( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CaptionIncludeTableNumber( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CaptionStyle( 
            /* [retval][out] */ cwbdtTextStyleEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CaptionStyle( 
            /* [in] */ cwbdtTextStyleEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CaptionTextSize( 
            /* [retval][out] */ cwbdtTextSizeEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CaptionTextSize( 
            /* [in] */ cwbdtTextSizeEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CellNumericAlign( 
            /* [retval][out] */ cwbdtCellDataAlignEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CellNumericAlign( 
            /* [in] */ cwbdtCellDataAlignEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CellPadding( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CellPadding( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CellSpacing( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CellSpacing( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CellTextAlign( 
            /* [retval][out] */ cwbdtCellDataAlignEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CellTextAlign( 
            /* [in] */ cwbdtCellDataAlignEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CellTextSize( 
            /* [retval][out] */ cwbdtTextSizeEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CellTextSize( 
            /* [in] */ cwbdtTextSizeEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CellWrapText( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CellWrapText( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DateTimeLocation( 
            /* [retval][out] */ cwbdtDateTimeLocationEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DateTimeLocation( 
            /* [in] */ cwbdtDateTimeLocationEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExtraRowsAction( 
            /* [retval][out] */ cwbdtExtraRowsActionEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ExtraRowsAction( 
            /* [in] */ cwbdtExtraRowsActionEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FewerRowsAction( 
            /* [retval][out] */ cwbdtFewerRowsActionEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FewerRowsAction( 
            /* [in] */ cwbdtFewerRowsActionEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HeadingsHorizAlign( 
            /* [retval][out] */ cwbdtHorizontalAlignEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HeadingsHorizAlign( 
            /* [in] */ cwbdtHorizontalAlignEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HeadingsStyle( 
            /* [retval][out] */ cwbdtTextStyleEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HeadingsStyle( 
            /* [in] */ cwbdtTextStyleEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HeadingsVertAlign( 
            /* [retval][out] */ cwbdtVerticalAlignEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HeadingsVertAlign( 
            /* [in] */ cwbdtVerticalAlignEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IncludeHeadings( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IncludeHeadings( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MaximumDocumentSize( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MaximumDocumentSize( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NumberOfColumns( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NumberOfColumns( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NumberOfRows( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NumberOfRows( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OverwriteIfFileExists( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OverwriteIfFileExists( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RowHorizAlign( 
            /* [retval][out] */ cwbdtHorizontalAlignEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RowHorizAlign( 
            /* [in] */ cwbdtHorizontalAlignEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RowStyle( 
            /* [retval][out] */ cwbdtTextStyleEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RowStyle( 
            /* [in] */ cwbdtTextStyleEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RowVertAlign( 
            /* [retval][out] */ cwbdtVerticalAlignEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RowVertAlign( 
            /* [in] */ cwbdtVerticalAlignEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TableAlignment( 
            /* [retval][out] */ cwbdtTableAlignmentEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TableAlignment( 
            /* [in] */ cwbdtTableAlignmentEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TableWidth( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TableWidth( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TableWidthUnits( 
            /* [retval][out] */ cwbdtSizeUnitsEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TableWidthUnits( 
            /* [in] */ cwbdtSizeUnitsEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Title( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Title( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetConversionType( 
            /* [out] */ VARIANT *conversionType,
            /* [out] */ VARIANT *characterSet) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTemplate( 
            /* [out] */ VARIANT *templateFile,
            /* [out] */ VARIANT *templateTag) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetConversionType( 
            /* [in] */ cwbdtHTMLConversionTypeEnum conversionType,
            /* [defaultvalue][optional][in] */ BSTR characterSet = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetTemplate( 
            /* [in] */ BSTR templateFile,
            /* [in] */ BSTR templateTag) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReceiveInfo( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseDownloadHTMLOptionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseDownloadHTMLOptions * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseDownloadHTMLOptions * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BorderWidth )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BorderWidth )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Caption )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Caption )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CaptionAlignment )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ cwbdtCaptionAlignmentEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CaptionAlignment )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ cwbdtCaptionAlignmentEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CaptionIncludeTableNumber )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CaptionIncludeTableNumber )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CaptionStyle )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ cwbdtTextStyleEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CaptionStyle )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ cwbdtTextStyleEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CaptionTextSize )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ cwbdtTextSizeEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CaptionTextSize )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ cwbdtTextSizeEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CellNumericAlign )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ cwbdtCellDataAlignEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CellNumericAlign )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ cwbdtCellDataAlignEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CellPadding )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CellPadding )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CellSpacing )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CellSpacing )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CellTextAlign )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ cwbdtCellDataAlignEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CellTextAlign )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ cwbdtCellDataAlignEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CellTextSize )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ cwbdtTextSizeEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CellTextSize )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ cwbdtTextSizeEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CellWrapText )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CellWrapText )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DateTimeLocation )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ cwbdtDateTimeLocationEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DateTimeLocation )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ cwbdtDateTimeLocationEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExtraRowsAction )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ cwbdtExtraRowsActionEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExtraRowsAction )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ cwbdtExtraRowsActionEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FewerRowsAction )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ cwbdtFewerRowsActionEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FewerRowsAction )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ cwbdtFewerRowsActionEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HeadingsHorizAlign )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ cwbdtHorizontalAlignEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HeadingsHorizAlign )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ cwbdtHorizontalAlignEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HeadingsStyle )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ cwbdtTextStyleEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HeadingsStyle )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ cwbdtTextStyleEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HeadingsVertAlign )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ cwbdtVerticalAlignEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HeadingsVertAlign )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ cwbdtVerticalAlignEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IncludeHeadings )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IncludeHeadings )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaximumDocumentSize )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaximumDocumentSize )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NumberOfColumns )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_NumberOfColumns )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NumberOfRows )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_NumberOfRows )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OverwriteIfFileExists )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OverwriteIfFileExists )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RowHorizAlign )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ cwbdtHorizontalAlignEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RowHorizAlign )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ cwbdtHorizontalAlignEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RowStyle )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ cwbdtTextStyleEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RowStyle )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ cwbdtTextStyleEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RowVertAlign )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ cwbdtVerticalAlignEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RowVertAlign )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ cwbdtVerticalAlignEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TableAlignment )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ cwbdtTableAlignmentEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TableAlignment )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ cwbdtTableAlignmentEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TableWidth )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TableWidth )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TableWidthUnits )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ cwbdtSizeUnitsEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TableWidthUnits )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ cwbdtSizeUnitsEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Title )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Title )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetConversionType )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [out] */ VARIANT *conversionType,
            /* [out] */ VARIANT *characterSet);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetTemplate )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [out] */ VARIANT *templateFile,
            /* [out] */ VARIANT *templateTag);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetConversionType )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ cwbdtHTMLConversionTypeEnum conversionType,
            /* [defaultvalue][optional][in] */ BSTR characterSet);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetTemplate )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ BSTR templateFile,
            /* [in] */ BSTR templateTag);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ReceiveInfo )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ long newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseDownloadHTMLOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IcwbxDatabaseDownloadHTMLOptionsVtbl;

    interface IcwbxDatabaseDownloadHTMLOptions
    {
        CONST_VTBL struct IcwbxDatabaseDownloadHTMLOptionsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseDownloadHTMLOptions_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseDownloadHTMLOptions_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseDownloadHTMLOptions_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseDownloadHTMLOptions_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseDownloadHTMLOptions_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseDownloadHTMLOptions_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseDownloadHTMLOptions_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseDownloadHTMLOptions_get_BorderWidth(This,pVal)	\
    (This)->lpVtbl -> get_BorderWidth(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_BorderWidth(This,newVal)	\
    (This)->lpVtbl -> put_BorderWidth(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_Caption(This,pVal)	\
    (This)->lpVtbl -> get_Caption(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_Caption(This,newVal)	\
    (This)->lpVtbl -> put_Caption(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_CaptionAlignment(This,pVal)	\
    (This)->lpVtbl -> get_CaptionAlignment(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_CaptionAlignment(This,newVal)	\
    (This)->lpVtbl -> put_CaptionAlignment(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_CaptionIncludeTableNumber(This,pVal)	\
    (This)->lpVtbl -> get_CaptionIncludeTableNumber(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_CaptionIncludeTableNumber(This,newVal)	\
    (This)->lpVtbl -> put_CaptionIncludeTableNumber(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_CaptionStyle(This,pVal)	\
    (This)->lpVtbl -> get_CaptionStyle(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_CaptionStyle(This,newVal)	\
    (This)->lpVtbl -> put_CaptionStyle(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_CaptionTextSize(This,pVal)	\
    (This)->lpVtbl -> get_CaptionTextSize(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_CaptionTextSize(This,newVal)	\
    (This)->lpVtbl -> put_CaptionTextSize(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_CellNumericAlign(This,pVal)	\
    (This)->lpVtbl -> get_CellNumericAlign(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_CellNumericAlign(This,newVal)	\
    (This)->lpVtbl -> put_CellNumericAlign(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_CellPadding(This,pVal)	\
    (This)->lpVtbl -> get_CellPadding(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_CellPadding(This,newVal)	\
    (This)->lpVtbl -> put_CellPadding(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_CellSpacing(This,pVal)	\
    (This)->lpVtbl -> get_CellSpacing(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_CellSpacing(This,newVal)	\
    (This)->lpVtbl -> put_CellSpacing(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_CellTextAlign(This,pVal)	\
    (This)->lpVtbl -> get_CellTextAlign(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_CellTextAlign(This,newVal)	\
    (This)->lpVtbl -> put_CellTextAlign(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_CellTextSize(This,pVal)	\
    (This)->lpVtbl -> get_CellTextSize(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_CellTextSize(This,newVal)	\
    (This)->lpVtbl -> put_CellTextSize(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_CellWrapText(This,pVal)	\
    (This)->lpVtbl -> get_CellWrapText(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_CellWrapText(This,newVal)	\
    (This)->lpVtbl -> put_CellWrapText(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_DateTimeLocation(This,pVal)	\
    (This)->lpVtbl -> get_DateTimeLocation(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_DateTimeLocation(This,newVal)	\
    (This)->lpVtbl -> put_DateTimeLocation(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_ExtraRowsAction(This,pVal)	\
    (This)->lpVtbl -> get_ExtraRowsAction(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_ExtraRowsAction(This,newVal)	\
    (This)->lpVtbl -> put_ExtraRowsAction(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_FewerRowsAction(This,pVal)	\
    (This)->lpVtbl -> get_FewerRowsAction(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_FewerRowsAction(This,newVal)	\
    (This)->lpVtbl -> put_FewerRowsAction(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_HeadingsHorizAlign(This,pVal)	\
    (This)->lpVtbl -> get_HeadingsHorizAlign(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_HeadingsHorizAlign(This,newVal)	\
    (This)->lpVtbl -> put_HeadingsHorizAlign(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_HeadingsStyle(This,pVal)	\
    (This)->lpVtbl -> get_HeadingsStyle(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_HeadingsStyle(This,newVal)	\
    (This)->lpVtbl -> put_HeadingsStyle(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_HeadingsVertAlign(This,pVal)	\
    (This)->lpVtbl -> get_HeadingsVertAlign(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_HeadingsVertAlign(This,newVal)	\
    (This)->lpVtbl -> put_HeadingsVertAlign(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_IncludeHeadings(This,pVal)	\
    (This)->lpVtbl -> get_IncludeHeadings(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_IncludeHeadings(This,newVal)	\
    (This)->lpVtbl -> put_IncludeHeadings(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_MaximumDocumentSize(This,pVal)	\
    (This)->lpVtbl -> get_MaximumDocumentSize(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_MaximumDocumentSize(This,newVal)	\
    (This)->lpVtbl -> put_MaximumDocumentSize(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_NumberOfColumns(This,pVal)	\
    (This)->lpVtbl -> get_NumberOfColumns(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_NumberOfColumns(This,newVal)	\
    (This)->lpVtbl -> put_NumberOfColumns(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_NumberOfRows(This,pVal)	\
    (This)->lpVtbl -> get_NumberOfRows(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_NumberOfRows(This,newVal)	\
    (This)->lpVtbl -> put_NumberOfRows(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_OverwriteIfFileExists(This,pVal)	\
    (This)->lpVtbl -> get_OverwriteIfFileExists(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_OverwriteIfFileExists(This,newVal)	\
    (This)->lpVtbl -> put_OverwriteIfFileExists(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_RowHorizAlign(This,pVal)	\
    (This)->lpVtbl -> get_RowHorizAlign(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_RowHorizAlign(This,newVal)	\
    (This)->lpVtbl -> put_RowHorizAlign(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_RowStyle(This,pVal)	\
    (This)->lpVtbl -> get_RowStyle(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_RowStyle(This,newVal)	\
    (This)->lpVtbl -> put_RowStyle(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_RowVertAlign(This,pVal)	\
    (This)->lpVtbl -> get_RowVertAlign(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_RowVertAlign(This,newVal)	\
    (This)->lpVtbl -> put_RowVertAlign(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_TableAlignment(This,pVal)	\
    (This)->lpVtbl -> get_TableAlignment(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_TableAlignment(This,newVal)	\
    (This)->lpVtbl -> put_TableAlignment(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_TableWidth(This,pVal)	\
    (This)->lpVtbl -> get_TableWidth(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_TableWidth(This,newVal)	\
    (This)->lpVtbl -> put_TableWidth(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_TableWidthUnits(This,pVal)	\
    (This)->lpVtbl -> get_TableWidthUnits(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_TableWidthUnits(This,newVal)	\
    (This)->lpVtbl -> put_TableWidthUnits(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_get_Title(This,pVal)	\
    (This)->lpVtbl -> get_Title(This,pVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_Title(This,newVal)	\
    (This)->lpVtbl -> put_Title(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_GetConversionType(This,conversionType,characterSet)	\
    (This)->lpVtbl -> GetConversionType(This,conversionType,characterSet)

#define IcwbxDatabaseDownloadHTMLOptions_GetTemplate(This,templateFile,templateTag)	\
    (This)->lpVtbl -> GetTemplate(This,templateFile,templateTag)

#define IcwbxDatabaseDownloadHTMLOptions_SetConversionType(This,conversionType,characterSet)	\
    (This)->lpVtbl -> SetConversionType(This,conversionType,characterSet)

#define IcwbxDatabaseDownloadHTMLOptions_SetTemplate(This,templateFile,templateTag)	\
    (This)->lpVtbl -> SetTemplate(This,templateFile,templateTag)

#define IcwbxDatabaseDownloadHTMLOptions_put_ReceiveInfo(This,newVal)	\
    (This)->lpVtbl -> put_ReceiveInfo(This,newVal)

#define IcwbxDatabaseDownloadHTMLOptions_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_BorderWidth_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_BorderWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_BorderWidth_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_BorderWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_Caption_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_Caption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_Caption_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_Caption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_CaptionAlignment_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ cwbdtCaptionAlignmentEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_CaptionAlignment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_CaptionAlignment_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ cwbdtCaptionAlignmentEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_CaptionAlignment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_CaptionIncludeTableNumber_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_CaptionIncludeTableNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_CaptionIncludeTableNumber_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_CaptionIncludeTableNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_CaptionStyle_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ cwbdtTextStyleEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_CaptionStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_CaptionStyle_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ cwbdtTextStyleEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_CaptionStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_CaptionTextSize_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ cwbdtTextSizeEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_CaptionTextSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_CaptionTextSize_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ cwbdtTextSizeEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_CaptionTextSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_CellNumericAlign_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ cwbdtCellDataAlignEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_CellNumericAlign_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_CellNumericAlign_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ cwbdtCellDataAlignEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_CellNumericAlign_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_CellPadding_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_CellPadding_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_CellPadding_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_CellPadding_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_CellSpacing_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_CellSpacing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_CellSpacing_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_CellSpacing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_CellTextAlign_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ cwbdtCellDataAlignEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_CellTextAlign_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_CellTextAlign_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ cwbdtCellDataAlignEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_CellTextAlign_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_CellTextSize_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ cwbdtTextSizeEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_CellTextSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_CellTextSize_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ cwbdtTextSizeEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_CellTextSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_CellWrapText_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_CellWrapText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_CellWrapText_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_CellWrapText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_DateTimeLocation_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ cwbdtDateTimeLocationEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_DateTimeLocation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_DateTimeLocation_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ cwbdtDateTimeLocationEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_DateTimeLocation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_ExtraRowsAction_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ cwbdtExtraRowsActionEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_ExtraRowsAction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_ExtraRowsAction_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ cwbdtExtraRowsActionEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_ExtraRowsAction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_FewerRowsAction_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ cwbdtFewerRowsActionEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_FewerRowsAction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_FewerRowsAction_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ cwbdtFewerRowsActionEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_FewerRowsAction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_HeadingsHorizAlign_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ cwbdtHorizontalAlignEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_HeadingsHorizAlign_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_HeadingsHorizAlign_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ cwbdtHorizontalAlignEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_HeadingsHorizAlign_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_HeadingsStyle_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ cwbdtTextStyleEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_HeadingsStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_HeadingsStyle_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ cwbdtTextStyleEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_HeadingsStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_HeadingsVertAlign_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ cwbdtVerticalAlignEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_HeadingsVertAlign_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_HeadingsVertAlign_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ cwbdtVerticalAlignEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_HeadingsVertAlign_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_IncludeHeadings_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_IncludeHeadings_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_IncludeHeadings_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_IncludeHeadings_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_MaximumDocumentSize_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_MaximumDocumentSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_MaximumDocumentSize_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_MaximumDocumentSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_NumberOfColumns_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_NumberOfColumns_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_NumberOfColumns_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_NumberOfColumns_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_NumberOfRows_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_NumberOfRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_NumberOfRows_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_NumberOfRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_OverwriteIfFileExists_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_OverwriteIfFileExists_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_OverwriteIfFileExists_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_OverwriteIfFileExists_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_RowHorizAlign_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ cwbdtHorizontalAlignEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_RowHorizAlign_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_RowHorizAlign_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ cwbdtHorizontalAlignEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_RowHorizAlign_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_RowStyle_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ cwbdtTextStyleEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_RowStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_RowStyle_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ cwbdtTextStyleEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_RowStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_RowVertAlign_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ cwbdtVerticalAlignEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_RowVertAlign_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_RowVertAlign_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ cwbdtVerticalAlignEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_RowVertAlign_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_TableAlignment_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ cwbdtTableAlignmentEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_TableAlignment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_TableAlignment_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ cwbdtTableAlignmentEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_TableAlignment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_TableWidth_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_TableWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_TableWidth_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_TableWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_TableWidthUnits_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ cwbdtSizeUnitsEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_TableWidthUnits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_TableWidthUnits_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ cwbdtSizeUnitsEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_TableWidthUnits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_get_Title_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_get_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_Title_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_GetConversionType_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [out] */ VARIANT *conversionType,
    /* [out] */ VARIANT *characterSet);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_GetConversionType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_GetTemplate_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [out] */ VARIANT *templateFile,
    /* [out] */ VARIANT *templateTag);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_GetTemplate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_SetConversionType_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ cwbdtHTMLConversionTypeEnum conversionType,
    /* [defaultvalue][optional][in] */ BSTR characterSet);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_SetConversionType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_SetTemplate_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ BSTR templateFile,
    /* [in] */ BSTR templateTag);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_SetTemplate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_ReceiveInfo_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_ReceiveInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadHTMLOptions_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseDownloadHTMLOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadHTMLOptions_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseDownloadHTMLOptions_INTERFACE_DEFINED__ */


#ifndef __IcwbxSystem_INTERFACE_DEFINED__
#define __IcwbxSystem_INTERFACE_DEFINED__

/* interface IcwbxSystem */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxSystem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("86F9DB11-15D5-11D2-849C-0004AC94E175")
    IcwbxSystem : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UserID( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UserID( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Password( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PersistenceMode( 
            /* [retval][out] */ cwbcoPersistenceModeEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PersistenceMode( 
            /* [in] */ cwbcoPersistenceModeEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ValidateMode( 
            /* [retval][out] */ cwbcoValidateModeEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ValidateMode( 
            /* [in] */ cwbcoValidateModeEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultUserMode( 
            /* [retval][out] */ cwbcoDefaultUserModeEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DefaultUserMode( 
            /* [in] */ cwbcoDefaultUserModeEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PromptMode( 
            /* [retval][out] */ cwbcoPromptModeEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PromptMode( 
            /* [in] */ cwbcoPromptModeEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IPAddressLookupMode( 
            /* [retval][out] */ cwbcoIPAddrLookupModeEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IPAddressLookupMode( 
            /* [in] */ cwbcoIPAddrLookupModeEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PortLookupMode( 
            /* [retval][out] */ cwbcoPortLookupModeEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PortLookupMode( 
            /* [in] */ cwbcoPortLookupModeEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WindowHandle( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_WindowHandle( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UseSecureSockets( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UseSecureSockets( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SignonDate( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PrevSignonDate( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PasswordExpireDate( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FailedSignons( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SystemName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CanModifyDefaultUserMode( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CanModifyIPAddressLookupMode( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CanModifyPortLookupMode( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CanModifyPersistenceMode( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CanModifyUseSecureSockets( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HostCodePage( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Errors( 
            /* [retval][out] */ IcwbxErrors **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Define( 
            /* [in] */ BSTR systemName) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE DefineLike( 
            /* [in] */ BSTR systemName,
            /* [in] */ IcwbxSystem *system) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Connect( 
            /* [in] */ cwbcoServiceEnum service) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Verify( 
            /* [in] */ cwbcoServiceEnum service,
            /* [retval][out] */ VARIANT_BOOL *canConnect) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Disconnect( 
            /* [in] */ cwbcoServiceEnum service) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IsConnected( 
            /* [in] */ cwbcoServiceEnum service,
            /* [retval][out] */ long *numberOfConnections) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Signon( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE VerifyUserIDPassword( 
            /* [in] */ BSTR userID,
            /* [in] */ BSTR password) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ChangePassword( 
            /* [in] */ BSTR userID,
            /* [in] */ BSTR oldPassword,
            /* [in] */ BSTR newPassword) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HostVersion( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get_Handle( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IPAddress( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IPAddress( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CanModifyIPAddress( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HostRelease( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HasSignedOn( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConnectTimeout( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ConnectTimeout( 
            /* [in] */ long newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxSystemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxSystem * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxSystem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxSystem * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxSystem * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxSystem * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxSystem * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxSystem * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UserID )( 
            IcwbxSystem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UserID )( 
            IcwbxSystem * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Password )( 
            IcwbxSystem * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PersistenceMode )( 
            IcwbxSystem * This,
            /* [retval][out] */ cwbcoPersistenceModeEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PersistenceMode )( 
            IcwbxSystem * This,
            /* [in] */ cwbcoPersistenceModeEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ValidateMode )( 
            IcwbxSystem * This,
            /* [retval][out] */ cwbcoValidateModeEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ValidateMode )( 
            IcwbxSystem * This,
            /* [in] */ cwbcoValidateModeEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultUserMode )( 
            IcwbxSystem * This,
            /* [retval][out] */ cwbcoDefaultUserModeEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DefaultUserMode )( 
            IcwbxSystem * This,
            /* [in] */ cwbcoDefaultUserModeEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PromptMode )( 
            IcwbxSystem * This,
            /* [retval][out] */ cwbcoPromptModeEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PromptMode )( 
            IcwbxSystem * This,
            /* [in] */ cwbcoPromptModeEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IPAddressLookupMode )( 
            IcwbxSystem * This,
            /* [retval][out] */ cwbcoIPAddrLookupModeEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IPAddressLookupMode )( 
            IcwbxSystem * This,
            /* [in] */ cwbcoIPAddrLookupModeEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PortLookupMode )( 
            IcwbxSystem * This,
            /* [retval][out] */ cwbcoPortLookupModeEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PortLookupMode )( 
            IcwbxSystem * This,
            /* [in] */ cwbcoPortLookupModeEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WindowHandle )( 
            IcwbxSystem * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_WindowHandle )( 
            IcwbxSystem * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UseSecureSockets )( 
            IcwbxSystem * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UseSecureSockets )( 
            IcwbxSystem * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SignonDate )( 
            IcwbxSystem * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrevSignonDate )( 
            IcwbxSystem * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PasswordExpireDate )( 
            IcwbxSystem * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FailedSignons )( 
            IcwbxSystem * This,
            /* [retval][out] */ short *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SystemName )( 
            IcwbxSystem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CanModifyDefaultUserMode )( 
            IcwbxSystem * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CanModifyIPAddressLookupMode )( 
            IcwbxSystem * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CanModifyPortLookupMode )( 
            IcwbxSystem * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CanModifyPersistenceMode )( 
            IcwbxSystem * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CanModifyUseSecureSockets )( 
            IcwbxSystem * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HostCodePage )( 
            IcwbxSystem * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Errors )( 
            IcwbxSystem * This,
            /* [retval][out] */ IcwbxErrors **pVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Define )( 
            IcwbxSystem * This,
            /* [in] */ BSTR systemName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DefineLike )( 
            IcwbxSystem * This,
            /* [in] */ BSTR systemName,
            /* [in] */ IcwbxSystem *system);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Connect )( 
            IcwbxSystem * This,
            /* [in] */ cwbcoServiceEnum service);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Verify )( 
            IcwbxSystem * This,
            /* [in] */ cwbcoServiceEnum service,
            /* [retval][out] */ VARIANT_BOOL *canConnect);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Disconnect )( 
            IcwbxSystem * This,
            /* [in] */ cwbcoServiceEnum service);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *IsConnected )( 
            IcwbxSystem * This,
            /* [in] */ cwbcoServiceEnum service,
            /* [retval][out] */ long *numberOfConnections);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Signon )( 
            IcwbxSystem * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VerifyUserIDPassword )( 
            IcwbxSystem * This,
            /* [in] */ BSTR userID,
            /* [in] */ BSTR password);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ChangePassword )( 
            IcwbxSystem * This,
            /* [in] */ BSTR userID,
            /* [in] */ BSTR oldPassword,
            /* [in] */ BSTR newPassword);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HostVersion )( 
            IcwbxSystem * This,
            /* [retval][out] */ long *pVal);
        
        /* [restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Handle )( 
            IcwbxSystem * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IPAddress )( 
            IcwbxSystem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IPAddress )( 
            IcwbxSystem * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CanModifyIPAddress )( 
            IcwbxSystem * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HostRelease )( 
            IcwbxSystem * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasSignedOn )( 
            IcwbxSystem * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConnectTimeout )( 
            IcwbxSystem * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ConnectTimeout )( 
            IcwbxSystem * This,
            /* [in] */ long newVal);
        
        END_INTERFACE
    } IcwbxSystemVtbl;

    interface IcwbxSystem
    {
        CONST_VTBL struct IcwbxSystemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxSystem_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxSystem_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxSystem_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxSystem_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxSystem_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxSystem_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxSystem_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxSystem_get_UserID(This,pVal)	\
    (This)->lpVtbl -> get_UserID(This,pVal)

#define IcwbxSystem_put_UserID(This,newVal)	\
    (This)->lpVtbl -> put_UserID(This,newVal)

#define IcwbxSystem_put_Password(This,newVal)	\
    (This)->lpVtbl -> put_Password(This,newVal)

#define IcwbxSystem_get_PersistenceMode(This,pVal)	\
    (This)->lpVtbl -> get_PersistenceMode(This,pVal)

#define IcwbxSystem_put_PersistenceMode(This,newVal)	\
    (This)->lpVtbl -> put_PersistenceMode(This,newVal)

#define IcwbxSystem_get_ValidateMode(This,pVal)	\
    (This)->lpVtbl -> get_ValidateMode(This,pVal)

#define IcwbxSystem_put_ValidateMode(This,newVal)	\
    (This)->lpVtbl -> put_ValidateMode(This,newVal)

#define IcwbxSystem_get_DefaultUserMode(This,pVal)	\
    (This)->lpVtbl -> get_DefaultUserMode(This,pVal)

#define IcwbxSystem_put_DefaultUserMode(This,newVal)	\
    (This)->lpVtbl -> put_DefaultUserMode(This,newVal)

#define IcwbxSystem_get_PromptMode(This,pVal)	\
    (This)->lpVtbl -> get_PromptMode(This,pVal)

#define IcwbxSystem_put_PromptMode(This,newVal)	\
    (This)->lpVtbl -> put_PromptMode(This,newVal)

#define IcwbxSystem_get_IPAddressLookupMode(This,pVal)	\
    (This)->lpVtbl -> get_IPAddressLookupMode(This,pVal)

#define IcwbxSystem_put_IPAddressLookupMode(This,newVal)	\
    (This)->lpVtbl -> put_IPAddressLookupMode(This,newVal)

#define IcwbxSystem_get_PortLookupMode(This,pVal)	\
    (This)->lpVtbl -> get_PortLookupMode(This,pVal)

#define IcwbxSystem_put_PortLookupMode(This,newVal)	\
    (This)->lpVtbl -> put_PortLookupMode(This,newVal)

#define IcwbxSystem_get_WindowHandle(This,pVal)	\
    (This)->lpVtbl -> get_WindowHandle(This,pVal)

#define IcwbxSystem_put_WindowHandle(This,newVal)	\
    (This)->lpVtbl -> put_WindowHandle(This,newVal)

#define IcwbxSystem_get_UseSecureSockets(This,pVal)	\
    (This)->lpVtbl -> get_UseSecureSockets(This,pVal)

#define IcwbxSystem_put_UseSecureSockets(This,newVal)	\
    (This)->lpVtbl -> put_UseSecureSockets(This,newVal)

#define IcwbxSystem_get_SignonDate(This,pVal)	\
    (This)->lpVtbl -> get_SignonDate(This,pVal)

#define IcwbxSystem_get_PrevSignonDate(This,pVal)	\
    (This)->lpVtbl -> get_PrevSignonDate(This,pVal)

#define IcwbxSystem_get_PasswordExpireDate(This,pVal)	\
    (This)->lpVtbl -> get_PasswordExpireDate(This,pVal)

#define IcwbxSystem_get_FailedSignons(This,pVal)	\
    (This)->lpVtbl -> get_FailedSignons(This,pVal)

#define IcwbxSystem_get_SystemName(This,pVal)	\
    (This)->lpVtbl -> get_SystemName(This,pVal)

#define IcwbxSystem_get_CanModifyDefaultUserMode(This,pVal)	\
    (This)->lpVtbl -> get_CanModifyDefaultUserMode(This,pVal)

#define IcwbxSystem_get_CanModifyIPAddressLookupMode(This,pVal)	\
    (This)->lpVtbl -> get_CanModifyIPAddressLookupMode(This,pVal)

#define IcwbxSystem_get_CanModifyPortLookupMode(This,pVal)	\
    (This)->lpVtbl -> get_CanModifyPortLookupMode(This,pVal)

#define IcwbxSystem_get_CanModifyPersistenceMode(This,pVal)	\
    (This)->lpVtbl -> get_CanModifyPersistenceMode(This,pVal)

#define IcwbxSystem_get_CanModifyUseSecureSockets(This,pVal)	\
    (This)->lpVtbl -> get_CanModifyUseSecureSockets(This,pVal)

#define IcwbxSystem_get_HostCodePage(This,pVal)	\
    (This)->lpVtbl -> get_HostCodePage(This,pVal)

#define IcwbxSystem_get_Errors(This,pVal)	\
    (This)->lpVtbl -> get_Errors(This,pVal)

#define IcwbxSystem_Define(This,systemName)	\
    (This)->lpVtbl -> Define(This,systemName)

#define IcwbxSystem_DefineLike(This,systemName,system)	\
    (This)->lpVtbl -> DefineLike(This,systemName,system)

#define IcwbxSystem_Connect(This,service)	\
    (This)->lpVtbl -> Connect(This,service)

#define IcwbxSystem_Verify(This,service,canConnect)	\
    (This)->lpVtbl -> Verify(This,service,canConnect)

#define IcwbxSystem_Disconnect(This,service)	\
    (This)->lpVtbl -> Disconnect(This,service)

#define IcwbxSystem_IsConnected(This,service,numberOfConnections)	\
    (This)->lpVtbl -> IsConnected(This,service,numberOfConnections)

#define IcwbxSystem_Signon(This)	\
    (This)->lpVtbl -> Signon(This)

#define IcwbxSystem_VerifyUserIDPassword(This,userID,password)	\
    (This)->lpVtbl -> VerifyUserIDPassword(This,userID,password)

#define IcwbxSystem_ChangePassword(This,userID,oldPassword,newPassword)	\
    (This)->lpVtbl -> ChangePassword(This,userID,oldPassword,newPassword)

#define IcwbxSystem_get_HostVersion(This,pVal)	\
    (This)->lpVtbl -> get_HostVersion(This,pVal)

#define IcwbxSystem_get_Handle(This,pVal)	\
    (This)->lpVtbl -> get_Handle(This,pVal)

#define IcwbxSystem_get_IPAddress(This,pVal)	\
    (This)->lpVtbl -> get_IPAddress(This,pVal)

#define IcwbxSystem_put_IPAddress(This,newVal)	\
    (This)->lpVtbl -> put_IPAddress(This,newVal)

#define IcwbxSystem_get_CanModifyIPAddress(This,pVal)	\
    (This)->lpVtbl -> get_CanModifyIPAddress(This,pVal)

#define IcwbxSystem_get_HostRelease(This,pVal)	\
    (This)->lpVtbl -> get_HostRelease(This,pVal)

#define IcwbxSystem_get_HasSignedOn(This,pVal)	\
    (This)->lpVtbl -> get_HasSignedOn(This,pVal)

#define IcwbxSystem_get_ConnectTimeout(This,pVal)	\
    (This)->lpVtbl -> get_ConnectTimeout(This,pVal)

#define IcwbxSystem_put_ConnectTimeout(This,newVal)	\
    (This)->lpVtbl -> put_ConnectTimeout(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_get_UserID_Proxy( 
    IcwbxSystem * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxSystem_get_UserID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_put_UserID_Proxy( 
    IcwbxSystem * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxSystem_put_UserID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_put_Password_Proxy( 
    IcwbxSystem * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxSystem_put_Password_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_get_PersistenceMode_Proxy( 
    IcwbxSystem * This,
    /* [retval][out] */ cwbcoPersistenceModeEnum *pVal);


void __RPC_STUB IcwbxSystem_get_PersistenceMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_put_PersistenceMode_Proxy( 
    IcwbxSystem * This,
    /* [in] */ cwbcoPersistenceModeEnum newVal);


void __RPC_STUB IcwbxSystem_put_PersistenceMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_get_ValidateMode_Proxy( 
    IcwbxSystem * This,
    /* [retval][out] */ cwbcoValidateModeEnum *pVal);


void __RPC_STUB IcwbxSystem_get_ValidateMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_put_ValidateMode_Proxy( 
    IcwbxSystem * This,
    /* [in] */ cwbcoValidateModeEnum newVal);


void __RPC_STUB IcwbxSystem_put_ValidateMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_get_DefaultUserMode_Proxy( 
    IcwbxSystem * This,
    /* [retval][out] */ cwbcoDefaultUserModeEnum *pVal);


void __RPC_STUB IcwbxSystem_get_DefaultUserMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_put_DefaultUserMode_Proxy( 
    IcwbxSystem * This,
    /* [in] */ cwbcoDefaultUserModeEnum newVal);


void __RPC_STUB IcwbxSystem_put_DefaultUserMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_get_PromptMode_Proxy( 
    IcwbxSystem * This,
    /* [retval][out] */ cwbcoPromptModeEnum *pVal);


void __RPC_STUB IcwbxSystem_get_PromptMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_put_PromptMode_Proxy( 
    IcwbxSystem * This,
    /* [in] */ cwbcoPromptModeEnum newVal);


void __RPC_STUB IcwbxSystem_put_PromptMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_get_IPAddressLookupMode_Proxy( 
    IcwbxSystem * This,
    /* [retval][out] */ cwbcoIPAddrLookupModeEnum *pVal);


void __RPC_STUB IcwbxSystem_get_IPAddressLookupMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_put_IPAddressLookupMode_Proxy( 
    IcwbxSystem * This,
    /* [in] */ cwbcoIPAddrLookupModeEnum newVal);


void __RPC_STUB IcwbxSystem_put_IPAddressLookupMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_get_PortLookupMode_Proxy( 
    IcwbxSystem * This,
    /* [retval][out] */ cwbcoPortLookupModeEnum *pVal);


void __RPC_STUB IcwbxSystem_get_PortLookupMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_put_PortLookupMode_Proxy( 
    IcwbxSystem * This,
    /* [in] */ cwbcoPortLookupModeEnum newVal);


void __RPC_STUB IcwbxSystem_put_PortLookupMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_get_WindowHandle_Proxy( 
    IcwbxSystem * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxSystem_get_WindowHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_put_WindowHandle_Proxy( 
    IcwbxSystem * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxSystem_put_WindowHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_get_UseSecureSockets_Proxy( 
    IcwbxSystem * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxSystem_get_UseSecureSockets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_put_UseSecureSockets_Proxy( 
    IcwbxSystem * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxSystem_put_UseSecureSockets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_get_SignonDate_Proxy( 
    IcwbxSystem * This,
    /* [retval][out] */ DATE *pVal);


void __RPC_STUB IcwbxSystem_get_SignonDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_get_PrevSignonDate_Proxy( 
    IcwbxSystem * This,
    /* [retval][out] */ DATE *pVal);


void __RPC_STUB IcwbxSystem_get_PrevSignonDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_get_PasswordExpireDate_Proxy( 
    IcwbxSystem * This,
    /* [retval][out] */ DATE *pVal);


void __RPC_STUB IcwbxSystem_get_PasswordExpireDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_get_FailedSignons_Proxy( 
    IcwbxSystem * This,
    /* [retval][out] */ short *pVal);


void __RPC_STUB IcwbxSystem_get_FailedSignons_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_get_SystemName_Proxy( 
    IcwbxSystem * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxSystem_get_SystemName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_get_CanModifyDefaultUserMode_Proxy( 
    IcwbxSystem * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxSystem_get_CanModifyDefaultUserMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_get_CanModifyIPAddressLookupMode_Proxy( 
    IcwbxSystem * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxSystem_get_CanModifyIPAddressLookupMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_get_CanModifyPortLookupMode_Proxy( 
    IcwbxSystem * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxSystem_get_CanModifyPortLookupMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_get_CanModifyPersistenceMode_Proxy( 
    IcwbxSystem * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxSystem_get_CanModifyPersistenceMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_get_CanModifyUseSecureSockets_Proxy( 
    IcwbxSystem * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxSystem_get_CanModifyUseSecureSockets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_get_HostCodePage_Proxy( 
    IcwbxSystem * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxSystem_get_HostCodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_get_Errors_Proxy( 
    IcwbxSystem * This,
    /* [retval][out] */ IcwbxErrors **pVal);


void __RPC_STUB IcwbxSystem_get_Errors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_Define_Proxy( 
    IcwbxSystem * This,
    /* [in] */ BSTR systemName);


void __RPC_STUB IcwbxSystem_Define_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_DefineLike_Proxy( 
    IcwbxSystem * This,
    /* [in] */ BSTR systemName,
    /* [in] */ IcwbxSystem *system);


void __RPC_STUB IcwbxSystem_DefineLike_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_Connect_Proxy( 
    IcwbxSystem * This,
    /* [in] */ cwbcoServiceEnum service);


void __RPC_STUB IcwbxSystem_Connect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_Verify_Proxy( 
    IcwbxSystem * This,
    /* [in] */ cwbcoServiceEnum service,
    /* [retval][out] */ VARIANT_BOOL *canConnect);


void __RPC_STUB IcwbxSystem_Verify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_Disconnect_Proxy( 
    IcwbxSystem * This,
    /* [in] */ cwbcoServiceEnum service);


void __RPC_STUB IcwbxSystem_Disconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_IsConnected_Proxy( 
    IcwbxSystem * This,
    /* [in] */ cwbcoServiceEnum service,
    /* [retval][out] */ long *numberOfConnections);


void __RPC_STUB IcwbxSystem_IsConnected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_Signon_Proxy( 
    IcwbxSystem * This);


void __RPC_STUB IcwbxSystem_Signon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_VerifyUserIDPassword_Proxy( 
    IcwbxSystem * This,
    /* [in] */ BSTR userID,
    /* [in] */ BSTR password);


void __RPC_STUB IcwbxSystem_VerifyUserIDPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_ChangePassword_Proxy( 
    IcwbxSystem * This,
    /* [in] */ BSTR userID,
    /* [in] */ BSTR oldPassword,
    /* [in] */ BSTR newPassword);


void __RPC_STUB IcwbxSystem_ChangePassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_get_HostVersion_Proxy( 
    IcwbxSystem * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxSystem_get_HostVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_get_Handle_Proxy( 
    IcwbxSystem * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxSystem_get_Handle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_get_IPAddress_Proxy( 
    IcwbxSystem * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxSystem_get_IPAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_put_IPAddress_Proxy( 
    IcwbxSystem * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxSystem_put_IPAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_get_CanModifyIPAddress_Proxy( 
    IcwbxSystem * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxSystem_get_CanModifyIPAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_get_HostRelease_Proxy( 
    IcwbxSystem * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxSystem_get_HostRelease_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_get_HasSignedOn_Proxy( 
    IcwbxSystem * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxSystem_get_HasSignedOn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_get_ConnectTimeout_Proxy( 
    IcwbxSystem * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxSystem_get_ConnectTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxSystem_put_ConnectTimeout_Proxy( 
    IcwbxSystem * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxSystem_put_ConnectTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxSystem_INTERFACE_DEFINED__ */


#ifndef __IcwbxSystemNames_INTERFACE_DEFINED__
#define __IcwbxSystemNames_INTERFACE_DEFINED__

/* interface IcwbxSystemNames */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxSystemNames;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FDE7ADB1-1A69-11D2-849C-0004AC94E175")
    IcwbxSystemNames : public IDispatch
    {
    public:
        virtual /* [restricted][id] */ HRESULT STDMETHODCALLTYPE _NewEnum( 
            /* [retval][out] */ IUnknown **ppvObject) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ActiveEnvironment( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultSystem( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxSystemNamesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxSystemNames * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxSystemNames * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxSystemNames * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxSystemNames * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxSystemNames * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxSystemNames * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxSystemNames * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [restricted][id] */ HRESULT ( STDMETHODCALLTYPE *_NewEnum )( 
            IcwbxSystemNames * This,
            /* [retval][out] */ IUnknown **ppvObject);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IcwbxSystemNames * This,
            /* [in] */ long index,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IcwbxSystemNames * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ActiveEnvironment )( 
            IcwbxSystemNames * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultSystem )( 
            IcwbxSystemNames * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IcwbxSystemNames * This);
        
        END_INTERFACE
    } IcwbxSystemNamesVtbl;

    interface IcwbxSystemNames
    {
        CONST_VTBL struct IcwbxSystemNamesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxSystemNames_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxSystemNames_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxSystemNames_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxSystemNames_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxSystemNames_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxSystemNames_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxSystemNames_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxSystemNames__NewEnum(This,ppvObject)	\
    (This)->lpVtbl -> _NewEnum(This,ppvObject)

#define IcwbxSystemNames_get_Item(This,index,pVal)	\
    (This)->lpVtbl -> get_Item(This,index,pVal)

#define IcwbxSystemNames_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IcwbxSystemNames_get_ActiveEnvironment(This,pVal)	\
    (This)->lpVtbl -> get_ActiveEnvironment(This,pVal)

#define IcwbxSystemNames_get_DefaultSystem(This,pVal)	\
    (This)->lpVtbl -> get_DefaultSystem(This,pVal)

#define IcwbxSystemNames_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [restricted][id] */ HRESULT STDMETHODCALLTYPE IcwbxSystemNames__NewEnum_Proxy( 
    IcwbxSystemNames * This,
    /* [retval][out] */ IUnknown **ppvObject);


void __RPC_STUB IcwbxSystemNames__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystemNames_get_Item_Proxy( 
    IcwbxSystemNames * This,
    /* [in] */ long index,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxSystemNames_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystemNames_get_Count_Proxy( 
    IcwbxSystemNames * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxSystemNames_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystemNames_get_ActiveEnvironment_Proxy( 
    IcwbxSystemNames * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxSystemNames_get_ActiveEnvironment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxSystemNames_get_DefaultSystem_Proxy( 
    IcwbxSystemNames * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxSystemNames_get_DefaultSystem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxSystemNames_Refresh_Proxy( 
    IcwbxSystemNames * This);


void __RPC_STUB IcwbxSystemNames_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxSystemNames_INTERFACE_DEFINED__ */


#ifndef __IcwbxClientInfo_INTERFACE_DEFINED__
#define __IcwbxClientInfo_INTERFACE_DEFINED__

/* interface IcwbxClientInfo */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxClientInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("86F9DB13-15D5-11D2-849C-0004AC94E175")
    IcwbxClientInfo : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ComponentInstallStatus( 
            /* [in] */ cwbadClientComponentEnum componentID,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ClientVersion( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ClientRelease( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ClientModificationLevel( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ClientFixLevel( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OpNavPluginInstallStatus( 
            /* [in] */ BSTR pluginName,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxClientInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxClientInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxClientInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxClientInfo * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxClientInfo * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxClientInfo * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxClientInfo * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxClientInfo * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ComponentInstallStatus )( 
            IcwbxClientInfo * This,
            /* [in] */ cwbadClientComponentEnum componentID,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ClientVersion )( 
            IcwbxClientInfo * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ClientRelease )( 
            IcwbxClientInfo * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ClientModificationLevel )( 
            IcwbxClientInfo * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ClientFixLevel )( 
            IcwbxClientInfo * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OpNavPluginInstallStatus )( 
            IcwbxClientInfo * This,
            /* [in] */ BSTR pluginName,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        END_INTERFACE
    } IcwbxClientInfoVtbl;

    interface IcwbxClientInfo
    {
        CONST_VTBL struct IcwbxClientInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxClientInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxClientInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxClientInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxClientInfo_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxClientInfo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxClientInfo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxClientInfo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxClientInfo_get_ComponentInstallStatus(This,componentID,pVal)	\
    (This)->lpVtbl -> get_ComponentInstallStatus(This,componentID,pVal)

#define IcwbxClientInfo_get_ClientVersion(This,pVal)	\
    (This)->lpVtbl -> get_ClientVersion(This,pVal)

#define IcwbxClientInfo_get_ClientRelease(This,pVal)	\
    (This)->lpVtbl -> get_ClientRelease(This,pVal)

#define IcwbxClientInfo_get_ClientModificationLevel(This,pVal)	\
    (This)->lpVtbl -> get_ClientModificationLevel(This,pVal)

#define IcwbxClientInfo_get_ClientFixLevel(This,pVal)	\
    (This)->lpVtbl -> get_ClientFixLevel(This,pVal)

#define IcwbxClientInfo_get_OpNavPluginInstallStatus(This,pluginName,pVal)	\
    (This)->lpVtbl -> get_OpNavPluginInstallStatus(This,pluginName,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxClientInfo_get_ComponentInstallStatus_Proxy( 
    IcwbxClientInfo * This,
    /* [in] */ cwbadClientComponentEnum componentID,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxClientInfo_get_ComponentInstallStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxClientInfo_get_ClientVersion_Proxy( 
    IcwbxClientInfo * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxClientInfo_get_ClientVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxClientInfo_get_ClientRelease_Proxy( 
    IcwbxClientInfo * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxClientInfo_get_ClientRelease_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxClientInfo_get_ClientModificationLevel_Proxy( 
    IcwbxClientInfo * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxClientInfo_get_ClientModificationLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxClientInfo_get_ClientFixLevel_Proxy( 
    IcwbxClientInfo * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxClientInfo_get_ClientFixLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxClientInfo_get_OpNavPluginInstallStatus_Proxy( 
    IcwbxClientInfo * This,
    /* [in] */ BSTR pluginName,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxClientInfo_get_OpNavPluginInstallStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxClientInfo_INTERFACE_DEFINED__ */


#ifndef __IcwbxDataQueue_INTERFACE_DEFINED__
#define __IcwbxDataQueue_INTERFACE_DEFINED__

/* interface IcwbxDataQueue */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDataQueue;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("86F9DB15-15D5-11D2-849C-0004AC94E175")
    IcwbxDataQueue : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_System( 
            /* [retval][out] */ IcwbxSystem **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_System( 
            /* [in] */ IcwbxSystem *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LibraryName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LibraryName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_QueueName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_QueueName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Create( 
            /* [defaultvalue][optional][in] */ IcwbxDataQueueAttributes *dqAttributes = 0) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Peek( 
            /* [defaultvalue][optional][in] */ long waitTime,
            /* [optional][out] */ VARIANT *senderInfo,
            /* [retval][out] */ VARIANT *dqData) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Read( 
            /* [defaultvalue][optional][in] */ long waitTime,
            /* [optional][out] */ VARIANT *senderInfo,
            /* [retval][out] */ VARIANT *dqData) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Write( 
            /* [in] */ VARIANT dqData,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL commitBeforeReturn = 1) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE QueryAttributes( 
            /* [retval][out] */ IcwbxDataQueueAttributes **dqAttributes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Errors( 
            /* [retval][out] */ IcwbxErrors **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MaximumRetrievalLength( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MaximumRetrievalLength( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Exists( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDataQueueVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDataQueue * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDataQueue * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDataQueue * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDataQueue * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDataQueue * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDataQueue * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDataQueue * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_System )( 
            IcwbxDataQueue * This,
            /* [retval][out] */ IcwbxSystem **pVal);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_System )( 
            IcwbxDataQueue * This,
            /* [in] */ IcwbxSystem *newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LibraryName )( 
            IcwbxDataQueue * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LibraryName )( 
            IcwbxDataQueue * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_QueueName )( 
            IcwbxDataQueue * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_QueueName )( 
            IcwbxDataQueue * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            IcwbxDataQueue * This,
            /* [defaultvalue][optional][in] */ IcwbxDataQueueAttributes *dqAttributes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Delete )( 
            IcwbxDataQueue * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Peek )( 
            IcwbxDataQueue * This,
            /* [defaultvalue][optional][in] */ long waitTime,
            /* [optional][out] */ VARIANT *senderInfo,
            /* [retval][out] */ VARIANT *dqData);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Read )( 
            IcwbxDataQueue * This,
            /* [defaultvalue][optional][in] */ long waitTime,
            /* [optional][out] */ VARIANT *senderInfo,
            /* [retval][out] */ VARIANT *dqData);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Write )( 
            IcwbxDataQueue * This,
            /* [in] */ VARIANT dqData,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL commitBeforeReturn);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IcwbxDataQueue * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *QueryAttributes )( 
            IcwbxDataQueue * This,
            /* [retval][out] */ IcwbxDataQueueAttributes **dqAttributes);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Errors )( 
            IcwbxDataQueue * This,
            /* [retval][out] */ IcwbxErrors **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaximumRetrievalLength )( 
            IcwbxDataQueue * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaximumRetrievalLength )( 
            IcwbxDataQueue * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Exists )( 
            IcwbxDataQueue * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        END_INTERFACE
    } IcwbxDataQueueVtbl;

    interface IcwbxDataQueue
    {
        CONST_VTBL struct IcwbxDataQueueVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDataQueue_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDataQueue_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDataQueue_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDataQueue_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDataQueue_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDataQueue_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDataQueue_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDataQueue_get_System(This,pVal)	\
    (This)->lpVtbl -> get_System(This,pVal)

#define IcwbxDataQueue_putref_System(This,newVal)	\
    (This)->lpVtbl -> putref_System(This,newVal)

#define IcwbxDataQueue_get_LibraryName(This,pVal)	\
    (This)->lpVtbl -> get_LibraryName(This,pVal)

#define IcwbxDataQueue_put_LibraryName(This,newVal)	\
    (This)->lpVtbl -> put_LibraryName(This,newVal)

#define IcwbxDataQueue_get_QueueName(This,pVal)	\
    (This)->lpVtbl -> get_QueueName(This,pVal)

#define IcwbxDataQueue_put_QueueName(This,newVal)	\
    (This)->lpVtbl -> put_QueueName(This,newVal)

#define IcwbxDataQueue_Create(This,dqAttributes)	\
    (This)->lpVtbl -> Create(This,dqAttributes)

#define IcwbxDataQueue_Delete(This)	\
    (This)->lpVtbl -> Delete(This)

#define IcwbxDataQueue_Peek(This,waitTime,senderInfo,dqData)	\
    (This)->lpVtbl -> Peek(This,waitTime,senderInfo,dqData)

#define IcwbxDataQueue_Read(This,waitTime,senderInfo,dqData)	\
    (This)->lpVtbl -> Read(This,waitTime,senderInfo,dqData)

#define IcwbxDataQueue_Write(This,dqData,commitBeforeReturn)	\
    (This)->lpVtbl -> Write(This,dqData,commitBeforeReturn)

#define IcwbxDataQueue_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define IcwbxDataQueue_QueryAttributes(This,dqAttributes)	\
    (This)->lpVtbl -> QueryAttributes(This,dqAttributes)

#define IcwbxDataQueue_get_Errors(This,pVal)	\
    (This)->lpVtbl -> get_Errors(This,pVal)

#define IcwbxDataQueue_get_MaximumRetrievalLength(This,pVal)	\
    (This)->lpVtbl -> get_MaximumRetrievalLength(This,pVal)

#define IcwbxDataQueue_put_MaximumRetrievalLength(This,newVal)	\
    (This)->lpVtbl -> put_MaximumRetrievalLength(This,newVal)

#define IcwbxDataQueue_get_Exists(This,pVal)	\
    (This)->lpVtbl -> get_Exists(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueue_get_System_Proxy( 
    IcwbxDataQueue * This,
    /* [retval][out] */ IcwbxSystem **pVal);


void __RPC_STUB IcwbxDataQueue_get_System_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueue_putref_System_Proxy( 
    IcwbxDataQueue * This,
    /* [in] */ IcwbxSystem *newVal);


void __RPC_STUB IcwbxDataQueue_putref_System_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueue_get_LibraryName_Proxy( 
    IcwbxDataQueue * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDataQueue_get_LibraryName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueue_put_LibraryName_Proxy( 
    IcwbxDataQueue * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDataQueue_put_LibraryName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueue_get_QueueName_Proxy( 
    IcwbxDataQueue * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDataQueue_get_QueueName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueue_put_QueueName_Proxy( 
    IcwbxDataQueue * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDataQueue_put_QueueName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueue_Create_Proxy( 
    IcwbxDataQueue * This,
    /* [defaultvalue][optional][in] */ IcwbxDataQueueAttributes *dqAttributes);


void __RPC_STUB IcwbxDataQueue_Create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueue_Delete_Proxy( 
    IcwbxDataQueue * This);


void __RPC_STUB IcwbxDataQueue_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueue_Peek_Proxy( 
    IcwbxDataQueue * This,
    /* [defaultvalue][optional][in] */ long waitTime,
    /* [optional][out] */ VARIANT *senderInfo,
    /* [retval][out] */ VARIANT *dqData);


void __RPC_STUB IcwbxDataQueue_Peek_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueue_Read_Proxy( 
    IcwbxDataQueue * This,
    /* [defaultvalue][optional][in] */ long waitTime,
    /* [optional][out] */ VARIANT *senderInfo,
    /* [retval][out] */ VARIANT *dqData);


void __RPC_STUB IcwbxDataQueue_Read_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueue_Write_Proxy( 
    IcwbxDataQueue * This,
    /* [in] */ VARIANT dqData,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL commitBeforeReturn);


void __RPC_STUB IcwbxDataQueue_Write_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueue_Clear_Proxy( 
    IcwbxDataQueue * This);


void __RPC_STUB IcwbxDataQueue_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueue_QueryAttributes_Proxy( 
    IcwbxDataQueue * This,
    /* [retval][out] */ IcwbxDataQueueAttributes **dqAttributes);


void __RPC_STUB IcwbxDataQueue_QueryAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueue_get_Errors_Proxy( 
    IcwbxDataQueue * This,
    /* [retval][out] */ IcwbxErrors **pVal);


void __RPC_STUB IcwbxDataQueue_get_Errors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueue_get_MaximumRetrievalLength_Proxy( 
    IcwbxDataQueue * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxDataQueue_get_MaximumRetrievalLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueue_put_MaximumRetrievalLength_Proxy( 
    IcwbxDataQueue * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDataQueue_put_MaximumRetrievalLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueue_get_Exists_Proxy( 
    IcwbxDataQueue * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDataQueue_get_Exists_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDataQueue_INTERFACE_DEFINED__ */


#ifndef __IcwbxKeyedDataQueue_INTERFACE_DEFINED__
#define __IcwbxKeyedDataQueue_INTERFACE_DEFINED__

/* interface IcwbxKeyedDataQueue */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxKeyedDataQueue;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("86F9DB19-15D5-11D2-849C-0004AC94E175")
    IcwbxKeyedDataQueue : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_System( 
            /* [retval][out] */ IcwbxSystem **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_System( 
            /* [in] */ IcwbxSystem *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LibraryName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LibraryName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_QueueName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_QueueName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ IcwbxDataQueueAttributes *dqAttributes) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Peek( 
            /* [out][in] */ VARIANT *keyValue,
            /* [defaultvalue][optional][in] */ cwbdqSearchOrderEnum searchOrder,
            /* [defaultvalue][optional][in] */ long waitTime,
            /* [optional][out] */ VARIANT *senderInfo,
            /* [retval][out] */ VARIANT *dqData) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Read( 
            /* [out][in] */ VARIANT *keyValue,
            /* [defaultvalue][optional][in] */ cwbdqSearchOrderEnum searchOrder,
            /* [defaultvalue][optional][in] */ long waitTime,
            /* [optional][out] */ VARIANT *senderInfo,
            /* [retval][out] */ VARIANT *dqData) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Write( 
            /* [in] */ VARIANT dqData,
            /* [in] */ VARIANT keyValue,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL commitBeforeReturn = 1) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ClearKey( 
            /* [in] */ VARIANT keyValue) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE QueryAttributes( 
            /* [retval][out] */ IcwbxDataQueueAttributes **dqAttributes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Errors( 
            /* [retval][out] */ IcwbxErrors **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MaximumRetrievalLength( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MaximumRetrievalLength( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Exists( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxKeyedDataQueueVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxKeyedDataQueue * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxKeyedDataQueue * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxKeyedDataQueue * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxKeyedDataQueue * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxKeyedDataQueue * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxKeyedDataQueue * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxKeyedDataQueue * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_System )( 
            IcwbxKeyedDataQueue * This,
            /* [retval][out] */ IcwbxSystem **pVal);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_System )( 
            IcwbxKeyedDataQueue * This,
            /* [in] */ IcwbxSystem *newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LibraryName )( 
            IcwbxKeyedDataQueue * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LibraryName )( 
            IcwbxKeyedDataQueue * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_QueueName )( 
            IcwbxKeyedDataQueue * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_QueueName )( 
            IcwbxKeyedDataQueue * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            IcwbxKeyedDataQueue * This,
            /* [in] */ IcwbxDataQueueAttributes *dqAttributes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Delete )( 
            IcwbxKeyedDataQueue * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Peek )( 
            IcwbxKeyedDataQueue * This,
            /* [out][in] */ VARIANT *keyValue,
            /* [defaultvalue][optional][in] */ cwbdqSearchOrderEnum searchOrder,
            /* [defaultvalue][optional][in] */ long waitTime,
            /* [optional][out] */ VARIANT *senderInfo,
            /* [retval][out] */ VARIANT *dqData);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Read )( 
            IcwbxKeyedDataQueue * This,
            /* [out][in] */ VARIANT *keyValue,
            /* [defaultvalue][optional][in] */ cwbdqSearchOrderEnum searchOrder,
            /* [defaultvalue][optional][in] */ long waitTime,
            /* [optional][out] */ VARIANT *senderInfo,
            /* [retval][out] */ VARIANT *dqData);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Write )( 
            IcwbxKeyedDataQueue * This,
            /* [in] */ VARIANT dqData,
            /* [in] */ VARIANT keyValue,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL commitBeforeReturn);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IcwbxKeyedDataQueue * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ClearKey )( 
            IcwbxKeyedDataQueue * This,
            /* [in] */ VARIANT keyValue);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *QueryAttributes )( 
            IcwbxKeyedDataQueue * This,
            /* [retval][out] */ IcwbxDataQueueAttributes **dqAttributes);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Errors )( 
            IcwbxKeyedDataQueue * This,
            /* [retval][out] */ IcwbxErrors **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaximumRetrievalLength )( 
            IcwbxKeyedDataQueue * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaximumRetrievalLength )( 
            IcwbxKeyedDataQueue * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Exists )( 
            IcwbxKeyedDataQueue * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        END_INTERFACE
    } IcwbxKeyedDataQueueVtbl;

    interface IcwbxKeyedDataQueue
    {
        CONST_VTBL struct IcwbxKeyedDataQueueVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxKeyedDataQueue_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxKeyedDataQueue_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxKeyedDataQueue_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxKeyedDataQueue_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxKeyedDataQueue_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxKeyedDataQueue_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxKeyedDataQueue_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxKeyedDataQueue_get_System(This,pVal)	\
    (This)->lpVtbl -> get_System(This,pVal)

#define IcwbxKeyedDataQueue_putref_System(This,newVal)	\
    (This)->lpVtbl -> putref_System(This,newVal)

#define IcwbxKeyedDataQueue_get_LibraryName(This,pVal)	\
    (This)->lpVtbl -> get_LibraryName(This,pVal)

#define IcwbxKeyedDataQueue_put_LibraryName(This,newVal)	\
    (This)->lpVtbl -> put_LibraryName(This,newVal)

#define IcwbxKeyedDataQueue_get_QueueName(This,pVal)	\
    (This)->lpVtbl -> get_QueueName(This,pVal)

#define IcwbxKeyedDataQueue_put_QueueName(This,newVal)	\
    (This)->lpVtbl -> put_QueueName(This,newVal)

#define IcwbxKeyedDataQueue_Create(This,dqAttributes)	\
    (This)->lpVtbl -> Create(This,dqAttributes)

#define IcwbxKeyedDataQueue_Delete(This)	\
    (This)->lpVtbl -> Delete(This)

#define IcwbxKeyedDataQueue_Peek(This,keyValue,searchOrder,waitTime,senderInfo,dqData)	\
    (This)->lpVtbl -> Peek(This,keyValue,searchOrder,waitTime,senderInfo,dqData)

#define IcwbxKeyedDataQueue_Read(This,keyValue,searchOrder,waitTime,senderInfo,dqData)	\
    (This)->lpVtbl -> Read(This,keyValue,searchOrder,waitTime,senderInfo,dqData)

#define IcwbxKeyedDataQueue_Write(This,dqData,keyValue,commitBeforeReturn)	\
    (This)->lpVtbl -> Write(This,dqData,keyValue,commitBeforeReturn)

#define IcwbxKeyedDataQueue_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define IcwbxKeyedDataQueue_ClearKey(This,keyValue)	\
    (This)->lpVtbl -> ClearKey(This,keyValue)

#define IcwbxKeyedDataQueue_QueryAttributes(This,dqAttributes)	\
    (This)->lpVtbl -> QueryAttributes(This,dqAttributes)

#define IcwbxKeyedDataQueue_get_Errors(This,pVal)	\
    (This)->lpVtbl -> get_Errors(This,pVal)

#define IcwbxKeyedDataQueue_get_MaximumRetrievalLength(This,pVal)	\
    (This)->lpVtbl -> get_MaximumRetrievalLength(This,pVal)

#define IcwbxKeyedDataQueue_put_MaximumRetrievalLength(This,newVal)	\
    (This)->lpVtbl -> put_MaximumRetrievalLength(This,newVal)

#define IcwbxKeyedDataQueue_get_Exists(This,pVal)	\
    (This)->lpVtbl -> get_Exists(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxKeyedDataQueue_get_System_Proxy( 
    IcwbxKeyedDataQueue * This,
    /* [retval][out] */ IcwbxSystem **pVal);


void __RPC_STUB IcwbxKeyedDataQueue_get_System_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IcwbxKeyedDataQueue_putref_System_Proxy( 
    IcwbxKeyedDataQueue * This,
    /* [in] */ IcwbxSystem *newVal);


void __RPC_STUB IcwbxKeyedDataQueue_putref_System_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxKeyedDataQueue_get_LibraryName_Proxy( 
    IcwbxKeyedDataQueue * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxKeyedDataQueue_get_LibraryName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxKeyedDataQueue_put_LibraryName_Proxy( 
    IcwbxKeyedDataQueue * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxKeyedDataQueue_put_LibraryName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxKeyedDataQueue_get_QueueName_Proxy( 
    IcwbxKeyedDataQueue * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxKeyedDataQueue_get_QueueName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxKeyedDataQueue_put_QueueName_Proxy( 
    IcwbxKeyedDataQueue * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxKeyedDataQueue_put_QueueName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxKeyedDataQueue_Create_Proxy( 
    IcwbxKeyedDataQueue * This,
    /* [in] */ IcwbxDataQueueAttributes *dqAttributes);


void __RPC_STUB IcwbxKeyedDataQueue_Create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxKeyedDataQueue_Delete_Proxy( 
    IcwbxKeyedDataQueue * This);


void __RPC_STUB IcwbxKeyedDataQueue_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxKeyedDataQueue_Peek_Proxy( 
    IcwbxKeyedDataQueue * This,
    /* [out][in] */ VARIANT *keyValue,
    /* [defaultvalue][optional][in] */ cwbdqSearchOrderEnum searchOrder,
    /* [defaultvalue][optional][in] */ long waitTime,
    /* [optional][out] */ VARIANT *senderInfo,
    /* [retval][out] */ VARIANT *dqData);


void __RPC_STUB IcwbxKeyedDataQueue_Peek_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxKeyedDataQueue_Read_Proxy( 
    IcwbxKeyedDataQueue * This,
    /* [out][in] */ VARIANT *keyValue,
    /* [defaultvalue][optional][in] */ cwbdqSearchOrderEnum searchOrder,
    /* [defaultvalue][optional][in] */ long waitTime,
    /* [optional][out] */ VARIANT *senderInfo,
    /* [retval][out] */ VARIANT *dqData);


void __RPC_STUB IcwbxKeyedDataQueue_Read_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxKeyedDataQueue_Write_Proxy( 
    IcwbxKeyedDataQueue * This,
    /* [in] */ VARIANT dqData,
    /* [in] */ VARIANT keyValue,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL commitBeforeReturn);


void __RPC_STUB IcwbxKeyedDataQueue_Write_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxKeyedDataQueue_Clear_Proxy( 
    IcwbxKeyedDataQueue * This);


void __RPC_STUB IcwbxKeyedDataQueue_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxKeyedDataQueue_ClearKey_Proxy( 
    IcwbxKeyedDataQueue * This,
    /* [in] */ VARIANT keyValue);


void __RPC_STUB IcwbxKeyedDataQueue_ClearKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxKeyedDataQueue_QueryAttributes_Proxy( 
    IcwbxKeyedDataQueue * This,
    /* [retval][out] */ IcwbxDataQueueAttributes **dqAttributes);


void __RPC_STUB IcwbxKeyedDataQueue_QueryAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxKeyedDataQueue_get_Errors_Proxy( 
    IcwbxKeyedDataQueue * This,
    /* [retval][out] */ IcwbxErrors **pVal);


void __RPC_STUB IcwbxKeyedDataQueue_get_Errors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxKeyedDataQueue_get_MaximumRetrievalLength_Proxy( 
    IcwbxKeyedDataQueue * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxKeyedDataQueue_get_MaximumRetrievalLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxKeyedDataQueue_put_MaximumRetrievalLength_Proxy( 
    IcwbxKeyedDataQueue * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxKeyedDataQueue_put_MaximumRetrievalLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxKeyedDataQueue_get_Exists_Proxy( 
    IcwbxKeyedDataQueue * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxKeyedDataQueue_get_Exists_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxKeyedDataQueue_INTERFACE_DEFINED__ */


#ifndef __IcwbxDataQueueAttributes_INTERFACE_DEFINED__
#define __IcwbxDataQueueAttributes_INTERFACE_DEFINED__

/* interface IcwbxDataQueueAttributes */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDataQueueAttributes;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("86F9DB1D-15D5-11D2-849C-0004AC94E175")
    IcwbxDataQueueAttributes : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PublicAuthority( 
            /* [in] */ cwbdqAuthorityEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ForceWritesToStorage( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ForceWritesToStorage( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MaxRecordLength( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MaxRecordLength( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RetrievalOrder( 
            /* [retval][out] */ cwbdqRetrievalOrderEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RetrievalOrder( 
            /* [in] */ cwbdqRetrievalOrderEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_KeySize( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_KeySize( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SenderInfoSaved( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SenderInfoSaved( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get_Handle( 
            /* [retval][out] */ long *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDataQueueAttributesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDataQueueAttributes * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDataQueueAttributes * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDataQueueAttributes * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDataQueueAttributes * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDataQueueAttributes * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDataQueueAttributes * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDataQueueAttributes * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PublicAuthority )( 
            IcwbxDataQueueAttributes * This,
            /* [in] */ cwbdqAuthorityEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            IcwbxDataQueueAttributes * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            IcwbxDataQueueAttributes * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ForceWritesToStorage )( 
            IcwbxDataQueueAttributes * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ForceWritesToStorage )( 
            IcwbxDataQueueAttributes * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxRecordLength )( 
            IcwbxDataQueueAttributes * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaxRecordLength )( 
            IcwbxDataQueueAttributes * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RetrievalOrder )( 
            IcwbxDataQueueAttributes * This,
            /* [retval][out] */ cwbdqRetrievalOrderEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RetrievalOrder )( 
            IcwbxDataQueueAttributes * This,
            /* [in] */ cwbdqRetrievalOrderEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_KeySize )( 
            IcwbxDataQueueAttributes * This,
            /* [retval][out] */ short *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_KeySize )( 
            IcwbxDataQueueAttributes * This,
            /* [in] */ short newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SenderInfoSaved )( 
            IcwbxDataQueueAttributes * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SenderInfoSaved )( 
            IcwbxDataQueueAttributes * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Handle )( 
            IcwbxDataQueueAttributes * This,
            /* [retval][out] */ long *pVal);
        
        END_INTERFACE
    } IcwbxDataQueueAttributesVtbl;

    interface IcwbxDataQueueAttributes
    {
        CONST_VTBL struct IcwbxDataQueueAttributesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDataQueueAttributes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDataQueueAttributes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDataQueueAttributes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDataQueueAttributes_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDataQueueAttributes_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDataQueueAttributes_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDataQueueAttributes_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDataQueueAttributes_put_PublicAuthority(This,newVal)	\
    (This)->lpVtbl -> put_PublicAuthority(This,newVal)

#define IcwbxDataQueueAttributes_get_Description(This,pVal)	\
    (This)->lpVtbl -> get_Description(This,pVal)

#define IcwbxDataQueueAttributes_put_Description(This,newVal)	\
    (This)->lpVtbl -> put_Description(This,newVal)

#define IcwbxDataQueueAttributes_get_ForceWritesToStorage(This,pVal)	\
    (This)->lpVtbl -> get_ForceWritesToStorage(This,pVal)

#define IcwbxDataQueueAttributes_put_ForceWritesToStorage(This,newVal)	\
    (This)->lpVtbl -> put_ForceWritesToStorage(This,newVal)

#define IcwbxDataQueueAttributes_get_MaxRecordLength(This,pVal)	\
    (This)->lpVtbl -> get_MaxRecordLength(This,pVal)

#define IcwbxDataQueueAttributes_put_MaxRecordLength(This,newVal)	\
    (This)->lpVtbl -> put_MaxRecordLength(This,newVal)

#define IcwbxDataQueueAttributes_get_RetrievalOrder(This,pVal)	\
    (This)->lpVtbl -> get_RetrievalOrder(This,pVal)

#define IcwbxDataQueueAttributes_put_RetrievalOrder(This,newVal)	\
    (This)->lpVtbl -> put_RetrievalOrder(This,newVal)

#define IcwbxDataQueueAttributes_get_KeySize(This,pVal)	\
    (This)->lpVtbl -> get_KeySize(This,pVal)

#define IcwbxDataQueueAttributes_put_KeySize(This,newVal)	\
    (This)->lpVtbl -> put_KeySize(This,newVal)

#define IcwbxDataQueueAttributes_get_SenderInfoSaved(This,pVal)	\
    (This)->lpVtbl -> get_SenderInfoSaved(This,pVal)

#define IcwbxDataQueueAttributes_put_SenderInfoSaved(This,newVal)	\
    (This)->lpVtbl -> put_SenderInfoSaved(This,newVal)

#define IcwbxDataQueueAttributes_get_Handle(This,pVal)	\
    (This)->lpVtbl -> get_Handle(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueueAttributes_put_PublicAuthority_Proxy( 
    IcwbxDataQueueAttributes * This,
    /* [in] */ cwbdqAuthorityEnum newVal);


void __RPC_STUB IcwbxDataQueueAttributes_put_PublicAuthority_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueueAttributes_get_Description_Proxy( 
    IcwbxDataQueueAttributes * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDataQueueAttributes_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueueAttributes_put_Description_Proxy( 
    IcwbxDataQueueAttributes * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDataQueueAttributes_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueueAttributes_get_ForceWritesToStorage_Proxy( 
    IcwbxDataQueueAttributes * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDataQueueAttributes_get_ForceWritesToStorage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueueAttributes_put_ForceWritesToStorage_Proxy( 
    IcwbxDataQueueAttributes * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDataQueueAttributes_put_ForceWritesToStorage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueueAttributes_get_MaxRecordLength_Proxy( 
    IcwbxDataQueueAttributes * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxDataQueueAttributes_get_MaxRecordLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueueAttributes_put_MaxRecordLength_Proxy( 
    IcwbxDataQueueAttributes * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDataQueueAttributes_put_MaxRecordLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueueAttributes_get_RetrievalOrder_Proxy( 
    IcwbxDataQueueAttributes * This,
    /* [retval][out] */ cwbdqRetrievalOrderEnum *pVal);


void __RPC_STUB IcwbxDataQueueAttributes_get_RetrievalOrder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueueAttributes_put_RetrievalOrder_Proxy( 
    IcwbxDataQueueAttributes * This,
    /* [in] */ cwbdqRetrievalOrderEnum newVal);


void __RPC_STUB IcwbxDataQueueAttributes_put_RetrievalOrder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueueAttributes_get_KeySize_Proxy( 
    IcwbxDataQueueAttributes * This,
    /* [retval][out] */ short *pVal);


void __RPC_STUB IcwbxDataQueueAttributes_get_KeySize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueueAttributes_put_KeySize_Proxy( 
    IcwbxDataQueueAttributes * This,
    /* [in] */ short newVal);


void __RPC_STUB IcwbxDataQueueAttributes_put_KeySize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueueAttributes_get_SenderInfoSaved_Proxy( 
    IcwbxDataQueueAttributes * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDataQueueAttributes_get_SenderInfoSaved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueueAttributes_put_SenderInfoSaved_Proxy( 
    IcwbxDataQueueAttributes * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDataQueueAttributes_put_SenderInfoSaved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueueAttributes_get_Handle_Proxy( 
    IcwbxDataQueueAttributes * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxDataQueueAttributes_get_Handle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDataQueueAttributes_INTERFACE_DEFINED__ */


#ifndef __IcwbxDataQueueSenderInfo_INTERFACE_DEFINED__
#define __IcwbxDataQueueSenderInfo_INTERFACE_DEFINED__

/* interface IcwbxDataQueueSenderInfo */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDataQueueSenderInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("43E0F3E2-3DFA-11D2-8392-0004ACBA1FF2")
    IcwbxDataQueueSenderInfo : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UserName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UserProfileName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_JobName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_JobNumber( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [restricted][id] */ HRESULT STDMETHODCALLTYPE Populate( 
            /* [in] */ long dqDataHandle,
            /* [out] */ long *returnCode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDataQueueSenderInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDataQueueSenderInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDataQueueSenderInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDataQueueSenderInfo * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDataQueueSenderInfo * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDataQueueSenderInfo * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDataQueueSenderInfo * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDataQueueSenderInfo * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UserName )( 
            IcwbxDataQueueSenderInfo * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UserProfileName )( 
            IcwbxDataQueueSenderInfo * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_JobName )( 
            IcwbxDataQueueSenderInfo * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_JobNumber )( 
            IcwbxDataQueueSenderInfo * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [restricted][id] */ HRESULT ( STDMETHODCALLTYPE *Populate )( 
            IcwbxDataQueueSenderInfo * This,
            /* [in] */ long dqDataHandle,
            /* [out] */ long *returnCode);
        
        END_INTERFACE
    } IcwbxDataQueueSenderInfoVtbl;

    interface IcwbxDataQueueSenderInfo
    {
        CONST_VTBL struct IcwbxDataQueueSenderInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDataQueueSenderInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDataQueueSenderInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDataQueueSenderInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDataQueueSenderInfo_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDataQueueSenderInfo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDataQueueSenderInfo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDataQueueSenderInfo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDataQueueSenderInfo_get_UserName(This,pVal)	\
    (This)->lpVtbl -> get_UserName(This,pVal)

#define IcwbxDataQueueSenderInfo_get_UserProfileName(This,pVal)	\
    (This)->lpVtbl -> get_UserProfileName(This,pVal)

#define IcwbxDataQueueSenderInfo_get_JobName(This,pVal)	\
    (This)->lpVtbl -> get_JobName(This,pVal)

#define IcwbxDataQueueSenderInfo_get_JobNumber(This,pVal)	\
    (This)->lpVtbl -> get_JobNumber(This,pVal)

#define IcwbxDataQueueSenderInfo_Populate(This,dqDataHandle,returnCode)	\
    (This)->lpVtbl -> Populate(This,dqDataHandle,returnCode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueueSenderInfo_get_UserName_Proxy( 
    IcwbxDataQueueSenderInfo * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDataQueueSenderInfo_get_UserName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueueSenderInfo_get_UserProfileName_Proxy( 
    IcwbxDataQueueSenderInfo * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDataQueueSenderInfo_get_UserProfileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueueSenderInfo_get_JobName_Proxy( 
    IcwbxDataQueueSenderInfo * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDataQueueSenderInfo_get_JobName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueueSenderInfo_get_JobNumber_Proxy( 
    IcwbxDataQueueSenderInfo * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDataQueueSenderInfo_get_JobNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id] */ HRESULT STDMETHODCALLTYPE IcwbxDataQueueSenderInfo_Populate_Proxy( 
    IcwbxDataQueueSenderInfo * This,
    /* [in] */ long dqDataHandle,
    /* [out] */ long *returnCode);


void __RPC_STUB IcwbxDataQueueSenderInfo_Populate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDataQueueSenderInfo_INTERFACE_DEFINED__ */


#ifndef __IcwbxProgram_INTERFACE_DEFINED__
#define __IcwbxProgram_INTERFACE_DEFINED__

/* interface IcwbxProgram */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxProgram;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("86F9DB1F-15D5-11D2-849C-0004AC94E175")
    IcwbxProgram : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_System( 
            /* [retval][out] */ IcwbxSystem **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_System( 
            /* [in] */ IcwbxSystem *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LibraryName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LibraryName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProgramName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProgramName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Call( 
            /* [defaultvalue][optional][in] */ IcwbxProgramParameters *parameters = 0) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Errors( 
            /* [retval][out] */ IcwbxErrors **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxProgramVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxProgram * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxProgram * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxProgram * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxProgram * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxProgram * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxProgram * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxProgram * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_System )( 
            IcwbxProgram * This,
            /* [retval][out] */ IcwbxSystem **pVal);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_System )( 
            IcwbxProgram * This,
            /* [in] */ IcwbxSystem *newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LibraryName )( 
            IcwbxProgram * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LibraryName )( 
            IcwbxProgram * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProgramName )( 
            IcwbxProgram * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ProgramName )( 
            IcwbxProgram * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Call )( 
            IcwbxProgram * This,
            /* [defaultvalue][optional][in] */ IcwbxProgramParameters *parameters);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Errors )( 
            IcwbxProgram * This,
            /* [retval][out] */ IcwbxErrors **pVal);
        
        END_INTERFACE
    } IcwbxProgramVtbl;

    interface IcwbxProgram
    {
        CONST_VTBL struct IcwbxProgramVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxProgram_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxProgram_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxProgram_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxProgram_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxProgram_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxProgram_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxProgram_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxProgram_get_System(This,pVal)	\
    (This)->lpVtbl -> get_System(This,pVal)

#define IcwbxProgram_putref_System(This,newVal)	\
    (This)->lpVtbl -> putref_System(This,newVal)

#define IcwbxProgram_get_LibraryName(This,pVal)	\
    (This)->lpVtbl -> get_LibraryName(This,pVal)

#define IcwbxProgram_put_LibraryName(This,newVal)	\
    (This)->lpVtbl -> put_LibraryName(This,newVal)

#define IcwbxProgram_get_ProgramName(This,pVal)	\
    (This)->lpVtbl -> get_ProgramName(This,pVal)

#define IcwbxProgram_put_ProgramName(This,newVal)	\
    (This)->lpVtbl -> put_ProgramName(This,newVal)

#define IcwbxProgram_Call(This,parameters)	\
    (This)->lpVtbl -> Call(This,parameters)

#define IcwbxProgram_get_Errors(This,pVal)	\
    (This)->lpVtbl -> get_Errors(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxProgram_get_System_Proxy( 
    IcwbxProgram * This,
    /* [retval][out] */ IcwbxSystem **pVal);


void __RPC_STUB IcwbxProgram_get_System_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IcwbxProgram_putref_System_Proxy( 
    IcwbxProgram * This,
    /* [in] */ IcwbxSystem *newVal);


void __RPC_STUB IcwbxProgram_putref_System_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxProgram_get_LibraryName_Proxy( 
    IcwbxProgram * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxProgram_get_LibraryName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxProgram_put_LibraryName_Proxy( 
    IcwbxProgram * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxProgram_put_LibraryName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxProgram_get_ProgramName_Proxy( 
    IcwbxProgram * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxProgram_get_ProgramName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxProgram_put_ProgramName_Proxy( 
    IcwbxProgram * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxProgram_put_ProgramName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxProgram_Call_Proxy( 
    IcwbxProgram * This,
    /* [defaultvalue][optional][in] */ IcwbxProgramParameters *parameters);


void __RPC_STUB IcwbxProgram_Call_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxProgram_get_Errors_Proxy( 
    IcwbxProgram * This,
    /* [retval][out] */ IcwbxErrors **pVal);


void __RPC_STUB IcwbxProgram_get_Errors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxProgram_INTERFACE_DEFINED__ */


#ifndef __IcwbxProgramParameter_INTERFACE_DEFINED__
#define __IcwbxProgramParameter_INTERFACE_DEFINED__

/* interface IcwbxProgramParameter */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxProgramParameter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("86F9DB21-15D5-11D2-849C-0004AC94E175")
    IcwbxProgramParameter : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ cwbrcParameterTypeEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_Type( 
            /* [in] */ cwbrcParameterTypeEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_Length( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get_Addr( 
            /* [retval][out] */ long *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxProgramParameterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxProgramParameter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxProgramParameter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxProgramParameter * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxProgramParameter * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxProgramParameter * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxProgramParameter * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxProgramParameter * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IcwbxProgramParameter * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IcwbxProgramParameter * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IcwbxProgramParameter * This,
            /* [retval][out] */ cwbrcParameterTypeEnum *pVal);
        
        /* [helpcontext][helpstring][restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Type )( 
            IcwbxProgramParameter * This,
            /* [in] */ cwbrcParameterTypeEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IcwbxProgramParameter * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Length )( 
            IcwbxProgramParameter * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            IcwbxProgramParameter * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            IcwbxProgramParameter * This,
            /* [in] */ VARIANT newVal);
        
        /* [restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Addr )( 
            IcwbxProgramParameter * This,
            /* [retval][out] */ long *pVal);
        
        END_INTERFACE
    } IcwbxProgramParameterVtbl;

    interface IcwbxProgramParameter
    {
        CONST_VTBL struct IcwbxProgramParameterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxProgramParameter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxProgramParameter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxProgramParameter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxProgramParameter_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxProgramParameter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxProgramParameter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxProgramParameter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxProgramParameter_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IcwbxProgramParameter_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IcwbxProgramParameter_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IcwbxProgramParameter_put_Type(This,newVal)	\
    (This)->lpVtbl -> put_Type(This,newVal)

#define IcwbxProgramParameter_get_Length(This,pVal)	\
    (This)->lpVtbl -> get_Length(This,pVal)

#define IcwbxProgramParameter_put_Length(This,newVal)	\
    (This)->lpVtbl -> put_Length(This,newVal)

#define IcwbxProgramParameter_get_Value(This,pVal)	\
    (This)->lpVtbl -> get_Value(This,pVal)

#define IcwbxProgramParameter_put_Value(This,newVal)	\
    (This)->lpVtbl -> put_Value(This,newVal)

#define IcwbxProgramParameter_get_Addr(This,pVal)	\
    (This)->lpVtbl -> get_Addr(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxProgramParameter_get_Name_Proxy( 
    IcwbxProgramParameter * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxProgramParameter_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxProgramParameter_put_Name_Proxy( 
    IcwbxProgramParameter * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxProgramParameter_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxProgramParameter_get_Type_Proxy( 
    IcwbxProgramParameter * This,
    /* [retval][out] */ cwbrcParameterTypeEnum *pVal);


void __RPC_STUB IcwbxProgramParameter_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxProgramParameter_put_Type_Proxy( 
    IcwbxProgramParameter * This,
    /* [in] */ cwbrcParameterTypeEnum newVal);


void __RPC_STUB IcwbxProgramParameter_put_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxProgramParameter_get_Length_Proxy( 
    IcwbxProgramParameter * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxProgramParameter_get_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxProgramParameter_put_Length_Proxy( 
    IcwbxProgramParameter * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxProgramParameter_put_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxProgramParameter_get_Value_Proxy( 
    IcwbxProgramParameter * This,
    /* [retval][out] */ VARIANT *pVal);


void __RPC_STUB IcwbxProgramParameter_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxProgramParameter_put_Value_Proxy( 
    IcwbxProgramParameter * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IcwbxProgramParameter_put_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxProgramParameter_get_Addr_Proxy( 
    IcwbxProgramParameter * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxProgramParameter_get_Addr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxProgramParameter_INTERFACE_DEFINED__ */


#ifndef __IcwbxProgramParameters_INTERFACE_DEFINED__
#define __IcwbxProgramParameters_INTERFACE_DEFINED__

/* interface IcwbxProgramParameters */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxProgramParameters;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FDE7ADB3-1A69-11D2-849C-0004AC94E175")
    IcwbxProgramParameters : public IDispatch
    {
    public:
        virtual /* [restricted][id] */ HRESULT STDMETHODCALLTYPE _NewEnum( 
            /* [retval][out] */ IUnknown **ppvObject) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT index,
            /* [retval][out] */ IcwbxProgramParameter **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Append( 
            /* [in] */ BSTR name,
            /* [in] */ cwbrcParameterTypeEnum Type,
            /* [defaultvalue][optional][in] */ long length,
            /* [retval][out] */ IcwbxProgramParameter **retval) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxProgramParametersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxProgramParameters * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxProgramParameters * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxProgramParameters * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxProgramParameters * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxProgramParameters * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxProgramParameters * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxProgramParameters * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [restricted][id] */ HRESULT ( STDMETHODCALLTYPE *_NewEnum )( 
            IcwbxProgramParameters * This,
            /* [retval][out] */ IUnknown **ppvObject);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IcwbxProgramParameters * This,
            /* [in] */ VARIANT index,
            /* [retval][out] */ IcwbxProgramParameter **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IcwbxProgramParameters * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Append )( 
            IcwbxProgramParameters * This,
            /* [in] */ BSTR name,
            /* [in] */ cwbrcParameterTypeEnum Type,
            /* [defaultvalue][optional][in] */ long length,
            /* [retval][out] */ IcwbxProgramParameter **retval);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IcwbxProgramParameters * This);
        
        END_INTERFACE
    } IcwbxProgramParametersVtbl;

    interface IcwbxProgramParameters
    {
        CONST_VTBL struct IcwbxProgramParametersVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxProgramParameters_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxProgramParameters_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxProgramParameters_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxProgramParameters_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxProgramParameters_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxProgramParameters_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxProgramParameters_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxProgramParameters__NewEnum(This,ppvObject)	\
    (This)->lpVtbl -> _NewEnum(This,ppvObject)

#define IcwbxProgramParameters_get_Item(This,index,pVal)	\
    (This)->lpVtbl -> get_Item(This,index,pVal)

#define IcwbxProgramParameters_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IcwbxProgramParameters_Append(This,name,Type,length,retval)	\
    (This)->lpVtbl -> Append(This,name,Type,length,retval)

#define IcwbxProgramParameters_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [restricted][id] */ HRESULT STDMETHODCALLTYPE IcwbxProgramParameters__NewEnum_Proxy( 
    IcwbxProgramParameters * This,
    /* [retval][out] */ IUnknown **ppvObject);


void __RPC_STUB IcwbxProgramParameters__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxProgramParameters_get_Item_Proxy( 
    IcwbxProgramParameters * This,
    /* [in] */ VARIANT index,
    /* [retval][out] */ IcwbxProgramParameter **pVal);


void __RPC_STUB IcwbxProgramParameters_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxProgramParameters_get_Count_Proxy( 
    IcwbxProgramParameters * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxProgramParameters_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxProgramParameters_Append_Proxy( 
    IcwbxProgramParameters * This,
    /* [in] */ BSTR name,
    /* [in] */ cwbrcParameterTypeEnum Type,
    /* [defaultvalue][optional][in] */ long length,
    /* [retval][out] */ IcwbxProgramParameter **retval);


void __RPC_STUB IcwbxProgramParameters_Append_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxProgramParameters_Clear_Proxy( 
    IcwbxProgramParameters * This);


void __RPC_STUB IcwbxProgramParameters_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxProgramParameters_INTERFACE_DEFINED__ */


#ifndef __IcwbxCommand_INTERFACE_DEFINED__
#define __IcwbxCommand_INTERFACE_DEFINED__

/* interface IcwbxCommand */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxCommand;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("86F9DB26-15D5-11D2-849C-0004AC94E175")
    IcwbxCommand : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_System( 
            /* [retval][out] */ IcwbxSystem **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_System( 
            /* [in] */ IcwbxSystem *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Errors( 
            /* [retval][out] */ IcwbxErrors **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Run( 
            /* [in] */ BSTR commandText) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxCommandVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxCommand * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxCommand * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxCommand * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxCommand * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxCommand * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxCommand * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxCommand * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_System )( 
            IcwbxCommand * This,
            /* [retval][out] */ IcwbxSystem **pVal);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_System )( 
            IcwbxCommand * This,
            /* [in] */ IcwbxSystem *newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Errors )( 
            IcwbxCommand * This,
            /* [retval][out] */ IcwbxErrors **pVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Run )( 
            IcwbxCommand * This,
            /* [in] */ BSTR commandText);
        
        END_INTERFACE
    } IcwbxCommandVtbl;

    interface IcwbxCommand
    {
        CONST_VTBL struct IcwbxCommandVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxCommand_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxCommand_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxCommand_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxCommand_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxCommand_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxCommand_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxCommand_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxCommand_get_System(This,pVal)	\
    (This)->lpVtbl -> get_System(This,pVal)

#define IcwbxCommand_putref_System(This,newVal)	\
    (This)->lpVtbl -> putref_System(This,newVal)

#define IcwbxCommand_get_Errors(This,pVal)	\
    (This)->lpVtbl -> get_Errors(This,pVal)

#define IcwbxCommand_Run(This,commandText)	\
    (This)->lpVtbl -> Run(This,commandText)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxCommand_get_System_Proxy( 
    IcwbxCommand * This,
    /* [retval][out] */ IcwbxSystem **pVal);


void __RPC_STUB IcwbxCommand_get_System_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IcwbxCommand_putref_System_Proxy( 
    IcwbxCommand * This,
    /* [in] */ IcwbxSystem *newVal);


void __RPC_STUB IcwbxCommand_putref_System_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxCommand_get_Errors_Proxy( 
    IcwbxCommand * This,
    /* [retval][out] */ IcwbxErrors **pVal);


void __RPC_STUB IcwbxCommand_get_Errors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxCommand_Run_Proxy( 
    IcwbxCommand * This,
    /* [in] */ BSTR commandText);


void __RPC_STUB IcwbxCommand_Run_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxCommand_INTERFACE_DEFINED__ */


#ifndef __IcwbxPackedConverter_INTERFACE_DEFINED__
#define __IcwbxPackedConverter_INTERFACE_DEFINED__

/* interface IcwbxPackedConverter */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxPackedConverter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("86F9DB2C-15D5-11D2-849C-0004AC94E175")
    IcwbxPackedConverter : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Digits( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Digits( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DecimalPosition( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DecimalPosition( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ToBytes( 
            /* [in] */ BSTR pcData,
            /* [retval][out] */ VARIANT *byteData) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE FromBytes( 
            /* [in] */ VARIANT byteData,
            /* [retval][out] */ BSTR *pcData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxPackedConverterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxPackedConverter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxPackedConverter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxPackedConverter * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxPackedConverter * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxPackedConverter * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxPackedConverter * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxPackedConverter * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IcwbxPackedConverter * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Digits )( 
            IcwbxPackedConverter * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Digits )( 
            IcwbxPackedConverter * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DecimalPosition )( 
            IcwbxPackedConverter * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DecimalPosition )( 
            IcwbxPackedConverter * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ToBytes )( 
            IcwbxPackedConverter * This,
            /* [in] */ BSTR pcData,
            /* [retval][out] */ VARIANT *byteData);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FromBytes )( 
            IcwbxPackedConverter * This,
            /* [in] */ VARIANT byteData,
            /* [retval][out] */ BSTR *pcData);
        
        END_INTERFACE
    } IcwbxPackedConverterVtbl;

    interface IcwbxPackedConverter
    {
        CONST_VTBL struct IcwbxPackedConverterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxPackedConverter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxPackedConverter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxPackedConverter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxPackedConverter_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxPackedConverter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxPackedConverter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxPackedConverter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxPackedConverter_get_Length(This,pVal)	\
    (This)->lpVtbl -> get_Length(This,pVal)

#define IcwbxPackedConverter_get_Digits(This,pVal)	\
    (This)->lpVtbl -> get_Digits(This,pVal)

#define IcwbxPackedConverter_put_Digits(This,newVal)	\
    (This)->lpVtbl -> put_Digits(This,newVal)

#define IcwbxPackedConverter_get_DecimalPosition(This,pVal)	\
    (This)->lpVtbl -> get_DecimalPosition(This,pVal)

#define IcwbxPackedConverter_put_DecimalPosition(This,newVal)	\
    (This)->lpVtbl -> put_DecimalPosition(This,newVal)

#define IcwbxPackedConverter_ToBytes(This,pcData,byteData)	\
    (This)->lpVtbl -> ToBytes(This,pcData,byteData)

#define IcwbxPackedConverter_FromBytes(This,byteData,pcData)	\
    (This)->lpVtbl -> FromBytes(This,byteData,pcData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxPackedConverter_get_Length_Proxy( 
    IcwbxPackedConverter * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxPackedConverter_get_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxPackedConverter_get_Digits_Proxy( 
    IcwbxPackedConverter * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxPackedConverter_get_Digits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxPackedConverter_put_Digits_Proxy( 
    IcwbxPackedConverter * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxPackedConverter_put_Digits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxPackedConverter_get_DecimalPosition_Proxy( 
    IcwbxPackedConverter * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxPackedConverter_get_DecimalPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxPackedConverter_put_DecimalPosition_Proxy( 
    IcwbxPackedConverter * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxPackedConverter_put_DecimalPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxPackedConverter_ToBytes_Proxy( 
    IcwbxPackedConverter * This,
    /* [in] */ BSTR pcData,
    /* [retval][out] */ VARIANT *byteData);


void __RPC_STUB IcwbxPackedConverter_ToBytes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxPackedConverter_FromBytes_Proxy( 
    IcwbxPackedConverter * This,
    /* [in] */ VARIANT byteData,
    /* [retval][out] */ BSTR *pcData);


void __RPC_STUB IcwbxPackedConverter_FromBytes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxPackedConverter_INTERFACE_DEFINED__ */


#ifndef __IcwbxZonedConverter_INTERFACE_DEFINED__
#define __IcwbxZonedConverter_INTERFACE_DEFINED__

/* interface IcwbxZonedConverter */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxZonedConverter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("86F9DB2E-15D5-11D2-849C-0004AC94E175")
    IcwbxZonedConverter : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Digits( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Digits( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DecimalPosition( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DecimalPosition( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ToBytes( 
            /* [in] */ BSTR pcData,
            /* [retval][out] */ VARIANT *byteData) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE FromBytes( 
            /* [in] */ VARIANT byteData,
            /* [retval][out] */ BSTR *pcData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxZonedConverterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxZonedConverter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxZonedConverter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxZonedConverter * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxZonedConverter * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxZonedConverter * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxZonedConverter * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxZonedConverter * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IcwbxZonedConverter * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Digits )( 
            IcwbxZonedConverter * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Digits )( 
            IcwbxZonedConverter * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DecimalPosition )( 
            IcwbxZonedConverter * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DecimalPosition )( 
            IcwbxZonedConverter * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ToBytes )( 
            IcwbxZonedConverter * This,
            /* [in] */ BSTR pcData,
            /* [retval][out] */ VARIANT *byteData);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FromBytes )( 
            IcwbxZonedConverter * This,
            /* [in] */ VARIANT byteData,
            /* [retval][out] */ BSTR *pcData);
        
        END_INTERFACE
    } IcwbxZonedConverterVtbl;

    interface IcwbxZonedConverter
    {
        CONST_VTBL struct IcwbxZonedConverterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxZonedConverter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxZonedConverter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxZonedConverter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxZonedConverter_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxZonedConverter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxZonedConverter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxZonedConverter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxZonedConverter_get_Length(This,pVal)	\
    (This)->lpVtbl -> get_Length(This,pVal)

#define IcwbxZonedConverter_get_Digits(This,pVal)	\
    (This)->lpVtbl -> get_Digits(This,pVal)

#define IcwbxZonedConverter_put_Digits(This,newVal)	\
    (This)->lpVtbl -> put_Digits(This,newVal)

#define IcwbxZonedConverter_get_DecimalPosition(This,pVal)	\
    (This)->lpVtbl -> get_DecimalPosition(This,pVal)

#define IcwbxZonedConverter_put_DecimalPosition(This,newVal)	\
    (This)->lpVtbl -> put_DecimalPosition(This,newVal)

#define IcwbxZonedConverter_ToBytes(This,pcData,byteData)	\
    (This)->lpVtbl -> ToBytes(This,pcData,byteData)

#define IcwbxZonedConverter_FromBytes(This,byteData,pcData)	\
    (This)->lpVtbl -> FromBytes(This,byteData,pcData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxZonedConverter_get_Length_Proxy( 
    IcwbxZonedConverter * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxZonedConverter_get_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxZonedConverter_get_Digits_Proxy( 
    IcwbxZonedConverter * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxZonedConverter_get_Digits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxZonedConverter_put_Digits_Proxy( 
    IcwbxZonedConverter * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxZonedConverter_put_Digits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxZonedConverter_get_DecimalPosition_Proxy( 
    IcwbxZonedConverter * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxZonedConverter_get_DecimalPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxZonedConverter_put_DecimalPosition_Proxy( 
    IcwbxZonedConverter * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxZonedConverter_put_DecimalPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxZonedConverter_ToBytes_Proxy( 
    IcwbxZonedConverter * This,
    /* [in] */ BSTR pcData,
    /* [retval][out] */ VARIANT *byteData);


void __RPC_STUB IcwbxZonedConverter_ToBytes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxZonedConverter_FromBytes_Proxy( 
    IcwbxZonedConverter * This,
    /* [in] */ VARIANT byteData,
    /* [retval][out] */ BSTR *pcData);


void __RPC_STUB IcwbxZonedConverter_FromBytes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxZonedConverter_INTERFACE_DEFINED__ */


#ifndef __IcwbxShortConverter_INTERFACE_DEFINED__
#define __IcwbxShortConverter_INTERFACE_DEFINED__

/* interface IcwbxShortConverter */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxShortConverter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3DEF9936-1673-11D2-849C-0004AC94E175")
    IcwbxShortConverter : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AS400Format( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AS400Format( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ToBytes( 
            /* [in] */ short pcData,
            /* [retval][out] */ VARIANT *byteData) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE FromBytes( 
            /* [in] */ VARIANT byteData,
            /* [retval][out] */ short *pcData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxShortConverterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxShortConverter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxShortConverter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxShortConverter * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxShortConverter * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxShortConverter * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxShortConverter * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxShortConverter * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IcwbxShortConverter * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AS400Format )( 
            IcwbxShortConverter * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AS400Format )( 
            IcwbxShortConverter * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ToBytes )( 
            IcwbxShortConverter * This,
            /* [in] */ short pcData,
            /* [retval][out] */ VARIANT *byteData);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FromBytes )( 
            IcwbxShortConverter * This,
            /* [in] */ VARIANT byteData,
            /* [retval][out] */ short *pcData);
        
        END_INTERFACE
    } IcwbxShortConverterVtbl;

    interface IcwbxShortConverter
    {
        CONST_VTBL struct IcwbxShortConverterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxShortConverter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxShortConverter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxShortConverter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxShortConverter_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxShortConverter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxShortConverter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxShortConverter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxShortConverter_get_Length(This,pVal)	\
    (This)->lpVtbl -> get_Length(This,pVal)

#define IcwbxShortConverter_get_AS400Format(This,pVal)	\
    (This)->lpVtbl -> get_AS400Format(This,pVal)

#define IcwbxShortConverter_put_AS400Format(This,newVal)	\
    (This)->lpVtbl -> put_AS400Format(This,newVal)

#define IcwbxShortConverter_ToBytes(This,pcData,byteData)	\
    (This)->lpVtbl -> ToBytes(This,pcData,byteData)

#define IcwbxShortConverter_FromBytes(This,byteData,pcData)	\
    (This)->lpVtbl -> FromBytes(This,byteData,pcData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxShortConverter_get_Length_Proxy( 
    IcwbxShortConverter * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxShortConverter_get_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxShortConverter_get_AS400Format_Proxy( 
    IcwbxShortConverter * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxShortConverter_get_AS400Format_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxShortConverter_put_AS400Format_Proxy( 
    IcwbxShortConverter * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxShortConverter_put_AS400Format_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxShortConverter_ToBytes_Proxy( 
    IcwbxShortConverter * This,
    /* [in] */ short pcData,
    /* [retval][out] */ VARIANT *byteData);


void __RPC_STUB IcwbxShortConverter_ToBytes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxShortConverter_FromBytes_Proxy( 
    IcwbxShortConverter * This,
    /* [in] */ VARIANT byteData,
    /* [retval][out] */ short *pcData);


void __RPC_STUB IcwbxShortConverter_FromBytes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxShortConverter_INTERFACE_DEFINED__ */


#ifndef __IcwbxLongConverter_INTERFACE_DEFINED__
#define __IcwbxLongConverter_INTERFACE_DEFINED__

/* interface IcwbxLongConverter */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxLongConverter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3DEF9938-1673-11D2-849C-0004AC94E175")
    IcwbxLongConverter : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AS400Format( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AS400Format( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ToBytes( 
            /* [in] */ long pcData,
            /* [retval][out] */ VARIANT *byteData) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE FromBytes( 
            /* [in] */ VARIANT byteData,
            /* [retval][out] */ long *pcData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxLongConverterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxLongConverter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxLongConverter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxLongConverter * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxLongConverter * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxLongConverter * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxLongConverter * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxLongConverter * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IcwbxLongConverter * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AS400Format )( 
            IcwbxLongConverter * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AS400Format )( 
            IcwbxLongConverter * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ToBytes )( 
            IcwbxLongConverter * This,
            /* [in] */ long pcData,
            /* [retval][out] */ VARIANT *byteData);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FromBytes )( 
            IcwbxLongConverter * This,
            /* [in] */ VARIANT byteData,
            /* [retval][out] */ long *pcData);
        
        END_INTERFACE
    } IcwbxLongConverterVtbl;

    interface IcwbxLongConverter
    {
        CONST_VTBL struct IcwbxLongConverterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxLongConverter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxLongConverter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxLongConverter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxLongConverter_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxLongConverter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxLongConverter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxLongConverter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxLongConverter_get_Length(This,pVal)	\
    (This)->lpVtbl -> get_Length(This,pVal)

#define IcwbxLongConverter_get_AS400Format(This,pVal)	\
    (This)->lpVtbl -> get_AS400Format(This,pVal)

#define IcwbxLongConverter_put_AS400Format(This,newVal)	\
    (This)->lpVtbl -> put_AS400Format(This,newVal)

#define IcwbxLongConverter_ToBytes(This,pcData,byteData)	\
    (This)->lpVtbl -> ToBytes(This,pcData,byteData)

#define IcwbxLongConverter_FromBytes(This,byteData,pcData)	\
    (This)->lpVtbl -> FromBytes(This,byteData,pcData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxLongConverter_get_Length_Proxy( 
    IcwbxLongConverter * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxLongConverter_get_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxLongConverter_get_AS400Format_Proxy( 
    IcwbxLongConverter * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxLongConverter_get_AS400Format_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxLongConverter_put_AS400Format_Proxy( 
    IcwbxLongConverter * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxLongConverter_put_AS400Format_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxLongConverter_ToBytes_Proxy( 
    IcwbxLongConverter * This,
    /* [in] */ long pcData,
    /* [retval][out] */ VARIANT *byteData);


void __RPC_STUB IcwbxLongConverter_ToBytes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxLongConverter_FromBytes_Proxy( 
    IcwbxLongConverter * This,
    /* [in] */ VARIANT byteData,
    /* [retval][out] */ long *pcData);


void __RPC_STUB IcwbxLongConverter_FromBytes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxLongConverter_INTERFACE_DEFINED__ */


#ifndef __IcwbxDoubleConverter_INTERFACE_DEFINED__
#define __IcwbxDoubleConverter_INTERFACE_DEFINED__

/* interface IcwbxDoubleConverter */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDoubleConverter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3DEF993B-1673-11D2-849C-0004AC94E175")
    IcwbxDoubleConverter : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AS400Format( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AS400Format( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ToBytes( 
            /* [in] */ double pcData,
            /* [retval][out] */ VARIANT *byteData) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE FromBytes( 
            /* [in] */ VARIANT byteData,
            /* [retval][out] */ double *pcData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDoubleConverterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDoubleConverter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDoubleConverter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDoubleConverter * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDoubleConverter * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDoubleConverter * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDoubleConverter * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDoubleConverter * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IcwbxDoubleConverter * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AS400Format )( 
            IcwbxDoubleConverter * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AS400Format )( 
            IcwbxDoubleConverter * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ToBytes )( 
            IcwbxDoubleConverter * This,
            /* [in] */ double pcData,
            /* [retval][out] */ VARIANT *byteData);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FromBytes )( 
            IcwbxDoubleConverter * This,
            /* [in] */ VARIANT byteData,
            /* [retval][out] */ double *pcData);
        
        END_INTERFACE
    } IcwbxDoubleConverterVtbl;

    interface IcwbxDoubleConverter
    {
        CONST_VTBL struct IcwbxDoubleConverterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDoubleConverter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDoubleConverter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDoubleConverter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDoubleConverter_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDoubleConverter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDoubleConverter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDoubleConverter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDoubleConverter_get_Length(This,pVal)	\
    (This)->lpVtbl -> get_Length(This,pVal)

#define IcwbxDoubleConverter_get_AS400Format(This,pVal)	\
    (This)->lpVtbl -> get_AS400Format(This,pVal)

#define IcwbxDoubleConverter_put_AS400Format(This,newVal)	\
    (This)->lpVtbl -> put_AS400Format(This,newVal)

#define IcwbxDoubleConverter_ToBytes(This,pcData,byteData)	\
    (This)->lpVtbl -> ToBytes(This,pcData,byteData)

#define IcwbxDoubleConverter_FromBytes(This,byteData,pcData)	\
    (This)->lpVtbl -> FromBytes(This,byteData,pcData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDoubleConverter_get_Length_Proxy( 
    IcwbxDoubleConverter * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxDoubleConverter_get_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDoubleConverter_get_AS400Format_Proxy( 
    IcwbxDoubleConverter * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDoubleConverter_get_AS400Format_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDoubleConverter_put_AS400Format_Proxy( 
    IcwbxDoubleConverter * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDoubleConverter_put_AS400Format_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDoubleConverter_ToBytes_Proxy( 
    IcwbxDoubleConverter * This,
    /* [in] */ double pcData,
    /* [retval][out] */ VARIANT *byteData);


void __RPC_STUB IcwbxDoubleConverter_ToBytes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDoubleConverter_FromBytes_Proxy( 
    IcwbxDoubleConverter * This,
    /* [in] */ VARIANT byteData,
    /* [retval][out] */ double *pcData);


void __RPC_STUB IcwbxDoubleConverter_FromBytes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDoubleConverter_INTERFACE_DEFINED__ */


#ifndef __IcwbxFloatConverter_INTERFACE_DEFINED__
#define __IcwbxFloatConverter_INTERFACE_DEFINED__

/* interface IcwbxFloatConverter */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxFloatConverter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3DEF993D-1673-11D2-849C-0004AC94E175")
    IcwbxFloatConverter : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AS400Format( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AS400Format( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ToBytes( 
            /* [in] */ float pcData,
            /* [retval][out] */ VARIANT *byteData) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE FromBytes( 
            /* [in] */ VARIANT byteData,
            /* [retval][out] */ float *pcData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxFloatConverterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxFloatConverter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxFloatConverter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxFloatConverter * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxFloatConverter * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxFloatConverter * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxFloatConverter * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxFloatConverter * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IcwbxFloatConverter * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AS400Format )( 
            IcwbxFloatConverter * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AS400Format )( 
            IcwbxFloatConverter * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ToBytes )( 
            IcwbxFloatConverter * This,
            /* [in] */ float pcData,
            /* [retval][out] */ VARIANT *byteData);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FromBytes )( 
            IcwbxFloatConverter * This,
            /* [in] */ VARIANT byteData,
            /* [retval][out] */ float *pcData);
        
        END_INTERFACE
    } IcwbxFloatConverterVtbl;

    interface IcwbxFloatConverter
    {
        CONST_VTBL struct IcwbxFloatConverterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxFloatConverter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxFloatConverter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxFloatConverter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxFloatConverter_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxFloatConverter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxFloatConverter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxFloatConverter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxFloatConverter_get_Length(This,pVal)	\
    (This)->lpVtbl -> get_Length(This,pVal)

#define IcwbxFloatConverter_get_AS400Format(This,pVal)	\
    (This)->lpVtbl -> get_AS400Format(This,pVal)

#define IcwbxFloatConverter_put_AS400Format(This,newVal)	\
    (This)->lpVtbl -> put_AS400Format(This,newVal)

#define IcwbxFloatConverter_ToBytes(This,pcData,byteData)	\
    (This)->lpVtbl -> ToBytes(This,pcData,byteData)

#define IcwbxFloatConverter_FromBytes(This,byteData,pcData)	\
    (This)->lpVtbl -> FromBytes(This,byteData,pcData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxFloatConverter_get_Length_Proxy( 
    IcwbxFloatConverter * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxFloatConverter_get_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxFloatConverter_get_AS400Format_Proxy( 
    IcwbxFloatConverter * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxFloatConverter_get_AS400Format_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxFloatConverter_put_AS400Format_Proxy( 
    IcwbxFloatConverter * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxFloatConverter_put_AS400Format_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxFloatConverter_ToBytes_Proxy( 
    IcwbxFloatConverter * This,
    /* [in] */ float pcData,
    /* [retval][out] */ VARIANT *byteData);


void __RPC_STUB IcwbxFloatConverter_ToBytes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxFloatConverter_FromBytes_Proxy( 
    IcwbxFloatConverter * This,
    /* [in] */ VARIANT byteData,
    /* [retval][out] */ float *pcData);


void __RPC_STUB IcwbxFloatConverter_FromBytes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxFloatConverter_INTERFACE_DEFINED__ */


#ifndef __IcwbxStringConverter_INTERFACE_DEFINED__
#define __IcwbxStringConverter_INTERFACE_DEFINED__

/* interface IcwbxStringConverter */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxStringConverter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3DEF9940-1673-11D2-849C-0004AC94E175")
    IcwbxStringConverter : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Length( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CodePage( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CodePage( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Strip( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Strip( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Errors( 
            /* [retval][out] */ IcwbxErrors **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ToBytes( 
            /* [in] */ BSTR pcData,
            /* [retval][out] */ VARIANT *byteData) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE FromBytes( 
            /* [in] */ VARIANT byteData,
            /* [retval][out] */ BSTR *pcData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxStringConverterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxStringConverter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxStringConverter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxStringConverter * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxStringConverter * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxStringConverter * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxStringConverter * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxStringConverter * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IcwbxStringConverter * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Length )( 
            IcwbxStringConverter * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CodePage )( 
            IcwbxStringConverter * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CodePage )( 
            IcwbxStringConverter * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Strip )( 
            IcwbxStringConverter * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Strip )( 
            IcwbxStringConverter * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Errors )( 
            IcwbxStringConverter * This,
            /* [retval][out] */ IcwbxErrors **pVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ToBytes )( 
            IcwbxStringConverter * This,
            /* [in] */ BSTR pcData,
            /* [retval][out] */ VARIANT *byteData);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FromBytes )( 
            IcwbxStringConverter * This,
            /* [in] */ VARIANT byteData,
            /* [retval][out] */ BSTR *pcData);
        
        END_INTERFACE
    } IcwbxStringConverterVtbl;

    interface IcwbxStringConverter
    {
        CONST_VTBL struct IcwbxStringConverterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxStringConverter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxStringConverter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxStringConverter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxStringConverter_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxStringConverter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxStringConverter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxStringConverter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxStringConverter_get_Length(This,pVal)	\
    (This)->lpVtbl -> get_Length(This,pVal)

#define IcwbxStringConverter_put_Length(This,newVal)	\
    (This)->lpVtbl -> put_Length(This,newVal)

#define IcwbxStringConverter_get_CodePage(This,pVal)	\
    (This)->lpVtbl -> get_CodePage(This,pVal)

#define IcwbxStringConverter_put_CodePage(This,newVal)	\
    (This)->lpVtbl -> put_CodePage(This,newVal)

#define IcwbxStringConverter_get_Strip(This,pVal)	\
    (This)->lpVtbl -> get_Strip(This,pVal)

#define IcwbxStringConverter_put_Strip(This,newVal)	\
    (This)->lpVtbl -> put_Strip(This,newVal)

#define IcwbxStringConverter_get_Errors(This,pVal)	\
    (This)->lpVtbl -> get_Errors(This,pVal)

#define IcwbxStringConverter_ToBytes(This,pcData,byteData)	\
    (This)->lpVtbl -> ToBytes(This,pcData,byteData)

#define IcwbxStringConverter_FromBytes(This,byteData,pcData)	\
    (This)->lpVtbl -> FromBytes(This,byteData,pcData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxStringConverter_get_Length_Proxy( 
    IcwbxStringConverter * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxStringConverter_get_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxStringConverter_put_Length_Proxy( 
    IcwbxStringConverter * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxStringConverter_put_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxStringConverter_get_CodePage_Proxy( 
    IcwbxStringConverter * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxStringConverter_get_CodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxStringConverter_put_CodePage_Proxy( 
    IcwbxStringConverter * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxStringConverter_put_CodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxStringConverter_get_Strip_Proxy( 
    IcwbxStringConverter * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxStringConverter_get_Strip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxStringConverter_put_Strip_Proxy( 
    IcwbxStringConverter * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxStringConverter_put_Strip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxStringConverter_get_Errors_Proxy( 
    IcwbxStringConverter * This,
    /* [retval][out] */ IcwbxErrors **pVal);


void __RPC_STUB IcwbxStringConverter_get_Errors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxStringConverter_ToBytes_Proxy( 
    IcwbxStringConverter * This,
    /* [in] */ BSTR pcData,
    /* [retval][out] */ VARIANT *byteData);


void __RPC_STUB IcwbxStringConverter_ToBytes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxStringConverter_FromBytes_Proxy( 
    IcwbxStringConverter * This,
    /* [in] */ VARIANT byteData,
    /* [retval][out] */ BSTR *pcData);


void __RPC_STUB IcwbxStringConverter_FromBytes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxStringConverter_INTERFACE_DEFINED__ */


#ifndef __IcwbxCodePageConverter_INTERFACE_DEFINED__
#define __IcwbxCodePageConverter_INTERFACE_DEFINED__

/* interface IcwbxCodePageConverter */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxCodePageConverter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3DEF9944-1673-11D2-849C-0004AC94E175")
    IcwbxCodePageConverter : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SourceCodePage( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SourceCodePage( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TargetCodePage( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TargetCodePage( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DataContainsSOSI( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DataContainsSOSI( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Pad( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Pad( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OEMCodePage( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ANSICodePage( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Length( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Convert( 
            /* [in] */ VARIANT source,
            /* [out] */ VARIANT *target,
            /* [optional][out] */ VARIANT *convertedLength,
            /* [optional][out] */ VARIANT *numberOfErrors,
            /* [optional][out] */ VARIANT *firstErrorIndex) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Errors( 
            /* [retval][out] */ IcwbxErrors **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxCodePageConverterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxCodePageConverter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxCodePageConverter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxCodePageConverter * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxCodePageConverter * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxCodePageConverter * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxCodePageConverter * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxCodePageConverter * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SourceCodePage )( 
            IcwbxCodePageConverter * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SourceCodePage )( 
            IcwbxCodePageConverter * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TargetCodePage )( 
            IcwbxCodePageConverter * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TargetCodePage )( 
            IcwbxCodePageConverter * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DataContainsSOSI )( 
            IcwbxCodePageConverter * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DataContainsSOSI )( 
            IcwbxCodePageConverter * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Pad )( 
            IcwbxCodePageConverter * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Pad )( 
            IcwbxCodePageConverter * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OEMCodePage )( 
            IcwbxCodePageConverter * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ANSICodePage )( 
            IcwbxCodePageConverter * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Length )( 
            IcwbxCodePageConverter * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IcwbxCodePageConverter * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Convert )( 
            IcwbxCodePageConverter * This,
            /* [in] */ VARIANT source,
            /* [out] */ VARIANT *target,
            /* [optional][out] */ VARIANT *convertedLength,
            /* [optional][out] */ VARIANT *numberOfErrors,
            /* [optional][out] */ VARIANT *firstErrorIndex);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Errors )( 
            IcwbxCodePageConverter * This,
            /* [retval][out] */ IcwbxErrors **pVal);
        
        END_INTERFACE
    } IcwbxCodePageConverterVtbl;

    interface IcwbxCodePageConverter
    {
        CONST_VTBL struct IcwbxCodePageConverterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxCodePageConverter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxCodePageConverter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxCodePageConverter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxCodePageConverter_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxCodePageConverter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxCodePageConverter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxCodePageConverter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxCodePageConverter_get_SourceCodePage(This,pVal)	\
    (This)->lpVtbl -> get_SourceCodePage(This,pVal)

#define IcwbxCodePageConverter_put_SourceCodePage(This,newVal)	\
    (This)->lpVtbl -> put_SourceCodePage(This,newVal)

#define IcwbxCodePageConverter_get_TargetCodePage(This,pVal)	\
    (This)->lpVtbl -> get_TargetCodePage(This,pVal)

#define IcwbxCodePageConverter_put_TargetCodePage(This,newVal)	\
    (This)->lpVtbl -> put_TargetCodePage(This,newVal)

#define IcwbxCodePageConverter_get_DataContainsSOSI(This,pVal)	\
    (This)->lpVtbl -> get_DataContainsSOSI(This,pVal)

#define IcwbxCodePageConverter_put_DataContainsSOSI(This,newVal)	\
    (This)->lpVtbl -> put_DataContainsSOSI(This,newVal)

#define IcwbxCodePageConverter_get_Pad(This,pVal)	\
    (This)->lpVtbl -> get_Pad(This,pVal)

#define IcwbxCodePageConverter_put_Pad(This,newVal)	\
    (This)->lpVtbl -> put_Pad(This,newVal)

#define IcwbxCodePageConverter_get_OEMCodePage(This,pVal)	\
    (This)->lpVtbl -> get_OEMCodePage(This,pVal)

#define IcwbxCodePageConverter_get_ANSICodePage(This,pVal)	\
    (This)->lpVtbl -> get_ANSICodePage(This,pVal)

#define IcwbxCodePageConverter_put_Length(This,newVal)	\
    (This)->lpVtbl -> put_Length(This,newVal)

#define IcwbxCodePageConverter_get_Length(This,pVal)	\
    (This)->lpVtbl -> get_Length(This,pVal)

#define IcwbxCodePageConverter_Convert(This,source,target,convertedLength,numberOfErrors,firstErrorIndex)	\
    (This)->lpVtbl -> Convert(This,source,target,convertedLength,numberOfErrors,firstErrorIndex)

#define IcwbxCodePageConverter_get_Errors(This,pVal)	\
    (This)->lpVtbl -> get_Errors(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxCodePageConverter_get_SourceCodePage_Proxy( 
    IcwbxCodePageConverter * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxCodePageConverter_get_SourceCodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxCodePageConverter_put_SourceCodePage_Proxy( 
    IcwbxCodePageConverter * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxCodePageConverter_put_SourceCodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxCodePageConverter_get_TargetCodePage_Proxy( 
    IcwbxCodePageConverter * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxCodePageConverter_get_TargetCodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxCodePageConverter_put_TargetCodePage_Proxy( 
    IcwbxCodePageConverter * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxCodePageConverter_put_TargetCodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxCodePageConverter_get_DataContainsSOSI_Proxy( 
    IcwbxCodePageConverter * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxCodePageConverter_get_DataContainsSOSI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxCodePageConverter_put_DataContainsSOSI_Proxy( 
    IcwbxCodePageConverter * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxCodePageConverter_put_DataContainsSOSI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxCodePageConverter_get_Pad_Proxy( 
    IcwbxCodePageConverter * This,
    /* [retval][out] */ VARIANT *pVal);


void __RPC_STUB IcwbxCodePageConverter_get_Pad_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxCodePageConverter_put_Pad_Proxy( 
    IcwbxCodePageConverter * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IcwbxCodePageConverter_put_Pad_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxCodePageConverter_get_OEMCodePage_Proxy( 
    IcwbxCodePageConverter * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxCodePageConverter_get_OEMCodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxCodePageConverter_get_ANSICodePage_Proxy( 
    IcwbxCodePageConverter * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxCodePageConverter_get_ANSICodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxCodePageConverter_put_Length_Proxy( 
    IcwbxCodePageConverter * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxCodePageConverter_put_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxCodePageConverter_get_Length_Proxy( 
    IcwbxCodePageConverter * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxCodePageConverter_get_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxCodePageConverter_Convert_Proxy( 
    IcwbxCodePageConverter * This,
    /* [in] */ VARIANT source,
    /* [out] */ VARIANT *target,
    /* [optional][out] */ VARIANT *convertedLength,
    /* [optional][out] */ VARIANT *numberOfErrors,
    /* [optional][out] */ VARIANT *firstErrorIndex);


void __RPC_STUB IcwbxCodePageConverter_Convert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxCodePageConverter_get_Errors_Proxy( 
    IcwbxCodePageConverter * This,
    /* [retval][out] */ IcwbxErrors **pVal);


void __RPC_STUB IcwbxCodePageConverter_get_Errors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxCodePageConverter_INTERFACE_DEFINED__ */


#ifndef __IcwbxStructure_INTERFACE_DEFINED__
#define __IcwbxStructure_INTERFACE_DEFINED__

/* interface IcwbxStructure */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxStructure;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3DEF9934-1673-11D2-849C-0004AC94E175")
    IcwbxStructure : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Fields( 
            /* [retval][out] */ IcwbxStructureFields **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Bytes( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Bytes( 
            /* [in] */ VARIANT newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxStructureVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxStructure * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxStructure * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxStructure * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxStructure * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxStructure * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxStructure * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxStructure * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Fields )( 
            IcwbxStructure * This,
            /* [retval][out] */ IcwbxStructureFields **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IcwbxStructure * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Bytes )( 
            IcwbxStructure * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Bytes )( 
            IcwbxStructure * This,
            /* [in] */ VARIANT newVal);
        
        END_INTERFACE
    } IcwbxStructureVtbl;

    interface IcwbxStructure
    {
        CONST_VTBL struct IcwbxStructureVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxStructure_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxStructure_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxStructure_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxStructure_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxStructure_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxStructure_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxStructure_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxStructure_get_Fields(This,pVal)	\
    (This)->lpVtbl -> get_Fields(This,pVal)

#define IcwbxStructure_get_Length(This,pVal)	\
    (This)->lpVtbl -> get_Length(This,pVal)

#define IcwbxStructure_get_Bytes(This,pVal)	\
    (This)->lpVtbl -> get_Bytes(This,pVal)

#define IcwbxStructure_put_Bytes(This,newVal)	\
    (This)->lpVtbl -> put_Bytes(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxStructure_get_Fields_Proxy( 
    IcwbxStructure * This,
    /* [retval][out] */ IcwbxStructureFields **pVal);


void __RPC_STUB IcwbxStructure_get_Fields_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxStructure_get_Length_Proxy( 
    IcwbxStructure * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxStructure_get_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxStructure_get_Bytes_Proxy( 
    IcwbxStructure * This,
    /* [retval][out] */ VARIANT *pVal);


void __RPC_STUB IcwbxStructure_get_Bytes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxStructure_put_Bytes_Proxy( 
    IcwbxStructure * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IcwbxStructure_put_Bytes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxStructure_INTERFACE_DEFINED__ */


#ifndef __IcwbxBinaryData_INTERFACE_DEFINED__
#define __IcwbxBinaryData_INTERFACE_DEFINED__

/* interface IcwbxBinaryData */
/* [object][oleautomation][nonextensible][dual][hidden][restricted][uuid] */ 


EXTERN_C const IID IID_IcwbxBinaryData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1D60C9E1-3644-11D4-92E2-002035AE9B5D")
    IcwbxBinaryData : public IDispatch
    {
    public:
        virtual /* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get_Bytes( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_Bytes( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [restricted][id] */ HRESULT STDMETHODCALLTYPE Read( 
            /* [in] */ long index,
            /* [in] */ long length,
            /* [out] */ unsigned char *bytes) = 0;
        
        virtual /* [restricted][id] */ HRESULT STDMETHODCALLTYPE Write( 
            /* [in] */ long index,
            /* [in] */ long length,
            /* [in] */ unsigned char *bytes) = 0;
        
        virtual /* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [restricted][id] */ HRESULT STDMETHODCALLTYPE IncrementLength( 
            /* [in] */ long increment) = 0;
        
        virtual /* [restricted][id] */ HRESULT STDMETHODCALLTYPE ClearLength( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxBinaryDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxBinaryData * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxBinaryData * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxBinaryData * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxBinaryData * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxBinaryData * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxBinaryData * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxBinaryData * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Bytes )( 
            IcwbxBinaryData * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Bytes )( 
            IcwbxBinaryData * This,
            /* [in] */ VARIANT newVal);
        
        /* [restricted][id] */ HRESULT ( STDMETHODCALLTYPE *Read )( 
            IcwbxBinaryData * This,
            /* [in] */ long index,
            /* [in] */ long length,
            /* [out] */ unsigned char *bytes);
        
        /* [restricted][id] */ HRESULT ( STDMETHODCALLTYPE *Write )( 
            IcwbxBinaryData * This,
            /* [in] */ long index,
            /* [in] */ long length,
            /* [in] */ unsigned char *bytes);
        
        /* [restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IcwbxBinaryData * This,
            /* [retval][out] */ long *pVal);
        
        /* [restricted][id] */ HRESULT ( STDMETHODCALLTYPE *IncrementLength )( 
            IcwbxBinaryData * This,
            /* [in] */ long increment);
        
        /* [restricted][id] */ HRESULT ( STDMETHODCALLTYPE *ClearLength )( 
            IcwbxBinaryData * This);
        
        END_INTERFACE
    } IcwbxBinaryDataVtbl;

    interface IcwbxBinaryData
    {
        CONST_VTBL struct IcwbxBinaryDataVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxBinaryData_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxBinaryData_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxBinaryData_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxBinaryData_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxBinaryData_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxBinaryData_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxBinaryData_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxBinaryData_get_Bytes(This,pVal)	\
    (This)->lpVtbl -> get_Bytes(This,pVal)

#define IcwbxBinaryData_put_Bytes(This,newVal)	\
    (This)->lpVtbl -> put_Bytes(This,newVal)

#define IcwbxBinaryData_Read(This,index,length,bytes)	\
    (This)->lpVtbl -> Read(This,index,length,bytes)

#define IcwbxBinaryData_Write(This,index,length,bytes)	\
    (This)->lpVtbl -> Write(This,index,length,bytes)

#define IcwbxBinaryData_get_Length(This,pVal)	\
    (This)->lpVtbl -> get_Length(This,pVal)

#define IcwbxBinaryData_IncrementLength(This,increment)	\
    (This)->lpVtbl -> IncrementLength(This,increment)

#define IcwbxBinaryData_ClearLength(This)	\
    (This)->lpVtbl -> ClearLength(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxBinaryData_get_Bytes_Proxy( 
    IcwbxBinaryData * This,
    /* [retval][out] */ VARIANT *pVal);


void __RPC_STUB IcwbxBinaryData_get_Bytes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxBinaryData_put_Bytes_Proxy( 
    IcwbxBinaryData * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IcwbxBinaryData_put_Bytes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id] */ HRESULT STDMETHODCALLTYPE IcwbxBinaryData_Read_Proxy( 
    IcwbxBinaryData * This,
    /* [in] */ long index,
    /* [in] */ long length,
    /* [out] */ unsigned char *bytes);


void __RPC_STUB IcwbxBinaryData_Read_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id] */ HRESULT STDMETHODCALLTYPE IcwbxBinaryData_Write_Proxy( 
    IcwbxBinaryData * This,
    /* [in] */ long index,
    /* [in] */ long length,
    /* [in] */ unsigned char *bytes);


void __RPC_STUB IcwbxBinaryData_Write_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxBinaryData_get_Length_Proxy( 
    IcwbxBinaryData * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxBinaryData_get_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id] */ HRESULT STDMETHODCALLTYPE IcwbxBinaryData_IncrementLength_Proxy( 
    IcwbxBinaryData * This,
    /* [in] */ long increment);


void __RPC_STUB IcwbxBinaryData_IncrementLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id] */ HRESULT STDMETHODCALLTYPE IcwbxBinaryData_ClearLength_Proxy( 
    IcwbxBinaryData * This);


void __RPC_STUB IcwbxBinaryData_ClearLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxBinaryData_INTERFACE_DEFINED__ */


#ifndef __IcwbxStructureField_INTERFACE_DEFINED__
#define __IcwbxStructureField_INTERFACE_DEFINED__

/* interface IcwbxStructureField */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxStructureField;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3DEF9948-1673-11D2-849C-0004AC94E175")
    IcwbxStructureField : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_Length( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_Offset( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [restricted][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_BinaryData( 
            /* [in] */ IcwbxBinaryData *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxStructureFieldVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxStructureField * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxStructureField * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxStructureField * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxStructureField * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxStructureField * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxStructureField * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxStructureField * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            IcwbxStructureField * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            IcwbxStructureField * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IcwbxStructureField * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IcwbxStructureField * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IcwbxStructureField * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Length )( 
            IcwbxStructureField * This,
            /* [in] */ long newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Offset )( 
            IcwbxStructureField * This,
            /* [in] */ long newVal);
        
        /* [restricted][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_BinaryData )( 
            IcwbxStructureField * This,
            /* [in] */ IcwbxBinaryData *newVal);
        
        END_INTERFACE
    } IcwbxStructureFieldVtbl;

    interface IcwbxStructureField
    {
        CONST_VTBL struct IcwbxStructureFieldVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxStructureField_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxStructureField_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxStructureField_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxStructureField_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxStructureField_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxStructureField_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxStructureField_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxStructureField_get_Value(This,pVal)	\
    (This)->lpVtbl -> get_Value(This,pVal)

#define IcwbxStructureField_put_Value(This,newVal)	\
    (This)->lpVtbl -> put_Value(This,newVal)

#define IcwbxStructureField_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IcwbxStructureField_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IcwbxStructureField_get_Length(This,pVal)	\
    (This)->lpVtbl -> get_Length(This,pVal)

#define IcwbxStructureField_put_Length(This,newVal)	\
    (This)->lpVtbl -> put_Length(This,newVal)

#define IcwbxStructureField_put_Offset(This,newVal)	\
    (This)->lpVtbl -> put_Offset(This,newVal)

#define IcwbxStructureField_putref_BinaryData(This,newVal)	\
    (This)->lpVtbl -> putref_BinaryData(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxStructureField_get_Value_Proxy( 
    IcwbxStructureField * This,
    /* [retval][out] */ VARIANT *pVal);


void __RPC_STUB IcwbxStructureField_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxStructureField_put_Value_Proxy( 
    IcwbxStructureField * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IcwbxStructureField_put_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxStructureField_get_Name_Proxy( 
    IcwbxStructureField * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxStructureField_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxStructureField_put_Name_Proxy( 
    IcwbxStructureField * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxStructureField_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxStructureField_get_Length_Proxy( 
    IcwbxStructureField * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxStructureField_get_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxStructureField_put_Length_Proxy( 
    IcwbxStructureField * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxStructureField_put_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxStructureField_put_Offset_Proxy( 
    IcwbxStructureField * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxStructureField_put_Offset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propputref] */ HRESULT STDMETHODCALLTYPE IcwbxStructureField_putref_BinaryData_Proxy( 
    IcwbxStructureField * This,
    /* [in] */ IcwbxBinaryData *newVal);


void __RPC_STUB IcwbxStructureField_putref_BinaryData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxStructureField_INTERFACE_DEFINED__ */


#ifndef __IcwbxStructureFields_INTERFACE_DEFINED__
#define __IcwbxStructureFields_INTERFACE_DEFINED__

/* interface IcwbxStructureFields */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxStructureFields;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FDE7ADB9-1A69-11D2-849C-0004AC94E175")
    IcwbxStructureFields : public IDispatch
    {
    public:
        virtual /* [restricted][id] */ HRESULT STDMETHODCALLTYPE _NewEnum( 
            /* [retval][out] */ IUnknown **ppvObject) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT index,
            /* [retval][out] */ IcwbxStructureField **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Append( 
            /* [in] */ BSTR name,
            /* [in] */ long length,
            /* [retval][out] */ IcwbxStructureField **retval) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [restricted][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_BinaryData( 
            /* [in] */ IcwbxBinaryData *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxStructureFieldsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxStructureFields * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxStructureFields * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxStructureFields * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxStructureFields * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxStructureFields * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxStructureFields * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxStructureFields * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [restricted][id] */ HRESULT ( STDMETHODCALLTYPE *_NewEnum )( 
            IcwbxStructureFields * This,
            /* [retval][out] */ IUnknown **ppvObject);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IcwbxStructureFields * This,
            /* [in] */ VARIANT index,
            /* [retval][out] */ IcwbxStructureField **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IcwbxStructureFields * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Append )( 
            IcwbxStructureFields * This,
            /* [in] */ BSTR name,
            /* [in] */ long length,
            /* [retval][out] */ IcwbxStructureField **retval);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IcwbxStructureFields * This);
        
        /* [restricted][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_BinaryData )( 
            IcwbxStructureFields * This,
            /* [in] */ IcwbxBinaryData *newVal);
        
        END_INTERFACE
    } IcwbxStructureFieldsVtbl;

    interface IcwbxStructureFields
    {
        CONST_VTBL struct IcwbxStructureFieldsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxStructureFields_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxStructureFields_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxStructureFields_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxStructureFields_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxStructureFields_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxStructureFields_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxStructureFields_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxStructureFields__NewEnum(This,ppvObject)	\
    (This)->lpVtbl -> _NewEnum(This,ppvObject)

#define IcwbxStructureFields_get_Item(This,index,pVal)	\
    (This)->lpVtbl -> get_Item(This,index,pVal)

#define IcwbxStructureFields_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IcwbxStructureFields_Append(This,name,length,retval)	\
    (This)->lpVtbl -> Append(This,name,length,retval)

#define IcwbxStructureFields_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define IcwbxStructureFields_putref_BinaryData(This,newVal)	\
    (This)->lpVtbl -> putref_BinaryData(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [restricted][id] */ HRESULT STDMETHODCALLTYPE IcwbxStructureFields__NewEnum_Proxy( 
    IcwbxStructureFields * This,
    /* [retval][out] */ IUnknown **ppvObject);


void __RPC_STUB IcwbxStructureFields__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxStructureFields_get_Item_Proxy( 
    IcwbxStructureFields * This,
    /* [in] */ VARIANT index,
    /* [retval][out] */ IcwbxStructureField **pVal);


void __RPC_STUB IcwbxStructureFields_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxStructureFields_get_Count_Proxy( 
    IcwbxStructureFields * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxStructureFields_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxStructureFields_Append_Proxy( 
    IcwbxStructureFields * This,
    /* [in] */ BSTR name,
    /* [in] */ long length,
    /* [retval][out] */ IcwbxStructureField **retval);


void __RPC_STUB IcwbxStructureFields_Append_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxStructureFields_Clear_Proxy( 
    IcwbxStructureFields * This);


void __RPC_STUB IcwbxStructureFields_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propputref] */ HRESULT STDMETHODCALLTYPE IcwbxStructureFields_putref_BinaryData_Proxy( 
    IcwbxStructureFields * This,
    /* [in] */ IcwbxBinaryData *newVal);


void __RPC_STUB IcwbxStructureFields_putref_BinaryData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxStructureFields_INTERFACE_DEFINED__ */


#ifndef __IcwbxError_INTERFACE_DEFINED__
#define __IcwbxError_INTERFACE_DEFINED__

/* interface IcwbxError */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxError;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3DEF994A-1673-11D2-849C-0004AC94E175")
    IcwbxError : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Class( 
            /* [retval][out] */ cwbsvErrorClassEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_Class( 
            cwbsvErrorClassEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Text( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_Text( 
            BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetHostMessageInfo( 
            /* [out] */ VARIANT *hostMessageLibraryName,
            /* [out] */ VARIANT *hostMessageFileName,
            /* [out] */ VARIANT *hostSubstitutionText) = 0;
        
        virtual /* [restricted][id] */ HRESULT STDMETHODCALLTYPE PutHostMessageInfo( 
            /* [in] */ BSTR hostMessageLibraryName,
            /* [in] */ BSTR hostMessageFileName,
            /* [in] */ VARIANT hostMessageSubstText) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxErrorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxError * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxError * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxError * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxError * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxError * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxError * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxError * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Class )( 
            IcwbxError * This,
            /* [retval][out] */ cwbsvErrorClassEnum *pVal);
        
        /* [helpcontext][helpstring][restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Class )( 
            IcwbxError * This,
            cwbsvErrorClassEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Text )( 
            IcwbxError * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Text )( 
            IcwbxError * This,
            BSTR newVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetHostMessageInfo )( 
            IcwbxError * This,
            /* [out] */ VARIANT *hostMessageLibraryName,
            /* [out] */ VARIANT *hostMessageFileName,
            /* [out] */ VARIANT *hostSubstitutionText);
        
        /* [restricted][id] */ HRESULT ( STDMETHODCALLTYPE *PutHostMessageInfo )( 
            IcwbxError * This,
            /* [in] */ BSTR hostMessageLibraryName,
            /* [in] */ BSTR hostMessageFileName,
            /* [in] */ VARIANT hostMessageSubstText);
        
        END_INTERFACE
    } IcwbxErrorVtbl;

    interface IcwbxError
    {
        CONST_VTBL struct IcwbxErrorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxError_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxError_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxError_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxError_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxError_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxError_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxError_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxError_get_Class(This,pVal)	\
    (This)->lpVtbl -> get_Class(This,pVal)

#define IcwbxError_put_Class(This,newVal)	\
    (This)->lpVtbl -> put_Class(This,newVal)

#define IcwbxError_get_Text(This,pVal)	\
    (This)->lpVtbl -> get_Text(This,pVal)

#define IcwbxError_put_Text(This,newVal)	\
    (This)->lpVtbl -> put_Text(This,newVal)

#define IcwbxError_GetHostMessageInfo(This,hostMessageLibraryName,hostMessageFileName,hostSubstitutionText)	\
    (This)->lpVtbl -> GetHostMessageInfo(This,hostMessageLibraryName,hostMessageFileName,hostSubstitutionText)

#define IcwbxError_PutHostMessageInfo(This,hostMessageLibraryName,hostMessageFileName,hostMessageSubstText)	\
    (This)->lpVtbl -> PutHostMessageInfo(This,hostMessageLibraryName,hostMessageFileName,hostMessageSubstText)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxError_get_Class_Proxy( 
    IcwbxError * This,
    /* [retval][out] */ cwbsvErrorClassEnum *pVal);


void __RPC_STUB IcwbxError_get_Class_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxError_put_Class_Proxy( 
    IcwbxError * This,
    cwbsvErrorClassEnum newVal);


void __RPC_STUB IcwbxError_put_Class_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxError_get_Text_Proxy( 
    IcwbxError * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxError_get_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxError_put_Text_Proxy( 
    IcwbxError * This,
    BSTR newVal);


void __RPC_STUB IcwbxError_put_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxError_GetHostMessageInfo_Proxy( 
    IcwbxError * This,
    /* [out] */ VARIANT *hostMessageLibraryName,
    /* [out] */ VARIANT *hostMessageFileName,
    /* [out] */ VARIANT *hostSubstitutionText);


void __RPC_STUB IcwbxError_GetHostMessageInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id] */ HRESULT STDMETHODCALLTYPE IcwbxError_PutHostMessageInfo_Proxy( 
    IcwbxError * This,
    /* [in] */ BSTR hostMessageLibraryName,
    /* [in] */ BSTR hostMessageFileName,
    /* [in] */ VARIANT hostMessageSubstText);


void __RPC_STUB IcwbxError_PutHostMessageInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxError_INTERFACE_DEFINED__ */


#ifndef __IcwbxErrors_INTERFACE_DEFINED__
#define __IcwbxErrors_INTERFACE_DEFINED__

/* interface IcwbxErrors */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxErrors;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FDE7ADBB-1A69-11D2-849C-0004AC94E175")
    IcwbxErrors : public IDispatch
    {
    public:
        virtual /* [restricted][id] */ HRESULT STDMETHODCALLTYPE _NewEnum( 
            /* [retval][out] */ IUnknown **ppvObject) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ IcwbxError **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get_Handle( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [restricted][id] */ HRESULT STDMETHODCALLTYPE RaiseError( 
            /* [in] */ long cwbRC,
            /* [defaultvalue][optional][in] */ BSTR functionName = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ReturnCode( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReturnCode( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_OwnerObject( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [restricted][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [restricted][id] */ HRESULT STDMETHODCALLTYPE Populate( 
            /* [in] */ long cwbRC) = 0;
        
        virtual /* [restricted][id] */ HRESULT STDMETHODCALLTYPE CopyErrors( 
            /* [in] */ IcwbxErrors *srcErrors) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxErrorsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxErrors * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxErrors * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxErrors * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxErrors * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxErrors * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxErrors * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxErrors * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [restricted][id] */ HRESULT ( STDMETHODCALLTYPE *_NewEnum )( 
            IcwbxErrors * This,
            /* [retval][out] */ IUnknown **ppvObject);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IcwbxErrors * This,
            /* [in] */ long index,
            /* [retval][out] */ IcwbxError **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IcwbxErrors * This,
            /* [retval][out] */ long *pVal);
        
        /* [restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Handle )( 
            IcwbxErrors * This,
            /* [retval][out] */ long *pVal);
        
        /* [restricted][id] */ HRESULT ( STDMETHODCALLTYPE *RaiseError )( 
            IcwbxErrors * This,
            /* [in] */ long cwbRC,
            /* [defaultvalue][optional][in] */ BSTR functionName);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ReturnCode )( 
            IcwbxErrors * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ReturnCode )( 
            IcwbxErrors * This,
            /* [in] */ long newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OwnerObject )( 
            IcwbxErrors * This,
            /* [in] */ long newVal);
        
        /* [restricted][id] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IcwbxErrors * This);
        
        /* [restricted][id] */ HRESULT ( STDMETHODCALLTYPE *Populate )( 
            IcwbxErrors * This,
            /* [in] */ long cwbRC);
        
        /* [restricted][id] */ HRESULT ( STDMETHODCALLTYPE *CopyErrors )( 
            IcwbxErrors * This,
            /* [in] */ IcwbxErrors *srcErrors);
        
        END_INTERFACE
    } IcwbxErrorsVtbl;

    interface IcwbxErrors
    {
        CONST_VTBL struct IcwbxErrorsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxErrors_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxErrors_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxErrors_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxErrors_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxErrors_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxErrors_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxErrors_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxErrors__NewEnum(This,ppvObject)	\
    (This)->lpVtbl -> _NewEnum(This,ppvObject)

#define IcwbxErrors_get_Item(This,index,pVal)	\
    (This)->lpVtbl -> get_Item(This,index,pVal)

#define IcwbxErrors_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IcwbxErrors_get_Handle(This,pVal)	\
    (This)->lpVtbl -> get_Handle(This,pVal)

#define IcwbxErrors_RaiseError(This,cwbRC,functionName)	\
    (This)->lpVtbl -> RaiseError(This,cwbRC,functionName)

#define IcwbxErrors_get_ReturnCode(This,pVal)	\
    (This)->lpVtbl -> get_ReturnCode(This,pVal)

#define IcwbxErrors_put_ReturnCode(This,newVal)	\
    (This)->lpVtbl -> put_ReturnCode(This,newVal)

#define IcwbxErrors_put_OwnerObject(This,newVal)	\
    (This)->lpVtbl -> put_OwnerObject(This,newVal)

#define IcwbxErrors_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define IcwbxErrors_Populate(This,cwbRC)	\
    (This)->lpVtbl -> Populate(This,cwbRC)

#define IcwbxErrors_CopyErrors(This,srcErrors)	\
    (This)->lpVtbl -> CopyErrors(This,srcErrors)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [restricted][id] */ HRESULT STDMETHODCALLTYPE IcwbxErrors__NewEnum_Proxy( 
    IcwbxErrors * This,
    /* [retval][out] */ IUnknown **ppvObject);


void __RPC_STUB IcwbxErrors__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxErrors_get_Item_Proxy( 
    IcwbxErrors * This,
    /* [in] */ long index,
    /* [retval][out] */ IcwbxError **pVal);


void __RPC_STUB IcwbxErrors_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxErrors_get_Count_Proxy( 
    IcwbxErrors * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxErrors_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxErrors_get_Handle_Proxy( 
    IcwbxErrors * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxErrors_get_Handle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id] */ HRESULT STDMETHODCALLTYPE IcwbxErrors_RaiseError_Proxy( 
    IcwbxErrors * This,
    /* [in] */ long cwbRC,
    /* [defaultvalue][optional][in] */ BSTR functionName);


void __RPC_STUB IcwbxErrors_RaiseError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxErrors_get_ReturnCode_Proxy( 
    IcwbxErrors * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxErrors_get_ReturnCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxErrors_put_ReturnCode_Proxy( 
    IcwbxErrors * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxErrors_put_ReturnCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxErrors_put_OwnerObject_Proxy( 
    IcwbxErrors * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxErrors_put_OwnerObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id] */ HRESULT STDMETHODCALLTYPE IcwbxErrors_Clear_Proxy( 
    IcwbxErrors * This);


void __RPC_STUB IcwbxErrors_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id] */ HRESULT STDMETHODCALLTYPE IcwbxErrors_Populate_Proxy( 
    IcwbxErrors * This,
    /* [in] */ long cwbRC);


void __RPC_STUB IcwbxErrors_Populate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id] */ HRESULT STDMETHODCALLTYPE IcwbxErrors_CopyErrors_Proxy( 
    IcwbxErrors * This,
    /* [in] */ IcwbxErrors *srcErrors);


void __RPC_STUB IcwbxErrors_CopyErrors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxErrors_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseTransfer_INTERFACE_DEFINED__
#define __IcwbxDatabaseTransfer_INTERFACE_DEFINED__

/* interface IcwbxDatabaseTransfer */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseTransfer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("35DD1AA0-0CAB-11D3-8392-C4CC6678F234")
    IcwbxDatabaseTransfer : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Errors( 
            /* [retval][out] */ IcwbxErrors **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Password( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UserID( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UserID( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Download( 
            /* [in] */ BSTR system,
            /* [in] */ BSTR hostFile,
            /* [in] */ BSTR pcFile,
            /* [defaultvalue][optional][in] */ cwbdtFileTypeEnum pcFileType = cwbdtASCIIText) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Transfer( 
            /* [in] */ BSTR requestFile) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Upload( 
            /* [in] */ BSTR system,
            /* [in] */ BSTR hostFile,
            /* [in] */ BSTR pcFile,
            /* [in] */ BSTR fileDescriptionFile) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TransferResults( 
            /* [retval][out] */ IcwbxDatabaseTransferResults **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseTransferVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseTransfer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseTransfer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseTransfer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseTransfer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseTransfer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseTransfer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseTransfer * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Errors )( 
            IcwbxDatabaseTransfer * This,
            /* [retval][out] */ IcwbxErrors **pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Password )( 
            IcwbxDatabaseTransfer * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UserID )( 
            IcwbxDatabaseTransfer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UserID )( 
            IcwbxDatabaseTransfer * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Download )( 
            IcwbxDatabaseTransfer * This,
            /* [in] */ BSTR system,
            /* [in] */ BSTR hostFile,
            /* [in] */ BSTR pcFile,
            /* [defaultvalue][optional][in] */ cwbdtFileTypeEnum pcFileType);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Transfer )( 
            IcwbxDatabaseTransfer * This,
            /* [in] */ BSTR requestFile);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Upload )( 
            IcwbxDatabaseTransfer * This,
            /* [in] */ BSTR system,
            /* [in] */ BSTR hostFile,
            /* [in] */ BSTR pcFile,
            /* [in] */ BSTR fileDescriptionFile);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TransferResults )( 
            IcwbxDatabaseTransfer * This,
            /* [retval][out] */ IcwbxDatabaseTransferResults **pVal);
        
        END_INTERFACE
    } IcwbxDatabaseTransferVtbl;

    interface IcwbxDatabaseTransfer
    {
        CONST_VTBL struct IcwbxDatabaseTransferVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseTransfer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseTransfer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseTransfer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseTransfer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseTransfer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseTransfer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseTransfer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseTransfer_get_Errors(This,pVal)	\
    (This)->lpVtbl -> get_Errors(This,pVal)

#define IcwbxDatabaseTransfer_put_Password(This,newVal)	\
    (This)->lpVtbl -> put_Password(This,newVal)

#define IcwbxDatabaseTransfer_get_UserID(This,pVal)	\
    (This)->lpVtbl -> get_UserID(This,pVal)

#define IcwbxDatabaseTransfer_put_UserID(This,newVal)	\
    (This)->lpVtbl -> put_UserID(This,newVal)

#define IcwbxDatabaseTransfer_Download(This,system,hostFile,pcFile,pcFileType)	\
    (This)->lpVtbl -> Download(This,system,hostFile,pcFile,pcFileType)

#define IcwbxDatabaseTransfer_Transfer(This,requestFile)	\
    (This)->lpVtbl -> Transfer(This,requestFile)

#define IcwbxDatabaseTransfer_Upload(This,system,hostFile,pcFile,fileDescriptionFile)	\
    (This)->lpVtbl -> Upload(This,system,hostFile,pcFile,fileDescriptionFile)

#define IcwbxDatabaseTransfer_get_TransferResults(This,pVal)	\
    (This)->lpVtbl -> get_TransferResults(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseTransfer_get_Errors_Proxy( 
    IcwbxDatabaseTransfer * This,
    /* [retval][out] */ IcwbxErrors **pVal);


void __RPC_STUB IcwbxDatabaseTransfer_get_Errors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseTransfer_put_Password_Proxy( 
    IcwbxDatabaseTransfer * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseTransfer_put_Password_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseTransfer_get_UserID_Proxy( 
    IcwbxDatabaseTransfer * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseTransfer_get_UserID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseTransfer_put_UserID_Proxy( 
    IcwbxDatabaseTransfer * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseTransfer_put_UserID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseTransfer_Download_Proxy( 
    IcwbxDatabaseTransfer * This,
    /* [in] */ BSTR system,
    /* [in] */ BSTR hostFile,
    /* [in] */ BSTR pcFile,
    /* [defaultvalue][optional][in] */ cwbdtFileTypeEnum pcFileType);


void __RPC_STUB IcwbxDatabaseTransfer_Download_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseTransfer_Transfer_Proxy( 
    IcwbxDatabaseTransfer * This,
    /* [in] */ BSTR requestFile);


void __RPC_STUB IcwbxDatabaseTransfer_Transfer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseTransfer_Upload_Proxy( 
    IcwbxDatabaseTransfer * This,
    /* [in] */ BSTR system,
    /* [in] */ BSTR hostFile,
    /* [in] */ BSTR pcFile,
    /* [in] */ BSTR fileDescriptionFile);


void __RPC_STUB IcwbxDatabaseTransfer_Upload_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseTransfer_get_TransferResults_Proxy( 
    IcwbxDatabaseTransfer * This,
    /* [retval][out] */ IcwbxDatabaseTransferResults **pVal);


void __RPC_STUB IcwbxDatabaseTransfer_get_TransferResults_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseTransfer_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadRequest2_INTERFACE_DEFINED__
#define __IcwbxDatabaseDownloadRequest2_INTERFACE_DEFINED__

/* interface IcwbxDatabaseDownloadRequest2 */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseDownloadRequest2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C0AF132D-EEDE-4BDF-8D57-7CBDCD774E77")
    IcwbxDatabaseDownloadRequest2 : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AS400File( 
            /* [retval][out] */ IcwbxDatabaseAS400File **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Convert65535( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Convert65535( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Errors( 
            /* [retval][out] */ IcwbxErrors **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Format( 
            /* [retval][out] */ IcwbxDatabaseFormatOptions **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LogDataErrorPositions( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LogDataErrorPositions( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_pcFile( 
            /* [retval][out] */ IcwbxDatabaseDownloadPCFile **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Query( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Query( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StopOnTruncation( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StopOnTruncation( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_System( 
            /* [retval][out] */ IcwbxSystem **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_System( 
            /* [in] */ IcwbxSystem *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StopOnUntranslatableField( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StopOnUntranslatableField( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Cancel( 
            /* [defaultvalue][optional][in] */ VARIANT_BOOL force = 0,
            /* [defaultvalue][optional][in] */ long timeOut = 10) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Download( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE DownloadAsync( 
            /* [defaultvalue][optional][in] */ long rowStatusInterval = 0) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadRequest( 
            /* [in] */ BSTR fileName) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveRequest( 
            /* [in] */ BSTR fileName,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL overwriteIfExists = -1) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UserLibraryList( 
            /* [retval][out] */ IcwbxDatabaseUserLibraryList **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_QueryDataTransferSyntax( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_QueryDataTransferSyntax( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UseFieldAlias( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UseFieldAlias( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TransferResults( 
            /* [retval][out] */ IcwbxDatabaseTransferResults **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UseCompression( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UseCompression( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Database( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Database( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseDownloadRequest2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseDownloadRequest2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseDownloadRequest2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AS400File )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [retval][out] */ IcwbxDatabaseAS400File **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Convert65535 )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Convert65535 )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Errors )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [retval][out] */ IcwbxErrors **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Format )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [retval][out] */ IcwbxDatabaseFormatOptions **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LogDataErrorPositions )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LogDataErrorPositions )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_pcFile )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [retval][out] */ IcwbxDatabaseDownloadPCFile **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Query )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Query )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StopOnTruncation )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StopOnTruncation )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_System )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [retval][out] */ IcwbxSystem **pVal);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_System )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [in] */ IcwbxSystem *newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StopOnUntranslatableField )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StopOnUntranslatableField )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Cancel )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL force,
            /* [defaultvalue][optional][in] */ long timeOut);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Download )( 
            IcwbxDatabaseDownloadRequest2 * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DownloadAsync )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [defaultvalue][optional][in] */ long rowStatusInterval);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadRequest )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [in] */ BSTR fileName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveRequest )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [in] */ BSTR fileName,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL overwriteIfExists);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UserLibraryList )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [retval][out] */ IcwbxDatabaseUserLibraryList **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_QueryDataTransferSyntax )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_QueryDataTransferSyntax )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UseFieldAlias )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UseFieldAlias )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TransferResults )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [retval][out] */ IcwbxDatabaseTransferResults **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UseCompression )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UseCompression )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Database )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Database )( 
            IcwbxDatabaseDownloadRequest2 * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } IcwbxDatabaseDownloadRequest2Vtbl;

    interface IcwbxDatabaseDownloadRequest2
    {
        CONST_VTBL struct IcwbxDatabaseDownloadRequest2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseDownloadRequest2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseDownloadRequest2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseDownloadRequest2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseDownloadRequest2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseDownloadRequest2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseDownloadRequest2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseDownloadRequest2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseDownloadRequest2_get_AS400File(This,pVal)	\
    (This)->lpVtbl -> get_AS400File(This,pVal)

#define IcwbxDatabaseDownloadRequest2_get_Convert65535(This,pVal)	\
    (This)->lpVtbl -> get_Convert65535(This,pVal)

#define IcwbxDatabaseDownloadRequest2_put_Convert65535(This,newVal)	\
    (This)->lpVtbl -> put_Convert65535(This,newVal)

#define IcwbxDatabaseDownloadRequest2_get_Errors(This,pVal)	\
    (This)->lpVtbl -> get_Errors(This,pVal)

#define IcwbxDatabaseDownloadRequest2_get_Format(This,pVal)	\
    (This)->lpVtbl -> get_Format(This,pVal)

#define IcwbxDatabaseDownloadRequest2_get_LogDataErrorPositions(This,pVal)	\
    (This)->lpVtbl -> get_LogDataErrorPositions(This,pVal)

#define IcwbxDatabaseDownloadRequest2_put_LogDataErrorPositions(This,newVal)	\
    (This)->lpVtbl -> put_LogDataErrorPositions(This,newVal)

#define IcwbxDatabaseDownloadRequest2_get_pcFile(This,pVal)	\
    (This)->lpVtbl -> get_pcFile(This,pVal)

#define IcwbxDatabaseDownloadRequest2_get_Query(This,pVal)	\
    (This)->lpVtbl -> get_Query(This,pVal)

#define IcwbxDatabaseDownloadRequest2_put_Query(This,newVal)	\
    (This)->lpVtbl -> put_Query(This,newVal)

#define IcwbxDatabaseDownloadRequest2_get_StopOnTruncation(This,pVal)	\
    (This)->lpVtbl -> get_StopOnTruncation(This,pVal)

#define IcwbxDatabaseDownloadRequest2_put_StopOnTruncation(This,newVal)	\
    (This)->lpVtbl -> put_StopOnTruncation(This,newVal)

#define IcwbxDatabaseDownloadRequest2_get_System(This,pVal)	\
    (This)->lpVtbl -> get_System(This,pVal)

#define IcwbxDatabaseDownloadRequest2_putref_System(This,newVal)	\
    (This)->lpVtbl -> putref_System(This,newVal)

#define IcwbxDatabaseDownloadRequest2_get_StopOnUntranslatableField(This,pVal)	\
    (This)->lpVtbl -> get_StopOnUntranslatableField(This,pVal)

#define IcwbxDatabaseDownloadRequest2_put_StopOnUntranslatableField(This,newVal)	\
    (This)->lpVtbl -> put_StopOnUntranslatableField(This,newVal)

#define IcwbxDatabaseDownloadRequest2_Cancel(This,force,timeOut)	\
    (This)->lpVtbl -> Cancel(This,force,timeOut)

#define IcwbxDatabaseDownloadRequest2_Download(This)	\
    (This)->lpVtbl -> Download(This)

#define IcwbxDatabaseDownloadRequest2_DownloadAsync(This,rowStatusInterval)	\
    (This)->lpVtbl -> DownloadAsync(This,rowStatusInterval)

#define IcwbxDatabaseDownloadRequest2_LoadRequest(This,fileName)	\
    (This)->lpVtbl -> LoadRequest(This,fileName)

#define IcwbxDatabaseDownloadRequest2_SaveRequest(This,fileName,overwriteIfExists)	\
    (This)->lpVtbl -> SaveRequest(This,fileName,overwriteIfExists)

#define IcwbxDatabaseDownloadRequest2_get_UserLibraryList(This,pVal)	\
    (This)->lpVtbl -> get_UserLibraryList(This,pVal)

#define IcwbxDatabaseDownloadRequest2_get_QueryDataTransferSyntax(This,pVal)	\
    (This)->lpVtbl -> get_QueryDataTransferSyntax(This,pVal)

#define IcwbxDatabaseDownloadRequest2_put_QueryDataTransferSyntax(This,newVal)	\
    (This)->lpVtbl -> put_QueryDataTransferSyntax(This,newVal)

#define IcwbxDatabaseDownloadRequest2_get_UseFieldAlias(This,pVal)	\
    (This)->lpVtbl -> get_UseFieldAlias(This,pVal)

#define IcwbxDatabaseDownloadRequest2_put_UseFieldAlias(This,newVal)	\
    (This)->lpVtbl -> put_UseFieldAlias(This,newVal)

#define IcwbxDatabaseDownloadRequest2_get_TransferResults(This,pVal)	\
    (This)->lpVtbl -> get_TransferResults(This,pVal)

#define IcwbxDatabaseDownloadRequest2_get_UseCompression(This,pVal)	\
    (This)->lpVtbl -> get_UseCompression(This,pVal)

#define IcwbxDatabaseDownloadRequest2_put_UseCompression(This,newVal)	\
    (This)->lpVtbl -> put_UseCompression(This,newVal)

#define IcwbxDatabaseDownloadRequest2_get_Database(This,pVal)	\
    (This)->lpVtbl -> get_Database(This,pVal)

#define IcwbxDatabaseDownloadRequest2_put_Database(This,newVal)	\
    (This)->lpVtbl -> put_Database(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_get_AS400File_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [retval][out] */ IcwbxDatabaseAS400File **pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_get_AS400File_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_get_Convert65535_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_get_Convert65535_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_put_Convert65535_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_put_Convert65535_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_get_Errors_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [retval][out] */ IcwbxErrors **pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_get_Errors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_get_Format_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [retval][out] */ IcwbxDatabaseFormatOptions **pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_get_Format_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_get_LogDataErrorPositions_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_get_LogDataErrorPositions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_put_LogDataErrorPositions_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_put_LogDataErrorPositions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_get_pcFile_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [retval][out] */ IcwbxDatabaseDownloadPCFile **pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_get_pcFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_get_Query_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [retval][out] */ VARIANT *pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_get_Query_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_put_Query_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_put_Query_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_get_StopOnTruncation_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_get_StopOnTruncation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_put_StopOnTruncation_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_put_StopOnTruncation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_get_System_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [retval][out] */ IcwbxSystem **pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_get_System_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_putref_System_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [in] */ IcwbxSystem *newVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_putref_System_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_get_StopOnUntranslatableField_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_get_StopOnUntranslatableField_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_put_StopOnUntranslatableField_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_put_StopOnUntranslatableField_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_Cancel_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL force,
    /* [defaultvalue][optional][in] */ long timeOut);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_Cancel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_Download_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_Download_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_DownloadAsync_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [defaultvalue][optional][in] */ long rowStatusInterval);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_DownloadAsync_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_LoadRequest_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [in] */ BSTR fileName);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_LoadRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_SaveRequest_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [in] */ BSTR fileName,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL overwriteIfExists);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_SaveRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_get_UserLibraryList_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [retval][out] */ IcwbxDatabaseUserLibraryList **pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_get_UserLibraryList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_get_QueryDataTransferSyntax_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_get_QueryDataTransferSyntax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_put_QueryDataTransferSyntax_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_put_QueryDataTransferSyntax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_get_UseFieldAlias_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_get_UseFieldAlias_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_put_UseFieldAlias_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_put_UseFieldAlias_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_get_TransferResults_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [retval][out] */ IcwbxDatabaseTransferResults **pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_get_TransferResults_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_get_UseCompression_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_get_UseCompression_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_put_UseCompression_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_put_UseCompression_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_get_Database_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_get_Database_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadRequest2_put_Database_Proxy( 
    IcwbxDatabaseDownloadRequest2 * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseDownloadRequest2_put_Database_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseDownloadRequest2_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadRequestEvents_DISPINTERFACE_DEFINED__
#define __IcwbxDatabaseDownloadRequestEvents_DISPINTERFACE_DEFINED__

/* dispinterface IcwbxDatabaseDownloadRequestEvents */
/* [helpcontext][helpstring][uuid] */ 


EXTERN_C const IID DIID_IcwbxDatabaseDownloadRequestEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("35DD1AA4-0CAB-11D3-8392-C4CC6678F234")
    IcwbxDatabaseDownloadRequestEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseDownloadRequestEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseDownloadRequestEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseDownloadRequestEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseDownloadRequestEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseDownloadRequestEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseDownloadRequestEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseDownloadRequestEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseDownloadRequestEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IcwbxDatabaseDownloadRequestEventsVtbl;

    interface IcwbxDatabaseDownloadRequestEvents
    {
        CONST_VTBL struct IcwbxDatabaseDownloadRequestEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseDownloadRequestEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseDownloadRequestEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseDownloadRequestEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseDownloadRequestEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseDownloadRequestEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseDownloadRequestEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseDownloadRequestEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IcwbxDatabaseDownloadRequestEvents_DISPINTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseUploadRequest2_INTERFACE_DEFINED__
#define __IcwbxDatabaseUploadRequest2_INTERFACE_DEFINED__

/* interface IcwbxDatabaseUploadRequest2 */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseUploadRequest2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5A08845C-D589-479E-A461-7A1726859307")
    IcwbxDatabaseUploadRequest2 : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AS400File( 
            /* [retval][out] */ IcwbxDatabaseAS400File **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Convert65535( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Convert65535( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Errors( 
            /* [retval][out] */ IcwbxErrors **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LogDataErrorPositions( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LogDataErrorPositions( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_pcFile( 
            /* [retval][out] */ IcwbxDatabaseUploadPCFile **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StopOnMissingData( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StopOnMissingData( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StopOnRounding( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StopOnRounding( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StopOnTruncation( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StopOnTruncation( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_System( 
            /* [retval][out] */ IcwbxSystem **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_System( 
            /* [in] */ IcwbxSystem *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Cancel( 
            /* [defaultvalue][optional][in] */ VARIANT_BOOL force = 0,
            /* [defaultvalue][optional][in] */ long timeOut = 10) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadRequest( 
            /* [in] */ BSTR fileName) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveRequest( 
            /* [in] */ BSTR fileName,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL overwriteIfxists = -1) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Upload( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE UploadAsync( 
            /* [defaultvalue][optional][in] */ long rowStatusInterval = 0) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UserLibraryList( 
            /* [retval][out] */ IcwbxDatabaseUserLibraryList **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TransferResults( 
            /* [retval][out] */ IcwbxDatabaseTransferResults **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UseCompression( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UseCompression( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Database( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Database( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseUploadRequest2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseUploadRequest2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseUploadRequest2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AS400File )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [retval][out] */ IcwbxDatabaseAS400File **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Convert65535 )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Convert65535 )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Errors )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [retval][out] */ IcwbxErrors **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LogDataErrorPositions )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LogDataErrorPositions )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_pcFile )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [retval][out] */ IcwbxDatabaseUploadPCFile **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StopOnMissingData )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StopOnMissingData )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StopOnRounding )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StopOnRounding )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StopOnTruncation )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StopOnTruncation )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_System )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [retval][out] */ IcwbxSystem **pVal);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_System )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [in] */ IcwbxSystem *newVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Cancel )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL force,
            /* [defaultvalue][optional][in] */ long timeOut);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadRequest )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [in] */ BSTR fileName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveRequest )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [in] */ BSTR fileName,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL overwriteIfxists);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Upload )( 
            IcwbxDatabaseUploadRequest2 * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UploadAsync )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [defaultvalue][optional][in] */ long rowStatusInterval);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UserLibraryList )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [retval][out] */ IcwbxDatabaseUserLibraryList **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TransferResults )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [retval][out] */ IcwbxDatabaseTransferResults **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UseCompression )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UseCompression )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Database )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Database )( 
            IcwbxDatabaseUploadRequest2 * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } IcwbxDatabaseUploadRequest2Vtbl;

    interface IcwbxDatabaseUploadRequest2
    {
        CONST_VTBL struct IcwbxDatabaseUploadRequest2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseUploadRequest2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseUploadRequest2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseUploadRequest2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseUploadRequest2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseUploadRequest2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseUploadRequest2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseUploadRequest2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseUploadRequest2_get_AS400File(This,pVal)	\
    (This)->lpVtbl -> get_AS400File(This,pVal)

#define IcwbxDatabaseUploadRequest2_get_Convert65535(This,pVal)	\
    (This)->lpVtbl -> get_Convert65535(This,pVal)

#define IcwbxDatabaseUploadRequest2_put_Convert65535(This,newVal)	\
    (This)->lpVtbl -> put_Convert65535(This,newVal)

#define IcwbxDatabaseUploadRequest2_get_Errors(This,pVal)	\
    (This)->lpVtbl -> get_Errors(This,pVal)

#define IcwbxDatabaseUploadRequest2_get_LogDataErrorPositions(This,pVal)	\
    (This)->lpVtbl -> get_LogDataErrorPositions(This,pVal)

#define IcwbxDatabaseUploadRequest2_put_LogDataErrorPositions(This,newVal)	\
    (This)->lpVtbl -> put_LogDataErrorPositions(This,newVal)

#define IcwbxDatabaseUploadRequest2_get_pcFile(This,pVal)	\
    (This)->lpVtbl -> get_pcFile(This,pVal)

#define IcwbxDatabaseUploadRequest2_get_StopOnMissingData(This,pVal)	\
    (This)->lpVtbl -> get_StopOnMissingData(This,pVal)

#define IcwbxDatabaseUploadRequest2_put_StopOnMissingData(This,newVal)	\
    (This)->lpVtbl -> put_StopOnMissingData(This,newVal)

#define IcwbxDatabaseUploadRequest2_get_StopOnRounding(This,pVal)	\
    (This)->lpVtbl -> get_StopOnRounding(This,pVal)

#define IcwbxDatabaseUploadRequest2_put_StopOnRounding(This,newVal)	\
    (This)->lpVtbl -> put_StopOnRounding(This,newVal)

#define IcwbxDatabaseUploadRequest2_get_StopOnTruncation(This,pVal)	\
    (This)->lpVtbl -> get_StopOnTruncation(This,pVal)

#define IcwbxDatabaseUploadRequest2_put_StopOnTruncation(This,newVal)	\
    (This)->lpVtbl -> put_StopOnTruncation(This,newVal)

#define IcwbxDatabaseUploadRequest2_get_System(This,pVal)	\
    (This)->lpVtbl -> get_System(This,pVal)

#define IcwbxDatabaseUploadRequest2_putref_System(This,newVal)	\
    (This)->lpVtbl -> putref_System(This,newVal)

#define IcwbxDatabaseUploadRequest2_Cancel(This,force,timeOut)	\
    (This)->lpVtbl -> Cancel(This,force,timeOut)

#define IcwbxDatabaseUploadRequest2_LoadRequest(This,fileName)	\
    (This)->lpVtbl -> LoadRequest(This,fileName)

#define IcwbxDatabaseUploadRequest2_SaveRequest(This,fileName,overwriteIfxists)	\
    (This)->lpVtbl -> SaveRequest(This,fileName,overwriteIfxists)

#define IcwbxDatabaseUploadRequest2_Upload(This)	\
    (This)->lpVtbl -> Upload(This)

#define IcwbxDatabaseUploadRequest2_UploadAsync(This,rowStatusInterval)	\
    (This)->lpVtbl -> UploadAsync(This,rowStatusInterval)

#define IcwbxDatabaseUploadRequest2_get_UserLibraryList(This,pVal)	\
    (This)->lpVtbl -> get_UserLibraryList(This,pVal)

#define IcwbxDatabaseUploadRequest2_get_TransferResults(This,pVal)	\
    (This)->lpVtbl -> get_TransferResults(This,pVal)

#define IcwbxDatabaseUploadRequest2_get_UseCompression(This,pVal)	\
    (This)->lpVtbl -> get_UseCompression(This,pVal)

#define IcwbxDatabaseUploadRequest2_put_UseCompression(This,newVal)	\
    (This)->lpVtbl -> put_UseCompression(This,newVal)

#define IcwbxDatabaseUploadRequest2_get_Database(This,pVal)	\
    (This)->lpVtbl -> get_Database(This,pVal)

#define IcwbxDatabaseUploadRequest2_put_Database(This,newVal)	\
    (This)->lpVtbl -> put_Database(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest2_get_AS400File_Proxy( 
    IcwbxDatabaseUploadRequest2 * This,
    /* [retval][out] */ IcwbxDatabaseAS400File **pVal);


void __RPC_STUB IcwbxDatabaseUploadRequest2_get_AS400File_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest2_get_Convert65535_Proxy( 
    IcwbxDatabaseUploadRequest2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseUploadRequest2_get_Convert65535_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest2_put_Convert65535_Proxy( 
    IcwbxDatabaseUploadRequest2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadRequest2_put_Convert65535_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest2_get_Errors_Proxy( 
    IcwbxDatabaseUploadRequest2 * This,
    /* [retval][out] */ IcwbxErrors **pVal);


void __RPC_STUB IcwbxDatabaseUploadRequest2_get_Errors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest2_get_LogDataErrorPositions_Proxy( 
    IcwbxDatabaseUploadRequest2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseUploadRequest2_get_LogDataErrorPositions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest2_put_LogDataErrorPositions_Proxy( 
    IcwbxDatabaseUploadRequest2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadRequest2_put_LogDataErrorPositions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest2_get_pcFile_Proxy( 
    IcwbxDatabaseUploadRequest2 * This,
    /* [retval][out] */ IcwbxDatabaseUploadPCFile **pVal);


void __RPC_STUB IcwbxDatabaseUploadRequest2_get_pcFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest2_get_StopOnMissingData_Proxy( 
    IcwbxDatabaseUploadRequest2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseUploadRequest2_get_StopOnMissingData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest2_put_StopOnMissingData_Proxy( 
    IcwbxDatabaseUploadRequest2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadRequest2_put_StopOnMissingData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest2_get_StopOnRounding_Proxy( 
    IcwbxDatabaseUploadRequest2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseUploadRequest2_get_StopOnRounding_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest2_put_StopOnRounding_Proxy( 
    IcwbxDatabaseUploadRequest2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadRequest2_put_StopOnRounding_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest2_get_StopOnTruncation_Proxy( 
    IcwbxDatabaseUploadRequest2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseUploadRequest2_get_StopOnTruncation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest2_put_StopOnTruncation_Proxy( 
    IcwbxDatabaseUploadRequest2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadRequest2_put_StopOnTruncation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest2_get_System_Proxy( 
    IcwbxDatabaseUploadRequest2 * This,
    /* [retval][out] */ IcwbxSystem **pVal);


void __RPC_STUB IcwbxDatabaseUploadRequest2_get_System_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest2_putref_System_Proxy( 
    IcwbxDatabaseUploadRequest2 * This,
    /* [in] */ IcwbxSystem *newVal);


void __RPC_STUB IcwbxDatabaseUploadRequest2_putref_System_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest2_Cancel_Proxy( 
    IcwbxDatabaseUploadRequest2 * This,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL force,
    /* [defaultvalue][optional][in] */ long timeOut);


void __RPC_STUB IcwbxDatabaseUploadRequest2_Cancel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest2_LoadRequest_Proxy( 
    IcwbxDatabaseUploadRequest2 * This,
    /* [in] */ BSTR fileName);


void __RPC_STUB IcwbxDatabaseUploadRequest2_LoadRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest2_SaveRequest_Proxy( 
    IcwbxDatabaseUploadRequest2 * This,
    /* [in] */ BSTR fileName,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL overwriteIfxists);


void __RPC_STUB IcwbxDatabaseUploadRequest2_SaveRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest2_Upload_Proxy( 
    IcwbxDatabaseUploadRequest2 * This);


void __RPC_STUB IcwbxDatabaseUploadRequest2_Upload_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest2_UploadAsync_Proxy( 
    IcwbxDatabaseUploadRequest2 * This,
    /* [defaultvalue][optional][in] */ long rowStatusInterval);


void __RPC_STUB IcwbxDatabaseUploadRequest2_UploadAsync_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest2_get_UserLibraryList_Proxy( 
    IcwbxDatabaseUploadRequest2 * This,
    /* [retval][out] */ IcwbxDatabaseUserLibraryList **pVal);


void __RPC_STUB IcwbxDatabaseUploadRequest2_get_UserLibraryList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest2_get_TransferResults_Proxy( 
    IcwbxDatabaseUploadRequest2 * This,
    /* [retval][out] */ IcwbxDatabaseTransferResults **pVal);


void __RPC_STUB IcwbxDatabaseUploadRequest2_get_TransferResults_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest2_get_UseCompression_Proxy( 
    IcwbxDatabaseUploadRequest2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseUploadRequest2_get_UseCompression_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest2_put_UseCompression_Proxy( 
    IcwbxDatabaseUploadRequest2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadRequest2_put_UseCompression_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest2_get_Database_Proxy( 
    IcwbxDatabaseUploadRequest2 * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseUploadRequest2_get_Database_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadRequest2_put_Database_Proxy( 
    IcwbxDatabaseUploadRequest2 * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseUploadRequest2_put_Database_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseUploadRequest2_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseUploadRequestEvents_DISPINTERFACE_DEFINED__
#define __IcwbxDatabaseUploadRequestEvents_DISPINTERFACE_DEFINED__

/* dispinterface IcwbxDatabaseUploadRequestEvents */
/* [helpcontext][helpstring][uuid] */ 


EXTERN_C const IID DIID_IcwbxDatabaseUploadRequestEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("35DD1AA7-0CAB-11D3-8392-C4CC6678F234")
    IcwbxDatabaseUploadRequestEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseUploadRequestEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseUploadRequestEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseUploadRequestEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseUploadRequestEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseUploadRequestEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseUploadRequestEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseUploadRequestEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseUploadRequestEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IcwbxDatabaseUploadRequestEventsVtbl;

    interface IcwbxDatabaseUploadRequestEvents
    {
        CONST_VTBL struct IcwbxDatabaseUploadRequestEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseUploadRequestEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseUploadRequestEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseUploadRequestEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseUploadRequestEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseUploadRequestEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseUploadRequestEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseUploadRequestEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IcwbxDatabaseUploadRequestEvents_DISPINTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseQuerySettings_INTERFACE_DEFINED__
#define __IcwbxDatabaseQuerySettings_INTERFACE_DEFINED__

/* interface IcwbxDatabaseQuerySettings */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseQuerySettings;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("35DD1AA8-0CAB-11D3-8392-C4CC6678F234")
    IcwbxDatabaseQuerySettings : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GroupBy( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_GroupBy( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Having( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Having( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_JoinBy( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_JoinBy( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_JoinReturnsMissingFields( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_JoinReturnsMissingFields( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OrderBy( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OrderBy( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Select( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Select( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Where( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Where( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSortSequence( 
            /* [in] */ cwbdtSortSequenceTypeEnum sortType,
            /* [defaultvalue][optional][in] */ BSTR tableOrLangID = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSortSequence( 
            /* [out] */ VARIANT *sortType,
            /* [out] */ VARIANT *tableOrLangID) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReceiveInfo( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseQuerySettingsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseQuerySettings * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseQuerySettings * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseQuerySettings * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseQuerySettings * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseQuerySettings * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseQuerySettings * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseQuerySettings * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GroupBy )( 
            IcwbxDatabaseQuerySettings * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_GroupBy )( 
            IcwbxDatabaseQuerySettings * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Having )( 
            IcwbxDatabaseQuerySettings * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Having )( 
            IcwbxDatabaseQuerySettings * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_JoinBy )( 
            IcwbxDatabaseQuerySettings * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_JoinBy )( 
            IcwbxDatabaseQuerySettings * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_JoinReturnsMissingFields )( 
            IcwbxDatabaseQuerySettings * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_JoinReturnsMissingFields )( 
            IcwbxDatabaseQuerySettings * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OrderBy )( 
            IcwbxDatabaseQuerySettings * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OrderBy )( 
            IcwbxDatabaseQuerySettings * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Select )( 
            IcwbxDatabaseQuerySettings * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Select )( 
            IcwbxDatabaseQuerySettings * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Where )( 
            IcwbxDatabaseQuerySettings * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Where )( 
            IcwbxDatabaseQuerySettings * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSortSequence )( 
            IcwbxDatabaseQuerySettings * This,
            /* [in] */ cwbdtSortSequenceTypeEnum sortType,
            /* [defaultvalue][optional][in] */ BSTR tableOrLangID);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSortSequence )( 
            IcwbxDatabaseQuerySettings * This,
            /* [out] */ VARIANT *sortType,
            /* [out] */ VARIANT *tableOrLangID);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ReceiveInfo )( 
            IcwbxDatabaseQuerySettings * This,
            /* [in] */ long newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseQuerySettings * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IcwbxDatabaseQuerySettingsVtbl;

    interface IcwbxDatabaseQuerySettings
    {
        CONST_VTBL struct IcwbxDatabaseQuerySettingsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseQuerySettings_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseQuerySettings_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseQuerySettings_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseQuerySettings_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseQuerySettings_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseQuerySettings_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseQuerySettings_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseQuerySettings_get_GroupBy(This,pVal)	\
    (This)->lpVtbl -> get_GroupBy(This,pVal)

#define IcwbxDatabaseQuerySettings_put_GroupBy(This,newVal)	\
    (This)->lpVtbl -> put_GroupBy(This,newVal)

#define IcwbxDatabaseQuerySettings_get_Having(This,pVal)	\
    (This)->lpVtbl -> get_Having(This,pVal)

#define IcwbxDatabaseQuerySettings_put_Having(This,newVal)	\
    (This)->lpVtbl -> put_Having(This,newVal)

#define IcwbxDatabaseQuerySettings_get_JoinBy(This,pVal)	\
    (This)->lpVtbl -> get_JoinBy(This,pVal)

#define IcwbxDatabaseQuerySettings_put_JoinBy(This,newVal)	\
    (This)->lpVtbl -> put_JoinBy(This,newVal)

#define IcwbxDatabaseQuerySettings_get_JoinReturnsMissingFields(This,pVal)	\
    (This)->lpVtbl -> get_JoinReturnsMissingFields(This,pVal)

#define IcwbxDatabaseQuerySettings_put_JoinReturnsMissingFields(This,newVal)	\
    (This)->lpVtbl -> put_JoinReturnsMissingFields(This,newVal)

#define IcwbxDatabaseQuerySettings_get_OrderBy(This,pVal)	\
    (This)->lpVtbl -> get_OrderBy(This,pVal)

#define IcwbxDatabaseQuerySettings_put_OrderBy(This,newVal)	\
    (This)->lpVtbl -> put_OrderBy(This,newVal)

#define IcwbxDatabaseQuerySettings_get_Select(This,pVal)	\
    (This)->lpVtbl -> get_Select(This,pVal)

#define IcwbxDatabaseQuerySettings_put_Select(This,newVal)	\
    (This)->lpVtbl -> put_Select(This,newVal)

#define IcwbxDatabaseQuerySettings_get_Where(This,pVal)	\
    (This)->lpVtbl -> get_Where(This,pVal)

#define IcwbxDatabaseQuerySettings_put_Where(This,newVal)	\
    (This)->lpVtbl -> put_Where(This,newVal)

#define IcwbxDatabaseQuerySettings_SetSortSequence(This,sortType,tableOrLangID)	\
    (This)->lpVtbl -> SetSortSequence(This,sortType,tableOrLangID)

#define IcwbxDatabaseQuerySettings_GetSortSequence(This,sortType,tableOrLangID)	\
    (This)->lpVtbl -> GetSortSequence(This,sortType,tableOrLangID)

#define IcwbxDatabaseQuerySettings_put_ReceiveInfo(This,newVal)	\
    (This)->lpVtbl -> put_ReceiveInfo(This,newVal)

#define IcwbxDatabaseQuerySettings_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseQuerySettings_get_GroupBy_Proxy( 
    IcwbxDatabaseQuerySettings * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseQuerySettings_get_GroupBy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseQuerySettings_put_GroupBy_Proxy( 
    IcwbxDatabaseQuerySettings * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseQuerySettings_put_GroupBy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseQuerySettings_get_Having_Proxy( 
    IcwbxDatabaseQuerySettings * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseQuerySettings_get_Having_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseQuerySettings_put_Having_Proxy( 
    IcwbxDatabaseQuerySettings * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseQuerySettings_put_Having_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseQuerySettings_get_JoinBy_Proxy( 
    IcwbxDatabaseQuerySettings * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseQuerySettings_get_JoinBy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseQuerySettings_put_JoinBy_Proxy( 
    IcwbxDatabaseQuerySettings * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseQuerySettings_put_JoinBy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseQuerySettings_get_JoinReturnsMissingFields_Proxy( 
    IcwbxDatabaseQuerySettings * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseQuerySettings_get_JoinReturnsMissingFields_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseQuerySettings_put_JoinReturnsMissingFields_Proxy( 
    IcwbxDatabaseQuerySettings * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseQuerySettings_put_JoinReturnsMissingFields_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseQuerySettings_get_OrderBy_Proxy( 
    IcwbxDatabaseQuerySettings * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseQuerySettings_get_OrderBy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseQuerySettings_put_OrderBy_Proxy( 
    IcwbxDatabaseQuerySettings * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseQuerySettings_put_OrderBy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseQuerySettings_get_Select_Proxy( 
    IcwbxDatabaseQuerySettings * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseQuerySettings_get_Select_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseQuerySettings_put_Select_Proxy( 
    IcwbxDatabaseQuerySettings * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseQuerySettings_put_Select_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseQuerySettings_get_Where_Proxy( 
    IcwbxDatabaseQuerySettings * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseQuerySettings_get_Where_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseQuerySettings_put_Where_Proxy( 
    IcwbxDatabaseQuerySettings * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseQuerySettings_put_Where_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseQuerySettings_SetSortSequence_Proxy( 
    IcwbxDatabaseQuerySettings * This,
    /* [in] */ cwbdtSortSequenceTypeEnum sortType,
    /* [defaultvalue][optional][in] */ BSTR tableOrLangID);


void __RPC_STUB IcwbxDatabaseQuerySettings_SetSortSequence_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseQuerySettings_GetSortSequence_Proxy( 
    IcwbxDatabaseQuerySettings * This,
    /* [out] */ VARIANT *sortType,
    /* [out] */ VARIANT *tableOrLangID);


void __RPC_STUB IcwbxDatabaseQuerySettings_GetSortSequence_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseQuerySettings_put_ReceiveInfo_Proxy( 
    IcwbxDatabaseQuerySettings * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseQuerySettings_put_ReceiveInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseQuerySettings_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseQuerySettings * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseQuerySettings_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseQuerySettings_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseFormatOptions_INTERFACE_DEFINED__
#define __IcwbxDatabaseFormatOptions_INTERFACE_DEFINED__

/* interface IcwbxDatabaseFormatOptions */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseFormatOptions;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("35DD1AAA-0CAB-11D3-8392-C4CC6678F234")
    IcwbxDatabaseFormatOptions : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DecimalSeparator( 
            /* [retval][out] */ cwbdtDecimalSeparatorEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DecimalSeparator( 
            /* [in] */ cwbdtDecimalSeparatorEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IgnoreDecimalErrors( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IgnoreDecimalErrors( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDateFormat( 
            /* [out] */ VARIANT *format,
            /* [out] */ VARIANT *separator) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTimeFormat( 
            /* [out] */ VARIANT *format,
            /* [out] */ VARIANT *separator) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDateFormat( 
            /* [in] */ cwbdtDateFormatEnum format,
            /* [defaultvalue][optional][in] */ cwbdtDateSeparatorEnum separator = cwbdtDateSepNotSpecified) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetTimeFormat( 
            /* [in] */ cwbdtTimeFormatEnum format,
            /* [defaultvalue][optional][in] */ cwbdtTimeSeparatorEnum separator = cwbdtTimeSepNotSpecified) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReceiveInfo( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseFormatOptionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseFormatOptions * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseFormatOptions * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseFormatOptions * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseFormatOptions * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseFormatOptions * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseFormatOptions * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseFormatOptions * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DecimalSeparator )( 
            IcwbxDatabaseFormatOptions * This,
            /* [retval][out] */ cwbdtDecimalSeparatorEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DecimalSeparator )( 
            IcwbxDatabaseFormatOptions * This,
            /* [in] */ cwbdtDecimalSeparatorEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IgnoreDecimalErrors )( 
            IcwbxDatabaseFormatOptions * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IgnoreDecimalErrors )( 
            IcwbxDatabaseFormatOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDateFormat )( 
            IcwbxDatabaseFormatOptions * This,
            /* [out] */ VARIANT *format,
            /* [out] */ VARIANT *separator);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetTimeFormat )( 
            IcwbxDatabaseFormatOptions * This,
            /* [out] */ VARIANT *format,
            /* [out] */ VARIANT *separator);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDateFormat )( 
            IcwbxDatabaseFormatOptions * This,
            /* [in] */ cwbdtDateFormatEnum format,
            /* [defaultvalue][optional][in] */ cwbdtDateSeparatorEnum separator);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetTimeFormat )( 
            IcwbxDatabaseFormatOptions * This,
            /* [in] */ cwbdtTimeFormatEnum format,
            /* [defaultvalue][optional][in] */ cwbdtTimeSeparatorEnum separator);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ReceiveInfo )( 
            IcwbxDatabaseFormatOptions * This,
            /* [in] */ long newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseFormatOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IcwbxDatabaseFormatOptionsVtbl;

    interface IcwbxDatabaseFormatOptions
    {
        CONST_VTBL struct IcwbxDatabaseFormatOptionsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseFormatOptions_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseFormatOptions_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseFormatOptions_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseFormatOptions_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseFormatOptions_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseFormatOptions_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseFormatOptions_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseFormatOptions_get_DecimalSeparator(This,pVal)	\
    (This)->lpVtbl -> get_DecimalSeparator(This,pVal)

#define IcwbxDatabaseFormatOptions_put_DecimalSeparator(This,newVal)	\
    (This)->lpVtbl -> put_DecimalSeparator(This,newVal)

#define IcwbxDatabaseFormatOptions_get_IgnoreDecimalErrors(This,pVal)	\
    (This)->lpVtbl -> get_IgnoreDecimalErrors(This,pVal)

#define IcwbxDatabaseFormatOptions_put_IgnoreDecimalErrors(This,newVal)	\
    (This)->lpVtbl -> put_IgnoreDecimalErrors(This,newVal)

#define IcwbxDatabaseFormatOptions_GetDateFormat(This,format,separator)	\
    (This)->lpVtbl -> GetDateFormat(This,format,separator)

#define IcwbxDatabaseFormatOptions_GetTimeFormat(This,format,separator)	\
    (This)->lpVtbl -> GetTimeFormat(This,format,separator)

#define IcwbxDatabaseFormatOptions_SetDateFormat(This,format,separator)	\
    (This)->lpVtbl -> SetDateFormat(This,format,separator)

#define IcwbxDatabaseFormatOptions_SetTimeFormat(This,format,separator)	\
    (This)->lpVtbl -> SetTimeFormat(This,format,separator)

#define IcwbxDatabaseFormatOptions_put_ReceiveInfo(This,newVal)	\
    (This)->lpVtbl -> put_ReceiveInfo(This,newVal)

#define IcwbxDatabaseFormatOptions_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseFormatOptions_get_DecimalSeparator_Proxy( 
    IcwbxDatabaseFormatOptions * This,
    /* [retval][out] */ cwbdtDecimalSeparatorEnum *pVal);


void __RPC_STUB IcwbxDatabaseFormatOptions_get_DecimalSeparator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseFormatOptions_put_DecimalSeparator_Proxy( 
    IcwbxDatabaseFormatOptions * This,
    /* [in] */ cwbdtDecimalSeparatorEnum newVal);


void __RPC_STUB IcwbxDatabaseFormatOptions_put_DecimalSeparator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseFormatOptions_get_IgnoreDecimalErrors_Proxy( 
    IcwbxDatabaseFormatOptions * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseFormatOptions_get_IgnoreDecimalErrors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseFormatOptions_put_IgnoreDecimalErrors_Proxy( 
    IcwbxDatabaseFormatOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseFormatOptions_put_IgnoreDecimalErrors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseFormatOptions_GetDateFormat_Proxy( 
    IcwbxDatabaseFormatOptions * This,
    /* [out] */ VARIANT *format,
    /* [out] */ VARIANT *separator);


void __RPC_STUB IcwbxDatabaseFormatOptions_GetDateFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseFormatOptions_GetTimeFormat_Proxy( 
    IcwbxDatabaseFormatOptions * This,
    /* [out] */ VARIANT *format,
    /* [out] */ VARIANT *separator);


void __RPC_STUB IcwbxDatabaseFormatOptions_GetTimeFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseFormatOptions_SetDateFormat_Proxy( 
    IcwbxDatabaseFormatOptions * This,
    /* [in] */ cwbdtDateFormatEnum format,
    /* [defaultvalue][optional][in] */ cwbdtDateSeparatorEnum separator);


void __RPC_STUB IcwbxDatabaseFormatOptions_SetDateFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseFormatOptions_SetTimeFormat_Proxy( 
    IcwbxDatabaseFormatOptions * This,
    /* [in] */ cwbdtTimeFormatEnum format,
    /* [defaultvalue][optional][in] */ cwbdtTimeSeparatorEnum separator);


void __RPC_STUB IcwbxDatabaseFormatOptions_SetTimeFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseFormatOptions_put_ReceiveInfo_Proxy( 
    IcwbxDatabaseFormatOptions * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseFormatOptions_put_ReceiveInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseFormatOptions_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseFormatOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseFormatOptions_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseFormatOptions_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseAS400File_INTERFACE_DEFINED__
#define __IcwbxDatabaseAS400File_INTERFACE_DEFINED__

/* interface IcwbxDatabaseAS400File */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseAS400File;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("35DD1AAC-0CAB-11D3-8392-C4CC6678F234")
    IcwbxDatabaseAS400File : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetUploadCreationInfo( 
            /* [in] */ cwbdtAS400FileCreateEnum createOption,
            /* [defaultvalue][optional][in] */ BSTR memberText = L"",
            /* [defaultvalue][optional][in] */ BSTR fileText = L"",
            /* [defaultvalue][optional][in] */ cwbdtObjectAuthorityEnum objectAuthority = cwbdtObjAuthReadWrite,
            /* [defaultvalue][optional][in] */ BSTR createBasedOnFile = L"",
            /* [defaultvalue][optional][in] */ long recordLength = 0) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_XferInfo( 
            /* [in] */ long xferType,
            /* [in] */ long newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetUploadCreationInfo( 
            /* [out] */ VARIANT *createOption,
            /* [out] */ VARIANT *memberText,
            /* [out] */ VARIANT *fileText,
            /* [out] */ VARIANT *objectAuthority,
            /* [out] */ VARIANT *createBasedOnFile,
            /* [out] */ VARIANT *recordLength) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseAS400FileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseAS400File * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseAS400File * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseAS400File * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseAS400File * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseAS400File * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseAS400File * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseAS400File * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IcwbxDatabaseAS400File * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IcwbxDatabaseAS400File * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetUploadCreationInfo )( 
            IcwbxDatabaseAS400File * This,
            /* [in] */ cwbdtAS400FileCreateEnum createOption,
            /* [defaultvalue][optional][in] */ BSTR memberText,
            /* [defaultvalue][optional][in] */ BSTR fileText,
            /* [defaultvalue][optional][in] */ cwbdtObjectAuthorityEnum objectAuthority,
            /* [defaultvalue][optional][in] */ BSTR createBasedOnFile,
            /* [defaultvalue][optional][in] */ long recordLength);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_XferInfo )( 
            IcwbxDatabaseAS400File * This,
            /* [in] */ long xferType,
            /* [in] */ long newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseAS400File * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetUploadCreationInfo )( 
            IcwbxDatabaseAS400File * This,
            /* [out] */ VARIANT *createOption,
            /* [out] */ VARIANT *memberText,
            /* [out] */ VARIANT *fileText,
            /* [out] */ VARIANT *objectAuthority,
            /* [out] */ VARIANT *createBasedOnFile,
            /* [out] */ VARIANT *recordLength);
        
        END_INTERFACE
    } IcwbxDatabaseAS400FileVtbl;

    interface IcwbxDatabaseAS400File
    {
        CONST_VTBL struct IcwbxDatabaseAS400FileVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseAS400File_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseAS400File_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseAS400File_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseAS400File_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseAS400File_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseAS400File_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseAS400File_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseAS400File_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IcwbxDatabaseAS400File_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IcwbxDatabaseAS400File_SetUploadCreationInfo(This,createOption,memberText,fileText,objectAuthority,createBasedOnFile,recordLength)	\
    (This)->lpVtbl -> SetUploadCreationInfo(This,createOption,memberText,fileText,objectAuthority,createBasedOnFile,recordLength)

#define IcwbxDatabaseAS400File_put_XferInfo(This,xferType,newVal)	\
    (This)->lpVtbl -> put_XferInfo(This,xferType,newVal)

#define IcwbxDatabaseAS400File_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#define IcwbxDatabaseAS400File_GetUploadCreationInfo(This,createOption,memberText,fileText,objectAuthority,createBasedOnFile,recordLength)	\
    (This)->lpVtbl -> GetUploadCreationInfo(This,createOption,memberText,fileText,objectAuthority,createBasedOnFile,recordLength)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseAS400File_get_Name_Proxy( 
    IcwbxDatabaseAS400File * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseAS400File_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseAS400File_put_Name_Proxy( 
    IcwbxDatabaseAS400File * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseAS400File_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseAS400File_SetUploadCreationInfo_Proxy( 
    IcwbxDatabaseAS400File * This,
    /* [in] */ cwbdtAS400FileCreateEnum createOption,
    /* [defaultvalue][optional][in] */ BSTR memberText,
    /* [defaultvalue][optional][in] */ BSTR fileText,
    /* [defaultvalue][optional][in] */ cwbdtObjectAuthorityEnum objectAuthority,
    /* [defaultvalue][optional][in] */ BSTR createBasedOnFile,
    /* [defaultvalue][optional][in] */ long recordLength);


void __RPC_STUB IcwbxDatabaseAS400File_SetUploadCreationInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseAS400File_put_XferInfo_Proxy( 
    IcwbxDatabaseAS400File * This,
    /* [in] */ long xferType,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseAS400File_put_XferInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseAS400File_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseAS400File * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseAS400File_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseAS400File_GetUploadCreationInfo_Proxy( 
    IcwbxDatabaseAS400File * This,
    /* [out] */ VARIANT *createOption,
    /* [out] */ VARIANT *memberText,
    /* [out] */ VARIANT *fileText,
    /* [out] */ VARIANT *objectAuthority,
    /* [out] */ VARIANT *createBasedOnFile,
    /* [out] */ VARIANT *recordLength);


void __RPC_STUB IcwbxDatabaseAS400File_GetUploadCreationInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseAS400File_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseUploadPCFile_INTERFACE_DEFINED__
#define __IcwbxDatabaseUploadPCFile_INTERFACE_DEFINED__

/* interface IcwbxDatabaseUploadPCFile */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseUploadPCFile;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DC72E800-4F12-11D3-8392-CFA6284581C3")
    IcwbxDatabaseUploadPCFile : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileType( 
            /* [retval][out] */ cwbdtFileTypeEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FileType( 
            /* [in] */ cwbdtFileTypeEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_fileDescriptionFile( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_fileDescriptionFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Options( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_SendInfo( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [restricted][id] */ HRESULT STDMETHODCALLTYPE InactivateOptions( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseUploadPCFileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseUploadPCFile * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseUploadPCFile * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseUploadPCFile * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseUploadPCFile * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseUploadPCFile * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseUploadPCFile * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseUploadPCFile * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IcwbxDatabaseUploadPCFile * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IcwbxDatabaseUploadPCFile * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FileType )( 
            IcwbxDatabaseUploadPCFile * This,
            /* [retval][out] */ cwbdtFileTypeEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FileType )( 
            IcwbxDatabaseUploadPCFile * This,
            /* [in] */ cwbdtFileTypeEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fileDescriptionFile )( 
            IcwbxDatabaseUploadPCFile * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fileDescriptionFile )( 
            IcwbxDatabaseUploadPCFile * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Options )( 
            IcwbxDatabaseUploadPCFile * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SendInfo )( 
            IcwbxDatabaseUploadPCFile * This,
            /* [in] */ long newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseUploadPCFile * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [restricted][id] */ HRESULT ( STDMETHODCALLTYPE *InactivateOptions )( 
            IcwbxDatabaseUploadPCFile * This);
        
        END_INTERFACE
    } IcwbxDatabaseUploadPCFileVtbl;

    interface IcwbxDatabaseUploadPCFile
    {
        CONST_VTBL struct IcwbxDatabaseUploadPCFileVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseUploadPCFile_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseUploadPCFile_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseUploadPCFile_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseUploadPCFile_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseUploadPCFile_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseUploadPCFile_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseUploadPCFile_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseUploadPCFile_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IcwbxDatabaseUploadPCFile_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IcwbxDatabaseUploadPCFile_get_FileType(This,pVal)	\
    (This)->lpVtbl -> get_FileType(This,pVal)

#define IcwbxDatabaseUploadPCFile_put_FileType(This,newVal)	\
    (This)->lpVtbl -> put_FileType(This,newVal)

#define IcwbxDatabaseUploadPCFile_get_fileDescriptionFile(This,pVal)	\
    (This)->lpVtbl -> get_fileDescriptionFile(This,pVal)

#define IcwbxDatabaseUploadPCFile_put_fileDescriptionFile(This,newVal)	\
    (This)->lpVtbl -> put_fileDescriptionFile(This,newVal)

#define IcwbxDatabaseUploadPCFile_get_Options(This,pVal)	\
    (This)->lpVtbl -> get_Options(This,pVal)

#define IcwbxDatabaseUploadPCFile_put_SendInfo(This,newVal)	\
    (This)->lpVtbl -> put_SendInfo(This,newVal)

#define IcwbxDatabaseUploadPCFile_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#define IcwbxDatabaseUploadPCFile_InactivateOptions(This)	\
    (This)->lpVtbl -> InactivateOptions(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadPCFile_get_Name_Proxy( 
    IcwbxDatabaseUploadPCFile * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseUploadPCFile_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadPCFile_put_Name_Proxy( 
    IcwbxDatabaseUploadPCFile * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseUploadPCFile_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadPCFile_get_FileType_Proxy( 
    IcwbxDatabaseUploadPCFile * This,
    /* [retval][out] */ cwbdtFileTypeEnum *pVal);


void __RPC_STUB IcwbxDatabaseUploadPCFile_get_FileType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadPCFile_put_FileType_Proxy( 
    IcwbxDatabaseUploadPCFile * This,
    /* [in] */ cwbdtFileTypeEnum newVal);


void __RPC_STUB IcwbxDatabaseUploadPCFile_put_FileType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadPCFile_get_fileDescriptionFile_Proxy( 
    IcwbxDatabaseUploadPCFile * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseUploadPCFile_get_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadPCFile_put_fileDescriptionFile_Proxy( 
    IcwbxDatabaseUploadPCFile * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseUploadPCFile_put_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadPCFile_get_Options_Proxy( 
    IcwbxDatabaseUploadPCFile * This,
    /* [retval][out] */ VARIANT *pVal);


void __RPC_STUB IcwbxDatabaseUploadPCFile_get_Options_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadPCFile_put_SendInfo_Proxy( 
    IcwbxDatabaseUploadPCFile * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseUploadPCFile_put_SendInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadPCFile_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseUploadPCFile * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadPCFile_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadPCFile_InactivateOptions_Proxy( 
    IcwbxDatabaseUploadPCFile * This);


void __RPC_STUB IcwbxDatabaseUploadPCFile_InactivateOptions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseUploadPCFile_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseUploadPCOptions_INTERFACE_DEFINED__
#define __IcwbxDatabaseUploadPCOptions_INTERFACE_DEFINED__

/* interface IcwbxDatabaseUploadPCOptions */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseUploadPCOptions;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("35DD1AAE-0CAB-11D3-8392-C4CC6678F234")
    IcwbxDatabaseUploadPCOptions : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CodePage( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CodePage( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_SendInfo( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseUploadPCOptionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseUploadPCOptions * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseUploadPCOptions * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseUploadPCOptions * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseUploadPCOptions * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseUploadPCOptions * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseUploadPCOptions * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseUploadPCOptions * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CodePage )( 
            IcwbxDatabaseUploadPCOptions * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CodePage )( 
            IcwbxDatabaseUploadPCOptions * This,
            /* [in] */ long newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SendInfo )( 
            IcwbxDatabaseUploadPCOptions * This,
            /* [in] */ long newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseUploadPCOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IcwbxDatabaseUploadPCOptionsVtbl;

    interface IcwbxDatabaseUploadPCOptions
    {
        CONST_VTBL struct IcwbxDatabaseUploadPCOptionsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseUploadPCOptions_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseUploadPCOptions_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseUploadPCOptions_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseUploadPCOptions_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseUploadPCOptions_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseUploadPCOptions_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseUploadPCOptions_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseUploadPCOptions_get_CodePage(This,pVal)	\
    (This)->lpVtbl -> get_CodePage(This,pVal)

#define IcwbxDatabaseUploadPCOptions_put_CodePage(This,newVal)	\
    (This)->lpVtbl -> put_CodePage(This,newVal)

#define IcwbxDatabaseUploadPCOptions_put_SendInfo(This,newVal)	\
    (This)->lpVtbl -> put_SendInfo(This,newVal)

#define IcwbxDatabaseUploadPCOptions_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadPCOptions_get_CodePage_Proxy( 
    IcwbxDatabaseUploadPCOptions * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxDatabaseUploadPCOptions_get_CodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadPCOptions_put_CodePage_Proxy( 
    IcwbxDatabaseUploadPCOptions * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseUploadPCOptions_put_CodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadPCOptions_put_SendInfo_Proxy( 
    IcwbxDatabaseUploadPCOptions * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseUploadPCOptions_put_SendInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadPCOptions_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseUploadPCOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadPCOptions_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseUploadPCOptions_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseUploadASCIIOptions_INTERFACE_DEFINED__
#define __IcwbxDatabaseUploadASCIIOptions_INTERFACE_DEFINED__

/* interface IcwbxDatabaseUploadASCIIOptions */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseUploadASCIIOptions;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("90F21460-D4DD-11D3-923D-002035AE9B5D")
    IcwbxDatabaseUploadASCIIOptions : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CodePage( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CodePage( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConvertTabs( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ConvertTabs( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_SendInfo( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseUploadASCIIOptionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseUploadASCIIOptions * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseUploadASCIIOptions * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseUploadASCIIOptions * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseUploadASCIIOptions * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseUploadASCIIOptions * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseUploadASCIIOptions * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseUploadASCIIOptions * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CodePage )( 
            IcwbxDatabaseUploadASCIIOptions * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CodePage )( 
            IcwbxDatabaseUploadASCIIOptions * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConvertTabs )( 
            IcwbxDatabaseUploadASCIIOptions * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ConvertTabs )( 
            IcwbxDatabaseUploadASCIIOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SendInfo )( 
            IcwbxDatabaseUploadASCIIOptions * This,
            /* [in] */ long newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseUploadASCIIOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IcwbxDatabaseUploadASCIIOptionsVtbl;

    interface IcwbxDatabaseUploadASCIIOptions
    {
        CONST_VTBL struct IcwbxDatabaseUploadASCIIOptionsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseUploadASCIIOptions_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseUploadASCIIOptions_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseUploadASCIIOptions_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseUploadASCIIOptions_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseUploadASCIIOptions_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseUploadASCIIOptions_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseUploadASCIIOptions_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseUploadASCIIOptions_get_CodePage(This,pVal)	\
    (This)->lpVtbl -> get_CodePage(This,pVal)

#define IcwbxDatabaseUploadASCIIOptions_put_CodePage(This,newVal)	\
    (This)->lpVtbl -> put_CodePage(This,newVal)

#define IcwbxDatabaseUploadASCIIOptions_get_ConvertTabs(This,pVal)	\
    (This)->lpVtbl -> get_ConvertTabs(This,pVal)

#define IcwbxDatabaseUploadASCIIOptions_put_ConvertTabs(This,newVal)	\
    (This)->lpVtbl -> put_ConvertTabs(This,newVal)

#define IcwbxDatabaseUploadASCIIOptions_put_SendInfo(This,newVal)	\
    (This)->lpVtbl -> put_SendInfo(This,newVal)

#define IcwbxDatabaseUploadASCIIOptions_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadASCIIOptions_get_CodePage_Proxy( 
    IcwbxDatabaseUploadASCIIOptions * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxDatabaseUploadASCIIOptions_get_CodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadASCIIOptions_put_CodePage_Proxy( 
    IcwbxDatabaseUploadASCIIOptions * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseUploadASCIIOptions_put_CodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadASCIIOptions_get_ConvertTabs_Proxy( 
    IcwbxDatabaseUploadASCIIOptions * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseUploadASCIIOptions_get_ConvertTabs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadASCIIOptions_put_ConvertTabs_Proxy( 
    IcwbxDatabaseUploadASCIIOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadASCIIOptions_put_ConvertTabs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadASCIIOptions_put_SendInfo_Proxy( 
    IcwbxDatabaseUploadASCIIOptions * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseUploadASCIIOptions_put_SendInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadASCIIOptions_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseUploadASCIIOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadASCIIOptions_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseUploadASCIIOptions_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseUploadUnicodeOptions_INTERFACE_DEFINED__
#define __IcwbxDatabaseUploadUnicodeOptions_INTERFACE_DEFINED__

/* interface IcwbxDatabaseUploadUnicodeOptions */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseUploadUnicodeOptions;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6CEAC38C-FF7C-4E64-A132-A7BB849814E1")
    IcwbxDatabaseUploadUnicodeOptions : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CodePage( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CodePage( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConvertTabs( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ConvertTabs( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_SendInfo( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseUploadUnicodeOptionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseUploadUnicodeOptions * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseUploadUnicodeOptions * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseUploadUnicodeOptions * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseUploadUnicodeOptions * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseUploadUnicodeOptions * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseUploadUnicodeOptions * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseUploadUnicodeOptions * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CodePage )( 
            IcwbxDatabaseUploadUnicodeOptions * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CodePage )( 
            IcwbxDatabaseUploadUnicodeOptions * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConvertTabs )( 
            IcwbxDatabaseUploadUnicodeOptions * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ConvertTabs )( 
            IcwbxDatabaseUploadUnicodeOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SendInfo )( 
            IcwbxDatabaseUploadUnicodeOptions * This,
            /* [in] */ long newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseUploadUnicodeOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IcwbxDatabaseUploadUnicodeOptionsVtbl;

    interface IcwbxDatabaseUploadUnicodeOptions
    {
        CONST_VTBL struct IcwbxDatabaseUploadUnicodeOptionsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseUploadUnicodeOptions_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseUploadUnicodeOptions_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseUploadUnicodeOptions_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseUploadUnicodeOptions_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseUploadUnicodeOptions_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseUploadUnicodeOptions_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseUploadUnicodeOptions_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseUploadUnicodeOptions_get_CodePage(This,pVal)	\
    (This)->lpVtbl -> get_CodePage(This,pVal)

#define IcwbxDatabaseUploadUnicodeOptions_put_CodePage(This,newVal)	\
    (This)->lpVtbl -> put_CodePage(This,newVal)

#define IcwbxDatabaseUploadUnicodeOptions_get_ConvertTabs(This,pVal)	\
    (This)->lpVtbl -> get_ConvertTabs(This,pVal)

#define IcwbxDatabaseUploadUnicodeOptions_put_ConvertTabs(This,newVal)	\
    (This)->lpVtbl -> put_ConvertTabs(This,newVal)

#define IcwbxDatabaseUploadUnicodeOptions_put_SendInfo(This,newVal)	\
    (This)->lpVtbl -> put_SendInfo(This,newVal)

#define IcwbxDatabaseUploadUnicodeOptions_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadUnicodeOptions_get_CodePage_Proxy( 
    IcwbxDatabaseUploadUnicodeOptions * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxDatabaseUploadUnicodeOptions_get_CodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadUnicodeOptions_put_CodePage_Proxy( 
    IcwbxDatabaseUploadUnicodeOptions * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseUploadUnicodeOptions_put_CodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadUnicodeOptions_get_ConvertTabs_Proxy( 
    IcwbxDatabaseUploadUnicodeOptions * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseUploadUnicodeOptions_get_ConvertTabs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadUnicodeOptions_put_ConvertTabs_Proxy( 
    IcwbxDatabaseUploadUnicodeOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadUnicodeOptions_put_ConvertTabs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadUnicodeOptions_put_SendInfo_Proxy( 
    IcwbxDatabaseUploadUnicodeOptions * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseUploadUnicodeOptions_put_SendInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadUnicodeOptions_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseUploadUnicodeOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadUnicodeOptions_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseUploadUnicodeOptions_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseUploadBIFFOptions2_INTERFACE_DEFINED__
#define __IcwbxDatabaseUploadBIFFOptions2_INTERFACE_DEFINED__

/* interface IcwbxDatabaseUploadBIFFOptions2 */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseUploadBIFFOptions2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FE897AB0-3895-4A92-A0fD-01A8914643E5")
    IcwbxDatabaseUploadBIFFOptions2 : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UploadExtraSheets( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UploadExtraSheets( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_SendInfo( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AllowNumericToCharConversion( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AllowNumericToCharConversion( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConvertDateAndTime( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ConvertDateAndTime( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseUploadBIFFOptions2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseUploadBIFFOptions2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseUploadBIFFOptions2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseUploadBIFFOptions2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseUploadBIFFOptions2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseUploadBIFFOptions2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseUploadBIFFOptions2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseUploadBIFFOptions2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UploadExtraSheets )( 
            IcwbxDatabaseUploadBIFFOptions2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UploadExtraSheets )( 
            IcwbxDatabaseUploadBIFFOptions2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseUploadBIFFOptions2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SendInfo )( 
            IcwbxDatabaseUploadBIFFOptions2 * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AllowNumericToCharConversion )( 
            IcwbxDatabaseUploadBIFFOptions2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AllowNumericToCharConversion )( 
            IcwbxDatabaseUploadBIFFOptions2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConvertDateAndTime )( 
            IcwbxDatabaseUploadBIFFOptions2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ConvertDateAndTime )( 
            IcwbxDatabaseUploadBIFFOptions2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IcwbxDatabaseUploadBIFFOptions2Vtbl;

    interface IcwbxDatabaseUploadBIFFOptions2
    {
        CONST_VTBL struct IcwbxDatabaseUploadBIFFOptions2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseUploadBIFFOptions2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseUploadBIFFOptions2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseUploadBIFFOptions2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseUploadBIFFOptions2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseUploadBIFFOptions2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseUploadBIFFOptions2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseUploadBIFFOptions2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseUploadBIFFOptions2_get_UploadExtraSheets(This,pVal)	\
    (This)->lpVtbl -> get_UploadExtraSheets(This,pVal)

#define IcwbxDatabaseUploadBIFFOptions2_put_UploadExtraSheets(This,newVal)	\
    (This)->lpVtbl -> put_UploadExtraSheets(This,newVal)

#define IcwbxDatabaseUploadBIFFOptions2_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#define IcwbxDatabaseUploadBIFFOptions2_put_SendInfo(This,newVal)	\
    (This)->lpVtbl -> put_SendInfo(This,newVal)

#define IcwbxDatabaseUploadBIFFOptions2_get_AllowNumericToCharConversion(This,pVal)	\
    (This)->lpVtbl -> get_AllowNumericToCharConversion(This,pVal)

#define IcwbxDatabaseUploadBIFFOptions2_put_AllowNumericToCharConversion(This,newVal)	\
    (This)->lpVtbl -> put_AllowNumericToCharConversion(This,newVal)

#define IcwbxDatabaseUploadBIFFOptions2_get_ConvertDateAndTime(This,pVal)	\
    (This)->lpVtbl -> get_ConvertDateAndTime(This,pVal)

#define IcwbxDatabaseUploadBIFFOptions2_put_ConvertDateAndTime(This,newVal)	\
    (This)->lpVtbl -> put_ConvertDateAndTime(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadBIFFOptions2_get_UploadExtraSheets_Proxy( 
    IcwbxDatabaseUploadBIFFOptions2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseUploadBIFFOptions2_get_UploadExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadBIFFOptions2_put_UploadExtraSheets_Proxy( 
    IcwbxDatabaseUploadBIFFOptions2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadBIFFOptions2_put_UploadExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadBIFFOptions2_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseUploadBIFFOptions2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadBIFFOptions2_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadBIFFOptions2_put_SendInfo_Proxy( 
    IcwbxDatabaseUploadBIFFOptions2 * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseUploadBIFFOptions2_put_SendInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadBIFFOptions2_get_AllowNumericToCharConversion_Proxy( 
    IcwbxDatabaseUploadBIFFOptions2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseUploadBIFFOptions2_get_AllowNumericToCharConversion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadBIFFOptions2_put_AllowNumericToCharConversion_Proxy( 
    IcwbxDatabaseUploadBIFFOptions2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadBIFFOptions2_put_AllowNumericToCharConversion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadBIFFOptions2_get_ConvertDateAndTime_Proxy( 
    IcwbxDatabaseUploadBIFFOptions2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseUploadBIFFOptions2_get_ConvertDateAndTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadBIFFOptions2_put_ConvertDateAndTime_Proxy( 
    IcwbxDatabaseUploadBIFFOptions2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadBIFFOptions2_put_ConvertDateAndTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseUploadBIFFOptions2_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseUploadWK4Options_INTERFACE_DEFINED__
#define __IcwbxDatabaseUploadWK4Options_INTERFACE_DEFINED__

/* interface IcwbxDatabaseUploadWK4Options */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseUploadWK4Options;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4A8AFC53-A8D9-11D3-91F5-002035AE9B5D")
    IcwbxDatabaseUploadWK4Options : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UploadExtraSheets( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UploadExtraSheets( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_SendInfo( 
            /* [in] */ long newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseUploadWK4OptionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseUploadWK4Options * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseUploadWK4Options * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseUploadWK4Options * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseUploadWK4Options * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseUploadWK4Options * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseUploadWK4Options * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseUploadWK4Options * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UploadExtraSheets )( 
            IcwbxDatabaseUploadWK4Options * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UploadExtraSheets )( 
            IcwbxDatabaseUploadWK4Options * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseUploadWK4Options * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SendInfo )( 
            IcwbxDatabaseUploadWK4Options * This,
            /* [in] */ long newVal);
        
        END_INTERFACE
    } IcwbxDatabaseUploadWK4OptionsVtbl;

    interface IcwbxDatabaseUploadWK4Options
    {
        CONST_VTBL struct IcwbxDatabaseUploadWK4OptionsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseUploadWK4Options_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseUploadWK4Options_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseUploadWK4Options_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseUploadWK4Options_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseUploadWK4Options_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseUploadWK4Options_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseUploadWK4Options_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseUploadWK4Options_get_UploadExtraSheets(This,pVal)	\
    (This)->lpVtbl -> get_UploadExtraSheets(This,pVal)

#define IcwbxDatabaseUploadWK4Options_put_UploadExtraSheets(This,newVal)	\
    (This)->lpVtbl -> put_UploadExtraSheets(This,newVal)

#define IcwbxDatabaseUploadWK4Options_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#define IcwbxDatabaseUploadWK4Options_put_SendInfo(This,newVal)	\
    (This)->lpVtbl -> put_SendInfo(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadWK4Options_get_UploadExtraSheets_Proxy( 
    IcwbxDatabaseUploadWK4Options * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseUploadWK4Options_get_UploadExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadWK4Options_put_UploadExtraSheets_Proxy( 
    IcwbxDatabaseUploadWK4Options * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadWK4Options_put_UploadExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadWK4Options_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseUploadWK4Options * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadWK4Options_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadWK4Options_put_SendInfo_Proxy( 
    IcwbxDatabaseUploadWK4Options * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseUploadWK4Options_put_SendInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseUploadWK4Options_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseUploadExcelXMLOptions_INTERFACE_DEFINED__
#define __IcwbxDatabaseUploadExcelXMLOptions_INTERFACE_DEFINED__

/* interface IcwbxDatabaseUploadExcelXMLOptions */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseUploadExcelXMLOptions;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EC642004-3B3B-4ad9-803F-7421A8564793")
    IcwbxDatabaseUploadExcelXMLOptions : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UploadExtraSheets( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UploadExtraSheets( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_SendInfo( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AllowNumericToCharConversion( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AllowNumericToCharConversion( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConvertDateAndTime( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ConvertDateAndTime( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseUploadExcelXMLOptionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseUploadExcelXMLOptions * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseUploadExcelXMLOptions * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseUploadExcelXMLOptions * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseUploadExcelXMLOptions * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseUploadExcelXMLOptions * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseUploadExcelXMLOptions * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseUploadExcelXMLOptions * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UploadExtraSheets )( 
            IcwbxDatabaseUploadExcelXMLOptions * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UploadExtraSheets )( 
            IcwbxDatabaseUploadExcelXMLOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseUploadExcelXMLOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SendInfo )( 
            IcwbxDatabaseUploadExcelXMLOptions * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AllowNumericToCharConversion )( 
            IcwbxDatabaseUploadExcelXMLOptions * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AllowNumericToCharConversion )( 
            IcwbxDatabaseUploadExcelXMLOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConvertDateAndTime )( 
            IcwbxDatabaseUploadExcelXMLOptions * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ConvertDateAndTime )( 
            IcwbxDatabaseUploadExcelXMLOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IcwbxDatabaseUploadExcelXMLOptionsVtbl;

    interface IcwbxDatabaseUploadExcelXMLOptions
    {
        CONST_VTBL struct IcwbxDatabaseUploadExcelXMLOptionsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseUploadExcelXMLOptions_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseUploadExcelXMLOptions_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseUploadExcelXMLOptions_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseUploadExcelXMLOptions_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseUploadExcelXMLOptions_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseUploadExcelXMLOptions_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseUploadExcelXMLOptions_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseUploadExcelXMLOptions_get_UploadExtraSheets(This,pVal)	\
    (This)->lpVtbl -> get_UploadExtraSheets(This,pVal)

#define IcwbxDatabaseUploadExcelXMLOptions_put_UploadExtraSheets(This,newVal)	\
    (This)->lpVtbl -> put_UploadExtraSheets(This,newVal)

#define IcwbxDatabaseUploadExcelXMLOptions_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#define IcwbxDatabaseUploadExcelXMLOptions_put_SendInfo(This,newVal)	\
    (This)->lpVtbl -> put_SendInfo(This,newVal)

#define IcwbxDatabaseUploadExcelXMLOptions_get_AllowNumericToCharConversion(This,pVal)	\
    (This)->lpVtbl -> get_AllowNumericToCharConversion(This,pVal)

#define IcwbxDatabaseUploadExcelXMLOptions_put_AllowNumericToCharConversion(This,newVal)	\
    (This)->lpVtbl -> put_AllowNumericToCharConversion(This,newVal)

#define IcwbxDatabaseUploadExcelXMLOptions_get_ConvertDateAndTime(This,pVal)	\
    (This)->lpVtbl -> get_ConvertDateAndTime(This,pVal)

#define IcwbxDatabaseUploadExcelXMLOptions_put_ConvertDateAndTime(This,newVal)	\
    (This)->lpVtbl -> put_ConvertDateAndTime(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadExcelXMLOptions_get_UploadExtraSheets_Proxy( 
    IcwbxDatabaseUploadExcelXMLOptions * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseUploadExcelXMLOptions_get_UploadExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadExcelXMLOptions_put_UploadExtraSheets_Proxy( 
    IcwbxDatabaseUploadExcelXMLOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadExcelXMLOptions_put_UploadExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadExcelXMLOptions_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseUploadExcelXMLOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadExcelXMLOptions_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadExcelXMLOptions_put_SendInfo_Proxy( 
    IcwbxDatabaseUploadExcelXMLOptions * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseUploadExcelXMLOptions_put_SendInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadExcelXMLOptions_get_AllowNumericToCharConversion_Proxy( 
    IcwbxDatabaseUploadExcelXMLOptions * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseUploadExcelXMLOptions_get_AllowNumericToCharConversion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadExcelXMLOptions_put_AllowNumericToCharConversion_Proxy( 
    IcwbxDatabaseUploadExcelXMLOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadExcelXMLOptions_put_AllowNumericToCharConversion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadExcelXMLOptions_get_ConvertDateAndTime_Proxy( 
    IcwbxDatabaseUploadExcelXMLOptions * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseUploadExcelXMLOptions_get_ConvertDateAndTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUploadExcelXMLOptions_put_ConvertDateAndTime_Proxy( 
    IcwbxDatabaseUploadExcelXMLOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUploadExcelXMLOptions_put_ConvertDateAndTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseUploadExcelXMLOptions_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseUpload123Options_INTERFACE_DEFINED__
#define __IcwbxDatabaseUpload123Options_INTERFACE_DEFINED__

/* interface IcwbxDatabaseUpload123Options */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseUpload123Options;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4A8AFC55-A8D9-11D3-91F5-002035AE9B5D")
    IcwbxDatabaseUpload123Options : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UploadExtraSheets( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UploadExtraSheets( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_SendInfo( 
            /* [in] */ long newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseUpload123OptionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseUpload123Options * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseUpload123Options * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseUpload123Options * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseUpload123Options * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseUpload123Options * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseUpload123Options * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseUpload123Options * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UploadExtraSheets )( 
            IcwbxDatabaseUpload123Options * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UploadExtraSheets )( 
            IcwbxDatabaseUpload123Options * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseUpload123Options * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SendInfo )( 
            IcwbxDatabaseUpload123Options * This,
            /* [in] */ long newVal);
        
        END_INTERFACE
    } IcwbxDatabaseUpload123OptionsVtbl;

    interface IcwbxDatabaseUpload123Options
    {
        CONST_VTBL struct IcwbxDatabaseUpload123OptionsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseUpload123Options_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseUpload123Options_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseUpload123Options_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseUpload123Options_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseUpload123Options_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseUpload123Options_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseUpload123Options_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseUpload123Options_get_UploadExtraSheets(This,pVal)	\
    (This)->lpVtbl -> get_UploadExtraSheets(This,pVal)

#define IcwbxDatabaseUpload123Options_put_UploadExtraSheets(This,newVal)	\
    (This)->lpVtbl -> put_UploadExtraSheets(This,newVal)

#define IcwbxDatabaseUpload123Options_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#define IcwbxDatabaseUpload123Options_put_SendInfo(This,newVal)	\
    (This)->lpVtbl -> put_SendInfo(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUpload123Options_get_UploadExtraSheets_Proxy( 
    IcwbxDatabaseUpload123Options * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseUpload123Options_get_UploadExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUpload123Options_put_UploadExtraSheets_Proxy( 
    IcwbxDatabaseUpload123Options * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUpload123Options_put_UploadExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUpload123Options_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseUpload123Options * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUpload123Options_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUpload123Options_put_SendInfo_Proxy( 
    IcwbxDatabaseUpload123Options * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseUpload123Options_put_SendInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseUpload123Options_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadPCFile_INTERFACE_DEFINED__
#define __IcwbxDatabaseDownloadPCFile_INTERFACE_DEFINED__

/* interface IcwbxDatabaseDownloadPCFile */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseDownloadPCFile;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1582B020-3F56-11D3-8392-ECC0749E73CB")
    IcwbxDatabaseDownloadPCFile : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileType( 
            /* [retval][out] */ cwbdtFileTypeEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FileType( 
            /* [in] */ cwbdtFileTypeEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Options( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReceiveInfo( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [restricted][id] */ HRESULT STDMETHODCALLTYPE InactivateOptions( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseDownloadPCFileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseDownloadPCFile * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseDownloadPCFile * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseDownloadPCFile * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseDownloadPCFile * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseDownloadPCFile * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseDownloadPCFile * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseDownloadPCFile * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IcwbxDatabaseDownloadPCFile * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IcwbxDatabaseDownloadPCFile * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FileType )( 
            IcwbxDatabaseDownloadPCFile * This,
            /* [retval][out] */ cwbdtFileTypeEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FileType )( 
            IcwbxDatabaseDownloadPCFile * This,
            /* [in] */ cwbdtFileTypeEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Options )( 
            IcwbxDatabaseDownloadPCFile * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ReceiveInfo )( 
            IcwbxDatabaseDownloadPCFile * This,
            /* [in] */ long newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseDownloadPCFile * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [restricted][id] */ HRESULT ( STDMETHODCALLTYPE *InactivateOptions )( 
            IcwbxDatabaseDownloadPCFile * This);
        
        END_INTERFACE
    } IcwbxDatabaseDownloadPCFileVtbl;

    interface IcwbxDatabaseDownloadPCFile
    {
        CONST_VTBL struct IcwbxDatabaseDownloadPCFileVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseDownloadPCFile_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseDownloadPCFile_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseDownloadPCFile_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseDownloadPCFile_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseDownloadPCFile_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseDownloadPCFile_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseDownloadPCFile_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseDownloadPCFile_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IcwbxDatabaseDownloadPCFile_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IcwbxDatabaseDownloadPCFile_get_FileType(This,pVal)	\
    (This)->lpVtbl -> get_FileType(This,pVal)

#define IcwbxDatabaseDownloadPCFile_put_FileType(This,newVal)	\
    (This)->lpVtbl -> put_FileType(This,newVal)

#define IcwbxDatabaseDownloadPCFile_get_Options(This,pVal)	\
    (This)->lpVtbl -> get_Options(This,pVal)

#define IcwbxDatabaseDownloadPCFile_put_ReceiveInfo(This,newVal)	\
    (This)->lpVtbl -> put_ReceiveInfo(This,newVal)

#define IcwbxDatabaseDownloadPCFile_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#define IcwbxDatabaseDownloadPCFile_InactivateOptions(This)	\
    (This)->lpVtbl -> InactivateOptions(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadPCFile_get_Name_Proxy( 
    IcwbxDatabaseDownloadPCFile * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseDownloadPCFile_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadPCFile_put_Name_Proxy( 
    IcwbxDatabaseDownloadPCFile * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseDownloadPCFile_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadPCFile_get_FileType_Proxy( 
    IcwbxDatabaseDownloadPCFile * This,
    /* [retval][out] */ cwbdtFileTypeEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadPCFile_get_FileType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadPCFile_put_FileType_Proxy( 
    IcwbxDatabaseDownloadPCFile * This,
    /* [in] */ cwbdtFileTypeEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadPCFile_put_FileType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadPCFile_get_Options_Proxy( 
    IcwbxDatabaseDownloadPCFile * This,
    /* [retval][out] */ VARIANT *pVal);


void __RPC_STUB IcwbxDatabaseDownloadPCFile_get_Options_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadPCFile_put_ReceiveInfo_Proxy( 
    IcwbxDatabaseDownloadPCFile * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownloadPCFile_put_ReceiveInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadPCFile_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseDownloadPCFile * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadPCFile_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadPCFile_InactivateOptions_Proxy( 
    IcwbxDatabaseDownloadPCFile * This);


void __RPC_STUB IcwbxDatabaseDownloadPCFile_InactivateOptions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseDownloadPCFile_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadPCOptions2_INTERFACE_DEFINED__
#define __IcwbxDatabaseDownloadPCOptions2_INTERFACE_DEFINED__

/* interface IcwbxDatabaseDownloadPCOptions2 */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseDownloadPCOptions2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5994D077-F9FF-4E5E-97C4-6DB356D8C6A2")
    IcwbxDatabaseDownloadPCOptions2 : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CodePage( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CodePage( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExistingFileOption( 
            /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ExistingFileOption( 
            /* [in] */ cwbdtExistingOutputFileEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_fileDescriptionFile( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_fileDescriptionFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReceiveInfo( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileDescriptionFileFormat( 
            /* [retval][out] */ cwbdtFDFFormatEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FileDescriptionFileFormat( 
            /* [in] */ cwbdtFDFFormatEnum newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseDownloadPCOptions2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseDownloadPCOptions2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseDownloadPCOptions2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseDownloadPCOptions2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseDownloadPCOptions2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseDownloadPCOptions2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseDownloadPCOptions2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseDownloadPCOptions2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CodePage )( 
            IcwbxDatabaseDownloadPCOptions2 * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CodePage )( 
            IcwbxDatabaseDownloadPCOptions2 * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExistingFileOption )( 
            IcwbxDatabaseDownloadPCOptions2 * This,
            /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExistingFileOption )( 
            IcwbxDatabaseDownloadPCOptions2 * This,
            /* [in] */ cwbdtExistingOutputFileEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fileDescriptionFile )( 
            IcwbxDatabaseDownloadPCOptions2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fileDescriptionFile )( 
            IcwbxDatabaseDownloadPCOptions2 * This,
            /* [in] */ BSTR newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ReceiveInfo )( 
            IcwbxDatabaseDownloadPCOptions2 * This,
            /* [in] */ long newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseDownloadPCOptions2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FileDescriptionFileFormat )( 
            IcwbxDatabaseDownloadPCOptions2 * This,
            /* [retval][out] */ cwbdtFDFFormatEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FileDescriptionFileFormat )( 
            IcwbxDatabaseDownloadPCOptions2 * This,
            /* [in] */ cwbdtFDFFormatEnum newVal);
        
        END_INTERFACE
    } IcwbxDatabaseDownloadPCOptions2Vtbl;

    interface IcwbxDatabaseDownloadPCOptions2
    {
        CONST_VTBL struct IcwbxDatabaseDownloadPCOptions2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseDownloadPCOptions2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseDownloadPCOptions2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseDownloadPCOptions2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseDownloadPCOptions2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseDownloadPCOptions2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseDownloadPCOptions2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseDownloadPCOptions2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseDownloadPCOptions2_get_CodePage(This,pVal)	\
    (This)->lpVtbl -> get_CodePage(This,pVal)

#define IcwbxDatabaseDownloadPCOptions2_put_CodePage(This,newVal)	\
    (This)->lpVtbl -> put_CodePage(This,newVal)

#define IcwbxDatabaseDownloadPCOptions2_get_ExistingFileOption(This,pVal)	\
    (This)->lpVtbl -> get_ExistingFileOption(This,pVal)

#define IcwbxDatabaseDownloadPCOptions2_put_ExistingFileOption(This,newVal)	\
    (This)->lpVtbl -> put_ExistingFileOption(This,newVal)

#define IcwbxDatabaseDownloadPCOptions2_get_fileDescriptionFile(This,pVal)	\
    (This)->lpVtbl -> get_fileDescriptionFile(This,pVal)

#define IcwbxDatabaseDownloadPCOptions2_put_fileDescriptionFile(This,newVal)	\
    (This)->lpVtbl -> put_fileDescriptionFile(This,newVal)

#define IcwbxDatabaseDownloadPCOptions2_put_ReceiveInfo(This,newVal)	\
    (This)->lpVtbl -> put_ReceiveInfo(This,newVal)

#define IcwbxDatabaseDownloadPCOptions2_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#define IcwbxDatabaseDownloadPCOptions2_get_FileDescriptionFileFormat(This,pVal)	\
    (This)->lpVtbl -> get_FileDescriptionFileFormat(This,pVal)

#define IcwbxDatabaseDownloadPCOptions2_put_FileDescriptionFileFormat(This,newVal)	\
    (This)->lpVtbl -> put_FileDescriptionFileFormat(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadPCOptions2_get_CodePage_Proxy( 
    IcwbxDatabaseDownloadPCOptions2 * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxDatabaseDownloadPCOptions2_get_CodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadPCOptions2_put_CodePage_Proxy( 
    IcwbxDatabaseDownloadPCOptions2 * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownloadPCOptions2_put_CodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadPCOptions2_get_ExistingFileOption_Proxy( 
    IcwbxDatabaseDownloadPCOptions2 * This,
    /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadPCOptions2_get_ExistingFileOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadPCOptions2_put_ExistingFileOption_Proxy( 
    IcwbxDatabaseDownloadPCOptions2 * This,
    /* [in] */ cwbdtExistingOutputFileEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadPCOptions2_put_ExistingFileOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadPCOptions2_get_fileDescriptionFile_Proxy( 
    IcwbxDatabaseDownloadPCOptions2 * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseDownloadPCOptions2_get_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadPCOptions2_put_fileDescriptionFile_Proxy( 
    IcwbxDatabaseDownloadPCOptions2 * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseDownloadPCOptions2_put_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadPCOptions2_put_ReceiveInfo_Proxy( 
    IcwbxDatabaseDownloadPCOptions2 * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownloadPCOptions2_put_ReceiveInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadPCOptions2_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseDownloadPCOptions2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadPCOptions2_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadPCOptions2_get_FileDescriptionFileFormat_Proxy( 
    IcwbxDatabaseDownloadPCOptions2 * This,
    /* [retval][out] */ cwbdtFDFFormatEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadPCOptions2_get_FileDescriptionFileFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadPCOptions2_put_FileDescriptionFileFormat_Proxy( 
    IcwbxDatabaseDownloadPCOptions2 * This,
    /* [in] */ cwbdtFDFFormatEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadPCOptions2_put_FileDescriptionFileFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseDownloadPCOptions2_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadASCIIOptions2_INTERFACE_DEFINED__
#define __IcwbxDatabaseDownloadASCIIOptions2_INTERFACE_DEFINED__

/* interface IcwbxDatabaseDownloadASCIIOptions2 */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseDownloadASCIIOptions2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8349D4B3-B904-4908-B682-B889EA393EFC")
    IcwbxDatabaseDownloadASCIIOptions2 : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AppendEOFIndicator( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AppendEOFIndicator( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CodePage( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CodePage( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExistingFileOption( 
            /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ExistingFileOption( 
            /* [in] */ cwbdtExistingOutputFileEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_fileDescriptionFile( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_fileDescriptionFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IncludeLeadingZeros( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IncludeLeadingZeros( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TruncateSpaces( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TruncateSpaces( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReceiveInfo( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileDescriptionFileFormat( 
            /* [retval][out] */ cwbdtFDFFormatEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FileDescriptionFileFormat( 
            /* [in] */ cwbdtFDFFormatEnum newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseDownloadASCIIOptions2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseDownloadASCIIOptions2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseDownloadASCIIOptions2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseDownloadASCIIOptions2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseDownloadASCIIOptions2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseDownloadASCIIOptions2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseDownloadASCIIOptions2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseDownloadASCIIOptions2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AppendEOFIndicator )( 
            IcwbxDatabaseDownloadASCIIOptions2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AppendEOFIndicator )( 
            IcwbxDatabaseDownloadASCIIOptions2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CodePage )( 
            IcwbxDatabaseDownloadASCIIOptions2 * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CodePage )( 
            IcwbxDatabaseDownloadASCIIOptions2 * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExistingFileOption )( 
            IcwbxDatabaseDownloadASCIIOptions2 * This,
            /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExistingFileOption )( 
            IcwbxDatabaseDownloadASCIIOptions2 * This,
            /* [in] */ cwbdtExistingOutputFileEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fileDescriptionFile )( 
            IcwbxDatabaseDownloadASCIIOptions2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fileDescriptionFile )( 
            IcwbxDatabaseDownloadASCIIOptions2 * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IncludeLeadingZeros )( 
            IcwbxDatabaseDownloadASCIIOptions2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IncludeLeadingZeros )( 
            IcwbxDatabaseDownloadASCIIOptions2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TruncateSpaces )( 
            IcwbxDatabaseDownloadASCIIOptions2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TruncateSpaces )( 
            IcwbxDatabaseDownloadASCIIOptions2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ReceiveInfo )( 
            IcwbxDatabaseDownloadASCIIOptions2 * This,
            /* [in] */ long newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseDownloadASCIIOptions2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FileDescriptionFileFormat )( 
            IcwbxDatabaseDownloadASCIIOptions2 * This,
            /* [retval][out] */ cwbdtFDFFormatEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FileDescriptionFileFormat )( 
            IcwbxDatabaseDownloadASCIIOptions2 * This,
            /* [in] */ cwbdtFDFFormatEnum newVal);
        
        END_INTERFACE
    } IcwbxDatabaseDownloadASCIIOptions2Vtbl;

    interface IcwbxDatabaseDownloadASCIIOptions2
    {
        CONST_VTBL struct IcwbxDatabaseDownloadASCIIOptions2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseDownloadASCIIOptions2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseDownloadASCIIOptions2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseDownloadASCIIOptions2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseDownloadASCIIOptions2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseDownloadASCIIOptions2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseDownloadASCIIOptions2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseDownloadASCIIOptions2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseDownloadASCIIOptions2_get_AppendEOFIndicator(This,pVal)	\
    (This)->lpVtbl -> get_AppendEOFIndicator(This,pVal)

#define IcwbxDatabaseDownloadASCIIOptions2_put_AppendEOFIndicator(This,newVal)	\
    (This)->lpVtbl -> put_AppendEOFIndicator(This,newVal)

#define IcwbxDatabaseDownloadASCIIOptions2_get_CodePage(This,pVal)	\
    (This)->lpVtbl -> get_CodePage(This,pVal)

#define IcwbxDatabaseDownloadASCIIOptions2_put_CodePage(This,newVal)	\
    (This)->lpVtbl -> put_CodePage(This,newVal)

#define IcwbxDatabaseDownloadASCIIOptions2_get_ExistingFileOption(This,pVal)	\
    (This)->lpVtbl -> get_ExistingFileOption(This,pVal)

#define IcwbxDatabaseDownloadASCIIOptions2_put_ExistingFileOption(This,newVal)	\
    (This)->lpVtbl -> put_ExistingFileOption(This,newVal)

#define IcwbxDatabaseDownloadASCIIOptions2_get_fileDescriptionFile(This,pVal)	\
    (This)->lpVtbl -> get_fileDescriptionFile(This,pVal)

#define IcwbxDatabaseDownloadASCIIOptions2_put_fileDescriptionFile(This,newVal)	\
    (This)->lpVtbl -> put_fileDescriptionFile(This,newVal)

#define IcwbxDatabaseDownloadASCIIOptions2_get_IncludeLeadingZeros(This,pVal)	\
    (This)->lpVtbl -> get_IncludeLeadingZeros(This,pVal)

#define IcwbxDatabaseDownloadASCIIOptions2_put_IncludeLeadingZeros(This,newVal)	\
    (This)->lpVtbl -> put_IncludeLeadingZeros(This,newVal)

#define IcwbxDatabaseDownloadASCIIOptions2_get_TruncateSpaces(This,pVal)	\
    (This)->lpVtbl -> get_TruncateSpaces(This,pVal)

#define IcwbxDatabaseDownloadASCIIOptions2_put_TruncateSpaces(This,newVal)	\
    (This)->lpVtbl -> put_TruncateSpaces(This,newVal)

#define IcwbxDatabaseDownloadASCIIOptions2_put_ReceiveInfo(This,newVal)	\
    (This)->lpVtbl -> put_ReceiveInfo(This,newVal)

#define IcwbxDatabaseDownloadASCIIOptions2_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#define IcwbxDatabaseDownloadASCIIOptions2_get_FileDescriptionFileFormat(This,pVal)	\
    (This)->lpVtbl -> get_FileDescriptionFileFormat(This,pVal)

#define IcwbxDatabaseDownloadASCIIOptions2_put_FileDescriptionFileFormat(This,newVal)	\
    (This)->lpVtbl -> put_FileDescriptionFileFormat(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions2_get_AppendEOFIndicator_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions2_get_AppendEOFIndicator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions2_put_AppendEOFIndicator_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions2_put_AppendEOFIndicator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions2_get_CodePage_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions2 * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions2_get_CodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions2_put_CodePage_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions2 * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions2_put_CodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions2_get_ExistingFileOption_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions2 * This,
    /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions2_get_ExistingFileOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions2_put_ExistingFileOption_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions2 * This,
    /* [in] */ cwbdtExistingOutputFileEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions2_put_ExistingFileOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions2_get_fileDescriptionFile_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions2 * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions2_get_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions2_put_fileDescriptionFile_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions2 * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions2_put_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions2_get_IncludeLeadingZeros_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions2_get_IncludeLeadingZeros_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions2_put_IncludeLeadingZeros_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions2_put_IncludeLeadingZeros_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions2_get_TruncateSpaces_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions2_get_TruncateSpaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions2_put_TruncateSpaces_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions2_put_TruncateSpaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions2_put_ReceiveInfo_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions2 * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions2_put_ReceiveInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions2_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions2_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions2_get_FileDescriptionFileFormat_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions2 * This,
    /* [retval][out] */ cwbdtFDFFormatEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions2_get_FileDescriptionFileFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadASCIIOptions2_put_FileDescriptionFileFormat_Proxy( 
    IcwbxDatabaseDownloadASCIIOptions2 * This,
    /* [in] */ cwbdtFDFFormatEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadASCIIOptions2_put_FileDescriptionFileFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseDownloadASCIIOptions2_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadTabDelimitedOptions2_INTERFACE_DEFINED__
#define __IcwbxDatabaseDownloadTabDelimitedOptions2_INTERFACE_DEFINED__

/* interface IcwbxDatabaseDownloadTabDelimitedOptions2 */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseDownloadTabDelimitedOptions2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B377C305-ADA6-4BB1-B5D8-1CD612A687BF")
    IcwbxDatabaseDownloadTabDelimitedOptions2 : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CodePage( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CodePage( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExistingFileOption( 
            /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ExistingFileOption( 
            /* [in] */ cwbdtExistingOutputFileEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_fileDescriptionFile( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_fileDescriptionFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RemoveLeadingNumericSpaces( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RemoveLeadingNumericSpaces( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RemoveTrailingCharSpaces( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RemoveTrailingCharSpaces( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReceiveInfo( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileDescriptionFileFormat( 
            /* [retval][out] */ cwbdtFDFFormatEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FileDescriptionFileFormat( 
            /* [in] */ cwbdtFDFFormatEnum newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseDownloadTabDelimitedOptions2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseDownloadTabDelimitedOptions2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseDownloadTabDelimitedOptions2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CodePage )( 
            IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CodePage )( 
            IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExistingFileOption )( 
            IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
            /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExistingFileOption )( 
            IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
            /* [in] */ cwbdtExistingOutputFileEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fileDescriptionFile )( 
            IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fileDescriptionFile )( 
            IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RemoveLeadingNumericSpaces )( 
            IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RemoveLeadingNumericSpaces )( 
            IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RemoveTrailingCharSpaces )( 
            IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RemoveTrailingCharSpaces )( 
            IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ReceiveInfo )( 
            IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
            /* [in] */ long newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FileDescriptionFileFormat )( 
            IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
            /* [retval][out] */ cwbdtFDFFormatEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FileDescriptionFileFormat )( 
            IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
            /* [in] */ cwbdtFDFFormatEnum newVal);
        
        END_INTERFACE
    } IcwbxDatabaseDownloadTabDelimitedOptions2Vtbl;

    interface IcwbxDatabaseDownloadTabDelimitedOptions2
    {
        CONST_VTBL struct IcwbxDatabaseDownloadTabDelimitedOptions2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseDownloadTabDelimitedOptions2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseDownloadTabDelimitedOptions2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseDownloadTabDelimitedOptions2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseDownloadTabDelimitedOptions2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseDownloadTabDelimitedOptions2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseDownloadTabDelimitedOptions2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseDownloadTabDelimitedOptions2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseDownloadTabDelimitedOptions2_get_CodePage(This,pVal)	\
    (This)->lpVtbl -> get_CodePage(This,pVal)

#define IcwbxDatabaseDownloadTabDelimitedOptions2_put_CodePage(This,newVal)	\
    (This)->lpVtbl -> put_CodePage(This,newVal)

#define IcwbxDatabaseDownloadTabDelimitedOptions2_get_ExistingFileOption(This,pVal)	\
    (This)->lpVtbl -> get_ExistingFileOption(This,pVal)

#define IcwbxDatabaseDownloadTabDelimitedOptions2_put_ExistingFileOption(This,newVal)	\
    (This)->lpVtbl -> put_ExistingFileOption(This,newVal)

#define IcwbxDatabaseDownloadTabDelimitedOptions2_get_fileDescriptionFile(This,pVal)	\
    (This)->lpVtbl -> get_fileDescriptionFile(This,pVal)

#define IcwbxDatabaseDownloadTabDelimitedOptions2_put_fileDescriptionFile(This,newVal)	\
    (This)->lpVtbl -> put_fileDescriptionFile(This,newVal)

#define IcwbxDatabaseDownloadTabDelimitedOptions2_get_RemoveLeadingNumericSpaces(This,pVal)	\
    (This)->lpVtbl -> get_RemoveLeadingNumericSpaces(This,pVal)

#define IcwbxDatabaseDownloadTabDelimitedOptions2_put_RemoveLeadingNumericSpaces(This,newVal)	\
    (This)->lpVtbl -> put_RemoveLeadingNumericSpaces(This,newVal)

#define IcwbxDatabaseDownloadTabDelimitedOptions2_get_RemoveTrailingCharSpaces(This,pVal)	\
    (This)->lpVtbl -> get_RemoveTrailingCharSpaces(This,pVal)

#define IcwbxDatabaseDownloadTabDelimitedOptions2_put_RemoveTrailingCharSpaces(This,newVal)	\
    (This)->lpVtbl -> put_RemoveTrailingCharSpaces(This,newVal)

#define IcwbxDatabaseDownloadTabDelimitedOptions2_put_ReceiveInfo(This,newVal)	\
    (This)->lpVtbl -> put_ReceiveInfo(This,newVal)

#define IcwbxDatabaseDownloadTabDelimitedOptions2_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#define IcwbxDatabaseDownloadTabDelimitedOptions2_get_FileDescriptionFileFormat(This,pVal)	\
    (This)->lpVtbl -> get_FileDescriptionFileFormat(This,pVal)

#define IcwbxDatabaseDownloadTabDelimitedOptions2_put_FileDescriptionFileFormat(This,newVal)	\
    (This)->lpVtbl -> put_FileDescriptionFileFormat(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadTabDelimitedOptions2_get_CodePage_Proxy( 
    IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxDatabaseDownloadTabDelimitedOptions2_get_CodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadTabDelimitedOptions2_put_CodePage_Proxy( 
    IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownloadTabDelimitedOptions2_put_CodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadTabDelimitedOptions2_get_ExistingFileOption_Proxy( 
    IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
    /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadTabDelimitedOptions2_get_ExistingFileOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadTabDelimitedOptions2_put_ExistingFileOption_Proxy( 
    IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
    /* [in] */ cwbdtExistingOutputFileEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadTabDelimitedOptions2_put_ExistingFileOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadTabDelimitedOptions2_get_fileDescriptionFile_Proxy( 
    IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseDownloadTabDelimitedOptions2_get_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadTabDelimitedOptions2_put_fileDescriptionFile_Proxy( 
    IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseDownloadTabDelimitedOptions2_put_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadTabDelimitedOptions2_get_RemoveLeadingNumericSpaces_Proxy( 
    IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadTabDelimitedOptions2_get_RemoveLeadingNumericSpaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadTabDelimitedOptions2_put_RemoveLeadingNumericSpaces_Proxy( 
    IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadTabDelimitedOptions2_put_RemoveLeadingNumericSpaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadTabDelimitedOptions2_get_RemoveTrailingCharSpaces_Proxy( 
    IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadTabDelimitedOptions2_get_RemoveTrailingCharSpaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadTabDelimitedOptions2_put_RemoveTrailingCharSpaces_Proxy( 
    IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadTabDelimitedOptions2_put_RemoveTrailingCharSpaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadTabDelimitedOptions2_put_ReceiveInfo_Proxy( 
    IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownloadTabDelimitedOptions2_put_ReceiveInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadTabDelimitedOptions2_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadTabDelimitedOptions2_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadTabDelimitedOptions2_get_FileDescriptionFileFormat_Proxy( 
    IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
    /* [retval][out] */ cwbdtFDFFormatEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadTabDelimitedOptions2_get_FileDescriptionFileFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadTabDelimitedOptions2_put_FileDescriptionFileFormat_Proxy( 
    IcwbxDatabaseDownloadTabDelimitedOptions2 * This,
    /* [in] */ cwbdtFDFFormatEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadTabDelimitedOptions2_put_FileDescriptionFileFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseDownloadTabDelimitedOptions2_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadBIFFOptions2_INTERFACE_DEFINED__
#define __IcwbxDatabaseDownloadBIFFOptions2_INTERFACE_DEFINED__

/* interface IcwbxDatabaseDownloadBIFFOptions2 */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseDownloadBIFFOptions2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A50723C4-C5BB-41AC-8F4F-33259258DB8E")
    IcwbxDatabaseDownloadBIFFOptions2 : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CreateExtraSheets( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CreateExtraSheets( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExistingFileOption( 
            /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ExistingFileOption( 
            /* [in] */ cwbdtExistingOutputFileEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_fileDescriptionFile( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_fileDescriptionFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HeadingsOnExtraSheets( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HeadingsOnExtraSheets( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HeadingsOnFirstSheet( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HeadingsOnFirstSheet( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReceiveInfo( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileDescriptionFileFormat( 
            /* [retval][out] */ cwbdtFDFFormatEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FileDescriptionFileFormat( 
            /* [in] */ cwbdtFDFFormatEnum newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseDownloadBIFFOptions2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseDownloadBIFFOptions2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseDownloadBIFFOptions2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseDownloadBIFFOptions2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseDownloadBIFFOptions2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseDownloadBIFFOptions2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseDownloadBIFFOptions2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseDownloadBIFFOptions2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CreateExtraSheets )( 
            IcwbxDatabaseDownloadBIFFOptions2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CreateExtraSheets )( 
            IcwbxDatabaseDownloadBIFFOptions2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExistingFileOption )( 
            IcwbxDatabaseDownloadBIFFOptions2 * This,
            /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExistingFileOption )( 
            IcwbxDatabaseDownloadBIFFOptions2 * This,
            /* [in] */ cwbdtExistingOutputFileEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fileDescriptionFile )( 
            IcwbxDatabaseDownloadBIFFOptions2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fileDescriptionFile )( 
            IcwbxDatabaseDownloadBIFFOptions2 * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HeadingsOnExtraSheets )( 
            IcwbxDatabaseDownloadBIFFOptions2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HeadingsOnExtraSheets )( 
            IcwbxDatabaseDownloadBIFFOptions2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HeadingsOnFirstSheet )( 
            IcwbxDatabaseDownloadBIFFOptions2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HeadingsOnFirstSheet )( 
            IcwbxDatabaseDownloadBIFFOptions2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ReceiveInfo )( 
            IcwbxDatabaseDownloadBIFFOptions2 * This,
            /* [in] */ long newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseDownloadBIFFOptions2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FileDescriptionFileFormat )( 
            IcwbxDatabaseDownloadBIFFOptions2 * This,
            /* [retval][out] */ cwbdtFDFFormatEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FileDescriptionFileFormat )( 
            IcwbxDatabaseDownloadBIFFOptions2 * This,
            /* [in] */ cwbdtFDFFormatEnum newVal);
        
        END_INTERFACE
    } IcwbxDatabaseDownloadBIFFOptions2Vtbl;

    interface IcwbxDatabaseDownloadBIFFOptions2
    {
        CONST_VTBL struct IcwbxDatabaseDownloadBIFFOptions2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseDownloadBIFFOptions2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseDownloadBIFFOptions2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseDownloadBIFFOptions2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseDownloadBIFFOptions2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseDownloadBIFFOptions2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseDownloadBIFFOptions2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseDownloadBIFFOptions2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseDownloadBIFFOptions2_get_CreateExtraSheets(This,pVal)	\
    (This)->lpVtbl -> get_CreateExtraSheets(This,pVal)

#define IcwbxDatabaseDownloadBIFFOptions2_put_CreateExtraSheets(This,newVal)	\
    (This)->lpVtbl -> put_CreateExtraSheets(This,newVal)

#define IcwbxDatabaseDownloadBIFFOptions2_get_ExistingFileOption(This,pVal)	\
    (This)->lpVtbl -> get_ExistingFileOption(This,pVal)

#define IcwbxDatabaseDownloadBIFFOptions2_put_ExistingFileOption(This,newVal)	\
    (This)->lpVtbl -> put_ExistingFileOption(This,newVal)

#define IcwbxDatabaseDownloadBIFFOptions2_get_fileDescriptionFile(This,pVal)	\
    (This)->lpVtbl -> get_fileDescriptionFile(This,pVal)

#define IcwbxDatabaseDownloadBIFFOptions2_put_fileDescriptionFile(This,newVal)	\
    (This)->lpVtbl -> put_fileDescriptionFile(This,newVal)

#define IcwbxDatabaseDownloadBIFFOptions2_get_HeadingsOnExtraSheets(This,pVal)	\
    (This)->lpVtbl -> get_HeadingsOnExtraSheets(This,pVal)

#define IcwbxDatabaseDownloadBIFFOptions2_put_HeadingsOnExtraSheets(This,newVal)	\
    (This)->lpVtbl -> put_HeadingsOnExtraSheets(This,newVal)

#define IcwbxDatabaseDownloadBIFFOptions2_get_HeadingsOnFirstSheet(This,pVal)	\
    (This)->lpVtbl -> get_HeadingsOnFirstSheet(This,pVal)

#define IcwbxDatabaseDownloadBIFFOptions2_put_HeadingsOnFirstSheet(This,newVal)	\
    (This)->lpVtbl -> put_HeadingsOnFirstSheet(This,newVal)

#define IcwbxDatabaseDownloadBIFFOptions2_put_ReceiveInfo(This,newVal)	\
    (This)->lpVtbl -> put_ReceiveInfo(This,newVal)

#define IcwbxDatabaseDownloadBIFFOptions2_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#define IcwbxDatabaseDownloadBIFFOptions2_get_FileDescriptionFileFormat(This,pVal)	\
    (This)->lpVtbl -> get_FileDescriptionFileFormat(This,pVal)

#define IcwbxDatabaseDownloadBIFFOptions2_put_FileDescriptionFileFormat(This,newVal)	\
    (This)->lpVtbl -> put_FileDescriptionFileFormat(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadBIFFOptions2_get_CreateExtraSheets_Proxy( 
    IcwbxDatabaseDownloadBIFFOptions2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadBIFFOptions2_get_CreateExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadBIFFOptions2_put_CreateExtraSheets_Proxy( 
    IcwbxDatabaseDownloadBIFFOptions2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadBIFFOptions2_put_CreateExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadBIFFOptions2_get_ExistingFileOption_Proxy( 
    IcwbxDatabaseDownloadBIFFOptions2 * This,
    /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadBIFFOptions2_get_ExistingFileOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadBIFFOptions2_put_ExistingFileOption_Proxy( 
    IcwbxDatabaseDownloadBIFFOptions2 * This,
    /* [in] */ cwbdtExistingOutputFileEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadBIFFOptions2_put_ExistingFileOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadBIFFOptions2_get_fileDescriptionFile_Proxy( 
    IcwbxDatabaseDownloadBIFFOptions2 * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseDownloadBIFFOptions2_get_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadBIFFOptions2_put_fileDescriptionFile_Proxy( 
    IcwbxDatabaseDownloadBIFFOptions2 * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseDownloadBIFFOptions2_put_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadBIFFOptions2_get_HeadingsOnExtraSheets_Proxy( 
    IcwbxDatabaseDownloadBIFFOptions2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadBIFFOptions2_get_HeadingsOnExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadBIFFOptions2_put_HeadingsOnExtraSheets_Proxy( 
    IcwbxDatabaseDownloadBIFFOptions2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadBIFFOptions2_put_HeadingsOnExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadBIFFOptions2_get_HeadingsOnFirstSheet_Proxy( 
    IcwbxDatabaseDownloadBIFFOptions2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadBIFFOptions2_get_HeadingsOnFirstSheet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadBIFFOptions2_put_HeadingsOnFirstSheet_Proxy( 
    IcwbxDatabaseDownloadBIFFOptions2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadBIFFOptions2_put_HeadingsOnFirstSheet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadBIFFOptions2_put_ReceiveInfo_Proxy( 
    IcwbxDatabaseDownloadBIFFOptions2 * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownloadBIFFOptions2_put_ReceiveInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadBIFFOptions2_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseDownloadBIFFOptions2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadBIFFOptions2_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadBIFFOptions2_get_FileDescriptionFileFormat_Proxy( 
    IcwbxDatabaseDownloadBIFFOptions2 * This,
    /* [retval][out] */ cwbdtFDFFormatEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadBIFFOptions2_get_FileDescriptionFileFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadBIFFOptions2_put_FileDescriptionFileFormat_Proxy( 
    IcwbxDatabaseDownloadBIFFOptions2 * This,
    /* [in] */ cwbdtFDFFormatEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadBIFFOptions2_put_FileDescriptionFileFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseDownloadBIFFOptions2_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadWK4Options2_INTERFACE_DEFINED__
#define __IcwbxDatabaseDownloadWK4Options2_INTERFACE_DEFINED__

/* interface IcwbxDatabaseDownloadWK4Options2 */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseDownloadWK4Options2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8f9ADB83-6C14-4dAE-9D2D-D5998E82E758")
    IcwbxDatabaseDownloadWK4Options2 : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CreateExtraSheets( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CreateExtraSheets( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExistingFileOption( 
            /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ExistingFileOption( 
            /* [in] */ cwbdtExistingOutputFileEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_fileDescriptionFile( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_fileDescriptionFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HeadingsOnExtraSheets( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HeadingsOnExtraSheets( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HeadingsOnFirstSheet( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HeadingsOnFirstSheet( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReceiveInfo( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileDescriptionFileFormat( 
            /* [retval][out] */ cwbdtFDFFormatEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FileDescriptionFileFormat( 
            /* [in] */ cwbdtFDFFormatEnum newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseDownloadWK4Options2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseDownloadWK4Options2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseDownloadWK4Options2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseDownloadWK4Options2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseDownloadWK4Options2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseDownloadWK4Options2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseDownloadWK4Options2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseDownloadWK4Options2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CreateExtraSheets )( 
            IcwbxDatabaseDownloadWK4Options2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CreateExtraSheets )( 
            IcwbxDatabaseDownloadWK4Options2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExistingFileOption )( 
            IcwbxDatabaseDownloadWK4Options2 * This,
            /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExistingFileOption )( 
            IcwbxDatabaseDownloadWK4Options2 * This,
            /* [in] */ cwbdtExistingOutputFileEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fileDescriptionFile )( 
            IcwbxDatabaseDownloadWK4Options2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fileDescriptionFile )( 
            IcwbxDatabaseDownloadWK4Options2 * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HeadingsOnExtraSheets )( 
            IcwbxDatabaseDownloadWK4Options2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HeadingsOnExtraSheets )( 
            IcwbxDatabaseDownloadWK4Options2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HeadingsOnFirstSheet )( 
            IcwbxDatabaseDownloadWK4Options2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HeadingsOnFirstSheet )( 
            IcwbxDatabaseDownloadWK4Options2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ReceiveInfo )( 
            IcwbxDatabaseDownloadWK4Options2 * This,
            /* [in] */ long newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseDownloadWK4Options2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FileDescriptionFileFormat )( 
            IcwbxDatabaseDownloadWK4Options2 * This,
            /* [retval][out] */ cwbdtFDFFormatEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FileDescriptionFileFormat )( 
            IcwbxDatabaseDownloadWK4Options2 * This,
            /* [in] */ cwbdtFDFFormatEnum newVal);
        
        END_INTERFACE
    } IcwbxDatabaseDownloadWK4Options2Vtbl;

    interface IcwbxDatabaseDownloadWK4Options2
    {
        CONST_VTBL struct IcwbxDatabaseDownloadWK4Options2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseDownloadWK4Options2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseDownloadWK4Options2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseDownloadWK4Options2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseDownloadWK4Options2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseDownloadWK4Options2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseDownloadWK4Options2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseDownloadWK4Options2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseDownloadWK4Options2_get_CreateExtraSheets(This,pVal)	\
    (This)->lpVtbl -> get_CreateExtraSheets(This,pVal)

#define IcwbxDatabaseDownloadWK4Options2_put_CreateExtraSheets(This,newVal)	\
    (This)->lpVtbl -> put_CreateExtraSheets(This,newVal)

#define IcwbxDatabaseDownloadWK4Options2_get_ExistingFileOption(This,pVal)	\
    (This)->lpVtbl -> get_ExistingFileOption(This,pVal)

#define IcwbxDatabaseDownloadWK4Options2_put_ExistingFileOption(This,newVal)	\
    (This)->lpVtbl -> put_ExistingFileOption(This,newVal)

#define IcwbxDatabaseDownloadWK4Options2_get_fileDescriptionFile(This,pVal)	\
    (This)->lpVtbl -> get_fileDescriptionFile(This,pVal)

#define IcwbxDatabaseDownloadWK4Options2_put_fileDescriptionFile(This,newVal)	\
    (This)->lpVtbl -> put_fileDescriptionFile(This,newVal)

#define IcwbxDatabaseDownloadWK4Options2_get_HeadingsOnExtraSheets(This,pVal)	\
    (This)->lpVtbl -> get_HeadingsOnExtraSheets(This,pVal)

#define IcwbxDatabaseDownloadWK4Options2_put_HeadingsOnExtraSheets(This,newVal)	\
    (This)->lpVtbl -> put_HeadingsOnExtraSheets(This,newVal)

#define IcwbxDatabaseDownloadWK4Options2_get_HeadingsOnFirstSheet(This,pVal)	\
    (This)->lpVtbl -> get_HeadingsOnFirstSheet(This,pVal)

#define IcwbxDatabaseDownloadWK4Options2_put_HeadingsOnFirstSheet(This,newVal)	\
    (This)->lpVtbl -> put_HeadingsOnFirstSheet(This,newVal)

#define IcwbxDatabaseDownloadWK4Options2_put_ReceiveInfo(This,newVal)	\
    (This)->lpVtbl -> put_ReceiveInfo(This,newVal)

#define IcwbxDatabaseDownloadWK4Options2_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#define IcwbxDatabaseDownloadWK4Options2_get_FileDescriptionFileFormat(This,pVal)	\
    (This)->lpVtbl -> get_FileDescriptionFileFormat(This,pVal)

#define IcwbxDatabaseDownloadWK4Options2_put_FileDescriptionFileFormat(This,newVal)	\
    (This)->lpVtbl -> put_FileDescriptionFileFormat(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadWK4Options2_get_CreateExtraSheets_Proxy( 
    IcwbxDatabaseDownloadWK4Options2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadWK4Options2_get_CreateExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadWK4Options2_put_CreateExtraSheets_Proxy( 
    IcwbxDatabaseDownloadWK4Options2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadWK4Options2_put_CreateExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadWK4Options2_get_ExistingFileOption_Proxy( 
    IcwbxDatabaseDownloadWK4Options2 * This,
    /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadWK4Options2_get_ExistingFileOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadWK4Options2_put_ExistingFileOption_Proxy( 
    IcwbxDatabaseDownloadWK4Options2 * This,
    /* [in] */ cwbdtExistingOutputFileEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadWK4Options2_put_ExistingFileOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadWK4Options2_get_fileDescriptionFile_Proxy( 
    IcwbxDatabaseDownloadWK4Options2 * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseDownloadWK4Options2_get_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadWK4Options2_put_fileDescriptionFile_Proxy( 
    IcwbxDatabaseDownloadWK4Options2 * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseDownloadWK4Options2_put_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadWK4Options2_get_HeadingsOnExtraSheets_Proxy( 
    IcwbxDatabaseDownloadWK4Options2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadWK4Options2_get_HeadingsOnExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadWK4Options2_put_HeadingsOnExtraSheets_Proxy( 
    IcwbxDatabaseDownloadWK4Options2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadWK4Options2_put_HeadingsOnExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadWK4Options2_get_HeadingsOnFirstSheet_Proxy( 
    IcwbxDatabaseDownloadWK4Options2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadWK4Options2_get_HeadingsOnFirstSheet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadWK4Options2_put_HeadingsOnFirstSheet_Proxy( 
    IcwbxDatabaseDownloadWK4Options2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadWK4Options2_put_HeadingsOnFirstSheet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadWK4Options2_put_ReceiveInfo_Proxy( 
    IcwbxDatabaseDownloadWK4Options2 * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownloadWK4Options2_put_ReceiveInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadWK4Options2_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseDownloadWK4Options2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadWK4Options2_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadWK4Options2_get_FileDescriptionFileFormat_Proxy( 
    IcwbxDatabaseDownloadWK4Options2 * This,
    /* [retval][out] */ cwbdtFDFFormatEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadWK4Options2_get_FileDescriptionFileFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadWK4Options2_put_FileDescriptionFileFormat_Proxy( 
    IcwbxDatabaseDownloadWK4Options2 * This,
    /* [in] */ cwbdtFDFFormatEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadWK4Options2_put_FileDescriptionFileFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseDownloadWK4Options2_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseDownload123Options2_INTERFACE_DEFINED__
#define __IcwbxDatabaseDownload123Options2_INTERFACE_DEFINED__

/* interface IcwbxDatabaseDownload123Options2 */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseDownload123Options2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E6953A46-A836-41DB-A97B-985F62BE744D")
    IcwbxDatabaseDownload123Options2 : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CreateExtraSheets( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CreateExtraSheets( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExistingFileOption( 
            /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ExistingFileOption( 
            /* [in] */ cwbdtExistingOutputFileEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_fileDescriptionFile( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_fileDescriptionFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HeadingsOnExtraSheets( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HeadingsOnExtraSheets( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HeadingsOnFirstSheet( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HeadingsOnFirstSheet( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReceiveInfo( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileDescriptionFileFormat( 
            /* [retval][out] */ cwbdtFDFFormatEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FileDescriptionFileFormat( 
            /* [in] */ cwbdtFDFFormatEnum newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseDownload123Options2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseDownload123Options2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseDownload123Options2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseDownload123Options2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseDownload123Options2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseDownload123Options2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseDownload123Options2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseDownload123Options2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CreateExtraSheets )( 
            IcwbxDatabaseDownload123Options2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CreateExtraSheets )( 
            IcwbxDatabaseDownload123Options2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExistingFileOption )( 
            IcwbxDatabaseDownload123Options2 * This,
            /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExistingFileOption )( 
            IcwbxDatabaseDownload123Options2 * This,
            /* [in] */ cwbdtExistingOutputFileEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fileDescriptionFile )( 
            IcwbxDatabaseDownload123Options2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fileDescriptionFile )( 
            IcwbxDatabaseDownload123Options2 * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HeadingsOnExtraSheets )( 
            IcwbxDatabaseDownload123Options2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HeadingsOnExtraSheets )( 
            IcwbxDatabaseDownload123Options2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HeadingsOnFirstSheet )( 
            IcwbxDatabaseDownload123Options2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HeadingsOnFirstSheet )( 
            IcwbxDatabaseDownload123Options2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ReceiveInfo )( 
            IcwbxDatabaseDownload123Options2 * This,
            /* [in] */ long newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseDownload123Options2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FileDescriptionFileFormat )( 
            IcwbxDatabaseDownload123Options2 * This,
            /* [retval][out] */ cwbdtFDFFormatEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FileDescriptionFileFormat )( 
            IcwbxDatabaseDownload123Options2 * This,
            /* [in] */ cwbdtFDFFormatEnum newVal);
        
        END_INTERFACE
    } IcwbxDatabaseDownload123Options2Vtbl;

    interface IcwbxDatabaseDownload123Options2
    {
        CONST_VTBL struct IcwbxDatabaseDownload123Options2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseDownload123Options2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseDownload123Options2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseDownload123Options2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseDownload123Options2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseDownload123Options2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseDownload123Options2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseDownload123Options2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseDownload123Options2_get_CreateExtraSheets(This,pVal)	\
    (This)->lpVtbl -> get_CreateExtraSheets(This,pVal)

#define IcwbxDatabaseDownload123Options2_put_CreateExtraSheets(This,newVal)	\
    (This)->lpVtbl -> put_CreateExtraSheets(This,newVal)

#define IcwbxDatabaseDownload123Options2_get_ExistingFileOption(This,pVal)	\
    (This)->lpVtbl -> get_ExistingFileOption(This,pVal)

#define IcwbxDatabaseDownload123Options2_put_ExistingFileOption(This,newVal)	\
    (This)->lpVtbl -> put_ExistingFileOption(This,newVal)

#define IcwbxDatabaseDownload123Options2_get_fileDescriptionFile(This,pVal)	\
    (This)->lpVtbl -> get_fileDescriptionFile(This,pVal)

#define IcwbxDatabaseDownload123Options2_put_fileDescriptionFile(This,newVal)	\
    (This)->lpVtbl -> put_fileDescriptionFile(This,newVal)

#define IcwbxDatabaseDownload123Options2_get_HeadingsOnExtraSheets(This,pVal)	\
    (This)->lpVtbl -> get_HeadingsOnExtraSheets(This,pVal)

#define IcwbxDatabaseDownload123Options2_put_HeadingsOnExtraSheets(This,newVal)	\
    (This)->lpVtbl -> put_HeadingsOnExtraSheets(This,newVal)

#define IcwbxDatabaseDownload123Options2_get_HeadingsOnFirstSheet(This,pVal)	\
    (This)->lpVtbl -> get_HeadingsOnFirstSheet(This,pVal)

#define IcwbxDatabaseDownload123Options2_put_HeadingsOnFirstSheet(This,newVal)	\
    (This)->lpVtbl -> put_HeadingsOnFirstSheet(This,newVal)

#define IcwbxDatabaseDownload123Options2_put_ReceiveInfo(This,newVal)	\
    (This)->lpVtbl -> put_ReceiveInfo(This,newVal)

#define IcwbxDatabaseDownload123Options2_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#define IcwbxDatabaseDownload123Options2_get_FileDescriptionFileFormat(This,pVal)	\
    (This)->lpVtbl -> get_FileDescriptionFileFormat(This,pVal)

#define IcwbxDatabaseDownload123Options2_put_FileDescriptionFileFormat(This,newVal)	\
    (This)->lpVtbl -> put_FileDescriptionFileFormat(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownload123Options2_get_CreateExtraSheets_Proxy( 
    IcwbxDatabaseDownload123Options2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownload123Options2_get_CreateExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownload123Options2_put_CreateExtraSheets_Proxy( 
    IcwbxDatabaseDownload123Options2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownload123Options2_put_CreateExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownload123Options2_get_ExistingFileOption_Proxy( 
    IcwbxDatabaseDownload123Options2 * This,
    /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownload123Options2_get_ExistingFileOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownload123Options2_put_ExistingFileOption_Proxy( 
    IcwbxDatabaseDownload123Options2 * This,
    /* [in] */ cwbdtExistingOutputFileEnum newVal);


void __RPC_STUB IcwbxDatabaseDownload123Options2_put_ExistingFileOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownload123Options2_get_fileDescriptionFile_Proxy( 
    IcwbxDatabaseDownload123Options2 * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseDownload123Options2_get_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownload123Options2_put_fileDescriptionFile_Proxy( 
    IcwbxDatabaseDownload123Options2 * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseDownload123Options2_put_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownload123Options2_get_HeadingsOnExtraSheets_Proxy( 
    IcwbxDatabaseDownload123Options2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownload123Options2_get_HeadingsOnExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownload123Options2_put_HeadingsOnExtraSheets_Proxy( 
    IcwbxDatabaseDownload123Options2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownload123Options2_put_HeadingsOnExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownload123Options2_get_HeadingsOnFirstSheet_Proxy( 
    IcwbxDatabaseDownload123Options2 * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownload123Options2_get_HeadingsOnFirstSheet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownload123Options2_put_HeadingsOnFirstSheet_Proxy( 
    IcwbxDatabaseDownload123Options2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownload123Options2_put_HeadingsOnFirstSheet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownload123Options2_put_ReceiveInfo_Proxy( 
    IcwbxDatabaseDownload123Options2 * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownload123Options2_put_ReceiveInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownload123Options2_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseDownload123Options2 * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownload123Options2_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownload123Options2_get_FileDescriptionFileFormat_Proxy( 
    IcwbxDatabaseDownload123Options2 * This,
    /* [retval][out] */ cwbdtFDFFormatEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownload123Options2_get_FileDescriptionFileFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownload123Options2_put_FileDescriptionFileFormat_Proxy( 
    IcwbxDatabaseDownload123Options2 * This,
    /* [in] */ cwbdtFDFFormatEnum newVal);


void __RPC_STUB IcwbxDatabaseDownload123Options2_put_FileDescriptionFileFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseDownload123Options2_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadExcelXMLOptions_INTERFACE_DEFINED__
#define __IcwbxDatabaseDownloadExcelXMLOptions_INTERFACE_DEFINED__

/* interface IcwbxDatabaseDownloadExcelXMLOptions */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseDownloadExcelXMLOptions;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B337C0ED-8686-4427-833F-FF6800168197")
    IcwbxDatabaseDownloadExcelXMLOptions : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CreateExtraSheets( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CreateExtraSheets( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExistingFileOption( 
            /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ExistingFileOption( 
            /* [in] */ cwbdtExistingOutputFileEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_fileDescriptionFile( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_fileDescriptionFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HeadingsOnExtraSheets( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HeadingsOnExtraSheets( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HeadingsOnFirstSheet( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HeadingsOnFirstSheet( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReceiveInfo( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileDescriptionFileFormat( 
            /* [retval][out] */ cwbdtFDFFormatEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FileDescriptionFileFormat( 
            /* [in] */ cwbdtFDFFormatEnum newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseDownloadExcelXMLOptionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseDownloadExcelXMLOptions * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseDownloadExcelXMLOptions * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseDownloadExcelXMLOptions * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseDownloadExcelXMLOptions * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseDownloadExcelXMLOptions * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseDownloadExcelXMLOptions * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseDownloadExcelXMLOptions * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CreateExtraSheets )( 
            IcwbxDatabaseDownloadExcelXMLOptions * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CreateExtraSheets )( 
            IcwbxDatabaseDownloadExcelXMLOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExistingFileOption )( 
            IcwbxDatabaseDownloadExcelXMLOptions * This,
            /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExistingFileOption )( 
            IcwbxDatabaseDownloadExcelXMLOptions * This,
            /* [in] */ cwbdtExistingOutputFileEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fileDescriptionFile )( 
            IcwbxDatabaseDownloadExcelXMLOptions * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fileDescriptionFile )( 
            IcwbxDatabaseDownloadExcelXMLOptions * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HeadingsOnExtraSheets )( 
            IcwbxDatabaseDownloadExcelXMLOptions * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HeadingsOnExtraSheets )( 
            IcwbxDatabaseDownloadExcelXMLOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HeadingsOnFirstSheet )( 
            IcwbxDatabaseDownloadExcelXMLOptions * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HeadingsOnFirstSheet )( 
            IcwbxDatabaseDownloadExcelXMLOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ReceiveInfo )( 
            IcwbxDatabaseDownloadExcelXMLOptions * This,
            /* [in] */ long newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseDownloadExcelXMLOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FileDescriptionFileFormat )( 
            IcwbxDatabaseDownloadExcelXMLOptions * This,
            /* [retval][out] */ cwbdtFDFFormatEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FileDescriptionFileFormat )( 
            IcwbxDatabaseDownloadExcelXMLOptions * This,
            /* [in] */ cwbdtFDFFormatEnum newVal);
        
        END_INTERFACE
    } IcwbxDatabaseDownloadExcelXMLOptionsVtbl;

    interface IcwbxDatabaseDownloadExcelXMLOptions
    {
        CONST_VTBL struct IcwbxDatabaseDownloadExcelXMLOptionsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseDownloadExcelXMLOptions_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseDownloadExcelXMLOptions_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseDownloadExcelXMLOptions_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseDownloadExcelXMLOptions_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseDownloadExcelXMLOptions_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseDownloadExcelXMLOptions_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseDownloadExcelXMLOptions_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseDownloadExcelXMLOptions_get_CreateExtraSheets(This,pVal)	\
    (This)->lpVtbl -> get_CreateExtraSheets(This,pVal)

#define IcwbxDatabaseDownloadExcelXMLOptions_put_CreateExtraSheets(This,newVal)	\
    (This)->lpVtbl -> put_CreateExtraSheets(This,newVal)

#define IcwbxDatabaseDownloadExcelXMLOptions_get_ExistingFileOption(This,pVal)	\
    (This)->lpVtbl -> get_ExistingFileOption(This,pVal)

#define IcwbxDatabaseDownloadExcelXMLOptions_put_ExistingFileOption(This,newVal)	\
    (This)->lpVtbl -> put_ExistingFileOption(This,newVal)

#define IcwbxDatabaseDownloadExcelXMLOptions_get_fileDescriptionFile(This,pVal)	\
    (This)->lpVtbl -> get_fileDescriptionFile(This,pVal)

#define IcwbxDatabaseDownloadExcelXMLOptions_put_fileDescriptionFile(This,newVal)	\
    (This)->lpVtbl -> put_fileDescriptionFile(This,newVal)

#define IcwbxDatabaseDownloadExcelXMLOptions_get_HeadingsOnExtraSheets(This,pVal)	\
    (This)->lpVtbl -> get_HeadingsOnExtraSheets(This,pVal)

#define IcwbxDatabaseDownloadExcelXMLOptions_put_HeadingsOnExtraSheets(This,newVal)	\
    (This)->lpVtbl -> put_HeadingsOnExtraSheets(This,newVal)

#define IcwbxDatabaseDownloadExcelXMLOptions_get_HeadingsOnFirstSheet(This,pVal)	\
    (This)->lpVtbl -> get_HeadingsOnFirstSheet(This,pVal)

#define IcwbxDatabaseDownloadExcelXMLOptions_put_HeadingsOnFirstSheet(This,newVal)	\
    (This)->lpVtbl -> put_HeadingsOnFirstSheet(This,newVal)

#define IcwbxDatabaseDownloadExcelXMLOptions_put_ReceiveInfo(This,newVal)	\
    (This)->lpVtbl -> put_ReceiveInfo(This,newVal)

#define IcwbxDatabaseDownloadExcelXMLOptions_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#define IcwbxDatabaseDownloadExcelXMLOptions_get_FileDescriptionFileFormat(This,pVal)	\
    (This)->lpVtbl -> get_FileDescriptionFileFormat(This,pVal)

#define IcwbxDatabaseDownloadExcelXMLOptions_put_FileDescriptionFileFormat(This,newVal)	\
    (This)->lpVtbl -> put_FileDescriptionFileFormat(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadExcelXMLOptions_get_CreateExtraSheets_Proxy( 
    IcwbxDatabaseDownloadExcelXMLOptions * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadExcelXMLOptions_get_CreateExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadExcelXMLOptions_put_CreateExtraSheets_Proxy( 
    IcwbxDatabaseDownloadExcelXMLOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadExcelXMLOptions_put_CreateExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadExcelXMLOptions_get_ExistingFileOption_Proxy( 
    IcwbxDatabaseDownloadExcelXMLOptions * This,
    /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadExcelXMLOptions_get_ExistingFileOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadExcelXMLOptions_put_ExistingFileOption_Proxy( 
    IcwbxDatabaseDownloadExcelXMLOptions * This,
    /* [in] */ cwbdtExistingOutputFileEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadExcelXMLOptions_put_ExistingFileOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadExcelXMLOptions_get_fileDescriptionFile_Proxy( 
    IcwbxDatabaseDownloadExcelXMLOptions * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseDownloadExcelXMLOptions_get_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadExcelXMLOptions_put_fileDescriptionFile_Proxy( 
    IcwbxDatabaseDownloadExcelXMLOptions * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseDownloadExcelXMLOptions_put_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadExcelXMLOptions_get_HeadingsOnExtraSheets_Proxy( 
    IcwbxDatabaseDownloadExcelXMLOptions * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadExcelXMLOptions_get_HeadingsOnExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadExcelXMLOptions_put_HeadingsOnExtraSheets_Proxy( 
    IcwbxDatabaseDownloadExcelXMLOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadExcelXMLOptions_put_HeadingsOnExtraSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadExcelXMLOptions_get_HeadingsOnFirstSheet_Proxy( 
    IcwbxDatabaseDownloadExcelXMLOptions * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadExcelXMLOptions_get_HeadingsOnFirstSheet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadExcelXMLOptions_put_HeadingsOnFirstSheet_Proxy( 
    IcwbxDatabaseDownloadExcelXMLOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadExcelXMLOptions_put_HeadingsOnFirstSheet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadExcelXMLOptions_put_ReceiveInfo_Proxy( 
    IcwbxDatabaseDownloadExcelXMLOptions * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownloadExcelXMLOptions_put_ReceiveInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadExcelXMLOptions_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseDownloadExcelXMLOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadExcelXMLOptions_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadExcelXMLOptions_get_FileDescriptionFileFormat_Proxy( 
    IcwbxDatabaseDownloadExcelXMLOptions * This,
    /* [retval][out] */ cwbdtFDFFormatEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadExcelXMLOptions_get_FileDescriptionFileFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadExcelXMLOptions_put_FileDescriptionFileFormat_Proxy( 
    IcwbxDatabaseDownloadExcelXMLOptions * This,
    /* [in] */ cwbdtFDFFormatEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadExcelXMLOptions_put_FileDescriptionFileFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseDownloadExcelXMLOptions_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseTransferResults_INTERFACE_DEFINED__
#define __IcwbxDatabaseTransferResults_INTERFACE_DEFINED__

/* interface IcwbxDatabaseTransferResults */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseTransferResults;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("35DD1ABA-0CAB-11D3-8392-C4CC6678F234")
    IcwbxDatabaseTransferResults : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CompletionTime( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DataErrorsOccurred( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DataWarningsOccurred( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RowsTransferred( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TablesTransferred( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DataErrors( 
            /* [retval][out] */ IcwbxDatabaseDataErrors **pVal) = 0;
        
        virtual /* [restricted][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [restricted][id] */ HRESULT STDMETHODCALLTYPE Populate( 
            long resultsInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseTransferResultsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseTransferResults * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseTransferResults * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseTransferResults * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseTransferResults * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseTransferResults * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseTransferResults * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseTransferResults * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CompletionTime )( 
            IcwbxDatabaseTransferResults * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DataErrorsOccurred )( 
            IcwbxDatabaseTransferResults * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DataWarningsOccurred )( 
            IcwbxDatabaseTransferResults * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RowsTransferred )( 
            IcwbxDatabaseTransferResults * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TablesTransferred )( 
            IcwbxDatabaseTransferResults * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DataErrors )( 
            IcwbxDatabaseTransferResults * This,
            /* [retval][out] */ IcwbxDatabaseDataErrors **pVal);
        
        /* [restricted][id] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IcwbxDatabaseTransferResults * This);
        
        /* [restricted][id] */ HRESULT ( STDMETHODCALLTYPE *Populate )( 
            IcwbxDatabaseTransferResults * This,
            long resultsInfo);
        
        END_INTERFACE
    } IcwbxDatabaseTransferResultsVtbl;

    interface IcwbxDatabaseTransferResults
    {
        CONST_VTBL struct IcwbxDatabaseTransferResultsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseTransferResults_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseTransferResults_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseTransferResults_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseTransferResults_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseTransferResults_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseTransferResults_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseTransferResults_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseTransferResults_get_CompletionTime(This,pVal)	\
    (This)->lpVtbl -> get_CompletionTime(This,pVal)

#define IcwbxDatabaseTransferResults_get_DataErrorsOccurred(This,pVal)	\
    (This)->lpVtbl -> get_DataErrorsOccurred(This,pVal)

#define IcwbxDatabaseTransferResults_get_DataWarningsOccurred(This,pVal)	\
    (This)->lpVtbl -> get_DataWarningsOccurred(This,pVal)

#define IcwbxDatabaseTransferResults_get_RowsTransferred(This,pVal)	\
    (This)->lpVtbl -> get_RowsTransferred(This,pVal)

#define IcwbxDatabaseTransferResults_get_TablesTransferred(This,pVal)	\
    (This)->lpVtbl -> get_TablesTransferred(This,pVal)

#define IcwbxDatabaseTransferResults_get_DataErrors(This,pVal)	\
    (This)->lpVtbl -> get_DataErrors(This,pVal)

#define IcwbxDatabaseTransferResults_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define IcwbxDatabaseTransferResults_Populate(This,resultsInfo)	\
    (This)->lpVtbl -> Populate(This,resultsInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseTransferResults_get_CompletionTime_Proxy( 
    IcwbxDatabaseTransferResults * This,
    /* [retval][out] */ DATE *pVal);


void __RPC_STUB IcwbxDatabaseTransferResults_get_CompletionTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseTransferResults_get_DataErrorsOccurred_Proxy( 
    IcwbxDatabaseTransferResults * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseTransferResults_get_DataErrorsOccurred_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseTransferResults_get_DataWarningsOccurred_Proxy( 
    IcwbxDatabaseTransferResults * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseTransferResults_get_DataWarningsOccurred_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseTransferResults_get_RowsTransferred_Proxy( 
    IcwbxDatabaseTransferResults * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxDatabaseTransferResults_get_RowsTransferred_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseTransferResults_get_TablesTransferred_Proxy( 
    IcwbxDatabaseTransferResults * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxDatabaseTransferResults_get_TablesTransferred_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseTransferResults_get_DataErrors_Proxy( 
    IcwbxDatabaseTransferResults * This,
    /* [retval][out] */ IcwbxDatabaseDataErrors **pVal);


void __RPC_STUB IcwbxDatabaseTransferResults_get_DataErrors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseTransferResults_Clear_Proxy( 
    IcwbxDatabaseTransferResults * This);


void __RPC_STUB IcwbxDatabaseTransferResults_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseTransferResults_Populate_Proxy( 
    IcwbxDatabaseTransferResults * This,
    long resultsInfo);


void __RPC_STUB IcwbxDatabaseTransferResults_Populate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseTransferResults_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseDataError_INTERFACE_DEFINED__
#define __IcwbxDatabaseDataError_INTERFACE_DEFINED__

/* interface IcwbxDatabaseDataError */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseDataError;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("092EA4E5-1E84-11D3-9159-002035AE9B5D")
    IcwbxDatabaseDataError : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Column( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_Column( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Row( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_Row( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ErrorType( 
            /* [retval][out] */ cwbdtDataErrorEnum *pVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_ErrorType( 
            /* [in] */ cwbdtDataErrorEnum newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseDataErrorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseDataError * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseDataError * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseDataError * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseDataError * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseDataError * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseDataError * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseDataError * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Column )( 
            IcwbxDatabaseDataError * This,
            /* [retval][out] */ long *pVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Column )( 
            IcwbxDatabaseDataError * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Row )( 
            IcwbxDatabaseDataError * This,
            /* [retval][out] */ long *pVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Row )( 
            IcwbxDatabaseDataError * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ErrorType )( 
            IcwbxDatabaseDataError * This,
            /* [retval][out] */ cwbdtDataErrorEnum *pVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ErrorType )( 
            IcwbxDatabaseDataError * This,
            /* [in] */ cwbdtDataErrorEnum newVal);
        
        END_INTERFACE
    } IcwbxDatabaseDataErrorVtbl;

    interface IcwbxDatabaseDataError
    {
        CONST_VTBL struct IcwbxDatabaseDataErrorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseDataError_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseDataError_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseDataError_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseDataError_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseDataError_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseDataError_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseDataError_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseDataError_get_Column(This,pVal)	\
    (This)->lpVtbl -> get_Column(This,pVal)

#define IcwbxDatabaseDataError_put_Column(This,newVal)	\
    (This)->lpVtbl -> put_Column(This,newVal)

#define IcwbxDatabaseDataError_get_Row(This,pVal)	\
    (This)->lpVtbl -> get_Row(This,pVal)

#define IcwbxDatabaseDataError_put_Row(This,newVal)	\
    (This)->lpVtbl -> put_Row(This,newVal)

#define IcwbxDatabaseDataError_get_ErrorType(This,pVal)	\
    (This)->lpVtbl -> get_ErrorType(This,pVal)

#define IcwbxDatabaseDataError_put_ErrorType(This,newVal)	\
    (This)->lpVtbl -> put_ErrorType(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDataError_get_Column_Proxy( 
    IcwbxDatabaseDataError * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxDatabaseDataError_get_Column_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDataError_put_Column_Proxy( 
    IcwbxDatabaseDataError * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDataError_put_Column_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDataError_get_Row_Proxy( 
    IcwbxDatabaseDataError * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxDatabaseDataError_get_Row_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDataError_put_Row_Proxy( 
    IcwbxDatabaseDataError * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDataError_put_Row_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDataError_get_ErrorType_Proxy( 
    IcwbxDatabaseDataError * This,
    /* [retval][out] */ cwbdtDataErrorEnum *pVal);


void __RPC_STUB IcwbxDatabaseDataError_get_ErrorType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDataError_put_ErrorType_Proxy( 
    IcwbxDatabaseDataError * This,
    /* [in] */ cwbdtDataErrorEnum newVal);


void __RPC_STUB IcwbxDatabaseDataError_put_ErrorType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseDataError_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseDataErrors_INTERFACE_DEFINED__
#define __IcwbxDatabaseDataErrors_INTERFACE_DEFINED__

/* interface IcwbxDatabaseDataErrors */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseDataErrors;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("092EA4E7-1E84-11D3-9159-002035AE9B5D")
    IcwbxDatabaseDataErrors : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [restricted][id] */ HRESULT STDMETHODCALLTYPE _NewEnum( 
            /* [retval][out] */ IUnknown **ppvObject) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ IcwbxDatabaseDataError **pVal) = 0;
        
        virtual /* [restricted][id] */ HRESULT STDMETHODCALLTYPE Append( 
            /* [in] */ cwbdtDataErrorEnum Type,
            /* [in] */ long row,
            /* [in] */ long column) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseDataErrorsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseDataErrors * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseDataErrors * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseDataErrors * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseDataErrors * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseDataErrors * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseDataErrors * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseDataErrors * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IcwbxDatabaseDataErrors * This,
            /* [retval][out] */ long *pVal);
        
        /* [restricted][id] */ HRESULT ( STDMETHODCALLTYPE *_NewEnum )( 
            IcwbxDatabaseDataErrors * This,
            /* [retval][out] */ IUnknown **ppvObject);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IcwbxDatabaseDataErrors * This,
            /* [in] */ long index,
            /* [retval][out] */ IcwbxDatabaseDataError **pVal);
        
        /* [restricted][id] */ HRESULT ( STDMETHODCALLTYPE *Append )( 
            IcwbxDatabaseDataErrors * This,
            /* [in] */ cwbdtDataErrorEnum Type,
            /* [in] */ long row,
            /* [in] */ long column);
        
        END_INTERFACE
    } IcwbxDatabaseDataErrorsVtbl;

    interface IcwbxDatabaseDataErrors
    {
        CONST_VTBL struct IcwbxDatabaseDataErrorsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseDataErrors_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseDataErrors_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseDataErrors_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseDataErrors_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseDataErrors_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseDataErrors_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseDataErrors_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseDataErrors_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IcwbxDatabaseDataErrors__NewEnum(This,ppvObject)	\
    (This)->lpVtbl -> _NewEnum(This,ppvObject)

#define IcwbxDatabaseDataErrors_get_Item(This,index,pVal)	\
    (This)->lpVtbl -> get_Item(This,index,pVal)

#define IcwbxDatabaseDataErrors_Append(This,Type,row,column)	\
    (This)->lpVtbl -> Append(This,Type,row,column)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDataErrors_get_Count_Proxy( 
    IcwbxDatabaseDataErrors * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxDatabaseDataErrors_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDataErrors__NewEnum_Proxy( 
    IcwbxDatabaseDataErrors * This,
    /* [retval][out] */ IUnknown **ppvObject);


void __RPC_STUB IcwbxDatabaseDataErrors__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDataErrors_get_Item_Proxy( 
    IcwbxDatabaseDataErrors * This,
    /* [in] */ long index,
    /* [retval][out] */ IcwbxDatabaseDataError **pVal);


void __RPC_STUB IcwbxDatabaseDataErrors_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDataErrors_Append_Proxy( 
    IcwbxDatabaseDataErrors * This,
    /* [in] */ cwbdtDataErrorEnum Type,
    /* [in] */ long row,
    /* [in] */ long column);


void __RPC_STUB IcwbxDatabaseDataErrors_Append_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseDataErrors_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseUserLibraryList_INTERFACE_DEFINED__
#define __IcwbxDatabaseUserLibraryList_INTERFACE_DEFINED__

/* interface IcwbxDatabaseUserLibraryList */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseUserLibraryList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0B3B2CC0-4F03-11D3-8392-C2193F05062D")
    IcwbxDatabaseUserLibraryList : public IDispatch
    {
    public:
        virtual /* [restricted][id] */ HRESULT STDMETHODCALLTYPE _NewEnum( 
            /* [retval][out] */ IUnknown **ppvObject) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR LibraryName,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL addBeforeSystemLibraries = -1) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ BSTR LibraryName) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_XferInfo( 
            /* [in] */ long xferType,
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseUserLibraryListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseUserLibraryList * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseUserLibraryList * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseUserLibraryList * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseUserLibraryList * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseUserLibraryList * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseUserLibraryList * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseUserLibraryList * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [restricted][id] */ HRESULT ( STDMETHODCALLTYPE *_NewEnum )( 
            IcwbxDatabaseUserLibraryList * This,
            /* [retval][out] */ IUnknown **ppvObject);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IcwbxDatabaseUserLibraryList * This,
            /* [in] */ long index,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IcwbxDatabaseUserLibraryList * This,
            /* [in] */ BSTR LibraryName,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL addBeforeSystemLibraries);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IcwbxDatabaseUserLibraryList * This,
            /* [in] */ BSTR LibraryName);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_XferInfo )( 
            IcwbxDatabaseUserLibraryList * This,
            /* [in] */ long xferType,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IcwbxDatabaseUserLibraryList * This,
            /* [retval][out] */ long *pVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseUserLibraryList * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IcwbxDatabaseUserLibraryListVtbl;

    interface IcwbxDatabaseUserLibraryList
    {
        CONST_VTBL struct IcwbxDatabaseUserLibraryListVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseUserLibraryList_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseUserLibraryList_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseUserLibraryList_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseUserLibraryList_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseUserLibraryList_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseUserLibraryList_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseUserLibraryList_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseUserLibraryList__NewEnum(This,ppvObject)	\
    (This)->lpVtbl -> _NewEnum(This,ppvObject)

#define IcwbxDatabaseUserLibraryList_get_Item(This,index,pVal)	\
    (This)->lpVtbl -> get_Item(This,index,pVal)

#define IcwbxDatabaseUserLibraryList_Add(This,LibraryName,addBeforeSystemLibraries)	\
    (This)->lpVtbl -> Add(This,LibraryName,addBeforeSystemLibraries)

#define IcwbxDatabaseUserLibraryList_Remove(This,LibraryName)	\
    (This)->lpVtbl -> Remove(This,LibraryName)

#define IcwbxDatabaseUserLibraryList_put_XferInfo(This,xferType,newVal)	\
    (This)->lpVtbl -> put_XferInfo(This,xferType,newVal)

#define IcwbxDatabaseUserLibraryList_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IcwbxDatabaseUserLibraryList_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [restricted][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUserLibraryList__NewEnum_Proxy( 
    IcwbxDatabaseUserLibraryList * This,
    /* [retval][out] */ IUnknown **ppvObject);


void __RPC_STUB IcwbxDatabaseUserLibraryList__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUserLibraryList_get_Item_Proxy( 
    IcwbxDatabaseUserLibraryList * This,
    /* [in] */ long index,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseUserLibraryList_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUserLibraryList_Add_Proxy( 
    IcwbxDatabaseUserLibraryList * This,
    /* [in] */ BSTR LibraryName,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL addBeforeSystemLibraries);


void __RPC_STUB IcwbxDatabaseUserLibraryList_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUserLibraryList_Remove_Proxy( 
    IcwbxDatabaseUserLibraryList * This,
    /* [in] */ BSTR LibraryName);


void __RPC_STUB IcwbxDatabaseUserLibraryList_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUserLibraryList_put_XferInfo_Proxy( 
    IcwbxDatabaseUserLibraryList * This,
    /* [in] */ long xferType,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseUserLibraryList_put_XferInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUserLibraryList_get_Count_Proxy( 
    IcwbxDatabaseUserLibraryList * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxDatabaseUserLibraryList_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseUserLibraryList_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseUserLibraryList * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseUserLibraryList_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseUserLibraryList_INTERFACE_DEFINED__ */


#ifndef __IcwbxDatabaseDownloadUnicodeOptions_INTERFACE_DEFINED__
#define __IcwbxDatabaseDownloadUnicodeOptions_INTERFACE_DEFINED__

/* interface IcwbxDatabaseDownloadUnicodeOptions */
/* [object][oleautomation][nonextensible][helpcontext][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IcwbxDatabaseDownloadUnicodeOptions;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8C3CBBF8-A522-4433-94AD-CD442DCEC927")
    IcwbxDatabaseDownloadUnicodeOptions : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CodePage( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CodePage( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExistingFileOption( 
            /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ExistingFileOption( 
            /* [in] */ cwbdtExistingOutputFileEnum newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_fileDescriptionFile( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_fileDescriptionFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IncludeLeadingZeros( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IncludeLeadingZeros( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TruncateSpaces( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TruncateSpaces( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReceiveInfo( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE put_AsyncRequestActive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AddByteOrderMark( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AddByteOrderMark( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileDescriptionFileFormat( 
            /* [retval][out] */ cwbdtFDFFormatEnum *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FileDescriptionFileFormat( 
            /* [in] */ cwbdtFDFFormatEnum newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcwbxDatabaseDownloadUnicodeOptionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcwbxDatabaseDownloadUnicodeOptions * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcwbxDatabaseDownloadUnicodeOptions * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcwbxDatabaseDownloadUnicodeOptions * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcwbxDatabaseDownloadUnicodeOptions * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcwbxDatabaseDownloadUnicodeOptions * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcwbxDatabaseDownloadUnicodeOptions * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcwbxDatabaseDownloadUnicodeOptions * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CodePage )( 
            IcwbxDatabaseDownloadUnicodeOptions * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CodePage )( 
            IcwbxDatabaseDownloadUnicodeOptions * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExistingFileOption )( 
            IcwbxDatabaseDownloadUnicodeOptions * This,
            /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExistingFileOption )( 
            IcwbxDatabaseDownloadUnicodeOptions * This,
            /* [in] */ cwbdtExistingOutputFileEnum newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fileDescriptionFile )( 
            IcwbxDatabaseDownloadUnicodeOptions * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fileDescriptionFile )( 
            IcwbxDatabaseDownloadUnicodeOptions * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IncludeLeadingZeros )( 
            IcwbxDatabaseDownloadUnicodeOptions * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IncludeLeadingZeros )( 
            IcwbxDatabaseDownloadUnicodeOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TruncateSpaces )( 
            IcwbxDatabaseDownloadUnicodeOptions * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TruncateSpaces )( 
            IcwbxDatabaseDownloadUnicodeOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ReceiveInfo )( 
            IcwbxDatabaseDownloadUnicodeOptions * This,
            /* [in] */ long newVal);
        
        /* [restricted][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AsyncRequestActive )( 
            IcwbxDatabaseDownloadUnicodeOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AddByteOrderMark )( 
            IcwbxDatabaseDownloadUnicodeOptions * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AddByteOrderMark )( 
            IcwbxDatabaseDownloadUnicodeOptions * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FileDescriptionFileFormat )( 
            IcwbxDatabaseDownloadUnicodeOptions * This,
            /* [retval][out] */ cwbdtFDFFormatEnum *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FileDescriptionFileFormat )( 
            IcwbxDatabaseDownloadUnicodeOptions * This,
            /* [in] */ cwbdtFDFFormatEnum newVal);
        
        END_INTERFACE
    } IcwbxDatabaseDownloadUnicodeOptionsVtbl;

    interface IcwbxDatabaseDownloadUnicodeOptions
    {
        CONST_VTBL struct IcwbxDatabaseDownloadUnicodeOptionsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcwbxDatabaseDownloadUnicodeOptions_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcwbxDatabaseDownloadUnicodeOptions_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcwbxDatabaseDownloadUnicodeOptions_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcwbxDatabaseDownloadUnicodeOptions_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcwbxDatabaseDownloadUnicodeOptions_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcwbxDatabaseDownloadUnicodeOptions_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcwbxDatabaseDownloadUnicodeOptions_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcwbxDatabaseDownloadUnicodeOptions_get_CodePage(This,pVal)	\
    (This)->lpVtbl -> get_CodePage(This,pVal)

#define IcwbxDatabaseDownloadUnicodeOptions_put_CodePage(This,newVal)	\
    (This)->lpVtbl -> put_CodePage(This,newVal)

#define IcwbxDatabaseDownloadUnicodeOptions_get_ExistingFileOption(This,pVal)	\
    (This)->lpVtbl -> get_ExistingFileOption(This,pVal)

#define IcwbxDatabaseDownloadUnicodeOptions_put_ExistingFileOption(This,newVal)	\
    (This)->lpVtbl -> put_ExistingFileOption(This,newVal)

#define IcwbxDatabaseDownloadUnicodeOptions_get_fileDescriptionFile(This,pVal)	\
    (This)->lpVtbl -> get_fileDescriptionFile(This,pVal)

#define IcwbxDatabaseDownloadUnicodeOptions_put_fileDescriptionFile(This,newVal)	\
    (This)->lpVtbl -> put_fileDescriptionFile(This,newVal)

#define IcwbxDatabaseDownloadUnicodeOptions_get_IncludeLeadingZeros(This,pVal)	\
    (This)->lpVtbl -> get_IncludeLeadingZeros(This,pVal)

#define IcwbxDatabaseDownloadUnicodeOptions_put_IncludeLeadingZeros(This,newVal)	\
    (This)->lpVtbl -> put_IncludeLeadingZeros(This,newVal)

#define IcwbxDatabaseDownloadUnicodeOptions_get_TruncateSpaces(This,pVal)	\
    (This)->lpVtbl -> get_TruncateSpaces(This,pVal)

#define IcwbxDatabaseDownloadUnicodeOptions_put_TruncateSpaces(This,newVal)	\
    (This)->lpVtbl -> put_TruncateSpaces(This,newVal)

#define IcwbxDatabaseDownloadUnicodeOptions_put_ReceiveInfo(This,newVal)	\
    (This)->lpVtbl -> put_ReceiveInfo(This,newVal)

#define IcwbxDatabaseDownloadUnicodeOptions_put_AsyncRequestActive(This,newVal)	\
    (This)->lpVtbl -> put_AsyncRequestActive(This,newVal)

#define IcwbxDatabaseDownloadUnicodeOptions_get_AddByteOrderMark(This,pVal)	\
    (This)->lpVtbl -> get_AddByteOrderMark(This,pVal)

#define IcwbxDatabaseDownloadUnicodeOptions_put_AddByteOrderMark(This,newVal)	\
    (This)->lpVtbl -> put_AddByteOrderMark(This,newVal)

#define IcwbxDatabaseDownloadUnicodeOptions_get_FileDescriptionFileFormat(This,pVal)	\
    (This)->lpVtbl -> get_FileDescriptionFileFormat(This,pVal)

#define IcwbxDatabaseDownloadUnicodeOptions_put_FileDescriptionFileFormat(This,newVal)	\
    (This)->lpVtbl -> put_FileDescriptionFileFormat(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadUnicodeOptions_get_CodePage_Proxy( 
    IcwbxDatabaseDownloadUnicodeOptions * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IcwbxDatabaseDownloadUnicodeOptions_get_CodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadUnicodeOptions_put_CodePage_Proxy( 
    IcwbxDatabaseDownloadUnicodeOptions * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownloadUnicodeOptions_put_CodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadUnicodeOptions_get_ExistingFileOption_Proxy( 
    IcwbxDatabaseDownloadUnicodeOptions * This,
    /* [retval][out] */ cwbdtExistingOutputFileEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadUnicodeOptions_get_ExistingFileOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadUnicodeOptions_put_ExistingFileOption_Proxy( 
    IcwbxDatabaseDownloadUnicodeOptions * This,
    /* [in] */ cwbdtExistingOutputFileEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadUnicodeOptions_put_ExistingFileOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadUnicodeOptions_get_fileDescriptionFile_Proxy( 
    IcwbxDatabaseDownloadUnicodeOptions * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcwbxDatabaseDownloadUnicodeOptions_get_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadUnicodeOptions_put_fileDescriptionFile_Proxy( 
    IcwbxDatabaseDownloadUnicodeOptions * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcwbxDatabaseDownloadUnicodeOptions_put_fileDescriptionFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadUnicodeOptions_get_IncludeLeadingZeros_Proxy( 
    IcwbxDatabaseDownloadUnicodeOptions * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadUnicodeOptions_get_IncludeLeadingZeros_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadUnicodeOptions_put_IncludeLeadingZeros_Proxy( 
    IcwbxDatabaseDownloadUnicodeOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadUnicodeOptions_put_IncludeLeadingZeros_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadUnicodeOptions_get_TruncateSpaces_Proxy( 
    IcwbxDatabaseDownloadUnicodeOptions * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadUnicodeOptions_get_TruncateSpaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadUnicodeOptions_put_TruncateSpaces_Proxy( 
    IcwbxDatabaseDownloadUnicodeOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadUnicodeOptions_put_TruncateSpaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadUnicodeOptions_put_ReceiveInfo_Proxy( 
    IcwbxDatabaseDownloadUnicodeOptions * This,
    /* [in] */ long newVal);


void __RPC_STUB IcwbxDatabaseDownloadUnicodeOptions_put_ReceiveInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadUnicodeOptions_put_AsyncRequestActive_Proxy( 
    IcwbxDatabaseDownloadUnicodeOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadUnicodeOptions_put_AsyncRequestActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadUnicodeOptions_get_AddByteOrderMark_Proxy( 
    IcwbxDatabaseDownloadUnicodeOptions * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcwbxDatabaseDownloadUnicodeOptions_get_AddByteOrderMark_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadUnicodeOptions_put_AddByteOrderMark_Proxy( 
    IcwbxDatabaseDownloadUnicodeOptions * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IcwbxDatabaseDownloadUnicodeOptions_put_AddByteOrderMark_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadUnicodeOptions_get_FileDescriptionFileFormat_Proxy( 
    IcwbxDatabaseDownloadUnicodeOptions * This,
    /* [retval][out] */ cwbdtFDFFormatEnum *pVal);


void __RPC_STUB IcwbxDatabaseDownloadUnicodeOptions_get_FileDescriptionFileFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcwbxDatabaseDownloadUnicodeOptions_put_FileDescriptionFileFormat_Proxy( 
    IcwbxDatabaseDownloadUnicodeOptions * This,
    /* [in] */ cwbdtFDFFormatEnum newVal);


void __RPC_STUB IcwbxDatabaseDownloadUnicodeOptions_put_FileDescriptionFileFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcwbxDatabaseDownloadUnicodeOptions_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_AS400System;

#ifdef __cplusplus

class DECLSPEC_UUID("86F9DB12-15D5-11D2-849C-0004AC94E175")
AS400System;
#endif

EXTERN_C const CLSID CLSID_ClientInfo;

#ifdef __cplusplus

class DECLSPEC_UUID("86F9DB14-15D5-11D2-849C-0004AC94E175")
ClientInfo;
#endif

EXTERN_C const CLSID CLSID_DataQueue;

#ifdef __cplusplus

class DECLSPEC_UUID("86F9DB16-15D5-11D2-849C-0004AC94E175")
DataQueue;
#endif

EXTERN_C const CLSID CLSID_KeyedDataQueue;

#ifdef __cplusplus

class DECLSPEC_UUID("86F9DB1A-15D5-11D2-849C-0004AC94E175")
KeyedDataQueue;
#endif

EXTERN_C const CLSID CLSID_DataQueueAttributes;

#ifdef __cplusplus

class DECLSPEC_UUID("86F9DB1E-15D5-11D2-849C-0004AC94E175")
DataQueueAttributes;
#endif

EXTERN_C const CLSID CLSID_Program;

#ifdef __cplusplus

class DECLSPEC_UUID("86F9DB20-15D5-11D2-849C-0004AC94E175")
Program;
#endif

EXTERN_C const CLSID CLSID_ProgramParameter;

#ifdef __cplusplus

class DECLSPEC_UUID("86F9DB22-15D5-11D2-849C-0004AC94E175")
ProgramParameter;
#endif

EXTERN_C const CLSID CLSID_Command;

#ifdef __cplusplus

class DECLSPEC_UUID("86F9DB27-15D5-11D2-849C-0004AC94E175")
Command;
#endif

EXTERN_C const CLSID CLSID_PackedConverter;

#ifdef __cplusplus

class DECLSPEC_UUID("86F9DB2D-15D5-11D2-849C-0004AC94E175")
PackedConverter;
#endif

EXTERN_C const CLSID CLSID_ZonedConverter;

#ifdef __cplusplus

class DECLSPEC_UUID("86F9DB2F-15D5-11D2-849C-0004AC94E175")
ZonedConverter;
#endif

EXTERN_C const CLSID CLSID_Structure;

#ifdef __cplusplus

class DECLSPEC_UUID("3DEF9935-1673-11D2-849C-0004AC94E175")
Structure;
#endif

EXTERN_C const CLSID CLSID_BinaryData;

#ifdef __cplusplus

class DECLSPEC_UUID("1D60C9E2-3644-11D4-92E2-002035AE9B5D")
BinaryData;
#endif

EXTERN_C const CLSID CLSID_ShortConverter;

#ifdef __cplusplus

class DECLSPEC_UUID("3DEF9937-1673-11D2-849C-0004AC94E175")
ShortConverter;
#endif

EXTERN_C const CLSID CLSID_LongConverter;

#ifdef __cplusplus

class DECLSPEC_UUID("3DEF993A-1673-11D2-849C-0004AC94E175")
LongConverter;
#endif

EXTERN_C const CLSID CLSID_DoubleConverter;

#ifdef __cplusplus

class DECLSPEC_UUID("3DEF993C-1673-11D2-849C-0004AC94E175")
DoubleConverter;
#endif

EXTERN_C const CLSID CLSID_FloatConverter;

#ifdef __cplusplus

class DECLSPEC_UUID("3DEF993E-1673-11D2-849C-0004AC94E175")
FloatConverter;
#endif

EXTERN_C const CLSID CLSID_StringConverter;

#ifdef __cplusplus

class DECLSPEC_UUID("3DEF9941-1673-11D2-849C-0004AC94E175")
StringConverter;
#endif

EXTERN_C const CLSID CLSID_CodePageConverter;

#ifdef __cplusplus

class DECLSPEC_UUID("3DEF9945-1673-11D2-849C-0004AC94E175")
CodePageConverter;
#endif

EXTERN_C const CLSID CLSID_StructureField;

#ifdef __cplusplus

class DECLSPEC_UUID("3DEF9949-1673-11D2-849C-0004AC94E175")
StructureField;
#endif

EXTERN_C const CLSID CLSID_Error;

#ifdef __cplusplus

class DECLSPEC_UUID("3DEF994B-1673-11D2-849C-0004AC94E175")
Error;
#endif

EXTERN_C const CLSID CLSID_SystemNames;

#ifdef __cplusplus

class DECLSPEC_UUID("FDE7ADB2-1A69-11D2-849C-0004AC94E175")
SystemNames;
#endif

EXTERN_C const CLSID CLSID_ProgramParameters;

#ifdef __cplusplus

class DECLSPEC_UUID("FDE7ADB4-1A69-11D2-849C-0004AC94E175")
ProgramParameters;
#endif

EXTERN_C const CLSID CLSID_StructureFields;

#ifdef __cplusplus

class DECLSPEC_UUID("FDE7ADBA-1A69-11D2-849C-0004AC94E175")
StructureFields;
#endif

EXTERN_C const CLSID CLSID_Errors;

#ifdef __cplusplus

class DECLSPEC_UUID("FDE7ADBC-1A69-11D2-849C-0004AC94E175")
Errors;
#endif

EXTERN_C const CLSID CLSID_DataQueueSenderInfo;

#ifdef __cplusplus

class DECLSPEC_UUID("43E0F3E3-3DFA-11D2-8392-0004ACBA1FF2")
DataQueueSenderInfo;
#endif

EXTERN_C const CLSID CLSID_DatabaseTransfer;

#ifdef __cplusplus

class DECLSPEC_UUID("35DD1AA1-0CAB-11D3-8392-C4CC6678F234")
DatabaseTransfer;
#endif

EXTERN_C const CLSID CLSID_DatabaseDownloadRequest;

#ifdef __cplusplus

class DECLSPEC_UUID("35DD1AA3-0CAB-11D3-8392-C4CC6678F234")
DatabaseDownloadRequest;
#endif

EXTERN_C const CLSID CLSID_DatabaseUploadRequest;

#ifdef __cplusplus

class DECLSPEC_UUID("35DD1AA6-0CAB-11D3-8392-C4CC6678F234")
DatabaseUploadRequest;
#endif

EXTERN_C const CLSID CLSID_DatabaseQuerySettings;

#ifdef __cplusplus

class DECLSPEC_UUID("35DD1AA9-0CAB-11D3-8392-C4CC6678F234")
DatabaseQuerySettings;
#endif

EXTERN_C const CLSID CLSID_DatabaseFormatOptions;

#ifdef __cplusplus

class DECLSPEC_UUID("35DD1AAB-0CAB-11D3-8392-C4CC6678F234")
DatabaseFormatOptions;
#endif

EXTERN_C const CLSID CLSID_DatabaseAS400File;

#ifdef __cplusplus

class DECLSPEC_UUID("35DD1AAD-0CAB-11D3-8392-C4CC6678F234")
DatabaseAS400File;
#endif

EXTERN_C const CLSID CLSID_DatabaseUploadPCFile;

#ifdef __cplusplus

class DECLSPEC_UUID("DC72E801-4F12-11D3-8392-CFA6284581C3")
DatabaseUploadPCFile;
#endif

EXTERN_C const CLSID CLSID_DatabaseUploadPCOptions;

#ifdef __cplusplus

class DECLSPEC_UUID("35DD1AAF-0CAB-11D3-8392-C4CC6678F234")
DatabaseUploadPCOptions;
#endif

EXTERN_C const CLSID CLSID_DatabaseUploadBIFFOptions;

#ifdef __cplusplus

class DECLSPEC_UUID("4A8AFC52-A8D9-11D3-91F5-002035AE9B5D")
DatabaseUploadBIFFOptions;
#endif

EXTERN_C const CLSID CLSID_DatabaseUploadWK4Options;

#ifdef __cplusplus

class DECLSPEC_UUID("4A8AFC54-A8D9-11D3-91F5-002035AE9B5D")
DatabaseUploadWK4Options;
#endif

EXTERN_C const CLSID CLSID_DatabaseUpload123Options;

#ifdef __cplusplus

class DECLSPEC_UUID("4A8AFC56-A8D9-11D3-91F5-002035AE9B5D")
DatabaseUpload123Options;
#endif

EXTERN_C const CLSID CLSID_DatabaseUploadExcelXMLOptions;

#ifdef __cplusplus

class DECLSPEC_UUID("4973408E-3A04-43c6-8283-111DC7C3E45D")
DatabaseUploadExcelXMLOptions;
#endif

EXTERN_C const CLSID CLSID_DatabaseDownloadPCFile;

#ifdef __cplusplus

class DECLSPEC_UUID("1582B021-3F56-11D3-8392-ECC0749E73CB")
DatabaseDownloadPCFile;
#endif

EXTERN_C const CLSID CLSID_DatabaseDownloadPCOptions;

#ifdef __cplusplus

class DECLSPEC_UUID("35DD1AB1-0CAB-11D3-8392-C4CC6678F234")
DatabaseDownloadPCOptions;
#endif

EXTERN_C const CLSID CLSID_DatabaseDownloadASCIIOptions;

#ifdef __cplusplus

class DECLSPEC_UUID("35DD1AB3-0CAB-11D3-8392-C4CC6678F234")
DatabaseDownloadASCIIOptions;
#endif

EXTERN_C const CLSID CLSID_DatabaseDownloadTabDelimitedOptions;

#ifdef __cplusplus

class DECLSPEC_UUID("092EA4E2-1E84-11D3-9159-002035AE9B5D")
DatabaseDownloadTabDelimitedOptions;
#endif

EXTERN_C const CLSID CLSID_DatabaseDownloadBIFFOptions;

#ifdef __cplusplus

class DECLSPEC_UUID("35DD1AB5-0CAB-11D3-8392-C4CC6678F234")
DatabaseDownloadBIFFOptions;
#endif

EXTERN_C const CLSID CLSID_DatabaseDownloadWK4Options;

#ifdef __cplusplus

class DECLSPEC_UUID("35DD1AB7-0CAB-11D3-8392-C4CC6678F234")
DatabaseDownloadWK4Options;
#endif

EXTERN_C const CLSID CLSID_DatabaseDownload123Options;

#ifdef __cplusplus

class DECLSPEC_UUID("092EA4E4-1E84-11D3-9159-002035AE9B5D")
DatabaseDownload123Options;
#endif

EXTERN_C const CLSID CLSID_DatabaseDownloadUnicodeOptions;

#ifdef __cplusplus

class DECLSPEC_UUID("1D8BB74F-C53B-4F91-A160-72E1451510F9")
DatabaseDownloadUnicodeOptions;
#endif

EXTERN_C const CLSID CLSID_DatabaseDownloadExcelXMLOptions;

#ifdef __cplusplus

class DECLSPEC_UUID("507770E6-82BE-4b87-8EB5-94E8CDA76753")
DatabaseDownloadExcelXMLOptions;
#endif

EXTERN_C const CLSID CLSID_DatabaseDownloadHTMLOptions;

#ifdef __cplusplus

class DECLSPEC_UUID("35DD1AB9-0CAB-11D3-8392-C4CC6678F234")
DatabaseDownloadHTMLOptions;
#endif

EXTERN_C const CLSID CLSID_DatabaseTransferResults;

#ifdef __cplusplus

class DECLSPEC_UUID("35DD1ABB-0CAB-11D3-8392-C4CC6678F234")
DatabaseTransferResults;
#endif

EXTERN_C const CLSID CLSID_DatabaseDataError;

#ifdef __cplusplus

class DECLSPEC_UUID("092EA4E6-1E84-11D3-9159-002035AE9B5D")
DatabaseDataError;
#endif

EXTERN_C const CLSID CLSID_DatabaseDataErrors;

#ifdef __cplusplus

class DECLSPEC_UUID("092EA4E8-1E84-11D3-9159-002035AE9B5D")
DatabaseDataErrors;
#endif

EXTERN_C const CLSID CLSID_DatabaseUserLibraryList;

#ifdef __cplusplus

class DECLSPEC_UUID("0B3B2CC1-4F03-11D3-8392-C2193F05062D")
DatabaseUserLibraryList;
#endif

EXTERN_C const CLSID CLSID_DatabaseUploadASCIIOptions;

#ifdef __cplusplus

class DECLSPEC_UUID("90F21461-D4DD-11D3-923D-002035AE9B5D")
DatabaseUploadASCIIOptions;
#endif

EXTERN_C const CLSID CLSID_DatabaseUploadUnicodeOptions;

#ifdef __cplusplus

class DECLSPEC_UUID("E5EAF115-40AA-48B7-82F9-7D7B8CCB0E57")
DatabaseUploadUnicodeOptions;
#endif
#endif /* __cwbx_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


