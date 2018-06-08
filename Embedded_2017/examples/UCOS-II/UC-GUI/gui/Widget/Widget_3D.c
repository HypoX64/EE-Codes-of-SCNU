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
*       WIDGET_Draw3DFrame
*/

void WIDGET_EFFECT_3D_DrawUpRect(const GUI_RECT* pRect) {
  GUI_RECT r;
  GUI_CONTEXT Context;
  GUI_SaveContext(&Context);
  r = *pRect;
  GUI_SetColor(0x000000);
  GUI_DrawRect(r.x0, r.y0, r.x1, r.y1);          /* Draw rectangle around it */
 /* Draw the bright sides */
  GUI_SetColor(0xffffff);
  GUI_DrawHLine(r.y0 + 1, r.x0 + 1, r.x1 - 2);    /* Draw top line */
  GUI_DrawVLine(r.x0 + 1, r.y0 + 1, r.y1 - 2);
  /* Draw the dark sides */
  GUI_SetColor(0x555555);
  GUI_DrawHLine(r.y1-1, r.x0 + 1, r.x1 - 1);
  GUI_DrawVLine(r.x1-1, r.y0 + 1, r.y1 - 2);
  GUI_RestoreContext(&Context);
}

/*********************************************************************
*
*       WIDGET_EFFECT_3D_DrawUp
*/

void WIDGET_EFFECT_3D_DrawUp(void) {
  GUI_RECT r;
  WM_GetClientRect(&r);
  WIDGET_EFFECT_3D_DrawUpRect(&r);
}
/*********************************************************************
*
*       WIDGET_EFFECT_3D_DrawDown
*/
void WIDGET_EFFECT_3D_DrawDownRect(const GUI_RECT* pRect) {
  GUI_RECT r;
  r = *pRect;
  GUI_SetColor(0x000000);  /// TBD: Use halftone
//  GUI_DrawRect(0, 0, r.x1, r.y1);
  /* Draw the upper left sides */
  GUI_SetColor(0x808080);
  GUI_DrawHLine(r.y0, r.x0, r.x1);
  GUI_DrawVLine(r.x0, r.y0 + 1, r.y1);
  GUI_SetColor(0x0);
  GUI_DrawHLine(r.y0 + 1, r.x0 + 1, r.x1 - 1);
  GUI_DrawVLine(r.x0 + 1, r.y0 + 2, r.y1 - 1);
  /* Draw the lower right sides */
  GUI_SetColor(0xffffff);
  GUI_DrawHLine(r.y1, r.x0 + 1, r.x1);
  GUI_DrawVLine(r.x1, r.y0 + 1, r.y1);
  GUI_SetColor(0xc0c0c0);
  GUI_DrawHLine(r.y1 - 1, r. x0 + 2, r.x1-1);
  GUI_DrawVLine(r.x1 - 1, r. y0 + 2, r.y1-1);
}

void WIDGET_EFFECT_3D_DrawDown(void) {
  GUI_RECT r;
  WM_GetClientRect(&r);
  WIDGET_EFFECT_3D_DrawDownRect(&r);
}

/*********************************************************************
*
*       WIDGET_EFFECT_3D_GetRect
*/
void WIDGET_EFFECT_3D_GetRect(GUI_RECT* pRect) {
  WM_GetClientRect(pRect);
  GUI__ReduceRect(pRect, pRect, 2);
}

void WIDGET_SetDefaultEffect_3D(void) {
  WIDGET_SetDefaultEffect(&WIDGET_Effect_3D);
}

/*********************************************************************
*
*       Effect tables --- Mainly function pointers
*
**********************************************************************
*/
const WIDGET_EFFECT WIDGET_Effect_3D = {
  WIDGET_EFFECT_3D_DrawUp, WIDGET_EFFECT_3D_DrawDown,
  WIDGET_EFFECT_3D_DrawUpRect, WIDGET_EFFECT_3D_DrawDownRect,
  WIDGET_EFFECT_3D_GetRect, 2
};


#else                            /* Avoid problems with empty object modules */
  void WIDGET_3D_C(void) {}
#endif /* GUI_WINSUPPORT */




