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
File        : EDIT.c
Purpose     : emWin GSC button widget
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>

#define EDIT_C       /* Required to generate intermodule data */

#include "EDIT.h"
#include "GUIDebug.h"
#include "GUI_Protected.h"
#include "EDIT_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

#ifndef EDIT_LOG_ENABLE
  #ifdef _DEBUG
    #define EDIT_LOG_ENABLE 0
  #else
    #define EDIT_LOG_ENABLE 0
  #endif
#endif

/* Define default fonts */
#ifndef EDIT_FONT_DEFAULT
  #define EDIT_FONT_DEFAULT &GUI_Font13_1
#endif

#ifndef EDIT_ALIGN_DEFAULT
  #define EDIT_ALIGN_DEFAULT GUI_TA_RIGHT | GUI_TA_VCENTER
#endif

/* Define colors */
#ifndef EDIT_BKCOLOR0_DEFAULT
  #define EDIT_BKCOLOR0_DEFAULT 0xc0c0c0
#endif

#ifndef EDIT_BKCOLOR1_DEFAULT
  #define EDIT_BKCOLOR1_DEFAULT GUI_WHITE
#endif

#ifndef EDIT_TEXTCOLOR0_DEFAULT
  #define EDIT_TEXTCOLOR0_DEFAULT GUI_BLACK
#endif

#ifndef EDIT_TEXTCOLOR1_DEFAULT
  #define EDIT_TEXTCOLOR1_DEFAULT GUI_BLACK
#endif

#ifndef EDIT_BORDER_DEFAULT
  #define EDIT_BORDER_DEFAULT 1
#endif

#ifndef EDIT_XOFF
  #define EDIT_XOFF 2
#endif

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static int _DefaultAlign              = EDIT_ALIGN_DEFAULT;
static int _DefaultBorder             = EDIT_BORDER_DEFAULT;
static const GUI_FONT * _pDefaultFont = EDIT_FONT_DEFAULT;

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/

#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  #define OBJECT_ID 0x4569   /* Magic nubmer, should be unique if possible */
  #define INIT_ID(p)   p->DebugId = OBJECT_ID
  #define DEINIT_ID(p) p->DebugId = 0
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
EDIT_Obj* EDIT_h2p(EDIT_Handle h) {
  EDIT_Obj* p = (EDIT_Obj*)WM_HMEM2Ptr(h);
  if (p) {
    if (p->DebugId != OBJECT_ID) {
      GUI_DEBUG_ERROROUT("EDIT.C: Wrong handle type or Object not init'ed");
      return 0;
    }
  }
  return p;
}
#endif

/*********************************************************************
*
*       _Paint
*/
static void _Paint(EDIT_Obj* pObj) {
  int PixelLen, xSize, ySize, xPosText, xPosCursor, yPosText, yPosCursor, XSizeCursor, YSizeCursor;
  int IsEnabled;
  GUI_RECT rClient, rWindow;
  char * s;
  s = (char*) WM_HMEM2Ptr(pObj->hpText);
  GUI_DEBUG_LOG("BUTTON: _Paint(..)\n");
  if (pObj->Border) {
    GUI_SetBkColor(pObj->aBkColor[0]);
    GUI_Clear();
  }
  IsEnabled = WIDGET__IsEnabled(&pObj->Widget);
  /* Set clipping rectangle */
  WIDGET__GetInsideRect(&pObj->Widget, &rWindow);
  WM_SetUserClipRect(&rWindow);
  /* Calculate size */
  GUI_GetClientRect(&rClient);
  xSize = rClient.x1 - rClient.x0 + 1;
  ySize = rClient.y1 - rClient.y0 + 1;
  /* Draw background */
  GUI_SetBkColor (pObj->aBkColor[IsEnabled]);
  GUI_SetColor   (pObj->aTextColor[0]);
  GUI_Clear();
  /* Calculate length */
  GUI_SetFont    (pObj->pFont);
  PixelLen = GUI_GetStringDistX(s);
  /* Calculate size of cursor */
  YSizeCursor = GUI_GetFontDistY();
  if (pObj->EditMode == GUI_EDIT_MODE_INSERT) {
    if (pObj->XSizeCursor != 0) {
      XSizeCursor = pObj->XSizeCursor;
    } else {
      XSizeCursor = GUI_GetCharDistX(' ');
    }
  } else {
    if (pObj->CursorPos < (int)strlen(s))  {
      XSizeCursor = GUI_GetCharDistX(*(s + pObj->CursorPos));
    } else {
      XSizeCursor = pObj->XSizeCursor;
    }
  }
  /* Calculate X-pos */
  switch (pObj->Align & GUI_TA_HORIZONTAL) {
    case GUI_TA_CENTER:
      xPosCursor = (xSize - PixelLen + 1) / 2;
      xPosText = xSize / 2;
      break;
    case GUI_TA_LEFT:
      xPosCursor = pObj->Border + EDIT_XOFF;
      xPosText   = pObj->Border + EDIT_XOFF;
      break;
    case GUI_TA_RIGHT:
      xPosCursor = xSize - (pObj->Border + EDIT_XOFF) - PixelLen;
      xPosText   = xSize - (pObj->Border + EDIT_XOFF);
      break;
  }
  /* Calculate Y-pos */
  switch (pObj->Align & GUI_TA_VERTICAL) {
    case GUI_TA_TOP:
      yPosCursor = 0;
      yPosText = 0;
      break;
    case GUI_TA_BOTTOM:
      yPosCursor = ySize - YSizeCursor;
      yPosText = ySize;
      break;
    case GUI_TA_VCENTER:
      yPosCursor = (ySize - YSizeCursor + 1) / 2;
      yPosText = ySize / 2;
      break;
  }
  /* Display text */
  GUI_SetTextAlign(pObj->Align);
  GUI_DispStringAt(s, xPosText, yPosText);
  /* Display cursor */
  if (pObj->Widget.State & WIDGET_STATE_FOCUS) {
    int i;
    for (i = 0; i != pObj->CursorPos; i++) {
      xPosCursor += GUI_GetCharDistX(*(s + i));
    }
    GUI_InvertRect(xPosCursor, 
                   yPosCursor, 
                   xPosCursor + XSizeCursor - 1, 
                   yPosCursor + YSizeCursor - 1);
  }
  WM_SetUserClipRect(NULL);
  /* Draw the 3D effect (if configured) */
  WIDGET__EFFECT_DrawDown(&pObj->Widget);
}

/*********************************************************************
*
*       _Delete
*/
static void _Delete(EDIT_Obj* pObj) {
  WM_FREEPTR(&pObj->hpText);
}


/*********************************************************************
*
*       _SetCursor
*/
static void _SetCursor(EDIT_Handle hObj, EDIT_Obj* pObj, int x) {
  int xPos, xSize, PixelLen, Len;
  char * s = (char*) WM_HMEM2Ptr(pObj->hpText);
  const GUI_FONT *pOldFont = GUI_SetFont(pObj->pFont);
  xSize = WM_GetWindowSizeX(hObj);
  PixelLen = GUI_GetStringDistX(s);
  xPos = x;
  switch (pObj->Align & GUI_TA_HORIZONTAL) {
    case GUI_TA_CENTER:
      xPos -= (xSize - PixelLen + 1) / 2;
      break;
    case GUI_TA_LEFT:
      xPos -= (pObj->Border + EDIT_XOFF);
      break;
    case GUI_TA_RIGHT:
      xPos -= xSize - PixelLen - (pObj->Border + EDIT_XOFF);
      break;
  }
  Len = strlen(s);
  if (xPos < 0) {
    pObj->CursorPos = 0;
  } else if (xPos > PixelLen) {
    pObj->CursorPos = Len;
  } else {
    int i, x;
    for (i = 0, x = 0; (i < Len) && (x < xPos); i++) {
      int xLenChar = GUI_GetCharDistX(*(s + i));
      if (xPos < (x + xLenChar))
        break;
      x += xLenChar;
    }
    pObj->CursorPos = i;
    EDIT_Invalidate(hObj);
  }
  GUI_SetFont(pOldFont);
}

/*********************************************************************
*
*       _OnTouch
*/
static void _OnTouch(EDIT_Handle hObj, EDIT_Obj* pObj, WM_MESSAGE*pMsg) {
  GUI_TOUCH_tState* pState = (GUI_TOUCH_tState*)pMsg->Data.p;
  if (pMsg->Data.p) {  /* Something happened in our area (pressed or released) */
    if (pState->Pressed) {
      GUI_DEBUG_LOG1("EDIT__Callback(WM_TOUCH, Pressed, Handle %d)\n",1);
      _SetCursor(hObj, pObj, pState->x);
      WM_SetFocus(hObj);
    } else {
      GUI_DEBUG_LOG1("EDIT__Callback(WM_TOUCH, Released, Handle %d)\n",1);
    }
  } else {
    GUI_DEBUG_LOG1("_EDIT_Callback(WM_TOUCH, Moved out, Handle %d)\n",1);
  }
}

/*********************************************************************
*
*       Callback
*/
static void EDIT__Callback (WM_MESSAGE * pMsg) {
  int IsEnabled;
  EDIT_Handle hObj = (EDIT_Handle)pMsg->hWin;
  EDIT_Obj* pObj = (EDIT_Obj*)WM_HMEM2Ptr(hObj);
  IsEnabled = WIDGET__IsEnabled(&pObj->Widget);
  /* Let widget handle the standard messages */
  if (WIDGET_HandleActive(hObj, pMsg) == 0) {
    return;
  }
  switch (pMsg->MsgId) {
  case WM_TOUCH:
    if (IsEnabled) {
      _OnTouch(hObj, pObj, pMsg);
    }
    break;
  case WM_PAINT:
    GUI_DEBUG_LOG("EDIT: _Callback(WM_PAINT)\n");
    _Paint(pObj);
    return;
  case WM_DELETE:
    GUI_DEBUG_LOG("EDIT: _Callback(WM_DELETE)\n");
    _Delete(pObj);
    break;       /* No return here ... WM_DefaultProc needs to be called */
  case WM_KEY:
    if (IsEnabled) {
      if ( ((WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt >0) {
        int Key = ((WM_KEY_INFO*)(pMsg->Data.p))->Key;
        switch (Key) {
          case GUI_KEY_TAB:
            break;                    /* Send to parent by not doing anything */
          default:
            EDIT_AddKey(hObj, Key);
            return;
        }
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

EDIT_Handle EDIT_CreateAsChild     (int x0, int y0, int xsize, int ysize, WM_HWIN hParent, int Id, int Flags, int MaxLen) {
  EDIT_Handle hObj;
  if (MaxLen == 0) {
    MaxLen = 8;
  }
  /* Alloc memory for obj */
  WM_LOCK();
  hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, 
                       WM_CF_SHOW | Flags, EDIT__Callback,
                       sizeof(EDIT_Obj)-sizeof(WM_Obj));
  if (hObj) {
    EDIT_Obj* pObj = (EDIT_Obj*)WM_HMEM2Ptr(hObj);
    /* init widget specific variables */
    WIDGET__Init(&pObj->Widget, WIDGET_STATE_FOCUSSABLE  | WIDGET_STATE_ENABLED);
    pObj->Widget.Id     = Id;
    /* init member variables */
    INIT_ID(pObj);
    pObj->pFont         = _pDefaultFont;
    pObj->aBkColor[0]   = EDIT_BKCOLOR0_DEFAULT;
    pObj->aBkColor[1]   = EDIT_BKCOLOR1_DEFAULT;
    pObj->aTextColor[0] = EDIT_TEXTCOLOR0_DEFAULT;
    pObj->aTextColor[1] = EDIT_TEXTCOLOR1_DEFAULT;
    pObj->Align         = _DefaultAlign;
    pObj->Border        = _DefaultBorder;
    pObj->XSizeCursor   = 1;
    pObj->MaxLen        = MaxLen;
    if ((pObj->hpText = WM_ALLOC(MaxLen+1)) ==0) {
      GUI_DEBUG_ERROROUT("EDIT_Create failed to alloc buffer");
      EDIT_Delete(hObj);
      hObj =0;
    }
  }
  WM_UNLOCK();
  return hObj;
}

EDIT_Handle EDIT_Create(int x0, int y0, int xsize, int ysize, int Id, int MaxLen, int Flags) {
  return EDIT_CreateAsChild(x0, y0, xsize, ysize, WM_HMEM_NULL, Id, Flags, MaxLen);
}

EDIT_Handle EDIT_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* pCallback) {
  EDIT_Handle hEdit;
  GUI_USE_PARA(pCallback);
  hEdit = EDIT_CreateAsChild(
    pCreateInfo->x0 + x0, pCreateInfo->y0 + y0, pCreateInfo->xSize, pCreateInfo->ySize,
    hWinParent, pCreateInfo->Id, pCreateInfo->Flags, pCreateInfo->Para);
  return hEdit;
}

/*********************************************************************
*
*       Exported routines:  Various methods
*
**********************************************************************
*/

void EDIT_AddKey(EDIT_Handle hObj, int Key) {
  EDIT_Obj* pObj;
  if (hObj == 0)
    return;
  WM_LOCK();
  pObj = EDIT_H2P(hObj);
  if (pObj) {
    if (pObj->pfAddKeyEx) {
      pObj->pfAddKeyEx(pObj, hObj, Key);
    } else {
      char*s = (char*) WM_HMEM2Ptr(pObj->hpText);
      int len = strlen(s);
      switch (Key) {
        case GUI_KEY_UP:
          {
            char c = *(s + pObj->CursorPos);
            if (c < 0x7f) {
              *(s + pObj->CursorPos) = c + 1;
              WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
            }
          }
          break;
        case GUI_KEY_DOWN:
          {
            char c = *(s + pObj->CursorPos);
            if (c > 0x20) {
              *(s + pObj->CursorPos) = c - 1;
              WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
            }
          }
          break;
        case GUI_KEY_RIGHT:
          if (pObj->CursorPos < (pObj->MaxLen - 1))
            if (pObj->CursorPos < len)
              pObj->CursorPos++;
          break;
        case GUI_KEY_LEFT:
          if (pObj->CursorPos > 0)
            pObj->CursorPos--;
          break;
        case GUI_KEY_BACKSPACE:
          if ((len > 0) && (pObj->CursorPos > 0)) {
            int CopyLength = pObj->MaxLen - pObj->CursorPos;
            strncpy(s + pObj->CursorPos - 1, s + pObj->CursorPos, CopyLength);
            *(s + len - 1) = 0;
            WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
            pObj->CursorPos--;
          }
          break;
        case GUI_KEY_DELETE:
          if ((len > 0) && (pObj->CursorPos < len)) {
            if (len > 1) {
              int CopyLength = pObj->MaxLen - pObj->CursorPos - 1;
              strncpy(s + pObj->CursorPos, s + pObj->CursorPos + 1, CopyLength);
            }
            *(s + len - 1) = 0;
            WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
          }
          break;
        case GUI_KEY_INSERT:
          if (pObj->EditMode == GUI_EDIT_MODE_OVERWRITE)
            pObj->EditMode = GUI_EDIT_MODE_INSERT;
          else
            pObj->EditMode = GUI_EDIT_MODE_OVERWRITE;
          break;
        case GUI_KEY_ENTER:
        case GUI_KEY_ESCAPE:
          break;
        default:
          if ((Key >= 0x20) && (Key <= 0x7f)) {
            if (pObj->EditMode == GUI_EDIT_MODE_INSERT) {
              if (len < pObj->MaxLen) {
                int CopyLength = pObj->MaxLen - pObj->CursorPos - 1;
                memmove(s + pObj->CursorPos + 1, s + pObj->CursorPos, CopyLength);
                *(s + pObj->CursorPos) = Key;
                WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
                if (pObj->CursorPos < (pObj->MaxLen - 1))
                  pObj->CursorPos++;
              }
            } else {
              *(s + pObj->CursorPos) = Key;
              WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
              if (pObj->CursorPos < (pObj->MaxLen - 1))
                pObj->CursorPos++;
            }
          }
          break;
      }
    }
    EDIT_Invalidate(hObj);
  }
  WM_UNLOCK();
}

void EDIT_SetFont(EDIT_Handle hObj, const GUI_FONT* pfont) {
  EDIT_Obj* pObj;
  if (hObj == 0)
    return;
  WM_LOCK();
  pObj = EDIT_H2P(hObj);
  if (pObj) {
    pObj->pFont = pfont;
    EDIT_Invalidate(hObj);
  }
  WM_UNLOCK();
}

void EDIT_SetBkColor(EDIT_Handle hObj, int Index, GUI_COLOR color) {
  EDIT_Obj* pObj;
  if (hObj == 0)
    return;
  WM_LOCK();
  pObj = EDIT_H2P(hObj);
  if (pObj) {
    pObj->aBkColor[Index] = color;
    EDIT_Invalidate(hObj);
  }
  WM_UNLOCK();
}

void EDIT_SetTextColor(EDIT_Handle hObj, int Index, GUI_COLOR color) {
  EDIT_Obj* pObj;
  if (hObj == 0)
    return;
  WM_LOCK();
  pObj = EDIT_H2P(hObj);
  if (pObj) {
    pObj->aTextColor[Index] = color;
    EDIT_Invalidate(hObj);
  }
  WM_UNLOCK();
}

void EDIT_SetText     (EDIT_Handle hObj, const char* sNew) {
  EDIT_Obj* pObj;
  if (hObj == 0)
    return;
  WM_LOCK();
  pObj = EDIT_H2P(hObj);
  if (pObj) {
    char*sDest = (char*) WM_HMEM2Ptr(pObj->hpText);
    int Len = sNew ? strlen(sNew) : 0;
    if (Len > pObj->MaxLen)
      Len = pObj->MaxLen;
    memcpy(sDest, sNew, Len);
    *(sDest+Len) = 0;
    pObj->CursorPos = Len;
    if (pObj->CursorPos == pObj->MaxLen)
      pObj->CursorPos--;
    EDIT_Invalidate(hObj);
  }
  WM_UNLOCK();
}

void EDIT_GetText(EDIT_Handle hObj, char* sDest, int MaxLen) {
  EDIT_Obj* pObj;
  if (hObj == 0)
    return;
  WM_LOCK();
  pObj = EDIT_H2P(hObj);
  if (pObj) {
    char * sSource = (char*) WM_HMEM2Ptr(pObj->hpText);
    int Len = strlen(sSource);
    if (Len > (MaxLen - 1))
      Len = MaxLen - 1;
    memcpy((void *)sDest, (const void *)sSource, Len);
    *(sDest+Len) = 0;
  }
  WM_UNLOCK();
}

I32  EDIT_GetValue(EDIT_Handle hObj) {
  EDIT_Obj* pObj;
  I32 r = 0;
  if (hObj) {
    WM_LOCK();
    pObj = EDIT_H2P(hObj);
    r = pObj->CurrentValue;
    WM_UNLOCK();
  }
  return r;
}

void EDIT_SetValue(EDIT_Handle hObj, I32 Value) {
  EDIT_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = EDIT_H2P(hObj);
    /* Put in min/max range */
    if (Value < pObj->Min) {
      Value = pObj->Min;
    }
    if (Value > pObj->Max) {
      Value = pObj->Max;
    }
    if (pObj->CurrentValue != (U32)Value) {
      pObj->CurrentValue = Value;
      if (pObj->pfUpdateBufer) {
        pObj->pfUpdateBufer(pObj);
      }
      WM_InvalidateWindow(hObj);
      WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
    }
    WM_UNLOCK();
  }
}

void EDIT_SetMaxLen(EDIT_Handle  hObj, int MaxLen) {
  EDIT_Obj* pObj;
  WM_HMEM hpText;
  if (hObj) {
    WM_LOCK();
    pObj = EDIT_H2P(hObj);
    if ((hpText = WM_ALLOC(MaxLen+1)) ==0) {
      GUI_DEBUG_ERROROUT("EDIT_SetMaxLen failed to alloc buffer");
    } else {
      WM_FREEPTR(&pObj->hpText);
      pObj->hpText = hpText;
      pObj->MaxLen = MaxLen;
    }
    EDIT_Invalidate(hObj);
    WM_UNLOCK();
  }
}

void EDIT_SetTextAlign(EDIT_Handle hObj, int Align) {
  EDIT_Obj* pObj;
  if (hObj == 0)
    return;
  WM_LOCK();
  pObj = EDIT_H2P(hObj);
  if (pObj) {
    pObj->Align = Align;
    EDIT_Invalidate(hObj);
  }
  WM_UNLOCK();
}

void EDIT_SetDefaultFont(const GUI_FONT* pFont) {
  _pDefaultFont = pFont;
}

const GUI_FONT* EDIT_GetDefaultFont(void) {
  return _pDefaultFont;
}

void EDIT_SetDefaultTextAlign(int Align) {
  WM_LOCK();
  _DefaultAlign = Align;
  WM_UNLOCK();
}

#else  /* avoid empty object files */

void Edit_C(void) {}

#endif
