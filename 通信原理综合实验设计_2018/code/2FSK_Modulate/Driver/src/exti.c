#include "exti.h"

//ALIENTEK miniSTM32开发板
//外部中断驱动代码	   
//修改日期:2017/2/11
//版本：V1.0
//@Hypo						   	    

/*
简介：    按键外部中断函数
使用方法：1.配置中断引脚、方式（上升沿或下降沿），可结合key.h
          2.在对应的的中断处理函数中加入中断处理函数   如:  EXTI0_IRQHandler()；
          3.主函数调用  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
						EXTIX_Init();  对外部中断进行初始化即可       
说明：开发板中KEY0  KEY1接地，为负逻辑 下降沿触发   //KEY0   PC5    //KEY1   PA15     
             WK_UP     接VCC 为正逻辑  上升沿触发  //WK_UP  PA0
      若改变开关引脚，则需要在key.h里初始化相关引脚
*/

//外部中断初始化函数
int mode=0;

void EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);             //外部中断，需要使能AFIO时钟

	KEY_Init();                                                     //初始化按键对应IO模式

	
    //PC5  KEY0 中断线路以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;                        //中断线为5
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	            //模式设置为外部中断
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;         //下降沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	                            //根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			    //使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;			//子优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);                                 //根据NVIC_InitStruct中指定的参数初始化向量中断寄存器寄存器
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	

    //PA15   KEY1  中断线路以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line15;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	                           	    //根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
   	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;			//子优先级0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);                                 //根据NVIC_InitStruct中指定的参数初始化向量中断寄存器寄存器

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //PA0   WK_UP	  中断线以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);

   	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		                            //根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			    //使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;			//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	                            //根据NVIC_InitStruct中指定的参数初始化向量中断寄存器寄存器
		
}

//自定义兼容函数（防止写错）
void exti_init(void)   
{
	EXTIX_Init();
}


//EXTI0中断处理函数
void EXTI0_IRQHandler(void)
{ 
	delay_ms(10);                                  //消抖
	if(WK_UP == 1)                                 //对应WK_UP消抖（WK_UP接VCC正逻辑）
	{
		/*LED0=0;
		LED1=0;*/

		
	}
	EXTI_ClearITPendingBit(EXTI_Line0);            //清除EXTI0线路挂起位
}


//EXTI9_5中断处理函数
 void EXTI9_5_IRQHandler(void)
{	
	if(EXTI_GetITStatus(EXTI_Line5) == 1)         //判断EXTI5线路中断
	{
		//delay_ms(10);                             //消抖	
		if(KEY0 == 0)	                          //对应KEY0消抖（负逻辑）
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
	 EXTI_ClearITPendingBit(EXTI_Line5);          //清除LINE5上的中断标志位  
}



//EXTI15_10中断处理函数
void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line15) == 1)       //判断EXTI15线路中断
	{
		delay_ms(10);                            //消抖	
		if(KEY1 == 0)	                         //对应KEY1消抖（负逻辑）
		{
			mode++;
			if(mode==3)
			{
				mode=0;
			}

		
		}
	
	}
	 EXTI_ClearITPendingBit(EXTI_Line15);        //清除LINE15线路挂起位
}
