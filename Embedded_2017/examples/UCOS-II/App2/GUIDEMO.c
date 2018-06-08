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
File        : GUIDEMO.c
Purpose     : Several GUIDEMO routines
----------------------------------------------------------------------
*/

#include <stddef.h>
#include "GUI.h"
#include "Progbar.h"
#include "LISTBOX.h"
#include "FrameWin.h"
#include "BUTTON.H"
#include "GUIDEMO.H"

/*********************************************************************
*
*       Static variables
*
**********************************************************************
*/

#if GUI_WINSUPPORT
  static BUTTON_Handle   _ahButton[2];
  static FRAMEWIN_Handle _ahFrameWin[2];
  static FRAMEWIN_Handle _ahInfoWin[2];
  static int             _FrameWinPosX[2],  _FrameWinPosY[2];
  static int             _FrameWinSizeX[2], _FrameWinSizeY[2];
  static int             _ButtonSizeX,      _ButtonSizeY;
#endif

static int         _iTest, _iTestMinor;
static char        _CmdNext;
static const char* _sInfo;
static const char* _sExplain;

#define countof(Obj) (sizeof(Obj)/sizeof(Obj[0]))

/*********************************************************************
*
*       Routine table
*
**********************************************************************

  The routines to be called are listed here. The advantage to calling
  directly is that we can execute some code before and after.
*/

typedef void fVoidVoid(void);

static fVoidVoid * _apfTest[] = {
  GUIDEMO_HardwareInfo,
  GUIDEMO_Speed,
  #if GUI_SUPPORT_MEMDEV
    GUIDEMO_Graph,
  #endif
  GUIDEMO_Bitmap,
  GUIDEMO_ShowInternationalFonts,
  GUIDEMO_Dialog,
  GUIDEMO_ShowColorBar,
  GUIDEMO_ShowColorList,
  GUIDEMO_DemoLUT,
  GUIDEMO_DemoPolygon,
  GUIDEMO_Circle,
  GUIDEMO_ShowMemoryDevice,
  GUIDEMO_Automotive,
  GUIDEMO_Navigation,                 
  #if GUI_WINSUPPORT
    GUIDEMO_DemoProgBar,
    GUIDEMO_DemoFrameWin,
    #if GUI_SUPPORT_TOUCH
      GUIDEMO_Touch,
    #endif
  #endif
  0  
};




/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/

static void _UpdateCmdWin(void) {
  #if GUI_WINSUPPORT && GUIDEMO_LARGE
    /* Update info in command window */
    WM_HWIN hWin;
    GUI_CONTEXT ContextOld;
    GUI_SaveContext(&ContextOld);
    hWin = WM_SelectWindow(_ahInfoWin[1]);
    GUI_SetDefault();
    GUI_SetBkColor(GUI_GRAY);
    GUI_Clear();
    GUI_DispStringAt("Demo ", 0, 0);
    GUI_DispDecMin(_iTest + 1);
    GUI_DispString(".");
    GUI_DispDecMin(_iTestMinor);
    GUI_DispString("/");
    GUI_DispDecMin(countof(_apfTest));
    WM_SelectWindow(hWin);
    GUI_RestoreContext(&ContextOld);
  #endif
}

static void _UpdateInfoWin(void) {
  #if GUI_WINSUPPORT && GUIDEMO_LARGE
    GUI_RECT rClient;
    WM_HWIN hWin;
    GUI_CONTEXT ContextOld;
    GUI_SaveContext(&ContextOld);
    /* Update info  window */
    WM_ShowWindow(_ahInfoWin[0]);
    WM_ShowWindow(_ahFrameWin[0]);
    hWin = WM_SelectWindow(_ahInfoWin[0]);
    GUI_GetClientRect(&rClient);
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();
    GUI_SetColor(GUI_BLACK);
    GUI_SetFont(&GUI_Font13_1);
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringHCenterAt(_sInfo, (rClient.x1 - rClient.x0) / 2, 0);
    GUI_SetTextAlign(GUI_TA_LEFT);
    GUI_SetFont(&GUI_Font8_ASCII);
    GUI_DispStringAt(_sExplain, 0, 20);
    WM_SelectWindow(hWin);
    GUI_RestoreContext(&ContextOld);
  #endif
}

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/

int GUIDEMO_Delay(int t) {
  int r = 0;
  #if GUI_WINSUPPORT
    int tRem, tEnd = GUI_GetTime() + t;
    PROGBAR_Handle hProg;
    WM_SetForegroundWindow(_ahButton[0]);
    hProg = (t >100) ? PROGBAR_Create(_FrameWinPosX[1]  + 10,
                                      _FrameWinPosY[1]  + 25,
                                      _FrameWinSizeX[1] - 20,
                                      7,
                                      WM_CF_SHOW|WM_CF_STAYONTOP) : 0;
    #if GUI_SUPPORT_MEMDEV
      PROGBAR_EnableMemdev(hProg);  
    #endif
    PROGBAR_SetMinMax(hProg, 0, t);
    for (; tRem = tEnd - GUI_GetTime(), (tRem > 0) && !GUIDEMO_CheckCancel();) {
      PROGBAR_SetValue(hProg, t - tRem);
      WM_ExecIdle();
      GUI_Delay(10);
    }
    PROGBAR_Delete(hProg);
    _UpdateCmdWin();
    WM_ExecIdle();
  #else
    GUI_Delay(t);
  #endif
  return r;
}

void GUIDEMO_Wait(void) {
  GUIDEMO_Delay(200);
  GUIDEMO_NotifyStartNext();
}

int GUIDEMO_CheckCancel(void) {
  int c = GUI_GetKeyNoDel();
  #if GUI_WINSUPPORT
    WM_ExecIdle();
  #endif
  if ((c == 'e') || (c=='E'))
  {
    _CmdNext =1;
    GUI_GetKey();
  }
  if ((c == 's') || (c=='S')) {
    GUI_Delay(500);
    do {
      GUI_Delay(10);
      #if GUI_WINSUPPORT
        WM_ExecIdle();
      #endif
      c = GUI_GetKey();
    } while (!c);
  }
  return _CmdNext;
}

void GUIDEMO_ShowInfo(const char* s) {
  _sExplain = s;
  _UpdateInfoWin();
}

void GUIDEMO_HideInfoWin(void) {
  #if GUI_WINSUPPORT
    WM_HideWindow(_ahFrameWin[0]);
  #endif
}


void GUIDEMO_NotifyStartNext(void) {
  _CmdNext = 0;
  _UpdateCmdWin();
  _iTestMinor++;
}

int GUIDEMO_WaitKey(void) {
  int r = 0;
  int tMax = GUI_GetTime() + 4000;
  int tDiff; 
  #if GUI_WINSUPPORT
    PROGBAR_Handle hProg = PROGBAR_Create(LCD_GetXSize() - 70, 
                                          LCD_GetYSize() - 40, 
                                          80, 5, WM_CF_SHOW);
  #endif
  while (tDiff = tMax-GUI_GetTime(), (tDiff > 0) && !GUIDEMO_CheckCancel()) {
    if ((r = GUI_GetKey()) != 0)
      break;
  }
  #if GUI_WINSUPPORT
    PROGBAR_Delete(hProg);
    WM_ExecIdle();
  #endif
  return r;
}

void GUIDEMO_ShowIntro(const char * s, const char * sExp) {
  GUI_CONTEXT ContextOld;
  GUI_SaveContext(&ContextOld);
  _sInfo = s;
  _sExplain = sExp;
  GUI_SetDefault();
  GUIDEMO_HideInfoWin();
  GUI_SetBkColor(GUI_BLUE);
  GUI_SetColor(GUI_WHITE);
  GUI_Clear();
  GUI_SetFont(&GUI_FontComic18B_ASCII);
  GUI_DispStringHCenterAt(s, LCD_GET_XSIZE() / 2, LCD_GET_YSIZE() / 3 - 10);
  if (_sExplain) {
    GUI_SetFont(&GUI_Font8_ASCII);
    GUI_DispStringHCenterAt(_sExplain, LCD_GET_XSIZE() / 2, LCD_GET_YSIZE() / 2 - 10);
  }
  GUIDEMO_Delay(_sExplain ? 200 : 400);
#if GUI_WINSUPPORT
  _UpdateInfoWin();
  _UpdateCmdWin();
#endif
  GUI_RestoreContext(&ContextOld);
  #if GUI_WINSUPPORT
    WM_ExecIdle();
  #endif
  GUIDEMO_NotifyStartNext();
  GUI_SetBkColor(GUI_RED);
  GUI_Clear();
}

/*********************************************************************
*
*       GUIDEMO_main(): Complete Demo
*
**********************************************************************
*/

#if GUIDEMO_LARGE

void GUIDEMO_main(void) {
  #if GUI_WINSUPPORT
    int i;
  #endif
  GUI_Clear();
  #if GUI_WINSUPPORT
    WM_SetCreateFlags(WM_CF_MEMDEV);  /* Automatically use memory devices on all windows */
    /* Calculate position and size of FrameWin[1] */
    _FrameWinSizeX[1] = 80;
    _FrameWinSizeY[1] = 60;
    _FrameWinPosX[1] = LCD_GetXSize() - _FrameWinSizeX[1];
    _FrameWinPosY[1] = LCD_GetYSize() - _FrameWinSizeY[1];
    _ButtonSizeX = (_FrameWinSizeX[1] - 20) / 2;
    _ButtonSizeY = 20;
    /* Create the control window incl. buttons */
    _ahFrameWin[1] = FRAMEWIN_Create("Control", NULL, WM_CF_SHOW | WM_CF_STAYONTOP,
                                     _FrameWinPosX[1], _FrameWinPosY[1],
                                     _FrameWinSizeX[1], _FrameWinSizeY[1]);
    _ahInfoWin[1] = WM_CreateWindowAsChild(0, 0, 0, 0, _ahFrameWin[1], 
                                           WM_CF_SHOW | WM_CF_STAYONTOP, 0, 0);
    _ahButton[0] = BUTTON_CreateAsChild(_FrameWinSizeX[1] / 20,
                                 + 20, _ButtonSizeX, _ButtonSizeY, _ahFrameWin[1], 
                                 'H' , WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV);
    _ahButton[1] = BUTTON_CreateAsChild(_FrameWinSizeX[1] / 2,
                                 + 20, _ButtonSizeX, _ButtonSizeY, _ahFrameWin[1], 
                                 'N' , WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV);
    BUTTON_SetText(_ahButton[0], "Stop");
    BUTTON_SetText(_ahButton[1], "Next");
    _UpdateCmdWin();
    WM_ExecIdle();
  #endif
  /* Show Intro */
  GUIDEMO_Intro();
  #if GUI_WINSUPPORT
    /* Calculate position and size of FrameWin[0] */
    _FrameWinSizeX[0] = LCD_GetXSize() / 2;
    _FrameWinSizeY[0] = 65;
    _FrameWinPosX[0] = LCD_GetXSize() - _FrameWinSizeX[0];
    _FrameWinPosY[0] = 0;
    /* Create info window and run the individual demos */
    _ahFrameWin[0] = FRAMEWIN_Create("µC/GUI Demo", NULL, WM_CF_STAYONTOP, 
                                     _FrameWinPosX[0], _FrameWinPosY[0], _FrameWinSizeX[0], _FrameWinSizeY[0]);
    _ahInfoWin[0] = WM_CreateWindowAsChild(0, 0, 0, 0, _ahFrameWin[0], WM_CF_STAYONTOP, 0, 0);
    WM_ExecIdle();
  #endif
  /* Run the individual demos !  */
  for (_iTest = 0; _apfTest[_iTest]; _iTest++) {
    GUI_CONTEXT ContextOld;
    GUI_SaveContext(&ContextOld);
    _iTestMinor = 0;
    _UpdateCmdWin();
    (*_apfTest[_iTest])();
    _CmdNext = 0;
    GUI_RestoreContext(&ContextOld);
  }
  /* Cleanup */
  #if GUI_WINSUPPORT
    for (i = 0; i < countof(_ahFrameWin); i++) {
      WM_DeleteWindow(_ahFrameWin[i]);
    }
    for (i = 0; i < countof(_ahInfoWin); i++) {
      WM_DeleteWindow(_ahInfoWin[i]);
    }
  #endif
}

#else /* GUIDEMO_LARGE */

void GUIDEMO_main(void) {
  #if GUI_WINSUPPORT
    int i;
  #endif
  #if GUI_WINSUPPORT
    WM_SetCreateFlags(WM_CF_MEMDEV);  /* Automatically use memory devices on all windows */
    _ButtonSizeX = 27;
    _ButtonSizeY = 14;
    _ahButton[0] = BUTTON_Create(LCD_GetXSize() - _ButtonSizeX * 2 - 5,
                                 LCD_GetYSize() - _ButtonSizeY - 3,
                                 _ButtonSizeX, _ButtonSizeY, 
                                 'H' , WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV);
    _ahButton[1] = BUTTON_Create(LCD_GetXSize() - _ButtonSizeX - 3,
                                 LCD_GetYSize() - _ButtonSizeY - 3,
                                 _ButtonSizeX, _ButtonSizeY, 
                                 'N' , WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV);
    BUTTON_SetFont(_ahButton[0], &GUI_Font8_ASCII);
    BUTTON_SetFont(_ahButton[1], &GUI_Font8_ASCII);
    BUTTON_SetText(_ahButton[0], "Stop");
    BUTTON_SetText(_ahButton[1], "Next");
    _UpdateCmdWin();
    WM_ExecIdle();
  #endif
  /* Show Intro */
  GUIDEMO_Intro();
  /* Run the individual demos !  */
  for (_iTest = 0; _apfTest[_iTest]; _iTest++) {
    GUI_CONTEXT ContextOld;
    GUI_SaveContext(&ContextOld);
    _iTestMinor = 0;
    _UpdateCmdWin();
    (*_apfTest[_iTest])();
    _CmdNext = 0;
    GUI_RestoreContext(&ContextOld);
  }
  /* Cleanup */
  #if GUI_WINSUPPORT
    for (i = 0; i < countof(_ahButton); i++) {
      BUTTON_Delete(_ahButton[i]);
    }
  #endif
}

#endif /* GUIDEMO_LARGE */
