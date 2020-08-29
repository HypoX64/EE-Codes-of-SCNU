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
File        : GUIPen.C
Purpose     : Getting / Setting pen attributes
---------------------------END-OF-HEADER------------------------------
*/


#include "GUI_Protected.H"


/*      *********************************
        *                               *
        *      Get / Set Attributes     *
        *                               *
        *********************************
*/

U8        GUI_GetPenSize   (void) {
  U8 r;
  GUI_LOCK();
  r = GUI_Context.PenSize;
  GUI_UNLOCK();
  return r;
}

U8        GUI_GetPenShape  (void) {
  U8 r;
  GUI_LOCK();
  r = GUI_Context.PenShape;
  GUI_UNLOCK();
  return r;
}


/*
        *********************************************************
        *                                                       *
        *       Set Pen attributes                              *
        *                                                       *
        *********************************************************

Purpose:  Assign color/index to foreground/ background

*/
U8 GUI_SetPenSize   (U8 PenSize) {
  U8 r;
  GUI_LOCK();
    r = GUI_Context.PenSize;
    GUI_Context.PenSize = PenSize;
  GUI_UNLOCK();
  return r;
}

U8 GUI_SetPenShape  (U8 PenShape) {
  U8 r;
  GUI_LOCK();
    r = GUI_Context.PenShape;
    GUI_Context.PenShape = PenShape;
  GUI_UNLOCK();
  return r;
}




