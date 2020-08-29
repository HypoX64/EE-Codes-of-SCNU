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
File        : GUIDEMO_ColorList.c
Purpose     : Shows color list
----------------------------------------------------------------------
*/

#include "LCD_ConfDefaults.h"  /* valid LCD configuration */
#include "WM.H"
#include "GUIDEMO.H"

/*********************************************************************
*
*       GUIDEMO_ShowColorList
*
**********************************************************************
*/

#if (LCD_BITSPERPIXEL > 2) && (LCD_BITSPERPIXEL <= 8)

void GUIDEMO_ShowColorList(void) {
  int NumColors = LCD_GetDevCap(LCD_DEVCAP_NUMCOLORS);
  int Lines = (NumColors - 1) / 16 + 1;
  int y0 = 70;
  int XSize = LCD_GetXSize();
  int YSize = LCD_GetYSize();
  #if (LCD_BITSPERPIXEL > 8)
    int XStep = XSize / 256;
    int YStep = NumColors / 256;
  #endif
  int i;
  GUIDEMO_ShowIntro("Available colors",
                    "Shows the first of the "
                    "\navailable colors in the "
                    "\nsimulated configuration");
  GUI_SetColor(GUI_WHITE);
  GUI_SetBkColor(GUI_BLACK); 
  GUI_Clear();
	GUI_SetFont(&GUI_Font8x16);
	GUI_DispString("Available colors\n");
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
  #if (LCD_BITSPERPIXEL <= 8)
  {
    int XStep = XSize / 16;
    int YStep = (YSize - y0 - (YSize < 320 ? 0 : 60)) / Lines;
	  for (i = 0; i < NumColors; i++) {
      GUI_SetColorIndex(i);
      GUI_FillRect((i%16) * XStep + 2,
                   (i/16) * YStep + 1 + y0,
                   (i%16 + 1) * XStep - 1,
                   (i/16 + 1) * YStep - 2 + y0);
    }
  }
  #else
  {
	  for (i = 0; i < NumColors; i++) {
      GUI_SetColorIndex(i);
      GUI_DrawPoint((U8)(i) + ((LCD_XSIZE - 1 - 256) >> 1), (i >> 8) + y0);
    }
  }
  #endif
  GUIDEMO_Delay(200);
}

#else

void GUIDEMO_ShowColorList(void) {}

#endif
