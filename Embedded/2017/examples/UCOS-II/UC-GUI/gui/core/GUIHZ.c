#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

unsigned char *hzk16 = 0x10000;
unsigned char *arcii16x8 = 0x90000;

#define LCD_YSIZE 240
#define LCD_XSIZE 320

extern unsigned char *frameBuffer256;
/*****************************************************************************
// Function name	: lcd_disp_hzk16
// Description	    : ��LCD��(x,y)���괦��colour��ɫ��ʾs�еĺ���
// Return type		: void
// Argument         : int x : x����
// Argument         : int y : y����
// Argument         : char *s : ����ʾ�ַ���
// Argument         : int colour : ��ʾ��ɫ
*****************************************************************************/
void lcd_disp_hzk16(int x,int y,char *s,int textcolour, int backcolour)
{
	char buffer[32];							/* 32�ֽڵ���ģ������		*/
 	int i,j,k;
 	unsigned char qh,wh;
 	unsigned long location;

 	while(*s)
  	{
   		qh=*s-0xa0;								/* ��������					*/
   		wh=*(s+1)-0xa0;							/* ����λ��					*/
   		location=(94*(qh-1)+(wh-1))*32L;		/* ������ģ���ļ��е�λ��	*/
   		memcpy(buffer, &hzk16[location], 32);	/* ��ȡ������ģ				*/
		for(i=0;i<16;i++)						/* ÿһ��					*/
		{
    		for(j=0;j<2;j++)					/* һ�������ֽ�				*/
			{
     			for(k=0;k<8;k++)				/* ÿ���ֽڰ�λ��ʾ			*/
				{
      				if(((buffer[i*2+j]>>(7-k)) & 0x1) != 0)
       					lcd_put_pixel(x+8*(j)+k,y+i,textcolour); /* ��ʾһλ	*/
       				else
       					lcd_put_pixel(x+8*(j)+k,y+i,backcolour); /* ��ʾһλ	*/
				}
			}
		}
   		s+=2;												/* ��һ������	*/
   		x+=16;												/* ���ּ��		*/
  	}
}
/*****************************************************************************
// Function name	: lcd_disp_ascii16x8
// Description	    : ��LCD��(x,y)���괦��colour��ɫ��ʾs�е�ASCII�ַ�
// Return type		: void
// Argument         : int x : x����
// Argument         : int y : y����
// Argument         : char c : ����ʾ�ַ���
// Argument         : int colour : ��ʾ��ɫ
*****************************************************************************/
void lcd_disp_ascii16x8(int x,int y,char c,int textcolour, int backcolour)
{
	char buffer[32];							/* 32�ֽڵ���ģ������		*/
 	int i,j,k;
 	unsigned long location;

  	location=c * 16;		/* ������ģ���ļ��е�λ��	*/
   	memcpy(buffer, &arcii16x8[location], 16);	/* ��ȡ������ģ				*/
	for(i=0;i<16;i++)						/* ÿһ��					*/
	{
    	for(j=0;j<1;j++)					/* һ�������ֽ�				*/
		{
     		for(k=0;k<8;k++)				/* ÿ���ֽڰ�λ��ʾ			*/
			{
      			if(((buffer[i*1+j]>>(7-k)) & 0x1) != 0)
     				lcd_put_pixel(x+8*(j)+k,y+i,textcolour); /* ��ʾһλ	*/
     			else
     				lcd_put_pixel(x+8*(j)+k,y+i,backcolour); /* ��ʾһλ	*/
			}
		}
	}
}
/*
 wirte screen
 */
void GUI_DispHZString(char *msg, int REPORT_X, int REPORT_Y, int COLOR_BACK, int COLOR_TEXT)
{
	#define LCD_X_HZ_STEP  16
	#define LCD_X_ASCII_STEP  8
	#define LCD_Y_STEP  16
    
    int i,j,k;
    int x,y;
    int len;
    char c;
    char color;
    int pixlocal;

	len = strlen(msg);
	for(k=0;k<len;k++)
	{
		c = msg[k];
		if(c == '\n')
		{
		    REPORT_Y += LCD_Y_STEP;
		    REPORT_X = 0;
			if(REPORT_Y >= LCD_YSIZE)
			{
				REPORT_Y = LCD_YSIZE - LCD_Y_STEP;
				memcpy(((unsigned char *)frameBuffer256), ((unsigned char *)frameBuffer256) + LCD_XSIZE * LCD_Y_STEP, LCD_XSIZE*(LCD_YSIZE - LCD_Y_STEP));
				memset(((unsigned char *)frameBuffer256) + LCD_XSIZE*(LCD_YSIZE - LCD_Y_STEP), COLOR_BACK, LCD_XSIZE * LCD_Y_STEP);
			}
		}else if(c == '\r')
		{
			// do nothing
		}else if(c == '\b')
		{
		    REPORT_X -= LCD_X_HZ_STEP;
			if(REPORT_X < 0)
			{
				REPORT_X = 0;
				REPORT_Y -= LCD_Y_STEP;
			}
		}else if(c <= 128)
		{
			// ��ʾascii�ַ�
			if(REPORT_X >= LCD_XSIZE)
			{
				REPORT_X = 0;
				REPORT_Y += LCD_Y_STEP;
				if(REPORT_Y >= LCD_YSIZE)
				{
					REPORT_Y = LCD_YSIZE - LCD_Y_STEP;
					memcpy(((unsigned char *)frameBuffer256), ((unsigned char *)frameBuffer256) + LCD_XSIZE * LCD_Y_STEP, LCD_XSIZE*(LCD_YSIZE - LCD_Y_STEP));
					memset(((unsigned char *)frameBuffer256) + LCD_XSIZE*(LCD_YSIZE - LCD_Y_STEP), COLOR_BACK, LCD_XSIZE * LCD_Y_STEP);
				}
			}
			lcd_disp_ascii16x8(REPORT_X, REPORT_Y, c, COLOR_TEXT, COLOR_BACK);
		    REPORT_X += LCD_X_ASCII_STEP;
		}else
		{
			char str[3];
			str[0] = msg[k];
			str[1] = msg[k+1];
			k++;
			str[2] = 0;
			if(REPORT_X >= LCD_XSIZE)
			{
				REPORT_X = 0;
				REPORT_Y += LCD_Y_STEP;
				if(REPORT_Y >= LCD_YSIZE)
				{
					REPORT_Y = LCD_YSIZE - LCD_Y_STEP;
					memcpy(((unsigned char *)frameBuffer256), ((unsigned char *)frameBuffer256) + LCD_XSIZE * LCD_Y_STEP, LCD_XSIZE*(LCD_YSIZE - LCD_Y_STEP));
					memset(((unsigned char *)frameBuffer256) + LCD_XSIZE*(LCD_YSIZE - LCD_Y_STEP), COLOR_BACK, LCD_XSIZE * LCD_Y_STEP );
				}
			}
			lcd_disp_hzk16(REPORT_X, REPORT_Y, str, COLOR_TEXT, COLOR_BACK);
		    REPORT_X += LCD_X_HZ_STEP;
		}
	}
}
