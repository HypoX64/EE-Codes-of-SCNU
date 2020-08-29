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
File        : GUI_SelLCD.C
Purpose     : emWin GSC, selection of LCD display
---------------------------END-OF-HEADER------------------------------
*/


#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Private.H"
#include "GUIDebug.h"
#include "LCD_Private.h"      /* Required for configuration, APIList */


#if (LCD_NUM_DISPLAYS > 1) && (GUI_SUPPORT_MEMDEV)

/*
      *************************************************
      *                                               *
      *             LCD Device                        *
			*       (if memory devices are supported)       *
      *                                               *
      *************************************************
*/

const tLCDDEV_APIList LCD_L0_1_APIList = {
#if LCD_YMAG_1 == 1
  LCD_L0_1_Color2Index,
  LCD_L0_1_DrawBitmap,
  LCD_L0_1_DrawHLine,
  LCD_L0_1_DrawVLine,
  LCD_L0_1_FillRect,
  LCD_L0_1_GetPixelIndex,
  LCD_L0_1_GetRect,
  LCD_L0_1_Index2Color,
  LCD_L0_1_SetPixelIndex,
  LCD_L0_1_XorPixel
#else
  LCD_L0_1_Color2Index,
  LCD_L0_1_MAG_DrawBitmap,
  LCD_L0_1_MAG_DrawHLine,
  LCD_L0_1_MAG_DrawVLine,
  LCD_L0_1_MAG_FillRect,
  LCD_L0_1_MAG_GetPixelIndex,
  LCD_L0_1_GetRect,          /* Original routine is o.k. here, since we use the logical
                                 coordinates for clipping, which are not magnified */
  LCD_L0_1_Index2Color,
  LCD_L0_1_MAG_SetPixelIndex,
  LCD_L0_1_MAG_XorPixel
#endif
};



/***********************************************************
*
*                 GUI_SelLCD
*
************************************************************

*/


const tLCDDEV_APIList * const aAPI[] = {
  &LCD_L0_APIList
#if LCD_NUM_DISPLAYS >1
  ,&LCD_L0_1_APIList
#endif
};


unsigned int GUI_SelLCD(unsigned int Index) {
  unsigned int OldIndex = 0;
  if (Index < LCD_NUM_DISPLAYS) {
    GUI_LOCK();
    GUI_SetDefault();
    OldIndex = (GUI_Context.pDeviceAPI == aAPI[0]) ? 0 : 1;
    GUI_Context.pDeviceAPI = aAPI[Index];
    LCD_SetClipRectMax();
  }
  GUI_UNLOCK();
  return OldIndex;
}

#else

void GUI_SelLCD_(void) {}

#endif
