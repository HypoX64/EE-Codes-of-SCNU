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
File        : WM_Paint.c
Purpose     : Windows manager, add. module
----------------------------------------------------------------------
*/


#include <stddef.h>
#include "WM_Intern.H"

#if GUI_WINSUPPORT

/*
  ********************************************************************
  *                                                                  *
  *        Exported routines:  Paint                                 *
  *                                                                  *
  ********************************************************************
*/

void WM_Paint(WM_HWIN hObj) {
  WM_MESSAGE Msg;
  WM_SelectWindow(hObj);
  WM_ValidateWindow(hObj);
  WM_SetDefault();
  Msg.MsgId  = WM_PAINT;
  Msg.Data.p = NULL;
  WM_SendMessage(hObj, &Msg);
}

#else

void WM_Paint(void) {} /* avoid empty object files */

#endif /* GUI_WINSUPPORT */
