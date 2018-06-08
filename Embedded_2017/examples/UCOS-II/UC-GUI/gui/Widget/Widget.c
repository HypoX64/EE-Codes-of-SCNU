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
File        : BUTTON.c
Purpose     : emWin GSC button widget
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>

#include "WIDGET.h"
#include "GUIDebug.h"
#include "GUI.h"
#include "GUI_Protected.h"
#include "WM_Intern.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/


/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

const WIDGET_EFFECT* _pEffectDefault = &WIDGET_Effect_3D;

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/

#define WIDGET_H2P(hWin)        ((WIDGET*)WM_HMEM2Ptr(hWin))

/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/
static void _RotateRect90(WIDGET* pWidget, GUI_RECT* pDest, const GUI_RECT* pRect) {
  int XSize;
  XSize = pWidget->Win.Rect.x1 - pWidget->Win.Rect.x0;
  pDest->x0 = XSize - pRect->y1;
  pDest->x1 = XSize - pRect->y0;
  pDest->y0 = pRect->x0;
  pDest->y1 = pRect->x1;

}


/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/

/*********************************************************************
*
*       WIDGET__GetClientRect

  Returns the logical client rectangle, which means the normal
  client rectangle for widgets with their standard orientation
  and the rotated one for rotated widgets.
*/
void WIDGET__GetClientRect(WIDGET* pWidget, GUI_RECT* pRect) {
  if (pWidget->State & WIDGET_STATE_VERTICAL) {
    GUI_RECT Rect;
    WM_GetClientRect(&Rect);
    pRect->x0 = Rect.y0;
    pRect->x1 = Rect.y1;
    pRect->y0 = Rect.x0;
    pRect->y1 = Rect.x1;
  } else {
    WM_GetClientRect(pRect);
  }
}

GUI_COLOR WIDGET__GetBkColor(WM_HWIN hObj) {
  GUI_COLOR BkColor = WM_GetBkColor(WM_GetParent(hObj));
  if (BkColor == GUI_INVALID_COLOR) {
    BkColor = DIALOG_GetBkColor();
  }
  return BkColor;
}

/*********************************************************************
*
*       WIDGET__GetInsideRect
*/
void WIDGET__GetInsideRect(WIDGET* pWidget, GUI_RECT* pRect) {
  WM__GetClientRectWin(&pWidget->Win, pRect);
  GUI__ReduceRect(pRect, pRect, pWidget->pEffect->EffectSize);
}


int WIDGET__GetXSize(const WIDGET* pWidget) {
  int r;
  if (pWidget->State & WIDGET_STATE_VERTICAL) {
    r = pWidget->Win.Rect.y1 - pWidget->Win.Rect.y0;
  } else {
    r = pWidget->Win.Rect.x1 - pWidget->Win.Rect.x0;
  }
  return r + 1;
}

int WIDGET__GetYSize(const WIDGET* pWidget) {
  int r;
  if (pWidget->State & WIDGET_STATE_VERTICAL) {
    r = pWidget->Win.Rect.x1 - pWidget->Win.Rect.x0;
  } else {
    r = pWidget->Win.Rect.y1 - pWidget->Win.Rect.y0;
  }
  return r + 1;
}

/*******************************************************************
*
*       WIDGET__GetWindowSizeX

  Return width (or height in case of rotation) of window in pixels
*/
int WIDGET__GetWindowSizeX(WM_HWIN hWin) {
  WIDGET* pWidget = WIDGET_H2P(hWin);
  if (pWidget->State & WIDGET_STATE_VERTICAL) {
    return WM_GetWindowSizeY(hWin);
  } else {
    return WM_GetWindowSizeX(hWin);
  }
}


/*********************************************************************
*
*       WIDGET_SetState
*/
void WIDGET_SetState(WM_HWIN hObj, int State) {
  WIDGET* pWidget = WIDGET_H2P(hObj);
  if (State != pWidget->State) {
    pWidget->State = State;
    WM_Invalidate(hObj);
  }
}

/*********************************************************************
*
*       WIDGET__IsEnabled

  Returns:
    1 if Widget is enabled
    0 else
*/
int WIDGET__IsEnabled(WIDGET* pWidget) {
  return pWidget->State & WIDGET_STATE_ENABLED ? 1 : 0;
}

/*********************************************************************
*
*       WIDGET_OrState
*/
void WIDGET_OrState(WM_HWIN hObj, int State) {
  WIDGET* pWidget = WIDGET_H2P(hObj);
  if (State != (pWidget->State & State)) {
    pWidget->State |= State;
    WM_Invalidate(hObj);
  }
}

/*********************************************************************
*
*       WIDGET_AndState

  Purpose:
    Clear flags in the State element of the widget.
    The bits to be cleared are set.
  Example:
    ...(..., 3);   // Clears bit 0, 1 int the state member 

*/
void WIDGET_AndState(WM_HWIN hObj, int Mask) {
  U16 StateNew;
  WIDGET* pWidget = WIDGET_H2P(hObj);
  StateNew = pWidget->State & (~Mask);
  if (pWidget->State != StateNew) {
    pWidget->State = StateNew;
    WM_Invalidate(hObj);
  }
}

/*********************************************************************
*
*       WIDGET_SetInactive
*/
void WIDGET_Disable(WM_HWIN hObj) {
  WIDGET* pWidget;
  if (hObj) {
    WM_LOCK();
    pWidget = WIDGET_H2P(hObj);
    if (pWidget->State & WIDGET_STATE_ENABLED) {
      pWidget->State &= ~WIDGET_STATE_ENABLED;
      WM_Invalidate(hObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       WIDGET_Enable
*/
void WIDGET_Enable(WM_HWIN hObj) {
  WIDGET* pWidget;
  if (hObj) {
    WM_LOCK();
    pWidget = WIDGET_H2P(hObj);
    if ((pWidget->State & WIDGET_STATE_ENABLED) == 0) {
      pWidget->State |= WIDGET_STATE_ENABLED;
      WM_Invalidate(hObj);
    }
    WM_UNLOCK();
  }
}


void WIDGET__Init(WIDGET* pWidget, U16 State) {
  pWidget->pEffect       = _pEffectDefault;
  pWidget->State         = State;
}


/*********************************************************************
*
*       WIDGET_HandleActive
*/
int WIDGET_HandleActive(WM_HWIN hObj, WM_MESSAGE* pMsg) {
  WM_MESSAGE Msg;
  WIDGET* pWidget = WIDGET_H2P(hObj);
  switch (pMsg->MsgId) {
    case WM_GET_ID:
      pMsg->Data.v = pWidget->Id;
      return 0;                        /* Message handled -> Return */
    case WM_SET_FOCUS:
      if (pMsg->Data.v == 1) {
        WIDGET_SetState(hObj, pWidget->State |  WIDGET_STATE_FOCUS);

      } else {
        WIDGET_SetState(hObj, pWidget->State & ~WIDGET_STATE_FOCUS);
      }
      Msg.MsgId = WM_NOTIFY_CHILD_HAS_FOCUS;
      Msg.Data.v = pMsg->Data.v;
      WM_SendToParent(hObj, &Msg);
      return 0;
    case WM_GET_HAS_FOCUS:
      pMsg->Data.v = pWidget->State & WIDGET_STATE_FOCUS;
      return 0;                         /* Message handled */
    case WM_SET_ENABLE:
      if (pMsg->Data.v) {
        WIDGET_OrState(hObj, WIDGET_STATE_ENABLED);
      } else {
        WIDGET_AndState(hObj, WIDGET_STATE_ENABLED);
      }
    case WM_GET_ACCEPT_FOCUS:
      pMsg->Data.v = (pWidget->State & WIDGET_STATE_FOCUSSABLE) ? 1 : 0;               /* Can handle focus */
      return 0;                         /* Message handled */
     case WM_GET_INSIDE_RECT:
      WIDGET__GetInsideRect(pWidget, (GUI_RECT*)pMsg->Data.p);
      return 0;                         /* Message handled */

  }
  return 1;                           /* Message NOT handled */
}



void WIDGET__SetScrollState(WM_HWIN hWin, const WM_SCROLL_STATE* pVState, const WM_SCROLL_STATE* pHState) {
  WM_HWIN hScroll;
  /* vertical scrollbar */
  hScroll = WM_GetDialogItem(hWin, GUI_ID_VSCROLL);
    WM_SetScrollState(hScroll, pVState);
  /* horizontal scrollbar */
  hScroll = WM_GetDialogItem(hWin, GUI_ID_HSCROLL);
    WM_SetScrollState(hScroll, pHState);
}



void WIDGET__DrawFocusRect(WIDGET* pWidget, const GUI_RECT* pRect, int Dist) {
  GUI_RECT Rect;
  if (pWidget->State & WIDGET_STATE_VERTICAL) {
    _RotateRect90(pWidget, &Rect, pRect);
    pRect = &Rect;
  }
  GUI_DrawFocusRect(pRect, Dist);
}

void WIDGET__DrawVLine(WIDGET* pWidget, int x, int y0, int y1) {
  if (pWidget->State & WIDGET_STATE_VERTICAL) {
    GUI_RECT r0, r1;
    r0.x0 = x;
    r0.x1 = x;
    r0.y0 = y0;
    r0.y1 = y1;
    _RotateRect90(pWidget, &r1, &r0);
    GUI_DrawHLine(r1.y0, r1.x0, r1.x1);
  } else {
    GUI_DrawVLine(x, y0, y1);
  }
}


/*********************************************************************
*
*       WIDGET_FillRectEx
*/
void WIDGET__FillRectEx(WIDGET* pWidget, const GUI_RECT* pRect) {
  if (pWidget->State & WIDGET_STATE_VERTICAL) {
    GUI_RECT r;
    _RotateRect90(pWidget, &r, pRect);
    pRect = &r;
  }
  GUI_FillRectEx(pRect);
}




/*********************************************************************
*
*       WIDGET__EFFECT_ ...
*/

void WIDGET__EFFECT_DrawDownRect(WIDGET* pWidget, GUI_RECT* pRect) {
  GUI_RECT Rect;
  if (pRect == NULL) {
    WM_GetClientRect(&Rect);
    pRect = &Rect;
  }
  if (pWidget->State & WIDGET_STATE_VERTICAL) {
    _RotateRect90(pWidget, &Rect, pRect);
    pRect = &Rect;
  }
  pWidget->pEffect->pfDrawDownRect(pRect);
}

void WIDGET__EFFECT_DrawDown(WIDGET* pWidget) {
  WIDGET__EFFECT_DrawDownRect(pWidget, NULL);
}





void WIDGET__EFFECT_DrawUpRect(WIDGET* pWidget, GUI_RECT* pRect) {
  GUI_RECT Rect;
  if (pWidget->State & WIDGET_STATE_VERTICAL) {
    _RotateRect90(pWidget, &Rect, pRect);
    pRect = &Rect;
  }
  pWidget->pEffect->pfDrawUpRect(pRect);
}




void WIDGET_SetDefaultEffect(const WIDGET_EFFECT* pEffect) {
  _pEffectDefault = pEffect;
}



#else                            /* Avoid problems with empty object modules */
  void WIDGET_C(void) {}
#endif /* GUI_WINSUPPORT */




