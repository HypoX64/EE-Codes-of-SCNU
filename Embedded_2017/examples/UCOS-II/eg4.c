/*
 *                         eg4.c uC/OS���������
 *
 * ���ݣ�
 *     uC/OS���������
 * Ŀ�ģ�
 *     uC/OS��������Ƶķ���
 *
 */
#include	"Includes.h"               /* uC/OS interface */
#include    "option.h"
#include    "2410lib.h"
#include    "uhal.h"

/* ��������ĸ��� */
#define		NUM_TASKS	3	/* ������1��62֮�� */

/* ����ջ */
OS_STK		 TaskStk[NUM_TASKS+1][STACKSIZE];

/* Idle����ID */
int		     pZERO = 0;		/* need a pointer to value of 0 */

/* �ź��������ڴ�����ʾ��ͬ�� */
OS_EVENT	*DispSem;

/* �������� */
void	Task(void *id);
void	IdleTask( void *id);

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
 * Main����.
 *     1����ʼ��Ŀ��ϵͳ����ʼ��Ӳ����ʱ���ȣ������ϵͳ�޹�
 *     2������OSInit��ʼ��uC/OS-II������ݽṹ�ȣ������ڴ�ʱ�ӽ����ж�֮ǰ����
 *     3������һ���ź���
 *     4������NUM_TASKS����������ʹ����ͬ������������ͨ����ͬ��ID�Ž����ж�
 *     5������OSStart����uC/OS-II
 */
void Main(void)
{
 	static int			id[NUM_TASKS];
 	int			j;

	/* ��������ID */
	for(j=0; j<NUM_TASKS; j++)	/* generate the ID's */
	{
		id[j] = (int)'1' + j;	/* create an id we can see */
	}
	    
    /* 
     * Ŀ��ϵͳ��ʼ��
     */
	ARMTargetInit();
    
    /* 
     * uC/OS-II�����ʼ��
     */
	OSInit();
	
	/* �����ź���DispSem���ڴ�����ʾ */
	DispSem = OSSemCreate( 1 );	/* ��ʾ�ź��� */

	/* 
	 * �����񴴽�������NUM_TASKS����������ʹ����ͬ������������ͨ����ͬ��ID�Ž����ж�
	 * ����ÿ���������ʹ�ò�ͬ������ջ�Ͳ�ͬ�����ȼ���
	 */
	for(j=0; j<NUM_TASKS; j++)
	{
		OSTaskCreate(Task, (void *)&id[j], (OS_STK *)&TaskStk[j][STACKSIZE-1], j+1);
	}

	/* ����һ���������� */
	OSTaskCreate(IdleTask,(void *)&pZERO,(OS_STK *)&TaskStk[j][STACKSIZE-1], j+1);
    
    /* 
     * �������������
     */
    OSStart();

    /* 
     * ��������£���Զ����ִ�е����� 
     */
	return;
}   

/*
 * ��������
 *     1���ڵ�һ��ʱ����ʱ�ӽ��Ķ�ʱ������ʼ���������
 *     2��ͨ��ID�Ը���������д���
 */
void	Task(void *id)
{
 	INT8U	err;
 	int	    j;
 	static  int bTargetStart = 0;

	if(bTargetStart == 0)
	{
    	/* ����ʱ�ӽ��Ķ�ʱ������ʼ��������� */
    	ARMTargetStart();
    	bTargetStart = 1;
    }

	while(1)
	{
		OSTimeDly(10);		/* Delay a while */
		OSSemPend(DispSem, 0, &err);
		switch(*(char *)id)
		{
			case '1' :
				User_SEG_Blink();			/* print task's id */
				break;
			case '2' :
				User_LED_Blink();			/* print task's id */
				break;
			case '3' :
				User_SEG_Blink();			/* print task's id */
				break;
			default:
				User_LED_Blink();			/* print task's id */
		}
		OSSemPost(DispSem);
	}
}

/*
 * Idle��������
 *     1��������ʾ�ַ���'.'
 */
void	IdleTask(void *id)
{
 	INT8U	err;

	while(1)
	{
		OSSemPend(DispSem, 0, &err);
		uHALr_printf(".");
		OSSemPost(DispSem);
		OSTimeDly(1);
	}
}
