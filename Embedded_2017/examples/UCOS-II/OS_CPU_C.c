#define  OS_CPU_GLOBALS
#include "includes.h"

/*
*********************************************************************************************************
*                                        INITIALIZE A TASK'S STACK
*
* Description: This function is called by either OSTaskCreate() or OSTaskCreateExt() to initialize the
*              stack frame of the task being created.  This function is highly processor specific.
*
* Arguments  : task          is a pointer to the task code
*
*              pdata         is a pointer to a user supplied data area that will be passed to the task
*                            when the task first executes.
*
*              ptos          is a pointer to the top of stack.  It is assumed that 'ptos' points to
*                            a 'free' entry on the task stack.  If OS_STK_GROWTH is set to 1 then 
*                            'ptos' will contain the HIGHEST valid address of the stack.  Similarly, if
*                            OS_STK_GROWTH is set to 0, the 'ptos' will contains the LOWEST valid address
*                            of the stack.
*
*              opt           specifies options that can be used to alter the behavior of OSTaskStkInit().
*                            (see uCOS_II.H for OS_TASK_OPT_???).
*
* Returns    : Always returns the location of the new top-of-stack' once the processor registers have
*              been placed on the stack in the proper order.
*
* Note(s)    : Interrupts are enabled when your task starts executing. You can change this by setting the
*              PSW to 0x0002 instead.  In this case, interrupts would be disabled upon task startup.  The
*              application code would be responsible for enabling interrupts at the beginning of the task
*              code.  You will need to modify OSTaskIdle() and OSTaskStat() so that they enable 
*              interrupts.  Failure to do this will make your system crash!
*********************************************************************************************************
*/

void *OSTaskStkInit (void (*task)(void *pd), void *pdata, void *ptos, INT16U opt)
{
    unsigned int *stk;

    opt    = opt;                           /* 'opt' is not used, prevent warning                      */
    stk    = (unsigned int *)ptos;          /* Load stack pointer                                      */

    /* build a context for the new task */
    *--stk = (unsigned int) task;       /* pc */
    *--stk = (unsigned int) task;       /* lr */

    *--stk = 0;                         /* r12 */
    *--stk = 0;                         /* r11 */
    *--stk = 0;                         /* r10 */
    *--stk = 0;                         /* r9 */
    *--stk = 0;                         /* r8 */
    *--stk = 0;                         /* r7 */
    *--stk = 0;                         /* r6 */
    *--stk = 0;                         /* r5 */
    *--stk = 0;                         /* r4 */
    *--stk = 0;                         /* r3 */
    *--stk = 0;                         /* r2 */
    *--stk = 0;                         /* r1 */
    *--stk = (unsigned int) pdata;      /* r0 */
    *--stk = (SVC32MODE|0x0);			/* cpsr  IRQ, FIQ disable*/
    *--stk = (SVC32MODE|0x0);			/* spsr  IRQ, FIQ disable */


    return ((void *)stk);
}

/*$PAGE*/
#if OS_CPU_HOOKS_EN
/*
*********************************************************************************************************
*                                          TASK CREATION HOOK
*
* Description: This function is called when a task is created.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being created.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/
void OSTaskCreateHook (OS_TCB *ptcb)
{
    ptcb = ptcb;                       /* Prevent compiler warning                                     */
}


/*
*********************************************************************************************************
*                                           TASK DELETION HOOK
*
* Description: This function is called when a task is deleted.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being deleted.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/
void OSTaskDelHook (OS_TCB *ptcb)
{
    ptcb = ptcb;                       /* Prevent compiler warning                                     */
}

/*
*********************************************************************************************************
*                                           TASK SWITCH HOOK
*
* Description: This function is called when a task switch is performed.  This allows you to perform other
*              operations during a context switch.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are disabled during this call.
*              2) It is assumed that the global pointer 'OSTCBHighRdy' points to the TCB of the task that
*                 will be 'switched in' (i.e. the highest priority task) and, 'OSTCBCur' points to the 
*                 task being switched out (i.e. the preempted task).
*********************************************************************************************************
*/
void OSTaskSwHook (void)
{
}

/*
*********************************************************************************************************
*                                           STATISTIC TASK HOOK
*
* Description: This function is called every second by uC/OS-II's statistics task.  This allows your 
*              application to add functionality to the statistics task.
*
* Arguments  : none
*********************************************************************************************************
*/
void OSTaskStatHook (void)
{
}

/*
*********************************************************************************************************
*                                               TICK HOOK
*
* Description: This function is called every tick.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/

void OSTimeTickHook (void)
{
#ifdef KBD_SCAN
	Kbd_Scan();
#endif

#ifdef STEPPER_PULSE
	DRVStepperPulse();
#endif
}
#endif

#define BUILD_DATE "Date: " __DATE__ "\n"

/*
 * Initialize an ARM Target board
 */
void ARMTargetInit(void)
{
	/* 配置系统时钟 */
    ChangeClockDivider(1,1);          // 1:2:4    
    ChangeMPllValue(0xa1,0x3,0x1);    // FCLK=202.8MHz  
	
	/* 中断初始化 */
    Isr_Init();
    /* 初始化端口 */
    Port_Init();
    
    /* 初始化串口 */
    Uart_Init(0,115200);
    Uart_Select(0);

	// Tell the world who we are //
	Uart_Printf("uC/OS-II, The Real-Time Kernel ARM9 (S3C2410X) Ported version\n");
    Uart_Printf("     (Ported by) CVTECH Ltd.,www.cvtech.com.cn\n");

	#ifdef DEBUG
		Uart_Printf("Initialising target\n");
	#endif

	// disable interrupts (IRQs) //
	ARMDisableInt();

	// soft vectors /
	#ifdef DEBUG
		Uart_Printf("Setting up soft vectors\n");
	#endif

	// Define pre & post-process routines for Interrupt //
	uHALir_DefineIRQ((void *)IrqStart, (void *)IrqFinish, (void *) 0);

	#ifdef DEBUG
		Uart_Printf("Timer init\n");
	#endif
	uHALr_InitTimers();

	#ifdef DEBUG
		Uart_Printf("targetInit() complete\n");
	#endif
}// targetInit //

// start the ARM target running //
void  ARMTargetStart(void)
{
	#ifdef DEBUG
		Uart_Printf("Starting target\n") ;
	#endif

	// Start system timer & enable the interrupt. //
	uHALr_InstallSystemTimer();
}

// just 'notice' that we need to change context //
int need_to_swap_context = 0 ;
void OSIntCtxSw(void)
{
	need_to_swap_context = 1;
}

/* This is what uCOS does at the start of an IRQ */
void IrqStart(void)
{
    /* increment nesting counter */
    OSIntNesting++;
}

/* This is what uCOS does at the end of an IRQ */
void *IrqFinish(void)
{
    OSIntExit() ;
	return (void *)0;
}

