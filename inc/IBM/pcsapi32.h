/*****************************************************************************/
/*                                                                           */
/*  Module Name     : PCSAPI32.H                                             */
/*                                                                           */
/*  Description     : 32 Bit PCSAPI Return Codes and Routines                */
/*                                                                           */
/*  Copyright Notice: IBM eNetwork Personal Communication                    */
/*                    (C) COPYRIGHT IBM CORP. 1984,1997 - PROGRAM PROPERTY   */
/*                    OF IBM ALL RIGHTS RESERVED                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*  Function:                                                                */
/*                                                                           */
/*    Define the PCSAPI return code constants and the external               */
/*    routines.                                                              */
/*                                                                           */
/*****************************************************************************/
/* V4.2 changes:                                                             */
/*   - Added pcsQuerySessionList() function and data structures              */
/*   - Added ordinal entry point values for dynamic loading of PCSAPI32.DLL  */
/*   - Added #define's for pcsStartSession() window-status parameter.        */
/* V4.3 changes:                                                             */
/*   - Added pcsSetLinkTimeout() function                                    */
/* $A1                             Add symbols for PCSAPI RexxHLLAPI support */
/* Defects                                                                   */
/* ==========================================================================*/
/*  flag   Defect#    rls  date    name description of change                */
/*  $P1    DF45036   4.20 05/17/99 CIL  pcsConnectSession fails              */
/*  $P2    AXA DCR   5.02 20010105 eeg  pcsQueryConnectionInfo               */
/*****************************************************************************/

#ifdef __cplusplus                     /* C++ compiler                       */
  extern "C" {
#endif

/*--------------------------------------------------------------------------*/
/*  General Purpose Definition                                              */
/*--------------------------------------------------------------------------*/
#define MAXPATHLEN                    256

/*--------------------------------------------------------------------------*/
/*  Definition for Query Session Status                                     */
/*--------------------------------------------------------------------------*/

#define PCS_SESSION_STARTED          0x00000001
#define PCS_SESSION_ONLINE           0x00000002
#define PCS_SESSION_API_ENABLED      0x00000004
#define PCS_SESSION_INTERIM_STATE    0x00000008                    //@P1a

/*--------------------------------------------------------------------------*/
/*  Definition for Start Session                                            */
/*--------------------------------------------------------------------------*/

#define PCS_HIDE                     0
#define PCS_SHOW                     1
#define PCS_MINIMIZE                 2
#define PCS_MAXIMIZE                 3

#define PCS_SUCCESSFUL               0
#define PCS_INVALID_ID               1
#define PCS_USED_ID                  2
#define PCS_INVALID_PROFILE          3
#define PCS_SYSTEM_ERROR             9

/*--------------------------------------------------------------------------*/
/*  Definition for Stop Session                                             */
/*--------------------------------------------------------------------------*/

#define PCS_SAVE_AS_PROFILE          0
#define PCS_SAVE_ON_EXIT             1
#define PCS_NOSAVE_ON_EXIT           2

// @A1+ [ added PCSAPI symbols ]
/*--------------------------------------------------------------------------*/
/*  Symbol definitions for RexxHLLAPI support                               */
/*--------------------------------------------------------------------------*/

#define PCSAPI_START_SESSION            140     /* Rexx - pcsStartSession    */
#define PCSAPI_STOP_SESSION             141     /* Rexx - pcsStopSession     */
#define PCSAPI_START_COMMUNICATION      142     /* Rexx - pcsStartCommunicati*/
#define PCSAPI_STOP_COMMUNICATION       143     /* Rexx - pcsStopCommunicatio*/
#define PCSAPI_QUERY_SESSLIST           144     /* Rexx - pcsQuerySessionList*/
#define PCSAPI_QUERY_EMULATOR_STAT      145     /* Rexx - pcsQueryEmulatorSta*/
#define PCSAPI_QUERY_WS_PROFILE         146     /* Rexx - pcsQueryWSProfile  */
// @A1+ [ end ]

/*--------------------------------------------------------------------------*/
/*  Definition for Query Session List (added V4.2)                          */
/*--------------------------------------------------------------------------*/

typedef union _SESSNAME {   // Name field of SessInfo structure
  char ShortName;           // Short session ID (A-Z)
  ULONG Handle;             // Session handle
  } SESSNAME;

typedef struct _SESSINFO {  // Description of a single session
  SESSNAME Name;            // Session name (ID or handle)
  ULONG    Status;          // Session status (PCS_SESSION_* bit flags)
  } SESSINFO;

typedef struct _CONNECTIONINFO { // Description of a connection
  char hostName[63];             // telnet host name
  char reserved1[1];             // reserved
  int  portNumber;               // host port number
  char luName[17];               // LU name
  char reserved2[3];             // reserved
  BOOL sslIndicator;             // Secure Connection indicator
  char reserved3[256];           // reserved
  } CONNECTIONINFO;

/*--------------------------------------------------------------------------*/
/*  Function Prototypes                                                     */
/*--------------------------------------------------------------------------*/
#if defined(__OS2__)
  #define PCSAPI_ENTRY APIENTRY
#else
  #define PCSAPI_ENTRY WINAPI
#endif

ULONG PCSAPI_ENTRY pcsQueryEmulatorStatus(char);
BOOL  PCSAPI_ENTRY pcsQueryWorkstationProfile(char, PSZ);
ULONG PCSAPI_ENTRY pcsStartSession(PSZ, char, USHORT);
BOOL  PCSAPI_ENTRY pcsStopSession(char, USHORT);
BOOL  PCSAPI_ENTRY pcsConnectSession(char);
BOOL  PCSAPI_ENTRY pcsDisconnectSession(char);
ULONG PCSAPI_ENTRY pcsQuerySessionList(ULONG Count, SESSINFO *SessList); // Added V4.2
#if defined(_V43)
ULONG PCSAPI_ENTRY pcsSetLinkTimeout(char, USHORT); // Added V4.3
#endif
#if defined(_V50)
BOOL  PCSAPI_ENTRY pcsQueryConnectionInfo(char, CONNECTIONINFO *);  // @P2A
#endif

/*--------------------------------------------------------------------------*/
/*  Ordinal numbers for function entry points                               */
/*--------------------------------------------------------------------------*/

#define ord_pcsQueryEmulatorStatus     3
#define ord_pcsQueryWorkstationProfile 4
#define ord_pcsStartSession            5
#define ord_pcsStopSession             6
#define ord_pcsConnectSession          7
#define ord_pcsDisconnectSession       8
#define ord_pcsQuerySessionList        9
#if defined(_V43)
#define ord_pcsSetLinkTimeout          10
#endif
#if defined(_V50)
#define ord_pcsQueryConnectionInfo     11
#endif

#ifdef __cplusplus
  }
#endif
