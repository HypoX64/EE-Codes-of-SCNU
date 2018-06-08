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
File        : WM_SetUserClipArea.c
Purpose     : Windows manager, add. module
----------------------------------------------------------------------
*/

#include "WM_Intern.H"

#if GUI_WINSUPPORT

/*
  ********************************************************************
  *                                                                  *
  *                    Reduce clipping area                          *
  *                                                                  *
  ********************************************************************
*/

const GUI_RECT* WM_SetUserClipRect(const GUI_RECT* pRect) {
  const GUI_RECT* pRectReturn;
  GUI_RECT r;
  WM_Obj* pAWin;
  WM_LOCK();
  pRectReturn = GUI_Context.WM__pUserClipRect;
  GUI_Context.WM__pUserClipRect = pRect;
/* Activate it ... */
  if (pRect) {
    r = *pRect;
    pAWin = WM_HANDLE2PTR(GUI_Context.hAWin);
    WM__Client2Screen(pAWin, &r);
    LCD_SetClipRectEx(&r);
  } else {
    WM_GetWindowRect(&r);
    LCD_SetClipRectEx(&r);
  }
  WM_UNLOCK();
  return pRectReturn;
}

#else

void WM_SetUserClipRect(void) {} /* avoid empty object files */

#endif
