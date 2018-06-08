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
File        : GUIDev_CopyFromLCD.C
Purpose     : Implementation of memory devices
----------------------------------------------------------------------
*/


#include "GUI_Private.h"
#include "GUIDebug.h"

/* Memory device capabilities are compiled only if support for them is enabled. */ 
#if GUI_SUPPORT_MEMDEV

/*******************************************************************
*
*                   Function replacement macros
*
********************************************************************
*/
#define LCD_LIMIT(Var, Op, Limit) if (Var Op Limit) Var = Limit

/**********************************************************************
*
*                        GUI_MEMDEV_CopyFromLCD
*
***********************************************************************
*/

void GUI_MEMDEV_CopyFromLCD(GUI_MEMDEV_Handle hMem) {
  /* Make sure memory handle is valid */
  if (!hMem) {
    hMem = GUI_Context.hDevData;
  }
  if (!hMem) {
    return;
  }
  {
    GUI_MEMDEV* pDevData = (GUI_MEMDEV*) GUI_ALLOC_LOCK(hMem);  /* Convert to pointer */
    LCD_RECT r;
    int y;
    int XMax;
    GUI_USAGE* pUsage = 0;
    GUI_MEMDEV_Handle hMemOld = GUI_Context.hDevData;
    GUI_MEMDEV_Select(hMem);
    if (pDevData->hUsage) 
      pUsage = GUI_USAGE_h2p(pDevData->hUsage);
    /* Get bounding rectangle */
    r.y0  = pDevData->y0;
    r.x0  = pDevData->x0;
    r.x1  = pDevData->x0 + pDevData->XSize-1;
    r.y1  = pDevData->y0 + pDevData->YSize-1;
    /* Make sure bounds are within LCD area so we can call driver directly */
    LCD_LIMIT(r.x0, <, 0);
    LCD_LIMIT(r.y0, <, 0);
    LCD_LIMIT(r.x1, >, LCD_GET_XSIZE() -1);
    LCD_LIMIT(r.y1, >, LCD_GET_YSIZE() -1);
    XMax = r.x1;
    for (y=r.y0; y<=r.y1; y++) {
      int x=r.x0;
      LCD_PIXELINDEX* pData = GUI_MEMDEV_XY2PTR(x,y);
      if (pUsage) 
        GUI_USAGE_AddHLine(pUsage, x, y, r.x1 - r.x0 + 1);
      for (; x<=XMax; x++) {
        *pData++ = LCD_L0_GetPixelIndex(x,y);
      }
    }
    GUI_MEMDEV_Select(hMemOld);
  }
  GUI_ALLOC_UNLOCK(hMem);
}

#endif /* GUI_MEMDEV_SUPPORT */
