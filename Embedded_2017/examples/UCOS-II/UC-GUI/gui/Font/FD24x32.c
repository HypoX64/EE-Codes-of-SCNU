/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              �C/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : FD24x32.C
Purpose     : Implementation of the non-proportional 24 by 32 digit
Height      : 32
---------------------------END-OF-HEADER------------------------------
*/


#include "GUI.H"

#ifndef GUI_FLASH
  #define GUI_FLASH
#endif

GUI_FLASH const U8 acFont24x32[15][96] = {
  {
   ________,_XXXXXXX,________,
   _______X,XXXXXXXX,XX______,
   ______XX,XXXXXXXX,XXX_____,
   _____XXX,XXXXXXXX,XXXX____,
   ____XXXX,XXX___XX,XXXXX___,
   ____XXXX,X_______,XXXXX___,
   ___XXXXX,________,_XXXXX__,
   ___XXXXX,________,_XXXXX__,
   ___XXXXX,________,_XXXXX__,
   __XXXXX_,________,__XXXXX_,
   __XXXXX_,________,__XXXXX_,
   __XXXXX_,________,__XXXXX_,
   __XXXXX_,________,__XXXXX_,
   __XXXXX_,________,__XXXXX_,
   __XXXXX_,________,__XXXXX_,
   __XXXXX_,________,__XXXXX_,
   __XXXXX_,________,__XXXXX_,
   __XXXXX_,________,__XXXXX_,
   __XXXXX_,________,__XXXXX_,
   __XXXXX_,________,__XXXXX_,
   __XXXXX_,________,__XXXXX_,
   __XXXXX_,________,__XXXXX_,
   __XXXXX_,________,__XXXXX_,
   ___XXXXX,________,_XXXXX__,
   ___XXXXX,________,_XXXXX__,
   ___XXXXX,________,_XXXXX__,
   ____XXXX,X_______,XXXXX___,
   ____XXXX,XXX___XX,XXXXX___,
   _____XXX,XXXXXXXX,XXXX____,
   ______XX,XXXXXXXX,XXX_____,
   _______X,XXXXXXXX,XX______,
   ________,_XXXXXXX,________}


 ,{
   ________,______XX,XX______,
   ________,______XX,XX______,
   ________,_____XXX,XX______,
   ________,_____XXX,XX______,
   ________,____XXXX,XX______,
   ________,__XXXXXX,XX______,
   ______XX,XXXXXXXX,XX______,
   ______XX,XXXXXXXX,XX______,
   ______XX,XXXXXXXX,XX______,
   ______XX,XXXXXXXX,XX______,
   ________,_____XXX,XX______,
   ________,_____XXX,XX______,
   ________,_____XXX,XX______,
   ________,_____XXX,XX______,
   ________,_____XXX,XX______,
   ________,_____XXX,XX______,
   ________,_____XXX,XX______,
   ________,_____XXX,XX______,
   ________,_____XXX,XX______,
   ________,_____XXX,XX______,
   ________,_____XXX,XX______,
   ________,_____XXX,XX______,
   ________,_____XXX,XX______,
   ________,_____XXX,XX______,
   ________,_____XXX,XX______,
   ________,_____XXX,XX______,
   ________,_____XXX,XX______,
   ________,_____XXX,XX______,
   ________,_____XXX,XX______,
   ________,_____XXX,XX______,
   ________,_____XXX,XX______,
   ________,_____XXX,XX______}


 ,{
   ________,_XXXXXXX,X_______,
   _______X,XXXXXXXX,XXX_____,
   ______XX,XXXXXXXX,XXXX____,
   _____XXX,XXXXXXXX,XXXXX___,
   ____XXXX,XXX____X,XXXXXX__,
   ___XXXXX,X_______,XXXXXX__,
   ___XXXXX,________,_XXXXXX_,
   __XXXXX_,________,__XXXXX_,
   __XXXXX_,________,__XXXXX_,
   __XXXXX_,________,__XXXXX_,
   ________,________,__XXXXX_,
   ________,________,__XXXXX_,
   ________,________,__XXXXX_,
   ________,________,_XXXXXX_,
   ________,________,XXXXXX__,
   ________,_______X,XXXXXX__,
   ________,_____XXX,XXXXX___,
   ________,____XXXX,XXX_____,
   ________,__XXXXXX,XX______,
   ________,_XXXXXXX,X_______,
   _______X,XXXXXXX_,________,
   ______XX,XXXXXX__,________,
   _____XXX,XXXX____,________,
   ____XXXX,XXX_____,________,
   ____XXXX,XX______,________,
   ___XXXXX,X_______,________,
   ___XXXXX,________,________,
   __XXXXXX,XXXXXXXX,XXXXXXX_,
   __XXXXXX,XXXXXXXX,XXXXXXX_,
   __XXXXXX,XXXXXXXX,XXXXXXX_,
   __XXXXXX,XXXXXXXX,XXXXXXX_,
   __XXXXXX,XXXXXXXX,XXXXXXX_}


 ,{
   ________,_XXXXXX_,________,
   ______XX,XXXXXXXX,XX______,
   _____XXX,XXXXXXXX,XXX_____,
   ____XXXX,XXXXXXXX,XXXX____,
   ___XXXXX,X______X,XXXXX___,
   ___XXXXX,________,XXXXX___,
   __XXXXX_,________,XXXXXX__,
   __XXXXX_,________,_XXXXX__,
   __XXXXX_,________,_XXXXX__,
   __XXXXX_,________,_XXXXX__,
   ________,________,XXXXX___,
   ________,________,XXXXX___,
   ________,_______X,XXXX____,
   ________,__XXXXXX,XXX_____,
   ________,__XXXXXX,XX______,
   ________,__XXXXXX,XXX_____,
   ________,__XXXXXX,XXXXX___,
   ________,_______X,XXXXXX__,
   ________,________,_XXXXX__,
   ________,________,_XXXXXX_,
   ________,________,__XXXXX_,
   ________,________,__XXXXX_,
   _XXXXX__,________,__XXXXX_,
   _XXXXX__,________,__XXXXX_,
   _XXXXX__,________,_XXXXXX_,
   __XXXXX_,________,_XXXXX__,
   __XXXXXX,________,XXXXXX__,
   ___XXXXX,X______X,XXXXX___,
   ____XXXX,XXXXXXXX,XXXX____,
   _____XXX,XXXXXXXX,XXX_____,
   ______XX,XXXXXXXX,XX______,
   ________,_XXXXXX_,________}


 ,{
   ________,_______X,XXXX____,
   ________,______XX,XXXX____,
   ________,_____XXX,XXXX____,
   ________,_____XXX,XXXX____,
   ________,____XXXX,XXXX____,
   ________,___XXXXX,XXXX____,
   ________,___XXXX_,XXXX____,
   ________,__XXXXX_,XXXX____,
   ________,_XXXXX__,XXXX____,
   ________,_XXXX___,XXXX____,
   ________,XXXXX___,XXXX____,
   _______X,XXXX____,XXXX____,
   _______X,XXX_____,XXXX____,
   ______XX,XXX_____,XXXX____,
   _____XXX,XX______,XXXX____,
   _____XXX,X_______,XXXX____,
   ____XXXX,X_______,XXXX____,
   ___XXXXX,________,XXXX____,
   ___XXXX_,________,XXXX____,
   __XXXXX_,________,XXXX____,
   __XXXXXX,XXXXXXXX,XXXXXXXX,
   __XXXXXX,XXXXXXXX,XXXXXXXX,
   __XXXXXX,XXXXXXXX,XXXXXXXX,
   __XXXXXX,XXXXXXXX,XXXXXXXX,
   ________,________,XXXX____,
   ________,________,XXXX____,
   ________,________,XXXX____,
   ________,________,XXXX____,
   ________,________,XXXX____,
   ________,________,XXXX____,
   ________,________,XXXX____,
   ________,________,XXXX____}


 ,{
   _____XXX,XXXXXXXX,XXXXXX__,
   _____XXX,XXXXXXXX,XXXXXX__,
   _____XXX,XXXXXXXX,XXXXXX__,
   _____XXX,XXXXXXXX,XXXXXX__,
   ____XXXX,X_______,________,
   ____XXXX,X_______,________,
   ____XXXX,X_______,________,
   ____XXXX,X_______,________,
   ____XXXX,________,________,
   ____XXXX,________,________,
   ____XXXX,___XXXXX,________,
   ____XXXX,_XXXXXXX,XXX_____,
   ____XXXX,XXXXXXXX,XXXX____,
   ___XXXXX,XXXXXXXX,XXXXX___,
   ___XXXXX,XXX____X,XXXXXX__,
   ___XXXXX,X_______,_XXXXXX_,
   ___XXXXX,________,__XXXXX_,
   ________,________,__XXXXXX,
   ________,________,___XXXXX,
   ________,________,___XXXXX,
   ________,________,___XXXXX,
   ________,________,___XXXXX,
   ________,________,___XXXXX,
   __XXXXX_,________,__XXXXXX,
   __XXXXX_,________,__XXXXX_,
   ___XXXXX,________,_XXXXXX_,
   ___XXXXX,X_______,XXXXXX__,
   ____XXXX,XX____XX,XXXXXX__,
   _____XXX,XXXXXXXX,XXXXX___,
   ______XX,XXXXXXXX,XXXX____,
   _______X,XXXXXXXX,XX______,
   ________,__XXXXX_,________}


 ,{
   ________,__XXXXXX,XX______,
   ________,XXXXXXXX,XXXX____,
   _______X,XXXXXXXX,XXXXX___,
   ______XX,XXXXXXXX,XXXXXX__,
   _____XXX,XXX_____,_XXXXX__,
   ____XXXX,XX______,__XXXXX_,
   ____XXXX,X_______,___XXXX_,
   ___XXXXX,________,___XXXX_,
   ___XXXXX,________,________,
   ___XXXXX,________,________,
   __XXXXX_,________,________,
   __XXXXX_,___XXXXX,________,
   __XXXXX_,_XXXXXXX,XXX_____,
   __XXXXX_,XXXXXXXX,XXXX____,
   __XXXXXX,XXXXXXXX,XXXXX___,
   __XXXXXX,XX______,XXXXXX__,
   __XXXXXX,X_______,_XXXXXX_,
   __XXXXXX,________,__XXXXX_,
   __XXXXXX,________,___XXXXX,
   __XXXXX_,________,___XXXXX,
   __XXXXX_,________,___XXXXX,
   __XXXXX_,________,___XXXXX,
   ___XXXX_,________,___XXXXX,
   ___XXXXX,________,___XXXXX,
   ___XXXXX,________,___XXXXX,
   ____XXXX,X_______,__XXXXX_,
   ____XXXX,X_______,_XXXXXX_,
   _____XXX,XXX_____,XXXXXX__,
   ______XX,XXXXXXXX,XXXXX___,
   _______X,XXXXXXXX,XXXX____,
   ________,XXXXXXXX,XXX_____,
   ________,___XXXXX,________}


 ,{
   __XXXXXX,XXXXXXXX,XXXXXXXX,
   __XXXXXX,XXXXXXXX,XXXXXXXX,
   __XXXXXX,XXXXXXXX,XXXXXXXX,
   __XXXXXX,XXXXXXXX,XXXXXXXX,
   __XXXXXX,XXXXXXXX,XXXXXXXX,
   ________,________,___XXXXX,
   ________,________,__XXXXX_,
   ________,________,_XXXXX__,
   ________,________,XXXXX___,
   ________,_______X,XXXX____,
   ________,______XX,XXX_____,
   ________,_____XXX,XXX_____,
   ________,_____XXX,XX______,
   ________,____XXXX,XX______,
   ________,___XXXXX,X_______,
   ________,___XXXXX,X_______,
   ________,__XXXXXX,________,
   ________,__XXXXXX,________,
   ________,_XXXXXX_,________,
   ________,_XXXXXX_,________,
   ________,_XXXXXX_,________,
   ________,XXXXXX__,________,
   ________,XXXXXX__,________,
   ________,XXXXXX__,________,
   _______X,XXXXX___,________,
   _______X,XXXXX___,________,
   _______X,XXXXX___,________,
   _______X,XXXXX___,________,
   ______XX,XXXX____,________,
   ______XX,XXXX____,________,
   ______XX,XXXX____,________,
   ______XX,XXXX____,________}


 ,{
   ________,_XXXXXXX,X_______,
   _______X,XXXXXXXX,XXX_____,
   _____XXX,XXXXXXXX,XXXXX___,
   ____XXXX,XXXXXXXX,XXXXXX__,
   ____XXXX,XX______,XXXXXX__,
   ___XXXXX,X_______,_XXXXXX_,
   ___XXXXX,________,__XXXXX_,
   ___XXXXX,________,__XXXXX_,
   ___XXXXX,________,__XXXXX_,
   ___XXXXX,________,__XXXXX_,
   ___XXXXX,X_______,_XXXXXX_,
   ____XXXX,X_______,_XXXXX__,
   ____XXXX,XXX____X,XXXXXX__,
   _____XXX,XXXXXXXX,XXXXX___,
   _______X,XXXXXXXX,XXX_____,
   ______XX,XXXXXXXX,XXXX____,
   ____XXXX,XXXXXXXX,XXXXXX__,
   ___XXXXX,XXX____X,XXXXXXX_,
   ___XXXXX,________,__XXXXX_,
   __XXXXX_,________,___XXXXX,
   __XXXXX_,________,___XXXXX,
   __XXXXX_,________,___XXXXX,
   __XXXXX_,________,___XXXXX,
   __XXXXX_,________,___XXXXX,
   __XXXXX_,________,___XXXXX,
   __XXXXXX,________,__XXXXXX,
   ___XXXXX,________,__XXXXX_,
   ___XXXXX,XX______,XXXXXXX_,
   ____XXXX,XXXXXXXX,XXXXXX__,
   _____XXX,XXXXXXXX,XXXXX___,
   ______XX,XXXXXXXX,XXXX____,
   ________,XXXXXXXX,XX______}


 ,{
   ________,_XXXXXXX,X_______,
   _______X,XXXXXXXX,XXX_____,
   ______XX,XXXXXXXX,XXXX____,
   _____XXX,XXXXXXXX,XXXXX___,
   ____XXXX,XX______,XXXXXX__,
   ___XXXXX,X_______,_XXXXX__,
   ___XXXXX,________,__XXXXX_,
   ___XXXX_,________,__XXXXX_,
   __XXXXX_,________,___XXXXX,
   __XXXXX_,________,___XXXXX,
   __XXXXX_,________,___XXXXX,
   __XXXXX_,________,___XXXXX,
   __XXXXX_,________,___XXXXX,
   ___XXXX_,________,__XXXXXX,
   ___XXXXX,________,__XXXXXX,
   ___XXXXX,X_______,_XXXXXXX,
   ____XXXX,XX_____X,XXXXXXXX,
   _____XXX,XXXXXXXX,XXXXXXXX,
   ______XX,XXXXXXXX,XX_XXXXX,
   ________,XXXXXXXX,___XXXXX,
   ________,__XXXX__,___XXXXX,
   ________,________,__XXXXXX,
   ________,________,__XXXXX_,
   ________,________,__XXXXX_,
   __XXXXX_,________,_XXXXXX_,
   __XXXXX_,________,_XXXXX__,
   ___XXXXX,________,XXXXX___,
   ___XXXXX,X______X,XXXXX___,
   ____XXXX,XXXXXXXX,XXXX____,
   _____XXX,XXXXXXXX,XXX_____,
   ______XX,XXXXXXXX,XX______,
   ________,XXXXXXXX,________}


 ,{
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,___XXX__,________,
   ________,__XXXXX_,________,
   ________,__XXXXX_,________,
   ________,__XXXXX_,________,
   ________,___XXX__,________}


 ,{
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,__XXXX__,________,
   ________,__XXXX__,________,
   ________,__XXXX__,________,
   ________,__XXXX__,________,
   ________,__XXXX__,________,
   ________,__XXXX__,________,
   ________,__XXXX__,________,
   __XXXXXX,XXXXXXXX,XXXXXX__,
   __XXXXXX,XXXXXXXX,XXXXXX__,
   __XXXXXX,XXXXXXXX,XXXXXX__,
   __XXXXXX,XXXXXXXX,XXXXXX__,
   ________,__XXXX__,________,
   ________,__XXXX__,________,
   ________,__XXXX__,________,
   ________,__XXXX__,________,
   ________,__XXXX__,________,
   ________,__XXXX__,________,
   ________,__XXXX__,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________}


 ,{
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   __XXXXXX,XXXXXXXX,XXXXXX__,
   __XXXXXX,XXXXXXXX,XXXXXX__,
   __XXXXXX,XXXXXXXX,XXXXXX__,
   __XXXXXX,XXXXXXXX,XXXXXX__,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________}


 ,{
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,___XXX__,________,
   ________,__XXXXX_,________,
   ________,__XXXXX_,________,
   ________,__XXXXX_,________,
   ________,___XXX__,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,___XXX__,________,
   ________,__XXXXX_,________,
   ________,__XXXXX_,________,
   ________,__XXXXX_,________,
   ________,___XXX__,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________}
 ,{
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________,
   ________,________,________}
};

/*
        **************************************
        *                                    *
        *       Digit translation table      *
        *                                    *
        **************************************

  This table is needed for translation of the big-digit font,
  which is defined for the following characters only : 0123456789+-.:
  Needs to be included only if if the digit-font is listed
  in the font table.

*/

GUI_FLASH const GUI_FONT_TRANSLIST TLDigits24x32[] = {
  {14,-1},              /* char 32 : ' ' */
  {-1,-1},              /* char 33 : n/a */
  {-1,-1},              /* char 34 : n/a */
  {-1,-1},              /* char 35 : n/a */
  {-1,-1},              /* char 36 : n/a */
  {-1,-1},              /* char 37 : n/a */
  {-1,-1},              /* char 38 : n/a */
  {-1,-1},              /* char 39 : n/a */
  {-1,-1},              /* char 40 : n/a */
  {-1,-1},              /* char 41 : n/a */
  {-1,-1},              /* char 42 : n/a */
  {11,-1},              /* char 43 : '+' */
  {-1,-1},              /* char 44 : n/a */
  {12,-1},              /* char 45 : '-' */
  {10,-1},              /* char 46 : '.' */
  {-1,-1},              /* char 47 : n/a */
  {0,-1},               /* char 48 : '0' */
  {1,-1},               /* char 49 : '1' */
  {2,-1},               /* char 50 : '2' */
  {3,-1},               /* char 51 : '3' */
  {4,-1},               /* char 52 : '4' */
  {5,-1},               /* char 53 : '5' */
  {6,-1},               /* char 54 : '6' */
  {7,-1},               /* char 55 : '7' */
  {8,-1},               /* char 56 : '8' */
  {9,-1},               /* char 57 : '9' */
  {13,-1},              /* char 58 : ':' */
};

GUI_FLASH const GUI_FONT_TRANSINFO TransInfo24x32 = {
  32,   /* First character for translation, plus sign */
  58,   /* Last character for translation, digit 9 */
  &TLDigits24x32[0]
};


GUI_FLASH const GUI_FONT_MONO FontMono24x32 = {
  (void GUI_FLASH *)acFont24x32,
  (void GUI_FLASH *)acFont24x32,
  &TransInfo24x32,
  0, 0,             /* All character are in translation table */
  24, 24,           /* width, spacing */
  3                 /* Bytes per line */
};

GUI_FLASH const GUI_FONT GUI_FontD24x32 = { GUI_FONTTYPE_MONO, 32,32,1,1, (void GUI_FLASH *)&FontMono24x32 };
