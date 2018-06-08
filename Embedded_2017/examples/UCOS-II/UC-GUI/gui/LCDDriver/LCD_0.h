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
File        : LCD_0.C
Purpose     : Glue defines for first display in a multi-controller
              environment
---------------------------END-OF-HEADER------------------------------
*/



#if ( (LCD_NUM_DISPLAYS > 1) && !defined(LCD_1_C) && !defined(LCD_2_C) && !defined(LCD_3_C))


/*********************************************************************
*
*      Map the defines for this controller
*
*      #define LCD_<xxx> LCD_<xxx>_0
*
**********************************************************************
*/
  #ifdef  LCD_CONTROLLER_0
    #define LCD_CONTROLLER     LCD_CONTROLLER_0
  #endif

  #ifdef LCD_XSIZE_0
    #define LCD_XSIZE          LCD_XSIZE_0
  #endif

  #ifdef  LCD_YSIZE_0
    #define LCD_YSIZE          LCD_YSIZE_0
  #endif

  #ifdef  LCD_BITSPERPIXEL_0
    #define LCD_BITSPERPIXEL   LCD_BITSPERPIXEL_0
  #endif

  #ifdef  LCD_VYSIZE_0
    #define LCD_VYSIZE          LCD_VYSIZE_0
  #endif

  #ifdef LCD_MIRROR_X_0
    #undef  LCD_MIRROR_X
    #define LCD_MIRROR_X  LCD_MIRROR_X_0
  #endif

  #ifdef LCD_MIRROR_Y_0
    #undef  LCD_MIRROR_Y
    #define LCD_MIRROR_Y  LCD_MIRROR_Y_0
  #endif

  #ifdef LCD_SWAP_XY_0
    #undef  LCD_SWAP_XY
    #define LCD_SWAP_XY   LCD_SWAP_XY_0
  #endif

  #ifdef LCD_BITSPERPIXEL_0
    #define LCD_BITSPERPIXEL LCD_BITSPERPIXEL_0
  #endif

  #ifdef LCD_CACHE_CONTROL_0
    #define LCD_CACHE_CONTROL LCD_CACHE_CONTROL_0
  #endif

  #ifdef LCD_FIRSTSEG0_0
    #undef  LCD_FIRSTSEG0
    #define LCD_FIRSTSEG0   LCD_FIRSTSEG0_0
  #endif

  #ifdef LCD_LASTSEG0_0
    #undef  LCD_LASTSEG0
    #define LCD_LASTSEG0    LCD_LASTSEG0_0
  #endif

  #ifdef LCD_FIRSTCOM0_0
    #undef  LCD_FIRSTCOM0
    #define LCD_FIRSTCOM0   LCD_FIRSTCOM0_0
  #endif

  #ifdef LCD_LASTCOM0_0
    #undef  LCD_LASTCOM0
    #define LCD_LASTCOM0    LCD_LASTCOM0_0
  #endif

  #ifdef LCD_XORG0_0
    #undef  LCD_XORG0
    #define LCD_XORG0       LCD_XORG0_0
  #endif

  #ifdef LCD_YORG0_0
    #undef  LCD_YORG0
    #define LCD_YORG0       LCD_YORG0_0
  #endif

#endif

/*********************************************************************
*
*      Some error checking
*
**********************************************************************
*/
  #ifndef LCD_CONTROLLER
    #error LCD_CONTROLLER not defined !
  #endif

