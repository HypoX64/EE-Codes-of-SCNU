/* 包含文件 */
#include "def.h"
#include "2410lib.h"
#include "option.h"
#include "2410addr.h"
#include "interrupt.h"

/* 函数声明 */
static void Dma0Done() __attribute__ ((interrupt("IRQ")));
static void Dma1Done() __attribute__ ((interrupt("IRQ")));
static void Dma2Done() __attribute__ ((interrupt("IRQ")));
static void Dma3Done() __attribute__ ((interrupt("IRQ")));
void DMA_M2M(int ch,int srcAddr,int dstAddr,int tc,int dsz,int burst);
void Test_DMA(void);

/* DMA特殊功能寄存器 */
typedef struct tagDMA
{
    volatile U32 DISRC;	    //0x0     DMA初始源寄存器
    volatile U32 DISRCC;    //0x4     DMA初始源控制寄存器
    volatile U32 DIDST;	    //0x8     DMA初始目的寄存器
    volatile U32 DIDSTC;    //0xc     DMA初始目的控制寄存器
    volatile U32 DCON;	    //0x10    DMA控制寄存器
    volatile U32 DSTAT;	    //0x14    DMA状态寄存器
    volatile U32 DCSRC;	    //0x18    当前源寄存器
    volatile U32 DCDST;	    //0x1c    当前目的寄存器
    volatile U32 DMASKTRIG; //0x20    DMA掩码触发寄存器
}DMA;

static volatile int dmaDone;

/********************************************************************
// Function name	: Main
// Description	    : JXARM9-2410 DMA操作实验主程序
//                    实现功能：
//                        实现DMA方式内存到内存的拷贝动作，修改DMA设置
//                        并比较其工作效率，实验包括：
//                        DMA0-DMA3
// Return type		: void
// Argument         : void
*********************************************************************/
void Main(void)
{
	/* 配置系统时钟 */
    ChangeClockDivider(1,1);          // 1:2:4    
    ChangeMPllValue(0xa1,0x3,0x1);    // FCLK=202.8MHz  
    
	/* 中断初始化 */
    Isr_Init();
    /* 初始化端口 */
    Port_Init();

    /* 初始化串口 */
    Uart_Init(0,115200);
    Uart_Select(0);
    
    /* 打印提示信息 */
	PRINTF("\n---DMA操作实验主程序---\n");
	PRINTF("\n请将UART0与PC串口进行连接，然后启动超级终端程序(115200, 8, N, 1)\n");
	PRINTF("\n开始DMA测试\n");
	
    /* 开始DMA测试 */
    Test_DMA();
    
    PRINTF("\nDMA测试结束\n");
	while(1)
	{
	}
}

void Test_DMA(void)
{
    //DMA Ch 0
    DMA_M2M(0,_NONCACHE_STARTADDRESS,_NONCACHE_STARTADDRESS+0x800000,0x80000,0,0); //byte,single
    DMA_M2M(0,_NONCACHE_STARTADDRESS,_NONCACHE_STARTADDRESS+0x800000,0x40000,1,0); //halfword,single
    DMA_M2M(0,_NONCACHE_STARTADDRESS,_NONCACHE_STARTADDRESS+0x800000,0x20000,2,0); //word,single
    DMA_M2M(0,_NONCACHE_STARTADDRESS,_NONCACHE_STARTADDRESS+0x800000,0x20000,0,1); //byte,burst
    DMA_M2M(0,_NONCACHE_STARTADDRESS,_NONCACHE_STARTADDRESS+0x800000,0x10000,1,1); //halfword,burst
    DMA_M2M(0,_NONCACHE_STARTADDRESS,_NONCACHE_STARTADDRESS+0x800000, 0x8000,2,1); //word,burst

    //DMA Ch 1
    DMA_M2M(1,_NONCACHE_STARTADDRESS,_NONCACHE_STARTADDRESS+0x800000,0x80000,0,0); //byte,single
    DMA_M2M(1,_NONCACHE_STARTADDRESS,_NONCACHE_STARTADDRESS+0x800000,0x40000,1,0); //halfword,single
    DMA_M2M(1,_NONCACHE_STARTADDRESS,_NONCACHE_STARTADDRESS+0x800000,0x20000,2,0); //word,single
    DMA_M2M(1,_NONCACHE_STARTADDRESS,_NONCACHE_STARTADDRESS+0x800000,0x20000,0,1); //byte,burst
    DMA_M2M(1,_NONCACHE_STARTADDRESS,_NONCACHE_STARTADDRESS+0x800000,0x10000,1,1); //halfword,burst
    DMA_M2M(1,_NONCACHE_STARTADDRESS,_NONCACHE_STARTADDRESS+0x800000, 0x8000,2,1); //word,burst

    //DMA Ch 2
    DMA_M2M(2,_NONCACHE_STARTADDRESS,_NONCACHE_STARTADDRESS+0x800000,0x80000,0,0); //byte,single
    DMA_M2M(2,_NONCACHE_STARTADDRESS,_NONCACHE_STARTADDRESS+0x800000,0x40000,1,0); //halfword,single
    DMA_M2M(2,_NONCACHE_STARTADDRESS,_NONCACHE_STARTADDRESS+0x800000,0x20000,2,0); //word,single
    DMA_M2M(2,_NONCACHE_STARTADDRESS,_NONCACHE_STARTADDRESS+0x800000,0x20000,0,1); //byte,burst
    DMA_M2M(2,_NONCACHE_STARTADDRESS,_NONCACHE_STARTADDRESS+0x800000,0x10000,1,1); //halfword,burst
    DMA_M2M(2,_NONCACHE_STARTADDRESS,_NONCACHE_STARTADDRESS+0x800000, 0x8000,2,1); //word,burst

    //DMA Ch 3
    DMA_M2M(3,_NONCACHE_STARTADDRESS,_NONCACHE_STARTADDRESS+0x800000,0x80000,0,0); //byte,single
    DMA_M2M(3,_NONCACHE_STARTADDRESS,_NONCACHE_STARTADDRESS+0x800000,0x40000,1,0); //halfword,single
    DMA_M2M(3,_NONCACHE_STARTADDRESS,_NONCACHE_STARTADDRESS+0x800000,0x20000,2,0); //word,single
    DMA_M2M(3,_NONCACHE_STARTADDRESS,_NONCACHE_STARTADDRESS+0x800000,0x20000,0,1); //byte,burst
    DMA_M2M(3,_NONCACHE_STARTADDRESS,_NONCACHE_STARTADDRESS+0x800000,0x10000,1,1); //halfword,burst
    DMA_M2M(3,_NONCACHE_STARTADDRESS,_NONCACHE_STARTADDRESS+0x800000, 0x8000,2,1); //word,burst   
}
/********************************************************************
// Function name	: DMA_M2M
// Description	    : DMA方式内存拷贝
// Return type		: void
// Argument         : int ch:DMA通道   0-DMA0, 1-DMA1, 2-DMA2, 3-DMA3
// Argument         : int srcAddr:源地址
// Argument         : int dstAddr:目的地址
// Argument         : int tc:初始传输计数值
// Argument         : int dsz:传输数据宽度  0-1字节 1-2字节 2-3字节
// Argument         : int burst:自动传输的传输宽度  0-单元传输（一个字节）  1-突发模式传输（四个字节）
*********************************************************************/
void DMA_M2M(int ch,int srcAddr,int dstAddr,int tc,int dsz,int burst)
{
    int i,time;
    volatile U32 memSum0=0,memSum1=0;
    DMA *pDMA;
    int length;
    
    length=tc*(burst ? 4:1)*((dsz==0)+(dsz==1)*2+(dsz==2)*4);
    
    PRINTF("[DMA%d MEM2MEM Test]\n",ch);

    switch(ch)
    {
    case 0:
    	Irq_Request(IRQ_DMA0, Dma0Done);
    	Irq_Enable(IRQ_DMA0);
    	pDMA=(void *)0x4b000000;
    	break;
    case 1:
    	Irq_Request(IRQ_DMA1, Dma1Done);
    	Irq_Enable(IRQ_DMA1);
    	pDMA=(void *)0x4b000040;
    	break;
    case 2:
    	Irq_Request(IRQ_DMA2, Dma2Done);
    	Irq_Enable(IRQ_DMA2);
    	pDMA=(void *)0x4b000080;
	break;
    case 3:
    	Irq_Request(IRQ_DMA3, Dma3Done);
    	Irq_Enable(IRQ_DMA3);
       	pDMA=(void *)0x4b0000c0;
        break;
    }
                                                                                                                            
    PRINTF("DMA%d %8xh->%8xh,size=%xh(tc=%xh),dsz=%d,burst=%d\n",ch,
    		srcAddr,dstAddr,length,tc,dsz,burst);

    PRINTF("Initialize the src.\n");
    
    for(i=srcAddr;i<(srcAddr+length);i+=4)
    {
    	*((U32 *)i)=i^0x55aa5aa5;
    	memSum0+=i^0x55aa5aa5;
    }

    PRINTF("DMA%d start\n",ch);
    
    dmaDone=0;
    
    pDMA->DISRC=srcAddr;
    pDMA->DISRCC=(0<<1)|(0<<0); // inc,AHB
    pDMA->DIDST=dstAddr;
    pDMA->DIDSTC=(0<<1)|(0<<0); // inc,AHB
    pDMA->DCON=tc|(1<<31)|(1<<30)|(1<<29)|(burst<<28)|(1<<27)|\
    	        (0<<23)|(1<<22)|(dsz<<20)|(tc);
    		//HS,AHB,TC interrupt,whole, SW request mode,relaod off
    pDMA->DMASKTRIG=(1<<1)|1; //DMA on, SW_TRIG

    Timer_Start(3);//128us resolution	      
    while(dmaDone==0);
    time=Timer_Stop();
    
    PRINTF("DMA transfer done. time=%f, %fMB/S\n",(float)time/ONESEC3,
        length/((float)time/ONESEC3)/1000000.);

   	Irq_Disable(IRQ_DMA0);
   	Irq_Disable(IRQ_DMA1);
   	Irq_Disable(IRQ_DMA2);
   	Irq_Disable(IRQ_DMA3);
    
    for(i=dstAddr;i<dstAddr+length;i+=4)
    {
    	memSum1+=*((U32 *)i)=i^0x55aa5aa5;
    }
    
    PRINTF("memSum0=%x,memSum1=%x\n",memSum0,memSum1);
    if(memSum0==memSum1)
    	PRINTF("DMA test result--------------------------------------O.K.\n");
    else 
    	PRINTF("DMA test result--------------------------------------ERROR!!!\n");

}


static void Dma0Done(void)
{
    Irq_Clear(IRQ_DMA0);
    dmaDone=1;
}

static void Dma1Done(void)
{
    Irq_Clear(IRQ_DMA1);
    dmaDone=1;
}

static void Dma2Done(void)
{
    Irq_Clear(IRQ_DMA2);
    dmaDone=1;
}

static void Dma3Done(void)
{
    Irq_Clear(IRQ_DMA3);
    dmaDone=1;
}

