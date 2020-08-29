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
File        : GUI_GetClientRect.c
Purpose     : Core file for emWin GSC
---------------------------END-OF-HEADER------------------------------
*/


#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Private.H"
#include "GUIDebug.h"

/*********************************************************************
*
*            GUI_GetClientRect
*
**********************************************************************
*/

void GUI_GetClientRect   (GUI_RECT* pRect) {
  if (!pRect)
    return;
  #if GUI_WINSUPPORT
    WM_GetClientRect(pRect);
  #else
    pRect->x0 = 0;
    pRect->y0 = 0;
    pRect->x1 = LCD_GET_XSIZE();
    pRect->y1 = LCD_GET_YSIZE();
  #endif
}




