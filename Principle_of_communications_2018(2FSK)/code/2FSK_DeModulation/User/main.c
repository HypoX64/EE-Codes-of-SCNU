#include "led.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "exti.h"

//连接方法：
//发射机：     接收机：        备注
//PA3：PN      none
//PA4:CLK      PC5:CLK      示波器：CLK
//PA5:Output   PA0:Input 	示波器：调制/载波0/载波1  （通过key1切换）
//none		   PA3:PN_out   示波器：解调输出

#define OUT PAout(3)

//频率调整	
#define clk_freq 200;
#define f0_freq 1000;
#define f1_freq 2000;

//是否需要CLK输入
int needCLK=1;

int clk_arr=72000000/(71+1)/2/clk_freq;
int time_VPT;

extern u8  TIM2CH1_CAPTURE_STA;		//输入捕获状态		    				
extern u16	TIM2CH1_CAPTURE_VAL;	//输入捕获值


 int main(void)
 {	
	u32 temp=0; 
	time_VPT=1000000/2/f0_freq+1000000/2/f1_freq;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	delay_init();	    	 //延时函数初始化	
	LED_Init();		  	//初始化与LED连接的硬件接口
	SIGNAL_GPIO_Init();
	 
	 if(needCLK==1)
	 {
		 EXTIX_Init();
	 }

 	TIM2_Cap_Init(0XFFFF,72-1);		//以1Mhz的频率计数 

   	while(1)
	{	 
		if(needCLK==0)
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
		
		}
		
	}
}

