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


#define OUT PAout(3)

extern u8  TIM2CH1_CAPTURE_STA;		//���벶��״̬		    				
extern u16	TIM2CH1_CAPTURE_VAL;	//���벶��ֵ
extern int needCLK;
extern int time_VPT;
u32 temp=0; 

void EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);             //�ⲿ�жϣ���Ҫʹ��AFIOʱ��


	
    //PC5  KEY0 �ж���·�Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;                        //�ж���Ϊ5
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	            //ģʽ����Ϊ�ⲿ�ж�
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;         //���ش���
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	                            //����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			    //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;			//�����ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);                                 //����NVIC_InitStruct��ָ���Ĳ�����ʼ�������жϼĴ����Ĵ���
	


		
}

//�Զ�����ݺ�������ֹд��
void exti_init(void)   
{
	EXTIX_Init();
}



//EXTI9_5�жϴ�����
 void EXTI9_5_IRQHandler(void)
{	
	if(TIM2CH1_CAPTURE_STA&0X80)//�ɹ�������һ�θߵ�ƽ
	{
		temp=TIM2CH1_CAPTURE_STA&0X3F;
		temp*=65536;					//���ʱ���ܺ�
		temp+=TIM2CH1_CAPTURE_VAL;		//�õ��ܵĸߵ�ƽʱ��
	if(temp>time_VPT)
	{
		OUT=0;
	}
	else
	{
		OUT=1;
	}
		TIM2CH1_CAPTURE_STA=0;			//������һ�β���
	}
	 EXTI_ClearITPendingBit(EXTI_Line5);          //���LINE5�ϵ��жϱ�־λ  
}

