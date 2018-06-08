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
File        : GUICurs.C
Purpose     : Cursor routines of the graphics library
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Private.h"

#if GUI_SUPPORT_CURSOR

/*******************************************************************
*
*       Types
*
********************************************************************
*/
void   (*_cbShowCursor)(void);
void   (*_cbHideCursor)(void);

/*******************************************************************
*
*       static data
*
********************************************************************
*/

static  GUI_HMEM _hBuffer;
static  GUI_RECT _Rect;
static  char _CursorOn;
static  const GUI_BITMAP* _pBM;
static  U8   _CursorDeActCnt;
static  int  _AllocSize;

/*******************************************************************
*
*                  static Show / Hide
*
********************************************************************

Purpose:
  Show / Hide cursor.
*/
static void Hide(void) {
  GUI_RECT r = GUI_Context.ClipRect;
  LCD_SetClipRectMax();
  if (_cbHideCursor)
    _cbHideCursor();
  GUI_Context.ClipRect = r;
}

static void Show(void) {
  GUI_RECT r = GUI_Context.ClipRect;
  LCD_SetClipRectMax();
  if (_cbShowCursor)
    _cbShowCursor();
  GUI_Context.ClipRect = r;
}

static void  _CalcRect(void) {
  if (_pBM) {
    _Rect.x1 = _Rect.x0 + _pBM->XSize - 1;
    _Rect.y1 = _Rect.y0 + _pBM->YSize - 1;
  }
}

/*******************************************************************
*
*                  Activate / Deactivate
*
********************************************************************

Purpose:
  Allows activation or deactivation of cursor. Can be used to make
  cursor flash.
*/
void GUI_CURSOR_Activate(void) {
  GUI_LOCK();
  if ((--_CursorDeActCnt) ==0) {
    Show();
  }
  GUI_UNLOCK();
}

void GUI_CURSOR_Deactivate(void) {
  GUI_LOCK();
  if (_CursorDeActCnt-- ==0)
    Hide();
  GUI_UNLOCK();
}



/*******************************************************************
*
*                  static: SetCursor
*
********************************************************************

Purpose:
  Show cursor.
*/
static void _SetCursor(const GUI_BITMAP* pBM, void (*cbShow)(void), void (*cbHide)(void)) {
  Hide();  /* Make sure the old cursor (if there was an old one) is history */
  _CursorOn = 1;
  _pBM = pBM;
  _cbShowCursor = cbShow;
  _cbHideCursor = cbHide;
  Show();
}

/*******************************************************************
*
*                  Cursor
*
********************************************************************
Purpose:
*/

static void _Draw(void) {
  int x, y, xSize, ySize;
  LCD_PIXELINDEX* pData;
  GUI_LOCK();
  /* Save bitmap data */
  pData = GUI_ALLOC_h2p(_hBuffer);
  xSize = _Rect.x1 - _Rect.x0 + 1;
  ySize = _Rect.y1 - _Rect.y0 + 1;
  for (y = 0; y < ySize; y++) {
    for (x = 0; x < xSize; x++) {
      *(pData + x) = LCD_GetPixelIndex(_Rect.x0 + x, _Rect.y0 + y);
    }
    pData += _pBM->XSize;
  }
  GUI_UNLOCK();
  /* Draw bitmap */
  GL_DrawBitmap(_pBM, _Rect.x0, _Rect.y0);
}

static void _Undraw(void) {
  int x, y, xSize, ySize;
  LCD_PIXELINDEX* pData;
  /* Save bitmap data */
  GUI_LOCK();
  pData = GUI_ALLOC_h2p(_hBuffer);
  xSize = _Rect.x1 - _Rect.x0 + 1;
  ySize = _Rect.y1 - _Rect.y0 + 1;
  for (y = 0; y < ySize; y++) {
    for (x = 0; x < xSize; x++) {
      LCD_SetPixelIndex(x + _Rect.x0, y + _Rect.y0, *(pData + x));
    }
    pData += _pBM->XSize;
  }
  GUI_UNLOCK();
}


void GUI_CURSOR_Select(const GUI_BITMAP* pBM) {
  int AllocSize;
  GUI_LOCK();
  if (pBM != _pBM) {
    AllocSize = pBM->XSize * pBM->YSize * sizeof(LCD_PIXELINDEX);
    if (AllocSize != _AllocSize) {
      GUI_ALLOC_FreePtr(&_hBuffer);
    }
    _hBuffer = GUI_ALLOC_Alloc(AllocSize);
    _SetCursor(pBM, _Draw, _Undraw);
    _pBM = pBM;
    _CalcRect();
  }
  GUI_UNLOCK();
}


/*******************************************************************
*
*                  GUI_CURSOR_TempHide
*
********************************************************************
Purpose:
  Hide cursor if a part of the given rectangle is located in the
  rectangle used for the cursor. This routine is called automatically
  by the window manager. This way the window manager can
  automatically make sure that the cursor is always displayed
  correctly.
Params:
  pRect   Rectangle under consideration

*/
void GUI_CURSOR_TempHide(const GUI_RECT* pRect) {
  if (_CursorOn) {
    if (_CursorDeActCnt==0) {
      if ((pRect == NULL) | GUI_RectsIntersect(pRect, &_Rect)) {
        Hide();
      }
    }
  }
}

void GUI_CURSOR_TempUnhide(const GUI_RECT* pRect) {
  if (_CursorOn) {
    if (_CursorDeActCnt==0) {
      if ((pRect == NULL) | GUI_RectsIntersect(pRect, &_Rect)) {
        Show();
      }
    }
  }
}


/*******************************************************************
*
*                  GUI_CURSOR_Clear
*
********************************************************************

Purpose:
  Clears cursor.
*/

void GUI_CURSOR_Clear(void) {
  GUI_LOCK();
  Hide();
  _CursorOn = 0;
  /* Set function pointer which window manager can use */
  GUI_CURSOR_pfTempHide   = NULL;
  GUI_CURSOR_pfTempUnhide = NULL;
  GUI_UNLOCK();
}

/*******************************************************************
*
*                  GUI_CURSOR_Show
*
********************************************************************

Purpose:
  Shows cursor.
*/

void GUI_CURSOR_Show(void) {
  GUI_LOCK();
  Hide();
  _CursorOn = 1;
  if (!_pBM) {
    GUI_CURSOR_Select(&GUI_MouseArrow);
  }
  /* Set function pointer which window manager can use */
  GUI_CURSOR_pfTempHide   = GUI_CURSOR_TempHide;
  GUI_CURSOR_pfTempUnhide = GUI_CURSOR_TempUnhide;
  GUI_UNLOCK();
}

/*******************************************************************
*
*                  GUI_CURSOR_SetPosition
*
********************************************************************

Purpose:
  Sets position of cursor.
*/

void GUI_CURSOR_SetPosition(int x, int y) {
  GUI_LOCK();
  if ((_Rect.x0 != x) | (_Rect.y0 != y)) {
    if (_CursorOn) {
      Hide();
    }
    _Rect.x0 = x;
    _Rect.y0 = y;
    _CalcRect();
    if (_CursorOn) {
      Show();
    }
  }
  GUI_UNLOCK();
}






#else

void GUICurs_C(void) {} /* avoid empty object files */

#endif   /* GUI_SUPPORT_CURSOR */








