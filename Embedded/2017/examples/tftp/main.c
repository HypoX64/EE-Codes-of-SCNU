/* 包含文件 */
#include "def.h"
#include "2410lib.h"
#include "option.h"
#include "2410addr.h"
#include "interrupt.h"

extern int data_len;

/********************************************************************
// Function name	: Main
// Description	    : JXARM9-2410 tftp通信实验主程序
// Return type		: void
// Argument         : void
*********************************************************************/
void Main(void)
{
	unsigned char *ip_s;
	unsigned long ip;

	/* 配置系统时钟 */
    ChangeClockDivider(1,1);          // 1:2:4    
    ChangeMPllValue(0xa1,0x3,0x1);    // FCLK=202.8MHz  
    
    /* 初始化端口 */
    Port_Init();
    
    /* 初始化串口 */
    Uart_Init(0,115200);
    Uart_Select(0);
    
    /* 打印提示信息 */
	PRINTF("\n---tftp测试程序---\n");
	PRINTF("\n请将UART0与PC串口进行连接，然后启动超级终端程序(115200, 8, N, 1)\n");
		
	ip_s=(unsigned char *)&ip;
	ip_s[3]=192;	
	ip_s[2]=168;
	ip_s[1]=1;
	ip_s[0]=46;
	
	tftp_main(ip, 0x30100000);
	
	Uart_Printf("\ntotal = %d bytes.\r", data_len);
	while(1)
	{
	}
}

