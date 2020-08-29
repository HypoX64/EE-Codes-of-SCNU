/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 2002         SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

**** emWin/GSC Grafical user interface for embedded applications ****
emWin is protected by international copyright laws. Knowledge of the
source code may not be used to write a similar product. This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUI_MoveRect.c
Purpose     : Implementation of GUI_MoveRect
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.h"


/*********************************************************************
*
*                    GUI_MoveRect
*
***********************************************************************
*/

void GUI_MoveRect(GUI_RECT *pRect, int dx, int dy) {
  if (pRect) {
    pRect->x0 += dx;
    pRect->x1 += dx;
    pRect->y0 += dy;
    pRect->y1 += dy;
  }
}




