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
File        : GUIDevB.C
Purpose     : Implementation of banding memory devices
----------------------------------------------------------------------
Version-Date---Author-Explanation
----------------------------------------------------------------------
        010830 RS     GUI_MEMDEV_Draw now limits rectangle to
                      LCD area in order to avoid wasting computation time
        001109 RS     Bugfix: x0 was changed to 0 when moving the
                      active area. Fixed.
1.00    001015 RS     First release
0.00.00 00     RS     Initial version for internal tests
----------------------------------------------------------------------
Known problems or limitations with current version
----------------------------------------------------------------------
None
---------------------------END-OF-HEADER------------------------------
*/


#include <string.h>
#include "GUI_Protected.h"
#include "GUIDebug.h"
/*
 Memory device capabilities are compiled only if support for them is enabled.
*/ 
#if GUI_SUPPORT_MEMDEV

/*
*********************************************************
*
*              GUI_MEMDEV_Draw
*
*********************************************************

This routine uses a banding memory device to draw the
given area flicker free. It not only draws, but also
automatically calculates the size of, creates, moves
and then destroys the memory device.

*/

static int Min(int v0, int v1) {
  if (v0 <= v1)
    return v0;
  return v1;
}

int GUI_MEMDEV_Draw(GUI_RECT* pRect, GUI_CALLBACK_VOID_P* pfDraw, void* pData, int NumLines, int Flags) {
  int x0,y0, x1, y1, xsize, ysize;
  GUI_MEMDEV_Handle hMD;
  if (pRect) {
    x0 = (pRect->x0 < 0) ? 0 : pRect->x0;
    y0 = (pRect->y0 < 0) ? 0 : pRect->y0;
    x1 = Min(pRect->x1, LCD_GET_XSIZE()-1);
    y1 = Min(pRect->y1, LCD_GET_YSIZE()-1);
    xsize = x1-x0+1;
    ysize = y1-y0+1;
  } else {
    x0 = 0;
    y0 = 0;
    xsize = LCD_GET_XSIZE();
    ysize = LCD_GET_YSIZE();
  }
  if (NumLines == 0) {
    NumLines = -ysize;   /* Request <ysize> lines ... Less is o.k. */
  }
  if ((xsize<=0) || (ysize<=0))
    return 0;           /* Nothing to do ... */
/* Create memory device */
  hMD = GUI_MEMDEV_CreateEx(x0,y0, xsize, NumLines, Flags);
  if (!hMD) {
    GUI_DEBUG_ERROROUT("GUI_MEMDEV_Draw() Not enough memory ...");            /* Not enough memory ! */
    pfDraw(pData);
    return 1;
  }
  NumLines = GUI_MEMDEV_GetYSize(hMD);
  GUI_MEMDEV_Select(hMD);
/* Start drawing ... */
  {
    int i;
    for (i=0; i< ysize; i+=NumLines) {
      int RemLines = ysize-i;
      if (RemLines<NumLines) {
        GUI_MEMDEV_ReduceYSize(hMD, RemLines);
      }
      if (i) {
        GUI_MEMDEV_SetOrg(hMD, x0, y0+i);
        GUI_MEMDEV_Clear(hMD);
      }
      pfDraw(pData);
      GUI_MEMDEV_CopyToLCD(hMD);
    }
  }
  GUI_MEMDEV_Delete(hMD);
  GUI_MEMDEV_Select(0);
  return 0;             /* Success ! */
}

#else

void GUIDEV_Banding(void) {} /* avoid empty object files */

#endif /* GUI_MEMDEV_SUPPORT */
