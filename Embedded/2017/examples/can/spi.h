#ifndef _SPI_H
#define _SPI_H


#include 	"2410addr.h"
#include 	"2410lib.h"
#include 	"def.h"

//===================== Register Configuration Constants ======================

#define CHIP_SELECT_nSS0				0xFFFFFFFB
#define CHIP_DESELECT_nSS0				0x00000004


#define SPI_INTERNAL_CLOCK_ENABLE		(1<<18)				// Enable CPU clock to SPI controller

//----- GPIO Configuration Masks -----
#define CLEAR_GPG2_MASK					0xFFFFFFCF
#define ENABLE_GPG2_OUTPUT				0x00000010
#define ENABLE_GPG2_PULLUP				0x0000FFFB;

#define ENABLE_SPICLK0					0x08000000
#define ENABLE_SPIMSIO					0x02000000
#define DISABLE_SPICLK_SPIMSIO_PULLUP	0x00003000

//----- Register definitions for SPCON0 control register (global config register) -----
#define SPI_MODE_POLLING				0x00000000				// Data transfer modes
#define SPI_MODE_DMA					0x00000040
#define SPI_MODE_INTERRUPT				0x00000020
#define SPI_CLOCK_ENABLE				0x00000010				// Enable SPI clock (in master mode)
#define SPI_SELECT_MASTER				0x00000008				// Select master mode
#define SPI_CLOCK_POLARITY_HIGH			0x00000000				// Determines active clock type (high or low)
#define SPI_CLOCK_POLARITY_LOW			0x00000004
#define SPI_CLOCK_PHASE_FORMAT_A		0x00000000				// Determines transfer format (A or B)
#define SPI_CLOCK_PHASE_FORMAT_B		0x00000002					
#define SPI_TX_AUTO_GARBAGE				0x00000001				// Used when only receiving data


//----- Register definitions for SPSTA0 status register (global status register) -----
#define SPI_DATA_COLLISION				0x00000004				// Indicates I/O timing error (see datasheet)
#define SPI_MULTI_MASTER_ERROR			0x00000002				// Indicates both sender/reciever configured as Master
#define SPI_TRANSFER_READY				0x00000001				// Indicates SPI is ready to transfer/receive

//----- Register definitions for SPPIN0 control register (global config register) -----
//		NOTE: Bit 1 always needs to be a '1'
#define SPI_MULTI_MASTER_ERROR_ENABLE	0x00000006				// Enables checking for multi-master error 
#define SPI_MASTER_OUT_KEEP				0x00000003				// Determines MOSI drive or release (see datasheet)


//----- Register definitions for SPPRE0 control register (global config register) -----
//		NOTE: The prescale values for selecting the baud rates are hardcoded in the
//			  SetSPIClockRate() routine.  The available baud rates are:
#define CLK_RATE_FULL					0x00					// Full Master clock
#define CLK_RATE_HALF					0x01					// 1/2 Master clock
#define CLK_RATE_FOUR					0x02					// 1/4 Master clock
#define CLK_RATE_EIGHT					0x03					// 1/8 Master clock
#define CLK_RATE_SIXTEEN				0x04					// 1/16 Master clock
#define CLK_RATE_THIRTY2				0x05					// 1/32 Master clock
#define CLK_RATE_SIXTY4					0x06					// 1/64 Master clock
#define CLK_RATE_SLOW					0x07	



//-------------------------- Public Interface ------------------------------
BOOL SPI_Init(VOID);
BOOL SPI_Deinit(VOID);
BOOL SPI_SendByte(BYTE bData, BYTE* pData);
BOOL SPI_WaitTxRxReady(VOID);
BOOL SPI_SendWord(WORD wData);

//-------------------- Private Interface (Helper routines) ------------------
VOID StartSPIClock(VOID);
VOID StopSPIClock(VOID);
VOID SetSPIClockRate(DWORD ClockRate);

#endif

