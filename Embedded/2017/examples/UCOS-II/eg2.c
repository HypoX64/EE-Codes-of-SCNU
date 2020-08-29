/*
 *                         eg2.c uC/OS�����ͨѶ��ͬ��ʵ��
 *
 * ���ݣ�
 *     uC/OS�����ͨѶ��ͬ��ʵ��,����һ�����̣�Ӧ�ó�����������һ�����񲻶���ʾ����ƣ�����һ�����񲻶���ʾ�����
 *     ʹ���ź���ʵ����������������ͬ������
 * Ŀ�ģ�
 *     uC/OS�����ͨѶ��ͬ����̣��Զ�����Ӧ�ñ���Լ������ͨѶ��ͬ����ֱ�۵��˽⡣
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

/* �ź��� */
OS_EVENT *Sem1; // �ź���Sem1
OS_EVENT *Sem2; // �ź���Sem2

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
 * ����LED��������
 *     1��OSStart����֮ǰ������������ȼ������ڸú���������ʱ�ӽ��Ķ�ʱ��
 *     2���ȴ��ź���Sem2����˸����ƣ�Ȼ���ͷ��ź���Sem1�����ӳ�2S
 */
void TaskLED(void *Id)
{
    INT8U Reply;
  
    /* ����ʱ�ӽ��Ķ�ʱ������ʼ��������� */
    ARMTargetStart();

    for (;;)
    {
        /* �ȴ��ź���Sem2  */
        OSSemPend(Sem2, 0, &Reply);

		/* 
		 * ����User_LED_Blink������˸����ƣ�����ӡ[TaskLED]������
		 * �˲��ִ���Ϊ��Ҫ������һ������ͬ���Ĵ���
		 */
        uHALr_printf("[");
        User_LED_Blink();
        uHALr_printf("TaskLED]");

        /* �ͷ��ź���Sem1 */
        OSSemPost(Sem1);
        
        /* �ӳ�2000ms */
		OSTimeDly(200);
    }
}

/*
 * ����SEG��������
 *     1��ÿ��100 ticks��1000ms����˸�����
 *     2���ȴ��ź���Sem1����˸����ܣ�Ȼ���ͷ��ź���Sem2�����ӳ�1S
 */
void TaskSEG(void *Id)
{
    INT8U Reply;

    for (;;)
    {
        /* �ȴ��ź���Sem1 */
        OSSemPend(Sem1, 0, &Reply);

		/* 
		 * ����User_SEG_Blink������˸����ܣ�����ӡ[TaskSEG]������
		 * �˲��ִ���Ϊ��Ҫ������һ������ͬ���Ĵ���
		 */
      	uHALr_printf("[");
        User_SEG_Blink();
        uHALr_printf("TaskSEG]");

        /* �ͷ��ź���Sem2 */
        OSSemPost(Sem2);

        /* �ӳ�1000ms */
		OSTimeDly(100);
    }
}

/*
 * Main����.
 *     1����ʼ��Ŀ��ϵͳ����ʼ��Ӳ����ʱ���ȣ������ϵͳ�޹�
 *     2������OSInit��ʼ��uC/OS-II������ݽṹ�ȣ������ڴ�ʱ�ӽ����ж�֮ǰ����
 *     3�����������ź�����Sem1��Sem2
 *     4��������������TaskLED��TaskSEG��TaskLED�����ȼ�Ϊ5��TaskSEG�����ȼ�Ϊ13��TaskLED�����ȼ�����TaskSEG
 *     5������OSStart����uC/OS-II
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
     * ���������ź�����Sem1��Sem2��Sem1�ĳ�ʼֵΪ0��Sem2�ĳ�ʼֵΪ1����Sem2ȱʡ�Ǵ����ͷ�״̬
     */
    Sem1 = OSSemCreate(0);
    Sem2 = OSSemCreate(1);

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

