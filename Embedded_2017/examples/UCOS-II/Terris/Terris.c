/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              礐/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : Terris.c
Purpose     : 俄罗斯方块游戏
----------------------------------------------------------------------
*/

#include "gui.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define LEFT      '4'  
#define RIGHT     '6'  
#define DOWN      '8'  
#define CHANGE    '2'  
#define ESC       'E'  
#define SPEEDUP   'C'
#define SPEEDDOWN 'D'

#define DefaultX 5  
#define DefaultY 1  

/* LATIN CAPITAL LETTER A */
static const unsigned char acFontSnake13_0000[ 13] = { /* code 0000 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};
/* LATIN CAPITAL LETTER B */
static const unsigned char acFontSnake13_0001[ 13] = { /* code 0001 */
  XXXXXXXX,
  XXXXXXXX,
  XXXXXXXX,
  XXXXXXXX,
  XXXXXXXX,
  XXXXXXXX,
  XXXXXXXX,
  XXXXXXXX,
  XXXXXXXX,
  XXXXXXXX,
  XXXXXXXX,
  XXXXXXXX,
  XXXXXXXX};

static const GUI_CHARINFO GUI_FontSnake13_CharInfo[2] = {
   {   8,   8,  1, (void *)&acFontSnake13_0000 } /* code 0000 */
  ,{   8,   8,  1, (void *)&acFontSnake13_0001 } /* code 0001 */
};
static const GUI_FONT_PROP GUI_FontSnake13_Prop1 = {
   0x0000 /* first character */
  ,0x0001 /* last character  */
  ,&GUI_FontSnake13_CharInfo[  0] /* address of first character */
  ,(void*)0 /* pointer to next GUI_FONT_PROP */
};
static const GUI_FONT GUI_FontSnake13 = {
   GUI_FONTTYPE_PROP_SJIS /* type of font    */
  ,8 /* height of font  */
  ,8 /* space of font y */
  ,1 /* magnification x */
  ,1 /* magnification y */
  ,(void *)&GUI_FontSnake13_Prop1
};

int  speed = 4;       /*游戏速度*/
int  gameover;
static unsigned counter=0;  
static unsigned shape[7][4][4][4]=
{  
	{  
		{{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},  
		{{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},  
		{{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},  
		{{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},  
	},  
	{  
		{{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},  
		{{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}},  
		{{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},  
		{{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}},  
	},  
	{  
		{{0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},  
		{{0,1,0,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},  
		{{0,0,0,0},{1,1,1,0},{0,1,0,0},{0,0,0,0}},  
		{{0,1,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}},  
	},  
	{  
		{{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}},  
		{{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}},  
		{{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}},  
		{{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}},  
	},  
	{  
		{{0,1,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}},  
		{{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}},  
		{{0,1,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}},  
		{{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}},  
	},  
	{  
		{{1,0,0,0},{1,0,0,0},{1,1,0,0},{0,0,0,0}},  
		{{0,0,0,0},{1,1,1,0},{1,0,0,0},{0,0,0,0}},  
		{{1,1,0,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}},  
		{{0,0,0,0},{0,0,1,0},{1,1,1,0},{0,0,0,0}},  
	},  
	{  
		{{0,1,0,0},{0,1,0,0},{1,1,0,0},{0,0,0,0}},  
		{{0,0,0,0},{1,0,0,0},{1,1,1,0},{0,0,0,0}},  
		{{1,1,0,0},{1,0,0,0},{1,0,0,0},{0,0,0,0}},  
		{{0,0,0,0},{1,1,1,0},{0,0,1,0},{0,0,0,0}},  
	},  
};  

unsigned back[22][14]=
{
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1},  
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};  

unsigned back1[22][14]=
{
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1},  
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1},  
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};  

int ShapeColor[7]={GUI_RED,GUI_GREEN,GUI_BLUE,GUI_LIGHTRED,GUI_BLUE,GUI_YELLOW,GUI_BLUE};  
char DigitalShape[10]={128+119,3,62,31,128+75,128+93,128+125,19,128+127,128+95};  
int ZodiacBack[11]={GUI_RED,GUI_BROWN,GUI_LIGHTRED,GUI_LIGHTMAGENTA,GUI_LIGHTCYAN,GUI_LIGHTGREEN,GUI_GREEN,GUI_CYAN,GUI_LIGHTBLUE,GUI_BLUE,GUI_DARKGRAY};  
char ZodiacSoft[18][14]={
	{0,0,0,0,96,0,0,0,0,0,0,0,60,0},  
	{255,248,0,0,96,0,0,0,0,248,0,0,124,0},  
	{255,248,0,0,97,128,0,0,3,248,0,0,192,0},  
	{0,112,0,0,97,128,0,0,7,0,0,1,128,48},  
	{0,224,0,0,96,0,0,0,14,0,0,1,128,48},  
	{1,192,0,0,96,0,0,0,12,0,0,1,128,48},  
	{3,128,120,15,97,128,240,60,12,0,15,15,249,255},  
	{7,0,252,31,225,131,248,127,14,0,31,143,249,255},  
	{7,1,142,48,225,135,24,227,7,240,49,193,128,48},  
	{14,3,134,96,97,142,24,192,3,252,112,193,128,48},  
	{28,3,6,96,97,140,25,192,0,28,96,193,128,48},  
	{56,3,6,96,97,140,25,128,0,6,96,193,128,48},  
	{56,3,6,96,97,140,25,128,0,6,96,193,128,48},  
	{120,3,6,96,97,140,25,128,0,6,96,193,128,48},  
	{224,1,140,48,225,142,25,195,24,14,49,129,128,48},  
	{255,249,252,63,225,135,252,255,28,28,63,129,128,48},  
	{255,248,240,15,97,131,236,60,15,248,30,1,128,48},  
	{0,0,0,0,0,0,0,0,7,224,0,1,128,0}
};  

unsigned long score=0;  
unsigned int Erasered=0,ETimes=0;  
int CEr=0;  
int NumOfLev[5]={0,0,0,0,0};  
int TimeDelay[10]={21,18,17,15,13,11,9,7,5,3};  
char NewShape[2];  
unsigned PerOnce[4];  

void setcolor(int c);

void game_over()  
{  
	int i, j;
	
	gameover = 1;
	draw_info("Game Over!!!"); 
	clrscr();  
}  
void DrawShape(int x,int y,int color)  
{  
	int i;
	setcolor(color);  
	for(i=0;i<19/*15*/;i++)  
		line(x*20,(y*20)+i,(x*20)+18/*14*/,(y*20)+i);  
	setcolor(GUI_DARKGRAY);  
	line((x*20)+19/*15*/,(y*20)+1,(x*20)+19/*15*/,(y*20)+19/*15*/);  
	line((x*20)+1,(y*20)+15,(x*20)+19/*15*/,(y*20)+19/*15*/);  
	setcolor(color-8);  
	line((x*20)+2,(y*20)+2,(x*20)+16/*12*/,(y*20)+2);  
	line((x*20)+2,(y*20)+2,(x*20)+2,(y*20)+16/*12*/);  
}  

void DrawNull(int x,int y)  
{  
	int i;
	setcolor(GUI_WHITE);  
	for(i=0;i<20/*16*/;i++)  
		line(x*20,(y*20)+i,(x*20)+19/*15*/,(y*20)+i);  
}  

void show(int x,int y,int CurrentShape,int Status)  
{  
	int temp, i, j, l, p;  
	for(i=0;i<20;i++)  
		for(j=2;j<12;j++)  
		{  
			if(back[i][j]==1)  
				DrawShape(6+j,2+i,GUI_BLUE);  
			else  
				DrawNull(6+j,2+i);  
		} //no matter what the status be,I will draw the background  
		for(l=0;l<4;l++)  
			for(p=0;p<4;p++)  
			{  
				if(l+x<2||x+l>11||p+y>19)  
					continue;  
				//if(shape[CurrentShape][Status][p][l]+back[y+p][x+l]==1)  
				// DrawShape(3+l+x,3+p+y,8+CurrentShape);  
				//else  
				//cout<<'O';  
				// DrawNull(3+j,3+i);  
				if(shape[CurrentShape][Status][p][l]==1)  
					DrawShape(6+l+x,2+p+y,ShapeColor[CurrentShape]);  
				if(back[y+p][x+l]==1)  
					DrawShape(6+l+x,2+p+y,GUI_BLUE);  
			}  
}  
int CreateNewShape()  
{  
	int l, p;
	
	setcolor(GUI_DARKGRAY);  
	bar(493, 141, 613, 235);

	NewShape[1]=NewShape[0];  
	NewShape[0]=rand()%7;  
	for(l=0;l<4;l++)  
		for(p=0;p<4;p++)  
			if(shape[NewShape[0]][0][p][l]==1)  
				DrawShape(26+l,8+p,GUI_GREEN/*ShapeColor[7]*/);  
			return NewShape[1];  
}  

int Possible(int x,int y,int CurrentShape,int Status)  
{  
	int i, j;
	
	for(i=0;i<4;i++)  
	{  
		for(j=0;j<4;j++)  
		{  
			if(shape[CurrentShape][Status][i][j]+back[y+i][x+j]==2)  
				//this line can also write as the following type:  
				//if(shape[CurrentShape][Status][i][j]&&back[y+i][x+j])  
				return 0;  
		}  
	}  
	return 1;  
}  

void GoLeft(int *x,int *y,int *CurrentShape,int *Status)  
{  
	if(Possible(*x-1,*y,*CurrentShape,*Status))  
		*x = (*x)-1;  
	show(*x,*y,*CurrentShape,*Status);  
}  

void GoRight(int *x,int *y,int *CurrentShape,int *Status)  
{  
	if(Possible(*x+1,*y,*CurrentShape,*Status))  
		*x = (*x) + 1;  
	show(*x,*y,*CurrentShape,*Status);  
}  

void GoDown(int *x,int *y,int *CurrentShape,int *Status)  
{  
	int AllAreOne=1,temp=0; 
	int i, j, r, l, rr, ll;
	 
	if(Possible(*x,(*y)+1,*CurrentShape,*Status))  
	{  
		*y = (*y)+1;  
		show(*x,*y,*CurrentShape,*Status);  
		return;  
	}  
	score+=3*(*CurrentShape);  
	for(i=0;i<4;i++)  
		for(j=0;j<4;j++)  
			back[i+(*y)][j+(*x)]+=shape[*CurrentShape][*Status][i][j];  
		for(r=1;r<20;r++)  
		{  
			for(l=2;l<13;l++)  
			{  
				if(back[r][l]==0)  
					AllAreOne=0;  
			}  
			if(AllAreOne==1)  
			{  
				for(rr=r;rr>0;rr--)  
					for(ll=2;ll<13;ll++)  
						back[rr][ll]=back[rr-1][ll];  
					Erasered++;  
					CEr++;  
					temp++;  
			}  
			AllAreOne=1;  
		}  
		*CurrentShape=CreateNewShape();  
		*x=DefaultX;*y=DefaultY;*Status=0;  
		NumOfLev[temp]++;  
		score+=5*temp;  
		show(*x,*y,*CurrentShape,*Status);  
		counter=0;  
		if(!Possible(*x,*y,*CurrentShape,*Status))  
		{  
			getch();  
			game_over();  
		}  
		if(CEr>=30)  
		{  
			speed=(speed+1)%10;  
			CEr/=30;  
		}  
		if(temp)  
			ETimes++;  
		draw_score();  
		return;  
}  

void ChageShape(int*x,int*y,int*CurrentShape,int*Status)  
{  
	if(Possible(*x,*y,*CurrentShape,(*Status+1)%4))  
		*Status=(*Status+1)%4;  
	show(*x,*y,*CurrentShape,*Status);  
}  

void DrawFace()  
{  
	int temp, i;  
	setcolor(GUI_WHITE);  
	line(491,139,615,139);  
	line(491,140,614,140);  
	line(491,139,491,236);  
	line(492,139,492,235);  
	setcolor(GUI_LIGHTGRAY);  
	line(614,141,614,234);  
	line(615,140,615,234);  
	line(493,235,615,235);  
	line(492,236,615,236);  
	setcolor(GUI_DARKGRAY);  
	bar(493, 141, 613, 235);
	setcolor(GUI_LIGHTGRAY);  
}  
/********************************************************************
// Function name	: draw_frame
// Description	    : 绘制边框
// Return type		: void
// Argument         : 
*********************************************************************/
void draw_frame()
{
	int loopcnt;
	
    GUI_SetFont(&GUI_FontSnake13);
	for(loopcnt = 0; loopcnt < 40; loopcnt ++ ) 
	{
		GUI_GotoXY(loopcnt * 8, 0);
		GUI_DispChar(0x1);

		GUI_GotoXY(loopcnt * 8, 240 - 8);
		GUI_DispChar(0x1);
	}

	for(loopcnt = 0; loopcnt < 30; loopcnt ++ ) 
	{
		GUI_GotoXY(0, loopcnt * 8);
		GUI_DispChar(0x1);

		GUI_GotoXY(240 - 8, loopcnt * 8);
		GUI_DispChar(0x1);

		GUI_GotoXY(320 - 8, loopcnt * 8);
		GUI_DispChar(0x1);
	}

	for(loopcnt = 30; loopcnt < 40; loopcnt ++ ) 
	{
		GUI_GotoXY(loopcnt * 8, 15 * 8);
		GUI_DispChar(0x1);
	}
	
    GUI_SetFont(&GUI_Font8_ASCII);
	GUI_DispStringAt("Terris 1.0", 248, 8);
	GUI_DispStringAt("2 - CHANGE", 242, 16);
	GUI_DispStringAt("8 - SPEED", 242, 24);
	GUI_DispStringAt("4 - LEFT", 242, 32);
	GUI_DispStringAt("6 - RIGHT", 242, 40);
	GUI_DispStringAt("UP - FAST", 242, 48);
	GUI_DispStringAt("DOWN - SLOW", 242, 56);
}
/********************************************************************
// Function name	: draw_level
// Description	    : 打印当前级别
// Return type		: void
// Argument         : 
*********************************************************************/
void draw_level()
{
	char str[20];
	GUI_SetBkColor(GUI_BLACK);
	GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font8_ASCII);
    sprintf(str, "LEVEL:%d", score / 50 + 1);
	GUI_DispStringAt(str, 242, 21 * 8);
}
/********************************************************************
// Function name	: draw_score
// Description	    : 打印当前得分数
// Return type		: void
// Argument         : 
*********************************************************************/
void draw_score()
{
	char str[20];
	GUI_SetBkColor(GUI_BLACK);
	GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font8_ASCII);
    sprintf(str, "SCORE:%d", score);
	GUI_DispStringAt(str, 242, 17 * 8);
	draw_level();
}
/********************************************************************
// Function name	: draw_speed
// Description	    : 打印游戏速度提示信息
// Return type		: void
// Argument         : 
*********************************************************************/
void draw_speed()
{
	char str[20];
	GUI_SetBkColor(GUI_BLACK);
	GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font8_ASCII);
    sprintf(str, "SPEED:%d", speed);
	GUI_DispStringAt(str, 242, 19 * 8);
}
/********************************************************************
// Function name	: draw_info
// Description	    : 打印提示信息
// Return type		: void
// Argument         : char *info
*********************************************************************/
void draw_info(char *info)
{
	GUI_SetBkColor(GUI_BLACK);
	GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font8_ASCII);
	GUI_DispStringAt(info, 242, 23 * 8);
}
/*******************************************************************
// Function name	: init
// Description	    : 初始化函数
// Return type		: void
// Argument         : 
*********************************************************************/
void init()
{
    int i;
    score =0;
    speed = 4;

    GUI_SetBkColor(GUI_BLACK);
    GUI_SetColor(GUI_WHITE);
    GUI_Clear();
    draw_frame();
    draw_speed();
    draw_score();
    draw_info("Press any key");
    while(GUI_GetKey() == 0);
    draw_info("Playing          ");
}
/********************************************************************
// Function name	: Terris_Main
// Description	    : 俄罗斯方块游戏主控程序
// Return type		: void
// Argument         : void
*********************************************************************/
void Terris_Main(void) 
{
	unsigned c;  
	int CurrentShape,x=6,y=0,Status=0;  
	NewShape[0]=rand()%7;  
	gameover = 0;
	
	init();
	memcpy(back, back1, 22*14 * sizeof(unsigned));
	
	DrawFace();  
	CurrentShape=CreateNewShape();  
	show(x,y,CurrentShape,Status);  
	while(gameover == 0)  
	{  
		c=getch();  
		if(c != 0)  
		{  
			if(c==0)  
				c=getch();  
			switch(c)  
			{  
			case DOWN :GoDown(&x,&y,&CurrentShape,&Status);break;  
			case LEFT :GoLeft(&x,&y,&CurrentShape,&Status);break;  
			case RIGHT :GoRight(&x,&y,&CurrentShape,&Status);break;  
			case CHANGE :ChageShape(&x,&y,&CurrentShape,&Status);break;  
			case SPEEDUP: speed --; if(speed <= 0) speed =1;  draw_speed(); break;
			case SPEEDDOWN: speed ++; if(speed > 10) speed =10;  draw_speed(); break;
			counter=0;  
			}  
		}  
		if(counter == (speed))  
		{  
			GoDown(&x,&y,&CurrentShape,&Status);  
			counter=0;  
		}  
		counter ++;
		OSTimeDly(1);
	}  
}

void setcolor(int c)
{
	GUI_SetColor(c);
}
int line(int x1, int y1, int x2, int y2)
{
	if(x1 == x2)
	{
		GUI_DrawVLine(x1/2, y1/2, y2/2);
	}else if(y1 == y2)
	{
		GUI_DrawHLine(y1/2, x1/2, x2/2);
	}
}
int getbkcolor()
{
	return GUI_GetBkColor();
}

int outtextxy(int x, int y, char *s)
{
	GUI_DispStringAt(s, x/2, y/2);
}

int gotoxy(int x, int y)
{
	GUI_GotoXY(x, y);
}

int getch()
{
	return GUI_GetKey();
}

int clrscr()
{
	GUI_Clear();
}

int setbkcolor(int c)
{
	GUI_SetBkColor(c);
}

int putpixel(int x, int y, int c)
{
	
}

int bar(int x1, int y1, int x2, int y2)
{
	GUI_SetBkColor(GUI_RED);
	GUI_FillRect(x1/2, y1/2, x2/2, y2/2);
}

int circle(int x0, int y0, int r)
{
	GL_DrawCircle(x0, y0, r);
}

