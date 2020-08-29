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
File        : LCDInfo1.C
Purpose     : Routines returning info at runtime
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "LCD.H"		          /* interface definitions */
#include "LCD_Private.H"      /* private modul definitions & config */


int LCD_GetXSize(void)        { return LCD_XSIZE; }
int LCD_GetYSize(void)        { return LCD_YSIZE; }
int LCD_GetVXSize(void)       { return LCD_VXSIZE; }
int LCD_GetVYSize(void)       { return LCD_VYSIZE; }
int LCD_GetBitsPerPixel(void) { return LCD_BITSPERPIXEL; }
U32 LCD_GetNumColors(void)    { return LCD_NUM_COLORS; }
int LCD_GetYMag(void)         { return LCD_YMAG; }
int LCD_GetXMag(void)         { return LCD_XMAG; }
int LCD_GetFixedPalette(void) {
  #if LCD_SWAP_RB == 0
    return LCD_FIXEDPALETTE;
  #else
    return (-1)*LCD_FIXEDPALETTE;
  #endif
}

