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
File        : GUI_Warn.C
Purpose     : Logging (used only at higher debug levels)
---------------------------END-OF-HEADER------------------------------
*/

#include <stdio.h>
#include <string.h>
#include "GUI_Protected.h"
#include "GUI_X.H"


/*********************************************************************
*
*      Logging: Publics referenced by upper layers
*
**********************************************************************

Note:
  These routines are needed only in higher debug levels.
*/

void GUI_X_Warn(const char *s)
{
	Uart_Printf/*uHALr_printf*/(s);
}

void GUI_Warn(const char *s) { GUI_X_Warn(s); }

void GUI_Warn1(const char *s, int p0) {
  char ac[50 + 10];
  char* sOut = ac;
  strncpy(ac, s, 49);
  sOut += strlen(sOut);
  GUI__AddSpaceHex(p0, 8, &sOut);
  GUI_Warn(ac);
}

void GUI_Warn2(const char *s, int p0, int p1) {
  char ac[50 + 20];
  char* sOut = ac;
  strncpy(ac, s, 49);
  sOut += strlen(sOut);
  GUI__AddSpaceHex(p0, 8, &sOut);
  GUI__AddSpaceHex(p1, 8, &sOut);
  GUI_Warn(ac);
}

void GUI_Warn3(const char *s, int p0, int p1, int p2) {
  char ac[50 + 30];
  char* sOut = ac;
  strncpy(ac, s, 49);
  sOut += strlen(sOut);
  GUI__AddSpaceHex(p0, 8, &sOut);
  GUI__AddSpaceHex(p1, 8, &sOut);
  GUI__AddSpaceHex(p2, 8, &sOut);
  GUI_Warn(ac);
}

void GUI_Warn4(const char *s, int p0, int p1, int p2, int p3) {
  char ac[50 + 40];
  char* sOut = ac;
  strncpy(ac, s, 49);
  sOut += strlen(sOut);
  GUI__AddSpaceHex(p0, 8, &sOut);
  GUI__AddSpaceHex(p1, 8, &sOut);
  GUI__AddSpaceHex(p2, 8, &sOut);
  GUI__AddSpaceHex(p3, 8, &sOut);
  GUI_Warn(ac);
}










