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
File        : WM_Screen2hWin.c
Purpose     : Windows manager, add. module
----------------------------------------------------------------------
*/

#include "WM_Intern.H"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

/*******************************************************************
*
*         Static code
*
********************************************************************
*/
static int _CheckHit(WM_Obj * pWin, int x, int y) {
  if (   (pWin->Status & WM_SF_ISVIS)
      && (x >= pWin->Rect.x0)
      && (x <= pWin->Rect.x1)
      && (y >= pWin->Rect.y0)
      && (y <= pWin->Rect.y1))
  {
    return 1;
  }
  return 0;
}

/*******************************************************************
*
*         _Screen2hWin

  This routine is recursive.
  It checks if the given coordinates are in the window or a decendant.
  Returns:
  0:   If coordinates are neither in the given window nor a decendent
  !=0  Handle of the topmost visible decendent in which the given
       coordinate falls.

*/
static WM_HWIN _Screen2hWin(WM_HWIN hWin, int x, int y) {
  WM_Obj* pWin = WM_HANDLE2PTR(hWin);
  WM_HWIN hChild, hHit;
  /* First check if the  coordinates are in the given window. If not, return 0 */
  if (_CheckHit(pWin, x, y) == 0) {
    return 0;
  }
  /* If the coordinates are in a child, search deeper ... */
  for (hChild = pWin->hFirstChild; hChild; ) {
    WM_Obj* pChild = WM_HANDLE2PTR(hChild);
    if ((hHit = _Screen2hWin(hChild, x, y)) != 0) {
      hWin = hHit;        /* Found a window */
    }
    hChild = pChild->hNext;
  }
  return hWin;            /* No Child affected ... The parent is the right one */
}

/*******************************************************************
*
*         Public code
*
********************************************************************
*/

WM_HWIN WM_Screen2hWin(int x, int y) {
  WM_HWIN r;
  WM_LOCK();
  r = _Screen2hWin(WM__FirstWin, x, y);
  WM_UNLOCK();
  return r;
}

#else                                       /* Avoid empty object files */
  void WM_Screen2Win(void) {}
#endif /* WM_MAX_WINDOW */
