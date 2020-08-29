/* �����ļ� */
#include "def.h"
#include "2410lib.h"
#include "option.h"
#include "2410addr.h"
#include "interrupt.h"

/********************************************************************
// Function name	: Test_PS2_Mouse
// Description	    : PS/2������
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
// Description	    : PS/2���̲���
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
// Description	    : JXARM9-2410 PS/2ʵ��������
//                    ʵ�ֹ��ܣ�
// Return type		: void
// Argument         : void
*********************************************************************/
void Main(void)
{
	/* ����ϵͳʱ�� */
    ChangeClockDivider(1,1);          // 1:2:4    
    ChangeMPllValue(0xa1,0x3,0x1);    // FCLK=202.8MHz  
    
    /* ��ʼ���˿� */
    Port_Init();
    
    /* ��ʼ������ */
    Uart_Init(0,115200);
    Uart_Select(0);
    
    /* ��ӡ��ʾ��Ϣ */
	PRINTF("\n---PS/2���Գ���---\n��������PS/2�����߼��̵�PS/2�ӿ�\n");
	
    /* ��ʼPS/2���ԣ��޸Ĵ˴���0Ϊ1�����������ԣ����򽫽��м��̲��� */
#if 1
    Test_PS2_Mouse();
#else
    Test_PS2_Keyboard();
#endif

	while(1)
	{
	}
}

