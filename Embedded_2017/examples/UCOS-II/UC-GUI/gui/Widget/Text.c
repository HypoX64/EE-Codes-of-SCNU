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
File        : TEXT.c
Purpose     : Template for new emWin GSC widgets
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "TEXT.h"
#include "Widget.h"
#include "GUIDebug.h"
#include "GUI_Private.H"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

/* Define default fonts */
#ifndef TEXT_FONT_DEFAULT
  #define TEXT_FONT_DEFAULT &GUI_Font13_1
#endif


/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/

typedef struct {
  WM_Obj WMObj;
  WM_HMEM hpText;
  const GUI_FONT* pFont;
  I16 Align;
  #if (GUI_DEBUG_LEVEL > 1)
    int DebugId;
  #endif  
} TEXT_Obj;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static const GUI_FONT * _pDefaultFont = TEXT_FONT_DEFAULT;

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/

#define TEXT_ID 0x4544   /* Magic numer, should be unique if possible */

#define TEXT_H2P(h) (TEXT_Obj*) WM_HMEM2Ptr(h)

#ifdef _DEBUG
  #define TEXT_ASSERT_IS_VALID_PTR(p) DEBUG_ERROROUT_IF(p->DebugId != TEXT_ID, "xxx.c: Wrong handle type or Object not init'ed")
  #define TEXT_INIT_ID(p)   p->DebugId = TEXT_ID
  #define TEXT_DEINIT_ID(p) p->DebugId = TEXT_ID+1
#else
  #define TEXT_ASSERT_IS_VALID_PTR(p)
  #define TEXT_INIT_ID(p)
  #define TEXT_DEINIT_ID(p)
#endif

/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/

static void _FreeAttached(TEXT_Obj* pObj) {
  WM_FREEPTR(&pObj->hpText);
}

static void _Paint(TEXT_Handle hObj, TEXT_Obj* pObj) {
  const char * s;
  GUI_RECT Rect;
  GUI_SetColor(GUI_BLACK);
  GUI_SetFont    (pObj->pFont);
  /* Fill with parents background color */
  GUI_SetBkColor(WIDGET__GetBkColor(hObj));
  GUI_Clear();
  /* Show the text */
  if (pObj->hpText) {
    s = (const char*) WM_HMEM2Ptr(pObj->hpText);
    GUI_SetTextMode(GUI_TM_TRANS);
    WM_GetClientRect(&Rect);
    GUI_DispStringInRect(s, &Rect, pObj->Align);
  }
}

static void _Delete(TEXT_Obj* pObj) {
  /* Delete attached objects (if any) */
  GUI_DEBUG_LOG("TEXT: Delete() Deleting attached items");
  if (pObj->hpText) {
    _FreeAttached(pObj);
  }
}

static void _TEXT_Callback (WM_MESSAGE*pMsg) {
  TEXT_Handle hObj = pMsg->hWin;
  TEXT_Obj* pObj = TEXT_H2P(hObj);
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_DEBUG_LOG("TEXT: _Callback(WM_PAINT)\n");
    _Paint(hObj, pObj);
    return;
  case WM_DELETE:
    GUI_DEBUG_LOG("TEXT: _Callback(WM_DELETE)\n");
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

/* Note: the parameters to a create function may vary.
         Some widgets may have multiple create functions */


TEXT_Handle TEXT_CreateAsChild (int x0, int y0, int xsize, int ysize, WM_HWIN hParent, int Id, int Flags, const char * s, int Align) {
  TEXT_Handle hObj;
  /* Create the window */
  WM_LOCK();
  GUI_USE_PARA(Id);
  hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent,
                       Flags, _TEXT_Callback,
                       sizeof(TEXT_Obj)-sizeof(WM_Obj));
  if (hObj) {
    TEXT_Obj* pObj = TEXT_H2P(hObj);
    /* init widget specific variables */
    /* init member variables */
    TEXT_INIT_ID(pObj);
    {
      WM_HMEM hMem = WM_ALLOC(strlen(s)+1);
      if (hMem) {
        strcpy((char *) WM_HMEM2Ptr(hMem), s);
      }
      pObj->hpText = hMem;
      pObj->Align  = Align;
      pObj->pFont  = _pDefaultFont;
    }
  } else {
    GUI_DEBUG_ERROROUT_IF(hObj==0, "TEXT_Create failed")
  }
  WM_UNLOCK();
  return hObj;
}

TEXT_Handle TEXT_Create      (  int x0, int y0, int xsize, int ysize, int Id, int Flags, const char * s, int Align) {
  return TEXT_CreateAsChild(x0, y0, xsize, ysize, WM_HMEM_NULL, Id, Flags, s, Align);
}

TEXT_Handle TEXT_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb) {
  TEXT_Handle  hThis;
  GUI_USE_PARA(cb);
  hThis = TEXT_CreateAsChild(pCreateInfo->x0 + x0, pCreateInfo->y0 + y0, pCreateInfo->xSize, pCreateInfo->ySize,
                             hWinParent, pCreateInfo->Id, 0, pCreateInfo->pName, pCreateInfo->Flags);
  if (hThis) {
    TEXT_Obj* pObj;
    pObj = TEXT_H2P(hThis);
    pObj->Align = pCreateInfo->Flags;
  }
  return hThis;
}

/*********************************************************************
*
*       Exported routines:  Various methods
*
**********************************************************************
*/

void TEXT_SetDefaultFont(const GUI_FONT* pFont) {
  _pDefaultFont = pFont;
}

const GUI_FONT* TEXT_GetDefaultFont(void) {
  return _pDefaultFont;
}

#endif  /* #if GUI_WINSUPPORT */


