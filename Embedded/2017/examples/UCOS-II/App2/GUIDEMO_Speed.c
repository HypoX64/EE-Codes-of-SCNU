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
File        : GUIDEMO_Speed.c
Purpose     : Speed demo
----------------------------------------------------------------------
*/

#include <stdlib.h>  /* for rand */
#include "GUI.H"
#include "GUIDEMO.H"


static const GUI_COLOR _aColor[8] = {
  0x000000, 
  0x0000FF, 
  0x00FF00, 
  0x00FFFF, 
  0xFF0000, 
  0xFF00FF, 
  0xFFFF00, 
  0xFFFFFF
};

/*********************************************************************
*
*       GUIDEMO_Speed
*
**********************************************************************
*/

void GUIDEMO_Speed(void) {
  int t = GUI_GetTime();
  int i = 0;
  int XSize = LCD_GET_XSIZE();
  int YSize = LCD_GET_YSIZE();
  I32 NumPixels=0;
  U16 aColorIndex[8];
  GUIDEMO_ShowIntro("High speed",
                    "Multi layer clipping"
                    "\nHighly optimized drivers"
                    );
  for (i = 0; i< 8; i++) {
    aColorIndex[i] = GUI_Color2Index(_aColor[i]);
  }  
  for (i = 0; (((t + 500) - (int)GUI_GetTime()) > 0) && !GUIDEMO_CheckCancel(); i++) {
    GUI_RECT r;
    GUI_SetColorIndex(aColorIndex[i&7]);
    /* Calculate random positions */
    r.x0 = rand() % XSize - XSize / 2;
    r.y0 = rand() % YSize - YSize / 2;
    r.x1 = r.x0 + rand() % XSize;
    r.y1 = r.y0 + rand() % YSize;
    GUI_FillRect(r.x0, r.y0, r.x1, r.y1);
    /* Clip rectangle to visible area and add the number of pixels (for speed computation) */
    if (r.x1 >= XSize)
      r.x1 = XSize - 1;
    if (r.y1 >= YSize)
      r.y1 = YSize - 1;
    if (r.x0 < 0 )
      r.x0 = 0;
    if (r.y1 < 0)
      r.y1 = 0;
    NumPixels += (r.x1 - r.x0) * (r.y1 - r.y0);
    /* Allow short breaks so we do not use all available CPU time ... */
  }
  t = (GUI_GetTime() - t) / 100;
  GUI_Clear();
  GUIDEMO_NotifyStartNext();
  #if GUIDEMO_LARGE
    GUI_SetFont(&GUI_FontComic24B_ASCII);
  #else
    GUI_SetFont(&GUI_Font16B_ASCII);
  #endif
  GUI_SetColor(GUI_WHITE);
  GUI_DispStringAt("Pixels/sec: ", 10, (LCD_GetYSize() - GUI_GetFontSizeY()) / 2);
  if (t == 0)
    t++;
  GUI_DispDecMin(10 * (NumPixels / t));
  GUIDEMO_Wait();
}
