//====================================================================
// File Name : 2410IIC.h
// Function  : S3C2410 IIC Test Program Head file
// Program   : Shin, On Pil (SOP)
// Date      : March 20, 2002
// Version   : 0.0
// History
//   0.0 : Programming start (March 11, 2002) -> SOP
//====================================================================

#ifndef __2410IIC_H__
#define __2410IIC_H__

#define WRDATA      (1)
#define POLLACK     (2)
#define RDDATA      (3)
#define SETRDADDR   (4)

#define IICBUFSIZE 0x20

void Test_Iic(void);
void Test_Iic2(void);
void Wr24C080(U32 slvAddr,U32 addr,U8 data);    
void Rd24C080(U32 slvAddr,U32 addr,U8 *data);   
void iic_write_24C08(U32 slvAddr,U32 addr,U8 data);   
void iic_read_24C08(U32 slvAddr,U32 addr,U8 *data);  
void iic_write_max5380(U32 slvAddr,U8 data);

void IicInt() __attribute__ ((interrupt("IRQ")));
void IicPoll(void);
void IicPoll1(void);
void Run_IicPoll(void);
void Run_IicPoll1(void);


#endif    //__2410IIC_H__
