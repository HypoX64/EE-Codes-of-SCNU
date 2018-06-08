#include "key.h"
#include "delay.h"

//ALIENTEK mini�SSTM32������
//KEY��������	   
//�޸�����:2017/2/10
//�汾��V1.0
//@Hypo						   	    

/*
��飺��ʼ��PC5��PA15Ϊ�����,��ʹ���������ڵ�ʱ��
ʹ�÷���������  KEY_Init();  ��
          GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)   //��ȡPC5�ĵ�ƽ         
˵������������KEY0  KEY1�ӵأ�Ϊ���߼�    //KEY0   PC5    //KEY1   PA15     
             WK_UP     ��VCC Ϊ���߼�    //WK_UP  PA0
*/
void KEY_Init(void)
{   
	GPIO_InitTypeDef GPIO_InitStructure;                                          //����ṹ��GPIO_InitStructure
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);     //ʹ��PORTA,PORTCʱ��
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;                  //PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                //���ó���������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		     //IO���ٶ�Ϊ50MHz
 	GPIO_Init(GPIOA, &GPIO_InitStructure);                       //��ʼ��GPIO A15
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;                   //PC5   //���ó���������  //IO���ٶ�Ϊ50MHz
 	GPIO_Init(GPIOC, &GPIO_InitStructure);                       //��ʼ��GPIO C5
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;                   //PA0   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;                //���ó���������  //IO���ٶ�Ϊ50MHz
 	GPIO_Init(GPIOA, &GPIO_InitStructure);                       //��ʼ��GPIO A0
	
	delay_init();                                                //��ʼ��delay����
	
}



/*
��飺ģ��51�����м���ɨ��
ʹ�÷���������   KEY_Scan(0);  // ��֧������
				KEY_Scan(1);   //֧������
˵�������ް�������  return 0;
      ��KEY0����    return KEY0_PRES;
      ��KEY1����    return KEY1_PRES;  
      ��WK_UP����   return WKUP_PRES;
*/
u8 KEY_Scan(u8 mode)
{
	static u8 key_up=1;                  //�������ɿ���־
	if(mode)key_up=1;                    //֧������		  
	if(key_up &&(KEY0 == 0||KEY1 == 0||WK_UP==1))
	{
		delay_ms(10);                    //ȥ���� 
		key_up=0;
		if(KEY0==0)
			return KEY0_PRES;
		else if(KEY1==0)
			return KEY1_PRES;
		else if(WK_UP==1)
			return WKUP_PRES; 
	}
	else if(KEY0==1&&KEY1==1&&WK_UP==0)
		key_up=1; 	     
	return 0;                            // �ް�������
	
}
