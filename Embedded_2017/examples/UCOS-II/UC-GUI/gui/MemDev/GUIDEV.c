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
File        : GUIDev.C
Purpose     : Implementation of memory devices
---------------------------END-OF-HEADER------------------------------
*/


#include <string.h>
#include "GUI_Private.H"
#include "GUIDebug.h"

/* Memory device capabilities are compiled only if support for them is enabled.*/ 
#if GUI_SUPPORT_MEMDEV


/*
        *********************************************************
        *                                                       *
        *                Macros                                 *
        *                                                       *
        *********************************************************
*/

#define POS_AUTO -4095   /* Position value for auto-pos */

/*
  ********************************************************************
  *
  *                  ID translation table
  *
  ********************************************************************

This table contains 0, 1, 2, ... and serves as translation table for DDBs

*/

#define INTS(Base)  Base+0,Base+1,Base+2,Base+3,Base+4,Base+5,   \
                    Base+6,Base+7,Base+8,Base+9,Base+10,Base+11, \
                    Base+12,Base+13,Base+14,Base+15

static const LCD_PIXELINDEX aID[] = {
  INTS(0)
};


/*
        *********************************************************
        *                                                       *
        *           internal routines                           *
        *                                                       *
				*     (not part of interface table)                     *
        *                                                       *
        *********************************************************
*/

LCD_PIXELINDEX* GUI_MEMDEV_XY2PTR(int x,int y) {
  GUI_MEMDEV* pDev = GUI_MEMDEV_h2p(GUI_Context.hDevData);
  U8 *pData = (U8*)(pDev+1);
  #if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
    if ((x >= pDev->x0+pDev->XSize) | (x<pDev->x0) | (y >= pDev->y0+pDev->YSize) | (y<pDev->y0)) {
      GUI_DEBUG_ERROROUT2("GUI_MEMDEV_XY2PTR: parameters out of bounds",x,y);
    }
  #endif
  pData += (y- pDev->y0) * pDev->BytesPerLine;
  return ((LCD_PIXELINDEX*)pData) + x - pDev->x0;
}




/*
        *********************************************************
        *                                                       *
        *          Draw Bitmap 1 BPP                            *
        *                                                       *
        *********************************************************
*/

static void  DrawBitLine1BPP(GUI_USAGE* pUsage, int x, int y, U8 const*p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  LCD_PIXELINDEX pixels;
  LCD_PIXELINDEX Index0 = *(pTrans+0);
  LCD_PIXELINDEX Index1 = *(pTrans+1);
  LCD_PIXELINDEX* pData;
  U8  PixelCnt;
  GUI_MEMDEV* pDev = GUI_MEMDEV_h2p(GUI_Context.hDevData);
  PixelCnt = 8- (Diff&7);
  pixels = (*p) << (Diff&7);
  pData = GUI_MEMDEV_XY2PTR(x,y);
  GUI_DEBUG_ERROROUT3_IF( x < pDev->x0, "GUIDEV.c: DrawBitLine1BPP, Act= %d, Border= %d, Clip= %d"
                    ,x,pDev->x0, GUI_Context.ClipRect.x0);
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS|LCD_DRAWMODE_XOR)) {
  case 0:    /* Write mode */
  PixelLoopWrite:
    if (PixelCnt>xsize)
      PixelCnt =xsize;
    xsize -= PixelCnt;
    do {
      *pData++ = (pixels&0x80) ? Index1 : Index0;
      pixels<<=1;
    } while (--PixelCnt);
    if (xsize) {
      PixelCnt=8;
      pixels = *(++p);
      goto PixelLoopWrite;
    }
    break;
  case LCD_DRAWMODE_TRANS:
  PixelLoopTrans:
    if (PixelCnt>xsize)
      PixelCnt =xsize;
    xsize -= PixelCnt;
    do {
      if ((pixels&0x80)) {
        if (pUsage)
          GUI_USAGE_AddPixel(pUsage, x,y);
        *pData = Index1;
      }
      x++;
      pData++;
      pixels<<=1;
    } while (--PixelCnt);
    if (xsize) {
      PixelCnt=8;
      pixels = *(++p);
      goto PixelLoopTrans;
    }
    break;
  case LCD_DRAWMODE_XOR:;
  PixelLoopXor:
    if (PixelCnt>xsize)
      PixelCnt =xsize;
    xsize -= PixelCnt;
    do {
      if ((pixels&0x80))
        *pData = pDev->NumColors - 1 - *pData;
      pData++;
      pixels<<=1;
    } while (--PixelCnt);
    if (xsize) {
      PixelCnt=8;
      pixels = *(++p);
      goto PixelLoopXor;
    }
    break;
  }
}

/*
        *********************************************************
        *                                                       *
        *          Draw Bitmap 2 BPP                            *
        *                                                       *
        *********************************************************
*/

static void  DrawBitLine2BPP(GUI_USAGE* pUsage, int x, int y, U8 const*p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  U8 pixels;
  U8  PixelCnt;
  LCD_PIXELINDEX* pData;
  PixelCnt = 4- (Diff&3);
  pixels = (*p) << ((Diff&3)<<1);
  pData = GUI_MEMDEV_XY2PTR(x,y);
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS|LCD_DRAWMODE_XOR)) {
  case 0:    /* Write mode */
  PixelLoopWrite:
    if (PixelCnt>xsize) {
      PixelCnt =xsize;
    }
    xsize -= PixelCnt;
    do {
      *pData++ = *(pTrans + (pixels>>6));
      pixels<<=2;
    } while (--PixelCnt);
    if (xsize) {
      PixelCnt=4;
      pixels = *(++p);
      goto PixelLoopWrite;
    }
    break;
  case LCD_DRAWMODE_TRANS:
  PixelLoopTrans:
    if (PixelCnt>xsize)
      PixelCnt =xsize;
    xsize -= PixelCnt;
    do {
      if (pixels&0xc0) {
        *pData = *(pTrans + (pixels>>6));
        GUI_USAGE_AddPixel(pUsage, x,y);
      }
      pData++;
      pixels<<=2;
    } while (--PixelCnt);
    if (xsize) {
      PixelCnt=4;
      pixels = *(++p);
      goto PixelLoopTrans;
    }
    break;
  case LCD_DRAWMODE_XOR:;
  PixelLoopXor:
    if (PixelCnt>xsize)
      PixelCnt =xsize;
    xsize -= PixelCnt;
    do {
      if ((pixels&0xc0))
        *pData ^= 255;
      pData++;
      pixels<<=2;
    } while (--PixelCnt);
    if (xsize) {
      PixelCnt=4;
      pixels = *(++p);
      goto PixelLoopXor;
    }
    break;
  }
}

/*
        *********************************************************
        *                                                       *
        *          Draw Bitmap 4 BPP                            *
        *                                                       *
        *********************************************************
*/

static void  DrawBitLine4BPP(GUI_USAGE* pUsage, int x, int y, U8 const*p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  U8 pixels;
  LCD_PIXELINDEX* pData;
  U8  PixelCnt;
  PixelCnt = 2- (Diff&1);
  pixels = (*p) << ((Diff&1)<<2);
  pData = GUI_MEMDEV_XY2PTR(x,y);
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS|LCD_DRAWMODE_XOR)) {
/*
          * Write mode *
*/
  case 0:
    /* Draw incomplete bytes to the left of center area */
    if (Diff) {
      *pData = *(pTrans + (pixels >>4));
      pData++;
      xsize--;
      pixels = *++p;
    }
    /* Draw center area (2 pixels in one byte) */
    if (xsize >= 2) {
      int i = xsize>>1;
      xsize &= 1;
      do {
        *pData     = *(pTrans + (pixels>>4));   /* Draw 1. (left) pixel */
        *(pData+1) = *(pTrans + (pixels&15));   /* Draw 2. (right) pixel */
        pData +=2;
        pixels = *++p;
      } while (--i);
    }
    /* Draw incomplete bytes to the right of center area */
    if (xsize) {
      *pData = * (pTrans + (pixels >> 4));
    }
    break;
/*
          * Transparent draw mode *
*/
  case LCD_DRAWMODE_TRANS:
    /* Draw incomplete bytes to the left of center area */
    if (Diff) {
      if (pixels&0xF0) {
        *pData = *(pTrans + (pixels>>4));
        if (pUsage)
          GUI_USAGE_AddPixel(pUsage, x,y);
      }
      pData++;
      x++;
      xsize--;
      pixels = *++p;
    }
    /* Draw center area (2 pixels in one byte) */
    while (xsize >= 2) {
      /* Draw 1. (left) pixel */
      if (pixels&0xF0) {
        *pData = *(pTrans + (pixels>>4));
        if (pUsage)
          GUI_USAGE_AddPixel(pUsage, x,y);
      }
      /* Draw 2. (right) pixel */
      if (pixels &= 15) {
        *(pData+1) = *(pTrans + pixels);
        if (pUsage)
          GUI_USAGE_AddPixel(pUsage, x+1,y);
      }
      pData +=2;
      x+=2;
      xsize-=2;
      pixels = *++p;
    }
    /* Draw incomplete bytes to the right of center area */
    if (xsize) {
      if (pixels >>= 4) {
        *pData = *(pTrans + pixels);
        if (pUsage)
          GUI_USAGE_AddPixel(pUsage, x,y);
      }
    }
    break;
  case LCD_DRAWMODE_XOR:;
  PixelLoopXor:
    if (PixelCnt>xsize)
      PixelCnt =xsize;
    xsize -= PixelCnt;
    do {
      if ((pixels&0xc0))
        *pData ^= 255;
      pData++;
      pixels<<=4;
    } while (--PixelCnt);
    if (xsize) {
      PixelCnt=2;
      pixels = *(++p);
      goto PixelLoopXor;
    }
    break;
  }
}

/*
        *********************************************************
        *                                                       *
        *          Draw Bitmap 8 BPP Trans                      *
        *                                                       *
        *********************************************************
*/

static void  DrawBitLine8BPP(GUI_USAGE* pUsage, int x, int y, U8 const*pSrc, int xsize, const LCD_PIXELINDEX*pTrans) {
  LCD_PIXELINDEX* pDest;
  pDest = GUI_MEMDEV_XY2PTR(x,y);
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS|LCD_DRAWMODE_XOR)) {
  case 0:    /* Write mode */
    do {
      *pDest = *(pTrans + *pSrc);
      pDest++;
      pSrc++;
    } while (--xsize);
    break;
  case LCD_DRAWMODE_TRANS:
    do {
      if (*pSrc) {
        *pDest = *(pTrans + *pSrc);
        GUI_USAGE_AddPixel(pUsage, x,y);
      }
      x++;
      pDest++;
      pSrc++;
    } while (--xsize);
    break;
  }
}

/*
        *********************************************************
        *                                                       *
        *          Draw Bitmap 8 BPP No Trans                   *
        *                                                       *
        *********************************************************
*/

static void  DrawBitLine8BPP_DDB(GUI_USAGE* pUsage, int x, int y, U8 const*pSrc, int xsize) {
  LCD_PIXELINDEX* pDest;
  pDest = GUI_MEMDEV_XY2PTR(x,y);
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS|LCD_DRAWMODE_XOR)) {
  case 0:    /* Write mode */
    #if LCD_BITSPERPIXEL <=8
      memcpy(pDest, pSrc, xsize);
    #else
      *pDest = *pSrc;
      while (--xsize) {
        *++pDest = *++pSrc;
      }
    #endif
    break;
  case LCD_DRAWMODE_TRANS:
    do {
      if (*pSrc) {
        *pDest = *pSrc;
        GUI_USAGE_AddPixel(pUsage, x,y);
      }
      x++;
      pDest++;
      pSrc++;
    } while (--xsize);
    break;
  }
}

/********************************************************
*
*          Draw Bitmap 16 BPP DDB
*
*********************************************************
*/

#if LCD_BITSPERPIXEL >8
static void  DrawBitLine16BPP_DDB(GUI_USAGE* pUsage, int x, int y, const U16 *pSrc, int xsize) {
  LCD_PIXELINDEX* pDest;
  pDest = GUI_MEMDEV_XY2PTR(x,y);
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS|LCD_DRAWMODE_XOR)) {
  case 0:    /* Write mode */
    memcpy(pDest, pSrc, xsize*2);
    break;
  case LCD_DRAWMODE_TRANS:
    do {
      if (*pSrc) {
        *pDest = *pSrc;
        GUI_USAGE_AddPixel(pUsage, x,y);
      }
      x++;
      pDest++;
      pSrc++;
    } while (--xsize);
    break;
  }
}
#endif
/*
        *********************************************************
        *                                                       *
        *         Universal draw Bitmap routine                 *
        *                                                       *
        *********************************************************
*/

static void _DrawBitmap   (int x0, int y0,
                       int xsize, int ysize,
                       int BitsPerPixel, 
                       int BytesPerLine,
                       const U8* pData, int Diff,
                       const LCD_PIXELINDEX* pTrans)
{
  int i;
  GUI_MEMDEV * pDev = GUI_MEMDEV_h2p(GUI_Context.hDevData);
  GUI_USAGE* pUsage = (pDev->hUsage) ? GUI_USAGE_h2p(pDev->hUsage) : 0;
  /* Mark all affected pixels dirty unless transparency is set */
  if (pUsage) {
    if ((GUI_Context.DrawMode & LCD_DRAWMODE_TRANS) ==0) {
      for (i=0; i<ysize; i++) {
        GUI_USAGE_AddHLine(pUsage, x0+Diff,y0+i,xsize);
      }
    }
  }
  /* Handle 8 bpp bitmaps seperately as we have different routine bitmaps with or without palette */
  x0+=Diff;
  /* handle 16 bpp bitmaps in high color modes, but only without palette */
  #if LCD_BITSPERPIXEL >8
    if (BitsPerPixel==16) {
      for (i=0; i<ysize; i++) {
        DrawBitLine16BPP_DDB(pUsage, x0, i+y0, (U16*)pData, xsize);
        pData += BytesPerLine;
      }
      return;
    }
  #endif
  /* handle 8 bpp bitmaps */
  if (BitsPerPixel==8) {
    for (i=0; i<ysize; i++) {
      if (pTrans) {
        DrawBitLine8BPP(pUsage, x0, i+y0, pData, xsize, pTrans);
      } else {
        DrawBitLine8BPP_DDB(pUsage, x0, i+y0, pData, xsize);
      }
      pData += BytesPerLine;
    }
    return;
  }
  /* Use aID for bitmaps without palette */
  if (!pTrans) {
    pTrans = aID;
  }
  for (i=0; i<ysize; i++) {
    switch (BitsPerPixel) {
    case 1:
      DrawBitLine1BPP(pUsage, x0, i+y0, pData, Diff, xsize, pTrans);
      break;
    case 2:
      DrawBitLine2BPP(pUsage, x0, i+y0, pData, Diff, xsize, pTrans);
      break;
    case 4:
      DrawBitLine4BPP(pUsage, x0, i+y0, pData, Diff, xsize, pTrans);
      break;
    }
    pData += BytesPerLine;
  }

}


static void _DrawHLine    (int x0, int y,  int x1) {
  GUI_MEMDEV * pDev = GUI_MEMDEV_h2p(GUI_Context.hDevData);
  GUI_USAGE_h hUsage = pDev->hUsage; 
  if (hUsage)
    GUI_USAGE_AddHLine(GUI_USAGE_h2p(hUsage), x0,y,x1-x0+1);
  {
    int len = x1-x0+1;
    LCD_PIXELINDEX* pData = GUI_MEMDEV_XY2PTR(x0,y);
    if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
      int NumColorsM1 = pDev->NumColors-1;
      do {
        *pData = NumColorsM1 - *pData;
        pData++;
      } while (--len);
    } else {  /* Fill */
      #if LCD_BITSPERPIXEL <=8
        memset (pData, LCD_COLORINDEX, len);
      #else
        *pData = LCD_COLORINDEX;   /* We write at least one pixel, so this is permitted ...
                                  (speed optimization) */
        while (--len) {
          *++pData = LCD_COLORINDEX;
        }
      #endif
    }
  }
}

static void _DrawVLine    (int x , int y0,  int y1) {
  GUI_MEMDEV * pDev = GUI_MEMDEV_h2p(GUI_Context.hDevData);
  GUI_USAGE_h hUsage = pDev->hUsage; 
  GUI_USAGE*  pUsage = hUsage ? GUI_USAGE_h2p(hUsage) : NULL;
  int NumColorsM1 = pDev->NumColors-1;
  LCD_PIXELINDEX* pData = GUI_MEMDEV_XY2PTR(x,y0);
  do {
    if (hUsage)
      GUI_USAGE_AddPixel(pUsage, x,y0);
    if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR)
      *pData = NumColorsM1 - *pData;
    else
      *pData = LCD_COLORINDEX;
    #if LCD_BITSPERPIXEL <= 8
      pData += pDev->BytesPerLine;
    #else
      pData += pDev->BytesPerLine>>1;
    #endif
  } while (++y0<=y1);
}

static void _SetPixelIndex (int x, int y, int Index){
  GUI_MEMDEV * pDev = GUI_MEMDEV_h2p(GUI_Context.hDevData);
  GUI_USAGE_h hUsage = pDev->hUsage; 
  LCD_PIXELINDEX* pData = GUI_MEMDEV_XY2PTR(x,y);
  *pData = Index;
  if (hUsage) {
    GUI_USAGE*  pUsage = GUI_USAGE_h2p(hUsage);
    GUI_USAGE_AddPixel(pUsage, x,y);
  }
}

static void _XorPixel (int x, int y) {
  GUI_MEMDEV * pDev = GUI_MEMDEV_h2p(GUI_Context.hDevData);
  GUI_USAGE_h hUsage = pDev->hUsage; 
  LCD_PIXELINDEX* pData = GUI_MEMDEV_XY2PTR(x,y);
  *pData = pDev->NumColors - 1-*pData;
  if (hUsage) {
    GUI_USAGE*  pUsage = GUI_USAGE_h2p(hUsage);
    GUI_USAGE_AddPixel(pUsage, x,y);
  }
}

static unsigned int _GetPixelIndex (int x, int y){
  LCD_PIXELINDEX* pData = GUI_MEMDEV_XY2PTR(x,y);
  return *pData;
}

static void _FillRect     (int x0, int y0, int x1, int y1){
  for (; y0 <= y1; y0++) {
    _DrawHLine(x0,y0, x1);
  }
}



static void _GetRect  (GUI_RECT* pRect) {
  GUI_MEMDEV * pDev = GUI_MEMDEV_h2p(GUI_Context.hDevData);
  pRect->x0 = pDev->x0;
  pRect->y0 = pDev->y0;
  pRect->x1 = pDev->x0 + pDev->XSize-1;
  pRect->y1 = pDev->y0 + pDev->YSize-1;
}

static  unsigned int _Color2Index (LCD_COLOR Color) {
  GUI_MEMDEV * pDev = GUI_MEMDEV_h2p(GUI_Context.hDevData);
  return pDev->pfColor2Index(Color);
}

static  LCD_COLOR _Index2Color (int Index) {
  GUI_MEMDEV * pDev = GUI_MEMDEV_h2p(GUI_Context.hDevData);
  return pDev->pfIndex2Color(Index);
}

/*********************************************************************
*
*             Device structure
*
**********************************************************************
*/
static const tLCDDEV_APIList _APIList = {
  _Color2Index,
  _DrawBitmap,
  _DrawHLine,
  _DrawVLine,
  _FillRect,
  _GetPixelIndex,
  _GetRect,
  _Index2Color,
  _SetPixelIndex,
  _XorPixel
};


/*
  *********************************************************
  *
  *            Exported routines
  *
  *********************************************************

*/

/*
      *************************************************
      *                                               *
      *             Delete                            *
      *                                               *
      *************************************************
*/
void GUI_MEMDEV_Delete(GUI_MEMDEV_Handle hMemDev) {
/* Make sure memory device is not used */
  GUI_LOCK();
  if (hMemDev) {
    GUI_MEMDEV* pDev;
    if (GUI_Context.hDevData == hMemDev) {
	    GUI_SelectLCD();
    }
    pDev = GUI_MEMDEV_h2p(hMemDev);
    /* Delete the associated usage device */
    if (pDev->hUsage)
      GUI_USAGE_DecUseCnt(pDev->hUsage);
    GUI_ALLOC_FREE(hMemDev);
  }
  GUI_UNLOCK();
}

/************************************************
*
*             CreateEx
*
*************************************************
*/

GUI_MEMDEV_Handle GUI_MEMDEV_CreateEx (int x0, int y0, int xsize, int ysize, int Flags) {
  I32 MemSize;
  GUI_USAGE_Handle hUsage =0;
  #if LCD_BITSPERPIXEL <= 8
    int BytesPerLine = (( 8*xsize+15)>>4)<<1;  /* Reserve 8 bits for pixels */
  #else
    int BytesPerLine = ((16*xsize+15)>>4)<<1;  /* Reserve 16 bits for pixels */
  #endif
  GUI_MEMDEV_Handle hMemDev;
  /* Calc avaliable MemSize */
  MemSize = GUI_ALLOC_GetMaxSize();
  if (!(Flags & GUI_MEMDEV_NOTRANS)) {
    MemSize = (MemSize/4)*3;   /* We need to reserve some memory for usage object */
  }
  if (ysize<=0) {
    int MaxLines = (MemSize-sizeof(GUI_MEMDEV))/BytesPerLine;
    ysize = (MaxLines >-ysize) ? -ysize : MaxLines;
  }
  if (!(Flags & GUI_MEMDEV_NOTRANS)) {
    /* Create the usage map */
    hUsage = GUI_USAGE_BM_Create(x0, y0, xsize, ysize, 0);
  }
  /* Check if we can alloc sufficient memory */
  if (ysize <= 0) {
    GUI_DEBUG_WARN("GUI_MEMDEV_Create: Too little memory");
    return 0;    
  }
  MemSize = ysize*BytesPerLine +sizeof(GUI_MEMDEV);
  hMemDev = GUI_ALLOC_ALLOC(MemSize);
  if (hMemDev) {
    GUI_MEMDEV* pDevData = GUI_MEMDEV_h2p(hMemDev);
    pDevData->x0    = x0;
    pDevData->y0    = y0;
    pDevData->XSize = xsize;
    pDevData->YSize = ysize;
    pDevData->NumColors = LCD_GET_NUMCOLORS();
    pDevData->BytesPerLine= BytesPerLine;
    pDevData->hUsage = hUsage;
    pDevData->pfColor2Index = GUI_Context.pDeviceAPI->pfColor2Index;    
    pDevData->pfIndex2Color = GUI_Context.pDeviceAPI->pfIndex2Color;
  } else {
    GUI_DEBUG_WARN("GUI_MEMDEV_Create: Alloc failed");
  }
  return hMemDev;
}

/************************************************
*
*             Create
*
*************************************************
*/

GUI_MEMDEV_Handle GUI_MEMDEV_Create (int x0, int y0, int xsize, int ysize) {
  return GUI_MEMDEV_CreateEx(x0, y0, xsize, ysize, GUI_MEMDEV_HASTRANS);
}


/************************************************
*
*             Select
*
*************************************************
*/


void GUI_MEMDEV_Select(GUI_MEMDEV_Handle hMem) {
  if (hMem==0) {
    GUI_SelectLCD();
  } else {
    #if GUI_WINSUPPORT
      WM_Deactivate();
    #endif
    /* If LCD was selected Save cliprect */
    if (GUI_Context.hDevData == 0)
      GUI_Context.ClipRectPrev = GUI_Context.ClipRect;
    GUI_Context.hDevData = hMem;
    GUI_Context.pDeviceAPI  = &_APIList;
    LCD_SetClipRectMax();
  }
}


/*
      *************************************************
      *                                               *
      *             CopyToLCDAt                       *
      *                                               *
      *************************************************
*/
#if LCD_BITSPERPIXEL <=8
  #define BITSPERPIXEL 8
#else
  #define BITSPERPIXEL 16
#endif
#define BYTESPERLINE (BITSPERPIXEL/8)

static void _CopyToLCDAt(GUI_MEMDEV_Handle hMem,int x, int y) {
  /* Make sure the memory handle is valid */
  if (!hMem) {
    return;
  }
  {
    GUI_MEMDEV * pDev = GUI_MEMDEV_h2p(hMem);
    GUI_USAGE_h hUsage = pDev->hUsage; 
    GUI_USAGE*  pUsage;
    int YSize = pDev->YSize;
    int yi;
    int BytesPerLine = pDev->BytesPerLine;
    U8 * pData = (U8*)(pDev+1);
    if (hUsage) {
      pUsage = GUI_USAGE_h2p(hUsage);
      for (yi = 0; yi < YSize; yi++) {
        int xOff = 0;
        int XSize;
        XSize = GUI_USAGE_GetNextDirty(pUsage, &xOff, yi);
        if (XSize == pDev->XSize) {
          /* If the entire line is affected, calculate the number of entire lines */
          int y0 = yi;
          while ((GUI_USAGE_GetNextDirty(pUsage, &xOff, yi + 1)) == XSize) {
            yi++;
          }
		      LCD_DrawBitmap(x, y + y0, pDev->XSize, yi - y0 + 1,
                         1, 1,
                         BITSPERPIXEL,
                         BytesPerLine, pData, NULL);
          pData += (yi - y0 + 1) * BytesPerLine;
        } else {
          /* Draw the partial line which needs to be drawn */
          for (; XSize; ) {
            LCD_DrawBitmap(x + xOff, y + yi, XSize, 1, 
                           1, 1, 
                           BITSPERPIXEL, 
                           BytesPerLine, pData + xOff * BYTESPERLINE, NULL);
            xOff += XSize;
            XSize = GUI_USAGE_GetNextDirty(pUsage, &xOff, yi);
          }
          pData += BytesPerLine;
        }
      }
    } else {
		  LCD_DrawBitmap(x, y, pDev->XSize, YSize,
                     1, 1,
                     BITSPERPIXEL,
                     BytesPerLine, pData, NULL);
    }
  }
  GUI_ALLOC_UNLOCK(hMem);
}

#if (GUI_WINSUPPORT)
void GUI_MEMDEV_CopyToLCDAt(GUI_MEMDEV_Handle hMem, int x, int y) {
  if (hMem) {
    WM_LOCK(); {
      GUI_MEMDEV_Handle hMemPrev = GUI_Context.hDevData;
      GUI_MEMDEV* pDevData = (GUI_MEMDEV*) GUI_ALLOC_LOCK(hMem);  /* Convert to pointer */
      GUI_RECT r;
      /* Make sure LCD is selected as device */
      if (hMemPrev) {
        GUI_MEMDEV_Select(0);  /* Activate LCD */
      }
      if (x==POS_AUTO) {
        x = pDevData->x0;
        y = pDevData->y0;
      }
      /* Calculate rectangle */
      r.x1 = (r.x0 = x) + pDevData->XSize-1;
      r.y1 = (r.y0 = y) + pDevData->YSize-1;;
      /* Do the drawing. WIndow manager has to be on */
      WM_Activate();
      WM_ITERATE_START(&r) {
        _CopyToLCDAt(hMem,x,y);
      } WM_ITERATE_END();
      /* Reactivate previously used device */
      GUI_MEMDEV_Select(hMemPrev);
    } WM_UNLOCK();
  }
}
#else
void GUI_MEMDEV_CopyToLCDAt(GUI_MEMDEV_Handle hMem,int x, int y) {
  GUI_MEMDEV_Handle hMemPrev = GUI_Context.hDevData;
  GUI_MEMDEV* pDevData = (GUI_MEMDEV*) GUI_ALLOC_LOCK(hMem);  /* Convert to pointer */
  /* Make sure LCD is selected as device */
  if (hMemPrev) {
    GUI_MEMDEV_Select(0);  /* Activate LCD */
  }
  if (x==POS_AUTO) {
    x = pDevData->x0;
    y = pDevData->y0;
  }
  _CopyToLCDAt(hMem,x,y);
  /* Reactivate previously used memory device */
  if (hMemPrev) {
    GUI_MEMDEV_Select(hMemPrev);
  }
}

#endif
/*
      *************************************************
      *                                               *
      *             CopyToLCD                         *
      *                                               *
      *************************************************
*/
void GUI_MEMDEV_CopyToLCD(GUI_MEMDEV_Handle hMem) {
  GUI_MEMDEV_CopyToLCDAt(hMem, POS_AUTO, POS_AUTO);
}

#else

void GUIDEV(void) {}

#endif /* GUI_SUPPORT_MEMDEV && (LCD_BITSPERPIXEL <= 8) */
