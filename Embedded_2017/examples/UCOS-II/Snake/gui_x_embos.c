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
File        : GUI_X.C
Purpose     : Config / System dependent externals for GUI
---------------------------END-OF-HEADER------------------------------
*/

#include <stdio.h>
#include "Includes.H"               /* embOS include */
#include "GUI.H"
#include "GUI_X.H"

#define OS_Delay     OSTimeDly
#define OS_GetTime   OSTimeGet



/*********************************************************************
*
*      Timing:
*                 GUI_GetTime()
*                 GUI_Delay(int)

  Some timing dependent routines of emWin require a GetTime
  and delay funtion. Default time unit (tick), normally is
  1 ms.
*/

int GUI_X_GetTime(void) {
  return OS_GetTime();
}

void GUI_X_Delay(int Period) {
  OS_Delay(Period);
}

/*********************************************************************
*
*       GUI_X_ExecIdle()
*
*/
void GUI_X_ExecIdle(void) {
  OS_Delay(1);
}

/*********************************************************************
*
*      Multitasking:
*
*                 GUI_X_InitOS()
*                 GUI_X_GetTaskId()
*                 GUI_X_Lock()
*                 GUI_X_Unlock()

Note:
  The following routines are required only if emWin is used in a
  true multi task environment, which means you have more than one
  thread using the emWin API.
  In this case the
                      #define GUI_OS 1
  needs to be in GUIConf.h
*/


/*static OS_RSEMA RSema;
*/

void GUI_X_InitOS(void)    { /*OS_CreateRSema(&RSema);*/    }
void GUI_X_Unlock(void)    { /*OS_Unuse(&RSema);*/ }
void GUI_X_Lock(void)      { /*OS_Use(&RSema);*/  }
U32  GUI_X_GetTaskId(void) { return (U32)1/*OSGetTaskID()*/; }


/*********************************************************************
*
*      Keyboard input from serial input

Note:
  If embOS is used, characters typed into the log window will be placed
  in the keyboard buffer. This is a neat feature which allows you to
  operate your target system without having to use or even to have
  a keyboard connected to it. (nice for demos !)
*/

void GUI_X_OnRx(INT8U Data) {
  GUI_StoreKeyMsg(Data, 1);
}

void GUI_X_Init(void) {
  /*OS_SetRxCallback(GUI_X_OnRx);*/
}

/*********************************************************************
*
*      Logging: OS dependent

Note:
  Logging is used in higher debug levels only. The typical target
  build does not use logging and does therefor not require any of
  the logging routines below. For a release build without logging
  the routines below may be eliminated to save some space.
  (If the linker is not function aware and eliminates unreferenced
  functions automatically)

*/

void GUI_X_Log     (const char *s) { /*OS_SendString(s);*/ }
//void GUI_X_Warn    (const char *s) { /*OS_SendString(s);*/ }
void GUI_X_ErrorOut(const char *s) { /*OS_SendString(s);*/ }
void GUI_HID_StoreState(const GUI_HID_STATE *pState){}







