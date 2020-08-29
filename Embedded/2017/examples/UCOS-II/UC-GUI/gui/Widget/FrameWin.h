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
File        : FrameWin.H
Purpose     : Frame window include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef FRAMEWIN_H
#define FRAMEWIN_H

#include "WM.H"
#if GUI_WINSUPPORT
#include "Dialog.h"      /* Req. for Create indirect data structure */


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
#define FRAMEWIN_CF_MOVEABLE   (1<<4)
#define FRAMEWIN_SF_MOVEABLE   (1<<4)


/*
      *************************************************************
      *                                                           *
      *                         Types                             *
      *                                                           *
      *************************************************************

*/
typedef WM_HMEM FRAMEWIN_Handle;

/*
      *************************************************************
      *                                                           *
      *                 Standard member functions                 *
      *                                                           *
      *************************************************************
*/

#define FRAMEWIN_EnableMemdev(hObj)  WM_EnableMemdev(hObj)
#define FRAMEWIN_DisableMemdev(hObj) WM_DisableMemdev(hObj)
#define FRAMEWIN_Delete(hObj)        WM_DeleteWindow(hObj)
#define FRAMEWIN_Paint(hObj)         WM_Paint(hObj)
#define FRAMEWIN_Invalidate(hObj)    WM_InvalidateWindow(hObj)

/*
      *************************************************************
      *                                                           *
      *                 Member functions                          *
      *                                                           *
      *************************************************************

*/
FRAMEWIN_Handle FRAMEWIN_Create       (const char* pTitle, WM_CALLBACK* cb, int Flags,
                                       int x0, int y0, int xsize, int ysize);
FRAMEWIN_Handle FRAMEWIN_CreateAsChild(int x0, int y0, int xsize, int ysize, WM_HWIN hParent,
                                       const char* pText, WM_CALLBACK* cb, int Flags);
void          FRAMEWIN_SetFont        (FRAMEWIN_Handle pObj, const GUI_FONT* pFont);
void          FRAMEWIN_SetBarColor    (FRAMEWIN_Handle pObj, int index, GUI_COLOR color);
void          FRAMEWIN_SetTextColor   (FRAMEWIN_Handle pObj, GUI_COLOR color);
void          FRAMEWIN_SetText        (FRAMEWIN_Handle pObj, const char* s);
void          FRAMEWIN_SetTextAlign   (FRAMEWIN_Handle pObj, int Align);
void          FRAMEWIN_SetTextPos     (FRAMEWIN_Handle pObj, int XOff, int YOff);
void          FRAMEWIN_SetActive      (FRAMEWIN_Handle hObj, int State);
void          FRAMEWIN_SetClientColor (FRAMEWIN_Handle hObj, GUI_COLOR Color);

/*
      *************************************************************
      *
      *                 Global functions
      *
      *************************************************************

*/
void            FRAMEWIN_SetDefaultFont       (const GUI_FONT* pFont);
const GUI_FONT* FRAMEWIN_GetDefaultFont       (void);
void            FRAMEWIN_SetDefaultBarColor   (int Index, GUI_COLOR Color);
int             FRAMEWIN_GetDefaultCaptionSize(void);
void            FRAMEWIN_SetDefaultCaptionSize(int DefaultCaptionSize);
int             FRAMEWIN_GetDefaultBorderSize (void);
void            FRAMEWIN_SetDefaultBorderSize (int DefaultBorderSize);

#endif
#endif   /* FRAMEWIN_H */
