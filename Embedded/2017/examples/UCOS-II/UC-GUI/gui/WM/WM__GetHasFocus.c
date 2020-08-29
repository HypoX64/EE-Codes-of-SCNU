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
File        : WM__GetHasFocus.c
Purpose     : Implementation of WM__GetHasFocus
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

/*********************************************************************
*
*       WM__GetHasFocus

  Return value:
    0    window does not have the focus
    1    window has focus
    -1   0 handle
*/
int WM__GetHasFocus(WM_HWIN hWin) {
  int r;
  WM_MESSAGE Msg;
  if (hWin) {
    Msg.MsgId  = WM_GET_HAS_FOCUS;
    Msg.Data.v = 0;
    WM__SendMessage(hWin, &Msg);
    r = Msg.Data.v;
  } else {
    r = -1;
  }
  return r;
}

#else
  void WM_GetHasFocus_C(void) {} /* avoid empty object files */
#endif
