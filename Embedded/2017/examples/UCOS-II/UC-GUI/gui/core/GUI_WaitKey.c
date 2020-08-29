/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 2002         SEGGER Microcontroller Systeme GmbH        *
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
File        : GUI_WaitKey.c
Purpose     : Implementation of GUI_WaitKey
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.H"

int GUI_WaitKey(void) {
  int r;
  do {
    r =  GUI_GetKey();
    if (r)
      break;
    GUI_Exec();
  } while (1);
  return r;
}

