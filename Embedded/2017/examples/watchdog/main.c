/* �����ļ� */
#include "def.h"
#include "2410lib.h"
#include "option.h"
#include "2410addr.h"
#include "interrupt.h"

extern unsigned char seg7table[];

/* ��ʾ���ڡ�ʱ������ݽṹ */
typedef struct ST_DATE
{
	short 	year;       // ��
	char	mon;        // ��
	char	day;        // ��
	char	week_day;   // ����
	char	hour;       // ʱ
	char	min;        // ��
	char	sec;        // ��
} st_date;

/* ȫ�ֱ��� */
int led_index = 0;
int ext0_count = 0;

/* functions */
void rtc_tick_isr(void) __attribute__ ((interrupt("IRQ")));;
void rtc_int_isr(void) __attribute__ ((interrupt("IRQ")));;

#define WDT_ENABLE			(0x01<<5)
#define WDT_INT_ENABLE		(0x01<<2)
#define WDT_RST_ENABLE		(0x01<<0)	

#define WDT_CLK_SEL			(0X3    <<3)		/* 1/128 */
#define WDT_PRE_SCALER		((PCLK/1000000-1)   <<8)		/* 49    */

/********************************************************************
// Function name	: watchdog_init
// Description	    : ���Ź���ʼ��
// Return type		: void
// Argument         : 
*********************************************************************/
void watchdog_init()
{
	rWTCNT = 8448 * 2;		/* ���ÿ��Ź���ʼֵ */
	rWTCON = WDT_ENABLE | WDT_RST_ENABLE | WDT_CLK_SEL | WDT_PRE_SCALER;	/* �򿪿��Ź� */		/* �򿪿��Ź� */
}
/*****************************************************************************
// Function name	: rtc_set_date
// Description	    : �޸�ʵʱʱ�ӵ�ǰʱ�䡢����
// Return type		: void
// Argument         : p_date, �����õ�����
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
// Description	    : ��ȡʵʱʱ�ӵ�ǰʱ�䡢����
// Return type		: void
// Argument         : p_date, �������ڵ�ָ��
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
// Description	    : ��ʼ��S3C2410��TICK��ʱ��
// Return type		: void
// Argument         : tick, ���õ�TICKƵ��(ʱ�ӵδ������Ϊ (1+tick)/128��)
*****************************************************************************/
void rtc_tick_init( char tick )
{
    Irq_Request(IRQ_TICK, rtc_tick_isr);
    
    rRTCCON   = 0x0;            //No reset[3], Merge BCD counters[2], BCD clock select XTAL[1], RTC Control disable[0]
    rTICNT  = (tick&0x7f)|0x80;		/*TICK �ж�ʹ��,����Ϊ(1+tick)/128��*/   

    Irq_Enable(IRQ_TICK);   
}

/*****************************************************************************
// Function name	: rtc_alarm_set
// Description	    : ����S3C2410�ĸ澯ʱ���Լ���ʽ
// Return type		: void
// Argument         : p_date, �澯��ʱ��
//                    mode, �澯ģʽ
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
// Description	    : JXARM9-2410 ���Ź�ʵ��������
//                    ��ɹ���:
//                        ��ʵʱʱ��ʵ��Ļ�������ӿ��Ź����ܣ�����ʱ�ӵδ�
//                        �ж���ʵ��ι������.
//       
// Return type		: void
// Argument         : void
*****************************************************************************/
void Main(void)
{
	int old_index ;
	
	st_date m_date;
	
	/* ����ϵͳʱ�� */
    ChangeClockDivider(1,1);          // 1:2:4    
    ChangeMPllValue(0xa1,0x3,0x1);    // FCLK=202.8MHz  
	
	/* �жϳ�ʼ�� */
    Isr_Init();
    /* ��ʼ���˿� */
    Port_Init();
    
    /* ��ʼ������ */
    Uart_Init(0,115200);
    Uart_Select(0);

    /* ��ӡ��ʾ��Ϣ */
	PRINTF("\n---���Ź����Գ���---\n");
	PRINTF("\n�뽫UART0��PC���ڽ������ӣ�Ȼ�����������ն˳���(115200, 8, N, 1)\n");
	PRINTF("\n���Ź����Կ�ʼ\n");

	/* ����BCD���룬��2004����Ҫ���õ�ֵΪ0x2004 */
    m_date.year		= 	0x2000+0x04 ;
    m_date.mon		= 	0x03 ;
    m_date.day		= 	0x02 ;
    m_date.week_day	= 	0x02 ;
    m_date.hour		= 	0x15 ;
    m_date.min		= 	0x40 ;
    m_date.sec		= 	0x00 ;
    
    /* �޸ĵ�ǰ���ں�ʱ�� */
    rtc_set_date(&m_date);
    
    m_date.sec		= 	0x05 ;
    
    /* ���ø澯��ʱ�估��ʽ��0x41��ʾʹ��RTC�澯���Լ�ʹ����ʱ�Ӹ澯 */
    rtc_alarm_set(&m_date, 0x41);
	
	rtc_tick_init(127);
	
	/* �򿪿��Ź���λ���� */
	watchdog_init();
	
	old_index = led_index;
   	PRINTF("����2����ι��������ϵͳ����Լ2���λ\n\n");
   	
    while(1)
    {
    	if(old_index != led_index)		/* ÿ��һ�����һ������				*/
    	{
   	    	rtc_get_date(&m_date);
   	    	old_index = led_index;
			
   	    	PRINTF(				/* ʱ������ΪBCD���ʽ,��16������ʾ */
				"\b\b\b\b\b\b\b\b%02x:%02x:%02x", m_date.hour, m_date.min, m_date.sec);
   	    }
    };
}

/*****************************************************************************
// Function name	: rtc_tick_isr
// Description	    : TICK�жϴ�����򣬳���������ÿ��������һ���ж�
//                    Ϊ���⿴�Ź���λ�ڴ˴�ι��
// Return type		: int
// Argument         : void
*****************************************************************************/
void rtc_tick_isr(void)
{
	Irq_Clear(IRQ_TICK);         /* ���TICK�ж� */

	*((U8*) 0x10000006) = 0x00;
  	*(unsigned char*)0x10000004 = seg7table[led_index%10];  
   	
   	led_index++;
   	
   	/* ι�� */
   	rWTCNT = 8448 * 2;
}

/*****************************************************************************
// Function name	: rtc_int_isr
// Description	    : rtc�жϴ�����򣬳���������ÿ���ӵĵ�5���������ж�
// Return type		: int
// Argument         : void
*****************************************************************************/
void rtc_int_isr(void)
{
	Irq_Clear(IRQ_RTC);          /*���RTC�ж�						*/
    
//    if(ext0_count&1)	
//   		*(unsigned char*)0x2000000 = 0x0f;  
//   	else
//   		*(unsigned char*)0x2000000 = 0xff;  
   		
   	ext0_count++;
   	
   	PRINTF("\r\nAlarm\r\n                  ");
}
