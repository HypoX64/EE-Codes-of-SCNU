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
File        : GUIDEMO_Dialog.c
Purpose     : Automotive samples
----------------------------------------------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "GUI.H"
#include "GUIDEMO.H"
#include "LCD_ConfDefaults.h"
#include "WM.h"
#include "Dialog.h"
#include "LISTBOX.h"
#include "EDIT.h"
#include "SLIDER.h"
#include "FRAMEWIN.h"

#if GUI_SUPPORT_MEMDEV && GUI_WINSUPPORT



/*********************************************************************
*
*       defines
*
**********************************************************************
*/


/*********************************************************************
*
*       static data
*
**********************************************************************
*/

/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created manually, but could also be created by a GUI-builder.
*/
static const GUI_WIDGET_CREATE_INFO aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Dialog", 0,               10,   10, 180, 230, FRAMEWIN_CF_MOVEABLE, 0 },
  { BUTTON_CreateIndirect,   "OK",     GUI_ID_OK,      100,    5,  60,  20, 0, 0 },
  { BUTTON_CreateIndirect,   "Cancel", GUI_ID_CANCEL,  100,   30,  60,  20, 0, 0 },
  { TEXT_CreateIndirect,     "LText",  0,               10,   55,  48,  15, 0, GUI_TA_VCENTER | GUI_TA_LEFT  },
  { TEXT_CreateIndirect,     "RText",  0,               10,   80,  48,  15, 0, GUI_TA_VCENTER | GUI_TA_RIGHT },
  { EDIT_CreateIndirect,     "",       GUI_ID_EDIT0,    60,   55, 100,  15, 0, 50 },
  { EDIT_CreateIndirect,     "",       GUI_ID_EDIT1,    60,   80, 100,  15, 0, 50 },
  { TEXT_CreateIndirect,     "Hex",    0,               10,  100,  48,  15, 0, GUI_TA_VCENTER | GUI_TA_RIGHT },
  { EDIT_CreateIndirect,     "",       GUI_ID_EDIT2,    60,  100, 100,  15, 0, 6 },
  { TEXT_CreateIndirect,     "Bin",    0,               10,  120,  48,  15, 0, GUI_TA_VCENTER | GUI_TA_RIGHT },
  { EDIT_CreateIndirect,     "",       GUI_ID_EDIT3,    60,  120, 100,  15, 0, 0 },
  { LISTBOX_CreateIndirect,  "",       GUI_ID_LISTBOX0, 10,    5,  48,  40, 0, 0 },
  { SLIDER_CreateIndirect,   NULL,     GUI_ID_SLIDER0,  10,  140, 100,  20, 0, 0 },
  { SLIDER_CreateIndirect,   NULL,     GUI_ID_SLIDER1,  10,  170, 140,  30, 0, 0 }
};


/*********************************************************************
*
*              Initializers for listbox
*/
static const GUI_ConstString _apListBox[] = {
  "English", "Deutsch", "Français", "Japanese", "Italiano", NULL
};

/*********************************************************************
*
*              Keys for demonstration of dialog box
*/
typedef struct {
  unsigned char Id;
  int Time;
} KEYSIM;


static KEYSIM _aID[] = {
  { GUI_KEY_TAB, 500 },
  { GUI_KEY_TAB, 500 },
  { GUI_KEY_TAB, 500 },
  { GUI_KEY_TAB, 500 },
  { GUI_KEY_TAB, 500 },
  { GUI_KEY_TAB, 500 },
  { GUI_KEY_DOWN, 500 },
  { GUI_KEY_DOWN, 500 },
  { GUI_KEY_DOWN, 500 },
  { GUI_KEY_DOWN, 500 },
  { GUI_KEY_UP, 100 }
};

/*********************************************************************
*
*       static code
*
**********************************************************************
*/

/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbCallback(WM_MESSAGE * pMsg) {
  int NCode, Id;
  WM_HWIN hEdit0, hEdit1, hEdit2, hEdit3, hListBox;
  WM_HWIN hWin = pMsg->hWin;
  switch (pMsg->MsgId) {
    case WM_INIT_DIALOG:
      /* Get window handles for all widgets */
      hEdit0   = WM_GetDialogItem(hWin, GUI_ID_EDIT0);
      hEdit1   = WM_GetDialogItem(hWin, GUI_ID_EDIT1);
      hEdit2   = WM_GetDialogItem(hWin, GUI_ID_EDIT2);
      hEdit3   = WM_GetDialogItem(hWin, GUI_ID_EDIT3);
      hListBox = WM_GetDialogItem(hWin, GUI_ID_LISTBOX0);
      /* Initialize all widgets */
      EDIT_SetText(hEdit0, "EDIT widget 0");
      EDIT_SetText(hEdit1, "EDIT widget 1");
      EDIT_SetTextAlign(hEdit1, GUI_TA_LEFT);
      EDIT_SetHexMode(hEdit2, 0x1234, 0, 0xffff);
      EDIT_SetBinMode(hEdit3, 0x1234, 0, 0xffff);
      LISTBOX_SetText(hListBox, _apListBox);
      SCROLLBAR_CreateAttached(hListBox, SCROLLBAR_CF_VERTICAL);
      break;
    case WM_KEY:
      switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) {
      case GUI_KEY_ESCAPE:
        GUI_EndDialog(hWin, 1);
        break;
      case GUI_KEY_ENTER:
        GUI_EndDialog(hWin, 0);
        break;
      }
      break;
    case WM_NOTIFY_PARENT:
      Id    = WM_GetId(pMsg->hWinSrc);    /* Id of widget */
      NCode = pMsg->Data.v;               /* Notification code */
      switch (NCode) {
        case WM_NOTIFICATION_RELEASED:    /* React only if released */
          if (Id == GUI_ID_OK) {          /* OK Button */
            GUI_EndDialog(hWin, 0);
          }
          if (Id == GUI_ID_CANCEL) {      /* Cancel Button */
            GUI_EndDialog(hWin, 1);
          }
          break;
        case WM_NOTIFICATION_SEL_CHANGED: /* Selection changed */
          FRAMEWIN_SetText(hWin, "Dialog - sel changed");
          break;
        default:
          FRAMEWIN_SetText(hWin, "Dialog - notification received");
      }
      break;
    default:
      WM_DefaultProc(pMsg);
  }
}



/*********************************************************************
*
*       GUIDEMO_Dialog
*
**********************************************************************
*/

void GUIDEMO_Dialog(void) {
  int i;
  WM_HWIN hWin;
  GUI_COLOR DesktopColorOld;
  GUI_CURSOR_Show();
  GUIDEMO_ShowIntro("Dialog boxes",
                    "Dialog boxes"
                    "\ncan easily be created");
  GUIDEMO_HideInfoWin();
  DesktopColorOld = WM_SetDesktopColor(GUI_RED);      /* Automatically update desktop window */
  hWin = GUI_CreateDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate), _cbCallback, 0, 0, 0);
  for (i = 0; i < GUI_COUNTOF(_aID); i++) {
    GUIDEMO_Delay(_aID[i].Time);
    GUI_SendKeyMsg(_aID[i].Id, 1);
  }
  GUIDEMO_Delay(100);
  for (i = 0; i <= 100; i+=10) {
    if (WM_IsWindow(hWin)) {
      SLIDER_SetValue(WM_GetDialogItem(hWin, GUI_ID_SLIDER1), i);
    }
    GUIDEMO_Delay(100);
  }
  if (WM_IsWindow(hWin)) {
    GUIDEMO_Delay(100);
    WM_MoveTo(hWin, 20,50);
  }
  if (WM_IsWindow(hWin)) {
    GUI_Delay(1000);
    WM_MoveTo(hWin,120,50);
  }
  /* Cleanup ... */
  if (WM_IsWindow(hWin)) {
    GUI_Delay(1000);
    WM_DeleteWindow(hWin);
  }
  GUIDEMO_NotifyStartNext();
  WM_SetDesktopColor(DesktopColorOld);      /* Restore old settings */
}

#else

void GUIDEMO_Dialog(void) {}

#endif /* GUI_SUPPORT_MEMDEV */
