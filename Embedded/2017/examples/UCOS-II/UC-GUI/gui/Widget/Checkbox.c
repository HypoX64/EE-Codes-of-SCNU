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
File        : CHECKBOX.c
Purpose     : Template for new emWin GSC widgets
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "GUI_Private.H"
#include "CHECKBOX.h"
#include "Widget.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

/* Define default fonts */
#ifndef CHECKBOX_FONT_DEFAULT
  #define CHECKBOX_FONT_DEFAULT &GUI_Font13_1
#endif

/* Support for 3D effects */
#ifndef CHECKBOX_USE_3D
  #define CHECKBOX_USE_3D 1
#endif

/* Define colors */
#ifndef CHECKBOX_BKCOLOR0_DEFAULT
  #define CHECKBOX_BKCOLOR0_DEFAULT 0x808080           /* Inactive color */
#endif

#ifndef CHECKBOX_BKCOLOR1_DEFAULT
  #define CHECKBOX_BKCOLOR1_DEFAULT GUI_WHITE          /* Active color */
#endif

#ifndef CHECKBOX_FGCOLOR0_DEFAULT
  #define CHECKBOX_FGCOLOR0_DEFAULT 0x101010
#endif

#ifndef CHECKBOX_FGCOLOR1_DEFAULT
  #define CHECKBOX_FGCOLOR1_DEFAULT GUI_BLACK
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
  GUI_COLOR aFgColor[2];
  #if GUI_DEBUG_LEVEL >1
    int DebugId;
  #endif  
} CHECKBOX_Obj;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static GUI_COLOR _aColor[2];

/*********************************************************************
*
*       Static const data
*
**********************************************************************
*/
static const GUI_LOGPALETTE _PalCheck = {
  2,	/* number of entries */
  0, 	/* No transparency */
  &_aColor[0]
};

static const unsigned char _acCheck[] = {
  XXXXXXXX, XXX_____,
  XXXXXXXX, XXX_____,
  XXXXXXXX, _XX_____,
  XXXXXXX_, _XX_____,
  XX_XXX__, _XX_____,
  XX__X___, XXX_____,
  XX_____X, XXX_____,
  XXX___XX, XXX_____,
  XXXX_XXX, XXX_____,
  XXXXXXXX, XXX_____,
  XXXXXXXX, XXX_____
};

static const GUI_BITMAP _bmCheck = {
 11, /* XSize */
 11, /* YSize */
 2, /* BytesPerLine */
 1, /* BitsPerPixel */
 _acCheck,  /* Pointer to picture data (indices) */
 &_PalCheck  /* Pointer to palette */
};

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/

#define CHECKBOX_ID 0x4544   /* Magic numer, should be unique if possible */

#define CHECKBOX_H2P(h) (CHECKBOX_Obj*) WM_H2P(h)

#ifdef _DEBUG
  #define CHECKBOX_ASSERT_IS_VALID_PTR(p) DEBUG_ERROROUT_IF(p->DebugId != CHECKBOX_ID, "xxx.c: Wrong handle type or Object not init'ed")
  #define CHECKBOX_INIT_ID(p)   p->DebugId = CHECKBOX_ID
  #define CHECKBOX_DEINIT_ID(p) p->DebugId = CHECKBOX_ID+1
#else
  #define CHECKBOX_ASSERT_IS_VALID_PTR(p)
  #define CHECKBOX_INIT_ID(p)
  #define CHECKBOX_DEINIT_ID(p)
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
static void _Paint(CHECKBOX_Obj* pObj) {
  int ColorIndex;
  ColorIndex = WIDGET__IsEnabled(&pObj->Widget);
  /* Clear inside  ... Just in case */
  GUI_SetBkColor (pObj->aBkColor[ColorIndex]);
  GUI_Clear();
  if (pObj->Widget.State & CHECKBOX_STATE_CHECKED) {
    _aColor[1] = pObj->aBkColor[ColorIndex];
    _aColor[0] = pObj->aFgColor[ColorIndex];
    GUI_DrawBitmap(&_bmCheck, 2, 2);
  }
  /* Draw the 3D effect (if configured) */
  WIDGET__EFFECT_DrawDown(&pObj->Widget);
}


/*********************************************************************
*
*       _OnTouch
*/
static void _OnTouch(CHECKBOX_Handle hObj, CHECKBOX_Obj* pObj, WM_MESSAGE*pMsg) {
  int Notification;
  int Hit = 0;
  GUI_TOUCH_tState* pState = (GUI_TOUCH_tState*)pMsg->Data.p;
  if (pMsg->Data.p) {  /* Something happened in our area (pressed or released) */
    if (pState->Pressed) {
      if (pObj->Widget.State & WIDGET_STATE_ENABLED) {
        pObj->Widget.State ^= CHECKBOX_STATE_CHECKED;
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
    GUI_DEBUG_LOG("CHECKBOX: Hit\n");
    GUI_StoreKey(pObj->Widget.Id);
  }
}

/*********************************************************************
*
*       _Callback
*/
static void _CHECKBOX_Callback (WM_MESSAGE *pMsg) {
  CHECKBOX_Handle hObj;
  CHECKBOX_Obj* pObj;
  hObj = pMsg->hWin;
  pObj = CHECKBOX_H2P(hObj);
  /* Let widget handle the standard messages */
  if (WIDGET_HandleActive(hObj, pMsg) == 0) {
    return;
  }
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_DEBUG_LOG("CHECKBOX: _Callback(WM_PAINT)\n");
    _Paint(pObj);
    return;
  case WM_TOUCH:
    _OnTouch(hObj, pObj, pMsg);
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


CHECKBOX_Handle CHECKBOX_Create (int x0, int y0, int xsize, int ysize, WM_HWIN hParent, int Id, int Flags) {
  CHECKBOX_Handle hObj;
  /* Create the window */
  WM_LOCK();
  hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent,
                                Flags, _CHECKBOX_Callback, sizeof(CHECKBOX_Obj)-sizeof(WM_Obj));
  if (hObj) {
    CHECKBOX_Obj* pObj = CHECKBOX_H2P(hObj);
    /* init widget specific variables */
    WIDGET__Init(&pObj->Widget, WIDGET_STATE_FOCUSSABLE | WIDGET_STATE_ENABLED);
    pObj->Widget.Id     = Id;
    /* init member variables */
    CHECKBOX_INIT_ID(pObj);
    pObj->aBkColor[0]   = CHECKBOX_BKCOLOR0_DEFAULT;
    pObj->aBkColor[1]   = CHECKBOX_BKCOLOR1_DEFAULT;
    pObj->aFgColor[0]   = CHECKBOX_FGCOLOR0_DEFAULT;
    pObj->aFgColor[1]   = CHECKBOX_FGCOLOR1_DEFAULT;
  } else {
    GUI_DEBUG_ERROROUT_IF(hObj==0, "CHECKBOX_Create failed")
  }
  WM_UNLOCK();
  return hObj;
}

CHECKBOX_Handle CHECKBOX_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb) {
  CHECKBOX_Handle  hThis;
  GUI_USE_PARA(cb);
  hThis = CHECKBOX_Create(pCreateInfo->x0 + x0, pCreateInfo->y0 + y0, 15, 15,
                          hWinParent, pCreateInfo->Id, pCreateInfo->Flags);
  return hThis;
}

/*********************************************************************
*
*       Exported routines:  Various methods
*
**********************************************************************
*/
void CHECKBOX_Check(CHECKBOX_Handle hObj) {
  WIDGET_OrState(hObj, CHECKBOX_STATE_CHECKED);
}

void CHECKBOX_Uncheck(CHECKBOX_Handle hObj) {
  WIDGET_AndState(hObj, CHECKBOX_STATE_CHECKED);
}

/*********************************************************************
*
*       Exported routines:  Query state
*
**********************************************************************
*/

/*********************************************************************
*
*       CHECKBOX_IsChecked
*/
int CHECKBOX_IsChecked(CHECKBOX_Handle hObj) {
  int r = 0;
  CHECKBOX_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = CHECKBOX_H2P(hObj);
    r = (pObj->Widget.State & CHECKBOX_STATE_CHECKED) ? 1 : 0;
    WM_UNLOCK();
  }
  return r;
}



#endif  /* #if GUI_WINSUPPORT */



