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

	I included some code for IPV6, currently
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

#define INET_ADDRSTRLEN		16 //pubs.opengroup.com netinit/in.h
#define INET6_ADDRSTRLEN	46

#define INET_MIN_ADDRSTRLEN		7 // ex: len of 0.0.0.0
#define INET6_MIN_ADDRSTRLEN	2 // ie: len of ::


#define IP_PARSE_STATE_NUM			0
#define IP_PARSE_STATE_DOT			1


class CSocketAddress
{
	U16	family;		// 'address family, AF_xxx'

	U8	data[14];	// '14 bytes of protocol address'
};

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
	I16	family;		// 'AF_INET'
	U16	port;		// 'in Network Byte order' ... Big Endian

	CIPV4Address address;

	U8	zeroes[8];	// 'same size as socket address'
};

class CSocketAddressIPV6
{
	U16	family;	// 'AF_INET6'
	U16 port;	// 'in Network Byte order'... Big Endian

	U32 flow_info;

	CIPV6Address address;

	U32	scope_id;
};

class CSocketAddressStorage
{/*	'designed to be large enough to
	hold both IPV4 and IPV6 structures.' */

	U16 family;

	U8 padding[26];

};

class CAddressInfo
{
	I32	flags;
	I32 family;
	I32 socket_type;
	I32 protocol;

	I64 address_length;

	CSocketAddress *address;

	U8 *canonical_name;

	CAddressInfo *next;
};

class CSocket
{
	U8	state;

	U16	type;
	U16 domain;
};

Bool IPV4AddressParse(U8 *string, U32 *destination)
{
//	U8* lexable_string;
//	lexable_string = StrReplace(string, ",", ","); // swap any commas with an unexpected value

	U8 *lexable_string = StrReplace(string, ".", ","); // swap dots with commas since Lex is easier with them.

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
							ZenithErr("Invalid value, must be 0 - 255.\n");
							return FALSE;
						}
						if (current_section > 3)
						{
							ZenithErr("IP Address can only have 4 sections.\n");
							return FALSE;
						}

						temp_destination |= cc->cur_i64 << (current_section * 8);
						current_section++;
						
						state = IP_PARSE_STATE_DOT;

						break;

					default:
						ZenithErr("Expected decimal. \n");
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
						ZenithErr("Expected dot. \n");
						return FALSE;
				}
				break;
		}
	}

	temp_destination = EndianU32(temp_destination); // store the address in Network Byte Order (Big-Endian)
	*destination = temp_destination;
	"\n\n%X\n\n", temp_destination;
	return TRUE;
}

I64 PresentationToNetwork(I64 address_family, U8 *string, CIPAddressStorage *destination)
{/*	Converts IP string to internet address class, our inet_pton().
	Destination written as CIPV4Address or CIPV6Address depending
	on value of address_family.
	The destination address is the generic class, functions
	calling this method must cast their classes in the params. 

	TODO:	test it more... clarify above comment? is casting shit needed if we do it like this?.. 
			if we declare the possible address classes, then just set them to where the
			destination is from param, wouldn't that suffice fully? I noticed that it wrote fine to
			a pointer to CIPV4Address without any complaints that it wasn't CIPAddressStorage .. */

	//CCompCtrl *cc = CompCtrlNew(string);

	CIPV4Address *ipv4_address;
	CIPV6Address *ipv6_address;

	I64 string_length = StrLen(string);

	switch (address_family)
	{
		case AF_INET:
			if (string_length > INET_ADDRSTRLEN || string_length < INET_MIN_ADDRSTRLEN)
			{
				ZenithErr("IP to Socket Address failed: Invalid Input String Size.\n");
				return -1;
			}
			ipv4_address = destination;

			IPV4AddressParse(string, &ipv4_address->address);

			break;

		case AF_INET6:
			if (string_length > INET6_ADDRSTRLEN || string_length < INET6_MIN_ADDRSTRLEN)
			{
				ZenithErr("IP to Socket Address failed: Invalid Input String Size.\n");
				return -1;
			}
			ipv6_address = destination;


			Debug("IPV6 support not implemented yet.\n");


			break;

		default:
			ZenithErr("IP to Socket Address failed: Invalid Address Family.\n");
			return -1;
	}

	//CompCtrlDel(cc);
	return 0;
	
}

U8 *NetworkToPresentation(I64 address_family, CIPAddressStorage *source)
{ // converts socket address to IP string, our inet_ntop. Taking Shrine approach of function returns U8* .

//	I64 i;

	U8 *ip_string;
//	U8* ip_string[INET_ADDRSTRLEN];
	CIPV4Address *ipv4_source;
	CIPV4Address *ipv6_source;

	switch (address_family)
	{
		case AF_INET:

			ipv4_source = source;

			StrPrint(ip_string, "%d.%d.%d.%d",
					 ipv4_source->address.u8[3],
					 ipv4_source->address.u8[2],
					 ipv4_source->address.u8[1],
					 ipv4_source->address.u8[0]);
			break;
		case AF_INET6:

			ipv6_source = source;

			Debug("IPV6 support not implemented yet.\n");

			break;
		default:
			ZenithErr("Socket Address to IP failed: Invalid Address Family.\n");
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
	ZenithErr("Socket attempted %s while in %s state.\n", request, state_string);
}




U0 SocketAccept(CSocket *socket)
{
	switch (socket->state)
	{
		case SOCKET_STATE_LISTENING:
			/*	Socket expected to stay listening.
				At protocol level, a new socket 'connected'
				to this one is expected to be made. */
			return;

		default:
			SocketStateErr("ACCEPT", socket->state);
			break;
	}
}

U0 SocketClose(CSocket *socket)
{	/* Sockets attempting close will enter close
	request state before destroying the socket at
	the protocol level. */
	socket->state = SOCKET_STATE_CLOSE_REQ;

	/*
	switch (socket->state)
	{
		case SOCKET_STATE_LISTENING:
		case SOCKET_STATE_OPEN:
			/*	Sockets can only be closed if
				they were opened or listening
				to incoming connections. */
			socket->state = SOCKET_STATE_CLOSE_REQ;
			break;

		default:
			SocketStateErr("CLOSE", socket->state);
			break;
	}*/
}

U0 SocketBind(CSocket *socket)
{
	switch (socket->state)
	{
		case SOCKET_STATE_READY:
			/*	Sockets can only be bound
				if they are in initial state. */
			socket->state = SOCKET_STATE_BIND_REQ;
			break;

		default:
			SocketStateErr("BIND", socket->state);
			break;
	}
}

U0 SocketConnect(CSocket *socket)
{
	switch (socket->state)
	{
		case SOCKET_STATE_READY:
			/*	Sockets can only be connected
				if they are in initial state. */
			socket->state = SOCKET_STATE_CONNECT_REQ;
			break;

		default:
			SocketStateErr("CONNECT", socket->state);
			break;
	}
}

U0 SocketListen(CSocket *socket)
{
	switch (socket->state)
	{
		case SOCKET_STATE_BOUND:
			/*	A socket must be bound to
				set it to listening. */
			socket->state = SOCKET_STATE_LISTEN_REQ;
			break;

		default:
			SocketStateErr("LISTEN", socket->state);
			break;
	}
}

U0 SocketReceive(CSocket *socket)
{
	switch (socket->state)
	{
		case SOCKET_STATE_OPEN:
		case SOCKET_STATE_BOUND:
			/*	Sockets can only recv when
				connected to or bound. */
			break;

		default:
			SocketStateErr("RECEIVE", socket->state);
			break;
	}
}

U0 SocketReceiveFrom(CSocket *socket)
{
	switch (socket->state)
	{
		case SOCKET_STATE_OPEN:
		case SOCKET_STATE_BOUND:
			/*	Sockets can only recvfrom when
				connected to or bound. */
			break;

		default:
			SocketStateErr("RECEIVE FROM", socket->state);
			break;
	}
}

U0 SocketSend(CSocket *socket)
{
	switch (socket->state)
	{
		case SOCKET_STATE_OPEN:
			/*	Sockets can only send when
				they have been connected to. */
			break;

		default:
			SocketStateErr("SEND", socket->state);
			break;
	}
}

U0 SocketSendTo(CSocket *socket)
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
			break;

		default:
			SocketStateErr("SEND TO", socket->state);
			break;
	}
}