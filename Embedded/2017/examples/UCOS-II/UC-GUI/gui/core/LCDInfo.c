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
File        : LCDInfo.C
Purpose     : Routines returning info at runtime
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "LCD.H"	  	        /* interface definitions */
#include "LCD_Private.H"      /* private modul definitions & config */


I32  LCD_GetDevCap(int Index) {
  switch (Index) {
  case LCD_DEVCAP_NUMCOLORS:
    return LCD_NUM_COLORS;
  case LCD_DEVCAP_XSIZE:
    return LCD_GetXSize();
  case LCD_DEVCAP_YSIZE:
    return LCD_GetYSize();
  case LCD_DEVCAP_VXSIZE:
    return LCD_VXSIZE;
  case LCD_DEVCAP_VYSIZE:
    return LCD_VYSIZE;
  case LCD_DEVCAP_CONTROLLER:
    return LCD_CONTROLLER;
  case LCD_DEVCAP_BITSPERPIXEL:
    return LCD_BITSPERPIXEL;
  }
  if ((Index >= LCD_DEVCAP_COLOR) && (Index < LCD_DEVCAP_COLOR+LCD_NUM_COLORS)) {
    return LCD_Index2Color(Index-LCD_DEVCAP_COLOR);
  }
  return 0;
}

