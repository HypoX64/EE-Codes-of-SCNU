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
File        : LCD_ConfDefaults.h
Purpose     : Valid LCD configuration and defaults
----------------------------------------------------------------------
*/

#ifndef LCD_CONFIG_DEFAULTS_H
#define LCD_CONFIG_DEFAULTS_H

#include "LCDConf.H"            /* Configuration header file */

/*******************************************************************
*
*               Defaults for config switches
*
********************************************************************
*/

#if !defined (LCD_NUM_DISPLAYS)
  #define LCD_NUM_DISPLAYS 1
#endif


#ifndef LCD_NUM_CONTROLLERS
  #define LCD_NUM_CONTROLLERS (1)
#endif

#ifndef LCD_NUM_COLORS
  #define LCD_NUM_COLORS (1L<<LCD_BITSPERPIXEL)
#endif



/*********************************************************************
*
*      Map the defines for controller 0 to general defines
*
**********************************************************************
*/
#ifndef LCD_MIRROR_X
  #define LCD_MIRROR_X   (0)    /* If active:  X -> -X */
#endif
#ifndef LCD_MIRROR_Y
  #define LCD_MIRROR_Y   (0)    /* If active:  Y -> -Y */
#endif
#ifndef LCD_SWAP_XY
  #define LCD_SWAP_XY    (0)    /* If active:  X <-> Y */
#endif

#ifndef LCD_XORG
  #define LCD_XORG        0     /* X-origin in log.coor., usually 0 */
#endif
#ifndef LCD_YORG
  #define LCD_YORG        0     /* Y-origin in log.coor., usually 0 */
#endif

/* Allow use of multiple physical lines for one logical line ...
   Used for delta-type LCDs, where value should be 2 */

#ifndef LCD_YMAG
  #define LCD_YMAG 1
#endif
#ifndef LCD_XMAG
  #define LCD_XMAG 1
#endif

#ifndef LCD_VXSIZE
  #define LCD_VXSIZE      (LCD_XSIZE*LCD_XMAG) /* virtual x-size */
#endif
#ifndef LCD_VYSIZE
  #define LCD_VYSIZE      (LCD_YSIZE*LCD_YMAG) /* virtual y-size */
#endif

#ifndef LCD_SWAP_BYTE_ORDER
  #define LCD_SWAP_BYTE_ORDER (0)    /* only for 16 bit bus, default is not swapped */
#endif

#ifndef  LCD_MAX_LOG_COLORS
  #define  LCD_MAX_LOG_COLORS (256)
#endif

#ifndef LCD_REVERSE
  #define LCD_REVERSE 0
#endif


#define LCD_SWAP_RB 1 // added by liusj
/* Optionally swap red and blue components */
#ifndef LCD_SWAP_RB
  #define LCD_SWAP_RB 0
#endif

#if !defined (LCD_CONTROLLER) && defined (LCD_CONTROLLER_0)
  #define LCD_CONTROLLER LCD_CONTROLLER_0
#endif

#if !defined (LCD_XSIZE) && defined (LCD_XSIZE_0)
  #define LCD_XSIZE          LCD_XSIZE_0
#endif

#if !defined (LCD_YSIZE) && defined (LCD_YSIZE_0)
  #define LCD_YSIZE          LCD_YSIZE_0
#endif

#if !defined (LCD_BITSPERPIXEL) && defined (LCD_BITSPERPIXEL_0)
  #define LCD_BITSPERPIXEL   LCD_BITSPERPIXEL_0
#endif

#if !defined (LCD_VYSIZE) && defined (LCD_VYSIZE_0)
  #define LCD_VYSIZE          LCD_VYSIZE_0
#endif

/*********************************************************************
*
*      Defaults for Display 0 (first display)
*
**********************************************************************
*/

#ifndef LCD_MIRROR_X
  #define LCD_MIRROR_X   (0)    /* If active:  X -> -X */
#endif
#ifndef LCD_MIRROR_Y
  #define LCD_MIRROR_Y   (0)    /* If active:  Y -> -Y */
#endif
#ifndef LCD_SWAP_XY
  #define LCD_SWAP_XY    (0)    /* If active:  X <-> Y */
#endif

/* Position data for controller 0 */
#ifndef LCD_XORG0
  #define LCD_XORG0     (0)     /* leftmost position covered by this controller */
#endif
#ifndef LCD_YORG0
  #define LCD_YORG0     (0)     /* topmost position covered by this controller */
#endif
#ifndef LCD_XSIZE0
  #define LCD_XSIZE0    (LCD_XSIZE)   /* horizontal size covered by this controller */
#endif
#ifndef LCD_YSIZE0
 #define LCD_YSIZE0    (LCD_YSIZE)   /* vertical size covered by this controller */
#endif
#ifndef LCD_FIRSTSEG0
  #define LCD_FIRSTSEG0 (0)     /* first segment used by this controller */
#endif
#ifndef LCD_LASTSEG0
  #define LCD_LASTSEG0    (LCD_XSIZE-1) /* Contr.0: last segment line used */
#endif
#ifndef LCD_FIRSTCOM0
  #define LCD_FIRSTCOM0 (0)     /* first com used by this controller */
#endif
#ifndef LCD_LASTCOM0
  #define LCD_LASTCOM0    (LCD_YSIZE-1) /* Contr.0: last com line used */
#endif

#if (!LCD_SWAP_XY)
  #define LCD_XSIZE_PHYS  LCD_XSIZE
  #define LCD_YSIZE_PHYS  LCD_YSIZE
  #define LCD_VXSIZE_PHYS LCD_VXSIZE
  #define LCD_VYSIZE_PHYS LCD_VYSIZE
#else
  #define LCD_XSIZE_PHYS  LCD_YSIZE
  #define LCD_YSIZE_PHYS  LCD_XSIZE
  #define LCD_VXSIZE_PHYS LCD_VYSIZE
  #define LCD_VYSIZE_PHYS LCD_VXSIZE
#endif


/**********************************************************
*
*       Color settings, display 0
*
*********************************************************

*/
#ifndef LCD_REVERSE
  #define LCD_REVERSE 0
#endif

#ifndef LCD_REVERSE_LUT
  #define LCD_REVERSE_LUT 0
#endif

#ifndef LCD_PHYSCOLORS_IN_RAM
  #define LCD_PHYSCOLORS_IN_RAM 0
#endif

#if !defined (LCD_PHYSCOLORS)
  #if   (LCD_BITSPERPIXEL == 1) | (LCD_BITSPERPIXEL == 2) | (LCD_BITSPERPIXEL == 4)
    #ifndef LCD_FIXEDPALETTE
      #define LCD_FIXEDPALETTE LCD_BITSPERPIXEL
    #endif
  #endif
#endif /* defined (LCD_PHYSCOLORS) */

#if !defined (LCD_FIXEDPALETTE)
  #if !defined (LCD_PHYSCOLORS)
    #if LCD_BITSPERPIXEL == 8
//      #define LCD_FIXEDPALETTE 8666
      #define LCD_FIXEDPALETTE 332 // added by liusj
    #elif LCD_BITSPERPIXEL == 12
      #define LCD_FIXEDPALETTE 444
    #elif LCD_BITSPERPIXEL == 15
      #define LCD_FIXEDPALETTE 555
    #elif LCD_BITSPERPIXEL == 16
      #define LCD_FIXEDPALETTE 565
    #else
      #define LCD_FIXEDPALETTE 0
    #endif
  #else
    #define LCD_FIXEDPALETTE 0
  #endif
#endif

#if (LCD_BITSPERPIXEL > 8) && defined (LCD_PHYSCOLORS)
  #error List of physical colors not permitted if more than 8 bpp are used !
#endif

#if (LCD_FIXEDPALETTE==0)
  #if !defined(LCD_PHYSCOLORS)
    #error You have to define a fixed palette (LCD_FIXEDPALETTE) or
    #error the list of physical colors (LCD_PHYSCOLORS) in LCDConf.h !
  #endif
#endif


/* In order to avoid warnings for undefined parameters */
#ifndef LCD_USE_PARA
  #define LCD_USE_PARA(para) para=para;
#endif

#ifndef LCD_BITSPERPIXEL
  #if LCD_BITSPERPIXEL_0 >= LCD_BITSPERPIXEL_1
    #define LCD_BITSPERPIXEL LCD_BITSPERPIXEL_0
  #else
    #define LCD_BITSPERPIXEL LCD_BITSPERPIXEL_1
  #endif
#endif

#if LCD_BITSPERPIXEL <=8
  #define LCD_PIXELINDEX U8
#else
  #define LCD_PIXELINDEX U16
#endif


/*********************************************************************
*
*      Defaults for Display 1 (second display)
*
**********************************************************************
*/
#if LCD_NUM_DISPLAYS > 1

  #ifndef LCD_MIRROR_X_1
    #define LCD_MIRROR_X_1   (0)    /* If active:  X -> -X */
  #endif
  #ifndef LCD_MIRROR_Y_1
    #define LCD_MIRROR_Y_1   (0)    /* If active:  Y -> -Y */
  #endif
  #ifndef LCD_SWAP_XY_1
    #define LCD_SWAP_XY_1    (0)    /* If active:  X <-> Y */
  #endif

  #ifndef LCD_YMAG_1
    #define LCD_YMAG_1 1
  #endif

  #ifndef LCD_XMAG_1
    #define LCD_XMAG_1 1
  #endif

  #ifndef LCD_VXSIZE_1
    #define LCD_VXSIZE_1      (LCD_XSIZE_1 * LCD_XMAG_1) /* virtual x-size */
  #endif

  #ifndef LCD_VYSIZE_1
    #define LCD_VYSIZE_1      (LCD_YSIZE_1 * LCD_YMAG_1) /* virtual y-size */
  #endif

  #ifndef LCD_NUM_COLORS_1
    #define LCD_NUM_COLORS_1 (1L<<LCD_BITSPERPIXEL_1)
  #endif

  /* Optionally swap red and blue components */
  #ifndef LCD_SWAP_RB_1
    #define LCD_SWAP_RB_1 0
  #endif

  /**********************************************************
  *
  *       Color settings, display 0
  *
  *********************************************************

  */
  #ifndef LCD_REVERSE_1
    #define LCD_REVERSE_1 0
  #endif

  #ifndef LCD_REVERSE_LUT_1
    #define LCD_REVERSE_LUT_1 0
  #endif

  #if !defined (LCD_PHYSCOLORS_1)
    #if   (LCD_BITSPERPIXEL_1 == 1) | (LCD_BITSPERPIXEL_1 == 2) | (LCD_BITSPERPIXEL_1 == 4)
      #ifndef LCD_FIXEDPALETTE_1
        #define LCD_FIXEDPALETTE_1 LCD_BITSPERPIXEL_1
      #endif
    #endif
  #endif /* defined (LCD_PHYSCOLORS) */

  #if !defined (LCD_FIXEDPALETTE_1)
    #if !defined (LCD_PHYSCOLORS_1)
      #if LCD_BITSPERPIXEL_1 == 8
        #define LCD_FIXEDPALETTE_1 8666
      #elif LCD_BITSPERPIXEL_1 == 15
        #define LCD_FIXEDPALETTE_1 555
      #elif LCD_BITSPERPIXEL_1 == 16
        #define LCD_FIXEDPALETTE_1 565
      #else
        #define LCD_FIXEDPALETTE_1 0
      #endif
    #else
      #define LCD_FIXEDPALETTE_1 0
    #endif
  #endif

  #if (LCD_BITSPERPIXEL_1 > 8) && defined (LCD_PHYSCOLORS_1)
    #error List of physical colors not permitted if more than 8 bpp are used !
  #endif

  #if (LCD_FIXEDPALETTE_1 == 0)
    #if !defined(LCD_PHYSCOLORS_1)
      #error You have to define a fixed palette (LCD_FIXEDPALETTE_1) or
      #error the list of physical colors (LCD_PHYSCOLORS_1) in LCDConf.h !
    #endif
  #endif
#endif   /* LCD_NUM_DISPLAYS > 1 */


#endif /* LCD_INTERN_H */




