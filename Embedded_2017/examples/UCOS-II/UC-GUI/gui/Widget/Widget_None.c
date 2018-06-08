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
*       WIDGET_EFFECT_None_ ...

  The following are called in case of disabled effects
*/
void WIDGET_EFFECT_None_DrawDown(void) { }
void WIDGET_EFFECT_None_DrawUp(void) { }
void WIDGET_EFFECT_None_DrawDownRect(const GUI_RECT* pRect) {
  GUI_USE_PARA(pRect);
}
void WIDGET_EFFECT_None_DrawUpRect(const GUI_RECT* pRect) {
  GUI_USE_PARA(pRect);
}
void WIDGET_EFFECT_None_GetRect(GUI_RECT * pRect) {
  WM_GetClientRect(pRect);
}


void WIDGET_SetDefaultEffect_None(void) {
  WIDGET_SetDefaultEffect(&WIDGET_Effect_None);
}


/*********************************************************************
*
*       Effect tables --- Mainly function pointers
*
**********************************************************************
*/

const WIDGET_EFFECT WIDGET_Effect_None = {
  WIDGET_EFFECT_None_DrawUp, WIDGET_EFFECT_None_DrawDown,
  WIDGET_EFFECT_None_DrawUpRect, WIDGET_EFFECT_None_DrawDownRect,
  WIDGET_EFFECT_None_GetRect, 0
};


#else                            /* Avoid problems with empty object modules */
  void WIDGET_None_C(void) {}
#endif /* GUI_WINSUPPORT */




