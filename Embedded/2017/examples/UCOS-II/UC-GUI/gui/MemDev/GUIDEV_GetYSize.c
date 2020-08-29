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
File        : GUIDev3.C
Purpose     : Implementation of memory devices, add. module
---------------------------END-OF-HEADER------------------------------
*/


#include <string.h>
#include "GUI_Protected.h"
#include "GUIDebug.h"

/* Memory device capabilities are compiled only if support for them is enabled. */ 
#if GUI_SUPPORT_MEMDEV

        
/*
************************************************
*
*             GetYSize
*
*************************************************
*/
int GUI_MEMDEV_GetYSize(GUI_MEMDEV_Handle hMem) {
  int r;
  if (!hMem) {
    if ((hMem = GUI_Context.hDevData) ==0) {
      return 0;
    }
  }
  { GUI_MEMDEV* pDevData = (GUI_MEMDEV*) GUI_ALLOC_LOCK(hMem);  /* Convert to pointer */
    r = pDevData->YSize;
  } GUI_ALLOC_UNLOCK(hMem);
  return r;
}

#else

void GUIDEV_GetYSize(void) {} /* avoid empty object files */

#endif /* GUI_MEMDEV_SUPPORT */
