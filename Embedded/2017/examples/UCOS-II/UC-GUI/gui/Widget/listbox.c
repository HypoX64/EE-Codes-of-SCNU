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
File        : LISTBOX.c
Purpose     : Multiple choice for emWin GSC
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "LISTBOX.h"
#include "SCROLLBAR.h"
#include "WIDGET.h"
#include "GUIDebug.h"
#include "GUI_Protected.h"
#include "WM_Intern.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

/* Support for 3D effects */
#ifndef LISTBOX_USE_3D
  #define LISTBOX_USE_3D 1
#endif

/* Define default fonts */
#ifndef LISTBOX_FONT_DEFAULT
  #define LISTBOX_FONT_DEFAULT &GUI_Font13_1
#endif

/* Define colors */
#ifndef LISTBOX_BKCOLOR0_DEFAULT
  #define LISTBOX_BKCOLOR0_DEFAULT GUI_WHITE
#endif

#ifndef LISTBOX_BKCOLOR1_DEFAULT
  #define LISTBOX_BKCOLOR1_DEFAULT GUI_GRAY
#endif

#ifndef LISTBOX_BKCOLOR2_DEFAULT
  #define LISTBOX_BKCOLOR2_DEFAULT GUI_WHITE
#endif

#ifndef LISTBOX_TEXTCOLOR0_DEFAULT
  #define LISTBOX_TEXTCOLOR0_DEFAULT GUI_BLACK
#endif

#ifndef LISTBOX_TEXTCOLOR1_DEFAULT
  #define LISTBOX_TEXTCOLOR1_DEFAULT GUI_BLACK
#endif

#ifndef LISTBOX_TEXTCOLOR2_DEFAULT
  #define LISTBOX_TEXTCOLOR2_DEFAULT GUI_BLACK
#endif


/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/

typedef struct {
  WIDGET Widget;
  I16 Sel;                   /* current selection */
  WM_SCROLL_STATE ScrollState;
  const GUI_ConstString* ppText;
  const GUI_FONT* pFont;
  GUI_COLOR aBackColor[3];
  GUI_COLOR aTextColor[3];
  #if GUI_DEBUG_LEVEL >1
    int DebugId;
  #endif  
} LISTBOX_Obj;


/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static const GUI_FONT* _pDefaultFont = LISTBOX_FONT_DEFAULT;

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/

#define LISTBOX_H2P(h) (LISTBOX_Obj*) WM_HMEM2Ptr(h)

#if GUI_DEBUG_LEVEL >1
  #define OBJECT_ID 0x4C69   /* Magic numer, should be unique if possible */
  #define ASSERT_IS_VALID_PTR(p) GUI_DEBUG_ERROROUT_IF(p->DebugId != OBJECT_ID, "EDIT.C: Wrong handle type or Object not init'ed")
  #define INIT_ID(p)   p->DebugId = OBJECT_ID
  #define DEINIT_ID(p) p->DebugId = 0
#else
  #define ASSERT_IS_VALID_PTR(p)
  #define INIT_ID(p)
  #define DEINIT_ID(p)
#endif

/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/


/*********************************************************************
*
*       _GetNumVisItems

  Returns:
    Number of fully or partially visible items
*/
static int _GetNumVisItems(LISTBOX_Obj* pObj) {
  int FontDist = GUI_GetYDistOfFont(pObj->pFont);
  int ysize = WM__GetWindowSizeY(&pObj->Widget.Win);
  ysize -= 2*  pObj->Widget.pEffect->EffectSize;
  if (FontDist)
    return ysize  / FontDist;
  return 1;
}

/*********************************************************************
*
*       _GetNumItems

  Returns:
    Number of fully or partially visible items
*/
static int _GetNumItems(LISTBOX_Obj* pObj) {
  int i;
  const GUI_ConstString* ppText = pObj->ppText;
  if (ppText) {
    for (i=0; *(ppText+i); i++);
	  return i;
  }
  return 0;
}

static void _SetScrollState(WM_HWIN hWin) {
  LISTBOX_Obj* pObj    = LISTBOX_H2P(hWin);
  WIDGET__SetScrollState(hWin, &pObj->ScrollState, NULL);
}

static void _CalcScrollParas(WM_HWIN hWin) {
  LISTBOX_Obj* pObj    = LISTBOX_H2P(hWin);
  pObj->ScrollState.NumItems = _GetNumItems(pObj);
  pObj->ScrollState.PageSize = _GetNumVisItems(pObj);
}


static void _SetScroll(LISTBOX_Handle hObj, LISTBOX_Obj* pObj, int iScroll) {
  pObj->ScrollState.v = iScroll;
  _SetScrollState(hObj);
}

static void _CheckSel(LISTBOX_Handle hObj) {
  int Sel;
  LISTBOX_Obj* pObj = LISTBOX_H2P(hObj);
  Sel = pObj->Sel;
  /* Check if we have to scroll up */
  if (Sel < pObj->ScrollState.v) {
    _SetScroll(hObj, pObj, Sel);
  } else {
  /* Check if we have to scroll down */
    if (Sel > pObj->ScrollState.v + pObj->ScrollState.PageSize -1) {
      _SetScroll(hObj, pObj, Sel - (pObj->ScrollState.PageSize -1));
    }
  }   
}

static int _Tolower(int Key) {
  if ((Key >= 0x41) && (Key <= 0x5a)) {
    Key += 0x20;
  }
  return Key;
}

static void _SelectByKey(LISTBOX_Handle hObj, int Key) {
  int i;
  LISTBOX_Obj* pObj = LISTBOX_H2P(hObj);
  Key = _Tolower(Key);
  for (i = 0; i < _GetNumItems(pObj); i++) {
    char c = _Tolower(*(*(pObj->ppText + i)));
    if (c == Key) {
      LISTBOX_SetSel(hObj, i);
      break;
    }
  }
}

/*********************************************************************
*
*       _Paint
*/
static void _Paint(LISTBOX_Handle hObj) {
  int i;
  int Border;
  GUI_RECT r;
  int FontDistY;
  LISTBOX_Obj* pObj = LISTBOX_H2P(hObj);
  int NumItems = _GetNumItems(pObj);
  const GUI_ConstString* ppText = pObj->ppText;
  Border = pObj->Widget.pEffect->EffectSize;
  GUI_SetFont(pObj->pFont);
  FontDistY = GUI_GetFontDistY();
  if (Border) {
    GUI_SetBkColor(pObj->aBackColor[0]);
    GUI_Clear();
  }
  /* Calculate rect used for painting (subtract border) */
  WM_GetClientRect(&r);
  r.x1 -= Border;
  r.y1 -= Border;
  r.y0 -= Border;
  WM_SetUserClipArea(&r);
  for (i = pObj->ScrollState.v; i < NumItems; i++) {
    int y, ColorIndex;
    y = Border + (i - pObj->ScrollState.v) * FontDistY;
    if (i == pObj->Sel) {
      ColorIndex = (pObj->Widget.State & WIDGET_STATE_FOCUS) ? 2 : 1;
    } else {
      ColorIndex = 0;
    }
    GUI_SetBkColor(pObj->aBackColor[ColorIndex]);
    GUI_SetColor  (pObj->aTextColor[ColorIndex]);
    GUI_ClearRect(Border, y, Border, y + FontDistY -1);
    GUI_DispStringAt(*(ppText+i), Border+1, y);
    GUI_DispCEOL();
  }
  WM_SetUserClipArea(NULL);
  /* Draw the 3D effect (if configured) */
  WIDGET__EFFECT_DrawDown(&pObj->Widget);
}

/*********************************************************************
*
*       _OnTouch
*/
static int _OnTouch(LISTBOX_Handle hObj, LISTBOX_Obj* pObj, WM_MESSAGE*pMsg) {
  int Notification;
  int Sel;
  GUI_TOUCH_tState* pState = (GUI_TOUCH_tState*)pMsg->Data.p;
  int FontDistY = GUI_GetYDistOfFont(pObj->pFont);
  if (pMsg->Data.p) {  /* Something happened in our area (pressed or released) */
    if (pState->Pressed) {
      Sel = pState->y / FontDistY + pObj->ScrollState.v; 
      WM_SetFocus(hObj);
      Notification = WM_NOTIFICATION_CLICKED;
      LISTBOX_SetSel(hObj, Sel);
    } else {
      Notification = WM_NOTIFICATION_RELEASED;
    }
  } else {     /* Mouse moved out */
    Notification = WM_NOTIFICATION_MOVED_OUT;
  }
  WM_NotifyParent(hObj, Notification);
  return 0;                        /* Message handled */
}

/*********************************************************************
*
*       Callback
*/
static void _LISTBOX_Callback (WM_MESSAGE*pMsg) {
  LISTBOX_Handle hObj = pMsg->hWin;
  LISTBOX_Obj* pObj = LISTBOX_H2P(hObj);
  WM_SCROLL_STATE ScrollState;
  /* Let widget handle the standard messages */
  if (WIDGET_HandleActive(hObj, pMsg) == 0) {
    return;
  }
  switch (pMsg->MsgId) {
  case WM_NOTIFY_PARENT:
    if (pMsg->Data.v == WM_NOTIFICATION_VALUE_CHANGED) {
      WM_GetScrollState(pMsg->hWinSrc, &ScrollState);
    }
    pObj->ScrollState.v = ScrollState.v;
    WM_InvalidateWindow(hObj);
    break;
  case WM_ADD_SCROLLBAR:
    _SetScrollState(hObj);
    break;
  case WM_PAINT:
    _Paint(hObj);
    break;
  case WM_TOUCH:
    if (_OnTouch(hObj, pObj, pMsg) == 0)
      return;
    break;
  case WM_KEY:
    if ( ((WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt >0) {
      int Key = ((WM_KEY_INFO*)(pMsg->Data.p))->Key;
      switch (Key) {
        case GUI_KEY_TAB:
          break;                    /* Send to parent by not doing anything */
        default:
          LISTBOX_AddKey(hObj, Key);
          return;
      }
    }
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

LISTBOX_Handle LISTBOX_CreateAsChild(
  const GUI_ConstString* ppText,
  WM_HWIN hWinParent,
  int x0, int y0, int xsize, int ysize, int Flags)
{
  LISTBOX_Handle hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, 
                                               hWinParent, Flags, _LISTBOX_Callback,
                                               sizeof(LISTBOX_Obj)-sizeof(WM_Obj));
  if (hObj) {
    LISTBOX_Obj* pObj   = LISTBOX_H2P(hObj);
    /* init widget specific variables */
    WIDGET__Init(&pObj->Widget, WIDGET_STATE_FOCUSSABLE | WIDGET_STATE_ENABLED);
    /* pObj->ppText = 0; */   /* Zero init not required */
    pObj->pFont  = _pDefaultFont;
    pObj->aBackColor[0] = 0xffffff;            /* Non selected state */
    pObj->aBackColor[1] = LISTBOX_BKCOLOR1_DEFAULT;    /* selected state */
    pObj->aBackColor[2] = GUI_BLUE;            /* selected state with focus */
    pObj->aTextColor[0] = 0x000000;            /* Non selected state */
    pObj->aTextColor[1] = 0xffffff;            /* selected state */
    pObj->aTextColor[2] = 0xffffff;            /* selected state with focus */
    if (hObj && ppText) {
      LISTBOX_Obj* pObj   = LISTBOX_H2P(hObj);
      INIT_ID(pObj);
      /* init member variables */
      /* Check size */
      if (!xsize) {
        const GUI_FONT* pFontOld = GUI_SetFont(pObj->pFont);
        int i;
		    for (i=0; *(ppText+i); i++) {
          int Size = GUI_GetStringDistX(*(ppText+i));
          if (Size>xsize)
			      xsize = Size;
		    }
        GUI_SetFont(pFontOld);
	    }
      /* Set non-zero attributes */
      pObj->ppText = ppText;
    }
    _CalcScrollParas(hObj);
  }
  return hObj;
}

LISTBOX_Handle LISTBOX_Create(
                    const GUI_ConstString* ppText,
                    int x0, int y0, int xsize, int ysize, int Flags)
{
   return LISTBOX_CreateAsChild(ppText, WM_HWIN_NULL /*hWin*/, x0, y0, xsize, ysize, Flags);
}

LISTBOX_Handle LISTBOX_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb) {
  LISTBOX_Handle  hThis;
  GUI_USE_PARA(cb);
  hThis = LISTBOX_CreateAsChild(0,
                                hWinParent,
                                pCreateInfo->x0 + x0, 
                                pCreateInfo->y0 + y0, 
                                pCreateInfo->xSize, 
                                pCreateInfo->ySize, 
                                pCreateInfo->Flags);
  if (hThis) {
    LISTBOX_Obj* pObj = LISTBOX_H2P(hThis);
    INIT_ID(pObj);
    pObj->Widget.Id     = pCreateInfo->Id;
    pObj->Widget.State  = LISTBOX_STATE_INACTIVE;
  }
  return hThis;
}

/*********************************************************************
*
*       Exported routines:  Various methods
*
**********************************************************************
*/

void LISTBOX_AddKey(LISTBOX_Handle hObj, int Key) {
  if (hObj) {
    WM_LOCK();
    switch (Key) {
      case GUI_KEY_DOWN:
        LISTBOX_IncSel(hObj);
        break;
      case GUI_KEY_UP:
        LISTBOX_DecSel(hObj);
        break;
      default:
        _SelectByKey(hObj, Key);
        break;
    }
    WM_UNLOCK();
  }
}
void LISTBOX_SetText(LISTBOX_Handle hObj, const GUI_ConstString* ppText) {
  LISTBOX_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = LISTBOX_H2P(hObj);
    ASSERT_IS_VALID_PTR(pObj);
    pObj->ppText = ppText;
    _CalcScrollParas(hObj);
    LISTBOX_Invalidate(hObj);
    WM_UNLOCK();
  }
}

void LISTBOX_SetFont(LISTBOX_Handle hObj, const GUI_FONT* pfont) {
  LISTBOX_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = LISTBOX_H2P(hObj);
    ASSERT_IS_VALID_PTR(pObj);
    pObj->pFont = pfont;
    _CalcScrollParas(hObj);
    LISTBOX_Invalidate(hObj);
    WM_UNLOCK();
  }
}

void LISTBOX_SetBackColor(LISTBOX_Handle hObj, int index, GUI_COLOR color) {
  LISTBOX_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = LISTBOX_H2P(hObj);
    ASSERT_IS_VALID_PTR(pObj);
    pObj->aBackColor[index] = color;
    LISTBOX_Invalidate(hObj);
    WM_UNLOCK();
  }
}

void LISTBOX_SetTextColor(LISTBOX_Handle hObj, int index, GUI_COLOR color) {
  LISTBOX_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = LISTBOX_H2P(hObj);
    ASSERT_IS_VALID_PTR(pObj);
    pObj->aTextColor[index] = color;
    LISTBOX_Invalidate(hObj);
    WM_UNLOCK();
  }
}

void LISTBOX_SetSel (LISTBOX_Handle hObj, int Sel) {
  int NumItems, MaxSel;
  LISTBOX_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = LISTBOX_H2P(hObj);
    ASSERT_IS_VALID_PTR(pObj);
    NumItems = _GetNumItems(pObj);
    MaxSel = NumItems ? NumItems-1 : 0;
    if (Sel>MaxSel) {
      Sel = MaxSel;
    }
    if (Sel != pObj->Sel) {
      pObj->Sel = Sel;
      LISTBOX_Invalidate(hObj);
      WM_NotifyParent(hObj, WM_NOTIFICATION_SEL_CHANGED);
    }
    _CheckSel(hObj);
    WM_UNLOCK();
  }
}

void LISTBOX_IncSel      (LISTBOX_Handle hObj) {
  LISTBOX_Obj* pObj = LISTBOX_H2P(hObj);
  int Sel = LISTBOX_GetSel(hObj);
  ASSERT_IS_VALID_PTR(pObj);
  LISTBOX_SetSel(hObj, Sel+1);
}

void LISTBOX_DecSel      (LISTBOX_Handle hObj) {
  int Sel = LISTBOX_GetSel(hObj);
  if (Sel)
	  Sel--;
  LISTBOX_SetSel(hObj, Sel);
}

int  LISTBOX_GetSel (LISTBOX_Handle hObj) {
  int r = 0;
  LISTBOX_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = LISTBOX_H2P(hObj);
    ASSERT_IS_VALID_PTR(pObj);
    r = pObj->Sel;
    WM_UNLOCK();
  }
  return r;
}

void LISTBOX_SetDefaultFont(const GUI_FONT* pFont) {
  _pDefaultFont = pFont;
}

const GUI_FONT* LISTBOX_GetDefaultFont(void) {
  return _pDefaultFont;
}

#else                            /* Avoid problems with empty object modules */
  void LISTBOX_C(void) {}
#endif
