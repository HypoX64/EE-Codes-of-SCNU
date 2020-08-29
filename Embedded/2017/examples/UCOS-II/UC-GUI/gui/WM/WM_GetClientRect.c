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
File        : WM_GetClientRect.c
Purpose     : Windows manager, submodule
----------------------------------------------------------------------
*/


#include "WM_Intern.H"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

/*******************************************************************
*
*                    WM_GetClientRect
*
********************************************************************

Purpose:
  Return the client rectangle in client coordinates.
  This means for all windows that
  x0 = y0 = 0
  x1 = width - 1
  y1 = height - 1

*/

        
void WM_GetClientRect   (GUI_RECT* pRect) {
  WM_Obj *pWin;
  WM_LOCK();
  if (pRect) {
    pWin = WM_HANDLE2PTR(GUI_Context.hAWin);  
    pRect->y0 = pRect->x0 = 0;
    pRect->x1 = pWin->Rect.x1 - pWin->Rect.x0;
    pRect->y1 = pWin->Rect.y1 - pWin->Rect.y0;
  }
  WM_UNLOCK();
}

#else

void WM_GetClientRect_Dummy(void) {} /* avoid empty object files */

#endif /* WM_MAX_WINDOW */
