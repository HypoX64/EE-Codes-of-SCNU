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
File        : GUIDEMO.h
Purpose     : Multiple choice for emWin GSC
----------------------------------------------------------------------
*/

#include "LCD_ConfDefaults.h"  /* valid LCD configuration */

/*********************************************************************
*
*      GUIDEMO publics
*
*********************************************************************

  The following are the routines which are available to the
  demo modules.
*/

void GUIDEMO_main(void);

/*********************************************************************
*
*      GUIDEMO main routines
*
*********************************************************************

  The following are the routines which are available to the
  demo modules.
*/

void GUIDEMO_Wait(void);
int  GUIDEMO_Delay(int t);
void GUIDEMO_ShowIntro(const char*s, const char* sExplain);
void GUIDEMO_ShowInfo(const char* sExplain);
int  GUIDEMO_CheckCancel(void);
void GUIDEMO_NotifyStartNext(void);
void GUIDEMO_HideInfoWin(void);
int  GUIDEMO_WaitKey(void);


extern const GUI_BITMAP GUIDEMO_bm4bpp;


/*********************************************************************
*
*      Demo modules
*
*********************************************************************

  The demo consists of different modules which are usually called
  by the main routine.
  The following are the declarations for the individual routines.
*/

void GUIDEMO_Messagebox(void);
void GUIDEMO_Dialog(void);
void GUIDEMO_HardwareInfo(void);
void GUIDEMO_Graph(void);
void GUIDEMO_Automotive(void);
void GUIDEMO_Bitmap(void);
void GUIDEMO_Intro(void);
void GUIDEMO_Navigation(void);
void GUIDEMO_ShowMemoryDevice(void);
void GUIDEMO_DemoBITMAPObj(void);
void GUIDEMO_Circle(void);
void GUIDEMO_Speed(void);
void GUIDEMO_ShowInternationalFonts(void);
void GUIDEMO_ShowColorBar(void);
void GUIDEMO_ShowColorList(void);
void GUIDEMO_DemoFrameWin(void);
void GUIDEMO_DemoLISTBOX(void);
void GUIDEMO_DemoWidgets(void);
void GUIDEMO_DemoPolygon(void);
void GUIDEMO_DemoProgBar(void);
//void GUIDEMO_ShowUCMix(void);
void GUIDEMO_DemoLISTBOX(void);
void GUIDEMO_DemoFrameWin(void);
void GUIDEMO_DemoLUT(void);
void GUIDEMO_ModifyLUT(int RFaktor, int GFaktor, int BFaktor);
void GUIDEMO_ShowColorList(void);
void GUIDEMO_Touch(void);

extern const GUI_BITMAP bmemWinGSCLogo320x46;
extern const GUI_BITMAP bmMicriumLogo;
extern const GUI_BITMAP bmMicriumLogoWRed;

/*********************************************************************
*
*      GUIDEMO defines
*
*********************************************************************
*/

#define GUIDEMO_LARGE ((LCD_XSIZE >= 240) && (LCD_YSIZE >= 200))
