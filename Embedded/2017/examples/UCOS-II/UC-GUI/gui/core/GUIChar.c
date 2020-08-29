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
Purpose     : Implementation of character and string services
----------------------------------------------------------------------
Version-Date---Author-Explanation
---------------------------END-OF-HEADER------------------------------
*/


#include <stddef.h>           /* needed for definition of NULL */
#include <stdio.h>
#include <string.h>
#include "GUI_Private.H"
#include "gb2312-unicode.h"
 

/*
***********************************************************
*
*                       Static subroutines
*
***********************************************************
*/



/*********************************************************************
  HandleEOLine
  Is called when processing strings which may consist of
  multiple lines after a line has been processed. It will
  a) Swall the line feed character (if it is there)
  b) Return 1 if end of string, otherwise 0
*/
int GUI__HandleEOLine(const char* *ps) {
  const char *s = *ps;
  char c= *s++;
  if (c==0)
    return 1;
  if (c=='\n') {
    *ps = s;
  }
  return 0;
}

/*************** GUI_GetStringDistX ****************************
This routine is used to calculate the length of a string in pixels.
*/

int GUI_GetLineDistX(const char GUI_FAR *s, int Len) {
  int Dist =0;
  if (s) {
    if (GUI_Context.pAFont->pafEncode) {
      return GUI_Context.pAFont->pafEncode->pfGetLineDistX(s, Len);
    }
#if (GUI_SUPPORT_UNICODE)
    {
      U8 c0;
      char UCActive=0;
      while (((c0=*(U8*)s) !=0) && Len >0) {
        s++; Len--;
        if (UCActive) {
          if (c0 == GUI_UC_ENDCHAR)
            UCActive = 0;
          else {
            U8  c1 = *(U8*)s++;
            Len--;
            Dist += GUI_GetCharDistX(GUI_DB2UC(c0, c1));
          }
        } else { /* Unicode not active */
          if (c0 == GUI_UC_STARTCHAR)
            UCActive = 1;
          else
            Dist += GUI_GetCharDistX(c0);
        }
      }
    }
#else
    while (--Len>=0) {
      Dist += GUI_GetCharDistX(*(U8*)s++);
    }
#endif
  }
  return Dist;
}

int GUI__GetFontSizeY(void) {
  return GUI_Context.pAFont->YSize * GUI_Context.pAFont->YMag;
}

/*************** GUI_GetLineLen ****************************
Returns the number of characters in a string
Note: The return value can be used as offset into the
string, which means that double characters count double
*/

int GUI__GetLineLen(const char GUI_FAR *s, int MaxLen) {
  int Len =0;
  if (!s)
    return 0;
  if (GUI_Context.pAFont->pafEncode) {
    return GUI_Context.pAFont->pafEncode->pfGetLineLen(s, MaxLen);
  }
#if (GUI_SUPPORT_UNICODE)
  {
    U8 c0;
    char UCActive=0;
    while (((c0=*(U8*)s) !=0) && Len < MaxLen) {
      s++;
      if (UCActive) {
        switch (c0) {
        case GUI_UC_ENDCHAR: UCActive = 0; break;
        default: Len++; s++;
        }
      } else { /* Unicode not active */
        switch (c0) {
        case GUI_UC_STARTCHAR: UCActive = 1; break;
        case '\n': return Len;
        case '\r': return Len;
        }
      }
      Len++;
    }
  }
#else
  for (;Len<MaxLen; Len++) {
    U8 Data = *(U8*)s++;
    if ((Data == 0) || (Data == '\n'))
      break;
  }
#endif
  return Len;
}

int GUI_GetStringDistX(const char GUI_FAR *s) {
  return GUI_GetLineDistX(s, strlen(s));
}


/**********************************************************************
*
*       "GET"   routines    (information retrieval)
*
***********************************************************************

These routines all return a value like selected font, current display
position in x/y direction, window size in x/y direction,
font size and matrix in x/y.
The routines prefixed with GUI_ can be called from the application
program or emWin internally, while the routines without that prefix
are not supposed to be called from outside emWin.
The main reason is that GUI_LOCK has to be called before these
values can be reliably retrieved in a multitasking environment.

*/

/*------------------------------------------------------------------
  GUI_GetYAdjust  --- returns adjustment in vertical (Y) direction
                  The return value needs to be subtracted from
                  the y-position of the character
*/

int GUI_GetYAdjust(void) {
  switch (GUI_Context.TextAlign&GUI_TA_VERTICAL) {
	case GUI_TA_BOTTOM:
		return GUI_Context.pAFont->YSize-1;
	case GUI_TA_VCENTER:
		return GUI_Context.pAFont->YSize/2;
	case GUI_TA_BASELINE:
		return GUI_Context.pAFont->YSize/2;
	}
  return 0;
}

/*
  Return X-component of current display position
*/

int GUI_GetDispPosX(void) {
  int r;
  GUI_LOCK();
  r = GUI_Context.DispPosX;
  GUI_UNLOCK();
  return r;
}

/*
  Return Y-component of current display position
*/
int GUI_GetDispPosY(void) {
  int r;
  GUI_LOCK();
  r = GUI_Context.DispPosY;
  GUI_UNLOCK();
  return r;
}

char GUI_IsInFont(const GUI_FONT*pFont, U16 c) {
  if (pFont==NULL)
    pFont = GUI_Context.pAFont;
  return pFont->pfIsInFont((void*)pFont, c);
}


/*
        *******************************************
        *                                         *
        *        Get Font Size Routines           *
        *                                         *
        *******************************************
*/


int GUI_GetFontSizeY(void) {
  int r;
  GUI_LOCK();
  r = GUI__GetFontSizeY();
  GUI_UNLOCK();
  return r;
}

int  GUI_GetYSizeOfFont(const GUI_FONT* pFont) {
  return pFont->YSize * pFont->YMag;
}

int  GUI_GetYDistOfFont(const GUI_FONT* pFont) {
  return pFont->YDist * pFont->YMag;
}

/*
        *******************************************
        *                                         *
        *        Get Font Spacing routines        *
        *                                         *
        *******************************************
*/

int GUI_GetFontDistY(void) {
  int r;
  GUI_LOCK();
  r = GUI_Context.pAFont->YDist * GUI_Context.pAFont->YMag;
  GUI_UNLOCK();
  return r;
}


/*
        *******************************************
        *                                         *
        *        Get Char spacing routines        *
        *                                         *
        *******************************************
*/

int GUI_GetCharDistX(U16 c) {
  int r;
  GUI_LOCK();
  r = GUI_Context.pAFont->pfGetCharDistX(c);
  GUI_UNLOCK();
  return r;
}

/*
        *******************************************
        *                                         *
        *        Get selected font                *
        *                                         *
        *******************************************
*/

const GUI_FONT* GUI_GetFont(void) {
  const GUI_FONT* r;
  GUI_LOCK();
  r = GUI_Context.pAFont;
  GUI_UNLOCK();
  return r;
}


/*
      **************************************************
      *                                                *
      *             Setting Text Mode                  *
      *                                                *
      **************************************************
*/
int GUI_SetTextMode(int Mode) {
  int r;
  GUI_LOCK();
  r = GUI_Context.TextMode;
  GUI_Context.TextMode = Mode;
  GUI_UNLOCK();
  return r;
}

int GUI_GetTextMode(void) {
  int r;
  GUI_LOCK();
  r = GUI_Context.TextMode;
  GUI_UNLOCK();
  return r;
}

/*
      **************************************************
      *                                                *
      *             Setting Text Mode                  *
      *                                                *
      **************************************************
*/
int GUI_SetTextAlign(int Align) {
  int r;
  GUI_LOCK();
  r = GUI_Context.TextAlign;
  GUI_Context.TextAlign = Align;
  GUI_UNLOCK();
  return r;
}

int GUI_GetTextAlign(void) {
  int r;
  GUI_LOCK();
  r = GUI_Context.TextAlign;
  GUI_UNLOCK();
  return r;
}




/*
      *********************************
      *                               *
      *       Clear to end of line    *
      *                               *
      *********************************

*/

void GUI_DispCEOL(void) {
  int y = GUI_Context.DispPosY - GUI_GetYAdjust();
  GUI_ClearRect(GUI_Context.DispPosX,
                y,
                4000,             /* Max pos x */
                y + GUI_Context.pAFont->YDist-1);
}


/*
      *********************************
      *                               *
      *       Linefeed                *
      *                               *
      *********************************

*/
void GUI_DispNextLine(void) {
  GUI_Context.DispPosY +=GUI_GetFontDistY();
  GUI_Context.DispPosX = GUI_Context.LBorder;
}

/*
************************************************************
*
*             GL/CL DispChar
*
************************************************************

*/

void GL_DispChar(U16 c) {
  /* check for control characters */
  if (c == '\n') {
    GUI_DispNextLine();
  } else {
    if (c != '\r') {
      GUI_Context.pAFont->pfDispChar(c);
    }
  }
}

#if (GUI_WINSUPPORT)
/* Note on usage of this routine:
   If at all possible, try to avoid using this, since
   every call will invoke the window manager. If possible,
   use the string routines.
*/
static void CL_DispChar(U16 c) {
  GUI_RECT r;
  WM_ADDORG(GUI_Context.DispPosX, GUI_Context.DispPosY);
  r.x1 = (r.x0 = GUI_Context.DispPosX) + GUI_GetCharDistX(c)-1;
  r.y1 = (r.y0 = GUI_Context.DispPosY) + GUI_GetFontSizeY()-1;
  WM_ITERATE_START(&r) {
    GL_DispChar(c);
    if (c != '\n')
      GUI_Context.DispPosX = r.x1 + 1;
  } WM_ITERATE_END();
  WM_SUBORG(GUI_Context.DispPosX,GUI_Context.DispPosY);
}
#endif

void GUI_DispChar(U16 c) {
  GUI_LOCK();
  #if (GUI_WINSUPPORT)
    CL_DispChar(c);
  #else
    GL_DispChar(c);
  #endif
  GUI_UNLOCK();
}



/*
************************************************************
*
*             GL/CL DispCharAt
*
************************************************************

*/

void GUI_DispCharAt(U16 c, I16P x, I16P y) {
  GUI_LOCK();
  GUI_Context.DispPosX =x;
  GUI_Context.DispPosY =y;
  #if (GUI_WINSUPPORT)
    CL_DispChar(c);
  #else
    GL_DispChar(c);
  #endif
  GUI_UNLOCK();
}



/*
************************************************************
*
*             GUI_SetFont
*
************************************************************

*/
const GUI_FONT* GUI_SetFont(const GUI_FONT* pNewFont) {
  const GUI_FONT * pOldFont = GUI_Context.pAFont;
  GUI_LOCK();
  if (pNewFont)
    GUI_Context.pAFont = pNewFont;
  GUI_UNLOCK();
  return pOldFont;
}


/*
        ************************************************************
        *                                                          *
        *             Set the write position                       *
        *                                                          *
        ************************************************************

Sets the write position. The routines routine 1 if it is clear that
the current write position is in an area outside the current window
and will therefor not be written.

*/

static char _GotoY(int y) {
  GUI_Context.DispPosY = y;
  return 0;
}

static char _GotoX(int x) {
  GUI_Context.DispPosX = x;
  return 0;
}


char GUI_GotoY(int y) {
  char r;
  GUI_LOCK();
  r = _GotoY(y);
  GUI_UNLOCK();
  return r;
}


char GUI_GotoX(int x) {
  char r;
  GUI_LOCK();
  r = _GotoX(x);
  GUI_UNLOCK();
  return r;
}

char GUI_GotoXY(int x, int y) {
  char r;
  GUI_LOCK();
  r  = GUI_GotoX(x);
  r |= GUI_GotoY(y);
  GUI_UNLOCK();
  return r;
}




/*
        ************************************************************
        *                                                          *
        *                 GUI_SetLBorder                           *
        *                                                          *
        *             Sets the left border (for carriage return)   *
        *                                                          *
        ************************************************************

*/


int GUI_SetLBorder(int x) {
  int r;
  GUI_LOCK();
  r = GUI_Context.LBorder;
  GUI_Context.LBorder = x;
  GUI_UNLOCK();
  return r;
}


/*
********************************************************
*
*                Display line
*
********************************************************
*/

void GL_DispLine(const char GUI_FAR *s, int Len, const GUI_RECT *pRect) {
  /*
    Check if we have anything to do at all ...
    If the window manager has already set the clipping rect, it does not
    make sense to due this. So it makes sense only if
    a) The window manager is not used (-> Configuration)
      or
    b) The window manager is inactive (-> Memory device active)
  */
  if (GUI_Context.pClipRect_HL) {
    if (GUI_RectsIntersect(GUI_Context.pClipRect_HL, pRect) == 0)
      return;
  }
  if (GUI_Context.pAFont->pafEncode) {
    GUI_Context.pAFont->pafEncode->pfDispLine(s, Len);
    return;
  }
#if (GUI_SUPPORT_UNICODE)
  {
    U8 c0;
    char UCActive=0;
    while (--Len >=0) {
      c0=*(U8*)s++;
      if (UCActive) {
        if (c0 == GUI_UC_ENDCHAR)
          UCActive = 0;
        else {
          U8  c1 = *(U8*)s++;
          Len--;
          GL_DispChar (GUI_DB2UC(c0, c1));
        }
      } else { /* Unicode not active */
        if (c0 == GUI_UC_STARTCHAR)
          UCActive = 1;
        else
          GL_DispChar(c0);
      }
    }
  }
#else
  {
    while (--Len >=0) {
      GL_DispChar(*(U8*)s++);
    }
  }
#endif
}

void GUI__DispLine(const char GUI_FAR *s, int Len, const GUI_RECT* pr) {
  GUI_RECT r;
  r = *pr;
  #if GUI_WINSUPPORT
  WM_ADDORG(r.x0,r.y0);
  WM_ADDORG(r.x1,r.y1);
  WM_ITERATE_START(&r) {
  #endif
     GUI_Context.DispPosX = r.x0;
     GUI_Context.DispPosY = r.y0;
  /* Do the actual drawing via routine call. */
     GL_DispLine(s, Len, &r);
  #if GUI_WINSUPPORT
  } WM_ITERATE_END();
  WM_SUBORG(GUI_Context.DispPosX, GUI_Context.DispPosY);
  #endif
}




void GUI_DispChars(U16P c, int Cnt) {
  while (Cnt-->0)
    GUI_DispChar(c);
}



void GUI_DispStringLen(const char GUI_FAR *s, int Len) {
  if (s) {
    U16 c;
    while (Len && ((c=(U16)(*s++))!=0)) {
      GUI_DispChar(c);
      Len--;
    }
  }
  while (Len--) {
    GUI_DispChar(' ');
  }
}


void GUI_DispStringAtCEOL(const char GUI_FAR *s, int x, int y) {
  GUI_DispStringAt(s,x,y);
  GUI_DispCEOL();
}

/*
	*********************************
	*                               *
	*	  Disp string                 *
  *   horizontally centered       *
	*                               *
	*********************************
*/

void GUI_DispStringHCenterAt(const char GUI_FAR *s, int x, int y) {
  int Align = GUI_SetTextAlign((GUI_Context.TextAlign&~GUI_TA_LEFT)|GUI_TA_CENTER);
  GUI_DispStringAt (s,x, y);
  GUI_SetTextAlign(Align);
}



/********************************************************************
*
*                Display String
*
*********************************************************************
*/

void GUI_DispString(const char GUI_FAR *s) {
  int xAdjust, yAdjust, xOrg;
  int FontSizeY;
  if (!s)
    return;
  GUI_LOCK();
  FontSizeY = GUI_Context.pAFont->YDist;
  xOrg = GUI_Context.DispPosX;
 /* Adjust vertical position */
  yAdjust = GUI_GetYAdjust();
  GUI_Context.DispPosY -= yAdjust;
  for (; *s; s++) {
    GUI_RECT r;
    int LineLen= GUI__GetLineLen(s,0x7fff);
    int xLineSize = GUI_GetLineDistX(s, LineLen);
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
    GUI__DispLine(s, LineLen, &r);
    GUI_Context.DispPosY = r.y0;
    s += LineLen;
    if ((*s=='\n') || (*s=='\r')) {
      switch (GUI_Context.TextAlign & GUI_TA_HORIZONTAL) { 
      case GUI_TA_CENTER:
      case GUI_TA_RIGHT:
        GUI_Context.DispPosX = xOrg;
        break;
      default:
        GUI_Context.DispPosX = GUI_Context.LBorder;
        break;
      }
      if (*s=='\n')
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


/********************************************************************
*
*                GUI_DispStringAt
*
*********************************************************************
*/
void GUI_DispStringAt(const char GUI_FAR *s, int x, int y) {
  GUI_LOCK();
  GUI_Context.DispPosX = x;
  GUI_Context.DispPosY = y;
  GUI_DispString(s);
  GUI_UNLOCK();
}

