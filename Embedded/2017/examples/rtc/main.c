/* 包含文件 */
#include "def.h"
#include "2410lib.h"
#include "option.h"
#include "2410addr.h"
#include "interrupt.h"

/* 表示日期、时间的数据结构 */
typedef struct ST_DATE
{
	short 	year;       // 年
	char	mon;        // 月
	char	day;        // 日
	char	week_day;   // 星期
	char	hour;       // 时
	char	min;        // 分
	char	sec;        // 秒
} st_date;

/* 全局变量 */
int led_index = 0;
int ext0_count = 0;

/* functions */
void rtc_tick_isr(void) __attribute__ ((interrupt("IRQ")));;
void rtc_int_isr(void) __attribute__ ((interrupt("IRQ")));;

/*****************************************************************************
// Function name	: rtc_set_date
// Description	    : 修改实时时钟当前时间、日期
// Return type		: void
// Argument         : p_date, 待设置的日期
*****************************************************************************/
void rtc_set_date(st_date* p_date)
{
    rRTCCON  = 0x01;	
    rBCDYEAR = p_date->year;
    rBCDMON  = p_date->mon;
    rBCDDAY  = p_date->day;
    rBCDDATE = p_date->week_day;
    rBCDHOUR = p_date->hour;
    rBCDMIN  = p_date->min;
    rBCDSEC  = p_date->sec;
    rRTCCON  = 0x00;	
}

/*****************************************************************************
// Function name	: rtc_get_date
// Description	    : 获取实时时钟当前时间、日期
// Return type		: void
// Argument         : p_date, 返回日期的指针
*****************************************************************************/
void rtc_get_date(st_date* p_date)
{
    rRTCCON  = 0x01;	
    
    p_date->year	= 	rBCDYEAR ;
    p_date->mon		= 	rBCDMON  ;
    p_date->day		= 	rBCDDAY  ;
    p_date->week_day= 	rBCDDATE ;
    p_date->hour	= 	rBCDHOUR ;
    p_date->min		= 	rBCDMIN  ;
    p_date->sec		= 	rBCDSEC  ;
    
    rRTCCON  = 0x00;	
}

/*****************************************************************************
// Function name	: rtc_tick_init
// Description	    : 初始化S3C2410的TICK定时器
// Return type		: void
// Argument         : tick, 设置的TICK频率(时钟滴答的周期为 (1+tick)/128秒)
*****************************************************************************/
void rtc_tick_init( char tick )
{
    Irq_Request(IRQ_TICK, rtc_tick_isr);
    
    rRTCCON   = 0x0;            //No reset[3], Merge BCD counters[2], BCD clock select XTAL[1], RTC Control disable[0]
    rTICNT  = (tick&0x7f)|0x80;		/*TICK 中断使能,周期为(1+tick)/128秒*/   

    Irq_Enable(IRQ_TICK);   
}

/*****************************************************************************
// Function name	: rtc_alarm_set
// Description	    : 设置S3C2410的告警时间以及方式
// Return type		: void
// Argument         : p_date, 告警的时间
//                    mode, 告警模式
*****************************************************************************/
void rtc_alarm_set(st_date* p_date, unsigned char mode)
{
    Irq_Request(IRQ_RTC, rtc_int_isr);
    
    rRTCCON  = 0x01;	
    
    rALMYEAR = p_date->year;
    rALMMON  = p_date->mon;
    rALMDATE = p_date->day;
    rALMHOUR = p_date->hour;
    rALMMIN  = p_date->min;
    rALMSEC  = p_date->sec;
    
    rRTCALM  = mode;
    
    rRTCCON  = 0x00;	

    Irq_Enable(IRQ_RTC);   
}

/*****************************************************************************
// Function name	: Main
// Description	    : JXARM9-2410 实时时钟实验主程序
//                    完成功能:
//                        时钟滴答:每秒钟刷新数码管显示
//                        设置当前日期、时间
//                        动态刷新当前日期、时间，通过串口打印出来
//                        时间告警功能:每分钟的第5秒告警，并进行跑马灯显示
// Return type		: void
// Argument         : void
*****************************************************************************/
void Main(void)
{
	int old_index ;
	
	st_date m_date;
	
	/* 配置系统时钟 */
    ChangeClockDivider(1,1);          // 1:2:4    
    ChangeMPllValue(0xa1,0x3,0x1);    // FCLK=202.8MHz  
	
	/* 中断初始化 */
    Isr_Init();
    /* 初始化端口 */
    Port_Init();
    
    /* 初始化串口 */
    Uart_Init(0,115200);
    Uart_Select(0);

    /* 打印提示信息 */
	PRINTF("\n---实时时钟测试程序---\n");
	PRINTF("\n请将UART0与PC串口进行连接，然后启动超级终端程序(115200, 8, N, 1)\n");
	PRINTF("\n实时时钟测试开始\n");

	/* 采用BCD编码，如2004年需要设置的值为0x2004 */
    m_date.year		= 	0x2000+0x04 ;
    m_date.mon		= 	0x03 ;
    m_date.day		= 	0x02 ;
    m_date.week_day	= 	0x02 ;
    m_date.hour		= 	0x15 ;
    m_date.min		= 	0x40 ;
    m_date.sec		= 	0x00 ;
    
    /* 修改当前日期和时间 */
    rtc_set_date(&m_date);
    
    m_date.sec		= 	0x05 ;
    
    /* 设置告警的时间及方式，0x41表示使能RTC告警，以及使能秒时钟告警 */
    rtc_alarm_set(&m_date, 0x41);
	
	rtc_tick_init(127);
	
	old_index = led_index;
   	PRINTF("\r\n\r\n");
   	
    while(1)
    {
    	if(old_index != led_index)		/* 每隔一秒更新一次数据				*/
    	{
   	    	rtc_get_date(&m_date);
   	    	old_index = led_index;
			
   	    	PRINTF(				/* 时钟数据为BCD码格式,以16进制显示 */
				"\b\b\b\b\b\b\b\b%02x:%02x:%02x", m_date.hour, m_date.min, m_date.sec);
   	    }
    };
}

/*****************************************************************************
// Function name	: rtc_tick_isr
// Description	    : TICK中断处理程序，程序中设置每秒钟引发一次中断
// Return type		: int
// Argument         : void
*****************************************************************************/
void rtc_tick_isr(void)
{
	Irq_Clear(IRQ_TICK);         /* 清除TICK中断 */

//	*((unsigned char*) 0x02000006) = 0x00;	
//  	*(unsigned char*)0x02000004 = seg7table[led_index%10];  
   	
   	led_index++;
}

/*****************************************************************************
// Function name	: rtc_int_isr
// Description	    : rtc中断处理程序，程序中设置每分钟的第5秒引发该中断
// Return type		: int
// Argument         : void
*****************************************************************************/
void rtc_int_isr(void)
{
	Irq_Clear(IRQ_RTC);          /*清除RTC中断						*/
    
//    if(ext0_count&1)	
//   		*(unsigned char*)0x2000000 = 0x0f;  
//   	else
//   		*(unsigned char*)0x2000000 = 0xff;  
   		
   	ext0_count++;
   	
   	PRINTF("\r\nAlarm\r\n                  ");
}
