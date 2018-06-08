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
File        : MARQUEE.H
Purpose     : MARQUEE include
----------------------------------------------------------------------
Version-Date---Author-Explanation
----------------------------------------------------------------------
0.00    --ALPHA--
----------------------------------------------------------------------
Open items:
None
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef MARQUEE_H
#define MARQUEE_H

#include "WM.H"

#if GUI_WINSUPPORT
/*
      *************************************************************
      *                                                           *
      *                 Defaults for configuration switches       *
      *                                                           *
      *************************************************************

*/
/* Default for ... */


/*
      *************************************************************
      *                                                           *
      *                         Types                             *
      *                                                           *
      *************************************************************

*/
typedef WM_HMEM MARQUEE_Handle;

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


MARQUEE_Handle MARQUEE_Create( int x0, int y0,
                             int xsize, int ysize, 
                             int Flags);

/*
      *************************************************************
      *                                                           *
      *                 Standard member functions                 *
      *                                                           *
      *************************************************************
*/

#define MARQUEE_EnableMemdev(hObj)  WM_EnableMemdev(hObj)
#define MARQUEE_DisableMemdev(hObj) WM_DisableMemdev(hObj)
#define MARQUEE_Delete(hObj)        WM_DeleteWindow(hObj)
#define MARQUEE_Paint(hObj)         WM_Paint(hObj)

/*
      *************************************************************
      *                                                           *
      *                 Member functions                          *
      *                                                           *
      *************************************************************

*/

/* Methods changing properties */
void         MARQUEE_SetText     (MARQUEE_Handle hObj, const char* s);


#endif   /* MARQUEE_H */
#endif   /* MARQUEE_H */
