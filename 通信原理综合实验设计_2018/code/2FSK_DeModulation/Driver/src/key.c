#include "key.h"
#include "delay.h"

//ALIENTEK miniSTM32开发板
//KEY驱动代码	   
//修改日期:2017/2/10
//版本：V1.0
//@Hypo						   	    

/*
简介：初始化PC5和PA15为输入口,并使能这两个口的时钟
使用方法：调用  KEY_Init();  后
          GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)   //读取PC5的电平         
说明：开发板中KEY0  KEY1接地，为负逻辑    //KEY0   PC5    //KEY1   PA15     
             WK_UP     接VCC 为正逻辑    //WK_UP  PA0
*/
void KEY_Init(void)
{   
	GPIO_InitTypeDef GPIO_InitStructure;                                          //定义结构体GPIO_InitStructure
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);     //使能PORTA,PORTC时钟
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;                  //PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                //设置成上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		     //IO口速度为50MHz
 	GPIO_Init(GPIOA, &GPIO_InitStructure);                       //初始化GPIO A15
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;                   //PC5   //设置成上拉输入  //IO口速度为50MHz
 	GPIO_Init(GPIOC, &GPIO_InitStructure);                       //初始化GPIO C5
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;                   //PA0   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;                //设置成下拉输入  //IO口速度为50MHz
 	GPIO_Init(GPIOA, &GPIO_InitStructure);                       //初始化GPIO A0
	
	delay_init();                                                //初始化delay函数
	
}



/*
简介：模仿51风格进行键盘扫描
使用方法：调用   KEY_Scan(0);  // 不支持连按
				KEY_Scan(1);   //支持连按
说明：若无按键按下  return 0;
      若KEY0按下    return KEY0_PRES;
      若KEY1按下    return KEY1_PRES;  
      若WK_UP按下   return WKUP_PRES;
*/
u8 KEY_Scan(u8 mode)
{
	static u8 key_up=1;                  //按键按松开标志
	if(mode)key_up=1;                    //支持连按		  
	if(key_up &&(KEY0 == 0||KEY1 == 0||WK_UP==1))
	{
		delay_ms(10);                    //去抖动 
		key_up=0;
		if(KEY0==0)
			return KEY0_PRES;
		else if(KEY1==0)
			return KEY1_PRES;
		else if(WK_UP==1)
			return WKUP_PRES; 
	}
	else if(KEY0==1&&KEY1==1&&WK_UP==0)
		key_up=1; 	     
	return 0;                            // 无按键按下
	
}
