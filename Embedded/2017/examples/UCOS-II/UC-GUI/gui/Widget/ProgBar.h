/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              �C/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : Progbar.H
Purpose     : Progressbar include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef PROGBAR_H        /* Avoid multiple inclusion  */
#define PROGBAR_H

#include "WM.h"
#include "Dialog_Intern.h"      /* Req. for Create indirect data structure */

#if GUI_WINSUPPORT

typedef WM_HMEM PROGBAR_Handle;


/************************************************************
*
*           Create
*
*************************************************************
*/

PROGBAR_Handle PROGBAR_Create(int x0, int y0, int xsize, int ysize, int Flags);
PROGBAR_Handle PROGBAR_CreateEx(int x0, int y0, int xsize, int ysize, WM_HWIN hParent, int Id, int Flags);
PROGBAR_Handle PROGBAR_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);

/************************************************************
*
*                 Standard member functions
*
*************************************************************
*/

#define PROGBAR_EnableMemdev(hObj)  WM_EnableMemdev(hObj)
#define PROGBAR_DisableMemdev(hObj) WM_DisableMemdev(hObj)
#define PROGBAR_Delete(hObj)        WM_DeleteWindow(hObj)
#define PROGBAR_Paint(hObj)         WM_Paint(hObj)


/************************************************************
*
*           Individual member functions
*
*************************************************************
*/

void            PROGBAR_SetBarColor (PROGBAR_Handle hObj, int index, GUI_COLOR color);
void            PROGBAR_SetFont     (PROGBAR_Handle hObj, const GUI_FONT* pfont);
void            PROGBAR_SetMinMax(PROGBAR_Handle hObj, int Min, int Max);
void            PROGBAR_SetText     (PROGBAR_Handle hObj, const char* s);
void            PROGBAR_SetTextAlign(PROGBAR_Handle hObj, int Align);
void            PROGBAR_SetTextColor(PROGBAR_Handle hObj, int index, GUI_COLOR color);
void            PROGBAR_SetTextPos  (PROGBAR_Handle hObj, int XOff, int YOff);
void            PROGBAR_SetValue    (PROGBAR_Handle hObj, int v);

#endif   /* GUI_WINSUPPORT */
#endif   /* PROGBAR_H */
