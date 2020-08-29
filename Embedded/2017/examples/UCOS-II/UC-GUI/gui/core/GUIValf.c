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
File        : GUIValF.C
Purpose     : Displaying floating point values
----------------------------------------------------------------------
Version-Date---Author-Explanation
----------------------------------------------------------------------
1.00.00 990322 RS     First release   
----------------------------------------------------------------------
Known problems or limitations with current version
----------------------------------------------------------------------
None.
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.H"
#include "math.h"

/*
	*******************************************
	*                                         *
	*          Helper functions               *
	*                                         *
	*******************************************
*/

static void _DispFloatFix(float f, char Len, char Decs, int DrawPlusSign) {
  f *= GUI_Pow10[Decs];
  f += 0.5;
  f = (float) floor (f);
  if (DrawPlusSign)
    GUI_DispSDecShift((long)f, Len, Decs);
  else
    GUI_DispDecShift((long)f, Len, Decs);
}

/*
	*******************************************
	*                                         *
	*     optional sign display routines      *
	*                                         *
	*******************************************
*/

void GUI_DispFloatFix(float f, char Len, char Decs) {
  _DispFloatFix(f, Len, Decs, 0);
}

void GUI_DispFloatMin(float f, char Fract) {
  char Len;
  Len = GUI_Long2Len((long)f);
  _DispFloatFix(f, (char)(Len+Fract+1), (char)Fract, 0);
}

void GUI_DispFloat(float f, char Len) {
  int Decs;
  Decs =  Len - GUI_Long2Len((long)f)-1;
  if (Decs<0)
    Decs =0;
  _DispFloatFix(f, Len, (char)Decs, 0);
}

/*
	*******************************************
	*                                         *
	*    Signed display routines              *
	*                                         *
	*******************************************
*/

void GUI_DispSFloatFix(float f, char Len, char Fract) {
  _DispFloatFix (f, Len, Fract, 1);
}

void GUI_DispSFloatMin(float f, char Fract) {
  char Len;
  Len = GUI_Long2Len((long)f);
  if (f>0)
    Len++;
  _DispFloatFix(f, (char)(Len+Fract+1), (char)Fract, 1);
}
