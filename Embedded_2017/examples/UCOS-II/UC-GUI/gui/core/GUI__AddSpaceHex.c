/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*           (C) 1996    SEGGER Microcontroller Systeme GmbH          *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

----------------------------------------------------------------------
File        : GUI__AddSpaceHex.C
Purpose     : Internal function
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "GUI_Protected.h"

/*********************************************************************
*
*        static code
*
**********************************************************************
*/
void GUI__AddSpaceHex(U32 v, U8 Len, char**ps) {
  char* s = *ps;
  *s++ = ' ';
  *ps = s;
  GUI_AddHex(v, Len, ps);
}











