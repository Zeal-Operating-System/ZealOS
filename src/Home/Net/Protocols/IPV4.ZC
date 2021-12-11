#define IPV4_ERR_ADDR_INVALID		-200001
#define IPV4_ERR_HOST_UNREACHABLE	-200002

#define IPV4_TTL	64

//Look up IP Protocol Numbers online to see many more.
#define IP_PROTOCOL_ICMP	0x01
#define IP_PROTOCOL_TCP		0x06
#define IP_PROTOCOL_UDP		0x11

class CIPV4Packet
{
	CEthernetFrame	*ethernet_frame;

	U32				 source_ip_address;
	U32				 destination_ip_address;

	U8				 protocol;
	U8				 padding[7];

	U8				*data;
	I64				 length;
};

class CIPV4Header
{ // note: U4's in some U8s.
	U8	version_ihl;			// Version for IPV4 is 4. IHL=Internet Header Length
	U8	dscp_ecn;				// DSCP=Differentiated Services Code Point. ECN=Explicit Congestion Notification

	U16 total_length;			// min 20B max 65535
	U16 identification;
	U16 flags_fragment_offset;	// flags first(?) 3 bits. fragment offset min 0 max 65528
								// flag: bit 0: reserved must be 0. bit 1: don't fragment. bit 2: more fragments

	U8	time_to_live;			// specified in seconds, wikipedia says nowadays serves as a hop count
	U8	protocol;

	U16 header_checksum;

	U32 source_ip_address;
	U32 destination_ip_address;
};

class CIPV4Globals
{ // _be indicates Big Endian
	U32 local_ip;
	U32 local_ip_be;

	U32 ipv4_router_address;
	U32 ipv4_subnet_mask;

} ipv4_globals;

U0 IPV4GlobalsInit()
{
	ipv4_globals.local_ip			 = 0;
	ipv4_globals.local_ip_be		 = 0;
	ipv4_globals.ipv4_router_address = 0;
	ipv4_globals.ipv4_subnet_mask	 = 0;
};

// For now, trusting Shrine's implement
// of checksum. Shrine links back to
// http://stackoverflow.com/q/26774761/2524350

U16 IPV4Checksum(U8 *header, I64 length)
{	//todo. make names clearer, and better comments.
	I64  nleft = length;
	U16 *w = header;
	I64  sum = 0;

	while (nleft > 1)
	{
		sum += *w++;
		nleft -= 2;
	}

	// "mop up an odd byte, if necessary"
	if (nleft == 1)
	{
		sum += *w & 0x00FF;
	}

	// "add back carry outs from top 16 bits to low 16 bits"
	sum = sum >> 16 + sum & 0xFFFF; // "add hi 16 to low 16"
	sum += sum >> 16; // add carry
	return ~sum & 0xFFFF;

}

I64 IPV4AddressMACGet(U32 ip_address, U8 **mac_out)
{
	CARPHash	*entry;
	I64			 retries;
	I64			 attempt;

	if (ip_address == 0)
	{
		NetErr("GET MAC FOR IP: Failed. Address = 0");
		return IPV4_ERR_ADDR_INVALID;
	}
	if (ip_address == 0xFFFFFFFF)
	{
		NetLog("GET MAC FOR IP: Returning ethernet broadcast");
		*mac_out = ethernet_globals.ethernet_broadcast;

		return 0;
	}

	// "outside this subnet; needs routing"
	if (ip_address & ipv4_globals.ipv4_subnet_mask != ipv4_globals.local_ip & ipv4_globals.ipv4_subnet_mask)
	{
		NetWarn("GET MAC FOR IP: TODO: Doing IPV4AddressMACGet recursion, could infinite loop and overflow stack.");
		return IPV4AddressMACGet(ipv4_globals.ipv4_router_address, mac_out);
	}
	else // "local network"
	{
		NetLog("GET MAC FOR IP: Attempting ARP Find by IP for address: %0X.", ip_address);
		entry = ARPCacheFind(ip_address);

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
			ARPSend(ARP_REQUEST,
					ethernet_globals.ethernet_broadcast,
					EthernetMACGet,
					ipv4_globals.local_ip_be,
					ethernet_globals.ethernet_null,
					EndianU32(ip_address));

			attempt = 0;
			for (attempt = 0; attempt < 50; attempt++)
			{
				Sleep(10);
				entry = ARPCacheFind(ip_address);
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
		NetErr("GET MAC FOR IP: Failed to resolve address %d", ip_address);
		return IPV4_ERR_HOST_UNREACHABLE;
	}
}

I64 IPV4PacketAllocate(U8 **frame_out, 
					   U8 protocol,
					   U32 source_ip_address,
					   U32 destination_ip_address,
					   I64 length)
{
	U8			*ipv4_frame;
	U8			*destination_mac_address;
	I64			 error;
	I64			 de_index;
	I64			 internet_header_length;
	CIPV4Header *header;

	error = IPV4AddressMACGet(destination_ip_address, &destination_mac_address);

	if (error < 0)
	{
		NetLog("IPV4 PACKET ALLOCATE: Failed to get MAC for destination.");
		return error;
	}

	de_index = EthernetFrameAllocate(&ipv4_frame,
									 EthernetMACGet,
									 destination_mac_address,
									 ETHERTYPE_IPV4,
									 sizeof(CIPV4Header) + length);
	if (de_index < 0)
	{
		NetLog("IPV4 PACKET ALLOCATE: Ethernet Frame Allocate failed.");
		return de_index;
	}

	internet_header_length = 5;// ... why. need a #define

	header = ipv4_frame;

	header->version_ihl				= internet_header_length | 4 << 4;// ? TODO: needs #define
	header->dscp_ecn				= 0; // a clear define of what this actually means would be good
	header->total_length			= EndianU16(internet_header_length * 4 + length); //...why?
	header->identification			= 0; // define would be clearer
	header->flags_fragment_offset	= 0; // define would be clearer
	header->time_to_live			= IPV4_TTL;
	header->protocol				= protocol;
	header->header_checksum			= 0; // why is 0 ok?
	header->source_ip_address		= EndianU32(source_ip_address);
	header->destination_ip_address	= EndianU32(destination_ip_address);
	header->header_checksum			= IPV4Checksum(header, internet_header_length * 4);//why the 4's...

	*frame_out = ipv4_frame + sizeof(CIPV4Header);
	return de_index;
}

U0 IPV4PacketFinish(I64 de_index) //alias for EthernetFrameFinish
{
	EthernetFrameFinish(de_index);
}

U32 IPV4AddressGet()
{
	return ipv4_globals.local_ip;
}

U0 IPV4AddressSet(U32 ip_address)
{
	ipv4_globals.local_ip	 = ip_address;
	ipv4_globals.local_ip_be = EndianU32(ip_address);

	ARPLocalIPV4Set(ip_address);
	
}

U0 IPV4SubnetSet(U32 router_address, U32 subnet_mask)
{
	ipv4_globals.ipv4_router_address = router_address;
	ipv4_globals.ipv4_subnet_mask	 = subnet_mask;
}

//I64
U0 IPV4PacketParse(CIPV4Packet *packet_out, CEthernetFrame *ethernet_frame)
{
	//...if ethertype not ipv4 error?

	// TODO: Check ethernet_frame length ! ... we need to know what's appropriate

	CIPV4Header *header = ethernet_frame->data;
	I64			 header_length = (header->version_ihl & 0x0F) * 4;//this Has to go. at least abstract or something..
	U16			 total_length = EndianU16(header->total_length);

	packet_out->ethernet_frame			= ethernet_frame;
	packet_out->source_ip_address		= EndianU32(header->source_ip_address);
	packet_out->destination_ip_address	= EndianU32(header->destination_ip_address);
	packet_out->protocol				= header->protocol;
	packet_out->data					= ethernet_frame->data + header_length;
	packet_out->length					= total_length - header_length;

//	return 0;
}

U0 IPV4Rep()
{
	"$$LTBLUE$$IPV4 Report:$$FG$$\n\n";

	"Local IPV4:$FG,6$			%d.%d.%d.%d$FG$\n",
		ipv4_globals.local_ip.u8[3],
		ipv4_globals.local_ip.u8[2],
		ipv4_globals.local_ip.u8[1],
		ipv4_globals.local_ip.u8[0];
	"Router IPV4:$FG,6$		%d.%d.%d.%d$FG$\n",
		ipv4_globals.ipv4_router_address.u8[3],
		ipv4_globals.ipv4_router_address.u8[2],
		ipv4_globals.ipv4_router_address.u8[1],
		ipv4_globals.ipv4_router_address.u8[0];
	"Subnet IPV4:$FG,6$		%d.%d.%d.%d$FG$\n",
		ipv4_globals.ipv4_subnet_mask.u8[3],
		ipv4_globals.ipv4_subnet_mask.u8[2],
		ipv4_globals.ipv4_subnet_mask.u8[1],
		ipv4_globals.ipv4_subnet_mask.u8[0];
	"\n";
}

// IPV4 handler moved to NetHandlerTask file.
IPV4GlobalsInit;