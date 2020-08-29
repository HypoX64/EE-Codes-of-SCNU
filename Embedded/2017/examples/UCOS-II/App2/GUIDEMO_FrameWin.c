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
File        : GUIDEMO_DemoFrameWin.c
Purpose     : Demonstrates the FRAMEWIN widget
----------------------------------------------------------------------
*/

#include <stddef.h>
#include "WM.H"
#include "LISTBOX.h"
#include "FrameWin.h"
#include "GUIDEMO.H"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static const GUI_ConstString _asLang[] = {
  "English", 
  "Deutsch", 
  "Français", 
  "Espa\xf1ol", /* "Español" -> "Espa\xf1ol" to avoid problems with NC308 */
  "Italiano", 
  NULL 
};

/*********************************************************************
*
*       GUIDEMO_DemoFrameWin
*
**********************************************************************
*/

void GUIDEMO_DemoFrameWin(void) {
  FRAMEWIN_Handle hFW;
  LISTBOX_Handle hLB;
  int i;
  const GUI_FONT* pFont = &GUI_FontComic18B_1;
  #if GUIDEMO_LARGE
    GUIDEMO_ShowIntro("Frame Window & Listbox", NULL);
  #else
    GUIDEMO_ShowIntro("Frame Window\n & Listbox", NULL);
  #endif
  #if GUIDEMO_LARGE
    hFW = FRAMEWIN_Create ( "Select language", NULL, WM_CF_SHOW, 10, 10, 100, 110);
  #else
    hFW = FRAMEWIN_Create ( "Select language", NULL, WM_CF_SHOW, 10, 10, 100, LCD_YSIZE - 20);
  #endif
  FRAMEWIN_SetFont(hFW, &GUI_Font13_ASCII);
  hLB = LISTBOX_CreateAsChild(_asLang, hFW, 0, 0, 0, /*5 * GUI_GetYSizeOfFont(pFont)*/0, WM_CF_SHOW);
  LISTBOX_SetFont(hLB, pFont);
  GUIDEMO_Wait();
  for (i = 0; (i < 10) && !GUIDEMO_CheckCancel(); i++) {
    LISTBOX_IncSel(hLB);
    GUIDEMO_Delay(250);
	}
  for (i = 0; (i < 10) && !GUIDEMO_CheckCancel(); i++) {
    LISTBOX_DecSel(hLB);
    GUIDEMO_Delay(250);
	}
  GUIDEMO_Delay(500);
  LISTBOX_Delete(hLB);
  FRAMEWIN_Delete(hFW);
}

#elif defined(NC30) || defined(NC308)

void GUIDEMO_FrameWin(void) {}

#endif
