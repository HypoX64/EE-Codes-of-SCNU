/* 包含文件 */
#include "def.h"
#include "2410lib.h"
#include "option.h"
#include "2410addr.h"
#include "interrupt.h"

/* 函数声明 */
void test_pwm();

/********************************************************************
// Function name	: Main
// Description	    : JXARM9-2410 PWM实验主程序
//                    实现功能：
//                        实现JXARM9-2410 PWM方式控制蜂鸣器
// Return type		: void
// Argument         : void
*********************************************************************/
void Main(void)
{
	unsigned char data[6] = {0, 1, 2, 3, 4, 5};

	/* 配置系统时钟 */
    ChangeClockDivider(1,1);          // 1:2:4    
    ChangeMPllValue(0xa1,0x3,0x1);    // FCLK=202.8MHz  
    
    /* 初始化端口 */
    Port_Init();
    
    /* 初始化串口 */
    Uart_Init(0,115200);
    Uart_Select(0);
    
    /* 打印提示信息 */
	PRINTF("\n---蜂鸣器测试程序---\n");
	
	/* 端口设置 */
	rGPBUP  = rGPBUP  & ~(0x1f)     | 0x1f;         //GPB4 ~ 0
    rGPBCON = rGPBCON & ~(0x3ff)    | 0x2aa;        //Function Setting TCLK0, TOUT3 ~ 0   
    rGPGUP  = rGPGUP  & ~(0x800)    | 0x800;        //GPG11
    rGPGCON = rGPGCON & ~(0xc00000) | 0xc00000;     //TCLK1
    rGPHUP  = rGPHUP  & ~(0x200)    | 0x200;        //GPH9
    rGPHCON = rGPHCON & ~(0x3<<18)  | (0x2<<18);    //CLKOUT0    
    rMISCCR = rMISCCR & ~(0xf0)     | 0x40;         //Select PCLK with CLKOUT0
    
    /* 开始测试 */
	test_pwm();
	while(1);
}

/*****************************************************************************
// Function name	: test_pwm
// Description	    : 测试PWM，通过蜂鸣器输出脉冲
// Return type		: int
// Argument         : void
*****************************************************************************/
void test_pwm()
{
	int index, rate ;
	unsigned short div;
	int freq;
	
	/* 设置定时器的预分频率值:TIME0/1=255, TIME2/3=0, TIME4/5=0				*/
    rTCFG0=0xFF; 	
    
    /* 设置定时器的工作模式:中断模式,设置分频率值:TIME0为1/4，其他为1/2		*/
    rTCFG1=0x1;	 	

    /* 输出脉冲：频率从4000HZ到14000HZ, 使用2/3的占空比						*/
	for ( freq = 500; freq < 14000; freq+=500 )
	{
		div = (PCLK/256/4)/freq;
    	rTCON=0x0;
     	rTCNTB0= div;
   		rTCMPB0= (2*div)/3;
		rTCON=0xa;						/* 手工装载定时器的计数值			*/
    	rTCON=0x9;						/* 启动定时器，并周期模式触发		*/
    	for( index = 0; index < 800000; index++);
    	rTCON=0x0;						/* 延时并停止定时器					*/
	}

    /* 输出脉冲：频率1000HZ, 使用1/100 - 95/100的占空比						*/
	div = (PCLK/256/4)/1000;
    for ( rate = 1; rate < 100; rate += 5 )
    {
    	rTCNTB0= div;
		rTCMPB0= (rate*div)/100;		/* 修改占空比						*/
		rTCON=0xa;						/* 手工装载定时器的计数值			*/
	    rTCON=0x9;						/* 启动定时器，并周期触发			*/
	    for( index = 0; index < 800000; index++);
	    rTCON=0x0;
    }
}
