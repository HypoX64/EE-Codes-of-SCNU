/* �����ļ� */
#include "def.h"
#include "2410lib.h"
#include "option.h"
#include "2410addr.h"
#include "interrupt.h"

/********************************************************************
// Function name	: Main
// Description	    : JXARM9-2410 A/D����ʵ��������
//                    ʵ�ֹ��ܣ�
//                        ʵ��JXRAM9-2410��ģ��ת��
//                        JXARM9-2410 UART0 <==> PC COM
// Return type		: void
// Argument         : void
*********************************************************************/
void Main(void)
{
	/* ����ϵͳʱ�� */
    ChangeClockDivider(1,1);          // 1:2:4    
    ChangeMPllValue(0xa1,0x3,0x1);    // FCLK=202.8MHz  
    
    /* ��ʼ���˿� */
    Port_Init();
    
    /* ��ʼ������ */
    Uart_Init(0,115200);
    Uart_Select(0);
    
    /* ��ӡ��ʾ��Ϣ */
	PRINTF("\n---AD��������---\n");
	PRINTF("\n�뽫UART0��PC���ڽ������ӣ�Ȼ�����������ն˳���(115200, 8, N, 1)\n");
	PRINTF("\n�����ڿ�ʼ�����ڳ����ն��Ͽ�������ֵ��������ťAIN2��AIN3�ı�ģ������\n");
	
    /* ��ʼ���� */
    Test_Adc();
	while(1)
	{
	}
}

#define ADC_FREQ 2500000

int ReadAdc(int ch);	        //Return type is int, Declare Prototype function

//==================================================================================
void Test_Adc(void)
{
    int i;
    int a0=0,a1=0,a2=0,a3=0,a4=0,a5=0,a6=0,a7=0; //Initialize variables
    
    PRINTF("----------AD����--------\n");
    PRINTF("����AIN0, AIN1��ť�ı�ģ������,������˳�\n");
        
    while(1)
    {
	    a0=Adc_Get_Data(0, ADC_FREQ);
	    a1=Adc_Get_Data(1, ADC_FREQ);

	    PRINTF("\rAIN0: %04d AIN1: %04d", a0,a1);
    }
    rADCCON=(0<<14)|(19<<6)|(7<<3)|(1<<2);  //stand by mode to reduce power consumption	

	PRINTF("\n");
    PRINTF("--------AD���Խ���------\n\n");
}







