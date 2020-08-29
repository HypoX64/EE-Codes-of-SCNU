#if !defined __UHAL_H
#define __UHAL_H

/* ARM board targetting source file.
   file name: uhal.h   
   date: 2001. 9. 1
   made by cho dong-seok
   homepage: www.pusanssm.com/~cthr36/
*/

//Define board cooperation
#define SAMSUNG
//#define NONE

//Indicate debug mode.
//#define DEBUG


//Define version of uC/OS Hardware Associated Layer code.
#define uHAL_VERSION_STRING	"Version 1.00  COiNS"


//Output through LCD or serial port to print information.
#define uHALr_printf Uart_SendString
#define PRINT_BUF_MAX   2048
extern char print_buf[PRINT_BUF_MAX];


/*** Called by ARMTargetInit() ***/
//Reset memory management unit.
void uHALr_ResetMMU(void);

//Define pre & post-process routines for Interrupt.
void uHALir_DefineIRQ(void *is, void *iq, void *n);

//Initialze interrupts.
void uHALr_InitInterrupts(void);


//Initialize timer that is used OS.
void uHALr_InitTimers(void);


/*** Called by ARMTargetStart() ***/
//Request the system timer.
//return value 1:success   0:fail
int uHALr_RequestSystemTimer(void *tick, const unsigned char *str);


//Start system timer & enable the interrupt.
void uHALr_InstallSystemTimer(void);


#endif

