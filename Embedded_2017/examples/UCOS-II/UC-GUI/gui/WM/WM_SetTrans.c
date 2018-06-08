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
File        : WM_SetTrans.C
Purpose     : Windows manager, optional routines
----------------------------------------------------------------------
*/


#include "WM_Intern.H"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */
#include "GUIDebug.h"
#define WM_DEBUG_LEVEL 1

/*
  ********************************************************************
  *                                                                  *
  *           Manage transparency attributes                         *
  *                                                                  *
  ********************************************************************

*/
void WM_SetHasTrans(WM_HWIN hWin) {
  WM_Obj *pWin = WM_HANDLE2PTR(hWin);  
  /* First check if this is necessary at all */
  if (pWin->Status&WM_SF_HASTRANS)
    return;
  /* Set Transparency flag */
  pWin->Status |= WM_SF_HASTRANS;
  /* Mark content as invalid */
  WM_InvalidateWindow(hWin);
}

void WM_ClrHasTrans(WM_HWIN hWin) {
  WM_Obj *pWin = WM_HANDLE2PTR(hWin);  
/* First check if this is necessary at all */
  if ((pWin->Status&WM_SF_HASTRANS) ==0)
    return;
  pWin->Status &= ~WM_SF_HASTRANS;
  /* Mark content as invalid */
  WM_InvalidateWindow(hWin);
}

int WM_GetHasTrans(WM_HWIN hWin) {
  return WM_HANDLE2PTR(hWin)->Status &WM_SF_HASTRANS;
}

#else

void WM_SetTrans(void) {} /* avoid empty object files */

#endif /* WM_MAX_WINDOW */
