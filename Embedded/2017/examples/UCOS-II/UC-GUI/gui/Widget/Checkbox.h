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
File        : CHECKBOX.H
Purpose     : CHECKBOX include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "WM.H"
#include "Dialog.h"      /* Req. for Create indirect data structure */

#if GUI_WINSUPPORT

/*********************************************************************
*
*            Defaults for public configuration switches
*
**********************************************************************

The following are defaults for config switches which affect the
interface specified in this module
*/
/* Default for ... */
#ifndef CHECKBOX_XXX_DEFAULT
  #define CHECKBOX_XXX_DEFAULT xx
#endif

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

#define CHECKBOX_STATE_CHECKED              WIDGET_STATE_USER0

/*********************************************************************
*
*                         Public Types
*
**********************************************************************

*/
typedef WM_HMEM CHECKBOX_Handle;

/*********************************************************************
*
*                 Create functions
*
**********************************************************************
*/

CHECKBOX_Handle CHECKBOX_Create        (int x0, int y0, int xsize, int ysize, WM_HWIN hParent, int Id, int Flags);
CHECKBOX_Handle CHECKBOX_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);

/*********************************************************************
*
*                 Member functions
*
**********************************************************************
*/

void CHECKBOX_Check(CHECKBOX_Handle hObj);
void CHECKBOX_Uncheck(CHECKBOX_Handle hObj);

/*********************************************************************
*
*                 Query state
*
**********************************************************************
*/
int CHECKBOX_IsChecked(CHECKBOX_Handle hObj);


#endif   /* if GUI_WINSUPPORT */
#endif   /* CHECKBOX_H */
