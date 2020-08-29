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
File        : RADIO.H
Purpose     : RADIO include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef RADIO_H
#define RADIO_H

#include "WM.H"
#include "Dialog_Intern.h"      /* Req. for Create indirect data structure */

#if GUI_WINSUPPORT

/*********************************************************************
*
*            Defaults for public configuration switches
*
**********************************************************************

The following are defaults for config switches which affect the
interface specified in this module
*/

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


/*********************************************************************
*
*                         Public Types
*
**********************************************************************

*/
typedef WM_HMEM RADIO_Handle;

/*********************************************************************
*
*                 Create functions
*
**********************************************************************
*/

RADIO_Handle RADIO_Create        (int x0, int y0, int xsize, int ysize, WM_HWIN hParent, int Id, int Flags, unsigned Para);
RADIO_Handle RADIO_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);

/*********************************************************************
*
*                 Member functions
*
**********************************************************************
*/

void RADIO_SetValue(RADIO_Handle hObj, int v);
void RADIO_Inc(RADIO_Handle hObj);
void RADIO_Dec(RADIO_Handle hObj);

/*********************************************************************
*
*                 Query state
*
**********************************************************************
*/
int RADIO_GetValue(RADIO_Handle hObj);


#endif   /* if GUI_WINSUPPORT */
#endif   /* RADIO_H */
