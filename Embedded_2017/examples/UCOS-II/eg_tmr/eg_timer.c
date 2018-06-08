/*
 *                         eg_Timer.c uC/OS软件定时器编程实验
 *
 * 内容：
 *     uC/OS下实现软件定时器
 * 目的：
 *     学习如何在uC/OS下实现软件定时器
 *
 */
#include	"Includes.h"               /* uC/OS interface */
#include    "option.h"
#include    "2410lib.h"
#include    "uhal.h"

/* 任务栈 */
OS_STK StackLED[STACKSIZE]= {0, }; // 任务LED任务栈
OS_STK StackSEG[STACKSIZE]= {0, }; // 任务SEG任务栈

/* 任务ID */
char IdLED = '1'; // 任务LED ID
char IdSEG = '2'; // 任务SEG ID

/* 任务处理函数 */
void TaskLED(void *Id); // 任务LED任务处理函数
void TaskSEG(void *Id); // 任务SEG任务处理函数

/* 定时器服务函数，三个定时器公用一个定时器服务函数 */
void TmrFunc1(INT8U arg);

/* 定时器1、2、3 */
OS_TMR *Tmr1;	
OS_TMR *Tmr2;
OS_TMR *Tmr3;

/*
 * 跑马灯闪烁函数，调用一次，四个跑马灯由亮变灭或者由灭变亮
 */
void User_LED_Blink(void)
{
	static int led_status = 0;
	
	led_status += 1;
	if(led_status % 2 == 0)
		Led_Display(0x0f);
	else
		Led_Display(0x00);			
}

/*
 * 数码管显示实验，由0到F依次显示
 */
void User_SEG_Blink(void)
{
	static unsigned char seg_value[] = { 0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e };		   
	static int seg_status = 0;
	
	*((unsigned char *)0x10000006) = 0x3e;
	*((unsigned char *)0x10000004) = seg_value[seg_status];
	seg_status += 1;
	if(seg_status > 15)
		seg_status = 0;
}

/*
 * 定时器Tmr1、Tmr2、Tmr3处理函数
 *     1、根据arg参数确定定时器
 *     2、三个定时器同时只打开一个，即Tmr1、Tmr2、Tmr3，三个定时器总和闪烁一次跑马灯
 */
void TmrFunc1(INT8U arg)
{
	/* 根据arg参数处理不同的定时器 */
	switch(arg)
	{
	/* 定时器1，关闭定时器1，打开定时器2 */
	case 1:
		OSEnableTimer(Tmr2);
		OSDisableTimer(Tmr1);
		User_LED_Blink();
		break;
	/* 定时器2，关闭定时器2，打开定时器3 */
	case 2:
		OSEnableTimer(Tmr3);
		OSDisableTimer(Tmr2);
		break;
	/* 定时器3，关闭定时器3，打开定时器1 */
	case 3:
		OSEnableTimer(Tmr1);
		OSDisableTimer(Tmr3);
		break;
	}
}

/*
 * 任务LED任务处理函数
 *     1、OSStart调用之前创建的最高优先级任务，在该函数重启动时钟节拍定时器
 *     2、创建三个定时器，定时时间都为2秒钟，它们使用同样的TmrFunc1定时器服务函数，但是使用不同的参数，定时器1的初始状态为开，其余为关
 */
void TaskLED(void *Id)
{
	char key_press;
	char led_status = 0x0;
    INT8U err;
	
    /* 启动时钟节拍定时器，开始多任务调度 */
    ARMTargetStart();

	/* 初始化定时器 */
	OSTmrInit();
	
	/* 创建三个定时器，定时时间都为2秒钟，它们使用同样的TmrFunc1定时器服务函数，但是使用不同的参数，定时器1的初始状态为开，其余为关 */
	err = OSCreateTimer( &Tmr1, TmrFunc1, 1, 200, OS_TMR_ENABLE);
	err = OSCreateTimer( &Tmr2, TmrFunc1, 2, 200, OS_TMR_DISABLE);
	err = OSCreateTimer( &Tmr3, TmrFunc1, 3, 200, OS_TMR_DISABLE);

	/* 该任务到此完成，不断延时 */
    for (;;)
    {
        OSTimeDly(100);       
    }
}

/*
 * 任务SEG任务处理函数
 *     1、每隔100 ticks即1000ms，闪烁数码管
 */
void TaskSEG(void *Id)
{
    uHALr_printf("Task2() called\n");

    for (;;)
    {       
		OSSchedLock();

		sprintf(print_buf, "Task%c() turned\n", *(char *)Id);
        uHALr_printf(print_buf);
        User_SEG_Blink();

        OSSchedUnlock();

        OSTimeDly(100);
    }
}

/*
 * Main函数.
 *     1、初始化目标系统，初始化硬件定时器等，与操作系统无关
 *     2、调用OSInit初始化uC/OS-II软件数据结构等，必须在打开时钟节拍中断之前调用
 *     3、创建两个任务，TaskLED和TaskSEG，TaskLED的优先级为5，TaskSEG的优先级为13，TaskLED的优先级高于TaskSEG
 *     4、调用OSStart启动uC/OS-II
 */
void Main(void)
{
    /* 
     * 目标系统初始化
     */
	ARMTargetInit();
    
    /* 
     * uC/OS-II软件初始化
     */
	OSInit();

    /* 
     * 创建两个任务，TaskLED和TaskSEG，TaskLED的优先级为5，TaskSEG的优先级为13，TaskLED的优先级高于TaskSEG
     */
	OSTaskCreate(TaskLED, (void *)&IdLED, (OS_STK *)&StackLED[STACKSIZE - 1], 5);
	OSTaskCreate(TaskSEG, (void *)&IdSEG, (OS_STK *)&StackSEG[STACKSIZE - 1], 13);
  
    /* 
     * 启动多任务调度
     */
    OSStart();

    /* 
     * 正常情况下，永远不会执行到这里 
     */
	return;
}   
