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
File        : WM_SetFocus.c
Purpose     : Implementation of WM_SetFocus
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
*       WM__SetFocus

  Sets the focus to the specified child. It sends 2 messages:

    WM_SET_FOCUS(1) to window to receive focus
    WM_SET_FOCUS(0) to window to lose focus

  Return value:
    0    on success (Focus could be set)
    !=0  on failure (Windows could not take the focus)
*/
int WM_SetFocus(WM_HWIN hWin) {
  int r;
  WM_MESSAGE Msg;
  WM_LOCK();
  if ((hWin) && (hWin != WM__hWinFocus)) {
    Msg.MsgId  = WM_SET_FOCUS;
    /* Send a "no more foucs" message to window losing focus */
    Msg.Data.v = 0;
    WM_SendMessage(WM__hWinFocus, &Msg);
    /* Send "You have the focus now" message to the window */
    Msg.Data.v = 1;
    WM_SendMessage(WM__hWinFocus = hWin, &Msg);
    r = Msg.Data.v;
  } else {
    r = 1;
  }
  WM_UNLOCK();
  return r;
}

#else
  void WM_SetFocus_C(void) {} /* avoid empty object files */
#endif
