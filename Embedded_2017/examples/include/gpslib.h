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
	int    bIsGPGGA;                 // 1表示为GPGGA命令，0为非GPGGA命令，仅解析该命令
	double latitude;                 // 纬度
	UInt8  latNS;                    // 'N'北纬  'S'南纬
	double longitud;                 // 经度
	UInt8  lgtEW;                    // 'E'东经  'W'西经
	UInt8  hour, bjhour, min, sec, secFrac;  // 格林威治时间，bjhour为转换后的北京时间
	UInt8  satellites;               // 卫星数
	Int16  altitude;                 // 高度
	UInt8  altUnit;                  // M米
}GPSINFO;

/*******************************************************************************
 *
 * Functions.
 *
 ******************************************************************************/
void GPSInit(void);
void GPSReceive(GPSINFO * pinfo, UInt8* pStreamIn, UInt32 len);

#endif

