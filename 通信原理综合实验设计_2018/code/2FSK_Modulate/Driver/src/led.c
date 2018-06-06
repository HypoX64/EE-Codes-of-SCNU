#include "led.h"

//ALIENTEK mini�SSTM32������
//LED��������	   
//�޸�����:2017/2/9
//�汾��V1.1
//@Hypo						   	    

/*
��飺��ʼ��PA8��PD2Ϊ����� ��ʹ���������ڵ�ʱ��
ʹ�÷���������  LED_Init(); ��
          GPIO_SetBits(GPIOA,GPIO_Pin_8);                    //PA8���1
		  GPIO_ResetBits(GPIOA,GPIO_Pin_8);                  //PA8���0
          GPIO_ResetBits(GPIOA, GPIO_Pin_10 | GPIO_Pin_15);  //PA10 PA15 ���0                  
˵����ʹ��ʱ�����и���IO�ڣ�Ϊ����ALIENTEK mini����ͨ�ã��ѽ����˼��ݻ�����������LED0��LED1�ĺ궨�壬����led.h���޸ģ�
      �������еĵ�Ϊ���߼�,LED0Ϊ��ɫ��LED1Ϊ��ɫ
*/

void LED_Init(void)
{	
	/*����һ��GPIO_InitTypeDef�Ľṹ��GPIO_InitStructure
	����ṹ��ľ������������ǿ����ڡ�stm32f10x_gpio.h�������ҵ�������������������ص�Ԫ��*/
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	//ʹ��PA,PD�˿�ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE);
	
/////////////////////////////////////////////////////////////////////////////////////////	
	//����LED0  PA8 ����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				     //PA8 �˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		     //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		     //IO���ٶ�Ϊ50MHz
	GPIO_SetBits(GPIOA, GPIO_Pin_8);                             //���
	
	//��ʼ���ṹ��GPIO_InitStructure�����úõ�GPIO�����ţ�ģʽ�Լ��ٶȣ�
    GPIO_Init(GPIOA, &GPIO_InitStructure);

	
/////////////////////////////////////////////////////////////////////////////////////////		
	//����LED1  PD2 ����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		    //PD2 �˿�����
	                                                            //���ģʽ��IO���ٶȲ��ظ�����
    GPIO_Init(GPIOD, &GPIO_InitStructure);                      //��ʼ������
	GPIO_SetBits(GPIOD, GPIO_Pin_2);                            //���

}

