/*
 *                         eg4.c uC/OS多任务控制
 *
 * 内容：
 *     uC/OS多任务控制
 * 目的：
 *     uC/OS多任务控制的方法
 *
 */
#include	"Includes.h"               /* uC/OS interface */
#include    "option.h"
#include    "2410lib.h"
#include    "uhal.h"

/* 创建任务的个数 */
#define		NUM_TASKS	3	/* 必须在1到62之间 */

/* 任务栈 */
OS_STK		 TaskStk[NUM_TASKS+1][STACKSIZE];

/* Idle任务ID */
int		     pZERO = 0;		/* need a pointer to value of 0 */

/* 信号量，用于串口显示的同步 */
OS_EVENT	*DispSem;

/* 任务处理函数 */
void	Task(void *id);
void	IdleTask( void *id);

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
 * Main函数.
 *     1、初始化目标系统，初始化硬件定时器等，与操作系统无关
 *     2、调用OSInit初始化uC/OS-II软件数据结构等，必须在打开时钟节拍中断之前调用
 *     3、创建一个信号量
 *     4、创建NUM_TASKS个任务，它们使用相同的任务处理函数，通过不同的ID号进行判断
 *     5、调用OSStart启动uC/OS-II
 */
void Main(void)
{
 	static int			id[NUM_TASKS];
 	int			j;

	/* 建立任务ID */
	for(j=0; j<NUM_TASKS; j++)	/* generate the ID's */
	{
		id[j] = (int)'1' + j;	/* create an id we can see */
	}
	    
    /* 
     * 目标系统初始化
     */
	ARMTargetInit();
    
    /* 
     * uC/OS-II软件初始化
     */
	OSInit();
	
	/* 创建信号量DispSem用于串口显示 */
	DispSem = OSSemCreate( 1 );	/* 显示信号量 */

	/* 
	 * 多任务创建，创建NUM_TASKS个任务，它们使用相同的任务处理函数，通过不同的ID号进行判断
	 * 但是每个任务必须使用不同的任务栈和不同的优先级数
	 */
	for(j=0; j<NUM_TASKS; j++)
	{
		OSTaskCreate(Task, (void *)&id[j], (OS_STK *)&TaskStk[j][STACKSIZE-1], j+1);
	}

	/* 创建一个空闲任务 */
	OSTaskCreate(IdleTask,(void *)&pZERO,(OS_STK *)&TaskStk[j][STACKSIZE-1], j+1);
    
    /* 
     * 启动多任务调度
     */
    OSStart();

    /* 
     * 正常情况下，永远不会执行到这里 
     */
	return;
}   

/*
 * 任务处理函数
 *     1、在第一次时启动时钟节拍定时器，开始多任务调度
 *     2、通过ID对各自任务进行处理
 */
void	Task(void *id)
{
 	INT8U	err;
 	int	    j;
 	static  int bTargetStart = 0;

	if(bTargetStart == 0)
	{
    	/* 启动时钟节拍定时器，开始多任务调度 */
    	ARMTargetStart();
    	bTargetStart = 1;
    }

	while(1)
	{
		OSTimeDly(10);		/* Delay a while */
		OSSemPend(DispSem, 0, &err);
		switch(*(char *)id)
		{
			case '1' :
				User_SEG_Blink();			/* print task's id */
				break;
			case '2' :
				User_LED_Blink();			/* print task's id */
				break;
			case '3' :
				User_SEG_Blink();			/* print task's id */
				break;
			default:
				User_LED_Blink();			/* print task's id */
		}
		OSSemPost(DispSem);
	}
}

/*
 * Idle任务处理函数
 *     1、不断显示字符串'.'
 */
void	IdleTask(void *id)
{
 	INT8U	err;

	while(1)
	{
		OSSemPend(DispSem, 0, &err);
		uHALr_printf(".");
		OSSemPost(DispSem);
		OSTimeDly(1);
	}
}
