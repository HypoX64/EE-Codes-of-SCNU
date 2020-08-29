#include "eth.h"
#include "s3c44b0.h"

unsigned char s3c44b0_eth_addr[ETH_ALEN] = {0x00,0x80,0x48,0x12,0x34,0x56};
unsigned long   CS8900_BASE = 0x04000300;

void udelay(int count)
{
	while(count--)
	{
		int ncount = 5;
	}
}

int s3c44b0_eth_init(void)
{
	bd_t bd;

	memcpy(bd.bi_enetaddr, s3c44b0_eth_addr, ETH_ALEN);
	cs8900a_eth_init(&bd);
	return 0;
}

int s3c44b0_eth_send(unsigned char *data, int len)
{

	return cs8900a_eth_send(data, len);
}

int s3c44b0_eth_rcv(unsigned char *data, int *len)
{
	return cs8900a_eth_rx();
}

int s3c44b0_eth_get_addr(unsigned char *addr)
{
	memcpy(addr, s3c44b0_eth_addr, ETH_ALEN);
	return 0;
}


#ifdef CS8900_BUS32
/* we don't need 16 bit initialisation on 32 bit bus */
#define get_reg_init_bus(x) get_reg((x))
#else
static unsigned short get_reg_init_bus (int regno)
{
	/* force 16 bit busmode */
	volatile unsigned char c;

	c = CS8900_BUS16_0;
	c = CS8900_BUS16_1;
	c = CS8900_BUS16_0;
	c = CS8900_BUS16_1;
	c = CS8900_BUS16_0;

	CS8900_PPTR = regno;
	return (unsigned short) CS8900_PDATA;
}
#endif

static unsigned short get_reg (int regno)
{
	CS8900_PPTR = regno;
	return (unsigned short) CS8900_PDATA;
}


static void put_reg (int regno, unsigned short val)
{
	CS8900_PPTR = regno;
	CS8900_PDATA = val;
}

static void cs8900a_eth_reset (void)
{
	int tmo;
	unsigned short us;

	/* reset NIC */
	put_reg (PP_SelfCTL, get_reg (PP_SelfCTL) | PP_SelfCTL_Reset);

	/* wait for 200ms */
	udelay (200000);
	/* Wait until the chip is reset */
}

void cs8900_get_enetaddr (uchar * addr)
{
	int i;
	unsigned char env_enetaddr[6];
	char *tmp = (char*)getenv ("ethaddr");
	char *end;

	for (i=0; i<6; i++) {
		env_enetaddr[i] = tmp ? strtoul(tmp, &end, 16) : 0;
		if (tmp)
			tmp = (*end) ? end+1 : end;
	}

	/* verify chip id */
	if (get_reg_init_bus (PP_ChipID) != 0x630e)
		return;
	cs8900a_eth_reset ();
	if ((get_reg (PP_SelfST) & (PP_SelfSTAT_EEPROM | PP_SelfSTAT_EEPROM_OK)) ==
			(PP_SelfSTAT_EEPROM | PP_SelfSTAT_EEPROM_OK)) {

		/* Load the MAC from EEPROM */
		for (i = 0; i < 6 / 2; i++) {
			unsigned int Addr;

			Addr = get_reg (PP_IA + i * 2);
			addr[i * 2] = Addr & 0xFF;
			addr[i * 2 + 1] = Addr >> 8;
		}

		if (memcmp(env_enetaddr, "\0\0\0\0\0\0", 6) != 0 &&
		    memcmp(env_enetaddr, addr, 6) != 0) {
			ETH_DBG ("\nWarning: MAC addresses don't match:\n");
			ETH_DBG ("\tHW MAC address:  "
				"%02X:%02X:%02X:%02X:%02X:%02X\n",
				addr[0], addr[1],
				addr[2], addr[3],
				addr[4], addr[5] );
			ETH_DBG ("\t\"ethaddr\" value: "
				"%02X:%02X:%02X:%02X:%02X:%02X\n",
				env_enetaddr[0], env_enetaddr[1],
				env_enetaddr[2], env_enetaddr[3],
				env_enetaddr[4], env_enetaddr[5]) ;
			ETH_DBG ("### Set MAC addr from environment\n");
			memcpy (addr, env_enetaddr, 6);
		}
		if (!tmp) {
			char ethaddr[20];
			ETH_DBG (ethaddr, "%02X:%02X:%02X:%02X:%02X:%02X",
				 addr[0], addr[1],
				 addr[2], addr[3],
				 addr[4], addr[5]) ;
			ETH_DBG ("### Set environment from HW MAC addr = \"%s\"\n",				ethaddr);
			setenv ("ethaddr", ethaddr);
		}

	}
}

void cs8900a_eth_halt (void)
{
	/* disable transmitter/receiver mode */
	put_reg (PP_LineCTL, 0);

	/* "shutdown" to show ChipID or kernel wouldn't find he cs8900 ... */
	get_reg_init_bus (PP_ChipID);
}

int cs8900a_eth_init (bd_t * bd)
{
	/* verify chip id */

	if (get_reg_init_bus (PP_ChipID) != 0x630e) {
		ETH_DBG ("CS8900 Ethernet chip not found?!\n");
		return 0;
	}

	cs8900a_eth_reset ();

	/* set the ethernet address */
	put_reg (PP_IA + 0, bd->bi_enetaddr[0] | (bd->bi_enetaddr[1] << 8));
	put_reg (PP_IA + 2, bd->bi_enetaddr[2] | (bd->bi_enetaddr[3] << 8));
	put_reg (PP_IA + 4, bd->bi_enetaddr[4] | (bd->bi_enetaddr[5] << 8));

	/* receive only error free packets addressed to this card */
	put_reg (PP_RxCTL, PP_RxCTL_IA | PP_RxCTL_Broadcast | PP_RxCTL_RxOK);

	/* do not generate any interrupts on receive operations */
	put_reg (PP_RxCFG, 0);

	/* do not generate any interrupts on transmit operations */
	put_reg (PP_TxCFG, 0);

	/* do not generate any interrupts on buffer operations */
	put_reg (PP_BufCFG, 0);

	/* enable transmitter/receiver mode */
	put_reg (PP_LineCTL, PP_LineCTL_Rx | PP_LineCTL_Tx);

	return 0;
}

/* Get a data block via Ethernet */
int cs8900a_eth_rx (unsigned char *data, int *len)
{
	int i;
	unsigned short *addr;
	unsigned short status;

	status = get_reg (PP_RER);

	if ((status & PP_RER_RxOK) == 0)
		return -1;

	status = CS8900_RTDATA;		/* stat */
	*len = CS8900_RTDATA;		/* len */

	for (addr = (unsigned short *)data, i = (*len) >> 1; i > 0;
		 i--)
		*addr++ = CS8900_RTDATA;
	if ((*len) & 1)
		*addr++ = CS8900_RTDATA;

 	return 0;
}

/* Send a data block via Ethernet. */
int cs8900a_eth_send (unsigned char *data, int len)
{
	volatile unsigned short *addr;
	int tmo;
	unsigned short s;

retry:
	/* initiate a transmit sequence */
	CS8900_TxCMD = PP_TxCmd_TxStart_Full;
	CS8900_TxLEN = len;

	/* Test to see if the chip has allocated memory for the packet */
	if ((get_reg (PP_BusSTAT) & PP_BusSTAT_TxRDY) == 0) {
		/* Oops... this should not happen! */
		ETH_DBG ("\rcs: unable to send packet; retrying...\n");

		cs8900a_eth_reset ();
		goto retry;
	}

	/* Write the contents of the packet */
	/* assume even number of bytes */
	for (addr = (unsigned short *)data; len > 0; len -= 2)
		CS8900_RTDATA = *addr++;

	/* wait for transfer to succeed */
	while ((s = get_reg (PP_TER) & ~0x1F) == 0) {};

	/* nothing */ ;
	if ((s & ( /*PP_TER_CRS |*/ PP_TER_TxOK)) != PP_TER_TxOK) {
		ETH_DBG ("\ntransmission error %#x\n", s);
	}

	return 0;
}

static void cs8900_e2prom_ready(void)
{
	while(get_reg(PP_SelfST) & SI_BUSY);
}

/***********************************************************/
/* read a 16-bit word out of the EEPROM                    */
/***********************************************************/

int cs8900_e2prom_read(unsigned char addr, unsigned short *value)
{
	cs8900_e2prom_ready();
	put_reg(PP_EECMD, EEPROM_READ_CMD | addr);
	cs8900_e2prom_ready();
	*value = get_reg(PP_EEData);

	return 0;
}


/***********************************************************/
/* write a 16-bit word into the EEPROM                     */
/***********************************************************/

void cs8900_e2prom_write(unsigned char addr, unsigned short value)
{
	cs8900_e2prom_ready();
	put_reg(PP_EECMD, EEPROM_WRITE_EN);
	cs8900_e2prom_ready();
	put_reg(PP_EEData, value);
	put_reg(PP_EECMD, EEPROM_WRITE_CMD | addr);
	cs8900_e2prom_ready();
	put_reg(PP_EECMD, EEPROM_WRITE_DIS);
	cs8900_e2prom_ready();

	return;
}


