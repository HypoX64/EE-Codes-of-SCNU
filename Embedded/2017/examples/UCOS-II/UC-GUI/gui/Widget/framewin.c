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
File        : FRAMEWIN.c
Purpose     : Framewindow for emWin GSC
---------------------------END-OF-HEADER------------------------------
*/


#include <stdlib.h>
#include <string.h>
#include "FRAMEWIN.h"
#include "WIDGET.h"
#include "GUI_Protected.h"
#if GUI_WINSUPPORT

/*
  *****************************************************************
  *                                                               *
  *              Config defaults                                  *
  *                                                               *
  *****************************************************************
*/
/* Support for 3D effects */
#ifndef FRAMEWIN_USE_3D
  #define FRAMEWIN_USE_3D 1
#endif

#ifndef FRAMEWIN_CLIENTCOLOR_DEFAULT
  #define FRAMEWIN_CLIENTCOLOR_DEFAULT 0xc0c0c0
#endif

/* Default for top frame size */
#ifndef FRAMEWIN_CAPTIONSIZE_DEFAULT
  #define FRAMEWIN_CAPTIONSIZE_DEFAULT 12
#endif

/* Default for left/right/top/bottom frame size */
#ifndef FRAMEWIN_BORDER_DEFAULT
  #define FRAMEWIN_BORDER_DEFAULT 3
#endif

/* Default for inner frame size */
#ifndef FRAMEWIN_IBORDER_DEFAULT
  #define FRAMEWIN_IBORDER_DEFAULT 1
#endif

#ifndef FRAMEWIN_DEFAULT_FONT
  #define FRAMEWIN_DEFAULT_FONT &GUI_Font8_1
#endif

#ifndef FRAMEWIN_BARCOLOR_ACTIVE_DEFAULT
  #define FRAMEWIN_BARCOLOR_ACTIVE_DEFAULT 0xff0000
#endif

#ifndef FRAMEWIN_BARCOLOR_INACTIVE_DEFAULT
  #define FRAMEWIN_BARCOLOR_INACTIVE_DEFAULT 0x404040
#endif

#ifndef FRAMEWIN_FRAMECOLOR_DEFAULT
  #define FRAMEWIN_FRAMECOLOR_DEFAULT 0xaaaaaa
#endif



/************************************************************
*
*                 Object definition
*
*************************************************************
*/

typedef struct {
  WIDGET Widget;
  GUI_COLOR BarColor[2];
  GUI_COLOR TextColor;
  WM_CALLBACK* cb;
  WM_HWIN hClient;
  GUI_POINT CapturePoint;
  const GUI_FONT* pFont;
  GUI_RECT rClient;
  GUI_COLOR ClientColor;
  const char* pText;
  I16 XOff, YOff;
  I16 FrameSize;
  I16 TitleHeight;
  I16 TextAlign;
  U16 Flags;
  WM_HWIN hFocussedChild;          /* Handle to focussed child .. default none (0) */
//  char HasFocus;
} FRAMEWIN_Obj;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static const GUI_FONT* _pDefaultFont = FRAMEWIN_DEFAULT_FONT;
static   GUI_COLOR _aBarColor[2] = {
  FRAMEWIN_BARCOLOR_INACTIVE_DEFAULT,
  FRAMEWIN_BARCOLOR_ACTIVE_DEFAULT
};
static GUI_COLOR _DefaultClientColor = FRAMEWIN_CLIENTCOLOR_DEFAULT;
static int _DefaultCaptionSize       = FRAMEWIN_CAPTIONSIZE_DEFAULT;
static int _DefaultBorderSize        = FRAMEWIN_BORDER_DEFAULT;

/*
  ********************************************************************
  *                                                                  *
  *                 Macros for internal use                          *
  *                                                                  *
  ********************************************************************
*/

#define FRAMEWIN_H2P(h) (FRAMEWIN_Obj*) WM_HMEM2Ptr(h)

/*
********************************************************************
*                                                                  *
*                    Static routines                               *
*                                                                  *
********************************************************************
*/




static void _OnTouch(FRAMEWIN_Handle hWin, FRAMEWIN_Obj* pObj, WM_MESSAGE* pMsg) {
  GUI_TOUCH_tState* pState;
  pState = (GUI_TOUCH_tState*)pMsg->Data.p;
  if (pMsg->Data.p) {  /* Something happened in our area (pressed or released) */
    if (pState->Pressed) {
      WM_SetFocus(hWin);
      WM_BringToTop(hWin);
      if (pObj->Flags & FRAMEWIN_SF_MOVEABLE) {
        if (!WM_HasCaptured(hWin)) {
          WM_SetCapture(hWin, 1);
          pObj->CapturePoint.x = pState->x;
          pObj->CapturePoint.y = pState->y;
        } else {
          int dx, dy;
          dx = pState->x - pObj->CapturePoint.x;
          dy = pState->y - pObj->CapturePoint.y;
          WM_MoveWindow(hWin, dx, dy);
        }
      }
    }
  }
}

static void _Paint(FRAMEWIN_Obj* pObj) {
  WM_HWIN hWin = WM_GetActiveWindow();
  int xsize = WM_GetWindowSizeX(hWin);
  int ysize = WM_GetWindowSizeY(hWin);
  int FrameSize = pObj->FrameSize;
  GUI_RECT rClient; GUI_GetClientRect(&rClient);
  GUI_SetFont(pObj->pFont);
/* Draw Title */
  GUI_SetBkColor((pObj->Widget.State & WIDGET_STATE_CHILD_HAS_FOCUS) ? pObj->BarColor[1] : pObj->BarColor[0]);
  GUI_SetColor  (pObj->TextColor);
  GUI_SetTextAlign(pObj->TextAlign);
	GUI_ClearRect(FrameSize,FrameSize, xsize-1-FrameSize, FrameSize+pObj->rClient.y0-1);
  GUI_DispStringAt( pObj->pText,
                   FrameSize+pObj->XOff,
                   FrameSize+pObj->YOff);
/* Draw Frame */
  GUI_SetColor  (FRAMEWIN_FRAMECOLOR_DEFAULT);  /* pObj->BarColor[1]*/
  GUI_FillRect  (0, 0, xsize-1, FrameSize-1);
	GUI_FillRect  (0, 0, pObj->rClient.x0-1, ysize-1);
	GUI_FillRect  (pObj->rClient.x1+1, 0, xsize-1, ysize-1);
  GUI_FillRect  (0, pObj->rClient.y1+1, xsize-1, ysize-1);
  GUI_FillRect  (0, pObj->TitleHeight+FrameSize,
                    xsize-1, pObj->TitleHeight+2*FrameSize-1);
/* Draw Client area */
  WM_SetUserClipArea(&pObj->rClient);
  /*GUI_SetBkColor(pObj->ClientColor);
  GUI_Clear();*/
  WM_SetUserClipArea(NULL);
/* Draw the 3D effect (if configured) */
  #if FRAMEWIN_USE_3D
    WIDGET_EFFECT_3D_DrawUp();
  #endif
  
}


static void CalcPositions( FRAMEWIN_Handle hObj) {
  if (hObj) {
    FRAMEWIN_Obj * pObj = FRAMEWIN_H2P(hObj);
    int TitleHeight;
    int FontSize = GUI_GetYSizeOfFont(pObj->pFont);
    int xsize = WM_GetWindowSizeX(hObj);
    int ysize = WM_GetWindowSizeY(hObj);
    TitleHeight = _DefaultCaptionSize;
    /* Make sure defaults are o.k. for us */
    if (FontSize + 2 >= TitleHeight)
      TitleHeight = FontSize + 2;
    /* Set object properties accordingly */
    pObj->rClient.x0  =         _DefaultBorderSize;
    pObj->rClient.x1  = xsize - _DefaultBorderSize - 1;
    pObj->rClient.y0  =         _DefaultBorderSize + FRAMEWIN_IBORDER_DEFAULT + TitleHeight;
    pObj->rClient.y1  = ysize - _DefaultBorderSize - 1;
    pObj->FrameSize   =         _DefaultBorderSize;
    pObj->TitleHeight = TitleHeight;
    if (pObj->hClient) {
      WM_MoveTo (pObj->hClient, 
                 pObj->rClient.x0 + pObj->Widget.Win.Rect.x0, 
                 pObj->rClient.y0 + pObj->Widget.Win.Rect.y0);
      WM_SetSize(pObj->hClient, 
                 pObj->rClient.x1 - pObj->rClient.x0 + 1, 
                 pObj->rClient.y1 - pObj->rClient.y0 + 1);
    }
  }  
}

/*********************************************************************
*
*       Framewin Callback
*/
static void _FRAMEWIN_Callback (WM_MESSAGE *pMsg) {
  FRAMEWIN_Handle hWin = (FRAMEWIN_Handle)(pMsg->hWin);
  FRAMEWIN_Obj* pObj = FRAMEWIN_H2P(hWin);
  GUI_RECT* pRect = (GUI_RECT*)(pMsg->Data.p);
  switch (pMsg->MsgId) {
  case WM_PAINT:
    _Paint(pObj);
    break;
  case WM_TOUCH:
    _OnTouch(hWin, pObj, pMsg);
    return;                       /* Return here ... Message handled */
  case WM_GETCLIENTRECT:
		*pRect = pObj->rClient;
    return;                       /* Return here ... Message handled */
  case WM_GETCLIENTRECT_ABS:  /* Do not seperate from WM_GETCLIENTRECT !!! */
	  *pRect = pObj->rClient;
    GUI_MoveRect(pRect, pObj->Widget.Win.Rect.x0, pObj->Widget.Win.Rect.y0);
    return;                       /* Return here ... Message handled */
  case WM_GET_CLIENT_WINDOW:      /* return handle to client window. For most windows, there is no seperate client window, so it is the same handle */
    pMsg->Data.v = pObj->hClient;
    return;                       /* Return here ... Message handled */
  case WM_GET_FOCUSSED_CHILD:
    pMsg->Data.v = pObj->hFocussedChild;
    return;                       /* Return here ... Message handled */
  case WM_SET_FOCUS:
    if (pMsg->Data.v == 1) {
      WM_SetFocus(pObj->hFocussedChild);
    } else {
      WM_SetFocus(0);
    }
    return;
  }
  /* Let widget handle the standard messages */
  if (WIDGET_HandleActive(hWin, pMsg) == 0) {
    return;
  }
  WM_DefaultProc(pMsg);
}

/*********************************************************************
*
*       Client Callback
*/
static void FRAMEWIN__cbClient(WM_MESSAGE* pMsg) {
  WM_HWIN hWin    = pMsg->hWin;
  WM_HWIN hParent = WM_GetParent(pMsg->hWin);
  FRAMEWIN_Obj* pObj = FRAMEWIN_H2P(hParent);
  WM_CALLBACK* cb = pObj->cb;
  switch (pMsg->MsgId) {
    case WM_PAINT:
      GUI_SetBkColor(pObj->ClientColor);
      GUI_Clear();
      if (pObj->cb) {
	      WM_MESSAGE msg;
        msg.hWin   = hWin;
		    msg.MsgId  = WM_PAINT;
        (*pObj->cb)(&msg);
      }
      return;
    case WM_GET_FOCUSSED_CHILD:
      pMsg->Data.v = pObj->hFocussedChild;
      return;
    case WM_SET_FOCUS:
      if (pMsg->Data.v) {      /* Focus received */
        if (pObj->hFocussedChild) {
          WM_SendMessage(pObj->hFocussedChild, pMsg);
        } else {
          pObj->hFocussedChild = WM_SetFocusOnNextChild(hWin);
        }
      }
      return;
    case WM_KEY:
      if ( ((WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt >0) {
        int Key = ((WM_KEY_INFO*)(pMsg->Data.p))->Key;
        switch (Key) {
          case GUI_KEY_TAB:
            pObj->hFocussedChild = WM_SetFocusOnNextChild(hWin);
            break;                    /* Send to parent by not doing anything */
        }
      }
      break;
    case WM_NOTIFY_CHILD_HAS_FOCUS:
      pObj->hFocussedChild = pMsg->hWinSrc;
      if (pMsg->Data.v) {
        pObj->Widget.State |= WIDGET_STATE_CHILD_HAS_FOCUS;
      } else {
        pObj->Widget.State &= ~WIDGET_STATE_CHILD_HAS_FOCUS;
      }
      WM_InvalidateWindow(hParent);
      break;
    case WM_GET_BKCOLOR:
      pMsg->Data.Color = pObj->ClientColor;
      return;                       /* Message handled */
    case WM_GETCLIENTRECT_ABS:      /* return client window in absolute (screen) coordinates */
    case WM_GET_CLIENT_WINDOW:      /* return handle to client window. For most windows, there is no seperate client window, so it is the same handle */
      WM_DefaultProc(pMsg);
      return;                       /* We are done ! */
  }
  if (cb) {
    pMsg->hWin = hParent;
    (*cb)(pMsg);
  }
}

/*********************************************************************
*
*        Exported routines:  Create
*
**********************************************************************
*/

FRAMEWIN_Handle FRAMEWIN_CreateAsChild( 
                                    int x0, int y0, int xsize, int ysize, WM_HWIN hParent,
                                    const char* pText, WM_CALLBACK* cb, int Flags)
{
  FRAMEWIN_Handle hObj;
  /* Create the window */
  GUI_LOCK();
  hObj = WM_CreateWindowAsChild(x0, y0, xsize/*+2*HBorder*/, ysize/*+TBorder+BBorder*/, hParent,
                        Flags, _FRAMEWIN_Callback, sizeof(FRAMEWIN_Obj) - sizeof(WM_Obj));
  if (hObj) {
    FRAMEWIN_Obj* pObj = FRAMEWIN_H2P(hObj);
    /* init widget specific variables */
    WIDGET__Init(&pObj->Widget, WIDGET_STATE_FOCUSSABLE | WIDGET_STATE_ENABLED);
    /* init member variables */
    pObj->pFont = _pDefaultFont;
    memcpy(pObj->BarColor, _aBarColor, sizeof(pObj->BarColor));
    pObj->TextColor    = 0xffffff;
    pObj->TextAlign    = GUI_TA_LEFT;
    pObj->ClientColor  = _DefaultClientColor;
    pObj->pText        = pText;
    pObj->XOff = 1;
    pObj->YOff = 1;
    pObj->cb = cb;
    CalcPositions(hObj);
    pObj->hClient = WM_CreateWindowAsChild(0, 0, 0, 0, hObj, WM_CF_SHOW, FRAMEWIN__cbClient, 0);
  }
  GUI_UNLOCK();
  return hObj;
}

FRAMEWIN_Handle FRAMEWIN_Create( const char* pText,
                                    WM_CALLBACK* cb,
                                    int Flags,
                                    int x0, int y0, int xsize, int ysize) {

  return FRAMEWIN_CreateAsChild(x0, y0, xsize, ysize, WM_HWIN_NULL, pText, cb, Flags);
}


FRAMEWIN_Handle FRAMEWIN_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* pCallback) {
  FRAMEWIN_Handle hObj;
  hObj = FRAMEWIN_CreateAsChild(
    pCreateInfo->x0 + x0, pCreateInfo->y0 + y0, pCreateInfo->xSize, pCreateInfo->ySize, hWinParent,
    pCreateInfo->pName, pCallback, 0);
  if (hObj) {
    FRAMEWIN_Obj* pObj = FRAMEWIN_H2P(hObj);
    pObj->Flags = pCreateInfo->Flags;
  }
  return hObj;
}

/*********************************************************************
*
*        Exported routines:  Various methods
*
**********************************************************************
*/
void FRAMEWIN_SetFont(FRAMEWIN_Handle hObj, const GUI_FONT* pFont) {
  GUI_LOCK();
  if (hObj) {
    FRAMEWIN_Obj* pObj = FRAMEWIN_H2P(hObj);
    pObj->pFont = pFont;
    CalcPositions(hObj);
    FRAMEWIN_Invalidate(hObj);
  }
  GUI_UNLOCK();
}

void FRAMEWIN_SetBarColor(FRAMEWIN_Handle hObj, int index, GUI_COLOR color) {
  GUI_LOCK();
  if (hObj) {
    FRAMEWIN_Obj* pObj = FRAMEWIN_H2P(hObj);
    pObj->BarColor[index] = color;
    FRAMEWIN_Invalidate(hObj);
  }
  GUI_UNLOCK();
}

void FRAMEWIN_SetTextColor(FRAMEWIN_Handle hObj, GUI_COLOR color) {
  GUI_LOCK();
  if (hObj) {
    FRAMEWIN_Obj* pObj = FRAMEWIN_H2P(hObj);
    pObj->TextColor = color;
    FRAMEWIN_Invalidate(hObj);
  }
  GUI_UNLOCK();
}

void FRAMEWIN_SetText(FRAMEWIN_Handle hObj, const char* s) {
  char NeedsInvalidate;
  GUI_LOCK();
  if (hObj) {
    FRAMEWIN_Obj* pObj = FRAMEWIN_H2P(hObj);
    NeedsInvalidate = 1;
    if (s && pObj->pText) {
      if (strcmp(s, pObj->pText) == 0) {
        NeedsInvalidate = 0;
      }
    }
    pObj->pText = s;
    if (NeedsInvalidate) {
      FRAMEWIN_Invalidate(hObj);
    }
  }
  GUI_UNLOCK();
}

void FRAMEWIN_SetTextAlign(FRAMEWIN_Handle hObj, int Align) {
  GUI_LOCK();
  if (hObj) {
    FRAMEWIN_Obj* pObj = FRAMEWIN_H2P(hObj);
    pObj->TextAlign = Align;
    switch (Align) {
    case GUI_TA_HCENTER:
      pObj->XOff = (pObj->rClient.x1 - pObj->rClient.x0) / 2;
      break;
    case GUI_TA_LEFT:
      pObj->XOff = pObj->FrameSize;
      break;
    case GUI_TA_RIGHT:
      pObj->XOff = pObj->rClient.x1 - pObj->FrameSize;
      break;
    }
    FRAMEWIN_Invalidate(hObj);
  }
  GUI_UNLOCK();
}

void FRAMEWIN_SetTextPos(FRAMEWIN_Handle hObj, int XOff, int YOff) {
  GUI_LOCK();
  if (hObj) {
    FRAMEWIN_Obj* pObj = FRAMEWIN_H2P(hObj);
    pObj->XOff = XOff;
    pObj->YOff = YOff;
    FRAMEWIN_Invalidate(hObj);
  }
  GUI_UNLOCK();
}

void FRAMEWIN_SetActive(FRAMEWIN_Handle hObj, int State) {
  GUI_LOCK();
  if (hObj) {
    if (State) {
      FRAMEWIN_SetBarColor(hObj, 0, FRAMEWIN_BARCOLOR_ACTIVE_DEFAULT);
    } else {
      FRAMEWIN_SetBarColor(hObj, 0, FRAMEWIN_BARCOLOR_INACTIVE_DEFAULT);
    }
  }
  GUI_UNLOCK();
}

void FRAMEWIN_SetClientColor(FRAMEWIN_Handle hObj, GUI_COLOR Color) {
  GUI_LOCK();
  if (hObj) {
    FRAMEWIN_Obj* pObj = FRAMEWIN_H2P(hObj);
    pObj->ClientColor = Color;
    FRAMEWIN_Invalidate(hObj);
  }
  GUI_UNLOCK();
}

  /***************************************************************
  *
  *                Set/Get defaults
  *
  ***************************************************************/

void FRAMEWIN_SetDefaultFont(const GUI_FONT* pFont) {
  _pDefaultFont = pFont;
}

const GUI_FONT* FRAMEWIN_GetDefaultFont(void) {
  return _pDefaultFont;
}

void FRAMEWIN_SetDefaultBarColor(int Index, GUI_COLOR Color) {
  if ((Index >= 0) && (Index <= 1)) {
    _aBarColor[Index] = Color;
  }
}

GUI_COLOR FRAMEWIN_GetDefaultBarColor(int Index) {
  GUI_COLOR r = 0;
  if ((Index >= 0) && (Index <= 1)) {
    r = _aBarColor[Index];
  }
  return r;
}

void FRAMEWIN_SetDefaultClientColor(GUI_COLOR Color) {
  _DefaultClientColor = Color;
}

GUI_COLOR FRAMEWIN_GetDefaultClientColor(void) {
  return _DefaultClientColor;
}

int FRAMEWIN_GetDefaultCaptionSize(void) {
  return _DefaultCaptionSize;
}

void FRAMEWIN_SetDefaultCaptionSize(int DefaultCaptionSize) {
  _DefaultCaptionSize = DefaultCaptionSize;
}

int FRAMEWIN_GetDefaultBorderSize(void) {
  return _DefaultBorderSize;
}

void FRAMEWIN_SetDefaultBorderSize(int DefaultBorderSize) {
  _DefaultBorderSize = DefaultBorderSize;
}

#else
  void WIDGET_FrameWin(void) {} /* avoid empty object files */
#endif /* GUI_WINSUPPORT */
