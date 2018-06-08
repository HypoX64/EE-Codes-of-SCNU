//====================================================================
// File Name : 2410IIC.c
// Function  : S3C2410 IIC-bus Master Tx/Rx mode Test Program
//             (Interrupt / Non Interrupt (Polling))
// Program   : Shin, On Pil (SOP)
// Date      : May 21, 2002
// Version   : 0.0
// History
//   0.0 : Programming start (March 11, 2002) -> SOP
//====================================================================

#include <string.h>
#include "2410addr.h"
#include "2410lib.h"
#include "def.h"
#include "2410IIC.h"

static U8 iic_buffer[IICBUFSIZE];
static volatile int iic_data_tx_size;
static volatile int _iicStatus;
static volatile int _iicMode;
static int _iicPt;

//===================================================================
//       SMDK2410 IIC configuration
//  GPE15=IICSDA, GPE14=IICSCL
//  "Interrupt mode" for IIC block
//=================================================================== 
//******************[ Test_Dac ]**************************************
void Test_Dac(void)
{
    int i,j,save_E,save_PE;
    static U8 data[256];
    
    PRINTF("---------DAC测试--------\n");

    save_E   = rGPECON;
    save_PE  = rGPEUP;

    rGPEUP  |= 0xc000;                  //Pull-up disable
    rGPECON |= 0xa00000;                //GPE15:IICSDA , GPE14:IICSCL    

    //Enable ACK, Prescaler IICCLK=PCLK/16, Enable interrupt, Transmit clock value Tx clock=IICCLK/16    
	rIICCON = (1<<7) | (0<<6) | (1<<5) | (0xf);
	
    rIICADD  = 0x10;                    //2410 slave address = [7:1]
    rIICSTAT = 0x10;                    //IIC bus data output enable(Rx/Tx)
    
    PRINTF("[1] 输出三角波\n");

	for(j = 0; j < 5; j++)
	{
	    for(i=0;i<256;i++)
    	{
        	iic_write_max5380(0x60,(U8)i);        
    	}    
	    for(i=256;i>=0;i--)
    	{
        	iic_write_max5380(0x60,(U8)i);        
    	}
    }    

    PRINTF("[2] 输出锯齿波\n");
	for(j = 0; j < 10; j++)
	{
	    for(i=0;i<256;i++)
 	   	{
        	iic_write_max5380(0x60,(U8)i);
    	}    
    }

    PRINTF("[3] 输出方波\n");
	for(j = 0; j < 10; j++)
	{
	    for(i=0;i<256;i++)
 	   	{
        	iic_write_max5380(0x60,(U8)0);
    	}    
	    for(i=0;i<256;i++)
 	   	{
        	iic_write_max5380(0x60,(U8)0xff);
    	}    
    }

    rGPEUP  = save_PE;
    rGPECON = save_E;   
    PRINTF("-------DAC测试结束------\n");
}

//******************[ Test_Iic ]**************************************
void Test_Iic(void)
{
    unsigned int i,j,save_E,save_PE;
    static U8 data[256];

    PRINTF("IIC测试开始!\n");

    save_E   = rGPECON;
    save_PE  = rGPEUP;
    rGPEUP  |= 0xc000;                  //Pull-up disable
    rGPECON |= 0xa00000;                //GPE15:IICSDA , GPE14:IICSCL 

    pISR_IIC = (unsigned)IicInt;
    rINTMSK &= ~(BIT_IIC);

      //Enable ACK, Prescaler IICCLK=PCLK/16, Enable interrupt, Transmit clock value Tx clock=IICCLK/16
      // If PCLK 50.7MHz, IICCLK = 3.17MHz, Tx Clock = 0.198MHz
    rIICCON = (1<<7) | (0<<6) | (1<<5) | (0xf);

    rIICADD  = 0x10;                    //2410 slave address = [7:1]
    rIICSTAT = 0x10;                    //IIC bus data output enable(Rx/Tx)

    PRINTF("Write test data into KS24C080\n");

    for(i=0;i<256;i++)
        Wr24C080(0xa0,(U8)i,i);
           
    for(i=0;i<256;i++)
        data[i] = 0;

    PRINTF("Read test data from KS24C080\n");
    
    for(i=0;i<256;i++)
        Rd24C080(0xa0,(U8)i,&(data[i])); 

    for(i=0;i<256;i++)
    {
        if(data[i] != i)
        	PRINTF("校验错误\n");
    }
    if(i >= 256)
    	PRINTF("校验正确\n");
	
    rINTMSK |= BIT_IIC;    
    rGPEUP  = save_PE;
    rGPECON = save_E;
    Delay(10);
    PRINTF("IIC测试结束!\n");
}


//*************************[ Wr24C080 ]****************************
void Wr24C080(U32 slvAddr,U32 addr,U8 data)
{
    _iicMode      = WRDATA;
    _iicPt        = 0;
    iic_buffer[0]   = (U8)addr;
    iic_buffer[1]   = data;
    iic_data_tx_size = 2;
    
    rIICDS   = slvAddr;                 //0xa0
    rIICSTAT = 0xf0;                    //MasTx,Start
      //Clearing the pending bit isn't needed because the pending bit has been cleared.
    while(iic_data_tx_size!=-1);

    _iicMode = POLLACK;

    while(1)
    {
        rIICDS     = slvAddr;
        _iicStatus = 0x100;
        rIICSTAT   = 0xf0;              //MasTx,Start        
        rIICCON    = 0xaf;              //Resumes IIC operation.
		                    
        while(_iicStatus==0x100);
           
        if(!(_iicStatus&0x1))
            break;                      //When ACK is received
    }
    rIICSTAT = 0xd0;                    //Stop MasTx condition     
    rIICCON  = 0xaf;                    //Resumes IIC operation. 
    Delay(1);                           //Wait until stop condtion is in effect.
    //Write is completed.
}
        
//**********************[ Rd24C080 ] ***********************************
void Rd24C080(U32 slvAddr,U32 addr,U8 *data)
{
    
    _iicMode      = SETRDADDR;
    _iicPt        = 0;
    iic_buffer[0]   = (U8)addr;
    iic_data_tx_size = 1;

    rIICDS   = slvAddr;
    rIICSTAT = 0xf0;                    //MasTx,Start  
      //Clearing the pending bit isn't needed because the pending bit has been cleared.
    while(iic_data_tx_size!=-1);

    _iicMode      = RDDATA;
    _iicPt        = 0;
    iic_data_tx_size = 1;
    
    rIICDS        = slvAddr;
    rIICSTAT      = 0xb0;               //MasRx,Start    
    rIICCON       = 0xaf;               //Resumes IIC operation.   
    while(iic_data_tx_size!=-1);

    *data = iic_buffer[1];
}


//-------------------------------------------------------------------------
void IicInt(void)
{
    U32 iicSt,i;
    
    rSRCPND = BIT_IIC;          //Clear pending bit
    rINTPND = BIT_IIC;
    iicSt   = rIICSTAT; 
    
    if(iicSt & 0x8){}           //When bus arbitration is failed.
    if(iicSt & 0x4){}           //When a slave address is matched with IICADD
    if(iicSt & 0x2){}           //When a slave address is 0000000b
    if(iicSt & 0x1){}           //When ACK isn't received

    switch(_iicMode)
    {
       case POLLACK:
           _iicStatus = iicSt;
           break;

       case RDDATA:
           if((iic_data_tx_size--)==0)
           {
               iic_buffer[_iicPt++] = rIICDS;
            
               rIICSTAT = 0x90;                 //Stop MasRx condition                
               rIICCON  = 0xaf;                 //Resumes IIC operation.
               Delay(1);                        //Wait until stop condtion is in effect.
                                                //Too long time... 
                                                //The pending bit will not be set after issuing stop condition.
               break;    
           }      
           iic_buffer[_iicPt++] = rIICDS;         //The last data has to be read with no ack.

           if((iic_data_tx_size)==0)           	   
               rIICCON = 0x2f;                  //Resumes IIC operation with NOACK.             
           else                
               rIICCON = 0xaf;                  //Resumes IIC operation with ACK               
           break;
		   Delay(1);                        
			
        case WRDATA:
            if((iic_data_tx_size--)==0)
            {
                rIICSTAT = 0xd0;                //Stop MasTx condition                 
                rIICCON  = 0xaf;                //Resumes IIC operation.
                Delay(1);                       //Wait until stop condtion is in effect.
                       //The pending bit will not be set after issuing stop condition.
                break;    
            }
            rIICDS = iic_buffer[_iicPt++];        //iic_buffer[0] has dummy.
            for(i=0;i<10;i++);                  //for setup time until rising edge of IICSCL
              
            rIICCON = 0xaf;                     //resumes IIC operation.
            Delay(1);                       //Wait until stop condtion is in effect.
            break;

        case SETRDADDR:
//            Uart_Printf("__irq IicInt SETDADDR [ S%d ]",iic_data_tx_size);
            if((iic_data_tx_size--)==0)
                break;                          //IIC operation is stopped because of IICCON[4]    
            rIICDS = iic_buffer[_iicPt++];
            for(i=0;i<10;i++);                  //For setup time until rising edge of IICSCL
            rIICCON = 0xaf;                     //Resumes IIC operation.
            break;

        default:
            break;      
    }
}
//===================================================================
//       SMDK2410 IIC configuration
//  GPE15=IICSDA, GPE14=IICSCL
//  "Non-Interrupt" mode for IIC block
//=================================================================== 

//*********************[ Test_Iic2 ]*********************************
void Test_Iic2(void)
{
    unsigned int i,j,save_E,save_PE;
    static U8 data[256], readdata[256];
    
    PRINTF("---------IIC测试--------\n");

    save_E   = rGPECON;
    save_PE  = rGPEUP;

    rGPEUP  |= 0xc000;                  //Pull-up disable
    rGPECON |= 0xa00000;                //GPE15:IICSDA , GPE14:IICSCL    

      //Enable ACK, Prescaler IICCLK=PCLK/16, Enable interrupt, Transmit clock value Tx clock=IICCLK/16
    rIICCON  = (1<<7) | (0<<6) | (1<<5) | (0xf);

    rIICADD  = 0x10;                    //2410 slave address = [7:1]
    rIICSTAT = 0x10;                    //IIC bus data output enable(Rx/Tx)

    PRINTF("[1] 写数据到KS24C08\n");

    for(i=0;i<256;i++)
    {
    	data[i] = 255-i;
        iic_write_24C08(0xa0,(U8)i,data[i]);
    }
    for(i=0;i<256;i++)
        readdata[i] = 0;

    PRINTF("[2] 从KS24C08读数据\n");
    for(i=0;i<256;i++)
        iic_read_24C08(0xa0,(U8)i,&(readdata[i])); 

	PRINTF("[3] 校验数据: ");
    for(i=0;i<16;i++)
    {
        for(j=0;j<16;j++)
        {
        	if(readdata[i*16+j] != data[i*16+j])
        	{
        		PRINTF("错误\n");
        		goto __out;
        	}
        }
    }
    Delay(10);
	PRINTF("正确\n");
	
__out:    
	Delay(10);
    PRINTF("-------IIC测试结束------\n\n");

    rGPEUP  = save_PE;
    rGPECON = save_E;
}

//**************[ iic_write_24C08 ]*****************************************
void iic_write_24C08(U32 slvAddr,U32 addr,U8 data)
{
    _iicMode      = WRDATA;
    _iicPt        = 0;
    iic_buffer[0]   = (U8)addr;
    iic_buffer[1]   = data;
    iic_data_tx_size = 2;
    
    rIICDS        = slvAddr;            //0xa0
      //Master Tx mode, Start(Write), IIC-bus data output enable
      //Bus arbitration sucessful, Address as slave status flag Cleared,
      //Address zero status flag cleared, Last received bit is 0
    rIICSTAT      = 0xf0;      
      //Clearing the pending bit isn't needed because the pending bit has been cleared.
    while(iic_data_tx_size!=-1)
       Run_IicPoll();

    _iicMode = POLLACK;

    while(1)
    {
        rIICDS     = slvAddr;
        _iicStatus = 0x100;             //To check if _iicStatus is changed 
        rIICSTAT   = 0xf0;              //Master Tx, Start, Output Enable, Sucessful, Cleared, Cleared, 0        
        rIICCON    = 0xaf;              //Resumes IIC operation. 
        while(_iicStatus==0x100)  
            Run_IicPoll();
              
        if(!(_iicStatus & 0x1))
            break;                      //When ACK is received
    }
    rIICSTAT = 0xd0;                    //Master Tx condition, Stop(Write), Output Enable    
    rIICCON  = 0xaf;                    //Resumes IIC operation. 
    Delay(1);                           //Wait until stop condtion is in effect.
    //Write is completed.
}
        
//************************[ iic_read_24C08 ]********************************
void iic_read_24C08(U32 slvAddr,U32 addr,U8 *data)
{
    _iicMode      = SETRDADDR;
    _iicPt        = 0;
    iic_buffer[0]   = (U8)addr;
    iic_data_tx_size = 1;

    rIICDS   = slvAddr;
    rIICSTAT = 0xf0;                    //MasTx,Start  
      //Clearing the pending bit isn't needed because the pending bit has been cleared.
    while(iic_data_tx_size!=-1)
        Run_IicPoll();

    _iicMode      = RDDATA;
    _iicPt        = 0;
    iic_data_tx_size = 1;
    
    rIICDS   = slvAddr;
    rIICSTAT = 0xb0;                    //Master Rx,Start    
    rIICCON  = 0xaf;                    //Resumes IIC operation.   
    while(iic_data_tx_size!=-1)
        Run_IicPoll();

    *data = iic_buffer[1];
}

//**************[ iic_write_max5380 ]*****************************************
void iic_write_max5380(U32 slvAddr,U8 data)
{
    _iicMode      = WRDATA;
    _iicPt        = 0;
    iic_buffer[0]   = data;
    iic_data_tx_size = 1;
    
    rIICDS        = slvAddr;            //0xa0
      //Master Tx mode, Start(Write), IIC-bus data output enable
      //Bus arbitration sucessful, Address as slave status flag Cleared,
      //Address zero status flag cleared, Last received bit is 0
    rIICSTAT      = 0xf0;      
    
     //Clearing the pending bit isn't needed because the pending bit has been cleared.
    while(iic_data_tx_size!=-1)
       Run_IicPoll1();

    _iicMode = POLLACK;

	while(_iicStatus & 0x1);                       
	
    rIICSTAT = 0xd0;                    //Master Tx condition, Stop(Write), Output Enable                
    rIICCON  = 0xef;                    //Resumes IIC operation.
    Delay(1);                           //Wait until stop condtion is in effect.          
    //Write is completed.
}

//**********************[ Run_IicPoll1 ]*********************************
void Run_IicPoll1(void)
{
    if(rIICCON & 0x10)                  //Tx/Rx Interrupt Enable
       IicPoll1();
}  

//**********************[ Run_IicPoll ]*********************************
void Run_IicPoll(void)
{
    if(rIICCON & 0x10)                  //Tx/Rx Interrupt Enable
       IicPoll();
}       
    
//**********************[IicPoll ]**************************************
void IicPoll(void)
{
    U32 iicSt,i;
    
    iicSt = rIICSTAT; 
    if(iicSt & 0x8){}                   //When bus arbitration is failed.
    if(iicSt & 0x4){}                   //When a slave address is matched with IICADD
    if(iicSt & 0x2){}                   //When a slave address is 0000000b
    if(iicSt & 0x1){}                   //When ACK isn't received

    switch(_iicMode)
    {
        case POLLACK:
            _iicStatus = iicSt;
            break;

        case RDDATA:
            if((iic_data_tx_size--)==0)
            {
                iic_buffer[_iicPt++] = rIICDS;            
                rIICSTAT = 0x90;                //Stop MasRx condition                 
                rIICCON  = 0xaf;                //Resumes IIC operation.
                Delay(1);                       //Wait until stop condtion is in effect.
                                                //Too long time... 
                                                //The pending bit will not be set after issuing stop condition.
                break;    
            }      
            iic_buffer[_iicPt++] = rIICDS;      //The last data has to be read with no ack.
            if((iic_data_tx_size)==0)            	
                rIICCON = 0x2f;                 //Resumes IIC operation with NOACK.  
            else            	
                rIICCON = 0xaf;                 //Resumes IIC operation with ACK
            break;

        case WRDATA:
            if((iic_data_tx_size--)==0)
            {
                rIICSTAT = 0xd0;                //stop MasTx condition                 
                rIICCON  = 0xaf;                //resumes IIC operation.
                Delay(1);                       //wait until stop condtion is in effect.
                //The pending bit will not be set after issuing stop condition.
                break;    
            }
            rIICDS = iic_buffer[_iicPt++];        //iic_buffer[0] has dummy.            
            rIICCON = 0xaf;                     //resumes IIC operation.                        
            for(i=0;i<10;i++);                  //for setup time until rising edge of IICSCL
            break;

        case SETRDADDR:
//          Uart_Printf("IicPoll() SETRADDR [S%d]",iic_data_tx_size);
            if((iic_data_tx_size--)==0)
            {
                break;                  //IIC operation is stopped because of IICCON[4]    
            }
            rIICDS = iic_buffer[_iicPt++];
            for(i=0;i<10;i++);          //for setup time until rising edge of IICSCL
            rIICCON = 0xaf;             //resumes IIC operation.
            break;

        default:
            break;      
    }
}

//**********************[IicPoll1 ]**************************************
void IicPoll1(void)
{
    U32 iicSt,i;
    
    iicSt = rIICSTAT; 
    if(iicSt & 0x8){}                   //When bus arbitration is failed.
    if(iicSt & 0x4){}                   //When a slave address is matched with IICADD
    if(iicSt & 0x2){}                   //When a slave address is 0000000b
    if(iicSt & 0x1){}                   //When ACK isn't received

    switch(_iicMode)
    {
        case POLLACK:
            _iicStatus = iicSt;
            break;

        case WRDATA:
            if((iic_data_tx_size--)==0)
            {
                rIICSTAT = 0xd0;                //stop MasTx condition                 
                rIICCON  = 0xef;                //resumes IIC operation.
//              Delay(1);                       //wait until stop condtion is in effect.
                //The pending bit will not be set after issuing stop condition.
                break;    
            }
            rIICDS = iic_buffer[_iicPt++];        //iic_buffer[0] has dummy.
            //for(i=0;i<10;i++);                  //for setup time until rising edge of IICSCL
            rIICCON = 0xef;                     //resumes IIC operation.
            break;

        default:
            break;      
    }
}
