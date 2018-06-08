/*

Module Name:	SPI.CPP

Abstract:		SPI Interface Routines for Samsung SC2410 CPU
  
Notes:			Presently, only the SPI Channel 0 is supported.

Environment:	Samsung SC2410 CPU

Date: 			2004/01/28

By: 			Li zhongmin
   
*/

#include 	"2410addr.h"
#include 	"2410lib.h"
#include 	"def.h"
#include 	"spi.h"


volatile DWORD g_dwWaitCounter = 0;
//----------------------------------------------------------------------------------


// Used to wait the specified # of clock cycles
#define WAIT(x)		{ for(g_dwWaitCounter=0; g_dwWaitCounter<x; g_dwWaitCounter++); }				

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Function:		SPI_Init()

Description:	Initializes the Serial Peripheral Interface (SPI)

Notes:			This routine assumes that the control registers (see 
				the globals section above) have already been initialized.

Returns:		Boolean indicating success.
-------------------------------------------------------------------*/
BOOL SPI_Init(VOID)
{
	int index;
	
	rGPGDAT |= CHIP_DESELECT_nSS0;
	
	//----- 1. IMPORTANT: By default, the internal clock is disabled.  To configure the controller ------
	//					  we must first enable it.
    StartSPIClock();
    
	SetSPIClockRate(CLK_RATE_SLOW);

	//----- 2. Configure the GPIO pins for SPI mode -----
	//
	//		   nSPICS0  (chip select)		= GPG2
	//		   SPICLK0  (SPI clock)			= GPE13
	//		   SPIMOSIO (SPI output data)	= GPE12
	//   
	//rGPGCON &= CLEAR_GPG2_MASK;
	//rGPGCON |= ENABLE_GPG2_OUTPUT;
	//rGPGUP  &= ENABLE_GPG2_PULLUP;

	//rGPECON |= (ENABLE_SPICLK0 | ENABLE_SPIMSIO);
	//rGPEUP  |= DISABLE_SPICLK_SPIMSIO_PULLUP;	// Disable pullup-resistor for SPICLK0 and SPIMOSIO 


	//----- 3. Configure the SPI controller with reasonable default values -----
	rSPCON0 = (SPI_MODE_POLLING | SPI_SELECT_MASTER | SPI_CLOCK_ENABLE);
	
	for( index = 0; index < 20; index++)
		rSPTDAT0 = 0xFF;
	
    //StopSPIClock();

	return TRUE;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Function:		SPI_Deinit()

Description:	Deinitializes the Serial Peripheral Interface (SPI)

Notes:			This routine DOES NOT unmap the control registers;
				the caller is responsible for freeing this memory.

Returns:		Boolean indicating success.
-------------------------------------------------------------------*/
BOOL SPI_Deinit(VOID)
{
	//----- 1. Stop the SPI clocks -----
    StopSPIClock();

	return TRUE;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Function:		SPI_SendByte()

Description:	Sends the specified byte out onto the SPI bus.

Returns:		Boolean indicating success.
-------------------------------------------------------------------*/
BOOL SPI_SendByte(BYTE bData, BYTE* pData)
{
    //----- 0. Start clock
    //StartSPIClock();

	//----- 1. Chip select the slave device (active low) -----
	//rGPGDAT &= CHIP_SELECT_nSS0;

	//----- 2. Wait until the controller is ready to transfer -----
	if(SPI_WaitTxRxReady()==FALSE) return FALSE;
	
	//----- 3. Put the byte out onto the SPI bus -----
	rSPTDAT0 = bData;
	
	//----- 4. Delay a little bit so the byte finishes clocking out before the chip select line is deasserted -----
	if(SPI_WaitTxRxReady()==FALSE) return FALSE;
	
	*pData = rSPRDAT0;

	//----- 5. Deselect the slave device (active low) -----
	//rGPGDAT |= CHIP_DESELECT_nSS0;

   // StopSPIClock();

	return TRUE;
}

BOOL SPI_ReadByte(BYTE *pData)
{
    BOOL    bRet = TRUE;
    
    //----- 0. Start clock
    //StartSPIClock();

	//----- 1. Chip select the slave device (active low) -----
	//rGPGDAT &= CHIP_SELECT_nSS0;

	//----- 2. Wait until the controller is ready to transfer -----
	if(SPI_WaitTxRxReady()==FALSE) return FALSE;

	//----- 3. Put the byte out onto the SPI bus -----
	*pData = rSPRDAT0;
	
	//----- 4. Delay a little bit so the byte finishes clocking out before the chip select line is deasserted -----
	//if(SPI_WaitTxRxReady()==FALSE) return FALSE;

	//----- 5. Deselect the slave device (active low) -----
	//rGPGDAT |= CHIP_DESELECT_nSS0;

   // StopSPIClock();

	return bRet;	
}

BOOL SPI_WaitTxRxReady(VOID)
{
	int waitCount;
	
	//----- 1. Wait until the controller is ready to transfer -----
	waitCount = 1000;
	while(!(rSPSTA0 & SPI_TRANSFER_READY))
	{
		if(--waitCount == 0)
		{
            return FALSE;
		}
	}
	
	return TRUE;
	
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Function:		SPI_SendWord()

Description:	Sends the specified word out onto the SPI bus.

Returns:		Boolean indicating success.
-------------------------------------------------------------------*/
BOOL SPI_SendWord(WORD wData)
{
    BOOL    bRet = TRUE;
	DWORD   waitCount = 0;

    StartSPIClock();

	//----- 1. Chip select the slave device (active low) -----
	rGPGDAT &= CHIP_SELECT_nSS0;

	//----- 2. Wait until the controller is ready to transfer -----
	waitCount = 1000;
	while(!(rSPSTA0 & SPI_TRANSFER_READY))
	{
		if(--waitCount == 0)
		{
            bRet = FALSE;
			goto SEND_ERROR;
		}
	}

	//----- 3. Send first half of word -----
	rSPTDAT0 = (wData & 0xFF00) >> 8;

	//----- 4. Wait until the controller is ready to transfer -----
	waitCount = 1000;
	while(!(rSPSTA0 & SPI_TRANSFER_READY))
	{
		if(--waitCount == 0)
		{
			//RETAILMSG(1, (TEXT("WAVEDEV.DLL: SPI_SendWord() - timeout occurred while waiting to transfer byte\r\n")));
            bRet = FALSE;
			goto SEND_ERROR;
		}
	}

	//----- 5. Send second half of word -----
	rSPTDAT0 = (wData & 0x00FF);

	//----- 6. Delay a little bit so the byte finishes clocking out before the chip select line is deasserted -----
	WAIT(10000);

	//----- 7. Deselect the slave device (active low) -----
	rGPGDAT |= CHIP_DESELECT_nSS0;

SEND_ERROR:

    StopSPIClock();

	return bRet;
}


//------------------------------------ Helper Routines ------------------------------------

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Function:		StartSPIClock()

Description:	Enables the SPI clock.

Returns:		N/A
-------------------------------------------------------------------*/
VOID StartSPIClock(VOID)
{
	rCLKCON |= SPI_INTERNAL_CLOCK_ENABLE;		// Enable the CPU clock to the SPI controller

	rSPCON0 |= (SPI_CLOCK_ENABLE|SPI_SELECT_MASTER);// Enable the SPI clock
	
	return;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Function:		StopSPIClock()

Description:	Disables the SPI clock.

Returns:		N/A
-------------------------------------------------------------------*/
VOID StopSPIClock(VOID)
{
	rCLKCON &= ~SPI_INTERNAL_CLOCK_ENABLE;	// Disable the CPU clock to the SPI controller

	rSPCON0 &= ~SPI_CLOCK_ENABLE;				// Disable the SPI clock
	
	return;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Function:		SetSPIClockRate()

Description:	Sets the SPI clock (a.k.a. baud) rate:

Params:			ClockRate       0x00 =      25Mhz
								0x01 = 1/2  25Mhz
								0x02 = 1/4  25Mhz
								0x03 = 1/8  25Mhz
								0x04 = 1/16 25Mhz
								0x05 = 1/32 25Mhz
								0x06 = 1/64 25Mhz
								0x07 = 99.121Khz

Returns:		N/A
-------------------------------------------------------------------*/
VOID SetSPIClockRate(DWORD ClockRate)
{
	UINT16 prescale;

    //----- 1. Set the clock rate  -----
	//		   NOTE: Using the prescale value, the clock's baud rate is
	//				 determined as follows: baud_rate = (PCLK / 2 / (prescale + 1))
	//
	//				 Hence, the prescale value can be computed as follows:
	//				 prescale = ((PCLK / 2) / baud_rate) - 1
	switch(ClockRate)
	{
		case CLK_RATE_FULL:						// 25 Mhz			
		prescale = (PCLK / 40000000) - 1;
		break;

		case CLK_RATE_HALF:						// 1/2  25 Mhz						
		prescale = (PCLK / 30000000) - 1;
		break;

		case CLK_RATE_FOUR:						// 1/4  25 Mhz						
		prescale = (PCLK / 10000000) - 1;
		break;

		case CLK_RATE_EIGHT:					// 1/8  25 Mhz						
		prescale = (PCLK / 500000) - 1;
		break;

		case CLK_RATE_SIXTEEN:					// 1/16 25 Mhz						
		prescale = (PCLK / 2500000) - 1;
		break;

		case CLK_RATE_THIRTY2:					// 1/32 25 Mhz						
		prescale = (PCLK / 1250000) - 1;
		break;

		case CLK_RATE_SIXTY4:					// 1/64 25 Mhz						
		prescale = (PCLK / 625000) - 1;
		break;

		case CLK_RATE_SLOW:						// 99.121 kHz (i.e. ~1/256 25Mhz)
		prescale = 255;
		break;

		default:
		return;
		break;
	}

	rSPPRE0 = prescale;


    return;
}
