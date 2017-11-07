/********************************************************************/
/*                                                                  */
/* 5769-XE1                                                         */
/* (C) Copyright IBM Corp. 1995,2005                                */
/* All rights reserved.                                             */
/* US Government Users Restricted Rights -                          */
/* Use, duplication or disclosure restricted                        */
/* by GSA ADP Schedule Contract with IBM Corp.                      */
/*                                                                  */
/* Licensed Materials-Property of IBM                               */
/*                                                                  */
/********************************************************************/
/*                                                                  */
/* Module:                                                          */
/*   CWBOBJ.H                                                       */
/*                                                                  */
/* Purpose:                                                         */
/*   It contains the declarations for the following API's:          */
/*                                                                  */
/* List APIs                                                        */
/*       cwbOBJ_CreateListHandle()                                  */
/*       cwbOBJ_CreateListHandleA()                                 */
/*       cwbOBJ_CreateListHandleW()                                 */
/*       cwbOBJ_SetListFilter()                                     */
/*       cwbOBJ_SetListFilterA()                                    */
/*       cwbOBJ_SetListFilterW()                                    */
/*       cwbOBJ_SetListFilterWithSplF()                             */
/*       cwbOBJ_ResetListFilter()                                   */
/*       cwbOBJ_SetListAttrsToRetrieve()                            */
/*       cwbOBJ_ResetListAttrsToRetrieve()                          */
/*       cwbOBJ_OpenList()                                          */
/*       cwbOBJ_GetListSize()                                       */
/*       cwbOBJ_CloseList()                                         */
/*       cwbOBJ_DeleteListHandle()                                  */
/*                                                                  */
/* Object APIs                                                      */
/*       cwbOBJ_GetObjHandle()                                      */
/*       cwbOBJ_GetObjID()                                          */
/*       cwbOBJ_GetObjHandleFromID()                                */
/*       cwbOBJ_GetObjAttr()                                        */
/*       cwbOBJ_GetObjAttrA()                                       */
/*       cwbOBJ_GetObjAttrW()                                       */
/*       cwbOBJ_GetObjAttrs()                                       */
/*       cwbOBJ_GetObjAttrsA()                                      */
/*       cwbOBJ_GetObjAttrsW()                                      */
/*       cwbOBJ_SetObjAttrs()                                       */
/*       cwbOBJ_RefreshObj()                                        */
/*       cwbOBJ_CopyObjHandle()                                     */
/*       cwbOBJ_DeleteObjHandle()                                   */
/*                                                                  */
/* Parameter Object APIs                                            */
/*       cwbOBJ_CreateParmObjHandle()                               */
/*       cwbOBJ_SetParameter()                                      */
/*       cwbOBJ_SetParameterA()                                     */
/*       cwbOBJ_SetParameterW()                                     */
/*       cwbOBJ_GetParameter()                                      */
/*       cwbOBJ_GetParameterA()                                     */
/*       cwbOBJ_GetParameterW()                                     */
/*       cwbOBJ_DeleteParmObjHandle()                               */
/*       cwbOBJ_CopyParmObjHandle()                                 */
/*                                                                  */
/* Writer job APIs                                                  */
/*       cwbOBJ_StartWriter()                                       */
/*       cwbOBJ_EndWriter()                                         */
/*                                                                  */
/* Output Queue APIs                                                */
/*       cwbOBJ_HoldOutputQueue()                                   */
/*       cwbOBJ_ReleaseOutputQueue()                                */
/*       cwbOBJ_PurgeOutputQueue()                                  */
/*                                                                  */
/* AFP Resource APIs                                                */
/*       cwbOBJ_CreateResourceHandle()                              */
/*       cwbOBJ_CreateResourceHandleA()                             */
/*       cwbOBJ_CreateResourceHandleW()                             */
/*       cwbOBJ_DisplayResource()                                   */
/*       cwbOBJ_OpenResource()                                      */
/*       cwbOBJ_OpenResourceForSplF()                               */
/*       cwbOBJ_OpenResourceForSplFA()                              */
/*       cwbOBJ_OpenResourceForSplFW()                              */
/*       cwbOBJ_ReadResource()                                      */
/*       cwbOBJ_SeekResource()                                      */
/*       cwbOBJ_CloseResource()                                     */
/*                                                                  */
/* Spooled File APIs for working with new spooled files             */
/*       cwbOBJ_CreateNewSplF()                                     */
/*       cwbOBJ_CreateNewSplFA()                                    */
/*       cwbOBJ_CreateNewSplFW()                                    */
/*       cwbOBJ_WriteNewSplF()                                      */
/*       cwbOBJ_GetSplFHandleFromNewSplF()                          */
/*       cwbOBJ_CloseNewSplF()                                      */
/*       cwbOBJ_CloseNewSplFAndGetHandle()                          */
/*                                                                  */
/* Spooled File APIs for reading spooled files                      */
/*       cwbOBJ_OpenSplF()                                          */
/*       cwbOBJ_ReadSplF()                                          */
/*       cwbOBJ_SeekSplF()                                          */
/*       cwbOBJ_CloseSplF()                                         */
/*                                                                  */
/* Spooled File APIs for manuipulating AS/400 spooled files         */
/*       cwbOBJ_MoveSplF()                                          */
/*       cwbOBJ_SendNetSplF()                                       */
/*       cwbOBJ_SendTCPSplF()                                       */
/*       cwbOBJ_HoldSplF()                                          */
/*       cwbOBJ_ReleaseSplF()                                       */
/*       cwbOBJ_DeleteSplF()                                        */
/*       cwbOBJ_CallExitPgmForSplF()                                */
/*       cwbOBJ_CreateSplFHandle()                                  */
/*       cwbOBJ_CreateSplFHandleA()                                 */
/*       cwbOBJ_CreateSplFHandleW()                                 */
/*       cwbOBJ_CreateSplFHandleEx()                                */
/*       cwbOBJ_CreateSplFHandleExA()                               */
/*       cwbOBJ_CreateSplFHandleExW()                               */
/*       cwbOBJ_IsViewerAvailable()                                 */
/*       cwbOBJ_DisplaySplF()                                       */
/*       cwbOBJ_DisplaySplFA()                                      */
/*       cwbOBJ_DisplaySplFW()                                      */
/*                                                                  */
/* Spooled File APIs for handling spooled file messages             */
/*       cwbOBJ_AnswerSplFMsg()                                     */
/*       cwbOBJ_AnswerSplFMsgA()                                    */
/*       cwbOBJ_AnswerSplFMsgW()                                    */
/*       cwbOBJ_GetSplFMsgAttr()                                    */
/*       cwbOBJ_GetSplFMsgAttrA()                                   */
/*       cwbOBJ_GetSplFMsgAttrW()                                   */
/*                                                                  */
/* Spooled File APIs for analyzing data                             */
/*       cwbOBJ_AnalyzeSplFData()                                   */
/*                                                                  */
/* Server program APIs                                              */
/*       cwbOBJ_GetNPServerAttr()                                   */
/*       cwbOBJ_GetNPServerAttrA()                                  */
/*       cwbOBJ_GetNPServerAttrW()                                  */
/*       cwbOBJ_SetConnectionsToKeep()                              */
/*       cwbOBJ_SetConnectionsToKeepA()                             */
/*       cwbOBJ_SetConnectionsToKeepW()                             */
/*       cwbOBJ_DropConnections()                                   */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Link with CWBAPI.LIB import library.                           */
/*   This module is to be used in conjunction with CWBOBJ.DLL.      */
/*                                                                  */
/*   Use these APIs for working with iSeries objects.  You can      */
/*   get a list of objects, retrieve attributes for an object, set  */
/*   attributes for an object and perform object specific tasks     */
/*   (hold an output queue, for example).  There are also apis for  */
/*   creating new spooled files.                                    */
/*                                                                  */
/*   When working with handles in these APIs, 0 will never be       */
/*   returned as a valid handle.                                    */
/*                                                                  */
/*   In addition to the return codes listed for APIs additional     */
/*   operating system specific return codes may also appear.  The   */
/*   precise meaning of these return codes can be found in the      */
/*   operating system manuals or relevant header files.             */
/*                                                                  */
/********************************************************************/

/* Prevent multiple includes */
#if !defined( _CWBOBJ_H_ )
  #define     _CWBOBJ_H_

#include <windows.h>

#include "CWB.H"


#ifdef __cplusplus
extern "C" {
#endif


/*------------------------------------------------------------------*/
/* handles typedefs used in the CWBOBJ APIs                         */
/*------------------------------------------------------------------*/
typedef cwb_Handle cwbOBJ_ParmHandle;    /* parameter list handle   */
typedef cwb_Handle cwbOBJ_ObjHandle;     /* object handle           */
typedef cwb_Handle cwbOBJ_ListHandle;    /* list handle             */


/*------------------------------------------------------------------*/
/* return codes                                                     */
/*------------------------------------------------------------------*/
#define CWBOBJ_START  CWB_LAST+1                    /* CWB_LAST is defined in CWB.H*/
#define CWBOBJ_RC_HOST_ERROR     CWBOBJ_START       /* Error on iSeries            */
#define CWBOBJ_RC_INVALID_TYPE   CWBOBJ_START + 1   /* Invalid type                */
#define CWBOBJ_RC_INVALID_KEY    CWBOBJ_START + 2   /* Invalid key                 */
#define CWBOBJ_RC_INVALID_INDEX  CWBOBJ_START + 3   /* Bad index to list           */
#define CWBOBJ_RC_LIST_OPEN      CWBOBJ_START + 4   /* The list is already opened  */
#define CWBOBJ_RC_LIST_NOT_OPEN  CWBOBJ_START + 5   /* The list has not been opened*/
#define CWBOBJ_RC_SEEKOUTOFRANGE CWBOBJ_START + 6   /* Seek offset is out of range */
#define CWBOBJ_RC_SPLFNOTOPEN    CWBOBJ_START + 7   /* Spooled file not opened     */
#define CWBOBJ_RC_RSCNOTOPEN     CWBOBJ_START + 7   /* Resource not opened         */
#define CWBOBJ_RC_SPLFENDOFFILE  CWBOBJ_START + 8   /* End of file was reached     */
#define CWBOBJ_RC_ENDOFFILE      CWBOBJ_START + 8   /* End of file was reached     */
#define CWBOBJ_RC_SPLFNOMESSAGE  CWBOBJ_START + 9   /* No message for spooled file */
#define CWBOBJ_RC_KEY_NOT_FOUND  CWBOBJ_START + 10  /* Key not found               */
#define CWBOBJ_RC_NO_EXIT_PGM    CWBOBJ_START + 11  /* No Exit program registered  */
#define CWBOBJ_RC_NOHOSTSUPPORT  CWBOBJ_START + 12  /* Host doesn't support function*/


/*------------------------------------------------------------------*/
/* defined keys or attribute ID's                                   */
/* These are the defined keys to be used with the CWBOBJ_ APIs.     */
/* See the specific APIs to see what keys are valid with which      */
/* APIs.                                                            */
/* See the iSeries Access for Windows API reference manual for more */
/* information about the keys.                                      */
/*------------------------------------------------------------------*/

typedef unsigned long cwbOBJ_KeyID;

 #define CWBOBJ_KEY_AFP          0x0000000A     /* AFP resources used                          */
 #define CWBOBJ_KEY_ALIGN        0x0000000B     /* Align forms before printing                 */
 #define CWBOBJ_KEY_ALWDRTPRT    0x0000000C     /* Allow direct printing                       */
 #define CWBOBJ_KEY_AUTHORITY    0x0000000D     /* Authority to users not on  output queue     */
 #define CWBOBJ_KEY_AUTHCHCK     0x0000000E     /* Authority allows user to all files on queue */
 #define CWBOBJ_KEY_LIBRARY      0x0000000F     /* Library name                                */
 #define CWBOBJ_KEY_AUTOEND      0x00000010     /* Automatically end writer *YES,*NO           */
 #define CWBOBJ_KEY_BKMGN_ACR    0x00000011     /* Back margin across                          */
 #define CWBOBJ_KEY_BKMGN_DWN    0x00000012     /* Back margin down                            */
 #define CWBOBJ_KEY_BKOVRLLIB    0x00000013     /* Back side overlay library                   */
 #define CWBOBJ_KEY_BKOVRLAY     0x00000014     /* Back side overlay name                      */
 #define CWBOBJ_KEY_BKOVL_DWN    0x00000015     /* Back overlay offset down                    */
 #define CWBOBJ_KEY_BKOVL_ACR    0x00000016     /* Back overlay offset across                  */
 #define CWBOBJ_KEY_CPI          0x00000017     /* Characters per inch                         */
 #define CWBOBJ_KEY_CODEDFNTLIB  0x00000018     /* Coded font library name                     */
 #define CWBOBJ_KEY_CODEPAGE     0x00000019     /* Code page                                   */
 #define CWBOBJ_KEY_CODEDFNT     0x0000001A     /* Coded font                                  */
 #define CWBOBJ_KEY_COPIES       0x0000001C     /* Copies (total)                              */
 #define CWBOBJ_KEY_COPIESLEFT   0x0000001D     /* Copies left to produce                      */
 #define CWBOBJ_KEY_CURPAGE      0x0000001E     /* Current page                                */
 #define CWBOBJ_KEY_DATAFORMAT   0x0000001F     /* Data format                                 */
 #define CWBOBJ_KEY_DATAQUELIB   0x00000020     /* Data queue library                          */
 #define CWBOBJ_KEY_DATAQUE      0x00000021     /* Data queue associated with output queue     */
 #define CWBOBJ_KEY_DATE         0x00000022     /* Date file was opened/msg was posted         */
 #define CWBOBJ_KEY_DFR_WRITE    0x00000023     /* Defer write                                 */
 #define CWBOBJ_KEY_PAGRTT       0x00000024     /* Degree of page rotation                     */
 #define CWBOBJ_KEY_DESTINATION  0x00000025     /* Destination type                            */
 #define CWBOBJ_KEY_DEVCLASS     0x00000026     /* Device class                                */
 #define CWBOBJ_KEY_DEVMODEL     0x00000027     /* Device model                                */
 #define CWBOBJ_KEY_DEVTYPE      0x00000028     /* Device type                                 */
 #define CWBOBJ_KEY_DISPLAYANY   0x00000029     /* Users can display any file on queue         */
 #define CWBOBJ_KEY_DRWRSEP      0x0000002A     /* Drawer to use for separators                */
 #define CWBOBJ_KEY_ENDPAGE      0x0000002B     /* Ending page number to print                 */
 #define CWBOBJ_KEY_FILESEP      0x0000002C     /* Number of file separators                   */
 #define CWBOBJ_KEY_FOLDREC      0x0000002D     /* Wrap text to next line                      */
 #define CWBOBJ_KEY_FONTID       0x0000002E     /* Font identifier to use (default)            */
 #define CWBOBJ_KEY_FORMFEED     0x0000002F     /* Type of paper  to be used                   */
 #define CWBOBJ_KEY_FORMTYPE     0x00000030     /* Name of the form to be used                 */
 #define CWBOBJ_KEY_FTMGN_ACR    0x00000031     /* Front margin across                         */
 #define CWBOBJ_KEY_FTMGN_DWN    0x00000032     /* Front margin down                           */
 #define CWBOBJ_KEY_FTOVRLLIB    0x00000033     /* Front side overlay library                  */
 #define CWBOBJ_KEY_FTOVRLAY     0x00000034     /* Front side overlay name                     */
 #define CWBOBJ_KEY_FTOVL_ACR    0x00000036     /* Front overlay offset across                 */
 #define CWBOBJ_KEY_FTOVL_DWN    0x00000035     /* Front overlay offset down                   */
 #define CWBOBJ_KEY_CHAR_ID      0x00000037     /* Set of graphic characters for this file     */
 #define CWBOBJ_KEY_JUSTIFY      0x00000038     /* Hardware justification                      */
 #define CWBOBJ_KEY_HOLD         0x00000039     /* Hold the spool file                         */
 #define CWBOBJ_KEY_JOBNAME      0x0000003B     /* Name of the job that created file           */
 #define CWBOBJ_KEY_JOBNUMBER    0x0000003C     /* Number of the job that created file         */
 #define CWBOBJ_KEY_JOBSEPRATR   0x0000003D     /* Number of job separators                    */
 #define CWBOBJ_KEY_USER         0x0000003E     /* Name of the user that created file          */
 #define CWBOBJ_KEY_LASTPAGE     0x0000003F     /* Last page that printed                      */
 #define CWBOBJ_KEY_LPI          0x00000040     /* Lines per inch                              */
 #define CWBOBJ_KEY_MFGTYPE      0x00000041     /* Manufacturer's type & model                 */
 #define CWBOBJ_KEY_MAXRECORDS   0x00000042     /* Maximum number of records allowed           */
 #define CWBOBJ_KEY_FORMTYPEMSG  0x00000043     /* Form type message option                    */
 #define CWBOBJ_KEY_MSGQUELIB    0x00000044     /* Message queue library                       */
 #define CWBOBJ_KEY_NUMFILES     0x00000045     /* Total spooled files on output queue         */
 #define CWBOBJ_KEY_OPCNTRL      0x00000046     /* Operator controlled                         */
 #define CWBOBJ_KEY_ORDER        0x00000047     /* Order on queue (sequence) - *FIFO, *JOBNBR  */
 #define CWBOBJ_KEY_OUTPTY       0x00000048     /* Output priority                             */
 #define CWBOBJ_KEY_OUTQUELIB    0x00000049     /* Output queue library                        */
 #define CWBOBJ_KEY_OUTQUE       0x0000004A     /* Output queue                                */
 #define CWBOBJ_KEY_OUTQUESTS    0x0000004B     /* output queue status                         */
 #define CWBOBJ_KEY_OVERFLOW     0x0000004C     /* Overflow line number                        */
 #define CWBOBJ_KEY_PAGELEN      0x0000004E     /* Page length                                 */
 #define CWBOBJ_KEY_MEASMETHOD   0x0000004F     /* Measurement method (*ROWCOL or *UOM)        */
 #define CWBOBJ_KEY_PAGEWIDTH    0x00000051     /* Page width                                  */
 #define CWBOBJ_KEY_MULTIUP      0x00000052     /* Logical pages per physical side             */
 #define CWBOBJ_KEY_POINTSIZE    0x00000053     /* The default font's point size               */
 #define CWBOBJ_KEY_FIDELITY     0x00000054     /* The error handling when printing            */
 #define CWBOBJ_KEY_DUPLEX       0x00000055     /* Print on both sides of paper                */
 #define CWBOBJ_KEY_PRTQUALITY   0x00000056     /* Print quality                               */
 #define CWBOBJ_KEY_PRTSEQUENCE  0x00000057     /* Print sequence                              */
 #define CWBOBJ_KEY_PRTTEXT      0x00000058     /* Text printed at bottom of each page         */
 #define CWBOBJ_KEY_PRINTER      0x00000059     /* Printer device name                         */
 #define CWBOBJ_KEY_PRTDEVTYPE   0x0000005A     /* Printer dev type (data stream type)         */
 #define CWBOBJ_KEY_PRTRFILELIB  0x0000005B     /* Printer file library                        */
 #define CWBOBJ_KEY_PRTRFILE     0x0000005C     /* Printer file                                */
 #define CWBOBJ_KEY_RMTPRTQ      0x0000005D     /* Remote print queue used on SNDTCPSPLF       */
 #define CWBOBJ_KEY_MSGQUE       0x0000005E     /* Message queue                               */
 #define CWBOBJ_KEY_RECLENGTH    0x0000005F     /* Record length                               */
 #define CWBOBJ_KEY_RMTSYSTEM    0x00000060     /* Remote system                               */
 #define CWBOBJ_KEY_RPLUNPRT     0x00000061     /* Replace unprintable characters              */
 #define CWBOBJ_KEY_RPLCHAR      0x00000062     /* Character to replace unprintables with      */
 #define CWBOBJ_KEY_RESTART      0x00000063     /* Where to restart printing at                */
 #define CWBOBJ_KEY_SAVESPLF     0x00000064     /* Whether to save after printing or not       */
 #define CWBOBJ_KEY_SENDPTY      0x00000065     /* Send priority                               */
 #define CWBOBJ_KEY_SRCDRWR      0x00000066     /* Source drawer                               */
 #define CWBOBJ_KEY_SPOOL        0x00000067     /* Spool the data                              */
 #define CWBOBJ_KEY_SPOOLFILE    0x00000068     /* Spool file name                             */
 #define CWBOBJ_KEY_SPLFNUM      0x00000069     /* Spool file number                           */
 #define CWBOBJ_KEY_SPLFSTATUS   0x0000006A     /* Spool file status                           */
 #define CWBOBJ_KEY_SCHEDULE     0x0000006B     /* When available to the writer                */
 #define CWBOBJ_KEY_STARTPAGE    0x0000006C     /* Starting page to print                      */
 #define CWBOBJ_KEY_DESCRIPTION  0x0000006D     /* Text description                            */
 #define CWBOBJ_KEY_TIME         0x0000006E     /* Time (eg. spooled file was opened at)       */
 #define CWBOBJ_KEY_PAGES        0x0000006F     /* Number of pages in spool file               */
 #define CWBOBJ_KEY_SCS2ASCII    0x00000071     /* Transform SCS to ASCII                      */
 #define CWBOBJ_KEY_UNITOFMEAS   0x00000072     /* Unit of measure                             */
 #define CWBOBJ_KEY_USERCMT      0x00000073     /* User comment                                */
 #define CWBOBJ_KEY_USERDATA     0x00000074     /* User data                                   */
 #define CWBOBJ_KEY_TOUSERID     0x00000075     /* User id to send spool file to               */
 #define CWBOBJ_KEY_TOADDRESS    0x00000076     /* Address of user to send file to             */
 #define CWBOBJ_KEY_VMMVSCLASS   0x00000077     /* VM/MVS SYSOUT class                         */
 #define CWBOBJ_KEY_WTRAUTOEND   0x00000078     /* When to automatically end writer            */
 #define CWBOBJ_KEY_WRITER       0x00000079     /* Writer job name                             */
 #define CWBOBJ_KEY_WTRJOBNUM    0x0000007A     /* Writer job number                           */
 #define CWBOBJ_KEY_WTRJOBSTS    0x0000007B     /* Writer job status                           */
 #define CWBOBJ_KEY_WTRJOBUSER   0x0000007C     /* Writer job user name                        */
 #define CWBOBJ_KEY_NUMBYTES     0x0000007D     /* Number of bytes to read/write               */
 #define CWBOBJ_KEY_SEEKOFF      0x0000007E     /* Seek offset                                 */
 #define CWBOBJ_KEY_SEEKORG      0x0000007F     /* Seek origin                                 */
 #define CWBOBJ_KEY_MSGTEXT      0x00000080     /* Message text                                */
 #define CWBOBJ_KEY_MSGHELP      0x00000081     /* Message help text                           */
 #define CWBOBJ_KEY_MSGREPLY     0x00000082     /* Message reply                               */
 #define CWBOBJ_KEY_ATTRDEFAULT  0x00000083     /* Attribute default value                     */
 #define CWBOBJ_KEY_ATTRMAX      0x00000084     /* Attribute maximum value                     */
 #define CWBOBJ_KEY_ATTRID       0x00000085     /* Attribute ID                                */
 #define CWBOBJ_KEY_ATTRMIN      0x00000086     /* Attribute minimum value                     */
 #define CWBOBJ_KEY_ATTRPOSSIBL  0x00000087     /* Possible value for attribute                */
 #define CWBOBJ_KEY_ATTRDESCRIPT 0x00000088     /* Attribute description                       */
 #define CWBOBJ_KEY_ATTRTYPE     0x00000089     /* Attribute type                              */
 #define CWBOBJ_KEY_NPSCCSID     0x0000008A     /* Server CCSID                                */
 #define CWBOBJ_KEY_NPSOBJECT    0x0000008B     /* Object ID                                   */
 #define CWBOBJ_KEY_NPSACTION    0x0000008C     /* Action ID                                   */
 #define CWBOBJ_KEY_NPSLEVEL     0x0000008D     /* Server code level                           */
 #define CWBOBJ_KEY_MSGTYPE      0x0000008E     /* Message type                                */
 #define CWBOBJ_KEY_WTRSTRPAGE   0x0000008F     /* Page to start the writer on                 */
 #define CWBOBJ_KEY_WTREND       0x00000090     /* When to end the writer                      */
 #define CWBOBJ_KEY_NUMWRITERS   0x00000091     /* Number of writers started to queue          */
 #define CWBOBJ_KEY_MSGID        0x00000093     /* Message ID                                  */
 #define CWBOBJ_KEY_INTERNETADDR 0x00000094     /* Internet address                            */
 #define CWBOBJ_KEY_WSCUSTMOBJ   0x00000095     /* Workstation customizing object              */
 #define CWBOBJ_KEY_WSCUSTMOBJL  0x00000096     /* Workstation customizing object library      */
 #define CWBOBJ_KEY_DELETESPLF   0x00000097     /* Delete file after sending?                  */
 #define CWBOBJ_KEY_DESTOPTION   0x00000098     /* Destinaton option sent                      */
 #define CWBOBJ_KEY_DBCSDATA     0x00000099     /* Contains DBCS character set data            */
 #define CWBOBJ_KEY_DBCSEXTENSN  0x0000009A     /* Process DBCS extension characters           */
 #define CWBOBJ_KEY_DBCSROTATE   0x0000009B     /* Rotate DBCS characters                      */
 #define CWBOBJ_KEY_DBCSCPI      0x0000009C     /* DBCS CPI                                    */
 #define CWBOBJ_KEY_DBCSSISO     0x0000009D     /* DBCS SI/SO positioning                      */
 #define CWBOBJ_KEY_HOLDTYPE     0x0000009E     /* When to hold spooled file                   */
 #define CWBOBJ_KEY_MSGSEV       0x0000009F     /* Message severity                            */
 #define CWBOBJ_KEY_OPENCMDS     0x000000A0     /* Retrieve Open Time SCS Commands             */
 #define CWBOBJ_KEY_SEPPAGE      0x000000A1     /* Print banner page or not                    */
 #define CWBOBJ_KEY_USRDFNDTA    0x000000A2     /* User defined data                           */
 #define CWBOBJ_KEY_USRDFNOPTS   0x000000A3     /* User defined options                        */
 #define CWBOBJ_KEY_USRDFNOBJLIB 0x000000A4     /* User defined object library                 */
 #define CWBOBJ_KEY_USRDFNOBJ    0x000000A5     /* User defined object                         */
 #define CWBOBJ_KEY_USRDFNOBJTYP 0x000000A6     /* User defined object type                    */
 #define CWBOBJ_KEY_USRTFMPGMLIB 0x000000A7     /* User data transform program library         */
 #define CWBOBJ_KEY_USRTFMPGM    0x000000A8     /* User data transform program                 */
 #define CWBOBJ_KEY_USRDRVPGMDTA 0x000000A9     /* User driver program data                    */
 #define CWBOBJ_KEY_USRDRVPGMLIB 0x000000AA     /* User driver program library                 */
 #define CWBOBJ_KEY_USRDRVPGM    0x000000AB     /* User driver program                         */
 #define CWBOBJ_KEY_WTRINIT      0x000000AC     /* When to initialize the printer device       */
 #define CWBOBJ_KEY_SPLSCS       0x000000AD     /* Type of SCS spooling to do                  */
 #define CWBOBJ_KEY_RSCLIB       0x000000AE     /* Resource library name                       */
 #define CWBOBJ_KEY_RSCNAME      0x000000AF     /* Resource name                               */
 #define CWBOBJ_KEY_RSCTYPE      0x000000B0     /* Resource object type                        */
 #define CWBOBJ_KEY_OBJEXTATTR   0x000000B1     /* Object extended attribute                   */
 #define CWBOBJ_KEY_PELDENSITY   0x000000B2     /* Font Pel Density "1"=240;"2"=300;           */
 #define CWBOBJ_KEY_RSCAVAIL      0x000000B3    /* Resource available?                     */
 #define CWBOBJ_KEY_NPSNLV        0x000000B4    /* NPS NLV ("2924") .                      */
 #define CWBOBJ_KEY_INSERT_5A     0x000000B5    /* Insert 5A?                              */
 #define CWBOBJ_KEY_FORMDEF       0x000000B6    /* Formdef name                            */
 #define CWBOBJ_KEY_FORMDEFLIB    0x000000B7    /* Formdef library                         */
 #define CWBOBJ_KEY_PRECMPT_SIZE  0x000000B8    /* Precompute the number of bytes?         */
 #define CWBOBJ_KEY_DEV_OUTTYPE   0x000000B9    /* Type of output device ie printer,tape  */
 #define CWBOBJ_KEY_PRT_ASSIGNED  0x000000BA    /* Indicates how printer is assigned      */
 #define CWBOBJ_KEY_WRITING_STAT  0x000000BB    /* Indicates whether writer is writing    */
 #define CWBOBJ_KEY_SYS_WHERE_CRT 0x000000BC    /* System where spooled file was created  */
 #define CWBOBJ_KEY_NETWORK_ID    0x000000BD    /* Network Id where file created          */
 #define CWBOBJ_KEY_ALIGN_FORMS   0x000000BE    /* Time when align forms msg will be sen  */
 #define CWBOBJ_KEY_CHANGES_TIME  0x000000BF    /* Time changes take affect               */
 #define CWBOBJ_KEY_OUTPUT_BIN    0x000000C0    /* Output bin used by printer             */
 #define CWBOBJ_KEY_WRITER_START  0x000000C1    /* Indicates whether writer is started    */
 #define CWBOBJ_KEY_REDUCE_OUPUT  0x000000C2    /* Indicates how logical pages print      */
 #define CWBOBJ_KEY_LINE_SPACING  0x000000C3    /* Type of line spacing used              */
 #define CWBOBJ_KEY_CONTROL_CHAR  0x000000C4    /* File contains ANS control chars?       */
 #define CWBOBJ_KEY_WRITER_USER   0x000000C5    /* User writer was started by             */
 #define CWBOBJ_KEY_API_CREATED   0x000000C6    /* Whether spooled file was create by API */
 #define CWBOBJ_KEY_DEVICE_STATUS 0x000000C7    /* Printer device status                  */
 #define CWBOBJ_KEY_LOGICAL_STAT  0x000000C8    /* Logical status of printer              */
 #define CWBOBJ_KEY_WAITING_DEV   0x000000C9    /* Waiting for device status              */
 #define CWBOBJ_KEY_WAITING_MSG   0x000000CA    /* Waiting for message status             */
 #define CWBOBJ_KEY_WAITING_DATA  0x000000CB    /* Waiting for data status of writer      */
 #define CWBOBJ_KEY_END_PENDING   0x000000CC    /* End writer pending status              */
 #define CWBOBJ_KEY_ON_JOB_QUEUE  0x000000CD    /* Indicates whether writer is on job que */
 #define CWBOBJ_KEY_BTWEEN_COPIES 0x000000CE    /* Writer between copies yes or no?       */
 #define CWBOBJ_KEY_BTWEEN_FILES  0x000000CF    /* Writer between files yes or no?        */
 #define CWBOBJ_KEY_HELD_STATUS   0x000000D0    /* Writer held yes or no?                 */
 #define CWBOBJ_KEY_HOLD_PENDING  0x000000D1    /* Hold pending status                    */
 #define CWBOBJ_KEY_INIT_PRINTER  0x000000D2    /* Specify time to initialize printer     */
 #define CWBOBJ_KEY_ENVELOPE_SIZE 0x000000D3    /* Size of envelope                       */
 #define CWBOBJ_KEY_PAPER_SOURCE1 0x000000D4    /* Size of paper in paper source 1        */
 #define CWBOBJ_KEY_PAPER_SOURCE2 0x000000D5    /* Size of paper in paper source 2        */
 #define CWBOBJ_KEY_PAGE_AT_TIME  0x000000D6    /* Open file to be read a page a time     */
 #define CWBOBJ_KEY_PAGE_NUMBER   0x000000D7    /* Page number to be read page at a time  */
 #define CWBOBJ_KEY_VIEW_FIDELITY 0x000000D8    /* Type of viewing fidelity requested     */
 #define CWBOBJ_KEY_NUMBYTES_LRG  0x000000D9    /* Number of bytes in large files>2**31-1 */
 #define CWBOBJ_KEY_ESTIMATED_CNT 0x000000DA    /* Page count estimated yes or no?        */
 #define CWBOBJ_KEY_SEEK_OFF_LRG  0x000000DB    /* Seek offset for large files            */
 #define CWBOBJ_KEY_ITEM_REP_CAP  0x000000DC    /* Return multiple items per reply        */
 #define CWBOBJ_KEY_USER_CMT_LST  0x000000DD    /* Surpress user comment                  */
 #define CWBOBJ_KEY_MAX_JOBS      0x000000DE    /* Max number of jobs to return in list   */
 #define CWBOBJ_KEY_SEQ_READ      0x000000DF    /* Open spoolfile for sequential read     */
 #define CWBOBJ_KEY_OPEN_CMD_SIZE 0x000000E0    /* Size of Open time commands             */
 #define CWBOBJ_KEY_IPP_CHARSET   0x000000E1    /* Ipp Character set                      */ 
 #define CWBOBJ_KEY_IPP_SECURITY  0x000000E2    /* Ipp security method used to create file*/ 
 #define CWBOBJ_KEY_IPP_AUTHEN    0x000000E3    /* Ipp authentication method used         */
 #define CWBOBJ_KEY_IPP_JOB_ID    0x000000E4    /* Ipp job id                             */
 #define CWBOBJ_KEY_IPP_URI       0x000000E5    /* Ipp Printer URI                        */
 #define CWBOBJ_KEY_IPP_JOB_NAME  0x000000E6    /* Ipp job name which created file        */
 #define CWBOBJ_KEY_IPP_JOB_LANG  0x000000E7    /* Ipp job natural language               */
 #define CWBOBJ_KEY_IPP_JOB_USER  0x000000E8    /* Ipp job user name which created file   */
 #define CWBOBJ_KEY_JOB_USER_LANG 0x000000E9    /* Ipp user natural language              */
 #define CWBOBJ_KEY_JOB_WTR_DATE  0x000000EA    /* Date writer began processing file      */
 #define CWBOBJ_KEY_JOB_DATE_COMP 0x000000EB    /* Date writer completed processing file  */
 #define CWBOBJ_KEY_JOB_WTR_TIME  0x000000EC    /* Time writer began processing file      */
 #define CWBOBJ_KEY_JOB_TIME_COMP 0x000000ED    /* Time writer completed processing file  */
 #define CWBOBJ_KEY_EDGE_STITCH_REF  0x000000EE /* Edge stitch reference                  */
 #define CWBOBJ_KEY_EDGE_REF_OFF  0x000000EF    /* Edge stitch reference offset           */
 #define CWBOBJ_KEY_NUM_STAPLES   0x000000F0    /* Number of staples in edge stitch       */
 #define CWBOBJ_KEY_STAPLE_OFF_INFO 0x000000F1  /* Edge stitch staple offset info         */
 #define CWBOBJ_KEY_SAD_STITCH_REF  0x000000F2  /* Saddle stitch reference                */
 #define CWBOBJ_KEY_NUM_SAD_STAPLES 0x000000F3  /* Number of saddle stitch staples        */
 #define CWBOBJ_KEY_SAD_STITCH_OFF  0x000000F4  /* Saddle stitch offset                   */
 #define CWBOBJ_KEY_PAGE_DEF_LIB  0x000000F5    /* Page definition library name           */
 #define CWBOBJ_KEY_PAGE_DEF      0x000000F6    /* Page definition name                   */
 #define CWBOBJ_KEY_CVT_LINE_DATA 0x000000F7    /* Convert line data                      */
 #define CWBOBJ_KEY_CORN_STAPLE   0x000000F8    /* Corner staple                          */
 #define CWBOBJ_KEY_USR_LIB_LIST  0x000000F9    /* User library list names                */
 #define CWBOBJ_KEY_IPP_ATTR_LANG 0x000000FA    /* Ipp attribues natural language         */
 #define CWBOBJ_KEY_JOBSYSTEM     0x000000FB    /* Job System Name which created file     */
 #define CWBOBJ_KEY_AUXSTORPOOL   0x000000FC    /* Auxilliary storage pool                */
 #define CWBOBJ_KEY_ENDDATE       0x000000FD    /* Ending date                            */
 #define CWBOBJ_KEY_ENDTIME       0x000000FE    /* Ending time                            */
 #define CWBOBJ_KEY_RMTLOCNAME    0x000000FF    /* Remote location name                   */
 #define CWBOBJ_KEY_IMGTRANSCONF  0x00000100    /* Image transform configuration          */
 #define CWBOBJ_KEY_COLORSUPPORT  0x00000101    /* Color support                          */
 #define CWBOBJ_KEY_COLORPPM      0x00000102    /* Color pages per minute                 */
 #define CWBOBJ_KEY_BLACKRPPM     0x00000103    /* Black pages per minute                 */
 #define CWBOBJ_KEY_DUPLEXSUPPORT 0x00000104    /* Duplex support                         */
 #define CWBOBJ_KEY_PRINTERLOC    0x00000105    /* Printer location                       */
 #define CWBOBJ_KEY_DATASUPPORT   0x00000106    /* Data streams supported                 */
 #define CWBOBJ_KEY_ACCOUNTCODE   0x00000109    /* Accounting code                        */
 #define CWBOBJ_KEY_ASPDEVNAME    0x0000010A    /* ASP Device name                        */
 #define CWBOBJ_KEY_ACIF          0x0000013B    /* ACIF Processing requested              */

                                                                                       
 #define CWBOBJ_KEY_LASTKEY CWBOBJ_KEY_ACIF                                       
                                                                                       
                                                                                       
/*-------------------------------------------------------------------*/
/* define the possible data types for an attribute                   */
/* CWBOBJ_TYPE_SHORT is a two byte, unsigned, integer number         */
/* CWBOBJ_TYPE_LONG is a four byte, unsigned, integer number         */
/* CWBOBJ_TYPE_STRING is a null-terminated string.                   */
/* CWBOBJ_TYPE_FLOAT is a 4 byte floating point number in IEEE format*/
/* CWBOBJ_TYPE_STRLIST is a list of null-terminated strings ending   */
/*                     with an extra null byte.                      */
/*-------------------------------------------------------------------*/

typedef unsigned long cwbOBJ_DataType;

#define  CWBOBJ_TYPE_SHORT    0x00000001  /* unsigned short integer    */
#define  CWBOBJ_TYPE_LONG     0x00000002  /* unsigned long integer     */
#define  CWBOBJ_TYPE_STRING   0x00000003  /* null-terminated string    */
#define  CWBOBJ_TYPE_FLOAT    0x00000004  /* IEEE floating point value */
#define  CWBOBJ_TYPE_BINARY   0x00000005  /* binary data               */
#define  CWBOBJ_TYPE_STRLIST  0x00000006  /* list of strings           */


/*-------------------------------------------------------------------*/
/* different types of lists allowed                                  */
/*-------------------------------------------------------------------*/
typedef unsigned long   cwbOBJ_ListType;
typedef cwbOBJ_ListType cwbOBJ_ObjType;

#define  CWBOBJ_LIST_SPLF  0x00000001    /* list spooled files       */
#define  CWBOBJ_LIST_OUTQ  0x00000002    /* list output queues       */
#define  CWBOBJ_LIST_PRTD  0x00000003    /* list printer devices     */
#define  CWBOBJ_LIST_PRTF  0x00000004    /* list printer files       */
#define  CWBOBJ_LIST_WTR   0x00000005    /* list writers             */
#define  CWBOBJ_LIST_LIB   0x00000006    /* list libraries           */
#define  CWBOBJ_LIST_RSC   0x00000007    /* list afp resources       */


/*-------------------------------------------------------------------*/
/* types of AFP resources allowed.  Values can be OR'd together to   */
/* provide input for listing multiple resource types or used alone   */
/* to provide the type of one particular resource                    */
/*-------------------------------------------------------------------*/
typedef unsigned long cwbOBJ_AFPResourceType;
#define CWBOBJ_AFPRSC_FONT     0x00000001  /* Font resource          */
#define CWBOBJ_AFPRSC_FORMDEF  0x00000002  /* Form definition        */
#define CWBOBJ_AFPRSC_OVERLAY  0x00000004  /* Overlay                */
#define CWBOBJ_AFPRSC_PAGESEG  0x00000008  /* Pagesegment            */
#define CWBOBJ_AFPRSC_PAGEDEF  0x00000010  /* Page Definition        */

/*-------------------------------------------------------------------*/
/* Different types of list openings allowed                          */
/*  For the first release only synchronous list are allowed.         */
/*                                                                   */
/*  CWBOBJ_LIST_OPEN_SYNCHRONOUS - open the list synchronously. The  */
/*   cwbOBJ_OpenList() API will not return until the list is built.  */
/*-------------------------------------------------------------------*/
typedef unsigned long cwbOBJ_List_OpenType;

#define CWBOBJ_LIST_OPEN_SYNCH  0x00000001 /* open list synchronously*/

/*-------------------------------------------------------------------*/
/* status that a list can be in                                      */
/*-------------------------------------------------------------------*/
typedef unsigned long cwbOBJ_List_Status;

#define  CWBOBJ_LISTSTS_COMPLETED   0x00000001 /* list completely built*/
#define  CWBOBJ_LISTSTS_NOTDONEYET  0x00000002 /* list not yet done    */


/*------------------------------------------------------------------*/
/* enumerated origins for seeking when reading a spooled file.      */
/*------------------------------------------------------------------*/
typedef unsigned long cwbOBJ_SeekOrigin;

#define  CWBOBJ_SEEK_BEGINNING  0x00000001 /* from beginning of file    */
#define  CWBOBJ_SEEK_CURRENT    0x00000002 /* from current read position*/
#define  CWBOBJ_SEEK_ENDING     0x00000003 /* from ending of file       */

/*-------------------------------------------------------------------*/
/* define the possible spooled file data types                       */
/* CWBOBJ_DT_USERASCII - default ascii transparent data              */
/* CWBOBJ_DT_SCS - SCS data                                          */
/* CWBOBJ_DT_AFP - AFP data                                          */
/*-------------------------------------------------------------------*/
typedef unsigned long cwbOBJ_SplFDataType;

#define  CWBOBJ_DT_USERASCII  0x00000001  /* *USERASCII              */
#define  CWBOBJ_DT_SCS        0x00000002  /* *SCS                    */
#define  CWBOBJ_DT_AFP        0x00000003  /* *AFPDS                  */

/*-------------------------------------------------------------------*/
/* define the possible spool SCS values - used when creating a new   */
/* spooled file.                                                     */
/* CWBOBJ_SPLSCS_NO - file contains no SCS data                      */
/* CWBOBJ_SPLSCS_YES - file has SCS data                             */
/* CWBOBJ_SPLSCS_PASSTHRU - unsupported SCS cmds are passed thru     */
/*-------------------------------------------------------------------*/
#define  CWBOBJ_SPLSCS_NO        0x00000000  /* NO SCS               */
#define  CWBOBJ_SPLSCS_YES       0x00000001  /* SCS                  */
#define  CWBOBJ_SPLSCS_PASSTHRU  0x00000002  /* Passthru all SCS cmds*/


/*-------------------------------------------------------------------*/
/* define bits that can be turned on in the flags parameter to the   */
/* cwbOBJ_DisplaySplF() API.                                         */
/*-------------------------------------------------------------------*/
#define CWBOBJ_DSPSPLF_WAIT   0x00000001   /* Wait for viewer        */

/*-------------------------------------------------------------------*/
/* define structure used as input to the cwbOBJ_GetObjAttrs() API    */
/* This structure should be packed (aligned on a byte boundary) when */
/* passed in.                                                        */
/*-------------------------------------------------------------------*/
#include "CWBPACK1.H"            /* 1-byte alignment                 */
typedef struct
{
   cwbOBJ_KeyID  key;
   void          *buffer;
   unsigned long bufLen;
} cwbOBJ_GetObjAttrParms;
#include "CWBPACK0.H"             /* turn default alignment back on */

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_AnalyzeSplFData                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Analyze data for a spooled file and give a best guess as to    */
/*   what the data type is.                                         */
/*                                                                  */
/* Parameters:                                                      */
/*   const char *data - input                                       */
/*     pointer to data to be analyzed.                              */
/*                                                                  */
/*   unsigned long bufLen - input                                   */
/*     The length of the buffer pointed to by data.                 */
/*                                                                  */
/*   cwbOBJ_SplFDataType *dataType - output                         */
/*     On output this will contain the data type.  If the data type */
/*     can not be determined, it defaults to CWBOBJ_DT_USERASCII.   */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_PARAMETER  - Invalid parameter specified.          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This uses the same routine that is used during the creation    */
/*   of spooled files that don't have a data type specified or have */
/*   a data type of *AUTO specified.                                */
/*   The result defaults to *USERASCII if it can not be determined. */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbOBJ_AnalyzeSplFData(
                              const char          *data,
                              unsigned long        bufLen,
                              cwbOBJ_SplFDataType *dataType,
                              cwbSV_ErrHandle      errorHandle);


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_AnswerSplFMsg                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Answer the message that the spooled file is waiting on.        */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle splFHandle - input                            */
/*     Handle of the spooled file to answer the message for.        */
/*                                                                  */
/*   const char *msgAnswer - input                                  */
/*     Pointer to a ASCIIZ string that contains the answer for the  */
/*     message.                                                     */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_INVALID_HANDLE - Handle is not valid spooled file handle.  */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*   CWBOBJ_RC_INVALID_TYPE - Handle is not a spooled file handle.  */
/*   CWBOBJ_RC_SPLFNOMESSAGE - The spooled file isn't waiting on a  */
/*                               message.                           */
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
unsigned int CWB_ENTRY  cwbOBJ_AnswerSplFMsg(
                               cwbOBJ_ObjHandle    splFHandle,
                               const char         *msgAnswer,
                               cwbSV_ErrHandle     errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbOBJ_AnswerSplFMsgA(
                                      cwbOBJ_ObjHandle    splFHandle
                                    , LPCSTR              msgAnswer
                                    , cwbSV_ErrHandle     errorHandle
                                           );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbOBJ_AnswerSplFMsgW(
                                      cwbOBJ_ObjHandle    splFHandle
                                    , LPCWSTR             msgAnswer
                                    , cwbSV_ErrHandle     errorHandle
                                           );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbOBJ_AnswerSplFMsg            cwbOBJ_AnswerSplFMsgW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbOBJ_AnswerSplFMsg            cwbOBJ_AnswerSplFMsgA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_CallExitPgmForSplF                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Instructs the ClientAccess/400 Netprint server program,        */
/*   QNPSERVR, to call down its exit program chain passing this     */
/*   spooled file's ID and some application specified data as       */
/*   parameters.                                                    */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle splFHandle - input                            */
/*     Handle of the spooled file to be passes as a parameter to    */
/*     the exit programs.                                           */
/*                                                                  */
/*   void *data - input                                             */
/*     Pointer to a block of date that will be passed to the exit   */
/*     programs.  The format of this data is exit program specific. */
/*                                                                  */
/*   unsigned long dataLen - input                                  */
/*     length of data pointed to by pData.                          */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not valid spooled file handle.  */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*   CWBOBJ_RC_INVALID_TYPE - Handle is not a spooled file handle.  */
/*   CWBOBJ_RC_NO_EXIT_PGM -  No exit program is registered with    */
/*                              the Network Print server.           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This is a way for a client program to communicate with its     */
/*   server portion to do processing of spooled files.              */
/*   All exit programs registered with the QNPSERVR program on the  */
/*   iSeries will be called, so it is up to the client program and  */
/*   exit program to architect the format of the data in *data such */
/*   that the exit program can recognize it.                        */
/*   See the iSeries 'Guide to Programming for Print' for information*/
/*   on the interface between the QNPSERVR server program and the   */
/*   exit programs.                                                 */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_CallExitPgmForSplF(
                               cwbOBJ_ObjHandle    splFHandle,
                               void               *data,
                               unsigned long       dataLen,
                               cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_CloseNewSplF                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Closes a newly created spooled file.                           */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle newSplFHandle - input                         */
/*     New spooled file handle.  This is the handle passed back on  */
/*     the cwbOBJ_CreateNewSplF() API.                              */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not valid spooled file handle.  */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Once a spooled file is closed, you can no longer write to it   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbOBJ_CloseNewSplF(
                              cwbOBJ_ObjHandle     newSplFHandle,
                              cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_CloseNewSplFAndGetHandle                                */
/*                                                                  */
/* Purpose:                                                         */
/*   Closes a newly created spooled file and returns a handle to it.*/
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle newSplFHandle - input                         */
/*     New spooled file handle.  This is the handle passed back on  */
/*     the cwbOBJ_CreateNewSplF() API.                              */
/*                                                                  */
/*                                                                  */
/*   cwbOBJ_ObjHandle *splFHandle - output                          */
/*     Pointer to an object handle that, upon successful,           */
/*     completion of this call, will hold the spooled file handle.  */
/*     This handle may be used with other APIs that take a          */
/*     spooled file handle as input.                                */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not valid spooled file handle.  */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*                                                                  */
/* Usage Notes:                                                     */
/*    The handle returned in splFHandle must be released with the   */
/*    cwbOBJ_DeleteObjHandle() API in order to free resources.      */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbOBJ_CloseNewSplFAndGetHandle(
                              cwbOBJ_ObjHandle     newSplFHandle,
                              cwbOBJ_ObjHandle    *splFHandle,
                              cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_CloseList                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Closes an opened list.                                         */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ListHandle listHandle - input                           */
/*     Handle of the list to be closed.  This list must be opened.  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not an allocated list handle.   */
/*   CWBOBJ_RC_LIST_NOT_OPEN - The list isn't open.                 */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Closing the list frees the memory used by the list to hold its */
/*   items.                                                         */
/*   Any object handles gotten with cwbOBJ_GetObjHandle() API       */
/*   should be released before closing the list to free resources.  */
/*   These handles are no longer valid.                             */
/*                                                                  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_CloseList(
                               cwbOBJ_ListHandle   listHandle,
                               cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_CloseResource                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Closes an AFP Resource object that was previously opened for   */
/*   for reading.                                                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle resourceHandle - input                        */
/*     Handle of the resource to be closed.                         */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not valid resource handle.      */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*   CWBOBJ_RC_RSCNOTOPEN -  Resource not opened                    */
/*                                                                  */
/* Usage Notes:                                                     */
/*   If the handle for the resource was obtained via a call to the  */
/*   cwbOBJ_OpenResourceForSplF() API, then this api will delete the*/
/*   handle for you (the handle was dynamically allocated for you   */
/*   when you opened the resource and this call deallocates it).    */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_CloseResource(
                               cwbOBJ_ObjHandle    resourceHandle,
                               cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_CloseSplF                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Closes an iSeries spooled file that was previously opened for  */
/*   for reading.                                                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle splFHandle - input                            */
/*     Handle of the spooled file to be closed.                     */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not valid spooled file handle.  */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*   CWBOBJ_RC_SPLFNOTOPEN -  Spooled file not opened               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_CloseSplF(
                               cwbOBJ_ObjHandle    splFHandle,
                               cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_CopyObjHandle                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Creates a duplicate handle to an object.                       */
/*   Use this API to get another handle to the same iSeries object. */
/*   This new handle will be valid until the                        */
/*   cwbOBJ_DeleteObjHandle() API has been called to release it.    */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle objectHandle - input                          */
/*     Handle of the object to copy.                                */
/*                                                                  */
/*   cwbOBJ_ObjHandle *newObjectHandle - output                     */
/*     Upon successful competition of this call, this handle will   */
/*     contain the new object handle.                               */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not an allocated object handle. */
/*                                                                  */
/* Usage Notes:                                                     */
/*   If you have a handle to an object in a list and wish to        */
/*   maintain a handle to that object after the list has been closed*/
/*   this API allows you to do that.                                */
/*   cwbOBJ_DeleteObjHandle() must be called to release resources   */
/*   for this handle.                                               */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_CopyObjHandle(
                               cwbOBJ_ObjHandle    objectHandle,
                               cwbOBJ_ObjHandle   *newObjectHandle,
                               cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_CopyParmObjHandle                                       */
/*                                                                  */
/* Purpose:                                                         */
/*   Creates a duplicate parameter list object.                     */
/*   All attribute keys and values in the parameter list object     */
/*   will be copied to the new parameter list object.               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ParmHandle parmListHandle - input                       */
/*     Handle of the parameter list object to copy.                 */
/*                                                                  */
/*   cwbOBJ_ParmHandle *newParmListHandle - output                  */
/*     Upon successful competition of this call, this handle will   */
/*     contain the new parameter list object handle.                */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not an allocated object handle. */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The cwbOBJ_DeleteParmObjectHandle API must be called to free   */
/*   resources allocated by this call.                              */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_CopyParmObjHandle(
                               cwbOBJ_ParmHandle    parmListHandle,
                               cwbOBJ_ParmHandle   *newParmListHandle,
                               cwbSV_ErrHandle      errorHandle);


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_CreateListHandle                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Allocates a handle for a list of objects.                      */
/*   After a list handle has been allocated, the filter criteria    */
/*   may be set for the list with the cwbOBJ_SetListFilter() API,   */
/*   the list may be built with the cwbOBJ_OpenList() API, etc.     */
/*                                                                  */
/*   cwbOBJ_DeleteListHandle() should be called to deallocated this */
/*   list handle and free any resources used by it.                 */
/*                                                                  */
/* Parameters:                                                      */
/*   const char *systemName - input                                 */
/*     Pointer to the system name contained in ASCIIZ string        */
/*                                                                  */
/*   cwbOBJ_ListType type - input                                   */
/*     Type of list to allocate (eg. spooled file list, output queue*/
/*       list, etc).                                                */
/*                                                                  */
/*   cwbOBJ_ListHandle *listHandle - output                         */
/*     Pointer to a list handle that will be passed back on output. */
/*     This handle is needed for other calls using the list.        */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
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
/*   Caller must call cwbOBJ_DeleteListHandle when done using this  */
/*   list handle.                                                   */
/*   Typical calling sequence for retrieving a list of objects would*/
/*   be:                                                            */
/*     1.cwbOBJ_CreateListHandle()                                  */
/*     2.cwbOBJ_SetListFilter()   { repeated as needed }            */
/*     3.cwbOBJ_OpenList()                                          */
/*     4.cwbOBJ_GetListSize() to get the size of the list           */
/*     5.For n=0 to list size - 1                                   */
/*         cwbOBJ_GetObjHandle for list item in position n          */
/*             do something with the object                         */
/*         cwbOBJ_DeleteObjHandle()                                 */
/*     6.cwbOBJ_CloseList()                                         */
/*         may go back to step 2. here                              */
/*     7.cwbOBJ_DeleteListHandle()                                  */
/*                                                                  */
/*   Lists of type CWBOBJ_LIST_RSC are only supported on iSeries    */
/*   at version V3R7 or later.                                      */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY  cwbOBJ_CreateListHandle(
                               const char         *systemName,
                               cwbOBJ_ListType     type,
                               cwbOBJ_ListHandle  *listHandle,
                               cwbSV_ErrHandle     errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbOBJ_CreateListHandleA(
                                       LPCSTR              systemName
                                     , cwbOBJ_ListType     type
                                     , cwbOBJ_ListHandle  *listHandle
                                     , cwbSV_ErrHandle     errorHandle
                                              );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbOBJ_CreateListHandleW(
                                       LPCWSTR             systemName
                                     , cwbOBJ_ListType     type
                                     , cwbOBJ_ListHandle  *listHandle
                                     , cwbSV_ErrHandle     errorHandle
                                              );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbOBJ_CreateListHandle         cwbOBJ_CreateListHandleW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbOBJ_CreateListHandle         cwbOBJ_CreateListHandleA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_CreateNewSplF                                           */
/*                                                                  */
/* Purpose:                                                         */
/*   Creates a new spooled file on the AS\400                       */
/*                                                                  */
/* Parameters:                                                      */
/*   const char *systemName - input                                 */
/*     Pointer to the system name contained in ASCIIZ string        */
/*                                                                  */
/*   cwbOBJ_ParmHandle *parmListHandle - input                      */
/*     Optional.  A pointer to a valid parameter list object handle */
/*     that contains parameters for creating the spooled file.      */
/*     Parameters set in this list override what is in the printer  */
/*     file and the *outputQueueHandle parameter.                   */
/*                                                                  */
/*   cwbOBJ_ObjHandle *printerFileHandle - input                    */
/*     Optional.  A pointer to a valid printer file object handle   */
/*     that references the printer file to be used when creating    */
/*     this spooled file.  The printer file must exist on the same  */
/*     system that this spooled file is being created on.           */
/*                                                                  */
/*   cwbOBJ_ObjHandle *outputQueueHandle - input                    */
/*     Optional.  A pointer to a valid output queue object handle   */
/*     that references the output queue that this spooled file      */
/*     should be created on. The output queue must exist on the same*/
/*     system that this spooled file is being created on.           */
/*     If the output queue is set in the *parmListHandle parameter  */
/*     (with CWBOBJ_KEY_OUTQUELIB & CWBOBJ_KEY_OUTQUE) it will over-*/
/*     ride the output queue specified by this output queue handle. */
/*                                                                  */
/*   cwbOBJ_ObjHandle *newSplFHandle - output                       */
/*     A pointer to a object handle that will be filled in upon     */
/*     successful completion of this call with the newly created    */
/*     spooled file handle.                                         */
/*     This handle is needed to write data into and close the new   */
/*     spooled file.                                                */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_INVALID_HANDLE - Handle is not valid                       */
/*   CWB_INVALID_PARAMETER  - Invalid parameter specified.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/*   If the parmListHandle is NULL, or doesn't specify an           */
/*   attribute, the attribute is taken from the printer file used.  */
/*   If the output queue is specified with the *parmListHandle,     */
/*   this will override what is specified in the *outputQueueHandle */
/*   parameter.                                                     */
/*                                                                  */
/*   If the output queue is not specified (not in the               */
/*   *parmListHandle AND outputQueueHandle is NULL), the output     */
/*   queue used is taken from the printer file.                     */
/*                                                                  */
/*   If the printer file is not specified (printerFileHandle is     */
/*   NULL), the server will use the default network print printer   */
/*   file, *LIBL/QNPSPRTF.                                          */
/*                                                                  */
/*   The following parameter key's may be set in the pParmListHandle*/
/*   object:                                                        */
/*                                                                  */
/*       CWBOBJ_KEY_ALIGN       - Align page                        */
/*       CWBOBJ_KEY_BKOVRLLIB   - Back overlay library name         */
/*       CWBOBJ_KEY_BKOVRLAY    - Back overlay                      */
/*       CWBOBJ_KEY_BKOVL_ACR   - Back overlay offset across        */
/*       CWBOBJ_KEY_BKOVL_DWN   - Back overlay offset down          */
/*       CWBOBJ_KEY_CPI         - Characters Per Inch               */
/*    (1)CWBOBJ_KEY_CODEPAGE    - Code page                         */
/*       CWBOBJ_KEY_COPIES      - Copies                            */
/*       CWBOBJ_KEY_DBCSDATA    - Contains DBCS Data                */
/*       CWBOBJ_KEY_DBCSEXTENSN - Process DBCS Extension characters */
/*       CWBOBJ_KEY_DBCSROTATE  - DBCS character rotation           */
/*       CWBOBJ_KEY_DBCSCPI     - DBCS CPI                          */
/*       CWBOBJ_KEY_DBCSSISO    - DBCS SO/SI spacing                */
/*       CWBOBJ_KEY_DFR_WRITE   - Defer writing                     */
/*       CWBOBJ_KEY_ENDPAGE     - Ending page                       */
/*    (2)CWBOBJ_KEY_FILESEP     - File Separators                   */
/*       CWBOBJ_KEY_FOLDREC     - Fold records                      */
/*       CWBOBJ_KEY_FONTID      - Font identifier                   */
/*       CWBOBJ_KEY_FORMFEED    - Form feed                         */
/*       CWBOBJ_KEY_FORMTYPE    - Form type                         */
/*       CWBOBJ_KEY_FTOVRLLIB   - Front overlay library name        */
/*       CWBOBJ_KEY_FTOVRLAY    - Front overlay                     */
/*       CWBOBJ_KEY_FTOVL_ACR   - Front overlay offset across       */
/*       CWBOBJ_KEY_FTOVL_DWN   - Front overlay offset down         */
/*    (1)CWBOBJ_KEY_CHAR_ID     - Graphic character set ID          */
/*       CWBOBJ_KEY_JUSTIFY     - Hardware Justification            */
/*       CWBOBJ_KEY_HOLD        - Hold spooled file                 */
/*       CWBOBJ_KEY_LPI         - Lines per inch                    */
/*       CWBOBJ_KEY_MAXRECORDS  - Maximum spooled file records      */
/*       CWBOBJ_KEY_OUTPTY      - Output priority                   */
/*       CWBOBJ_KEY_OUTQUELIB   - Output queue library name         */
/*       CWBOBJ_KEY_OUTQUE      - Output queue                      */
/*       CWBOBJ_KEY_OVERFLOW    - Overflow line number              */
/*       CWBOBJ_KEY_PAGELEN     - Page length                       */
/*       CWBOBJ_KEY_MEASMETHOD  - Measurement method                */
/*       CWBOBJ_KEY_PAGEWIDTH   - Page width                        */
/*       CWBOBJ_KEY_MULTIUP     - Logical number of pages per side  */
/*       CWBOBJ_KEY_POINTSIZE   - The default font's point size     */
/*       CWBOBJ_KEY_FIDELITY    - Print fidelity                    */
/*       CWBOBJ_KEY_DUPLEX      - Print on both sides               */
/*       CWBOBJ_KEY_PRTQUALITY  - Print quality                     */
/*       CWBOBJ_KEY_PRTTEXT     - Print text                        */
/*       CWBOBJ_KEY_PRINTER     - Printer device name               */
/*       CWBOBJ_KEY_PRTDEVTYPE  - Printer device type               */
/*       CWBOBJ_KEY_RPLUNPRT    - Replace unprintable characters    */
/*       CWBOBJ_KEY_RPLCHAR     - Replacement character             */
/*       CWBOBJ_KEY_SAVESPLF    - Save spooled file after printing  */
/*       CWBOBJ_KEY_SRCDRWR     - Source drawer                     */
/*       CWBOBJ_KEY_SPOOL       - Spool the data                    */
/*       CWBOBJ_KEY_SPOOLFILE   - Spool file name                   */
/*       CWBOBJ_KEY_SCHEDULE    - When spooled file available       */
/*       CWBOBJ_KEY_STARTPAGE   - Starting page                     */
/*       CWBOBJ_KEY_UNITOFMEAS  - Unit of measure                   */
/*       CWBOBJ_KEY_USERCMT     - User comment (100 chars)          */
/*       CWBOBJ_KEY_USERDATA    - User data    (10 chars)           */
/*       CWBOBJ_KEY_SPLSCS      - Spool SCS Data                    */
/*       CWBOBJ_KEY_USRDFNDTA   - User defined data                 */
/*    (3)CWBOBJ_KEY_USRDFNOPTS  - User defined options              */
/*       CWBOBJ_KEY_USRDFNOBJLIB- User defined object library       */
/*       CWBOBJ_KEY_USRDFNOBJ   - User defined object               */
/*       CWBOBJ_KEY_USRDFNOBJTYP- User defined object type          */
/*                                                                  */
/*  Note: (1) Code page and graphic character set are dependent on  */
/*            each other.  If you specify one of these, you must    */
/*            specify the other.                                    */
/*                                                                  */
/*        (2) The special value of *FILE is not allowed when using  */
/*            this attribute to create a new spooled file.          */
/*                                                                  */
/*        (3) Up to 4 user defined options may be specified.        */
/*                                                                  */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbOBJ_CreateNewSplF(
                              const char          *systemName,
                              cwbOBJ_ParmHandle   *parmListHandle,
                              cwbOBJ_ObjHandle    *printerFileHandle,
                              cwbOBJ_ObjHandle    *outputQueueHandle,
                              cwbOBJ_ObjHandle    *newSplFHandle,
                              cwbSV_ErrHandle      errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbOBJ_CreateNewSplFA(
                                LPCSTR               systemName
                              , cwbOBJ_ParmHandle   *parmListHandle
                              , cwbOBJ_ObjHandle    *printerFileHandle
                              , cwbOBJ_ObjHandle    *outputQueueHandle
                              , cwbOBJ_ObjHandle    *newSplFHandle
                              , cwbSV_ErrHandle      errorHandle
                                           );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbOBJ_CreateNewSplFW(
                                LPCWSTR              systemName
                              , cwbOBJ_ParmHandle   *parmListHandle
                              , cwbOBJ_ObjHandle    *printerFileHandle
                              , cwbOBJ_ObjHandle    *outputQueueHandle
                              , cwbOBJ_ObjHandle    *newSplFHandle
                              , cwbSV_ErrHandle      errorHandle
                                           );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbOBJ_CreateNewSplF            cwbOBJ_CreateNewSplFW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbOBJ_CreateNewSplF            cwbOBJ_CreateNewSplFA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_CreateParmObjHandle                                     */
/*                                                                  */
/* Purpose:                                                         */
/*   Allocate a parameter list object handle.                       */
/*   The parameter list object can be used to hold a list of        */
/*   parameters that can be passed in on other APIs.                */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ParmHandle  *parmListHandle - output                    */
/*     Handle of the parameter object.                              */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The cwbOBJ_DeleteParmObjHandle API must be called to free      */
/*   resources allocated by this call.                              */
/*                                                                  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_CreateParmObjHandle(
                               cwbOBJ_ParmHandle  *parmListHandle,
                               cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_CreateResourceHandle                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   Create a resource handle for a particular AFP resource on      */
/*   a specified system.                                            */
/*                                                                  */
/* Parameters:                                                      */
/*   const char *systemName - input                                 */
/*     Pointer to the system name contained in an ASCIIZ string.    */
/*                                                                  */
/*   const char *resourceName - input                               */
/*     Pointer to the name of the AFP resource.                     */
/*                                                                  */
/*   const char *resourceLibrary - input                            */
/*     Pointer to the name of the iSeries library that contains the */
/*     resource.                                                    */
/*                                                                  */
/*   cwbOBJ_AFPResourceType resourceType - input                    */
/*     Specifies what type of resource this is.  Must be one of     */
/*     the following:                                               */
/*                 CWBOBJ_AFPRSC_FONT                               */
/*                 CWBOBJ_AFPRSC_FORMDEF                            */
/*                 CWBOBJ_AFPRSC_OVERLAY                            */
/*                 CWBOBJ_AFPRSC_PAGESEG                            */
/*                 CWBOBJ_AFPRSC_PAGEDEF                            */
/*                                                                                                                                      */
/*   cwbOBJ_ObjHandle *objectHandle - output                        */
/*     On output this will contain the resource handle.             */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_INVALID_PARAMETER  - Invalid parameter specified.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use this API to get a handle to a resource if you know the name*/
/*   library and type of resource.                                                                      */
/*   If you don't know any of these or want to choose from a list   */
/*   use the list APIs to list AFP resources instead.                           */
/*                                                                                                                                      */
/*   This API does no checking of the AFP resource on the host.     */
/*   The first time this handle is used to retrieve data for the    */
/*   resource, a host error will be encountered if the resource     */
/*   file doesn't exist.                                            */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY  cwbOBJ_CreateResourceHandle(const char     *systemName,
                                                    const char     *resourceName,
                                                    const char     *resourceLibrary,
                                                                                                        cwbOBJ_AFPResourceType resourceType,
                                                    cwbOBJ_ObjHandle   *objectHandle,
                                                    cwbSV_ErrHandle     errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbOBJ_CreateResourceHandleA(
                                    LPCSTR                systemName
                                  , LPCSTR                resourceName
                                  , LPCSTR                resourceLibrary
                                  , cwbOBJ_AFPResourceType resourceType
                                  , cwbOBJ_ObjHandle     *objectHandle
                                  , cwbSV_ErrHandle       errorHandle
                                              );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbOBJ_CreateResourceHandleW(
                                    LPCWSTR               systemName
                                  , LPCWSTR               resourceName
                                  , LPCWSTR               resourceLibrary
                                  , cwbOBJ_AFPResourceType resourceType
                                  , cwbOBJ_ObjHandle     *objectHandle
                                  , cwbSV_ErrHandle       errorHandle
                                              );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbOBJ_CreateResourceHandle         cwbOBJ_CreateResourceHandleW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbOBJ_CreateResourceHandle         cwbOBJ_CreateResourceHandleA
#endif // of UNICODE/ANSI selection



/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_CreateSplFHandle                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Create a spooled file handle for a particular spooled file on  */
/*   a specified system.                                            */
/*                                                                  */
/* Parameters:                                                      */
/*   const char *systemName - input                                 */
/*     Pointer to the system name contained in an ASCIIZ string.    */
/*                                                                  */
/*   const char *jobName - input                                    */
/*     Pointer to the name of the iSeries job that created the      */
/*     spooled file in an ASCIIZ string.                            */
/*                                                                  */
/*   const char *jobNumber - input                                  */
/*     Pointer to the number of the iSeries job that created the    */
/*     spooled file in an ASCIIZ string.                            */
/*                                                                  */
/*   const char *jobUser - input                                    */
/*     Pointer to the user of the iSeries job that created the      */
/*     spooled file in an ASCIIZ string.                            */
/*                                                                  */
/*   const char *splFName - input                                   */
/*     Pointer to the name of the spooled file in an ASCIIZ string. */
/*                                                                  */
/*   const unsigned long splFNumber - input                         */
/*     The number of the spooled file.                              */
/*                                                                  */
/*   cwbOBJ_ObjHandle *objectHandle - output                        */
/*     On output this will contain the spooled file handle.         */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_INVALID_PARAMETER  - Invalid parameter specified.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API does no checking of the spooled file on the host.     */
/*   The first time this handle is used to retrieve data for the    */
/*   spooled file, a host error will be encountered if the spooled  */
/*   file doesn't exist.                                            */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY  cwbOBJ_CreateSplFHandle(const char         *systemName,
                                                const char         *jobName,
                                                const char         *jobNumber,
                                                const char         *jobUser,
                                                const char         *splFName,
                                                const unsigned long splFNumber,
                                                cwbOBJ_ObjHandle   *objectHandle,
                                                cwbSV_ErrHandle     errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbOBJ_CreateSplFHandleA(
                                    LPCSTR                systemName
                                  , LPCSTR                jobName
                                  , LPCSTR                jobNumber
                                  , LPCSTR                jobUser
                                  , LPCSTR                splFName
                                  , const ULONG           splFNumber
                                  , cwbOBJ_ObjHandle     *objectHandle
                                  , cwbSV_ErrHandle       errorHandle
                                              );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbOBJ_CreateSplFHandleW(
                                    LPCWSTR               systemName
                                  , LPCWSTR               jobName
                                  , LPCWSTR               jobNumber
                                  , LPCWSTR               jobUser
                                  , LPCWSTR               splFName
                                  , const ULONG           splFNumber
                                  , cwbOBJ_ObjHandle     *objectHandle
                                  , cwbSV_ErrHandle       errorHandle
                                              );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbOBJ_CreateSplFHandle         cwbOBJ_CreateSplFHandleW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbOBJ_CreateSplFHandle         cwbOBJ_CreateSplFHandleA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_CreateSplFHandleEx                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Create a spooled file handle for a particular spooled file on  */
/*   a specified system.                                            */
/*                                                                  */
/* Parameters:                                                      */
/*   const char *systemName - input                                 */
/*     Pointer to the system name contained in an ASCIIZ string.    */
/*                                                                  */
/*   const char *jobName - input                                    */
/*     Pointer to the name of the iSeris job that created the       */
/*     spooled file in an ASCIIZ string.                            */
/*                                                                  */
/*   const char *jobNumber - input                                  */
/*     Pointer to the number of the iSeries job that created the    */
/*     spooled file in an ASCIIZ string.                            */
/*                                                                  */
/*   const char *jobUser - input                                    */
/*     Pointer to the user of the iSeries job that created the      */
/*     spooled file in an ASCIIZ string.                            */
/*                                                                  */
/*   const char *splFName - input                                   */
/*     Pointer to the name of the spooled file in an ASCIIZ string. */
/*                                                                  */
/*   const unsigned long splFNumber - input                         */
/*     The number of the spooled file.                              */
/*                                                                  */
/*   const char *createdSystem - input                              */
/*     Pointer to the name of the system the spooled file was       */
/*     created on in an ASCIIZ string.                              */
/*                                                                  */
/*   const char *createdDate - input                                */
/*     Pointer to the date the spooled file was created in an       */
/*     ASCIIZ string                                                */
/*                                                                  */
/*   const char *createdTime - input                                */
/*     Pointer to the time the spooled file was created in an       */
/*     ASCIIZ string                                                */
/*                                                                  */
/*   cwbOBJ_ObjHandle *objectHandle - output                        */
/*     On output this will contain the spooled file handle.         */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_INVALID_PARAMETER  - Invalid parameter specified.          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This API does no checking of the spooled file on the host.     */
/*   The first time this handle is used to retrieve data for the    */
/*   spooled file, a host error will be encountered if the spooled  */
/*   file doesn't exist.                                            */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY  cwbOBJ_CreateSplFHandleEx(const char         *systemName,
                                                  const char         *jobName,
                                                  const char         *jobNumber,
                                                  const char         *jobUser,
                                                  const char         *splFName,
                                                  const unsigned long splFNumber,
                                                  const char         *createdSystem,
                                                  const char         *createdDate,
                                                  const char         *createdTime,
                                                  cwbOBJ_ObjHandle   *objectHandle,
                                                  cwbSV_ErrHandle     errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbOBJ_CreateSplFHandleExA(
                                    LPCSTR                systemName
                                  , LPCSTR                jobName
                                  , LPCSTR                jobNumber
                                  , LPCSTR                jobUser
                                  , LPCSTR                splFName
                                  , const ULONG           splFNumber
                                  , LPCSTR                createdSystem
                                  , LPCSTR                createdDate
                                  , LPCSTR                createdTime
                                  , cwbOBJ_ObjHandle     *objectHandle
                                  , cwbSV_ErrHandle       errorHandle
                                              );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbOBJ_CreateSplFHandleExW(
                                    LPCWSTR               systemName
                                  , LPCWSTR               jobName
                                  , LPCWSTR               jobNumber
                                  , LPCWSTR               jobUser
                                  , LPCWSTR               splFName
                                  , const ULONG           splFNumber
                                  , LPCWSTR               createdSystem
                                  , LPCWSTR               createdDate
                                  , LPCWSTR               createdTime
                                  , cwbOBJ_ObjHandle     *objectHandle
                                  , cwbSV_ErrHandle       errorHandle
                                              );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbOBJ_CreateSplFHandleEx         cwbOBJ_CreateSplFHandleExW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbOBJ_CreateSplFHandleEx         cwbOBJ_CreateSplFHandleExA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_DeleteListHandle                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Deallocates a list handle that was previously allocated with   */
/*   the cwbOBJ_CreateListHandle() API.                             */
/*   This will free any  resources associated with the list.        */
/*                                                                  */
/* Parameters:                                                      */
/*                                                                  */
/*   cwbOBJ_ListHandle listHandle - input                           */
/*     List handle that will be deleted.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_INVALID_HANDLE - List handle not found.                    */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/*   If the list associated with this handle is opened, this call   */
/*   will close it.                                                 */
/*   If there are opened handles to objects in this list, they will */
/*   no longer be valid.                                            */
/*   After this call returns successfully, the list handle is no    */
/*   longer valid.                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_DeleteListHandle(
                               cwbOBJ_ListHandle  listHandle,
                               cwbSV_ErrHandle    errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_DeleteObjHandle                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Releases a handle to an object.                                */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle objectHandle - input                          */
/*     Handle of the object to release.                             */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not an allocated object handle. */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_DeleteObjHandle(
                               cwbOBJ_ObjHandle   objectHandle,
                               cwbSV_ErrHandle    errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_DeleteParmObjHandle                                     */
/*                                                                  */
/* Purpose:                                                         */
/*   Deallocate a parameter list object handle and free the         */
/*   resources used by it.                                          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ParmHandle parmListHandle - input                       */
/*     Handle of the parameter object.                              */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not a parameter object handle.  */
/*                                                                  */
/* Usage Notes:                                                     */
/*   After this call returns successfully, the parmListHandle is    */
/*   no longer valid.                .                              */
/*                                                                  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_DeleteParmObjHandle(
                               cwbOBJ_ParmHandle  parmListHandle,
                               cwbSV_ErrHandle    errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_DeleteSplF                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Delete an iSeries spooled file.                                */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle splFHandle - input                            */
/*     Handle of the spooled file to be deleted.                    */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not valid.                      */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*   CWBOBJ_RC_INVALID_TYPE - Handle is not a spooled file handle   */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/*   After this calls returns successfully, cwbOBJ_DeleteObjHandle()*/
/*   should be called to release the splFHandle.                    */
/*                                                                  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_DeleteSplF(
                               cwbOBJ_ObjHandle   splFHandle,
                               cwbSV_ErrHandle    errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_DisplayResource                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Displays the specified AFP resource to the user.               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle resourceHandle - input                        */
/*     Handle of the AFP Resource object.                           */
/*     It must be an overlay or a pagesegment type of resource.         */
/*                                                                  */
/*   const char *view - input                                       */
/*     Optional, may be NULL.                                       */
/*     If specified it is a pointer to an ASCIIZ string that        */
/*     specifies the view to use when invoking the AFP viewer.      */
/*     The are two predefined views shipped with the viewer:        */
/*       LETTER  (8.5" x 11")                                       */
/*       SFLVIEW (132 column)                                       */
/*     Users may also add their own.                                */
/*                                                                  */
/*   const unsigned long flags - input                              */
/*     Any of following bits may be set:                            */
/*       CWBOBJ_DSPSPLF_WAIT - instructs this call to wait until    */
/*         the viewer process has successfully opened the resource  */
/*         before returning.  If this bit is 0, this API will       */
/*         return after it starts the viewer process.  If it is 1,  */
/*         this API will wait for the viewer to get the resource    */
/*         open before returning.                                   */
/*     All other bits must be set to 0.                             */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_INVALID_HANDLE - Handle is not an allocated object handle. */
/*   CWB_NO_VIEWER - The viewer support for ClientAccess/400 was    */
/*                         not installed.                           */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*   CWBOBJ_RC_INVALID_TYPE - The handle given for resourceHandle is*/
/*     not a handle to an overlay or pagesegment resource.          */
/*                                                                  */
/* Usage Notes:                                                     */
/*    Use this API to bring up the AFP viewer on the specified      */
/*    AFP resource.  The type of the resource must be an overlay or */
/*    a pagesegment.                                                                                            */
/*    A return code of CWB_NO_VIEWER means that the viewer          */
/*    component was not installed on the workstation.               */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY  cwbOBJ_DisplayResource(cwbOBJ_ObjHandle    resourceHandle,
                                               const char         *view,
                                               const unsigned long flags,
                                               cwbSV_ErrHandle     errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbOBJ_DisplayResourceA(
                                      cwbOBJ_ObjHandle    resourceHandle
                                    , LPCSTR              view
                                    , const ULONG         flags
                                    , cwbSV_ErrHandle     errorHandle
                                         );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbOBJ_DisplayResourceW(
                                      cwbOBJ_ObjHandle    resourceHandle
                                    , LPCWSTR             view
                                    , const ULONG         flags
                                    , cwbSV_ErrHandle     errorHandle
                                         );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbOBJ_DisplayResource              cwbOBJ_DisplayResourceW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbOBJ_DisplayResource              cwbOBJ_DisplayResourceA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_DisplaySplF                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Displays the specified spooled file to the user.               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle splFHandle - input                            */
/*     Handle of the spooled file object.                           */
/*                                                                  */
/*   const char *view - input                                       */
/*     Optional, may be NULL.                                       */
/*     If specified it is a pointer to an ASCIIZ string that        */
/*     specifies the view to use when invoking the spooled file     */
/*     viewer.                                                      */
/*     The are two predefined views shipped with the viewer:        */
/*       LETTER  (8.5" x 11")                                       */
/*       SFLVIEW (132 column)                                       */
/*     Users may also add their own.                                */
/*                                                                  */
/*   const unsigned long flags - input                              */
/*     Any of following bits may be set:                            */
/*       CWBOBJ_DSPSPLF_WAIT - instructs this call to wait until    */
/*         the viewer process has successfully opened the spooled   */
/*         file before returning.  If this bit is 0, this API will  */
/*         return after it starts the viewer process.  If it is 1,  */
/*         this API will wait for the viewer to get the spooled file*/
/*         open before returning.                                   */
/*     All other bits must be set to 0.                             */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_INVALID_HANDLE - Handle is not an allocated object handle. */
/*   CWB_NO_VIEWER - The viewer support for ClientAccess/400 was    */
/*                         not installed.                           */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*    Use this API to bring up the AFP viewer on the specified      */
/*    spooled file.                                                 */
/*    The AFP viewer can view AFP data, SCS data and plain ASCII    */
/*    text data.                                                    */
/*    A return code of CWB_NO_VIEWER means that the viewer          */
/*    component was not installed on the workstation.               */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY  cwbOBJ_DisplaySplF(cwbOBJ_ObjHandle    splFHandle,
                                           const char         *view,
                                           const unsigned long flags,
                                           cwbSV_ErrHandle     errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbOBJ_DisplaySplFA(
                                      cwbOBJ_ObjHandle    splFHandle
                                    , LPCSTR              view
                                    , const ULONG         flags
                                    , cwbSV_ErrHandle     errorHandle
                                         );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbOBJ_DisplaySplFW(
                                      cwbOBJ_ObjHandle    splFHandle
                                    , LPCWSTR             view
                                    , const ULONG         flags
                                    , cwbSV_ErrHandle     errorHandle
                                         );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbOBJ_DisplaySplF              cwbOBJ_DisplaySplFW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbOBJ_DisplaySplF              cwbOBJ_DisplaySplFA
#endif // of UNICODE/ANSI selection

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_DropConnections                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Drops all unused converations to all systems for the network   */
/*   print server for this process.                                 */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The CWBOBJ.DLL maintains a pool of available conversations  to */
/*   the network print server for use on the APIs.  These           */
/*   converations normally timeout after not having been used for   */
/*   10 to 20 minutes and are then dropped.                         */
/*   This API allows the application to clean up the pool of        */
/*   converations immediately without waiting for the timeout.  It  */
/*   can also be used at the end of the process to make sure that   */
/*   any converations are terminated.                               */
/*   This API will drop all connections to all servers for this     */
/*   process that are not "in use".  In use connections include     */
/*   those with open spooled files on them (for creating or reading */
/*   from).                                                         */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_DropConnections(
                               cwbSV_ErrHandle    errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_EndWriter                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   Ends an iSeries writer job.                                    */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle writerHandle - input                          */
/*     Handle of the writer job to be stopped.                      */
/*     This handle can be obtained by either listing writers and    */
/*     getting the writer handle from that list or from starting    */
/*     a writer and asking for the writer handle to be returned.    */
/*                                                                  */
/*   cwbOBJ_ParmHandle *parmListHandle - input                      */
/*     Optional.  A pointer to a valid parameter list object handle */
/*     that contains parameters for ending the writer.              */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not valid.                      */
/*   CWB_INVALID_PARAMETER - Invalid parameter specified.           */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*                                                                  */
/* Usage Notes:                                                     */
/*   After this calls returns successfully, cwbOBJ_DeleteObjHandle()*/
/*   should be called to release the writerHandle.                  */
/*                                                                  */
/*   The following parameter key's may be set in the pParmListHandle*/
/*   object:                                                        */
/*    CWBOBJ_KEY_WTREND      - When to end the writer.  May be any  */
/*                             these special values:                */
/*                             *CNTRLD - end the writer after the   */
/*                               current file is done printing.     */
/*                             *IMMED  - end the writer immediately */
/*                             *PAGEEND - end the writer at the end */
/*                               of the current page.               */
/*                                                                  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_EndWriter(
                               cwbOBJ_ObjHandle   writerHandle,
                               cwbOBJ_ParmHandle *parmListHandle,
                               cwbSV_ErrHandle    errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_GetListSize                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the size of an opened list.                                */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ListHandle listHandle - input                           */
/*     Handle of the list to get the size of.  This list must be    */
/*     opened.                                                      */
/*                                                                  */
/*   unsigned long *size - output                                   */
/*     On output, this will be set to the current size of the list. */
/*                                                                  */
/*   cwbOBJ_List_Status *listStatus - output                        */
/*     Optional, may be NULL.  This will always be                  */
/*     CWBOBJ_LISTSTS_COMPLETED for lists opened synchronously.     */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.                                                         */
/*     If the parameter is set to zero, no messages will be         */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not an allocated list handle.   */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*   CWBOBJ_RC_LIST_NOT_OPEN - The list isn't open.                 */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_GetListSize(
                               cwbOBJ_ListHandle   listHandle,
                               unsigned long      *size,
                               cwbOBJ_List_Status *listStatus,
                               cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_GetNPServerAttr                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Get an attribute of the QNPSERVR program on a specified system */
/*                                                                  */
/* Parameters:                                                      */
/*   const char *systemName - input                                 */
/*     Pointer to the system name contained in an ASCIIZ string.    */
/*                                                                  */
/*   cwbOBJ_KeyID key - input                                       */
/*     Identifying key of the attribute to retrieve.                */
/*                                                                  */
/*   void *buffer - output                                          */
/*     The buffer that will hold the attribute value. If this call  */
/*     returns successfully.  The value of the key determines what  */
/*     type of data will be put into pBuffer.   The type is also    */
/*     returned to the *keyType parameter, if provided.             */
/*                                                                  */
/*   unsigned long bufLen - input                                   */
/*     The length of the buffer pointed to by pBuffer.              */
/*                                                                  */
/*   unsigned long *bytesNeeded - output                            */
/*     On output, this will be the number of bytes needed to hold   */
/*     result.                                                      */
/*                                                                  */
/*   cwbOBJ_DataType *keyType - output                              */
/*     Optional, may be NULL.  On output this will contain the type */
/*     of data used to represent this attribute and what is stored  */
/*     at *buffer.                                                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_BUFFER_OVERFLOW - Buffer too small.                        */
/*   CWB_INVALID_PARAMETER - Invalid parameter specified.           */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*   CWBOBJ_RC_INVALID_KEY - Key isn't valid.                       */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*  The following attributes may be retrieved from the QNPSERVR     */
/*   program:                                                       */
/*                                                                  */
/*     CWBOBJ_KEY_NPSCCSID    - Server CCSID                        */
/*     CWBOBJ_KEY_NPSLEVEL    - Server code level                   */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbOBJ_GetNPServerAttr(
                              const char          *systemName,
                              cwbOBJ_KeyID         key,
                              void                *buffer,
                              unsigned long        bufLen,
                              unsigned long       *bytesNeeded,
                              cwbOBJ_DataType     *keyType,
                              cwbSV_ErrHandle      errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbOBJ_GetNPServerAttrA(
                                   LPCSTR               systemName
                                 , cwbOBJ_KeyID         key
                                 , void                *buffer
                                 , ULONG                bufLen
                                 , ULONG               *bytesNeeded
                                 , cwbOBJ_DataType     *keyType
                                 , cwbSV_ErrHandle      errorHandle
                                             );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbOBJ_GetNPServerAttrW(
                                   LPCWSTR              systemName
                                 , cwbOBJ_KeyID         key
                                 , void                *buffer
                                 , ULONG                bufLen
                                 , ULONG               *bytesNeeded
                                 , cwbOBJ_DataType     *keyType
                                 , cwbSV_ErrHandle      errorHandle
                                             );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbOBJ_GetNPServerAttr          cwbOBJ_GetNPServerAttrW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbOBJ_GetNPServerAttr          cwbOBJ_GetNPServerAttrA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_GetObjAttr                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Get an attribute of an object.                                 */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle objectHandle - input                          */
/*     Handle of the object to get the attribute for.               */
/*                                                                  */
/*   cwbOBJ_KeyID key - input                                       */
/*     Identifying key of the attribute to retrieve.                */
/*     The CWBOBJ_KEY_XXX constants define the key ids.             */
/*     The type of object pointed to by objectHandle determine which*/
/*     keys are valid.                                              */
/*                                                                  */
/*   void *buffer - output                                          */
/*     The buffer that will hold the attribute value, if this call  */
/*     returns successfully.  The value of the key determines what  */
/*     type of data will be put into pBuffer.   The type is also    */
/*     returned to the *keyType parameter, if provided.             */
/*                                                                  */
/*   unsigned long bufLen - input                                   */
/*     The length of the buffer pointed to by pBuffer.              */
/*                                                                  */
/*   unsigned long *bytesNeeded - output                            */
/*     On output, this will be the number of bytes needed to hold   */
/*     result.                                                      */
/*                                                                  */
/*   cwbOBJ_DataType *keyType - output                              */
/*     Optional, may be NULL.  On output this will contain the type */
/*     of data used to represent this attribute and what is stored  */
/*     at *buffer.                                                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_INVALID_HANDLE - Handle is not an allocated object handle. */
/*   CWB_BUFFER_OVERFLOW - Buffer too small.                        */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*   CWBOBJ_RC_INVALID_KEY - Key isn't valid.                       */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*  The following attributes may be retrieved for these object      */
/*  types:                                                          */
/*                                                                  */
/*  CWBOBJ_LIST_SPLF:                                               */
/*     CWBOBJ_KEY_AFP         - AFP resources used                  */
/*     CWBOBJ_KEY_ALIGN       - Align page                          */
/*     CWBOBJ_KEY_BKMGN_ACR   - Back margin across                  */
/*     CWBOBJ_KEY_BKMGN_DWN   - Back margin down                    */
/*     CWBOBJ_KEY_BKOVRLLIB   - Back overlay library name           */
/*     CWBOBJ_KEY_BKOVRLAY    - Back overlay name                   */
/*     CWBOBJ_KEY_BKOVL_ACR   - Back overlay offset across          */
/*     CWBOBJ_KEY_BKOVL_DWN   - Back overlay offset down            */
/*     CWBOBJ_KEY_CPI         - Characters per inch                 */
/*     CWBOBJ_KEY_CODEDFNTLIB - Coded font library name             */
/*     CWBOBJ_KEY_CODEDFNT    - Coded font                          */
/*     CWBOBJ_KEY_COPIES      - Copies (total)                      */
/*     CWBOBJ_KEY_COPIESLEFT  - Copies left to produce              */
/*     CWBOBJ_KEY_CURPAGE     - Current page                        */
/*     CWBOBJ_KEY_DATE        - Date file was opened                */
/*     CWBOBJ_KEY_PAGRTT      - Degree of page rotation             */
/*     CWBOBJ_KEY_ENDPAGE     - Ending page                         */
/*     CWBOBJ_KEY_FILESEP     - File separators                     */
/*     CWBOBJ_KEY_FOLDREC     - Wrap text to next line              */
/*     CWBOBJ_KEY_FONTID      - Font identifier to use (default)    */
/*     CWBOBJ_KEY_FORMFEED    - Form feed                           */
/*     CWBOBJ_KEY_FORMTYPE    - Form type                           */
/*     CWBOBJ_KEY_FTMGN_ACR   - Front margin across                 */
/*     CWBOBJ_KEY_FTMGN_DWN   - Front margin down                   */
/*     CWBOBJ_KEY_FTOVRLLIB   - Front overlay library name          */
/*     CWBOBJ_KEY_FTOVRLAY    - Front overlay                       */
/*     CWBOBJ_KEY_FTOVL_ACR   - Front overlay offset across         */
/*     CWBOBJ_KEY_FTOVL_DWN   - Front overlay offset down           */
/*     CWBOBJ_KEY_CHAR_ID     - Graphic character set               */
/*     CWBOBJ_KEY_JUSTIFY     - Hardware justification              */
/*     CWBOBJ_KEY_HOLD        - Hold the spool file                 */
/*     CWBOBJ_KEY_JOBNAME     - Name of the job that created file   */
/*     CWBOBJ_KEY_JOBNUMBER   - Number of the job that created file */
/*     CWBOBJ_KEY_USER        - Name of the user that created file  */
/*     CWBOBJ_KEY_LASTPAGE    - Last page that printed              */
/*     CWBOBJ_KEY_LPI         - Lines per inch                      */
/*     CWBOBJ_KEY_MAXRECORDS  - Maximum number of records allowed   */
/*     CWBOBJ_KEY_OUTPTY      - Output priority                     */
/*     CWBOBJ_KEY_OUTQUELIB   - Output queue library name           */
/*     CWBOBJ_KEY_OUTQUE      - Output queue                        */
/*     CWBOBJ_KEY_OVERFLOW    - Overflow line number                */
/*     CWBOBJ_KEY_PAGELEN     - Page length                         */
/*     CWBOBJ_KEY_MEASMETHOD  - Measurement method                  */
/*     CWBOBJ_KEY_PAGEWIDTH   - Page width                          */
/*     CWBOBJ_KEY_MULTIUP     - Logical pages per physical side     */
/*     CWBOBJ_KEY_POINTSIZE   - The default font's point size       */
/*     CWBOBJ_KEY_FIDELITY    - The error handling when printing    */
/*     CWBOBJ_KEY_DUPLEX      - Print on both sides of paper        */
/*     CWBOBJ_KEY_PRTQUALITY  - Print quality                       */
/*     CWBOBJ_KEY_PRTTEXT     - Text printed at bottom of each page */
/*     CWBOBJ_KEY_PRTDEVTYPE  - Printer dev type (data stream type) */
/*     CWBOBJ_KEY_PRTRFILELIB - Printer file library                */
/*     CWBOBJ_KEY_PRTRFILE    - Printer file                        */
/*     CWBOBJ_KEY_RECLENGTH   - Record length                       */
/*     CWBOBJ_KEY_RPLUNPRT    - Replace unprintable characters      */
/*     CWBOBJ_KEY_RPLCHAR     - Character to replace unprintables   */
/*     CWBOBJ_KEY_RESTART     - Where to restart printing at        */
/*     CWBOBJ_KEY_SAVESPLF    - Save file after printing            */
/*     CWBOBJ_KEY_SRCDRWR     - Source drawer                       */
/*     CWBOBJ_KEY_SPOOLFILE   - Spool file name                     */
/*     CWBOBJ_KEY_SPLFNUM     - Spool file number                   */
/*     CWBOBJ_KEY_SPLFSTATUS  - Spool file status                   */
/*     CWBOBJ_KEY_STARTPAGE   - Starting page to print              */
/*     CWBOBJ_KEY_TIME        - Time spooled file was opened at     */
/*     CWBOBJ_KEY_PAGES       - Number of pages in spool file       */
/*     CWBOBJ_KEY_UNITOFMEAS  - Unit of measure                     */
/*     CWBOBJ_KEY_USERCMT     - User comment                        */
/*     CWBOBJ_KEY_USERDATA    - User data                           */
/*     CWBOBJ_KEY_USRDFNDTA   - User defined data                   */
/*     CWBOBJ_KEY_USRDFNOPTS  - User defined options                */
/*     CWBOBJ_KEY_USRDFNOBJLIB- User defined object library         */
/*     CWBOBJ_KEY_USRDFNOBJ   - User defined object                 */
/*     CWBOBJ_KEY_USRDFNOBJTYP- User defined object type            */
/*                                                                  */
/*  CWBOBJ_LIST_OUTQ:                                               */
/*     CWBOBJ_KEY_AUTHCHCK    - authority to check                  */
/*     CWBOBJ_KEY_DATAQUELIB  - data queue libarary                 */
/*     CWBOBJ_KEY_DATAQUE     - data queue                          */
/*     CWBOBJ_KEY_DISPLAYANY  - users can display any file on queue */
/*     CWBOBJ_KEY_JOBSEPRATR  - number of job separators            */
/*     CWBOBJ_KEY_NUMFILES    - total spooled files on output queue */
/*     CWBOBJ_KEY_NUMWRITERS  - number of writers started to queue  */
/*     CWBOBJ_KEY_OPCNTRL     - operator controlled                 */
/*     CWBOBJ_KEY_ORDER       - order on queue (sequence)           */
/*     CWBOBJ_KEY_OUTQUELIB   - output queue library name           */
/*     CWBOBJ_KEY_OUTQUE      - output queue                        */
/*     CWBOBJ_KEY_OUTQUESTS   - output queue status                 */
/*     CWBOBJ_KEY_PRINTER     - printer                             */
/*     CWBOBJ_KEY_DESCRIPTION - text description                    */
/*     CWBOBJ_KEY_WRITER      - writer job name                     */
/*     CWBOBJ_KEY_WTRJOBNUM   - writer job number                   */
/*     CWBOBJ_KEY_WTRJOBSTS   - writer job status                   */
/*     CWBOBJ_KEY_WTRJOBUSER  - writer job user                     */
/*     CWBOBJ_KEY_SEPPAGE     - print banner page or not                */
/*     CWBOBJ_KEY_USRDFNDTA   - user defined data                       */
/*     CWBOBJ_KEY_USRDFNOPTS  - user defined options                    */
/*     CWBOBJ_KEY_USRDFNOBJLIB- user defined object library             */
/*     CWBOBJ_KEY_USRDFNOBJ   - user defined object                     */
/*     CWBOBJ_KEY_USRDFNOBJTYP- user defined object type                */
/*     CWBOBJ_KEY_USRTFMPGMLIB- user data transform program library     */
/*     CWBOBJ_KEY_USRTFMPGM   - user data transform program             */
/*     CWBOBJ_KEY_USRDRVPGMDTA- user driver program data                */
/*     CWBOBJ_KEY_USRDRVPGMLIB- user driver program library             */
/*     CWBOBJ_KEY_USRDRVPGM   - user driver program                     */
/*                                                                  */
/*  CWBOBJ_LIST_PRTD:                                               */
/*     CWBOBJ_KEY_AFP         - AFP resources used                  */
/*     CWBOBJ_KEY_CODEPAGE    - code page                           */
/*     CWBOBJ_KEY_DEVCLASS    - device class                        */
/*     CWBOBJ_KEY_DEVMODEL    - device model                        */
/*     CWBOBJ_KEY_DEVTYPE     - device type                         */
/*     CWBOBJ_KEY_DRWRSEP     - drawer to use for separators        */
/*     CWBOBJ_KEY_FONTID      - font identifier                     */
/*     CWBOBJ_KEY_FORMFEED    - form feed                           */
/*     CWBOBJ_KEY_CHAR_ID     - graphic character set               */
/*     CWBOBJ_KEY_MFGTYPE     - manufacturer's type & model         */
/*     CWBOBJ_KEY_MSGQUELIB   - message queue library               */
/*     CWBOBJ_KEY_MSGQUE      - message queue                       */
/*     CWBOBJ_KEY_POINTSIZE   - default font's point size           */
/*     CWBOBJ_KEY_PRINTER     - printer                             */
/*     CWBOBJ_KEY_PRTQUALITY  - print quality                       */
/*     CWBOBJ_KEY_DESCRIPTION - text description                    */
/*     CWBOBJ_KEY_SCS2ASCII   - transform SCS to ASCII              */
/*     CWBOBJ_KEY_USRDFNDTA   - user defined data                   */
/*     CWBOBJ_KEY_USRDFNOPTS  - user defined options                */
/*     CWBOBJ_KEY_USRDFNOBJLIB- user defined object library         */
/*     CWBOBJ_KEY_USRDFNOBJ   - user defined object                 */
/*     CWBOBJ_KEY_USRDFNOBJTYP- user defined object type            */
/*     CWBOBJ_KEY_USRTFMPGMLIB- user data transform program library */
/*     CWBOBJ_KEY_USRTFMPGM   - user data transform program         */
/*     CWBOBJ_KEY_USRDRVPGMDTA- user driver program data            */
/*     CWBOBJ_KEY_USRDRVPGMLIB- user driver program library         */
/*     CWBOBJ_KEY_USRDRVPGM   - user driver program                 */
/*                                                                  */
/*                                                                  */
/*  CWBOBJ_LIST_PRTF:                                               */
/*     CWBOBJ_KEY_ALIGN       - align page                          */
/*     CWBOBJ_KEY_BKMGN_ACR   - back margin across                  */
/*     CWBOBJ_KEY_BKMGN_DWN   - back margin down                    */
/*     CWBOBJ_KEY_BKOVRLLIB   - back side overlay library           */
/*     CWBOBJ_KEY_BKOVRLAY    - back side overlay name              */
/*     CWBOBJ_KEY_BKOVL_DWN   - back overlay offset down            */
/*     CWBOBJ_KEY_BKOVL_ACR   - back overlay offset across          */
/*     CWBOBJ_KEY_CPI         - characters per inch                 */
/*     CWBOBJ_KEY_CODEDFNTLIB - coded font library name             */
/*     CWBOBJ_KEY_CODEPAGE    - code page                           */
/*     CWBOBJ_KEY_CODEDFNT    - coded font                          */
/*     CWBOBJ_KEY_COPIES      - copies (total)                      */
/*     CWBOBJ_KEY_DBCSDATA    - contains DBCS character set data    */
/*     CWBOBJ_KEY_DBCSEXTENSN - process DBCS extension characters   */
/*     CWBOBJ_KEY_DBCSROTATE  - rotate DBCS characters              */
/*     CWBOBJ_KEY_DBCSCPI     - DBCS CPI                            */
/*     CWBOBJ_KEY_DBCSSISO    - DBCS SI/SO positioning              */
/*     CWBOBJ_KEY_DFR_WRITE   - defer write                         */
/*     CWBOBJ_KEY_PAGRTT      - degree of page rotation             */
/*     CWBOBJ_KEY_ENDPAGE     - ending page number to print         */
/*     CWBOBJ_KEY_FILESEP     - number of file separators           */
/*     CWBOBJ_KEY_FOLDREC     - wrap text to next line              */
/*     CWBOBJ_KEY_FONTID      - Font identifier to use (default)    */
/*     CWBOBJ_KEY_FORMFEED    - type of paperfeed to be used        */
/*     CWBOBJ_KEY_FORMTYPE    - name of the form to be used         */
/*     CWBOBJ_KEY_FTMGN_ACR   - front margin across                 */
/*     CWBOBJ_KEY_FTMGN_DWN   - front margin down                   */
/*     CWBOBJ_KEY_FTOVRLLIB   - front side overlay library          */
/*     CWBOBJ_KEY_FTOVRLAY    - front side overlay name             */
/*     CWBOBJ_KEY_FTOVL_ACR   - front overlay offset across         */
/*     CWBOBJ_KEY_FTOVL_DWN   - front overlay offset down           */
/*     CWBOBJ_KEY_CHAR_ID     - graphic character set for this file */
/*     CWBOBJ_KEY_JUSTIFY     - hardware justification              */
/*     CWBOBJ_KEY_HOLD        - hold the spool file                 */
/*     CWBOBJ_KEY_LPI         - lines per inch                      */
/*     CWBOBJ_KEY_MAXRCDS     - maximum number of records allowed   */
/*     CWBOBJ_KEY_OUTPTY      - output priority                     */
/*     CWBOBJ_KEY_OUTQUELIB   - output queue library                */
/*     CWBOBJ_KEY_OUTQUE      - output queue                        */
/*     CWBOBJ_KEY_OVERFLOW    - overflow line number                */
/*     CWBOBJ_KEY_LINES_PAGE  - page length in lines per page       */
/*     CWBOBJ_KEY_PAGELEN     - page length in Units of Measurement */
/*     CWBOBJ_KEY_MEASMETHOD  - measurement method (*ROWCOL or *UOM)*/
/*     CWBOBJ_KEY_CHAR_LINE   - page width in characters per line   */
/*     CWBOBJ_KEY_PAGEWIDTH   - width of page in Units of Measure   */
/*     CWBOBJ_KEY_MULTIUP     - logical pages per physical side     */
/*     CWBOBJ_KEY_POINTSIZE   - the default font's point size       */
/*     CWBOBJ_KEY_FIDELITY    - the error handling when printing    */
/*     CWBOBJ_KEY_DUPLEX      - print on both sides of paper        */
/*     CWBOBJ_KEY_PRTQUALITY  - print quality                       */
/*     CWBOBJ_KEY_PRTTEXT     - text printed at bottom of each page */
/*     CWBOBJ_KEY_PRINTER     - printer device name                 */
/*     CWBOBJ_KEY_PRTDEVTYPE  - printer dev type (data stream type  */
/*     CWBOBJ_KEY_PRTRFILELIB - printer file library                */
/*     CWBOBJ_KEY_PRTRFILE    - printer file                        */
/*     CWBOBJ_KEY_RPLUNPRT    - replace unprintable characters      */
/*     CWBOBJ_KEY_RPLCHAR     - character to replace unprintables   */
/*     CWBOBJ_KEY_SAVE        - save spooled file after printing    */
/*     CWBOBJ_KEY_SRCDRWR     - source drawer                       */
/*     CWBOBJ_KEY_SPOOL       - spool the data                      */
/*     CWBOBJ_KEY_SCHEDULE    - when available to the writer        */
/*     CWBOBJ_KEY_STARTPAGE   - starting page to print              */
/*     CWBOBJ_KEY_DESCRIPTION - text description                    */
/*     CWBOBJ_KEY_UNITOFMEAS  - unit of measure                     */
/*     CWBOBJ_KEY_USERDATA    - user data                           */
/*     CWBOBJ_KEY_USRDFNDTA   - User defined data                   */
/*     CWBOBJ_KEY_USRDFNOPTS  - User defined options                */
/*     CWBOBJ_KEY_USRDFNOBJLIB- User defined object library         */
/*     CWBOBJ_KEY_USRDFNOBJ   - User defined object                 */
/*     CWBOBJ_KEY_USRDFNOBJTYP- User defined object type            */
/*                                                                  */
/*  CWBOBJ_LIST_WTR:                                                */
/*     CWBOBJ_KEY_WRITER      - writer job name                     */
/*     CWBOBJ_KEY_WTRJOBNUM   - writer job number                   */
/*     CWBOBJ_KEY_WTRJOBSTS   - writer job status                   */
/*     CWBOBJ_KEY_WTRJOBUSER  - writer job user                     */
/*                                                                  */
/*  CWBOBJ_LIST_LIB:                                                */
/*    CWBOBJ_KEY_LIBRARY      - the library name                    */
/*    CWBOBJ_KEY_DESCRIPTION  - the description of the library      */
/*                                                                  */
/*  CWBOBJ_LIST_RSC:                                                */
/*    CWBOBJ_KEY_RSCNAME      - resource name                       */
/*    CWBOBJ_KEY_RSCLIB       - resource library                    */
/*    CWBOBJ_KEY_RSCTYPE      - resource object type                */
/*    CWBOBJ_KEY_OBJEXTATTR   - object extended attribute           */
/*    CWBOBJ_KEY_DESCRIPTION  - the description of the resource     */
/*    CWBOBJ_KEY_DATE         - date object was last modified       */
/*    CWBOBJ_KEY_TIME         - time object was last modified       */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbOBJ_GetObjAttr(
                              cwbOBJ_ObjHandle     objectHandle,
                              cwbOBJ_KeyID         key,
                              void                *buffer,
                              unsigned long        bufLen,
                              unsigned long       *bytesNeeded,
                              cwbOBJ_DataType     *keyType,
                              cwbSV_ErrHandle      errorHandle);
#endif   // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbOBJ_GetObjAttrA(
                                   cwbOBJ_ObjHandle     objectHandle
                                 , cwbOBJ_KeyID         key
                                 , void                *buffer
                                 , ULONG                bufLen
                                 , ULONG               *bytesNeeded
                                 , cwbOBJ_DataType     *keyType
                                 , cwbSV_ErrHandle      errorHandle
                                        );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbOBJ_GetObjAttrW(
                                   cwbOBJ_ObjHandle     objectHandle
                                 , cwbOBJ_KeyID         key
                                 , void                *buffer
                                 , ULONG                bufLen
                                 , ULONG               *bytesNeeded
                                 , cwbOBJ_DataType     *keyType
                                 , cwbSV_ErrHandle      errorHandle
                                        );
#endif    // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbOBJ_GetObjAttr               cwbOBJ_GetObjAttrW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbOBJ_GetObjAttr               cwbOBJ_GetObjAttrA
#endif // of UNICODE/ANSI selection



/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_GetObjAttrs                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Get serveral attributes of an object.                          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle objectHandle - input                          */
/*     Handle of the object to get the attribute for.               */
/*                                                                  */
/*   unsigned long  numAttrs - input                                */
/*     number of attributes to retrieve                             */
/*                                                                  */
/*   cwbOBJ_GetObjAttrParms *getAttrParms - input                   */
/*     an array of numAttrs elements that for each attribute to     */
/*     retrieve gives the attribute key (id), the buffer where to   */
/*     store the value for that attribute and the size of the buffer*/
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_INVALID_HANDLE - Handle is not an allocated object handle. */
/*   CWB_BUFFER_OVERFLOW - Buffer too small.                        */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*   CWBOBJ_RC_INVALID_KEY - Key isn't valid.                       */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*  See the Usage Notes in cwbOBJ_GetObjAttr to see which attributes*/
/*  are valid for the various types of objects.                     */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbOBJ_GetObjAttrs(
                              cwbOBJ_ObjHandle        objectHandle,
                              unsigned long           numAttrs,
                              cwbOBJ_GetObjAttrParms *getAttrParms,
                              cwbSV_ErrHandle         errorHandle);
#endif   // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbOBJ_GetObjAttrsA(
                                   cwbOBJ_ObjHandle        objectHandle
                                 , ULONG                   numAttrs
                                 , cwbOBJ_GetObjAttrParms *getAttrParms
                                 , cwbSV_ErrHandle         errorHandle
                                         );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbOBJ_GetObjAttrsW(
                                   cwbOBJ_ObjHandle        objectHandle
                                 , ULONG                   numAttrs
                                 , cwbOBJ_GetObjAttrParms *getAttrParms
                                 , cwbSV_ErrHandle         errorHandle
                                         );
#endif    // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbOBJ_GetObjAttrs              cwbOBJ_GetObjAttrsW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbOBJ_GetObjAttrs              cwbOBJ_GetObjAttrsA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_GetObjHandle                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Get list object.  This call gets a handle to an object in an   */
/*   opened list.  The handle returned must be released with the    */
/*   the cwbOBJ_DeleteObjHandle when the caller is done with it to  */
/*   release resources.                                             */
/*   The handle returned is only valid while the list is opened.    */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ListHandle listHandle - input                           */
/*     Handle of the list to get the object handle from.  This list */
/*     must be opened.                                              */
/*                                                                  */
/*   unsigned long position - input                                 */
/*     The position within the list of the object to get a handle   */
/*     for.  It is 0 based.  Valid values are 0 to the number of    */
/*     objects in the list - 1.                                     */
/*     You can use cwbOBJ_GetListSize() to get the size of the list.*/
/*                                                                  */
/*   cwbOBJ_ObjHandle *objectHandle - output                        */
/*     On return, this will contain the handle of the object.       */
/*                                                                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not an allocated list handle.   */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*   CWBOBJ_RC_LIST_NOT_OPEN - The list isn't open.                 */
/*   CWBOBJ_RC_INVALID_INDEX - The ulPosition is out of range.      */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_GetObjHandle(
                               cwbOBJ_ListHandle   listHandle,
                               unsigned long       position,
                               cwbOBJ_ObjHandle   *objectHandle,
                               cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_GetObjHandleFromID                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Regenerate an object handle from it's binary ID and type.      */
/*   cwbOBJ_DeleteObjHandle() must be called to free resources when */
/*   you are done using the object handle.                          */
/*                                                                  */
/* Parameters:                                                      */
/*   void *idBuffer - input                                         */
/*     The buffer that holds the id of this object.                 */
/*                                                                  */
/*   unsigned long bufLen - input                                   */
/*     The length of the data pointed to by pIDBuffer.              */
/*                                                                  */
/*   cwbOBJ_ObjType type - input                                    */
/*     Type of object this ID is for.  This must match the type     */
/*       of object the ID was taken from.                           */
/*                                                                  */
/*   cwbOBJ_ObjHandle *objectHandle - output                        */
/*     If this call returns successfully, this will be the handle   */
/*     to the object.  This handle should be released with the      */
/*     cwbOBJ_DeleteObjHandle() API when done using it.             */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not an allocated object handle. */
/*   CWB_INVALID_PARAMETER - Invalid parameter specified.           */
/*   CWBOBJ_RC_INVALID_TYPE - objectType is not correct.            */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_GetObjHandleFromID(
                               void               *idBuffer,
                               unsigned long       bufLen,
                               cwbOBJ_ObjType      objectType,
                               cwbOBJ_ObjHandle   *objectHandle,
                               cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_GetObjID                                                */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the id of an object.  This is the data the uniquely        */
/*   identifies this object on the server.                          */
/*   The data gotten is not readable and is binary.  It can be      */
/*   passed back on the cwbOBJ_GetObjHandleFromID() API to get a    */
/*   handle back to that object.                                    */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle objectHandle - input                          */
/*     Handle of the object to get the id from.                     */
/*                                                                  */
/*   void *idBuffer - output                                        */
/*     The buffer that will hold the id of this object.             */
/*                                                                  */
/*   unsigned long bufLen - input                                   */
/*     The length of the buffer pointed to by pIDBuffer.            */
/*                                                                  */
/*   unsigned long *bytesNeeded - output                            */
/*     On output, this will be the number of bytes needed to hold   */
/*     id.                                                          */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not an allocated object handle. */
/*   CWB_BUFFER_OVERFLOW - Buffer too small.                        */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_GetObjID(
                               cwbOBJ_ObjHandle    objectHandle,
                               void               *idBuffer,
                               unsigned long       bufLen,
                               unsigned long      *bytesNeeded,
                               cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_GetParameter                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Gets the value of a parameter in a parameter list object.      */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ParmHandle parmListHandle - input                       */
/*     Handle of the parameter object.                              */
/*                                                                  */
/*   cwbOBJ_KeyID key - input                                       */
/*     The id of the parameter to get.                              */
/*                                                                  */
/*                                                                  */
/*   void *buffer - output                                          */
/*     The buffer that will hold the attribute value. If this call  */
/*     returns successfully.  The value of the key determines what  */
/*     type of data will be put into pBuffer.   The type is also    */
/*     returned to the *keyType parameter, if provided.             */
/*                                                                  */
/*   unsigned long bufLen - input                                   */
/*     The length of the buffer pointed to by buffer.               */
/*                                                                  */
/*   unsigned long *bytesNeeded - output                            */
/*     On output, this will be the number of bytes needed to hold   */
/*     result.                                                      */
/*                                                                  */
/*   cwbOBJ_DataType *keyType - output                              */
/*     Optional, may be NULL.  On output this will contain the type */
/*     of data used to represent this attribute and what is stored  */
/*     at *buffer.                                                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_INVALID_HANDLE - Handle is not an allocated object handle. */
/*   CWB_BUFFER_OVERFLOW - Buffer too small.                        */
/*   CWBOBJ_RC_KEY_NOT_FOUND - Key isn't specified in parameter list*/
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbOBJ_GetParameter(
                              cwbOBJ_ParmHandle    parmListHandle,
                              cwbOBJ_KeyID         key,
                              void                *buffer,
                              unsigned long        bufLen,
                              unsigned long       *bytesNeeded,
                              cwbOBJ_DataType     *keyType,
                              cwbSV_ErrHandle      errorHandle);
#endif   // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbOBJ_GetParameterA(
                                cwbOBJ_ParmHandle    parmListHandle
                              , cwbOBJ_KeyID         key
                              , void                *buffer
                              , ULONG                bufLen
                              , ULONG               *bytesNeeded
                              , cwbOBJ_DataType     *keyType
                              , cwbSV_ErrHandle      errorHandle
                                          );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbOBJ_GetParameterW(
                                cwbOBJ_ParmHandle    parmListHandle
                              , cwbOBJ_KeyID         key
                              , void                *buffer
                              , ULONG                bufLen
                              , ULONG               *bytesNeeded
                              , cwbOBJ_DataType     *keyType
                              , cwbSV_ErrHandle      errorHandle
                                          );
#endif    // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbOBJ_GetParameter             cwbOBJ_GetParameterW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbOBJ_GetParameter             cwbOBJ_GetParameterA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_GetSplFHandleFromNewSplF()                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Uses a new spooled file handle to generate a spooled file      */
/*   handle.   See notes below about using this API on a new spooled*/
/*   file that was created with data type automatic.                */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle newSplFHandle - input                         */
/*     New spooled file handle.  This is the handle passed back on  */
/*     the cwbOBJ_CreateNewSplF() API.                              */
/*                                                                  */
/*                                                                  */
/*   cwbOBJ_ObjHandle *splFHandle - output                          */
/*     Pointer to an object handle that, upon successful            */
/*     completion of this call, will hold the spooled file handle.  */
/*     This handle may be used with other APIs that take a          */
/*     spooled file handle as input.                                */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not valid spooled file handle.  */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*   CWBOBJ_RC_SPLFNOTOPEN - Spooled file hasn't been created on the*/
/*                           host yet.                              */
/*                                                                  */
/* Usage Notes:                                                     */
/*    The handle returned in splFHandle must be released with the   */
/*    cwbOBJ_DeleteObjHandle() API in order to free resources.      */
/*                                                                  */
/*    If you are using automatic data typing for the spooled file   */
/*    (the attribute of CWBOBJ_KEY_PRTDEVTYPE was set to *AUTO or   */
/*     or wasn't specified on the cwbOBJ_CreateNewSplF() API) then  */
/*    creation of the spooled file will be delayed until sufficient */
/*    data has been written to the spooled file to determine the    */
/*    type of the data (*SCS, *AFPDS or *USERASCII).   If the new   */
/*    spooled file is in this state when you call this API, the     */
/*    return code will be CWBOBJ_RC_SPLFNOTOPEN.                    */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbOBJ_GetSplFHandleFromNewSplF(
                              cwbOBJ_ObjHandle     newSplFHandle,
                              cwbOBJ_ObjHandle    *splFHandle,
                              cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_GetSplFMsgAttr                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   Retrieves an attribute of a message that's associated with a   */
/*   spooled file                                                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle splFHandle - input                            */
/*     Handle of the spooled file.                                  */
/*                                                                  */
/*   cwbOBJ_KeyID key - input                                       */
/*     Identifying key of the attribute to retrieve.                */
/*     The CWBOBJ_KEY_XXX constants define the key ids.             */
/*                                                                  */
/*   void *buffer - output                                          */
/*     The buffer that will hold the attribute value, if this call  */
/*     returns successfully.  The value of the key determines what  */
/*     type of data will be put into pBuffer.   The type is also    */
/*     returned to the *keyType parameter, if provided.             */
/*                                                                  */
/*   unsigned long bufLen - input                                   */
/*     The length of the buffer pointed to by pBuffer.              */
/*                                                                  */
/*   unsigned long *bytesNeeded - output                            */
/*     On output, this will be the number of bytes needed to hold   */
/*     result.                                                      */
/*                                                                  */
/*   cwbOBJ_DataType *keyType - output                              */
/*     Optional, may be NULL.  On output this will contain the type */
/*     of data used to represent this attribute and what is stored  */
/*     at *buffer.                                                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_INVALID_HANDLE - Handle is not an allocated object handle. */
/*   CWB_BUFFER_OVERFLOW - Buffer too small.                        */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*   CWBOBJ_RC_INVALID_KEY - Key isn't valid.                       */
/*   CWBOBJ_RC_SPLFNOMESSAGE - The spooled file isn't waiting on a  */
/*                               message.                           */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*  The following keys are valid:                                   */
/*     CWBOBJ_KEY_MSGTEXT       -   Message text                    */
/*     CWBOBJ_KEY_MSGHELP       -   Message help text               */
/*     CWBOBJ_KEY_MSGREPLY      -   Message reply                   */
/*     CWBOBJ_KEY_MSGTYPE       -   Message type                    */
/*     CWBOBJ_KEY_MSGID         -   Message ID                      */
/*     CWBOBJ_KEY_MSGSEV        -   Message severity                */
/*     CWBOBJ_KEY_DATE          -   Message date                    */
/*     CWBOBJ_KEY_TIME          -   Message time                    */
/*                                                                  */
/*  Message formatting characters will appear in the message text   */
/*  and should be used as follows:                                  */
/*    &N - Force the text to a new line (column 2).  If the text is */
/*         longer than 1 line, the next lines should be indented to */
/*         column 4 until the end of text or another format control */
/*         character is found.                                      */
/*    &P - Force the text to new line indented to column 6.  If the */
/*         text is longer than 1 line, next lines should start in   */
/*         column 4 until end of text or another format control     */
/*         character is found.                                      */
/*    &B - Force the text to a new line starting in colum 4.  If the*/
/*         text is longer than 1 line, next lines should start in   */
/*         column 6 until end of text or another format control     */
/*         character is found.                                      */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY  cwbOBJ_GetSplFMsgAttr(
                               cwbOBJ_ObjHandle    splFHandle,
                               cwbOBJ_KeyID        key,
                               void               *buffer,
                               unsigned long       bufLen,
                               unsigned long      *bytesNeeded,
                               cwbOBJ_DataType    *keyType,
                               cwbSV_ErrHandle     errorHandle);
#endif   // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbOBJ_GetSplFMsgAttrA(
                                     cwbOBJ_ObjHandle    splFHandle
                                   , cwbOBJ_KeyID        key
                                   , void               *buffer
                                   , ULONG               bufLen
                                   , ULONG              *bytesNeeded
                                   , cwbOBJ_DataType    *keyType
                                   , cwbSV_ErrHandle     errorHandle
                                            );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbOBJ_GetSplFMsgAttrW(
                                     cwbOBJ_ObjHandle    splFHandle
                                   , cwbOBJ_KeyID        key
                                   , void               *buffer
                                   , ULONG               bufLen
                                   , ULONG              *bytesNeeded
                                   , cwbOBJ_DataType    *keyType
                                   , cwbSV_ErrHandle     errorHandle
                                            );
#endif    // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbOBJ_GetSplFMsgAttr           cwbOBJ_GetSplFMsgAttrW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbOBJ_GetSplFMsgAttr           cwbOBJ_GetSplFMsgAttrA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_HoldOutputQueue                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Holds an iSeries output queue.                                 */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle queueHandle - input                           */
/*     Handle of the output queue to be held.                       */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not a  valid queue handle.      */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_HoldOutputQueue(
                        cwbOBJ_ObjHandle queueHandle,
                        cwbSV_ErrHandle errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_HoldSplF                                                */
/*                                                                  */
/* Purpose:                                                         */
/*   Holds a spooled file.                                          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle splFHandle - input                            */
/*     Handle of the spooled file to be held.                       */
/*                                                                  */
/*   cwbOBJ_ParmHandle *parmListHandle - input                      */
/*     Optional.  A pointer to a valid parameter list object handle */
/*     that contains parameters for holding the spooled file.       */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not valid.                      */
/*   CWB_INVALID_PARAMETER - Invalid parameter specified.           */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*   CWBOBJ_RC_INVALID_TYPE - Handle is not a spooled file handle   */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/*   The following parameter key's may be set in the parmListHandle */
/*   object:                                                        */
/*                                                                  */
/*    CWBOBJ_KEY_HOLDTYPE       - what type of hold to do.  May be  */
/*                                "*IMMED" or "*PAGEEND".  "*IMMED" */
/*                                is the default.                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_HoldSplF(
                               cwbOBJ_ObjHandle    splFHandle,
                               cwbOBJ_ParmHandle  *parmListHandle,
                               cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_IsViewerAvailable                                       */
/*                                                                  */
/* Purpose:                                                         */
/*   Checks if the spooled file viewer is available.                */
/*                                                                  */
/* Parameters:                                                      */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK   - Successful completion (viewer is installed)         */
/*   CWB_NO_VIEWER - Viewer not installed                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use this function to test for the presence of the viewer on    */
/*   the workstation.  If the viewer is installed this function will*/
/*   return CWB_OK.  If the viewer is not available, the function   */
/*   will return CWB_NO_VIEWER and the errorHandle parameter (if    */
/*   provided) will contain an appropriate error message.           */
/*   Using this function, applications can check for viewer support */
/*   without calling the cwbOBJ_DisplaySplF() API.                  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_IsViewerAvailable(
                               cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_MoveSplF                                                */
/*                                                                  */
/* Purpose:                                                         */
/*   Moves an iSeries spooled file to another output queue or to    */
/*   another position on the same output queue.                     */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle splFHandle - input                            */
/*     Handle of the spooled file to be moved.                      */
/*                                                                  */
/*   cwbOBJ_ObjHandle *targetSplFHandle - input                     */
/*     Optional.  The handle of another spooled file on the same    */
/*     system, that specifies the spooled file to move this spooled */
/*     file after.  If this is specified, *outputQueueHandle is not */
/*     used.                                                        */
/*                                                                  */
/*   cwbOBJ_ObjHandle *outputQueueHandle - input                    */
/*     Optional.  The handle of an output queue on the same system  */
/*     that specifies which output queue to move the spooled file   */
/*     to.  The spooled file will be moved to the first position on */
/*     this queue.   This parameter is ignored if targetSplFHandle  */
/*     is specified.                                                */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not valid.                      */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*   CWBOBJ_RC_INVALID_TYPE - Handle is not a spooled file handle.  */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/*   If both targetSplFHandle and outputQueueHandle are NULL, the   */
/*   spooled file will be moved to the first position on the current*/
/*   output queue.                                                  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_MoveSplF(
                               cwbOBJ_ObjHandle    splFHandle,
                               cwbOBJ_ObjHandle   *targetSplFHandle,
                               cwbOBJ_ObjHandle   *outputQueueHandle,
                               cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_OpenList                                                */
/*                                                                  */
/* Purpose:                                                         */
/*   Open the list.  This actually builds the list.  Caller must    */
/*   call the cwbOBJ_ClostList() API when done with the list to     */
/*   free resources.                                                */
/*   After the list is opened, the caller may use other APIs on     */
/*   the list to do things such as get the list size and get object */
/*   handles to items in the list.                                  */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ListHandle listHandle - input                           */
/*     Handle of the list to open.                                  */
/*                                                                  */
/*   cwbOBJ_List_OpenType openHandle - input                        */
/*     Manner in which to open the list.                            */
/*     Must be set to CWBOBJ_LIST_OPEN_SYNCH                        */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not an allocated list handle.   */
/*   CWBOBJ_RC_LIST_OPEN  - The list is already open.               */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*   CWBOBJ_RC_NOHOSTSUPPORT - Host doesn't support this type of    */
/*                              list.                               */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_OpenList(
                               cwbOBJ_ListHandle     listHandle,
                               cwbOBJ_List_OpenType  openType,
                               cwbSV_ErrHandle       errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_OpenResource                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Opens an AFP resource object for reading.                      */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle resourceHandle - input                        */
/*     Handle of the AFP resource file to be opened for reading.    */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not valid resource handle.      */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*   CWBOBJ_RC_NOHOSTSUPPORT - Host doesn't support working with    */
/*                              Resources.                          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The resource should be closed with the cwbOBJ_CloseResource()  */
/*   API when done reading from it.                                 */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_OpenResource(
                               cwbOBJ_ObjHandle    resourceHandle,
                               cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_OpenResourceForSplF                                     */
/*                                                                  */
/* Purpose:                                                         */
/*   Opens an AFP Resource object for reading for a spooled file    */
/*    that is already opened for reading.                           */
/*    The API is useful if you are reading an AFP Spooled file and  */
/*    run into an external AFP Resource that you need to read.      */
/*    Using this API you can open that resource for reading without */
/*    having to list the resource first.                            */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle splFHandle - input                            */
/*     Handle of the spooled file that is already opened for        */
/*      reading and that the resource will be opened against.       */
/*      The same conversation (and same instance of the the network */
/*      print server program on the iSeries) will be used for reading*/
/*      the resource and spooled file.                              */
/*                                                                  */
/*   const char *resourceName - input                               */
/*     Pointer to the name of the AFP Resource in an ASCIIZ string. */
/*                                                                  */
/*   const char *resourceLibrary - input                            */
/*     Optional, may be NULL.                                       */
/*     Pointer to the iSeries library of the AFP Resource in an     */
/*      ASCIIZ string. If no library is specified, the library list */
/*      of the spooled file is used to search for the resource.     */
/*                                                                  */
/*   unsigned long resourceType - input                             */
/*     An unsigned long integer with one of the following bits on:  */
/*                 CWBOBJ_AFPRSC_FONT                               */
/*                 CWBOBJ_AFPRSC_FORMDEF                            */
/*                 CWBOBJ_AFPRSC_OVERLAY                            */
/*                 CWBOBJ_AFPRSC_PAGESEG                            */
/*                 CWBOBJ_AFPRSC_PAGEDEF                            */
/*     Specifies what type of resource to open.                     */
/*                                                                  */
/*   const char *reserved -                                         */
/*     Reserved, must be NULL.                                      */
/*                                                                  */
/*   cwbOBJ_OBJHandle *resourceHandle - output                      */
/*     Pointer to an OBJHandle that on successful return will       */
/*     contain the dynamically allocated resource handle that can   */
/*     be used to read, seek and eventually close the resource.     */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_FILE_NOT_FOUND - The resource wasn't found                 */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_INVALID_HANDLE - Handle is not valid resource handle.      */
/*   CWB_INVALID_PARAMETER  - Invalid parameter specified.          */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*   CWBOBJ_RC_SPLFNOTOPEN - The spooled file is not opened         */
/*   CWBOBJ_RC_NOHOSTSUPPORT - Host doesn't support working with    */
/*                              Resources.                          */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This call, if successful, will generate a temporary resource   */
/*   handle and return it in the resourceHandle parameter.  This    */
/*   handle will be deleted automatically when the caller calls the */
/*   cwbOBJ_CloseResource() API with it.                            */
/*                                                                  */
/*   The resource should be closed with the cwbOBJ_CloseResource()  */
/*   API when done reading from it.                                 */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY  cwbOBJ_OpenResourceForSplF(
                               cwbOBJ_ObjHandle    splFHandle,
                               const char         *resourceName,
                               const char         *resourceLibrary,
                               unsigned long       resourceType,
                               const char         *reserved,
                               cwbOBJ_ObjHandle   *resourceHandle,
                               cwbSV_ErrHandle     errorHandle);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbOBJ_OpenResourceForSplFA(
                               cwbOBJ_ObjHandle    splFHandle
                             , LPCSTR              resourceName
                             , LPCSTR              resourceLibrary
                             , ULONG               resourceType
                             , LPCSTR              reserved
                             , cwbOBJ_ObjHandle   *resourceHandle
                             , cwbSV_ErrHandle     errorHandle
                                                 );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbOBJ_OpenResourceForSplFW(
                               cwbOBJ_ObjHandle    splFHandle
                             , LPCWSTR             resourceName
                             , LPCWSTR             resourceLibrary
                             , ULONG               resourceType
                             , LPCWSTR             reserved
                             , cwbOBJ_ObjHandle   *resourceHandle
                             , cwbSV_ErrHandle     errorHandle
                                                 );
#endif   // UNICODE-only selection

#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbOBJ_OpenResourceForSplF      cwbOBJ_OpenResourceForSplFW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbOBJ_OpenResourceForSplF      cwbOBJ_OpenResourceForSplFA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_OpenSplF                                                */
/*                                                                  */
/* Purpose:                                                         */
/*   Opens an iSeries spooled file for reading.                     */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle splFHandle - input                            */
/*     Handle of the spooled file to be opened for reading.         */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not valid spooled file handle.  */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The spooled file should be closed with the cwbOBJ_CloseSplF()  */
/*   API when done reading from it.                                 */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_OpenSplF(
                               cwbOBJ_ObjHandle    splFHandle,
                               cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_OpenSplFEx                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Opens an iSeries spooled file for reading while allowing the   */
/*   caller to set the open attributes.                             */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle splFHandle - input                            */
/*     Handle of the spooled file to be opened for reading.         */
/*                                                                  */
/*   cwbOBJ_ParmHandle *pParmListHandle - input                     */
/*     handle of the parameter object containing the attributes     */
/*     to be set when opening the spoolfile.                        */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.  If an error occurs that there is error  */
/*     text for, this handle may be used to retreive the error      */
/*     message and secondary help text.                             */
/*                                                                  */
/* Return Codes:                                                    */
/*   CWB_OKOR - no error occurred                                   */
/*   CWB_NOT_ENOUGH_MEMORY - insufficient memory                    */
/*   CWB_INVALID_HANDLE - handle is not valid spooled file handle   */
/*   CWBOBJ_RC_HOST_ERROR - Host error occured. Text may be in      */
/*                          errorHandle.                            */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The spooled file should be closed with the cwbOBJ_CloseSplF()  */
/*   API when done reading from it.                                 */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_OpenSplFEx(cwbOBJ_ObjHandle  splFHandle,
                                          cwbOBJ_ParmHandle parmListHandle,
                                          cwbSV_ErrHandle errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_PurgeOutputQueue                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   Purges spooled files on an iSeries output queue.               */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle queueHandle - input                           */
/*     Handle of the output queue to be purged.                     */
/*                                                                  */
/*   cwbOBJ_ParmHandle * parmListHandle - input                     */
/*     Optional.  A pointer to a valid parameter list object handle */
/*     that contains parameters for purging the output queue.       */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not valid.                      */
/*   CWB_INVALID_PARAMETER   - Invalid parameter specified.         */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/*   The parameters specified in parmListHandle, if provided, will  */
/*   specify which spooled files are purged.  If parmListHandle is  */
/*   NULL, all spooled files for the current user are purged.       */
/*                                                                  */
/*   The following parameter key's may be set in the parmListHandle */
/*   object:                                                        */
/*                                                                  */
/*    CWBOBJ_KEY_USER           - which user's spooled files to     */
/*                                purge. May be a specific user ID, */
/*                                "*ALL" or "*CURRENT".  "*CURRENT" */
/*                                is the default.                   */
/*    CWBOBJ_KEY_FORMTYPE       - which spooled files to purge based*/
/*                                on what formtype they have.  May  */
/*                                be a specific formtype, "*ALL" or */
/*                                "*STD".  "*ALL" is the default.   */
/*    CWBOBJ_KEY_USERDATA       - which spooled files to purge based*/
/*                                on what userdata they have.  May  */
/*                                be a specific value or "*ALL".    */
/*                                "*ALL" is the default.            */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_PurgeOutputQueue(
                               cwbOBJ_ObjHandle    queueHandle,
                               cwbOBJ_ParmHandle  *parmListHandle,
                               cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_ReadResource                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Reads bytes from the current read location.                    */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle resourceHandle - input                        */
/*     Handle of the AFP resource object to be read from.           */
/*                                                                  */
/*   char *buffer - input                                           */
/*     Pointer to buffer to hold the bytes read from the resource.  */
/*                                                                  */
/*   unsigned long bytesToRead - input                              */
/*     Maximum number of bytes to read.  The number read may be less*/
/*     than this.                                                   */
/*                                                                  */
/*   unsigned long *bytesRead - output                              */
/*     Number of bytes actually read.                               */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not valid spooled file handle   */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*   CWBOBJ_RC_RSCNOTOPEN - Resource file has not been opened yet.  */
/*   CWBOBJ_RC_ENDOFFILE - The end of file was read.                */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The cwbOBJ_OpenResource() API must be called with this resource*/
/*   handle before this API is called OR the handle must be         */
/*   retrieved with a call to the cwbOBJ_OpenResourceForSplF() API. */
/*   If the end of file is reached when reading, the return code    */
/*   will be CWBOBJ_RC_ENDOFFILE and bytesRead will contain the     */
/*   actual number of bytes read.                                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_ReadResource(
                               cwbOBJ_ObjHandle    resourceHandle,
                               char               *bBuffer,
                               unsigned long       bytesToRead,
                               unsigned long      *bytesRead,
                               cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_ReadSplF                                                */
/*                                                                  */
/* Purpose:                                                         */
/*   Reads bytes from the current read location.                    */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle splFHandle - input                            */
/*     Handle of the spooled file to be read from.                  */
/*                                                                  */
/*   char *buffer - input                                           */
/*     Pointer to buffer to hold the bytes read from the spooled    */
/*     file.                                                        */
/*                                                                  */
/*   unsigned long bytesToRead - input                              */
/*     Maximum number of bytes to read.  The number read may be less*/
/*     than this.                                                   */
/*                                                                  */
/*   unsigned long *bytesRead - output                              */
/*     Number of bytes actually read.                               */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not valid spooled file handle   */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*   CWBOBJ_RC_SPLFNOTOPEN - Spooled file has not been opened yet.  */
/*   CWBOBJ_RC_SPLFENDOFFILE - The end of file was read.            */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The cwbOBJ_OpenSplF() API must be called with this spooled file*/
/*   handle before this API is called.                              */
/*   If the end of file is reached when reading, the return code    */
/*   will be CWBOBJ_RC_ENDOFFILE and bytesRead will contain the     */
/*   actual number of bytes read.                                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_ReadSplF(
                               cwbOBJ_ObjHandle    splFHandle,
                               char               *bBuffer,
                               unsigned long       bytesToRead,
                               unsigned long      *bytesRead,
                               cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_RefreshObj                                              */
/*                                                                  */
/* Purpose:                                                         */
/*   Refreshes the object with the latest information from the      */
/*   iSeries server.  This will ensure the attributes returned for  */
/*   the object are up to date.                                     */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle objectHandle - input                          */
/*     Handle of the object to be refreshed.                        */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not an allocated object handle. */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*                                                                  */
/* Usage Notes:                                                     */
/* The following object types may be refreshed.                     */
/*    CWBOBJ_LIST_SPLF (spooled files)                              */
/*    CWBOBJ_LIST_PRTF (printer files)                              */
/*    CWBOBJ_LIST_OUTQ (output queues)                              */
/*    CWBOBJ_LIST_PRTD (printer devices)                            */
/*    CWBOBJ_LIST_WTR (writers)                                     */
/*                                                                  */
/* Example:                                                         */
/*   assume listHandle points to a spooled file list with at least  */
/*   one entry in it.                                               */
/*                                                                  */
/*    cwbOBJ_ObjHandle splFileHandle;                               */
/*    ulRC = cwbOBJ_GetObjHandle(listHandle,                        */
/*                               0,                                 */
/*                               &splFileHandle,                    */
/*                               NULL);                             */
/*    if (ulRC == CWB_NO_ERROR)                                     */
/*    {                                                             */
/*        ulRC = cwbOBJ_RefreshObj(splFileHandle);                  */
/*            .....                                                 */
/*            get attributes for object                             */
/*            .....                                                 */
/*        ulRC = cwbOBJ_DeleteObjHandle(splFileHandle);             */
/*    }                                                             */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbOBJ_RefreshObj(
                              cwbOBJ_ObjHandle     objectHandle,
                              cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_ReleaseOutputQueue                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Releases an iSeries output queue.                              */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle queueHandle - input                           */
/*     Handle of the output queue to be released.                   */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not a valid queue handle.       */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_ReleaseOutputQueue(
                               cwbOBJ_ObjHandle    queueHandle,
                               cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_ReleaseSplF                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Releases a spooled file.                                       */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle splFHandle - input                            */
/*     Handle of the spooled file to be released.                   */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not valid.                      */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*   CWBOBJ_RC_INVALID_TYPE - Handle is not a spooled file handle   */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_ReleaseSplF(
                               cwbOBJ_ObjHandle    splFHandle,
                               cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_ResetListAttrsToRetrieve                                */
/*                                                                  */
/* Purpose:                                                         */
/*   Resets the list attributes to retrieve information to its      */
/*   default list.                                                  */
/*                                                                  */
/* Parameters:                                                      */
/*                                                                  */
/*   cwbOBJ_ListHandle listHandle - input                           */
/*     List handle to reset.                                        */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK   - Successful completion                               */
/*   CWB_INVALID_HANDLE - Handle is not an allocated list handle.   */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Use this call to reset the list handle's list of attributes    */
/*   to retrieve after calling cwbOBJ_SetListAttrsToRetrieve().     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_ResetListAttrsToRetrieve(
                               cwbOBJ_ListHandle    listHandle,
                               cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_ResetListFilter                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Resets the filter on a list to what it was when the list was   */
/*   first allocated (the default filter).                          */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ListHandle listHandle - input                           */
/*     Handle of the list to have its filter reset.                 */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not allocated list handle.      */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The list must be closed and reopened for the change to take    */
/*   affect.                                                        */
/*                                                                  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_ResetListFilter(
                               cwbOBJ_ListHandle   listHandle,
                               cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_SeekResource                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Moves the current read position on a resource that is open     */
/*   for reading.                                                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle resourceHandle - input                        */
/*     Handle of the AFP resource file to be seeked.                */
/*                                                                  */
/*   cwbOBJ_SeekOrigin seekOrigin - input                           */
/*     Where to seek from.  Valid values are:                       */
/*      CWBOBJ_SEEK_BEGINNING - seek from the beginning of file     */
/*      CWBOBJ_SEEK_CURRENT   - seek from the current read position */
/*      CWBOBJ_SEEK_ENDING    - seek from the end of the file       */
/*                                                                  */
/*   signed long seekOffset - input                                 */
/*     Offset (negative or positive) from the seek origin in bytes  */
/*     to move the current read pointer to.                         */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not valid spooled file handle   */
/*   CWB_INVALID_PARAMETER   - Invalid parameter specified.         */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*   CWBOBJ_RC_RSCNOTOPEN  - Resource has not been opened yet.      */
/*   CWBOBJ_RC_SEEKOUTOFRANGE - Seek offset out of range.           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The cwbOBJ_OpenResource() API must be called with this resource*/
/*   handle before this API is called OR the handle must be         */
/*   retrieved with a call to the cwbOBJ_OpenResourceForSplF() API. */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_SeekResource(
                               cwbOBJ_ObjHandle    resourceHandle,
                               cwbOBJ_SeekOrigin   seekOrigin,
                               signed long         seekOffset,
                               cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_SeekSplF                                                */
/*                                                                  */
/* Purpose:                                                         */
/*   Moves the current read position on a spooled file that is open */
/*   for reading.                                                   */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle splFHandle - input                            */
/*     Handle of the spooled file to be seeked.                     */
/*                                                                  */
/*   cwbOBJ_SeekOrigin seekOrigin - input                           */
/*     Where to seek from.  Valid values are:                       */
/*      CWBOBJ_SEEK_BEGINNING - seek from the beginning of file     */
/*      CWBOBJ_SEEK_CURRENT   - seek from the current read position */
/*      CWBOBJ_SEEK_ENDING    - seek from the end of the file       */
/*                                                                  */
/*   signed long seekOffset - input                                 */
/*     Offset (negative or positive) from the seek origin in bytes  */
/*     to move the current read pointer to.                         */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not valid spooled file handle   */
/*   CWB_INVALID_PARAMETER   - Invalid parameter specified.         */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*   CWBOBJ_RC_SPLFNOTOPEN  - Spooled file has not been opened yet. */
/*   CWBOBJ_RC_SEEKOUTOFRANGE - Seek offset out of range.           */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The cwbOBJ_OpenSplF() API must be called with this spooled file*/
/*   handle before this API is called.                              */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_SeekSplF(
                               cwbOBJ_ObjHandle    splFHandle,
                               cwbOBJ_SeekOrigin   seekOrigin,
                               signed long         seekOffset,
                               cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_SendNetSplF                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Sends a spooled file to another user on the same system or to  */
/*   a remote system on the network.                                */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle splFHandle - input                            */
/*     Handle of the spooled file to be sent.                       */
/*                                                                  */
/*   cwbOBJ_ParmHandle parmListHandle - input                       */
/*     Required.  A handle of a parameter list object that contains */
/*     the parameters for sending the spooled file.                 */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not valid.                      */
/*   CWB_INVALID_PARAMETER - invalid parameter specified.           */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*   CWBOBJ_RC_INVALID_TYPE - Handle is not a spooled file handle.  */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/*   The equivalent of an iSeries send net spooled file (SNDNETSPLF)*/
/*   command will be issued against the spooled file.               */
/*                                                                  */
/*   The following parameter key's MUST be set in the parmListHandle*/
/*   object:                                                        */
/*                                                                  */
/*    CWBOBJ_KEY_TOUSERID       - Specifies user ID to send the     */
/*                                spooled file to.                  */
/*                                                                  */
/*    CWBOBJ_KEY_TOADDRESS      - Specifies the remote system to    */
/*                                send the spooled file to.         */
/*                                "*NORMAL" is the default.         */
/*                                                                  */
/*   The following parameter key's may be set in the parmListHandle */
/*   object:                                                        */
/*                                                                  */
/*    CWBOBJ_KEY_DATAFORMAT     - Specifies the data format in which*/
/*                                to transmit the spooled file.     */
/*                                May be "*RCDDATA" or "*ALLDATA".  */
/*                                "*RCDDATA" is the default.        */
/*                                                                  */
/*    CWBOBJ_KEY_VMMVSCLASS     - Specifies the VM/MVS SYSOUT class */
/*                                for distributions sent to a VM    */
/*                                host system or to an MVS host     */
/*                                system.                           */
/*                                May be "A" to "Z" or "0" to "9".  */
/*                                "A" is the default.               */
/*                                                                  */
/*    CWBOBJ_KEY_SENDPTY        - Specifies the queueing priority   */
/*                                used for this spooled file when   */
/*                                it is being routed through a snads*/
/*                                network.                          */
/*                                May be "*NORMAL" or "*HIGH".      */
/*                                "*NORMAL" is the default.         */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_SendNetSplF(
                               cwbOBJ_ObjHandle    splFHandle,
                               cwbOBJ_ParmHandle   parmListHandle,
                               cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_SendTCPSplF                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Sends a spooled file to be printed on a remote system.  This is*/
/*   the iSeries version of the TCP/IP LPR command.                 */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle splFHandle - input                            */
/*     Handle of the spooled file to be sent.                       */
/*                                                                  */
/*   cwbOBJ_ParmHandle parmListHandle - input                       */
/*     Required.  A handle of a parameter list object that contains */
/*     the parameters for sending the spooled file.                 */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not valid.                      */
/*   CWB_INVALID_PARAMETER - Invalid parameter specified.           */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*   CWBOBJ_RC_INVALID_TYPE - Handle is not a spooled file handle.  */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/*   The equivalent of an iSeries send TCP/IP spooled file          */
/*   (SNDTCPSPLF) command will be issued against the spooled file.  */
/*                                                                  */
/*   The following parameter key's MUST be set in the parmListHandle*/
/*   object:                                                        */
/*                                                                  */
/*    CWBOBJ_KEY_RMTSYSTEM      - Specifies the remote system to    */
/*                                which the print request is sent.  */
/*                                May be a remote system name or    */
/*                                "*INTNETADR".                     */
/*                                                                  */
/*    CWBOBJ_KEY_RMTPRTQ        - Specifies the name of the         */
/*                                destination print queue.          */
/*                                                                  */
/*   The following parameter key's may be set in the parmListHandle */
/*   object:                                                        */
/*                                                                  */
/*    CWBOBJ_KEY_DELETESPLF     - Specifies whether or not to delete*/
/*                                the spooled file after it has been*/
/*                                successfully sent.                */
/*                                May be "*NO" or "*YES".           */
/*                                "*NO" is the default.             */
/*                                                                  */
/*    CWBOBJ_KEY_DESTOPTION     - Specifies a destination-dependant */
/*                                option.  These options will be    */
/*                                sent to the remote system with    */
/*                                the spooled file.                 */
/*                                                                  */
/*    CWBOBJ_KEY_DESTINATION    - Specifies the type of system to   */
/*                                which the spooled file is being   */
/*                                sent.  When sending to other      */
/*                                iSeries systems, this value should*/
/*                                be "*AS/400".  May also be        */
/*                                "*OTHER", "*PSF/2".  "*OTHER" is  */
/*                                the default.                      */
/*                                                                  */
/*    CWBOBJ_KEY_INTERNETADDR   - Specifies the internet address of */
/*                                the receiving system.             */
/*                                                                  */
/*    CWBOBJ_KEY_MFGTYPE        - Specifies the manufacturer, type  */
/*                                and model when transforming print */
/*                                data for SCS to ASCII.            */
/*                                                                  */
/*    CWBOBJ_KEY_SCS2ASCII      - Specifies wether the print data   */
/*                                is to be transformed for SCS to   */
/*                                ASCII.                            */
/*                                May be "*NO" or "*YES".           */
/*                                "*NO" is the default.             */
/*                                                                  */
/*    CWBOBJ_KEY_WSCUSTMOBJ     - Specifies the name of the         */
/*                                workstation customizing object.   */
/*                                                                  */
/*    CWBOBJ_KEY_WSCUSTMOBJL    - Specifies the name of the         */
/*                                workstation customizing object    */
/*                                library.                          */
/*                                                                  */
/*    CWBOBJ_KEY_SEPPAGE        - Specifies wether or not to print  */
/*                                the separator page.               */
/*                                                                  */
/*    CWBOBJ_KEY_USRDTATFMLIB   - Specifies the name of the user    */
/*                                data transform library.           */
/*                                                                  */
/*    CWBOBJ_KEY_USRDTATFM      - Specifies the name of the user    */
/*                                data transform.                   */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_SendTCPSplF(
                               cwbOBJ_ObjHandle    splFHandle,
                               cwbOBJ_ParmHandle   parmListHandle,
                               cwbSV_ErrHandle     errorHandle);


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_SetConnectionsToKeep                                    */
/*                                                                  */
/* Purpose:                                                         */
/*   Set the number of connections that should be left active for a */
/*   pariticular system.                                            */
/*   Normally, the cwbobj.dll will time out and drop connections    */
/*   after they have not been used for a while.  With this API you  */
/*   can force it to leave open a certain number of connections for */
/*   this system.                                                                                                       */
/*                                                                  */
/* Parameters:                                                      */
/*   const char *systemName - input                                 */
/*     Pointer to the system name contained in ASCIIZ string        */
/*                                                                  */
/*   unsigned int connections - input                               */
/*     The  number to of connections to keep open.                  */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_PARAMETER   - Invalid parameter specified.         */
/*                                                                  */
/* Usage Notes:                                                     */
/*   The default number of connections left open per system is 0.   */
/*   The connections are made per process so this API only affects  */
/*   connections under the process it is called under.              */
/*   Setting the number of connections to be left open does not open*/
/*   any new connections.                                           */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbOBJ_SetConnectionsToKeep(
                                const char *systemName
                              , unsigned int connections
                              , cwbSV_ErrHandle  errorHandle);
#endif   // OEM-only selection
#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbOBJ_SetConnectionsToKeepA(
                               LPCSTR systemName
                             , unsigned int connections
                             , cwbSV_ErrHandle  errorHandle
                                                  );

#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbOBJ_SetConnectionsToKeepW(
                               LPCWSTR systemName
                             , unsigned int connections
                             , cwbSV_ErrHandle  errorHandle
                                                  );

#endif   // UNICODE-only selection

#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbOBJ_SetConnectionsToKeep      cwbOBJ_SetConnectionsToKeepW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbOBJ_SetConnectionsToKeep      cwbOBJ_SetConnectionsToKeepA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_SetListAttrsToRetrieve                                  */
/*                                                                  */
/* Purpose:                                                         */
/*   An optional function that may be applied to list handle before */
/*   the list is opened.  The purpose of doing this is to improve   */
/*   efficiency by allowing the cwbOBJ_OpenList() API to retrieve   */
/*   just the attributes of each object that the application will be*/
/*   using.                                                         */
/*                                                                  */
/* Parameters:                                                      */
/*                                                                  */
/*   cwbOBJ_ListHandle listHandle - input                           */
/*     List handle to apply the list of attribute keys to.          */
/*                                                                  */
/*   unsigned long numKeys - input                                  */
/*     The number of keys pointed to by the 'keys' parameter.       */
/*     May be 0, which means that no attributes are needed for      */
/*     objects in the list.                                         */
/*                                                                  */
/*   const cwbOBJ_KeyID *keys - input                               */
/*     An array of numKeys keys that are the IDs of the attributes  */
/*     to be retrieved for each object in the list when the list is */
/*     opened.                                                      */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK   - Successful completion                               */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not an allocated list handle.   */
/*   CWB_INVALID_PARAMETER  - Invalid parameter specified.          */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This call is  used to provide a clue to the cwbOBJ_OpenList()  */
/*   API as to what attributes the application is interested in for */
/*   the objects that are listed.  Using this information, the      */
/*   cwbOBJ_OpenList() API can be more efficient.                   */
/*   The attribute keys that are valid in the 'keys' list depend on */
/*   type of object being listed (set on cwbOBJ_CreateListHandle()).*/
/*   Call cwbOBJ_ResetListAttrsToRetrieve() to reset the list to    */
/*   its default list of keys.                                      */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_SetListAttrsToRetrieve(
                               cwbOBJ_ListHandle    listHandle,
                               unsigned long        numKeys,
                               const cwbOBJ_KeyID  *keys,
                               cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_SetListFilter                                           */
/*                                                                  */
/* Purpose:                                                         */
/*    Sets filters for the list.  This filter is applied the next   */
/*    time cwbOBJ_OpenList() is called.                             */
/*                                                                  */
/* Parameters:                                                      */
/*                                                                  */
/*   cwbOBJ_ListHandle listHandle - input                           */
/*     List handle that this filter will be applied to.             */
/*                                                                  */
/*   cwbOBJ_KeyID key - input                                       */
/*     The id of the filtering field to be set.                     */
/*                                                                  */
/*   const void *value - input                                      */
/*     The value this field should be set to.                       */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_INVALID_HANDLE - List handle not found.                    */
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
/*   The value of key will determine the type that is pointed to    */
/*   value.  The length of value is determined by its type.         */
/*   See also the cwbOBJ_SetListFilterWithSplF() API to list AFP    */
/*   resources used by a spooled file.                              */
/*                                                                  */
/* The following filters may be set against these list types        */
/* Spooled File Lists:                                              */
/*  CWBOBJ_LIST_SPLF:              default value:                   */
/*        CWBOBJ_KEY_USER          - Specifies which user's spooled */
/*                                   files are to be listed.        */
/*                                   May be a specific user ID or   */
/*                                   one of these special values:   */
/*                                    *ALL - all users.             */
/*                                    *CURRENT - list spooled files */
/*                                     for the current user only.   */
/*                                    *CURRENT is the default.      */
/*                                                                  */
/*        CWBOBJ_KEY_OUTQUELIB     - Specifies which libraries to   */
/*                                   search for output queues in.   */
/*                                   May be a specific name or      */
/*                                   one of these special values:   */
/*                                    "" - if the OUTQUEUE key word */
/*                                     is *ALL, this combination    */
/*                                     will search all output queues*/
/*                                     on the system.               */
/*                                    *CURLIB - the current library */
/*                                    *LIBL   - the library list    */
/*                                    *LIBL is the default if the   */
/*                                     OUTQUE filter is not *ALL.   */
/*                                   "" is the default if the OUTQUE*/
/*                                    filter is set to *ALL.        */
/*                                                                  */
/*        CWBOBJ_KEY_OUTQUE        - Specifies which output queues  */
/*                                   to search for spooled files on.*/
/*                                   May be a specific name or the  */
/*                                   special value *ALL.            */
/*                                   *ALL is the default.           */
/*                                                                  */
/*        CWBOBJ_KEY_FORMTYPE      - Specifies which spooled files  */
/*                                   are listed by the form type    */
/*                                   attribute that they have.  May */
/*                                   be a specific name or one of   */
/*                                   these special values:          */
/*                                    *ALL - spooled files with any */
/*                                     form type are listed.        */
/*                                    *STD - spooled files with the */
/*                                     form type of *STD are listed.*/
/*                                    *ALL is the default.          */
/*                                                                  */
/*        CWBOBJ_KEY_USERDATA      - Specifies which spooled files  */
/*                                   are listed by the user data    */
/*                                   that they have.  May be a      */
/*                                   specific value or one of these */
/*                                   special values:                */
/*                                    *ALL - spooled files with any */
/*                                     user data value are listed.  */
/*                                    *ALL is the default.          */
/*                                                                  */
/* Output Queue Lists:                                              */
/*  CWBOBJ_LIST_OUTQ:                                               */
/*        CWBOBJ_KEY_OUTQUELIB     - Specifies which libraries to   */
/*                                   search for output queues in.   */
/*                                   May be a specific name, a      */
/*                                   generic name or any of these   */
/*                                   special values:                */
/*                                    *ALL - all libraries          */
/*                                    *ALLUSR - all user-defined    */
/*                                     libraries, plus libraries    */
/*                                     containing user data and     */
/*                                     having names starting with Q.*/
/*                                    *CURLIB - the current library */
/*                                    *LIBL   - the library list    */
/*                                    *USRLIBL - the user portion of*/
/*                                      the library list.           */
/*                                    *LIBL is the default.         */
/*                                                                  */
/*        CWBOBJ_KEY_OUTQUE        - Specifies which output queues  */
/*                                   to list.  May be a specific    */
/*                                   name, a generic name or *ALL.  */
/*                                    *ALL is the default.          */
/*                                                                  */
/* Printer Device Description Lists:                                */
/*  CWBOBJ_LIST_PRTD:                                               */
/*        CWBOBJ_KEY_PRINTER       - Specifies which printer devices*/
/*                                   to list.  May be a specific    */
/*                                   name, a generic name or *ALL.  */
/*                                   *ALL is the default.           */
/*                                                                  */
/* Printer File Lists:                                              */
/*  CWBOBJ_LIST_PRTF:                                               */
/*        CWBOBJ_KEY_PRTRFILELIB   - Specifies which libraries to   */
/*                                   search for printer files in.   */
/*                                   May be a specific name, a      */
/*                                   generic name or any of these   */
/*                                   special values:                */
/*                                    *ALL - all libraries          */
/*                                    *ALLUSR - all user-defined    */
/*                                     libraries, plus libraries    */
/*                                     containing user data and     */
/*                                     having names starting with Q.*/
/*                                    *CURLIB - the current library */
/*                                    *LIBL  - the library list     */
/*                                    *USRLIBL - the user portion of*/
/*                                      the library list.           */
/*                                   *ALL is the default.           */
/*                                                                  */
/*        CWBOBJ_KEY_PRTRFILE      - Specifies which printer files  */
/*                                   to list.  May be a specific    */
/*                                   name, a generic name or *ALL.  */
/*                                   *ALL is the default.           */
/*                                                                  */
/* Writer Job Lists:                                                */
/*  CWBOBJ_LIST_WTR:               default value:                   */
/*        CWBOBJ_KEY_WRITER        - Specifies which writer jobs    */
/*                                   to list.  May be a specific    */
/*                                   name, a generic name or *ALL.  */
/*                                   *ALL is the default.           */
/*                                                                  */
/*        CWBOBJ_KEY_OUTQUELIB     - These filters are used together*/
/*        CWBOBJ_KEY_OUTQUE          to get a list of writers active*/
/*                                   to a particular output queue.  */
/*                                   If the OUTQUE key is specified,*/
/*                                   the WRITER key is ignored.     */
/*                                   (all writers for the specified */
/*                                   output queue are listed).      */
/*                                   If the OUTQUE key is specified */
/*                                   and the OUTQUELIB isn't, the   */
/*                                   OUTQUEULIB will default to     */
/*                                   *LIBL - the system library list*/
/*                                   The default is for neither     */
/*                                   of these to be specified.      */
/*                                                                  */
/* Library Lists:                                                   */
/*  CWBOBJ_LIST_LIB:                                                */
/*        CWBOBJ_KEY_LIBRARY       - Specifies which libraries to   */
/*                                   list.  May be a specific name, */
/*                                   a generic name or any of these */
/*                                   special values:                */
/*                                    *ALL - all libraries          */
/*                                    *CURLIB - the current library */
/*                                    *LIBL  - the library list     */
/*                                    *USRLIBL - the user portion of*/
/*                                      the library list.           */
/*                                   *USRLIBL is the default.       */
/*                                                                  */
/*  CWBOBJ_LIST_RSC:                                                */
/*    Resources can be listed in a spooled file (list all of the    */
/*    external AFP resources used by this spooled file) or in a     */
/*    library or set of libraries.  To list resources for a spooled */
/*    file, use the cwbOBJ_SetListFilterWithSplF() API along with   */
/*    the SetListFilter API for the RSCTYPE and RSCNAME attributes. */
/*                                                                  */
/*        CWBOBJ_KEY_RSCLIB        - Specifies which libraries to   */
/*                                   search for resources in.       */
/*                                   This filter is ignored if the  */
/*                                   list is filtered by spooled    */
/*                                   file (ie.SetListFilterWithSplF)*/
/*                                   May be a specific name, a      */
/*                                   generic name or any of these   */
/*                                   special values:                */
/*                                    *ALL - all libraries          */
/*                                    *ALLUSR - all user-defined    */
/*                                     libraries, plus libraries    */
/*                                     containing user data and     */
/*                                     having names starting with Q.*/
/*                                    *CURLIB - the current library */
/*                                    *LIBL   - the library list    */
/*                                    *USRLIBL - the user portion of*/
/*                                      the library list.           */
/*                                    *LIBL is the default.         */
/*                                                                  */
/*        CWBOBJ_KEY_RSCNAME       - Specifies which resources to   */
/*                                   list by name.  May be a        */
/*                                   specific name, a generic name  */
/*                                   or *ALL.                       */
/*                                   *ALL is the default.           */
/*                                                                  */
/*        CWBOBJ_KEY_RSCTYPE       - Specifies which type of        */
/*                                   resources to list.  May be any */
/*                                   combination of the following   */
/*                                   bits logically OR'd together:  */
/*                                    CWBOBJ_AFPRSC_FONT            */
/*                                    CWBOBJ_AFPRSC_FORMDEF         */
/*                                    CWBOBJ_AFPRSC_OVERLAY         */
/*                                    CWBOBJ_AFPRSC_PAGESEG         */
/*                                    CWBOBJ_AFPRSC_PAGEDEF         */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY  cwbOBJ_SetListFilter(
                               cwbOBJ_ListHandle   listHandle,
                               cwbOBJ_KeyID        key,
                               const void         *value,
                               cwbSV_ErrHandle     errorHandle);
#endif   // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbOBJ_SetListFilterA(
                                      cwbOBJ_ListHandle   listHandle
                                    , cwbOBJ_KeyID        key
                                    , const void         *value
                                    , cwbSV_ErrHandle     errorHandle
                                           );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbOBJ_SetListFilterW(
                                      cwbOBJ_ListHandle   listHandle
                                    , cwbOBJ_KeyID        key
                                    , const void         *value
                                    , cwbSV_ErrHandle     errorHandle
                                           );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbOBJ_SetListFilter            cwbOBJ_SetListFilterW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbOBJ_SetListFilter            cwbOBJ_SetListFilterA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_SetListFilterWithSplF                                   */
/*                                                                  */
/* Purpose:                                                         */
/*    Sets filter for a list to a spooled file.   For listing       */
/*    resources this limits the resources returned by the openList  */
/*    to those used by the spooled file.                            */
/*                                                                  */
/* Parameters:                                                      */
/*                                                                  */
/*   cwbOBJ_ListHandle listHandle - input                           */
/*     List handle that this filter will be applied to.             */
/*                                                                  */
/*   cwbOBJ_ObjHandle splFHandle - input                            */
/*     Handle of the spooled file to filter on.                     */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWBOBJ_RC_INVALID_TYPE - Incorrect type of list                */
/*   CWB_INVALID_HANDLE - List handle not found or bad spooled file */
/*                          handle.                                 */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/*   Filtering by spooled file is used when listing AFP resources   */
/*   so the list type must be CWBOBJ_LIST_RSC.                      */
/*   If you filter resources based on a spooled file you cannot also*/
/*   filter based on a library or libraries.  The resource library  */
/*   filter will be ignored if both are specified.                  */
/*   Resetting a list filter will also reset the the spooled file   */
/*   filter to nothing.                                             */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_SetListFilterWithSplF(
                               cwbOBJ_ListHandle   listHandle,
                               cwbOBJ_ObjHandle    splFHandle,
                               cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_SetObjAttrs                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Change the attributes of the object on the server.             */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle objectHandle - input                          */
/*     Handle to the object that is to be changed.                  */
/*                                                                  */
/*   cwbOBJ_ParmHandle parmListHandle - input                       */
/*     Handle to the parameter object which contains the attributes */
/*     that are to be modified for the object.                      */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not an allocated object handle. */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*                                                                  */
/* Usage Notes:                                                     */
/*  The following objects allow these attributes to be changed:     */
/*                                                                  */
/*    CWBOBJ_LIST_SPLF (spooled files):                             */
/*       CWBOBJ_KEY_ALIGN       - Align page                        */
/*       CWBOBJ_KEY_BKOVRLLIB   - Back overlay library name         */
/*       CWBOBJ_KEY_BKOVRLAY    - Back overlay                      */
/*       CWBOBJ_KEY_BKOVL_ACR   - Back overlay offset across        */
/*       CWBOBJ_KEY_BKOVL_DWN   - Back overlay offset down          */
/*       CWBOBJ_KEY_COPIES      - Copies                            */
/*       CWBOBJ_KEY_ENDPAGE     - Ending page                       */
/*       CWBOBJ_KEY_FILESEP     - File separators                   */
/*       CWBOBJ_KEY_FORMFEED    - Form feed                         */
/*       CWBOBJ_KEY_FORMTYPE    - Form type                         */
/*       CWBOBJ_KEY_FTOVRLLIB   - Front overlay library name        */
/*       CWBOBJ_KEY_FTOVRLAY    - Front overlay                     */
/*       CWBOBJ_KEY_FTOVL_ACR   - Front overlay offset across       */
/*       CWBOBJ_KEY_FTOVL_DWN   - Front overlay offset down         */
/*       CWBOBJ_KEY_OUTPTY      - Output priority                   */
/*       CWBOBJ_KEY_OUTQUELIB   - Output queue library name         */
/*       CWBOBJ_KEY_OUTQUE      - Output queue                      */
/*       CWBOBJ_KEY_MULTIUP     - Logical number of pages per side  */
/*       CWBOBJ_KEY_FIDELITY    - Print fidelity                    */
/*       CWBOBJ_KEY_DUPLEX      - Print on both sides               */
/*       CWBOBJ_KEY_PRTQUALITY  - Print quality                     */
/*       CWBOBJ_KEY_PRTSEQUENCE - Print sequence                    */
/*       CWBOBJ_KEY_PRINTER     - Printer                           */
/*       CWBOBJ_KEY_RESTART     - Where to restart printing at      */
/*       CWBOBJ_KEY_SAVESPLF    - Save spooled file after printing  */
/*       CWBOBJ_KEY_SCHEDULE    - When spooled file available       */
/*       CWBOBJ_KEY_STARTPAGE   - Starting page                     */
/*       CWBOBJ_KEY_USERDATA    - User data                         */
/*       CWBOBJ_KEY_USRDFNDTA   - User defined data                 */
/*       CWBOBJ_KEY_USRDFNOPTS  - User defined options              */
/*       CWBOBJ_KEY_USRDFNOBJLIB- User defined object library       */
/*       CWBOBJ_KEY_USRDFNOBJ   - User defined object               */
/*       CWBOBJ_KEY_USRDFNOBJTYP- User defined object type          */
/*                                                                  */
/*    CWBOBJ_LIST_PRTF (printer files):                             */
/*       CWBOBJ_KEY_ALIGN       - Align page                        */
/*       CWBOBJ_KEY_BKMGN_ACR   - Back margin offset across         */
/*       CWBOBJ_KEY_BKMGN_DWN   - Back margin offset down           */
/*       CWBOBJ_KEY_BKOVRLLIB   - Back overlay library name         */
/*       CWBOBJ_KEY_BKOVRLAY    - Back overlay                      */
/*       CWBOBJ_KEY_BKOVL_ACR   - Back overlay offset across        */
/*       CWBOBJ_KEY_BKOVL_DWN   - Back overlay offset down          */
/*       CWBOBJ_KEY_CPI         - Characters Per Inch               */
/*       CWBOBJ_KEY_CODEPAGE    - Code page                         */
/*       CWBOBJ_KEY_CODEDFNTLIB - Coded font library name           */
/*       CWBOBJ_KEY_CODEDFNT    - Coded font name                   */
/*       CWBOBJ_KEY_COPIES      - Copies                            */
/*       CWBOBJ_KEY_DBCSDATA    - Contains DBCS Data                */
/*       CWBOBJ_KEY_DBCSEXTENSN - Process DBCS Extension characters */
/*       CWBOBJ_KEY_DBCSROTATE  - DBCS character rotation           */
/*       CWBOBJ_KEY_DBCSCPI     - DBCS CPI                          */
/*       CWBOBJ_KEY_DBCSSISO    - DBCS SO/SI spacing                */
/*       CWBOBJ_KEY_DFR_WRITE   - Defer writing                     */
/*       CWBOBJ_KEY_ENDPAGE     - Ending page                       */
/*       CWBOBJ_KEY_FILESEP     - File Separators(*FILE not allowed)*/
/*       CWBOBJ_KEY_FOLDREC     - Fold records                      */
/*       CWBOBJ_KEY_FONTID      - Font identifier                   */
/*       CWBOBJ_KEY_FORMFEED    - Form feed                         */
/*       CWBOBJ_KEY_FORMTYPE    - Form type                         */
/*       CWBOBJ_KEY_FTMGN_ACR   - Front margin offset across        */
/*       CWBOBJ_KEY_FTMGN_DWN   - Front margin offset down          */
/*       CWBOBJ_KEY_FTOVRLLIB   - Front overlay library name        */
/*       CWBOBJ_KEY_FTOVRLAY    - Front overlay                     */
/*       CWBOBJ_KEY_FTOVL_ACR   - Front overlay offset across       */
/*       CWBOBJ_KEY_FTOVL_DWN   - Front overlay offset down         */
/*       CWBOBJ_KEY_CHAR_ID     - Graphic character set ID          */
/*       CWBOBJ_KEY_JUSTIFY     - Hardware Justification            */
/*       CWBOBJ_KEY_HOLD        - Hold spooled file                 */
/*       CWBOBJ_KEY_LPI         - Lines per inch                    */
/*       CWBOBJ_KEY_MAXRECORDS  - Maximum spooled file records      */
/*       CWBOBJ_KEY_OUTPTY      - Output priority                   */
/*       CWBOBJ_KEY_OUTQUELIB   - Output queue library name         */
/*       CWBOBJ_KEY_OUTQUE      - Output queue                      */
/*       CWBOBJ_KEY_OVERFLOW    - Overflow line number              */
/*       CWBOBJ_KEY_PAGELEN     - Page Length                       */
/*       CWBOBJ_KEY_MEASMETHOD  - Measurement method                */
/*       CWBOBJ_KEY_PAGEWIDTH   - Page width                        */
/*       CWBOBJ_KEY_MULTIUP     - Logical number of pages per side  */
/*       CWBOBJ_KEY_POINTSIZE   - The default font's point size     */
/*       CWBOBJ_KEY_FIDELITY    - Print fidelity                    */
/*       CWBOBJ_KEY_DUPLEX      - Print on both sides               */
/*       CWBOBJ_KEY_PRTQUALITY  - Print quality                     */
/*       CWBOBJ_KEY_PRTTEXT     - Print text                        */
/*       CWBOBJ_KEY_PRINTER     - Printer                           */
/*       CWBOBJ_KEY_PRTDEVTYPE  - Printer Device Type               */
/*       CWBOBJ_KEY_RPLUNPRT    - Replace unprintable characters    */
/*       CWBOBJ_KEY_RPLCHAR     - Replacement character             */
/*       CWBOBJ_KEY_SAVESPLF    - Save spooled file after printing  */
/*       CWBOBJ_KEY_SRCDRWR     - Source drawer                     */
/*       CWBOBJ_KEY_SPOOL       - Spool the data                    */
/*       CWBOBJ_KEY_SCHEDULE    - When spooled file available       */
/*       CWBOBJ_KEY_STARTPAGE   - Starting page                     */
/*       CWBOBJ_KEY_DESCRIPTION - Text description                  */
/*       CWBOBJ_KEY_UNITOFMEAS  - Unit of measure                   */
/*       CWBOBJ_KEY_USERDATA    - User data                         */
/*       CWBOBJ_KEY_USRDFNDTA   - User defined data                 */
/*       CWBOBJ_KEY_USRDFNOPTS  - User defined options              */
/*       CWBOBJ_KEY_USRDFNOBJLIB- User defined object library       */
/*       CWBOBJ_KEY_USRDFNOBJ   - User defined object               */
/*       CWBOBJ_KEY_USRDFNOBJTYP- User defined object type          */
/*                                                                  */
/*    CWBOBJ_LIST_OUTQ (output queues):                             */
/*    CWBOBJ_LIST_PRTD (printer devices):                           */
/*    CWBOBJ_LIST_WTR (writers):                                    */
/*    CWBOBJ_LIST_LIB (libraries):                                  */
/*    CWBOBJ_LIST_RSC (afp resources)                               */
/*       NONE                                                       */
/*                                                                  */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbOBJ_SetObjAttrs(
                              cwbOBJ_ObjHandle     objectHandle,
                              cwbOBJ_ParmHandle    parmListHandle,
                              cwbSV_ErrHandle      errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_SetParameter                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Sets the value of a parameter in a parameter list object.      */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ParmHandle parmListHandle - input                       */
/*     Handle of the parameter object.                              */
/*                                                                  */
/*   cwbOBJ_KeyID key - input                                       */
/*     The id of the parameter to set.                              */
/*                                                                  */
/*   void *value - input                                            */
/*     The value to set the parameter to.  The type that value      */
/*     points to is determined by the value of key.                 */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory; may have failed   */
/*                           to allocate temporary buffer.          */
/*   CWB_INVALID_HANDLE - Handle is not a parameter object handle.  */
/*   CWB_NON_REPRESENTABLE_UNICODE_CHAR - One or more input UNICODE */
/*                                        characters have no        */
/*                                        representation in the     */
/*                                        codepage being used.      */
/*   CWB_API_ERROR - General API failure.                           */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY  cwbOBJ_SetParameter(
                               cwbOBJ_ParmHandle   parmListHandle,
                               cwbOBJ_KeyID        key,
                               const void         *value,
                               cwbSV_ErrHandle     errorHandle);
#endif   // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
UINT CWB_ENTRY cwbOBJ_SetParameterA(
                                 cwbOBJ_ParmHandle   parmListHandle
                               , cwbOBJ_KeyID        key
                               , const void         *value
                               , cwbSV_ErrHandle     errorHandle
                                          );
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
UINT CWB_ENTRY cwbOBJ_SetParameterW(
                                 cwbOBJ_ParmHandle   parmListHandle
                               , cwbOBJ_KeyID        key
                               , const void         *value
                               , cwbSV_ErrHandle     errorHandle
                                          );
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbOBJ_SetParameter             cwbOBJ_SetParameterW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbOBJ_SetParameter             cwbOBJ_SetParameterA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_StartWriter                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Starts an iSeries writer job.                                  */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle *printerHandle - input                        */
/*     Required.  A pointer to a valid printer object handle that   */
/*     identifies which printer this writer is to be started to.    */
/*                                                                  */
/*   cwbOBJ_ObjHandle *outputQueueHandle - input                    */
/*     Optional.  A pointer to a valid output queue object handle   */
/*     that identifies which output queue this writer is to be      */
/*     started from.                                                */
/*     If the parmListHandle is also specified and contains the     */
/*     CWBOBJ_KEY_OUTQUE parameter key, this parameter is ignored.  */
/*                                                                  */
/*   cwbOBJ_ParmHandle *parmListHandle - input                      */
/*     Optional.  A pointer to a valid parameter list object handle */
/*     that contains parameters for starting the writer.            */
/*                                                                  */
/*   cwbOBJ_ObjHandle *writerHandle - output                        */
/*     Optional.  A pointer to a writer object handle that will be  */
/*     filled in upon successful return from this API.              */
/*     If this parameter is specified, the caller must call         */
/*     cwbOBJ_DeleteObjHandle() to release resources allocated for  */
/*     this writer handle.                                          */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not valid.                      */
/*   CWB_INVALID_PARAMETER - Invalid parameter specified.           */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Calling this API causes the writer job to be submitted to run. */
/*   The writer job may fail to start even though this API returns  */
/*   successfully (the job may be successfully submitted, but fail  */
/*   to start).  This is the behavior of the STRPRTWTR command on   */
/*   the iSeries.                                                   */
/*                                                                  */
/*   The following parameter key's may be set in the parmListHandle */
/*   object:                                                        */
/*    CWBOBJ_KEY_ALIGN       - Align page                           */
/*    CWBOBJ_KEY_ALWDRTPRT   - Allow direct printing                */
/*    CWBOBJ_KEY_AUTOEND     - Automatically end writer (*YES,*NO)  */
/*    CWBOBJ_KEY_DRWRSEP     - Drawer to use for separators         */
/*    CWBOBJ_KEY_FILESEP     - Number of file separators            */
/*    CWBOBJ_KEY_FORMTYPE    - Name of the form to be used          */
/*    CWBOBJ_KEY_JOBNAME     - Name of the job that created file    */
/*    CWBOBJ_KEY_JOBNUMBER   - Number of the job that created file  */
/*    CWBOBJ_KEY_USER        - Name of the user that created file   */
/*    CWBOBJ_KEY_FORMTYPEMSG - Form type message option             */
/*    CWBOBJ_KEY_MSGQUELIB   - Message queue library                */
/*    CWBOBJ_KEY_MSGQUE      - Message queue name                   */
/*    CWBOBJ_KEY_OUTQUELIB   - Output queue library                 */
/*    CWBOBJ_KEY_OUTQUE      - Output queue                         */
/*    CWBOBJ_KEY_SPOOLFILE   - Spool file name                      */
/*    CWBOBJ_KEY_SPLFNUM     - Spool file number                    */
/*    CWBOBJ_KEY_WTRSTRPAGE  - Page to start the writer on          */
/*    CWBOBJ_KEY_WTREND      - When to end the writer               */
/*    CWBOBJ_KEY_WRITER      - Writer job name                      */
/*    CWBOBJ_KEY_WTRINIT     - When to initialize the printer device*/
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY  cwbOBJ_StartWriter(
                               cwbOBJ_ObjHandle   *printerHandle,
                               cwbOBJ_ObjHandle   *outputQueueHandle,
                               cwbOBJ_ParmHandle  *parmListHandle,
                               cwbOBJ_ObjHandle   *writerHandle,
                               cwbSV_ErrHandle     errorHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbOBJ_WriteNewSplF                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Writes data into a newly created spooled file.                 */
/*                                                                  */
/* Parameters:                                                      */
/*   cwbOBJ_ObjHandle newSplFHandle - input                         */
/*     New spooled file handle.  This is the handle passed back on  */
/*     the cwbOBJ_CreateNewSplF() API.                              */
/*                                                                  */
/*   const char *data - input                                       */
/*     Pointer to the data buffer that will be written into the     */
/*     spooled file.                                                */
/*                                                                  */
/*   unsigned long dataLen - input                                  */
/*     Length of the data to be written.                            */
/*                                                                  */
/*   cwbSV_ErrHandle errorHandle - output                           */
/*     Optional, may be 0.                                          */
/*     Any returned messages will be written to this object.        */
/*     It is created with the cwbSV_CreateErrHandle() API.          */
/*     The messages may be retrieved through the cwbSV_GetErrText() */
/*     API.  If the parameter is set to zero, no messages will be   */
/*     retrievable.                                                 */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_NO_ERROR - Successful completion.                          */
/*   CWB_NOT_ENOUGH_MEMORY - Insufficient memory.                   */
/*   CWB_INVALID_HANDLE - Handle is not valid spooled file handle.  */
/*   CWBOBJ_RC_HOST_ERROR - Host error occurred. Text may be in     */
/*                          errorHandle.                            */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbOBJ_WriteNewSplF(
                              cwbOBJ_ObjHandle     newSplFHandle,
                              const char          *data,
                              unsigned long        dataLen,
                              cwbSV_ErrHandle      errorHandle);




#ifdef __cplusplus
}
#endif

#endif /* _CWBOBJ_H_ */
