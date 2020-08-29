/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*      (c) 1996-2002    SEGGER Microcontroller Systeme GmbH          *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

**** emWin/GSC Grafical user interface for embedded applications ****
emWin is protected by international copyright laws. Knowledge of the
source code may not be used to write a similar product. This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUITOUCH.C
Purpose     : Touch screen manager
----------------------------------------------------------------------
This module handles the touch screen. It is configured in the file
GUITouch.conf.h (Should be located in the Config\ directory).
----------------------------------------------------------------------
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LCD_Private.H"      /* private modul definitions & config */
#include "GUI_Protected.h"


/*********************************************************************
*
*       static data
*
**********************************************************************
*/

GUI_HID_STATE _State;


/*********************************************************************
*
*              GUI_TOUCH_GetState
*
**********************************************************************

*/

int GUI_TOUCH_GetState(GUI_HID_STATE *pState) {
  *pState = _State;
  return (_State.Pressed != 0) ? 1 : 0;
}


void GUI_TOUCH_StoreState(int x, int y) {
  #if GUI_SUPPORT_TOUCH
    static int xPrev=-1, yPrev=-1;
    _State.x       = xPrev;
    _State.y       = yPrev;
    _State.Pressed = ((x==-1) | (xPrev==-1))  ? 0 : 1;
    if ((xPrev != x) || (yPrev != y)) {
      GUI_HID_StoreState(&_State);
    }
    xPrev = x;
    yPrev = y;
  #else
    GUI_USE_PARA(x);
    GUI_USE_PARA(y);
  #endif
}




