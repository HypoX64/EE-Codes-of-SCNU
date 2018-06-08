/* �����ļ� */
#include "spi_cmd.h"
#include "mcp2510.h"
#include "def.h"
#include "2410lib.h"
#include "option.h"
#include "2410addr.h"
#include "interrupt.h"

void LedOn()
{
	rGPGDAT &= ~0x100;
}


void LedOff()
{
	rGPGDAT |= 0x100;
}

/* ��ʼ���󣬴����￪ʼִ��C���� */
int Main( void )
{	
	int idType, datalen;
	unsigned int id;
	char data[9];
	char tmp[]="abcdefgh";
	
	/* ����ϵͳʱ�� */
    ChangeClockDivider(1,1);          // 1:2:4    
    ChangeMPllValue(0xa1,0x3,0x1);    // FCLK=202.8MHz  
    
    /* ��ʼ���˿� */
    Port_Init();
    
    /* ��ʼ������ */
    Uart_Init(0,115200);
    Uart_Select(0);
    
    /* ��ӡ��ʾ��Ϣ */
	PRINTF("\n---can���߲��Գ���---\n");
	PRINTF("\n�뽫UART0��PC���ڽ������ӣ�Ȼ�����������ն˳���(115200, 8, N, 1)\n");

	MCP2510_Init();
	
	datalen = 0;
	id = 0;
	idType = 0;
	
	
	while(1)
	{	
		MCP2510_Init();
		
		PRINTF("Can Test ...\n");
	   	LedOn();
    	Delay(5000);
		MCP2510_TX( TXBUF0, STANDID, 23, 8, tmp );
    	LedOff();
    	Delay(5000);    	
	}
	
	//MCP2510_TX( TXBUF0, STANDID, 23, 8, tmp );
	//MCP2510_TX( TXBUF1, STANDID, 23, 8, tmp );
	//MCP2510_TX( TXBUF2, STANDID, 23, 8, tmp );
	
	while(1)
	{
		MCP2510_RX( RXBUF0, &idType, &id, &datalen, data );
		
		if((datalen!=8)||(id!=23)||(idType!=STANDID))
		{
			// Error
			while(1);
		}
		
		for( datalen = 0; datalen < 8; datalen++)
		{
			if(tmp[datalen]!=data[datalen])
			{
				while(1);
			}
		}
	}
	
	while(1);
	
	return 0;
}
