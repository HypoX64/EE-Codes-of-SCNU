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
File        : WM_BringToTop.c
Purpose     : Windows manager routine
----------------------------------------------------------------------
*/


#include "WM_Intern.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */




/*********************************************************************
*
*                Pull window in foreground (top of stack)
*
**********************************************************************
*/
void WM_BringToTop(WM_HWIN hWin) {
  WM_HWIN hPrev, hLast;
  WM_Obj* pWin;
  WM_Obj* pLast;
  if (hWin) {
    WM_LOCK();
    pWin = WM_H2P(hWin);
  /* First of all check if window is already top of stack */
    if (pWin->hNext && pWin->hParent) {
      /* unlink hWin */
      if ((hPrev = WM__GetPrevSibling(hWin)) != 0) {
        WM_Obj* pPrev;
        pPrev = WM_H2P(hPrev);
        pPrev->hNext = pWin->hNext;
      } else {
        WM_Obj* pParent;
        pParent= WM_H2P(pWin->hParent);
        pParent->hFirstChild = pWin->hNext;
      }
      /* Link last sibling */
      hLast = WM__GetLastSibling(hWin);
      pLast = WM_H2P(hLast);
      pLast->hNext = hWin;
      pWin->hNext = 0;
      /* Send message in order to make sure top window will be drawn */
      WM_InvalidateArea(&pWin->Rect);     /* Invalidate new area */
    }
    WM_UNLOCK();
  }
}

#else

void WM_BringToTop_c(void) {} /* avoid empty object files */

#endif /* WM_MAX_WINDOW */
