/*
*********************************************************************************************************
*                                                礐/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2000, SEGGER Microcontroller Systeme GmbH          
*
*              礐/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed 
*              in any way. We appreciate your understanding and fairness.
*
* File        : Main.c
* Purpose     : Application program in windows simulator
*********************************************************************************************************
*/


#include "GUI.h"
#include "..\UC-GUI\gui\WM\WM_Intern.h"

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
#define AD_STACKSIZE      (20480)
OS_STK StackLCD[LCD_STACKSIZE]= {0, };
OS_STK StackAD[AD_STACKSIZE]= {0, };

/* task name string */
char IdLCD = '3';
char IdAD = '3';

#define WM_USER_PAINT_ADC              201      /* Reserved for user messages */

WM_HWIN    hADCMain = 0;

/* task entry function */
void LCD_Task_Main(void *Id);

void Dialog_Main(void);

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
#ifdef MMU_ON  	
	MMU_Init();
#endif
  	GUI_Init();
	ARMTargetStart();

  	Dialog_Main();
}

#define ADC_MAX_VALUE			0x3ff
void ADC_Init(void)
{
}
#define ADC_FREQ 2500000
void ADC_Get(void)
{
	int ch0, ch1;
	
    ch0=Adc_Get_Data(0, ADC_FREQ);
    ch1=Adc_Get_Data(1, ADC_FREQ);

	// 重绘
	AD_Draw_Data(1, ch0);
	AD_Draw_Data(2, ch1);
}		

#define    CH1_BACK_COLOR  GUI_WHITE
#define    CH1_COLOR       GUI_RED

#define    CH2_BACK_COLOR  GUI_WHITE
#define    CH2_COLOR       GUI_GREEN

#define    CH1_TOP_X      100
#define    CH1_TOP_Y       30
#define    CH1_BOT_X      310
#define    CH1_BOT_Y      130
#define    CH2_TOP_X      100
#define    CH2_TOP_Y      135
#define    CH2_BOT_X      310
#define    CH2_BOT_Y      235

#define    AD_ACQUIRE_POINT   209 //(CH1_BOT_X - CH1_TOP_X - 1)

INT32U      ch1_acq_pt[AD_ACQUIRE_POINT] = {0, };
INT32U      ch2_acq_pt[AD_ACQUIRE_POINT] = {0, };

void AD_Draw_Data(INT8U ch, INT32U data)
{
	char   str[20];
	INT32U loopcnt;
	
	data &= 0x3ff;
	
	sprintf(str, "%03d", data);
	switch(ch)
	{
		case 1:
		GUI_SetBkColor(GUI_WHITE); 
		GUI_SetColor(CH1_COLOR); 
		GUI_DispStringAt(str, 20,CH1_TOP_Y + 50);
		GUI_SetBkColor(CH1_BACK_COLOR);
  		GUI_SetColor(CH1_BACK_COLOR);
		GUI_FillRect(CH1_TOP_X, CH1_TOP_Y, CH1_BOT_X, CH1_BOT_Y);
  		for(loopcnt = 0; loopcnt < AD_ACQUIRE_POINT - 1; loopcnt ++)
  			ch1_acq_pt[loopcnt] = ch1_acq_pt[loopcnt + 1];
  		ch1_acq_pt[AD_ACQUIRE_POINT - 1] = data*1.0*(CH1_BOT_Y - CH1_TOP_Y)/ADC_MAX_VALUE;
  		GUI_SetColor(CH1_COLOR);
  		for(loopcnt = CH1_TOP_X + 1; loopcnt < CH1_BOT_X; loopcnt ++)
  			GUI_DrawVLine(loopcnt, CH1_BOT_Y - ch1_acq_pt[loopcnt - CH1_TOP_X - 1], CH1_BOT_Y);
		break;
		case 2:
		GUI_SetBkColor(GUI_WHITE); 
		GUI_SetColor(CH2_COLOR); 
		GUI_DispStringAt(str, 20,CH2_TOP_Y + 50);
		GUI_SetBkColor(CH2_BACK_COLOR);
  		GUI_SetColor(CH2_BACK_COLOR);
		GUI_FillRect(CH2_TOP_X, CH2_TOP_Y, CH2_BOT_X, CH2_BOT_Y);
  		for(loopcnt = 0; loopcnt < AD_ACQUIRE_POINT - 1; loopcnt ++)
  			ch2_acq_pt[loopcnt] = ch2_acq_pt[loopcnt + 1];
  		ch2_acq_pt[AD_ACQUIRE_POINT - 1] = data*1.0*(CH2_BOT_Y - CH2_TOP_Y)/ADC_MAX_VALUE;
  		GUI_SetColor(CH2_COLOR);
  		for(loopcnt = CH2_TOP_X + 1; loopcnt < CH2_BOT_X; loopcnt ++)
  			GUI_DrawVLine(loopcnt, CH2_BOT_Y - ch2_acq_pt[loopcnt - CH2_TOP_X - 1], CH2_BOT_Y);
		break;
	}
}
/********************************************************************
// Function name	: Dialog_Main
// Description	    : 对话框主函数
// Return type		: void
// Argument         : void
*********************************************************************/
void Dialog_Main(void) 
{
	int loopcnt = 0;
	
	GUI_SetBkColor(GUI_BLUE); 
	GUI_Clear();
  	GUI_SetColor(GUI_WHITE);
  	GUI_SetFont(&GUI_FontComic24B_1);
	GUI_DispStringAt("Two-channel A/D data acquire system", 0,5);
  	GUI_SetFont(&GUI_FontComic18B_1);
	GUI_DispStringAt("Channel One", 0,CH1_TOP_Y);
	GUI_DispStringAt("Channel Two", 0,CH2_TOP_Y);

	// 画边框
	GUI_SetBkColor(CH1_BACK_COLOR);
	GUI_FillRect(CH1_TOP_X, CH1_TOP_Y, CH1_BOT_X, CH1_BOT_Y);
	GUI_SetBkColor(CH2_BACK_COLOR);
	GUI_FillRect(CH2_TOP_X, CH2_TOP_Y, CH2_BOT_X, CH2_BOT_Y);
	
	// 初始化
	for(loopcnt = 0; loopcnt <= AD_ACQUIRE_POINT - 1; loopcnt ++)
	{
		ch1_acq_pt[loopcnt] = 0;
		ch2_acq_pt[loopcnt] = 0;
	}

	while(1)
	{
		ADC_Get();
		OSTimeDly(20);
	}
}

