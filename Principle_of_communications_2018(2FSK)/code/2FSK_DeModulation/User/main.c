#include "led.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "exti.h"

//���ӷ�����
//�������     ���ջ���        ��ע
//PA3��PN      none
//PA4:CLK      PC5:CLK      ʾ������CLK
//PA5:Output   PA0:Input 	ʾ����������/�ز�0/�ز�1  ��ͨ��key1�л���
//none		   PA3:PN_out   ʾ������������

#define OUT PAout(3)

//Ƶ�ʵ���	
#define clk_freq 200;
#define f0_freq 1000;
#define f1_freq 2000;

//�Ƿ���ҪCLK����
int needCLK=1;

int clk_arr=72000000/(71+1)/2/clk_freq;
int time_VPT;

extern u8  TIM2CH1_CAPTURE_STA;		//���벶��״̬		    				
extern u16	TIM2CH1_CAPTURE_VAL;	//���벶��ֵ


 int main(void)
 {	
	u32 temp=0; 
	time_VPT=1000000/2/f0_freq+1000000/2/f1_freq;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	delay_init();	    	 //��ʱ������ʼ��	
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	SIGNAL_GPIO_Init();
	 
	 if(needCLK==1)
	 {
		 EXTIX_Init();
	 }

 	TIM2_Cap_Init(0XFFFF,72-1);		//��1Mhz��Ƶ�ʼ��� 

   	while(1)
	{	 
		if(needCLK==0)
		{
			if(TIM2CH1_CAPTURE_STA&0X80)//�ɹ�������һ�θߵ�ƽ
			{
				temp=TIM2CH1_CAPTURE_STA&0X3F;
				temp*=65536;					//���ʱ���ܺ�
				temp+=TIM2CH1_CAPTURE_VAL;		//�õ��ܵĸߵ�ƽʱ��
				if(temp>time_VPT)
				{
					OUT=0;
				}
				else
				{
					OUT=1;
				}
				TIM2CH1_CAPTURE_STA=0;			//������һ�β���
			}
		
		}
		
	}
}

