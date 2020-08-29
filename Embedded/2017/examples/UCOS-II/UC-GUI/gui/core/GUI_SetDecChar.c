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
File        : GUI_SetDecChar.C
Purpose     : Routines to set the character used for decimal point
----------------------------------------------------------------------
*/

#include "GUI_Protected.H"
#include "GUIDebug.h"

/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/


/*********************************************************************
*
*     GUI_SetDecChar
*/

char GUI_SetDecChar(char c) {
  char r = GUI_DecChar;
  GUI_DecChar = c;
  return r;
}

char GUI_GetDecChar(void) {
  return GUI_DecChar;
}



