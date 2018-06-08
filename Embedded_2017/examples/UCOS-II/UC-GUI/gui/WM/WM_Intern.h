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
File        : WM_Intern.H
Purpose     : Windows manager internal include
----------------------------------------------------------------------
*/

#ifndef WM_INTERN_H            /* Make sure we only include it once */
#define WM_INTERN_H            /* Make sure we only include it once */

#include "WM.h"
#include "GUI_Protected.h"       /* For GUI_Context */

#if GUI_WINSUPPORT

typedef void WM_DELETE_WINDOW_HOOK( WM_HWIN hWin);
extern WM_DELETE_WINDOW_HOOK* WM__pfDeleteWindowHook;
extern U16 WM__CreateFlags;
extern GUI_COLOR WM__BkColor;
extern WM_HWIN WM__hCapture, WM__hWinFocus;
extern char WM__CaptureReleaseAuto;

/*
      *************************************************************
      *                                                           *
      *                 Module internals                          *
      *                                                           *
      *************************************************************

The following datastructure(s) and routines are mentioned in the
documentation and not explained at this point here in any detail,
as they are just needed internally to iterate in drawing routines
in order over all invalid rectangles.
*/

void    WM__Client2Screen(const WM_Obj* pWin, GUI_RECT *pRect);
void    WM__GetClientRectWin(WM_Obj* pWin, GUI_RECT* pRect);
int     WM__GetHasFocus(WM_HWIN hWin);
WM_HWIN WM__GetLastSibling(WM_HWIN hWin);
WM_HWIN WM__GetPrevSibling(WM_HWIN hWin);
int     WM__GetWindowSizeX(WM_Obj* pWin);
int     WM__GetWindowSizeY(WM_Obj* pWin);
void    WM__InvalidateAreaBelow(const GUI_RECT* pRect, WM_HWIN StopWin);
void    WM__InvalidateTransAreaAbove(const GUI_RECT* pRect, WM_HWIN StopWin);
int     WM__IntersectRect(GUI_RECT* pDest, const GUI_RECT* pr0, const GUI_RECT* pr1);
int     WM__IsWindow(WM_HWIN hWin);
void    WM__LeaveIVRSearch(void);
void    WM__MoveTo(WM_HWIN hWin, int x, int y);
void    WM__MoveBWin(WM_Obj* pWin, int dx, int dy);
void    WM__MoveWindow(WM_HWIN hWin, int dx, int dy);
int     WM__RectIsNZ(const GUI_RECT* pr);
void    WM__RemoveFromLinList(WM_HWIN hWin);
void    WM__Screen2Client(const WM_Obj* pWin, GUI_RECT *pRect);
void    WM__SendMsgNoData(WM_HWIN hWin, U8 MsgId);
void    WM__SendMessage(WM_HWIN hWin, WM_MESSAGE* pm);
void    WM__SendMessageNoPara(WM_HWIN hWin, int MsgId);
WM_HWIN WM__GetFirstSibling(WM_HWIN hWin);

#endif   /* GUI_WINSUPPORT */

#endif   /* WM_INTERN_H */
