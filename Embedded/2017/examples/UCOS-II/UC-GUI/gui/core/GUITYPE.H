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
File        : GUIType.H
Purpose     : Include file define the types used for GUI
---------------------------END-OF-HEADER------------------------------

Attention : Do not modify this file ! If you do, you will not
            be able do update to a later version of emWin !

*/

#ifndef  GUITYPE_H_INCLUDED
#define  GUITYPE_H_INCLUDED

#include "LCD.H"

/*      *************************************************************
        *                                                           *
        *                Simple types                               *
        *                                                           *
        *************************************************************
*/

typedef const char *  GUI_ConstString;
typedef GUI_ConstString GUI_aConstString[];


/*      *************************************************************
        *                                                           *
        *                Structures                                 *
        *                                                           *
        *************************************************************
*/

typedef LCD_COLOR       GUI_COLOR;
typedef LCD_LOGPALETTE  GUI_LOGPALETTE;
typedef LCD_DRAWMODE    GUI_DRAWMODE;
typedef LCD_RECT        GUI_RECT;

typedef struct {
  U16P XSize;
  U16P YSize;
  U16P BytesPerLine;
  U16P BitsPerPixel;
  const U8* pData;
  const GUI_LOGPALETTE* pPal;
  tfDrawSpecialBitmap* pfDraw;
} GUI_BITMAP;

/* This structure may not be changed because the data that it
   expects is read in binary form (via any kind of interface,
   at runtime).
   This structure should therefor not be changed.
*/
typedef struct {
  U16 ID;           /* Version 1.00 => 100*/
  U16 Version;
  U16 XSize;
  U16 YSize;
  U16 BytesPerLine;
  U16 BitsPerPixel;
  U16 NumColors;
  U16 HasTrans;
} GUI_BITMAP_STREAM;

/*
      ****************************************
      *                                      *
      *      FONT structures (new in V1.10)  *
      *                                      *
      ****************************************
*/

/* Translation list. Translates a character code into up to 2
   indices of images to display on top of each other;
   'á' -> index('a'), index('´') */
typedef struct {
  I16P c0;
  I16P c1;
} GUI_FONT_TRANSLIST;

typedef struct {
  U16P FirstChar;
  U16P LastChar;
  const GUI_FONT_TRANSLIST* pList;
} GUI_FONT_TRANSINFO;

typedef struct {
  U8 XSize;
  U8 XDist;
  U8 BytesPerLine;
  void* pData;
} GUI_CHARINFO;

typedef struct {
  U16P First;         /* first character               */
  U16P Last;          /* last character                */
  const GUI_CHARINFO* paCharInfo;    /* address of first character    */
  void* pNext;        /* pointer to next */
} GUI_FONT_PROP;

typedef struct {
  void* pData;
  void* pTransData;
  const GUI_FONT_TRANSINFO * pTrans;
  U16P FirstChar;
  U16P LastChar;
  U8 XSize;
  U8 XDist;
  U8 BytesPerLine;
} GUI_FONT_MONO;


typedef struct {
  U16P First;         /* first character               */
  U16P Last;          /* last character                */
  const GUI_CHARINFO* paCharInfo;    /* address of first character    */
  void* pNext;        /* pointer to next */
} GUI_FONT_INFO;

/*
      ****************************************
      *                                      *
      *      FONT info structure             *
      *                                      *
      ****************************************

This structure is used when retrieving information about a font.
It is designed for future expansion without incompatibilities.
*/
typedef struct {
  U16 Flags;
} GUI_FONTINFO;

#define GUI_FONTINFO_FLAG_PROP (1<<0)    /* Is proportional */
#define GUI_FONTINFO_FLAG_MONO (1<<1)    /* Is monospaced */
#define GUI_FONTINFO_FLAG_AA   (1<<2)    /* Is an antialiased font */
#define GUI_FONTINFO_FLAG_AA2  (1<<3)    /* Is an antialiased font, 2bpp */
#define GUI_FONTINFO_FLAG_AA4  (1<<4)    /* Is an antialiased font, 4bpp */


/**********************************************************************
*
*                 FONT Encoding
*
***********************************************************************
*/

typedef int  tGUI_GetLineDistX(const char *s, int Len);
typedef int  tGUI_GetLineLen(const char *s, int MaxLen);
typedef void tGL_DispLine(const char *s, int Len);

typedef struct {
  tGUI_GetLineDistX*          pfGetLineDistX;
  tGUI_GetLineLen*            pfGetLineLen;
  tGL_DispLine*               pfDispLine;
} tGUI_ENC_APIList;

extern tGUI_ENC_APIList* GUI_pafENCODE;
extern tGUI_ENC_APIList GUI_ENC_APIList_SJIS;


/*
      ****************************************
      *                                      *
      *      FONT methods                    *
      *                                      *
      ****************************************

The parameter to the methods called pFont should be of type
GUI_FONT, but unfortunately a lot of compilers can not handle
forward declarations right ...
So it ends up to be a void pointer.
*/

typedef void GUI_DISPCHAR(U16 c);
typedef int  GUI_GETCHARDISTX(U16P c);
typedef void GUI_GETFONTINFO(void *pFont, GUI_FONTINFO* pfi);
typedef char GUI_ISINFONT   (void *pFont, U16 c);

#define DECLARE_FONT(Type)                        \
void GUI##Type##_DispChar(U16P c);     \
int  GUI##Type##_GetCharDistX(U16P c);            \
void GUI##Type##_GetFontInfo(void* pFont, GUI_FONTINFO* pfi); \
char GUI##Type##_IsInFont   (void* pFont, U16 c)

/* MONO: Monospaced fonts */
DECLARE_FONT(MONO);
#define GUI_FONTTYPE_MONO       \
  GUIMONO_DispChar,             \
	GUIMONO_GetCharDistX,         \
	GUIMONO_GetFontInfo,          \
	GUIMONO_IsInFont,             \
  (tGUI_ENC_APIList*)0

/* PROP: Proportional fonts */
DECLARE_FONT(PROP);
#define GUI_FONTTYPE_PROP       \
  GUIPROP_DispChar,             \
	GUIPROP_GetCharDistX,         \
	GUIPROP_GetFontInfo,          \
	GUIPROP_IsInFont,             \
  (tGUI_ENC_APIList*)0

/* PROP: Proportional fonts SJIS */
DECLARE_FONT(PROP);
#define GUI_FONTTYPE_PROP_SJIS  \
  GUIPROP_DispChar,             \
	GUIPROP_GetCharDistX,         \
	GUIPROP_GetFontInfo,          \
	GUIPROP_IsInFont,             \
  &GUI_ENC_APIList_SJIS

/* PROPAA: Proportional, antialiased fonts */
DECLARE_FONT(PROPAA);
#define GUI_FONTTYPE_PROPAA       \
  GUIPROPAA_DispChar,             \
	GUIPROPAA_GetCharDistX,         \
	GUIPROPAA_GetFontInfo,          \
	GUIPROPAA_IsInFont,             \
  (tGUI_ENC_APIList*)0

/* PROPAA: Proportional, antialiased fonts, 2bpp */
DECLARE_FONT(PROP_AA2);
#define GUI_FONTTYPE_PROP_AA2       \
  GUIPROP_AA2_DispChar,             \
	GUIPROP_AA2_GetCharDistX,         \
	GUIPROP_AA2_GetFontInfo,          \
	GUIPROP_AA2_IsInFont,             \
  (tGUI_ENC_APIList*)0

/* PROPAA: Proportional, antialiased fonts, 2bpp, SJIS encoding */
DECLARE_FONT(PROP_AA2);
#define GUI_FONTTYPE_PROP_AA2_SJIS  \
  GUIPROP_AA2_DispChar,             \
	GUIPROP_AA2_GetCharDistX,         \
	GUIPROP_AA2_GetFontInfo,          \
	GUIPROP_AA2_IsInFont,             \
  GUI_ENCODE_SJIS

/* PROPAA: Proportional, antialiased fonts, 4bpp */
DECLARE_FONT(PROP_AA4);
#define GUI_FONTTYPE_PROP_AA4       \
  GUIPROP_AA4_DispChar,             \
	GUIPROP_AA4_GetCharDistX,         \
	GUIPROP_AA4_GetFontInfo,          \
	GUIPROP_AA4_IsInFont,             \
  (tGUI_ENC_APIList*)0

/* PROPAA: Proportional, antialiased fonts, 4bpp, SJIS encoding */
DECLARE_FONT(PROP_AA4);
#define GUI_FONTTYPE_PROP_AA4_SJIS  \
  GUIPROP_AA4_DispChar,             \
	GUIPROP_AA4_GetCharDistX,         \
	GUIPROP_AA4_GetFontInfo,          \
	GUIPROP_AA4_IsInFont,             \
  GUI_ENCODE_SJIS

typedef struct {
  GUI_DISPCHAR*     pfDispChar; 
  GUI_GETCHARDISTX* pfGetCharDistX; 
  GUI_GETFONTINFO*  pfGetFontInfo; 
  GUI_ISINFONT*     pfIsInFont;
  tGUI_ENC_APIList* pafEncode;
  U8 YSize;
  U8 YDist;
  U8 XMag;
  U8 YMag;
  union {
    void  *pFontData;
    const GUI_FONT_MONO* pMono;
    const GUI_FONT_PROP* pProp;
  } p;
  U8 Baseline;
} GUI_FONT;


/*
      ****************************************
      *                                      *
      *      Window flag definitions         *
      *                                      *
      ****************************************
*/
#define GUI_WINHANDLE_CUR         255
#define GUI_WINHANDLE_BACKGROUND  0 
#define GUI_WINHANDLE2PTR(hWin) ((hWin==GUI_WINHANDLE_CUR) ? pAWin : &Windows[hWin])


/*
      *********************************
      *                               *
      *      Typedefs                 *
      *                               *
      *********************************
*/

#define GUI_HANDLE int
/* Define window handle */
#define GUI_HWIN            I16P
#define GUI_HWIN_NULL       0
/* WM currently always uses static memory */
#define     GUI_HMEM I16P
#define     GUI_HMEM_NULL (0)


#endif  /* GUITYPE_H_INCLUDED */

