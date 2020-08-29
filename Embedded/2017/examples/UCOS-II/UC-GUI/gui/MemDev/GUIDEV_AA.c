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
File        : GUIDevAA.C
Purpose     : Memory device drawing with Antialiasing
----------------------------------------------------------------------
Version-Date---Author-Explanation
----------------------------------------------------------------------
1.02    000804 RS     LCD_CopyFromLCDAA added
1.00a   000804 RS     Fix for odd X-sizes
1.00    000728 RS     First release
----------------------------------------------------------------------
Known problems or limitations with current version
----------------------------------------------------------------------
None.
---------------------------END-OF-HEADER------------------------------
*/


#include "GUI_Private.h"
#include <string.h>

#if GUI_SUPPORT_MEMDEV

/*
        *********************************************************
        *                                                       *
        *              Check config                             *
        *                                                       *
        *********************************************************
*/

/*
        *********************************************************
        *                                                       *
        *                Macros                                 *
        *                                                       *
        *********************************************************
*/

#define SETPIXEL(x,y,colorindex) _SetPixel(x,y,colorindex);
#define BKCOLORINDEX GUI_Context.pDevData->aColorIndex[0]
#define   COLORINDEX GUI_Context.pDevData->aColorIndex[1]



/*
      *************************************************
      *                                               *
      *             CopyToLCDAA                       *
      *                                               *
      *************************************************
*/

void GUI_MEMDEV_CopyToLCDAA(GUI_MEMDEV_Handle hMem) {
  /* Make sure memory handle is valid */
  if (hMem) {
    int x,y;
    static const tLCDDEV_APIList* pDevicePrev;
    GUI_MEMDEV* pDev = (GUI_MEMDEV*)GUI_ALLOC_LOCK(hMem);  /* Convert to pointer */
    LCD_PIXELINDEX* pData0 = (LCD_PIXELINDEX*)(pDev+1);
    int LineOff = pDev->XSize;
    int x0 = pDev->x0;
    int y0 = pDev->y0;
    int XMax = pDev->XSize/2;
    int YMax = pDev->YSize/2;
    pDevicePrev = GUI_Context.pDeviceAPI; /* Remember list ptr (for restore) */
    GUI_Context.pDeviceAPI = &LCD_L0_APIList;
    LCD_SetClipRectMax();
    for (y=0; y< YMax; y++) {
      LCD_PIXELINDEX* pData = pData0;
      for (x=0; x< XMax; x++) {
        LCD_PIXELINDEX PixelIndex;
        int ColorSep[3];
        U32 Color = LCD_Index2Color(*pData);
        ColorSep[0] = Color&255;
        ColorSep[1] = (Color>>8)  &255;
        ColorSep[2] = (Color>>16) &255;
        Color = LCD_Index2Color(*(pData+1));
        ColorSep[0] += Color&255;
        ColorSep[1] += (Color>>8)  &255;
        ColorSep[2] += (Color>>16) &255;
        Color = LCD_Index2Color(*(pData+LineOff));
        ColorSep[0] += Color&255;
        ColorSep[1] += (Color>>8)  &255;
        ColorSep[2] += (Color>>16) &255;
        Color = LCD_Index2Color(*(pData+LineOff+1));
        ColorSep[0] += Color&255;
        ColorSep[1] += (Color>>8)  &255;
        ColorSep[2] += (Color>>16) &255;
        Color  = (ColorSep[0]+2)>>2;
        Color |= ((ColorSep[1]+2)>>2)<<8;
        Color |= ((U32)((ColorSep[2]+2)>>2))<<16;
        PixelIndex = LCD_Color2Index(Color);
        LCD_SetPixelIndex(x+x0, y+y0, PixelIndex);
        pData+=2;
      }
      pData0 += 2*LineOff;
    }
    GUI_Context.pDeviceAPI = pDevicePrev; /* Restore API list ptr */
  }
}

/*
      *************************************************
      *                                               *
      *             CopyFromLCDAA                     *
      *                                               *
      *************************************************
*/

void GUI_MEMDEV_CopyFromLCDAA(GUI_MEMDEV_Handle hMem) {
  /* Make sure memory handle is valid */
  if (!hMem) {
    hMem = GUI_Context.hDevData;
  }
  if (hMem) {
    int x,y;
    GUI_MEMDEV* pDevData = (GUI_MEMDEV*) GUI_ALLOC_LOCK(hMem);  /* Convert to pointer */
    GUI_USAGE* pUsage = 0;
    int x0 = pDevData->x0;
    int y0 = pDevData->y0;
    int XMax = pDevData->XSize/2;
    int YMax = pDevData->YSize/2;
    LCD_PIXELINDEX* pData = (LCD_PIXELINDEX*)(pDevData+1);
    int LineOff = pDevData->BytesPerLine;
    if (pDevData->hUsage) 
      pUsage = GUI_USAGE_h2p(pDevData->hUsage);
    for (y=0; y< YMax; y++) {
      if (pUsage) {
        GUI_USAGE_AddHLine(pUsage, 0, y*2, pDevData->XSize);
        GUI_USAGE_AddHLine(pUsage, 0, y*2+1, pDevData->XSize);
      }
      for (x=0; x< XMax; x++) {
        *pData = *(pData+1) = *(pData+LineOff) = *(pData+LineOff+1) = LCD_GetPixelIndex(x+x0,y+y0);
        pData+=2;
      }
      pData += LineOff + (pDevData->XSize&1);
    }
  }
  GUI_ALLOC_UNLOCK(hMem);
}

#else

void GUIDEV_AA(void) {} /* avoid empty object files */

#endif /* GUI_MEMDEV_SUPPORT */
