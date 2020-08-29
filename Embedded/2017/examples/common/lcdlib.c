/*****************************************
  NAME: lcdlib.c
  DESC: lcd configuration low-level codes
  HISTORY:
  2002.03.13:draft ver 0.0
 *****************************************/
#include <string.h>
#include "2410addr.h"
#include "2410lib.h"
#include "def.h"
//#include "option.h"
//#include "24xslib.h" 
#include "lcdlib.h"

//Mono STN
U32 (*frameBuffer1Bit)[SCR_XSIZE_STN/32];
//Gray
U32 (*frameBuffer2Bit)[SCR_XSIZE_STN/16];
U32 (*frameBuffer4Bit)[SCR_XSIZE_STN/8];
//Color STN
U32 (*frameBuffer8Bit)[SCR_XSIZE_CSTN/4];
U32 (*frameBuffer12Bit)[SCR_XSIZE_CSTN*3/8];
//TFT 240320
U32 (*frameBuffer8BitTft240320)[SCR_XSIZE_TFT_240320/4];
U32 (*frameBuffer16BitTft240320)[SCR_XSIZE_TFT_240320/2];
//TFT 640480
U32 (*frameBuffer1BitTft640480)[SCR_XSIZE_TFT_640480/32];
U32 (*frameBuffer8BitTft640480)[SCR_XSIZE_TFT_640480/4];
U32 (*frameBuffer16BitTft640480)[SCR_XSIZE_TFT_640480/2];
U32 (*frameBuffer24BitTft640480)[SCR_XSIZE_TFT_640480];
//TFT 800600
U32 (*frameBuffer1BitTft800600)[SCR_XSIZE_TFT_800600/32];
U32 (*frameBuffer8BitTft800600)[SCR_XSIZE_TFT_800600/4];
U32 (*frameBuffer16BitTft800600)[SCR_XSIZE_TFT_800600/2];

void Lcd_Init(int type)
{
    switch(type)
    {
    case MODE_STN_1BIT:
       	frameBuffer1Bit=(U32 (*)[SCR_XSIZE_STN/32])LCDFRAMEBUFFER;
	rLCDCON1=(CLKVAL_STN_MONO<<8)|(MVAL_USED<<7)|(1<<5)|(0<<1)|0; 
   	// 4-bit single scan,1bpp STN,ENVID=off
	rLCDCON2=(0<<24)|(LINEVAL_STN<<14)|(0<<6)|(0<<0);	// It is not TFT LCD. So,.....    		
	rLCDCON3=(WDLY_STN<<19)|(HOZVAL_STN<<8)|(LINEBLANK_MONO<<0);
	rLCDCON4=(MVAL<<8)|(WLH_STN<<0);
	rLCDCON5=0;
	//BPP24BL:x,FRM565:x,INVVCLK:x,INVVLINE:x,INVVFRAME:x,INVVD:x,
	//INVVDEN:x,INVPWREN:x,INVLEND:x,PWREN:x,ENLEND:x,BSWP:x,HWSWP:x
	rLCDSADDR1=(((U32)frameBuffer1Bit>>22)<<21)|M5D((U32)frameBuffer1Bit>>1);		
	rLCDSADDR2=M5D( ((U32)frameBuffer1Bit+(SCR_XSIZE_STN*LCD_YSIZE_STN/8))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_STN-LCD_XSIZE_STN)/16)<<11)|(LCD_XSIZE_STN/16);
    break;

    case MODE_STN_2BIT:
    	frameBuffer2Bit=(U32 (*)[SCR_XSIZE_STN/16])LCDFRAMEBUFFER;
    	rLCDCON1=(CLKVAL_STN_GRAY<<8)|(MVAL_USED<<7)|(1<<5)|(1<<1)|0;
   	// 4-bit single scan,2bpp STN,ENVID=off
    	rLCDCON2=(0<<24)|(LINEVAL_STN<<14)|(0<<6)|(0<<0);
    	rLCDCON3=(WDLY_STN<<19)|(HOZVAL_STN<<8)|(LINEBLANK_GRAY<<0);
    	rLCDCON4=(MVAL<<8)|(WLH_STN<<0);
    	rLCDCON5=0;
	//BPP24BL:x,FRM565:x,INVVCLK:x,INVVLINE:x,INVVFRAME:x,INVVD:x,
	//INVVDEN:x,INVPWREN:x,INVLEND:x,PWREN:x,ENLEND:x,BSWP:x,HWSWP:x
    	rLCDSADDR1=(((U32)frameBuffer2Bit>>22)<<21)|M5D((U32)frameBuffer2Bit>>1);
    	rLCDSADDR2=M5D( ((U32)frameBuffer2Bit+(SCR_XSIZE_STN*LCD_YSIZE_STN/4))>>1);
    	rLCDSADDR3=(((SCR_XSIZE_STN-LCD_XSIZE_STN)/8)<<11)|(LCD_XSIZE_STN/8);
	rDITHMODE=0x0;
	rBLUELUT =0xf950;	// 4-Gray only
    break;
    	
    case MODE_STN_4BIT:
    	frameBuffer4Bit=(U32 (*)[SCR_XSIZE_STN/8])LCDFRAMEBUFFER;
    	rLCDCON1=(CLKVAL_STN_GRAY<<8)|(MVAL_USED<<7)|(1<<5)|(2<<1)|0;
    	// 4-bit single scan,4bpp STN,ENVID=off
	rLCDCON2=(0<<24)|(LINEVAL_STN<<14)|(0<<6)|(0<<0);
	rLCDCON3=(WDLY_STN<<19)|(HOZVAL_STN<<8)|(LINEBLANK_GRAY<<0);
	rLCDCON4=(MVAL<<8)|(WLH_STN<<0);
	rLCDCON5=0;
	//BPP24BL:x,FRM565:x,INVVCLK:x,INVVLINE:x,INVVFRAME:x,INVVD:x,
	//INVVDEN:x,INVPWREN:x,INVLEND:x,PWREN:x,ENLEND:x,BSWP:x,HWSWP:x
	rLCDSADDR1=(((U32)frameBuffer4Bit>>22)<<21)|M5D((U32)frameBuffer4Bit>>1);
	rLCDSADDR2=M5D( ((U32)frameBuffer4Bit+(SCR_XSIZE_STN*LCD_YSIZE_STN/2))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_STN-LCD_XSIZE_STN)/4)<<11)|(LCD_XSIZE_STN/4);
	rDITHMODE=0x0;
    break;

    case MODE_CSTN_8BIT:
    	frameBuffer8Bit=(U32 (*)[SCR_XSIZE_CSTN/4])LCDFRAMEBUFFER;
	rLCDCON1=(CLKVAL_CSTN<<8)|(MVAL_USED<<7)|(2<<5)|(3<<1)|0;
    	// 8-bit single scan,8bpp CSTN,ENVID=off
	rLCDCON2=(0<<24)|(LINEVAL_CSTN<<14)|(0<<6)|(0<<0);
	rLCDCON3=(WDLY_CSTN<<19)|(HOZVAL_CSTN<<8)|(LINEBLANK_CSTN<<0);
	rLCDCON4=(MVAL<<8)|(WLH_CSTN<<0);
	rLCDCON5=0;
	//BPP24BL:x,FRM565:x,INVVCLK:x,INVVLINE:x,INVVFRAME:x,INVVD:x,
	//INVVDEN:x,INVPWREN:x,INVLEND:x,PWREN:x,ENLEND:x,BSWP:x,HWSWP:x
	rLCDSADDR1=(((U32)frameBuffer8Bit>>22)<<21 )|M5D((U32)frameBuffer8Bit>>1);
	rLCDSADDR2=M5D( ((U32)frameBuffer8Bit+(SCR_XSIZE_CSTN*LCD_YSIZE_CSTN/1))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_CSTN-LCD_XSIZE_CSTN)/2)<<11)|(LCD_XSIZE_CSTN/2);
	rDITHMODE=0x0;
	rREDLUT  =0xfdb96420;
	rGREENLUT=0xfdb96420;
	rBLUELUT =0xfb40;
    break;
	
    case MODE_CSTN_12BIT:
    	frameBuffer12Bit=(U32 (*)[SCR_XSIZE_CSTN*3/8])LCDFRAMEBUFFER;
    	// Packed Type : The L.C.M of 12 and 32 is 96.
    	rLCDCON1=(CLKVAL_CSTN<<8)|(MVAL_USED<<7)|(2<<5)|(4<<1)|0;
    	// 8-bit single scan,12bpp CSTN,ENVID=off
    	rLCDCON2=(0<<24)|(LINEVAL_CSTN<<14)|(0<<6)|0;
    	rLCDCON3=(WDLY_CSTN<<19)|(HOZVAL_CSTN<<8)|(LINEBLANK_CSTN<<0);
    	rLCDCON4=(MVAL<<8)|(WLH_CSTN<<0);
    	rLCDCON5=0;
    	//BPP24BL:x,FRM565:x,INVVCLK:x,INVVLINE:x,INVVFRAME:x,INVVD:x,
	//INVVDEN:x,INVPWREN:x,INVLEND:x,PWREN:x,ENLEND:x,BSWP:x,HWSWP:x
    	rLCDSADDR1=(((U32)frameBuffer12Bit>>22)<<21)|M5D((U32)frameBuffer12Bit>>1);
    	rLCDSADDR2=M5D(((U32)frameBuffer12Bit+((SCR_XSIZE_CSTN*3/2)*LCD_YSIZE_CSTN))>>1);
    	rLCDSADDR3=(((SCR_XSIZE_CSTN-LCD_XSIZE_CSTN)*3/4)<<11)|(LCD_XSIZE_CSTN*3/4);
	rDITHMODE=0;
    break;

    case MODE_TFT_8BIT_240320:
	frameBuffer8BitTft240320=(U32 (*)[SCR_XSIZE_TFT_240320/4])LCDFRAMEBUFFER;
	rLCDCON1=(CLKVAL_TFT_240320<<8)|(MVAL_USED<<7)|(3<<5)|(11<<1)|0;
        // TFT LCD panel,8bpp TFT,ENVID=off
	rLCDCON2=(VBPD_240320<<24)|(LINEVAL_TFT_240320<<14)|(VFPD_240320<<6)|(VSPW_240320);
	rLCDCON3=(HBPD_240320<<19)|(HOZVAL_TFT_240320<<8)|(HFPD_240320);
	rLCDCON4=(MVAL<<8)|(HSPW_240320);
	rLCDCON5=(1<<11)|(1<<9)|(1<<8);	//FRM5:6:5,HSYNC and VSYNC are inverted
	rLCDSADDR1=(((U32)frameBuffer8BitTft240320>>22)<<21)|M5D((U32)frameBuffer8BitTft240320>>1);
	rLCDSADDR2=M5D( ((U32)frameBuffer8BitTft240320+(SCR_XSIZE_TFT_240320*LCD_YSIZE_TFT_240320/1))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_TFT_240320-LCD_XSIZE_TFT_240320)/2)<<11)|(LCD_XSIZE_TFT_240320/2);
	rLCDINTMSK|=(3); // MASK LCD Sub Interrupt
	rLPCSEL&=(~7); // Disable LPC3600
	rTPAL=0; // Disable Temp Palette
    break;
    		
    case MODE_TFT_16BIT_240320:
	frameBuffer16BitTft240320=(U32 (*)[SCR_XSIZE_TFT_240320/2])LCDFRAMEBUFFER;
	rLCDCON1=(CLKVAL_TFT_240320<<8)|(MVAL_USED<<7)|(3<<5)|(12<<1)|0;
    // TFT LCD panel,16bpp TFT,ENVID=off
	rLCDCON2=(VBPD_240320<<24)|(LINEVAL_TFT_240320<<14)|(VFPD_240320<<6)|(VSPW_240320);
	rLCDCON3=(HBPD_240320<<19)|(HOZVAL_TFT_240320<<8)|(HFPD_240320);
	rLCDCON4=(MVAL<<8)|(HSPW_240320);
	rLCDCON5=(1<<11)|(0<<9)|(0<<8);	//FRM5:6:5,HSYNC and VSYNC are inverted	
	rLCDSADDR1=(((U32)frameBuffer16BitTft240320>>22)<<21)|M5D((U32)frameBuffer16BitTft240320>>1);
	rLCDSADDR2=M5D( ((U32)frameBuffer16BitTft240320+(SCR_XSIZE_TFT_240320*LCD_YSIZE_TFT_240320*2))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_TFT_240320-LCD_XSIZE_TFT_240320)/1)<<11)|(LCD_XSIZE_TFT_240320/1);
	rLCDINTMSK|=(3); // MASK LCD Sub Interrupt
	rLPCSEL&=(~7); // Disable LPC3600
	rTPAL=0; // Disable Temp Palette
    break;

    case MODE_TFT_1BIT_640480:
    	frameBuffer1BitTft640480=(U32 (*)[SCR_XSIZE_TFT_640480/32])LCDFRAMEBUFFER;
	rLCDCON1=(CLKVAL_TFT_640480<<8)|(MVAL_USED<<7)|(3<<5)|(8<<1)|0;
	rLCDCON2=(VBPD_640480<<24)|(LINEVAL_TFT_640480<<14)|(VFPD_640480<<6)|(VSPW_640480);
	rLCDCON3=(HBPD_640480<<19)|(HOZVAL_TFT_640480<<8)|(HFPD_640480);
	rLCDCON4=(MVAL<<8)|(HSPW_640480);
	rLCDCON5=(1<<11)|(1<<9)|(1<<8);	//FRM5:6:5,HSYNC and VSYNC are inverted
	rLCDSADDR1=(((U32)frameBuffer1BitTft640480>>22)<<21)|M5D((U32)frameBuffer1BitTft640480>>1);
	rLCDSADDR2=M5D( ((U32)frameBuffer1BitTft640480+(SCR_XSIZE_TFT_640480*LCD_YSIZE_TFT_640480/8))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_TFT_640480-LCD_XSIZE_TFT_640480)/16)<<11)|(LCD_XSIZE_TFT_640480/16);
	rLCDINTMSK|=(3); // MASK LCD Sub Interrupt
	rLPCSEL&=(~7); // Disable LPC3600
	rTPAL=0; // Disable Temp Palette
    break;

    case MODE_TFT_8BIT_640480:
    	frameBuffer8BitTft640480=(U32 (*)[SCR_XSIZE_TFT_640480/4])LCDFRAMEBUFFER;
	rLCDCON1=(CLKVAL_TFT_640480<<8)|(MVAL_USED<<7)|(3<<5)|(11<<1)|0;
   	// TFT LCD panel,8bpp TFT,ENVID=off
	rLCDCON2=(VBPD_640480<<24)|(LINEVAL_TFT_640480<<14)|(VFPD_640480<<6)|(VSPW_640480);
	rLCDCON3=(HBPD_640480<<19)|(HOZVAL_TFT_640480<<8)|(HFPD_640480);
	rLCDCON4=(MVAL<<8)|(HSPW_640480);
	rLCDCON5=(1<<11)|(1<<9)|(1<<8);	//FRM5:6:5,HSYNC and VSYNC are inverted
	rLCDSADDR1=(((U32)frameBuffer8BitTft640480>>22)<<21)|M5D((U32)frameBuffer8BitTft640480>>1);
	rLCDSADDR2=M5D( ((U32)frameBuffer8BitTft640480+(SCR_XSIZE_TFT_640480*LCD_YSIZE_TFT_640480/1))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_TFT_640480-LCD_XSIZE_TFT_640480)/2)<<11)|(LCD_XSIZE_TFT_640480/2);
	rLCDINTMSK|=(3); // MASK LCD Sub Interrupt
	rLPCSEL&=(~7); // Disable LPC3600
	rTPAL=0; // Disable Temp Palette
    break;
    	
    case MODE_TFT_16BIT_640480:
    	frameBuffer16BitTft640480=(U32 (*)[SCR_XSIZE_TFT_640480/2])LCDFRAMEBUFFER;
	rLCDCON1=(CLKVAL_TFT_640480<<8)|(MVAL_USED<<7)|(3<<5)|(12<<1)|0;
        // TFT LCD panel,16bpp TFT,ENVID=off
	rLCDCON2=(VBPD_640480<<24)|(LINEVAL_TFT_640480<<14)|(VFPD_640480<<6)|(VSPW_640480);
	rLCDCON3=(HBPD_640480<<19)|(HOZVAL_TFT_640480<<8)|(HFPD_640480);
	rLCDCON4=(MVAL<<8)|(HSPW_640480);
	rLCDCON5=(1<<11)|(1<<9)|(1<<8);	//FRM5:6:5,HSYNC and VSYNC are inverted
	rLCDSADDR1=(((U32)frameBuffer16BitTft640480>>22)<<21)|M5D((U32)frameBuffer16BitTft640480>>1);
	rLCDSADDR2=M5D( ((U32)frameBuffer16BitTft640480+(SCR_XSIZE_TFT_640480*LCD_YSIZE_TFT_640480*2))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_TFT_640480-LCD_XSIZE_TFT_640480)/1)<<11)|(LCD_XSIZE_TFT_640480/1);
	rLCDINTMSK|=(3); // MASK LCD Sub Interrupt
	rLPCSEL&=(~7); // Disable LPC3600
	rTPAL=0; // Disable Temp Palette
    break;

    case MODE_TFT_24BIT_640480:
    	frameBuffer24BitTft640480=(U32 (*)[SCR_XSIZE_TFT_640480])LCDFRAMEBUFFER;
	rLCDCON1=(CLKVAL_TFT_640480<<8)|(MVAL_USED<<7)|(3<<5)|(13<<1)|0;
        // TFT LCD panel,24bpp TFT,ENVID=off
	rLCDCON2=(VBPD_640480<<24)|(LINEVAL_TFT_640480<<14)|(VFPD_640480<<6)|(VSPW_640480);
	rLCDCON3=(HBPD_640480<<19)|(HOZVAL_TFT_640480<<8)|(HFPD_640480);
	rLCDCON4=(MVAL<<8)|(HSPW_640480);
	rLCDCON5=(1<<12)|(1<<9)|(1<<8);	// BPP24:MSB,HSYNC and VSYNC are inverted
	rLCDSADDR1=(((U32)frameBuffer24BitTft640480>>22)<<21)|M5D((U32)frameBuffer24BitTft640480>>1);
	rLCDSADDR2=M5D( ((U32)frameBuffer24BitTft640480+(SCR_XSIZE_TFT_640480*LCD_YSIZE_TFT_640480*4))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_TFT_640480-LCD_XSIZE_TFT_640480)*2)<<11)|(LCD_XSIZE_TFT_640480*2);
	rLCDINTMSK|=(3); // MASK LCD Sub Interrupt
	rLPCSEL&=(~7); // Disable LPC3600
	rTPAL=0; // Disable Temp Palette

    break;

    case MODE_TFT_1BIT_800600:
	frameBuffer1BitTft800600=(U32 (*)[SCR_XSIZE_TFT_800600/32])LCDFRAMEBUFFER;
   	rLCDCON1=(CLKVAL_TFT_800600<<8)|(MVAL_USED<<7)|(3<<5)|(8<<1)|0;
        // TFT LCD panel,1bpp TFT,ENVID=off
	rLCDCON2=(VBPD_800600<<24)|(LINEVAL_TFT_800600<<14)|(VFPD_800600<<6)|(VSPW_800600);
	rLCDCON3=(HBPD_800600<<19)|(HOZVAL_TFT_800600<<8)|(HFPD_800600);
	rLCDCON4=(MVAL<<8)|(HSPW_800600);
	rLCDCON5=(1<<9)|(1<<8);	
   	//BPP24BL:x,FRM565:x,INVVCLK:x,INVVLINE:o,INVVFRAME:o,INVVD:x,
	//INVVDEN:x,INVPWREN:x,INVLEND:x,PWREN:x,ENLEND:x,BSWP:x,HWSWP:x
	rLCDSADDR1=(((U32)frameBuffer1BitTft800600>>22)<<21)|M5D((U32)frameBuffer1BitTft800600>>1);
	rLCDSADDR2=M5D( ((U32)frameBuffer1BitTft800600+(SCR_XSIZE_TFT_800600*LCD_YSIZE_TFT_800600/8))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_TFT_800600-LCD_XSIZE_TFT_800600)/16)<<11)|(LCD_XSIZE_TFT_800600/16);
	rLCDINTMSK|=(3); // MASK LCD Sub Interrupt
	rLPCSEL&=(~7); // Disable LPC3600
	rTPAL=0; // Disable Temp Palette

    break;

    case MODE_TFT_8BIT_800600:
	frameBuffer8BitTft800600=(U32 (*)[SCR_XSIZE_TFT_800600/4])LCDFRAMEBUFFER;
   	rLCDCON1=(CLKVAL_TFT_800600<<8)|(MVAL_USED<<7)|(3<<5)|(11<<1)|0;
        // TFT LCD panel,8bpp TFT,ENVID=off
	rLCDCON2=(VBPD_800600<<24)|(LINEVAL_TFT_800600<<14)|(VFPD_800600<<6)|(VSPW_800600);
	rLCDCON3=(HBPD_800600<<19)|(HOZVAL_TFT_800600<<8)|(HFPD_800600);
	rLCDCON4=(MVAL<<8)|(HSPW_800600);
	rLCDCON5=(1<<9)|(1<<8);	
	//BPP24BL:x,FRM565:x,INVVCLK:x,INVVLINE:o,INVVFRAME:o,INVVD:x,
	//INVVDEN:x,INVPWREN:x,INVLEND:x,PWREN:x,ENLEND:x,BSWP:x,HWSWP:x
	rLCDSADDR1=(((U32)frameBuffer8BitTft800600>>22)<<21)|M5D((U32)frameBuffer8BitTft800600>>1);
	rLCDSADDR2=M5D( ((U32)frameBuffer8BitTft800600+(SCR_XSIZE_TFT_800600*LCD_YSIZE_TFT_800600/1))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_TFT_800600-LCD_XSIZE_TFT_800600)/2)<<11)|(LCD_XSIZE_TFT_800600/2);
	rLCDINTMSK|=(3); // MASK LCD Sub Interrupt
	rLPCSEL&=(~7); // Disable LPC3600
	rTPAL=0; // Disable Temp Palette
    break;
    	
    case MODE_TFT_16BIT_800600:
	frameBuffer16BitTft800600=(U32 (*)[SCR_XSIZE_TFT_800600/2])LCDFRAMEBUFFER;
   	rLCDCON1=(CLKVAL_TFT_800600<<8)|(MVAL_USED<<7)|(3<<5)|(12<<1)|0;
        // TFT LCD panel,16bpp TFT,ENVID=off
	rLCDCON2=(VBPD_800600<<24)|(LINEVAL_TFT_800600<<14)|(VFPD_800600<<6)|(VSPW_800600);
	rLCDCON3=(HBPD_800600<<19)|(HOZVAL_TFT_800600<<8)|(HFPD_800600);
	rLCDCON4=(MVAL<<8)|(HSPW_800600);
	rLCDCON5=(1<<11)|(1<<10)|(1<<9)|(1<<8);
	//BPP24BL:x,FRM565:o,INVVCLK:x,INVVLINE:o,INVVFRAME:o,INVVD:x,
	//INVVDEN:x,INVPWREN:x,INVLEND:x,PWREN:x,ENLEND:x,BSWP:x,HWSWP:x
	rLCDSADDR1=(((U32)frameBuffer16BitTft800600>>22)<<21)|M5D((U32)frameBuffer16BitTft800600>>1);
	rLCDSADDR2=M5D( ((U32)frameBuffer16BitTft800600+(SCR_XSIZE_TFT_800600*LCD_YSIZE_TFT_800600*2))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_TFT_800600-LCD_XSIZE_TFT_800600)/1)<<11)|(LCD_XSIZE_TFT_800600/1);
	rLCDINTMSK|=(3); // MASK LCD Sub Interrupt
	rLPCSEL&=(~7); // Disable LPC3600
	rTPAL=0; // Disable Temp Palette

    break;

    default:
    break;
    }	
}


/*
void Lcd_Palette_Init(void)
{
    unsigned char cdata, p_red, p_green, p_blue;
    U32 *palette;
    
    palette=(U32 *)PALETTE;
    *palette++=0; //black
    for(cdata=1;cdata<255;cdata++)
    {
		p_red=(cdata & 0xe0);
		p_green=(cdata & 0x1c);
		p_blue=(cdata & 0x03);
    	*palette++=((U32)((p_red<<8)|(p_green<<6)|(p_blue<<3)));
    }
    *palette=0xffff; //white
}
*/


void Lcd_CstnOnOff(int onoff)
{
    // 1:CSTN Panel on  0:CSTN Panel off //	
    if(onoff==1)
    	rLCDCON1|=1; // ENVID=ON
    else
	rLCDCON1 =rLCDCON1 & 0x3fffe; // ENVID Off
    rGPGUP=rGPGUP|(1<<4); // Pull-up disable
    rGPGDAT=rGPGDAT&(~(1<<4))|(onoff<<4); // GPB5=On or Off
    rGPGCON=rGPGCON&(~(3<<8))|(1<<8);    //GPD9=output
}    


void Lcd_EnvidOnOff(int onoff)
{
    if(onoff==1)
	rLCDCON1|=1; // ENVID=ON
    else
	rLCDCON1 =rLCDCON1 & 0x3fffe; // ENVID Off
}    


void Lcd_Lpc3600Enable(void)
{
    rLPCSEL&=~(7);
    rLPCSEL|=(7); // 240320,Enable LPC3600
}    


void Lcd_PowerEnable(int invpwren,int pwren)
{
    //GPG4 is setted as LCD_PWREN
    rGPGUP=rGPGUP&(~(1<<4))|(1<<4); // Pull-up disable
    rGPGCON=rGPGCON&(~(3<<8))|(3<<8); //GPG4=LCD_PWREN
    //Enable LCD POWER ENABLE Function
    rLCDCON5=rLCDCON5&(~(1<<3))|(pwren<<3);   // PWREN
    rLCDCON5=rLCDCON5&(~(1<<5))|(invpwren<<5);   // INVPWREN
}    


void MoveViewPort(int type)
{
    int vx=0,vy=0,vd;
    vd=(type==MODE_STN_1BIT)*16+(type==MODE_STN_2BIT)*8+(type==MODE_STN_4BIT)*4
        +(type==MODE_CSTN_8BIT)*2+(type==MODE_CSTN_12BIT)*4 
        +(type==MODE_TFT_1BIT_240320)*16+(type==MODE_TFT_8BIT_240320)*2+(type==MODE_TFT_16BIT_240320)*1
        +(type==MODE_TFT_1BIT_640480)*16+(type==MODE_TFT_8BIT_640480)*2+(type==MODE_TFT_16BIT_640480)*1+(type==MODE_TFT_24BIT_640480)/2
        +(type==MODE_TFT_1BIT_800600)*16+(type==MODE_TFT_8BIT_800600)*2+(type==MODE_TFT_16BIT_800600)*1;        
    while(1)
    {
    	switch(Uart_Getch())
    	{
    	case 'i':
	    if(vy>=vd)vy-=vd;    	   	
        break;

    	case 'j':
    	    if(vx>=vd)vx-=vd;
    	break;

    	case 'k':
	    //if((type==MODE_TFT_1BIT_800600)|(type==MODE_TFT_8BIT_800600)|(type==MODE_TFT_16BIT_800600))   
	    if((type&0x4000)&&(type&0x400))		  
	    {
                if(vx<=(SCR_XSIZE_TFT_800600-LCD_XSIZE_TFT_800600-vd))vx+=vd;   	    
	    }
	    //else if((type==MODE_TFT_1BIT_640480)|(type==MODE_TFT_8BIT_640480)|(type==MODE_TFT_16BIT_640480)|(type==MODE_TFT_24BIT_640480))   
	    else if((type&0x4000)&&(type&0x200))		  
	    {
                if(vx<=(SCR_XSIZE_TFT_640480-LCD_XSIZE_TFT_640480-vd))vx+=vd;   	    
	    }
            //else if((type==MODE_TFT_8BIT_240320)|(type==MODE_TFT_16BIT_240320))   
	    else if((type&0x4000)&&(type&0x100)) 
	    {
                if(vx<=(SCR_XSIZE_TFT_240320-LCD_XSIZE_TFT_240320-vd))vx+=vd;   	    
	    }
            //else if((type==MODE_CSTN_8BIT)|(type==MODE_CSTN_12BIT))   
            else if(type&0x2000)   
            {
                if(vx<=(SCR_XSIZE_CSTN-LCD_XSIZE_CSTN-vd))vx+=vd;   	    
            }
            else
            {
                if(vx<=(SCR_XSIZE_STN-LCD_XSIZE_STN-vd))vx+=vd;   	    
            }
   	    break;

    	case 'm':
	    if((type&0x4000)&&(type&0x400))
            {
                if(vy<=(SCR_YSIZE_TFT_800600-LCD_YSIZE_TFT_800600-vd))vy+=vd; 
                else if(vy=592)vy+=8;
            }
	    else if((type&0x4000)&&(type&0x200))
            {
                if(vy<=(SCR_YSIZE_TFT_640480-LCD_YSIZE_TFT_640480-vd))vy+=vd;   	    
            }
	    else if((type&0x4000)&&(type&0x100))
            {
                if(vy<=(SCR_YSIZE_TFT_240320-LCD_YSIZE_TFT_240320-vd))vy+=vd;   	    
            }
            else if(type&0x2000)   
            {
                if(vy<=(SCR_YSIZE_CSTN-LCD_YSIZE_CSTN-vd))vy+=vd;   	    
            }
            else
            {
                if(vy<=(SCR_YSIZE_STN-LCD_YSIZE_STN-vd))vy+=vd;   	    
            }
   	    break;

    	case '\r':
   	    return;

    	default:
	    break;
		}
	PRINTF("vx=%3d,vy=%3d\n",vx,vy);
	Lcd_MoveViewPort(vx,vy,type);
    }
}


void Lcd_MoveViewPort(int vx,int vy,int type)
{
    U32 addr;
    switch(type)
    {
    case MODE_STN_1BIT:
    	// LCDBASEU,LCDBASEL register has to be changed before 12 words before the end of VLINE.
    	// In mono mode, x=320 is 10 words, So, We can't change LCDBASEU,LCDBASEL 
    	// during LINECNT=1~0 at mono mode. 
	// The processor mode should be superviser mode.  
    	SET_IF();
	#if (LCD_XSIZE_STN<512)
    	    while((rLCDCON1>>18)<=1); // if x<512
   	#else	
    	    while((rLCDCON1>>18)==0); // if x>512 ((12+4)*32) 
    	#endif
	addr=(U32)frameBuffer1Bit+(vx/8)+vy*(SCR_XSIZE_STN/8);
	rLCDSADDR1= ( (addr>>22)<<21 ) | M5D(addr>>1);
	rLCDSADDR2= M5D( ((addr+(SCR_XSIZE_STN*LCD_YSIZE_STN/8))>>1) );
	CLR_IF();
   	break;

    case MODE_STN_2BIT:
	SET_IF(); 
	#if (LCD_XSIZE_STN<256)
   	    while((rLCDCON1>>18)<=1); // if x<256
	#else	
    	    while((rLCDCON1>>18)==0); // if x>256
	#endif
        addr=(U32)frameBuffer2Bit+(vx/4)+vy*(SCR_XSIZE_STN/4);
	rLCDSADDR1= ( (addr>>22)<<21 ) | M5D(addr>>1);
	rLCDSADDR2= M5D(((addr+(SCR_XSIZE_STN*LCD_YSIZE_STN/4))>>1));
	CLR_IF();
    break;

    case MODE_STN_4BIT:
	SET_IF(); 
    	#if (LCD_XSIZE_STN<128)
    	    while((rLCDCON1>>18)<=1); // if x<128
	#else	
    	    while((rLCDCON1>>18)==0); // if x>128
	#endif
        addr=(U32)frameBuffer4Bit+(vx/2)+vy*(SCR_XSIZE_STN/2);
	rLCDSADDR1= ( (addr>>22)<<21 ) | M5D(addr>>1);
	rLCDSADDR2= M5D(((addr+(SCR_XSIZE_STN*LCD_YSIZE_STN/2))>>1));
	CLR_IF();
    break;

    case MODE_CSTN_8BIT:
	SET_IF(); 
	#if (LCD_XSIZE_CSTN<64)
    	    while((rLCDCON1>>18)<=1); // if x<64
	#else	
 	    while((rLCDCON1>>18)==0); // if x>64
	#endif
        addr=(U32)frameBuffer8Bit+(vx/1)+vy*(SCR_XSIZE_CSTN/1);
	rLCDSADDR1= ( (addr>>22)<<21 ) | M5D(addr>>1);
	rLCDSADDR2= M5D(((addr+(SCR_XSIZE_CSTN*LCD_YSIZE_CSTN))>>1));
	CLR_IF();
    break;

    case MODE_CSTN_12BIT:
    	SET_IF(); 
	#if (LCD_XSIZE_CSTN<43)
    	    while((rLCDCON1>>18)<=1); // if x<43
	#else	
    	    while((rLCDCON1>>18)==0); // if x>43
	#endif
    	addr=(U32)frameBuffer12Bit+(vx*3/2)+vy*(SCR_XSIZE_CSTN*3/2); // Move 6Byte(4pixel)
	rLCDSADDR1= ( (addr>>22)<<21 ) | M5D(addr>>1);
	rLCDSADDR2= M5D(((addr+(SCR_XSIZE_CSTN*LCD_YSIZE_CSTN*3/2))>>1));
	CLR_IF();
    break;
    	
    case MODE_TFT_1BIT_240320:
    	SET_IF(); 
	#if (LCD_XSIZE_TFT_240320<512)
    	    while((rLCDCON1>>18)<=1); // if x<512
	#else	
	    while((rLCDCON1>>18)==0); // if x>512
	#endif
        addr=(U32)frameBuffer8BitTft240320+(vx/8)+vy*(SCR_XSIZE_TFT_240320/8);
	rLCDSADDR1= ( (addr>>22)<<21 ) | M5D(addr>>1);
	rLCDSADDR2= M5D(((addr+(SCR_XSIZE_TFT_240320*LCD_YSIZE_TFT_240320/8))>>1));
	CLR_IF();
    break;

    case MODE_TFT_8BIT_240320:
    	SET_IF(); 
	#if (LCD_XSIZE_TFT_240320<64)
    	    while((rLCDCON1>>18)<=1); // if x<64
	#else	
	    while((rLCDCON1>>18)==0); // if x>64
	#endif
        addr=(U32)frameBuffer8BitTft240320+(vx/1)+vy*(SCR_XSIZE_TFT_240320/1);
	rLCDSADDR1= ( (addr>>22)<<21 ) | M5D(addr>>1);
	rLCDSADDR2= M5D(((addr+(SCR_XSIZE_TFT_240320*LCD_YSIZE_TFT_240320))>>1));
	CLR_IF();
    break;

    case MODE_TFT_16BIT_240320:
    	SET_IF(); 
	#if (LCD_XSIZE_TFT_240320<32)
    	    while((rLCDCON1>>18)<=1); // if x<32
	#else	
    	    while((rLCDCON1>>18)==0); // if x>32
	#endif
        addr=(U32)frameBuffer16BitTft240320+(vx*2)+vy*(SCR_XSIZE_TFT_240320*2);
	rLCDSADDR1= ( (addr>>22)<<21 ) | M5D(addr>>1);
	rLCDSADDR2= M5D(((addr+(SCR_XSIZE_TFT_240320*LCD_YSIZE_TFT_240320*2))>>1));
	CLR_IF();
    break;

    case MODE_TFT_1BIT_640480:
    	SET_IF();
	#if (LCD_XSIZE_TFT_640480<512)
    	    while((rLCDCON1>>18)<=1); // if x<512
	#else	
    	    while((rLCDCON1>>18)==0); // if x>512 ((12+4)*32) 
	#endif
        addr=(U32)frameBuffer1BitTft640480+(vx/8)+vy*(SCR_XSIZE_TFT_640480/8);
	rLCDSADDR1= ( (addr>>22)<<21 ) | M5D(addr>>1);
	rLCDSADDR2= M5D( ((addr+(SCR_XSIZE_TFT_640480*LCD_YSIZE_TFT_640480/8))>>1) );
	CLR_IF();
    break;

    case MODE_TFT_8BIT_640480:
    	SET_IF(); 
	#if (LCD_XSIZE_TFT_640480<64)
    	    while((rLCDCON1>>18)<=1); // if x<64
	#else	
	    while((rLCDCON1>>18)==0); // if x>64
	#endif
        addr=(U32)frameBuffer8BitTft640480+(vx/1)+vy*(SCR_XSIZE_TFT_640480/1);
	rLCDSADDR1= ( (addr>>22)<<21 ) | M5D(addr>>1);
	rLCDSADDR2= M5D(((addr+(SCR_XSIZE_TFT_640480*LCD_YSIZE_TFT_640480))>>1));
	CLR_IF();
    break;

    case MODE_TFT_16BIT_640480:
    	SET_IF(); 
	#if (LCD_XSIZE_TFT_640480<32)
    	    while((rLCDCON1>>18)<=1); // if x<32
	#else	
    	    while((rLCDCON1>>18)==0); // if x>32
	#endif
        addr=(U32)frameBuffer16BitTft640480+(vx*2)+vy*(SCR_XSIZE_TFT_640480*2);
	rLCDSADDR1= ( (addr>>22)<<21 ) | M5D(addr>>1);
	rLCDSADDR2= M5D(((addr+(SCR_XSIZE_TFT_640480*LCD_YSIZE_TFT_640480*2))>>1));
	CLR_IF();
    break;

    case MODE_TFT_24BIT_640480:
    	SET_IF(); 
	#if (LCD_XSIZE_TFT_640480<16)
    	    while((rLCDCON1>>18)<=1); // if x<16
	#else	
    	    while((rLCDCON1>>18)==0); // if x>16
	#endif
        addr=(U32)frameBuffer24BitTft640480+(vx*4)+vy*(SCR_XSIZE_TFT_640480*4);
	rLCDSADDR1= ( (addr>>22)<<21 ) | M5D(addr>>1);
	rLCDSADDR2= M5D(((addr+(SCR_XSIZE_TFT_640480*LCD_YSIZE_TFT_640480*4))>>1));
	CLR_IF();
    break;

    case MODE_TFT_1BIT_800600:
    	SET_IF();
	#if (LCD_XSIZE_TFT_800600<512)
    	    while((rLCDCON1>>18)<=1); // if x<512
	#else	
    	    while((rLCDCON1>>18)==0); // if x>512 ((12+4)*32) 
	#endif
        addr=(U32)frameBuffer1BitTft800600+(vx/8)+vy*(SCR_XSIZE_TFT_800600/8);
	rLCDSADDR1= ( (addr>>22)<<21 ) | M5D(addr>>1);
	rLCDSADDR2= M5D( ((addr+(SCR_XSIZE_TFT_800600*LCD_YSIZE_TFT_800600/8))>>1) );
	CLR_IF();
    break;

    case MODE_TFT_8BIT_800600:
    	SET_IF(); 
	#if (LCD_XSIZE_TFT_800600<64)
    	    while((rLCDCON1>>18)<=1); // if x<64
	#else	
	    while((rLCDCON1>>18)==0); // if x>64
	#endif
        addr=(U32)frameBuffer8BitTft800600+(vx/1)+vy*(SCR_XSIZE_TFT_800600/1);
	rLCDSADDR1= ( (addr>>22)<<21 ) | M5D(addr>>1);
	rLCDSADDR2= M5D(((addr+(SCR_XSIZE_TFT_800600*LCD_YSIZE_TFT_800600))>>1));
	CLR_IF();
    break;

    case MODE_TFT_16BIT_800600:
    	SET_IF(); 
	#if (LCD_XSIZE_TFT_800600<32)
    	    while((rLCDCON1>>18)<=1); // if x<32
	#else	
    	    while((rLCDCON1>>18)==0); // if x>32
	#endif
        addr=(U32)frameBuffer16BitTft800600+(vx*2)+vy*(SCR_XSIZE_TFT_800600*2);
	rLCDSADDR1= ( (addr>>22)<<21 ) | M5D(addr>>1);
	rLCDSADDR2= M5D(((addr+(SCR_XSIZE_TFT_800600*LCD_YSIZE_TFT_800600*2))>>1));
	CLR_IF();
    break;

    default:
    break;
    }   
}    
    
