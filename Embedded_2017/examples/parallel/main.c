#include "2410addr.h"
#include "2410lib.h"

#define LP_ADDR_CONTROL       0x28000000
#define LP_ADDR_STATUS        0x28000000
#define LP_ADDR_DATA          0x28000002

#define LP_nERROR  (1 << 3)//(1 << 4)
#define LP_SELECT  (1 << 4)//(1 << 3)
#define LP_PE      (1 << 5)//(1 << 2)
#define LP_BUSY    (1 << 6)//(1 << 1)
#define LP_nACK    (1 << 7)//(1 << 0)

#define LP_nSTROBE       (1 << 0)
#define LP_AUTOFEED      (1 << 1)
#define LP_nINIT         (1 << 2)
#define LP_nSELECT_IN    (1 << 3)

void printchar(unsigned char);
int lp_ctrl_value = LP_nSTROBE | LP_AUTOFEED | LP_nINIT;

void Main()
{
	char  test_data[]= "12345\n\n67890\n";
	char  *p_test_data;
	char  status;
	int i=0;
	
	/* 配置系统时钟 */
    ChangeClockDivider(1,1);          // 1:2:4    
    ChangeMPllValue(0xa1,0x3,0x1);    // FCLK=202.8MHz  
    
    /* 初始化端口 */
    Port_Init();
    
    /* 初始化串口 */
    Uart_Init(0,115200);
    Uart_Select(0);
    
    /* 打印提示信息 */
	PRINTF("\n---打印机测试程序---\n");
	PRINTF("任意键退出\n");

	p_test_data = test_data;

	/* 初始化 */
	*(unsigned char *)LP_ADDR_CONTROL = lp_ctrl_value;

	/* 打印字符串 */
	while(*p_test_data!=0)
	{
		i++;
		// wait for no busy.
		do
		{
			int KeySel;
			status = *((unsigned char *)LP_ADDR_STATUS);
			if(status & LP_PE)
				PRINTF("\r缺纸    ");
			else
				PRINTF("\r错误    ");
	    	
	    	KeySel = Uart_GetKey();
	    	if(KeySel == 0)
	    		continue;
	    	else
	    		goto OUT;
	    	Delay(1);
		}while(status & LP_BUSY);
		PRINTF("\r就绪    ");
		
		// send data
		*(unsigned char *)LP_ADDR_DATA = *p_test_data++;
		Delay(1);
		
		// send strobe
		lp_ctrl_value |= LP_nSTROBE;
		*(unsigned char *)LP_ADDR_CONTROL = lp_ctrl_value;
		Delay(1);
		lp_ctrl_value &= ~LP_nSTROBE;
		*(unsigned char *)LP_ADDR_CONTROL = lp_ctrl_value;
		Delay(1);
		lp_ctrl_value |= LP_nSTROBE;
		*(unsigned char *)LP_ADDR_CONTROL = lp_ctrl_value;
		Delay(1);

		// wait ack
		do
		{
			int KeySel;
			status = *((unsigned char *)LP_ADDR_STATUS);
			PRINTF("\r等待应答");
	    	
	    	KeySel = Uart_GetKey();
	    	if(KeySel == 0)
	    		continue;
	    	else
	    		goto OUT;
		}while(!(status & LP_nACK));
		PRINTF("\r应答    ");
	}
	
OUT:	
    PRINTF("\n-----打印机测试结束-----\n\n");
}

