/*****************************************************************************/
/*                                                                           */
/*  Module Name     : DDE_C.H                                                */
/*                                                                           */
/*  Description     : DDE  Structure, Return Codes and Routines              */
/*                                                                           */
/*  Copyright Notice: IBM Personal Communication/3270 Version 4.1            */
/*                    for Windows 95.                                        */
/*                    (C) COPYRIGHT IBM CORP. 1984,1996 - PROGRAM PROPERTY   */
/*                    OF IBM ALL RIGHTS RESERVED                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*  Function:                                                                */
/*                                                                           */
/*    Define the DDE  structure, return code constants.                      */
/*                                                                           */
/*****************************************************************************/

#ifdef __cplusplus                     /* C++                                */
  extern "C" {
#endif

/*---------------------------------------------------------------------------*/
/*  Return Codes                                                             */
/*---------------------------------------------------------------------------*/

#define PCS_DDE_ACK                      0x0001
#define PCS_DDE_NACK_ADVISED             0x0100
#define PCS_DDE_NACK_INVALID_POSITION    0x0100
#define PCS_DDE_NACK_INVALID_OPTION      0x0100
#define PCS_DDE_NACK_DATA_NOT_READY      0x0100
#define PCS_DDE_NACK_INVALID_LENGTH      0x0200
#define PCS_DDE_NACK_INVALID_PSPOSITION  0x0200
#define PCS_DDE_NACK_UNFORMATTED         0x0200
#define PCS_DDE_NACK_NOT_FOUND           0x0200
#define PCS_DDE_NACK_ADCON_ACTIVE        0x0200
#define PCS_DDE_NACK_INVALID_PARAM       0x0200
#define PCS_DDE_NACK_INVALID_ADVPOS      0x0300
#define PCS_DDE_NACK_INVALID_FLAG        0x0300
#define PCS_DDE_NACK_INVALID_ROW         0x0300
#define PCS_DDE_NACK_DOID_INUSE          0x0300
#define PCS_DDE_NACK_UNCONDITION         0x0300
#define PCS_DDE_NACK_INVALID_STRLEN      0x0400
#define PCS_DDE_NACK_INVALID_COL         0x0400
#define PCS_DDE_NACK_INVALID_SRCHDIR     0x0400
#define PCS_DDE_NACK_ALREADY_SET         0x0400
#define PCS_DDE_NACK_INPUT_INHIBITTED    0x0500
#define PCS_DDE_NACK_SYNTAX_ERROR        0x0600
#define PCS_DDE_NACK_INVALID_FORMAT      0x0600
#define PCS_DDE_NACK_DATA_TRUNCATED      0x0700
#define PCS_DDE_NACK_SYSTEM_ERROR        0x0900
#define PCS_DDE_NACK_BUFFER_EXCEEDED     0x1000
#define PCS_DDE_NACK_XLATE_ERROR         0x1100

/*---------------------------------------------------------------------------*/
/*  Code Conversion                                                          */
/*---------------------------------------------------------------------------*/

typedef struct tagWCDDE_CONV
{
	BYTE  ddepoke[(sizeof(DDEPOKE)-1)];
	char  szSourceName[256];
	char  szTargetName[256];
	BYTE  ConvType;
	WORD  uSourceLength;
	WORD  uTargetLength;
} WCDDE_CONV;

typedef union tagDDE_CONV
{
	DDEPOKE DDEpoke;
	WCDDE_CONV  DDEConv;
} DDE_CONV;

typedef DDE_CONV FAR *LPDDE_CONV;

/*---------------------------------------------------------------------------*/
/*  Find Field                                                               */
/*---------------------------------------------------------------------------*/

typedef struct tagFINDFIELD
{
  unsigned char  data[(sizeof(DDEDATA)-1)];
  unsigned short uFieldStart;    /* Field start offset                       */
  unsigned short uFieldLength;   /* Field Length                             */
  unsigned char  cAttribute;     /* Attribute character                      */
  unsigned char  ubReserved;     /* *** Reserved ***                         */
} FINDFIELD;

typedef union tagDDE_FINDFIELD
{
  DDEDATA     DDEdata;
  FINDFIELD   DDEfield;
} DDE_FINDFIELD, *lpDDE_FINDFIELD;

typedef struct tagFINDFIELD_CF_TEXT                 
{                                                   
  unsigned char     data[(sizeof(DDEDATA)-1)];              
  unsigned char     Fielddata[80];                          
} FINDFIELD_CF_TEXT;                                
                                                    
typedef FINDFIELD_CF_TEXT FAR *LPFINDFIELD_CF_TEXT; 

typedef union tagDDE_FIELD
{
  DDEDATA     DDEdata;
  FINDFIELD   DDEFindField;
  FINDFIELD_CF_TEXT DDEFindField_cftxt;             
} DDE_FIELD;

typedef DDE_FIELD FAR *LPDDE_FIELD;

typedef struct tagPSFIELDS16
{
  BYTE      ubAttribute;                                                //@wd01a
  WORD      uFieldStart;                                                //@wd01a
  WORD      uFieldLength;                                               //@wd01a
} PSFIELDS16;                                                           //@wd01a

typedef PSFIELDS16 FAR *LPPSFIELDS16;

typedef struct tagFINDFIELD16
{
  unsigned char       data[(sizeof(DDEDATA)-1)];
  PSFIELDS16  field;
} FINDFIELD16;

typedef FINDFIELD16 FAR *LPFINDFIELD16;


typedef union tagDDE_FIELD16
{
  DDEDATA     DDEdata;
  FINDFIELD16 DDEFindField;
  FINDFIELD_CF_TEXT DDEFindField_cftxt;                         //@D4A
} DDE_FIELD16;

typedef DDE_FIELD16 FAR *LPDDE_FIELD16;

/*---------------------------------------------------------------------------*/
/*  Get Keystrokes                                                           */
/*---------------------------------------------------------------------------*/

typedef struct tagKEYSTROKE
{
  unsigned char  data[(sizeof(DDEDATA)-1)];
  unsigned short uTextType;      /* Type of keystrokes                       */
  unsigned char  szKeyData[1];   /* Keystrokes                               */
} KEYSTROKE;

typedef union tagDDE_GETKEYSTROKE
{
  DDEDATA     DDEdata;
  KEYSTROKE   DDEkey;
} DDE_GETKEYSTROKE, *lpDDE_GETKEYSTROKE;

#define PCS_PURETEXT   0         /* Pure text, no HLLAPI commands            */
#define PCS_HLLAPITEXT 1         /* Text, including HLLAPI tokens            */

/*---------------------------------------------------------------------------*/
/*  Get Mouse Input                                                          */
/*---------------------------------------------------------------------------*/

typedef struct tagMOUSE_CF_DSPTEXT
{
  unsigned char  data[(sizeof(DDEDATA)-1)];
  unsigned short uPSPos;         /* PS Offset of the Mouse position          */
  unsigned short uPSRowPos;      /* ROW number of Mouse position             */
  unsigned short uPSColPos;      /* Column number of Mouse position          */
  unsigned short uPSSize;        /* Size od Presentation Space               */
  unsigned short uPSRows;        /* Row number of PS                         */
  unsigned short uPSCols;        /* Column number of PS                      */
  unsigned short uButtonType;    /* Type of clicked mouse button             */
  unsigned short uClickType;     /* Type of clicking                         */
  unsigned char  zClickString[1];/* Retrived string                          */
} MOUSE_CF_DSPTEXT;

typedef union tagDDE_MOUSE_CF_DSPTEXT
{
  DDEDATA           DDEdata;
  MOUSE_CF_DSPTEXT  DDEmouse;
} DDE_MOUSE_CF_DSPTEXT, *lpDDE_MOUSE_CF_DSPTEXT;

#define PCS_MOUSE_LEFT   0x0001  /* Left button                              */
#define PCS_MOUSE_RIGHT  0x0002  /* Right button                             */
#define PCS_MOUSE_MIDDLE 0x0003  /* Middle button                            */
#define PCS_MOUSE_SINGLE 0x0001  /* Single Click                             */
#define PCS_MOUSE_DOUBLE 0x0002  /* Double click                             */

typedef struct tagMOUSE_CF_TEXT
{
  unsigned char data[(sizeof(DDEDATA)-1)];
  unsigned char PSPos[4];        /* PS Offset of the Mouse position          */
  unsigned char Tab1[1];         /* Tab character                            */
  unsigned char PSRowPos[4];     /* ROW number of Mouse position             */
  unsigned char Tab2[1];         /* Tab character                            */
  unsigned char PSColPos[4];     /* Column number of Mouse position          */
  unsigned char Tab3[1];         /* Tab character                            */
  unsigned char PSSize[4];       /* Size od Presentation Space               */
  unsigned char Tab4[1];         /* Tab character                            */
  unsigned char PSRows[4];       /* Row number of PS                         */
  unsigned char Tab5[1];         /* Tab character                            */
  unsigned char PSCols[4];       /* Column number of PS                      */
  unsigned char Tab6[1];         /* Tab character                            */
  unsigned char Button[1];       /* Type of clicked mouse button             */
  unsigned char Tab7[1];         /* Tab character                            */
  unsigned char Click[1];        /* Type of clicking                         */
  unsigned char Tab8[1];         /* Tab character                            */
  unsigned char zClickString[1]; /* Retrived string                          */
} MOUSE_CF_TEXT;

typedef union tagDDE_MOUSE_CF_TEXT
{
  DDEDATA        DDEdata;
  MOUSE_CF_TEXT  DDEmouse;
} DDE_MOUSE_CF_TEXT, *lpDDE_MOUSE_CF_TEXT;

#define PCS_MOUSE_TEXT_LEFT   'L' /* Left button                             */
#define PCS_MOUSE_TEXT_RIGHT  'R' /* Right button                            */
#define PCS_MOUSE_TEXT_MIDDLE 'M' /* Middle button                           */
#define PCS_MOUSE_TEXT_SINGLE 'S' /* Single Click                            */
#define PCS_MOUSE_TEXT_DOUBLE 'D' /* Double click                            */

/*---------------------------------------------------------------------------*/
/*  Get Number of Close Request                                              */
/*---------------------------------------------------------------------------*/

typedef struct tagCLOSEREQ
{
  unsigned char  data[(sizeof(DDEDATA)-1)];
  unsigned short uCloseReqCount; /* Number of the close requests.            */
} CLOSEREQ;

typedef union tagDDE_CLOSEREQ
{
  DDEDATA   DDEdata;
  CLOSEREQ  DDEclose;
} DDE_CLOSEREQ, *lpDDE_CLOSEREQ;

/*---------------------------------------------------------------------------*/
/*  Get Operator Indicator Area                                              */
/*---------------------------------------------------------------------------*/

typedef struct tagOIADATA
{
  unsigned char  data[(sizeof(DDEDATA)-1)];
  unsigned char  OIA[80];        /*                                          */
} OIADATA;

typedef union tagDDE_OIADATA
{
  DDEDATA   DDEdata;
  OIADATA   DDEoia;
} DDE_OIADATA, *lpDDE_OIADATA;

/*---------------------------------------------------------------------------*/
/*  Get Partial Presentation Space                                           */
/*---------------------------------------------------------------------------*/

typedef struct tagEPS_CF_DSPTEXT
{
  unsigned char  data[(sizeof(DDEDATA)-1)];
  unsigned short uPSPosition;    /* Position of the part of PS               */
  unsigned short uPSLength;      /* Length of the part of the PS             */
  unsigned short uPSRows;        /* PS number of rows                        */
  unsigned short uPSCols;        /* PS number of columns                     */
  unsigned short uPSOffset;      /* Offset to the presentation space         */
  unsigned short uFieldCount;    /* Number of fields                         */
  unsigned short uFieldOffset;   /* Offset to the field array                */
  unsigned char  PSData[1];      /* PS and Field list Array(lpPSFIELDS)      */
} EPS_CF_DSPTEXT;

typedef union tagDDE_EPS_CF_DSPTEXT
{
  DDEDATA         DDEdata;
  EPS_CF_DSPTEXT  DDEeps;
} DDE_EPS_CF_DSPTEXT, *lpDDE_EPS_CF_DSPTEXT;

typedef struct tagEPS_CF_TEXT
{
  unsigned char  data[(sizeof(DDEDATA)-1)];
  unsigned char  PSPOSITION[4];  /* Postion of part of the PS                */
  unsigned char  Tab1[1];        /* Tab character                            */
  unsigned char  PSLENGTH[4];    /* Length of the part of the PS             */
  unsigned char  Tab2[1];        /* Tab character                            */
  unsigned char  PSROWS[4];      /* Number of rows in the PS                 */
  unsigned char  Tab3[1];        /* Tab character                            */
  unsigned char  PSCOLS[4];      /* Number of Cols in the PS                 */
  unsigned char  Tab4[1];        /* Tab character                            */
  unsigned char  PS[1];          /* PS                                       */
} EPS_CF_TEXT;

typedef union tagDDE_EPS_CF_TEXT
{
  DDEDATA      DDEdata;
  EPS_CF_TEXT  DDEeps;
} DDE_EPS_CF_TEXT, *lpDDE_EPS_CF_TEXT;

typedef struct tagPS_FIELD
{
  unsigned char  FieldStart[4];
  unsigned char  TabF1[1];
  unsigned char  FieldLength[4];
  unsigned char  TabF2[1];
  unsigned char  Attribute;
  unsigned char  TabF3[1];
} PS_FIELD, *lpPS_FIELD;

typedef struct tagFL_CF_TEXT
{
  unsigned char  Tab5[1];        /* Tab character                            */
  unsigned char  PSFldCount[4];  /* Number of fields in the PS               */
  unsigned char  Tab6[1];        /* Tab character                            */
  PS_FIELD       Field[1];       /* Field List Array                         */
} FL_CF_TEXT, *lpFL_CF_TEXT;

typedef struct tagPSFIELDS
{
  unsigned short uFieldStart;    /* Field start offset                       */
  unsigned short uFieldLength;   /* Field Length                             */
  unsigned char  cAttribute;     /* Attribute character                      */
  unsigned char  ubReserved;     /* *** Reserved ***                         */
} PSFIELDS, *lpPSFIELDS;

/*---------------------------------------------------------------------------*/
/*  Get Presentation Space                                                   */
/*---------------------------------------------------------------------------*/

typedef struct tagPS_CF_DSPTEXT
{
  unsigned char  data[(sizeof(DDEDATA)-1)];
  unsigned short uPSSize;        /* Size of the presentation space           */
  unsigned short uPSRows;        /* PS number of rows                        */
  unsigned short uPSCols;        /* PS number of columns                     */
  unsigned short uPSOffset;      /* Offset to the presentation space         */
  unsigned short uFieldCount;    /* Number of fields                         */
  unsigned short uFieldOffset;   /* Offset to the field array                */
  unsigned char  PSData[1];      /* PS and Field list Array(lpPSFIELDS)      */
} PS_CF_DSPTEXT;

typedef union tagDDE_PS_CF_DSPTEXT
{
  DDEDATA        DDEdata;
  PS_CF_DSPTEXT  DDEps;
} DDE_PS_CF_DSPTEXT, *lpDDE_PS_CF_DSPTEXT;

typedef struct tagPS_CF_TEXT
{
  unsigned char  data[(sizeof(DDEDATA)-1)];
  unsigned char  PSSIZE[4];      /* Size of the PS                           */
  unsigned char  Tab1[1];        /* Tab character                            */
  unsigned char  PSROWS[4];      /* Number of rows in the PS                 */
  unsigned char  Tab2[1];        /* Tab character                            */
  unsigned char  PSCOLS[4];      /* Number of Cols in the PS                 */
  unsigned char  Tab3[1];        /* Tab character                            */
  unsigned char  PS[1];          /* PS                                       */
} PS_CF_TEXT;

typedef union tagDDE_PS_CF_TEXT
{
  DDEDATA     DDEdata;
  PS_CF_TEXT  DDEps;
} DDE_PS_CF_TEXT, *lpDDE_PS_CF_TEXT;

/*---------------------------------------------------------------------------*/
/*  Put Data to Presentation Space                                           */
/*---------------------------------------------------------------------------*/

typedef struct tagPutString
{
  unsigned char  poke[(sizeof(DDEPOKE)-1)];
  unsigned short uPSStart;       /* PS Position                              */
  unsigned short uEOFflag;       /* EOF effective switch                     */
  unsigned char  szStringData[1];/* String Data                              */
} PUTSTRING;

typedef union tagDDE_PUTSTRING
{
  DDEPOKE    DDEpoke;
  PUTSTRING  DDEputstring;
} DDE_PUTSTRING, *lpDDE_PUTSTRING;

/*---------------------------------------------------------------------------*/
/*  Search for String                                                        */
/*---------------------------------------------------------------------------*/

typedef struct tagSEARCH
{
  unsigned char  data[(sizeof(DDEDATA)-1)];
  unsigned short uFieldStart;    /* String start offset                      */
} SEARCH;

typedef union tagDDE_SEARCH
{
  DDEDATA  DDEdata;
  SEARCH   DDEsearch;
} DDE_SEARCH, *lpDDE_SEARCH;

/*---------------------------------------------------------------------------*/
/*  Send Keystrokes                                                          */
/*---------------------------------------------------------------------------*/

typedef struct tagKeystrokes
{
  unsigned char  poke[(sizeof(DDEPOKE)-1)];
  unsigned short uTextType;      /* Type of keystrokes                       */
  unsigned short uRetryCount;    /* Retry count 1 .. 16                      */
  unsigned char  szKeyData[1];   /* Keystrokes                               */
} KEYSTROKES;

typedef union tagDDE_SENDKEYSTROKES
{
  DDEPOKE     DDEpoke;
  KEYSTROKES  DDEkeys;
} DDE_SENDKEYSTROKES, *lpDDE_SENDKEYSTROKES;

/*---------------------------------------------------------------------------*/
/*  Set Cursor Position                                                      */
/*---------------------------------------------------------------------------*/

typedef struct tagSETCURSOR
{
  unsigned char  poke[(sizeof(DDEPOKE)-1)];
  unsigned short uSetCursorType; /* Cursor Set Type                          */
  unsigned short uSetCursor1;    /* Cursor Row or PS Offset                  */
  unsigned short uSetCursor2;    /* Cursor Col                               */
} SETCURSOR;

typedef union tagDDE_SETCURSOR
{
  DDEPOKE    DDEpoke;
  SETCURSOR  DDEsetcursor;
} DDE_SETCURSOR, *lpDDE_SETCURSOR;

#define PCS_SETCURSOR_PSPOS  0x0000
#define PCS_SETCURSOR_ROWCOL 0x0001

/*---------------------------------------------------------------------------*/
/*  Set Mouse Intercept Condition                                            */
/*---------------------------------------------------------------------------*/

typedef struct tagSETMOUSE_CF_DSPTEXT
{
  unsigned char poke[(sizeof(DDEPOKE)-1)];
  BOOL          bLeftButton;     /* Enable intercepting left button          */
  BOOL          bRightButton;    /* Enable intercepting right button         */
  BOOL          bMiddleButton;   /* Enable intercepting middle button        */
  BOOL          bSingleClick;    /* Enable intercepting single click         */
  BOOL          bDoubleClick;    /* Enable intercepting double click         */
  BOOL          bRetrieveString; /* Enable intercepting retrieve string      */
} SETMOUSE_CF_DSPTEXT;

typedef union tagDDE_SETMOUSE_CF_DSPTEXT
{
  DDEPOKE              DDEpoke;
  SETMOUSE_CF_DSPTEXT  DDEcond;
} DDE_SETMOUSE_CF_DSPTEXT, *lpDDE_SETMOUSE_CF_DSPTEXT;

typedef struct tagSETMOUSE_CF_TEXT
{
  unsigned char poke[(sizeof(DDEPOKE)-1)];
  unsigned char zMouseCondition[1];
} SETMOUSE_CF_TEXT;

typedef union tagDDE_SETMOUSE_CF_TEXT
{
  DDEPOKE           DDEpoke;
  SETMOUSE_CF_TEXT  DDEcond;
} DDE_SETMOUSE_CF_TEXT, *lpDDE_SETMOUSE_CF_TEXT;

#define PCS_SETMOUSE_TEXT_LEFTON    'L' /* Enable intercepting left button   */
#define PCS_SETMOUSE_TEXT_LEFTOFF   'l' /* Disable intercepting left button  */
#define PCS_SETMOUSE_TEXT_RIGHTON   'R' /* Enable intercepting Right button  */
#define PCS_SETMOUSE_TEXT_RIGHTOFF  'r' /* Disable intercepting Right button */
#define PCS_SETMOUSE_TEXT_MIDDLEON  'M' /* Enable intercepting Middle button */
#define PCS_SETMOUSE_TEXT_MIDDLEOFF 'm' /* Disable intercepting Middle button*/
#define PCS_SETMOUSE_TEXT_SINGLEON  'S' /* Enable intercepting Single Click  */
#define PCS_SETMOUSE_TEXT_SINGLEOFF 's' /* Disable intercepting Single Click */
#define PCS_SETMOUSE_TEXT_DOUBLEON  'D' /* Enable intercepting Double click  */
#define PCS_SETMOUSE_TEXT_DOUBLEOFF 'd' /* Disable intercepting Double click */
#define PCS_SETMOUSE_TEXT_RETSTRON  'T' /* Retrieve the pointed string       */
#define PCS_SETMOUSE_TEXT_RETSTROFF 't' /* Not retieve the pointed string    */

/*---------------------------------------------------------------------------*/
/*  Set Presentation Space Service Condition                                 */
/*---------------------------------------------------------------------------*/

typedef struct tagPSSERVCOND
{
  unsigned char  poke[(sizeof(DDEPOKE)-1)];
  unsigned short uPSStart;       /* PS Position                              */
  unsigned short uPSLength;      /* Length of String or PS                   */
  unsigned short uSearchDir;     /* Direction for search                     */
  unsigned short uEOFflag;       /* EOF effective switch                     */
  unsigned char  szTargetString[1]; /* Target String                         */
} PSSERVCOND;

typedef union tagDDE_PSSERVCOND
{
  DDEPOKE     DDEpoke;
  PSSERVCOND  DDEcond;
} DDE_PSSERVCOND, *lpDDE_PSSERVCOND;

#define PCS_SRCHFRWD    0        /* Search forward.                          */
#define PCS_SRCHBKWD    1        /* Search backward.                         */
#define PCS_UNEFFECTEOF 0        /* The string is not truncated at EOF.      */
#define PCS_EFFECTEOF   1        /* The string is truncated at EOF.          */

/*---------------------------------------------------------------------------*/
/*  Set Session Advise Condition                                             */
/*---------------------------------------------------------------------------*/

typedef struct tagSEARCHDATA
{
  unsigned char  poke[(sizeof(DDEPOKE)-1)];
  unsigned short uPSStart;       /* PS Position of string                    */
  unsigned short uPSLength;      /* Length of String                         */
  BOOL           bCaseSensitive; /* Case Sensitive TRUE=YES                  */
  unsigned char  SearchString[1];/* Search String                            */
} SEARCHDATA;

typedef union tagDDE_SEARCHDATA
{
  DDEPOKE     DDEpoke;
  SEARCHDATA  DDEcond;
} DDE_SEARCHDATA, *lpDDE_SEARCHDATA;

/*---------------------------------------------------------------------------*/
/*  Set Structured Field Service Condition                                   */
/*---------------------------------------------------------------------------*/

typedef struct tagSFSERVCOND
{
  unsigned char  poke[(sizeof(DDEPOKE)-1)];
  unsigned short uBufferLength;  /* Buffer size of Read_SF                   */
  unsigned short uQRLength;      /* Length of Query Reply data               */
  unsigned char  szQueryReply[1];/* Query Reply data                         */
} SFSERVCOND;

typedef union tagDDE_SFSERVCOND
{
  DDEPOKE     DDEpoke;
  SFSERVCOND  DDEcond;
} DDE_SFSERVCOND, *lpDDE_SFSERVCOND;

/*---------------------------------------------------------------------------*/
/*  Start Read SF                                                            */
/*---------------------------------------------------------------------------*/

typedef struct tagSFDATA
{
  unsigned char  data[(sizeof(DDEDATA)-1)];
  unsigned short uSFLength;      /* Length of SF data                        */
  unsigned char  szSFData[1];    /* SF data                                  */
} SFDATA;

typedef union tagDDE_SFDATA
{
  DDEDATA  DDEdata;
  SFDATA   DDEsfdata;
} DDE_SFDATA, *lpDDE_SFDATA;

/*---------------------------------------------------------------------------*/
/*  Start Write SF                                                           */
/*---------------------------------------------------------------------------*/

typedef struct tagWRITESF
{
  unsigned char  poke[(sizeof(DDEPOKE)-1)];
  unsigned short uSFLength;      /* Length of SF data                        */
  unsigned char  Work[8];        /* Work area                                */
  unsigned char  szSFData[1];    /* SF data                                  */
} WRITESF;

typedef union tagDDE_WRITESF
{
  DDEPOKE  DDEpoke;
  WRITESF  DDEwritesf;
} DDE_WRITESF, *lpDDE_WRITESF;

/*---------------------------------------------------------------------------*/
/*  Change Menu Item                                                         */
/*---------------------------------------------------------------------------*/

typedef struct tagChangeMenu
{
  unsigned char  poke[(sizeof(DDEPOKE)-1)];
  HWND           hMenu;           /* Window handle of menu item              */
  unsigned long  wIDNew;          /* The menu ID of the new menu item        */
  unsigned short wPosition;       /* The position of the menu item           */
  unsigned short wOperation;      /* Specifies the operation                 */
  unsigned short wFlags;          /* Specifies the options                   */
  unsigned char  szItemName[1];   /* String of the item                      */
} CHANGEMENU;

typedef union tagDDE_CHANGEMENU
{
  DDEPOKE     DDEpoke;
  CHANGEMENU  DDEmenu;
} DDE_CHANGEMENU, *lpDDE_CHANGEMENU;

#define PCS_INSERT       0x0000   /* Inserts a menu item into a menu.        */
#define PCS_CHANGE       0x0080   /* Modifies a menu item in a menu.         */
#define PCS_APPEND       0x0100   /* Appends a menu item to the end of a menu*/
#define PCS_DELETE       0x0200   /* Deletes a menu item from a menu,        */
                                  /* destroying the menu item.               */
#define PCS_REMOVE       0x1000   /* Removes a menu item from a menu but     */
                                  /* does not destroy the menu item.         */

#define PCS_CHECKED      0x0008   /* Places a checkmark next to the item.    */
#define PCS_DISABLED     0x0002   /* Disables the menu item so that it cannot*/
                                  /* be selected, but does not gray it.      */
#define PCS_ENABLED      0x0000   /* Enables the menu item so that it can be */
                                  /* selected and restores from its grayed   */
                                  /* state.                                  */
#define PCS_GRAYED       0x0001   /* Disables the menu item so that it cannot*/
                                  /* be selected, and grays it.              */
#define PCS_MENUBARBREAK 0x0020   /* Same as PCS_MENUBREAK except that for   */
                                  /* popup menus, separates the new column   */
                                  /* from the old column with a vertical line*/
#define PCS_MENUBREAK    0x0040   /* Plaves the item on a new line for menu  */
                                  /* bar items. For popupmenus, places the   */
                                  /* item in a new column, with no dividing  */
                                  /* line between the columns.               */
#define PCS_SEPARATOR    0x0800   /* Draws a horizontal dividing line. Can   */
                                  /* only be used in a popup menu. This line */
                                  /* cannot be grayed, disabled, or          */
                                  /* highlighted. The wIDNew and szItemName  */
                                  /* fields are ignored.                     */
#define PCS_UNCHAKED     0x0000   /* Does not place a checkmark next to the  */
                                  /* item (default).                         */

#define PCS_BYCOMMAND    0x0000   /* Specifies that the nPosition parameter  */
                                  /* gives the menu item control ID number.  */
                                  /* This is the default if neither item     */
                                  /* control ID number. This is the default  */
                                  /* if neither PCS_BYCOMMAND nor            */
                                  /* PCS_POSITION is set.                    */
#define PCS_BYPOSITION   0x0400   /* Specifies that the nPosition parameter  */
                                  /* gives the position of the menu item     */
                                  /* to be deleted rather than an ID number. */

/*---------------------------------------------------------------------------*/
/*  Change Menu Item                                                         */
/*---------------------------------------------------------------------------*/

typedef struct tagCreateMenu
{
  unsigned char    data[(sizeof(DDEDATA)-1)];
  HWND             hMemuItem;     /* Handle of the menu item                 */
} CREATEMENU;

typedef union tagDDE_CREATEMENU
{
  DDEDATA     DDEdata;
  CREATEMENU  DDEmenu;
} DDE_CREATEMENU, *lpDDE_CREATEMENU;

/*---------------------------------------------------------------------------*/
/*  Start Menu Advise                                                        */
/*---------------------------------------------------------------------------*/

typedef struct tagSELECTMENU
{
  unsigned char  data[(sizeof(DDEDATA)-1)];
  unsigned short uIDSelected;     /* Command ID of the selected menu item    */
} SELECTMENU;

typedef union tagDDE_SELECTMENU
{
  DDEDATA     DDEdata;
  SELECTMENU  DDEmenu;
} DDE_SELECTMENU, *lpDDE_SELECTMENU;

#ifdef __cplusplus
  }
#endif
