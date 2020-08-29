/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              µC/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : WM_SetDesktopColor.c
Purpose     : Windows manager, add. module
----------------------------------------------------------------------
*/


#include "WM_Intern.H"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */


/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

GUI_COLOR WM_SetDesktopColor(GUI_COLOR Color) {
  GUI_COLOR r;
  r = WM__BkColor;
  WM__BkColor = Color;
  WM_InvalidateWindow(WM__FirstWin);
  return r;
}

#else

void WM_SetDesktopColor_c(void) {} /* avoid empty object files */

#endif /* WM_MAX_WINDOW */
