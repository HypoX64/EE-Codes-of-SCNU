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
File        : WM_Move.C
Purpose     : Windows manager, add. module
----------------------------------------------------------------------
*/


#include "WM_Intern.H"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

static void _MoveAllChildren(WM_HWIN hChild, int dx, int dy) {
  while (hChild) {
    WM_Obj* pChild = WM_HANDLE2PTR(hChild);
    WM__MoveWindow(hChild, dx, dy);
    hChild = pChild->hNext;
  }
}

/*********************************************************************
*
*       Public module internal code
*
**********************************************************************
*/
void WM__MoveWindow(WM_HWIN hWin, int dx, int dy) {
  GUI_RECT r;
  WM_Obj* pWin;
  pWin = WM_HANDLE2PTR(hWin);
  r = pWin->Rect;
  GUI_MoveRect(&pWin->Rect, dx, dy);
  /* Invalidate old and new area ... */
  if (pWin->Status & WM_SF_ISVIS) {
    WM_InvalidateArea(&pWin->Rect);     /* Invalidate new area */
    WM_InvalidateArea(&r)         ;     /* Invalidate old area */
  }
  WM__SendMsgNoData(hWin, WM_MOVE); /* Notify window it has been moved */
  _MoveAllChildren(pWin->hFirstChild, dx, dy);  /* Children need to be moved along ...*/
}

void WM__MoveTo(WM_HWIN hWin, int x, int y) {
  WM_Obj* pWin = WM_HANDLE2PTR(hWin);
  x -= pWin->Rect.x0;
  y -= pWin->Rect.y0;
  WM__MoveWindow(hWin, x, y);
}

/*********************************************************************
*
*       Public API code
*
**********************************************************************
*/

void WM_MoveWindow(WM_HWIN hWin, int dx, int dy) {
  WM_LOCK(); {
    WM__MoveWindow(hWin, dx, dy);
  } WM_UNLOCK();
}


void WM_MoveTo(WM_HWIN hWin, int x, int y) {
  WM_LOCK(); {
    WM__MoveTo(hWin, x, y);
  } WM_UNLOCK();
}

#else

void WM_Move_c(void) {} /* avoid empty object files */

#endif /* WM_MAX_WINDOW */
