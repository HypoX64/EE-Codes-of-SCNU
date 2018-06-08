/* �����ļ� */
#include "def.h"
#include "2410lib.h"
#include "option.h"
#include "2410addr.h"
#include "interrupt.h"

/********************************************************************
// Function name	: Main
// Description	    : JXARM9-2410 �������ʾʵ��������
// Return type		: void
// Argument         : void
*********************************************************************/
void Main(void)
{
	unsigned char data[6] = {0, 1, 2, 3, 4, 5};

	/* ����ϵͳʱ�� */
    ChangeClockDivider(1,1);          // 1:2:4    
    ChangeMPllValue(0xa1,0x3,0x1);    // FCLK=202.8MHz  
    
    /* ��ʼ���˿� */
    Port_Init();
    
    /* ��ʼ������ */
    Uart_Init(0,115200);
    Uart_Select(0);
    
    /* ��ӡ��ʾ��Ϣ */
	PRINTF("\n---�������ʾ����---\n");
	
    /* ��ʼ���� */
	while(1)
	{
		int i,loopcnt;
		
	    for(i=0;i<0x10;i++)
		{
			/* ���������� */
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

