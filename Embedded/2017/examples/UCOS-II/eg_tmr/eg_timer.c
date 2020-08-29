/*
 *                         eg_Timer.c uC/OS�����ʱ�����ʵ��
 *
 * ���ݣ�
 *     uC/OS��ʵ�������ʱ��
 * Ŀ�ģ�
 *     ѧϰ�����uC/OS��ʵ�������ʱ��
 *
 */
#include	"Includes.h"               /* uC/OS interface */
#include    "option.h"
#include    "2410lib.h"
#include    "uhal.h"

/* ����ջ */
OS_STK StackLED[STACKSIZE]= {0, }; // ����LED����ջ
OS_STK StackSEG[STACKSIZE]= {0, }; // ����SEG����ջ

/* ����ID */
char IdLED = '1'; // ����LED ID
char IdSEG = '2'; // ����SEG ID

/* �������� */
void TaskLED(void *Id); // ����LED��������
void TaskSEG(void *Id); // ����SEG��������

/* ��ʱ����������������ʱ������һ����ʱ�������� */
void TmrFunc1(INT8U arg);

/* ��ʱ��1��2��3 */
OS_TMR *Tmr1;	
OS_TMR *Tmr2;
OS_TMR *Tmr3;

/*
 * �������˸����������һ�Σ��ĸ������������������������
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
 * �������ʾʵ�飬��0��F������ʾ
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
 * ��ʱ��Tmr1��Tmr2��Tmr3������
 *     1������arg����ȷ����ʱ��
 *     2��������ʱ��ͬʱֻ��һ������Tmr1��Tmr2��Tmr3��������ʱ���ܺ���˸һ�������
 */
void TmrFunc1(INT8U arg)
{
	/* ����arg��������ͬ�Ķ�ʱ�� */
	switch(arg)
	{
	/* ��ʱ��1���رն�ʱ��1���򿪶�ʱ��2 */
	case 1:
		OSEnableTimer(Tmr2);
		OSDisableTimer(Tmr1);
		User_LED_Blink();
		break;
	/* ��ʱ��2���رն�ʱ��2���򿪶�ʱ��3 */
	case 2:
		OSEnableTimer(Tmr3);
		OSDisableTimer(Tmr2);
		break;
	/* ��ʱ��3���رն�ʱ��3���򿪶�ʱ��1 */
	case 3:
		OSEnableTimer(Tmr1);
		OSDisableTimer(Tmr3);
		break;
	}
}

/*
 * ����LED��������
 *     1��OSStart����֮ǰ������������ȼ������ڸú���������ʱ�ӽ��Ķ�ʱ��
 *     2������������ʱ������ʱʱ�䶼Ϊ2���ӣ�����ʹ��ͬ����TmrFunc1��ʱ��������������ʹ�ò�ͬ�Ĳ�������ʱ��1�ĳ�ʼ״̬Ϊ��������Ϊ��
 */
void TaskLED(void *Id)
{
	char key_press;
	char led_status = 0x0;
    INT8U err;
	
    /* ����ʱ�ӽ��Ķ�ʱ������ʼ��������� */
    ARMTargetStart();

	/* ��ʼ����ʱ�� */
	OSTmrInit();
	
	/* ����������ʱ������ʱʱ�䶼Ϊ2���ӣ�����ʹ��ͬ����TmrFunc1��ʱ��������������ʹ�ò�ͬ�Ĳ�������ʱ��1�ĳ�ʼ״̬Ϊ��������Ϊ�� */
	err = OSCreateTimer( &Tmr1, TmrFunc1, 1, 200, OS_TMR_ENABLE);
	err = OSCreateTimer( &Tmr2, TmrFunc1, 2, 200, OS_TMR_DISABLE);
	err = OSCreateTimer( &Tmr3, TmrFunc1, 3, 200, OS_TMR_DISABLE);

	/* �����񵽴���ɣ�������ʱ */
    for (;;)
    {
        OSTimeDly(100);       
    }
}

/*
 * ����SEG��������
 *     1��ÿ��100 ticks��1000ms����˸�����
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
 * Main����.
 *     1����ʼ��Ŀ��ϵͳ����ʼ��Ӳ����ʱ���ȣ������ϵͳ�޹�
 *     2������OSInit��ʼ��uC/OS-II������ݽṹ�ȣ������ڴ�ʱ�ӽ����ж�֮ǰ����
 *     3��������������TaskLED��TaskSEG��TaskLED�����ȼ�Ϊ5��TaskSEG�����ȼ�Ϊ13��TaskLED�����ȼ�����TaskSEG
 *     4������OSStart����uC/OS-II
 */
void Main(void)
{
    /* 
     * Ŀ��ϵͳ��ʼ��
     */
	ARMTargetInit();
    
    /* 
     * uC/OS-II�����ʼ��
     */
	OSInit();

    /* 
     * ������������TaskLED��TaskSEG��TaskLED�����ȼ�Ϊ5��TaskSEG�����ȼ�Ϊ13��TaskLED�����ȼ�����TaskSEG
     */
	OSTaskCreate(TaskLED, (void *)&IdLED, (OS_STK *)&StackLED[STACKSIZE - 1], 5);
	OSTaskCreate(TaskSEG, (void *)&IdSEG, (OS_STK *)&StackSEG[STACKSIZE - 1], 13);
  
    /* 
     * �������������
     */
    OSStart();

    /* 
     * ��������£���Զ����ִ�е����� 
     */
	return;
}   
