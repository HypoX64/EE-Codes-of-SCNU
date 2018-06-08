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
File        : WM_GetClientWindow.c
Purpose     : Implementation of WM_GetClientWindow
----------------------------------------------------------------------
*/


#include "WM_Intern.H"

#if GUI_WINSUPPORT

/*******************************************************************
*
*        Public code
*
********************************************************************
*/

WM_HWIN WM_GetClientWindow(WM_HWIN hObj) {
  WM_MESSAGE Msg;
  Msg.MsgId  = WM_GET_CLIENT_WINDOW;
  WM_SendMessage(hObj, &Msg);
  return Msg.Data.v;

}

#else                            /* Avoid problems with empty object modules */
  void WM_GETCLIENTWINDOW_C(void) {}
#endif /* GUI_WINSUPPORT */
