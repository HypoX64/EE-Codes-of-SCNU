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
OS_STK StackLED[STACKSIZE]= {0, }; // 任务LED任务栈  //响应任务栈
OS_STK StackSEG[STACKSIZE]= {0, }; // 任务SEG任务栈 //KEY1任务栈
OS_STK StackKEY2[STACKSIZE]= {0, }; // KEY2任务栈

/* 任务ID */
char IdLED = '1'; // 任务LED ID
char IdSEG = '2'; // 任务SEG ID
char IdKEY2 = '3'; // 任务KEY2 ID

/* 任务处理函数 */
void TaskLED(void *Id); // 任务LED任务处理函数
void TaskSEG(void *Id); // 任务SEG任务处理函数
void TaskKEY2(void *Id); // 任务KEY2任务处理函数

/* 邮箱 */
OS_EVENT *Mbox1;


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
void User_SEG_Blink(char a)
{
	static unsigned char seg_value[] = { 
		0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 
		0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e 
	};		   
	
	*((unsigned char *)0x10000006) = 0x3e;
	*((unsigned char *)0x10000004) = seg_value[a];
	
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
	int benable = STEP_MOTOR_ENABLE;
	int direct = STEP_MOTOR_CLOCKWISE;

    /* 启动时钟节拍定时器，开始多任务调度 */
    ARMTargetStart();
	
	/* 初始化步进电机 */
	DRVStepperInit();
	
	/* 开始启动步进电机 */
	DRVStepperSetDirect(direct);
	DRVStepperControl(benable);
    
	for (;;) 
	{
		
		INT8U ch;	
		/* 等待邮箱中的消息，如果没有消息则挂起该任务 */
		Msg = (char *)OSMboxPend(Mbox1, 0, &err);	
		
		ch=*Msg;//ch=Msg[0];
		
		/* 打印接受到的消息 */
		uHALr_printf("The key nyou pressed is:");
		uHALr_printf(Msg);
		uHALr_printf("\n");
		
		//if(ch == 0) continue;
		switch( ch )
		{
			/*步进电机： C:加速  D：减速  E：正反转  F：启动/停止*/
			case 'C': 
				uHALr_printf("加速\n");
				DRVStepperSpeedUp();
				break;
			case 'D':  
				uHALr_printf("减速\n");
				DRVStepperSpeedDown();
				break;
			case 'F': 
				if(direct == STEP_MOTOR_CLOCKWISE) {
					uHALr_printf("正转\n");
					direct = STEP_MOTOR_ANTICLOCKWISE;
				} else {
					uHALr_printf("反转\n");
					direct = STEP_MOTOR_CLOCKWISE;
				}
				DRVStepperSetDirect(direct);
				break;
			case 'E': 
				if(benable == STEP_MOTOR_ENABLE) {
					uHALr_printf("停止\n");
					benable = STEP_MOTOR_DISABLE;
				} else {
					uHALr_printf("启动\n");
					benable = STEP_MOTOR_ENABLE;
				}
				DRVStepperControl(benable);
				break;
			/*数码管*/	
			case '0':
				User_SEG_Blink(0);
				break;
			case '1':
				User_SEG_Blink(1);
				break;
			case '2':
				User_SEG_Blink(2);
				break;
			case '3':
				User_SEG_Blink(3);
				break;
			case '4':
				User_SEG_Blink(4);
				break;
			case '5':
				User_SEG_Blink(5);
				break;
			case '6':
				User_SEG_Blink(6);
				break;
			case '7':
				User_SEG_Blink(7);
				break;
			case '8':
				User_SEG_Blink(8);
				break;
			case '9':
				User_SEG_Blink(9);
				break;	
		}		
			
        OSTimeDly(10);     
		
	}
}

/*
 * 任务SEG任务处理函数//KEY1任务函数
 */
void TaskSEG(void *Id)
{
	INT8U Reply;
	char	Msg[100];
	char 	key_press;
	INT8U	err;
	ARMTargetStart();//可以删掉
	for (;;) {
		key_press = Key_GetKey();
		
		//若信号量2被释放（及当Sem2=1）则程序继续执行，否则继续等待
		OSSemPend(Sem2,0,&Reply);
		//Sem2=0，直到释放才变为1
		
		if(key_press!=0)
		{
			/* 发送数据到邮箱 */
			sprintf(Msg, "%c", key_press);
			OSMboxPost(Mbox1, Msg);
		}	
		OSSemPost(Sem1);//释放信号量1
	}
}


/*
 * 任务KEY2任务处理函数
 */
void TaskKEY2(void *Id)
{
	INT8U Reply;
	char	Msg[100];
	char 	key_press;
	INT8U	err;
	ARMTargetStart();//可以删掉
	
	for (;;)
	{
		
		key_press = Key_GetKey();
		OSSemPend(Sem1,0,&Reply);
		
		if(key_press!=0)
		{
			/* 发送数据到邮箱 */
			sprintf(Msg, "%c", key_press);
			OSMboxPost(Mbox1, Msg);
		}
		OSSemPost(Sem2);//释放信号量2	
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
	 * 创建两个信号量
	 */ 
	Sem1=OSSemCreate(0);
	Sem2=OSSemCreate(1);
	
    /* 
     * 创建三个任务
	 TaskLED的优先级为5，TaskSEG的优先级为13，TaskKey2的优先级为14（数字越小优先级越高）
     */
	OSTaskCreate(TaskLED, (void *)&IdLED, (OS_STK *)&StackLED[STACKSIZE - 1], 5);
	OSTaskCreate(TaskSEG, (void *)&IdSEG, (OS_STK *)&StackSEG[STACKSIZE - 1], 13);
	OSTaskCreate(TaskKEY2, (void *)&IdKEY2, (OS_STK *)&StackKEY2[STACKSIZE - 1], 14);

    /* 
     * 启动多任务调度
     */
    OSStart();

    /* 
     * 正常情况下，永远不会执行到这里 
     */
	return;
}   




