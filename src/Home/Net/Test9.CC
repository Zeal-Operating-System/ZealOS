"\n$$TX+UL,\"Making new socket\"$$\n";

CUDPSocket *s = UDPSocket(AF_INET);
CSocketAddressIPV4 *addr = CAlloc(sizeof(CSocketAddressIPV4));

ClassRep(s,, 9);
ClassRep(addr,, 9);

"\n$$TX+UL,\"Setting addr family to AF_INET and port to 0xDEAF in B.E., then P to N with 102.33.6.1\"$$\n";

addr->family = AF_INET;
addr->port = EndianU16(0xDEAF);
PresentationToNetwork(AF_INET,"102.33.6.1",&addr->address);

ClassRep(addr,, 9);

"\n$$TX+UL,\"UDPSocket bind with socket to addr\"$$\n";

UDPSocketBind(s, addr);

ClassRep(s,, 9);

"\n$$TX+UL,\"Global Tree:\"$$\n";

ClassRep(udp_globals.bound_socket_tree,, 9);

"\n$$TX+UL,\"Global Tree: Port 0xDEAF Queue\"$$\n";

ClassRep(udp_globals.bound_socket_tree->queue,, 9);






"\n$$TX+UL,\"Closing first socket\"$$\n";

UDPSocketClose(s);

"\n$$TX+UL,\"Global Tree:\"$$\n";

ClassRep(udp_globals.bound_socket_tree,, 9);

"\n$$TX+UL,\"Global Tree: Port 0xDEAF Queue\"$$\n";

ClassRep(udp_globals.bound_socket_tree->queue,, 9);
ClassRep(udp_globals.bound_socket_tree->queue->socket,, 9);