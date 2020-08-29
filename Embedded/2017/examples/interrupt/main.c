/* 包含文件 */
#include "def.h"
#include "2410lib.h"
#include "option.h"
#include "2410addr.h"
#include "interrupt.h"

/* functions */
void eint2_isr(void) __attribute__ ((interrupt("IRQ")));;
void eint3_isr(void) __attribute__ ((interrupt("IRQ")));;
void delay();

/* variables */
int dither_count2 = 0;
int dither_count3 = 0;
static int nLed = 0;

/*****************************************************************************
// Function name	: Main
// Description	    : JXARM9-2410 中断实验主程序
//                    完成功能:
//                        外部中断按键引发中断
// Return type		: void
// Argument         : void
*****************************************************************************/
void Main(void)
{
	/* 配置系统时钟 */
    ChangeClockDivider(1,1);          // 1:2:4    
    ChangeMPllValue(0xa1,0x3,0x1);    // FCLK=202.8MHz  
	
	/* 中断初始化 */
    Isr_Init();
    /* 初始化端口 */
    Port_Init();
    
    /* 初始化串口 */
    Uart_Init(0,115200);
    Uart_Select(0);

    /* 打印提示信息 */
	PRINTF("\n---外部中断测试程序---\n");
	PRINTF("\n请将UART0与PC串口进行连接，然后启动超级终端程序(115200, 8, N, 1)\n");
	PRINTF("\n外部中断测试开始\n");

	/* 请求中断 */
	Irq_Request(IRQ_EINT2, eint2_isr);
	Irq_Request(IRQ_EINT3, eint3_isr);

    /* 使能中断 */
    Irq_Enable(IRQ_EINT2);
    Irq_Enable(IRQ_EINT3);
       	
    dither_count2 = 0;
    dither_count3 = 0;
    while(1)
    {
    	delay();
    	dither_count2++;
    	dither_count3++;
    }
}

/*****************************************************************************
// Function name	: eint2_isr
// Description	    : EINT2中断处理程序
// Return type		: int
// Argument         : void
*****************************************************************************/
void eint2_isr(void)
{
	Irq_Clear(IRQ_EINT2);         

    if(dither_count2 > 5) 
    {
	   	dither_count2 = 0;
	
		Led_Display(nLed);

		nLed = (nLed ^ 0x01);
	}
}

/*****************************************************************************
// Function name	: eint3_isr
// Description	    : EINT3中断处理程序
// Return type		: int
// Argument         : void
*****************************************************************************/
void eint3_isr(void)
{
	Irq_Clear(IRQ_EINT3);        

    if(dither_count3 > 5) 
    {
	   	dither_count3 = 0;
	
		Led_Display(nLed);

		nLed = (nLed ^ 0x02);
	}
}

void delay()
{
	int index = 0; 
	
	for ( index = 0 ; index < 20000; index++);
}
