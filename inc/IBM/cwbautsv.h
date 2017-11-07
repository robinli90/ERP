
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Sun Mar 04 17:33:23 2007
 */
/* Compiler settings for C:\spk\sp41c1\cwbautsv.odl:
    Os, W1, Zp8, env=Win32 (32b run)
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

#ifndef __cwbautsv_h__
#define __cwbautsv_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DcwbErrorMessage_FWD_DEFINED__
#define ___DcwbErrorMessage_FWD_DEFINED__
typedef interface _DcwbErrorMessage _DcwbErrorMessage;
#endif 	/* ___DcwbErrorMessage_FWD_DEFINED__ */


#ifndef __cwbErrorMessage_FWD_DEFINED__
#define __cwbErrorMessage_FWD_DEFINED__

#ifdef __cplusplus
typedef class cwbErrorMessage cwbErrorMessage;
#else
typedef struct cwbErrorMessage cwbErrorMessage;
#endif /* __cplusplus */

#endif 	/* __cwbErrorMessage_FWD_DEFINED__ */


#ifndef ___DcwbRemoteCallConversation_FWD_DEFINED__
#define ___DcwbRemoteCallConversation_FWD_DEFINED__
typedef interface _DcwbRemoteCallConversation _DcwbRemoteCallConversation;
#endif 	/* ___DcwbRemoteCallConversation_FWD_DEFINED__ */


#ifndef __cwbRemoteCallConversation_FWD_DEFINED__
#define __cwbRemoteCallConversation_FWD_DEFINED__

#ifdef __cplusplus
typedef class cwbRemoteCallConversation cwbRemoteCallConversation;
#else
typedef struct cwbRemoteCallConversation cwbRemoteCallConversation;
#endif /* __cplusplus */

#endif 	/* __cwbRemoteCallConversation_FWD_DEFINED__ */


#ifndef ___DcwbCommand_FWD_DEFINED__
#define ___DcwbCommand_FWD_DEFINED__
typedef interface _DcwbCommand _DcwbCommand;
#endif 	/* ___DcwbCommand_FWD_DEFINED__ */


#ifndef __cwbCommand_FWD_DEFINED__
#define __cwbCommand_FWD_DEFINED__

#ifdef __cplusplus
typedef class cwbCommand cwbCommand;
#else
typedef struct cwbCommand cwbCommand;
#endif /* __cplusplus */

#endif 	/* __cwbCommand_FWD_DEFINED__ */


#ifndef ___DcwbProgram_FWD_DEFINED__
#define ___DcwbProgram_FWD_DEFINED__
typedef interface _DcwbProgram _DcwbProgram;
#endif 	/* ___DcwbProgram_FWD_DEFINED__ */


#ifndef __cwbProgram_FWD_DEFINED__
#define __cwbProgram_FWD_DEFINED__

#ifdef __cplusplus
typedef class cwbProgram cwbProgram;
#else
typedef struct cwbProgram cwbProgram;
#endif /* __cplusplus */

#endif 	/* __cwbProgram_FWD_DEFINED__ */


#ifndef ___DcwbDataQueue_FWD_DEFINED__
#define ___DcwbDataQueue_FWD_DEFINED__
typedef interface _DcwbDataQueue _DcwbDataQueue;
#endif 	/* ___DcwbDataQueue_FWD_DEFINED__ */


#ifndef __cwbDataQueue_FWD_DEFINED__
#define __cwbDataQueue_FWD_DEFINED__

#ifdef __cplusplus
typedef class cwbDataQueue cwbDataQueue;
#else
typedef struct cwbDataQueue cwbDataQueue;
#endif /* __cplusplus */

#endif 	/* __cwbDataQueue_FWD_DEFINED__ */


#ifndef ___DcwbDataQueueAttr_FWD_DEFINED__
#define ___DcwbDataQueueAttr_FWD_DEFINED__
typedef interface _DcwbDataQueueAttr _DcwbDataQueueAttr;
#endif 	/* ___DcwbDataQueueAttr_FWD_DEFINED__ */


#ifndef __cwbDataQueueAttr_FWD_DEFINED__
#define __cwbDataQueueAttr_FWD_DEFINED__

#ifdef __cplusplus
typedef class cwbDataQueueAttr cwbDataQueueAttr;
#else
typedef struct cwbDataQueueAttr cwbDataQueueAttr;
#endif /* __cplusplus */

#endif 	/* __cwbDataQueueAttr_FWD_DEFINED__ */


#ifndef ___DcwbDataQueueDataAttr_FWD_DEFINED__
#define ___DcwbDataQueueDataAttr_FWD_DEFINED__
typedef interface _DcwbDataQueueDataAttr _DcwbDataQueueDataAttr;
#endif 	/* ___DcwbDataQueueDataAttr_FWD_DEFINED__ */


#ifndef __cwbDataQueueDataAttr_FWD_DEFINED__
#define __cwbDataQueueDataAttr_FWD_DEFINED__

#ifdef __cplusplus
typedef class cwbDataQueueDataAttr cwbDataQueueDataAttr;
#else
typedef struct cwbDataQueueDataAttr cwbDataQueueDataAttr;
#endif /* __cplusplus */

#endif 	/* __cwbDataQueueDataAttr_FWD_DEFINED__ */


#ifndef ___DcwbDatabaseConnection_FWD_DEFINED__
#define ___DcwbDatabaseConnection_FWD_DEFINED__
typedef interface _DcwbDatabaseConnection _DcwbDatabaseConnection;
#endif 	/* ___DcwbDatabaseConnection_FWD_DEFINED__ */


#ifndef __cwbDatabaseConnection_FWD_DEFINED__
#define __cwbDatabaseConnection_FWD_DEFINED__

#ifdef __cplusplus
typedef class cwbDatabaseConnection cwbDatabaseConnection;
#else
typedef struct cwbDatabaseConnection cwbDatabaseConnection;
#endif /* __cplusplus */

#endif 	/* __cwbDatabaseConnection_FWD_DEFINED__ */


#ifndef ___DcwbDatabaseCatalog_FWD_DEFINED__
#define ___DcwbDatabaseCatalog_FWD_DEFINED__
typedef interface _DcwbDatabaseCatalog _DcwbDatabaseCatalog;
#endif 	/* ___DcwbDatabaseCatalog_FWD_DEFINED__ */


#ifndef __cwbDatabaseCatalog_FWD_DEFINED__
#define __cwbDatabaseCatalog_FWD_DEFINED__

#ifdef __cplusplus
typedef class cwbDatabaseCatalog cwbDatabaseCatalog;
#else
typedef struct cwbDatabaseCatalog cwbDatabaseCatalog;
#endif /* __cplusplus */

#endif 	/* __cwbDatabaseCatalog_FWD_DEFINED__ */


#ifndef ___DcwbDatabaseDB2_FWD_DEFINED__
#define ___DcwbDatabaseDB2_FWD_DEFINED__
typedef interface _DcwbDatabaseDB2 _DcwbDatabaseDB2;
#endif 	/* ___DcwbDatabaseDB2_FWD_DEFINED__ */


#ifndef __cwbDatabaseDB2_FWD_DEFINED__
#define __cwbDatabaseDB2_FWD_DEFINED__

#ifdef __cplusplus
typedef class cwbDatabaseDB2 cwbDatabaseDB2;
#else
typedef struct cwbDatabaseDB2 cwbDatabaseDB2;
#endif /* __cplusplus */

#endif 	/* __cwbDatabaseDB2_FWD_DEFINED__ */


#ifndef ___DcwbDatabaseSQL_FWD_DEFINED__
#define ___DcwbDatabaseSQL_FWD_DEFINED__
typedef interface _DcwbDatabaseSQL _DcwbDatabaseSQL;
#endif 	/* ___DcwbDatabaseSQL_FWD_DEFINED__ */


#ifndef __cwbDatabaseSQL_FWD_DEFINED__
#define __cwbDatabaseSQL_FWD_DEFINED__

#ifdef __cplusplus
typedef class cwbDatabaseSQL cwbDatabaseSQL;
#else
typedef struct cwbDatabaseSQL cwbDatabaseSQL;
#endif /* __cplusplus */

#endif 	/* __cwbDatabaseSQL_FWD_DEFINED__ */


#ifndef ___DcwbDatabaseDataFormat_FWD_DEFINED__
#define ___DcwbDatabaseDataFormat_FWD_DEFINED__
typedef interface _DcwbDatabaseDataFormat _DcwbDatabaseDataFormat;
#endif 	/* ___DcwbDatabaseDataFormat_FWD_DEFINED__ */


#ifndef __cwbDatabaseDataFormat_FWD_DEFINED__
#define __cwbDatabaseDataFormat_FWD_DEFINED__

#ifdef __cplusplus
typedef class cwbDatabaseDataFormat cwbDatabaseDataFormat;
#else
typedef struct cwbDatabaseDataFormat cwbDatabaseDataFormat;
#endif /* __cplusplus */

#endif 	/* __cwbDatabaseDataFormat_FWD_DEFINED__ */


#ifndef ___DcwbDatabaseParmMarkerFormat_FWD_DEFINED__
#define ___DcwbDatabaseParmMarkerFormat_FWD_DEFINED__
typedef interface _DcwbDatabaseParmMarkerFormat _DcwbDatabaseParmMarkerFormat;
#endif 	/* ___DcwbDatabaseParmMarkerFormat_FWD_DEFINED__ */


#ifndef __cwbDatabaseParmMarkerFormat_FWD_DEFINED__
#define __cwbDatabaseParmMarkerFormat_FWD_DEFINED__

#ifdef __cplusplus
typedef class cwbDatabaseParmMarkerFormat cwbDatabaseParmMarkerFormat;
#else
typedef struct cwbDatabaseParmMarkerFormat cwbDatabaseParmMarkerFormat;
#endif /* __cplusplus */

#endif 	/* __cwbDatabaseParmMarkerFormat_FWD_DEFINED__ */


#ifndef ___DcwbDatabaseSQLCA_FWD_DEFINED__
#define ___DcwbDatabaseSQLCA_FWD_DEFINED__
typedef interface _DcwbDatabaseSQLCA _DcwbDatabaseSQLCA;
#endif 	/* ___DcwbDatabaseSQLCA_FWD_DEFINED__ */


#ifndef __cwbDatabaseSQLCA_FWD_DEFINED__
#define __cwbDatabaseSQLCA_FWD_DEFINED__

#ifdef __cplusplus
typedef class cwbDatabaseSQLCA cwbDatabaseSQLCA;
#else
typedef struct cwbDatabaseSQLCA cwbDatabaseSQLCA;
#endif /* __cplusplus */

#endif 	/* __cwbDatabaseSQLCA_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __cwbautsv_LIBRARY_DEFINED__
#define __cwbautsv_LIBRARY_DEFINED__

/* library cwbautsv */
/* [helpfile][helpcontext][helpstring][version][uuid] */ 

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("449CFFA0-D65F-11CE-9930-10005A62858B") 
enum __MIDL___MIDL_itf_cwbautsv_0123_0001
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
	cwbCannotStartProcess	= 4026
    } 	cwbConstants;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("449CFFA1-D65F-11CE-9930-10005A62858B") 
enum __MIDL___MIDL_itf_cwbautsv_0123_0002
    {	cwbsvClassInformational	= 0,
	cwbsvClassErrorRetry	= 1,
	cwbsvClassErrorAbort	= 2,
	cwbsvNoErrorMessages	= 6003
    } 	cwbsvConstants;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("449cffa2-d65f-11ce-9930-10005a62858B") 
enum __MIDL___MIDL_itf_cwbautsv_0123_0003
    {	cwbrcInput	= 1,
	cwbrcOutput	= 2,
	cwbrcInout	= 3,
	cwbrcTextConvertInput	= 0x10,
	cwbrcTextConvertOutput	= 0x20,
	cwbrcTextConvert	= 0x30,
	cwbrcInvalidSystemHandle	= 6000,
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
    } 	cwbrcConstants;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("449CFFA3-D65F-11CE-9930-10005A62858B") 
enum __MIDL___MIDL_itf_cwbautsv_0123_0004
    {	cwbdqAll	= 0,
	cwbdqExclude	= 1,
	cwbdqChange	= 2,
	cwbdqUse	= 3,
	cwbdqLibcrtaut	= 4,
	cwbdqSeqLifo	= 0,
	cwbdqSeqFifo	= 1,
	cwbdqSeqKeyed	= 2,
	cwbdqEqual	= 1,
	cwbdqNotEqual	= 2,
	cwbdqGtOrEqual	= 3,
	cwbdqGreater	= 4,
	cwbdqLtOrEqual	= 5,
	cwbdqLess	= 6,
	cwbdqInvalidAttributeHandle	= 6000,
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
	cwbdqUnexpectedError	= 6099
    } 	cwbdqConstants;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("449CFFA4-D65F-11CE-9930-10005A62858B") 
enum __MIDL___MIDL_itf_cwbautsv_0123_0005
    {	cwbdbCannotContactServer	= 6001,
	cwbdbAttributesFailure	= 6002,
	cwbdbServerAlreadyStarted	= 6003,
	cwbdbInvalidDRDAPkgSize	= 6004,
	cwbdbRequestMemoryAllocationFailure	= 6005,
	cwbdbRequestInvalidConversion	= 6006,
	cwbdbServerNotActive	= 6007,
	cwbdbParameterError	= 6008,
	cwbdbCloneCreationError	= 6009,
	cwbdbInvalidDataFormatForConnection	= 6010,
	cwbdbDataFormatInUse	= 6011,
	cwbdbInvalidDataFormatForData	= 6012,
	cwbdbStringArgTooLong	= 6013,
	cwbdbInvalidInternalArg	= 6014,
	cwbdbInvalidNumericArg	= 6015,
	cwbdbInvalidArg	= 6016,
	cwbdbStmtNotSelect	= 6017,
	cwbdbStreamFetchNotComplete	= 6018,
	cwbdbStreamFetchNotActive	= 6019,
	cwbdbMissingDataProcessor	= 6020,
	cwbdbIllegalCloneRequestType	= 6021,
	cwbdbUnsolicitedData	= 6022,
	cwbdbMissingData	= 6023,
	cwbdbParmInvalidBitstream	= 6024,
	cwbdbConsistencyTokenError	= 6025,
	cwbdbInvalidFunction	= 6026,
	cwbdbFormatInvalidArg	= 6027,
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
	cwbdbNlConversionError	= 6052,
	cwbdbCommunicationsError	= 6053,
	cwbdbInvalidArgAPI	= 6054,
	cwbdbMissingDataHandler	= 6055,
	cwbdbRequestDatastreamNotValid	= 6056,
	cwbdbServerUnable	= 6057,
	cwbdbWorkQueueStartError	= 6058,
	cwbdbWorkQueueCreateError	= 6059,
	cwbdbInitializationError	= 6060,
	cwbdbServerAttribsError	= 6061,
	cwbdbClientLevelError	= 6062,
	cwbdbClientLFCError	= 6063,
	cwbdbClientCCSIDError	= 6064,
	cwbdbTranslationIndicatorError	= 6065,
	cwbdbReturnServerAttribsError	= 6066,
	cwbdbServerAttribsRequest	= 6067,
	cwbdbReturnAttribsError	= 6068,
	cwbdbServerAttribsMissing	= 6069,
	cwbdbServerLFCConversionError	= 6070,
	cwbdbServerLevelConversionError	= 6071,
	cwbdbServerLanguageTableError	= 6072,
	cwbdbServerLanguageLibraryError	= 6073,
	cwbdbServerLanguageIDError	= 6074,
	cwbdbCommDequeueError	= 6075,
	cwbdbCommEnqueueError	= 6076,
	cwbdbLastStreamChunk	= 6099,
	cwbdbPeriodNameConv	= 0,
	cwbdbSlashNameConv	= 1,
	cwbdbIgnoreError	= 0,
	cwbdbCorrectError	= 1,
	cwbdbNlssSortHex	= 0,
	cwbdbNlssSortShared	= 1,
	cwbdbNlssSortUnique	= 2,
	cwbdbNlssSortUser	= 3,
	cwbdbNone	= 0,
	cwbdbCursorStability	= 1,
	cwbdbChange	= 2,
	cwbdbAll	= 3,
	cwbdbAllFilesAttributes	= 1,
	cwbdbPhysicalFilesAttributes	= 2,
	cwbdbLogicalFilesAttributes	= 3,
	cwbdbODBCTablesAttributes	= 4,
	cwbdbODBCViewsAttributes	= 5,
	cwbdbAllFiles	= 1,
	cwbdbSourceFiles	= 2,
	cwbdbDataFiles	= 3,
	cwbdbUniqueIndex	= 1,
	cwbdbDuplicateIndex	= 2,
	cwbdbDupNullIndex	= 3,
	cwbdbAllStatements	= 1,
	cwbdbDeclareStatements	= 2,
	cwbdbSelectStatements	= 3,
	cwbdbExecStatements	= 4,
	cwbdbGetLibraryName	= 0x1000000,
	cwbdbGetLibraryDesc	= 0x2000000,
	cwbdbGetLibraryOwner	= 0x4000000,
	cwbdbGetRDBName	= 0x1000000,
	cwbdbGetRDBDevice	= 0x2000000,
	cwbdbGetRDBMode	= 0x4000000,
	cwbdbGetRDBRmtloc	= 0x8000000,
	cwbdbGetRDBLocloc	= 0x10000000,
	cwbdbGetRDBRmtnet	= 0x20000000,
	cwbdbGetRDBTpname	= 0x40000000,
	cwbdbGetRDBDesc	= 0x80000000,
	cwbdbGetRDBTpndisp	= 0x10000,
	cwbdbGetRDBPgm	= 0x40000,
	cwbdbGetRDBPgmlib	= 0x80000,
	cwbdbGetRDBPgmlevel	= 0x100000,
	cwbdbGetSQLPkgLib	= 0x1000000,
	cwbdbGetSQLPkgName	= 0x2000000,
	cwbdbGetSQLPkgDesc	= 0x4000000,
	cwbdbGetSQLStmtLib	= 0x1000000,
	cwbdbGetSQLStmtPkg	= 0x2000000,
	cwbdbGetSQLStmtName	= 0x4000000,
	cwbdbGetSQLStmtType	= 0x8000000,
	cwbdbGetSQLStmtText	= 0x10000000,
	cwbdbGetSQLStmtPmCnt	= 0x20000000,
	cwbdbGetFileLib	= 0x1000000,
	cwbdbGetFileRemarks	= 0x2000000,
	cwbdbGetFileName	= 0x4000000,
	cwbdbGetFileAttrib	= 0x8000000,
	cwbdbGetFileDesc	= 0x20000000,
	cwbdbGetFileColCnt	= 0x40000000,
	cwbdbGetFileAuth	= 0x80000000,
	cwbdbGetMbrLib	= 0x1000000,
	cwbdbGetMbrFile	= 0x2000000,
	cwbdbGetMbrName	= 0x4000000,
	cwbdbGetMbrDesc	= 0x8000000,
	cwbdbGetFmtLib	= 0x1000000,
	cwbdbGetFmtFile	= 0x2000000,
	cwbdbGetFmtName	= 0x4000000,
	cwbdbGetFmtRecLen	= 0x8000000,
	cwbdbGetFmtDesc	= 0x10000000,
	cwbdbGetFldLib	= 0x1000000,
	cwbdbGetFldRemarks	= 0x2000000,
	cwbdbGetFldFile	= 0x4000000,
	cwbdbGetFldName	= 0x10000000,
	cwbdbGetFldDesc	= 0x20000000,
	cwbdbGetFldDataType	= 0x40000000,
	cwbdbGetFldLen	= 0x80000000,
	cwbdbGetFldNull	= 0x10000,
	cwbdbGetFldRadix	= 0x20000,
	cwbdbGetFldPrec	= 0x40000,
	cwbdbGetFldScale	= 0x80000,
	cwbdbGetIdxTblLib	= 0x1000000,
	cwbdbGetIdxTblName	= 0x4000000,
	cwbdbGetIdxUnique	= 0x8000000,
	cwbdbGetIdxIdxLib	= 0x10000000,
	cwbdbGetIdxIdxName	= 0x20000000,
	cwbdbGetIdxColCnt	= 0x40000000,
	cwbdbGetIdxColName	= 0x80000000,
	cwbdbGetIdxColSeq	= 0x10000,
	cwbdbGetIdxCollat	= 0x20000,
	cwbdbGetSpColLib	= 0x1000000,
	cwbdbGetSpColTable	= 0x4000000,
	cwbdbGetSpColColName	= 0x8000000,
	cwbdbGetSpColDataType	= 0x10000000,
	cwbdbGetSpColPrecision	= 0x20000000,
	cwbdbGetSpColLength	= 0x40000000,
	cwbdbGetSpColScale	= 0x80000000,
	cwbdbGetPrKeyLib	= 0x1000000,
	cwbdbGetPrKeyFile	= 0x8000000,
	cwbdbGetPrKeyColID	= 0x10000000,
	cwbdbGetPrKeyColSeq	= 0x20000000,
	cwbdbGetFgPrkeyLib	= 0x1000000,
	cwbdbGetFgPrkeyFile	= 0x4000000,
	cwbdbGetFgPrkeyColID	= 0x8000000,
	cwbdbGetFgKeyLib	= 0x10000000,
	cwbdbGetFgKeyFile	= 0x40000000,
	cwbdbGetFgKeyColID	= 0x80000000,
	cwbdbGetFgKeySeq	= 0x10000,
	cwbdbGetFgKeyUpdate	= 0x20000,
	cwbdbGetFgKeyDelete	= 0x40000,
	cwbdbNotNullable	= 0xf0,
	cwbdbNullable	= 0xf1,
	cwbdbSetLibraryCreateAuthority	= 0,
	cwbdbSetAllAuthority	= 1,
	cwbdbSetChangeAuthority	= 2,
	cwbdbSetExcludeAuthority	= 3,
	cwbdbSetUseAuthority	= 4,
	cwbdbSetSameAuthority	= 5,
	cwbdbDoNotCopyData	= 0,
	cwbdbCopyData	= 1,
	cwbdbNormalPrepare	= 0,
	cwbdbEnhancedPrepare	= 1,
	cwbdbDescAliasNames	= 0xd5,
	cwbdbDescNamesOnly	= 0xe2,
	cwbdbDescLabels	= 0xd3,
	cwbdbCursorNotScrollable	= 0,
	cwbdbCursorScrollable	= 1,
	cwbdbScrollNext	= 0,
	cwbdbScrollPrevious	= 1,
	cwbdbScrollFirst	= 2,
	cwbdbScrollLast	= 3,
	cwbdbScrollBeforeFirst	= 4,
	cwbdbScrollAfterLast	= 5,
	cwbdbScrollCurrent	= 6,
	cwbdbScrollRelative	= 7,
	cwbdbWork	= 0,
	cwbdbHold	= 1,
	cwbdbRead	= 0x80,
	cwbdbWrite	= 0x40,
	cwbdbUpdate	= 0x20,
	cwbdbDelete	= 0x10,
	cwbdbOpenAll	= 0xf0,
	cwbdbSystem	= 0,
	cwbdbLocal	= 1,
	cwbdbPCNoConversion	= 0,
	cwbdbPCString	= 1,
	cwbdbPCLong	= 2,
	cwbdbPCShort	= 3,
	cwbdbPCFloat	= 4,
	cwbdbPCDouble	= 5,
	cwbdbPCPacked	= 6,
	cwbdbPCZoned	= 7,
	cwbdbPCInvalidType	= 8,
	cwbdbPCVarstring	= 9,
	cwbdbPCGraphic	= 10,
	cwbdbPCVargraphic	= 11,
	cwbdbDateFmtJUL	= 0,
	cwbdbDateFmtMDY	= 1,
	cwbdbDateFmtDMY	= 2,
	cwbdbDateFmtYMD	= 3,
	cwbdbDateFmtUSA	= 4,
	cwbdbDateFmtISO	= 5,
	cwbdbDateFmtEUR	= 6,
	cwbdbDateFmtJIS	= 7,
	cwbdbDateSepSlash	= 0,
	cwbdbDateSepDash	= 1,
	cwbdbDateSepPeriod	= 2,
	cwbdbDateSepComma	= 3,
	cwbdbDateSepBlank	= 4,
	cwbdbTimeFmtHMS	= 0,
	cwbdbTimeFmtUSA	= 1,
	cwbdbTimeFmtISO	= 2,
	cwbdbTimeFmtEUR	= 3,
	cwbdbTimeFmtJIS	= 4,
	cwbdbTimeSepColon	= 0,
	cwbdbTimeSepPeriod	= 1,
	cwbdbTimeSepComma	= 2,
	cwbdbTimeSepBlank	= 3,
	cwbdbDecimalSepPeriod	= 0,
	cwbdbDecimalSepComma	= 1,
	cwbdbAddLibraryToFront	= 0,
	cwbdbAddLibraryToEnd	= 1,
	cwbdbDefaultCatalogOrdering	= 1,
	cwbdbODBCTableOrdering	= 2,
	cwbdbODBCTablePrivilegeOrder	= 3,
	cwbdbSynchronousRetrieval	= 0,
	cwbdbAsynchronousRetrieval	= 1,
	cwbdbRetrieveData	= 0x1,
	cwbdbRetrieveDataFormat	= 0x2,
	cwbdbRetrieveSQLCA	= 0x4,
	cwbdbRetrieveParmMarkerFormat	= 0x8
    } 	cwbdbConstants;


DEFINE_GUID(LIBID_cwbautsv,0x82E11B60,0xF4E2,0x11ce,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#ifndef ___DcwbErrorMessage_DISPINTERFACE_DEFINED__
#define ___DcwbErrorMessage_DISPINTERFACE_DEFINED__

/* dispinterface _DcwbErrorMessage */
/* [hidden][helpstring][helpcontext][uuid] */ 


DEFINE_GUID(DIID__DcwbErrorMessage,0x82E11B61,0xF4E2,0x11ce,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("82E11B61-F4E2-11ce-9930-10005A62858B")
    _DcwbErrorMessage : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DcwbErrorMessageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DcwbErrorMessage * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DcwbErrorMessage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DcwbErrorMessage * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DcwbErrorMessage * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DcwbErrorMessage * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DcwbErrorMessage * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DcwbErrorMessage * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DcwbErrorMessageVtbl;

    interface _DcwbErrorMessage
    {
        CONST_VTBL struct _DcwbErrorMessageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DcwbErrorMessage_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DcwbErrorMessage_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DcwbErrorMessage_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DcwbErrorMessage_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DcwbErrorMessage_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DcwbErrorMessage_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DcwbErrorMessage_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DcwbErrorMessage_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_cwbErrorMessage,0xBC530760,0xF4E1,0x11ce,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#ifdef __cplusplus

class DECLSPEC_UUID("BC530760-F4E1-11ce-9930-10005A62858B")
cwbErrorMessage;
#endif

#ifndef ___DcwbRemoteCallConversation_DISPINTERFACE_DEFINED__
#define ___DcwbRemoteCallConversation_DISPINTERFACE_DEFINED__

/* dispinterface _DcwbRemoteCallConversation */
/* [hidden][helpstring][helpcontext][uuid] */ 


DEFINE_GUID(DIID__DcwbRemoteCallConversation,0x82E11B62,0xF4E2,0x11ce,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("82E11B62-F4E2-11ce-9930-10005A62858B")
    _DcwbRemoteCallConversation : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DcwbRemoteCallConversationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DcwbRemoteCallConversation * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DcwbRemoteCallConversation * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DcwbRemoteCallConversation * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DcwbRemoteCallConversation * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DcwbRemoteCallConversation * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DcwbRemoteCallConversation * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DcwbRemoteCallConversation * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DcwbRemoteCallConversationVtbl;

    interface _DcwbRemoteCallConversation
    {
        CONST_VTBL struct _DcwbRemoteCallConversationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DcwbRemoteCallConversation_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DcwbRemoteCallConversation_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DcwbRemoteCallConversation_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DcwbRemoteCallConversation_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DcwbRemoteCallConversation_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DcwbRemoteCallConversation_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DcwbRemoteCallConversation_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DcwbRemoteCallConversation_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_cwbRemoteCallConversation,0xBC530761,0xF4E1,0x11ce,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#ifdef __cplusplus

class DECLSPEC_UUID("BC530761-F4E1-11ce-9930-10005A62858B")
cwbRemoteCallConversation;
#endif

#ifndef ___DcwbCommand_DISPINTERFACE_DEFINED__
#define ___DcwbCommand_DISPINTERFACE_DEFINED__

/* dispinterface _DcwbCommand */
/* [hidden][helpstring][helpcontext][uuid] */ 


DEFINE_GUID(DIID__DcwbCommand,0x82E11B63,0xF4E2,0x11ce,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("82E11B63-F4E2-11ce-9930-10005A62858B")
    _DcwbCommand : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DcwbCommandVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DcwbCommand * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DcwbCommand * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DcwbCommand * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DcwbCommand * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DcwbCommand * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DcwbCommand * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DcwbCommand * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DcwbCommandVtbl;

    interface _DcwbCommand
    {
        CONST_VTBL struct _DcwbCommandVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DcwbCommand_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DcwbCommand_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DcwbCommand_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DcwbCommand_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DcwbCommand_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DcwbCommand_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DcwbCommand_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DcwbCommand_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_cwbCommand,0xBC530762,0xF4E1,0x11ce,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#ifdef __cplusplus

class DECLSPEC_UUID("BC530762-F4E1-11ce-9930-10005A62858B")
cwbCommand;
#endif

#ifndef ___DcwbProgram_DISPINTERFACE_DEFINED__
#define ___DcwbProgram_DISPINTERFACE_DEFINED__

/* dispinterface _DcwbProgram */
/* [hidden][helpstring][helpcontext][uuid] */ 


DEFINE_GUID(DIID__DcwbProgram,0x82E11B64,0xF4E2,0x11ce,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("82E11B64-F4E2-11ce-9930-10005A62858B")
    _DcwbProgram : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DcwbProgramVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DcwbProgram * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DcwbProgram * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DcwbProgram * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DcwbProgram * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DcwbProgram * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DcwbProgram * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DcwbProgram * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DcwbProgramVtbl;

    interface _DcwbProgram
    {
        CONST_VTBL struct _DcwbProgramVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DcwbProgram_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DcwbProgram_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DcwbProgram_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DcwbProgram_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DcwbProgram_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DcwbProgram_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DcwbProgram_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DcwbProgram_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_cwbProgram,0xBC530763,0xF4E1,0x11ce,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#ifdef __cplusplus

class DECLSPEC_UUID("BC530763-F4E1-11ce-9930-10005A62858B")
cwbProgram;
#endif

#ifndef ___DcwbDataQueue_DISPINTERFACE_DEFINED__
#define ___DcwbDataQueue_DISPINTERFACE_DEFINED__

/* dispinterface _DcwbDataQueue */
/* [hidden][helpstring][helpcontext][uuid] */ 


DEFINE_GUID(DIID__DcwbDataQueue,0x82E11B65,0xF4E2,0x11ce,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("82E11B65-F4E2-11ce-9930-10005A62858B")
    _DcwbDataQueue : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DcwbDataQueueVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DcwbDataQueue * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DcwbDataQueue * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DcwbDataQueue * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DcwbDataQueue * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DcwbDataQueue * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DcwbDataQueue * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DcwbDataQueue * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DcwbDataQueueVtbl;

    interface _DcwbDataQueue
    {
        CONST_VTBL struct _DcwbDataQueueVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DcwbDataQueue_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DcwbDataQueue_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DcwbDataQueue_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DcwbDataQueue_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DcwbDataQueue_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DcwbDataQueue_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DcwbDataQueue_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DcwbDataQueue_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_cwbDataQueue,0xBC530764,0xF4E1,0x11ce,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#ifdef __cplusplus

class DECLSPEC_UUID("BC530764-F4E1-11ce-9930-10005A62858B")
cwbDataQueue;
#endif

#ifndef ___DcwbDataQueueAttr_DISPINTERFACE_DEFINED__
#define ___DcwbDataQueueAttr_DISPINTERFACE_DEFINED__

/* dispinterface _DcwbDataQueueAttr */
/* [hidden][helpstring][helpcontext][uuid] */ 


DEFINE_GUID(DIID__DcwbDataQueueAttr,0x82E11B66,0xF4E2,0x11ce,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("82E11B66-F4E2-11ce-9930-10005A62858B")
    _DcwbDataQueueAttr : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DcwbDataQueueAttrVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DcwbDataQueueAttr * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DcwbDataQueueAttr * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DcwbDataQueueAttr * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DcwbDataQueueAttr * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DcwbDataQueueAttr * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DcwbDataQueueAttr * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DcwbDataQueueAttr * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DcwbDataQueueAttrVtbl;

    interface _DcwbDataQueueAttr
    {
        CONST_VTBL struct _DcwbDataQueueAttrVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DcwbDataQueueAttr_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DcwbDataQueueAttr_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DcwbDataQueueAttr_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DcwbDataQueueAttr_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DcwbDataQueueAttr_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DcwbDataQueueAttr_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DcwbDataQueueAttr_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DcwbDataQueueAttr_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_cwbDataQueueAttr,0xBC530765,0xF4E1,0x11ce,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#ifdef __cplusplus

class DECLSPEC_UUID("BC530765-F4E1-11ce-9930-10005A62858B")
cwbDataQueueAttr;
#endif

#ifndef ___DcwbDataQueueDataAttr_DISPINTERFACE_DEFINED__
#define ___DcwbDataQueueDataAttr_DISPINTERFACE_DEFINED__

/* dispinterface _DcwbDataQueueDataAttr */
/* [hidden][helpstring][helpcontext][uuid] */ 


DEFINE_GUID(DIID__DcwbDataQueueDataAttr,0x82E11B67,0xF4E2,0x11ce,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("82E11B67-F4E2-11ce-9930-10005A62858B")
    _DcwbDataQueueDataAttr : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DcwbDataQueueDataAttrVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DcwbDataQueueDataAttr * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DcwbDataQueueDataAttr * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DcwbDataQueueDataAttr * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DcwbDataQueueDataAttr * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DcwbDataQueueDataAttr * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DcwbDataQueueDataAttr * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DcwbDataQueueDataAttr * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DcwbDataQueueDataAttrVtbl;

    interface _DcwbDataQueueDataAttr
    {
        CONST_VTBL struct _DcwbDataQueueDataAttrVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DcwbDataQueueDataAttr_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DcwbDataQueueDataAttr_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DcwbDataQueueDataAttr_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DcwbDataQueueDataAttr_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DcwbDataQueueDataAttr_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DcwbDataQueueDataAttr_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DcwbDataQueueDataAttr_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DcwbDataQueueDataAttr_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_cwbDataQueueDataAttr,0xBC530766,0xF4E1,0x11ce,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#ifdef __cplusplus

class DECLSPEC_UUID("BC530766-F4E1-11ce-9930-10005A62858B")
cwbDataQueueDataAttr;
#endif

#ifndef ___DcwbDatabaseConnection_DISPINTERFACE_DEFINED__
#define ___DcwbDatabaseConnection_DISPINTERFACE_DEFINED__

/* dispinterface _DcwbDatabaseConnection */
/* [hidden][helpstring][helpcontext][uuid] */ 


DEFINE_GUID(DIID__DcwbDatabaseConnection,0x244B2CC1,0xBDC0,0x11CE,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("244B2CC1-BDC0-11CE-9930-10005A62858B")
    _DcwbDatabaseConnection : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DcwbDatabaseConnectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DcwbDatabaseConnection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DcwbDatabaseConnection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DcwbDatabaseConnection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DcwbDatabaseConnection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DcwbDatabaseConnection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DcwbDatabaseConnection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DcwbDatabaseConnection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DcwbDatabaseConnectionVtbl;

    interface _DcwbDatabaseConnection
    {
        CONST_VTBL struct _DcwbDatabaseConnectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DcwbDatabaseConnection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DcwbDatabaseConnection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DcwbDatabaseConnection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DcwbDatabaseConnection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DcwbDatabaseConnection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DcwbDatabaseConnection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DcwbDatabaseConnection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DcwbDatabaseConnection_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_cwbDatabaseConnection,0x244B2CC0,0xBDC0,0x11CE,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#ifdef __cplusplus

class DECLSPEC_UUID("244B2CC0-BDC0-11CE-9930-10005A62858B")
cwbDatabaseConnection;
#endif

#ifndef ___DcwbDatabaseCatalog_DISPINTERFACE_DEFINED__
#define ___DcwbDatabaseCatalog_DISPINTERFACE_DEFINED__

/* dispinterface _DcwbDatabaseCatalog */
/* [hidden][helpstring][helpcontext][uuid] */ 


DEFINE_GUID(DIID__DcwbDatabaseCatalog,0x244B2CC3,0xBDC0,0x11CE,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("244B2CC3-BDC0-11CE-9930-10005A62858B")
    _DcwbDatabaseCatalog : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DcwbDatabaseCatalogVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DcwbDatabaseCatalog * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DcwbDatabaseCatalog * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DcwbDatabaseCatalog * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DcwbDatabaseCatalog * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DcwbDatabaseCatalog * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DcwbDatabaseCatalog * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DcwbDatabaseCatalog * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DcwbDatabaseCatalogVtbl;

    interface _DcwbDatabaseCatalog
    {
        CONST_VTBL struct _DcwbDatabaseCatalogVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DcwbDatabaseCatalog_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DcwbDatabaseCatalog_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DcwbDatabaseCatalog_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DcwbDatabaseCatalog_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DcwbDatabaseCatalog_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DcwbDatabaseCatalog_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DcwbDatabaseCatalog_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DcwbDatabaseCatalog_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_cwbDatabaseCatalog,0x244B2CC2,0xBDC0,0x11CE,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#ifdef __cplusplus

class DECLSPEC_UUID("244B2CC2-BDC0-11CE-9930-10005A62858B")
cwbDatabaseCatalog;
#endif

#ifndef ___DcwbDatabaseDB2_DISPINTERFACE_DEFINED__
#define ___DcwbDatabaseDB2_DISPINTERFACE_DEFINED__

/* dispinterface _DcwbDatabaseDB2 */
/* [hidden][helpstring][helpcontext][uuid] */ 


DEFINE_GUID(DIID__DcwbDatabaseDB2,0x244B2CC5,0xBDC0,0x11CE,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("244B2CC5-BDC0-11CE-9930-10005A62858B")
    _DcwbDatabaseDB2 : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DcwbDatabaseDB2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DcwbDatabaseDB2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DcwbDatabaseDB2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DcwbDatabaseDB2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DcwbDatabaseDB2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DcwbDatabaseDB2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DcwbDatabaseDB2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DcwbDatabaseDB2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DcwbDatabaseDB2Vtbl;

    interface _DcwbDatabaseDB2
    {
        CONST_VTBL struct _DcwbDatabaseDB2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DcwbDatabaseDB2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DcwbDatabaseDB2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DcwbDatabaseDB2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DcwbDatabaseDB2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DcwbDatabaseDB2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DcwbDatabaseDB2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DcwbDatabaseDB2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DcwbDatabaseDB2_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_cwbDatabaseDB2,0x244B2CC4,0xBDC0,0x11CE,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#ifdef __cplusplus

class DECLSPEC_UUID("244B2CC4-BDC0-11CE-9930-10005A62858B")
cwbDatabaseDB2;
#endif

#ifndef ___DcwbDatabaseSQL_DISPINTERFACE_DEFINED__
#define ___DcwbDatabaseSQL_DISPINTERFACE_DEFINED__

/* dispinterface _DcwbDatabaseSQL */
/* [hidden][helpstring][helpcontext][uuid] */ 


DEFINE_GUID(DIID__DcwbDatabaseSQL,0x244B2CC7,0xBDC0,0x11CE,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("244B2CC7-BDC0-11CE-9930-10005A62858B")
    _DcwbDatabaseSQL : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DcwbDatabaseSQLVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DcwbDatabaseSQL * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DcwbDatabaseSQL * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DcwbDatabaseSQL * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DcwbDatabaseSQL * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DcwbDatabaseSQL * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DcwbDatabaseSQL * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DcwbDatabaseSQL * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DcwbDatabaseSQLVtbl;

    interface _DcwbDatabaseSQL
    {
        CONST_VTBL struct _DcwbDatabaseSQLVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DcwbDatabaseSQL_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DcwbDatabaseSQL_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DcwbDatabaseSQL_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DcwbDatabaseSQL_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DcwbDatabaseSQL_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DcwbDatabaseSQL_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DcwbDatabaseSQL_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DcwbDatabaseSQL_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_cwbDatabaseSQL,0x244B2CC6,0xBDC0,0x11CE,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#ifdef __cplusplus

class DECLSPEC_UUID("244B2CC6-BDC0-11CE-9930-10005A62858B")
cwbDatabaseSQL;
#endif

#ifndef ___DcwbDatabaseDataFormat_DISPINTERFACE_DEFINED__
#define ___DcwbDatabaseDataFormat_DISPINTERFACE_DEFINED__

/* dispinterface _DcwbDatabaseDataFormat */
/* [hidden][helpstring][helpcontext][uuid] */ 


DEFINE_GUID(DIID__DcwbDatabaseDataFormat,0x244B2CC9,0xBDC0,0x11CE,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("244B2CC9-BDC0-11CE-9930-10005A62858B")
    _DcwbDatabaseDataFormat : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DcwbDatabaseDataFormatVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DcwbDatabaseDataFormat * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DcwbDatabaseDataFormat * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DcwbDatabaseDataFormat * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DcwbDatabaseDataFormat * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DcwbDatabaseDataFormat * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DcwbDatabaseDataFormat * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DcwbDatabaseDataFormat * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DcwbDatabaseDataFormatVtbl;

    interface _DcwbDatabaseDataFormat
    {
        CONST_VTBL struct _DcwbDatabaseDataFormatVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DcwbDatabaseDataFormat_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DcwbDatabaseDataFormat_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DcwbDatabaseDataFormat_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DcwbDatabaseDataFormat_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DcwbDatabaseDataFormat_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DcwbDatabaseDataFormat_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DcwbDatabaseDataFormat_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DcwbDatabaseDataFormat_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_cwbDatabaseDataFormat,0x244B2CC8,0xBDC0,0x11CE,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#ifdef __cplusplus

class DECLSPEC_UUID("244B2CC8-BDC0-11CE-9930-10005A62858B")
cwbDatabaseDataFormat;
#endif

#ifndef ___DcwbDatabaseParmMarkerFormat_DISPINTERFACE_DEFINED__
#define ___DcwbDatabaseParmMarkerFormat_DISPINTERFACE_DEFINED__

/* dispinterface _DcwbDatabaseParmMarkerFormat */
/* [hidden][helpstring][helpcontext][uuid] */ 


DEFINE_GUID(DIID__DcwbDatabaseParmMarkerFormat,0xC430ED21,0xC03A,0x11CE,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("C430ED21-C03A-11CE-9930-10005A62858B")
    _DcwbDatabaseParmMarkerFormat : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DcwbDatabaseParmMarkerFormatVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DcwbDatabaseParmMarkerFormat * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DcwbDatabaseParmMarkerFormat * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DcwbDatabaseParmMarkerFormat * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DcwbDatabaseParmMarkerFormat * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DcwbDatabaseParmMarkerFormat * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DcwbDatabaseParmMarkerFormat * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DcwbDatabaseParmMarkerFormat * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DcwbDatabaseParmMarkerFormatVtbl;

    interface _DcwbDatabaseParmMarkerFormat
    {
        CONST_VTBL struct _DcwbDatabaseParmMarkerFormatVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DcwbDatabaseParmMarkerFormat_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DcwbDatabaseParmMarkerFormat_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DcwbDatabaseParmMarkerFormat_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DcwbDatabaseParmMarkerFormat_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DcwbDatabaseParmMarkerFormat_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DcwbDatabaseParmMarkerFormat_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DcwbDatabaseParmMarkerFormat_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DcwbDatabaseParmMarkerFormat_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_cwbDatabaseParmMarkerFormat,0xC430ED20,0xC03A,0x11CE,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#ifdef __cplusplus

class DECLSPEC_UUID("C430ED20-C03A-11CE-9930-10005A62858B")
cwbDatabaseParmMarkerFormat;
#endif

#ifndef ___DcwbDatabaseSQLCA_DISPINTERFACE_DEFINED__
#define ___DcwbDatabaseSQLCA_DISPINTERFACE_DEFINED__

/* dispinterface _DcwbDatabaseSQLCA */
/* [hidden][helpstring][helpcontext][uuid] */ 


DEFINE_GUID(DIID__DcwbDatabaseSQLCA,0xC430ED23,0xC03A,0x11CE,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("C430ED23-C03A-11CE-9930-10005A62858B")
    _DcwbDatabaseSQLCA : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DcwbDatabaseSQLCAVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DcwbDatabaseSQLCA * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DcwbDatabaseSQLCA * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DcwbDatabaseSQLCA * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DcwbDatabaseSQLCA * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DcwbDatabaseSQLCA * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DcwbDatabaseSQLCA * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DcwbDatabaseSQLCA * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DcwbDatabaseSQLCAVtbl;

    interface _DcwbDatabaseSQLCA
    {
        CONST_VTBL struct _DcwbDatabaseSQLCAVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DcwbDatabaseSQLCA_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DcwbDatabaseSQLCA_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DcwbDatabaseSQLCA_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DcwbDatabaseSQLCA_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DcwbDatabaseSQLCA_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DcwbDatabaseSQLCA_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DcwbDatabaseSQLCA_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DcwbDatabaseSQLCA_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_cwbDatabaseSQLCA,0xC430ED22,0xC03A,0x11CE,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#ifdef __cplusplus

class DECLSPEC_UUID("C430ED22-C03A-11CE-9930-10005A62858B")
cwbDatabaseSQLCA;
#endif
#endif /* __cwbautsv_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


