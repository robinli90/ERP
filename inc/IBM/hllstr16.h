/*****************************************************************************/
/*                                                                           */
/*  Module Name     : HLLSTR16.H                                             */
/*                                                                           */
/*  Description     : 16 Bit HLLAPI Structures                               */
/*                                                                           */
/*  Copyright Notice: IBM Personal Communication/3270 Version 4.1            */
/*                    (C) COPYRIGHT IBM CORP. 1989,1995 - PROGRAM PROPERTY   */
/*                    OF IBM ALL RIGHTS RESERVED                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*  Function:                                                                */
/*                                                                           */
/*    Define the 16 Bit HLLAPI structures                                    */
/*                                                                           */
/*****************************************************************************/
#ifndef HLLSTR16_HEAD
#define HLLSTR16_HEAD

#ifdef __cplusplus
  extern "C" {
#endif

/*********************************************************************/
/******************* EHLLAPI 16 BIT STRUCTURES ***********************/
/*********************************************************************/

#define  stps_struct HLDConnectPS
#define  qses_struct HLDQuerySessions
#define  coia_struct HLDCopyOIA
#define  stor_struct HLDStorageMgr
#define  paus_struct HLDPause
#define  qsys_struct HLDQuerySystem
#define  qsst_struct HLDQuerySessionStatus
#define  sthn_struct HLDStartHostNotify
#define  qyhn_struct HLDQueryHostUpdate
#define  sphn_struct HLDStopHostNotify
#define  stci_struct HLDStartCloseIntercept
#define  qyci_struct HLDQueryCloseIntercept
#define  spci_struct HLDStopCloseIntercept
#define  stki_struct HLDStartKeyIntercept
#define  gkey_struct HLDGetKey
#define  pist_struct HLDPostInterceptStatus
#define  spki_struct HLDStopKeyIntercept
#define  lkps_struct HLDLockPS
#define  lkpm_struct HLDLockPMSVC
#define  cvrc_struct HLDConvertPosRowCol
#define  stpm_struct HLDConnectPM
#define  sppm_struct HLDDisconnectPM
#define  gcor_struct HLDQueryWindowCoords
#define  cwin_struct HLDPMWindowStatus
#define  xwin_struct HLDPMWindowStatusExt
#define  chsw_struct HLDChangeSwitchName
#define  chlt_struct HLDChangeWindowName
#define  stsf_struct HLDConnectSF
#define  spsf_struct HLDDisconnectSF
#define  qbuf_struct HLDQueryBufferSize
#define  abuf_struct HLDAllocateCommBuff
#define  fbuf_struct HLDFreeCommBuff
#define  gcmp_struct HLDGetAsyncCompletion
#define  rdsf_struct HLDReadSF
#define  wrsf_struct HLDWriteSF

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
/*                     Get NLS Inforation (16)                       */
/*********************************************************************/

struct HLDGetNLSInformation             /* 000 Get NLS Information   */     
{
  unsigned char gnlsi_shortname;        /* 000 Session Shortname     */
  unsigned int  gnlsi_API_CodePage;     /* CP set in API Settings    */
  unsigned int  gnlsi_Host_CodePage;    /* CP Used By Host           */
  unsigned int  gnlsi_OS_CodePage;      /* CP returned from OS       */
  int           gnlsi_DBCS;             /* DBCS?                     */
};

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
  HWND          sthn_hwnd;              /* Window Handle for async   */
                                        /* request.                  */
  unsigned char sthn_reserved[2];       /* Reserved                  */
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
;                                       /* 000                       */

#ifdef __cplusplus
  }
#endif

#endif // #ifdef HLLSTR16_HEAD
