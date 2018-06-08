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
File        : GUIDev2.C
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
*
*             SetYSize
*
*************************************************
*/
void GUI_MEMDEV_ReduceYSize(GUI_MEMDEV_Handle hMem, int YSize) {
  /* Make sure memory handle is valid */
  if (!hMem)
    hMem = GUI_Context.hDevData;
  if (!hMem)
    return;
  { GUI_MEMDEV* pDevData = (GUI_MEMDEV*) GUI_ALLOC_LOCK(hMem);  /* Convert to pointer */
    if (YSize < pDevData->YSize)
      pDevData->YSize = YSize;
  } GUI_ALLOC_UNLOCK(hMem);
  
}

#else
        
void GUIDEV_ReduceYSize(void) {} /* avoid empty object files */

#endif /* GUI_MEMDEV_SUPPORT */
