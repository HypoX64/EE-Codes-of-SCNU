#ifndef __GPS_H_
#define __GPS_H_

/*******************************************************************************
 *
 * defines.
 *
 ******************************************************************************/
#define UInt32     unsigned int
#define Int16      short
#define UInt16     unsigned short
#define UInt8      unsigned char
#define Boolean    int

#define false      0
#define true       1

/*******************************************************************************
 *
 * Variables.
 *
 ******************************************************************************/
typedef struct GPSINFO{
	int    bIsGPGGA;                 // 1��ʾΪGPGGA���0Ϊ��GPGGA���������������
	double latitude;                 // γ��
	UInt8  latNS;                    // 'N'��γ  'S'��γ
	double longitud;                 // ����
	UInt8  lgtEW;                    // 'E'����  'W'����
	UInt8  hour, bjhour, min, sec, secFrac;  // ��������ʱ�䣬bjhourΪת����ı���ʱ��
	UInt8  satellites;               // ������
	Int16  altitude;                 // �߶�
	UInt8  altUnit;                  // M��
}GPSINFO;

/*******************************************************************************
 *
 * Functions.
 *
 ******************************************************************************/
void GPSInit(void);
void GPSReceive(GPSINFO * pinfo, UInt8* pStreamIn, UInt32 len);

#endif

