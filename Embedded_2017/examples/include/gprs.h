// Comm.h: interface for the CComm class.
//
//////////////////////////////////////////////////////////////////////

#ifndef GPRS_H__
#define GPRS_H__

#define GPRS_CONTROL_ADDR       0x28000004

#define GPRS_CONTROL_MASK_SLEEP  (1<<2)
#define GPRS_CONTROL_MASK_UART   (3<<0)

#define GPRS_PWR_ON  1   // ����
#define GPRS_PWR_OFF 0   // �ر�

#define GPRS_ERR     1   // ����
#define GPRS_OK      0   // ��ȷ

// ����������
enum 
{
	AT_RECV_MSG_NULL,    // ����Ч����
	AT_RECV_MSG_OK,      // "OK"
	AT_RECV_MSG_CMTI,    // "CMTI"
	AT_RECV_MSG_CMGR,    // "+CMGR"
	AT_RECV_MSG_RING,    // "RING"
	AT_RECV_GET_MSG,     // ">"
	AT_RECV_MSG_NO_CARRIER, // "NO CARRIER"
	AT_RECV_MSG_ERROR,   // "ERROR"
}; 

// �û���Ϣ���뷽ʽ
#define GSM_7BIT		0
#define GSM_8BIT		4
#define GSM_UCS2		8

#define BOOL int
#define TRUE   1
#define FALSE  0
#define WCHAR  short

#define GPRS_RECV_CMD_MAX_BUF 1024

// ����Ϣ�����ṹ������/���빲��
// ���У��ַ�����0��β
typedef struct {
	char SCA[16];			// ����Ϣ�������ĺ���(SMSC��ַ)
	char TPA[16];			// Ŀ������ظ�����(TP-DA��TP-RA)
	char TP_PID;			// �û���ϢЭ���ʶ(TP-PID)
	char TP_DCS;			// �û���Ϣ���뷽ʽ(TP-DCS)
	char TP_SCTS[16];		// ����ʱ����ַ���(TP_SCTS), ����ʱ�õ�
	char TP_UD[161];		// ԭʼ�û���Ϣ(����ǰ�������TP-UD)
	char index;				// ����Ϣ��ţ��ڶ�ȡʱ�õ�
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
