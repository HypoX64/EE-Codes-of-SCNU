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
File        : SLIDER.c
Purpose     : SLIDER for new emWin GSC widgets
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "GUI_Private.H"
#include "SLIDER.h"
#include "Widget.h"


#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

/* Support for 3D effects */
#ifndef SLIDER_USE_3D
  #define SLIDER_USE_3D 1
#endif

/* Define colors */
#ifndef SLIDER_BKCOLOR0_DEFAULT
  #define SLIDER_BKCOLOR0_DEFAULT 0xc0c0c0
#endif

#ifndef SLIDER_BKCOLOR1_DEFAULT
  #define SLIDER_BKCOLOR1_DEFAULT GUI_WHITE
#endif

#ifndef SLIDER_COLOR0_DEFAULT
  #define SLIDER_COLOR0_DEFAULT 0xc0c0c0
#endif

#ifndef SLIDER_COLOR1_DEFAULT
  #define SLIDER_COLOR1_DEFAULT GUI_BLACK
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
  int Min, Max, v;
  int Flags;
  int NumSections;
  I16 Width;
  #if GUI_DEBUG_LEVEL >1
    int DebugId;
  #endif  
} SLIDER_Obj;

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

#define SLIDER_ID 0x4544   /* Magic numer, should be unique if possible */

#define SLIDER_H2P(h) (SLIDER_Obj*) WM_H2P(h)

#ifdef _DEBUG
  #define SLIDER_ASSERT_IS_VALID_PTR(p) DEBUG_ERROROUT_IF(p->DebugId != SLIDER_ID, "xxx.c: Wrong handle type or Object not init'ed")
  #define SLIDER_INIT_ID(p)   p->DebugId = SLIDER_ID
  #define SLIDER_DEINIT_ID(p) p->DebugId = SLIDER_ID+1
#else
  #define SLIDER_ASSERT_IS_VALID_PTR(p)
  #define SLIDER_INIT_ID(p)
  #define SLIDER_DEINIT_ID(p)
#endif

/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/

/*********************************************************************
*
*       _Paint
*/
static void _Paint(SLIDER_Obj* pObj/*, GUI_RECT*pRect*/) {
  int i;
  int xsize;
  int x0;
  GUI_RECT r, rFocus, rSlider, rSlot;
  WIDGET__GetClientRect(&pObj->Widget, &rFocus);
  GUI__ReduceRect(&r, &rFocus, 1);
  xsize = r.x1 - r.x0  + 1 - pObj->Width /*- 2*xSizeEffect*/;
  x0 = r.x0 + pObj->Width / 2;
  GUI_SetBkColor(pObj->aBkColor[0]);
  GUI_Clear();
  /* Calculate Slider position */
  rSlider = r;
  rSlider.y0 = 5;
  rSlider.x0 = x0 + xsize * (pObj->v - pObj->Min) / (pObj->Max - pObj->Min) - pObj->Width/2;
  rSlider.x1  = rSlider.x0 + pObj->Width;
  /* Calculate Slot position */
  rSlot.x0 = x0;
  rSlot.x1 = x0 + xsize;
  rSlot.y0 = (rSlider.y0 + rSlider.y1) /2 -1;
  rSlot.y1 = rSlot.y0 +3;
  WIDGET__EFFECT_DrawDownRect(&pObj->Widget, &rSlot);        /* Draw slot */
  /* Draw the ticks */
  GUI_SetColor(GUI_BLACK);
  for (i = 0; i <= pObj->NumSections; i++) {
    int x = x0 + xsize * i / pObj->NumSections;
    WIDGET__DrawVLine(&pObj->Widget, x, 1, 3);
  }
  /* Draw the slider itself */
  GUI_SetColor(pObj->aColor[0]);
  WIDGET__FillRectEx(&pObj->Widget, &rSlider);
  GUI_SetColor(GUI_BLACK);
  WIDGET__EFFECT_DrawUpRect(&pObj->Widget, &rSlider);
  /* Draw focus */
  if (pObj->Widget.State & WIDGET_STATE_FOCUS) {
    GUI_SetColor(GUI_BLACK);
    WIDGET__DrawFocusRect(&pObj->Widget, &rFocus, 0);
  }
}


/*********************************************************************
*
*       _OnTouch
*/
static void _OnTouch(SLIDER_Handle hObj, SLIDER_Obj* pObj, WM_MESSAGE*pMsg) {
  GUI_TOUCH_tState* pState = (GUI_TOUCH_tState*)pMsg->Data.p;
  if (pMsg->Data.p) {  /* Something happened in our area (pressed or released) */
    if (pState->Pressed) {
      int Sel;
      int Range = (pObj->Max - pObj->Min);
      int x0, xsize;
      int x;
      x0 = 1 + pObj->Width/2;  /* 1 pixel focus rectangle + width of actual slider */
      x = (pObj->Widget.State & WIDGET_STATE_VERTICAL) ? pState->y : pState->x;
      x -= x0;
      xsize = WIDGET__GetWindowSizeX(hObj) - 2 * x0;
      if (x <= 0) {
        Sel = pObj->Min;
      } else if (x >= xsize) {
        Sel = pObj->Max;
      } else {
        Sel = GUI__DivideRound(Range* x, xsize);
        Sel += pObj->Min;
      }
      WM_SetFocus(hObj);
      WM_SetCapture(hObj, 1);
      SLIDER_SetValue(hObj, Sel);
    } 
  }
}

/*********************************************************************
*
*       _OnKey
*/
static void  _OnKey(SLIDER_Handle hObj, WM_MESSAGE*pMsg) {
  WM_KEY_INFO* pKeyInfo;
  int Key;
  pKeyInfo = (WM_KEY_INFO*)(pMsg->Data.p);
  Key = pKeyInfo->Key;
  if (pKeyInfo->PressedCnt > 0) {
    switch (Key) {
      case GUI_KEY_RIGHT:
        SLIDER_Inc(hObj);
        break;                    /* Send to parent by not doing anything */
      case GUI_KEY_LEFT:
        SLIDER_Dec(hObj);
        break;                    /* Send to parent by not doing anything */
      default:
        return;
    }
  }
}

/*********************************************************************
*
*       _SLIDER_Callback
*/
static void _SLIDER_Callback (WM_MESSAGE *pMsg) {
  SLIDER_Handle hObj;
  SLIDER_Obj* pObj;
  hObj = pMsg->hWin;
  pObj = SLIDER_H2P(hObj);
  /* Let widget handle the standard messages */
  if (WIDGET_HandleActive(hObj, pMsg) == 0) {
    return;
  }
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_DEBUG_LOG("SLIDER: _Callback(WM_PAINT)\n");
    _Paint(pObj);
    return;
  case WM_TOUCH:
    _OnTouch(hObj, pObj, pMsg);
    break;
  case WM_KEY:
    _OnKey(hObj, pMsg);
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


SLIDER_Handle SLIDER_Create (int x0, int y0, int xsize, int ysize, WM_HWIN hParent, int Id, int WinFlags, int SpecialFlags) {
  SLIDER_Handle hObj;
  /* Create the window */
  WM_LOCK();
  hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent,
                       WinFlags, _SLIDER_Callback, sizeof(SLIDER_Obj)-sizeof(WM_Obj));
  if (hObj) {
    SLIDER_Obj* pObj = SLIDER_H2P(hObj);
    U16 InitState;
    /* Handle SpecialFlags */
    InitState = WIDGET_STATE_ENABLED;
    if (SpecialFlags & SLIDER_CF_VERTICAL) {
      InitState |= WIDGET_CF_VERTICAL;
    }
    /* init widget specific variables */
    WIDGET__Init(&pObj->Widget, InitState);
    /* init member variables */
    SLIDER_INIT_ID(pObj);
    pObj->Widget.Id       = Id;
    pObj->aBkColor[0]   = SLIDER_BKCOLOR0_DEFAULT;
    pObj->aBkColor[1]   = SLIDER_BKCOLOR1_DEFAULT;
    pObj->aColor[0]     = SLIDER_COLOR0_DEFAULT;
    pObj->aColor[1]     = SLIDER_COLOR1_DEFAULT;
    pObj->Width = 8;
    pObj->Max =100;
    pObj->Min =0;
    pObj->NumSections = 10;
  } else {
    GUI_DEBUG_ERROROUT_IF(hObj==0, "SLIDER_Create failed")
  }
  WM_UNLOCK();
  return hObj;
}

SLIDER_Handle SLIDER_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb) {
  SLIDER_Handle  hThis;
  GUI_USE_PARA(cb);
  hThis = SLIDER_Create(pCreateInfo->x0 + x0, pCreateInfo->y0 + y0, pCreateInfo->xSize, pCreateInfo->ySize,
                        hWinParent, pCreateInfo->Id, 0, pCreateInfo->Flags);
  return hThis;
}

/*********************************************************************
*
*       Exported routines:  Various methods
*
**********************************************************************
*/
void SLIDER_Dec(SLIDER_Handle hObj) {
  SLIDER_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = SLIDER_H2P(hObj);
    if (pObj->v > pObj->Min) {
      pObj->v--;
      WM_InvalidateWindow(hObj);
      WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
    }
    WM_UNLOCK();
  }
}

void SLIDER_Inc(SLIDER_Handle hObj) {
  SLIDER_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = SLIDER_H2P(hObj);
    if (pObj->v < pObj->Max) {
      pObj->v++;
      WM_InvalidateWindow(hObj);
      WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
    }
    WM_UNLOCK();
  }
}

void SLIDER_SetWidth(SLIDER_Handle hObj, int Width) {
  SLIDER_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = SLIDER_H2P(hObj);
    if (pObj->Width != Width) {
      pObj->Width = Width;
      WM_InvalidateWindow(hObj);
    }
    WM_UNLOCK();
  }
}

void SLIDER_SetValue(SLIDER_Handle hObj, int v) {
  SLIDER_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = SLIDER_H2P(hObj);
    /* Put in min/max range */
    if (v < pObj->Min) {
      v = pObj->Min;
    }
    if (v > pObj->Max) {
      v = pObj->Max;
    }
    if (pObj->v != v) {
      pObj->v = v;
      WM_InvalidateWindow(hObj);
      WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
    }
    WM_UNLOCK();
  }
}

void SLIDER_SetRange(SLIDER_Handle hObj, int Min, int Max) {
  SLIDER_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = SLIDER_H2P(hObj);
    pObj->Min = Min;
    pObj->Max = Max;
    WM_InvalidateWindow(hObj);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       Query state
*
**********************************************************************
*/
int SLIDER_GetValue(SLIDER_Handle hObj) {
  int r = 0;
  SLIDER_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = SLIDER_H2P(hObj);
    r = pObj->v;
    WM_UNLOCK();
  }
  return r;
}


#endif  /* #if GUI_WINSUPPORT */



