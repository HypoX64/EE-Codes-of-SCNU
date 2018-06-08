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
File        : GUIDEMO_Circle.c
Purpose     : Drawing circles
----------------------------------------------------------------------
*/

#include "WM.H"
#include "GUIDEMO.H"

/*********************************************************************
*
*       GUIDEMO_Circle
*
**********************************************************************
*/

void GUIDEMO_Circle(void) {
  int XSize = LCD_GetXSize();
  int YSize = LCD_GetYSize();
  GUIDEMO_ShowIntro("Circles",
                    "Arbitrary circles and arcs.");
  GUI_Clear();
  GUI_SetFont(&GUI_Font8x16);
  GUI_SetColor(GUI_WHITE);
  #if GUIDEMO_LARGE
    GUI_DispStringAt("Circle", 0, 0);
  #endif
  GUI_FillCircle (XSize / 2, YSize / 2, 50);
  GUIDEMO_Wait();
  GUI_SetDrawMode(GUI_DM_XOR);
  GUI_FillCircle (XSize / 2, YSize / 2, 60);
  GUI_SetDrawMode(0);
  GUIDEMO_Wait();
  #if GUIDEMO_LARGE
    GUIDEMO_ShowInfo("Circles with\nAntialiasing");
  #endif
  GUI_Clear();
  GUI_SetColor(GUI_WHITE);
  #if GUIDEMO_LARGE
    GUI_DispStringAt("Antialiased\ncircle", 0, 0);
  #endif
//  GUI_AA_FillCircle(XSize / 2, YSize / 2, 47);
  GUIDEMO_Wait();
}
