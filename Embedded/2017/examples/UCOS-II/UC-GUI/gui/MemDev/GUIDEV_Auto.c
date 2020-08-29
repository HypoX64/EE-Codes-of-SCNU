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
File        : GUIAutoDev.c
Purpose     : Implementation of automatic banding memory devices
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.h"
#include "GUIDebug.h"

/*
 Memory device capabilities are compiled only if support for them is enabled.
*/ 

#if GUI_SUPPORT_MEMDEV

/******************************************************************
*
*              GUI_MEMDEV_CreateAuto
*
*******************************************************************
*/

int GUI_MEMDEV_CreateAuto(GUI_AUTODEV * pAutoDev) {
  pAutoDev->FirstCall = 1;
  return 0;
}

/******************************************************************
*
*              GUI_MEMDEV_DeleteAuto
*
*******************************************************************
*/

void GUI_MEMDEV_DeleteAuto(GUI_AUTODEV * pAutoDev) {
  GUI_USE_PARA(pAutoDev);
}

/******************************************************************
*
*              GUI_MEMDEV_DrawAuto
*
*******************************************************************
*/

int GUI_MEMDEV_DrawAuto(GUI_AUTODEV * pAutoDev, GUI_AUTODEV_INFO * pAutoDevInfo, GUI_CALLBACK_VOID_P * pfDraw, void * pData) {
  GUI_RECT rTemp;
  GUI_HMEM hMem = GUI_MEASDEV_Create();
  if (!hMem) {
    return 1;
  }
  GUI_MEASDEV_Select(hMem);
  /* Measure area to draw */
  if (pAutoDev->FirstCall) {
    /* Measure complete area */
    pAutoDevInfo->DrawFixed = 1;
    pfDraw(pData);
    GUI_MEASDEV_GetRect(hMem, &pAutoDev->rView);
    /* Measure variable area only */
    GUI_MEASDEV_ClearRect(hMem);
    pAutoDevInfo->DrawFixed = 0;
    pfDraw(pData);
    GUI_MEASDEV_GetRect(hMem, &pAutoDev->rPrev);
  } else {
    /* Measure variable area only */
    pfDraw(pData);
    GUI_MEASDEV_GetRect(hMem, &pAutoDev->rView);
    rTemp = pAutoDev->rView;
    GUI_MergeRect(&pAutoDev->rView, &pAutoDev->rView, &pAutoDev->rPrev);
    pAutoDev->rPrev = rTemp;
  }
  GUI_MEASDEV_Delete(hMem);



  /* Do the actual drawing */
  pAutoDevInfo->DrawFixed = 1;
  if (GUI_MEMDEV_Draw(&pAutoDev->rView, pfDraw, pData, 0, GUI_MEMDEV_NOTRANS)) {
    return 1;
  }
  pAutoDevInfo->DrawFixed = 0;
  pAutoDev->FirstCall = 0;
  return 0;
}

#else

void GUIDEV_Auto(void) {} /* avoid empty object files */

#endif /* GUI_SUPPORT_MEMDEV */
