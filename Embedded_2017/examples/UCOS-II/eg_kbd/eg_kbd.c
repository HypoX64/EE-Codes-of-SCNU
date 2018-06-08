/*
 *                         eg_kbd.c uC/OS键盘驱动实验
 *
 * 内容：
 *     建立一个任务，在该任务中接收键盘输入，并处理键盘输入
 * 目的：
 *     uC/OS控制键盘驱动的编程方法
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
 *     2、调用Key_GetKey函数接收键盘输入，并处理键盘输入，处理了如下键：
 *        '1' - LED1 ON/OFF
 *        '2' - LED2 ON/OFF
 *        '3' - LED3 ON/OFF
 *        '4' - LED4 ON/OFF
 */
void TaskLED(void *Id)
{
	char key_press;
	char led_status = 0x0;
	
    uHALr_printf("Task1() called\n");

    /* 启动时钟节拍定时器，开始多任务调度 */
    ARMTargetStart();

	/* 熄灭所有跑马灯 */
	Led_Display(led_status);
	
    for (;;)
    {
    	/* 获取键盘输入，key_press为键值 */
		key_press = Key_GetKey();
		
		/* 处理键值 */
		switch(key_press)
		{
			/* 处理'1'键 */
			case '1':
				led_status ^= 0x01;
				Led_Display(led_status);
			break;
			/* 处理'2'键 */
			case '2':
				led_status ^= 0x02;
				Led_Display(led_status);
			break;
			/* 处理'3'键 */
			case '3':
				led_status ^= 0x04;
				Led_Display(led_status);
			break;
			/* 处理'4'键 */
			case '4':
				led_status ^= 0x08;
				Led_Display(led_status);
			break;
		}
        
        /* 延时一段时间 */
        OSTimeDly(10);       
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

		/* 闪烁数码管 */
		sprintf(print_buf, "Task%c() turned\n", *(char *)Id);
        uHALr_printf(print_buf);
        User_SEG_Blink();

        OSSchedUnlock();

        /* 延迟1000ms */
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
