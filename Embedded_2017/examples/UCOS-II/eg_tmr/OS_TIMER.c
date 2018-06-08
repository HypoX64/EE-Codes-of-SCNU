/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                          (c) Copyright 1992-2001, Jean J. Labrosse, Weston, FL
*                                           All Rights Reserved
*
* File : OS_TIMER.C
* By   : cooljet
*********************************************************************************************************
*/
#include	"Includes.h"               /* uC/OS interface */
#include    "option.h"
#include    "2410lib.h"
#include    "uhal.h"

#define          OS_TMR_ERR                88
#define          TMR_STACK_SIZE           256
#define          OS_TMR_PRIO                4             /* hightest prior */

OS_TMR           OSTmrCB[OS_MAX_TMRS];                    /* array to save timers */

INT32U           StackTmr[TMR_STACK_SIZE];

// Function name	: TaskTmr
// Description	    : 定时器任务
// Return type		: void 
// Argument         : void *i
void OSTaskTmr(void *i)
{
    INT8S loopcnt;

    for (;;)
    {
        /* delay some times */
		OSTimeDly(1);

		/* search the timer */
		for(loopcnt = 0; loopcnt < OS_MAX_TMRS; loopcnt++)
		{
			if(OSTmrCB[loopcnt].TmrEn == OS_TMR_ENABLE)
			{
				OS_ENTER_CRITICAL();
				
				// increase the counter
				OSTmrCB[loopcnt].TmrCtr --;
				if(OSTmrCB[loopcnt].TmrCtr == 0)
				{
					// timer is expired
					OSTmrCB[loopcnt].TmrCtr = OSTmrCB[loopcnt].TmrInit;
					OS_EXIT_CRITICAL();

					// do expired function
					if(OSTmrCB[loopcnt].TmrFunc != 0)
					{
						OSTmrCB[loopcnt].TmrFunc(OSTmrCB[loopcnt].TmrArg);
					}
				}else
				{
					OS_EXIT_CRITICAL();
				}
			}
		}
    }
}

// Function name	: TmrInit
// Description	    : 定时器初始化函数
// Return type		: INT8U 
INT8U OSTmrInit()
{
	INT8S loopcnt;
	INT8U status;
	
	/* init timer handler */
	for(loopcnt = 0; loopcnt < OS_MAX_TMRS; loopcnt++)
	{
		OSTmrCB[loopcnt].TmrEn   = OS_TMR_DISABLE;
		OSTmrCB[loopcnt].TmrFunc = 0;
	}

	/* create task */
	status = OSTaskCreate(OSTaskTmr, 0, (OS_STK *)&StackTmr[TMR_STACK_SIZE], OS_TMR_PRIO);

	return status;
}
// Function name	: CreateTimer
// Description	    : 创建定时器
// Return type		: INT8U 
// Argument         : OS_TMR **tmr            : 定时器句柄
// Argument         : (* ImrFunc)(UINT8u arg) : 超时函数
// Argument         : INT8U TmrArg            : 函数参数
// Argument         : INT8U Ticks             : 定时器ticks数
// Argument         : INT8U initStatus        : 初始状态
INT8U OSCreateTimer(OS_TMR **tmr, void (* TmrFunc)(INT8U arg), INT8U TmrArg, INT8U Ticks, INT8U initStatus)
{
	INT8S loopcnt;
	INT8U status = OS_TMR_ERR;
	
	*tmr = 0;

	/* Check parameters */
	if(TmrFunc == 0 || Ticks == 0 || (initStatus != OS_TMR_ENABLE && initStatus != OS_TMR_DISABLE))
		return OS_TMR_ERR;

	/* search timer handler */
	for(loopcnt = 0; loopcnt < OS_MAX_TMRS; loopcnt++)
	{
		if(OSTmrCB[loopcnt].TmrFunc == 0)
		{
			OS_ENTER_CRITICAL();

			// found a timer handler
			OSTmrCB[loopcnt].TmrEn   = initStatus;
			OSTmrCB[loopcnt].TmrFunc = TmrFunc;
			OSTmrCB[loopcnt].TmrArg  = TmrArg;
			OSTmrCB[loopcnt].TmrCtr  = OSTmrCB[loopcnt].TmrInit = Ticks;
			
			*tmr = &OSTmrCB[loopcnt];
			
			status = OS_NO_ERR;

			OS_EXIT_CRITICAL();
			break;
		}
	}
	
	return status;
}
// Function name	: EnableTimer
// Description	    : 使能定时器
// Return type		: INT8U 
// Argument         : OS_TMR *tmr : 定时器句柄
INT8U OSEnableTimer(OS_TMR *tmr)
{
	if(tmr != 0)
	{
		OS_ENTER_CRITICAL();
		tmr->TmrEn = OS_TMR_ENABLE;
		OS_EXIT_CRITICAL();

		return OS_NO_ERR;
	}else
	{
		return OS_TMR_ERR;
	}
}
// Function name	: DisableTimer
// Description	    : 关闭定时器
// Return type		: INT8U 
// Argument         : OS_TMR *tmr : 定时器句柄
INT8U OSDisableTimer(OS_TMR *tmr)
{
	if(tmr != 0)
	{
		OS_ENTER_CRITICAL();
		tmr->TmrEn = OS_TMR_DISABLE;
		OS_EXIT_CRITICAL();

		return OS_NO_ERR;
	}else
	{
		return OS_TMR_ERR;
	}
}
// Function name	: DeleteTimer
// Description	    : 删除定时器
// Return type		: INT8U 
// Argument         : OS_TMR *tmr : 定时器句柄
INT8U OSDeleteTimer(OS_TMR *tmr)
{
	if(tmr != 0)
	{
		OS_ENTER_CRITICAL();
		tmr->TmrEn   = OS_TMR_DISABLE;
		tmr->TmrFunc = 0;
		OS_EXIT_CRITICAL();

		return OS_NO_ERR;
	}else
	{
		return OS_TMR_ERR;
	}
}
