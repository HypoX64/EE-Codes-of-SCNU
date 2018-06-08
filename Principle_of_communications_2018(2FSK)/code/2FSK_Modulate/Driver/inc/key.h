#ifndef __KEY_H_
#define __KEY_H_

/*包含相关的头文件*/
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

/*
简介：初始化PC5和PA15为输入口,并使能这两个口的时钟
使用方法：调用  KEY_Init();  后
          GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)   //读取PC5的电平         
说明：开发板中KEY0  KEY1接地，为负逻辑    //KEY0   PC5    //KEY1   PA15     
              WK_UP     接VCC 为正逻辑    //WK_UP  PA0
*/


//宏定义按键，可模仿51风格编程使用 example: if(KEY0 == 1)
#define KEY0 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)       //KEY0 PC5
#define KEY1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)      //KEY1 PA15
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)    //WK_UP PA0

#define KEY0_PRES	1		//KEY0  
#define KEY1_PRES	2		//KEY1
#define WKUP_PRES	3		//WK_UP 


void KEY_Init(void);        //IO口初始化
u8 KEY_Scan(u8 mode);       //键盘扫描


#endif
