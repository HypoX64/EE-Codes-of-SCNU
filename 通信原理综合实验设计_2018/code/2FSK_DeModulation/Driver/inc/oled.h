#ifndef __OLED_H
#define __OLED_H			  	 
#include "sys.h"
#include "stdlib.h"	    


//OLEDģʽ����
//0:SPI4�ߴ���ģʽ
//1:����8080ģʽ
#define OLED_MODE 0
		    						  
//-----------------OLED�˿ڶ���----------------  					   
#define OLED_CS PCout(9)
//#define OLED_RST  PBout(14)//��MINISTM32��ֱ�ӽӵ���STM32�ĸ�λ�ţ�	
#define OLED_RS PCout(8)
#define OLED_WR PCout(7)		  
#define OLED_RD PCout(6)

//PB0~7,��Ϊ������
#define DATAOUT(DataValue) {GPIO_Write(GPIOB,(GPIO_ReadOutputData(GPIOB)&0xff00)|(DataValue&0x00FF));}  

//ʹ��4�ߴ��нӿ�ʱʹ�� 
#define OLED_SCLK PBout(0)
#define OLED_SDIN PBout(1)
		     
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����
//OLED�����ú���

//OLED�����ú���
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);		   
							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);
void OLED_ShowString(u8 x,u8 y,const u8 *p);
void OLED_Show_Font(u16 x,u16 y,u8 font_size,u8 fnum);
#endif  
	 



