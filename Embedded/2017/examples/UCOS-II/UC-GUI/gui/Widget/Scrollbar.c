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
File        : SCROLLBAR.c
Purpose     : SCROLLBAR for new emWin GSC widgets
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "GUI_Private.H"
#include "SCROLLBAR.h"
#include "Widget.h"


#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

/* Support for 3D effects */
#ifndef SCROLLBAR_USE_3D
  #define SCROLLBAR_USE_3D 1
#endif

/* Define colors */
#ifndef SCROLLBAR_BKCOLOR0_DEFAULT
  #define SCROLLBAR_BKCOLOR0_DEFAULT 0x808080
#endif

#ifndef SCROLLBAR_BKCOLOR1_DEFAULT
  #define SCROLLBAR_BKCOLOR1_DEFAULT GUI_BLACK
#endif

#ifndef SCROLLBAR_COLOR0_DEFAULT
  #define SCROLLBAR_COLOR0_DEFAULT 0xc0c0c0
#endif

#ifndef SCROLLBAR_COLOR1_DEFAULT
  #define SCROLLBAR_COLOR1_DEFAULT GUI_BLACK
#endif


/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/

typedef struct {
  WIDGET Widget;
  GUI_COLOR aBkColor[2];
  GUI_COLOR aColor[2];
  int NumItems, v, PageSize;
  #if GUI_DEBUG_LEVEL >1
    int DebugId;
  #endif  
} SCROLLBAR_Obj;

typedef struct {
  int x1_LeftArrow;
  int x0_Thumb;
  int x1_Thumb;
  int x0_RightArrow;
  int xSizeMoveable;
  int ThumbSize;
} POSITIONS;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

I16 _DefaultWidth = 11;

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/

#define SCROLLBAR_ID 0x4544   /* Magic numer, should be unique if possible */

#define SCROLLBAR_H2P(h) (SCROLLBAR_Obj*) WM_H2P(h)

#ifdef _DEBUG
  #define SCROLLBAR_ASSERT_IS_VALID_PTR(p) DEBUG_ERROROUT_IF(p->DebugId != SCROLLBAR_ID, "xxx.c: Wrong handle type or Object not init'ed")
  #define SCROLLBAR_INIT_ID(p)   p->DebugId = SCROLLBAR_ID
  #define SCROLLBAR_DEINIT_ID(p) p->DebugId = SCROLLBAR_ID+1
#else
  #define SCROLLBAR_ASSERT_IS_VALID_PTR(p)
  #define SCROLLBAR_INIT_ID(p)
  #define SCROLLBAR_DEINIT_ID(p)
#endif

/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/
static int _GetArrowSize(SCROLLBAR_Obj* pObj) {
  unsigned int r;
  unsigned int xSize = WIDGET__GetXSize(&pObj->Widget);
  unsigned int ySize = WIDGET__GetYSize(&pObj->Widget);
  r = ySize/2 + 5;
  if (r > xSize-5)
    r = xSize-5;
  return r;
}

/*********************************************************************
*
*       _GetPositions

  Calculates all positions required for drawing or for mouse / touch
  evaluation.
*/
static void _GetPositions(SCROLLBAR_Obj* pObj, POSITIONS* pPos) {
  int xSizeArrow, xSize, xSizeMoveable, ThumbSize, NumItems, xSizeThumbArea;
  NumItems      = pObj->NumItems;
  xSize         = WIDGET__GetXSize(&pObj->Widget);
  xSizeArrow    = _GetArrowSize(pObj);
  xSizeThumbArea= xSize - 2*xSizeArrow;     /* Number of pixels available for thumb and movement */
  ThumbSize     = GUI__DivideRound(xSizeThumbArea * pObj->PageSize, NumItems);
  if (ThumbSize < 4)
    ThumbSize = 4;
  xSizeMoveable = xSizeThumbArea - ThumbSize;
  pPos->x1_LeftArrow  = xSizeArrow-1;
  pPos->x0_RightArrow = xSize - xSizeArrow;
  pPos->x0_Thumb      = pPos->x1_LeftArrow + 1+ GUI__DivideRound(xSizeMoveable * pObj->v, NumItems - pObj->PageSize);
  pPos->x1_Thumb      = pPos->x0_Thumb + ThumbSize - 1;
  pPos->xSizeMoveable = xSizeMoveable;
  pPos->ThumbSize     = ThumbSize;
}

/*********************************************************************
*
*       _DrawTriangle
*/
static void _DrawTriangle(WIDGET* pWidget, int x, int y, int Size, int Inc) {
  if (pWidget->State & WIDGET_STATE_VERTICAL) {
    for (; Size >= 0; Size--, x += Inc) {
      GUI_DrawHLine(x, y - Size, y + Size);
    }
  } else {
    for (; Size >= 0; Size--, x += Inc) {
      GUI_DrawVLine(x, y - Size, y + Size);
    }
  }
}

/*********************************************************************
*
*       _Paint
*/
static void _Paint(SCROLLBAR_Obj* pObj) {
  int xArrow, ArrowSize, ArrowOff;
  POSITIONS Pos;
  GUI_RECT r, rClient;
  /*
    Get / calc position info
  */
  _GetPositions(pObj, &Pos);
  xArrow = _GetArrowSize(pObj);
  WIDGET__GetClientRect(&pObj->Widget, &rClient);
  r = rClient;
  ArrowSize = ((r.y1 - r.y0) /3) - 1;
  /*
    Draw the thumb area ( optimized ... We could also fill using GUI_Clear())
  */
  GUI_SetColor(pObj->aBkColor[0]);
  r = rClient;
  r.x0 = Pos.x1_LeftArrow + 1;
  r.x1 = Pos.x0_Thumb - 1;
  WIDGET__FillRectEx(&pObj->Widget, &r);
  r.x0 = Pos.x1_Thumb + 1;
  r.x1 = Pos.x0_RightArrow - 1;
  WIDGET__FillRectEx(&pObj->Widget, &r);
  /*
    Draw left Arrow
  */
  ArrowOff = 3 + ArrowSize+ ArrowSize/3;
  GUI_SetColor(pObj->aColor[0]);
  r = rClient;
  r.x1 = xArrow-1;
  WIDGET__FillRectEx(&pObj->Widget, &r);
  GUI_SetColor(pObj->aBkColor[1]);
  _DrawTriangle(&pObj->Widget, r.x0 + ArrowOff, (r.y1 - r.y0) >> 1, ArrowSize, -1);
  WIDGET__EFFECT_DrawUpRect(&pObj->Widget, &r);
  /*
    Draw right Arrow
  */
  GUI_SetColor(pObj->aColor[0]);
  r = rClient;
  r.x0 = r.x1 - (xArrow - 1);
  WIDGET__FillRectEx(&pObj->Widget, &r);
  GUI_SetColor(pObj->aBkColor[1]);
  _DrawTriangle(&pObj->Widget, r.x1 - ArrowOff, (r.y1 - r.y0) >> 1, ArrowSize, 1);
  WIDGET__EFFECT_DrawUpRect(&pObj->Widget, &r);
  /*
    Draw Thumb
  */
  r = rClient;
  r.x0 = Pos.x0_Thumb;
  r.x1 = Pos.x1_Thumb;
  GUI_SetColor(pObj->aColor[0]);
  WIDGET__FillRectEx(&pObj->Widget, &r);
  WIDGET__EFFECT_DrawUpRect(&pObj->Widget, &r);
}


/*********************************************************************
*
*       _OnTouch
*/
static void _OnTouch(SCROLLBAR_Handle hObj, SCROLLBAR_Obj* pObj, WM_MESSAGE*pMsg) {
  POSITIONS Pos;
  GUI_TOUCH_tState* pState = (GUI_TOUCH_tState*)pMsg->Data.p;
  if (pMsg->Data.p) {  /* Something happened in our area (pressed or released) */
    if (pState->Pressed) {
      int Sel;
      int Range;
      int x;
      Sel = pObj->v;
      _GetPositions(pObj, &Pos);
      Range = pObj->NumItems - pObj->PageSize;
      /* Swap mouse coordinates if necessary */
      if (pObj->Widget.State & WIDGET_STATE_VERTICAL) {
        int t = pState->x;
        pState->x = pState->y;
        pState->y = t;
      }
      x = pState->x;
      if (x <= Pos.x1_LeftArrow) {         /* left arrow (line left) */
        Sel--;
      } else if (x < Pos.x0_Thumb) {       /* left area  (page left) */
        Sel -= pObj->PageSize;
      } else if (x <= Pos.x1_Thumb) {      /* Thumb area */
        if (Pos.xSizeMoveable > 0) {
          x = x - Pos.ThumbSize/2 - Pos.x1_LeftArrow-1;
          Sel = GUI__DivideRound(Range * x, Pos.xSizeMoveable);
        }
      } else if (x < Pos.x0_RightArrow) {  /* right area (page right) */
        Sel += pObj->PageSize;
      } else {
        Sel++;
      }
      /* WM_SetFocus(hObj); */
      WM_SetCapture(hObj, 1);
      SCROLLBAR_SetValue(hObj, Sel);
    }
  }
}

/*********************************************************************
*
*       _OnKey
*/
static void  _OnKey(SCROLLBAR_Handle hObj, WM_MESSAGE*pMsg) {
  WM_KEY_INFO* pKeyInfo;
  int Key;
  pKeyInfo = (WM_KEY_INFO*)(pMsg->Data.p);
  Key = pKeyInfo->Key;
  if (pKeyInfo->PressedCnt > 0) {
    switch (Key) {
      case GUI_KEY_RIGHT:
      case GUI_KEY_DOWN:
        SCROLLBAR_Inc(hObj);
        break;                    /* Send to parent by not doing anything */
      case GUI_KEY_LEFT:
      case GUI_KEY_UP:
        SCROLLBAR_Dec(hObj);
        break;                    /* Send to parent by not doing anything */
      default:
        return;
    }
  }
}

/*********************************************************************
*
*       _OnSetScrollState 
*/
static void _OnSetScrollState(SCROLLBAR_Handle hObj, SCROLLBAR_Obj* pObj, const WM_SCROLL_STATE* pState) {
  pObj->NumItems = pState->NumItems;
  pObj->PageSize = pState->PageSize;
  pObj->v        = pState->v;
  WM_InvalidateWindow(hObj);
}


/*********************************************************************
*
*       _SCROLLBAR_Callback
*/
static void _SCROLLBAR_Callback (WM_MESSAGE *pMsg) {
  SCROLLBAR_Handle hObj;
  SCROLLBAR_Obj* pObj;
  hObj = pMsg->hWin;
  pObj = SCROLLBAR_H2P(hObj);
  /* Let widget handle the standard messages */
  if (WIDGET_HandleActive(hObj, pMsg) == 0) {
    return;
  }
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_DEBUG_LOG("SCROLLBAR: _Callback(WM_PAINT)\n");
    _Paint(pObj);
    return;
  case WM_TOUCH:
    _OnTouch(hObj, pObj, pMsg);
    break;
  case WM_KEY:
    _OnKey(hObj, pMsg);
    break;
  case WM_SET_SCROLL_STATE:
    _OnSetScrollState(hObj, pObj, (const WM_SCROLL_STATE*)pMsg->Data.p);
    break;
  case WM_GET_SCROLL_STATE:
    ((WM_SCROLL_STATE*)pMsg->Data.p)->NumItems = pObj->NumItems;
    ((WM_SCROLL_STATE*)pMsg->Data.p)->PageSize = pObj->PageSize;
    ((WM_SCROLL_STATE*)pMsg->Data.p)->v        = pObj->v;
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

/* Note: the parameters to a create function may vary.
         Some widgets may have multiple create functions */


SCROLLBAR_Handle SCROLLBAR_Create (int x0, int y0, int xsize, int ysize, WM_HWIN hParent, int Id, int WinFlags, int SpecialFlags) {
  SCROLLBAR_Handle hObj;
  WM_LOCK();
  /* Set defaults if necessary */
  if ((xsize == 0) && (ysize == 0)) {
    GUI_RECT Rect;
    WM_GetInsideRect(hParent, &Rect);
    if (SpecialFlags & SCROLLBAR_CF_VERTICAL) {
      xsize = _DefaultWidth;
      x0 = Rect.x1 +1 - xsize;
      y0 = Rect.y0;
      ysize = Rect.y1 - Rect.y0 +1;
    } else {
      ysize = _DefaultWidth;
    }
  }
  /* Create the window */
  hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent,
                       WinFlags, _SCROLLBAR_Callback, sizeof(SCROLLBAR_Obj)-sizeof(WM_Obj));
  if (hObj) {
    SCROLLBAR_Obj* pObj = SCROLLBAR_H2P(hObj);
    U16 InitState;
    /* Handle SpecialFlags */
    InitState = WIDGET_STATE_ENABLED;
    if (SpecialFlags & SCROLLBAR_CF_VERTICAL) {
      InitState |= WIDGET_CF_VERTICAL;
    }
    if ((SpecialFlags & SCROLLBAR_CF_FOCUSSABLE) == 0) {
      InitState |= WIDGET_STATE_FOCUSSABLE;
    }
    /* init widget specific variables */
    WIDGET__Init(&pObj->Widget, InitState);
    /* init member variables */
    SCROLLBAR_INIT_ID(pObj);
    pObj->Widget.Id       = Id;
    pObj->aBkColor[0]   = SCROLLBAR_BKCOLOR0_DEFAULT;
    pObj->aBkColor[1]   = SCROLLBAR_BKCOLOR1_DEFAULT;
    pObj->aColor[0]     = SCROLLBAR_COLOR0_DEFAULT;
    pObj->aColor[1]     = SCROLLBAR_COLOR1_DEFAULT;
    pObj->NumItems      = 100;
    pObj->PageSize      =  10;
  } else {
    GUI_DEBUG_ERROROUT_IF(hObj==0, "SCROLLBAR_Create failed")
  }
  WM_UNLOCK();
  return hObj;
}

SCROLLBAR_Handle SCROLLBAR_CreateAttached(WM_HWIN hParent, int SpecialFlags) {
  SCROLLBAR_Handle  hThis;
  int Id;
  Id = (SpecialFlags & SCROLLBAR_CF_VERTICAL) ? GUI_ID_VSCROLL : GUI_ID_HSCROLL;
  hThis = SCROLLBAR_Create(0,0,0,0, hParent, Id, WM_CF_SHOW,         /* WinFlags */
                           SpecialFlags);
  if (hThis) {
    WM_MESSAGE Msg;
    Msg.MsgId = WM_ADD_SCROLLBAR;
    WM_SendMessage(hParent, &Msg);
  }
  return hThis;
}

SCROLLBAR_Handle SCROLLBAR_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb) {
  SCROLLBAR_Handle  hThis;
  GUI_USE_PARA(cb);
  hThis = SCROLLBAR_Create(pCreateInfo->x0 + x0, pCreateInfo->y0 + y0, pCreateInfo->xSize, pCreateInfo->ySize,
                        hWinParent, pCreateInfo->Id, 0, pCreateInfo->Flags);
  return hThis;
}

/*********************************************************************
*
*       Exported routines:  Various methods
*
**********************************************************************
*/


void SCROLLBAR_Dec(SCROLLBAR_Handle hObj) { SCROLLBAR_AddValue(hObj, -1); }
void SCROLLBAR_Inc(SCROLLBAR_Handle hObj) { SCROLLBAR_AddValue(hObj,  1); }

void SCROLLBAR_AddValue(SCROLLBAR_Handle hObj, int Add) {
  SCROLLBAR_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = SCROLLBAR_H2P(hObj);
    SCROLLBAR_SetValue(hObj, pObj->v + Add);
    WM_UNLOCK();
  }
}

void SCROLLBAR_SetValue(SCROLLBAR_Handle hObj, int v) {
  SCROLLBAR_Obj* pObj;
  int Max;
  if (hObj) {
    WM_LOCK();
    pObj = SCROLLBAR_H2P(hObj);
    Max = pObj->NumItems - pObj->PageSize;
    if (Max < 0)
      Max =0;
    /* Put in min/max range */
    if (v < 0) {
      v = 0;
    }
    if (v > Max) {
      v = Max;
    }
    if (pObj->v != v) {
      pObj->v = v;
      WM_InvalidateWindow(hObj);
      WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
    }
    WM_UNLOCK();
  }
}

void SCROLLBAR_SetNumItems(SCROLLBAR_Handle hObj, int NumItems) {
  SCROLLBAR_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = SCROLLBAR_H2P(hObj);
    if (pObj->NumItems != NumItems) {
      pObj->NumItems = NumItems;
      WM_InvalidateWindow(hObj);
    }
    WM_UNLOCK();
  }
}

void SCROLLBAR_SetPageSize(SCROLLBAR_Handle hObj, int PageSize) {
  SCROLLBAR_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = SCROLLBAR_H2P(hObj);
    if (pObj->PageSize != PageSize) {
      pObj->PageSize = PageSize;
      WM_InvalidateWindow(hObj);
    }
    WM_UNLOCK();
  }
}

void  SCROLLBAR_SetState   (SCROLLBAR_Handle hObj, const WM_SCROLL_STATE* pState) {
  if (hObj) {
    SCROLLBAR_SetPageSize(hObj, pState->PageSize);
    SCROLLBAR_SetNumItems(hObj, pState->NumItems);
    SCROLLBAR_SetValue   (hObj, pState->v);
  }
}

/*********************************************************************
*
*       Query state
*
**********************************************************************
*/
int SCROLLBAR_GetValue(SCROLLBAR_Handle hObj) {
  int r = 0;
  SCROLLBAR_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = SCROLLBAR_H2P(hObj);
    r = pObj->v;
    WM_UNLOCK();
  }
  return r;
}


#endif  /* #if GUI_WINSUPPORT */



