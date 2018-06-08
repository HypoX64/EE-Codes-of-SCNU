/* �����ļ� */
#include "def.h"
#include "2410lib.h"
#include "option.h"
#include "2410addr.h"
#include "interrupt.h"

/********************************************************************
// Function name	: Main
// Description	    : JXARM9-2410 RS485ͨ��ʵ��������
//                    ʵ�ֹ��ܣ�
//                        ʵ��JXARM9-2410 RS485�ػ�����
//                        JXARM9-2410 UART0 <==> PC COM
// Return type		: void
// Argument         : void
*********************************************************************/
void Main(void)
{
	unsigned char data[6] = {0, 1, 2, 3, 4, 5};
	unsigned char ch = 'a';

	/* ����ϵͳʱ�� */
    ChangeClockDivider(1,1);          // 1:2:4    
    ChangeMPllValue(0xa1,0x3,0x1);    // FCLK=202.8MHz  
    
    /* ��ʼ���˿� */
    Port_Init();
    
    /* ��ʼ������ */
    Uart_Init(0,115200);
    Uart_Select(0);
    
    /* ��ӡ��ʾ��Ϣ */
	PRINTF("\n---RS485ͨѶ����(�ػ����ԣ��뽫�����ϵ�JP12��JP13���߽���)---\n");
	PRINTF("\n---�ڳ����ն����������ݣ�Ȼ�󽫸����ݷ��͵�RS485��RS485�����ݻ��͵�UART2����UART2���յ����ݺ���UART0�н�����ʾ---\n");
	
    /* ��ʼ���� */
    // Additional configuration for UART2 port
    rGPHCON&=0x3fafff;      // TXD2,RXD2

	while(1)
	{
		/* ��UART0��ȡ���� */				
    	Uart_Select(0);
		ch = Uart_Getch();  	
    	
    	/* �����յ������ݷ��͵�RS485 */
    	Uart_Select(2);
		Uart_SendByte(ch);  	

		/* ��RS485��ȡ���� */				
    	Uart_Select(2);
		ch = Uart_Getch();  	

		/* �����յ���������ʾ��UART0 */
	    Uart_Select(0);
		Uart_Printf("%c", ch);
	}
}

