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


#if LCD_NUM_DISPLAYS > 1
  int LCD_GetXSize_1(void)        { return LCD_XSIZE_1; }
  int LCD_GetYSize_1(void)        { return LCD_YSIZE_1; }
  int LCD_GetVXSize_1(void)       { return LCD_VXSIZE_1; }
  int LCD_GetVYSize_1(void)       { return LCD_VYSIZE_1; }
  int LCD_GetBitsPerPixel_1(void) { return LCD_BITSPERPIXEL_1; }
  U32 LCD_GetNumColors_1(void)    { return LCD_NUM_COLORS_1; }
  int LCD_GetYMag_1(void)         { return LCD_YMAG_1; }
  int LCD_GetXMag_1(void)         { return LCD_XMAG_1; }
  int LCD_GetFixedPalette_1(void) {
    #if LCD_SWAP_RB_1 == 0
      return LCD_FIXEDPALETTE_1;
    #else
      return (-1)*LCD_FIXEDPALETTE_1;
    #endif
  }
#else
  int LCD_GetXSize_1(void)        { return 0; }
  int LCD_GetYSize_1(void)        { return 0; }
  int LCD_GetVXSize_1(void)       { return 0; }
  int LCD_GetVYSize_1(void)       { return 0; }
  int LCD_GetBitsPerPixel_1(void) { return 0; }
  U32 LCD_GetNumColors_1(void)    { return 0; }
  int LCD_GetYMag_1(void)         { return 0; }
  int LCD_GetXMag_1(void)         { return 0; }
  int LCD_GetFixedPalette_1(void) { return 0; }
#endif
