#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

//ALIENTEK mini�SSTM32������
//LED��������	   
//�޸�����:2017/2/9
//�汾��V1.0
//@Hypo	
/*
��飺��ʼ��PA8��PD2Ϊ�����.��ʹ���������ڵ�ʱ��
ʹ�÷�����
˵����ʹ��ʱ�����и���IO�ڣ�Ϊ����ALIENTEK mini����ͨ�ã��ѽ����˼��ݻ�����������LED0��LED1�ĺ궨�壬����led.h���޸ģ�
*/

#define LED0 PAout(8)	// LED�궨��
#define LED1 PDout(2)

void LED_Init(void);    //��ʼ��

		 				    
#endif
