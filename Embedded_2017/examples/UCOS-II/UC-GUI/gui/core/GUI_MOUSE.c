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
File        : GUI_MOUSE.C
Purpose     : Generic mouse routines
----------------------------------------------------------------------
*/


#include <string.h>           /* memcmp */
#include "LCD_Private.H"      /* private modul definitions & config */
#include "GUI_Protected.h"

/*********************************************************************
*
*          Config defaults
*
**********************************************************************
*/

#ifndef GUI_MOUSE_SWAP_XY    /* Is XY of touch swapped ? */
  #define GUI_MOUSE_SWAP_XY 0
#endif

#ifndef GUI_MOUSE_MIRROR_X
  #define GUI_MOUSE_MIRROR_X 0
#endif

#ifndef GUI_MOUSE_MIRROR_Y
  #define GUI_MOUSE_MIRROR_Y 0
#endif

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static GUI_HID_STATE _State;

/*********************************************************************
*
*              GUI_MOUSE_StoreState
*
**********************************************************************
*/

void GUI_MOUSE_StoreState(const GUI_HID_STATE *pState) {
  #if GUI_SUPPORT_TOUCH
    if (memcmp(pState, &_State, sizeof(_State))) {
      _State = *pState;
      GUI_HID_StoreState(pState);
    }
  #else
    GUI_USE_PARA(pState);
  #endif
}


