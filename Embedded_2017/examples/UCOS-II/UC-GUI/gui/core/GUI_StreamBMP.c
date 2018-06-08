/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 2002         SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

**** emWin/GSC Grafical user interface for embedded applications ****
emWin is protected by international copyright laws. Knowledge of the
source code may not be used to write a similar product. This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUI_StreamBMP.C
Purpose     : Draw stream data bitmaps
---------------------------END-OF-HEADER------------------------------
*/


#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Private.H"
#include "GUIDebug.h"

#define BI_RGB  0   /* Windows define */


static void StreamU16 (U16 Data, GUI_CALLBACK_VOID_U8_P* pfStream, void* p) {
  (*pfStream) (Data,      p);
  (*pfStream) (Data >> 8, p);
}

static void StreamU32 (U32 Data, GUI_CALLBACK_VOID_U8_P* pfStream, void* p) {
  StreamU16(Data, pfStream, p);
  StreamU16(Data >> 16, pfStream, p);
}


/************************************************
*                                               *
*             Draw  point                       *
*                                               *
*************************************************
*/
 
void GUI_StreamBMP (GUI_RECT* pRect, GUI_CALLBACK_VOID_U8_P* pfStream, void *p) {
  GUI_RECT r;
  int i, x, y, BPP;
  int NumColors;
  U32 Size;
  GUI_LOCK();
  if (pRect) {
    r = *pRect;
  } else {
    r.x0 = r.y0 = 0;
    r.x1 = LCD_GetXSize() -1;
    r.y1 = LCD_GetYSize() -1;
  }
  Size = (r.x1 - r.x0 + 1) * (r.y1 - r.y0 + 1);
  BPP = LCD_GetBitsPerPixel();
  NumColors = (BPP <= 8) ? (1 << BPP) : 0;
/* Save Bitmap fileheader : BITMAPFILEHEADER : 14 bytes */
  (*pfStream) ('B', p);             /* WORD Type */
  (*pfStream) ('M', p);
  StreamU32(Size, pfStream, p);     /* DWORD bfSize */
  StreamU32(0, pfStream, p);        /*  WORD aReserved[2]: Has to be 0 */
  StreamU32(0x76, pfStream, p);     /* DWORD bfOffBits: Offset to bits (constant) */
/* BITMAPINFOHEADER: 40 bytes */
  StreamU32(0x28, pfStream, p);     /* DWORD sizeof(BITMAPINFOHEADER) */
  StreamU32(r.x1 - r.x0 +1, pfStream, p);  /* I32    biWidth */
  StreamU32(r.y1 - r.y0 +1, pfStream, p);  /* I32    biHeigth */
  StreamU16(1, pfStream, p);               /* WORD   biPlanes; */
  StreamU16(BPP, pfStream, p); /* WORD   biBitCount */
  StreamU32(BI_RGB, pfStream, p);          /*    DWORD  biCompression; */
  StreamU32(0, pfStream, p);               /*    DWORD  biSizeImage; (may be 0 for BI_RGB) */
  StreamU32(0, pfStream, p);               /*    LONG   biXPelsPerMeter; */
  StreamU32(0, pfStream, p);               /*    LONG   biYPelsPerMeter; */ 
  StreamU32(0, pfStream, p);               /*    DWORD  biClrUsed;  0 means max. number fitting into bits */
  StreamU32(0, pfStream, p);               /*    DWORD  biClrImportant;  0 means all colors are required  */
/* RGBQuads */
  for (i = 0; i < NumColors; i++) {
    LCD_COLOR Color;
    Color = GUI_Index2Color(i);
    StreamU32(Color, pfStream, p);
  }
/* Store indices */
  for (y = r.y0; y <= r.y1; y++) {
    for (x = r.x0; x <= r.x1; x++) {
      U8 Data;
      Data = LCD_L0_GetPixelIndex(x, y);
      (*pfStream) (Data, p);
    }
  }  
  GUI_UNLOCK();
}

