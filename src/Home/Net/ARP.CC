#include "PCNet"
#include "Ethernet"

#define ARP_HASHTABLE_SIZE	1024

#define HTT_ARP	0x00100	//identical to HTT_DICT_WORD

#define ARP_REQUEST	0x01
#define ARP_REPLY	0x02

class CARPHeader
{
	U16	hardware_type;
	U16	protocol_type;

	U8	hardware_addr_len;
	U8	protocol_addr_len;

	U16	operation;

	U8	sender_hardware_addr[MAC_ADDRESS_LENGTH];
	U32	sender_protocol_addr;

	U8	target_hardware_addr[MAC_ADDRESS_LENGTH];
	U32	target_protocol_addr;

};

class CARPHash:CHash
{	//store U32 ip_address as CHash->str U8*, MStrPrint("%d")
//	U32 ip_address;
	U8	mac_address[MAC_ADDRESS_LENGTH];
};

class CARPGlobals
{
	U32	local_ipv4; // stored in Big Endian

} arp_globals;

CHashTable *arp_cache = NULL;

U0 ARPCacheInit()
{
	arp_cache = HashTableNew(ARP_HASHTABLE_SIZE);
	arp_globals.local_ipv4 = 0;
}


I64 ARPSend(U16 operation,
			U8 *dest_mac_address,
			U8 *send_mac_address,
			U32 send_ip,
			U8 *target_mac_address,
			U32 target_ip)
{//method currently assumes send_ and target_ip EndianU16 already...

	U8 *ethernet_frame;
	CARPHeader *header;
	I64 de_index = EthernetFrameAllocate(&ethernet_frame,
										 send_mac_address,
										 dest_mac_address,
										 ETHERTYPE_ARP,
										 sizeof(CARPHeader));

	if (de_index < 0)
		return de_index; // error state

	header = ethernet_frame;

	header->hardware_type = EndianU16(HTYPE_ETHERNET);
	header->protocol_type = EndianU16(ETHERTYPE_IPV4);

	header->hardware_addr_len = MAC_ADDRESS_LENGTH;
	header->protocol_addr_len = IP_ADDRESS_LENGTH;

	header->operation = EndianU16(operation);

	MemCopy(header->sender_hardware_addr, send_mac_address, MAC_ADDRESS_LENGTH);
	header->sender_protocol_addr = send_ip;

	MemCopy(header->target_hardware_addr, target_mac_address, MAC_ADDRESS_LENGTH);
	header->target_protocol_addr = target_ip;

	EthernetFrameFinish(de_index);
	return 0;
}




CARPHash *ARPCacheFindByIP(U32 ip_address)
{
	U8 *ip_string = MStrPrint("%d", ip_address);
	CARPHash *entry = HashFind(ip_string, arp_cache, HTT_ARP);
	if (entry == NULL)
		ZenithErr("Could not find an IP in ARP cache.");

	Free(ip_string);
	return entry;
}

CARPHash *ARPCachePut(U32 ip_address, U8 *mac_address)
{
	CARPHash *entry = ARPCacheFindByIP(ip_address);
	Free(entry);

	entry = CAlloc(sizeof(CARPHash));
	entry->str = MStrPrint("%d", ip_address);
	MemCopy(entry->mac_address, mac_address, 6);
	return entry;
}

U0 ARPSetIPV4Address(U32 ip_address)
{ // takes in little endian IP, stores into globals as Big Endian
	arp_globals.local_ipv4 = EndianU32(ip_address);

	ARPSend(ARP_REPLY,
			ethernet_globals.ethernet_broadcast,
			EthernetGetMAC(),
			arp_globals.local_ipv4,
			ethernet_globals.ethernet_broadcast,
			arp_globals.local_ipv4);
}



//ARP Handler? Takes an eth_frame CEthFrame* ?
//Seems like a weird way to do this,
//and then it goes into a a RegisterL3Protocol
//function that does some function-handler
//magic. Idk why it _has_ to do that, it seems
//like a choice they made. I really do wonder if
//their is a slicker way to implement this.
//Less of this fucky function syntax mess.

//We'll just make the ARP handle function
//and directly call it based on a switch in
//the NetQueueHandler
I64 ARPHandler(CEthernetFrame *ethernet_frame)
{
	// shrine checks if frame ethertype is ARP and ensures length is not less than CARPHeader
	// since revising Shrine implement, will do same checks for now ..
	if (ethernet_frame->ethertype != ETHERTYPE_ARP)
	{
		ZenithErr("ARP Handler caught wrong frame ethertype.");
		return -1; // External use of ARPHandler must account for -1 error codes
	}
	if (ethernet_frame->length < sizeof(CARPHeader))
	{
		ZenithErr("ARP Handler caught wrong frame length.");
		return -1; // External use of ARPHandler must account for -1 error codes
	}


	CARPHeader *header = ethernet_frame->data;
	U16 operation = EndianU16(header->operation);

	// shrine checks to ensure header->htype is 1,
	// EndianU16(header->protocol_type) == ethertype ipv4,
	// hlen(?) != 6(?), and that plen(?) == 4 (?)
	if (EndianU16(header->hardware_type) != HTYPE_ETHERNET)
	{
		ZenithErr("ARP Handler caught wrong frame hardware type.");
		return -1; // External use of ARPHandler must account for -1 error codes
	}

	if (EndianU16(header->protocol_type) != ETHERTYPE_IPV4)
	{
		ZenithErr("ARP Handler caught wrong frame protocol type.");
		return -1; // External use of ARPHandler must account for -1 error codes
	}
	if (header->hardware_addr_len != HLEN_ETHERNET)
	{
		ZenithErr("ARP Handler caught wrong frame hardware address length.");
		return -1; // External use of ARPHandler must account for -1 error codes
	}
	if (header->protocol_addr_len != PLEN_IPV4)
	{
		ZenithErr("ARP Handler caught wrong frame protocol address length.");
		return -1; // External use of ARPHandler must account for -1 error codes
	}



	switch (operation)
	{
		case ARP_REQUEST:
			if (header->target_protocol_addr == arp_globals.local_ipv4)
				ARPSend(ARP_REPLY,
						header->sender_hardware_addr,
						EthernetGetMAC(),
						arp_globals.local_ipv4,
						header->sender_hardware_addr,
						header->sender_protocol_addr);
			break;
		case ARP_REPLY:
			ARPCachePut(EndianU32(header->sender_protocol_addr), header->sender_hardware_addr);
			break;
	}
}









































