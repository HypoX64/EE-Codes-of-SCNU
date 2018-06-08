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
File        : LCDP323.C
Purpose     : Color conversion routines for 323 mode
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "LCD_Protected.h"    /* inter modul definitions */

/*********************************************************************
*
*       LCD_FIXEDPALETTE == 323
*
*       256 colors     BBBGGRRR
*
**********************************************************************
*/

int LCD_Color2Index_323(LCD_COLOR Color) {
  int r, g, b;
  r = Color & 255;
  g = (Color >> 8 ) & 255;
  b = Color >> 16;
  r = (r * 7 + 127) / 255;
  g = (g + 42) / 85;
  b = (b * 7 + 127) / 255;
  return r + (g << 3) + (b << 5);
}

LCD_COLOR LCD_Index2Color_323(int Index) {
  int r, g, b;
  r = (Index & 7) * 255 / 7;
  g = ((Index >> 3) & 3) * 85;
  b = ((Index >> 5) & 7) * 255 / 7;
  return r + (g << 8) + (((U32)b) << 16);
}

