
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Fri Mar 02 14:55:17 2007
 */
/* Compiler settings for DA400.idl:
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

#ifndef __DA400_h__
#define __DA400_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "oledb.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_DA400_0000 */
/* [local] */ 

#ifdef DBINITCONSTANTS
// Custom schemas
// Objects {457B9480-4DC4-11d0-9B98-0020AF344E0A}
extern const GUID IBMSCHEMA_OBJECTS = { 0x457b9480, 0x4dc4, 0x11d0, { 0x9b, 0x98, 0x0, 0x20, 0xaf, 0x34, 0x4e, 0xa } };
// Custom command dialects
// Command/Program {457B9488-4DC4-11d0-9B98-0020AF344E0A}
extern const GUID IBMGUID_COMMAND = { 0x457b9488, 0x4dc4, 0x11d0, { 0x9b, 0x98, 0x0, 0x20, 0xaf, 0x34, 0x4e, 0xa } };
// Data Queue {457B9489-4DC4-11d0-9B98-0020AF344E0A}
extern const GUID IBMGUID_DATAQ = { 0x457b9489, 0x4dc4, 0x11d0, { 0x9b, 0x98, 0x0, 0x20, 0xaf, 0x34, 0x4e, 0xa } };
// Record Level Access {DDA19E80-4611-11d1-B40A-0004ACB6843D}
extern const GUID IBMGUID_RLA = { 0xdda19e80, 0x4611, 0x11d1, { 0xb4, 0xa, 0x0, 0x4, 0xac, 0xb6, 0x84, 0x3d } };
// Column description
#define IBMCOLGUID   {0xf9211d62,0xd80f,0x11d3,{0x9e,0xb2,0x0,0x20,0x35,0xc2,0x14,0x71}}
extern const DBID IBMCOLUMN_DESCRIPTION = {IBMCOLGUID, DBKIND_GUID_PROPID, (LPOLESTR)0};
// Column heading
extern const DBID IBMCOLUMN_HEADING = {IBMCOLGUID, DBKIND_GUID_PROPID, (LPOLESTR)1};
// Custom property sets
// Datasource Init {457B9490-4DC4-11d0-9B98-0020AF344E0A}
extern const GUID IBMPROPSET_DBINIT = { 0x457b9490, 0x4dc4, 0x11d0, { 0x9b, 0x98, 0x0, 0x20, 0xaf, 0x34, 0x4e, 0xa } };
// Datasource Init External {457B949A-4DC4-11d0-9B98-0020AF344E0A}
extern const GUID IBMPROPSET_DBINIT_EXT = { 0x457b949A, 0x4dc4, 0x11d0, { 0x9b, 0x98, 0x0, 0x20, 0xaf, 0x34, 0x4e, 0xa } };
// Datasource Init (ALL) {457B9491-4DC4-11d0-9B98-0020AF344E0A}
extern const GUID IBMPROPSET_DBINITALL = { 0x457b9491, 0x4dc4, 0x11d0, { 0x9b, 0x98, 0x0, 0x20, 0xaf, 0x34, 0x4e, 0xa } };
// Session {457B9492-4DC4-11d0-9B98-0020AF344E0A}
extern const GUID IBMPROPSET_SESSION = { 0x457b9492, 0x4dc4, 0x11d0, { 0x9b, 0x98, 0x0, 0x20, 0xaf, 0x34, 0x4e, 0xa } };
// Session (ALL) {457B9493-4DC4-11d0-9B98-0020AF344E0A}
extern const GUID IBMPROPSET_SESSIONALL = { 0x457b9493, 0x4dc4, 0x11d0, { 0x9b, 0x98, 0x0, 0x20, 0xaf, 0x34, 0x4e, 0xa } };
// File (DDM) Rowset {457B9494-4DC4-11d0-9B98-0020AF344E0A}
extern const GUID IBMPROPSET_FILEROWSET = { 0x457b9494, 0x4dc4, 0x11d0, { 0x9b, 0x98, 0x0, 0x20, 0xaf, 0x34, 0x4e, 0xa } };
// File (DDM) Rowset (ALL) {457B9495-4DC4-11d0-9B98-0020AF344E0A}
extern const GUID IBMPROPSET_FILEROWSETALL = { 0x457b9495, 0x4dc4, 0x11d0, { 0x9b, 0x98, 0x0, 0x20, 0xaf, 0x34, 0x4e, 0xa } };
// Data Queue Rowset {457B9496-4DC4-11d0-9B98-0020AF344E0A}
extern const GUID IBMPROPSET_DATAQROWSET = { 0x457b9496, 0x4dc4, 0x11d0, { 0x9b, 0x98, 0x0, 0x20, 0xaf, 0x34, 0x4e, 0xa } };
// Data Queue Rowset (ALL) {457B9497-4DC4-11d0-9B98-0020AF344E0A}
extern const GUID IBMPROPSET_DATAQROWSETALL = { 0x457b9497, 0x4dc4, 0x11d0, { 0x9b, 0x98, 0x0, 0x20, 0xaf, 0x34, 0x4e, 0xa } };
// Column {457B9498-4DC4-11d0-9B98-0020AF344E0A}
extern const GUID IBMPROPSET_COLUMN = { 0x457b9498, 0x4dc4, 0x11d0, { 0x9b, 0x98, 0x0, 0x20, 0xaf, 0x34, 0x4e, 0xa } };
// Column (ALL) {457B9499-4DC4-11d0-9B98-0020AF344E0A}
extern const GUID IBMPROPSET_COLUMNALL = { 0x457b9499, 0x4dc4, 0x11d0, { 0x9b, 0x98, 0x0, 0x20, 0xaf, 0x34, 0x4e, 0xa } };
#else // !DBINITCONSTANTS
extern const GUID IBMSCHEMA_OBJECTS;
extern const GUID IBMGUID_COMMAND;
extern const GUID IBMGUID_DATAQ;
extern const GUID IBMGUID_RLA;
extern const DBID IBMCOLUMN_DESCRIPTION;
extern const DBID IBMCOLUMN_HEADING;
extern const GUID IBMPROPSET_DBINIT;
extern const GUID IBMPROPSET_DBINIT_EXT;
extern const GUID IBMPROPSET_DBINITALL;
extern const GUID IBMPROPSET_SESSION;
extern const GUID IBMPROPSET_SESSIONALL;
extern const GUID IBMPROPSET_FILEROWSET;
extern const GUID IBMPROPSET_FILEROWSETALL;
extern const GUID IBMPROPSET_DATAQROWSET;
extern const GUID IBMPROPSET_DATAQROWSETALL;
extern const GUID IBMPROPSET_COLUMN;
extern const GUID IBMPROPSET_COLUMNALL;
#endif // DBINITCONSTANTS
// Custom property ids
enum IBMPROPENUM
{
    // IBMPROPSET_DBINIT
        IBMPROP_INIT_CURLIB = 0x0001L, // Initial Current Library
        IBMPROP_INIT_USRLIBL = 0x0002L, // Initial Library List
        IBMPROP_INIT_TRANSPORT = 0x0003L, // Product to run over - Client Access
        IBMPROP_INIT_SSL = 0x0004L, // Use SSL or not
        IBMPROP_INIT_TRANSLATE = 0X0005L, //Force Translate or not
        IBMPROP_INIT_DEFAULT_COLLECTION = 0X0006L, //Default Collection
        IBMPROP_INIT_CONVERT_DATE_TIME_TO_CHAR = 0x0007L, //Convert Date Time To Char
        IBMPROP_INIT_CATALOG_LIBRARY_LIST = 0x0008L, //Catalog Library List
        IBMPROP_INIT_CURSOR_SENSITIVITY = 0x0009L, // Cursor Sensitivity
        IBMPROP_INIT_USE_SQL_PACKAGES = 0x000AL, // Use SQL packages
        IBMPROP_INIT_SQL_PACKAGE_LIBRARY = 0x000BL, // SQL package library name
        IBMPROP_INIT_SQL_PACKAGE_NAME = 0x000CL, // SQL package name
        IBMPROP_INIT_SQL_PACKAGE_ADD_STATEMENTS = 0x000DL, // Add statements to SQL package
        IBMPROP_INIT_SQL_PACKAGE_UNUSABLE_ACTION = 0x000EL, // Unusable SQL package action
        IBMPROP_INIT_BLOCK_FETCH = 0x000FL, //Block Fetch
        IBMPROP_INIT_DATA_COMPRESSION = 0x0010L, //Data Compression
        IBMPROP_INIT_SORT_SEQUENCE = 0x0011L, //Sort Sequence
        IBMPROP_INIT_SORT_TABLE = 0x0012L, //Sort table name
        IBMPROP_INIT_SORT_LANGUAGE_ID = 0x0013L, //Sort Language ID
        IBMPROP_INIT_QUERY_OPTIONS_FILE_LIBRARY = 0x0014L, //Query Options File Library
        IBMPROP_INIT_TRACE = 0x0015L, //Trace
        IBMPROP_INIT_HEXPARSEROPTION = 0x0016L, //Hex Parser Option
        IBMPROP_INIT_MAX_DECIMAL_PRECISION = 0x0017L, //Maximum Decimal Precision
        IBMPROP_INIT_MAX_DECIMAL_SCALE = 0x0018L, //Maximum Decimal Scale
        IBMPROP_INIT_MIN_DIVIDE_SCALE = 0x0019L, //Minimum Divide Scale
        IBMPROP_INIT_JOBNAME = 0x001AL, //Job Name
        IBMPROP_INIT_LIBRARY_LIST = 0x001BL, //Library List
        IBMPROP_INIT_NAMING_CONVENTION = 0x001CL, //Naming Convention
        IBMPROP_INIT_QUERY_OPTIMIZE_GOAL = 0x001DL, // Query Optimize Goal

    // IBMPROPSET_SESSION
        IBMPROP_SESS_JOBNAME = 0x0001L, // DDM Jobname
        IBMPROP_SESS_EWLM_CORRELATOR = 0x0002L, //eWLM Correlator

    // IBMPROPSET_DATAQROWSET
    IBMPROP_RECEIVETIMEOUT = 0x0001L, // Data Queue Timeout

    // IBMPROPSET_FILEROWSET
    IBMPROP_FORMATSEQ = 0x0001L, // Format Sequence Level

    // IBMPROPSET_COLUMN
        IBMPROP_COL_HEADINGS = 0x0001L, // Column Headings
};


extern RPC_IF_HANDLE __MIDL_itf_DA400_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_DA400_0000_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


