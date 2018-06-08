#include "tftpput.h"
#include "hexput.h"
#include "tftp.h"
 
static unsigned char *buf;
int data_len;
int tftp_put_ok = 0;
unsigned long tftp_buff_addr;

int tftp_put_begin(void)
{
	tftp_printf("\nTFTP download to 0x%x...\r\n\r", tftp_buff_addr);
	buf = (unsigned char *)tftp_buff_addr;
	data_len = 0;
	return 0;
}

int tftp_put(unsigned char *data, int len)
{
	static int count = 0;

	count += len;
	if (count > 32 * 1024) 
	{
		tftp_printf(".");
		count = 0;
	}

	memcpy(buf + data_len, data, len);
	data_len += len;
	return 0;
}

int update_bios(unsigned char *bios, int size)
{

	return 0;
}

int update_system_table(unsigned char *system_table, int size)
{
	return 0;
}

int update_firmware(unsigned char *firmware, int size)
{
	return 0;
}

int tftp_put_end(void)
{
	int ch;
	unsigned long l;

	tftp_printf("\rTFTP download complete\n");

	tftp_put_ok =1;
	return 0;
}
