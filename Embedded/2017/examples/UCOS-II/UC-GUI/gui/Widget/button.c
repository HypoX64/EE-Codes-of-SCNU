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
#include "BUTTON.h"
#include "WIDGET.h"
#include "GUIDebug.h"
#include "GUI.h"
#include "GUI_Protected.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

/* Define default fonts */
#ifndef BUTTON_FONT_DEFAULT
  #define BUTTON_FONT_DEFAULT &GUI_Font13_1
#endif

/* Support for 3D effects */
#ifndef BUTTON_USE_3D
  #define BUTTON_USE_3D 1
#endif

#ifndef BUTTON_3D_MOVE_X
  #define BUTTON_3D_MOVE_X 1
#endif
#ifndef BUTTON_3D_MOVE_Y
  #define BUTTON_3D_MOVE_Y 1
#endif

/* Define colors */
#ifndef BUTTON_BKCOLOR0_DEFAULT
  #define BUTTON_BKCOLOR0_DEFAULT 0xAAAAAA
#endif

#ifndef BUTTON_BKCOLOR1_DEFAULT
  #define BUTTON_BKCOLOR1_DEFAULT GUI_WHITE
#endif

#ifndef BUTTON_TEXTCOLOR0_DEFAULT
  #define BUTTON_TEXTCOLOR0_DEFAULT GUI_BLACK
#endif

#ifndef BUTTON_TEXTCOLOR1_DEFAULT
  #define BUTTON_TEXTCOLOR1_DEFAULT GUI_BLACK
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
  GUI_COLOR aTextColor[2];
  const GUI_FONT* pFont;
  const GUI_BITMAP* apBitmap[2];
  WM_HMEM hpText;
  #if BUTTON_SUPPORT_STREAMED_BITMAP
    U8 aBitmapIsStreamed[2];
  #endif
  #if BUTTON_SUPPORT_BITMAP_OFFSET    /* Support for bitmap offsets */
    I16 xOffBitmap[2], yOffBitmap[2];
  #endif
  #ifdef _DEBUG
    int DebugId;
  #endif  
} BUTTON_Obj;

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

#define BUTTON_ID 0x42555454

#define BUTTON_H2P(h) (BUTTON_Obj*) WM_HMEM2Ptr(h)

#ifdef _DEBUG
  #define BUTTON_ASSERT_IS_VALID_PTR(p) GUI_DEBUG_ERROROUT_IF(p->DebugId != BUTTON_ID, "BUTTON.C: Wrong handle type or object not init'ed")
  #define BUTTON_INIT_ID(p)   p->DebugId = BUTTON_ID
  #define BUTTON_DEINIT_ID(p) p->DebugId = BUTTON_ID+1
#else
  #define BUTTON_ASSERT_IS_VALID_PTR(p)
  #define BUTTON_INIT_ID(p)
  #define BUTTON_DEINIT_ID(p)
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
static void _Paint(BUTTON_Obj* pObj) {
  const char*s =NULL;
  int State = pObj->Widget.State;
  int PressedState = (State & BUTTON_STATE_PRESSED) ? 1:0;
  GUI_RECT rClient;
  GUI_RECT r;
  GUI_SetFont(pObj->pFont);
  GUI_DEBUG_LOG("BUTTON: Paint(..)\n");
  if (pObj->hpText) {
    s = (const char*) WM_HMEM2Ptr(pObj->hpText);
  }
  GUI_GetClientRect(&rClient);
  r = rClient;
/* Draw background */
  GUI_SetBkColor (pObj->aBkColor[PressedState]);
  GUI_SetColor   (pObj->aTextColor[PressedState]);
  GUI_Clear();
/* Draw bitmap.
   If we have only one, we will use it.
   If we have to we will use the second one (Index 1) for the pressed state
*/
  {
    int Index =0;
    if (pObj->apBitmap[1] && PressedState) {
      Index =1;   
    }
    if (pObj->apBitmap[Index]) {
      #if BUTTON_SUPPORT_STREAMED_BITMAP
        if(pObj->aBitmapIsStreamed[Index]) {
        #if BUTTON_SUPPORT_BITMAP_OFFSET
          GUI_DrawStreamedBitmap((const GUI_BITMAP_STREAM*)(pObj->apBitmap[Index]), pObj->xOffBitmap, pObj->yOffBitmap);
        #else
          GUI_DrawBitmapStreamed((const GUI_BITMAP_STREAM*)(pObj->apBitmap[Index]), 0,0);
        #endif
        } else
      #endif
      {
        #if BUTTON_SUPPORT_BITMAP_OFFSET
          GUI_DrawBitmap(pObj->apBitmap[Index], pObj->xOffBitmap[Index], pObj->yOffBitmap[Index]);
        #else
          GUI_DrawBitmap(pObj->apBitmap[Index], 0,0);
        #endif
      }
    }
  }
/* Draw the actual button (background and text) */  
  #if BUTTON_USE_3D
    if (pObj->Widget.State & BUTTON_STATE_PRESSED) {
      GUI_MoveRect(&r, BUTTON_3D_MOVE_X,BUTTON_3D_MOVE_Y);
    }
  #endif
  GUI_SetTextMode(GUI_TM_TRANS);
  GUI_DispStringInRect(s, &r, GUI_TA_HCENTER | GUI_TA_VCENTER);
/* Draw the 3D effect (if configured) */
  #if BUTTON_USE_3D
  if ((State & BUTTON_STATE_PRESSED) == 0) {
    WIDGET_EFFECT_3D_DrawUp();
  } else {
    GUI_SetColor(0x000000);  /// TBD: Use halftone
    GUI_DrawRect(rClient.y0, rClient.x0, rClient.x1, rClient.y1);
  }
  #endif
  /* Draw focus */
  if (State & BUTTON_STATE_FOCUS) {
    GUI_SetColor(GUI_BLACK);
    GUI_DrawFocusRect(&rClient, 2);
  }
}

/*********************************************************************
*
*       _Delete
*
* Delete attached objects (if any)
*/
static void _Delete(BUTTON_Obj* pObj) {
  WM_FREEPTR(&pObj->hpText);
}

/*********************************************************************
*
*       _OnTouch
*/
static void _OnTouch(BUTTON_Handle hObj, BUTTON_Obj* pObj, WM_MESSAGE*pMsg) {
  int Notification;
  int Hit = 0;
  GUI_TOUCH_tState* pState = (GUI_TOUCH_tState*)pMsg->Data.p;
  if (pMsg->Data.p) {  /* Something happened in our area (pressed or released) */
    if (pState->Pressed) {
      WIDGET_OrState(hObj, BUTTON_STATE_PRESSED);
      Notification = WM_NOTIFICATION_CLICKED;
      WM_SetFocus(hObj);
    } else {
      Hit =1;
      Notification = WM_NOTIFICATION_RELEASED;
      WIDGET_AndState(hObj, BUTTON_STATE_PRESSED);
    }
  } else {
    Notification = WM_NOTIFICATION_MOVED_OUT;
    WIDGET_AndState(hObj, BUTTON_STATE_PRESSED);
  }
  WM_NotifyParent(hObj, Notification);
  if (Hit == 1) {
    GUI_DEBUG_LOG("BUTTON: Hit\n");
    GUI_StoreKey(pObj->Widget.Id);
  }
}

/*********************************************************************
*
*       Callback
*/
static void _BUTTON_Callback(WM_MESSAGE *pMsg) {
  BUTTON_Handle hObj = pMsg->hWin;
  BUTTON_Obj* pObj = BUTTON_H2P(hObj);
  /* Let widget handle the standard messages */
  if (WIDGET_HandleActive(hObj, pMsg) == 0) {
    return;
  }
  switch (pMsg->MsgId) {
  case WM_TOUCH:
    _OnTouch(hObj, pObj, pMsg);
    break;
  case WM_PAINT:
    GUI_DEBUG_LOG("BUTTON: _BUTTON_Callback(WM_PAINT)\n");
    _Paint(pObj);
    return;
  case WM_DELETE:
    GUI_DEBUG_LOG("BUTTON: _BUTTON_Callback(WM_DELETE)\n");
    _Delete(pObj);
    break;       /* No return here ... WM_DefaultProc needs to be called */
  }
  WM_DefaultProc(pMsg);
}

/*********************************************************************
*
*       Exported routines:  Create
*
**********************************************************************
*/

BUTTON_Handle BUTTON_CreateAsChild (int x0, int y0, int xsize, int ysize, WM_HWIN hParent, int Id, int Flags) {
  BUTTON_Handle hObj;
  /* Create the window */
  WM_LOCK();
  hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent,
                       Flags, _BUTTON_Callback,
                       sizeof(BUTTON_Obj)-sizeof(WM_Obj));
  if (hObj) {
    BUTTON_Obj* pObj = BUTTON_H2P(hObj);
    /* init widget specific variables */
    /* init member variables */
    BUTTON_INIT_ID(pObj);
    pObj->Widget.Id     = Id;
    pObj->pFont         = BUTTON_FONT_DEFAULT;
    pObj->aBkColor[0]   = BUTTON_BKCOLOR0_DEFAULT;
    pObj->aBkColor[1]   = BUTTON_BKCOLOR1_DEFAULT;
    pObj->aTextColor[0] = BUTTON_TEXTCOLOR0_DEFAULT;
    pObj->aTextColor[1] = BUTTON_TEXTCOLOR1_DEFAULT;
    pObj->Widget.State  = BUTTON_STATE_INACTIVE;
  } else {
    GUI_DEBUG_ERROROUT_IF(hObj==0, "BUTTON_Create failed")
  }
  WM_UNLOCK();
  return hObj;
}

BUTTON_Handle BUTTON_Create      (  int x0, int y0, int xsize, int ysize, int Id, int Flags) {
  return BUTTON_CreateAsChild(x0, y0, xsize, ysize, WM_HMEM_NULL, Id, Flags);
}

BUTTON_Handle BUTTON_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb) {
  BUTTON_Handle  hThis;
  GUI_USE_PARA(cb);
  hThis = BUTTON_CreateAsChild(
    pCreateInfo->x0 + x0, pCreateInfo->y0 + y0, pCreateInfo->xSize, pCreateInfo->ySize,
    hWinParent, pCreateInfo->Id, pCreateInfo->Flags);
  BUTTON_SetText(hThis, pCreateInfo->pName);
  return hThis;
}

/*********************************************************************
*
*       Exported routines:  Various methods
*
**********************************************************************
*/

void BUTTON_SetText(BUTTON_Handle hObj, const char* s) {
  WM_LOCK();
  if (hObj) {
    BUTTON_Obj* pObj = BUTTON_H2P(hObj);
    BUTTON_ASSERT_IS_VALID_PTR(pObj);
    WM_FREEPTR(&pObj->hpText);
    {
      WM_HMEM hMem = WM_ALLOC(strlen(s)+1);
      if (hMem) {
        strcpy((char *) WM_HMEM2Ptr(hMem), s);
      }
      pObj->hpText = hMem;
    }
    BUTTON_Invalidate(hObj);
  } else {
    GUI_DEBUG_WARN("BUTTON_SetText: Invalid handle");
  }
  WM_UNLOCK();
}

void BUTTON_SetFont(BUTTON_Handle hObj, const GUI_FONT* pfont) {
  if (hObj) {
    BUTTON_Obj* pObj = BUTTON_H2P(hObj);
    BUTTON_ASSERT_IS_VALID_PTR(pObj);
    pObj->pFont = pfont;
    BUTTON_Invalidate(hObj);
  } else {
    GUI_DEBUG_WARN("BUTTON_SetFont: Invalid handle");
  }
}

void BUTTON_SetBkColor(BUTTON_Handle hObj, int Index, GUI_COLOR color) {
  if (hObj) {
    BUTTON_Obj* pObj = BUTTON_H2P(hObj);
    BUTTON_ASSERT_IS_VALID_PTR(pObj);
    pObj->aBkColor[Index] = color;
    BUTTON_Invalidate(hObj);
  } else {
    GUI_DEBUG_WARN("BUTTON_SetBkColor: Invalid handle");
  }
}

void BUTTON_SetTextColor(BUTTON_Handle hObj, int Index, GUI_COLOR color) {
  if (hObj) {
    BUTTON_Obj* pObj = BUTTON_H2P(hObj);
    BUTTON_ASSERT_IS_VALID_PTR(pObj);
    pObj->aTextColor[Index] = color;
    BUTTON_Invalidate(hObj);
  } else {
    GUI_DEBUG_WARN("BUTTON_SetTextColor: Invalid handle");
  }
}

void BUTTON_SetState(BUTTON_Handle hObj, int State) {
  WIDGET_SetState(hObj, State);
}

#if BUTTON_SUPPORT_BITMAP_OFFSET
void BUTTON_SetBitmapEx(BUTTON_Handle hObj, int Index, const GUI_BITMAP* pBitmap, int x, int y) {
  if (hObj) {
    BUTTON_Obj* pObj = BUTTON_H2P(hObj);
    BUTTON_ASSERT_IS_VALID_PTR(pObj);
    if ((unsigned int)Index > GUI_COUNTOF(pObj->apBitmap))
      return;
    pObj->apBitmap[Index] = pBitmap;
    pObj->xOffBitmap[Index] = x;
    pObj->yOffBitmap[Index] = y;
    BUTTON_Invalidate(hObj);
  }
}
#endif

void BUTTON_SetBitmap(BUTTON_Handle hObj, int Index, const GUI_BITMAP* pBitmap) {
  #if BUTTON_SUPPORT_BITMAP_OFFSET
    BUTTON_SetBitmapEx(hObj, Index, pBitmap, 0,0);
  #else
  if (hObj) {
    BUTTON_Obj* pObj = BUTTON_H2P(hObj);
    BUTTON_ASSERT_IS_VALID_PTR(pObj);
    if ((unsigned int)Index > GUI_COUNTOF(pObj->apBitmap))
      return;
    pObj->apBitmap[Index] = pBitmap;
    BUTTON_Invalidate(hObj);
  }
  #endif
}

#if BUTTON_SUPPORT_STREAMED_BITMAP
void BUTTON_SetStreamedBitmap(BUTTON_Handle hObj, int Index, const GUI_BITMAP_STREAM* pBitmap) {
  if (hObj) {
    BUTTON_Obj* pObj = BUTTON_H2P(hObj);
    BUTTON_ASSERT_IS_VALID_PTR(pObj);
    if ((unsigned int)Index > GUI_COUNTOF(pObj->apBitmap))
      return;
    pObj->apBitmap[Index] = (const GUI_BITMAP*)pBitmap;
    pObj->aBitmapIsStreamed[Index] = 1;
    BUTTON_Invalidate(hObj);
  }
}
#endif

#else                            /* Avoid problems with empty object modules */
  void BUTTON_C(void) {}
#endif /* GUI_WINSUPPORT */




