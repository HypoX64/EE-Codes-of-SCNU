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
File        : LCDSIM.H
Purpose     : Declares LCD interface functions
----------------------------------------------------------------------
*/

#ifndef LCDSIM_H
#define LCDSIM_H



/************************************************************
*
*  LCDSIM_      General declarations
*
*************************************************************
*/

int  LCDSIM_GetPixelIndex(int x, int y);
int  LCDSIM_GetMouseState(LCD_tMouseState *pState);
void LCDSIM_SetMouseState(int x, int y, int KeyStat);
void LCDSIM_RLUT_SetPixelIndex(int x, int y, int Index);
int  LCDSIM_RLUT_GetPixelIndex(int x, int y);

/************************************************************
*
*  LCDSIM_      Declarations for display 0
*
*************************************************************
*/

void  LCDSIM_FillRect(int x0, int y0, int x1, int y1, int Index);
int   LCDSIM_GetPixelColor(int x, int y);
int   LCDSIM_Index2Color(int Index);
int   LCDSIM_GetModifyCnt(void);
int   LCDSIM_GetModifyCntInfo(void);
char* LCDSIM_Init(void);
void  LCDSIM_SetLUTEntry(U8 Pos, LCD_COLOR color);
void  LCDSIM_SetPixelIndex(int x, int y, int Index);
void LCDSIM_SetSubPixel(int x, int y, U8 Value);

/************************************************************
*
*  LCDSIM_      Declarations for display 1
*
*************************************************************
*/

void  LCDSIM_1_FillRect(int x0, int y0, int x1, int y1, int Index);
int   LCDSIM_1_GetModifyCnt(void);
int   LCDSIM_1_GetModifyCntInfo(void);
int   LCDSIM_1_GetColor(int Index);
char* LCDSIM_1_Init(void);
void  LCDSIM_1_SetPixelIndex(int x, int y, int Index);
void  LCDSIM_1_SetLUTEntry(U8 Pos, LCD_COLOR color);

/************************************************************
*
*  LCDSIM_      Declarations for painting in windows program
*
*************************************************************
*/

#ifdef _WINDOWS_   /* if windows.h has already been included */
  void LCDSIM_Paint(HDC hDC);
  void LCDSIM_PaintEx(HDC hDC, LPRECT pRectDest, LPRECT pRectSrc);
  void LCDSIM_PaintAt(HDC hDC, int x, int y);
  void LCDSIM_1_Paint(HDC hDC);
  void LCDSIM_1_PaintEx(HDC hDC, LPRECT pRectDest, LPRECT pRectSrc);
  void LCDSIM_1_PaintAt(HDC hDC, int x, int y);
#endif


#endif /* LCD_H */




