//===================================================================
// File Name : 2410lib.c
// Function  : S3C2410 PLL,Uart, LED, Port Init
// Program   : Shin, On Pil (SOP)
// Date      : May 14, 2002
// Version   : 0.0
// History
//   0.0 : Programming start (February 20,2002) -> SOP
//===================================================================

#include "def.h"
#include "2410lib.h"
#include "option.h"
#include "2410addr.h"
#include "interrupt.h"

#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

extern char Image_RW_Limit[];
void *mallocPt=Image_RW_Limit;

//===========================[ SYSTEM ]===================================================
//static int delayLoopCount = 400;
static int delayLoopCount = FCLK/10000/10;

void Delay(int time)
{
      // time=0: adjust the Delay function by WatchDog timer.
      // time>0: the number of loop time
      // resolution of time is 100us.
    int i,adjust=0;
    if(time==0)
    {
        time   = 200;
        adjust = 1;
        delayLoopCount = 400;
            //PCLK/1M,Watch-dog disable,1/64,interrupt disable,reset disable
        rWTCON = ((PCLK/1000000-1)<<8)|(2<<3); 
        rWTDAT = 0xffff;                              //for first update
        rWTCNT = 0xffff;                              //resolution=64us @any PCLK 
        rWTCON = ((PCLK/1000000-1)<<8)|(2<<3)|(1<<5); //Watch-dog timer start
    }
    for(;time>0;time--)
        for(i=0;i<delayLoopCount;i++);
    if(adjust==1)
    {
        rWTCON = ((PCLK/1000000-1)<<8)|(2<<3);   //Watch-dog timer stop
        i = 0xffff - rWTCNT;                     //1count->64us, 200*400 cycle runtime = 64*i us
        delayLoopCount = 8000000/(i*64);         //200*400:64*i=1*x:100 -> x=80000*100/(64*i)   
    }
}

//===========================[ PORTS ]===================================================*
/********************************************************************
// Function name	: Port_Init
// Description	    : JXARM9-2410端口初始化
// Return type		: void
// Argument         : void
*********************************************************************/
void Port_Init(void)
{
    //CAUTION:Follow the configuration order for setting the ports. 
    // 1) setting value(GPnDAT) 
    // 2) setting control register  (GPnCON)
    // 3) configure pull-up resistor(GPnUP)  

    //32bit data bus configuration  
    //=== PORT A GROUP
    //Ports  : GPA22 GPA21  GPA20 GPA19 GPA18 GPA17 GPA16 GPA15 GPA14 GPA13 GPA12  
    //Signal : nFCE nRSTOUT nFRE   nFWE  ALE   CLE  nGCS5 nGCS4 nGCS3 nGCS2 nGCS1 
    //Binary :  1     1      1  , 1   1   1    1   ,  1     1     1     1
    //Ports  : GPA11   GPA10  GPA9   GPA8   GPA7   GPA6   GPA5   GPA4   GPA3   GPA2   GPA1  GPA0
    //Signal : ADDR26 ADDR25 ADDR24 ADDR23 ADDR22 ADDR21 ADDR20 ADDR19 ADDR18 ADDR17 ADDR16 ADDR0 
    //Binary :  1       1      1      1   , 1       1      1      1   ,  1       1     1      1         
    rGPACON = 0x7fffff; 

    //===* PORT B GROUP
    //Ports  : GPB10    GPB9    GPB8    GPB7    GPB6     GPB5    GPB4   GPB3   GPB2     GPB1      GPB0
    //Signal : nXDREQ0 nXDACK0 nXDREQ1 nXDACK1 nSS_KBD nDIS_OFF L3CLOCK L3DATA L3MODE nIrDATXDEN Keyboard
    //Setting: INPUT  OUTPUT   INPUT  OUTPUT   INPUT   OUTPUT   OUTPUT OUTPUT OUTPUT   OUTPUT    OUTPUT 
    //Binary :   00  ,  01       00  ,   01      00   ,  01       01  ,   01     01   ,  01        01  
    rGPBCON = 0x044555;
    rGPBUP  = 0x7ff;     // The pull up function is disabled GPB[10:0]

    //=== PORT C GROUP
    //Ports  : GPC15 GPC14 GPC13 GPC12 GPC11 GPC10 GPC9 GPC8  GPC7   GPC6   GPC5 GPC4 GPC3  GPC2  GPC1 GPC0
    //Signal : VD7   VD6   VD5   VD4   VD3   VD2   VD1  VD0 LCDVF2 LCDVF1 LCDVF0 VM VFRAME VLINE VCLK LEND  
    //Binary :  10   10  , 10    10  , 10    10  , 10   10  , 10     10  ,  10   10 , 10     10 , 10   10
    rGPCCON = 0xaaaaaaaa;       
    rGPCUP  = 0xffff;     // The pull up function is disabled GPC[15:0] 

    //=== PORT D GROUP
    //Ports  : GPD15 GPD14 GPD13 GPD12 GPD11 GPD10 GPD9 GPD8 GPD7 GPD6 GPD5 GPD4 GPD3 GPD2 GPD1 GPD0
    //Signal : VD23  VD22  VD21  VD20  VD19  VD18  VD17 VD16 VD15 VD14 VD13 VD12 VD11 VD10 VD9  VD8
    //Binary : 10    10  , 10    10  , 10    10  , 10   10 , 10   10 , 10   10 , 10   10 ,10   10
    rGPDCON = 0xaaaaaaaa;       
    rGPDUP  = 0xffff;     // The pull up function is disabled GPD[15:0]

    //=== PORT E GROUP
    //Ports  : GPE15  GPE14 GPE13   GPE12   GPE11   GPE10   GPE9    GPE8     GPE7  GPE6  GPE5   GPE4  
    //Signal : IICSDA IICSCL SPICLK SPIMOSI SPIMISO SDDATA3 SDDATA2 SDDATA1 SDDATA0 SDCMD SDCLK I2SSDO 
    //Binary :  10     10  ,  10      10  ,  10      10   ,  10      10   ,   10    10  , 10     10  ,     
    //-------------------------------------------------------------------------------------------------------
    //Ports  :  GPE3   GPE2  GPE1    GPE0    
    //Signal : I2SSDI CDCLK I2SSCLK I2SLRCK     
    //Binary :  10     10  ,  10      10 
    rGPECON = 0xaaaaaaaa;       
    rGPEUP  = 0xffff;     // The pull up function is disabled GPE[15:0]

    //=== PORT F GROUP
    //Ports  : GPF7   GPF6   GPF5   GPF4      GPF3     GPF2  GPF1   GPF0
    //Signal : nLED_8 nLED_4 nLED_2 nLED_1 nIRQ_PCMCIA EINT2 KBDINT EINT0
    //Setting: Output Output Output Output    EINT3    EINT2 EINT1  EINT0
    //Binary :  01      01 ,  01     01  ,     10       10  , 10     10
    rGPFCON = 0x55aa;
    rGPFUP  = 0xff;     // The pull up function is disabled GPF[7:0]

#if 0       // LIUSJ, Commented for AIJI
    //*** PORT G GROUP
    //Ports  : GPG15 GPG14 GPG13 GPG12 GPG11    GPG10    GPG9     GPG8     GPG7      GPG6    
    //Signal : nYPON  YMON nXPON XMON  EINT19 DMAMODE1 DMAMODE0 DMASTART KBDSPICLK KBDSPIMOSI
    //Setting: nYPON  YMON nXPON XMON  EINT19  Output   Output   Output   SPICLK1    SPIMOSI1
    //Binary :   11    11 , 11    11  , 10      01    ,   01       01   ,    11         11
    //-----------------------------------------------------------------------------------------
    //Ports  :    GPG5       GPG4    GPG3    GPG2    GPG1    GPG0    
    //Signal : KBDSPIMISO LCD_PWREN EINT11 nSS_SPI IRQ_LAN IRQ_PCMCIA
    //Setting:  SPIMISO1  LCD_PWRDN EINT11   nSS0   EINT9    EINT8
    //Binary :     11         11   ,  10      11  ,  10        10
    rGPGCON = 0xff95ffba;
    rGPGUP  = 0xffff;    // The pull up function is disabled GPG[15:0]
#else     
	//config GPG15-12 to Touch Panel signals
	//config GPG11-10 to output pins
	//config GPG9-8   to output pins
	//config GPG7-5   to output pins ----Testpoints:TP6,4,2
	//config GPG4     to LCD Power Enable
	//config GPG3-2   to output pins ----Testpints:TP8,7
	//config GPG1-0   to output pins ----GPRS_boot and GPRS_PWR 
	rGPGCON = 0xff055555;
	rGPGUP  = 0xfffff;
#endif

/*    
    //GPG4 Output Port [9:8] 01      -> LCD_PWREN Enable
    rGPGCON = (rGPGCON & 0xfffffcff) | (1<<8);
    rGPGDAT = (rGPGDAT & 0xffef) | (1<<4);
*/
    //=== PORT H GROUP
    //Ports  :  GPH10    GPH9  GPH8 GPH7  GPH6  GPH5 GPH4 GPH3 GPH2 GPH1  GPH0 
    //Signal : CLKOUT1 CLKOUT0 UCLK nCTS1 nRTS1 RXD1 TXD1 RXD0 TXD0 nRTS0 nCTS0
    //Binary :   10   ,  10     10 , 11    11  , 10   10 , 10   10 , 10    10
    rGPHCON = 0x2afaaa;
    rGPHUP  = 0x7ff;    // The pull up function is disabled GPH[10:0]
    
    //External interrupt will be falling edge triggered. 
    rEXTINT0 = 0x22222222;    // EINT[7:0]
    rEXTINT1 = 0x22222222;    // EINT[15:8]
    rEXTINT2 = 0x22222222;    // EINT[23:16]
}

/* 当前UART号：0-UART0, 1-UART1, 2-UART2 */
static int whichUart=0;

/********************************************************************
// Function name	: Uart_Init
// Description	    : JXARM9-2410串口初始化
// Return type		: void
// Argument         : int pclk:APB总线时钟，0时使用缺省值PCLK
// Argument         : int baud:波特率
*********************************************************************/
void Uart_Init(int pclk,int baud)
{
    int i;
    
    if(pclk == 0)
    pclk    = PCLK;
    rUFCON0 = 0x0;   //UART channel 0 FIFO control register, FIFO disable
    rUFCON1 = 0x0;   //UART channel 1 FIFO control register, FIFO disable
    rUFCON2 = 0x0;   //UART channel 2 FIFO control register, FIFO disable
    rUMCON0 = 0x0;   //UART chaneel 0 MODEM control register, AFC disable
    rUMCON1 = 0x0;   //UART chaneel 1 MODEM control register, AFC disable

	/* 串口0 */    
    rULCON0 = 0x3;   //Line control register : Normal,No parity,1 stop,8 bits
     //    [10]       [9]     [8]        [7]        [6]      [5]         [4]           [3:2]        [1:0]
     // Clock Sel,  Tx Int,  Rx Int, Rx Time Out, Rx err, Loop-back, Send break,  Transmit Mode, Receive Mode
     //     0          1       0    ,     0          1        0           0     ,       01          01
     //   PCLK       Level    Pulse    Disable    Generate  Normal      Normal        Interrupt or Polling
    rUCON0  = 0x245;                        // Control register
    rUBRDIV0=( (int)(pclk/16./baud) -1 );   //Baud rate divisior register 0
    
	/* 串口1 */    
    rULCON1 = 0x3;
    rUCON1  = 0x245;
    rUBRDIV1=( (int)(pclk/16./baud) -1 );
    
	/* 串口2 */    
    rULCON2 = 0x3;
    rUCON2  = 0x245;
    rUBRDIV2=( (int)(pclk/16./baud) -1 );    

    for(i=0;i<100;i++);
}
/********************************************************************
// Function name	: Uart_Select
// Description	    : UART选择
// Return type		: void
// Argument         : int ch:UART号，0-UART0, 1-UART1, 2-UART2
*********************************************************************/
void Uart_Select(int ch)
{
    whichUart = ch;
}
/********************************************************************
// Function name	: Uart_TxEmpty
// Description	    : 清空UART发送缓冲区
// Return type		: void
// Argument         : int ch:UART号，0-UART0, 1-UART1, 2-UART2
*********************************************************************/
void Uart_TxEmpty(int ch)
{
    if(ch==0)
        while(!(rUTRSTAT0 & 0x4)); //Wait until tx shifter is empty.
          
    else if(ch==1)
        while(!(rUTRSTAT1 & 0x4)); //Wait until tx shifter is empty.
        
    else if(ch==2)
        while(!(rUTRSTAT2 & 0x4)); //Wait until tx shifter is empty.
}
/********************************************************************
// Function name	: Uart_Getch
// Description	    : 从串口接收字符，如果没有字符则一直等待
// Return type		: char:接收到的字符
// Argument         : void
*********************************************************************/
char Uart_Getch(void)
{
    if(whichUart==0)
    {       
        while(!(rUTRSTAT0 & 0x1)); //Receive data ready
        return RdURXH0();
    }
    else if(whichUart==1)
    {       
        while(!(rUTRSTAT1 & 0x1)); //Receive data ready
        return RdURXH1();
    }
    else if(whichUart==2)
    {
        while(!(rUTRSTAT2 & 0x1)); //Receive data ready
        return RdURXH2();
    }
}
/********************************************************************
// Function name	: Uart_GetKey
// Description	    : 从串口接收字符，如果没有字符则返回0
// Return type		: char:接收到的字符
// Argument         : void
*********************************************************************/
char Uart_GetKey(void)
{
    if(whichUart==0)
    {       
        if(rUTRSTAT0 & 0x1)    //Receive data ready
            return RdURXH0();
        else
            return 0;
    }
    else if(whichUart==1)
    {
        if(rUTRSTAT1 & 0x1)    //Receive data ready
            return RdURXH1();
        else
            return 0;
    }
    else if(whichUart==2)
    {       
        if(rUTRSTAT2 & 0x1)    //Receive data ready
            return RdURXH2();
        else
            return 0;
    }    
}
/********************************************************************
// Function name	: Uart_GetString
// Description	    : 从串口接收一个字符串，以回车键结束
// Return type		: void
// Argument         : char *string:收到的字符串
*********************************************************************/
void Uart_GetString(char *string)
{
    char *string2 = string;
    char c;
    while((c = Uart_Getch())!='\r')
    {
        if(c=='\b')
        {
            if( (int)string2 < (int)string )
            {
                Uart_Printf("\b \b");
                string--;
            }
        }
        else 
        {
            *string++ = c;
            Uart_SendByte(c);
        }
    }
    *string='\0';
    Uart_SendByte('\n');
}
/********************************************************************
// Function name	: Uart_GetIntNum
// Description	    : 从串口接收一个字符串，并将其解析为一个整数值
// Return type		: int:收到的整数值
// Argument         : void
*********************************************************************/
int Uart_GetIntNum(void)
{
    char str[30];
    char *string = str;
    int base     = 10;
    int minus    = 0;
    int result   = 0;
    int lastIndex;    
    int i;
    
    Uart_GetString(string);
    
    if(string[0]=='-')
    {
        minus = 1;
        string++;
    }
    
    if(string[0]=='0' && (string[1]=='x' || string[1]=='X'))
    {
        base    = 16;
        string += 2;
    }
    
    lastIndex = strlen(string) - 1;
    
    if(lastIndex<0)
        return -1;
    
    if(string[lastIndex]=='h' || string[lastIndex]=='H' )
    {
        base = 16;
        string[lastIndex] = 0;
        lastIndex--;
    }

    if(base==10)
    {
        result = atoi(string);
        result = minus ? (-1*result):result;
    }
    else
    {
        for(i=0;i<=lastIndex;i++)
        {
            if(isalpha(string[i]))
            {
                if(isupper(string[i]))
                    result = (result<<4) + string[i] - 'A' + 10;
                else
                    result = (result<<4) + string[i] - 'a' + 10;
            }
            else
                result = (result<<4) + string[i] - '0';
        }
        result = minus ? (-1*result):result;
    }
    return result;
}
/********************************************************************
// Function name	: Uart_SendByte
// Description	    : 通过串口发送字符
// Return type		: void
// Argument         : int data:待发送字符
*********************************************************************/
void Uart_SendByte(int data)
{
    if(whichUart==0)
    {
        if(data=='\n')
        {
            while(!(rUTRSTAT0 & 0x2));
//            Delay(10);                 //because the slow response of hyper_terminal 
            WrUTXH0('\r');
        }
        while(!(rUTRSTAT0 & 0x2));   //Wait until THR is empty.
//        Delay(10);
        WrUTXH0(data);
    }
    else if(whichUart==1)
    {
        if(data=='\n')
        {
            while(!(rUTRSTAT1 & 0x2));
//            Delay(10);                 //because the slow response of hyper_terminal 
            rUTXH1 = '\r';
        }
        while(!(rUTRSTAT1 & 0x2));   //Wait until THR is empty.
//        Delay(10);
        rUTXH1 = data;
    }   
    else if(whichUart==2)
    {
        if(data=='\n')
        {
            while(!(rUTRSTAT2 & 0x2));
//            Delay(10);                 //because the slow response of hyper_terminal 
            rUTXH2 = '\r';
        }
        while(!(rUTRSTAT2 & 0x2));   //Wait until THR is empty.
        Delay(10);
        rUTXH2 = data;
    }       
}               
/********************************************************************
// Function name	: Uart_SendString
// Description	    : 通过串口发送字符串
// Return type		: void
// Argument         : char *pt:字符串指针
*********************************************************************/
void Uart_SendString(char *pt)
{
    while(*pt)
        Uart_SendByte(*pt++);
}
/********************************************************************
// Function name	: Uart_Printf
// Description	    : 串口打印函数
// Return type		: void
// Argument         : char *fmt
// Argument         : ...
*********************************************************************/
void Uart_Printf(char *fmt,...)
{
    va_list ap;
    char string[256];

    va_start(ap,fmt);
    vsprintf(string,fmt,ap);
    Uart_SendString(string);
    va_end(ap);
}
/********************************************************************
// Function name	: Led_Display
// Description	    : 显示LED灯
// Return type		: void
// Argument         : int data (1 - on, 0 - off)
//                        3    2    1    0
//                     LED4 LED3 LED2 LED1
*********************************************************************/
unsigned char output_0x10000000 = 0xff;
void Led_Display(int data)
{	
	output_0x10000000 &= (~0xf0);
	output_0x10000000 |= (((~data)<< 4) & 0xf0);
	*((unsigned char *)0x10000000) = output_0x10000000;
}
unsigned char seg7table[16] = 
{
    /* 0       1       2       3       4       5       6      7*/
    0xc0,   0xf9,   0xa4,   0xb0,   0x99,   0x92,   0x82,   0xf8,

    /* 8       9      A        B       C       D       E      F*/
    0x80,   0x90,   0x88,   0x83,   0xc6,   0xa1,   0x86,   0x8e,
};

/********************************************************************
// Function name	: Seg7_Display
// Description	    : 数码管显示程序
// Return type		: void
// Argument         : unsigned char mask : 数码管显示掩码 bit0 - bit5 : SEG0 - SEG5
// Argument         : unsigned char * pdata : 数码管对应数据 bit0 - bit5 : SEG0 - SEG5
*********************************************************************/
void Seg7_Display(unsigned char mask, unsigned char * pdata)
{
	int i = 0;
	
	for(i = 0; i < 6; i++)
	{
		if(mask & (1 << i))
		{
			*((unsigned char *)0x10000006) = ~(1 << i) & 0x3f;
			*((unsigned char *)0x10000004) = seg7table[(pdata[i]) & 0xf]; 
			Delay(40);
		}
	}
}

/********************************************************************
// Function name	: Adc_Get_Data
// Description	    : AD采样
// Return type		: int:返回的采样值
// Argument         : int ch:通道0-7
// Argument         : int freq:采样频率
*********************************************************************/
int Adc_Get_Data(int ch, int freq)
{
#define LOOP 10000

    int i;
	volatile U32 preScaler;
    static int prevCh=-1;
    
    preScaler = PCLK/freq -1;               //PCLK:50.7MHz
    
    rADCCON = (1<<14)|(preScaler<<6)|(ch<<3);	//setup channel

    if(prevCh!=ch)
    {
		rADCCON = (1<<14)|(preScaler<<6)|(ch<<3);   //setup channel
		for(i=0;i<LOOP;i++);	//delay to set up the next channel
		prevCh=ch;
    }
    rADCCON|=0x1;   //start ADC

    while(rADCCON & 0x1);	//check if Enable_start is low
    while(!(rADCCON & 0x8000));	//check if EC(End of Conversion) flag is high

    return ( (int)rADCDAT0 & 0x3ff );
}

//========================*[ Timer ]==============================**
void Timer_Start(int divider)  //0:16us,1:32us 2:64us 3:128us
{
    rWTCON = ((PCLK/1000000-1)<<8)|(divider<<3);  //Watch-dog timer control register
    rWTDAT = 0xffff;  //Watch-dog timer data register
    rWTCNT = 0xffff;  //Watch-dog count register

      //Watch-dog timer enable & interrupt  disable
//    rWTCON = rWTCON |(1<<5) & !(1<<2);  //?
    rWTCON = rWTCON | (1<<5) | ~(1<<2);  //May 06, 2002 SOP
}

//=================================================================
int Timer_Stop(void)
{
    rWTCON = ((PCLK/1000000-1)<<8);
    return (0xffff - rWTCNT);
}
/********************************************************************
// Function name	: ChangeMPllValue
// Description	    : 设置MPLL值
// Return type		: void
// Argument         : int mdiv
// Argument         : int pdiv
// Argument         : int sdiv
*********************************************************************/
void ChangeMPllValue(int mdiv,int pdiv,int sdiv)
{
    rMPLLCON = (mdiv<<12) | (pdiv<<4) | sdiv;
}
/********************************************************************
// Function name	: ChangeClockDivider
// Description	    : 配置HCLK和PCLK
// Return type		: void
// Argument         : int hdivn
// Argument         : int pdivn
*********************************************************************/
void ChangeClockDivider(int hdivn,int pdivn)
{
     // hdivn,pdivn FCLK:HCLK:PCLK
     //     0,0         1:1:1 
     //     0,1         1:1:2 
     //     1,0         1:2:2
     //     1,1         1:2:4
    rCLKDIVN = (hdivn<<1) | pdivn;    
    
    if(hdivn)
        MMU_SetAsyncBusMode();
    else 
        MMU_SetFastBusMode();
}
/********************************************************************
// Function name	: ChangeUPllValue
// Description	    : 设置UPLL值
// Return type		: void
// Argument         : int mdiv
// Argument         : int pdiv
// Argument         : int sdiv
*********************************************************************/
void ChangeUPllValue(int mdiv,int pdiv,int sdiv)
{
    rUPLLCON = (mdiv<<12) | (pdiv<<4) | sdiv;
}

unsigned short ntohs(unsigned short s)
{
	return (s >> 8) | (s << 8);
}

unsigned long ntohl(unsigned long l)
{
	return	((l >> 24) & 0x000000ff) |
		((l >>	8) & 0x0000ff00) |
		((l <<	8) & 0x00ff0000) |
		((l << 24) & 0xff000000);
}

unsigned short htons(unsigned short s)
{
	return (s >> 8) | (s << 8);
}

unsigned long htonl(unsigned long l)
{
	return	((l >> 24) & 0x000000ff) |
		((l >>	8) & 0x0000ff00) |
		((l <<	8) & 0x00ff0000) |
		((l << 24) & 0xff000000);
}

