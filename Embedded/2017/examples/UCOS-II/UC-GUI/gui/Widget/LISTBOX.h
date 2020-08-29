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
File        : LISTBOX.H
Purpose     : Multiple choice object include
----------------------------------------------------------------------
Version-Date---Author-Explanation
----------------------------------------------------------------------
0.50    990909 RS     First beta release.
----------------------------------------------------------------------
Open items:
None
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef LISTBOX_H
#define LISTBOX_H

#include "WM.H"
#include "Dialog_Intern.h"      /* Req. for Create indirect data structure */

#if GUI_WINSUPPORT


/************************************************************
*
*       States
*/

#define LISTBOX_STATE_INACTIVE            0

typedef WM_HMEM LISTBOX_Handle;

/*********************************************************************
*
*                 Standard member functions
*
**********************************************************************
*/

#define LISTBOX_EnableMemdev(hObj)  WM_EnableMemdev(hObj)
#define LISTBOX_DisableMemdev(hObj) WM_DisableMemdev(hObj)
#define LISTBOX_Delete(hObj)        WM_DeleteWindow(hObj)
#define LISTBOX_Paint(hObj)         WM_Paint(hObj)
#define LISTBOX_Invalidate(hObj)    WM_InvalidateWindow(hObj)

/*********************************************************************
*
*                 Create functions
*
**********************************************************************
*/

LISTBOX_Handle LISTBOX_Create        (const GUI_ConstString* ppText, int x0, int y0, int xsize, int ysize, int Flags);
LISTBOX_Handle LISTBOX_CreateAsChild (const GUI_ConstString* ppText, WM_HWIN hWinParent, int x0, int y0, int xsize, int ysize, int Flags);
LISTBOX_Handle LISTBOX_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);

/*********************************************************************
*
*                 Member functions
*
**********************************************************************
*/
void         LISTBOX_SetFont     (LISTBOX_Handle hObj, const GUI_FONT* pfont);
void         LISTBOX_SetBackColor(LISTBOX_Handle hObj, int index, GUI_COLOR color);
void         LISTBOX_SetTextColor(LISTBOX_Handle hObj, int index, GUI_COLOR color);
void         LISTBOX_SetText     (LISTBOX_Handle hObj, const GUI_ConstString* ppText);

/* Set / Query selection */
void         LISTBOX_IncSel      (LISTBOX_Handle hObj);
void         LISTBOX_DecSel      (LISTBOX_Handle hObj);
void         LISTBOX_SetSel      (LISTBOX_Handle hObj, int Sel);
int          LISTBOX_GetSel      (LISTBOX_Handle hObj);
void         LISTBOX_AddKey      (LISTBOX_Handle hObj, int Key);


/*********************************************************************
*
*                 Global functions
*
**********************************************************************
*/
const GUI_FONT* LISTBOX_GetDefaultFont(void);
void            LISTBOX_SetDefaultFont(const GUI_FONT* pFont);


#endif   /* GUI_WINSUPPORT */
#endif   /* LISTBOX_H */
