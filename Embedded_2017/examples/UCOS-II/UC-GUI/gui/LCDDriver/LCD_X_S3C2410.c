/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              礐/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : LCDWin.C
Purpose     : Driver for Simulator under Windows
----------------------------------------------------------------------
Version-Date---Author-Explanation
----------------------------------------------------------------------
2.00    010402 RS     a) LCD_GetDevCaps removed from driver
                         (now LCD.c)
1.30c   000529 JE     a) Interface changed
1.30b   000428 RS     a) DIB class eliminated
                      b) Internal cleanups, support for high color
1.30a   000417 RS     a) Major cleanup in DIB class
1.30    000309 RS     a) Interface change for emWIn V1.30
                         (LCD_L0_SetLUTEntry, LCD_GetDevCap)
1.10a   000121 RS     a) RECTHEIGHT, RECTWIDTH modified in order to
                         fix bug which would at some time prevent
												 displaying the first line of the display.
1.10.00 000110 RS     a) Modifications in order to make it easy to
                         implement driver in any windows program
1.04.02 991118 RS     a) additional assertion added
                         LCD_MAX_LOG_COLORS
1.04.01 991018 RS     a) Support for LCD_FIXEDPALETTE added
                         with Anitaliasing enabled
1.04.00 991013 JE/RS  a) Support for LCD_FIXEDPALETTE added
                      b) Driver now accepts the same LCDConf.h as
											   the embedded system
											c) Bugfix for ..
1.02.02 990831 RS     a) Small optimization added for 16-color bitmaps
1.02.01 990726 RS     a) Transparency support for 16-color bitmpas
                         added
1.02.00 990212 RS     a) New interface version 1.02 supported
1.00    990118 RS     First release
----------------------------------------------------------------------
Known problems or limitations with current version
----------------------------------------------------------------------
---------------------------END-OF-HEADER------------------------------
*/

#include "LCD.H"
#include "LCD_Private.h"              /* include LCDConf.h */
#include "LCDSim.H"
#include "GUI_Private.h"

#include "Includes.h"

#if LCD_BITSPERPIXEL <= 8
  #define PIXELINDEX U8
#else
  #define PIXELINDEX WORD
#endif

#ifdef WIN32
  #ifndef ASSERT
    #define ASSERT(Val) \
    if (!(Val)) \
      MessageBox(NULL,"...in file "__FILE__,"Assertion failed...",MB_OK);
  #endif
#endif

#ifdef LCD_ASSERT
  #undef LCD_ASSERT
#endif
#define LCD_ASSERT(v) ASSERT(v)

#ifndef LCD_DISPLAY_INDEX
  #define LCD_DISPLAY_INDEX 0
#endif


/*
        *********************************************************
        *                                                       *
        *       Macros for internal use                         *
        *                                                       *
        *********************************************************
*/

#define SETPIXEL(x, y, c) LCDSIM_SetPixelIndex(x, y, c)
#define GETPIXEL(x, y)    LCD_GetPixel(x,y)
#define XORPIXEL(x, y)    XorPixel(x,y)

#if LCD_DISPLAY_INDEX == 1     /* Second display in a multi-display configuration */
  #define LCDSIM_SetPixelIndex  LCDSIM_1_SetPixelIndex
  #define LCDSIM_SetLUTEntry    LCDSIM_1_SetLUTEntry
#endif

/*
        *********************************************************
        *                                                       *
        *       ID translation table                            *
        *                                                       *
        *********************************************************

This table contains 0, 1, 2, ... and serves as translation table for DDBs

*/

#define INTS(Base)  Base+0,Base+1,Base+2,Base+3,Base+4,Base+5,   \
                    Base+6,Base+7,Base+8,Base+9,Base+10,Base+11, \
                    Base+12,Base+13,Base+14,Base+15

static void XorPixel   (int x, int y) {
  unsigned int Index = LCD_L0_GetPixelIndex(x,y);
  LCDSIM_SetPixelIndex(x, y, LCD_NUM_COLORS-1-Index);
}


/*
        *********************************************************
        *                                                       *
        *       LCD_L0_SetColorIndex                            *
        *       LCD_L0_SetBkColorIndex                          *
        *                                                       *
        *********************************************************
*/


#define   COLORINDEX LCD_COLORINDEX
#define BKCOLORINDEX LCD_BKCOLORINDEX

/*
        *********************************************************
        *                                                       *
        *       LCD_L0_DrawPixel                                   *
        *                                                       *
        *********************************************************

Purpose:  This routine is called by emWin. It writes 1 pixel into the
          display.

*/


void LCD_L0_DrawPixel(int x, int y) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    XORPIXEL(x, y);
  } else {
    SETPIXEL(x, y, COLORINDEX);
  }
}

/*
        *********************************************************
        *                                                       *
        *          LCD_DrawLine  vertical/horizontal            *
        *          LCD_DrawRect                                 *
        *                                                       *
        *********************************************************
*/

void LCD_L0_DrawHLine  (int x0, int y,  int x1) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    for (;x0 <= x1; x0++) {
      XORPIXEL(x0, y);
    }
  } else {
//    LCDSIM_FillLine(x0,y,x1,COLORINDEX);
    for (;x0 <= x1; x0++) {
      SETPIXEL(x0, y, COLORINDEX);
    }
  }
}

void LCD_L0_DrawVLine  (int x, int y0,  int y1) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    while (y0 <= y1) {
      XORPIXEL(x, y0);
      y0++;
    }
  } else {
    while (y0 <= y1) {
      SETPIXEL(x, y0, COLORINDEX);
      y0++;
    }
  }
}

void LCD_L0_FillRect(int x0, int y0, int x1, int y1) {
  for (; y0 <= y1; y0++) {
    LCD_L0_DrawHLine(x0,y0, x1);
  }
}



/*
  ***************************************************************
  *                                                             *
  *            Internal bitmap routines                         *
  *                                                             *
  ***************************************************************

*/


/*
    *********************************************
    *                                           *
    *      Draw Bitmap 1 BPP                    *
    *                                           *
    *********************************************
*/

static void  DrawBitLine1BPP(int x, int y, U8 const*p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  LCD_PIXELINDEX Index0 = *(pTrans+0);
  LCD_PIXELINDEX Index1 = *(pTrans+1);
  x+=Diff;
/*
// Jump to right entry point
*/
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS|LCD_DRAWMODE_XOR)) {
  case 0:    /* Write mode */
    do {
      LCDSIM_SetPixelIndex(x++,y, (*p & (0x80>>Diff)) ? Index1 : Index0);
			if (++Diff==8) {
        Diff=0;
				p++;
			}
		} while (--xsize);
    break;
  case LCD_DRAWMODE_TRANS:
    do {
  		if (*p & (0x80>>Diff))
        LCDSIM_SetPixelIndex(x,y, Index1);
      x++;
			if (++Diff==8) {
        Diff=0;
				p++;
			}
		} while (--xsize);
    break;
  case LCD_DRAWMODE_XOR:;
    do {
  		if (*p & (0x80>>Diff)) {
        int Pixel = LCDSIM_GetPixelIndex(x,y);
        LCDSIM_SetPixelIndex(x,y, LCD_NUM_COLORS-1-Pixel);
      }
      x++;
			if (++Diff==8) {
        Diff=0;
				p++;
			}
		} while (--xsize);
    break;
	}
}

/*
    *********************************************
    *                                           *
    *      Draw Bitmap 2 BPP                    *
    *                                           *
    *********************************************
*/

#if (LCD_MAX_LOG_COLORS > 2)
static void  DrawBitLine2BPP(int x, int y, U8 const*p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  PIXELINDEX pixels;
/*
// Jump to right entry point
*/
  pixels = *p;
  if (GUI_Context.DrawMode & LCD_DRAWMODE_TRANS) switch (Diff&3) {
  case 0:
    goto WriteTBit0;
  case 1:
    goto WriteTBit1;
  case 2:
    goto WriteTBit2;
  default:
    goto WriteTBit3;
  } else switch (Diff&3) {
  case 0:
    goto WriteBit0;
  case 1:
    goto WriteBit1;
  case 2:
    goto WriteBit2;
  default:
    goto WriteBit3;
  }
/*
        Write without transparency
*/
WriteBit0:
  SETPIXEL(x+0, y, *(pTrans+(pixels>>6)));
  if (!--xsize)
    return;
WriteBit1:
  SETPIXEL(x+1, y, *(pTrans+(3&(pixels>>4))));
  if (!--xsize)
    return;
WriteBit2:
  SETPIXEL(x+2, y, *(pTrans+(3&(pixels>>2))));
  if (!--xsize)
    return;
WriteBit3:
  SETPIXEL(x+3, y, *(pTrans+(3&(pixels))));
  if (!--xsize)
    return;
  pixels = *(++p);
  x+=4;
  goto WriteBit0;
/*
        Write with transparency
*/
WriteTBit0:
  if (pixels&(3<<6))
    SETPIXEL(x+0, y, *(pTrans+(pixels>>6)));
  if (!--xsize)
    return;
WriteTBit1:
  if (pixels&(3<<4))
    SETPIXEL(x+1, y, *(pTrans+(3&(pixels>>4))));
  if (!--xsize)
    return;
WriteTBit2:
  if (pixels&(3<<2))
    SETPIXEL(x+2, y, *(pTrans+(3&(pixels>>2))));
  if (!--xsize)
    return;
WriteTBit3:
  if (pixels&(3<<0))
    SETPIXEL(x+3, y, *(pTrans+(3&(pixels))));
  if (!--xsize)
    return;
  pixels = *(++p);
  x+=4;
  goto WriteTBit0;
}
#endif


/*
    *********************************************
    *                                           *
    *      Draw Bitmap 4 BPP                    *
    *                                           *
    *********************************************
*/
#if (LCD_MAX_LOG_COLORS > 4)
static void  DrawBitLine4BPP(int x, int y, U8 const*p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  U8 pixels;
/*
// Jump to right entry point
*/
  pixels = *p;
  if (GUI_Context.DrawMode & LCD_DRAWMODE_TRANS) {
    if ((Diff&1) ==0)
      goto WriteTBit0;
    goto WriteTBit1;
  } else {
    if ((Diff&1) ==0)
      goto WriteBit0;
    goto WriteBit1;
  }
/*
        Write without transparency
*/
WriteBit0:
  SETPIXEL(x+0, y, *(pTrans+(pixels>>4)));
  if (!--xsize)
    return;
WriteBit1:
  SETPIXEL(x+1, y, *(pTrans+(pixels&0xf)));
  if (!--xsize)
    return;
  x+=2;
  pixels = *(++p);
  goto WriteBit0;
/*
        Write with transparency
*/
WriteTBit0:
  if (pixels>>4)
    SETPIXEL(x+0, y, *(pTrans+(pixels>>4)));
  if (!--xsize)
    return;
WriteTBit1:
  if (pixels&0xf)
    SETPIXEL(x+1, y, *(pTrans+(pixels&0xf)));
  if (!--xsize)
    return;
  x+=2;
  pixels = *(++p);
  goto WriteTBit0;
}
#endif

/*
    *********************************************
    *                                           *
    *      Draw Bitmap 8 BPP  (256 colors)      *
    *                                           *
    *********************************************
*/


#if (LCD_MAX_LOG_COLORS > 16)
static void  DrawBitLine8BPP(int x, int y, U8 const*p, int xsize, const LCD_PIXELINDEX*pTrans) {
  LCD_PIXELINDEX pixel;
  if ((GUI_Context.DrawMode & LCD_DRAWMODE_TRANS)==0) {
    if (pTrans) {
      for (;xsize > 0; xsize--,x++,p++) {
        pixel = *p;
        SETPIXEL(x, y, *(pTrans+pixel));
      }
    } else {
      for (;xsize > 0; xsize--,x++,p++) {
        SETPIXEL(x, y, *p);
      }
    }
  } else {   /* Handle transparent bitmap */
    if (pTrans) {
      for (; xsize > 0; xsize--, x++, p++) {
        pixel = *p;
        if (pixel) {
          SETPIXEL(x+0, y, *(pTrans+pixel));
        }
      }
    } else {
      for (; xsize > 0; xsize--, x++, p++) {
        pixel = *p;
        if (pixel) {
          SETPIXEL(x+0, y, pixel);
        }
      }
    }
  }
}
#endif

/*
    *********************************************
    *                                           *
    *      Draw Bitmap 16 BPP  (65536 colors)   *
    *                                           *
    *********************************************
*/


#if (LCD_BITSPERPIXEL > 8)
static void  DrawBitLine16BPP(int x, int y, U16 const*p, int xsize, const LCD_PIXELINDEX*pTrans) {
  LCD_PIXELINDEX pixel;
  if ((GUI_Context.DrawMode & LCD_DRAWMODE_TRANS)==0) {
    if (pTrans) {
      for (;xsize > 0; xsize--,x++,p++) {
        pixel = *p;
        SETPIXEL(x, y, *(pTrans+pixel));
      }
    } else {
      for (;xsize > 0; xsize--,x++,p++) {
        SETPIXEL(x, y, *p);
      }
    }
  } else {   /* Handle transparent bitmap */
    if (pTrans) {
      for (; xsize > 0; xsize--, x++, p++) {
        pixel = *p;
        if (pixel) {
          SETPIXEL(x+0, y, *(pTrans+pixel));
        }
      }
    } else {
      for (; xsize > 0; xsize--, x++, p++) {
        pixel = *p;
        if (pixel) {
          SETPIXEL(x+0, y, pixel);
        }
      }
    }
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

void LCD_L0_DrawBitmap   (int x0, int y0,
                       int xsize, int ysize,
                       int BitsPerPixel, 
                       int BytesPerLine,
                       const U8* pData, int Diff,
                       const LCD_PIXELINDEX* pTrans)
{
  int i;
  /*
     Use DrawBitLineXBPP
  */
  for (i=0; i<ysize; i++) {
    switch (BitsPerPixel) {
    case 1:
      DrawBitLine1BPP(x0, i+y0, pData, Diff, xsize, pTrans);
      break;
    #if (LCD_MAX_LOG_COLORS > 2)
      case 2:
        DrawBitLine2BPP(x0, i+y0, pData, Diff, xsize, pTrans);
        break;
    #endif
    #if (LCD_MAX_LOG_COLORS > 4)
      case 4:
        DrawBitLine4BPP(x0, i+y0, pData, Diff, xsize, pTrans);
        break;
    #endif
    #if (LCD_MAX_LOG_COLORS > 16)
      case 8:
        DrawBitLine8BPP(x0, i+y0, pData, xsize, pTrans);
        break;
    #endif
    #if (LCD_BITSPERPIXEL > 8)
      case 16:
        DrawBitLine16BPP(x0, i+y0, (const U16 *)pData, xsize, pTrans);
        break;
    #endif
    }
    pData += BytesPerLine;
  }
}


/********************************************************
*
*       LCD_L0_SetOrg
*
*********************************************************

Purpose:        Sets the original position of the virtual display.
                Has no function at this point with the PC-driver.
*/

int OrgX, OrgY;
void LCD_L0_SetOrg(int x, int y) {
  OrgX = x;
  OrgY = y;
}

/*
        *********************************************************
        *                                                       *
        *           Support for verification                    *
        *                                                       *
        *********************************************************

The following routines are implemented, but have no functionility
at this point. The reason is that these functions are supposed
to supervise the hardware, which for obvious reasons can not be
done in a simulation.

*/
#if LCD_VERIFY
int  LCD_GetErrStat(void) {
  return 0;
}
void LCD_ClrErrStat(void) {
}
int  LCD_GetErrCnt (void) {
  return 0;
}
#endif  

/*
        *********************************************************
        *                                                       *
        *       LCD_On                                          *
        *       LCD_Off                                         *
        *                                                       *
        *********************************************************

(Not supported in Simulation)
*/

void LCD_Off          (void) {}
void LCD_On           (void) {}

/*
        *********************************************************
        *                                                       *
        *       LUT routines (lookup tables)                    *
        *                                                       *
        *********************************************************
*/
void LCD_L0_SetLUTEntry(U8 Pos, LCD_COLOR color) {
  LCDSIM_SetLUTEntry(Pos, color);
}

#include <string.h>
#include "2410addr.h"
#include "2410lib.h"
#include "def.h"
#include "lcdlib.h"
#include "glib.h"
#include "lcd.h"

//Mono STN
U32 (*frameBuffer1Bit)[SCR_XSIZE_STN/32];
//Gray
U32 (*frameBuffer2Bit)[SCR_XSIZE_STN/16];
U32 (*frameBuffer4Bit)[SCR_XSIZE_STN/8];
//Color STN
U32 (*frameBuffer8Bit)[SCR_XSIZE_CSTN/4];
U32 (*frameBuffer12Bit)[SCR_XSIZE_CSTN*3/8];
//TFT 240320
U32 (*frameBuffer8BitTft240320)[SCR_XSIZE_TFT_240320/4];
U32 (*frameBuffer16BitTft240320)[SCR_XSIZE_TFT_240320/2];
//TFT 640480
U32 (*frameBuffer1BitTft640480)[SCR_XSIZE_TFT_640480/32];
U32 (*frameBuffer8BitTft640480)[SCR_XSIZE_TFT_640480/4];
U32 (*frameBuffer16BitTft640480)[SCR_XSIZE_TFT_640480/2];
U32 (*frameBuffer24BitTft640480)[SCR_XSIZE_TFT_640480];
//TFT 800600
U32 (*frameBuffer1BitTft800600)[SCR_XSIZE_TFT_800600/32];
U32 (*frameBuffer8BitTft800600)[SCR_XSIZE_TFT_800600/4];
U32 (*frameBuffer16BitTft800600)[SCR_XSIZE_TFT_800600/2];

unsigned save_rGPCUP,save_rGPCDAT,save_rGPCCON;
unsigned save_rGPDUP,save_rGPDDAT,save_rGPDCON; 
unsigned lcd_count;

void Lcd_Port_Init(void)
{
    save_rGPCCON=rGPCCON;
    save_rGPCDAT=rGPCDAT;
    save_rGPCUP=rGPCUP;
    save_rGPDCON=rGPDCON;
    save_rGPDDAT=rGPDDAT;
    save_rGPDUP=rGPDUP;
    rGPCUP=0xffffffff; // Disable Pull-up register
    rGPCCON=0xaaaaaaaa; //Initialize VD[7:0],LCDVF[2:0],VM,VFRAME,VLINE,VCLK,LEND 
    rGPDUP=0xffffffff; // Disable Pull-up register
    rGPDCON=0xaaaaaaaa; //Initialize VD[23:8]
}
void Lcd_CstnOnOff(int onoff)
{
    // 1:CSTN Panel on  0:CSTN Panel off //	
    if(onoff==1)
    	rLCDCON1|=1; // ENVID=ON
    else
	rLCDCON1 =rLCDCON1 & 0x3fffe; // ENVID Off
    rGPGUP=rGPGUP|(1<<4); // Pull-up disable
    rGPGDAT=rGPGDAT&(~(1<<4))|(onoff<<4); // GPB5=On or Off
    rGPGCON=rGPGCON&(~(3<<8))|(1<<8);    //GPD9=output
}    
void Lcd_Init(int type)
{
    switch(type)
    {
    case MODE_STN_1BIT:
       	frameBuffer1Bit=(U32 (*)[SCR_XSIZE_STN/32])LCDFRAMEBUFFER;
	rLCDCON1=(CLKVAL_STN_MONO<<8)|(MVAL_USED<<7)|(1<<5)|(0<<1)|0; 
   	// 4-bit single scan,1bpp STN,ENVID=off
	rLCDCON2=(0<<24)|(LINEVAL_STN<<14)|(0<<6)|(0<<0);	// It is not TFT LCD. So,.....    		
	rLCDCON3=(WDLY_STN<<19)|(HOZVAL_STN<<8)|(LINEBLANK_MONO<<0);
	rLCDCON4=(MVAL<<8)|(WLH_STN<<0);
	rLCDCON5=0;
	//BPP24BL:x,FRM565:x,INVVCLK:x,INVVLINE:x,INVVFRAME:x,INVVD:x,
	//INVVDEN:x,INVPWREN:x,INVLEND:x,PWREN:x,ENLEND:x,BSWP:x,HWSWP:x
	rLCDSADDR1=(((U32)frameBuffer1Bit>>22)<<21)|M5D((U32)frameBuffer1Bit>>1);		
	rLCDSADDR2=M5D( ((U32)frameBuffer1Bit+(SCR_XSIZE_STN*LCD_YSIZE_STN/8))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_STN-LCD_XSIZE_STN)/16)<<11)|(LCD_XSIZE_STN/16);
    break;

    case MODE_STN_2BIT:
    	frameBuffer2Bit=(U32 (*)[SCR_XSIZE_STN/16])LCDFRAMEBUFFER;
    	rLCDCON1=(CLKVAL_STN_GRAY<<8)|(MVAL_USED<<7)|(1<<5)|(1<<1)|0;
   	// 4-bit single scan,2bpp STN,ENVID=off
    	rLCDCON2=(0<<24)|(LINEVAL_STN<<14)|(0<<6)|(0<<0);
    	rLCDCON3=(WDLY_STN<<19)|(HOZVAL_STN<<8)|(LINEBLANK_GRAY<<0);
    	rLCDCON4=(MVAL<<8)|(WLH_STN<<0);
    	rLCDCON5=0;
	//BPP24BL:x,FRM565:x,INVVCLK:x,INVVLINE:x,INVVFRAME:x,INVVD:x,
	//INVVDEN:x,INVPWREN:x,INVLEND:x,PWREN:x,ENLEND:x,BSWP:x,HWSWP:x
    	rLCDSADDR1=(((U32)frameBuffer2Bit>>22)<<21)|M5D((U32)frameBuffer2Bit>>1);
    	rLCDSADDR2=M5D( ((U32)frameBuffer2Bit+(SCR_XSIZE_STN*LCD_YSIZE_STN/4))>>1);
    	rLCDSADDR3=(((SCR_XSIZE_STN-LCD_XSIZE_STN)/8)<<11)|(LCD_XSIZE_STN/8);
	rDITHMODE=0x0;
	rBLUELUT =0xf950;	// 4-Gray only
    break;
    	
    case MODE_STN_4BIT:
    	frameBuffer4Bit=(U32 (*)[SCR_XSIZE_STN/8])LCDFRAMEBUFFER;
    	rLCDCON1=(CLKVAL_STN_GRAY<<8)|(MVAL_USED<<7)|(1<<5)|(2<<1)|0;
    	// 4-bit single scan,4bpp STN,ENVID=off
	rLCDCON2=(0<<24)|(LINEVAL_STN<<14)|(0<<6)|(0<<0);
	rLCDCON3=(WDLY_STN<<19)|(HOZVAL_STN<<8)|(LINEBLANK_GRAY<<0);
	rLCDCON4=(MVAL<<8)|(WLH_STN<<0);
	rLCDCON5=0;
	//BPP24BL:x,FRM565:x,INVVCLK:x,INVVLINE:x,INVVFRAME:x,INVVD:x,
	//INVVDEN:x,INVPWREN:x,INVLEND:x,PWREN:x,ENLEND:x,BSWP:x,HWSWP:x
	rLCDSADDR1=(((U32)frameBuffer4Bit>>22)<<21)|M5D((U32)frameBuffer4Bit>>1);
	rLCDSADDR2=M5D( ((U32)frameBuffer4Bit+(SCR_XSIZE_STN*LCD_YSIZE_STN/2))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_STN-LCD_XSIZE_STN)/4)<<11)|(LCD_XSIZE_STN/4);
	rDITHMODE=0x0;
    break;

    case MODE_CSTN_8BIT:
    	frameBuffer8Bit=(U32 (*)[SCR_XSIZE_CSTN/4])LCDFRAMEBUFFER;
	rLCDCON1=(CLKVAL_CSTN<<8)|(MVAL_USED<<7)|(2<<5)|(3<<1)|0;
    	// 8-bit single scan,8bpp CSTN,ENVID=off
	rLCDCON2=(0<<24)|(LINEVAL_CSTN<<14)|(0<<6)|(0<<0);
	rLCDCON3=(WDLY_CSTN<<19)|(HOZVAL_CSTN<<8)|(LINEBLANK_CSTN<<0);
	rLCDCON4=(MVAL<<8)|(WLH_CSTN<<0);
	rLCDCON5=0;
	//BPP24BL:x,FRM565:x,INVVCLK:x,INVVLINE:x,INVVFRAME:x,INVVD:x,
	//INVVDEN:x,INVPWREN:x,INVLEND:x,PWREN:x,ENLEND:x,BSWP:x,HWSWP:x
	rLCDSADDR1=(((U32)frameBuffer8Bit>>22)<<21 )|M5D((U32)frameBuffer8Bit>>1);
	rLCDSADDR2=M5D( ((U32)frameBuffer8Bit+(SCR_XSIZE_CSTN*LCD_YSIZE_CSTN/1))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_CSTN-LCD_XSIZE_CSTN)/2)<<11)|(LCD_XSIZE_CSTN/2);
	rDITHMODE=0x0;
	rREDLUT  =0xfdb96420;
	rGREENLUT=0xfdb96420;
	rBLUELUT =0xfb40;
    break;
	
    case MODE_CSTN_12BIT:
    	frameBuffer12Bit=(U32 (*)[SCR_XSIZE_CSTN*3/8])LCDFRAMEBUFFER;
    	// Packed Type : The L.C.M of 12 and 32 is 96.
    	rLCDCON1=(CLKVAL_CSTN<<8)|(MVAL_USED<<7)|(2<<5)|(4<<1)|0;
    	// 8-bit single scan,12bpp CSTN,ENVID=off
    	rLCDCON2=(0<<24)|(LINEVAL_CSTN<<14)|(0<<6)|0;
    	rLCDCON3=(WDLY_CSTN<<19)|(HOZVAL_CSTN<<8)|(LINEBLANK_CSTN<<0);
    	rLCDCON4=(MVAL<<8)|(WLH_CSTN<<0);
    	rLCDCON5=0;
    	//BPP24BL:x,FRM565:x,INVVCLK:x,INVVLINE:x,INVVFRAME:x,INVVD:x,
	//INVVDEN:x,INVPWREN:x,INVLEND:x,PWREN:x,ENLEND:x,BSWP:x,HWSWP:x
    	rLCDSADDR1=(((U32)frameBuffer12Bit>>22)<<21)|M5D((U32)frameBuffer12Bit>>1);
    	rLCDSADDR2=M5D(((U32)frameBuffer12Bit+((SCR_XSIZE_CSTN*3/2)*LCD_YSIZE_CSTN))>>1);
    	rLCDSADDR3=(((SCR_XSIZE_CSTN-LCD_XSIZE_CSTN)*3/4)<<11)|(LCD_XSIZE_CSTN*3/4);
	rDITHMODE=0;
    break;

    case MODE_TFT_8BIT_240320:
	frameBuffer8BitTft240320=(U32 (*)[SCR_XSIZE_TFT_240320/4])LCDFRAMEBUFFER;
	rLCDCON1=(CLKVAL_TFT_240320<<8)|(MVAL_USED<<7)|(3<<5)|(11<<1)|0;
        // TFT LCD panel,8bpp TFT,ENVID=off
	rLCDCON2=(VBPD_240320<<24)|(LINEVAL_TFT_240320<<14)|(VFPD_240320<<6)|(VSPW_240320);
	rLCDCON3=(HBPD_240320<<19)|(HOZVAL_TFT_240320<<8)|(HFPD_240320);
	rLCDCON4=(MVAL<<8)|(HSPW_240320);
	rLCDCON5=(1<<11)|(1<<9)|(1<<8);	//FRM5:6:5,HSYNC and VSYNC are inverted
	rLCDSADDR1=(((U32)frameBuffer8BitTft240320>>22)<<21)|M5D((U32)frameBuffer8BitTft240320>>1);
	rLCDSADDR2=M5D( ((U32)frameBuffer8BitTft240320+(SCR_XSIZE_TFT_240320*LCD_YSIZE_TFT_240320/1))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_TFT_240320-LCD_XSIZE_TFT_240320)/2)<<11)|(LCD_XSIZE_TFT_240320/2);
	rLCDINTMSK|=(3); // MASK LCD Sub Interrupt
	rLPCSEL&=(~7); // Disable LPC3600
	rTPAL=0; // Disable Temp Palette
    break;
    		
    case MODE_TFT_16BIT_240320:
	frameBuffer16BitTft240320=(U32 (*)[SCR_XSIZE_TFT_240320/2])LCDFRAMEBUFFER;
	rLCDCON1=(CLKVAL_TFT_240320<<8)|(MVAL_USED<<7)|(3<<5)|(12<<1)|0;
    	// TFT LCD panel,12bpp TFT,ENVID=off
	rLCDCON2=(VBPD_240320<<24)|(LINEVAL_TFT_240320<<14)|(VFPD_240320<<6)|(VSPW_240320);
	rLCDCON3=(HBPD_240320<<19)|(HOZVAL_TFT_240320<<8)|(HFPD_240320);
	rLCDCON4=(MVAL<<8)|(HSPW_240320);
	rLCDCON5=(1<<11)|(0<<9)|(0<<8);	//FRM5:6:5,HSYNC and VSYNC are inverted	
	rLCDSADDR1=(((U32)frameBuffer16BitTft240320>>22)<<21)|M5D((U32)frameBuffer16BitTft240320>>1);
	rLCDSADDR2=M5D( ((U32)frameBuffer16BitTft240320+(SCR_XSIZE_TFT_240320*LCD_YSIZE_TFT_240320*2))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_TFT_240320-LCD_XSIZE_TFT_240320)/1)<<11)|(LCD_XSIZE_TFT_240320/1);
	rLCDINTMSK|=(3); // MASK LCD Sub Interrupt
	rLPCSEL&=(~7); // Disable LPC3600
	rTPAL=0; // Disable Temp Palette
    break;

    case MODE_TFT_16BIT_640480:
    	frameBuffer16BitTft640480=(U32 (*)[SCR_XSIZE_TFT_640480/2])LCDFRAMEBUFFER;
	rLCDCON1=(CLKVAL_TFT_640480<<8)|(MVAL_USED<<7)|(3<<5)|(12<<1)|0;
        // TFT LCD panel,16bpp TFT,ENVID=off
	rLCDCON2=(VBPD_640480<<24)|(LINEVAL_TFT_640480<<14)|(VFPD_640480<<6)|(VSPW_640480);
	rLCDCON3=(HBPD_640480<<19)|(HOZVAL_TFT_640480<<8)|(HFPD_640480);
	rLCDCON4=(MVAL<<8)|(HSPW_640480);
	rLCDCON5=(1<<11)|(1<<9)|(1<<8)/*|(1<<0)*/;	//FRM5:6:5,HSYNC and VSYNC are inverted
	rLCDSADDR1=(((U32)frameBuffer16BitTft640480>>22)<<21)|M5D((U32)frameBuffer16BitTft640480>>1);
	rLCDSADDR2=M5D( ((U32)frameBuffer16BitTft640480+(SCR_XSIZE_TFT_640480*LCD_YSIZE_TFT_640480*2))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_TFT_640480-LCD_XSIZE_TFT_640480)/1)<<11)|(LCD_XSIZE_TFT_640480/1);
	rLCDINTMSK|=(3); // MASK LCD Sub Interrupt
	rLPCSEL&=(~7); // Disable LPC3600
	rTPAL=0; // Disable Temp Palette
    break;

    case MODE_TFT_1BIT_640480:
    	frameBuffer1BitTft640480=(U32 (*)[SCR_XSIZE_TFT_640480/32])LCDFRAMEBUFFER;
	rLCDCON1=(CLKVAL_TFT_640480<<8)|(MVAL_USED<<7)|(3<<5)|(8<<1)|0;
	rLCDCON2=(VBPD_640480<<24)|(LINEVAL_TFT_640480<<14)|(VFPD_640480<<6)|(VSPW_640480);
	rLCDCON3=(HBPD_640480<<19)|(HOZVAL_TFT_640480<<8)|(HFPD_640480);
	rLCDCON4=(MVAL<<8)|(HSPW_640480);
	rLCDCON5=(1<<11)|(1<<9)|(1<<8);	//FRM5:6:5,HSYNC and VSYNC are inverted
	rLCDSADDR1=(((U32)frameBuffer1BitTft640480>>22)<<21)|M5D((U32)frameBuffer1BitTft640480>>1);
	rLCDSADDR2=M5D( ((U32)frameBuffer1BitTft640480+(SCR_XSIZE_TFT_640480*LCD_YSIZE_TFT_640480/8))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_TFT_640480-LCD_XSIZE_TFT_640480)/16)<<11)|(LCD_XSIZE_TFT_640480/16);
	rLCDINTMSK|=(3); // MASK LCD Sub Interrupt
	rLPCSEL&=(~7); // Disable LPC3600
	rTPAL=0; // Disable Temp Palette
    break;

    case MODE_TFT_8BIT_640480:
    	frameBuffer8BitTft640480=(U32 (*)[SCR_XSIZE_TFT_640480/4])LCDFRAMEBUFFER;
	rLCDCON1=(CLKVAL_TFT_640480<<8)|(MVAL_USED<<7)|(3<<5)|(11<<1)|0;
   	// TFT LCD panel,8bpp TFT,ENVID=off
	rLCDCON2=(VBPD_640480<<24)|(LINEVAL_TFT_640480<<14)|(VFPD_640480<<6)|(VSPW_640480);
	rLCDCON3=(HBPD_640480<<19)|(HOZVAL_TFT_640480<<8)|(HFPD_640480);
	rLCDCON4=(MVAL<<8)|(HSPW_640480);
	rLCDCON5=(1<<11)|(1<<9)|(1<<8);	//FRM5:6:5,HSYNC and VSYNC are inverted
	rLCDSADDR1=(((U32)frameBuffer8BitTft640480>>22)<<21)|M5D((U32)frameBuffer8BitTft640480>>1);
	rLCDSADDR2=M5D( ((U32)frameBuffer8BitTft640480+(SCR_XSIZE_TFT_640480*LCD_YSIZE_TFT_640480/1))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_TFT_640480-LCD_XSIZE_TFT_640480)/2)<<11)|(LCD_XSIZE_TFT_640480/2);
	rLCDINTMSK|=(3); // MASK LCD Sub Interrupt
	rLPCSEL&=(~7); // Disable LPC3600
	rTPAL=0; // Disable Temp Palette
    break;
    	
    case MODE_TFT_24BIT_640480:
    	frameBuffer24BitTft640480=(U32 (*)[SCR_XSIZE_TFT_640480])LCDFRAMEBUFFER;
	rLCDCON1=(CLKVAL_TFT_640480<<8)|(MVAL_USED<<7)|(3<<5)|(13<<1)|0;
        // TFT LCD panel,24bpp TFT,ENVID=off
	rLCDCON2=(VBPD_640480<<24)|(LINEVAL_TFT_640480<<14)|(VFPD_640480<<6)|(VSPW_640480);
	rLCDCON3=(HBPD_640480<<19)|(HOZVAL_TFT_640480<<8)|(HFPD_640480);
	rLCDCON4=(MVAL<<8)|(HSPW_640480);
	rLCDCON5=(1<<12)|(1<<9)|(1<<8);	// BPP24:MSB,HSYNC and VSYNC are inverted
	rLCDSADDR1=(((U32)frameBuffer24BitTft640480>>22)<<21)|M5D((U32)frameBuffer24BitTft640480>>1);
	rLCDSADDR2=M5D( ((U32)frameBuffer24BitTft640480+(SCR_XSIZE_TFT_640480*LCD_YSIZE_TFT_640480*4))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_TFT_640480-LCD_XSIZE_TFT_640480)*2)<<11)|(LCD_XSIZE_TFT_640480*2);
	rLCDINTMSK|=(3); // MASK LCD Sub Interrupt
	rLPCSEL&=(~7); // Disable LPC3600
	rTPAL=0; // Disable Temp Palette

    break;

    case MODE_TFT_1BIT_800600:
	frameBuffer1BitTft800600=(U32 (*)[SCR_XSIZE_TFT_800600/32])LCDFRAMEBUFFER;
   	rLCDCON1=(CLKVAL_TFT_800600<<8)|(MVAL_USED<<7)|(3<<5)|(8<<1)|0;
        // TFT LCD panel,1bpp TFT,ENVID=off
	rLCDCON2=(VBPD_800600<<24)|(LINEVAL_TFT_800600<<14)|(VFPD_800600<<6)|(VSPW_800600);
	rLCDCON3=(HBPD_800600<<19)|(HOZVAL_TFT_800600<<8)|(HFPD_800600);
	rLCDCON4=(MVAL<<8)|(HSPW_800600);
	rLCDCON5=(1<<9)|(1<<8);	
   	//BPP24BL:x,FRM565:x,INVVCLK:x,INVVLINE:o,INVVFRAME:o,INVVD:x,
	//INVVDEN:x,INVPWREN:x,INVLEND:x,PWREN:x,ENLEND:x,BSWP:x,HWSWP:x
	rLCDSADDR1=(((U32)frameBuffer1BitTft800600>>22)<<21)|M5D((U32)frameBuffer1BitTft800600>>1);
	rLCDSADDR2=M5D( ((U32)frameBuffer1BitTft800600+(SCR_XSIZE_TFT_800600*LCD_YSIZE_TFT_800600/8))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_TFT_800600-LCD_XSIZE_TFT_800600)/16)<<11)|(LCD_XSIZE_TFT_800600/16);
	rLCDINTMSK|=(3); // MASK LCD Sub Interrupt
	rLPCSEL&=(~7); // Disable LPC3600
	rTPAL=0; // Disable Temp Palette

    break;

    case MODE_TFT_8BIT_800600:
	frameBuffer8BitTft800600=(U32 (*)[SCR_XSIZE_TFT_800600/4])LCDFRAMEBUFFER;
   	rLCDCON1=(CLKVAL_TFT_800600<<8)|(MVAL_USED<<7)|(3<<5)|(11<<1)|0;
        // TFT LCD panel,8bpp TFT,ENVID=off
	rLCDCON2=(VBPD_800600<<24)|(LINEVAL_TFT_800600<<14)|(VFPD_800600<<6)|(VSPW_800600);
	rLCDCON3=(HBPD_800600<<19)|(HOZVAL_TFT_800600<<8)|(HFPD_800600);
	rLCDCON4=(MVAL<<8)|(HSPW_800600);
	rLCDCON5=(1<<9)|(1<<8);	
	//BPP24BL:x,FRM565:x,INVVCLK:x,INVVLINE:o,INVVFRAME:o,INVVD:x,
	//INVVDEN:x,INVPWREN:x,INVLEND:x,PWREN:x,ENLEND:x,BSWP:x,HWSWP:x
	rLCDSADDR1=(((U32)frameBuffer8BitTft800600>>22)<<21)|M5D((U32)frameBuffer8BitTft800600>>1);
	rLCDSADDR2=M5D( ((U32)frameBuffer8BitTft800600+(SCR_XSIZE_TFT_800600*LCD_YSIZE_TFT_800600/1))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_TFT_800600-LCD_XSIZE_TFT_800600)/2)<<11)|(LCD_XSIZE_TFT_800600/2);
	rLCDINTMSK|=(3); // MASK LCD Sub Interrupt
	rLPCSEL&=(~7); // Disable LPC3600
	rTPAL=0; // Disable Temp Palette
    break;
    	
    case MODE_TFT_16BIT_800600:
	frameBuffer16BitTft800600=(U32 (*)[SCR_XSIZE_TFT_800600/2])LCDFRAMEBUFFER;
   	rLCDCON1=(CLKVAL_TFT_800600<<8)|(MVAL_USED<<7)|(3<<5)|(12<<1)|0;
        // TFT LCD panel,16bpp TFT,ENVID=off
	rLCDCON2=(VBPD_800600<<24)|(LINEVAL_TFT_800600<<14)|(VFPD_800600<<6)|(VSPW_800600);
	rLCDCON3=(HBPD_800600<<19)|(HOZVAL_TFT_800600<<8)|(HFPD_800600);
	rLCDCON4=(MVAL<<8)|(HSPW_800600);
	rLCDCON5=(1<<11)|(1<<10)|(1<<9)|(1<<8);
	//BPP24BL:x,FRM565:o,INVVCLK:x,INVVLINE:o,INVVFRAME:o,INVVD:x,
	//INVVDEN:x,INVPWREN:x,INVLEND:x,PWREN:x,ENLEND:x,BSWP:x,HWSWP:x
	rLCDSADDR1=(((U32)frameBuffer16BitTft800600>>22)<<21)|M5D((U32)frameBuffer16BitTft800600>>1);
	rLCDSADDR2=M5D( ((U32)frameBuffer16BitTft800600+(SCR_XSIZE_TFT_800600*LCD_YSIZE_TFT_800600*2))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_TFT_800600-LCD_XSIZE_TFT_800600)/1)<<11)|(LCD_XSIZE_TFT_800600/1);
	rLCDINTMSK|=(3); // MASK LCD Sub Interrupt
	rLPCSEL&=(~7); // Disable LPC3600
	rTPAL=0; // Disable Temp Palette

    break;

    default:
    break;
    }	
}

void Lcd_PowerEnable(int invpwren,int pwren)
{
    rGPGCON &= ~(3 << 8);                 /* Set LCD_PWREN as output                          */
    rGPGCON |=  (1 << 8);

    rGPGDAT &=  ~(1 << 4);                 /* Backlight ON                                     */
}   
void Lcd_EnvidOnOff(int onoff)
{
    if(onoff==1)
	rLCDCON1|=1; // ENVID=ON
    else
	rLCDCON1 =rLCDCON1 & 0x3fffe; // ENVID Off
}    
/*****************************************************************************
// Function name	: s3c2410x_lcd_init
// Description	    : LCD显示驱动初始化函数
// Return type		: void
// Argument         : 无
*****************************************************************************/
void s3c2410x_lcd_init()
{
	Lcd_Port_Init();
#ifdef LCD_TFT_3_5    
	    Lcd_Init(MODE_TFT_16BIT_240320);
#else
	#ifdef LCD_TFT_8_0
		rGPCCON &= ~(3<<8);
		rGPCCON |= (2<<8);
	
		Lcd_Init(MODE_TFT_16BIT_640480);
	
	    Lcd_PowerEnable(0, 1);
	    Lcd_EnvidOnOff(1);   
	#else
	    Lcd_Init(MODE_CSTN_8BIT);
	    Lcd_CstnOnOff(1);
	#endif
#endif	    
}
void _PutTft16Bit_640480(U32 x,U32 y,U32 c)
{
    if(x<SCR_XSIZE_TFT_640480 && y<SCR_YSIZE_TFT_640480)
        frameBuffer16BitTft640480[(y)][(x)/2]=( frameBuffer16BitTft640480[(y)][x/2]
        & ~(0xffff0000>>((x)%2)*16) ) | ( (c&0x0000ffff)<<((2-1-((x)%2))*16) );
}
void _PutTft16Bit_240320(U32 x,U32 y,U32 c)
{
	U32 tmp = x;
	
    if(x<SCR_XSIZE_TFT_240320 && y<SCR_YSIZE_TFT_240320)
        frameBuffer16BitTft240320[(y)][(x)/2]=( frameBuffer16BitTft240320[(y)][x/2]
        & ~(0xffff0000>>((x)%2)*16) ) | ( (c&0x0000ffff)<<((2-1-((x)%2))*16) );
}
void _PutCstn8Bit(U32 x,U32 y,U32 c)
{
    if(x<SCR_XSIZE_CSTN&& y<SCR_YSIZE_CSTN)
        frameBuffer8Bit[(y)][(x)/4]=( frameBuffer8Bit[(y)][x/4]
	    & ~(0xff000000>>((x)%4)*8) ) | ( (c&0x000000ff)<<((4-1-((x)%4))*8) );
}
/*****************************************************************************
// Function name	: lcd_put_pixel
// Description	    : LCD打点函数
// Return type		: void
// Argument         : int x : x坐标
// Argument         : int y : y坐标
// Argument         : int c : 颜色
*****************************************************************************/
void lcd_put_pixel(int x,int y,int c)
{
#ifdef LCD_TFT_3_5    
    _PutTft16Bit_240320(x, y, c);
#else
	#ifdef LCD_TFT_8_0
    	_PutTft16Bit_640480(x, y, c);
	#else
	    _PutCstn8Bit(x, y, c);
	#endif
#endif	    
}
#if 0
int touch_up_poll = 0;
static void touch_touched(int irq, void *dev_id, struct pt_regs *regs)
{
  // 清除EINT3中断
  rI_ISPC=BIT_EINT3;
  
  rPCONG &= 0xff3f;
  
  touch_up_poll = 1;
}
void udelay()
{
	int loopcnt = 100;
	while(loopcnt --)
	{
		loopcnt -= 1;
		loopcnt += 1;
	}
}
static void read_xy(int *tx, int *ty)
{
  int i;
  int tmp[32];

  rADCPSR = 0x2f;
  rPCONE &= 0x300ff;
  rPCONE |= 0x0500;
  rPDATE = 0x20;
  udelay(50);
  for(i=0; i<32; i++){
     rADCCON = 1;
     while(rADCCON&0x01) udelay(1);
     while(!(rADCCON&0x40)) udelay(1);
     tmp[i] = (rADCDAT);
  }
  *tx = 0;
  for(i=5; i<27; i++){
     *tx += tmp[i];
  }
  *tx /= 22;
  (rADCPSR) = 0x2f;
  (rPCONE) &= 0x300ff;
  (rPCONE) |= 0x5000;
  (rPDATE) = 0x80;

  udelay(50);
  for(i=0; i<32; i++){
     (rADCCON) = 1|(1<<2);
     while((rADCCON)&0x01) udelay(1);
     while(!((rADCCON)&0x40)) udelay(1);
     tmp[i] = (rADCDAT);
  }
  *ty = 0;
  for(i=5; i<27; i++){
     *ty += tmp[i];
  }
  *ty /= 22;
}
extern GUI_HID_STATE _State;
struct ts_event{
    unsigned short status;
    unsigned short x;
    unsigned short y;
    unsigned short pad;
};
struct ts_device{
    struct ts_event last;
    struct ts_event ebuf[32];
    int head, tail;
    int isdrag;
}tsdev;
#define PEN_UP		1
#define PEN_DOWN 	0
#define PEN_DISCARD	2
static void put_event(int x, int y, int down)
{
  int dx, dy;
  switch(tsdev.last.status){
  case PEN_UP:
    if(!down){
      tsdev.isdrag = 0;
      return;
    }
    tsdev.last.status = PEN_DISCARD;
    return;
 case PEN_DISCARD:
    if(!down){
      tsdev.last.status = PEN_UP;
      tsdev.isdrag = 0;
      return;
    }
    tsdev.last.status = PEN_DOWN;
    tsdev.last.x = x;
    tsdev.last.y = y;
    _State.x = x;
    _State.y = y;
    _State.Pressed = 1;
    break;
 case PEN_DOWN:
    if(!down){
      tsdev.last.status = PEN_UP;
      tsdev.isdrag = 0;
      _State.x = x;
      _State.y = y;
      _State.Pressed = 0;
      break;
    }

    if(!tsdev.isdrag){
      dx = x-tsdev.last.x;
      dy = y-tsdev.last.y;
      if(dx<0)
        dx = -dx;
        if(dy<0)
          dy = -dy;

        if(dy<6 && dx<4)
          return;
        tsdev.isdrag = 1;
    }
    
    tsdev.last.x = x;
    tsdev.last.y = y;
    break;
  }
  tsdev.ebuf[tsdev.head] = tsdev.last;
  tsdev.head = (tsdev.head+1)&(32-1);
  if(tsdev.head == tsdev.tail)
    tsdev.tail = (tsdev.tail+1)&(32-1);
}
static void do_touch()
{
  int tx, ty;
  int tx1, ty1;
  int tx2, ty2;

  if((rPDATG)&0x08)
  {
     put_event(0, 0, 0);
     (rPCONG) |= 0x000c0;
     touch_up_poll = 0;
     return;
  }
 
  read_xy(&ty, &tx);

  // done
  #define X1_Y 0x1ca
  #define X1_X 0x75

  #define X4_Y 0x89
  #define X4_X 0x1c9

  #define X2_Y 0x1b7
  #define X2_X 0x1c4

  #define X3_Y 0xa2
  #define X3_X 0x81

  #ifdef TS_VERIFY
  printk("tx = 0x%x , ty = 0x%x\n", tx, ty);
  #endif

  tx1 = (int)((tx-X1_X) * 320.0 / (X4_X - X1_X));
  ty1 = (int)((ty-X1_Y) * 240.0 / (X4_Y - X1_Y));

  tx2 = (int)((tx-X3_X) * 320.0 / (X2_X - X3_X));
  ty2 = (int)((ty-X2_Y) * 240.0 / (X3_Y - X2_Y));

  //printk("tx1 = 0x%x , ty1 = 0x%x\n", tx1, ty1);
  //printk("tx2 = 0x%x , ty2 = 0x%x\n", tx2, ty2);

  tx = (tx2 + tx1) / 2;
  ty = (ty2 + ty1) / 2;

  tx = tx<0 ? 0 : tx;
  ty = ty<0 ? 0 : ty;
  tx = tx>320 ? 320 : tx;
  ty = ty>240 ? 240 : ty;
  put_event(tx, ty, 1);

#ifdef TS_VERIFY
  printk("do_touch (%d, %d)\n", tx, ty); 
#endif

  (rPCONE) &= 0x300ff;
  (rPCONE) |= 0x00400;
  (rPDATE)&= 0x0000f;
  
  touch_up_poll = 1;
}
void s3c44b0x_touch_init()
{ 
  rPCONE &= 0x300ff;
  rPCONE |= 0x0400;
  rPUPE = 0xff;
  rPDATE &= 0x0f;
 
  rPCONG |= 0x0c0;
  
  pISR_EINT3=(int)touch_touched;
  rI_ISPC = BIT_EINT3;
  rINTMSK &= ~BIT_EINT3;
}
#endif
/*
        *********************************************************
        *                                                       *
        *       LCD_Init : Init the display                     *
        *                                                       *
        *********************************************************
*/

int  LCD_L0_Init(void) {
  int x,y;
  s3c2410x_lcd_init();
//  s3c44b0x_touch_init();
  
  // Create Bitmaps to simulate LCD (pages)
//  for (x=0; x< LCD_XSIZE; x++)
//    for (y=0; y< LCD_YSIZE; y++)
//      SETPIXEL( x, y, BKCOLORINDEX);
	return 0;
}

int  LCD_L0_CheckInit(void) {
  return 0;
} 

/*
        ******************************************
        *                                        *
        *    Re-initialize LCD                   *
        *                                        *
        ******************************************

This routine is supplied for compatibility and interchangability of
"C"-sources with embedded versions of the driver. It has no real
effect in the PC-version as there is simply no need to re-initialize
the LCD since it is just simulated anyhow.
*/

void LCD_L0_ReInit       (void) {}

unsigned LCD_L0_GetPixelIndex(int x, int y)  {
  return LCDSIM_GetPixelIndex(x,y);
}

/*
        *********************************************************
        *                                                       *
        *       LCD_L0_XorPixel                                 *
        *                                                       *
        *********************************************************

Purpose:  This routine is called by emWin. It writes 1 pixel into the
          display.

*/

void LCD_L0_XorPixel(int x, int y) {
  XORPIXEL(x, y);
}


/*
        *********************************************************
        *                                                       *
        *       LCD_L0_SetPixelIndex                            *
        *                                                       *
        *********************************************************

Purpose:  This routine is called by emWin. It writes 1 pixel into the
          display.

*/

void LCD_L0_SetPixelIndex(int x, int y, int ColorIndex) {
  SETPIXEL(x, y, ColorIndex);
}

int  LCDSIM_GetPixelIndex(int x, int y){
}

void  LCDSIM_SetPixelIndex(int x, int y, int c) {
	lcd_put_pixel(x, y, c);
}

void  LCDSIM_SetLUTEntry(U8 Pos, LCD_COLOR color)
{
}

////////////////////////////////////////////////////////////////////////////////////
////  Keyboard
////////////////////////////////////////////////////////////////////////////////////
/********************************************************************
// Function name	: get_key
// Description	    : 如果有键按下返回键，否则返回0
// Return type		: char
// Argument         : 
*********************************************************************/
char get_key()
{
//	DrvKeyGet();
}
char get_key_no_del()
{
//	DrvKeyGetNoDel();
}
/********************************************************************
// Function name	: timer1_isr
// Description	    : 定时器1中断服务程序，用于扫描键盘，每隔10ms一次中断
// Return type		: void
// Argument         : void
*********************************************************************/
void touch_poll(void)
{
//	// touch
//	if(touch_up_poll)
//		do_touch();
}

