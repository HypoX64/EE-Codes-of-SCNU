#include "exti.h"

//ALIENTEK mini�SSTM32������
//�ⲿ�ж���������	   
//�޸�����:2017/2/11
//�汾��V1.0
//@Hypo						   	    

/*
��飺    �����ⲿ�жϺ���
ʹ�÷�����1.�����ж����š���ʽ�������ػ��½��أ����ɽ��key.h
          2.�ڶ�Ӧ�ĵ��жϴ������м����жϴ�����   ��:  EXTI0_IRQHandler()��
          3.����������  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
						EXTIX_Init();  ���ⲿ�жϽ��г�ʼ������       
˵������������KEY0  KEY1�ӵأ�Ϊ���߼� �½��ش���   //KEY0   PC5    //KEY1   PA15     
             WK_UP     ��VCC Ϊ���߼�  �����ش���  //WK_UP  PA0
      ���ı俪�����ţ�����Ҫ��key.h���ʼ���������
*/

//�ⲿ�жϳ�ʼ������
int mode=0;

void EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);             //�ⲿ�жϣ���Ҫʹ��AFIOʱ��

	KEY_Init();                                                     //��ʼ��������ӦIOģʽ

	
    //PC5  KEY0 �ж���·�Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;                        //�ж���Ϊ5
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	            //ģʽ����Ϊ�ⲿ�ж�
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;         //�½��ش���
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	                            //����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			    //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;			//�����ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);                                 //����NVIC_InitStruct��ָ���Ĳ�����ʼ�������жϼĴ����Ĵ���
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	

    //PA15   KEY1  �ж���·�Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line15;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	                           	    //����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
   	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;			//�����ȼ�0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);                                 //����NVIC_InitStruct��ָ���Ĳ�����ʼ�������жϼĴ����Ĵ���

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //PA0   WK_UP	  �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);

   	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		                            //����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			    //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;			//�����ȼ�2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	                            //����NVIC_InitStruct��ָ���Ĳ�����ʼ�������жϼĴ����Ĵ���
		
}

//�Զ�����ݺ�������ֹд��
void exti_init(void)   
{
	EXTIX_Init();
}


//EXTI0�жϴ�����
void EXTI0_IRQHandler(void)
{ 
	delay_ms(10);                                  //����
	if(WK_UP == 1)                                 //��ӦWK_UP������WK_UP��VCC���߼���
	{
		/*LED0=0;
		LED1=0;*/

		
	}
	EXTI_ClearITPendingBit(EXTI_Line0);            //���EXTI0��·����λ
}


//EXTI9_5�жϴ�����
 void EXTI9_5_IRQHandler(void)
{	
	if(EXTI_GetITStatus(EXTI_Line5) == 1)         //�ж�EXTI5��·�ж�
	{
		//delay_ms(10);                             //����	
		if(KEY0 == 0)	                          //��ӦKEY0���������߼���
		{
//			LED0 = 0;
//			delay_ms(100);
//			LED0 = 1;
//			delay_ms(100);
//			LED0 = 0;
//			delay_ms(100);
//			LED0 = 1;
//			delay_ms(100);
//			LED0 = 0;
//			delay_ms(100);
//			LED0 = 1;
//			delay_ms(100);
		}
	
	}	
	 EXTI_ClearITPendingBit(EXTI_Line5);          //���LINE5�ϵ��жϱ�־λ  
}



//EXTI15_10�жϴ�����
void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line15) == 1)       //�ж�EXTI15��·�ж�
	{
		delay_ms(10);                            //����	
		if(KEY1 == 0)	                         //��ӦKEY1���������߼���
		{
			mode++;
			if(mode==3)
			{
				mode=0;
			}

		
		}
	
	}
	 EXTI_ClearITPendingBit(EXTI_Line15);        //���LINE15��·����λ
}
