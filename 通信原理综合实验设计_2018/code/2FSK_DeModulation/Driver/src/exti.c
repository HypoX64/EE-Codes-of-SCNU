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


#define OUT PAout(3)

extern u8  TIM2CH1_CAPTURE_STA;		//输入捕获状态		    				
extern u16	TIM2CH1_CAPTURE_VAL;	//输入捕获值
extern int needCLK;
extern int time_VPT;
u32 temp=0; 

void EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);             //外部中断，需要使能AFIO时钟


	
    //PC5  KEY0 中断线路以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;                        //中断线为5
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	            //模式设置为外部中断
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;         //边沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	                            //根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			    //使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;			//子优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);                                 //根据NVIC_InitStruct中指定的参数初始化向量中断寄存器寄存器
	


		
}

//自定义兼容函数（防止写错）
void exti_init(void)   
{
	EXTIX_Init();
}



//EXTI9_5中断处理函数
 void EXTI9_5_IRQHandler(void)
{	
	if(TIM2CH1_CAPTURE_STA&0X80)//成功捕获到了一次高电平
	{
		temp=TIM2CH1_CAPTURE_STA&0X3F;
		temp*=65536;					//溢出时间总和
		temp+=TIM2CH1_CAPTURE_VAL;		//得到总的高电平时间
	if(temp>time_VPT)
	{
		OUT=0;
	}
	else
	{
		OUT=1;
	}
		TIM2CH1_CAPTURE_STA=0;			//开启下一次捕获
	}
	 EXTI_ClearITPendingBit(EXTI_Line5);          //清除LINE5上的中断标志位  
}

