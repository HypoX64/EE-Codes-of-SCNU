//ioport unsigned port100e;

/* functions */
void delay(int count);

// ����ģʽ��ת����
unsigned char pluse_table[] = 
{
	0x05, 0x09, 0x0a, 0x06,
};

void Main(void)
{
	int row = 0;
	
	for( ; ; )
	{
		if( row == 4 ) row = 0;
		(*(volatile unsigned char*)0x28000006) = pluse_table[row++];
		delay(20);
	}
}

/*****************************************************************************
// Function name	: delay
// Description	    : ��ʱ�ӳ���
// Return type		: void
// Argument         : count,��ʱ����ֵ
*****************************************************************************/
void delay( int count )
{
	int cnt;
	
	for( count = count; count>0; count--)
		for( cnt = 0; cnt < 100; cnt++);
}

