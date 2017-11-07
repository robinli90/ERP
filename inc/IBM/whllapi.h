/*****************************************************************************/
/*                                                                           */
/*  Module Name     : WHLLAPI.H                                              */
/*                                                                           */
/*  Description     : WinHLLAPI Structure, Return Codes and Routines         */
/*                                                                           */
/*  Copyright Notice: IBM Personal Communication/3270 Version 4.3            */
/*                    (C) COPYRIGHT IBM CORP. 1989,1995 - PROGRAM PROPERTY   */
/*                    OF IBM ALL RIGHTS RESERVED                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*  Function:                                                                */
/*                                                                           */
/*    Define the WinHLLAPI structure, return code constants and              */
/*    the external routines for WinHLLAPI.                                   */
/*                                                                           */
/*****************************************************************************/
#ifndef WHLLAPI_HEAD
#define WHLLAPI_HEAD

#ifdef __cplusplus
  extern "C" {
#endif

#define WHLLDESCRIPTION_LEN            127

typedef struct tagWHLLAPIDATA
{
    WORD    wVersion;
    char    szDescription[WHLLDESCRIPTION_LEN + 1];
} WHLLAPIDATA, * PWHLLAPIDATA, FAR * LPWHLLAPIDATA;

/*************************************************************************/
/******************** WinHLLAPI FUNCTION PROTOTYPES **********************/
/*************************************************************************/
extern void far pascal     WinHLLAPI(LPWORD , LPBYTE , LPWORD , LPWORD );
extern HANDLE far pascal   WinHLLAPIAsync(HWND, LPWORD, LPBYTE, LPWORD, LPWORD);
extern HANDLE far pascal   WinAsyncHLLAPI(HWND, LPWORD, LPBYTE, LPWORD, LPWORD);
extern BOOL far pascal     WinHLLAPICancelAsyncRequest(WORD, WORD);
extern int far pascal      WinHLLAPICancelBlockingCall(void);
extern int far pascal      WinHLLAPICleanup(void);
extern BOOL far pascal     WinHLLAPIIsBlocking(void);
extern FARPROC far pascal  WinHLLAPISetBlockingHook(FARPROC);
extern int far pascal      WinHLLAPIStartup(WORD, LPWHLLAPIDATA);
extern BOOL far pascal     WinHLLAPIUnhookBlockingHook(void);

/*************************************************************************/
/******************* WinHLLAPI STRUCTURE DEFINITIONS *********************/
/*************************************************************************/
/*********************************************************************/
/*                     Connect for Presentation Services (1)         */
/*********************************************************************/

struct HLDConnectPS                     /* 000 Connect For           */
                                        /* Presentation              */
                                        /* Services structure        */
{
  unsigned char stps_shortname;         /* 000 Session Shortname     */
}
;                                       /* 000                       */

/*********************************************************************/
/*                     Query Sessions (10)                           */
/*********************************************************************/

struct HLDQuerySessions                 /* 000 Query Sessions        */
                                        /* structure                 */
{
  unsigned char qses_shortname;         /* 000 Session Shortname     */
  unsigned char qses_longname[8];       /* 000 Session Longname      */
  unsigned char qses_sestype;           /* 000 Session Type          */
  unsigned short int qses_pssize;       /* 000 Presentation Space    */
                                        /* Size.                     */
}
;                                       /* 000                       */

/*********************************************************************/
/*                         Copy OIA (13)                             */
/*********************************************************************/

struct HLDCopyOIA                       /* 000 Copy OIA structure    */
{
  unsigned char coia_format;            /* 000 The OIA Format        */
                                        /* Byte for the 3270 PC.     */

  unsigned char coia_image[80];         /* 000 The OIA image         */

  unsigned char coia_group[22];         /* 000 The OIA group         */
}
;                                       /* 000                       */

/*********************************************************************/
/*                     Storage Manager (17)                          */
/*********************************************************************/

struct HLDStorageMgr                    /* 000 Storage Manager       */
                                        /* structure.                */
{
  unsigned char far * stor_ptr;         /* 000 4 byte pointer to     */
                                        /* memory.                   */
}
;                                       /* 000                       */

/*********************************************************************/
/*                     Pause (18)                                    */
/*********************************************************************/

struct HLDPause                         /* 000 Pause                 */
                                        /* structure.                */
{
  unsigned char paus_shortname;         /* 000 Session Shortname     */
  unsigned char paus_singleses;         /* 000 Single session        */
                                        /* indicater                 */
}
;                                       /* 000                       */

/*********************************************************************/
/*                     Query System (20)                             */
/*********************************************************************/

struct HLDQuerySystem                   /* 000 Query System          */
                                        /* structure                 */
{
  unsigned char qsys_hllapi_ver;        /* 000 Ehllapi version       */
  unsigned char qsys_hllapi_lvl[2];     /* 000 Ehllapi level         */
  unsigned char qsys_hllapi_date[6];    /* 000 Ehllapi release       */
                                        /* date                      */
  unsigned char qsys_lim_ver;           /* 000 LIM version           */
  unsigned char qsys_lim_lvl[2];        /* 000 LIM level             */
  unsigned char qsys_hardware_base;     /* 000 Hardware base         */
  unsigned char qsys_ctrl_prog_type;    /* 000 Control program       */
                                        /* type                      */
  unsigned char qsys_seq_num[2];        /* 000 Sequence number       */
  unsigned char qsys_ctrl_prog_ver[2];  /* 000 Control program       */
                                        /* version                   */
  unsigned char qsys_pc_sname;          /* 000 Base pc session       */
                                        /* name                      */
  unsigned char qsys_err1[4];           /* 000 System error words    */
                                        /* and 2                     */
  unsigned char qsys_err2[4];           /* 000 System error words    */
                                        /* and 4                     */
  unsigned char qsys_sys_model;         /* 000 System model          */
  unsigned char qsys_sys_submodel;      /* 000 System submodel       */
  unsigned short qsys_pc_nls;           /* 000 Pc code page          */
  unsigned char qsys_monitor_type;      /* 000 Monitor type          */
  unsigned char qsys_reserved[3];       /* 000 RESERVED              */
}
;                                       /* 000                       */

/*********************************************************************/
/*                     Query Session Status (22)                     */
/*********************************************************************/

struct HLDQuerySessionStatus            /* 000 Query Session         */
                                        /* Status structure          */
{
  unsigned char qsst_shortname;         /* 000 Session shortname     */
  unsigned char qsst_longname[8];       /* 000 Session longname      */
  unsigned char qsst_sestype;           /* 000 Session type          */
  unsigned char qsst_char;              /* 000 Session               */
                                        /* characteristics           */
  unsigned short int qsst_ps_rows;      /* 000 Number of rows in     */
                                        /* presentation space        */
  unsigned short int qsst_ps_cols;      /* 000 Number of columns     */
                                        /* in presentation space     */
  unsigned short int qsst_host_nls;     /* 000 Host code page        */
  unsigned char qsst_reserv18;          /* 000 Reserved byte         */
}
;                                       /* 000                       */

/*********************************************************************/
/*                     Start Host Notification (23)                  */
/*********************************************************************/

struct HLDStartHostNotify               /* 000 Start Host            */
                                        /* Notification              */
                                        /* structure.                */
{
  unsigned char sthn_shortname;         /* 000 Session Shortname     */
  unsigned char sthn_event_opt;         /* 000 Update event          */
                                        /* option                    */
  unsigned char sthn_reserved[4];       /* Reserved                  */
  unsigned char sthn_aevent_opt;        /* 000 Async update event    */
                                        /* option                    */
}
;                                       /* 000                       */

/*********************************************************************/
/*                     Query Host Update (24)                        */
/*********************************************************************/

struct HLDQueryHostUpdate               /* 000 Query Host Update     */
                                        /* structure                 */
{
  unsigned char qyhn_shortname;         /* 000 Session Shortname     */
}
;                                       /* 000                       */

/*********************************************************************/
/*                     Stop Host Notification (25)                   */
/*********************************************************************/

struct HLDStopHostNotify                /* 000 Stop Host Notification*/
                                        /* structure                 */
{
  unsigned char sphn_shortname;         /* 000 Session Shortname     */
}
;                                       /* 000                       */

/*********************************************************************/
/*                     Start Close Click Intercept (41)              */
/*********************************************************************/

struct HLDStartCloseIntercept           /* 000 Start Close Click     */
                                        /* Intercept structure       */
{
  unsigned char stci_shortname;         /* 000 Session Shortname     */
  HWND          stci_hwnd;              /* Window Handle for async   */
                                        /* request.                  */
  unsigned char stci_reserved[2];       /* Reserved                  */
  unsigned char stci_close_opt;         /* type of notification      */
}
;                                       /* 000                       */

/*********************************************************************/
/*                     Query Close Click Intercept (42)              */
/*********************************************************************/

struct HLDQueryCloseIntercept           /* 000 Query Close Click     */
                                        /* Intercept structure       */
{
  unsigned char qyci_shortname;         /* 000 Session Shortname     */
}
;                                       /* 000                       */

/*********************************************************************/
/*                     Stop  Close Click Intercept (43)              */
/*********************************************************************/

struct HLDStopCloseIntercept            /* 000 Stop Close Click      */
                                        /* Intercept structure       */
{
  unsigned char spci_shortname;         /* 000 Session Shortname     */
}
;                                       /* 000                       */

/*********************************************************************/
/*                     Start Keystroke Intercept (50)                */
/*********************************************************************/

struct HLDStartKeyIntercept             /* 000 Start Keystroke       */
                                        /* Intercept structure       */
{
  unsigned char stki_shortname;         /* 000 Session Shortname     */
  unsigned char stki_keytyp_opt;        /* 000 Type of keys to       */
                                        /* intercept                 */
  HWND          stki_hwnd;              /* Window Handle for async   */
                                        /* request.                  */
  unsigned char stki_reserved[2];       /* Reserved                  */
  unsigned char stki_akeytyp_opt;       /* 000 async type of keys to */
                                        /* intercept                 */
}
;                                       /* 000                       */

/*********************************************************************/
/*                     Get Key (51)                                  */
/*********************************************************************/

struct HLDGetKey                        /* 000 Get Key structure.    */
{
  unsigned char gkey_shortname;         /* 000 Session Shortname     */
  unsigned char gkey_keytype;           /* 000 Type of key           */
                                        /* intercepted               */
  unsigned char gkey_key[6];            /* 000 Ascii or ascii        */
                                        /* mnemonic                  */
}
;                                       /* 000                       */

/*********************************************************************/
/*                     Post Intercept Status (52)                    */
/*********************************************************************/

struct HLDPostInterceptStatus           /* 000 Post Intercept        */
                                        /* Status structure          */
{
  unsigned char pist_shortname;         /* 000 Session Shortname     */
  unsigned char pist_post_opt;          /* 000 Key accepted or       */
                                        /* rejected                  */
}
;                                       /* 000                       */

/*********************************************************************/
/*                     Stop  Keystroke Intercept (53)                */
/*********************************************************************/

struct HLDStopKeyIntercept              /* 000 Stop Intercept        */
                                        /* Status structure          */
{
  unsigned char spki_shortname;         /* 000 Session Shortname     */
}
;                                       /* 000                       */

/*********************************************************************/
/*                     Lock Presentation Space API (60)              */
/*********************************************************************/

struct HLDLockPS                        /* 000 LockPS structure     */
{
  unsigned char lkps_shortname;         /* 000 Session Shortname     */
  unsigned char lkps_lockopt;           /* 000 Lock/unlock option    */
  unsigned char lkps_queueopt;          /* 000 Queue option          */
}
;                                       /* 000                       */

/*********************************************************************/
/*                     Lock PMSVC API (61)                           */
/*********************************************************************/

struct HLDLockPMSVC                     /* 000 LockPMSVC structure   */
{
  unsigned char lkpm_shortname;         /* 000 Session Shortname     */
  unsigned char lkpm_lockopt;           /* 000 Lock/unlock option    */
  unsigned char lkpm_queueopt;          /* 000 Queue option          */
}
;                                       /* 000                       */

/*********************************************************************/
/*                     Convert Position or Row Column (99)           */
/*********************************************************************/

struct HLDConvertPosRowCol              /* 000 Convert Position      */
                                        /* or Row Column             */
                                        /* structure                 */
{
  unsigned char cvrc_shortname;         /* 000 Session Shortname     */
  unsigned char cvrc_opt;               /* 000 Convert option        */
}
;                                       /* 000                       */

/*********************************************************************/
/*                     Connect for PM Services (101)                 */
/*********************************************************************/

struct HLDConnectPM                     /* 000 Connect For           */
                                        /* Presentation Manager      */
                                        /* Services structure        */
{
  unsigned char stpm_shortname;         /* 000 Session Shortname     */
}
;                                       /* 000                       */

/*********************************************************************/
/*                     Disconnect from PM Services (102)             */
/*********************************************************************/

struct HLDDisconnectPM                  /* 000 Disconnect From       */
                                        /* Presentation Manager      */
                                        /* Services structure        */
{
  unsigned char sppm_shortname;         /* 000 Session Shortname     */
}
;                                       /* 000                       */

/*********************************************************************/
/*                       Query PM Window Coordinates (103)           */
/*********************************************************************/

struct HLDQueryWindowCoords             /* 000 Query PM Window       */
                                        /* Coordinates structure     */
{
  unsigned char gcor_shortname;         /* 000 Session Shortname     */
  unsigned long int gcor_xLeft;         /* 000 Left X coordinate     */
  unsigned long int gcor_yBottom;       /* 000 Bottom Y coordinate   */
  unsigned long int gcor_xRight;        /* 000 Right X coordinate    */
  unsigned long int gcor_yTop;          /* 000 Top Y coordinate      */
}
;                                       /* 000                       */

/*********************************************************************/
/*                       PM Window Status (104)                      */
/*********************************************************************/

struct HLDPMWindowStatus                /* 000 PM Window Status      */
                                        /* structure                 */
{
  unsigned char cwin_shortname;         /* 000 Session Shortname     */
  unsigned char cwin_option;            /* 000 Set/Query option      */
  unsigned short int cwin_flags;        /* 000 Window flags          */
  short int cwin_xpos;                  /* 000 X coordinate position */
  short int cwin_ypos;                  /* 000 Y coordinate position */
  short int cwin_xsize;                 /* 000 X axis window size    */
  short int cwin_ysize;                 /* 000 Y axis window size    */
  unsigned long int cwin_behind;        /* 000 Relative Window       */
                                        /*     placement             */
}
;                                       /* 000                       */

struct HLDPMWindowStatusExt             /* 000 PM Window Status for  */
                                        /* extended structure        */
{
  unsigned char xwin_shortname;         /* 000 Session Shortname     */
  unsigned char xwin_option;            /* 000 Set/Query option      */
  unsigned short int xwin_flags;        /* 000 Window flags          */
  short int xwin_fontx;                 /* 000 X font size           */
  short int xwin_fonty;                 /* 000 Y font size           */
  short int xwin_offsetx;               /* 000 X offset              */
  short int xwin_offsety;               /* 000 Y offset              */
  short int xwin_firstrow;              /* 000 first row             */
  short int xwin_firstcol;              /* 000 first col             */
  unsigned long int xwin_handle;        /* 000 Window handle         */
}
;                                       /* 000                       */

/*********************************************************************/
/*                Change Switch List Name (105)                      */
/*********************************************************************/

struct HLDChangeSwitchName              /* 000 Change Switch List    */
                                        /* Name structure            */
{
  unsigned char chsw_shortname;         /* 000 Session Shortname     */
  unsigned char chsw_option;            /* 000 Set/Reset option      */
  unsigned char chsw_swname[61];        /* 000 Switch List name      */
}
;                                       /* 000                       */

/*********************************************************************/
/*                Change LT Window Name (106)                        */
/*********************************************************************/

struct HLDChangeWindowName              /* 000 Change LT Window      */
                                        /* Name structure            */
{
  unsigned char chlt_shortname;         /* 000 Session Shortname     */
  unsigned char chlt_option;            /* 000 Set/Reset option      */
  unsigned char chlt_ltname[61];        /* 000 LT Window Name        */
}
;                                       /* 000                       */

/*********************************************************************/
/*                Start Structured Field           (120)             */
/*********************************************************************/

struct HLDConnectSF                     /* 000 Connect SF structure  */
{
  unsigned char stsf_shortname;         /* 000 Session Shortname     */
  unsigned char far * stsf_query;       /* 000 4 byte pointer to     */
                                        /* 000 Query reply           */
  unsigned short int  stsf_doid;        /* 000 Destination/Orgin id  */
  unsigned char far * stsf_asem;        /* 000 4 byte pointer to     */
                                        /* 000 notification semaphore*/
}
;                                       /* 000                       */

/*********************************************************************/
/*                Stop  Structured Field           (121)             */
/*********************************************************************/

struct HLDDisconnectSF                  /* 000 Disconnect SF         */
                                        /* structure                 */
{
  unsigned char spsf_shortname;         /* 000 Session Shortname     */
  unsigned short int spsf_doid;         /* 000 Destination/Orgin id  */
}
;                                       /* 000                       */

/*********************************************************************/
/*                Query Communications buffer sizes(122)             */
/*********************************************************************/

struct HLDQueryBufferSize               /* 000 Query Communication   */
                                        /* buffer size structure     */
{
  unsigned char qbuf_shortname;         /* 000 Session Shortname     */
  unsigned short int qbuf_opt_inbound;  /* 000 Optimal inbound buffer*/
                                        /* 000 length                */
  unsigned short int qbuf_max_inbound;  /* 000 Maximum inbound buffer*/
                                        /* 000 length                */
  unsigned short int qbuf_opt_outbound; /* 000 Optiomal outbound     */
                                        /* 000 buffer length         */
  unsigned short int qbuf_max_outbound; /* 000 Maximum outbound      */
                                        /* 000 buffer length         */
}
;                                       /* 000                       */

/*********************************************************************/
/*                Allocate communications buffer   (123)             */
/*********************************************************************/

struct HLDAllocateCommBuff              /* 000 Allocate Communication*/
                                        /* buffer structure          */
{
  unsigned short int  abuf_length;      /* 000 request buffer length */
  unsigned char far * abuf_address;     /* 000 4 byte pointer to     */
                                        /* 000 return buffer address */
}
;                                       /* 000                       */

/*********************************************************************/
/*                Free communications buffer       (124)             */
/*********************************************************************/

struct HLDFreeCommBuff                  /* 000 Free Communication    */
                                        /* buffer structure          */
{
  unsigned short int  fbuf_length;      /* 000 buffer length to free */
  unsigned char far * fbuf_address;     /* 000 4 byte buffer address */
}
;                                       /* 000                       */

/*********************************************************************/
/*                Get Async Request completion     (125)             */
/*********************************************************************/

struct HLDGetAsyncCompletion            /* 000 Get Async Request     */
                                        /* Completion structure      */
{
  unsigned char  gcmp_shortname;        /* 000 Session Shortname     */
  unsigned char  gcmp_option;           /* 000 Wait option           */
  unsigned short int  gcmp_requestid;   /* 000 request id            */
  unsigned short int  gcmp_ret_functid; /* 000 returned function id  */
  unsigned char far * gcmp_ret_datastr; /* 000 4 byte pointer to     */
                                        /* 000 returned datastring   */
  unsigned short int  gcmp_ret_length;  /* 000 returned length       */
  unsigned short int  gcmp_ret_retcode; /* 000 returned return code  */
}
;                                       /* 000                       */

/*********************************************************************/
/*                Read  Structured Field            (126)            */
/*********************************************************************/

struct HLDReadSF                        /* 000 Read SF structure     */
{
  unsigned char  rdsf_shortname;        /* 000 Session Shortname     */
  unsigned char  rdsf_option;           /* 000 Wait option           */
  unsigned short int  rdsf_doid;        /* 000 destination/orgin id  */
  unsigned char far * rdsf_buffer;      /* 000 4 byte pointer to     */
                                        /* 000 read buffer           */
  unsigned short int  rdsf_requestid;   /* 000 request id            */
  HWND                rdsf_hwnd;        /* Window Handle for async   */
                                        /* request.                  */
  unsigned char       rdsf_reserved[2]; /* Reserved                  */
}
;                                       /* 000                       */

/*********************************************************************/
/*               Write Structured Field            (127)             */
/*********************************************************************/

struct HLDWriteSF                       /* 000 Write SF structure    */
{
  unsigned char  wrsf_shortname;        /* 000 Session Shortname     */
  unsigned char  wrsf_option;           /* 000 Wait option           */
  unsigned short int  wrsf_doid;        /* 000 destination/orgin id  */
  unsigned char far * wrsf_buffer;      /* 000 4 byte pointer to     */
                                        /* 000 write buffer          */
  unsigned short int  wrsf_requestid;   /* 000 request id            */
  HWND                wrsf_hwnd;        /* Window Handle for async   */
                                        /* request.                  */
  unsigned char       wrsf_reserved[2]; /* Reserved                  */
}
;

/*************************************************************************/
/******************** WinHLLAPI FUNCTION NUMBERS *************************/
/*************************************************************************/
#define  CONNECTPS                        1 /* 000 Connect PS            */
#define  DISCONNECTPS                     2 /* 000 Disconnect PS         */
#define  SENDKEY                          3 /* 000 Sendkey function      */
#define  WAIT                             4 /* 000 Wait function         */
#define  COPYPS                           5 /* 000 Copy PS function      */
#define  SEARCHPS                         6 /* 000 Search PS function    */
#define  QUERYCURSORLOC                   7 /* 000 Query Cursor          */
#define  COPYPSTOSTR                      8 /* 000 Copy PS to String     */
#define  SETSESSIONPARAMETERS             9 /* 000 Set Session           */
#define  QUERYSESSIONS                   10 /* 000 Query Sessions        */
#define  RESERVE                         11 /* 000 Reserve function      */
#define  RELEASE                         12 /* 000 Release function      */
#define  COPYOIA                         13 /* 000 Copy OIA function     */
#define  QUERYFIELDATTRIBUTE             14 /* 000 Query Field           */
#define  COPYSTRTOPS                     15 /* 000 Copy string to PS     */
#define  STORAGEMGR                      17 /* 000 Storage Manager       */
#define  PAUSE                           18 /* 000 Pause function        */
#define  QUERYSYSTEM                     20 /* 000 Query System          */
#define  RESETSYSTEM                     21 /* 000 Reset System          */
#define  QUERYSESSIONSTATUS              22 /* 000 Query Session         */
#define  STARTHOSTNOTIFICATION           23 /* 000 Start Host            */
#define  QUERYHOSTUPDATE                 24 /* 000 Query Host Update     */
#define  STOPHOSTNOTIFICATION            25 /* 000 Stop Host             */
#define  SEARCHFIELD                     30 /* 000 Search Field          */
#define  FINDFIELDPOSITION               31 /* 000 Find Field            */
#define  FINDFIELDLENGTH                 32 /* 000 Find Field Length     */
#define  COPYSTRINGTOFIELD               33 /* 000 Copy String to        */
#define  COPYFIELDTOSTRING               34 /* 000 Copy Field to         */
#define  SETCURSOR                       40 /* 000 Set Cursor            */
#define  STARTCLOSEINTERCEPT             41 /* 000 Start Close Intercept */
#define  QUERYCLOSEINTERCEPT             42 /* 000 Query Close Intercept */
#define  STOPCLOSEINTERCEPT              43 /* 000 Stop Close Intercept  */
#define  STARTKSINTERCEPT                50 /* 000 Start Keystroke       */
#define  GETKEY                          51 /* 000 Get Key function      */
#define  POSTINTERCEPTSTATUS             52 /* 000 Post Intercept        */
#define  STOPKSINTERCEPT                 53 /* 000 Stop Keystroke        */
#define  LOCKPSAPI                       60 /* 000 Lock Presentation     */
#define  LOCKWINDOWSERVICESAPI           61 /* 000 Lock PM Window        */
#define  SENDFILE                        90 /* 000 Send File function    */
#define  RECEIVEFILE                     91 /* 000 Receive file          */
#define  CONVERT                         99 /* 000 Convert Position      */
#define  CONNECTWINDOWSERVICES          101 /* 000 Connect For           */
#define  DISCONNECTWINDOWSERVICES       102 /* 000 Disconnect From       */
#define  QUERYWINDOWCOORDINATES         103 /* 000 Query Presentation    */
#define  WINDOWSTATUS                   104 /* 000 PM Window Status      */
#define  CHANGEPSNAME                   105 /* 000 Change Switch List    */
#define  CHANGEWINDOWNAME               106 /* 000 Change PS Window      */
#define  STARTPLAYINGMACRO              110 /* 000 Start playing macro   */
#define  CONNECTSTRFLDS                 120 /* 000 Start Structured      */
#define  DISCONSTRFLDS                  121 /* 000 Stop Structured       */
#define  QUERYCOMMBUFSIZ                122 /* 000 Query Communications  */
#define  ALLOCCOMMBUFF                  123 /* 000 Allocate              */
#define  FREECOMMBUFF                   124 /* 000 Free Communications   */
#define  GETREQUESTCOMP                 125 /* 000 Get Asynchronous      */
#define  READSTRFLDS                    126 /* 000 Read Structured Field */
#define  WRITESTRFLDS                   127 /* 000 Write Structured      */

//=============================================================================
// SetSessionParameters definitions
//=============================================================================
#define  WHLL_SSP_NEWRET                0x00000001
#define  WHLL_SSP_OLDRET                0x00000002
#define  WHLL_SSP_ATTRB                 0x00000004
#define  WHLL_SSP_NOATTRB               0x00000008
#define  WHLL_SSP_NWAIT                 0x00000010
#define  WHLL_SSP_LWAIT                 0x00000020
#define  WHLL_SSP_TWAIT                 0x00000040
#define  WHLL_SSP_EAB                   0x00000080
#define  WHLL_SSP_NOEAB                 0x00000100
#define  WHLL_SSP_AUTORESET             0x00000200
#define  WHLL_SSP_NORESET               0x00000400
#define  WHLL_SSP_SRCHALL               0x00001000
#define  WHLL_SSP_SRCHFROM              0x00002000
#define  WHLL_SSP_SRCHFRWD              0x00004000
#define  WHLL_SSP_SRCHBKWD              0x00008000
#define  WHLL_SSP_FPAUSE                0x00010000
#define  WHLL_SSP_IPAUSE                0x00020000

//=============================================================================
// Convert Row or Column Flags
//=============================================================================
#define  WHLL_CONVERT_POSITION          'P'
#define  WHLL_CONVERT_ROW               'R'

//=============================================================================
// Storage Manager Sub-Function Values
//=============================================================================
#define  WHLL_GETSTORAGE                1
#define  WHLL_FREESTORAGE               2
#define  WHLL_FREEALLSTORAGE            3
#define  WHLL_QUERYFREESTORAGE          4

//=============================================================================
// Change PS Name Values
//=============================================================================
#define  WHLL_CHANGEPSNAME_SET          0X01
#define  WHLL_CHANGEPSNAME_RESET        0X02

//=============================================================================
// Window Status Values
//=============================================================================
#define  WHLL_WINDOWSTATUS_SET          0X01
#define  WHLL_WINDOWSTATUS_RESET        0X02

#define  WHLL_WINDOWSTATUS_NULL         0X0000
#define  WHLL_WINDOWSTATUS_SIZE         0X0001
#define  WHLL_WINDOWSTATUS_MOVE         0X0002
#define  WHLL_WINDOWSTATUS_ZORDER       0X0004
#define  WHLL_WINDOWSTATUS_SHOW         0X0008
#define  WHLL_WINDOWSTATUS_HIDE         0X0010
#define  WHLL_WINDOWSTATUS_ACTIVATE     0X0080
#define  WHLL_WINDOWSTATUS_DEACTIVATE   0X0100
#define  WHLL_WINDOWSTATUS_MINIMIZE     0X0400
#define  WHLL_WINDOWSTATUS_MAXIMIZE     0X0800
#define  WHLL_WINDOWSTATUS_RESTORE      0X1000

#define  WHLL_WINDOWSTATUS_FRONT        0X00000003
#define  WHLL_WINDOWSTATUS_BACK         0X00000004

/*********************************************************************/
/******************** WinHLLAPI RETURN CODES *************************/
/*********************************************************************/
#define  WHLLOK                         0
#define  WHLLNOTCONNECTED               1
#define  WHLLBLOCKNOTAVAIL              1
#define  WHLLPARAMETERERROR             2
#define  WHLLBLOCKIDINVALID             2
#define  WHLLFTXCOMPLETE                3
#define  WHLLFTXSEGMENTED               4
#define  WHLLPSBUSY                     4
#define  WHLLINHIBITED                  5
#define  WHLLTRUNCATED                  6
#define  WHLLPOSITIONERROR              7
#define  WHLLNOTAVAILABLE               8
#define  WHLLSYSERROR                   9
#define  WHLLWOULDBLOCK                 10
#define  WHLLUNAVAILABLE                11
#define  WHLLPSENDED                    12
#define  WHLLUNDEFINEDKEY               20
#define  WHLLOIAUPDATE                  21
#define  WHLLPSUPDATE                   22
#define  WHLLBOTHUPDATE                 23
#define  WHLLNOFIELD                    24
#define  WHLLNOKEYSTROKES               25
#define  WHLLPSCHANGED                  26
#define  WHLLFTXABORTED                 27
#define  WHLLZEROLENFIELD               28
#define  WHLLINVALIDTYPE                30
#define  WHLLKEYOVERFLOW                31
#define  WHLLSFACONN                    32
#define  WHLLTRANCANCLI                 34
#define  WHLLTRANCANCL                  35
#define  WHLLHOSTCLOST                  36
#define  WHLLOKDISABLED                 37
#define  WHLLNOTCOMPLETE                38
#define  WHLLSFDDM                      39
#define  WHLLSFDPEND                    40
#define  WHLLBUFFINUSE                  41
#define  WHLLNOMATCH                    42
#define  WHLLFTXCOMPLETECICS            101

#define  WHLLINVALIDFUNCTIONNUM         301
#define  WHLLFILENOTFOUND               301
#define  WHLLACCESSDENIED               305
#define  WHLLMEMORY                     308
#define  WHLLINVALIDENVIRONMENT         310
#define  WHLLINVALIDFORMAT              311

#define  WHLLINVALIDPSID                9998
#define  WHLLINVALIDRC                  9999

//=============================================================================
// Windows HLLAPI Extension Return Codes
//=============================================================================
#define  WHLLALREADY                    0xF000
#define  WHLLINVALID                    0xF001
#define  WHLLCANCEL                     0xF002
#define  WHLLSYSNOTREADY                0xF003
#define  WHLLVERNOTSUPPORTED            0xF004

#ifdef __cplusplus
  }
#endif

#endif // #ifdef WHLLAPI_HEAD
