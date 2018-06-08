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
File        : TEXT.H
Purpose     : TEXT include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef TEXT_H
#define TEXT_H

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
#define TEXT_CF_LEFT    GUI_TA_LEFT
#define TEXT_CF_RIGHT   GUI_TA_RIGHT
#define TEXT_CF_HCENTER GUI_TA_HCENTER

#define TEXT_CF_VCENTER GUI_TA_VCENTER
#define TEXT_CF_TOP     GUI_TA_TOP
#define TEXT_CF_BOTTOM  GUI_TA_BOTTOM


/*********************************************************************
*
*       Public Types
*
**********************************************************************

*/
typedef WM_HMEM TEXT_Handle;

/*********************************************************************
*
*       Standard member functions
*
**********************************************************************
*/

#define TEXT_EnableMemdev(hObj)  WM_EnableMemdev(hObj)
#define TEXT_DisableMemdev(hObj) WM_DisableMemdev(hObj)
#define TEXT_Delete(hObj)        WM_DeleteWindow(hObj)
#define TEXT_Paint(hObj)         WM_Paint(hObj)
#define TEXT_Invalidate(hObj)    WM_InvalidateWindow(hObj)

/*********************************************************************
*
*       Create functions
*
**********************************************************************
*/

TEXT_Handle TEXT_Create        (int x0, int y0, int xsize, int ysize, int Id, int Flags, const char * s, int Align);
TEXT_Handle TEXT_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);

/*********************************************************************
*
*       Member functions
*
**********************************************************************
*/

/* Methods changing properties */
/* Note: These are just examples. The actual methods available for the
   widget will depend on the type of widget. */
void         TEXT_SetFont     (TEXT_Handle pObj, const GUI_FONT* pFont);
void         TEXT_SetText     (TEXT_Handle pObj, const char* s);
void         TEXT_SetTextAlign(TEXT_Handle pObj, int Align);
void         TEXT_SetTextPos  (TEXT_Handle pObj, int XOff, int YOff);

/*********************************************************************
*
*       Global functions
*
**********************************************************************
*/

void            TEXT_SetDefaultFont(const GUI_FONT* pFont);
const GUI_FONT* TEXT_GetDefaultFont(void);

#endif   /* if GUI_WINSUPPORT */
#endif   /* TEXT_H */
