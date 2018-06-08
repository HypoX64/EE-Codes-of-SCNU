/*
*********************************************************************************************************
*                                                µC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2000, SEGGER Microcontroller Systeme GmbH          
*
*              µC/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed 
*              in any way. We appreciate your understanding and fairness.
*
* File        : Main.c
* Purpose     : Application program in windows simulator
*********************************************************************************************************
*/


#include "GUI.h"

extern const GUI_BITMAP bmMicriumLogo;
extern const GUI_BITMAP bmMicriumLogo_1bpp;


/*
 * File:        eg1.c
 *
 * uC/OS Real-time multitasking kernel for the ARM processor.
 *
 * Simple example of using multiple tasks to blink the led and seg int eb44b0 board.
 *
 * Created by cooljet (www.cvtech.com.cn)
 *
 */
#include	"Includes.h"               /* uC/OS interface */
#include    "option.h"
#include    "2410lib.h"
#include    "uhal.h"

/* task stack */
#define LCD_STACKSIZE     (20480)
OS_STK StackLED[STACKSIZE]= {0, };
OS_STK StackSEG[STACKSIZE]= {0, };
OS_STK StackTIMER[STACKSIZE]= {0, };
OS_STK StackLCD[LCD_STACKSIZE]= {0, };

/* task name string */
char IdSEG = '2';
char IdLCD = '3';
char IdTIMER = '4';

/* task entry function */
void TaskSEG(void *Id);
void TaskTimer(void *Id);
void LCD_Task_Main(void *Id);

/*
 * LED blink function. 
 *     this function blink the led
 */
void User_SEG_Blink(void)
{
	static unsigned char seg_value[] = { 0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e };		   
	static int seg_status = 0;
	
	*((unsigned char *)0x10000006) = 0x3e;
	*((unsigned char *)0x10000004) = seg_value[seg_status];
	seg_status += 1;
	if(seg_status > 15)
		seg_status = 0;
}

/*
 * Task entry function. 
 *     this task blink the seg every 200 ticks
 *     that is 1s.
 */
void TaskSEG(void *Id)
{
    for (;;)
    {       
        User_SEG_Blink();

        OSTimeDly(100);
    }
}
void TaskTimer(void *Id)
{
#if 0
	char info[20];
	st_date m_date;

    m_date.year		= 	0x2000+0x04 ;
    m_date.mon		= 	0x06 ;
    m_date.day		= 	0x15 ;
    m_date.week_day	= 	0x02 ;
    m_date.hour		= 	0x15 ;
    m_date.min		= 	0x40 ;
    m_date.sec		= 	0x00 ;    
    OSRtcTimeSet(&m_date);
	
	while(1)
	{
		OSRtcTimeGet(&m_date);
		sprintf(info, "%02x : %02x : %02x", m_date.hour, m_date.min, m_date.sec);
		GUI_SetBkColor(GUI_BLUE);
		GUI_SetColor(GUI_WHITE);
	    GUI_SetFont(&GUI_Font8_ASCII);
		GUI_DispStringAt(info, 242, 23 * 8);
		
		OSTimeDly(100);
	}
#endif
}
/*
 * Main function.
 */
void Main(void)
{
    /* 
     * do target (uHAL based ARM system) initialisation 
     */
	ARMTargetInit();
    
    uHALr_printf("#########Example 1#########\n");

    /* 
     * needed by uC/OS 
     */
	OSInit();

    /* 
     * create the tasks in uC/OS and assign increasing
     * priorities to them so that Task3 at the end of
     * the pipeline has the highest priority.
     */
	/* Create seg blink tasks */
	OSTaskCreate(TaskSEG, (void *)&IdSEG, (OS_STK *)&StackSEG[STACKSIZE - 1], 13);
	/* Create Time tasks */
//	OSTaskCreate(TaskTimer, (void *)&IdTIMER, (OS_STK *)&StackTIMER[STACKSIZE - 1], 14);
	/* Create LCD tasks */
	OSTaskCreate(LCD_Task_Main, (void *)&IdLCD, (OS_STK *)&StackLCD[LCD_STACKSIZE - 1], 12);
    /* 
     * start the task 
     */
    OSStart();
    

    /* 
     * never reached 
     */
	return;
}   

void LCD_Task_Main(void *Id)
{
	ARMTargetStart();
	
	GUI_Init();
	
	while(1)	
	{
  		Snake_Main();
  	}
}
