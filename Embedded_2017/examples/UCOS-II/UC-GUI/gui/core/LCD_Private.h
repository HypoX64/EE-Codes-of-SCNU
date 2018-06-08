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
File        : LCD_Private.H
Purpose     : Internals of the LCD level
----------------------------------------------------------------------
*/

#ifndef LCD_Private_H
#define LCD_Private_H

#include "LCD_ConfDefaults.h"            /* Configuration header file */
#include "LCD_Protected.h"

typedef void tLCDDEV_DrawBitmap   (int x0, int y0, int xsize, int ysize,
                       int BitsPerPixel, int BytesPerLine,
                       const U8* pData, int Diff,
                       const LCD_PIXELINDEX* pTrans);

struct tLCDDEV_APIList_struct {
  tLCDDEV_Color2Index*        pfColor2Index;
  tLCDDEV_DrawBitmap*         pfDrawBitmap;
  tLCDDEV_DrawHLine*          pfDrawHLine;
  tLCDDEV_DrawVLine*          pfDrawVLine;
  tLCDDEV_FillRect*           pfFillRect;
  tLCDDEV_GetPixelIndex*      pfGetPixelIndex;
  tLCDDEV_GetRect*            pfGetRect;
  tLCDDEV_Index2Color*        pfIndex2Color;
  tLCDDEV_SetPixelIndex*      pfSetPixelIndex;
  tLCDDEV_XorPixel*           pfXorPixel;
  tLCDDEV_FillPolygon*        pfFillPolygon;
  tLCDDEV_FillPolygonAA*      pfFillPolygonAA;
};

#if LCD_BITSPERPIXEL <=8
  #define LCD_BKCOLORINDEX GUI_Context.LCD.aColorIndex8[0]
  #define LCD_COLORINDEX   GUI_Context.LCD.aColorIndex8[1]
  #define LCD_ACOLORINDEX  GUI_Context.LCD.aColorIndex8
#else
  #define LCD_BKCOLORINDEX GUI_Context.LCD.aColorIndex16[0]
  #define LCD_COLORINDEX   GUI_Context.LCD.aColorIndex16[1]
  #define LCD_ACOLORINDEX  GUI_Context.LCD.aColorIndex16
#endif

#if !defined (__C51__) /* To bypass Keil-compiler bug */
  extern const struct tLCDDEV_APIList_struct LCD_L0_APIList, LCD_L0_1_APIList;
#endif

/*********************************************************************
*
*          Support for Segment/COMLUTs
*
**********************************************************************
*/

#define LCD_TYPE_SEGTRANS U16
#define LCD_TYPE_COMTRANS U16

#ifdef LCD_LUT_COM
  #ifdef LCDCOLOR_C
    LCD_TYPE_COMTRANS LCD__aLine2Com0[LCD_YSIZE] = { LCD_LUT_COM };
  #else
    extern LCD_TYPE_COMTRANS LCD__aLine2Com0[LCD_YSIZE];
  #endif
#endif

#ifdef LCD_LUT_SEG
  #ifdef LCDCOLOR_C
    LCD_TYPE_SEGTRANS LCD__aCol2Seg0[LCD_XSIZE] = { LCD_LUT_SEG };
  #else
    extern LCD_TYPE_COMTRANS LCD__aCol2Seg0[LCD_XSIZE];
  #endif
#endif

#endif /* Avoid multiple inclusion */




