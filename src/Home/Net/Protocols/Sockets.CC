/*	docs.idris-lang.org/en/latest/st/examples.html
	beej.us/guide/bgnet/html/

	Sockets are non-standard, a simple
	Finite State Machine. The functions'
	only args are the socket. Socket functions
	requiring more parameters should be
	defined at the protocol level. 

	The state machine exists to allow
	protocol code to execute code in
	the appropriate order. When calling
	a socket function, code can use
	the modified/unmodified states to
	determine next procedure. 

	Some code is inclded for IPV6, currently
	unused. */

#define SOCKET_STATE_READY			0
#define SOCKET_STATE_BIND_REQ		1
#define SOCKET_STATE_CONNECT_REQ	2
#define SOCKET_STATE_BOUND			3
#define SOCKET_STATE_LISTEN_REQ		4
#define SOCKET_STATE_LISTENING		5
#define SOCKET_STATE_OPEN			6
#define SOCKET_STATE_CLOSE_REQ		7
#define SOCKET_STATE_CLOSED			8

#define SOCKET_STREAM	1
#define SOCKET_DATAGRAM	2
#define SOCKET_RAW		3

#define AF_UNSPEC	0
#define	AF_INET		2
#define AF_INET6	10

#define INADDR_ANY	0

#define INET_ADDRSTRLEN		16 //pubs.opengroup.com netinit/in.h
#define INET6_ADDRSTRLEN	46

#define INET_MIN_ADDRSTRLEN		7 // ex: len of 0.0.0.0
#define INET6_MIN_ADDRSTRLEN	2 // ie: len of ::


#define IP_PARSE_STATE_NUM			0
#define IP_PARSE_STATE_DOT			1

class CIPV4Address
{
	U32 address;	// 'in Network Byte order' ... Big Endian
};

class CIPV6Address
{
	U8	address[16]; // a clear #define would be nice
};

class CIPAddressStorage
{// class specifically meant to be generic casted either IPV4 or IPV6 Address.
	U8	padding[16];
};

class CSocketAddressIPV4
{
	U16				family;		// 'AF_INET'
	U16				port;		// 'in Network Byte order' ... Big Endian
	CIPV4Address	address;
	U8				zeroes[8];	// 'same size as socket address'
};

class CSocketAddressIPV6
{
	U16				family;	// 'AF_INET6'
	U16				port;	// 'in Network Byte order'... Big Endian
	U32				flow_info;
	CIPV6Address	address;
	U32				scope_id;
};

class CSocketAddressStorage
{/*	'designed to be large enough to
	hold both IPV4 and IPV6 structures.' */

	U16 family;
	U8	padding[26];
};

class CAddressInfo
{
	I32						 flags;
	I32						 family;
	I32						 socket_type;
	I32						 protocol;
	I64						 address_length;
	CSocketAddressStorage	*address;
	U8						*canonical_name;
	CAddressInfo			*next;
};

class CSocket
{
	U8	state;

	U16	type;
	U16 domain;
};

U0 AddressInfoCopy(CAddressInfo *out, CAddressInfo *in)
{ // assumes *out already exists
	MemCopy(out, in, sizeof(CAddressInfo));

	if (in->address)
	{
		out->address = CAlloc(in->address_length);
		MemCopy(out->address, in->address, in->address_length);
	}

	if (in->canonical_name)
	{
		out->canonical_name = StrNew(in->canonical_name);
	}
}

U0 AddressInfoFree(CAddressInfo *info)
{
	CAddressInfo *next;

	while (info)
	{
		next = info->next;

		Free(info->address);
		Free(info->canonical_name);
		Free(info);

		info = next;
	}
}

Bool IPV4AddressParse(U8 *string, U32 *destination)
{
	U8 *lexable_string = StrNew(string);

	lexable_string = StrReplace(lexable_string, ".", ","); // swap dots with commas since Lex is easier with them.

	CCompCtrl *cc = CompCtrlNew(lexable_string);
	//Bts(&cc->opts, OPTf_DECIMAL_ONLY);

	cc->opts |= 1 << OPTf_DECIMAL_ONLY;

	I64 tk;

	I64 state = IP_PARSE_STATE_NUM;
	U32 temp_destination = 0;

	I64 current_section = 0; // IPV4 address has 4 total sections

	while (tk = Lex(cc))
	{
		switch (state)
		{
			case IP_PARSE_STATE_NUM:
				switch (tk)
				{
					case TK_I64:
						if (cc->cur_i64 > 255 || cc->cur_i64 < 0)
						{
							NetErr("IPV4 ADDRESS PARSE: Invalid value, must be 0 - 255.");
							return FALSE;
						}
						if (current_section > 3)
						{
							NetErr("IPV4 ADDRESS PARSE: IP Address can only have 4 sections.");
							return FALSE;
						}

						temp_destination |= cc->cur_i64 << (current_section * 8);
						current_section++;
						
						state = IP_PARSE_STATE_DOT;

						break;

					default:
						NetErr("IPV4 ADDRESS PARSE: Expected decimal. ");
						return FALSE;
				}
				break;

			case IP_PARSE_STATE_DOT:
				switch (tk)
				{
					case ',':
						state = IP_PARSE_STATE_NUM;
						break;

					default:
						NetErr("IPV4 ADDRESS PARSE: Expected dot. ");
						return FALSE;
				}
				break;
		}
	}

	CompCtrlDel(cc);

	temp_destination = EndianU32(temp_destination); // store the address in Network Byte Order (Big-Endian)
	*destination = temp_destination;

	return TRUE;
}

I64 PresentationToNetwork(I64 address_family, U8 *string, CIPAddressStorage *destination)
{
/*	Converts IP string to internet address class, our inet_pton().
	Destination written as CIPV4Address or CIPV6Address depending
	on value of address_family.
	The destination address is the generic class, functions
	calling this method must cast their classes in the params. */

	CIPV4Address *ipv4_address;
	CIPV6Address *ipv6_address;

	I64 string_length = StrLen(string);

	switch (address_family)
	{
		case AF_INET:
			if (string_length > INET_ADDRSTRLEN || string_length < INET_MIN_ADDRSTRLEN)
			{
				NetErr("IP to Socket Address failed: Invalid Input String Size.");
				return -1;
			}
			ipv4_address = destination;

			if (!IPV4AddressParse(string, &ipv4_address->address))
				return -1;

			break;

		case AF_INET6:
			if (string_length > INET6_ADDRSTRLEN || string_length < INET6_MIN_ADDRSTRLEN)
			{
				NetErr("IP to Socket Address failed: Invalid Input String Size.");
				return -1;
			}
			ipv6_address = destination;


			NetErr("IP to Socket Address failed: FIXME, IPV6 support not implemented yet.\n");
			return -1;

		default:
			NetErr("IP to Socket Address failed: Invalid Address Family.");
			return -1;
	}

	return 0;
	
}

U8 *NetworkToPresentation(I64 address_family, CIPAddressStorage *source)
{ // converts socket address to IP string, our inet_ntop. Taking Shrine approach of function returns U8* .


	U8			 *ip_string = NULL;
	CIPV4Address *ipv4_source;
	CIPV4Address *ipv6_source;

	switch (address_family)
	{
		case AF_INET:

			ipv4_source = source;

			ip_string = MStrPrint("%d.%d.%d.%d",
					 ipv4_source->address.u8[0],
					 ipv4_source->address.u8[1],
					 ipv4_source->address.u8[2],
					 ipv4_source->address.u8[3]);
			break;

		case AF_INET6:

			ipv6_source = source;

			NetErr("Socket Address to IP failed: FIXME, IPV6 support not implemented yet.\n");
			return -1;

			break;
		default:
			NetErr("Socket Address to IP failed: Invalid Address Family.");
			break;
	}

	return ip_string;
}


CSocket *Socket(U16 domain, U16 type)
{
	CSocket *socket = CAlloc(sizeof(CSocket));

	socket->domain = domain;
	socket->type = type;

	socket->state = SOCKET_STATE_READY;

	return socket;
}

U0 SocketStateErr(U8 *request, U8 state)
{
	U8 *state_string;
	switch (state)
	{
		case SOCKET_STATE_READY:
			state_string = StrNew("READY");
			break;
		case SOCKET_STATE_BIND_REQ:
			state_string = StrNew("BIND REQUEST");
			break;
		case SOCKET_STATE_CONNECT_REQ:
			state_string = StrNew("CONNECT REQUEST");
			break;
		case SOCKET_STATE_BOUND:
			state_string = StrNew("BOUND");
			break;
		case SOCKET_STATE_LISTEN_REQ:
			state_string = StrNew("LISTEN REQUEST");
			break;
		case SOCKET_STATE_LISTENING:
			state_string = StrNew("LISTENING");
			break;
		case SOCKET_STATE_OPEN:
			state_string = StrNew("OPEN");
			break;
		case SOCKET_STATE_CLOSE_REQ:
			state_string = StrNew("CLOSE REQUEST");
			break;
		case SOCKET_STATE_CLOSED:
			state_string = StrNew("CLOSED");
			break;
	}
	NetErr("Socket attempted %s while in %s state.", request, state_string);
}

Bool SocketAccept(CSocket *socket)
{
	switch (socket->state)
	{
		case SOCKET_STATE_LISTENING:
			/*	Socket expected to stay listening.
				At protocol level, a new socket 'connected'
				to this one is expected to be made. */
			return TRUE;

		default:
			SocketStateErr("ACCEPT", socket->state);
			return FALSE;
	}
}

Bool SocketClose(CSocket *socket)
{	/* Sockets attempting close will enter close
	request state before destroying the socket at
	the protocol level. */
	socket->state = SOCKET_STATE_CLOSE_REQ;
	return TRUE;
}

Bool SocketBind(CSocket *socket)
{
	switch (socket->state)
	{
		case SOCKET_STATE_READY:
			/*	Sockets can only be bound
				if they are in initial state. */
			socket->state = SOCKET_STATE_BIND_REQ;
			return TRUE;

		default:
			SocketStateErr("BIND", socket->state);
			return FALSE;
	}
}

Bool SocketConnect(CSocket *socket)
{
	switch (socket->state)
	{
		case SOCKET_STATE_READY:
			/*	Sockets can only be connected
				if they are in initial state. */
			socket->state = SOCKET_STATE_CONNECT_REQ;
			return TRUE;

		default:
			SocketStateErr("CONNECT", socket->state);
			return FALSE;
	}
}

Bool SocketListen(CSocket *socket)
{
	switch (socket->state)
	{
		case SOCKET_STATE_BOUND:
			/*	A socket must be bound to
				set it to listening. */
			socket->state = SOCKET_STATE_LISTEN_REQ;
			return TRUE;

		default:
			SocketStateErr("LISTEN", socket->state);
			return FALSE;
	}
}

Bool SocketReceive(CSocket *socket)
{
	switch (socket->state)
	{
		case SOCKET_STATE_OPEN:
		case SOCKET_STATE_BOUND:
			/*	Sockets can only recv when
				connected to or bound. */
			return TRUE;

		default:
			SocketStateErr("RECEIVE", socket->state);
			return FALSE;
	}
}

Bool SocketReceiveFrom(CSocket *socket)
{
	switch (socket->state)
	{
		case SOCKET_STATE_OPEN:
		case SOCKET_STATE_BOUND:
			/*	Sockets can only recvfrom when
				connected to or bound. */
			return TRUE;

		default:
			SocketStateErr("RECEIVE FROM", socket->state);
			return FALSE;
	}
}

Bool SocketSend(CSocket *socket)
{
	switch (socket->state)
	{
		case SOCKET_STATE_OPEN:
			/*	Sockets can only send when
				they have been connected to. */
			return TRUE;

		default:
			SocketStateErr("SEND", socket->state);
			return FALSE;
	}
}

Bool SocketSendTo(CSocket *socket)
{
	switch (socket->state)
	{
		case SOCKET_STATE_OPEN:
		case SOCKET_STATE_BOUND:
		case SOCKET_STATE_READY:
			/*	Sockets can only sendto when
				connected to, bound, or in
				initial state. Protocol logic
				will determine how to change
				state based on params. */
			return TRUE;

		default:
			SocketStateErr("SEND TO", socket->state);
			return FALSE;
	}
}