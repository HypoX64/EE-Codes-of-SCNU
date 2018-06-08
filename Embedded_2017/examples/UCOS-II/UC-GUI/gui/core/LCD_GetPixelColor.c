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
File        : LCD_GetPixelColor.c
Purpose     : Get Pixel routines
              Note: These routines are in a module of their own
                    because they are mostly not required to link
---------------------------END-OF-HEADER------------------------------
*/


#include "LCD.H"              /* interface definitions */
#include "LCD_Protected.h"    /* inter modul definitions */



/*********************************************************************
*
*           LCD_GetPixelColor
*
**********************************************************************
*/

LCD_COLOR LCD_GetPixelColor(int x, int y) {
  return LCD_Index2Color(LCD_GetPixelIndex(x,y));
}







