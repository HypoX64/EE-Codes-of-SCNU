#include "dma.h"

#define DAC_DHR12R2_Address      0x40007414
uint16_t Sine12bit[64] = {  
0x7FF,0x8C8,0x98E,0xA51,0xB0F,0xBC4,0xC71,0xD12,0xDA7,0xE2E,0xEA5,0xF0D,0xF63,0xFA6,0xFD7,0xFF5  
,0xFFE,0xFF5,0xFD7,0xFA6,0xF63,0xF0D,0xEA5,0xE2E,0xDA7,0xD12,0xC71,0xBC4,0xB0F,0xA51,0x98E,0x8C8  
,0x7FF,0x736,0x670,0x5AD,0x4EF,0x43A,0x38D,0x2EC,0x257,0x1D0,0x159,0x0F1,0x09B,0x058,0x027,0x009  
,0x000,0x009,0x027,0x058,0x09B,0x0F1,0x159,0x1D0,0x257,0x2EC,0x38D,0x43A,0x4EF,0x5AD,0x670,0x736  
}; 
void DMAx_Init(void)  
{  
	DMA_InitTypeDef DMA_InitStructure;  
	GPIO_InitTypeDef GPIO_InitStructure;  
	/* DMA1 clock enable */  
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);  
	/* GPIOA Periph clock enable */  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  
	/* DAC Periph clock enable */  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);  

	/* Once the DAC channel is enabled, the corresponding GPIO pin is automatically  
	 connected to the DAC converter. In order to avoid parasitic consumption,  
	 the GPIO pin should be configured in analog */  
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//配置为模拟输入，抗噪声干扰  
	GPIO_Init(GPIOA, &GPIO_InitStructure);  

	/* DMA1 channel4 configuration */  
	DMA_DeInit(DMA2_Channel4);  

	DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12R2_Address;//DAC通道2的12位右对齐寄存器地址  
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&Sine12bit;  
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  
	DMA_InitStructure.DMA_BufferSize = 64;//采样64点，故缓存大小为64  
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;  
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;  
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  

	DMA_Init(DMA2_Channel4,&DMA_InitStructure);  
	DMA_Cmd(DMA2_Channel4, ENABLE);  
  
} 

void TIM2_DAC_Init(u16 arr,u16 psc)  
{  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
	DAC_InitTypeDef DAC_InitStructure;  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  
	  
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);   
	TIM_TimeBaseStructure.TIM_Period = arr;            
	TIM_TimeBaseStructure.TIM_Prescaler = psc;         
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;      
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;  //设为向下计数  
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);  

	TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);  

	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;  
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;  
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;  //使能输出缓存  
	DAC_Init(DAC_Channel_2, &DAC_InitStructure);  
	  
		  
	DAC_Cmd(DAC_Channel_2, ENABLE);  

	DAC_DMACmd(DAC_Channel_2, ENABLE);  
	  
	TIM_Cmd(TIM2, ENABLE);  
  
  
} 

void SinData_Init(void) 
{
	int i=0;
	for (i = 0; i < 64; i++)  
	{  
		Sine12bit[i] = Sine12bit[i]*8/10+500;   //防止出现底部失真  
	}
}
