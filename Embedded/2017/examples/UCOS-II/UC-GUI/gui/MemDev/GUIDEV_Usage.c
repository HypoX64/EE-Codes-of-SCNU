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
File        : GUIDev.C
Purpose     : Implementation of memory devices
---------------------------END-OF-HEADER------------------------------
*/


#include <string.h>
#include "GUI_Protected.h"
#include "GUIDebug.h"

/* Memory device capabilities are compiled only if support for them is enabled.*/ 
#if GUI_SUPPORT_MEMDEV

/*
  *****************************************************************
  *
  *              GUI_USAGE_Select
  *
  *****************************************************************

Purpose:
  Selects a usage object into the active memory device.
*/

void GUI_USAGE_Select(GUI_USAGE_Handle hUsage) {
  GUI_MEMDEV * pDev;
  GUI_LOCK();
  pDev = GUI_MEMDEV_h2p(GUI_Context.hDevData);
  pDev->hUsage = hUsage;
  GUI_UNLOCK();
}

/************************************************
*
*             DecUseCnt
*
*************************************************

Purpose: Decrements the usage count and deletes the usage object if
         the counter reaches 0.
*/

void GUI_USAGE_DecUseCnt(GUI_USAGE_Handle  hUsage) {
  GUI_USAGE* pThis;
  GUI_LOCK();
  pThis = GUI_USAGE_h2p(hUsage);
  if (--pThis->UseCnt == 0) {
    GUI_ALLOC_FREE(hUsage);
  }
  GUI_UNLOCK();
}

#else

void GUIDEV_Usage(void) {} /* avoid empty object files */

#endif /* GUI_SUPPORT_MEMDEV */
