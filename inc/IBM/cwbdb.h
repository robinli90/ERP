/***   START of SPECIFICATIONS   ************************************/
/*                                                                  */
/* 5722-XE1  (C) Copyright IBM Corp. 1995,1999                      */
/* All rights reserved.                                             */
/* US Government Users Restricted Rights -                          */
/* Use, duplication or disclosure restricted                        */
/* by GSA ADP Schedule Contract with IBM Corp.                      */
/*                                                                  */
/* Licensed Materials-Property of IBM                               */
/*                                                                  */
/*                                                                  */
/* Module:                                                          */
/*   cwbdb.h                                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   It contains the declarations for the following API's:          */
/*                                                                  */
/*    The following APIs are used to control attributes of the      */
/*    database server.                                              */
/*                                                                  */
/*     cwbDB_ApplyAttributes                                        */
/*     cwbDB_CreateConnectionHandle                                 */
/*     cwbDB_CreateConnectionHandleA                                */
/*     cwbDB_CreateConnectionHandleW                                */
/*     cwbDB_CreateConnectionHandleEx                               */
/*     cwbDB_DeleteConnectionHandle                                 */
/*     cwbDB_GetCommitmentControl                                   */
/*     cwbDB_GetDateFormat                                          */
/*     cwbDB_GetDateSeparator                                       */
/*     cwbDB_GetDecimalSeparator                                    */
/*     cwbDB_GetIgnoreDecimalDataError                              */
/*     cwbDB_GetNamingConvention                                    */
/*     cwbDB_GetRelationalDBName                                    */
/*     cwbDB_GetServerFunctionalLevel                               */
/*     cwbDB_GetTimeFormat                                          */
/*     cwbDB_GetTimeSeparator                                       */
/*     cwbDB_SetCommitmentControl                                   */
/*     cwbDB_SetDateFormat                                          */
/*     cwbDB_SetDateSeparator                                       */
/*     cwbDB_SetDecimalSeparator                                    */
/*     cwbDB_SetIgnoreDecimalDataError                              */
/*     cwbDB_SetNLSS                                                */
/*     cwbDB_SetNLSSA                                               */
/*     cwbDB_SetNLSSW                                               */
/*     cwbDB_SetNamingConvention                                    */
/*     cwbDB_SetRelationalDBName                                    */
/*     cwbDB_SetRelationalDBNameA                                   */
/*     cwbDB_SetRelationalDBNameW                                   */
/*     cwbDB_SetTimeFormat                                          */
/*     cwbDB_SetTimeSeparator                                       */
/*     cwbDB_StartServer                                            */
/*     cwbDB_StartServerDetailed                                    */
/*     cwbDB_StopServer                                             */
/*                                                                  */
/*    The following APIs are specific to the catalog request.       */
/*                                                                  */
/*     cwbDB_CreateCatalogRequestHandle                             */
/*     cwbDB_DeleteCatalogRequestHandle                             */
/*     cwbDB_RetrieveFieldInformation                               */
/*     cwbDB_RetrieveFileInformation                                */
/*     cwbDB_RetrieveForeignKeyInformation                          */
/*     cwbDB_RetrieveIndexInformation                               */
/*     cwbDB_RetrieveLibraryInformation                             */
/*     cwbDB_RetrieveMemberInformation                              */
/*     cwbDB_RetrievePackageStatementInformation                    */
/*     cwbDB_RetrievePrimaryKeyInformation                          */
/*     cwbDB_RetrieveRDBInformation                                 */
/*     cwbDB_RetrieveRecordFormatInformation                        */
/*     cwbDB_RetrieveSQLPackageInformation                          */
/*     cwbDB_RetrieveSpecialColumnInformation                       */
/*     cwbDB_SetFieldName                                           */
/*     cwbDB_SetFieldNameA                                          */
/*     cwbDB_SetFieldNameW                                          */
/*     cwbDB_SetFileAttributes                                      */
/*     cwbDB_SetFileInfoOrdering                                    */
/*     cwbDB_SetFileType                                            */
/*     cwbDB_SetForeignKeyFileName                                  */
/*     cwbDB_SetForeignKeyFileNameA                                 */
/*     cwbDB_SetForeignKeyFileNameW                                 */
/*     cwbDB_SetForeignKeyLibName                                   */
/*     cwbDB_SetForeignKeyLibNameA                                  */
/*     cwbDB_SetForeignKeyLibNameW                                  */
/*     cwbDB_SetFormatName                                          */
/*     cwbDB_SetFormatNameA                                         */
/*     cwbDB_SetFormatNameW                                         */
/*     cwbDB_SetIndexType                                           */
/*     cwbDB_SetLongFileName                                        */
/*     cwbDB_SetLongFileNameA                                       */
/*     cwbDB_SetLongFileNameW                                       */
/*     cwbDB_SetMemberName                                          */
/*     cwbDB_SetMemberNameA                                         */
/*     cwbDB_SetMemberNameW                                         */
/*     cwbDB_SetNullable                                            */
/*     cwbDB_SetPackageName                                         */
/*     cwbDB_SetPackageNameA                                        */
/*     cwbDB_SetPackageNameW                                        */
/*     cwbDB_SetPrimaryKeyFileName                                  */
/*     cwbDB_SetPrimaryKeyFileNameA                                 */
/*     cwbDB_SetPrimaryKeyFileNameW                                 */
/*     cwbDB_SetPrimaryKeyLibName                                   */
/*     cwbDB_SetPrimaryKeyLibNameA                                  */
/*     cwbDB_SetPrimaryKeyLibNameW                                  */
/*     cwbDB_SetRDBName                                             */
/*     cwbDB_SetRDBNameA                                            */
/*     cwbDB_SetRDBNameW                                            */
/*     cwbDB_SetStatementType                                       */
/*                                                                  */
/*    The following APIs are specific to the native database (NDB)  */
/*    request.                                                      */
/*                                                                  */
/*     cwbDB_AddLibraryToList                                       */
/*     cwbDB_AddMember                                              */
/*     cwbDB_ClearMember                                            */
/*     cwbDB_CreateDuplicateFile                                    */
/*     cwbDB_CreateNDBRequestHandle                                 */
/*     cwbDB_CreateSourcePhysicalFile                               */
/*     cwbDB_DeleteFile                                             */
/*     cwbDB_DeleteNDBRequestHandle                                 */
/*     cwbDB_OverrideFile                                           */
/*     cwbDB_RemoveMember                                           */
/*     cwbDB_RemoveOverride                                         */
/*     cwbDB_SetAddLibraryName                                      */
/*     cwbDB_SetAddLibraryNameA                                     */
/*     cwbDB_SetAddLibraryNameW					                    */
/*     cwbDB_SetAddLibraryPosition                                  */
/*     cwbDB_SetAuthority                                           */
/*     cwbDB_SetBaseFile                                            */
/*     cwbDB_SetBaseFileA                                           */
/*     cwbDB_SetBaseFileW                                           */
/*     cwbDB_SetFileText                                            */
/*     cwbDB_SetFileTextA                                           */
/*     cwbDB_SetFileTextW                                           */
/*     cwbDB_SetMaximumMembers                                      */
/*     cwbDB_SetMemberText                                          */
/*     cwbDB_SetMemberTextA                                         */
/*     cwbDB_SetMemberTextW                                         */
/*     cwbDB_SetOverrideInformation                                 */
/*     cwbDB_SetOverrideInformationA                                */
/*     cwbDB_SetOverrideInformationW                                */
/*     cwbDB_SetRecordLength                                        */
/*                                                                  */
/*    The following APIs are specific to the SQL request.           */
/*                                                                  */
/*     cwbDB_ClearPackage                                           */
/*     cwbDB_Close                                                  */
/*     cwbDB_Commit                                                 */
/*     cwbDB_Connect                                                */
/*     cwbDB_GetLOBMaxSize                                          */
/*     cwbDB_CreatePackage                                          */
/*     cwbDB_CreateSQLRequestHandle                                 */
/*     cwbDB_SetDefaultSQLLibraryName                               */
/*     cwbDB_SetDefaultSQLLibraryNameA                              */
/*     cwbDB_SetDefaultSQLLibraryNameW                              */
/*     cwbDB_DeletePackage                                          */
/*     cwbDB_DeleteSQLRequestHandle                                 */
/*     cwbDB_Describe                                               */
/*     cwbDB_DescribeParameterMarkers                               */
/*     cwbDB_DynamicStreamFetch                                     */
/*     cwbDB_DynamicStreamFetchA                                    */
/*     cwbDB_DynamicStreamFetchW                                    */
/*     cwbDB_EndStreamFetch                                         */
/*     cwbDB_Execute                                                */
/*     cwbDB_ExecuteImmediate                                       */
/*     cwbDB_ExtendedDynamicStreamFetch                             */
/*     cwbDB_ExtendedDynamicStreamFetchA                            */
/*     cwbDB_ExtendedDynamicStreamFetchW                            */
/*     cwbDB_Fetch                                                  */
/*     cwbDB_GetExtendedColumnInfo                                  */
/*     cwbDB_GetBaseColumnName                                      */
/*     cwbDB_GetBaseSchemaName                                      */
/*     cwbDB_GetBaseTableName                                       */
/*     cwbDB_GetLabelName                                           */
/*     cwbDB_MoreStreamData                                         */
/*     cwbDB_Open                                                   */
/*     cwbDB_OpenDescribeFetch                                      */
/*     cwbDB_Prepare                                                */
/*     cwbDB_PrepareDescribe                                        */
/*     cwbDB_PrepareDescribeOpenFetch                               */
/*     cwbDB_RetrieveLOBData                                        */
/*     cwbDB_ReturnExtendedDataFormat                               */
/*     cwbDB_ReturnSQLCA                                            */
/*     cwbDB_ReturnParameterMarkerFormat                            */
/*     cwbDB_Rollback                                               */
/*     cwbDB_SetAllowAddStatementToPackage                          */
/*     cwbDB_SetAmbiguousSelectOption                               */
/*     cwbDB_SetAutoCommit                                          */
/*     cwbDB_SetBlockCount                                          */
/*     cwbDB_SetCursorName                                          */
/*     cwbDB_SetCursorNameA                                         */
/*     cwbDB_SetCursorNameW                                         */
/*     cwbDB_SetCursorReuse                                         */
/*     cwbDB_SetDescribeOption                                      */
/*     cwbDB_SetFetchScrollOptions                                  */
/*     cwbDB_SetExtendedDataFormat                                  */
/*     cwbDB_SetHoldIndicator                                       */
/*     cwbDB_SetLOBFieldThreshold                                   */
/*     cwbDB_SetParameterMarkerBlock                                */
/*     cwbDB_SetParameterMarkers                                    */
/*     cwbDB_SetPrepareOption                                       */
/*     cwbDB_SetQueryTimeoutValue                                   */
/*     cwbDB_SetScrollableCursor                                    */
/*     cwbDB_SetStatementName                                       */
/*     cwbDB_SetStatementNameA                                      */
/*     cwbDB_SetStatementNameW                                      */
/*     cwbDB_SetStatementText                                       */
/*     cwbDB_SetStatementTextA                                      */
/*     cwbDB_SetStatementTextW                                      */
/*     cwbDB_SetStreamFetchSyncCount                                */
/*     cwbDB_WriteLOBData                                           */
/*                                                                  */
/*    The following APIs are used with multiple requests types      */
/*    as specified.                                                 */
/*                                                                  */
/*     cwbDB_GetData                  - Catalog, NDB, SQL           */
/*     cwbDB_ReturnData               - Catalog, NDB, SQL           */
/*     cwbDB_SetClientDataCCSID       - Catalog, NDB, SQL           */
/*     cwbDB_SetClientInputCCSID      - Catalog, NDB, SQL           */
/*     cwbDB_ReturnDataFormat         - Catalog, SQL                */
/*     cwbDB_ReturnHostErrorInfo      - Catalog, NDB, SQL           */
/*     cwbDB_SetClientHostErrorCCSID  - Catalog, NDB, SQL           */
/*     cwbDB_SetFileName              - Catalog, NDB                */
/*     cwbDB_SetFileNameA             - Catalog, NDB                */
/*     cwbDB_SetFileNameW             - Catalog, NDB                */
/*     cwbDB_SetLibraryName           - Catalog, NDB, SQL           */
/*     cwbDB_SetLibraryNameA          - Catalog, NDB, SQL           */
/*     cwbDB_SetLibraryNameW          - Catalog, NDB, SQL           */
/*     cwbDB_StoreRequestParameters   - Catalog, NDB, SQL           */
/*                                                                  */
/*    The following APIs are for manipulating the description of    */
/*    data being exchanged between the client and server.           */
/*                                                                  */
/*     cwbDB_CreateDataFormatHandle                                 */
/*     cwbDB_CreateDataHandle                                       */
/*     cwbDB_CreateParameterMarkerFormatHandle                      */
/*     cwbDB_DeleteDataFormatHandle                                 */
/*     cwbDB_DeleteDataHandle                                       */
/*     cwbDB_DeleteParameterMarkerFormatHandle                      */
/*     cwbDB_GetColumnCCSID                                         */
/*     cwbDB_GetColumnCount                                         */
/*     cwbDB_GetColumnLength                                        */
/*     cwbDB_GetColumnName                                          */
/*     cwbDB_GetColumnPrecision                                     */
/*     cwbDB_GetColumnScale                                         */
/*     cwbDB_GetColumnType                                          */
/*     cwbDB_GetConversionIndicator                                 */
/*     cwbDB_GetDataLength                                          */
/*     cwbDB_GetDataPointer                                         */
/*     cwbDB_GetLOBLocator                                          */
/*     cwbDB_GetParameterCCSID                                      */
/*     cwbDB_GetParameterCount                                      */
/*     cwbDB_GetParameterLength                                     */
/*     cwbDB_GetParameterName                                       */
/*     cwbDB_GetParameterPrecision                                  */
/*     cwbDB_GetParameterScale                                      */
/*     cwbDB_GetParameterType                                       */
/*     cwbDB_GetRowSize                                             */
/*     cwbDB_GetSizeOfInputParameters                               */
/*     cwbDB_GetSizeOfOutputParameters                              */
/*     cwbDB_GetSizeOfParameters                                    */
/*     cwbDB_IsParameterInput                                       */
/*     cwbDB_IsParameterInputOutput                                 */
/*     cwbDB_SetClientColumnToNumeric                               */
/*     cwbDB_SetClientColumnToString                                */
/*     cwbDB_SetClientParameterToNumeric                            */
/*     cwbDB_SetClientParameterToString                             */
/*     cwbDB_SetConversionIndicator                                 */
/*     cwbDB_SetConvert65535                                        */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Link with CWBAPI.LIB import library.                           */
/*   This module is to be used in conjunction with CWBDB.DLL.       */
/*                                                                  */
/*   The Database APIs are used to access Catalog, SQL and          */
/*   Native Database (NDB) functions on the AS/400.  Since this     */
/*   API is built on an Object Oriented base, there are handles     */
/*   that correspond to the following classes of objects:           */
/*                                                                  */
/*   CONNECTION - this class of object represents a communication   */
/*   connection to an AS/400 server module.  There may be multiple  */
/*   connections to the same AS/400 system (each connection would   */
/*   result in a separate instance of the database access server    */
/*   process).                                                      */
/*                                                                  */
/*   All functional requests are funnelled through the connection   */
/*   so the connection must be created first and then the resulting */
/*   handle is used when creating the other objects.  Once the      */
/*   connection is created, the server that the connection          */
/*   represents must be started before any request operations can   */
/*   be performed.  Attributes of the server job (such as date      */
/*   format) can be manipulated through the connection object.      */
/*                                                                  */
/*   SQL REQUEST - this class of object is used to request SQL      */
/*   operations to be performed on the AS/400.                      */
/*                                                                  */
/*   The SQL request object allows an application to set various    */
/*   parameters that control the execution of SQL statements on     */
/*   the AS/400.  Among these parameters are the library and SQL    */
/*   package name that allows the application to use "extended      */
/*   dynamic" SQL.  When extended dynamic SQL is used, SQL          */
/*   statements only need to be prepared once.  The prepared        */
/*   statement is stored in the specified package and can be        */
/*   reused at a later time.                                        */
/*                                                                  */
/*   CATALOG REQUEST - this class of object is used to get          */
/*   information about databases and other SQL objects (SQL         */
/*   packages) which reside on the AS/400.                          */
/*                                                                  */
/*   The catalog request allows an application to control both the  */
/*   data to be returned (names, descriptions, etc.) and the        */
/*   objects for which the data is to be returned (for example -    */
/*   returning the descriptions for all files that start with Q     */
/*   in the QIWS library).                                          */
/*                                                                  */
/*   NDB REQUEST - this class of object is used to manipulate       */
/*   database file objects on the AS/400.                           */
/*                                                                  */
/*   DATA FORMAT - this class of object describes data contained    */
/*   in a result set (for example - the result of a SELECT          */
/*   statement or the result of a catalog request.                  */
/*                                                                  */
/*   The data format contains a description for each item in the    */
/*   result set.  That description includes - data type, data       */
/*   length, precision, scale, CCSID, and column name.              */
/*                                                                  */
/*   PARAMETER MARKER FORMAT - this class of object describes       */
/*   data that corresponds to parameter markers that are contained  */
/*   in SQL statements.                                             */
/*                                                                  */
/*   The parameter marker format contains a description for each    */
/*   parameter marker in a prepared SQL statement. That description */
/*   includes - data type, data length, precision, scale, and       */
/*   CCSID.                                                         */
/*                                                                  */
/*   DATA OBJECT - this class of object is used to return data to   */
/*   the calling application.                                       */
/*                                                                  */
/*   In addition to the return codes listed for APIs additional     */
/*   operating system specific return codes may also appear.  The   */
/*   precise meaning of these return codes can be found in the      */
/*   operating system manuals or relevant header files.             */
/*                                                                  */
/********************************************************************/
/*                                                                  */
/* In Windows 95 and Windows NT data can be manipulated in ASCII    */
/* (OEM), or ANSI code pages. The default behavior of these         */
/* database APIs is to use the ASCII code page. If you want your    */
/* program to use the ANSI code page instead, use the               */
/* cwbNL_GetANSICodePage API to retrieve the ANSI code page,        */
/* convert the code page to a CCSID with cwbNL_CodePageToCCSID,     */
/* and then use cwbDB_SetClientDataCCSID and                        */
/* cwbDB_SetClientHostErrorCCSID to change the behavior of these    */
/* DB APIs.                                                         */
/*                                                                  */
/* Unicode is not supported by these APIs.                          */
/*                                                                  */
/***   END OF SPECIFICATIONS   **************************************/

/* Prevent multiple includes */
#if !defined( _CWBDB_H_ )
#define _CWBDB_H_

#include <windows.h>

#include "cwb.h"
#include "cwbcosys.h"


#if defined( __cplusplus )
extern "C"
{
#endif


#define CWBDB_START                          CWB_LAST+1

/*------------------------------------------------------------------*/
/* An error was encountered which prevented the Data Access server  */
/* from being started.                                              */
/*------------------------------------------------------------------*/
#define CWBDB_CANNOT_CONTACT_SERVER          CWBDB_START+1

/*------------------------------------------------------------------*/
/* An error was encountered during attempt to set the Data Access   */
/* server attributes.                                               */
/*------------------------------------------------------------------*/
#define CWBDB_ATTRIBUTES_FAILURE             CWBDB_START+2

/*------------------------------------------------------------------*/
/* An attempt to start the Data Access server was made while a valid*/
/* server was running. Stop the server before restarting it.        */
/*------------------------------------------------------------------*/
#define CWBDB_SERVER_ALREADY_STARTED         CWBDB_START+3

/*------------------------------------------------------------------*/
/* The valid submitted for the DRDA package size was invalid.       */
/*------------------------------------------------------------------*/
#define CWBDB_INVALID_DRDA_PKG_SIZE          CWBDB_START+4

/*------------------------------------------------------------------*/
/* A memory allocation attempt by a request handle failed.          */
/*------------------------------------------------------------------*/
#define CWBDB_REQUEST_MEMORY_ALLOCATION_FAILURE CWBDB_START+5

/*------------------------------------------------------------------*/
/* A Request handle failed in an attempt to convert data.           */
/*------------------------------------------------------------------*/
#define CWBDB_REQUEST_INVALID_CONVERSION CWBDB_START+6

/*------------------------------------------------------------------*/
/* The Data Access server is not started. It must be started before */
/* continuing.                                                      */
/*------------------------------------------------------------------*/
#define CWBDB_SERVER_NOT_ACTIVE              CWBDB_START+7

/*------------------------------------------------------------------*/
/* Attempt to set a parameter failed. Re-try. If error persists,    */
/* there may be a lack of available memory.                         */
/*------------------------------------------------------------------*/
#define CWBDB_PARAMETER_ERROR                CWBDB_START+8

/*------------------------------------------------------------------*/
/* Could not create a clone request.                                */
/*------------------------------------------------------------------*/
#define CWBDB_CLONE_CREATION_ERROR           CWBDB_START+9

/*------------------------------------------------------------------*/
/* The data format object was not valid for this connection.        */
/*------------------------------------------------------------------*/
#define CWBDB_INVALID_DATA_FORMAT_FOR_CONNECTION   CWBDB_START+10

/*------------------------------------------------------------------*/
/* The data format object is already being used by another request. */
/*------------------------------------------------------------------*/
#define CWBDB_DATA_FORMAT_IN_USE             CWBDB_START+11

/*------------------------------------------------------------------*/
/* The data format object does not match the format of the data.    */
/*------------------------------------------------------------------*/
#define CWBDB_INVALID_DATA_FORMAT_FOR_DATA   CWBDB_START+12

/*------------------------------------------------------------------*/
/* The string provided was too long for the parameter.              */
/*------------------------------------------------------------------*/
#define CWBDB_STRING_ARG_TOO_LONG            CWBDB_START+13

/*------------------------------------------------------------------*/
/* Invalid internally generated arguemtn (not user supplied)        */
/*------------------------------------------------------------------*/
#define CWBDB_INVALID_INTERNAL_ARG           CWBDB_START+14

/*------------------------------------------------------------------*/
/* Value of numeric argument is invalid.                            */
/*------------------------------------------------------------------*/
#define CWBDB_INVALID_NUMERIC_ARG            CWBDB_START+15

/*------------------------------------------------------------------*/
/* Value of argument is invalid.                                    */
/*------------------------------------------------------------------*/
#define CWBDB_INVALID_ARG                    CWBDB_START+16

/*------------------------------------------------------------------*/
/* The statement provided was not a SELECT statement. This call     */
/* requires a SELECT statement.                                     */
/*------------------------------------------------------------------*/
#define CWBDB_STMT_NOT_SELECT                CWBDB_START+17

/*------------------------------------------------------------------*/
/* The connection is in stream fetch mode. Cannot perform desired   */
/* operation until stream fetch has ended.                          */
/*------------------------------------------------------------------*/
#define CWBDB_STREAM_FETCH_NOT_COMPLETE      CWBDB_START+18

/*------------------------------------------------------------------*/
/* The connection is not in stream fetch mode and must be in order  */
/* to perform the desired operation.                                */
/*------------------------------------------------------------------*/
#define CWBDB_STREAM_FETCH_NOT_ACTIVE        CWBDB_START+19

/*------------------------------------------------------------------*/
/* Pointer to data processor in request object is null.             */
/*------------------------------------------------------------------*/
#define CWBDB_MISSING_DATA_PROCESSOR         CWBDB_START+20

/*------------------------------------------------------------------*/
/* Cannot create a clone of an attributes request.                  */
/*------------------------------------------------------------------*/
#define CWBDB_ILLEGAL_CLONE_REQUEST_TYPE     CWBDB_START+21

/*------------------------------------------------------------------*/
/* Data were received from the server, but none were requested.     */
/*------------------------------------------------------------------*/
#define CWBDB_UNSOLICITED_DATA               CWBDB_START+22

/*------------------------------------------------------------------*/
/* Data were requested from the server, but not all were received.  */
/*------------------------------------------------------------------*/
#define CWBDB_MISSING_DATA                   CWBDB_START+23

/*------------------------------------------------------------------*/
/* Bitstream within a parameter is invalid.                         */
/*------------------------------------------------------------------*/
#define CWBDB_PARM_INVALID_BITSTREAM         CWBDB_START+24

/*------------------------------------------------------------------*/
/* The data format used to interpret the data from the AS/400 does  */
/* not match the data returned.                                     */
/*------------------------------------------------------------------*/
#define CWBDB_CONSISTENCY_TOKEN_ERROR        CWBDB_START+25

/*------------------------------------------------------------------*/
/* The function is invalid for this type of request.                */
/*------------------------------------------------------------------*/
#define CWBDB_INVALID_FUNCTION               CWBDB_START+26

/*------------------------------------------------------------------*/
/* A parameter value passed to the API was not valid.               */
/*------------------------------------------------------------------*/
#define CWBDB_FORMAT_INVALID_ARG            CWBDB_START+27

/*------------------------------------------------------------------*/
/* The column position passed to the API was not valid.             */
/*------------------------------------------------------------------*/
#define CWBDB_INVALID_COLUMN_POSITION        CWBDB_START+28

/*------------------------------------------------------------------*/
/* The column type passed to the API was not valid.                 */
/*------------------------------------------------------------------*/
#define CWBDB_INVALID_COLUMN_TYPE            CWBDB_START+29

/*------------------------------------------------------------------*/
/* Invalid or corrupted format handle.                              */
/*------------------------------------------------------------------*/
#define CWBDB_ROW_VECTOR_NOT_EMPTY           CWBDB_START+30

/*------------------------------------------------------------------*/
/* Invalid or corrupted format handle.                              */
/*------------------------------------------------------------------*/
#define CWBDB_ROW_VECTOR_EMPTY               CWBDB_START+31

/*------------------------------------------------------------------*/
/* An error occurred while attempting to allocate memory.           */
/*------------------------------------------------------------------*/
#define CWBDB_MEMORY_ALLOCATION_FAILURE      CWBDB_START+32

/*------------------------------------------------------------------*/
/* An invalid type conversion was attempted.                        */
/*------------------------------------------------------------------*/
#define CWBDB_INVALID_CONVERSION             CWBDB_START+33

/*------------------------------------------------------------------*/
/* The data stream received from the host was too short.            */
/*------------------------------------------------------------------*/
#define CWBDB_DATASTREAM_TOO_SHORT           CWBDB_START+34

/*------------------------------------------------------------------*/
/* The database server received a warning from a SQL operation.     */
/*------------------------------------------------------------------*/
#define CWBDB_SQL_WARNING                    CWBDB_START+35

/*------------------------------------------------------------------*/
/* The database server received an error from a SQL operation.      */
/*------------------------------------------------------------------*/
#define CWBDB_SQL_ERROR                      CWBDB_START+36

/*------------------------------------------------------------------*/
/*  The database server received a warning about a parameter used   */
/*  in a SQL operation.                                             */
/*------------------------------------------------------------------*/
#define CWBDB_SQL_PARAMETER_WARNING          CWBDB_START+37

/*------------------------------------------------------------------*/
/* The database server received an error about a parameter used     */
/* in a SQL operation.                                              */
/*------------------------------------------------------------------*/
#define CWBDB_SQL_PARAMETER_ERROR            CWBDB_START+38

/*------------------------------------------------------------------*/
/* The database server returned a warning from a catalog operation. */
/*------------------------------------------------------------------*/
#define CWBDB_LIST_SERVER_WARNING            CWBDB_START+39

/*------------------------------------------------------------------*/
/* The database server returned an error from a catalog operation.  */
/*------------------------------------------------------------------*/
#define CWBDB_LIST_SERVER_ERROR              CWBDB_START+40

/*------------------------------------------------------------------*/
/* The database server returned a warning about a parameter used in */
/* a catalog operation.                                             */
/*------------------------------------------------------------------*/
#define CWBDB_LIST_PARAMETER_WARNING         CWBDB_START+41

/*------------------------------------------------------------------*/
/* The database server returned an error about a parameter used in  */
/* a catalog operation.                                             */
/*------------------------------------------------------------------*/
#define CWBDB_LIST_PARAMETER_ERROR           CWBDB_START+42

/*------------------------------------------------------------------*/
/* The database server returned a warning from a file processing    */
/* operation.                                                       */
/*------------------------------------------------------------------*/
#define CWBDB_NDB_FILE_SERVER_WARNING        CWBDB_START+43

/*------------------------------------------------------------------*/
/* The database server returned an error from a file processing     */
/* operation.                                                       */
/*------------------------------------------------------------------*/
#define CWBDB_NDB_FILE_SERVER_ERROR          CWBDB_START+44

/*------------------------------------------------------------------*/
/* The database server returned a warning about a parameter used in */
/* a file processing operation.                                     */
/*------------------------------------------------------------------*/
#define CWBDB_FILE_PARAMETER_WARNING         CWBDB_START+45

/*------------------------------------------------------------------*/
/* The database server returned an error about a parameter used in  */
/* a file processing operation.                                     */
/*------------------------------------------------------------------*/
#define CWBDB_FILE_PARAMETER_ERROR           CWBDB_START+46

/*------------------------------------------------------------------*/
/* The database server returned a general warning.                  */
/*------------------------------------------------------------------*/
#define CWBDB_GENERAL_SERVER_WARNING         CWBDB_START+47

/*------------------------------------------------------------------*/
/* The database server returned a general error.                    */
/*------------------------------------------------------------------*/
#define CWBDB_GENERAL_SERVER_ERROR           CWBDB_START+48

/*------------------------------------------------------------------*/
/* The database server returned a warning from an exit program.     */
/*------------------------------------------------------------------*/
#define CWBDB_EXIT_PROGRAM_WARNING           CWBDB_START+49

/*------------------------------------------------------------------*/
/* The database server returned an error from an exit program.      */
/*------------------------------------------------------------------*/
#define CWBDB_EXIT_PROGRAM_ERROR             CWBDB_START+50

/*------------------------------------------------------------------*/
/* Target data buffer is smaller than source buffer                 */
/*------------------------------------------------------------------*/
#define CWBDB_DATA_BUFFER_TOO_SMALL         CWBDB_START+51

/*------------------------------------------------------------------*/
/* Received error back from PiNlConverter                           */
/*------------------------------------------------------------------*/
#define CWBDB_NL_CONVERSION_ERROR           CWBDB_START+52

/*------------------------------------------------------------------*/
/* Received a communications error during processing                */
/*------------------------------------------------------------------*/
#define CWBDB_COMMUNICATIONS_ERROR          CWBDB_START+53

/*------------------------------------------------------------------*/
/* Value of argument is invalid - API level.                        */
/*------------------------------------------------------------------*/
#define CWBDB_INVALID_ARG_API                CWBDB_START+54

/*------------------------------------------------------------------*/
/* Data handler not found in data handler list.                     */
/*------------------------------------------------------------------*/
#define CWBDB_MISSING_DATA_HANDLER           CWBDB_START+55

/*------------------------------------------------------------------*/
/* Invalid datastream in catalog request.                           */
/*------------------------------------------------------------------*/
#define CWBDB_REQUEST_DATASTREAM_NOT_VALID   CWBDB_START+56

/*------------------------------------------------------------------*/
/* Server incapable of performing desired function.                 */
/*------------------------------------------------------------------*/
#define CWBDB_SERVER_UNABLE                  CWBDB_START+57

/*------------------------------------------------------------------*/
/*      The next group of return codes are returned by the new      */
/*      cwbDB_StartServerDetailed API.                              */
/* Unable to start server because of client work queue problem.     */
/*------------------------------------------------------------------*/
#define CWBDB_WORK_QUEUE_START_ERROR         CWBDB_START+58

/*------------------------------------------------------------------*/
/* Unable to start server because of client work queue problem.     */
/*------------------------------------------------------------------*/
#define CWBDB_WORK_QUEUE_CREATE_ERROR        CWBDB_START+59

/*------------------------------------------------------------------*/
/* Unable to start server because of client initialization problem. */
/*------------------------------------------------------------------*/
#define CWBDB_INITIALIZATION_ERROR           CWBDB_START+60

/*------------------------------------------------------------------*/
/* Unable to start server because of server attribute problem.      */
/*------------------------------------------------------------------*/
#define CWBDB_SERVER_ATTRIBS_ERROR           CWBDB_START+61

/*------------------------------------------------------------------*/
/* Unable to start server because of set client level problem.      */
/*------------------------------------------------------------------*/
#define CWBDB_CLIENT_LEVEL_ERROR             CWBDB_START+62

/*------------------------------------------------------------------*/
/* Unable to start server because of set client language feature    */
/* code problem.                                                    */
/*------------------------------------------------------------------*/
#define CWBDB_CLIENT_LFC_ERROR               CWBDB_START+63

/*------------------------------------------------------------------*/
/* Unable to start server because of set client CCSID problem.      */
/*------------------------------------------------------------------*/
#define CWBDB_CLIENT_CCSID_ERROR             CWBDB_START+64

/*------------------------------------------------------------------*/
/* Unable to start server because of set translation indicator error*/
/*------------------------------------------------------------------*/
#define CWBDB_TRANSLATION_INDICATOR_ERROR    CWBDB_START+65

/*------------------------------------------------------------------*/
/* Unable to start server because of return server attribute problem*/
/*------------------------------------------------------------------*/
#define CWBDB_RETURN_SERVER_ATTRIBS_ERROR    CWBDB_START+66

/*------------------------------------------------------------------*/
/* Unable to start server because of missing server attributes      */
/* request object.                                                  */
/*------------------------------------------------------------------*/
#define CWBDB_SERVER_ATTRIBS_REQUEST         CWBDB_START+67

/*------------------------------------------------------------------*/
/* Unable to start server because of return attribute problem.      */
/*------------------------------------------------------------------*/
#define CWBDB_RETURN_ATTRIBS_ERROR           CWBDB_START+68

/*------------------------------------------------------------------*/
/* Unable to start server because returned server attributes too    */
/* short (missing data).                                            */
/*------------------------------------------------------------------*/
#define CWBDB_SERVER_ATTRIBS_MISSING         CWBDB_START+69

/*------------------------------------------------------------------*/
/* Unable to start server because of data conversion error on       */
/* server language feature code field of server attributes.         */
/*------------------------------------------------------------------*/
#define CWBDB_SERVER_LFC_CONVERSION_ERROR    CWBDB_START+70

/*------------------------------------------------------------------*/
/* Unable to start server because of data conversion error on       */
/* server functional level field of server attributes.              */
/*------------------------------------------------------------------*/
#define CWBDB_SERVER_LEVEL_CONVERSION_ERROR  CWBDB_START+71

/*------------------------------------------------------------------*/
/* Unable to start server because of data conversion error on       */
/* server language table ID field of server attributes.             */
/*------------------------------------------------------------------*/
#define CWBDB_SERVER_LANGUAGE_TABLE_ERROR    CWBDB_START+72

/*------------------------------------------------------------------*/
/* Unable to start server because of data conversion error on       */
/* server language library ID field of server attributes.           */
/*------------------------------------------------------------------*/
#define CWBDB_SERVER_LANGUAGE_LIBRARY_ERROR  CWBDB_START+73

/*------------------------------------------------------------------*/
/* Unable to start server because of data conversion error on       */
/* server language ID field of server attributes.                   */
/*------------------------------------------------------------------*/
#define CWBDB_SERVER_LANGUAGE_ID_ERROR       CWBDB_START+74

/*------------------------------------------------------------------*/
/* Unable to start server because of communications error.          */
/*------------------------------------------------------------------*/
#define CWBDB_COMM_DEQUEUE_ERROR             CWBDB_START+75

/*------------------------------------------------------------------*/
/* Unable to start server because of communications error.          */
/*------------------------------------------------------------------*/
#define CWBDB_COMM_ENQUEUE_ERROR             CWBDB_START+76

/*------------------------------------------------------------------*/
/* An unsupported column type was found in the data format.         */
/*------------------------------------------------------------------*/
#define CWBDB_UNSUPPORTED_COLUMN_TYPE        CWBDB_START+77

/*------------------------------------------------------------------*/
/* A connection to the database server for the given connection     */
/* handle is already being used by another connection handle which  */
/* was created with the same system object handle.                  */
/*------------------------------------------------------------------*/
#define CWBDB_SERVER_IN_USE                  CWBDB_START+78

/*------------------------------------------------------------------*/
/* Unable to start server because of data conversion error on       */
/* server relational DB  field of server attributes.                */
/*  There is no message or help text for this return code.          */
/*------------------------------------------------------------------*/
#define CWBDB_SERVER_REL_DB_CONVERSION_ERROR    CWBDB_START+79

/*------------------------------------------------------------------*/
/* This function is not available on this version of the host server*/
/*------------------------------------------------------------------*/
#define CWBDB_SERVER_FUNCTION_NOT_AVAILABLE      CWBDB_START + 80

/*------------------------------------------------------------------*/
/* This function is not valid after connected to the host server    */
/*------------------------------------------------------------------*/
#define CWBDB_FUNCTION_NOT_VALID_AFTER_CONNECT   CWBDB_START + 81

/*------------------------------------------------------------------*/
/* The initial relational DB name (IASP) was invalid                */
/*------------------------------------------------------------------*/
#define CWBDB_INVALID_INITIAL_REL_DB_NAME        CWBDB_START + 82

/*------------------------------------------------------------------*/
/* Stream fetch complete. NOTE: Informational; not an error.        */
/*  There is no message or help text for this return code.          */
/*------------------------------------------------------------------*/
#define CWBDB_LAST_STREAM_CHUNK              CWBDB_START+99

/*------------------------------------------------------------------*/
/* TYPEDEFS:                                                        */
/*------------------------------------------------------------------*/

typedef cwb_Handle cwbDB_ConnectionHandle;
typedef cwb_Handle cwbDB_RequestHandle;
typedef cwb_Handle cwbDB_FormatHandle;
typedef cwb_Handle cwbDB_DataHandle;



/*------------------------------------------------------------------*/
/*                                                                  */
/* Definitions for parameter types                                  */
/*                                                                  */
/*------------------------------------------------------------------*/
#define CWBDB_PERIOD_NAME_CONV  0  /* SQL naming convention (.)     */
#define CWBDB_SLASH_NAME_CONV   1  /* Native AS/400 naming convention (/) */

#define CWBDB_IGNORE_ERROR      0  /* Ignore decimal data error     */
#define CWBDB_CORRECT_ERROR     1  /* Correct decimal data error    */

#define CWBDB_NONE              0  /* *NONE - No commitment control */
#define CWBDB_CURSOR_STABILITY  1  /* *CS   - Cursor stability      */
#define CWBDB_CHANGE            2  /* *CHG  - Change                */
#define CWBDB_ALL               3  /* *ALL  - All                   */

#define CWBDB_ALL_FILES_ATTRIBUTES      1 /* All files              */
#define CWBDB_PHYSICAL_FILES_ATTRIBUTES 2 /* Only physical files    */
#define CWBDB_LOGICAL_FILES_ATTRIBUTES  3 /* Logical files          */
#define CWBDB_ODBC_TABLES_ATTRIBUTES    4 /* phys. files, tables, indexes */
#define CWBDB_ODBC_VIEWS_ATTRIBUTES     5 /* logical files and views*/
#define CWBDB_ODBC_SYSTEM_TABLES        6
#define CWBDB_ODBC_TABLES_VIEWS         7
#define CWBDB_ODBC_TABLES_SYSTEM_TABLES 8
#define CWBDB_ODBC_VIEWS_SYSTEM_TABLES  9

#define CWBDB_ALL_FILES         1  /* All files                     */
#define CWBDB_SOURCE_FILES      2  /* Source files                  */
#define CWBDB_DATA_FILES        3  /* Data files                    */

#define CWBDB_DEFAULT_CATALOG_ORDERING   1  /* Use the default order    */
#define CWBDB_ODBC_TABLE_ORDERING        2  /* Order by ODBC tables     */
#define CWBDB_ODBC_TABLE_PRIVILEGE_ORDER 3  /* Order by  ODBC privilege */

#define CWBDB_UNIQUE_INDEX      1  /* Index is unique               */
#define CWBDB_DUPLICATE_INDEX   2  /* Duplicates are allowed        */
#define CWBDB_DUP_NULL_INDEX    3  /* Duplicate null values are allowed */

#define CWBDB_ALL_STATEMENTS     1  /* All statement types          */
#define CWBDB_DECLARE_STATEMENTS 2  /* Declare statements           */
#define CWBDB_SELECT_STATEMENTS  3  /* Select statements            */
#define CWBDB_EXEC_STATEMENTS    4  /* Executable statements        */

#define CWBDB_GET_LIBRARY_NAME  0x01000000 /* Retrieve library name */
#define CWBDB_GET_LIBRARY_DESC  0x02000000 /* Retrieve description  */
#define CWBDB_GET_LIBRARY_OWNER 0x04000000 /* Retrieve owner        */

#define CWBDB_GET_RDB_NAME     0x01000000  /* Remote Relational Database name */
#define CWBDB_GET_RDB_DEVICE   0x02000000  /* Relational Database device */
#define CWBDB_GET_RDB_MODE     0x04000000  /* Relational Database mode */
#define CWBDB_GET_RDB_RMTLOC   0x08000000  /* Relational Database remote location */
#define CWBDB_GET_RDB_LOCLOC   0x10000000  /* Local location        */
#define CWBDB_GET_RDB_RMTNET   0x20000000  /* Remote network        */
#define CWBDB_GET_RDB_TPNAME   0x40000000  /* Remote Transaction Program name */
#define CWBDB_GET_RDB_DESC     0x80000000  /* Relational Database Text description */
#define CWBDB_GET_RDB_TPNDISP  0x00010000  /* Transaction Program name display */
#define CWBDB_GET_RDB_PGM      0x00040000  /* Relational Database program */
#define CWBDB_GET_RDB_PGMLIB   0x00080000  /* Relational Database program library */
#define CWBDB_GET_RDB_PGMLEVEL 0x00100000  /* Relational Database program level */

#define CWBDB_GET_SQLPKG_LIB   0x01000000  /* SQL package library   */
#define CWBDB_GET_SQLPKG_NAME  0x02000000  /* SQL Package name      */
#define CWBDB_GET_SQLPKG_DESC  0x04000000  /* Text description of package*/

#define CWBDB_GET_SQLSTMT_LIB    0x01000000 /* SQL package library  */
#define CWBDB_GET_SQLSTMT_PKG    0x02000000 /* SQL statement package*/
#define CWBDB_GET_SQLSTMT_NAME   0x04000000 /* SQL statement name   */
#define CWBDB_GET_SQLSTMT_TYPE   0x08000000 /* Statement Type       */
#define CWBDB_GET_SQLSTMT_TEXT   0x10000000 /* Text of statement    */
#define CWBDB_GET_SQLSTMT_PM_CNT 0x20000000 /* Parameter marker count*/

#define CWBDB_GET_FILE_LIB     0x01000000  /* Library name          */
#define CWBDB_GET_FILE_REMARKS 0x02000000  /* Remarks               */
#define CWBDB_GET_FILE_NAME    0x04000000  /* File name             */
#define CWBDB_GET_FILE_ATTRIB  0x08000000  /* Attribute             */
#define CWBDB_GET_FILE_TYPE    0x10000000  /* File type (source/db) */
#define CWBDB_GET_FILE_DESC    0x20000000  /* Text description      */
#define CWBDB_GET_FILE_COL_CNT 0x40000000  /* Number of columns     */
#define CWBDB_GET_FILE_AUTH    0x80000000  /* Current authority     */

#define CWBDB_GET_MBR_LIB      0x01000000  /* Library of member     */
#define CWBDB_GET_MBR_FILE     0x02000000  /* Member file           */
#define CWBDB_GET_MBR_NAME     0x04000000  /* Member name           */
#define CWBDB_GET_MBR_DESC     0x08000000  /* Text description      */

#define CWBDB_GET_FMT_LIB      0x01000000  /* Record format library */
#define CWBDB_GET_FMT_FILE     0x02000000  /* Record format file    */
#define CWBDB_GET_FMT_NAME     0x04000000  /* Record format name    */
#define CWBDB_GET_FMT_REC_LEN  0x08000000  /* Record length         */
#define CWBDB_GET_FMT_DESC     0x10000000  /* Text description      */

#define CWBDB_GET_FLD_LIB       0x01000000 /* Field library         */
#define CWBDB_GET_FLD_REMARKS   0x02000000 /* Field remarks         */
#define CWBDB_GET_FLD_FILE      0x04000000 /* Field file            */
#define CWBDB_GET_FLD_NAME      0x10000000 /* Field name            */
#define CWBDB_GET_FLD_DESC      0x20000000 /* Text description      */
#define CWBDB_GET_FLD_DATA_TYPE 0x40000000 /* Data type             */
#define CWBDB_GET_FLD_LEN       0x80000000 /* Length                */
#define CWBDB_GET_FLD_NULL      0x00010000 /* Null capability       */
#define CWBDB_GET_FLD_RADIX     0x00020000 /* Radix                 */
#define CWBDB_GET_FLD_PREC      0x00040000 /* Precision             */
#define CWBDB_GET_FLD_SCALE     0x00080000 /* Scale                 */
#define CWBDB_GET_FLD_CCSID     0x00200000 /* CCSID                 */

#define CWBDB_GET_IDX_TBL_LIB   0x01000000 /* Library name          */
#define CWBDB_GET_IDX_TBL_NAME  0x04000000 /* Table name            */
#define CWBDB_GET_IDX_UNIQUE    0x08000000 /* Index unique rule     */
#define CWBDB_GET_IDX_IDX_LIB   0x10000000 /* Index library         */
#define CWBDB_GET_IDX_IDX_NAME  0x20000000 /* Index name            */
#define CWBDB_GET_IDX_COL_CNT   0x40000000 /* Column count          */
#define CWBDB_GET_IDX_COL_NAME  0x80000000 /* Column names          */
#define CWBDB_GET_IDX_COL_SEQ   0x00010000 /* Column sequence       */
#define CWBDB_GET_IDX_COLLAT    0x00020000 /* Collation sequence    */

#define CWBDB_GET_SP_COL_LIB       0x01000000 /* Library name       */
#define CWBDB_GET_SP_COL_TABLE     0x04000000 /* Table name         */
#define CWBDB_GET_SP_COL_COL_NAME  0x08000000 /* Column name        */
#define CWBDB_GET_SP_COL_DATA_TYPE 0x10000000 /* Data type          */
#define CWBDB_GET_SP_COL_PRECISION 0x20000000 /* Precision          */
#define CWBDB_GET_SP_COL_LENGTH    0x40000000 /* Length             */
#define CWBDB_GET_SP_COL_SCALE     0x80000000 /* Scale              */

/* Primary Key Information constants                                */
#define CWBDB_GET_PR_KEY_LIB       0x01000000 /* Library name       */
#define CWBDB_GET_PR_KEY_FILE      0x08000000 /* File name          */
#define CWBDB_GET_PR_KEY_COL_ID    0x10000000 /* Column ID          */
#define CWBDB_GET_PR_KEY_COL_SEQ   0x20000000 /* Column Sequence    */

/* Foreign Key Primary Key Information constants                    */
#define CWBDB_GET_FG_PRKEY_LIB     0x01000000 /* Library name       */
#define CWBDB_GET_FG_PRKEY_FILE    0x04000000 /* File name          */
#define CWBDB_GET_FG_PRKEY_COL_ID  0x08000000 /* Column ID          */
/* Foreign Key Information constants                                */
#define CWBDB_GET_FG_KEY_LIB       0x10000000 /* Library name       */
#define CWBDB_GET_FG_KEY_FILE      0x40000000 /* File name          */
#define CWBDB_GET_FG_KEY_COL_ID    0x80000000 /* Column ID          */
#define CWBDB_GET_FG_KEY_SEQ       0x00010000 /* Key sequence       */
#define CWBDB_GET_FG_KEY_UPDATE    0x00020000 /* Update rule        */
#define CWBDB_GET_FG_KEY_DELETE    0x00040000 /* Delete rule        */

#define CWBDB_NOT_NULLABLE      0xF0   /* not null capable          */
#define CWBDB_NULLABLE          0xF1   /* Null capable              */

#define CWBDB_SET_LIBRARY_CREATE_AUTHORITY 0 /* *LIBCRTAUT          */
#define CWBDB_SET_ALL_AUTHORITY            1 /* *ALL                */
#define CWBDB_SET_CHANGE_AUTHORITY         2 /* *CHANGE             */
#define CWBDB_SET_EXCLUDE_AUTHORITY        3 /* *EXCLUDE            */
#define CWBDB_SET_USE_AUTHORITY            4 /* *USE                */
#define CWBDB_SET_SAME_AUTHORITY           5 /* *SAME               */

#define CWBDB_DO_NOT_COPY_DATA  0   /* Do not copy data to new file */
#define CWBDB_COPY_DATA         1   /* Copy data to new file        */

#define CWBDB_NORMAL_PREPARE    0   /* Normal prepare (default)     */
#define CWBDB_ENHANCED_PREPARE  1   /* Enhanced prepare             */

#define CWBDB_DESC_ALIAS_NAMES 0xD5 /* Use alias names (default)    */
#define CWBDB_DESC_NAMES_ONLY  0xE2 /* Use names only               */
#define CWBDB_DESC_LABELS      0xD3 /* Use labels                   */

#define CWBDB_CURSOR_NOT_SCROLLABLE 0 /* Non-scrollable (default)   */
#define CWBDB_CURSOR_SCROLLABLE     1 /* Scrollable                 */
#define CWBDB_CURSOR_STATIC_SCROLLABLE     2 /* Static Scrollable   */

#define CWBDB_CURSOR_NOT_SCROLLABLE_ASENSITIVE     0  /*Non-scrollable (default), don’t care about changes */
#define CWBDB_CURSOR_SCROLLABLE_ASENSITIVE         1  /*Scrollable, don’t care about changes               */
#define CWBDB_CURSOR_STATIC_SCROLLABLE_INSENSITIVE 2  /*Static scrollable, insensitive to changes          */
#define CWBDB_CURSOR_SCROLLABLE_SENSITIVE          3  /*Scrollable, sensitive to changes                   */
#define CWBDB_CURSOR_NOT_SCROLLABLE_SENSITIVE      4  /*Non-scrollable, sensitive to changes               */
#define CWBDB_CURSOR_NOT_SCROLLABLE_INSENSITIVE    5  /*Non-scrollable, insensitive to changes             */

#define CWBDB_SCROLL_NEXT         0   /* Fetch next record          */
#define CWBDB_SCROLL_PREVIOUS     1   /* Fetch previous record      */
#define CWBDB_SCROLL_FIRST        2   /* Fetch first record         */
#define CWBDB_SCROLL_LAST         3   /* Fetch last record          */
#define CWBDB_SCROLL_BEFORE_FIRST 4   /* Fetch before first record (BOF)*/
#define CWBDB_SCROLL_AFTER_LAST   5   /* Fetch after last record   (EOF)*/
#define CWBDB_SCROLL_CURRENT      6   /* Fetch current record       */
#define CWBDB_SCROLL_RELATIVE     7   /* Fetch relative from cursor */
#define CWBDB_SCROLL_DIRECT       8   /* Fetch from absolute position */

#define CWBDB_WORK   0                /* Commit/Rollback work option*/
#define CWBDB_HOLD   1                /* Commit/Rollback hold option*/

#define CWBDB_READ     0x80           /* Indicates read intent      */
#define CWBDB_WRITE    0x40           /* Indicates write intent     */
#define CWBDB_UPDATE   0x20           /* Indicates update intent    */
#define CWBDB_DELETE   0x10           /* Indicates delete intent    */
#define CWBDB_OPEN_ALL 0xF0           /* Indicates all of the above */

#define CWBDB_SYSTEM    0             /* Returns system format      */
#define CWBDB_LOCAL     1             /* Returns local format       */

#define CWBDB_PCNOCONVERSION      0        /* No conversion done         */
#define CWBDB_PCSTRING            1        /* character data             */
#define CWBDB_PCLONG              2        /*  4 byte integer            */
#define CWBDB_PCSHORT             3        /*  2 byte integer            */
#define CWBDB_PCFLOAT             4        /*  4 byte floating point     */
#define CWBDB_PCDOUBLE            5        /*  8 byte floating point     */
#define CWBDB_PCPACKED            6        /*    packed decimal          */
#define CWBDB_PCZONED             7        /*    zoned decimal           */
#define CWBDB_PCINVALIDTYPE       8        /*                            */
#define CWBDB_PCVARSTRING         9        /* Varying length string      */
#define CWBDB_PCGRAPHIC          10        /* Graphic data "pure DBCS"   */
#define CWBDB_PCVARGRAPHIC       11        /* Varying length graphic     */
#define CWBDB_PCVARDATALINK      12        /* Varying length DataLink    */
#define CWBDB_PCBLOB             13        /* BLOB data - binary         */
#define CWBDB_PCCLOB             14        /* CLOB data - character      */
#define CWBDB_PCDBCLOB           15        /* Double Byte CLOB           */
#define CWBDB_PCBLOBLOCATOR      16        /* BLOB locator               */
#define CWBDB_PCCLOBLOCATOR      17        /* CLOB locator               */
#define CWBDB_PCDBCLOBLOCATOR    18        /* Double byte CLOB locator   */
#define CWBDB_PCUNSUPPORTEDTYPE  19        /* Unsupported                */
#define CWBDB_PCBIGINT           20        /* Big integer (8 byte)       */
#define CWBDB_PCROWID            21        /* RowID                      */



/* These constants define the SQL type values from  Appendix C of the    */
/* SQL Reference.  Each data type has two versions, one with NC at the   */
/* end of the name, which is null capable and the other without NC at    */
/* the end of the name, which is not null capable.  These constants are  */
/* numbers where the value of the null capable type is odd and the       */
/* value of the not null capable type is even and one less than the      */
/* null capable value for the same type.                                 */

#define CWBDB_SQLNullCapable  1      /* adding to any type makes it null capable */

#define CWBDB_SQLDate                384        /* 384/385 10 byte date  */
#define CWBDB_SQLDateNC              CWBDB_SQLDate + CWBDB_SQLNullCapable
#define CWBDB_SQLTime                388        /* 388/389  8 byte time  */
#define CWBDB_SQLTimeNC              CWBDB_SQLTime + CWBDB_SQLNullCapable
#define CWBDB_SQLTimeStamp           392        /* 392/393 26 byte date/time stamp */
#define CWBDB_SQLTimeStampNC         CWBDB_SQLTimeStamp + CWBDB_SQLNullCapable
#define CWBDB_SQLVarDataLink         396
#define CWBDB_SQLVarDataLinkNC       CWBDB_SQLVarDataLink + CWBDB_SQLNullCapable
#define CWBDB_SQLBLOB                404
#define CWBDB_SQLBLOBNC              CWBDB_SQLBLOB + CWBDB_SQLNullCapable
#define CWBDB_SQLCLOB                408
#define CWBDB_SQLCLOBNC              CWBDB_SQLCLOB + CWBDB_SQLNullCapable
#define CWBDB_SQLDBCLOB              412
#define CWBDB_SQLDBCLOBNC            CWBDB_SQLDBCLOB + CWBDB_SQLNullCapable
#define CWBDB_SQLVaryingString       448        /* 448/449 */
#define CWBDB_SQLVaryingStringNC     CWBDB_SQLVaryingString + CWBDB_SQLNullCapable
#define CWBDB_SQLString              452        /* 452/453 */
#define CWBDB_SQLStringNC            CWBDB_SQLString + CWBDB_SQLNullCapable
#define CWBDB_SQLLongVaryingString   456        /* 456/457 */
#define CWBDB_SQLLongVaryingStringNC CWBDB_SQLLongVaryingString + CWBDB_SQLNullCapable
#define CWBDB_SQLVaryingGraphic      464        /* 464/465 */
#define CWBDB_SQLVaryingGraphicNC    CWBDB_SQLVaryingGraphic + CWBDB_SQLNullCapable
#define CWBDB_SQLGraphic             468        /* 468/469 */
#define CWBDB_SQLGraphicNC           CWBDB_SQLGraphic + CWBDB_SQLNullCapable
#define CWBDB_SQLLongVaryingGraphic  472        /* 472/473 */
#define CWBDB_SQLLongVaryingGraphicNC  CWBDB_SQLLongVaryingGraphic + CWBDB_SQLNullCapable
#define CWBDB_SQLFloat               480        /* 480/481  4 or 8 byte binary float */
#define CWBDB_SQLFloatNC             CWBDB_SQLFloat + CWBDB_SQLNullCapable
#define CWBDB_SQLPacked              484        /* 484/485    packed decimal */
#define CWBDB_SQLPackedNC            CWBDB_SQLPacked + CWBDB_SQLNullCapable
#define CWBDB_SQLZoned               488        /* 488/489    zoned decimal */
#define CWBDB_SQLZonedNC             CWBDB_SQLZoned + CWBDB_SQLNullCapable
#define CWBDB_SQLBigInt              492        /* 492/493  8 byte integer */
#define CWBDB_SQLBigIntNC            CWBDB_SQLBigInt + CWBDB_SQLNullCapable
#define CWBDB_SQLLargeInt            496        /* 496/497  4 byte integer */
#define CWBDB_SQLLargeIntNC          CWBDB_SQLLargeInt + CWBDB_SQLNullCapable
#define CWBDB_SQLSmallInt            500        /* 500/501  2 byte integer */
#define CWBDB_SQLSmallIntNC          CWBDB_SQLSmallInt + CWBDB_SQLNullCapable
#define CWBDB_SQLRowId               904
#define CWBDB_SQLRowIdNC             CWBDB_SQLRowId + CWBDB_SQLNullCapable /* Not valid in the database */
#define CWBDB_SQLBLOBLocator         960
#define CWBDB_SQLBLOBLocatorNC       CWBDB_SQLBLOBLocator + CWBDB_SQLNullCapable
#define CWBDB_SQLCLOBLocator         964
#define CWBDB_SQLCLOBLocatorNC       CWBDB_SQLCLOBLocator + CWBDB_SQLNullCapable
#define CWBDB_SQLDBCLOBLocator       968
#define CWBDB_SQLDBCLOBLocatorNC     CWBDB_SQLDBCLOBLocator + CWBDB_SQLNullCapable
#define CWBDB_SQLInvalidType         8


/* These are some SQL limits for Appendix A of the SQL Reference         */
#define CWBDB_MAX_COLUMN_NAME     30  /* Longest unqualified column name */
#define CWBDB_MAX_PARAMETER_NAME  64  /* Longest unqualified SQL parameter name */



#define CWBDB_PATTERNMATCH_LIB      0      /* Library                    */
#define CWBDB_PATTERNMATCH_FILE     1      /* File                       */
#define CWBDB_PATTERNMATCH_MBR      2      /* Member                     */
#define CWBDB_PATTERNMATCH_FIELD    3      /* Field                      */
#define CWBDB_PATTERNMATCH_FORMAT   4      /* Format                     */
#define CWBDB_PATTERNMATCH_RDB      5      /* RDB                        */
#define CWBDB_PATTERNMATCH_SQLPKG   6      /* SQL Package                */

#define CWBDB_DATE_FMT_JUL          0      /* Julian                     */
#define CWBDB_DATE_FMT_MDY          1      /* month day year             */
#define CWBDB_DATE_FMT_DMY          2      /* day month year             */
#define CWBDB_DATE_FMT_YMD          3      /* year month day             */
#define CWBDB_DATE_FMT_USA          4      /* USA                        */
#define CWBDB_DATE_FMT_ISO          5      /* ISO                        */
#define CWBDB_DATE_FMT_EUR          6      /* IBM Europe                 */
#define CWBDB_DATE_FMT_JIS          7      /* IBM Japan                  */

#define CWBDB_DATE_SEP_SLASH        0      /* slash    03/17/94          */
#define CWBDB_DATE_SEP_DASH         1      /* dash     03-17-94          */
#define CWBDB_DATE_SEP_PERIOD       2      /* period   03.17.94          */
#define CWBDB_DATE_SEP_COMMA        3      /* comma    03,17,94          */
#define CWBDB_DATE_SEP_BLANK        4      /* blank    03 17 94          */

#define CWBDB_TIME_FMT_HMS          0      /* hours minutes seconds      */
#define CWBDB_TIME_FMT_USA          1      /* USA                        */
#define CWBDB_TIME_FMT_ISO          2      /* ISO                        */
#define CWBDB_TIME_FMT_EUR          3      /* Europe                     */
#define CWBDB_TIME_FMT_JIS          4      /* Japan                      */

#define CWBDB_TIME_SEP_COLON        0      /* colon    11:10:03          */
#define CWBDB_TIME_SEP_PERIOD       1      /* period   11.10.03          */
#define CWBDB_TIME_SEP_COMMA        2      /* comma    11,10,03          */
#define CWBDB_TIME_SEP_BLANK        3      /* blank    11 10 03          */

#define CWBDB_DECIMAL_SEP_PERIOD    0      /* period     123.45          */
#define CWBDB_DECIMAL_SEP_COMMA     1      /* comma      123,45          */

#define CWBDB_NLSS_SORT_HEX         0      /* *HEX                       */
#define CWBDB_NLSS_SORT_SHARED      1      /* *SHARED                    */
#define CWBDB_NLSS_SORT_UNIQUE      2      /* *UNIQUE                    */
#define CWBDB_NLSS_SORT_USER        3      /* *USER                      */

#define CWBDB_PZ_PC_SIGN            0      /* Packed/zoned use PC sign   */
#define CWBDB_PZ_400_SIGN           1      /* Packed/zoned use 400 sign  */

#define CWBDB_PZ_LEAVE_UNXLATE      0      /* Ignore untranslateble p/z  */
#define CWBDB_PZ_UNXLATE_ERROR      1      /* Untranslateble p/z is error*/

#define CWBDB_ADD_LIBRARY_TO_FRONT  0      /* Add library to front of list*/
#define CWBDB_ADD_LIBRARY_TO_END    1      /* Add library to end of list  */


#define CWBDB_UPDATEABLE            0      /* Ambiguous Select updateable */
#define CWBDB_READONLY              1      /* Ambiguous Select read only  */

#define CWBDB_CLOSE_ALL_CURSORS     0xF1   /* Close cursor/all result sets*/
#define CWBDB_CLOSE_CURRENT_CURSOR  0xF2   /* Close current result set    */

#define CWBDB_PM_INPUT_ONLY           1    /* Input only parameter        */
#define CWBDB_PM_INPUT_OUTPUT         2    /* Input output parameter      */
#define CWBDB_PM_OUTPUT_ONLY          3    /* Output only parameter       */

#define CWBDB_NO_AUTO_COMMIT          0    /* Do not perform implicit commits.*/
#define CWBDB_AUTO_COMMIT             1    /* Implicit commits will be done.  */


/*                                                                       */
/* The following bit definitions apply to the extended column            */
/* information returned from cwbDB_GetExtendedColumnInfo.                */
/* The extended column info is a 4-byte field which is mapped below.     */

/* Updatability - column is either writeable or read-only                */
#define CWBDB_COLUMNINFO_UPDATE_READONLY     0xF0000000
#define CWBDB_COLUMNINFO_UPDATE_WRITEABLE    0xF1000000

/* Searchability - these flags are mutually exclusive                    */
#define CWBDB_COLUMNINFO_SEARCHABLE_NEVER         0x00F00000
#define CWBDB_COLUMNINFO_SEARCHABLE_LIKEONLY      0x00F10000  /* unused  */
#define CWBDB_COLUMNINFO_SEARCHABLE_ALLEXCEPTLIKE 0x00F20000
#define CWBDB_COLUMNINFO_SEARCHABLE_ALWAYS        0x00F30000

/* Identity column   */
#define CWBDB_COLUMNINFO_IDENTITY_COLUMN   0x00008000

/* Column generation mode - Applies to both identity-column types and   */
/* rowid types.  Specifies whether it is generated always or by         */
/* default.                                                             */
#define CWBDB_COLUMNINFO_GENERATION_DEFAULT 0x00004000

/* Part of any index */
#define CWBDB_COLUMNINFO_PARTOFANYINDEX    0x00002000

/* Column comprises a unique index by itself */
#define CWBDB_COLUMNINFO_LONEUNIQUEINDEX   0x00001000

/* Column is part of a unique index */
#define CWBDB_COLUMNINFO_PARTOFUNIQUEINDEX 0x00000800

/* Parameter values for cwbDB_SetExtendedDataFormat                      */
#define CWBDB_USE_EXTENDED_FORMAT  0xF1     /* use extended data fromat  */
#define CWBDB_USE_NORMAL_FORMAT    0xF0     /* use normal data  format   */


/*------------------------------------------------------------------*/
/*                                                                  */
/* Structure Name:  cwbDB_SQLCA                                     */
/*                                                                  */
/* Used With APIs:  cwbDB_ReturnSQLCA                               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/*------------------------------------------------------------------*/

#include "CWBPACK1.H"
  typedef struct
  {
   unsigned char  sqlcaid[8];     /* Eyecatcher = 'SQLCA   '        */
   long           sqlcabc;        /* SQLCA size in bytes = 136      */
   long           sqlcode;        /* SQL return code                */
   short          sqlerrml;       /* Length for SQLERRMC            */
   unsigned char  sqlerrmc[70];   /* Error message tokens           */
   unsigned char  sqlerrp[8];     /* Diagnostic information         */
   long           sqlerrd[6];     /* Diagnostic information         */
   unsigned char  sqlwarn[11];    /* Warning flags                  */
   unsigned char  sqlext[5];      /* Reserved                       */
  } cwbDB_SQLCA;
#include "CWBPACK0.H"


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_AddLibraryToList                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Add a library to the AS/400 library list.                      */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for List or SQL requests.                */
/*                                                                  */
/*   The cwbDB_AddLibraryToList API may be called after setting the */
/*   position in the library list at which the library is to be     */
/*   added using the cwbDB_SetAddLibraryPosition API.               */
/*                                                                  */
/*   The cwbDB_AddLibraryToList API should be called after setting  */
/*   the library name in the request via the                        */
/*   cwbDB_SetAddLibraryName API.                                   */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/*   A call to cwbDB_ReturnHostErrorInfo is needed in order         */
/*   determine the success of the operation for this API. Calling   */
/*   cwbDB_ReturnHostErrorInfo prior to calling this API will       */
/*   result in a synchronous operation (the application will not    */
/*   get control back until the result is returned to the PC from   */
/*   the AS/400).                                                   */
/*                                                                  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_AddLibraryToList(
                             cwbDB_RequestHandle  request,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_AddMember                                                */
/*                                                                  */
/* Purpose:                                                         */
/*   Add a member to a file on the AS/400.                          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for List or SQL requests.                */
/*                                                                  */
/*   The cwbDB_AddMember API should be called after setting the     */
/*   desired values in the request.                                 */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/*   A call to cwbDB_ReturnHostErrorInfo is needed in order         */
/*   determine the success of the operation for this API. Calling   */
/*   cwbDB_ReturnHostErrorInfo prior to calling this API will       */
/*   result in a synchronous operation (the application will not    */
/*   get control back until the result is returned to the PC from   */
/*   the AS/400).                                                   */
/*                                                                  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_AddMember(
                             cwbDB_RequestHandle  request,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_ApplyAttributes                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   Activates the changes that were made to server attributes      */
/*   by previous calls - (naming convention, commitment control,    */
/*   etc.)  Use this to change server attributes after the server   */
/*   has been started.                                              */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*       Handle to connection to AS/400 database access server      */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is only needed if the server attributes are changed   */
/*   after the server has been started (cwbDB_StartServer).         */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_ApplyAttributes(
                             cwbDB_ConnectionHandle  connection,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_ClearMember                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Clear data from a member in an AS/400 file.                    */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for List or SQL requests.                */
/*                                                                  */
/*   The cwbDB_ClearMember API should be called after setting the   */
/*   desired values in the request.                                 */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/*   A call to cwbDB_ReturnHostErrorInfo is needed in order         */
/*   determine the success of the operation for this API.  Calling  */
/*   cwbDB_ReturnHostErrorInfo prior to calling this API will       */
/*   result in a synchronous operation (the application will not    */
/*   get control back until the result is returned to the PC from   */
/*   the AS/400).                                                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_ClearMember(
                             cwbDB_RequestHandle  request,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_ClearPackage                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Clear all statements from a SQL package.                       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/*   The cwbDB_ClearPackage API should be called after setting the  */
/*   desired values in the request.                                 */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/*   A call to cwbDB_ReturnHostErrorInfo is needed in order         */
/*   determine the success of the operation for this API.  Calling  */
/*   cwbDB_ReturnHostErrorInfo prior to calling this API will       */
/*   result in a synchronous operation (the application will not    */
/*   get control back until the result is returned to the PC from   */
/*   the AS/400).                                                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_ClearPackage(
                             cwbDB_RequestHandle  request,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_Close                                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   Close an open cursor.                                          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/*   The cwbDB_Close API should be called after setting the desired */
/*   values in the request.                                         */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_Close(
                             cwbDB_RequestHandle  request,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_Commit                                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Perform a commit operation to commit a unit of work.           */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/*   The cwbDB_Commit API should be called after setting the        */
/*   desired values in the request.                                 */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_Commit(
                             cwbDB_RequestHandle  request,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_Connect                                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   Perform a Distributed Relational Database Architecture (DRDA)  */
/*   connection management function.  This API is used to establish */
/*   and switch between connections to other Relational Databases.  */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/*   The cwbDB_Connect API should be called after setting the       */
/*   desired values in the request.                                 */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/*   A call to either cwbDB_ReturnHostErrorInfo or                  */
/*   cwbDB_ReturnSQLCA prior to this call will allow an application */
/*   to determine the success of the API operation.                 */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_Connect(
                             cwbDB_RequestHandle  request,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_CreateCatalogRequestHandle                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Allocate a handle to a database request.  This handle will     */
/*   be used on subsequent API calls that request object            */
/*   information.                                                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*           Handle to the connection which will be used when       */
/*           servicing the request.                                 */
/*                                                                  */
/*   cwbDB_RequestHandle *request - output                          */
/*           Pointer to a cwbDB_RequestHandle where the handle      */
/*           of the Request will be returned.                       */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_CreateCatalogRequestHandle(
                             cwbDB_ConnectionHandle  connection,
                             cwbDB_RequestHandle    *request,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_CreateConnectionHandle                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Allocate a handle to an AS/400 database access server.         */
/*                                                                  */
/* Parameters:                                                      */
/*   const char *systemName - input                                 */
/*           Pointer to an ASCIIZ string that contains the name     */
/*           of the system from which database requests will be     */
/*           serviced.                                              */
/*                                                                  */
/*   cwbDB_ConnectionHandle *connection - output                    */
/*           Pointer to a cwbDB_ConnectionHandle where the handle   */
/*           of the connection will be returned.                    */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDB_CreateConnectionHandle(
                             const char             *systemName,
                             cwbDB_ConnectionHandle *connection,
                             cwbSV_ErrHandle         errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDB_CreateConnectionHandleA(
                             LPCSTR                    systemName,
                             cwbDB_ConnectionHandle   *connection,
                             cwbSV_ErrHandle           errorHandle);
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDB_CreateConnectionHandleW(
                             LPCWSTR                   systemName,
                             cwbDB_ConnectionHandle   *connection,
                             cwbSV_ErrHandle           errorHandle );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDB_CreateConnectionHandle    cwbDB_CreateConnectionHandleW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDB_CreateConnectionHandle    cwbDB_CreateConnectionHandleA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_CreateConnectionHandleEx                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   Allocate a handle to an AS/400 database access server.         */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbCO_SysHandle sysHandle - input                              */
/*           Handle to a system object.                             */
/*                                                                  */
/*   cwbDB_ConnectionHandle* connection - output                    */
/*           Pointer to a cwbDB_ConnectionHandle where the handle   */
/*           of the connection will be returned.                    */
/*                                                                  */
/*     cwbSV_ErrHandle errorHandle - input                          */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   CWB_OK   - no error occurred                                   */
/*   CWB_NOT_ENOUGH_MEMORY - insufficient memory                    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This function requires that you have previously issued:        */
/*     cwbCO_CreateSystem()                                         */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_CreateConnectionHandleEx(
                             cwbCO_SysHandle sysHandle,
                             cwbDB_ConnectionHandle* connection,
                             cwbSV_ErrHandle errorHandle  );

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_CreateDataFormatHandle                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Allocate a handle to a description of SQL data.                */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*       Handle to connection to AS/400 database access server      */
/*                                                                  */
/*   cwbDB_FormatHandle *format - output                            */
/*           Pointer to a cwbDB_FormatHandle where the handle       */
/*           of the data format will be returned.                   */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_CreateDataFormatHandle(
                             cwbDB_ConnectionHandle  connection,
                             cwbDB_FormatHandle     *format,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_CreateDataHandle                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Allocate a handle to a data object.                            */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_DataHandle *dataHandle - output                          */
/*           Pointer to a cwbDB_DataHandle where the handle         */
/*           of a data object will be returned.                     */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The cwbDB_CreateDataHandle is used prior to requesting various */
/*   pieces of information to be returned to an application.  In    */
/*   general, if a the information being requested has a varying    */
/*   length, the information will be returned using a data handle.  */
/*   This mechanism moves the responsibility of allocating the      */
/*   memory that is to contain the data from the calling            */
/*   application to the API.  When finished with the data handle,   */
/*   the cwbDB_DeleteDataHandle API should be called to free any    */
/*   resources that are associated with the data handle.            */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_CreateDataHandle(
                             cwbDB_DataHandle *dataHandle,
                             cwbSV_ErrHandle   errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_CreateDuplicateFile                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Create a file based on existing file.                          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwb_Boolean copyDataIndicator - input                          */
/*           Boolean value that indicates whether the data from the */
/*           base file is to be copied into the duplicate file.     */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use one of the defined values for the copyDataIndicator:       */
/*                    CWBDB_DO_NOT_COPY_DATA                        */
/*                    CWBDB_COPY_DATA                               */
/*                                                                  */
/*   This API is not valid for List or SQL requests.                */
/*                                                                  */
/*   The cwbDB_CreateDuplicateFile API should be called after       */
/*   setting the desired values in the request.                     */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/*   A call to cwbDB_ReturnHostErrorInfo is needed in order         */
/*   determine the success of the operation for this API.  Calling  */
/*   cwbDB_ReturnHostErrorInfo prior to calling this API will       */
/*   result in a synchronous operation (the application will not    */
/*   get control back until the result is returned to the PC from   */
/*   the AS/400).                                                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_CreateDuplicateFile(
                             cwbDB_RequestHandle  request,
                             cwb_Boolean          copyDataIndicator,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_CreateNDBRequestHandle                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Allocate a handle to a database request.  This handle will     */
/*   be used on subsequent API calls that request operations to     */
/*   be performed with AS/400 file objects.                         */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*           Handle to the connection which will be used when       */
/*           servicing the request.                                 */
/*                                                                  */
/*   cwbDB_RequestHandle *request - output                          */
/*           Pointer to a cwbDB_RequestHandle where the handle      */
/*           of the Request will be returned.                       */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_CreateNDBRequestHandle(
                             cwbDB_ConnectionHandle  connection,
                             cwbDB_RequestHandle    *request,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_CreatePackage                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Create a SQL package for preparing statements.                 */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/*   The cwbDB_CreatePackage API should be called after             */
/*   setting the desired values in the request.                     */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_CreatePackage(
                             cwbDB_RequestHandle  request,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_CreateParameterMarkerFormatHandle                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Allocate a handle to a description of SQL parameter marker     */
/*   data.                                                          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*       Handle to connection to AS/400 database access server      */
/*                                                                  */
/*   cwbDB_FormatHandle *format - output                            */
/*           Pointer to a cwbDB_FormatHandle where the handle       */
/*           of the parameter marker format will be returned.       */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_CreateParameterMarkerFormatHandle(
                             cwbDB_ConnectionHandle  connection,
                             cwbDB_FormatHandle     *format,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_CreateSourcePhysicalFile                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   Create a source file on the AS/400.                            */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for List or SQL requests.                */
/*                                                                  */
/*   The cwbDB_CreateSourcePhysicalFile API should be called after  */
/*   setting the desired values in the request.                     */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/*   A call to cwbDB_ReturnHostErrorInfo is needed in order         */
/*   determine the success of the operation for this API.  Calling  */
/*   cwbDB_ReturnHostErrorInfo prior to calling this API will       */
/*   result in a synchronous operation (the application will not    */
/*   get control back until the result is returned to the PC from   */
/*   the AS/400).                                                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_CreateSourcePhysicalFile(
                             cwbDB_RequestHandle  request,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_CreateSQLRequestHandle                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Allocate a handle to a database request.  This handle will     */
/*   be used on subsequent API calls that request SQL services.     */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*           Handle to the connection which will be used when       */
/*           servicing the request.                                 */
/*                                                                  */
/*   cwbDB_RequestHandle *request - output                          */
/*           Pointer to a cwbDB_RequestHandle where the handle      */
/*           of the Request will be returned.                       */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_CreateSQLRequestHandle(
                             cwbDB_ConnectionHandle  connection,
                             cwbDB_RequestHandle    *request,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_DeleteCatalogRequestHandle                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Deallocates a request handle.                                  */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_DeleteCatalogRequestHandle(
                             cwbDB_RequestHandle  request,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_DeleteConnectionHandle                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Deallocates the handle to the AS/400 server.                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*       Handle to connection to AS/400 database access server.     */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_DeleteConnectionHandle(
                             cwbDB_ConnectionHandle  connection,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_DeleteDataFormatHandle                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Deallocates a format handle.                                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a data format object.                        */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_DeleteDataFormatHandle(
                             cwbDB_FormatHandle  format,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_DeleteDataHandle                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Deallocates a data handle.                                     */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_DataHandle dataHandle - input                            */
/*           Handle to a data object.                               */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_DeleteDataHandle(
                             cwbDB_DataHandle  dataHandle,
                             cwbSV_ErrHandle   errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_DeleteFile                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Delete a file from an AS/400.                                  */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for List or SQL requests.                */
/*                                                                  */
/*   The cwbDB_DeleteFile API should be called after setting the    */
/*   desired values in the request.                                 */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/*   A call to cwbDB_ReturnHostErrorInfo is needed in order         */
/*   determine the success of the operation for this API.  Calling  */
/*   cwbDB_ReturnHostErrorInfo prior to calling this API will       */
/*   result in a synchronous operation (the application will not    */
/*   get control back until the result is returned to the PC from   */
/*   the AS/400).                                                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_DeleteFile(
                             cwbDB_RequestHandle  request,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_DeleteNDBRequestHandle                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Deallocates a request handle.                                  */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_DeleteNDBRequestHandle(
                             cwbDB_RequestHandle  request,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_DeletePackage                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Delete a SQL package.                                          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/*   The cwbDB_DeletePackage API should be called after setting the */
/*   desired values in the request.                                 */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/*   A call to cwbDB_ReturnHostErrorInfo is needed in order         */
/*   determine the success of the operation for this API.  Calling  */
/*   cwbDB_ReturnHostErrorInfo prior to calling this API will       */
/*   result in a synchronous operation (the application will not    */
/*   get control back until the result is returned to the PC from   */
/*   the AS/400).                                                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_DeletePackage(
                             cwbDB_RequestHandle  request,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_DeleteParameterMarkerFormatHandle                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Deallocates a format handle.                                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a parameter marker format object.            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_DeleteParameterMarkerFormatHandle(
                             cwbDB_FormatHandle  format,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_DeleteSQLRequestHandle                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Deallocates a request handle.                                  */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_DeleteSQLRequestHandle(
                             cwbDB_RequestHandle  request,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_Describe                                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   Describes a prepared statement.  If there is no result set,    */
/*   no column descriptions will be returned.                       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/*   The cwbDB_Describe API should be called after setting the      */
/*   desired values in the request.                                 */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/*   A call to cwbDB_ReturnDataFormat is needed in order get the    */
/*   description of the data.  Calling cwbDB_ReturnDataFormat prior */
/*   to calling this API will result in a synchronous operation     */
/*   (the application will not get control back until the result is */
/*   returned to the PC from the AS/400).                           */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_Describe(
                             cwbDB_RequestHandle  request,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_DescribeParameterMarkers                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   Describes the parameter markers for a prepared statement.      */
/*   If the statement is an "UPDATE WHERE CURRENT OF CURSOR", the   */
/*   cursor must be open before the describe parameter markers can  */
/*   be performed.                                                  */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/*   The cwbDB_Describe API should be called after setting the      */
/*   desired values in the request.                                 */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/*   A call to cwbDB_ReturnParameterMarkerFormat is needed in order */
/*   get the description of the parameter markers.  Calling         */
/*   cwbDB_ReturnParameterMarkerFormat prior to calling this API    */
/*   will result in a synchronous operation (the application will   */
/*   not get control back until the result is returned to the PC    */
/*   from the AS/400).                                              */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_DescribeParameterMarkers(
                             cwbDB_RequestHandle  request,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_DynamicStreamFetch                                       */
/*                                                                  */
/* Purpose:                                                         */
/*   This API will prepare a select statement, open a cursor and    */
/*   fetch all resulting data. The row data will be returned to the */
/*   application in blocks, the size of which will be optimized for */
/*   the communication mechanism.  To get additional blocks, use    */
/*   the cwbDB_MoreStreamData API.                                  */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   const char *statementText - input                              */
/*           Pointer to an ASCIIZ string containing select text.    */
/*                                                                  */
/*   cwbDB_DataHandle data - input                                  */
/*           Handle to a data object into which the returned data   */
/*           will be placed.                                        */
/*                                                                  */
/*   cwbDB_DataHandle indicators - input                            */
/*           Handle to a data object into which the returned        */
/*           data indicators will be placed.  There is              */
/*           one indicator value for each column value              */
/*           of each row of data that is returned from the AS/400.  */
/*           The indicator will be a negative number if the value   */
/*           for the column is NULL.  If an error occurs while      */
/*           converting the data, a character 'E' will be placed    */
/*           in that column's indicator field.                      */
/*                                                                  */
/*   cwbDB_FormatHandle formatHandle - input                        */
/*           Handle to a data format that contains a description    */
/*           of the returned data.                                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWBDB_UNSUPPORTED_COLUMN_TYPE - An unsupported column type     */
/*                            was found in the data.  The result    */
/*                            set data is undefined.  Stream fetch  */
/*                            is left active, users must call       */
/*                            CWBDB_EndStreamFetch to close the     */
/*                            the active stream fetch request.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDB_DynamicStreamFetch(
                             cwbDB_RequestHandle  request,
                             const char          *statementText,
                             cwbDB_DataHandle     data,
                             cwbDB_DataHandle     indicators,
                             cwbDB_FormatHandle   formatHandle,
                             cwbSV_ErrHandle      errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDB_DynamicStreamFetchA(
                             cwbDB_RequestHandle  request,
                             LPCSTR               statementText,
                             cwbDB_DataHandle     data,
                             cwbDB_DataHandle     indicators,
                             cwbDB_FormatHandle   formatHandle,
                             cwbSV_ErrHandle      errorHandle   );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDB_DynamicStreamFetchW(
                             cwbDB_RequestHandle  request,
                             LPCWSTR              statementText,
                             cwbDB_DataHandle     data,
                             cwbDB_DataHandle     indicators,
                             cwbDB_FormatHandle   formatHandle,
                             cwbSV_ErrHandle      errorHandle  );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDB_DynamicStreamFetch        cwbDB_DynamicStreamFetchW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDB_DynamicStreamFetch        cwbDB_DynamicStreamFetchA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_EndStreamFetch                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Cancel the stream fetch operation before all the data has      */
/*   been returned.                                                 */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_EndStreamFetch(
                             cwbDB_RequestHandle  request,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_Execute                                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   Execute a prepared SQL statement.                              */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/*   The cwbDB_Execute API should be called after setting the       */
/*   desired values in the request.                                 */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_Execute(
                             cwbDB_RequestHandle  request,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_ExecuteImmediate                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Prepare and execute a SQL statement.                           */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/*   The cwbDB_ExecuteImmediate API should be called after setting  */
/*   the desired values in the request.                             */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_ExecuteImmediate(
                             cwbDB_RequestHandle  request,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_ExtendedDynamicStreamFetch                               */
/*                                                                  */
/* Purpose:                                                         */
/*   This API will perform a stream fetch (see previous API) for    */
/*   a statement that is already prepared in a SQL package.         */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   const char *libraryName - input                                */
/*           Pointer to an ASCIIZ string containing library name.   */
/*                                                                  */
/*   const char *packageName - input                                */
/*           Pointer to an ASCIIZ string containing package name.   */
/*                                                                  */
/*   const char *statementName - input                              */
/*           Pointer to an ASCIIZ string containing statement name. */
/*                                                                  */
/*   cwbDB_DataHandle data - input                                  */
/*           Handle to a data object into which the returned data   */
/*           will be placed.                                        */
/*                                                                  */
/*   cwbDB_DataHandle indicators - input                            */
/*           Handle to a data object into which the returned        */
/*           data indicators will be placed.  There is              */
/*           one indicator value for each column value              */
/*           of each row of data that is returned from the AS/400.  */
/*           The indicator will be a negative number if the value   */
/*           for the column is NULL.  If an error occurs while      */
/*           converting the data, a character 'E' will be placed    */
/*           in that column's indicator field.                      */
/*                                                                  */
/*   cwbDB_FormatHandle formatHandle - input                        */
/*           Handle to a data format that contains a description    */
/*           of the returned data.                                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWBDB_UNSUPPORTED_COLUMN_TYPE - An unsupported column type     */
/*                            was found in the data.  The result    */
/*                            set data is undefined.                */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDB_ExtendedDynamicStreamFetch(
                             cwbDB_RequestHandle  request,
                             const char          *libraryName,
                             const char          *packageName,
                             const char          *statementName,
                             cwbDB_DataHandle     data,
                             cwbDB_DataHandle     indicators,
                             cwbDB_FormatHandle   formatHandle,
                             cwbSV_ErrHandle      errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDB_ExtendedDynamicStreamFetchA(
                                    cwbDB_RequestHandle  request,
                                    LPCSTR               libraryName,
                                    LPCSTR               packageName,
                                    LPCSTR               statementName,
                                    cwbDB_DataHandle     data,
                                    cwbDB_DataHandle     indicators,
                                    cwbDB_FormatHandle   formatHandle,
                                    cwbSV_ErrHandle      errorHandle );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDB_ExtendedDynamicStreamFetchW(
                                    cwbDB_RequestHandle  request,
                                    LPCWSTR              libraryName,
                                    LPCWSTR              packageName,
                                    LPCWSTR              statementName,
                                    cwbDB_DataHandle     data,
                                    cwbDB_DataHandle     indicators,
                                    cwbDB_FormatHandle   formatHandle,
                                    cwbSV_ErrHandle      errorHandle );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDB_ExtendedDynamicStreamFetch   cwbDB_ExtendedDynamicStreamFetchW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDB_ExtendedDynamicStreamFetch   cwbDB_ExtendedDynamicStreamFetchA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_Fetch                                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   Fetch a row or block of rows (this is controlled by the        */
/*   cwbDB_SetBlockCount API) from an open cursor.                  */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWBDB_UNSUPPORTED_COLUMN_TYPE - An unsupported column type     */
/*                            was found in the data.  The result    */
/*                            set data is undefined.                */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/*   The cwbDB_Fetch API should be called after setting the desired */
/*   values in the request.                                         */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.  Please note that fetched data     */
/*   data will not be returned unless the data is requested         */
/*   (using the cwbDB_ReturnData API).                              */
/*                                                                  */
/*   A call to the cwbDB_ReturnData API is needed prior to calling  */
/*   this API if the application is to process the data             */
/*   immediately.  If the application is to operate asynchronously, */
/*   then the call to cwbDB_ReturnData and subsequently             */
/*   cwbDB_GetData are needed after this API in order to get the    */
/*   data that result from this API call.  Once the data is         */
/*   returned, information in the data format handle is used to     */
/*   determine how to parse the data.                               */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_Fetch(
                             cwbDB_RequestHandle  request,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetBaseColumnName                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the base column name (if it exists) for a column of    */
/*   data.                                                          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a data format object.                        */
/*                                                                  */
/*   unsigned long columnPosition - input                           */
/*           Specifies the relative position of the column.         */
/*                                                                  */
/*   cwbDB_DataHandle columnHandle - input                          */
/*           Handle to a data object which will contain the         */
/*           base column name.                                      */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetBaseColumnName(
                             cwbDB_FormatHandle format,
                             unsigned long      columnPosition,
                             cwbDB_DataHandle   columnHandle,
                             cwbSV_ErrHandle    errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetBaseSchemaName                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the base schema name (if it exists) for a column of    */
/*   data.                                                          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a data format object.                        */
/*                                                                  */
/*   unsigned long columnPosition - input                           */
/*           Specifies the relative position of the column.         */
/*                                                                  */
/*   cwbDB_DataHandle schemaHandle - input                          */
/*           Handle to a data object which will contain the         */
/*           extended schema name.                                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetBaseSchemaName(
                             cwbDB_FormatHandle format,
                             unsigned long      columnPosition,
                             cwbDB_DataHandle   schemaHandle,
                             cwbSV_ErrHandle    errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetBaseTableName                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the base table name (if it exists) for a column of     */
/*   data.                                                          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a data format object.                        */
/*                                                                  */
/*   unsigned long columnPosition - input                           */
/*           Specifies the relative position of the column.         */
/*                                                                  */
/*   cwbDB_DataHandle tableHandle - input                           */
/*           Handle to a data object which will contain the         */
/*           base table name.                                       */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetBaseTableName(
                             cwbDB_FormatHandle format,
                             unsigned long      columnPosition,
                             cwbDB_DataHandle   tableHandle,
                             cwbSV_ErrHandle    errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetColumnCCSID                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the Coded Character Set Identifier (CCSID) for a       */
/*   specified column of data.                                      */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a data format object.                        */
/*                                                                  */
/*   unsigned long location - input                                 */
/*           Indicates whether the system or local information is   */
/*           to be returned.                                        */
/*                                                                  */
/*   unsigned long columnPosition - input                           */
/*           Specifies the relative position of the column.         */
/*                                                                  */
/*   unsigned short *dataCCSID - output                             */
/*           Pointer to a short integer to contain the CCSID        */
/*           for the specified column.                              */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   For the location parameter, use one of the defined values:     */
/*                    CWBDB_SYSTEM                                  */
/*                    CWBDB_LOCAL                                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetColumnCCSID(
                             cwbDB_FormatHandle  format,
                             unsigned long       location,
                             unsigned long       columnPosition,
                             unsigned short     *dataCCSID,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetColumnCount                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the number of columns of data that are described by    */
/*   the data format.                                               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a data format object.                        */
/*                                                                  */
/*   unsigned long *columnCount - output                            */
/*           Pointer to an unsined long integer which will          */
/*           contain the column count.                              */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetColumnCount(
                             cwbDB_FormatHandle  format,
                             unsigned long      *columnCount,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetColumnLength                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the length (in bytes) of the data for a specified      */
/*   column.                                                        */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a data format object.                        */
/*                                                                  */
/*   unsigned long location - input                                 */
/*           Indicates whether the system or local information is   */
/*           to be returned.                                        */
/*                                                                  */
/*   unsigned long columnPosition - input                           */
/*           Specifies the relative position of the column.         */
/*                                                                  */
/*   unsigned long *dataLength - output                             */
/*           Pointer to short integer to contain the data length.   */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   For the location parameter, use one of the defined values:     */
/*                    CWBDB_SYSTEM                                  */
/*                    CWBDB_LOCAL                                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetColumnLength(
                             cwbDB_FormatHandle  format,
                             unsigned long       location,
                             unsigned long       columnPosition,
                             unsigned long      *dataLength,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetColumnName                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the column name (if it exists) for a column of data.   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a data format object.                        */
/*                                                                  */
/*   unsigned long columnPosition - input                           */
/*           Specifies the relative position of the column.         */
/*                                                                  */
/*   cwbDB_DataHandle columnHandle - input                          */
/*          handle to a data object which will contain the          */
/*          column name                                             */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetColumnName(
                             cwbDB_FormatHandle  format,
                             unsigned long       columnPosition,
                             cwbDB_DataHandle    columnHandle,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetColumnPrecision                                       */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the precision for a specified column of data.          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a data format object.                        */
/*                                                                  */
/*   unsigned long location - input                                 */
/*           Indicates whether the system or local information is   */
/*           to be returned.                                        */
/*                                                                  */
/*   unsigned long columnPosition - input                           */
/*           Specifies the relative position of the column.         */
/*                                                                  */
/*   unsigned short *dataPrecision - output                         */
/*           Pointer to short integer to contain the data           */
/*           precision.                                             */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   For the location parameter, use one of the defined values:     */
/*                    CWBDB_SYSTEM                                  */
/*                    CWBDB_LOCAL                                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetColumnPrecision(
                             cwbDB_FormatHandle  format,
                             unsigned long       location,
                             unsigned long       columnPosition,
                             unsigned short     *dataPrecision,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetColumnScale                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the scale for a specified column of data.              */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a data format object.                        */
/*                                                                  */
/*   unsigned long location - input                                 */
/*           Indicates whether the system or local information is   */
/*           to be returned.                                        */
/*                                                                  */
/*   unsigned long columnPosition - input                           */
/*           Specifies the relative position of the column.         */
/*                                                                  */
/*   unsigned short *dataScale - output                             */
/*           Pointer to short integer to contain the data scale.    */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   For the location parameter, use one of the defined values:     */
/*                    CWBDB_SYSTEM                                  */
/*                    CWBDB_LOCAL                                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetColumnScale(
                             cwbDB_FormatHandle  format,
                             unsigned long       location,
                             unsigned long       columnPosition,
                             unsigned short     *dataScale,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetColumnType                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the data type for a specified column of data.          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a data format object.                        */
/*                                                                  */
/*   unsigned long location - input                                 */
/*           Indicates whether the system or local information is   */
/*           to be returned.                                        */
/*                                                                  */
/*   unsigned long columnPosition - input                           */
/*           Specifies the relative position of the column.         */
/*                                                                  */
/*   signed short *dataType - output                                */
/*           Short integer which will contain the data type.        */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   For the location parameter, use one of the defined values:     */
/*                    CWBDB_SYSTEM                                  */
/*                    CWBDB_LOCAL                                   */
/*                                                                  */
/*   If the system information is requested, the type returned is   */
/*   the SQL type.  If the local information is requested, see      */
/*   the defined values:                                            */
/*                    CWBDB_PCNOCONVERSION                          */
/*                    CWBDB_PCSTRING                                */
/*                    CWBDB_PCLONG                                  */
/*                    CWBDB_PCSHORT                                 */
/*                    CWBDB_PCFLOAT                                 */
/*                    CWBDB_PCDOUBLE                                */
/*                    CWBDB_PCPACKED                                */
/*                    CWBDB_PCZONED                                 */
/*                    CWBDB_PCINVALIDTYPE                           */
/*                    CWBDB_PCVARSTRING                             */
/*                    CWBDB_PCGRAPHIC                               */
/*                    CWBDB_PCVARGRAPHIC                            */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetColumnType(
                             cwbDB_FormatHandle  format,
                             unsigned long       location,
                             unsigned long       columnPosition,
                             signed short       *dataType,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetCommitmentControl                                     */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the current commitment control level.                      */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*       Handle to connection to AS/400 database access server      */
/*                                                                  */
/*   unsigned short *commitmentLevel - output                       */
/*       Pointer to an unsigned short where the current value       */
/*       will be returned.                                          */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The cwbDB_StartServer API must be called before this API can   */
/*   return valid data.  The value that is returned will be one of  */
/*   the following:                                                 */
/*                    CWBDB_NONE                                    */
/*                    CWBDB_CURSOR_STABILITY                        */
/*                    CWBDB_CHANGE                                  */
/*                    CWBDB_ALL                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetCommitmentControl(
                             cwbDB_ConnectionHandle  connection,
                             unsigned short         *commitmentLevel,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetConversionIndicator                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Gets the indicator that says whether data is to be converted   */
/*   between the client and host format.                            */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a data format object.                        */
/*                                                                  */
/*   cwb_Boolean *conversionIndicator - output                      */
/*        CWB_FALSE indicates no conversion                         */
/*        CWB_TRUE indicates conversion                             */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetConversionIndicator(
                             cwbDB_FormatHandle  format,
                             cwb_Boolean        *conversionIndicator,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetData                                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the requested data from the host.  This data can include   */
/*   the selected data, data format, host return code, and SQLCA.   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The cwbDB_GetData API should be called after requesting the    */
/*   desired data (using the cwbDB_Return* APIs).                   */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetData(
                             cwbDB_RequestHandle  request,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetDataLength                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the length of the data contained in a data object.     */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_DataHandle dataHandle - input                            */
/*           Handle to a data object.                               */
/*                                                                  */
/*   unsigned long *dataLength - output                             */
/*           Unsigned long integer to contain the length of the     */
/*           data.                                                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetDataLength(
                             cwbDB_DataHandle  dataHandle,
                             unsigned long    *dataLength,
                             cwbSV_ErrHandle   errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetDataPointer                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the address of the data in a data object.              */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_DataHandle dataHandle - input                            */
/*           Handle to a data object.                               */
/*                                                                  */
/*   char **data - output                                           */
/*           Pointer to pointer to the data buffer.                 */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetDataPointer(
                             cwbDB_DataHandle   dataHandle,
                             char             **data,
                             cwbSV_ErrHandle    errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetDateFormat                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the current date format. See cwbDB_SetDateFormat for       */
/*   additional information about date formats.                     */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*       Handle to connection to AS/400 database access server.     */
/*                                                                  */
/*   unsigned short *dateFormat - output                            */
/*       Pointer to an unsigned short where the current date format */
/*       value will be returned.                                    */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*   CWBDB_INVALID_ARG_API - Value specified is not in range.       */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The cwbDB_StartServer API must be called before this API can   */
/*   return valid data.  The value that is returned will be one of  */
/*   the following:                                                 */
/*        Format name          Date format constant       Value     */
/*        ---------------      --------------------       ------    */
/*        Julian               CWBDB_DATE_FMT_JUL           0       */
/*        month day year       CWBDB_DATE_FMT_MDY           1       */
/*        day month year       CWBDB_DATE_FMT_DMY           2       */
/*        year month day       CWBDB_DATE_FMT_YMD           3       */
/*        USA                  CWBDB_DATE_FMT_USA           4       */
/*        ISO                  CWBDB_DATE_FMT_ISO           5       */
/*        IBM Japan            CWBDB_DATE_FMT_JIS           6       */
/*        IBM Europe           CWBDB_DATE_FMT_EUR           7       */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbDB_GetDateFormat(
                             cwbDB_ConnectionHandle  connection,
                             unsigned short          *dateFormat,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetDateSeparator                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the current date separator. See cwbDB_SetDateSeparator for */
/*   additional information about date separators.                  */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*       Handle to connection to AS/400 database access server      */
/*                                                                  */
/*   unsigned short *dateSeparator - output                         */
/*       Pointer to an unsigned short where the current date data   */
/*       separator value will be returned.                          */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The cwbDB_StartServer API must be called before this API can   */
/*   return valid data.  The value that is returned will be one of  */
/*   the following:                                                 */
/*                                                                  */
/*        Date separator       Date separator constant              */
/*        ---------------      -----------------------              */
/*        Slash                CWBDB_DATE_SEP_SLASH                 */
/*        Dash                 CWBDB_DATE_SEP_DASH                  */
/*        Period               CWBDB_DATE_SEP_PERIOD                */
/*        Comma                CWBDB_DATE_SEP_COMMA                 */
/*        Blank                CWBDB_DATE_SEP_BLANK                 */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbDB_GetDateSeparator(
                             cwbDB_ConnectionHandle  connection,
                             unsigned short          *dateSeparator,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetDecimalSeparator                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the current decimal separator. See                         */
/*   cwbDB_SetDecimalSeparator for additional information about     */
/*   decimal separators.                                            */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*       Handle to connection to AS/400 database access server      */
/*                                                                  */
/*   unsigned short *decimalSeparator - output                      */
/*       Pointer to an unsigned short where the current decimal     */
/*       separator value will be returned.                          */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The cwbDB_StartServer API must be called before this API can   */
/*   return valid data.  The value that is returned will be one of  */
/*   the following:                                                 */
/*                                                                  */
/*        Time separator       Time separator constant              */
/*        ---------------      -----------------------              */
/*        Period               CWBDB_DECIMAL_SEP_PERIOD             */
/*        Comma                CWBDB_DECIMAL_SEP_COMMA              */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbDB_GetDecimalSeparator(
                             cwbDB_ConnectionHandle  connection,
                             unsigned short          *decimalSeparator,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetExtendedColumnInfo                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the fixed-length portion of the extended column        */
/*   information.                                                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a data format object.                        */
/*                                                                  */
/*   unsigned long columnPosition - input                           */
/*           Specifies the relative position of the column.         */
/*                                                                  */
/*   unsigned long *columnInfo - output                             */
/*           Pointer to 4-byte integer to contain the extended      */
/*           column information.                                    */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetExtendedColumnInfo(
                             cwbDB_FormatHandle format,
                             unsigned long      columnPosition,
                             unsigned long      *columnInfo,
                             cwbSV_ErrHandle    errorHandle);


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetIgnoreDecimalDataError                                */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the current setting for the decimal data error indicator.  */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*       Handle to connection to AS/400 database access server      */
/*                                                                  */
/*   unsigned short  *ignoreDecimalError - output                   */
/*       Pointer to an unsigned short where the current value       */
/*       will be returned.                                          */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The cwbDB_StartServer API must be called before this API can   */
/*   return valid data.  The value returned will be one of the      */
/*   following:                                                     */
/*                    CWBDB_IGNORE_ERROR                            */
/*                    CWBDB_CORRECT_ERROR                           */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetIgnoreDecimalDataError(
                             cwbDB_ConnectionHandle  connection,
                             unsigned short         *ignoreDecimalError,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetLabelName                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the label name (if it exists) for a column of data.    */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to an extended format object.                   */
/*                                                                  */
/*   unsigned long columnPosition - input                           */
/*           Specifies the relative position of the column.         */
/*                                                                  */
/*   cwbDB_DataHandle labelHandle - input                           */
/*           Handle to a data object which will contain the         */
/*           label name.                                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetLabelName(
                             cwbDB_FormatHandle format,
                             unsigned long      columnPosition,
                             cwbDB_DataHandle   labelHandle,
                             cwbSV_ErrHandle    errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetLOBLocator                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the LOB Locator for a specified parameter              */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a data format object.                        */
/*                                                                  */
/*   unsigned long parameterPosition - input                        */
/*           Specifies the relative position of the parameter.      */
/*                                                                  */
/*   unsigned long *dataLocator - output                            */
/*           Pointer to a long integer to contain the locator       */
/*           for the specified parameter.                           */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetLOBLocator(
                             cwbDB_FormatHandle  format,
                             unsigned long       parameterPosition,
                             unsigned long      *dataLocator,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetLOBMaxSize                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the LOB Maximum size for a specified parameter         */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a data format object.                        */
/*                                                                  */
/*   unsigned long columnPosition - input                           */
/*           Specifies the relative position of the column          */
/*                                                                  */
/*   unsigned long *maxSize  - output                               */
/*           Pointer to a long integer to contain the LOB           */
/*           maximum size for the specified parameter.              */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/*                                                                  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetLOBMaxSize(
                             cwbDB_FormatHandle  format,
                             unsigned long       columnPosition,
                             unsigned long      *maxSize,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetNamingConvention                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the naming convention (SQL or native AS/400) that is in    */
/*   effect for the specified connection.                           */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*       Handle to connection to AS/400 database access server.     */
/*                                                                  */
/*   unsigned short *namingConvention - output                      */
/*       Pointer to an unsigned short where the current naming      */
/*       convention will be returned.                               */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The cwbDB_StartServer API must be called before this API can   */
/*   return valid data.  The value that is returned will be one of  */
/*   the following:                                                 */
/*                    CWBDB_PERIOD_NAME_CONV                        */
/*                    CWBDB_SLASH_NAME_CONV                         */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetNamingConvention(
                             cwbDB_ConnectionHandle  connection,
                             unsigned short         *namingConvention,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetParameterCCSID                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the Coded Character Set Identifier (CCSID) for a       */
/*   specified parameter.                                           */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a data format object.                        */
/*                                                                  */
/*   unsigned long location - input                                 */
/*           Indicates whether the system or local information is   */
/*           to be returned.                                        */
/*                                                                  */
/*   unsigned long parameterPosition - input                        */
/*           Specifies the relative position of the parameter.      */
/*                                                                  */
/*   unsigned short *dataCCSID - output                             */
/*           Pointer to a short integer to contain the CCSID        */
/*           for the specified parameter.                           */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   For the location parameter, use one of the defined values:     */
/*                    CWBDB_SYSTEM                                  */
/*                    CWBDB_LOCAL                                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetParameterCCSID(
                             cwbDB_FormatHandle  format,
                             unsigned long       location,
                             unsigned long       parameterPosition,
                             unsigned short     *dataCCSID,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetParameterCount                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the number of parameters that are described by the     */
/*   data format.                                                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a data format object.                        */
/*                                                                  */
/*   unsigned long *parameterCount - output                         */
/*           Pointer to an unsined long integer which will          */
/*           contain the parameter count.                           */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetParameterCount(
                             cwbDB_FormatHandle  format,
                             unsigned long      *parameterCount,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetParameterDirection                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the parameter direction.                               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a parameter marker format object.            */
/*                                                                  */
/*   unsigned long parameterPosition - input                        */
/*           Specifies the relative position of the parameter.      */
/*                                                                  */
/*   unsigned short*     columnDirection                            */
/*          Receives the column direction, which will be one of     */
/*					he following:                                           */
/*              CWBDB_PM_INPUT_ONLY                                 */
/*              CWBDB_PM_INPUT_OUTPUT                               */
/*              CWBDB_PM_OUTPUT_ONLY                                */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetParameterDirection(
                             cwbDB_FormatHandle  format,
                             unsigned long       parameterPosition,
                             unsigned short*     columnDirection,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetParameterLength                                       */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the length (in bytes) of the data for a specified      */
/*   parameter.                                                     */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a data format object.                        */
/*                                                                  */
/*   unsigned long location - input                                 */
/*           Indicates whether the system or local information is   */
/*           to be returned.                                        */
/*                                                                  */
/*   unsigned long parameterPosition - input                        */
/*           Specifies the relative position of the parameter.      */
/*                                                                  */
/*   unsigned long *dataLength - output                             */
/*           Pointer to short integer to contain the data length.   */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   For the location parameter, use one of the defined values:     */
/*                    CWBDB_SYSTEM                                  */
/*                    CWBDB_LOCAL                                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetParameterLength(
                             cwbDB_FormatHandle  format,
                             unsigned long       location,
                             unsigned long       parameterPosition,
                             unsigned long      *dataLength,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetParameterName                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the parameter name (if it exists) for a column of data */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a data format object.                        */
/*                                                                  */
/*   unsigned long parameterPosition - input                        */
/*           Specifies the relative position of the parameter       */
/*                                                                  */
/*   cwbDB_DataHandle parameterHandle - input                       */
/*          Handle to a data object which will contain the          */
/*          parameter name                                          */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetParameterName(
                             cwbDB_FormatHandle  format,
                             unsigned long       parameterPosition,
                             cwbDB_DataHandle    parameterHandle,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetParameterPrecision                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the precision for a specified parameter.               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a data format object.                        */
/*                                                                  */
/*   unsigned long location - input                                 */
/*           Indicates whether the system or local information is   */
/*           to be returned.                                        */
/*                                                                  */
/*   unsigned long parameterPosition - input                        */
/*           Specifies the relative position of the parameter.      */
/*                                                                  */
/*   unsigned short *dataPrecision - output                         */
/*           Pointer to short integer to contain the data           */
/*           precision.                                             */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   For the location parameter, use one of the defined values:     */
/*                    CWBDB_SYSTEM                                  */
/*                    CWBDB_LOCAL                                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetParameterPrecision(
                             cwbDB_FormatHandle  format,
                             unsigned long       location,
                             unsigned long       parameterPosition,
                             unsigned short     *dataPrecision,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetParameterScale                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the scale for a specified parameter.                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a data format object.                        */
/*                                                                  */
/*   unsigned long location - input                                 */
/*           Indicates whether the system or local information is   */
/*           to be returned.                                        */
/*                                                                  */
/*   unsigned long parameterPosition - input                        */
/*           Specifies the relative position of the parameter.      */
/*                                                                  */
/*   unsigned short *dataScale - output                             */
/*           Pointer to short integer to contain the data scale.    */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   For the location parameter, use one of the defined values:     */
/*                    CWBDB_SYSTEM                                  */
/*                    CWBDB_LOCAL                                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetParameterScale(
                             cwbDB_FormatHandle  format,
                             unsigned long       location,
                             unsigned long       parameterPosition,
                             unsigned short     *dataScale,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetParameterType                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the data type for a specified parameter.               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a data format object.                        */
/*                                                                  */
/*   unsigned long location - input                                 */
/*           Indicates whether the system or local information is   */
/*           to be returned.                                        */
/*                                                                  */
/*   unsigned long parameterPosition - input                        */
/*           Specifies the relative position of the parameter.      */
/*                                                                  */
/*   signed short *dataType - output                                */
/*           Short integer which will contain the data type.        */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   For the location parameter, use one of the defined values:     */
/*                    CWBDB_SYSTEM                                  */
/*                    CWBDB_LOCAL                                   */
/*                                                                  */
/*   If the system information is requested, the type returned is   */
/*   the SQL type.  If the local information is requested, see      */
/*   the defined values:                                            */
/*                    CWBDB_PCNOCONVERSION                          */
/*                    CWBDB_PCSTRING                                */
/*                    CWBDB_PCLONG                                  */
/*                    CWBDB_PCSHORT                                 */
/*                    CWBDB_PCFLOAT                                 */
/*                    CWBDB_PCDOUBLE                                */
/*                    CWBDB_PCPACKED                                */
/*                    CWBDB_PCZONED                                 */
/*                    CWBDB_PCINVALIDTYPE                           */
/*                    CWBDB_PCVARSTRING                             */
/*                    CWBDB_PCGRAPHIC                               */
/*                    CWBDB_PCVARGRAPHIC                            */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetParameterType(
                             cwbDB_FormatHandle  format,
                             unsigned long       location,
                             unsigned long       parameterPosition,
                             signed short       *dataType,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetRelationalDBName                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the initial relational database name (usually system).     */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*       Handle to connection to AS/400 database access server      */
/*                                                                  */
/*   char * relationalDBName - output                               */
/*       Pointer to buffer 18 characters long to receive the        */
/*       database name (Not null terminated).                       */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The cwbDB_StartServer API must be called before this API can   */
/*   return valid data.                                             */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetRelationalDBName(
                             cwbDB_ConnectionHandle  connection,
                             char                   *relationalDBName,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetRowSize                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the size (in bytes) of the data described by the       */
/*   data format.                                                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a data format object.                        */
/*                                                                  */
/*   unsigned long location - input                                 */
/*           Indicates whether the system or local information is   */
/*           to be returned.                                        */
/*                                                                  */
/*   unsigned long *rowSize - output                                */
/*           Pointer to an unsigned long integer which will         */
/*           contain the row size.                                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   For the location parameter, use one of the defined values:     */
/*                    CWBDB_SYSTEM                                  */
/*                    CWBDB_LOCAL                                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetRowSize(
                             cwbDB_FormatHandle  format,
                             unsigned long       location,
                             unsigned long      *rowSize,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetServerFunctionalLevel                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the current server functional level.                       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*       Handle to connection to AS/400 database access server      */
/*                                                                  */
/*   char * serverFunctionalLevel - output                          */
/*       Pointer to buffer 11 characters long to receive the        */
/*       server's functional level                                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The cwbDB_StartServer API must be called before this API can   */
/*   return valid data.                                             */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetServerFunctionalLevel(
                             cwbDB_ConnectionHandle  connection,
                             char                   *serverFunctionalLevel,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetSizeOfInputParameters                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the size (in bytes) of the input data described by     */
/*   parameter marker format.                                       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a parameter marker format object.            */
/*                                                                  */
/*   unsigned long location - input                                 */
/*           Indicates whether the system or local information is   */
/*           to be returned.                                        */
/*                                                                  */
/*   unsigned long *inputSize - output                              */
/*           Pointer to an unsigned long integer which will         */
/*           contain the row size.                                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   For the location parameter, use one of the defined values:     */
/*                    CWBDB_SYSTEM                                  */
/*                    CWBDB_LOCAL                                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetSizeOfInputParameters(
                             cwbDB_FormatHandle  format,
                             unsigned long       location,
                             unsigned long      *inputSize,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetSizeOfOutputParameters                                */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the size (in bytes) of the output data described by    */
/*   parameter marker format.                                       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a parameter marker format object.            */
/*                                                                  */
/*   unsigned long location - input                                 */
/*           Indicates whether the system or local information is   */
/*           to be returned.                                        */
/*                                                                  */
/*   unsigned long *outputSize - output                             */
/*           Pointer to an unsigned long integer which will         */
/*           contain the row size.                                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   For the location parameter, use one of the defined values:     */
/*                    CWBDB_SYSTEM                                  */
/*                    CWBDB_LOCAL                                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetSizeOfOutputParameters(
                             cwbDB_FormatHandle  format,
                             unsigned long       location,
                             unsigned long      *inputSize,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetSizeOfParameters                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the size (in bytes) of the all data described by       */
/*   parameter marker format.                                       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a parameter marker format object.            */
/*                                                                  */
/*   unsigned long *bufferSize - output                             */
/*           Pointer to an unsigned long integer which will         */
/*           contain the parameter buffer size.                     */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_GetSizeOfParameters(
                             cwbDB_FormatHandle  format,
                             unsigned long      *bufferSize,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetTimeFormat                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the current time format. See cwbDB_SetTimeFormat for       */
/*   additional information about time formats.                     */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*       Handle to connection to AS/400 database access server      */
/*                                                                  */
/*   unsigned short *timeFormat - output                            */
/*       Pointer to an unsigned short where the current time format */
/*       value will be returned.                                    */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The cwbDB_StartServer API must be called before this API can   */
/*   return valid data.  The value that is returned will be one of  */
/*   the following:                                                 */
/*    Format name              Time format constant                 */
/*    ---------------          -----------------------              */
/*    Hours minutes seconds    CWBDB_TIME_FMT_HMS                   */
/*    USA                      CWBDB_TIME_FMT_USA                   */
/*    ISO                      CWBDB_TIME_FMT_ISO                   */
/*    IBM Europe               CWBDB_TIME_FMT_EUR                   */
/*    IBM Japan                CWBDB_TIME_FMT_JIS                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbDB_GetTimeFormat(
                             cwbDB_ConnectionHandle  connection,
                             unsigned short          *timeFormat,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_GetTimeSeparator                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the current time separator. See cwbDB_SetTimeSeparator for */
/*   additional information about time separators.                  */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*       Handle to connection to AS/400 database access server      */
/*                                                                  */
/*   unsigned short *timeSeparator - output                         */
/*       Pointer to an unsigned short where the current time        */
/*       separator value will be returned.                          */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The cwbDB_StartServer API must be called before this API can   */
/*   return valid data.  The value that is returned will be one of  */
/*   the following:                                                 */
/*                                                                  */
/*        Time separator       Time separator constant              */
/*        ---------------      -----------------------              */
/*        Colon                CWBDB_TIME_SEP_COLON                 */
/*        Period               CWBDB_TIME_SEP_PERIOD                */
/*        Comma                CWBDB_TIME_SEP_COMMA                 */
/*        Blank                CWBDB_TIME_SEP_BLANK                 */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbDB_GetTimeSeparator(
                             cwbDB_ConnectionHandle  connection,
                             unsigned short          *timeSeparator,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_IsParameterInput                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns a boolean value indicating whether the parameter is    */
/*   input only.                                                    */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a parameter marker format object.            */
/*                                                                  */
/*   unsigned long parameterPosition - input                        */
/*           Specifies the relative position of the parameter.      */
/*                                                                  */
/*   cwb_Boolean *parameterIsInput - output                         */
/*           Pointer to an boolean indicating if the parameter is   */
/*           input only.                                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_IsParameterInput(
                             cwbDB_FormatHandle  format,
                             unsigned long       parameterPosition,
                             cwb_Boolean        *parameterIsInput,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_IsParameterInputOutput                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns a boolean value indicating whether the parameter is    */
/*   input and output.                                              */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a parameter marker format object.            */
/*                                                                  */
/*   unsigned long parameterPosition - input                        */
/*           Specifies the relative position of the parameter.      */
/*                                                                  */
/*   cwb_Boolean *parameterIsInputOutput - output                   */
/*           Pointer to an boolean indicating if the parameter is   */
/*           input and output.                                      */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_IsParameterInputOutput(
                             cwbDB_FormatHandle  format,
                             unsigned long       parameterPosition,
                             cwb_Boolean        *parameterIsInputOutput,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_MoreStreamData                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   This API will get the next block of stream fetch data.         */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*                                                                  */
/*   cwbDB_DataHandle data - input                                  */
/*           Handle to a data object into which the returned data   */
/*           will be placed.                                        */
/*                                                                  */
/*   cwbDB_DataHandle indicators - input                            */
/*           Handle to a data object into which the returned        */
/*           data indicators will be placed.  There is              */
/*           one indicator value for each column value              */
/*           of each row of data that is returned from the AS/400.  */
/*           The indicator will be a negative number if the value   */
/*           for the column is NULL.  If an error occurs while      */
/*           converting the data, a character 'E' will be placed    */
/*           in that column's indicator field.                      */
/*                                                                  */
/*   cwbDB_FormatHandle formatHandle - input                        */
/*           Handle to a data format that contains a description    */
/*           of the returned data.                                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_MoreStreamData(
                             cwbDB_RequestHandle  request,
                             cwbDB_DataHandle     data,
                             cwbDB_DataHandle     indicators,
                             cwbDB_FormatHandle   formatHandle,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_Open                                                     */
/*                                                                  */
/* Purpose:                                                         */
/*   Open a cursor.                                                 */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned char openOptions - input                              */
/*           Input value for open options indicator.                */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   For the openOptions, use the defined values:                   */
/*                    CWBDB_READ                                    */
/*                    CWBDB_WRITE                                   */
/*                    CWBDB_UPDATE                                  */
/*                    CWBDB_DELETE                                  */
/*                    CWBDB_OPEN_ALL - Provided for convenience     */
/*                                                                  */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/*   The cwbDB_Open API should be called after setting the desired  */
/*   values in the request.                                         */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_Open(
                             cwbDB_RequestHandle  request,
                             unsigned char        openOptions,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_OpenDescribeFetch                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   This API combines the open, describe and fetch operations.     */
/*   This combined function is valuable when the statement is       */
/*   already prepared (extended dynamic SQL).                       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned char openOptions - input                              */
/*           Input value for open options indicator.                */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   For the openOptions, use the defined values:                   */
/*                    CWBDB_READ                                    */
/*                    CWBDB_WRITE                                   */
/*                    CWBDB_UPDATE                                  */
/*                    CWBDB_DELETE                                  */
/*                    CWBDB_OPEN_ALL - Provided for convenience     */
/*                                                                  */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/*   The cwbDB_OpenDescribeFetch API should be called after setting */
/*   the desired values in the request.                             */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.  Please note that fetched data     */
/*   data will not be returned unless the data is requested         */
/*   (using the cwbDB_ReturnData API).                              */
/*                                                                  */
/*   A call to the cwbDB_ReturnData API is needed prior to calling  */
/*   this API if the application is to process the data             */
/*   immediately.  If the application is to operate asynchronously, */
/*   then the call to cwbDB_ReturnData and subsequently             */
/*   cwbDB_GetData are needed after this API in order to get the    */
/*   data that result from this API call.  Once the data is         */
/*   returned, information in the data format handle is used to     */
/*   determine how to parse the data.                               */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_OpenDescribeFetch(
                             cwbDB_RequestHandle  request,
                             unsigned char        openOptions,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_OverrideFile                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Override database file reference to another file/member.       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for List or SQL requests.                */
/*                                                                  */
/*   The cwbDB_OverRideFile API should be called after setting      */
/*   the desired values in the request.                             */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_OverrideFile(
                             cwbDB_RequestHandle  request,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_Prepare                                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   Prepares an SQL statement.  If a SQL package has been set,     */
/*   this API will prepare a statement into the package.            */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/*   The cwbDB_Prepare API should be called after setting the       */
/*   desired values in the request.                                 */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_Prepare(
                             cwbDB_RequestHandle  request,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_PrepareDescribe                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   This API combines the prepare and describe operations.  The    */
/*   advantage of using this API is that the SQL component is       */
/*   called only once.                                              */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/*   The cwbDB_PrepareDescribe API should be called after setting   */
/*   the desired values in the request.                             */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/*   A call to cwbDB_ReturnDataFormat is needed in order get the    */
/*   description of the data.  Calling cwbDB_ReturnDataFormat prior */
/*   to calling this API will result in a synchronous operation     */
/*   (the application will not get control back until the result is */
/*   returned to the PC from the AS/400).                           */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_PrepareDescribe(
                             cwbDB_RequestHandle  request,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_PrepareDescribeOpenFetch                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   This API combines the prepare, describe, open, and fetch       */
/*   operations. By combining these operations, performance will    */
/*   improve because only one call is made to the SQL component     */
/*   on the host.                                                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned char openOptions - input                              */
/*           Input value for open options indicator.                */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   For the openOptions, use the defined values:                   */
/*                    CWBDB_READ                                    */
/*                    CWBDB_WRITE                                   */
/*                    CWBDB_UPDATE                                  */
/*                    CWBDB_DELETE                                  */
/*                    CWBDB_OPEN_ALL - Provided for convenience     */
/*                                                                  */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/*   The cwbDB_PrepareDescribeOpenFetch API should be called after  */
/*   setting the desired values in the request.                     */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.  Please note that fetched data     */
/*   data will not be returned unless the data is requested         */
/*   (using the cwbDB_ReturnData API).                              */
/*                                                                  */
/*   A call to the cwbDB_ReturnData API is needed prior to calling  */
/*   this API if the application is to process the data             */
/*   immediately.  If the application is to operate asynchronously, */
/*   then the call to cwbDB_ReturnData and subsequently             */
/*   cwbDB_GetData are needed after this API in order to get the    */
/*   data that result from this API call.  Once the data is         */
/*   returned, information in the data format handle is used to     */
/*   determine how to parse the data.                               */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_PrepareDescribeOpenFetch(
                             cwbDB_RequestHandle  request,
                             unsigned char        openOptions,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_RemoveMember                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Remove a member from an AS/400 file.                           */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for List or SQL requests.                */
/*                                                                  */
/*   The cwbDB_RemoveMember API should be called after setting      */
/*   the desired values in the request.                             */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/*   A call to cwbDB_ReturnHostErrorInfo is needed in order         */
/*   determine the success of the operation for this API.  Calling  */
/*   cwbDB_ReturnHostErrorInfo prior to calling this API will       */
/*   result in a synchronous operation (the application will not    */
/*   get control back until the result is returned to the PC from   */
/*   the AS/400).                                                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_RemoveMember(
                             cwbDB_RequestHandle  request,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_RemoveOverride                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Remove an override from a file reference.                      */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for List or SQL requests.                */
/*                                                                  */
/*   The cwbDB_RemoveOverRide API should be called after setting    */
/*   the desired values in the request.                             */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/*   A call to cwbDB_ReturnHostErrorInfo is needed in order         */
/*   determine the success of the operation for this API.  Calling  */
/*   cwbDB_ReturnHostErrorInfo prior to calling this API will       */
/*   result in a synchronous operation (the application will not    */
/*   get control back until the result is returned to the PC from   */
/*   the AS/400).                                                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_RemoveOverride(
                             cwbDB_RequestHandle  request,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_RetrieveFieldInformation                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   Get information about the fields in an AS/400 file.            */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned long retrieveInformation - input                      */
/*           Bitmap that indicates what information is to be        */
/*           retrieved for the fields.                              */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use the defined values:                                        */
/*                    CWBDB_GET_FLD_LIB                             */
/*                    CWBDB_GET_FLD_REMARKS                         */
/*                    CWBDB_GET_FLD_FILE                            */
/*                    CWBDB_GET_FLD_NAME                            */
/*                    CWBDB_GET_FLD_DESC                            */
/*                    CWBDB_GET_FLD_DATA_TYPE                       */
/*                    CWBDB_GET_FLD_LEN                             */
/*                    CWBDB_GET_FLD_NULL                            */
/*                    CWBDB_GET_FLD_RADIX                           */
/*                    CWBDB_GET_FLD_PREC                            */
/*                    CWBDB_GET_FLD_SCALE                           */
/*                    CWBDB_GET_FLD_CCSID                           */
/*                                                                  */
/*   rc = cwbDB_RetrieveFieldInformation(                           */
/*              requestHandle,                                      */
/*              CWBDB_GET_FLD_FILE      |                           */
/*              CWBDB_GET_FLD_NAME      |                           */
/*              CWBDB_GET_FLD_DATA_TYPE |                           */
/*              CWBDB_GET_FLD_PREC      |                           */
/*              CWBDB_GET_FLD_SCALE,                                */
/*              errorHandle);                                       */
/*                                                                  */
/*   This API is not valid for NDB or SQL requests.                 */
/*                                                                  */
/*   The cwbDB_RetrieveFieldInformation API should be called after  */
/*   setting the desired values in the request.                     */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/*   A call to the cwbDB_ReturnData API is needed prior to calling  */
/*   this API if the application is to process the data             */
/*   immediately.  If the application is to operate asynchronously, */
/*   then the call to cwbDB_ReturnData and subsequently             */
/*   cwbDB_GetData are needed after this API in order to get the    */
/*   data that result from this API call.  Once the data is         */
/*   returned, information in the data format handle is used to     */
/*   determine how to parse the data.                               */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_RetrieveFieldInformation(
                             cwbDB_RequestHandle  request,
                             unsigned long        retrieveInformation,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_RetrieveFileInformation                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   Get information about files on the AS/400.                     */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned long retrieveInformation - input                      */
/*           Bitmap that indicates what information is to be        */
/*           retrieved for the files.                               */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use the defined values:                                        */
/*                    CWBDB_GET_FILE_LIB                            */
/*                    CWBDB_GET_FILE_REMARKS                        */
/*                    CWBDB_GET_FILE_NAME                           */
/*                    CWBDB_GET_FILE_ATTRIB                         */
/*                    CWBDB_GET_FILE_TYPE                           */
/*                    CWBDB_GET_FILE_DESC                           */
/*                    CWBDB_GET_FILE_COL_CNT                        */
/*                    CWBDB_GET_FILE_AUTH                           */
/*                                                                  */
/*   rc = cwbDB_RetrieveFileInformation(                            */
/*              requestHandle,                                      */
/*              CWBDB_GET_FILE_NAME    |                            */
/*              CWBDB_GET_FILE_ATTRIB  |                            */
/*              CWBDB_GET_FILE_TYPE    |                            */
/*              CWBDB_GET_FILE_DESC    |                            */
/*              CWBDB_GET_FILE_COL_CNT |                            */
/*              CWBDB_GET_FILE_AUTH,                                */
/*              errorHandle );                                      */
/*                                                                  */
/*   This API is not valid for NDB or SQL requests.                 */
/*                                                                  */
/*   The cwbDB_RetrieveFileInformation API should be called after   */
/*   setting the desired values in the request.                     */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/*   A call to the cwbDB_ReturnData API is needed prior to calling  */
/*   this API if the application is to process the data             */
/*   immediately.  If the application is to operate asynchronously, */
/*   then the call to cwbDB_ReturnData and subsequently             */
/*   cwbDB_GetData are needed after this API in order to get the    */
/*   data that result from this API call.  Once the data is         */
/*   returned, information in the data format handle is used to     */
/*   determine how to parse the data.                               */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_RetrieveFileInformation(
                             cwbDB_RequestHandle  request,
                             unsigned long        retrieveInformation,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_RetrieveForeignKeyInformation                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Get information about foreign keys for an AS/400 file.         */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned long retrieveInformation - input                      */
/*           Bitmap that indicates what information is to be        */
/*           retrieved for foreign keys.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use the defined values:                                        */
/* Foreign Key Primary Key Information constants                    */
/*              CWBDB_GET_FG_PRKEY_LIB                              */
/*              CWBDB_GET_FG_PRKEY_FILE                             */
/*              CWBDB_GET_FG_PRKEY_COL_ID                           */
/* Foreign Key Information constants                                */
/*              CWBDB_GET_FG_KEY_LIB                                */
/*              CWBDB_GET_FG_KEY_FILE                               */
/*              CWBDB_GET_FG_KEY_COL_ID                             */
/*              CWBDB_GET_FG_KEY_SEQ                                */
/*              CWBDB_GET_FG_KEY_UPDATE                             */
/*              CWBDB_GET_FG_KEY_DELETE                             */
/*                                                                  */
/*   rc = cwbDB_RetrievePrimaryKeyInformation(                      */
/*              requestHandle,                                      */
/*              CWBDB_GET_FG_PRKEY_LIB |                            */
/*              CWBDB_GET_FG_PRKEY_FILE |                           */
/*              CWBDB_GET_FG_PRKEY_COL_ID |                         */
/*              CWBDB_GET_FG_KEY_LIB |                              */
/*              CWBDB_GET_FG_KEY_FILE |                             */
/*              CWBDB_GET_FG_KEY_COL_ID |                           */
/*              CWBDB_GET_FG_KEY_SEQ |                              */
/*              CWBDB_GET_FG_KEY_UPDATE |                           */
/*              CWBDB_GET_FG_KEY_DELETE,                            */
/*              errorHandle );                                      */
/*                                                                  */
/*   This API is not valid for NDB or SQL requests.                 */
/*                                                                  */
/*   The cwbDB_RetrieveForeignKeyInformation API should be called   */
/*   after setting the desired values in the request.               */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/*                                                                  */
/*   A call to the cwbDB_ReturnData API is needed prior to calling  */
/*   this API if the application is to process the data             */
/*   immediately.  If the application is to operate asynchronously, */
/*   then the call to cwbDB_ReturnData and subsequently             */
/*   cwbDB_GetData are needed after this API in order to get the    */
/*   data that result from this API call.  Once the data is         */
/*   returned, information in the data format handle is used to     */
/*   determine how to parse the data.                               */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_RetrieveForeignKeyInformation(
                             cwbDB_RequestHandle  request,
                             unsigned long        retrieveInformation,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_RetrieveIndexInformation                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   Get information about the indices for an AS/400 file.          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned long retrieveInformation - input                      */
/*           Bitmap that indicates what information is to be        */
/*           retrieved for the indices.                             */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use the defined values:                                        */
/*                    CWBDB_GET_IDX_LIB                             */
/*                    CWBDB_GET_IDX_TBL_NAME                        */
/*                    CWBDB_GET_IDX_UNIQUE                          */
/*                    CWBDB_GET_IDX_IDX_LIB                         */
/*                    CWBDB_GET_IDX_IDX_NAME                        */
/*                    CWBDB_GET_IDX_COL_CNT                         */
/*                    CWBDB_GET_IDX_COL_NAME                        */
/*                    CWBDB_GET_IDX_COL_SEQ                         */
/*                    CWBDB_GET_IDX_COLLAT                          */
/*                                                                  */
/*   rc = cwbDB_RetrieveIndexInformation(                           */
/*              requestHandle,                                      */
/*              CWBDB_GET_IDX_TBL_NAME  |                           */
/*              CWBDB_GET_IDX_UNIQUE    |                           */
/*              CWBDB_GET_IDX_IDX_LIB   |                           */
/*              CWBDB_GET_IDX_IDX_NAME  |                           */
/*              CWBDB_GET_IDX_COL_CNT,                              */
/*              errorHandle );                                      */
/*                                                                  */
/*   This API is not valid for NDB or SQL requests.                 */
/*                                                                  */
/*   The cwbDB_RetrieveIndexInformation API should be called        */
/*   after setting the desired values in the request.               */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/*   A call to the cwbDB_ReturnData API is needed prior to calling  */
/*   this API if the application is to process the data             */
/*   immediately.  If the application is to operate asynchronously, */
/*   then the call to cwbDB_ReturnData and subsequently             */
/*   cwbDB_GetData are needed after this API in order to get the    */
/*   data that result from this API call.  Once the data is         */
/*   returned, information in the data format handle is used to     */
/*   determine how to parse the data.                               */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_RetrieveIndexInformation(
                             cwbDB_RequestHandle  request,
                             unsigned long        retrieveInformation,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_RetrieveLibraryInformation                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Get information about a library or list of libraries.          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned long retrieveInformation - input                      */
/*           Bitmap that indicates what information is to be        */
/*           retrieved for the libraries.                           */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use the defined values:                                        */
/*                    CWBDB_GET_LIBRARY_NAME                        */
/*                    CWBDB_GET_LIBRARY_DESC                        */
/*                                                                  */
/*   rc = cwbDB_RetrieveLibraryInformation(                         */
/*              requestHandle,                                      */
/*              CWBDB_GET_LIBRARY_NAME |                            */
/*              CWBDB_GET_LIBRARY_DESC,                             */
/*              errorHandle );                                      */
/*                                                                  */
/*   This API is not valid for NDB or SQL requests.                 */
/*                                                                  */
/*   The cwbDB_RetrieveLibraryInformation API should be called      */
/*   after setting the desired values in the request.               */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/*   A call to the cwbDB_ReturnData API is needed prior to calling  */
/*   this API if the application is to process the data             */
/*   immediately.  If the application is to operate asynchronously, */
/*   then the call to cwbDB_ReturnData and subsequently             */
/*   cwbDB_GetData are needed after this API in order to get the    */
/*   data that result from this API call.  Once the data is         */
/*   returned, information in the data format handle is used to     */
/*   determine how to parse the data.                               */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_RetrieveLibraryInformation(
                             cwbDB_RequestHandle  request,
                             unsigned long        retrieveInformation,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_RetrieveLOBData                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   Retrieve LOB Data                                              */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbDB_DataHandle     data - input                              */
/*                                                                  */
/*   unsigned long        locator - input                           */
/*                                                                  */
/*   unsigned long        size - input                              */
/*                                                                  */
/*   unsigned long        start - input                             */
/*                                                                  */
/*   unsigned long        columnIndex - input                       */
/*             Column Index one based column number.  This is an    */
/*             optional parameter used to retrieve lob data for     */
/*             more than one row.  Must be zero if not used.        */
/*                                                                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_RetrieveLOBData(
                 cwbDB_RequestHandle  request,
                 cwbDB_DataHandle     data,
                 unsigned long        locator,
			     unsigned long        size,
			     unsigned long        start,
				 unsigned long        columnIndex,
                 cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_RetrieveMemberInformation                                */
/*                                                                  */
/* Purpose:                                                         */
/*   Get information about members of an AS/400 file.               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned long retrieveInformation - input                      */
/*           Bitmap that indicates what information is to be        */
/*           retrieved for the members.                             */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use the defined values:                                        */
/*                    CWBDB_GET_MBR_LIB                             */
/*                    CWBDB_GET_MBR_FILE                            */
/*                    CWBDB_GET_MBR_NAME                            */
/*                    CWBDB_GET_MBR_DESC                            */
/*                                                                  */
/*   rc = cwbDB_RetrieveMemberInformation(                          */
/*              requestHandle,                                      */
/*              CWBDB_GET_MBR_LIB      |                            */
/*              CWBDB_GET_MBR_FILE     |                            */
/*              CWBDB_GET_MBR_NAME     |                            */
/*              CWBDB_GET_MBR_DESC,                                 */
/*              errorHandle );                                      */
/*                                                                  */
/*   This API is not valid for NDB or SQL requests.                 */
/*                                                                  */
/*   The cwbDB_RetrieveMemberInformation API should be called       */
/*   after setting the desired values in the request.               */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/*   A call to the cwbDB_ReturnData API is needed prior to calling  */
/*   this API if the application is to process the data             */
/*   immediately.  If the application is to operate asynchronously, */
/*   then the call to cwbDB_ReturnData and subsequently             */
/*   cwbDB_GetData are needed after this API in order to get the    */
/*   data that result from this API call.  Once the data is         */
/*   returned, information in the data format handle is used to     */
/*   determine how to parse the data.                               */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_RetrieveMemberInformation(
                             cwbDB_RequestHandle  request,
                             unsigned long        retrieveInformation,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_RetrievePackageStatementInformation                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Get information about statements stored in a SQL package on    */
/*   the AS/400.                                                    */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned long retrieveInformation - input                      */
/*           Bitmap that indicates what information is to be        */
/*           retrieved for the SQL statements.                      */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use the defined values:                                        */
/*                    CWBDB_GET_SQLSTMT_LIB                         */
/*                    CWBDB_GET_SQLSTMT_PKG                         */
/*                    CWBDB_GET_SQLSTMT_NAME                        */
/*                    CWBDB_GET_SQLSTMT_TYPE                        */
/*                    CWBDB_GET_SQLSTMT_TEXT                        */
/*                    CWBDB_GET_SQLSTMT_PM_CNT                      */
/*                                                                  */
/*   rc = cwbDB_RetrievePackageStatementInformation(                */
/*              requestHandle,                                      */
/*              CWBDB_GET_SQLSTMT_NAME |                            */
/*              CWBDB_GET_SQLSTMT_TYPE |                            */
/*              CWBDB_GET_SQLSTMT_TEXT,                             */
/*              errorHandle );                                      */
/*                                                                  */
/*   This API is not valid for NDB or SQL requests.                 */
/*                                                                  */
/*   The cwbDB_RetrievePackageStatementInformation API should be    */
/*   called after setting the desired values in the request.        */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/*   A call to the cwbDB_ReturnData API is needed prior to calling  */
/*   this API if the application is to process the data             */
/*   immediately.  If the application is to operate asynchronously, */
/*   then the call to cwbDB_ReturnData and subsequently             */
/*   cwbDB_GetData are needed after this API in order to get the    */
/*   data that result from this API call.  Once the data is         */
/*   returned, information in the data format handle is used to     */
/*   determine how to parse the data.                               */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_RetrievePackageStatementInformation(
                             cwbDB_RequestHandle  request,
                             unsigned long        retrieveInformation,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_RetrievePrimaryKeyInformation                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Get information about primary keys for an AS/400 file.         */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned long retrieveInformation - input                      */
/*           Bitmap that indicates what information is to be        */
/*           retrieved for primary keys.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use the defined values:                                        */
/*              CWBDB_GET_PR_KEY_LIB                                */
/*              CWBDB_GET_PR_KEY_FILE                               */
/*              CWBDB_GET_PR_KEY_COL_ID                             */
/*              CWBDB_GET_PR_KEY_COL_SEQ                            */
/*                                                                  */
/*   rc = cwbDB_RetrievePrimaryKeyInformation(                      */
/*              requestHandle,                                      */
/*              CWBDB_GET_PR_KEY_LIB |                              */
/*              CWBDB_GET_PR_KEY_FILE |                             */
/*              CWBDB_GET_PR_KEY_COL_ID |                           */
/*              CWBDB_GET_PR_KEY_COL_SEQ,                           */
/*              errorHandle );                                      */
/*                                                                  */
/*   This API is not valid for NDB or SQL requests.                 */
/*                                                                  */
/*   The cwbDB_RetrievePrimaryKeyInformation API should be          */
/*   called after setting the desired values in the request.        */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/*   A call to the cwbDB_ReturnData API is needed prior to calling  */
/*   this API if the application is to process the data             */
/*   immediately.  If the application is to operate asynchronously, */
/*   then the call to cwbDB_ReturnData and subsequently             */
/*   cwbDB_GetData are needed after this API in order to get the    */
/*   data that result from this API call.  Once the data is         */
/*   returned, information in the data format handle is used to     */
/*   determine how to parse the data.                               */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_RetrievePrimaryKeyInformation(
                             cwbDB_RequestHandle  request,
                             unsigned long        retrieveInformation,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_RetrieveRDBInformation                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Get information about a relational database on the AS/400.     */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned long retrieveInformation - input                      */
/*           Bitmap that indicates what information is to be        */
/*           retrieved for the relational database.                 */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use the defined values:                                        */
/*                    CWBDB_GET_RDB_NAME                            */
/*                    CWBDB_GET_RDB_DEVICE                          */
/*                    CWBDB_GET_RDB_MODE                            */
/*                    CWBDB_GET_RDB_RMTLOC                          */
/*                    CWBDB_GET_RDB_LOCLOC                          */
/*                    CWBDB_GET_RDB_RMTNET                          */
/*                    CWBDB_GET_RDB_TPNAME                          */
/*                    CWBDB_GET_RDB_DESC                            */
/*                    CWBDB_GET_RDB_TPNDISP                         */
/*                    CWBDB_GET_RDB_PGM                             */
/*                    CWBDB_GET_RDB_PGMLIB                          */
/*                    CWBDB_GET_RDB_PGMLEVEL                        */
/*                                                                  */
/*   rc = cwbDB_RetrieveRDBInformation(                             */
/*              requestHandle,                                      */
/*              CWBDB_GET_RDB_NAME   |                              */
/*              CWBDB_GET_RDB_RMTLOC |                              */
/*              CWBDB_GET_RDB_RMTNET |                              */
/*              CWBDB_GET_RDB_TPNAME |                              */
/*              CWBDB_GET_RDB_DESC,                                 */
/*              errorHandle );                                      */
/*                                                                  */
/*   This API is not valid for NDB or SQL requests.                 */
/*                                                                  */
/*   The cwbDB_RetrieveRDBInformation API should be called after    */
/*   setting the desired values in the request.                     */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/*   A call to the cwbDB_ReturnData API is needed prior to calling  */
/*   this API if the application is to process the data             */
/*   immediately.  If the application is to operate asynchronously, */
/*   then the call to cwbDB_ReturnData and subsequently             */
/*   cwbDB_GetData are needed after this API in order to get the    */
/*   data that result from this API call.  Once the data is         */
/*   returned, information in the data format handle is used to     */
/*   determine how to parse the data.                               */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_RetrieveRDBInformation(
                             cwbDB_RequestHandle  request,
                             unsigned long        retrieveInformation,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_RetrieveRecordFormatInformation                          */
/*                                                                  */
/* Purpose:                                                         */
/*   Get information about the record formats for an AS/400 file.   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned long retrieveInformation - input                      */
/*           Bitmap that indicates what information is to be        */
/*           retrieved for the record formats.                      */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use the defined values:                                        */
/*                    CWBDB_GET_FMT_LIB                             */
/*                    CWBDB_GET_FMT_FILE                            */
/*                    CWBDB_GET_FMT_NAME                            */
/*                    CWBDB_GET_FMT_REC_LEN                         */
/*                    CWBDB_GET_FMT_DESC                            */
/*                                                                  */
/*   rc = cwbDB_RetrieveRecordFormatInformation(                    */
/*              requestHandle,                                      */
/*              CWBDB_GET_FMT_LIB      |                            */
/*              CWBDB_GET_FMT_FILE     |                            */
/*              CWBDB_GET_FMT_NAME     |                            */
/*              CWBDB_GET_FMT_REC_LEN  |                            */
/*              CWBDB_GET_FMT_DESC,                                 */
/*              errorHandle );                                      */
/*                                                                  */
/*   This API is not valid for NDB or SQL requests.                 */
/*                                                                  */
/*   The cwbDB_RetrieveRecordFormatInformation API should be called */
/*   after setting the desired values in the request.               */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/*   A call to the cwbDB_ReturnData API is needed prior to calling  */
/*   this API if the application is to process the data             */
/*   immediately.  If the application is to operate asynchronously, */
/*   then the call to cwbDB_ReturnData and subsequently             */
/*   cwbDB_GetData are needed after this API in order to get the    */
/*   data that result from this API call.  Once the data is         */
/*   returned, information in the data format handle is used to     */
/*   determine how to parse the data.                               */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_RetrieveRecordFormatInformation(
                             cwbDB_RequestHandle  request,
                             unsigned long        retrieveInformation,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_RetrieveSpecialColumnInformation                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Get information about special columns for an AS/400 file.      */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned long retrieveInformation - input                      */
/*           Bitmap that indicates what information is to be        */
/*           retrieved for the columns.                             */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use the defined values:                                        */
/*                    CWBDB_GET_SP_COL_LIB                          */
/*                    CWBDB_GET_SP_COL_TABLE                        */
/*                    CWBDB_GET_SP_COL_COL_NAME                     */
/*                    CWBDB_GET_SP_COL_DATA_TYPE                    */
/*                    CWBDB_GET_SP_COL_PRECISION                    */
/*                    CWBDB_GET_SP_COL_LENGTH                       */
/*                    CWBDB_GET_SP_COL_SCALE                        */
/*                                                                  */
/*   rc = cwbDB_RetrieveSpecialColumnInformation(                   */
/*              requestHandle,                                      */
/*              CWBDB_GET_SP_COL_LIB |                              */
/*              CWBDB_GET_SP_COL_TABLE |                            */
/*              CWBDB_GET_SP_COL_COL_NAME |                         */
/*              CWBDB_GET_SP_COL_DATA_TYPE |                        */
/*              CWBDB_GET_SP_COL_PRECISION |                        */
/*              CWBDB_GET_SP_COL_LENGTH |                           */
/*              CWBDB_GET_SP_COL_SCALE,                             */
/*              errorHandle );                                      */
/*                                                                  */
/*   This API is not valid for NDB or SQL requests.                 */
/*                                                                  */
/*   The cwbDB_RetrieveSpecialColumnInformation API should be       */
/*   called after setting the desired values in the request.        */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/*   A call to the cwbDB_ReturnData API is needed prior to calling  */
/*   this API if the application is to process the data             */
/*   immediately.  If the application is to operate asynchronously, */
/*   then the call to cwbDB_ReturnData and subsequently             */
/*   cwbDB_GetData are needed after this API in order to get the    */
/*   data that result from this API call.  Once the data is         */
/*   returned, information in the data format handle is used to     */
/*   determine how to parse the data.                               */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_RetrieveSpecialColumnInformation(
                             cwbDB_RequestHandle  request,
                             unsigned long        retrieveInformation,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_RetrieveSQLPackageInformation                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Get information about a SQL package on the AS/400.             */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned long retrieveInformation - input                      */
/*           Bitmap that indicates what information is to be        */
/*           retrieved for the SQL packages.                        */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use the defined values:                                        */
/*                    CWBDB_GET_SQLPKG_LIB                          */
/*                    CWBDB_GET_SQLPKG_NAME                         */
/*                    CWBDB_GET_SQLPKG_DESC                         */
/*                                                                  */
/*   rc = cwbDB_RetrieveSQLPackageInformation(                      */
/*              requestHandle,                                      */
/*              CWBDB_GET_SQLPKG_LIB   |                            */
/*              CWBDB_GET_SQLPKG_NAME  |                            */
/*              CWBDB_GET_SQLPKG_DESC,                              */
/*              errorHandle );                                      */
/*                                                                  */
/*   This API is not valid for NDB or SQL requests.                 */
/*                                                                  */
/*   The cwbDB_RetrieveSQLPackageInformation API should be          */
/*   called after setting the desired values in the request.        */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/*   A call to the cwbDB_ReturnData API is needed prior to calling  */
/*   this API if the application is to process the data             */
/*   immediately.  If the application is to operate asynchronously, */
/*   then the call to cwbDB_ReturnData and subsequently             */
/*   cwbDB_GetData are needed after this API in order to get the    */
/*   data that result from this API call.  Once the data is         */
/*   returned, information in the data format handle is used to     */
/*   determine how to parse the data.                               */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_RetrieveSQLPackageInformation(
                             cwbDB_RequestHandle  request,
                             unsigned long        retrieveInformation,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_ReturnData                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Instructs the API to return the data that is in the result set */
/*   for the operation.                                             */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbDB_DataHandle data - input                                  */
/*           Handle for the data being returned.  This address is   */
/*           returned when the data is received from the AS/400     */
/*           upon completion of a function request.                 */
/*                                                                  */
/*   cwbDB_DataHandle indicators - input                            */
/*           Handle  which will be used to return the address of    */
/*           of the null value/error indicators being returned.     */
/*           There is one indicator value for each column value     */
/*           that is to be returned (for each column of each row)   */
/*           The indicator will be a negative number if the value   */
/*           for the column is NULL.  If an error occurs while      */
/*           converting the data, a character 'E' will be placed    */
/*           in that columns indicator field.  This address is      */
/*           returned when the data is received from the AS/400     */
/*           upon completion of a function request.                 */
/*                                                                  */
/*   cwbDB_FormatHandle formatHandle - input                        */
/*           Handle to a data format that contains a description    */
/*           of the returned data.                                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The cwbDB_ReturnData API is used to instruct the AS/400 server */
/*   to return the data which results from an operation (either a   */
/*   SQL fetch operation or a catalog retrieval operation).  After  */
/*   calling this API, the next API call for the request that       */
/*   results in a datastream to flow to the server will result in   */
/*   the requested data being returned to the application.          */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_ReturnData(
                             cwbDB_RequestHandle  request,
                             cwbDB_DataHandle     data,
                             cwbDB_DataHandle     indicators,
                             cwbDB_FormatHandle   formatHandle,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_ReturnDataFormat                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Instructs the API to return the format of the data to be       */
/*   returned.                                                      */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbDB_FormatHandle formatHandle - input                        */
/*           Handle to a data format that contains a description    */
/*           of the returned data.                                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The cwbDB_ReturnDataFormat API is used to instruct the AS/400  */
/*   server to return the data format which describes a set of      */
/*   selected data.  After calling this API, the next API call for  */
/*   the request that results in a datastream to flow to the server */
/*   will result in the requested data being returned to the        */
/*   application.                                                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_ReturnDataFormat(
                             cwbDB_RequestHandle  request,
                             cwbDB_FormatHandle   formatHandle,
                             cwbSV_ErrHandle      errorHandle);


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_ReturnExtendedDataFormat                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   Instructs the API to return the Extended version format of the */
/*   data to be returned.                                           */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbDB_FormatHandle formatHandle - input                        */
/*           Handle to a data format that contains a description of */
/*           the returned data, including the extended data.        */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWBDB_SERVER_FUNCTION_NOT_AVAILABLE - The host server is not   */
/*                   at the required level to support this feature. */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The cwbDB_ReturnExtendedDataFormat API is used to instruct the */
/*   AS/400 server to retrieve the extended data format             */
/*   information, in addition to the base data format information.  */
/*                                                                  */
/*   This API is used instead of the cwbDB_ReturnDataFormat() API   */
/*   in cases where the extended data format information is         */
/*   required in addition to the base data format information.      */
/*                                                                  */
/*   The extended format data includes the information retrieved    */
/*   using the following APIs:                                      */
/*                                                                  */
/*   cwbDB_GetExtendedColumnInfo                                    */
/*   cwbDB_GetBaseColumnName                                        */
/*   cwbDB_GetBaseSchemaName                                        */
/*   cwbDB_GetBaseTableName                                         */
/*   cwbDB_GetLabelName                                             */
/*                                                                  */
/*   After calling this API, the next API call for the request that */
/*   results in a datastream to flow to the server will result in   */
/*   the requested data being returned to the application.          */
/*                                                                  */
/*   If the host server is not at the required level to support     */
/*   this feature, then the non-extended version of the data format */
/*   will be returned, and subsequent calls to get extended data    */
/*   will return default values.                                    */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_ReturnExtendedDataFormat(
                             cwbDB_RequestHandle request,
                             cwbDB_FormatHandle  format,
                             cwbSV_ErrHandle     errorHandle);


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_ReturnHostErrorInfo                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Instructs the API to return host error information when a      */
/*   function is performed on the host server.                      */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned short *hostErrorClass - input                         */
/*           Pointer to location where the error class will be      */
/*           returned.  This class indicates which database server  */
/*           module encountered an error.                           */
/*                    0 - no error                                  */
/*                    1 - SQL functional error                      */
/*                    2 - SQL parameter error                       */
/*                    3 - List functional error                     */
/*                    4 - List parameter error                      */
/*                    5 - NDB functional error                      */
/*                    6 - NDB parameter error                       */
/*                    7 - General server error                      */
/*                    8 - User exit error                           */
/*                                                                  */
/*   signed long *hostErrorCode - input                             */
/*           Pointer to location where the return code from the     */
/*           server module will be placed.                          */
/*                                                                  */
/*   cwbDB_DataHandle hostMsgID - input                             */
/*           Handle to a data object that will contain              */
/*           the host message identifier.                           */
/*           If this parameter is set to 0, the                     */
/*           host message identifier will not be retrieved.         */
/*                                                                  */
/*   cwbDB_DataHandle firstLevelMessageText - input                 */
/*           Handle to a data object that will contain              */
/*           the host first level message text.                     */
/*           If this parameter is set to 0, the                     */
/*           first level message text will not be retrieved.        */
/*                                                                  */
/*   cwbDB_DataHandle secondLevelMessageText - input                */
/*           Handle to a data object that will contain              */
/*           the host second level message text.                    */
/*           If this parameter is set to 0, the                     */
/*           second level message text will not be retrieved.       */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The cwbDB_ReturnHostErrorInfo API is used to instruct the      */
/*   AS/400 server to return the error or diagnostic information    */
/*   pertaining to a functional request.  After calling this API,   */
/*   the next API call for the request that results in a datastream */
/*   to flow to the server will result in the requested data being  */
/*   returned to the application.                                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_ReturnHostErrorInfo(
                             cwbDB_RequestHandle     request,
                             unsigned short         *hostErrorClass,
                             signed long            *hostErrorCode,
                             cwbDB_DataHandle        hostMsgID,
                             cwbDB_DataHandle        firstLevelMessageText,
                             cwbDB_DataHandle        secondLevelMessageText,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_ReturnParameterMarkerFormat                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Instructs the API to return the format of the parameter marker */
/*   data for a SQL statement.                                      */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbDB_FormatHandle formatHandle - input                        */
/*           Handle to a parameter marker format that will contain  */
/*           the description of parameter data.                     */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The cwbDB_ReturnParameterMarkerFormat API is used to instruct  */
/*   the AS/400 server to return the format which describes a set   */
/*   parameter markers for a prepared statement.                    */
/*   After calling this API, the next API call for the request that */
/*   results in a datastream to flow to the server will result in   */
/*   the requested data being returned to the application.          */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_ReturnParameterMarkerFormat(
                             cwbDB_RequestHandle  request,
                             cwbDB_FormatHandle   formatHandle,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_ReturnSQLCA                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Instructs the API to return the SQL Communication Area         */
/*   (SQLCA).                                                       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   struct cwbDB_SQLCA *sqlca - input                              */
/*           Pointer to a structure that will contain SQLCA         */
/*           returned from the host.                                */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The cwbDB_ReturnSQLCA API is used to instruct the AS/400       */
/*   server to return the SQL Communication Area (SQLCA).           */
/*   After calling this API, the next API call for the request that */
/*   results in a datastream to flow to the server will result in   */
/*   the requested data being returned to the application.          */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_ReturnSQLCA(
                             cwbDB_RequestHandle  request,
                             cwbDB_SQLCA         *sqlca,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_Rollback                                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   Perform a rollback operation.                                  */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/*   The cwbDB_Rollback API should be called after setting the      */
/*   desired values in the request.                                 */
/*                                                                  */
/*   This API will result in a request datastream flowing to the    */
/*   AS/400 server and if requested, a response to the request      */
/*   flowing back to the client.                                    */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_Rollback(
                             cwbDB_RequestHandle  request,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetAddLibraryName                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Add a library to the AS/400 library list.                      */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   const char *addLibraryName - input                             */
/*           The name of the library to be added to the library     */
/*           list.                                                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The cwbDB_AddLibraryToList API should be called after calling  */
/*   this API.                                                      */
/*                                                                  */
/*   The cwbDB_SetAddLibraryPosition API may be called before or    */
/*   after this API is called, but before cwbDB_AddLibraryToList is */
/*   called.                                                        */
/*                                                                  */
/*   This API is not valid for List or SQL requests.                */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDB_SetAddLibraryName(
                             cwbDB_RequestHandle  request,
                             const char          *addLibraryName,
                             cwbSV_ErrHandle      errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDB_SetAddLibraryNameA(
                                 cwbDB_RequestHandle  request,
                                 LPCSTR               addLibraryName,
                                 cwbSV_ErrHandle      errorHandle  );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDB_SetAddLibraryNameW(
				 cwbDB_RequestHandle  request,
				 LPCWSTR              addLibraryName,
				 cwbSV_ErrHandle      errorHandle  );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) )) )
   #define  cwbDB_SetAddLibraryName    cwbDB_SetAddLibraryNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) )) )
   #define  cwbDB_SetAddLibraryName    cwbDB_SetAddLibraryNameA
#endif

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetAddLibraryPosition                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   Sets the position at which to add a library to the library     */
/*   list via the cwbDB_AddLibraryToList API.                       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   const unsigned short position - input                          */
/*           The position in the library list to add the library    */
/*           name set via cwbDB_SetAddLibraryName. Use one of the   */
/*           following defined constants:                           */
/*                                                                  */
/*        CWBDB_ADD_LIBRARY_TO_FRONT - Add library to front of list */
/*        CWBDB_ADD_LIBRARY_TO_END   - Add library to end of list   */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for List or SQL requests.                */
/*                                                                  */
/*   The cwbDB_AddLibraryToList API should be called after calling  */
/*   this API.                                                      */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetAddLibraryPosition(
                             cwbDB_RequestHandle  request,
                             const unsigned short position,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetAllowAddStatementToPackage                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Sets server attribute for the connection to indicate if        */
/*   statements can be added to the package.                        */
/*                                                                  */
/* unsigned int CWB_ENTRY cwbDB_SetAllowAddStatementToPackage(      */
/*          cwbDB_ConnectionHandle    connection,                   */
/*          cwb_Boolean               allowAdd,                     */
/*          cwbSV_ErrHandle           errorHandle);                 */
/*                                                                  */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*      Handle to connection to AS/400 database access server.      */
/*                                                                  */
/*   cwb_Boolean  allowAdd - input                                  */
/*           Indicates whether SQL statements should be added to    */
/*           the package, if one is in use.                         */
/*                                                                  */
/*           CWB_FALSE indicates don't allow statements to be added.*/
/*           CWB_TRUE indicates add statement allowed.  Default is  */
/*           allow add.                                             */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*                                                                  */
/*                                                                  */
/*   The cwbDB_ApplyAttributes API must be called after             */
/*   cwbDB_SetAllowAddStatementToPackage in order for the new value */
/*   to take affect.                                                */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetAllowAddStatementToPackage(
                             cwbDB_ConnectionHandle  connection,
                             cwb_Boolean               allowAdd,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetAmbiguousSelectOption                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   Sets server attribute for the connection to indicate the       */
/*   explicit updateability                                         */
/* Syntax                                                           */
/*   unsigned int CWB_ENTRY cwbDB_SetAmbiguousSelectOption(         */
/*           cwbDB_ConnectionHandle    connection,                  */
/*           unsigned short            updateability,               */
/*           cwbSV_ErrHandle           errorHandle);                */
/*                                                                  */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*      Handle to connection to AS/400 database access server.      */
/*                                                                  */
/*   unsigned short     updateability  - input                      */
/*      Indicates if SQL SELECT statements which do not have        */
/*      explicit FOR FETCH ONLY or FOR UPDATE OF clauses specified  */
/*      should be updateable or read-only.  The default is          */
/*      updateable.                                                 */
/*                                                                  */
/*         Use one of these two predefined values:                  */
/*              CWBDB_UPDATEABLE                                    */
/*              CWBDB_READONLY                                      */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*                                                                  */
/*                                                                  */
/*   The cwbDB_ApplyAttributes API must be called after             */
/*   cwbDB_SetAmbiguousSelectOption in order for the new value      */
/*   to take affect.                                                */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetAmbiguousSelectOption(
                             cwbDB_ConnectionHandle  connection,
                             unsigned short          updateability,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetAuthority                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the public authority for a file that will be created       */
/*   through the API.                                               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned short authority - input                               */
/*           Long integer that indicates the public authority for   */
/*           a newly created file.                                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWBDB_INVALID_ARG_API - Invalid authority value                */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use one of the defined values:                                 */
/*                    CWBDB_SET_LIBRARY_CREATE_AUTHORITY            */
/*                    CWBDB_SET_ALL_AUTHORITY                       */
/*                    CWBDB_SET_CHANGE_AUTHORITY                    */
/*                    CWBDB_SET_EXCLUDE_AUTHORITY                   */
/*                    CWBDB_SET_USE_AUTHORITY                       */
/*                    CWBDB_SET_SAME_AUTHORITY
/*                                                                  */
/*   This API is not valid for List or SQL requests.                */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetAuthority(
                             cwbDB_RequestHandle  request,
                             unsigned short       authority,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetAutoCommit                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Set an indicator that indicates if implicit commits will       */
/*   be done on the server                                          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*       Handle to connection to AS/400 database access server      */
/*                                                                  */
/*   unsigned short autoCommit - input                              */
/*       Indicates if auto commit will be done.                      */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use one of the defined values:                                 */
/*                    CWBDB_AUTO_COMMIT                             */
/*                    CWBDB_NO_AUTO_COMMIT                          */
/*                                                                  */
/*   The default if not set is iplicit commits will be done.       */
/*                                                                  */
/*                                                                  */
/*   The cwbDB_ApplyAttributes API must be called after             */
/*   cwbDB_SetAutoCommit in order for the new value to              */
/*   take affect.                                                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetAutoCommit(
                             cwbDB_ConnectionHandle  connection,
                             unsigned short          autoCommit,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetBaseFile                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the name of a base file for creating a new file with the   */
/*   same format through the API.                                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   const char *baseLibraryName - input                            */
/*           Pointer to an ASCIIZ string that contains the base     */
/*           library name to be used when creating a new file.      */
/*                                                                  */
/*   const char *baseFileName - input                               */
/*           Pointer to an ASCIIZ string that contains the base     */
/*           file name to be used when creating a new file.         */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is used in preparation for cwbDB_CreateDuplicateFile. */
/*                                                                  */
/*   This API is not valid for List or SQL requests.                */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDB_SetBaseFile(
                             cwbDB_RequestHandle  request,
                             const char          *baseLibraryName,
                             const char          *baseFileName,
                             cwbSV_ErrHandle      errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDB_SetBaseFileA(
                                   cwbDB_RequestHandle  request,
                                   LPCSTR               baseLibraryName,
                                   LPCSTR               baseFileName,
                                   cwbSV_ErrHandle      errorHandle  );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDB_SetBaseFileW(
                                   cwbDB_RequestHandle  request,
                                   LPCWSTR              baseLibraryName,
                                   LPCWSTR              baseFileName,
                                   cwbSV_ErrHandle      errorHandle );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDB_SetBaseFile               cwbDB_SetBaseFileW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDB_SetBaseFile               cwbDB_SetBaseFileA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetBlockCount                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the number of rows to be blocked together when fetching    */
/*   data.                                                          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned long blockCount - input                               */
/*           Input value for block count.                           */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetBlockCount(
                             cwbDB_RequestHandle  request,
                             unsigned long        blockCount,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetClientColumnToNumeric                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   Sets the information for a column description for string data. */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a data format object.                        */
/*                                                                  */
/*   unsigned long columnPosition - input                           */
/*           Specifies the relative position of the column.         */
/*                                                                  */
/*   signed short columnType - input                                */
/*         Specifies the numeric type to be used.                   */
/*                                                                  */
/*   unsigned long columnLength - input                             */
/*         Only used if the type is zoned or packed decimal         */
/*                                                                  */
/*   unsigned short columnPrecision - input                         */
/*         Only used if the type is zoned or packed decimal         */
/*                                                                  */
/*   unsigned short columnScale - input                             */
/*         Only used if the type is zoned or packed decimal         */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   For the columnType parameter, use one of the defined values:   */
/*                    CWBDB_PCLONG                                  */
/*                    CWBDB_PCSHORT                                 */
/*                    CWBDB_PCFLOAT                                 */
/*                    CWBDB_PCDOUBLE                                */
/*                    CWBDB_PCPACKED                                */
/*                    CWBDB_PCZONED                                 */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetClientColumnToNumeric(
                             cwbDB_FormatHandle  format,
                             unsigned long       columnPosition,
                             signed short        columnType,
                             unsigned long       columnLength,
                             unsigned short      columnPrecision,
                             unsigned short      columnScale,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetClientColumnToString                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   Sets the information for a column description for string data. */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a data format object.                        */
/*                                                                  */
/*   unsigned long columnPosition - input                           */
/*           Specifies the relative position of the column.         */
/*                                                                  */
/*   signed short columnType - input                                */
/*           Specifies the string type to be used.                  */
/*                                                                  */
/*   unsigned long columnLength - input                             */
/*           Specifies the column length to be used.                */
/*                                                                  */
/*   unsigned short columnCCSID - input                             */
/*           Specifies the column CCSID (Coded Character Set        */
/*           Identifier) to be used.                                */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   For the columnType parameter, use one of the defined values:   */
/*                    CWBDB_PCSTRING                                */
/*                    CWBDB_PCVARSTRING                             */
/*                    CWBDB_PCGRAPHIC                               */
/*                    CWBDB_PCVARGRAPHIC                            */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetClientColumnToString(
                             cwbDB_FormatHandle  format,
                             unsigned long       columnPosition,
                             signed short        columnType,
                             unsigned long       columnLength,
                             unsigned short      columnCCSID,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetClientDataCCSID                                       */
/*                                                                  */
/* Purpose:                                                         */
/*   Sets the CCSID (Coded Character Set ID) for the client.        */
/*   The new CCSID value will be used when converting EBCDIC data   */
/*   from the AS/400.                                               */
/*                                                                  */
/*   Use cwbDB_SetClientHostErrorCCSID to set the CCSID used when   */
/*   converting host error information.                             */
/*                                                                  */
/* Parameters:                                                      */
/*                                                                  */
/*   cwbDB_ConnectionHandle connection - input                      */
/*       Handle to connection to AS/400 database access server.     */
/*                                                                  */
/*   unsigned short clientCCSID - input                             */
/*           Specifies the CCSID (Coded Character Set Identifier    */
/*           to be used.                                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API may be called any time after a connection handle      */
/*   has been created.                                              */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetClientDataCCSID(
                             cwbDB_ConnectionHandle  connection,
                             unsigned short          clientDataCCSID,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetClientHostErrorCCSID                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   Sets the CCSID (Coded Character Set ID) for the client.        */
/*   The new CCSID value will be used when converting EBCDIC server */
/*   messages.                                                      */
/*                                                                  */
/*   Use cwbDB_SetClientDataCCSID to change the CCSID used          */
/*   for converting data.                                           */
/*                                                                  */
/* Parameters:                                                      */
/*                                                                  */
/*   cwbDB_ConnectionHandle connection - input                      */
/*       Handle to connection to AS/400 database access server.     */
/*                                                                  */
/*   unsigned short clientHostErrorCCSID - input                    */
/*           Specifies the CCSID (Coded Character Set Identifier    */
/*           to be used.                                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API may be called any time after a connection handle      */
/*   has been created.                                              */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetClientHostErrorCCSID(
                             cwbDB_ConnectionHandle  connection,
                             unsigned short          clientHostErrorCCSID,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetClientInputCCSID                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Sets the CCSID (Coded Character Set ID) for data being         */
/*   input such as file names, SQL statement text, and so on.       */
/*   The new CCSID value will be used when converting EBCDIC data   */
/*   from the AS/400.                                               */
/*                                                                  */
/*   Use cwbDB_SetClientHostErrorCCSID to set the CCSID used when   */
/*   converting host error information.                             */
/*                                                                  */
/* Parameters:                                                      */
/*                                                                  */
/*   cwbDB_ConnectionHandle connection - input                      */
/*       Handle to connection to AS/400 database access server.     */
/*                                                                  */
/*   unsigned short inputCCSID - input                              */
/*           Specifies the CCSID (Coded Character Set Identifier    */
/*           to be used.                                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API may be called any time after a connection handle      */
/*   has been created.                                              */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetClientInputCCSID(
                             cwbDB_ConnectionHandle  connection,
                             unsigned short          inputCCSID,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetClientParameterToNumeric                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Sets the information for a parameter description for string    */
/*   data.                                                          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a data format object.                        */
/*                                                                  */
/*   unsigned long parameterPosition - input                        */
/*           Specifies the relative position of the parameter.      */
/*                                                                  */
/*   signed short parameterType - input                             */
/*         Specifies the numeric type to be used.                   */
/*                                                                  */
/*   unsigned long parameterLength - input                          */
/*         Only used if the type is zoned or packed decimal         */
/*                                                                  */
/*   unsigned short parameterPrecision - input                      */
/*         Only used if the type is zoned or packed decimal         */
/*                                                                  */
/*   unsigned short parameterScale - input                          */
/*         Only used if the type is zoned or packed decimal         */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   For the parameterType parameter, use one of the defined        */
/*   values:                                                        */
/*                    CWBDB_PCLONG                                  */
/*                    CWBDB_PCSHORT                                 */
/*                    CWBDB_PCFLOAT                                 */
/*                    CWBDB_PCDOUBLE                                */
/*                    CWBDB_PCPACKED                                */
/*                    CWBDB_PCZONED                                 */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetClientParameterToNumeric(
                             cwbDB_FormatHandle  format,
                             unsigned long       parameterPosition,
                             signed short        parameterType,
                             unsigned long       parameterLength,
                             unsigned short      parameterPrecision,
                             unsigned short      parameterScale,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetClientParameterToString                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Sets the information for a parameter description for string    */
/*   data.                                                          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to a data format object.                        */
/*                                                                  */
/*   unsigned long parameterPosition - input                        */
/*           Specifies the relative position of the parameter.      */
/*                                                                  */
/*   signed short parameterType - input                             */
/*           Specifies the string type to be used.                  */
/*                                                                  */
/*   unsigned long parameterLength - input                          */
/*           Specifies the parameter length to be used.             */
/*                                                                  */
/*   unsigned short parameterCCSID - input                          */
/*           Specifies the parameter CCSID (Coded Character Set     */
/*           Identifier) to be used.                                */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   For the parameterType parameter, use one of the defined        */
/*   values:                                                        */
/*                    CWBDB_PCSTRING                                */
/*                    CWBDB_PCVARSTRING                             */
/*                    CWBDB_PCGRAPHIC                               */
/*                    CWBDB_PCVARGRAPHIC                            */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetClientParameterToString(
                             cwbDB_FormatHandle  format,
                             unsigned long       parameterPosition,
                             signed short        parameterType,
                             unsigned long       parameterLength,
                             unsigned short      parameterCCSID,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetCommitmentControl                                     */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the commitment level for the database server to use when   */
/*   accessing data.                                                */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*      Handle to connection to AS/400 database access server.      */
/*                                                                  */
/*   unsigned short commitmentLevel - input                         */
/*       Indicates the commitment level for server operations.      */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use one of the defined values:                                 */
/*                    CWBDB_NONE                                    */
/*                    CWBDB_CURSOR_STABILITY                        */
/*                    CWBDB_CHANGE                                  */
/*                    CWBDB_ALL                                     */
/*                                                                  */
/*   The cwbDB_ApplyAttributes API must be called after             */
/*   cwbDB_SetCommitmentControl in order for the new commitment     */
/*   level to take affect.                                          */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetCommitmentControl(
                             cwbDB_ConnectionHandle  connection,
                             unsigned short          commitmentLevel,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetConversionIndicator                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Sets the indicator that says whether data is to be converted   */
/*   between the client and host format.                            */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_FormatHandle format - input                              */
/*        Handle to a data format object.                           */
/*                                                                  */
/*   cwb_Boolean conversionIndicator - input                        */
/*        CWB_FALSE indicates no conversion.                        */
/*        CWB_TRUE indicates conversion.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/*   The cwbDB_ApplyAttributes API must be called after             */
/*   cwbDB_SetConversionIndicator in order for the new value to     */
/*   take affect.                                                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetConversionIndicator(
                             cwbDB_FormatHandle  format,
                             cwb_Boolean         conversionIndicator,
                             cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetConvert65535                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   Sets the indicator that says whether data marked with CCSID    */
/*   65535 is to be converted between ASCII and EBCDIC. Data tagged */
/*   with CCSID 65535 are binary data. Selecting to convert this    */
/*   this data may cause conversion errors and possible data        */
/*   integrity problems. USE THIS API AT YOUR OWN RISK.             */
/*                                                                  */
/*   Having said that, it is important to note that some older data */
/*   may have text data tagged with CCSID 65535. Also, some AS/400  */
/*   tools still write data to files using CCSID 65535. Therefore,  */
/*   there may be appropriate times to use this API.                */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*        Handle to a connection object.                            */
/*                                                                  */
/*   cwb_Boolean convert65535indicator - input                      */
/*        CWB_FALSE indicates no conversion of binary data.         */
/*        CWB_TRUE indicates conversion of data will take place.    */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetConvert65535(
                             cwbDB_ConnectionHandle   connection,
                             cwb_Boolean              convert65535indicator,
                             cwbSV_ErrHandle          errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetCursorName                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the statement name to be used for this request.            */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   const char *cursorName - input                                 */
/*           Pointer to an ASCIIZ string containing the cursor      */
/*           name being used for a SQL request.                     */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDB_SetCursorName(
                             cwbDB_RequestHandle  request,
                             const char          *cursorName,
                             cwbSV_ErrHandle      errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDB_SetCursorNameA(
                                  cwbDB_RequestHandle    request,
                                  LPCSTR                 cursorName,
                                  cwbSV_ErrHandle        errorHandle  );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDB_SetCursorNameW(
                                  cwbDB_RequestHandle    request,
                                  LPCWSTR                cursorName,
                                  cwbSV_ErrHandle        errorHandle );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDB_SetCursorName             cwbDB_SetCursorNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDB_SetCursorName             cwbDB_SetCursorNameA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetCursorReuse                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   This API inicates to SQL what our future plans are for cusors  */
/*   when we close them. This is valid when there are multiple      */
/*   result sets.                                                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned short reuseIndicator - input                          */
/*        Input value for reuse indicator.                          */
/*                                                                  */
/*        This parameter should be one of the following values:     */
/*           CWBDB_CLOSE_ALL_CURSORS Close the cursor for all       */
/*                                   result sets                    */
/*           CWBDB_CLOSE_CURRENT_CURSOR  Close the cursor for       */
/*                                       current resutlt set only   */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWBDB_INVALID_ARG_API - Invalid reuseIndicator value.          */
/*                                                                  */
/* Usage Notes:                                                     */
/*  When a cursor is opened against a stored procedure which has    */
/*  multiple result sets all result sets are opened and handled     */
/*  with the same cursor.  When the cursor is opened it points to   */
/*  the first result set.  When it is closed with the               */
/*  CWBDB_CLOSE_CURRENT_CURSOR option it closes the cursor and      */
/*  current result set.  When it is opened again it points to the   */
/*  next result set until the last result set is closed.            */
/*                                                                  */
/*  When it is closed with the CWBDB_CLOSE_ALL_CURSORS option it    */
/*  closes the cursor and all result sets, so it cannot be opened   */
/*  again.                                                          */
/*                                                                  */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetCursorReuse(
                             cwbDB_RequestHandle  request,
                             unsigned short       reuseIndicator,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/* API:                                                             */
/*   cwbDB_SetDateFormat                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the format for date data returned from the AS/400.         */
/*   Date data on the AS/400 are stored encoded and are             */
/*   returned to the client as character strings. These             */
/*   character strings can be formatted in eight different          */
/*   ways:                                                          */
/*                                                                  */
/*    Format name          Format          Example                  */
/*    ---------------      ----------      ---------------          */
/*    Julian               yy/ddd          87/253                   */
/*    month day year       mm/dd/yy        10/12/87                 */
/*    day month year       dd/mm/yy        12/10/87                 */
/*    year month day       yy/mm/dd        87/10/12                 */
/*    USA                  mm/dd/yyyy      10/12/1987               */
/*    ISO                  yyyy-mm-dd      1987-10-12               */
/*    IBM Japan            yyyy-mm-dd      1987-10-12               */
/*    IBM Europe           dd.mm.yyyy      12.10.1987               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*      Handle to connection to AS/400 database access server.      */
/*                                                                  */
/*   unsigned short dateFormat - input                              */
/*       Indicates the format of date data.                         */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*   CWBDB_INVALID_ARG_API - Value specified is not in range.       */
/*                                                                  */
/* Usage Notes:                                                     */
/*   It is not valid to call this API after calling the             */
/*   cwbDB_StartServer API.                                         */
/*                                                                  */
/*   Use one of the defined values:                                 */
/*        Format name          Date format constant       Value     */
/*        ---------------      --------------------       ------    */
/*        Julian               CWBDB_DATE_FMT_JUL           0       */
/*        month day year       CWBDB_DATE_FMT_MDY           1       */
/*        day month year       CWBDB_DATE_FMT_DMY           2       */
/*        year month day       CWBDB_DATE_FMT_YMD           3       */
/*        USA                  CWBDB_DATE_FMT_USA           4       */
/*        ISO                  CWBDB_DATE_FMT_ISO           5       */
/*        IBM Japan            CWBDB_DATE_FMT_JIS           6       */
/*        IBM Europe           CWBDB_DATE_FMT_EUR           7       */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbDB_SetDateFormat(
                             cwbDB_ConnectionHandle  connection,
                             unsigned short          dateFormat,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetDateSeparator                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the character which separates the elements of date data    */
/*   returned from the AS/400.                                      */
/*                                                                  */
/*   Date data on the AS/400 are stored encoded and are             */
/*   returned to the client as character strings. These             */
/*   character strings can have one of five different date          */
/*   separator characters:                                          */
/*                                                                  */
/*    Date separator       Character       Example                  */
/*    ---------------      ----------      ---------------          */
/*    Slash                /               03/17/94                 */
/*    Dash                 -               03-17-94                 */
/*    Period               .               03.17.94                 */
/*    Comma                ,               03,17,94                 */
/*    Blank                                03 17 94                 */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*      Handle to connection to AS/400 database access server.      */
/*                                                                  */
/*   unsigned short dateSeparator - input                           */
/*       Indicates the separator character for date fields.         */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*   CWBDB_INVALID_ARG_API - Value specified is not in range.       */
/*                                                                  */
/* Usage Notes:                                                     */
/*   It is not valid to call this API after calling the             */
/*   cwbDB_StartServer API.                                         */
/*                                                                  */
/*   Use one of the defined values:                                 */
/*        Date separator       Date separator constant              */
/*        ---------------      -----------------------              */
/*        Slash                CWBDB_DATE_SEP_SLASH                 */
/*        Dash                 CWBDB_DATE_SEP_DASH                  */
/*        Period               CWBDB_DATE_SEP_PERIOD                */
/*        Comma                CWBDB_DATE_SEP_COMMA                 */
/*        Blank                CWBDB_DATE_SEP_BLANK                 */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbDB_SetDateSeparator(
                             cwbDB_ConnectionHandle  connection,
                             unsigned short          dateSeparator,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetDecimalSeparator                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the character which separates the elements of decimal      */
/*   data returned from the AS/400.                                 */
/*                                                                  */
/*    Decimal separator      Character       Example                */
/*    -----------------      ----------      ---------------        */
/*    Period                 .               123.45                 */
/*    Comma                  ,               123,45                 */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*      Handle to connection to AS/400 database access server.      */
/*                                                                  */
/*   unsigned short decimalSeparator - input                        */
/*       Indicates the desired decimal separator character.         */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*   CWBDB_INVALID_ARG_API - Value specified is not in range.       */
/*                                                                  */
/* Usage Notes:                                                     */
/*   It is not valid to call this API after calling the             */
/*   cwbDB_StartServer API.                                         */
/*                                                                  */
/*   Use one of the defined values:                                 */
/*        Time separator       Time separator constant              */
/*        ---------------      -----------------------              */
/*        Period               CWBDB_DECIMAL_SEP_PERIOD             */
/*        Comma                CWBDB_DECIMAL_SEP_COMMA              */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbDB_SetDecimalSeparator(
                             cwbDB_ConnectionHandle  connection,
                             unsigned short          decimalSeparator,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetDefaultSQLLibraryName                                 */
/*                                                                  */
/* Purpose                                                          */
/*  Sets server attribute for the connection to indicate the        */
/*  default library name.                                           */
/*                                                                  */
/* Syntax                                                           */
/*    unsigned int CWB_ENTRY cwbDB_SetDefaultSQLLibraryName(        */
/*          cwbDB_ConnectionHandle    connection,                   */
/*          char*                     libraryName,                  */
/*          cwbSV_ErrHandle           errorHandle);                 */
/*                                                                  */
/* Parameters                                                       */
/*    cwbDB_ConnectionHandle  connection - input                    */
/*                                                                  */
/*    Handle to a connection object.                                */
/*                                                                  */
/*    char*   libraryName,  - input                                 */
/*        Pointer to a character string up to 10 characters long    */
/*        that specifies the qualified library name to use on the   */
/*        SQL statement text when no library name is specified in   */
/*        the statement text.  The default is 10 space characters   */
/*                                                                  */
/*    cwbSV_ErrHandle  errorHandle - input                          */
/*        Any returned messages will be written to this object.     */
/*        If the parameter is set to zero, no messages will         */
/*        be retrievable.                                           */
/*                                                                  */
/* Return Codes                                                     */
/*    CWB_OK                                                        */
/*        Successful completion.                                    */
/*    CWB_INVALID_API_HANDLE                                        */
/*        Invalid connection handle.                                */
/*    CWBDB_INVALID_ARG_API                                         */
/*        libaryName = NULL                                         */
/*    CWBDB_STRING_ARG_TOO_LONG                                     */
/*        libraryName > 10                                          */
/*                                                                  */
/* Usage Notes                                                      */
/*    This API may be called any time after the connection handle   */
/*    has been created, but if it is called after the server is     */
/*    started for that connection handle then the                   */
/*    cwbDB_ApplyAttributes API must be called in order for the     */
/*    setting to take affect.                                       */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDB_SetDefaultSQLLibraryName(
                              cwbDB_ConnectionHandle  connection,
                              const char            *libraryName,
                              cwbSV_ErrHandle        errorHandle );
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDB_SetDefaultSQLLibraryNameA(
                              cwbDB_ConnectionHandle  connection,
                              LPCSTR                 libraryName,
                              cwbSV_ErrHandle        errorHandle);
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDB_SetDefaultSQLLibraryNameW(
                              cwbDB_ConnectionHandle  connection,
                              LPCWSTR                libraryName,
                              cwbSV_ErrHandle        errorHandle);
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define cwbDB_SetDefaultSQLLibraryName    cwbDB_SetDefaultSQLLibraryNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define cwbDB_SetDefaultSQLLibraryName    cwbDB_SetDefaultSQLLibraryNameA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetDescribeOption                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the describe option to determine what data is to be        */
/*   returned as a result of a describe.                            */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned short describeOption - input                          */
/*           Long integer specifying the type of data to be         */
/*           returned on a describe operation.                      */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWBDB_INVALID_ARG_API - Invalid describeOption value.          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use one of the defined values:                                 */
/*                    CWBDB_DESC_ALIAS_NAMES                        */
/*                    CWBDB_DESC_NAMES_ONLY                         */
/*                    CWBDB_DESC_LABELS                             */
/*                                                                  */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetDescribeOption(
                             cwbDB_RequestHandle  request,
                             unsigned short       describeOption,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetExtendedDataFormat                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   This API inicates to SQL if it should build extended data      */
/*   format information.                                            */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned short extendedFormatIndicator - input                 */
/*        Input value for extended format indicator.                */
/*                                                                  */
/*        This parameter should be one of the following values:     */
/*           CWBDB_USE_EXTENDED_FORMAT Indicates that extended      */
/*                                     data fromat will be used.    */
/*           CWBDB_USE_NORMAL_FORMAT   Indicates that normal data   */
/*                                     format will be used.         */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWBDB_INVALID_ARG_API - Invalid extendedFormat indicator value.*/
/*   CWBDB_SERVER_FUNCTION_NOT_AVAILABLE - The host server is not   */
/*                   at the required level to support this feature. */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This tells the host if it should build extended data format    */
/*   information. It can be included with any of the following      */
/*   flows or stored in the RPB.                                    */
/*     cwbDB_ExecuteImmediate                                       */
/*     cwbDB_Prepare                                                */
/*     cwbDB_PrepareDescribe                                        */
/*     cwbDB_PrepareDescribeOpenFetch                               */
/*   Note that the host must know at prepare time to build the      */
/*   extended information.  Also this call only tells the host      */
/*   to build the information.  A call to                           */
/*   cwbDB_ReturnExtendedDataFormat must be made before retrieving  */
/*   the information in order to actually get the extended info.    */
/*                                                                  */
/*   The default value is to not build extended information.        */
/*                                                                  */
/*   If the host server is not at the required level to support     */
/*   this feature, then this call will do nothing, the extended     */
/*   version of the data format will not be build, and a warning    */
/*   will be returned. Subsequent calls to get extended data will   */
/*   return default values.                                         */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetExtendedDataFormat(
                             cwbDB_RequestHandle  request,
                             unsigned short       extendedFormatIndicator,
                             cwbSV_ErrHandle      errorHandle);


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetFetchScrollOptions                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   After using the cwbDB_SetScrollableCursor, this API is used    */
/*   to indicate how to scroll through the data.                    */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned short scrollType - input                              */
/*           Indicates type of scrolling to be performed.           */
/*                                                                  */
/*   unsigned long relativeDistance - input                         */
/*           If the scrollType indicates scrolling relative to the  */
/*           current cursor position, this parameter indicates the  */
/*           relative distance.  For other scrollType values, this  */
/*           parameter is ignored.                                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWBDB_INVALID_ARG_API - Invalid scrollType value.              */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use one of the defined values:                                 */
/*                    CWBDB_SCROLL_NEXT                             */
/*                    CWBDB_SCROLL_PREVIOUS                         */
/*                    CWBDB_SCROLL_FIRST                            */
/*                    CWBDB_SCROLL_LAST                             */
/*                    CWBDB_SCROLL_BEFORE_FIRST                     */
/*                    CWBDB_SCROLL_AFTER_LAST                       */
/*                    CWBDB_SCROLL_CURRENT                          */
/*                    CWBDB_SCROLL_RELATIVE                         */
/*                    CWBDB_SCROLL_DIRECT                           */
/*                                                                  */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetFetchScrollOptions(
                             cwbDB_RequestHandle  request,
                             unsigned short       scrollType,
                             unsigned long        relativeDistance,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetFieldName                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the field name to be used in a catalog request.            */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   const char *fieldName - input                                  */
/*           Pointer to an ASCIIZ string containing the field       */
/*           name.                                                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API may be used prior to a cwbDB_Retrieve* API call for   */
/*   a catalog request.                                             */
/*                                                                  */
/*   This API is not valid for NDB or SQL requests.                 */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDB_SetFieldName(
                             cwbDB_RequestHandle  request,
                             const char          *fieldName,
                             cwbSV_ErrHandle      errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDB_SetFieldNameA(
                                cwbDB_RequestHandle  request,
                                LPCSTR               fieldName,
                                cwbSV_ErrHandle      errorHandle  );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDB_SetFieldNameW(
                                cwbDB_RequestHandle  request,
                                LPCWSTR              fieldName,
                                cwbSV_ErrHandle      errorHandle  );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDB_SetFieldName              cwbDB_SetFieldNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDB_SetFieldName              cwbDB_SetFieldNameA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetFileAttributes                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the file attributes to be used as a qualifier for a list   */
/*   request.                                                       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned short fileAttributes - input                          */
/*           Long integer that indicates attributes of files to be  */
/*           retrieved for a catalog request.                       */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API may be used prior to a cwbDB_Retrieve* API call.      */
/*                                                                  */
/*   Use one of the defined values:                                 */
/*                    CWBDB_ALL_FILES_ATTRIBUTES                    */
/*                    CWBDB_PHYSICAL_FILES_ATTRIBUTES               */
/*                    CWBDB_LOGICAL_FILES_ATTRIBUTES                */
/*                    CWBDB_ODBC_TABLES_ATTRIBUTES                  */
/*                    CWBDB_ODBC_VIEWS_ATTRIBUTES                   */
/*                                                                  */
/*   This API is not valid for NDB or SQL requests.                 */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetFileAttributes(
                             cwbDB_RequestHandle  request,
                             unsigned short       fileAttributes,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetFileInfoOrdering                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Changes the ordering of the data returned by catalog requests. */
/*                                                                  */
/* Parameters:                                                      */
/*     cwbDB_RequestHandle request - input                          */
/*                                                                  */
/*     unsigned long infoOrdering - input                           */
/*           Long integer that indicates how the returned           */
/*           onformation is to be ordered.                          */
/*                                                                  */
/*     cwbSV_ErrHandle errorHandle - input                          */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   CWB_OK   - no error occurred                                   */
/*   CWB_INVALID_API_HANDLE - invalid request handle                */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API may be used prior to a cwbDB_Retrieve* API call.      */
/*                                                                  */
/*   Use one of the defined values:                                 */
/*     CWBDB_DEFAULT_CATALOG_ORDERING    Use the default order      */
/*     CWBDB_ODBC_TABLE_ORDERING         Order by ODBC tables       */
/*     CWBDB_ODBC_TABLE_PRIVILEGE_ORDER  Order by  ODBC privilege   */
/*                                                                  */
/*   This API is not valid for NDB or SQL requests.                 */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetFileInfoOrdering(
                             cwbDB_RequestHandle  request,
                             unsigned short       fileInfoOrder,
                             cwbSV_ErrHandle      errorHandle   );

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetFileName                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the file name to be used as a qualifier for a list         */
/*   request.  This is the short file name (system name).           */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   const char *fileName - input                                   */
/*           Pointer to an ASCIIZ string containing the file        */
/*           name.                                                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API may be used prior to a cwbDB_Retrieve* API call.      */
/*                                                                  */
/*   This API is not valid for SQL requests.                        */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDB_SetFileName(
                             cwbDB_RequestHandle  request,
                             const char          *fileName,
                             cwbSV_ErrHandle      errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDB_SetFileNameA(
                                 cwbDB_RequestHandle  request,
                                 LPCSTR               fileName,
                                 cwbSV_ErrHandle      errorHandle );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDB_SetFileNameW(
                                 cwbDB_RequestHandle  request,
                                 LPCWSTR              fileName,
                                 cwbSV_ErrHandle      errorHandle );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDB_SetFileName               cwbDB_SetFileNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDB_SetFileName               cwbDB_SetFileNameA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetFileText                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the text description for a file that will be created       */
/*   through the API.                                               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   const char *fileText - input                                   */
/*           Pointer to an ASCIIZ string that contains the text     */
/*           description to be used when creating a file.           */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for List or SQL requests.                */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDB_SetFileText(
                             cwbDB_RequestHandle  request,
                             const char          *fileText,
                             cwbSV_ErrHandle      errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDB_SetFileTextA(
                                 cwbDB_RequestHandle  request,
                                 LPCSTR               fileText,
                                 cwbSV_ErrHandle      errorHandle );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDB_SetFileTextW(
                                 cwbDB_RequestHandle  request,
                                 LPCWSTR              fileText,
                                 cwbSV_ErrHandle      errorHandle );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDB_SetFileText               cwbDB_SetFileTextW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDB_SetFileText               cwbDB_SetFileTextA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetFileType                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the file type to be used as a qualifier for a list         */
/*   request.                                                       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned short fileAttribute - input                           */
/*           Long integer that indicates type of files to be        */
/*           retrieved for a catalog request.                       */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API may be used prior to a cwbDB_Retrieve* API call.      */
/*                                                                  */
/*   Use one of the defined values:                                 */
/*                    CWBDB_ALL_FILES                               */
/*                    CWBDB_SOURCE_FILES                            */
/*                    CWBDB_DATA_FILES                              */
/*                                                                  */
/*   This API is not valid for NDB or SQL requests.                 */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetFileType(
                             cwbDB_RequestHandle  request,
                             unsigned short       fileType,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetForeignKeyFileName                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the foreign key file name to be used in a request.         */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   const char *fileName - input                                   */
/*           Pointer to an ASCIIZ string containing the foreign     */
/*           key file name.                                         */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API may be used prior to a cwbDB_Retrieve* API call for   */
/*   a catalog request.                                             */
/*                                                                  */
/*   This API is not valid for NDB or SQL requests.                 */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDB_SetForeignKeyFileName(
                             cwbDB_RequestHandle  request,
                             const char          *fileName,
                             cwbSV_ErrHandle      errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDB_SetForeignKeyFileNameA(
                                 cwbDB_RequestHandle  request,
                                 LPCSTR               fileName,
                                 cwbSV_ErrHandle      errorHandle  );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDB_SetForeignKeyFileNameW(
                                 cwbDB_RequestHandle  request,
                                 LPCWSTR              fileName,
                                 cwbSV_ErrHandle      errorHandle  );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDB_SetForeignKeyFileName     cwbDB_SetForeignKeyFileNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDB_SetForeignKeyFileName     cwbDB_SetForeignKeyFileNameA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetForeignKeyLibName                                     */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the foreign key library name to be used in a request.      */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   const char *libName - input                                    */
/*           Pointer to an ASCIIZ string containing the foreign     */
/*           key library name.                                      */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API may be used prior to a cwbDB_Retrieve* API call for   */
/*   a catalog request.                                             */
/*                                                                  */
/*   This API is not valid for NDB or SQL requests.                 */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDB_SetForeignKeyLibName(
                             cwbDB_RequestHandle  request,
                             const char          *libName,
                             cwbSV_ErrHandle      errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDB_SetForeignKeyLibNameA(
                                 cwbDB_RequestHandle  request,
                                 LPCSTR               libName,
                                 cwbSV_ErrHandle      errorHandle  );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDB_SetForeignKeyLibNameW(
                                 cwbDB_RequestHandle  request,
                                 LPCWSTR              libName,
                                 cwbSV_ErrHandle      errorHandle );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDB_SetForeignKeyLibName      cwbDB_SetForeignKeyLibNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDB_SetForeignKeyLibName      cwbDB_SetForeignKeyLibNameA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetFormatName                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the record format name to be used in a request.            */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   const char *formatName - input                                 */
/*           Pointer to an ASCIIZ string containing the record      */
/*           format name.                                           */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API may be used prior to a cwbDB_Retrieve* API call for   */
/*   a catalog request.                                             */
/*                                                                  */
/*   This API is not valid for NDB or SQL requests.                 */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDB_SetFormatName(
                             cwbDB_RequestHandle  request,
                             const char          *formatName,
                             cwbSV_ErrHandle      errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDB_SetFormatNameA(
                                 cwbDB_RequestHandle  request,
                                 LPCSTR               formatName,
                                 cwbSV_ErrHandle      errorHandle );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDB_SetFormatNameW(
                                 cwbDB_RequestHandle  request,
                                 LPCWSTR              formatName,
                                 cwbSV_ErrHandle      errorHandle  );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDB_SetFormatName             cwbDB_SetFormatNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDB_SetFormatName             cwbDB_SetFormatNameA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetHoldIndicator                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   This API instructs SQL how to treat active statements (open    */
/*   cursors and prepared dynamic SQL statements) when a commit or  */
/*   rollback operation is performed.  CWBDB_HOLD indicates that    */
/*   open cursors and prepared dynamic SQL statements will be       */
/*   preserved.  CWBDB_WORK will cause open cursors to be closed    */
/*   and prepared dynamic SQL statement to be destroyed.            */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned short holdIndicator - input                           */
/*           Input value for hold indicator.                        */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWBDB_INVALID_ARG_API - Invalid holdIndicator value.           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use one of the defined values:                                 */
/*                    CWBDB_WORK                                    */
/*                    CWBDB_HOLD                                    */
/*                                                                  */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetHoldIndicator(
                             cwbDB_RequestHandle  request,
                             unsigned short       holdIndicator,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetIgnoreDecimalDataError                                */
/*                                                                  */
/* Purpose:                                                         */
/*   Set an indicator that says whether to ignore or correct        */
/*   zoned decimal data errors.                                     */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*       Handle to connection to AS/400 database access server      */
/*                                                                  */
/*   unsigned short ignoreDecimalError - input                      */
/*       Indicates how decimal data errors will be treated.         */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use one of the defined values:                                 */
/*                    CWBDB_IGNORE_ERROR                            */
/*                    CWBDB_CORRECT_ERROR                           */
/*                                                                  */
/*                                                                  */
/*   The cwbDB_ApplyAttributes API must be called after             */
/*   cwbDB_SetIgnoreDecimalDataError in order for the new value to  */
/*   take affect.                                                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetIgnoreDecimalDataError(
                             cwbDB_ConnectionHandle  connection,
                             unsigned short          ignoreDecimalError,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetIndexType                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the type of index criteria to be used in a catalog request.*/
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned short indexType - input                               */
/*           Long integer that indicates index rule to be           */
/*           retrieved for a catalog request.                       */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API may be used prior to a cwbDB_Retrieve* API call for   */
/*   a catalog request.                                             */
/*                                                                  */
/*   Use one of the defined values:                                 */
/*                    CWBDB_UNIQUE_INDEX                            */
/*                    CWBDB_DUPLICATE_INDEX                         */
/*                    CWBDB_DUP_NULL_INDEX                          */
/*                                                                  */
/*   This API is not valid for NDB or SQL requests.                 */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetIndexType(
                             cwbDB_RequestHandle  request,
                             unsigned short       indexType,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetLibraryName                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the library name to be used for the current database       */
/*   request.                                                       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   const char *libraryName  - input                               */
/*           Pointer to an ASCIIZ string containing the library     */
/*           name.                                                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   For SQL requests, this is the library that is used             */
/*   when locating an SQL package to be used for stored statements. */
/*   For List and Native Database requests, this is the library     */
/*   containing objects to be operated on.                          */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDB_SetLibraryName(
                             cwbDB_RequestHandle  request,
                             const char          *libraryName,
                             cwbSV_ErrHandle      errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDB_SetLibraryNameA(
                                 cwbDB_RequestHandle  request,
                                 LPCSTR               libraryName,
                                 cwbSV_ErrHandle      errorHandle  );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDB_SetLibraryNameW(
                                 cwbDB_RequestHandle  request,
                                 LPCWSTR              libraryName,
                                 cwbSV_ErrHandle      errorHandle  );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDB_SetLibraryName            cwbDB_SetLibraryNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDB_SetLibraryName            cwbDB_SetLibraryNameA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetLOBFieldThreshold                                     */
/*                                                                  */
/* Purpose:                                                         */
/*   Sets server attribute for the connection to indicate the       */
/*   threshold length for LOB fields.                               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*       Handle to connection to AS/400 database access server      */
/*                                                                  */
/*   unsigned long  thresholdSize - input                           */
/*       Threshold where all FETCH result sets which contain a LOB  */
/*       field with a length which is less than or equal to the     */
/*       threshold length will be have the LOB data for the field   */
/*       returned in-line as part of the row data. If a LOB field   */
/*       in a result set has a length which is greater than the     */
/*       threshold, a LOB handle will be returned to the client on  */
/*       the FETCH request.  Default is zero.                       */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API may be called any time after the connection handle    */
/*   has been created and must be called before the server is       */
/*   started.  This attribute cannot be changed after the server    */
/*   is started. The default value is zero.                         */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetLOBFieldThreshold(
                            cwbDB_ConnectionHandle  connection,
                            unsigned long           thresholdSize,
                            cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetLongFileName                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the long file name to be used as a qualifier for a list    */
/*   request.                                                       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   const char *longFileName - input                               */
/*         Pointer to an ASCIIZ string containing the long file     */
/*         name.                                                    */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API may be used prior to a cwbDB_Retrieve* API call.      */
/*                                                                  */
/*   This API is not valid for NDB or SQL requests.                 */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDB_SetLongFileName(
                             cwbDB_RequestHandle  request,
                             const char          *longFileName,
                             cwbSV_ErrHandle      errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDB_SetLongFileNameA(
                                 cwbDB_RequestHandle  request,
                                 LPCSTR               longFileName,
                                 cwbSV_ErrHandle      errorHandle  );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDB_SetLongFileNameW(
                                 cwbDB_RequestHandle  request,
                                 LPCWSTR              longFileName,
                                 cwbSV_ErrHandle      errorHandle   );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDB_SetLongFileName           cwbDB_SetLongFileNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDB_SetLongFileName           cwbDB_SetLongFileNameA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetMaximumMembers                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the maximum number of members for creating a file          */
/*   through the API.                                               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   signed short maxMembers - input                                */
/*           Input value for maximum number of members.             */
/*           A value of -1 for this parameter indicates no maximum. */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for List or SQL requests.                */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetMaximumMembers(
                             cwbDB_RequestHandle  request,
                             signed short         maxMembers,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetMemberName                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the member name to be used in a request.                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   const char *memberName - input                                 */
/*           Pointer to an ASCIIZ string containing the member      */
/*           name.                                                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API may be used prior to a cwbDB_Retrieve* API call for   */
/*   a catalog request.                                             */
/*   This API is also used for NDB requests when operating on a     */
/*   database file member.                                          */
/*                                                                  */
/*   This API is not valid for SQL requests.                        */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDB_SetMemberName(
                             cwbDB_RequestHandle  request,
                             const char          *memberName,
                             cwbSV_ErrHandle      errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDB_SetMemberNameA(
                                 cwbDB_RequestHandle  request,
                                 LPCSTR               memberName,
                                 cwbSV_ErrHandle      errorHandle  );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDB_SetMemberNameW(
                                 cwbDB_RequestHandle  request,
                                 LPCWSTR              memberName,
                                 cwbSV_ErrHandle      errorHandle  );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDB_SetMemberName             cwbDB_SetMemberNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDB_SetMemberName             cwbDB_SetMemberNameA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetMemberText                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the text description for a member at will be added         */
/*   through the API.                                               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   const char *memberText - input                                 */
/*           Pointer to an ASCIIZ string that contains the text     */
/*           description to be used when adding a member.           */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for List or SQL requests.                */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDB_SetMemberText(
                             cwbDB_RequestHandle  request,
                             const char          *memberText,
                             cwbSV_ErrHandle      errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDB_SetMemberTextA(
                                 cwbDB_RequestHandle  request,
                                 LPCSTR               memberText,
                                 cwbSV_ErrHandle      errorHandle);
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDB_SetMemberTextW(
                                 cwbDB_RequestHandle  request,
                                 LPCWSTR              memberText,
                                 cwbSV_ErrHandle      errorHandle);
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDB_SetMemberText             cwbDB_SetMemberTextW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDB_SetMemberText             cwbDB_SetMemberTextA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetNamingConvention                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the naming convention (SQL or native AS/400) to be used by */
/*   the database access server.                                    */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*       Handle to connection to AS/400 database access server      */
/*                                                                  */
/*   unsigned short newNamingConvention - input                     */
/*       Indicates the type of naming convention to use.  SQL       */
/*       naming convention (library.table) or AS/400 native naming  */
/*       convention (library/table).                                */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*   CWBDB_INVALID_ARG_API - Invalid naming convention value.       */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use one of the defined values:                                 */
/*                    CWBDB_PERIOD_NAME_CONV                        */
/*                    CWBDB_SLASH_NAME_CONV                         */
/*                                                                  */
/*   The cwbDB_ApplyAttributes API must be called after             */
/*   cwbDB_SetNamingConvention in order for the new naming          */
/*   convention to take affect.                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetNamingConvention(
                             cwbDB_ConnectionHandle  connection,
                             unsigned short          newNamingConvention,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetNLSS                                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   Sets the National Language Sort Sequence (NLSS) attribute of   */
/*   the Data Access server.                                        */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle - input                                 */
/*       Connection through which the attribute is to be set        */
/*                                                                  */
/*   unsigned short NLSSTypeID - input                              */
/*       The type of NLSS attribute.  Possible values:              */
/*                                                                  */
/*          CWBDB_NLSS_SORT_HEX                                     */
/*          CWBDB_NLSS_SORT_SHARED                                  */
/*          CWBDB_NLSS_SORT_UNIQUE                                  */
/*          CWBDB_NLSS_SORT_USER                                    */
/*                                                                  */
/*   const char *tableOrLangID - input                              */
/*       Depends on value of the NLSSType parameter (above).        */
/*         CWBDB_NLSS_SORT_HEX:  This parameter is not used.        */
/*                                                                  */
/*         CWBDB_NLSS_SORT_SHARED or CWBDB_NLSS_SORT_UNIQUE:        */
/*         This parameter represents the language feature code      */
/*         attribute ID for the server. It is a required parameter. */
/*                                                                  */
/*         Examples of language feature code values:                */
/*         AFR Afrikaans                  CSY Czech                 */
/*         SQI Albanian                   DAN Danish                */
/*         ARA Arabic                     NLD Dutch                 */
/*         NLB Belgian Dutch              ENA English Australian    */
/*         FRB Belgian French             ENP English Upper Case    */
/*         PTB Brazilian Portuguese       FAR Farsi                 */
/*         BGR Bulgarian                  FIN Finnish               */
/*         BEL Byelorussian               FRA French                */
/*         FRC Canadian French            DEU German                */
/*         CAT Catalan                    ELL Greek                 */
/*         HRV Croatian                   HEB Hebrew                */
/*         GAE Irish Gaelic               HUN Hungarian             */
/*         ITA Italian                    ISL Icelandic             */
/*         JPN Japanese Katakana          SRL Serbian Latin         */
/*         KOR Korean                     CHS Simplified Chinese    */
/*         MKD Macedonian                 SKY Slovakian             */
/*         NOR Norwegian - Bokmal         SLO Slovenian             */
/*         NON Norwegian - Nynorsk        ESP Spanish               */
/*         PLK Polish                     SVE Swedish               */
/*         PTG Portuguese                 FRS Swiss French          */
/*         RMS Rhaeto-Romanic             DES Swiss German          */
/*         ROM Romanian                   ITS Swiss Italian         */
/*         RUS Russian                    THA Thai                  */
/*         SRB Serbian Cyrillic           CHT Traditional Chinese   */
/*         ENU US English                 TRK Turkish               */
/*         ENG UK English                                           */
/*                                                                  */
/*                                                                  */
/*         CWBDB_NLSS_SORT_USER: This parameter represents the NLSS */
/*         table name attribute.  It is a required parameter.       */
/*                                                                  */
/*   const char *library - input                                    */
/*       Depends on value of the NLSSType parameter (above).        */
/*         CWBDB_NLSS_SORT_HEX:  This parameter is not used.        */
/*                                                                  */
/*         CWBDB_NLSS_SORT_SHARED or CWBDB_NLSS_SORT_UNIQUE:        */
/*         This parameter is not used                               */
/*                                                                  */
/*         CWBDB_NLSS_SORT_USER: This parameter represents the NLSS */
/*         library name attribute.  It is an optional parameter.    */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid connection handle.            */
/*   CWBDB_INVALID_ARG_API - Invalid type, language ID, or table.   */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/*   The cwbDB_ApplyAttributes API must be called after             */
/*   cwbDB_SetNLSS in order for the new sort sequence to take       */
/*   affect.                                                        */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDB_SetNLSS(
                             cwbDB_ConnectionHandle  connection,
                             unsigned short          NLSSTypeID,
                             const char             *tableOrLangID,
                             const char             *library,
                             cwbSV_ErrHandle         errorHandle );
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDB_SetNLSSA(
                                 cwbDB_ConnectionHandle  connection,
                                 USHORT                  NLSSTypeID,
                                 LPCSTR                  tableOrLangID,
                                 LPCSTR                  library,
                                 cwbSV_ErrHandle         errorHandle);
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDB_SetNLSSW(
                                 cwbDB_ConnectionHandle  connection,
                                 USHORT                  NLSSTypeID,
                                 LPCWSTR                 tableOrLangID,
                                 LPCWSTR                 library,
                                 cwbSV_ErrHandle         errorHandle);
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDB_SetNLSS                   cwbDB_SetNLSSW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDB_SetNLSS                   cwbDB_SetNLSSA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetNullable                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the nullable indicator for a special column.               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned short nullableInd - input                             */
/*           Integer that indicates whether special                 */
/*           column is null capable.                                */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API may be used prior to a cwbDB_Retrieve* API call.      */
/*                                                                  */
/*   Use one of the defined values:                                 */
/*                    CWBDB_NOT_NULLABLE                            */
/*                    CWBDB_NULLABLE                                */
/*                                                                  */
/*   This API is not valid for NDB or SQL requests.                 */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetNullable(
                             cwbDB_RequestHandle  request,
                             unsigned short       nullableInd,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetOverrideInformation                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the overriding library, file, and member for an override   */
/*   database operation.                                            */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   const char *overrideLibraryName - input                        */
/*           Pointer to an ASCIIZ string that contains the          */
/*           overriding library name.                               */
/*                                                                  */
/*   const char *baseFileName - input                               */
/*           Pointer to an ASCIIZ string that contains the          */
/*           overriding file name.                                  */
/*                                                                  */
/*   const char *overrideMemberName - input                         */
/*           Pointer to an ASCIIZ string that contains the          */
/*           overriding member name.                                */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is used in preparation for cwbDB_OverrideFile.        */
/*                                                                  */
/*   This API is not valid for List or SQL requests.                */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDB_SetOverrideInformation(
                             cwbDB_RequestHandle  request,
                             const char          *overrideLibraryName,
                             const char          *overrideFileName,
                             const char          *overrideMemberName,
                             cwbSV_ErrHandle      errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDB_SetOverrideInformationA(
                                 cwbDB_RequestHandle  request,
                                 LPCSTR               overrideLibraryName,
                                 LPCSTR               overrideFileName,
                                 LPCSTR               overrideMemberName,
                                 cwbSV_ErrHandle      errorHandle);
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDB_SetOverrideInformationW(
                                 cwbDB_RequestHandle  request,
                                 LPCWSTR              overrideLibraryName,
                                 LPCWSTR              overrideFileName,
                                 LPCWSTR              overrideMemberName,
                                 cwbSV_ErrHandle      errorHandle);
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDB_SetOverrideInformation    cwbDB_SetOverrideInformationW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDB_SetOverrideInformation    cwbDB_SetOverrideInformationA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetPackageName                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the SQL package name for a database request.               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   const char *packageName - input                                */
/*           Pointer to an ASCIIZ string containing the SQL package */
/*           name.                                                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   For catalog requests, this API is used prior to                */
/*   cwbDB_RetrievePackageInformation or                            */
/*   cwbDB_RetrievePackageStatementInformation.                     */
/*   For SQL requests, this API is used to set the name of the SQL  */
/*   package to be used for preparing or executing SQL statements.  */
/*   This is optional for SQL requests.                             */
/*                                                                  */
/*   This API is not valid for NDB requests.                        */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDB_SetPackageName(
                             cwbDB_RequestHandle  request,
                             const char          *packageName,
                             cwbSV_ErrHandle      errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDB_SetPackageNameA(
                                 cwbDB_RequestHandle  request,
                                 LPCSTR               packageName,
                                 cwbSV_ErrHandle      errorHandle );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDB_SetPackageNameW(
                                 cwbDB_RequestHandle  request,
                                 LPCWSTR              packageName,
                                 cwbSV_ErrHandle      errorHandle );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDB_SetPackageName            cwbDB_SetPackageNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDB_SetPackageName            cwbDB_SetPackageNameA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetParameterMarkerBlock                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   Provides the data to be used for the parameter markers         */
/*   contained in a prepared statement for a block of rows.         */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned long numberOfRows - input                             */
/*           Number of sets of parameter marker data that is in the */
/*           dataBuffer.                                            */
/*                                                                  */
/*   cwbDB_FormatHandle format - input                              */
/*           Handle to the format of the data being provided.       */
/*                                                                  */
/*   void *dataBuffer - input                                       */
/*           Pointer to a buffer containing the data to be used     */
/*           for the parameter markers.                             */
/*                                                                  */
/*   signed short *indicators - input                               */
/*           Pointer to a buffer containing the null indicators.    */
/*           If the value of the indicator is less than zero,       */
/*           the value for the corresponding parameter marker is    */
/*           null.                                                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetParameterMarkerBlock(
                             cwbDB_RequestHandle  request,
                             unsigned long        numberOfRows,
                             cwbDB_FormatHandle   format,
                             void                *dataPointer,
                             signed short        *indicators,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetParameterMarkers                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Provides the data to be used for the parameter markers         */
/*   contained in a prepared statement.                             */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbDB_FormatHandle *format - input                             */
/*           Handle to the format of the data being provided.       */
/*                                                                  */
/*   void *dataBuffer - input                                       */
/*           Pointer to a buffer containing the data to be used     */
/*           for the parameter markers.                             */
/*                                                                  */
/*   signed short *indicators - input                               */
/*           Pointer to a buffer containing the null indicators.    */
/*           If the value of the indicator is less than zero,       */
/*           the value for the corresponding parameter marker is    */
/*           null.                                                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetParameterMarkers(
                             cwbDB_RequestHandle  request,
                             cwbDB_FormatHandle   format,
                             void                *dataBuffer,
                             signed short        *indicators,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetPatternMatching                                       */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the pattern matching characteristics for the specified     */
/*   object type.  Pattern matching controls if characters such     */
/*   as _ (underscore) are treated as "wildcard" characters or not. */
/*                                                                  */
/* Parameters:                                                      */
/*     cwbDB_RequestHandle request - input                          */
/*                                                                  */
/*     unsigned short objectType - input                            */
/*           The type of object you want to set the pattern         */
/*           matching characteristic of.                            */
/*                                                                  */
/*           Possible values:                                       */
/*              CWBDB_PATTERNMATCH_LIB    - Library                 */
/*              CWBDB_PATTERNMATCH_FILE   - File                    */
/*              CWBDB_PATTERNMATCH_MBR    - Member                  */
/*              CWBDB_PATTERNMATCH_FIELD  - Field                   */
/*              CWBDB_PATTERNMATCH_FORMAT - Format                  */
/*              CWBDB_PATTERNMATCH_RDB    - RDB                     */
/*              CWBDB_PATTERNMATCH_SQLPKG - SQL package             */
/*                                                                  */
/*     cwb_Boolean patternMatch - input                             */
/*           Set to true to perform pattern matching, set to false  */
/*           to not perform pattern matching.                       */
/*                                                                  */
/*     cwbSV_ErrHandle errorHandle - input                          */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   CWB_OK   - no error occurred                                   */
/*   CWB_INVALID_API_HANDLE - invalid request handle                */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for SQL or NDB requests.  It is only     */
/*   valid for Catalog requests.                                    */
/*                                                                  */
/*   This API would normally be called before calling an API        */
/*   such as cwbDB_SetLibraryName, and would control if pattern     */
/*   matching would be performed if the library name contained a    */
/*   "wildcard" type of character.                                  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetPatternMatching(
                             cwbDB_RequestHandle request,
                             unsigned short      objectType,
                             cwb_Boolean         patternMatch,
                             cwbSV_ErrHandle     errorHandle  );

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetPrepareOption                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the option for doing a normal or enhanced prepare.         */
/*   Doing an enhanced prepare will search the specified SQL        */
/*   package for the given statement.  If it is found, the          */
/*   statement will be used.  If not, the statement will be         */
/*   prepared.                                                      */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned short prepareOption - input                           */
/*           Long integer specifying the type of prepare to be      */
/*           performed.                                             */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWBDB_INVALID_ARG_API - Invalid prepareOption value.           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use one of the defined values:                                 */
/*                    CWBDB_NORMAL_PREPARE                          */
/*                    CWBDB_ENHANCED_PREPARE                        */
/*                                                                  */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetPrepareOption(
                             cwbDB_RequestHandle  request,
                             unsigned short       prepareOption,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetPrimaryKeyFileName                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the primary key file name to be used in a request.         */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   const char *fileName - input                                   */
/*           Pointer to an ASCIIZ string containing the primary     */
/*           key file name.                                         */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API may be used prior to a cwbDB_Retrieve* API call for   */
/*   a catalog request.                                             */
/*                                                                  */
/*   This API is not valid for NDB or SQL requests.                 */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDB_SetPrimaryKeyFileName(
                             cwbDB_RequestHandle  request,
                             const char          *fileName,
                             cwbSV_ErrHandle      errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDB_SetPrimaryKeyFileNameA(
                                 cwbDB_RequestHandle  request,
                                 LPCSTR               fileName,
                                 cwbSV_ErrHandle      errorHandle );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDB_SetPrimaryKeyFileNameW(
                                 cwbDB_RequestHandle  request,
                                 LPCWSTR              fileName,
                                 cwbSV_ErrHandle      errorHandle );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDB_SetPrimaryKeyFileName     cwbDB_SetPrimaryKeyFileNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDB_SetPrimaryKeyFileName     cwbDB_SetPrimaryKeyFileNameA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetPrimaryKeyLibName                                     */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the primary key library name to be used in a request.      */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   const char *libName - input                                    */
/*           Pointer to an ASCIIZ string containing the primary     */
/*           key library name.                                      */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API may be used prior to a cwbDB_Retrieve* API call for   */
/*   a catalog request.                                             */
/*                                                                  */
/*   This API is not valid for NDB or SQL requests.                 */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDB_SetPrimaryKeyLibName(
                             cwbDB_RequestHandle  request,
                             const char          *libName,
                             cwbSV_ErrHandle      errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDB_SetPrimaryKeyLibNameA(
                                 cwbDB_RequestHandle  request,
                                 LPCSTR               libName,
                                 cwbSV_ErrHandle      errorHandle );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDB_SetPrimaryKeyLibNameW(
                                 cwbDB_RequestHandle  request,
                                 LPCWSTR              libName,
                                 cwbSV_ErrHandle      errorHandle);
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDB_SetPrimaryKeyLibName      cwbDB_SetPrimaryKeyLibNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDB_SetPrimaryKeyLibName      cwbDB_SetPrimaryKeyLibNameA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetQueryTimeoutValue                                     */
/*                                                                  */
/* Purpose                                                          */
/*   Sets the query timeout value contained in the RPB.             */
/*                                                                  */
/* Syntax                                                           */
/*    unsigned int CWB_ENTRY cwbDB_SetQueryTimeoutValue(            */
/*        cwbDB_RequestHandle    request,                           */
/*        long                   timeout,                           */
/*        cwbSV_ErrHandle        errorHandle);                      */
/*                                                                  */
/* Parameters                                                       */
/*    cwbDB_RequestHandle  request - input                          */
/*      Handle to a request object.  This api is only valid for     */
/*      an sql request.                                             */
/*                                                                  */
/*    long   timeout - input                                        */
/*      The timeout value greater than zero.  The special value -1  */
/*      indicates a value of *NOMAX.                                */
/*                                                                  */
/*    cwbSV_ErrHandle  errorHandle - input                          */
/*      Any returned messages will be written to this object.  If   */
/*      the parameter is set to zero, no messages will be           */
/*      retrievable.                                                */
/*                                                                  */
/* Return Codes                                                     */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle (must be SQL   */
/*                            request).                             */
/*   CWBDB_PARAMETER_ERROR - timeout not greater than zero or -1    */
/*                                                                  */
/* Usage Notes                                                      */
/*    The cwbDB_StoreRequestParameters API must be called in order  */
/*    for the setting to take affect.                               */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetQueryTimeoutValue(
                             cwbDB_RequestHandle  request,
                             long                 timeout,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetRDBName                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the Relational Database (RDB) name for a catalog request.  */
/*   This is the RDB for which information is being requested.      */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   const char *RDBName - input                                    */
/*           Pointer to an ASCIIZ string containing the RDB name.   */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is used prior to cwbDB_RetrieveDBInformation.         */
/*   This API is not valid for SQL or NDB requests.                 */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDB_SetRDBName(
                             cwbDB_RequestHandle  request,
                             const char          *RDBName,
                             cwbSV_ErrHandle      errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDB_SetRDBNameA(
                                 cwbDB_RequestHandle  request,
                                 LPCSTR               RDBName,
                                 cwbSV_ErrHandle      errorHandle);
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDB_SetRDBNameW(
                                 cwbDB_RequestHandle  request,
                                 LPCWSTR              RDBName,
                                 cwbSV_ErrHandle      errorHandle );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDB_SetRDBName                cwbDB_SetRDBNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDB_SetRDBName                cwbDB_SetRDBNameA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetRecordLength                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the record length in preparation for creating a file       */
/*   through the API.                                               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned long recordLength - input                             */
/*           Length of records to be contained in the file to be    */
/*           created.                                               */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for List or SQL requests.                */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetRecordLength(
                             cwbDB_RequestHandle  request,
                             unsigned long        recordLength,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetRelationalDBName                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the current relational database name.                      */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle  connection - input                     */
/*           Handle to a request object.                            */
/*                                                                  */
/*   const char *relationalDBName - input                           */
/*           Pointer to an 18 character string containing the       */
/*           relational database name. A special value of *SYSBAS   */
/*           indicates that a connection should be made to  *SYSBAS */
/*           RDB.  This value should be used if a connection to the */
/*           system ASP (SYSBAS) RDB is desired.                    */
/*         Note: This name should be blank padded to 18 characters. */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid connection handle.            */
/*   CWBDB_FUNCTION_NOT_VALID_AFTER_CONNECT - cannot change IASP    */
/*                                            after connected.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/* If a call to cwbDB_SetRelationalDBName has not been made then    */
/* the default database is used.                                    */
/* The RDB can only be set before connecting to the system.         */
/* This call is used to switch to a specific IASP while connecting  */
/* the system.                                                      */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDB_SetRelationalDBName(
                             cwbDB_ConnectionHandle  connection,
                             const char          *relationalDBName,
                             cwbSV_ErrHandle      errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDB_SetRelationalDBNameA(
                                 cwbDB_ConnectionHandle  connection,
                                 LPCSTR               relationalDBName,
                                 cwbSV_ErrHandle      errorHandle  );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDB_SetRelationalDBNameW(
                                 cwbDB_ConnectionHandle  connection,
                                 LPCWSTR              relationalDBName,
                                 cwbSV_ErrHandle      errorHandle  );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDB_SetRelationalDBName             cwbDB_SetRelationalDBNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDB_SetRelationalDBName             cwbDB_SetRelationalDBNameA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetScrollableCursor                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Indicate whether the cursor used by this request is scrollable */
/*   or not.                                                        */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned short scrollIndicator - input                         */
/*           Input value for scroll indicator.                      */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWBDB_INVALID_ARG_API - Invalid scrollIndicator value.         */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use one of the defined values:                                 */
/*                    CWBDB_CURSOR_NOT_SCROLLABLE                   */
/*                    CWBDB_CURSOR_SCROLLABLE                       */
/*                    CWBDB_CURSOR_STATIC_SCROLLABLE                */
/*                                                                  */
/*Starting with the v5r2 host six cursor types are defined.         */
/*They are listed below.  The first three are just alternate names  */
/*for the three above.                                              */
/*If the host version is previous to v5r2 then the last 3, which    */
/*would be invalid, are mapped to a valid value as listed below:    */
/* ScrollableSensitive      ->  ScrollableAsensitive                */
/* NonScrollableSensitive   ->  NonScrollableAsensitive             */
/* NonScrollableInsensitive ->  NonScrollableAsensitive             */
/*                                                                  */
/*                    CWBDB_CURSOR_NOT_SCROLLABLE_ASENSITIVE        */
/*                    CWBDB_CURSOR_SCROLLABLE_ASENSITIVE            */
/*                    CWBDB_CURSOR_STATIC_SCROLLABLE_INSENSITIVE    */
/*                    CWBDB_CURSOR_SCROLLABLE_SENSITIVE             */
/*                    CWBDB_CURSOR_NOT_SCROLLABLE_SENSITIVE         */
/*                    CWBDB_CURSOR_NOT_SCROLLABLE_INSENSITIVE       */
/*                                                                  */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetScrollableCursor(
                             cwbDB_RequestHandle  request,
                             unsigned short       scrollIndicator,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetStatementName                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the statement name to be used for this request.            */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   const char *statementName - input                              */
/*           Pointer to an ASCIIZ string containing the statement   */
/*           name being used for a SQL request.                     */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDB_SetStatementName(
                             cwbDB_RequestHandle  request,
                             const char          *statementName,
                             cwbSV_ErrHandle      errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDB_SetStatementNameA(
                                 cwbDB_RequestHandle  request,
                                 LPCSTR               statementName,
                                 cwbSV_ErrHandle      errorHandle );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDB_SetStatementNameW(
                                 cwbDB_RequestHandle  request,
                                 LPCWSTR              statementName,
                                 cwbSV_ErrHandle      errorHandle );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDB_SetStatementName          cwbDB_SetStatementNameW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDB_SetStatementName          cwbDB_SetStatementNameA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetStatementText                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the statement text to be used for this request.            */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   const char *statementText - input                              */
/*           Pointer to an ASCIIZ string containing the statement   */
/*           text being used for a SQL request.                     */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for NDB or catalog requests.             */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbDB_SetStatementText(
                             cwbDB_RequestHandle  request,
                             const char          *statementText,
                             cwbSV_ErrHandle      errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbDB_SetStatementTextA(
                                 cwbDB_RequestHandle  request,
                                 LPCSTR               statementText,
                                 cwbSV_ErrHandle      errorHandle  );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbDB_SetStatementTextW(
                                 cwbDB_RequestHandle  request,
                                 LPCWSTR              statementText,
                                 cwbSV_ErrHandle      errorHandle  );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbDB_SetStatementText          cwbDB_SetStatementTextW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbDB_SetStatementText          cwbDB_SetStatementTextA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetStatementType                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the type of SQL statement for which information is being   */
/*   requested .                                                    */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned short statementType - input                           */
/*           Long integer that indicates type of SQL statement      */
/*           being used for a catalog request.                      */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API may be used prior to making a                         */
/*   cwbDB_RetrieveSQLPackageStatement API call.                    */
/*                                                                  */
/*   Use one of the defined values:                                 */
/*                    CWBDB_ALL_STATEMENTS                          */
/*                    CWBDB_DECLARE_STATEMENTS                      */
/*                    CWBDB_SELECT_STATEMENTS                       */
/*                    CWBDB_EXEC_STATEMENTS                         */
/*                                                                  */
/*   This API is not valid for NDB or SQL requests.                 */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetStatementType(
                             cwbDB_RequestHandle  request,
                             unsigned short       statementType,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetStaticCursorResultSetThreshold                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Sets threshold for static cursor result set size.              */
/*                                                                  */
/* Parameters:                                                      */
/*    cwbDB_RequestHandle  request - input                          */
/*      Handle to a request object.  This api is only valid for     */
/*      an sql request.                                             */
/*                                                                  */
/*   unsigned long  thresholdSize - input                           */
/*       Threshold that limits the number of records in a temporary */
/*       record set of a static cursor.  Valid range is             */
/*       1 -  2147483647 (2GB- 1)). Default value is 2147483647."   */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes                                                      */
/*   This API is not valid for NDB or catalog requests.             */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetStaticCursorResultSetThreshold(
                            cwbDB_RequestHandle  request,
							unsigned long           thresholdSize,
                            cwbSV_ErrHandle         errorHandle);


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetStreamFetchSyncCount                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the number of 32Kb blocks sent from the server to the      */
/*   client during a stream fetch before a synchronizing handshake  */
/*   is required.                                                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   unsigned short syncCount - input                               */
/*           Unsigned short integer which indicates how many 32Kb   */
/*           flows from the server will happen before a             */
/*           synchronizing hadshake will happen.                    */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*   CWBDB_STREAM_FETCH_NOT_COMPLETE - Stream fetch in process      */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is not valid for NDB or Catalog requests.             */
/*                                                                  */
/*   This API must be called before the cwbDB_DynamicStreamFetch    */
/*   or the cwbDB_ExtendedDynamicStreamFetch API is called.         */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_SetStreamFetchSyncCount(
                             cwbDB_RequestHandle  request,
                             unsigned short       syncCount,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetTimeFormat                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the format for time data returned from the AS/400.         */
/*   Time data on the AS/400 are stored encoded and are             */
/*   returned to the client as character strings. These             */
/*   character strings can be formatted in five different           */
/*   ways:                                                          */
/*                                                                  */
/*    Format name            Format            Example              */
/*    ---------------        ----------        ---------------      */
/*    Hours minutes seconds  hh:mm:ss          13:30:05             */
/*    USA                    hh:mm AM or PM    1:30 PM              */
/*    ISO                    hh.mm.ss          13:30:05             */
/*    IBM Europe             hh.mm.ss          13:30:05             */
/*    IBM Japan              hh:mm:ss          13:30:05             */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*      Handle to connection to AS/400 database access server.      */
/*                                                                  */
/*   unsigned short timeFormat - input                              */
/*       Indicates the format of time data.                         */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*   CWBDB_INVALID_ARG_API - Value specified is not in range.       */
/*                                                                  */
/* Usage Notes:                                                     */
/*   It is not valid to call this API after calling the             */
/*   cwbDB_StartServer API.                                         */
/*                                                                  */
/*   Use one of the defined values:                                 */
/*    Format name              Time format constant                 */
/*    ---------------          -----------------------              */
/*    Hours minutes seconds    CWBDB_TIME_FMT_HMS                   */
/*    USA                      CWBDB_TIME_FMT_USA                   */
/*    ISO                      CWBDB_TIME_FMT_ISO                   */
/*    IBM Europe               CWBDB_TIME_FMT_EUR                   */
/*    IBM Japan                CWBDB_TIME_FMT_JIS                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbDB_SetTimeFormat(
                             cwbDB_ConnectionHandle  connection,
                             unsigned short          timeFormat,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_SetTimeSeparator                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the character which separates the elements of time data    */
/*   returned from the AS/400.                                      */
/*                                                                  */
/*   Time data on the AS/400 are stored encoded and are             */
/*   returned to the client as character strings. These             */
/*   character strings can have one of four different time          */
/*   separator characters:                                          */
/*                                                                  */
/*    Date separator       Character       Example                  */
/*    ---------------      ----------      ---------------          */
/*    Colon                :               11:10:03                 */
/*    Period               .               11.10.03                 */
/*    Comma                ,               11,10,03                 */
/*    Blank                                11 10 03                 */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*      Handle to connection to AS/400 database access server.      */
/*                                                                  */
/*   unsigned short timeSeparator - input                           */
/*       Indicates the time data separator character.               */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*   CWBDB_INVALID_ARG_API - Value specified is not in range.       */
/*                                                                  */
/* Usage Notes:                                                     */
/*   It is not valid to call this API after calling the             */
/*   cwbDB_StartServer API.                                         */
/*                                                                  */
/*   Use one of the defined values:                                 */
/*        Time separator       Time separator constant              */
/*        ---------------      -----------------------              */
/*        Colon                CWBDB_TIME_SEP_COLON                 */
/*        Period               CWBDB_TIME_SEP_PERIOD                */
/*        Comma                CWBDB_TIME_SEP_COMMA                 */
/*        Blank                CWBDB_TIME_SEP_BLANK                 */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbDB_SetTimeSeparator(
                             cwbDB_ConnectionHandle  connection,
                             unsigned short          timeSeparator,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_StartServer                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Starts the communication between the client and the AS/400     */
/*   server.                                                        */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*       Handle to connection to AS/400 database access server.     */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_StartServer(
                             cwbDB_ConnectionHandle  connection,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_StartServerDetailed                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Starts the communication between the client and the AS/400     */
/*   server. Returns a more detailed return code than               */
/*   cwbDB_StartServer. Otherwise the same as cwbDB_StartServer.    */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*       Handle to connection to AS/400 database access server.     */
/*                                                                  */
/*   unsigned long *returnCode          - output                    */
/*       Pointer to an unsigned long to receive the detailed        */
/*       return code.                                               */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_StartServerDetailed(
                             cwbDB_ConnectionHandle  connection,
                             unsigned long          *returnCode,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_StopServer                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Ends the communication between the client and the AS/400       */
/*   server.                                                        */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_ConnectionHandle connection - input                      */
/*       Handle to connection to AS/400 database access server.     */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_StopServer(
                             cwbDB_ConnectionHandle  connection,
                             cwbSV_ErrHandle         errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_StoreRequestParameters                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Sends the current parameters to the AS/400 to the stored by    */
/*   the database access server.  Those parameters can then be      */
/*   used by the request on subsequent funtion calls.               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Incorrect connection handle.          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API is used to store a set of parameters in a buffer on   */
/*   the AS/400.  This is useful if there is a set of common        */
/*   parameters that are to be used for multiple functions.  The    */
/*   API allows the application to reduce the amount of data that   */
/*   needs to flow in order to perform all of the requests.         */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_StoreRequestParameters(
                             cwbDB_RequestHandle  request,
                             cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbDB_WriteLOBData                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Write LOB Data                                                 */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbDB_RequestHandle request - input                            */
/*           Handle to a request object.                            */
/*                                                                  */
/*   void*                dataPointer                               */
/*                                                                  */
/*   unsigned long        locator - input                           */
/*                                                                  */
/*   unsigned short       ccsid - input                             */
/*                                                                  */
/*   unsigned long        size - input                              */
/*                                                                  */
/*   unsigned long        start - input                             */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - input                            */
/*           Any returned messages will be written to this object.  */
/*           It is created with the cwbSV_CreateErrHandle API.      */
/*           The messages may be retrieved through the              */
/*           cwbSV_GetErrText API.  If the parameter is set to      */
/*           zero, no messages will be retrievable.                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_API_HANDLE - Invalid request handle.               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbDB_WriteLOBData(
                             cwbDB_RequestHandle  request,
			     void*                dataPointer,
                             unsigned long        locator,
                             unsigned short       ccsid,
			     unsigned long        size,
			     unsigned long        start,
                             cwbSV_ErrHandle      errorHandle);



#if defined( __cplusplus )
}
#endif

#endif /* _CWBDB_H_ */
