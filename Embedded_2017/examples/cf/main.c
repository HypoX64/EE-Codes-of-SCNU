/****************************************************************************/
/*                                                                          */
/* FILE NAME                                      VERSION                   */
/*                                                                          */
/* CF.C                                            1.0                      */
/*                                                                          */
/* DESCRIPTION                                                              */
/*                                                                          */
/*     JXARM9-2410(S3C2410X)CF卡驱动实验                                    */
/*                                                                          */
/*                                                                          */
/* DATA STRUCTURES                                                          */
/*                                                                          */
/* FUNCTIONS :                                                              */
/*     在JXARM9-2410教学实验箱进行CF卡读写的实验                            */
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
/* 学习JXARM9-2410中CF卡操作函数的编写方法：                                */
/* 注意：                                                                   */
/*     1. 程序运行前请插入CF卡到CF卡座                                      */
/*     2. 请不要带电拔插CF卡                                                */
/*     3. 写CF卡操作将破坏CF卡中的数据，请小心实验，并备份您的数据          */
/****************************************************************************/

/* 包含文件 */
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
	
	/* 配置系统时钟 */
    ChangeClockDivider(1,1);          // 1:2:4    
    ChangeMPllValue(0xa1,0x3,0x1);    // FCLK=202.8MHz  
    
    /* 初始化端口 */
    Port_Init();
    
    /* 初始化串口 */
    Uart_Init(0,115200);
    Uart_Select(0);
    
    /* 打印提示信息 */
	PRINTF("\n---Compact Flash Card测试程序---\n请先将CF卡插入CF卡插座\n");

	memset(cf_cis_string, 0x0, 512);

	cf_init();
		
	// read cis
	/* 读取CF卡信息 */
	cf_read_cis(cf_cis_string);
	Uart_Printf("\nManufacturer Information Stored in CIS:\n");
	Uart_Printf(cf_cis_string);
	Uart_Printf("\n");
		
	/* 写数据到BLOCK0 */
	for(i=0; i<512; i++)
		cf_cis_string[i] = i;
	cf_memory_write_block(cf_cis_string, 0);
		
	while(1)
	{
		static int ncount = 0;
		Uart_Printf("ncount = %d\n", ncount);

	/* 读取CF卡ncount BLOCK的数据到cf_cis_string中，并打印 */
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
