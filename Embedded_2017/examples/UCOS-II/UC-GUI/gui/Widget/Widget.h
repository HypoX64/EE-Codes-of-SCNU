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
File        : WIDGET.h
Purpose     : emWin widget
---------------------------END-OF-HEADER------------------------------
*/

#ifndef WIDGET_H        /* Avoid multiple inclusion  */
#define WIDGET_H

#include "WM.H"

#if GUI_WINSUPPORT
#include "SCROLLBAR.H"

/*********************************************************************
*
*           defines
*
**********************************************************************
*/


/*********************************************************************
*
*       States
*/

#define WIDGET_STATE_FOCUS              (1<<0)
#define WIDGET_STATE_CHILD_HAS_FOCUS    (1<<1)
#define WIDGET_STATE_ENABLED            (1<<2)
#define WIDGET_STATE_VERTICAL           (1<<3)
#define WIDGET_STATE_FOCUSSABLE         (1<<4)

#define WIDGET_STATE_USER0              (1<<8)    /* Freely available for derived widget */
#define WIDGET_STATE_USER1              (1<<9)    /* Freely available for derived widget */
#define WIDGET_STATE_USER2              (1<<10)   /* Freely available for derived widget */

/*********************************************************************
*
*       Create flags
*/
#define WIDGET_CF_VERTICAL     WIDGET_STATE_VERTICAL



/*********************************************************************
*
*           typedefs
*
**********************************************************************
*/

typedef struct {
  void  (*pfDrawUp)(void);
  void  (*pfDrawDown)(void);
  void  (*pfDrawUpRect)  (const GUI_RECT *pRect);
  void  (*pfDrawDownRect)(const GUI_RECT *pRect);
  void  (*pfGetRect)(GUI_RECT *pRect);
  int EffectSize;
} WIDGET_EFFECT;

typedef struct {
  WM_Obj      Win;
  const WIDGET_EFFECT* pEffect;
  I16 Id;
  U16 State;
} WIDGET;

/*********************************************************************
*
*           Global data
*
**********************************************************************
*/
extern const WIDGET_EFFECT WIDGET_Effect_3D;
extern const WIDGET_EFFECT WIDGET_Effect_None;
extern const WIDGET_EFFECT WIDGET_Effect_Simple;

/*********************************************************************
*
*           Internal API routines
*
**********************************************************************
*/

GUI_COLOR WIDGET__GetBkColor(WM_HWIN hObj);
void      WIDGET__GetClientRect(WIDGET* pWidget, GUI_RECT* pRect);
void      WIDGET__GetInsideRect(WIDGET* pWidget, GUI_RECT* pRect);
void      WIDGET__EFFECT_DrawDownRect(WIDGET* pWidget, GUI_RECT* pRect);
void      WIDGET__EFFECT_DrawDown(WIDGET* pWidget);
void      WIDGET__EFFECT_DrawUpRect(WIDGET* pWidget, GUI_RECT* pRect);
void      WIDGET__Init(WIDGET* pWidget, U16 State);
int       WIDGET__IsEnabled(WIDGET* pObj);
void      WIDGET__DrawFocusRect(WIDGET* pWidget, const GUI_RECT* pRect, int Dist);
void      WIDGET__DrawVLine(WIDGET* pWidget, int x, int y0, int y1);
void      WIDGET__FillRectEx(WIDGET* pWidget, const GUI_RECT* pRect);
int       WIDGET__GetWindowSizeX(WM_HWIN hWin);
int       WIDGET__GetXSize(const WIDGET* pWidget);
int       WIDGET__GetYSize(const WIDGET* pWidget);
void      WIDGET__SetScrollState(WM_HWIN hWin, const WM_SCROLL_STATE* pVState, const WM_SCROLL_STATE* pState);

/*********************************************************************
*
*           API routines
*
**********************************************************************
*/
void WIDGET_SetState      (WM_HWIN hObj, int State);
void WIDGET_AndState      (WM_HWIN hObj, int State);
void WIDGET_OrState       (WM_HWIN hObj, int State);
void WIDGET_Enable        (WM_HWIN hObj);
void WIDGET_Disable       (WM_HWIN hObj);
int  WIDGET_HandleActive  (WM_HWIN hObj, WM_MESSAGE* pMsg);

void WIDGET_EFFECT_3D_DrawUp(void);
void WIDGET_EFFECT_3D_DrawDown(void);
void WIDGET_EFFECT_3D_DrawDownRect(const GUI_RECT* pRect);




void WIDGET_SetDefaultEffect(const WIDGET_EFFECT* pEffect);
void WIDGET_SetDefaultEffect_None(void);
void WIDGET_SetDefaultEffect_3D(void);
void WIDGET_SetDefaultEffect_Simple(void);

#endif /* GUI_WINSUPPORT */
#endif   /* SLIDER_H */




