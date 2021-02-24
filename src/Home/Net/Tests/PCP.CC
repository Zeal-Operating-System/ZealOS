// Port Control Protocol prototyping.
// RFC 6887

class CPCPRequestHeader
{
	U8	version;
	U8	opcode;				// includes R bit.
	U16	reserved;			// must be all 0 on TX
	U32	req_lifetime;		// seconds. 0 interpreted as 'delete'.
	U8	pcp_client_ip[16];	// source ipv4 addr converted to ipv4-mapped ipv6 as per spec. 128 bits
};

class CPCPMapRequest
{
	CPCPRequestHeader	header;
	U8					nonce[12];		// "Mapping Nonce" 96 bits of random vals.
	U8					protocol;		// 6 TCP. 17 UDP. 0 'all protocols'.
	U8					reserved[3];	// 24 bits, TX must be 0, ignore on RX.

	U16					internal_port;
	/*	internal_port. 0 'all ports' legal only on lifetime 0 (delete) or client req 'all ports'.
		must be ignored on RX. */

	U16					external_port;
	/*	external_port. 'suggested'. if client doesnt know it or has no preference it must be 0.*/

	U8					external_ip[16];
	/*	external_ip. 'suggested'. if client doesnt know it or no preference,
								  it must use 'address-family-specific all-zero address. */

};

I64 PCPSendMapRequest(U16 internal_port, U16 external_port=NULL, U32 external_ip=NULL)
{
	U8			 	*frame;
	CPCPMapRequest	*request;
	I64				 de_index;
	I64				 i;

	de_index = UDPPacketAllocate(&frame,
								 IPV4AddressGet,
								 5351,
								 ipv4_globals.ipv4_router_address,
								 5351,
								 sizeof(CPCPMapRequest));
	if (de_index < 0)
	{
		NetErr("PCP SEND MAP REQ: Failed, UDPPacketAllocate returned error.");
		return de_index;
	}

	request = frame;

	request->header.version			= 2;
	request->header.opcode			= 1; // MAP
	request->header.req_lifetime	= 60; // live for 1 min.

	// force local IPV4 addr into IPV4-mapped-IPV6
	for (i = 0; i < 10; i++) // first 80 bits 0
		request->header.pcp_client_ip[i] = 0;

	for (; i < 10 + 2; i++) // next 16 bits 1
		request->header.pcp_client_ip[i] = 0xFF;

	*(&request->header.pcp_client_ip[i](U32 *)) = EndianU32(IPV4AddressGet);
	//

	// set random 'nonce'
	for (i = 0; i < 12; i++)
		request->nonce[i] = RandU8;

	request->protocol = IP_PROTOCOL_UDP;

	request->internal_port = internal_port;
	request->external_port = external_port;

	if (!external_ip)
	{ // if no specified ext ip, use specific ipv4-mapped-ipv6 all-zeroes address.
		for (i = 0; i < 10; i++)
			request->external_ip[i] = 0;
		for (; i < 10 + 2; i++)
			request->external_ip[i] = 0xFF;
		*(&request->external_ip[i](U32 *)) = 0;
	}
	else
	{ // else, map to param ip
		for (i = 0; i < 10; i++)
			request->external_ip[i] = 0;
		for (; i < 10 + 2; i++)
			request->external_ip[i] = 0xFF;
		*(&request->external_ip[i](U32 *)) = EndianU32(external_ip);
	}

	UDPPacketFinish(de_index);
	return 0;

}

PCPSendMapRequest(0xDEAD, 0xBEEF);