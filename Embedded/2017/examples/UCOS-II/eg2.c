/*
 *                         eg2.c uC/OS任务间通讯和同步实验
 *
 * 内容：
 *     uC/OS任务间通讯和同步实验,建立一个工程，应用程序含两个任务，一个任务不断显示跑马灯，另外一个任务不断显示数码管
 *     使用信号量实现两个任务间操作的同步进行
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

/* 信号量 */
OS_EVENT *Sem1; // 信号量Sem1
OS_EVENT *Sem2; // 信号量Sem2

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
 *     2、等待信号量Sem2并闪烁跑马灯，然后释放信号量Sem1，并延迟2S
 */
void TaskLED(void *Id)
{
    INT8U Reply;
  
    /* 启动时钟节拍定时器，开始多任务调度 */
    ARMTargetStart();

    for (;;)
    {
        /* 等待信号量Sem2  */
        OSSemPend(Sem2, 0, &Reply);

		/* 
		 * 调用User_LED_Blink函数闪烁跑马灯，并打印[TaskLED]到串口
		 * 此部分代码为需要与另外一个任务同步的代码
		 */
        uHALr_printf("[");
        User_LED_Blink();
        uHALr_printf("TaskLED]");

        /* 释放信号量Sem1 */
        OSSemPost(Sem1);
        
        /* 延迟2000ms */
		OSTimeDly(200);
    }
}

/*
 * 任务SEG任务处理函数
 *     1、每隔100 ticks即1000ms，闪烁数码管
 *     2、等待信号量Sem1并闪烁数码管，然后释放信号量Sem2，并延迟1S
 */
void TaskSEG(void *Id)
{
    INT8U Reply;

    for (;;)
    {
        /* 等待信号量Sem1 */
        OSSemPend(Sem1, 0, &Reply);

		/* 
		 * 调用User_SEG_Blink函数闪烁数码管，并打印[TaskSEG]到串口
		 * 此部分代码为需要与另外一个任务同步的代码
		 */
      	uHALr_printf("[");
        User_SEG_Blink();
        uHALr_printf("TaskSEG]");

        /* 释放信号量Sem2 */
        OSSemPost(Sem2);

        /* 延迟1000ms */
		OSTimeDly(100);
    }
}

/*
 * Main函数.
 *     1、初始化目标系统，初始化硬件定时器等，与操作系统无关
 *     2、调用OSInit初始化uC/OS-II软件数据结构等，必须在打开时钟节拍中断之前调用
 *     3、创建两个信号量，Sem1和Sem2
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
     * 创建两个信号量，Sem1和Sem2，Sem1的初始值为0，Sem2的初始值为1，即Sem2缺省是处于释放状态
     */
    Sem1 = OSSemCreate(0);
    Sem2 = OSSemCreate(1);

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

