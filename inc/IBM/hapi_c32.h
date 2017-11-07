/*****************************************************************************/
/*                                                                           */
/*  Module Name     : HAPI_C32.H                                             */
/*                                                                           */
/*  Description     : 32 Bit HLLAPI Structure, Return Codes and Routines     */
/*                                                                           */
/*  Copyright Notice: IBM Personal Communication/3270 Version 4.1            */
/*                    (C) COPYRIGHT IBM CORP. 1989,1995 - PROGRAM PROPERTY   */
/*                    OF IBM ALL RIGHTS RESERVED                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*  Function:                                                                */
/*                                                                           */
/*    Define the 32 Bit HLLAPI structure, return code constants and          */
/*    the external routines HLLAPI.                                          */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Change Activity:                                                          */
/*                                                                           */
/* DCRs                                                                      */
/* ==========================================================================*/
/*       dcrnum   rls   date     name description of change                  */
/* @BD1  fp000011 600   012301   MM   Add Hllapi call for Query Additional   */
/*                                    Field Attributes                       */
/*****************************************************************************/
#ifdef __cplusplus
  extern "C" {
#endif

#ifndef  HLLAPI_C_INCLUDED
#define  HLLAPI_C_INCLUDED
#endif

/* Packing will be returned to default at the end of this file */
#pragma pack(1) 

#define ord_hllapi  3

long WINAPI hllapi(LPINT, LPSTR, LPINT, LPINT);

#include "hllstr32.h"                   /* 32 bit structure defs    */

/*********************************************************************/
/**************** EHLLAPI FUNCTION NUMBERS ***************************/
/*********************************************************************/

#define HA_CONNECT_PS            1      /* 000 Connect PS            */
                                        /* function number.          */

#define HA_DISCONNECT_PS         2      /* 000 Disconnect PS         */
                                        /* function number.          */

#define HA_SENDKEY               3      /* 000 Sendkey function      */
                                        /* number.                   */

#define HA_WAIT                  4      /* 000 Wait function         */
                                        /* number.                   */

#define HA_COPY_PS               5      /* 000 Copy PS function      */
                                        /* number.                   */

#define HA_SEARCH_PS             6      /* 000 Search PS function    */
                                        /* number.                   */

#define HA_QUERY_CURSOR_LOC      7      /* 000 Query Cursor          */
                                        /* Location function         */
                                        /* number.                   */

#define HA_COPY_PS_TO_STR        8      /* 000 Copy PS to String     */
                                        /* function number.          */

#define HA_SET_SESSION_PARMS     9      /* 000 Set Session           */
                                        /* Parameters function       */
                                        /* number.                   */

#define HA_QUERY_SESSIONS        10     /* 000 Query Sessions        */
                                        /* function number.          */

#define HA_RESERVE               11     /* 000 Reserve function      */
                                        /* number.                   */

#define HA_RELEASE               12     /* 000 Release function      */
                                        /* number.                   */


#define HA_COPY_OIA              13     /* 000 Copy OIA function     */
                                        /* number.                   */

#define HA_QUERY_FIELD_ATTR      14     /* 000 Query Field           */
                                        /* Attribute function        */
                                        /* number.                   */

#define HA_COPY_STR_TO_PS        15     /* 000 Copy string to PS     */
                                        /* function number.          */

#define HA_GET_NLS_INFORMATION   16     /* Get NLS Information Funct */

#define HA_STORAGE_MGR           17     /* 000 Storage Manager       */
                                        /* function number.          */

#define HA_PAUSE                 18     /* 000 Pause function        */
                                        /* number.                   */

#define HA_QUERY_SYSTEM          20     /* 000 Query System          */
                                        /* function number.          */

#define HA_RESET_SYSTEM          21     /* 000 Reset System          */
                                        /* function number.          */

#define HA_QUERY_SESSION_STATUS  22     /* 000 Query Session         */
                                        /* Status function           */
                                        /* number.                   */

#define HA_START_HOST_NOTIFY     23     /* 000 Start Host            */
                                        /* Notification function     */
                                        /* number.                   */

#define HA_QUERY_HOST_UPDATE     24     /* 000 Query Host Update     */
                                        /* function number.          */

#define HA_STOP_HOST_NOTIFY      25     /* 000 Stop Host             */
                                        /* Notification function     */
                                        /* number.                   */

#define HA_SEARCH_FIELD          30     /* 000 Search Field          */
                                        /* function number.          */

#define HA_FIND_FIELD_POS        31     /* 000 Find Field            */
                                        /* Position function         */
                                        /* number.                   */

#define HA_FIND_FIELD_LEN        32     /* 000 Find Field Length     */
                                        /* function number.          */

#define HA_COPY_STR_TO_FIELD     33     /* 000 Copy String to        */
                                        /* Field function number.    */

#define HA_COPY_FIELD_TO_STR     34     /* 000 Copy Field to         */
                                        /* String function           */
                                        /* number.                   */

#define HA_SET_CURSOR            40     /* 000 Set Cursor            */
                                        /* function number.          */

#define HA_START_CLOSE_INTERCEPT 41     /* 000 Start Close Intercept */
                                        /* function number.          */

#define HA_QUERY_CLOSE_INTERCEPT 42     /* 000 Query Close Intercept */
                                        /* function number.          */

#define HA_STOP_CLOSE_INTERCEPT  43     /* 000 Stop Close Intercept  */
                                        /* function number.          */

#define HA_QUERY_ADD_FIELD_ATTR  45     /* 000 Query additional 5250 */ //BD1a
                                        /* Field attributes          */ //BD1a 
                                        /* function number.          */	//BD1a 

#define HA_START_KEY_INTERCEPT   50     /* 000 Start Keystroke       */
                                        /* Intercept function        */
                                        /* number.                   */

#define HA_GET_KEY               51     /* 000 Get Key function      */
                                        /* number.                   */

#define HA_POST_INTERCEPT_STATUS 52     /* 000 Post Intercept        */
                                        /* Status function           */
                                        /* number.                   */

#define HA_STOP_KEY_INTERCEPT    53     /* 000 Stop Keystroke        */
                                        /* Intercept function        */
                                        /* number.                   */

#define HA_LOCK_PS               60     /* 000 Lock Presentation     */
                                        /* Space function            */
                                        /* number.                   */

#define HA_LOCK_PMSVC            61     /* 000 Lock PM Window        */
                                        /* Services function         */
                                        /* number.                   */

#define HA_SEND_FILE             90     /* 000 Send File function    */
                                        /* number.                   */

#define HA_RECEIVE_FILE          91     /* 000 Receive file          */
                                        /* function number.          */

#define HA_CONVERT_POS_ROW_COL   99     /* 000 Convert Position      */
                                        /* or Row Column function    */
                                        /* number.                   */

#define HA_CONNECT_PM_SRVCS     101     /* 000 Connect For           */
                                        /* Presentation Manager      */
                                        /* Window Services function  */
                                        /* number                    */

#define HA_DISCONNECT_PM_SRVCS  102     /* 000 Disconnect From       */
                                        /* Presentation Manager      */
                                        /* Window Services function  */
                                        /* number                    */

#define HA_QUERY_WINDOW_COORDS  103     /* 000 Query Presentation    */
                                        /* Manager Window            */
                                        /* Coordinates function      */
                                        /* number                    */

#define HA_PM_WINDOW_STATUS     104     /* 000 PM Window Status      */
                                        /* function number           */

#define HA_CHANGE_SWITCH_NAME   105     /* 000 Change Switch List    */
                                        /* Logical Terminal name     */
                                        /* function number           */

#define HA_CHANGE_WINDOW_NAME   106     /* 000 Change PS Window      */
                                        /* Name function number      */

#define HA_START_PLAYING_MACRO  110     /* 000 Start playing macro   */
                                        /* function                  */

#define HA_START_STRUCTURED_FLD 120     /* 000 Start Structured      */
                                        /* Field function number     */

#define HA_STOP_STRUCTURED_FLD  121     /* 000 Stop Structured       */
                                        /* Field function number     */

#define HA_QUERY_BUFFER_SIZE    122     /* 000 Query Communications  */
                                        /* Buffer Size function      */
                                        /* number                    */

#define HA_ALLOCATE_COMMO_BUFF  123     /* 000 Allocate              */
                                        /* Communications Buffer     */
                                        /* function number           */

#define HA_FREE_COMMO_BUFF      124     /* 000 Free Communications   */
                                        /* Buffer function number    */

#define HA_GET_ASYNC_COMPLETION 125     /* 000 Get Asynchronous      */
                                        /* Completion Request        */
                                        /* function                  */

#define HA_READ_STRUCTURED_FLD  126     /* 000 Read Structured Field */
                                        /* function number           */

#define HA_WRITE_STRUCTURED_FLD 127     /* 000 Write Structured      */
                                        /* Field function number     */


/*********************************************************************/
/******************** EHLLAPI RETURN CODES ***************************/
/*********************************************************************/


#define HARC_SUCCESS               0    /* 000 Good return code.     */

#define HARC99_INVALID_INP         0    /* 000 Incorrect input       */
                                        /* for Convert Position      */
                                        /* or RowCol(99).            */

#define HARC_INVALID_PS            1    /* 000 Invalid PS, Not       */
                                        /* connected return code.    */

#define HARC_BAD_PARM              2    /* 000 Bad parameter, or     */
                                        /* verb not supported        */
                                        /* return code.              */

#define HARC_BUSY                  4    /* 000 PS is busy return     */
                                        /* code.                     */

#define HARC_LOCKED                5    /* 000 PS is LOCKed, or      */
                                        /* invalid keystroke         */
                                        /* return code.              */

#define HARC_TRUNCATION            6    /* 000 Truncation            */
                                        /* occured, or invalid       */
                                        /* length return code.       */

#define HARC_INVALID_PS_POS        7    /* 000 Invalid PS            */
                                        /* position return code.     */

#define HARC_NO_PRIOR_START        8    /* 000 No prior start        */
                                        /* keystroke int. or host    */
                                        /* notify return code.       */

#define HARC_SYSTEM_ERROR          9    /* 000 A system error        */
                                        /* occured return code.      */

#define HARC_UNSUPPORTED           10   /* 000 Invalid or            */
                                        /* unsupported function      */
                                        /* number return code.       */

#define HARC_UNAVAILABLE           11   /* 000 Resource is           */
                                        /* unavalible at this        */
                                        /* time return code.         */

#define HARC_SESSION_STOPPED       12   /* 000 Session has           */
                                        /* been stopped              */

#define HARC_BAD_MNEMONIC          20   /* 000 Illegal mnemonic      */
                                        /* return code.              */

#define HARC_OIA_UPDATE            21   /* 000 A OIA update          */
                                        /* occurred return code.     */

#define HARC_PS_UPDATE             22   /* 000 A PS update           */
                                        /* occurred return code.     */

#define HARC_PS_AND_OIA_UPDATE     23   /* A PS and OIA update       */
                                        /* occurred return code.     */

#define HARC_STR_NOT_FOUND_UNFM_PS 24   /* 000 String not found,     */
                                        /* or Unformated PS          */
                                        /* return code.              */

#define HARC_NO_KEYS_AVAIL         25   /* 000 No keys available     */
                                        /* return code.              */

#define HARC_HOST_UPDATE           26   /* 000 A HOST update         */
                                        /* occurred return code.     */

#define HARC_FIELD_LEN_ZERO        28   /* 000 Field length = 0      */
                                        /* return code.              */

#define HARC_QUEUE_OVERFLOW        31   /* 000 Keystroke queue       */
                                        /* overflow return code.     */

#define HARC_ANOTHER_CONNECTION    32   /* 000 Successful. Another   */
                                        /* Structured Field          */
                                        /* connection to this        */
                                        /* session concurrently      */
                                        /* exists.                   */

#define HARC_INBOUND_CANCELLED     34   /* 000 Inbound structured    */
                                        /* field cancelled.          */

#define HARC_OUTBOUND_CANCELLED    35   /* 000 Outbound structured   */
                                        /* field cancelled.          */

#define HARC_CONTACT_LOST          36   /* 000 Contact with the      */
                                        /* Host was lost.            */

#define HARC_INBOUND_DISABLED      37   /* 000 Host structured field */
                                        /* state is inbound disabled.*/

#define HARC_FUNCTION_INCOMPLETE   38   /* 000 Requested Asynchronous*/
                                        /* function has not completed*/

#define HARC_DDM_ALREADY_EXISTS    39   /* 000 Request for DDM       */
                                        /* structured field connect  */
                                        /* failed because another    */
                                        /* DDM connection to this    */
                                        /* session already exists.   */

#define HARC_ASYNC_REQUESTS_OUT    40   /* 000 Disconnect successful.*/
                                        /* Pending asynchronous      */
                                        /* requests pending.         */

#define HARC_MEMORY_IN_USE         41   /* 000 Memory cannot be freed*/
                                        /* because it is in use.     */

#define HARC_NO_MATCH              42   /* 000 No pending            */
                                        /* asynchronous request meet */
                                        /* supplied criterion.       */

#define HARC_OPTION_INVALID        43   /* 000 Option requested is   */
                                        /* invalid at this time.     */

#define HARC99_INVALID_PS        9998   /* 000 An invalid PS id      */
                                        /* was specified, or PS      */
                                        /* was never connected, or   */
                                        /* System Error occured      */
                                        /* for Convert Position      */
                                        /* or RowCol(99).            */

#define HARC99_INVALID_CONV_OPT  9999   /* 000 Invalid convert       */
                                        /* option was specified.     */
                                        /* for Convert Position      */
                                        /* or RowCol(99).            */

#pragma pack() /* Return to default alignment packing */

#ifdef __cplusplus
  }
#endif
