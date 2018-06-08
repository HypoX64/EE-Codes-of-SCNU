/*
*********************************************************************************************************
*                                               uC/OS-II
*                                        The Real-Time Kernel
*
*                        (c) Copyright 1992-1998, Jean J. Labrosse, Plantation, FL
*                                          All Rights Reserved
*                        (c) Copyright ARM Limited 1999.  All rights reserved.
*
*                                          ARM Specific code
*
* File : OS_CPU.H
*********************************************************************************************************
*/

#ifdef  OS_CPU_GLOBALS
#define OS_CPU_EXT
#else
#define OS_CPU_EXT  extern
#endif

/*
*********************************************************************************************************
*                                              DATA TYPES
*                                         (Compiler Specific)
*********************************************************************************************************
*/

typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;                    /* Unsigned  8 bit quantity                           */
typedef signed   char  INT8S;                    /* Signed    8 bit quantity                           */
typedef unsigned int   INT16U;                   /* Unsigned 16 bit quantity                           */
typedef signed   int   INT16S;                   /* Signed   16 bit quantity                           */
typedef unsigned long  INT32U;                   /* Unsigned 32 bit quantity                           */
typedef signed   long  INT32S;                   /* Signed   32 bit quantity                           */
typedef float          FP32;                     /* Single precision floating point                    */
typedef double         FP64;                     /* Double precision floating point                    */

typedef unsigned int   OS_STK;                   /* Each stack entry is 16-bit wide                    */

#define BYTE           INT8S                     /* Define data types for backward compatibility ...   */
#define UBYTE          INT8U                     /* ... to uC/OS V1.xx.  Not actually needed for ...   */
#define WORD           INT16S                    /* ... uC/OS-II.                                      */
#define UWORD          INT16U
#define LONG           INT32S
#define ULONG          INT32U

/* 
*********************************************************************************************************
*                              ARM, various architectures
*
*********************************************************************************************************
*/
#define	OS_ENTER_CRITICAL()	ARMDisableInt()
#define	OS_EXIT_CRITICAL()	ARMEnableInt()

#define ARMDisableInt SET_IF
#define ARMEnableInt CLR_IF
/*
 * Definitions specific to ARM/uHAL
 */
#define	SVC32MODE	0x13

/* stack stuff */
#define OS_STK_GROWTH    1

/* angel takes up stack */
#define SEMIHOSTED_STACK_NEEDS 1024

/* idle task stack size (words) */
#ifdef SEMIHOSTED
#define OS_IDLE_STK_SIZE        (32+SEMIHOSTED_STACK_NEEDS)
#else
#define OS_IDLE_STK_SIZE        32
#endif

/*
 * Functions specific to uHAL
 */
/* defined in os_cpu_c.c */
extern void IrqStart(void);
extern void* IrqFinish(void);

extern void ARMTargetInit(void);
extern void ARMTargetStart(void);

/* defined in os_cpu_a.s */
extern void OS_TASK_SW(void);
extern void ARMDisableInt(void);
extern void ARMEnableInt(void);
