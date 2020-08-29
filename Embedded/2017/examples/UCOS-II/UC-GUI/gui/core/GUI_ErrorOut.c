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
File        : GUI_ErrorOut.C
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


void GUI_ErrorOut(const char *s) { GUI_X_ErrorOut(s); }

void GUI_ErrorOut1(const char *s, int p0) {
  char ac[50 + 10];
  char* sOut = ac;
  strncpy(ac, s, 49);
  sOut += strlen(sOut);
  GUI__AddSpaceHex(p0, 8, &sOut);
  GUI_ErrorOut(ac);
}

void GUI_ErrorOut2(const char *s, int p0, int p1) {
  char ac[50 + 20];
  char* sOut = ac;
  strncpy(ac, s, 49);
  sOut += strlen(sOut);
  GUI__AddSpaceHex(p0, 8, &sOut);
  GUI__AddSpaceHex(p1, 8, &sOut);
  GUI_ErrorOut(ac);
}

void GUI_ErrorOut3(const char *s, int p0, int p1, int p2) {
  char ac[50 + 30];
  char* sOut = ac;
  strncpy(ac, s, 49);
  sOut += strlen(sOut);
  GUI__AddSpaceHex(p0, 8, &sOut);
  GUI__AddSpaceHex(p1, 8, &sOut);
  GUI__AddSpaceHex(p2, 8, &sOut);
  GUI_ErrorOut(ac);
}

void GUI_ErrorOut4(const char *s, int p0, int p1, int p2, int p3) {
  char ac[50 + 40];
  char* sOut = ac;
  strncpy(ac, s, 49);
  sOut += strlen(sOut);
  GUI__AddSpaceHex(p0, 8, &sOut);
  GUI__AddSpaceHex(p1, 8, &sOut);
  GUI__AddSpaceHex(p2, 8, &sOut);
  GUI__AddSpaceHex(p3, 8, &sOut);
  GUI_ErrorOut(ac);
}










