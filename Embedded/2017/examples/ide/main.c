/****************************************************************************/
/*                                                                          */
/* FILE NAME                                      VERSION                   */
/*                                                                          */
/* IDE.C                                            1.0                     */
/*                                                                          */
/* DESCRIPTION                                                              */
/*                                                                          */
/*     JXARM9-2410(S3C2410X)IDE驱动实验                                     */
/*                                                                          */
/*                                                                          */
/* DATA STRUCTURES                                                          */
/*                                                                          */
/* FUNCTIONS :                                                              */
/*     在JXARM9-2410教学实验箱进行IDE硬盘驱动的实验                         */
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
/* 学习JXARM9-2410中IDE驱动函数的编写方法：                                 */
/* 注意：                                                                   */
/*     1. 程序运行前请正确接入IDE硬盘，并通电，具体连接请阅读用户手册       */
/*     2. 请不要带电拔插IDE硬盘接口                                         */
/*     3. 写硬盘操作将破坏硬盘中的数据，请小心实验，并备份您的硬盘数据      */
/****************************************************************************/


/**************************************************************************
7.2  I/O Register Descriptions 

Communication to or from the drive is through an I/O Register that routes the 
input or output data to or from registers (selected) by a code on signals from 
the host (CS1FX-, CS3FX-, DA2, DA1, DA0, DIOR- and DIOW-). 

The Command Block Registers are used for sending commands to the drive or 
posting status from the drive. 

The Control Block Registers are used for drive control and to post alternate 
status. 

Table 7-1 lists these registers and the addresses that select them. 

Logic conventions are:   A = signal asserted
                         N = signal negated
                         x = does not matter which it is

            TABLE 7-1:  I/O PORT FUNCTIONS/SELECTION ADDRESSES 
 +-------------------------------+-----------------------------------------+
 |         Addresses             |                 Functions               |
 |CS1FX-|CS3FX-| DA2 | DA1 | DA0 |    READ (DIOR-)     |   WRITE (DIOW-)   |
 +------+------+-----+-----+-----+---------------------+-------------------+
 |                                        Control Block Registers          |
 +------+------+-----+-----+-----+---------------------+-------------------+
 |  N   |  N   |  x  |  x  |  x  | Data Bus High Imped | Not used          |
 |  N   |  A   |  0  |  x  |  X  | Data Bus High Imped | Not used          |
 |  N   |  A   |  1  |  0  |  x  | Data Bus High Imped | Not used          |
 |  N   |  A   |  1  |  1  |  0  | Alternate Status    | Device Control    | 
 |  N   |  A   |  1  |  1  |  1  | Drive Address       | Not used          |
 +------+------+-----+-----+-----+---------------------+-------------------+
 |                                        Command Block Registers          |
 +------+------+-----+-----+-----+---------------------+-------------------+
 |  A   |  N   |  0  |  0  |  0  | Data                | Data              |
 |  A   |  N   |  0  |  0  |  1  | Error Register      | Features          |
 |  A   |  N   |  0  |  1  |  0  | Sector Count        | Sector Count      |
 |  A   |  N   |  0  |  1  |  1  | Sector Number       | Sector Number     | 
 |  A   |  N   |  0  |  1  |  1  | * LBA Bits  0- 7    | * LBA Bits  0- 7  |
 |  A   |  N   |  1  |  0  |  0  | Cylinder Low        | Cylinder Low      |
 |  A   |  N   |  1  |  0  |  0  | * LBA Bits  8-15    | * LBA Bits  8-15  |
 |  A   |  N   |  1  |  0  |  1  | Cylinder High       | Cylinder High     | 
 |  A   |  N   |  1  |  0  |  1  | * LBA Bits 16-23    | * LBA Bits 16-23  |
 |  A   |  N   |  1  |  1  |  0  | Drive/Head          | Drive/Head        |
 |  A   |  N   |  1  |  1  |  0  | * LBA Bits 24-27    | * LBA Bits 24-27  |
 |  A   |  N   |  1  |  1  |  1  | Status              | Command           |
 |  A   |  A   |  x  |  x  |  x  | Invalid Address     | Invalid Address   |
 +------+------+-----+-----+-----+---------------------+-------------------+
                      * Mapping of registers in LBA Mode
**************************************************************************/

#include "def.h"
#include "2410lib.h"
#include "option.h"
#include "2410addr.h"
#include "interrupt.h"

void Main(void)
{
	unsigned short 	dd [256];   /* DiskData */
	unsigned short 	dd_off;     /* DiskData offset */
	unsigned long  	wait_loop;  /* Timeout loop */
	unsigned int 	base;       /* Base address of drive controller */
	unsigned char 	in_val;
    unsigned int 	i;	
	
	/* 配置系统时钟 */
    ChangeClockDivider(1,1);          // 1:2:4    
    ChangeMPllValue(0xa1,0x3,0x1);    // FCLK=202.8MHz  
    
    /* 初始化端口 */
    Port_Init();
    
    /* 初始化串口 */
    Uart_Init(0,115200);
    Uart_Select(0);
    
    /* 打印提示信息 */
	PRINTF("\n---IDE测试程序---\n请先将IDE硬盘插入IDE插座\n");

	// base address
    base = IDE_COMMAND_BASE;
    
    // set iois
    ide_iois_ctrl(0x0);
    Delay(10);
    
	// switch to command block registers
	ide_cs_ctrl(2);
	Delay(10);
	
	// reset
	ide_rst_ctrl(1);
	Delay(30);
	ide_rst_ctrl(0);
	Delay(50);
	ide_rst_ctrl(1);
	Delay(30);
	
	rBWSCON &= (~(0xf<<8));
	rBWSCON |= (0x01<<8);

	rBANKCON2 = 0x7ffc;	
	Delay(300);


	/* Wait for controller not busy */
	while (1)
	{
		in_val = inp (base + 14);
		Uart_Printf("in_val = 0x%x\n", in_val);
	
		if ((in_val & 0x80) != 0x80)
			break;
	}
			
	Delay(10);
	outp (base + 12, 0xA0);		
	Delay(10);
	outp (base + 14, 0xEC);          /* Get drive info data */
	Delay(50);	

	for (dd_off = 0; dd_off != 512; dd_off+=2) /* Read "sector" */
	{
		if(dd_off % 0x10 == 0)
			Uart_Printf("\n");
		dd[dd_off/2] = inw (base);
		Uart_Printf("%c %c ", dd[dd_off/2], dd[dd_off/2 + 1]);
	}

	Uart_Printf ("Model Number______________________: %s\n", getascii (dd, 27, 46));
	Uart_Printf ("Serial Number_____________________: %s\n", getascii (dd, 10, 19));
	Uart_Printf ("Controller Revision Number________: %s\n\n", getascii (dd, 23, 26));
		
	Uart_Printf ("Able to do Double Word Transfer___: %s\n", (dd [48] == 0 ? "No" : "Yes"));
	Uart_Printf ("Controller buffer size (bytes)____: %u\n", dd [21] * 512);
	Uart_Printf ("Transfer Speed____________________: ");
	if (dd [0] & 0x0400)
		Uart_Printf ("> 10 Mbit/sec\n");
	if (dd [0] & 0x0200)
		Uart_Printf ("5-10 Mbit/sec\n");
	if (dd [0] & 0x0100)
		Uart_Printf ("< 5 Mbit/sec\n");
	Uart_Printf ("\nDrive Type________________________: ");
	if (dd [0] & 0x0080)
		Uart_Printf ("Removable\n");
	if (dd [0] & 0x0040)
		Uart_Printf ("Fixed\n");
	Uart_Printf ("IORDY Supported___________________: %s\n", ((dd [49] & 0x0800) ? "Yes" : "No"));
	Uart_Printf ("Can IORDY be disabled by device___: %s\n", ((dd [49] & 0x0400) ? "Yes" : "No"));
	Uart_Printf ("LBA Mode supported________________: %s\n", ((dd [49] & 0x0200) ? "Yes" : "No"));
	Uart_Printf ("DMA Supported_____________________: %s\n", ((dd [49] & 0x0100) ? "Yes" : "No"));
	Uart_Printf ("Number of ECC bytes transferred___: %u\n", dd [22]);
	Uart_Printf ("Number of sectors per interrupt___: %u\n\n", dd [47] % 256);
	Uart_Printf ("Number of Cylinders_______________: %u\n", dd [1]);
	Uart_Printf ("Number of Heads___________________: %u\n", dd [3]);
	Uart_Printf ("Number of Sectors per Track_______: %u\n\n", dd [6]);
	 
 	Delay(100);
	
	Uart_Printf ("\nRead head %d clyn %d sec_num %d...\n", 0,0,2);
	ide_read_sector(1, 2, 0, 0, (unsigned char*)dd);
	dump_data((unsigned char*)dd, 512);

	Uart_Printf ("\nRead head %d clyn %d sec_num %d...\n", 0,0,1);
	ide_read_sector(1, 1, 0, 0, (unsigned char*)dd);
	dump_data((unsigned char*)dd, 512);
	
	for (dd_off = 0; dd_off != 256; dd_off+=1) /* Read "sector" */
	{
		dd[dd_off] = dd_off;
	}
			
	while(1);
    
	return;
}

