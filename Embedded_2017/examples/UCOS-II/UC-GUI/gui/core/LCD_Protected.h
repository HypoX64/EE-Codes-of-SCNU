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
File        : LCD_Protected.H
Purpose     : Internals of the LCD level
----------------------------------------------------------------------
*/

#ifndef LCD_INTERN_H
#define LCD_INTERN_H

#include "LCD.h"

/*********************************************************************
*
*      Data types
*
**********************************************************************
*/

typedef struct {
  int              NumEntries; 
  const LCD_COLOR* pPalEntries; 
} LCD_PHYSPALETTE; 



/********************************************************
*
*     Color conversion routines (used internally only !
*
*********************************************************
*/
int LCD_Color2Index_0   (LCD_COLOR Color, const LCD_PHYSPALETTE* pPhysPal);
int LCD_Color2Index_1   (LCD_COLOR Color);
int LCD_Color2Index_2   (LCD_COLOR Color);
int LCD_Color2Index_4   (LCD_COLOR Color);
int LCD_Color2Index_111 (LCD_COLOR Color);
int LCD_Color2Index_222 (LCD_COLOR Color);
int LCD_Color2Index_233 (LCD_COLOR Color);
int LCD_Color2Index_323 (LCD_COLOR Color);
int LCD_Color2Index_332 (LCD_COLOR Color);
int LCD_Color2Index_444 (LCD_COLOR Color);
int LCD_Color2Index_555 (LCD_COLOR Color);
int LCD_Color2Index_565 (LCD_COLOR Color);
int LCD_Color2Index_8666(LCD_COLOR Color);
int LCD_Color2Index_M111 (LCD_COLOR Color);
int LCD_Color2Index_M222 (LCD_COLOR Color);
int LCD_Color2Index_M233 (LCD_COLOR Color);
int LCD_Color2Index_M323 (LCD_COLOR Color);
int LCD_Color2Index_M332 (LCD_COLOR Color);
int LCD_Color2Index_M444 (LCD_COLOR Color);
int LCD_Color2Index_M555(LCD_COLOR Color);
int LCD_Color2Index_M565 (LCD_COLOR Color);

LCD_COLOR LCD_Index2Color_0    (int Index, const LCD_PHYSPALETTE* pPhysPal);
LCD_COLOR LCD_Index2Color_1    (int Index);
LCD_COLOR LCD_Index2Color_2    (int Index);
LCD_COLOR LCD_Index2Color_4    (int Index);
LCD_COLOR LCD_Index2Color_111  (int Index);
LCD_COLOR LCD_Index2Color_222  (int Index);
LCD_COLOR LCD_Index2Color_233  (int Index);
LCD_COLOR LCD_Index2Color_323  (int Index);
LCD_COLOR LCD_Index2Color_332  (int Index);
LCD_COLOR LCD_Index2Color_444  (int Index);
LCD_COLOR LCD_Index2Color_555  (int Index);
LCD_COLOR LCD_Index2Color_565  (int Index);
LCD_COLOR LCD_Index2Color_8666 (int Index);
LCD_COLOR LCD_Index2Color_M111  (int Index);
LCD_COLOR LCD_Index2Color_M222  (int Index);
LCD_COLOR LCD_Index2Color_M233  (int Index);
LCD_COLOR LCD_Index2Color_M323  (int Index);
LCD_COLOR LCD_Index2Color_M332  (int Index);
LCD_COLOR LCD_Index2Color_M444  (int Index);
LCD_COLOR LCD_Index2Color_M555  (int Index);
LCD_COLOR LCD_Index2Color_M565  (int Index);


/*********************************************************************
*
*      LCDDEV function table
*
**********************************************************************

  Below the routines which need to in an LCDDEV routine table are
  defined. All of these routines have to be in the low-level driver
  (LCD_L0) or in the memory device which can be used to replace the
  driver.
  The one exception to this is the SetClipRect routine, which would
  be identical for all drivers and is therefor contained in the
  level above (LCD).
*/
typedef void         tLCDDEV_DrawHLine    (int x0, int y0,  int x1);
typedef void         tLCDDEV_DrawVLine    (int x , int y0,  int y1);
typedef void         tLCDDEV_FillRect     (int x0, int y0, int x1, int y1);
typedef unsigned int tLCDDEV_GetPixelIndex(int x, int y);
typedef void         tLCDDEV_SetPixelIndex(int x, int y, int ColorIndex);
typedef void         tLCDDEV_XorPixel     (int x, int y);
typedef void         tLCDDEV_FillPolygon  (const GUI_POINT*, int NumPoints, int x0, int y0);
typedef void         tLCDDEV_FillPolygonAA(const GUI_POINT*, int NumPoints, int x0, int y0);
typedef void         tLCDDEV_GetRect      (LCD_RECT*pRect);
typedef int          tLCDDEV_Init(void);
typedef unsigned int tLCDDEV_Color2Index  (LCD_COLOR Color);


/*********************************************************************
*
*              Declarations for LCD_L0_
*
**********************************************************************

  Prefixes are as follows:
  LCD_L0_xxx       ... Driver for first LCD
  LCD_L0_1_xxx     ... Driver for second LCD
  LCD_L0_MAG_xxx   ... Driver for first LCD, magnification level (calling LCD_L0_xxx after magnification)

*/

#if !defined (__C51__) /* To bypass Keil-compiler bug */
  tLCDDEV_Color2Index          LCD_L0_Color2Index,   LCD_L0_1_Color2Index;
  tLCDDEV_DrawHLine            LCD_L0_DrawHLine,     LCD_L0_1_DrawHLine,     LCD_L0_MAG_DrawHLine;
  tLCDDEV_DrawVLine            LCD_L0_DrawVLine,     LCD_L0_1_DrawVLine,     LCD_L0_MAG_DrawVLine;
  tLCDDEV_FillRect             LCD_L0_FillRect,      LCD_L0_1_FillRect,      LCD_L0_MAG_FillRect;
  tLCDDEV_GetPixelIndex        LCD_L0_GetPixelIndex, LCD_L0_1_GetPixelIndex, LCD_L0_MAG_GetPixelIndex;
  tLCDDEV_GetRect              LCD_L0_GetRect,       LCD_L0_1_GetRect;
  tLCDDEV_SetPixelIndex        LCD_L0_SetPixelIndex, LCD_L0_1_SetPixelIndex, LCD_L0_MAG_SetPixelIndex;
  tLCDDEV_XorPixel             LCD_L0_XorPixel,      LCD_L0_1_XorPixel,      LCD_L0_MAG_XorPixel;
  tLCDDEV_Init                 LCD_L0_Init,          LCD_L0_1_Init,          LCD_L0_MAG_Init;
#else
  /* tLCDDEV_Color2Index */
  unsigned int LCD_L0_Color2Index  (LCD_COLOR Color);
  unsigned int LCD_L0_1_Color2Index(LCD_COLOR Color);
  /* tLCDDEV_DrawHLine */
  void         LCD_L0_DrawHLine        (int x0, int y0,  int x1);
  void         LCD_L0_1_DrawHLine      (int x0, int y0,  int x1);
  void         LCD_L0_MAG_DrawHLine    (int x0, int y0,  int x1);
  /* tLCDDEV_DrawVLine */
  void         LCD_L0_DrawVLine        (int x , int y0,  int y1);
  void         LCD_L0_1_DrawVLine      (int x , int y0,  int y1);
  void         LCD_L0_MAG_DrawVLine    (int x , int y0,  int y1);
  /* tLCDDEV_FillRect */
  void         LCD_L0_FillRect         (int x0, int y0, int x1, int y1);
  void         LCD_L0_1_FillRect       (int x0, int y0, int x1, int y1);
  void         LCD_L0_MAG_FillRect     (int x0, int y0, int x1, int y1);
  /* tLCDDEV_GetPixelIndex */
  unsigned int LCD_L0_GetPixelIndex    (int x, int y);
  unsigned int LCD_L0_1_GetPixelIndex  (int x, int y);
  unsigned int LCD_L0_MAG_GetPixelIndex(int x, int y);
  /* tLCDDEV_GetRect */
  void         LCD_L0_GetRect          (LCD_RECT*pRect);
  void         LCD_L0_1_GetRect        (LCD_RECT*pRect);
  /* tLCDDEV_SetPixelIndex */
  void         LCD_L0_SetPixelIndex    (int x, int y, int ColorIndex);
  void         LCD_L0_1_SetPixelIndex  (int x, int y, int ColorIndex);
  void         LCD_L0_MAG_SetPixelIndex(int x, int y, int ColorIndex);
  /* tLCDDEV_XorPixel */
  void         LCD_L0_XorPixel         (int x, int y);
  void         LCD_L0_1_XorPixel       (int x, int y);
  void         LCD_L0_MAG_XorPixel     (int x, int y);
  /* tLCDDEV_Init */
  int          LCD_L0_Init             (void);
  int          LCD_L0_1_Init           (void);
  int          LCD_L0_MAG_Init         (void);
#endif

void LCD_L0_Off          (void); /* switch LCD off, hiding contents of VRAM */
void LCD_L0_On           (void); /* switch LCD off, Showing contents of VRAM */
void LCD_L0_ReInit       (void); /* Reinitialize LCD using config-paramters */
void LCD_L0_Refresh      (void); /* Refresh entire LCD */
                                 /* Refresh LCD partially. Could be one line, depends on what
                                    the LCD controller can handle efficiently */
void LCD_L0_SetLUTEntry  (U8 Pos, LCD_COLOR color);
void LCD_L0_1_SetLUTEntry(U8 Pos, LCD_COLOR color);
void LCD_L0_SetOrg       (int x, int y);

#endif /* LCD_INTERN_H */




