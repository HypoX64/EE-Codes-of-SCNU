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
File        : EditBin
Purpose     : Edit binary values
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
*             Helpers
*
**********************************************************************
*/

static int _BinChar2Int(int Char) {
  if ((Char >= '0') && (Char <= '1'))
    return Char - '0';
  return -1;
}

static void _UpdateBuffer(EDIT_Obj* pObj) {
  char * s = (char*) WM_HMEM2Ptr(pObj->hpText);
  GUI_AddBin(pObj->CurrentValue, pObj->MaxLen, &s);
}

static void _EditBin(U8 Bit, EDIT_Obj* pObj, EDIT_Handle hObj) {
  int Pos = pObj->MaxLen - pObj->CursorPos - 1;   /* Bit position */
  U32 AndMask = ~(1   << Pos);
  U32 OrMask  =   Bit << Pos;
  I32 Result  = pObj->CurrentValue & AndMask;
  Result     |= OrMask;
  EDIT_SetValue(hObj, Result);
  /*
  U32 AndMask = ~(1   << Pos);
  U32 OrMask  =   Bit << Pos;
  pObj->CurrentValue &= AndMask;
  pObj->CurrentValue |= OrMask;
  if (pObj->CurrentValue > (U32)pObj->Max)
    pObj->CurrentValue = pObj->Max;
  if (pObj->CurrentValue < (U32)pObj->Min)
    pObj->CurrentValue = pObj->Min;
  */
}

static U8 _GetCurrentBit(EDIT_Obj* pObj) {
  int Pos = pObj->MaxLen - pObj->CursorPos - 1;   /* Bit position */
  U32 AndMask = 1 << Pos;
  U8 Bit = (pObj->CurrentValue & AndMask) >> Pos;
  return Bit;
}

static int _GetNumDigits(U32 Value) {
  int Ret;
  for (Ret = 0; Value; Value >>= 1, Ret++);
  return Ret;
}

/*********************************************************************
*
*             Handle input
*
**********************************************************************
*/

static void _AddKeyBin(EDIT_Obj* pObj, EDIT_Handle hObj, int Key) {
  if (pObj) {
    switch (Key) {
      case GUI_KEY_UP:
        {
          int Bit = _GetCurrentBit(pObj) + 1;
          if (Bit > 1)
            Bit = 0;
          _EditBin(Bit, pObj, hObj);
        }
        break;
      case GUI_KEY_DOWN:
        {
          int Bit = _GetCurrentBit(pObj) - 1;
          if (Bit < 0)
            Bit = 1;
          _EditBin(Bit, pObj, hObj);
        }
        break;
      case GUI_KEY_RIGHT:
        if (pObj->CursorPos < (pObj->MaxLen - 1))
          pObj->CursorPos++;
        break;
      case GUI_KEY_LEFT:
        if (pObj->CursorPos > 0)
          pObj->CursorPos--;
        break;
      default:
        {
          int Bit = _BinChar2Int(Key);
          if (Bit >= 0) {
            _EditBin(Bit, pObj, hObj);
            if (pObj->CursorPos < (pObj->MaxLen - 1))
              pObj->CursorPos++;
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

void EDIT_SetBinMode(EDIT_Handle hEdit, U32 Value, U32 Min, U32 Max) {
  EDIT_Obj* pObj;
  int MaxLen;
  WM_LOCK();
  pObj = EDIT_H2P(hEdit);
  pObj->pfAddKeyEx    = _AddKeyBin;
  pObj->pfUpdateBufer = _UpdateBuffer;
  pObj->CurrentValue = Value;
  pObj->CursorPos = 0;
  MaxLen = pObj->MaxLen;
  if (MaxLen <= 0 ) {
    MaxLen = _GetNumDigits(Max);
  }
  if (MaxLen > 32) {
    MaxLen = 32;
  }
  if (MaxLen != pObj->MaxLen) {
    EDIT_SetMaxLen(hEdit, MaxLen);
  }
  pObj->Min = Min;
  pObj->Max = Max;
  pObj->EditMode = GUI_EDIT_MODE_OVERWRITE;
  _UpdateBuffer(pObj);
  WM_UNLOCK();
}

#else  /* avoid empty object files */

void EditBin_C(void);

#endif /* GUI_WINSUPPORT */
