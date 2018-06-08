/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                          (c) Copyright 1992-2001, Jean J. Labrosse, Weston, FL
*                                           All Rights Reserved
*
* File : DRV_STEPPER.C
* By   : cooljet
*********************************************************************************************************
*/

#include	"Includes.h"               /* uC/OS interface */
#include    "option.h"
#include    "2410lib.h"
#include    "uhal.h"

INT8U     step_speed        =    1; 
INT8U     step_cur_count    =    1;
INT8U     step_enable       = STEP_MOTOR_DISABLE;  
INT8U     step_dire         = STEP_MOTOR_CLOCKWISE;

// ����ģʽ��ת����
unsigned char pluse_table[] = 
{
	0x05, 0x09, 0x0a, 0x06,
};

/********************************************************************
// Function name	: DRVStepperControl
// Description	    : 
// Return type		: void
// Argument         : int benable
//     STEP_MOTOR_ENABLE   -- stepper enable
//     STEP_MOTOR_DISABLE  -- stepper disable
*********************************************************************/
void DRVStepperControl(INT8U benable) 
{   
	step_enable = benable;
	if(benable == STEP_MOTOR_ENABLE) 
	{                                
		step_cur_count = 1;
	}                                
	else                             
	{             
	}           
}
/********************************************************************
// Function name	: stepper_set_direct
// Description	    : 
// Return type		: void
// Argument         : INT8U direct
//     STEP_MOTOR_CLOCKWISE      -- clockwise direction
//     STEP_MOTOR_ANTICLOCKWISE  -- anticlockwise direction
*********************************************************************/
void DRVStepperSetDirect(INT8U direct)
{
	step_dire = direct;
}
/********************************************************************
// Function name	: DRVStepperSetSpeed
// Description	    : ���ò������ת�٣���λΪÿ��speedx10ms��1<=s<=100��ֵԽС�ٶ�Խ��
// Return type		: void
// Argument         : INT8U speed
*********************************************************************/
void DRVStepperSetSpeed(INT8U speed)
{
	if(speed >= STEP_SPEED_MAX && speed <= STEP_SPEED_MIN)
		step_speed = speed;	 
}
/********************************************************************
// Function name	: DRVStepperSpeedUp
// Description	    : ����
// Return type		: void
// Argument         : void
*********************************************************************/
void DRVStepperSpeedUp(void)
{
	if(step_speed > STEP_SPEED_MAX)
		step_speed -= 1;
}
/********************************************************************
// Function name	: DRVStepperSpeedDown
// Description	    : ����
// Return type		: void
// Argument         : void
*********************************************************************/
void DRVStepperSpeedDown(void)
{
	if(step_speed < STEP_SPEED_MIN)
		step_speed += 1;
}
/********************************************************************
// Function name	: DRVStepperInit
// Description	    : ����������������ʼ��
// Return type		: void
// Argument         : 
*********************************************************************/
void DRVStepperInit()
{
}
/********************************************************************
// Function name	: DRVStepperPulse
// Description	    : ���Ͳ���������壬ÿʮ�������һ��
// Return type		: void
// Argument         : void
*********************************************************************/
void DRVStepperPulse(void)
{
	static int row = 0;
	
	step_cur_count --;
	if (step_enable == STEP_MOTOR_ENABLE && step_cur_count <= 0)
	{
		if( row == 4 ) row = 0;
		if( row < 0 )  row = 3;
		(*(volatile unsigned char*)0x28000006) = pluse_table[row];
		if(step_dire == STEP_MOTOR_CLOCKWISE)
			row ++;
		else
			row --;		

		step_cur_count = step_speed;
	}
}
