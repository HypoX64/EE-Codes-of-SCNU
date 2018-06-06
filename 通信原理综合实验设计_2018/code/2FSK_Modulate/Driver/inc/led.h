#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

//ALIENTEK miniSTM32开发板
//LED驱动代码	   
//修改日期:2017/2/9
//版本：V1.0
//@Hypo	
/*
简介：初始化PA8和PD2为输出口.并使能这两个口的时钟
使用方法：
说明：使用时可自行更改IO口，为了与ALIENTEK mini例程通用，已进行了兼容化处理（保留了LED0及LED1的宏定义，可在led.h中修改）
*/

#define LED0 PAout(8)	// LED宏定义
#define LED1 PDout(2)

void LED_Init(void);    //初始化

		 				    
#endif
