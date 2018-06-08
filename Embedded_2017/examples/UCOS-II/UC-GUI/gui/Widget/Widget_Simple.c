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
File        : BUTTON.c
Purpose     : emWin GSC button widget
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>

#include "WIDGET.h"
#include "GUIDebug.h"
#include "GUI.h"
#include "GUI_Protected.h"
#include "WM_Intern.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/


/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/


/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/

#define WIDGET_H2P(hWin)        ((WIDGET*)WM_HMEM2Ptr(hWin))

/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/


/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/

/*********************************************************************
*
*       WIDGET_DrawSimpleFrame
*/

void WIDGET_EFFECT_Simple_DrawUpRect(const GUI_RECT* pRect) {
  GUI_CONTEXT Context;
  GUI_SaveContext(&Context);
  GUI_SetColor(GUI_BLACK);
  GUI_DrawRect(pRect->x0, pRect->y0, pRect->x1, pRect->y1);          /* Draw rectangle around it */
  GUI_RestoreContext(&Context);
}

/*********************************************************************
*
*       WIDGET_EFFECT_Simple_DrawUp
*/

void WIDGET_EFFECT_Simple_DrawUp(void) {
  GUI_RECT r;
  WM_GetClientRect(&r);
  WIDGET_EFFECT_Simple_DrawUpRect(&r);
}
/*********************************************************************
*
*       WIDGET_EFFECT_Simple_DrawDown
*/
void WIDGET_EFFECT_Simple_DrawDownRect(const GUI_RECT* pRect) {
  GUI_CONTEXT Context;
  GUI_SaveContext(&Context);
  GUI_SetColor(GUI_BLACK);
  GUI_DrawRect(pRect->x0, pRect->y0, pRect->x1, pRect->y1);          /* Draw rectangle around it */
  GUI_RestoreContext(&Context);
}

void WIDGET_EFFECT_Simple_DrawDown(void) {
  GUI_RECT r;
  WM_GetClientRect(&r);
  WIDGET_EFFECT_Simple_DrawDownRect(&r);
}

/*********************************************************************
*
*       WIDGET_EFFECT_Simple_GetRect
*/
void WIDGET_EFFECT_Simple_GetRect(GUI_RECT* pRect) {
  WM_GetClientRect(pRect);
  GUI__ReduceRect(pRect, pRect, 1);
}

/*********************************************************************
*
*       Effect tables --- Mainly function pointers
*
**********************************************************************
*/

const WIDGET_EFFECT WIDGET_Effect_Simple = {
  WIDGET_EFFECT_Simple_DrawUp, WIDGET_EFFECT_Simple_DrawDown,
  WIDGET_EFFECT_Simple_DrawUpRect, WIDGET_EFFECT_Simple_DrawDownRect,
  WIDGET_EFFECT_Simple_GetRect, 1
};

void WIDGET_SetDefaultEffect_Simple(void) {
  WIDGET_SetDefaultEffect(&WIDGET_Effect_Simple);
}

#else                            /* Avoid problems with empty object modules */
  void WIDGET_Simple_C(void) {}
#endif /* GUI_WINSUPPORT */




