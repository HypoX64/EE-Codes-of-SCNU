//（1）创建两个任务，一个按键任务一个响应任务。按键任务检测是否有键按下，有键按下即发送消息邮箱。响应任务检测消息邮箱，有消息则在串口打印输出。

#include	"Includes.h"               
#include    "option.h"
#include    "2410lib.h"
#include    "uhal.h"

OS_STK StackLED[STACKSIZE]= {0, }; 
OS_STK StackSEG[STACKSIZE]= {0, }; 

char IdLED = '1'; 
char IdSEG = '2'; 

void TaskLED(void *Id); 
void TaskSEG(void *Id); 

OS_EVENT *Mbox1;


void TaskLED(void *Id)
{
	char *Msg;
	INT8U err, Reply;
	ARMTargetStart(); 
   
	for (;;) {
		Msg = (char *)OSMboxPend(Mbox1, 0, &err);
		uHALr_printf(Msg);
	}
}

void TaskSEG(void *Id)
{
	char Msg[100];
	char key_press;
	INT8U err;

	for (;;) {
		key_press = Key_GetKey();
		if(key_press!=0) {
			sprintf(Msg, "%c", key_press);
			OSMboxPost(Mbox1, Msg);			
		}
	}
}

void Main(void)
{
	ARMTargetInit();
	OSInit();
	Mbox1 = OSMboxCreate((void *)0); 
	OSTaskCreate(TaskLED,(void*)&IdLED, (OS_STK *)&StackLED[STACKSIZE - 1], 5);
	OSTaskCreate(TaskSEG,(void*)&IdSEG, (OS_STK *)&StackSEG[STACKSIZE - 1], 13);
    OSStart();
	return;
}   



//（2）创建两个任务，一个按键任务一个响应任务。按键任务检测是否有键按下，有键按下即发送消息邮箱。响应任务检测消息邮箱，有消息则控制步进电机的正转，反转，停止、加速和减速。

#include	"Includes.h"               
#include    "option.h"
#include    "2410lib.h"
#include    "uhal.h"

OS_STK StackLED[STACKSIZE]= {0, }; 
OS_STK StackSEG[STACKSIZE]= {0, }; 

OS_EVENT *Mbox1;

char IdLED = '1'; // 任务LED ID
char IdSEG = '2'; // 任务SEG ID

void TaskLED(void *Id); 
void TaskSEG(void *Id); 

void User_LED_Blink(void)
{
	static int led_status = 0;
	led_status += 1;
	if(led_status % 2 == 0) {
		Led_Display(0x0f);
	} else {
		Led_Display(0x00);
	}		
}

void User_SEG_Blink(void)
{
	static unsigned char seg_value[] = { 0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e };		   
	static int seg_status = 0;
	
	*((unsigned char *)0x10000006) = 0x3e;
	*((unsigned char *)0x10000004) = seg_value[seg_status];
	seg_status += 1;
	if(seg_status > 15) {
		seg_status = 0;
	}
}


void TaskLED(void *Id)
{
    INT8U err;
    char	*Msg;
	int benable = STEP_MOTOR_ENABLE;
	int direct = STEP_MOTOR_CLOCKWISE;

    ARMTargetStart();

    uHALr_printf("Task1() called\n");
	uHALr_printf("步进电机测试!\n");
	uHALr_printf("E -- 正反转 F-- 起停\n");
	uHALr_printf("UP -- 加速  DOWN -- 减速\n");
    
    DRVStepperInit();
	DRVStepperSetDirect(direct);
	DRVStepperControl(benable);
	
    for (;;) {
    	INT8U err;
    	Msg = (char *)OSMboxPend(Mbox1, 0, &err);
		INT8U  ch;	
	
		ch = *Msg;
		uHALr_printf(Msg);	uHALr_printf(Msg);	uHALr_printf(Msg);
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
			case 'E': // 正反转控制
				if(direct == STEP_MOTOR_CLOCKWISE) {
					uHALr_printf("\r正转");
					direct = STEP_MOTOR_ANTICLOCKWISE;
				} else {
					uHALr_printf("\r反转");
					direct = STEP_MOTOR_CLOCKWISE;
				}
				DRVStepperSetDirect(direct);
				break;
			case 'F': // 使能控制
				if(benable == STEP_MOTOR_ENABLE) {
					uHALr_printf("\r停止");
					benable = STEP_MOTOR_DISABLE;
				} else {
					uHALr_printf("\r启动");
					benable = STEP_MOTOR_ENABLE;
				}
				DRVStepperControl(benable);
				break;
		}
        OSTimeDly(10);       
    }
}

void TaskSEG(void *Id)
{
	char Msg[100];
	char key_press;
	INT8U err;

	for (;;) {
		key_press = Key_GetKey();
		if(key_press!=0) {
			/* 发送数据到邮箱 */
			sprintf(Msg, "%c", key_press);
			OSMboxPost(Mbox1, Msg);		
		}
	}
}



void Main(void)
{
   
	ARMTargetInit();
	OSInit();
	Mbox1 = OSMboxCreate((void *)0); 

	OSTaskCreate(TaskLED,(void*)&IdLED, (OS_STK *)&StackLED[STACKSIZE - 1], 5);
	OSTaskCreate(TaskSEG,(void*)&IdSEG, (OS_STK *)&StackSEG[STACKSIZE - 1], 13);
    
    OSStart();
	return;
}   


//（3）结合内容1和内容2，修改程序，创建三个任务，两个按键任务一个响应任务。有键按下即发送消息邮箱。任一消息均控制响应任务运行。两个按键任务中任意一个按键按下，则发送一个消息邮箱给响应任务。若按下是数字（0-9），则在串口打印输出，并在数码管显示；如为非数字（其他），则分别对应LED灯的闪烁、步进电机的正转，反转，停止、加速和减速。

#include "Includes.h"               /* uC/OS interface */
#include "option.h"
#include "2410lib.h"
#include "uhal.h"

OS_STK StackRESPONSE[STACKSIZE]= {0, }; 
OS_STK StackKEY1[STACKSIZE]= {0, }; // 任务KEY1任务栈
OS_STK StackKEY2[STACKSIZE]= {0, };

char IdRESPONSE= '1'; 
char IdKEY1 = '2'; // 任务KEY1 ID
char IdKEY2 = '3';


void TaskRESPONSE(void *Id); 
void TaskKEY1(void *Id); 
void TaskKEY2(void *Id);


OS_EVENT *Mbox1;
OS_EVENT *Sem1;
OS_EVENT *Sem2;


void User_LED_Blink(void)
{
	static int led_status = 0;
	
	led_status += 1;
	if(led_status % 2 == 0) {
		Led_Display(0x0f);
	} else {
		Led_Display(0x00);
	}			
}


void User_SEG_Blink(char a)
{
	static unsigned char seg_value[] = { 
		0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 
		0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e 
	};		   
	
	*((unsigned char *)0x10000006) = 0x3e;
	*((unsigned char *)0x10000004) = seg_value[a];
	
}


void TaskRESPONSE(void *Id)
{
	char *Msg;
	INT8U err;
	int benable = STEP_MOTOR_ENABLE;
	int direct = STEP_MOTOR_CLOCKWISE; 
   
	/* 启动时钟节拍定时器，开始多任务调度 */
	ARMTargetStart();

	uHALr_printf("数码管:0~9\n");
	uHALr_printf("步进电机测试!\n");
	uHALr_printf("E -- 正反转 F -- 起停\n");
	uHALr_printf("A -- 加速  B-- 减速"); 
   	DRVStepperInit();
	DRVStepperSetDirect(direct);
	DRVStepperControl(benable);
    
	for (;;) {
		Msg = (char *)OSMboxPend(Mbox1, 0, &err);
		INT8U ch;
		ch = *Msg;
		if(ch == 0) continue;
		switch( ch )
		{	
		/*步进电机： A:加速  B：减速  E：正反转  F：启动/停止*/
			case 'A': 
				uHALr_printf("\t加速");
				DRVStepperSpeedUp();
				break;
			case 'B':  
				uHALr_printf("\t减速");
				DRVStepperSpeedDown();
				break;
			case 'F': 
				if(direct == STEP_MOTOR_CLOCKWISE) {
					uHALr_printf("\t正转");
					direct = STEP_MOTOR_ANTICLOCKWISE;
				} else {
					uHALr_printf("\t反转");
					direct = STEP_MOTOR_CLOCKWISE;
				}
				DRVStepperSetDirect(direct);
				break;
			case 'E': 
				if(benable == STEP_MOTOR_ENABLE) {
					uHALr_printf("\t停止");
					benable = STEP_MOTOR_DISABLE;
				} else {
					uHALr_printf("\t启动");
					benable = STEP_MOTOR_ENABLE;
				}
				DRVStepperControl(benable);
				break;
			/*数码管部分：显示0~9*/	
			case '0':
				uHALr_printf(Msg);
				User_SEG_Blink(0);
				break;
			case '1':
				uHALr_printf(Msg);
				User_SEG_Blink(1);
				break;
			case '2':
				uHALr_printf(Msg);
				User_SEG_Blink(2);
				break;
			case '3':
				uHALr_printf(Msg);
				User_SEG_Blink(3);
				break;
			case '4':
				uHALr_printf(Msg);
				User_SEG_Blink(4);
				break;
			case '5':
				uHALr_printf(Msg);
				User_SEG_Blink(5);
				break;
			case '6':
				uHALr_printf(Msg);
				User_SEG_Blink(6);
				break;
			case '7':
				uHALr_printf(Msg);
				User_SEG_Blink(7);
				break;
			case '8':
				uHALr_printf(Msg);
				User_SEG_Blink(8);
				break;
			case '9':
				uHALr_printf(Msg);
				User_SEG_Blink(9);
				break;	
		}		
        OSTimeDly(10);       
	}
}

void TaskKEY1(void *Id)
{
	INT8U Reply;
	ARMTargetStart();
	char Msg[100];
	char key_press;
	INT8U err;

	for (;;) {
		key_press = Key_GetKey();
		OSSemPend(Sem2,0,&Reply);
		if(key_press!=0)
		{				
			sprintf(Msg, "%c", key_press);
			uHALr_printf("\n");
			OSMboxPost(Mbox1, Msg);
		}
		OSSemPost(Sem1);
	}	
}

void TaskKEY2(void *Id)
{
	INT8U Reply;
	ARMTargetStart();
	char Msg[100];
	char key_press;
	INT8U err;

	for (;;) {
		
		key_press = Key_GetKey();
		OSSemPend(Sem1,0,&Reply);
		if(key_press!=0)
		{
			sprintf(Msg, "%c", key_press);
			uHALr_printf("\n");
			OSMboxPost(Mbox1, Msg);			
		}
		OSSemPost(Sem2);
	}
}

void Main(void)
{
	ARMTargetInit();     
	OSInit();
	Mbox1 = OSMboxCreate((void *)0); 
	Sem1=OSSemCreate(0);
	Sem2=OSSemCreate(1);
	
	OSTaskCreate(TaskRESPONSE,(void*)&IdRESPONSE,(OS_STK*)&StackRESPONSE[STACKSIZE - 1], 5);
	OSTaskCreate(TaskKEY1,(void*)&IdKEY1,(OS_STK*)&StackKEY1[STACKSIZE - 1], 13);
	OSTaskCreate(TaskKEY2,(void*)&IdKEY2,(OS_STK*)&StackKEY2[STACKSIZE - 1], 14);

    OSStart();
	return;
}
//（4）使用软件定时器实现led灯每隔3s闪烁一次。（参考E:\caderm\examples\UCOS-II\ Eg_timer.apj）
//在步骤（3）的程序中加入：
//A、在主函数main中加入定时器的初始化和创建

/* 初始化定时器 */
OSTmrInit();
/* 创建1个定时器，定时时间都为3秒钟，它们使用同样的TmrFunc1定时器服务函数，但是使用不同的参数，定时器1的初始状态为
开 */
err = OSCreateTimer( &Tmr1, TmrFunc1, 1, 200, OS_TMR_ENABLE);

//B、TaskRESPONSE任务的swicth语句加入：
case 'C': 
uHALr_printf("\tLED ON");
OSEnableTimer(Tmr1);//开定时器
break;
case 'D': 
uHALr_printf("\tLED OFF");
OSDisableTimer(Tmr1);//关定时器
break;