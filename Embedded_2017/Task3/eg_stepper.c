/*
 *                         eg3.c uC/OS�����ͨѶ��ͬ��ʵ��
 *
 * ���ݣ�
 *     uC/OS�����ͨѶ��ͬ��ʵ��,����һ�����̣�Ӧ�ó�����������һ�����񲻶���ʾ����ƣ�����һ�����񲻶���ʾ�����
 *     ʹ������ʵ����������������ͨѶ����
 * Ŀ�ģ�
 *     uC/OS�����ͨѶ��ͬ����̣��Զ�����Ӧ�ñ���Լ������ͨѶ��ͬ����ֱ�۵��˽⡣
 *
 */
#include	"Includes.h"               /* uC/OS interface */
#include    "option.h"
#include    "2410lib.h"
#include    "uhal.h"

/* ����ջ */
OS_STK StackLED[STACKSIZE]= {0, }; // ����LED����ջ  //��Ӧ����ջ
OS_STK StackSEG[STACKSIZE]= {0, }; // ����SEG����ջ //KEY1����ջ
OS_STK StackKEY2[STACKSIZE]= {0, }; // KEY2����ջ

/* ����ID */
char IdLED = '1'; // ����LED ID
char IdSEG = '2'; // ����SEG ID
char IdKEY2 = '3'; // ����KEY2 ID

/* �������� */
void TaskLED(void *Id); // ����LED��������
void TaskSEG(void *Id); // ����SEG��������
void TaskKEY2(void *Id); // ����KEY2��������

/* ���� */
OS_EVENT *Mbox1;


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
 * ����LED��������
 *     1��OSStart����֮ǰ������������ȼ������ڸú���������ʱ�ӽ��Ķ�ʱ��
 *     2���ȴ������е���Ϣ������ӡ����
 */
void TaskLED(void *Id)
{
	char	*Msg;
	INT8U	err;
	int benable = STEP_MOTOR_ENABLE;
	int direct = STEP_MOTOR_CLOCKWISE;

    /* ����ʱ�ӽ��Ķ�ʱ������ʼ��������� */
    ARMTargetStart();
	
	/* ��ʼ��������� */
	DRVStepperInit();
	
	/* ��ʼ����������� */
	DRVStepperSetDirect(direct);
	DRVStepperControl(benable);
    
	for (;;) 
	{
		
		INT8U ch;	
		/* �ȴ������е���Ϣ�����û����Ϣ���������� */
		Msg = (char *)OSMboxPend(Mbox1, 0, &err);	
		
		ch=*Msg;//ch=Msg[0];
		
		/* ��ӡ���ܵ�����Ϣ */
		uHALr_printf("The key nyou pressed is:");
		uHALr_printf(Msg);
		uHALr_printf("\n");
		
		//if(ch == 0) continue;
		switch( ch )
		{
			/*��������� C:����  D������  E������ת  F������/ֹͣ*/
			case 'C': 
				uHALr_printf("����\n");
				DRVStepperSpeedUp();
				break;
			case 'D':  
				uHALr_printf("����\n");
				DRVStepperSpeedDown();
				break;
			case 'F': 
				if(direct == STEP_MOTOR_CLOCKWISE) {
					uHALr_printf("��ת\n");
					direct = STEP_MOTOR_ANTICLOCKWISE;
				} else {
					uHALr_printf("��ת\n");
					direct = STEP_MOTOR_CLOCKWISE;
				}
				DRVStepperSetDirect(direct);
				break;
			case 'E': 
				if(benable == STEP_MOTOR_ENABLE) {
					uHALr_printf("ֹͣ\n");
					benable = STEP_MOTOR_DISABLE;
				} else {
					uHALr_printf("����\n");
					benable = STEP_MOTOR_ENABLE;
				}
				DRVStepperControl(benable);
				break;
			/*�����*/	
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
 * ����SEG��������//KEY1������
 */
void TaskSEG(void *Id)
{
	INT8U Reply;
	char	Msg[100];
	char 	key_press;
	INT8U	err;
	ARMTargetStart();//����ɾ��
	for (;;) {
		key_press = Key_GetKey();
		
		//���ź���2���ͷţ�����Sem2=1����������ִ�У���������ȴ�
		OSSemPend(Sem2,0,&Reply);
		//Sem2=0��ֱ���ͷŲű�Ϊ1
		
		if(key_press!=0)
		{
			/* �������ݵ����� */
			sprintf(Msg, "%c", key_press);
			OSMboxPost(Mbox1, Msg);
		}	
		OSSemPost(Sem1);//�ͷ��ź���1
	}
}


/*
 * ����KEY2��������
 */
void TaskKEY2(void *Id)
{
	INT8U Reply;
	char	Msg[100];
	char 	key_press;
	INT8U	err;
	ARMTargetStart();//����ɾ��
	
	for (;;)
	{
		
		key_press = Key_GetKey();
		OSSemPend(Sem1,0,&Reply);
		
		if(key_press!=0)
		{
			/* �������ݵ����� */
			sprintf(Msg, "%c", key_press);
			OSMboxPost(Mbox1, Msg);
		}
		OSSemPost(Sem2);//�ͷ��ź���2	
	}
}

/*
 * Main����.
 *     1����ʼ��Ŀ��ϵͳ����ʼ��Ӳ����ʱ���ȣ������ϵͳ�޹�
 *     2������OSInit��ʼ��uC/OS-II������ݽṹ�ȣ������ڴ�ʱ�ӽ����ж�֮ǰ����
 *     3������һ������
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
	 * ����һ������
	 */
	Mbox1 = OSMboxCreate((void *)0); 
	
	
	/* 
	 * ���������ź���
	 */ 
	Sem1=OSSemCreate(0);
	Sem2=OSSemCreate(1);
	
    /* 
     * ������������
	 TaskLED�����ȼ�Ϊ5��TaskSEG�����ȼ�Ϊ13��TaskKey2�����ȼ�Ϊ14������ԽС���ȼ�Խ�ߣ�
     */
	OSTaskCreate(TaskLED, (void *)&IdLED, (OS_STK *)&StackLED[STACKSIZE - 1], 5);
	OSTaskCreate(TaskSEG, (void *)&IdSEG, (OS_STK *)&StackSEG[STACKSIZE - 1], 13);
	OSTaskCreate(TaskKEY2, (void *)&IdKEY2, (OS_STK *)&StackKEY2[STACKSIZE - 1], 14);

    /* 
     * �������������
     */
    OSStart();

    /* 
     * ��������£���Զ����ִ�е����� 
     */
	return;
}   




