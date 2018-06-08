#ifndef __EXTI_H_
#define __EXIT_H_	 

//ALIENTEK miniSTM32开发板
//外部中断驱动代码	   
//修改日期:2017/2/11
//版本：V1.0
//@Hypo						   	    

/*
简介：    按键外部中断函数
使用方法：1.配置中断引脚、方式（上升沿或下降沿），可结合key.h
          2.在对应的的中断处理函数中加入中断处理函数   如:  EXTI0_IRQHandler()；
          3.主函数调用  EXTIX_Init();  对外部中断进行初始化即可       
说明：开发板中KEY0  KEY1接地，为负逻辑 下降沿触发   //KEY0   PC5    //KEY1   PA15     
             WK_UP     接VCC 为正逻辑  上升沿触发  //WK_UP  PA0
*/


#include "led.h"
#include "key.h"
#include "delay.h"
	 
void EXTIX_Init(void);   //IO初始化
void exti_init(void);    //自定义兼容函数				    
#endif
