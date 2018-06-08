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
File        : GUI_Protected.h
Purpose     : GUI internal declarations
---------------------------END-OF-HEADER------------------------------
*/

#ifndef  GUI_PROTECTED_H
#define  GUI_PROTECTED_H

#include "GUI.h"
#include "LCD_Protected.h"
#include "GUIDebug.h"


/**********************************************************************
*
*                        Defaults for config switches
*
***********************************************************************

  The config switches below do not affect the interface in GUI.h and
  are therefor not required to be in GUI.h.
*/

#ifndef GUI_ALLOC_SIZE
  #define GUI_ALLOC_SIZE      1000
#endif

/* Short address area.
   For  most compilers, this is "near" or "__near"
   We do not use this except for some CPUs which we know to always have some
   near memory, because the GUI_Context ans some other data will be declared
   to be in this short address (near) memory area as it has a major effect
   on performance.
   Please define in GUIConf.h (if you want to use it)
*/
#ifndef GUI_SADDR
  #define GUI_SADDR
#endif


/*      *********************************
        *                               *
        *      Angles                   *
        *                               *
        *********************************
*/

#define GUI_45DEG  512
#define GUI_90DEG  (2*GUI_45DEG)
#define GUI_180DEG (4*GUI_45DEG)
#define GUI_360DEG (8*GUI_45DEG)




/*********************************************************************
*
*             Support for multitasking systems
*
**********************************************************************
*/

void GUI_Lock(void);
void GUI_Unlock(void);
void GUITASK_Init(void);

#if !GUI_OS
  #define GUI_LOCK()
  #define GUI_UNLOCK()
  #define GUITASK_INIT()
#else
  #define GUI_LOCK() GUI_Lock()
  #define GUI_UNLOCK() GUI_Unlock()
  #define GUITASK_INIT() GUITASK_Init()
#endif

/*****************************************************
*
*        ALLOC internals  (memory allocation)
*
******************************************************
*/


/*****************************************************
*
*        Usage internals
*
******************************************************

*/

typedef GUI_HMEM GUI_USAGE_Handle;
typedef struct tsUSAGE_APIList tUSAGE_APIList;
typedef struct GUI_Usage GUI_USAGE;
#define GUI_USAGE_h GUI_USAGE_Handle



typedef GUI_USAGE_h tUSAGE_CreateCompatible(GUI_USAGE* p);
typedef void        tUSAGE_AddPixel        (GUI_USAGE* p, int x, int y);
typedef void        tUSAGE_AddHLine        (GUI_USAGE* p, int x0, int y0, int len);
typedef void        tUSAGE_Clear           (GUI_USAGE* p);
typedef void        tUSAGE_Delete          (GUI_USAGE_h h);
typedef int         tUSAGE_GetNextDirty    (GUI_USAGE* p, int *pxOff, int yOff);
#define GUI_USAGE_h2p(h) ((GUI_USAGE*)GUI_ALLOC_h2p(h))


void GUI_USAGE_DecUseCnt(GUI_USAGE_Handle  hUsage);

GUI_USAGE_Handle GUI_USAGE_BM_Create(int x0, int y0, int xsize, int ysize, int Flags);
void GUI_USAGE_Select(GUI_USAGE_Handle hUsage);
#define GUI_USAGE_AddPixel(p, x,y)            p->pAPI->pfAddPixel(p,x,y)
#define GUI_USAGE_AddHLine(p,x,y,len)         p->pAPI->pfAddHLine(p,x,y,len)
#define GUI_USAGE_Clear(p)                    p->pAPI->pfClear(p)
#define GUI_USAGE_Delete(p)                   p->pAPI->pfDelete(p)
#define GUI_USAGE_GetNextDirty(p,pxOff, yOff) p->pAPI->pfGetNextDirty(p,pxOff, yOff)

struct tsUSAGE_APIList {
  tUSAGE_AddPixel*                pfAddPixel;
  tUSAGE_AddHLine*                pfAddHLine;
  tUSAGE_Clear*                   pfClear;
  tUSAGE_CreateCompatible*        pfCreateCompatible;
  tUSAGE_Delete*                  pfDelete;
  tUSAGE_GetNextDirty*            pfGetNextDirty;
} ;

struct GUI_Usage {
  I16P x0, y0, XSize, YSize;
  const tUSAGE_APIList *pAPI;
  I16 UseCnt;
};

/*****************************************************
*
*        GUI_MEMDEV
*
******************************************************
*/

#if GUI_SUPPORT_MEMDEV
  typedef struct GUI_MemDev GUI_MEMDEV;

  struct GUI_MemDev {
    I16P                  x0, y0, XSize, YSize;
    int                   NumColors;
    int                   BytesPerLine;
    GUI_HMEM              hUsage;
    tLCDDEV_Color2Index*  pfColor2Index;
    tLCDDEV_Index2Color*  pfIndex2Color;
  };

  #define GUI_MEMDEV_h2p(h) ((GUI_MEMDEV*)GUI_ALLOC_h2p(h))
  void GUI_MEMDEV__CopyFromLCD(GUI_MEMDEV_Handle hMem);
#endif

/*******************************************************************
*
*                   LCD_HL_ level defines
*
********************************************************************
*/

#if GUI_SUPPORT_MEMDEV
  #define LCD_HL_DrawHLine             GUI_Context.pLCD_HL->pfDrawHLine
  #define LCD_HL_DrawPixel             GUI_Context.pLCD_HL->pfDrawPixel
#else
  #define LCD_HL_DrawHLine             LCD_DrawHLine
  #define LCD_HL_DrawPixel             LCD_DrawPixel
#endif


/*********************************************************************
*
*                     Helper functions
*
***********************************************************************
*/

#define GUI_ZEROINIT(Obj) memset(Obj, 0, sizeof(Obj))
int  GUI_cos(int angle);
int  GUI_sin(int angle);
void GL_DrawLine1(int x0, int y0, int x1, int y1);
extern const U32 GUI_Pow10[10];

/* GUIAALib.c --- direct anti-aliased drawing */
int  GUI_AA_Init(int x0, int x1);
int  GUI_AA_Init_HiRes(int x0, int x1);
void GUI_AA_Exit(void);
I16 GUI_AA_HiRes2Pixel(int HiRes);

void GL_FillCircleAA_HiRes(int x0, int y0, int r);

/* Conversion routines */
void GUI_AddHex(U32 v, U8 Len, char**ps);
void GUI_AddBin(U32 v, U8 Len, char**ps);
void GUI_AddDecShift(I32 v, U8 Len, U8 Shift, char**ps);
long GUI_AddSign(long v, char**ps);

int GUI__GetLineLen(const char GUI_FAR *s, int MaxLen);
int GUI_GetLineDistX(const char GUI_FAR *s, int Len);
int GUI__GetFontSizeY(void);
int GUI__HandleEOLine(const char* *ps);
void GUI__DispLine(const char GUI_FAR *s, int Len, const GUI_RECT* pr);
void GUI__AddSpaceHex(U32 v, U8 Len, char**ps);


/*********************************************************************
*
*             2d - GL
*
**********************************************************************
*/

void GL_DispChar         (U16 c);
void GL_DrawArc          (int x0, int y0, int rx, int ry, int a0, int a1);
void GL_DrawBitmap       (const GUI_BITMAP* pBM, int x0, int y0);
void GL_DrawCircle       (int x0, int y0, int r);
void GL_DrawEllipse      (int x0, int y0, int rx, int ry);
void GL_DrawHLine        (int y0, int x0, int x1);
void GL_DrawPolygon      (const GUI_POINT* pPoints, int NumPoints, int x0, int y0);
void GL_DrawPoint        (int x, int y);
void GL_DrawLineRel      (int dx, int dy);
void GL_DrawLineTo       (int x, int y);
void GL_DrawLine         (int x0, int y0, int x1, int y1);
void GL_MoveTo           (int x, int y);
void GL_FillCircle       (int x0, int y0, int r);
void GL_FillCircleAA     (int x0, int y0, int r);
void GL_FillEllipse      (int x0, int y0, int rx, int ry);
void GL_FillPolygon      (const GUI_POINT* pPoints, int NumPoints, int x0, int y0);
void GL_SetDefault       (void);

/************************************************************
*
*                 Callback pointers for dynamic linkage
*
*************************************************************
Dynamic linkage pointers reduces configuration hassles.
*/
typedef int  GUI_tfTimer(void);
typedef void GUI_CURSOR_tfTempHide  (const GUI_RECT* pRect);
typedef void GUI_CURSOR_tfTempUnhide(const GUI_RECT* pRect);
typedef int  WM_tfHandleHID(void);

/************************************************************
*
*         EXTERN decalartions/definitions
*
*************************************************************
Dynamic linkage pointers reduces configuration hassles.
*/
#ifdef  GL_CORE_C
  #define EXTERN
#else
  #define EXTERN extern
#endif

EXTERN GUI_SADDR GUI_CONTEXT GUI_Context; /* Thread wide globals */
EXTERN GUI_SADDR char GUI_DecChar;        /* System wide globals */

EXTERN GUI_tfTimer*       GUI_pfTimerExec;

EXTERN WM_tfHandleHID*  WM_pfHandleHID;

#if GUI_SUPPORT_CURSOR
  EXTERN GUI_CURSOR_tfTempHide*   GUI_CURSOR_pfTempHide;
  EXTERN GUI_CURSOR_tfTempUnhide* GUI_CURSOR_pfTempUnhide;
#endif

#undef EXTERN

#endif   /* ifdef GUI_H */
