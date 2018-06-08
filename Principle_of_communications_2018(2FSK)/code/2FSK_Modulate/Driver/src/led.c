#include "led.h"

//ALIENTEK miniSTM32开发板
//LED驱动代码	   
//修改日期:2017/2/9
//版本：V1.1
//@Hypo						   	    

/*
简介：初始化PA8和PD2为输出口 并使能这两个口的时钟
使用方法：调用  LED_Init(); 后
          GPIO_SetBits(GPIOA,GPIO_Pin_8);                    //PA8输出1
		  GPIO_ResetBits(GPIOA,GPIO_Pin_8);                  //PA8输出0
          GPIO_ResetBits(GPIOA, GPIO_Pin_10 | GPIO_Pin_15);  //PA10 PA15 输出0                  
说明：使用时可自行更改IO口，为了与ALIENTEK mini例程通用，已进行了兼容化处理（保留了LED0及LED1的宏定义，可在led.h中修改）
      开发板中的灯为负逻辑,LED0为红色，LED1为绿色
*/

void LED_Init(void)
{	
	/*定义一个GPIO_InitTypeDef的结构体GPIO_InitStructure
	这个结构体的具体描述，我们可以在“stm32f10x_gpio.h”里面找到包含了所有与引脚相关的元素*/
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	//使能PA,PD端口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE);
	
/////////////////////////////////////////////////////////////////////////////////////////	
	//配置LED0  PA8 引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				     //PA8 端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		     //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		     //IO口速度为50MHz
	GPIO_SetBits(GPIOA, GPIO_Pin_8);                             //灭灯
	
	//初始化结构体GPIO_InitStructure中配置好的GPIO（引脚，模式以及速度）
    GPIO_Init(GPIOA, &GPIO_InitStructure);

	
/////////////////////////////////////////////////////////////////////////////////////////		
	//配置LED1  PD2 引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		    //PD2 端口配置
	                                                            //输出模式，IO口速度不重复定义
    GPIO_Init(GPIOD, &GPIO_InitStructure);                      //初始化配置
	GPIO_SetBits(GPIOD, GPIO_Pin_2);                            //灭灯

}

