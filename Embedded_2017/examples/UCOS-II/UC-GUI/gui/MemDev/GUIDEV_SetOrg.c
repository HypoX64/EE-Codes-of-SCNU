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
      *************************************************
      *                                               *
      *             SetOrg                            *
      *                                               *
      *************************************************
*/

void GUI_MEMDEV_SetOrg(GUI_MEMDEV_Handle hMem, int x0, int y0) {
  /* Make sure memory handle is valid */
  if (!hMem) {
    if ((hMem = GUI_Context.hDevData) ==0) {
      return;
    }
  }
  GUI_LOCK();
  {
    GUI_MEMDEV* pDev = GUI_MEMDEV_h2p(hMem);  /* Convert to pointer */
    pDev->y0 = y0;
    pDev->x0 = x0;
    LCD_SetClipRectMax();
    /* Move usage along */
    if (pDev->hUsage) {
      GUI_USAGE* pUsage = GUI_USAGE_h2p(pDev->hUsage);
      if (((pUsage->XSize = pDev->XSize) != 0) && ((pUsage->YSize = pDev->YSize) != 0)) {
        pUsage->x0 = x0;
        pUsage->y0 = y0;
      }
    }
  }
  GUI_UNLOCK();
}

#else

void GUIDEV_SetOrg(void) {} /* avoid empty object files */

#endif /* GUI_MEMDEV_SUPPORT */
