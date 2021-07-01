//www.networksorcery.com/enp/protocol/dhcp.htm

#define DHCP_OPCODE_BOOTREQUEST		0x01

#define DHCP_OPTION_SUBNET_MASK		1
#define DHCP_OPTION_ROUTER			3
#define DHCP_OPTION_DNS				6
#define DHCP_OPTION_DOMAIN_NAME		15

#define DHCP_OPTION_REQUESTED_IP	50
#define DHCP_OPTION_MESSAGETYPE		53
#define DHCP_OPTION_SERVER_ID		54
#define DHCP_OPTION_PARAMLIST		55

#define DHCP_MESSAGETYPE_DISCOVER	0x01
#define DHCP_MESSAGETYPE_OFFER		0x02
#define DHCP_MESSAGETYPE_REQUEST	0x03
#define DHCP_MESSAGETYPE_ACK		0x05

#define DHCP_COOKIE	0x63825363

#define DHCP_STATE_CLIENT_START			0
#define DHCP_STATE_CLIENT_DISCOVER		1
#define DHCP_STATE_CLIENT_REQUEST		2
#define DHCP_STATE_CLIENT_REQ_ACCEPTED	3

#define DHCP_TIMEOUT		3000
#define DHCP_MAX_RETRIES	5	// shrine has 3, why not 5 :^)

class CDHCPHeader
{
	U8	opcode;				// Opcode
	U8	hw_type;			// Hardware Type
	U8	hw_addr_len;		// Hardware Address Length
	U8	hops;				// Hop Count
	U32 xid;				// Transaction ID
	U16	seconds;			// Elapsed time in seconds since client began address acquisition or renewal process
	U16 flags;				// Flags
	U32 client_ip;			// Client IP Address
	U32 your_ip;			// Your IP Address
	U32 server_ip;			// Server IP Address
	U32 gateway_ip;			// Gateway IP Address
	U8	client_hw_addr[16];	// Client Hardware Address
	U8	server_name[64];	// Server Hostname
	U8	boot_file[128];		// Boot Filename
};

class CDHCPDiscoverOptions
{
	U32 cookie;
	U8	message_type;
	U8	message_length;
	U8	message; // dmt
	U8	param_req_list_type;
	U8	param_req_list_length;
	U8	param_req_list[4];
	U8	end;
};

class CDHCPRequestOptions
{
	U32 cookie;
	U8	message_type;
	U8	message_length;
	U8	message; // dmt
	U8	requested_ip_type;
	U8	requested_ip_length;
	U32 requested_ip;
	U8	server_id_type;
	U8	server_id_length;
	U32	server_id;
	U8	end;
};

U32 DHCPTransactionBegin()
{
	return RandU32;
}

I64 DHCPDiscoverSend(U32 xid)
{
	U8						*dhcp_frame;
	I64						 de_index;
	CDHCPHeader				*dhcp;
	CDHCPDiscoverOptions	*opts;


	de_index = UDPPacketAllocate(&dhcp_frame,
								 0x00000000,
								 68,
								 0xFFFFFFFF,
								 67,
								 sizeof(CDHCPHeader) + sizeof(CDHCPDiscoverOptions));
	if (de_index < 0)
	{
		NetErr("DHCP SEND DISCOVER: Failed, UDP Packet Allocate error.");
		return de_index;
	}

	dhcp = dhcp_frame;
	MemSet(dhcp, 0, sizeof(CDHCPHeader));

	dhcp->opcode		= DHCP_OPCODE_BOOTREQUEST;
	dhcp->hw_type		= HTYPE_ETHERNET;
	dhcp->hw_addr_len	= HLEN_ETHERNET;
	dhcp->hops			= 0;
	dhcp->xid			= EndianU32(xid);
	dhcp->seconds		= 0;
	dhcp->flags			= EndianU16(0x8000); // DHCP flag: accept Offer from Broadcast.
	dhcp->client_ip		= 0;
	dhcp->your_ip		= 0;
	dhcp->server_ip		= 0;
	dhcp->gateway_ip	= 0;
	MemCopy(dhcp->client_hw_addr, EthernetMACGet, MAC_ADDRESS_LENGTH);

	opts = dhcp_frame + sizeof(CDHCPHeader);

	opts->cookie				= EndianU32(DHCP_COOKIE);
	opts->message_type			= DHCP_OPTION_MESSAGETYPE;
	opts->message_length		= 1;
	opts->message				= DHCP_MESSAGETYPE_DISCOVER;
	opts->param_req_list_type	= DHCP_OPTION_PARAMLIST;
	opts->param_req_list_length	= 4;
	opts->param_req_list[0]		= DHCP_OPTION_SUBNET_MASK;
	opts->param_req_list[1]		= DHCP_OPTION_ROUTER;
	opts->param_req_list[2]		= DHCP_OPTION_DNS;
	opts->param_req_list[3]		= DHCP_OPTION_DOMAIN_NAME;
	opts->end					= 0xFF; // ??

	UDPPacketFinish(de_index);
	return de_index;
}

I64 DHCPRequestSend(U32 xid, U32 requested_ip, U32 server_ip)
{
	U8					*dhcp_frame;
	I64					 de_index;
	CDHCPHeader			*dhcp;
	CDHCPRequestOptions	*opts;

	de_index = UDPPacketAllocate(&dhcp_frame,
								 0x00000000,
								 68,
								 0xFFFFFFFF,
								 67,
								 sizeof(CDHCPHeader) + sizeof(CDHCPRequestOptions));
	if (de_index < 0)
	{
		NetErr("DHCP SEND REQUEST: Failed, UDP Packet Allocate error.");
	}

	dhcp = dhcp_frame;
	MemSet(dhcp, 0, sizeof(CDHCPHeader));

	dhcp->opcode		= DHCP_OPCODE_BOOTREQUEST;
	dhcp->hw_type		= HTYPE_ETHERNET;
	dhcp->hw_addr_len	= HLEN_ETHERNET;
	dhcp->hops			= 0;
	dhcp->xid			= EndianU32(xid);
	dhcp->seconds		= 0;
	dhcp->flags			= EndianU16(0x0000); // DHCP flag: accept ACK from Unicast.
	dhcp->client_ip		= 0;
	dhcp->your_ip		= 0;
	dhcp->server_ip		= EndianU32(server_ip);
	dhcp->gateway_ip	= 0;
	MemCopy(dhcp->client_hw_addr, EthernetMACGet, MAC_ADDRESS_LENGTH);

	opts = dhcp_frame + sizeof(CDHCPHeader);

	opts->cookie				= EndianU32(DHCP_COOKIE);
	opts->message_type			= DHCP_OPTION_MESSAGETYPE;
	opts->message_length		= 1;
	opts->message				= DHCP_MESSAGETYPE_REQUEST;
	opts->requested_ip_type		= DHCP_OPTION_REQUESTED_IP;
	opts->requested_ip_length	= 4;
	opts->requested_ip			= EndianU32(requested_ip);
	opts->server_id_type		= DHCP_OPTION_SERVER_ID;
	opts->server_id_length		= 4;
	opts->server_id				= EndianU32(server_ip);
	opts->end					= 0xFF;

	UDPPacketFinish(de_index);
	return 0;
}

I64 DHCPBeginParse(U8 **data_inout, I64 *length_inout, CDHCPHeader **header_out)
{
	U8	*data	= *data_inout;
	I64  length	= *length_inout;
	U32 *cookie;

	if (length < sizeof(CDHCPHeader) + 4) // + 4?
	{
		NetErr("DHCP PARSE BEGIN: Failed, length too short.");
		return -1;
	}

	cookie = data + sizeof(CDHCPHeader);

	if (EndianU32(*cookie) != DHCP_COOKIE)
	{
		NetErr("DHCP PARSE BEGIN: Failed, cookie doesn't match DHCP-cookie.");
		return -1;
	}

	*header_out		= data;
	*data_inout		= data   + sizeof(CDHCPHeader) + 4; // ?
	*length_inout	= length - sizeof(CDHCPHeader) + 4; // ?..

	return 0;
}

I64 DHCPOptionParse(U8 **data_inout, I64 *length_inout, U8 *type_out, U8 *value_length_out, U8 **value_out)
{
	U8 *data	= *data_inout;
	I64 length	= *length_inout;

	if (length < 2 || length < 2 + data[1]) // ??? what is the 1
	{
		NetErr("DHCP PARSE OPTION: Failed, length too short.");
		return -1;
	}

	if (data[0] == 0xFF) // ahead, data[0] is type_out, so data[0] is perhaps usually type?
	{
		NetLog("DHCP PARSE OPTION: Saw 0xFF, returning 0.");
		return 0;
	}

	*type_out			= data[0];
	*value_length_out	= data[1];
	*value_out			= data + 2;

	*data_inout		= data   + 2 + *value_length_out;
	*length_inout	= length - 2 + *value_length_out;

	return data[0]; // returns ... type?
}

I64 DHCPOfferParse(U32 xid, U8 *data, I64 length,
				   U32 *your_ip_out,
				   U32 *dns_ip_out,
				   U32 *router_ip_out,
				   U32 *subnet_mask_out)
{
	CDHCPHeader *header;
	I64			 error		 = DHCPBeginParse(&data, &length, &header);
	Bool		 have_type	 = FALSE;
	Bool		 have_dns	 = FALSE;
	Bool		 have_router = FALSE;
	Bool		 have_subnet = FALSE;
	U8			 type;
	U8			 value_length;
	U8			*value;
	U32			 address;
	

	if (EndianU32(header->xid) != xid)
	{
		NetErr("DHCP PARSE OFFER: Failed, parsed and parameter Transaction IDs do not match.");
		return -1;
	}

	while (length)
	{
		error = DHCPOptionParse(&data, &length, &type, &value_length, &value);

		if (error < 0)
		{
			NetErr("DHCP PARSE OFFER: Failed at DHCP Parse Option.");
			return error;
		}
		if (error == 0)
		{
			break;
		}

		address = EndianU32(*value(U32 *));

		switch (type)
		{
			case DHCP_OPTION_MESSAGETYPE:
				NetLog("DHCP PARSE OFFER: Parsed Option, Type MESSAGETYPE.");
				if (value_length == 1 && value[0] == DHCP_MESSAGETYPE_OFFER)
					have_type = TRUE;
				break;

			case DHCP_OPTION_DNS:
				NetLog("DHCP PARSE OFFER: Parsed Option, Type DNS.");
				if (value_length == 4)
				{
					*dns_ip_out = address;
					have_dns	= TRUE;
				}
				break;

			case DHCP_OPTION_ROUTER:
				NetLog("DHCP PARSE OFFER: Parsed Option, Type ROUTER.");
				if (value_length == 4)
				{
					*router_ip_out	= address;
					have_router		= TRUE;
				}
				break;

			case DHCP_OPTION_SUBNET_MASK:
				NetLog("DHCP PARSE OFFER: Parsed Option, Type SUBNET MASK.");
				if (value_length == 4)
				{
					*subnet_mask_out = address;
					have_subnet		 = TRUE;
				}
				break;
		}
	}

	if (have_type && have_dns && have_subnet && have_router)
	{
		*your_ip_out = EndianU32(header->your_ip);
		NetLog("DHCP PARSE OFFER: Success, got your-ip from DHCP Header.");
		return 0;
	}
	else
	{
		NetErr("DHCP PARSE OFFER: Failed, did not have needed Options.");
		NetErr("                  have_type: %Z", have_type, "ST_FALSE_TRUE");
		NetErr("                  have_dns: %Z", have_dns, "ST_FALSE_TRUE");
		NetErr("                  have_router: %Z", have_router, "ST_FALSE_TRUE");
		NetErr("                  have_subnet: %Z", have_subnet, "ST_FALSE_TRUE");
		return -1;
	}
}

I64 DHCPAckParse(U32 xid, U8 *data, I64 length)
{
	CDHCPHeader *header;
	I64			 error = DHCPBeginParse(&data, &length, &header);
	U8			 type;
	U8			 value_length;
	U8			*value;

	if (EndianU32(header->xid) != xid)
	{
		NetErr("DHCP PARSE ACK: Failed, parsed and parameter Transaction IDs do not match.");
		return -1;
	}

	while (length)
	{
		error = DHCPOptionParse(&data, &length, &type, &value_length, &value);

		if (error < 0)
		{
			NetErr("DHCP PARSE ACK: Failed at DHCP Parse Option.");
			return error;
		}
		if (error == 0)
		{
			break;
		}

		switch (type)
		{
			case DHCP_OPTION_MESSAGETYPE:
				if (value_length == 1 && value[0] == DHCP_MESSAGETYPE_ACK)
					return 0;
				break;
		}
	}

	NetErr("DHCP PARSE ACK: Failed.");
	return -1;
}

I64 DHCPInnerConfigure(CUDPSocket *udp_socket,
					   U32 *your_ip_out,
					   U32 *dns_ip_out,
					   U32 *router_ip_out,
					   U32 *subnet_mask_out)
{
	I64	state	= DHCP_STATE_CLIENT_START;
	I64	retries = 0;
	I64	timeout = DHCP_TIMEOUT;
	I64 error	= 0;
	U32 xid;
	U32 dhcp_addr;
	U8	buffer[2048];
	I64 count;

	CSocketAddressIPV4	ipv4_addr;
	CSocketAddressIPV4	ipv4_addr_in;

	//Shrine: setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO_MS, &timeout, sizeof(timeout)))
	udp_socket->receive_timeout_ms = timeout;

	ipv4_addr.family			= AF_INET;
	ipv4_addr.port				= EndianU16(68);
	ipv4_addr.address.address	= INADDR_ANY;

	if (UDPSocketBind(udp_socket, &ipv4_addr) < 0)
	{
		NetErr("DHCP CONFIGURE INNER: Failed to Bind UDP Socket.");
		return -1;
	}

	xid = DHCPTransactionBegin;

	while (state != DHCP_STATE_CLIENT_REQ_ACCEPTED)
	{
		switch (state)
		{
			case DHCP_STATE_CLIENT_START:
				state	= DHCP_STATE_CLIENT_DISCOVER;
				retries = 0;

				break;

			case DHCP_STATE_CLIENT_DISCOVER:
				NetLog("DHCP CONFIGURE INNER: Trying Discover.");
				error = DHCPDiscoverSend(xid);
				if (error < 0)
				{
					NetErr("DHCP CONFIGURE INNER: Failed, DHCP Send Discover error.");
					return error;
				}

				count = UDPSocketReceiveFrom(udp_socket, buffer, sizeof(buffer), &ipv4_addr_in);

				if (count > 0)
				{ // 'Try a parse offer'
					NetLog("DHCP CONFIGURE INNER: Trying Parse Offer.");
					error = DHCPOfferParse(xid, buffer, count, your_ip_out, dns_ip_out, router_ip_out, subnet_mask_out);

					if (error < 0)
						NetWarn("DHCP CONFIGURE INNER: Unsuccessful DHCP Parse Offer.");
				}

				if (count > 0 && error >= 0)
				{
					dhcp_addr	= EndianU32(ipv4_addr_in.address.address);
					state		= DHCP_STATE_CLIENT_REQUEST;
					retries		= 0;
				}
				else if (++retries == DHCP_MAX_RETRIES)
				{
					NetErr("DHCP CONFIGURE INNER: Failed, hit max retries in DHCP DISCOVER state.");
					return -1;
				}

				break;

			case DHCP_STATE_CLIENT_REQUEST:
				NetLog("DHCP CONFIGURE INNER: Trying Send Request.");
				error = DHCPRequestSend(xid, *your_ip_out, dhcp_addr);

				if (error < 0)
				{
					NetErr("DHCP CONFIGURE INNER: Failed, unsuccessful DHCP Send Request.");
					return error;
				}

				count = UDPSocketReceiveFrom(udp_socket, buffer, sizeof(buffer), &ipv4_addr_in);

				if (count > 0)
				{ // 'Try parse Ack'
					error = DHCPAckParse(xid, buffer, count);

					if (error < 0)
						NetWarn("DHCP CONFIGURE INNER: Unsuccessful DHCP Parse Ack.");
				}

				if (count > 0 && error >= 0)
				{
					dhcp_addr	= EndianU32(ipv4_addr_in.address.address);
					state		= DHCP_STATE_CLIENT_REQ_ACCEPTED;
				}
				else if (++retries == DHCP_MAX_RETRIES)
				{
					NetErr("DHCP CONFIGURE INNER: Failed, hit max retries in DHCP REQUEST state.");
					return -1;
				}

				break;
		}
	}

	return state;
}

I64 DHCPConfigure()
{
	CUDPSocket		*udp_socket = UDPSocket(AF_INET);
	CIPV4Address	 address;
	U32				 your_ip;
	U32				 dns_ip;
	U32				 router_ip;
	U32				 subnet_mask;
	I64				 state = DHCPInnerConfigure(udp_socket, &your_ip, &dns_ip, &router_ip, &subnet_mask);

	UDPSocketClose(udp_socket);

	if (state == DHCP_STATE_CLIENT_REQ_ACCEPTED)
	{
		address.address = EndianU32(your_ip);
		NetLog("$$BG,2$$$$FG,15$$DHCP CONFIGURE: Obtained IPV4 Address! : %s $$BG$$$$FG$$", NetworkToPresentation(AF_INET, &address));

		IPV4AddressSet(your_ip);
		IPV4SubnetSet(router_ip, subnet_mask);
		DNSResolverIPV4Set(dns_ip);
		return 0;
	}
	else
	{
		NetErr("$$BG,4$$DHCP CONFIGURE: Failed, incorrect state.$$BG$$");
		return -1;
	}
}


U0 NetConfigure()
{
	I64 error;

	NetLog("\n==== Configuring Network. ====\n");
	error = DHCPConfigure;

	if (error < 0)
		NetErr("==== Network Configure Failed ====");
	else
		NetLog("$$BG,2$$$$FG,15$$==== Network Configure Success ====$$FG$$$$BG$$");
}

U0 NetRep()
{
	"\n$$LTGREEN$$Network Report:$$FG$$\n\n";
	UDPRep;
	TCPRep;
	DNSRep;
	ARPRep;
	IPV4Rep;
}