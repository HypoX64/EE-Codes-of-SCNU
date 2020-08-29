//====================================================================
// File Name : option.h
// Function  : S3C2410 
// Program   : Shin, On Pil (SOP)
// Date      : January 03, 2003
// Version   : 0.0
// History
//   0.0 : Programming start (February 20,2002) -> SOP
//====================================================================

#ifndef __OPTION_H__
#define __OPTION_H__

//#define FCLK 50700000
//#define HCLK 50700000
//#define PCLK 50700000
//#define UCLK 50700000

//#define FCLK 101250000      //SDRAM 2.5V use
//#define HCLK (FCLK/2)
//#define PCLK (FCLK/2)
//#define UCLK PCLK

//#define FCLK 135428571
//#define FCLK 200000000
#define FCLK 202800000
//#define FCLK 220000000
//#define FCLK 226000000
//#define FCLK 237000000
//#define FCLK 266000000


#define HCLK (FCLK/2)
#define PCLK (FCLK/4)
#define UCLK PCLK

// BUSWIDTH : 16,32
#define BUSWIDTH    (32)

//64MB
// 0x30000000 ~ 0x30ffffff : Download Area (16MB) Cacheable
// 0x31000000 ~ 0x33feffff : Non-Cacheable Area
// 0x33ff0000 ~ 0x33ff47ff : Heap & RW Area
// 0x33ff4800 ~ 0x33ff7fff : FIQ ~ User Stack Area
// 0x33ff8000 ~ 0x33fffeff : Not Used Area
// 0x33ffff00 ~ 0x33ffffff : Exception & ISR Vector Table

#define _RAM_STARTADDRESS       0x30000000
#define _NONCACHE_STARTADDRESS	0x31000000
#define _ISR_STARTADDRESS       0x33ffff00     
#define _MMUTT_STARTADDRESS     0x33ff8000
#define _STACK_BASEADDRESS      0x33ff8000
#define HEAPEND                 0x33ff0000

//If you use ADS1.x, please define ADS10
//#define ADS10 TRUE

// note: makefile,option.a should be changed

#endif    //__OPTION_H__
