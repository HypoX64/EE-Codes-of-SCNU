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
File        : GUIDEMO_Polygon.c
Purpose     : Several GUIDEMO routines
----------------------------------------------------------------------
*/

#include "GUI.H"
#include "GUIDEMO.H"

#define countof(Obj) (sizeof(Obj)/sizeof(Obj[0]))

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static const GUI_POINT _aArrow[] = {
  {  0, - 5 },
  {-40, -35 },
  {-10, -25 },
  {-10, -85 },
  { 10, -85 },
  { 10, -25 },
  { 40, -35 }
};

static const GUI_POINT _aTriangle[] = {
	{  0,   0 }, 
  {-30, -30 },
  { 30, -30 },
};

static GUI_POINT _aiCursor[] = {
  {  0,  0 }, 
  { 50, 100 }, 
  {  0, 90 }, 
  {-50, 100 },
};

/*********************************************************************
*
*       Typedefs
*
**********************************************************************
*/

typedef struct {
  float Angle;
  int DoClear;
} tDrawContext;

/*********************************************************************
*
*       GUIDEMO_DemoPolygon
*
**********************************************************************
*/

void GUIDEMO_DemoPolygon(void) {
  int XMid = LCD_GetXSize() / 2;
  int YMid = LCD_GetYSize() / 2;
  GUIDEMO_ShowIntro("Arbitrary Polygons", 
                    "Standard and antialiased");
  GUI_SetColor(GUI_WHITE);
  GUI_SetFont(&GUI_FontComic18B_1);
  #if GUIDEMO_LARGE
    GUI_DispStringAt("Arbitrary\nPolygons", 0, 0);
  #endif
  GUI_FillPolygon(&_aArrow[0], 7, XMid - 50, YMid + 40);
  GUI_FillPolygon(&_aArrow[0], 7, XMid + 50, YMid + 40);
  GUI_SetColor(GUI_GREEN);
  GUI_FillPolygon(&_aTriangle[0], 3, XMid, YMid + 60);
  GUI_SetColor(GUI_WHITE);
//  GUI_AA_EnableHiRes();
//  GUI_FillPolygonAA(&_aiCursor[0], 4, XMid * 3, (YMid - 40) * 3);
  GUIDEMO_Wait();
}
