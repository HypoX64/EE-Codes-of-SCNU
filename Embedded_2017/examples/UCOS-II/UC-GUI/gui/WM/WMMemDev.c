/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              �C/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : WMMemDev.C
Purpose     : Windows manager add on, support for memory devices
----------------------------------------------------------------------
*/


#include "WM_Intern.H"
#include "GUIDebug.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

/*
  ********************************************************************
  *                                                                  *
  *           Enable /disable memory devices for window              *
  *                                                                  *
  ********************************************************************
*/

void WM_EnableMemdev (WM_HWIN hWin) {
  #if GUI_SUPPORT_MEMDEV
    if (hWin) {
      WM_Obj *pWin    = WM_HANDLE2PTR(hWin);  
      pWin->Status |= (WM_SF_MEMDEV);
    }
  #else
    GUI_DEBUG_WARN("WM_EnableMemdev: No effect because disabled in GUIConf.h (GUI_SUPPORT_MEMDEV == 0)");
  #endif
}

void WM_DisableMemdev(WM_HWIN hWin) {
  #if GUI_SUPPORT_MEMDEV
    if (hWin) {
      WM_Obj *pWin = WM_HANDLE2PTR(hWin);  
      pWin->Status &= ~(WM_SF_MEMDEV);
    }
  #else
    GUI_DEBUG_WARN("WM_EnableMemdev: No effect because disabled in GUIConf.h (GUI_SUPPORT_MEMDEV == 0)");
  #endif
}

#else

void WM_MemDev(void) {} /* avoid empty object files */

#endif /* GUI_WIN_SUPPORT */
