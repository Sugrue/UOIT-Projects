#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/in.h>
#include <linux/icmp.h>
static struct nf_hook_ops netfilter_ops_in;					//initialize netfilter structure

unsigned int main_hook(	unsigned int 		hooknum,
			struct sk_buff 		*skb,
			const struct net_device *in,
			const struct net_device *out,
			int (*okfn)(struct sk_buff*))
{
	struct iphdr *iph;											//initialize an ipheader structure to point to the skb/data access
	struct icmphdr *icmph;										//initialize an ICMPheader structure to point to the ICMP header within the packet

	if (!skb)
		return NF_ACCEPT; 										//returns the packet if the skb dos not contain any information

	iph = ip_hdr(skb);											//set the iph pointer to the skb creating an easier means of accessing information
	if (!iph)
		return NF_ACCEPT;										//if there was an error, allow the packet to continue, IE allow another function to handle the error

	if (iph->protocol == IPPROTO_ICMP)							//if the packet in question is an ICMP packet, print a debug  message
	{
		printk("ICMP packet\n");

		icmph = icmp_hdr(skb);									//point the ICMPheader pointer to the packet ICMP header
		if (!icmph)												//if unsuccessful, allow the packet to pass and print an error message
		{
			printk("ERROR GETTING ICMP HEADER\n");
			return NF_ACCEPT;
		}

		if (icmph->type == ICMP_ECHO)							//as this function is hooked on pre-routing (incomming flow) we can check if the packet is an echo reply or request, any requests should be blocked to disable incoming pings but allow outgoing pings. A debugging message is also issued.
		{
			//printk("Echo Request; Dropping\n");
			return NF_DROP;
		}
	}

	return NF_ACCEPT;
}

static int __init init(void)									//initialization of the module, and hooking the function to the local out hook
{
	netfilter_ops_in.hook = main_hook;
	netfilter_ops_in.pf = PF_INET;
	netfilter_ops_in.pf = PF_INET;
	netfilter_ops_in.hooknum = NF_INET_PRE_ROUTING;
	netfilter_ops_in.priority = NF_IP_PRI_FIRST;
	nf_register_hook(&netfilter_ops_in);
	return 0;
}
static void __exit cleanup(void)								//unloading the function gracefully 
{
	nf_unregister_hook(&netfilter_ops_in);
}

module_init(init);
module_exit(cleanup);
