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
File        : GUITASK.C
Purpose     : Saves/Restores task context with supported OSs.
              It also uses a resource semaphore.

  The following externals are used and should typically be defined
  in GUI_X.c:
  
    U32  GUI_X_GetTaskId();
    void GUI_X_Unlock();
    void GUI_X_Lock();

----------------------------------------------------------------------
Version-Date---Author-Explanation
----------------------------------------------------------------------
3.02a   020722 RS     Use of macro GUI_DEBUG_ERROROUT_IF in order
                      to simplify th code.
3.02    020514 RS     Avoided nested calls of GUI_X_Lock, GUI_X_Unlock
                      (because some RTOSes, such as CMX and u/C-OS
                      could not handle this easily)
3.00    010425 RS     Cleanup for emWin Version 3.00
                      a) Dummy routines added to avoid link errors
                        in case some emWin modules are compiled with
                        different settings
1.00.01 990926 RS     Fix in order to make sure init task has no
                      context of its own (_CurrentTaskNo =-1)
1.00.00 990918 RS     Initial version for version control purposes.
                      This is a generic version which can be used with
                      both emWin b/w and emWin GSC; it is based on the
                      Context saver of emWin b/w.
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Protected.H"
#include "GUIDEBUG.H"

/*********************************************************************
*
*       Configuration defaults
*
*********************************************************************
*/

#ifndef GUI_MAXTASK
  #define GUI_MAXTASK (4)
#endif

#if GUI_OS

/*********************************************************************
*
*       Static data
*
*********************************************************************
*/

static struct {
  U32  TaskID;
  GUI_CONTEXT Context;
} _Save[GUI_MAXTASK];

static int _CurrentTaskNo = -1;
static int _EntranceCnt   =  0;
static U32 _TaskIDLock = 0;

/*********************************************************************
*
*       Static functions
*
*********************************************************************
*/

static int _GetTaskNo(void) {
  int i;
  for (i=0; i< GUI_MAXTASK; i++) {
    U32 TaskId = GUI_X_GetTaskId();
    if (_Save[i].TaskID == TaskId)
      return i;
    if (_Save[i].TaskID == 0) {
      _Save[i].TaskID = TaskId;
      return i;
    }
  }
  GUI_DEBUG_ERROROUT("No Context available for task ... (increase GUI_MAXTASK)");
  return 0;
}

/*********************************************************************
*
*       Public functions
*
*********************************************************************
*/

void GUI_Unlock(void) {
  if (--_EntranceCnt == 0) {
    GUI_X_Unlock();
  }
  /* Test if _EntranceCnt is in reasonable range ... Not required in release builds */
  GUI_DEBUG_ERROROUT_IF((_EntranceCnt < 0), "GUITASK.c: GUI_Unlock() _EntranceCnt underflow ");
}

void GUI_Lock(void) {
  if (_EntranceCnt == 0) {
    GUI_X_Lock();
    _TaskIDLock = GUI_X_GetTaskId();         /* Save task ID */
  } else {
    if (_TaskIDLock != GUI_X_GetTaskId()) {
      GUI_X_Lock();
      _TaskIDLock = GUI_X_GetTaskId();         /* Save task ID */
    }
  }
  if (++_EntranceCnt == 1) {
    int TaskNo = _GetTaskNo();
    if (TaskNo != _CurrentTaskNo) {
      /* Save data of current task */
      if (_CurrentTaskNo>=0) {  /* Make sure _CurrentTaskNo is valid */
        _Save[_CurrentTaskNo].Context = GUI_Context;
      }
      /* Load data of this task */
      GUI_Context = _Save[TaskNo].Context;
      _CurrentTaskNo = TaskNo;
    }
  }
  /* Test if _EntranceCnt is in reasonable range ... Not required in release builds */
  GUI_DEBUG_ERROROUT_IF((_EntranceCnt>12), "GUITASK.c: GUI_Lock() _EntranceCnt overflow ");
}

void GUITASK_Init(void) {
  int i;
  _CurrentTaskNo =-1;   /* Invalidate */
  GUI_X_InitOS();
  for (i=0; i<GUI_MAXTASK; i++) {
    _Save[i].Context = GUI_Context;
  }
}

#else

/*********************************************************************
*
*       Dummy Kernel routines

The routines below are dummies in case configuration tells us not
to use any kernel. In this case the routines below should
not be required, but it can not hurt to have them. The linker
will eliminate them anyhow.

*/

void GUI_Unlock(void) {}
void GUI_Lock(void) {}
void GUITASK_Init(void) {}
void GUITASK_StoreDefaultContext(void) {}

#endif

