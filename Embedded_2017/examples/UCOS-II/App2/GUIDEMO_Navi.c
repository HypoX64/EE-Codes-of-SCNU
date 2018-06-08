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
File        : GUIDEMO_Navi.c
Purpose     : Navigation system demo
----------------------------------------------------------------------
*/

#include "GUI.h"
#include "WM.h"
#include "GUIDEMO.H"
#include "FrameWin.h"

#if GUI_WINSUPPORT & GUI_SUPPORT_MEMDEV

#include "Map.h"

/*********************************************************************
*
*       Typedefs
*
**********************************************************************
*/

typedef struct {
  int x;
  int y;
  int xHere, yHere;
  const GUI_BITMAP* pBitmap;
} tDrawContext;

/*********************************************************************
*
*       Static functions
*
**********************************************************************
*/

/* The user defined callback routine */
static void _Draw(void*p) {
  tDrawContext* pPara;
  GUI_CONTEXT ContextOld;
  GUI_SaveContext(&ContextOld);
  pPara = (tDrawContext*)p;
  GUI_DrawBitmap(pPara->pBitmap, -pPara->x, -pPara->y);
  GUI_SetPenSize(3);
  GUI_SetDrawMode(GUI_DRAWMODE_NORMAL);
  GUI_SetColor(GUI_RED);
  GUI_DrawCircle(pPara->xHere, pPara->yHere, 5);
  GUI_SetTextMode(GUI_TM_TRANS);
  GUI_SetFont(&GUI_FontComic18B_ASCII);
  GUI_DispStringAt("You are here", pPara->xHere - 20, pPara->yHere - 20);
  GUI_RestoreContext(&ContextOld);
}

static void _ShowMovingMap(void) {
  int i;
  tDrawContext DrawContext = {0};
  GUI_RECT r;
  int t0, t, tRef;
  #if GUIDEMO_LARGE
    int y0 = 70;
  #else
    int y0 = 20;
  #endif
  WM_HWIN hFrameWin, hClientWin;
  int XSize = LCD_GetXSize();
  #if GUIDEMO_LARGE
    hFrameWin  = FRAMEWIN_Create("Map to Segger Hilden", NULL, WM_CF_SHOW, 
                                 10, y0, (XSize > 270 ? 260 : XSize - 20), 160);
  #else
    hFrameWin  = FRAMEWIN_Create("Map to Segger Hilden", NULL, WM_CF_SHOW, 
                                 10, 10, (XSize > 270 ? 260 : XSize - 20), LCD_YSIZE - 20);
  #endif
  hClientWin = WM_CreateWindowAsChild(0, 0, 0, 0, hFrameWin, WM_CF_SHOW , 0 , 0);
  FRAMEWIN_SetActive(hFrameWin, 0);
  WM_SelectWindow(hClientWin);
  WM_GetWindowRect(&r);
  DrawContext.pBitmap = &bmMap;
/* Move text */
  for (i = 0, t0 = GUI_GetTime(); t = GUI_GetTime() - t0, (t < 2000) && !GUIDEMO_CheckCancel(); i++) {
    DrawContext.x = 0;
    DrawContext.y = 0;
    DrawContext.xHere = y0 + 2 * i;
    DrawContext.yHere = y0;
    tRef = GUI_GetTime() + 100;
    GUI_MEMDEV_Draw(&r, _Draw, &DrawContext, 0, GUI_MEMDEV_NOTRANS);
    tRef -= GUI_GetTime();
    GUI_Delay(tRef);
  }
/* Move map in x */
  for (t0 = GUI_GetTime(); t = GUI_GetTime() - t0, (t < 4000) && !GUIDEMO_CheckCancel();) {
    DrawContext.x += 2;
    tRef = GUI_GetTime() + 100;
    GUI_MEMDEV_Draw(&r, _Draw, &DrawContext, 0, GUI_MEMDEV_NOTRANS);
    tRef -= GUI_GetTime();
    GUI_Delay(tRef);
  }
/* Move map in y */
  for (t0 = GUI_GetTime(); t = GUI_GetTime() - t0, (t < 4000) && !GUIDEMO_CheckCancel(); ) {
    DrawContext.y += 2;
    tRef = GUI_GetTime() + 100;
    GUI_MEMDEV_Draw(&r, _Draw, &DrawContext, 0, GUI_MEMDEV_NOTRANS);
    tRef -= GUI_GetTime();
    GUI_Delay(tRef);
  }
/* Move map in x and y */
  for (t0 = GUI_GetTime(); t = GUI_GetTime()- t0, (t < 4000) && !GUIDEMO_CheckCancel();) {
    DrawContext.x -= 2;
    DrawContext.y -= 2;
    tRef = GUI_GetTime() + 100;
    GUI_MEMDEV_Draw(&r, _Draw, &DrawContext, 0, GUI_MEMDEV_NOTRANS);
    tRef -= GUI_GetTime();
    GUI_Delay(tRef);
  }
  WM_DeleteWindow(hFrameWin);
  /*WM_DeleteWindow(hClientWin);*/
}

#else

#define _ShowMovingMap()

#endif

/*********************************************************************
*
*       GUIDEMO_Navigation
*
**********************************************************************
*/

void GUIDEMO_Navigation(void) {
  GUIDEMO_ShowIntro("Navigation system",
                    "Samples used in"
                    "\nNavigation systems");
  _ShowMovingMap();
}
