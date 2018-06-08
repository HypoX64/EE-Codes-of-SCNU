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
File        : GUI_FillPolygon.C
Purpose     : Fill polygon routine
---------------------------END-OF-HEADER------------------------------
*/


#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Protected.H"
#include "GUIDebug.h"



/********************************************************
*
*              Configurable defines
*
*********************************************************
*/

/*
#define GUI_USE_POLYV2 1
*/

/*
        *********************************************************
        *                                                       *
        *              Fill Polygon                             *
        *                                                       *
        *********************************************************
*/
/*
    **********************************
    *                                *
    *      Helper functions          *
    *                                *
    **********************************
*/

/*
  This function returns the x-coordinate of the intersection
  of the given line at the given y-coordinate.
  If there is no intersection, GUI_XMAX is returned.
  This routine does not work for horizontal lines, as there
  would be more than a single point as intersection. This situation
  needs to be checked prior to calling the routine.
*/
int GL_CheckYInterSect(int y, const GUI_POINT*paPoint0
                            , const GUI_POINT*paPoint1) {
  int x0,y0,x1,y1;
  if (paPoint0->y <= (paPoint1)->y) {
    y0 = paPoint0->y;
    if (y0>y)      /* Check if there is an intersection ... (early out) */
      return GUI_XMAX+1;
    y1 = paPoint1->y;
    if (y1<y)      /* Check if there is an intersection ... (early out) */
      return GUI_XMAX+1;
    x0 = paPoint0->x;
    x1 = paPoint1->x;
  } else {
    y0 = paPoint1->y;
    if (y0>y)      /* Check if there is an intersection ... (early out) */
      return GUI_XMAX+1;
    y1 = paPoint0->y;
    if (y1<y)      /* Check if there is an intersection ... (early out) */
      return GUI_XMAX+1;
    x0 = paPoint1->x;
    x1 = paPoint0->x;
  }
/* Calc intermediate variables */
/* Calculate intersection */
  {
    I32 Mul = (I32)(x1-x0)* (I32)(y-y0);
    if (Mul >0)
      Mul += (y1-y0)>>1;	  /* for proper rounding */
    else
      Mul -= ((y1-y0)>>1)-1;	  /* for proper rounding */
    x0 +=Mul/(y1-y0);
  }
  return x0;
} 



int GL_GetSign(int v) {
  if (v>0)
    return 1;
  if (v<0)
    return -1;
  return 0;
}

/*********************************************************************
*
*      GL_FillPolygon   - Old Version
*
**********************************************************************

  The routine(s) below fill a given polygon.
*/
#if !defined(GUI_USE_POLYV2) /* Old proven, but slow version */
void GL_FillPolygon  (const GUI_POINT*paPoint, int NumPoints, int xOff, int yOff) {
  int i;
  int y;
  int yMin = GUI_YMAX;
  int yMax = GUI_YMIN;
/* First step : find uppermost and lowermost coordinates */
  for (i=0; i<NumPoints; i++) {
    y = (paPoint+i)->y;
    if (y<yMin)
      yMin = y;
    if (y>yMax)
      yMax = y;
  }
/* Use Clipping rect to reduce calculation (if possible) */
  if (GUI_Context.pClipRect_HL) {
    if (yMax > (GUI_Context.pClipRect_HL->y1 -yOff))
      yMax = (GUI_Context.pClipRect_HL->y1 -yOff);
    if (yMin < (GUI_Context.pClipRect_HL->y0 -yOff))
      yMin = (GUI_Context.pClipRect_HL->y0 -yOff);
  }
/* Second step: Calculate and draw horizontal lines */
  for (y=yMin; y<=yMax; y++) {
    int x0 = GUI_XMIN;         /* Left edge of line */
    int LineCntTotal =0;
    /* Draw all line segments */
    while (x0<GUI_XMAX) {
      char PointOnly=0;
      char OnEdge =0;
      char LineCntAdd =0;
      int xX = GUI_XMAX;  /* x-coordinate of next intersection */
      /* find next intersection and count lines*/
      for (i=0; i<NumPoints; i++) {
        int x;
        int iPrev = i ? (i-1) : NumPoints-1;
        int i1 = (i <(NumPoints-1)) ? i +1 : 0;
        int i2 = (i1<(NumPoints-1)) ? i1+1 : 0;
        /* Check if end-point is on the line */
        if ((paPoint+i1)->y ==y) {
          /* Start-point also on the line ?*/
          if ((paPoint+i)->y ==y) {
            /* Get xmin, xmax */
            int xmin = (paPoint+i)->x;
            int xmax = (paPoint+i1)->x;
            if (xmin > xmax) {
              int t = xmin; xmin = xmax; xmax =t;
            }
            /* left point */
            if ((xmin>x0) && (xmin<=xX)) {
              xX = xmin;
              LineCntAdd =0;
            }
            if ((xmax>x0) && (xmax<=xX)) {
              xX = xmax;
              OnEdge =1;
              /* Check if the line crosses ... */
              LineCntAdd = (GL_GetSign((paPoint+i2)->y-y)
                         == GL_GetSign((paPoint+iPrev)->y-y))
                         ? 0 : 1;
            }
          } else { /* end-point.y == y, start-point.y !=y */
            x = (paPoint+i1)->x;
            if ((x>x0) && (x<=xX)) {
              if (xX > x) {
                xX = x;
                if (GL_GetSign((paPoint+i2)->y -y) == GL_GetSign((paPoint+i)->y -y))
                {
                  PointOnly  = 1;
                  LineCntAdd = 0;
                } else {
                  LineCntAdd=1;
                }
              }
            }
          }
        } else { /* end point not on the line, find intersection */
          if (y != (paPoint+i)->y) { /* if startpoint not on y */
            x = GL_CheckYInterSect(y, paPoint+i, paPoint+i1);
            if ((x>x0) && (x<=xX)) {
              if (x==xX) 
                LineCntAdd++;
              else
                LineCntAdd=1;
              xX = x;
            }
          } 
        }
      }
      if ((LineCntTotal&1) || OnEdge) {
        LCD_HL_DrawHLine(x0+xOff,y+yOff,xX+xOff);
      } else {
      /* We are looking at a endpoint ... */
    		if (PointOnly) {
          LCD_HL_DrawHLine(xX+xOff,y+yOff,xX+xOff); /* LCD_HL_DrawPixel(xX+xOff,y+yOff); */
        }
      }
      x0 = xX;
      LineCntTotal += LineCntAdd;
    }
  }  
}

#else
/*********************************************************************
*
*      GL_FillPolygon   - New Version
*
**********************************************************************

  The routine(s) below fill a given polygon.
*/

#define GUI_FP_MAXCOUNT 10
#define FP_TYPE_X    0
#define FP_TYPE_V    1


static int GL_FP_Cnt;
static struct {
  I16 x;
  U8  Type;
} GL_FP_a[GUI_FP_MAXCOUNT];

static void GL_FP_Add(int x, U8 Type) {
  if (GL_FP_Cnt < GUI_FP_MAXCOUNT) {
    int i;
    /* Move all entries to the right (bigger x-value) */
    for (i=GL_FP_Cnt; i ; i--) {
      if (GL_FP_a[i-1].x < x)
        break;
      GL_FP_a[i] = GL_FP_a[i-1];
    }
    /* Insert new entry */
    GL_FP_a[i].x = x;
    GL_FP_a[i].Type = Type;
    GL_FP_Cnt++;
  }
}

void GL_FP_Init(void) {
  GL_FP_Cnt = 0;
}

void GL_FP_Flush(int x0, int y) {
  int i;
  int x;
  char On=0;
  for (i=0; i<GL_FP_Cnt; i++) {
    int xNew = GL_FP_a[i].x;
    switch (GL_FP_a[i].Type) {
    case FP_TYPE_X:
      if (On) {
        LCD_HL_DrawHLine(x0+x, y, x0+xNew);
      }
      On ^= 1;
      break;
    case FP_TYPE_V:
      if (On) {
        LCD_HL_DrawHLine(x0+x, y, x0+xNew);
      } else {
        LCD_HL_DrawHLine(x0+x, y, x0); /* Do not use LCD_HL_DrawPixel(x0+xNew, y); --- AA module does not support SetPixel */
      }
      break;
    }
    x = xNew+1;
  }
}

void GL_FillPolygon  (const GUI_POINT*paPoint, int NumPoints, int xOff, int yOff) {
  int i;
  int y;
  int yMin = GUI_YMAX;
  int yMax = GUI_YMIN;
/* First step : find uppermost and lowermost coordinates */
  for (i=0; i<NumPoints; i++) {
    y = (paPoint+i)->y;
    if (y<yMin)
      yMin = y;
    if (y>yMax)
      yMax = y;
  }
/* Use Clipping rect to reduce calculation (if possible) */
  if (GUI_Context.pClipRect_HL) {
    if (yMax > (GUI_Context.pClipRect_HL->y1 -yOff))
      yMax = (GUI_Context.pClipRect_HL->y1 -yOff);
    if (yMin < (GUI_Context.pClipRect_HL->y0 -yOff))
      yMin = (GUI_Context.pClipRect_HL->y0 -yOff);
  }
/* Second step: Calculate and draw horizontal lines */
  for (y=yMin; y<=yMax; y++) {
    GL_FP_Init();
    /* find next intersection and count lines*/
    for (i=0; i<NumPoints; i++) {
      int i1 = (i <(NumPoints-1)) ? i +1 : 0;
      int y0 = (paPoint+i)->y;
      int y1 = (paPoint+i1)->y;
      /* Check if starting point is on line */
      if (y0 == y) {
        if (y1 == y) {  /* Add the entire line */
          GL_FP_Add((paPoint+i )->x, FP_TYPE_X);
          GL_FP_Add((paPoint+i1)->x, FP_TYPE_X);
        } else {        /* Add only one point */
          GL_FP_Add((paPoint+i )->x, FP_TYPE_V);
        }
      }
      else if (y1 != y) {  /* Ignore if end-point is on the line */
        if (((y1 >= y) && (y0 <= y)) || ((y0 >= y) && (y1 <= y))) {
          int x = GL_CheckYInterSect(y, paPoint+i, paPoint+i1);
          GL_FP_Add(x, FP_TYPE_X);
        }
      }
    }
    GL_FP_Flush(xOff, y+yOff);
  }  
}

#endif

void GUI_FillPolygon  (const GUI_POINT* pPoints, int NumPoints, int x0, int y0) {
  GUI_LOCK();
  #if (GUI_WINSUPPORT)
    WM_ADDORG(x0,y0);
    WM_ITERATE_START(NULL); {
  #endif
  GL_FillPolygon (pPoints, NumPoints, x0, y0);
  #if (GUI_WINSUPPORT)
    } WM_ITERATE_END();
  #endif
  GUI_UNLOCK();
}


