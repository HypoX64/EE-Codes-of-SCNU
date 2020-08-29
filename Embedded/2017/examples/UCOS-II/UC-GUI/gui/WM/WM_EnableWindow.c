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
File        : WM_EnableWindow.c
Purpose     : Implementation of WM_EnableWindow, WM_DisableWindow
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

*/
void WM_EnableWindow(WM_HWIN hWin) {
  WM_MESSAGE Msg;
  Msg.MsgId = WM_SET_ENABLE;
  Msg.Data.v = 1;
  WM_SendMessage(hWin, &Msg);
}

void WM_DisableWindow(WM_HWIN hWin) {
  WM_MESSAGE Msg;
  Msg.MsgId  = WM_SET_ENABLE;
  Msg.Data.v = 0;
  WM_SendMessage(hWin, &Msg);
}

void WM_SetEnableState(WM_HWIN hItem, int State) {
  if (State) {
    WM_EnableWindow(hItem);
  } else {
    WM_DisableWindow(hItem);
  }
}

#else
  void WM_EnableWindow_C(void) {} /* avoid empty object files */
#endif
