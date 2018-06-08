/* �����ļ� */
#include "def.h"
#include "2410lib.h"
#include "option.h"
#include "2410addr.h"
#include "interrupt.h"

/* �������� */
void test_pwm();

/********************************************************************
// Function name	: Main
// Description	    : JXARM9-2410 PWMʵ��������
//                    ʵ�ֹ��ܣ�
//                        ʵ��JXARM9-2410 PWM��ʽ���Ʒ�����
// Return type		: void
// Argument         : void
*********************************************************************/
void Main(void)
{
	unsigned char data[6] = {0, 1, 2, 3, 4, 5};

	/* ����ϵͳʱ�� */
    ChangeClockDivider(1,1);          // 1:2:4    
    ChangeMPllValue(0xa1,0x3,0x1);    // FCLK=202.8MHz  
    
    /* ��ʼ���˿� */
    Port_Init();
    
    /* ��ʼ������ */
    Uart_Init(0,115200);
    Uart_Select(0);
    
    /* ��ӡ��ʾ��Ϣ */
	PRINTF("\n---���������Գ���---\n");
	
	/* �˿����� */
	rGPBUP  = rGPBUP  & ~(0x1f)     | 0x1f;         //GPB4 ~ 0
    rGPBCON = rGPBCON & ~(0x3ff)    | 0x2aa;        //Function Setting TCLK0, TOUT3 ~ 0   
    rGPGUP  = rGPGUP  & ~(0x800)    | 0x800;        //GPG11
    rGPGCON = rGPGCON & ~(0xc00000) | 0xc00000;     //TCLK1
    rGPHUP  = rGPHUP  & ~(0x200)    | 0x200;        //GPH9
    rGPHCON = rGPHCON & ~(0x3<<18)  | (0x2<<18);    //CLKOUT0    
    rMISCCR = rMISCCR & ~(0xf0)     | 0x40;         //Select PCLK with CLKOUT0
    
    /* ��ʼ���� */
	test_pwm();
	while(1);
}

/*****************************************************************************
// Function name	: test_pwm
// Description	    : ����PWM��ͨ���������������
// Return type		: int
// Argument         : void
*****************************************************************************/
void test_pwm()
{
	int index, rate ;
	unsigned short div;
	int freq;
	
	/* ���ö�ʱ����Ԥ��Ƶ��ֵ:TIME0/1=255, TIME2/3=0, TIME4/5=0				*/
    rTCFG0=0xFF; 	
    
    /* ���ö�ʱ���Ĺ���ģʽ:�ж�ģʽ,���÷�Ƶ��ֵ:TIME0Ϊ1/4������Ϊ1/2		*/
    rTCFG1=0x1;	 	

    /* ������壺Ƶ�ʴ�4000HZ��14000HZ, ʹ��2/3��ռ�ձ�						*/
	for ( freq = 500; freq < 14000; freq+=500 )
	{
		div = (PCLK/256/4)/freq;
    	rTCON=0x0;
     	rTCNTB0= div;
   		rTCMPB0= (2*div)/3;
		rTCON=0xa;						/* �ֹ�װ�ض�ʱ���ļ���ֵ			*/
    	rTCON=0x9;						/* ������ʱ����������ģʽ����		*/
    	for( index = 0; index < 800000; index++);
    	rTCON=0x0;						/* ��ʱ��ֹͣ��ʱ��					*/
	}

    /* ������壺Ƶ��1000HZ, ʹ��1/100 - 95/100��ռ�ձ�						*/
	div = (PCLK/256/4)/1000;
    for ( rate = 1; rate < 100; rate += 5 )
    {
    	rTCNTB0= div;
		rTCMPB0= (rate*div)/100;		/* �޸�ռ�ձ�						*/
		rTCON=0xa;						/* �ֹ�װ�ض�ʱ���ļ���ֵ			*/
	    rTCON=0x9;						/* ������ʱ���������ڴ���			*/
	    for( index = 0; index < 800000; index++);
	    rTCON=0x0;
    }
}
