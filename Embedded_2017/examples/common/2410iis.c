//====================================================================
// File Name : 2410iis.c
// Function  : S3C2410 IIS (UDA1341) Record & Play Test Program
//             (DMA2, Double Buffer, Record, Play)
// Program   : Shin, On Pil (SOP)
// Date      : October 01, 2002
// Version   : 0.0
// History
//   0.0 : Programming start (March 06, 2002) -> SOP
//   0.1 : Added Slave mode Test Program(July 24, 2002) -> KWT(Tark), SOP
//         Optimization (December 09, 2002) -> SOP
//====================================================================

#include "2410addr.h"
#include "2410lib.h"
#include "def.h"
#include "2410iis.h"
#include "iis_wave.h"

void ChangeDMA2(void);
void IIS_PortSetting(void);
void _WrL3Addr(U8 data);
void _WrL3Data(U8 data,int halt);
void DMA2_Done() __attribute__ ((interrupt("IRQ")));
void DMA2_Rec_Done() __attribute__ ((interrupt("IRQ")));
void RxInt() __attribute__ ((interrupt("IRQ")));
void Muting() __attribute__ ((interrupt("IRQ")));

#define L3C (1<<6)            //GPB4 = L3CLOCK
#define L3D (1<<7)            //GPB3 = L3DATA
#define L3M (1<<5)            //GPB2 = L3MODE

#define PLAY    0
#define RECORD  1
//#define REC_LEN 0x50000         //327,680 Bytes
#define REC_LEN 0x100000         //1,048,576 Bytes

#define DataCount   0x10000     //IIS Master/Slave Data Rx/Tx Count
#define DataDisplay 0x100       //IIS Master Data Display Count
//#define DataDisplay 0x10000     //IIS Master Data Display Count
//#define DataCount   0x100       //IIS Master/Slave Data Rx/Tx Count

#define PollMode    0           //1: Polling Mode
#define DMA2Mode    1           //1: DMA2 Mode

unsigned char  *Buf,*_temp;
unsigned short *rec_buf;

volatile unsigned int size = 0;
volatile unsigned int   fs = 0;
volatile char    which_Buf = 1;
volatile char     Rec_Done = 0;
volatile char         mute = 1;

volatile char    dma2_done = 0;
//------------------------------------------------------------------------------
//      SMDK2410 IIS Configuration
// GPB4 = L3CLOCK, GPB3 = L3DATA, GPB2 = L3MODE
// GPE4 = I2SSDO,  GPE3 = I2SSDI, GPE2 = CDCLK, GPE1 = I2SSCLK, GPE0 = I2SLRCK  
//------------------------------------------------------------------------------


//*********************[ Play_Iis ] *********************************
void Play_Iis(void)
{
    unsigned int save_G, save_E, save_PG, save_PE;

    Uart_TxEmpty(0);
    
    ChangeClockDivider(1,1);        //1:2:4
    ChangeMPllValue(0x96,0x5,0x1);  //FCLK=135.428571MHz (PCLK=33.857142MHz)

    Uart_Init(33857142,115200);    
    
    PRINTF("--------放音测试--------\n");
    
    save_G  = rGPGCON;       
    save_E  = rGPECON;       
    save_PG = rGPGUP;
    save_PE = rGPEUP;

    IIS_PortSetting();

    pISR_DMA2  = (unsigned)DMA2_Done;

      //Non-cacheable area = 0x31000000 ~ 0x33feffff
    Buf   = (unsigned char *)__IIS_WAV__;

	size = *((Buf) + 0x28) | *((Buf) + 0x29)<<8 | *((Buf) + 0x2a)<<16 | *((Buf) + 0x2b)<<24;

    fs   = *((Buf) + 0x18) | *((Buf) + 0x19)<<8 | *((Buf) + 0x1a)<<16 | *((Buf) + 0x1b)<<24;

    PRINTF("[1] 采样点 = 0x%x\n",size/2);
    PRINTF("[2] 采样频率 = %d Hz\n",fs);
    PRINTF("[3] 请接上耳机\n");
    PRINTF("[4] 开始放音\n");

    Init1341(PLAY);

    //DMA2 Initialize
    rDISRC2  = (int)(Buf + 0x2c);               //0x31000030~(Remove header)      
    rDISRCC2 = (0<<1) + (0<<0);                 //The source is in the system bus(AHB), Increment      
    rDIDST2  = ((U32)IISFIFO);                  //IISFIFO    
    rDIDSTC2 = (1<<1) + (1<<0);                 //The destination is in the peripheral bus(APB), Fixed  
    rDCON2   = (1<<31)+(0<<30)+(1<<29)+(0<<28)+(0<<27)+(0<<24)+(1<<23)+(0<<22)+(1<<20)+(size/4);
    //1010 0000 1001 xxxx xxxx xxxx xxxx xxxx
    //Handshake[31], Sync PCLK[30], CURR_TC Interrupt Request[29], Single Tx[28], Single service[27], 
    //I2SSDO[26:24], DMA source selected[23],Auto-reload[22], Half-word[21:20], size/2[19:0]
      
    rDMASKTRIG2 = (0<<2) + (1<<1) + (0<<0);          //No-stop[2], DMA2 channel On[1], No-sw trigger[0] 

      //IIS Initialize
    if(fs==44100)               //11.2896MHz(256fs)
        rIISPSR = (2<<5) + 2;   //Prescaler A,B=2 <- FCLK 135.4752MHz(1:2:4)     
    else                        //fs=22050, 5.6448MHz(256fs)
        rIISPSR = (5<<5) + 5;   //Prescaler A,B=5 <- FCLK 135.4752MHz(1:2:4)  
        
    rIISCON = (1<<5) + (1<<2) + (1<<1);         //Tx DMA enable[5], Rx idle[2], Prescaler enable[1]
      //Master mode[8],Tx mode[7:6],Low for Left Channel[5],IIS format[4],16bit ch.[3],CDCLK 256fs[2],IISCLK 32fs[1:0]
    rIISMOD = (0<<8) + (2<<6) + (0<<5) + (0<<4) + (1<<3) + (0<<2) + (1<<0);
    
    rIISFCON = (1<<15) + (1<<13);        //Tx DMA,Tx FIFO --> start piling....
    
      //IIS Tx Start
    rIISCON |= 0x1;             //IIS Interface start
    rINTMSK    &= ~(/*BIT_EINT0 | BIT_UART0 |*/ BIT_DMA2);   
    ClearPending(BIT_DMA2);     //Clear pending bit

    dma2_done = 0;
    while(dma2_done == 0) Delay(1);
    dma2_done = 0;
    PRINTF("    放音结束\n");

      //IIS Tx Stop
    Delay(10);                   //For end of H/W Tx
    rIISCON      = 0x0;          //IIS Interface stop
    rDMASKTRIG2  = (1<<2);       //DMA2 stop
    rIISFCON     = 0x0;          //For FIFO flush

    size = 0;

    rGPGCON = save_G;
    rGPECON = save_E;
    rGPGUP  = save_PG;
    rGPEUP  = save_PE;

    rINTMSK |= (BIT_DMA2);

    ChangeMPllValue(0xa1,0x3,0x1);    // FCLK=202.8MHz
    Uart_Init(0,115200);
    mute = 1;
    PRINTF("------放音测试结束------\n\n");
}

//**************** [ Record_Iis ] ***************************************
void Record_Iis(void)
{
    unsigned int save_G, save_E, save_PG, save_PE;

    Uart_TxEmpty(0);

    ChangeClockDivider(1,1);        //1:2:4
    ChangeMPllValue(0x96,0x5,0x1);  //FCLK=135428571Hz, PCLK=3.385714MHz

    Uart_Init(33857142,115200);
    
    PRINTF("--------录音测试--------\n");
    PRINTF("[1] 请接上耳机和麦克风\n");
    
    save_G  = rGPGCON;       
    save_E  = rGPECON;       
    save_PG = rGPGUP;
    save_PE = rGPEUP;

    IIS_PortSetting();
        
      //Record Buf initialize, Non-cacheable area = 0x31000000 ~ 0x33feffff
    rec_buf = (unsigned short *)0x31000000;

    pISR_DMA2  = (unsigned)DMA2_Rec_Done;
    pISR_EINT0 = (unsigned)Muting;

    rINTMSK &= ~(BIT_DMA2);

    Init1341(RECORD);

      //--- DMA2 Initialize
    rDISRCC2 = (1<<1) + (1<<0);                         //APB, Fix  
    rDISRC2  = ((U32)IISFIFO);                          //IISFIFO
    rDIDSTC2 = (0<<1) + (0<<0);                         //PHB, Increment
    rDIDST2  = (int)rec_buf;                            //0x31000000 ~
    rDCON2   = (1<<31)+(0<<30)+(1<<29)+(0<<28)+(0<<27)+(1<<24)+(1<<23)+(1<<22)+(1<<20)+REC_LEN;
      //Handshake, sync PCLK, TC int, single tx, single service, I2SSDI, I2S Rx request, 
      //Off-reload, half-word, 0x50000 half word.
    rDMASKTRIG2 = (0<<2) + (1<<1) + 0;    //No-stop, DMA2 channel on, No-sw trigger

      //IIS Initialize
      //Master,Rx,L-ch=low,IIS,16bit ch,CDCLK=256fs,IISCLK=32fs
    rIISMOD = (0<<8) + (1<<6) + (0<<5) + (0<<4) + (1<<3) + (0<<2) + (1<<0);
    rIISPSR = (2<<5) + 2; //Prescaler_A/B=2 <- FCLK 135.4752MHz(1:2:4),11.2896MHz(256fs),44.1KHz
    rIISCON = (0<<5) + (1<<4) + (1<<3) + (0<<2) + (1<<1);
      //Tx DMA disable,Rx DMA enable,Tx idle,Rx not idle,prescaler enable,stop
    rIISFCON = (1<<14) + (1<<12);     //Rx DMA,Rx FIFO --> start piling....

    PRINTF("[2] 开始录音...\n");

      //Rx start
    rIISCON |= 0x1;

    while(!Rec_Done) Delay(1);

    rINTMSK  |= BIT_DMA2;
    Rec_Done = 0;
	PRINTF("    录音完毕\n");

      //IIS Stop
    Delay(10);                          //For end of H/W Rx
    rIISCON     = 0x0;                  //IIS stop
    rDMASKTRIG2 = (1<<2);               //DMA2 stop
    rIISFCON    = 0x0;                  //For FIFO flush
    
    size = REC_LEN * 2;
    PRINTF("[3] 播放录音数据...\n");
    PRINTF("    采样点 = %d\n",size);

    Init1341(PLAY);

    pISR_DMA2 = (unsigned)DMA2_Done;
    rINTMSK   &= ~(BIT_DMA2 | BIT_EINT0);

      //DMA2 Initialize
    rDISRCC2 = (0<<1) + (0<<0);                         //AHB, Increment
    rDISRC2  = (int)rec_buf;                            //0x31000000
    rDIDSTC2 = (1<<1) + (1<<0);                         //APB, Fixed
    rDIDST2  = ((U32)IISFIFO);                          //IISFIFO
    rDCON2   = (1<<31)+(0<<30)+(1<<29)+(0<<28)+(0<<27)+(0<<24)+(1<<23)+(0<<22)+(1<<20)+(size/2);
      //Handshake, sync PCLK, TC int, single tx, single service, I2SSDO, I2S request, 
      //Auto-reload, half-word, size/2
    rDMASKTRIG2 = (0<<2)+(1<<1)+0;    //No-stop, DMA2 channel on, No-sw trigger 

      //IIS Initialize
      //Master,Tx,L-ch=low,iis,16bit ch.,CDCLK=256fs,IISCLK=32fs
    rIISMOD = (0<<8) + (2<<6) + (0<<5) + (0<<4) + (1<<3) + (0<<2) + (1<<0);      
//  rIISPSR = (4<<5) + 4;            //Prescaler_A/B=4 for 11.2896MHz
    rIISCON = (1<<5)+(0<<4)+(0<<3)+(1<<2)+(1<<1);
      //Tx DMA enable,Tx DMA disable,Tx not idle,Rx idle,prescaler enable,stop
    rIISFCON = (1<<15) + (1<<13);       //Tx DMA,Tx FIFO --> start piling....

    rIISCON |= 0x1;                   //IIS Tx Start
    dma2_done = 0;
    while(dma2_done == 0);
    dma2_done = 0;

      //IIS Tx Stop
    Delay(10);               //For end of H/W Tx
    rIISCON     = 0x0;       //IIS stop
    rDMASKTRIG2 = (1<<2);    //DMA2 stop
    rIISFCON    = 0x0;       //For FIFO flush

    size = 0;

    rGPGCON = save_G;
    rGPECON = save_E;
    rGPGUP  = save_PG;
    rGPEUP  = save_PE;

    rINTMSK |= (BIT_DMA2 | BIT_EINT0);
    
    ChangeMPllValue(0xa1,0x3,0x1);              // FCLK=202.8MHz
    Uart_Init(0,115200);
    mute = 1;
    PRINTF("------录音测试结束------\n\n");
}

//******************[ Init1341 ]**************************************
void Init1341(char mode)
{
    //Port Initialize
    //Port Initialize
    //----------------------------------------------------------
    //   PORT G GROUP
    //Ports  :   GPG6    GPG7   GPG5  
    //Signal :  L3CLOCK L3DATA L3MODE
    //Setting:   OUTPUT OUTPUT OUTPUT 
    //           [13:12]   [15:14}  [11:10]
    //Binary :     01  ,   01    01 
    //----------------------------------------------------------    
    rGPGDAT = rGPGDAT & ~(L3M|L3C|L3D) |(L3M|L3C); //Start condition : L3M=H, L3C=H
    rGPGUP  = rGPGUP  & ~(0x7<<5) |(0x7<<5);       //The pull up function is disabled GPB[4:2] 1 1100    
    rGPGCON = rGPGCON & ~(0x3f<<10) |(0x15<<10);     //GPG[15:10]=Output(L3CLOCK):Output(L3DATA):Output(L3MODE)

      //L3 Interface
    _WrL3Addr(0x14 + 2);     //STATUS (000101xx+10)
    _WrL3Data(0x60,0);       //0,1,10, 000,0 : Status 0,Reset,256fs,IIS-bus,no DC-filtering

    _WrL3Addr(0x14 + 2);     //STATUS (000101xx+10)
    _WrL3Data(0x20,0);       //0,0,10, 000,0 : Status 0,No reset,256fs,IIS-bus,no DC-filtering
    
    _WrL3Addr(0x14 + 2);     //STATUS (000101xx+10)
    _WrL3Data(0x81,0);       //1,0,0,0, 0,0,01 
                             //Status 1,Gain of DAC 0 dB,Gain of ADC 0dB,ADC non-inverting,DAC non-inverting
                             //,Single speed playback,ADC-Off DAC-On
    
      //Record
    if(mode)
    {
        _WrL3Addr(0x14 + 2);    //STATUS (000101xx+10)
//        _WrL3Data(0xa2,0);      //1,0,1,0, 0,0,10 
                                //Status 1,Gain of DAC 0 dB,Gain of ADC 6dB,ADC non-inverting,DAC non-inverting
                                //,Single speed playback,ADC-On DAC-Off       
                                
        _WrL3Data(0xe3,0);      //1,1,1,0, 0,0,11 
                                //Status 1,Gain of DAC 6 dB,Gain of ADC 6dB,ADC non-inverting,DAC non-inverting
                                //,Single speed playback,ADC-On DAC-On                                   

//        _WrL3Addr(0x14 + 0);    //DATA0 (000101xx+00)
//        _WrL3Data(0x3f,0);      //00,11 1111  : Volume control (6 bits)  
//        _WrL3Data(0x00,0);      //00,00 0000  : Volume control (6 bits) 0dB    

        _WrL3Addr(0x14 + 0);    //DATA0 (000101xx+00)
        _WrL3Data(0x7b,0);      //01,11 10,11 : Data0, Bass Boost 18~24dB, Treble 6dB             

//        _WrL3Addr(0x14 + 0);    //DATA0 (000101xx+00)        
        _WrL3Data(0xc4,0);      //1100 0,100  : Extended addr(3bits), 100 
        _WrL3Data(0x91,0);      //100,1 00,01 : DATA0, Enable AGC, 00, input amplifier gain channel 2 (2bits)                                  

//        _WrL3Addr(0x14 + 0);    //DATA0 (000101xx+00)
        _WrL3Data(0xc2,0);      //1100 0,010  : Extended addr(3bits), 010 
//        _WrL3Data(0x4d,0);      //010,0 11,01 : DATA0, MIC Amplifier Gain 9dB, input channel 1 select(input channel 2 off) 
        _WrL3Data(0x59,0);      //010,1 10,01 : DATA0, MIC Amplifier Gain 27dB, input channel 1 select(input channel 2 off)
//        _WrL3Data(0x41,0);      //010,0 00,01 : DATA0, MIC Amplifier Gain -3dB, input channel 1 select(input channel 2 off)
    }

}

//===================================================================
void ChangeDMA2(void)
{
    if(which_Buf)
    {
        rDISRCC2 = (0<<1) + (0<<0);                         //AHB, Increment
        rDISRC2  = (int)(Buf + 0x30);                       //0x31000030~(Remove header)
    }
    else
    {
        rDISRCC2 = (0<<1) + (0<<0);                         //AHB, Increment
        rDISRC2  = (int)(Buf + 0x30+(size/2));              //0x31000030 + size/2~
    }
}

//===================================================================
void IIS_PortSetting(void)
{
    //Port Initialize
    //----------------------------------------------------------
    //   PORT G GROUP
    //Ports  :   GPG6    GPG7   GPG5  
    //Signal :  L3CLOCK L3DATA L3MODE
    //Setting:   OUTPUT OUTPUT OUTPUT 
    //           [13:12]   [15:14}  [11:10]
    //Binary :     01  ,   01    01 
    //----------------------------------------------------------    
    rGPGUP  = rGPGUP  & ~(0x7<<5) | (0x7<<5);   //The pull up function is disabled GPB[4:2] 1 1100    
    rGPGCON = rGPGCON & ~(0x3f<<10) | (0x15<<10); //GPG[13:10]=Output(L3CLOCK):Output(L3DATA):Output(L3MODE)

//----------------------------------------------------------
//   PORT E GROUP
//Ports  :  GPE4    GPE3   GPE2  GPE1    GPE0 
//Signal : I2SSDO  I2SSDI CDCLK I2SSCLK I2SLRCK 
//Binary :   10  ,   10     10 ,  10      10    
//----------------------------------------------------------
    rGPEUP  = rGPEUP  & ~(0x1f)  | 0x1f;    //The pull up function is disabled GPE[4:0] 1 1111
    rGPECON = rGPECON & ~(0x3ff) | 0x2aa;   //GPE[4:0]=I2SSDO:I2SSDI:CDCLK:I2SSCLK:I2SLRCK

    rGPFUP   = ((rGPFUP   & ~(1<<0)) | (1<<0));     //GPF0
    rGPFCON  = ((rGPFCON  & ~(3<<0)) | (1<<1));     //GPF0=EINT0    
    
    rEXTINT0 = ((rEXTINT0 & ~(7<<0)) | (2<<0));     //EINT0=falling edge triggered  
}

//===================================================================
void _WrL3Addr(U8 data)
{       
    S32 i,j;

    rGPGDAT  = rGPGDAT & ~(L3D | L3M | L3C) | L3C;      //L3D=L, L3M=L(in address mode), L3C=H

    for(j=0;j<4;j++);                   //tsu(L3) > 190ns

      //GPB[4:2]=L3C:L3D:L3M
    for(i=0;i<8;i++)                    //LSB first
    {
        if(data & 0x1)                  //If data's LSB is 'H'
        {
            rGPGDAT &= ~L3C;            //L3C=L
            rGPGDAT |= L3D;             //L3D=H             
            for(j=0;j<4;j++);           //tcy(L3) > 500ns
            rGPGDAT |= L3C;             //L3C=H
            rGPGDAT |= L3D;             //L3D=H
            for(j=0;j<4;j++);           //tcy(L3) > 500ns
        }
        else                            //If data's LSB is 'L'
        {
            rGPGDAT &= ~L3C;            //L3C=L
            rGPGDAT &= ~L3D;            //L3D=L
            for(j=0;j<4;j++);           //tcy(L3) > 500ns
            rGPGDAT |= L3C;             //L3C=H
            rGPGDAT &= ~L3D;            //L3D=L
            for(j=0;j<4;j++);           //tcy(L3) > 500ns            
        }
        data >>= 1;
    }
    rGPGDAT  = rGPGDAT & ~(L3D | L3M | L3C) | (L3C | L3M);       //L3M=H,L3C=H   
}

//===================================================================
void _WrL3Data(U8 data,int halt)
{
    S32 i,j;

    if(halt)
    {
        rGPGDAT  = rGPGDAT & ~(L3D | L3M | L3C) | L3C;   //L3C=H(while tstp, L3 interface halt condition)        
        for(j=0;j<4;j++);                                //tstp(L3) > 190ns
    }

    rGPGDAT  = rGPGDAT & ~(L3D | L3M | L3C) | (L3C | L3M);   //L3M=H(in data transfer mode)        
    for(j=0;j<4;j++);                                        //tsu(L3)D > 190ns

      //GPB[4:2]=L3C:L3D:L3M
    for(i=0;i<8;i++)
    {
        if(data & 0x1)                   //if data's LSB is 'H'
        {
           rGPGDAT &= ~L3C;              //L3C=L
           rGPGDAT |= L3D;               //L3D=H
           for(j=0;j<4;j++);             //tcy(L3) > 500ns
           rGPGDAT |= (L3C | L3D);       //L3C=H,L3D=H
           for(j=0;j<4;j++);             //tcy(L3) > 500ns
        }
        else                             //If data's LSB is 'L'
        {
           rGPGDAT &= ~L3C;              //L3C=L
           rGPGDAT &= ~L3D;              //L3D=L
           for(j=0;j<4;j++);             //tcy(L3) > 500ns
           rGPGDAT |= L3C;               //L3C=H
           rGPGDAT &= ~L3D;              //L3D=L
           for(j=0;j<4;j++);             //tcy(L3) > 500ns
        }
        data >>= 1;                      //For check next bit
    }
    rGPGDAT  = rGPGDAT & ~(L3D | L3M | L3C) | (L3C | L3M);    //L3M=H,L3C=H
}

//===================================================================
void DMA2_Done(void)
{
    ClearPending(BIT_DMA2);     //Clear pending bit

	dma2_done = 1;
	
    if(!which_Buf)
        which_Buf = 1;
    else
        which_Buf = 0;
}

//===================================================================
void DMA2_Rec_Done(void)
{
    ClearPending(BIT_DMA2);     //Clear pending bit
    Rec_Done = 1;
}

//===================================================================
void RxInt(void)
{
    rSUBSRCPND = BIT_SUB_RXD0;          //Clear pending bit (Requested)
    rSUBSRCPND;
    ClearPending(BIT_UART0);

    *_temp ++= RdURXH0(); 
}

//===================================================================
void Muting(void)
{
    ClearPending(BIT_EINT0);            //Clear pending bit

    if(mute)    //Mute
    {
        _WrL3Addr(0x14 + 0);            //DATA0 (000101xx+00)
        _WrL3Data(0xa4,0);              //10,1,00,1,00 : after, no de-emp, mute, flat 
        mute = 0;
        PRINTF("= Mute =\n");
    }
    else        //No mute
    {
        _WrL3Addr(0x14 + 0);            //DATA0 (000101xx+00)
        _WrL3Data(0xa0,0);              //10,1,00,0,00 : after, no de-emp, no mute, flat 
        mute = 1;
        PRINTF("= No Mute =\n");
    }
}

//=======[ Added Slave mode Test Program as Bellow --> July 24, 2002 Tark, SOP ]=====

volatile int Tx_Done;
volatile int Rx_Done;

void TR_Done(void)
{
    ClearPending(BIT_DMA2);     //Clear pending bit

    Rx_Done = 1;
    Tx_Done = 1;
//    WrUTXH0('.');
}

void iis_init(char mode)
{
	if(mode == PLAY)
	{
	}else if(mode == RECORD)
	{
	}
}

//===================================================================
void Iis_Tx(void)
{
    unsigned int i, j;
    unsigned short *txdata;

    Tx_Done = 0;
    Uart_TxEmpty(0);

    PRINTF("[ IIS Slave Tx test ]\n");

    IIS_PortSetting();

      //Tx DATA initialize 
    txdata = (unsigned short *)0x31000000;
    
    for(i=0;i<DataCount;i++)
        *(txdata+i) = i;    

      //IIS Initialize
      //Slave[8],Tx[7:6],L-ch=low[5],MSB[4],16bit ch[3],CDCLK[2]=256fs,IISCLK[1:0]=32fs
    rIISMOD  = (1<<8) + (2<<6) + (0<<5) + (1<<4) + (1<<3) + (0<<2) + (1<<0);
    rIISPSR  = (2<<5) + 2;              //Prescaler_A/B=2 <- FCLK 135.4752MHz(1:2:4),11.2896MHz(256fs),44.1KHz
    rIISFCON = (0<<15) + (1<<13);       //Tx Normal[15],Tx FIFO Enable[13] --> start piling....  
      //Tx DMA disable[5],Rx DMA disable[4],Tx not idle[3],Rx idle[2],prescaler enable[1],stop[0]
    rIISCON  = (0<<5) + (0<<4) + (0<<3) + (1<<2) + (1<<1) + (0<<0);            
   
      //Tx start
    rIISCON |=0x1;
    
    for(i=0;i<DataCount;i++)
    {
        while( (rIISCON & 0x080) == 0x80 );     //wait when fifo is not empty.
        *IISFIFO = *(txdata+i);                 // put the data into fifo        
    }

      //Tx Stop(Slave)
    Delay(10);
    rIISCON     = 0x0;          //IIS stop
    rDMASKTRIG2 = (1<<2);       //DMA2 stop
    rIISFCON    = 0x0;          //for FIFO flush

    PRINTF("\nTx End...\n");

    PRINTF("Last 256 Half-Word in 65KBytes transferred data\n");
    
    for(i=0;i<DataDisplay;i++)
    {
        PRINTF("0x%x=",(txdata+0xff00+i));
        PRINTF("%04x   ",*(txdata+0xff00+i));        
    }
}
  
//===================================================================
void Iis_Rx(void)
{
    unsigned int i, j, k, count;
    unsigned short *rxdata;

    Rx_Done = 0;
    Uart_TxEmpty(0);

#if PollMode
    PRINTF("[ IIS Master Rx Polling mode test ]\n");
#endif

#if DMA2Mode
    PRINTF("[ IIS Master Rx DMA2 mode test ]\n");
#endif
    
    IIS_PortSetting();

    pISR_DMA2= (unsigned)TR_Done;
    rINTMSK  &= ~(BIT_DMA2);

      //Rx Buf initialize
    rxdata=(unsigned short *)0x31000000;
    
    for(i=0;i<DataCount;i++)
        *(rxdata+i)=0x0;
        
#if DMA2Mode
      //DMA2 Initialize
    rDISRCC2 = (1<<1) + (1<<0);     //The source is in the system bus(APB), address Fixed
    rDISRC2  = ((U32)IISFIFO);      //Base address (start address) of source to transfer(IISFIFO)
    rDIDSTC2 = (0<<1) + (0<<0);     //The destination is in the system bus (AHB), address Increment.
    rDIDST2  = (int)rxdata;         //Base address (start address) of destination to transfer(0x31000000)
    rDCON2   = (1<<31)+(0<<30)+(1<<29)+(0<<28)+(0<<27)+(1<<24)+(1<<23)+(1<<22)+(1<<20)+(DataCount);
      //Handshake[31], sync PCLK[30], TC int[29], single tx[28], single service[27], I2SSDI[24], I2S request[23], 
      //off-reload[22], half-word[20], Initial transfer count=DataCount      
    rDMASKTRIG2 = (0<<2)+(1<<1)+0;  //No-stop, DMA2 channel on, No-sw trigger 
 
      //IIS Initialize (DMA Mode)
      //Master[8],Rx[7:6],L-ch=low[5],MSB[4],16bit ch[3],CDCLK[2]=256fs,IISCLK[1:0]=32fs
    rIISMOD  = (0<<8) + (1<<6) + (0<<5) + (1<<4) + (1<<3) + (0<<2) + (1<<0);
    rIISPSR  = (2<<5) + 2;            //Prescaler_A/B=2 <- FCLK 135.4752MHz(1:2:4),11.2896MHz(256fs),44.1KHz
    rIISFCON = (1<<14) + (1<<12);     //Rx DMA[14],Rx FIFO Enable[12]--> start piling....    
      //Tx DMA disable[5],Rx DMA enable[4],Tx idle[3],Rx not idle[2],prescaler enable[1],stop[0]
    rIISCON  = (0<<5) + (1<<4) + (1<<3) + (0<<2) + (1<<1) + (0<<0);    
#endif

#if PollMode
      //IIS Initialize (Polling Mode)
      //Master[8],Rx[7:6],L-ch=low[5],MSB[4],16bit ch[3],CDCLK[2]=256fs,IISCLK[1:0]=32fs
    rIISMOD  = (0<<8) + (1<<6) + (0<<5) + (1<<4) + (1<<3) + (0<<2) + (1<<0);
    rIISPSR  = (2<<5) + 2;            //Prescaler_A/B=2 <- FCLK 135.4752MHz(1:2:4),11.2896MHz(256fs),44.1KHz
    rIISFCON = (0<<14) + (1<<12);     //Rx normal[14],Rx FIFO Enable[12]--> start piling.... 
      //Tx DMA disable[5],Rx DMA disable[4],Tx idle[3],Rx not idle[2],prescaler enable[1],stop[0]
    rIISCON  = (0<<5) + (0<<4) + (1<<3) + (0<<2) + (1<<1) + (0<<0);    
#endif

      //Rx start
    rIISCON |= 0x1;

#if PollMode       //*** Need to Polling mode ***
    count = DataCount;                 
    while(0<count) 
    {
        j = rIISFCON & 0x1f;            //Rx FIFO data count(Read only)=31
        if(j == 0)
        {
            while(!j)
                j = rIISFCON & 0x1f;    //Rx FIFO data count(Read only)=31
         }
        
        for(i=0;i<j;i++)
        {
            count--;
            *rxdata++ = *IISFIFO;                   
        }
    }
#endif    

#if DMA2Mode  
    while(!Rx_Done);
#endif

      //Rx Stop(Master)
    Delay(10);
    rIISCON     = 0x0;          //IIS stop
    rDMASKTRIG2 = (1<<2);       //DMA2 stop
    rIISFCON    = 0x0;          //for FIFO flush

    PRINTF("Last 256 Half-Word in 65KBytes received data\n");

    rxdata=(unsigned short *)0x31000000;  
    
    for(i=0;i<DataDisplay;i++)
    {
        PRINTF("0x%x=", (rxdata+0xff00+i));        
        PRINTF("%04x   ",*(rxdata+0xff00+i));                
    }
    rINTMSK &= (BIT_DMA2);
}
