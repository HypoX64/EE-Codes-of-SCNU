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
File        : EditDec
Purpose     : Edit decimal values
---------------------------END-OF-HEADER------------------------------
*/

#include <string.h>

#include "EDIT.h"
#include "GUIDebug.h"
#include "GUI_Protected.h"
#include "EDIT_Private.h"

#if GUI_WINSUPPORT


/*********************************************************************
*
*        Defaults for config switches
*
**********************************************************************
*/
#ifndef EDIT_DEC_DIGITONLY
  #define EDIT_DEC_DIGITONLY     0
#endif


/*********************************************************************
*
*        static Helpers
*
**********************************************************************
*/

static int _DecChar2Int(int Char) {
  if ((Char >= '0') && (Char <= '9'))
    return Char - '0';
  return -1;
}

static void _UpdateBuffer(EDIT_Obj* pObj) {
  char * s = (char*) WM_HMEM2Ptr(pObj->hpText);
  if (pObj->Flags == GUI_EDIT_SIGNED) {
    I32 Result = GUI_AddSign(pObj->CurrentValue, &s);
    GUI_AddDecShift(Result, pObj->MaxLen - 1, pObj->NumDecs, &s);
  } else {
    GUI_AddDecShift(pObj->CurrentValue, pObj->MaxLen, pObj->NumDecs, &s);
  }
}

static void _EditDec(int Digit, EDIT_Obj* pObj, EDIT_Handle hObj) {
  I32 Result = 0;
  int i, Pos = 0;
  char * s = (char*) WM_HMEM2Ptr(pObj->hpText);
  for (i = 0; i < pObj->MaxLen; i++) {
    int Index = pObj->MaxLen - i - 1;
    if (Index == pObj->CursorPos) {
      Result += GUI_Pow10[Pos++] * Digit;
    } else {
      char c = *(s + Index);
      int Value = _DecChar2Int(c);
      if (Value >= 0) {
        Result += GUI_Pow10[Pos++] * Value;
      }
      if (c == '-') {
        Result *= -1;
      }
    }
  }
  EDIT_SetValue(hObj, Result);
}

static char _GetCurrentChar(EDIT_Obj* pObj) {
  return *((char*) WM_HMEM2Ptr(pObj->hpText) + pObj->CursorPos);
}

#if EDIT_DEC_DIGITONLY
static int GetCurrentDigit(EDIT_Obj* pObj) {
  return _DecChar2Int(_GetCurrentChar(pObj));
}
#endif

static void _MakePositive(EDIT_Obj* pObj, EDIT_Handle hObj) {
  if ((I32)pObj->CurrentValue < 0) {
    EDIT_SetValue(hObj, (I32)pObj->CurrentValue * -1);
  }
}

static void _MakeNegative(EDIT_Obj* pObj, EDIT_Handle hObj) {
  if ((I32)pObj->CurrentValue > 0) {
    EDIT_SetValue(hObj, (I32)pObj->CurrentValue * -1);
  }
}

static void _SwapSign(EDIT_Obj* pObj, EDIT_Handle hObj) {
  if ((I32)pObj->CurrentValue > 0)
    _MakeNegative(pObj, hObj);
  else
    _MakePositive(pObj, hObj);
}

static void _IncrementCursor(EDIT_Obj* pObj) {
  if (pObj->CursorPos < (pObj->MaxLen - 1))
    pObj->CursorPos++;
  if (_GetCurrentChar(pObj) == '.') {
    if (pObj->CursorPos < (pObj->MaxLen - 1)) {
      pObj->CursorPos++;
    } else {
      pObj->CursorPos--;
    }
  }
}

#if !EDIT_DEC_DIGITONLY
static void _AddPosition(EDIT_Obj* pObj, EDIT_Handle hObj, int Sign) {
  int Pos;
  I32 v;
  v = Sign;
  Pos = pObj->MaxLen - pObj->CursorPos-1;
  if (pObj->NumDecs && (Pos > pObj->NumDecs)) {
    Pos--;
  }
  while (Pos--) {
    v *= 10;
  }
  EDIT_SetValue(hObj, (I32)pObj->CurrentValue + v);
}
#endif

/*********************************************************************
*
*             Handle input
*
**********************************************************************
*/

static void _AddKeyDec(EDIT_Obj* pObj, EDIT_Handle hObj, int Key) {
  char c;
  if (pObj) {
    switch (Key) {
      case '+':
        if (pObj->CursorPos == 0) {
          _MakePositive(pObj, hObj);
          _IncrementCursor(pObj);
        }
        break;
      case '-':
        if (pObj->CursorPos == 0) {
          _MakeNegative(pObj, hObj);
          _IncrementCursor(pObj);
        }
        break;
      #if EDIT_DEC_DIGITONLY
        case GUI_KEY_UP:
          c = _GetCurrentChar(pObj);
          if ((c == '-') || (c == '+')) {
            _SwapSign(pObj, hObj);
          } else {
            int Digit = GetCurrentDigit(pObj) + 1;
            if (Digit > 9)
              Digit = 0;
            _EditDec(Digit, pObj, hObj);
          }
          break;
        case GUI_KEY_DOWN:
          c = _GetCurrentChar(pObj);
          if ((c == '-') || (c == '+')) {
            _SwapSign(pObj, hObj);
          } else {
            int Digit = GetCurrentDigit(pObj) - 1;
            if (Digit < 0)
              Digit = 9;
            _EditDec(Digit, pObj, hObj);
          }
          break;
      #else
        case GUI_KEY_UP:
          c = _GetCurrentChar(pObj);
          if ((c == '-') || (c == '+')) {
            _SwapSign(pObj, hObj);
          } else {
            _AddPosition(pObj, hObj, 1);
          }
          break;
        case GUI_KEY_DOWN:
          c = _GetCurrentChar(pObj);
          if ((c == '-') || (c == '+')) {
            _SwapSign(pObj, hObj);
          } else {
            _AddPosition(pObj, hObj, -1);
          }
          break;
      #endif
      case GUI_KEY_RIGHT:
        _IncrementCursor(pObj);
        break;
      case GUI_KEY_LEFT:
        if (pObj->CursorPos > 0)
          pObj->CursorPos--;
        if (_GetCurrentChar(pObj) == '.') {
          if (pObj->CursorPos > 0) {
            pObj->CursorPos--;
          } else {
            pObj->CursorPos++;
          }
        }
        break;
      default:
        {
          char c = _GetCurrentChar(pObj);
          if ((c != '-') && (c != '+')) {
            int Digit = _DecChar2Int(Key);
            if (Digit >= 0) {
              _EditDec(Digit, pObj, hObj);
              _IncrementCursor(pObj);
            }
          }
        }
        break;
    }
  }
  _UpdateBuffer(pObj);
}

/*********************************************************************
*
*             Exported routines
*
**********************************************************************
*/

void EDIT_SetDecMode(EDIT_Handle hEdit, I32 Value, I32 Min, I32 Max, int Shift, U8 Flags) {
  EDIT_Obj* pObj;
  WM_LOCK();
  if (hEdit) {
    pObj = EDIT_H2P(hEdit);
    pObj->pfAddKeyEx    = _AddKeyDec;
    pObj->pfUpdateBufer = _UpdateBuffer;
    pObj->CurrentValue  = Value;
    pObj->CursorPos     = 0;
    pObj->Min           = Min;
    pObj->Max           = Max;
    pObj->NumDecs       = Shift;
    pObj->Flags         = Flags;
    pObj->EditMode      = GUI_EDIT_MODE_OVERWRITE;
    _UpdateBuffer(pObj);
    if (_GetCurrentChar(pObj) == '.') {
      pObj->CursorPos++;
    }
  }
  WM_UNLOCK();
}

#else  /* avoid empty object files */

void EditDec_C(void);

#endif /* GUI_WINSUPPORT */
