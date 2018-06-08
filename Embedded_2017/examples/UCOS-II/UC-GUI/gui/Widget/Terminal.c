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
File        : TEMPLATE.c
Purpose     : Template for new emWin GSC widgets
----------------------------------------------------------------------
Version-Date---Author-Explanation
----------------------------------------------------------------------
0.0     yymmdd RS     Start of development
----------------------------------------------------------------------
Known problems or limitations with current version
----------------------------------------------------------------------
None.
----------------------------------------------------------------------
Open issues
----------------------------------------------------------------------
None
---------------------------END-OF-HEADER------------------------------
*/


#include <stdlib.h>
#include <string.h>

#include "GUI.h"
#if GUI_WINSUPPORT

#include "TERMINAL.h"
#include "GUIDebug.h"


/*********************************************************************
*
*              Private config defaults
*
**********************************************************************
*/
/* None */


/*********************************************************************
*
*                 Object definition
*
**********************************************************************

*/
typedef struct {
  WM_Obj WMObj;
  WM_HMEM hpText;
  I16 MaxLen;
  const GUI_FONT* pFont;
  int Flags;
  #if GUI_DEBUG_LEVEL >1
    int DebugId;
  #endif  
} TERMINAL_Obj;

/*********************************************************************
*
*              Static data
*
**********************************************************************
*/

/* None */

/*********************************************************************
*
*                 Macros for internal use
*
**********************************************************************
*/

#define TERMINAL_H2P(h) ((TERMINAL_Obj*)WM_HMEM2Ptr(h))
#define Invalidate(h) WM_InvalidateWindow(h)

#if GUI_DEBUG_LEVEL >1
  #define OBJECT_ID 0x5565   /* Magic numer, should be unique if possible */
  #define ASSERT_IS_VALID_PTR(p) GUI_DEBUG_ERROROUT_IF(p->DebugId != OBJECT_ID, "EDIT.C: Wrong handle type or Object not init'ed")
  #define INIT_ID(p)   p->DebugId = OBJECT_ID
  #define DEINIT_ID(p) p->DebugId = 0
#else
  #define ASSERT_IS_VALID_PTR(p)
  #define INIT_ID(p)
  #define DEINIT_ID(p)
#endif

/*********************************************************************
*
*                 Static routines
*
**********************************************************************
*/

static void Paint(TERMINAL_Obj* pObj/*, GUI_RECT*pRect*/) {
  char*s = (char*) WM_HMEM2Ptr(pObj->hpText);
  GUI_RECT rClient;
  GUI_DEBUG_LOG("TERMINAL: Paint(..)\n");
  GUI_GetClientRect(&rClient);
/* Draw background */
  GUI_SetBkColor (GUI_WHITE/*pObj->aBkColor[0]*/);
  GUI_SetColor   (GUI_BLACK /*pObj->aTextColor[0]*/);
  GUI_Clear();
/* Draw the text */  
  {
    GUI_RECT rText = rClient;
    rText.x0 +=3;
//    GUI_SetFont    (pObj->pFont);
    GUI_DispStringInRect(s, &rText, GUI_TA_LEFT);
  }
}

static void Delete(TERMINAL_Obj* pObj) {
  if (pObj->hpText) {
    GUI_ALLOC_Free(pObj->hpText);
    pObj->hpText = 0;
    GUI_DEBUG_LOG("TERMINAL: Delete: Deleting attached string\n");
  }
}


static WM_RESULT _TERMINAL_Callback (/*const*/ WM_MESSAGE*pMsg) {
  TERMINAL_Handle hObj = pMsg->hWin;
  TERMINAL_Obj* pObj = TERMINAL_H2P(hObj);
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_DEBUG_LOG("BUTTON: _Callback(WM_PAINT)\n");
    Paint(pObj/*, (GUI_RECT*)pMsg->Data.p*/);
    return;
  case WM_DELETE:
    GUI_DEBUG_LOG("EDIT: _Callback(WM_DELETE)\n");
    Delete(pObj);
    break;       /* No return here ... WM_DefaultProc needs to be called */
  }
  WM_DefaultProc(pMsg);
}


/*********************************************************************
*
*           Exported routines:  Create
*
**********************************************************************
*/

/* Note: the parameters to a create function may vary.
         Some widgets may have multiple create functions */


TERMINAL_Handle TERMINAL_CreateAsChild( int x0, int y0, int xsize, int ysize, WM_HWIN hWinParent, int MaxLen, int Flags) {
  TERMINAL_Handle hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hWinParent, 
                       Flags, _TERMINAL_Callback,
                       sizeof(TERMINAL_Obj)-sizeof(WM_Obj));
  if (hObj) {
    TERMINAL_Obj* pObj = TERMINAL_H2P(hObj);
    pObj->hpText = WM_ALLOC(MaxLen+1);
    /* init member variables */
    if (pObj->hpText ==0) {
      GUI_DEBUG_ERROROUT("TERMINAL_Create failed to alloc buffer");
      TERMINAL_Delete(hObj);
      hObj =0;
    }
    pObj->MaxLen = MaxLen;
  } else {
    GUI_DEBUG_ERROROUT_IF(hObj==0, "TERMINAL_Create failed")
  }
  return hObj;
}

TERMINAL_Handle TERMINAL_Create(int x0, int y0, int xsize, int ysize, int MaxLen, int Flags) {
  return TERMINAL_CreateAsChild(x0, y0, xsize, ysize, 0/* hWinParent */,  MaxLen, Flags);
}

TERMINAL_Handle TERMINAL_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb) {
  TERMINAL_Handle  hThis;
  GUI_USE_PARA(cb);
  hThis = TERMINAL_CreateAsChild(pCreateInfo->x0 + x0, pCreateInfo->y0 + y0, pCreateInfo->xSize, pCreateInfo->ySize,
                                 hWinParent, pCreateInfo->Id, pCreateInfo->Flags);
  return hThis;
}


/*********************************************************************
*
*        Exported routines:  Various methods
*
**********************************************************************
*/
void TERMINAL_SetFont(TERMINAL_Handle hObj, const GUI_FONT* pfont) {
  TERMINAL_Obj* pObj = TERMINAL_H2P(hObj);
  pObj->pFont = pfont;
  Invalidate(hObj);
}

void TERMINAL_Add(TERMINAL_Handle hObj, const char* sAdd) {
  if (!sAdd) {
    GUI_DEBUG_WARN("TERMINAL_Add: NULL pointer passed");
    return;
  }
  if (hObj) {
    TERMINAL_Obj* pObj = TERMINAL_H2P(hObj);
    char* sBuffer = (char*) WM_HMEM2Ptr(pObj->hpText);
    int AddLen = strlen(sAdd);
    int NewLen = AddLen+strlen(sBuffer);
    if (AddLen > pObj->MaxLen) {
      GUI_DEBUG_WARN("TERMINAL_Add: String longer than buffer !");
      return;
    }
    /* Make space in buffer if necessary */
    if (NewLen > pObj->MaxLen) {
      *sBuffer =0;
    }
    sBuffer+= strlen(sBuffer); 
    memcpy(sBuffer, sAdd, AddLen);
    *(sBuffer+AddLen) = 0;
    Invalidate(hObj);
  }
}

void TERMINAL_GetText(TERMINAL_Handle hObj, char* sDest, int MaxLen) {
  TERMINAL_Obj* pObj = TERMINAL_H2P(hObj);
  if (pObj) {
    char * sSource = (char*) WM_HMEM2Ptr(pObj->hpText);
    int Len = strlen(sSource);
    if (Len > (MaxLen - 1))
      Len = MaxLen - 1;
    memcpy((void *)sDest, (const void *)sSource, Len);
    *(sDest+Len) = 0;
  }
}

#else

void WIDGET_Terminal(void) {} /* avoid empty object files */

#endif   /* if GUI_WINSUPPORT */

