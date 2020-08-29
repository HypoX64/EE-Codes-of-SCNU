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
File        : GUI_SetDefault.c
Purpose     : Implementation of GUI_SetDefault for emWin GSC
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.H"

void GL_SetDefault(void) {
  GUI_SetBkColor(GUI_DEFAULT_BKCOLOR);
  GUI_SetColor  (GUI_DEFAULT_COLOR);
  GUI_SetPenSize(1);
  GUI_SetTextAlign(0);
  GUI_SetTextMode(0);
  GUI_SetDrawMode(0);
  GUI_SetFont(GUI_DEFAULT_FONT);
  GUI_SetLineStyle(GUI_LS_SOLID);
}

void GUI_SetDefault(void) {
  GUI_LOCK();
  GL_SetDefault();
  GUI_UNLOCK();
}


