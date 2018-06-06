#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

#define CLK PAout(4)	
#define PN PAout(3)
 
 
void TIM1_PWM_Init(u16 arr,u16 psc);
void TIM2_Cap_Init(u16 arr,u16 psc);
void TIM3_Int_Init(u16 arr,u16 psc); 
void SIGNAL_GPIO_Init(void);
#endif
