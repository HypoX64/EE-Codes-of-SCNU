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
File        : ProgBar.c
Purpose     : Progress bar for emWin GSC
---------------------------END-OF-HEADER------------------------------
*/


#include <stdlib.h>
#include <string.h>
#include "GUI_Private.h"
#include "ProgBar.h"
#include "Widget.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

#ifndef PROGBAR_DEFAULT_FONT
  #define PROGBAR_DEFAULT_FONT GUI_DEFAULT_FONT
#endif

#ifndef PROGBAR_DEFAULT_BARCOLOR0
  #define PROGBAR_DEFAULT_BARCOLOR0 0x555555
#endif

#ifndef PROGBAR_DEFAULT_BARCOLOR1
  #define PROGBAR_DEFAULT_BARCOLOR1 0xAAAAAA
#endif

#ifndef PROGBAR_DEFAULT_TEXTCOLOR0
  #define PROGBAR_DEFAULT_TEXTCOLOR0 0xFFFFFF
#endif

#ifndef PROGBAR_DEFAULT_TEXTCOLOR1
  #define PROGBAR_DEFAULT_TEXTCOLOR1 0x000000
#endif

/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/

typedef struct {
  WIDGET Widget;
  int v;
  const GUI_FONT* pFont;
  GUI_COLOR BarColor[2];
  GUI_COLOR TextColor[2];
  WM_HMEM hpText;
  I16 XOff, YOff;
  I16 TextAlign;
  int Min, Max;
/*  I16 Options; */
  #if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
    int DebugId;
  #endif  
} PROGBAR_Obj;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

/* None */

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/

#define Invalidate(h) WM_InvalidateWindow(h)

#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  #define OBJECT_ID 0x4569   /* Magic nubmer, should be unique if possible */
  #define INIT_ID(p)   p->DebugId = OBJECT_ID
  #define DEINIT_ID(p) p->DebugId = OBJECT_ID+1
#else
  #define INIT_ID(p)
  #define DEINIT_ID(p)
#endif

/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/

#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  PROGBAR_Obj* PROGBAR_h2p(PROGBAR_Handle h) {
    PROGBAR_Obj* p = (PROGBAR_Obj*)WM_HMEM2Ptr(h);
    if (p) {
      if (p->DebugId != OBJECT_ID) {
        GUI_DEBUG_ERROROUT("PROGBAR.C: Wrong handle type or Object not init'ed");
        return 0;
      }
    }
    return p;
  }
  #define PROGBAR_H2P(h) PROGBAR_h2p(h)
#else
  #define PROGBAR_H2P(h) (PROGBAR_Obj*) WM_HMEM2Ptr(h)
#endif

/*********************************************************************
*
*       _FreeText
*/
static void _FreeText(PROGBAR_Handle hObj) {
  PROGBAR_Obj* pObj = PROGBAR_H2P(hObj);
  WM_FREEPTR(&pObj->hpText);
}

/*********************************************************************
*
*       _Value2X
*/
static int _Value2X(PROGBAR_Handle hObj, int v) {
  PROGBAR_Obj* pObj = PROGBAR_H2P(hObj);
  int xsize  = WM_GetWindowSizeX(hObj);
  int Min = pObj->Min;
  int Max = pObj->Max;
  if (v<Min)
	  v = Min;
  if (v> Max)
	  v = Max;
  return (xsize* (I32)(v-Min)) / (Max-Min);
}

/*********************************************************************
*
*       _DrawPart
*/
static void _DrawPart(PROGBAR_Obj* pThis,
                     int Index,
										 int xText, int yText,
										 const char* pText)
{
    GUI_SetBkColor(pThis->BarColor[Index]);
    GUI_SetColor(pThis->TextColor[Index]);
    GUI_Clear();
    GUI_GotoXY(xText,yText);
		GUI_DispString(pText);
}

/*********************************************************************
*
*       _Paint
*/
static void _Paint(PROGBAR_Handle hObj) {
  PROGBAR_Obj* pObj = PROGBAR_H2P(hObj);
  WM_HWIN hWin = hObj;
  int xsize = WM_GetWindowSizeX(hWin);
  int ysize = WM_GetWindowSizeY(hWin);
  int tm;
  GUI_SetFont(pObj->pFont);
  {
    int x1;
    int FontSizeY = GUI_GetFontSizeY();
    int xText;
    int yText = (ysize-FontSizeY)/2;
    GUI_RECT r;
    int XSizeChar;
    char ac[5];   /* Just enough for the percentage */
    char*s = ac;
    const char* pText;
    if (pObj->hpText != WM_HMEM_NULL) {
      pText = (const char*) WM_HMEM2Ptr(pObj->hpText);
    } else {
      GUI_AddDecMin((100*(I32)(pObj->v-pObj->Min))/(pObj->Max-pObj->Min), &s);
      *s = '%';
			*(s+1) =0;
			pText = &ac[0];
		}
/* Calculate text positions */
    XSizeChar = GUI_GetStringDistX(pText);
    x1 = _Value2X(hObj, pObj->v);
    switch (pObj->TextAlign &GUI_TA_HORIZONTAL) {
    case GUI_TA_CENTER:
      xText  = (xsize-XSizeChar)/2;
			break;
    case GUI_TA_LEFT:
      xText  = 0;
			break;
    case GUI_TA_RIGHT:
      xText  = xsize-XSizeChar-1;
			break;
		}
    xText += pObj->XOff;
    yText += pObj->YOff;
    tm = GUI_SetTextMode(GUI_TM_TRANS);
/* Draw left bar */
    r.x0=0; r.x1=x1-1; r.y0=0; r.y1 = GUI_YMAX;
    WM_SetUserClipArea(&r);
    _DrawPart(pObj, 0, xText, yText, pText);
/* Draw right bar */
    r.x0=r.x1+1; r.x1=GUI_XMAX;
    WM_SetUserClipArea(&r);
    _DrawPart(pObj, 1, xText, yText, pText);
  }
  WM_SetUserClipArea(NULL);
  GUI_SetTextMode(tm);
}

/*********************************************************************
*
*       _Delete
*/
void _Delete(PROGBAR_Handle hObj) {
  _FreeText(hObj);
  DEINIT_ID(PROGBAR_H2P(hObj));
}

/*********************************************************************
*
*       _Callback
*/
static void _Callback (WM_MESSAGE*pMsg) {
  PROGBAR_Handle hObj = (PROGBAR_Handle)pMsg->hWin;
  switch (pMsg->MsgId) {
  case WM_PAINT:
    _Paint(hObj);
    return;
  case WM_DELETE:
    _Delete(hObj);
    break;
  }
  WM_DefaultProc(pMsg);
}

/*********************************************************************
*
*       Exported routines:  Create
*
**********************************************************************
*/

PROGBAR_Handle PROGBAR_CreateEx(int x0, int y0, int xsize, int ysize, WM_HWIN hParent, int Id, int Flags) {
  /* Create the window */
  PROGBAR_Handle hObj =WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, 
                                              Flags, _Callback, sizeof(PROGBAR_Obj) - sizeof(WM_Obj));
  if (hObj) {
    PROGBAR_Obj* pObj = (PROGBAR_Obj*) WM_HMEM2Ptr(hObj);
    INIT_ID(pObj);
    pObj->Widget.Id       = Id;
    /* init member variables */
    pObj->pFont =GUI_DEFAULT_FONT;
    pObj->BarColor[0] = 0x555555;
    pObj->BarColor[1] = 0xaaaaaa;
    pObj->TextColor[0] = 0xffffff;
    pObj->TextColor[1] = 0x000000;
    pObj->TextAlign    = GUI_TA_CENTER;
    pObj->Max =100;
    pObj->Min =0;
  }
  return hObj;
}

PROGBAR_Handle PROGBAR_Create(int x0, int y0, int xsize, int ysize, int Flags) {
  return PROGBAR_CreateEx(x0, y0, xsize, ysize, 0, 0, Flags) ;
}

PROGBAR_Handle  PROGBAR_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb) {
  PROGBAR_Handle  hThis;
  GUI_USE_PARA(cb);
  hThis = PROGBAR_CreateEx(
    pCreateInfo->x0 + x0, pCreateInfo->y0 + y0, pCreateInfo->xSize, pCreateInfo->ySize,
    hWinParent, pCreateInfo->Id, pCreateInfo->Flags);
  return hThis;
}

/*********************************************************************
*
*       Exported routines:  Various methods
*
**********************************************************************
*/
void PROGBAR_SetValue(PROGBAR_Handle hObj, int v) {
  PROGBAR_Obj* pObj;
  GUI_RECT r;
  if (hObj) {
    WM_LOCK();
    pObj= PROGBAR_H2P(hObj);
    /* Put v into legal range */
    if (v < pObj->Min)
	    v = pObj->Min;
    if (v > pObj->Max)
	    v = pObj->Max;
    if (pObj->v != v) {
      /* Invalidate */
      if (pObj->hpText) {
        /* Calculate invalid area */
        r.x0 = _Value2X(hObj, pObj->v);
        r.x1 = _Value2X(hObj, v);
        /* Make sure x0 <= x1 */
		    if (r.x0 > r.x1) {
			    int t = r.x0;
			    r.x0 = r.x1;
			    r.x1 = t;
		    }
		    r.y0 =0;
		    r.y1 =4095;
        WM_InvalidateRect(hObj,&r);
	    } else {
        Invalidate(hObj);
	    }
      pObj->v = v;                         /* Update stored value */
    }
    WM_UNLOCK();
  }
}

void PROGBAR_SetFont(PROGBAR_Handle hObj, const GUI_FONT* pfont) {
  PROGBAR_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = PROGBAR_H2P(hObj);
    pObj->pFont = pfont;
    Invalidate(hObj);
    WM_UNLOCK();
  }
}

void PROGBAR_SetBarColor(PROGBAR_Handle hObj, int index, GUI_COLOR color) {
  PROGBAR_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = PROGBAR_H2P(hObj);
    pObj->BarColor[index] = color;
    Invalidate(hObj);
    WM_UNLOCK();
  }
}

void PROGBAR_SetTextColor(PROGBAR_Handle hObj, int index, GUI_COLOR color) {
  PROGBAR_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = PROGBAR_H2P(hObj);
    pObj->TextColor[index] = color;
    Invalidate(hObj);
    WM_UNLOCK();
  }
}

void PROGBAR_SetText(PROGBAR_Handle hObj, const char* s) {
  PROGBAR_Obj* pObj;
  WM_HMEM hMem;
  if (hObj) {
    WM_LOCK();
    pObj = PROGBAR_H2P(hObj);
    _FreeText(hObj);
    hMem = WM_ALLOC(strlen(s)+1);
    strcpy((char *) WM_HMEM2Ptr(hMem), s);
    pObj->hpText = hMem;
    Invalidate(hObj);
    WM_UNLOCK();
  }
}

void PROGBAR_SetTextAlign(PROGBAR_Handle hObj, int Align) {
  PROGBAR_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = PROGBAR_H2P(hObj);
    pObj->TextAlign = Align;
    Invalidate(hObj);
    WM_UNLOCK();
  }
}

void PROGBAR_SetTextPos(PROGBAR_Handle hObj, int XOff, int YOff) {
  PROGBAR_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = PROGBAR_H2P(hObj);
    pObj->XOff = XOff;
    pObj->YOff = YOff;
    Invalidate(hObj);
    WM_UNLOCK();
  }
}

void PROGBAR_SetMinMax(PROGBAR_Handle hObj, int Min, int Max) {
  PROGBAR_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = PROGBAR_H2P(hObj);
    if (Max > Min) {
      if ((Max != pObj->Max) || (Min != pObj->Min)) {
        pObj->Min = Min;
        pObj->Max = Max;
        Invalidate(hObj);
      }
    }
    WM_UNLOCK();
  }
}

#else

void WIDGET_Progbar(void) {} /* avoid empty object files */

#endif /* GUI_WINSUPPORT */
