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
File        : RADIO.c
Purpose     : Template for new emWin GSC widgets
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "GUI_Private.H"
#include "RADIO.h"
#include "Widget.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

/* Define colors */
#ifndef RADIO_BKCOLOR0_DEFAULT
  #define RADIO_BKCOLOR0_DEFAULT 0xc0c0c0           /* Inactive color */
#endif

#ifndef RADIO_BKCOLOR1_DEFAULT
  #define RADIO_BKCOLOR1_DEFAULT GUI_WHITE          /* Active color */
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
  I16 Sel;                   /* current selection */
  I16 Spacing;
  I16 Height;
  I16 NumItems;
  #if GUI_DEBUG_LEVEL >1
    int DebugId;
  #endif  
} RADIO_Obj;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static GUI_COLOR _aColor[] = {
     0xC0C0C0,0x808080,0x000000,0xFFFFFF
};

/*********************************************************************
*
*       Static const data
*
**********************************************************************
*/


const GUI_LOGPALETTE PalRadio0 = {
  4,	/* number of entries */
  0, 	/* No transparency */
  &_aColor[0]
};

const unsigned char acRadio0[] = {
  0x00, 0x55, 0x00,
  0x05, 0xAA, 0x50,
  0x1A, 0xFF, 0xAC,
  0x1B, 0xFF, 0xCC,
  0x6F, 0xFF, 0xF3,
  0x6F, 0xFF, 0xF3,
  0x6F, 0xFF, 0xF3,
  0x6F, 0xFF, 0xF3,
  0x1B, 0xFF, 0xCC,
  0x10, 0xFF, 0x0C,
  0x0F, 0x00, 0xF0,
  0x00, 0xFF, 0x00
};

const GUI_BITMAP _bmRadio0 = {
 12, /* XSize */
 12, /* YSize */
 3, /* BytesPerLine */
 2, /* BitsPerPixel */
 acRadio0,  /* Pointer to picture data (indices) */
 &PalRadio0  /* Pointer to palette */
};

const GUI_COLOR ColorsCheck1[] = {
     0xFFFFFF,0x000000
};

const GUI_LOGPALETTE PalCheck1 = {
  2,	/* number of entries */
  1, 	/* No transparency */
  &ColorsCheck1[0]
};

const unsigned char acCheck1[] = {
  _XX_____,
  XXXX____,
  XXXX____,
  _XX_____
};

const GUI_BITMAP _bmCheck1 = {
 4, /* XSize */
 4, /* YSize */
 1, /* BytesPerLine */
 1, /* BitsPerPixel */
 acCheck1,  /* Pointer to picture data (indices) */
 &PalCheck1  /* Pointer to palette */
};


/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/

#define RADIO_ID 0x4544   /* Magic numer, should be unique if possible */

#define RADIO_H2P(h) (RADIO_Obj*) WM_H2P(h)

#ifdef _DEBUG
  #define RADIO_ASSERT_IS_VALID_PTR(p) DEBUG_ERROROUT_IF(p->DebugId != RADIO_ID, "xxx.c: Wrong handle type or Object not init'ed")
  #define RADIO_INIT_ID(p)   p->DebugId = RADIO_ID
  #define RADIO_DEINIT_ID(p) p->DebugId = RADIO_ID+1
#else
  #define RADIO_ASSERT_IS_VALID_PTR(p)
  #define RADIO_INIT_ID(p)
  #define RADIO_DEINIT_ID(p)
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
static void _Paint(RADIO_Handle hObj, RADIO_Obj* pObj) {
  int IsEnabled;
  int i;
  IsEnabled = WIDGET__IsEnabled(&pObj->Widget);
  /* Clear inside  ... Just in case */
  /* Fill with parents background color */
  GUI_SetBkColor(WIDGET__GetBkColor(hObj));
  GUI_Clear();
  for (i = 0; i < pObj->NumItems; i++) {
    int y = i* pObj->Spacing;
    _aColor[3] = pObj->aBkColor[IsEnabled];
    GUI_DrawBitmap(&_bmRadio0, 2, 2 + y);
    if (pObj->Sel == i) {
      GUI_DrawBitmap(&_bmCheck1, 6, 6 + y);
    }
  }
  if (pObj->Widget.State & WIDGET_STATE_FOCUS) {
    GUI_RECT r;
    WIDGET__GetClientRect(&pObj->Widget, &r);
    GUI_SetColor(GUI_BLACK);
    WIDGET__DrawFocusRect(&pObj->Widget, &r, 0);
  }
}


/*********************************************************************
*
*       _OnTouch
*/
static void _OnTouch(RADIO_Handle hObj, RADIO_Obj* pObj, WM_MESSAGE*pMsg) {
  int Notification;
  int Hit = 0;
  GUI_TOUCH_tState* pState = (GUI_TOUCH_tState*)pMsg->Data.p;
  if (pMsg->Data.p) {  /* Something happened in our area (pressed or released) */
    if (pState->Pressed) {
      int y = pState->y;
      int Sel = y / pObj->Spacing;
      y -= Sel * pObj->Spacing;
      if (pObj->Widget.State & WIDGET_STATE_ENABLED) {
        if (y < pObj->Height) {
          RADIO_SetValue(hObj, Sel);
        }
        WM_Invalidate(hObj);
        Notification = WM_NOTIFICATION_CLICKED;
        WM_SetFocus(hObj);
      }
    } else {
      Hit =1;
      Notification = WM_NOTIFICATION_RELEASED;
    }
  } else {
    Notification = WM_NOTIFICATION_MOVED_OUT;
  }
  WM_NotifyParent(hObj, Notification);
  if (Hit == 1) {
    GUI_DEBUG_LOG("RADIO: Hit\n");
    GUI_StoreKey(pObj->Widget.Id);
  }
}

/*********************************************************************
*
*       _OnKey
*/
static void  _OnKey(RADIO_Handle hObj, WM_MESSAGE*pMsg) {
  WM_KEY_INFO* pKeyInfo;
  int Key;
  pKeyInfo = (WM_KEY_INFO*)(pMsg->Data.p);
  Key = pKeyInfo->Key;
  if (pKeyInfo->PressedCnt > 0) {
    switch (Key) {
      case GUI_KEY_RIGHT:
      case GUI_KEY_DOWN:
        RADIO_Inc(hObj);
        break;                    /* Send to parent by not doing anything */
      case GUI_KEY_LEFT:
      case GUI_KEY_UP:
        RADIO_Dec(hObj);
        break;                    /* Send to parent by not doing anything */
      default:
        return;
    }
  }
}

/*********************************************************************
*
*       _Callback
*/
static void _RADIO_Callback (WM_MESSAGE *pMsg) {
  RADIO_Handle hObj;
  RADIO_Obj* pObj;
  hObj = pMsg->hWin;
  pObj = RADIO_H2P(hObj);
  /* Let widget handle the standard messages */
  if (WIDGET_HandleActive(hObj, pMsg) == 0) {
    return;
  }
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_DEBUG_LOG("RADIO: _Callback(WM_PAINT)\n");
    _Paint(hObj, pObj);
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


RADIO_Handle RADIO_Create (int x0, int y0, int xsize, int ysize, WM_HWIN hParent, int Id, int Flags, unsigned Para) {
  RADIO_Handle hObj;
  unsigned NumItems;
  unsigned Spacing;
  int Height = 15;
  /* Create the window */
  WM_LOCK();
  /* Calculate helper variables */
  Spacing = (Para >> 8) & 255;
  if (Spacing == 0) {
    Spacing = 20;
  }
  NumItems = Para  & 255;
  if (NumItems == 0) {
    NumItems = 2;
  }
  if (ysize == 0) {
    ysize = Height + ((NumItems-1) * Spacing);
  }
  hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent,
                                Flags, _RADIO_Callback, sizeof(RADIO_Obj)-sizeof(WM_Obj));
  if (hObj) {
    RADIO_Obj* pObj = RADIO_H2P(hObj);
    /* init widget specific variables */
    WIDGET__Init(&pObj->Widget, WIDGET_STATE_FOCUSSABLE | WIDGET_STATE_ENABLED);
    pObj->Widget.Id     = Id;
    /* init member variables */
    RADIO_INIT_ID(pObj);
    pObj->aBkColor[0]   = RADIO_BKCOLOR0_DEFAULT;
    pObj->aBkColor[1]   = RADIO_BKCOLOR1_DEFAULT;
    pObj->NumItems   = NumItems;
    pObj->Spacing       = Spacing;
    pObj->Height = Height;
  } else {
    GUI_DEBUG_ERROROUT_IF(hObj==0, "RADIO_Create failed")
  }
  WM_UNLOCK();
  return hObj;
}

RADIO_Handle RADIO_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb) {
  RADIO_Handle  hThis;
  GUI_USE_PARA(cb);
  hThis = RADIO_Create(pCreateInfo->x0 + x0, pCreateInfo->y0 + y0, 16, 0,
                          hWinParent, pCreateInfo->Id, pCreateInfo->Flags, pCreateInfo->Para);
  return hThis;
}

/*********************************************************************
*
*       Exported routines:  Various methods
*
**********************************************************************
*/

void RADIO_AddValue(RADIO_Handle hObj, int Add) {
  RADIO_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = RADIO_H2P(hObj);
    RADIO_SetValue(hObj, pObj->Sel + Add);
    WM_UNLOCK();
  }
}

void RADIO_Dec(RADIO_Handle hObj) { RADIO_AddValue(hObj, -1); }
void RADIO_Inc(RADIO_Handle hObj) { RADIO_AddValue(hObj,  1); }

void RADIO_SetValue(RADIO_Handle hObj, int v) {
  RADIO_Obj* pObj;
  int Max;
  if (hObj) {
    WM_LOCK();
    pObj = RADIO_H2P(hObj);
    Max = pObj->NumItems - 1;
    if (Max < 0)
      Max =0;
    /* Put in min/max range */
    if (v < 0) {
      v = 0;
    }
    if (v > Max) {
      v = Max;
    }
    if (pObj->Sel != v) {
      pObj->Sel = v;
      WM_InvalidateWindow(hObj);
      WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       Exported routines:  Query state
*
**********************************************************************
*/

int RADIO_GetValue(RADIO_Handle hObj) {
  int r = 0;
  RADIO_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = RADIO_H2P(hObj);
    r = pObj->Sel;
    WM_UNLOCK();
  }
  return r;
}



#endif  /* #if GUI_WINSUPPORT */



