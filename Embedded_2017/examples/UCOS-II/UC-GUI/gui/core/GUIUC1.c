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
File        : GUIUC1.C
Purpose     : Implementation of character and string services
----------------------------------------------------------------------
Version-Date---Author-Explanation
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Private.H"

#if GUI_SUPPORT_UNICODE

/*
************************************************************
*
*            static functions
*
************************************************************
*/

static int GetLineDistX(const U16 GUI_FAR *s, int Len) {
  int Dist =0;
  if (s) {
    U16 c0;
    while (((c0=*s) !=0) && Len >=0) {
      s++; Len--;
      Dist += GUI_GetCharDistX(c0);
    }
  }
  return Dist;
}

static int GetLineLen(const U16 GUI_FAR *s, int MaxLen) {
  int Len =0;
  if (!s)
    return 0;
  {
    while ((*s !=0) && Len < MaxLen) {
      Len++; s++;
    }
  }
  return Len;
}

static void DispLine_UC(const U16 GUI_FAR *s, int Len, const GUI_RECT *pRect) {
  if (GUI_Context.pClipRect_HL) {
    if (GUI_RectsIntersect(GUI_Context.pClipRect_HL, pRect) == 0)
      return;
  }
  {
    U16 c0;
    while (--Len >=0) {
      c0=*s++;
      GL_DispChar (c0);
    }
  }
}

static void DispLine(const U16 GUI_FAR *s, int Len, const GUI_RECT* pr) {
  GUI_RECT r;
  r = *pr;
  #if GUI_WINSUPPORT
  WM_ADDORG(r.x0,r.y0);
  WM_ADDORG(r.x1,r.y1);
  WM_ITERATE_START(&r) {
  #endif
     GUI_Context.DispPosX = r.x0;
     GUI_Context.DispPosY = r.y0;
     DispLine_UC(s, Len, &r);    /* Do the actual drawing via routine call. */
  #if GUI_WINSUPPORT
  } WM_ITERATE_END();
  WM_SUBORG(GUI_Context.DispPosX, GUI_Context.DispPosY);
  #endif
}

/*
************************************************************
*
*            UNICODE routines
*
************************************************************
*/

void GUI_DispString_UC(const U16 GUI_FAR *s) {
  int xAdjust, yAdjust, xOrg;
  int FontSizeY;
  if (!s)
    return;
  GUI_LOCK();
  FontSizeY = GUI_Context.pAFont->YSize;
  xOrg = GUI_Context.DispPosX;
 /* Adjust vertical position */
  yAdjust = GUI_GetYAdjust();
  GUI_Context.DispPosY -= yAdjust;
  for (; *s; s++) {
    GUI_RECT r;
    int LineLen= GetLineLen(s,0x7fff);
    int xLineSize = GetLineDistX(s, LineLen);
  /* Check if x-position needs to be changed due to h-alignment */
    switch (GUI_Context.TextAlign & GUI_TA_HORIZONTAL) { 
    case GUI_TA_CENTER: xAdjust= xLineSize/2; break;
    case GUI_TA_RIGHT:  xAdjust= xLineSize; break;
    default:            xAdjust= 0;
    }
    r.x0 = GUI_Context.DispPosX -= xAdjust;
    r.x1 = r.x0 + xLineSize-1;    
    r.y0 = GUI_Context.DispPosY;
    r.y1 = r.y0 + FontSizeY-1;    
    DispLine(s, LineLen, &r);
    GUI_Context.DispPosY = r.y0;
    s += LineLen;
    if (*s=='\n') {
      switch (GUI_Context.TextAlign & GUI_TA_HORIZONTAL) { 
      case GUI_TA_CENTER:
      case GUI_TA_RIGHT:
        GUI_Context.DispPosX = xOrg;
        break;
      default:
        GUI_Context.DispPosX = GUI_Context.LBorder;
        break;
      }
      GUI_Context.DispPosY += GUI_GetFontDistY();
    } else {
      GUI_Context.DispPosX = r.x0+xLineSize;
    }
    if (*s==0)    /* end of string (last line) reached ? */
      break;
  }
  GUI_Context.DispPosY += yAdjust;
  GUI_Context.TextAlign &= ~GUI_TA_HORIZONTAL;
  GUI_UNLOCK();
}

#else

void GUIUC1_C(void) {} /* avoid empty object files */

#endif /* GUI_SUPPORT_UNICODE */
