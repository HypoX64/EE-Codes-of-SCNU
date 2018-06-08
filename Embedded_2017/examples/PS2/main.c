/* 包含文件 */
#include "def.h"
#include "2410lib.h"
#include "option.h"
#include "2410addr.h"
#include "interrupt.h"

/********************************************************************
// Function name	: Test_PS2_Mouse
// Description	    : PS/2鼠标测试
// Return type		: void
// Argument         : void
*********************************************************************/
void Test_PS2_Mouse(void)
{
	PS2_Mouse_Init();

	while(1)
	{
		char ch;
		ch = PS2_Mouse_Get_Byte();
		Uart_Printf("From Mouse 0x%x\n", ch);
	}
}

/********************************************************************
// Function name	: Test_PS2_Keyboard
// Description	    : PS/2键盘测试
// Return type		: void
// Argument         : void
*********************************************************************/
void Test_PS2_Keyboard(void)
{
	PS2_KBD_Init();

	Delay(100);

	while(1)
	{
		char ch;
		ch = PS2_KBD_Get_Byte();
		PS2_KBD_Handle_Rawcode(ch);
	}
}

/********************************************************************
// Function name	: Main
// Description	    : JXARM9-2410 PS/2实验主程序
//                    实现功能：
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
	PRINTF("\n---PS/2测试程序---\n请先连接PS/2鼠标或者键盘到PS/2接口\n");
	
    /* 开始PS/2测试，修改此处的0为1将进行鼠标测试，否则将进行键盘测试 */
#if 1
    Test_PS2_Mouse();
#else
    Test_PS2_Keyboard();
#endif

	while(1)
	{
	}
}

