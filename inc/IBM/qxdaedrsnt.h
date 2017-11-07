/*********************************************************************/
/*                                                                   */
/* 5722-XE1                                                          */
/* (C) Copyright IBM Corp. 2000,2003                                 */
/* All rights reserved.                                              */
/* US Government Users Restricted Rights -                           */
/* Use, duplication or disclosure restricted                         */
/* by GSA ADP Schedule Contract with IBM Corp.                       */
/*                                                                   */
/* Licensed Materials-Property of IBM                                */
/*                                                                   */
/*********************************************************************/
/*                                                                   */
/*                                                                   */
/* Module:                                                           */
/*     qxdaedrsnt.h                                                  */
/*                                                                   */
/* Purpose:                                                          */
/*     The functions listed in this file can be used to perform      */
/*     database operations on a remote iSeries server.               */
/*                                                                   */
/* The following APIs can be used to Connect to and Disconnect from  */
/* the remote database:                                              */
/*     QxdaConnectEDRS()                                             */
/*     QxdaDisconnectEDRS()                                          */
/*                                                                   */
/* The following APIs can be used for regular committment control:   */
/*     QxdaCommitEDRS()                                              */
/*     QxdaRollbackEDRS()                                            */
/*                                                                   */
/* The following APIs can be used to perform SQL work:               */
/*     QxdaProcessImmediateEDRS()                                    */
/*     QxdaProcessExtDynEDRS()                                       */
/*                                                                   */
/* The following APIs can be used to perform system work:            */
/*     QxdaProcessCommandEDRS()                                      */
/*     QxdaCallProgramEDRS()                                         */
/*     QxdaFindEDRSJob()                                             */
/*     QxdaCancelEDRS()                                              */
/*                                                                   */
/* The following APIs can be used for external committment control:  */
/*     QxdaSetConnection()                                           */
/*     QxdaXAPrepare()                                               */
/*     QxdaXACommit()                                                */
/*     QxdaXARollback()                                              */
/*     QxdaXAForget()                                                */
/*     QxdaXARecover()                                               */
/*                                                                   */
/* The following APIs can be used to set options related to XDA:     */
/*     QxdaSetOptions()                                              */
/*                                                                   */
/* Usage Notes:                                                      */
/*                                                                   */
/*   When building an appliation            Link with this           */
/*   this hardware platform:                import library           */
/*   ---------------------------            --------------           */
/*           x86-32                         CWBAPI.LIB               */
/*           x86-64                         CWBAPI6A.LIB             */
/*            IA64                          CWBAPI6I.LIB             */
/*                                                                   */
/*   This module is to be used in conjunction with QXDAEDRS.DLL.     */
/*                                                                   */
/* Note: Comments in this file refer to iSeries concepts and         */
/*       terminology.                                                */
/*                                                                   */
/*********************************************************************/

/* Prevent multiple includes */
#if !defined( _QXDAEDRSNT_H_ )
  #define     _QXDAEDRSNT_H_

/* Include base Client Access information */
#include "cwb.h"


/* Typedef to maintain consistency when declaring fields in certain  */
/* structures that are common on both the iSeries and Windows        */
/* platforms                                                         */
typedef void * _SYSPTR;

#define QXDA_MAX_CONNECTIONS     30  /* Max # of connections allowed */

#define QXDA_MAX_USER_DATA_LEN  256  /* Max length of job and suspend
                                        data in Qxda_CDBI0200 struct */

/*********************************************************************/
/* Commit options to use with QxdaCommit API                         */
/*********************************************************************/
#define QXDA_COMMIT_WORK          0
#define QXDA_COMMIT_WITH_HOLD     1

/*********************************************************************/
/* Rollback options to use with QxdaRollback API                     */
/*********************************************************************/
#define QXDA_ROLLBACK_WORK        0
#define QXDA_ROLLBACK_WITH_HOLD   1

/*********************************************************************/
/* Additional options to use with QxdaProcessExtDyn API              */
/*********************************************************************/
#define QXDA_EXTDYN_NOOPTS        0x00000000
#define QXDA_CREATE_OBJECTS       0x00000001
#define QXDA_FIND_STMT            0x00000010
#define QXDA_DEFER_OPEN           0x00000100

/*********************************************************************/
/* Disconnect options to use with QxdaDisconnectDB API               */
/*********************************************************************/
#define QXDA_DISCONNECT_COMMIT    0
#define QXDA_DISCONNECT_ROLLBACK  1

/*********************************************************************/
/* Parameter usages to use with QxdaCallProgram API                  */
/*********************************************************************/
#define QXDA_INPUT                0
#define QXDA_OUTPUT               1
#define QXDA_IN_OUT               2

/*********************************************************************/
/* Parameter types to use with QxdaCallProgram API                   */
/*********************************************************************/
#define QXDA_BIN4                 1
#define QXDA_CHAR                 2
#define QXDA_HEX                  3
#define QXDA_BIN2                 4

/*********************************************************************/
/* The following are XA operation ID's.                              */
/*********************************************************************/
#define QXDA_SQL_TXN_FIND     1
#define QXDA_SQL_TXN_CREATE   2
#define QXDA_SQL_TXN_SUSPEND  3
#define QXDA_SQL_TXN_END      4
#define QXDA_SQL_TXN_END_FAIL 5
#define QXDA_SQL_TXN_RESUME   6
#define QXDA_SQL_TXN_LOOSELY_COUPLED_CREATE 7 
#define QXDA_SQL_TXN_JOIN     8       	

/*********************************************************************/
/* The values are definitions for customer tracing                   */
/*********************************************************************/
#define     QXDA_TRACE_NONE      0                       
#define     QXDA_TRACE_INFO      1                       
#define     QXDA_TRACE_ERROR     2                       
#define     QXDA_TRACE_VERBOSE   3                       
#define     QXDA_TRACE_NET        "TRACENET"		
#define     QXDA_TRACE_DATA_BLOCK "TRACEDATABLOCK"


#if defined( __cplusplus )
  extern "C" {
#endif

/*************************************************************************/
/* Prototypes for calling the APIs                                       */
/*************************************************************************/

/*************************************************************************/
/* API: QxdaCancelEDRS                                                   */
/*                                                                       */
/* Purpose: The Cancel EDRS Request (QxdaCancelEDRS) API is used to      */
/*          cancel a previous call to the QxdaProcessExtDynEDRS or       */
/*          QxdaProcessImmediateEDRS APIs. All parameters are passed     */
/*          to the program by reference.                                 */
/*                                                                       */
/* Parameters:                                                           */
/*                                                                       */
/*   Connection handle - Input                                           */
/*     The handle number of the connection on which to execute the cancel*/
/*     request. The connection handle must have been generated by the    */
/*     QxdaConnectEDRS API in the current job and activation group. The  */
/*     connection must have been made to the same system where the       */
/*     qualified job name, user, and number currently is executing.      */
/*                                                                       */
/*   Input structure - Input                                             */
/*     The structure in which to pass information about the job to       */
/*     cancel. For the format of this parameter, see CNCL0100 Format.    */
/*                                                                       */
/*   Input structure format - Input                                      */
/*     The format of the input structure template being used. The        */
/*     possible value is:  CNCL0100 Basic input structure.  See          */
/*     declaration of the CNCL0100 structure.                            */
/*                                                                       */
/*   Error code - Input/Output                                           */
/*     The structure in which to return error information.  See          */
/*     declarations for the Qus_EC_t and Qus_ERRC0200_t structures.      */
/*                                                                       */
/* Error codes: Here is a list of the most common error codes returned   */
/*              from this API:                                           */
/*              Message ID Error Message Text                            */
/*              CPFAE14 E Cannot allocate &1 bytes.                      */
/*              CPFB750 E Connection handle specified not valid.         */
/*              CPFB757 E The connection is suspended.                   */
/*              CPFB758 E The EDRS server system has been switched.      */
/*              CPF1344 E Not authorized to control job &1.              */
/*              CPF1321 E Job &1 user &2 job number &3 not found.        */
/*                                                                       */
/* Usage Notes:                                                          */
/*   This function may be called from the initial thread of a job only.  */
/*                                                                       */
/*************************************************************************/
void CWB_ENTRY QxdaCancelEDRS(
                          int  * connectionHandle,
                          void * inputStructure,
                          char * inputStructureFormat,
                          void * errorCode);


/*************************************************************************/
/* API: QxdaConnectEDRS                                                  */
/*                                                                       */
/* Purpose: The Connect to EDRS Server (QxdaConnectEDRS) API is used to  */
/*          initiate a connection between the local system (requesting   */
/*          system), and a server system.                                */
/*                                                                       */
/*          The CDBI0200 input format is intended for use only with      */
/*          TCP/IP socket connections. When using the CDBI0200 input     */
/*          format, the shadow job will run under the specified user     */
/*          profile name. It will use the specified user profile's       */
/*          associated job description and job priority. The CCSID will  */
/*          be set to the CCSID of the server job field in the input     */
/*          structure.                                                   */
/*                                                                       */
/*          If a relational database (RDB) name is specified for the     */
/*          CDBI0200 format, it must be blank padded to 18 characters,   */
/*          the maximum length of an RDB name. If the server system      */
/*          does not have any active independent ASPs, the only RDB that */
/*          can be connected is the *LOCAL RDB. All other RDB names will */
/*          cause the CPFB752 message to be sent to the caller. The      */
/*          *LOCAL RDB can be determined by viewing the 'remote location'*/
/*          column when executing the WRKRDBDIRE command.                */
/*                                                                       */
/*          If XA commitment control is specified for the CDBI0200       */
/*          format, the Transaction Manager Information field must be    */
/*          blank padded to 10 characters, the maximum length, and a     */
/*          Lock Timeout Value should be given.                          */
/*                                                                       */
/* Parameters:                                                           */
/*                                                                       */
/*   Input structure - Input                                             */
/*     The structure in which to pass information about the connection.  */
/*                                                                       */
/*   Input structure format - Input                                      */
/*     The format of the input structure template being used. The        */
/*     possible value is:                                                */
/*                                                                       */
/*     CDBI0200 Basic input structure with user profile and password     */
/*     fields.  See declaration of the CDBI0200 format.                  */
/*                                                                       */
/*   Receiver variable  - Output                                         */
/*     The structure in which to return information about the            */
/*     connection.  For the format of this parameter, see CDBO0100       */
/*     Format.                                                           */
/*                                                                       */
/*   Length of receiver variable - Input                                 */
/*     The number of bytes that the calling program provides for the     */
/*     receiver variable data.                                           */
/*                                                                       */
/*   Receiver variable format - Input                                    */
/*     The format of the receiver variable template being used. The      */
/*     possible value is:                                                */
/*                                                                       */
/*     CDBO0100 Basic receiver variable.  See declaration of the format. */
/*                                                                       */
/*   Error code - Input/Output                                           */
/*     The structure in which to return error information.  The "Key"    */
/*     field in the Qus_ERRC0200_t structure is an input field.  Also,   */
/*     the "Bytes_Provided" field in both the Qus_ERRC0200_t and Qus_EC_t*/
/*     structures is for input.  The rest of the fields are for Output.  */
/*     See declarations of the Qus_EC_t and Qus_ERRC0200_t structures.   */
/*                                                                       */
/* Error codes: Here is a list of the most common error codes returned   */
/*              from this API:                                           */
/*              Message ID Error Message Text                            */
/*              CPF180C E Function &1 not allowed.                       */
/*              CPF24B4 E Severe error while addressing parameter list.  */
/*              CPF3C21 E Format name &1 is not valid.                   */
/*              CPF3C90 E Literal value cannot be changed.               */
/*              CPF9872 E Program or service program &1 in library &2    */
/*                        ended. Reason code &3.                         */
/*              CPFAE14 E Cannot allocate &1 bytes.                      */
/*              CPFB751 E Parameter &1 passed not correct.               */
/*              CPFB752 E Internal error in &1 API.                      */
/*              CPFB753 E Required OptiConnect support not installed.    */
/*              CPFB754 E Unable to open connection. Reason code &1.     */
/*              CPFB757 E The connection is suspended.                   */
/*              CPFB758 E The EDRS server system has been switched.      */
/*                                                                       */
/* Usage Notes:                                                          */
/*   This function may be called from the initial thread of a job only.  */
/*                                                                       */
/*************************************************************************/
void CWB_ENTRY QxdaConnectEDRS(
                          void * inputStructure,
                          char * inputStructureFormat,
                          void * receiverVariable,
                          int  * receiverVariableLength,
                          char * receiverVariableFormat,
                          void * errorCode);


/*************************************************************************/
/* API: QxdaCommitEDRS                                                   */
/*                                                                       */
/* Purpose: The Commit EDRS Server (QxdaCommitEDRS) API is used to commit*/
/*          transactions on the database server.                         */
/*                                                                       */
/* Parameters:                                                           */
/*                                                                       */
/*   Connection handle - Input                                           */
/*     The handle number of the connection on which to perform the commit*/
/*     operation. The connection handle must have been generated by the  */
/*     QxdaConnectEDRS API in the current job and activation group.      */
/*                                                                       */
/*   Additional commit options - Input                                   */
/*     The following are valid commit options:                           */
/*      0 QXDA_COMMIT_WORK                                               */
/*      1 QXDA_COMMIT_WITH_HOLD                                          */
/*                                                                       */
/*   SQL communications area  - Output                                   */
/*     Returns diagnostic information. It includes the SQLCODE variable, */
/*     indicating whether an error has occurred. If SQLCODE has a value  */
/*     of 0 after a call to this API, the function was successful.       */
/*                                                                       */
/*   Error code - Input/Output                                           */
/*     The structure in which to return error information.  The "Key"    */
/*     field in the Qus_ERRC0200_t structure is an input field.  Also,   */
/*     the "Bytes_Provided" field in both the Qus_ERRC0200_t and Qus_EC_t*/
/*     structures is for input.  The rest of the fields are for Output.  */
/*     See declarations of the Qus_EC_t and Qus_ERRC0200_t structures.   */
/*                                                                       */
/* Error codes: Here is a list of the most common error codes returned   */
/*              from this API:                                           */
/*              Message ID Error Message Text                            */
/*              CPF180C E Function &1 not allowed.                       */
/*              CPF24B4 E Severe error while addressing parameter list.  */
/*              CPF3C90 E Literal value cannot be changed.               */
/*              CPF9872 E Program or service program &1 in library &2    */
/*                        ended. Reason code &3.                         */
/*              CPFB750 E Connection handle specified not valid.         */
/*              CPFB751 E Parameter &1 passed not correct.               */
/*              CPFB752 E Internal error in &1 API.                      */
/*              CPFB757 E The connection is suspended.                   */
/*              CPFB758 E The EDRS server system has been switched.      */
/*                                                                       */
/* Usage Notes:                                                          */
/*   This function may be called from the initial thread of a job only.  */
/*                                                                       */
/*************************************************************************/
void CWB_ENTRY QxdaCommitEDRS(
                          int  * connectionHandle,
                          int  * commitOptions,
                          void * SQL_CommunicationsArea,
                          void * errorCode);


/*************************************************************************/
/* API: QxdaRollbackEDRS                                                 */
/*                                                                       */
/* Purpose: The Roll Back EDRS Server (QxdaRollbackEDRS) API is used to  */
/*          roll back transactions on the database server.               */
/*                                                                       */
/* Parameters:                                                           */
/*                                                                       */
/*   Connection handle - Input                                           */
/*     The handle number of the connection on which to perform the       */
/*     rollback operation. The connection handle must have been generated*/
/*     by the QxdaConnectEDRS API in the current job and activation      */
/*     group.                                                            */
/*                                                                       */
/*   Additional rollback options - Input                                 */
/*     The following are valid rollback options:                         */
/*      0 QXDA_ROLLBACK_WORK                                             */
/*      1 QXDA_ROLLBACK_WITH_HOLD                                        */
/*                                                                       */
/*   SQL communications area  - Output                                   */
/*     Returns diagnostic information. It includes the SQLCODE variable, */
/*     indicating whether an error has occurred. If SQLCODE has a value  */
/*     of 0 after a call to this API, the function was successful.       */
/*                                                                       */
/*   Error code - Input/Output                                           */
/*     The structure in which to return error information.  The "Key"    */
/*     field in the Qus_ERRC0200_t structure is an input field.  Also,   */
/*     the "Bytes_Provided" field in both the Qus_ERRC0200_t and Qus_EC_t*/
/*     structures is for input.  The rest of the fields are for Output.  */
/*     See declarations of the Qus_EC_t and Qus_ERRC0200_t structures.   */
/*                                                                       */
/* Error codes: Here is a list of the most common error codes returned   */
/*              from this API:                                           */
/*              Message ID Error Message Text                            */
/*              CPF180C E Function &1 not allowed.                       */
/*              CPF24B4 E Severe error while addressing parameter list.  */
/*              CPF3C90 E Literal value cannot be changed.               */
/*              CPF9872 E Program or service program &1 in library &2    */
/*                        ended. Reason code &3.                         */
/*              CPFB750 E Connection handle specified not valid.         */
/*              CPFB751 E Parameter &1 passed not correct.               */
/*              CPFB752 E Internal error in &1 API.                      */
/*              CPFB757 E The connection is suspended.                   */
/*              CPFB758 E The EDRS server system has been switched.      */
/*                                                                       */
/* Usage Notes:                                                          */
/*   This function may be called from the initial thread of a job only.  */
/*                                                                       */
/*************************************************************************/
void CWB_ENTRY QxdaRollbackEDRS(
                          int  * connectionHandle,
                          int  * rollbackOptions,
                          void * SQL_CommunicationsArea,
                          void * errorCode);


/*************************************************************************/
/* API: QxdaProcessImmediateEDRS                                         */
/*                                                                       */
/* Purpose: The Process Immediate SQL Statement                          */
/*          (QxdaProcessImmediateEDRS) API is used to run an SQL         */
/*          statement on the database server. The statement is processed */
/*          exactly as provided, without coded character set identifier  */
/*          (CCSID) conversion.                                          */
/*                                                                       */
/* Parameters:                                                           */
/*                                                                       */
/*   Connection handle - Input                                           */
/*     The handle number of the connection on which to process the SQL   */
/*     statement.The connection handle must have been generated by the   */
/*     QxdaConnectEDRS API in the current job and activation group.      */
/*                                                                       */
/*   SQL statement - Input                                               */
/*     The SQL statement to process.                                     */
/*                                                                       */
/*   Length of SQL statement - Input                                     */
/*     The length of the SQL statement passed.                           */
/*                                                                       */
/*   SQL communications area  - Output                                   */
/*     Returns diagnostic information. It includes the SQLCODE variable, */
/*     indicating whether an error has occurred. If SQLCODE has a value  */
/*     of 0 after a call to this API, the function was successful.       */
/*                                                                       */
/*   Error code - Input/Output                                           */
/*     The structure in which to return error information.  The "Key"    */
/*     field in the Qus_ERRC0200_t structure is an input field.  Also,   */
/*     the "Bytes_Provided" field in both the Qus_ERRC0200_t and Qus_EC_t*/
/*     structures is for input.  The rest of the fields are for Output.  */
/*     See declarations of the Qus_EC_t and Qus_ERRC0200_t structures.   */
/*                                                                       */
/* Error codes: Here is a list of the most common error codes returned   */
/*              from this API:                                           */
/*              Message ID Error Message Text                            */
/*              CPF180C E Function &1 not allowed.                       */
/*              CPF24B4 E Severe error while addressing parameter list.  */
/*              CPF3C90 E Literal value cannot be changed.               */
/*              CPF9872 E Program or service program &1 in library &2    */
/*                        ended. Reason code &3.                         */
/*              CPFB750 E Connection handle specified not valid.         */
/*              CPFB752 E Internal error in &1 API.                      */
/*              CPFB756 E Rollback operation performed.                  */
/*              CPFB757 E The connection is suspended.                   */
/*              CPFB758 E The EDRS server system has been switched.      */
/*                                                                       */
/* Usage Notes:                                                          */
/*   This function may be called from the initial thread of a job only.  */
/*                                                                       */
/*************************************************************************/
void CWB_ENTRY QxdaProcessImmediateEDRS(
                          int  * connectionHandle,
                          char * SQL_Statement,
                          int  * SQL_StatementLength,
                          void * SQL_CommunicationsArea,
                          void * errorCode);


/*************************************************************************/
/* API: QxdaProcessExtDynEDRS                                            */
/*                                                                       */
/* Purpose: The Process Remote Extended Dynamic SQL                      */
/*          (QxdaProcessExtDynEDRS) API is used to perform extended      */
/*          dynamic SQL operations on the database server system. The    */
/*          SQL operations are performed by the Process Extended Dynamic */
/*          SQL (QSQPRCED API).                                          */
/*                                                                       */
/* Parameters:                                                           */
/*                                                                       */
/*   Connection handle - Input                                           */
/*     The handle number of the connection on which to perform the       */
/*     extended dynamic SQL operation. The connection handle must have   */
/*     been generated by the QxdaConnectEDRS API in the current job and  */
/*     activation group.                                                 */
/*                                                                       */
/*   SQL descriptor area  - Input                                        */
/*     Passes information about the variables being used on a specific   */
/*     SQL statement. The SQLDA is used for passing the address, data    */
/*     type, length, and CCSID for variables on an OPEN, EXECUTE, FETCH, */
/*     or DESCRIBE function.                                             */
/*                                                                       */
/*   SQL communications area  - Output                                   */
/*     Returns diagnostic information. It includes the SQLCODE variable, */
/*     indicating whether an error has occurred. If SQLCODE has a value  */
/*     of 0 after a call to this API, the function was successful.       */
/*                                                                       */
/*   QSQPRCED function template format - Input                           */
/*     The format of the function template being used.                   */
/*                                                                       */
/*   QSQPRCED function template - Input                                  */
/*     Determines the function to perform, the requested statement to    */
/*     process, and the SQL package to be used. It also contains the     */
/*     text of the statement, which is required for the PREPARE function.*/
/*                                                                       */
/*   Receiver variable - Output                                          */
/*     The structure in which to return information about the connection.*/
/*                                                                       */
/*   Length of receiver variable - Input                                 */
/*     The number of bytes that the calling program provides for the     */
/*     receiver variable data.                                           */
/*                                                                       */
/*   Receiver variable format - Input                                    */
/*     The format of the receiver variable template being used. The      */
/*     possible value is:                                                */
/*                                                                       */
/*     EXDO0100 Basic receiver variable.  See declaration of the         */
/*     EXDO0100 structure.                                               */
/*                                                                       */
/*   Additional options - Input                                          */
/*     The following are valid options. The binary OR operation can be   */
/*     used to use more than one of these options together:              */
/*                                                                       */
/*     0x00000000 - 0 - QXDA_EXTDYN_NOOPTS                               */
/*     0x00000001 - 1 - QXDA_CREATE_OBJECTS                              */
/*     0x00000010 - 16 - QXDA_DEFER_OPEN                                 */
/*     0x00000100 - 256 - QXDA_FIND_STMT                                 */
/*                                                                       */
/*   Error code - Input/Output                                           */
/*     The structure in which to return error information.  The "Key"    */
/*     field in the Qus_ERRC0200_t structure is an input field.  Also,   */
/*     the "Bytes_Provided" field in both the Qus_ERRC0200_t and Qus_EC_t*/
/*     structures is for input.  The rest of the fields are for Output.  */
/*     See declarations of the Qus_EC_t and Qus_ERRC0200_t structures.   */
/*                                                                       */
/* Error codes: Here is a list of the most common error codes returned   */
/*              from this API:                                           */
/*              Message ID Error Message Text                            */
/*              CPF180C E Function &1 not allowed.                       */
/*              CPF24B4 E Severe error while addressing parameter list.  */
/*              CPF3C21 E Format name &1 is not valid.                   */
/*              CPF3C90 E Literal value cannot be changed.               */
/*              CPF9872 E Program or service program &1 in library &2    */
/*                        ended. Reason code &3.                         */
/*              CPFAE14 E Cannot allocate &1 bytes.                      */
/*              CPFB750 E Connection handle specified not valid.         */
/*              CPFB752 E Internal error in &1 API.                      */
/*              CPFB756 E Rollback operation performed.                  */
/*              CPFB757 E The connection is suspended.                   */
/*              CPFB758 E The EDRS server system has been switched.      */
/*              CPFB759 E Cursor not valid for operation.                */
/*                                                                       */
/* Usage Notes:                                                          */
/*   This function may be called from the initial thread of a job only.  */
/*                                                                       */
/*************************************************************************/
void CWB_ENTRY QxdaProcessExtDynEDRS(
                          int  * connectionHandle,
                          void * SQL_DescriptorArea,
                          void * SQL_CommunicationsArea,
                          char * QSQPRCED_FormatName,
                          void * QSQPRCED_InputFormat,
                          void * receiverVariable,
                          int  * receiverVariableLength,
                          char * receiverVariableFormat,
                          int  * extendedDynamicOptions,
                          void * errorCode);



/*************************************************************************/
/* API: QxdaProcessCommandEDRS                                           */
/*                                                                       */
/* Purpose: The Process Command (QxdaProcessCommandEDRS) API is used to  */
/*          run a system command on the database server system. The      */
/*          command is called exactly as passed, without coded character */
/*          set identifier (CCSID) conversion.                           */
/*                                                                       */
/* Parameters:                                                           */
/*                                                                       */
/*   Connection handle - Input                                           */
/*     The handle number of the connection on which to call the command. */
/*     The connection handle must have been generated by the             */
/*     QxdaConnectEDRS API in the current job and activation group.      */
/*                                                                       */
/*   Command - Input                                                     */
/*     The command you want to run entered as a character string. If the */
/*     command contains blanks, it must be enclosed in apostrophes. The  */
/*     maximum length of the string is 32702 characters.                 */
/*                                                                       */
/*   Length of command  - Input                                          */
/*     The length of the command to run.                                 */
/*                                                                       */
/*   Error code - Input/Output                                           */
/*     The structure in which to return error information.  The "Key"    */
/*     field in the Qus_ERRC0200_t structure is an input field.  Also,   */
/*     the "Bytes_Provided" field in both the Qus_ERRC0200_t and Qus_EC_t*/
/*     structures is for input.  The rest of the fields are for Output.  */
/*     See declarations of the Qus_EC_t and Qus_ERRC0200_t structures.   */
/*                                                                       */
/* Error codes: Here is a list of the most common error codes returned   */
/*              from this API:                                           */
/*              Message ID Error Message Text                            */
/*              CPF180C E Function &1 not allowed.                       */
/*              CPF24B4 E Severe error while addressing parameter list.  */
/*              CPF3C90 E Literal value cannot be changed.               */
/*              CPF9872 E Program or service program &1 in library &2    */
/*                        ended. Reason code &3.                         */
/*              CPFAE14 E Cannot allocate &1 bytes.                      */
/*              CPFB750 E Connection handle specified not valid.         */
/*              CPFB752 E Internal error in &1 API.                      */
/*              CPFB756 E Rollback operation performed.                  */
/*              CPFB757 E The connection is suspended.                   */
/*              CPFB758 E The EDRS server system has been switched.      */
/*              xxxnnnn E Any escape message issued by any command may   */
/*                        be returned.                                   */
/*                                                                       */
/* Usage Notes:                                                          */
/*   This function may be called from the initial thread of a job only.  */
/*                                                                       */
/*************************************************************************/
void CWB_ENTRY QxdaProcessCommandEDRS(
                          int  * connectionHandle,
                          char * systemCommand,
                          int  * systemCommandLength,
                          void * errorCode);


/*************************************************************************/
/* API: QxdaCallProgramEDRS                                              */
/*                                                                       */
/* Purpose: The Call Program (QxdaCallProgramEDRS) API is used to call a */
/*          user-defined program on the database server system.          */
/*                                                                       */
/* Parameters:                                                           */
/*                                                                       */
/*   Connection handle - Input                                           */
/*     The handle number of the connection on which to call the program. */
/*     The connection handle must have been generated by the             */
/*     QxdaConnectEDRS API in the current job and activation group.      */
/*                                                                       */
/*   Qualified program name  - Input                                     */
/*     The library and name of the program to call.                      */
/*                                                                       */
/*   Number of parameters - Input                                        */
/*     The number of parameters to pass to the program.                  */
/*                                                                       */
/*   Parameter information - Input                                       */
/*     Information about each of the parameters. This should be an array */
/*     of type Qxda_ParmInfo_t, with one entry for each parameter. See   */
/*     declaration of the Qxda_ParmInfo_t structure.                     */
/*                                                                       */
/*   Error code - Input/Output                                           */
/*     The structure in which to return error information.  The "Key"    */
/*     field in the Qus_ERRC0200_t structure is an input field.  Also,   */
/*     the "Bytes_Provided" field in both the Qus_ERRC0200_t and Qus_EC_t*/
/*     structures is for input.  The rest of the fields are for Output.  */
/*     See declarations of the Qus_EC_t and Qus_ERRC0200_t structures.   */
/*                                                                       */
/* Error codes: Here is a list of the most common error codes returned   */
/*              from this API:                                           */
/*              Message ID Error Message Text                            */
/*              CPF180C E Function &1 not allowed.                       */
/*              CPF24B4 E Severe error while addressing parameter list.  */
/*              CPF3C90 E Literal value cannot be changed.               */
/*              CPF9872 E Program or service program &1 in library &2    */
/*                        ended. Reason code &3.                         */
/*              CPFAE14 E Cannot allocate &1 bytes.                      */
/*              CPFB750 E Connection handle specified not valid.         */
/*              CPFB752 E Internal error in &1 API.                      */
/*              CPFB755 E Program &1 in library &2 not found.            */
/*              CPFB756 E Rollback operation performed.                  */
/*              CPFB757 E The connection is suspended.                   */
/*              CPFB758 E The EDRS server system has been switched.      */
/*                                                                       */
/* Usage Notes:                                                          */
/*   This function may be called from the initial thread of a job only.  */
/*                                                                       */
/*************************************************************************/
void CWB_ENTRY QxdaCallProgramEDRS(
                          int  * connectionHandle,
                          char * qualifiedProgramName,
                          int  * parameters,
                          void * parameterInformation,
                          void * errorCode);


/*************************************************************************/
/* API: QxdaFindEDRSJob                                                  */
/*                                                                       */
/* Purpose: The Find EDRS Job (QxdaFindEDRSJob) API is used to find all  */
/*          jobs with user-defined data associated with the Connect to   */
/*          EDRS Server (QxdaConnectEDRS) API that matches the data      */
/*          passed to this API.                                          */
/*                                                                       */
/* Parameters:                                                           */
/*                                                                       */
/*   Connection handle - Input                                           */
/*     The handle number of the connection in which to find jobs.        */
/*     The connection handle must have been generated by the             */
/*     QxdaConnectEDRS API in the current job and activation group.      */
/*                                                                       */
/*   Job-associated user data   - Input                                  */
/*     User data that also was passed to the Connect to EDRS Server      */
/*     (QxdaConnectEDRS) API. This may be the complete user data or only */
/*     a part of it. If it is only part, it must be the beginning of the */
/*     user data string.                                                 */
/*                                                                       */
/*   Length of job-associated user data  - Input                         */
/*     The length of the user data to compare.                           */
/*                                                                       */
/*   Receiver variable - Output                                          */
/*     Space for the job information to be returned. This information is */
/*     returned as an array of QJBI0100 structures, one for each job     */
/*     found. For the format of each array element, see QJBI0100 Format. */
/*                                                                       */
/*   Length of receiver variable - Input                                 */
/*     Length (in bytes) of the receiver variable provided to return     */
/*     information about the jobs found.                                 */
/*                                                                       */
/*   Receiver variable format - Input                                    */
/*     The format of the structure in which to return information about  */
/*     the jobs found. The possible value is:                            */
/*                                                                       */
/*     QJBI0100 Basic receiver variable structure.  See the declaration  */
/*     of the QJBI0100 structure.                                        */
/*                                                                       */
/*   Number of jobs found - Output                                       */
/*     The number of jobs found with associated user data that matches   */
/*     the user data passed in. This is the total number found, even if  */
/*     the information for all the jobs cannot fit in the space provided.*/
/*                                                                       */
/*   Number of jobs returned - Output                                    */
/*     The actual number of jobs for which information was returned.     */
/*                                                                       */
/*   Error code - Input/Output                                           */
/*     The structure in which to return error information.  The "Key"    */
/*     field in the Qus_ERRC0200_t structure is an input field.  Also,   */
/*     the "Bytes_Provided" field in both the Qus_ERRC0200_t and Qus_EC_t*/
/*     structures is for input.  The rest of the fields are for Output.  */
/*     See declarations of the Qus_EC_t and Qus_ERRC0200_t structures.   */
/*                                                                       */
/* Error codes: Here is a list of the most common error codes returned   */
/*              from this API:                                           */
/*              Message ID Error Message Text                            */
/*              CPF180C E Function &1 not allowed.                       */
/*              CPF24B4 E Severe error while addressing parameter list.  */
/*              CPF3C90 E Literal value cannot be changed.               */
/*              CPF9872 E Program or service program &1 in library &2    */
/*                        ended. Reason code &3.                         */
/*              CPFB750 E Connection handle specified not valid.         */
/*              CPFB751 E Parameter &1 passed not correct.               */
/*              CPFB752 E Internal error in &1 API.                      */
/*              CPFB756 E Rollback operation performed.                  */
/*              CPFB757 E The connection is suspended.                   */
/*              CPFB758 E The EDRS server system has been switched.      */
/*                                                                       */
/* Usage Notes:                                                          */
/*   This function may be called from the initial thread of a job only.  */
/*                                                                       */
/*************************************************************************/
void CWB_ENTRY QxdaFindEDRSJob(
                          int  * connectionHandle,
                          char * userData,
                          int  * userDataLength,
                          void * receiverVariable,
                          int  * receiverVariableLength,
                          char * receiverVariableFormat,
                          int  * jobsFound,
                          int  * jobsReturned,
                          void * errorCode);


/*************************************************************************/
/* API: QxdaDisconnectEDRS                                               */
/*                                                                       */
/* Purpose: The Disconnect from EDRS Server (QxdaDisconnectEDRS) API is  */
/*          used to end a connection to a server system.                 */
/*                                                                       */
/* Parameters:                                                           */
/*                                                                       */
/*   Connection handle - Input                                           */
/*     The handle number of the connection to end. The connection handle */
/*     must have been generated by the QxdaConnectEDRS API in the current*/
/*     job and activation group.                                         */
/*                                                                       */
/*   Additional disconnection options - Input                            */
/*     The following are valid disconnection options:                    */
/*     0 - QXDA_DISCONNECT_COMMIT                                        */
/*     1 - QXDA_DISCONNECT_ROLLBACK                                      */
/*                                                                       */
/*   Error code - Input/Output                                           */
/*     The structure in which to return error information.  The "Key"    */
/*     field in the Qus_ERRC0200_t structure is an input field.  Also,   */
/*     the "Bytes_Provided" field in both the Qus_ERRC0200_t and Qus_EC_t*/
/*     structures is for input.  The rest of the fields are for Output.  */
/*     See declarations of the Qus_EC_t and Qus_ERRC0200_t structures.   */
/*                                                                       */
/* Error codes: Here is a list of the most common error codes returned   */
/*              from this API:                                           */
/*              Message ID Error Message Text                            */
/*              CPF180C E Function &1 not allowed.                       */
/*              CPF24B4 E Severe error while addressing parameter list.  */
/*              CPF3C90 E Literal value cannot be changed.               */
/*              CPF9872 E Program or service program &1 in library &2    */
/*                        ended. Reason code &3.                         */
/*              CPFB750 E Connection handle specified not valid.         */
/*              CPFB751 E Parameter &1 passed not correct.               */
/*              CPFB752 E Internal error in &1 API.                      */
/*              CPFB756 E Rollback operation performed.                  */
/*              CPFB757 E The connection is suspended.                   */
/*                                                                       */
/* Usage Notes:                                                          */
/*   This function may be called from the initial thread of a job only.  */
/*                                                                       */
/*************************************************************************/
void CWB_ENTRY QxdaDisconnectEDRS(
                          int  * connectionHandle,
                          int  * disconnectOptions,
                          void * errorCode);


/*************************************************************************/
/* API: QxdaSetConnection                                                */
/*                                                                       */
/* Purpose: A transaction manager calls QxdaSetConnection() to perform   */
/*          XA-transaction related operations for a particular           */
/*          connection.                                                  */
/*                                                                       */
/* Parameters:                                                           */
/*                                                                       */
/*   Connection handle - Input                                           */
/*     The handle number of the connection on which to perform the XA    */
/*     operation. The connection handle must have been generated by the  */
/*     QxdaConnectEDRS API in the current job and activation group.      */
/*                                                                       */
/*   Transaction branch identifier - Input                               */
/*     A pointer to the transaction branch identifier. This identifier   */
/*     is generated by the transaction manager when it starts the        */
/*     transaction branch. The max length is 140 bytes.                  */
/*                                                                       */
/*   Return value - Output                                               */
/*     The return value of the XA operation. Possible return values:     */
/*                                                                       */
/*     0 SQL_SUCCESS                                                     */
/*     1 SQL_SUCCESS_WITH_INFO                                           */
/*    -1 SQL_ERROR                                                       */
/*    -2 SQL_INVALID_HANDLE                                              */
/*                                                                       */
/*   Operation - Input                                                   */
/*     Valid operations are:                                             */
/*                                                                       */
/*     QXDA_SQL_TXN_FIND                                                 */
/*     QXDA_SQL_TXN_CREATE                                               */
/*     QXDA_SQL_TXN_SUSPEND                                              */
/*     QXDA_SQL_TXN_END                                                  */
/*                                                                       */
/*   Timeout value - Input                                               */
/*     Timeout value for the transaction in seconds. If the Timout Value */
/*     is not greater than 0, then the default system timeout value will */
/*     be used. This value must be >= 0 and applies to the               */
/*     XDA_SQL_TXN_CREATE operation.                                     */
/*                                                                       */
/*   Error code - Input/Output                                           */
/*     The structure in which to return error information.  The "Key"    */
/*     field in the Qus_ERRC0200_t structure is an input field.  Also,   */
/*     the "Bytes_Provided" field in both the Qus_ERRC0200_t and Qus_EC_t*/
/*     structures is for input.  The rest of the fields are for Output.  */
/*     See declarations of the Qus_EC_t and Qus_ERRC0200_t structures.   */
/*                                                                       */
/* Error codes: Here is a list of the most common error codes returned   */
/*              from this API:                                           */
/*              Message ID Error Message Text                            */
/*              CPE3418 E Possible APAR condition or hardware failure.   */
/*              CPF3CF2 E Error(s) occurred during running of &1 API.    */
/*              CPF9872 E Program or service program &1 in library &2    */
/*                        ended. Reason code &3.                         */
/*              CPFB760 E Error encountered in &2 API, return code &1.   */
/*                                                                       */
/* Usage Notes:                                                          */
/*   This function may be called from the initial thread of a job only.  */
/*                                                                       */
/*************************************************************************/
void CWB_ENTRY QxdaSetConnection (
                          int  * connectionHandle,
                          void * transactionBranchIdentifier,
                          int  * returnValue,
                          int  * operation,
                          int  * timeoutValue,
                          void * errorCode);


/*************************************************************************/
/* API: QxdaXAPrepare                                                    */
/*                                                                       */
/* Purpose: A transaction manager calls QxdaXAPrepare() to request that  */
/*          a resource manager prepare for commitment any work performed */
/*          on behalf of the Transaction Branch Identifier. The resource */
/*          manager places all resources used in the transaction branch  */
/*          in a state that the changes can be made permanently when it  */
/*          later receives the QxdaXACommit() request. The connection    */
/*          does not have to be associated with the transaction in any   */
/*          way.                                                         */
/*                                                                       */
/* Parameters:                                                           */
/*                                                                       */
/*   Connection handle - Input                                           */
/*     The handle number of the connection on which to perform the XA    */
/*     operation. The connection handle must have been generated by the  */
/*     QxdaConnectEDRS API in the current job and activation group.      */
/*                                                                       */
/*   Transaction branch identifier - Input                               */
/*     A pointer to the transaction branch identifier. This identifier   */
/*     is generated by the transaction manager when it starts the        */
/*     transaction branch. The max length is 140 bytes.                  */
/*                                                                       */
/*   Return value - Output                                               */
/*     The return value of the XA operation. The following return codes  */
/*     indicate that the resource manager has rolled back the work done  */
/*     on this transaction branch.                                       */
/*                                                                       */
/*     XA_RBROLLBACK                                                     */
/*     XA_RBCOMMFAIL                                                     */
/*     XA_RBDEADLOCK                                                     */
/*     XA_RBINTEGRITY                                                    */
/*     XA_RBOTHER                                                        */
/*     XA_RBPROTO                                                        */
/*     XA_RBTIMEOUT                                                      */
/*     XA_RBTRANSIENT                                                    */
/*                                                                       */
/*     All other return codes:                                           */
/*                                                                       */
/*     XAER_RMFAIL                                                       */
/*     XAER_PROTO                                                        */
/*     XAER_INVAL                                                        */
/*     XAER_NOTA                                                         */
/*     XAER_RMERR                                                        */
/*     XAER_ASYNC                                                        */
/*     XA_OK                                                             */
/*     XA_RDONLY                                                         */
/*                                                                       */
/*   Flags - Input                                                       */
/*     Indicator of how to perform the XA operation. The following are   */
/*     valid settings of flags:                                          */
/*                                                                       */
/*     TMNOFLAGS: x00000000 Perform the prepare operation normally.      */
/*                                                                       */
/*   Error code - Input/Output                                           */
/*     The structure in which to return error information.  The "Key"    */
/*     field in the Qus_ERRC0200_t structure is an input field.  Also,   */
/*     the "Bytes_Provided" field in both the Qus_ERRC0200_t and Qus_EC_t*/
/*     structures is for input.  The rest of the fields are for Output.  */
/*     See declarations of the Qus_EC_t and Qus_ERRC0200_t structures.   */
/*                                                                       */
/* Error codes: Here is a list of the most common error codes returned   */
/*              from this API:                                           */
/*              Message ID Error Message Text                            */
/*              CPE3418 E Possible APAR condition or hardware failure.   */
/*              CPF3CF2 E Error(s) occurred during running of &1 API.    */
/*              CPF9872 E Program or service program &1 in library &2    */
/*                        ended. Reason code &3.                         */
/*              CPFB760 E Error encountered in &2 API, return code &1.   */
/*                                                                       */
/* Usage Notes:                                                          */
/*   This function may be called from the initial thread of a job only.  */
/*                                                                       */
/*************************************************************************/
void CWB_ENTRY QxdaXAPrepare(
                          int  * connectionHandle,
                          void * transactionBranchIdentifier,
                          int  * returnValue,
                          int  * flags,
                          void * errorCode);


/*************************************************************************/
/* API: QxdaXARollback                                                   */
/*                                                                       */
/* Purpose: A transaction manager calls QxdaXARollback() to roll back    */
/*          work performed on behalf of the transaction branch. A        */
/*          transaction branch is capable of being rolled back until it  */
/*          has been successfully committed. The connection does not     */
/*          have to be associated with the transaction in any way.       */
/*                                                                       */
/* Parameters:                                                           */
/*                                                                       */
/*   Connection handle - Input                                           */
/*     The handle number of the connection on which to perform the XA    */
/*     operation. The connection handle must have been generated by the  */
/*     QxdaConnectEDRS API in the current job and activation group.      */
/*                                                                       */
/*   Transaction branch identifier - Input                               */
/*     A pointer to the transaction branch identifier. This identifier   */
/*     is generated by the transaction manager when it starts the        */
/*     transaction branch. The max length is 140 bytes.                  */
/*                                                                       */
/*   Return value - Output                                               */
/*     The return value of the XA operation. The following return codes  */
/*     indicate that the resource manager rolled back the work done on   */
/*     this transaction branch. These values are typically returned when */
/*     the transaction branch was previously marked rollback-only:       */
/*                                                                       */
/*     XA_RBROLLBACK                                                     */
/*     XA_RBCOMMFAIL                                                     */
/*     XA_RBDEADLOCK                                                     */
/*     XA_RBINTEGRITY                                                    */
/*     XA_RBOTHER                                                        */
/*     XA_RBPROTO                                                        */
/*     XA_RBTIMEOUT                                                      */
/*     XA_RBTRANSIENT                                                    */
/*                                                                       */
/*     All other return codes:                                           */
/*                                                                       */
/*     XAER_RMFAIL                                                       */
/*     XAER_PROTO                                                        */
/*     XAER_INVAL                                                        */
/*     XAER_NOTA                                                         */
/*     XAER_RMERR                                                        */
/*     XAER_ASYNC                                                        */
/*     XA_OK                                                             */
/*     XA_HEURMIX                                                        */
/*     XA_HEURRB                                                         */
/*     XA_HEURCOM                                                        */
/*     XA_HEURHAZ                                                        */
/*                                                                       */
/*   Flags - Input                                                       */
/*     Indicator of how to perform the XA operation. The following are   */
/*     valid settings of flags:                                          */
/*                                                                       */
/*     TMNOFLAGS: x00000000 Perform the rollback operation normally.     */
/*                                                                       */
/*   Error code - Input/Output                                           */
/*     The structure in which to return error information.  The "Key"    */
/*     field in the Qus_ERRC0200_t structure is an input field.  Also,   */
/*     the "Bytes_Provided" field in both the Qus_ERRC0200_t and Qus_EC_t*/
/*     structures is for input.  The rest of the fields are for Output.  */
/*     See declarations of the Qus_EC_t and Qus_ERRC0200_t structures.   */
/*                                                                       */
/* Error codes: Here is a list of the most common error codes returned   */
/*              from this API:                                           */
/*              Message ID Error Message Text                            */
/*              CPE3418 E Possible APAR condition or hardware failure.   */
/*              CPF3CF2 E Error(s) occurred during running of &1 API.    */
/*              CPF9872 E Program or service program &1 in library &2    */
/*                        ended. Reason code &3.                         */
/*              CPFB760 E Error encountered in &2 API, return code &1.   */
/*                                                                       */
/* Usage Notes:                                                          */
/*   This function may be called from the initial thread of a job only.  */
/*                                                                       */
/*************************************************************************/
void CWB_ENTRY QxdaXARollback(
                          int  * connectionHandle,
                          void * transactionBranchIdentifier,
                          int  * returnValue,
                          int  * flags,
                          void * errorCode);


/*************************************************************************/
/* API: QxdaXACommit                                                     */
/*                                                                       */
/* Purpose: A transaction manager calls QxdaXACommit() to commit the work*/
/*          associated with the Transaction Branch Identifier. All       */
/*          changes that were made to resources managed by DB2 UDB for   */
/*          iSeries during the transaction branch are made permanent.    */
/*          The connection does not have to be associated with the       */
/*          transaction in any way.                                      */
/*                                                                       */
/* Parameters:                                                           */
/*                                                                       */
/*   Connection handle - Input                                           */
/*     The handle number of the connection on which to perform the XA    */
/*     operation. The connection handle must have been generated by the  */
/*     QxdaConnectEDRS API in the current job and activation group.      */
/*                                                                       */
/*   Transaction branch identifier - Input                               */
/*     A pointer to the transaction branch identifier. This identifier   */
/*     is generated by the transaction manager when it starts the        */
/*     transaction branch. The max length is 140 bytes.                  */
/*                                                                       */
/*   Return value - Output                                               */
/*     The return value of the XA operation. The following values may be */
/*     returned only if TMONEPHASE(x40000000) was set in the flags       */
/*     parameter:                                                        */
/*                                                                       */
/*     XA_RBROLLBACK                                                     */
/*     XA_RBCOMMFAIL                                                     */
/*     XA_RBDEADLOCK                                                     */
/*     XA_RBINTEGRITY                                                    */
/*     XA_RBOTHER                                                        */
/*     XA_RBPROTO                                                        */
/*     XA_RBTIMEOUT                                                      */
/*     XA_RBTRANSIENT                                                    */
/*                                                                       */
/*     All other return codes:                                           */
/*                                                                       */
/*     XAER_RMFAIL                                                       */
/*     XAER_PROTO                                                        */
/*     XAER_INVAL                                                        */
/*     XAER_NOTA                                                         */
/*     XAER_RMERR                                                        */
/*     XAER_ASYNC                                                        */
/*     XA_OK                                                             */
/*     XA_RETRY                                                          */
/*     XA_HEURMIX                                                        */
/*     XA_HEURRB                                                         */
/*     XA_HEURCOM                                                        */
/*     XA_HEURHAZ                                                        */
/*                                                                       */
/*   Flags - Input                                                       */
/*     Indicator of how to perform the XA operation. The following are   */
/*     valid settings of flags:                                          */
/*                                                                       */
/*     TMNOWAIT: x10000000                                               */
/*     TMONEPHASE: x40000000                                             */
/*     TMNOFLAGS: x00000000                                              */
/*                                                                       */
/*   Error code - Input/Output                                           */
/*     The structure in which to return error information.  The "Key"    */
/*     field in the Qus_ERRC0200_t structure is an input field.  Also,   */
/*     the "Bytes_Provided" field in both the Qus_ERRC0200_t and Qus_EC_t*/
/*     structures is for input.  The rest of the fields are for Output.  */
/*     See declarations of the Qus_EC_t and Qus_ERRC0200_t structures.   */
/*                                                                       */
/* Error codes: Here is a list of the most common error codes returned   */
/*              from this API:                                           */
/*              Message ID Error Message Text                            */
/*              CPE3418 E Possible APAR condition or hardware failure.   */
/*              CPF3CF2 E Error(s) occurred during running of &1 API.    */
/*              CPF9872 E Program or service program &1 in library &2    */
/*                        ended. Reason code &3.                         */
/*              CPFB760 E Error encountered in &2 API, return code &1.   */
/*                                                                       */
/* Usage Notes:                                                          */
/*   This function may be called from the initial thread of a job only.  */
/*                                                                       */
/*************************************************************************/
void CWB_ENTRY QxdaXACommit (
                          int  * connectionHandle,
                          void * transactionBranchIdentifier,
                          int  * returnValue,
                          int  * flags,
                          void * errorCode);


/*************************************************************************/
/* API: QxdaXAForget                                                     */
/*                                                                       */
/* Purpose:  A transaction manager calls QxdaXAForget() to forget about  */
/*           a heuristically completed transaction branch. After this    */
/*           call, the Transaction Branch Identifier is no longer valid. */
/*           The connection does not have to be associated with the      */
/*           transaction in any way.                                     */
/*                                                                       */
/* Parameters:                                                           */
/*                                                                       */
/*   Connection handle - Input                                           */
/*     The handle number of the connection on which to perform the XA    */
/*     operation. The connection handle must have been generated by the  */
/*     QxdaConnectEDRS API in the current job and activation group.      */
/*                                                                       */
/*   Transaction branch identifier - Input                               */
/*     A pointer to the transaction branch identifier. This identifier   */
/*     is generated by the transaction manager when it starts the        */
/*     transaction branch. The max length is 140 bytes.                  */
/*                                                                       */
/*   Return value - Output                                               */
/*     The return value of the XA operation.                             */
/*                                                                       */
/*     XAER_RMFAIL                                                       */
/*     XAER_PROTO                                                        */
/*     XAER_INVAL                                                        */
/*     XAER_NOTA                                                         */
/*     XAER_RMERR                                                        */
/*     XAER_ASYNC                                                        */
/*     XA_OK                                                             */
/*                                                                       */
/*   Flags - Input                                                       */
/*     Indicator of how to perform the XA operation. The following are   */
/*     valid settings of flags:                                          */
/*                                                                       */
/*     TMNOFLAGS: x00000000 Perform the forget operation normally.       */
/*                                                                       */
/*   Error code - Input/Output                                           */
/*     The structure in which to return error information.  The "Key"    */
/*     field in the Qus_ERRC0200_t structure is an input field.  Also,   */
/*     the "Bytes_Provided" field in both the Qus_ERRC0200_t and Qus_EC_t*/
/*     structures is for input.  The rest of the fields are for Output.  */
/*     See declarations of the Qus_EC_t and Qus_ERRC0200_t structures.   */
/*                                                                       */
/* Error codes: Here is a list of the most common error codes returned   */
/*              from this API:                                           */
/*              Message ID Error Message Text                            */
/*              CPE3418 E Possible APAR condition or hardware failure.   */
/*              CPF3CF2 E Error(s) occurred during running of &1 API.    */
/*              CPF9872 E Program or service program &1 in library &2    */
/*                        ended. Reason code &3.                         */
/*              CPFB760 E Error encountered in &2 API, return code &1.   */
/*                                                                       */
/* Usage Notes:                                                          */
/*   This function may be called from the initial thread of a job only.  */
/*                                                                       */
/*************************************************************************/
void CWB_ENTRY QxdaXAForget (
                          int  * connectionHandle,
                          void * transactionBranchIdentifier,
                          int  * returnValue,
                          int  * flags,
                          void * errorCode);


/*************************************************************************/
/* API: QxdaXARecover                                                    */
/*                                                                       */
/* Purpose:  A transaction manager calls QxdaXARecover() during recovery */
/*           to obtain a list of Transaction Branch Identifiers that are */
/*           currently in a prepared or heuristically completed state.   */
/*           Multiple calls to this function can be made in a single     */
/*           recovery scan. The flags parameter defines when a recovery  */
/*           scan should start or end. The connection does not have to   */
/*           be associated with the transaction in any way.              */
/*                                                                       */
/* Parameters:                                                           */
/*                                                                       */
/*   Connection handle - Input                                           */
/*     The handle number of the connection on which to perform the XA    */
/*     operation. The connection handle must have been generated by the  */
/*     QxdaConnectEDRS API in the current job and activation group.      */
/*                                                                       */
/*   Array of transaction branch identifiers  - Output                   */
/*     A pointer to an array into which the resource manager places XIDs,*/
/*     each containing a max size of 140 bytes, for transaction branches */
/*     in prepared or heuristically completed states.                    */
/*                                                                       */
/*   Array entries allocated - Input                                     */
/*     The number of transaction branch identifiers that can be returned */
/*     into the Array of transaction branch identifiers.                 */
/*                                                                       */
/*   Return value - Output                                               */
/*     The return value of the XA operation.                             */
/*                                                                       */
/*     XAER_PROTO                                                        */
/*     XAER_INVAL                                                        */
/*     XAER_RMERR                                                        */
/*     XA_OK                                                             */
/*      >= 0 The total number of XIDs returned in the xids array.        */
/*                                                                       */
/*   Flags - Input                                                       */
/*     Indicator of how to perform the XA operation. The following are   */
/*     valid settings of flags:                                          */
/*                                                                       */
/*     TMSTARTRSCAN: x01000000                                           */
/*     TMENDRSCAN:  x00800000                                            */
/*     TMNOFLAGS: x00000000                                              */
/*                                                                       */
/*   Error code - Input/Output                                           */
/*     The structure in which to return error information.  The "Key"    */
/*     field in the Qus_ERRC0200_t structure is an input field.  Also,   */
/*     the "Bytes_Provided" field in both the Qus_ERRC0200_t and Qus_EC_t*/
/*     structures is for input.  The rest of the fields are for Output.  */
/*     See declarations of the Qus_EC_t and Qus_ERRC0200_t structures.   */
/*                                                                       */
/* Error codes: Here is a list of the most common error codes returned   */
/*              from this API:                                           */
/*              Message ID Error Message Text                            */
/*              CPE3418 E Possible APAR condition or hardware failure.   */
/*              CPF3CF2 E Error(s) occurred during running of &1 API.    */
/*              CPF9872 E Program or service program &1 in library &2    */
/*                        ended. Reason code &3.                         */
/*              CPFB760 E Error encountered in &2 API, return code &1.   */
/*                                                                       */
/* Usage Notes:                                                          */
/*   This function may be called from the initial thread of a job only.  */
/*                                                                       */
/*************************************************************************/
void CWB_ENTRY QxdaXARecover (
                          int  * connectionHandle,
                          void * transactionBranchIdentifierArray,
                          int  * transactionBranchIdentifierArraySize,
                          int  * returnValue,
                          int  * flags,
                          void * errorCode);

/*************************************************************************/
/* API: QxdaSetOptions                                                   */
/*                                                                       */
/* Purpose:  Set options related to XDA.                                 */
/*                                                                       */
/* Parameters:                                                           */
/*                                                                       */
/*   Input structure - Input                                             */
/*     The structure in which to pass information about options to set.  */
/*                                                                       */
/*   Input structure format - Input                                      */
/*     The format of the input structure template being used. The        */
/*     possible value is:                                                */
/*                                                                       */
/*     SETO0100 Set Options structure.  See declaration of the SETO0100  */
/*     format.                                                           */
/*                                                                       */
/*   Error code - Input/Output                                           */
/*     The structure in which to return error information.  See          */
/*     declarations for the Qus_EC_t and Qus_ERRC0200_t structures.      */
/*                                                                       */
/* Error codes: Here is a list of the most common error codes returned   */
/*              from this API:                                           */
/*              Message ID Error Message Text                            */
/*              CPF3C21 E Format name &1 is not valid.                   */
/*              CPFB751 E Parameter &1 passed not correct.               */
/*              CPFB752 E Internal error in &1 API.                      */
/*                                                                       */
/* Usage Notes:                                                          */
/*   This function has been added for cross-platform compatibility.      */
/*   The thread safety setting is not supported on this platform.        */
/*   The trace settings are supported on this platform.                  */
/*                                                                       */
/*************************************************************************/

void CWB_ENTRY QxdaSetOptions(void *,   
                              char *,   
                              void *);  



#if defined( __cplusplus )
}
#endif

/* Define all the structures as packed, so there is a guaranteed
   alignment across any compilers that might use this header.        */
#include "cwbpack1.h"

/********************************************************************/
/* Type Definition for any format that uses Statement Text in       */
/* an extension.                                                    */
/********************************************************************/
typedef struct Qxda_statement_data
{
   short Statement_Length;
   /*char Statement_Text[];*/    /* Varying length                  */
} Qxda_statement_data_t;


/*********************************************************************/
/* Type Definition for the CDBI0100 format for the QxdaConnectEDRS   */
/* API input format.                                                 */
/*                                                                   */
/* NOTE: The following type definition only defines the fixed        */
/*       portion of the format.  Any varying length field will have  */
/*       to be defined by the user.                                  */
/*                                                                   */
/* NOTE 2:  THIS FORMAT CANNOT BE USED FROM THE XDA WORKSTATION      */
/*          CLIENT. IT IS PRESENT ONLY TO ALLOW MULTI-PLATFORM XDA   */
/*          CLIENT CODE TO COMPILE WHEN OBJECTS OF THIS TYPE (AND    */
/*          THEIR FIELDS ARE USED IN THE MULTI-PLATFORM CODE         */
/*********************************************************************/
typedef struct Qxda_CDBI0100
{
   char    Connection_Type;
   char    Commitment_Control;
   char    Commit_Scope[10];
   char    Allow_Suspend;
   char    Server_Name[256];
   char    RDB_Specified;
   char    SQL_Hex_Constants;
   char    Autocommit;
   int     SQLDA_Cache_Size;
   int     Offset_Job_Data;
   int     Length_Job_Data;
   int     Offset_Suspend_Data;
   int     Length_Suspend_Data;
   char    RDB_Name[18];
   char    TM_Info[10];
   int     Locktimeout;
/*char     Job_Data[]; */              /* Variable length            */
/*char     Suspend_Data[]; */          /* Variable length            */
} Qxda_CDBI0100_t;


/*********************************************************************/
/* Type Definition for the CDBI0200 format for the QxdaConnectEDRS   */
/* API input format.                                                 */
/*                                                                   */
/* NOTE: The following type definition only defines the fixed        */
/*       portion of the format.  Any varying length field will have  */
/*       to be defined by the user.                                  */
/*********************************************************************/
typedef struct Qxda_CDBI0200
{
   char    Connection_Type;
   char    Commitment_Control;
   char    Commit_Scope[10];
   char    Allow_Suspend;
   char    Server_Name[256];
   char    Convert_Endian_Data;
   char    RDB_Specified;
   char    SQL_Hex_Constants;
   int     SQLDA_Cache_Size;
   int     Offset_Job_Data;
   int     Length_Job_Data;
   int     Offset_Suspend_Data;
   int     Length_Suspend_Data;
   int     Offset_Profile;
   int     Length_Profile;
   int     Offset_Password;
   int     Length_Password;
   int     Server_Job_CCSID;
   int     Password_CCSID;
   char    RDB_Name[18];
   char    TM_Info[10];
   int     Locktimeout;
/*char     Job_Data[]; */        /* Variable length            */
/*char     Suspend_Data[]; */    /* Variable length            */
/*char     Profile_Data[]; */    /* Variable length            */
/*char     Password_Data[];*/    /* Variable length            */
} Qxda_CDBI0200_t;

/*********************************************************************/
/* Type Definition for the CDBO0100 format for the QxdaConnectEDRS   */
/* API output format.                                                */
/*********************************************************************/
typedef struct Qxda_CDBO0100
{
   int     Bytes_Returned;
   int     Bytes_Available;
   int     Connection_Handle;
   char    Server_Job_Name[10];
   char    Server_User_Name[10];
   char    Server_Job_Number[6];
   char    Connection_Type_Used;
} Qxda_CDBO0100_t;

/*********************************************************************/
/* Type Definition for the EXDO0100 format for the                   */
/* QxdaProcessExtDynEDRS API receiver variable.                      */
/*********************************************************************/
typedef struct Qxda_EXDO0100
{
   int     Bytes_Returned;
   int     Bytes_Available;
   char    Statement_Name[18];
} Qxda_EXDO0100_t;

/*********************************************************************/
/* Type Definition for the Qxda_QJBI0100 structure for the           */
/* QxdaFindEDRSJob API.                                              */
/*********************************************************************/
typedef struct Qxda_QJBI0100
{
   int     pid;
   char    Name[10];
   char    User[10];
   char    Number[6];
   char    JobID[16];
   char    Reserved[2];
} Qxda_QJBI0100_t;

/*********************************************************************/
/* Type Definition for the Qxda_ParmInfo_t structure for the         */
/* QxdaCallProgram API.                                              */
/*********************************************************************/
typedef struct Qxda_ParmInfo
{
   void  *ParmAddr;
   int    ParmType;
   int    ParmLen;
   int    ParmUsage;
   char   Reserved[4];
} Qxda_ParmInfo_t;


/*********************************************************************/
/* Type Definition for the Qxda_CNCL0100 structure for the           */
/* QxdaCancelEDRS API.                                               */
/*********************************************************************/
typedef struct Qxda_CNCL0100
{
   char    Job_Name[10];
   char    Job_User[10];
   char    Job_Number[6];
} Qxda_CNCL0100_t;

/*********************************************************************/
/* The QXDA_SETO0100 structure has been added for cross-platform     */
/* compatibility. The Thread_Safe option is not supported on this    */
/* platform. The trace options are supported on this platform.       */
/*********************************************************************/
typedef struct Qxda_SETO0100
{
   char Thread_Safe;
   char Trace_Mode;
   char Reserved1[2];
   int  Trace_File_Size;
   int  Offset_Trace_Config;
   int  Length_Trace_Config;
   char Reserved2[112];
} Qxda_SETO0100_t;


#ifndef QUSEC_h

 /******************************************************************/
 /* Record structure for Error Code Parameter                      */
 /*                                                                */
 /* NOTE: The following type definition only defines the fixed     */
 /*       portion of the format.  Varying length field Exception   */
 /*       Data will not be defined here.                           */
 /*                                                                */
 /******************************************************************/
typedef struct Qus_EC
{
   int  Bytes_Provided;
   int  Bytes_Available;
   char Exception_Id[7];
   char Reserved;
 /*char Exception_Data[];*/      /* Variable length            */
} Qus_EC_t;

typedef struct Qus_ERRC0200
{
   int Key;
   int Bytes_Provided;
   int Bytes_Available;
   char Exception_Id[7];
   char Reserved;
   int CCSID;
   int Offset_Exc_Data;
   int Length_Exc_Data;
 /*char Exception_Data[];*/      /* Variable length            */
} Qus_ERRC0200_t;
#endif /* QUSEC_h */



/*************************************************************************************/
/* The structures used for the SQL_CommunicationsArea and                            */
/* SQL_DescriptorArea parameters in 1 or more of the XDA APIs.                       */
/* Reference the QSQPRCED API documentation in the IBM Info Center at:               */
/*    http://publib.boulder.ibm.com/pubs/html/as400/infocenter.html                  */
/* Go to the Info Center for your location and language, then search for "QSQPRCED"  */
/* and follow the links.                                                             */
/*************************************************************************************/

typedef struct Qsq_sqlca
{
   unsigned char   sqldaid[8];
   int             sqlcabc;
   int             sqlcode;
   short           sqlerrml;
   unsigned char   sqlerrmc[70];
   unsigned char   sqlerrp[8];
   int             sqlerrd[6];
   unsigned char   sqlwarn[11];
   unsigned char   sqlstate[5];
} Qsq_sqlca_t;

struct sqlname
{
   short         length;
   unsigned char data[30];
};

struct sqlvar
{
   short          sqltype;
   short          sqllen;
   unsigned char  sqlres[12];
   unsigned char  *sqldata;
   short          *sqlind;
   struct         sqlname sqlname;
};

// Increase the size of sqlvar2 on a 64bit platform (Windows or Linux)
// to match the size of sqlvar2. Depend on no compiler specific
// preprocessor value.
struct sqlvar2
{
   struct
   {
     int  sqllonglen;
     char reserve1[16 + (sizeof(void *)-4)];
   } len;
   char *sqldatalen;
   struct
   {
     short length;
     unsigned char data[30];
   } sqldatatype_name;
};


typedef struct Qsq_sqlda
{
   unsigned char sqldaid[8];
   int    sqldabc;
   short  sqln;
   short  sqld;
   struct sqlvar sqlvar[1];
} Qsq_sqlda_t;



/********************************************************************/
/* Type Definition for the SQLP0300 format of the userspace in the  */
/* QSQPRCED API.                                                    */
/*                                                                  */
/* NOTE: The following type definition only defines the fixed       */
/*       portion of the format.  Any varying length field will have */
/*       to be defined by the user.                                 */
/********************************************************************/

typedef struct Qsq_SQLP0300
{
   char Function;
   char SQL_Package_Name[10];
   char Library_Name[10];
   char Main_Pgm[10];            /* not used by Windows clients */
   char Main_Lib[10];            /* not used by Windows clients */
   char Statement_Name[18];
   char Cursor_Name[18];
   char Open_Options;
   char Clause_For_Describe;
   char Commitment_Control;
   char Date_Format[3];
   char Date_Separator;
   char Time_Format[3];
   char Time_Separator;
   char Naming_Option[3];
   char Decimal_Point;
   short  Blocking_Factor;
   short  Scrollable_Option;
   short  Position_Option;
   int  Relative_Record;
   int  Rows_To_Insert;
   char Direct_Map;
   char Reuse_DA;
   char Name_Check;
   char Use_Ptrs;
   char With_Hold;
   char User_Defined_Field[18];
   char Close_File_Name[10];
   char Close_Library_Name[10];
   char Reopen;
   char Use_Perf;
   char Reval;
   char reserved_space[4];
   int  Statement_Text_CCSID;
   _SYSPTR package_syp;          /* not used by Windows clients */
   _SYSPTR main_program_syp;     /* not used by Windows clients */
   short  Statement_Length;
 /*char Statement_Text[];*/      /* Variable length            */
} Qsq_SQLP0300_t;

/********************************************************************/
/* Type Definition for the SQLP0310 format of the userspace         */
/*  in the QSQPRCED API.                                            */
/*                                                                  */
/* NOTE: The following type definition only defines the fixed       */
/*       portion of the format.  Any varying length field will have */
/*       to be defined by the user. By using the Statement_Offset,  */
/*       the Qxda_statement_data_t Text would not be required to    */
/*       immediately follow the fixed portion of the format.        */
/********************************************************************/
typedef struct Qsq_SQLP0310
{
    char Function;
    char SQL_Package_Name[10];
    char Library_Name[10];
    char Main_Pgm[10];
    char Main_Lib[10];
    char Statement_Name[18];
    char Cursor_Name[18];
    char Open_Options;
    char Clause_For_Describe;
    char Commitment_Control;
    char Date_Format[3];
    char Date_Separator;
    char Time_Format[3];
    char Time_Separator;
    char Naming_Option[3];
    char Decimal_Point;
    short  Blocking_Factor;
    short  Scrollable_Option;
    short  Position_Option;
    int  Relative_Record;
    int  Rows_To_Insert;
    char Direct_Map;
    char Reuse_DA;
    char Name_Check;
    char Use_Ptrs;
    char With_Hold;
    char User_Defined_Field[18];
    char Close_File_Name[10];
    char Close_Library_Name[10];
    char Reopen;
    char Use_Perf;
    char Reval;
    unsigned short int Max_Scale;
    char Max_Precision;
    char Min_Divide_Scale;
    int  Statement_Text_CCSID;
    _SYSPTR package_syp;
    _SYSPTR main_program_syp;
    int  Statement_Offset;
    char Hex_Literal_Option;
    char Statement_Length_Type;   
    unsigned short Ext_User_Defined_Field_Length;   
    int  Ext_User_Defined_Field_Offset;         
    char Reserved_Space[4];      
    /*Qxda_statement_data_t Text;*//* Varying length */
}Qsq_SQLP0310_t;



/********************************************************************/
/* Type Definition for the SQLP0400 format of the userspace in the  */
/* QSQPRCED API.                                                    */
/*                                                                  */
/* NOTE: The following type definition only defines the fixed       */
/*       portion of the format.  Any varying length field will have */
/*       to be defined by the user.                                 */
/********************************************************************/

typedef struct Qsq_SQLP0400
{
   char Function;
   char SQL_Package_Name[10];
   char Library_Name[10];
   char Main_Pgm[10];            /* not used by Windows clients */
   char Main_Lib[10];            /* not used by Windows clients */
   char Statement_Name[18];
   char Cursor_Name[18];
   char Open_Options;
   char Clause_For_Describe;
   char Commitment_Control;
   char Date_Format[3];
   char Date_Separator;
   char Time_Format[3];
   char Time_Separator;
   char Naming_Option[3];
   char Decimal_Point;
   short  Blocking_Factor;
   short  Scrollable_Option;
   short  Position_Option;
   int  Relative_Record;
   int  Rows_To_Insert;
   char Direct_Map;
   char Reuse_DA;
   char Name_Check;
   char Use_Ptrs;
   char With_Hold;
   char User_Defined_Field[18];
   char Close_File_Name[10];
   char Close_Library_Name[10];
   char Reopen;
   char Use_Perf;
   char Reval;
   char reserved_space[4];
   int  Statement_Text_CCSID;
   _SYSPTR package_syp;          /* not used by Windows clients */
   _SYSPTR main_program_syp;     /* not used by Windows clients */
   char Sort_Sequence_Table[10];
   char Sort_Sequence_Library[10];
   char Language_ID[10];
   char Allow_Copy_Data;
   char Allow_Blocking;
   short  Statement_Length;
 /*char Statement_Text[];*/      /* Variable length            */
} Qsq_SQLP0400_t;


/********************************************************************/
/* Type Definition for the SQLP0400 extended format of the userspace*/
/* in the QSQPRCED API.                                             */
/*                                                                  */
/* NOTE: The following type definition only defines the fixed       */
/*       portion of the format.  Any varying length field will have */
/*       to be defined by the user. By using the Statement_Offset,  */
/*       the Qxda_statement_data_t Text would not be required to    */
/*       immediately follow the fixed portion of the format.        */
/********************************************************************/
typedef struct Qsq_SQLP0410
{
    char Function;
    char SQL_Package_Name[10];
    char Library_Name[10];
    char Main_Pgm[10];
    char Main_Lib[10];
    char Statement_Name[18];
    char Cursor_Name[18];
    char Open_Options;
    char Clause_For_Describe;
    char Commitment_Control;
    char Date_Format[3];
    char Date_Separator;
    char Time_Format[3];
    char Time_Separator;
    char Naming_Option[3];
    char Decimal_Point;
    short  Blocking_Factor;
    short  Scrollable_Option;
    short  Position_Option;
    int  Relative_Record;
    int  Rows_To_Insert;
    char Direct_Map;
    char Reuse_DA;
    char Name_Check;
    char Use_Ptrs;
    char With_Hold;
    char User_Defined_Field[18];
    char Close_File_Name[10];
    char Close_Library_Name[10];
    char Reopen;
    char Use_Perf;
    char Reval;
    unsigned short int Max_Scale;
    char Max_Precision;
    char Min_Divide_Scale;
    int  Statement_Text_CCSID;
    _SYSPTR package_syp;
    _SYSPTR main_program_syp;
    char Sort_Sequence_Table[10];
    char Sort_Sequence_Library[10];
    char Language_ID[10];
    char Allow_Copy_Data;
    char Allow_Blocking;
    int  Statement_Offset;
    char Hex_Literal_Option;
    char Statement_Length_Type;   
    unsigned short Ext_User_Defined_Field_Length;  
    int  Ext_User_Defined_Field_Offset;           
    char Reserved_Space[4];     
    /*Qxda_statement_data_t Text;*//* Varying length */
}Qsq_SQLP0410_t;



#include "cwbpack0.h"                  /* return to unpacked structures */

#endif   /* _QXDAEDRSNT_H_ */

