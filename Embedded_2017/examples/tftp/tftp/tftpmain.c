#include "skbuff.h"
#include "eth.h"
#include "arp.h" 
#include "ip.h"
#include "udp.h"
#include "tftp.h"

extern int tftp_put_ok;
extern unsigned long tftp_buff_addr;

int net_handle(void)
{
	struct sk_buff *skb;
	struct ethhdr *eth_hdr;

	skb = alloc_skb(ETH_FRAME_LEN);

	if (eth_rcv(skb) != -1) {

		eth_hdr = (struct ethhdr *)(skb->data);
		skb_pull(skb, ETH_HLEN);

		if (ntohs(eth_hdr->h_proto) == ETH_P_ARP)
			arp_rcv_packet(skb);

		else if(ntohs(eth_hdr->h_proto) == ETH_P_IP)
		 	ip_rcv_packet(skb);
	}

	free_skb(skb);

	return 0;
}

int timeout_handle(void)
{
	static int timeout = 0;

	timeout++;
	if (timeout < 5000) return 0;

	timeout = 0;

	return 0;
}

int tftp_main(unsigned long ip, unsigned long addr)
{
	unsigned char eth_addr[ETH_ALEN];
	unsigned char *s = (unsigned char *)&ip;
	int timeout = 0;

	tftp_printf("\nMini TFTP Server 1.0 (IP : %d.%d.%d.%d)\r", s[3], s[2], s[1], s[0]);
	tftp_printf("\nCommand: tftp -i %d.%d.%d.%d put image.bin\r",s[3],s[2],s[1],s[0]);

	tftp_buff_addr = addr;
	eth_init();
	eth_get_addr(eth_addr);
	arp_init();
	ip_init(ip);
	udp_init();

	arp_add_entry(eth_addr, ip);

	tftp_put_ok =0;
	while (1) 
    {
	     net_handle();
	     timeout_handle();
	     if (tftp_put_ok || getkey()) break;
	}
	
	return 0;
}
