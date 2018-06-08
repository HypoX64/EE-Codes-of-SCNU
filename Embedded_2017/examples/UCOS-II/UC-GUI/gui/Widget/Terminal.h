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
File        : TERMINAL.H
Purpose     : TERMINAL include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef TERMINAL_H
#define TERMINAL_H

#include "GUI.H"

#if GUI_WINSUPPORT
#include "WM.H"
#include "Dialog_Intern.h"      /* Req. for Create indirect data structure */


/*********************************************************************
*
*            Defaults for public configuration switches
*
**********************************************************************

The following are defaults for config switches which affect the
interface specified in this module
*/
/* Default for ... */
#ifndef TERMINAL_XXX_DEFAULT
  #define TERMINAL_XXX_DEFAULT xx
#endif


/*********************************************************************
*
*                         Public Types
*
**********************************************************************

*/
typedef WM_HMEM TERMINAL_Handle;

/*********************************************************************
*
*                 Standard member functions
*
**********************************************************************
*/

#define TERMINAL_EnableMemdev(hObj)  WM_EnableMemdev(hObj)
#define TERMINAL_DisableMemdev(hObj) WM_DisableMemdev(hObj)
#define TERMINAL_Delete(hObj)        WM_DeleteWindow(hObj)
#define TERMINAL_Paint(hObj)         WM_Paint(hObj)


/*********************************************************************
*
*                 Create functions
*
**********************************************************************
*/

TERMINAL_Handle TERMINAL_Create(    int x0, int y0, int xsize, int ysize,
                                    int MaxLen,
                                    int Flags);
TERMINAL_Handle TERMINAL_CreateAsChild(
                                    int x0, int y0, int xsize, int ysize,
                                    WM_HWIN hWinParent,
                                    int MaxLen,
                                    int Flags);

/*********************************************************************
*
*                 Member functions
*
**********************************************************************
*/

/* Methods changing properties */
/* Note: These are just examples. The actual methods available for the
   widget will depend on the type of widget. */
void         TERMINAL_Add(TERMINAL_Handle hObj, const char* sAdd);
void         TERMINAL_SetFont     (TERMINAL_Handle pObj, const GUI_FONT* pFont);
void         TERMINAL_SetText     (TERMINAL_Handle pObj, const char* s);
void         TERMINAL_SetTextAlign(TERMINAL_Handle pObj, int Align);
void         TERMINAL_SetTextPos  (TERMINAL_Handle pObj, int XOff, int YOff);

/* Get data */
void TERMINAL_GetText(TERMINAL_Handle hObj, char* sDest, int MaxLen);

#endif /* GUI_WINSUPPORT */

#endif   /* TERMINAL_H */
