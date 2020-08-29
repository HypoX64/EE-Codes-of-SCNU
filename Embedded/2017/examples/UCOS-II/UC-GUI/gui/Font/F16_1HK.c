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
File        : F16_1HK.C
Purpose     : ASCII, West European, Hiragana & Katakana
Height      : 16
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.H"

#ifndef GUI_FLASH
  #define GUI_FLASH
#endif

/* The following line needs to be included in any file selecting the
   font. A good place would be GUIConf.H
*/
extern GUI_FLASH const GUI_FONT GUI_Font16_HK;
extern GUI_FLASH const GUI_FONT GUI_Font16_1HK_2_2;


extern GUI_FLASH const GUI_FONT_PROP GUI_Font16_1_FontProp1;
extern GUI_FLASH const GUI_CHARINFO GUI_Font16_HK_CharInfo[169];

GUI_FLASH const GUI_FONT_PROP GUI_Font16_1HK_Prop2 = {
   0x30A1                         /* first character               */
  ,0x30F6                         /* last character                */
  ,&GUI_Font16_HK_CharInfo[83] /* address of first character    */
  ,(void GUI_FLASH *)&GUI_Font16_1_FontProp1                          /* pointer to next GUI_FONT_PROP */
};

GUI_FLASH const GUI_FONT_PROP GUI_Font16_1HK_Prop1 = {
   0x3041                         /* first character               */
  ,0x3093                         /* last character                */
  ,&GUI_Font16_HK_CharInfo[0] /* address of first character    */
  ,(void GUI_FLASH *)&GUI_Font16_1HK_Prop2                         /* pointer to next GUI_FONT_PROP */
};

GUI_FLASH const GUI_FONT GUI_Font16_1HK = {
   GUI_FONTTYPE_PROP /* type of font    */
  ,16                /* height of font  */
  ,16                /* space of font y */
  ,1                /* magnification x */
  ,1                /* magnification y */
  ,(void GUI_FLASH *)&GUI_Font16_1HK_Prop1
};

GUI_FLASH const GUI_FONT GUI_Font16_1HK_2_2 = {
   GUI_FONTTYPE_PROP /* type of font    */
  ,16                /* height of font  */
  ,16                /* space of font y */
  ,2                /* magnification x */
  ,2                /* magnification y */
  ,(void GUI_FLASH *)&GUI_Font16_1HK_Prop1
};

