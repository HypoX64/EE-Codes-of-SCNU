/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              �C/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : WM_HasCaptured.c
Purpose     : Windows manager, add. module
----------------------------------------------------------------------
*/

#include "WM_Intern.H"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/


/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

int WM_HasCaptured(WM_HWIN hWin) {
  return hWin == WM__hCapture;
}

#else

void WM_HasCaptured_C(void) {} /* avoid empty object files */

#endif /* WM_MAX_WINDOW */
