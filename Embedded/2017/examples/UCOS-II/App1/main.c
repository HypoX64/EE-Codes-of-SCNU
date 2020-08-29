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
OS_STK StackLCD[LCD_STACKSIZE]= {0, };

/* task name string */
char IdLED = '1';
char IdSEG = '2';
char IdLCD = '3';

/* task entry function */
void TaskLED(void *Id);
void TaskSEG(void *Id);
void LCD_Task_Main(void *Id);

/*
 * LED blink function. 
 *     this function blink the led
 */
void User_LED_Blink(void)
{
	static int led_status = 0;
	
	led_status += 1;
	if(led_status % 2 == 0)
		Led_Display(0x0f);
	else
		Led_Display(0x00);			
}

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
 *     this task blink the led every 200 ticks
 *     that is 2s.
 */
void TaskLED(void *Id)
{
    for (;;)
    {
//		OSSchedLock();

        User_LED_Blink();

//        OSSchedUnlock();
        
        OSTimeDly(100);       
    }
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
//		OSSchedLock();

        User_SEG_Blink();

//        OSSchedUnlock();

        OSTimeDly(100);
    }
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
	OSTaskCreate(TaskLED, (void *)&IdLED, (OS_STK *)&StackLED[STACKSIZE - 1], 15);
	/* Create seg blink tasks */
	OSTaskCreate(TaskSEG, (void *)&IdSEG, (OS_STK *)&StackSEG[STACKSIZE - 1], 13);
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

/*
  *******************************************************************
  *
  *              LCD_Task_Main()
  *
  *******************************************************************
*/
void LCD_Task_Main(void *Id) 
{
  	int Cnt =0;
  	int i,YPos;
  	int LCDXSize = LCD_GET_XSIZE();
  	int LCDYSize = LCD_GET_YSIZE();
  	GUI_BITMAP *pBitmap;
  	
  	GUI_Init();
	ARMTargetStart();
  	   
    uHALr_printf("LCD_Task_Main Start...\n");
  	while(1)
  	{
    	uHALr_printf("Set RED Screen...\n");
	  	GUI_SetBkColor(GUI_RED); 
	  	GUI_Clear();
	  	GUI_Delay(100);
    	uHALr_printf("Set BLUE Screen...\n");
	  	GUI_SetBkColor(GUI_BLUE); 
	  	GUI_Clear();
	  	GUI_Delay(100);
    	uHALr_printf("Draw Line...\n");
	  	GUI_SetColor(GUI_WHITE);
	  	for (i=0; i<1000; i+=10) 
	  	{
	    	GUI_DrawHLine(i,0,100);
	    	GUI_DispStringAt("Line ",0,i);
	    	GUI_DispDecMin(i);
	  	}
	  	GUI_Delay(200);
	  	GUI_SetColor(0x0);
	  	GUI_SetBkColor(0xffffff);
	  	for (i=0; i<160; i++) 
	  	{
	    	int len = (i<80) ? i : 160-i;
	    	GUI_DrawHLine(i,20,len+20);
	  	}
	  	GUI_Delay(200);
	  	GUI_Clear();
	  	if (LCD_GET_YSIZE()>(100+bmMicriumLogo_1bpp.YSize)) 
	  	{
	    	pBitmap=&bmMicriumLogo;
	  	}else 
	  	{
	    	GUI_SetColor(GUI_BLUE);
	    	pBitmap=&bmMicriumLogo_1bpp;
	  	}
    	uHALr_printf("Draw Bitmap...\n");
	  	GUI_DrawBitmap(pBitmap,(LCDXSize-pBitmap->XSize)/2,10);
	  	YPos=20+pBitmap->YSize;
	  	GUI_SetFont(&GUI_FontComic24B_1);
	  	GUI_DispStringHCenterAt("www.micrium.com",LCDXSize/2,YPos);
	  	GUI_Delay(200);
	  	GUI_SetColor(GUI_RED);
	  	GUI_DispStringHCenterAt("© 2002\n", LCDXSize/2,YPos+30);
	  	GUI_SetFont(&GUI_Font10S_1);
	  	GUI_DispStringHCenterAt("Micriµm Inc.",LCDXSize/2,YPos+60);;
	  	GUI_Delay(200);
	}
}
