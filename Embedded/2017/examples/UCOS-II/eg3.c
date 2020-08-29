/*
 *                         eg3.c uC/OS任务间通讯和同步实验
 *
 * 内容：
 *     uC/OS任务间通讯和同步实验,建立一个工程，应用程序含两个任务，一个任务不断显示跑马灯，另外一个任务不断显示数码管
 *     使用邮箱实现两个任务间操作的通讯动作
 * 目的：
 *     uC/OS任务间通讯和同步编程，对多任务应用编程以及任务间通讯和同步有直观的了解。
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

/* 邮箱 */
OS_EVENT *Mbox1;

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
 * 任务LED任务处理函数
 *     1、OSStart调用之前创建的最高优先级任务，在该函数重启动时钟节拍定时器
 *     2、等待邮箱中的消息，并打印出来
 */
void TaskLED(void *Id)
{
	char	*Msg;
	INT8U	err;

    /* 启动时钟节拍定时器，开始多任务调度 */
    ARMTargetStart();
    
	for (;;) {
		/* 等待邮箱中的消息，如果没有消息则挂起该任务 */
		Msg = (char *)OSMboxPend(Mbox1, 0, &err);

		/* 打印接受到的消息 */
		uHALr_printf(Msg);
	}
}

/*
 * 任务SEG任务处理函数
 *     1、每隔100 ticks即1000ms，闪烁数码管
 *     2、每隔100 ticks即1000ms，向邮箱发送一个字符串数据
 */
void TaskSEG(void *Id)
{
	char	Msg[100];
	INT8U	err;
	int     nCount = 0;

	for (;;) {
		/* 发送数据到邮箱 */
		sprintf(Msg, "TaskSEG %d", nCount++);
		OSMboxPost(Mbox1, Msg);
		
		/* 闪烁数码管 */
		User_SEG_Blink();
		
        /* 延迟1000ms */
		OSTimeDly(100);
	}
}

/*
 * Main函数.
 *     1、初始化目标系统，初始化硬件定时器等，与操作系统无关
 *     2、调用OSInit初始化uC/OS-II软件数据结构等，必须在打开时钟节拍中断之前调用
 *     3、创建一个邮箱
 *     4、创建两个任务，TaskLED和TaskSEG，TaskLED的优先级为5，TaskSEG的优先级为13，TaskLED的优先级高于TaskSEG
 *     5、调用OSStart启动uC/OS-II
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
	 * 创建一个邮箱
	 */
	Mbox1 = OSMboxCreate((void *)0); 
	
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




