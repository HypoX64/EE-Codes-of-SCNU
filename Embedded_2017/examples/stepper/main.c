//ioport unsigned port100e;

/* functions */
void delay(int count);

// 整步模式正转脉冲
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
// Description	    : 延时子程序
// Return type		: void
// Argument         : count,延时的数值
*****************************************************************************/
void delay( int count )
{
	int cnt;
	
	for( count = count; count>0; count--)
		for( cnt = 0; cnt < 100; cnt++);
}

