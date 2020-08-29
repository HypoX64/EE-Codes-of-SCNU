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
File        : WM_GetParent.c
Purpose     : Windows manager, add. module
----------------------------------------------------------------------
*/


#include "WM_Intern.H"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

/*******************************************************************
*
*         Public code
*
********************************************************************
*/

/*******************************************************************
*
*         WM_DialogItem

  Recursively scan window and its child windows until dialog item is
  found or all children have been scanned.
*/
WM_HWIN WM__GetDialogItem(WM_HWIN hWin, int Id) {
  WM_HWIN hi;
  WM_HWIN r =0;
  WM_Obj* pWin = WM_H2P(hWin);
  hi = pWin->hFirstChild;
  while (hi) {
    /* This windows Id matching ? */
    if (WM_GetId(hi) == Id)
      return hi;
    /* Any child windows Id matching ? */
    if ((r = WM__GetDialogItem(hi, Id)) != 0)
      break;
    hi = WM_HANDLE2PTR(hi)->hNext;
  }
  return r;
}

WM_HWIN WM_GetDialogItem(WM_HWIN hWin, int Id) {
  WM_HWIN r;
  WM_LOCK();
    r = WM__GetDialogItem(hWin, Id);
  WM_UNLOCK();
  return r;
}
#else                                       /* Avoid empty object files */
  void WM_DialogItem_C(void) {}
#endif /* WM_MAX_WINDOW */
