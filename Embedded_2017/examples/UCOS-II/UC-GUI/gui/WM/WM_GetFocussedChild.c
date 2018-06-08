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
File        : WM_GetFocussedChild.c
Purpose     : Implementation of WM_GetFocussedChild
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

WM_HWIN WM_GetFocussedChild(WM_HWIN hWin) {
  int r;
  WM_MESSAGE Msg;
  Msg.MsgId  = WM_GET_FOCUSSED_CHILD;
  Msg.hWin   = hWin;
  WM__SendMessage(hWin, &Msg);
  r = Msg.Data.v;
  return r;
}

#else
  void WM_GetFocussedChild_C(void) {} /* avoid empty object files */
#endif
