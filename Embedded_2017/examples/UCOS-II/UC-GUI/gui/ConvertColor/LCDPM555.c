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
File        : LCD555.C
Purpose     : Color conversion routines for LCD-drivers
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "LCD_Protected.h"    /* inter modul definitions */

/*********************************************************************
*
*       LCD_FIXEDPALETTE == -555
*
*         2^15 = 32768 basic colors
*
**********************************************************************
*/

int LCD_Color2Index_M555(LCD_COLOR Color) {
  int r,g,b;
  r = (Color>>3)  &0x1f;
  g = (Color>>11) &0x1f;
  b = (Color>>19) &0x1f;
  return b+(g<<5)+(r<<10);
}

LCD_COLOR LCD_Index2Color_M555(int Index) {
  unsigned int r,g,b;
  /* Seperate the color masks */
  b = Index & 0x1f;
  g = (Index>>5) & 0x3f;
  r = ((unsigned)Index >> 11) & 0x1f;
  /* Convert the color masks */
  r = r * 255 / 31;
  g = g * 255 / 63;
  b = b * 255 / 31;
  return r + (g<<8) + (((U32)b)<<16);
}



