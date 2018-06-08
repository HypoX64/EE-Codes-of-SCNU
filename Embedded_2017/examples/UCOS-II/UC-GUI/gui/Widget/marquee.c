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
File        : MARQUEE.c
Purpose     : emWin GSC bitmap widget, which allows to show blinking
              bitmaps
----------------------------------------------------------------------
Version-Date---Author-Explanation
----------------------------------------------------------------------
1.02     001011 RS     a) Debug info (logging option) added.
                       b) Support for Zero-time (transparent)
                          bitmaps added.
1.00     000613 RS     Release.
0.50     000223 RS     First (Beta) release
0.00     000107 RS     Start of development
----------------------------------------------------------------------
Known problems or limitations with current version
----------------------------------------------------------------------
None.
----------------------------------------------------------------------
Open issues
----------------------------------------------------------------------
None
---------------------------END-OF-HEADER------------------------------
*/

#include "stdlib.h"
#include "string.h"
#include "MARQUEE.h"
#include "GUIDEBUG.h"
#include "GUI.h"

#if GUI_WINSUPPORT

/*
  *****************************************************************
  *                                                               *
  *              Config defaults                                  *
  *                                                               *
  *****************************************************************
*/
#ifndef MARQUEE_LOG_ENABLE
  #ifdef _DEBUG
    #define MARQUEE_LOG_ENABLE 0
  #else
    #define MARQUEE_LOG_ENABLE 0
  #endif
#endif

/*
  *****************************************************************
  *
  *              Internal macros
  *
  *****************************************************************
*/
#define Invalidate(h) WM_InvalidateWindow(h)

#if MARQUEE_LOG_ENABLE
  #define LOG(s) SIM_Log(s)
  #define LOG1(s,p1) SIM_Log(s,p1)
  #define LOG_TIME() SIM_LogTime()
#else
  #define LOG(s)
  #define LOG1(s)
  #define LOG_TIME()
#endif


/*
      *************************************************************
      *                                                           *
      *                 LIST ITEM  definition                     *
      *                                                           *
      *************************************************************
*/

/*
      *************************************************************
      *                                                           *
      *                 Object definition                         *
      *                                                           *
      *************************************************************
*/
typedef struct {
  WM_Obj WMObj;
  GUI_TIMER_Handle hTimer;
  WM_HMEM hpText;
  GUI_COLOR TextColor;
  GUI_COLOR BkColor;
  const GUI_FONT* pFont;
#ifdef _DEBUG
  int Id;
#endif  
} MARQUEE_Obj;

/*
  *****************************************************************
  *                                                               *
  *              Static data                                      *
  *                                                               *
  *****************************************************************
*/

/* None */
/*
  ********************************************************************
  *                                                                  *
  *                 Macros for internal use                          *
  *                                                                  *
  ********************************************************************
*/
#define MARQUEE_ID 0x4249544d


#define MARQUEE_H2P(h) (MARQUEE_Obj*) WM_HMEM2Ptr(h)
#define LI_H2P(h)     (LI_Obj*)     WM_HMEM2Ptr(h)

#ifdef _DEBUG
  #define MARQUEE_ASSERT_IS_VALID_PTR(p) WM_ASSERT(p->Id == MARQUEE_ID)
  #define MARQUEE_INIT_ID(p)   p->Id = MARQUEE_ID
  #define MARQUEE_DEINIT_ID(p) p->Id = MARQUEE_ID+1
#else
  #define MARQUEE_ASSERT_IS_VALID_PTR(p)
  #define MARQUEE_INIT_ID(p)
  #define MARQUEE_DEINIT_ID(p)
#endif
/*
  ********************************************************************
  *                                                                  *
  *                    Static routines                               *
  *                                                                  *
  ********************************************************************
*/

static void FreeAttached(MARQUEE_Handle hObj) {
  MARQUEE_Obj* pObj = MARQUEE_H2P(hObj);
  WM_FREEPTR(&pObj->hpText);
}


static void Paint(MARQUEE_Obj* pObj/*, GUI_RECT*pRect*/) {
  const char*s = (const char*) WM_HMEM2Ptr(pObj->hpText);
  GUI_SetFont    (pObj->pFont);
  GUI_SetBkColor (pObj->BkColor);
  GUI_SetColor   (pObj->TextColor);
  GUI_DispStringAt(s,0,0);
  LOG_TIME(); LOG("MARQUEE: Paint(..)\n");
}


static void Delete(MARQUEE_Obj* pObj) {
  if (pObj->hTimer) {
    GUI_TIMER_Delete(pObj->hTimer);
    pObj->hTimer =0;
	}
  if (pObj->hpText) {
//    GUI_ALLOC_Free(hLI);
    LOG_TIME(); LOG("MARQUEE: Delete: Deleting attached string\n");
  }
}

static void _Callback (WM_MESSAGE * pMsg) {
  MARQUEE_Handle hObj = (MARQUEE_Handle)pMsg->hWin;
  MARQUEE_Obj* pObj = MARQUEE_H2P(hObj);
  switch (pMsg->MsgId) {
  case WM_PAINT:
    LOG_TIME(); LOG("MARQUEE: _Callback(WM_PAINT)\n");
    Paint(pObj/*, (GUI_RECT*)pMsg->Data.p*/);
    return;
  case WM_DELETE:
    LOG_TIME(); LOG("MARQUEE: _Callback(WM_DELETE)\n");
    Delete(pObj);
    break;       /* No return here ... WM_DefaultProc needs to be called */
#if MARQUEE_LOG_ENABLE  /* Debug code ... normally not compiled */
  case WM_CREATE:
    LOG_TIME(); LOG("MARQUEE: _Callback(WM_CREATE)\n");
    break;       /* No return here ... WM_DefaultProc needs to be called */
  default:
    LOG_TIME(); LOG("MARQUEE: _Callback(unhandle message)\n");
#endif
  }
  WM_DefaultProc(pMsg);
}

static void cbTimer (GUI_TIMER_MESSAGE *pMsg) {
  MARQUEE_Handle hObj = pMsg->Context;
  MARQUEE_Obj*   pObj = MARQUEE_H2P(hObj);
  MARQUEE_ASSERT_IS_VALID_PTR(pObj);
  LOG_TIME(); LOG("MARQUEE: cbTimer\n");
//  ShowNext(pObj);
}


/*
  ********************************************************************
  *                                                                  *
  *        Exported routines:  Create                                *
  *                                                                  *
  ********************************************************************
*/

/* Note: the parameters to a create function may vary.
         Some widgets may have multiple create functions */


MARQUEE_Handle MARQUEE_Create      (
                                    int x0, int y0, int xsize, int ysize,
                                    int Flags)
{
  /* Alloc memory for obj */
  MARQUEE_Handle hObj =  WM_CreateWindow(x0, y0, xsize, ysize,
                  WM_CF_SHOW |Flags, _Callback,
                  sizeof(MARQUEE_Obj)-sizeof(WM_Obj));
  if (hObj) {
    MARQUEE_Obj* pObj = MARQUEE_H2P(hObj);
    /* init widget specific variables */
    /* init member variables */
    MARQUEE_INIT_ID(pObj);
    pObj->pFont =GUI_DEFAULT_FONT;
    pObj->BkColor   = GUI_BLACK;
    pObj->TextColor = GUI_WHITE;
/* Create Timer */
    pObj->hTimer = GUI_TIMER_Create(cbTimer,
		                            0,    /* Time, 0 means not yet active */
                                hObj, /* Instance handle */
																0);
  }
  return hObj;
}


/*
  ********************************************************************
  *                                                                  *
  *        Exported routines:  Various methods                       *
  *                                                                  *
  ********************************************************************
*/

void MARQUEE_SetText(MARQUEE_Handle hObj, const char* s) {
  MARQUEE_Obj* pObj = MARQUEE_H2P(hObj);
  FreeAttached(hObj);
  {
    WM_HMEM hMem = WM_ALLOC(strlen(s)+1);
    strcpy((char *) WM_HMEM2Ptr(hMem), s);
    pObj->hpText = hMem;
  }
  Invalidate(hObj);
}

void MARQUEE_SetFont(MARQUEE_Handle hObj, const GUI_FONT* pfont) {
  MARQUEE_Obj* pObj = MARQUEE_H2P(hObj);
  pObj->pFont = pfont;
  Invalidate(hObj);
}

void MARQUEE_SetBkColor(MARQUEE_Handle hObj, GUI_COLOR color) {
  MARQUEE_Obj* pObj = MARQUEE_H2P(hObj);
  pObj->BkColor = color;
  Invalidate(hObj);
}

void MARQUEE_SetTextColor(MARQUEE_Handle hObj, GUI_COLOR color) {
  MARQUEE_Obj* pObj = MARQUEE_H2P(hObj);
  pObj->TextColor = color;
  Invalidate(hObj);
}

#else

void WIDGET_Marquee(void) {} /* avoid empty object files */

#endif
