#include <string.h>
#include <stdlib.h>
#include "2410addr.h"
#include "2410lib.h"
#include "def.h"
#include "uart0.h"

void Uart_Port_Set(void);
void Uart_Port_Return(void);

void Uart0_TxInt() __attribute__ ((interrupt("IRQ")));
void Uart0_RxIntOrErr() __attribute__ ((interrupt("IRQ")));
void Uart0_TxDmaDone() __attribute__ ((interrupt("IRQ")));
void Uart0_RxDmaDone() __attribute__ ((interrupt("IRQ")));
void Uart0_RxDmaOrErr() __attribute__ ((interrupt("IRQ")));
void Uart0_TxFifo() __attribute__ ((interrupt("IRQ")));
void Uart0_RxFifoOrErr() __attribute__ ((interrupt("IRQ")));
void Uart0_AfcTx() __attribute__ ((interrupt("IRQ")));
void Uart0_AfcRxOrErr() __attribute__ ((interrupt("IRQ")));

void __sub_Uart0_RxInt(void);
void __sub_Uart0_RxFifo(void);
void __sub_Uart0_RxAfc(void);
void __sub_Uart0_RxErrInt(void);


volatile U16 rx_dncs;
volatile U32 rx_point,rx_isdone,rx_filesize,rx_checksum;
volatile U32 isDone,isTxInt,isRxInt,tx_cnt,tx_end,rx_cnt,rx_end,afc_err;
volatile U8 *txdataPt;
volatile U8 *txdataFl;
volatile U8 *rxdataPt;
volatile U8 *rxdataCk;


volatile U32 save_rGPHCON,save_rGPHDAT,save_rGPHUP;
volatile U32 save_ULCON0,save_UCON0,save_UFCON0,save_UMCON0;
volatile U32 save_ULCON1,save_UCON1,save_UFCON1,save_UMCON1;
volatile U32 save_ULCON2,save_UCON2,save_UFCON2,save_UMCON2;

volatile static char *uart0TxStr;
volatile static char *uart0RxStr;

volatile static char *uart2TxStr;
volatile static char *uart2RxStr;

void Uart_Port_Set(void)
{
    //Push UART GPIO port configuration
    save_rGPHCON=rGPHCON; 
    save_rGPHDAT=rGPHDAT;
    save_rGPHUP=rGPHUP;
    //Configure UART port
    rGPHCON&=0x3c0000;
    rGPHCON|=0x2faaa;	// nRTS1,nCTS1
    rGPHUP|=0x1ff;	//Uart port pull-up disable
    //rINTSUBMSK=0x7ff;   //SUBINT ALL MASK
    //Push Uart control registers 
    save_ULCON0=rULCON0;   		
    save_UCON0=rUCON0;	   	
    save_UFCON0=rUFCON0;   		
    save_UMCON0=rUMCON0;   		
    save_ULCON1=rULCON1;		
    save_UCON1 =rUCON1;		
    save_UFCON1=rUFCON1;		
    save_UMCON1=rUMCON1;	
    save_ULCON2=rULCON2;		
    save_UCON2 =rUCON2;		
    save_UFCON2=rUFCON2;		
    save_UMCON2=rUMCON2;		
    //Initialize UART1,2 port
}       
        
void Uart_Port_Return(void)
{       
    //Pop UART GPIO port configuration
    rGPHCON=save_rGPHCON;
    rGPHDAT=save_rGPHDAT;
    rGPHUP=save_rGPHUP;
    //Pop Uart control registers 
    rULCON0=save_ULCON0;   		
    rUCON0 =save_UCON0;   	
    rUFCON0=save_UFCON0;   		
    rUMCON0=save_UMCON0;   		
    rULCON1=save_ULCON1;		
    rUCON1 =save_UCON1;	
    rUFCON1=save_UFCON1;		
    rUMCON1=save_UMCON1;
    rULCON2=save_ULCON2;		
    rUCON2 =save_UCON2;	
    rUFCON2=save_UFCON2;		
    rUMCON2=save_UMCON2;		
}

void Uart_Uclk_En(int ch,int baud)
{
    /*
    int ch, baud;
    Uart_Printf("\nSelect UART channel[0:UART0/1:UART1/2:UART2]:\n");
    ch=Uart_GetIntNum();
    Uart_Printf("\nSelect baud rate :\n");
    baud=Uart_GetIntNum();
    */
    if(ch == 0) {
   	Uart_Select(0);
    	rUCON0|=0x400;	// Select UCLK
     	rUBRDIV0=( (int)(UCLK/16./baud) -1 );	//Baud rate divisior register
    	Uart_Printf("UCLK is enabled by UART0.\n"); 
    	}
    else if(ch==1){
    	Uart_Select(1);
    	rUCON1|=0x400;	// Select UCLK
        rUBRDIV1=( (int)(UCLK/16./baud) -1 );	//Baud rate divisior register
        Uart_Select(0);
        Uart_Printf("UCLK is enabled by UART1.\n");
    	}
    else {
    	Uart_Select(2);
    	rUCON2|=0x400;	// Select UCLK
        rUBRDIV2=( (int)(UCLK/16./baud) -1 );	//Baud rate divisior register
        Uart_Select(0);
        Uart_Printf("UCLK is enabled by UART2.\n");
    	}
    //for(i=0;i<100;i++);	// For the satble operation
}

void Uart_Pclk_En(int ch, int baud)
{
    /*
    int ch, baud;
    Uart_Printf("\nSelect UART channel[0:UART0/1:UART1/2:UART2]:\n");
    ch=Uart_GetIntNum();
    Uart_Printf("\nSelect baud rate :\n");
    baud=Uart_GetIntNum();
    */
    
    if(ch == 0) {
    	Uart_Select(0);
    	rUCON0&=0x3ff;	// Select PCLK
   	rUBRDIV0=( (int)(PCLK/16./baud) -1 );	//Baud rate divisior register
   	Uart_Printf("PCLK is enabled by UART0.\n"); 
    	}
    else if(ch==1){
    	Uart_Select(1);
    	rUCON1|=0x3ff;	// Select PCLK
   	rUBRDIV1=( (int)(PCLK/16./baud) -1 );	//Baud rate divisior register
   	Uart_Select(0);
   	Uart_Printf("PCLK is enabled by UART1.\n");
    	}
    else {
    	Uart_Select(2);
    	rUCON2|=0x3ff;	// Select PCLK
   	rUBRDIV2=( (int)(PCLK/16./baud) -1 );	//Baud rate divisior register
   	Uart_Select(0);
   	Uart_Printf("PCLK is enabled by UART2.\n");
    	}
    //for(i=0;i<100;i++);	// For the satble operation
}

//---------------------------------------UART0 test function-------------------------------------
void Uart0_TxInt(void)
{
    rINTSUBMSK|=(BIT_SUB_RXD0|BIT_SUB_TXD0|BIT_SUB_ERR0);	// Just for the safety
    if(*uart0TxStr != '\0') 
    {
        WrUTXH0(*uart0TxStr++);
	    ClearPending(BIT_UART0);		// Clear master pending
	    rSUBSRCPND=(BIT_SUB_TXD0);		// Clear Sub int pending
	    rINTSUBMSK&=~(BIT_SUB_TXD0);	// Unmask sub int
    }
    else
    {
    	isTxInt=0;
    	ClearPending(BIT_UART0);		// Clear master pending
        rSUBSRCPND=(BIT_SUB_TXD0);		// Clear Sub int pending
        rINTMSK|=(BIT_UART0);
    }
}

void Uart0_RxIntOrErr(void)
{
    rINTSUBMSK|=(BIT_SUB_RXD0|BIT_SUB_TXD0|BIT_SUB_ERR0);
    if(rSUBSRCPND&BIT_SUB_RXD0) __sub_Uart0_RxInt();
    else __sub_Uart0_RxErrInt();
    ClearPending(BIT_UART0); 
    rSUBSRCPND=(BIT_SUB_RXD0|BIT_SUB_ERR0);	// Clear Sub int pending    
    rINTSUBMSK&=~(BIT_SUB_RXD0|BIT_SUB_ERR0);    
}

void __sub_Uart0_RxInt(void)
{
    if(RdURXH0()!='\r') 
    {
    	Uart_Printf("%c",RdURXH0());
    	*uart0RxStr++ =(char)RdURXH0();
    }
    else
    {
    	isRxInt=0;
    	*uart0RxStr='\0';
    	Uart_Printf("\n");
    }
}

void __sub_Uart0_RxErrInt(void)
{
    switch(rUERSTAT0)//to clear and check the status of register bits
    {
	case '1':
	    Uart_Printf("Overrun error\n");
	    break;
	case '2':
	    Uart_Printf("Parity error\n");
	    break;
	case '4':
	    Uart_Printf("Frame error\n");
	    break;
	case '8':
	    Uart_Printf("Breake detect\n");
	    break;
	default :
	    break;
    }
}


void Test_Uart0_Int(void)
{
    Uart_Port_Set(); 
    Uart_Select(0);    
    /*********** UART0 Tx test with interrupt ***********/  
    isTxInt=1;
    uart0TxStr="ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890->UART0 Tx interrupt test is good!!!!\r\n";
    Uart_Printf("[Uart channel 0 Tx Interrupt Test]\n");

    pISR_UART0=(unsigned)Uart0_TxInt;

    rULCON0=(0<<6)|(0<<3)|(0<<2)|(3);	// Normal,No parity,One stop bit, 8bit
    rUCON0 &= 0x400;	// For the PCLK <-> UCLK fuction
    rUCON0 |= (TX_INTTYPE<<9)|(RX_INTTYPE<<8)|(0<<7)|(0<<6)|(0<<5)|(0<<4)|(1<<2)|(1);
    //Clock,Tx:Def,Rx:Def,Rx timeout:x,Rx error int:x,Loop-back:x,Send break:x,Tx:int,Rx:int
    Uart_TxEmpty(0); //wait until tx buffer is empty.
    rINTMSK=~(BIT_UART0);
    rINTSUBMSK=~(BIT_SUB_TXD0);

    while(isTxInt);
    
    /*********** UART0 Rx test with interrupt ***********/
    isRxInt=1;
    uart0RxStr=(char *)UARTBUFFER;
    Uart_Printf("\n[Uart channel 0 Rx Interrupt Test]:\n");
    Uart_Printf("After typing ENTER key, you will see the characters which was typed by you.");
    Uart_Printf("\nTo quit, press ENTER key.!!!\n");
    Uart_TxEmpty(0); //wait until tx buffer is empty.
    pISR_UART0 =(unsigned)Uart0_RxIntOrErr;
    rULCON0=(0<<6)|(0<<3)|(0<<2)|(3);	// Normal,No parity,One stop bit, 8bit
    rUCON0 &= 0x400;	// For the PCLK <-> UCLK fuction
    rUCON0 |= (TX_INTTYPE<<9)|(RX_INTTYPE<<8)|(0<<7)|(1<<6)|(0<<5)|(0<<4)|(1<<2)|(1);
    //Clock,Tx:pulse,Rx:pulse,Rx timeout:x,Rx error int:o,Loop-back:x,Send break:x,Tx:int,Rx:int

    // Clear Int Pending and Unmask    
    ClearPending(BIT_UART0);
    rINTMSK=~(BIT_UART0);
    rSUBSRCPND=(BIT_SUB_TXD0|BIT_SUB_RXD0|BIT_SUB_ERR0);    
    rINTSUBMSK=~(BIT_SUB_RXD0|BIT_SUB_ERR0);
    
    while(isRxInt);
    
    rINTSUBMSK|=(BIT_SUB_RXD0|BIT_SUB_ERR0);
    rINTMSK|=(BIT_UART0);
 
    Uart_Printf("%s\n",(char *)UARTBUFFER);
    Uart_Port_Return();
}


void Uart0_TxDmaDone(void)
{
    rDMASKTRIG0=0x0;	// Stop Dma0
    isDone=0;
    rINTMSK |= BIT_DMA0;
    ClearPending(BIT_DMA0);
}

void Uart0_RxDmaOrErr(void)
{
    rINTSUBMSK|=(BIT_SUB_RXD0|BIT_SUB_TXD0|BIT_SUB_ERR0);
    if(rSUBSRCPND&BIT_SUB_ERR0) Uart_Printf("Error : UART0 Rx Interrupt is occured!!!\n");
    else __sub_Uart0_RxErrInt();
    
    ClearPending(BIT_UART0);
    rSUBSRCPND=(BIT_SUB_ERR0);	// Clear Sub int pending    
    rINTSUBMSK&=~(BIT_SUB_ERR0);    
}

void Uart0_RxDmaDone(void)
{
    rDMASKTRIG0=0x0;	//DMA0 Channel Off
    isDone=0;
    *(uart0RxStr+5)='\0';
    rINTMSK|=(BIT_DMA0);
    ClearPending(BIT_DMA0);
}

void Test_Uart0_Dma(void)
{
    Uart_Port_Set(); 
    Uart_Select(0);    
    /*********** UART0 Tx test with DMA0 ***********/ 
    isDone=1;
    uart0TxStr="ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890->UART0 Tx Test by DMA0 is good!!!!\r\n";
    Uart_Printf("\n[Uart channel 0 DMA0 Tx Test]\n");
    Uart_TxEmpty(0);
    
    pISR_DMA0  =(unsigned)Uart0_TxDmaDone;

    rULCON0=(0<<6)|(0<<3)|(0<<2)|(3);	// Normal,No parity,One stop bit, 8bit
    rUCON0 &= 0x400;	// For the PCLK <-> UCLK fuction    
    rUCON0 |= (TX_INTTYPE<<9)|(RX_INTTYPE<<8)|(0<<7)|(0<<6)|(0<<5)|(0<<4)|(2<<2)|(0);
    //Clock,Tx:Def,Rx:Def,Rx timeout:x,Rx error int:x,Loop-back:x,Send break:x,Tx:dma0,Rx:x

    /***DMA0 init***/
    rDISRC0=(U32)uart0TxStr;	// Start address
    rDISRCC0=(0<<1)|(0);		// AHB,Increment
    rDIDST0=(U32)UTXH0;			// Memory buffer Address
    rDIDSTC0=(1<<1)|(1);		// APB,Fixed
    rDCON0=(1<<31)|(0<<30)|(1<<29)|(0<<28)|(0<<27)|(1<<24)|(1<<23)|(1<<22)|(0<<20)|strlen((char*)uart0TxStr);
    //handshake, sync PCLK, TC int, single tx, single service, Uart0, H/W request,auto-reload off, Byte size Tx, Tx count value
    rINTMSK=~(BIT_DMA0);
    rDMASKTRIG0=(0<<2)|(1<<1)|(0);    //no-stop, DMA0 channel on, no-SW trigger 

    while(isDone);

    /*********** UART0 Rx test with DMA0 ***********/ 
    isDone=1;
    uart0RxStr=(char *)UARTBUFFER;
    Uart_Printf("\n[Uart channel 0 DMA0 Rx Test]\n");
    Uart_Printf("Type any five keys!!!\n");    
    Uart_Printf("Then you will see what you typed.\n");

    pISR_DMA0=(unsigned)Uart0_RxDmaDone;
    pISR_UART0=(unsigned)Uart0_RxDmaOrErr;
    
    rULCON0=(0<<6)|(0<<3)|(0<<2)|(3);	// Normal,No parity,One stop bit, 8bit
    rUCON0 &= 0x400;	// For the PCLK <-> UCLK fuction    
    rUCON0 |= (TX_INTTYPE<<9)|(RX_INTTYPE<<8)|(0<<7)|(1<<6)|(0<<5)|(0<<4)|(1<<2)|(2);
    //Clock,Tx:Def,Rx:Def,Rx timeout:x,Rx error int:o,Loop-back:x,Send break:x,Tx:int,Rx:dma0

    /***DMA0 init***/
    rDISRC0=(U32)URXH0;			// Start address
    rDISRCC0=(1<<1)|(1);		// APB,Fixed
    rDIDST0=(U32)uart0RxStr;	        // Memory buffer Address
    rDIDSTC0= (0<<1)|(0);		// AHB,Increment
    rDCON0=(1<<31)|(0<<30)|(1<<29)|(0<<28)|(0<<27)|(1<<24)|(1<<23)|(1<<22)|(0<<20)|(5);
    //handshake, sync PCLK, TC int, single tx, single service, Uart0, H/W request,auto-reload off, Byte size Tx, Tx count value

    // Clear Int Pending and Unmask    
    ClearPending(BIT_UART0);
    rINTMSK=~(BIT_DMA0|BIT_UART0);
    rSUBSRCPND=(BIT_SUB_TXD0|BIT_SUB_RXD0|BIT_SUB_ERR0);        
    rINTSUBMSK=~(BIT_SUB_ERR0);
    rDMASKTRIG0=(0<<2)|(1<<1)|(0);    //no-stop, DMA0 channel on, no-SW trigger 

    while(isDone);

    Uart_Printf("%s\n",uart0RxStr);
    Uart_Port_Return();
}


void Uart0_TxFifo(void)
{
    rINTSUBMSK|=(BIT_SUB_RXD0|BIT_SUB_TXD0|BIT_SUB_ERR0);	// Just for the safety
    while (!(rUFSTAT0 & 0x200) && (*uart0TxStr != '\0')) 	//until tx fifo full or end of string
    	WrUTXH0(*uart0TxStr++);	
   
    if(*uart0TxStr == '\0') 
    {
    	rINTMSK|=BIT_UART0;
    	rSUBSRCPND=BIT_SUB_TXD0;	// Clear Sub int pending
        ClearPending(BIT_UART0);	// Clear master pending
    }
    else 
    {
        ClearPending(BIT_UART0);	// Clear master pending
    	rSUBSRCPND=BIT_SUB_TXD0;	// Clear Sub int pending
        rINTSUBMSK&=~(BIT_SUB_TXD0);	// Unmask sub int
    }
}

void Uart0_RxFifoOrErr(void)
{
    rINTSUBMSK|=(BIT_SUB_RXD0|BIT_SUB_TXD0|BIT_SUB_ERR0);
    if(rSUBSRCPND&BIT_SUB_RXD0) __sub_Uart0_RxFifo();
    else __sub_Uart0_RxErrInt();
    ClearPending(BIT_UART0);
    rSUBSRCPND=(BIT_SUB_RXD0|BIT_SUB_ERR0);	// Clear Sub int pending    
    rINTSUBMSK&=~(BIT_SUB_RXD0|BIT_SUB_ERR0);    
}

void __sub_Uart0_RxFifo(void)
{
    while((rUFSTAT0&0x100)||(rUFSTAT0&0xf))	//During the Rx FIFO is not empty
    {
	rx_point++;
	if(rx_point<5)
		rx_filesize |= (RdURXH0()<<(8*(rx_point-1))); // First 4-bytes mean file size
	else if(rx_point>(rx_filesize-2))	
	{
		rx_dncs |= (RdURXH0()<<(8*(1-(rx_filesize-rx_point)))); //Last 2-bytes mean checksum.
		if(rx_point==rx_filesize) rx_isdone=0;
	}
	else
		rx_checksum+=RdURXH0();
    }
}

void Test_Uart0_Fifo(void)
{
    Uart_Port_Set(); 
    Uart_Select(0);
    /******* UART0 Tx FIFO test with interrupt ********/     
    Uart_Printf("[Uart channel 0 Tx FIFO Interrupt Test]\n");
    Uart_TxEmpty(0);	//wait until tx buffer is empty.
    
    /* <Tx Trigger Level:8Byte> */    
    uart0TxStr="ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890->UART0 Tx FIFO interrupt(8byte) test is good!!!!\r\n";
    pISR_UART0=(U32)Uart0_TxFifo;
    rULCON0=(0<<6)|(0<<3)|(0<<2)|(3);	// Normal,No parity,One stop bit, 8bit
    rUCON0 &= 0x400;	// For the PCLK <-> UCLK fuction    
    rUCON0 |= (TX_INTTYPE<<9)|(RX_INTTYPE<<8)|(0<<7)|(0<<6)|(0<<5)|(0<<4)|(1<<2)|(0);
    //Clock,Tx:Def,Rx:Def,Rx timeout:x,Rx error int:x,Loop-back:x,Send break:x,Tx:int,Rx:x
    rUFCON0=(2<<6)|(1<<4)|(1<<2)|(1<<1)|(1);
    //Tx and Rx FIFO Trigger Level:8byte,Tx and Rx FIFO Reset,FIFO on
    rINTMSK=~(BIT_UART0);
    rINTSUBMSK=~(BIT_SUB_TXD0);
    Delay(500);
    rUFCON0=(2<<6)|(1<<4)|(1<<2)|(1<<1)|(0);
    //Tx and Rx FIFO Trigger Level:8byte,Tx and Rx FIFO Reset,FIFO off

    /* <Tx Trigger Level:12Byte> */    
    uart0TxStr="ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890->UART0 Tx FIFO interrupt(12byte) test is good!!!!\r\n";
    pISR_UART0=(unsigned)Uart0_TxFifo;
    rULCON0=(0<<6)|(0<<3)|(0<<2)|(3);	// Normal,No parity,One stop bit, 8bit
    rUCON0 &= 0x400;	// For the PCLK <-> UCLK fuction    
    rUCON0 |= (TX_INTTYPE<<9)|(RX_INTTYPE<<8)|(0<<7)|(0<<6)|(0<<5)|(0<<4)|(1<<2)|(0);
    //Clock,Tx:Def,Rx:Def,Rx timeout:x,Rx error int:x,Loop-back:x,Send break:x,Tx:int,Rx:x
    rUFCON0=(3<<6)|(2<<4)|(1<<2)|(1<<1)|(1);
    //Tx and Rx FIFO Trigger Level:12byte,Tx and Rx FIFO Reset,FIFO on
    rINTMSK=~(BIT_UART0);
    rINTSUBMSK=~(BIT_SUB_RXD0|BIT_SUB_TXD0|BIT_SUB_ERR0);
    Delay(500);
    rUFCON0=(3<<6)|(2<<4)|(1<<2)|(1<<1)|(0);
    //Tx and Rx FIFO Trigger Level:12byte,Tx and Rx FIFO Reset,FIFO off

    
    /******* UART0 Rx FIFO test with interrupt ********/     
    rx_dncs=0;
    rx_point=0;
    rx_isdone=1;
    rx_filesize=0;
    rx_checksum=0;
    Uart_Printf("[Uart channel 0 Rx FIFO Interrupt Test]\n");
//----------------------------------------------------
    pISR_UART0=(unsigned)Uart0_RxFifoOrErr;

    rULCON0=(0<<6)|(0<<3)|(0<<2)|(3);	// Normal,No parity,One stop bit, 8bit
    rUCON0 &= 0x400;	// For the PCLK <-> UCLK fuction
    rUCON0 |= (TX_INTTYPE<<9)|(RX_INTTYPE<<8)|(1<<7)|(1<<6)|(0<<5)|(0<<4)|(1<<2)|(1);
    //Clock,Tx:Def,Rx:Def,Rx timeout:o,Rx error int:o,Loop-back:x,Send break:x,Tx:int,Rx:int
    rUFCON0=(1<<6)|(0<<4)|(1<<2)|(1<<1)|(1);
    //Tx and Rx FIFO Trigger Level:4byte,Tx and Rx FIFO Reset,FIFO on

    // Clear Int Pending and Unmask 
    ClearPending(BIT_UART0);
    rINTMSK=~(BIT_UART0);
    rSUBSRCPND=(BIT_SUB_RXD0|BIT_SUB_TXD0|BIT_SUB_ERR0);
    rINTSUBMSK=~(BIT_SUB_RXD0|BIT_SUB_ERR0);

    Uart_Printf("Download the target file[*.bin] by Uart0\n");
	
    while(rx_isdone);

    rINTMSK |= (BIT_UART0);	
    rINTSUBMSK|=(BIT_SUB_RXD0|BIT_SUB_TXD0|BIT_SUB_ERR0);

    rUFCON0=(3<<6)|(2<<4)|(1<<2)|(1<<1)|(0);
    //Tx and Rx FIFO Trigger Level:12byte,Tx and Rx FIFO Reset,FIFO off
			
    if(rx_dncs==(rx_checksum&0xffff)) 
	Uart_Printf("\nDownload test OK!!!\n");
    else 
	Uart_Printf("\nError!!!\n");
    Uart_Port_Return();	
}



void Uart0_AfcTx(void)
{
    rINTSUBMSK|=(BIT_SUB_RXD0|BIT_SUB_TXD0|BIT_SUB_ERR0);

    if(tx_cnt<AFC_BUFLEN)
    {
    	Uart_Printf("%d,",*txdataPt);
    	WrUTXH0(*txdataPt++);
	tx_cnt++;
        ClearPending(BIT_UART0);
        rSUBSRCPND=(BIT_SUB_TXD0);
        rINTSUBMSK&=~(BIT_SUB_TXD0);
    }
    else
    {
   	tx_end=1;
        while(rUFSTAT0 & 0x2f0);	//Until FIFO is empty
        ClearPending(BIT_UART0);
        rSUBSRCPND=(BIT_SUB_TXD0);
    	rINTMSK|=BIT_UART0;
    }
}

void Uart0_AfcRxOrErr(void)
{
    rINTSUBMSK|=(BIT_SUB_RXD0|BIT_SUB_TXD0|BIT_SUB_ERR0);
    if(rSUBSRCPND&BIT_SUB_RXD0) __sub_Uart0_RxAfc();    
    else __sub_Uart0_RxErrInt();

    ClearPending(BIT_UART0);
    rSUBSRCPND=(BIT_SUB_RXD0|BIT_SUB_TXD0|BIT_SUB_ERR0);
    rINTSUBMSK&=~(BIT_SUB_RXD0|BIT_SUB_TXD0|BIT_SUB_ERR0);
}

void __sub_Uart0_RxAfc(void)
{
    while( (rUFSTAT0 & 0x100) || ((rUFSTAT0 & 0xf) >0) )
    {
	*rxdataPt=rURXH0;
	Uart_Printf("%d,",*rxdataPt++);
	rx_cnt++;
    }
    if(rx_cnt == AFC_BUFLEN) 
    {
   	rx_end=1;
    	rINTMSK|=BIT_UART0;
    }
}
 
void Test_Uart0_AfcTx(void)
{
    int i;
    tx_cnt=0;
    tx_end=0;
    txdataFl=(volatile U8 *)UARTBUFFER;
    txdataPt=(volatile U8 *)UARTBUFFER;
    for(i=0;i<AFC_BUFLEN;i++) *txdataFl++=i;	// Initialize the AFC data
    Uart_Port_Set(); 
    Uart_Select(0);
    Uart_Printf("[Uart channel 0 AFC Tx Test]\n");
    Uart_Printf("This test should be configured two boards.\n");
    Uart_Printf("Connect Tx and Rx Board with twitsted(rx/tx, nCTS/nRTS) cable .\n");
    Uart_Printf("\nConnect PC[COM1 or COM2] and UART1 of SMDK2410 with a serial cable!!! \n");

    Uart_Printf("Then, press any key........\n");
    Uart_Select(1);	// Change the uart port    
    Uart_Getch();
    Uart_Printf("Start Rx first and then press any key to start Tx.....\n");
    Uart_Getch();

    pISR_UART0=(unsigned) Uart0_AfcTx;

    rULCON0=(0<<6)|(0<<3)|(0<<2)|(3);	// Normal,No parity,One stop bit, 8bit
    rUCON0 &= 0x400;	// For the PCLK <-> UCLK fuction    
    rUCON0 |= (1<<9)|(1<<8)|(0<<7)|(0<<6)|(0<<5)|(0<<4)|(1<<2)|(1);
    //Clock,Tx:Lev,Rx:Lev,Rx timeout:x,Rx error int:x,Loop-back:x,Send break:x,Tx:int,Rx:int
    rUFCON0=(1<<6)|(0<<4)|(1<<2)|(1<<1)|(1);
    //Tx and Rx FIFO Trigger Level:4byte,Tx and Rx FIFO Reset,FIFO on
    rUMCON0=0x10;   // Enable Uart0 AFC 
    rINTMSK=~(BIT_UART0);
    rINTSUBMSK=~(BIT_SUB_RXD0|BIT_SUB_TXD0|BIT_SUB_ERR0);

    while(!tx_end);

    rINTSUBMSK|=(BIT_SUB_RXD0|BIT_SUB_TXD0|BIT_SUB_ERR0);
    rUFCON0=(3<<6)|(2<<4)|(1<<2)|(1<<1)|(0);
    //Tx and Rx FIFO Trigger Level:12byte,Tx and Rx FIFO Reset,FIFO off
    Uart_Printf("\nEnd Tx, transfer data count=%d\n",tx_cnt);

    Uart_Printf("\nConnect PC[COM1 or COM2] and UART0 of SMDK2410 with a serial cable!!! \n");
    Uart_Printf("Then, press any key........\n");
    Uart_Select(0);
    Uart_Getch();
    Uart_Port_Return();
}

void Test_Uart0_AfcRx(void)
{
    unsigned int i;
    rx_cnt=0;
    rx_end=0;
    afc_err=0;
    rxdataCk=(volatile U8 *)UARTBUFFER;
    rxdataPt=(volatile U8 *)UARTBUFFER;
    Uart_Port_Set(); 
    Uart_Select(0);
    Uart_Printf("[Uart channel 0 AFC Rx Test]\n");
    Uart_Printf("This test should be configured two boards.\n");
    Uart_Printf("Connect Tx and Rx Board with twitsted(rx/tx, nCTS/nRTS) cable .\n");
    
    Uart_Printf("\nConnect PC[COM1 or COM2] and UART1 of SMDK2410 with a serial cable!!! \n");
    Uart_Printf("Then, press any key........\n");
    Uart_Select(1);	// Change the uart port    
    Uart_Getch();
    Uart_Printf("Press any key to start Rx and then Star Tx....\n");
    Uart_Getch();

    pISR_UART0=(unsigned) Uart0_AfcRxOrErr;

    rULCON0=(0<<6)|(0<<3)|(0<<2)|(3);	// Normal,No parity,One stop bit, 8bit
    rUCON0 &= 0x400;	// For the PCLK <-> UCLK fuction    
    rUCON0 |= (1<<9)|(1<<8)|(1<<7)|(1<<6)|(0<<5)|(0<<4)|(1<<2)|(1);
    //Clock,Tx:Lev,Rx:Lev,Rx timeout:o,Rx error int:o,Loop-back:x,Send break:x,Tx:o,Rx:o
    
    rUFCON0=(1<<6)|(0<<4)|(1<<2)|(1<<1)|(1);
    //Tx and Rx FIFO Trigger Level:4byte,Tx and Rx FIFO Reset,FIFO on
    rUMCON0=0x10;   // Enable Uart0 AFC 
    rINTMSK=~(BIT_UART0);
    rINTSUBMSK=~(BIT_SUB_RXD0|BIT_SUB_TXD0|BIT_SUB_ERR0);

    while(!rx_end);
    
    rINTSUBMSK|=(BIT_SUB_RXD0|BIT_SUB_TXD0|BIT_SUB_ERR0);
    rUFCON0=(3<<6)|(2<<4)|(1<<2)|(1<<1)|(0);
    //Tx and Rx FIFO Trigger Level:12byte,Tx and Rx FIFO Reset,FIFO off
    Uart_Printf("\nEnd Rx, receive data count=%d\n",rx_cnt);
    for(i=0;i<AFC_BUFLEN;i++) 
    	if(i-(*rxdataCk++)) {
    		Uart_Printf("i=%d\n",i);
    		afc_err++;
    		}
    if(afc_err)
    	Uart_Printf("AFC test fail!! Error count=%d\n",afc_err);
    else
    	Uart_Printf("AFC test is good!!\n");

    Uart_Printf("\nConnect PC[COM1 or COM2] and UART0 of SMDK2410 with a serial cable!!! \n");
    Uart_Printf("Then, press any key........\n");
    Uart_Select(0);
    Uart_Getch();
    Uart_Port_Return();
}
//---------------------------------------UART0 test function-------------------------------------
