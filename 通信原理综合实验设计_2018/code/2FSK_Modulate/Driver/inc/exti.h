#ifndef __EXTI_H_
#define __EXIT_H_	 

//ALIENTEK mini�SSTM32������
//�ⲿ�ж���������	   
//�޸�����:2017/2/11
//�汾��V1.0
//@Hypo						   	    

/*
��飺    �����ⲿ�жϺ���
ʹ�÷�����1.�����ж����š���ʽ�������ػ��½��أ����ɽ��key.h
          2.�ڶ�Ӧ�ĵ��жϴ������м����жϴ�����   ��:  EXTI0_IRQHandler()��
          3.����������  EXTIX_Init();  ���ⲿ�жϽ��г�ʼ������       
˵������������KEY0  KEY1�ӵأ�Ϊ���߼� �½��ش���   //KEY0   PC5    //KEY1   PA15     
             WK_UP     ��VCC Ϊ���߼�  �����ش���  //WK_UP  PA0
*/


#include "led.h"
#include "key.h"
#include "delay.h"
	 
void EXTIX_Init(void);   //IO��ʼ��
void exti_init(void);    //�Զ�����ݺ���				    
#endif
