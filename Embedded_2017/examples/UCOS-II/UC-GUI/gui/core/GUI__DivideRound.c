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
File        : GUI__DivideRound.C
Purpose     : Implementation of GUI__DivideRound
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.H"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/


/*********************************************************************
*
*       GUI__DivideRound

  This routine is used internally for computations. Primary goal is
  to minimize the effects of rounding which occur if we simply
  divide.
*/
int GUI__DivideRound(int a, int b) {
  int r = 0;
  if (b) {
    r = ((a +b/2) / b);
  }
  return r;
}












