/*
CUDPSocket *s = UDPSocket(AF_INET);

CSocketAddressIPV4 *addr = CAlloc(sizeof(CSocketAddressIPV4));

ClassRep(addr);
Class:"CSocketAddressIPV4"
15A984E30 $FG,2$family              :$FG$0000 
15A984E32 $FG,2$port                :$FG$0000 
15A984E34 $TR-C,"address"$
$ID,2$Class:"CIPV4Address"
15A984E34 $FG,2$address             :$FG$00000000 
$ID,-2$15A984E38 $FG,2$zeroes              :$FG$00 00 00 00 00 00 00 00 

0.000360s
addr->family = AF_INET;
0.000006s ans=0x00000002=2
addr->port = EndianU16(0xDEAF);
0.000007s ans=0x0000AFDE=45022
PresentationToNetwork(AF_INET,"102.33.6.1",&addr->address);


66210601

0.000027s ans=0x00000000=0
ClassRep(addr);
Class:"CSocketAddressIPV4"
15A984E30 $FG,2$family              :$FG$0002 
15A984E32 $FG,2$port                :$FG$AFDE 
15A984E34 $TR-C,"address"$
$ID,2$Class:"CIPV4Address"
15A984E34 $FG,2$address             :$FG$66210601 
$ID,-2$15A984E38 $FG,2$zeroes              :$FG$00 00 00 00 00 00 00 00 

0.000385s
UDPSocketBind(s, addr);
0.000008s ans=0x00000000=0
ClassRep(s);
Class:"CUDPSocket"
15A982C58 $TR,"socket"$
$ID,2$Class:"CSocket"
15A9931E8 $FG,2$state               :$FG$03 
15A9931E9 $FG,2$type                :$FG$0002 
15A9931EB $FG,2$domain              :$FG$0002 
$ID,-2$15A982C60 $FG,2$receive_timeout_ms  :$FG$0000000000000000 
15A982C68 $FG,2$receive_max_timeout :$FG$0000000000000000 
15A982C70 $FG,2$receive_buffer      :$FG$
15A982C78 $FG,2$receive_len         :$FG$0000000000000000 
15A982C80 $TR-C,"receive_address"$
$ID,2$Class:"CSocketAddressIPV4"
15A982C80 $FG,2$family              :$FG$0002 
15A982C82 $FG,2$port                :$FG$0000 
15A982C84 $TR,"address"$
$ID,2$$ID,-2$15A982C88 $FG,2$zeroes              :$FG$00 00 00 00 00 00 00 00 
$ID,-2$15A982C90 $FG,2$bound_to            :$FG$DEAF 

0.000526s
ClassRep(&s->receive_address);
Class:"CSocketAddressIPV4"
15A982C80 $FG,2$family              :$FG$0002 
15A982C82 $FG,2$port                :$FG$0000 
15A982C84 $TR-C,"address"$
$ID,2$Class:"CIPV4Address"
15A982C84 $FG,2$address             :$FG$66210601 
$ID,-2$15A982C88 $FG,2$zeroes              :$FG$00 00 00 00 00 00 00 00 

0.000323s

*/

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
//ClassRep(&s->receive_address,, 9);

"\n$$TX+UL,\"Global Tree:\"$$\n";

ClassRep(udp_globals.bound_socket_tree,, 9);

"\n$$TX+UL,\"Global Tree: Port 0xDEAF Queue\"$$\n";

ClassRep(udp_globals.bound_socket_tree->queue,, 9);

///

"\n$$TX+UL,\"Making new socket\"$$\n";

CUDPSocket *s2 = UDPSocket(AF_INET);
CSocketAddressIPV4 *addr2 = CAlloc(sizeof(CSocketAddressIPV4));

ClassRep(s2,, 9);
ClassRep(addr2,, 9);

"\n$$TX+UL,\"Setting addr2 family to AF_INET and port to 0xDEAF in B.E., then P to N with 104.32.3.66\"$$\n";

addr2->family = AF_INET;
addr2->port = EndianU16(0xDEAF);
PresentationToNetwork(AF_INET, "104.32.3.66", &addr2->address);

ClassRep(addr2,, 9);

"\n$$TX+UL,\"UDPSocket bind with socket2 to addr2\"$$\n";

UDPSocketBind(s2, addr2);

ClassRep(s2,, 9);
//ClassRep(&s2->receive_address,, 9);

"\n$$TX+UL,\"Global Tree:\"$$\n";

ClassRep(udp_globals.bound_socket_tree,, 9);

"\n$$TX+UL,\"Global Tree: Port 0xDEAF Queue\"$$\n";

ClassRep(udp_globals.bound_socket_tree->queue,, 9);
ClassRep(udp_globals.bound_socket_tree->queue->socket,, 9);

"\n$$TX+UL,\"Closing first socket\"$$\n";

UDPSocketClose(s);

"\n$$TX+UL,\"Global Tree:\"$$\n";

ClassRep(udp_globals.bound_socket_tree,, 9);

"\n$$TX+UL,\"Global Tree: Port 0xDEAF Queue\"$$\n";

ClassRep(udp_globals.bound_socket_tree->queue,, 9);
ClassRep(udp_globals.bound_socket_tree->queue->socket,, 9);