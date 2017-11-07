/********************************************************************/
/*                                                                  */
/* 5722-XE1                                                         */
/* (C) Copyright IBM Corp. 1995,2003                                */
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
/*   cwbnldlg.h                                                     */
/*                                                                  */
/* Purpose:                                                         */
/*   Win/95 MRI Dialog Box Processing                               */
/*                                                                  */
/*   This module contains the routines necessary to replace the     */
/*   translatable text (caption and control names) within a         */
/*   dialog box.                                                    */
/*                                                                  */
/*   This module will also expand controls according to the         */
/*   text associated with them.  The size of the dialog box frame   */
/*   will also be adjusted.                                         */
/*                                                                  */
/*   cwbNL_CalcControlGrowthXY                                      */
/*   cwbNL_CalcDialogGrowthXY                                       */
/*   cwbNL_GrowControlXY                                            */
/*   cwbNL_GrowDialogXY                                             */
/*   cwbNL_LoadDialogStrings                                        */
/*   cwbNL_LoadMenu                                                 */
/*   cwbNL_LoadMenuStrings                                          */
/*   cwbNL_SizeDialog                                               */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Link with CWBAPI.LIB import library.                           */
/*   This module is to be used in conjunction with CWBNLDLG.DLL     */
/*                                                                  */
/* Disclaimer:                                                      */
/*   This module works ONLY on the following kinds of dialog box    */
/*   controls:  Static text, Button, Group box, Edit box, check box,*/
/*   and Radio button. It does NOT work on complex controls such as */
/*   Combo box.                                                     */
/*   This module works with ONLY a one level of menu.               */
/********************************************************************/

#if !defined(_CWBNLDLG_H_)
#define      _CWBNLDLG_H_

#include "cwb.h"

#if defined( __cplusplus )
 extern "C"
 {
#endif

#define CWBNLDLG_START CWB_LAST+1

#define CWBNL_DLG_MENU_LOAD_ERROR      CWBNLDLG_START+1
#define CWBNL_DLG_INVALID_HANDLE       CWBNLDLG_START+2

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbNL_CalcControlGrowthXY                                      */
/*                                                                  */
/* Purpose:                                                         */
/*   Routine to calculate the growth factor of an individual        */
/*   control within a dialog box.                                   */
/*                                                                  */
/* Parameters:                                                      */
/*   HWND windowHandle - Input                                      */
/*     Window handle of the control to calculate the growth         */
/*     factor for.                                                  */
/*                                                                  */
/*   HDC hDC - Input                                                */
/*     Device context. Used by GetTextExtentPoint32 to              */
/*     determine extent needed for the translated                   */
/*     string in the control.                                       */
/*                                                                  */
/*   float* growthFactorX - Output                                  */
/*     +/- growth to the width needed to contain the string         */
/*     for the control.                                             */
/*                                                                  */
/*   float* growthFactorY - Output                                  */
/*     +/- growth to the height needed to contain the string        */
/*     for the control.                                             */
/*                                                                  */
/* Return Codes:                                                    */
/*   Return value from Win/95 function calls.                       */
/*   CWB_OK - Successful Completion                                 */
/*                                                                  */
/* Usage Notes:                                                     */
/*   It is assumed that the translated text has been loaded into the*/
/*   control prior to calling this function.                        */
/*                                                                  */
/*   A control that does not contain text will return a 1.00        */
/*   growth factor.  This means that it does not need to change     */
/*   size.                                                          */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbNL_CalcControlGrowthXY(
                      HWND windowHandle,
                      HDC  hDC,
                      float* growthFactorX,
                                          float* growthFactorY);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbNL_CalcDialogGrowthXY                                         */
/*                                                                  */
/* Purpose:                                                         */
/*   Routine to calculate the growth factor of a dialog box.        */
/*   All of the controls within the dialog box will looked at to    */
/*   determine how much the dialog box size needs to be adjusted.   */
/*                                                                  */
/* Parameters:                                                      */
/*   HWND windowHandle - Input                                      */
/*     Window handle of the dialog box to calculate the growth      */
/*     factor for.                                                  */
/*                                                                  */
/*   float* growthFactorX - Output                                  */
/*     +/- growth to the width needed to contain the string         */
/*     for all of the controls in the dialog box.                   */
/*                                                                  */
/*   float* growthFactorY - Output                                  */
/*     +/- growth to the height needed to contain the string        */
/*     for all of the controls in the dialog box.                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   Return value from Win/95 function calls.                       */
/*   CWB_OK - Successful Completion                                 */
/*                                                                  */
/* Usage Notes:                                                     */
/*   It is assumed that the translated text has been loaded into the*/
/*   controls prior to calling this function.                       */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbNL_CalcDialogGrowthXY(
                      HWND windowHandle,
                      float* growthFactorX,
                                          float* growthFactorY);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbNL_GrowControlXY                                            */
/*                                                                  */
/* Purpose:                                                         */
/*   Routine to grow an individual control within a dialog box.     */
/*                                                                  */
/* Parameters:                                                      */
/*   HWND windowHandle - Input                                      */
/*     Window handle of the control to be resized.                  */
/*                                                                  */
/*   HWND parentWindowHandle - Input                                */
/*     Window handle of the dialog box that contains the controls.  */
/*                                                                  */
/*   float growthFactorX - Input                                    */
/*     Multiplication factor for growing the width of               */
/*     the control.                                                 */
/*       1.00 = Stay same size                                      */
/*       1.50 = 1 1/2 times original size                           */
/*                                                                  */
/*   float growthFactorY - Input                                    */
/*     Multiplication factor for growing the height of              */
/*     the control.                                                 */
/*       1.00 = Stay same size                                      */
/*       1.50 = 1 1/2 times original size                           */
/*                                                                  */
/*   cwb_Boolean growAllControls - Input                            */
/*     CWB_TRUE = All controls will be resized by the growthFactor  */
/*     CWB_FALSE = Only controls with text will be resized.         */
/*                                                                  */
/* Return Codes:                                                    */
/*   Return value from Win/95 function calls.                       */
/*   CWB_OK - Successful Completion                                 */
/*                                                                  */
/* Usage Notes:                                                     */
/*   Care should be used to not pass in a growth factor that will   */
/*   cause a control to not fit on the physical display.            */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbNL_GrowControlXY(
                             HWND        windowHandle,
                             HWND        parentWindowHandle,
                             float       growthFactorX,
                             float       growthFactorY,
                             cwb_Boolean growAllControls);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbNL_GrowDialogXY                                             */
/*                                                                  */
/* Purpose:                                                         */
/*   Internal routine to growth the dialog box and its controls     */
/*   proportionally based off of a growth factor that is input.     */
/*                                                                  */
/* Parameters:                                                      */
/*   HWND windowHandle - Input                                      */
/*     Window handle of the window owning the controls.             */
/*                                                                  */
/*   float growthFactorX - Input                                    */
/*     Multiplication factor for growing the dialog                 */
/*     box. ie.                                                     */
/*       1.00 = Stay same size                                      */
/*       1.50 = 1 1/2 times original size                           */
/*                                                                  */
/*   float growthFactorY - Input                                    */
/*     Multiplication factor for growing the dialog                 */
/*     box. ie.                                                     */
/*       1.00 = Stay same size                                      */
/*       1.50 = 1 1/2 times original size                           */
/*                                                                  */
/*   cwb_Boolean growAllControls - Input                            */
/*     CWB_TRUE = All controls will be resized by the growthFactor  */
/*     CWB_FALSE = Only controls with text will be resized.         */
/*                                                                  */
/* Return Codes:                                                    */
/*   Return value from Win/95 function calls.                       */
/*   CWB_OK - Successful Completion                                 */
/*                                                                  */
/* Usage Notes:                                                     */
/*   It is assumed that the translated text has been loaded into the*/
/*   controls prior to calling this function.                       */
/*                                                                  */
/*   The dialog box frame will not be allowed to grow larger than   */
/*   the desktop window size.                                       */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbNL_GrowDialogXY(
                             HWND        windowHandle,
                             float       growthFactorX,
                             float       growthFactorY,
                             cwb_Boolean growAllControls);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbNL_LoadDialogStrings                                        */
/*                                                                  */
/* Purpose:                                                         */
/*   This routine will control the replacement of translatable text */
/*   within a dialog box. This includes dialog control text as well */
/*   as the dialog box caption.                                     */
/*                                                                  */
/* Parameters:                                                      */
/*   HINSTANCE MRIHandle - Input                                    */
/*      Handle of the module containing the strings for the dialog. */
/*                                                                  */
/*   HWND windowHandle - Input                                      */
/*      Window handle of the dialog box.                            */
/*                                                                  */
/*   int nCaptionID - Input                                         */
/*       ID of the caption string for the dialog box                */
/*                                                                  */
/*   USHORT menuID - Input                                          */
/*      ID of the menu for the dialog box.                          */
/*                                                                  */
/*   HINSTANCE menuLibHandle - Input                                */
/*      Handle of the module containing the menu for the dialog.    */
/*                                                                  */
/*   cwb_Boolean growAllControls - Input                            */
/*      CWB_TRUE = All controls will be resized by the growthFactor */
/*      CWB_FALSE = Only controls with text will be resized.        */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful Completion                                 */
/*   CWBNL_DLG_MENU_LOAD_ERROR - Could not load the menu            */
/*   CWBNL_DLG_INVALID_HANDLE - Incorrect MRIHandle                 */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This process begins by enumerating, replacing the text of, and */
/*   horizontally adjusting all dialog controls within the dialog   */
/*   box and finally right-adjusting the dialog box itself, relative*/
/*   to the adjusted controls therein. These adjustments are made   */
/*   only if the current window extents do not fully encompass the  */
/*   expansion space required for the text or all controls.         */
/*                                                                  */
/*   After all of the text substitution has been completed, if a    */
/*   menu ID has been passed, it will be loaded and                 */
/*   attached to the dialog box.                                    */
/*                                                                  */
/*   It is suggested that this routine be called for every dialog   */
/*   box procedure as the first thing done during the INITDLG       */
/*   message processing.                                            */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbNL_LoadDialogStrings(
                             HINSTANCE   MRIHandle,
                             HWND        windowHandle,
                                                         int             nCaptionID,
                             USHORT      menuID,
                             HINSTANCE   menuLibHandle,
                             cwb_Boolean growAllControls);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbNL_LoadMenu                                                 */
/*                                                                  */
/* Purpose:                                                         */
/*   This routine will control the loading of the given menu from   */
/*   a module and replacing the translatable text within the menu.  */
/*                                                                  */
/* Parameters:                                                      */
/*   HWND    windowHandle - Input                                   */
/*      Window handle of the dialog box that contains the menu.     */
/*                                                                  */
/*   HINSTANCE menuResourceHandle - Input                           */
/*      Handle of the resource dll containing the menu.             */
/*                                                                  */
/*   USHORT  menuID - Input                                         */
/*      ID of the menu for the dialog box.                          */
/*                                                                  */
/*   HINSTANCE MRIHandle - Input                                    */
/*      Handle of the resource dll containing the strings for the       */
/*      menu.                                                       */
/*                                                                  */
/* Return Codes:                                                    */
/*   HINSTANCE - Handle of the menu.                                */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/*********************************************************************/
HWND CWB_ENTRY cwbNL_LoadMenu(
                     HWND    windowHandle,
                     HINSTANCE menuResourceHandle,
                     USHORT  menuID,
                     HINSTANCE MRIHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbNL_LoadMenuStrings                                          */
/*                                                                  */
/* Purpose:                                                         */
/*   This routine will control the replacement of translatable text */
/*   within a menu.                                                 */
/*                                                                  */
/* Parameters:                                                      */
/*   HWND    windowHandle - Input                                   */
/*      Window handle of the dialog box that contains the menu.     */
/*                                                                  */
/*   HMODULE menuHandle - Input                                     */
/*      Handle of the menu for the dialog.                          */
/*                                                                  */
/*   HMODULE MRIHandle - Input                                      */
/*      Handle of the resource dll containing the strings for           */
/*      the menu.                                                   */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*   CWB_OK - Successful Completion                                 */
/*                                                                  */
/* Usage Notes:                                                     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbNL_LoadMenuStrings(
                             HWND      WindowHandle,
                             HINSTANCE menuHandle,
                             HINSTANCE MRIHandle);

/********************************************************************/
/*                                                                  */
/* API:                                                             */
/*   cwbNL_SizeDialog                                               */
/*                                                                  */
/* Purpose:                                                         */
/*   This routine will control the sizing of the dialog box and     */
/*   its child controls. The expansion amount is based off of the   */
/*   length of the text extent and the length of each control. The  */
/*   growth of the dialog box and its controls will be proportional.*/
/*   By setting the growAllControls to FALSE, only controls with    */
/*   text will expand/contract. This allows the programmer the      */
/*   flexibility of non-translatable fields to remain the same size.*/
/*   This may make sense for dialogs that contain drop-down lists,  */
/*   combo-boxes, or spin buttons.                                  */
/*                                                                  */
/* Parameters:                                                      */
/*   HWND windowHandle - Input                                      */
/*     Window handle of the window owning the controls.             */
/*                                                                  */
/*   cwb_Boolean growAllControls - Input                            */
/*      CWB_TRUE = All controls will be resized by the growthFactor */
/*      CWB_FALSE = Only controls with text will be resized.        */
/*                                                                  */
/* Return Codes:                                                    */
/*   The following list shows common return values.                 */
/*                                                                  */
/*   CWB_OK - Successful Completion                                 */
/*                                                                  */
/* Usage Notes:                                                     */
/*   This routine assumes that the translated text has already been */
/*   loaded into the dialog box controls.  If the text has not been */
/*   loaded into the controls, you should use cwbNL_LoadDialog.     */
/*                                                                  */
/********************************************************************/
unsigned int CWB_ENTRY cwbNL_SizeDialog(
                             HWND        windowHandle,
                             cwb_Boolean growAllControls);

#if defined( __cplusplus )
 }
#endif

#endif /* _CWBNLDLG_H_ */
