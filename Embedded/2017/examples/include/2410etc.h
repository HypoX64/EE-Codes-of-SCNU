//====================================================================
// File Name : 2410etc.h
// Function  : S3C2410 Read Page Mode, Nonaligned
// Program   : Shin, On Pil (SOP)
// Date      : March 14, 2002
// Version   : 0.0
// History
//   0.0 : Programming start (March 14, 2002) -> SOP
//====================================================================

#ifndef __2410ETC_H__
#define __2410ETC_H__

void SdramPseudoRefresh(void);
void WriteMemory(void);
void ReadMemory(void);
void ReadPageMode(void);
void Test_NonalignedAccess(void);

#endif  //__2410ETC_H__
