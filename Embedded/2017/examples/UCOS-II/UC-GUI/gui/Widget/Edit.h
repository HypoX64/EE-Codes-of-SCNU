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
File        : EDIT.H
Purpose     : EDIT include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef EDIT_H
#define EDIT_H

#include "WM.H"
#include "Dialog.h"      /* Req. for Create indirect data structure */

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Defaults for configuration switches
*
**********************************************************************

The following are defaults for config switches which affect the
interface specified in this module
*/

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

/************************************************************
*
*       States
*/

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef WM_HMEM EDIT_Handle;

/*
      *************************************************************
      *                                                           *
      *                 Create function(s)                        *
      *                                                           *
      *                   (Constructors)                          *
      *                                                           *
      *************************************************************

*/
/* Note: the parameters to a create function may vary.
         Some widgets may have multiple create functions */


EDIT_Handle EDIT_Create        (int x0, int y0, int xsize, int ysize, int ID, int MaxLen, int Flags);
EDIT_Handle EDIT_CreateAsChild (int x0, int y0, int xsize, int ysize, WM_HWIN hParent, int Id, int Flags, int MaxLen);
EDIT_Handle EDIT_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* pCallback);

/*
      *************************************************************
      *                                                           *
      *                 Standard member functions                 *
      *                                                           *
      *************************************************************
*/

#define EDIT_EnableMemdev(hObj)  WM_EnableMemdev(hObj)
#define EDIT_DisableMemdev(hObj) WM_DisableMemdev(hObj)
#define EDIT_Delete(hObj)        WM_DeleteWindow(hObj)
#define EDIT_Paint(hObj)         WM_Paint(hObj)
#define EDIT_Invalidate(hObj)    WM_InvalidateWindow(hObj)

/*
      *************************************************************
      *                                                           *
      *           Individual member functions                     *
      *                                                           *
      *************************************************************

*/

/* Methods changing preferences */
void EDIT_SetDefaultFont(const GUI_FONT* pFont);
void EDIT_SetDefaultTextAlign(int Align);

/* Query preferences */
const GUI_FONT* EDIT_GetDefaultFont(void);

/* Methods changing properties */
void EDIT_SetText     (EDIT_Handle hObj, const char* s);
void EDIT_SetBkColor  (EDIT_Handle hObj, int Index, GUI_COLOR color);
void EDIT_SetTextColor(EDIT_Handle hObj, int Index, GUI_COLOR color);
void EDIT_SetFont     (EDIT_Handle hObj, const GUI_FONT* pfont);
void EDIT_AddKey      (EDIT_Handle hObj, int Key);
void EDIT_SetTextAlign(EDIT_Handle hObj, int Align);
void EDIT_SetCursor   (EDIT_Handle hObj);
void EDIT_ClearCursor (EDIT_Handle hObj);
void EDIT_SetMaxLen   (EDIT_Handle hObj, int MaxLen);

/* Get/Set user input */
void EDIT_GetText (EDIT_Handle hObj, char* sDest, int MaxLen);
I32  EDIT_GetValue(EDIT_Handle hObj);
void EDIT_SetValue(EDIT_Handle hObj, I32 Value);

/*********************************************************************
*
*             Routines for editing values
*
**********************************************************************
*/

void  EDIT_SetHexMode(EDIT_Handle hEdit, U32 Value, U32 Min, U32 Max);
void  EDIT_SetBinMode(EDIT_Handle hEdit, U32 Value, U32 Min, U32 Max);
void  EDIT_SetDecMode(EDIT_Handle hEdit, I32 Value, I32 Min, I32 Max, int Shift, U8 Flags);
void  EDIT_SetFloatMode(EDIT_Handle hEdit, float Value, float Min, float Max, int Shift, U8 Flags);

U32   GUI_EditHex(U32 Value, U32 Min, U32 Max, int Len, int xsize);
U32   GUI_EditBin(U32 Value, U32 Min, U32 Max, int Len, int xsize);
I32   GUI_EditDec(I32 Value, I32 Min, I32 Max, int Len, int xsize, int Shift, U8 Flags);
float GUI_EditFloat(float Value, float Min, float Max, int Len, int xsize, int Shift, U8 Flags);
void  GUI_EditString(char * pString, int Len, int xsize);


/*********************************************************************
*
*             Flags
*
**********************************************************************
*/

/* Signed or normal mode */
#define GUI_EDIT_NORMAL 0
#define GUI_EDIT_SIGNED 1

/* Edit modes */
#define GUI_EDIT_MODE_INSERT    0
#define GUI_EDIT_MODE_OVERWRITE 1

#endif   /* GUI_WINSUPPORT */
#endif   /* EDIT_H */
