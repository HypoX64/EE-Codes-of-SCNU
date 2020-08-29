// Comm.h: interface for the CComm class.
//
//////////////////////////////////////////////////////////////////////

#ifndef GPRS_H__
#define GPRS_H__

#define GPRS_CONTROL_ADDR       0x28000004

#define GPRS_CONTROL_MASK_SLEEP  (1<<2)
#define GPRS_CONTROL_MASK_UART   (3<<0)

#define GPRS_PWR_ON  1   // 开启
#define GPRS_PWR_OFF 0   // 关闭

#define GPRS_ERR     1   // 错误
#define GPRS_OK      0   // 正确

// 接收命令结果
enum 
{
	AT_RECV_MSG_NULL,    // 无有效数据
	AT_RECV_MSG_OK,      // "OK"
	AT_RECV_MSG_CMTI,    // "CMTI"
	AT_RECV_MSG_CMGR,    // "+CMGR"
	AT_RECV_MSG_RING,    // "RING"
	AT_RECV_GET_MSG,     // ">"
	AT_RECV_MSG_NO_CARRIER, // "NO CARRIER"
	AT_RECV_MSG_ERROR,   // "ERROR"
}; 

// 用户信息编码方式
#define GSM_7BIT		0
#define GSM_8BIT		4
#define GSM_UCS2		8

#define BOOL int
#define TRUE   1
#define FALSE  0
#define WCHAR  short

#define GPRS_RECV_CMD_MAX_BUF 1024

// 短消息参数结构，编码/解码共用
// 其中，字符串以0结尾
typedef struct {
	char SCA[16];			// 短消息服务中心号码(SMSC地址)
	char TPA[16];			// 目标号码或回复号码(TP-DA或TP-RA)
	char TP_PID;			// 用户信息协议标识(TP-PID)
	char TP_DCS;			// 用户信息编码方式(TP-DCS)
	char TP_SCTS[16];		// 服务时间戳字符串(TP_SCTS), 接收时用到
	char TP_UD[161];		// 原始用户信息(编码前或解码后的TP-UD)
	char index;				// 短消息序号，在读取时用到
} SM_PARAM;

// SMS
int gprsEncodePdu(const SM_PARAM* pSrc, char* pDst);
int gprsDecodePdu(const char* pSrc, SM_PARAM* pDst);
BOOL gprsSendMessage(const SM_PARAM* pSrc);

// GPRS
void gprs_init();
void gprs_send_cmd(char *cmdstring);
int gprs_recv_cmd(char *cmd);

#endif // !defined(GPRS_H__)
