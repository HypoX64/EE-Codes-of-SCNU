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
File        : GUIDev1.C
Purpose     : Implementation of memory devices, add. module
---------------------------END-OF-HEADER------------------------------
*/


#include "GUI_Protected.h"
#include "GUIDebug.h"
#include <string.h>

/* Memory device capabilities are compiled only if support for them is enabled. */ 
#if GUI_SUPPORT_MEMDEV


/*
************************************************
*
*             Clear
*
*************************************************
*/

void GUI_MEMDEV_Clear(GUI_MEMDEV_Handle hMem) {
  if (!hMem) {
    if ((hMem = GUI_Context.hDevData) ==0) {
      return;
    }
  }
  {
    GUI_MEMDEV* pDev = GUI_MEMDEV_h2p(hMem);  /* Convert to pointer */
    GUI_USAGE_h hUsage = pDev->hUsage; 
    if (hUsage) {
      GUI_USAGE* pUsage = GUI_USAGE_h2p(hUsage);
      GUI_USAGE_Clear(pUsage);
    }/* else {
      GUI_Clear();
    }*/
  }
}

#else

void GUIDEV_Clear(void) {} /* avoid empty object files */

#endif /* GUI_MEMDEV_SUPPORT */
