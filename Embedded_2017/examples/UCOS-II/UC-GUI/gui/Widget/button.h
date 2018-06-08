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
File        : BUTTON.H
Purpose     : BUTTON public header file (API)
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef BUTTON_H
#define BUTTON_H

#include "WM.H"
#include "Dialog.h"      /* Req. for Create indirect data structure */

#if GUI_WINSUPPORT

/************************************************************
*
*       Defaults for configuration switches
*
*************************************************************

The following are defaults for config switches which affect the
interface specified in this module
*/
#ifndef BUTTON_SUPPORT_BITMAP_OFFSET
  #define BUTTON_SUPPORT_BITMAP_OFFSET 1
#endif
#ifndef BUTTON_SUPPORT_STREAMED_BITMAP
  #define BUTTON_SUPPORT_STREAMED_BITMAP 0
#endif

/************************************************************
*
*       Create flags
*/
/* For compatibility only ! */
#define BUTTON_CF_HIDE   WM_CF_HIDE
#define BUTTON_CF_SHOW   WM_CF_SHOW
#define BUTTON_CF_MEMDEV WM_CF_MEMDEV

/************************************************************
*
*       Messages
*/

/************************************************************
*
*       States
*/

#define BUTTON_STATE_FOCUS   (1<<0)
#define BUTTON_STATE_PRESSED (1<<1)
#define BUTTON_STATE_ACTIVE  (1<<2)
#define BUTTON_STATE_INACTIVE            0

/************************************************************
*
*       Types
*
*************************************************************
*/
typedef WM_HMEM BUTTON_Handle;

/************************************************************
*
*       Create function(s)

  Note: the parameters to a create function may vary.
         Some widgets may have multiple create functions
*/

BUTTON_Handle BUTTON_Create        (int x0, int y0, int xsize, int ysize, int ID, int Flags);
BUTTON_Handle BUTTON_CreateAsChild (int x0, int y0, int xsize, int ysize, WM_HWIN hParent, int Id, int Flags);
BUTTON_Handle BUTTON_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* pCallback);

/*********************************************************************
*
*       Standard member functions
*
**********************************************************************
*/

#define BUTTON_EnableMemdev(hObj)  WM_EnableMemdev(hObj)
#define BUTTON_DisableMemdev(hObj) WM_DisableMemdev(hObj)
#define BUTTON_Delete(hObj)        WM_DeleteWindow(hObj)
#define BUTTON_Paint(hObj)         WM_Paint(hObj)
#define BUTTON_Invalidate(hObj)    WM_InvalidateWindow(hObj)

/*********************************************************************
*
*                 Member functions, unconditional
*
**********************************************************************

*/

/* Methods changing properties */
void BUTTON_SetBitmap(BUTTON_Handle hObj, int Index, const GUI_BITMAP* pBitmap);
void BUTTON_SetBkColor(BUTTON_Handle hObj, int Index, GUI_COLOR color);
void BUTTON_SetFont(BUTTON_Handle hObj, const GUI_FONT* pfont);
void BUTTON_SetState(BUTTON_Handle hObj, int State);
void BUTTON_SetText     (BUTTON_Handle hObj, const char* s);
void BUTTON_SetTextColor(BUTTON_Handle hObj, int Index, GUI_COLOR color);

/*********************************************************************
*
*                 Member functions, conditional
*
**********************************************************************

*/
#if BUTTON_SUPPORT_BITMAP_OFFSET
  void BUTTON_SetBitmapEx(BUTTON_Handle hObj, int Index, const GUI_BITMAP* pBitmap, int x, int y);
#endif
#if BUTTON_SUPPORT_STREAMED_BITMAP
  void BUTTON_SetStreamedBitmap(BUTTON_Handle hObj, int Index, const GUI_BITMAP_STREAM* pBitmap);
#endif

/************************************************************
*
*       States
*/
#define BUTTON_STATE_HASFOCUS 0

#endif   /* BUTTON_H */
#endif   /* BUTTON_H */
