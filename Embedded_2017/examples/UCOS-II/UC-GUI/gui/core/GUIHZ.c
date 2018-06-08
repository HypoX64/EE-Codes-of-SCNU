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
// Description	    : 在LCD的(x,y)坐标处以colour颜色显示s中的汉字
// Return type		: void
// Argument         : int x : x坐标
// Argument         : int y : y坐标
// Argument         : char *s : 待显示字符串
// Argument         : int colour : 显示颜色
*****************************************************************************/
void lcd_disp_hzk16(int x,int y,char *s,int textcolour, int backcolour)
{
	char buffer[32];							/* 32字节的字模缓冲区		*/
 	int i,j,k;
 	unsigned char qh,wh;
 	unsigned long location;

 	while(*s)
  	{
   		qh=*s-0xa0;								/* 计算区码					*/
   		wh=*(s+1)-0xa0;							/* 计算位码					*/
   		location=(94*(qh-1)+(wh-1))*32L;		/* 计算字模在文件中的位置	*/
   		memcpy(buffer, &hzk16[location], 32);	/* 获取汉字字模				*/
		for(i=0;i<16;i++)						/* 每一行					*/
		{
    		for(j=0;j<2;j++)					/* 一行两个字节				*/
			{
     			for(k=0;k<8;k++)				/* 每个字节按位显示			*/
				{
      				if(((buffer[i*2+j]>>(7-k)) & 0x1) != 0)
       					lcd_put_pixel(x+8*(j)+k,y+i,textcolour); /* 显示一位	*/
       				else
       					lcd_put_pixel(x+8*(j)+k,y+i,backcolour); /* 显示一位	*/
				}
			}
		}
   		s+=2;												/* 下一个汉字	*/
   		x+=16;												/* 汉字间距		*/
  	}
}
/*****************************************************************************
// Function name	: lcd_disp_ascii16x8
// Description	    : 在LCD的(x,y)坐标处以colour颜色显示s中的ASCII字符
// Return type		: void
// Argument         : int x : x坐标
// Argument         : int y : y坐标
// Argument         : char c : 待显示字符串
// Argument         : int colour : 显示颜色
*****************************************************************************/
void lcd_disp_ascii16x8(int x,int y,char c,int textcolour, int backcolour)
{
	char buffer[32];							/* 32字节的字模缓冲区		*/
 	int i,j,k;
 	unsigned long location;

  	location=c * 16;		/* 计算字模在文件中的位置	*/
   	memcpy(buffer, &arcii16x8[location], 16);	/* 获取汉字字模				*/
	for(i=0;i<16;i++)						/* 每一行					*/
	{
    	for(j=0;j<1;j++)					/* 一行两个字节				*/
		{
     		for(k=0;k<8;k++)				/* 每个字节按位显示			*/
			{
      			if(((buffer[i*1+j]>>(7-k)) & 0x1) != 0)
     				lcd_put_pixel(x+8*(j)+k,y+i,textcolour); /* 显示一位	*/
     			else
     				lcd_put_pixel(x+8*(j)+k,y+i,backcolour); /* 显示一位	*/
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
			// 显示ascii字符
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
