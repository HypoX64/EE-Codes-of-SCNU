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
File        : GUIChar.C
Purpose     : Implementation of memory devices
----------------------------------------------------------------------
Version-Date---Author-Explanation
----------------------------------------------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */

#include "GUI_Private.H"
 


/*
      ***********************************************************
      *                                                         *
      *       Monospaced Font                                   *
      *                                                         *
      ***********************************************************

This is the routine that displays a character. It is used by all
other routines which display characters as a subroutine.

Parameters:     c       character to display
*/


void GUIMONO_DispChar(U16P c) {
  int c0, c1;
  U8 * pd;
  int x = GUI_Context.DispPosX;
  int y = GUI_Context.DispPosY;
/* do some checking if drawing is actually necessary ... */
  const GUI_FONT_MONO* pMono = GUI_Context.pAFont->p.pMono;
  unsigned int FirstChar = pMono->FirstChar;
  /* translate character into 2 characters to display : c0,c1
     Check if regular character first. */
  if ((c >= (U16P)FirstChar) &&(c <= (U16P)pMono->LastChar)) {
    pd = (U8*)pMono->pData;
    c0 = ((int)c) - FirstChar;
    c1 = -1;
  } else {
   /* Check if character is in translation table */
    GUI_FONT_TRANSINFO const* pti = pMono->pTrans;
    pd = (U8*)pMono->pTransData;
    if (pti) {
      FirstChar = pti->FirstChar;
      if ((c >= (U16P)FirstChar) && (c <= (U16P)pti->LastChar)) {
        GUI_FONT_TRANSLIST const* ptl;
        c -= pti->FirstChar;
        ptl = pti->pList;
        ptl += c;
        c0  = ptl->c0;
        c1  = ptl->c1;
      } else {
        c0 = c1 = -1;
      }
    } else {
      c0 = c1 = -1;
    }
  }
/*
   Draw first character if it is valid
*/
  if (c0!=-1) {
    int BytesPerChar = GUI_Context.pAFont->YSize*pMono->BytesPerLine;
    GUI_DRAWMODE DrawMode;
    int XSize = pMono->XSize;
    int YSize = GUI_Context.pAFont->YSize;
/* Select the right drawing mode */
    DrawMode = GUI_Context.TextMode;
/* call drawing routine */
    {
      U8 OldMode = LCD_SetDrawMode(DrawMode);
      LCD_DrawBitmap( x, y,
                         XSize, YSize,
                         GUI_Context.pAFont->XMag,  GUI_Context.pAFont->YMag,
                         1,     /* Bits per Pixel */
                         pMono->BytesPerLine,
                         pd + c0* BytesPerChar,
                         NULL  /* no palette means default palette */
                         );
      if (c1 != -1) {
        LCD_SetDrawMode(DrawMode | LCD_DRAWMODE_TRANS);
        LCD_DrawBitmap( x, y,
                           XSize, YSize,
                           GUI_Context.pAFont->XMag,  GUI_Context.pAFont->YMag,
                           1,     /* Bits per Pixel */
                           pMono->BytesPerLine,
                           pd + c1* BytesPerChar,
                           NULL  /* no palette means default palette */
                           );
      }
      /* Fill empty pixel lines */
      if (GUI_Context.pAFont->YDist > GUI_Context.pAFont->YSize) {
        int YMag = GUI_Context.pAFont->YMag;
        int YDist = GUI_Context.pAFont->YDist * YMag;
        int YSize = GUI_Context.pAFont->YSize * YMag;
        if (DrawMode != LCD_DRAWMODE_TRANS) {
          LCD_SetDrawMode(DrawMode ^ LCD_DRAWMODE_REV);  /* Reverse so we can fill with BkColor */
          LCD_FillRect(x, y + YSize, x + XSize, y + YDist);
        }
      }
      LCD_SetDrawMode(OldMode);
    } 
  }
  GUI_Context.DispPosX+=pMono->XDist;
}

int GUIMONO_GetCharDistX(U16P c) {
  const GUI_FONT_MONO* pMono = GUI_Context.pAFont->p.pMono;
  GUI_USE_PARA(c);
  return pMono->XDist;
}

void GUIMONO_GetFontInfo(void* pFont, GUI_FONTINFO* pfi) {
  GUI_USE_PARA(pFont);
  pfi->Flags = GUI_FONTINFO_FLAG_MONO;
}

char GUIMONO_IsInFont(void* pFont, U16 c) {
  const GUI_FONT_MONO* pMono = ((GUI_FONT*)pFont)->p.pMono;
  unsigned int FirstChar = pMono->FirstChar;
  /* Check if regular character first. */
  if ((c >= (U16P)FirstChar) &&(c <= (U16P)pMono->LastChar)) {
    return 1;  /* Yes, we have it ! */
  } else {
   /* Check if character is in translation table */
    GUI_FONT_TRANSINFO const* pti = pMono->pTrans;
    if (pti) {
      if ((c >= pti->FirstChar) && (c <= pti->LastChar)) {
        return 1;  /* Yes, we have it ! */
      }
		}
	}
  return 0;  /* No, we can not display this character */
}

