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
File        : LCDP0.C
Purpose     : Color conversion routines for LCD-drivers
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.H>
#include "LCD_Protected.h"    /* inter modul definitions */

/*
        *********************************************************
        *                                                       *
        *       calculation macros and support                  *
        *                                                       *
        *********************************************************
*/
#if 1  /* Normaly calculate square values */
  #define  SQUARE(Dist) ((U16)Dist) * ((U16)Dist)
#else

#define S(x) ((x)*(x))
#define SQUARES(Base)  S(Base+0),  S(Base+1),  S(Base+2),  S(Base+3), S(Base+4),  S(Base+5),   \
                       S(Base+6),  S(Base+7),  S(Base+8),  S(Base+9), S(Base+10), S(Base+11), \
                       S(Base+12), S(Base+13), S(Base+14), S(Base+15)

static const U16 aSquare[] = {
  SQUARES(0*16)
  ,SQUARES(1*16), SQUARES(2*16), SQUARES(3*16)
  ,SQUARES(4*16) ,SQUARES(5*16), SQUARES(6*16), SQUARES(7*16)
  ,SQUARES(8*16) ,SQUARES(9*16), SQUARES(10*16),SQUARES(11*16)
  ,SQUARES(12*16),SQUARES(13*16),SQUARES(14*16),SQUARES(15*16)
};

  #define  SQUARE(Dist) aSquare[Dist]
#endif

/*
        *********************************************************
        *                                                       *
        *       Color conversions for palette based displays    *
        *                                                       *
        *********************************************************
*/

static U32 CalcColorDist (LCD_COLOR PalColor, LCD_COLOR  Color) {
/* This routine does not use abs() because we are optimizing for speed ! */
  I16 Dist;
  U32 Sum;
  Dist  = (PalColor&0xff) - (Color&0xff);
  if (Dist < 0)
	  Dist = -Dist;
  Sum = SQUARE(Dist);
  Dist  = ((PalColor>>8)&0xff) -  ((Color>>8)&0xff);
  if (Dist < 0)
	  Dist = -Dist;
  Sum += SQUARE(Dist);
  Dist  = (PalColor>>16) - (Color>>16);
  if (Dist < 0)
	  Dist = -Dist;
  return Sum + SQUARE(Dist);
}


  /*
          *********************************************************
          *                                                       *
          *   Color conversions for 1/2/4/8 bpp color displays    *
          *                                                       *
          *              with table based palette                 *
          *                                                       *
          *********************************************************
  */

  int LCD_Color2Index_0(LCD_COLOR Color, const LCD_PHYSPALETTE* pPhysPal) {
    int i;
    int NumEntries = pPhysPal->NumEntries;
    int BestIndex;
    U32 BestDiff = 0xffffff; /* Initialize to worst match */
    const LCD_COLOR* pPalEntry;
/* Try to find perfect match */
    i=0; pPalEntry = &pPhysPal->pPalEntries[0];
    do {
	    if (Color==*(pPalEntry+i))
	      return i;
    } while (++i<NumEntries);
/* Find best match */
    i=0; pPalEntry = &pPhysPal->pPalEntries[0];
    do {
      U32 Diff = CalcColorDist (Color, *(pPalEntry+i));
      if (Diff < BestDiff) {
        BestDiff  = Diff;
        BestIndex = i;
      }
    } while (++i<NumEntries);
    return BestIndex;
  }

  LCD_COLOR LCD_Index2Color_0(int Index, const LCD_PHYSPALETTE* pPhysPal) {
    if ((unsigned)Index >= (unsigned) pPhysPal->NumEntries) {
      return 0;     /* Illegal index */
    }
    return *(pPhysPal->pPalEntries+Index);
  }





