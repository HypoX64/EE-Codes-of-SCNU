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
File        : GUI_DrawRectEx.C
Purpose     : Implementation of GUI_DrawRectEx
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.H"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/


void GUI_DrawRectEx(const GUI_RECT* pRect) {
  GUI_DrawRect(pRect->x0, pRect->y0, pRect->x1, pRect->y1);
}






