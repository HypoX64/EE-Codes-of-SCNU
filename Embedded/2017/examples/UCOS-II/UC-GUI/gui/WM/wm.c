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
File        : WM.C
Purpose     : Windows manager core
----------------------------------------------------------------------
Version-Date---Author-Explanation
----------------------------------------------------------------------

3.00a   010621 RS     a) module accelerated by skipping parameter
                         to FindNext_IVR
3.00    010502 RS     a) WM module split up for library applications
                      b) Module dramatically accelerated (without
                         changes in the routine structure)
1.18    000909 RS     a) WM_CreateBWin does not activate the
                         new window unless specified via create flags
1.16a   000724 RS     a) Function WM_EnableMemdevRead added
1.16    000614 RS     a) Cleanup
                      b) Counter for invalid windows and
                         WM_GetNumInvalidWindows() added
1.14g   000522 RS     a) WM_ExecAll added
1.14f   000316 RS     a) Internal Create routine created in order to
                         handle creation of regular windows and
                         objects seperately (and correctly) in all
                         cases (by avoiding casts)
1.14e   000307 RS     a) WM_MoveTo added
1.14d   000224 RS     a) WM_CF_ACTIVATE flag now needed in order to
                         automatically activate a created window
1.14c   000209 RS     a) GUI_Clear eliminated in default callback for
                         default background window
1.14b   000125 RS     a) Bugfix for bug created in 1.14a
1.14a   000122 RS     a) WM_CreateObj: Change in order to avoid
                         compiler warning with IARs new frontend
1.14    999109 RS     a) Bugfix: Deleted window could still receive
                         up to 1 drawing message. Fixed. (->NextDrawWin)
                      b) WM_Obj now uses memory handle
                      c) WM_DefaultProc now handles WM_DELETE
                      d) Drawing area reduction for callbacks
                         to invalide area
                      e) WM_SetCallback added
                      f) Call to WM_Error if insufficient windows have
                         been configured
1.12h   000107 RS     a) WM_Sendmessage: unused local eliminated
                      b) WMALLOC_Init call eliminated
1.12g   991230 RS     a) Callback for background window defined
1.12f   991228 RS     a) Locking macros moved -> WM.H
1.12e   991208 RS     a) WM_DrawNext now saves the entire context, not
                         just the active window
1.12d   991204 RS     a) WM_GetBGndWin added
1.12c   991203 RS     a) WM_Init now creates default window
1.12b   991126 RS     a) Cleanup in order to avoid compiler warnings
1.12a   991112 RS     a) Invalidate now also invalidates any
                         transparent window on top of the invalidated
                         area
                      b) Internal changes in order to support
                         dynamic memory (using WM_ALLOC)
                      c) Additional ASSERTs inserted
1.12    991110 RS     a) Invalidate now also invalidates a window
                         below a transparent window
1.10c   991018 RS     a) WM_DrawNext:
                         NextDrawWin=WM_HWIN_NULL -> NextDrawWin==WM_HWIN_NULL
1.10b   991015 RS     a) WM_ValidateBWin corrected (Invalid
                         flag was never reset, leading to superfluos redraws)
                      b) WM_SetDefault(void) implemented
1.10a   991012 RS     a) Compile warnings eliminated
1.10    990918 RS     a) Objects for windows manager added:
                         WM_CreateObject, WM_DeleteObject
                      b) "Magic number" -1 eliminated
                      c) static routines put on top of file
                      d) Locking added (WM_LOCK), ensuring thread
                         safety of all routines
                      e) Window marked as valid only if a callback
                         exists, allowing mixed callback/non callback
                         modes for different windows
1.08.02 990827 RS     a) Optimization bug in WM_SetHasTrans
                         fixed
1.08.01 990826 RS     a) Transparent windows can no longer obstruct
                      an area of a window below in Z-direction
                      (in FindNext_IVR) for correct handling of
                      transparent windows
1.08.00 990823 RS     a) WM__GetOrgX -> WM_GetOrgX
                         WM__GetOrgY -> WM_GetOrgY
                      b) Clearing memory in WM_Init
1.07.01 990730 RS     a) In WM_DrawNext() add. condition added to make
                      sure that loop does not iterate using
                      -1 (end-of-list) as index
1.07    990720 RS     a) New switch: WM_SUPPORT_OBSTRUCT, def. 1
1.06    990504 BB     functions WM_GetWinSizeX() and WM_GetWinSizeY()
                      added.
1.05    990423 RS     a) Prototype for WM_CreateBWin changed,
                      parameter WM_MESSAGE* is no longer const
                      (Causing some other changes reg. const)
                      b) WM_ShowBWin WM_HideBWin tested in simulator
1.04    990417 RS     a) DrawNext bug fixed: It had passed the
                      entire WIndow-Rectangle instead of just
                      the InvalidRectangle with the WM_PAINT
                      command
1.03    990401 RS     a) Implemented the following functions
                      WM_SetHasTrans()
                      WM_ClrHasTrans()
                      WM_GetHasTrans()
                      WM_HideBWin()
                      WM_ShowBWin()
                      WM_ValidateBWin()
                      WM_GetActiveBWin()
1.02    990315 RS     a) Windows stack organisation routines cleaned
                      up, resulting in more efficient code
1.01    990314 RS     a) Invalidation and IVR calculation optimized
                      b) Windows which are on top of a window causing
                      invalidation are no longer affected
1.00    990310 RS     Moving and resizing tested in simulation
0.99    990309 RS     All routines implemented, moving & resizing
                      need to be tested under different circumstances.
0.50    990308 RS     Core of WM works (Calculation and iteration over
                      IVRs). Side routines like moving windows and the
                      corresponding message handling missing.
                      There is now a clear seperation between the LCD
                      and GL layers and WM.
0.01    990301 RS     Incomplete version, for BB to check
----------------------------------------------------------------------
Known problems:
None.
----------------------------------------------------------------------
Open issues:
None.
----------------------------------------------------------------------
Todo:
Nothing.
*/


#include <stddef.h>           /* needed for definition of NULL */
#include <string.h>           /* required for memset */

#define WM_C
#include "WM_Intern.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */


/******************************************************************
*
*              Config defaults
*
*******************************************************************
*/

/* This is for tests only. It will fill the invalid area of a window.
   Can be used for debugging. */

#ifndef WM_SHOW_INVALID
  #define WM_SHOW_INVALID 0
#endif

/*******************************************************************
*
*                 Macros for internal use
*
********************************************************************
*/

#define ASSIGN_IF_LESS(v0,v1) if (v1<v0) v0=v1

/******************************************************************
*
*              Local typedefs
*
*******************************************************************
*/

typedef struct {
  GUI_RECT ClientRect;
  GUI_RECT CurRect;
  int Cnt;
  int EntranceCnt;
} WM_IVR_CONTEXT;

/******************************************************************
*
*              WM_ global data
*
*******************************************************************
*/

U8                     WM_IsActive;
U16                    WM__CreateFlags;
WM_DELETE_WINDOW_HOOK* WM__pfDeleteWindowHook;
GUI_COLOR              WM__BkColor = GUI_INVALID_COLOR;
WM_HWIN                WM__hCapture, WM__hWinFocus;
char                   WM__CaptureReleaseAuto;

/******************************************************************
*
*              Static data
*
*******************************************************************
*/

static WM_HWIN        NextDrawWin;
static U8             IsInCallback;
static WM_IVR_CONTEXT ClipContext;
static char           _IsInited;

/*******************************************************************
*
*       Static routines
*
********************************************************************
*/


/*******************************************************************
*
*       _ClipAtParentBorders

  Iterates over all its ancestors and intersects all rectangles to
  find out which part is actually visible.
  Reduces the rectangle to the visible area.
*/
void _ClipAtParentBorders(GUI_RECT* pRect, WM_Obj* pWin) {
  WM_HWIN hWin;
  hWin = pWin->hParent;
  while (hWin) {
    pWin = WM_H2P(hWin);
    GUI__IntersectRect(pRect, &pWin->Rect);
    hWin = pWin->hParent;
  }
}

/*******************************************************************
*
*

  When drawing, we have to start at the bottom window !
*/

static void ResetNextDrawWin(void) {
  NextDrawWin = WM_HWIN_NULL;
}


/*******************************************************************
*
*       _AddChild
*/
void _AddChild(WM_HWIN hParent, WM_HWIN hChild, int OnTop) {
  WM_Obj* pChild;
  WM_Obj* pParent;
  WM_Obj* pi;
  WM_HWIN hi;
  if (hParent) {
    pParent = WM_H2P(hParent);
    pChild  = WM_H2P(hChild);
    hi = pParent->hFirstChild;
    if (hi == 0) {   /* No child yet ... Makes things easy ! */
      pParent->hFirstChild = hChild;
        return;                         /* Early out ... We are done */
    }
    if (!OnTop) {
      pi = WM_H2P(hi);
      if (pi->Status & WM_SF_STAYONTOP) {
        pChild->hNext = hi;
        pParent->hFirstChild = hChild;
        return;                         /* Early out ... We are done */
      }
    }
    /* put if at the end of the list or after the last non "STAY-ON-TOP" child */
    do {
      WM_Obj* pNext;
      WM_HWIN hNext;
      pi = WM_H2P(hi);
      if ((hNext = pi->hNext) == 0) {
        pi->hNext = hChild;
        break;
      }
      if (!OnTop) {
        pNext = WM_H2P(hNext);
        if (pNext->Status & WM_SF_STAYONTOP) {
          pi->hNext = hChild;
          pChild->hNext = hNext;
          break;
        }
      }
      hi = hNext;
    }  while (1);
  }
}

/*******************************************************************
*
*
*/
static void _DeleteAllChildren(WM_HWIN hChild) {
  while (hChild) {
    WM_Obj* pChild = WM_H2P(hChild);
    WM_HWIN hNext = pChild->hNext;
    WM_DeleteWindow(hChild);
    hChild = hNext;
  }
}

/*******************************************************************
*
*
*/
static void _DeleteInSiblingList(WM_HWIN hWin) {
  WM_Obj* pWin;
  WM_Obj* pParent;
  WM_Obj* pi;
  WM_HWIN hParent;
  WM_HWIN hi;
  pWin = WM_H2P(hWin);
  if (pWin->hParent) {
    hParent = pWin->hParent;
    pParent = WM_H2P(hParent);
    hi = pParent->hFirstChild;
    if (hi == hWin) {
      pi = WM_H2P(hi);
      pParent->hFirstChild = pi->hNext;
    } else {
      while (hi) {
        pi = WM_H2P(hi);
        if (pi->hNext == hWin) {
          pi->hNext = pWin->hNext;
          return;
        }
        hi = pi->hNext;
      }
    }
  }
}


/*********************************************************************
*
*             Module internal routines
*
**********************************************************************
*/

void WM__Client2Screen(const WM_Obj* pWin, GUI_RECT *pRect) {
  GUI_MoveRect(pRect, pWin->Rect.x0, pWin->Rect.y0);
}

int WM__IsWindow(WM_HWIN hWin) {
  WM_HWIN iWin;
  int r = 0;
  for (iWin = WM__FirstWin; iWin; iWin = WM_H2P(iWin)->hNextLin) {
    if (iWin == hWin) {
      r = 1;
      break;
    }
  }
  return r;
}


/*******************************************************************
*
*
*/
void WM__RemoveFromLinList(WM_HWIN hWin) {
  WM_Obj* piWin;
  WM_HWIN hiWin, hNext;
  for (hiWin = WM__FirstWin; hiWin; ) {
    piWin = WM_H2P(hiWin);
    hNext = piWin->hNextLin;
    if (hNext == hWin) {
      piWin->hNextLin = WM_H2P(hWin)->hNextLin;
      break;
    }
    hiWin = hNext;
  }
}


/*******************************************************************
*
*
*/
void _AddToLinList(WM_HWIN hNew) {
  WM_Obj* pFirst;
  WM_Obj* pNew;
  if (WM__FirstWin) {
    pFirst = WM_H2P(WM__FirstWin);
    pNew   = WM_H2P(hNew);
    pNew->hNextLin = pFirst->hNextLin;
    pFirst->hNextLin = hNew;
  } else {
    WM__FirstWin = hNew;
  }
}


/*********************************************************************
   Check if the rectangle has some content (is non-zero)
   Returns 0 if the Rectangle has no content, else 1.
*/
int WM__RectIsNZ(const GUI_RECT* pr) {
  if (pr->x0 > pr->x1)
    return 0;
  if (pr->y0 > pr->y1)
    return 0;
  return 1;
}


/*
  ********************************************************************
  *                                                                  *
  *                    Sending messages                              *
  *                                                                  *
  ********************************************************************
*/


void WM_SendMessage(WM_HWIN hWin, WM_MESSAGE* pMsg) {
  WM_Obj* pWin;
  WM_LOCK();
  if (hWin) {
    pWin = WM_H2P(hWin);
  /* Do some checking to avoid program crashes due to user
     programming errors */
    #if GUI_DEBUG_LEVEL > 0
      if (!pWin->Status)
        goto Done;
    #endif
    if (pWin->cb != NULL) {
      pMsg->hWin = hWin;
      IsInCallback = 1;
      (*pWin->cb)(pMsg);
      IsInCallback = 0;
    }
  }
  #if GUI_DEBUG_LEVEL > 0
Done:
  #endif
  WM_UNLOCK();
}

/*******************************************************************
*
*
*/
void WM__SendMsgNoData(WM_HWIN hWin, U8 MsgId) {
  WM_MESSAGE Msg;
  Msg.hWin  = hWin;
  Msg.MsgId = MsgId;
  WM_SendMessage(hWin, &Msg);
}



/* Get client rectangle in windows coordinates. This means that the
  upper left corner is always at (0,0). */
void WM__GetClientRectWin(WM_Obj* pWin, GUI_RECT* pRect) {
  pRect->x0 = pRect->y0 = 0;
  pRect->x1 = pWin->Rect.x1 - pWin->Rect.x0;
  pRect->y1 = pWin->Rect.y1 - pWin->Rect.y0;
}


static void WM__GetInvalidRectAbs(WM_Obj* pWin, GUI_RECT* pRect) {
  *pRect = pWin->InvalidRect;
  GUI_MoveRect (pRect, pWin->Rect.x0, pWin->Rect.y0);
}


/*
          *****************************************************************
          *                                                               *
          *              Invalidation functions                           *
          *                                                               *
          *****************************************************************
*/

/* Invalidate, using window coordinates */
static void WM_InvalidateBWin1(WM_HWIN hWin, const GUI_RECT*pRect) {
  GUI_RECT r;
  WM_Obj* pWin = WM_H2P(hWin);
  WM__GetClientRectWin(pWin, &r);
  if (pRect)
    GUI__IntersectRect(&r, pRect);
  if (WM__RectIsNZ(&r)) {
    if (pWin->Status & WM_SF_INVALID) {
      GUI_MergeRect(&pWin->InvalidRect, &pWin->InvalidRect, &r);
    } else {
      pWin->InvalidRect = r;
      pWin->Status |= WM_SF_INVALID;
      WM__NumInvalidWindows++;
      /* Debug code: shows invalid areas */
      #if (WM_SHOW_INVALID)
      {
        GUI_CONTEXT Context = GUI_Context;
        WM_SelectWindow(hWin);
        GUI_SetBkColor(GUI_GREEN);
        GUI_ClearRect(r.x0, r.y0, r.x1, r.y1);
        GUI_Context = Context;
      }
      #endif


    }
  }
}

/* Invalidate, using desktop coordinates (only this window,
   not the ones below !!!)
*/
static void WM_InvalidateBWin1Abs(WM_HWIN hWin, const GUI_RECT*pRect) {
  GUI_RECT r = *pRect;
  WM_LOCK();
  GUI_MoveRect(&r, -WM_H2P(hWin)->Rect.x0, -WM_H2P(hWin)->Rect.y0);
  WM_InvalidateBWin1(hWin, &r);
  WM_UNLOCK();
}



/*
  Invalidate a certain section of the display. One main reason for this is
  that a window has been moved or destroyed.
  The following windows are affected:
  * windows below the window creating the invalidation.
  * transparent windows located above
  The coordinates given are absolute coordinates (desktop coordinates)
*/
void WM__InvalidateAreaBelow(const GUI_RECT* pRect, WM_HWIN StopWin) {
  WM_HWIN   iWin, iNext;
  /* Iterate over windows below StopWin */
  for (iWin = WM__FirstWin; iWin!=StopWin; iWin = iNext) {
    GUI_RECT r = *pRect;
    WM_Obj* pWin = WM_H2P(iWin);
    iNext = pWin->hNextLin;
    if (GUI__IntersectRects(&r, &r, &pWin->Rect)) {
      WM_InvalidateBWin1Abs (iWin, &r);
    }
  };
}

/*
  Invalidate any transparent window above the given area
*/
void WM__InvalidateTransAreaAbove(const GUI_RECT* pRect, WM_HWIN StopWin) {
  GUI_USE_PARA(pRect);
  GUI_USE_PARA(StopWin);
#if 0
  WM_HWIN   iWin;
  /* Iterate over windows below StopWin */
  for (iWin = StopWin; iWin!=WM_HWIN_NULL; iWin = WM_H2P(iWin)->Next) {
    WM_Obj *pWin = WM_H2P(iWin);
    if (pWin->Status & WM_SF_HASTRANS) {
      GUI_RECT r = *pRect;
      if (GUI__IntersectRects(&r, &r, &WM_H2P(iWin)->Rect)) {
        WM_InvalidateBWin1Abs (iWin, &r);
      }
    }
  }
#endif
}


/*
          *****************************************************************
          *                                                               *
          *              Invalidation functions                           *
          *                                                               *
          *****************************************************************
*/

/* Invalidate a section of the window. The optional rectangle
   contains client coordinates, which are independent of the
   position of the window on the logical desktop area.
*/


void WM_InvalidateRect(WM_HWIN hWin, const GUI_RECT*pRect) {
  GUI_RECT r;
  WM_Obj* pWin;
  WM_LOCK();
  pWin = WM_H2P(hWin);
  WM__GetClientRectWin(pWin, &r);
  if (pRect) {
    GUI__IntersectRect(&r, pRect);
  }
  WM_InvalidateBWin1(hWin, &r);
/* Convert into absolute coordinates ... */
  GUI_MoveRect (&r, pWin->Rect.x0, pWin->Rect.y0);
/* Make sure windows below are invalidated if this one is transparent */
  if (pWin->Status & WM_SF_HASTRANS) {
    ResetNextDrawWin();
    WM__InvalidateAreaBelow(&r, hWin);
  }
/* Invalidate the transparent ones above */
  WM__InvalidateTransAreaAbove(&r,hWin);
  WM_UNLOCK();
}

void WM_InvalidateWindow(WM_HWIN hWin) {
  WM_InvalidateRect(hWin, NULL);
}

/* Invalidate, using desktop coordinates */
void WM_InvalidateBWinAbs(WM_HWIN hWin, const GUI_RECT*pRect) {
  GUI_RECT r = *pRect;
  WM_LOCK();
  GUI_MoveRect(&r, -WM_H2P(hWin)->Rect.x0, -WM_H2P(hWin)->Rect.y0);
  WM_InvalidateRect(hWin, &r);
  WM_UNLOCK();
}


/*
  Invalidate a certain section of the display. One main reason for this is
  that the top window has been moved or destroyed.
  The coordinates given are absolute coordinates (desktop coordinates)
*/
void WM_InvalidateArea(GUI_RECT* pRect) {
  WM_HWIN   iWin;
  WM_LOCK();
  /* Iterate over all windows */
  for (iWin=WM__FirstWin; iWin !=0; ) {
    WM_Obj* pWin = WM_H2P(iWin);
    GUI_RECT r = *pRect;
    GUI__IntersectRect(&r, &pWin->Rect);
    /* Calculate which area is actually visible by subtracting the
       windows which are on top of this one */
    WM_InvalidateBWinAbs (iWin, &r);
    iWin = pWin->hNextLin;
  }
  WM_UNLOCK();
}


/*
  ********************************************************************
  *                                                                  *
  *              manage windows stack                                *
  *                                                                  *
  ********************************************************************
*/


/* Return index (handle) of the window which is bottom of stack.
   Note that in the current implementation, this is always
   window 0.
*/
WM_HWIN WM_GetDesktopWindow(void) {
  return WM__FirstWin;
}

/*
  ********************************************************************
  *
  *              Create window (as child)
  *
  ********************************************************************
*/

WM_HWIN WM_CreateWindowAsChild(
                    int x0, int y0, int width, int height
                   ,WM_HWIN hWinParent
                   ,U16 Style
                   ,WM_CALLBACK* cb
                   ,int NumExtraBytes)
{
  WM_Obj* pWin;
  WM_HWIN hWin;
  WM_LOCK();
  Style |= WM__CreateFlags;
  /* Get Parent info */
  if (!hWinParent) {
    if (WM__NumWindows) {
      hWinParent = WM_HBKWIN;
    }
  }
  if (hWinParent) {
    GUI_RECT Rect;
    WM_MESSAGE Msg;
    Msg.MsgId = WM_GETCLIENTRECT_ABS;
    Msg.Data.p = &Rect;
    WM_SendMessage(hWinParent, &Msg);
    x0 += Rect.x0;
    y0 += Rect.y0;
    if (width==0)
      width = Rect.x1-Rect.x0+1;
    if (height==0)
      height = Rect.y1-Rect.y0+1;
  }
  if ((hWin = (WM_HWIN) WM_ALLOC(NumExtraBytes+sizeof(WM_Obj))) == 0) {
    GUI_DEBUG_ERROROUT("WM_CreateWindow: No memory to create window");
  } else {
    WM__NumWindows++;
    pWin = WM_H2P(hWin);
    memset (pWin,   0, sizeof(WM_Obj));        /* erase this data structure
           The explicit zero-init is no longer needed since the entire data structure
           is already zeroed. The advantage is that it reduces program size.
           */
    pWin->Rect.x0 = x0;
    pWin->Rect.y0 = y0;
    pWin->Rect.x1 = x0+width-1;
    pWin->Rect.y1 = y0+height-1;
    pWin->Status = WM_SF_INUSE;     /* Mark window as in use */
    pWin->cb = cb;
    /* Add to linked lists */
    pWin->hParent = hWinParent;
    _AddChild(hWinParent, hWin, Style & WM_CF_STAYONTOP);
    _AddToLinList(hWin);
  /* Put Window on top (or bottom) of windows stack */
    if (Style & WM_CF_ACTIVATE /*| (cb==NULL)*/) {
      WM_SelectWindow(hWin);  /* This is not needed
                                 if callbacks are being used, but it
                                 does not cost a lot and makes life
                                 easier ... */
    }
  /* Mark client area as invalid */
    WM__SendMsgNoData(hWin, WM_CREATE);
  /* Handle the Style flags, one at a time */
    if (Style & WM_CF_SHOW) {
      WM_ShowWindow(hWin);
    }
  /* Hide if parent is not visible */
    if (hWinParent) {
      WM_Obj* pWinParent = WM_H2P(hWinParent);
      if (!(pWinParent->Status & WM_SF_ISVIS)) {
        WM_HideWindow(hWin);
      }
    }
    /* Copy the flags which can simply be accepted */
    pWin->Status |= (Style & (WM_SF_MEMDEV|WM_SF_STAYONTOP|WM_SF_HASTRANS));
  }
  WM_UNLOCK();
  return hWin;
}

WM_HWIN WM_CreateWindow(int x0, int y0, int width, int height, U16 Style, WM_CALLBACK* cb, int NumExtraBytes) {
  return WM_CreateWindowAsChild(x0,y0,width,height, 0 /* No parent */,  Style, cb, NumExtraBytes);
}



/****************************************************************
*
*          Delete window
*
*****************************************************************

*/

void WM_DeleteWindow (WM_HWIN Win) {
  WM_Obj* pWin;
  if (!Win)
    return;
  WM_LOCK();
  if (WM__IsWindow(Win)) {
    pWin = WM_H2P(Win);
    ResetNextDrawWin();              /* Make sure the window will no longer receive drawing messages */
  /* Make sure that focus is set to an existing window */
    if (WM__hWinFocus == Win) {
      WM__hWinFocus = 0;
    }
    if (Win == WM__hCapture) {
      WM__hCapture = 0;
    }
  /* Delete all children */
    _DeleteAllChildren(pWin->hFirstChild);
    _DeleteInSiblingList(Win);
  /* Send WM_DELETE message to window in order to inform window itself */
    WM__SendMsgNoData(Win, WM_DELETE);     /* tell window about it */
    /* Inform other modules if necessary */
    if (WM__pfDeleteWindowHook) {
      (*WM__pfDeleteWindowHook)(Win);
    }
  /* Remove window from window stack */
    if (pWin->Status & WM_SF_INVALID) {
      WM__NumInvalidWindows--;
    }
    WM__RemoveFromLinList(Win);
  /* Clear area used by this window */
    WM_InvalidateArea(&pWin->Rect);
  /* Free window memory */
    WM__NumWindows--;
    WM_FREE(Win);
  /* Select a valid window */
    WM_SelectWindow(WM__FirstWin);
  } else {
    GUI_DEBUG_WARN("WM_DeleteWindow: Invalid handle");
  }
  WM_UNLOCK();
}


void WM__SetMaxClipRect(const WM_Obj* pWin) {
  WM_LOCK();
  LCD_SetClipRectEx(&pWin->Rect);
  WM_UNLOCK();
}

/****************************************************************
*
*              WM_SelectWindow
*
*****************************************************************

Sets the active Window. The active Window is the one that is used for all
drawing (and text) operations.
*/

WM_HWIN WM_SelectWindow(WM_HWIN  hWin) {
  WM_HWIN hWinPrev;
  WM_LOCK();
  hWinPrev = GUI_Context.hAWin;
  if (hWin == 0) {
    hWin = WM__FirstWin;
  }
  if (!(WM_H2P(hWin)->Status & WM_SF_INUSE)) {
    GUI_DEBUG_ERROROUT1("Selecting invalid window", hWin);
    hWin=0;
  }
  /* Select new window */
  GUI_Context.hAWin = hWin;
  WM__SetMaxClipRect(WM_H2P(hWin));
  WM_UNLOCK();
  return hWinPrev;
}


WM_HWIN WM_GetActiveWindow(void) {
  return GUI_Context.hAWin;
}



/*
  ********************************************************************
  *                                                                  *
  *                 Show / hide window                               *
  *                                                                  *
  ********************************************************************
*/
void WM_ShowWindow   (WM_HWIN hWin) {
  WM_Obj *pWin;
  WM_LOCK();
  pWin = WM_H2P(hWin);  
  /* First check if this is necessary at all */
  if ((pWin->Status&WM_SF_ISVIS)) {
    WM_UNLOCK();
    return;
  }
  /* Set Visibility flag */
  pWin->Status |= WM_SF_ISVIS;
  /* Mark content as invalid */
  WM_InvalidateWindow(hWin);
  WM_UNLOCK();
}



/*
          *****************************************************************
          *                                                               *
          *                    GetOrg                                     *
          *                                                               *
          *****************************************************************

These routines return the offset of the client area in absolute coordinates.
They are used to convert window coordinates into absolute coordinates and are
used in the clipping libraries (CL_).
*/


int WM__GetOrgX(void) {
  return WM_H2P(GUI_Context.hAWin)->Rect.x0;
}

int WM__GetOrgY(void) {
  return WM_H2P(GUI_Context.hAWin)->Rect.y0;
}


/*********************************************************************
*
*           IVR calculation

IVRs are invalid rectangles. When redrawing, only the portion of the
window which is
  a) within the window-rectangle
  b) not covered by an other window
  c) marked as invalid
  is actually redrawn. Unfortunately, this section is not always
  rectangular. If the window is partially covered by an other window,
  it consists of the sum of multiple rectangles. In all drawing
  operations, we have to iterate over every one of these rectangles in
  order to make sure the window is drawn completly.
Function works as follows:
  STEP 1: - Set upper left coordinates to next pixel. If end of line (right border), goto next line -> (r.x0, r.y0)
  STEP 2: - Check if we are done, return if we are.
  STEP 3: - If we are at the left border, find max. heigtht (r.y1) by iterating over windows above
  STEP 4: - Find x0 for the given y0, y1 by iterating over windows above
  STEP 5: - If r.x0 out of right border, this stripe is done. Set next stripe and goto STEP 2
  STEP 6: - Find r.x1. We have to Iterate over all windows which are above
*/



#if WM_SUPPORT_OBSTRUCT
static int FindNext_IVR(void) {
  int hParent;
  int iWin;
  GUI_RECT r;
  U8 Status;
  WM_Obj* pWin;
  WM_Obj* pAWin;
  WM_Obj* pParent;
  r = ClipContext.CurRect;  /* temps  so we do not have to work with pointers too much */
  /*
     STEP 1:
       Set the next position which could be part of the next IVR
       This will be the first unhandle pixel in reading order, i.e. next one to the right
       or next one down if we are at the right border.
  */
  if (ClipContext.Cnt == 0) {       /* First IVR starts in upper left */
    r.x0 = ClipContext.ClientRect.x0;
    r.y0 = ClipContext.ClientRect.y0;
  } else {
    r.x0 = ClipContext.CurRect.x1+1;
    r.y0 = ClipContext.CurRect.y0;
    if (r.x0 > ClipContext.ClientRect.x1) {
NextStripe:  /* go down to next stripe */
      r.x0 = ClipContext.ClientRect.x0;
      r.y0 = ClipContext.CurRect.y1+1;
    }
  }
  /*
     STEP 2:
       Check if we are done completely.
  */
  if (r.y0 >ClipContext.ClientRect.y1)
    return 0;
  /* STEP 3:
       Find out the max. height (r.y1) if we are at the left border.
       Since we are using the same height for all IVRs at the same y0,
       we do this only for the leftmost one.
  */
  pAWin = WM_H2P(GUI_Context.hAWin);
  if (r.x0 == ClipContext.ClientRect.x0) {
    r.y1 = ClipContext.ClientRect.y1;
    r.x1 = ClipContext.ClientRect.x1;
    /* Iterate over all windows which are above */
    /* Check all siblings above (Iterate over Parents and top siblings (hNext) */
    for (hParent = GUI_Context.hAWin; hParent; hParent = pParent->hParent) {
      pParent = WM_H2P(hParent);
      for (iWin= pParent->hNext; iWin !=0; iWin = pWin->hNext) { 
        Status = (pWin = WM_H2P(iWin))->Status;
        /* Check if this window affects us at all */    
        if ((Status & WM_SF_ISVIS)  && (!(Status & WM_SF_HASTRANS)) && GUI_RectsIntersect(&r, &pWin->Rect)) {
          if (pWin->Rect.y0 > r.y0) {
            ASSIGN_IF_LESS(r.y1, pWin->Rect.y0-1);      /* Check upper border of window */
          } else {
            ASSIGN_IF_LESS(r.y1, pWin->Rect.y1);        /* Check lower border of window */
          }
        }
      }
    }
    /* Check all children */
    for (iWin= pAWin->hFirstChild; iWin !=0; iWin = pWin->hNext) { 
      Status = (pWin = WM_H2P(iWin))->Status;
      /* Check if this window affects us at all */    
      if ((Status & WM_SF_ISVIS)  && (!(Status & WM_SF_HASTRANS)) && GUI_RectsIntersect(&r, &pWin->Rect)) {
        if (pWin->Rect.y0 > r.y0) {
          ASSIGN_IF_LESS(r.y1, pWin->Rect.y0-1);      /* Check upper border of window */
        } else {
          ASSIGN_IF_LESS(r.y1, pWin->Rect.y1);        /* Check lower border of window */
        }
      }
    }
  }
  /* 
    STEP 4
      Find out x0 for the given y0, y1 by iterating over windows above.
      if we find one that intersects, adjust x0 to the right.
  */
Find_x0:
  r.x1 = r.x0;
  /* Iterate over all windows which are above */
  /* Check all siblings above */
    for (hParent = GUI_Context.hAWin; hParent; hParent = pParent->hParent) {
    pParent = WM_H2P(hParent);
    for (iWin= pParent->hNext; iWin !=0; iWin = pWin->hNext) { 
      Status = (pWin = WM_H2P(iWin))->Status;
      if ( (Status & WM_SF_ISVIS) && (!(Status & WM_SF_HASTRANS)) && GUI_RectsIntersect(&r, &pWin->Rect)) {     /* Check if this window affects us at all */
        r.x0 = pWin->Rect.x1+1;
        goto Find_x0;
      }
    }
  }
  /* Check all children */
  for (iWin= pAWin->hFirstChild; iWin !=0; iWin = pWin->hNext) { 
    Status = (pWin = WM_H2P(iWin))->Status;
    if ( (Status & WM_SF_ISVIS) && (!(Status & WM_SF_HASTRANS)) && GUI_RectsIntersect(&r, &pWin->Rect)) {     /* Check if this window affects us at all */
      r.x0 = pWin->Rect.x1+1;
      goto Find_x0;
    }
  }
  /* 
   STEP 5:
     If r.x0 out of right border, this stripe is done. Set next stripe and goto STEP 2
     Find out x1 for the given x0, y0, y1
  */
  r.x1 = ClipContext.ClientRect.x1;
  if (r.x1 < r.x0) {/* horizontal border reached ? */
    ClipContext.CurRect = r;
    goto NextStripe;
  }    
  /* 
   STEP 6:
     Find r.x1. We have to Iterate over all windows which are above
  */
  /* Check all siblings above (Iterate over Parents and top siblings (hNext) */
  for (hParent = GUI_Context.hAWin; hParent; hParent = pParent->hParent) {
    pParent = WM_H2P(hParent);
    for (iWin= pParent->hNext; iWin !=0; iWin = pWin->hNext) { 
      Status = (pWin = WM_H2P(iWin))->Status;
      if (    (Status & WM_SF_ISVIS) && (!(Status & WM_SF_HASTRANS)) && GUI_RectsIntersect(&r, &pWin->Rect)) {     /* Check if this window affects us at all */
        r.x1 = pWin->Rect.x0-1;    
      }
    }
  }
  /* Check all children */
  for (iWin= pAWin->hFirstChild; iWin !=0; iWin = pWin->hNext) { 
    Status = (pWin = WM_H2P(iWin))->Status;
    if (    (Status & WM_SF_ISVIS) && (!(Status & WM_SF_HASTRANS)) && GUI_RectsIntersect(&r, &pWin->Rect)) {     /* Check if this window affects us at all */
      r.x1 = pWin->Rect.x0-1;    
    }
  }
  /* We are done. Return the rectangle we found in the ClipContext. */
  if (ClipContext.Cnt >200) {
    return 0;  /* error !!! This should not happen !*/
  }
  ClipContext.CurRect = r;
  return 1;  /* IVR is valid ! */
}

#else

static int FindNext_IVR(void) {
  if (ClipContext.Cnt ==0) {
    ClipContext.CurRect = GUI_Context.pAWin->Rect;
    return 1;  /* IVR is valid ! */
  }
  return 0;  /* Nothing left to draw */
}
#endif



/*********************************************************************
*
*              Get next IVR

  Sets the next clipping rectangle. If a valid one has
  been found (and set), 1 is returned in order to indicate
  that the drawing operation needs to be executed.
  Returning 0 signals that we have iterated over all
  rectangles.

  Returns: 0 if no valid rectangle is found
           1 if rectangle has been found
*/

int  WM__GetNextIVR   (void) {
  #if GUI_SUPPORT_CURSOR
    static char _CursorHidden;
  #endif
  /* If WM is not active, we have no rectangles to return */
  if (WM_IsActive==0)
    return 0;
  if (ClipContext.EntranceCnt > 1) {
    ClipContext.EntranceCnt--;
    return 0;
  }
  #if GUI_SUPPORT_CURSOR
    if (_CursorHidden) {
      _CursorHidden = 0;
      (*GUI_CURSOR_pfTempUnhide) ( &ClipContext.CurRect);
    }
  #endif
  ++ClipContext.Cnt;
  /* Find next rectangle and use it as ClipRect */
  if (!FindNext_IVR()) {
    ClipContext.EntranceCnt--;  /* This search is over ! */
    return 0;        /* Could not find an other one ! */
  }
  /* Hide cursor if necessary */
  LCD_SetClipRectEx(&ClipContext.CurRect);
  #if GUI_SUPPORT_CURSOR
    if (GUI_CURSOR_pfTempHide) {
      _CursorHidden = 1;
      (*GUI_CURSOR_pfTempHide) ( &ClipContext.CurRect);
    }
  #endif
  return 1;
}



/*********************************************************************
*
*              Init IVR  search

  This routine is called from the clipping level
  (the WM_ITERATE_START macro) when starting an iteration over the
  visible rectangles.

  Return value:
    0 : There is no valid rectangle (nothing to do ...)
    1 : There is a valid rectangle
*/


int WM__InitIVRSearch(const GUI_RECT* pMaxRect) {
  GUI_RECT r;
  WM_Obj* pAWin;
   /* If WM is not active -> nothing to do, leave cliprect alone */
  if (WM_IsActive==0)
    return 1;            
  /* If we entered multiple times, leave Cliprect alone */
  if (++ClipContext.EntranceCnt > 1)
    return 1;
  pAWin = WM_H2P(GUI_Context.hAWin);
  ClipContext.Cnt        = -1;
 /* When using callback mechanism, it is legal to reduce drawing
    area to the invalid area ! */
  if (IsInCallback) {
    WM__GetInvalidRectAbs(pAWin, &r);
  } else {  /* Not using callback mechanism, therefor allow entire rectangle */
    if (pAWin->Status & WM_SF_ISVIS) {
      r = pAWin->Rect;
    } else {
      --ClipContext.EntranceCnt;
      return 0;  /* window is not even visible ! */
    }
  }
  /* If the drawing routine has specified a rectangle, use it to reduce the rectangle */
  if (pMaxRect) {
    GUI__IntersectRect(&r, pMaxRect);
  }
  /* If user has reduced the cliprect size, reduce the rectangle */
  if (GUI_Context.WM__pUserClipRect) {
    GUI_RECT rUser = *(GUI_Context.WM__pUserClipRect);
    WM__Client2Screen(pAWin, &rUser);
    GUI__IntersectRect(&r, &rUser);
  }
  /* Iterate over all ancestors and clip at their borders */
  _ClipAtParentBorders(&r, pAWin);
  /* Store the rectangle and find the first rectangle of the area */
  ClipContext.ClientRect = r;
  return WM__GetNextIVR();
}


/*
          ********************************************
          *                                          *
          *       Set default                        *
          *                                          *
          ********************************************

  This routine sets the defaults for WM and the layers below.
  It is used before a drawing routine is called in order to
  make sure that defaults are set (in case the default settings
  had been altered before by the application)
*/
void WM_SetDefault(void) {
  GL_SetDefault();
  GUI_Context.WM__pUserClipRect = NULL;   /* No add. clipping */
}

/*
  ********************************************
  *
  *        Callback for Paint message
  *
  ********************************************

  This callback is used by the window manger in conjunction with banding
  memory devices. A pointer to this routine is given to the banding memory device.
  This callback in turn will send the paint message to the window.
*/
#if GUI_SUPPORT_MEMDEV

static void cbPaint(void* pMsg) {
  WM_SendMessage(((WM_MESSAGE*)pMsg)->hWin, (WM_MESSAGE*) pMsg);
}

#endif

/*
          ********************************************
          *                                          *
          *       Draw next window                   *
          *                                          *
          ********************************************
*/


static void _DrawNext(void) {
  int UpdateRem = 1;
  WM_HWIN iWin = (NextDrawWin == WM_HWIN_NULL) ? WM__FirstWin : NextDrawWin;
  GUI_CONTEXT ContextOld;
  GUI_SaveContext(&ContextOld);
  /* Make sure the next window to redraw is valid */
  for (; (iWin!=WM_HWIN_NULL) && UpdateRem; ) {
    WM_Obj* pWin = WM_H2P(iWin);
    if (pWin->Status & WM_SF_INVALID) {
      U8 Status = (pWin->Status &=  ~WM_SF_INVALID); /* Clear invalid flag */
      WM__NumInvalidWindows--;
      /* Send WM_PAINT if window is visible and a callback is defined */
      if ((pWin->cb != NULL)  && (Status & WM_SF_ISVIS)) {
        WM_MESSAGE Msg;
        Msg.hWin   = iWin;
        Msg.MsgId  = WM_PAINT;
        Msg.Data.p = (GUI_RECT*)&pWin->InvalidRect;
        WM_SelectWindow(iWin);
        WM_SetDefault();
        #if GUI_SUPPORT_MEMDEV
          if (Status & WM_SF_MEMDEV) {
            GUI_RECT r = pWin->InvalidRect;
            GUI_MoveRect (&r, pWin->Rect.x0, pWin->Rect.y0);
            GUI_MEMDEV_Draw(&r, cbPaint, &Msg, 0, (Status & WM_SF_HASTRANS) ? GUI_MEMDEV_HASTRANS : 0);
          } else
        #endif
        WM_SendMessage(iWin, &Msg);
        UpdateRem--;  /* Only the given number of windows at a time ... */
      }
    }
    iWin = pWin->hNextLin;
  }  
  NextDrawWin = iWin;   /* Remember the window */
  GUI_RestoreContext(&ContextOld);
}

/*
          *****************************************************************
          *                                                               *
          *                 Idle loop                                     *
          *                                                               *
          *****************************************************************
*/

int WM_Exec1(void) {
  if (WM_pfHandleHID) {
    if (WM_pfHandleHID())
      return 1;               /* We have done something ... */
  }
  if (GUI_PollKeyMsg()) {
    return 1;               /* We have done something ... */
  }
  if (WM_IsActive && WM__NumInvalidWindows) {
    WM_LOCK();
    _DrawNext();
    WM_UNLOCK();
    return 1;               /* We have done something ... */
  }
  return 0;                  /* There was nothing to do ... */
}

int WM_Exec(void) {
  int r = 0;
  while (WM_Exec1()) {
    r = 1;                  /* We have done something */
  }
  return r;
}


/****************************************************************
*                                                               *
*              Callback for background window                   *
*                                                               *
*****************************************************************
*/

static WM_RESULT cbBackWin( WM_MESSAGE* pMsg) {
  WM_KEY_INFO* pKeyInfo;
  switch (pMsg->MsgId) {
  case WM_KEY:
    pKeyInfo = (WM_KEY_INFO*)pMsg->Data.p;
    if (pKeyInfo->PressedCnt == 0) {
      GUI_StoreKey(pKeyInfo->Key);
    }
    break;
  case WM_PAINT:
    if (WM__BkColor != GUI_INVALID_COLOR) {
      GUI_SetBkColor(WM__BkColor);
      GUI_Clear();
    }
  default:
    WM_DefaultProc(pMsg);
  }
}


/****************************************************************
*
*                    WM_Activate  / WM_Deactivate
*
*****************************************************************

*/

void WM_Activate(void) {
  WM_IsActive = 1;       /* Running */
}

void WM_Deactivate(void) {
  WM_IsActive = 0;       /* No clipping performed by WM */
  WM__SetMaxClipRect(WM_H2P(WM_HBKWIN));
}

/*
          *****************************************************************
          *                                                               *
          *              WM_Init                                         *
          *                                                               *
          *****************************************************************
*/
void WM_Init(void) {
	if (!_IsInited) {
	  WM_HWIN hWin;
	  NextDrawWin = WM__FirstWin = WM_HWIN_NULL;
	  GUI_Context.WM__pUserClipRect = NULL;
	  WM__NumWindows = WM__NumInvalidWindows =0;
	  /* Make sure we have at least one window. This greatly simplifies the
		  drawing routines as they do not have to check if the window is valid.
	  */
	  hWin = WM_CreateWindow(0,0, LCD_GET_VXSIZE(), LCD_GET_VYSIZE(), WM_CF_SHOW, cbBackWin, 0);
	  WM_SelectWindow(hWin);
	  WM_Activate();
    _IsInited =1;
	}
}



/*
          ******************************************************
          *                                                    *
          *              Default procedure                     *
          *                                                    *
          ******************************************************
*/


WM_RESULT WM_DefaultProc(WM_MESSAGE* pMsg) {
  WM_HWIN hWin = pMsg->hWin;
  void *p = pMsg->Data.p;
  WM_Obj* pWin = WM_H2P(hWin);
  /* Exec message */
  switch (pMsg->MsgId) {
  case WM_GETORG:
    ((GUI_POINT*)p)->x = pWin->Rect.x0;
    ((GUI_POINT*)p)->y = pWin->Rect.y0;
    break;
  case WM_GETCLIENTRECT:     /* return client window in window coordinates */
    WM__GetClientRectWin(pWin, (GUI_RECT*)p);
    break;
  case WM_GETCLIENTRECT_ABS:      /* return client window in absolute (screen) coordinates */
    WM__GetClientRectWin(pWin, (GUI_RECT*)p);
    GUI_MoveRect((GUI_RECT*)p, pWin->Rect.x0, pWin->Rect.y0);
    break;
  case WM_GET_CLIENT_WINDOW:      /* return handle to client window. For most windows, there is no seperate client window, so it is the same handle */
    pMsg->Data.v = hWin;
    return;                       /* Message handled */
  case WM_KEY:
    WM_SendToParent(hWin, pMsg);
    return;                       /* Message handled */
   case WM_GET_BKCOLOR:
    pMsg->Data.Color = GUI_INVALID_COLOR;
    return;                       /* Message handled */
  }
  /* Message not handled. If it queries something, we return 0 to be on the safe side. */
  pMsg->Data.v = 0;
  pMsg->Data.p = 0;
}

#else

void WM(void) {} /* avoid empty object files */

#endif /* WM_MAX_WINDOW */
