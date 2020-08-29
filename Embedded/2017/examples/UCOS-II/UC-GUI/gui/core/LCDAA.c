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
File        : LCDAA.c
Purpose     : Low level antialiasing routines.
---------------------------END-OF-HEADER------------------------------
*/

#define LCD_C

#include <stddef.h>           /* needed for definition of NULL */
#include "LCD.H"
#include "GUI_Private.H"
#include "LCD_Private.h"

/*
        *********************************************************
        *                                                       *
        *       Macros for internal use                         *
        *                                                       *
        *********************************************************
*/

#define RETURN_IF_Y_OUT() \
  if (y < GUI_Context.ClipRect.y0)                     \
    return;                                            \
  if (y > GUI_Context.ClipRect.y1)                     \
    return;

#define RETURN_IF_X_OUT() \
  if (x < GUI_Context.ClipRect.x0) return;             \
  if (x > GUI_Context.ClipRect.x1) return;

#define CLIP_X() \
  if (x0 < GUI_Context.ClipRect.x0) { x0 = GUI_Context.ClipRect.x0; } \
  if (x1 > GUI_Context.ClipRect.x1) { x1 = GUI_Context.ClipRect.x1; }

#define CLIP_Y() \
  if (y0 < GUI_Context.ClipRect.y0) { y0 = GUI_Context.ClipRect.y0; } \
  if (y1 > GUI_Context.ClipRect.y1) { y1 = GUI_Context.ClipRect.y1; }


/*
        *********************************************************
        *                                                       *
        *           Antialiasing (opt)                          *
        *                                                       *
        *********************************************************
*/



LCD_COLOR LCD_AA_MixColors(LCD_COLOR Color, LCD_COLOR BkColor, U8 Intens) {
  /* Calc Color seperations for FgColor first */
  I32 R = (Color&0xff)*Intens;
  I32 G = (Color&0xff00)*Intens;
  I32 B = (Color&0xff0000)*Intens;
  /* Add Color seperations for BkColor */
  Intens = 15-Intens;
  R += (BkColor&0xff)*Intens;
  G += (BkColor&0xff00)*Intens;
  B += (BkColor&0xff0000)*Intens;
  R = (R/15)&0xff;
  G = (G/15)&0xff00;
  B = (B/15)&0xff0000;
  Color = R+G+B;
  return Color;
}


/* Draw 1-pixel with Foreground color */
void LCD_SetPixelAA(int x, int y, U8 Intens) {
  if (Intens == 0)
    return;
  RETURN_IF_Y_OUT();
  RETURN_IF_X_OUT();
  if (Intens >= 15) {
    LCDDEV_L0_SetPixelIndex(x,y, LCD_COLORINDEX);
  } else {
    LCD_COLOR Color = LCD_Index2Color(LCD_COLORINDEX);
    LCD_COLOR BkColor =  LCD_GetPixelColor(x,y);
    Color = LCD_AA_MixColors(Color, BkColor, Intens);
    LCDDEV_L0_SetPixelIndex(x,y, LCD_Color2Index(Color));
  }
}

/* Draw 1-pixel with Foreground and background color */
void LCD_SetPixelAA_NoTrans(int x, int y, U8 Intens) {
  RETURN_IF_Y_OUT();
  RETURN_IF_X_OUT();
  if (Intens == 0) {
    LCDDEV_L0_SetPixelIndex(x,y, LCD_BKCOLORINDEX);
  } else if (Intens == 15) {
    LCDDEV_L0_SetPixelIndex(x,y, LCD_COLORINDEX);
  } else {
    LCD_COLOR Color = LCD_AA_MixColors(LCD_Index2Color(LCD_COLORINDEX),
                                   LCD_Index2Color(LCD_BKCOLORINDEX),
                                   Intens);
    LCDDEV_L0_SetPixelIndex(x,y,LCD_Color2Index(Color));
  }
}

