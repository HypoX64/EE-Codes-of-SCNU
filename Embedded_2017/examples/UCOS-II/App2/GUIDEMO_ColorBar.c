/*
*********************************************************************************************************
*                                                �C/GUI
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
File        : GUIDEMO_ShowColorBar.c
Purpose     : Draws color bars
----------------------------------------------------------------------
*/

#include "LCD.H"		           /* interface definitions */
#include "LCD_ConfDefaults.h"  /* valid LCD configuration */
#include "WM.H"
#include "GUIDEMO.H"

/*********************************************************************
*
*       GUIDEMO_ShowColorBar
*
**********************************************************************
*/

#if LCD_BITSPERPIXEL > 2

void GUIDEMO_ShowColorBar(void) {
  int nBars = 13;
  int YSize = LCD_GetYSize();
  int y0 = 70; 
  int yStep = (YSize - y0 - (YSize < 320 ? 0 : 60)) / nBars;
  int i;
  int x0 = 60;
  int NumColors = LCD_GetDevCap(LCD_DEVCAP_NUMCOLORS);
  int xsize = LCD_GetDevCap(LCD_DEVCAP_XSIZE);
	xsize -=x0;
  GUIDEMO_ShowIntro("Color bar",
                    "uC/GUI features an integrated"
                    "\nmanagement that will always"
                    "\nfind the best available"
                    "\ncolor for any logical color");
  GUI_SetColor(GUI_WHITE);
  GUI_SetBkColor(GUI_BLACK); 
  GUI_Clear();
	GUI_SetFont(&GUI_Font8x16);
	GUI_DispString("Color bars\n");
	GUI_SetFont(&GUI_Font8_ASCII);
  #ifdef LCD_CONTROLLER
    GUI_DispString("\nLCD_CONTROLLER: ");
    GUI_DispDecMin(LCD_CONTROLLER);
    GUI_DispString("\n");
  #endif
  GUI_DispDecMin(LCD_BITSPERPIXEL);
  GUI_DispString(" bpp");
  #ifdef LCD_BUSWIDTH
    GUI_DispString(", ");
    GUI_DispDecMin(LCD_BUSWIDTH);
    GUI_DispString(" bit bus");
  #endif
  GUI_DispString(", ");
  GUI_DispDecMin(NumColors);
  GUI_DispString(" colors\n");
  #if (LCD_FIXEDPALETTE) 
    GUI_DispString("Fixed palette: ");
    GUI_DispDecMin(LCD_FIXEDPALETTE);
  #else
    GUI_DispString("(Custom)");
  #endif
  GUI_SetFont(&GUI_Font8x8);
  GUI_SetColor(GUI_WHITE);
  GUI_DispStringAt("Red",     0, y0 +      yStep);
  GUI_DispStringAt("Green",   0, y0 + 3  * yStep);
  GUI_DispStringAt("Blue",    0, y0 + 5  * yStep);
  GUI_DispStringAt("Grey",    0, y0 + 6  * yStep);
  GUI_DispStringAt("Yellow",  0, y0 + 8  * yStep);
  GUI_DispStringAt("Cyan",    0, y0 + 10 * yStep);
  GUI_DispStringAt("Magenta", 0, y0 + 12 * yStep);
  for (i = 0; (i < xsize) && !GUIDEMO_CheckCancel(); i++) {
    U16 cs = (255 * (U32)i) / xsize;
    U16 x = x0 + i;;
/* Red */
    GUI_SetColor(cs);
    GUI_DrawVLine(x, y0, y0 + yStep - 1);
    GUI_SetColor(0x0000ff + (255 - cs) * 0x10100L);
    GUI_DrawVLine(x, y0 + yStep, y0 + 2 * yStep - 1);
/* Green */
    GUI_SetColor(cs<<8);
    GUI_DrawVLine(x, y0 + 2 * yStep, y0 + 3 * yStep - 1);
    GUI_SetColor(0x00ff00 + (255 - cs) * 0x10001L);
    GUI_DrawVLine(x, y0 + 3 * yStep, y0 + 4 * yStep - 1);
/* Blue */
    GUI_SetColor(cs * 0x10000L);
    GUI_DrawVLine(x, y0 + 4 * yStep, y0 + 5 * yStep - 1);
    GUI_SetColor(0xff0000 + (255 - cs) * 0x00101L);
    GUI_DrawVLine(x, y0 + 5 * yStep, y0 + 6 * yStep - 1);
/* Gray */
    GUI_SetColor(cs * 0x10101L);
    GUI_DrawVLine(x, y0 + 6 * yStep, y0 + 7 * yStep - 1);
/* Yellow */
    GUI_SetColor(cs * 0x00101L);
    GUI_DrawVLine(x, y0 + 7 * yStep, y0 + 8 * yStep - 1);
    GUI_SetColor(0x00ffff + (255 - cs) * 0x10000L);
    GUI_DrawVLine(x, y0 + 8 * yStep, y0 + 9 * yStep - 1);
/* Cyan */
    GUI_SetColor(cs * 0x10100L);
    GUI_DrawVLine(x, y0 + 9 * yStep, y0 + 10 * yStep - 1);
    GUI_SetColor(0xffff00 + (255 - cs) * 0x00001L);
    GUI_DrawVLine(x, y0 + 10 * yStep, y0 + 11 * yStep - 1);
/* Magenta */
    GUI_SetColor(cs * 0x10001L);
    GUI_DrawVLine(x, y0 + 11 * yStep, y0 + 12 * yStep - 1);
    GUI_SetColor(0xff00ff + (255 - cs) * 0x00100L);
    GUI_DrawVLine(x, y0 + 12 * yStep, y0 + 13 * yStep - 1);
  }
  GUIDEMO_Wait();
}

#else

void GUIDEMO_ShowColorBar(void) {}

#endif

