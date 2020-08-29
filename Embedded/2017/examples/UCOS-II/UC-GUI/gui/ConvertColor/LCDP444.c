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
File        : LCD444.C
Purpose     : Color conversion routines for LCD-drivers
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "LCD_Protected.h"    /* inter modul definitions */

/*********************************************************************
*
*       LCD_FIXEDPALETTE == 444
*
*         2^12 = 4096 colors
*
**********************************************************************
*/

int LCD_Color2Index_444(LCD_COLOR Color) {
  int r,g,b;
  r = (Color>>4)   &0xf;
  g = (Color>>12)  &0xf;
  b = (Color>>20)  &0xf;
  return r + (g << 4) + (b << 8);
}

LCD_COLOR LCD_Index2Color_444(int Index) {
  unsigned int r,g,b;
  /* Seperate the color masks */
  r = Index & 0xf;
  g = (Index >> 4) & 0xf;
  b = ((unsigned)Index >> 8) & 0xf;
  /* Convert the color masks */
  r = r * 17;
  g = g * 17;
  b = b * 17;
  return r + (g<<8) + (((U32)b)<<16);
}




