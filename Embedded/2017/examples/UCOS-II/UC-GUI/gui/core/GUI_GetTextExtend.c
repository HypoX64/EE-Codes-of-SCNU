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
File        : GUI_GetTextExtend.c
Purpose     : Implementation of GUI_GetTextExtend
---------------------------END-OF-HEADER------------------------------
*/


#include <stddef.h>           /* needed for definition of NULL */
#include <stdio.h>
#include <string.h>
#include "GUI_Private.H"
 

/*********************************************************************
*
*       GUI_GetTextExtend

*/

void GUI_GetTextExtend(GUI_RECT* pRect, const char* s, int Len) {
  int xMax =0;
  int NumLines =0;
  int LineLen;
  pRect->x0 = GUI_Context.DispPosX;
  pRect->y0 = GUI_Context.DispPosY;
  while (((LineLen = GUI__GetLineLen(s, Len)) !=0) && (Len>0)) {
    int xSize = GUI_GetLineDistX(s, LineLen);
    if (xSize > xMax)
      xMax= xSize;
    s += LineLen;
    while (*s == '\n')
      s++;
    Len -= LineLen;
    NumLines++;
  }
  pRect->x1 = pRect->x0 + xMax-1;
  pRect->y1 = pRect->y0 + GUI__GetFontSizeY()*NumLines-1;
}


