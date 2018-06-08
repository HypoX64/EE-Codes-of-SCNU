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
File        : GUI_SaveContext.c
Purpose     : Code to save and restore GUI context
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.H"
#include "GUIDebug.h"

/*********************************************************************
*
*        Public code
*
**********************************************************************
*/

void GUI_SaveContext   (      GUI_CONTEXT* pContext) {
  *pContext = GUI_Context;
}
void GUI_RestoreContext(const GUI_CONTEXT* pContext) {
  GUI_Context = *pContext;
}


