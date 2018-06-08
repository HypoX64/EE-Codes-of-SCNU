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
File        : GUICore.C
Purpose     : Core file for emWin GSC
---------------------------END-OF-HEADER------------------------------
*/


#include <stddef.h>           /* needed for definition of NULL */

#define  GL_CORE_C
#include "GUI_Private.H"

#include "GUIDebug.h"


/*      *********************************
        *                               *
        *      Get / Set Attributes     *
        *                               *
        *********************************
*/


U8        GUI_GetLineStyle (void) {
  U8 r;
  GUI_LOCK();
  r = GUI_Context.LineStyle;
  GUI_UNLOCK();
  return r;
}

/*
        *********************************************************
        *                                                       *
        *       GUI_SetColor                                    *
        *       GUI_SetBkColor                                  *
        *                                                       *
        *********************************************************

Purpose:  Assign color/index to foreground/ background
*/

void GUI_SetBkColor(GUI_COLOR color) {
  GUI_LOCK(); {
    LCD_SetBkColor(color);
  } GUI_UNLOCK();
}

void GUI_SetColor(GUI_COLOR color) {
  GUI_LOCK(); {
    LCD_SetColor(color);
  } GUI_UNLOCK();
}

/*
  *********************************************************
  *
  *        GUI_SetDrawMode
  *
  *********************************************************
*/

GUI_DRAWMODE GUI_SetDrawMode(GUI_DRAWMODE dm) {
  GUI_DRAWMODE OldMode;
  GUI_LOCK(); {
  OldMode = LCD_SetDrawMode(dm);
  } GUI_UNLOCK();
  return OldMode;
}



U8 GUI_SetLineStyle (U8 LineStyle) {
  U8 r;
  GUI_LOCK();
    r = GUI_Context.LineStyle;
    GUI_Context.LineStyle = LineStyle;
  GUI_UNLOCK();
  return r;
}


/*********************************************************************
*
*            GUI_ClearRect
*
**********************************************************************
*/

void GUI_ClearRect(int x0, int y0, int x1, int y1) {
  GUI_DRAWMODE PrevDraw;
  GUI_LOCK();
  PrevDraw = LCD_SetDrawMode(GUI_DRAWMODE_REV);
  #if GUI_WINSUPPORT
    WM_ADDORG(x0,y0);
    WM_ADDORG(x1,y1);
    WM_ITERATE_START(NULL) {
  #endif
  LCD_FillRect(x0,y0,x1,y1);
  #if GUI_WINSUPPORT
    } WM_ITERATE_END();
  #endif
  LCD_SetDrawMode(PrevDraw);
  GUI_UNLOCK();
}



/*********************************************************************
*
*            GUI_Clear
*
**********************************************************************
*/


void GUI_Clear(void) {
  GUI_GotoXY(0,0);     /* Reset text cursor to upper left */
  GUI_ClearRect(GUI_XMIN, GUI_YMIN, GUI_XMAX, GUI_YMAX);
}


/*
        ********************************************************
        *                                                      *
        *                 GUI_SelectLCD                        *
        *                                                      *
        ********************************************************
*/

#if GUI_SUPPORT_MEMDEV
void GUI_SelectLCD(void) {
  int hDevDataOld = GUI_Context.hDevData;
  GUI_Context.hDevData = 0;
  GUI_Context.pDeviceAPI   = &LCD_L0_APIList;
  GUI_Context.pClipRect_HL = &GUI_Context.ClipRect;
  LCD_SetClipRectMax();
  /* If we are switching batck, restore the former clip rect */
  if (hDevDataOld)
    GUI_Context.ClipRect = GUI_Context.ClipRectPrev;
  #if GUI_WINSUPPORT
    WM_Activate();
  #endif
}
#endif


/*
        ********************************************************
        *                                                      *
        *                 GUI_Init                             *
        *                                                      *
        *     Init of GUI internal data structures & variables *
        *                                                      *
        ********************************************************
*/

const tLCD_HL_APIList LCD_HL_APIList = {
  LCD_DrawHLine,
  LCD_DrawPixel
};

static void _InitContext(GUI_CONTEXT* pContext) {
  #if GUI_SUPPORT_MEMDEV
    GUI_SelectLCD();
  #else
    LCD_SetClipRectMax();
  #endif
  pContext->pLCD_HL      = &LCD_HL_APIList;
  pContext->pAFont       = GUI_DEFAULT_FONT;
  pContext->pClipRect_HL = &GUI_Context.ClipRect;
  pContext->PenSize      = 1;
  /* Variables in WM module */
  #if GUI_WINSUPPORT
    pContext->hAWin    = WM_GetDesktopWindow();
  #endif
  /* Variables in GUI_AA module */
  pContext->AA_Factor = 3;
  LCD_SetBkColor(GUI_DEFAULT_BKCOLOR);
  LCD_SetColor(GUI_DEFAULT_COLOR);
}




int GUI_Init(void) {
  int r;
  GUI_DEBUG_LOG("\nGUI_Init()");
  /* Init system wide globals first */
  GUI_DecChar = '.';
  GUI_X_Init();
  /* Init context */
  _InitContext(&GUI_Context);
  GUITASK_INIT();
  r = LCD_Init();
  #if GUI_WINSUPPORT
    WM_Init();
  #endif
  GUI_DEBUG_LOG("\nGUI_Init out()");
  return r;
}








