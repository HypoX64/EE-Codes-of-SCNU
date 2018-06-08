/* 包含文件 */
#include "def.h"
#include "2410lib.h"
#include "option.h"
#include "2410addr.h"
#include "interrupt.h"

/********************************************************************
// Function name	: Main
// Description	    : JXARM9-2410 RS485通信实验主程序
//                    实现功能：
//                        实现JXARM9-2410 RS485回环测试
//                        JXARM9-2410 UART0 <==> PC COM
// Return type		: void
// Argument         : void
*********************************************************************/
void Main(void)
{
	unsigned char data[6] = {0, 1, 2, 3, 4, 5};
	unsigned char ch = 'a';

	/* 配置系统时钟 */
    ChangeClockDivider(1,1);          // 1:2:4    
    ChangeMPllValue(0xa1,0x3,0x1);    // FCLK=202.8MHz  
    
    /* 初始化端口 */
    Port_Init();
    
    /* 初始化串口 */
    Uart_Init(0,115200);
    Uart_Select(0);
    
    /* 打印提示信息 */
	PRINTF("\n---RS485通讯程序(回环测试，请将主板上的JP12和JP13跳线接上)---\n");
	PRINTF("\n---在超级终端中输入数据，然后将该数据发送到RS485，RS485将数据回送到UART2，从UART2接收到数据后在UART0中进行显示---\n");
	
    /* 开始测试 */
    // Additional configuration for UART2 port
    rGPHCON&=0x3fafff;      // TXD2,RXD2

	while(1)
	{
		/* 从UART0获取数据 */				
    	Uart_Select(0);
		ch = Uart_Getch();  	
    	
    	/* 将接收到的数据发送到RS485 */
    	Uart_Select(2);
		Uart_SendByte(ch);  	

		/* 从RS485获取数据 */				
    	Uart_Select(2);
		ch = Uart_Getch();  	

		/* 将接收到的数据显示到UART0 */
	    Uart_Select(0);
		Uart_Printf("%c", ch);
	}
}

