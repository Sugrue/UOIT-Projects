#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/in.h>

static struct nf_hook_ops netfilter_ops_out;					//initialize netfilter strutcture
int UDPcounter = 0;												//initialize UDP packet counter

unsigned int main_hook(	unsigned int 		hooknum,
			struct sk_buff 		*skb,
			const struct net_device *in,
			const struct net_device *out,
			int (*okfn)(struct sk_buff*))
{
	struct iphdr *iph;											//initialize an ipheader structure to point to the skb/data access

	if (!skb)													
		return NF_ACCEPT;										//returns the packet if the skb dos not contain any information

	iph = ip_hdr(skb);											//set the iph pointer to the skb creating an easier means of accessing information
	if (!iph)
		return NF_ACCEPT;										//if there was an error, allow the packet to continue, IE allow another function to handle the error

	if (iph->protocol == IPPROTO_UDP)							//if the ip packet's layer 4 protocol is UDP, increment the counter and print a debugging message
	{
		UDPcounter++;
		//printk("got a UDP packet - [%d]\n",UDPcounter);
	}

	return NF_ACCEPT;
}

static int __init init(void)									//initialization of the module, and hooking the function to the local out hook
{
	netfilter_ops_out.hook = main_hook;
	netfilter_ops_out.pf = PF_INET;
	netfilter_ops_out.pf = PF_INET;
	netfilter_ops_out.hooknum = NF_INET_LOCAL_OUT;
	netfilter_ops_out.priority = NF_IP_PRI_FIRST;
	nf_register_hook(&netfilter_ops_out);
	return 0;
}
static void __exit cleanup(void)								//unloading the function gracefully 
{
	printk("%d UDP packets were recorded\n",UDPcounter);
	nf_unregister_hook(&netfilter_ops_out);
}

module_init(init);
module_exit(cleanup);

