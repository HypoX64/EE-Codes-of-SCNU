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
File        : WM_SetFocusOnNextChild.c
Purpose     : Implementation of WM_SetFocusOnNextChild
----------------------------------------------------------------------
*/

#include "WM_Intern.H"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

/*********************************************************************
*
*       static code
*
**********************************************************************
*/
static WM_HWIN _SetFocusOnNextChild(WM_HWIN hParent) {     /* Set the focus to the first child */
  WM_Obj* pParent = WM_HANDLE2PTR(hParent);
  WM_Obj* pi;
  WM_HWIN hChild  = WM_GetFocussedChild(hParent);
  WM_HWIN hi = hChild;
  if (pParent->hFirstChild == 0) {
    return 0;                                     /* "Parent" does not have a child ... */
  }
  do {
    if (hi == 0) {
      hi = pParent->hFirstChild;
    } else {
      pi = WM_HANDLE2PTR(hi);
      hi = pi->hNext;
    }
    if (hi == hChild) {
      break;                                      /* We have completed a round -- No other child to focus --- give up ! */
    }
    if (WM_SetFocus(hi)) {
      break;
    }
  } while (1);
  return hi;
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

/*********************************************************************
*
*       WM_SetFocusOnNextChild
*/


WM_HWIN WM_SetFocusOnNextChild(WM_HWIN hParent) {     /* Set the focus to the first child */
  WM_HWIN r;
  WM_LOCK();
    r = _SetFocusOnNextChild(hParent);
  WM_UNLOCK();
  return r;
}


#else
  void WM_SetFocusOnNextChild_C(void) {} /* avoid empty object files */
#endif
