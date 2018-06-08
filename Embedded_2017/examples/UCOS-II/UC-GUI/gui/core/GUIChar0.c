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
File        : GUIChar0.C
Purpose     : Implementation of character and string services
----------------------------------------------------------------------
Version-Date---Author-Explanation
---------------------------END-OF-HEADER------------------------------
*/


#include <stddef.h>           /* needed for definition of NULL */
#include "GUI.H"
 

int GUI_GetFontSizeYOf(const GUI_FONT* pFont) {
  if (!pFont)
    pFont = GUI_DEFAULT_FONT;
  return pFont->YDist;
}

