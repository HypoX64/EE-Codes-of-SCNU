#include <string.h>
#include "2410addr.h"
#include "2410lib.h"
#include "def.h"
#include "lcdlib.h"
#include "glib.h"
#include "lcd.h"

void Lcd_Port_Init(void);
void Lcd_Port_Return(void);
void Lcd_Palette1Bit_Init(void);
void Lcd_Palette8Bit_Init(void);
void Lcd_Int_Frame() __attribute__ ((interrupt("IRQ")));
void Lcd_Int_Fifo() __attribute__ ((interrupt("IRQ")));
void Lcd_Int_Fifo_640480() __attribute__ ((interrupt("IRQ")));

unsigned save_rGPCUP,save_rGPCDAT,save_rGPCCON;
unsigned save_rGPDUP,save_rGPDDAT,save_rGPDCON; 
unsigned lcd_count;

static const unsigned short STN256pal[]={
	0x0b5e,0xce9a,0xffd9,0x9d99,0xb63a,0xae7c,0xdd71,0x6c57,0xfd4d,0x00ae,0x9c4d,0xb5f8,0xad96,0x0131,0x0176,0xefff,0xcedd,0x9556,0xe4bf,0x00b6,0x22b7,0x002b,0x89de,0x002c,0x57df,0xab5f,0x3031,0x14bf,0x797e,0x5391,0x93ab,0x7239,0x7453,0xafdf,0x71b9,0x8c92,0x014d,0x302e,0x5175,0x0029,0x0969,0x004e,0x2a6d,0x0021,0x3155,0x4b6e,0xd677,0xf6b6,0x9b5f,0x4bb5,0xffd5,0x0027,0xdfdf,0x74d8,0x1256,0x6bcd,0x9b08,0x2ab2,0xbd72,0x84b5,0xfe52,0xd4ad,0x00ad,0xfffc,0x422b,0x73b0,0x0024,0x5246,0x8e5e,0x28b3,0x0050,0x3b52,0x2a4a,0x3a74,0x8559,0x3356,0x1251,0x9abf,0x4034,0x40b1,
	0x8cb9,0x00b3,0x5c55,0xdf3d,0x61b7,0x1f5f,0x00d9,0x4c59,0x0926,0xac3f,0x925f,0x85bc,0x29d2,0xc73f,0xef5c,0xcb9f,0x827b,0x5279,0x4af5,0x01b9,0x4290,0xf718,0x126d,0x21a6,0x515e,0xefbd,0xd75e,0x42ab,0x00aa,0x10b3,0x7349,0x63b5,0x61a3,0xaadf,0xcb27,0x87df,0x6359,0xc7df,0x4876,0xb5bc,0x4114,0xfe2e,0xef5e,0x65be,0x43b9,0xe5df,0x21c9,0x7d16,0x6abb,0x5c11,0x49f7,0xbc0b,0x9e1a,0x3b0f,0x202b,0xff12,0x821b,0x842f,0xbccf,0xdefb,0x8a3e,0x68fa,0xa4f1,0x38ae,0x28b7,0x21ad,0x31d7,0x0073,0x182b,0x1831,0x3415,0xbdf6,0x2dbf,0x0a5d,0xc73d,0x182c,0x293e,0x7b3d,0x643d,0x3cbd,
	0x92dd,0x09d4,0x1029,0x7cdd,0x6239,0x182e,0x5aea,0x11eb,0x8abc,0x7bfa,0x00a7,0x2153,0x1853,0x1318,0x0109,0x54fa,0x72a7,0x89e3,0x01cf,0x3a07,0x7b17,0x1a14,0x2150,0x23dc,0x4142,0x1b33,0x00a4,0xf6df,0x08fc,0x18ae,0x3a7e,0x18d1,0xa51c,0xff5a,0x1a0f,0x28fa,0xdfbe,0x82de,0x60d7,0x1027,0x48fa,0x5150,0x6213,0x89d6,0x110d,0x9bbb,0xbedd,0x28e1,0x1925,0xf449,0xaa79,0xd5f4,0x693c,0x110a,0x2889,0x08a2,0x923d,0x10a6,0xd9bc,0x5b2e,0x32ec,0xcf7f,0x1025,0x2148,0x74b4,0x6d59,0x9d14,0x0132,0x00f0,0x56bf,0x00f1,0xffff,0x0173,0x0133,0x00b0,0x00b1,0xf7ff,0x08b1,0xfffe,0x08b0,
	0x0171,0xf7bf,0x10f3,0xf7fe,0x08ef,0x1192,0xefbe,0x1131,0x2177,0xff9f,0x1116,0xffbc,0x5914,0x22ef,0xb285,0xa6df,
};

void Lcd_Port_Init(void)
{
    save_rGPCCON=rGPCCON;
    save_rGPCDAT=rGPCDAT;
    save_rGPCUP=rGPCUP;
    save_rGPDCON=rGPDCON;
    save_rGPDDAT=rGPDDAT;
    save_rGPDUP=rGPDUP;
    rGPCUP=0xffffffff; // Disable Pull-up register
    rGPCCON=0xaaaaaaaa; //Initialize VD[7:0],LCDVF[2:0],VM,VFRAME,VLINE,VCLK,LEND 
    rGPDUP=0xffffffff; // Disable Pull-up register
    rGPDCON=0xaaaaaaaa; //Initialize VD[23:8]
}

void Lcd_Port_Return(void)
{
    rGPCCON=save_rGPCCON;
    rGPCDAT=save_rGPCDAT;
    rGPCUP=save_rGPCUP;
    rGPDCON=save_rGPDCON;
    rGPDDAT=save_rGPDDAT;
    rGPDUP=save_rGPDUP;
}

void Lcd_Palette1Bit_Init(void)
{
    U32 *palette;
    palette=(U32 *)PALETTE;
    *palette++=0x0; // Black
    *palette=0xffff; // White
}

void Lcd_Palette8Bit_Init(void)
{
    int i;	
    U32 *palette;
    rLCDCON5|=(1<<11); // 5:6:5 Palette Setting
    palette=(U32 *)PALETTE;
    for(i=0;i<256;i++)
	*palette++=STN256pal[i];
}


void Lcd_Int_Frame(void)
{
    rLCDINTMSK|=3; // Mask LCD SUB Interrupt

    // GPG4 is .... 
    rGPGDAT&=(~(1<<4)); // GPG4=Low
    Delay(50); // GPG4=Low
    rGPGDAT|=(1<<4); //GPG4=High

    rLCDSRCPND=2; // Clear LCD SUB Interrupt source pending
    rLCDINTPND=2; // Clear LCD SUB Interrupt pending
    rLCDINTMSK&=(~(2)); // Unmask LCD FRAME Interrupt
    ClearPending(BIT_LCD);
}


//240320
void Lcd_Int_Fifo(void)
{
    rLCDINTMSK|=3; // Mask LCD SUB Interrupt

    if((lcd_count%20)==0) PRINTF("\n");
    PRINTF(".");
    lcd_count++;

    rLCDSRCPND=1; // Clear LCD SUB Interrupt source pending
    rLCDINTPND=1; // Clear LCD SUB Interrupt pending
    rLCDINTMSK&=(~(1)); // Unmask LCD FRAME Interrupt
    ClearPending(BIT_LCD);
}

void Test_Lcd_Stn_1Bit(void)
{
    int i,j;
    Lcd_Port_Init();
    Lcd_Init(MODE_STN_1BIT);
    Glib_Init(MODE_STN_1BIT);
    Lcd_EnvidOnOff(1); // Enable ENVID Bit
    PRINTF("[STN Mono(1bit/1pixel) LCD Test]\n");              

    Glib_ClearScr(0, MODE_STN_1BIT);
    for(j=0;j<LCD_YSIZE_STN;j+=16)
		for(i=0;i<LCD_XSIZE_STN;i+=16)
		    Glib_FilledRectangle(i,j,i+15,j+15,((j+i)/16)%2);
    PRINTF("STN Mono test 1. Press any key!\n");
    Uart_Getch();  	

    Glib_ClearScr(0, MODE_STN_1BIT);
    Glib_FilledRectangle(160,0,319,239,1);    //Half Screen
    PRINTF("STN Mono test 2. Press any key!\n");
    Uart_Getch();  	

    Glib_ClearScr(0, MODE_STN_1BIT); 
    Glib_Rectangle(0,0,319,239,1);   // #0
    Glib_Line(0,0,319,239,1);        // 00
    Glib_Line(0,239,319,0,1);

    Glib_Rectangle(0+320,0,319+320,239,1);   // 0#
    Glib_Line(0+320,0,319+320,239,1);        // 00
    Glib_Line(0+320,239,319+320,0,1);
    Glib_FilledRectangle(50+320,50,269+320,189,1);

    Glib_Rectangle(0,0+240,319,239+240,1);   // 00
    Glib_Line(0,0+240,319,239+240,1);        // #0
    Glib_Line(0,239+240,319,0+240,1);
    Glib_FilledRectangle(50,50+240,269,189+240,1);
    
    Glib_Rectangle(0+320,0+240,319+320,239+240,1);   // 00	
    Glib_Line(0+320,0+240,319+320,239+240,1);        // 0#
    Glib_Line(0+320,239+240,319+320,0+240,1);
    Glib_Rectangle(50+320,50+240,269+320,189+240,1);

    PRINTF("Virtual Screen Test(STN Mono). Press any key[ijkm\\r]!\n");
    MoveViewPort(MODE_STN_1BIT);
    Lcd_MoveViewPort(0,0,MODE_STN_1BIT);
    Lcd_EnvidOnOff(0); // Disable ENVID Bit
    Lcd_Port_Return();
}


void Test_Lcd_Stn_2Bit(void)
{
    int i,j,k;
    Lcd_Port_Init();
    Lcd_Init(MODE_STN_2BIT);
    Glib_Init(MODE_STN_2BIT);
    Lcd_EnvidOnOff(1); // Enable ENVID Bit
    PRINTF("[STN 4 gray(2bit/1pixel) LCD Test]\n");

    Glib_ClearScr(0, MODE_STN_2BIT);
    j=0;
    for(i=0;i<320;i+=80)
        Glib_FilledRectangle(0+i,0,79+i,239,j++);
    PRINTF("4 gray mode test 1. Press any key!\n");
    Uart_Getch();  	

    Glib_ClearScr(0, MODE_STN_2BIT);
    j=0;
    for(i=0;i<320;i+=80)
    {
    	Glib_FilledRectangle(0+i,0,79+i,119,j);
    	Glib_FilledRectangle(0+i,120,79+i,239,3-j);
    	j++;
    }
    PRINTF("4 gray mode test 2. Press any key!\n");
    Uart_Getch();  	

    Glib_ClearScr(0, MODE_STN_2BIT);
    j=0;
    for(i=0;i<240;i+=60)
    {
    	Glib_FilledRectangle(i,i,i+59,i+59,j);
    	j++;
    }
    PRINTF("4 gray mode test 3. Press any key!\n");
    Uart_Getch();  	

    Glib_ClearScr(0, MODE_STN_2BIT);
    k=0;
    for(i=160;i<480;i+=80)
    {
    	for(j=120;j<360;j+=60)
    	{
    	    Glib_FilledRectangle(i,j,i+79,j+59,k%4);
    	    k++;
    	}
    	k+=2;;
    }

    // #0
    // 00
    Glib_Rectangle(0,0,319,239,3);   
    Glib_Line(0,0,319,239,3);        
    Glib_Line(0,239,319,0,3);

    // 0#
    // 00
    Glib_Rectangle(0+320,0,319+320,239,3);          
    Glib_Line(0+320,0,319+320,239,3);        
    Glib_Line(0+320,239,319+320,0,3);

    // 00
    // #0
    Glib_Rectangle(0,0+240,319,239+240,3);          
    Glib_Line(0,0+240,319,239+240,3);        
    Glib_Line(0,239+240,319,0+240,3);

    // 00
    // 0#
    Glib_Line(0+320,0+240,319+320,239+240,3);        
    Glib_Line(0+320,239+240,319+320,0+240,3);
    Glib_Rectangle(50+320,50+240,269+320,189+240,3);

    PRINTF("Virtual Screen Test(STN 4 gray). Press any key[ijkm\\r]!\n");
    MoveViewPort(MODE_STN_2BIT);
    Lcd_MoveViewPort(0,0,MODE_STN_2BIT);
    Lcd_EnvidOnOff(0); // Disable ENVID Bit
    Lcd_Port_Return();
}


void Test_Lcd_Stn_4Bit(void)
{
    int i,j,k;
    Lcd_Port_Init();
    Lcd_Init(MODE_STN_4BIT);
    Glib_Init(MODE_STN_4BIT);
    Lcd_EnvidOnOff(1);
    PRINTF("[STN 16 gray(4bit/1pixel) LCD Test]\n");

    Glib_ClearScr(0, MODE_STN_4BIT);
    j=0;
    for(i=0;i<320;i+=20)
        Glib_FilledRectangle(0+i,0,19+i,239,j++);
    PRINTF("16 gray mode test 1. Press any key!\n");
    Uart_Getch();  	

    Glib_ClearScr(0, MODE_STN_4BIT);
    j=0;
    for(i=0;i<320;i+=20)
    {
    	Glib_FilledRectangle(0+i,0,19+i,119,j);
    	Glib_FilledRectangle(0+i,120,19+i,239,15-j);
    	j++;
    }
    PRINTF("16 gray mode test 2. Press any key!\n");
    Uart_Getch();  	


    Glib_ClearScr(0, MODE_STN_4BIT);
    j=0;
    for(i=0;i<240;i+=30)
    {
    	Glib_FilledRectangle(i,i,i+29,i+29,j);
    	Glib_FilledRectangle(i+110,i,i+29+110,i+29,j+8);
    	j++;
    }
    PRINTF("4 gray mode test 3. Press any key!\n");
    Uart_Getch();  	 


    Glib_ClearScr(0, MODE_STN_4BIT);
    k=0;
    for(i=160;i<480;i+=40)
    	for(j=120;j<360;j+=30)
    	{
    	    Glib_FilledRectangle(i,j,i+39,j+29,k%16);
    	    k++;
    	}
    		    
    // #0		    
    // 00		    
    Glib_Rectangle(0,0,319,239,15);   
    Glib_Line(0,0,319,239,15);        
    Glib_Line(0,239,319,0,15);

    // 0#
    // 00
    Glib_Rectangle(0+320,0,319+320,239,15);
    Glib_Line(0+320,0,319+320,239,15);        
    Glib_Line(0+320,239,319+320,0,15);

    // 00
    // #0
    Glib_Rectangle(0,0+240,319,239+240,15);
    Glib_Line(0,0+240,319,239+240,15);        
    Glib_Line(0,239+240,319,0+240,15);

    // 00
    // 0#
    Glib_Rectangle(0+320,0+240,319+320,239+240,15);
    Glib_Line(0+320,0+240,319+320,239+240,15);     
    Glib_Line(0+320,239+240,319+320,0+240,15);
    Glib_Rectangle(50+320,50+240,269+320,189+240,15);

    PRINTF("Virtual Screen Test(STN 16 gray). Press any key[ijkm\\r]!\n");
    MoveViewPort(MODE_STN_4BIT);
    Lcd_MoveViewPort(0,0,MODE_STN_4BIT);
    Lcd_EnvidOnOff(0);
    Lcd_Port_Return();
}


void Test_Lcd_Cstn_8Bit(void)
{
    int i,j,k;
    Lcd_Port_Init();
    Lcd_Init(MODE_CSTN_8BIT);
    Glib_Init(MODE_CSTN_8BIT);
    Lcd_CstnOnOff(1); // Enable ENVID Bit and GPB5 output
    PRINTF("[CSTN 256 COLOR(8bit/1pixel) LCD TEST]\n");
    PRINTF("     R:0   ...    7 \n");
    PRINTF("G:0  B0:1 B0:1 B0:1 \n");
    PRINTF("G:.   2:3  2:3  2:3 \n");
    PRINTF("G:.  B0:1 B0:1 B0:1 \n");
    PRINTF("G:.   2:3  2:3  2:3 \n");
    PRINTF("G:.  B0:1 B0:1 B0:1 \n");
    PRINTF("G:7   2:3  2:3  2:3 \n");

    
    Glib_ClearScr(0, MODE_CSTN_8BIT);
    for(j=0;j<240;j++)
		for(i=0;i<320;i++) //RRRGGGBB
		    PutPixel(i,j,((i/40)<<5)+((j/30)<<2)+(((j/15)%2)<<1)+((i/20)%2));
    PRINTF("CSTN 256 color mode test 1. Press any key!\n");
    Uart_Getch();  	
  
    Glib_ClearScr(0, MODE_CSTN_8BIT);
    k=0;
    for(i=160;i<480;i+=20)
    	for(j=120;j<360;j+=15)
    	{
    	    Glib_FilledRectangle(i,j,i+19,j+14,k);
    	    k++;
    	}

    // #0		    
    // 00		    
    Glib_Rectangle(0,0,319,239,255);   
    Glib_Line(0,0,319,239,255);        
    Glib_Line(0,239,319,0,255);

    // 0#
    // 00
    Glib_Rectangle(0+320,0,319+320,239,255);
    Glib_Line(0+320,0,319+320,239,255);        
    Glib_Line(0+320,239,319+320,0,255);

    // 00
    // #0
    Glib_Rectangle(0,0+240,319,239+240,255);
    Glib_Line(0,0+240,319,239+240,255);        
    Glib_Line(0,239+240,319,0+240,255);

    // 00
    // 0#
    Glib_Rectangle(0+320,0+240,319+320,239+240,255);
    Glib_Line(0+320,0+240,319+320,239+240,255);     
    Glib_Line(0+320,239+240,319+320,0+240,255);
    Glib_Rectangle(50+320,50+240,269+320,189+240,255);

    PRINTF("Virtual Screen Test(CSTN 256 color). Press any key[ijkm\\r]!\n");
    MoveViewPort(MODE_CSTN_8BIT);
    Lcd_MoveViewPort(0,0,MODE_CSTN_8BIT);
    Lcd_CstnOnOff(0); // Disable ENVID Bit and GPB5 output
    Lcd_Port_Return();
}


void Test_Lcd_Cstn_8Bit_On(void)
{
    int i,j;
    Lcd_Port_Init();
    Lcd_Init(MODE_CSTN_8BIT);
    Glib_Init(MODE_CSTN_8BIT);
    Lcd_CstnOnOff(1); // Enable ENVID Bit and GPB5 output
    for(j=0;j<240;j++)
	for(i=0;i<320;i++)	//RRRGGGBB
	    PutPixel(i,j,((i/40)<<5)+((j/30)<<2)+(((j/15)%2)<<1)+((i/20)%2));
}


void Test_Lcd_Cstn_12Bit(void)
{
    int i,j,k;
    Lcd_Port_Init();
    Lcd_Init(MODE_CSTN_12BIT);
    Glib_Init(MODE_CSTN_12BIT);
    Lcd_CstnOnOff(1); // Enable ENVID Bit and GPB5 output
    PRINTF("[CSTN 4K COLOR(12bit/1pixel) LCD TEST]\n");
    PRINTF("R:0 ...    16\n");
    PRINTF("G:0 ...    16\n");
    PRINTF("B:0 ...    16\n");
 
    Glib_ClearScr(0, MODE_CSTN_12BIT);
    k=0;
    for(j=0;j<240;j+=80)
        for(i=0;i<320;i+=20)
		{   
	 	   if((k<16)|(k>31))
		    {
		        Glib_FilledRectangle(i,j,i+19,j+79,((k%16)<<(4*(k/16))));
		        k++;
		    }
		    else
		    {
		        Glib_FilledRectangle(i,j,i+19,j+79,((k-(1+2*(k%16)))<<(4*(k/16))));
		        k++;
		    }
		}
    PRINTF("CSTN 4K color mode test 1. Press any key!\n");
    Uart_Getch();  	

    Glib_ClearScr(0, MODE_CSTN_12BIT);
    for(j=0;j<240;j++)
		for(i=0;i<320;i++)
		    PutPixel(i,j,((i/40)<<9)+((j/30)<<5)+(((j/15)%2)<<1)+((i/20)%2));
    PRINTF("CSTN 4K color mode test 2. Press any key!\n");
    Uart_Getch();  	

    Glib_ClearScr(0, MODE_CSTN_12BIT);
    k=0;
    for(i=160;i<480;i+=20)
    	for(j=120;j<360;j+=15)
    	{
    	    Glib_FilledRectangle(i,j,i+19,j+14,(((k&0xf)<<8)|((k%4)<<4)|(k&0xf0)) );
    	    k++;
    	}

    // #0		    
    // 00		    
    Glib_Rectangle(0,0,319,239,0xf00);   
    Glib_Line(0,0,319,239,0x0f0);        
    Glib_Line(0,239,319,0,0x00f);
    // 0#
    // 00
    Glib_Rectangle(0+320,0,319+320,239,0xfff);
    Glib_Line(0+320,0,319+320,239,0xfff);        
    Glib_Line(0+320,239,319+320,0,0xfff);
    // 00
    // #0
    Glib_Rectangle(0,0+240,319,239+240,0xfff);
    Glib_Line(0,0+240,319,239+240,0xfff);        
    Glib_Line(0,239+240,319,0+240,0xfff);
    // 00
    // 0#
    Glib_Rectangle(0+320,0+240,319+320,239+240,0xfff);
    Glib_Line(0+320,0+240,319+320,239+240,0xfff);     
    Glib_Line(0+320,239+240,319+320,0+240,0xfff);
    Glib_Rectangle(50+320,50+240,269+320,189+240,0xfff);

    PRINTF("Virtual Screen Test(CSTN 4K color). Press any key[ijkm\\r]!\n");
    MoveViewPort(MODE_CSTN_12BIT);
    Lcd_MoveViewPort(0,0,MODE_CSTN_12BIT);
    Lcd_CstnOnOff(0); // Disable ENVID Bit and GPB5 output
    Lcd_Port_Return();
}


void Test_Lcd_Tft_8Bit_240320(void)
{
    int i,j,k;
    Lcd_Port_Init();
    Lcd_Palette8Bit_Init(); // Initialize 256 palette 
    Lcd_Init(MODE_TFT_8BIT_240320);
    Glib_Init(MODE_TFT_8BIT_240320);
    Lcd_Lpc3600Enable(); // Enable LPC3600
    Lcd_PowerEnable(0, 1);
    PRINTF("[TFT 256 COLOR(8bit/1pixel) LCD TEST]\n");
    rTPAL = (1<<24)|((0xff)<<16); // Enable Temporary Palette : Red
    Lcd_EnvidOnOff(1); // Enable ENVID Bit
    PRINTF("TFT 256 color mode test 1. Press any key!\n");
    Uart_Getch(); 

    Glib_ClearScr(0, MODE_TFT_8BIT_240320); // Fill the LCD panel with Black Color
    k=0;
    for(i=0;i<320;i+=20)
		for(j=0;j<240;j+=15)
		{ 
		    Glib_FilledRectangle(j,i,j+14,i+19,(k%256));
		    k++;
		}
    rTPAL = 0; // Disable Temporary Palette
    PRINTF("TFT 256 color mode test 2. Press any key!\n");
    Uart_Getch();  	

    Glib_ClearScr(0, MODE_TFT_8BIT_240320); // Fill the LCD panel with Black Color
    k=0;
    for(i=0;i<320;i+=10)
		for(j=0;j<240;j+=10)
		{ 
		    Glib_FilledRectangle(j,i,j+9,i+9,(k%256));
		    k+=30;
		}
    PRINTF("TFT 256 color mode test 3. Press any key!\n");
    Uart_Getch();  	

    Glib_ClearScr(0, MODE_TFT_8BIT_240320);
    k=0;
    for(i=80;i<240;i+=10)
    {
    	for(j=60;j<180;j+=10)
    	{
    	    Glib_FilledRectangle(j,i,j+9,i+9,k);
    	    k++;
    	}
    }
    Glib_Rectangle(0,0,239,319,255);   
    Glib_Line(0,0,239,319,255);        
    Glib_Line(0,319,239,0,255);
    
    Glib_Rectangle(0+240,0,239+240,319,255);
    Glib_Line(0+240,0,239+240,319,255);        
    Glib_Line(0+240,319,239+240,0,255);
    
    Glib_Rectangle(0,0+320,239,319+320,255);
    Glib_Line(0,0+320,239,319+320,255);        
    Glib_Line(0,319+320,239,0+320,255);
    
    Glib_Rectangle(0+240,0+320,239+240,319+320,255);
    Glib_Line(0+240,0+320,239+240,319+320,255);     
    Glib_Line(0+240,319+320,239+240,0+320,255);

    Glib_Rectangle(10+240,10+320,480-11,640-11,255);

    PRINTF("Virtual Screen Test(TFT 256 color). Press any key[ijkm\\r]!\n");
    MoveViewPort(MODE_TFT_8BIT_240320);
    Lcd_MoveViewPort(0,0,MODE_TFT_8BIT_240320);
    Lcd_EnvidOnOff(0);
    Lcd_Port_Return();
}


void Test_Lcd_Tft_16Bit_240320(void)
{
    int i,j,k;
    Lcd_Port_Init();
    Lcd_Init(MODE_TFT_16BIT_240320);
    Glib_Init(MODE_TFT_16BIT_240320);
    Lcd_Lpc3600Enable(); // Enable LPC3600
    Lcd_PowerEnable(0, 1);
    Lcd_EnvidOnOff(1);
    PRINTF("[TFT 64K COLOR(16bit/1pixel) LCD TEST]\n");

    Glib_ClearScr(0, MODE_TFT_16BIT_240320);
    Glib_FilledRectangle(0,0,239,159,0xf800);    
    Glib_FilledRectangle(0,160,239,320,0xf800);    
    PRINTF("TFT 64K color mode test 1. Press any key!\n");
    Uart_Getch();  	
    

    Glib_ClearScr(0, MODE_TFT_16BIT_240320);
    Glib_Rectangle(0,0,239,319,0x07e0);   
    Glib_FilledRectangle(0,0,20,20,65535);   
    Glib_Rectangle(220,300,239,319,65535);   
    Glib_Line(0,0,239,319,0x1f);        
    Glib_Line(239,0,0,319,0xf800);
    PRINTF("TFT 64K color mode test 2. Press any key!\n");
    Uart_Getch();  	

    Glib_ClearScr(0, MODE_TFT_16BIT_240320);
    k=0;
    for(i=80;i<240;i+=10)
    {
    	for(j=60;j<180;j+=10)
    	{
    	    Glib_FilledRectangle(j,i,j+9,i+9,k);
    	    k++;
    	}
    }

    Glib_Rectangle(0,0,239,319,65535);   
    Glib_Line(0,0,239,319,65535);        
    Glib_Line(0,319,239,0,65535);
    
    Glib_Rectangle(0+240,0,239+240,319,255);
    Glib_Line(0+240,0,239+240,319,255);        
    Glib_Line(0+240,319,239+240,0,255);
    
    Glib_Rectangle(0,0+320,239,319+320,255);
    Glib_Line(0,0+320,239,319+320,255);        
    Glib_Line(0,319+320,239,0+320,255);
    
    Glib_Rectangle(0+240,0+320,239+240,319+320,255);
    Glib_Line(0+240,0+320,239+240,319+320,255);     
    Glib_Line(0+240,319+320,239+240,0+320,255);
    Glib_Rectangle(40+240,40+320,480-41,640-41,0x1f);

    PRINTF("Virtual Screen Test(TFT 64K color). Press any key[ijkm\\r]!\n");
    MoveViewPort(MODE_TFT_16BIT_240320);
    Lcd_MoveViewPort(0,0,MODE_TFT_16BIT_240320);
    Lcd_EnvidOnOff(0);
    Lcd_Port_Return();
}


void Test_Lcd_Tft_8Bit_240320_On(void)
{
    int i,j,k=0;
    Lcd_Port_Init();
    Lcd_Palette8Bit_Init();
    Lcd_Init(MODE_TFT_8BIT_240320);
    Glib_Init(MODE_TFT_8BIT_240320);
    Lcd_Lpc3600Enable(); // Enable LPC3600
    Lcd_PowerEnable(0, 1);    
    PRINTF("[TFT LCD(240x320 ,8bpp) WILL BE TURNED ON EVEN DURING OTHER TEST]\n");
    PRINTF("If you'd like to off the TFT LCD, then excute other LCD test program,\n");     

//    for(j=0;j<320;j++)
//        for(i=0;i<240;i++)
//            PutPixel(i,j,((int)DEMO256[k++]));
            
    Lcd_EnvidOnOff(1);
}


void Test_Lcd_Tft_8Bit_240320_Bmp(void)
{
    int i,j,k=0;
    Lcd_Port_Init();
    Lcd_Palette8Bit_Init();
    Lcd_Init(MODE_TFT_8BIT_240320);
    Glib_Init(MODE_TFT_8BIT_240320);
    Lcd_Lpc3600Enable(); // Enable LPC3600
    Lcd_PowerEnable(0, 1);    
    //Lcd_PowerEnable(0, 1); // Enable LCD_PWREN

//    for(j=0;j<320;j++)
//        for(i=0;i<240;i++)
//            PutPixel(i,j,((int)DEMO256[k++]));

    Lcd_EnvidOnOff(1); // Enable ENVID    
/*
    PRINTF("Do you want to change palette(5:5:1->5:6:5)..........\n");        
    PRINTF("then press any key\n");        
    Uart_Getch();
    Lcd_EnvidOnOff(0);
    PRINTF("One more ,please...\n");
    Uart_Getch();    
    Lcd_EnvidOnOff(1);
    rLCDCON5|=(1<<11); // 5:6:5 Palette Setting
*/
    PRINTF("Press any key to quit!\n");        
    Uart_Getch();
    Glib_ClearScr(0, MODE_TFT_8BIT_240320);
    Delay(5000);
    Lcd_EnvidOnOff(0);
    Lcd_Port_Return();
}


void Test_Lcd_Tft_8Bit_240320_IntFr(void)
{
    int i,j,k=0;
    Lcd_Port_Init();
    Lcd_Palette8Bit_Init();
    Lcd_Init(MODE_TFT_8BIT_240320);
    Glib_Init(MODE_TFT_8BIT_240320);
    Lcd_Lpc3600Enable(); // Enable LPC3600
    Lcd_PowerEnable(0, 1);    
    rLCDCON5|=(1<<11); // 5:6:5 Palette Setting
    
//    for(j=0;j<320;j++)
//        for(i=0;i<240;i++)
//            PutPixel(i,j,((int)DEMO256[k++]));

    //--------LCD frame interrupt test---------------------------------------------------START
    //The content of GPG4 is changed to OUTPUT('01'). 
    //We will check the frame interrupt with using Logic Analyzer. 
    rGPGUP=rGPGUP&(~(1<<4))|(1<<4); // Pull-up disable
    rGPGDAT=rGPGDAT&(~(1<<4))|(1<<4); // GPG4=High
    rGPGCON=rGPGCON&(~(3<<8))|(1<<8); // GPG4=Output
   
    pISR_LCD=(unsigned)Lcd_Int_Frame;
    rINTMSK=~(BIT_LCD);
    rLCDINTMSK=(1<<2)|(0<<1)|(1); // 8Words Trigger Level,Unmask Frame int,mask Fifo int
    //--------LCD frame interrupt test-----------------------------------------------------END
 
    Lcd_EnvidOnOff(1); // Enable ENVID    
    PRINTF("Press any key to quit!\n");        
    Uart_Getch();
    rLCDINTMSK|=3; // Mask LCD SUB Interrupt
    rINTMSK|=(BIT_LCD); // Mask LCD INT
    Lcd_EnvidOnOff(0);
    Lcd_Port_Return();
}


void Test_Lcd_Tft_8Bit_240320_IntFi(void)
{
    int i,j,k=0;
    Lcd_Port_Init();
    Lcd_Palette8Bit_Init();
    Lcd_Init(MODE_TFT_8BIT_240320);
    Glib_Init(MODE_TFT_8BIT_240320);
    Lcd_Lpc3600Enable(); // Enable LPC3600
    Lcd_PowerEnable(0, 1);    
    rLCDCON5|=(1<<11); // 5:6:5 Palette Setting
    
//    for(j=0;j<320;j++)
//        for(i=0;i<240;i++)
//            PutPixel(i,j,((int)DEMO256[k++]));

    Lcd_EnvidOnOff(1); // Enable ENVID    
    //--------LCD FIFO interrupt test---------------------------------------------------START
    pISR_LCD=(unsigned)Lcd_Int_Fifo;
    rINTMSK=~(BIT_LCD);
    rLCDINTMSK=(0<<2)|(1<<1)|(0); // 4Words Trigger Level,Mask Frame int,Unmask Fifo int
    //--------LCD FIFO interrupt test-----------------------------------------------------END
 
    PRINTF("Press any key to quit!\n");        
    Uart_Getch();
    rLCDINTMSK|=3; // Mask LCD SUB Interrupt
    rINTMSK|=(BIT_LCD); // Mask LCD INT
    Lcd_EnvidOnOff(0);
    Lcd_Port_Return();
}



//640480
void Lcd_Int_Fifo_640480(void)
{
    int i;
    rLCDINTMSK|=3; // Mask LCD SUB Interrupt

    // GPG4 is .... 
    rGPGDAT&=(~(1<<4)); // GPG4=Low
    for(i=0;i<1;i++); // GPG4=Low
    rGPGDAT|=(1<<4); //GPG4=High

    rLCDSRCPND=1; // Clear LCD SUB Interrupt source pending
    rLCDINTPND=1; // Clear LCD SUB Interrupt pending
    rLCDINTMSK&=(~(1)); // Unmask LCD FRAME Interrupt
    ClearPending(BIT_LCD);
}


void Test_Lcd_Tft_1Bit_640480(void)
{
    int i,j;
    Lcd_Palette1Bit_Init();
    Lcd_Port_Init();
    Lcd_Init(MODE_TFT_1BIT_640480);
    Glib_Init(MODE_TFT_1BIT_640480);
    Lcd_PowerEnable(0, 1);    
    Lcd_EnvidOnOff(1);
    PRINTF("[TFT Mono(1bit/1pixel) LCD TEST]\n");
    Glib_ClearScr(0,MODE_TFT_1BIT_640480);

    rTPAL = (1<<24)|((0xff)<<8); // Enable Temporary Palette : Green
    PRINTF("TFT Mono mode test 1. Press any key!\n");
    Uart_Getch();  	

    rTPAL = 0;
    Glib_FilledRectangle(0,0,639,239,1);
    Glib_FilledRectangle(0,239,639,479,0);   
    PRINTF("TFT Mono mode test 2. Press any key!\n");
    Uart_Getch();  	

    Glib_FilledRectangle(0,0,319,479,1);
    Glib_FilledRectangle(320,0,639,479,0);   
    PRINTF("TFT Mono mode test 3. Press any key!\n");
    Uart_Getch();  	

    for(j=0;j<LCD_YSIZE_TFT_640480;j+=20)
	for(i=320;i<640;i+=20)
	    Glib_FilledRectangle(i,j,i+19,j+19,((j+i)/20)%2);
    PRINTF("TFT Mono mode test 4. Press any key!\n");
    Uart_Getch();  	

    Glib_ClearScr(0, MODE_TFT_1BIT_640480);
    Glib_FilledRectangle(0+320,0+240,1279-320,959-240,1);
    
    // #0		    
    // 00		    
    Glib_Rectangle(0,0,639,479,1);   
    Glib_Line(0,0,639,479,1);        
    Glib_Line(0,479,639,0,1);

    // 0#
    // 00
    Glib_Rectangle(0+640,0,639+640,479,1);   
    Glib_Line(0+640,0,639+640,479,1);        
    Glib_Line(0+640,479,639+640,0,1);

    // 00
    // #0
    Glib_Rectangle(0,0+480,639,479+480,1);   
    Glib_Line(0,0+480,639,479+480,1);        
    Glib_Line(0,479+480,639,0+480,1);

    // 00
    // 0#
    Glib_Rectangle(0+640,0+480,639+640,479+480,1);   
    Glib_Line(0+640,0+480,639+640,479+480,1);        
    Glib_Line(0+640,479+480,639+640,0+480,1);
    Glib_Rectangle(50+640,50+480,639+640-50,479+480-50,1);   

    PRINTF("Virtual Screen Test(TFT 256 color). Press any key[ijkm\\r]!\n");
    MoveViewPort(MODE_TFT_1BIT_640480);
    Lcd_MoveViewPort(0,0,MODE_TFT_1BIT_640480);
    Lcd_EnvidOnOff(0);
    Lcd_Port_Return();
}



void Test_Lcd_Tft_8Bit_640480(void)
{
    int i,j,k;
    Lcd_Palette8Bit_Init();
    Lcd_Port_Init();
    Lcd_Init(MODE_TFT_8BIT_640480);
    Glib_Init(MODE_TFT_8BIT_640480);
    Lcd_PowerEnable(0, 1);
    Lcd_EnvidOnOff(1);
    PRINTF("[TFT 256 COLOR(8bit/1pixel) LCD TEST]\n");
    Glib_ClearScr(0, MODE_TFT_8BIT_640480);
    rTPAL = (1<<24)|((0xff)<<0); // Enable Temporary Palette : Blue
    PRINTF("TFT 256 color mode test 1. Press any key!\n");
    Uart_Getch();  	

    k=0;
    for(i=0;i<640;i+=40)
	for(j=0;j<480;j+=30)
	{ 
	    Glib_FilledRectangle(i,j,i+39,j+29,(k%256));
	    k++;
	}
    rTPAL = 0;
    PRINTF("TFT 256 color mode test 2. Press any key!\n");
    Uart_Getch();  	

    Glib_ClearScr(0, MODE_TFT_8BIT_640480);
    k=0;
    for(i=0;i<640;i+=20)
		for(j=0;j<480;j+=20)
		{ 
		    Glib_FilledRectangle(i,j,i+19,j+19,(k%256));
		    k+=30;
		}
    PRINTF("TFT 256 color mode test 3. Press any key!\n");
    Uart_Getch();  	

    Glib_ClearScr(0, MODE_TFT_8BIT_640480);
    k=0;
    for(i=160;i<480;i+=20)
    	for(j=120;j<360;j+=15)
    	{
    	    Glib_FilledRectangle(i,j,i+19,j+14,k);
    	    k++;
    	}

    // #0		    
    // 00		    
    Glib_Rectangle(0,0,319,239,255);   
    Glib_Line(0,0,319,239,255);        
    Glib_Line(0,239,319,0,255);

    // 0#
    // 00
    Glib_Rectangle(0+320,0,319+320,239,255);
    Glib_Line(0+320,0,319+320,239,255);        
    Glib_Line(0+320,239,319+320,0,255);

    // 00
    // #0
    Glib_Rectangle(0,0+240,319,239+240,255);
    Glib_Line(0,0+240,319,239+240,255);        
    Glib_Line(0,239+240,319,0+240,255);

    // 00
    // 0#
    Glib_Rectangle(0+320,0+240,319+320,239+240,255);
    Glib_Line(0+320,0+240,319+320,239+240,255);     
    Glib_Line(0+320,239+240,319+320,0+240,255);
    Glib_Rectangle(50+320,50+240,269+320,189+240,255);

    PRINTF("TFT 256 color mode test 4. Press any key!\n");
    Uart_Getch();  	
   
    Glib_ClearScr(0, MODE_TFT_8BIT_640480);
    k=0;
    for(i=320;i<960;i+=40)
    	for(j=240;j<720;j+=30)
    	{
    	    Glib_FilledRectangle(i,j,i+39,j+29,(k%256));
    	    k++;
    	}

    // #0		    
    // 00		    
    Glib_Rectangle(0,0,639,479,255);   
    Glib_Line(0,0,639,479,255);        
    Glib_Line(0,479,639,0,255);

    // 0#
    // 00
    Glib_Rectangle(0+640,0,639+640,479,255);   
    Glib_Line(0+640,0,639+640,479,255);        
    Glib_Line(0+640,479,639+640,0,255);

    // 00
    // #0
    Glib_Rectangle(0,0+480,639,479+480,255);   
    Glib_Line(0,0+480,639,479+480,255);        
    Glib_Line(0,479+480,639,0+480,255);

    // 00
    // 0#
    Glib_Rectangle(0+640,0+480,639+640,479+480,255);   
    Glib_Line(0+640,0+480,639+640,479+480,255);        
    Glib_Line(0+640,479+480,639+640,0+480,255);
    Glib_Rectangle(50+640,50+480,639+640-50,479+480-50,255);   

    PRINTF("Virtual Screen Test(TFT 256 color). Press any key[ijkm\\r]!\n");
    MoveViewPort(MODE_TFT_8BIT_640480);
    Lcd_MoveViewPort(0,0,MODE_TFT_8BIT_640480);
    Lcd_EnvidOnOff(0);
    Lcd_Port_Return();
}


void Test_Lcd_Tft_8Bit_640480_Palette(void)
{
    int i,j,k;
    unsigned char cdata, p_red, p_green, p_blue;
    U32 *palette;
    Lcd_Palette8Bit_Init();
    Lcd_Port_Init();
    Lcd_Init(MODE_TFT_8BIT_640480);
    Glib_Init(MODE_TFT_8BIT_640480);
    PRINTF("[TFT 256 COLOR(8bit/1pixel) Palette TEST]\n");
    Glib_ClearScr(0, MODE_TFT_8BIT_640480);
    rTPAL = (1<<24)|((0xff)<<0); // Enable Temporary Palette : Blue
    Lcd_PowerEnable(0, 1);
    Lcd_EnvidOnOff(1);
    PRINTF("Temporary palette test. Press any key!\n");    
    Uart_Getch();  	

    k=0;
    for(i=0;i<640;i+=40)
	for(j=0;j<480;j+=30)
	{ 
	    Glib_FilledRectangle(i,j,i+39,j+29,(k%256));
	    k++;
	}
    rTPAL = 0;
    PRINTF("Press any key to test writing palette during non-active.\n");

    palette=(U32 *)PALETTE;
    for(cdata=0;cdata<255;cdata++)
    {
	p_red=(cdata | 0xe0);
	p_green=(cdata | 0x1c);
	p_blue=(cdata | 0x03);

        while((rLCDCON5>>19)==2);
    	*palette++=((U32)((p_red<<8)|(p_green<<6)|(p_blue<<3)));
    	PRINTF("VSTATUS=%x\n",(rLCDCON5>>19));
    	PRINTF("cdata=%d\n",(int)cdata);
    }
    *palette=0x0;    
    Uart_Getch();
    Lcd_EnvidOnOff(0);
    Lcd_Port_Return();
}


void Test_Lcd_Tft_8Bit_640480_Bswp(void)
{
    int k;
    Lcd_Palette8Bit_Init();
    Lcd_Port_Init();
    Lcd_Init(MODE_TFT_8BIT_640480);
    Glib_Init(MODE_TFT_8BIT_640480);
    Lcd_EnvidOnOff(1);
    Lcd_PowerEnable(0, 1);
    rLCDCON5 &= 0x1ffffd;    //BSWP Disable
    PRINTF("[TFT 256 COLOR(16bit/1pixel) BSWP TEST]\n");

    Glib_ClearScr(0, MODE_TFT_8BIT_640480);
    Glib_Rectangle(0,0,639,479,0xff);
    Glib_Rectangle(1,1,638,478,0x03);
    Glib_Rectangle(0+100,0+100,639-100,479-100,0xff);
    Glib_Rectangle(1+100,1+100,638-100,478-100,0x03);
    Glib_Line(0,0,639,479,0xe0);     
    Glib_Line(639,0,0,479,0x1c);
    PRINTF("TFT 256 color BSWP test. Press any key excet return!\n");

    while(Uart_Getch()!='\r')
    {
        rLCDCON5 &= 0x1ffffd;    //BSWP Disable
        rLCDCON5 |= ((k%2)<<1);  //BSWP Enable
        k++;
    }

    Lcd_EnvidOnOff(0);
    Lcd_Port_Return();
}


void Test_Lcd_Tft_16Bit_640480(void)
{
    int i,j,k;
    Lcd_Port_Init();
    Lcd_Init(MODE_TFT_16BIT_640480);
    Glib_Init(MODE_TFT_16BIT_640480);
    Lcd_PowerEnable(0, 1);
    Lcd_EnvidOnOff(1);
    PRINTF("[TFT 64K COLOR(16bit/1pixel) LCD TEST]\n");

    Glib_ClearScr(0, MODE_TFT_16BIT_640480);
    Glib_FilledRectangle(0,0,639,479,0xf800);    
    PRINTF("TFT 64K color mode test 1. Press any key!\n");
    Uart_Getch();  	

    Glib_ClearScr(0, MODE_TFT_16BIT_640480);
    Glib_Rectangle(0,0,639,479,0x07e0);   
    Glib_FilledRectangle(0,0,20,20,65535);   
    Glib_Rectangle(620,460,639,479,65535);   
    Glib_Line(0,0,639,479,0x1f);        
    Glib_Line(639,0,0,479,0xf800);
    PRINTF("TFT 64K color mode test 2. Press any key!\n");
    Uart_Getch();  	

    Glib_ClearScr(0, MODE_TFT_16BIT_640480);
    k=0;
    for(i=160;i<480;i+=20)
    	for(j=120;j<360;j+=15)
    	{
	    	while((rLCDCON5>>19)==2);
    	    Glib_FilledRectangle(i,j,i+19,j+14,k);
    	    k+=500;
    	}

    // #0		    
    // 00		    
    Glib_Rectangle(0,0,319,239,65535);   
    Glib_Line(0,0,319,239,65535);        
    Glib_Line(0,239,319,0,65535);

    // 0#
    // 00
    Glib_Rectangle(0+320,0,319+320,239,255);
    Glib_Line(0+320,0,319+320,239,255);        
    Glib_Line(0+320,239,319+320,0,255);

    // 00
    // #0
    Glib_Rectangle(0,0+240,319,239+240,255);
    Glib_Line(0,0+240,319,239+240,255);        
    Glib_Line(0,239+240,319,0+240,255);

    // 00
    // 0#
    Glib_Rectangle(0+320,0+240,319+320,239+240,255);
    Glib_Line(0+320,0+240,319+320,239+240,255);     
    Glib_Line(0+320,239+240,319+320,0+240,255);
    Glib_Rectangle(50+320,50+240,269+320,189+240,255);

    PRINTF("TFT 64K color mode test 3. Press any key!\n");
    Uart_Getch();  	

    Glib_ClearScr(0, MODE_TFT_16BIT_640480);
    k=0;
    for(i=320;i<960;i+=40)
    	for(j=240;j<720;j+=30)
    	{
    	    Glib_FilledRectangle(i,j,i+39,j+29,k);
    	    k+=500;
    	}

    // #0		    
    // 00		    
    Glib_Rectangle(0,0,639,479,65535);   
    Glib_Line(0,0,639,479,65535);        
    Glib_Line(0,479,639,0,65535);

    // 0#
    // 00
    Glib_Rectangle(0+640,0,639+640,479,65535);   
    Glib_Line(0+640,0,639+640,479,65535);        
    Glib_Line(0+640,479,639+640,0,65535);

    // 00
    // #0
    Glib_Rectangle(0,0+480,639,479+480,65535);   
    Glib_Line(0,0+480,639,479+480,65535);        
    Glib_Line(0,479+480,639,0+480,65535);

    // 00
    // 0#
    Glib_Rectangle(0+640,0+480,639+640,479+480,65535);   
    Glib_Line(0+640,0+480,639+640,479+480,65535);        
    Glib_Line(0+640,479+480,639+640,0+480,65535);
    Glib_Rectangle(50+640,50+480,639+640-50,479+480-50,65535);   

    PRINTF("Virtual Screen Test(TFT 64K color). Press any key[ijkm\\r]!\n");
    MoveViewPort(MODE_TFT_16BIT_640480);
    Lcd_MoveViewPort(0,0,MODE_TFT_16BIT_640480);
    Lcd_EnvidOnOff(0);
    Lcd_Port_Return();
}


void Test_Lcd_Tft_16Bit_640480_Hwswp(void)
{
    int k;
    Lcd_Port_Init();
    Lcd_Init(MODE_TFT_16BIT_640480);
    Glib_Init(MODE_TFT_16BIT_640480);
    Lcd_PowerEnable(0, 1);
    Lcd_EnvidOnOff(1);
    rLCDCON5 &= 0x1ffffe;    //HWSWP Disable
    PRINTF("[TFT 64K COLOR(16bit/1pixel) HWSWP TEST]\n");

    Glib_ClearScr(0, MODE_TFT_16BIT_640480);
    Glib_Rectangle(0,0,639,479,0xffff);
    Glib_Rectangle(1,1,638,478,0xf800);
    Glib_Rectangle(0+100,0+100,639-100,479-100,0xffff);
    Glib_Rectangle(1+100,1+100,638-100,478-100,0xf800);
    Glib_Line(0,0,639,479,0x7e0);     
    Glib_Line(639,0,0,479,0x1f);
    PRINTF("TFT 64K color HWSWP test. Press any key excet return!\n");

    while(Uart_Getch()!='\r')
    {
        rLCDCON5 &= 0x1ffffe;    //HWSWP Disable
        rLCDCON5 |= (k%2);       //HWSWP Enable
        k++;
    }

    Lcd_EnvidOnOff(0);
    Lcd_Port_Return();
}


void Test_Lcd_Tft_1Bit_800600(void)
{
    int i,j;
    Lcd_Port_Init();
    Lcd_Palette1Bit_Init(); 
    Lcd_Init(MODE_TFT_1BIT_800600);
    Glib_Init(MODE_TFT_1BIT_800600);
    PRINTF("[TFT Mono(1bit/1pixel) LCD TEST]\n");

    rTPAL = (1<<24)|((0xff)<<0); // Enable Temporary Palette : Blue
//--------LCD FIFO interrupt test---------------------------------------------------START
	Lcd_EnvidOnOff(1); // Enable ENVID   
	//The content of GPG4 is changed to OUTPUT('01'). 
	//We will check the frame interrupt with using Logic Analyzer. 
	rGPGUP=rGPGUP&(~(1<<4))|(1<<4); // Pull-up disable
	rGPGDAT=rGPGDAT&(~(1<<4))|(1<<4); // GPG4=High
	rGPGCON=rGPGCON&(~(3<<8))|(1<<8); // GPG4=Output

	pISR_LCD=(unsigned)Lcd_Int_Fifo_640480;
	rINTMSK=~(BIT_LCD);
	rLCDINTMSK=(0<<2)|(1<<1)|(0); // 4Words Trigger Level,Mask Frame int,Unmask Fifo int
//        rLCDINTMSK=(1<<2)|(1<<1)|(0); // 8Words Trigger Level,Mask Frame int,Unmask Fifo int    
//        Lcd_EnvidOnOff(1); // Enable ENVID       
//--------LCD FIFO interrupt test-----------------------------------------------------END
    PRINTF("TFT Mono mode test 1. Press any key!\n");
    Uart_Getch();  	

    rTPAL = 0; // Disable TPAL
    Glib_FilledRectangle(0,0,LCD_XSIZE_TFT_800600-1,LCD_YSIZE_TFT_800600-1,1);
    PRINTF("TFT Mono mode test 2. Press any key!\n");
    Uart_Getch();  	

    Glib_FilledRectangle(200,200,LCD_XSIZE_TFT_800600-201,LCD_YSIZE_TFT_800600-201,0);   
    PRINTF("TFT Mono mode test 3. Press any key!\n");
    Uart_Getch();  	

    Glib_ClearScr(0, MODE_TFT_1BIT_800600);
    Glib_Rectangle(200,200,SCR_XSIZE_TFT_800600-201,SCR_YSIZE_TFT_800600-201,1);
    
    // #0		    
    // 00		    
    Glib_Rectangle(0,0,LCD_XSIZE_TFT_800600-1,LCD_YSIZE_TFT_800600-1,1);   
    Glib_Line(0,0,LCD_XSIZE_TFT_800600-1,LCD_YSIZE_TFT_800600-1,1);        
    Glib_Line(0,LCD_YSIZE_TFT_800600-1,LCD_XSIZE_TFT_800600-1,0,1);

    // 0#
    // 00
    Glib_Rectangle(LCD_XSIZE_TFT_800600,0,SCR_XSIZE_TFT_800600-1,LCD_YSIZE_TFT_800600-1,1);   
    Glib_Rectangle(LCD_XSIZE_TFT_800600+100,100,SCR_XSIZE_TFT_800600-101,LCD_YSIZE_TFT_800600-101,1);   
    
    // 00
    // #0
    Glib_Rectangle(0,LCD_YSIZE_TFT_800600,LCD_XSIZE_TFT_800600-1,SCR_YSIZE_TFT_800600-1,1);   
    Glib_Rectangle(200,LCD_YSIZE_TFT_800600+200,LCD_XSIZE_TFT_800600-201,SCR_YSIZE_TFT_800600-201,1);   

    // 00
    // 0#
    Glib_Rectangle(LCD_XSIZE_TFT_800600,LCD_YSIZE_TFT_800600,SCR_XSIZE_TFT_800600-1,SCR_YSIZE_TFT_800600-1,1);   
    Glib_Line(LCD_XSIZE_TFT_800600,LCD_YSIZE_TFT_800600,SCR_XSIZE_TFT_800600-1,SCR_YSIZE_TFT_800600-1,1);        
    Glib_Line(LCD_XSIZE_TFT_800600,SCR_YSIZE_TFT_800600-1,SCR_XSIZE_TFT_800600-1,LCD_YSIZE_TFT_800600,1);

    PRINTF("Virtual Screen Test(Mono). Press any key[ijkm\\r]!\n");
    MoveViewPort(MODE_TFT_1BIT_800600);
    Lcd_MoveViewPort(0,0,MODE_TFT_1BIT_800600);
//--------LCD FIFO interrupt test---------------------------------------------------START
    rLCDINTMSK|=3; // Mask LCD SUB Interrupt
    rINTMSK|=(BIT_LCD); // Mask LCD INT
//--------LCD FIFO interrupt test-----------------------------------------------------END   
    Lcd_EnvidOnOff(0);
    Lcd_Port_Return();
}


void Test_Lcd_Tft_8Bit_800600(void)
{
    int i,j,k;
    Lcd_Port_Init();
    Lcd_Palette8Bit_Init();
    Lcd_Init(MODE_TFT_8BIT_800600);
    Glib_Init(MODE_TFT_8BIT_800600);
    PRINTF("[TFT 256 COLOR(8bit/1pixel) LCD TEST]\n");

    rTPAL = (1<<24)|((0xff)<<0); // Enable Temporary Palette : Blue
//--------LCD FIFO interrupt test---------------------------------------------------START
	Lcd_EnvidOnOff(1); // Enable ENVID   
	//The content of GPG4 is changed to OUTPUT('01'). 
	//We will check the frame interrupt with using Logic Analyzer. 
	rGPGUP=rGPGUP&(~(1<<4))|(1<<4); // Pull-up disable
	rGPGDAT=rGPGDAT&(~(1<<4))|(1<<4); // GPG4=High
	rGPGCON=rGPGCON&(~(3<<8))|(1<<8); // GPG4=Output

	pISR_LCD=(unsigned)Lcd_Int_Fifo_640480;
	rINTMSK=~(BIT_LCD);
	rLCDINTMSK=(0<<2)|(1<<1)|(0); // 4Words Trigger Level,Mask Frame int,Unmask Fifo int
//        rLCDINTMSK=(1<<2)|(1<<1)|(0); // 8Words Trigger Level,Mask Frame int,Unmask Fifo int    
//        Lcd_EnvidOnOff(1); // Enable ENVID       
//--------LCD FIFO interrupt test-----------------------------------------------------END
    PRINTF("TFT 256 color mode test 1. Press any key!\n");
    Uart_Getch();  	

    Glib_ClearScr(0, MODE_TFT_8BIT_800600);
    rTPAL = 0;
    k=0;
    for(i=0;i<LCD_XSIZE_TFT_800600;i+=40)
	for(j=0;j<LCD_YSIZE_TFT_800600;j+=30)
	{ 
	    Glib_FilledRectangle(i,j,i+39,j+29,(k%256));
	    k++;
	}

    PRINTF("TFT 256 color mode test 2. Press any key!\n");
    Uart_Getch();  	

    Glib_ClearScr(0xff, MODE_TFT_8BIT_800600);
    PRINTF("TFT 256 color mode test 3. Press any key!\n");
    Uart_Getch();  	

    Glib_ClearScr(0, MODE_TFT_8BIT_800600);
    k=0;
    for(i=(SCR_XSIZE_TFT_800600/4);i<(SCR_XSIZE_TFT_800600*(3/4));i+=40)
    	for(j=SCR_YSIZE_TFT_800600/4;j<(SCR_YSIZE_TFT_800600*(3/4));j+=30)
    	{
    	    Glib_FilledRectangle(i,j,i+39,j+29,(k%256));
    	    k++;
    	}

    // #0		    
    // 00		    
    Glib_Rectangle(0,0,LCD_XSIZE_TFT_800600-1,LCD_YSIZE_TFT_800600-1,0xff);   
    Glib_Line(0,0,LCD_XSIZE_TFT_800600-1,LCD_YSIZE_TFT_800600-1,0xff);        
    Glib_Line(0,LCD_YSIZE_TFT_800600-1,LCD_XSIZE_TFT_800600-1,0,0xff);

    // 0#
    // 00
    Glib_Rectangle(LCD_XSIZE_TFT_800600,0,SCR_XSIZE_TFT_800600-1,LCD_YSIZE_TFT_800600-1,0xf0);   
    Glib_Rectangle(LCD_XSIZE_TFT_800600+100,100,SCR_XSIZE_TFT_800600-101,LCD_YSIZE_TFT_800600-101,0xf0);   
    
    // 00
    // #0
    Glib_Rectangle(0,LCD_YSIZE_TFT_800600,LCD_XSIZE_TFT_800600-1,SCR_YSIZE_TFT_800600-1,0x0f);   
    Glib_Rectangle(200,LCD_YSIZE_TFT_800600+200,LCD_XSIZE_TFT_800600-201,SCR_YSIZE_TFT_800600-201,0x0f);   

    // 00
    // 0#
    Glib_Rectangle(LCD_XSIZE_TFT_800600,LCD_YSIZE_TFT_800600,SCR_XSIZE_TFT_800600-1,SCR_YSIZE_TFT_800600-1,0xff);   
    Glib_Line(LCD_XSIZE_TFT_800600,LCD_YSIZE_TFT_800600,SCR_XSIZE_TFT_800600-1,SCR_YSIZE_TFT_800600-1,0xff);        
    Glib_Line(LCD_XSIZE_TFT_800600,SCR_YSIZE_TFT_800600-1,SCR_XSIZE_TFT_800600-1,LCD_YSIZE_TFT_800600,0xff);

    PRINTF("Virtual Screen Test(TFT 256 color). Press any key[ijkm\\r]!\n");
    MoveViewPort(MODE_TFT_8BIT_800600);
    Lcd_MoveViewPort(0,0,MODE_TFT_8BIT_800600);
//--------LCD FIFO interrupt test---------------------------------------------------START
    rLCDINTMSK|=3; // Mask LCD SUB Interrupt
    rINTMSK|=(BIT_LCD); // Mask LCD INT
//--------LCD FIFO interrupt test-----------------------------------------------------END
    Lcd_EnvidOnOff(0);
    Lcd_Port_Return();
}


