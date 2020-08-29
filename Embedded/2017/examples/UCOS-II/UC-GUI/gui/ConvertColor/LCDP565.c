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
File        : LCD565.C
Purpose     : Color conversion routines for emWin GSC
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "LCD_Protected.h"    /* inter modul definitions */

/*********************************************************************
*
*       LCD_FIXEDPALETTE == 565
*
*         2^16 = 65536 colors
*
**********************************************************************
*/

int LCD_Color2Index_565(LCD_COLOR Color) {
  int r,g,b;
  r = (Color>> (0+3))  &0x1f;
  g = (Color>> (8+2)) &0x3f;
  b = (Color>>(16+3)) &0x1f;
  return r+(g<<5)+(b<<11);
}

LCD_COLOR LCD_Index2Color_565(int Index) {
  unsigned int r,g,b;
  /* Seperate the color masks */
  r = Index & 0x1f;
  g = (Index>>5) & 0x3f;
  b = ((unsigned)Index >> 11) & 0x1f;
  /* Convert the color masks */
  r = r * 255 / 31;
  g = g * 255 / 63;
  b = b * 255 / 31;
  return r + (g<<8) + (((U32)b)<<16);
}



