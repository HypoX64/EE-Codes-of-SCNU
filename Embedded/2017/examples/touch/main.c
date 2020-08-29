/* 包含文件 */
#include "def.h"
#include "2410lib.h"
#include "option.h"
#include "2410addr.h"
#include "interrupt.h"

#include <string.h>
#include "2410addr.h"
#include "2410lib.h"
#include "Ts_sep.h"
#include "def.h"

#define LOOP 1
#define ADCPRS 39

#define TS_JUSTIFY_LEFTTOP  1
#define TS_JUSTIFY_RIGHTBOT 2
#define TS_START            3

int ts_status = TS_JUSTIFY_LEFTTOP;
int ts_lefttop_x, ts_lefttop_y, ts_rightbot_x, ts_rightbot_y;
int ts_lcd_x, ts_lcd_y;

void Adc_or_TsSep() __attribute__ ((interrupt("IRQ")));
void Adc_or_TsSep(void)
{
    int i;
    U32 Ptx[6], Pty[6];
    
    rINTSUBMSK |= (BIT_SUB_ADC|BIT_SUB_TC); // Mask sub interrupt (ADC and TC) 

      // TC(Touch screen Control) Interrupt 
    if(rADCTSC & 0x100)
    {
        PRINTF("\nStylus Up!!\n");
        rADCTSC &= 0xff;    // Set stylus down interrupt
    }
    else 
    {
        PRINTF("\nStylus Down!!\n");
           
          // <X-Position Read>
        rADCTSC=(0<<8)|(0<<7)|(1<<6)|(1<<5)|(0<<4)|(1<<3)|(0<<2)|(1);
          // Down,Hi-Z,AIN5,GND,Ext vlt,Pullup Dis,Normal,X-position
        for(i=0;i<LOOP;i++);            //delay to set up the next channel
        for(i=0;i<5;i++)
        {
            rADCCON|=0x1;               // Start X-position conversion
            while(rADCCON & 0x1);       // Check if Enable_start is low
            while(!(0x8000&rADCCON));   // Check ECFLG
            Ptx[i]=(0x3ff&rADCDAT0);
        }
        Ptx[5]=(Ptx[0]+Ptx[1]+Ptx[2]+Ptx[3]+Ptx[4])/5;

          // <Y-Position Read>
        rADCTSC=(0<<8)|(0<<7)|(1<<6)|(1<<5)|(0<<4)|(1<<3)|(0<<2)|(2);
          // Down,GND,Ext vlt,Hi-Z,AIN7,Pullup Dis,Normal,Y-position
        for(i=0;i<LOOP;i++);            //delay to set up the next channel
        for(i=0;i<5;i++)
        {
            rADCCON|=0x1;               // Start X-position conversion
            while(rADCCON & 0x1);       // Check if Enable_start is low
            while(!(0x8000&rADCCON));   // Check ECFLG
            Pty[i]=(0x3ff&rADCDAT1);
        }
        Pty[5]=(Pty[0]+Pty[1]+Pty[2]+Pty[3]+Pty[4])/5;
        rADCTSC=(1<<8)|(1<<7)|(1<<6)|(0<<5)|(1<<4)|(0<<3)|(0<<2)|(3);
          // Up,GND,AIN,Hi-z,AIN,Pullup En,Normal,Waiting mode

        PRINTF("TOUCH Position = (%04d, %04d)        ", Ptx[5], Pty[5]);
		if(ts_status == TS_JUSTIFY_LEFTTOP)
        {
        	ts_lefttop_x = Ptx[5];
        	ts_lefttop_y = Pty[5];
        	ts_status = TS_JUSTIFY_RIGHTBOT;
        	PRINTF("\nLeft top (0, 0) -> (%04d, %04d)\n", ts_lefttop_x, ts_lefttop_y);
    		PRINTF("    请触摸屏幕右下角位置\n");
        }else if(ts_status == TS_JUSTIFY_RIGHTBOT)
        {
        	ts_rightbot_x = Ptx[5];
        	ts_rightbot_y = Pty[5];
        	ts_status = TS_START;
        	PRINTF("\nRight bottom (319, 239) -> (%04d, %04d)\n", ts_rightbot_x, ts_rightbot_y);
     		PRINTF("[2] 请点击触摸屏\n");
       }else
        {
        	ts_lcd_x = 320 - (Ptx[5] - ts_rightbot_x) * 1.0 / (ts_lefttop_x - ts_rightbot_x) * 320.0 ;
        	ts_lcd_y = (Pty[5] - ts_lefttop_y) * 1.0 / (ts_rightbot_y - ts_lefttop_y) * 240.0 ;
        	if(ts_lcd_x > 319) ts_lcd_x = 319;
        	if(ts_lcd_x < 0) ts_lcd_x = 0;
        	if(ts_lcd_y > 239) ts_lcd_x = 239;
        	if(ts_lcd_y < 0) ts_lcd_x = 0;
        	PRINTF("LCD Position = (%04d, %04d)\n", ts_lcd_x, ts_lcd_y);
        }
    }

    rSUBSRCPND |= BIT_SUB_TC;
    rINTSUBMSK =~ (BIT_SUB_TC);         // Unmask sub interrupt (TC)     
    ClearPending(BIT_ADC);
}
            

void Ts_Sep(void)
{
    PRINTF("------触摸屏测试------\n");
    PRINTF("[1] 触摸屏校准\n    请触摸屏幕左上角位置\n");

	ts_status = TS_JUSTIFY_LEFTTOP;
    rADCDLY = (50000);  // ADC Start or Interval Delay

    rADCCON = (1<<14)|(ADCPRS<<6)|(0<<3)|(0<<2)|(0<<1)|(0);
      // Enable Prescaler,Prescaler,AIN7/5 fix,Normal,Disable read start,No operation
    rADCTSC = (0<<8)|(1<<7)|(1<<6)|(0<<5)|(1<<4)|(0<<3)|(0<<2)|(3);
      // Down,YM:GND,YP:AIN5,XM:Hi-z,XP:AIN7,XP pullup En,Normal,Waiting for interrupt mode

    pISR_ADC   = (unsigned)Adc_or_TsSep;
    rINTMSK    &=~(BIT_ADC);
    rINTSUBMSK =~(BIT_SUB_TC);
   
    while(1);

    rINTSUBMSK |= BIT_SUB_TC;
    rINTMSK    |= BIT_ADC;
    PRINTF("----触摸屏测试结束----\n");
}

/********************************************************************
// Function name	: Main
// Description	    : JXARM9-2410 触摸屏实验主程序
// Return type		: void
// Argument         : void
*********************************************************************/
void Main(void)
{
	/* 配置系统时钟 */
    ChangeClockDivider(1,1);          // 1:2:4    
    ChangeMPllValue(0xa1,0x3,0x1);    // FCLK=202.8MHz  
    
    /* 初始化端口 */
    Port_Init();
    
    /* 初始化串口 */
    Uart_Init(0,115200);
    Uart_Select(0);
    
    /* 打印提示信息 */
	PRINTF("\n---触摸屏测试程序---\n");
	PRINTF("\n请将UART0与PC串口进行连接，然后启动超级终端程序(115200, 8, N, 1)\n");
	
    /* 开始回环测试 */
    Ts_Sep();
	while(1)
	{
	}
}

