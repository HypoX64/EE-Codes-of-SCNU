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
File        : WM_ResizeWindow.C
Purpose     : Windows manager, add. module
----------------------------------------------------------------------
*/

#include <stddef.h>
#include "WM_Intern.H"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */
#include "GUIDebug.h"
#define WM_DEBUG_LEVEL 1


/*
  ********************************************************************
  *
  *               Resize window
  *
  ********************************************************************
*/

void WM_ResizeWindow(WM_HWIN hWin, int dx, int dy) {
  GUI_RECT r;
  WM_LOCK();
  r = WM_HANDLE2PTR(hWin)->Rect;
  if (dx>0)
    r.x1+=dx;
  if (dy>0)
    r.y1+=dy;
  WM_HANDLE2PTR(hWin)->Rect.x1+=dx;
  WM_HANDLE2PTR(hWin)->Rect.y1+=dy;
  WM_InvalidateArea(&r);
/* Send size message to the window */
  WM__SendMsgNoData(hWin, WM_SIZE);
  WM_UNLOCK();
}

#else

void WM_ResizeWindow(void) {} /* avoid empty object files */

#endif /* WM_MAX_WINDOW */
