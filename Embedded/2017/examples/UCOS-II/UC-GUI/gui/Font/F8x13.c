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
File        : F8x13.C
Purpose     : Monospaced Font similar to courier
Height      : 13
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.H"

#ifndef GUI_FLASH
  #define GUI_FLASH
#endif

/* The following line needs to be included in any file selecting the
   font. A good place would be GUIConf.H
*/
extern GUI_FLASH const GUI_FONT GUI_Font8x13;

GUI_FLASH const unsigned char acF8x13_32[13] = { /* code 32 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_33[13] = { /* code 33 */
  ________,
  ________,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ________,
  ____X___,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_34[13] = { /* code 34 */
  ________,
  ________,
  ___X_X__,
  ___X_X__,
  ___X_X__,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_35[13] = { /* code 35 */
  ________,
  ________,
  ____X_X_,
  ____X_X_,
  __XXXXXX,
  ___X_X__,
  ___X_X__,
  ___X_X__,
  _XXXXXX_,
  __X_X___,
  __X_X___,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_36[13] = { /* code 36 */
  ________,
  ________,
  ____X___,
  ___XXX__,
  __X___X_,
  __X_____,
  ___XXX__,
  ______X_,
  __X___X_,
  ___XXX__,
  ____X___,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_37[13] = { /* code 37 */
  ________,
  ________,
  __X_____,
  _X_X___X,
  __X___X_,
  _____X__,
  ____X___,
  ___X____,
  __X___X_,
  _X___X_X,
  ______X_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_38[13] = { /* code 38 */
  ________,
  ________,
  ___XX___,
  __X_____,
  __X_____,
  ___X____,
  __XX____,
  _X__X__X,
  _X__X_X_,
  _X___X__,
  __XXX_XX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_39[13] = { /* code 39 */
  ________,
  ________,
  ____X___,
  ____X___,
  ____X___,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_40[13] = { /* code 40 */
  ________,
  ________,
  _____X__,
  ____X___,
  ____X___,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ____X___,
  ____X___,
  _____X__};

GUI_FLASH const unsigned char acF8x13_41[13] = { /* code 41 */
  ________,
  ________,
  ___X____,
  ____X___,
  ____X___,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  ____X___,
  ____X___,
  ___X____};

GUI_FLASH const unsigned char acF8x13_42[13] = { /* code 42 */
  ________,
  ________,
  ________,
  ________,
  __XX_XX_,
  ___XXX__,
  _XXXXXXX,
  ___XXX__,
  __XX_XX_,
  ________,
  ________,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_43[13] = { /* code 43 */
  ________,
  ________,
  ________,
  ________,
  ____X___,
  ____X___,
  ____X___,
  _XXXXXXX,
  ____X___,
  ____X___,
  ____X___,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_44[13] = { /* code 44 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ____X___,
  ___X____,
  ________};

GUI_FLASH const unsigned char acF8x13_45[13] = { /* code 45 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXXXXXX,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_46[13] = { /* code 46 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ____X___,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_47[13] = { /* code 47 */
  ________,
  ________,
  ________,
  _______X,
  ______X_,
  _____X__,
  ____X___,
  ___X____,
  __X_____,
  _X______,
  ________,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_48[13] = { /* code 48 */
  ________,
  ________,
  ___XXX__,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  ___XXX__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_49[13] = { /* code 49 */
  ________,
  ________,
  ____X___,
  __XXX___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_50[13] = { /* code 50 */
  ________,
  ________,
  ___XXX__,
  __X___X_,
  ______X_,
  ______X_,
  _____X__,
  ____X___,
  ___X____,
  __X_____,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_51[13] = { /* code 51 */
  ________,
  ________,
  ___XXX__,
  __X___X_,
  ______X_,
  ______X_,
  ____XX__,
  ______X_,
  ______X_,
  __X___X_,
  ___XXX__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_52[13] = { /* code 52 */
  ________,
  ________,
  _____X__,
  ____XX__,
  ____XX__,
  ___X_X__,
  ___X_X__,
  __X__X__,
  __XXXXX_,
  _____X__,
  ____XXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_53[13] = { /* code 53 */
  ________,
  ________,
  __XXXXX_,
  __X_____,
  __X_____,
  __X_____,
  __XXXX__,
  ______X_,
  ______X_,
  __X___X_,
  ___XXX__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_54[13] = { /* code 54 */
  ________,
  ________,
  ____XX__,
  ___X____,
  __X_____,
  __X_____,
  __XXXX__,
  __X___X_,
  __X___X_,
  __X___X_,
  ___XXX__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_55[13] = { /* code 55 */
  ________,
  ________,
  __XXXXX_,
  __X___X_,
  ______X_,
  _____X__,
  _____X__,
  ____X___,
  ____X___,
  ___X____,
  ___X____,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_56[13] = { /* code 56 */
  ________,
  ________,
  ___XXX__,
  __X___X_,
  __X___X_,
  __X___X_,
  ___XXX__,
  __X___X_,
  __X___X_,
  __X___X_,
  ___XXX__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_57[13] = { /* code 57 */
  ________,
  ________,
  ___XXX__,
  __X___X_,
  __X___X_,
  __X___X_,
  ___XXXX_,
  ______X_,
  ______X_,
  _____X__,
  ___XX___,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_58[13] = { /* code 58 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ____X___,
  ________,
  ________,
  ________,
  ________,
  ____X___,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_59[13] = { /* code 59 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ____X___,
  ________,
  ________,
  ________,
  ________,
  ____X___,
  ___X____,
  ________};

GUI_FLASH const unsigned char acF8x13_60[13] = { /* code 60 */
  ________,
  ________,
  ________,
  ________,
  _____X__,
  ____X___,
  ___X____,
  __X_____,
  ___X____,
  ____X___,
  _____X__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_61[13] = { /* code 61 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXXXX_,
  ________,
  __XXXXX_,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_62[13] = { /* code 62 */
  ________,
  ________,
  ________,
  ________,
  ___X____,
  ____X___,
  _____X__,
  ______X_,
  _____X__,
  ____X___,
  ___X____,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_63[13] = { /* code 63 */
  ________,
  ________,
  ___XXX__,
  __X___X_,
  ______X_,
  ______X_,
  _____X__,
  ____X___,
  ____X___,
  ________,
  ____X___,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_64[13] = { /* code 64 */
  ________,
  ________,
  ___XXXX_,
  __X____X,
  _X__XX_X,
  _X_X_X_X,
  _X_X_X_X,
  _X_X_X_X,
  _X__XXX_,
  __X_____,
  ___XXX__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_65[13] = { /* code 65 */
  ________,
  ________,
  ___XX___,
  ____X___,
  ____X___,
  ___X_X__,
  ___X_X__,
  __X___X_,
  __XXXXX_,
  __X___X_,
  _XXX_XXX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_66[13] = { /* code 66 */
  ________,
  ________,
  _XXXXXX_,
  __X____X,
  __X____X,
  __X____X,
  __XXXXX_,
  __X____X,
  __X____X,
  __X____X,
  _XXXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_67[13] = { /* code 67 */
  ________,
  ________,
  ___XXXX_,
  __X____X,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  __X____X,
  ___XXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_68[13] = { /* code 68 */
  ________,
  ________,
  _XXXXX__,
  __X___X_,
  __X____X,
  __X____X,
  __X____X,
  __X____X,
  __X____X,
  __X___X_,
  _XXXXX__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_69[13] = { /* code 69 */
  ________,
  ________,
  _XXXXXXX,
  __X____X,
  __X_____,
  __X__X__,
  __XXXX__,
  __X__X__,
  __X_____,
  __X____X,
  _XXXXXXX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_70[13] = { /* code 70 */
  ________,
  ________,
  _XXXXXXX,
  __X____X,
  __X_____,
  __X__X__,
  __XXXX__,
  __X__X__,
  __X_____,
  __X_____,
  _XXXX___,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_71[13] = { /* code 71 */
  ________,
  ________,
  ___XXXX_,
  __X____X,
  _X______,
  _X______,
  _X______,
  _X___XXX,
  _X_____X,
  __X____X,
  ___XXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_72[13] = { /* code 72 */
  ________,
  ________,
  _XXX_XXX,
  __X___X_,
  __X___X_,
  __X___X_,
  __XXXXX_,
  __X___X_,
  __X___X_,
  __X___X_,
  _XXX_XXX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_73[13] = { /* code 73 */
  ________,
  ________,
  __XXXXX_,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_74[13] = { /* code 74 */
  ________,
  ________,
  ___XXXX_,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _X___X__,
  _X___X__,
  __XXX___,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_75[13] = { /* code 75 */
  ________,
  ________,
  _XXX__XX,
  __X___X_,
  __X__X__,
  __X__X__,
  __X_X___,
  __XXX___,
  __X__X__,
  __X___X_,
  _XXX__XX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_76[13] = { /* code 76 */
  ________,
  ________,
  _XXXXX__,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X___X,
  _XXXXXXX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_77[13] = { /* code 77 */
  ________,
  ________,
  _XX___XX,
  __X___X_,
  __XX_XX_,
  __XX_XX_,
  __X_X_X_,
  __X_X_X_,
  __X___X_,
  __X___X_,
  _XXX_XXX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_78[13] = { /* code 78 */
  ________,
  ________,
  _XX__XXX,
  __X___X_,
  __XX__X_,
  __XX__X_,
  __X_X_X_,
  __X__XX_,
  __X__XX_,
  __X___X_,
  _XXX__X_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_79[13] = { /* code 79 */
  ________,
  ________,
  ___XXX__,
  __X___X_,
  _X_____X,
  _X_____X,
  _X_____X,
  _X_____X,
  _X_____X,
  __X___X_,
  ___XXX__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_80[13] = { /* code 80 */
  ________,
  ________,
  _XXXXXX_,
  __X____X,
  __X____X,
  __X____X,
  __XXXXX_,
  __X_____,
  __X_____,
  __X_____,
  _XXXX___,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_81[13] = { /* code 81 */
  ________,
  ________,
  ___XXX__,
  __X___X_,
  _X_____X,
  _X_____X,
  _X_____X,
  _X_____X,
  _X_____X,
  __X___X_,
  ___XXX__,
  ___XX_XX,
  ________};

GUI_FLASH const unsigned char acF8x13_82[13] = { /* code 82 */
  ________,
  ________,
  _XXXXXX_,
  __X____X,
  __X____X,
  __X____X,
  __XXXXX_,
  __X__X__,
  __X__X__,
  __X___X_,
  _XXX__XX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_83[13] = { /* code 83 */
  ________,
  ________,
  __XXXXX_,
  _X_____X,
  _X______,
  _X______,
  __XXXXX_,
  _______X,
  _______X,
  _X_____X,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_84[13] = { /* code 84 */
  ________,
  ________,
  _XXXXXXX,
  _X__X__X,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ___XXX__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_85[13] = { /* code 85 */
  ________,
  ________,
  _XXX_XXX,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  ___XXX__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_86[13] = { /* code 86 */
  ________,
  ________,
  _XXX_XXX,
  __X___X_,
  __X___X_,
  __X___X_,
  ___X_X__,
  ___X_X__,
  ___X_X__,
  ____X___,
  ____X___,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_87[13] = { /* code 87 */
  ________,
  ________,
  _XXX_XXX,
  __X___X_,
  __X___X_,
  __X___X_,
  __X_X_X_,
  __X_X_X_,
  __X_X_X_,
  ___X_X__,
  ___X_X__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_88[13] = { /* code 88 */
  ________,
  ________,
  _XXX_XXX,
  __X___X_,
  ___X_X__,
  ___X_X__,
  ____X___,
  ___X_X__,
  ___X_X__,
  __X___X_,
  _XXX_XXX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_89[13] = { /* code 89 */
  ________,
  ________,
  _XXX_XXX,
  __X___X_,
  __X___X_,
  ___X_X__,
  ___X_X__,
  ____X___,
  ____X___,
  ____X___,
  ___XXX__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_90[13] = { /* code 90 */
  ________,
  ________,
  _XXXXXXX,
  _X____X_,
  _____X__,
  _____X__,
  ____X___,
  ___X____,
  ___X____,
  __X____X,
  _XXXXXXX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_91[13] = { /* code 91 */
  ________,
  ________,
  ___XXX__,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___XXX__};

GUI_FLASH const unsigned char acF8x13_92[13] = { /* code 92 */
  ________,
  ________,
  ________,
  _X______,
  __X_____,
  ___X____,
  ____X___,
  _____X__,
  ______X_,
  _______X,
  ________,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_93[13] = { /* code 93 */
  ________,
  ________,
  ___XXX__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  ___XXX__};

GUI_FLASH const unsigned char acF8x13_94[13] = { /* code 94 */
  ________,
  ____X___,
  ___X_X__,
  __X___X_,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_95[13] = { /* code 95 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  XXXXXXXX};

GUI_FLASH const unsigned char acF8x13_96[13] = { /* code 96 */
  ________,
  ________,
  ___X____,
  ____X___,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_97[13] = { /* code 97 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXXX__,
  ______X_,
  __XXXXX_,
  _X____X_,
  _X____X_,
  __XXXX_X,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_98[13] = { /* code 98 */
  ________,
  ________,
  _XX_____,
  __X_____,
  __X_____,
  __XXXXX_,
  __X____X,
  __X____X,
  __X____X,
  __X____X,
  _XXXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_99[13] = { /* code 99 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXXXX_,
  _X_____X,
  _X______,
  _X______,
  _X_____X,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_100[13] = { /* code 100 */
  ________,
  ________,
  _____XX_,
  ______X_,
  ______X_,
  __XXXXX_,
  _X____X_,
  _X____X_,
  _X____X_,
  _X____X_,
  __XXXXXX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_101[13] = { /* code 101 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXXXX_,
  _X_____X,
  _XXXXXXX,
  _X______,
  _X_____X,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_102[13] = { /* code 102 */
  ________,
  ________,
  ____XX__,
  ___X____,
  ___X____,
  __XXXX__,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  __XXXX__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_103[13] = { /* code 103 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXXXXX,
  _X____X_,
  _X____X_,
  _X____X_,
  __XXXXX_,
  ______X_,
  ______X_,
  __XXXX__};

GUI_FLASH const unsigned char acF8x13_104[13] = { /* code 104 */
  ________,
  ________,
  _XX_____,
  __X_____,
  __X_____,
  __X_XX__,
  __XX__X_,
  __X___X_,
  __X___X_,
  __X___X_,
  _XXX_XXX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_105[13] = { /* code 105 */
  ________,
  ________,
  ____X___,
  ________,
  ________,
  __XXX___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_106[13] = { /* code 106 */
  ________,
  ________,
  _____X__,
  ________,
  ________,
  __XXXX__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  __XXX___};

GUI_FLASH const unsigned char acF8x13_107[13] = { /* code 107 */
  ________,
  ________,
  _XX_____,
  __X_____,
  __X_____,
  __X__XX_,
  __X__X__,
  __X_X___,
  __XXX___,
  __X__X__,
  _XX___XX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_108[13] = { /* code 108 */
  ________,
  ________,
  ___XX___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_109[13] = { /* code 109 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXX_X__,
  __X_X_X_,
  __X_X_X_,
  __X_X_X_,
  __X_X_X_,
  _XX_X_XX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_110[13] = { /* code 110 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XX_XX__,
  __XX__X_,
  __X___X_,
  __X___X_,
  __X___X_,
  _XXX_XXX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_111[13] = { /* code 111 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXXXX_,
  _X_____X,
  _X_____X,
  _X_____X,
  _X_____X,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_112[13] = { /* code 112 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXXXXX_,
  __X____X,
  __X____X,
  __X____X,
  __X____X,
  __XXXXX_,
  __X_____,
  _XXX____};

GUI_FLASH const unsigned char acF8x13_113[13] = { /* code 113 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXXXXX,
  _X____X_,
  _X____X_,
  _X____X_,
  _X____X_,
  __XXXXX_,
  ______X_,
  _____XXX};

GUI_FLASH const unsigned char acF8x13_114[13] = { /* code 114 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXX_XX_,
  ___XX__X,
  ___X____,
  ___X____,
  ___X____,
  _XXXXX__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_115[13] = { /* code 115 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXXXX_,
  _X_____X,
  __XXX___,
  _____XX_,
  _X_____X,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_116[13] = { /* code 116 */
  ________,
  ________,
  ________,
  ___X____,
  ___X____,
  __XXXX__,
  ___X____,
  ___X____,
  ___X____,
  ___X__X_,
  ____XX__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_117[13] = { /* code 117 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XX__XX_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X__XX_,
  ___XX_XX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_118[13] = { /* code 118 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXX_XXX,
  __X___X_,
  __X___X_,
  ___X_X__,
  ___X_X__,
  ____X___,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_119[13] = { /* code 119 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXX_XXX,
  __X___X_,
  __X_X_X_,
  __X_X_X_,
  ___X_X__,
  ___X_X__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_120[13] = { /* code 120 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXX_XXX,
  __X___X_,
  ___XXX__,
  ___XXX__,
  __X___X_,
  _XXX_XXX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_121[13] = { /* code 121 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXX_XXX,
  __X___X_,
  __X___X_,
  ___X_X__,
  ___X_X__,
  ____X___,
  ____X___,
  __XX____};

GUI_FLASH const unsigned char acF8x13_122[13] = { /* code 122 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXXXXX_,
  _X___X__,
  ____X___,
  ___X____,
  __X___X_,
  _XXXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_123[13] = { /* code 123 */
  ________,
  ________,
  _____XX_,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  __XX____,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  _____XX_};

GUI_FLASH const unsigned char acF8x13_124[13] = { /* code 124 */
  ________,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___};

GUI_FLASH const unsigned char acF8x13_125[13] = { /* code 125 */
  ________,
  ________,
  __XX____,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  _____XX_,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  __XX____};

GUI_FLASH const unsigned char acF8x13_126[13] = { /* code 126 */
  ________,
  ________,
  ________,
  __XX___X,
  _X__X__X,
  _X___XX_,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_127[13] = { /* code 127 */
  ________,
  ________,
  ________,
  ___XXX__,
  ___XXX__,
  ___XXX__,
  ___XXX__,
  ___XXX__,
  ___XXX__,
  ___XXX__,
  ___XXX__,
  ___XXX__,
  ________};

GUI_FLASH const unsigned char acF8x13_160[13] = { /* code 160 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_161[13] = { /* code 161 */
  ________,
  ________,
  ____X___,
  ________,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_162[13] = { /* code 162 */
  ________,
  ________,
  ________,
  ________,
  ____X___,
  ___XXX__,
  __X___X_,
  __X_____,
  __X___X_,
  ___XXX__,
  ____X___,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_163[13] = { /* code 163 */
  ________,
  ________,
  ________,
  ___XX___,
  __X__X__,
  __X_____,
  ___X____,
  __XXXX__,
  ___X____,
  ___X____,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_164[13] = { /* code 164 */
  ________,
  ________,
  _X_____X,
  __XXXXX_,
  __X___X_,
  __X___X_,
  __X___X_,
  __XXXXX_,
  _X_____X,
  ________,
  ________,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_165[13] = { /* code 165 */
  ________,
  ________,
  ________,
  _XXX_XXX,
  __X___X_,
  _XXXXXXX,
  ___X_X__,
  _XXXXXXX,
  ____X___,
  ____X___,
  ___XXX__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_166[13] = { /* code 166 */
  ________,
  ________,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ________,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___};

GUI_FLASH const unsigned char acF8x13_167[13] = { /* code 167 */
  ________,
  ________,
  ___XXXX_,
  __X___X_,
  _X_X____,
  _X__X___,
  __X__X__,
  ___X__X_,
  ____X_X_,
  _X___X__,
  _XXXX___,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_168[13] = { /* code 168 */
  ________,
  ________,
  __X___X_,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_169[13] = { /* code 169 */
  ________,
  ________,
  ___XXX__,
  __X___X_,
  _X__XX_X,
  _X_X___X,
  _X_X___X,
  _X__XX_X,
  __X___X_,
  ___XXX__,
  ________,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_170[13] = { /* code 170 */
  ________,
  ________,
  ___XX___,
  _____X__,
  ___XXX__,
  __X__X__,
  ___XXX__,
  ________,
  __XXXX__,
  ________,
  ________,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_171[13] = { /* code 171 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ___X___X,
  __X___X_,
  _X___X__,
  __X___X_,
  ___X___X,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_172[13] = { /* code 172 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXXXX_,
  ______X_,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_173[13] = { /* code 173 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXXXXXX,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_174[13] = { /* code 174 */
  ________,
  ________,
  ___XXX__,
  __X___X_,
  _X_XX__X,
  _X_X_X_X,
  _X_XX__X,
  _X_X_X_X,
  __X___X_,
  ___XXX__,
  ________,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_175[13] = { /* code 175 */
  ________,
  XXXXXXXX,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_176[13] = { /* code 176 */
  ________,
  ________,
  ____X___,
  ___X_X__,
  ____X___,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_177[13] = { /* code 177 */
  ________,
  ________,
  ____X___,
  ____X___,
  ____X___,
  _XXXXXXX,
  ____X___,
  ____X___,
  ____X___,
  ________,
  _XXXXXXX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_178[13] = { /* code 178 */
  ________,
  ________,
  ____X___,
  ___X_X__,
  _____X__,
  ____X___,
  ___XXX__,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_179[13] = { /* code 179 */
  ________,
  ________,
  ___XX___,
  _____X__,
  ____X___,
  _____X__,
  ___XX___,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_180[13] = { /* code 180 */
  ________,
  ________,
  _____X__,
  ____X___,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_181[13] = { /* code 181 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  __XXXX__,
  __X_____,
  _X______};

GUI_FLASH const unsigned char acF8x13_182[13] = { /* code 182 */
  ________,
  ________,
  __XXXXXX,
  _XXXX_X_,
  _XXXX_X_,
  _XXXX_X_,
  __XXX_X_,
  ____X_X_,
  ____X_X_,
  ____X_X_,
  ___XX_XX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_183[13] = { /* code 183 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ____X___,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_184[13] = { /* code 184 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ____X___,
  _____X__,
  ___XX___};

GUI_FLASH const unsigned char acF8x13_185[13] = { /* code 185 */
  ________,
  ________,
  ___XX___,
  ____X___,
  ____X___,
  ____X___,
  ___XXX__,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_186[13] = { /* code 186 */
  ________,
  ________,
  ___XX___,
  __X__X__,
  __X__X__,
  __X__X__,
  ___XX___,
  ________,
  __XXXX__,
  ________,
  ________,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_187[13] = { /* code 187 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  _X___X__,
  __X___X_,
  ___X___X,
  __X___X_,
  _X___X__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_188[13] = { /* code 188 */
  ________,
  ________,
  _XX_____,
  __X____X,
  __X___X_,
  __X__X__,
  _XXXX__X,
  ___X__XX,
  __X__X_X,
  _X__XXXX,
  _______X,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_189[13] = { /* code 189 */
  ________,
  ________,
  _XX_____,
  __X____X,
  __X___X_,
  __X__X__,
  _XXXX_X_,
  ___X_X_X,
  __X____X,
  _X____X_,
  _____XXX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_190[13] = { /* code 190 */
  ________,
  ________,
  _XX_____,
  ___X___X,
  __X___X_,
  ___X_X__,
  _XX_X__X,
  ___X__XX,
  __X__X_X,
  _X__XXXX,
  _______X,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_191[13] = { /* code 191 */
  ________,
  ________,
  ____X___,
  ________,
  ____X___,
  ____X___,
  ___X____,
  __X_____,
  __X_____,
  __X___X_,
  ___XXX__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_192[13] = { /* code 192 */
  ___X____,
  ____X___,
  ___XX___,
  ____X___,
  ____X___,
  ___X_X__,
  ___X_X__,
  __X___X_,
  __XXXXX_,
  __X___X_,
  _XXX_XXX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_193[13] = { /* code 193 */
  _____X__,
  ____X___,
  ___XX___,
  ____X___,
  ____X___,
  ___X_X__,
  ___X_X__,
  __X___X_,
  __XXXXX_,
  __X___X_,
  _XXX_XXX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_194[13] = { /* code 194 */
  ____X___,
  ___X_X__,
  ___XX___,
  ____X___,
  ____X___,
  ___X_X__,
  ___X_X__,
  __X___X_,
  __XXXXX_,
  __X___X_,
  _XXX_XXX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_195[13] = { /* code 195 */
  __XXX__X,
  _X__XXX_,
  ___XX___,
  ____X___,
  ____X___,
  ___X_X__,
  ___X_X__,
  __X___X_,
  __XXXXX_,
  __X___X_,
  _XXX_XXX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_196[13] = { /* code 196 */
  __X___X_,
  ________,
  ___XX___,
  ____X___,
  ____X___,
  ___X_X__,
  ___X_X__,
  __X___X_,
  __XXXXX_,
  __X___X_,
  _XXX_XXX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_197[13] = { /* code 197 */
  ____X___,
  ___X_X__,
  ____X___,
  ____X___,
  ____X___,
  ___X_X__,
  ___X_X__,
  __X___X_,
  __XXXXX_,
  __X___X_,
  _XXX_XXX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_198[13] = { /* code 198 */
  ________,
  ________,
  __XXXXXX,
  ___XX__X,
  ___XX___,
  __X_X_X_,
  __X_XXX_,
  __X_X_X_,
  _XXXX___,
  _X__X__X,
  _X__XXXX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_199[13] = { /* code 199 */
  ________,
  ________,
  ________,
  ___XXXX_,
  __X____X,
  _X______,
  _X______,
  _X______,
  _X______,
  __X____X,
  ___XXXX_,
  _____X__,
  ____XX__};

GUI_FLASH const unsigned char acF8x13_200[13] = { /* code 200 */
  ___X____,
  ____X___,
  _XXXXXXX,
  __X____X,
  __X_____,
  __X__X__,
  __XXXX__,
  __X__X__,
  __X_____,
  __X____X,
  _XXXXXXX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_201[13] = { /* code 201 */
  _____X__,
  ____X___,
  _XXXXXXX,
  __X____X,
  __X_____,
  __X__X__,
  __XXXX__,
  __X__X__,
  __X_____,
  __X____X,
  _XXXXXXX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_202[13] = { /* code 202 */
  ____X___,
  ___X_X__,
  _XXXXXXX,
  __X____X,
  __X_____,
  __X__X__,
  __XXXX__,
  __X__X__,
  __X_____,
  __X____X,
  _XXXXXXX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_203[13] = { /* code 203 */
  __X___X_,
  ________,
  _XXXXXXX,
  __X____X,
  __X_____,
  __X__X__,
  __XXXX__,
  __X__X__,
  __X_____,
  __X____X,
  _XXXXXXX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_204[13] = { /* code 204 */
  ___X____,
  ____X___,
  __XXXXX_,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_205[13] = { /* code 205 */
  _____X__,
  ____X___,
  __XXXXX_,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_206[13] = { /* code 206 */
  ____X___,
  ___X_X__,
  __XXXXX_,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_207[13] = { /* code 207 */
  __X___X_,
  ________,
  __XXXXX_,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_208[13] = { /* code 208 */
  ________,
  ________,
  _XXXXX__,
  __X___X_,
  __X____X,
  __X____X,
  _XXXX__X,
  __X____X,
  __X____X,
  __X___X_,
  _XXXXX__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_209[13] = { /* code 209 */
  __XXX__X,
  _X__XXX_,
  _XX__XXX,
  __X___X_,
  __XX__X_,
  __XX__X_,
  __X_X_X_,
  __X__XX_,
  __X__XX_,
  __X___X_,
  _XXX__X_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_210[13] = { /* code 210 */
  ___X____,
  ____X___,
  ___XXX__,
  __X___X_,
  _X_____X,
  _X_____X,
  _X_____X,
  _X_____X,
  _X_____X,
  __X___X_,
  ___XXX__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_211[13] = { /* code 211 */
  _____X__,
  ____X___,
  ___XXX__,
  __X___X_,
  _X_____X,
  _X_____X,
  _X_____X,
  _X_____X,
  _X_____X,
  __X___X_,
  ___XXX__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_212[13] = { /* code 212 */
  ____X___,
  ___X_X__,
  ___XXX__,
  __X___X_,
  _X_____X,
  _X_____X,
  _X_____X,
  _X_____X,
  _X_____X,
  __X___X_,
  ___XXX__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_213[13] = { /* code 213 */
  __XXX__X,
  _X__XXX_,
  ___XXX__,
  __X___X_,
  _X_____X,
  _X_____X,
  _X_____X,
  _X_____X,
  _X_____X,
  __X___X_,
  ___XXX__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_214[13] = { /* code 214 */
  __X___X_,
  ________,
  ___XXX__,
  __X___X_,
  _X_____X,
  _X_____X,
  _X_____X,
  _X_____X,
  _X_____X,
  __X___X_,
  ___XXX__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_215[13] = { /* code 215 */
  ________,
  ________,
  ________,
  ________,
  _X_____X,
  __X___X_,
  ___X_X__,
  ____X___,
  ___X_X__,
  __X___X_,
  _X_____X,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_216[13] = { /* code 216 */
  ________,
  ________,
  ___XXX_X,
  __X___X_,
  _X___X_X,
  _X___X_X,
  _X__X__X,
  _X_X___X,
  _X_X___X,
  __X___X_,
  _X_XXX__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_217[13] = { /* code 217 */
  ___X____,
  ____X___,
  _XXX_XXX,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  ___XXX__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_218[13] = { /* code 218 */
  _____X__,
  ____X___,
  _XXX_XXX,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  ___XXX__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_219[13] = { /* code 219 */
  ____X___,
  ___X_X__,
  _XXX_XXX,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  ___XXX__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_220[13] = { /* code 220 */
  __X___X_,
  ________,
  _XXX_XXX,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  ___XXX__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_221[13] = { /* code 221 */
  _____X__,
  ____X___,
  _XXX_XXX,
  __X___X_,
  __X___X_,
  ___X_X__,
  ___X_X__,
  ____X___,
  ____X___,
  ____X___,
  ___XXX__,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_222[13] = { /* code 222 */
  ________,
  ________,
  _XX_____,
  __X_____,
  __XXXXX_,
  __X____X,
  __X____X,
  __X____X,
  __XXXXX_,
  __X_____,
  _XXX____,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_223[13] = { /* code 223 */
  ________,
  ________,
  ___XXX__,
  __X___X_,
  __X___X_,
  __X___X_,
  __X_XXX_,
  __X____X,
  __X____X,
  __X____X,
  _XX_XXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_224[13] = { /* code 224 */
  ________,
  ________,
  ___X____,
  ____X___,
  ________,
  __XXXX__,
  ______X_,
  __XXXXX_,
  _X____X_,
  _X____X_,
  __XXXX_X,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_225[13] = { /* code 225 */
  ________,
  ________,
  _____X__,
  ____X___,
  ________,
  __XXXX__,
  ______X_,
  __XXXXX_,
  _X____X_,
  _X____X_,
  __XXXX_X,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_226[13] = { /* code 226 */
  ________,
  ________,
  ____X___,
  ___X_X__,
  ________,
  __XXXX__,
  ______X_,
  __XXXXX_,
  _X____X_,
  _X____X_,
  __XXXX_X,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_227[13] = { /* code 227 */
  ________,
  ________,
  __XXX__X,
  _X__XXX_,
  ________,
  __XXXX__,
  ______X_,
  __XXXXX_,
  _X____X_,
  _X____X_,
  __XXXX_X,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_228[13] = { /* code 228 */
  ________,
  ________,
  __X___X_,
  ________,
  ________,
  __XXXX__,
  ______X_,
  __XXXXX_,
  _X____X_,
  _X____X_,
  __XXXX_X,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_229[13] = { /* code 229 */
  ________,
  ____X___,
  ___X_X__,
  ____X___,
  ________,
  __XXXX__,
  ______X_,
  __XXXXX_,
  _X____X_,
  _X____X_,
  __XXXX_X,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_230[13] = { /* code 230 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __XX_XX_,
  ____X__X,
  __XXXXXX,
  _X__X___,
  _X__X__X,
  __XX_XX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_231[13] = { /* code 231 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXXXX_,
  _X_____X,
  _X______,
  _X______,
  _X_____X,
  __XXXXX_,
  _____X__,
  ____XX__};

GUI_FLASH const unsigned char acF8x13_232[13] = { /* code 232 */
  ________,
  ________,
  ___X____,
  ____X___,
  ________,
  __XXXXX_,
  _X_____X,
  _XXXXXXX,
  _X______,
  _X_____X,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_233[13] = { /* code 233 */
  ________,
  ________,
  _____X__,
  ____X___,
  ________,
  __XXXXX_,
  _X_____X,
  _XXXXXXX,
  _X______,
  _X_____X,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_234[13] = { /* code 234 */
  ________,
  ________,
  ____X___,
  ___X_X__,
  ________,
  __XXXXX_,
  _X_____X,
  _XXXXXXX,
  _X______,
  _X_____X,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_235[13] = { /* code 235 */
  ________,
  ________,
  __X___X_,
  ________,
  ________,
  __XXXXX_,
  _X_____X,
  _XXXXXXX,
  _X______,
  _X_____X,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_236[13] = { /* code 236 */
  ________,
  ________,
  ___X____,
  ____X___,
  ________,
  __XXX___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_237[13] = { /* code 237 */
  ________,
  ________,
  ____X___,
  ___X____,
  ________,
  __XXX___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_238[13] = { /* code 238 */
  ________,
  ________,
  ____X___,
  ___X_X__,
  ________,
  __XXX___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_239[13] = { /* code 239 */
  ________,
  ________,
  __X__X__,
  ________,
  ________,
  __XXX___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_240[13] = { /* code 240 */
  ________,
  ________,
  __XX_XX_,
  ____X___,
  __XX_X__,
  ______X_,
  __XXXXX_,
  _X_____X,
  _X_____X,
  _X_____X,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_241[13] = { /* code 241 */
  ________,
  ________,
  __XXX__X,
  _X__XXX_,
  ________,
  _XX_XX__,
  __XX__X_,
  __X___X_,
  __X___X_,
  __X___X_,
  _XXX_XXX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_242[13] = { /* code 242 */
  ________,
  ________,
  ___X____,
  ____X___,
  ________,
  __XXXXX_,
  _X_____X,
  _X_____X,
  _X_____X,
  _X_____X,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_243[13] = { /* code 243 */
  ________,
  ________,
  _____X__,
  ____X___,
  ________,
  __XXXXX_,
  _X_____X,
  _X_____X,
  _X_____X,
  _X_____X,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_244[13] = { /* code 244 */
  ________,
  ________,
  ____X___,
  ___X_X__,
  ________,
  __XXXXX_,
  _X_____X,
  _X_____X,
  _X_____X,
  _X_____X,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_245[13] = { /* code 245 */
  ________,
  ________,
  __XXX__X,
  _X__XXX_,
  ________,
  __XXXXX_,
  _X_____X,
  _X_____X,
  _X_____X,
  _X_____X,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_246[13] = { /* code 246 */
  ________,
  ________,
  __X___X_,
  ________,
  ________,
  __XXXXX_,
  _X_____X,
  _X_____X,
  _X_____X,
  _X_____X,
  __XXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_247[13] = { /* code 247 */
  ________,
  ________,
  ________,
  ________,
  ____X___,
  ________,
  ________,
  _XXXXXXX,
  ________,
  ________,
  ____X___,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_248[13] = { /* code 248 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXXXXX,
  _X____XX,
  _X__XX_X,
  _X_XX__X,
  _XX____X,
  _XXXXXX_,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_249[13] = { /* code 249 */
  ________,
  ________,
  ___X____,
  ____X___,
  ________,
  _XX__XX_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X__XX_,
  ___XX_XX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_250[13] = { /* code 250 */
  ________,
  ________,
  _____X__,
  ____X___,
  ________,
  _XX__XX_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X__XX_,
  ___XX_XX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_251[13] = { /* code 251 */
  ________,
  ________,
  ____X___,
  ___X_X__,
  ________,
  _XX__XX_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X__XX_,
  ___XX_XX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_252[13] = { /* code 252 */
  ________,
  ________,
  __X___X_,
  ________,
  ________,
  _XX__XX_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X__XX_,
  ___XX_XX,
  ________,
  ________};

GUI_FLASH const unsigned char acF8x13_253[13] = { /* code 253 */
  ________,
  ________,
  _____X__,
  ____X___,
  ________,
  _XXX_XXX,
  __X___X_,
  __X___X_,
  ___X_X__,
  ___X_X__,
  ____X___,
  ____X___,
  __XX____};

GUI_FLASH const unsigned char acF8x13_254[13] = { /* code 254 */
  ________,
  ________,
  _XX_____,
  __X_____,
  __X_____,
  __XXXXX_,
  __X____X,
  __X____X,
  __X____X,
  __X____X,
  __XXXXX_,
  __X_____,
  _XXX____};

GUI_FLASH const unsigned char acF8x13_255[13] = { /* code 255 */
  ________,
  ________,
  __X___X_,
  ________,
  ________,
  _XXX_XXX,
  __X___X_,
  __X___X_,
  ___X_X__,
  ___X_X__,
  ____X___,
  ____X___,
  __XX____};



GUI_FLASH const GUI_CHARINFO CharInfoF8x13[192] = {
   {   8,   8,  1, (void GUI_FLASH *)&acF8x13_32 } /* code  32 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_33 } /* code  33 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_34 } /* code  34 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_35 } /* code  35 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_36 } /* code  36 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_37 } /* code  37 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_38 } /* code  38 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_39 } /* code  39 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_40 } /* code  40 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_41 } /* code  41 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_42 } /* code  42 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_43 } /* code  43 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_44 } /* code  44 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_45 } /* code  45 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_46 } /* code  46 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_47 } /* code  47 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_48 } /* code  48 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_49 } /* code  49 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_50 } /* code  50 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_51 } /* code  51 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_52 } /* code  52 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_53 } /* code  53 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_54 } /* code  54 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_55 } /* code  55 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_56 } /* code  56 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_57 } /* code  57 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_58 } /* code  58 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_59 } /* code  59 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_60 } /* code  60 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_61 } /* code  61 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_62 } /* code  62 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_63 } /* code  63 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_64 } /* code  64 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_65 } /* code  65 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_66 } /* code  66 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_67 } /* code  67 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_68 } /* code  68 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_69 } /* code  69 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_70 } /* code  70 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_71 } /* code  71 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_72 } /* code  72 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_73 } /* code  73 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_74 } /* code  74 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_75 } /* code  75 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_76 } /* code  76 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_77 } /* code  77 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_78 } /* code  78 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_79 } /* code  79 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_80 } /* code  80 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_81 } /* code  81 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_82 } /* code  82 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_83 } /* code  83 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_84 } /* code  84 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_85 } /* code  85 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_86 } /* code  86 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_87 } /* code  87 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_88 } /* code  88 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_89 } /* code  89 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_90 } /* code  90 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_91 } /* code  91 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_92 } /* code  92 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_93 } /* code  93 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_94 } /* code  94 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_95 } /* code  95 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_96 } /* code  96 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_97 } /* code  97 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_98 } /* code  98 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_99 } /* code  99 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_100 } /* code 100 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_101 } /* code 101 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_102 } /* code 102 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_103 } /* code 103 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_104 } /* code 104 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_105 } /* code 105 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_106 } /* code 106 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_107 } /* code 107 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_108 } /* code 108 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_109 } /* code 109 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_110 } /* code 110 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_111 } /* code 111 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_112 } /* code 112 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_113 } /* code 113 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_114 } /* code 114 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_115 } /* code 115 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_116 } /* code 116 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_117 } /* code 117 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_118 } /* code 118 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_119 } /* code 119 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_120 } /* code 120 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_121 } /* code 121 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_122 } /* code 122 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_123 } /* code 123 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_124 } /* code 124 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_125 } /* code 125 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_126 } /* code 126 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_127 } /* code 127 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_160 } /* code 160 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_161 } /* code 161 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_162 } /* code 162 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_163 } /* code 163 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_164 } /* code 164 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_165 } /* code 165 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_166 } /* code 166 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_167 } /* code 167 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_168 } /* code 168 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_169 } /* code 169 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_170 } /* code 170 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_171 } /* code 171 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_172 } /* code 172 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_173 } /* code 173 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_174 } /* code 174 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_175 } /* code 175 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_176 } /* code 176 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_177 } /* code 177 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_178 } /* code 178 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_179 } /* code 179 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_180 } /* code 180 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_181 } /* code 181 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_182 } /* code 182 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_183 } /* code 183 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_184 } /* code 184 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_185 } /* code 185 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_186 } /* code 186 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_187 } /* code 187 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_188 } /* code 188 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_189 } /* code 189 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_190 } /* code 190 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_191 } /* code 191 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_192 } /* code 192 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_193 } /* code 193 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_194 } /* code 194 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_195 } /* code 195 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_196 } /* code 196 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_197 } /* code 197 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_198 } /* code 198 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_199 } /* code 199 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_200 } /* code 200 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_201 } /* code 201 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_202 } /* code 202 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_203 } /* code 203 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_204 } /* code 204 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_205 } /* code 205 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_206 } /* code 206 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_207 } /* code 207 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_208 } /* code 208 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_209 } /* code 209 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_210 } /* code 210 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_211 } /* code 211 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_212 } /* code 212 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_213 } /* code 213 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_214 } /* code 214 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_215 } /* code 215 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_216 } /* code 216 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_217 } /* code 217 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_218 } /* code 218 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_219 } /* code 219 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_220 } /* code 220 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_221 } /* code 221 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_222 } /* code 222 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_223 } /* code 223 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_224 } /* code 224 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_225 } /* code 225 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_226 } /* code 226 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_227 } /* code 227 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_228 } /* code 228 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_229 } /* code 229 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_230 } /* code 230 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_231 } /* code 231 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_232 } /* code 232 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_233 } /* code 233 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_234 } /* code 234 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_235 } /* code 235 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_236 } /* code 236 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_237 } /* code 237 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_238 } /* code 238 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_239 } /* code 239 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_240 } /* code 240 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_241 } /* code 241 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_242 } /* code 242 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_243 } /* code 243 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_244 } /* code 244 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_245 } /* code 245 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_246 } /* code 246 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_247 } /* code 247 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_248 } /* code 248 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_249 } /* code 249 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_250 } /* code 250 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_251 } /* code 251 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_252 } /* code 252 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_253 } /* code 253 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_254 } /* code 254 */
  ,{   8,   8,  1, (void GUI_FLASH *)&acF8x13_255 } /* code 255 */
};

GUI_FLASH const GUI_FONT_PROP FontPropF8x13_2 = {
   160            /* first character               */
  ,255            /* last character                */
  ,&CharInfoF8x13[96] /* address of first character    */
  ,(void GUI_FLASH *)0            /* pointer to next GUI_FONT_PROP */
};

GUI_FLASH const GUI_FONT_PROP FontPropF8x13_1 = {
   32            /* first character               */
  ,127            /* last character                */
  ,&CharInfoF8x13[0] /* address of first character    */
  ,(void GUI_FLASH *)&FontPropF8x13_2            /* pointer to next GUI_FONT_PROP */
};

GUI_FLASH const GUI_FONT GUI_Font8x13 = {
   GUI_FONTTYPE_PROP /* type of font    */
  ,13                /* height of font  */
  ,13                /* space of font y */
  ,1                /* magnification x */
  ,1                /* magnification y */
  ,(void GUI_FLASH *)&FontPropF8x13_1
};

