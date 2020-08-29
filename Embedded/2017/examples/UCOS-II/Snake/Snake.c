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
File        : Snake.c
Purpose     : 贪食蛇游戏
----------------------------------------------------------------------
*/

#include "gui.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CHAR_WIDTH    8
#define CHAR_HIGH     8

#define SCREEN_HEIGHT (240 - CHAR_HIGH)
#define SCREEN_WIDTH  (240 - CHAR_WIDTH)

#define MAX_NODE 2000

#define VK_LEFT  ('4')
#define VK_RIGHT ('6')
#define VK_UP    ('2')
#define VK_DOWN  ('8')
#define VK_ESC   ('E')
#define VK_SPEED_UP  ('C')
#define VK_SPEED_DOWN  ('D')

#define CH_HEAD 0x1
#define CH_BODY 0x1
#define CH_TAIL 0x1
#define CH_BKG  0

#define DIRE_LEFT    1
#define DIRE_UP      2
#define DIRE_RIGHT   3
#define DIRE_DOWN    4

int  head, tail, length;  /*定义头尾坐标及长度*/
int  speed;       /*游戏速度*/
int  key;         /*键盘按键*/
int  food_x, food_y, food_value;    /*食物的坐标及其分值*/
int  score;

static int nodes[MAX_NODE][3];     /*蛇身节点坐标及移动方向(理论上蛇身最长可有2000节)*/

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

File        : FONT_ShiftJIS.c

Purpose     : Example demonstrating ShiftJIS capabilities of emWin

----------------------------------------------------------------------

*/

#include "gui.h"

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

/********************************************************************
// Function name	: is_xy_inbody
// Description	    : 检查点(x, y)是否已被占用
// Return type		: int
// Argument         : int x
// Argument         : int y
*********************************************************************/
int is_xy_inbody(int x, int y)    /*检查点(x, y)的是否已被占用*/
{
    int i;
    if(head>tail)
    {
    for(i=tail; i<head; i++)
           if(nodes[i][0]==x && nodes[i][1]==y) return 1;
    }
    else
    {
       for(i=tail; i<=MAX_NODE; i++)
           if(nodes[i][0]==x && nodes[i][1]==y) return 1;

       for(i=0; i<head; i++)
           if(nodes[i][0]==x && nodes[i][1]==y) return 1;
    };
    return 0;   /*正常返回0*/
}
/********************************************************************
// Function name	: drawfood
// Description	    : 绘制食物
// Return type		: void
// Argument         : 
*********************************************************************/
void drawfood()
{
    while(!(food_value = rand() % 10));    /*获取一个从1至9的随机整数,并放至food_value*/
    GUI_SetFont(&GUI_Font8_ASCII);

    do
    {
        while(!(food_x = rand() % (SCREEN_WIDTH - CHAR_WIDTH)));
        while(!(food_y = rand() % (SCREEN_HEIGHT - CHAR_HIGH)));
        
        food_x = (food_x / CHAR_WIDTH) * CHAR_WIDTH;
        food_y = (food_y / CHAR_HIGH) * CHAR_HIGH;
    }while(food_x < CHAR_WIDTH || food_y < CHAR_HIGH || is_xy_inbody(food_x, food_y) ||
       	   food_x == nodes[head][0] ||
           food_y == nodes[head][1]);

    GUI_GotoXY(food_x, food_y);
    GUI_DispChar(food_value + 48);
}
/********************************************************************
// Function name	: do_draw
// Description	    : 绘制蛇身
// Return type		: void
// Argument         : int x
// Argument         :  int y
// Argument         :  int type
*********************************************************************/
void do_draw(int x, int y, int type)
{
    GUI_GotoXY(x, y);
    GUI_SetFont(&GUI_FontSnake13);
    
    switch(type)
    {
        case 1: GUI_DispChar(CH_HEAD); break;
        case 2: GUI_DispChar(CH_BODY); break;
        case 3: GUI_DispChar(CH_TAIL); break;
        case 4: GUI_DispChar(CH_BKG);          /*用背景擦除尾巴*/
    };
}
/********************************************************************
// Function name	: draw
// Description	    : 绘制贪食蛇
// Return type		: void
// Argument         : 
*********************************************************************/
void draw()
{
    int i;
    do_draw(nodes[tail][0], nodes[tail][1], 3);    /*画尾巴*/
    if(head>tail)
    {
        for(i = tail + 1; i < head; i++ ) do_draw(nodes[i][0], nodes[i][1], 2);    /*画蛇身*/
    }
    else    /*因为在check()中保证head不可能等于tail,即首尾不会重叠.*/
    {
        for(i = tail + 1; i < MAX_NODE - 1; i++ ) do_draw(nodes[i][0], nodes[i][1], 2);    /*分两步画蛇身*/
        for(i = 0; i < head; i++ ) do_draw(nodes[i][0], nodes[i][1], 2);
    };
    do_draw(nodes[head][0], nodes[head][1], 1);    /*画蛇头*/
}
/********************************************************************
// Function name	: turn
// Description	    : 变换方向
// Return type		: int
// Argument         : int dire
*********************************************************************/
int turn(int dire)
{
    switch(nodes[head][2])
    {
        case DIRE_LEFT:
        case DIRE_RIGHT: switch(dire)
                         {
                             case DIRE_UP:   nodes[head][2] = DIRE_UP;   break;
                             case DIRE_DOWN: nodes[head][2] = DIRE_DOWN;
                         };
                         break;
        case DIRE_UP:
        case DIRE_DOWN:  switch(dire)
                         {
                             case DIRE_LEFT: nodes[head][2] = DIRE_LEFT; break;
                             case DIRE_RIGHT:nodes[head][2] = DIRE_RIGHT;
                         };
    }
}
/********************************************************************
// Function name	: step
// Description	    : 行进一步
// Return type		: void
// Argument         : int increased
*********************************************************************/
void step(int increased)
{
    int newhead;

    newhead = (head + 1) % MAX_NODE;   /*计算蛇头的偏移量*/

    nodes[newhead][0] = nodes[head][0];
    nodes[newhead][1] = nodes[head][1];
    nodes[newhead][2] = nodes[head][2];
    head = newhead;

    switch(nodes[head][2])
    {
        case 1: nodes[head][0]-=CHAR_WIDTH; break;
        case 2: nodes[head][1]-=CHAR_HIGH; break;
        case 3: nodes[head][0]+=CHAR_WIDTH; break;
        case 4: nodes[head][1]+=CHAR_HIGH; break;
    };

    if(!increased)   /*当蛇处于增长状态时,不擦除尾巴*/
    {
        do_draw(nodes[tail][0], nodes[tail][1], 4);   /*擦除尾巴*/
        tail = (tail + 1) % MAX_NODE;   /*计算蛇尾的偏移量*/
    };

    draw();   /*重画蛇*/
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
	GUI_DispStringAt("Snake 1.0", 248, 8);
	GUI_DispStringAt("2 - UP", 242, 16);
	GUI_DispStringAt("8 - DOWN", 242, 24);
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
    length = 10;
    speed = 4;

    GUI_SetFont(&GUI_FontSnake13);
    for(i=0; i <= length - 1; i++)        /*蛇身各节坐标及运动方向,共有6节,且蛇头向左.*/
    {
        nodes[i][0] = 25*CHAR_WIDTH - i*CHAR_WIDTH;     /* X坐标 */
        nodes[i][1] = 12*CHAR_HIGH;         /* Y坐标 */
        nodes[i][2] = DIRE_LEFT;  /* 方向 */
    };
    head = length - 1;
    tail = 0;
    GUI_SetBkColor(GUI_BLUE);
    GUI_SetColor(GUI_WHITE);
    GUI_Clear();
    draw_frame();
    draw_speed();
    draw_score();
    draw_info("Press any key");
    while(GUI_GetKey() == 0) OSTimeDly(1);
    draw_info("Playing          ");
    draw();
    drawfood();
}
/********************************************************************
// Function name	: check
// Description	    : 检查游戏是否结束，为0表示可以继续进行
// Return type		: int
// Argument         : 
*********************************************************************/
int check()        /*返回0表示游戏可以继续进行*/
{
    if(nodes[head][0]==food_x && nodes[head][1]==food_y)   /*吃到食物后的处理*/
    {
        score = score + food_value;
        draw_score();
        length++;
        step(1);
        drawfood();
    }
    else
    {
        step(0);
        {
            int x, y;
            x = nodes[head][0];
            y = nodes[head][1];
        if(x<CHAR_WIDTH || x+CHAR_WIDTH>SCREEN_WIDTH || y<CHAR_HIGH || y+CHAR_HIGH>SCREEN_HEIGHT || is_xy_inbody(x, y)) return 1;
        }
    };
    return 0;    /*正常返回0*/
}
/********************************************************************
// Function name	: gameover
// Description	    : 游戏结束
// Return type		: void
// Argument         : 
*********************************************************************/
void gameover()
{
    draw_info("Game Over!!!      ");
}
/********************************************************************
// Function name	: Snake_Main
// Description	    : 贪食蛇游戏主控程序
// Return type		: void
// Argument         : void
*********************************************************************/
void Snake_Main(void) 
{
    int i=0;

    init();

    while(1)
    {
    	key = GUI_GetKey();
        if(key != 0)     /*检索按键*/
        {
            if(key==VK_ESC) break;

            switch(key)
            {
                case VK_LEFT:  turn(DIRE_LEFT);  break;
                case VK_UP:    turn(DIRE_UP);    break;
                case VK_DOWN:  turn(DIRE_DOWN);  break;
                case VK_RIGHT: turn(DIRE_RIGHT); break;
                case VK_SPEED_UP: 
                	speed --; 
                	if(speed < 1) 
                		speed = 1; 
                	draw_speed(); 
                	break;
                case VK_SPEED_DOWN: 
                	speed ++; 
                	if(speed >= 10) 
                		speed = 10; 
                	draw_speed(); 
                	break;
            };

        };

        if(i = (++i) % 2) if(check()) break;

        OSTimeDly(speed * 4);
    };

    gameover();
}






