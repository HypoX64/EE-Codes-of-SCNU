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
File        : WM_Hide.c
Purpose     : Windows manager, add. module
----------------------------------------------------------------------
*/

#include "WM_Intern.H"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */
#include "GUIDebug.h"
#define WM_DEBUG_LEVEL 1

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

static void _HideAllChildren(WM_HWIN hChild) {
  while (hChild) {
    WM_Obj* pChild = WM_HANDLE2PTR(hChild);
    WM_HWIN hNext = pChild->hNext;
    WM_HideWindow(hChild);
    hChild = hNext;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

void WM_HideWindow(WM_HWIN hWin) {
  if (hWin) {
    WM_Obj *pWin = WM_HANDLE2PTR(hWin);  
    /* First check if this is necessary at all */
    if ((pWin->Status&WM_SF_ISVIS) ==0)
      return;
    /* Clear Visibility flag */
    pWin->Status &= ~WM_SF_ISVIS;
    /* Mark content as invalid */
    WM__InvalidateAreaBelow(&WM_HANDLE2PTR(hWin)->Rect, hWin);
    _HideAllChildren(pWin->hFirstChild);
  }
}

#else

void WM_Hide(void) {} /* avoid empty object files */

#endif /* WM_MAX_WINDOW */
