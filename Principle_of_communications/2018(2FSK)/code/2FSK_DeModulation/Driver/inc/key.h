#ifndef __KEY_H_
#define __KEY_H_

/*������ص�ͷ�ļ�*/
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

/*
��飺��ʼ��PC5��PA15Ϊ�����,��ʹ���������ڵ�ʱ��
ʹ�÷���������  KEY_Init();  ��
          GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)   //��ȡPC5�ĵ�ƽ         
˵������������KEY0  KEY1�ӵأ�Ϊ���߼�    //KEY0   PC5    //KEY1   PA15     
              WK_UP     ��VCC Ϊ���߼�    //WK_UP  PA0
*/


//�궨�尴������ģ��51�����ʹ�� example: if(KEY0 == 1)
#define KEY0 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)       //KEY0 PC5
#define KEY1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)      //KEY1 PA15
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)    //WK_UP PA0

#define KEY0_PRES	1		//KEY0  
#define KEY1_PRES	2		//KEY1
#define WKUP_PRES	3		//WK_UP 


void KEY_Init(void);        //IO�ڳ�ʼ��
u8 KEY_Scan(u8 mode);       //����ɨ��


#endif
