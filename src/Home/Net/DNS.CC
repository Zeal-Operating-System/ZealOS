#include "UDP";

// https://www2.cs.duke.edu/courses/fall16/compsci356/DNS/DNS-primer.pdf
// https://en.wikipedia.org/wiki/Domain_Name_System

// DNS Cache is a HashTable, similar to ARP Cache

#define DNS_HASHTABLE_SIZE	2048	// 1024 might be fine, test it
#define HTT_DNS				0x00100 // identical to HTT_DICT_WORD

#define DNS_FLAG_RD		0x0100

#define DNS_OP_QUERY	0

#define DNS_TYPE_A		1

#define DNS_CLASS_IN	1

#define DNS_TIMEOUT		5000
class CDNSHash:CHash
{	// store U8 *hostname as CHash->str U8 *
	CAddressInfo info;
	// Shrine has 'TODO: honor TTL' ...
	// Duke: 'TTL: the number of seconds the results can be cached'
	// perhaps have a separate task for removing cached results ?
};

class CDNSDomainName
{
	U8 **labels;
	I64  num_labels;
};

class CDNSQuestion
{
	CDNSQuestion	*next;
	CDNSDomainName	 q_name;
	U16				 q_type;
	U16				 q_class;
};

class CDNSHeader
{
	U16 id;
	U16 flags;
	U16 q_count;	// number of entries in question section
	U16 a_count;	// number of resource records in answer section
	U16 ns_count;	// number of name server resource records in authority records section
	U16 ar_count;	// number of resource records in additional records section
};

class CDNSRR
{ // RR: Resource Record
	CDNSRR			*next;
	CDNSDomainName	 name;		// name of the node this record is for
	U16				 type;		// RR type, e.g. 44=SSHFP, 15=MX, 49=DHCID ...
	U16				 rr_class;	// class code
	U32				 ttl;		// count in seconds that RR stays valid (max = 2^31 - 1)
	U16				 rd_length;	// length of r_data member
	U8				*r_data;	// additional RR-specific data
};

class CDNSGlobals
{
	U16					addr_family;
	CIPAddressStorage	dns_ip;

} dns_globals;

CHashTable *dns_cache = NULL;

U0 DNSCacheInit()
{
	dns_cache = HashTableNew(DNS_HASHTABLE_SIZE);

	MemSet(&dns_globals.dns_ip, 0, sizeof(CIPAddressStorage));
	dns_globals.addr_family = 0;
}

CDNSHash *DNSCacheFind(U8 *hostname)
{
	CDNSHash *entry = HashFind(hostname, dns_cache, HTT_DNS);

	if (entry == NULL)
		ZenithErr("Could not find a hostname in the DNS Cache.\n");

	return entry;
}

CDNSHash *DNSCachePut(U8 *hostname, CAddressInfo *info)
{
	CDNSHash *entry = DNSCacheFind(hostname);

	if (!entry)
	{
		entry = CAlloc(sizeof(CDNSHash));
		entry->str = StrNew(hostname);
		AddressInfoCopy(&entry->info, info);

		HashAdd(entry, dns_cache);
	}
	else
		ZenithWarn("DNS Cache Put attempted but entry was already found in Cache. TODO: overwrite?");

	return entry;
}

I64 DNSCalculateQuestionSize(CDNSQuestion *q)
{ // ??
	I64 i, size = 0;

	for (i = 0; i < q->q_name.num_labels; i++)
	{
		size += 1 + StrLen(q->q_name.labels[i]);
	}

	return size + 1 + 4;
}

U0 DNSSerializeQuestion(U8 *buffer, CDNSQuestion *q)
{ // ??
	I64 i;
	U8 *label;

	for (i = 0; i < q->q_name.num_labels; i++)
	{
		label = q->q_name.labels[i];

		*(buffer++) = StrLen(label);

		while (*label)
			*(buffer++) = *(label++);
	}

	*(buffer++) = 0;
	*(buffer++) = q->q_type >> 8;
	*(buffer++) = q->q_type & 0xFF;
	*(buffer++) = q->q_class >> 8;
	*(buffer++) = q->q_class & 0xFF;
}

I64 DNSSendQuestion(U16 id, U16 local_port, CDNSQuestion *q)
{
	CIPV4Address* ipv4_addr;
	U8 *frame;
	U16 flags;
	CDNSHeader *header;
	I64 de_index;

	switch (dns_globals.addr_family)
	{
		case AF_UNSPEC: // 0, global dns ip not set
			return -1;

		case AF_INET6:
			ZenithErr("IPV6 not supported yet in DNS.\n");
			throw('DNS');

		case AF_INET:
			ipv4_addr = &dns_globals.dns_ip;

			if (!*ipv4_addr)
				return -1;
	}

	// UDPPacketAllocate currently only accepts IPV4 ...
	de_index = UDPPacketAllocate(&frame,
								 IPV4GetAddress(),
								 local_port,
								 *ipv4_addr,
								 53,
								 sizeof(CDNSHeader) + DNSCalculateQuestionSize(q));
	if (de_index < 0)
		return de_index;

	flags = (DNS_OP_QUERY << 11) | DNS_FLAG_RD;

	header = frame;

	header->id			= EndianU16(id);
	header->flags		= EndianU16(flags);
	header->q_count		= EndianU16(1);
	header->a_count		= 0;
	header->ns_count	= 0;
	header->ar_count	= 0;

	DNSSerializeQuestion(frame + sizeof(CDNSHeader), q);

	UDPPacketFinish(de_index);
	return 0;

}


I64 DNSParseDomainName(U8 *packet_data, I64 packet_length, U8 **data_inout, I64 *length_inout, CDNSDomainName *name_out)
{ // these methods look not-so-good, ngl.
	U8 *data = *data_inout;
	U8 *name_buf;
	I64 length = *length_inout;
	I64 label_len;
	Bool jump_taken = FALSE;

	if (length < 1)
	{
		ZenithErr("DNS parsed domain name, hit length of 0 or less\n");
		return -1;
	}

	name_out->labels		= CAlloc(16 * sizeof(U8 *));
	name_out->num_labels	= 0;

	name_buf = CAlloc(256); // ?..
	name_out->labels[0] = name_buf;

	while (length)
	{
		label_len = *(data++);
		length--;

		if (label_len == 0)
			break;
		else if (label_len >= 192)
		{
			label_len &= 0x3F; // ...

			if (!jump_taken)
			{
				*data_inout		= data   + 1;
				*length_inout	= length - 1;
				jump_taken		= TRUE;
				ZenithLog("UDP parsed domain name, jump taken\n");
			}

			data	= packet_data + ((label_len << 8) | *data);
			length	= packet_data + packet_length - data;
		}
		else
		{
			if (length < label_len)
				return -1; // ?

			MemCopy(name_buf, data, label_len);
			data	+= label_len;
			length	-= label_len;

			name_buf[label_len] = 0;
			name_out->labels[name_out->num_labels++] = name_buf;

			name_buf += label_len + 1;
		}
	}

	if (!jump_taken)
	{
		*data_inout		= data;
		*length_inout	= length;
	}

	return 0;
}


I64 DNSParseQuestion(U8 *packet_data, I64 packet_length, U8 **data_inout, I64 *length_inout, CDNSQuestion *q_out)
{
	U8 *data;
	I64 length;
	I64 error = DNSParseDomainName(packet_data, packet_length, data_inout, length_inout, &q_out->q_name);

	if (error < 0)
		return error;

	data	= *data_inout;
	length	= *length_inout;

	if (length < 4)
		return -1;

	q_out->next		= NULL;
	q_out->q_type	= (data[1] << 8) | data[0];
	q_out->q_class	= (data[3] << 8) | data[2];

	*data_inout		= data   + 4;
	*length_inout	= length - 4;

	return 0;
}

I64 DNSParseRR(U8 *packet_data, I64 packet_length, U8 **data_inout, I64 *length_inout, CDNSRR *rr_out)
{
	U8 *data;
	I64 length;
	I64 record_length;
	I64 error = DNSParseDomainName(packet_data, packet_length, data_inout, length_inout, &rr_out->name);

	if (error < 0)
		return error;

	data	= *data_inout;
	length	= *length_inout;

	if (length < 10)
		return -1;

	rr_out->next = NULL;
	MemCopy(&rr_out->type, data, 10); // ???

	record_length = 10 + EndianU16(rr_out->rd_length);

	if (length < record_length)
		return -1;

	rr_out->r_data = data + 10; // ??

	*data_inout		= data   + record_length;
	*length_inout	= length - record_length;

	return 0;
}

I64 DNSParseResponse(U16 id, U8 *data, I64 len, CDNSHeader **header_out, CDNSQuestion **questions_out, CDNSRR **answers_out)
{
	CDNSHeader		*header;
	CDNSQuestion	*question;
	CDNSRR			*answer;
	I64				 i;
	U8				*packet_data	= data;
	I64				 packet_length	= length;

	if (length < sizeof(CDNSHeader))
	{
		ZenithErr("DNS Response Parsed, length too short.\n");
		return -1;
	}

	header = data;
	data += sizeof(CDNSHeader);

	if (id != 0 && EndianU16(header->id) != id)
	{
		ZenithErr("DNS Response Parsed, header id mismatch.\n");
		return -1;
	}

	for (i = 0; i < EndianU16(header->q_count); i++)
	{
		question = CAlloc(sizeof(CDNSQuestion));
		if (DNSParseQuestion(packet_data, packet_length, &data, &length, question) < 0)
			return -1;

		question->next = *questions_out;
		*questions_out = question;
	}

	for (i = 0; i < EndianU16(header->a_count); i++)
	{
		answer = CAlloc(sizeof(CDNSRR));
		if (DNSParseRR(packet_data, packet_length, &data, &length, answer) < 0)
			return -1;

		answer->next = *answers_out;
		*answers_out = answer;
	}

	*header_out = header;
	return 0;

}

U0 DNSBuildQuestion(CDNSQuestion *q, U8 *name)
{
	U8 *copy = StrNew(name);
	U8 *dot;

	q->next					= NULL;
	q->q_name.labels		= CAlloc(16 * sizeof(U8 *));
	q->q_name.labels[0]		= 0;
	q->q_name.num_labels	= 0;
	q->q_type				= DNS_TYPE_A;
	q->q_class				= DNS_CLASS_IN;

	while (*copy)
	{
		q->q_name.labels[q->q_name.num_labels++] = copy;
		dot = StrFirstOcc(copy, ".");

		if (dot)
		{
			*dot = 0;
			copy = dot + 1;
		}
		else
			break;
	}
}

// these Free methods bother me a bit...
U0 DNSFreeQuestion(CDNSQuestion *q)
{
	Free(q->q_name.labels[0]);
}

U0 DNSFreeRR(CDNSRR *r)
{
	Free(rr->name.labels[0]);
}

U0 DNSFreeQuestionChain(CDNSQuestion *questions)
{
	CDNSQuestion *next;

	while (questions)
	{
		next = questions->next;
		DNSFreeQuestion(questions);
		Free(questions);
		questions = next;
	}
}

U0 DNSFreeRRChain(CDNSRR *rrs)
{ // Shrine sets rrs->next to a CDNSQuestion when it would be a CDNSRR ... assuming it's wrong and fixing it here..
	CDNSRR *next;

	while (rrs)
	{
		next = rrs->next;
		DNSFreeRR(rrs);
		Free(rrs);
		rrs = next;
	}
}

/*
I64 DNSRunQuery(CUDPSocket *udp_socket, U8 *name, U16 port, CAddressInfo **result_out)
{ // IPV4-UDP-based
	I64  retries	= 0;
	I64	 timeout	= DNS_TIMEOUT;
	U16	 local_port	= RandU16;
	U16  id			= RandU16;
	I64  error		= 0;
	U8  *buffer;
	I64  count;
	Bool have;

	CDNSQuestion	 q;
	CDNSHeader		*header;
	CDNSQuestion	*questions;
	CDNSRR			*answers;
	CDNSRR			*a;

	CSocketAddressIPV4	 ipv4_addr;
	CSocketAddressIPV4	 ipv4_addr_in; // ?
	CAddressInfo		*res;

	//setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO_MS, &timeout, sizeof(timeout))
	udp_socket->receive_timeout_ms = timeout;

	

}
*/

/*
I64 DNSRunQuery(socket?, U8 *name, U16 port, CAddressInfo **result_out)

I64 DNSGetAddressInfo(U8 *node, U8 *service, CAddressInfo *hints, CAddressInfo **result)

U0 DNSSetResolverIPV4(U32 ip) // funny enough he explicitly labeled IPV4.........

U0 Host(U8 *hostname)

U0 DNSInit()

*/

DNSCacheInit;