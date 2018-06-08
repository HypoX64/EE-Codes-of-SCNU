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
File        : LCD222.C
Purpose     : Color conversion routines for 222 mode
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "LCD.H"		          /* interface definitions */
#include "LCD_Protected.h"    /* inter modul definitions */

/*********************************************************************
*
*       LCD_FIXEDPALETTE == 222
*
*       64 colors
*
**********************************************************************
*/

int LCD_Color2Index_222(LCD_COLOR Color) {
  int r,g,b;
  r = ((Color&255)      +0x2a)/0x55;
  g = (((Color>>8)&255) +0x2a)/0x55;
  b = (((Color>>16)&255)+0x2a)/0x55;
  return r+(g<<2)+(b<<4);
}

LCD_COLOR LCD_Index2Color_222(int Index) {
  U16P r,g,b;
  r = ((Index>>0)&3)*0x55;
  g = ((Index>>2)&3)*0x55;
  b = (Index>>4)    *0x55;
  return (((U32)b)<<16)|(g<<8)|r;
}

/*********************************************************************
*
*       LCD_FIXEDPALETTE == 222, Red/Blue swapped
*
*       64 colors
*
**********************************************************************
*/

int LCD_Color2Index_M222(LCD_COLOR Color) {
  int r,g,b;
  r = ((Color&255)      +0x2a)/0x55;
  g = (((Color>>8)&255) +0x2a)/0x55;
  b = (((Color>>16)&255)+0x2a)/0x55;
  return b+(g<<2)+(r<<4);
}

LCD_COLOR LCD_Index2Color_M222(int Index) {
  U16P r,g,b;
  r = ((Index>>0)&3)*0x55;
  g = ((Index>>2)&3)*0x55;
  b = (Index>>4)    *0x55;
  return (((U32)r)<<16)|(g<<8)|b;
}
