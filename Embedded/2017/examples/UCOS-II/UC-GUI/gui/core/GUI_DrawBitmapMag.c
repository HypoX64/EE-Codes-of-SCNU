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
File        : GUI_DrawBitmapMag.C
Purpose     : Implementation file for GUI_DrawBitmapMag
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Protected.H"

void GUI_DrawBitmapMag (const GUI_BITMAP *pBitmap, int x0, int y0, int xMul, int yMul) {
  GUI_DRAWMODE PrevDraw;
  int xSize, ySize;
  const GUI_LOGPALETTE* pPal;
  GUI_LOCK();
  pPal = pBitmap->pPal;
  xSize = pBitmap->XSize;
  ySize = pBitmap->YSize;
  PrevDraw = GUI_SetDrawMode((pPal && pPal->HasTrans) ? GUI_DRAWMODE_TRANS : 0);
  #if (GUI_WINSUPPORT)
    WM_ADDORG(x0,y0);
    {
      GUI_RECT r;
      r.x0 = x0;
      r.x1 = x0 + xSize * yMul -1;
      r.y0 = y0;
      r.y1 = y0 + xSize * yMul -1;
      WM_ITERATE_START(&r);
  #endif
  if (pBitmap->pfDraw) {
    #if !defined (__C51__)  /* Avoid Keil C51 limitation */
      pBitmap->pfDraw(x0, y0, pBitmap->XSize ,pBitmap->YSize, (U8 const *)pBitmap->pData, pBitmap->pPal, xMul, yMul);
    #endif
  } else {
    LCD_DrawBitmap(x0, y0, xSize, ySize, xMul, yMul
                    ,pBitmap->BitsPerPixel, pBitmap->BytesPerLine
                    ,pBitmap->pData, pBitmap->pPal);
  }
  #if (GUI_WINSUPPORT)
      WM_ITERATE_END();
    }
  #endif
  GUI_SetDrawMode(PrevDraw);
  GUI_UNLOCK();
}





