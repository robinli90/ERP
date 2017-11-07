/*****************************************************************************/
/*                                                                           */
/*  Module Name     : EHLAPI32.H                                             */
/*                                                                           */
/*  Description     : EHLLAPI Structure, Return Codes and Routines           */
/*                                                                           */
/*  Copyright Notice: IBM Personal Communication/3270 Version 4.3            */
/*                    (C) COPYRIGHT IBM CORP. 1989,1995 - PROGRAM PROPERTY   */
/*                    OF IBM ALL RIGHTS RESERVED                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*  Function:                                                                */
/*                                                                           */
/*    Define the EHLLAPI structure, return code constants and                */
/*    the external routines for EHLLAPI.                                     */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Change Activity:                                                          */
/*                                                                           */
/* DCRs                                                                      */
/* ==========================================================================*/
/*       dcrnum   rls   date     name description of change                  */
/* @BD1  fp000011 600   012301   MM   Add Hllapi call for Query Additional   */
/*                                    Field Attributes                       */
/* @BD2  Def81383 5.5   062602   Supriya  Connect SF return 9 due to padding */
/*                                        in 16-bit Structures               */
/*****************************************************************************/
#ifndef EHLAPI32_HEAD
#define EHLAPI32_HEAD

#ifdef __cplusplus
  extern "C" {
#endif

#pragma pack(1)                                                        //@BD2a

/*********************************************************************/
/**************** EHLLAPI FUNCTION PROTOTYPES ************************/
/*********************************************************************/
extern long far pascal HLLAPI(WORD*, LPSTR, WORD*, WORD*);
extern long far pascal hllapi(WORD*, LPSTR, WORD*, WORD*);

#include "hllstr16.h"                   /* EHLAPI struct definitions */

/*********************************************************************/
/**************** EHLLAPI FUNCTION NUMBERS ***************************/
/*********************************************************************/
#define HA_CONNECT_PS            1      /* 000 Connect PS            */
#define HA_DISCONNECT_PS         2      /* 000 Disconnect PS         */
#define HA_SENDKEY               3      /* 000 Sendkey function      */
#define HA_WAIT                  4      /* 000 Wait function         */
#define HA_COPY_PS               5      /* 000 Copy PS function      */
#define HA_SEARCH_PS             6      /* 000 Search PS function    */
#define HA_QUERY_CURSOR_LOC      7      /* 000 Query Cursor          */
#define HA_COPY_PS_TO_STR        8      /* 000 Copy PS to String     */
#define HA_SET_SESSION_PARMS     9      /* 000 Set Session           */
#define HA_QUERY_SESSIONS        10     /* 000 Query Sessions        */
#define HA_RESERVE               11     /* 000 Reserve function      */
#define HA_RELEASE               12     /* 000 Release function      */
#define HA_COPY_OIA              13     /* 000 Copy OIA function     */
#define HA_QUERY_FIELD_ATTR      14     /* 000 Query Field           */
#define HA_COPY_STR_TO_PS        15     /* 000 Copy string to PS     */
#define HA_STORAGE_MGR           17     /* 000 Storage Manager       */
#define HA_PAUSE                 18     /* 000 Pause function        */
#define HA_QUERY_SYSTEM          20     /* 000 Query System          */
#define HA_RESET_SYSTEM          21     /* 000 Reset System          */
#define HA_QUERY_SESSION_STATUS  22     /* 000 Query Session         */
#define HA_START_HOST_NOTIFY     23     /* 000 Start Host            */
#define HA_QUERY_HOST_UPDATE     24     /* 000 Query Host Update     */
#define HA_STOP_HOST_NOTIFY      25     /* 000 Stop Host             */
#define HA_SEARCH_FIELD          30     /* 000 Search Field          */
#define HA_FIND_FIELD_POS        31     /* 000 Find Field            */
#define HA_FIND_FIELD_LEN        32     /* 000 Find Field Length     */
#define HA_COPY_STR_TO_FIELD     33     /* 000 Copy String to        */
#define HA_COPY_FIELD_TO_STR     34     /* 000 Copy Field to         */
#define HA_SET_CURSOR            40     /* 000 Set Cursor            */
#define HA_START_CLOSE_INTERCEPT 41     /* 000 Start Close Intercept */
#define HA_QUERY_CLOSE_INTERCEPT 42     /* 000 Query Close Intercept */
#define HA_STOP_CLOSE_INTERCEPT  43     /* 000 Stop Close Intercept  */
#define HA_QUERY_ADD_FIELD_ATTR  45     /* 000 Additional Query Field*/ //BD1a 
#define HA_START_KEY_INTERCEPT   50     /* 000 Start Keystroke       */
#define HA_GET_KEY               51     /* 000 Get Key function      */
#define HA_POST_INTERCEPT_STATUS 52     /* 000 Post Intercept        */
#define HA_STOP_KEY_INTERCEPT    53     /* 000 Stop Keystroke        */
#define HA_LOCK_PS               60     /* 000 Lock Presentation     */
#define HA_LOCK_PMSVC            61     /* 000 Lock PM Window        */
#define HA_SEND_FILE             90     /* 000 Send File function    */
#define HA_RECEIVE_FILE          91     /* 000 Receive file          */
#define HA_CONVERT_POS_ROW_COL   99     /* 000 Convert Position      */
#define HA_CONNECT_PM_SRVCS     101     /* 000 Connect For           */
#define HA_DISCONNECT_PM_SRVCS  102     /* 000 Disconnect From       */
#define HA_QUERY_WINDOW_COORDS  103     /* 000 Query Presentation    */
#define HA_PM_WINDOW_STATUS     104     /* 000 PM Window Status      */
#define HA_CHANGE_SWITCH_NAME   105     /* 000 Change Switch List    */
#define HA_CHANGE_WINDOW_NAME   106     /* 000 Change PS Window      */
#define HA_START_PLAYING_MACRO  110     /* 000 Start playing macro   */
#define HA_START_STRUCTURED_FLD 120     /* 000 Start Structured      */
#define HA_STOP_STRUCTURED_FLD  121     /* 000 Stop Structured       */
#define HA_QUERY_BUFFER_SIZE    122     /* 000 Query Communications  */
#define HA_ALLOCATE_COMMO_BUFF  123     /* 000 Allocate              */
#define HA_FREE_COMMO_BUFF      124     /* 000 Free Communications   */
#define HA_GET_ASYNC_COMPLETION 125     /* 000 Get Asynchronous      */
#define HA_READ_STRUCTURED_FLD  126     /* 000 Read Structured Field */
#define HA_WRITE_STRUCTURED_FLD 127     /* 000 Write Structured      */

/*********************************************************************/
/******************** EHLLAPI RETURN CODES ***************************/
/*********************************************************************/
#define HARC_SUCCESS               0    /* 000 Good return code.     */
#define HARC99_INVALID_INP         0    /* 000 Incorrect input       */
#define HARC_INVALID_PS            1    /* 000 Invalid PS, Not       */
#define HARC_BAD_PARM              2    /* 000 Bad parameter, or     */
#define HARC_BUSY                  4    /* 000 PS is busy return     */
#define HARC_LOCKED                5    /* 000 PS is LOCKed, or      */
#define HARC_TRUNCATION            6    /* 000 Truncation            */
#define HARC_INVALID_PS_POS        7    /* 000 Invalid PS            */
#define HARC_NO_PRIOR_START        8    /* 000 No prior start        */
#define HARC_SYSTEM_ERROR          9    /* 000 A system error        */
#define HARC_UNSUPPORTED           10   /* 000 Invalid or            */
#define HARC_UNAVAILABLE           11   /* 000 Resource is           */
#define HARC_SESSION_STOPPED       12   /* 000 Session has           */
#define HARC_BAD_MNEMONIC          20   /* 000 Illegal mnemonic      */
#define HARC_OIA_UPDATE            21   /* 000 A OIA update          */
#define HARC_PS_UPDATE             22   /* 000 A PS update           */
#define HARC_PS_AND_OIA_UPDATE     23   /* A PS and OIA update       */
#define HARC_STR_NOT_FOUND_UNFM_PS 24   /* 000 String not found,     */
#define HARC_NO_KEYS_AVAIL         25   /* 000 No keys available     */
#define HARC_HOST_UPDATE           26   /* 000 A HOST update         */
#define HARC_FIELD_LEN_ZERO        28   /* 000 Field length = 0      */
#define HARC_QUEUE_OVERFLOW        31   /* 000 Keystroke queue       */
#define HARC_ANOTHER_CONNECTION    32   /* 000 Successful. Another   */
#define HARC_INBOUND_CANCELLED     34   /* 000 Inbound structured    */
#define HARC_OUTBOUND_CANCELLED    35   /* 000 Outbound structured   */
#define HARC_CONTACT_LOST          36   /* 000 Contact with the      */
#define HARC_INBOUND_DISABLED      37   /* 000 Host structured field */
#define HARC_FUNCTION_INCOMPLETE   38   /* 000 Requested Asynchronous*/
#define HARC_DDM_ALREADY_EXISTS    39   /* 000 Request for DDM       */
#define HARC_ASYNC_REQUESTS_OUT    40   /* 000 Disconnect successful.*/
#define HARC_MEMORY_IN_USE         41   /* 000 Memory cannot be freed*/
#define HARC_NO_MATCH              42   /* 000 No pending            */
#define HARC_OPTION_INVALID        43   /* 000 Option requested is   */
#define HARC99_INVALID_PS        9998   /* 000 An invalid PS id      */
#define HARC99_INVALID_CONV_OPT  9999   /* 000 Invalid convert       */

#ifdef __cplusplus
  }
#endif

#endif // #ifdef EHLAPI32_HEAD
