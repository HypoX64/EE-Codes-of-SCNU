//====================================================================
// File Name : 2410iis.h
// Function  : S3C2410 
// Program   : Shin, On Pil (SOP)
// Date      : September 30, 2002
// Version   : 0.0
// History
//   0.0 : Programming start (March 06, 2002) -> SOP
//   0.1 : Added Slave mode Test Program(July 24, 2002) -> KWT (Tark)
//====================================================================

#ifndef __2410IIS_H__
#define __2410IIS_H__

#ifdef __cplusplus
extern "C" {
#endif

void Init1341(char);
void Test_Iis(void);
void Record_Iis(void);
void Iis_Rx(void);
void Iis_Tx(void);

#ifdef __cplusplus
}
#endif

#endif    //__2410IIS_H__
