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
File        : WM.H
Purpose     : Windows manager include
----------------------------------------------------------------------
*/

#ifndef WM_H            /* Make sure we only include it once */
#ifndef GUI_H
  #include "GUI.H"      /* Needed because of typedefs only */
#endif

#ifndef WM_H		        /* Make sure circular reference do not lead
                           to multiple-inclusion problem */
#define WM_H

/* Make sure we actually have configured windows. If we have not,
  there is no point for a windows manager and it will therefor not
  generate any code !
*/

#if GUI_WINSUPPORT

/*
      *************************************************************
      *                                                           *
      *                 Defaults for configuration switches       *
      *                                                           *
      *************************************************************
*/

#ifndef WM_ASSERT
  #define WM_ASSERT(expr) GUI_DEBUG_ASSERT(expr)
#endif

#ifndef WM_RESULT
  #define WM_RESULT void
#endif

#ifndef WM_SUPPORT_TOUCH
  #define WM_SUPPORT_TOUCH        GUI_SUPPORT_TOUCH
#endif

#ifndef WM_SUPPORT_OBSTRUCT
  #define WM_SUPPORT_OBSTRUCT 1
#endif

#ifndef WM_COMPATIBLE_MODE
  #define WM_COMPATIBLE_MODE 1
#endif

/*
      *************************************************************
      *                                                           *
      *               Configuration check                         *
      *                                                           *
      *************************************************************
*/

/*
      *************************************************************
      *                                                           *
      *               Locking macros                              *
      *                                                           *
      *************************************************************
  For performance reasons, the windows manager user the same locking mechanisms
  as the GUI layer. The advantage is that wiht a single call to GUI_LOCK both
  the graphic level and the WM level are covered.
*/

#define WM_LOCK()   GUI_LOCK()
#define WM_UNLOCK() GUI_UNLOCK()

/* Memory allocation locking is seperate from Windows managers in
   order to be able to use different resource semaphores. Per
	 default, the same one is used.
*/

#ifndef WMALLOC_LOCK
  #define WMALLOC_LOCK()   WM_LOCK()
  #define WMALLOC_UNLOCK() WM_UNLOCK()
#endif

/************************************************************
*
*          Public data (just for inline functions
*                       in form of macros)
*
*************************************************************
*/

extern U8 WM_IsActive;


/************************************************************
*
*          Data types
*
*************************************************************
*/

typedef struct {
  int Key, PressedCnt;
} WM_KEY_INFO;

typedef struct {
  int NumItems, v, PageSize;
} WM_SCROLL_STATE;


/*
      *************************************************************
      *                                                           *
      *               Function replacement macros                 *
      *                                                           *
      *************************************************************
*/

#define WM_GetIsActive()          WM_IsActive
#define WM_GetNumWindows()        WM__NumWindows
#define WM_GetNumInvalidWindows() WM__NumInvalidWindows

/*********************************************************************
*
*               Messages Ids

The following is the list of windows messages.
*/

#ifndef _WINUSER_              /* Conflicts with winuser.h ... */

#define WM_PAINT               1 /* Repaint window (because content is (partially) invalid */
#define WM_COVER               2 /* Window has been partially covered. Normally, there is no reaction to this event. */
#define WM_CREATE              3 /* The first message received, right after client has actually been created */
#define WM_DELETE              4 /* Delete (Destroy) command: This tells the client to free its data strutures since the window
                                    it is associates with no longer exists.*/
#define WM_SIZE                6 /* Is sent to a window after its size has changed */
#define WM_MOVE                7 /* window has been moved */
#define WM_SHOW                8 /* windows has just received the show command */
#define WM_HIDE                9 /* windows has just received the hide command */
#define WM_FGND               10 /* window has been made top of window stack */
#define WM_BGND               11 /* window has just been put to bottom of stack */
#define WM_TOUCH              12 /* touch screen message */
#define WM_KEY                13 /* Key has been pressed */

#define WM_GETCLIENTRECT      100      /* get client rectangle in window coordinates*/
#define WM_GETCLIENTRECT_ABS  101      /* get client rectangle in absolute coordinates*/
#define WM_GET_INSIDE_RECT    102      /* get inside rectangle: client rectangle minus pixels lost to effect */
#define WM_GETORG             104
#define WM_GET_ID             105      /* Get id of widget */
#define WM_GET_CLIENT_WINDOW  106      /* Get window handle of client window. Default is the same as window */
#define WM_CAPTURE_RELEASED   107      /* Let window know that mouse capture is over */

#define WM_INIT_DIALOG        109      /* Inform dialog that it is ready for init */
#define WM_SET_FOCUS          110      /* Inform window that it has gotten or lost the focus */
#define WM_GET_ACCEPT_FOCUS   111      /* Find out if window can accept the focus */
#define WM_GET_FOCUSSED_CHILD 112      /* Which child currently has the focus */
#define WM_GET_HAS_FOCUS      113      /* Does this window have the focus ? */
#define WM_GET_BKCOLOR        114      /* Return back ground color (only frame window and similar) */
#define WM_SET_ENABLE         115      /* Enable or disable widget */
#define WM_GET_SCROLL_STATE   116      /* Query state of scroll bar */

#define WM_ADD_SCROLLBAR      118      /* Scroller added */
#define WM_SET_SCROLL_STATE   119      /* Set scroll info ... only effective for scrollbars */

#define WM_NOTIFY_CHILD_HAS_FOCUS 120
#define WM_NOTIFY_PARENT      121

#define WM_USER              200      /* Reserved for user messages */

#endif


/*********************************************************************
*
*               Notification codes

The following is the list of notification codes send
with the WM_NOTIFY message
*/
#define WM_NOTIFICATION_CLICKED       1
#define WM_NOTIFICATION_RELEASED      2
#define WM_NOTIFICATION_MOVED_OUT     3
#define WM_NOTIFICATION_SEL_CHANGED   4
#define WM_NOTIFICATION_VALUE_CHANGED 5

/*
        *******************************************************************
        *                                                                 *
        *              Memory management                                  *
        *                                                                 *
        *******************************************************************
*/

#define WM_FREE(h)     GUI_ALLOC_FREE(h)
#define WM_ALLOC(h)    GUI_ALLOC_ALLOC(h)
#define WM_HWIN        GUI_HWIN
#define WM_HWIN_NULL   GUI_HWIN_NULL
#define WM_HMEM        GUI_HMEM
#define WM_HMEM2Ptr    GUI_ALLOC_H2P
#define WM_FREEPTR(ph) GUI_ALLOC_FreePtr(ph)
#define WM_HMEM_NULL   GUI_HMEM_NULL
#define WM_HBKWIN      1                         /* Handle of background window */

/*
        *******************************************************************
        *                                                                 *
        *           Windows manager types                                 *
        *                                                                 *
        *******************************************************************
*/

/* Windows create flags. These flags can be passed to the create window
   function as flag-parameter. The flags are combinable using the
   binary or operator.
*/

#define WM_CF_HASTRANS   (1<<0)  /* Has transparency. Needs to be defined
                                    for windows which do not fill the entire
                                    section of their (client) rectangle. */
#define WM_CF_HIDE       (0<<1)  /* Hide window after creation (default !) */
#define WM_CF_SHOW       (1<<1)  /* Show window after creation */
#define WM_CF_FGND       (0<<2)  /* Put window in foreground after creation
                                    (default !) */
#define WM_CF_BGND       (1<<2)  /* Put window in background after creation */
#define WM_CF_MEMDEV     (1<<3)  /* Use memory device for redraws */
#define WM_CF_STAYONTOP  (1<<4)  /* Stay on top */
#define WM_CF_ACTIVATE   (1<<5)  /* If automatic activation upon creation of
                                    window is desired */

typedef struct {
  int MsgId;            /* type of message */
  WM_HWIN hWin;         /* Destination window */
  WM_HWIN hWinSrc;      /* Source window  */
  union {
    void* p;            /* Some messages need more info ... */
    int v;
    GUI_COLOR Color;
  } Data;
} WM_MESSAGE;

typedef void WM_CALLBACK( WM_MESSAGE* pMsg);

typedef struct WM_OBJ_struct WM_Obj;
struct WM_OBJ_struct {
  GUI_RECT Rect;        /* outer dimensions of window */
  GUI_RECT InvalidRect; /* invalid rectangle */
  WM_CALLBACK* cb;      /* ptr to notification callback */
  WM_HWIN hNextLin;     /* Next window in linear list */
  WM_HWIN hParent, hFirstChild, hNext;
  U16 Status;	          /* Some status flags */
};

/*
**********************************************************************
*
*              General control routines
*
**********************************************************************
*/

void WM_Activate  (void);
void WM_Deactivate(void);
void WM_Init      (void);
int  WM_Exec      (void);    /* Execute all jobs ... Return 0 if nothing was done. */
int  WM_Exec1     (void);    /* Execute one job  ... Return 0 if nothing was done. */
U16  WM_SetCreateFlags(U16 Flags);
void WM_SetCapture(WM_HWIN hObj, int AutoRelease);
void WM_ReleaseCapture(void);

/*********************************************************************
*
*           Window manager interface
*
**********************************************************************
*/

/* Create/delete windows */
WM_HWIN WM_CreateWindow           (int x0, int y0, 
                                   int xSize, int ySize,
                                   U16 Style, WM_CALLBACK* cb, int NumExtraBytes);
WM_HWIN WM_CreateWindowAsChild    (int x0, int y0, 
                                   int xSize, int ySize, 
                                   WM_HWIN hWinParent, 
                                   U16 Style, WM_CALLBACK* cb, int NumExtraBytes);
void WM_DeleteWindow              (WM_HWIN hWin);

/* Check validity */
int WM_IsWindow                   (WM_HWIN hWin);

/* Show/hide windows */
void WM_HideWindow                (WM_HWIN hWin);
void WM_ShowWindow                (WM_HWIN hWin);

/* Set/clear the has transparency flag */
void WM_SetHasTrans               (WM_HWIN hWin);
void WM_ClrHasTrans               (WM_HWIN hWin);
int  WM_GetHasTrans               (WM_HWIN hWin);

/* Invalidate/validate windows or rectangles */
void WM_InvalidateArea            (GUI_RECT* pRect);
void WM_InvalidateRect            (WM_HWIN hWin, const GUI_RECT*pRect);
void WM_InvalidateWindow          (WM_HWIN hWin);
void WM_ValidateRect              (WM_HWIN hWin, const GUI_RECT*pRect);
void WM_ValidateWindow            (WM_HWIN hWin);

/* Move/resize windows */
void WM_MoveWindow                (WM_HWIN hWin, int dx, int dy);
void WM_ResizeWindow              (WM_HWIN hWin, int XSize, int YSize);
void WM_MoveTo                    (WM_HWIN hWin, int x, int y);
void WM_SetSize                   (WM_HWIN hWin, int XSize, int YSize);

/* Set (new) callback function */
WM_CALLBACK* WM_SetCallback       (WM_HWIN Win, WM_CALLBACK* cb);

/* Get size/origin of a window */
void WM_GetClientRect             (GUI_RECT* pRect);
void WM_GetInsideRect             (WM_HWIN hWin, GUI_RECT* pRect);
void WM_GetWindowRect             (GUI_RECT* pRect);
int  WM_GetOrgX                   (void);
int  WM_GetOrgY                   (void);
int  WM_GetWindowOrgX             (WM_HWIN hWin);
int  WM_GetWindowOrgY             (WM_HWIN hWin);
int  WM_GetWindowSizeX            (WM_HWIN hWin);
int  WM_GetWindowSizeY            (WM_HWIN hWin);
WM_HWIN WM_GetFirstChild          (WM_HWIN hWin);
WM_HWIN WM_GetNextSibling         (WM_HWIN hWin);
WM_HWIN WM_GetParent              (WM_HWIN hWin);
int  WM_GetId                     (WM_HWIN hWin);
WM_HWIN WM_GetClientWindow        (WM_HWIN hObj);
GUI_COLOR WM_GetBkColor           (WM_HWIN hObj);

/* Change Z-Order of windows */
void WM_BringToBottom(WM_HWIN hWin);
void WM_BringToTop(WM_HWIN hWin);

GUI_COLOR WM_SetDesktopColor(GUI_COLOR Color);

/* Select window used for drawing operations */
WM_HWIN WM_SelectWindow           (WM_HWIN  hWin);
WM_HWIN WM_GetActiveWindow        (void);
void    WM_Paint                  (WM_HWIN hObj);

/* Get foreground/background windows */
WM_HWIN WM_GetDesktopWindow    (void);

/* Reduce clipping area of a window */
const GUI_RECT* WM_SetUserClipRect(const GUI_RECT* pRect);
void            WM_SetDefault     (void);

/* Use of memory devices */
void WM_EnableMemdev              (WM_HWIN hWin);
void WM_DisableMemdev             (WM_HWIN hWin);

int WM_OnKey(int Key, int Pressed);


/******************************************************************
*
*           Message related funcions
*
*******************************************************************
  Please note that some of these functions do not yet show up in the
  documentation, as they should not be required by application program.
*/

void      WM_NotifyParent         (WM_HWIN hWin, int Notification);
void      WM_SendMessage          (WM_HWIN hWin, WM_MESSAGE* p);
void      WM_DefaultProc          (WM_MESSAGE* pMsg);
int       WM_BroadcastMessage     (WM_MESSAGE* pMsg);
void      WM_SetScrollState       (WM_HWIN hWin, const WM_SCROLL_STATE* pState);
void      WM_SetEnableState       (WM_HWIN hItem, int State);
void      WM_SendToParent         (WM_HWIN hWin, WM_MESSAGE* pMsg);
int       WM_HasCaptured(WM_HWIN hWin);
int       WM_SetFocus(WM_HWIN hWin);
WM_HWIN   WM_GetFocussedChild(WM_HWIN hDialog);
WM_HWIN   WM_SetFocusOnNextChild(WM_HWIN hParent);     /* Set the focus to the next child */
WM_HWIN   WM_GetDialogItem(WM_HWIN hWin, int Id);
void      WM_EnableWindow (WM_HWIN hWin);
void      WM_DisableWindow(WM_HWIN hWin);
void      WM_GetScrollState(WM_HWIN hObj, WM_SCROLL_STATE* pScrollState);


/*********************************************************************
*
*           Misc routines
*
**********************************************************************

*/

int       WM_HandleHID   (void);
WM_HWIN   WM_Screen2hWin   (int x, int y);
int       WM__InitIVRSearch(const GUI_RECT* pMaxRect);
int       WM__GetNextIVR   (void);
int       WM__GetOrgX(void);
int       WM__GetOrgY(void);


/*
      *************************************************
      *                                               *
      *        Macros for lower levels                *
      *                                               *
      *************************************************

These are the core macro of this module. They make sure that the
windows manager is called an that we iterate over all the rect-
angles that thw windows manager has registered as visible
and invalid (IVR, for InValid Rectangle). Using these macros makes
the code in the actual routines easier to read.
*/

#define WM_ITERATE_START(pRect)                   \
  {                                               \
    GUI_LOCK();                                   \
    if (WM__InitIVRSearch(pRect))                 \
      do {

#define WM_ITERATE_END()                          \
    } while (WM__GetNextIVR());                   \
    GUI_UNLOCK();                                 \
  }

#define WM_ADDORGX(x)    x += WM__GetOrgX()
#define WM_ADDORGY(y)    y += WM__GetOrgY()
#define WM_ADDORG(x0,y0) WM_ADDORGX(x0); WM_ADDORGY(y0)
#define WM_SUBORGX(x)    x-=WM__GetOrgX()
#define WM_SUBORGY(y)    y-=WM__GetOrgY()
#define WM_SUBORG(x0,y0) WM_SUBORGX(x0); WM_SUBORGY(y0)

/*
      *************************************************
      *                                               *
      *  Macros for compatibility with older versions *
      *                                               *
      *************************************************
*/

#if WM_COMPATIBLE_MODE
  #define HBWIN             WM_HWIN
  #define HBWIN_NULL        WM_HWIN_NULL

  #define WM_HideWin        WM_HideWindow
  #define WM_ShowWin        WM_ShowWindow
  #define WM_GetKey         GUI_GetKey
  #define WM_WaitKey        GUI_WaitKey

  #define WM_ExecIdle       WM_Exec
  #define WM_ExecIdle1      WM_Exec1

  #define WM_HideBWin       WM_HideWindow
  #define WM_ShowBWin       WM_ShowWindow
  #define WM_DeleteBWin     WM_DeleteWindow
  #define WM_Invalidate     WM_InvalidateWindow
  #define WM_InvalidateBWin WM_InvalidateWindow
  #define WM_MoveBWin       WM_MoveWindow
  #define WM_ResizeBWin     WM_ResizeWindow
  #define WM_GetWinRect     WM_GetWindowRect
  #define WM_GetWinOrgX     WM_GetWindowOrgX
  #define WM_GetWinOrgY     WM_GetWindowOrgY
  #define WM_GetWinSizeX    WM_GetWindowSizeX
  #define WM_GetWinSizeY    WM_GetWindowSizeY
  #define WM_GetXSize       WM_GetWindowSizeX
  #define WM_GetYSize       WM_GetWindowSizeY
  #define WM_SetFGndBWin    WM_SetForegroundWindow
  #define WM_SetBGndBWin    WM_SetBackgroundWindow
  #define WM_SelWin         WM_SelectWindow
  #define WM_SetActiveBWin  WM_SelectWindow
  #define WM_GetActiveBWin  WM_GetActiveWindow
  #define WM_GetBGndBWin    WM_GetDesktopWindow
  #define WM_GetBackgroundWindow  WM_GetDesktopWindow
  #define WM_GetFGndBWin            0
  #define WM_GetForegroundWindow    0
  #define WM_SetForegroundWindow    WM_BringToTop
  #define WM_SetUserClipArea WM_SetUserClipRect

  #define WM_CreateBWin(x0,y0,xsize,ysize, Style,cb) WM_CreateWindow(x0,y0,xsize,ysize, Style,cb, 0)

  #define WM_Start()
  #define WM_Stop()
  #define WM_SetBkWindowColor(Color)  WM_SetDesktopColor(Color)

#endif

/*
  *****************************************************************
  *
  *              Internal types and declarations
  *
  *****************************************************************

  The following could be placed in a file of its own as it is not
  used outside of the window manager

*/
/* Basic Windows status flags.
   For module-internally use only !
*/
#define WM_SF_HASTRANS    (1<<0)
#define WM_SF_INVALID     (1<<1)
#define WM_SF_INUSE       (1<<2)    /* mark entry in array as used */
#define WM_SF_MEMDEV      (1<<3)
#define WM_SF_STAYONTOP   WM_CF_STAYONTOP
#define WM_SF_ISVIS       (1<<7)    /* Is visible flag */

#define WM_HANDLE2PTR(hWin) ((WM_Obj*)WM_HMEM2Ptr(hWin))    /* older form ... to be eliminated */
#define WM_H2P(hWin)        ((WM_Obj*)WM_HMEM2Ptr(hWin))

/*
  *****************************************************************
  *
  *              WM_ module internal data
  *
  *****************************************************************
*/
#ifdef WM_C
  #define EXTERN
#else
  #define EXTERN extern
#endif

EXTERN U16     WM__NumWindows;
EXTERN U16     WM__NumInvalidWindows;
EXTERN WM_HWIN WM__FirstWin;

#undef EXTERN

#endif   /* GUI_WINSUPPORT */
#endif   /* WM_H */
#endif   /* WM_H */
