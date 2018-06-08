/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 2002         SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

**** emWin/GSC Grafical user interface for embedded applications ****
emWin is protected by international copyright laws. Knowledge of the
source code may not be used to write a similar product. This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUI_OnKey.c
Purpose     : Implementation of GUI_StoreKeyMsg
---------------------------END-OF-HEADER------------------------------
*/


#include "GUI_Protected.H"

static int _Key;
static int _KeyMsgCnt;
static struct {
  int Key;
  int PressedCnt;
} _KeyMsg;

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

/*******************************************************************
*
*                  GUI_GetKey
*/

int GUI_GetKey(void) {
  int r = Key_GetKey();
  _Key = r;
  return r;
}
int GUI_GetKeyNoDel(void) {
//  int r = DrvKeyGetNoDel();
//  return r;
}
/*******************************************************************
*
*                  GUI_StoreKey
*/

void GUI_StoreKey(int Key) {
  if (!_Key)
    _Key = Key;
}

/*******************************************************************
*
*                  GUI_ClearKeyBuffer
*/

void GUI_ClearKeyBuffer(void) {
  while (GUI_GetKey());
}

/*********************************************************************
*
*     GUI_StoreKeyMsg
*/
void GUI_StoreKeyMsg(int Key, int PressedCnt) {
  #if GUI_WINSUPPORT    /* If 0, WM will not generate any code */
  _KeyMsg.Key = Key;
  _KeyMsg.PressedCnt = PressedCnt;
  _KeyMsgCnt = 1;
  #else
    GUI_USE_PARA(PressedCnt);
    GUI_StoreKey(Key);
  #endif
}

/*********************************************************************
*
*     GUI_PollKeyMsg
*/
#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */
int GUI_PollKeyMsg(void) {
  int r = 0;
  if (_KeyMsgCnt) {
    int Key;
    Key = _KeyMsg.Key;
    if (WM_OnKey(Key, _KeyMsg.PressedCnt) == 0) {
      if (_KeyMsg.PressedCnt == 1) {
        GUI_StoreKey(Key);
      }
    }
    _KeyMsgCnt--;
    r = 1;              /* We have done something */
  }
  return r;
}
#endif

/*********************************************************************
*
*     GUI_SendKeyMsg
*
* Purpose:
*   Send the key to a window using the window manager (if available).
*   If no window is ready to take the input, we call the store routine
*   and wait for somebody to poll the buffer.
*/
void GUI_SendKeyMsg(int Key, int PressedCnt) {
  #if GUI_WINSUPPORT    /* If 0, WM will not generate any code */
  if (!WM_OnKey(Key, PressedCnt)) {
    GUI_StoreKeyMsg(Key, PressedCnt);
  }
  #else
  GUI_StoreKeyMsg(Key, PressedCnt);
  #endif
}


