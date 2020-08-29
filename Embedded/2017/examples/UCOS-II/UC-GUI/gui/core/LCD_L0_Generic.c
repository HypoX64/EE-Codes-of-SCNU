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
File        : LCD_L0_Generic.h
Purpose     : Color conversion routines for LCD-drivers
              This file may not be compiled by itself, bud needs
              to be included in every LCD driver
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "LCD_Private.H"      /* private modul definitions & config */
#include "GUI_Private.H"
#include "GUIDebug.h"

/*
        *********************************************************
        *                                                       *
        *                  Color info                           *
        *                                                       *
        *********************************************************
*/


#if (LCD_FIXEDPALETTE==0)
  static 
  #if !LCD_PHYSCOLORS_IN_RAM
    const
  #endif
  LCD_COLOR       LCD_PhysColors[] = { LCD_PHYSCOLORS };
  const LCD_PHYSPALETTE LCD_PhysPal      = { LCD_NUM_COLORS, &LCD_PhysColors[0] };
#endif

#if LCD_NUM_DISPLAYS > 1
  #if (LCD_FIXEDPALETTE_1 == 0)
    static  const LCD_COLOR       LCD_PhysColors_[] = { LCD_PHYSCOLORS_1 };
            const LCD_PHYSPALETTE LCD_PhysPal_      = { LCD_NUM_COLORS_1, &LCD_PhysColors_1[0] };
  #endif
#endif

/*
      *************************************************
      *                                               *
      *             LCD Device                        *
			*       (if memory devices are supported)       *
      *                                               *
      *************************************************
*/
#if GUI_SUPPORT_MEMDEV

const tLCDDEV_APIList LCD_L0_APIList = {

#if LCD_YMAG==1
  LCD_L0_Color2Index,
  LCD_L0_DrawBitmap,
  LCD_L0_DrawHLine,
  LCD_L0_DrawVLine,
  LCD_L0_FillRect,
  LCD_L0_GetPixelIndex,
  LCD_L0_GetRect,
  LCD_L0_Index2Color,
  LCD_L0_SetPixelIndex,
  LCD_L0_XorPixel
#else
  LCD_L0_Color2Index,
  LCD_L0_MAG_DrawBitmap,
  LCD_L0_MAG_DrawHLine,
  LCD_L0_MAG_DrawVLine,
  LCD_L0_MAG_FillRect,
  LCD_L0_MAG_GetPixelIndex,
  LCD_L0_GetRect,          /* Original routine is o.k. here, since we use the logical
                                 coordinates for clipping, which are not magnified */
  LCD_L0_Index2Color,
  LCD_L0_MAG_SetPixelIndex,
  LCD_L0_MAG_XorPixel,
#endif
};

#endif




/*********************************************************************
*
*           Color conversion routines display 0
*
**********************************************************************
*/

#if   LCD_FIXEDPALETTE == 0
  #define COLOR2INDEX(Color) LCD_Color2Index_0(Color, &LCD_PhysPal)
  #define INDEX2COLOR(Index) LCD_Index2Color_0(Index, &LCD_PhysPal)
#elif LCD_FIXEDPALETTE == 1
  #define COLOR2INDEX(Color) LCD_Color2Index_1(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_1(Index)
#elif LCD_FIXEDPALETTE == 2
  #define COLOR2INDEX(Color) LCD_Color2Index_2(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_2(Index)
#elif LCD_FIXEDPALETTE == 4
  #define COLOR2INDEX(Color) LCD_Color2Index_4(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_4(Index)
#elif (LCD_FIXEDPALETTE == 111) && (LCD_SWAP_RB==0)
  #define COLOR2INDEX(Color) LCD_Color2Index_111(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_111(Index)
#elif (LCD_FIXEDPALETTE == 111) && (LCD_SWAP_RB)
  #define COLOR2INDEX(Color) LCD_Color2Index_M111(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_M111(Index)
#elif (LCD_FIXEDPALETTE == 222) && (LCD_SWAP_RB==0)
  #define COLOR2INDEX(Color) LCD_Color2Index_222(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_222(Index)
#elif (LCD_FIXEDPALETTE == 222) && (LCD_SWAP_RB==1)
  #define COLOR2INDEX(Color) LCD_Color2Index_M222(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_M222(Index)
#elif (LCD_FIXEDPALETTE == 233) && (LCD_SWAP_RB==0)
  #define COLOR2INDEX(Color) LCD_Color2Index_233(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_233(Index)
#elif (LCD_FIXEDPALETTE == 233) && (LCD_SWAP_RB==1)
  #define COLOR2INDEX(Color) LCD_Color2Index_M233(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_M233(Index)
#elif (LCD_FIXEDPALETTE == 323) && (LCD_SWAP_RB==0)
  #define COLOR2INDEX(Color) LCD_Color2Index_323(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_323(Index)
#elif (LCD_FIXEDPALETTE == 323) && (LCD_SWAP_RB==1)
  #define COLOR2INDEX(Color) LCD_Color2Index_M323(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_M323(Index)
#elif (LCD_FIXEDPALETTE == 332) && (LCD_SWAP_RB==0)
#error askdfad
  #define COLOR2INDEX(Color) LCD_Color2Index_332(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_332(Index)
#elif (LCD_FIXEDPALETTE == 332) && (LCD_SWAP_RB==1)
  #define COLOR2INDEX(Color) LCD_Color2Index_M332(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_M332(Index)
#elif (LCD_FIXEDPALETTE == 444)  && (LCD_SWAP_RB==0)
  #define COLOR2INDEX(Color) LCD_Color2Index_444(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_444(Index)
#elif (LCD_FIXEDPALETTE == 555)  && (LCD_SWAP_RB==0)
  #define COLOR2INDEX(Color) LCD_Color2Index_555(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_555(Index)
#elif (LCD_FIXEDPALETTE == 555)  && (LCD_SWAP_RB)
  #define COLOR2INDEX(Color) LCD_Color2Index_M555(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_M555(Index)
#elif (LCD_FIXEDPALETTE == 565) && (LCD_SWAP_RB==0)
  #define COLOR2INDEX(Color) LCD_Color2Index_565(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_565(Index)
#elif (LCD_FIXEDPALETTE == 565) && (LCD_SWAP_RB)
  #define COLOR2INDEX(Color) LCD_Color2Index_M565(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_M565(Index)
#elif LCD_FIXEDPALETTE == 8666
  #define COLOR2INDEX(Color) LCD_Color2Index_8666(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_8666(Index)
#else
  #error Unsupported color mode
#endif


unsigned int LCD_L0_Color2Index(LCD_COLOR Color) {
  unsigned int Index;
  Index = COLOR2INDEX(Color);
  #if LCD_REVERSE
    Index ^= ((1<<LCD_BITSPERPIXEL)-1);
  #endif
  return Index;
}

LCD_COLOR LCD_L0_Index2Color(int Index) {
  #if LCD_REVERSE
    Index ^= ((1<<LCD_BITSPERPIXEL)-1);
  #endif
  return INDEX2COLOR(Index);
}

/*********************************************************************
*
*           LCD_L0_GetRect
*
**********************************************************************

*/
void LCD_L0_GetRect (LCD_RECT *pRect) {
  pRect->x0 = 0;
  pRect->y0 = 0;
  pRect->x1 = LCD_XSIZE-1;
  pRect->y1 = LCD_YSIZE-1;
}


/*********************************************************************
*
*           Color conversion routines display 1
*
**********************************************************************
*/

#if LCD_NUM_DISPLAYS > 1
  #undef COLOR2INDEX
  #undef INDEX2COLOR
  #if   LCD_FIXEDPALETTE_1 == 0
    #define COLOR2INDEX(Color) LCD_Color2Index_0(Color, &LCD_PhysPal)
    #define INDEX2COLOR(Index) LCD_Index2Color_0(Index, &LCD_PhysPal)
  #elif LCD_FIXEDPALETTE_1 == 1
    #define COLOR2INDEX(Color) LCD_Color2Index_1(Color)
    #define INDEX2COLOR(Index) LCD_Index2Color_1(Index)
  #elif LCD_FIXEDPALETTE_1 == 2
    #define COLOR2INDEX(Color) LCD_Color2Index_2(Color)
    #define INDEX2COLOR(Index) LCD_Index2Color_2(Index)
  #elif LCD_FIXEDPALETTE_1 == 4
    #define COLOR2INDEX(Color) LCD_Color2Index_4(Color)
    #define INDEX2COLOR(Index) LCD_Index2Color_4(Index)
  #elif (LCD_FIXEDPALETTE_1 == 111) && (LCD_SWAP_RB_1==0)
    #define COLOR2INDEX(Color) LCD_Color2Index_111(Color)
    #define INDEX2COLOR(Index) LCD_Index2Color_111(Index)
  #elif (LCD_FIXEDPALETTE_1 == 111) && (LCD_SWAP_RB_1)
    #define COLOR2INDEX(Color) LCD_Color2Index_M111(Color)
    #define INDEX2COLOR(Index) LCD_Index2Color_M111(Index)
  #elif (LCD_FIXEDPALETTE_1 == 222) && (LCD_SWAP_RB_1==0)
    #define COLOR2INDEX(Color) LCD_Color2Index_222(Color)
    #define INDEX2COLOR(Index) LCD_Index2Color_222(Index)
  #elif (LCD_FIXEDPALETTE_1 == 222) && (LCD_SWAP_RB_1==1)
    #define COLOR2INDEX(Color) LCD_Color2Index_M222(Color)
    #define INDEX2COLOR(Index) LCD_Index2Color_M222(Index)
  #elif (LCD_FIXEDPALETTE_1 == 233) && (LCD_SWAP_RB_1==0)
    #define COLOR2INDEX(Color) LCD_Color2Index_233(Color)
    #define INDEX2COLOR(Index) LCD_Index2Color_233(Index)
  #elif (LCD_FIXEDPALETTE_1 == 233) && (LCD_SWAP_RB_1==1)
    #define COLOR2INDEX(Color) LCD_Color2Index_M233(Color)
    #define INDEX2COLOR(Index) LCD_Index2Color_M233(Index)
  #elif (LCD_FIXEDPALETTE_1 == 323) && (LCD_SWAP_RB_1==0)
    #define COLOR2INDEX(Color) LCD_Color2Index_323(Color)
    #define INDEX2COLOR(Index) LCD_Index2Color_323(Index)
  #elif (LCD_FIXEDPALETTE_1 == 323) && (LCD_SWAP_RB_1==1)
    #define COLOR2INDEX(Color) LCD_Color2Index_M323(Color)
    #define INDEX2COLOR(Index) LCD_Index2Color_M323(Index)
  #elif (LCD_FIXEDPALETTE_1 == 332) && (LCD_SWAP_RB_1==0)
    #define COLOR2INDEX(Color) LCD_Color2Index_332(Color)
    #define INDEX2COLOR(Index) LCD_Index2Color_332(Index)
  #elif (LCD_FIXEDPALETTE_1 == 332) && (LCD_SWAP_RB_1==1)
    #define COLOR2INDEX(Color) LCD_Color2Index_M332(Color)
    #define INDEX2COLOR(Index) LCD_Index2Color_M332(Index)
  #elif (LCD_FIXEDPALETTE_1 == 555)  && (LCD_SWAP_RB_1==0)
    #define COLOR2INDEX(Color) LCD_Color2Index_555(Color)
    #define INDEX2COLOR(Index) LCD_Index2Color_555(Index)
  #elif (LCD_FIXEDPALETTE_1 == 555)  && (LCD_SWAP_RB_1)
    #define COLOR2INDEX(Color) LCD_Color2Index_M555(Color)
    #define INDEX2COLOR(Index) LCD_Index2Color_M555(Index)
  #elif (LCD_FIXEDPALETTE_1 == 565) && (LCD_SWAP_RB_1==0)
    #define COLOR2INDEX(Color) LCD_Color2Index_565(Color)
    #define INDEX2COLOR(Index) LCD_Index2Color_565(Index)
  #elif (LCD_FIXEDPALETTE_1 == 565) && (LCD_SWAP_RB_1)
    #define COLOR2INDEX(Color) LCD_Color2Index_M565(Color)
    #define INDEX2COLOR(Index) LCD_Index2Color_M565(Index)
  #elif LCD_FIXEDPALETTE_1 == 8666
    #define COLOR2INDEX(Color) LCD_Color2Index_8666(Color)
    #define INDEX2COLOR(Index) LCD_Index2Color_8666(Index)
  #else
    #error Unsupported color mode
  #endif


  unsigned int LCD_L0_1_Color2Index(LCD_COLOR Color) {
    unsigned int Index;
    Index = COLOR2INDEX(Color);
    #if LCD_REVERSE
      Index ^= ((1<<LCD_BITSPERPIXEL)-1);
    #endif
    return Index;
  }

  LCD_COLOR LCD_L0_1_Index2Color(int Index) {
    #if LCD_REVERSE
      Index ^= ((1<<LCD_BITSPERPIXEL)-1);
    #endif
    return INDEX2COLOR(Index);
  }
  /*********************************************************************
  *
  *           LCD_L0_1_GetRect
  *
  **********************************************************************

  */
  void LCD_L0_1_GetRect (LCD_RECT *pRect) {
    pRect->x0 = 0;
    pRect->y0 = 0;
    pRect->x1 = LCD_XSIZE_1 - 1;
    pRect->y1 = LCD_YSIZE_1 - 1;
  }

#endif




