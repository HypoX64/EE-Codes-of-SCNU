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
File        : LCD4.C
Purpose     : Color conversion routines for 4 bpp gray LCDs
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include "LCD_Protected.h"    /* inter modul definitions */

/*********************************************************************
*
*       LCD_FIXEDPALETTE == 4
*
*       16 gray scales
*
**********************************************************************
*/

int LCD_Color2Index_4(LCD_COLOR Color) {
  int r,g,b;
  r = (Color>>(0+4))  &15;
  g = (Color>>(8+4))  &15;
  b = (Color>>(16+4)) &15;
  return (r+g+b+1) /3;
}

LCD_COLOR LCD_Index2Color_4(int Index) {
  return ((U32)Index)*0x111111;
}

