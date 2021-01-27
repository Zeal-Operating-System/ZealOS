//#include "IPV4"

#define ICMP_TYPE_ECHO_REPLY	0
#define ICMP_TYPE_ECHO_REQUEST	8

class CICMPHeader // Shrine's use of id and seq indicate this header is for Address Mask Reply/Request
{
	U8	type;
	U8	code;
	U16 checksum;

	U16 identifier;
	U16 sequence_number;
};


I64 ICMPSendReply(U32 destination_ip_address,
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
								  IPV4GetAddress(),
								  destination_ip_address,
								  sizeof(CICMPHeader) + length);
	if (de_index < 0)
	{
		NetErr("ICMP SEND REPLY: Failed to allocate IPV4 packet.");
		return de_index;
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
	//return IPV4PacketFinish
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

	if (header->type == ICMP_TYPE_ECHO_REQUEST && header->code == 0)//why zero? need more #defines in here
	{
		ARPCachePut(packet->source_ip_address, packet->ethernet_frame->source_address);

		ICMPSendReply(packet->source_ip_address,
					  header->identifier,
					  header->sequence_number,
					  header->checksum,
					  packet->data   + sizeof(CICMPHeader),
					  packet->length - sizeof(CICMPHeader)); // TODO: ??
	}

	NetLog("ICMP HANDLER: Exiting.");

	return 0;
}