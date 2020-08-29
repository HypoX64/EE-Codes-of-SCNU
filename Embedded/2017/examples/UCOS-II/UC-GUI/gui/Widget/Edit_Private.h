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
File        : EDIT_Private.h
Purpose     : Internal header file
---------------------------END-OF-HEADER------------------------------
*/


#if GUI_WINSUPPORT

#include "WIDGET.h"

/*********************************************************************
*
*             Types
*
**********************************************************************
*/

typedef struct EDIT_Obj_struct EDIT_Obj;

typedef void EDIT_ADDKEY_EX(EDIT_Obj* pObj, EDIT_Handle hObj, int Key);
typedef void EDIT_UPDATE_BUFFER(EDIT_Obj* pObj);

struct EDIT_Obj_struct {
  WIDGET Widget;
  WM_HMEM hpText;
  I16 MaxLen;
  GUI_COLOR aTextColor[2];
  GUI_COLOR aBkColor[2];
  I16 Border;              /* Left and right border */
  I32 Min, Max;            /* Min max values as normalized floats (integers) */
  U8 NumDecs;              /* Number of decimals */
  U32 CurrentValue;        /* Current value */
  int CursorPos;           /* Cursor position. 0 means left most */
  U8 EditMode;             /* Insert or overwrite mode */
  U8 XSizeCursor;          /* Size of cursor when working in insert mode */
  U8 Flags;
  EDIT_ADDKEY_EX     * pfAddKeyEx;     /* Handle key input */
  EDIT_UPDATE_BUFFER * pfUpdateBufer;  /* Update textbuffer */
  U8 Align;
  const GUI_FONT* pFont;
  #if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
    int DebugId;
  #endif  
};

#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  EDIT_Obj* EDIT_h2p(EDIT_Handle h);
  #define EDIT_H2P(h) EDIT_h2p(h)
#else
  #define EDIT_H2P(h) ((EDIT_Obj*)WM_HMEM2Ptr(h))
#endif



#endif /* GUI_WINSUPPORT */
