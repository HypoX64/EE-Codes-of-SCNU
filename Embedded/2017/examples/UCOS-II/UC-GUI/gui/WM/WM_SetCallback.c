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
File        : WM_SetCallback.C
Purpose     : Windows manager, add. module
----------------------------------------------------------------------
*/


#include "WM_Intern.H"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */
#include "GUIDebug.h"
#define WM_DEBUG_LEVEL 1


/*
  ********************************************************************
  *
  *        Exported routines:  Set callback
  *
  ********************************************************************
*/

WM_CALLBACK* WM_SetCallback (WM_HWIN Win, WM_CALLBACK* cb) {
  WM_CALLBACK* r;  
  WM_LOCK(); {
    WM_Obj* pWin = WM_HANDLE2PTR(Win);
    if (pWin) {
      r = pWin->cb;
      pWin->cb = cb; 
    }
  } WM_UNLOCK();
  return r;
}

#else

void WM_SetCallBack(void) {} /* avoid empty object files */

#endif /* WM_MAX_WINDOW */
