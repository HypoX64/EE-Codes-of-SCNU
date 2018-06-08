/*
 *                         eg_kbd.c uC/OS��������ʵ��
 *
 * ���ݣ�
 *     ����һ�������ڸ������н��ռ������룬�������������
 * Ŀ�ģ�
 *     uC/OS���Ƽ��������ı�̷���
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
 *     2������Key_GetKey�������ռ������룬������������룬���������¼���
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

    /* ����ʱ�ӽ��Ķ�ʱ������ʼ��������� */
    ARMTargetStart();

	/* Ϩ����������� */
	Led_Display(led_status);
	
    for (;;)
    {
    	/* ��ȡ�������룬key_pressΪ��ֵ */
		key_press = Key_GetKey();
		
		/* �����ֵ */
		switch(key_press)
		{
			/* ����'1'�� */
			case '1':
				led_status ^= 0x01;
				Led_Display(led_status);
			break;
			/* ����'2'�� */
			case '2':
				led_status ^= 0x02;
				Led_Display(led_status);
			break;
			/* ����'3'�� */
			case '3':
				led_status ^= 0x04;
				Led_Display(led_status);
			break;
			/* ����'4'�� */
			case '4':
				led_status ^= 0x08;
				Led_Display(led_status);
			break;
		}
        
        /* ��ʱһ��ʱ�� */
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

		/* ��˸����� */
		sprintf(print_buf, "Task%c() turned\n", *(char *)Id);
        uHALr_printf(print_buf);
        User_SEG_Blink();

        OSSchedUnlock();

        /* �ӳ�1000ms */
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
