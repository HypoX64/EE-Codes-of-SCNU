/* 包含文件 */
#include "def.h"
#include "2410lib.h"
#include "option.h"
#include "2410addr.h"
#include "interrupt.h"

/********************************************************************
// Function name	: Main
// Description	    : JXARM9-2410 数码管显示实验主程序
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
	PRINTF("\n---数码管显示程序---\n");
	
    /* 开始测试 */
	while(1)
	{
		int i,loopcnt;
		
	    for(i=0;i<0x10;i++)
		{
			/* 查表并输出数据 */
			Seg7_Display(0x01, data);
			for(loopcnt = 0; loopcnt < 6; loopcnt++)
			{
				data[loopcnt] ++;
				data[loopcnt] &= 0xf; 
			}
			Delay(100);
   		}
   	}
}

