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
File        : GUI_SetPhysColor.c
Purpose     : Implementation of GUI_SetPhysColor
---------------------------END-OF-HEADER------------------------------
*/


#include "GUI_Protected.H"
#include "LCD_ConfDefaults.h"


/*********************************************************************
*
*      Public code
*
**********************************************************************
*/

void GUI_SetPhysColor(U8 Pos, LCD_COLOR Color) {
  #if LCD_PHYSCOLORS_IN_RAM
    GUI_LOCK();
    LCD_PhysColors[Pos] = Color;
    LCD_SetLUTEntry(Pos, Color);
    GUI_UNLOCK();
  #else
    GUI_USE_PARA(Pos);
    GUI_USE_PARA(Color);
  #endif
}





