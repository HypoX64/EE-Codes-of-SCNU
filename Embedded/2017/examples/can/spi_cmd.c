/*

Module Name:	SPI_CMD.C

Abstract:		Function definition for the CAN's spi command interface
  
Notes:			Presently, only the SPI Channel 0 is supported.

Environment:	MCP2515

Date: 			2004/01/28

By: 			Li zhongmin
   
*/ 

#include 	"spi.h"
#include	"spi_cmd.h"

unsigned char CAN_SPI_CMD( unsigned char cmd, unsigned long addr, unsigned char arg1, unsigned char arg2 )
{
	unsigned char ret=0;
	unsigned char data=0;	

	// Empty the spi's transfer and receive buffer
	// SPI_TXFlush( CAN_SPI_MODULE );
	// SPI_RXFlush( CAN_SPI_MODULE );
	
	//StartSPIClock();
	rGPGDAT &= CHIP_SELECT_nSS0;

	switch( cmd ){
		case SPI_CMD_READ:
			
			ret = SPI_SendByte(SPI_CMD_READ, &data);
			ret = SPI_SendByte(addr, &data);			
			ret = SPI_SendByte(0xff, &data);	
			
			break;
			
		case SPI_CMD_WRITE:
		
			ret = SPI_SendByte(SPI_CMD_WRITE, &data);
			ret = SPI_SendByte(addr, &data);
			ret = SPI_SendByte(arg1, &data);	
						
			break;
		case SPI_CMD_RTS:
			
			ret = SPI_SendByte(SPI_CMD_RTS, &data);
			
			break;
		case SPI_CMD_READSTA:
			
			ret = SPI_SendByte(SPI_CMD_READSTA, &data);
			ret = SPI_SendByte(0xff, &data);			
			
			break;
		case SPI_CMD_BITMOD:
			
			ret = SPI_SendByte(SPI_CMD_BITMOD, &data);
			ret = SPI_SendByte(addr, &data);
			ret = SPI_SendByte(arg1, &data);	
			ret = SPI_SendByte(arg2, &data);				
			
			break;
		case SPI_CMD_RESET:
			ret = SPI_SendByte(SPI_CMD_RESET, &data);
			break;
		default:
			ret = 0x30;										// any value is ok
	}
	
	rGPGDAT |= CHIP_DESELECT_nSS0;
 	//StopSPIClock();
			 
	//SPI_RXFlush( CAN_SPI_MODULE );
	
	return data;
}
