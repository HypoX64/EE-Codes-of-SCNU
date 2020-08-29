/*
 * File:        eg1.c
 *
 * uC/OS Real-time multitasking kernel for the ARM processor.
 *
 * Simple example of using multiple tasks to blink the led and seg int eb44b0 board.
 *
 * Created by cooljet (www.cvtech.com.cn)
 *
 */
#include	"Includes.h"               /* uC/OS interface */
#include    "44blib\option.h"
#include    "44blib\44blib.h"

/* task stack */
OS_STK StackLED[STACKSIZE]= {0, };
OS_STK StackSEG[STACKSIZE]= {0, };

/* task name string */
char IdLED = '1';
char IdSEG = '2';

/* task entry function */
void TaskLED(void *Id);
void TaskSEG(void *Id);

/*
 * Task entry function. 
 *     this task blink the led every 200 ticks
 *     that is 2s.
 */
void TaskLED(void *Id)
{
    uHALr_printf("Task1() called\n");

    for (;;)
    {
		OSSchedLock();

        uHALr_printf("Task%c() turned\n", *(char *)Id);

        OSSchedUnlock();
        
        OSTimeDly(100);       
    }
}

/*
 * Task entry function. 
 *     this task blink the seg every 200 ticks
 *     that is 1s.
 */
void TaskSEG(void *Id)
{
    uHALr_printf("Task2() called\n");

    for (;;)
    {       
		OSSchedLock();

        uHALr_printf("Task%c() turned\n", *(char *)Id);

        OSSchedUnlock();

        OSTimeDly(100);
    }
}

/*
 * Main function.
 */
void Main(void)
{
    /* 
     * do target (uHAL based ARM system) initialisation 
     */
	ARMTargetInit();
    
    uHALr_printf("#########Example 1#########\n");

    /* 
     * needed by uC/OS 
     */
	OSInit();

    /* 
     * create the tasks in uC/OS and assign increasing
     * priorities to them so that Task3 at the end of
     * the pipeline has the highest priority.
     */
	OSTaskCreate(TaskLED, (void *)&IdLED, (OS_STK *)&StackLED[STACKSIZE - 1], 5);
	/* Create seg blink tasks */
	OSTaskCreate(TaskSEG, (void *)&IdSEG, (OS_STK *)&StackSEG[STACKSIZE - 1], 13);

    /* Start the (uHAL based ARM system) system running */
    ARMTargetStart();

    /* 
     * start the task 
     */
    OSStart();

    /* 
     * never reached 
     */
	return;
}   
