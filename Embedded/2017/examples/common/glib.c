#include "def.h"
#include "lcdlib.h"
#include "glib.h"
#include "lcd.h"
#include "hzk16.h"
#include "ascii.h"

void (*PutPixel)(U32,U32,U32);

void Glib_Init(int type)
{
    switch(type)
    {
    case MODE_STN_1BIT:
    	PutPixel=_PutStn1Bit;
    	break;
    case MODE_STN_2BIT:
       	PutPixel=_PutStn2Bit;
       	break;
    case MODE_STN_4BIT:
        PutPixel=_PutStn4Bit;
        break;
    case MODE_CSTN_8BIT:
    	PutPixel=_PutCstn8Bit;
    	break;   
    case MODE_CSTN_12BIT:
    	PutPixel=_PutCstn12Bit;
    	break;   
    case MODE_TFT_8BIT_240320:
    	PutPixel=_PutTft8Bit_240320;   	
    	break;   
    case MODE_TFT_16BIT_240320:
    	PutPixel=_PutTft16Bit_240320;
    	break;   
    case MODE_TFT_1BIT_640480:
    	PutPixel=_PutTft1Bit_640480;
    	break;   
    case MODE_TFT_8BIT_640480:
    	PutPixel=_PutTft8Bit_640480;
    	break;   
    case MODE_TFT_16BIT_640480:
    	PutPixel=_PutTft16Bit_640480;
    	break;   
    case MODE_TFT_24BIT_640480:
    	PutPixel=_PutTft24Bit_640480;
    	break;   
//--------------------------------------
    case MODE_TFT_1BIT_800600:
    	PutPixel=_PutTft1Bit_800600;
    	break;   
    case MODE_TFT_8BIT_800600:
    	PutPixel=_PutTft8Bit_800600;
    	break;   
    case MODE_TFT_16BIT_800600:
    	PutPixel=_PutTft16Bit_800600;
    	break;   
//--------------------------------------
    default: 
    	break;
    }
}


void _PutStn1Bit(U32 x,U32 y,U32 c)
{
    if(x<SCR_XSIZE_STN&& y<SCR_YSIZE_STN)
	frameBuffer1Bit[(y)][(x)/32]=( frameBuffer1Bit[(y)][(x)/32]
	& ~(0x80000000>>((x)%32)*1) ) | ( (c&0x00000001)<< ((32-1-((x)%32))*1) );
}


void _PutStn2Bit(U32 x,U32 y,U32 c)
{
    if(x<SCR_XSIZE_STN&& y<SCR_YSIZE_STN)
        frameBuffer2Bit[(y)][(x)/16]=( frameBuffer2Bit[(y)][x/16]
	& ~(0xc0000000>>((x)%16)*2) ) | ( (c&0x00000003)<<((16-1-((x)%16))*2) );
}


void _PutStn4Bit(U32 x,U32 y,U32 c)
{
    if(x<SCR_XSIZE_STN&& y<SCR_YSIZE_STN)
        frameBuffer4Bit[(y)][(x)/8]=( frameBuffer4Bit[(y)][x/8]
	& ~(0xf0000000>>((x)%8)*4) ) | ( (c&0x0000000f)<<((8-1-((x)%8))*4) );
}


void _PutCstn8Bit(U32 x,U32 y,U32 c)
{
    if(x<SCR_XSIZE_CSTN&& y<SCR_YSIZE_CSTN)
        frameBuffer8Bit[(y)][(x)/4]=( frameBuffer8Bit[(y)][x/4]
	    & ~(0xff000000>>((x)%4)*8) ) | ( (c&0x000000ff)<<((4-1-((x)%4))*8) );
}


void _PutCstn12Bit(U32 x,U32 y,U32 c)
{
    U32 z;
    z=((x)%8);
    if(x<SCR_XSIZE_CSTN&& y<SCR_YSIZE_CSTN)
    {

        if((z%3)!=2)
            frameBuffer12Bit[(y)][(x)*3/8]=
            ( frameBuffer12Bit[(y)][(x)*3/8] & ~(0xfff00000>>(((z/3)*4)+((z)%3)*12) )
		| ( (c&0xfff)<<(20-(((z/3)*4)+((z)%3)*12))) );
        else
        {
            if(z==2)
            {
                frameBuffer12Bit[(y)][(x)*3/8]=( (frameBuffer12Bit[(y)][(x)*3/8]
		    & ~(0xff)) | ((c&0xff0)>>4)  ); 
                frameBuffer12Bit[(y)][((x)*3/8)+1]=( (frameBuffer12Bit[(y)][((x)*3/8)+1]
		    & ~(0xf0000000)) | ((c&0xf)<<28)  );
            }   
            else if(z==5)
            {
                frameBuffer12Bit[(y)][(x)*3/8]=( (frameBuffer12Bit[(y)][(x)*3/8]
	            & ~(0xf)) | ((c&0xf00)>>8)  );
                frameBuffer12Bit[(y)][((x)*3/8)+1]=( (frameBuffer12Bit[(y)][((x)*3/8)+1]
	            & ~(0xff000000)) | ((c&0xff)<<24)  );
            }   
        }
    }
}


void _PutTft8Bit_240320(U32 x,U32 y,U32 c)
{
    if(x<SCR_XSIZE_TFT_240320 && y<SCR_YSIZE_TFT_240320)
        frameBuffer8BitTft240320[(y)][(x)/4]=( frameBuffer8BitTft240320[(y)][x/4]
        & ~(0xff000000>>((x)%4)*8) ) | ( (c&0x000000ff)<<((4-1-((x)%4))*8) );
}


void _PutTft16Bit_240320(U32 x,U32 y,U32 c)
{
    if(x<SCR_XSIZE_TFT_240320 && y<SCR_YSIZE_TFT_240320)
        frameBuffer16BitTft240320[(y)][(x)/2]=( frameBuffer16BitTft240320[(y)][x/2]
        & ~(0xffff0000>>((x)%2)*16) ) | ( (c&0x0000ffff)<<((2-1-((x)%2))*16) );
}


void _PutTft1Bit_640480(U32 x,U32 y,U32 c)
{
    if(x<SCR_XSIZE_TFT_640480 && y<SCR_YSIZE_TFT_640480)
        frameBuffer1BitTft640480[(y)][(x)/32]=( frameBuffer1BitTft640480[(y)][x/32]
	& ~(0x80000000>>((x)%32)*1) ) | ( (c&0x00000001)<< ((32-1-((x)%32))*1) );
}


void _PutTft8Bit_640480(U32 x,U32 y,U32 c)
{
    if(x<SCR_XSIZE_TFT_640480 && y<SCR_YSIZE_TFT_640480)
        frameBuffer8BitTft640480[(y)][(x)/4]=( frameBuffer8BitTft640480[(y)][x/4]
        & ~(0xff000000>>((x)%4)*8) ) | ( (c&0x000000ff)<<((4-1-((x)%4))*8) );
}


void _PutTft16Bit_640480(U32 x,U32 y,U32 c)
{
    if(x<SCR_XSIZE_TFT_640480 && y<SCR_YSIZE_TFT_640480)
        frameBuffer16BitTft640480[(y)][(x)/2]=( frameBuffer16BitTft640480[(y)][x/2]
        & ~(0xffff0000>>((x)%2)*16) ) | ( (c&0x0000ffff)<<((2-1-((x)%2))*16) );
}



void _PutTft24Bit_640480(U32 x,U32 y,U32 c)
{
    if(x<SCR_XSIZE_TFT_640480 && y<SCR_YSIZE_TFT_640480)
        frameBuffer24BitTft640480[(y)][(x)]=( frameBuffer24BitTft640480[(y)][(x)]
        & (0x0) | ( c&0xffffff00)); // | ( c&0x00ffffff)); LSB 
}



void _PutTft1Bit_800600(U32 x,U32 y,U32 c)
{
    if(x<SCR_XSIZE_TFT_800600 && y<SCR_YSIZE_TFT_800600)
        frameBuffer1BitTft800600[(y)][(x)/32]=( frameBuffer1BitTft800600[(y)][x/32]
	& ~(0x80000000>>((x)%32)*1) ) | ( (c&0x00000001)<< ((32-1-((x)%32))*1) );
}


void _PutTft8Bit_800600(U32 x,U32 y,U32 c)
{
    if(x<SCR_XSIZE_TFT_800600 && y<SCR_YSIZE_TFT_800600)
        frameBuffer8BitTft800600[(y)][(x)/4]=( frameBuffer8BitTft800600[(y)][x/4]
        & ~(0xff000000>>((x)%4)*8) ) | ( (c&0x000000ff)<<((4-1-((x)%4))*8) );
}


void _PutTft16Bit_800600(U32 x,U32 y,U32 c)
{
    if(x<SCR_XSIZE_TFT_800600 && y<SCR_YSIZE_TFT_800600)
        frameBuffer16BitTft800600[(y)][(x)/2]=( frameBuffer16BitTft800600[(y)][x/2]
        & ~(0xffff0000>>((x)%2)*16) ) | ( (c&0x0000ffff)<<((2-1-((x)%2))*16) );
}


void Glib_Rectangle(int x1,int y1,int x2,int y2,int color)
{
    Glib_Line(x1,y1,x2,y1,color);
    Glib_Line(x2,y1,x2,y2,color);
    Glib_Line(x1,y2,x2,y2,color);
    Glib_Line(x1,y1,x1,y2,color);
}



void Glib_FilledRectangle(int x1,int y1,int x2,int y2,int color)
{
    int i;

    for(i=y1;i<=y2;i++)
	Glib_Line(x1,i,x2,i,color);
}



// LCD display is flipped vertically
// But, think the algorithm by mathematics point.
//   3I2
//   4 I 1
//  --+--   <-8 octants  mathematical cordinate
//   5 I 8
//   6I7
void Glib_Line(int x1,int y1,int x2,int y2,int color)
{
	int dx,dy,e;
	dx=x2-x1; 
	dy=y2-y1;
    
	if(dx>=0)
	{
		if(dy >= 0) // dy>=0
		{
			if(dx>=dy) // 1/8 octant
			{
				e=dy-dx/2;
				while(x1<=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1+=1;e-=dx;}	
					x1+=1;
					e+=dy;
				}
			}
			else		// 2/8 octant
			{
				e=dx-dy/2;
				while(y1<=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1+=1;e-=dy;}	
					y1+=1;
					e+=dx;
				}
			}
		}
		else		   // dy<0
		{
			dy=-dy;   // dy=abs(dy)

			if(dx>=dy) // 8/8 octant
			{
				e=dy-dx/2;
				while(x1<=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1-=1;e-=dx;}	
					x1+=1;
					e+=dy;
				}
			}
			else		// 7/8 octant
			{
				e=dx-dy/2;
				while(y1>=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1+=1;e-=dy;}	
					y1-=1;
					e+=dx;
				}
			}
		}	
	}
	else //dx<0
	{
		dx=-dx;		//dx=abs(dx)
		if(dy >= 0) // dy>=0
		{
			if(dx>=dy) // 4/8 octant
			{
				e=dy-dx/2;
				while(x1>=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1+=1;e-=dx;}	
					x1-=1;
					e+=dy;
				}
			}
			else		// 3/8 octant
			{
				e=dx-dy/2;
				while(y1<=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1-=1;e-=dy;}	
					y1+=1;
					e+=dx;
				}
			}
		}
		else		   // dy<0
		{
			dy=-dy;   // dy=abs(dy)

			if(dx>=dy) // 5/8 octant
			{
				e=dy-dx/2;
				while(x1>=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1-=1;e-=dx;}	
					x1-=1;
					e+=dy;
				}
			}
			else		// 6/8 octant
			{
				e=dx-dy/2;
				while(y1>=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1-=1;e-=dy;}	
					y1-=1;
					e+=dx;
				}
			}
		}	
	}
}



void Glib_ClearScr(U32 c, int type)
{	
    //Very inefficient function.
    int i,j;
    //if((type==MODE_TFT_1BIT_800600)|(type==MODE_TFT_8BIT_800600)|(type==MODE_TFT_16BIT_800600))
    if((type&0x4000)&&(type&0x400))
	for(j=0;j<SCR_YSIZE_TFT_800600;j++)
            for(i=0;i<SCR_XSIZE_TFT_800600;i++)
		        PutPixel(i,j,c);
    //else if((type==MODE_TFT_1BIT_640480)|(type==MODE_TFT_8BIT_640480)|(type==MODE_TFT_16BIT_640480))
    else if((type&0x4000)&&(type&0x200))
	for(j=0;j<SCR_YSIZE_TFT_640480;j++)
            for(i=0;i<SCR_XSIZE_TFT_640480;i++)
		        PutPixel(i,j,c);
    //else if((type==MODE_TFT_1BIT_240320)|(type==MODE_TFT_8BIT_240320)|(type==MODE_TFT_16BIT_240320))
    else if((type&0x4000)&&(type&0x100))
	for(j=0;j<SCR_YSIZE_TFT_240320;j++)
            for(i=0;i<SCR_XSIZE_TFT_240320;i++)
		        PutPixel(i,j,c);
    else if(type&0x2000)
        for(j=0;j<SCR_YSIZE_CSTN;j++)
    	    for(i=0;i<SCR_XSIZE_CSTN;i++)
		        PutPixel(i,j,c);
    else
        for(j=0;j<SCR_YSIZE_STN;j++)
    	    for(i=0;i<SCR_XSIZE_STN;i++)
		        PutPixel(i,j,c);
}

/*****************************************************************************
// Function name	: Glib_disp_hzk16
// Description	    : 在LCD的(x,y)坐标处以colour颜色显示s中的汉字
// Return type		: void
// Argument         : int x : x坐标
// Argument         : int y : y坐标
// Argument         : char *s : 待显示字符串
// Argument         : int colour : 显示颜色
*****************************************************************************/
void Glib_disp_hzk16(int x,int y,char *s,int colour)
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
   		memcpy(buffer, &__HZK16X16__[location], 32);	/* 获取汉字字模				*/
		for(i=0;i<16;i++)						/* 每一行					*/
		{
    		for(j=0;j<2;j++)					/* 一行两个字节				*/
			{
     			for(k=0;k<8;k++)				/* 每个字节按位显示			*/
				{
      				if(((buffer[i*2+j]>>(7-k)) & 0x1) != 0)
       					PutPixel(x+8*(j)+k,y+i,colour); /* 显示一位	*/
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
// Argument         : char *s : 待显示字符串
// Argument         : int colour : 显示颜色
*****************************************************************************/
void Glib_disp_ascii16x8(int x,int y,char *s,int colour)
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
   		memcpy(buffer, &__ASCII8X16__[location], 32);	/* 获取汉字字模				*/
		for(i=0;i<16;i++)						/* 每一行					*/
		{
    		for(j=0;j<1;j++)					/* 一行两个字节				*/
			{
     			for(k=0;k<8;k++)				/* 每个字节按位显示			*/
				{
      				if(((buffer[i*2+j]>>(7-k)) & 0x1) != 0)
       					PutPixel(x+8*(j)+k,y+i,colour); /* 显示一位	*/
				}
			}
		}
   		s+=1;												/* 下一个汉字	*/
   		x+=8;												/* 字符间距		*/
  	}
}
