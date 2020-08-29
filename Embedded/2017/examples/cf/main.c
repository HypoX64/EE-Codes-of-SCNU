/****************************************************************************/
/*                                                                          */
/* FILE NAME                                      VERSION                   */
/*                                                                          */
/* CF.C                                            1.0                      */
/*                                                                          */
/* DESCRIPTION                                                              */
/*                                                                          */
/*     JXARM9-2410(S3C2410X)CF������ʵ��                                    */
/*                                                                          */
/*                                                                          */
/* DATA STRUCTURES                                                          */
/*                                                                          */
/* FUNCTIONS :                                                              */
/*     ��JXARM9-2410��ѧʵ�������CF����д��ʵ��                            */
/*                                                                          */
/* DEPENDENCIES                                                             */
/*     JXARM9-2410-1                                                        */
/*     JXARM9-2410-2                                                        */
/*     JXARM9-2410-3                                                        */
/*                                                                          */
/*                                                                          */
/* NAME:                                                                    */
/* REMARKS:                                                                 */
/*                                                                          */
/*								Copyright (C) 2003 Wuhan CVTECH CO.,LTD     */
/****************************************************************************/

/****************************************************************************/
/* ѧϰJXARM9-2410��CF�����������ı�д������                                */
/* ע�⣺                                                                   */
/*     1. ��������ǰ�����CF����CF����                                      */
/*     2. �벻Ҫ����β�CF��                                                */
/*     3. дCF���������ƻ�CF���е����ݣ���С��ʵ�飬��������������          */
/****************************************************************************/

/* �����ļ� */
#include "def.h"
#include "2410lib.h"
#include "option.h"
#include "2410addr.h"
#include "interrupt.h"

void Main()
{
	int i = 0;
	unsigned char cf_cis_string[512];
	unsigned char ch1, ch2, ch3, ch4;
	
	/* ����ϵͳʱ�� */
    ChangeClockDivider(1,1);          // 1:2:4    
    ChangeMPllValue(0xa1,0x3,0x1);    // FCLK=202.8MHz  
    
    /* ��ʼ���˿� */
    Port_Init();
    
    /* ��ʼ������ */
    Uart_Init(0,115200);
    Uart_Select(0);
    
    /* ��ӡ��ʾ��Ϣ */
	PRINTF("\n---Compact Flash Card���Գ���---\n���Ƚ�CF������CF������\n");

	memset(cf_cis_string, 0x0, 512);

	cf_init();
		
	// read cis
	/* ��ȡCF����Ϣ */
	cf_read_cis(cf_cis_string);
	Uart_Printf("\nManufacturer Information Stored in CIS:\n");
	Uart_Printf(cf_cis_string);
	Uart_Printf("\n");
		
	/* д���ݵ�BLOCK0 */
	for(i=0; i<512; i++)
		cf_cis_string[i] = i;
	cf_memory_write_block(cf_cis_string, 0);
		
	while(1)
	{
		static int ncount = 0;
		Uart_Printf("ncount = %d\n", ncount);

	/* ��ȡCF��ncount BLOCK�����ݵ�cf_cis_string�У�����ӡ */
		memset(cf_cis_string, 0x0, 512);
		cf_memory_read_block(cf_cis_string, ncount);
		{
			int loopcnt;
			for(loopcnt = 0; loopcnt < 512; loopcnt ++)
			{
				if(loopcnt % 0x10 == 0)
					Uart_Printf("\n");
				Uart_Printf("%02x ", cf_cis_string[loopcnt]);
			}	
			Uart_Printf("\n");
		}
		Uart_Getch();
		ncount++;
	}
	
	while(1);	/* dead here! */
}
