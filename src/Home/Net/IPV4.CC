#include "ARP"

#define IPV4_ERR_ADDR_INVALID		-200001
#define IPV4_ERR_HOST_UNREACHABLE	-200002

//i'd like to know why 64 was chosen
#define IPV4_TTL	64

//Look up IP Protocol Numbers online to see many more.
#define IP_PROTOCOL_ICMP	0x01
#define IP_PROTOCOL_TCP		0x06
#define IP_PROTOCOL_UDP		0x11


class CIPV4Packet
{
	CEthernetFrame *ethernet_frame;

	U32 source_ip_address;
	U32 destination_ip_address;

	U8 protocol;

	U8 padding[7];

	U8 *data;

	I64 length;
};

class CIPV4Header
{ // note: U4's in some U8s.
	U8 version_ihl;				// Version for IPV4 is 4. IHL=Internet Header Length

	U8 dscp_ecn;				// DSCP=Differentiated Services Code Point. ECN=Explicit Congestion Notification

	U16 total_length;			// min 20B max 65535

	U16 identification;

	U16 flags_fragment_offset;	// flags first(?) 3 bits. fragment offset min 0 max 65528
	// flag: bit 0: reserved must be 0. bit 1: don't fragment. bit 2: more fragments

	U8 time_to_live;			// specified in seconds, wikipedia says nowadays serves as a hop count

	U8 protocol;

	U16 header_checksum;

	U32 source_ip_address;
	U32 destination_ip_address;
}

class CIPV4Globals
{ // _be indicates Big Endian
	U32 local_ip;
	U32 local_ip_be;

	U32 ipv4_router_address;
	U32 ipv4_subnet_mask;

} ipv4_globals;

U0 InitIPV4Globals()
{
	ipv4_globals.local_ip			 = 0;
	ipv4_globals.local_ip_be		 = 0;
	ipv4_globals.ipv4_router_address = 0;
	ipv4_globals.ipv4_subnet_mask	 = 0;
}


// For now, trusting Shrine's implement
// of this. Shrine links back to
// http://stackoverflow.com/q/26774761/2524350

U16 IPV4Checksum(U8* header, I64 length)
{	//todo. make names clearer, and better comments.
	I64 nleft = length;
	U16 *w = header;
	I64 sum = 0;

	while (nleft > 1)
	{
		sum += *(w++);
		nleft -= 2;
	}

	// "mop up an odd byte, if necessary"
	if (nleft == 1)
	{
		sum += ((*w) & 0x00FF);
	}

	// "add back carry outs from top 16 bits to low 16 bits"
	sum = (sum >> 16) + (sum & 0xFFFF); // "add hi 16 to low 16"
	sum += (sum >> 16); // add carry
	return (~sum) & 0xFFFF;

}



I64 GetMACAddressForIP(U32 ip_address, U8 **mac_out)
{
	CARPHash *entry;
	I64 retries;
	I64 attempt;
/*
	switch (ip_address)
	{
		case 0:
			return IPV4_ERR_ADDR_INVALID;
		case 0xFFFFFFFF:
			*mac_out = ethernet_globals.ethernet_broadcast;
			return 0;
	}
*/

	if (ip_address == 0)
	{
		ZenithLog("Get MAC for IP failed. Address = 0\n");
		return IPV4_ERR_ADDR_INVALID;
	}
	if (ip_address == 0xFFFFFFFF)
	{
		ZenithLog("Get MAC for IP requested and returning ethernet broadcast\n");
		*mac_out = ethernet_globals.ethernet_broadcast;
		return 0;
	}


	// "outside this subnet; needs routing"
	if ((ip_address & ipv4_globals.ipv4_subnet_mask) != (ipv4_globals.local_ip & ipv4_globals.ipv4_subnet_mask))
	{
		// Shrine recurses here... and says FIXME infinite loop if mis-configured...
	}
	else // "local network"
	{
		entry = ARPCacheFindByIP(ip_address);

		if (entry)
		{
			*mac_out = entry->mac_address;
			return 0;
		}
		//else, not in cache, need to request it

		// "Up to 4 retries, 500 ms each"
		retries = 4;
		while (retries)
		{
			attempt = 0;
			for (attempt = 0; attempt < 50; attempt++)
			{
				Sleep(10);
				entry = ARPCacheFindByIP(ip_address);
				if (entry)
					break;
			}

			if (entry)
			{
				*mac_out = entry->mac_address;
				return 0;
			}

			retries--;
		}

		//Shrine does some in_addr mess to log error
		ZenithLog("Failed to resolve address %d", ip_address);
		return IPV4_ERR_HOST_UNREACHABLE;
	}
}

I64 IPV4PacketAllocate(U8 **frame_out, 
					   U8 protocol,
					   U32 source_ip_address,
					   U32 destination_ip_address,
					   I64 length)
{
	U8 *ethernet_frame;
	U8 *destination_mac_address;

	I64 error;
	I64 de_index;

	I64 internet_header_length;

	CIPV4Header *header;


	error = GetMACAddressForIP(destination_ip_address, &destination_mac_address);
	if (error < 0)
	{
		ZenithLog("IPV4 Packet Allocate failed to get MAC for destination.\n");
		return error;
	}

	de_index = EthernetFrameAllocate(&ethernet_frame,
									 EthernetGetMAC(),
									 destination_mac_address,
									 ETHERTYPE_IPV4,
									 sizeof(CIPV4Header) + length);
	if (de_index < 0)
	{
		ZenithLog("IPV4 Ethernet Frame Allocate failed.\n");
		return de_index;
	}

	internet_header_length = 5;// ... why. need a #define


	header = ethernet_frame;


	header->version_ihl				= internet_header_length | (4 << 4);// whaaat the fuck is this? #define!
	header->dscp_ecn				= 0; // a clear define of what this actually means would be good
	header->total_length			= EndianU16(internet_header_length * 4 + length); //...why?
	header->identification			= 0; // define would be clearer
	header->flags_fragment_offset	= 0; // define would be clearer
	header->time_to_live			= IPV4_TTL;
	header->protocol				= protocol;
	header->header_checksum			= 0; // why is 0 ok?
	header->source_ip_address		= EndianU32(source_ip_address);
	header->destination_ip_address	= EndianU32(destination_ip_address);
	header->header_checksum			= IPV4Checksum(header, internet_header_length + 4);//why the 4's...

	*frame_out = ethernet_frame + sizeof(CIPV4Header);
	return de_index;
}

U0 IPV4PacketFinish(I64 de_index) //alias for EthernetFrameFinish
{
	EthernetFrameFinish(de_index);
}

U32 IPV4GetAddress()
{
	return ipv4_globals.local_ip;
}

U0 IPV4SetAddress(U32 ip_address)
{
	ipv4_globals.local_ip	 = ip_address;
	ipv4_globals.local_ip_be = EndianU32(ip_address);

	ARPSetIPV4Address(ip_address);
	
}

U0 IPV4SetSubnet(U32 router_address, U32 subnet_mask)
{
	ipv4_globals.ipv4_router_address = router_address;
	ipv4_globals.ipv4_subnet_mask	 = subnet_mask;
}

//I64
U0 IPV4ParsePacket(CIPV4Packet *packet_out, CEthernetFrame *ethernet_frame)
{
	//...if ethertype not ipv4 error?

	//Shrine says FIXME check ethernet_frame length !! ... we need to know what's appropriate

	CIPV4Header *header = ethernet_frame->data;
	I64 header_length = (header->version_ihl & 0x0F) * 4;//this Has to go. at least abstract or something..
	U16 total_length = EndianU16(header->total_length);

	packet_out->ethernet_frame			= ethernet_frame;
	packet_out->source_ip_address		= EndianU32(header->source_ip_address);
	packet_out->destination_ip_address	= EndianU32(header->destination_ip_address);
	packet_out->protocol				= header->protocol;
	packet_out->data					= ethernet_frame->data + header_length;
	packet_out->length					= total_length - header_length;

//	return 0;
}

// IPV4 handler moved to NetHandlerTask file.




























InitIPV4Globals;