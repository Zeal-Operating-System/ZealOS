#define ICMP_TYPE_ECHO_REPLY	0
#define ICMP_TYPE_ECHO_REQUEST	8
#define ICMP_CODE_ECHO			0 // RFC 792: "Echo or Echo Reply Message". 0 is the only code explicitly defined for Echo.

class CICMPHeader
{
	U8	type;
	U8	code;
	U16 checksum;

	U16 identifier;
	U16 sequence_number;
};


U0 ICMPReplySend(U32 destination_ip_address,
				  U16 identifier,
				  U16 sequence_number,
				  U16 request_checksum,
				  U8 *payload,
				  I64 length)
{
	U8			*frame;
	I64			 de_index;
	CICMPHeader	*header;

	de_index = IPV4PacketAllocate(&frame,
								  IP_PROTOCOL_ICMP,
								  IPV4AddressGet,
								  destination_ip_address,
								  sizeof(CICMPHeader) + length);
	if (de_index < 0)
	{
		NetErr("ICMP SEND REPLY: Failed to allocate IPV4 packet.");
		return;
	}

	header = frame;

	header->type				= ICMP_TYPE_ECHO_REPLY;
	header->code				= 0;	// why is 0 okay?
	header->checksum			= EndianU16(EndianU16(request_checksum) + 0x0800);
	header->identifier			= identifier;
	header->sequence_number		= sequence_number;
	// TODO: header checksum is awful. Shrine says hack alert.

	MemCopy(frame + sizeof(CICMPHeader), payload, length);

	IPV4PacketFinish(de_index);
}

I64 ICMPHandler(CIPV4Packet *packet)
{
	CICMPHeader *header;

	if (packet->length < sizeof(CICMPHeader))
	{
		NetErr("ICMP HANDLER: Caught wrong IPV4 length.");
		return -1;
	}

	header = packet->data;

	if (header->type == ICMP_TYPE_ECHO_REQUEST && header->code == ICMP_CODE_ECHO)
	{
		ARPCachePut(packet->source_ip_address, packet->ethernet_frame->source_address);

		ICMPReplySend(packet->source_ip_address,
					  header->identifier,
					  header->sequence_number,
					  header->checksum,
					  packet->data   + sizeof(CICMPHeader),	// Data payload at IPV4Packet data location after the ICMP header
					  packet->length - sizeof(CICMPHeader));// Payload length is size of packet after dropping header.
	}
	else
		NetWarn("ICMP HANDLER: Unhandled ICMP packet. type, code: 0x%X, 0x%X", header->type, header->code);

	NetLog("ICMP HANDLER: Exiting.");

	return 0;
}