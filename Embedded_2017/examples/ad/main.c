/* 包含文件 */
#include "def.h"
#include "2410lib.h"
#include "option.h"
#include "2410addr.h"
#include "interrupt.h"

/********************************************************************
// Function name	: Main
// Description	    : JXARM9-2410 A/D采样实验主程序
//                    实现功能：
//                        实现JXRAM9-2410的模数转换
//                        JXARM9-2410 UART0 <==> PC COM
// Return type		: void
// Argument         : void
*********************************************************************/
void Main(void)
{
	/* 配置系统时钟 */
    ChangeClockDivider(1,1);          // 1:2:4    
    ChangeMPllValue(0xa1,0x3,0x1);    // FCLK=202.8MHz  
    
    /* 初始化端口 */
    Port_Init();
    
    /* 初始化串口 */
    Uart_Init(0,115200);
    Uart_Select(0);
    
    /* 打印提示信息 */
	PRINTF("\n---AD采样程序---\n");
	PRINTF("\n请将UART0与PC串口进行连接，然后启动超级终端程序(115200, 8, N, 1)\n");
	PRINTF("\n从现在开始您将在超级终端上看到采样值，旋动旋钮AIN2和AIN3改变模拟输入\n");
	
    /* 开始测试 */
    Test_Adc();
	while(1)
	{
	}
}

#define ADC_FREQ 2500000

int ReadAdc(int ch);	        //Return type is int, Declare Prototype function

//==================================================================================
void Test_Adc(void)
{
    int i;
    int a0=0,a1=0,a2=0,a3=0,a4=0,a5=0,a6=0,a7=0; //Initialize variables
    
    PRINTF("----------AD测试--------\n");
    PRINTF("旋动AIN0, AIN1旋钮改变模拟输入,任意键退出\n");
        
    while(1)
    {
	    a0=Adc_Get_Data(0, ADC_FREQ);
	    a1=Adc_Get_Data(1, ADC_FREQ);

	    PRINTF("\rAIN0: %04d AIN1: %04d", a0,a1);
    }
    rADCCON=(0<<14)|(19<<6)|(7<<3)|(1<<2);  //stand by mode to reduce power consumption	

	PRINTF("\n");
    PRINTF("--------AD测试结束------\n\n");
}







