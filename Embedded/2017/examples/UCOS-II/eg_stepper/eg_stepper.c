/*
 *                         eg_stepper.c �����������ʵ��
 *
 * ���ݣ�
 *     uC/OS�������������
 * Ŀ�ģ�
 *     ѧϰ�����uC/OS�������������
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
 *     2�����ռ������벢���Ʋ������
 */
void TaskLED(void *Id)
{
    INT8U err;
	int benable = STEP_MOTOR_ENABLE;
	int direct = STEP_MOTOR_CLOCKWISE;

    /* ����ʱ�ӽ��Ķ�ʱ������ʼ��������� */
    ARMTargetStart();

    uHALr_printf("Task1() called\n");
	uHALr_printf("�����������!\n");
	uHALr_printf("1 -- ����ת 2 -- ��ͣ\n");
	uHALr_printf("UP -- ����  DOWN -- ����\n");
    
    /* ��ʼ��������� */
    DRVStepperInit();

	/* ��ʼ����������� */
	DRVStepperSetDirect(direct);
	DRVStepperControl(benable);
	
    for (;;)
    {
		INT8U  ch;
		
		/* ��ȡ��ֵ */
		ch = Key_GetKey();
		if(ch == 0)
			continue;
		switch( ch )
		{
			case 'C':  // ����
				uHALr_printf("\r����");
				DRVStepperSpeedUp();
				break;
			case 'D':  // ����
				uHALr_printf("\r����");
				DRVStepperSpeedDown();
				break;
			case '1': // ����ת����
				if(direct == STEP_MOTOR_CLOCKWISE)
				{
					uHALr_printf("\r��ת");
					direct = STEP_MOTOR_ANTICLOCKWISE;
				}
				else
				{
					uHALr_printf("\r��ת");
					direct = STEP_MOTOR_CLOCKWISE;
				}
				DRVStepperSetDirect(direct);
				break;
			case '2': // ʹ�ܿ���
				if(benable == STEP_MOTOR_ENABLE)
				{
					uHALr_printf("\rֹͣ");
					benable = STEP_MOTOR_DISABLE;
				}
				else
				{
					uHALr_printf("\r����");
					benable = STEP_MOTOR_ENABLE;
				}
				DRVStepperControl(benable);
				break;
		}
			
        OSTimeDly(10);       
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
