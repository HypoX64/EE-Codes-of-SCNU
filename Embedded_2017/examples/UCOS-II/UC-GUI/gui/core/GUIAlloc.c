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
File        : GUIAlloc.C
Purpose     : emWin dynamic memory management
----------------------------------------------------------------------
Version-Date---Author-Explanation
----------------------------------------------------------------------
1.00    000107 RS     First version
----------------------------------------------------------------------
Known problems:
None.
----------------------------------------------------------------------
Open issues:
None.
----------------------------------------------------------------------
Todo:
Nothing.

*/


#include <stddef.h>           /* needed for definition of NULL */
#include <string.h>           /* for memcpy, memset */

#include "GUI_Protected.H"
#include "GUIDebug.h"

#if GUI_ALLOC_SIZE==0
  #error GUI_ALLOC_SIZE needs to be > 0 when using this module
#endif
/*
  *****************************************************************
  *
  *              Config defaults
  *
  *****************************************************************
*/

/* Permit automatic defragmentation when necessary */
#ifndef GUI_ALLOC_AUTDEFRAG
  #define GUI_ALLOC_AUTDEFRAG 1
#endif

#ifndef GUI_BLOCK_ALIGN
  #define GUI_BLOCK_ALIGN 2    /* 2 means 4 bytes, 1 means 2 bytes */
                              /* 1 can be used on 16-bit CPUs and
                                 CPUs which do not require aligned
                                 32-bit values (such as x86) */ 
#endif

#ifndef GUI_MAXBLOCKS
  #define GUI_MAXBLOCKS (2+GUI_ALLOC_SIZE/32)
#endif


/*
  *****************************************************************
  *
  *              Internal types and declarations
  *
  *****************************************************************
*/
#if GUI_ALLOC_SIZE <32767
  #define tALLOCINT I16
#else
  #define tALLOCINT I32
#endif

#if GUI_MAXBLOCKS >= 256
  #define HANDLE U16
#else
  #define HANDLE U8
#endif




typedef struct {
  tALLOCINT Off;       /* Offset of memory area */
  tALLOCINT Size;      /* usable size of allocated block */
  HANDLE Next;      /* next handle in linked list */
  HANDLE Prev;
} tBlock;

/****************************************************************
*
*              Static data
*
*****************************************************************
*/

GUI_HEAP GUI_Heap;       /* Public for debugging only */
static tBlock aBlock[GUI_MAXBLOCKS];

struct {
  int       NumUsedBlocks, NumFreeBlocks, NumFreeBlocksMin;        /* For statistical purposes only */
  tALLOCINT NumUsedBytes,  NumFreeBytes,  NumFreeBytesMin;
} GUI_ALLOC;

static char   IsInitialized =0;

/*
  ********************************************************************
  *
  *                 Macros for internal use
  *
  ********************************************************************
*/

#define Min(v0,v1) ((v0>v1) ? v1 : v0)
#define Max(v0,v1) ((v0>v1) ? v0 : v1)
#define ASSIGN_IF_LESS(v0,v1) if (v1<v0) v0=v1
#define HMEM2PTR(hMem) (void*)&GUI_Heap.abHeap[aBlock[hMem].Off]


/*
  ********************************************************************
  *
  *                    Internal routines
  *
  ********************************************************************
*/


/*
  *************************************************
  *
  *                 Size2LegalSize
  *
  *************************************************

  returns: Legal allocation size
*/

static int Size2LegalSize(int size) {
  return (size + ((1<<GUI_BLOCK_ALIGN)-1)) & ~((1<<GUI_BLOCK_ALIGN)-1);
}
  
/*
  *************************************************
  *
  *                 FindFreeHandle
  *
  *************************************************

  returns: Free handle
*/

static GUI_HMEM FindFreeHandle(void) {
  int i;
  for (i=1; i< GUI_MAXBLOCKS; i++) {
    if (aBlock[i].Size ==0)
	  return i;
  }
  GUI_DEBUG_ERROROUT1("Insufficient memory handles configured (GUI_MAXBLOCKS == %d (See GUIConf.h))", GUI_MAXBLOCKS);
  return GUI_HMEM_NULL;
}


/*
  *************************************************
  *
  *               Find hole in heap area
  *
  *************************************************

  returns: Offset to the memory hole (if available)
           -1 if not available
*/
static GUI_HMEM FindHole(int Size) {
  int i, iNext;
  for (i=0; (iNext = aBlock[i].Next) != 0; i = iNext) {
    int NumFreeBytes = aBlock[iNext].Off- (aBlock[i].Off+aBlock[i].Size);
    if (NumFreeBytes>=Size)
      return i;
  }
/* Check last block */
  if (GUI_ALLOC_SIZE - (aBlock[i].Off+aBlock[i].Size) >= Size)
    return i;
  return -1;
}

/*
  *************************************************
  *
  *             Create hole in heap area
  *
  *************************************************

  returns: Offset to the memory hole (if available)
           -1 if not available
*/
static GUI_HMEM CreateHole(int Size) {
  int i, iNext;
  int r = -1;
  for (i=0; (iNext =aBlock[i].Next) !=0; i= iNext) {
    int NumFreeBytes = aBlock[iNext].Off- (aBlock[i].Off+aBlock[i].Size);
    if (NumFreeBytes < Size) {
      int NumBytesBeforeBlock = aBlock[iNext].Off - (aBlock[i].Off+aBlock[i].Size);
      if (NumBytesBeforeBlock) {
        U8* pData = &GUI_Heap.abHeap[aBlock[iNext].Off];
        memmove(pData-NumBytesBeforeBlock, pData, aBlock[iNext].Size);
        aBlock[iNext].Off -=NumBytesBeforeBlock;
      }
    }
  }
/* Check last block */
  if (GUI_ALLOC_SIZE - (aBlock[i].Off+aBlock[i].Size) >= Size)
    r = i;
  return r;
}

static void CheckInit(void) {
  if (!IsInitialized)
    GUI_ALLOC_Init();
}

/*
  ********************************************************************
  *
  *                  Exported routines
  *
  ********************************************************************
*/

void GUI_ALLOC_Init(void) {
  GUI_DEBUG_LOG("\nGUI_ALLOC_Init...");
  GUI_ALLOC.NumFreeBlocksMin = GUI_ALLOC.NumFreeBlocks = GUI_MAXBLOCKS-1;
  GUI_ALLOC.NumFreeBytesMin  = GUI_ALLOC.NumFreeBytes  = GUI_ALLOC_SIZE;
  GUI_ALLOC.NumUsedBlocks = 0;
  GUI_ALLOC.NumUsedBytes = 0;
  aBlock[0].Size = (1<<GUI_BLOCK_ALIGN);  /* occupy minimum for a block */
  aBlock[0].Off  = 0;
  aBlock[0].Next = 0;
  IsInitialized =1;
}

static GUI_HMEM _Alloc(int size) {
  GUI_HMEM hMemNew, hMemIns;
  CheckInit();
  size = Size2LegalSize(size);
  /* Check if memory is available at all ...*/
  if (size > GUI_ALLOC.NumFreeBytes) {
    GUI_DEBUG_WARN1("GUI_ALLOC_Alloc: Insufficient memory configured (Trying to alloc % bytes)", size);
    return 0;
  }
  /* Locate free handle */
  if ((hMemNew = FindFreeHandle()) == 0)
    return 0;
  /* Locate or Create hole of sufficient size */
  hMemIns = FindHole(size);
  #if GUI_ALLOC_AUTDEFRAG
    if (hMemIns == -1) {
      hMemIns = CreateHole(size);
    }
  #endif
/* Occupy hole */
  if (hMemIns==-1) {
    GUI_DEBUG_ERROROUT1("GUI_ALLOC_Alloc: Could not allocate %d bytes",size);
    return 0;
	}
  {
    int Off = aBlock[hMemIns].Off+aBlock[hMemIns].Size;
    int Next = aBlock[hMemIns].Next;
    aBlock[hMemNew].Size  = size;
    aBlock[hMemNew].Off   = Off;
    if ((aBlock[hMemNew].Next  = Next) >0) {
      aBlock[Next].Prev = hMemNew;  
    }
    aBlock[hMemNew].Prev  = hMemIns;
    aBlock[hMemIns].Next  = hMemNew;
  }
/* Keep track of number of blocks and av. memory */
  GUI_ALLOC.NumUsedBlocks++;
  GUI_ALLOC.NumFreeBlocks--;
  if (GUI_ALLOC.NumFreeBlocksMin > GUI_ALLOC.NumFreeBlocks) {
    GUI_ALLOC.NumFreeBlocksMin = GUI_ALLOC.NumFreeBlocks;
  }
  GUI_ALLOC.NumUsedBytes += size;
  GUI_ALLOC.NumFreeBytes -= size;
  if (GUI_ALLOC.NumFreeBytesMin > GUI_ALLOC.NumFreeBytes) {
    GUI_ALLOC.NumFreeBytesMin = GUI_ALLOC.NumFreeBytes;
  }
/* In order to be on the safe side, zeroinit ! */
  memset(HMEM2PTR(hMemNew), 0, size);
  return hMemNew;
}

GUI_HMEM GUI_ALLOC_Alloc(int size) {
  GUI_HMEM hMem;
 /* First make sure that init has been called */
  GUI_LOCK();
  GUI_DEBUG_LOG2("\nGUI_ALLOC_Alloc... requesting %d, %d avail", size, GUI_ALLOC.NumFreeBytes);
  hMem = _Alloc(size);
  GUI_DEBUG_LOG1("\nGUI_ALLOC_Alloc : Handle", hMem);
  GUI_UNLOCK();
  return hMem;
}

void GUI_ALLOC_Free(GUI_HMEM hMem) {
  int Size;
  if (hMem == GUI_HMEM_NULL)  /* Note: This is not an error, it is permitted */
    return;
  GUI_LOCK();
  GUI_DEBUG_LOG1("\nGUI_ALLOC_Free(%d)", hMem);
  /* Do some error checking ... */
  #if GUI_DEBUG_LEVEL>0
    /* Block not allocated ? */
    if (aBlock[hMem].Size==0) {
      GUI_DEBUG_ERROROUT("GUI_ALLOC_Free(): Invalid hMem");
      return;
    }
  #endif
  Size = aBlock[hMem].Size;
  #ifdef WIN32
    memset(&GUI_Heap.abHeap[aBlock[hMem].Off], 0xcc, Size);
  #endif
  GUI_ALLOC.NumFreeBytes += Size;
  GUI_ALLOC.NumUsedBytes -= Size;
  aBlock[hMem].Size = 0;
  {
    int Next = aBlock[hMem].Next;
    int Prev = aBlock[hMem].Prev;
    aBlock[Prev].Next = Next;
    if (Next)
      aBlock[Next].Prev = Prev;
  }  
  GUI_ALLOC.NumFreeBlocks++;
  GUI_ALLOC.NumUsedBlocks--;
  GUI_UNLOCK();
}

void*       GUI_ALLOC_h2p   (GUI_HMEM  hMem) {
  #if GUI_DEBUG_LEVEL>0
    if (!hMem) {
      GUI_DEBUG_ERROROUT("\n"__FILE__ " GUI_ALLOC_h2p: illegal argument (0 handle)");
      return 0;
    }
  #endif
  return HMEM2PTR(hMem);
}

void GUI_ALLOC_FreePtr(GUI_HMEM *ph) {
  GUI_LOCK();
  GUI_ALLOC_Free(*ph);
  *ph =0;
  GUI_UNLOCK();
}

/*
  ********************************************************************
  *
  *                  Exported info routines
  *
  ********************************************************************
*/

int GUI_GetUsedMem(void) {
  int NumUsedBytes=0;
  int i;
  GUI_LOCK();
  CheckInit();
  for (i=1; i; i = aBlock[i].Next) {
    NumUsedBytes += aBlock[i].Size;
  }
  GUI_UNLOCK();
  return NumUsedBytes;
}


int GUI_ALLOC_GetNumFreeBytes(void) {
  CheckInit();
  return GUI_ALLOC.NumFreeBytes;  
}
/*
  *************************************************
  *
  *       GetMaxSize
  *
  *************************************************

  Returns the biggest available blocksize
  (without relocation)

*/
int GUI_ALLOC_GetMaxSize(void) {
  int r=0;
  int NumFreeBytes;
  int i, iNext;
  GUI_LOCK();
  CheckInit();
  for (i=0; (iNext =aBlock[i].Next) !=0; i= iNext) {
    NumFreeBytes = aBlock[iNext].Off- (aBlock[i].Off+aBlock[i].Size);
    if (NumFreeBytes > r) {
      r = NumFreeBytes;
    }
  }
/* Check last block */
  NumFreeBytes = (GUI_ALLOC_SIZE - (aBlock[i].Off+aBlock[i].Size));
  if (NumFreeBytes > r) {
    r = NumFreeBytes;
  }
  GUI_UNLOCK();
  return r;
}

