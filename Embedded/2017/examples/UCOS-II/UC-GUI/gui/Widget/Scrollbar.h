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
File        : SCROLLBAR.H
Purpose     : SCROLLBAR include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include "WM.H"
#include "Dialog_Intern.h"      /* Req. for Create indirect data structure */

#if GUI_WINSUPPORT

/************************************************************
*
*       #defines
*
*************************************************************
*/

/************************************************************
*
*       Create / Status flags
*/
#define SCROLLBAR_CF_VERTICAL     WIDGET_CF_VERTICAL
#define SCROLLBAR_CF_FOCUSSABLE   WIDGET_STATE_FOCUSSABLE

/*********************************************************************
*
*                         Public Types
*
**********************************************************************

*/
typedef WM_HMEM SCROLLBAR_Handle;

/*********************************************************************
*
*                 Create functions
*
**********************************************************************
*/

SCROLLBAR_Handle SCROLLBAR_Create (int x0, int y0, int xsize, int ysize, WM_HWIN hParent, int Id, int WinFlags, int SpecialFlags);
SCROLLBAR_Handle SCROLLBAR_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);
SCROLLBAR_Handle SCROLLBAR_CreateAttached(WM_HWIN hParent, int SpecialFlags);

/*********************************************************************
*
*                 Member functions
*
**********************************************************************
*/

/* Methods changing properties */

void SCROLLBAR_AddValue    (SCROLLBAR_Handle hObj, int Add);
void SCROLLBAR_Dec         (SCROLLBAR_Handle hObj);
void SCROLLBAR_Inc         (SCROLLBAR_Handle hObj);
void SCROLLBAR_SetNumItems (SCROLLBAR_Handle hObj, int NumItems);
void SCROLLBAR_SetPageSize (SCROLLBAR_Handle hObj, int PageSize);
void SCROLLBAR_SetValue    (SCROLLBAR_Handle hObj, int v);
void SCROLLBAR_SetWidth    (SCROLLBAR_Handle hObj, int Width);

/*********************************************************************
*
*                 Query state
*
**********************************************************************
*/
int SCROLLBAR_GetValue(SCROLLBAR_Handle hObj);

#endif   /* if GUI_WINSUPPORT */
#endif   /* SCROLLBAR_H */
