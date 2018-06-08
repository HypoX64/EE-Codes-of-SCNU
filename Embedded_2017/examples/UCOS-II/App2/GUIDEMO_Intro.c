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
File        : GUIDEMO_Intro.c
Purpose     : Introduction for µC/GUI generic demo
              (This is also a good file to demo and explain basic
              emWin features by setting breakpoints)
----------------------------------------------------------------------
*/

#include "GUI.H"
#include "GUIDEMO.H"
#include <string.h>

/*********************************************************************
*
*       GUIDEMO_Intro
*
**********************************************************************
*/

#if GUIDEMO_LARGE

void GUIDEMO_Intro(void) {
  int xCenter = LCD_GET_XSIZE() / 2;
  int y;
  char acText[50] = "Version of µC/GUI: ";
  strcat(acText, GUI_GetVersionString());
  GUI_SetBkColor(GUI_BLUE);
  GUI_SetColor(GUI_LIGHTRED);
  GUI_Clear();
  GUI_SetFont(&GUI_Font24B_1);
  GUI_DispStringHCenterAt("µC/GUI", xCenter, y= 15);
  GUI_SetColor(GUI_WHITE);
  GUI_SetFont(&GUI_Font13H_ASCII);
  GUI_DispStringHCenterAt("Universal graphic software"
                          "\nfor embedded applications"
                          , xCenter, y += 30);
  GUI_SetColor(GUI_LIGHTRED);
  GUI_SetFont(&GUI_Font16_ASCII);
  GUI_DispStringHCenterAt("Any CPU - Any LCD - Any Application"
                          , xCenter, y += 40);
  GUI_SetFont(&GUI_Font10S_ASCII);
  GUI_DispStringHCenterAt("Compiled " __DATE__ " "__TIME__, xCenter, y += 25);
  GUI_SetFont(&GUI_Font13HB_1);
  GUI_SetColor(GUI_WHITE);
  GUI_DispStringHCenterAt(acText, xCenter, y += 21);
  GUI_SetFont(&GUI_FontComic18B_1);
  GUI_SetColor(GUI_WHITE);
  GUI_DispStringHCenterAt("www.micrium.com", LCD_GET_XSIZE() / 2, LCD_GET_YSIZE() - 40);
  GUI_DrawBitmap(&bmMicriumLogo, (LCD_GET_XSIZE() - bmMicriumLogo.XSize) / 2, 150);
  GUI_SetFont(&GUI_Font10S_ASCII);
  GUI_DispStringAt("GUI_OS: ", 0,220); GUI_DispDecMin(GUI_OS);
  GUI_DispStringAt("GUI_ALLOC_SIZE: ",0, 230); GUI_DispDecMin(GUI_ALLOC_SIZE);
  GUIDEMO_Delay(300);
}

#else

void GUIDEMO_Intro(void) {
  int xCenter = LCD_GET_XSIZE() / 2;
  int y;
  char acText[50] = "Version of µC/GUI: ";
  strcat(acText, GUI_GetVersionString());
  GUI_SetBkColor(GUI_BLUE);
  GUI_SetColor(GUI_YELLOW);
  GUI_Clear();
  GUI_SetFont(&GUI_Font13B_1);
  GUI_DispStringHCenterAt("µC/GUI", xCenter, y= 10);
  GUI_SetFont(&GUI_Font10_ASCII);
  GUI_SetColor(GUI_WHITE);
  GUI_DispStringHCenterAt("Universal graphic software"
                          "\nfor embedded applications"
                          , xCenter, y += 20);
  GUI_SetFont(&GUI_Font10S_ASCII);
  GUI_DispStringHCenterAt("Compiled " __DATE__ " "__TIME__, xCenter, y += 25);
  GUI_DispStringHCenterAt(acText, xCenter, y += 16);
  GUIDEMO_Delay(500);

  GUI_Clear();
  GUI_DrawBitmap(&bmMicriumLogo, (LCD_GET_XSIZE() - bmMicriumLogo.XSize) / 2, 6);
  GUI_SetFont(&GUI_Font13B_1);
  GUI_DispStringHCenterAt("www.micrium.com", LCD_GET_XSIZE() / 2, LCD_GET_YSIZE() - 50);
  GUIDEMO_Delay(500);


}

#endif
