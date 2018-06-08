/*
 *                         eg_stepper.c 步进电机驱动实验
 *
 * 内容：
 *     uC/OS下驱动步进电机
 * 目的：
 *     学习如何在uC/OS下驱动步进电机
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
 *     2、接收键盘输入并控制步进电机
 */
void TaskLED(void *Id)
{
    INT8U err;
	int benable = STEP_MOTOR_ENABLE;
	int direct = STEP_MOTOR_CLOCKWISE;

    /* 启动时钟节拍定时器，开始多任务调度 */
    ARMTargetStart();

    uHALr_printf("Task1() called\n");
	uHALr_printf("步进电机测试!\n");
	uHALr_printf("1 -- 正反转 2 -- 起停\n");
	uHALr_printf("UP -- 加速  DOWN -- 减速\n");
    
    /* 初始化步进电机 */
    DRVStepperInit();

	/* 开始启动步进电机 */
	DRVStepperSetDirect(direct);
	DRVStepperControl(benable);
	
    for (;;)
    {
		INT8U  ch;
		
		/* 获取键值 */
		ch = Key_GetKey();
		if(ch == 0)
			continue;
		switch( ch )
		{
			case 'C':  // 加速
				uHALr_printf("\r加速");
				DRVStepperSpeedUp();
				break;
			case 'D':  // 减速
				uHALr_printf("\r减速");
				DRVStepperSpeedDown();
				break;
			case '1': // 正反转控制
				if(direct == STEP_MOTOR_CLOCKWISE)
				{
					uHALr_printf("\r正转");
					direct = STEP_MOTOR_ANTICLOCKWISE;
				}
				else
				{
					uHALr_printf("\r反转");
					direct = STEP_MOTOR_CLOCKWISE;
				}
				DRVStepperSetDirect(direct);
				break;
			case '2': // 使能控制
				if(benable == STEP_MOTOR_ENABLE)
				{
					uHALr_printf("\r停止");
					benable = STEP_MOTOR_DISABLE;
				}
				else
				{
					uHALr_printf("\r启动");
					benable = STEP_MOTOR_ENABLE;
				}
				DRVStepperControl(benable);
				break;
		}
			
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
