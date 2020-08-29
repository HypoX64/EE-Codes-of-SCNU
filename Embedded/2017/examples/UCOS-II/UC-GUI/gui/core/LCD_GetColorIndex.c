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
File        : LCD_GetColorIndex.c
Purpose     : Implementation of different LCD_GetColorIndex routines
---------------------------END-OF-HEADER------------------------------
*/


#include "LCD_Private.h"
#include "GUI_Protected.h"


int LCD_GetBkColorIndex (void) {
  return LCD_BKCOLORINDEX;
}

int LCD_GetColorIndex (void) {
  return LCD_COLORINDEX;
}



