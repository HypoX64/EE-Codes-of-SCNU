#include "led.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "dma.h"
#include "key.h"
#include "exti.h"

//连接方法：
//发射机：     接收机：        备注
//PA3：PN      none
//PA4:CLK      PC5:CLK      示波器：CLK
//PA5:Output   PA0:Input 	示波器：调制/载波0/载波1  （通过key1切换）
//none		   PA3:PN_out   示波器：解调输出

//DAC输出采样点：32

//频率调整
#define clk_freq 200;
#define f0_freq 1000;
#define f1_freq 2000;

//输出序列调整
u8 PN_array[8]={1,0,0,1,1,0,1,0};
u8 PN_array_length=8;

int clk_arr=72000000/(71+1)/2/clk_freq;
int f0_arr=72000000/32/f0_freq;
int f1_arr=72000000/32/f1_freq;
extern int PN_signal ;
extern int mode;

 int main(void)
 {	
	 
	delay_init();	    	 //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	LED_Init();		  	//初始化与LED连接的硬件接口
	KEY_Init();
	SIGNAL_GPIO_Init();
	EXTIX_Init();
 	TIM3_Int_Init(clk_arr,71);
	 
	SinData_Init();
	DMAx_Init();
	 
	TIM2_DAC_Init(f1_arr,0);
   	while(1)
	{
		if(mode==0)
		{
			if(PN_signal == 1)  
			{  
				TIM2->ARR = f1_arr;
			}  
			else 
			{  
				TIM2->ARR = f0_arr;
			}   
		}
		else if(mode==1)
		{
			TIM2->ARR = f0_arr;	
		}
		else
		{
			TIM2->ARR = f1_arr;	
		}
	
	}
}



