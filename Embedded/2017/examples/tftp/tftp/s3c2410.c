#include "eth.h"
#include "s3c2410.h"


/*
 * Realtek 8019AS Ethernet
 * (C) Copyright 2002-2003
 * Xue Ligong(lgxue@hotmail.com),Wang Kehao, ESLAB, whut.edu.cn
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * This code works in 8bit mode.
 * If you need to work in 16bit mode, PLS change it!
 */

/* packet page register access functions */
void udelay(int count)
{
	while(count--)
	{
		int ncount = 5;
	}
}

static unsigned char get_reg (unsigned int regno)
{
	return (*(unsigned char *) regno);
}


static void put_reg (unsigned int regno, unsigned char val)
{
	*(volatile unsigned char *) regno = val;
}

static void eth_reset (void)
{
	unsigned char ucTemp;

	/* reset NIC */
	ucTemp = get_reg (RTL8019_RESET);
	put_reg (RTL8019_RESET, ucTemp);
	put_reg (RTL8019_INTERRUPTSTATUS, 0xff);
	udelay (200000);		/* wait for 2ms */
}

void rtl8019_eth_halt(void)
{
	put_reg (RTL8019_COMMAND, 0x01);
}

void rtl8019_get_enetaddr (unsigned char * addr)
{
	unsigned char i;
	unsigned char temp;
	
	eth_reset ();

	put_reg (RTL8019_COMMAND, RTL8019_REMOTEDMARD);
	put_reg (RTL8019_DATACONFIGURATION, 0x48);
	put_reg (RTL8019_REMOTESTARTADDRESS0, 0x00);
	put_reg (RTL8019_REMOTESTARTADDRESS1, 0x00);
	put_reg (RTL8019_REMOTEBYTECOUNT0, 12);
	put_reg (RTL8019_REMOTEBYTECOUNT1, 0x00);
	put_reg (RTL8019_COMMAND, RTL8019_REMOTEDMARD);
	ETH_DBG ("MAC: ");
	for (i = 0; i < 6; i++) {
		temp = get_reg (RTL8019_DMA_DATA);
		*addr++ = temp;
		temp = get_reg (RTL8019_DMA_DATA);
		ETH_DBG ("0x%x:", temp);
	}

	while ((!get_reg (RTL8019_INTERRUPTSTATUS) & 0x40));
	ETH_DBG ("\b \n");
	put_reg (RTL8019_REMOTEBYTECOUNT0, 0x00);
	put_reg (RTL8019_REMOTEBYTECOUNT1, 0x00);
	put_reg (RTL8019_COMMAND, RTL8019_PAGE0);
}


void eth_halt (void)
{
	put_reg (RTL8019_COMMAND, 0x01);
}

int s3c2410_eth_init (bd_t * bd)
{
	unsigned char id0, id1;

	eth_halt();
	udelay(100000);
	
	/* read id */
	eth_reset ();
	id0 = get_reg(RTL8019_REMOTEBYTECOUNT0);
	id1 = get_reg(RTL8019_REMOTEBYTECOUNT1);
	if(id0 != 0x50 || id1 != 0x70)
	{
		ETH_DBG("error: RTL8019AS chip not found { 0x%x(0x50), 0x%x(0x70)}!\n", id0, id1);
		return -1;
	}
	ETH_DBG("RTL8019AS Founded!\n");
	ETH_DBG("MAC : 0x%x-0x%x-0x%x-0x%x-0x%x-0x%x\n", bd->bi_enetaddr[0], bd->bi_enetaddr[1], bd->bi_enetaddr[2], bd->bi_enetaddr[3], bd->bi_enetaddr[4], bd->bi_enetaddr[5]);

	eth_reset ();
	put_reg (RTL8019_COMMAND, RTL8019_PAGE0STOP);
	put_reg (RTL8019_DATACONFIGURATION, 0x48);
	put_reg (RTL8019_REMOTEBYTECOUNT0, 0x00);
	put_reg (RTL8019_REMOTEBYTECOUNT1, 0x00);
	put_reg (RTL8019_RECEIVECONFIGURATION, 0x00);	/*00; */
	put_reg (RTL8019_TRANSMITPAGE, RTL8019_TPSTART);
	put_reg (RTL8019_TRANSMITCONFIGURATION, 0x02);
	put_reg (RTL8019_PAGESTART, RTL8019_PSTART);
	put_reg (RTL8019_BOUNDARY, RTL8019_PSTART);
	put_reg (RTL8019_PAGESTOP, RTL8019_PSTOP);
	put_reg (RTL8019_INTERRUPTSTATUS, 0xff);
	put_reg (RTL8019_INTERRUPTMASK, 0x11);	/*b; */
	put_reg (RTL8019_COMMAND, RTL8019_PAGE1STOP);
	put_reg (RTL8019_PHYSICALADDRESS0, bd->bi_enetaddr[0]);
	put_reg (RTL8019_PHYSICALADDRESS1, bd->bi_enetaddr[1]);
	put_reg (RTL8019_PHYSICALADDRESS2, bd->bi_enetaddr[2]);
	put_reg (RTL8019_PHYSICALADDRESS3, bd->bi_enetaddr[3]);
	put_reg (RTL8019_PHYSICALADDRESS4, bd->bi_enetaddr[4]);
	put_reg (RTL8019_PHYSICALADDRESS5, bd->bi_enetaddr[5]);
	put_reg (RTL8019_MULTIADDRESS0, 0x00);
	put_reg (RTL8019_MULTIADDRESS1, 0x00);
	put_reg (RTL8019_MULTIADDRESS2, 0x00);
	put_reg (RTL8019_MULTIADDRESS3, 0x00);
	put_reg (RTL8019_MULTIADDRESS4, 0x00);
	put_reg (RTL8019_MULTIADDRESS5, 0x00);
	put_reg (RTL8019_MULTIADDRESS6, 0x00);
	put_reg (RTL8019_MULTIADDRESS7, 0x00);
	put_reg (RTL8019_CURRENT, RTL8019_PSTART);
	put_reg (RTL8019_COMMAND, RTL8019_PAGE0);
	put_reg (RTL8019_TRANSMITCONFIGURATION, 0xe0);	/*58; */

#if 1
	{
	char macid[10];
	rtl8019_get_enetaddr(macid);
	}
#endif
	udelay(100000);
	return 0;
}


static unsigned char nic_to_pc (unsigned char *data, int *len)
{
	unsigned char rec_head_status;
	unsigned char next_packet_pointer;
	unsigned char packet_length0;
	unsigned char packet_length1;
	unsigned short rxlen = 0;
	unsigned int i = 4;
	unsigned char current_point;
	unsigned char *addr;

	/*
	 * The RTL8019's first 4B is packet status,page of next packet
	 * and packet length(2B).So we receive the fist 4B.
	 */
	put_reg (RTL8019_REMOTESTARTADDRESS1, get_reg (RTL8019_BOUNDARY));
	put_reg (RTL8019_REMOTESTARTADDRESS0, 0x00);
	put_reg (RTL8019_REMOTEBYTECOUNT1, 0x00);
	put_reg (RTL8019_REMOTEBYTECOUNT0, 0x04);

	put_reg (RTL8019_COMMAND, RTL8019_REMOTEDMARD);

	rec_head_status = get_reg (RTL8019_DMA_DATA);
	next_packet_pointer = get_reg (RTL8019_DMA_DATA);
	packet_length0 = get_reg (RTL8019_DMA_DATA);
	packet_length1 = get_reg (RTL8019_DMA_DATA);

	put_reg (RTL8019_COMMAND, RTL8019_PAGE0);
	/*Packet length is in two 8bit registers */
	rxlen = packet_length1;
	rxlen = (((rxlen << 8) & 0xff00) + packet_length0);
	rxlen -= 4;

	if (rxlen > PKTSIZE_ALIGN + PKTALIGN)
		ETH_DBG ("packet too big!\n");

	/*Receive the packet */
	put_reg (RTL8019_REMOTESTARTADDRESS0, 0x04);
	put_reg (RTL8019_REMOTESTARTADDRESS1, get_reg (RTL8019_BOUNDARY));

	put_reg (RTL8019_REMOTEBYTECOUNT0, (rxlen & 0xff));
	put_reg (RTL8019_REMOTEBYTECOUNT1, ((rxlen >> 8) & 0xff));


	put_reg (RTL8019_COMMAND, RTL8019_REMOTEDMARD);

	for (addr = (unsigned char *) data, i = rxlen; i > 0; i--)
		*addr++ = get_reg (RTL8019_DMA_DATA);
	*len = rxlen;

	while (!(get_reg (RTL8019_INTERRUPTSTATUS)) & 0x40);	/* wait for the op. */

	/*
	 * To test whether the packets are all received,get the
	 * location of current point
	 */
	put_reg (RTL8019_COMMAND, RTL8019_PAGE1);
	current_point = get_reg (RTL8019_CURRENT);
	put_reg (RTL8019_COMMAND, RTL8019_PAGE0);
	put_reg (RTL8019_BOUNDARY, next_packet_pointer);
	return current_point;
}

/* Get a data block via Ethernet */
int s3c2410_eth_rcv (unsigned char *data, int *len)
{
	unsigned char temp, current_point;
	put_reg (RTL8019_COMMAND, RTL8019_PAGE0);

	while (1) {
		temp = get_reg (RTL8019_INTERRUPTSTATUS);

		if (temp & 0x90) {
			/*overflow */
			put_reg (RTL8019_COMMAND, RTL8019_PAGE0STOP);
			udelay (200000);
			put_reg (RTL8019_REMOTEBYTECOUNT0, 0);
			put_reg (RTL8019_REMOTEBYTECOUNT1, 0);
			put_reg (RTL8019_TRANSMITCONFIGURATION, 2);
			do {
				current_point = nic_to_pc (data, len);
			} while (get_reg (RTL8019_BOUNDARY) != current_point);

			put_reg (RTL8019_TRANSMITCONFIGURATION, 0xe0);
		}

		if (temp & 0x1) {
			/*packet received */
			do {
				put_reg (RTL8019_INTERRUPTSTATUS, 0x01);
				current_point = nic_to_pc (data, len);
			} while (get_reg (RTL8019_BOUNDARY) != current_point);
			return 0;
		}

		if (!(temp & 0x1))
			return -1;
		/* done and exit. */
	}
}

/* Send a data block via Ethernet. */
extern int s3c2410_eth_send (unsigned char *data, int len)
{
	volatile unsigned char *p;
	unsigned int pn;

#if 0
	int loopcnt;
	ETH_DBG("->\n");
	for(loopcnt = 0; loopcnt < length; loopcnt ++)
	{
		if(loopcnt%16 == 0)
                        ETH_DBG("\n    ");

		ETH_DBG("0x%x ", *(((volatile unsigned char *) data) + loopcnt));
	}
	ETH_DBG("\n");
#endif
	pn = len;
	p = (volatile unsigned char *) data;

	while (get_reg (RTL8019_COMMAND) == RTL8019_TRANSMIT);

	put_reg (RTL8019_REMOTESTARTADDRESS0, 0);
	put_reg (RTL8019_REMOTESTARTADDRESS1, RTL8019_TPSTART);
	put_reg (RTL8019_REMOTEBYTECOUNT0, (pn & 0xff));
	put_reg (RTL8019_REMOTEBYTECOUNT1, ((pn >> 8) & 0xff));

	put_reg (RTL8019_COMMAND, RTL8019_REMOTEDMAWR);
	while (pn > 0) {
		put_reg (RTL8019_DMA_DATA, *p++);
		pn--;
	}

	pn = len;

	while (pn < 60) {	/*Padding */
		put_reg (RTL8019_DMA_DATA, 0);
		pn++;
	}

	while (!(get_reg (RTL8019_INTERRUPTSTATUS)) & 0x40);

	put_reg (RTL8019_INTERRUPTSTATUS, 0x40);
	put_reg (RTL8019_TRANSMITPAGE, RTL8019_TPSTART);
	put_reg (RTL8019_TRANSMITBYTECOUNT0, (pn & 0xff));
	put_reg (RTL8019_TRANSMITBYTECOUNT1, ((pn >> 8 & 0xff)));
	put_reg (RTL8019_COMMAND, RTL8019_TRANSMIT);

	return 0;
}

int s3c2410_eth_get_addr(unsigned char *addr)
{
	memcpy(addr, "00:00:00:00:00:00", ETH_ALEN);
	return 0;
}




