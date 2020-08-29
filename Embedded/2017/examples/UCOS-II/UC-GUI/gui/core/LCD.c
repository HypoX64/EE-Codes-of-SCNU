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
File        : LCD.c
Purpose     : Link between GUI and LCD_L0
              Performs most of the clipping.
---------------------------END-OF-HEADER------------------------------
*/

#define LCD_C

#include <stdio.h>
#include "GUI_Private.H"
#include "LCD_Private.h"
#include "GUIDebug.h"

/*
        *********************************************************
        *                                                       *
        *       Macros for internal use                         *
        *                                                       *
        *********************************************************
*/

#define RETURN_IF_Y_OUT() \
  if (y < GUI_Context.ClipRect.y0) return;             \
  if (y > GUI_Context.ClipRect.y1) return;

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
        *       LCD_SetColorIndex                               *
        *       LCD_SetBkColorIndex                             *
        *                                                       *
        *********************************************************
*/
static int GetColorIndex(int i)  /* i is 0 or 1 */ {
  return  (GUI_Context.DrawMode & LCD_DRAWMODE_REV) ? i-1 : i;
}

void LCD_SetColorIndex(int Index)   { LCD_ACOLORINDEX[GetColorIndex(1)] = Index; }
void LCD_SetBkColorIndex(int Index) { LCD_ACOLORINDEX[GetColorIndex(0)] = Index; }

/*
        *********************************************************
        *                                                       *
        *       LCD_SetDrawMode                                 *
        *                                                       *
        *********************************************************

*/
LCD_DRAWMODE LCD_SetDrawMode  (LCD_DRAWMODE dm) {
  LCD_DRAWMODE OldDM = GUI_Context.DrawMode;
  if ((GUI_Context.DrawMode^dm) & LCD_DRAWMODE_REV) {
    LCD_PIXELINDEX temp = LCD_BKCOLORINDEX;
    LCD_BKCOLORINDEX    = LCD_COLORINDEX;
    LCD_COLORINDEX = temp;
  }
  GUI_Context.DrawMode = dm;
  return OldDM;
}

/*
        *********************************************************
        *                                                       *
        *       LCD_SetPixel                                    *
        *                                                       *
        *********************************************************

Purpose:  This routine is called by emWin. It writes 1 pixel into the
          display.

*/

void LCD_SetPixelIndex(int x, int y, int ColorIndex) {
  RETURN_IF_X_OUT();
  RETURN_IF_Y_OUT();
  LCDDEV_L0_SetPixelIndex(x, y, ColorIndex);
}

/*
        *********************************************************
        *                                                       *
        *       LCD_DrawPixel                                   *
        *                                                       *
        *********************************************************

Purpose:  This routine is called by emWin. It writes 1 pixel into the
          display using the current drawing mode.

*/


void LCD_DrawPixel(int x, int y) {
  RETURN_IF_Y_OUT();
  RETURN_IF_X_OUT();
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    LCDDEV_L0_XorPixel(x, y);
  } else {
    LCDDEV_L0_SetPixelIndex(x, y, LCD_COLORINDEX);
  }
}

/*
        *********************************************************
        *                                                       *
        *          LCD_DrawLine  vertical/horizontal            *
        *          LCD_DrawRect                                 *
        *                                                       *
        *********************************************************
*/

void LCD_DrawHLine  (int x0, int y,  int x1) {
  /* Perform clipping and check if there is something to do */
  RETURN_IF_Y_OUT();
  CLIP_X();
  if (x1<x0)
    return;
  /* Call driver to draw */
  LCDDEV_L0_DrawHLine(x0, y, x1);
}

void LCD_DrawVLine  (int x, int y0,  int y1) {
  /* Perform clipping and check if there is something to do */
  RETURN_IF_X_OUT();
  CLIP_Y();
  if (y1<y0)
    return;
  /* Call driver to draw */
  LCDDEV_L0_DrawVLine(x, y0, y1);
}

void LCD_FillRect(int x0, int y0, int x1, int y1) {
  /* Perform clipping and check if there is something to do */
  CLIP_X();
  if (x1<x0)
    return;
  CLIP_Y();
  if (y1<y0)
    return;
  /* Call driver to draw */
  LCDDEV_L0_FillRect(x0,y0,x1,y1);
}




/*
    **********************************************************************
    *                                                                    *
    *             Universal draw Bitmap routine                          *
    *                                                                    *
    **********************************************************************
*/
void LCD_DrawBitmap   (int x0, int y0,
                       int xsize, int ysize,
                       int xMul, int yMul,
                       int BitsPerPixel,
                       int BytesPerLine,
                       const U8* pPixel,
                       const LCD_LOGPALETTE* pLogPal) {
  U8  Data;
  int x1, y1;
  const LCD_PIXELINDEX* pTrans;
  /* Handle the optional Y-magnification */
  y1 = y0+ysize-1;
  x1 = x0+xsize-1;
  /* Handle color translation */
  if ((pLogPal) && (pLogPal->pPalEntries)) {
    if ((pTrans = LCD_GetpPalConvTable(pLogPal)) == NULL) {
      return;
    }
  } else {
		pTrans = (BitsPerPixel != 1) ? NULL : &LCD_BKCOLORINDEX;
  }
/*  Handle BITMAP without magnification */
  if ((xMul==1) && (yMul==1)) {
    int Diff;
    /*    Clip Y    */
    if (y0 < GUI_Context.ClipRect.y0) {
      Diff = GUI_Context.ClipRect.y0 -y0;
      y0     = GUI_Context.ClipRect.y0;
      pPixel += Diff*BytesPerLine;
      ysize -= Diff;
    }
    if (y1 > GUI_Context.ClipRect.y1) {
      int Diff = y1-GUI_Context.ClipRect.y1;
      ysize -= Diff;
    }
    if (ysize <=0)
		  return;
    /*        Clip right side    */
    if (x1 > GUI_Context.ClipRect.x1) {
      int Diff = x1-GUI_Context.ClipRect.x1;
      xsize -= Diff;
    }
    /*        Clip left side ... (The difficult side ...)    */
    Diff =0;
    if (x0 < GUI_Context.ClipRect.x0) {
      Diff = GUI_Context.ClipRect.x0-x0;
			xsize-=Diff;
			switch (BitsPerPixel) {
			case 1:
  			pPixel+= (Diff>>3); x0 += (Diff>>3)<<3; Diff &=7;
				break;
			case 2:
	  		pPixel+= (Diff>>2); x0 += (Diff>>2)<<2; Diff &=3;
				break;
			case 4:
				pPixel+= (Diff>>1); x0 += (Diff>>1)<<1; Diff &=1;
				break;
			case 8:
				pPixel+= Diff;      x0 += Diff; Diff=0;
				break;
			case 16:
				pPixel+= (Diff<<1); x0 += Diff; Diff=0;
				break;
			}
    }
    if (xsize <=0)
		  return;
    LCDDEV_L0_DrawBitmap   (x0,y0, xsize, ysize, BitsPerPixel, BytesPerLine, pPixel, Diff, pTrans);
  } else {
    /**** Handle BITMAP with magnification ***/
    int x,y;
    int yi;
    int Shift = 8-BitsPerPixel;
    for (y=y0, yi=0; yi<ysize; yi++, y+= yMul, pPixel+=BytesPerLine) {
      int yMax = y+yMul-1;
      /* Draw if within clip area (Optimization ... "if" is not required !) */
      if ((yMax >= GUI_Context.ClipRect.y0) && (y <= GUI_Context.ClipRect.y1)) {
        int BitsLeft =0;
        int xi;
        const U8* pDataLine = pPixel;
        for (x=x0, xi=0; xi<xsize; xi++, x+=xMul) {
          U8  Index;
          if (!BitsLeft) {
            Data = *pDataLine++;
            BitsLeft =8;
          }
          Index = Data>>Shift;
          Data    <<= BitsPerPixel;
          BitsLeft -= BitsPerPixel;
          if (Index | ((GUI_Context.DrawMode & LCD_DRAWMODE_TRANS) ==0)) {
            LCD_PIXELINDEX  OldColor = LCD_COLORINDEX;
            if (pTrans) {
              LCD_COLORINDEX = *(pTrans+Index);
            } else {
              LCD_COLORINDEX = Index;
            }
            LCD_FillRect(x,y, x+xMul-1, yMax);
            LCD_COLORINDEX = OldColor;
          }
        }
      }
    }
  }
}

/*********************************************************************
*
*           LCD_SetClipRect
*
**********************************************************************

This function is actually a driver function.
Since it is identical for all drivers with only one controller,
it is placed here.
For multi-controller systems, this routine is placed in the
distribution driver.

*/

void LCD_SetClipRectEx(const GUI_RECT* pRect) {
  LCD_RECT r;
  LCDDEV_L0_GetRect(&r);
  GUI__IntersectRects(&GUI_Context.ClipRect, pRect, &r);
}


/*********************************************************************
*
*           Set Max Clip Rect
*
**********************************************************************
*/

void LCD_SetClipRectMax(void) {
  LCDDEV_L0_GetRect(&GUI_Context.ClipRect);
}



/*
        *********************************************************
        *                                                       *
        *       LCD_Init : Init the display                     *
        *                                                       *
        *********************************************************
*/

int  LCD_Init(void) {
  int r;
  GUI_DEBUG_LOG("\nLCD_Init...");
  LCD_SetClipRectMax();
  if ((r = LCD_L0_Init()) != 0)
    return r;
#if LCD_NUM_DISPLAYS > 1
  if ((r = LCD_L0_1_Init()) != 0)
    return r;
#endif
  GUI_DEBUG_LOG("\nLCD_Init 1...");
  LCD_InitLUT();
  GUI_DEBUG_LOG("\nLCD_Init 2...");
/* Clear video memory */
  LCD_SetDrawMode(GUI_DRAWMODE_REV);
  GUI_DEBUG_LOG("\nLCD_Init 3...");
  LCD_FillRect(0,0, GUI_XMAX, GUI_YMAX);
  GUI_DEBUG_LOG("\nLCD_Init 4...");
  LCD_SetDrawMode(0);
/* Switch LCD on */
  GUI_DEBUG_LOG("\nLCD_Init 5...");
  LCD_On();
  GUI_DEBUG_LOG("\nLCD_Init out...");
  return 0;
}


/*********************************************************************
*
*           LCD_Index2Color
*           LCD_Color2Index
*
**********************************************************************
*/

int LCD_Color2Index     (LCD_COLOR Color) {
  return LCDDEV_L0_Color2Index(Color);
}

LCD_COLOR LCD_Index2Color (int Index) {
  return LCDDEV_L0_Index2Color(Index);
}



/*********************************************************************
*
*           LCD_SetBkColor
*           LCD_SetColor
*
**********************************************************************

Purpose:  Assign color/index to foreground/ background
*/


void LCD_SetBkColor(GUI_COLOR color) {
  LCD_SetBkColorIndex(LCD_Color2Index(color));
}

void LCD_SetColor(GUI_COLOR color) {
  LCD_SetColorIndex(LCD_Color2Index(color));
}


