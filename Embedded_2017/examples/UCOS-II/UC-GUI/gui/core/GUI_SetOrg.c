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
File        : GUI_SetOrg.C
Purpose     : emWin GSC, defines the GUI_SetOrg function
---------------------------END-OF-HEADER------------------------------
*/


#include <stddef.h>           /* needed for definition of NULL */

#include "GUI_Protected.H"
#include "GUIDebug.h"


/***********************************************************
*
*                 GUI_SetOrg
*
************************************************************

*/

void GUI_SetOrg(int x, int y) {
  GUI_LOCK();
  LCD_L0_SetOrg(x, y);
  GUI_UNLOCK();
}









