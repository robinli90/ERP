/********************************************************************/
/*                                                                  */
/* 5769-XE1                                                         */
/* (C) Copyright IBM Corp. 1995,1998                                */
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
/*   CWBAD.H                                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   The functions listed in this file can be used to access        */
/*   information concerning the Client Access Express product       */
/*   which is installed on the PC.                                  */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Link with CWBAPI.LIB import library.                           */
/*   This module is to be used in conjunction with CWBAD.DLL.       */
/*                                                                  */
/*   In addition to the return codes listed for APIs additional     */
/*   operating system specific return codes may also appear.  The   */
/*   precise meaning of these return codes can be found in the      */
/*   operating system manuals or relevant header files.             */
/*                                                                  */
/********************************************************************/

#if !defined( _CWBAD_H_ )
#define       _CWBAD_H_

#include <windows.h>
#include "cwb.h"
#include "cwbport.h"

#if defined( __cplusplus )
extern "C" {
#endif


/*------------------------------------------------------------------*/
/* Return values specific to APIs listed below                      */
/*------------------------------------------------------------------*/
#define CWBAD_START                         (CWB_LAST+1)

#define CWBAD_INVALID_COMPONENT_ID          (CWBAD_START+1)


/*------------------------------------------------------------------*/
/* Component IDs for cwbAD_IsComponentInstalled                     */
/*                                                                  */
/* Note: These do not change from release to release                */
/*------------------------------------------------------------------*/
// Express required programs
#define CWBAD_COMP_BASESUPPORT             (1)

// Express Optional Components
#define CWBAD_COMP_OPTIONAL_COMPS          (2)

// Directory Update
#define   CWBAD_COMP_DIRECTORYUPDATE       (3)

// Incoming Remote Command
#define   CWBAD_COMP_IRC                   (4)

// MAPI
#define   CWBAD_COMP_MAPI                  (5)

// Express Online User's Guide
#define   CWBAD_COMP_OUG                   (6)

// AS400 Operations Navigator
#define CWBAD_COMP_OPNAV                   (7)

// Data Access
#define CWBAD_COMP_DATA_ACCESS             (8)

// Data Transfer
#define   CWBAD_COMP_DATA_TRANSFER         (9)

// Data Transfer Base Support
#define     CWBAD_COMP_DT_BASESUPPORT      (10)

// Data Transfer Excel Add-in
#define     CWBAD_COMP_DT_EXCEL_ADDIN      (11)

// Data Transfer WK4 file support
#define     CWBAD_COMP_DT_WK4SUPPORT       (12)

// ODBC
#define CWBAD_COMP_ODBC                    (13)

// OLE DB Provider
#define CWBAD_COMP_OLEDB                   (14)

// AFP Workbench Viewer
#define CWBAD_COMP_AFP_VIEWER              (15)

// AS400 Java Toolbox
#define CWBAD_COMP_JAVA_TOOLBOX            (16)

// 5250 Display and Printer Emulator
#define CWBAD_COMP_PC5250                  (17)

// Printer Drivers
#define CWBAD_COMP_PRINTERDRIVERS          (18)

// AFP printer driver
#define   CWBAD_COMP_AFP_DRIVER            (19)

// SCS printer driver
#define   CWBAD_COMP_SCS_DRIVER            (20)

// AS400 Operations Console
#define CWBAD_COMP_OP_CONSOLE              (21)

// Client Access Express Toolkit
#define CWBAD_COMP_TOOLKIT                 (22)

// Headers, Libraries, and Documentation
#define   CWBAD_COMP_TOOLKIT_BASE          (23)

// Visual Basic Wizards
#define   CWBAD_COMP_TOOLKIT_VBW           (24)

// EZ Setup
#define   CWBAD_COMP_EZSETUP               (25)

// Client Access Express Toolkit Tools for Java
#define CWBAD_COMP_TOOLKIT_JAVA_TOOLS      (26)

// Screen Customizer Enabler (component has been removed)
#define CWBAD_COMP_SCREEN_CUSTOMIZER_ENABLER  (27)

// .NET Data Provider
#define CWBAD_COMP_MP                       (28)

// Operations Navigator Base Support
#define CWBAD_COMP_OPNAV_BASESUPPORT       (100)

// Operations Navigator Basic Operations
#define CWBAD_COMP_OPNAV_BASE_OPS          (101)

// Operations Navigator Job Management
#define CWBAD_COMP_OPNAV_JOB_MGMT          (102)

// Operations Navigator System Configuration
#define CWBAD_COMP_OPNAV_SYS_CFG           (103)

// Operations Navigator Networks
#define CWBAD_COMP_OPNAV_NETWORK           (104)

// Operations Navigator Security
#define CWBAD_COMP_OPNAV_SECURITY          (105)

// Operations Navigator Users and Groups
#define CWBAD_COMP_OPNAV_USERS_GROUPS      (106)

// Operations Navigator Database
#define CWBAD_COMP_OPNAV_DATABASE          (107)

// Operations Navigator Multimedia
#define CWBAD_COMP_OPNAV_MULTIMEDIA        (108)

// Operations Navigator Backup
#define CWBAD_COMP_OPNAV_BACKUP            (109)

// Operations Navigator Application Development
#define CWBAD_COMP_OPNAV_APP_DEV           (110)

// Operations Navigator Application Administration
#define CWBAD_COMP_OPNAV_APP_ADMIN         (111)

// Operations Navigator File Systems
#define CWBAD_COMP_OPNAV_FILE_SYSTEMS      (112)

// Operations Navigator Management Central
#define CWBAD_COMP_OPNAV_MGMT_CENTRAL      (113)

//V5R1 additions (through 118)
// OpNav Management Central - Commands
#define CWBAD_COMP_OPNAV_MGMT_COMMANDS     (114)

/// OpNav Management Central - Packages and Products
#define CWBAD_COMP_OPNAV_MGMT_PACK_PROD    (115)

// OpNav Management Central - Monitors
#define CWBAD_COMP_OPNAV_MGMT_MONITORS     (116)

// Operations Navigator Logical Systems
#define CWBAD_COMP_OPNAV_LOGICAL_SYS       (117)

// Operations Navigator Advanced Function Presentation
#define CWBAD_COMP_OPNAV_ADV_FUNC_PRES     (118)

// Operations Navigator Integrated Server Administration
#define CWBAD_COMP_OPNAV_INT_SRV_ADM       (119)

//5250 Display and Printer Emulator subcomponents
#define CWBAD_COMP_PC5250_BASE_KOREAN      (150)
#define CWBAD_COMP_PC5250_PDFPDT_KOREAN    (151)
#define CWBAD_COMP_PC5250_BASE_SIMPCHIN    (152)
#define CWBAD_COMP_PC5250_PDFPDT_SIMPCHIN  (153)
#define CWBAD_COMP_PC5250_BASE_TRADCHIN    (154)
#define CWBAD_COMP_PC5250_PDFPDT_TRADCHIN  (155)
#define CWBAD_COMP_PC5250_BASE_STANDARD    (156)
#define CWBAD_COMP_PC5250_PDFPDT_STANDARD  (157)
#define CWBAD_COMP_PC5250_FONT_ARABIC      (158)
#define CWBAD_COMP_PC5250_FONT_BALTIC      (159)
#define CWBAD_COMP_PC5250_FONT_LATIN2      (160)
#define CWBAD_COMP_PC5250_FONT_CYRILLIC    (161)
#define CWBAD_COMP_PC5250_FONT_GREEK       (162)
#define CWBAD_COMP_PC5250_FONT_HEBREW      (163)
#define CWBAD_COMP_PC5250_FONT_LAO         (164)
#define CWBAD_COMP_PC5250_FONT_THAI        (165)
#define CWBAD_COMP_PC5250_FONT_TURKISH     (166)
#define CWBAD_COMP_PC5250_FONT_VIET        (167)
#define CWBAD_COMP_PC5250_FONT_HINDI       (168)

// SSL
#define CWBAD_COMP_SSL                     (200)
#define CWBAD_COMP_SSL_128_BIT             (CWBAD_COMP_SSL)
#define CWBAD_COMP_SSL_56_BIT              (CWBAD_COMP_SSL)
#define CWBAD_COMP_SSL_40_BIT              (CWBAD_COMP_SSL)

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbAD_GetClientVersion                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Get the version of the Client Access product currently         */
/*   installed on the PC.                                           */
/*                                                                  */
/* Parameters:                                                      */
/*   unsigned long * version - output                               */
/*     Pointer to a buffer where the version level of the Client    */
/*     Access product is returned.                                  */
/*   unsigned long * release - output                               */
/*     Pointer to a buffer where the release level of the Client    */
/*     Access product is returned.                                  */
/*   unsigned long * modificationLevel - output                     */
/*     Pointer to a buffer where the modification level of the      */
/*     Client Access product is returned.                           */
/*                                                                  */
/* Return Codes:                                                    */
/*  The following list shows common return values.                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - One or more pointer parameters are NULL. */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbAD_GetClientVersion(
                                    unsigned long  *version,
                                    unsigned long  *release,
                                    unsigned long  *modificationLevel);


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbAD_GetProductFixLevel                                       */
/*                                                                  */
/* Purpose:                                                         */
/*   Returns the current Fix Level of Client Access                 */
/*                                                                  */
/* Parameters:                                                      */
/*   char * szBuffer - output                                       */
/*   unsigned long ulBufLen - input/output                          */
/*     Size of szBuffer, including space for the NULL terminator.   */
/*     On output, will contain the length of the fix level string,  */
/*     including the terminating NULL.                              */
/*                                                                  */
/* Return Codes:                                                    */
/*  The following list shows common return values.                  */
/*   CWB_OK                 - Successful completion                 */
/*   CWB_BUFFER_OVERFLOW    - Buffer overflow.  The required length */
/*                            is returned in ulBufLen.              */
/*   CWB_INVALID_POINTER    - One or more pointer parameters are    */
/*                            NULL.                                 */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Returns the fix level of the Client Access product.  Returns   */
/*   an empty string if fixes have not been applied.                */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbAD_GetProductFixLevel(
                                      char           *szBuffer,
                                      unsigned long  *ulBufLen);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbAD_GetProductFixLevelA(
                                      LPSTR           szBuffer,
                                      unsigned long  *ulBufLen);
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
unsigned int CWB_ENTRY cwbAD_GetProductFixLevelW(
                                      LPWSTR          szBuffer,
                                      unsigned long  *ulBufLen);
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbAD_GetProductFixLevel        cwbAD_GetProductFixLevelW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbAD_GetProductFixLevel        cwbAD_GetProductFixLevelA
#endif // of UNICODE/ANSI selection


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbAD_IsComponentInstalled                                     */
/*                                                                  */
/* Purpose:                                                         */
/*   Indicates whether or not a specific Client Access component    */
/*   is installed.                                                  */
/*                                                                  */
/* Parameters:                                                      */
/*   unsigned long ulComponentID - input                            */
/*     Must be set to one of the component ID's listed at the       */
/*     beginning of this file.                                      */
/*   cwb_Boolean * bIndicator - output                              */
/*     Will contain CWB_TRUE if the component is installed.         */
/*     Will return CWB_FALSE if the component is not installed.     */
/*     Will not be set if an error occurs.                          */
/*                                                                  */
/* Return Codes:                                                    */
/*  The following list shows common return values.                  */
/*   CWB_OK                   - Successful completion.              */
/*   CWB_INVALID_POINTER      - bIndicator is NULL.                 */
/*   CWB_INVALID_COMPONENT_ID - The component id is invalid for     */
/*                              this release.                       */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned long CWB_ENTRY cwbAD_IsComponentInstalled(
                                      unsigned long   ulComponentID,
                                      cwb_Boolean    *bIndicator);


/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbAD_IsOpNavPluginInstalled                                   */
/*                                                                  */
/* Purpose:                                                         */
/*   Indicates whether or not a specific Operations Navigator       */
/*   plug-in is installed.                                          */
/*                                                                  */
/* Parameters:                                                      */
/*   char * szPluginName - input                                    */
/*     Pointer to a null-terminated string containing the name of   */
/*     plug-in.                                                     */
/*   cwb_Boolean * bIndicator - output                              */
/*     Will contain CWB_TRUE if the component is installed.         */
/*     Will return CWB_FALSE if the component is not installed.     */
/*     Will not be set if an error occurs.                          */
/*                                                                  */
/* Return Codes:                                                    */
/*  The following list shows common return values.                  */
/*   CWB_OK - Successful completion.                                */
/*   CWB_INVALID_POINTER - One of the pointer parameters is NULL.   */
/*                                                                  */
/* Usage Notes:                                                     */
/*   If the return value is not CWB_OK, the value in bIndicator     */
/*   is meaningless.                                                */
/*                                                                  */
/********************************************************************/
#if !( defined(CWB_ANSI_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbAD_IsOpNavPluginInstalled(
                                      const char    *szPluginName,
                                      cwb_Boolean   *bIndicator);
#endif    // OEM-only selection

#if !( defined(CWB_OEM_ONLY) || defined(CWB_UNICODE_ONLY) )
unsigned int CWB_ENTRY cwbAD_IsOpNavPluginInstalledA(
                                      LPCSTR         szPluginName,
                                      cwb_Boolean   *bIndicator);
#endif   // ANSI-only selection

#if !( defined(CWB_ANSI_ONLY) || defined(CWB_OEM_ONLY) )
unsigned int CWB_ENTRY cwbAD_IsOpNavPluginInstalledW(
                                      LPCWSTR        szPluginName,
                                      cwb_Boolean   *bIndicator);
#endif   // UNICODE-only selection

// UNICODE/ANSI API selection
#if (  defined(CWB_UNICODE) && (!( defined(CWB_OEM) || defined(CWB_ANSI) ))  )
   #define  cwbAD_IsOpNavPluginInstalled        cwbAD_IsOpNavPluginInstalledW
#elif (  defined(CWB_ANSI) && (!( defined(CWB_OEM) || defined(CWB_UNICODE) ))  )
   #define  cwbAD_IsOpNavPluginInstalled        cwbAD_IsOpNavPluginInstalledA
#endif // of UNICODE/ANSI selection


#if defined( __cplusplus )
}
#endif


#endif
