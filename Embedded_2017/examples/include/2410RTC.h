//====================================================================
// File Name : 2410RTC.h
// Function  : S3C2410 RTC Head file
// Program   : Shin, On Pil (SOP)
// Date      : May 06, 2002
// Version   : 0.0
// History
//   0.0 : Programming start (March 11, 2002) -> SOP
//====================================================================

#ifndef __2410RTC_H__
#define __2410RTC_H__

void Display_Rtc(void);
void RndRst_Rtc(void);
void Test_Rtc_Alarm(void);
void Rtc_Init(void);
void Rtc_TimeSet(void);
void Test_Rtc_Tick(void);
void EINT0_int() __attribute__ ((interrupt("IRQ")));
void rtc_tick_isr() __attribute__ ((interrupt("IRQ")));
void rtc_int_isr() __attribute__ ((interrupt("IRQ")));

#define TESTYEAR    (0x01)
#define TESTMONTH   (0x12)
#define TESTDATE    (0x31)
#define TESTDAY     (0x02)      //SUN:1 MON:2 TUE:3 WED:4 THU:5 FRI:6 SAT:7   
#define TESTHOUR    (0x23)
#define TESTMIN     (0x59)
#define TESTSEC     (0x59)

#define TESTYEAR2   (0x02)
#define TESTMONTH2  (0x01)
#define TESTDATE2   (0x01)
#define TESTDAY2    (0x03)      //SUN:1 MON:2 TUE:3 WED:4 THU:5 FRI:6 SAT:7   
#define TESTHOUR2   (0x00)
#define TESTMIN2    (0x00)
#define TESTSEC2    (0x00)

#endif  //__2410RTC_H__
