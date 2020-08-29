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
File        : 
Purpose     : Dialog box include
----------------------------------------------------------------------
Open items:
None
--------------------END-OF-HEADER-------------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "Dialog.h"
#include "Widget.h"
#include "WM_Intern.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

/* Define colors */
#ifndef DIALOG_BKCOLOR0_DEFAULT
  #define DIALOG_BKCOLOR0_DEFAULT 0xc0c0c0
#endif

/*********************************************************************
*
*           static data;
*
**********************************************************************
*/
static WM_CALLBACK* _cb;
static int _r;
static LCD_COLOR _BkColor = DIALOG_BKCOLOR0_DEFAULT;

/*********************************************************************
*
*           static code: API functions
*
**********************************************************************
*/





/************************************************************
*
*           _cbDialog
  This callback is hooked before the user callback in order to be
  able to intercept some messages.
*/

static void _cbDialog(WM_MESSAGE* pMsg) {
  if (_cb) {
    (*_cb)(pMsg);
  }
}

/*********************************************************************
*
*           Public code: API functions
*
**********************************************************************
*/

/************************************************************
*
*           GUI_CreateDialogbox
*/
WM_HWIN GUI_CreateDialogBox(const GUI_WIDGET_CREATE_INFO* paWidget, int NumWidgets, WM_CALLBACK* cb, WM_HWIN hParent,
                            int x0, int y0)
{
  WM_HWIN hDialog = paWidget->pfCreateIndirect(paWidget, hParent, x0, y0, cb);     /* Create parent window */
  WM_HWIN hDialogClient = WM_GetClientWindow(hDialog);
  WIDGET_OrState(hDialog, paWidget->Flags);
  WM_ShowWindow(hDialog);
  WM_ShowWindow(hDialogClient);
  while (--NumWidgets > 0) {
    WM_HWIN hChild;
    paWidget++;
    hChild = paWidget->pfCreateIndirect(paWidget, hDialogClient, 0, 0, 0);     /* Create child window */
    WM_ShowWindow(hChild);
  }
  WM_SetFocusOnNextChild(hDialog);     /* Set the focus to the first child */
  WM__SendMessageNoPara(hDialogClient, WM_INIT_DIALOG);
  return hDialog;
}

/************************************************************
*
*           GUI_EndDialog
*/
void GUI_EndDialog(WM_HWIN hWin, int r) {
  _cb = NULL;
  _r = r;
  WM_DeleteWindow(hWin);
}

/************************************************************
*
*           DIALOG_GetBkColor()
*/
LCD_COLOR DIALOG_GetBkColor(void) {
  return _BkColor;
}

/************************************************************
*
*           DIALOG_SetBkColor()
*/
LCD_COLOR DIALOG_SetBkColor(LCD_COLOR BkColor) {
  LCD_COLOR r;
  r = _BkColor;
  _BkColor = BkColor;
  return r;
}

/************************************************************
*
*           GUI_ExecDialogbox
*/
int     GUI_ExecDialogBox(const GUI_WIDGET_CREATE_INFO* paWidget,
                          int NumWidgets, WM_CALLBACK* cb, WM_HWIN hParent,
                          int x0, int y0)
{
  _cb = cb;
  GUI_CreateDialogBox(paWidget, NumWidgets, _cbDialog, hParent, x0, y0);
  while (_cb) {
    if (!GUI_Exec())
      GUI_X_ExecIdle();
  }
  return _r;
}


#else
  void Dialog_c(void);    /* Avoid problems with empty object modules */
#endif   /* GUI_WINSUPPORT */

