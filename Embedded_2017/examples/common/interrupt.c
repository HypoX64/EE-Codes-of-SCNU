#include "def.h"
#include "option.h"
#include "2410addr.h"
#include "2410lib.h"
#include "2410slib.h" 
#include "interrupt.h"

#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void HaltUndef(void);
void HaltSwi(void);
void HaltPabort(void);
void HaltDabort(void);

/********************************************************************
// Function name	: Isr_Init
// Description	    : 中断初始化功能
// Return type		: void
// Argument         : void
*********************************************************************/
void Isr_Init(void)
{
    pISR_UNDEF  = (unsigned)HaltUndef;
    pISR_SWI    = (unsigned)HaltSwi;
    pISR_PABORT = (unsigned)HaltPabort;
    pISR_DABORT = (unsigned)HaltDabort;
    
    rINTMOD     = 0x0;                     //All=IRQ mode
    rINTMSK     = BIT_ALLMSK;              //All interrupt is masked.
    rINTSUBMSK  = BIT_SUB_ALLMSK;          //All sub-interrupt is masked. <- April 01, 2002 SOP
}
/********************************************************************
// Function name	: Isr_Request
// Description	    : 注册中断函数
// Return type		: void
// Argument         : int irq_no
//                    #define IRQ_EINT0     1
//                    #define IRQ_EINT1     2
//                    #define IRQ_EINT2     3
//                    #define IRQ_EINT3     4
//                    #define IRQ_EINT4_7   5
//                    #define IRQ_EINT8_23  6
//                    #define IRQ_NOTUSED6  7
//                    #define IRQ_BAT_FLT   8
//                    #define IRQ_TICK      9
//                    #define IRQ_WDT       10
//                    #define IRQ_TIMER0    11
//                    #define IRQ_TIMER1    12
//                    #define IRQ_TIMER2    13
//                    #define IRQ_TIMER3    14
//                    #define IRQ_TIMER4    15
//                    #define IRQ_UART2     16
//                    #define IRQ_LCD       17
//                    #define IRQ_DMA0      18
//                    #define IRQ_DMA1      19
//                    #define IRQ_DMA2      20
//                    #define IRQ_DMA3      21
//                    #define IRQ_SDI       22
//                    #define IRQ_SPI0      23
//                    #define IRQ_UART1     24
//                    #define IRQ_NOTUSED24 25
//                    #define IRQ_USBD      26
//                    #define IRQ_USBH      27
//                    #define IRQ_IIC       28
//                    #define IRQ_UART0     29
//                    #define IRQ_SPI1      30
//                    #define IRQ_RTC       31
//                    #define IRQ_ADC       32
// Argument         : void* irq_routine
*********************************************************************/
void Irq_Request(int irq_no, void* irq_routine)
{
	if(irq_no >= IRQ_MIN && irq_no <= IRQ_MAX)
		*(unsigned int*)((irq_no - 1) * sizeof(unsigned int) + (unsigned int)(_ISR_STARTADDRESS+0x20)) = (unsigned int)irq_routine;
}
/********************************************************************
// Function name	: Irq_Enable
// Description	    : 开中断
// Return type		: void
// Argument         : int irq_no
*********************************************************************/
void Irq_Enable(int irq_no)
{
	if(irq_no >= IRQ_MIN && irq_no <= IRQ_MAX)
		rINTMSK &= ~(1 << (irq_no - 1));
}
/********************************************************************
// Function name	: Irq_Disable
// Description	    : 关中断
// Return type		: void
// Argument         : int irq_no
*********************************************************************/
void Irq_Disable(int irq_no)
{
	if(irq_no >= IRQ_MIN && irq_no <= IRQ_MAX)
		rINTMSK |= (1 << (irq_no - 1));
}
/********************************************************************
// Function name	: Irq_Clear
// Description	    : 清除中断
// Return type		: void
// Argument         : int irq_no
*********************************************************************/
void Irq_Clear(int irq_no)
{
    rSRCPND = (1 << (irq_no - 1));					/*清除RTC中断						*/
    rINTPND = (1 << (irq_no - 1));
    rINTPND;
}
/********************************************************************
// Function name	: HaltUndef
// Description	    : undef异常处理
// Return type		: void
// Argument         : void
*********************************************************************/
void HaltUndef(void)
{
    Uart_Printf("Undefined instruction exception.\n");
    while(1);
}
/********************************************************************
// Function name	: HaltSwi
// Description	    : SWI异常处理
// Return type		: void
// Argument         : void
*********************************************************************/
void HaltSwi(void)
{
    Uart_Printf("SWI exception.\n");
    while(1);
}
/********************************************************************
// Function name	: HaltPabort
// Description	    : Pabort异常处理
// Return type		: void
// Argument         : void
*********************************************************************/
void HaltPabort(void)
{
    Uart_Printf("Pabort exception.\n");
    while(1);
}
/********************************************************************
// Function name	: HaltDabort
// Description	    : Dabort异常处理
// Return type		: void
// Argument         : void
*********************************************************************/
void HaltDabort(void)
{
    Uart_Printf("Dabort exception.\n");
    while(1);
}
