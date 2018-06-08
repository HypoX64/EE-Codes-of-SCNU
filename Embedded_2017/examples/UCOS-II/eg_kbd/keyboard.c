#include <string.h>
#include "2410addr.h"
#include "2410lib.h"
#include "timer.h"
#include "interrupt.h"


#define RECV_CMD_MAX_BUF 2048
char recv_buf[RECV_CMD_MAX_BUF];
int  recv_read = 0;
int  recv_write = 0;

char key_recv_buf[RECV_CMD_MAX_BUF];
int  key_recv_read = 0;
int  key_recv_write = 0;

// ����ɨ��
int  timer1_count = 0;
enum KEYBOARD_SCAN_STATUS
{
	KEYBOARD_SCAN_FIRST,
	KEYBOARD_SCAN_SECOND,
	KEYBOARD_SCAN_THIRD,
	KEYBOARD_SCAN_FOURTH
};
int row = 0;
extern unsigned char output_0x10000000;
unsigned char 	ascii_key, input_key[4], input_key1[4], key_mask = 0x0F;
unsigned char*	keyboard_port_scan = (unsigned char*)0x10000000;
unsigned char*	keyboard_port_value = (unsigned char*)0x10000002;
int              keyboard_scan_status[4] = {
														KEYBOARD_SCAN_FIRST,
														KEYBOARD_SCAN_FIRST,
														KEYBOARD_SCAN_FIRST,
														KEYBOARD_SCAN_FIRST
													  };

char key_get_char(int row, int col)
{
	char key = 0;
	
	switch( row )
	{
	case 0:
		if((col & 0x01) == 0) key = '0'; 
		else if((col & 0x02) == 0) key = 'A'; 
		else if((col & 0x04) == 0) key = 'B'; 
		else if((col & 0x08) == 0) key = 'F'; 
		break;
	case 1:
		if((col & 0x01) == 0) key = '7'; 
		else if((col & 0x02) == 0) key = '8'; 
		else if((col & 0x04) == 0) key = '9';
		else if((col & 0x08) == 0) key = 'E';
		break;
	case 2:
		if((col & 0x01) == 0) key = '4'; 
		else if((col & 0x02) == 0) key = '5'; 
		else if((col & 0x04) == 0) key = '6'; 
		else if((col & 0x08) == 0) key = 'D'; 
		break;
	case 3:
		if((col & 0x01) == 0) key = '1'; 
		else if((col & 0x02) == 0) key = '2'; 
		else if((col & 0x04) == 0) key = '3'; 
		else if((col & 0x08) == 0) key = 'C'; 
		break;
	default:
		break;
	}
	
	return key;
}
/********************************************************************
// Function name	: recv_key
// Description	    : ����ȡ�ļ�ֵ���밴��������
// Return type		: void
// Argument         : int key
*********************************************************************/
void recv_key(int key)
{
	key_recv_buf[key_recv_write] = key;
	key_recv_write ++;
	if(key_recv_write >= RECV_CMD_MAX_BUF)
		key_recv_write = 0;
		
	if(key_recv_write == key_recv_read)
	{
		// ����������
		key_recv_read ++;
		if(key_recv_read >= RECV_CMD_MAX_BUF)
			key_recv_read = 0;
	}
}
/********************************************************************
// Function name	: Kbd_Scan
// Description	    : ��ʱ��1�жϷ����������ɨ����̣�ÿ��10msһ���ж�
// Return type		: void
// Argument         : void
*********************************************************************/
void Kbd_Scan(void)
{
	int loopcnt = row, bexit = 0;
	int temp;

	// ����ɨ��
	for( loopcnt = row; loopcnt < row + 4; loopcnt ++)
	{
		if(loopcnt >= 4)
			temp = loopcnt - 4;
		else
			temp = loopcnt;
		switch(keyboard_scan_status[temp])
		{
			case KEYBOARD_SCAN_FIRST:
				*keyboard_port_scan = output_0x10000000 & (~(0x00000001<<temp));        /*��row���õ͵�ƽ	*/
				keyboard_scan_status[temp] = KEYBOARD_SCAN_SECOND;
				bexit = 1;
				break;
			case KEYBOARD_SCAN_SECOND:
				input_key[temp] = (*keyboard_port_value) & key_mask;	/*����ȡ��һ��ɨ��ֵ*/
				if(input_key[temp] == key_mask)	
					keyboard_scan_status[temp] = KEYBOARD_SCAN_FIRST;		/* û�а���,�ص���ʼ״̬			*/
				else
				{
					keyboard_scan_status[temp] = KEYBOARD_SCAN_THIRD;		/* �а���		*/
					bexit = 1;
				}
				break;
			case KEYBOARD_SCAN_THIRD:
				if (((*keyboard_port_value) & key_mask) != input_key[temp]) 
					keyboard_scan_status[temp] = KEYBOARD_SCAN_FIRST;	
				else	
				{
					ascii_key = key_get_char(temp, input_key[temp]);
					keyboard_scan_status[temp] = KEYBOARD_SCAN_FOURTH;
					
					*keyboard_port_scan = output_0x10000000 & (~(0x00000001<<temp));        /*��row���õ͵�ƽ	*/
					bexit = 1;
				}
				break;
			case KEYBOARD_SCAN_FOURTH:
				input_key1[temp] = (*keyboard_port_value) & key_mask;	/*����ȡ��һ��ɨ��ֵ*/
				if(input_key1[temp] == key_mask)	
				{
					// get a key
					recv_key(ascii_key);					
					keyboard_scan_status[temp] = KEYBOARD_SCAN_FIRST;
				}else
				{
					*keyboard_port_scan = output_0x10000000 & (~(0x00000001<<temp));        /*��row���õ͵�ƽ	*/
					bexit = 1;
				}
				break;
		}			
		if(bexit)
			break;
	}
	
	row = temp;	
}

/********************************************************************
// Function name	: Key_GetKey
// Description	    : ����м����·��ؼ������򷵻�0
// Return type		: char
// Argument         : 
*********************************************************************/
char Key_GetKey()
{
	char ch;
	
	if(key_recv_write == key_recv_read)
	{
		/* no key found */
		ch = 0;
	}else
	{
		ch = key_recv_buf[key_recv_read];
		key_recv_read ++;
		if(key_recv_read >= RECV_CMD_MAX_BUF)
			key_recv_read = 0;
	}
	return ch;
}

/********************************************************************
// Function name	: Key_GetKeyPoll(��ѯ��ʽ)
// Description	    : ����м����·��ؼ������򷵻�0
// Return type		: char
// Argument         : 
*********************************************************************/
char Key_GetKeyPoll()
{
	int row;
	unsigned char 	ascii_key, input_key, input_key1, key_mask = 0x0F;
	
	for( row = 0; row < 4; row++)
	{
		*keyboard_port_scan = output_0x10000000 & (~(0x00000001<<row));        /*��row���õ͵�ƽ	*/

		Delay(3);								/*��ʱ				*/
		input_key = (*keyboard_port_value) & key_mask;	/*����ȡ��һ��ɨ��ֵ*/
			
		if(input_key == key_mask)	continue;		/* û�а���			*/
					
		/* ��ʱ���ٴλ�ȡɨ��ֵ��������ε�ֵ���ȣ�����Ϊ��һ������		*/
		Delay(3);
		if (((*keyboard_port_value) & key_mask) != input_key) continue;
			
		// �ȴ������ɿ�
		while(1)
		{
			*keyboard_port_scan = output_0x10000000 & (~(0x00000001<<row));        /*��row���õ͵�ƽ	*/
	
			Delay(3);
			input_key1 = (*keyboard_port_value) & key_mask;	/*����ȡ��һ��ɨ��ֵ*/
				
			if(input_key1 == key_mask)	break;		/* û�а���			*/
		}
		
		ascii_key = key_get_char(row, input_key);	/* ���				*/
			
		return ascii_key;					/* ��ʾ���			*/
	}
	return 0;
}

