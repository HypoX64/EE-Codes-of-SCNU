/*
 * mcp2510.c
 * Common Function Definition for mcp2510 CAN Controller
 * Date	: 2004/04/29
 * By	: Zhang Jing
 */

#define	MCP2510_FLAG
#include	"mcp2510.h"
#include	"spi_cmd.h"
#include    "spi.h"

/* Initialize the mcp2510 */
void MCP2510_Init( void )
{
	// Configure the SPI Interface in MX1
	SPI_Init( ); 
	// Configure the mcp2510 through spi interface

	// Reset controller
	CAN_SPI_CMD( SPI_CMD_RESET, ARG_UNUSED, ARG_UNUSED, ARG_UNUSED );
	
	CAN_SPI_CMD( SPI_CMD_BITMOD, TOLONG(&(MCP2510_MAP->CANCTRL)), 0xe0, 0x80 );		// LOOP BACK MODE
	
	// make sure we are in configuration mode
	while( (CAN_SPI_CMD( SPI_CMD_READ, TOLONG(&(MCP2510_MAP->CANSTAT)), ARG_UNUSED, ARG_UNUSED )>>5)!=0x04 );
	// start configuration
	CAN_SPI_CMD( SPI_CMD_WRITE, TOLONG(&(MCP2510_MAP->BFPCTRL)), 	BFPCTRL_INIT_VAL, 	ARG_UNUSED);
	CAN_SPI_CMD( SPI_CMD_WRITE, TOLONG(&(MCP2510_MAP->TXRTSCTRL)), 	TXRTSCTRL_INIT_VAL, ARG_UNUSED);
	CAN_SPI_CMD( SPI_CMD_WRITE, TOLONG(&(MCP2510_MAP->CNF3)), 		CNF3_INIT_VAL, 		ARG_UNUSED);
	CAN_SPI_CMD( SPI_CMD_WRITE, TOLONG(&(MCP2510_MAP->CNF2)), 		CNF2_INIT_VAL, 		ARG_UNUSED);
	CAN_SPI_CMD( SPI_CMD_WRITE, TOLONG(&(MCP2510_MAP->CNF1)),		CNF1_INIT_VAL, 		ARG_UNUSED);
	CAN_SPI_CMD( SPI_CMD_WRITE, TOLONG(&(MCP2510_MAP->CANINTE)),	CANINTE_INIT_VAL, 	ARG_UNUSED);
	CAN_SPI_CMD( SPI_CMD_WRITE, TOLONG(&(MCP2510_MAP->CANINTF)), 	CANINTF_INIT_VAL, 	ARG_UNUSED);
	CAN_SPI_CMD( SPI_CMD_WRITE, TOLONG(&(MCP2510_MAP->EFLG)), 		EFLG_INIT_VAL, 		ARG_UNUSED);
	CAN_SPI_CMD( SPI_CMD_WRITE, TOLONG(&(MCP2510_MAP->TXB0CTRL)), 	TXBnCTRL_INIT_VAL, 	ARG_UNUSED);
	CAN_SPI_CMD( SPI_CMD_WRITE, TOLONG(&(MCP2510_MAP->TXB1CTRL)), 	TXBnCTRL_INIT_VAL, 	ARG_UNUSED);
	CAN_SPI_CMD( SPI_CMD_WRITE, TOLONG(&(MCP2510_MAP->TXB2CTRL)), 	TXBnCTRL_INIT_VAL, 	ARG_UNUSED);
	CAN_SPI_CMD( SPI_CMD_WRITE, TOLONG(&(MCP2510_MAP->RXB0CTRL)), 	RXB1CTRL_INIT_VAL, 	ARG_UNUSED);
	CAN_SPI_CMD( SPI_CMD_WRITE, TOLONG(&(MCP2510_MAP->RXB1CTRL)), 	RXB1CTRL_INIT_VAL, 	ARG_UNUSED);
	
	// switch to normal mode or loopback mode ( for testing)
	//CAN_SPI_CMD( SPI_CMD_BITMOD, TOLONG(&(MCP2510_MAP->CANCTRL)), 0xe0, 0x40 );		// LOOP BACK MODE
	CAN_SPI_CMD( SPI_CMD_BITMOD, TOLONG(&(MCP2510_MAP->CANCTRL)), 0xe0, 0x00 );	// NORMAL OPERATION MODE
	
	// Flush the MX1 SPI receive buffer
	
	CAN_SPI_CMD( SPI_CMD_READ, TOLONG(&(MCP2510_MAP->CANSTAT)), ARG_UNUSED, ARG_UNUSED );
}
/* Transmit data */
/*
 TxBuf	: select the transmit buffer( 0=buffer0 or 1=buffer1 2=buffer2 )
 IdType	: 0=standard id or 1=extended id
 id	: frame identifier
 DataLen	: the number of byte
 data	: the pointer to data byte
*/
void MCP2510_TX( int TxBuf, int IdType, unsigned int id, int DataLen, char * data )
{
	int i, offset;

	switch( TxBuf ){
		case TXBUF0:
			offset = 0;
			break;
		case TXBUF1:
			offset = 0x10;
			break;
		case TXBUF2:
			offset = 0x20;
			break;
	}
	// Set the frame identifier
	if( IdType==STANDID ){
		CAN_SPI_CMD( SPI_CMD_WRITE, TOLONG(&(MCP2510_MAP->TXB0SIDL))+offset, (id&0x7)<<5, ARG_UNUSED );
		CAN_SPI_CMD( SPI_CMD_WRITE, TOLONG(&(MCP2510_MAP->TXB0SIDH))+offset, (id>>3)&0xff, ARG_UNUSED );
	}else if( IdType==EXTID ){
		CAN_SPI_CMD( SPI_CMD_WRITE, TOLONG(&(MCP2510_MAP->TXB0EID0))+offset, id&0xff, ARG_UNUSED );
		CAN_SPI_CMD( SPI_CMD_WRITE, TOLONG(&(MCP2510_MAP->TXB0EID8))+offset, (id>>8)&0xff, ARG_UNUSED );			CAN_SPI_CMD( SPI_CMD_WRITE, TOLONG(&(MCP2510_MAP->TXB0SIDL)), ((id>>16)&0x3)|0x08, ARG_UNUSED );
	}
	// Set the data length
	CAN_SPI_CMD( SPI_CMD_WRITE, TOLONG(&(MCP2510_MAP->TXB0DLC))+offset, DataLen, ARG_UNUSED );
	// fill the data
	if( DataLen>8 )
		DataLen = 8;
	for( i=0; i<DataLen; i++ ){
		CAN_SPI_CMD( SPI_CMD_WRITE, TOLONG(&(MCP2510_MAP->TXB0D0))+offset+i, data[i], ARG_UNUSED );
	}
	// initiate transmit
	while( CAN_SPI_CMD( SPI_CMD_READ, TOLONG(&(MCP2510_MAP->TXB0CTRL))+offset, ARG_UNUSED, ARG_UNUSED )&0x08 );
	CAN_SPI_CMD( SPI_CMD_BITMOD, TOLONG(&(MCP2510_MAP->TXB0CTRL))+offset, 0x08, 0x08 );
}

/* Receive data */
/*
 * RxBuf		: The receive buffer from which the data is get
 * IdType		: Identifier type of the data frame ( STANDID, EXTID )
 * id		: The identifier of the received frame
 * DataLen	: The number of bytes received
 * data		: The received data
 */
void MCP2510_RX( int RxBuf, int *IdType, unsigned int *id, int *DataLen, char *data )
{
	unsigned int flag;
	int offset, i;
	
	switch( RxBuf ){
		case RXBUF0:
			flag = 0x1;
			offset = 0x00;
			break;
		case RXBUF1:
			flag = 0x2;
			offset = 0x10;
			break;
	}
	// wait for a frame to com
	while( !(CAN_SPI_CMD( SPI_CMD_READ, TOLONG(&(MCP2510_MAP->CANINTF)), ARG_UNUSED, ARG_UNUSED )&flag) );
	// Get the identifier
	if( CAN_SPI_CMD( SPI_CMD_READ, TOLONG(&(MCP2510_MAP->RXB0SIDL))+offset, ARG_UNUSED, ARG_UNUSED )&0x08 ){
		// Extended identifier
		if( IdType )
			*IdType = EXTID;
		if( id ){
			*id = (CAN_SPI_CMD( SPI_CMD_READ, TOLONG(&(MCP2510_MAP->RXB0SIDL))+offset, ARG_UNUSED, ARG_UNUSED )&0x3)<<16;
			*id |= (CAN_SPI_CMD( SPI_CMD_READ, TOLONG(&(MCP2510_MAP->RXB0EID8))+offset, ARG_UNUSED, ARG_UNUSED ))<<8;
			*id |= (CAN_SPI_CMD( SPI_CMD_READ, TOLONG(&(MCP2510_MAP->RXB0EID0))+offset, ARG_UNUSED, ARG_UNUSED ));
		}
	}else{
		// Standard identifier
		if( IdType )
			*IdType = STANDID;
		if( id ){
			*id = (CAN_SPI_CMD( SPI_CMD_READ, TOLONG(&(MCP2510_MAP->RXB0SIDH))+offset, ARG_UNUSED, ARG_UNUSED ))<<3;
			*id |= (CAN_SPI_CMD( SPI_CMD_READ, TOLONG(&(MCP2510_MAP->RXB0SIDL))+offset, ARG_UNUSED, ARG_UNUSED ))>>5;
		}
	}
	// Get the data frame lenth
	if( DataLen )
		*DataLen = (CAN_SPI_CMD( SPI_CMD_READ, TOLONG(&(MCP2510_MAP->RXB0DLC))+offset, ARG_UNUSED, ARG_UNUSED )&0xf);
	// Get the data
	for( i=0; DataLen&&(i<*DataLen)&&data; i++ ){
		data[i] = CAN_SPI_CMD( SPI_CMD_READ, TOLONG(&(MCP2510_MAP->RXB0D0))+offset+i, ARG_UNUSED, ARG_UNUSED );
	}
	// clear the receive int flag
	CAN_SPI_CMD( SPI_CMD_BITMOD, TOLONG(&(MCP2510_MAP->CANINTF)), flag, 0x00 );
	
}
