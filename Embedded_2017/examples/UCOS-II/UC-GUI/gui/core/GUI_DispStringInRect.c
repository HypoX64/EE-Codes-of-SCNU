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
File        : GUI_DispStringInRect.c
Purpose     : Implementation of GUI_DispStringInRect
---------------------------END-OF-HEADER------------------------------
*/


#include <stddef.h>           /* needed for definition of NULL */
#include <stdio.h>
#include <string.h>
#include "GUI_Private.H"
 

/********************************************************************
*
*                Display String in given rectangle
*
*********************************************************************
*/

static void _DispStringInRect(const char GUI_FAR *s, GUI_RECT* pRect, int TextAlign) {
  GUI_RECT r;
  GUI_RECT rLine;
  int y;
  int NumLines;
  const char *sOrg =s;
  int FontYSize;
  int xLine;
  FontYSize = GUI_GetFontSizeY();
  if (pRect) {
    r = *pRect;
  } else {
    GUI_GetClientRect(&r);
  }
  /* Count the number of lines for vertical alignment */
  for (NumLines=1; ;NumLines++) {
    int LineLen= GUI__GetLineLen(s,0x7fff);
    s += LineLen;
    if (GUI__HandleEOLine(&s))
      break;
  }
  /* Do the vertical alignment */
  switch (TextAlign & GUI_TA_VERTICAL) {
	case GUI_TA_TOP:
		y = r.y0;
    break;
	case GUI_TA_BASELINE:
	case GUI_TA_BOTTOM:
	y = r.y1 -NumLines * FontYSize+1;
    break;
	case GUI_TA_VCENTER:
		y = r.y0+(r.y1-r.y0+1 -NumLines * FontYSize) /2;
    break;
	}
  for (s=sOrg; ;) {
    int LineLen= GUI__GetLineLen(s,0x7fff);
    int xLineSize = GUI_GetLineDistX(s, LineLen);
    switch (TextAlign & GUI_TA_HORIZONTAL) {
    case GUI_TA_HCENTER:
      xLine = r.x0+(r.x1-r.x0-xLineSize)/2; break;
    case GUI_TA_LEFT:
      xLine = r.x0; break;
    case GUI_TA_RIGHT:
      xLine = r.x1 -xLineSize;
    }
    rLine.x0 = GUI_Context.DispPosX = xLine;
    rLine.x1 = rLine.x0 + xLineSize-1;
    rLine.y0 = GUI_Context.DispPosY = y;
    rLine.y1 = y + FontYSize-1;
    GUI__DispLine(s, LineLen, &rLine);
    s += LineLen;
    y += GUI_GetFontDistY();
    if (GUI__HandleEOLine(&s))
      break;
  }
}


void GUI_DispStringInRect(const char GUI_FAR *s, GUI_RECT* pRect, int TextAlign) {
  #if (GUI_WINSUPPORT)
    const GUI_RECT *pClipRect_Old;
  #else
    GUI_RECT Rect_Old;
  #endif
  if (s) {
    GUI_LOCK();
    if (pRect) {
      #if (GUI_WINSUPPORT)
        pClipRect_Old = WM_SetUserClipRect(pRect);
      #else
        Rect_Old = GUI_Context.ClipRect;
        LCD_SetClipRectEx(pRect);
      #endif      
    }
    _DispStringInRect(s, pRect, TextAlign);
    #if (GUI_WINSUPPORT)
      WM_SetUserClipRect(pClipRect_Old);
    #else
      LCD_SetClipRectEx(&Rect_Old);
    #endif      
    GUI_UNLOCK();
  }
}

/***  End of file ***/
