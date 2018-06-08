/*
 * spi_cmd.h
 * Define the constant for the CAN's spi command interface
 * Date	: 2004/04/27
 * By	: Zhang Jing
 */

#ifndef	SPI_CMD_H
#define	SPI_CMD_H

#ifdef	SPI_CMD_FLAG
	#define	SPI_CMD_EXT
#else
	#define	SPI_CMD_EXT	extern
#endif

#include 	"2410addr.h"
#include 	"2410lib.h"
#include 	"def.h"

// Define the command constant
#define	SPI_CMD_READ			(0x03)
#define	SPI_CMD_WRITE			(0x02)

#define	SPI_CMD_RTS			(0x80)
#define	RTS_TXB0			(0x1)
#define	RTS_TXB1			(0x2)
#define	RTS_TXB2			(0x4)

#define	SPI_CMD_READSTA			(0xa0)
#define	SPI_CMD_BITMOD			(0x05)
#define	SPI_CMD_RESET			(0xc0)

// Define the spi module connected to can bus
#define	CAN_SPI_MODULE			S3C2410_SPI0
// Define the GPIO port and pin for chip select
#define	CAN_GPIO_PORT			MX1_GPIO_PC
#define	CAN_GPIO_PIN			15
// Define the value of unused argument
#define	ARG_UNUSED			0

// Function prototypes
SPI_CMD_EXT unsigned char CAN_SPI_CMD(unsigned char cmd, unsigned long addr, unsigned char arg1, unsigned char arg2);

#endif
