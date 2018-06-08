/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                        (c) Copyright 1992-1998, Jean J. Labrosse, Plantation, FL
*                                           All Rights Reserved
*
*                                           MASTER INCLUDE FILE
*********************************************************************************************************
*/

#ifndef __INCLUDES_H__

#define  __INCLUDES_H__

//****************CPU**************//
#include		"option.h"
#include		"2410lib.h"
#include    "os_cpu.h"
//****************OS***************//
#include    "os_cfg.h"
#include    "ucos_ii.h"
#include    "uhal.h"
/////////////////////////////////////////////////
#ifdef      EX3_GLOBALS
  #define     EX3_EXT
#else
  #define     EX3_EXT  extern
#endif

#ifdef SEMIHOSTED
	#define	STACKSIZE	(64+SEMIHOSTED_STACK_NEEDS)
#else
	#define	STACKSIZE	256
#endif

/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/

typedef struct {
    char    TaskName[30];
    INT16U  TaskCtr;
    INT16U  TaskExecTime;
    INT32U  TaskTotExecTime;
} TASK_USER_DATA;

/*
*********************************************************************************************************
*                                              VARIABLES
*********************************************************************************************************
*/

EX3_EXT  TASK_USER_DATA  TaskUserData[10];

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void   DispTaskStat(INT8U id);

/*
*********************************************************************************************************
*                                             Timer structure
*********************************************************************************************************
*/
typedef struct {
    INT8U   TmrEn;   // 是否可用
    INT8U   TmrCtr;  // 当前计数
    INT8U   TmrInit; // 初始计数
    void    (* TmrFunc)(INT8U );  
	INT8U   TmrArg;  // 参数
} OS_TMR;

/* timer status */
#define    OS_TMR_ENABLE    1
#define    OS_TMR_DISABLE   0

/* maxium timers */
#define    OS_MAX_TMRS   3

/* timer used function */
extern INT8U OSTmrInit(void);
extern INT8U OSCreateTimer(OS_TMR **tmr, void (* ImrFunc)(INT8U arg), INT8U TmrArg, INT8U Ticks, INT8U initStatus);
extern INT8U OSEnableTimer(OS_TMR *tmr);
extern INT8U OSDisableTimer(OS_TMR *tmr);
extern INT8U OSDeleteTimer(OS_TMR *tmr);

/* stepper driver */
#define STEP_SPEED_MIN  100
#define STEP_SPEED_MAX  1

#define STEP_MOTOR_ENABLE         1
#define STEP_MOTOR_DISABLE        0
#define STEP_MOTOR_CLOCKWISE      0        
#define STEP_MOTOR_ANTICLOCKWISE  1 

void DRVStepperControl(INT8U benable);
void DRVStepperSetDirect(INT8U direct);
void DRVStepperSetSpeed(INT8U speed);
void DRVStepperSpeedUp(void);
void DRVStepperSpeedDown(void);
void DRVStepperInit();
void DRVStepperPulse(void);

#endif // __INCLUDES_H__
