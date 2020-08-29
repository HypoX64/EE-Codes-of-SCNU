/*
 * mcp2510.h
 * Register Map and Constant Definition of MCP2510 CAN Controller
 * Date	: 2004/04/29
 * By	: Zhang Jing
 */

#ifndef	MCP2510_H
#define	MCP2510_H

#ifdef	MCP2510_FLAG
	#define	MCP2510_EXT
#else
	#define	MCP2510_EXT	extern
#endif

typedef	volatile unsigned char	mcp2510_reg;

typedef	struct struct_mcp2510_map{
	// x000 xxxx
	mcp2510_reg	RXF0SIDH;
	mcp2510_reg	RXF0SIDL;
	mcp2510_reg	RXF0EID8;
	mcp2510_reg	RXF0EID0;
	mcp2510_reg	RXF1SIDH;
	mcp2510_reg	RXF1SIDL;
	mcp2510_reg	RXF1EID8;
	mcp2510_reg	RXF1EID0;
	mcp2510_reg	RXF2SIDH;
	mcp2510_reg	RXF2SIDL;
	mcp2510_reg	RXF2EID8;
	mcp2510_reg	RXF2EID0;
	mcp2510_reg	BFPCTRL;
	mcp2510_reg	TXRTSCTRL;
	mcp2510_reg	CANSTAT;
	mcp2510_reg	CANCTRL;
	// x001 xxxx
	mcp2510_reg	RXF3SIDH;
	mcp2510_reg	RXF3SIDL;
	mcp2510_reg	RXF3EID8;
	mcp2510_reg	RXF3EID0;
	mcp2510_reg	RXF4SIDH;
	mcp2510_reg	RXF4SIDL;
	mcp2510_reg	RXF4EID8;
	mcp2510_reg	RXF4EID0;
	mcp2510_reg	RXF5SIDH;
	mcp2510_reg	RXF5SIDL;
	mcp2510_reg	RXF5EID8;
	mcp2510_reg	RXF5EID0;
	mcp2510_reg	TEC;
	mcp2510_reg	REC;
	mcp2510_reg	CANSTAT_x001;	// refer to the same register CANSTAT
	mcp2510_reg	CANCTRL_x001;	// refer to the same register CANCTRL
	// x010 xxxx
	mcp2510_reg	RXM0SIDH;
	mcp2510_reg	RXM0SIDL;
	mcp2510_reg	RXM0EID8;
	mcp2510_reg	RXM0EID0;
	mcp2510_reg	RXM1SIDH;
	mcp2510_reg	RXM1SIDL;
	mcp2510_reg	RXM1EID8;
	mcp2510_reg	RXM1EID0;
	mcp2510_reg	CNF3;
	mcp2510_reg	CNF2;
	mcp2510_reg	CNF1;
	mcp2510_reg	CANINTE;
	mcp2510_reg	CANINTF;
	mcp2510_reg	EFLG;
	mcp2510_reg	CANSTAT_x010;
	mcp2510_reg	CANCTRL_x010;
	// x011 xxxx
	mcp2510_reg	TXB0CTRL;
	mcp2510_reg	TXB0SIDH;
	mcp2510_reg	TXB0SIDL;
	mcp2510_reg	TXB0EID8;
	mcp2510_reg	TXB0EID0;
	mcp2510_reg	TXB0DLC;
	mcp2510_reg	TXB0D0;
	mcp2510_reg	TXB0D1;
	mcp2510_reg	TXB0D2;
	mcp2510_reg	TXB0D3;
	mcp2510_reg	TXB0D4;
	mcp2510_reg	TXB0D5;
	mcp2510_reg	TXB0D6;
	mcp2510_reg	TXB0D7;
	mcp2510_reg	CANSTAT_x011;
	mcp2510_reg	CANCTRL_x011;
	// x100 xxxx
	mcp2510_reg	TXB1CTRL;
	mcp2510_reg	TXB1SIDH;
	mcp2510_reg	TXB1SIDL;
	mcp2510_reg	TXB1EID8;
	mcp2510_reg	TXB1EID0;
	mcp2510_reg	TXB1DLC;
	mcp2510_reg	TXB1D0;
	mcp2510_reg	TXB1D1;
	mcp2510_reg	TXB1D2;
	mcp2510_reg	TXB1D3;
	mcp2510_reg	TXB1D4;
	mcp2510_reg	TXB1D5;
	mcp2510_reg	TXB1D6;
	mcp2510_reg	TXB1D7;
	mcp2510_reg	CANSTAT_x100;
	mcp2510_reg	CANCTRL_x100;
	// x101 xxxx
	mcp2510_reg	TXB2CTRL;
	mcp2510_reg	TXB2SIDH;
	mcp2510_reg	TXB2SIDL;
	mcp2510_reg	TXB2EID8;
	mcp2510_reg	TXB2EID0;
	mcp2510_reg	TXB2DLC;
	mcp2510_reg	TXB2D0;
	mcp2510_reg	TXB2D1;
	mcp2510_reg	TXB2D2;
	mcp2510_reg	TXB2D3;
	mcp2510_reg	TXB2D4;
	mcp2510_reg	TXB2D5;
	mcp2510_reg	TXB2D6;
	mcp2510_reg	TXB2D7;
	mcp2510_reg	CANSTAT_x101;
	mcp2510_reg	CANCTRL_x101;
	// x110 xxxx
	mcp2510_reg	RXB0CTRL;
	mcp2510_reg	RXB0SIDH;
	mcp2510_reg	RXB0SIDL;
	mcp2510_reg	RXB0EID8;
	mcp2510_reg	RXB0EID0;
	mcp2510_reg	RXB0DLC;
	mcp2510_reg	RXB0D0;
	mcp2510_reg	RXB0D1;
	mcp2510_reg	RXB0D2;
	mcp2510_reg	RXB0D3;
	mcp2510_reg	RXB0D4;
	mcp2510_reg	RXB0D5;
	mcp2510_reg	RXB0D6;
	mcp2510_reg	RXB0D7;
	mcp2510_reg	CANSTAT_x110;
	mcp2510_reg	CANCTRL_x110;
	// x111 xxxx
	mcp2510_reg	RXB1CTRL;
	mcp2510_reg	RXB1SIDH;
	mcp2510_reg	RXB1SIDL;
	mcp2510_reg	RXB1EID8;
	mcp2510_reg	RXB1EID0;
	mcp2510_reg	RXB1DLC;
	mcp2510_reg	RXB1D0;
	mcp2510_reg	RXB1D1;
	mcp2510_reg	RXB1D2;
	mcp2510_reg	RXB1D3;
	mcp2510_reg	RXB1D4;
	mcp2510_reg	RXB1D5;
	mcp2510_reg	RXB1D6;
	mcp2510_reg	RXB1D7;
	mcp2510_reg	CANSTAT_x111;
	mcp2510_reg	CANCTRL_x111;	
} T_MCP2510_MAP;

// Define the Base Address( in its own address space ) of MCP20510
#define	MCP2510_MAP	((T_MCP2510_MAP*)0x0)

// Define the initial value for the mcp2510's configuration register
// Buffer Pin Full Control : disabled
#define	BFPCTRL_INIT_VAL	(0x00)
// Transmitter Request to Send pin : Digital Input
#define	TXRTSCTRL_INIT_VAL	(0x00)
// Configure the bit timing : 125kHZ
#define	CNF1_INIT_VAL		(0x03)
#define	CNF2_INIT_VAL		(0xb1)
#define	CNF3_INIT_VAL		(0x05)
// Configure the interrupt : disable all interrupts
#define	CANINTE_INIT_VAL	(0x00)
#define	CANINTF_INIT_VAL	(0x00)
// Reset Error Flag Register
#define	EFLG_INIT_VAL		(0x00)
// Transmitter Buffer Control
#define	TXBnCTRL_INIT_VAL	(0x00)
// Receiver Buffer 0 Control Register : Turn mask/filter off, receiver all message, Rollover disable
#define	RXB0CTRL_INIT_VAL	(0x60)
// Receiver Buffer 1 Control Register : Turn mask/filter off, receiver all message
#define	RXB1CTRL_INIT_VAL	(0x60)

/* Function prototypes */
#define	TOLONG( addr )		((unsigned long)(addr))
MCP2510_EXT void MCP2510_Init( void );
//--------------------------------//
#define	TXBUF0		0
#define	TXBUF1		1
#define	TXBUF2		2

#define	RXBUF0		3
#define	RXBUF1		4

#define	STANDID		0
#define	EXTID		1
MCP2510_EXT void MCP2510_TX(int TxBuf, int IdType, unsigned int id, int DataLen, char * data);
MCP2510_EXT void MCP2510_RX(int RxBuf, int * IdType, unsigned int * id, int * DataLen, char *data);

#endif
