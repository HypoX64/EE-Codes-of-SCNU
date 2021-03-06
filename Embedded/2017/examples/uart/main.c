/* 包含文件 */
#include "def.h"
#include "2410lib.h"
#include "option.h"
#include "2410addr.h"
#include "interrupt.h"

/********************************************************************
// Function name	: Main
// Description	    : JXARM9-2410 串口通信实验主程序
//                    实现功能：
//                        实现JXRAM9-2410与PC机的串口通讯
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

	PRINTF("\n---UART测试程序---\n");
	PRINTF("\n请将UART0与PC串口进行连接，然后启动超级终端程序(115200, 8, N, 1)\n");
	PRINTF("\n从现在开始您从超级中断发送的字符将被回显在超级终端上\n");
	
    /* 开始回环测试 */
	while(1)
	{
		unsigned char ch = 'a';
		
		ch = Uart_Getch();
		Uart_SendByte(ch);
		if(ch == 0x0d)
			Uart_SendByte(0x0a);
	}
}

