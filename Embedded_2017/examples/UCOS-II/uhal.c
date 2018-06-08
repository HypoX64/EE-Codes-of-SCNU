/*
 * File:        uhal.c
 *
 * uC/OS Real-time multitasking kernel port for the ARM processor.
 *
 * hard related layerof eb44b0 board.
 *
 * Created by cooljet (www.cvtech.com.cn)
 *
 */
#include <stdarg.h>
#include <string.h>
#include "uhal.h"
#include "2410lib.h"
#include "interrupt.h"
#include "2410addr.h"
#include "os_cpu.h"

/* timer interrupt handler routine */
extern void OSTickISR(void);

/* for interrupt enable or disable */
extern void ARMDisableInt(void);
extern void ARMEnableInt(void);

void (*pre_isr)(void);
void *(*post_isr)(void);

/* ´òÓ¡»º³åÇø */
char print_buf[PRINT_BUF_MAX];

void uHALir_DefineIRQ(void *is, void *iq, void *n)
{
	pre_isr= (void (*)(void))is;
	post_isr= (void *(*)(void))iq;
}

void uHALr_InitTimers(void)
{
    Irq_Request(IRQ_TIMER1, OSTickISR);

    rTCFG0 = rTCFG0 & ~(0xffffff) | 0x000f0f;         //Dead zone=0,Prescaler1=15(0x0f),Prescaler0=15(0x0f)
    rTCFG1 = rTCFG1 & ~(0xffffff) | 0x001233;         //All interrupt,Mux4=1/2,Mux3=1/4,Mux2=1/8,Mux1=1/16,Mux0=1/16

    //Timer input clock frequency = PCLK/(prescaler value+1)/(divider value)
    rTCNTB1 = 0x7aa;           //(1/(50MHz/16/16)) * 0x7aa (1962) = 0.01s ( Hz)
    
    rTCON  = rTCON & ~(0xffffff) | 0xa00;         //Auto reload, Inverter off, Manual update, Dead zone disable, Stop  
    
    rTCON  = rTCON & ~(0xffffff) | 0x900;         //Auto reload(T0=One-shot),Inverter off,No operation,Dead zone disable,Start
}

void uHALr_InstallSystemTimer(void)
{
    Irq_Enable(IRQ_TIMER1);
}




